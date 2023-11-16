/*
 * ZSK FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <string.h>

/**
 * \file format_zsk.c The ZSK USA Embroidery Format (.zsk)
 * \addindex zsk
 * \addindex ZSK USA
 *
 * The ZSK USA zsk format is stitch-only.
 */

#include "../embroidery_internal.h"

char
readZsk(EmbPattern* pattern, FILE* file)
{
    char b[3];
    int stitchType;
    unsigned char colorNumber;

    fseek(file, 0, SEEK_END);
    if (ftell(file) < 0x230) {
        return 0;
    }

    fseek(file, 0x230, SEEK_SET);
    colorNumber = fgetc(file);
    while (colorNumber != 0) {
        EmbThread t;
        embColor_read(file, &(t.color), 3);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        embPattern_addThread(pattern, t);
        fseek(file, 0x48, SEEK_CUR);
        colorNumber = fgetc(file);
    }
    fseek(file, 0x2E, SEEK_CUR);

    while (fread(b, 1, 3, file) == 3) {
        stitchType = NORMAL;
        if (b[0] & 0x04) {
            b[2] = -b[2];
        }
        if (b[0] & 0x08) {
            b[1] = -b[1];
        }
        if (b[0] & 0x02) {
            stitchType = JUMP;
        }
        if (b[0] & 0x20) {
            if (b[1] == 2) {
                stitchType = TRIM;
            } else if (b[1] == -1) {
                break;
            } else {
                if (b[2] != 0) {
                    colorNumber = b[2];
                }
                /* TODO: need to determine what b[1] is used for.*/
                stitchType = STOP;
                embPattern_changeColor(pattern, colorNumber - 1);
            }
            b[1] = 0;
            b[2] = 0;
        }
        embPattern_addStitchRel(pattern, b[1] / 10.0,
            b[2] / 10.0, stitchType, 0);
    }

    return 1;
}

/* based on the readZsk function */
char
writeZsk(EmbPattern* pattern, FILE* file)
{
    int i;

    fpad(file, 0x00, 0x230);

    fprintf(file, "%c", pattern->thread_list->count);
    for (i=pattern->thread_list->count; i>0; i--) {
        EmbThread t = pattern->thread_list->thread[i-1];
        embColor_write(file, t.color, 3);
        fpad(file, 0x00, 0x48);
        fprintf(file, "%c", i-1);
    }

    fpad(file, 0x00, 0x2E);

    for (i=0; i<pattern->stitch_list->count; i++) {
        EmbStitch st;
        unsigned char b[3];
        st = pattern->stitch_list->stitch[i];
        b[0] = 0;
        b[1] = st.x;
        b[2] = st.y;
        if (st.flags & JUMP) {
            b[0] |= 0x02;
        }
        if (st.x < 0) {
            b[0] |= 0x08;
            b[1] = -st.x;
        }
        if (st.y < 0) {
            b[0] |= 0x04;
            b[2] = -st.y;
        }
        if (st.flags & TRIM) {
            b[0] |= 0x20;
            b[1] = 0x00;
            b[2] = 0x00;
        }
        if (st.flags & STOP) {
            b[0] |= 0x20;
            b[1] = 0x00;
            b[2] = st.color;
        }
        if (st.flags & END) {
            b[0] |= 0x20;
            b[1] = 0x80;
            b[2] = 0x00;
            fwrite(b, 1, 3, file);
            break;
        }
        fwrite(b, 1, 3, file);
    }
    return 1;
}
