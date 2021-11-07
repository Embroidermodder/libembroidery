#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readCnd(EmbPattern* pattern, const char* fileName)
{
    if (!validateReadPattern(pattern, fileName, "readCnd")) return 0;

    puts("readCnd is not implimented");
    return 0; /*TODO: finish readCnd */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeCnd(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeCnd")) return 0;

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    puts("writeCnd is not implimented");
    return 0; /*TODO: finish writeCnd */
}

