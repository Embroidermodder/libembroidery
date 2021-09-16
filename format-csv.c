#include "embroidery.h"
#include <stdlib.h>
#include <string.h>

#define CSV_EXPECT_NULL   0
#define CSV_EXPECT_QUOTE1 1
#define CSV_EXPECT_QUOTE2 2
#define CSV_EXPECT_COMMA  3

#define CSV_MODE_NULL     0
#define CSV_MODE_COMMENT  1
#define CSV_MODE_VARIABLE 2
#define CSV_MODE_THREAD   3
#define CSV_MODE_STITCH   4

static char* csvStitchFlagToStr(int flags)
{
    switch (flags) {
    case NORMAL:
        return "STITCH";
        break;
    case JUMP:
        return "JUMP";
        break;
    case TRIM:
        return "TRIM";
        break;
    case STOP:
        return "COLOR";
        break;
    case END:
        return "END";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}

static int csvStrToStitchFlag(const char* str)
{
    if (!str) {
        embLog("ERROR: format-csv.c csvStrToStitchFlag(), str argument is null\n");
        return -1;
    }
    if (!strcmp(str, "STITCH"))
        return NORMAL;
    else if (!strcmp(str, "JUMP"))
        return JUMP;
    else if (!strcmp(str, "TRIM"))
        return TRIM;
    else if (!strcmp(str, "COLOR"))
        return STOP;
    else if (!strcmp(str, "END"))
        return END;
    else if (!strcmp(str, "UNKNOWN"))
        return -1;
    return -1;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readCsv(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int numColorChanges = 0;
    int size = 1024;
    int pos = 0;
    int c = 0;
    int cellNum = 0;
    int process = 0;
    int csvMode = CSV_MODE_NULL;
    int expect = CSV_EXPECT_QUOTE1;
    int flags = 0;
    double xx = 0.0;
    double yy = 0.0;
    unsigned char r = 0, g = 0, b = 0;
    char* buff = 0;

    buff = (char*)malloc(size);
    if (!buff) {
        embLog("ERROR: format-csv.c readCsv(), unable to allocate memory for buff\n");
        return 0;
    }

    pos = 0;
    do {
        c = embFile_getc(file);
        switch (c) {
        case '"':
            if (expect == CSV_EXPECT_QUOTE1) {
                expect = CSV_EXPECT_QUOTE2;
            } else if (expect == CSV_EXPECT_QUOTE2)
                expect = CSV_EXPECT_COMMA;
            break;
        case ',':
            if (expect == CSV_EXPECT_COMMA) {
                process = 1;
            }
            break;
        case '\n':
            if (expect == CSV_EXPECT_COMMA) {
                process = 1;
            } else if (expect == CSV_EXPECT_QUOTE1) {
                /* Do Nothing. We encountered a blank line. */
            } else {
                embLog("ERROR: format-csv.c readCsv(), premature newline\n");
                return 0;
            }
            break;
        }
        if (pos >= size - 1) {
            size *= 2;
            buff = (char*)realloc(buff, size);
            if (!buff) {
                embLog("ERROR: format-csv.c readCsv(), cannot re-allocate memory for buff\n");
                return 0;
            }
        }

        if (process) {
            buff[pos] = 0;
            pos = 0;
            process = 0;
            cellNum++;
            expect = CSV_EXPECT_QUOTE1;
            if (csvMode == CSV_MODE_NULL) {
                if (!strcmp(buff, "#")) {
                    csvMode = CSV_MODE_COMMENT;
                } else if (!strcmp(buff, ">")) {
                    csvMode = CSV_MODE_VARIABLE;
                } else if (!strcmp(buff, "$")) {
                    csvMode = CSV_MODE_THREAD;
                } else if (!strcmp(buff, "*")) {
                    csvMode = CSV_MODE_STITCH;
                } else { /* TODO: error */
                    return 0;
                }
            } else if (csvMode == CSV_MODE_COMMENT) {
                /* Do Nothing */
            } else if (csvMode == CSV_MODE_VARIABLE) {
                /* Do Nothing */
            } else if (csvMode == CSV_MODE_THREAD) {
                if (cellNum == 2) {
                    /* Do Nothing. Ignore Thread Number */
                } else if (cellNum == 3)
                    r = (unsigned char)atoi(buff);
                else if (cellNum == 4)
                    g = (unsigned char)atoi(buff);
                else if (cellNum == 5)
                    b = (unsigned char)atoi(buff);
                else if (cellNum == 6) {
                    /* TODO: Thread Description */
                } else if (cellNum == 7) {
                    /* TODO: Thread Catalog Number */
                    EmbThread t;
                    t.color.r = r;
                    t.color.g = g;
                    t.color.b = b;
                    t.description = "TODO:DESCRIPTION";
                    t.catalogNumber = "TODO:CATALOG_NUMBER";
                    embPattern_addThread(pattern, t);
                    csvMode = CSV_MODE_NULL;
                    cellNum = 0;
                } else {
                    /* TODO: error */
                    return 0;
                }
            } else if (csvMode == CSV_MODE_STITCH) {
                if (cellNum == 2) {
                    flags = csvStrToStitchFlag(buff);
                    if (flags == STOP)
                        numColorChanges++;
                } else if (cellNum == 3)
                    xx = atof(buff);
                else if (cellNum == 4) {
                    yy = atof(buff);
                    embPattern_addStitchAbs(pattern, xx, yy, flags, 1);
                    csvMode = CSV_MODE_NULL;
                    cellNum = 0;
                } else {
                    /* TODO: error */
                    return 0;
                }
            }

            if (c == '\n') {
                csvMode = CSV_MODE_NULL;
                cellNum = 0;
            }
        } else {
            if (expect == CSV_EXPECT_QUOTE2 && c != '"')
                buff[pos++] = (char)c;
        }
    } while (c != EOF);

    /* if not enough colors defined, fill in random colors */
    while (pattern->threads->count < numColorChanges) {
        embPattern_addThread(pattern, embThread_getRandom());
    }

    free(buff);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeCsv(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbStitch st;
    EmbRect boundingRect;
    EmbThread thr;
    int i;
    int stitchCount = 0;
    int threadCount = 0;

    stitchCount = pattern->stitchList->count;
    threadCount = pattern->threads->count;

    boundingRect = embPattern_calcBoundingBox(pattern);

    if (!stitchCount) {
        embLog("ERROR: format-csv.c writeCsv(), pattern contains no stitches\n");
        return 0;
    }

    embPattern_end(pattern);

    /* write header */
    embFile_print(file, "\"#\",\"Embroidermodder 2 CSV Embroidery File\"\n");
    embFile_print(file, "\"#\",\"http://embroidermodder.github.io\"\n");
    embFile_print(file, "\n");
    embFile_print(file, "\"#\",\"General Notes:\"\n");
    embFile_print(file, "\"#\",\"This file can be read by Excel or LibreOffice as CSV (Comma Separated Value) or with a text editor.\"\n");
    embFile_print(file, "\"#\",\"Lines beginning with # are comments.\"\n");
    embFile_print(file, "\"#\",\"Lines beginning with > are variables: [VAR_NAME], [VAR_VALUE]\"\n");
    embFile_print(file, "\"#\",\"Lines beginning with $ are threads: [THREAD_NUMBER], [RED], [GREEN], [BLUE], [DESCRIPTION], [CATALOG_NUMBER]\"\n");
    embFile_print(file, "\"#\",\"Lines beginning with * are stitch entries: [STITCH_TYPE], [X], [Y]\"\n");
    embFile_print(file, "\n");
    embFile_print(file, "\"#\",\"Stitch Entry Notes:\"\n");
    embFile_print(file, "\"#\",\"STITCH instructs the machine to move to the position [X][Y] and then make a stitch.\"\n");
    embFile_print(file, "\"#\",\"JUMP instructs the machine to move to the position [X][Y] without making a stitch.\"\n");
    embFile_print(file, "\"#\",\"TRIM instructs the machine to cut the thread before moving to the position [X][Y] without making a stitch.\"\n");
    embFile_print(file, "\"#\",\"COLOR instructs the machine to stop temporarily so that the user can change to a different color thread before resuming.\"\n");
    embFile_print(file, "\"#\",\"END instructs the machine that the design is completed and there are no further instructions.\"\n");
    embFile_print(file, "\"#\",\"UNKNOWN encompasses instructions that may not be supported currently.\"\n");
    embFile_print(file, "\"#\",\"[X] and [Y] are absolute coordinates in millimeters (mm).\"\n");
    embFile_print(file, "\n");

    /* write variables */
    embFile_print(file, "\"#\",\"[VAR_NAME]\",\"[VAR_VALUE]\"\n");
    embFile_print(file, "\">\",\"STITCH_COUNT:\",\"");
    writeInt(file, stitchCount, 6);
    embFile_print(file, "\"\n");
    embFile_print(file, "\">\",\"THREAD_COUNT:\",\"");
    writeInt(file, threadCount, 6);
    embFile_print(file, "\"\n");
    embFile_print(file, "\">\",\"EXTENTS_LEFT:\",\"");
    writeFloat(file, boundingRect.left);
    embFile_print(file, "\"\n");
    embFile_print(file, "\">\",\"EXTENTS_TOP:\",\"");
    writeFloat(file, boundingRect.top);
    embFile_print(file, "\"\n");
    embFile_print(file, "\">\",\"EXTENTS_RIGHT:\",\"");
    writeFloat(file, boundingRect.right);
    embFile_print(file, "\"\n");
    embFile_print(file, "\">\",\"EXTENTS_BOTTOM:\",\"");
    writeFloat(file, boundingRect.bottom);
    embFile_print(file, "\"\n");
    embFile_print(file, "\">\",\"EXTENTS_WIDTH:\",\"");
    writeFloat(file, embRect_width(boundingRect));
    embFile_print(file, "\"\n");
    embFile_print(file, "\">\",\"EXTENTS_HEIGHT:\",\"");
    writeFloat(file, embRect_height(boundingRect));
    embFile_print(file, "\"\n\n");

    /* write colors */
    embFile_print(file, "\"#\",\"[THREAD_NUMBER]\",\"[RED]\",\"[GREEN]\",\"[BLUE]\",\"[DESCRIPTION]\",\"[CATALOG_NUMBER]\"\n");
    for (i = 0; i < threadCount; i++) {
        thr = pattern->threads->thread[i];
        /* TODO: fix segfault that backtraces here when libembroidery-convert from dst to csv. */
        embFile_print(file, "\"$\",\"");
        writeInt(file, i + 1, 3);
        embFile_print(file, "\",\"");
        writeInt(file, (int)thr.color.r, 4);
        embFile_print(file, "\",\"");
        writeInt(file, (int)thr.color.g, 4);
        embFile_print(file, "\",\"");
        writeInt(file, (int)thr.color.b, 4);
        embFile_print(file, "\",\"");
        embFile_print(file, thr.description);
        embFile_print(file, "\",\"");
        embFile_print(file, thr.catalogNumber);
        embFile_print(file, "\"\n");
    }
    embFile_print(file, "\n");

    /* write stitches */
    embFile_print(file, "\"#\",\"[STITCH_TYPE]\",\"[X]\",\"[Y]\"\n");
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        embFile_print(file, "\"*\",\"");
        embFile_print(file, csvStitchFlagToStr(st.flags));
        embFile_print(file, "\",\"");
        writeFloat(file, st.x);
        embFile_print(file, "\",\"");
        writeFloat(file, st.y);
        embFile_print(file, "\"\n");
    }

    return 1;
}

