/*
 * PLT FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
\subsection AutoCAD Embroidery Format (.plt)
\addindex plt
\addindex AutoCAD

The AutoCAD plt format is stitch-only.
 */

/* ---------------------------------------------------------------- */
/* format plt */

char
readPlt(EmbPattern* pattern, FILE* file)
{
    EmbReal x, y;
    EmbReal scalingFactor = 40;
    char input[512];

    /* TODO: replace all scanf code */
    while (emb_readline(file, input, 511)) {
        if (input[0] == 'P' && input[1] == 'D') {
            /* TODO: replace all scanf code */
            if (sscanf(input, "PD%f,%f;", &x, &y) < 2) {
                break;
            }
            embPattern_addStitchAbs(pattern, x / scalingFactor,
                            y / scalingFactor, NORMAL, 1);
        } else if (input[0] == 'P' && input[1] == 'U') {
            /* TODO: replace all scanf code */
            if (sscanf(input, "PU%f,%f;", &x, &y) < 2) {
                break;
            }
            embPattern_addStitchAbs(pattern, x / scalingFactor,
                    y / scalingFactor, STOP, 1);
        }
    }
    return 1;
}

char
writePlt(EmbPattern* pattern, FILE* file) {
    /* TODO: pointer safety */
    EmbReal scalingFactor = 40;
    char firstStitchOfBlock = 1;
    int i;

    fprintf(file, "IN;");
    fprintf(file, "ND;");

    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch stitch;
        stitch = pattern->stitch_list->stitch[i];
        if (stitch.flags & STOP) {
            firstStitchOfBlock = 1;
        }
        if (firstStitchOfBlock) {
            fprintf(file, "PU%f,%f;", stitch.x * scalingFactor,
                    stitch.y * scalingFactor);
            fprintf(file, "ST0.00,0.00;");
            fprintf(file, "SP0;");
            fprintf(file, "HT0;");
            fprintf(file, "HS0;");
            fprintf(file, "TT0;");
            fprintf(file, "TS0;");
            firstStitchOfBlock = 0;
        } else {
            fprintf(file, "PD%f,%f;", stitch.x * scalingFactor,
                stitch.y * scalingFactor);
        }
    }
    fprintf(file, "PU0.0,0.0;");
    fprintf(file, "PU0.0,0.0;");
    return 1; /*TODO: finish WritePlt */
}

