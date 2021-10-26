#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readTxt(EmbPattern* pattern, const char* fileName)
{
    if(!pattern) { printf("ERROR: format-txt.c readTxt(), pattern argument is null\n"); return 0; }
    if(!fileName) { printf("ERROR: format-txt.c readTxt(), fileName argument is null\n"); return 0; }
    return 0; /*TODO: finish readTxt */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeTxt(EmbPattern* pattern, const char* fileName)
{
    EmbStitchList* pointer = 0;
    EmbFile* file = 0;

    if (!validateWritePattern(pattern, fileName, "writeTxt")) {
        return 0;
    }

    file = embFile_open(fileName, "w", 0);
    if(!file)
        return 0;

    pointer = pattern->stitchList;
    embFile_printf(file, "%u\n", (unsigned int) embStitchList_count(pointer));

    while(pointer)
    {
        EmbStitch s = pointer->stitch;
        embFile_printf(file, "%.1f,%.1f color:%i flags:%i\n", s.x, s.y, s.color, s.flags);
        pointer = pointer->next;
    }

    embFile_close(file);
    return 1;
}

