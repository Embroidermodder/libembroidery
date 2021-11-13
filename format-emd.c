#include "embroidery.h"

static char emdDecode(unsigned char inputByte)
{
    return (inputByte >= 0x80) ? ((-~inputByte) - 1) : inputByte; /* TODO: eliminate ternary return statement */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readEmd(EmbPattern* pattern, const char* fileName)
{
    unsigned char b0 = 0, b1 = 0;
    char dx = 0, dy = 0;
    int flags = NORMAL;
    char endOfStream = 0;
    unsigned char jemd0[6]; /* TODO: more descriptive name */
    int width, height, colors;
    int i;
    EmbFile* file;

    if (!validateReadPattern(pattern, fileName, "readEmd")) return 0;

    file = embFile_open(fileName, "rb", 0);
    if (!file) return 0;

    embPattern_loadExternalColorFile(pattern, fileName);

    binaryReadBytes(file, jemd0, 6); /* TODO: check return value */
    width = binaryReadInt16(file);
    height = binaryReadInt16(file);
    colors = binaryReadInt16(file);

    printf("width: %d\nheight: %d\ncolors: %d\n", width, height, colors);

    embFile_seek(file, 0x30, SEEK_SET);

    for (i = 0; !endOfStream; i++) {
            flags = NORMAL;
            b0 = binaryReadUInt8(file);
            b1 = binaryReadUInt8(file);

            if(b0 == 0x80) {
                if(b1 == 0x2A) {
                    embPattern_addStitchRel(pattern, 0, 0, STOP, 1);
                    continue;
                }
                else if(b1 == 0x80) {
                    b0 = binaryReadUInt8(file);
                    b1 = binaryReadUInt8(file);
                    flags = TRIM;
                }
                else if(b1 == 0xFD) {
                    embPattern_addStitchRel(pattern, 0, 0, END, 1);
                    break;
                }
                else {
                    continue;
                }
            }
            dx = emdDecode(b0);
            dy = emdDecode(b1);
            embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    embFile_close(file);

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeEmd(EmbPattern* pattern, const char* fileName)
{
    FILE *file;

    if (!validateWritePattern(pattern, fileName, "writeEmd")) return 0;

    file = fopen(fileName, "wb");
    if (!file) {
        puts("ERROR: Failed to open file.");
        return 0;
    }

    fclose(file);

    puts("writeEmd not implimented.");
    return 0; /*TODO: finish writeEmd */
}

