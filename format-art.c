#include "format-art.h"
#include "emb-file.h"
#include "emb-logging.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readArt(EmbPattern* pattern, const char* fileName)
{
    if (!validateReadPattern(pattern, fileName, "readArt")) return 0;
    return 0; /*TODO: finish readArt */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeArt(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeArt")) return 0;

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writeArt */
}

