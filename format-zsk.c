#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readZsk(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char b[3];
    int stitchType;
    unsigned char colorNumber;
    EmbThread t;

    embFile_seek(file, 0x230, SEEK_SET);
    colorNumber = binaryReadUInt8(file);
    while (colorNumber != 0) {
        t.color.r = binaryReadUInt8(file);
        t.color.g = binaryReadUInt8(file);
        t.color.b = binaryReadUInt8(file);
        t.catalogNumber = "";
        t.description = "";
        embPattern_addThread(pattern, t);
        embFile_seek(file, 0x48, SEEK_CUR);
        colorNumber = binaryReadUInt8(file);
    }
    embFile_seek(file, 0x2E, SEEK_CUR);

    while (embFile_read(b, 1, 3, file) == 3) {
        stitchType = NORMAL;
        if (b[0] & 0x4) {
            b[2] = -b[2];
        }
        if (b[0] & 0x8) {
            b[1] = -b[1];
        }
        if (b[0] & 0x02) {
            stitchType = JUMP;
        }
        if (b[0] & 0x20) {
            if (b[1] == 2) {
                stitchType = TRIM;
            } else if (b[1] == -1) {
                break;
            } else {
                if (b[2] != 0) {
                    colorNumber = b[2];
                }
                stitchType = STOP; /* TODO: need to determine what b[1] is used for.*/
                embPattern_changeColor(pattern, colorNumber - 1);
            }
            b[1] = 0;
            b[2] = 0;
        }
        embPattern_addStitchRel(pattern, b[1] / 10.0, b[2] / 10.0, stitchType, 0);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeZsk(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeZsk */
}

