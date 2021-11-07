#include "embroidery.h"

#include <stdio.h>

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char read100(EmbPattern* pattern, const char* fileName)
{
    FILE* file;
    int x, y;
    int stitchType;
    unsigned char b[4];

    if (!validateReadPattern(pattern, fileName, "read100")) return 0;

    file = fopen(fileName, "rb");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 0;
    }

    embPattern_loadExternalColorFile(pattern, fileName);
    while (fread(b, 1, 4, file) == 4) {
        stitchType = NORMAL;
        x = (b[2] > 0x80) ? -(b[2] - 0x80) : b[2];
        y = (b[3] > 0x80) ? -(b[3] - 0x80) : b[3];
        /*if(!(b[0] & 0xFC)) stitchType = JUMP; TODO: review & fix */
        if(!(b[0] & 0x01)) stitchType = STOP;
        if(b[0] == 0x1F) stitchType = END;
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }
    fclose(file);

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char write100(EmbPattern* pattern, const char* fileName)
{
    FILE *file;
    int x, y;
    int stitchType;
    unsigned char b[4];

    if (!validateWritePattern(pattern, fileName, "write100")) {
        printf("Failed to validate file with name: %s.", fileName);
        return 0;
    }

    file = fopen(fileName, "wb");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 0;
    }

    /*
    TODO:
    while (1) {
        stitchType = NORMAL;
        x = (b[2] > 0x80) ? -(b[2] - 0x80) : b[2];
        y = (b[3] > 0x80) ? -(b[3] - 0x80) : b[3];
        if (st.flags & JUMP) {
            ?
        }
        if (st.flags & STOP) {
            ?
        }
        if (st.flags & END) {
            ?
        }
        // if(!(b[0] & 0xFC)) stitchType = JUMP; TODO: review & fix
        if (!(b[0] & 0x01)) stitchType = STOP;
        if (b[0] == 0x1F) stitchType = END;
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
        fwrite(b, 1, 4, file);
    }
    */

    fclose(file);
    return 1;
}

