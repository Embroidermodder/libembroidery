#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readGnc(EmbPattern* pattern, const char* fileName)
{
    if (!validateReadPattern(pattern, fileName, "readGnc")) {
        return 0;
    }

    embPattern_end(pattern);

    return 0; /*TODO: finish readGnc */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeGnc(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeGnc")) {
        return 0;
    }

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writeGnc */
}

