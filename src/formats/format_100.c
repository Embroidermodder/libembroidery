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

char
read100(EmbPattern* pattern, FILE* file)
{
    unsigned char b[4];

    while (fread(b, 1, 4, file) == 4) {
        int x, y;
        int stitchType;
        stitchType = NORMAL;
        x = (b[2] > 0x80) ? -(b[2] - 0x80) : b[2];
        y = (b[3] > 0x80) ? -(b[3] - 0x80) : b[3];
        /*if (!(b[0] & 0xFC)) stitchType = JUMP; TODO: review & fix */
        if (!(b[0] & 0x01)) stitchType = STOP;
        if (b[0] == 0x1F) stitchType = END;
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }
    return 1;
}

char
write100(EmbPattern* pattern, FILE* file)
{
    int i;
    EmbVector delta, position;

    position = pattern->home;
    for (i=0; i<pattern->stitch_list->count; i++) {
        unsigned char b[4];
        EmbStitch st = pattern->stitch_list->stitch[i];
        delta.x = st.x - position.x;
        delta.y = st.y - position.y;
        position = embVector_add(position, delta);
        b[0] = 0;
        b[1] = 0;
        if (delta.x < 0.0) {
            b[2] = -emb_round(10.0*delta.x);
        }
        else {
            b[2] = emb_round(10.0*delta.x);
        }
        if (delta.y < 0.0) {
            b[3] = -emb_round(10.0*delta.y);
        }
        else {
            b[3] = emb_round(10.0*delta.y);
        }
        if (!(st.flags & STOP)) {
            b[0] |= 0x01;
        }
        if (st.flags & END) {
            b[0] = 0x1F;
        }
        fwrite(b, 1, 4, file);
    }
    return 1;
}
