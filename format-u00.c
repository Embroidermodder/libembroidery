#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readU00(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;
    char dx = 0, dy = 0;
    int flags = NORMAL;
    char endOfStream = 0;
    EmbThread t;
    unsigned char b[4];

    /* 16 3byte RGB's start @ 0x08 followed by 14 bytes between 0 and 15 with index of color for each color change */
    embFile_seek(file, 0x08, SEEK_SET);

    for (i = 0; i < 16; i++) {
        t.color.r = binaryReadUInt8(file);
        t.color.g = binaryReadUInt8(file);
        t.color.b = binaryReadUInt8(file);
        embPattern_addThread(pattern, t);
    }

    embFile_seek(file, 0x100, SEEK_SET);
    for (i = 0; !endOfStream; i++) {
        char negativeX, negativeY;
        unsigned char b0 = binaryReadUInt8(file);
        unsigned char b1 = binaryReadUInt8(file);
        unsigned char b2 = binaryReadUInt8(file);

        if (b0 == 0xF8 || b0 == 0x87 || b0 == 0x91) {
            break;
        }
        if ((b0 & 0x0F) == 0) {
            flags = NORMAL;
        } else if ((b0 & 0x1f) == 1) {
            flags = JUMP;
        } else if ((b0 & 0x0F) > 0) {
            flags = STOP;
        }
        negativeX = ((b0 & 0x20) > 0);
        negativeY = ((b0 & 0x40) > 0);

        dx = (char)b2;
        dy = (char)b1;
        if (negativeX)
            dx = (char)-dx;
        if (negativeY)
            dy = (char)-dy;
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeU00(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish WriteU00 */
}

