/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readCol(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int numberOfColors, i;
    int num, blue, green, red;
    EmbThread t;
    char line[30];

    embArray_free(pattern->threads);
    pattern->threads = embArray_create(EMB_THREAD);

    embFile_readline(file, line, 30);
    numberOfColors = atoi(line);
    if (numberOfColors < 1) {
        embLog("ERROR: Number of colors is zero.");
        return 0;
    }
    for (i = 0; i < numberOfColors; i++) {
        embFile_readline(file, line, 30);
        if (strlen(line) < 1) {
            embLog("ERROR: Empty line in col file.");
            return 0;
        }
        /* TODO: replace all scanf code */
        if (sscanf(line, "%d,%d,%d,%d", &num, &blue, &green, &red) != 4) {
            break;
        }
        t.color.r = (unsigned char)red;
        t.color.g = (unsigned char)green;
        t.color.b = (unsigned char)blue;
        t.catalogNumber = "";
        t.description = "";
        embPattern_addThread(pattern, t);
    }
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeCol(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;
    EmbColor c;
    unsigned char buffer[30];

    sprintf(buffer, "%d\r\n", pattern->threads->count);
    embFile_print(file, buffer);
    for (i = 0; i < pattern->threads->count; i++) {
        c = pattern->threads->thread[i].color;
        sprintf(buffer, "%d,%d,%d,%d\r\n", i, (int)c.r, (int)c.g, (int)c.b);
        embFile_print(file, buffer);
    }
    return 1;
}

