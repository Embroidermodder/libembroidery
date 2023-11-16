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
 * \file format_emd.c The Elna Embroidery Format (.emd)
 * \addindex emd
 * \addindex Elna
 *
 * Stitch Only Format.
 */


char
emdDecode(unsigned char inputByte) {
    if (inputByte >= 0x80) {
        return (-~inputByte) - 1;
    }
    return inputByte;
}

char
readEmd(EmbPattern* pattern, FILE* file) {
    unsigned char b[2];
    unsigned char jemd0[6]; /* TODO: more descriptive name */
    int width, height, colors, length;

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    if (length < 0x30) {
        puts("File invalid: shorter than the header.");
        return 0;
    }
    fseek(file, 0, SEEK_SET);

    fread(jemd0, 1, 6, file); /* TODO: check return value */
    embInt_read(file, "width", &width, EMB_INT16_LITTLE);
    embInt_read(file, "height", &height, EMB_INT16_LITTLE);
    embInt_read(file, "colors", &colors, EMB_INT16_LITTLE);

    fseek(file, 0x30, SEEK_SET);

    while (!feof(file)) {
        char dx, dy;
        int flags = NORMAL;
        fread(b, 1, 2, file);

            if (b[0] == 0x80) {
                if (b[1] == 0x2A) {
                    embPattern_addStitchRel(pattern, 0, 0, STOP, 1);
                    continue;
                } else if (b[1] == 0x80) {
                    fread(b, 1, 2, file);
                    flags = TRIM;
                } else if (b[1] == 0xFD) {
                    embPattern_addStitchRel(pattern, 0, 0, END, 1);
                    break;
                } else {
                    continue;
                }
            }
            dx = emdDecode(b[0]);
            dy = emdDecode(b[1]);
            embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writeEmd(EmbPattern* pattern, FILE* file) {
    puts("writeEmd not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeEmd */
}
