#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readT09(EmbPattern* pattern, const char* fileName)
{
    unsigned char b[3];
    EmbFile* file;

    if (!validateReadPattern(pattern, fileName, "readT09"))
        return 0;

    file = embFile_open(fileName, "rb", 0);
    if (!file)
        return 0;

    embFile_seek(file, 0x0C, SEEK_SET);

    while (embFile_read(b, 1, 3, file) == 3) {
        int stitchType = NORMAL;
        int b1 = b[0];
        int b2 = b[1];
        unsigned char commandByte = b[2];
        if (commandByte == 0x00) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        if (commandByte & 0x10)
            stitchType = STOP;
        if (commandByte & 0x20)
            b1 = -b1;
        if (commandByte & 0x40)
            b2 = -b2;

        embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    embFile_close(file);
    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeT09(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file;
    if (!validateWritePattern(pattern, fileName, "writeT09")) {
        return 0;
    }

    file = embFile_open(fileName, "wb", 0);
    if (!file)
        return 0;

    embFile_close(file);
    return 0; /*TODO: finish writeT09 */
}

