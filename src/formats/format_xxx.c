/*
 * XXX FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
\subsection Singer Embroidery Format (.xxx)
\addindex xxx
\addindex Singer

The Singer xxx format is stitch-only.
 */

char
xxxDecodeByte(unsigned char inputByte)
{
    if (inputByte >= 0x80) {
        return (char) ((-~inputByte) - 1);
    }
    return ((char) inputByte);
}

char
readXxx(EmbPattern* pattern, FILE* file)
{
    int dx = 0, dy = 0, numberOfColors, paletteOffset, i;
    char thisStitchJump = 0;

    if (emb_verbose>1) {
        puts("readXxx has been overridden.");
        return 0;
    }

    fseek(file, 0x27, SEEK_SET);
    embInt_read(file, ".", &numberOfColors, EMB_INT16_LITTLE);
    fseek(file, 0xFC, SEEK_SET);
    embInt_read(file, ".", &paletteOffset, EMB_INT32_LITTLE);
    fseek(file, paletteOffset + 6, SEEK_SET);

    for (i = 0; i < numberOfColors; i++) {
        EmbThread thread;
        strcpy(thread.catalogNumber, "NULL");
        strcpy(thread.description, "NULL");
        fseek(file, 1, SEEK_CUR);
        embColor_read(file, &(thread.color), 3);
        embPattern_addThread(pattern, thread);
    }
    fseek(file, 0x100, SEEK_SET);

    for (i = 0; !feof(file) && ftell(file) < paletteOffset; i++) {
        unsigned char b0, b1;
        int flags;
        flags = NORMAL;
        if (thisStitchJump) flags = TRIM;
        thisStitchJump = 0;
        b0 = (char)fgetc(file);
        b1 = (char)fgetc(file);
        /* TODO: ARE THERE OTHER BIG JUMP CODES? */
        if (b0 == 0x7E || b0 == 0x7D) {
            dx = b1 + ((char)fgetc(file) << 8);
            dx = ((short) dx);
            dy = fread_int16(file);
            flags = TRIM;
        } else if (b0 == 0x7F) {
            /* TODO: LOOKS LIKE THESE CODES ARE IN THE HEADER */
            if (b1 != 0x17 && b1 != 0x46 && b1 >= 8) {
                b0 = 0;
                b1 = 0;
                thisStitchJump = 1;
                flags = STOP;
            } else if (b1 == 1) {
                flags = TRIM;
                b0 = (char)fgetc(file);
                b1 = (char)fgetc(file);
            } else {
                continue;
            }
            dx = xxxDecodeByte(b0);
            dy = xxxDecodeByte(b1);
        } else {
            dx = xxxDecodeByte(b0);
            dy = xxxDecodeByte(b1);
        }
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    /* TODO: check end of pattern for multiple STOPs */
    return 1;
}

void
xxxEncodeStop(FILE* file, EmbStitch s)
{
    fputc((unsigned char)0x7F, file);
    fputc((unsigned char)(s.color + 8), file);
}

void
xxxEncodeStitch(FILE* file, EmbReal deltaX, EmbReal deltaY, int flags)
{
    if ((flags & (JUMP | TRIM)) && (fabs(deltaX) > 124 || fabs(deltaY) > 124)) {
        fputc(0x7E, file);
        /* Does this cast work right? */
        binaryWriteShort(file, (short)deltaX);
        binaryWriteShort(file, (short)deltaY);
    } else {
        /* TODO: Verify this works after changing this to unsigned char */
        fputc((unsigned char)emb_round(deltaX), file);
        fputc((unsigned char)emb_round(deltaY), file);
    }
}

void
xxxEncodeDesign(FILE* file, EmbPattern* p)
{
    int i;
    EmbReal thisX = 0.0f;
    EmbReal thisY = 0.0f;

    if (p->stitch_list->count > 0) {
        thisX = (float)p->stitch_list->stitch[0].x;
        thisY = (float)p->stitch_list->stitch[0].y;
    }
    for (i = 0; i < p->stitch_list->count; i++) {
        EmbStitch s = p->stitch_list->stitch[i];
        EmbReal deltaX, deltaY;
        EmbReal previousX = thisX;
        EmbReal previousY = thisY;
        thisX = s.x;
        thisY = s.y;
        deltaX = thisX - previousX;
        deltaY = thisY - previousY;
        if (s.flags & STOP) {
            xxxEncodeStop(file, s);
        } else if (s.flags & END) {
        } else {
            xxxEncodeStitch(file, deltaX * 10.0f, deltaY * 10.0f, s.flags);
        }
    }
}

char
writeXxx(EmbPattern* pattern, FILE* file)
{
    int i;
    EmbRect rect;
    int endOfStitches;
    EmbReal width, height;
    short to_write;
    unsigned int n_stitches;
    unsigned short n_threads;

    embPattern_correctForMaxStitchLength(pattern, 124, 127);

    fpad(file, 0, 0x17);
    n_stitches = (unsigned int)pattern->stitch_list->count;
    embInt_write(file, "n_stitches", &n_stitches, EMB_INT32_LITTLE);

    fpad(file, 0, 0x0C);
    n_threads = (unsigned short)pattern->thread_list->count;
    embInt_write(file, "n_threads", &n_threads, EMB_INT16_LITTLE);

    fpad(file, 0, 0x02);

    rect = embPattern_calcBoundingBox(pattern);
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;
    to_write = (short)(width * 10.0);
    embInt_write(file, "width", &to_write, EMB_INT16_LITTLE);
    to_write = (short)(height * 10.0);
    embInt_write(file, "height", &to_write, EMB_INT16_LITTLE);

    /*TODO: xEnd from start point x=0 */
    to_write = (short)(width / 2.0 * 10);
    embInt_write(file, "xEnd from start", &to_write, EMB_INT16_LITTLE);
    /*TODO: yEnd from start point y=0 */
    to_write = (short)(height / 2.0 * 10);
    embInt_write(file, "yEnd from start", &to_write, EMB_INT16_LITTLE);
    /*TODO: left from start x = 0     */
    to_write = (short)(width / 2.0 * 10);
    embInt_write(file, "left from start", &to_write, EMB_INT16_LITTLE);
    /*TODO: bottom from start y = 0   */
    to_write = (short)(height / 2.0 * 10);
    embInt_write(file, "bottom from start", &to_write, EMB_INT16_LITTLE);

    fpad(file, 0, 0xC5);

    /* place holder for end of stitches */
    binaryWriteInt(file, 0x0000);
    xxxEncodeDesign(file, pattern);
    endOfStitches = ftell(file);
    fseek(file, 0xFC, SEEK_SET);
    binaryWriteUInt(file, endOfStitches);
    fseek(file, 0, SEEK_END);
    /* is this really correct? */
    fwrite("\x7F\x7F\x03\x14\x00\x00", 1, 6, file);

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c = pattern->thread_list->thread[i].color;
        fputc(0x00, file);
        embColor_write(file, c, 3);
    }
    for (i = 0; i < (22 - pattern->thread_list->count); i++) {
        unsigned int padder = 0x01000000;
        embInt_write(file, "padder", &padder, EMB_INT32_LITTLE);
    }
    fwrite("\x00\x01", 1, 2, file);
    return 1;
}
