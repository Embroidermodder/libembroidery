/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readTxt(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    if (!pattern) {
        embLog("ERROR: format-txt.c readTxt(), pattern argument is null\n");
        return 0;
    }
    if (!fileName) {
        embLog("ERROR: format-txt.c readTxt(), fileName argument is null\n");
        return 0;
    }
    return 0; /*TODO: finish readTxt */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeTxt(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbStitch st;
    int i;

    writeInt(file, pattern->stitchList->count, 6);
    embFile_print(file, "\n");

    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        /* embFile_print(file, "%.1f,%.1f color:%i flags:%i\n", st.x, st.y, st.color, st.flags); */
        writeFloat(file, st.x);
        embFile_print(file, ",");
        writeFloat(file, st.y);
        embFile_print(file, " color:");
        writeInt(file, st.color, 6);
        embFile_print(file, " flags:");
        writeInt(file, st.flags, 6);
        embFile_print(file, "\n");
    }
    return 1;
}

