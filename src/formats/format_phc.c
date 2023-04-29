/*
 * PHC FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
\subsection Brother Embroidery Format (.phc)
\addindex phc
\addindex Brother

The Brother phc format is stitch-only.
 */

char
readPhc(EmbPattern* pattern, FILE* file)
{
    int colorChanges, version, bytesInSection2;
    unsigned int fileLength;
    unsigned short pecOffset, bytesInSection, bytesInSection3;
    char pecAdd;
    int i;

    fseek(file, 0x07, SEEK_SET);
    version = (char)fgetc(file) - 0x30; /* converting from ansi number */
    fseek(file, 0x4D, SEEK_SET);
    colorChanges = fread_uint16(file);

    for (i = 0; i < colorChanges; i++) {
        EmbThread t = pecThreads[(int)(char)fgetc(file)];
        embPattern_addThread(pattern, t);
    }
    fseek(file, 0x2B, SEEK_SET);
    pecAdd = (char)fgetc(file);
    embInt_read(file, "file length", &fileLength, EMB_INT32_LITTLE);
    pecOffset = fread_uint16(file);
    fseek(file, pecOffset + pecAdd, SEEK_SET);
    bytesInSection = fread_uint16(file);
    fseek(file, bytesInSection, SEEK_CUR);
    embInt_read(file, "bytes in sec 2", &bytesInSection2, EMB_INT32_LITTLE);
    fseek(file, bytesInSection2, SEEK_CUR);
    bytesInSection3 = fread_uint16(file);
    fseek(file, bytesInSection3 + 0x12, SEEK_CUR);

    if (emb_verbose>1) {
        printf("version: %d\n", version);
    }

    readPecStitches(pattern, file);

    embPattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhc */
}

char
writePhc(EmbPattern* pattern, FILE* file)
{
    puts("ERROR: writePhc is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writePhc */
}

