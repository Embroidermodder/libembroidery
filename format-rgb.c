#include "embroidery.h"
#include <stdlib.h>

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readRgb(EmbPattern* pattern, const char* fileName)
{
    int i, numberOfColors;
    EmbFile* file;
    EmbThread t;

    if (!validateReadPattern(pattern, fileName, "readRgb")) return 0;

    file = embFile_open(fileName, "rb", 1);
    if(!file)
        return 0;

    embFile_seek(file, 0x00, SEEK_END);
    numberOfColors = embFile_tell(file) / 4;

    embArray_free(pattern->threads);
    pattern->threads = embArray_create(EMB_THREAD);

    embFile_seek(file, 0x00, SEEK_SET);
    for (i = 0; i < numberOfColors; i++) {
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        t.catalogNumber = "";
        t.description = "";
        binaryReadByte(file);
        embPattern_addThread(pattern, t);
    }
    embFile_close(file);
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeRgb(EmbPattern* pattern, const char* fileName)
{
    int i;
    EmbFile* file = 0;
    EmbColor c;

    if (!validateWritePattern(pattern, fileName, "writeRgb")) return 0;

    file = embFile_open(fileName, "wb", 0);
    if(!file)
        return 0;

    for (i=0; i<pattern->threads->count; i++) {
        c = pattern->threads->thread[i].color;
        binaryWriteByte(file, c.r);
        binaryWriteByte(file, c.g);
        binaryWriteByte(file, c.b);
        binaryWriteByte(file, 0);
    }
    embFile_close(file);
    return 1;
}

