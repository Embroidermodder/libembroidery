#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>

#include "embroidery.h"

char readRgb(EmbPattern * pattern, FILE * file);
char writeRgb(EmbPattern * pattern, FILE * file);

char readDst(EmbPattern * pattern, FILE * file);
char writeDst(EmbPattern * pattern, FILE * file);

char readInf(EmbPattern * pattern, FILE * file);
char writeInf(EmbPattern * pattern, FILE * file);

char readPhb(EmbPattern * pattern, FILE * file);
char writePhb(EmbPattern * pattern, FILE * file);
char readPec(EmbPattern * pattern, FILE * file);
char writePec(EmbPattern * pattern, FILE * file);
char readPel(EmbPattern * pattern, FILE * file);
char writePel(EmbPattern * pattern, FILE * file);
char readPem(EmbPattern * pattern, FILE * file);
char writePem(EmbPattern * pattern, FILE * file);

/*
 * Script section
 */

static EmbPattern *focussed_pattern = NULL;

/* Tests if char * matches a fixed string, often from compiled-in program
 * data.
 */
bool string_equal(char *a, const char *b)
{
        return (strncmp(a, b, MAX_STRING_LENGTH) == 0);
}

/* . */
int parse_floats(const char *line, float result[], int n)
{
        char substring[MAX_STRING_LENGTH];
        const char *c;
        int i = 0;
        int pos = 0;
        for (c = line; *c; c++) {
                substring[pos] = *c;
                if (*c == ',' || *c == ' ') {
                        substring[pos] = 0;
                        result[i] = atof(substring);
                        pos = 0;
                        i++;
                        if (i > n - 1) {
                                return -1;
                        }
                } else {
                        pos++;
                }
        }
        substring[pos] = 0;
        result[i] = atof(substring);
        return i + 1;
}

int parse_vector(const char *line, EmbVector *v)
{
        float v_[2];
        if (parse_floats(line, v_, 2) == 2) {
                return 0;
        }
        v->x = v_[0];
        v->y = v_[1];
        return 1;
}

/* . */
bool valid_rgb(float r, float g, float b)
{
        if (isnan(r)) {
                return false;
        }
        if (isnan(g)) {
                return false;
        }
        if (isnan(b)) {
                return false;
        }
        if (r < 0 || r > 255) {
                return false;
        }
        if (g < 0 || g > 255) {
                return false;
        }
        if (b < 0 || b > 255) {
                return false;
        }
        return true;
}

/* This version of string_array_length does not protect against the END_SYMBOL
 * missing, because it is only to be used for compiled in constant tables.
 *
 * For string tables edited during run time, the END_SYMBOL is checked for during loops.
 */
int table_length(char *s[])
{
        int i;
        for (i = 0; i < 1000; i++) {
                if (s[i][0] == END_SYMBOL[0]) {
                        if (!strncmp(s[i], END_SYMBOL, MAX_STRING_LENGTH)) {
                                break;
                        }
                }
        }
        if (i == 1000) {
                puts("ERROR: Table is missing END_SYMBOL.");
                return 1000;
        }
        return i;
}

/* . */
unsigned char *load_file(char *fname)
{
        FILE *f = fopen(fname, "r");
        if (!f) {
                printf("ERROR: Failed to open \"%s\".\n", fname);
                return NULL;
        }
        fseek(f, 0, SEEK_END);
        size_t length = ftell(f);
        unsigned char *data = malloc(length + 1);
        fseek(f, 0, SEEK_SET);
        if (!read_n_bytes(f, data, length)) {
                fclose(f);
                return NULL;
        }
        fclose(f);
        return data;
}

/* . */
bool int32_underflow(int64_t a, int64_t b)
{
        int64_t c;
        assert(LLONG_MAX > INT_MAX);
        c = (int64_t) a - b;
        if (c < INT_MIN || c > INT_MAX) {
                return true;
        }
        return false;
}

/* . */
bool int32_overflow(int64_t a, int64_t b)
{
        int64_t c;
        assert(LLONG_MAX > INT_MAX);
        c = (int64_t) a + b;
        if (c < INT_MIN || c > INT_MAX) {
                return true;
        }
        return false;
}

/* . */
int round_to_multiple(bool roundUp, int numToRound, int multiple)
{
        if (multiple == 0) {
                return numToRound;
        }
        int remainder = numToRound % multiple;
        if (remainder == 0) {
                return numToRound;
        }

        if (numToRound < 0 && roundUp) {
                return numToRound - remainder;
        }
        if (roundUp) {
                return numToRound + multiple - remainder;
        }
        /* else round down */
        if (numToRound < 0 && !roundUp) {
                return numToRound - multiple - remainder;
        }
        return numToRound - remainder;
}

/* Formats each message with a timestamp. */
void debug_message(const char *msg, ...)
{
        char buffer[MAX_STRING_LENGTH], fname[MAX_STRING_LENGTH];
        time_t t;
        struct tm *tm_info;
        sprintf(fname, "debug.log");
        FILE *f = fopen(fname, "a");
        if (!f) {
                printf("Failed to write to debug.log.");
                return;
        }
        t = time(NULL);
        tm_info = localtime(&t);
        strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
        fprintf(f, "%s ", buffer);

        va_list args;
        va_start(args, msg);
        vfprintf(f, msg, args);
        va_end(args);

        fprintf(f, "\n");
        fclose(f);
}

/* . */
bool valid_file_format(char *fileName)
{
        if (emb_identify_format(fileName) >= 0) {
                return true;
        }
        return false;
}

const int shvThreadCount = 42;

/* The Melco Embroidery Format (.cnd)
 *
 * The Melco cnd format is a stitch-only format.
 *
 * We don't know much about this format.
 *
 * \todo Find a source.
 */
char readCnd(EmbPattern *pattern, FILE *file)
{
        puts("readCnd is not implemented");
        printf("Cannot read %p %p\n", pattern, file);
        return 0;               /*TODO: finish readCnd */
}

char writeCnd(EmbPattern *pattern, FILE *file)
{
        puts("writeCnd is not implemented");
        printf("Cannot write %p %p\n", pattern, file);
        return 0;               /*TODO: finish writeCnd */
}

/* Comma Separated Values (.csv)
 *
 * Comma Seperated Values files aren't a universal system, here we aim to
 * offer a broad support. The dialect is detected based on the opening lines,
 * as each manufacturer should label their CSV files there.
 *
 * ## Embroidermodder 2.0 CSV Dialect
 *
 * Our own version has the identifier comment line:
 *
 * | Control Symbol | Type | Description |
 * |---|---|
 * | `#` | `COMMENT` | |
 * | `>` | `VARIABLE` | To store records of a pattern's width, height etc. This means that data stored in the header of say a .dst file is preserved. |
 * | `$` | `THREAD` | |
 * | `*` | `STITCH` | |
 * | `*` | `JUMP` | |
 * | `*` | `COLOR` | To change a color: used for trim as well |
 * | `*` | `END` | To end a pattern. |
 * | `*` | `UNKNOWN` | For any feature that we can't identify.
 *
 * ## EmBird CSV Dialect
 *
 */
char *csvStitchFlagToStr(int flags)
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

int csvStrToStitchFlag(const char *str)
{
        if (!str) {
                printf
                    ("ERROR: format-csv.c csvStrToStitchFlag(), str argument is null\n");
                return -1;
        }
        if (!strncmp(str, "STITCH", 10)) {
                return NORMAL;
        }
        if (!strncmp(str, "JUMP", 10)) {
                return JUMP;
        }
        if (!strncmp(str, "TRIM", 10)) {
                return TRIM;
        }
        if (!strncmp(str, "COLOR", 10)) {
                return STOP;
        }
        if (!strncmp(str, "END", 10)) {
                return END;
        }
        if (!strncmp(str, "UNKNOWN", 10)) {
                return STOP;
        }
        return -1;
}

char readCsv(EmbPattern *pattern, FILE *file)
{
        int numColorChanges = 0;
        int pos = 0;
        int c = 0;
        int cellNum = 0;
        int process = 0;
        int csvMode = CSV_MODE_NULL;
        int expect = CSV_EXPECT_QUOTE1;
        int flags = 0;
        EmbReal xx = 0.0;
        EmbReal yy = 0.0;
        unsigned char r = 0, g = 0, b = 0;
        EmbString buff;

        pos = 0;
        while (!feof(file)) {
                c = fgetc(file);
                switch (c) {
                case '"':
                        if (expect == CSV_EXPECT_QUOTE1) {
                                expect = CSV_EXPECT_QUOTE2;
                        } else if (expect == CSV_EXPECT_QUOTE2) {
                                expect = CSV_EXPECT_COMMA;
                        }
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
                                printf
                                    ("ERROR: format-csv.c readCsv(), premature newline\n");
                                return 0;
                        }
                        break;
                default:
                        break;
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
                                } else {        /* TODO: error */
                                        return 0;
                                }
                        } else if (csvMode == CSV_MODE_COMMENT) {
                                /* Do Nothing */
                        } else if (csvMode == CSV_MODE_VARIABLE) {
                                /* Do Nothing */
                        } else if (csvMode == CSV_MODE_THREAD) {
                                if (cellNum == 2) {
                                        /* Do Nothing. Ignore Thread Number */
                                } else if (cellNum == 3) {
                                        r = (unsigned char)atoi(buff);
                                } else if (cellNum == 4) {
                                        g = (unsigned char)atoi(buff);
                                } else if (cellNum == 5) {
                                        b = (unsigned char)atoi(buff);
                                } else if (cellNum == 6) {
                                        /* TODO: Thread Description */
                                } else if (cellNum == 7) {
                                        /* TODO: Thread Catalog Number */
                                        EmbThread t;
                                        t.color.r = r;
                                        t.color.g = g;
                                        t.color.b = b;
                                        strcpy(t.description,
                                               "TODO:DESCRIPTION");
                                        strcpy(t.catalogNumber,
                                               "TODO:CATALOG_NUMBER");
                                        embp_addThread(pattern, t);
                                        csvMode = CSV_MODE_NULL;
                                        cellNum = 0;
                                } else {
                                        /* TODO: error */
                                        return 0;
                                }
                        } else if (csvMode == CSV_MODE_STITCH) {
                                /* printf("%s\n", buff); */
                                if (cellNum == 2) {
                                        flags = csvStrToStitchFlag(buff);
                                        if (flags == STOP) {
                                                numColorChanges++;
                                        }
                                } else if (cellNum == 3) {
                                        xx = atof(buff);
                                } else if (cellNum == 4) {
                                        yy = atof(buff);
                                        /* printf("%d %d %f %f\n",
                                           pattern->stitch_list->count, flags, xx, yy); */
                                        embp_addStitchAbs(pattern, xx, yy,
                                                          flags, 1);
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
                        if (expect == CSV_EXPECT_QUOTE2 && c != '"') {
                                buff[pos++] = (char)c;
                        }
                }
        }

        return 1;
}

char writeCsv(EmbPattern *pattern, FILE *file)
{
        EmbRect boundingRect;
        int i;

        boundingRect = embp_bounds(pattern);

        fprintf(file, "\"#\",\"Embroidermodder 2 CSV Embroidery File\"\n");
        fprintf(file, "\"#\",\"http://embroidermodder.github.io\"\n");
        fprintf(file, "\"#\",\" \"\n");
        fprintf(file, "\"#\",\"General Notes:\"\n");
        fprintf(file,
                "\"#\",\"This file can be read by Excel or LibreOffice as CSV (Comma Separated Value) or with a text editor.\"\n");
        fprintf(file, "\"#\",\"Lines beginning with # are comments.\"\n");
        fprintf(file,
                "\"#\",\"Lines beginning with > are variables: [VAR_NAME], [VAR_VALUE]\"\n");
        fprintf(file,
                "\"#\",\"Lines beginning with $ are threads: [THREAD_NUMBER], [RED], [GREEN], [BLUE], [DESCRIPTION], [CATALOG_NUMBER]\"\n");
        fprintf(file,
                "\"#\",\"Lines beginning with * are stitch entries: [STITCH_TYPE], [X], [Y]\"\n");
        fprintf(file, "\"#\",\" \"\n");
        fprintf(file, "\"#\",\"Stitch Entry Notes:\"\n");
        fprintf(file,
                "\"#\",\"STITCH instructs the machine to move to the position [X][Y] and then make a stitch.\"\n");
        fprintf(file,
                "\"#\",\"JUMP instructs the machine to move to the position [X][Y] without making a stitch.\"\n");
        fprintf(file,
                "\"#\",\"TRIM instructs the machine to cut the thread before moving to the position [X][Y] without making a stitch.\"\n");
        fprintf(file,
                "\"#\",\"COLOR instructs the machine to stop temporarily so that the user can change to a different color thread before resuming.\"\n");
        fprintf(file,
                "\"#\",\"END instructs the machine that the design is completed and there are no further instructions.\"\n");
        fprintf(file,
                "\"#\",\"UNKNOWN encompasses instructions that may not be supported currently.\"\n");
        fprintf(file,
                "\"#\",\"[X] and [Y] are absolute coordinates in millimeters (mm).\"\n");
        fprintf(file, "\"#\",\" \"\n");

        /* write variables */
        fprintf(file, "\"#\",\"[VAR_NAME]\",\"[VAR_VALUE]\"\n");
        fprintf(file, "\">\",\"STITCH_COUNT:\",\"%u\"\n",
                (unsigned int)pattern->stitch_list->count);
        fprintf(file, "\">\",\"THREAD_COUNT:\",\"%u\"\n",
                (unsigned int)pattern->thread_list->count);
        fprintf(file, "\">\",\"EXTENTS_LEFT:\",\"%f\"\n", boundingRect.x);
        fprintf(file, "\">\",\"EXTENTS_TOP:\",\"%f\"\n", boundingRect.y);
        fprintf(file, "\">\",\"EXTENTS_RIGHT:\",\"%f\"\n",
                boundingRect.x + boundingRect.w);
        fprintf(file, "\">\",\"EXTENTS_BOTTOM:\",\"%f\"\n",
                boundingRect.y + boundingRect.h);
        fprintf(file, "\">\",\"EXTENTS_WIDTH:\",\"%f\"\n", boundingRect.w);
        fprintf(file, "\">\",\"EXTENTS_HEIGHT:\",\"%f\"\n", boundingRect.h);
        fprintf(file, "\n");

        /* write colors */
        fprintf(file, "\"#\",\"[THREAD_NUMBER]\",\"[RED]\",\"[GREEN]\",");
        fprintf(file, "\"[BLUE]\",\"[DESCRIPTION]\",\"[CATALOG_NUMBER]\"\n");

        for (i = 0; i < pattern->thread_list->count; i++) {
                EmbThread thr = pattern->thread_list->thread[i];
                /* TODO: fix segfault that backtraces here when
                   libembroidery-convert from dst to csv. */
                fprintf(file,
                        "\"$\",\"%d\",\"%d\",\"%d\",\"%d\",\"%s\",\"%s\"\n",
                        i + 1, (int)thr.color.r, (int)thr.color.g,
                        (int)thr.color.b, thr.description, thr.catalogNumber);
        }
        fprintf(file, "\n");

        /* write stitches */
        fprintf(file, "\"#\",\"[STITCH_TYPE]\",\"[X]\",\"[Y]\"\n");
        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch s = pattern->stitch_list->stitch[i];
                fprintf(file, "\"*\",\"%s\",\"%f\",\"%f\"\n",
                        csvStitchFlagToStr(s.flags), s.x, s.y);
        }
        return 1;
}

/* The Barudan Embroidery Format (.dat)
 *
 * Stitch Only Format.
 */
char readDat(EmbPattern *pattern, FILE *file)
{
        unsigned char b0;
        int fileLength, stitchesRemaining, b1, b2, stitchType;

        fseek(file, 0x00, SEEK_END);
        fileLength = ftell(file);
        if (fileLength < 0x100) {
                puts("ERROR: dat file too short to contain header.");
                return 0;
        }
        fseek(file, 0x02, SEEK_SET);
        LOAD_U16(file, stitchesRemaining)
            fseek(file, 0x100, SEEK_SET);

        while (!feof(file)) {
                b1 = (int)fgetc(file);
                b2 = (int)fgetc(file);
                b0 = fgetc(file);

                stitchType = NORMAL;

                if ((b0 & 0x02) == 0)
                        stitchType = TRIM;

                if (b0 == 0x87) {
                        stitchType = STOP;
                }
                if (b0 == 0xF8) {
                        break;
                }
                if (b1 >= 0x80) {
                        b1 = -(b1 & 0x7F);
                }
                if (b2 >= 0x80) {
                        b2 = -(b2 & 0x7F);
                }
                embp_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
        }

        return 1;
}

char writeDat(EmbPattern *pattern, FILE *file)
{
        int i;
        fpad(file, 0x00, 0x100);
        for (i = 0; i < pattern->stitch_list->count; i++) {
                unsigned char b[3];
                EmbStitch st = pattern->stitch_list->stitch[i];
                b[0] = 0;
                b[1] = 0;
                b[2] = 0;
                if (st.flags == STOP) {
                        b[2] = 0x87;
                }
                if (st.flags == END) {
                        b[2] |= 0xF8;
                } else {
                        if (st.flags != TRIM) {
                                b[2] |= 0x02;
                        }
                }
                /* TODO: check that this works */
                if (st.x < 0) {
                        b[0] = st.x + 0xFF;
                }
                if (st.y < 0) {
                        b[1] = st.y + 0xFF;
                }
                fwrite(b, 1, 3, file);
        }
        return 1;               /*TODO: finish writeDat */
}

/* The Melco Embroidery Format (.dem)
 *
 * Stitch Only Format
 */
char readDem(EmbPattern *pattern, FILE *file)
{
        puts("readDem is not implemented.");
        puts("Overridden, defaulting to dst.");
        return readDst(pattern, file);  /*TODO: finish readDem */
}

char writeDem(EmbPattern *pattern, FILE *file)
{
        puts("writeDem is not implemented.");
        puts("Overridden, defaulting to dst.");
        return writeDst(pattern, file); /*TODO: finish writeDem */
}

/* The Barudan Embroidery Format (.dsb)
 *
 * Stitch Only Format.
 * [X] Basic Read Support
 * [o] Basic Write Support
 * [o] Well Tested Read
 * [o] Well Tested Write
 */
char readDsb(EmbPattern *pattern, FILE *file)
{
        char header[512 + 1];
        unsigned char buffer[3];

        if (fread(header, 1, 512, file) != 512) {
                puts("ERROR");
                return 0;
        }

        while (fread(buffer, 1, 3, file) == 3) {
                int x, y;
                unsigned char ctrl;
                int stitchType = NORMAL;

                ctrl = buffer[0];
                y = buffer[1];
                x = buffer[2];
                if (ctrl & 0x01)
                        stitchType = TRIM;
                if (ctrl & 0x20)
                        x = -x;
                if (ctrl & 0x40)
                        y = -y;
                /* ctrl & 0x02 - Speed change? *//* TODO: review this line */
                /* ctrl & 0x04 - Clutch? *//* TODO: review this line */
                if ((ctrl & 0x05) == 0x05) {
                        stitchType = STOP;
                }
                if (ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87) {
                        embp_addStitchRel(pattern, 0, 0, END, 1);
                        break;
                }
                embp_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
        }
        return 1;
}

char writeDsb(EmbPattern *pattern, FILE *file)
{
        puts("writeDsb is not implemented");
        puts("Overridden, defaulting to dst.");
        writeDst(pattern, file);
        return 0;               /*TODO: finish writeDsb */
}

/*
 * # Tajima Embroidery Format (.dst)
 * .DST (Tajima) embroidery file read/write routines
 * Format comments are thanks to tspilman@dalcoathletic.com who's
 * notes appeared at http://www.wotsit.org under Tajima Format.
 *
 * Stitch Only Format.
 * [X] Basic Read Support
 * [X] Basic Write Support
 * [ ] Well Tested Read
 * [ ] Well Tested Write
 *
 * Other references: \cite kde_tajima , \cite acatina .
 *
 * ## Header
 *
 * The header contains general information about the design. It is in lines of ASCII, so
 * if you open a DST file as a text file, it's the only part that's easy to read. The
 * line ending symbol is  `0x0D}. The header is necessary for the file to be read by
 * most softwares and hardwares.
 *
 * The header is 125 bytes of data followed by padding spaces to make it 512 bytes
 * in total.
 *
 * The lines are as follows.
 *
 * | *Label* | *Size* | *Description* | *Example* |
 * |----|----|----|----|
 * | `LA:` | 17 | The design name with no path or extension. The space reserved is 16 characters, but the name must not be longer than 8 and be padded to 16 with spaces (0x20). | `"LA:Star            "` |
 * | `ST:` | 8 | The stitch count. An integer in the format `%07d`, that is: a 7 digit number padded by leading zeros. This is the total accross all possible stitch flags. | |
 * | `CO:` | 4 | The number of color changes (not to be confused with thread count, an all black design we would have the record \textbf{000}). An integer in the format  `%03d`, that is: a 3 digit number padded by leading zeros. | |
 * | `+X:` | 6 | The extent of the pattern in the postitive x direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit number padded by leading zeros. | |
 * | `-X:` | 6 | The extent of the pattern in the negative x direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit integer padded by leading zeros. | |
 * | `+Y:` | 6 | The extent of the pattern in the postitive y direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit integer padded by leading zeros. | |
 * | `-Y:` | 6 | The extent of the pattern in the negative y direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit integer padded by leading zeros. | |
 * | `AX:` | 7 | The difference of the end from the start in the x direction in 0.1mm, the first char should be the sign, followed by an integer in the format `%05d`, that is: a 5 digit integer padded by leading zeros. | |
 * | `AY:` | 7 | The difference of the end from the start in the y direction in 0.1mm, the first char should be the sign, followed by an integer in the format `%05d`, that is: a 5 digit integer padded by leading zeros. | |
 * | `MX:` | 7 | The x co-ordinate of the last point in the previous file should the design span multiple files. Like AX, it is the sign, followed by a 5 digit integer. If we have a one file design set it to zero. | |
 * | `MY:` | 7 | The y co-ordinate of the last point in the previous file should the design span multiple files. Like AY, it is the sign, followed by a 5 digit integer. If we have a one file design set it to zero. | |
 * | `PD:` | 10 | Information about multivolume designs. | |
 *
 * ### Stitch Data
 *
 * Uses 3 byte per stitch encoding with the format as follows:
 *
 * | *Bit* | *7* | *6* | *5* | *4* | *3* | *2* | *1* | *0* |
 * |-------|-----|-----|-----|-----|-----|-----|-----|-----|
 * | Byte 0 | y+1 | y-1 | y+9 | y-9 | x-9 | x+9 | x-1 | x+1 |
 * | Byte 1 | y+3 | y-3 | y+27 | y-27 | x-27 | x+27 | x-3 | x+3 |
 * | Byte 2 | jump | color change | y+81 | y-81 | x-81 | x+81 | set | set |
 *
 * T01 and Tap appear to use Tajima Ternary.
 *
 * Where the stitch type is determined as:
 * 
 * * Normal Stitch `0b00000011 0x03`
 * * Jump Stitch `0b10000011 0x83`
 * * Stop/Change Color `0b11000011 0xC3`
 * * End Design `0b11110011 0xF3`
 *
 * Inclusive or'ed with the last byte.
 *
 * Note that the max stitch length is the largest sum of $1+3+9+27+81=121$
 * where the unit length is 0.1mm so 12.1mm. The coordinate system is right handed.
 *
 */
int decode_record_flags(unsigned char b2)
{
        if (b2 == 0xF3) {
                return END;
        }
        if (b2 & 0x40) {
                return STOP;
        }
        if (b2 & 0x80) {
                return JUMP;
        }
        return NORMAL;
}

/* TODO: review this then remove since emb-pattern.c has a similar function */
/*
void
combine_jump_stitches(EmbPattern* p, int jumpsPerTrim)
{
    if (!p) {
        printf("ERROR: format-dst.c combineJumpStitches(), p argument is null\n");
        return;
    }
    Embstitch_list* pointer = p->stitch_list;
    int jumpCount = 0;
    Embstitch_list* jumpListStart = 0;
    char needleDown = 0;
    while (pointer) {
        if ((pointer->stitch.flags & JUMP) && !(pointer->stitch.flags & STOP)) {
            if (jumpCount == 0)
            {
                jumpListStart = pointer;
            }
            jumpCount++;
            if (needleDown && jumpCount >= jumpsPerTrim)
            {
                Embstitch_list* removePointer = jumpListStart->next;
                jumpListStart->stitch.x = pointer->stitch.x;
                jumpListStart->stitch.y = pointer->stitch.y;
                jumpListStart->stitch.flags |= TRIM;
                jumpListStart->next = pointer;

                jumpCount-=2;
                for (; jumpCount > 0; jumpCount--)
                {
                    Embstitch_list* tempPointer = removePointer->next;
                    jumpListStart->stitch.flags |= removePointer->stitch.flags;
                    safe_free(removePointer);
                    removePointer = 0;
                    removePointer = tempPointer;
                }
                jumpCount = 0;
                needleDown = 0;
            }
        }
        else {
            if (pointer->stitch.flags == NORMAL)
            {
                needleDown = 1;
                jumpCount = 0;
            }
        }
        pointer = pointer->next;
    }
}
*/

void encode_record(FILE *file, int x, int y, int flags)
{
        unsigned char b[3];
        encode_tajima_ternary(b, x, y);

        b[2] |= 0x03;

        if (flags & END) {
                /* 0b10001101 = -13 = 0x8D */
                b[0] = 0;
                b[1] = 0;
                b[2] = 0x8D;
        }

        /* make the variable v configurable for the pattern */
        if (flags & TRIM) {
                int dx, dy, i, v = 5;
                dx = x / v;
                dy = y / v;
                for (i = 1; i < v; i++) {
                        encode_record(file, dx, dy, JUMP);
                }
                encode_record(file, x - (dx * (v - 1)), y - (dy * (v - 1)),
                              JUMP);
                return;
        }
        if (flags & (JUMP | TRIM)) {
                b[2] = (char)(b[2] | 0x83);
        }
        if (flags & STOP) {
                b[2] = (char)(b[2] | 0xC3);
        }

        fwrite(b, 1, 3, file);
}

/*convert 2 characters into 1 int for case statement */
/*#define cci(s) (s[0]*256+s[1]) */
#define cci(c1, c2) (c1*256+c2)

void set_dst_variable(EmbPattern *pattern, char *var, char *val)
{
        unsigned int i;
        EmbThread t;
        for (i = 0; i <= (unsigned int)strlen(var); i++) {
                /* uppercase the var */
                if (var[i] >= 'a' && var[i] <= 'z') {
                        var[i] += 'A' - 'a';
                }
        }

        /* macro converts 2 characters to 1 int, allows case statement... */
        switch (cci(var[0], var[1])) {
        case cci('L', 'A'):    /* Design Name (LA) */
                /*pattern->set_variable("Design_Name",val); TODO: review this line. */
                break;
        case cci('S', 'T'):    /* Stitch count, 7 digits padded by leading 0's */
        case cci('C', 'O'):    /* Color change count, 3 digits padded by leading 0's */
        case cci('+', 'X'):    /* Design extents (+/-X,+/-Y), 5 digits padded by leading 0's */
        case cci('-', 'X'):
        case cci('+', 'Y'):
        case cci('-', 'Y'):
                /* don't store these variables, they are recalculated at save */
                break;
        case cci('A', 'X'):    /* Relative coordinates of last point, 6 digits, padded with leading spaces, first char may be +/- */
        case cci('A', 'Y'):
        case cci('M', 'X'):    /* Coordinates of last point in previous file of multi-volume design, 6 digits, padded with leading spaces, first char may be +/- */
        case cci('M', 'Y'):
                /* store these variables as-is, they will be converted to numbers and back at save; */
                /*pattern->set_variable(var,val); TODO: review this line. */
                break;
        case cci('P', 'D'):
                /* store this string as-is, it will be saved as-is, 6 characters */
                if (strlen(val) != 6) {
                        /*pattern->messages.add("Warning: in DST file read,
                           PD is not 6 characters, but ",(int)strlen(val)); */
                }
                /*pattern->set_variable(var,val); */
                break;
                /* Begin extended fields section */
        case cci('A', 'U'):    /* Author string, arbitrary length */
        case cci('C', 'P'):    /* Copyright string, arbitrary length */
                /*pattern->set_variable(var,val); TODO: review this line. */
                break;
                /*Thread Color: #RRGGBB,Description,Catalog Number (1st field RGB
                   hex values, 2nd&3rd fields optional arbitrary length) */
        case cci('T', 'C'):
                /* TODO: review these lines below.
                   description=split_cell_str(val,2);
                   catalog_number=split_cell_str(val,3);
                 */
                t.color = embColor_fromHexStr(val);
                strcpy(t.description, "");
                strcpy(t.catalogNumber, "");
                embp_addThread(pattern, t);
                break;
        default:
                /* unknown field, just save it. */
                /*pattern->set_variable(var,val); TODO: review this line. */
                break;
        }
}

/*
 * The header seems to contain information about the design.
 * Seems to be ASCII text delimited by 0x0D (carriage returns).
 * This must be in the file for most new software or hardware
 * to consider it a good file! This is much more important
 * than I originally believed. The header is 125 bytes in
 * length and padded out by 0x20 to 512 bytes total.
 * All entries in the header seem to be 2 ASCII characters
 * followed by a colon, then it's value trailed by a carriage return.
 *
 * char LA[16+1];  First is the 'LA' entry, which is the design name with no
 *                 path or extension information. The blank is 16 characters
 *                 in total, but the name must not be longer that 8 characters
 *                 and padded out with 0x20.
 *
 * char ST[7+1];   Next is the stitch count ST, this is a 7 digit number
 *                 padded by leading zeros. This is the total stitch count
 *                 including color changes, jumps, nups, and special records.
 *
 * char CO[3+1];   Next, is CO or colors, a 3 digit number padded by leading
 *                 zeros. This is the number of color change records in the file.
 *
 * char POSX[5+1]; Next is +X or the positive X extent in centimeters, a 5
 *                 digit non-decimal number padded by leading zeros.
 *
 * char NEGX[5+1]; Following is the -X or the negative X extent in millimeters,
 *                 a 5 digit non-decimal number padded by leading zeros.
 *
 * char POSY[5+1]; Again, the +Y extents.
 *
 * char NEGY[5+1]; Again, the -Y extents.
 *
 * char AX[6+1];   AX and AY should express the relative coordinates of the
 * char AY[6+1];   last point from the start point in 0.1 mm. If the start
 *                 and last points are the same, the coordinates are (0,0).
 *
 * char MX[6+1];   MX and MY should express coordinates of the last point of
 * char MY[6+1];   the previous file for a multi-volume design. A multi-
 *                 volume design means a design consisted of two or more files.
 *                 This was used for huge designs that can not be stored in a
 *                 single paper tape roll. It is not used so much (almost
 *                 never) nowadays.
 *
 * char PD[9+1];   PD is also storing some information for multi-volume design.
 */
char readDst(EmbPattern *pattern, FILE *file)
{
        char var[3];            /* temporary storage variable name */
        char val[512];          /* temporary storage variable value */
        int valpos;
        unsigned char b[3];
        char header[512 + 1];
        int i = 0, flags;

        /* TODO: review commented code below
           pattern->clear();
           pattern->set_variable("file_name",filename);
         */

        if (fread(header, 1, 512, file) != 512) {
                puts("ERROR: Failed to read header bytes.");
                return 0;
        }

        /*TODO:It would probably be a good idea to
           validate file before accepting it. */
        /* fill variables from header fields */
        for (i = 0; i < 512; i++) {
                if (header[i] == ':' && i > 1) {
                        var[0] = header[i - 2];
                        var[1] = header[i - 1];
                        var[2] = '\0';
                        valpos = i + 1;
                        for (i++; i < 512; i++) {
                                /* don't accept : without CR because there's a bug below: i-valpos must be > 0 which is not the case if the : is before the third character. */
                                if (header[i] == 13 /*||header[i]==':' */ ) {   /* 0x0d = carriage return */
                                        /* : indicates another variable, CR was missing! */
                                        if (header[i] == ':') {
                                                i -= 2;
                                        }
                                        /* TODO: used to be strncpy, make sure this is a safe substitution. */
                                        memcpy(val, &header[valpos],
                                               (size_t)(i - valpos));
                                        val[i - valpos] = '\0';
                                        set_dst_variable(pattern, var, val);
                                        break;
                                }
                        }
                }
        }

        while (fread(b, 1, 3, file) == 3) {
                int x, y;
                decode_tajima_ternary(b, &x, &y);
                flags = decode_record_flags(b[2]);
                if (flags == END) {
                        break;
                }
                embp_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        }

        /* combine_jump_stitches(pattern, 5); */
        return 1;
}

char writeDst(EmbPattern *pattern, FILE *file)
{
        EmbRect boundingRect;
        int i, ax, ay, mx, my;
        EmbVector pos;
        EmbString pd;

        embp_correctForMaxStitchLength(pattern, 12.1f, 12.1f);

        /* TODO: make sure that pattern->thread_list->count
         * defaults to 1 in new patterns */
        boundingRect = embp_bounds(pattern);
        /* TODO: review the code below
           if (pattern->get_variable("design_name") != NULL) {
           char *la = stralloccopy(pattern->get_variable("design_name"));
           if (strlen(la)>16) la[16]='\0';

           fprintf(file,"LA:%-16s\x0d",la);
           safe_free(la);
           }
         */
        fprintf(file, "LA:%-16s\x0d", "Untitled");
        fprintf(file, "ST:%7d\x0d", pattern->stitch_list->count);
        /* number of color changes, not number of colors! */
        fprintf(file, "CO:%3d\x0d", pattern->thread_list->count - 1);
        fprintf(file,
                "+X:%5d\x0d"
                "-X:%5d\x0d"
                "+Y:%5d\x0d"
                "-Y:%5d\x0d",
                (int)((boundingRect.x + boundingRect.w) * 10.0),
                (int)(fabs(boundingRect.x) * 10.0),
                (int)((boundingRect.y + boundingRect.h) * 10.0),
                (int)(fabs(boundingRect.y) * 10.0));

        ax = ay = mx = my = 0;
        /* TODO: review the code below */
        /*ax=pattern->get_variable_int("ax"); *//* will return 0 if not defined */
        /*ay=pattern->get_variable_int("ay"); */
        /*mx=pattern->get_variable_int("mx"); */
        /*my=pattern->get_variable_int("my"); */

        /*pd=pattern->get_variable("pd"); *//* will return null pointer if not defined */
        /* pd = 0;
           if (pd == 0 || strlen(pd) != 6) { */
        /* pd is not valid, so fill in a default consisting of "******" */
        strcpy(pd, "******");
        /*} */
        fprintf(file,
                "AX:+%5d\x0d"
                "AY:+%5d\x0d"
                "MX:+%5d\x0d"
                "MY:+%5d\x0d" "PD:%6s\x0d\x1a", ax, ay, mx, my, pd);

        /* pad out header to proper length */
        fpad(file, ' ', 512 - 125);

        /* write stitches */
        pos.x = 0.0;
        pos.y = 0.0;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch st;
                int dx, dy;
                st = pattern->stitch_list->stitch[i];
                /* convert from mm to 0.1mm for file format */
                dx = (int)emb_round(10.0f * (st.x - pos.x));
                dy = (int)emb_round(10.0f * (st.y - pos.y));
                pos.x += 0.1f * dx;
                pos.y += 0.1f * dy;
                if (emb_verbose > 0) {
                        printf("%d %f %f %d %d %f %f %d\n", i, st.x, st.y, dx,
                               dy, pos.x, pos.y, st.flags);
                }
                encode_record(file, dx, dy, st.flags);
        }

        /* Finish file with a terminator character and two zeros to
         * keep the post header part a multiple of three.
         */
        fwrite("\xa1\0\0", 1, 3, file);
        return 1;
}

/* Embird Embroidery Format (.edr)
 * Stitch Only Format
 */
char readEdr(EmbPattern *pattern, FILE *file)
{
        /* appears identical to readRgb, so backends to that */
        return readRgb(pattern, file);
}

char writeEdr(EmbPattern *pattern, FILE *file)
{
        /* appears identical to writeRgb, so backends to that */
        return writeRgb(pattern, file);
}

/* The Elna Embroidery Format (.emd)
 * Stitch Only Format.
 */

char emdDecode(unsigned char inputByte)
{
        if (inputByte >= 0x80) {
                return (-~inputByte) - 1;
        }
        return inputByte;
}

/* . */
char readEmd(EmbPattern *pattern, FILE *file)
{
        unsigned char b[2];
        unsigned char jemd0[6]; /* TODO: more descriptive name */
        int width, height, colors, length;

        fseek(file, 0, SEEK_END);
        length = ftell(file);
        if (length < 0x30) {
                puts("File invalid: shorter than the header.");
                return 0;
        }
        fseek(file, 0, SEEK_SET);

        if (fread(jemd0, 1, 6, file) != 6) {
                puts("ERROR: Failed to read 6 bytes for jemd0");
                return 0;
        }
        width = emb_read_i16(file);
        height = emb_read_i16(file);
        colors = emb_read_i16(file);
        printf("%d %d %d\n", width, height, colors);

        fseek(file, 0x30, SEEK_SET);

        while (!feof(file)) {
                char dx, dy;
                int flags = NORMAL;
                if (fread(b, 1, 2, file) != 2) {
                        puts("ERROR: Failed to read 2 bytes for stitch.");
                        return 0;
                }

                if (b[0] == 0x80) {
                        if (b[1] == 0x2A) {
                                embp_addStitchRel(pattern, 0, 0, STOP, 1);
                                continue;
                        } else if (b[1] == 0x80) {
                                if (fread(b, 1, 2, file) != 2) {
                                        puts("ERROR: Failed to read 2 bytes for stitch.");
                                        return 0;
                                }
                                flags = TRIM;
                        } else if (b[1] == 0xFD) {
                                embp_addStitchRel(pattern, 0, 0, END, 1);
                                break;
                        } else {
                                continue;
                        }
                }
                dx = emdDecode(b[0]);
                dy = emdDecode(b[1]);
                embp_addStitchRel(pattern, dx / 10.0f, dy / 10.0f, flags, 1);
        }
        return 1;
}

char writeEmd(EmbPattern *pattern, FILE *file)
{
        puts("writeEmd not implemented.");
        if (emb_verbose > 1) {
                printf("Called with %p %p\n", (void *)pattern, (void *)file);
        }
        return 0;               /*TODO: finish writeEmd */
}

/* Fortron Embroidery Format (.fxy)
 * Stitch Only Format.
 */
char readFxy(EmbPattern *pattern, FILE *file)
{
        /* TODO: review for combining code. This line appears
           to be the only difference from the GT format. */
        fseek(file, 0x100, SEEK_SET);

        while (!feof(file)) {
                int stitchType = NORMAL;
                int b1 = fgetc(file);
                int b2 = fgetc(file);
                unsigned char commandByte = (unsigned char)fgetc(file);

                if (commandByte == 0x91) {
                        embp_addStitchRel(pattern, 0, 0, END, 1);
                        break;
                }
                if ((commandByte & 0x01) == 0x01)
                        stitchType = TRIM;
                if ((commandByte & 0x02) == 0x02)
                        stitchType = STOP;
                if ((commandByte & 0x20) == 0x20)
                        b1 = -b1;
                if ((commandByte & 0x40) == 0x40)
                        b2 = -b2;
                embp_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
        }
        return 1;
}

char writeFxy(EmbPattern *pattern, FILE *file)
{
        puts("Overridden, defaulting to dst.");
        printf("%p %p\n", pattern, file);
        return 0;               /*TODO: finish writeFxy */
}

/* Husqvarna Viking Embroidery Format (.hus)
 *
 * Stitch Only Format.
 */
int husDecodeStitchType(unsigned char b)
{
        switch (b) {
        case 0x80:
                return NORMAL;
        case 0x81:
                return JUMP;
        case 0x84:
                return STOP;
        case 0x90:
                return END;
        default:
                return NORMAL;
        }
}

unsigned char *husDecompressData(unsigned char *input,
                                 int compressedInputLength,
                                 int decompressedContentLength)
{
        char *decompressedData =
            (char *)malloc(sizeof(char) * decompressedContentLength);
        if (!decompressedData) {
                printf
                    ("ERROR: husDecompressData(), cannot allocate memory for decompressedData\n");
                return 0;
        }
        hus_decompress((char *)input, compressedInputLength, decompressedData,
                       &decompressedContentLength);
        return (unsigned char *)decompressedData;
}

unsigned char *husCompressData(unsigned char *input, int decompressedInputSize,
                               int *compressedSize)
{
        char *compressedData =
            (char *)malloc(sizeof(char) * decompressedInputSize * 2);
        if (!compressedData) {
                printf
                    ("ERROR: husCompressData(), cannot allocate memory for compressedData\n");
                return 0;
        }
        hus_compress((char *)input, decompressedInputSize, compressedData,
                     compressedSize);
        return (unsigned char *)compressedData;
}

int husDecodeByte(unsigned char b)
{
        return (char)b;
}

unsigned char husEncodeByte(EmbReal f)
{
        return (unsigned char)(int)emb_round(f);
}

unsigned char husEncodeStitchType(int st)
{
        switch (st) {
        case NORMAL:
                return (0x80);
        case JUMP:
        case TRIM:
                return (0x81);
        case STOP:
                return (0x84);
        case END:
                return (0x90);
        default:
                return (0x80);
        }
}

char readHus(EmbPattern *pattern, FILE *file)
{
        int fileLength;
        int magicCode, numberOfStitches, numberOfColors;
        int positiveXHoopSize, positiveYHoopSize, negativeXHoopSize,
            negativeYHoopSize;
        int attributeOffset, xOffset, yOffset;
        unsigned char *attributeData, *xData, *yData;
        unsigned char *attributeDataDecompressed = 0;
        unsigned char *xDecompressed = 0;
        unsigned char *yDecompressed = 0;
        unsigned char *stringVal = 0;

        int unknown, i = 0;

        fseek(file, 0x00, SEEK_END);
        fileLength = ftell(file);
        fseek(file, 0x00, SEEK_SET);

        magicCode = emb_read_i32(file);
        numberOfStitches = emb_read_i32(file);
        numberOfColors = emb_read_i32(file);

        /* These should be put in the EmbPattern. */
        positiveXHoopSize = emb_read_i16(file);
        positiveYHoopSize = emb_read_i16(file);
        negativeXHoopSize = emb_read_i16(file);
        negativeYHoopSize = emb_read_i16(file);

        attributeOffset = emb_read_i32(file);
        xOffset = emb_read_i32(file);
        yOffset = emb_read_i32(file);

        REPORT_INT(magicCode)
            REPORT_INT(numberOfStitches)
            REPORT_INT(numberOfColors)
            REPORT_INT(positiveXHoopSize)
            REPORT_INT(positiveYHoopSize)
            REPORT_INT(negativeXHoopSize)
            REPORT_INT(negativeYHoopSize)
            REPORT_INT(attributeOffset)
            REPORT_INT(xOffset)
            REPORT_INT(yOffset)
            stringVal = (unsigned char *)malloc(sizeof(unsigned char) * 8);
        if (!stringVal) {
                printf
                    ("ERROR: format-hus.c readHus(), cannot allocate memory for stringVal\n");
                return 0;
        }
        size_t size = 8;
        if (fread(stringVal, 1, size, file) != size) {
                puts("Ran out of bytes before full file read.");
                return 0;
        }

        unknown = emb_read_i16(file);
        printf("unknown: %d\n", unknown);
        for (i = 0; i < numberOfColors; i++) {
                short pos = emb_read_i16(file);
                embp_addThread(pattern, hus_colors[pos]);
        }

        attributeData =
            (unsigned char *)malloc(sizeof(unsigned char) *
                                    (xOffset - attributeOffset + 1));
        if (!attributeData) {
                printf
                    ("ERROR: format-hus.c readHus(), cannot allocate memory for attributeData\n");
                return 0;
        }
        size = xOffset - attributeOffset;
        if (fread(attributeData, 1, size, file) != size) {
                puts("Ran out of bytes before full file read.");
                return 0;
        }
        attributeDataDecompressed =
            husDecompressData(attributeData, size, numberOfStitches + 1);

        xData =
            (unsigned char *)malloc(sizeof(unsigned char) *
                                    (yOffset - xOffset + 1));
        if (!xData) {
                printf
                    ("ERROR: format-hus.c readHus(), cannot allocate memory for xData\n");
                return 0;
        }
        size = yOffset - xOffset;
        if (fread(xData, 1, size, file) != size) {
                puts("Ran out of bytes before full file read.");
                return 0;
        }
        xDecompressed = husDecompressData(xData, size, numberOfStitches);

        yData =
            (unsigned char *)malloc(sizeof(unsigned char) *
                                    (fileLength - yOffset + 1));
        if (!yData) {
                printf
                    ("ERROR: format-hus.c readHus(), cannot allocate memory for yData\n");
                return 0;
        }
        size = fileLength - yOffset;
        if (fread(yData, 1, size, file) != size) {
                puts("Ran out of bytes before full file read.");
                return 0;
        }
        yDecompressed = husDecompressData(yData, size, numberOfStitches);

        for (i = 0; i < numberOfStitches; i++) {
                int flag;
                EmbVector v;
                v.x = husDecodeByte(xDecompressed[i]) / 10.0;
                v.y = husDecodeByte(yDecompressed[i]) / 10.0;
                flag = husDecodeStitchType(attributeDataDecompressed[i]);
                embp_addStitchRel(pattern, v.x, v.y, flag, 1);
        }

        safe_free(stringVal);
        safe_free(xData);
        safe_free(xDecompressed);
        safe_free(yData);
        safe_free(yDecompressed);
        safe_free(attributeData);
        safe_free(attributeDataDecompressed);

        return 1;
}

char writeHus(EmbPattern *pattern, FILE *file)
{
        EmbRect boundingRect;
        int stitchCount, minColors, patternColor, attributeSize,
            xCompressedSize, yCompressedSize, i;
        EmbReal previousX, previousY;
        short right, top, bottom, left;
        unsigned int code, colors, offset1, offset2;
        unsigned char *xValues = 0, *yValues = 0, *attributeValues = 0,
            *attributeCompressed = 0, *xCompressed = 0, *yCompressed = 0;

        stitchCount = pattern->stitch_list->count;
        /* embp_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */
        minColors = pattern->thread_list->count;
        patternColor = minColors;
        if (minColors > 24)
                minColors = 24;
        code = 0x00C8AF5B;
        emb_write_i32(file, code);
        emb_write_i32(file, stitchCount);
        emb_write_i32(file, minColors);

        boundingRect = embp_bounds(pattern);
        right = (int16_t) emb_round((boundingRect.w + boundingRect.x) * 10.0);
        top = (int16_t) - emb_round(boundingRect.y * 10.0);
        left = (int16_t) emb_round(boundingRect.x * 10.0);
        bottom =
            (int16_t) - emb_round((boundingRect.h + boundingRect.y) * 10.0);
        emb_write_i16(file, right);
        emb_write_i16(file, top);
        emb_write_i16(file, left);
        emb_write_i16(file, bottom);

        colors = 0x2A + 2 * minColors;
        emb_write_i32(file, colors);

        xValues =
            (unsigned char *)malloc(sizeof(unsigned char) * (stitchCount));
        if (!xValues) {
                printf
                    ("ERROR: format-hus.c writeHus(), cannot allocate memory for xValues\n");
                return 0;
        }
        yValues =
            (unsigned char *)malloc(sizeof(unsigned char) * (stitchCount));
        if (!yValues) {
                printf
                    ("ERROR: format-hus.c writeHus(), cannot allocate memory for yValues\n");
                return 0;
        }
        attributeValues =
            (unsigned char *)malloc(sizeof(unsigned char) * (stitchCount));
        if (!attributeValues) {
                printf
                    ("ERROR: format-hus.c writeHus(), cannot allocate memory for attributeValues\n");
                return 0;
        }

        previousX = 0.0;
        previousY = 0.0;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch st;
                st = pattern->stitch_list->stitch[i];
                xValues[i] = husEncodeByte((st.x - previousX) * 10.0);
                previousX = st.x;
                yValues[i] = husEncodeByte((st.y - previousY) * 10.0);
                previousY = st.y;
                attributeValues[i] = husEncodeStitchType(st.flags);
        }
        attributeCompressed =
            husCompressData(attributeValues, stitchCount, &attributeSize);
        xCompressed = husCompressData(xValues, stitchCount, &xCompressedSize);
        yCompressed = husCompressData(yValues, stitchCount, &yCompressedSize);
        /* TODO: error if husCompressData returns zero? */

        offset1 = (unsigned int)(0x2A + 2 * patternColor + attributeSize);
        offset2 =
            (unsigned int)(0x2A + 2 * patternColor + attributeSize +
                           xCompressedSize);
        emb_write_i32(file, offset1);
        emb_write_i32(file, offset2);
        fpad(file, 0, 10);

        for (i = 0; i < patternColor; i++) {
                short color_index =
                    (int16_t) emb_find_nearest_thread(pattern->
                                                      thread_list->thread[i].
                                                      color,
                                                      (EmbThread *) hus_colors,
                                                      29);
                emb_write_i16(file, color_index);
        }

        fwrite(attributeCompressed, 1, attributeSize, file);
        fwrite(xCompressed, 1, xCompressedSize, file);
        fwrite(yCompressed, 1, yCompressedSize, file);

        safe_free(xValues);
        safe_free(xCompressed);
        safe_free(yValues);
        safe_free(yCompressed);
        safe_free(attributeValues);
        safe_free(attributeCompressed);

        return 1;
}

/*
 * Inbro Embroidery Format (.inb)
 * Stitch Only Format.
 */
char readInb(EmbPattern *pattern, FILE *file)
{
        /* TODO: determine what this represents */
        unsigned char fileDescription[8], nullVal, bytesUnknown[300];
        int stitchCount, x, y, i, fileLength;
        short width, height, colorCount, unknown3, unknown2,
            nullbyte, left, right, top, bottom, imageWidth, imageHeight;

        fseek(file, 0, SEEK_END);
        fileLength = ftell(file);
        fread(fileDescription, 1, 8, file);     /* TODO: check return value */
        LOAD_U8(file, nullVal)
            fgetc(file);
        fgetc(file);
        LOAD_I32(file, stitchCount)
            LOAD_I16(file, width)
            LOAD_I16(file, height)
            LOAD_I16(file, colorCount)
            LOAD_I16(file, unknown3)
            LOAD_I16(file, unknown2)
            LOAD_I16(file, imageWidth)
            LOAD_I16(file, imageHeight)
            fread(bytesUnknown, 1, 300, file);  /* TODO: check return value */
        LOAD_I16(file, nullbyte)
            LOAD_I16(file, left)
            LOAD_I16(file, right)
            LOAD_I16(file, top)
            LOAD_I16(file, bottom)
            fseek(file, 0x2000, SEEK_SET);
        /* Calculate stitch count since header has been seen to be blank */
        stitchCount = (int)((fileLength - 0x2000) / 3);
        for (i = 0; i < stitchCount; i++) {
                unsigned char type;
                int stitch = NORMAL;
                x = (char)fgetc(file);
                y = (char)fgetc(file);
                type = (char)fgetc(file);
                if ((type & 0x40) > 0)
                        x = -x;
                if ((type & 0x10) > 0)
                        y = -y;
                if ((type & 1) > 0)
                        stitch = STOP;
                if ((type & 2) > 0)
                        stitch = TRIM;
                embp_addStitchRel(pattern, x / 10.0, y / 10.0, stitch, 1);
        }
        embp_flipVertical(pattern);

        return 1;
}

char writeInb(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: writeInb not implemented.");
        REPORT_PTR(pattern)
            REPORT_PTR(file)
            return 0;           /*TODO: finish writeInb */
}

/* Mitsubishi Embroidery Format (.mit)
 *
 * Stitch Only Format.
 */
char readMit(EmbPattern *pattern, FILE *file)
{
        unsigned char data[2];

        while (fread(data, 1, 2, file) == 2) {
                int x = mitDecodeStitch(data[0]);
                int y = mitDecodeStitch(data[1]);
                embp_addStitchRel(pattern, x / 10.0, y / 10.0, NORMAL, 1);
        }
        return 1;
}

char writeMit(EmbPattern *pattern, FILE *file)
{
        EmbReal xx, yy;
        int i;

        embp_correctForMaxStitchLength(pattern, 0x1F, 0x1F);
        xx = 0;
        yy = 0;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                unsigned char b[2];
                EmbStitch st = pattern->stitch_list->stitch[i];
                b[0] = mitEncodeStitch(st.x - xx);
                b[1] = mitEncodeStitch(st.y - yy);
                xx = st.x;
                yy = st.y;
                fwrite(b, 1, 2, file);
        }
        return 1;
}

/* Ameco Embroidery Format (.new)
 *
 * Stitch Only Format.
 */
char readNew(EmbPattern *pattern, FILE *file)
{
        unsigned int stitchCount;
        unsigned char data[3];

        LOAD_I16(file, stitchCount)
            while (fread(data, 1, 3, file) == 3) {
                int x = decodeNewStitch(data[0]);
                int y = decodeNewStitch(data[1]);
                int flag = NORMAL;
                char val = data[2];
                if (data[2] & 0x40) {
                        x = -x;
                }
                if (data[2] & 0x20) {
                        y = -y;
                }
                if (data[2] & 0x10) {
                        flag = TRIM;
                }
                if (data[2] & 0x01) {
                        flag = JUMP;
                }
                if ((val & 0x1E) == 0x02) {
                        flag = STOP;
                }
                /* Unknown values, possibly TRIM
                   155 = 1001 1011 = 0x9B
                   145 = 1001 0001 = 0x91
                 */
                /*val = (data[2] & 0x1C);
                   if (val != 0 && data[2] != 0x9B && data[2] != 0x91) {
                   int z = 1;
                   } */
                embp_addStitchRel(pattern, x / 10.0, y / 10.0, flag, 1);
        }

        return 1;
}

/* . */
char writeNew(EmbPattern *pattern, FILE *file)
{
        puts("Overridden, defaulting to dst.");
        writeDst(pattern, file);
        return 0;               /*TODO: finish writeNew */
}

/* Melco Embroidery Format (.ofm)
 *
 * Stitch Only Format.
 */
char *ofmReadLibrary(FILE *file)
{
        int stringLength = 0;
        char *libraryName = 0;
        /* FF FE FF */
        unsigned char leadIn[3];

        if (!file) {
                printf
                    ("ERROR: format-ofm.c ofmReadLibrary(), file argument is null\n");
                return 0;
        }

        fread(leadIn, 1, 3, file);      /* TODO: check return value */
        unsigned char a;
        fread(&a, 1, 1, file);
        stringLength = a;
        libraryName = (char *)malloc(sizeof(char) * stringLength * 2);
        if (!libraryName) {
                printf
                    ("ERROR: format-ofm.c ofmReadLibrary(), unable to allocate memory for libraryName\n");
                return 0;
        }
        fread((unsigned char *)libraryName, 1, stringLength * 2, file); /* TODO: check return value */
        return libraryName;
}

static int ofmReadClass(FILE *file)
{
        int len;
        EmbString s;

        if (!file) {
                printf
                    ("ERROR: format-ofm.c ofmReadClass(), file argument is null\n");
                return 0;
        }

        emb_read_i16(file);
        len = emb_read_i16(file);

        fread((unsigned char *)s, 1, len, file);
        /* TODO: check return value */
        s[len] = '\0';
        if (!strcmp(s, "CExpStitch")) {
                return 0x809C;
        }
        if (!strcmp(s, "CColorChange")) {
                return 0xFFFF;
        }
        return 0;
}

void ofmReadBlockHeader(FILE *file)
{
        int val[10], i;         /* TODO: determine what these represent */
        unsigned char len;
        char *s = 0;
        unsigned short short1;
        short unknown1;
        /* TODO: determine what the unknown variables represent */
        int unknown3, unknown2;
        /* TODO: determine what this represents */

        if (!file) {
                printf
                    ("ERROR: format-ofm.c ofmReadBlockHeader(), file argument is null\n");
                return;
        }

        LOAD_I16(file, unknown1)
            LOAD_I32(file, unknown2)
            LOAD_I32(file, unknown3)
            /* int v = fread(&v, 1, 3, file)?; TODO: review */
            emb_read_i16(file);
        fseek(file, 1, SEEK_CUR);
        len = (char)fgetc(file);
        s = (char *)malloc(2 * len);
        if (!s) {
                printf
                    ("ERROR: format-ofm.c ofmReadBlockHeader(), unable to allocate memory for s\n");
                return;
        }
        fread((unsigned char *)s, 1, 2 * len, file);
        /* TODO: check return value */
        /* 0, 0, 0, 0, 1, 1, 1, 0, 64, 64 */
        for (i = 0; i < 10; i++) {
                val[i] = emb_read_i32(file);
                printf("%d", val[i]);
        }
        LOAD_I16(file, short1)  /*  0 */
}

/* . */
void ofmReadColorChange(FILE *file, EmbPattern *pattern)
{
        if (!file) {
                printf
                    ("ERROR: format-ofm.c ofmReadColorChange(), file argument is null\n");
                return;
        }
        if (!pattern) {
                printf
                    ("ERROR: format-ofm.c ofmReadColorChange(), pattern argument is null\n");
                return;
        }

        ofmReadBlockHeader(file);
        embp_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
}

void ofmReadThreads(FILE *file, EmbPattern *p)
{
        int i, numberOfColors, stringLen, numberOfLibraries;
        char *primaryLibraryName = 0;
        char *expandedString = 0;

        if (!file) {
                printf("ERROR: ofm_read_threads(), file argument is null\n");
                return;
        }
        if (!p) {
                printf("ERROR: ofm_read_threads(), p argument is null\n");
                return;
        }

        /* FF FE FF 00 */
        fseek(file, 4, SEEK_CUR);

        numberOfColors = emb_read_i16(file);

        fseek(file, 4, SEEK_CUR);
        stringLen = emb_read_i16(file);
        expandedString = (char *)malloc(stringLen);
        if (!expandedString) {
                printf
                    ("ERROR: format-ofm.c ofm_read_threads(), unable to allocate memory for expandedString\n");
                return;
        }
        fread((unsigned char *)expandedString, 1, stringLen, file);
        /* TODO: check return value */
        for (i = 0; i < numberOfColors; i++) {
                EmbThread thread;
                char colorNumberText[11], colorName[512];
                int threadLibrary, colorNameLength, colorNumber;
                embColor_read(file, &(thread.color), 4);
                LOAD_I16(file, threadLibrary)
                    fseek(file, 2, SEEK_CUR);
                LOAD_I32(file, colorNumber)
                    fseek(file, 3, SEEK_CUR);
                LOAD_I8(file, colorNameLength)
                    fread(colorName, 1, colorNameLength * 2, file);
                /* TODO: check return value */
                fseek(file, 2, SEEK_CUR);
                sprintf(colorNumberText, "%10d", colorNumber);
                strcpy(thread.catalogNumber, colorNumberText);
                strcpy(thread.description, colorName);
                embp_addThread(p, thread);
        }
        fseek(file, 2, SEEK_CUR);
        primaryLibraryName = ofmReadLibrary(file);
        numberOfLibraries = emb_read_i16(file);

        if (emb_verbose > 1) {
                printf("primary library name: %s\n", primaryLibraryName);
        }

        for (i = 0; i < numberOfLibraries; i++) {
                /*libraries.Add( TODO: review */
                char *libName = ofmReadLibrary(file);
                safe_free(libName);
        }
}

EmbReal ofmDecode(unsigned char b1, unsigned char b2)
{
        EmbReal val = (EmbReal) (int16_t) (b1 << 8 | b2);
        return val;
}

void ofmReadExpanded(FILE *file, EmbPattern *p)
{
        int i, numberOfStitches = 0;

        if (!file) {
                printf
                    ("ERROR: format-ofm.c ofmReadExpanded(), file argument is null\n");
                return;
        }
        if (!p) {
                printf
                    ("ERROR: format-ofm.c ofmReadExpanded(), p argument is null\n");
                return;
        }

        ofmReadBlockHeader(file);
        numberOfStitches = emb_read_i32(file);

        for (i = 0; i < numberOfStitches; i++) {
                unsigned char stitch[5];
                fread(stitch, 1, 5, file);      /* TODO: check return value */
                if (stitch[0] == 0) {
                        EmbReal x = ofmDecode(stitch[1], stitch[2]) / 10.0;
                        EmbReal y = ofmDecode(stitch[3], stitch[4]) / 10.0;
                        embp_addStitchAbs(p, x, y, i == 0 ? JUMP : NORMAL, 1);
                } else if (stitch[0] == 32) {
                        EmbReal x = ofmDecode(stitch[1], stitch[2]) / 10.0;
                        EmbReal y = ofmDecode(stitch[3], stitch[4]) / 10.0;
                        embp_addStitchAbs(p, x, y, i == 0 ? TRIM : NORMAL, 1);
                }
        }
}

char readOfm(EmbPattern *pattern, FILE *fileCompound)
{
        int unknownCount, key = 0, classNameLength;
        char *s = 0;
        FILE *file;
        bcf_file *bcfFile = 0;

        if (emb_verbose > 1) {
                puts("Overridden during development.");
                return 0;
        }

        bcfFile = (bcf_file *) malloc(sizeof(bcf_file));
        if (!bcfFile) {
                printf
                    ("ERROR: format-ofm.c readOfm(), unable to allocate memory for bcfFile\n");
                return 0;
        }
        bcfFile_read(fileCompound, bcfFile);
        file = GetFile(bcfFile, fileCompound, "EdsIV Object");
        bcf_file_free(bcfFile);
        bcfFile = 0;
        fseek(file, 0x1C6, SEEK_SET);
        ofmReadThreads(file, pattern);
        fseek(file, 0x110, SEEK_CUR);
        fseek(file, 0x4, SEEK_CUR);     /* EMB_INT32_LITTLE */
        classNameLength = emb_read_i16(file);
        s = (char *)malloc(sizeof(char) * classNameLength);
        if (!s) {
                printf
                    ("ERROR: format-ofm.c readOfm(), unable to allocate memory for s\n");
                return 0;
        }
        fread((unsigned char *)s, 1, classNameLength, file);    /* TODO: check return value */
        unknownCount = emb_read_i16(file);
        /* TODO: determine what unknown count represents */
        if (emb_verbose > 1) {
                printf("unknownCount = %d\n", unknownCount);
        }

        emb_read_i16(file);
        key = ofmReadClass(file);
        while (1) {
                if (key == 0xFEFF) {
                        break;
                }
                if (key == 0x809C) {
                        ofmReadExpanded(file, pattern);
                } else {
                        ofmReadColorChange(file, pattern);
                }
                LOAD_U16(file, key)
                    if (key == 0xFFFF) {
                        ofmReadClass(file);
                }
        }

        embp_flip(pattern, 1, 1);

        return 1;
}

char writeOfm(EmbPattern *pattern, FILE *file)
{
        puts("Overridden, defaulting to dst.");
        writeDst(pattern, file);
        return 0;               /*TODO: finish writeOfm */
}

/* Pfaff PCD File Format (.pcd)
 *
 * Stitch Only Format.
 *
 * The format uses a signed 3 byte-length number type.
 *
 * See the description here ([5](5)) for the overview of the format.
 *
 * For an example of the format see ([11](11)).
 *
 */
char readPcd(EmbPattern *pattern, const char *fileName, FILE *file)
{
        char allZeroColor = 1;
        int i = 0;
        unsigned char b[9];
        EmbReal dx = 0, dy = 0;
        int st = 0;
        unsigned char version, hoopSize;
        unsigned short colorCount = 0;

        version = (char)fgetc(file);
        /* 0 for PCD
         * 1 for PCQ (MAXI)
         * 2 for PCS with small hoop(80x80)
         * 3 for PCS with large hoop (115x120)
         */
        hoopSize = (char)fgetc(file);
        LOAD_U16(file, colorCount)
            if (emb_verbose > 1) {
                printf("version: %d\n", version);
                printf("hoop size: %d\n", hoopSize);
        }

        for (i = 0; i < colorCount; i++) {
                EmbThread t;
                embColor_read(file, &(t.color), 4);
                strcpy(t.catalogNumber, "");
                strcpy(t.description, "");
                if (t.color.r || t.color.g || t.color.b) {
                        allZeroColor = 0;
                }
                embp_addThread(pattern, t);
        }
        if (allZeroColor) {
                embp_loadExternalColorFile(pattern, fileName);
        }
        LOAD_U16(file, st)
            /* READ STITCH RECORDS */
            for (i = 0; i < st; i++) {
                int flags;
                if (fread(b, 1, 9, file) != 9) {
                        break;
                }
                flags = NORMAL;
                if (b[8] & 0x01) {
                        flags = STOP;
                } else if (b[8] & 0x04) {
                        flags = TRIM;
                } else if (b[8] != 0) {
                        /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
                }
                dx = pfaffDecode(b[1], b[2], b[3]);
                dy = pfaffDecode(b[5], b[6], b[7]);
                embp_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }
        return 1;
}

char writePcd(EmbPattern *pattern, FILE *file)
{
        int i;

        /* TODO: select hoop size defaulting to Large PCS hoop */
        fwrite("2\x03", 1, 2, file);
        emb_write_u16(file, (unsigned short)pattern->thread_list->count);
        for (i = 0; i < pattern->thread_list->count; i++) {
                EmbColor color = pattern->thread_list->thread[i].color;
                embColor_write(file, color, 4);
        }

        fpad(file, 0, 4 * (16 - i));
        /* write remaining colors to reach 16 */

        emb_write_u16(file, (unsigned short)pattern->stitch_list->count);
        /* write stitches */
        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch st = pattern->stitch_list->stitch[i];
                pfaffEncode(file, (int)emb_round(st.x * 10.0),
                            (int)emb_round(st.y * 10.0), st.flags);
        }
        return 1;
}

/*
 * Pfaff Embroidery Format (.pcm)
 *
 * The Pfaff pcm format is stitch-only.
 */
char readPcm(EmbPattern *pattern, FILE *file)
{
        int i = 0, st;
        EmbReal dx = 0, dy = 0;
        int header_size = 16 * 2 + 6;

        if (emb_verbose > 1) {
                printf("TODO: check header_size %d\n", header_size);
        }

        fseek(file, 4, SEEK_SET);
        for (i = 0; i < 16; i++) {
                int colorNumber;
                (void)fgetc(file);      /* zero */
                colorNumber = fgetc(file);
                embp_addThread(pattern, pcm_colors[colorNumber]);
        }
        st = emb_read_i16be(file);
        st = EMB_MIN(st, MAX_STITCHES);
        /* READ STITCH RECORDS */
        for (i = 0; i < st; i++) {
                int flags;
                unsigned char b[9];
                flags = NORMAL;
                if (fread(b, 1, 9, file) != 9) {
                        break;
                }
                if (b[8] & 0x01) {
                        flags = STOP;
                } else if (b[8] & 0x04) {
                        flags = TRIM;
                } else if (b[8] != 0) {
                        /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
                }
                dx = pfaffDecode(b[2], b[1], b[0]);
                dy = pfaffDecode(b[6], b[5], b[4]);
                embp_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }
        return 1;
}

char writePcm(EmbPattern *pattern, FILE *file)
{
        puts("overridden, defaulting to dst");
        writeDst(pattern, file);
        return 0;               /*TODO: finish writePcm */
}

/*
 * Pfaff Embroidery Format (.pcq)
 *
 * The Pfaff pcq format is stitch-only.
 */
char readPcq(EmbPattern *pattern, const char *fileName, FILE *file)
{
        char allZeroColor = 1;
        int i = 0;
        unsigned char b[9];
        EmbReal dx = 0, dy = 0;
        int flags = 0, st = 0;
        unsigned char version, hoopSize;
        unsigned short colorCount;

        version = (char)fgetc(file);
        hoopSize = (char)fgetc(file);
        /* 0 for PCD
         * 1 for PCQ (MAXI)
         * 2 for PCS with small hoop(80x80)
         * 3 for PCS with large hoop (115x120)
         */
        LOAD_U16(file, colorCount)
            if (emb_verbose > 1) {
                printf("version: %d\n", version);
                printf("hoop size: %d\n", hoopSize);
        }

        for (i = 0; i < colorCount; i++) {
                EmbThread t;
                embColor_read(file, &(t.color), 4);
                strcpy(t.catalogNumber, "");
                strcpy(t.description, "");
                if (t.color.r || t.color.g || t.color.b) {
                        allZeroColor = 0;
                }
                embp_addThread(pattern, t);
        }
        if (allZeroColor) {
                embp_loadExternalColorFile(pattern, fileName);
        }
        LOAD_U16(file, st)
            /* READ STITCH RECORDS */
            for (i = 0; i < st; i++) {
                flags = NORMAL;
                if (fread(b, 1, 9, file) != 9) {
                        break;
                }

                if (b[8] & 0x01) {
                        flags = STOP;
                } else if (b[8] & 0x04) {
                        flags = TRIM;
                } else if (b[8] != 0) {
                        /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
                }
                dx = pfaffDecode(b[1], b[2], b[3]);
                dy = pfaffDecode(b[5], b[6], b[7]);
                embp_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }
        return 1;
}

char writePcq(EmbPattern *pattern, FILE *file)
{
        int i;

        /* TODO: select hoop size defaulting to Large PCS hoop */
        fwrite("2\x03", 1, 2, file);
        emb_write_u16(file, (unsigned short)pattern->thread_list->count);
        for (i = 0; i < pattern->thread_list->count; i++) {
                EmbColor color = pattern->thread_list->thread[i].color;
                embColor_write(file, color, 4);
        }

        /* write remaining colors to reach 16 */
        fpad(file, 0, (16 - i) * 4);

        emb_write_u16(file, (unsigned short)pattern->stitch_list->count);
        /* write stitches */
        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch st = pattern->stitch_list->stitch[i];
                pfaffEncode(file, (int)emb_round(st.x * 10.0),
                            (int)emb_round(st.y * 10.0), st.flags);
        }
        return 1;
}

/*
 * Pfaff Embroidery Format (.pcs)
 *
 * The Pfaff pcs format is stitch-only.
 */
char readPcs(EmbPattern *pattern, const char *fileName, FILE *file)
{
        char allZeroColor = 1;
        int i = 0;
        unsigned char b[9];
        EmbReal dx = 0, dy = 0;
        int flags = 0, st = 0;
        unsigned char version, hoopSize;
        unsigned short colorCount;

        version = (char)fgetc(file);

        /* 0 for PCD
         * 1 for PCQ (MAXI)
         * 2 for PCS with small hoop(80x80)
         * 3 for PCS with large hoop (115x120)
         */
        hoopSize = (char)fgetc(file);
        switch (hoopSize) {
        case 2:
                pattern->hoop_width = 80.0;
                pattern->hoop_height = 80.0;
                break;
        case 3:
                pattern->hoop_width = 115.0;
                pattern->hoop_height = 120.0;
                break;
        }

        LOAD_U16(file, colorCount)
            if (emb_verbose > 1) {
                printf("version: %d\n", version);
                printf("hoop size: %d\n", hoopSize);
                printf("color count: %d\n", colorCount);
        }

        for (i = 0; i < colorCount; i++) {
                EmbThread t;
                embColor_read(file, &(t.color), 4);
                strcpy(t.catalogNumber, "");
                strcpy(t.description, "");
                if (t.color.r || t.color.g || t.color.b) {
                        allZeroColor = 0;
                }
                embp_addThread(pattern, t);
        }
        if (allZeroColor) {
                embp_loadExternalColorFile(pattern, fileName);
        }
        LOAD_U16(file, st)
            /* READ STITCH RECORDS */
            for (i = 0; i < st; i++) {
                flags = NORMAL;
                if (fread(b, 1, 9, file) != 9)
                        break;

                if (b[8] & 0x01) {
                        flags = STOP;
                } else if (b[8] & 0x04) {
                        flags = TRIM;
                } else if (b[8] != 0) {
                        /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
                }
                dx = pfaffDecode(b[1], b[2], b[3]);
                dy = pfaffDecode(b[5], b[6], b[7]);
                embp_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }

        return 1;
}

char writePcs(EmbPattern *pattern, FILE *file)
{
        int i;

        /* TODO: select hoop size defaulting to Large PCS hoop */
        fwrite("2\x03", 1, 2, file);
        emb_write_u16(file, (unsigned short)pattern->thread_list->count);
        for (i = 0; i < pattern->thread_list->count; i++) {
                EmbColor color = pattern->thread_list->thread[i].color;
                embColor_write(file, color, 4);
        }

        /* write remaining colors to reach 16 */
        /* fpad(file, 0, 4*(16-i)); */

        emb_write_u16(file, (unsigned short)pattern->stitch_list->count);
        /* write stitches */
        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch st = pattern->stitch_list->stitch[i];
                pfaffEncode(file, (int)emb_round(st.x * 10.0),
                            (int)emb_round(st.y * 10.0), st.flags);
        }
        return 1;
}

/*
 * AutoCAD Embroidery Format (.plt)
 * The AutoCAD plt format is stitch-only.
 */
char readPlt(EmbPattern *pattern, FILE *file)
{
        EmbReal x, y;
        EmbReal scalingFactor = 40;
        char input[512];

        /* TODO: replace all scanf code */
        while (emb_readline(file, input, 511)) {
                if (input[0] == 'P' && input[1] == 'D') {
                        /* TODO: replace all scanf code */
                        if (sscanf(input, "PD%f,%f;", &x, &y) < 2) {
                                break;
                        }
                        embp_addStitchAbs(pattern, x / scalingFactor,
                                          y / scalingFactor, NORMAL, 1);
                } else if (input[0] == 'P' && input[1] == 'U') {
                        /* TODO: replace all scanf code */
                        if (sscanf(input, "PU%f,%f;", &x, &y) < 2) {
                                break;
                        }
                        embp_addStitchAbs(pattern, x / scalingFactor,
                                          y / scalingFactor, STOP, 1);
                }
        }
        return 1;
}

char writePlt(EmbPattern *pattern, FILE *file)
{
        /* TODO: pointer safety */
        EmbReal scalingFactor = 40;
        char firstStitchOfBlock = 1;
        int i;

        fprintf(file, "IN;");
        fprintf(file, "ND;");

        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch stitch;
                stitch = pattern->stitch_list->stitch[i];
                if (stitch.flags & STOP) {
                        firstStitchOfBlock = 1;
                }
                if (firstStitchOfBlock) {
                        fprintf(file, "PU%f,%f;", stitch.x * scalingFactor,
                                stitch.y * scalingFactor);
                        fprintf(file, "ST0.00,0.00;");
                        fprintf(file, "SP0;");
                        fprintf(file, "HT0;");
                        fprintf(file, "HS0;");
                        fprintf(file, "TT0;");
                        fprintf(file, "TS0;");
                        firstStitchOfBlock = 0;
                } else {
                        fprintf(file, "PD%f,%f;", stitch.x * scalingFactor,
                                stitch.y * scalingFactor);
                }
        }
        fprintf(file, "PU0.0,0.0;");
        fprintf(file, "PU0.0,0.0;");
        return 1;               /*TODO: finish WritePlt */
}

/*
 * RGB Color File (.rgb)
 * The RGB format is a color-only format to act as an external color file for other formats.
 */
char readRgb(EmbPattern *pattern, FILE *file)
{
        int i, numberOfColors;

        fseek(file, 0x00, SEEK_END);
        numberOfColors = ftell(file) / 4;

        pattern->thread_list->count = 0;

        printf("numberOfColors: %d\n", numberOfColors);

        fseek(file, 0x00, SEEK_SET);
        for (i = 0; i < numberOfColors; i++) {
                EmbThread t;
                embColor_read(file, &(t.color), 4);
                strcpy(t.catalogNumber, "");
                strcpy(t.description, "");
                embp_addThread(pattern, t);
        }
        return 1;
}

char writeRgb(EmbPattern *pattern, FILE *file)
{
        int i;
        for (i = 0; i < pattern->thread_list->count; i++) {
                EmbColor c = pattern->thread_list->thread[i].color;
                embColor_write(file, c, 4);
        }
        return 1;
}

/*
 * Janome Embroidery Format (.sew)
 * The Janome sew format is stitch-only.
 */

char sewDecode(unsigned char inputByte)
{
        /* TODO: fix return statement */
        return (inputByte >=
                0x80) ? (char)(-~(inputByte - 1)) : (char)inputByte;
}

char readSew(EmbPattern *pattern, FILE *file)
{
        int i, flags, numberOfColors, fileLength;
        char dx, dy, thisStitchIsJump = 0;

        fseek(file, 0x00, SEEK_END);
        fileLength = ftell(file);
        fseek(file, 0x00, SEEK_SET);
        numberOfColors = fgetc(file);
        numberOfColors += (fgetc(file) << 8);

        for (i = 0; i < numberOfColors; i++) {
                int color = emb_read_i16(file);
                embp_addThread(pattern, jef_colors[color % 78]);
        }
        fseek(file, 0x1D78, SEEK_SET);

        for (i = 0; ftell(file) < fileLength; i++) {
                unsigned char b[2];
                fread(b, 1, 2, file);

                flags = NORMAL;
                if (thisStitchIsJump) {
                        flags = TRIM;
                        thisStitchIsJump = 0;
                }
                if (b[0] == 0x80) {
                        if (b[1] == 1) {
                                fread(b, 1, 2, file);
                                flags = STOP;
                        } else if ((b[1] == 0x02) || (b[1] == 0x04)) {
                                thisStitchIsJump = 1;
                                fread(b, 1, 2, file);
                                flags = TRIM;
                        } else if (b[1] == 0x10) {
                                break;
                        }
                }
                dx = sewDecode(b[0]);
                dy = sewDecode(b[1]);
                if (abs(dx) == 127 || abs(dy) == 127) {
                        thisStitchIsJump = 1;
                        flags = TRIM;
                }
                embp_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }
        printf("current position: %ld\n", ftell(file));
        return 1;
}

char writeSew(EmbPattern *pattern, FILE *file)
{
        int i;
        EmbReal xx = 0.0, yy = 0.0;
        emb_write_i16(file, pattern->thread_list->count);

        if (emb_verbose > 1) {
                printf("Debugging Information\n");
                printf("number of colors = %d\n", pattern->thread_list->count);
                printf("number of stitches = %d\n",
                       pattern->stitch_list->count);
        }

        for (i = 0; i < pattern->thread_list->count; i++) {
                short thr;
                EmbColor col;
                col = pattern->thread_list->thread[i].color;
                thr =
                    emb_find_nearest_thread(col, (EmbThread *) jef_colors, 79);
                emb_write_i16(file, thr);
        }
        fpad(file, 0, 0x1D78 - 2 - pattern->thread_list->count * 2);

        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch st;
                unsigned char b[4];
                char dx, dy;
                st = pattern->stitch_list->stitch[i];
                dx = (char)emb_round(10.0 * (st.x - xx));
                dy = (char)emb_round(10.0 * (st.y - yy));
                xx += 0.1 * dx;
                yy += 0.1 * dy;
                if (st.flags & STOP) {
                        b[0] = 0x80;
                        b[1] = 0x01;
                        b[2] = dx;
                        b[3] = dy;
                        fwrite(b, 1, 4, file);
                } else if (st.flags & END) {
                        b[0] = 0x80;
                        b[1] = 0x10;
                        b[2] = 0;
                        b[3] = 0;
                        fwrite(b, 1, 4, file);
                } else if ((st.flags & TRIM) || (st.flags & JUMP)) {
                        b[0] = 0x80;
                        b[1] = 2;
                        b[2] = dx;
                        b[3] = dy;
                        fwrite(b, 1, 4, file);
                } else {
                        b[0] = dx;
                        b[1] = dy;
                        fwrite(b, 1, 2, file);
                }
        }
        return 1;
}

/*
 * Husqvarna Viking Embroidery Format (.shv)
 * The Husqvarna Viking shv format is stitch-only.
 */
char shvDecode(unsigned char inputByte)
{
        if (inputByte >= 0x80) {
                return (char)-((unsigned char)((~inputByte) + 1));
        }
        return ((char)inputByte);
}

short shvDecodeShort(unsigned short inputByte)
{
        if (inputByte > 0x8000) {
                return (int16_t) - ((unsigned short)((~inputByte) + 1));
        }
        return ((int16_t) inputByte);
}

char readShv(EmbPattern *pattern, FILE *file)
{
        int i;
        char inJump = 0;
        unsigned char fileNameLength, designWidth, designHeight;
        char halfDesignWidth, halfDesignHeight, halfDesignWidth2,
            halfDesignHeight2;
        char *headerText =
            "Embroidery disk created using software licensed from Viking Sewing Machines AB, Sweden";
        char dx = 0, dy = 0;
        char numberOfColors;
        unsigned short magicCode;
        int something;
        short left, top, right, bottom;
        char something2, numberOfSections, something3;
        int stitchesPerColor[256];
        int stitchesSinceChange = 0;
        int currColorIndex = 0;
        unsigned short sx, sy;

        if (!check_header_present(file, 25)) {
                return 0;
        }

        fseek(file, strlen(headerText), SEEK_SET);
        fileNameLength = fgetc(file);
        fseek(file, fileNameLength, SEEK_CUR);
        designWidth = fgetc(file);
        designHeight = fgetc(file);
        LOAD_I8(file, halfDesignWidth)
            LOAD_I8(file, halfDesignHeight)
            LOAD_I8(file, halfDesignWidth2)
            LOAD_I8(file, halfDesignHeight2)
            if ((designHeight % 2) == 1) {
                fseek(file, ((designHeight + 1) * designWidth) / 2, SEEK_CUR);
        } else {
                fseek(file, (designHeight * designWidth) / 2, SEEK_CUR);
        }
        numberOfColors = fgetc(file);
        LOAD_U16(file, magicCode)
            fseek(file, 1, SEEK_CUR);
        LOAD_I32(file, something)
            LOAD_I16(file, left)
            LOAD_U16(file, top)
            LOAD_U16(file, right)
            LOAD_U16(file, bottom)
            LOAD_I8(file, something2)
            LOAD_I8(file, numberOfSections)
            LOAD_I8(file, something3)
            for (i = 0; i < numberOfColors; i++) {
                unsigned int stitchCount, colorNumber;
                stitchCount = emb_read_i32be(file);
                colorNumber = fgetc(file);
                embp_addThread(pattern, shv_colors[colorNumber % 43]);
                stitchesPerColor[i] = stitchCount;
                fseek(file, 9, SEEK_CUR);
        }

        fseek(file, -2, SEEK_CUR);

        for (i = 0; !feof(file); i++) {
                unsigned char b0, b1;
                int flags;
                flags = NORMAL;
                if (inJump) {
                        flags = JUMP;
                }
                b0 = fgetc(file);
                b1 = fgetc(file);
                if (stitchesSinceChange >= stitchesPerColor[currColorIndex]) {
                        embp_addStitchRel(pattern, 0, 0, STOP, 1);
                        currColorIndex++;
                        stitchesSinceChange = 0;
                }
                if (b0 == 0x80) {
                        stitchesSinceChange++;
                        if (b1 == 3) {
                                continue;
                        } else if (b1 == 0x02) {
                                inJump = 0;
                                continue;
                        } else if (b1 == 0x01) {
                                stitchesSinceChange += 2;
                                sx = fgetc(file);
                                sx = (unsigned short)(sx << 8 | fgetc(file));
                                sy = fgetc(file);
                                sy = (unsigned short)(sy << 8 | fgetc(file));
                                flags = TRIM;
                                inJump = 1;
                                embp_addStitchRel(pattern,
                                                  shvDecodeShort(sx) / 10.0,
                                                  shvDecodeShort(sy) / 10.0,
                                                  flags, 1);
                                continue;
                        }
                }
                dx = shvDecode(b0);
                dy = shvDecode(b1);
                stitchesSinceChange++;
                embp_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }
        embp_flipVertical(pattern);

        return 1;
}

char writeShv(EmbPattern *pattern, FILE *file)
{
        puts("writeShv not implemented.");
        if (emb_verbose > 1) {
                printf("Called with %p %p\n", (void *)pattern, (void *)file);
        }
        return 0;               /*TODO: finish writeShv */
}

/*
 * Sunstar Embroidery Format (.sst)
 * The Sunstar sst format is stitch-only.
 */
char readSst(EmbPattern *pattern, FILE *file)
{
        int fileLength;

        fseek(file, 0, SEEK_END);
        fileLength = ftell(file);
        fseek(file, 0xA0, SEEK_SET);    /* skip the all zero header */
        while (ftell(file) < fileLength) {
                int stitchType = NORMAL;

                int b1 = fgetc(file);
                int b2 = fgetc(file);
                unsigned char commandByte = (unsigned char)fgetc(file);

                if (commandByte == 0x04) {
                        embp_addStitchRel(pattern, 0, 0, END, 1);
                        break;
                }

                if ((commandByte & 0x01) == 0x01)
                        stitchType = STOP;
                if ((commandByte & 0x02) == 0x02)
                        stitchType = JUMP;
                if ((commandByte & 0x10) != 0x10)
                        b2 = -b2;
                if ((commandByte & 0x40) == 0x40)
                        b1 = -b1;
                embp_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
        }

        return 1;               /*TODO: finish readSst */
}

char writeSst(EmbPattern *pattern, FILE *file)
{
        int i;
        int head_length = 0xA0;
        for (i = 0; i < head_length; i++) {
                fprintf(file, " ");
        }
        for (i = 0; i < pattern->stitch_list->count; i++) {
                printf(".");
        }
        return 0;               /*TODO: finish writeSst */
}

/*
 * Data Stitch Embroidery Format (.stx)
 * The Data Stitch stx format is stitch-only.
 */
int stxReadThread(StxThread *thread, FILE *file)
{
        int j, colorNameLength, sectionNameLength;
        int somethingSomething, somethingSomething2, somethingElse, numberOfOtherDescriptors;   /* TODO: determine what these represent */
        int codeLength = 0;
        char *codeBuff = 0;
        char *codeNameBuff = 0;
        EmbColor col;
        char *sectionNameBuff = 0;

        if (!thread) {
                printf
                    ("ERROR: format-stx.c stxReadThread(), thread argument is null\n");
                return 0;
        }
        if (!file) {
                printf
                    ("ERROR: format-stx.c stxReadThread(), file argument is null\n");
                return 0;
        }

        codeLength = fgetc(file);
        codeBuff = (char *)malloc(codeLength);
        if (!codeBuff) {
                printf
                    ("ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeBuff\n");
                return 0;
        }
        /* TODO: check return value */
        fread(codeBuff, 1, codeLength, file);
        thread->colorCode = codeBuff;
        colorNameLength = fgetc(file);
        codeNameBuff = (char *)malloc(colorNameLength);
        if (!codeNameBuff) {
                printf
                    ("ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeNameBuff\n");
                return 0;
        }
        fread((unsigned char *)codeNameBuff, 1, colorNameLength, file); /* TODO: check return value */
        thread->colorName = codeNameBuff;

        embColor_read(file, &col, 4);
        if (emb_verbose > 1) {
                printf("col red: %d\n", col.r);
                printf("col green: %d\n", col.g);
                printf("col blue: %d\n", col.b);
        }

        sectionNameLength = fgetc(file);
        sectionNameBuff = (char *)malloc(sectionNameLength);
        if (!sectionNameBuff) {
                printf
                    ("ERROR: format-stx.c stxReadThread(), unable to allocate memory for sectionNameBuff\n");
                return 0;
        }
        fread((unsigned char *)sectionNameBuff, 1, sectionNameLength, file);    /* TODO: check return value */
        thread->sectionName = sectionNameBuff;

        LOAD_I32(file, somethingSomething)
            LOAD_I32(file, somethingSomething2)
            LOAD_I32(file, somethingElse)
            LOAD_I16(file, numberOfOtherDescriptors)
            thread->subDescriptors =
            (SubDescriptor *) malloc(sizeof(SubDescriptor) *
                                     numberOfOtherDescriptors);
        if (!thread->subDescriptors) {
                printf
                    ("ERROR: format-stx.c stxReadThread(), unable to allocate memory for thread->subDescriptors\n");
                return 0;
        }
        for (j = 0; j < numberOfOtherDescriptors; j++) {
                SubDescriptor sd;
                char *subCodeBuff, *subColorNameBuff;
                int subCodeLength, subColorNameLength;

                sd.someNum = emb_read_i16(file);
                /* Debug.Assert(sd.someNum == 1); TODO: review */
                sd.someInt = emb_read_i32(file);
                subCodeLength = fgetc(file);
                subCodeBuff = (char *)malloc(subCodeLength);
                if (!subCodeBuff) {
                        printf
                            ("ERROR: format-stx.c stxReadThread(), unable to allocate memory for subCodeBuff\n");
                        return 0;
                }
                fread((unsigned char *)subCodeBuff, 1, subCodeLength, file);    /* TODO: check return value */
                sd.colorCode = subCodeBuff;
                subColorNameLength = fgetc(file);
                subColorNameBuff = (char *)malloc(subColorNameLength);
                if (!subColorNameBuff) {
                        printf
                            ("ERROR: format-stx.c stxReadThread(), unable to allocate memory for subColorNameBuff\n");
                        return 0;
                }
                fread((unsigned char *)subColorNameBuff, 1, subColorNameLength, file);  /* TODO: check return value */
                sd.colorName = subColorNameBuff;
                sd.someOtherInt = emb_read_i32(file);
                thread->subDescriptors[j] = sd;
        }
        return 1;
}

char readStx(EmbPattern *pattern, FILE *file)
{
        int i, threadCount;
        unsigned char *gif = 0;
        /* public Bitmap Image; */
        StxThread *stxThreads = 0;
        unsigned char headerBytes[7];
        char *header = 0;
        char stor;
        char filetype[4], version[5];
        int paletteLength, imageLength, something1, stitchDataOffset,
            something3;
        int threadDescriptionOffset, stitchCount, left, right, colors;
        int val[12];
        int bottom, top;

        if (!check_header_present(file, 15)) {
                puts("ERROR: header is not present.");
                return 0;
        }

        /* bytes 0-6 */
        if (!read_n_bytes(file, headerBytes, 7)) {
                return 0;
        }
        header = (char *)headerBytes;

        /* bytes 7-9 */
        memcpy(filetype, &header[0], 3);
        /* bytes 10-13 */
        memcpy(version, &header[3], 4);
        filetype[3] = '\0';
        version[4] = '\0';
        /* byte 14 */
        stor = (char)fgetc(file);
        if (emb_verbose > 1) {
                printf("stor: %d\n", stor);
        }

        /* bytes 15- */
        LOAD_I32(file, paletteLength)
            LOAD_I32(file, imageLength)
            LOAD_I32(file, something1)
            LOAD_I32(file, stitchDataOffset)
            LOAD_I32(file, something3)
            LOAD_I32(file, threadDescriptionOffset)
            LOAD_I32(file, stitchCount)
            LOAD_I32(file, colors)
            LOAD_I16(file, right)
            LOAD_I16(file, left)
            LOAD_I16(file, bottom)
            LOAD_I16(file, top)
            gif = (unsigned char *)malloc(imageLength);
        if (!gif) {
                printf
                    ("ERROR: format-stx.c readStx(), unable to allocate memory for gif\n");
                return 0;
        }
        if (!read_n_bytes(file, gif, imageLength)) {
                return 0;
        }
        /*Stream s2 = new MemoryStream(gif); TODO: review */
        /*Image = new Bitmap(s2); TODO: review */

        threadCount = emb_read_i16(file);
        stxThreads = (StxThread *) malloc(sizeof(StxThread) * threadCount);
        if (!stxThreads) {
                printf("ERROR: format-stx.c readStx(), unable ");
                printf("to allocate memory for stxThreads\n");
                return 0;
        }
        for (i = 0; i < threadCount; i++) {
                EmbThread t;
                StxThread st;
                stxReadThread(&st, file);

                t.color = st.stxColor;
                strcpy(t.description, st.colorName);
                strcpy(t.catalogNumber, st.colorCode);
                embp_addThread(pattern, t);
                stxThreads[i] = st;
        }

        fseek(file, 15, SEEK_CUR);

        for (i = 0; i < 12; i++) {
                val[i] = emb_read_i16(file);
                if (emb_verbose > 1) {
                        printf("identify val[%d] = %d", i, val[i]);
                }
        }
        if (emb_verbose > 1) {
                puts("val[4] == val[5] == 0");
                puts("val[10] == val[11] == 0");
        }
        fseek(file, 8, SEEK_CUR);       /* 0 0 */
        /* br.BaseStream.Position = stitchDataOffset; TODO: review */
        for (i = 1; i < stitchCount;) {
                char b0 = (char)fgetc(file);
                char b1 = (char)fgetc(file);
                if (b0 == -128) {
                        switch (b1) {
                        case 1:
                                b0 = (char)fgetc(file);
                                b1 = (char)fgetc(file);
                                /*embp_addStitchRel(b0, b1, STOP); TODO: review */

                                i++;
                                break;
                        case 2:
                                b0 = (char)fgetc(file);
                                b1 = (char)fgetc(file);
                                embp_addStitchRel(pattern, b0 / 10.0,
                                                  b1 / 10.0, JUMP, 1);
                                i++;
                                break;
                        case -94:
                                /* TODO: Is this a synchronize?
                                   If so document it in the comments. */
                                break;
                        default:
                                /*Debugger.Break(); TODO: review */
                                break;
                        }
                } else {
                        embp_addStitchRel(pattern, b0 / 10.0, b1 / 10.0, NORMAL,
                                          1);
                        i++;
                }
        }
        embp_flipVertical(pattern);
        return 1;
}

char writeStx(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: writeStx is not implemented.");
        if (emb_verbose > 1) {
                printf("Called with %p %p\n", (void *)pattern, (void *)file);
        }
        return 0;               /*TODO: finish writeStx */
}

/*
 * Pfaff Embroidery Format (.t09)
 * The Pfaff t09 format is stitch-only.
 */

char readT09(EmbPattern *pattern, FILE *file)
{
        unsigned char b[3];

        fseek(file, 0x0C, SEEK_SET);

        while (fread(b, 1, 3, file) == 3) {
                int stitchType = NORMAL;
                int b1 = b[0];
                int b2 = b[1];
                unsigned char commandByte = b[2];
                if (commandByte == 0x00) {
                        break;
                }
                if (commandByte & 0x10) {
                        stitchType = STOP;
                }
                if (commandByte & 0x20) {
                        b1 = -b1;
                }
                if (commandByte & 0x40) {
                        b2 = -b2;
                }
                embp_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
        }
        return 1;
}

char writeT09(EmbPattern *pattern, FILE *file)
{
        int i;
        EmbVector pos;
        fpad(file, 0x00, 0x0C);

        pos.x = 0.0;
        pos.y = 0.0;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                unsigned char b[3];
                int dx, dy;
                EmbStitch st = pattern->stitch_list->stitch[i];
                /* convert from mm to 0.1mm for file format */
                dx = (int)emb_round(10.0 * (st.x - pos.x));
                dy = (int)emb_round(10.0 * (st.y - pos.y));
                pos.x += 0.1 * dx;
                pos.y += 0.1 * dy;

                b[0] = dx;
                b[1] = dy;
                b[2] = 0;
                if (st.flags & NORMAL) {
                        /* guessing based on T01 here */
                        b[2] |= 0x03;
                }
                /* inferred from readT09 */
                if (st.flags & STOP) {
                        b[2] |= 0x10;
                }
                if (dx < 0) {
                        b[0] = -dx;
                        b[2] |= 0x20;
                }
                if (dy < 0) {
                        b[0] = -dy;
                        b[2] |= 0x40;
                }
                fwrite(b, 1, 3, file);
        }
        return 1;
}

/*
 * Happy Embroidery Format (.tap)
 * The Happy tap format is stitch-only.
 */

void encode_tap_record(FILE *file, int x, int y, int flags)
{
        unsigned char b[3];
        encode_tajima_ternary(b, x, y);

        b[2] |= (char)3;
        if (flags & END) {
                b[0] = 0;
                b[1] = 0;
                b[2] = 0xF3;
        }
        if (flags & (JUMP | TRIM)) {
                b[2] = (char)(b[2] | 0x83);
        }
        if (flags & STOP) {
                b[2] = (char)(b[2] | 0xC3);
        }
        fwrite(b, 1, 3, file);
}

int decode_tap_record_flags(unsigned char b2)
{
        if (b2 == 0xF3) {
                return END;
        }
        switch (b2 & 0xC3) {
        case 0x03:
                return NORMAL;
        case 0x83:
                return TRIM;
        case 0xC3:
                return STOP;
        default:
                return NORMAL;
        }
}

char readTap(EmbPattern *pattern, FILE *file)
{
        unsigned char b[3];

        while (fread(b, 1, 3, file) == 3) {
                int flags, x, y;
                decode_tajima_ternary(b, &x, &y);
                flags = decode_tap_record_flags(b[2]);
                embp_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
                if (flags == END) {
                        break;
                }
        }
        return 1;
}

char writeTap(EmbPattern *pattern, FILE *file)
{
        int i;
        EmbVector pos;

        embp_correctForMaxStitchLength(pattern, 12.1, 12.1);

        pos.x = 0.0;
        pos.y = 0.0;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                int dx, dy;
                EmbStitch st = pattern->stitch_list->stitch[i];
                /* convert from mm to 0.1mm for file format */
                dx = (int)emb_round(10.0 * (st.x - pos.x));
                dy = (int)emb_round(10.0 * (st.y - pos.y));
                pos.x += 0.1 * dx;
                pos.y += 0.1 * dy;
                encode_tap_record(file, dx, dy, st.flags);
        }
        return 1;
}

/*
 * ThredWorks Embroidery Format (.thr)
 * The ThreadWorks thr format is stitch-only.
 *
 * bit definitions for attributes of stitch
 * 0-3     stitch color
 * 4-14    form pointer
 * 15-18   spares
 * 19      not a form stitch
 * 20      center walk stitch
 * 21      edge walk stitch
 * 22      underlay stitch
 * 23      knot stitch
 * 24      feather stitch
 * 25-27   layer
 * 28      spare
 * 29-30   stitch type
 *             00=not a form stitch,
 *             01=form fill,
 *             10=form border fill,
 *             11=applique stitches
 * 31      set for user edited stitches
 */
char readThr(EmbPattern *pattern, FILE *file)
{
        ThredHeader header;
        EmbColor background;
        int currentColor;
        int i;

        header.sigVersion = emb_read_i32(file);
        header.length = emb_read_i32(file);
        header.numStiches = emb_read_i16(file);
        LOAD_U16(file, header.hoopSize)
            for (i = 0; i < 7; i++) {
                header.reserved[i] = emb_read_u16(file);
                printf("header.reserved[%d] = %d\n", i, header.reserved[i]);
        }

        if ((header.sigVersion & 0xffffff) == 0x746872) {
                unsigned int verVar = (header.sigVersion & 0xff000000) >> 24;
                switch (verVar) {
                case 0:
                        break;
                case 1:
                case 2:
                        /* skip the file header extension */
                        fseek(file, 144, SEEK_CUR);
                        break;
                default:
                        return 0;       /* unsupported version */
                }
        }
        currentColor = -1;
        for (i = 0; i < header.numStiches; i++) {
                int type = NORMAL;
                float x, y;
                unsigned int color;
                x = emb_read_i32(file);
                y = emb_read_i32(file);
                color = emb_read_i32(file);
                x /= 10.0;
                y /= 10.0;

                if ((int)(color & 0xF) != currentColor) {
                        currentColor = (int)color & 0xF;
                        embp_changeColor(pattern, currentColor);
                        type = STOP | TRIM;
                }
                embp_addStitchAbs(pattern, x, y, type, 0);
        }
        fseek(file, 16, SEEK_CUR);      /* skip bitmap name (16 chars) */

        embColor_read(file, &background, 4);
        if (emb_verbose > 1) {
                printf("background: %c %c %c\n", background.r, background.g,
                       background.b);
        }
        for (i = 0; i < 16; i++) {
                EmbThread thread;
                strcpy(thread.description, "NULL");
                strcpy(thread.catalogNumber, "NULL");
                embColor_read(file, &(thread.color), 4);
                embp_addThread(pattern, thread);
        }
        /*  64 bytes of rgbx(4 bytes) colors (16 custom colors) */
        /*  16 bytes of thread size (ascii representation ie. '4') */
        return 1;
}

char writeThr(EmbPattern *pattern, FILE *file)
{
        int i, stitchCount;
        unsigned char version = 0;
        ThredHeader header;
        ThredExtension extension;
        char bitmapName[16];

        stitchCount = pattern->stitch_list->count;

        memset(&header, 0, sizeof(ThredHeader));
        header.sigVersion = 0x746872 | (version << 24);
        header.length = stitchCount * 12 + 16;
        if (version == 1 || version == 2) {
                header.length = header.length + sizeof(ThredHeader);
        }
        header.numStiches = (unsigned short)stitchCount;        /* number of stitches in design */
        header.hoopSize = 5;

        emb_write_u32(file, header.sigVersion);
        emb_write_u32(file, header.length);
        emb_write_u16(file, header.numStiches);
        emb_write_u16(file, header.hoopSize);
        for (i = 0; i < 7; i++) {
                emb_write_u16(file, header.reserved[i]);
        }

        if (version == 1 || version == 2) {
                memset(&extension, 0, sizeof(ThredExtension));
                extension.auxFormat = 1;
                extension.hoopX = 640;
                extension.hoopY = 640;

                emb_write_i32(file, extension.hoopX);
                emb_write_i32(file, extension.hoopY);
                emb_write_i32(file, extension.stitchGranularity);
                fwrite(extension.creatorName, 1, 50, file);
                fwrite(extension.modifierName, 1, 50, file);
                fputc(extension.auxFormat, file);
                fwrite(extension.reserved, 1, 31, file);
        }

        /* write stitches */
        for (i = 0; i < pattern->stitch_list->count; i++) {
                unsigned int NOTFRM = 0x00080000;
                EmbStitch st = pattern->stitch_list->stitch[i];
                float x, y;
                x = (float)(st.x * 10.0);
                y = (float)(st.y * 10.0);
                emb_write_i32(file, x);
                emb_write_i32(file, y);
                emb_write_u32(file, NOTFRM | (st.color & 0x0F));
        }
        fwrite(bitmapName, 1, 16, file);
        /* background color */
        fwrite("\xFF\xFF\xFF\x00", 1, 4, file);

        for (i = 0; i < pattern->thread_list->count; i++) {
                EmbColor c = pattern->thread_list->thread[i].color;
                embColor_write(file, c, 4);
                if (i >= 16)
                        break;
        }

        /* write remaining colors if not yet 16 */
        fpad(file, 0, 4 * (16 - i));

        fpad(file, '4', 16);
        return 1;
}

/*
 * Text File (.txt)
 * The txt format is stitch-only and isn't associated with a specific company.
 */
char readTxt(EmbPattern *pattern, FILE *file)
{
        EmbString line;
        int stated_count, i;
        emb_readline(file, line, 99);
        stated_count = atoi(line);
        for (i = 0; i < stated_count; i++) {
                EmbStitch st;
                char *p, *y, *color, *flags;
                int state = 0;
                emb_readline(file, line, 99);
                p = line;
                y = line;
                color = line;
                flags = line;
                for (p = line; *p; p++) {
                        if (*p == ',' || *p == ' ') {
                                *p = 0;
                                switch (state) {
                                case 0:
                                        y = p + 1;
                                        break;
                                case 1:
                                        color = p + 7;
                                        break;
                                case 2:
                                        flags = p + 7;
                                        break;
                                default:
                                        break;
                                }
                                state++;
                        }
                }
                st.x = atof(line);
                st.y = atof(y);
                st.color = atoi(color);
                st.flags = atoi(flags);
                embp_addStitchAbs(pattern, st.x, st.y, st.flags, st.color);
        }
        puts("Overridden, defaulting to dst.");
        readDst(pattern, file);
        return 0;               /*TODO: finish readTxt */
}

char writeTxt(EmbPattern *pattern, FILE *file)
{
        int i;
        fprintf(file, "%u\n", (unsigned int)pattern->stitch_list->count);

        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch s = pattern->stitch_list->stitch[i];
                fprintf(file, "%.1f,%.1f color:%i flags:%i\n",
                        s.x, s.y, s.color, s.flags);
        }
        return 1;
}

/*
 * Barudan Embroidery Format (.u00)
 * The Barudan u00 format is stitch-only.
 */
char readU00(EmbPattern *pattern, FILE *file)
{
        int i;
        char dx = 0, dy = 0;
        int flags = NORMAL;
        unsigned char b[3];

        if (!check_header_present(file, 0x100)) {
                return 0;
        }

        /* 16 3byte RGB's start @ 0x08 followed by 14 bytes between
           0 and 15 with index of color for each color change */
        fseek(file, 0x08, SEEK_SET);
        for (i = 0; i < 16; i++) {
                EmbThread t;
                embColor_read(file, &(t.color), 3);
                strcpy(t.catalogNumber, "");
                strcpy(t.description, "");
                embp_addThread(pattern, t);
        }

        fseek(file, 0x100, SEEK_SET);
        while (fread(b, 1, 3, file) == 3) {
                char negativeX, negativeY;

                if (b[0] == 0xF8 || b[0] == 0x87 || b[0] == 0x91) {
                        break;
                }
                if ((b[0] & 0x0F) == 0) {
                        flags = NORMAL;
                } else if ((b[0] & 0x1f) == 1) {
                        flags = JUMP;
                } else if ((b[0] & 0x0F) > 0) {
                        flags = STOP;
                }
                negativeX = ((b[0] & 0x20) > 0);
                negativeY = ((b[0] & 0x40) > 0);

                dx = (char)b[2];
                dy = (char)b[1];
                if (negativeX) {
                        dx = (char)-dx;
                }
                if (negativeY) {
                        dy = (char)-dy;
                }
                embp_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }
        return 1;
}

char writeU00(EmbPattern *pattern, FILE *file)
{
        puts("writeU00 not implemented.");
        if (emb_verbose > 1) {
                printf("Called with %p %p\n", (void *)pattern, (void *)file);
        }
        return 0;               /*TODO: finish WriteU00 */
}

/*
 * Barudan Embroidery Format (.u01)
 * The Barudan u01 format is stitch-only.
 *
 * TODO: AFAIK this is a duplicate of U00. Review for differences and merge
 * files and handle accordingly.
 */
char readU01(EmbPattern *pattern, FILE *file)
{
        int fileLength, negativeX = 0, negativeY = 0, flags = NORMAL;
        char dx, dy;
        unsigned char data[3];

        if (!check_header_present(file, 0x100)) {
                return 0;
        }

        fseek(file, 0, SEEK_END);
        fileLength = ftell(file);
        fseek(file, 0x100, SEEK_SET);

        if (emb_verbose > 1) {
                printf("file length: %d\n", fileLength);
        }

        while (fread(data, 1, 3, file) == 3) {
                if (data[0] == 0xF8 || data[0] == 0x87 || data[0] == 0x91) {
                        break;
                }
                if ((data[0] & 0x0F) == 0) {
                        flags = NORMAL;
                } else if ((data[0] & 0x1f) == 1) {
                        flags = JUMP;
                } else if ((data[0] & 0x0F) > 0) {
                        flags = STOP;
                }
                negativeX = ((data[0] & 0x20) > 0);
                negativeY = ((data[0] & 0x40) > 0);

                dx = (char)data[2];
                dy = (char)data[1];
                if (negativeX) {
                        dx = (char)-dx;
                }
                if (negativeY) {
                        dy = (char)-dy;
                }
                embp_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }
        return 1;
}

char writeU01(EmbPattern *pattern, FILE *file)
{
        if (emb_verbose > 1) {
                printf("Called with %p %p\n", (void *)pattern, (void *)file);
        }
        return 0;               /*TODO: finish writeU01 */
}

/*
 * Pfaff Embroidery Format (.vip). The vip format is stitch-only.
 */

const unsigned char vipDecodingTable[] = {
        0x2E, 0x82, 0xE4, 0x6F, 0x38, 0xA9, 0xDC, 0xC6, 0x7B, 0xB6, 0x28, 0xAC,
        0xFD, 0xAA, 0x8A, 0x4E,
        0x76, 0x2E, 0xF0, 0xE4, 0x25, 0x1B, 0x8A, 0x68, 0x4E, 0x92, 0xB9, 0xB4,
        0x95, 0xF0, 0x3E, 0xEF,
        0xF7, 0x40, 0x24, 0x18, 0x39, 0x31, 0xBB, 0xE1, 0x53, 0xA8, 0x1F, 0xB1,
        0x3A, 0x07, 0xFB, 0xCB,
        0xE6, 0x00, 0x81, 0x50, 0x0E, 0x40, 0xE1, 0x2C, 0x73, 0x50, 0x0D, 0x91,
        0xD6, 0x0A, 0x5D, 0xD6,
        0x8B, 0xB8, 0x62, 0xAE, 0x47, 0x00, 0x53, 0x5A, 0xB7, 0x80, 0xAA, 0x28,
        0xF7, 0x5D, 0x70, 0x5E,
        0x2C, 0x0B, 0x98, 0xE3, 0xA0, 0x98, 0x60, 0x47, 0x89, 0x9B, 0x82, 0xFB,
        0x40, 0xC9, 0xB4, 0x00,
        0x0E, 0x68, 0x6A, 0x1E, 0x09, 0x85, 0xC0, 0x53, 0x81, 0xD1, 0x98, 0x89,
        0xAF, 0xE8, 0x85, 0x4F,
        0xE3, 0x69, 0x89, 0x03, 0xA1, 0x2E, 0x8F, 0xCF, 0xED, 0x91, 0x9F, 0x58,
        0x1E, 0xD6, 0x84, 0x3C,
        0x09, 0x27, 0xBD, 0xF4, 0xC3, 0x90, 0xC0, 0x51, 0x1B, 0x2B, 0x63, 0xBC,
        0xB9, 0x3D, 0x40, 0x4D,
        0x62, 0x6F, 0xE0, 0x8C, 0xF5, 0x5D, 0x08, 0xFD, 0x3D, 0x50, 0x36, 0xD7,
        0xC9, 0xC9, 0x43, 0xE4,
        0x2D, 0xCB, 0x95, 0xB6, 0xF4, 0x0D, 0xEA, 0xC2, 0xFD, 0x66, 0x3F, 0x5E,
        0xBD, 0x69, 0x06, 0x2A,
        0x03, 0x19, 0x47, 0x2B, 0xDF, 0x38, 0xEA, 0x4F, 0x80, 0x49, 0x95, 0xB2,
        0xD6, 0xF9, 0x9A, 0x75,
        0xF4, 0xD8, 0x9B, 0x1D, 0xB0, 0xA4, 0x69, 0xDB, 0xA9, 0x21, 0x79, 0x6F,
        0xD8, 0xDE, 0x33, 0xFE,
        0x9F, 0x04, 0xE5, 0x9A, 0x6B, 0x9B, 0x73, 0x83, 0x62, 0x7C, 0xB9, 0x66,
        0x76, 0xF2, 0x5B, 0xC9,
        0x5E, 0xFC, 0x74, 0xAA, 0x6C, 0xF1, 0xCD, 0x93, 0xCE, 0xE9, 0x80, 0x53,
        0x03, 0x3B, 0x97, 0x4B,
        0x39, 0x76, 0xC2, 0xC1, 0x56, 0xCB, 0x70, 0xFD, 0x3B, 0x3E, 0x52, 0x57,
        0x81, 0x5D, 0x56, 0x8D,
        0x51, 0x90, 0xD4, 0x76, 0xD7, 0xD5, 0x16, 0x02, 0x6D, 0xF2, 0x4D, 0xE1,
        0x0E, 0x96, 0x4F, 0xA1,
        0x3A, 0xA0, 0x60, 0x59, 0x64, 0x04, 0x1A, 0xE4, 0x67, 0xB6, 0xED, 0x3F,
        0x74, 0x20, 0x55, 0x1F,
        0xFB, 0x23, 0x92, 0x91, 0x53, 0xC8, 0x65, 0xAB, 0x9D, 0x51, 0xD6, 0x73,
        0xDE, 0x01, 0xB1, 0x80,
        0xB7, 0xC0, 0xD6, 0x80, 0x1C, 0x2E, 0x3C, 0x83, 0x63, 0xEE, 0xBC, 0x33,
        0x25, 0xE2, 0x0E, 0x7A,
        0x67, 0xDE, 0x3F, 0x71, 0x14, 0x49, 0x9C, 0x92, 0x93, 0x0D, 0x26, 0x9A,
        0x0E, 0xDA, 0xED, 0x6F,
        0xA4, 0x89, 0x0C, 0x1B, 0xF0, 0xA1, 0xDF, 0xE1, 0x9E, 0x3C, 0x04, 0x78,
        0xE4, 0xAB, 0x6D, 0xFF,
        0x9C, 0xAF, 0xCA, 0xC7, 0x88, 0x17, 0x9C, 0xE5, 0xB7, 0x33, 0x6D, 0xDC,
        0xED, 0x8F, 0x6C, 0x18,
        0x1D, 0x71, 0x06, 0xB1, 0xC5, 0xE2, 0xCF, 0x13, 0x77, 0x81, 0xC5, 0xB7,
        0x0A, 0x14, 0x0A, 0x6B,
        0x40, 0x26, 0xA0, 0x88, 0xD1, 0x62, 0x6A, 0xB3, 0x50, 0x12, 0xB9, 0x9B,
        0xB5, 0x83, 0x9B, 0x37
};

int vipDecodeByte(unsigned char b)
{
        if (b >= 0x80)
                return (-(unsigned char)(~b + 1));
        return b;
}

int vipDecodeStitchType(unsigned char b)
{
        switch (b) {
        case 0x80:
                return NORMAL;
        case 0x81:
                return TRIM;
        case 0x84:
                return STOP;
        case 0x90:
                return END;
        default:
                return NORMAL;
        }
}

unsigned char *vipDecompressData(unsigned char *input,
                                 int compressedInputLength,
                                 int decompressedContentLength)
{
        unsigned char *decompressedData =
            (unsigned char *)malloc(decompressedContentLength);
        if (!decompressedData) {
                printf
                    ("ERROR: format-vip.c vipDecompressData(), cannot allocate memory for decompressedData\n");
                return 0;
        }
        hus_decompress((char *)input, compressedInputLength,
                       (char *)decompressedData, &decompressedContentLength);
        return decompressedData;
}

char readVip(EmbPattern *pattern, FILE *file)
{
        int fileLength;
        int i;
        unsigned char prevByte = 0;
        unsigned char *attributeData = 0, *decodedColors = 0;
        unsigned char *attributeDataDecompressed = 0;
        unsigned char *xData = 0, *xDecompressed = 0, *yData =
            0, *yDecompressed = 0;
        VipHeader header;

        fileLength = check_header_present(file, 32);
        if (!fileLength) {
                printf("ERROR: file shorter than header.");
                return 0;
        }

        header.magicCode = emb_read_i32(file);
        header.numberOfStitches = emb_read_i32(file);
        header.numberOfColors = emb_read_i32(file);

        header.postitiveXHoopSize = emb_read_i16(file);
        header.postitiveYHoopSize = emb_read_i16(file);
        header.negativeXHoopSize = emb_read_i16(file);
        header.negativeYHoopSize = emb_read_i16(file);
        header.attributeOffset = emb_read_i32(file);
        header.xOffset = emb_read_i32(file);
        header.yOffset = emb_read_i32(file);

        if (!read_n_bytes(file, header.stringVal, 8)) {
                return 0;
        }

        header.unknown = emb_read_i16(file);

        header.colorLength = emb_read_i32(file);
        decodedColors = (unsigned char *)malloc(header.numberOfColors * 4);
        if (!decodedColors) {
                printf("ERROR: format-vip.c readVip(), ");
                printf("cannot allocate memory for decodedColors\n");
                return 0;
        }
        for (i = 0; i < header.numberOfColors * 4; ++i) {
                unsigned char inputByte = (char)fgetc(file);
                unsigned char tmpByte =
                    (unsigned char)(inputByte ^ vipDecodingTable[i]);
                decodedColors[i] = (unsigned char)(tmpByte ^ prevByte);
                prevByte = inputByte;
        }
        for (i = 0; i < header.numberOfColors; i++) {
                EmbThread thread;
                int startIndex = i << 2;
                thread.color.r = decodedColors[startIndex];
                thread.color.g = decodedColors[startIndex + 1];
                thread.color.b = decodedColors[startIndex + 2];
                /* printf("%d\n", decodedColors[startIndex + 3]); */
                embp_addThread(pattern, thread);
        }
        fseek(file, header.attributeOffset, SEEK_SET);
        attributeData =
            (unsigned char *)malloc(header.xOffset - header.attributeOffset);
        if (!attributeData) {
                printf
                    ("ERROR: format-vip.c readVip(), cannot allocate memory for attributeData\n");
                return 0;
        }
        fread(attributeData, 1, header.xOffset - header.attributeOffset, file); /* TODO: check return value */
        attributeDataDecompressed =
            vipDecompressData(attributeData,
                              header.xOffset - header.attributeOffset,
                              header.numberOfStitches);

        fseek(file, header.xOffset, SEEK_SET);
        xData = (unsigned char *)malloc(header.yOffset - header.xOffset);
        if (!xData) {
                printf
                    ("ERROR: format-vip.c readVip(), cannot allocate memory for xData\n");
                return 0;
        }
        fread(xData, 1, header.yOffset - header.xOffset, file); /* TODO: check return value */
        xDecompressed =
            vipDecompressData(xData, header.yOffset - header.xOffset,
                              header.numberOfStitches);

        fseek(file, header.yOffset, SEEK_SET);
        yData = (unsigned char *)malloc(fileLength - header.yOffset);
        if (!yData) {
                printf
                    ("ERROR: format-vip.c readVip(), cannot allocate memory for yData\n");
                return 0;
        }
        fread(yData, 1, fileLength - header.yOffset, file);     /* TODO: check return value */
        yDecompressed =
            vipDecompressData(yData, fileLength - header.yOffset,
                              header.numberOfStitches);

        for (i = 0; i < header.numberOfStitches; i++) {
                embp_addStitchRel(pattern,
                                  vipDecodeByte(xDecompressed[i]) / 10.0,
                                  vipDecodeByte(yDecompressed[i]) / 10.0,
                                  vipDecodeStitchType(attributeDataDecompressed
                                                      [i]), 1);
        }
        embp_addStitchRel(pattern, 0, 0, END, 1);

        safe_free(attributeData);
        safe_free(xData);
        safe_free(yData);
        safe_free(attributeDataDecompressed);
        safe_free(xDecompressed);
        safe_free(yDecompressed);
        return 1;
}

unsigned char *vipCompressData(unsigned char *input, int decompressedInputSize,
                               int *compressedSize)
{
        unsigned char *compressedData =
            (unsigned char *)malloc(decompressedInputSize * 2);
        if (!compressedData) {
                printf
                    ("ERROR: format-vip.c vipCompressData(), cannot allocate memory for compressedData\n");
                return 0;
        }
        hus_compress((char *)input, decompressedInputSize,
                     (char *)compressedData, compressedSize);
        return compressedData;
}

unsigned char vipEncodeByte(EmbReal f)
{
        return (unsigned char)(int)emb_round(f);
}

unsigned char vipEncodeStitchType(int st)
{
        switch (st) {
        case NORMAL:
                return (0x80);
        case JUMP:
        case TRIM:
                return (0x81);
        case STOP:
                return (0x84);
        case END:
                return (0x90);
        default:
                return (0x80);
        }
}

char writeVip(EmbPattern *pattern, FILE *file)
{
        EmbRect boundingRect;
        int stitchCount, minColors, patternColor;
        int attributeSize = 0;
        int xCompressedSize = 0;
        int yCompressedSize = 0;
        EmbReal previousX = 0;
        EmbReal previousY = 0;
        unsigned char *xValues = 0, *yValues = 0, *attributeValues = 0;
        EmbReal xx = 0.0;
        EmbReal yy = 0.0;
        int flags = 0;
        int i = 0;
        unsigned char *attributeCompressed = 0, *xCompressed = 0;
        unsigned char *yCompressed = 0, *decodedColors = 0, *encodedColors = 0;
        unsigned char prevByte = 0;

        puts("VIP not yet implemented.");
        return 0;

        stitchCount = pattern->stitch_list->count;
        minColors = pattern->thread_list->count;
        decodedColors = (unsigned char *)malloc(minColors << 2);
        if (!decodedColors) {
                return 0;
        }
        encodedColors = (unsigned char *)malloc(minColors << 2);
        if (!encodedColors) {
                safe_free(decodedColors);
                return 0;
        }
        /* embp_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */

        patternColor = minColors;
        if (emb_verbose > 1) {
                printf("patternColor: %d\n", patternColor);
        }
        if (minColors > 24) {
                minColors = 24;
        }
        emb_write_u32(file, 0x0190FC5D);
        emb_write_u32(file, stitchCount);
        emb_write_u32(file, minColors);

        boundingRect = embp_bounds(pattern);
        emb_write_i16(file,
                      (int16_t) emb_round((boundingRect.x + boundingRect.w) *
                                          10.0));
        emb_write_i16(file, (int16_t) - emb_round(boundingRect.y * 10.0 - 1.0));
        emb_write_i16(file, (int16_t) emb_round(boundingRect.x * 10.0));
        emb_write_i16(file,
                      (int16_t) -
                      emb_round((boundingRect.y + boundingRect.h) * 10.0 -
                                1.0));

        emb_write_u32(file, 0x38 + (minColors << 3));

        xValues =
            (unsigned char *)malloc(sizeof(unsigned char) * (stitchCount));
        yValues =
            (unsigned char *)malloc(sizeof(unsigned char) * (stitchCount));
        attributeValues =
            (unsigned char *)malloc(sizeof(unsigned char) * (stitchCount));
        if (xValues && yValues && attributeValues) {
                for (i = 0; i < pattern->stitch_list->count; i++) {
                        EmbStitch st;
                        st = pattern->stitch_list->stitch[i];
                        xx = st.x;
                        yy = st.y;
                        flags = st.flags;
                        xValues[i] = vipEncodeByte((xx - previousX) * 10.0);
                        previousX = xx;
                        yValues[i] = vipEncodeByte((yy - previousY) * 10.0);
                        previousY = yy;
                        attributeValues[i] = vipEncodeStitchType(flags);
                }
                attributeCompressed =
                    vipCompressData(attributeValues, stitchCount,
                                    &attributeSize);
                xCompressed =
                    vipCompressData(xValues, stitchCount, &xCompressedSize);
                yCompressed =
                    vipCompressData(yValues, stitchCount, &yCompressedSize);

                emb_write_u32(file,
                              (unsigned int)(0x38 + (minColors << 3) +
                                             attributeSize));
                emb_write_u32(file,
                              (unsigned int)(0x38 + (minColors << 3) +
                                             attributeSize + xCompressedSize));
                emb_write_u32(file, 0x00000000);
                emb_write_u32(file, 0x00000000);
                emb_write_u16(file, 0x0000);

                emb_write_i32(file, minColors << 2);

                for (i = 0; i < minColors; i++) {
                        int byteChunk = i << 2;
                        EmbColor currentColor =
                            pattern->thread_list->thread[i].color;
                        decodedColors[byteChunk] = currentColor.r;
                        decodedColors[byteChunk + 1] = currentColor.g;
                        decodedColors[byteChunk + 2] = currentColor.b;
                        decodedColors[byteChunk + 3] = 0x01;
                }

                for (i = 0; i < minColors << 2; ++i) {
                        unsigned char tmpByte =
                            (unsigned char)(decodedColors[i] ^
                                            vipDecodingTable[i]);
                        prevByte = (unsigned char)(tmpByte ^ prevByte);
                        fputc(prevByte, file);
                }
                for (i = 0; i <= minColors; i++) {
                        emb_write_i32(file, 1);
                }
                emb_write_u32(file, 0); /* string length */
                emb_write_i16(file, 0);
                fwrite((char *)attributeCompressed, 1, attributeSize, file);
                fwrite((char *)xCompressed, 1, xCompressedSize, file);
                fwrite((char *)yCompressed, 1, yCompressedSize, file);
        }

        safe_free(attributeCompressed);
        safe_free(xCompressed);
        safe_free(yCompressed);
        safe_free(attributeValues);
        safe_free(xValues);
        safe_free(yValues);
        safe_free(decodedColors);
        safe_free(encodedColors);
        return 1;
}

/*
 * VP3 FORMAT
 * Pfaff Embroidery Format (.vp3)
 *
 * The Pfaff vp3 format is stitch-only.
 */
unsigned char *vp3ReadString(FILE *file)
{
        short stringLength;
        unsigned char *charString = 0;
        if (!file) {
                printf
                    ("ERROR: format-vp3.c vp3ReadString(), file argument is null\n");
                return 0;
        }
        stringLength = emb_read_i16be(file);
        charString = (unsigned char *)malloc(stringLength);
        if (!charString) {
                printf
                    ("ERROR: format-vp3.c vp3ReadString(), cannot allocate memory for charString\n");
                return 0;
        }
        fread(charString, 1, stringLength, file);       /* TODO: check return value */
        return charString;
}

int vp3Decode(unsigned char inputByte)
{
        if (inputByte > 0x80) {
                return (int)-((unsigned char)((~inputByte) + 1));
        }
        return ((int)inputByte);
}

short vp3DecodeInt16(unsigned short inputByte)
{
        if (inputByte > 0x8000) {
                return -((int16_t) ((~inputByte) + 1));
        }
        return ((int16_t) inputByte);
}

vp3Hoop vp3ReadHoopSection(FILE *file)
{
        vp3Hoop hoop;

        if (!file) {
                printf
                    ("ERROR: format-vp3.c vp3ReadHoopSection(), file argument is null\n");
                hoop.bottom = 0;
                hoop.left = 0;
                hoop.right = 0;
                hoop.top = 0;
                hoop.threadLength = 0;
                hoop.unknown2 = 0;
                hoop.numberOfColors = 0;
                hoop.unknown3 = 0;
                hoop.unknown4 = 0;
                hoop.numberOfBytesRemaining = 0;

                hoop.xOffset = 0;
                hoop.yOffset = 0;

                hoop.byte1 = 0;
                hoop.byte2 = 0;
                hoop.byte3 = 0;
                hoop.right2 = 0;
                hoop.left2 = 0;
                hoop.bottom2 = 0;
                hoop.top2 = 0;
                hoop.height = 0;
                hoop.width = 0;
                return hoop;
        }

        hoop.right = emb_read_i32be(file);
        hoop.bottom = emb_read_i32be(file);
        hoop.left = emb_read_i32be(file);
        hoop.top = emb_read_i32be(file);

        /* yes, it seems this is _not_ big endian */
        hoop.threadLength = emb_read_i32(file);
        hoop.unknown2 = (char)fgetc(file);
        hoop.numberOfColors = (char)fgetc(file);
        hoop.unknown3 = emb_read_i16be(file);
        hoop.unknown4 = emb_read_i32be(file);
        hoop.numberOfBytesRemaining = emb_read_i32be(file);

        hoop.xOffset = emb_read_i32be(file);
        hoop.yOffset = emb_read_i32be(file);

        hoop.byte1 = (char)fgetc(file);
        hoop.byte2 = (char)fgetc(file);
        hoop.byte3 = (char)fgetc(file);

        /* Centered hoop dimensions */
        hoop.right2 = emb_read_i32be(file);
        hoop.left2 = emb_read_i32be(file);
        hoop.bottom2 = emb_read_i32be(file);
        hoop.top2 = emb_read_i32be(file);

        hoop.width = emb_read_i32be(file);
        hoop.height = emb_read_i32be(file);
        return hoop;
}

char readVp3(EmbPattern *pattern, FILE *file)
{
        unsigned char magicString[5];
        unsigned char some;
        unsigned char *softwareVendorString = 0;
        /* unsigned char v2, ..., v18; */
        unsigned char *anotherSoftwareVendorString = 0;
        int numberOfColors;
        long colorSectionOffset;
        unsigned char magicCode[6];
        short someShort;
        unsigned char someByte;
        int bytesRemainingInFile, hoopConfigurationOffset;
        unsigned char *fileCommentString = 0;   /* some software writes used settings here */
        unsigned char *anotherCommentString = 0;
        int i;

        fread(magicString, 1, 5, file); /* %vsm% *//* TODO: check return value */
        LOAD_I8(file, some)     /* 0 */
            softwareVendorString = vp3ReadString(file);
        REPORT_STR(softwareVendorString)
            safe_free(softwareVendorString);
        LOAD_I16(file, someShort)
            LOAD_I8(file, someByte)
            LOAD_I32(file, bytesRemainingInFile)
            fileCommentString = vp3ReadString(file);
        hoopConfigurationOffset = (int)ftell(file);
        REPORT_INT(hoopConfigurationOffset);

        vp3ReadHoopSection(file);

        anotherCommentString = vp3ReadString(file);
        REPORT_STR(anotherCommentString);
        safe_free(anotherCommentString);

        /* TODO: review v1 thru v18 variables and use emb_unused() if needed */
        for (i = 0; i < 18; i++) {
                unsigned char v1;
                v1 = (char)fgetc(file);
                if (emb_verbose > 1) {
                        printf("v%d = %d\n", i, v1);
                }
        }

        /* TODO: check return value */
        /* 0x78 0x78 0x55 0x55 0x01 0x00 */
        if (fread(magicCode, 1, 6, file) != 6) {
                puts("ERROR: Failed to read magicCode.");
                return 0;
        }

        anotherSoftwareVendorString = vp3ReadString(file);
        REPORT_STR(anotherSoftwareVendorString);
        safe_free(anotherSoftwareVendorString);

        numberOfColors = emb_read_i16be(file);
        colorSectionOffset = (int)ftell(file);

        for (i = 0; i < numberOfColors; i++) {
                EmbThread t;
                char tableSize;
                int startX, startY, offsetToNextColorX, offsetToNextColorY;
                unsigned char *threadColorNumber, *colorName, *threadVendor;
                int unknownThreadString, numberOfBytesInColor;

                strcpy(t.catalogNumber, "");
                strcpy(t.description, "");
                fseek(file, colorSectionOffset, SEEK_SET);
                printf("ERROR: format-vp3.c Color Check Byte #1: 0 == %d\n",
                       (char)fgetc(file));
                printf("ERROR: format-vp3.c Color Check Byte #2: 5 == %d\n",
                       (char)fgetc(file));
                printf("ERROR: format-vp3.c Color Check Byte #3: 0 == %d\n",
                       (char)fgetc(file));
                colorSectionOffset = emb_read_i32be(file);
                colorSectionOffset += ftell(file);
                startX = emb_read_i32be(file);
                startY = emb_read_i32be(file);
                embp_addStitchAbs(pattern, startX / 1000.0, -startY / 1000.0,
                                  JUMP, 1);

                tableSize = (char)fgetc(file);
                fseek(file, 1, SEEK_CUR);
                embColor_read(file, &(t.color), 3);
                embp_addThread(pattern, t);
                fseek(file, 6 * tableSize - 1, SEEK_CUR);

                threadColorNumber = vp3ReadString(file);
                colorName = vp3ReadString(file);
                threadVendor = vp3ReadString(file);

                offsetToNextColorX = emb_read_i32be(file);
                offsetToNextColorY = emb_read_i32be(file);

                unknownThreadString = emb_read_i16be(file);
                fseek(file, unknownThreadString, SEEK_CUR);
                numberOfBytesInColor = emb_read_i32be(file);
                fseek(file, 0x3, SEEK_CUR);

                if (emb_verbose > 1) {
                        printf("number of bytes in color: %d\n",
                               numberOfBytesInColor);
                        printf("thread color number: %s\n", threadColorNumber);
                        printf("offset to next color x: %d\n",
                               offsetToNextColorX);
                        printf("offset to next color y: %d\n",
                               offsetToNextColorY);
                        printf("color name: %s\n", colorName);
                        printf("thread vendor: %s\n", threadVendor);
                        printf("fileCommentString: %s\n", fileCommentString);
                }

                safe_free(threadColorNumber);
                safe_free(colorName);
                safe_free(threadVendor);

                while (ftell(file) < colorSectionOffset - 1) {
                        int lastFilePosition = ftell(file);
                        int x = vp3Decode((char)fgetc(file));
                        int y = vp3Decode((char)fgetc(file));
                        short readIn;
                        if (x == 0x80) {
                                switch (y) {
                                case 0x00:
                                case 0x03:
                                        break;
                                case 0x01:{
                                                readIn = emb_read_i16be(file);
                                                x = vp3DecodeInt16(readIn);
                                                readIn = emb_read_i16be(file);
                                                y = vp3DecodeInt16(readIn);
                                                fseek(file, 2, SEEK_CUR);
                                                embp_addStitchRel(pattern,
                                                                  x / 10.0,
                                                                  y / 10.0,
                                                                  TRIM, 1);
                                                break;
                                        }
                                default:
                                        break;
                                }
                        } else {
                                embp_addStitchRel(pattern, x / 10.0, y / 10.0,
                                                  NORMAL, 1);
                        }

                        if (ftell(file) == lastFilePosition) {
                                printf
                                    ("ERROR: format-vp3.c could not read stitch block in entirety\n");
                                return 0;
                        }
                }
                if (i + 1 < numberOfColors) {
                        embp_addStitchRel(pattern, 0, 0, STOP, 1);
                }
        }
        safe_free(fileCommentString);
        embp_flipVertical(pattern);
        return 1;
}

void vp3WriteStringLen(FILE *file, const char *str, int len)
{
        emb_write_u16be(file, len);
        fwrite(str, 1, len, file);
}

void vp3WriteString(FILE *file, const char *str)
{
        vp3WriteStringLen(file, str, strlen(str));
}

void vp3PatchByteCount(FILE *file, int offset, int adjustment)
{
        int currentPos = ftell(file);
        fseek(file, offset, SEEK_SET);
        printf("Patching byte count: %d\n", currentPos - offset + adjustment);
        emb_write_i32be(file, currentPos - offset + adjustment);
        fseek(file, currentPos, SEEK_SET);
}

char writeVp3(EmbPattern *pattern, FILE *file)
{
        EmbRect bounds;
        int remainingBytesPos, remainingBytesPos2;
        int colorSectionStitchBytes, first = 1, i, numberOfColors;
        EmbColor color;
        color.r = 0xFE;
        color.g = 0xFE;
        color.b = 0xFE;

        bounds = embp_bounds(pattern);

        embp_correctForMaxStitchLength(pattern, 3200.0, 3200.0);        /* VP3 can encode signed 16bit deltas */

        embp_flipVertical(pattern);

        fwrite("%vsm%\0", 1, 6, file);
        vp3WriteString(file, "Embroidermodder");
        fwrite("\x00\x02\x00", 1, 3, file);

        remainingBytesPos = ftell(file);
        emb_write_i32(file, 0); /* placeholder */
        vp3WriteString(file, "");
        emb_write_i32be(file, (bounds.x + bounds.w) * 1000);
        emb_write_i32be(file, (bounds.y + bounds.h) * 1000);
        emb_write_i32be(file, bounds.x * 1000);
        emb_write_i32be(file, bounds.y * 1000);
        emb_write_i32(file, 0); /* this would be some (unknown) function of thread length */
        fputc(0, file);

        numberOfColors = embp_color_count(pattern, color);
        fputc(numberOfColors, file);
        fwrite("\x0C\x00\x01\x00\x03\x00", 1, 6, file);

        remainingBytesPos2 = ftell(file);
        emb_write_i32(file, 0); /* placeholder */

        emb_write_i32be(file, 0);       /* origin X */
        emb_write_i32be(file, 0);       /* origin Y */
        fpad(file, 0, 3);

        emb_write_i32be(file, (bounds.x + bounds.w) * 1000);
        emb_write_i32be(file, (bounds.y + bounds.h) * 1000);
        emb_write_i32be(file, bounds.x * 1000);
        emb_write_i32be(file, bounds.y * 1000);

        emb_write_i32be(file, bounds.w * 1000);
        emb_write_i32be(file, bounds.h * 1000);

        vp3WriteString(file, "");
        emb_write_i16be(file, 25700);
        emb_write_i32be(file, 4096);
        emb_write_i32be(file, 0);
        emb_write_i32be(file, 0);
        emb_write_i32be(file, 4096);

        fwrite("xxPP\x01\0", 1, 6, file);
        vp3WriteString(file, "");
        emb_write_i16be(file, numberOfColors);

        for (i = 0; i < pattern->stitch_list->count; i++) {
                char colorName[8] = { 0 };
                EmbReal lastX, lastY;
                int colorSectionLengthPos, j;
                EmbStitch s;
                int lastColor;

                j = 0;
                s.x = 0.0;
                s.y = 0.0;
                s.color = 0;
                s.flags = 0;

                if (!first) {
                        fputc(0, file);
                }
                fputc(0, file);
                fputc(5, file);
                fputc(0, file);

                colorSectionLengthPos = ftell(file);
                emb_write_i32(file, 0); /* placeholder */

                /*
                   pointer = mainPointer;
                   color = pattern->thread_list->thread[pointer->stitch.color].color;

                   if (first && pointer->stitch.flags & JUMP && pointer->next->stitch.flags & JUMP) {
                   pointer = pointer->next;
                   }

                   s = pointer->stitch;
                 */
                if (emb_verbose > 1) {
                        printf("%d\n", j);
                        printf("format-vp3.c DEBUG %d, %f, %f\n", s.flags, s.x,
                               s.y);
                }
                emb_write_i32be(file, s.x * 1000);
                emb_write_i32be(file, -s.y * 1000);
                /* pointer = pointer->next; */

                first = 0;

                lastX = s.x;
                lastY = s.y;
                lastColor = s.color;
                if (emb_verbose > 1) {
                        printf("last %f %f %d\n", lastX, lastY, lastColor);
                }

                fwrite("\x01\x00", 1, 2, file);

                printf
                    ("format-vp3.c writeVp3(), switching to color (%d, %d, %d)\n",
                     color.r, color.g, color.b);
                embColor_write(file, color, 4);

                fwrite("\x00\x00\x05", 1, 3, file);
                fputc(40, file);

                vp3WriteString(file, "");

                sprintf(colorName, "#%02x%02x%02x", color.b, color.g, color.r);

                vp3WriteString(file, colorName);
                vp3WriteString(file, "");

                emb_write_i32be(file, 0);
                emb_write_i32be(file, 0);

                vp3WriteStringLen(file, "\0", 1);

                colorSectionStitchBytes = ftell(file);
                emb_write_i32(file, 0); /* placeholder */

                fputc(10, file);
                fputc(246, file);
                fputc(0, file);

                /*
                   for (j=i; j<pattern->stitch_list->count; j++) {
                   while (pointer) {
                   short dx, dy;

                   EmbStitch s = pointer->stitch;
                   if (s.color != lastColor) {
                   break;
                   }
                   if (s.flags & END || s.flags & STOP) {
                   break;
                   }
                   dx = (s.x - lastX) * 10;
                   dy = (s.y - lastY) * 10;
                   // output is in ints, ensure rounding errors do not sum up.
                   lastX = lastX + dx / 10.0;
                   lastY = lastY + dy / 10.0;

                   if (dx < -127 || dx > 127 || dy < -127 || dy > 127) {
                   fputc(128, file);
                   fputc(1, file);
                   emb_write_i16be(file, dx);
                   emb_write_i16be(file, dy);
                   fputc(128, file);
                   fputc(2, file);
                   }
                   else {
                   char b[2];
                   b[0] = dx;
                   b[1] = dy;
                   fwrite(b, 1, 2, file);
                   }

                   pointer = pointer->next;
                   }
                 */

                vp3PatchByteCount(file, colorSectionStitchBytes, -4);
                vp3PatchByteCount(file, colorSectionLengthPos, -3);

                /* mainPointer = pointer; */
        }

        vp3PatchByteCount(file, remainingBytesPos2, -4);
        vp3PatchByteCount(file, remainingBytesPos, -4);

        embp_flipVertical(pattern);
        return 0;
}

/*
 * Singer Embroidery Format (.xxx)
 * The Singer xxx format is stitch-only.
 */

char xxxDecodeByte(unsigned char inputByte)
{
        if (inputByte >= 0x80) {
                return (char)((-~inputByte) - 1);
        }
        return ((char)inputByte);
}

char readXxx(EmbPattern *pattern, FILE *file)
{
        int dx = 0, dy = 0, numberOfColors, paletteOffset, i;
        char thisStitchJump = 0;

        if (emb_verbose > 1) {
                puts("readXxx has been overridden.");
                return 0;
        }

        fseek(file, 0x27, SEEK_SET);
        numberOfColors = emb_read_i16(file);
        fseek(file, 0xFC, SEEK_SET);
        paletteOffset = emb_read_i32(file);
        fseek(file, paletteOffset + 6, SEEK_SET);

        for (i = 0; i < numberOfColors; i++) {
                EmbThread thread;
                strcpy(thread.catalogNumber, "NULL");
                strcpy(thread.description, "NULL");
                fseek(file, 1, SEEK_CUR);
                embColor_read(file, &(thread.color), 3);
                embp_addThread(pattern, thread);
        }
        fseek(file, 0x100, SEEK_SET);

        for (i = 0; !feof(file) && ftell(file) < paletteOffset; i++) {
                unsigned char b0, b1;
                int flags;
                flags = NORMAL;
                if (thisStitchJump)
                        flags = TRIM;
                thisStitchJump = 0;
                b0 = (char)fgetc(file);
                b1 = (char)fgetc(file);
                /* TODO: ARE THERE OTHER BIG JUMP CODES? */
                if (b0 == 0x7E || b0 == 0x7D) {
                        dx = b1 + ((char)fgetc(file) << 8);
                        dx = ((int16_t) dx);
                        dy = emb_read_i16(file);
                        flags = TRIM;
                } else if (b0 == 0x7F) {
                        /* TODO: LOOKS LIKE THESE CODES ARE IN THE HEADER */
                        if (b1 != 0x17 && b1 != 0x46 && b1 >= 8) {
                                b0 = 0;
                                b1 = 0;
                                thisStitchJump = 1;
                                flags = STOP;
                        } else if (b1 == 1) {
                                flags = TRIM;
                                b0 = (char)fgetc(file);
                                b1 = (char)fgetc(file);
                        } else {
                                continue;
                        }
                        dx = xxxDecodeByte(b0);
                        dy = xxxDecodeByte(b1);
                } else {
                        dx = xxxDecodeByte(b0);
                        dy = xxxDecodeByte(b1);
                }
                embp_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }
        /* TODO: check end of pattern for multiple STOPs */
        return 1;
}

void xxxEncodeStop(FILE *file, EmbStitch s)
{
        fputc((unsigned char)0x7F, file);
        fputc((unsigned char)(s.color + 8), file);
}

void xxxEncodeStitch(FILE *file, EmbReal deltaX, EmbReal deltaY, int flags)
{
        if ((flags & (JUMP | TRIM))
            && (fabs(deltaX) > 124 || fabs(deltaY) > 124)) {
                fputc(0x7E, file);
                /* Does this cast work right? */
                emb_write_i16(file, (int16_t) deltaX);
                emb_write_i16(file, (int16_t) deltaY);
        } else {
                /* TODO: Verify this works after changing this to unsigned char */
                fputc((unsigned char)emb_round(deltaX), file);
                fputc((unsigned char)emb_round(deltaY), file);
        }
}

void xxxEncodeDesign(FILE *file, EmbPattern *p)
{
        int i;
        EmbReal thisX = 0.0f;
        EmbReal thisY = 0.0f;

        if (p->stitch_list->count > 0) {
                thisX = (float)p->stitch_list->stitch[0].x;
                thisY = (float)p->stitch_list->stitch[0].y;
        }
        for (i = 0; i < p->stitch_list->count; i++) {
                EmbStitch s = p->stitch_list->stitch[i];
                EmbReal deltaX, deltaY;
                EmbReal previousX = thisX;
                EmbReal previousY = thisY;
                thisX = s.x;
                thisY = s.y;
                deltaX = thisX - previousX;
                deltaY = thisY - previousY;
                if (s.flags & STOP) {
                        xxxEncodeStop(file, s);
                } else if (s.flags & END) {
                } else {
                        xxxEncodeStitch(file, deltaX * 10.0f, deltaY * 10.0f,
                                        s.flags);
                }
        }
}

char writeXxx(EmbPattern *pattern, FILE *file)
{
        int i;
        EmbRect rect;
        int endOfStitches;
        EmbReal width, height;
        //short to_write;
        //unsigned int n_stitches;
        //unsigned short n_threads;

        embp_correctForMaxStitchLength(pattern, 124, 127);

        fpad(file, 0, 0x17);
        emb_write_i32(file, (unsigned int)pattern->stitch_list->count);

        fpad(file, 0, 0x0C);
        emb_write_i16(file, (unsigned short)pattern->thread_list->count);

        fpad(file, 0, 0x02);

        rect = embp_bounds(pattern);
        width = rect.w;
        height = rect.h;
        emb_write_i16(file, (int16_t) (width * 10.0));
        emb_write_i16(file, (int16_t) (height * 10.0));

        /* TODO: xEnd from start point x=0 */
        emb_write_i16(file, (int16_t) (width / 2.0 * 10));
        /* TODO: yEnd from start point y=0 */
        emb_write_i16(file, (int16_t) (height / 2.0 * 10));
        /* TODO: left from start x = 0 */
        emb_write_i16(file, (int16_t) (width / 2.0 * 10));
        /* TODO: bottom from start y = 0 */
        emb_write_i16(file, (int16_t) (height / 2.0 * 10));

        fpad(file, 0, 0xC5);

        /* place holder for end of stitches */
        emb_write_i32(file, 0x0000);
        xxxEncodeDesign(file, pattern);
        endOfStitches = ftell(file);
        fseek(file, 0xFC, SEEK_SET);
        emb_write_u32(file, endOfStitches);
        fseek(file, 0, SEEK_END);
        /* is this really correct? */
        fwrite("\x7F\x7F\x03\x14\x00\x00", 1, 6, file);

        for (i = 0; i < pattern->thread_list->count; i++) {
                EmbColor c = pattern->thread_list->thread[i].color;
                fputc(0x00, file);
                embColor_write(file, c, 3);
        }
        for (i = 0; i < (22 - pattern->thread_list->count); i++) {
                emb_write_u32(file, 0x01000000);
        }
        fwrite("\x00\x01", 1, 2, file);
        return 1;
}

/*
 * ZSK FORMAT
 *
 * The ZSK USA Embroidery Format (.zsk)
 * The ZSK USA zsk format is stitch-only.
 */

char readZsk(EmbPattern *pattern, FILE *file)
{
        char b[3];
        unsigned char colorNumber;

        fseek(file, 0, SEEK_END);
        if (ftell(file) < 0x230) {
                return 0;
        }

        fseek(file, 0x230, SEEK_SET);
        colorNumber = fgetc(file);
        while (colorNumber != 0) {
                EmbThread t;
                embColor_read(file, &(t.color), 3);
                strcpy(t.catalogNumber, "");
                strcpy(t.description, "");
                embp_addThread(pattern, t);
                fseek(file, 0x48, SEEK_CUR);
                colorNumber = fgetc(file);
        }
        fseek(file, 0x2E, SEEK_CUR);

        while (fread(b, 1, 3, file) == 3) {
                int stitchType = NORMAL;
                if (b[0] & 0x04) {
                        b[2] = -b[2];
                }
                if (b[0] & 0x08) {
                        b[1] = -b[1];
                }
                if (b[0] & 0x02) {
                        stitchType = JUMP;
                }
                if (b[0] & 0x20) {
                        if (b[1] == 2) {
                                stitchType = TRIM;
                        } else if (b[1] == -1) {
                                break;
                        } else {
                                if (b[2] != 0) {
                                        colorNumber = b[2];
                                }
                                /* TODO: need to determine what b[1] is used for. */
                                stitchType = STOP;
                                embp_changeColor(pattern, colorNumber - 1);
                        }
                        b[1] = 0;
                        b[2] = 0;
                }
                embp_addStitchRel(pattern, b[1] / 10.0,
                                  b[2] / 10.0, stitchType, 0);
        }

        return 1;
}

/* based on the readZsk function */
char writeZsk(EmbPattern *pattern, FILE *file)
{
        int i;
        fpad(file, 0x00, 0x230);

        fprintf(file, "%c", pattern->thread_list->count);
        for (i = pattern->thread_list->count; i > 0; i--) {
                EmbThread t = pattern->thread_list->thread[i - 1];
                embColor_write(file, t.color, 3);
                fpad(file, 0x00, 0x48);
                fprintf(file, "%c", i - 1);
        }

        fpad(file, 0x00, 0x2E);

        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch st;
                unsigned char b[3];
                st = pattern->stitch_list->stitch[i];
                b[0] = 0;
                b[1] = st.x;
                b[2] = st.y;
                if (st.flags & JUMP) {
                        b[0] |= 0x02;
                }
                if (st.x < 0) {
                        b[0] |= 0x08;
                        b[1] = -st.x;
                }
                if (st.y < 0) {
                        b[0] |= 0x04;
                        b[2] = -st.y;
                }
                if (st.flags & TRIM) {
                        b[0] |= 0x20;
                        b[1] = 0x00;
                        b[2] = 0x00;
                }
                if (st.flags & STOP) {
                        b[0] |= 0x20;
                        b[1] = 0x00;
                        b[2] = st.color;
                }
                if (st.flags & END) {
                        b[0] |= 0x20;
                        b[1] = 0x80;
                        b[2] = 0x00;
                        fwrite(b, 1, 3, file);
                        break;
                }
                fwrite(b, 1, 3, file);
        }
        return 1;
}

/*
 * Libembroidery 1.0.0-alpha
 * https://www.libembroidery.org
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright 2018-2025 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * -----------------------------------------------------------------------------
 *
 * Only uses source from this directory or standard C libraries,
 * not including POSIX headers like unistd since this library
 * needs to support non-POSIX systems like Windows.
 *
 * -----------------------------------------------------------------------------
 *
 * The Geometry System
 */

extern EmbReal epsilon;

const char *justify_options[] = {
        "Left",
        "Center",
        "Right",
        "Aligned",
        "Middle",
        "Fit",
        "Top Left",
        "Top Center",
        "Top Right",
        "Middle Left",
        "Middle Center",
        "Middle Right",
        "Bottom Left",
        "Bottom Center",
        "Bottom Right",
        END_SYMBOL
};

const char *emb_error_desc[] = {
        "No error.",
        "Wrong type: this is unsupported usage.",
        "Division by zero.",
        "Unfinished."
};

/* Create an EmbVector from data. */
EmbVector emb_vector(EmbReal x, EmbReal y)
{
        EmbVector v;
        v.x = x;
        v.y = y;
        return v;
}

/* Finds the unit length vector a result in the same direction as a vector. */
EmbVector emb_vector_normalize(EmbVector vector)
{
        EmbVector result;
        EmbReal length = emb_vector_length(vector);
        result.x = vector.x / length;
        result.y = vector.y / length;
        return result;
}

/* The scalar multiple a magnitude of a vector. Returned as a vector. */
EmbVector emb_vector_scale(EmbVector vector, EmbReal magnitude)
{
        EmbVector result;
        result.x = vector.x * magnitude;
        result.y = vector.y * magnitude;
        return result;
}

/* The sum of two vectors returned as a vector. */
EmbVector emb_vector_add(EmbVector a, EmbVector b)
{
        EmbVector result;
        result.x = a.x + b.x;
        result.y = a.y + b.y;
        return result;
}

/* The average of two vectors returned as a vector. */
EmbVector emb_vector_average(EmbVector a, EmbVector b)
{
        EmbVector result;
        result.x = 0.5 * (a.x + b.x);
        result.y = 0.5 * (a.y + b.y);
        return result;
}

/* The difference between two vectors returned as a result. */
EmbVector emb_vector_subtract(EmbVector v1, EmbVector v2)
{
        EmbVector result;
        result.x = v1.x - v2.x;
        result.y = v1.y - v2.y;
        return result;
}

/* The dot product of two vectors returned as a EmbReal. */
EmbReal emb_vector_dot(EmbVector a, EmbVector b)
{
        return a.x * b.x + a.y * b.y;
}

/*
 * The "cross product" as vectors a and b returned as a real value.
 *
 * Technically, this is the magnitude of the cross product when the
 * embroidery is placed in the z=0 plane (since the cross product is defined for
 * 3-dimensional vectors).
 */
EmbReal emb_vector_cross(EmbVector a, EmbVector b)
{
        return a.x * b.y - a.y * b.x;
}

/*
 * Since we aren't using full 3D vector algebra here, all vectors are "vertical".
 * so this is like the product v1^{T} I_{2} v2 for our vectors a v1 and v2
 * so a "component-wise product". The result is stored at the pointer a result.
 */
EmbVector emb_vector_transpose_product(EmbVector v1, EmbVector v2)
{
        EmbVector result;
        result.x = v1.x * v2.x;
        result.y = v1.y * v2.y;
        return result;
}

/* The length or absolute value of the vector a vector. */
EmbReal emb_vector_length(EmbVector vector)
{
        return sqrt(vector.x * vector.x + vector.y * vector.y);
}

/* The x-component of the vector. */
EmbReal emb_vector_relativeX(EmbVector a1, EmbVector a2, EmbVector a3)
{
        EmbVector b, c;
        b = emb_vector_subtract(a1, a2);
        c = emb_vector_subtract(a3, a2);
        return emb_vector_dot(b, c);
}

/* The y-component of the vector. */
EmbReal emb_vector_relativeY(EmbVector a1, EmbVector a2, EmbVector a3)
{
        EmbVector b, c;
        b = emb_vector_subtract(a1, a2);
        c = emb_vector_subtract(a3, a2);
        return emb_vector_cross(b, c);
}

/* The angle, measured anti-clockwise from the x-axis, of a vector v. */
EmbReal emb_vector_angle(EmbVector v)
{
        return atan2(v.y, v.x);
}

/* The unit vector in the direction a angle. */
EmbVector emb_vector_unit(EmbReal alpha)
{
        EmbVector a;
        a.x = cos(alpha);
        a.y = sin(alpha);
        return a;
}

/* The distance between vectors "a" and "b" returned as a real value. */
EmbReal emb_vector_distance(EmbVector a, EmbVector b)
{
        EmbVector delta = emb_vector_subtract(a, b);
        return emb_vector_length(delta);
}

/* Translate a geometric object by the vector "delta". */
void emb_geometry_move(EmbGeometry *obj, EmbVector delta)
{
        switch (obj->type) {
        case EMB_ARC:{
                        EmbArc *arc = &(obj->object.arc);
                        arc->start = emb_vector_add(arc->start, delta);
                        arc->mid = emb_vector_add(arc->mid, delta);
                        arc->end = emb_vector_add(arc->end, delta);
                        return;
                }
        case EMB_CIRCLE:{
                        EmbCircle *circle = &(obj->object.circle);
                        circle->center = emb_vector_add(circle->center, delta);
                        return;
                }
        default:
                break;
        }
}

/* Approximate equals for vectors. */
int emb_approx(EmbVector point1, EmbVector point2)
{
        return (emb_vector_distance(point1, point2) < epsilon);
}

/* . */
EmbReal emb_apothem(EmbGeometry *g, EmbError *error)
{
        switch (g->type) {
        case EMB_ARC:{
                        *error = EMB_NO_ERR;
                        EmbReal radius = emb_radius(g, error);
                        if (*error) {
                                return 0.0;
                        }
                        EmbReal sagitta = emb_sagitta(g, error);
                        if (*error) {
                                return 0.0;
                        }
                        return fabs(radius - sagitta);
                }
        default:
                *error = EMB_WRONG_TYPE_ERR;
                break;
        }
        return 0.0;
}

/* FIXME */
EmbReal emb_sagitta(EmbGeometry *g, EmbError *error)
{
        *error = EMB_UNFINISHED_ERR;
        return 0.0;
}

/* FIXME */
EmbVector emb_start(EmbGeometry *g, EmbError *error)
{
        *error = EMB_UNFINISHED_ERR;
        return emb_vector(0.0, 0.0);
}

/* FIXME */
EmbVector emb_end(EmbGeometry *g, EmbError *error)
{
        *error = EMB_UNFINISHED_ERR;
        return emb_vector(0.0, 0.0);
}

/* FIXME */
EmbReal emb_width(EmbGeometry *g, EmbError *error)
{
        *error = EMB_NO_ERR;
        switch (g->type) {
        case EMB_CIRCLE:{
                        return 2.0f * g->object.circle.radius;
                }
        case EMB_ELLIPSE:{
                        return 2.0f * g->object.ellipse.radius.x;
                }
        default:
                *error = EMB_WRONG_TYPE_ERR;
                break;
        }
        return 1.0;
}

/* FIXME: finish all types. */
EmbReal emb_height(EmbGeometry *g, EmbError *error)
{
        *error = EMB_NO_ERR;
        switch (g->type) {
        case EMB_CIRCLE:{
                        return 2.0f * g->object.circle.radius;
                }
        case EMB_ELLIPSE:{
                        return 2.0f * g->object.ellipse.radius.y;
                }
        default:
                *error = EMB_WRONG_TYPE_ERR;
                break;
        }
        return 1.0;
}

/* FIXME: finish all types. */
EmbReal emb_radius(EmbGeometry *g, EmbError *error)
{
        *error = EMB_NO_ERR;
        switch (g->type) {
        case EMB_ARC:{
                        EmbReal incAngle = emb_included_angle(g, error);
                        EmbReal chord = emb_vector_length(emb_chord(g, error));
                        return fabs(chord / (2.0 * sin(incAngle / 2.0)));
                }
        default:
                *error = EMB_WRONG_TYPE_ERR;
                break;
        }
        return 1.0;
}

/* FIXME */
EmbReal emb_radius_major(EmbGeometry *g, EmbError *error)
{
        *error = EMB_NO_ERR;
        switch (g->type) {
        default:
                *error = EMB_WRONG_TYPE_ERR;
                break;
        }
        return 1.0;
}

/* FIXME */
EmbReal emb_radius_minor(EmbGeometry *g, EmbError *error)
{
        *error = EMB_NO_ERR;
        switch (g->type) {
        default:
                break;
        }
        return 1.0;
}

/* FIXME */
EmbReal emb_diameter_major(EmbGeometry *g, EmbError *error)
{
        *error = EMB_NO_ERR;
        switch (g->type) {
        default:
                break;
        }
        return 1.0;
}

/* FIXME */
EmbReal emb_diameter_minor(EmbGeometry *g, EmbError *error)
{
        switch (g->type) {
        default:
                break;
        }
        return 1.0;
}

/* FIXME */
EmbReal emb_diameter(EmbGeometry *g, EmbError *error)
{
        switch (g->type) {
        default:
                break;
        }
        return 1.0;
}

/* . */
EmbVector emb_quadrant(EmbGeometry *geometry, int degrees, EmbError *error)
{
        EmbVector v;
        EmbReal radius = 1.0;
        v.x = 0.0;
        v.y = 0.0;
        switch (geometry->type) {
        case EMB_CIRCLE:{
                        v = geometry->object.circle.center;
                        radius = geometry->object.circle.radius;
                        break;
                }
        case EMB_ELLIPSE:{
                        v = geometry->object.ellipse.center;
                        if (degrees % 180 == 0) {
                                radius = geometry->object.ellipse.radius.x;
                        } else {
                                radius = geometry->object.ellipse.radius.y;
                        }
                        break;
                }
        default:
                break;
        }
        EmbReal rot = radians( /* rotation() + */ degrees);
        v.x += radius * cos(rot);
        v.y += radius * sin(rot);
        return v;
}

/* . */
EmbReal emb_angle(EmbGeometry *geometry, EmbError *error)
{
        EmbVector v = emb_vector_subtract(geometry->object.line.end,
                                          geometry->object.line.start);
        EmbReal angle = emb_vector_angle(v) /* - rotation() */ ;
        return fmod(angle + 360.0, 360.0);
}

/* . */
EmbReal emb_start_angle(EmbGeometry *geometry, EmbError *error)
{
        switch (geometry->type) {
        case EMB_ARC:{
                        *error = EMB_NO_ERR;
                        EmbVector center = emb_center(geometry, error);
                        if (*error) {
                                return 0.0;
                        }
                        EmbVector v = emb_vector_subtract(center,
                                                          geometry->object.arc.
                                                          start);
                        EmbReal angle = emb_vector_angle(v) /* - rotation() */ ;
                        return fmod(angle + 360.0, 360.0);
                }
        default:
                break;
        }
        return 0.0f;
}

/* . */
EmbReal emb_end_angle(EmbGeometry *geometry, EmbError *error)
{
        switch (geometry->type) {
        case EMB_ARC:{
                        *error = EMB_NO_ERR;
                        EmbVector center = emb_center(geometry, error);
                        if (*error) {
                                return 0.0;
                        }
                        EmbVector v = emb_vector_subtract(center,
                                                          geometry->object.arc.
                                                          end);
                        EmbReal angle = emb_vector_angle(v) /* - rotation() */ ;
                        return fmod(angle + 360.0, 360.0);
                }
        default:
                break;
        }
        return 0.0f;
}

/* . */
EmbReal emb_arc_length(EmbGeometry *g, EmbError *error)
{
        switch (g->type) {
        case EMB_ARC:{
                        *error = EMB_NO_ERR;
                        EmbReal radius = emb_radius(g, error);
                        if (*error) {
                                return 0.0;
                        }
                        EmbReal angle = emb_included_angle(g, error);
                        if (*error) {
                                return 0.0;
                        }
                        return radians(angle) * radius;
                }
        default:
                break;
        }
        return 0.0;
}

/* . */
EmbReal emb_area(EmbGeometry *g, EmbError *error)
{
        switch (g->type) {
        case EMB_ARC:{
                        /* Area of a circular segment */
                        *error = EMB_NO_ERR;
                        EmbReal r = emb_radius(g, error);
                        if (*error) {
                                return 0.0;
                        }
                        EmbReal theta = emb_included_angle(g, error);
                        if (*error) {
                                return 0.0;
                        }
                        theta = radians(theta);
                        return ((r * r) / 2) * (theta - sin(theta));
                }
        case EMB_CIRCLE:{
                        EmbReal r = g->object.circle.radius;
                        return embConstantPi * r * r;
                }
        case EMB_RECT:
                return g->object.rect.w * g->object.rect.h;
        case EMB_IMAGE:
        default:
                break;
        }
        /* The area of most objects defaults to the area of the rectangle described by the
         * object's width and height.
         */
        EmbReal width = emb_width(g, error);
        if (*error) {
                return 0.0;
        }
        EmbReal height = emb_height(g, error);
        if (*error) {
                return 0.0;
        }
        return fabs(width * height);
}

/* FIXME */
EmbVector emb_center(EmbGeometry *g, EmbError *error)
{
        switch (g->type) {
        case EMB_ARC:{
/* FIXME: Calculates the CenterPoint of the Arc */

#if 0
                        EmbArc arc = g.object.arc;
                        int emb_error = 0;
                        EmbVector center;
                        EmbVector a_vec, b_vec, aMid_vec, bMid_vec, aPerp_vec,
                            bPerp_vec, pa, pb;
                        EmbLine line1, line2;
                        EmbReal paAngleInRadians, pbAngleInRadians;
                        a_vec = emb_vector_subtract(arc.mid, arc.start);
                        aMid_vec = emb_vector_average(arc.mid, arc.start);

                        paAngleInRadians =
                            emb_vector_angle(a_vec) + (embConstantPi / 2.0);
                        pa = emb_vector_unit(paAngleInRadians);
                        aPerp_vec = emb_vector_add(aMid_vec, pa);

                        b_vec = emb_vector_subtract(arc.end, arc.mid);
                        bMid_vec = emb_vector_average(arc.end, arc.mid);

                        pbAngleInRadians =
                            emb_vector_angle(b_vec) + (embConstantPi / 2.0);
                        pb = emb_vector_unit(pbAngleInRadians);
                        bPerp_vec = emb_vector_add(bMid_vec, pb);

                        line1.start = aMid_vec;
                        line1.end = aPerp_vec;
                        line2.start = bMid_vec;
                        line2.end = bPerp_vec;
                        center =
                            emb_line_intersectionPoint(line1, line2,
                                                       &emb_error);
                        if (emb_error) {
                                puts("ERROR: no intersection, cannot find arcCenter.");
                        }
                        return center;
#endif
                        *error = EMB_UNFINISHED_ERR;
                        break;
                }
        default:
                *error = EMB_WRONG_TYPE_ERR;
                break;
        }
        return emb_vector(0.0, 0.0);
}

/* . */
EmbVector emb_chord(EmbGeometry *g, EmbError *error)
{
        switch (g->type) {
        case EMB_ARC:
        case EMB_LINE:
        case EMB_PATH:
        case EMB_POLYLINE:{
                        *error = EMB_NO_ERR;
                        EmbVector start = emb_start(g, error);
                        if (*error) {
                                return emb_vector(0.0, 0.0);
                        }
                        EmbVector end = emb_end(g, error);
                        if (*error) {
                                return emb_vector(0.0, 0.0);
                        }
                        return emb_vector_subtract(end, start);
                }
        default:
                *error = EMB_WRONG_TYPE_ERR;
                break;
        }
        return emb_vector(0.0, 0.0);
}

/* . */
EmbReal emb_included_angle(EmbGeometry *g, EmbError *error)
{
        switch (g->type) {
        case EMB_ARC:{
                        /* Properties of a Circle - Get the Included Angle - Reference: ASD9 */
                        *error = EMB_NO_ERR;
                        EmbReal chord = emb_chord_length(g, error);
                        if (*error) {
                                return 0.0;
                        }
                        EmbReal rad = emb_radius(g, error);
                        if (*error) {
                                return 0.0;
                        }
                        if (chord <= 0 || rad <= 0) {
                                /* Prevents division by zero and non-existant circles. */
                                *error = EMB_DIV_ZERO_ERR;
                                return 0.0;
                        }

                        /* NOTE: Due to floating point rounding errors, we need to clamp the
                         * quotient so it is in the range [-1, 1]
                         * If the quotient is out of that range, then the result of asin()
                         * will be NaN.
                         */
                        EmbReal quotient = chord / (2.0 * rad);
                        quotient = EMB_MIN(1.0, quotient);
                        /* NOTE: 0 rather than -1 since we are enforcing a positive chord and
                         * radius
                         */
                        quotient = EMB_MAX(0.0, quotient);

                        return degrees(2.0 * asin(quotient));
                }
        default:
                break;
        }
        return 0.0;
}

/* . */
char emb_clockwise(EmbGeometry *geometry, EmbError *error)
{
        switch (geometry->type) {
        case EMB_ARC:{
                        /* NOTE: Y values are inverted here on purpose. */
                        geometry->object.arc.start.y =
                            -geometry->object.arc.start.y;
                        geometry->object.arc.mid.y =
                            -geometry->object.arc.start.y;
                        geometry->object.arc.end.y =
                            -geometry->object.arc.end.y;
                        return emb_arc_clockwise(*geometry);
                }
        default:
                break;
        }
        return 0;
}

/* . */
EmbError emb_set_start_angle(EmbGeometry *geometry, EmbReal angle)
{
        printf("%f\n", angle);
        switch (geometry->type) {
        case EMB_ARC:{
                        /* TODO: ArcObject setObjectStartAngle */
                        break;
                }
        default:
                break;
        }
        return EMB_NO_ERR;
}

/* . */
EmbError emb_set_end_angle(EmbGeometry *geometry, EmbReal angle)
{
        printf("%f\n", angle);
        switch (geometry->type) {
        case EMB_ARC:{
                        /* TODO: ArcObject setObjectEndAngle */
                        break;
                }
        default:
                break;
        }
        return EMB_NO_ERR;
}

/* . */
EmbError emb_set_start_point(EmbGeometry *geometry, EmbVector point)
{
        switch (geometry->type) {
        case EMB_ARC:{
                        geometry->object.arc.start = point;
                        /* calculateData(); */
                        break;
                }
        default:
                break;
        }
        return EMB_NO_ERR;
}

/* . */
EmbError emb_set_mid_point(EmbGeometry *geometry, EmbVector point)
{
        switch (geometry->type) {
        case EMB_ARC:{
                        geometry->object.arc.mid = point;
                        /* calculateData(); */
                        break;
                }
        default:
                break;
        }
        return EMB_NO_ERR;
}

/* . */
EmbError emb_set_end_point(EmbGeometry *geometry, EmbVector point)
{
        switch (geometry->type) {
        case EMB_ARC:{
                        geometry->object.arc.end = point;
                        /* calculateData(); */
                        break;
                }
        default:
                break;
        }
        return EMB_NO_ERR;
}

/* . */
EmbError emb_set_radius(EmbGeometry *g, EmbReal radius)
{
        switch (g->type) {
        case EMB_ARC:{
                        EmbVector delta;
                        float rad;
                        if (radius <= 0.0f) {
                                rad = 0.0000001f;
                        } else {
                                rad = radius;
                        }

                        EmbError error = EMB_NO_ERR;
                        EmbVector center = emb_center(g, &error);
                        if (error) {
                                return error;
                        }
                        EmbReal delta_length;

                        delta =
                            emb_vector_subtract(g->object.arc.start, center);
                        delta_length = emb_vector_length(delta);
                        delta = emb_vector_scale(delta, rad / delta_length);
                        g->object.arc.start = emb_vector_add(center, delta);

                        delta = emb_vector_subtract(g->object.arc.mid, center);
                        delta_length = emb_vector_length(delta);
                        delta = emb_vector_scale(delta, rad / delta_length);
                        g->object.arc.mid = emb_vector_add(center, delta);

                        delta = emb_vector_subtract(g->object.arc.end, center);
                        delta_length = emb_vector_length(delta);
                        delta = emb_vector_scale(delta, rad / delta_length);
                        g->object.arc.end = emb_vector_add(center, delta);
                        return EMB_NO_ERR;
                }
        case EMB_CIRCLE:
                g->object.circle.radius = radius;
                return EMB_NO_ERR;
        default:
                break;
        }
        return EMB_WRONG_TYPE_ERR;
}

/* . */
EmbError emb_set_diameter(EmbGeometry *geometry, EmbReal diameter)
{
        switch (geometry->type) {
        case EMB_CIRCLE:{
                        geometry->object.circle.radius = diameter / 2.0;
                        /* FIXME: updatePath(); */
                        break;
                }
        default:
                break;
        }
        return EMB_NO_ERR;
}

/*
 * Sets the area of the geometry if that is meaningful, otherwise
 * return EMB_WRONG_TYPE_ERR.
 */
EmbError emb_set_area(EmbGeometry *geometry, EmbReal area)
{
        switch (geometry->type) {
        case EMB_CIRCLE:{
                        EmbReal radius = sqrt(area / embConstantPi);
                        emb_set_radius(geometry, radius);
                        return EMB_NO_ERR;
                }
        default:
                break;
        }
        return EMB_WRONG_TYPE_ERR;
}

/*
 * Sets the circumference of the geometry if that is meaningful, otherwise
 * return EMB_WRONG_TYPE_ERR.
 */
EmbError emb_set_circumference(EmbGeometry *geometry, EmbReal circumference)
{
        switch (geometry->type) {
        case EMB_CIRCLE:{
                        EmbReal diameter = circumference / embConstantPi;
                        emb_set_diameter(geometry, diameter);
                        return EMB_NO_ERR;
                }
        default:
                break;
        }
        return EMB_WRONG_TYPE_ERR;
}

/* . */
EmbError emb_set_radius_major(EmbGeometry *geometry, EmbReal radius)
{
        emb_set_diameter_major(geometry, radius * 2.0);
        return EMB_NO_ERR;
}

/* . */
EmbError emb_set_radius_minor(EmbGeometry *geometry, EmbReal radius)
{
        emb_set_diameter_minor(geometry, radius * 2.0);
        return EMB_NO_ERR;
}

/* . */
EmbError emb_set_diameter_major(EmbGeometry *geometry, EmbReal diameter)
{
        switch (geometry->type) {
        case EMB_ELLIPSE:
                /* FIXME: Identify longer axis and replace. */
                geometry->object.ellipse.radius.x = diameter;
                break;
        default:
                break;
        }
        return EMB_NO_ERR;
}

/* . */
EmbError emb_set_diameter_minor(EmbGeometry *geometry, EmbReal diameter)
{
        switch (geometry->type) {
        case EMB_ELLIPSE:
                /* FIXME: Identify longer axis and replace. */
                geometry->object.ellipse.radius.x = diameter;
                break;
        default:
                break;
        }
        return EMB_NO_ERR;
}

/* . */
void emb_geometry_path(EmbGeometry *geometry, char *path, EmbError *error)
{
}

#if 0
/* . */
QColor emb_color(EmbGeometry *geometry)
{
        return data.objPen.color();
}

/* . */
QRgb emb_color_rgb(EmbGeometry *geometry)
{
        return data.objPen.color().rgb();
}

/* . */
Qt::PenStyle emb_line_type(EmbGeometry *geometry)
{
        return data.objPen.style();
}

/* . */
EmbReal emb_line_weight(EmbGeometry *geometry)
{
        return data.lwtPen.widthF();
}

/* . */
EmbVector emb_rubber_point(EmbGeometry *geometry, const char *key)
{
        return;
}

/* . */
QString emb_rubber_text(EmbGeometry *geometry, const char *key)
{
        return;
}

/* . */
EmbVector emb_pos(EmbGeometry *geometry)
{
        return scenePos();
}

/* . */
EmbReal emb_x(EmbGeometry *geometry)
{
        return scenePos().x();
}

/* . */
EmbReal emb_y(EmbGeometry *geometry)
{
        return scenePos().y();
}

/* . */
EmbVector emb_center(EmbGeometry *geometry)
{
        return;
}

/* . */
EmbReal emb_center_x(EmbGeometry *geometry)
{
        return scenePos().x();
}

/* . */
EmbReal emb_center_y(EmbGeometry *geometry)
{
        return scenePos().y();
}

/* . */
EmbReal emb_radius(EmbGeometry *geometry)
{
        return rect().width() / 2.0 * scale();
}

/* . */
EmbReal emb_diameter(EmbGeometry *geometry)
{
        return rect().width() * scale();
}
#endif

/* . */
EmbReal emb_circumference(EmbGeometry *geometry, EmbError *error)
{
        switch (geometry->type) {
        case EMB_CIRCLE:{
                        return 2.0 * embConstantPi *
                            geometry->object.circle.radius;
                }
        default:
                break;
        }
        return 1.0;
}

#if 0
/* . */
EmbVector emb_end_point_1(EmbGeometry *geometry)
{
        return emb_pos(geometry);
}

/* . */
EmbVector emb_end_point_2(EmbGeometry *geometry)
{
        return emb_pos(geometry);
}

/* . */
EmbVector emb_start_point(EmbGeometry *geometry)
{
        return;
}

/* . */
EmbVector emb_mid_point(EmbGeometry *geometry)
{
        return;
}

/* . */
EmbVector emb_end_point(EmbGeometry *geometry)
{
        return;
}

/* . */
EmbVector emb_delta(EmbGeometry *geometry)
{
        return objectEndPoint2(geometry) - objectEndPoint1(geometry);
}

/* . */
EmbVector top_left(EmbGeometry *geometry)
{
}

/* . */
EmbVector top_right(EmbGeometry *geometry)
{
}

/* . */
EmbVector bottom_left(EmbGeometry *geometry)
{
}

/* . */
EmbVector bottom_right(EmbGeometry *geometry)
{
}

/* . */
void update_rubber(QPainter * painter);
{
}

/* . */
void update_rubber_grip(QPainter * painter);
{
}

/* . */
void update_leader(EmbGeometry * geometry);
{
}

/* . */
void update_path(EmbGeometry * geometry);
{
}

/* . */
void update_path(const QPainterPath & p);
{
}

/* . */
void update_arc_rect(EmbReal radius);
{
}

/* . */
EmbReal emb_length(EmbGeometry *geometry)
{
        return line().length() * scale();
}

/* . */
void emb_set_end_point_1(EmbGeometry *geometry, const QPointF & endPt1)
{
}

/* . */
void emb_set_end_point_1(EmbGeometry *geometry, EmbReal x1, EmbReal y1)
{
}

/* . */
void emb_set_end_point_2(EmbGeometry *geometry, QPointF endPt2)
{
}

/* . */
void emb_set_end_point_2(EmbGeometry *geometry, EmbReal x2, EmbReal y2)
{
}

/* . */
void emb_set_x1(EmbReal x)
{
        emb_set_EndPoint1(x, objectEndPoint1().y());
}

/* . */
void emb_set_y1(EmbReal y)
{
        emb_set_EndPoint1(objectEndPoint1().x(), y);
}

/* . */
void emb_set_x2(EmbReal x)
{
        emb_set_EndPoint2(x, objectEndPoint2().y());
}

/* . */
void emb_set_y2(EmbReal y)
{
        emb_set_EndPoint2(objectEndPoint2().x(), y);
}

/* . */
QRectF emb_rect(EmbGeometry *geometry)
{
        return path().boundingRect();
}

/* . */
void emb_setRect(const QRectF & r)
{
        QPainterPath p;
        p.addRect(r);
        setPath(p);
}

/* . */
void emb_setRect(EmbReal x, EmbReal y, EmbReal w, EmbReal h)
{
        QPainterPath p;
        p.addRect(x, y, w, h);
        setPath(p);
}

/* . */
QLineF line(EmbGeometry *geometry)
{
        return data.objLine;
}

/* . */
void emb_setLine(const QLineF & li)
{
        QPainterPath p;
        p.moveTo(li.p1());
        p.lineTo(li.p2());
        setPath(p);
        data.objLine = li;
}

/* . */
void emb_set_line(EmbReal x1, EmbReal y1, EmbReal x2, EmbReal y2)
{
        QPainterPath p;
        p.moveTo(x1, y1);
        p.lineTo(x2, y2);
        setPath(p);
        data.objLine.setLine(x1, y1, x2, y2);
}

/* . */
void emb_set_pos(QPointF point)
{
        setPos(point.x(), point.y());
}

/* . */
void emb_set_pos(EmbGeometry *geometry, EmbReal x, EmbReal y)
{
        setPos(x, y);
}

/* . */
void emb_set_x(EmbGeometry *geometry, EmbReal x)
{
        emb_set_pos(geometry, x, emb_y(geometry));
}

/* . */
void emb_set_y(EmbGeometry *geometry, EmbReal y)
{
        emb_set_pos(geometry, emb_x(geometry), y);
}

/* . */
void emb_set_Rect(EmbReal x1, EmbReal y1, EmbReal x2, EmbReal y2)
{
}

/* . */
virtual QRectF boundingRect(EmbGeometry *geometry)
{
}

/* . */
virtual QPainterPath shape(EmbGeometry *geometry)
{
        return path();
}

/* . */
void emb_set_Color(const QColor & color)
{
}

/* . */
void emb_set_ColorRGB(QRgb rgb)
{
}

/* . */
void emb_set_LineType(Qt::PenStyle lineType)
{
}

/* . */
void emb_set_LineWeight(EmbReal lineWeight)
{
}

/* . */
void emb_set_Path(const QPainterPath & p)
{
        setPath(p);
}

/* . */
void emb_set_rubber_mode(int mode)
{
        data.objRubberMode = mode;
}

/* . */
void emb_set_rubber_point(const QString & key, const QPointF & point)
{
        data.objRubberPoints.insert(key, point);
}

/* . */
void emb_set_rubber_text(const QString & key, const QString & txt)
{
        data.objRubberTexts.insert(key, txt);
}

/* . */
void
draw_rubber_line(const QLineF & rubLine, QPainter *painter =
                 0, const char *colorFromScene = 0)
{
}

/* . */
QPen lineWeightPen(EmbGeometry *geometry)
{
        return data.lwtPen;
}

/* . */
void emb_real_render(QPainter *painter, const QPainterPath & renderPath)
{
}

/* . */
void emb_set_center(EmbVector point)
{
}

/* . */
void emb_set_center(const QPointF & center)
{
}

/* . */
void emb_set_center_x(EmbGeometry *geometry, EmbReal centerX)
{
}

/* . */
void emb_set_center_y(EmbGeometry *geometry, EmbReal centerY)
{
}

/* . */
void emb_calculate_data(EmbGeometry *geometry)
{
}

/* . */
void emb_set_size(EmbGeometry *geometry, EmbReal width, EmbReal height)
{
}

/* . */
QPainterPath emb_object_copy_path(EmbGeometry *geometry)
{
}

/* . */
QPainterPath emb_object_save_path(EmbGeometry *geometry)
{
}

/* . */
QList < QPainterPath > emb_object_save_path_list(EmbGeometry *geometry)
{
        return subPathList();
}

/* . */
QList < QPainterPath > emb_sub_path_list(EmbGeometry *geometry)
{
        return;
}

#endif

/* Our generic object interface backends to each individual type.
 * The caller defines what the type is.
 */
EmbGeometry *emb_init(int type_in)
{
        EmbGeometry *obj = (EmbGeometry *) malloc(sizeof(EmbGeometry));
        obj->type = type_in;
        obj->color.r = 0;
        obj->color.g = 0;
        obj->color.b = 0;

        /*
           // QGraphicsItem* parent
           debug_message("BaseObject Constructor()");

           objPen.setCapStyle(RoundCap);
           objPen.setJoinStyle(RoundJoin);
           lwtPen.setCapStyle(RoundCap);
           lwtPen.setJoinStyle(RoundJoin);

           objID = QDateTime::currentMSecsSinceEpoch();
         */

        switch (obj->type) {
        case EMB_ARC:{
                        /*
                           obj = emb_arc(1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
                           emb_arc_init(EmbArc arc_in, unsigned int rgb, int lineType)
                           arc = arc_in;

                           setFlag(ItemIsSelectable, true);

                           calculateArcData(arc);

                           setColor(rgb);
                           setLineType(lineType);
                           setLineWeight(0.35); //TODO: pass in proper lineweight
                           setPen(objPen);
                         */
                        break;
                }
        }
        return obj;
}

/* Free the memory occupied by a non-stitch geometry object.
 *
 * Pointer to geometry memory.
 */
void emb_free(EmbGeometry *obj)
{
        switch (obj->type) {
        case EMB_ARC:{
                        return;
                }
        case EMB_CIRCLE:{
                        return;
                }
        case EMB_ELLIPSE:{
                        return;
                }
        default:
                return;
        }
}

/* Calculate the bounding box of geometry a obj based on what kind of
 * geometric object it is.
 *
 * obj A pointer to the geometry memory.
 * Returns an EmbRect, the bounding box in the same scale as the input geometry.
 *
 * In the case of a failure the bounding box returned is always the unit square
 * with top left corner at (0, 0).
 */
EmbRect emb_boundingRect(EmbGeometry *obj)
{
        EmbRect r;
        if (obj->type == EMB_ARC) {
                /*
                   arcRect.setWidth(radius*2.0);
                   arcRect.setHeight(radius*2.0);
                   arcRect.moveCenter(EmbVector(0,0));
                   setRect(arcRect);
                 */
        }
        r.y = 0.0;
        r.x = 0.0;
        r.w = 1.0;
        r.h = 1.0;
        /*
           "Base"
           //If gripped, force this object to be drawn even if it is offscreen
           if (objectRubberMode() == OBJ_RUBBER_GRIP)
           return scene()->sceneRect();
           return path().boundingRect();
         */
        return r;
}

/*
 * Create an arc from data.
 *
 * ------------------------------------------------------------
 *
 * The EmbArc is implicitly an elliptical arc not a circular one
 * because of our need to cover all of the SVG spec. Note that
 * the circlar arcs are a subset of the elliptical arcs.
 *
 * TODO: some of these formulae may assume that the arc is circular,
 * correct for elliptic versions.
 *
 * Returns an EmbGeometry. It is created on the stack.
 *
 * Note that the default arc is the semicircular arc of the circle of radius
 * arc.
 */
EmbGeometry
emb_arc(EmbReal x1, EmbReal y1, EmbReal x2, EmbReal y2, EmbReal x3, EmbReal y3)
{
        EmbGeometry g;
        g.object.arc.start = emb_vector(x1, y1);
        g.object.arc.mid = emb_vector(x2, y2);
        g.object.arc.end = emb_vector(x3, y3);
        g.type = EMB_ARC;
        return g;
}

/* Calculus based approach at determining whether a polygon is clockwise or counterclockwise.
 * Returns true if arc is clockwise.
 */
char emb_arc_clockwise(EmbGeometry g)
{
        if (g.type != EMB_ARC) {
                return 0;
        }
        EmbArc arc = g.object.arc;
        EmbReal edge1 = (arc.mid.x - arc.start.x) * (arc.mid.y + arc.start.y);
        EmbReal edge2 = (arc.end.x - arc.mid.x) * (arc.end.y + arc.mid.y);
        EmbReal edge3 = (arc.start.x - arc.end.x) * (arc.start.y + arc.end.y);
        if (edge1 + edge2 + edge3 >= 0.0) {
                return 1;
        }
        return 0;
}

/* Calculates Arc Geometry from Bulge Data.
 * Returns false if there was an error calculating the data.
    Calculate the Sagitta Angle (from chordMid to arcMid)
    if (*clockwise) sagittaAngleInRadians = chordAngleInRadians + radians(90.0);
    else           sagittaAngleInRadians = chordAngleInRadians - radians(90.0);

    Calculate the Arc MidPoint
    fx = emb_arc_sagitta(arc) * cos(sagittaAngleInRadians);
    fy = emb_arc_sagitta(arc) * sin(sagittaAngleInRadians);
    arc->mid.x = *chordMidX + fx;
    arc->mid.y = *chordMidY + fy;

    Convert the Included Angle from Radians to Degrees
    *incAngleInDegrees = degrees(incAngleInRadians);

    return 1;
}
 */

EmbError emb_set_center(EmbGeometry *g, EmbVector point)
{
        switch (g->type) {
        case EMB_ARC:{
                        EmbError error = EMB_NO_ERR;
                        EmbVector delta;
                        EmbVector old_center = emb_center(g, &error);
                        delta = emb_vector_subtract(point, old_center);
                        g->object.arc.start =
                            emb_vector_add(g->object.arc.start, delta);
                        g->object.arc.mid =
                            emb_vector_add(g->object.arc.mid, delta);
                        g->object.arc.end =
                            emb_vector_add(g->object.arc.end, delta);
                        break;
                }
        default:
                break;
        }
        return EMB_NO_ERR;
}

void emb_set_color(EmbGeometry *obj, EmbColor color)
{
        obj->color = color;
        /*
           objPen.setColor(color);
           lwtPen.setColor(color);
         */
}

void emb_set_color_rgb(EmbGeometry *obj, unsigned int rgb)
{
        printf("%p", obj);
        printf("%d", rgb);
        /*
           objPen.setColor(QColor(rgb));
           lwtPen.setColor(QColor(rgb));
         */
}

void emb_set_linetype(EmbGeometry *obj, int lineType)
{
        printf("%p %d\n", obj, lineType);
        /*
           objPen.setStyle(lineType);
           lwtPen.setStyle(lineType);
         */
}

void emb_set_line_weight(EmbGeometry *obj, float lineWeight)
{
        printf("%p %f\n", obj, lineWeight);
        /*
           objPen.setWidthF(0); //NOTE: The objPen will always be cosmetic

           if (lineWeight < 0) {
           if (lineWeight == OBJ_LWT_BYLAYER) {
           lwtPen.setWidthF(0.35); //TODO: getLayerLineWeight
           }
           else if (lineWeight == OBJ_LWT_BYBLOCK) {
           lwtPen.setWidthF(0.35); //TODO: getBlockLineWeight
           }
           else {
           QMessageBox::warning(0, translate("Error - Negative Lineweight"),
           translate("Lineweight: %1")
           .arg(std::string().setNum(lineWeight)));
           debug_message("Lineweight cannot be negative! Inverting sign.");
           lwtPen.setWidthF(-lineWeight);
           }
           }
           else {
           lwtPen.setWidthF(lineWeight);
           }
         */
}

EmbVector emb_base_rubber_point(EmbGeometry *obj, const char *key)
{
        EmbVector v;
        v.x = 0.0;
        v.y = 0.0;
        printf("%p %s\n", obj, key);
        /*
           if (objRubberPoints.contains(key)) {
           return objRubberPoints.value(key);
           }

           QGraphicsScene* gscene = scene();
           if (gscene) {
           return scene()->attribute("SCENE_QSNAP_POINT").toPointF();
           }
         */
        return v;
}

const char *emb_base_rubber_text(EmbGeometry *obj, const char *key)
{
        printf("%p %s\n", obj, key);
        /*
           if (objRubberTexts.contains(key))
           return objRubberTexts.value(key);
         */
        return "";
}

/*
 * TODO: pass in proper lineweight
void dim_leader_init(EmbLine line, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Leader Dimension");

    setFlag(ItemIsSelectable, true);

    curved = false;
    filled = true;
    setEndPoint1(x1, y1);
    setEndPoint2(x2, y2);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35);
    setPen(objPen);
}
*/

/*
void
emb_dimleader_set_end_point_1(EmbVector endPt1)
{
    EmbVector endPt2 = objectEndPoint2();
    EmbVector delta = emb_vector_subtract(endPt2, endPt1);
    setRotation(0);
    setLine(0, 0, dx, dy);
    setPos(endPt1);
    updateLeader();
}

void
dimleader_set_end_point_2(EmbVector endPt2)
{
    EmbVector delta;
    EmbVector endPt1 = scenePos();
    emb_vector_subtract(endPt2, endPt1, &delta);
    setRotation(0);
    setLine(0, 0, delta.x, delta.y);
    setPos(endPt1);
    updateLeader();
}

EmbVector
dimleader_end_point_1()
{
    return scenePos();
}

EmbVector
dimleader_objectEndPoint2()
{
    EmbLine lyne = line();
    float rot = radians(rotation());
    EmbVector point2;
    point2.x = lyne.x2()*scale();
    point2.y = lyne.y2()*scale();
    EmbVector rot = emb_vector_rotate(point2, alpha);

    return (scenePos() + rot);
}

EmbVector dimleader_objectMidPoint()
{
    EmbVector mp = line().pointAt(0.5) * scale();
    float alpha = radians(rotation());
    EmbVector rotMid = emb_vector_rotate(mp, alpha);
    return scenePos() + rotMid;
}

float dimleader_objectAngle()
{
    return fmodf(line().angle() - rotation(), 360.0);
}

//TODO: Make arrow style, angle, length and line angle and length customizable.
void
dimleader_updateLeader()
{
    int arrowStyle = Closed;
    float arrowStyleAngle = 15.0;
    float arrowStyleLength = 1.0;
    float lineStyleAngle = 45.0;
    float lineStyleLength = 1.0;

    EmbLine lyne = line();
    float angle = lyne.angle();
    EmbVector ap0 = lyne.p1();
    EmbVector lp0 = lyne.p2();

    //Arrow
    EmbLine lynePerp(lyne.pointAt(arrowStyleLength/lyne.length()) ,lp0);
    lynePerp.setAngle(angle + 90);
    EmbLine lyne1(ap0, lp0);
    EmbLine lyne2(ap0, lp0);
    lyne1.setAngle(angle + arrowStyleAngle);
    lyne2.setAngle(angle - arrowStyleAngle);
    EmbVector ap1;
    EmbVector ap2;
    lynePerp.intersects(lyne1, &ap1);
    lynePerp.intersects(lyne2, &ap2);

    //Math Diagram
    //                 .(ap1)                     .(lp1)
    //                /|                         /|
    //               / |                        / |
    //              /  |                       /  |
    //             /   |                      /   |
    //            /    |                     /    |
    //           /     |                    /     |
    //          /      |                   /      |
    //         /       |                  /       |
    //        /+(aSA)  |                 /+(lSA)  |
    // (ap0)./__(aSL)__|__________(lp0)./__(lSL)__|
    //       \ -(aSA)  |                \ -(lSA)  |
    //        \        |                 \        |
    //         \       |                  \       |
    //          \      |                   \      |
    //           \     |                    \     |
    //            \    |                     \    |
    //             \   |                      \   |
    //              \  |                       \  |
    //               \ |                        \ |
    //                \|                         \|
    //                 .(ap2)                     .(lp2)

    if (arrowStyle == Open) {
        arrowStylePath = QPainterPath();
        arrowStylePath.moveTo(ap1);
        arrowStylePath.lineTo(ap0);
        arrowStylePath.lineTo(ap2);
        arrowStylePath.lineTo(ap0);
        arrowStylePath.lineTo(ap1);
    }
    else if (arrowStyle == Closed) {
        arrowStylePath = QPainterPath();
        arrowStylePath.moveTo(ap1);
        arrowStylePath.lineTo(ap0);
        arrowStylePath.lineTo(ap2);
        arrowStylePath.lineTo(ap1);
    }
    else if (arrowStyle == Dot) {
        arrowStylePath = QPainterPath();
        arrowStylePath.addEllipse(ap0, arrowStyleLength, arrowStyleLength);
    }
    else if (arrowStyle == Box) {
        arrowStylePath = QPainterPath();
        float side = EmbLine(ap1, ap2).length();
        EmbRect ar0(0, 0, side, side);
        ar0.moveCenter(ap0);
        arrowStylePath.addRect(ar0);
    }
    else if (arrowStyle == Tick) {
    }

    lineStylePath = QPainterPath();
    lineStylePath.moveTo(ap0);
    lineStylePath.lineTo(lp0);
}
*/

void emb_ellipse_main(void)
{
        /*
           initCommand();
           clearSelection();
           view.ui_mode = "ELLIPSE_MODE_MAJORDIAMETER_MINORRADIUS";
           global.point1 = zero_vector;
           global.point2 = zero_vector;
           global.point3 = zero_vector;
         */
}

/*
void emb_ellipse(float centerX, float centerY, float width, float height, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("EllipseObject Constructor()");
    init(centerX, centerY, width, height, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void emb_ellipse(EllipseObject* obj, QGraphicsItem* parent)
{
    debug_message("EllipseObject Constructor()");
    if (obj) {
        init(obj->objectCenterX(), obj->objectCenterY(), obj->objectWidth(), obj->objectHeight(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
    }
}

void image_init(EmbRect rect, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Image");

    setFlag(ItemIsSelectable, true);

    setRect(rect);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void image_setRect(float x, float y, float w, float h)
{
    setPos(x, y);
    setRect(0, 0, w, h);
    updatePath();
}

EmbVector image_objectTopLeft()
{
    float alpha = radians(rotation());
    EmbVector tl = rect().topRight() * scale();
    EmbVector ptlrot = emb_vector_rotate(tl, alpha);
    return scenePos() + ptlrot;
}

EmbVector image_objectTopRight()
{
    float alpha = radians(rotation());
    EmbVector tr = rect().topRight() * scale();
    EmbVector ptrrot = emb_vector_rotate(tr, alpha);
    return scenePos() + ptrrot;
}

EmbVector image_objectBottomLeft()
{
    float alpha = radians(rotation());
    EmbVector bl = rect().topRight() * scale();
    EmbVector pblrot = emb_vector_rotate(bl, alpha);
    return scenePos() + pblrot;
}

EmbVector image_objectBottomRight()
{
    float alpha = radians(rotation());
    EmbVector br = rect().topRight() * scale();
    EmbVector pbrrot = emb_vector_rotate(br, alpha);
    return scenePos() + pbrrot;
}

//Command: Line

float global = {}; //Required

void
emb_line_init(void)
{
    initCommand();
    clearSelection();
    global.firstRun = true;
    global.first.x = NaN;
    global.first.y = NaN;
    global.prev.x = NaN;
    global.prev.y = NaN;
}

void
emb_line_init(EmbLine line_in, unsigned int rgb, PenStyle lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Line");

    line = line_in;

    setFlag(ItemIsSelectable, true);

    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void
emb_line_set_endpoint1(EmbVector point1)
{
    float dx = line.start.x - point1.x;
    float dy = line.start.y - point1.y;
    setRotation(0);
    setScale(1);
    setLine(0, 0, dx, dy);
    setPos(point1);
}

void
emb_line_set_endpoint2(EmbVector point1)
{
    float dx = line.end.x - point1.x;
    float dy = line.end.y - point1.y;
    setRotation(0);
    setScale(1);
    setLine(0, 0, dx, dy);
    setPos(point1);
}

EmbVector
emb_line_EndPoint2()
{
    EmbLine lyne = line();
    float alpha = radians(rotation());
    EmbVector point2;
    point2.x = lyne.x2()*scale();
    point2.y = lyne.y2()*scale();
    EmbVector rotEnd = emb_vector_rotate(point2, alpha);

    return scenePos() + rotEnd;
}

EmbVector
emb_line_MidPoint()
{
    EmbLine lyne = line();
    EmbVector mp = lyne.pointAt(0.5) * scale();
    float alpha = radians(rotation());
    EmbVector rotMid = emb_vector_rotate(mp, alpha);

    return scenePos() + rotMid;
}

float
emb_line_angle()
{
    return fmodf(line().angle() - rotation(), 360.0);
}

path_PathObject(float x, float y, const QPainterPath p, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("PathObject Constructor()");
    init(x, y, p, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

path_PathObject(PathObject* obj, QGraphicsItem* parent)
{
    debug_message("PathObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void path_init(float x, float y, const QPainterPath& p, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Path");

    setFlag(ItemIsSelectable, true);

    updatePath(p);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void point_init(float x, float y, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Point");

    setFlag(ItemIsSelectable, true);

    setRect(-0.00000001, -0.00000001, 0.00000002, 0.00000002);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void
emb_polygon(float x, float y, const QPainterPath& p, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("PolygonObject Constructor()");
    init(x, y, p, rgb, SolidLine); //TODO: getCurrentLineType
}

void
polygon_PolygonObject(PolygonObject* obj, QGraphicsItem* parent)
{
    debug_message("PolygonObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void
emb_polygon_init(float x, float y, const QPainterPath& p, unsigned int rgb, PenStyle lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Polygon");

    setFlag(ItemIsSelectable, true);

    gripIndex = -1;
    updatePath(p);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
}

int polygon_findIndex(EmbVector point)
{
    int i = 0;
    int elemCount = normalPath.elementCount();
    //NOTE: Points here are in item coordinates
    EmbVector itemPoint = mapFromScene(point);
    for (i = 0; i < elemCount; i++) {
        QPainterPath::Element e = normalPath.elementAt(i);
        EmbVector elemPoint = EmbVector(e.x, e.y);
        if (itemPoint == elemPoint) return i;
    }
    return -1;
}

void
emb_polyline(float x, float y, const QPainterPath& p, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("PolylineObject Constructor()");
    init(x, y, p, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void
emb_polyline(EmbPolyline* obj, QGraphicsItem* parent)
{
    debug_message("PolylineObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void embPolyline_init(float x, float y, QPainterPath *p, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Polyline");

    setFlag(ItemIsSelectable, true);

    gripIndex = -1;
    updatePath(p);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
}

int
embPolyline_findIndex(const EmbVector& point)
{
    int elemCount = normalPath.elementCount();
    //NOTE: Points here are in item coordinates
    EmbVector itemPoint = mapFromScene(point);
    for (int i = 0; i < elemCount; i++) {
        QPainterPath::Element e = normalPath.elementAt(i);
        EmbVector elemPoint = EmbVector(e.x, e.y);
        if (itemPoint == elemPoint) return i;
    }
    return -1;
}

void
rect_init(EmbRect rect, unsigned int rgb, PenStyle lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Rectangle");

    setFlag(ItemIsSelectable, true);

    setRect(x, y, w, h);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
}

EmbVector
rect_topLeft()
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    float alpha = radians(rotation());
    EmbVector tl = rect().topLeft() * scale();
    EmbVector ptlrot = emb_vector_rotate(t1, alpha);
    return scenePos() + ptlrot;
    return v;
}

EmbVector
rect_topRight()
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    float alpha = radians(rotation());
    EmbVector tr = rect().topRight() * scale();
    EmbVector ptlrot = emb_vector_rotate(t1, alpha);
    return scenePos() + ptrrot;
    return v;
}
*/

EmbVector embRect_bottomLeft(EmbRect rect)
{
        printf("%f", rect.x);
        EmbVector v;
        v.x = 0.0;
        v.y = 0.0;
        /*
           float alpha = radians(rotation());
           EmbVector bl = rect().bottomLeft() * scale();
           EmbVector pblrot = emb_vector_rotate(b1, alpha);
           return scenePos() + pblrot;
         */
        return v;
}

EmbVector embRect_bottomRight(EmbRect rect)
{
        printf("%f", rect.x);
        EmbVector v;
        v.x = 0.0;
        v.y = 0.0;
        /*
           float alpha = radians(rotation());
           EmbVector br = rect().bottomRight() * scale();
           EmbVector pbrrot = emb_vector_rotate(br, alpha);
           return scenePos() + pbrrot;
         */
        return v;
}

/*
 */
EmbEllipse emb_ellipse_init(void)
{
        EmbEllipse ellipse;
        ellipse.center.x = 0.0;
        ellipse.center.y = 0.0;
        ellipse.radius.x = 1.0;
        ellipse.radius.y = 2.0;
        ellipse.rotation = 0.0;
        return ellipse;
}

/* . */
EmbReal emb_ellipse_diameterX(EmbEllipse ellipse)
{
        return ellipse.radius.x * 2.0;
}

EmbReal emb_ellipse_diameterY(EmbEllipse ellipse)
{
        return ellipse.radius.y * 2.0;
}

/*
void emb_ellipse_init(EmbEllipse ellipse, unsigned int rgb, int lineType)
{
    printf("%f %d %d", ellipse.radius.x, rgb, lineType);
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Ellipse");

    setFlag(ItemIsSelectable, true);

    setSize(width, height);
    setCenter(centerX, centerY);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
    updatePath();
}
*/

void emb_ellipse_setSize(float width, float height)
{
        printf("%f %f", width, height);
        /*
           EmbRect elRect = rect();
           elRect.setWidth(width);
           elRect.setHeight(height);
           elRect.moveCenter(EmbVector(0,0));
           setRect(elRect);
         */
}

/*
 * BASIC FUNCTIONS
 */

/* round is C99 and we're committed to C90 so here's a replacement.
 */
int emb_round(EmbReal x)
{
        EmbReal y = floor(x);
        if (fabs(x - y) > 0.5) {
                return (int)ceil(x);
        }
        return (int)y;
}

EmbReal radians(EmbReal degree)
{
        return degree * embConstantPi / 180.0;
}

EmbReal degrees(EmbReal radian)
{
        return radian * 180.0 / embConstantPi;
}

/* Finds the normalized vector perpendicular (clockwise) to the line
 * given by v1->v2 (normal to the line) */
EmbVector emb_line_normalVector(EmbLine line, int clockwise)
{
        EmbVector result;
        EmbReal temp;
        result = emb_vector_subtract(line.end, line.start);
        result = emb_vector_normalize(result);
        temp = result.x;
        result.x = result.y;
        result.y = -temp;
        if (!clockwise) {
                result.x = -result.x;
                result.y = -result.y;
        }
        return result;
}

/* Returns the vector that is the same length as the line, in the same
 * direction.
 */
EmbVector emb_line_toVector(EmbLine line)
{
        return emb_vector_subtract(line.end, line.start);
}

/*
 * Finds the intersection of two lines given by v1->v2 and v3->v4
 * and sets the value in the result variable.
 */
EmbVector
emb_line_intersectionPoint(EmbLine line1, EmbLine line2, int *emb_error)
{
        EmbReal det, C2, C1, tolerance;
        EmbVector vec1, vec2, result;
        *emb_error = 0;
        vec1 = emb_line_toVector(line1);
        vec2 = emb_line_toVector(line2);
        C2 = emb_vector_cross(line1.start, vec1);
        C1 = emb_vector_cross(line2.start, vec2);

        tolerance = 1e-10;
        det = emb_vector_cross(vec2, vec1);

        if (fabs(det) < tolerance) {
                /* Default to the origin when an error is thrown. */
                *emb_error = 1;
                result.x = 0.0;
                result.y = 0.0;
                return result;
        }
        result.x = (vec2.x * C2 - vec1.x * C1) / det;
        result.y = (vec2.y * C2 - vec1.y * C1) / det;
        return result;
}

/* .
 */
EmbRect emb_rect(EmbReal x, EmbReal y, EmbReal w, EmbReal h)
{
        EmbRect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        return rect;
}

//NOTE: This void should be used to interpret various object types and save them as polylines for stitchOnly formats.
/*
void
save_to_polyline(EmbPattern* pattern, const EmbVector& objPos, const QPainterPath& objPath, const char* layer, const QColor& color, const char* lineType, const char* lineWeight)
{
    float startX = objPos.x();
    float startY = objPos.y();
    EmbArray *pointList = emb_array_create(EMB_POINT);
    EmbPoint lastPoint;
    QPainterPath::Element element;
    for (int i = 0; i < objPath.elementCount(); ++i) {
        element = objPath.elementAt(i);
        if (pointList->count == 0) {
            lastPoint.position.x = element.x + startX;
            lastPoint.position.y = -(element.y + startY);
            emb_array_addPoint(pointList, lastPoint);
        }
        else {
            lastPoint.position.x += element.x + startX;
            lastPoint.position.y += -(element.y + startY);
        }
    }

    EmbPolyline polyObject;
    polyObject.pointList = pointList;
    polyObject.color.r = color.red();
    polyObject.color.g = color.green();
    polyObject.color.b = color.blue();
    //TODO: proper lineType
    embp_addPolylineAbs(pattern, polyObject);
}

void textSingle_TextSingleObject(const char* str, float x, float y, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("TextSingleObject Constructor()");
    init(str, x, y, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void textSingle_TextSingleObject(TextSingleObject* obj, QGraphicsItem* parent)
{
    debug_message("TextSingleObject Constructor()");
    if (obj) {
        setTextFont(obj->objTextFont);
        setTextSize(obj->objTextSize);
        setRotation(obj->rotation());
        setTextBackward(obj->objTextBackward);
        setTextUpsideDown(obj->objTextUpsideDown);
        setTextStyle(obj->objTextBold, obj->objTextItalic, obj->objTextUnderline, obj->objTextStrikeOut, obj->objTextOverline);
        init(obj->objText, obj->objectX(), obj->objectY(), obj->objectColorRGB(), SolidLine); //TODO: getCurrentLineType
        setScale(obj->scale());
    }
}

void textSingle_init(const char* str, float x, float y, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Single Line Text");

    setFlag(ItemIsSelectable, true);

    objTextJustify = "Left"; //TODO: set the justification properly

    setText(str);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

std::stringList text_single_objectTextJustifyList()
{
    std::stringList justifyList;
    justifyList << "Left" << "Center" << "Right" << "Middle";
    // TODO: << "Fit" << "Aligned";
    justifyList << "Top Left" << "Top Center" << "Top Right";
    justifyList << "Middle Left" << "Middle Center" << "Middle Right";
    justifyList << "Bottom Left" << "Bottom Center" << "Bottom Right";
    return justifyList;
}

void textSingle_setText(const char* str)
{
    objText = str;
    QPainterPath textPath;
    QFont font;
    font.setFamily(objTextFont);
    font.setPointSizeF(objTextSize);
    font.setBold(objTextBold);
    font.setItalic(objTextItalic);
    font.setUnderline(objTextUnderline);
    font.setStrikeOut(objTextStrikeOut);
    font.setOverline(objTextOverline);
    textPath.addText(0, 0, font, str);

    //Translate the path based on the justification
    EmbRect jRect = textPath.boundingRect();
    if (objTextJustify == "Left") {
        textPath.translate(-jRect.left(), 0);
    }
    else if (objTextJustify == "Center") {
        textPath.translate(-jRect.center().x(), 0);
    }
    else if (objTextJustify == "Right") {
        textPath.translate(-jRect.right(), 0);
    }
    else if (objTextJustify == "Aligned") {

    } //TODO: TextSingleObject Aligned Justification
    else if (objTextJustify == "Middle") {
        textPath.translate(-jRect.center()); }
    else if (objTextJustify == "Fit") {

    } //TODO: TextSingleObject Fit Justification
    else if (objTextJustify == "Top Left") {
        textPath.translate(-jRect.topLeft());
    }
    else if (objTextJustify == "Top Center") {
        textPath.translate(-jRect.center().x(), -jRect.top());
    }
    else if (objTextJustify == "Top Right") {
        textPath.translate(-jRect.topRight());
    }
    else if (objTextJustify == "Middle Left") {
        textPath.translate(-jRect.left(), -jRect.top()/2.0);
    }
    else if (objTextJustify == "Middle Center") { textPath.translate(-jRect.center().x(), -jRect.top()/2.0); }
    else if (objTextJustify == "Middle Right")  { textPath.translate(-jRect.right(), -jRect.top()/2.0); }
    else if (objTextJustify == "Bottom Left")   { textPath.translate(-jRect.bottomLeft()); }
    else if (objTextJustify == "Bottom Center") { textPath.translate(-jRect.center().x(), -jRect.bottom()); }
    else if (objTextJustify == "Bottom Right")  { textPath.translate(-jRect.bottomRight()); }

    //Backward or Upside Down
    if (objTextBackward || objTextUpsideDown) {
        float horiz = 1.0;
        float vert = 1.0;
        if (objTextBackward) horiz = -1.0;
        if (objTextUpsideDown) vert = -1.0;

        QPainterPath flippedPath;

        QPainterPath::Element element;
        QPainterPath::Element P2;
        QPainterPath::Element P3;
        QPainterPath::Element P4;
        for (int i = 0; i < textPath.elementCount(); ++i) {
            element = textPath.elementAt(i);
            if (element.isMoveTo()) {
                flippedPath.moveTo(horiz * element.x, vert * element.y);
            }
            else if (element.isLineTo()) {
                flippedPath.lineTo(horiz * element.x, vert * element.y);
            }
            else if (element.isCurveTo()) {
                                              // start point P1 is not needed
                P2 = textPath.elementAt(i);   // control point
                P3 = textPath.elementAt(i+1); // control point
                P4 = textPath.elementAt(i+2); // end point

                flippedPath.cubicTo(horiz * P2.x, vert * P2.y,
                                    horiz * P3.x, vert * P3.y,
                                    horiz * P4.x, vert * P4.y);
            }
        }
        objTextPath = flippedPath;
    }
    else {
        objTextPath = textPath;
    }

    //Add the grip point to the shape path
    QPainterPath gripPath = objTextPath;
    gripPath.connectPath(objTextPath);
    gripPath.addRect(-0.00000001, -0.00000001, 0.00000002, 0.00000002);
    setPath(gripPath);
}
*/

void textSingle_setJustify(EmbGeometry *g, const char *justify)
{
        printf("%p, %s\n", g, justify);
        /*
           // Verify the string is a valid option
           objTextJustify = "Left";
           if ((justify == "Left") || (justify == "Center") || (justify == "Right")
           || (justify == "Aligned") || (justify == "Middle") || (justify == "Fit")
           || (justify == "Top Left") || (justify == "Top Center") || (justify == "Top Right")
           || (justify == "Middle Left") || (justify == "Middle Center") || (justify == "Middle Right")
           || (justify == "Bottom Left") || (justify == "Bottom Center") || (justify == "Bottom Right")) {
           objTextJustify = justify;
           }
           setText(objText);
         */
}

/* . */
int emb_backwards(EmbGeometry *g, EmbError *error)
{
        /*
           objTextBackward = value;
           setText(objText);
         */
        *error = EMB_NO_ERR;
        return 0;
}

int emb_bold(EmbGeometry *g, EmbError *error)
{
        /*
           objTextBold = val;
           setText(objText);
         */
        *error = EMB_NO_ERR;
        return 0;
}

int emb_bulge(EmbGeometry *g, EmbError *error)
{
        *error = EMB_NO_ERR;
        return 0;
}

EmbReal emb_chord_length(EmbGeometry *g, EmbError *error)
{
        EmbVector v = emb_chord(g, error);
        if (*error) {
                return 0.0;
        }
        *error = EMB_NO_ERR;
        return emb_vector_length(v);
}

EmbReal emb_chord_angle(EmbGeometry *g, EmbError *error)
{
        return 0.0;
}

#if 0
case EMB_CHORDANGLE:{
        EmbVector delta = emb_chord(g, EMB_CHORD).v;
        v = script_real(emb_vector_angle(delta));
        break;
}

case EMB_CHORDMID:{
        v = emb_chord(g, EMB_CHORD);
        v.v = emb_vector_scale(v.v, 0.5);
        break;
}

case EMB_DIAMETER:{
        v = emb_radius(g, error);
        v.r = fabs(v.r * 2.0);
        break;
}

case EMB_INCANGLE:{
        EmbReal bulge = emb_bulge(g, EMB_BULGE).r;
        v = script_real(atan(bulge) * 4.0);
        break;
}

case EMB_FONT:{
        /*
           objTextFont = font;
           setText(objText);
         */
        break;
}

case EMB_ITALIC:{
        /*
           objTextItalic = val;
           setText(objText);
         */
        break;
}

case EMB_SAGITTA:{
        EmbReal chord = emb_chord(g);
        ScriptValue bulge = emb_bulge(g, EMB_BULGE);
        return script_real(fabs((chord / 2.0) * bulge.r));
}

case EMB_STRIKEOUT:{
        /*
           objTextStrikeOut = val;
           setText(objText);
         */
        break;
}

case EMB_OVERLINE:{
        /*
           objTextOverline = val;
           setText(objText);
         */
        break;
}

case EMB_UNDERLINE:{
        /*
           objTextUnderline = val;
           setText(objText);
         */
        break;
}

case EMB_UPSIDEDOWN:{
        /*
           objTextUpsideDown = value;
           setText(objText);
         */
        break;
}

case EMB_SIZE:{
        /*
           objTextSize = value;
           setText(objText);
         */
        break;
}

case EMB_PERIMETER:{
        break;
}

default:
break;
}

return v;
}

/* */
int emb_gset(EmbGeometry *g, int attribute, ScriptValue value)
{
        printf("%d\n", value.type);
        switch (g->type) {
        case EMB_BOLD:{
                        /*
                           objTextBold = val;
                           setText(objText);
                         */
                        break;
                }
        case EMB_ITALIC:{
                        /*
                           objTextItalic = val;
                           setText(objText);
                         */
                        break;
                }
        case EMB_UNDERLINE:{
                        /*
                           objTextUnderline = val;
                           setText(objText);
                         */
                        break;
                }
        case EMB_STRIKEOUT:{
                        /*
                           objTextStrikeOut = val;
                           setText(objText);
                         */
                        break;
                }
        case EMB_OVERLINE:{
                        /*
                           objTextOverline = val;
                           setText(objText);
                         */
                        break;
                }
        case EMB_BACKWARDS:{
                        /*
                           objTextBackward = val;
                           setText(objText);
                         */
                        break;
                }
        case EMB_UPSIDEDOWN:{
                        /*
                           objTextUpsideDown = val;
                           setText(objText);
                         */
                        break;
                }
        case EMB_SAGITTA:{
                        if (g->type != EMB_ARC) {
                                /* ERROR */
                                return 0;
                        }
                        break;
                }
        case EMB_BULGE:{
                        if (g->type != EMB_ARC) {
                                /* ERROR */
                                return 0;
                        }
                        break;
                }
        case EMB_SIZE:{
                        /*
                           objTextSize = value;
                           setText(objText);
                         */
                        break;
                }
        case EMB_PERIMETER:{
                        /* TODO: Use Ramanujan's approximation here. */
                        break;
                }
        case EMB_AREA:{
                        /* TODO: look up a formula for ellipses. */
                        break;
                }
        default:
                break;
        }
        return 0;
}
#endif

/* Finds the location of the first non-whitespace character
 * in the string and returns it.
 */
int string_whitespace(const char *s)
{
        int i;
        for (i = 0; i < 200; i++) {
                if (s[i] == ' ')
                        continue;
                if (s[i] == '\t')
                        continue;
                if (s[i] == '\r')
                        continue;
                if (s[i] == '\n')
                        continue;
                return i;
        }
        return i;
}

/* Note that our version of strlen can tell us that
 * the string is not null-terminated by returning -1.
 */
int embstr_len(EmbString src)
{
        int i;
        for (i = 0; i < 200; i++) {
                if (src[i] == 0) {
                        return i;
                }
        }
        return -1;
}

/*
 */
int string_rchar(const char *s, char c)
{
        int i;
        int n = embstr_len(s);
        for (i = n - 1; i >= 0; i--) {
                if (s[i] == c) {
                        return i;
                }
        }
        return 0;
}

/* ENCODING SECTION
 * ----------------------------------------------------------------------------
 *
 * The functions in this section are grouped together to aid the developer's
 * understanding of the similarities between the file formats. This also helps
 * reduce errors between reimplementation of the same idea.
 *
 * For example: the Tajima ternary encoding of positions is used by at least 4
 * formats and the only part that changes is the flag encoding.
 *
 * Converts a 6 digit hex string (I.E. "00FF00")
 * into an EmbColor and returns it.
 *
 * a val 6 byte code describing the color as a hex string, doesn't require null termination.
 * Returns EmbColor the same color as our internal type.
 */
EmbColor embColor_fromHexStr(char *val)
{
        EmbColor color;
        char r[3];
        char g[3];
        char b[3];

        r[0] = val[0];
        r[1] = val[1];
        r[2] = 0;

        g[0] = val[2];
        g[1] = val[3];
        g[2] = 0;

        b[0] = val[4];
        b[1] = val[5];
        b[2] = 0;

        color.r = (unsigned char)strtol(r, 0, 16);
        color.g = (unsigned char)strtol(g, 0, 16);
        color.b = (unsigned char)strtol(b, 0, 16);
        return color;
}

EmbColor
embColor_make(unsigned char red, unsigned char green, unsigned char blue)
{
        EmbColor c;
        c.r = red;
        c.b = green;
        c.g = blue;
        return c;
}

/* Swap two bytes' positions. */
void emb_swap(char *a, int i, int j)
{
        char tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
}

/* The array management for libembroidery's arrays.
 */

/* Allocates memory for an EmbArray of the type determined by
 * the argument a type.
 */
EmbArray *emb_array_create(int type)
{
        EmbArray *a;
        a = (EmbArray *) malloc(sizeof(EmbArray));
        a->type = type;
        a->length = CHUNK_SIZE;
        a->count = 0;
        switch (type) {
        case EMB_STITCH:
                a->stitch =
                    (EmbStitch *) malloc(CHUNK_SIZE * sizeof(EmbStitch));
                break;
        case EMB_THREAD:
                a->thread =
                    (EmbThread *) malloc(CHUNK_SIZE * sizeof(EmbThread));
                break;
        default:
                a->geometry =
                    (EmbGeometry *) malloc(CHUNK_SIZE * sizeof(EmbGeometry));
                break;
        }
        return a;
}

/* Resizes the array a a to be CHUNK_SIZE entries longer
 * if and only if the amount of room left is less than
 * 3 entries.
 */
int emb_array_resize(EmbArray *a)
{
        if (a->count < a->length - 3) {
                return 1;
        }
        a->length += CHUNK_SIZE;
        switch (a->type) {
        case EMB_STITCH:
                a->stitch =
                    (EmbStitch *) realloc(a->stitch,
                                          a->length * sizeof(EmbStitch));
                if (!a->stitch) {
                        /* TODO: Error reporting */
                        return 0;
                }
                break;
        case EMB_THREAD:
                a->thread =
                    (EmbThread *) realloc(a->thread,
                                          a->length * sizeof(EmbThread));
                if (!a->thread) {
                        /* TODO: Error reporting */
                        return 0;
                }
                break;
        default:
                a->geometry =
                    (EmbGeometry *) realloc(a->geometry,
                                            a->length * sizeof(EmbGeometry));
                if (!a->geometry) {
                        /* TODO: Error reporting */
                        return 0;
                }
                break;
        }

        return 1;
}

/* Copies all entries in the EmbArray struct from a src to a dst.
 */
void emb_array_copy(EmbArray *dst, EmbArray *src)
{
        dst = emb_array_create(src->type);
        dst->length = src->length;
        dst->count = src->count;
        emb_array_resize(dst);
        /* BUG: Potential failure to copy path memory, only copy pointers? */

        switch (dst->type) {
        case EMB_STITCH:
                memcpy(dst->stitch, src->stitch,
                       sizeof(EmbStitch) * src->count);
                break;
        case EMB_THREAD:
                memcpy(dst->thread, src->thread,
                       sizeof(EmbThread) * src->count);
                break;
        default:
                memcpy(dst->geometry, src->geometry,
                       sizeof(EmbGeometry) * src->count);
                break;
        }
}

/* Add a circle a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int emb_array_add_circle(EmbArray *a, EmbCircle b)
{
        a->count++;
        if (!emb_array_resize(a)) {
                return 0;
        }
        a->geometry[a->count - 1].object.circle = b;
        a->geometry[a->count - 1].type = EMB_CIRCLE;
        return 1;
}

/* Add an ellipse a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int emb_array_add_ellipse(EmbArray *a, EmbEllipse b)
{
        a->count++;
        if (!emb_array_resize(a)) {
                return 0;
        }
        a->geometry[a->count - 1].object.ellipse = b;
        a->geometry[a->count - 1].type = EMB_ELLIPSE;
        return 1;
}

/* Add a flag a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int emb_array_add_flag(EmbArray *a, EmbFlag b)
{
        a->count++;
        if (!emb_array_resize(a)) {
                return 0;
        }
        a->geometry[a->count - 1].flag = b;
        a->geometry[a->count - 1].type = EMB_FLAG;
        return 1;
}

/* Add a line a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int emb_array_addLine(EmbArray *a, EmbLine b)
{
        a->count++;
        if (!emb_array_resize(a)) {
                return 0;
        }
        a->geometry[a->count - 1].object.line = b;
        a->geometry[a->count - 1].type = EMB_LINE;
        return 1;
}

/* Add a path a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int emb_array_addPath(EmbArray *a, EmbPath b)
{
        a->count++;
        if (!emb_array_resize(a)) {
                return 0;
        }
        a->geometry[a->count - 1].object.path = b;
        a->geometry[a->count - 1].type = EMB_PATH;
        return 1;
}

/* Add a point a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int emb_array_addPoint(EmbArray *a, EmbPoint b)
{
        a->count++;
        if (!emb_array_resize(a)) {
                return 0;
        }
        a->geometry[a->count - 1].object.point = b;
        a->geometry[a->count - 1].type = EMB_POINT;
        return 1;
}

/* Add a polyline a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int emb_array_addPolyline(EmbArray *a, EmbPolyline b)
{
        a->count++;
        if (!emb_array_resize(a)) {
                return 0;
        }
        a->geometry[a->count - 1].object.polyline = b;
        a->geometry[a->count - 1].type = EMB_POLYLINE;
        return 1;
}

/* Add a polygon a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int emb_array_addPolygon(EmbArray *a, EmbPolygon b)
{
        a->count++;
        if (!emb_array_resize(a)) {
                return 0;
        }
        a->geometry[a->count - 1].object.polygon = b;
        a->geometry[a->count - 1].type = EMB_POLYGON;
        return 1;
}

/* Add a rectangle a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int emb_array_addRect(EmbArray *a, EmbRect b)
{
        a->count++;
        if (!emb_array_resize(a)) {
                return 0;
        }
        a->geometry[a->count - 1].object.rect = b;
        a->geometry[a->count - 1].type = EMB_RECT;
        return 1;
}

/* Add a stitch a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int emb_array_addStitch(EmbArray *a, EmbStitch b)
{
        a->count++;
        if (!emb_array_resize(a)) {
                return 0;
        }
        a->stitch[a->count - 1] = b;
        return 1;
}

/* Add a generic geometry to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int emb_array_add_geometry(EmbArray *a, EmbGeometry g)
{
        a->count++;
        if (!emb_array_resize(a)) {
                return 0;
        }
        a->geometry[a->count - 1] = g;
        return 1;
}

/* Add a vector a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int emb_array_addVector(EmbArray *a, EmbVector b)
{
        a->count++;
        if (!emb_array_resize(a)) {
                return 0;
        }
        a->geometry[a->count - 1].object.vector = b;
        a->geometry[a->count - 1].type = EMB_VECTOR;
        return 1;
}

/* Free the memory of EmbArray a a, recursively if necessary.
 */
void emb_array_free(EmbArray *a)
{
        if (!a) {
                return;
        }
        switch (a->type) {
        case EMB_STITCH:
                safe_free(a->stitch);
                break;
        case EMB_THREAD:
                safe_free(a->thread);
                break;
        default:{
                        int i;
                        for (i = 0; i < a->count; i++) {
                                EmbGeometry g = a->geometry[i];
                                switch (a->geometry[i].type) {
                                case EMB_PATH:{
                                                emb_array_free(g.object.
                                                               path.pointList);
                                                break;
                                        }
                                case EMB_POLYGON:{
                                                emb_array_free(g.object.
                                                               polygon.pointList);
                                                break;
                                        }
                                case EMB_POLYLINE:{
                                                emb_array_free(g.
                                                               object.polyline.pointList);
                                                break;
                                        }
                                default:
                                        break;
                                }
                        }
                        safe_free(a->geometry);
                        break;
                }
        }
        safe_free(a);
}

/* Print the vector "v2 with the name "label". */
void emb_vector_print(EmbVector v, char *label)
{
        printf("%sX = %f\n", label, v.x);
        printf("%sY = %f\n", label, v.y);
}

/* Print the arc "arc". */
void emb_arc_print(EmbArc arc)
{
        emb_vector_print(arc.start, "start");
        emb_vector_print(arc.mid, "middle");
        emb_vector_print(arc.end, "end");
}

/* Checks that there are enough bytes to interpret the header,
 * stops possible segfaults when reading in the header bytes.
 *
 * Returns 0 if there aren't enough, or the length of the file
 * if there are.
 */
int check_header_present(FILE *file, int minimum_header_length)
{
        int length;
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        if (length < minimum_header_length) {
                return 0;
        }
        return length;
}

/* sectorSize based on the bcfFile version. */
unsigned int sectorSize(bcf_file *bcfFile)
{
        /* version 3 uses 512 byte */
        if (bcfFile->header.majorVersion == 3) {
                return 512;
        }
        return 4096;
}

/* . */
int haveExtraDIFATSectors(bcf_file *file)
{
        return (int)(entriesInDifatSector(file->difat) > 0);
}

/* . */
int seekToSector(bcf_file *bcfFile, FILE *file, const unsigned int sector)
{
        unsigned int offset =
            sector * sectorSize(bcfFile) + sectorSize(bcfFile);
        return fseek(file, offset, SEEK_SET);
}

/* . */
void parseDIFATSectors(FILE *file, bcf_file *bcfFile)
{
        unsigned int difatEntriesToRead =
            bcfFile->header.numberOfFATSectors - difatEntriesInHeader;
        unsigned int difatSectorNumber =
            bcfFile->header.firstDifatSectorLocation;
        while ((difatSectorNumber != CompoundFileSector_EndOfChain)
               && (difatEntriesToRead > 0)) {
                seekToSector(bcfFile, file, difatSectorNumber);
                difatSectorNumber =
                    readFullSector(file, bcfFile->difat, &difatEntriesToRead);
        }
}

/* . */
int bcfFile_read(FILE *file, bcf_file *bcfFile)
{
        unsigned int i, numberOfDirectoryEntriesPerSector;
        unsigned int directorySectorToReadFrom;

        bcfFile->header = bcfFileHeader_read(file);
        if (memcmp
            (bcfFile->header.signature, "\xd0\xcf\x11\xe0\xa1\xb1\x1a\xe1",
             8) != 0) {
                printf("bad header signature\n");
                printf("Failed to parse header\n");
                return 0;
        }

        bcfFile->difat =
            bcf_difat_create(file, bcfFile->header.numberOfFATSectors,
                             sectorSize(bcfFile));
        if (haveExtraDIFATSectors(bcfFile)) {
                parseDIFATSectors(file, bcfFile);
        }

        bcfFile->fat = bcfFileFat_create(sectorSize(bcfFile));
        for (i = 0; i < bcfFile->header.numberOfFATSectors; ++i) {
                unsigned int fatSectorNumber =
                    bcfFile->difat->fatSectorEntries[i];
                seekToSector(bcfFile, file, fatSectorNumber);
                loadFatFromSector(bcfFile->fat, file);
        }

        numberOfDirectoryEntriesPerSector =
            sectorSize(bcfFile) / sizeOfDirectoryEntry;
        bcfFile->directory =
            CompoundFileDirectory(numberOfDirectoryEntriesPerSector);
        directorySectorToReadFrom =
            bcfFile->header.firstDirectorySectorLocation;
        while (directorySectorToReadFrom != CompoundFileSector_EndOfChain) {
                seekToSector(bcfFile, file, directorySectorToReadFrom);
                readNextSector(file, bcfFile->directory);
                directorySectorToReadFrom =
                    bcfFile->fat->fatEntries[directorySectorToReadFrom];
        }

        return 1;
}

/* Get the File object. */
void *GetFile(bcf_file *bcfFile, FILE *file, char *fileToFind)
{
        int filesize, sectorSize, currentSector;
        int sizeToWrite, currentSize, totalSectors, i, j;
        FILE *fileOut = tmpfile();
        bcf_directory_entry *pointer = bcfFile->directory->dirEntries;
        while (pointer) {
                if (!strcmp(fileToFind, pointer->directoryEntryName)) {
                        break;
                }
                pointer = pointer->next;
        }
        filesize = pointer->streamSize;
        sectorSize = bcfFile->difat->sectorSize;
        currentSize = 0;
        currentSector = pointer->startingSectorLocation;
        totalSectors = (int)ceil((float)filesize / sectorSize);
        for (i = 0; i < totalSectors; i++) {
                seekToSector(bcfFile, file, currentSector);
                sizeToWrite = filesize - currentSize;
                if (sectorSize < sizeToWrite) {
                        sizeToWrite = sectorSize;
                }
                for (j = 0; j < sizeToWrite; j++) {
                        char input;
                        if (fread(&input, 1, 1, file) != 1) {
                                /* TODO: Needs an error code. */
                                puts("ERROR: GetFile failed to read byte.");
                                return fileOut;
                        }
                        if (fwrite(&input, 1, 1, fileOut) != 1) {
                                /* TODO: Needs an error code. */
                                puts("ERROR: GetFile failed to read byte.");
                                return fileOut;
                        }
                }
                currentSize += sizeToWrite;
                currentSector = bcfFile->fat->fatEntries[currentSector];
        }
        return fileOut;
}

/* . */
void bcf_file_free(bcf_file *bcfFile)
{
        safe_free(bcfFile->difat);
        safe_free(bcfFile->fat);
        bcf_directory_free(&bcfFile->directory);
        safe_free(bcfFile);
}

/* . */
bcf_file_difat *bcf_difat_create(FILE *file, unsigned int fatSectors,
                                 const unsigned int sectorSize)
{
        unsigned int i;
        bcf_file_difat *difat = 0;
        unsigned int sectorRef;

        difat = (bcf_file_difat *) malloc(sizeof(bcf_file_difat));
        if (!difat) {
                printf
                    ("ERROR: compound-file-difat.c bcf_difat_create(), cannot allocate memory for difat\n");
                return NULL;
        }

        difat->sectorSize = sectorSize;
        if (fatSectors > difatEntriesInHeader) {
                fatSectors = difatEntriesInHeader;
        }

        for (i = 0; i < fatSectors; ++i) {
                sectorRef = emb_read_i32(file);
                difat->fatSectorEntries[i] = sectorRef;
        }
        difat->fatSectorCount = fatSectors;
        for (i = fatSectors; i < difatEntriesInHeader; ++i) {
                sectorRef = emb_read_i32(file);
                if (sectorRef != CompoundFileSector_FreeSector) {
                        printf
                            ("ERROR: compound-file-difat.c bcf_difat_create(), Unexpected sector value %x at DIFAT[%d]\n",
                             sectorRef, i);
                }
        }
        return difat;
}

/* . */
unsigned int entriesInDifatSector(bcf_file_difat *fat)
{
        return (fat->sectorSize -
                sizeOfChainingEntryAtEndOfDifatSector) / sizeOfDifatEntry;
}

/* . */
unsigned int
readFullSector(FILE *file,
               bcf_file_difat *bcfFile, unsigned int *difatEntriesToRead)
{
        unsigned int i;
        unsigned int sectorRef;
        unsigned int nextDifatSectorInChain;
        unsigned int entriesToReadInThisSector = 0;
        if (*difatEntriesToRead > entriesInDifatSector(bcfFile)) {
                entriesToReadInThisSector = entriesInDifatSector(bcfFile);
                *difatEntriesToRead -= entriesToReadInThisSector;
        } else {
                entriesToReadInThisSector = *difatEntriesToRead;
                *difatEntriesToRead = 0;
        }

        for (i = 0; i < entriesToReadInThisSector; ++i) {
                sectorRef = emb_read_i32(file);
                bcfFile->fatSectorEntries[bcfFile->fatSectorCount] = sectorRef;
                bcfFile->fatSectorCount++;
        }
        for (i = entriesToReadInThisSector; i < entriesInDifatSector(bcfFile);
             ++i) {
                sectorRef = emb_read_i32(file);
                if (sectorRef != CompoundFileSector_FreeSector) {
                        printf
                            ("ERROR: compound-file-difat.c readFullSector(), ");
                        printf("Unexpected sector value %x at DIFAT[%d]]\n",
                               sectorRef, i);
                }
        }
        nextDifatSectorInChain = emb_read_i32(file);
        return nextDifatSectorInChain;
}

/* . */
void parseDirectoryEntryName(FILE *file, bcf_directory_entry *dir)
{
        int i;
        for (i = 0; i < 32; ++i) {
                uint16_t unicodechar = emb_read_i16(file);
                if (unicodechar != 0x0000) {
                        dir->directoryEntryName[i] = (char)unicodechar;
                }
        }
}

/* . */
bcf_directory *CompoundFileDirectory(const unsigned int
                                     maxNumberOfDirectoryEntries)
{
        bcf_directory *dir = (bcf_directory *) malloc(sizeof(bcf_directory));
        if (!dir) {
                printf
                    ("ERROR: compound-file-directory.c CompoundFileDirectory(), cannot allocate memory for dir\n");
                return NULL;
        }                       /* TODO: avoid crashing. null pointer will be accessed */
        dir->maxNumberOfDirectoryEntries = maxNumberOfDirectoryEntries;
        dir->dirEntries = 0;
        return dir;
}

/* . */
EmbTime parseTime(FILE *file)
{
        EmbTime returnVal;
        unsigned int ft_low, ft_high;
        /*embTime_time(&returnVal); TODO: use embTime_time() rather than time(). */
        ft_low = emb_read_i32(file);
        ft_high = emb_read_i32(file);
        printf("%u %u\n", ft_low, ft_high);
        /* TODO: translate to actual date time */
        returnVal.day = 1;
        returnVal.hour = 2;
        returnVal.minute = 3;
        returnVal.month = 4;
        returnVal.second = 5;
        returnVal.year = 6;
        return returnVal;
}

/* . */
bcf_directory_entry *CompoundFileDirectoryEntry(FILE *file)
{
        int i;
        const int guidSize = 16;
        bcf_directory_entry *dir = malloc(sizeof(bcf_directory_entry));
        if (dir == NULL) {
                printf
                    ("ERROR: compound-file-directory.c CompoundFileDirectoryEntry(), cannot allocate memory for dir\n");
                return NULL;
        }
        memset(dir->directoryEntryName, 0, 32);
        parseDirectoryEntryName(file, dir);
        dir->next = 0;
        dir->directoryEntryNameLength = emb_read_u16(file);
        dir->objectType = (unsigned char)fgetc(file);
        if ((dir->objectType != ObjectTypeStorage)
            && (dir->objectType != ObjectTypeStream)
            && (dir->objectType != ObjectTypeRootEntry)) {
                printf
                    ("ERROR: compound-file-directory.c CompoundFileDirectoryEntry()");
                printf(", unexpected object type: %d\n", dir->objectType);
                return NULL;
        }
        dir->colorFlag = (unsigned char)fgetc(file);
        dir->leftSiblingId = emb_read_i32(file);
        dir->rightSiblingId = emb_read_i32(file);
        dir->childId = emb_read_i32(file);
        if (fread(dir->CLSID, 1, guidSize, file) < guidSize) {
                printf("ERROR: Failed to read guidSize bytes for CLSID");
                return dir;
        }
        dir->stateBits = emb_read_i32(file);
        for (i = 0; i < 6; i++) {
                dir->creationTime[i] = emb_read_i32(file);
        }
        for (i = 0; i < 6; i++) {
                dir->modifiedTime[i] = emb_read_i32(file);
        }
        dir->startingSectorLocation = emb_read_i32(file);
        /* StreamSize should really be __int64 or long long,
         * but for our uses we should never run into an issue */
        dir->streamSize = emb_read_i32(file);
        /* top portion of int64 */
        dir->streamSizeHigh = emb_read_i32(file);
        return dir;
}

/* . */
void readNextSector(FILE *file, bcf_directory *dir)
{
        unsigned int i;
        for (i = 0; i < dir->maxNumberOfDirectoryEntries; ++i) {
                bcf_directory_entry *dirEntry =
                    CompoundFileDirectoryEntry(file);
                bcf_directory_entry *pointer = dir->dirEntries;
                if (!pointer) {
                        dir->dirEntries = dirEntry;
                } else {
                        while (pointer) {
                                if (!pointer->next) {
                                        pointer->next = dirEntry;
                                        break;
                                }
                                pointer = pointer->next;
                        }
                }
        }
}

/* . */
void bcf_directory_free(bcf_directory **dir)
{
        bcf_directory *dirptr;
        bcf_directory_entry *pointer;
        if (dir == NULL) {
                return;
        }
        dirptr = *dir;
        pointer = dirptr->dirEntries;
        while (pointer) {
                bcf_directory_entry *entryToFree;
                entryToFree = pointer;
                pointer = pointer->next;
                safe_free(entryToFree);
        }
        safe_free(*dir);
}

/* . */
bcf_file_fat *bcfFileFat_create(const unsigned int sectorSize)
{
        bcf_file_fat *fat = (bcf_file_fat *) malloc(sizeof(bcf_file_fat));
        if (!fat) {
                printf("ERROR: compound-file-fat.c bcfFileFat_create(), ");
                printf("cannot allocate memory for fat\n");
                return NULL;
        }
        fat->numberOfEntriesInFatSector = sectorSize / sizeOfFatEntry;
        fat->fatEntryCount = 0;
        return fat;
}

/* . */
void loadFatFromSector(bcf_file_fat *fat, FILE *file)
{
        unsigned int i;
        unsigned int current_fat_entries = fat->fatEntryCount;
        unsigned int newSize =
            current_fat_entries + fat->numberOfEntriesInFatSector;
        for (i = current_fat_entries; i < newSize; ++i) {
                fat->fatEntries[i] = emb_read_i32(file);
        }
        fat->fatEntryCount = newSize;
}

/* . */
bcf_file_header bcfFileHeader_read(FILE *file)
{
        bcf_file_header header;
        if (fread(header.signature, 1, 8, file) < 8) {
                puts("ERROR: failed to read signature bytes from bcf file.");
                return header;
        }
        if (fread(header.CLSID, 1, 16, file) < 16) {
                puts("ERROR: failed to read CLSID bytes from bcf file.");
                return header;
        }
        header.minorVersion = emb_read_u16(file);
        header.majorVersion = emb_read_u16(file);
        header.byteOrder = emb_read_u16(file);
        header.sectorShift = emb_read_u16(file);
        header.miniSectorShift = emb_read_u16(file);
        header.reserved1 = emb_read_u16(file);
        header.reserved2 = emb_read_i32(file);
        header.numberOfDirectorySectors = emb_read_i32(file);
        header.numberOfFATSectors = emb_read_i32(file);
        header.firstDirectorySectorLocation = emb_read_i32(file);
        header.transactionSignatureNumber = emb_read_i32(file);
        header.miniStreamCutoffSize = emb_read_i32(file);
        header.firstMiniFATSectorLocation = emb_read_i32(file);
        header.numberOfMiniFatSectors = emb_read_i32(file);
        header.firstDifatSectorLocation = emb_read_i32(file);
        header.numberOfDifatSectors = emb_read_i32(file);
        return header;
}

/* . */
int
emb_generate_satin_outline(EmbArray *lines, EmbReal thickness,
                           EmbSatinOutline *result)
{
        int i;
        EmbLine line1, line2;
        EmbSatinOutline outline;
        EmbVector out;
        EmbVector v1;
        EmbVector temp;
        EmbLine line;

        EmbReal halfThickness = thickness / 2.0;
        int intermediateOutlineCount = 2 * lines->count - 2;
        outline.side1 = emb_array_create(EMB_VECTOR);
        if (!outline.side1) {
                printf
                    ("ERROR: emb_generate_satin_outline(), cannot allocate memory for outline->side1\n");
                return 0;
        }
        outline.side2 = emb_array_create(EMB_VECTOR);
        if (!outline.side2) {
                printf
                    ("ERROR: emb_generate_satin_outline(), cannot allocate memory for outline->side2\n");
                return 0;
        }

        for (i = 1; i < lines->count; i++) {
                line.start = lines->geometry[i - 1].object.vector;
                line.end = lines->geometry[i].object.vector;

                v1 = emb_line_normalVector(line, 1);

                temp = emb_vector_scale(v1, halfThickness);
                temp =
                    emb_vector_add(temp, lines->geometry[i - 1].object.vector);
                emb_array_addVector(outline.side1, temp);
                temp = emb_vector_add(temp, lines->geometry[i].object.vector);
                emb_array_addVector(outline.side1, temp);

                temp = emb_vector_scale(v1, -halfThickness);
                temp =
                    emb_vector_add(temp, lines->geometry[i - 1].object.vector);
                emb_array_addVector(outline.side2, temp);
                temp = emb_vector_add(temp, lines->geometry[i].object.vector);
                emb_array_addVector(outline.side2, temp);
        }

        if (!result) {
                printf
                    ("ERROR: emb_generate_satin_outline(), result argument is null\n");
                return 0;
        }
        result->side1 = emb_array_create(EMB_VECTOR);
        if (!result->side1) {
                printf
                    ("ERROR: emb_generate_satin_outline(), cannot allocate memory for result->side1\n");
                return 0;
        }
        result->side2 = emb_array_create(EMB_VECTOR);
        if (!result->side2) {
                printf
                    ("ERROR: emb_generate_satin_outline(), cannot allocate memory for result->side2\n");
                return 0;
        }

        emb_array_addVector(result->side1,
                            outline.side1->geometry[0].object.vector);
        emb_array_addVector(result->side2,
                            outline.side2->geometry[0].object.vector);

        for (i = 3; i < intermediateOutlineCount; i += 2) {
                int emb_error = 0;
                line1.start = outline.side1->geometry[i - 3].object.vector;
                line1.end = outline.side1->geometry[i - 2].object.vector;
                line2.start = outline.side1->geometry[i - 1].object.vector;
                line2.end = outline.side1->geometry[i].object.vector;
                out = emb_line_intersectionPoint(line1, line2, &emb_error);
                if (emb_error) {
                        puts("No intersection point.");
                }
                emb_array_addVector(result->side1, out);

                line1.start = outline.side2->geometry[i - 3].object.vector;
                line1.end = outline.side2->geometry[i - 2].object.vector;
                line2.start = outline.side2->geometry[i - 1].object.vector;
                line2.end = outline.side2->geometry[i].object.vector;
                out = emb_line_intersectionPoint(line1, line2, &emb_error);
                if (emb_error) {
                        puts("No intersection point.");
                }
                emb_array_addVector(result->side2, out);
        }

        emb_array_addVector(result->side1,
                            outline.side1->geometry[2 * lines->count -
                                                    3].object.vector);
        emb_array_addVector(result->side2,
                            outline.side2->geometry[2 * lines->count -
                                                    3].object.vector);
        result->length = lines->count;
        return 1;
}

/* . */
EmbArray *emb_satin_outline_render(EmbSatinOutline *result, EmbReal density)
{
        int i, j;
        EmbVector currTop, currBottom, topDiff, bottomDiff, midDiff;
        EmbVector midLeft, midRight, topStep, bottomStep;
        EmbArray *stitches = 0;
        int numberOfSteps;
        EmbReal midLength;

        if (!result) {
                printf
                    ("ERROR: emb_satin_outline_render(), result argument is null\n");
                return 0;
        }

        if (result->length > 0) {
                for (j = 0; j < result->length - 1; j++) {
                        EmbGeometry *g10 = &(result->side1->geometry[j + 0]);
                        EmbGeometry *g11 = &(result->side1->geometry[j + 1]);
                        EmbGeometry *g20 = &(result->side2->geometry[j + 0]);
                        EmbGeometry *g21 = &(result->side2->geometry[j + 1]);
                        topDiff =
                            emb_vector_subtract(g10->object.vector,
                                                g11->object.vector);
                        bottomDiff =
                            emb_vector_subtract(g21->object.vector,
                                                g20->object.vector);

                        midLeft =
                            emb_vector_average(g10->object.vector,
                                               g20->object.vector);
                        midRight =
                            emb_vector_average(g11->object.vector,
                                               g21->object.vector);

                        midDiff = emb_vector_subtract(midLeft, midRight);
                        midLength = emb_vector_length(midDiff);

                        numberOfSteps = (int)(midLength * density / 200);
                        topStep =
                            emb_vector_scale(topDiff, 1.0 / numberOfSteps);
                        bottomStep =
                            emb_vector_scale(bottomDiff, 1.0 / numberOfSteps);
                        currTop = g10->object.vector;
                        currBottom = g20->object.vector;

                        for (i = 0; i < numberOfSteps; i++) {
                                if (!stitches) {
                                        stitches = emb_array_create(EMB_VECTOR);
                                }
                                emb_array_addVector(stitches, currTop);
                                emb_array_addVector(stitches, currBottom);
                                currTop = emb_vector_add(currTop, topStep);
                                currBottom =
                                    emb_vector_add(currBottom, bottomStep);
                        }
                }
                emb_array_addVector(stitches, currTop);
                emb_array_addVector(stitches, currBottom);
        }
        return stitches;
}

/* . */
void write_24bit(FILE *file, int x)
{
        unsigned char a[4];
        a[0] = (unsigned char)0;
        a[1] = (unsigned char)(x & 0xFF);
        a[2] = (unsigned char)((x >> 8) & 0xFF);
        a[3] = (unsigned char)((x >> 16) & 0xFF);
        fwrite(a, 1, 4, file);
}

/* . */
int embColor_distance(EmbColor a, EmbColor b)
{
        int t;
        t = (a.r - b.r) * (a.r - b.r);
        t += (a.g - b.g) * (a.g - b.g);
        t += (a.b - b.b) * (a.b - b.b);
        return t;
}

/* . */
void embColor_read(void *f, EmbColor *c, int toRead)
{
        unsigned char b[4];
        if (fread(b, 1, toRead, f) < (unsigned int)toRead) {
                puts("ERROR: Failed to read embColor bytes.");
                return;
        }
        c->r = b[0];
        c->g = b[1];
        c->b = b[2];
}

/* . */
void embColor_write(void *f, EmbColor c, int toWrite)
{
        unsigned char b[4];
        b[0] = c.r;
        b[1] = c.g;
        b[2] = c.b;
        b[3] = 0;
        fwrite(b, 1, toWrite, f);
}

/* Returns the closest color to the required color based on
 * a list of available threads. The algorithm is a simple least
 * squares search against the list. If the (square of) Euclidean 3-dimensional
 * distance between the points in (red, green, blue) space is smaller
 * then the index is saved and the remaining index is returned to the
 * caller.
 *
 * color:  The EmbColor color to match.
 * colors: The EmbThreadList pointer to start the search at.
 * mode:   Is the argument an array of threads (0) or colors (1)?
 * Returns closestIndex: The entry in the ThreadList that matches.
 */
int emb_find_nearest_color(EmbColor color, EmbColor *color_list, int n_colors)
{
        int currentClosestValue = 256 * 256 * 3;
        int closestIndex = -1, i;
        for (i = 0; i < n_colors; i++) {
                int delta = embColor_distance(color, color_list[i]);

                if (delta <= currentClosestValue) {
                        currentClosestValue = delta;
                        closestIndex = i;
                }
        }
        return closestIndex;
}

/* The maximum distance. */
int
emb_find_nearest_thread(EmbColor color, EmbThread *thread_list, int n_threads)
{
        int currentClosestValue = 256 * 256 * 3;
        int closestIndex = -1, i;
        for (i = 0; i < n_threads; i++) {
                int delta = embColor_distance(color, thread_list[i].color);

                if (delta <= currentClosestValue) {
                        currentClosestValue = delta;
                        closestIndex = i;
                }
        }
        return closestIndex;
}

/*
 * Returns a random thread color, useful in filling in cases where the
 * actual color of the thread doesn't matter but one needs to be declared
 * to test or render a pattern.
 *
 * Returns c: The resulting color.
 */
EmbThread emb_get_random_thread(void)
{
        EmbThread c;
        c.color.r = rand() % 256;
        c.color.g = rand() % 256;
        c.color.b = rand() % 256;
        strcpy(c.description, "random");
        strcpy(c.catalogNumber, "");
        return c;
}

/* . */
void binaryReadString(FILE *file, char *buffer, int maxLength)
{
        int i = 0;
        while (i < maxLength) {
                buffer[i] = (char)fgetc(file);
                if (buffer[i] == '\0') {
                        break;
                }
                i++;
        }
}

/* . */
void binaryReadUnicodeString(FILE *file, char *buffer, const int stringLength)
{
        int i = 0;
        for (i = 0; i < stringLength * 2; i++) {
                char input = (char)fgetc(file);
                if (input != 0) {
                        buffer[i] = input;
                }
        }
}

/*
 * Tests for the presence of a string a s in the supplied
 * a array.
 *
 * The end of the array is marked by an empty string.
 *
 * Returns 0 if not present 1 if present.
 */
int stringInArray(const char *s, const char **array)
{
        int i;
        for (i = 0; embstr_len(array[i]); i++) {
                if (!strncmp(s, array[i], 200)) {
                        return 1;
                }
        }
        return 0;
}

/* . */
int emb_readline(FILE *file, char *line, int maxLength)
{
        int i;
        char c;
        for (i = 0; i < maxLength - 1; i++) {
                if (!fread(&c, 1, 1, file)) {
                        break;
                }
                if (c == '\r') {
                        if (fread(&c, 1, 1, file) != 1) {
                                /* Incomplete Windows-style line ending. */
                                break;
                        }
                        if (c != '\n') {
                                fseek(file, -1L, SEEK_CUR);
                        }
                        break;
                }
                if (c == '\n') {
                        break;
                }
                *line = c;
                line++;
        }
        *line = 0;
        return i;
}

/* TODO: description */

/* Get the trim bounds object. */
void
get_trim_bounds(char const *s, char const **firstWord,
                char const **trailingSpace)
{
        char const *lastWord = 0;
        *firstWord = lastWord = s + string_whitespace(s);
        do {
                *trailingSpace = lastWord + string_whitespace(lastWord);
                lastWord = *trailingSpace + string_whitespace(*trailingSpace);
        } while (*lastWord != '\0');
}

/* . */
char *copy_trim(char const *s)
{
        char const *firstWord = 0, *trailingSpace = 0;
        char *result = 0;
        size_t newLength;

        get_trim_bounds(s, &firstWord, &trailingSpace);
        newLength = trailingSpace - firstWord;

        result = (char *)malloc(newLength + 1);
        memcpy(result, firstWord, newLength);
        result[newLength] = '\0';
        return result;
}

/* Optimizes the number (a num) for output to a text file and returns
 * it as a string (a str).
 */
char *emb_optOut(EmbReal num, char *str)
{
        char *str_end;
        /* Convert the number to a string */
        sprintf(str, "%.10f", num);
        /* Remove trailing zeroes */
        str_end = str + embstr_len(str);
        while (*--str_end == '0') ;
        str_end[1] = 0;
        /* Remove the decimal point if it happens to be an integer */
        if (*str_end == '.') {
                *str_end = 0;
        }
        return str;
}

/* . */
void embTime_initNow(EmbTime *t)
{
        printf("%d", t->year);
        /*
           time_t rawtime;
           struct tm* timeinfo;
           time(&rawtime);
           timeinfo = localtime(&rawtime);

           t->year   = timeinfo->tm_year;
           t->month  = timeinfo->tm_mon;
           t->day    = timeinfo->tm_mday;
           t->hour   = timeinfo->tm_hour;
           t->minute = timeinfo->tm_min;
           t->second = timeinfo->tm_sec;
         */
}

/* . */
EmbTime embTime_time(EmbTime *t)
{
        int divideByZero = 0;
        divideByZero = divideByZero / divideByZero;
        /* TODO: wrap time() from time.h and verify it works consistently */

        return *t;
}

/* a points a n_points a width a tolerence
 *
 * Remove points that lie in the middle of two short stitches that could
 * be one longer stitch. Repeat until none are found.
 */
static void
join_short_stitches(int *points, int *n_points, int width, int tolerence)
{
        int found = 1;
        while (found > 0) {
                int i;
                found = 0;
                for (i = *n_points - 2; i >= 0; i--) {
                        int st1 = points[i + 1] % width - points[i] % width;
                        int st2 = points[i + 2] % width - points[i + 1] % width;
                        int same_line =
                            (points[i + 1] / width == points[i] / width)
                            && (points[i + 2] / width == points[i + 1] / width);
                        if (st1 < tolerence && st2 < tolerence && same_line) {
                                found++;
                                break;
                        }
                }
                if (found) {
                        /* Remove the point. */
                        i++;
                        for (; i < *n_points; i++) {
                                points[i] = points[i + 1];
                        }
                        (*n_points)--;
                }
        }
}

/* a image a n_points a subsample_width a subsample_height
 * a threshold
 * Returns int*
 *
 * Identify darker pixels to put stitches in.
 */
static int *threshold_method(EmbImage *image, int *n_points,
                             int subsample_width, int subsample_height,
                             int threshold)
{
        int i, j;
        int *points;
        int height = image->height;
        int width = image->width;
        points = (int *)malloc((height / subsample_height)
                               * (width / subsample_width) * sizeof(int));
        *n_points = 0;
        for (i = 0; i < height / subsample_height; i++)
                for (j = 0; j < width / subsample_width; j++) {
                        EmbColor color;
                        int index =
                            subsample_height * i * width + subsample_width * j;
                        color.r = image->data[3 * index + 0];
                        color.g = image->data[3 * index + 1];
                        color.b = image->data[3 * index + 2];
                        if (color.r + color.g + color.b < threshold) {
                                points[*n_points] = index;
                                (*n_points)++;
                        }
                }
        return points;
}

/* a points a n_points a width a bias
 *
 * Greedy Algorithm
 * ----------------
 * For each point in the list find the shortest distance to
 * any possible neighbour, then perform a swap to make that
 * neighbour the next item in the list.
 *
 * To make the stitches lie more on one axis than the other
 * bias the distance operator to prefer horizontal direction.
 */
static void greedy_algorithm(int *points, int n_points, int width, EmbReal bias)
{
        int i, j;
        printf("points[0] = %d\n", points[0]);
        printf("n_points = %d\n", n_points);
        printf("width = %d\n", width);
        printf("bias = %f\n", bias);

        for (i = 0; i < n_points - 1; i++) {
                int stor;
                EmbReal shortest = 1.0e20;
                int next = i + 1;
                /* Find nearest neighbour. */
                int x1 = points[i] % width;
                int y1 = points[i] / width;
                for (j = i + 1; j < n_points; j++) {
                        int x, y;
                        EmbReal distance;
                        x = x1 - (points[j] % width);
                        if (x * x > shortest) {
                                continue;
                        }
                        y = y1 - (points[j] / width);
                        distance = x * x + bias * y * y;
                        if (distance < shortest) {
                                next = j;
                                shortest = distance;
                        }
                }
                if (i % 100 == 0) {
                        printf("%2.1f%%\n", (100.0 * i) / (1.0 * n_points));
                }
                /* swap points */
                stor = points[next];
                points[next] = points[i + 1];
                points[i + 1] = stor;
        }
}

/* a pattern a points a n_points
 * a scale a width a height
 */
static void
save_points_to_pattern(EmbPattern *pattern, int *points, int n_points,
                       EmbReal scale, int width, int height)
{
        int i;
        for (i = 0; i < n_points; i++) {
                int x, y;
                x = points[i] % width;
                y = height - points[i] / width;
                embp_addStitchAbs(pattern, scale * x, scale * y, NORMAL, 0);
        }
}

/* a pattern a image a threshhold
 *
 * Uses a threshhold method to determine where to put
 * lines in the fill.
 *
 * Needs to pass a "donut test", i.e. an image with black pixels where:
 *     10 < x*x + y*y < 20
 * over the area (-30, 30) x (-30, 30).
 *
 * Use render then image difference to see how well it passes.
 */
void embp_horizontal_fill(EmbPattern *pattern, EmbImage *image, int threshhold)
{
        /* Size of the crosses in millimeters. */
        EmbReal scale = 0.1;
        int sample_w = 3;
        int sample_h = 3;
        EmbReal bias = 1.2;
        int *points;
        int n_points;

        points =
            threshold_method(image, &n_points, sample_w, sample_h, threshhold);
        greedy_algorithm(points, n_points, image->width, bias);
        join_short_stitches(points, &n_points, image->width, 40);
        save_points_to_pattern(pattern, points, n_points, scale, image->width,
                               image->height);

        embp_end(pattern);
        safe_free(points);
}

/* a pattern a image a threshhold
 *
 * Uses a threshhold method to determine where to put
 * crosses in the fill.
 *
 * To improve this, we can remove the vertical stitches when two crosses
 * neighbour. Currently the simple way to do this is to chain crosses
 * that are neighbours exactly one ahead.
 */
void embp_crossstitch(EmbPattern *pattern, EmbImage *image, int threshhold)
{
        int i;
        /* Size of the crosses in millimeters. */
        EmbReal scale = 0.1;
        int sample_w = 5;
        int sample_h = 5;
        EmbReal bias = 1.0;
        int *points;
        int n_points;
        int width = 1000;
        points =
            threshold_method(image, &n_points, sample_w, sample_h, threshhold);
        greedy_algorithm(points, n_points, width, bias);

        for (i = 0; i < n_points; i++) {
                EmbReal x, y;
                x = points[i] % width;
                y = points[i] / width;
                printf("%f %f\n", x, y);
                embp_addStitchAbs(pattern, scale * x, scale * y, NORMAL, 0);
                embp_addStitchAbs(pattern, scale * (x + sample_w),
                                  scale * (y + sample_h), NORMAL, 0);
                embp_addStitchAbs(pattern, scale * x, scale * (y + sample_h),
                                  NORMAL, 0);
                embp_addStitchAbs(pattern, scale * (x + sample_w), scale * y,
                                  NORMAL, 0);
        }

        embp_end(pattern);
}

#if 0
/* a pattern
 * Returns StitchBlock*
 */
StitchBlock *BreakIntoColorBlocks(EmbPattern *pattern)
{
        int i;
        int sa2 = new StitchBlock();
        int oldColor = pattern->stitch_list->stitch[0].color;
        int color = pattern.ColorList[oldColor];
        sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch s = pattern->stitch_list->stitch[i];
                if (s.color != oldColor) {
                        yield return sa2;
                        sa2 = new StitchBlock();
                        color = pattern.ColorList[s.ColorIndex];
                        sa2.Thread =
                            new Thread(color.Red, color.Blue, color.Green);
                        oldColor = s.ColorIndex;
                }
                int vs = new VectorStitch { Xy = new Point(s.X, s.Y), Color =
                            s.ColorIndex
                };
                sa2.Stitches.Add(vs);
        }
        yield return sa2;
}

/* a blocks
 * Returns StitchBlock*
 */
StitchBlock *BreakIntoSeparateObjects(EmbStitchBlock *blocks)
{
        int i, block;
        EmbReal previousAngle = 0.0;
        for (block = 0; block < blocks->length; block++) {
                int stitches = new List < VectorStitch > ();
                block.Stitches[0].Type = VectorStitchType.Contour;
                block.Stitches[block.Stitches.Count - 1].Type =
                    VectorStitchType.Contour;

                for (int i = 0; i < block.Stitches.Count - 2; i++) {    /* step 0 */
                        EmbReal dx =
                            (emb_vector_relativeX
                             (block.Stitches[i].Xy, block.Stitches[i + 1].Xy,
                              block.Stitches[i + 2].Xy));
                        block.Stitches[i + 1].Type =
                            dx <=
                            0 ? VectorStitchType.Run : VectorStitchType.Contour;
                        block.Stitches[i].Angle =
                            GetAngle(block.Stitches[i], block.Stitches[i + 1]);
                        stitches.Add(block.Stitches[i].Clone());
                        if (i > 0) {
                                if ((block.Stitches[i].Type ==
                                     VectorStitchType.Contour)
                                    && fabs(block.Stitches[i].Angle -
                                            previousAngle) >
                                    (20 / 180 * embConstantPi)) {
                                        yield return new StitchBlock {
                                                Stitches = stitches,
                                                    Angle = stitches.Average(x =
                                                                             >x.Angle),
                                                    Thread =
                                                    new Thread(block.Thread.Red,
                                                               block.
                                                               Thread.Blue,
                                                               block.
                                                               Thread.Green)
                                        };
                                        stitches = new List < VectorStitch > ();

                                }
                        }
                }

                /* step 1 */
                for (i = 1; i < sa.Stitches.Count - 3; i++) {
                        if (sa.Stitches[i + 1].Type == VectorStitchType.Contour) {
                                float dy = emb_vector_relativeY(sa[i + 1].XY,
                                                                sa[i + 2].XY,
                                                                sa[i + 3].XY);
                                float dy2 =
                                    emb_vector_relativeY(sa[i].XY, sa[i + 1].XY,
                                                         sa[i + 2].XY);
                                float dy3 = emb_vector_relativeY(sa[i + 2].XY,
                                                                 sa[i + 3].XY,
                                                                 sa[i + 4].XY);
                                if (dy)
                                        if (sa.Stitches[i - 1].Type ==
                                            VectorStitchType.Run
                                            || sa.Stitches[i + 1].Type ==
                                            VectorStitchType.Run) {
                                                sa.Stitches[i].Type =
                                                    VectorStitchType.Tatami;
                                        } else {
                                                sa.Stitches[i].Type =
                                                    VectorStitchType.Satin;
                                        }
                        }
                }
        }
}

/* a stitchData
 * Returns StitchObject*
 */
StitchObject *FindOutline(EmbStitchBlock *stitchData)
{
        int currColorIndex = 0, sa;
        int pOdd = new List < Point > ();
        int pEven = new List < Point > ();
        for (sa = 0; sa < stitchData->count; sa++) {
                if (sa.Stitches.Count > 0) {
                        sa.Stitches[0].Type = VectorStitchType.Contour;
                        sa.Stitches[sa.Stitches.Count - 1].Type =
                            VectorStitchType.Contour;
                        /* step 0 */
                        for (int i = 0; i < sa.Stitches.Count - 2; i++) {
                                float dx =
                                    (GetRelativeX
                                     (sa.Stitches[i].Xy, sa.Stitches[i + 1].Xy,
                                      sa.Stitches[i + 2].Xy));
                                sa.Stitches[i + 1].Type =
                                    dx <=
                                    0 ? VectorStitchType.
                                    Run : VectorStitchType.Contour;
                                sa.Stitches[i].Angle =
                                    emb_vector_angle(sa.Stitches[i],
                                                     sa.Stitches[i + 1]);
                        }
                        /* step 1 */
                        for (int i = 1; i < sa.Stitches.Count - 3; i++) {
                                if (sa.Stitches[i + 1].Type ==
                                    VectorStitchType.Contour) {
                                        float dy =
                                            emb_vector_relativeY(sa[i + 1].XY,
                                                                 sa[i + 2].XY,
                                                                 sa[i + 3].XY);
                                        float dy2 =
                                            emb_vector_relativeY(sa[i].XY,
                                                                 sa[i + 1].XY,
                                                                 sa[i + 2].XY);
                                        float dy3 =
                                            emb_vector_relativeY(sa[i + 2].XY,
                                                                 sa[i + 3].XY,
                                                                 sa[i + 4].XY);
                                        if (dy)
                                                if (sa.Stitches[i - 1].Type ==
                                                    VectorStitchType.Run
                                                    || sa.Stitches[i +
                                                                   1].Type ==
                                                    VectorStitchType.Run) {
                                                        sa.Stitches[i].Type =
                                                            VectorStitchType.Tatami;
                                                } else {
                                                        sa.Stitches[i].Type =
                                                            VectorStitchType.Satin;
                                                }
                                }
                        }
                }

                int oddEven = 0;
                foreach(VectorStitch t in sa.Stitches) {
                        if ((t.Type == VectorStitchType.Contour)
                            && (oddEven % 2) == 0) {
                                pEven.Add(t.Xy);

                                oddEven++;
                        } else if ((t.Type == VectorStitchType.Contour)
                                   && (oddEven % 2) == 1) {
                                pOdd.Add(t.Xy);
                                oddEven++;
                        }
                }
                currColorIndex++;
                int so = new StitchObject { SideOne = pEven, SideTwo =
                            pOdd, ColorIndex = currColorIndex
                };
                yield return so;
                pEven = new List < Point > ();
                pOdd = new List < Point > ();
                /* break; */
        }
}

/* a p
 * Returns EmbPattern
 */
EmbPattern DrawGraphics(EmbPattern p)
{
        int stitchData = BreakIntoColorBlocks(p);

        int outBlock =
            new List < StitchBlock > (BreakIntoSeparateObjects(stitchData));
        foreach(var block in stitchData) {
                foreach(var stitch in block.Stitches) {
                        if (stitch.Angle != 0) {
                                int aaa = 1;
                        }
                }
        }
        int xxxxx = outBlock;
        int objectsFound = FindOutline(stitchData);
        int outPattern = new Pattern();
        outPattern.AddColor(new Thread(255, 0, 0, "none", "None"));
        int colorIndex = outPattern.ColorList.Count - 1;
        int r = new Random();
        foreach(StitchObject stitchObject in objectsFound) {
                if (stitchObject.SideOne.Count > 1
                    && stitchObject.SideTwo.Count > 1) {
                        outPattern.AddColor(new
                                            Thread((byte) (r.Next() % 256),
                                                   (byte) (r.Next() % 256),
                                                   (byte) (r.Next() % 256),
                                                   "none", "None"));
                        colorIndex++;
                        outPattern.AddStitchRelative(0, 0, StitchTypes.Stop);
                        int points = stitchObject.Generate2(75);
                        foreach(var point in points) {
                                outPattern.AddStitchAbsolute(point.X, point.Y,
                                                             StitchTypes.Normal);
                        }
                        break;
                        StitchObject stitchObject = objectsFound[1];
                        ))
                            if (stitchObject.SideOne.Count > 0) {
                                outPattern.stitch_list.Add(new
                                                           Stitch
                                                           (stitchObject.SideOne
                                                            [0].X,
                                                            stitchObject.SideOne
                                                            [0].Y,
                                                            StitchType.Jump,
                                                            colorIndex));
                        }
                        foreach(Point t in stitchObject.SideOne) {

                                outPattern.stitch_list.Add(new Stitch(t.X, t.Y,
                                                                      StitchType.Normal,
                                                                      colorIndex));
                        }
                        foreach(Point t in stitchObject.SideTwo) {
                                outPattern.stitch_list.Add(new Stitch(t.X, t.Y,
                                                                      StitchType.Normal,
                                                                      colorIndex));
                        }
                        break;
                }
        }
        outPattern.AddStitchRelative(0, 0, StitchTypes.End);
        return outPattern;
        /*
           return (SimplifyOutline(outPattern));
         */
}

/* a pattern
 * Returns EmbPattern
 */
EmbPattern SimplifyOutline(EmbPattern pattern) {
        int v = new Vertices();
        v.AddRange(pattern.
                   stitch_list.Select(point = >new Vector2(point.X, point.Y)));
        int output = SimplifyTools.DouglasPeuckerSimplify(v, 10);
        int patternOut = new Pattern();
        foreach(var color in pattern.ColorList) {
                patternOut.AddColor(color);
        }

        foreach(var vertex in output) {
                patternOut.AddStitchAbsolute(vertex.X, vertex.Y,
                                             StitchTypes.Normal);
        }
        patternOut.AddStitchRelative(0, 0, StitchTypes.End);
        return patternOut;
}

bool[]_usePt;
EmbReal _distanceTolerance;

/* Removes all collinear points on the polygon.
 *
 * a vertices
 * a collinearityTolerance
 * Returns Vertices
 */
Vertices CollinearSimplify(Vertices vertices, float collinearityTolerance) {
        /* We can't simplify polygons under 3 vertices */
        if (vertices.Count < 3)
                return vertices;

        int simplified = new Vertices();

        for (int i = 0; i < vertices.Count; i++) {
                int prevId = vertices.PreviousIndex(i);
                int nextId = vertices.NextIndex(i);

                Vector2 prev = vertices[prevId];
                Vector2 current = vertices[i];
                Vector2 next = vertices[nextId];

                /* If they collinear, continue */
                if (emb_vector_collinear
                    (ref prev, ref current, ref next, collinearityTolerance))
                        continue;

                simplified.Add(current);
        }

        return simplified;
}

/* vertices
 * Returns Vertices
 *
 * Removes all collinear points on the polygon. Has a default bias of 0.
 *
 * param vertices: The polygon that needs simplification.
 * returns: A simplified polygon.
 */
Vertices CollinearSimplify(Vertices vertices) {
        return CollinearSimplify(vertices, 0);
}

/* vertices
 * a distanceTolerance
 * Returns Vertices
 *
 * Ramer-Douglas-Peucker polygon simplification algorithm.
 * This is the general recursive version that does not use the
 * speed-up technique by using the Melkman convex hull.
 * If you pass in 0, it will remove all collinear points.
 *
 * \todo Ramer-Douglas-Peucker citation
 */
Vertices DouglasPeuckerSimplify(Vertices vertices, float distanceTolerance) {
        _distanceTolerance = distanceTolerance;

        _usePt = new bool[vertices.Count];
        for (int i = 0; i < vertices.Count; i++) {
                _usePt[i] = true;
        }
        SimplifySection(vertices, 0, vertices.Count - 1);
        int result = new Vertices();
        result.AddRange(vertices.Where((t, i) = >_usePt[i]));
        return result;
}

/*  vertices a i a j */
void SimplifySection(Vertices vertices, int i, int j) {
        if ((i + 1) == j)
                return;

        Vector2 a = vertices[i];
        Vector2 b = vertices[j];
        EmbReal maxDistance = -1.0;
        int maxIndex = i;
        for (int k = i + 1; k < j; k++) {
                EmbReal distance = DistancePointLine(vertices[k], a, b);

                if (distance > maxDistance) {
                        maxDistance = distance;
                        maxIndex = k;
                }
        }
        if (maxDistance <= _distanceTolerance) {
                for (int k = i + 1; k < j; k++) {
                        _usePt[k] = 0;
                }
        } else {
                SimplifySection(vertices, i, maxIndex);
                SimplifySection(vertices, maxIndex, j);
        }
}

/* p a a a b
 * Returns EmbReal
 */
EmbReal DistancePointLine(EmbVector p, EmbVector a, EmbVector b) {
        /* if start == end, then use point-to-point distance */
        if (a.X == b.X && a.Y == b.Y)
                return DistancePointPoint(p, a);

        /* otherwise use comp.graphics.algorithms Frequently Asked Questions method */
        /* (1)               AC dot AB
           r =   ---------
           ||AB||^2

           r has the following meaning:
           r=0 Point = A
           r=1 Point = B
           r<0 Point is on the backward extension of AB
           r>1 Point is on the forward extension of AB
           0<r<1 Point is interior to AB
         */

        EmbReal r = ((p.X - a.X) * (b.X - a.X) + (p.Y - a.Y) * (b.Y - a.Y))
            / ((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y));

        if (r <= 0.0)
                return DistancePointPoint(p, a);
        if (r >= 1.0)
                return DistancePointPoint(p, b);

        /* (2)
           (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)
           s = -----------------------------
           Curve^2

           Then the distance from C to Point = |s|*Curve.
         */

        EmbReal s = ((a.Y - p.Y) * (b.X - a.X) - (a.X - p.X) * (b.Y - a.Y))
            / ((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y));

        return fabs(s) *
            sqrt(((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y)));
}

/* vertices a areaTolerance
 * Returns public
 *
 * From physics2d.net.
 */
public Vertices ReduceByArea(Vertices vertices, float areaTolerance) {
        if (vertices.Count <= 3)
                return vertices;

        if (areaTolerance < 0) {
                throw new ArgumentOutOfRangeException("areaTolerance",
                                                      "must be equal to or greater then zero.");
        }

        int result = new Vertices();
        Vector2 v3;
        Vector2 v1 = vertices[vertices.Count - 2];
        Vector2 v2 = vertices[vertices.Count - 1];
        areaTolerance *= 2;
        for (int index = 0; index < vertices.Count; ++index, v2 = v3) {
                if (index == vertices.Count - 1) {
                        if (result.Count == 0) {
                                throw new
                                    ArgumentOutOfRangeException("areaTolerance",
                                                                "The tolerance is too high!");
                        }
                        v3 = result[0];
                } else {
                        v3 = vertices[index];
                }
                float old1, old2, new1;
                MathUtils.Cross(ref v1, ref v2, out old1);
                MathUtils.Cross(ref v2, ref v3, out old2);
                MathUtils.Cross(ref v1, ref v3, out new1);
                if (fabs(new1 - (old1 + old2)) > areaTolerance) {
                        result.Add(v2);
                        v1 = v2;
                }
        }
        return result;
}

/* vertices a tolerance
 *
 * From Eric Jordan's convex decomposition library.
 * Merges all parallel edges in the list of vertices.
 */
void
 MergeParallelEdges(EmbArray * vertices, float tolerance) {
        int i;
        if (vertices.Count <= 3) {
                /* Can't do anything useful here to a triangle. */
                return;
        }

        int mergeMe = new bool[vertices.Count];
        int newNVertices = vertices.Count;

        /* Gather points to process */
        for (i = 0; i < vertices->count; i++) {
                EmbVector delta0, delta1;
                int lower = (i == 0) ? (vertices.Count - 1) : (i - 1);
                int upper = (i == vertices.Count - 1) ? (0) : (i + 1);

                delta0 = emb_vector_subtract(vertices[i], vertices[lower]);
                delta1 = emb_vector_subtract(vertices[upper], vertices[i]);
                float norm0 = emb_vector_length(delta0);
                float norm1 = emb_vector_length(delta0);

                if (!(norm0 > 0.0f && norm1 > 0.0f) && newNVertices > 3) {
                        /* Merge identical points */
                        mergeMe[i] = 1;
                        newNVertices--;
                }

                delta0 = emb_vector_normalize(delta0);
                delta1 = emb_vector_normalize(delta1);
                float cross = emb_vector_cross(delta0, delta1);
                float dot = emb_vector_dot(delta0, delta1);

                if (fabs(cross) < tolerance && dot > 0 && newNVertices > 3) {
                        mergeMe[i] = 1;
                        newNVertices--;
                } else {
                        mergeMe[i] = 0;
                }
        }

        if (newNVertices == vertices.Count || newNVertices == 0)
                return;

        int currIndex = 0;

        /* Copy the vertices to a new list and clear the old */
        int oldVertices = new Vertices(vertices);
        vertices.Clear();

        for (i = 0; i < oldVertices.Count; i++) {
                if (mergeMe[i] || newNVertices == 0
                    || currIndex == newNVertices)
                        continue;

                vertices.Add(oldVertices[i]);
                currIndex++;
        }
}
#endif

void embPolygon_reduceByDistance(EmbArray * vertices, EmbArray * simplified,
                                 float distance);
void embPolygon_reduceByNth(EmbArray * vertices, EmbArray * out, int nth);

/* vertices a simplified a distance
 *
 * Reduces the polygon by distance.
 *
 * This is a non-destructive function, so the caller is responsible for
 * freeing "vertices" if they choose to keep "simplified".
 */
void embPolygon_reduceByDistance(EmbArray * vertices, EmbArray * simplified,
                                 float distance) {
        int i;
        /* We can't simplify polygons under 3 vertices */
        if (vertices->count < 3) {
                emb_array_copy(simplified, vertices);
                return;
        }

        for (i = 0; i < vertices->count; i++) {
                EmbVector delta;
                int nextId = (i + 1) % vertices->count;

                delta =
                    emb_vector_subtract(vertices->geometry[nextId].
                                        object.vector,
                                        vertices->geometry[i].object.vector);

                /* If they are closer than the distance, continue */
                if (emb_vector_length(delta) < distance) {
                        continue;
                }

                emb_array_addVector(simplified,
                                    vertices->geometry[i].object.vector);
        }
}

/* vertices a out a nth
 *
 * Reduces the polygon by removing the Nth vertex in the vertices list.
 * This is a non-destructive function, so the caller is responsible for
 * freeing vertices if they choose to keep out.
 */
void
 embPolygon_reduceByNth(EmbArray * vertices, EmbArray * out, int nth) {
        int i;
        /* We can't simplify polygons under 3 vertices */
        if (vertices->count < 3) {
                emb_array_copy(out, vertices);
                return;
        }

        for (i = 0; i < vertices->count; i++) {
                if (i != nth) {
                        emb_array_addVector(out,
                                            vertices->geometry[i].
                                            object.vector);
                }
        }
}

/* p1 a p2
 * Returns EmbPattern*
 */
EmbPattern *embp_combine(EmbPattern * p1, EmbPattern * p2) {
        int i;
        EmbPattern *out = embp_create();
        for (i = 0; i < p1->stitch_list->count; i++) {
                emb_array_addStitch(out->stitch_list,
                                    p1->stitch_list->stitch[i]);
        }
        for (i = 0; i < p2->stitch_list->count; i++) {
                emb_array_addStitch(out->stitch_list,
                                    p2->stitch_list->stitch[i]);
        }
        /* These need to be merged, not appended. */
        for (i = 0; i < p1->thread_list->count; i++) {
                embp_addThread(out, p1->thread_list->thread[i]);
        }
        for (i = 0; i < p2->thread_list->count; i++) {
                embp_addThread(out, p2->thread_list->thread[i]);
        }
        return out;
}

/* p a arc a thread_index a style
 */
void
 embp_stitchArc(EmbPattern * p, EmbArc arc, int thread_index, int style) {
        printf("DEBUG stitchArc (unfinished): %f %f %d %d\n",
               p->home.x, arc.start.x, thread_index, style);
}

/* p a circle a thread_index a style
 *
 * style determines:
 *     stitch density
 *     fill pattern
 *     outline or fill
 *
 * For now it's a straight fill of 1000 stitches of the whole object by
 * default.
 *
 * Consider the intersection of a line in direction "d" that passes through
 * the disc with center "c", radius "r". The start and end points are:
 *
 *     $(c-r(d/|d|), c + r(d/|d|))$
 *
 * Lines that are above and below this with an even seperation $s$ can be
 * found by taking the point on the line to be c+sn where the $n$ is the
 * unit normal vector to $d$ and the vector to be $d$ again. The
 * intersection points are therefore a right angled triangle, with one side
 * r, another s and the third the length to be solved, by Pythagoras we
 * have:
 *
 *    $(c + sn - \sqrt{r^2-s^2}(d/|d|), c + sn + \sqrt{r^2-s^2}(d/|d|))$
 *
 * repeating this process gives us all the end points and the fill only
 * alters these lines by splitting the ones longer than some tolerence.
 */
void
 embp_stitchCircle(EmbPattern * p, EmbCircle circle, int thread_index,
                   int style) {
        float s;
        float seperation = 0.1;
        EmbVector direction = { 1.0, 1.0 };
        EmbVector normal = { -1.0, 1.0 };
        direction = emb_vector_normalize(direction);
        normal = emb_vector_normalize(normal);
        printf("style %d\n", style);
        for (s = -circle.radius; s < circle.radius; s += seperation) {
                EmbLine line;
                float length = sqrt(circle.radius * circle.radius - s * s);
                EmbVector scaled = emb_vector_scale(normal, s);
                line.start = emb_vector_add(circle.center, scaled);
                scaled = emb_vector_scale(direction, length);
                line.start = emb_vector_subtract(line.start, scaled);
                scaled = emb_vector_scale(normal, s);
                line.end = emb_vector_add(circle.center, scaled);
                scaled = emb_vector_scale(direction, length);
                line.end = emb_vector_add(line.end, scaled);
                /* Split long stitches here. */
                embp_addStitchAbs(p, line.start.x, line.start.y, NORMAL,
                                  thread_index);
                embp_addStitchAbs(p, line.end.x, line.end.y, NORMAL,
                                  thread_index);
        }
}

/* a p a ellipse a thread_index a style
 *
 * \todo finish stitchEllipse
 */
void
 embp_stitchEllipse(EmbPattern * p, EmbEllipse ellipse, int thread_index,
                    int style) {
        printf("DEBUG stitchEllipse: %f %f %d %d\n", p->home.x,
               ellipse.center.x, thread_index, style);
}

/*a p a rect a thread_index a style
 *
 * \todo finish stitch path
 */
void
 embp_stitchPath(EmbPattern * p, EmbPath path, int thread_index, int style) {
        printf("DEBUG stitchPath: %f %d %d %d\n",
               p->home.x, path.pointList->count, thread_index, style);
}

/*a p a rect a thread_index a style
 *
 * \todo finish stitch polygon
 */
void
 embp_stitchPolygon(EmbPattern * p, EmbPolygon polygon, int thread_index,
                    int style) {
        printf("DEBUG stitchPolygon: %f %d %d %d\n", p->home.x,
               polygon.pointList->count, thread_index, style);
}

/* a p a rect a thread_index a style
 *
 * \todo finish stitch polyline
 */
void
 embp_stitchPolyline(EmbPattern * p, EmbPolyline polyline, int thread_index,
                     int style) {
        printf("DEBUG stitchPolyline: %f %d %d %d\n", p->home.x,
               polyline.pointList->count, thread_index, style);
}

/* a p a rect a thread_index a style
 *
 * Here we just stitch the rectangle in the direction of it's longer side.
 */
void
 embp_stitchRect(EmbPattern * p, EmbRect rect, int thread_index, int style) {
        EmbReal seperation = 0.1;
        if (style > 0) {
                puts("WARNING: Only style 0 has been implimented.");
        }
        if (rect.w > rect.h) {
                float s;
                for (s = rect.y; s < rect.y + rect.h; s += seperation) {
                        /* Split long stitches here. */
                        embp_addStitchAbs(p, rect.y, s, NORMAL, thread_index);
                        embp_addStitchAbs(p, rect.y + rect.h, s, NORMAL,
                                          thread_index);
                }
        } else {
                float s;
                for (s = rect.x; s < rect.x + rect.w; s += seperation) {
                        /* Split long stitches here. */
                        embp_addStitchAbs(p, s, rect.x, NORMAL, thread_index);
                        embp_addStitchAbs(p, s, rect.x + rect.w, NORMAL,
                                          thread_index);
                }
        }
}

/* a p a rect a thread_index a style
 */
void
 embp_stitchText(EmbPattern * p, EmbRect rect, int thread_index, int style) {
        printf("DEBUG: %f %f %d %d", p->home.x, rect.y, thread_index, style);
}

/* a p
 */
void
 embp_convertGeometry(EmbPattern * p) {
        int i;
        for (i = 0; i < p->geometry->count; i++) {
                EmbGeometry g = p->geometry->geometry[i];
                switch (g.type) {
                case EMB_ARC:{
                                /* To Do make the thread up here. */
                                embp_stitchArc(p, g.object.arc, 0, 0);
                                break;
                        }
                case EMB_CIRCLE:{
                                /* To Do make the thread up here. */
                                embp_stitchCircle(p, g.object.circle, 0, 0);
                                break;
                        }
                case EMB_ELLIPSE:{
                                /* To Do make the thread up here. */
                                embp_stitchEllipse(p, g.object.ellipse, 0, 0);
                                break;
                        }
                case EMB_RECT:{
                                /* To Do make the thread up here. */
                                embp_stitchRect(p, g.object.rect, 0, 0);
                                break;
                        }
                default:
                        break;
                }
        }
        /* Now ignore the geometry when writing. */
        p->geometry->count = 0;
}

/* Check that the pointer isn't NULL before freeing. */
void
 safe_free(void *data) {
        if (data) {
                free(data);
                data = 0;
        }
}

unsigned char
 char_to_lower(unsigned char a) {
        if (a >= 'A' && a <= 'Z') {
                a = a - 'A' + 'a';
        }
        return a;
}

/* The distance between the arrays a and b of length size. */
float
 image_diff(unsigned char *a, unsigned char *b, int size) {
        int i;
        float total = 0.0;
        for (i = 0; i < size; i++) {
                int diff = a[i] - b[i];
                total += diff * diff;
        }
        return total;
}

/* Render the pattern a p to the file with name a fname.
 * Return whether it was successful as an int.
 *
 * Basic Render
 * ------------
 *
 * Backends rendering to nanosvg/stb_image.
 *
 * The caller is responsible for the memory in p.
 */
int
 embp_render(EmbPattern * p, char *fname) {
        printf("Cannot render %p, %s\n", p, fname);
/*
    const char *tmp_fname = "libembroidery_temp.svg";
    NSVGimage *image = NULL;
    NSVGrasterizer rast;
    unsigned char *img_data = NULL;
    embp_writeAuto(p, tmp_fname);
    image = nsvgParseFromFile(tmp_fname, "px", 96.0f);
    img_data = malloc(4*image->width*image->height);
    nsvgRasterize(
        &rast,
        image,
        0, 0, 1,
        img_data,
        image->width,
        image->height,
        4*image->width);
    stbi_write_png(
         fname,
         image->width,
        image->height,
        4,
        img_data,
        4*image->width);
*/
        return 0;
}

/* Simulate the stitching of a pattern, using the image for rendering
 * hints about how to represent the pattern.
 */
int
 embp_simulate(EmbPattern * pattern, char *fname) {
        embp_render(pattern, fname);
        return 0;
}

/* The file is for the management of the main struct: EmbPattern.
 *
 * Returns a pointer to an EmbPattern. It is created on the heap.
 * The caller is responsible for freeing the allocated memory with
 * embp_free().
 *
 * Returns EmbPattern*
 */
EmbPattern *embp_create(void) {
        EmbPattern *p = (EmbPattern *) malloc(sizeof(EmbPattern));
        if (!p) {
                printf("ERROR: emb-pattern.c embp_create(), ");
                printf("unable to allocate memory for p\n");
                return 0;
        }
        p->dstJumpsPerTrim = 6;
        p->home.x = 0.0;
        p->home.y = 0.0;
        p->currentColorIndex = 0;
        p->stitch_list = emb_array_create(EMB_STITCH);
        p->thread_list = emb_array_create(EMB_THREAD);
        p->hoop_height = 0.0;
        p->hoop_width = 0.0;
        p->geometry = emb_array_create(EMB_LINE);
        return p;
}

/* a p a length
 */
void
 embp_hideStitchesOverLength(EmbPattern * p, int length) {
        EmbVector prev;
        int i;
        prev.x = 0.0;
        prev.y = 0.0;

        if (!p) {
                printf("ERROR: emb-pattern.c embp_hideStitchesOverLength(), ");
                printf("p argument is null\n");
                return;
        }
        for (i = 0; i < p->stitch_list->count; i++) {
                if ((fabs(p->stitch_list->stitch[i].x - prev.x) > length)
                    || (fabs(p->stitch_list->stitch[i].y - prev.y) > length)) {
                        p->stitch_list->stitch[i].flags |= TRIM;
                        p->stitch_list->stitch[i].flags &= ~NORMAL;
                }
                prev.x = p->stitch_list->stitch[i].x;
                prev.y = p->stitch_list->stitch[i].y;
        }
}

/* a pattern a thread
 * Returns int
 */
int
 embp_addThread(EmbPattern * pattern, EmbThread thread) {
        if (pattern->thread_list->count + 1 > pattern->thread_list->length) {
                if (!emb_array_resize(pattern->thread_list)) {
                        return 0;
                }
        }
        pattern->thread_list->thread[pattern->thread_list->count] = thread;
        pattern->thread_list->count++;
        return 1;
}

/* a p
 */
void
 embp_fixColorCount(EmbPattern * p) {
        /* fix color count to be max of color index. */
        int maxColorIndex = 0, i;

        if (!p) {
                printf("ERROR: emb-pattern.c embp_fixColorCount(), ");
                printf("p argument is null\n");
                return;
        }
        for (i = 0; i < p->stitch_list->count; i++) {
/*        printf("%d %d\n", list->stitch.color, maxColorIndex);*/
                maxColorIndex =
                    EMB_MAX(maxColorIndex, p->stitch_list->stitch[i].color);
        }
        if (p->thread_list->count == 0 || maxColorIndex == 0) {
                embp_addThread(p, black_thread);
        } else {
                if (maxColorIndex > 0) {
                        while (p->thread_list->count <= maxColorIndex) {
/*        printf("%d %d\n", p->n_threads, maxColorIndex);*/
                                embp_addThread(p, emb_get_random_thread());
                        }
                }
        }
        /*
           while (p->threadLists->count > (maxColorIndex + 1)) {
           TODO: erase last color    p->threadList.pop_back();
           }
         */
}

/* Copies all of the Embstitch_list data to
 * EmbPolylineObjectList data for pattern (a p).
 */
void
 embp_copystitch_listToPolylines(EmbPattern * p) {
        int breakAtFlags, i;
        EmbPoint point;
        EmbColor color;

        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_copystitch_listToPolylines(), ");
                printf("p argument is null\n");
                return;
        }

        breakAtFlags = (STOP | JUMP | TRIM);

        for (i = 0; i < p->stitch_list->count; i++) {
                EmbArray *pointList = 0;
                for (; i < p->stitch_list->count; i++) {
                        EmbStitch st = p->stitch_list->stitch[i];
                        if (st.flags & breakAtFlags) {
                                break;
                        }
                        if (!(st.flags & JUMP)) {
                                if (!pointList) {
                                        pointList = emb_array_create(EMB_POINT);
                                        color =
                                            p->thread_list->thread[st.
                                                                   color].color;
                                }
                                point.position.x = st.x;
                                point.position.y = st.y;
                                emb_array_addPoint(pointList, point);
                        }
                }

                /* NOTE: Ensure empty polylines are not created. This is critical. */
                if (pointList) {
                        EmbPolyline currentPolyline;
                        currentPolyline.pointList = pointList;
                        currentPolyline.color = color;
                        /* TODO: Determine what the correct value should be */
                        currentPolyline.lineType = 1;

                        emb_array_addPolyline(p->geometry, currentPolyline);
                }
        }
}

/* Copies all of the EmbPolylineObjectList data to Embstitch_list
 * data for pattern (a p).
 */
void
 embp_copyPolylinesTostitch_list(EmbPattern * p) {
        int firstObject = 1, i, j;
        /*int currentColor = polyList->polylineObj->color TODO: polyline color */

        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_copyPolylinesTostitch_list(), ");
                printf("p argument is null\n");
                return;
        }
        for (i = 0; i < p->geometry->count; i++) {
                EmbPolyline currentPoly;
                EmbArray *currentPointList;
                EmbThread thread;

                if (p->geometry->geometry[i].type != EMB_POLYLINE) {
                        continue;
                }

                currentPoly = p->geometry->geometry[i].object.polyline;
                currentPointList = currentPoly.pointList;

                strcpy(thread.catalogNumber, "");
                thread.color = currentPoly.color;
                strcpy(thread.description, "");
                embp_addThread(p, thread);

                if (!firstObject) {
                        embp_addStitchAbs(p,
                                          currentPointList->geometry[0].
                                          object.point.position.x,
                                          currentPointList->geometry[0].
                                          object.point.position.y, TRIM, 1);
                        embp_addStitchRel(p, 0.0, 0.0, STOP, 1);
                }

                embp_addStitchAbs(p,
                                  currentPointList->geometry[0].object.
                                  point.position.x,
                                  currentPointList->geometry[0].object.
                                  point.position.y, JUMP, 1);
                for (j = 1; j < currentPointList->count; j++) {
                        EmbVector v =
                            currentPointList->geometry[j].object.point.position;
                        embp_addStitchAbs(p, v.x, v.y, NORMAL, 1);
                }
                firstObject = 0;
        }
        embp_addStitchRel(p, 0.0, 0.0, END, 1);
}

/* Moves all of the Embstitch_list data to EmbPolylineObjectList
 * data for pattern (a p).
 */
void
 embp_movestitch_listToPolylines(EmbPattern * p) {
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_movestitch_listToPolylines(), p argument is null\n");
                return;
        }
        embp_copystitch_listToPolylines(p);
        /* Free the stitch_list and threadList since their data has now been transferred to polylines */
        p->stitch_list->count = 0;
        p->thread_list->count = 0;
}

/* Moves all of the EmbPolylineObjectList data to Embstitch_list
 * data for pattern (a p).
 */
void
 embp_movePolylinesTostitch_list(EmbPattern * p) {
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_movePolylinesTostitch_list(), p argument is null\n");
                return;
        }
        embp_copyPolylinesTostitch_list(p);
}

/* Adds a stitch to the pattern (a p) at the absolute position
 * (a x,a y). Positive y is up. Units are in millimeters.
 */
void
 embp_addStitchAbs(EmbPattern * p, EmbReal x, EmbReal y,
                   int flags, int isAutoColorIndex) {
        EmbStitch s;

        if (!p) {
                printf("ERROR: emb-pattern.c embp_addStitchAbs(), ");
                printf("p argument is null\n");
                return;
        }

        if (flags & END) {
                if (p->stitch_list->count == 0) {
                        return;
                }
                /* Prevent unnecessary multiple END stitches */
                if (p->stitch_list->
                    stitch[p->stitch_list->count - 1].flags & END) {
                        printf
                            ("ERROR: emb-pattern.c embp_addStitchAbs(), found multiple END stitches\n");
                        return;
                }
                embp_fixColorCount(p);
                /* HideStitchesOverLength(127); TODO: fix or remove this */
        }

        if (flags & STOP) {
                if (p->stitch_list->count == 0) {
                        return;
                }
                if (isAutoColorIndex) {
                        p->currentColorIndex++;
                }
        }

        /* NOTE: If the stitch_list is empty, we will create it before adding
           stitches to it. The first coordinate will be the HOME position. */
        if (p->stitch_list->count == 0) {
                /* NOTE: Always HOME the machine before starting any stitching */
                EmbStitch h;
                h.x = p->home.x;
                h.y = p->home.y;
                h.flags = JUMP;
                h.color = p->currentColorIndex;
                emb_array_addStitch(p->stitch_list, h);
        }
        s.x = x;
        s.y = y;
        s.flags = flags;
        s.color = p->currentColorIndex;
        emb_array_addStitch(p->stitch_list, s);
}

/* Adds a stitch to the pattern (a p) at the relative position
 * (a dx,a dy) to the previous stitch. Positive y is up.
 * Units are in millimeters.
 */
void
 embp_addStitchRel(EmbPattern * p, EmbReal dx, EmbReal dy,
                   int flags, int isAutoColorIndex) {
        EmbReal x, y;
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_addStitchRel(), p argument is null\n");
                return;
        }
        if (p->stitch_list->count > 0) {
                EmbStitch st =
                    p->stitch_list->stitch[p->stitch_list->count - 1];
                x = st.x + dx;
                y = st.y + dy;
        } else {
                /* NOTE: The stitch_list is empty, so add it to the HOME position.
                 * The embstitch_list_create function will ensure the first coordinate is at the HOME position. */
                x = p->home.x + dx;
                y = p->home.y + dy;
        }
        embp_addStitchAbs(p, x, y, flags, isAutoColorIndex);
}

/* Change the currentColorIndex of pattern a p to a index.
 */
void
 embp_changeColor(EmbPattern * p, int index) {
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_changeColor(), p argument is null\n");
                return;
        }
        p->currentColorIndex = index;
}

/* Very simple scaling of the x and y axis for every point.
 * Doesn't insert or delete stitches to preserve density.
 */
void
 embp_scale(EmbPattern * p, EmbReal scale) {
        int i;
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_scale(), p argument is null\n");
                return;
        }

        for (i = 0; i < p->stitch_list->count; i++) {
                p->stitch_list->stitch[i].x *= scale;
                p->stitch_list->stitch[i].y *= scale;
        }
}

/* Returns an EmbRect that encapsulates all stitches and objects in the
 * pattern (a p).
 */
EmbRect embp_bounds(EmbPattern * p) {
        EmbRect r;
        EmbStitch pt;
        int i, j;

        r.x = 0.0;
        r.y = 0.0;
        r.w = 1.0;
        r.h = 1.0;

        if (!p) {
                printf("ERROR: emb-pattern.c embp_bounds(), ");
                printf("p argument is null\n");
                return r;
        }

        /* Calculate the bounding rectangle.  It's needed for smart repainting. */
        /* TODO: Come back and optimize this mess so that after going thru all objects
         * and stitches, if the rectangle isn't reasonable, then return a default rect
         */
        if ((p->stitch_list->count == 0) && (p->geometry->count == 0)) {
                return r;
        }
        r.x = -99999.0;
        r.y = -99999.0;
        double right = 99999.0;
        double bottom = 99999.0;

        for (i = 0; i < p->stitch_list->count; i++) {
                /* If the point lies outside of the accumulated bounding
                 * rectangle, then inflate the bounding rect to include it. */
                pt = p->stitch_list->stitch[i];
                if (!(pt.flags & TRIM)) {
                        r.x = EMB_MAX(r.x, pt.x);
                        r.y = EMB_MAX(r.y, pt.y);
                        right = EMB_MIN(right, pt.x);
                        bottom = EMB_MIN(bottom, pt.y);
                }
        }

        for (i = 0; i < p->geometry->count; i++) {
                EmbGeometry g = p->geometry->geometry[i];
                switch (g.type) {
                case EMB_ARC:{
                                /* TODO: embp_calcBoundingBox for arcs,
                                   for now just checks the start point */
                                EmbArc arc = g.object.arc;
                                r.x = EMB_MIN(r.x, arc.start.x);
                                r.y = EMB_MIN(r.y, arc.start.y);
                                right = EMB_MAX(right, arc.start.x);
                                bottom = EMB_MAX(bottom, arc.start.y);
                                break;
                        }
                case EMB_CIRCLE:{
                                EmbCircle circle = g.object.circle;
                                r.x =
                                    EMB_MIN(r.x,
                                            circle.center.x - circle.radius);
                                r.y =
                                    EMB_MIN(r.y,
                                            circle.center.y - circle.radius);
                                right =
                                    EMB_MAX(right,
                                            circle.center.x + circle.radius);
                                bottom =
                                    EMB_MAX(bottom,
                                            circle.center.y + circle.radius);
                                break;
                        }
                case EMB_ELLIPSE:{
                                /* TODO: account for rotation */
                                EmbEllipse ellipse = g.object.ellipse;
                                r.x =
                                    EMB_MIN(r.x,
                                            ellipse.center.x -
                                            ellipse.radius.x);
                                r.y =
                                    EMB_MIN(r.y,
                                            ellipse.center.y -
                                            ellipse.radius.y);
                                right =
                                    EMB_MAX(right,
                                            ellipse.center.x +
                                            ellipse.radius.x);
                                bottom =
                                    EMB_MAX(bottom,
                                            ellipse.center.y +
                                            ellipse.radius.y);
                                break;
                        }
                case EMB_LINE:{
                                EmbLine line = g.object.line;
                                r.x = EMB_MIN(r.x, line.start.x);
                                r.x = EMB_MIN(r.x, line.end.x);
                                r.y = EMB_MIN(r.y, line.start.y);
                                r.y = EMB_MIN(r.y, line.end.y);
                                right = EMB_MAX(right, line.start.x);
                                right = EMB_MAX(right, line.end.x);
                                bottom = EMB_MAX(bottom, line.start.y);
                                bottom = EMB_MAX(bottom, line.end.y);
                                break;
                        }
                case EMB_POINT:{
                                EmbVector point = g.object.point.position;
                                r.x = EMB_MIN(r.x, point.x);
                                r.y = EMB_MIN(r.y, point.y);
                                right = EMB_MAX(right, point.x);
                                bottom = EMB_MAX(bottom, point.y);
                                break;
                        }
                case EMB_POLYGON:{
                                EmbArray *polygon = g.object.polygon.pointList;
                                for (j = 0; j < polygon->count; j++) {
                                        /* TODO: embp_calcBoundingBox for polygons */
                                }
                                break;
                        }
                case EMB_POLYLINE:{
                                EmbArray *polyline =
                                    g.object.polyline.pointList;
                                for (j = 0; j < polyline->count; j++) {
                                        /* TODO: embp_calcBoundingBox for polylines */
                                }
                                break;
                        }
                case EMB_RECT:{
                                EmbRect rect = g.object.rect;
                                r.x = EMB_MIN(r.x, rect.x);
                                r.y = EMB_MIN(r.y, rect.y);
                                right = EMB_MAX(right, r.x + rect.w);
                                bottom = EMB_MAX(bottom, r.y + rect.h);
                                break;
                        }
                case EMB_SPLINE:{
                                /* EmbBezier bezier;
                                   bezier = p->splines->spline[i].bezier; */
                                /* TODO: embp_calcBoundingBox for splines */
                                break;
                        }
                default:
                        break;
                }
        }

        r.w = right - r.x;
        r.h = bottom - r.y;

        return r;
}

/* Flips the entire pattern (a p) horizontally about the y-axis.
 */
void
 embp_flipHorizontal(EmbPattern * p) {
        if (!p) {
                printf("ERROR: emb-pattern.c embp_flipHorizontal(), ");
                printf("p argument is null\n");
                return;
        }
        embp_flip(p, 1, 0);
}

/* Flips the entire pattern (a p) vertically about the x-axis.
 */
void
 embp_flipVertical(EmbPattern * p) {
        if (!p) {
                printf("ERROR: emb-pattern.c embp_flipVertical(), ");
                printf("p argument is null\n");
                return;
        }
        embp_flip(p, 0, 1);
}

/* Flips the entire pattern (a p) horizontally about the x-axis if (a horz) is true.
 *  Flips the entire pattern (a p) vertically about the y-axis if (a vert) is true.
 */
void
 embp_flip(EmbPattern * p, int horz, int vert) {
        int i, j;

        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_flip(), p argument is null\n");
                return;
        }

        for (i = 0; i < p->stitch_list->count; i++) {
                if (horz) {
                        p->stitch_list->stitch[i].x *= -1.0;
                }
                if (vert) {
                        p->stitch_list->stitch[i].y *= -1.0;
                }
        }

        for (i = 0; i < p->geometry->count; i++) {
                EmbGeometry *g = &(p->geometry->geometry[i]);
                switch (g->type) {
                case EMB_ARC:{
                                if (horz) {
                                        g->object.arc.start.x *= -1.0;
                                        g->object.arc.mid.x *= -1.0;
                                        g->object.arc.end.x *= -1.0;
                                }
                                if (vert) {
                                        g->object.arc.start.y *= -1.0;
                                        g->object.arc.mid.y *= -1.0;
                                        g->object.arc.end.y *= -1.0;
                                }
                                break;
                        }
                case EMB_LINE:{
                                if (horz) {
                                        g->object.line.start.x *= -1.0;
                                        g->object.line.end.x *= -1.0;
                                }
                                if (vert) {
                                        g->object.line.start.y *= -1.0;
                                        g->object.line.end.y *= -1.0;
                                }
                                break;
                        }
                case EMB_CIRCLE:{
                                if (horz) {
                                        g->object.circle.center.x *= -1.0;
                                }
                                if (vert) {
                                        g->object.circle.center.y *= -1.0;
                                }
                                break;
                        }
                case EMB_ELLIPSE:
                        if (horz) {
                                g->object.ellipse.center.x *= -1.0;
                        }
                        if (vert) {
                                g->object.ellipse.center.y *= -1.0;
                        }
                        break;
                case EMB_PATH:{
                                EmbArray *point_list = g->object.path.pointList;
                                for (j = 0; j < point_list->count; j++) {
                                        if (horz) {
                                                point_list->geometry[j].
                                                    object.point.position.x *=
                                                    -1.0;
                                        }
                                        if (vert) {
                                                point_list->geometry[j].
                                                    object.point.position.y *=
                                                    -1.0;
                                        }
                                }
                                break;
                        }
                case EMB_POINT:
                        if (horz) {
                                g->object.point.position.x *= -1.0;
                        }
                        if (vert) {
                                g->object.point.position.y *= -1.0;
                        }
                        break;
                case EMB_POLYGON:{
                                EmbArray *point_list =
                                    g->object.polygon.pointList;
                                for (j = 0; j < point_list->count; j++) {
                                        if (horz) {
                                                point_list->geometry[i].
                                                    object.point.position.x *=
                                                    -1.0;
                                        }
                                        if (vert) {
                                                point_list->geometry[i].
                                                    object.point.position.y *=
                                                    -1.0;
                                        }
                                }
                                break;
                        }
                case EMB_POLYLINE:{
                                EmbArray *point_list =
                                    g->object.polygon.pointList;
                                for (j = 0; j < point_list->count; j++) {
                                        if (horz) {
                                                point_list->geometry[j].
                                                    object.point.position.x *=
                                                    -1.0;
                                        }
                                        if (vert) {
                                                point_list->geometry[j].
                                                    object.point.position.y *=
                                                    -1.0;
                                        }
                                }
                                break;
                        }
                case EMB_RECT:{
                                if (horz) {
                                        g->object.rect.x *= -1.0;
                                        g->object.rect.y *= -1.0;
                                }
                                if (vert) {
                                        g->object.rect.w *= -1.0;
                                        g->object.rect.h *= -1.0;
                                }
                                break;
                        }
                case EMB_SPLINE:
                        /* TODO */
                        break;
                default:
                        break;
                }
        }
}

/* a p
 */
void embp_combineJumpStitches(EmbPattern * p) {
        int jumpCount = 0, i;
        EmbArray *newList;
        EmbStitch j;

        if (!p) {
                printf("ERROR: emb-pattern.c embp_combineJumpStitches(), ");
                printf("p argument is null\n");
                return;
        }
        newList = emb_array_create(EMB_STITCH);
        for (i = 0; i < p->stitch_list->count; i++) {
                EmbStitch st = p->stitch_list->stitch[i];
                if (st.flags & JUMP) {
                        if (jumpCount == 0) {
                                j = st;
                        } else {
                                j.x += st.x;
                                j.y += st.y;
                        }
                        jumpCount++;
                } else {
                        if (jumpCount > 0) {
                                emb_array_addStitch(newList, j);
                        }
                        emb_array_addStitch(newList, st);
                }
        }
        emb_array_free(p->stitch_list);
        p->stitch_list = newList;
}

/* \todo The params determine the max XY movement rather than the length.
 * They need renamed or clarified further.
 */
void embp_correctForMaxStitchLength(EmbPattern * p, EmbReal maxStitchLength,
                                    EmbReal maxJumpLength) {
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_correctForMaxStitchLength(), ");
                printf("p argument is null\n");
                return;
        }
        if (p->stitch_list->count > 1) {
                int i, j, splits;
                EmbReal maxXY, maxLen, addX, addY;
                EmbArray *newList = emb_array_create(EMB_STITCH);
                for (i = 1; i < p->stitch_list->count; i++) {
                        EmbStitch st = p->stitch_list->stitch[i];
                        EmbReal xx = st.x;
                        EmbReal yy = st.y;
                        EmbReal dx = p->stitch_list->stitch[i - 1].x - xx;
                        EmbReal dy = p->stitch_list->stitch[i - 1].y - yy;
                        if ((fabs(dx) > maxStitchLength)
                            || (fabs(dy) > maxStitchLength)) {
                                maxXY = EMB_MAX(fabs(dx), fabs(dy));
                                if (st.flags & (JUMP | TRIM)) {
                                        maxLen = maxJumpLength;
                                } else {
                                        maxLen = maxStitchLength;
                                }
                                splits = (int)ceil((EmbReal) maxXY / maxLen);

                                if (splits > 1) {
                                        addX = (EmbReal) dx / splits;
                                        addY = (EmbReal) dy / splits;

                                        for (j = 1; j < splits; j++) {
                                                EmbStitch s;
                                                s = st;
                                                s.x = xx + addX * j;
                                                s.y = yy + addY * j;
                                                emb_array_addStitch(newList, s);
                                        }
                                }
                        }
                        emb_array_addStitch(newList, st);
                }
                emb_array_free(p->stitch_list);
                p->stitch_list = newList;
        }
        embp_end(p);
}

/* Center the pattern a p.
 */
void embp_center(EmbPattern * p) {
        /* TODO: review this. currently not used in anywhere.
           Also needs to handle various design objects */
        int moveLeft, moveTop, i;
        EmbRect boundingRect;
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_center(), p argument is null\n");
                return;
        }
        boundingRect = embp_bounds(p);

        moveLeft = (int)(boundingRect.x - boundingRect.w / 2.0);
        moveTop = (int)(boundingRect.y - boundingRect.h / 2.0);

        for (i = 0; i < p->stitch_list->count; i++) {
                p->stitch_list->stitch[i].x -= moveLeft;
                p->stitch_list->stitch[i].y -= moveTop;
        }
}

/* TODO: Description needed.
 */
void
 embp_loadExternalColorFile(EmbPattern * p, const char *fileName) {
        int hasRead, stub_len, format;
        char extractName[200];

        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_loadExternalColorFile(), p argument is null\n");
                return;
        }
        if (!fileName) {
                printf
                    ("ERROR: emb-pattern.c embp_loadExternalColorFile(), fileName argument is null\n");
                return;
        }

        strcpy(extractName, fileName);
        format = emb_identify_format(fileName);
        stub_len =
            embstr_len(fileName) - embstr_len(formatTable[format].extension);
        extractName[stub_len] = 0;
        strcat(extractName, ".edr");
        hasRead = embp_read(p, extractName, EMB_FORMAT_EDR);
        if (!hasRead) {
                extractName[stub_len] = 0;
                strcat(extractName, ".rgb");
                hasRead = embp_read(p, extractName, EMB_FORMAT_RGB);
        }
        if (!hasRead) {
                extractName[stub_len] = 0;
                strcat(extractName, ".col");
                hasRead = embp_read(p, extractName, EMB_FORMAT_COL);
        }
        if (!hasRead) {
                extractName[stub_len] = 0;
                strcat(extractName, ".inf");
                hasRead = embp_read(p, extractName, EMB_FORMAT_INF);
        }
}

/* Frees all memory allocated in the pattern (a p).
 */
void
 embp_free(EmbPattern * p) {
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_free(), p argument is null\n");
                return;
        }
        emb_array_free(p->stitch_list);
        emb_array_free(p->thread_list);
        emb_array_free(p->geometry);
        safe_free(p);
}

/*
 */
void
 emb_add_geometry(EmbPattern * p, EmbGeometry g) {
        emb_array_add_geometry(p->geometry, g);
}

/* Adds a circle object to pattern (a p) with its center at the absolute
 * position (a cx,a cy) with a radius of (a r). Positive y is up.
 * Units are in millimeters.
 */
void
 emb_add_circle(EmbPattern * p, EmbCircle circle) {
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c emb_add_circle(), p argument is null\n");
                return;
        }

        EmbGeometry g;
        g.object.circle = circle;
        g.type = EMB_CIRCLE;
        emb_array_add_geometry(p->geometry, g);
}

/* Adds an ellipse object to pattern (a p) with its center at the
 * absolute position (a cx,a cy) with radii of (a rx,a ry). Positive y is up.
 * Units are in millimeters.
 */
void
 emb_add_ellipse(EmbPattern * p, EmbEllipse ellipse) {
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_addEllipseObjectAbs(), p argument is null\n");
                return;
        }

        emb_array_add_ellipse(p->geometry, ellipse);
}

/* Adds a line object to pattern (a p) starting at the absolute position
 * (a x1,a y1) and ending at the absolute position (a x2,a y2).
 * Positive y is up. Units are in millimeters.
 */
void
 emb_add_line(EmbPattern * p, EmbLine line) {
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_addLineObjectAbs(), p argument is null\n");
                return;
        }

        emb_array_addLine(p->geometry, line);
}

/* .
 */
void
 emb_add_path(EmbPattern * p, EmbPath obj) {
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_addPathObjectAbs(), p argument is null\n");
                return;
        }
        if (!obj.pointList) {
                printf
                    ("ERROR: emb-pattern.c embp_addPathObjectAbs(), obj->pointList is empty\n");
                return;
        }

        emb_array_addPath(p->geometry, obj);
}

/*! Adds a point object to pattern (a p) at the absolute position (a x,a y). Positive y is up. Units are in millimeters. */
void
 embp_addPointAbs(EmbPattern * p, EmbPoint obj) {
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_addPointObjectAbs(), p argument is null\n");
                return;
        }

        emb_array_addPoint(p->geometry, obj);
}

void
 embp_addPolygonAbs(EmbPattern * p, EmbPolygon obj) {
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_addPolygonObjectAbs(), p argument is null\n");
                return;
        }
        if (!obj.pointList) {
                printf
                    ("ERROR: emb-pattern.c embp_addPolygonObjectAbs(), obj->pointList is empty\n");
                return;
        }

        emb_array_addPolygon(p->geometry, obj);
}

void
 embp_addPolylineObjectAbs(EmbPattern * p, EmbPolyline obj) {
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_addPolylineObjectAbs(), p argument is null\n");
                return;
        }
        if (!obj.pointList) {
                printf
                    ("ERROR: emb-pattern.c embp_addPolylineObjectAbs(), obj->pointList is empty\n");
                return;
        }
        emb_array_addPolyline(p->geometry, obj);
}

/* Adds a rectangle object to pattern (a p) at the absolute position
 * (a x,a y) with a width of (a w) and a height of (a h).
 * Positive y is up. Units are in millimeters.
 */
void
 embp_addRectAbs(EmbPattern * p, EmbRect rect) {
        if (!p) {
                printf
                    ("ERROR: emb-pattern.c embp_addRectObjectAbs(), p argument is null\n");
                return;
        }
        emb_array_addRect(p->geometry, rect);
}

/* . */
void
 embp_end(EmbPattern * p) {
        if (p->stitch_list->count == 0) {
                return;
        }
        /* Check for an END stitch and add one if it is not present */
        if (p->stitch_list->stitch[p->stitch_list->count - 1].flags != END) {
                embp_addStitchRel(p, 0, 0, END, 1);
        }
}

/*
 *
 */
int convert(const char *inf, const char *outf) {
        EmbPattern *p = 0;
        int reader, writer;

        reader = emb_identify_format(inf);
        writer = emb_identify_format(outf);

        p = embp_create();
        if (!p) {
                printf("ERROR: convert(), cannot allocate memory for p\n");
                return 1;
        }

        if (!embp_read(p, inf, reader)) {
                printf("ERROR: convert(), reading file was unsuccessful: %s\n",
                       inf);
                embp_free(p);
                return 1;
        }

        if (formatTable[reader].type == EMBFORMAT_OBJECTONLY) {
                if (formatTable[writer].type == EMBFORMAT_STITCHONLY) {
                        embp_movePolylinesTostitch_list(p);
                }
        }

        if (!embp_write(p, outf, writer)) {
                printf("ERROR: convert(), writing file %s was unsuccessful\n",
                       outf);
                embp_free(p);
                return 1;
        }

        embp_free(p);
        return 0;
}

/* The Thread Management System
 * -----------------------------------------------------------------------------
 */
int threadColor(const char *name, int brand) {
        int i;
        for (i = 0; brand_codes[brand].codes[i].manufacturer_code >= 0; i++) {
                if (!strcmp(brand_codes[brand].codes[i].name, name)) {
                        return brand_codes[brand].codes[i].hex_code;
                }
        }
        return -1;
}

int threadColorNum(unsigned int color, int brand) {
        int i;
        for (i = 0; brand_codes[brand].codes[i].manufacturer_code >= 0; i++) {
                if (brand_codes[brand].codes[i].hex_code == color) {
                        return brand_codes[brand].codes[i].manufacturer_code;
                }
        }

        return -1;
}

const char *threadColorName(unsigned int color, int brand) {
        int i;
        for (i = 0; brand_codes[brand].codes[i].manufacturer_code >= 0; i++) {
                if (brand_codes[brand].codes[i].hex_code == color) {
                        return brand_codes[brand].codes[i].name;
                }
        }

        return "COLOR NOT FOUND";
}

/* . */
EmbVector scale_and_rotate(EmbVector v, double scale, double angle) {
        EmbVector w;
        double rot = radians(angle);
        double cosRot = cos(rot);
        double sinRot = sin(rot);
        w.x = v.x * scale;
        w.y = v.y * scale;
        w.x = w.x * cosRot - w.y * sinRot;
        w.y = w.x * sinRot + w.y * cosRot;
        return w;
}
