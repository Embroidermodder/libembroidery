#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readArt(EmbPattern* pattern, const char* fileName)
{
    if (!validateReadPattern(pattern, fileName, "readArt")) return 0;

    embPattern_end(pattern);

    puts("readArt is not implimented");
    return 0; /*TODO: finish readArt */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeArt(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeArt")) return 0;

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    puts("writeArt is not implimented");
    return 0; /*TODO: finish writeArt */
}

