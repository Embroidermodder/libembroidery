#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readPel(EmbPattern* pattern, const char* fileName)
{
    if(!pattern) { printf("ERROR: format-pel.c readPel(), pattern argument is null\n"); return 0; }
    if(!fileName) { printf("ERROR: format-pel.c readPel(), fileName argument is null\n"); return 0; }
    return 0; /*TODO: finish readPel */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writePel(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writePel")) {
        return 0;
    }

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writePel */
}

