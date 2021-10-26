#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readCnd(EmbPattern* pattern, const char* fileName)
{
    if(!pattern) { printf("ERROR: format-cnd.c readCnd(), pattern argument is null\n"); return 0; }
    if(!fileName) { printf("ERROR: format-cnd.c readCnd(), fileName argument is null\n"); return 0; }
    return 0; /*TODO: finish readCnd */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeCnd(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeCnd")) return 0;

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writeCnd */
}

