/*
 * U01 FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
\subsection Barudan Embroidery Format (.u01)
\addindex u01
\addindex Barudan

The Barudan u01 format is stitch-only.

 */

/* TODO: AFAIK this is a duplicate of U00. Review for differences and merge files and handle accordingly. */

char
readU01(EmbPattern* pattern, FILE* file)
{
    int fileLength, negativeX = 0, negativeY = 0, flags = NORMAL;
    char dx, dy;
    unsigned char data[3];

    if (!check_header_present(file, 0x100)) {
        return 0;
    }

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x100, SEEK_SET);
   
    if (emb_verbose>1) {
        printf("file length: %d\n", fileLength);
    }

    while (fread(data, 1, 3, file) == 3) {
        if (data[0] == 0xF8 || data[0] == 0x87 || data[0] == 0x91) {
            break;
        }
        if ((data[0] & 0x0F) == 0) {
            flags = NORMAL;
        } else if ((data[0] & 0x1f) == 1) {
            flags = JUMP;
        } else if ((data[0] & 0x0F) > 0) {
            flags = STOP;
        }
        negativeX = ((data[0] & 0x20) > 0);
        negativeY = ((data[0] & 0x40) > 0);

        dx = (char) data[2];
        dy = (char) data[1];
        if (negativeX) {
            dx = (char) -dx;
        }
        if (negativeY) {
            dy = (char) -dy;
        }
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writeU01(EmbPattern* pattern, FILE* file)
{
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeU01 */
}
