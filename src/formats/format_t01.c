/*
 * T09 FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

char
readT01(EmbPattern* pattern, FILE* file)
{
    unsigned char b[3];

    while (fread(b, 1, 3, file) == 3) {
        int flags, x, y;
        decode_t01_record(b, &flags, &x, &y);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        if (flags == END) {
            break;
        }
    }
    return 1;
}

char
writeT01(EmbPattern* pattern, FILE* file)
{
    EmbRect boundingRect;
    int i;
    EmbVector pos;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    boundingRect = embPattern_calcBoundingBox(pattern);
    if (emb_verbose>1) {
        printf("bounding rectangle with top %f not used ", boundingRect.top);
        printf("in the function writeT01\n");
    }
    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        unsigned char b[3];
        int dx, dy;
        EmbStitch st = pattern->stitchList->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)emb_round(10.0*(st.x - pos.x));
        dy = (int)emb_round(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;
        encode_t01_record(b, dx, dy, st.flags);
        fwrite(b, 1, 3, file);
    }
    return 1;
}
