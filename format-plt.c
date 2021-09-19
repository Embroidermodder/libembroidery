/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readPlt(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    double x, y;
    double scalingFactor = 40;
    char input[512];

    embPattern_loadExternalColorFile(pattern, fileName);
    /* TODO: replace all scanf code */
    /* readline needs not to stop at \n, check the file format definition */
    while (!embFile_eof(file)) {
        embFile_readline(file, input, 511);
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
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writePlt(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    /* TODO: pointer safety */
    double scalingFactor = 40;
    EmbStitch stitch;
    int i;
    char firstStitchOfBlock = 1;

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

    return 1; /*TODO: finish WritePlt */
}

