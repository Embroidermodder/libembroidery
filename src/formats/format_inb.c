/*
 * 100 FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
 *
\subsection inbro-inb-format Inbro Embroidery Format (.inb)
\addindex inb
\addindex Inbro

Stitch Only Format.

 */

/* ---------------------------------------------------------------- */
/* format inb */

char
readInb(EmbPattern* pattern, FILE* file)
{
    /* TODO: determine what this represents */
    unsigned char fileDescription[8], nullVal, bytesUnknown[300];
    int stitchCount, x, y, i, fileLength;
    short width, height, colorCount, unknown3, unknown2,
        nullbyte, left, right, top, bottom, imageWidth, imageHeight;

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fread(fileDescription, 1, 8, file); /* TODO: check return value */
    nullVal = (char)fgetc(file);
    fgetc(file);
    fgetc(file);
    embInt_read(file, "stitchCount", &stitchCount, EMB_INT32_LITTLE);
    embInt_read(file, "width", &width, EMB_INT16_LITTLE);
    embInt_read(file, "height", &height, EMB_INT16_LITTLE);
    colorCount = fread_int16(file);
    unknown3 = fread_int16(file);
    unknown2 = fread_int16(file);
    imageWidth = fread_int16(file);
    imageHeight = fread_int16(file);
    fread(bytesUnknown, 1, 300, file); /* TODO: check return value */
    nullbyte = fread_int16(file);
    embInt_read(file, "left", &left, EMB_INT16_LITTLE);
    embInt_read(file, "right", &right, EMB_INT16_LITTLE);
    embInt_read(file, "top", &top, EMB_INT16_LITTLE);
    embInt_read(file, "bottom", &bottom, EMB_INT16_LITTLE);
    if (emb_verbose>1) {
        printf("nullVal:                 %c\n", nullVal);
        printf("colorCount:              %d\n", colorCount);
        printf("Identify the purpose of:\n");
        printf("    unknown3:            %d\n", unknown3);
        printf("    unknown2:            %d\n", unknown2);
        printf("imageWidth:              %d\n", imageWidth);
        printf("imageHeight:             %d\n", imageHeight);
        printf("This should be null:     %d\n", nullbyte);
    }

    fseek(file, 0x2000, SEEK_SET);
    /* Calculate stitch count since header has been seen to be blank */
    stitchCount = (int)((fileLength - 0x2000) / 3);
    for (i = 0; i < stitchCount; i++) {
        unsigned char type;
        int stitch = NORMAL;
        x = (char)fgetc(file);
        y = (char)fgetc(file);
        type = (char)fgetc(file);
        if ((type & 0x40) > 0)
            x = -x;
        if ((type & 0x10) > 0)
            y = -y;
        if ((type & 1) > 0)
            stitch = STOP;
        if ((type & 2) > 0)
            stitch = TRIM;
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitch, 1);
    }
    embPattern_flipVertical(pattern);

    return 1;
}

char
writeInb(EmbPattern* pattern, FILE* file)
{
    puts("ERROR: writeInb not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeInb */
}
