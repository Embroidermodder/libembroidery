#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readDat(EmbPattern* pattern, const char* fileName)
{
    unsigned char b0;
    int fileLength, stitchesRemaining, b1, b2, stitchType;
    EmbFile* file;

    if (!validateReadPattern(pattern, fileName, "readDat")) return 0;

    file = embFile_open(fileName, "rb", 0);
    if (!file) return 0;

    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_seek(file, 0x00, SEEK_END);
    fileLength = embFile_tell(file);
    embFile_seek(file, 0x02, SEEK_SET);
    stitchesRemaining = binaryReadUInt16(file);
    embFile_seek(file, 0x100, SEEK_SET);

    while(embFile_tell(file) < fileLength)
    {
        b1 = (int)binaryReadUInt8(file);
        b2 = (int)binaryReadUInt8(file);
        b0 = binaryReadByte(file);

        stitchType = NORMAL;
        stitchesRemaining--;

        if((b0 & 0x02) == 0) stitchType = TRIM;

        if(b0 == 0x87)
        {
            stitchType = STOP;
        }
        if(b0 == 0xF8)
        {
            break;
        }
        if(b1 >= 0x80)
        {
            b1 = -(b1 & 0x7F);
        }
        if(b2 >= 0x80)
        {
            b2 = -(b2 & 0x7F);
        }
        embPattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }
    embFile_close(file);

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeDat(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeDat")) return 0;

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    puts("writeDat is not implimented.");
    return 0; /*TODO: finish writeDat */
}

