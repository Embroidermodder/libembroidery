#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readTxt(EmbPattern* pattern, const char* fileName)
{
    if(!validateReadPattern(pattern, fileName, "readTxt")) { return 0; }

    return 0; /*TODO: finish readTxt */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeTxt(EmbPattern* pattern, const char* fileName)
{
    int i;
    EmbFile* file = 0;

    if (!validateWritePattern(pattern, fileName, "writeTxt")) {
        return 0;
    }

    file = embFile_open(fileName, "w", 0);
    if(!file)
        return 0;

    embFile_printf(file, "%u\n", (unsigned int) pattern->stitchList->count);

    for (i=0; i<pattern->stitchList->count; i++) {
        EmbStitch s = pattern->stitchList->stitch[i];
        embFile_printf(file, "%.1f,%.1f color:%i flags:%i\n", s.x, s.y, s.color, s.flags);
    }

    embFile_close(file);
    return 1;
}

