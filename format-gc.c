/* Smoothie G-Code */
#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readGc(EmbPattern* pattern, const char* fileName)
{
    if (!validateReadPattern(pattern, fileName, "readGc")) {
        return 0;
    }

    return 0; /*TODO: finish readGc */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeGc(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeGc")) {
        return 0;
    }

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writeGc */
}

