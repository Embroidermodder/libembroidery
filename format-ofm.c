#include "embroidery.h"
#include <stdlib.h>
#include <string.h>
#include "emb-macro.h"

static char* ofmReadLibrary(EmbFile* file)
{
    int stringLength = 0;
    char* libraryName = 0;
    /* FF FE FF */
    unsigned char leadIn[3];

    if (!file) {
        embLog("ERROR: format-ofm.c ofmReadLibrary(), file argument is null\n");
        return 0;
    }

    binaryReadBytes(file, leadIn, 3); /* TODO: check return value */
    stringLength = binaryReadByte(file);
    libraryName = (char*)malloc(sizeof(char) * stringLength * 2);
    if (!libraryName) {
        embLog("ERROR: format-ofm.c ofmReadLibrary(), unable to allocate memory for libraryName\n");
        return 0;
    }
    binaryReadBytes(file, (unsigned char*)libraryName, stringLength * 2); /* TODO: check return value */
    return libraryName;
}

static int ofmReadClass(EmbFile* file)
{
    int len;
    char* s = 0;

    if (!file) {
        embLog("ERROR: format-ofm.c ofmReadClass(), file argument is null\n");
        return 0;
    }

    binaryReadInt16(file);
    len = binaryReadInt16(file);

    s = (char*)malloc(sizeof(char) * len + 1);
    if (!s) {
        embLog("ERROR: format-ofm.c ofmReadClass(), unable to allocate memory for s\n");
        return 0;
    }
    binaryReadBytes(file, (unsigned char*)s, len); /* TODO: check return value */
    s[len] = '\0';
    if (strcmp(s, "CExpStitch") == 0)
        return 0x809C;
    if (strcmp(s, "CColorChange") == 0)
        return 0xFFFF;
    return 0;
}

static void ofmReadBlockHeader(EmbFile* file)
{
    int val1, val2, val3, val4, val5, val6, val7, val8, val9, val10; /* TODO: determine what these represent */
    unsigned char len;
    unsigned short short1;
    char header[512];
    /* TODO: determine what these 3 variables represent */
    short unknown1 = 0;
    short unknown2 = 0;
    int unknown3 = 0;

    if (!file) {
        embLog("ERROR: format-ofm.c ofmReadBlockHeader(), file argument is null\n");
        return;
    }

    embFile_read(header, 1, 14, file);
    unknown1 = EMB_GET_SHORT(header);
    unknown2 = (short)EMB_GET_INT(header+2);
    unknown3 = EMB_GET_INT(header+6);

    /* int v = binaryReadBytes(3); TODO: review */
    len = (unsigned char)(header+13);
    embFile_read(header, 1, 2*len, file);
    /* TODO: check return value here */
    embFile_read(header, 1, 42, file);
    val1 = EMB_GET_INT(header+0); /*  0 */
    val2 = EMB_GET_INT(header+4); /*  0 */
    val3 = EMB_GET_INT(header+8); /*  0 */
    val4 = EMB_GET_INT(header+12); /*  0 */
    val5 = EMB_GET_INT(header+16); /*  1 */
    val6 = EMB_GET_INT(header+20); /*  1 */
    val7 = EMB_GET_INT(header+24); /*  1 */
    val8 = EMB_GET_INT(header+28); /*  0 */
    val9 = EMB_GET_INT(header+32); /* 64 */
    val10 = EMB_GET_INT(header+36); /* 64 */
    short1 = EMB_GET_SHORT(header+40); /*  0 */
}

static void ofmReadColorChange(EmbFile* file, EmbPattern* pattern)
{
    if (!file) {
        embLog("ERROR: format-ofm.c ofmReadColorChange(), file argument is null\n");
        return;
    }
    if (!pattern) {
        embLog("ERROR: format-ofm.c ofmReadColorChange(), pattern argument is null\n");
        return;
    }

    ofmReadBlockHeader(file);
    embPattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
}

static void ofmReadThreads(EmbFile* file, EmbPattern* p)
{
    int i, numberOfColors, stringLen, numberOfLibraries;
    char* primaryLibraryName = 0;
    char* expandedString = 0;

    if (!file) {
        embLog("ERROR: format-ofm.c ofmReadThreads(), file argument is null\n");
        return;
    }
    if (!p) {
        embLog("ERROR: format-ofm.c ofmReadThreads(), p argument is null\n");
        return;
    }

    /* FF FE FF 00 */
    binaryReadInt32(file);

    numberOfColors = binaryReadInt16(file);

    binaryReadInt16(file);
    binaryReadInt16(file);
    stringLen = binaryReadInt16(file);
    expandedString = (char*)malloc(stringLen);
    if (!expandedString) {
        embLog("ERROR: format-ofm.c ofmReadThreads(), unable to allocate memory for expandedString\n");
        return;
    }
    binaryReadBytes(file, (unsigned char*)expandedString, stringLen); /* TODO: check return value */
    for (i = 0; i < numberOfColors; i++) {
        EmbThread thread;
        char colorNumberText[10];
        int threadLibrary = 0, colorNameLength, colorNumber;
        char* colorName = 0;
        int r = binaryReadByte(file);
        int g = binaryReadByte(file);
        int b = binaryReadByte(file);
        binaryReadByte(file);
        threadLibrary = binaryReadInt16(file);
        binaryReadInt16(file);
        colorNumber = binaryReadInt32(file);
        binaryReadByte(file);
        binaryReadInt16(file);
        colorNameLength = binaryReadByte(file);
        colorName = (char*)malloc(colorNameLength * 2);
        if (!colorName) {
            embLog("ERROR: format-ofm.c ofmReadThreads(), unable to allocate memory for colorName\n");
            return;
        }
        binaryReadBytes(file, (unsigned char*)colorName, colorNameLength * 2); /* TODO: check return value */
        binaryReadInt16(file);
        /* itoa(colorNumber, colorNumberText, 10); TODO: never use itoa, it's non-standard, use sprintf: http://stackoverflow.com/questions/5242524/converting-int-to-string-in-c */
        thread.color.r = (unsigned char)r;
        thread.color.g = (unsigned char)g;
        thread.color.b = (unsigned char)b;
        thread.catalogNumber = colorNumberText;
        thread.description = colorName;
        embPattern_addThread(p, thread);
    }
    binaryReadInt16(file);
    primaryLibraryName = ofmReadLibrary(file);
    numberOfLibraries = binaryReadInt16(file);
    for (i = 0; i < numberOfLibraries; i++) {
        /*libraries.Add( TODO: review */
        char* libName = ofmReadLibrary(file);
        free(libName);
        libName = 0;
    }
}

static double ofmDecode(unsigned char b1, unsigned char b2)
{
    double val = (double)(short)(b1 << 8 | b2);
    return val;
}

static void ofmReadExpanded(EmbFile* file, EmbPattern* p)
{
    int i, numberOfStitches = 0;

    if (!file) {
        embLog("ERROR: format-ofm.c ofmReadExpanded(), file argument is null\n");
        return;
    }
    if (!p) {
        embLog("ERROR: format-ofm.c ofmReadExpanded(), p argument is null\n");
        return;
    }

    ofmReadBlockHeader(file);
    numberOfStitches = binaryReadInt32(file);

    for (i = 0; i < numberOfStitches; i++) {
        unsigned char stitch[5];
        binaryReadBytes(file, stitch, 5); /* TODO: check return value */
        if (stitch[0] == 0) {
            embPattern_addStitchAbs(p, ofmDecode(stitch[1], stitch[2]) / 10.0, ofmDecode(stitch[3], stitch[4]) / 10.0, i == 0 ? JUMP : NORMAL, 1);
        } else if (stitch[0] == 32) {
            embPattern_addStitchAbs(p, ofmDecode(stitch[1], stitch[2]) / 10.0, ofmDecode(stitch[3], stitch[4]) / 10.0, i == 0 ? TRIM : NORMAL, 1);
        }
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readOfm(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int unknownCount = 0;
    int key = 0, classNameLength;
    char* s = 0;
    EmbFile* fileCompound = 0;
    bcf_file* bcfFile = 0;

    fileCompound = embFile_open(fileName, "rb", 0);
    if (!fileCompound)
        return 0;

    bcfFile = (bcf_file*)malloc(sizeof(bcf_file));
    if (!bcfFile) {
        embLog("ERROR: format-ofm.c readOfm(), unable to allocate memory for bcfFile\n");
        return 0;
    }
    bcfFile_read(fileCompound, bcfFile);
    file = GetFile(bcfFile, fileCompound, "EdsIV Object");
    bcf_file_free(bcfFile);
    bcfFile = 0;
    embFile_seek(file, 0x1C6, SEEK_SET);
    ofmReadThreads(file, pattern);
    embFile_seek(file, 0x110, SEEK_CUR);
    binaryReadInt32(file);
    classNameLength = binaryReadInt16(file);
    s = (char*)malloc(sizeof(char) * classNameLength);
    if (!s) {
        embLog("ERROR: format-ofm.c readOfm(), unable to allocate memory for s\n");
        return 0;
    }
    binaryReadBytes(file, (unsigned char*)s, classNameLength); /* TODO: check return value */
    unknownCount = binaryReadInt16(file); /* TODO: determine what unknown count represents */

    binaryReadInt16(file);
    key = ofmReadClass(file);
    while (1) {
        if (key == 0xFEFF) {
            break;
        }
        if (key == 0x809C) {
            ofmReadExpanded(file, pattern);
        } else {
            ofmReadColorChange(file, pattern);
        }
        key = binaryReadUInt16(file);
        if (key == 0xFFFF) {
            ofmReadClass(file);
        }
    }

    embFile_close(fileCompound);

    embPattern_flip(pattern, 1, 1);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeOfm(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeOfm */
}

