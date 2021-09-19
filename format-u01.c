/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readU01(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return readU00(pattern, file, fileName);
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeU01(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return writeU00(pattern, file, fileName);
}

