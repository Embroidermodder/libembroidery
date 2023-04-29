/*
 * THR FORMAT
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
\subsection ThredWorks Embroidery Format (.thr)
\addindex thr
\addindex ThreadWorks

The ThreadWorks thr format is stitch-only.
 */

/*
 * bit definitions for attributes of stitch
 * 0-3     stitch color
 * 4-14    form pointer
 * 15-18   spares
 * 19      not a form stitch
 * 20      center walk stitch
 * 21      edge walk stitch
 * 22      underlay stitch
 * 23      knot stitch
 * 24      feather stitch
 * 25-27   layer
 * 28      spare
 * 29-30   stitch type
 *             00=not a form stitch,
 *             01=form fill,
 *             10=form border fill,
 *             11=applique stitches
 * 31      set for user edited stitches
 */

char
readThr(EmbPattern* pattern, FILE* file)
{
    ThredHeader header;
    EmbColor background;
    int currentColor;
    int i;

    embInt_read(file, "sig version", &(header.sigVersion), EMB_INT32_LITTLE);
    embInt_read(file, "length", &(header.length), EMB_INT32_LITTLE);
    embInt_read(file, "number of stitches", &(header.numStiches), EMB_INT16_LITTLE);
    header.hoopSize    = fread_uint16(file);
    for (i=0; i<7; i++) {
        header.reserved[i] = fread_uint16(file);
    }

    if ((header.sigVersion & 0xffffff) == 0x746872) {
        unsigned int verVar = (header.sigVersion & 0xff000000) >> 24;
        switch (verVar) {
            case 0:
                break;
            case 1:
            case 2:
                /* skip the file header extension */
                fseek(file, 144, SEEK_CUR); 
                break;
            default:
                return 0; /* unsupported version */
        }
    }
    currentColor = -1;
    for (i = 0; i < header.numStiches; i++) {
        int type = NORMAL;
        float x, y;
        unsigned int color;
        embInt_read(file, "x", &x, EMB_INT32_LITTLE);
        embInt_read(file, "y", &y, EMB_INT32_LITTLE);
        embInt_read(file, "color", &color, EMB_INT32_LITTLE);
        x /= 10.0;
        y /= 10.0;

        if ((int)(color & 0xF) != currentColor) {
            currentColor = (int)color & 0xF;
            embPattern_changeColor(pattern, currentColor);
            type = STOP | TRIM;
        }
        embPattern_addStitchAbs(pattern, x, y, type, 0);
    }
    fseek(file, 16, SEEK_CUR); /* skip bitmap name (16 chars) */

    embColor_read(file, &background, 4);
    if (emb_verbose>1) {
        printf("background: %c %c %c\n", background.r, background.g, background.b);
    }
    for (i = 0; i < 16; i++) {
        EmbThread thread;
        strcpy(thread.description, "NULL");
        strcpy(thread.catalogNumber, "NULL");
        embColor_read(file, &(thread.color), 4);
        embPattern_addThread(pattern, thread);
    }
    /*  64 bytes of rgbx(4 bytes) colors (16 custom colors) */
    /*  16 bytes of thread size (ascii representation ie. '4') */
    return 1;
}

char
writeThr(EmbPattern* pattern, FILE* file)
{
    int i, stitchCount;
    unsigned char version = 0;
    ThredHeader header;
    ThredExtension extension;
    char bitmapName[16];

    stitchCount = pattern->stitch_list->count;

    memset(&header, 0, sizeof(ThredHeader));
    header.sigVersion = 0x746872 | (version << 24);
    header.length = stitchCount * 12 + 16;
    if (version == 1 || version == 2) {
        header.length = header.length + sizeof(ThredHeader);
    }
    header.numStiches = (unsigned short)stitchCount; /* number of stitches in design */
    header.hoopSize = 5;

    binaryWriteUInt(file, header.sigVersion);
    binaryWriteUInt(file, header.length);
    binaryWriteUShort(file, header.numStiches);
    binaryWriteUShort(file, header.hoopSize);
    for (i=0; i<7; i++) {
        binaryWriteUShort(file, header.reserved[i]);
    }

    if (version == 1 || version == 2) {
        memset(&extension, 0, sizeof(ThredExtension));
        extension.auxFormat = 1;
        extension.hoopX = 640;
        extension.hoopY = 640;

        embInt_write(file, ".", &(extension.hoopX), EMB_INT32_LITTLE);
        embInt_write(file, ".", &(extension.hoopY), EMB_INT32_LITTLE);
        embInt_write(file, ".", &(extension.stitchGranularity), EMB_INT32_LITTLE);
        fwrite(extension.creatorName, 1, 50, file);
        fwrite(extension.modifierName, 1, 50, file);
        fputc(extension.auxFormat, file);
        fwrite(extension.reserved, 1, 31, file);
    }

    /* write stitches */
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned int NOTFRM = 0x00080000;
        EmbStitch st = pattern->stitch_list->stitch[i];
        float x, y;
        x = (float)(st.x * 10.0);
        y = (float)(st.y * 10.0);
        embInt_write(file, ".", &x, EMB_INT32_LITTLE);
        embInt_write(file, ".", &y, EMB_INT32_LITTLE);
        binaryWriteUInt(file, NOTFRM | (st.color & 0x0F));
    }
    fwrite(bitmapName, 1, 16, file);
    /* background color */
    fwrite("\xFF\xFF\xFF\x00", 1, 4, file);

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c = pattern->thread_list->thread[i].color;
        embColor_write(file, c, 4);
        if (i >= 16) break;
    }

    /* write remaining colors if not yet 16 */
    fpad(file, 0, 4*(16-i));

    fpad(file, '4', 16);
    return 1;
}
