/*
 * VP3 FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

char
readMit(EmbPattern* pattern, FILE* file)
{
    unsigned char data[2];

    while (fread(data, 1, 2, file) == 2) {
        int x = mitDecodeStitch(data[0]);
        int y = mitDecodeStitch(data[1]);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, NORMAL, 1);
    }
    return 1;
}

char
writeMit(EmbPattern* pattern, FILE* file)
{
    EmbReal xx, yy;
    int i;

    embPattern_correctForMaxStitchLength(pattern, 0x1F, 0x1F);
    xx = 0;
    yy = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned char b[2];
        EmbStitch st = pattern->stitch_list->stitch[i];
        b[0] = mitEncodeStitch(st.x - xx);
        b[1] = mitEncodeStitch(st.y - yy);
        xx = st.x;
        yy = st.y;
        fwrite(b, 1, 2, file);
    }
    return 1;
}
