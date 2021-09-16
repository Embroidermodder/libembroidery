#include "embroidery.h"
#include <stdio.h>
#include <string.h>

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readPlt(EmbPattern* pattern, const char* fileName)
{
    double x, y;
    double scalingFactor = 40;
    char input[512];
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readPlt"))
        return 0;

    file = fopen(fileName, "rb");
    if (!file) {
        embLog("ERROR: format-plt.c readPlt(), cannot open");
        embLog(fileName);
        embLog(" for reading\n");
        return 0;
    }

    embPattern_loadExternalColorFile(pattern, fileName);
    /* TODO: replace all scanf code */
    while (fscanf(file, "%s", input) >= 0) {
        if (input[0] == 'P' && input[1] == 'D') {
            /* TODO: replace all scanf code */
            if (sscanf(input, "PD%lf,%lf;", &x, &y) < 2) {
                break;
            }
            embPattern_addStitchAbs(pattern, x / scalingFactor, y / scalingFactor, NORMAL, 1);
        } else if (input[0] == 'P' && input[1] == 'U') {
            /* TODO: replace all scanf code */
            if (sscanf(input, "PU%lf,%lf;", &x, &y) < 2) {
                break;
            }
            embPattern_addStitchAbs(pattern, x / scalingFactor, y / scalingFactor, STOP, 1);
        }
    }
    fclose(file);
    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writePlt(EmbPattern* pattern, const char* fileName)
{
    /* TODO: pointer safety */
    double scalingFactor = 40;
    EmbStitch stitch;
    int i;
    char firstStitchOfBlock = 1;
    EmbFile* file;

    if (!validateWritePattern(pattern, fileName, "writePlt")) {
        return 0;
    }

    file = embFile_open(fileName, "wb", 0);
    if (!file)
        return 0;

    embFile_print(file, "IN;ND;");

    for (i = 0; i < pattern->stitchList->count; i++) {
        stitch = pattern->stitchList->stitch[i];
        if (stitch.flags & STOP) {
            firstStitchOfBlock = 1;
        }
        if (firstStitchOfBlock) {
            embFile_print(file, "PU");
            writeFloat(file, stitch.x * scalingFactor);
            embFile_print(file, ",");
            writeFloat(file, stitch.y * scalingFactor);
            embFile_print(file, ";ST0.00,0.00;SP0;HT0;HS0;TT0;TS0;");
            firstStitchOfBlock = 0;
        } else {
            embFile_print(file, "PD");
            writeFloat(file, stitch.x * scalingFactor);
            embFile_print(file, ",");
            writeFloat(file, stitch.y * scalingFactor);
            embFile_print(file, ";");
        }
    }
    embFile_print(file, "PU0.0,0.0;PU0.0,0.0;");
    embFile_close(file);
    return 1; /*TODO: finish WritePlt */
}

