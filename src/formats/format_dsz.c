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

/**
 *

\subsection zsk-dsz-format ZSK USA Embroidery Format (.dsz)
\addindex dsz
\addindex ZSK USA

The ZSK USA dsz format is stitch-only.

 */

char
readDsz(EmbPattern* pattern, FILE* file)
{
    unsigned char b[3];

    fseek(file, 0x200, SEEK_SET);
    while (fread(b, 1, 3, file) == 3) {
        int x, y;
        unsigned char ctrl;
        int stitchType = NORMAL;

        y = b[0];
        x = b[1];
        ctrl = b[2];
        if (ctrl & 0x01) {
            stitchType = TRIM;
        }
        if (ctrl & 0x20) {
            y = -y;
        }
        if (ctrl & 0x40) {
            x = -x;
        }
        if (ctrl & 0x0E) {
            /*
            TODO: Add back if head number is added to the library 
            int headNumber = (ctrl & 0x0E) >> 1;
            */
            stitchType = STOP;
        }
        if (ctrl & 0x10) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x  / 10.0, y  / 10.0, stitchType, 1);
    }
    return 1;
}

/* WARNING: this is untested.
 * This is based on the readDsz function.
 */
char
writeDsz(EmbPattern* pattern, FILE* file)
{
    int i;
    EmbVector delta;
    EmbVector start;
    fpad(file, ' ', 200);
    start.x = 0.0;
    start.y = 0.0;
    for (i=0; i<pattern->stitch_list->count; i++) {
        EmbVector pos;
        EmbStitch st;
        unsigned char b[3];
        st = pattern->stitch_list->stitch[i];
        pos.x = st.x;
        pos.y = st.y;
        delta = embVector_subtract(pos, start);
        b[2] = 0;
        if (st.flags & TRIM) {
            b[2] |= 0x01;
        }
        if (10.0*delta.x < 0.0) {
            b[2] |= 0x20;
        }
        if (10.0*delta.y < 0.0) {
            b[2] |= 0x40;
        }
        if (st.flags & STOP) {
            b[2] |= 0x0E;
        }
        if (st.flags & END) {
            b[2] |= 0x10;
        }
        b[0] = emb_round(10.0*delta.x);
        b[1] = emb_round(10.0*delta.y);
        fwrite(b, 1, 3, file);
    }
    return 1;
}

