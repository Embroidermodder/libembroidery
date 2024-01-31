/*
 * 100 FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
\subsection embroidery-inf-format Embroidery Color Format (.inf)
\addindex inf

Stitch Only Format.

 */

/* ---------------------------------------------------------------- */
/* format inf */

char
readInf(EmbPattern* pattern, FILE* file)
{
    int nColors, i;
    char colorType[50];
    char colorDescription[50];
    EmbThread t;

    fseek(file, 12, SEEK_CUR);
    embInt_read(file, "nColors", &nColors, EMB_INT32_BIG);

    pattern->thread_list->count = 0;

    for (i = 0; i < nColors; i++) {
        fseek(file, 4, SEEK_CUR);
        embColor_read(file, &(t.color), 3);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        embPattern_addThread(pattern, t);
        fseek(file, 2, SEEK_CUR);
        binaryReadString(file, colorType, 50);
        binaryReadString(file, colorDescription, 50);
    }
    return 1;
}

char
writeInf(EmbPattern* pattern, FILE* file)
{
    int i, bytesRemaining;

    binaryWriteUIntBE(file, 0x01);
    binaryWriteUIntBE(file, 0x08);
    /* write place holder offset */
    binaryWriteUIntBE(file, 0x00);
    binaryWriteUIntBE(file, pattern->thread_list->count);

    for (i = 0; i < pattern->thread_list->count; i++) {
        char buffer[50];
        unsigned short record_length, record_number, needle_number;
        EmbColor c;
        c = pattern->thread_list->thread[i].color;
        sprintf(buffer, "RGB(%d,%d,%d)", (int)c.r, (int)c.g, (int)c.b);
        record_length = 14 + strlen(buffer);
        record_number = i;
        needle_number = i;
        embInt_write(file, "record length", &record_length, EMB_INT16_BIG);
        embInt_write(file, "record number", &record_number, EMB_INT16_BIG);
        embColor_write(file, c, 3);
        embInt_write(file, "needle number", &needle_number, EMB_INT16_BIG);
        fwrite("RGB\0", 1, 4, file);
        fprintf(file, "%s", buffer);
        fwrite("\0", 1, 1, file);
    }
    /* It appears that there should be a pad here otherwise it clips into
     * the color description. */
    fpad(file, 0, 8);
    fseek(file, -8, SEEK_END);
    bytesRemaining = ftell(file);
    fseek(file, 8, SEEK_SET);
    binaryWriteUIntBE(file, bytesRemaining);
    return 1;
}
