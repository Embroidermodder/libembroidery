#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readT09(EmbPattern* pattern, const char* fileName)
{
    unsigned char b[3];
    FILE* file;
    int i;

    if (!validateReadPattern(pattern, fileName, "readT09")) return 0;

    file = fopen(fileName, "rb");
    if (!file)
        return 0;

    for (i=0; i<0x0C; i++) {
        fwrite(" ", 1, 1, file);
    }

    while (fread(b, 1, 3, file) == 3) {
        int stitchType = NORMAL;
        int b1 = b[0];
        int b2 = b[1];
        unsigned char commandByte = b[2];
        if (commandByte == 0x00) break;
        if (commandByte & 0x10) stitchType = STOP;
        if (commandByte & 0x20) b1 = -b1;
        if (commandByte & 0x40) b2 = -b2;

        embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    fclose(file);
    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeT09(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeT09")) {
        return 0;
    }

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    puts("writeT09 is not implimented.");
    return 0; /*TODO: finish writeT09 */
}

