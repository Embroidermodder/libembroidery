#include "embroidery.h"
#include "embroidery-internal.h"

#include <string.h>

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readPlt(EmbPattern* pattern, const char* fileName)
{
    double x, y;
    double scalingFactor = 40;
    char input[512];
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readPlt"))
        return 0;

    file = fopen(fileName, "rb");
    if (!file) {
        printf("ERROR: format-plt.c readPlt(), cannot open %s for reading\n", fileName);
        return 0;
    }

    embPattern_loadExternalColorFile(pattern, fileName);
    /* TODO: replace all scanf code */
    while (emb_readline(file, input, 511)) {
        if (input[0] == 'P' && input[1] == 'D') {
            /* TODO: replace all scanf code */
            if(sscanf(input, "PD%lf,%lf;", &x, &y) < 2)
            {
                break;
            }
            embPattern_addStitchAbs(pattern, x / scalingFactor, y / scalingFactor, NORMAL, 1);
        }
        else if (input[0] == 'P' && input[1] == 'U') {
            /* TODO: replace all scanf code */
            if(sscanf(input, "PU%lf,%lf;", &x, &y) < 2)
            {
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
char writePlt(EmbPattern* pattern, const char* fileName)
{
    /* TODO: pointer safety */
    double scalingFactor = 40;
    EmbStitch stitch;
    EmbStitchList* pointer = 0;
    char firstStitchOfBlock = 1;
    FILE* file;

    if (!validateWritePattern(pattern, fileName, "writePlt")) {
        return 0;
    }
    
    file = fopen(fileName, "w");
    if (!file)
        return 0;

    fprintf(file, "IN;");
    fprintf(file, "ND;");

    pointer = pattern->stitchList;
    while(pointer)
    {
        stitch = pointer->stitch;
        if(stitch.flags & STOP)
        {
            firstStitchOfBlock = 1;
        }
        if(firstStitchOfBlock)
        {
            fprintf(file, "PU%f,%f;", stitch.x * scalingFactor, stitch.y * scalingFactor);
            fprintf(file, "ST0.00,0.00;");
            fprintf(file, "SP0;");
            fprintf(file, "HT0;");
            fprintf(file, "HS0;");
            fprintf(file, "TT0;");
            fprintf(file, "TS0;");
            firstStitchOfBlock = 0;
        }
        else
        {
            fprintf(file, "PD%f,%f;", stitch.x * scalingFactor, stitch.y * scalingFactor);
        }

        pointer = pointer->next;
    }
    fprintf(file, "PU0.0,0.0;");
    fprintf(file, "PU0.0,0.0;");
    fclose(file);
    return 1; /*TODO: finish WritePlt */
}


