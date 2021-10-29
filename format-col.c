#include "embroidery.h"
#include <stdlib.h>
#include <string.h>

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readCol(EmbPattern* pattern, const char* fileName)
{
    int numberOfColors, i;
    EmbFile* file;
    int num, blue, green, red;
    EmbThread t;
    char line[30];

    if (!validateReadPattern(pattern, fileName, "readCol")) return 0;

    file = embFile_open(fileName, "r", 1);
    if (!file) return 0;

    embArray_free(pattern->threads);
    pattern->threads = embArray_create(EMB_THREAD);

    embFile_readline(file, line, 30);
    numberOfColors = atoi(line);
    if (numberOfColors < 1) {
        printf("ERROR: Number of colors is zero.");
        return 0;
    }
    for (i = 0; i < numberOfColors; i++) {
        embFile_readline(file, line, 30);
        if (strlen(line) < 1) {
            printf("ERROR: Empty line in col file.");
            return 0;
        }
        /* TODO: replace all scanf code */
        if(sscanf(line,"%d,%d,%d,%d", &num, &blue, &green, &red) != 4) {
            break;
        }
        t.color.r = (unsigned char)red;
        t.color.g = (unsigned char)green;
        t.color.b = (unsigned char)blue;
        t.catalogNumber = "";
        t.description = "";
        embPattern_addThread(pattern, t);
    }
    embFile_close(file);
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeCol(EmbPattern* pattern, const char* fileName)
{
    FILE* file = 0;
    int i;
    EmbColor c;

    if (!validateWritePattern(pattern, fileName, "writeCol")) return 0;

    file = fopen(fileName, "w");
    if (!file) {
        printf("ERROR: format-col.c writeCol(), cannot open %s for writing\n", fileName);
        return 0;
    }
    fprintf(file, "%d\r\n", pattern->threads->count);
    for (i=0; i<pattern->threads->count; i++) {
        c = pattern->threads->thread[i].color;
        fprintf(file, "%d,%d,%d,%d\r\n", i, (int)c.r, (int)c.g, (int)c.b);
    }
    fclose(file);
    return 1;
}

