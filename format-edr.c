#include "embroidery.h"
#include <stdlib.h>

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readEdr(EmbPattern* pattern, const char* fileName)
{
    int numberOfColors, i;
    EmbFile* file;
    EmbThread t;

    if (!validateReadPattern(pattern, fileName, "readEdr")) return 0;

    file = embFile_open(fileName, "rb", 1);

    embFile_seek(file, 0x00, SEEK_END);
    numberOfColors = embFile_tell(file) / 4;
    embFile_seek(file, 0x00, SEEK_SET);

    embArray_free(pattern->threads);

    for(i = 0; i < numberOfColors; i++)
    {
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
int writeEdr(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file;
    EmbColor c;
    int i;

    if (!validateWritePattern(pattern, fileName, "writeEdr")) return 0;

    file = embFile_open(fileName, "wb", 0);
    if (!file) return 0;

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

