/*
 * BRO FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
 * \file format_bro.c The Bits and Volts Embroidery Format (.bro)
 * \addindex bro
 * \addindex Bits and Volts
 * 
 * The Bits and Volts bro format is a stitch-only format that
 * uses an external color file.
 * 
 * The header is 256 bytes.
 * There's a series of unknown variables in the header.
 * 
 * The stitch list uses a variable length encoding which is
 * 2 bytes for any stitch.
 */

char
readBro(EmbPattern* pattern, FILE* file)
{
    unsigned char x55;
    short unknown1, unknown2, unknown3, unknown4, moreBytesToEnd;
    char name[8];
    int stitchType;
    fread(&x55, 1, 1, file);
    /* TODO: determine what this unknown data is */
    fread(&unknown1, 2, 1, file);

    fread(name, 1, 8, file);
    /* TODO: determine what this unknown data is */
    fread(&unknown2, 2, 1, file);
    /* TODO: determine what this unknown data is */
    fread(&unknown3, 2, 1, file);
    /* TODO: determine what this unknown data is */
    fread(&unknown4, 2, 1, file);
    fread(&moreBytesToEnd, 2, 1, file);

    fseek(file, 0x100, SEEK_SET);

    while (!feof(file)) {
        short b1, b2;
        stitchType = NORMAL;
        b1 = (unsigned char)fgetc(file);
        b2 = (unsigned char)fgetc(file);
        if (b1 == -128) {
            unsigned char bCode = (unsigned char)fgetc(file);
            fread(&b1, 2, 1, file);
            fread(&b2, 2, 1, file);
            /* Embird uses 0x02 and Wilcom uses 0xE1 */
            if (bCode == 0x02 || bCode == 0xE1) {
                stitchType = STOP;
            } else if (bCode == 3) {
                stitchType = TRIM;
            } else if (bCode == 0x7E) {
                embPattern_addStitchRel(pattern, 0, 0, END, 1);
                break;
            }
        }
        embPattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }
    return 1;
}

char
writeBro(EmbPattern* pattern, FILE* file)
{
    puts("writeBro is not implemented");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeBro */
}
