/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readEdr(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int numberOfColors, i;
    EmbThread t;

    embFile_seek(file, 0x00, SEEK_END);
    numberOfColors = embFile_tell(file) / 4;
    embFile_seek(file, 0x00, SEEK_SET);

    embArray_free(pattern->threads);

    for (i = 0; i < numberOfColors; i++) {
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        t.catalogNumber = "";
        t.description = "";
        binaryReadByte(file);
        embPattern_addThread(pattern, t);
    }
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeEdr(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbColor c;
    int i;

    for (i = 0; i < pattern->threads->count; i++) {
        c = pattern->threads->thread[i].color;
        binaryWriteByte(file, c.r);
        binaryWriteByte(file, c.g);
        binaryWriteByte(file, c.b);
        binaryWriteByte(file, 0);
    }
    return 1;
}

