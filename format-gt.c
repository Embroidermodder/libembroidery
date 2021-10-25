#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readGt(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file;

    if (!validateReadPattern(pattern, fileName, "readGt")) return 0;

    file = embFile_open(fileName, "rb", 0);
    if (!file) return 0;

    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_seek(file, 0x200, SEEK_SET); /* TODO: review for combining code. This line appears to be the only difference from the FXY format. */

    while(1)
    {
        int stitchType = NORMAL;
        int b1 = (int)binaryReadByte(file);
        int b2 = (int)binaryReadByte(file);
        unsigned char commandByte = binaryReadByte(file);

        if(commandByte == 0x91)
        {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        if((commandByte & 0x01) == 0x01)
            stitchType = TRIM;
        if((commandByte & 0x02) == 0x02)
            stitchType = STOP;
        if((commandByte & 0x20) == 0x20)
            b1 = -b1;
        if((commandByte & 0x40) == 0x40)
            b2 = -b2;
        embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    embFile_close(file);

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeGt(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeGt")) return 0;

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writeGt */
}

