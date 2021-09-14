#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readInb(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file;
    unsigned char fileDescription[8];
    unsigned char nullVal;
    int stitchCount;
    short width, height;
    short colorCount;
    short unknown3, unknown2;
    short imageWidth, imageHeight;
    unsigned char bytesUnknown[300]; /* TODO: determine what this represents */
    short nullbyte;
    short left, right, top, bottom;
    int x, y, i, fileLength;

    if (!validateReadPattern(pattern, fileName, "readInb"))
        return 0;

    file = embFile_open(fileName, "rb", 0);
    if (!file)
        return 0;

    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_seek(file, 0, SEEK_END);
    fileLength = embFile_tell(file);
    binaryReadBytes(file, fileDescription, 8); /* TODO: check return value */
    nullVal = binaryReadByte(file);
    binaryReadInt16(file);
    stitchCount = binaryReadInt32(file);
    width = binaryReadInt16(file);
    height = binaryReadInt16(file);
    colorCount = binaryReadInt16(file);
    unknown3 = binaryReadInt16(file);
    unknown2 = binaryReadInt16(file);
    imageWidth = binaryReadInt16(file);
    imageHeight = binaryReadInt16(file);
    binaryReadBytes(file, bytesUnknown, 300); /* TODO: check return value */
    nullbyte = binaryReadInt16(file);
    left = binaryReadInt16(file);
    right = binaryReadInt16(file);
    top = binaryReadInt16(file);
    bottom = binaryReadInt16(file);
    embFile_seek(file, 0x2000, SEEK_SET);
    /* Calculate stitch count since header has been seen to be blank */
    stitchCount = (int)((fileLength - 0x2000) / 3);
    for (i = 0; i < stitchCount; i++) {
        unsigned char type;
        int stitch = NORMAL;
        x = binaryReadByte(file);
        y = binaryReadByte(file);
        type = binaryReadByte(file);
        if ((type & 0x40) > 0)
            x = -x;
        if ((type & 0x10) > 0)
            y = -y;
        if ((type & 1) > 0)
            stitch = STOP;
        if ((type & 2) > 0)
            stitch = TRIM;
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitch, 1);
    }
    embFile_close(file);

    embPattern_end(pattern);
    embPattern_flipVertical(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeInb(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeInb"))
        return 0;

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writeInb */
}

