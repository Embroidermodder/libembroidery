/*
 * PCQ FORMAT
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
\subsection Pfaff Embroidery Format (.pcq)
\addindex pcq
\addindex Pfaff

The Pfaff pcq format is stitch-only.
 */

char
readPcq(EmbPattern* pattern, const char* fileName, FILE* file)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    EmbReal dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount;

    version = (char)fgetc(file);
    hoopSize = (char)fgetc(file);
    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * 3 for PCS with large hoop (115x120)
     */
    colorCount = fread_uint16(file);
    if (emb_verbose>1) {
        printf("version: %d\n", version);
        printf("hoop size: %d\n", hoopSize);
        printf("color count: %d\n", colorCount);
    }

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        embPattern_addThread(pattern, t);
    }
    if (allZeroColor) {
        embPattern_loadExternalColorFile(pattern, fileName);
    }
    st = fread_uint16(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        flags = NORMAL;
        if (fread(b, 1, 9, file) != 9) {
            break;
        }

        if (b[8] & 0x01) {
            flags = STOP;
        }
        else if (b[8] & 0x04) {
            flags = TRIM;
        }
        else if (b[8] != 0) {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[1], b[2], b[3]);
        dy = pfaffDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writePcq(EmbPattern* pattern, FILE* file)
{
    int i;

    /* TODO: select hoop size defaulting to Large PCS hoop */
    fwrite("2\x03", 1, 2, file);
    binaryWriteUShort(file, (unsigned short)pattern->thread_list->count);
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor color = pattern->thread_list->thread[i].color;
        embColor_write(file, color, 4);
    }

    /* write remaining colors to reach 16 */
    fpad(file, 0, (16-i)*4);

    binaryWriteUShort(file, (unsigned short)pattern->stitch_list->count);
    /* write stitches */
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        pfaffEncode(file, (int)emb_round(st.x * 10.0), (int)emb_round(st.y * 10.0), st.flags);
    }
    return 1;
}