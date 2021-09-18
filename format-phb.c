/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readPhb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned int fileOffset;
    short colorCount;
    int i;

    embFile_seek(file, 0x71, SEEK_SET);
    colorCount = binaryReadInt16(file);

    for (i = 0; i < colorCount; i++) {
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
    for (i = 0; i < colorCount; i++) {
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
    readPecStitches(pattern, file, fileName);

    embPattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhb */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writePhb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writePhb */
}

