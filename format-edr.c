#include "embroidery.h"

#include <stdio.h>
#include <stdlib.h>

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readEdr(EmbPattern* pattern, const char* fileName)
{
    int numberOfColors, i;
    FILE* file;
    EmbThread t;

    if (!validateReadPattern(pattern, fileName, "readEdr")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }

    fseek(file, 0x00, SEEK_END);
    numberOfColors = ftell(file) / 4;
    fseek(file, 0x00, SEEK_SET);

    embArray_free(pattern->threads);

    for (i = 0; i < numberOfColors; i++) {
        unsigned char color[4];
        fread(color, 1, 4, file);
        t.color.r = color[0];
        t.color.g = color[1];
        t.color.b = color[2];
        t.catalogNumber = "";
        t.description = "";
        embPattern_addThread(pattern, t);
    }
    fclose(file);
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeEdr(EmbPattern* pattern, const char* fileName)
{
    FILE* file;
    EmbColor c;
    int i;

    if (!validateWritePattern(pattern, fileName, "writeEdr")) {
        return 0;
    }

    file = fopen(fileName, "wb");
    if (!file) {
        return 0;
    }

    for (i=0; i<pattern->threads->count; i++) {
        unsigned char output[4];
        c = pattern->threads->thread[i].color;
        output[0] = c.r;
        output[1] = c.g;
        output[2] = c.b;
        output[3] = 0;
        fwrite(output, 1, 4, file);
    }
    fclose(file);
    return 1;
}

