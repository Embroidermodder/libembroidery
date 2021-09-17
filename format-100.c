#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int read100(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int x, y;
    int stitchType;
    unsigned char b[4];

    embPattern_loadExternalColorFile(pattern, fileName);
    while (embFile_read(b, 1, 4, file) == 4) {
        stitchType = NORMAL;
        x = (b[2] > 0x80) ? -(b[2] - 0x80) : b[2];
        y = (b[3] > 0x80) ? -(b[3] - 0x80) : b[3];
        /*if(!(b[0] & 0xFC)) stitchType = JUMP; TODO: review & fix */
        if (!(b[0] & 0x01))
            stitchType = STOP;
        if (b[0] == 0x1F)
            stitchType = END;
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int write100(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish write100 */
}

