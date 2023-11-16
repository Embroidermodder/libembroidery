/*
 * 10o FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
 * \file format_10o.c The Toyota Embroidery Format (.100)
 * \addindex 100
 * \addindex Toyota
 *
 * The Toyota 100 format is a stitch-only format that
 * uses an external color file.
 *
 * The stitch encoding is in 4 byte chunks.
 */

char
read10o(EmbPattern* pattern, FILE* file)
{
    unsigned char b[3];
    while (fread(b, 1, 3, file) == 3) {
        int x, y;
        int stitchType = NORMAL;
        unsigned char ctrl = b[0];
        y = b[1];
        x = b[2];
        if (ctrl & 0x20) {
            x = -x;
        }
        if (ctrl & 0x40) {
            y = -y;
        }
        if (ctrl & 0x01) {
            stitchType = TRIM;
        }
        if ((ctrl & 0x5) == 5) {
            stitchType = STOP;
        }
        if (ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }
    return 1;
}

char
write10o(EmbPattern* pattern, FILE* file)
{
    int i;
    for (i=0; i<pattern->stitch_list->count; i++) {
        unsigned char b[3];
        EmbStitch st = pattern->stitch_list->stitch[i];
        b[0] = 0;
        b[1] = 0;
        b[2] = 0;
        if (st.x < 0) {
            b[2] |= 0x20;
            b[0] = -st.x;
        }
        else {
            b[0] = st.x;
        }
        if (st.y < 0) {
            b[2] |= 0x40;
            b[1] = -st.y;
        }
        else {
            b[1] = st.y;
        }
        if (st.flags == TRIM) {
            b[2] |= 1;
        }
        if (st.flags == STOP) {
            b[2] |= 5;
        }
        if (st.flags == END) {
            b[2] = 0xF8;
        }
        fwrite(b, 1, 3, file);   
    }
    return 1;
}
