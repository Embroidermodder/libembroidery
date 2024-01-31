/*
 * PHB FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.

\subsection Brother Embroidery Format (.phb)
\addindex phb
\addindex Brother

The Brother phb format is stitch-only.

 */

/* ---------------------------------------------------------------- */
/* format phb */

char
readPhb(EmbPattern* pattern, FILE* file)
{
    unsigned int fileOffset, readIn;
    short colorCount;
    int i;

    fseek(file, 0x71, SEEK_SET);
    colorCount = fread_int16(file);

    for (i = 0; i < colorCount; i++) {
        EmbThread t = pecThreads[fgetc(file)];
        embPattern_addThread(pattern, t);
    }

    /* TODO: check that file begins with #PHB */
    fseek(file, 0x54, SEEK_SET);
    fileOffset = 0x52;
    embInt_read(file, "fileOffset readin", &readIn, EMB_INT32_LITTLE);
    fileOffset += readIn;

    fseek(file, fileOffset, SEEK_SET);
    embInt_read(file, "fileOffset readin", &readIn, EMB_INT32_LITTLE);
    fileOffset += readIn + 2;

    fseek(file, fileOffset, SEEK_SET);
    embInt_read(file, "fileOffset readin", &readIn, EMB_INT32_LITTLE);
    fileOffset += readIn;

    fseek(file, fileOffset + 14, SEEK_SET); /* 28 */

    colorCount = (short)(char)fgetc(file);
    for (i = 0; i <  colorCount; i++) {
        char stor;
        stor = (char)fgetc(file);
        if (emb_verbose>1) {
            printf("stor: %d\n", stor);
        }
    }
    fseek(file, 4, SEEK_CUR); /* bytes to end of file */
    fseek(file, 17, SEEK_CUR);

    readPecStitches(pattern, file);

    embPattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhb */
}

char
writePhb(EmbPattern* pattern, FILE* file)
{
    puts("ERROR: writePhb is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writePhb */
}
