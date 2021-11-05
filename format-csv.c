#include "embroidery.h"
#include <stdlib.h>
#include <string.h>

typedef enum
{
    CSV_EXPECT_NULL,
    CSV_EXPECT_QUOTE1,
    CSV_EXPECT_QUOTE2,
    CSV_EXPECT_COMMA
} CSV_EXPECT;

typedef enum
{
    CSV_MODE_NULL,
    CSV_MODE_COMMENT,
    CSV_MODE_VARIABLE,
    CSV_MODE_THREAD,
    CSV_MODE_STITCH
} CSV_MODE;

static char* csvStitchFlagToStr(int flags)
{
    switch(flags)
    {
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
    if(!str)
    {
        printf("ERROR: format-csv.c csvStrToStitchFlag(), str argument is null\n");
        return -1;
    }
    if(!strcmp(str, "STITCH"))
        return NORMAL;
    else if(!strcmp(str, "JUMP"))
        return JUMP;
    else if(!strcmp(str, "TRIM"))
        return TRIM;
    else if(!strcmp(str, "COLOR"))
        return STOP;
    else if(!strcmp(str, "END"))
        return END;
    else if(!strcmp(str, "UNKNOWN"))
        return -1;
    return -1;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readCsv(EmbPattern* pattern, const char* fileName)
{
    FILE* file = 0;
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

    if (!validateReadPattern(pattern, fileName, "readCsv")) return 0;

    buff = (char*)malloc(size);
    if (!buff) {
        printf("ERROR: format-csv.c readCsv(), unable to allocate memory for buff\n");
        return 0;
    }

    file = fopen(fileName, "r");
    if (!file) {
        printf("ERROR: failed to open file with name %s.", fileName);
        return 0;
    }

    pos = 0;
    do {
        c = fgetc(file);
        switch(c) {
            case '"':
                if (expect == CSV_EXPECT_QUOTE1) {
                    expect = CSV_EXPECT_QUOTE2;
                }
                else if(expect == CSV_EXPECT_QUOTE2)
                    expect = CSV_EXPECT_COMMA;
                break;
            case ',':
                if (expect == CSV_EXPECT_COMMA) {
                    process = 1;
                }
                    break;
            case '\n':
                if(expect == CSV_EXPECT_COMMA) {
                    process = 1;
                }
                else if(expect == CSV_EXPECT_QUOTE1) {
                        /* Do Nothing. We encountered a blank line. */
                }
                else {
                    printf("ERROR: format-csv.c readCsv(), premature newline\n");
                    return 0;
                }
                break;
            default:
                break;
        }
        if (pos >= size - 1) {
            size *= 2;
            buff = (char*)realloc(buff,size);
            if (!buff) {
                printf("ERROR: format-csv.c readCsv(), cannot re-allocate memory for buff\n");
                return 0;
            }
        }

        if (process) {
            buff[pos] = 0;
            pos = 0;
            process = 0;
            cellNum++;
            expect = CSV_EXPECT_QUOTE1;
                if(csvMode == CSV_MODE_NULL)
                {
                    if     (!strcmp(buff, "#")) { csvMode = CSV_MODE_COMMENT; }
                    else if(!strcmp(buff, ">")) { csvMode = CSV_MODE_VARIABLE; }
                    else if(!strcmp(buff, "$")) { csvMode = CSV_MODE_THREAD; }
                    else if(!strcmp(buff, "*")) { csvMode = CSV_MODE_STITCH; }
                    else { /* TODO: error */ return 0; }
                }
                else if(csvMode == CSV_MODE_COMMENT)
                {
                    /* Do Nothing */
                }
                else if(csvMode == CSV_MODE_VARIABLE)
                {
                    /* Do Nothing */
                }
                else if(csvMode == CSV_MODE_THREAD)
                {
                    if(cellNum == 2)
                    {
                        /* Do Nothing. Ignore Thread Number */
                    }
                    else if(cellNum == 3)
                        r = (unsigned char)atoi(buff);
                    else if(cellNum == 4)
                        g = (unsigned char)atoi(buff);
                    else if(cellNum == 5)
                        b = (unsigned char)atoi(buff);
                    else if(cellNum == 6)
                    {
                        /* TODO: Thread Description */
                    }
                    else if(cellNum == 7)
                    {
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
                    }
                    else
                    {
                        /* TODO: error */
                        return 0;
                    }
                }
                else if(csvMode == CSV_MODE_STITCH)
                {
                    if(cellNum == 2)
                    {
                        flags = csvStrToStitchFlag(buff);
                        if(flags == STOP)
                            numColorChanges++;
                    }
                    else if(cellNum == 3)
                        xx = atof(buff);
                    else if(cellNum == 4)
                    {
                        yy = atof(buff);
                        embPattern_addStitchAbs(pattern, xx, yy, flags, 1);
                        csvMode = CSV_MODE_NULL;
                        cellNum = 0;
                    }
                    else
                    {
                        /* TODO: error */
                        return 0;
                    }
                }

                if(c == '\n')
                {
                    csvMode = CSV_MODE_NULL;
                    cellNum = 0;
                }
            }
            else
            {
                if(expect == CSV_EXPECT_QUOTE2 && c != '"')
                    buff[pos++] = (char)c;
            }
        }
        while(c != EOF);
        fclose(file);

    /* if not enough colors defined, fill in random colors */
    while (pattern->threads->count < numColorChanges) {
        embPattern_addThread(pattern, embThread_getRandom());
    }

    free(buff);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeCsv(EmbPattern* pattern, const char* fileName)
{
    FILE* file;
    EmbStitchList* sList;
    EmbRect boundingRect;
    EmbThread thr;
    int i;
    int stitchCount = 0;
    int threadCount = 0;

    if (!validateReadPattern(pattern, fileName, "writeCsv")) {
        printf("ERROR: Failed to validate pattern.");
        return 60;
    }

    sList = pattern->stitchList;
    stitchCount = embStitchList_count(sList);
    threadCount = pattern->threads->count;

    boundingRect = embPattern_calcBoundingBox(pattern);

    if(!stitchCount)
    {
        printf("ERROR: format-csv.c writeCsv(), pattern contains no stitches.\n");
        return 1;
    }

    embPattern_end(pattern);

    file = fopen(fileName, "w");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 1;
    }

    /* write header */
    fprintf(file, "\"#\",\"Embroidermodder 2 CSV Embroidery File\"\n");
    fprintf(file, "\"#\",\"http://embroidermodder.github.io\"\n");
    fprintf(file, "\n");
    fprintf(file, "\"#\",\"General Notes:\"\n");
    fprintf(file, "\"#\",\"This file can be read by Excel or LibreOffice as CSV (Comma Separated Value) or with a text editor.\"\n");
    fprintf(file, "\"#\",\"Lines beginning with # are comments.\"\n");
    fprintf(file, "\"#\",\"Lines beginning with > are variables: [VAR_NAME], [VAR_VALUE]\"\n");
    fprintf(file, "\"#\",\"Lines beginning with $ are threads: [THREAD_NUMBER], [RED], [GREEN], [BLUE], [DESCRIPTION], [CATALOG_NUMBER]\"\n");
    fprintf(file, "\"#\",\"Lines beginning with * are stitch entries: [STITCH_TYPE], [X], [Y]\"\n");
    fprintf(file, "\n");
    fprintf(file, "\"#\",\"Stitch Entry Notes:\"\n");
    fprintf(file, "\"#\",\"STITCH instructs the machine to move to the position [X][Y] and then make a stitch.\"\n");
    fprintf(file, "\"#\",\"JUMP instructs the machine to move to the position [X][Y] without making a stitch.\"\n");
    fprintf(file, "\"#\",\"TRIM instructs the machine to cut the thread before moving to the position [X][Y] without making a stitch.\"\n");
    fprintf(file, "\"#\",\"COLOR instructs the machine to stop temporarily so that the user can change to a different color thread before resuming.\"\n");
    fprintf(file, "\"#\",\"END instructs the machine that the design is completed and there are no further instructions.\"\n");
    fprintf(file, "\"#\",\"UNKNOWN encompasses instructions that may not be supported currently.\"\n");
    fprintf(file, "\"#\",\"[X] and [Y] are absolute coordinates in millimeters (mm).\"\n");
    fprintf(file, "\n");

    /* write variables */
    fprintf(file,"\"#\",\"[VAR_NAME]\",\"[VAR_VALUE]\"\n");
    fprintf(file, "\">\",\"STITCH_COUNT:\",\"%u\"\n",   (unsigned int)stitchCount);
    fprintf(file, "\">\",\"THREAD_COUNT:\",\"%u\"\n",   (unsigned int)threadCount);
    fprintf(file, "\">\",\"EXTENTS_LEFT:\",\"%f\"\n",   boundingRect.left);
    fprintf(file, "\">\",\"EXTENTS_TOP:\",\"%f\"\n",    boundingRect.top);
    fprintf(file, "\">\",\"EXTENTS_RIGHT:\",\"%f\"\n",  boundingRect.right);
    fprintf(file, "\">\",\"EXTENTS_BOTTOM:\",\"%f\"\n", boundingRect.bottom);
    fprintf(file, "\">\",\"EXTENTS_WIDTH:\",\"%f\"\n",  embRect_width(boundingRect));
    fprintf(file, "\">\",\"EXTENTS_HEIGHT:\",\"%f\"\n", embRect_height(boundingRect));
    fprintf(file,"\n");

    /* write colors */
    fprintf(file, "\"#\",\"[THREAD_NUMBER]\",\"[RED]\",\"[GREEN]\",\"[BLUE]\",\"[DESCRIPTION]\",\"[CATALOG_NUMBER]\"\n");
    for (i=0; i<threadCount; i++) {
        thr = pattern->threads->thread[i];
        /* TODO: fix segfault that backtraces here when libembroidery-convert from dst to csv. */
        fprintf(file, "\"$\",\"%d\",\"%d\",\"%d\",\"%d\",\"%s\",\"%s\"\n", i+1,
                (int)thr.color.r,
                (int)thr.color.g,
                (int)thr.color.b,
                thr.description,
                thr.catalogNumber);
    }
    fprintf(file, "\n");

    /* write stitches */
    fprintf(file, "\"#\",\"[STITCH_TYPE]\",\"[X]\",\"[Y]\"\n");
    while (sList) {
        EmbStitch s = sList->stitch;
        fprintf(file, "\"*\",\"%s\",\"%f\",\"%f\"\n", csvStitchFlagToStr(s.flags), s.x, s.y);
        sList = sList->next;
    }

    fclose(file);
    return 0;
}

