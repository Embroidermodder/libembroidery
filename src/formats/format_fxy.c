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
\subsection Fortron Embroidery Format (.fxy)
\addindex fxy
\addindex Fortron

Stitch Only Format.
 */

char
readFxy(EmbPattern* pattern, FILE* file)
{
    /* TODO: review for combining code. This line appears 
        to be the only difference from the GT format. */
    fseek(file, 0x100, SEEK_SET);

    while (!feof(file)) {
        int stitchType = NORMAL;
        int b1 = fgetc(file);
        int b2 = fgetc(file);
        unsigned char commandByte = (unsigned char)fgetc(file);

        if (commandByte == 0x91) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        if ((commandByte & 0x01) == 0x01)
            stitchType = TRIM;
        if ((commandByte & 0x02) == 0x02)
            stitchType = STOP;
        if ((commandByte & 0x20) == 0x20)
            b1 = -b1;
        if ((commandByte & 0x40) == 0x40)
            b2 = -b2;
        embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    return 1;
}

char
writeFxy(EmbPattern* pattern, FILE* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeFxy */
}
