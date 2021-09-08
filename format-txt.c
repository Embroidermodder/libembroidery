#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readTxt(EmbPattern* pattern, const char* fileName)
{
    if(!pattern) { embLog_error("format-txt.c readTxt(), pattern argument is null\n"); return 0; }
    if(!fileName) { embLog_error("format-txt.c readTxt(), fileName argument is null\n"); return 0; }
    return 0; /*TODO: finish readTxt */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeTxt(EmbPattern* pattern, const char* fileName)
{
    EmbStitch st;
    EmbFile* file = 0;
    int i;

    if (!validateWritePattern(pattern, fileName, "writeTxt")) {
        return 0;
    }

    file = embFile_open(fileName, "w", 0);
    if (!file) return 0;

    embFile_printf(file, "%u\n", (unsigned int)pattern->stitchList->count);

    for (i=0; i<pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        embFile_printf(file, "%.1f,%.1f color:%i flags:%i\n", st.x, st.y, st.color, st.flags);
    }

    embFile_close(file);
    return 1;
}

