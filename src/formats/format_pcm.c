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

/**
 *
\subsection pfaff-pcm-format Pfaff Embroidery Format (.pcm)
\addindex pcm
\addindex Pfaff

The Pfaff pcm format is stitch-only.
 */

char
readPcm(EmbPattern* pattern, FILE* file)
{
    int i = 0, st;
    EmbReal dx = 0, dy = 0;
    int header_size = 16*2+6;

    if (emb_verbose>1) {
        printf("TODO: check header_size %d\n", header_size);
    }

    fseek(file, 4, SEEK_SET);
    for (i = 0; i < 16; i++) {
        int colorNumber;
        (void)fgetc(file); /* zero */
        colorNumber = fgetc(file);
        embPattern_addThread(pattern, pcmThreads[colorNumber]);
    }
    embInt_read(file, "st", &st, EMB_INT16_BIG);
    st = EMB_MIN(st, MAX_STITCHES);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        int flags;
        unsigned char b[9];
        flags = NORMAL;
        if (fread(b, 1, 9, file) != 9) {
            break;
        }
        if (b[8] & 0x01) {
            flags = STOP;
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
        /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[2], b[1], b[0]);
        dy = pfaffDecode(b[6], b[5], b[4]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writePcm(EmbPattern* pattern, FILE* file)
{
    puts("overridden, defaulting to dst");
    writeDst(pattern, file);
    return 0; /*TODO: finish writePcm */
}
