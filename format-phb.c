#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readPhb(EmbPattern* pattern, const char* fileName)
{
    unsigned int fileOffset;
    short colorCount;
    EmbFile* file = 0;
    int i;

    if(!pattern) { printf("ERROR: format-phb.c readPhb(), pattern argument is null\n"); return 0; }
    if(!fileName) { printf("ERROR: format-phb.c readPhb(), fileName argument is null\n"); return 0; }

    file = embFile_open(fileName, "rb", 0);
    if(!file)
        return 0;

    embFile_seek(file, 0x71, SEEK_SET);
    colorCount = binaryReadInt16(file);

    for(i = 0; i < colorCount; i++)
    {
        EmbThread t = pecThreads[(int)binaryReadByte(file)];
        embPattern_addThread(pattern, t);
    }

    /* TODO: check that file begins with #PHB */
    embFile_seek(file, 0x54, SEEK_SET);
    fileOffset = 0x52;
    fileOffset += binaryReadUInt32(file);

    embFile_seek(file, fileOffset, SEEK_SET);
    fileOffset += binaryReadUInt32(file) + 2;

    embFile_seek(file, fileOffset, SEEK_SET);
    fileOffset += binaryReadUInt32(file);

    embFile_seek(file, fileOffset + 14, SEEK_SET); /* 28 */

    colorCount = (short)binaryReadByte(file);
    for(i = 0; i< colorCount; i++)
    {
        binaryReadByte(file);
    }
    binaryReadInt32(file); /* bytes to end of file */
    binaryReadInt32(file);
    binaryReadByte(file);

    binaryReadInt16(file);
    binaryReadInt16(file);
    binaryReadInt16(file);
    binaryReadInt16(file);
    binaryReadInt16(file);
    binaryReadInt16(file);
    readPecStitches(pattern, file);
    embFile_close(file);

    embPattern_end(pattern);
    embPattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhb */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writePhb(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writePhb")) {
        return 0;
    }

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writePhb */
}

