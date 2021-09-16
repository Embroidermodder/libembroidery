#include "embroidery.h"
#include <stdlib.h>
#include <string.h>

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readInf(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int numberOfColors, i;
    char colorType[50];
    char colorDescription[50];
    EmbThread t;

    embFile_seek(file, 12L, SEEK_SET);
    numberOfColors = binaryReadUInt32BE(file);

    embArray_free(pattern->threads);
    pattern->threads = embArray_create(EMB_THREAD);

    for (i = 0; i < numberOfColors; i++) {
        binaryReadUInt16(file);
        binaryReadUInt16(file);
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        t.catalogNumber = "";
        t.description = "";
        embPattern_addThread(pattern, t);
        binaryReadUInt16(file);
        binaryReadString(file, colorType, 50);
        binaryReadString(file, colorDescription, 50);
    }
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeInf(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i, bytesRemaining;
    char buffer[50];
    EmbColor c;

    binaryWriteUIntBE(file, 0x01);
    binaryWriteUIntBE(file, 0x08);
    /* write place holder offset */
    binaryWriteUIntBE(file, 0x00);
    binaryWriteUIntBE(file, pattern->threads->count);

    for (i = 0; i < pattern->threads->count; i++) {
        c = pattern->threads->thread[i].color;
        sprintf(buffer, "RGB(%d,%d,%d)", (int)c.r, (int)c.g, (int)c.b);
        binaryWriteUShortBE(file, (unsigned short)(14 + strlen(buffer))); /* record length */
        binaryWriteUShortBE(file, (unsigned short)i); /* record number */
        binaryWriteByte(file, c.r);
        binaryWriteByte(file, c.g);
        binaryWriteByte(file, c.b);
        binaryWriteUShortBE(file, (unsigned short)i); /* needle number */
        binaryWriteBytes(file, "RGB\0", 4);
        embFile_print(file, buffer);
        binaryWriteByte(file, 0);
    }
    embFile_seek(file, -8, SEEK_END);
    bytesRemaining = embFile_tell(file);
    embFile_seek(file, 8, SEEK_SET);
    binaryWriteUIntBE(file, bytesRemaining);
    return 1;
}

