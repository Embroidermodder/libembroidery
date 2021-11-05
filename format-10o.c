#include "embroidery.h"

#include <stdio.h>

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char read10o(EmbPattern* pattern, const char* fileName)
{
    FILE* file;

    if (!validateReadPattern(pattern, fileName, "read10o")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 0;
    }

    embPattern_loadExternalColorFile(pattern, fileName);

    while (1) {
        int x, y;
        int stitchType = NORMAL;
        unsigned char ctrl = (unsigned char)fgetc(file);
        if (feof(file))
            break;
        y = fgetc(file);
        if (feof(file))
            break;
        x = fgetc(file);
        if (feof(file))
            break;
        if(ctrl & 0x20)
            x = -x;
        if(ctrl & 0x40)
            y = -y;
        if(ctrl & 0x01)
            stitchType = TRIM;
        if((ctrl & 0x5) == 5)
        {
            stitchType = STOP;
        }
        if(ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87)
        {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }
    fclose(file);

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char write10o(EmbPattern* pattern, const char* fileName)
{
    FILE *file;
    if (!validateWritePattern(pattern, fileName, "write10o")) {
        printf("Failed to validate file with name: %s.", fileName);
        return 1;
    }

    file = fopen(fileName, "wb");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 1;
    }

    /*
    TODO:
    while (1) {
        int x, y;
        int stitchType = NORMAL;
        unsigned char ctrl = (unsigned char)fgetc(file);
        if (feof(file))
            break;
        y = fgetc(file);
        if (feof(file))
            break;
        x = fgetc(file);
        if (feof(file))
            break;
        if(ctrl & 0x20)
            x = -x;
        if(ctrl & 0x40)
            y = -y;
        if(ctrl & 0x01)
            stitchType = TRIM;
        if((ctrl & 0x5) == 5)
        {
            stitchType = STOP;
        }
        if(ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87)
        {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
        fwrite(b, 1, 4, file);
    }
    */
    fclose(file);
    return 0; /*TODO: finish write10o */
}

