#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readDem(EmbPattern* pattern, const char* fileName)
{
    if (!validateReadPattern(pattern, fileName, "readDem"))
        return 0;

    embPattern_end(pattern);

    return 0; /*TODO: finish readDem */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeDem(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeDem"))
        return 0;

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writeDem */
}
