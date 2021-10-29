#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readSst(EmbPattern* pattern, const char* fileName)
{
    int fileLength;
    EmbFile* file = 0;

    if (!validateReadPattern(pattern, fileName, "readSst"))
        return 0;

    file = embFile_open(fileName, "rb", 0);
    if(!file)
        return 0;

    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_seek(file, 0, SEEK_END);
    fileLength = embFile_tell(file);
    embFile_seek(file, 0xA0, SEEK_SET); /* skip the all zero header */
    while(embFile_tell(file) < fileLength)
    {
        int stitchType = NORMAL;

        int b1 = (int) binaryReadByte(file);
        int b2 = (int) binaryReadByte(file);
        unsigned char commandByte = binaryReadByte(file);

        if(commandByte == 0x04)
        {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }

        if((commandByte & 0x01) == 0x01)
            stitchType = STOP;
        if((commandByte & 0x02) == 0x02)
            stitchType = JUMP;
        if((commandByte & 0x10) != 0x10)
            b2 = -b2;
        if((commandByte & 0x40) == 0x40)
            b1 = -b1;
        embPattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }

    embFile_close(file);
    embPattern_end(pattern);

    return 1; /*TODO: finish readSst */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeSst(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeSst"))
        return 0;

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writeSst */
}

