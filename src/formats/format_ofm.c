/*
 * OFM FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
\subsection melco-ofm-format Melco Embroidery Format (.ofm)
\addindex ofm
\addindex Melco

Stitch Only Format.
 */

char*
ofmReadLibrary(FILE* file)
{
    int stringLength = 0;
    char* libraryName = 0;
    /* FF FE FF */
    unsigned char leadIn[3];

    if (!file) { printf("ERROR: format-ofm.c ofmReadLibrary(), file argument is null\n"); return 0; }

    fread(leadIn, 1, 3, file); /* TODO: check return value */
    stringLength = (char)fgetc(file);
    libraryName = (char*)malloc(sizeof(char) * stringLength * 2);
    if (!libraryName) { printf("ERROR: format-ofm.c ofmReadLibrary(), unable to allocate memory for libraryName\n"); return 0; }
    fread((unsigned char*)libraryName, 1, stringLength * 2, file); /* TODO: check return value */
    return libraryName;
}

static int
ofmReadClass(FILE* file)
{
    int len;
    char* s = 0;

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadClass(), file argument is null\n");
        return 0;
    }

    fread_int16(file);
    len = fread_int16(file);

    s = (char*)malloc(sizeof(char) * len + 1);
    if (!s) {
        printf("ERROR: format-ofm.c ofmReadClass(), unable to allocate memory for s\n");
        return 0;
    }
    fread((unsigned char*)s, 1, len, file);
    /* TODO: check return value */
    s[len] = '\0';
    if (strcmp(s, "CExpStitch") == 0) {
        return 0x809C;
    }
    if (strcmp(s, "CColorChange") == 0) {
        return 0xFFFF;
    }
    return 0;
}

void
ofmReadBlockHeader(FILE* file)
{
    int val[10], i; /* TODO: determine what these represent */
    unsigned char len;
    char* s = 0;
    unsigned short short1;
    short unknown1;
    /* TODO: determine what the unknown variables represent */
    int unknown3, unknown2;
    /* TODO: determine what this represents */

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadBlockHeader(), file argument is null\n");
        return;
    }

    embInt_read(file, "unknown1", &unknown1, EMB_INT16_LITTLE);
    embInt_read(file, "unknown2", &unknown2, EMB_INT32_LITTLE);
    embInt_read(file, "unknown3", &unknown3, EMB_INT32_LITTLE);

    /* int v = fread(&v, 1, 3, file)?; TODO: review */
    fread_int16(file);
    fseek(file, 1, SEEK_CUR);
    len = (char)fgetc(file);
    s = (char*)malloc(2 * len);
    if (!s) {
        printf("ERROR: format-ofm.c ofmReadBlockHeader(), unable to allocate memory for s\n");
        return;
    }
    fread((unsigned char *)s, 1, 2 * len, file);
    /* TODO: check return value */
    /* 0, 0, 0, 0, 1, 1, 1, 0, 64, 64 */
    for (i=0; i<10; i++) {
        embInt_read(file, "val[i]", val+i, EMB_INT32_LITTLE);
    }
    embInt_read(file, "short1", &short1, EMB_INT16_LITTLE); /*  0 */
}

void
ofmReadColorChange(FILE* file, EmbPattern* pattern)
{
    if (!file) {
        printf("ERROR: format-ofm.c ofmReadColorChange(), file argument is null\n");
        return;
    }
    if (!pattern) {
        printf("ERROR: format-ofm.c ofmReadColorChange(), pattern argument is null\n");
        return;
    }

    ofmReadBlockHeader(file);
    embPattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
}

void
ofmReadThreads(FILE* file, EmbPattern* p)
{
    int i, numberOfColors, stringLen, numberOfLibraries;
    char* primaryLibraryName = 0;
    char* expandedString = 0;

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadThreads(), file argument is null\n");
        return;
    }
    if (!p) {
        printf("ERROR: format-ofm.c ofmReadThreads(), p argument is null\n");
        return;
    }

    /* FF FE FF 00 */
    fseek(file, 4, SEEK_CUR);

    numberOfColors = fread_int16(file);

    fseek(file, 4, SEEK_CUR);
    stringLen = fread_int16(file);
    expandedString = (char*)malloc(stringLen);
    if (!expandedString) {
        printf("ERROR: format-ofm.c ofmReadThreads(), unable to allocate memory for expandedString\n");
        return;
    }
    fread((unsigned char*)expandedString, 1, stringLen, file);
    /* TODO: check return value */
    for (i = 0; i < numberOfColors; i++) {
        EmbThread thread;
        char colorNumberText[11], colorName[512];
        int threadLibrary, colorNameLength, colorNumber;
        embColor_read(file, &(thread.color), 4);
        embInt_read(file, "threadLibrary", &threadLibrary, EMB_INT16_LITTLE);
        fseek(file, 2, SEEK_CUR);
        embInt_read(file, "colorNumber", &colorNumber, EMB_INT32_LITTLE);
        fseek(file, 3, SEEK_CUR);
        colorNameLength = (char)fgetc(file);
        fread(colorName, 1, colorNameLength*2, file);
        /* TODO: check return value */
        fseek(file, 2, SEEK_CUR);
        sprintf(colorNumberText, "%10d", colorNumber);
        strcpy(thread.catalogNumber, colorNumberText);
        strcpy(thread.description, colorName);
        embPattern_addThread(p, thread);
    }
    fseek(file, 2, SEEK_CUR);
    primaryLibraryName = ofmReadLibrary(file);
    numberOfLibraries = fread_int16(file);

    if (emb_verbose>1) {
        printf("primary library name: %s\n", primaryLibraryName);
    }

    for (i = 0; i < numberOfLibraries; i++) {
        /*libraries.Add( TODO: review */
        char* libName = ofmReadLibrary(file);
        safe_free(libName);
    }
}

EmbReal ofmDecode(unsigned char b1, unsigned char b2)
{
    EmbReal val = (EmbReal)(short)(b1 << 8 | b2);
    return val;
}

void
ofmReadExpanded(FILE* file, EmbPattern* p)
{
    int i, numberOfStitches = 0;

    if (!file) { printf("ERROR: format-ofm.c ofmReadExpanded(), file argument is null\n"); return; }
    if (!p) { printf("ERROR: format-ofm.c ofmReadExpanded(), p argument is null\n"); return; }

    ofmReadBlockHeader(file);
    embInt_read(file, "numberOfStitchs", &numberOfStitches, EMB_INT32_LITTLE);

    for (i = 0; i < numberOfStitches; i++) {
        unsigned char stitch[5];
        fread(stitch, 1, 5, file); /* TODO: check return value */
        if (stitch[0] == 0) {
            embPattern_addStitchAbs(p, ofmDecode(stitch[1], stitch[2]) / 10.0, ofmDecode(stitch[3], stitch[4]) / 10.0, i == 0 ? JUMP : NORMAL, 1);
        }
        else if (stitch[0] == 32) {
            embPattern_addStitchAbs(p, ofmDecode(stitch[1], stitch[2]) / 10.0, ofmDecode(stitch[3], stitch[4]) / 10.0, i == 0 ? TRIM : NORMAL, 1);
        }
    }
}

char
readOfm(EmbPattern* pattern, FILE* fileCompound)
{
    int unknownCount, key = 0, classNameLength;
    char* s = 0;
    FILE *file;
    bcf_file* bcfFile = 0;

    if (emb_verbose>1) {
        puts("Overridden during development.");
        return 0;
    }

    bcfFile = (bcf_file*)malloc(sizeof(bcf_file));
    if (!bcfFile) {
        printf("ERROR: format-ofm.c readOfm(), unable to allocate memory for bcfFile\n");
        return 0;
    }
    bcfFile_read(fileCompound, bcfFile);
    file = GetFile(bcfFile, fileCompound, "EdsIV Object");
    bcf_file_free(bcfFile);
    bcfFile = 0;
    fseek(file, 0x1C6, SEEK_SET);
    ofmReadThreads(file, pattern);
    fseek(file, 0x110, SEEK_CUR);
    fseek(file, 0x4, SEEK_CUR); /* EMB_INT32_LITTLE */
    classNameLength = fread_int16(file);
    s = (char*)malloc(sizeof(char) * classNameLength);
    if (!s) {
        printf("ERROR: format-ofm.c readOfm(), unable to allocate memory for s\n");
        return 0;
    }
    fread((unsigned char*)s, 1, classNameLength, file); /* TODO: check return value */
    unknownCount = fread_int16(file);
    /* TODO: determine what unknown count represents */
    if (emb_verbose>1) {
        printf("unknownCount = %d\n", unknownCount);
    }

    fread_int16(file);
    key = ofmReadClass(file);
    while (1) {
        if (key == 0xFEFF) {
            break;
        }
        if (key == 0x809C) {
            ofmReadExpanded(file, pattern);
        }
        else {
            ofmReadColorChange(file, pattern);
        }
        key = fread_uint16(file);
        if (key == 0xFFFF) {
            ofmReadClass(file);
        }
    }

    embPattern_flip(pattern, 1, 1);

    return 1;
}

char
writeOfm(EmbPattern* pattern, FILE* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeOfm */
}
