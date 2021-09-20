static int read100(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[4];
    EmbStitch st;

    embPattern_loadExternalColorFile(pattern, fileName);
    while (embFile_read(b, 1, 4, file) == 4) {
        /* What does byte b[1] do? Is it the color index? */
        st.flags = NORMAL;
        st.x = (b[2] > 0x80) ? -(b[2] - 0x80) : b[2];
        st.y = (b[3] > 0x80) ? -(b[3] - 0x80) : b[3];
        /*if(!(b[0] & 0xFC)) st.flags = JUMP; TODO: review & fix */
        if (!(b[0] & 0x01))
            st.flags = STOP;
        if (b[0] == 0x1F)
            st.flags = END;
        st.color = 1;
        st.x /= 10.0;
        st.y /= 10.0;
        embPattern_addStitchRel(pattern, st.x, st.y, st.flags, st.color);
    }

    return 1;
}

static int write100(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish write100 */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int read10o(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[3];
    /* file = embFile_open(fileName, "rb", 0); */

    embPattern_loadExternalColorFile(pattern, fileName);

    while (embFile_read(b, 1, 3, file) == 3) {
        EmbStitch st;
        st.flags = NORMAL;
        st.y = b[1] / 10.0;
        st.x = b[2] / 10.0;
        if (b[0] & 0x20)
            st.x *= 1.0;
        if (b[0] & 0x40)
            st.y *= 1.0;
        if (b[0] & 0x01)
            st.flags = TRIM;
        if ((b[0] & 0x5) == 5) {
            st.flags = STOP;
        }
        if (b[0] == 0xF8 || b[0] == 0x91 || b[0] == 0x87) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, st.x, st.y, st.flags, 1);
    }

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int write10o(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish write10o */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readArt(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    embPattern_end(pattern);

    return 0; /*TODO: finish readArt */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeArt(EmbPattern* pattern, EmbFile* file, const char* fileName)
{

    return 0; /*TODO: finish writeArt */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readBmc(EmbPattern* pattern, EmbFile* file, const char* fileName)
{

    return 0; /*TODO: finish readBmc */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeBmc(EmbPattern* pattern, EmbFile* file, const char* fileName)
{

    return 0; /*TODO: finish writeBmc */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readBro(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char x55;
    short unknown1, unknown2, unknown3, unknown4, moreBytesToEnd;
    char name[8];
    int stitchType;

    embPattern_loadExternalColorFile(pattern, fileName);

    x55 = binaryReadByte(file);
    unknown1 = binaryReadInt16(file); /* TODO: determine what this unknown data is */

    embFile_read(name, 1, 8, file);
    unknown2 = binaryReadInt16(file); /* TODO: determine what this unknown data is */
    unknown3 = binaryReadInt16(file); /* TODO: determine what this unknown data is */
    unknown4 = binaryReadInt16(file); /* TODO: determine what this unknown data is */
    moreBytesToEnd = binaryReadInt16(file);

    embFile_seek(file, 0x100, SEEK_SET);

    while (1) {
        short b1, b2;
        stitchType = NORMAL;
        b1 = binaryReadByte(file);
        b2 = binaryReadByte(file);
        if (b1 == -128) {
            unsigned char bCode = binaryReadByte(file);
            b1 = binaryReadInt16(file);
            b2 = binaryReadInt16(file);
            if (bCode == 2) {
                stitchType = STOP;
            } else if (bCode == 3) {
                stitchType = TRIM;
            } else if (bCode == 0x7E) {
                break;
            }
        }
        embPattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeBro(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeBro */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readCnd(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish readCnd */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeCnd(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeCnd */
}

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

#define CsdSubMaskSize 479
#define CsdXorMaskSize 501

static char _subMask[CsdSubMaskSize];
static char _xorMask[CsdXorMaskSize];

static void BuildDecryptionTable(int seed)
{
    int i;
    const int mul1 = 0x41C64E6D;
    const int add1 = 0x3039;

    for (i = 0; i < CsdSubMaskSize; i++) {
        seed *= mul1;
        seed += add1;
        _subMask[i] = (char)((seed >> 16) & 0xFF);
    }
    for (i = 0; i < CsdXorMaskSize; i++) {
        seed *= mul1;
        seed += add1;
        _xorMask[i] = (char)((seed >> 16) & 0xFF);
    }
}

static unsigned char DecodeCsdByte(long fileOffset, unsigned char val, int type)
{
    static const unsigned char _decryptArray[] = {
        0x43, 0x6E, 0x72, 0x7A, 0x76, 0x6C, 0x61, 0x6F, 0x7C, 0x29, 0x5D, 0x62, 0x60, 0x6E, 0x61, 0x62, 0x20, 0x41, 0x66, 0x6A, 0x3A, 0x35, 0x5A, 0x63, 0x7C, 0x37, 0x3A, 0x2A, 0x25, 0x24, 0x2A, 0x33, 0x00, 0x10, 0x14, 0x03, 0x72, 0x4C, 0x48, 0x42, 0x08, 0x7A, 0x5E, 0x0B, 0x6F, 0x45, 0x47, 0x5F, 0x40, 0x54, 0x5C, 0x57, 0x55, 0x59, 0x53, 0x3A, 0x32, 0x6F, 0x53, 0x54, 0x50, 0x5C, 0x4A, 0x56, 0x2F, 0x2F, 0x62, 0x2C, 0x22, 0x65, 0x25, 0x28, 0x38, 0x30, 0x38, 0x22, 0x2B, 0x25, 0x3A, 0x6F, 0x27, 0x38, 0x3E, 0x3F, 0x74, 0x37, 0x33, 0x77, 0x2E, 0x30, 0x3D, 0x34, 0x2E, 0x32, 0x2B, 0x2C, 0x0C, 0x18, 0x42, 0x13, 0x16, 0x0A, 0x15, 0x02, 0x0B, 0x1C, 0x1E, 0x0E, 0x08, 0x60, 0x64, 0x0D, 0x09, 0x51, 0x25, 0x1A, 0x18, 0x16, 0x19, 0x1A, 0x58, 0x10, 0x14, 0x5B, 0x08, 0x15, 0x1B, 0x5F, 0xD5, 0xD2, 0xAE, 0xA3, 0xC1, 0xF0, 0xF4, 0xE8, 0xF8, 0xEC, 0xA6, 0xAB, 0xCD, 0xF8, 0xFD, 0xFB, 0xE2, 0xF0, 0xFE, 0xFA, 0xF5, 0xB5, 0xF7, 0xF9, 0xFC, 0xB9, 0xF5, 0xEF, 0xF4, 0xF8, 0xEC, 0xBF, 0xC3, 0xCE, 0xD7, 0xCD, 0xD0, 0xD7, 0xCF, 0xC2, 0xDB, 0xA4, 0xA0, 0xB0, 0xAF, 0xBE, 0x98, 0xE2, 0xC2, 0x91, 0xE5, 0xDC, 0xDA, 0xD2, 0x96, 0xC4, 0x98, 0xF8, 0xC9, 0xD2, 0xDD, 0xD3, 0x9E, 0xDE, 0xAE, 0xA5, 0xE2, 0x8C, 0xB6, 0xAC, 0xA3, 0xA9, 0xBC, 0xA8, 0xA6, 0xEB, 0x8B, 0xBF, 0xA1, 0xAC, 0xB5, 0xA3, 0xBB, 0xB6, 0xA7, 0xD8, 0xDC, 0x9A, 0xAA, 0xF9, 0x82, 0xFB, 0x9D, 0xB9, 0xAB, 0xB3, 0x94, 0xC1, 0xA0, 0x8C, 0x8B, 0x8E, 0x95, 0x8F, 0x87, 0x99, 0xE7, 0xE1, 0xA3, 0x83, 0x8B, 0xCF, 0xA3, 0x85, 0x9D, 0x83, 0xD4, 0xB7, 0x83, 0x84, 0x91, 0x97, 0x9F, 0x88, 0x8F, 0xDD, 0xAD, 0x90
    };
    int newOffset;

    fileOffset = fileOffset - 1;
    if (type != 0) {
        int final;
        int fileOffsetHigh = (int)(fileOffset & 0xFFFFFF00);
        int fileOffsetLow = (int)(fileOffset & 0xFF);

        newOffset = fileOffsetLow;
        fileOffsetLow = fileOffsetHigh;
        final = fileOffsetLow % 0x300;
        if (final != 0x100 && final != 0x200) {
            newOffset = _decryptArray[newOffset] | fileOffsetHigh;
        } else if (final != 0x100 && final == 0x200) {
            if (newOffset == 0) {
                fileOffsetHigh = fileOffsetHigh - 0x100;
            }
            newOffset = _decryptArray[newOffset] | fileOffsetHigh;
        } else if (newOffset != 1 && newOffset != 0) {
            newOffset = _decryptArray[newOffset] | fileOffsetHigh;
        } else {
            fileOffsetHigh = fileOffsetHigh - 0x100;
            newOffset = _decryptArray[newOffset] | fileOffsetHigh;
        }
    } else {
        newOffset = (int)fileOffset;
    }
    return ((unsigned char)((unsigned char)(val ^ _xorMask[newOffset % CsdXorMaskSize]) - _subMask[newOffset % CsdSubMaskSize]));
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readCsd(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i, type = 0;
    unsigned char identifier[8];
    unsigned char unknown1, unknown2;
    char dx = 0, dy = 0;
    int colorChange = -1;
    int flags;
    char endOfStream = 0;
    unsigned char colorOrder[14];

    binaryReadBytes(file, identifier, 8); /* TODO: check return value */

    if (identifier[0] != 0x7C && identifier[2] != 0xC3) {
        type = 1;
    }
    if (type == 0) {
        BuildDecryptionTable(0xC);
    } else {
        BuildDecryptionTable(identifier[0]);
    }
    embFile_seek(file, 8, SEEK_SET);
    for (i = 0; i < 16; i++) {
        EmbThread thread;
        thread.color.r = DecodeCsdByte(embFile_tell(file), binaryReadByte(file), type);
        thread.color.g = DecodeCsdByte(embFile_tell(file), binaryReadByte(file), type);
        thread.color.b = DecodeCsdByte(embFile_tell(file), binaryReadByte(file), type);
        thread.catalogNumber = "";
        thread.description = "";
        embPattern_addThread(pattern, thread);
    }
    unknown1 = DecodeCsdByte(embFile_tell(file), binaryReadByte(file), type);
    unknown2 = DecodeCsdByte(embFile_tell(file), binaryReadByte(file), type);

    for (i = 0; i < 14; i++) {
        colorOrder[i] = (unsigned char)DecodeCsdByte(embFile_tell(file), binaryReadByte(file), type);
    }
    for (i = 0; !endOfStream; i++) {
        char negativeX, negativeY;
        unsigned char b0 = DecodeCsdByte(embFile_tell(file), binaryReadByte(file), type);
        unsigned char b1 = DecodeCsdByte(embFile_tell(file), binaryReadByte(file), type);
        unsigned char b2 = DecodeCsdByte(embFile_tell(file), binaryReadByte(file), type);

        if (b0 == 0xF8 || b0 == 0x87 || b0 == 0x91) {
            break;
        }
        negativeX = ((b0 & 0x20) > 0);
        negativeY = ((b0 & 0x40) > 0);
        b0 = (unsigned char)(b0 & (0xFF ^ 0xE0));

        if ((b0 & 0x1F) == 0)
            flags = NORMAL;
        else if ((b0 & 0x0C) > 0) {
            flags = STOP;
            if (colorChange >= 14) {
                printf("Invalid color change detected\n");
            }
            embPattern_changeColor(pattern, colorOrder[colorChange % 14]);
            colorChange += 1;
        } else if ((b0 & 0x1F) > 0)
            flags = TRIM;
        else
            flags = NORMAL;
        dx = (char)b2;
        dy = (char)b1;
        if (negativeX)
            dx = (char)-dx;
        if (negativeY)
            dy = (char)-dy;
        if (flags == STOP)
            embPattern_addStitchRel(pattern, 0, 0, flags, 1);
        else
            embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    embPattern_end(pattern);
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeCsd(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeCsd */
}

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
static int readCsv(EmbPattern* pattern, EmbFile* file, const char* fileName)
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
static int writeCsv(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readDat(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b0;
    int fileLength, stitchesRemaining, b1, b2, stitchType;

    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_seek(file, 0x00, SEEK_END);
    fileLength = embFile_tell(file);
    embFile_seek(file, 0x02, SEEK_SET);
    stitchesRemaining = binaryReadUInt16(file);
    embFile_seek(file, 0x100, SEEK_SET);

    while (embFile_tell(file) < fileLength) {
        b1 = (int)binaryReadUInt8(file);
        b2 = (int)binaryReadUInt8(file);
        b0 = binaryReadByte(file);

        stitchType = NORMAL;
        stitchesRemaining--;

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
        embPattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeDat(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeDat */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readDem(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish readDem */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeDem(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeDem */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readDsb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char header[512];
    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_read(header, 1, 512, file);

    embFile_seek(file, 0x200, SEEK_SET);
    while (1) {
        int x, y;
        unsigned char ctrl;
        int stitchType = NORMAL;

        ctrl = (unsigned char)embFile_getc(file);
        if (embFile_eof(file))
            break;
        y = embFile_getc(file);
        if (embFile_eof(file))
            break;
        x = embFile_getc(file);
        if (embFile_eof(file))
            break;
        if (ctrl & 0x01)
            stitchType = TRIM;
        if (ctrl & 0x20)
            x = -x;
        if (ctrl & 0x40)
            y = -y;
        /* ctrl & 0x02 - Speed change? */ /* TODO: review this line */
        /* ctrl & 0x04 - Clutch? */ /* TODO: review this line */
        if ((ctrl & 0x05) == 0x05) {
            stitchType = STOP;
        }
        if (ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87) {
            embPattern_end(pattern);
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeDsb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeDsb */
}

/* .DST (Tajima) embroidery file read/write routines
 * Format comments are thanks to tspilman@dalcoathletic.com who's
 * notes appeared at http://www.wotsit.org under Tajima Format.
 */

/* TODO: review this then remove since emb-pattern.c has a similar function */
/* void combineJumpStitches(EmbPattern* p, int jumpsPerTrim)
{
    if(!p) { embLog("ERROR: format-dst.c combineJumpStitches(), p argument is null\n"); return; }
    EmbStitchList* pointer = p->stitchList;
    int jumpCount = 0;
    EmbStitchList* jumpListStart = 0;
    char needleDown = 0;
    while(pointer)
    {
        if((pointer->stitch.flags & JUMP) && !(pointer->stitch.flags & STOP))
        {
            if(jumpCount == 0)
            {
                jumpListStart = pointer;
            }
            jumpCount++;
            if(needleDown && jumpCount >= jumpsPerTrim)
            {
                EmbStitchList* removePointer = jumpListStart->next;
                jumpListStart->stitch.x = pointer->stitch.x;
                jumpListStart->stitch.y = pointer->stitch.y;
                jumpListStart->stitch.flags |= TRIM;
                jumpListStart->next = pointer;

                jumpCount-=2;
                for(; jumpCount > 0; jumpCount--)
                {
                    EmbStitchList* tempPointer = removePointer->next;
                    jumpListStart->stitch.flags |= removePointer->stitch.flags;
                    free(removePointer);
                    removePointer = 0;
                    removePointer = tempPointer;
                }
                jumpCount = 0;
                needleDown = 0;
            }
        }
        else
        {
            if(pointer->stitch.flags == NORMAL)
            {
                needleDown = 1;
                jumpCount = 0;
            }
        }
        pointer = pointer->next;
    }
}
*/

static void encode_record(EmbFile* file, int x, int y, int flags)
{
    char b[4];
    b[0] = b[1] = b[2] = 0;

    /* cannot encode values > +121 or < -121. */
    if (x > 121 || x < -121)
        embLog("ERROR: format-dst.c encode_record(), x is not in valid range [-121,121] , x =\n"); /* , x); */
    if (y > 121 || y < -121)
        embLog("ERROR: format-dst.c encode_record(), y is not in valid range [-121,121] , y = \n"); /* , y); */

    if (x >= +41) {
        SETBIT(b[2], 2);
        x -= 81;
    }
    if (x <= -41) {
        SETBIT(b[2], 3);
        x += 81;
    }
    if (x >= +14) {
        SETBIT(b[1], 2);
        x -= 27;
    }
    if (x <= -14) {
        SETBIT(b[1], 3);
        x += 27;
    }
    if (x >= +5) {
        SETBIT(b[0], 2);
        x -= 9;
    }
    if (x <= -5) {
        b[0] += 1 << 3;
        x += 9;
    }
    if (x >= +2) {
        b[1] += 1 << 0;
        x -= 3;
    }
    if (x <= -2) {
        b[1] += 1 << 1;
        x += 3;
    }
    if (x >= +1) {
        b[0] += 1 << 0;
        x -= 1;
    }
    if (x <= -1) {
        b[0] += 1 << 1;
        x += 1;
    }
    if (x != 0) {
        embLog("ERROR: format-dst.c encode_record(), x should be zero yet x = \n"); /*, x); */
    }
    if (y >= +41) {
        b[2] += 1 << 5;
        y -= 81;
    }
    if (y <= -41) {
        b[2] += 1 << 4;
        y += 81;
    }
    if (y >= +14) {
        b[1] += 1 << 5;
        y -= 27;
    }
    if (y <= -14) {
        b[1] += 1 << 4;
        y += 27;
    }
    if (y >= +5) {
        b[0] += 1 << 5;
        y -= 9;
    }
    if (y <= -5) {
        b[0] += 1 << 4;
        y += 9;
    }
    if (y >= +2) {
        b[1] += 1 << 7;
        y -= 3;
    }
    if (y <= -2) {
        b[1] += 1 << 6;
        y += 3;
    }
    if (y >= +1) {
        b[0] += 1 << 7;
        y -= 1;
    }
    if (y <= -1) {
        b[0] += 1 << 6;
        y += 1;
    }
    if (y != 0) {
        embLog("ERROR: format-dst.c encode_record(), y should be zero yet y = \n"); /* , y); */
    }

    b[2] |= (char)3;

    if (flags & END) {
        b[2] = (char)-13;
        b[0] = b[1] = (char)0;
    }

    /* if(flags & TRIM)
    {
        int v = 5;
        int dx = (int)(x/v), dy = (int)(y/v);
        for(i = 1; i < v; i++)
        {
            encode_record(file, dx, dy, JUMP);
        }
        encode_record(file, x - (dx * (v - 1)), y - (dy * (v - 1)), JUMP);
        return;
    } */
    if (flags & (JUMP | TRIM)) {
        b[2] = (char)(b[2] | 0x83);
    }
    if (flags & STOP) {
        b[2] = (char)(b[2] | 0xC3);
    }

    embFile_write(b, 1, 3, file);
}

/*convert 2 characters into 1 int for case statement */
/*#define cci(s) (s[0]*256+s[1]) */
#define cci(c1, c2) (c1 * 256 + c2)

static void set_dst_variable(EmbPattern* pattern, char* var, char* val)
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
    case cci('L', 'A'): /* Design Name (LA) */
        /*pattern->set_variable("Design_Name",val); TODO: review this line. */
        break;
    case cci('S', 'T'): /* Stitch count, 7 digits padded by leading 0's */
    case cci('C', 'O'): /* Color change count, 3 digits padded by leading 0's */
    case cci('+', 'X'): /* Design extents (+/-X,+/-Y), 5 digits padded by leading 0's */
    case cci('-', 'X'):
    case cci('+', 'Y'):
    case cci('-', 'Y'):
        /* don't store these variables, they are recalculated at save */
        break;
    case cci('A', 'X'): /* Relative coordinates of last point, 6 digits, padded with leading spaces, first char may be +/- */
    case cci('A', 'Y'):
    case cci('M', 'X'): /* Coordinates of last point in previous file of multi-volume design, 6 digits, padded with leading spaces, first char may be +/- */
    case cci('M', 'Y'):
        /* store these variables as-is, they will be converted to numbers and back at save; */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    case cci('P', 'D'):
        /* store this string as-is, it will be saved as-is, 6 characters */
        if (strlen(val) != 6) {
            /*pattern->messages.add("Warning: in DST file read, PD is not 6 characters, but ",(int)strlen(val)); */
        }
        /*pattern->set_variable(var,val);*/
        break;
        /* Begin extended fields section */
    case cci('A', 'U'): /* Author string, arbitrary length */
    case cci('C', 'P'): /* Copyright string, arbitrary length */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    case cci('T', 'C'): /*Thread Color: #RRGGBB,Description,Catalog Number (1st field RGB hex values, 2nd&3rd fields optional arbitrary length) */
        /* TODO: review these lines below.
        description=split_cell_str(val,2);
        catalog_number=split_cell_str(val,3);
        */
        t.color = embColor_fromHexStr(val);
        t.description = "";
        t.catalogNumber = "";
        embPattern_addThread(pattern, t);
        break;
    default:
        /* unknown field, just save it. */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readDst(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char var[3]; /* temporary storage variable name */
    char val[512]; /* temporary storage variable value */
    int valpos;
    unsigned char b[3];
    char header[512 + 1];
    int i = 0;
    int flags; /* for converting stitches from file encoding */

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

    /* TODO: review commented code below
    pattern->clear();
    pattern->set_variable("file_name",filename);
    */

    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_read(header, 1, 512, file);

    /*TODO:It would probably be a good idea to validate file before accepting it. */

    /* fill variables from header fields */
    for (i = 0; i < 512; i++) {
        if (header[i] == ':' && i > 1) {
            var[0] = header[i - 2];
            var[1] = header[i - 1];
            var[2] = '\0';
            valpos = i + 1;
            for (i++; i < 512; i++) {
                /* don't accept : without CR because there's a bug below: i-valpos must be > 0 which is not the case if the : is before the third character. */
                if (header[i] == 13 /*||header[i]==':'*/) /* 0x0d = carriage return */
                {
                    if (header[i] == ':') /* : indicates another variable, CR was missing! */
                    {
                        i -= 2;
                    }
                    strncpy(val, &header[valpos], (size_t)(i - valpos));
                    val[i - valpos] = '\0';
                    set_dst_variable(pattern, var, val);
                    break;
                }
            }
        }
    }

    while (embFile_read(b, 1, 3, file) == 3) {
        int x;
        int y;
        /* A version of the stitch decoding with less branching,
         * the BIT macro returns either 0 or 1 based on the value
         * of that bit and then is multiplied by what value that represents.
         */
        if (b[2] == 0xF3) {
            break;
        }
        x  =     BIT(b[0], 1) - BIT(b[0], 2);
        x +=  9*(BIT(b[0], 3) - BIT(b[0], 4));
        y  =     BIT(b[0], 8) - BIT(b[0], 7);
        y +=  9*(BIT(b[0], 6) - BIT(b[0], 5));
        x +=  3*(BIT(b[1], 1) - BIT(b[1], 2));
        x += 27*(BIT(b[1], 3) - BIT(b[1], 4));
        y +=  3*(BIT(b[1], 8) - BIT(b[1], 7));
        y += 27*(BIT(b[1], 6) - BIT(b[1], 5));
        x += 81*(BIT(b[2], 3) - BIT(b[2], 4));
        y += 81*(BIT(b[2], 6) - BIT(b[2], 5));

        flags = (BIT(b[2], 8) * JUMP) | (BIT(b[2], 7) * STOP);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
    }

    /* combineJumpStitches(pattern, 5); */
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeDst(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbRect boundingRect;
    int xx, yy, dx, dy, flags, i, ax, ay, mx, my;
    char* pd = 0;
    EmbStitch st;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    /* TODO: make sure that pattern->threads->count defaults to 1 in new patterns */
    flags = NORMAL;
    boundingRect = embPattern_calcBoundingBox(pattern);
    /* TODO: review the code below
    if(pattern->get_variable("design_name") != NULL)
    {
    char *la = stralloccopy(pattern->get_variable("design_name"));
    if(strlen(la)>16) la[16]='\0';

    embFile_print(file,"LA:%-16s\x0d",la);
    free(la);
    }
    else
    {
    */
    /* pad to 16 char */
    embFile_print(file, "LA:Untitled        \x0d");
    /*} */
    /* TODO: check that the number of characters adds to 125, or pad
    correctly. */
    embFile_print(file, "ST:");
    writeInt(file, pattern->stitchList->count, 6);
    embFile_print(file, "\x0dCO:");
    writeInt(file, pattern->threads->count - 1, 6); /* number of color changes, not number of colors! */
    embFile_print(file, "\x0d+X:");
    writeInt(file, (int)(boundingRect.right * 10.0), 6);
    embFile_print(file, "\x0d-X:");
    writeInt(file, (int)(fabs(boundingRect.left) * 10.0), 6);
    embFile_print(file, "\x0d+Y:");
    writeInt(file, (int)(boundingRect.bottom * 10.0), 6);
    embFile_print(file, "\x0d-Y:");
    writeInt(file, (int)(fabs(boundingRect.top) * 10.0), 6);
    embFile_print(file, "\x0d");

    ax = ay = mx = my = 0;
    /* TODO: review the code below */
    /*ax=pattern->get_variable_int("ax"); */ /* will return 0 if not defined */
    /*ay=pattern->get_variable_int("ay"); */
    /*mx=pattern->get_variable_int("mx"); */
    /*my=pattern->get_variable_int("my"); */

    /*pd=pattern->get_variable("pd");*/ /* will return null pointer if not defined */
    pd = 0;
    if (pd == 0 || strlen(pd) != 6) {
        /* pd is not valid, so fill in a default consisting of "******" */
        pd = "******";
    }
    embFile_print(file, "AX:+");
    writeInt(file, ax, 6);
    embFile_print(file, "\x0dAY:+");
    writeInt(file, ay, 6);
    embFile_print(file, "\x0dMX:+");
    writeInt(file, mx, 6);
    embFile_print(file, "\x0dMY:+");
    writeInt(file, my, 6);
    embFile_print(file, "\x0dPD:");
    embFile_print(file, pd); /* 6 char, swap for embFile_write */
    embFile_print(file, "\x0d\x1a"); /* 0x1a is the code for end of section. */

    embFile_pad(file, ' ', 512-125);

    /* write stitches */
    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = roundDouble(st.x * 10.0) - xx;
        dy = roundDouble(st.y * 10.0) - yy;
        xx = roundDouble(st.x * 10.0);
        yy = roundDouble(st.y * 10.0);
        encode_record(file, dx, dy, st.flags);
    }
    /* finish file with a terminator character */
    embFile_write("\xA1\0\0", 1, 3, file);
    return 1;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readDsz(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    embPattern_loadExternalColorFile(pattern, fileName);

    embFile_seek(file, 0x200, SEEK_SET);
    while (1) {
        int x, y;
        unsigned char ctrl;
        int stitchType = NORMAL;

        y = embFile_getc(file);
        if (embFile_eof(file))
            break;
        x = embFile_getc(file);
        if (embFile_eof(file))
            break;
        ctrl = (unsigned char)embFile_getc(file);
        if (embFile_eof(file))
            break;
        if (ctrl & 0x01)
            stitchType = TRIM;
        if (ctrl & 0x20)
            y = -y;
        if (ctrl & 0x40)
            x = -x;

        if (ctrl & 0x0E) {
            int headNumber = (ctrl & 0x0E) >> 1;
            stitchType = STOP;
        }
        if (ctrl & 0x10) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeDsz(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeDsz */
}

/* DXF Version Identifiers */
#define DXF_VERSION_R10 "AC1006"
#define DXF_VERSION_R11 "AC1009"
#define DXF_VERSION_R12 "AC1009"
#define DXF_VERSION_R13 "AC1012"
#define DXF_VERSION_R14 "AC1014"
#define DXF_VERSION_R15 "AC1015"
#define DXF_VERSION_R18 "AC1018"
#define DXF_VERSION_R21 "AC1021"
#define DXF_VERSION_R24 "AC1024"
#define DXF_VERSION_R27 "AC1027"

#define DXF_VERSION_2000 "AC1015"
#define DXF_VERSION_2002 "AC1015"
#define DXF_VERSION_2004 "AC1018"
#define DXF_VERSION_2006 "AC1018"
#define DXF_VERSION_2007 "AC1021"
#define DXF_VERSION_2009 "AC1021"
#define DXF_VERSION_2010 "AC1024"
#define DXF_VERSION_2013 "AC1027"

/* Based on the DraftSight color table */
static const unsigned char _dxfColorTable[][3] = {
    { 0, 0, 0 }, /*   '0' (BYBLOCK)    */
    { 255, 0, 0 }, /*   '1' (red)        */
    { 255, 255, 0 }, /*   '2' (yellow)     */
    { 0, 255, 0 }, /*   '3' (green)      */
    { 0, 255, 255 }, /*   '4' (cyan)       */
    { 0, 0, 255 }, /*   '5' (blue)       */
    { 255, 0, 255 }, /*   '6' (magenta)    */
    { 255, 255, 255 }, /*   '7' (white)      */
    { 128, 128, 128 }, /*   '8' (dark gray)  */
    { 192, 192, 192 }, /*   '9' (light gray) */
    { 255, 0, 0 }, /*  '10' */
    { 255, 127, 127 }, /*  '11' */
    { 204, 0, 0 }, /*  '12' */
    { 204, 102, 102 }, /*  '13' */
    { 153, 0, 0 }, /*  '14' */
    { 153, 76, 76 }, /*  '15' */
    { 127, 0, 0 }, /*  '16' */
    { 127, 63, 63 }, /*  '17' */
    { 76, 0, 0 }, /*  '18' */
    { 76, 38, 38 }, /*  '19' */
    { 255, 63, 0 }, /*  '20' */
    { 255, 159, 127 }, /*  '21' */
    { 204, 51, 0 }, /*  '22' */
    { 204, 127, 102 }, /*  '23' */
    { 153, 38, 0 }, /*  '24' */
    { 153, 95, 76 }, /*  '25' */
    { 127, 31, 0 }, /*  '26' */
    { 127, 79, 63 }, /*  '27' */
    { 76, 19, 0 }, /*  '28' */
    { 76, 47, 38 }, /*  '29' */
    { 255, 127, 0 }, /*  '30' */
    { 255, 191, 127 }, /*  '31' */
    { 204, 102, 0 }, /*  '32' */
    { 204, 153, 102 }, /*  '33' */
    { 153, 76, 0 }, /*  '34' */
    { 153, 114, 76 }, /*  '35' */
    { 127, 63, 0 }, /*  '36' */
    { 127, 95, 63 }, /*  '37' */
    { 76, 38, 0 }, /*  '38' */
    { 76, 57, 38 }, /*  '39' */
    { 255, 191, 0 }, /*  '40' */
    { 255, 223, 127 }, /*  '41' */
    { 204, 153, 0 }, /*  '42' */
    { 204, 178, 102 }, /*  '43' */
    { 153, 114, 0 }, /*  '44' */
    { 153, 133, 76 }, /*  '45' */
    { 127, 95, 0 }, /*  '46' */
    { 127, 111, 63 }, /*  '47' */
    { 76, 57, 0 }, /*  '48' */
    { 76, 66, 38 }, /*  '49' */
    { 255, 255, 0 }, /*  '50' */
    { 255, 255, 127 }, /*  '51' */
    { 204, 204, 0 }, /*  '52' */
    { 204, 204, 102 }, /*  '53' */
    { 153, 153, 0 }, /*  '54' */
    { 153, 153, 76 }, /*  '55' */
    { 127, 127, 0 }, /*  '56' */
    { 127, 127, 63 }, /*  '57' */
    { 76, 76, 0 }, /*  '58' */
    { 76, 76, 38 }, /*  '59' */
    { 191, 255, 0 }, /*  '60' */
    { 223, 255, 127 }, /*  '61' */
    { 153, 204, 0 }, /*  '62' */
    { 178, 204, 102 }, /*  '63' */
    { 114, 153, 0 }, /*  '64' */
    { 133, 153, 76 }, /*  '65' */
    { 95, 127, 0 }, /*  '66' */
    { 111, 127, 63 }, /*  '67' */
    { 57, 76, 0 }, /*  '68' */
    { 66, 76, 38 }, /*  '69' */
    { 127, 255, 0 }, /*  '70' */
    { 191, 255, 127 }, /*  '71' */
    { 102, 204, 0 }, /*  '72' */
    { 153, 204, 102 }, /*  '73' */
    { 76, 153, 0 }, /*  '74' */
    { 114, 153, 76 }, /*  '75' */
    { 63, 127, 0 }, /*  '76' */
    { 95, 127, 63 }, /*  '77' */
    { 38, 76, 0 }, /*  '78' */
    { 57, 76, 38 }, /*  '79' */
    { 63, 255, 0 }, /*  '80' */
    { 159, 255, 127 }, /*  '81' */
    { 51, 204, 0 }, /*  '82' */
    { 127, 204, 102 }, /*  '83' */
    { 38, 153, 0 }, /*  '84' */
    { 95, 153, 76 }, /*  '85' */
    { 31, 127, 0 }, /*  '86' */
    { 79, 127, 63 }, /*  '87' */
    { 19, 76, 0 }, /*  '88' */
    { 47, 76, 38 }, /*  '89' */
    { 0, 255, 0 }, /*  '90' */
    { 127, 255, 127 }, /*  '91' */
    { 0, 204, 0 }, /*  '92' */
    { 102, 204, 102 }, /*  '93' */
    { 0, 153, 0 }, /*  '94' */
    { 76, 153, 76 }, /*  '95' */
    { 0, 127, 0 }, /*  '96' */
    { 63, 127, 63 }, /*  '97' */
    { 0, 76, 0 }, /*  '98' */
    { 38, 76, 38 }, /*  '99' */
    { 0, 255, 63 }, /* '100' */
    { 127, 255, 159 }, /* '101' */
    { 0, 204, 51 }, /* '102' */
    { 102, 204, 127 }, /* '103' */
    { 0, 153, 38 }, /* '104' */
    { 76, 153, 95 }, /* '105' */
    { 0, 127, 31 }, /* '106' */
    { 63, 127, 79 }, /* '107' */
    { 0, 76, 19 }, /* '108' */
    { 38, 76, 47 }, /* '109' */
    { 0, 255, 127 }, /* '110' */
    { 127, 255, 191 }, /* '111' */
    { 0, 204, 102 }, /* '112' */
    { 102, 204, 153 }, /* '113' */
    { 0, 153, 76 }, /* '114' */
    { 76, 153, 114 }, /* '115' */
    { 0, 127, 63 }, /* '116' */
    { 63, 127, 95 }, /* '117' */
    { 0, 76, 38 }, /* '118' */
    { 38, 76, 57 }, /* '119' */
    { 0, 255, 191 }, /* '120' */
    { 127, 255, 223 }, /* '121' */
    { 0, 204, 153 }, /* '122' */
    { 102, 204, 178 }, /* '123' */
    { 0, 153, 114 }, /* '124' */
    { 76, 153, 133 }, /* '125' */
    { 0, 127, 95 }, /* '126' */
    { 63, 127, 111 }, /* '127' */
    { 0, 76, 57 }, /* '128' */
    { 38, 76, 66 }, /* '129' */
    { 0, 255, 255 }, /* '130' */
    { 127, 255, 255 }, /* '131' */
    { 0, 204, 204 }, /* '132' */
    { 102, 204, 204 }, /* '133' */
    { 0, 153, 153 }, /* '134' */
    { 76, 153, 153 }, /* '135' */
    { 0, 127, 127 }, /* '136' */
    { 63, 127, 127 }, /* '137' */
    { 0, 76, 76 }, /* '138' */
    { 38, 76, 76 }, /* '139' */
    { 0, 191, 255 }, /* '140' */
    { 127, 223, 255 }, /* '141' */
    { 0, 153, 204 }, /* '142' */
    { 102, 178, 204 }, /* '143' */
    { 0, 114, 153 }, /* '144' */
    { 76, 133, 153 }, /* '145' */
    { 0, 95, 127 }, /* '146' */
    { 63, 111, 127 }, /* '147' */
    { 0, 57, 76 }, /* '148' */
    { 38, 66, 76 }, /* '149' */
    { 0, 127, 255 }, /* '150' */
    { 127, 191, 255 }, /* '151' */
    { 0, 102, 204 }, /* '152' */
    { 102, 153, 204 }, /* '153' */
    { 0, 76, 153 }, /* '154' */
    { 76, 114, 153 }, /* '155' */
    { 0, 63, 127 }, /* '156' */
    { 63, 95, 127 }, /* '157' */
    { 0, 38, 76 }, /* '158' */
    { 38, 57, 76 }, /* '159' */
    { 0, 63, 255 }, /* '160' */
    { 127, 159, 255 }, /* '161' */
    { 0, 51, 204 }, /* '162' */
    { 102, 127, 204 }, /* '163' */
    { 0, 38, 153 }, /* '164' */
    { 76, 95, 153 }, /* '165' */
    { 0, 31, 127 }, /* '166' */
    { 63, 79, 127 }, /* '167' */
    { 0, 19, 76 }, /* '168' */
    { 38, 47, 76 }, /* '169' */
    { 0, 0, 255 }, /* '170' */
    { 127, 127, 255 }, /* '171' */
    { 0, 0, 204 }, /* '172' */
    { 102, 102, 204 }, /* '173' */
    { 0, 0, 153 }, /* '174' */
    { 76, 76, 153 }, /* '175' */
    { 0, 0, 127 }, /* '176' */
    { 63, 63, 127 }, /* '177' */
    { 0, 0, 76 }, /* '178' */
    { 38, 38, 76 }, /* '179' */
    { 63, 0, 255 }, /* '180' */
    { 159, 127, 255 }, /* '181' */
    { 51, 0, 204 }, /* '182' */
    { 127, 102, 204 }, /* '183' */
    { 38, 0, 153 }, /* '184' */
    { 95, 76, 153 }, /* '185' */
    { 31, 0, 127 }, /* '186' */
    { 79, 63, 127 }, /* '187' */
    { 19, 0, 76 }, /* '188' */
    { 47, 38, 76 }, /* '189' */
    { 127, 0, 255 }, /* '190' */
    { 191, 127, 255 }, /* '191' */
    { 102, 0, 204 }, /* '192' */
    { 153, 102, 204 }, /* '193' */
    { 76, 0, 153 }, /* '194' */
    { 114, 76, 153 }, /* '195' */
    { 63, 0, 127 }, /* '196' */
    { 95, 63, 127 }, /* '197' */
    { 38, 0, 76 }, /* '198' */
    { 57, 38, 76 }, /* '199' */
    { 191, 0, 255 }, /* '200' */
    { 223, 127, 255 }, /* '201' */
    { 153, 0, 204 }, /* '202' */
    { 178, 102, 204 }, /* '203' */
    { 114, 0, 153 }, /* '204' */
    { 133, 76, 153 }, /* '205' */
    { 95, 0, 127 }, /* '206' */
    { 111, 63, 127 }, /* '207' */
    { 57, 0, 76 }, /* '208' */
    { 66, 38, 76 }, /* '209' */
    { 255, 0, 255 }, /* '210' */
    { 255, 127, 255 }, /* '211' */
    { 204, 0, 204 }, /* '212' */
    { 204, 102, 204 }, /* '213' */
    { 153, 0, 153 }, /* '214' */
    { 153, 76, 153 }, /* '215' */
    { 127, 0, 127 }, /* '216' */
    { 127, 63, 127 }, /* '217' */
    { 76, 0, 76 }, /* '218' */
    { 76, 38, 76 }, /* '219' */
    { 255, 0, 191 }, /* '220' */
    { 255, 127, 223 }, /* '221' */
    { 204, 0, 153 }, /* '222' */
    { 204, 102, 178 }, /* '223' */
    { 153, 0, 114 }, /* '224' */
    { 153, 76, 133 }, /* '225' */
    { 127, 0, 95 }, /* '226' */
    { 127, 63, 111 }, /* '227' */
    { 76, 0, 57 }, /* '228' */
    { 76, 38, 66 }, /* '229' */
    { 255, 0, 127 }, /* '230' */
    { 255, 127, 191 }, /* '231' */
    { 204, 0, 102 }, /* '232' */
    { 204, 102, 153 }, /* '233' */
    { 153, 0, 76 }, /* '234' */
    { 153, 76, 114 }, /* '235' */
    { 127, 0, 63 }, /* '236' */
    { 127, 63, 95 }, /* '237' */
    { 76, 0, 38 }, /* '238' */
    { 76, 38, 57 }, /* '239' */
    { 255, 0, 63 }, /* '240' */
    { 255, 127, 159 }, /* '241' */
    { 204, 0, 51 }, /* '242' */
    { 204, 102, 127 }, /* '243' */
    { 153, 0, 38 }, /* '244' */
    { 153, 76, 95 }, /* '245' */
    { 127, 0, 31 }, /* '246' */
    { 127, 63, 79 }, /* '247' */
    { 76, 0, 19 }, /* '248' */
    { 76, 38, 47 }, /* '249' */
    { 51, 51, 51 }, /* '250' */
    { 91, 91, 91 }, /* '251' */
    { 132, 132, 132 }, /* '252' */
    { 173, 173, 173 }, /* '253' */
    { 214, 214, 214 }, /* '254' */
    { 255, 255, 255 }, /* '255' */
    { 0, 0, 0 } /* '256' (BYLAYER) */
};

char* readline(FILE* file)
{
    char str[255];
    /* TODO: replace all scanf code */
    fscanf(file, "%s", str);
    return lTrim(str, ' ');
}

#define MAX_LAYERS 16
#define MAX_LAYER_NAME_LENGTH 30
/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readDxf(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char buff[1024];
    char* dxfVersion = "";
    char* section = "";
    char* tableName = "";
    char* layerName = "";
    char* entityType = "";
    /* layer_names uses the same indexing as the EmbColor array, no need for hash table */
    char layer_names[MAX_LAYERS][MAX_LAYER_NAME_LENGTH];

    int eof = 0; /* End Of File */

    double bulge = 0.0, firstX = 0.0, firstY = 0.0, x = 0.0, y, prevX = 0.0, prevY = 0.0;
    char firstStitch = 1;
    char bulgeFlag = 0;
    int fileLength = 0;

    embFile_seek(file, 0L, SEEK_END);

    fileLength = embFile_tell(file);
    embFile_seek(file, 0L, SEEK_SET);

    while (embFile_tell(file) < fileLength) {
        embFile_readline(file, buff, 1000);
        /*printf("%s\n", buff);*/
        if ((!strcmp(buff, "HEADER")) || (!strcmp(buff, "CLASSES")) || (!strcmp(buff, "TABLES")) || (!strcmp(buff, "BLOCKS")) || (!strcmp(buff, "ENTITIES")) || (!strcmp(buff, "OBJECTS")) || (!strcmp(buff, "THUMBNAILIMAGE"))) {
            section = buff;
            printf("SECTION:%s\n", buff);
        }
        if (!strcmp(buff, "ENDSEC")) {
            section = "";
            printf("ENDSEC:%s\n", buff);
        }
        if ((!strcmp(buff, "ARC")) || (!strcmp(buff, "CIRCLE")) || (!strcmp(buff, "ELLIPSE")) || (!strcmp(buff, "LINE")) || (!strcmp(buff, "LWPOLYLINE")) || (!strcmp(buff, "POINT"))) {
            entityType = buff;
        }
        if (!strcmp(buff, "EOF")) {
            eof = 1;
        }

        if (!strcmp(section, "HEADER")) {
            if (!strcmp(buff, "$ACADVER")) {
                embFile_readline(file, buff, 1000);
                embFile_readline(file, dxfVersion, 1000);
                /* TODO: Allow these versions when POLYLINE is handled. */
                if ((!strcmp(dxfVersion, DXF_VERSION_R10))
                    || (!strcmp(dxfVersion, DXF_VERSION_R11))
                    || (!strcmp(dxfVersion, DXF_VERSION_R12))
                    || (!strcmp(dxfVersion, DXF_VERSION_R13)))
                    return 0;
            }
        } else if (!strcmp(section, "TABLES")) {
            if (!strcmp(buff, "ENDTAB")) {
                tableName = NULL;
            }

            if (tableName == NULL) {
                if (!strcmp(buff, "2")) /* Table Name */
                {
                    embFile_readline(file, tableName, 1000);
                }
            } else if (!strcmp(tableName, "LAYER")) {
                /* Common Group Codes for Tables */
                if (!strcmp(buff, "5")) /* Handle */
                {
                    embFile_readline(file, buff, 1000);
                    continue;
                } else if (!strcmp(buff, "330")) /* Soft Pointer */
                {
                    embFile_readline(file, buff, 1000);
                    continue;
                } else if (!strcmp(buff, "100")) /* Subclass Marker */
                {
                    embFile_readline(file, buff, 1000);
                    continue;
                } else if (!strcmp(buff, "70")) /* Number of Entries in Table */
                {
                    embFile_readline(file, buff, 1000);
                    continue;
                }
                /* The meaty stuff */
                else if (!strcmp(buff, "2")) /* Layer Name */
                {
                    embFile_readline(file, layerName, 1000);
                } else if (!strcmp(buff, "62")) /* Color Number */
                {
                    embFile_readline(file, buff, 1000);
                    /*
                    TODO: finish this
                    unsigned char colorNum = atoi(buff);
                    EmbColor co;
                    co.r = _dxfColorTable[colorNum][0];
                    co.g = _dxfColorTable[colorNum][1];
                    co.b = _dxfColorTable[colorNum][2];
                    printf("inserting:%s,%d,%d,%d\n", layerName, co.r, co.g, co.b);
                    if (embHash_insert(layer_names[i], emb_strdup(layerName), &co)) {
                         TODO: log error: failed inserting into layerColorHash
                    }
                    */
                    layerName = NULL;
                }
            }
        } else if (!strcmp(section, "ENTITIES")) {
            /* Common Group Codes for Entities */
            if (!strcmp(buff, "5")) /* Handle */
            {
                embFile_readline(file, buff, 1000);
                continue;
            } else if (!strcmp(buff, "330")) /* Soft Pointer */
            {
                embFile_readline(file, buff, 1000);
                continue;
            } else if (!strcmp(buff, "100")) /* Subclass Marker */
            {
                embFile_readline(file, buff, 1000);
                continue;
            } else if (!strcmp(buff, "8")) /* Layer Name */
            {
                embFile_readline(file, buff, 1000);
                /* embPattern_changeColor(pattern, colorIndexMap[buff]); TODO: port to C */
                continue;
            }

            if (!strcmp(entityType, "LWPOLYLINE")) {
                /* The not so important group codes */
                if (!strcmp(buff, "90")) /* Vertices */
                {
                    embFile_readline(file, buff, 1000);
                    continue;
                } else if (!strcmp(buff, "70")) /* Polyline Flag */
                {
                    embFile_readline(file, buff, 1000);
                    continue;
                }
                /* TODO: Try to use the widths at some point */
                else if (!strcmp(buff, "40")) /* Starting Width */
                {
                    embFile_readline(file, buff, 1000);
                    continue;
                } else if (!strcmp(buff, "41")) /* Ending Width */
                {
                    embFile_readline(file, buff, 1000);
                    continue;
                } else if (!strcmp(buff, "43")) /* Constant Width */
                {
                    embFile_readline(file, buff, 1000);
                    continue;
                }
                /* The meaty stuff */
                else if (!strcmp(buff, "42")) /* Bulge */
                {
                    embFile_readline(file, buff, 1000);
                    bulge = atof(buff);
                    bulgeFlag = 1;
                } else if (!strcmp(buff, "10")) /* X */
                {
                    embFile_readline(file, buff, 1000);
                    x = atof(buff);
                } else if (!strcmp(buff, "20")) /* Y */
                {
                    embFile_readline(file, buff, 1000);
                    y = atof(buff);

                    if (bulgeFlag) {
                        EmbArc arc;
                        EmbVector arcCenter;
                        bulgeFlag = 0;
                        arc.start.x = prevX;
                        arc.start.y = prevY;
                        arc.end.x = x;
                        arc.end.y = y;
                        /* TODO: sort arcMidX etc. */
                        if (!getArcDataFromBulge(bulge, &arc, &arcCenter, 0, 0, 0, 0, 0, 0, 0, 0)) {
                            /*TODO: error */
                            return 0;
                        }
                        if (firstStitch) {
                            /* embPattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        }
                        /* embPattern_addStitchAbs(pattern, x, y, ARC, 1); TODO: Add arcTo point to embPath pointList */
                    } else {
                        /*if(firstStitch) embPattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        /*else            embPattern_addStitchAbs(pattern, x, y, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
                    }
                    prevX = x;
                    prevY = y;
                    if (firstStitch) {
                        firstX = x;
                        firstY = y;
                        firstStitch = 0;
                    }
                } else if (!strcmp(buff, "0")) {
                    entityType = NULL;
                    firstStitch = 1;
                    if (bulgeFlag) {
                        EmbArc arc;
                        EmbVector arcCenter;
                        bulgeFlag = 0;
                        arc.start.x = prevX;
                        arc.start.y = prevY;
                        arc.end.x = firstX;
                        arc.end.y = firstY;
                        if (!getArcDataFromBulge(bulge, &arc, &arcCenter, 0, 0, 0, 0, 0, 0, 0, 0)) {
                            /*TODO: error */
                            return 0;
                        }
                        /* embPattern_addStitchAbs(pattern, prevX, prevY, ARC, 1); TODO: Add arcTo point to embPath pointList */
                    } else {
                        /* embPattern_addStitchAbs(pattern, firstX, firstY, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
                    }
                }
            } /* end LWPOLYLINE */
        } /* end ENTITIES section */
    } /* end while loop */

    /*
    EmbColor* testColor = 0;
    testColor = embHash_value(layerColorHash, "OMEGA");
    if(!testColor) printf("NULL POINTER!!!!!!!!!!!!!!\n");
    else printf("LAYERCOLOR: %d,%d,%d\n", testColor->r, testColor->g, testColor->b);
    */

    if (!eof) {
        /* NOTE: The EOF item must be present at the end of file to be considered a valid DXF file. */
        embLog("ERROR: format-dxf.c readDxf(), missing EOF at end of DXF file\n");
    }
    return eof;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeDxf(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeDxf */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readEdr(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int numberOfColors, i;
    EmbThread t;

    embFile_seek(file, 0x00, SEEK_END);
    numberOfColors = embFile_tell(file) / 4;
    embFile_seek(file, 0x00, SEEK_SET);

    embArray_free(pattern->threads);

    for (i = 0; i < numberOfColors; i++) {
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        t.catalogNumber = "";
        t.description = "";
        binaryReadByte(file);
        embPattern_addThread(pattern, t);
    }
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeEdr(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbColor c;
    int i;

    for (i = 0; i < pattern->threads->count; i++) {
        c = pattern->threads->thread[i].color;
        binaryWriteByte(file, c.r);
        binaryWriteByte(file, c.g);
        binaryWriteByte(file, c.b);
        binaryWriteByte(file, 0);
    }
    return 1;
}

static char emdDecode(unsigned char inputByte)
{
    return (inputByte >= 0x80) ? ((-~inputByte) - 1) : inputByte; /* TODO: eliminate ternary return statement */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readEmd(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b0 = 0, b1 = 0;
    char dx = 0, dy = 0;
    int flags = NORMAL;
    char endOfStream = 0;
    unsigned char jemd0[6]; /* TODO: more descriptive name */
    int width, height, colors;
    int i;

    embPattern_loadExternalColorFile(pattern, fileName);

    binaryReadBytes(file, jemd0, 6); /* TODO: check return value */
    width = binaryReadInt16(file);
    height = binaryReadInt16(file);
    colors = binaryReadInt16(file);

    embFile_seek(file, 0x30, SEEK_SET);

    for (i = 0; !endOfStream; i++) {
        flags = NORMAL;
        b0 = binaryReadUInt8(file);
        b1 = binaryReadUInt8(file);

        if (b0 == 0x80) {
            if (b1 == 0x2A) {
                embPattern_addStitchRel(pattern, 0, 0, STOP, 1);
                continue;
            } else if (b1 == 0x80) {
                b0 = binaryReadUInt8(file);
                b1 = binaryReadUInt8(file);
                flags = TRIM;
            } else if (b1 == 0xFD) {
                embPattern_addStitchRel(pattern, 0, 0, END, 1);
                break;
            } else {
                continue;
            }
        }
        dx = emdDecode(b0);
        dy = emdDecode(b1);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeEmd(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeEmd */
}

static char expDecode(unsigned char a1)
{
    return (a1 > 0x80) ? ((-~a1) - 1) : a1;
}

static void expEncode(unsigned char* b, char dx, char dy, int flags)
{
    if (!b) {
        embLog("ERROR: format-exp.c expEncode(), b argument is null\n");
        return;
    }

    if (flags == STOP) {
        b[0] = 0x80;
        b[1] = 0x01;
        b[2] = dx;
        b[3] = dy;
    } else if (flags == JUMP) {
        b[0] = 0x80;
        b[1] = 0x04;
        b[2] = dx;
        b[3] = dy;
    } else if (flags == TRIM || flags == END) {
        b[0] = 0x80;
        b[1] = 0x80;
        b[2] = 0;
        b[3] = 0;
    } else {
        b[0] = dx;
        b[1] = dy;
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readExp(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i = 0;
    unsigned char b0 = 0, b1 = 0;
    char dx = 0, dy = 0;
    int flags = 0;

    embPattern_loadExternalColorFile(pattern, fileName);

    for (i = 0; !embFile_eof(file); i++) {
        flags = NORMAL;
        b0 = (unsigned char)embFile_getc(file);
        if (embFile_eof(file))
            break;
        b1 = (unsigned char)embFile_getc(file);
        if (embFile_eof(file))
            break;
        if (b0 == 0x80) {
            if (b1 & 1) {
                b0 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
                b1 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
                flags = STOP;
            } else if ((b1 == 2) || (b1 == 4) || b1 == 6) {
                flags = TRIM;
                if (b1 == 2)
                    flags = NORMAL;
                b0 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
                b1 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
            } else if (b1 == 0x80) {
                b0 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
                b1 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
                /* Seems to be b0=0x07 and b1=0x00
                 * Maybe used as extension functions */
                b0 = 0;
                b1 = 0;
                flags = TRIM;
            }
        }
        dx = expDecode(b0);
        dy = expDecode(b1);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeExp(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    double dx, dy, xx, yy;
    int flags = 0, i;
    unsigned char b[4];
    EmbStitch st;

    /* write stitches */
    xx = yy = 0.0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        flags = st.flags;
        expEncode(b, (char)roundDouble(dx), (char)roundDouble(dy), flags);
        if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
            embFile_write(b, 1, 4, file);
        } else {
            embFile_write(b, 1, 2, file);
        }
    }
    embFile_print(file, "\x1a");
    return 1;
}

static int exyDecodeFlags(unsigned char b2)
{
    int returnCode = 0;
    if (b2 == 0xF3)
        return (END);
    if ((b2 & 0xC3) == 0xC3)
        return TRIM | STOP;
    if (b2 & 0x80)
        returnCode |= TRIM;
    if (b2 & 0x40)
        returnCode |= STOP;
    return returnCode;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readExy(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[3];

    embPattern_loadExternalColorFile(pattern, fileName);

    embFile_seek(file, 0x100, SEEK_SET);

    while (embFile_read(b, 1, 3, file) == 3) {
        int flags;
        int x = 0;
        int y = 0;
        if (b[0] & 0x01)
            x += 1;
        if (b[0] & 0x02)
            x -= 1;
        if (b[0] & 0x04)
            x += 9;
        if (b[0] & 0x08)
            x -= 9;
        if (b[0] & 0x80)
            y += 1;
        if (b[0] & 0x40)
            y -= 1;
        if (b[0] & 0x20)
            y += 9;
        if (b[0] & 0x10)
            y -= 9;
        if (b[1] & 0x01)
            x += 3;
        if (b[1] & 0x02)
            x -= 3;
        if (b[1] & 0x04)
            x += 27;
        if (b[1] & 0x08)
            x -= 27;
        if (b[1] & 0x80)
            y += 3;
        if (b[1] & 0x40)
            y -= 3;
        if (b[1] & 0x20)
            y += 27;
        if (b[1] & 0x10)
            y -= 27;
        if (b[2] & 0x04)
            x += 81;
        if (b[2] & 0x08)
            x -= 81;
        if (b[2] & 0x20)
            y += 81;
        if (b[2] & 0x10)
            y -= 81;
        flags = exyDecodeFlags(b[2]);
        if ((flags & END) == END) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
    }

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeExy(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeExy */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readEys(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish readEys */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeEys(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeEys */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readFxy(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_seek(file, 0x100, SEEK_SET); /* TODO: review for combining code. This line appears to be the only difference from the GT format. */

    while (1) {
        int stitchType = NORMAL;
        int b1 = (int)binaryReadByte(file);
        int b2 = (int)binaryReadByte(file);
        unsigned char commandByte = binaryReadByte(file);

        if (commandByte == 0x91) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
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
        embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeFxy(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeFxy */
}

/* Smoothie G-Code */
/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readGc(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish readGc */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeGc(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeGc */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readGnc(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish readGnc */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeGnc(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeGnc */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readGt(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_seek(file, 0x200, SEEK_SET); /* TODO: review for combining code. This line appears to be the only difference from the FXY format. */

    while (1) {
        int stitchType = NORMAL;
        int b1 = (int)binaryReadByte(file);
        int b2 = (int)binaryReadByte(file);
        unsigned char commandByte = binaryReadByte(file);

        if (commandByte == 0x91) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
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
        embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeGt(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeGt */
}

/*****************************************
 * HUS Colors
 ****************************************/
static const int husThreadCount = 29;
static const EmbThread husThreads[] = {
    { { 0, 0, 0 }, "Black", "TODO:HUS_CATALOG_NUMBER" },
    { { 0, 0, 255 }, "Blue", "TODO:HUS_CATALOG_NUMBER" },
    { { 0, 255, 0 }, "Light Green", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 0, 0 }, "Red", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 0, 255 }, "Purple", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 255, 0 }, "Yellow", "TODO:HUS_CATALOG_NUMBER" },
    { { 127, 127, 127 }, "Gray", "TODO:HUS_CATALOG_NUMBER" },
    { { 51, 154, 255 }, "Light Blue", "TODO:HUS_CATALOG_NUMBER" },
    { { 51, 204, 102 }, "Green", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 127, 0 }, "Orange", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 160, 180 }, "Pink", "TODO:HUS_CATALOG_NUMBER" },
    { { 153, 75, 0 }, "Brown", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 255, 255 }, "White", "TODO:HUS_CATALOG_NUMBER" },
    { { 0, 0, 127 }, "Dark Blue", "TODO:HUS_CATALOG_NUMBER" },
    { { 0, 127, 0 }, "Dark Green", "TODO:HUS_CATALOG_NUMBER" },
    { { 127, 0, 0 }, "Dark Red", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 127, 127 }, "Light Red", "TODO:HUS_CATALOG_NUMBER" },
    { { 127, 0, 127 }, "Dark Purple", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 127, 255 }, "Light Purple", "TODO:HUS_CATALOG_NUMBER" },
    { { 200, 200, 0 }, "Dark Yellow", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 255, 153 }, "Light Yellow", "TODO:HUS_CATALOG_NUMBER" },
    { { 60, 60, 60 }, "Dark Gray", "TODO:HUS_CATALOG_NUMBER" },
    { { 192, 192, 192 }, "Light Gray", "TODO:HUS_CATALOG_NUMBER" },
    { { 232, 63, 0 }, "Dark Orange", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 165, 65 }, "Light Orange", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 102, 122 }, "Dark Pink", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 204, 204 }, "Light Pink", "TODO:HUS_CATALOG_NUMBER" },
    { { 115, 40, 0 }, "Dark Brown", "TODO:HUS_CATALOG_NUMBER" },
    { { 175, 90, 10 }, "Light Brown", "TODO:HUS_CATALOG_NUMBER" }
};

/*TODO: 'husDecode' is defined but not used. Either remove it or use it. */
/*
static short husDecode(unsigned char a1, unsigned char a2)
{
    unsigned short res = (a2 << 8) + a1;
    if(res >= 0x8000)
    {
        return ((-~res) - 1);
    }
    else
    {
        return (res);
	}
}
*/

static int husDecodeStitchType(unsigned char b)
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

static unsigned char* husDecompressData(unsigned char* input, int compressedInputLength, int decompressedContentLength)
{
    unsigned char* decompressedData = (unsigned char*)malloc(sizeof(unsigned char) * decompressedContentLength);
    if (!decompressedData) {
        embLog("ERROR: format-hus.c husDecompressData(), cannot allocate memory for decompressedData\n");
        return 0;
    }
    husExpand((unsigned char*)input, decompressedData, compressedInputLength, 10);
    return decompressedData;
}

static unsigned char* husCompressData(unsigned char* input, int decompressedInputSize, int* compressedSize)
{
    unsigned char* compressedData = (unsigned char*)malloc(sizeof(unsigned char) * decompressedInputSize * 2);
    if (!compressedData) {
        embLog("ERROR: format-hus.c husCompressData(), cannot allocate memory for compressedData\n");
        return 0;
    }
    *compressedSize = husCompress(input, (unsigned long)decompressedInputSize, compressedData, 10, 0);
    return compressedData;
}

static int husDecodeByte(unsigned char b)
{
    return (char)b;
}

static unsigned char husEncodeByte(double f)
{
    return (unsigned char)(int)roundDouble(f);
}

static unsigned char husEncodeStitchType(int st)
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

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readHus(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int fileLength, i, magicCode, numberOfStitches, numberOfColors;
    int postitiveXHoopSize, postitiveYHoopSize, negativeXHoopSize, negativeYHoopSize, attributeOffset, xOffset, yOffset;
    unsigned char* attributeData = 0;
    unsigned char* attributeDataDecompressed = 0;

    unsigned char* xData = 0;
    unsigned char* xDecompressed = 0;

    unsigned char* yData = 0;
    unsigned char* yDecompressed = 0;
    unsigned char* stringVal = 0;

    embFile_seek(file, 0x00, SEEK_END);
    fileLength = embFile_tell(file);
    embFile_seek(file, 0x00, SEEK_SET);

    magicCode = binaryReadInt32(file);
    numberOfStitches = binaryReadInt32(file);
    numberOfColors = binaryReadInt32(file);

    postitiveXHoopSize = binaryReadInt16(file);
    postitiveYHoopSize = binaryReadInt16(file);
    negativeXHoopSize = binaryReadInt16(file);
    negativeYHoopSize = binaryReadInt16(file);

    attributeOffset = binaryReadInt32(file);
    xOffset = binaryReadInt32(file);
    yOffset = binaryReadInt32(file);

    stringVal = (unsigned char*)malloc(sizeof(unsigned char) * 8);
    if (!stringVal) {
        embLog("ERROR: format-hus.c readHus(), cannot allocate memory for stringVal\n");
        return 0;
    }
    binaryReadBytes(file, stringVal, 8); /* TODO: check return value */

    binaryReadInt16(file);
    for (i = 0; i < numberOfColors; i++) {
        int pos = binaryReadInt16(file);
        embPattern_addThread(pattern, husThreads[pos]);
    }

    attributeData = (unsigned char*)malloc(sizeof(unsigned char) * (xOffset - attributeOffset + 1));
    if (!attributeData) {
        embLog("ERROR: format-hus.c readHus(), cannot allocate memory for attributeData\n");
        return 0;
    }
    binaryReadBytes(file, attributeData, xOffset - attributeOffset); /* TODO: check return value */
    attributeDataDecompressed = husDecompressData(attributeData, xOffset - attributeOffset, numberOfStitches + 1);

    xData = (unsigned char*)malloc(sizeof(unsigned char) * (yOffset - xOffset + 1));
    if (!xData) {
        embLog("ERROR: format-hus.c readHus(), cannot allocate memory for xData\n");
        return 0;
    }
    binaryReadBytes(file, xData, yOffset - xOffset); /* TODO: check return value */
    xDecompressed = husDecompressData(xData, yOffset - xOffset, numberOfStitches);

    yData = (unsigned char*)malloc(sizeof(unsigned char) * (fileLength - yOffset + 1));
    if (!yData) {
        embLog("ERROR: format-hus.c readHus(), cannot allocate memory for yData\n");
        return 0;
    }
    binaryReadBytes(file, yData, fileLength - yOffset); /* TODO: check return value */
    yDecompressed = husDecompressData(yData, fileLength - yOffset, numberOfStitches);

    for (i = 0; i < numberOfStitches; i++) {
        embPattern_addStitchRel(pattern,
            husDecodeByte(xDecompressed[i]) / 10.0,
            husDecodeByte(yDecompressed[i]) / 10.0,
            husDecodeStitchType(attributeDataDecompressed[i]), 1);
    }

    if (stringVal) {
        free(stringVal);
        stringVal = 0;
    }
    if (xData) {
        free(xData);
        xData = 0;
    }
    if (xDecompressed) {
        free(xDecompressed);
        xDecompressed = 0;
    }
    if (yData) {
        free(yData);
        yData = 0;
    }
    if (yDecompressed) {
        free(yDecompressed);
        yDecompressed = 0;
    }
    if (attributeData) {
        free(attributeData);
        attributeData = 0;
    }
    if (attributeDataDecompressed) {
        free(attributeDataDecompressed);
        attributeDataDecompressed = 0;
    }

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeHus(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor;
    int attributeSize, xCompressedSize, yCompressedSize, i;
    double previousX, previousY;
    unsigned char *xValues = 0, *yValues = 0, *attributeValues = 0;
    unsigned char *attributeCompressed = 0, *xCompressed = 0, *yCompressed = 0;
    EmbStitch st;

    stitchCount = pattern->stitchList->count;
    /* embPattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */
    minColors = pattern->threads->count;
    patternColor = minColors;
    if (minColors > 24)
        minColors = 24;
    binaryWriteUInt(file, 0x00C8AF5B);
    binaryWriteUInt(file, stitchCount);
    binaryWriteUInt(file, minColors);

    boundingRect = embPattern_calcBoundingBox(pattern);
    binaryWriteShort(file, (short)roundDouble(boundingRect.right * 10.0));
    binaryWriteShort(file, (short)-roundDouble(boundingRect.top * 10.0 - 1.0));
    binaryWriteShort(file, (short)roundDouble(boundingRect.left * 10.0));
    binaryWriteShort(file, (short)-roundDouble(boundingRect.bottom * 10.0 - 1.0));

    binaryWriteUInt(file, 0x2A + 2 * minColors);

    xValues = (unsigned char*)malloc(sizeof(unsigned char) * (stitchCount));
    if (!xValues) {
        embLog("ERROR: format-hus.c writeHus(), cannot allocate memory for xValues\n");
        return 0;
    }
    yValues = (unsigned char*)malloc(sizeof(unsigned char) * (stitchCount));
    if (!yValues) {
        embLog("ERROR: format-hus.c writeHus(), cannot allocate memory for yValues\n");
        return 0;
    }
    attributeValues = (unsigned char*)malloc(sizeof(unsigned char) * (stitchCount));
    if (!attributeValues) {
        embLog("ERROR: format-hus.c writeHus(), cannot allocate memory for attributeValues\n");
        return 0;
    }

    previousX = 0.0;
    previousY = 0.0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        xValues[i] = husEncodeByte((st.x - previousX) * 10.0);
        previousX = st.x;
        yValues[i] = husEncodeByte((st.y - previousY) * 10.0);
        previousY = st.y;
        attributeValues[i] = husEncodeStitchType(st.flags);
    }
    attributeCompressed = husCompressData(attributeValues, stitchCount, &attributeSize);
    xCompressed = husCompressData(xValues, stitchCount, &xCompressedSize);
    yCompressed = husCompressData(yValues, stitchCount, &yCompressedSize);
    /* TODO: error if husCompressData returns zero? */

    binaryWriteUInt(file, (unsigned int)(0x2A + 2 * patternColor + attributeSize));
    binaryWriteUInt(file, (unsigned int)(0x2A + 2 * patternColor + attributeSize + xCompressedSize));
    binaryWriteUInt(file, 0x00000000);
    binaryWriteUInt(file, 0x00000000);
    binaryWriteUShort(file, 0x0000);

    for (i = 0; i < patternColor; i++) {
        short color_index = (short)embThread_findNearestColor_fromThread(pattern->threads->thread[i].color, husThreads, 0);
        binaryWriteShort(file, color_index);
    }

    binaryWriteBytes(file, (char*)attributeCompressed, attributeSize);
    binaryWriteBytes(file, (char*)xCompressed, xCompressedSize);
    binaryWriteBytes(file, (char*)yCompressed, yCompressedSize);

    free(xValues);
    free(xCompressed);
    free(yValues);
    free(yCompressed);
    free(attributeValues);
    free(attributeCompressed);
    return 1;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readInb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char fileDescription[8];
    unsigned char nullVal;
    int stitchCount;
    short width, height;
    short colorCount;
    short unknown3, unknown2;
    short imageWidth, imageHeight;
    unsigned char bytesUnknown[300]; /* TODO: determine what this represents */
    short nullbyte;
    short left, right, top, bottom;
    int x, y, i, fileLength;

    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_seek(file, 0, SEEK_END);
    fileLength = embFile_tell(file);
    binaryReadBytes(file, fileDescription, 8); /* TODO: check return value */
    nullVal = binaryReadByte(file);
    binaryReadInt16(file);
    stitchCount = binaryReadInt32(file);
    width = binaryReadInt16(file);
    height = binaryReadInt16(file);
    colorCount = binaryReadInt16(file);
    unknown3 = binaryReadInt16(file);
    unknown2 = binaryReadInt16(file);
    imageWidth = binaryReadInt16(file);
    imageHeight = binaryReadInt16(file);
    binaryReadBytes(file, bytesUnknown, 300); /* TODO: check return value */
    nullbyte = binaryReadInt16(file);
    left = binaryReadInt16(file);
    right = binaryReadInt16(file);
    top = binaryReadInt16(file);
    bottom = binaryReadInt16(file);
    embFile_seek(file, 0x2000, SEEK_SET);
    /* Calculate stitch count since header has been seen to be blank */
    stitchCount = (int)((fileLength - 0x2000) / 3);
    for (i = 0; i < stitchCount; i++) {
        unsigned char type;
        int stitch = NORMAL;
        x = binaryReadByte(file);
        y = binaryReadByte(file);
        type = binaryReadByte(file);
        if ((type & 0x40) > 0)
            x = -x;
        if ((type & 0x10) > 0)
            y = -y;
        if ((type & 1) > 0)
            stitch = STOP;
        if ((type & 2) > 0)
            stitch = TRIM;
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitch, 1);
    }

    embPattern_flipVertical(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeInb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeInb */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readInf(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int numberOfColors, i;
    char colorType[50];
    char colorDescription[50];
    EmbThread t;

    embFile_seek(file, 12L, SEEK_SET);
    numberOfColors = binaryReadUInt32BE(file);

    embArray_free(pattern->threads);
    pattern->threads = embArray_create(EMB_THREAD);

    for (i = 0; i < numberOfColors; i++) {
        binaryReadUInt16(file);
        binaryReadUInt16(file);
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        t.catalogNumber = "";
        t.description = "";
        embPattern_addThread(pattern, t);
        binaryReadUInt16(file);
        binaryReadString(file, colorType, 50);
        binaryReadString(file, colorDescription, 50);
    }
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeInf(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i, bytesRemaining;
    char buffer[50];
    EmbColor c;

    binaryWriteUIntBE(file, 0x01);
    binaryWriteUIntBE(file, 0x08);
    /* write place holder offset */
    binaryWriteUIntBE(file, 0x00);
    binaryWriteUIntBE(file, pattern->threads->count);

    for (i = 0; i < pattern->threads->count; i++) {
        c = pattern->threads->thread[i].color;
        sprintf(buffer, "RGB(%d,%d,%d)", (int)c.r, (int)c.g, (int)c.b);
        binaryWriteUShortBE(file, (unsigned short)(14 + strlen(buffer))); /* record length */
        binaryWriteUShortBE(file, (unsigned short)i); /* record number */
        binaryWriteByte(file, c.r);
        binaryWriteByte(file, c.g);
        binaryWriteByte(file, c.b);
        binaryWriteUShortBE(file, (unsigned short)i); /* needle number */
        binaryWriteBytes(file, "RGB\0", 4);
        embFile_print(file, buffer);
        binaryWriteByte(file, 0);
    }
    embFile_seek(file, -8, SEEK_END);
    bytesRemaining = embFile_tell(file);
    embFile_seek(file, 8, SEEK_SET);
    binaryWriteUIntBE(file, bytesRemaining);
    return 1;
}

static const EmbThread jefThreads[] = {
    { { 0, 0, 0 }, "Black", "" },
    { { 0, 0, 0 }, "Black", "" },
    { { 255, 255, 255 }, "White", "" },
    { { 255, 255, 23 }, "Yellow", "" },
    { { 250, 160, 96 }, "Orange", "" },
    { { 92, 118, 73 }, "Olive Green", "" },
    { { 64, 192, 48 }, "Green", "" },
    { { 101, 194, 200 }, "Sky", "" },
    { { 172, 128, 190 }, "Purple", "" },
    { { 245, 188, 203 }, "Pink", "" },
    { { 255, 0, 0 }, "Red", "" },
    { { 192, 128, 0 }, "Brown", "" },
    { { 0, 0, 240 }, "Blue", "" },
    { { 228, 195, 93 }, "Gold", "" },
    { { 165, 42, 42 }, "Dark Brown", "" },
    { { 213, 176, 212 }, "Pale Violet", "" },
    { { 252, 242, 148 }, "Pale Yellow", "" },
    { { 240, 208, 192 }, "Pale Pink", "" },
    { { 255, 192, 0 }, "Peach", "" },
    { { 201, 164, 128 }, "Beige", "" },
    { { 155, 61, 75 }, "Wine Red", "" },
    { { 160, 184, 204 }, "Pale Sky", "" },
    { { 127, 194, 28 }, "Yellow Green", "" },
    { { 185, 185, 185 }, "Silver Grey", "" },
    { { 160, 160, 160 }, "Grey", "" },
    { { 152, 214, 189 }, "Pale Aqua", "" },
    { { 184, 240, 240 }, "Baby Blue", "" },
    { { 54, 139, 160 }, "Powder Blue", "" },
    { { 79, 131, 171 }, "Bright Blue", "" },
    { { 56, 106, 145 }, "Slate Blue", "" },
    { { 0, 32, 107 }, "Nave Blue", "" },
    { { 229, 197, 202 }, "Salmon Pink", "" },
    { { 249, 103, 107 }, "Coral", "" },
    { { 227, 49, 31 }, "Burnt Orange", "" },
    { { 226, 161, 136 }, "Cinnamon", "" },
    { { 181, 148, 116 }, "Umber", "" },
    { { 228, 207, 153 }, "Blonde", "" },
    { { 225, 203, 0 }, "Sunflower", "" },
    { { 225, 173, 212 }, "Orchid Pink", "" },
    { { 195, 0, 126 }, "Peony Purple", "" },
    { { 128, 0, 75 }, "Burgundy", "" },
    { { 160, 96, 176 }, "Royal Purple", "" },
    { { 192, 64, 32 }, "Cardinal Red", "" },
    { { 202, 224, 192 }, "Opal Green", "" },
    { { 137, 152, 86 }, "Moss Green", "" },
    { { 0, 170, 0 }, "Meadow Green", "" },
    { { 33, 138, 33 }, "Dark Green", "" },
    { { 93, 174, 148 }, "Aquamarine", "" },
    { { 76, 191, 143 }, "Emerald Green", "" },
    { { 0, 119, 114 }, "Peacock Green", "" },
    { { 112, 112, 112 }, "Dark Grey", "" },
    { { 242, 255, 255 }, "Ivory White", "" },
    { { 177, 88, 24 }, "Hazel", "" },
    { { 203, 138, 7 }, "Toast", "" },
    { { 247, 146, 123 }, "Salmon", "" },
    { { 152, 105, 45 }, "Cocoa Brown", "" },
    { { 162, 113, 72 }, "Sienna", "" },
    { { 123, 85, 74 }, "Sepia", "" },
    { { 79, 57, 70 }, "Dark Sepia", "" },
    { { 82, 58, 151 }, "Violet Blue", "" },
    { { 0, 0, 160 }, "Blue Ink", "" },
    { { 0, 150, 222 }, "Solar Blue", "" },
    { { 178, 221, 83 }, "Green Dust", "" },
    { { 250, 143, 187 }, "Crimson", "" },
    { { 222, 100, 158 }, "Floral Pink", "" },
    { { 181, 80, 102 }, "Wine", "" },
    { { 94, 87, 71 }, "Olive Drab", "" },
    { { 76, 136, 31 }, "Meadow", "" },
    { { 228, 220, 121 }, "Mustard", "" },
    { { 203, 138, 26 }, "Yellow Ochre", "" },
    { { 198, 170, 66 }, "Old Gold", "" },
    { { 236, 176, 44 }, "Honeydew", "" },
    { { 248, 128, 64 }, "Tangerine", "" },
    { { 255, 229, 5 }, "Canary Yellow", "" },
    { { 250, 122, 122 }, "Vermillion", "" },
    { { 107, 224, 0 }, "Bright Green", "" },
    { { 56, 108, 174 }, "Ocean Blue", "" },
    { { 227, 196, 180 }, "Beige Grey", "" },
    { { 227, 172, 129 }, "Bamboo", "" }
};

#define HOOP_126X110 0
#define HOOP_110X110 1
#define HOOP_50X50 2
#define HOOP_140X200 3
#define HOOP_230X200 4

static int jefGetHoopSize(int width, int height)
{
    if (width < 50 && height < 50) {
        return HOOP_50X50;
    }
    if (width < 110 && height < 110) {
        return HOOP_110X110;
    }
    if (width < 140 && height < 200) {
        return HOOP_140X200;
    }
    return ((int)HOOP_110X110);
}
static char jefDecode(unsigned char inputByte)
{
    if (inputByte >= 0x80)
        return (char)((-~inputByte) - 1);
    return ((char)inputByte);
}
static void jefSetHoopFromId(EmbPattern* pattern, int hoopCode)
{
    if (!pattern) {
        embLog("ERROR: format-jef.c jefSetHoopFromId(), pattern argument is null\n");
        return;
    }

    switch (hoopCode) {
    case HOOP_126X110:
        pattern->hoop.height = 126.0;
        pattern->hoop.width = 110.0;
        break;
    case HOOP_50X50:
        pattern->hoop.height = 50.0;
        pattern->hoop.width = 50.0;
        break;
    case HOOP_110X110:
        pattern->hoop.height = 110.0;
        pattern->hoop.width = 110.0;
        break;
    case HOOP_140X200:
        pattern->hoop.height = 140.0;
        pattern->hoop.width = 200.0;
        break;
    case HOOP_230X200:
        pattern->hoop.height = 230.0;
        pattern->hoop.width = 200.0;
        break;
    }
}

struct hoop_padding {
    int left;
    int right;
    int top;
    int bottom;
};

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readJef(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int stitchOffset, formatFlags, numberOfColors, numberOfStitchs;
    int hoopSize, i;
    struct hoop_padding bounds, rectFrom110x110, rectFrom50x50, rectFrom200x140, rect_from_custom;
    int stitchCount;
    char date[8], time[8];
    unsigned char b0 = 0, b1 = 0;
    char dx = 0, dy = 0;
    int flags = 0;

    stitchOffset = binaryReadInt32(file);
    formatFlags = binaryReadInt32(file); /* TODO: find out what this means */

    binaryReadBytes(file, (unsigned char*)date, 8); /* TODO: check return value */
    binaryReadBytes(file, (unsigned char*)time, 8); /* TODO: check return value */
    numberOfColors = binaryReadInt32(file);
    numberOfStitchs = binaryReadInt32(file);
    hoopSize = binaryReadInt32(file);
    jefSetHoopFromId(pattern, hoopSize);

    bounds.left = binaryReadInt32(file);
    bounds.top = binaryReadInt32(file);
    bounds.right = binaryReadInt32(file);
    bounds.bottom = binaryReadInt32(file);

    rectFrom110x110.left = binaryReadInt32(file);
    rectFrom110x110.top = binaryReadInt32(file);
    rectFrom110x110.right = binaryReadInt32(file);
    rectFrom110x110.bottom = binaryReadInt32(file);

    rectFrom50x50.left = binaryReadInt32(file);
    rectFrom50x50.top = binaryReadInt32(file);
    rectFrom50x50.right = binaryReadInt32(file);
    rectFrom50x50.bottom = binaryReadInt32(file);

    rectFrom200x140.left = binaryReadInt32(file);
    rectFrom200x140.top = binaryReadInt32(file);
    rectFrom200x140.right = binaryReadInt32(file);
    rectFrom200x140.bottom = binaryReadInt32(file);

    rect_from_custom.left = binaryReadInt32(file);
    rect_from_custom.top = binaryReadInt32(file);
    rect_from_custom.right = binaryReadInt32(file);
    rect_from_custom.bottom = binaryReadInt32(file);

    for (i = 0; i < numberOfColors; i++) {
        embPattern_addThread(pattern, jefThreads[binaryReadInt32(file) % 79]);
    }
    embFile_seek(file, stitchOffset, SEEK_SET);
    stitchCount = 0;
    while (stitchCount < numberOfStitchs + 100) {
        flags = NORMAL;
        b0 = (unsigned char)embFile_getc(file);
        if (embFile_eof(file)) {
            break;
        }
        b1 = (unsigned char)embFile_getc(file);
        if (embFile_eof(file)) {
            break;
        }
        if (b0 == 0x80) {
            if (b1 & 1) {
                b0 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
                b1 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file))
                    break;
                flags = STOP;
            } else if ((b1 == 2) || (b1 == 4) || b1 == 6) {
                flags = TRIM;
                b0 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file)) {
                    break;
                }
                b1 = (unsigned char)embFile_getc(file);
                if (embFile_eof(file)) {
                    break;
                }
            } else if (b1 == 0x10) {
                embPattern_addStitchRel(pattern, 0.0, 0.0, END, 1);
                break;
            }
        }
        dx = jefDecode(b0);
        dy = jefDecode(b1);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

static void jefEncode(unsigned char* b, char dx, char dy, int flags)
{
    if (!b) {
        embLog("ERROR: format-jef.c expEncode(), b argument is null\n");
        return;
    }
    if (flags == STOP) {
        b[0] = 0x80;
        b[1] = 1;
        b[2] = dx;
        b[3] = dy;
    } else if (flags == END) {
        b[0] = 0x80;
        b[1] = 0x10;
        b[2] = 0;
        b[3] = 0;
    } else if (flags == TRIM || flags == JUMP) {
        b[0] = 0x80;
        b[1] = 2;
        b[2] = dx;
        b[3] = dy;
    } else {
        b[0] = dx;
        b[1] = dy;
    }
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeJef(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int colorlistSize, minColors, designWidth, designHeight, i;
    EmbRect boundingRect;
    EmbTime time;
    EmbStitch st;
    double dx = 0.0, dy = 0.0, xx = 0.0, yy = 0.0;
    unsigned char b[4];

    embPattern_correctForMaxStitchLength(pattern, 12.7, 12.7);

    colorlistSize = pattern->threads->count;
    minColors = EMB_MAX_2(colorlistSize, 6);
    binaryWriteInt(file, 0x74 + (minColors * 4));
    binaryWriteInt(file, 0x0A);

    embTime_initNow(&time);

    writeInt(file, (int)(time.year + 1900), 4);
    writeInt(file, (int)(time.month + 1), 2); /* TODO: pad with zeros all date/time entries */
    writeInt(file, (int)(time.day), 2);
    writeInt(file, (int)(time.hour), 2);
    writeInt(file, (int)(time.minute), 2);
    writeInt(file, (int)(time.second), 2);
    binaryWriteByte(file, 0x00);
    binaryWriteByte(file, 0x00);
    binaryWriteInt(file, pattern->threads->count);
    binaryWriteInt(file, pattern->stitchList->count + EMB_MAX_2(0, (6 - colorlistSize) * 2) + 1);

    boundingRect = embPattern_calcBoundingBox(pattern);

    designWidth = (int)(embRect_width(boundingRect) * 10.0);
    designHeight = (int)(embRect_width(boundingRect) * 10.0);

    binaryWriteInt(file, jefGetHoopSize(designWidth, designHeight));

    /* Distance from center of Hoop */
    binaryWriteInt(file, (int)(designWidth / 2)); /* left */
    binaryWriteInt(file, (int)(designHeight / 2)); /* top */
    binaryWriteInt(file, (int)(designWidth / 2)); /* right */
    binaryWriteInt(file, (int)(designHeight / 2)); /* bottom */

    /* Distance from default 110 x 110 Hoop */
    if (EMB_MIN_2(550 - designWidth / 2, 550 - designHeight / 2) >= 0) {
        binaryWriteInt(file, EMB_MAX_2(-1, 550 - designWidth / 2)); /* left */
        binaryWriteInt(file, EMB_MAX_2(-1, 550 - designHeight / 2)); /* top */
        binaryWriteInt(file, EMB_MAX_2(-1, 550 - designWidth / 2)); /* right */
        binaryWriteInt(file, EMB_MAX_2(-1, 550 - designHeight / 2)); /* bottom */
    } else {
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
    }

    /* Distance from default 50 x 50 Hoop */
    if (EMB_MIN_2(250 - designWidth / 2, 250 - designHeight / 2) >= 0) {
        binaryWriteInt(file, (int)EMB_MAX_2(-1, 250 - designWidth / 2)); /* left */
        binaryWriteInt(file, (int)EMB_MAX_2(-1, 250 - designHeight / 2)); /* top */
        binaryWriteInt(file, (int)EMB_MAX_2(-1, 250 - designWidth / 2)); /* right */
        binaryWriteInt(file, (int)EMB_MAX_2(-1, 250 - designHeight / 2)); /* bottom */
    } else {
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
    }

    /* Distance from default 140 x 200 Hoop */
    binaryWriteInt(file, (int)(700 - designWidth / 2)); /* left */
    binaryWriteInt(file, (int)(1000 - designHeight / 2)); /* top */
    binaryWriteInt(file, (int)(700 - designWidth / 2)); /* right */
    binaryWriteInt(file, (int)(1000 - designHeight / 2)); /* bottom */

    /* repeated Distance from default 140 x 200 Hoop */
    /* TODO: Actually should be distance to custom hoop */
    binaryWriteInt(file, (int)(630 - designWidth / 2)); /* left */
    binaryWriteInt(file, (int)(550 - designHeight / 2)); /* top */
    binaryWriteInt(file, (int)(630 - designWidth / 2)); /* right */
    binaryWriteInt(file, (int)(550 - designHeight / 2)); /* bottom */

    for (i = 0; i < pattern->threads->count; i++) {
        int j = embThread_findNearestColor_fromThread(pattern->threads->thread[i].color, jefThreads, 79);
        binaryWriteInt(file, j);
    }

    for (i = 0; i < (minColors - colorlistSize); i++) {
        binaryWriteInt(file, 0x0D);
    }

    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        jefEncode(b, (char)roundDouble(dx), (char)roundDouble(dy), st.flags);
        if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
            embFile_write(b, 1, 4, file);
        } else {
            embFile_write(b, 1, 2, file);
        }
    }
    return 1;
}

static void ksmEncode(unsigned char* b, char dx, char dy, int flags)
{
    if (!b) {
        embLog("ERROR: format-ksm.c ksmEncode(), b argument is null\n");
        return;
    }
    /* TODO: How to encode JUMP stitches? JUMP must be handled. Also check this for the EXP format since it appears to be similar */
    if (flags == TRIM) {
        b[0] = 128;
        b[1] = 2;
        b[2] = dx;
        b[3] = dy;
    } else if (flags == STOP) {
        b[0] = 128;
        b[1] = 1;
        b[2] = dx;
        b[3] = dy;
    } else {
        b[0] = dx;
        b[1] = dy;
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readKsm(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int prevStitchType = NORMAL;
    char b[3];

    embFile_seek(file, 0x200, SEEK_SET);

    while (embFile_read(b, 1, 3, file) == 3) {
        int flags = NORMAL;

        if (((prevStitchType & 0x08) == 0x08) && (b[2] & 0x08) == 0x08) {
            flags = STOP;
        } else if ((b[2] & 0x1F) != 0) {
            flags = TRIM;
        }
        prevStitchType = b[2];
        if (b[2] & 0x40)
            b[1] = -b[1];
        if (b[2] & 0x20)
            b[0] = -b[0];
        embPattern_addStitchRel(pattern, b[1] / 10.0, b[0] / 10.0, flags, 1);
    }
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeKsm(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbStitch st;
    double xx, yy, dx, dy;
    int i;
    unsigned char b[4];

    for (i = 0; i < 0x80; i++) {
        binaryWriteInt(file, 0);
    }
    /* write stitches */
    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        dx = st.x - xx;
        dy = st.y - yy;
        xx = st.x;
        yy = st.y;
        ksmEncode(b, (char)(dx * 10.0), (char)(dy * 10.0), st.flags);
        embFile_write(b, 1, 2, file);
    }
    embFile_print(file, "\x1a");
    return 1;
}

/* Pfaff MAX embroidery file format */

static double maxDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res)&0x7FFFFF) - 1));
    }
    return res;
}

static void maxEncode(EmbFile* file, int x, int y)
{
    if (!file) {
        embLog("ERROR: format-max.c maxEncode(), file argument is null\n");
        return;
    }

    binaryWriteByte(file, (unsigned char)0);
    binaryWriteByte(file, (unsigned char)(x & 0xFF));
    binaryWriteByte(file, (unsigned char)((x >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((x >> 16) & 0xFF));

    binaryWriteByte(file, (unsigned char)0);
    binaryWriteByte(file, (unsigned char)(y & 0xFF));
    binaryWriteByte(file, (unsigned char)((y >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((y >> 16) & 0xFF));
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readMax(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[8];
    double dx, dy;
    int i, flags, stitchCount;

    embFile_seek(file, 0xD5, SEEK_SET);
    stitchCount = binaryReadUInt32(file);

    /* READ STITCH RECORDS */
    for (i = 0; i < stitchCount; i++) {
        flags = NORMAL;
        if (embFile_read(b, 1, 8, file) != 8)
            break;

        dx = maxDecode(b[0], b[1], b[2]);
        dy = maxDecode(b[4], b[5], b[6]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    embPattern_flipVertical(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeMax(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char header[] = {
        0x56, 0x43, 0x53, 0x4D, 0xFC, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0xF6, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x33, 0x37, 0x38,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4D, 0x61, 0x64, 0x65, 0x69, 0x72, 0x61, 0x20,
        0x52, 0x61, 0x79, 0x6F, 0x6E, 0x20, 0x34, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x38, 0x09, 0x31, 0x33, 0x30, 0x2F, 0x37, 0x30, 0x35, 0x20, 0x48, 0xFA, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00
    };
    double x, y;
    EmbStitch st;
    int i;

    binaryWriteBytes(file, header, 0xD5);
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        x = roundDouble(st.x * 10.0);
        y = roundDouble(st.y * 10.0);
        maxEncode(file, x, y);
    }
    return 1;
}

static int mitDecodeStitch(unsigned char value)
{
    if (value & 0x80) {
        return -(value & 0x1F);
    }
    return value;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readMit(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char data[2];

    /* embPattern_loadExternalColorFile(pattern, fileName); TODO: review this and uncomment or remove it */

    while (binaryReadBytes(file, data, 2) == 2) {
        embPattern_addStitchRel(pattern, mitDecodeStitch(data[0]) / 10.0, mitDecodeStitch(data[1]) / 10.0, NORMAL, 1);
    }

    return 1;
}

static unsigned char mitEncodeStitch(double value)
{
    if (value < 0) {
        return 0x80 | (unsigned char)(-value);
    }
    return (unsigned char)value;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeMit(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbStitch st;
    double xx = 0, yy = 0, dx = 0, dy = 0;
    int flags = 0, i;

    embPattern_correctForMaxStitchLength(pattern, 0x1F, 0x1F);
    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        dx = st.x - xx;
        dy = st.y - yy;
        xx = st.x;
        yy = st.y;
        flags = st.flags;
        embFile_putc(mitEncodeStitch(dx), file);
        embFile_putc(mitEncodeStitch(dy), file);
    }
    return 1;
}

static int decodeNewStitch(unsigned char value)
{
    return (int)value;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readNew(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned int stitchCount;
    unsigned char data[3];

    embPattern_loadExternalColorFile(pattern, fileName);
    stitchCount = binaryReadUInt16(file);
    while (binaryReadBytes(file, data, 3) == 3) {
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
        if(val != 0 && data[2] != 0x9B && data[2] != 0x91)
        {
            int z = 1;
        }*/
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flag, 1);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeNew(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeNew */
}

static char* ofmReadLibrary(EmbFile* file)
{
    int stringLength = 0;
    char* libraryName = 0;
    /* FF FE FF */
    unsigned char leadIn[3];

    if (!file) {
        embLog("ERROR: format-ofm.c ofmReadLibrary(), file argument is null\n");
        return 0;
    }

    binaryReadBytes(file, leadIn, 3); /* TODO: check return value */
    stringLength = binaryReadByte(file);
    libraryName = (char*)malloc(sizeof(char) * stringLength * 2);
    if (!libraryName) {
        embLog("ERROR: format-ofm.c ofmReadLibrary(), unable to allocate memory for libraryName\n");
        return 0;
    }
    binaryReadBytes(file, (unsigned char*)libraryName, stringLength * 2); /* TODO: check return value */
    return libraryName;
}

static int ofmReadClass(EmbFile* file)
{
    int len;
    char* s = 0;

    if (!file) {
        embLog("ERROR: format-ofm.c ofmReadClass(), file argument is null\n");
        return 0;
    }

    binaryReadInt16(file);
    len = binaryReadInt16(file);

    s = (char*)malloc(sizeof(char) * len + 1);
    if (!s) {
        embLog("ERROR: format-ofm.c ofmReadClass(), unable to allocate memory for s\n");
        return 0;
    }
    binaryReadBytes(file, (unsigned char*)s, len); /* TODO: check return value */
    s[len] = '\0';
    if (strcmp(s, "CExpStitch") == 0)
        return 0x809C;
    if (strcmp(s, "CColorChange") == 0)
        return 0xFFFF;
    return 0;
}

static void ofmReadBlockHeader(EmbFile* file)
{
    int val1, val2, val3, val4, val5, val6, val7, val8, val9, val10; /* TODO: determine what these represent */
    unsigned char len;
    unsigned short short1;
    char header[512];
    /* TODO: determine what these 3 variables represent */
    short unknown1 = 0;
    short unknown2 = 0;
    int unknown3 = 0;

    if (!file) {
        embLog("ERROR: format-ofm.c ofmReadBlockHeader(), file argument is null\n");
        return;
    }

    embFile_read(header, 1, 14, file);
    unknown1 = EMB_GET_SHORT(header);
    unknown2 = (short)EMB_GET_INT(header+2);
    unknown3 = EMB_GET_INT(header+6);

    /* int v = binaryReadBytes(3); TODO: review */
    len = (unsigned char)(header+13);
    embFile_read(header, 1, 2*len, file);
    /* TODO: check return value here */
    embFile_read(header, 1, 42, file);
    val1 = EMB_GET_INT(header+0); /*  0 */
    val2 = EMB_GET_INT(header+4); /*  0 */
    val3 = EMB_GET_INT(header+8); /*  0 */
    val4 = EMB_GET_INT(header+12); /*  0 */
    val5 = EMB_GET_INT(header+16); /*  1 */
    val6 = EMB_GET_INT(header+20); /*  1 */
    val7 = EMB_GET_INT(header+24); /*  1 */
    val8 = EMB_GET_INT(header+28); /*  0 */
    val9 = EMB_GET_INT(header+32); /* 64 */
    val10 = EMB_GET_INT(header+36); /* 64 */
    short1 = EMB_GET_SHORT(header+40); /*  0 */
}

static void ofmReadColorChange(EmbFile* file, EmbPattern* pattern)
{
    if (!file) {
        embLog("ERROR: format-ofm.c ofmReadColorChange(), file argument is null\n");
        return;
    }
    if (!pattern) {
        embLog("ERROR: format-ofm.c ofmReadColorChange(), pattern argument is null\n");
        return;
    }

    ofmReadBlockHeader(file);
    embPattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
}

static void ofmReadThreads(EmbFile* file, EmbPattern* p)
{
    int i, numberOfColors, stringLen, numberOfLibraries;
    char* primaryLibraryName = 0;
    char* expandedString = 0;

    if (!file) {
        embLog("ERROR: format-ofm.c ofmReadThreads(), file argument is null\n");
        return;
    }
    if (!p) {
        embLog("ERROR: format-ofm.c ofmReadThreads(), p argument is null\n");
        return;
    }

    /* FF FE FF 00 */
    binaryReadInt32(file);

    numberOfColors = binaryReadInt16(file);

    binaryReadInt16(file);
    binaryReadInt16(file);
    stringLen = binaryReadInt16(file);
    expandedString = (char*)malloc(stringLen);
    if (!expandedString) {
        embLog("ERROR: format-ofm.c ofmReadThreads(), unable to allocate memory for expandedString\n");
        return;
    }
    binaryReadBytes(file, (unsigned char*)expandedString, stringLen); /* TODO: check return value */
    for (i = 0; i < numberOfColors; i++) {
        EmbThread thread;
        char colorNumberText[10];
        int threadLibrary = 0, colorNameLength, colorNumber;
        char* colorName = 0;
        int r = binaryReadByte(file);
        int g = binaryReadByte(file);
        int b = binaryReadByte(file);
        binaryReadByte(file);
        threadLibrary = binaryReadInt16(file);
        binaryReadInt16(file);
        colorNumber = binaryReadInt32(file);
        binaryReadByte(file);
        binaryReadInt16(file);
        colorNameLength = binaryReadByte(file);
        colorName = (char*)malloc(colorNameLength * 2);
        if (!colorName) {
            embLog("ERROR: format-ofm.c ofmReadThreads(), unable to allocate memory for colorName\n");
            return;
        }
        binaryReadBytes(file, (unsigned char*)colorName, colorNameLength * 2); /* TODO: check return value */
        binaryReadInt16(file);
        /* itoa(colorNumber, colorNumberText, 10); TODO: never use itoa, it's non-standard, use sprintf: http://stackoverflow.com/questions/5242524/converting-int-to-string-in-c */
        thread.color.r = (unsigned char)r;
        thread.color.g = (unsigned char)g;
        thread.color.b = (unsigned char)b;
        thread.catalogNumber = colorNumberText;
        thread.description = colorName;
        embPattern_addThread(p, thread);
    }
    binaryReadInt16(file);
    primaryLibraryName = ofmReadLibrary(file);
    numberOfLibraries = binaryReadInt16(file);
    for (i = 0; i < numberOfLibraries; i++) {
        /*libraries.Add( TODO: review */
        char* libName = ofmReadLibrary(file);
        free(libName);
        libName = 0;
    }
}

static double ofmDecode(unsigned char b1, unsigned char b2)
{
    double val = (double)(short)(b1 << 8 | b2);
    return val;
}

static void ofmReadExpanded(EmbFile* file, EmbPattern* p)
{
    int i, numberOfStitches = 0;

    if (!file) {
        embLog("ERROR: format-ofm.c ofmReadExpanded(), file argument is null\n");
        return;
    }
    if (!p) {
        embLog("ERROR: format-ofm.c ofmReadExpanded(), p argument is null\n");
        return;
    }

    ofmReadBlockHeader(file);
    numberOfStitches = binaryReadInt32(file);

    for (i = 0; i < numberOfStitches; i++) {
        unsigned char stitch[5];
        binaryReadBytes(file, stitch, 5); /* TODO: check return value */
        if (stitch[0] == 0) {
            embPattern_addStitchAbs(p, ofmDecode(stitch[1], stitch[2]) / 10.0, ofmDecode(stitch[3], stitch[4]) / 10.0, i == 0 ? JUMP : NORMAL, 1);
        } else if (stitch[0] == 32) {
            embPattern_addStitchAbs(p, ofmDecode(stitch[1], stitch[2]) / 10.0, ofmDecode(stitch[3], stitch[4]) / 10.0, i == 0 ? TRIM : NORMAL, 1);
        }
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readOfm(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int unknownCount = 0;
    int key = 0, classNameLength;
    char* s = 0;
    EmbFile* fileCompound = 0;
    bcf_file* bcfFile = 0;

    fileCompound = embFile_open(fileName, "rb", 0);
    if (!fileCompound)
        return 0;

    bcfFile = (bcf_file*)malloc(sizeof(bcf_file));
    if (!bcfFile) {
        embLog("ERROR: format-ofm.c readOfm(), unable to allocate memory for bcfFile\n");
        return 0;
    }
    bcfFile_read(fileCompound, bcfFile);
    file = GetFile(bcfFile, fileCompound, "EdsIV Object");
    bcf_file_free(bcfFile);
    bcfFile = 0;
    embFile_seek(file, 0x1C6, SEEK_SET);
    ofmReadThreads(file, pattern);
    embFile_seek(file, 0x110, SEEK_CUR);
    binaryReadInt32(file);
    classNameLength = binaryReadInt16(file);
    s = (char*)malloc(sizeof(char) * classNameLength);
    if (!s) {
        embLog("ERROR: format-ofm.c readOfm(), unable to allocate memory for s\n");
        return 0;
    }
    binaryReadBytes(file, (unsigned char*)s, classNameLength); /* TODO: check return value */
    unknownCount = binaryReadInt16(file); /* TODO: determine what unknown count represents */

    binaryReadInt16(file);
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
        key = binaryReadUInt16(file);
        if (key == 0xFFFF) {
            ofmReadClass(file);
        }
    }

    embFile_close(fileCompound);

    embPattern_flip(pattern, 1, 1);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeOfm(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeOfm */
}

static double pcdDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res)&0x7FFFFF) - 1));
    }
    return res;
}

static void pcdEncode(EmbFile* file, int dx, int dy, int flags)
{
    unsigned char flagsToWrite = 0;

    if (!file) {
        embLog("ERROR: format-pcd.c pcdEncode(), file argument is null\n");
        return;
    }

    binaryWriteByte(file, (unsigned char)0);
    binaryWriteByte(file, (unsigned char)(dx & 0xFF));
    binaryWriteByte(file, (unsigned char)((dx >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((dx >> 16) & 0xFF));

    binaryWriteByte(file, (unsigned char)0);
    binaryWriteByte(file, (unsigned char)(dy & 0xFF));
    binaryWriteByte(file, (unsigned char)((dy >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((dy >> 16) & 0xFF));
    if (flags & STOP) {
        flagsToWrite |= 0x01;
    }
    if (flags & TRIM) {
        flagsToWrite |= 0x04;
    }
    binaryWriteByte(file, flagsToWrite);
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readPcd(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char allZeroColor = 1;
    int i;
    unsigned char b[9];
    double dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount = 0;

    version = binaryReadByte(file);
    hoopSize = binaryReadByte(file); /* 0 for PCD, 1 for PCQ (MAXI), 2 for PCS with small hoop(80x80), */
    /* and 3 for PCS with large hoop (115x120) */
    colorCount = binaryReadUInt16(file);

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        t.color.r = (unsigned char)embFile_getc(file);
        t.color.g = (unsigned char)embFile_getc(file);
        t.color.b = (unsigned char)embFile_getc(file);
        t.catalogNumber = "";
        t.description = "";
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        embPattern_addThread(pattern, t);
        embFile_getc(file);
    }
    if (allZeroColor)
        embPattern_loadExternalColorFile(pattern, fileName);
    st = binaryReadUInt16(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        flags = NORMAL;
        if (embFile_read(b, 1, 9, file) != 9)
            break;

        if (b[8] & 0x01) {
            flags = STOP;
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pcdDecode(b[1], b[2], b[3]);
        dy = pcdDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writePcd(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbStitch st;
    int i;
    unsigned char colorCount;
    double xx = 0.0, yy = 0.0;

    binaryWriteByte(file, (unsigned char)'2');
    binaryWriteByte(file, 3); /* TODO: select hoop size defaulting to Large PCS hoop */
    colorCount = (unsigned char)pattern->threads->count;
    binaryWriteUShort(file, (unsigned short)colorCount);
    for (i = 0; i < pattern->threads->count; i++) {
        EmbColor color = pattern->threads->thread[i].color;
        binaryWriteByte(file, color.r);
        binaryWriteByte(file, color.g);
        binaryWriteByte(file, color.b);
        binaryWriteByte(file, 0);
    }

    for (; i < 16; i++) {
        binaryWriteUInt(file, 0); /* write remaining colors to reach 16 */
    }

    binaryWriteUShort(file, (unsigned short)pattern->stitchList->count);
    /* write stitches */
    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        pcdEncode(file, roundDouble(st.x * 10.0), roundDouble(st.y * 10.0), st.flags);
    }
    return 1;
}

static const int pcmThreadCount = 65;
static const EmbThread pcmThreads[] = {
    { { 0x00, 0x00, 0x00 }, "PCM Color 1", "" },
    { { 0x00, 0x00, 0x80 }, "PCM Color 2", "" },
    { { 0x00, 0x00, 0xFF }, "PCM Color 3", "" },
    { { 0x00, 0x80, 0x80 }, "PCM Color 4", "" },
    { { 0x00, 0xFF, 0xFF }, "PCM Color 5", "" },
    { { 0x80, 0x00, 0x80 }, "PCM Color 6", "" },
    { { 0xFF, 0x00, 0xFF }, "PCM Color 7", "" },
    { { 0x80, 0x00, 0x00 }, "PCM Color 8", "" },
    { { 0xFF, 0x00, 0x00 }, "PCM Color 9", "" },
    { { 0x00, 0x80, 0x00 }, "PCM Color 10", "" },
    { { 0x00, 0xFF, 0x00 }, "PCM Color 11", "" },
    { { 0x80, 0x80, 0x00 }, "PCM Color 12", "" },
    { { 0xFF, 0xFF, 0x00 }, "PCM Color 13", "" },
    { { 0x80, 0x80, 0x80 }, "PCM Color 14", "" },
    { { 0xC0, 0xC0, 0xC0 }, "PCM Color 15", "" },
    { { 0xFF, 0xFF, 0xFF }, "PCM Color 16", "" }
};

static double pcmDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res)&0x7FFFFF) - 1));
    }
    return res;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readPcm(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i = 0;
    unsigned char b[9];
    double dx = 0, dy = 0;
    int flags = 0, st = 0;

    embFile_seek(file, 4, SEEK_SET);

    for (i = 0; i < 16; i++) {
        int colorNumber;
        (void)embFile_getc(file); /* zero */
        colorNumber = embFile_getc(file);
        embPattern_addThread(pattern, pcmThreads[colorNumber]);
    }
    st = binaryReadUInt16BE(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        flags = NORMAL;
        if (embFile_read(b, 1, 9, file) != 9)
            break;

        if (b[8] & 0x01) {
            flags = STOP;
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pcmDecode(b[2], b[1], b[0]);
        dy = pcmDecode(b[6], b[5], b[4]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writePcm(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writePcm */
}

static double pcqDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res)&0x7FFFFF) - 1));
    }
    return res;
}

static void pcqEncode(EmbFile* file, int dx, int dy, int flags)
{
    unsigned char flagsToWrite = 0;

    if (!file) {
        embLog("ERROR: format-pcq.c pcqEncode(), file argument is null\n");
        return;
    }

    binaryWriteByte(file, (unsigned char)0);
    binaryWriteByte(file, (unsigned char)(dx & 0xFF));
    binaryWriteByte(file, (unsigned char)((dx >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((dx >> 16) & 0xFF));

    binaryWriteByte(file, (unsigned char)0);
    binaryWriteByte(file, (unsigned char)(dy & 0xFF));
    binaryWriteByte(file, (unsigned char)((dy >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((dy >> 16) & 0xFF));
    if (flags & STOP) {
        flagsToWrite |= 0x01;
    }
    if (flags & TRIM) {
        flagsToWrite |= 0x04;
    }
    binaryWriteByte(file, flagsToWrite);
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readPcq(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    double dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount;
    EmbThread t;

    version = binaryReadByte(file);
    hoopSize = binaryReadByte(file);
    /* 0 for PCD, 1 for PCQ (MAXI), 2 for PCS with small hoop(80x80), */
    /* and 3 for PCS with large hoop (115x120) */
    colorCount = binaryReadUInt16(file);

    for (i = 0; i < colorCount; i++) {
        embFile_read(b, 1, 4, file);
        t.color = embColor_fromStr(b);
        t.catalogNumber = "";
        t.description = "";
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        embPattern_addThread(pattern, t);
    }
    if (allZeroColor)
        embPattern_loadExternalColorFile(pattern, fileName);
    st = binaryReadUInt16(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        flags = NORMAL;
        if (embFile_read(b, 1, 9, file) != 9)
            break;

        if (b[8] & 0x01) {
            flags = STOP;
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pcqDecode(b[1], b[2], b[3]);
        dy = pcqDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writePcq(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbStitch st;
    unsigned char colorCount, b[4], i;

    binaryWriteByte(file, (unsigned char)'2');
    binaryWriteByte(file, 3);
    /* TODO: select hoop size defaulting to Large PCS hoop */
    colorCount = (unsigned char)pattern->threads->count;
    binaryWriteUShort(file, (unsigned short)colorCount);
    b[3] = 0;
    for (i = 0; i < 16; i++) {
        /* If there are threads remaining, write them,
         * else, repeat the last color to 16. */
        if (i < pattern->threads->count) {
            embColor_toStr(pattern->threads->thread[i].color, b);
        }
        embFile_write(b, 1, 4, file);
    }

    binaryWriteUShort(file, (unsigned short)pattern->stitchList->count);
    /* write stitches */
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        pcqEncode(file, roundDouble(st.x * 10.0), roundDouble(st.y * 10.0), st.flags);
    }
    return 1;
}

static double pcsDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res)&0x7FFFFF) - 1));
    }
    return res;
}

static void pcsEncode(EmbFile* file, int dx, int dy, int flags)
{
    unsigned char flagsToWrite = 0;

    if (!file) {
        embLog("ERROR: format-pcs.c pcsEncode(), file argument is null\n");
        return;
    }

    binaryWriteByte(file, (unsigned char)0);
    binaryWriteByte(file, (unsigned char)(dx & 0xFF));
    binaryWriteByte(file, (unsigned char)((dx >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((dx >> 16) & 0xFF));

    binaryWriteByte(file, (unsigned char)0);
    binaryWriteByte(file, (unsigned char)(dy & 0xFF));
    binaryWriteByte(file, (unsigned char)((dy >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((dy >> 16) & 0xFF));
    if (flags & STOP) {
        flagsToWrite |= 0x01;
    }
    if (flags & TRIM) {
        flagsToWrite |= 0x04;
    }
    binaryWriteByte(file, flagsToWrite);
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readPcs(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    double dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount;

    version = binaryReadByte(file);
    hoopSize = binaryReadByte(file); /* 0 for PCD, 1 for PCQ (MAXI), 2 for PCS with small hoop(80x80), */
    /* and 3 for PCS with large hoop (115x120) */

    switch (hoopSize) {
    case 2:
        pattern->hoop.width = 80.0;
        pattern->hoop.height = 80.0;
        break;
    case 3:
        pattern->hoop.width = 115;
        pattern->hoop.height = 120.0;
        break;
    }

    colorCount = binaryReadUInt16(file);

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        t.catalogNumber = "";
        t.description = "";
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        embPattern_addThread(pattern, t);
        binaryReadByte(file);
    }
    if (allZeroColor)
        embPattern_loadExternalColorFile(pattern, fileName);
    st = binaryReadUInt16(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        flags = NORMAL;
        if (embFile_read(b, 1, 9, file) != 9)
            break;

        if (b[8] & 0x01) {
            flags = STOP;
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pcsDecode(b[1], b[2], b[3]);
        dy = pcsDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writePcs(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbStitch st;
    int i = 0;
    unsigned char colorCount = 0;

    binaryWriteByte(file, (unsigned char)'2');
    binaryWriteByte(file, 3); /* TODO: select hoop size defaulting to Large PCS hoop */
    colorCount = (unsigned char)pattern->threads->count;
    binaryWriteUShort(file, (unsigned short)colorCount);
    for (i = 0; i < colorCount; i++) {
        EmbColor color = pattern->threads->thread[i].color;
        binaryWriteByte(file, color.r);
        binaryWriteByte(file, color.g);
        binaryWriteByte(file, color.b);
        binaryWriteByte(file, 0);
    }

    for (; i < 16; i++) {
        binaryWriteUInt(file, 0); /* write remaining colors to reach 16 */
    }

    binaryWriteUShort(file, (unsigned short)pattern->stitchList->count);
    /* write stitches */
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        pcsEncode(file, roundDouble(st.x * 10.0), roundDouble(st.y * 10.0), st.flags);
    }
    return 1;
}

static const int pecThreadCount = 65;
static const EmbThread pecThreads[] = {
    { { 0, 0, 0 }, "Unknown", "" }, /* Index  0 */
    { { 14, 31, 124 }, "Prussian Blue", "" }, /* Index  1 */
    { { 10, 85, 163 }, "Blue", "" }, /* Index  2 */
    { { 0, 135, 119 }, "Teal Green", "" }, /* Index  3 */ /* TODO: Verify RGB value is correct */
    { { 75, 107, 175 }, "Cornflower Blue", "" }, /* Index  4 */
    { { 237, 23, 31 }, "Red", "" }, /* Index  5 */
    { { 209, 92, 0 }, "Reddish Brown", "" }, /* Index  6 */
    { { 145, 54, 151 }, "Magenta", "" }, /* Index  7 */
    { { 228, 154, 203 }, "Light Lilac", "" }, /* Index  8 */
    { { 145, 95, 172 }, "Lilac", "" }, /* Index  9 */
    { { 158, 214, 125 }, "Mint Green", "" }, /* Index 10 */ /* TODO: Verify RGB value is correct */
    { { 232, 169, 0 }, "Deep Gold", "" }, /* Index 11 */
    { { 254, 186, 53 }, "Orange", "" }, /* Index 12 */
    { { 255, 255, 0 }, "Yellow", "" }, /* Index 13 */
    { { 112, 188, 31 }, "Lime Green", "" }, /* Index 14 */
    { { 186, 152, 0 }, "Brass", "" }, /* Index 15 */
    { { 168, 168, 168 }, "Silver", "" }, /* Index 16 */
    { { 125, 111, 0 }, "Russet Brown", "" }, /* Index 17 */ /* TODO: Verify RGB value is correct */
    { { 255, 255, 179 }, "Cream Brown", "" }, /* Index 18 */
    { { 79, 85, 86 }, "Pewter", "" }, /* Index 19 */
    { { 0, 0, 0 }, "Black", "" }, /* Index 20 */
    { { 11, 61, 145 }, "Ultramarine", "" }, /* Index 21 */
    { { 119, 1, 118 }, "Royal Purple", "" }, /* Index 22 */
    { { 41, 49, 51 }, "Dark Gray", "" }, /* Index 23 */
    { { 42, 19, 1 }, "Dark Brown", "" }, /* Index 24 */
    { { 246, 74, 138 }, "Deep Rose", "" }, /* Index 25 */
    { { 178, 118, 36 }, "Light Brown", "" }, /* Index 26 */
    { { 252, 187, 197 }, "Salmon Pink", "" }, /* Index 27 */ /* TODO: Verify RGB value is correct */
    { { 254, 55, 15 }, "Vermillion", "" }, /* Index 28 */
    { { 240, 240, 240 }, "White", "" }, /* Index 29 */
    { { 106, 28, 138 }, "Violet", "" }, /* Index 30 */
    { { 168, 221, 196 }, "Seacrest", "" }, /* Index 31 */
    { { 37, 132, 187 }, "Sky Blue", "" }, /* Index 32 */
    { { 254, 179, 67 }, "Pumpkin", "" }, /* Index 33 */
    { { 255, 243, 107 }, "Cream Yellow", "" }, /* Index 34 */
    { { 208, 166, 96 }, "Khaki", "" }, /* Index 35 */
    { { 209, 84, 0 }, "Clay Brown", "" }, /* Index 36 */
    { { 102, 186, 73 }, "Leaf Green", "" }, /* Index 37 */
    { { 19, 74, 70 }, "Peacock Blue", "" }, /* Index 38 */
    { { 135, 135, 135 }, "Gray", "" }, /* Index 39 */
    { { 216, 204, 198 }, "Warm Gray", "" }, /* Index 40 */ /* TODO: Verify RGB value is correct */
    { { 67, 86, 7 }, "Dark Olive", "" }, /* Index 41 */
    { { 253, 217, 222 }, "Flesh Pink", "" }, /* Index 42 */ /* TODO: Verify RGB value is correct */
    { { 249, 147, 188 }, "Pink", "" }, /* Index 43 */
    { { 0, 56, 34 }, "Deep Green", "" }, /* Index 44 */
    { { 178, 175, 212 }, "Lavender", "" }, /* Index 45 */
    { { 104, 106, 176 }, "Wisteria Violet", "" }, /* Index 46 */
    { { 239, 227, 185 }, "Beige", "" }, /* Index 47 */
    { { 247, 56, 102 }, "Carmine", "" }, /* Index 48 */
    { { 181, 75, 100 }, "Amber Red", "" }, /* Index 49 */ /* TODO: Verify RGB value is correct */
    { { 19, 43, 26 }, "Olive Green", "" }, /* Index 50 */
    { { 199, 1, 86 }, "Dark Fuschia", "" }, /* Index 51 */ /* TODO: Verify RGB value is correct */
    { { 254, 158, 50 }, "Tangerine", "" }, /* Index 52 */
    { { 168, 222, 235 }, "Light Blue", "" }, /* Index 53 */
    { { 0, 103, 62 }, "Emerald Green", "" }, /* Index 54 */ /* TODO: Verify RGB value is correct */
    { { 78, 41, 144 }, "Purple", "" }, /* Index 55 */
    { { 47, 126, 32 }, "Moss Green", "" }, /* Index 56 */
    { { 255, 204, 204 }, "Flesh Pink", "" }, /* Index 57 */ /* TODO: Verify RGB value is correct */ /* TODO: Flesh Pink is Index 42, is this Index incorrect? */
    { { 255, 217, 17 }, "Harvest Gold", "" }, /* Index 58 */
    { { 9, 91, 166 }, "Electric Blue", "" }, /* Index 59 */
    { { 240, 249, 112 }, "Lemon Yellow", "" }, /* Index 60 */
    { { 227, 243, 91 }, "Fresh Green", "" }, /* Index 61 */
    { { 255, 153, 0 }, "Orange", "" }, /* Index 62 */ /* TODO: Verify RGB value is correct */ /* TODO: Orange is Index 12, is this Index incorrect? */
    { { 255, 240, 141 }, "Cream Yellow", "" }, /* Index 63 */ /* TODO: Verify RGB value is correct */ /* TODO: Cream Yellow is Index 34, is this Index incorrect? */
    { { 255, 200, 200 }, "Applique", "" } /* Index 64 */
};

static const char imageWithFrame[38][48] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void readPecStitches(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int stitchNumber = 0;

    if (!pattern) {
        embLog("ERROR: format-pec.c readPecStitches(), pattern argument is null\n");
        return;
    }
    if (!file) {
        embLog("ERROR: format-pec.c readPecStitches(), file argument is null\n");
        return;
    }

    while (!embFile_eof(file)) {
        int val1 = (int)binaryReadUInt8(file);
        int val2 = (int)binaryReadUInt8(file);

        int stitchType = NORMAL;
        if (val1 == 0xFF && val2 == 0x00) {
            embPattern_addStitchRel(pattern, 0.0, 0.0, END, 1);
            break;
        }
        if (val1 == 0xFE && val2 == 0xB0) {
            (void)binaryReadByte(file);
            embPattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
            stitchNumber++;
            continue;
        }
        /* High bit set means 12-bit offset, otherwise 7-bit signed delta */
        if (val1 & 0x80) {
            if (val1 & 0x20)
                stitchType = TRIM;
            if (val1 & 0x10)
                stitchType = JUMP;
            val1 = ((val1 & 0x0F) << 8) + val2;

            /* Signed 12-bit arithmetic */
            if (val1 & 0x800) {
                val1 -= 0x1000;
            }

            val2 = binaryReadUInt8(file);
        } else if (val1 >= 0x40) {
            val1 -= 0x80;
        }
        if (val2 & 0x80) {
            if (val2 & 0x20)
                stitchType = TRIM;
            if (val2 & 0x10)
                stitchType = JUMP;
            val2 = ((val2 & 0x0F) << 8) + binaryReadUInt8(file);

            /* Signed 12-bit arithmetic */
            if (val2 & 0x800) {
                val2 -= 0x1000;
            }
        } else if (val2 >= 0x40) {
            val2 -= 0x80;
        }
        embPattern_addStitchRel(pattern, val1 / 10.0, val2 / 10.0, stitchType, 1);
        stitchNumber++;
    }
}

static void pecEncodeJump(EmbFile* file, int x, int types)
{
    int outputVal = abs(x) & 0x7FF;
    unsigned int orPart = 0x80;

    if (!file) {
        embLog("ERROR: format-pec.c pecEncodeJump(), file argument is null\n");
        return;
    }

    if (types & TRIM) {
        orPart |= 0x20;
    }
    if (types & JUMP) {
        orPart |= 0x10;
    }

    if (x < 0) {
        outputVal = x + 0x1000 & 0x7FF;
        outputVal |= 0x800;
    }
    binaryWriteByte(file, (unsigned char)(((outputVal >> 8) & 0x0F) | orPart));
    binaryWriteByte(file, (unsigned char)(outputVal & 0xFF));
}

static void pecEncodeStop(EmbFile* file, unsigned char val)
{
    if (!file) {
        embLog("ERROR: format-pec.c pecEncodeStop(), file argument is null\n");
        return;
    }
    binaryWriteByte(file, 0xFE);
    binaryWriteByte(file, 0xB0);
    binaryWriteByte(file, val);
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readPec(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned int graphicsOffset;
    unsigned char colorChanges;
    int i;

    embFile_seek(file, 0x38, SEEK_SET);
    colorChanges = (unsigned char)binaryReadByte(file);
    for (i = 0; i <= colorChanges; i++) {
        embPattern_addThread(pattern, pecThreads[binaryReadByte(file) % 65]);
    }

    /* Get Graphics offset */
    embFile_seek(file, 0x20A, SEEK_SET);

    graphicsOffset = (unsigned int)(binaryReadUInt8(file));
    graphicsOffset |= (binaryReadUInt8(file) << 8);
    graphicsOffset |= (binaryReadUInt8(file) << 16);

    (void)binaryReadByte(file); /* 0x31 */
    (void)binaryReadByte(file); /* 0xFF */
    (void)binaryReadByte(file); /* 0xF0 */
    /* Get X and Y size in .1 mm */
    /* 0x210 */
    binaryReadInt16(file); /* x size */
    binaryReadInt16(file); /* y size */

    binaryReadInt16(file); /* 0x01E0 */
    binaryReadInt16(file); /* 0x01B0 */
    binaryReadInt16(file); /* distance left from start */
    binaryReadInt16(file); /* distance up from start */

    /* Begin Stitch Data */
    /* 0x21C */
    /*unsigned int end = graphicsOffset + 0x208; */
    readPecStitches(pattern, file, fileName);

    embPattern_flipVertical(pattern);

    return 1;
}

static void pecEncode(EmbFile* file, EmbPattern* p)
{
    double thisX = 0.0;
    double thisY = 0.0;
    unsigned char stopCode = 2;
    EmbStitch s;
    int deltaX, deltaY, i;

    for (i = 0; i < p->stitchList->count; i++) {
        s = p->stitchList->stitch[i];

        deltaX = roundDouble(s.x - thisX);
        deltaY = roundDouble(s.y - thisY);
        thisX += (double)deltaX;
        thisY += (double)deltaY;

        if (s.flags & STOP) {
            pecEncodeStop(file, stopCode);
            if (stopCode == (unsigned char)2) {
                stopCode = (unsigned char)1;
            } else {
                stopCode = (unsigned char)2;
            }
        } else if (s.flags & END) {
            binaryWriteByte(file, 0xFF);
            break;
        } else if (deltaX < 63 && deltaX > -64 && deltaY < 63 && deltaY > -64 && (!(s.flags & (JUMP | TRIM)))) {
            binaryWriteByte(file, (deltaX < 0) ? (unsigned char)(deltaX + 0x80) : (unsigned char)deltaX);
            binaryWriteByte(file, (deltaY < 0) ? (unsigned char)(deltaY + 0x80) : (unsigned char)deltaY);
        } else {
            pecEncodeJump(file, deltaX, s.flags);
            pecEncodeJump(file, deltaY, s.flags);
        }
    }
}

static void clearImage(unsigned char image[][48])
{
    memcpy(image, imageWithFrame, 48 * 38);
}

static void writeImage(EmbFile* file, unsigned char image[][48])
{
    int i, j;

    if (!file) {
        embLog("ERROR: format-pec.c writeImage(), file argument is null\n");
        return;
    }

    for (i = 0; i < 38; i++) {
        for (j = 0; j < 6; j++) {
            int offset = j * 8;
            unsigned char output = 0;
            output |= (unsigned char)(image[i][offset] != 0);
            output |= (unsigned char)(image[i][offset + 1] != (unsigned char)0) << 1;
            output |= (unsigned char)(image[i][offset + 2] != (unsigned char)0) << 2;
            output |= (unsigned char)(image[i][offset + 3] != (unsigned char)0) << 3;
            output |= (unsigned char)(image[i][offset + 4] != (unsigned char)0) << 4;
            output |= (unsigned char)(image[i][offset + 5] != (unsigned char)0) << 5;
            output |= (unsigned char)(image[i][offset + 6] != (unsigned char)0) << 6;
            output |= (unsigned char)(image[i][offset + 7] != (unsigned char)0) << 7;
            binaryWriteByte(file, output);
        }
    }
}

void writePecStitches(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbStitch st;
    EmbRect bounds;
    unsigned char image[38][48];
    int i, flen, currentThreadCount, graphicsOffsetLocation, graphicsOffsetValue, height, width;
    double xFactor, yFactor;
    const char* forwardSlashPos = strrchr(fileName, '/');
    const char* backSlashPos = strrchr(fileName, '\\');
    const char* dotPos = strrchr(fileName, '.');
    const char* start = 0;

    if (forwardSlashPos) {
        start = forwardSlashPos + 1;
    }
    if (backSlashPos && backSlashPos > start) {
        start = backSlashPos + 1;
    }
    if (!start) {
        start = fileName;
    }
    binaryWriteBytes(file, "LA:", 3);
    flen = (int)(dotPos - start);

    while (start < dotPos) {
        binaryWriteByte(file, (unsigned char)*start);
        start++;
    }
    for (i = 0; i < (int)(16 - flen); i++) {
        binaryWriteByte(file, (unsigned char)0x20);
    }
    binaryWriteByte(file, 0x0D);
    for (i = 0; i < 12; i++) {
        binaryWriteByte(file, (unsigned char)0x20);
    }
    binaryWriteByte(file, (unsigned char)0xFF);
    binaryWriteByte(file, (unsigned char)0x00);
    binaryWriteByte(file, (unsigned char)0x06);
    binaryWriteByte(file, (unsigned char)0x26);

    for (i = 0; i < 12; i++) {
        binaryWriteByte(file, (unsigned char)0x20);
    }
    currentThreadCount = pattern->threads->count;
    binaryWriteByte(file, (unsigned char)(currentThreadCount - 1));

    for (i = 0; i < currentThreadCount; i++) {
        binaryWriteByte(file, (unsigned char)embThread_findNearestColor_fromThread(pattern->threads->thread[i].color, (EmbThread*)pecThreads, pecThreadCount));
    }
    for (i = 0; i < (int)(0x1CF - currentThreadCount); i++) {
        binaryWriteByte(file, (unsigned char)0x20);
    }
    binaryWriteShort(file, (short)0x0000);

    graphicsOffsetLocation = embFile_tell(file);
    /* placeholder bytes to be overwritten */
    binaryWriteByte(file, (unsigned char)0x00);
    binaryWriteByte(file, (unsigned char)0x00);
    binaryWriteByte(file, (unsigned char)0x00);

    binaryWriteByte(file, (unsigned char)0x31);
    binaryWriteByte(file, (unsigned char)0xFF);
    binaryWriteByte(file, (unsigned char)0xF0);

    bounds = embPattern_calcBoundingBox(pattern);

    height = roundDouble(embRect_height(bounds));
    width = roundDouble(embRect_width(bounds));
    /* write 2 byte x size */
    binaryWriteShort(file, (short)width);
    /* write 2 byte y size */
    binaryWriteShort(file, (short)height);

    /* Write 4 miscellaneous int16's */
    binaryWriteShort(file, (short)0x1E0);
    binaryWriteShort(file, (short)0x1B0);

    binaryWriteUShortBE(file, (unsigned short)(0x9000 | -roundDouble(bounds.left)));
    binaryWriteUShortBE(file, (unsigned short)(0x9000 | -roundDouble(bounds.top)));

    pecEncode(file, pattern);
    graphicsOffsetValue = embFile_tell(file) - graphicsOffsetLocation + 2;
    embFile_seek(file, graphicsOffsetLocation, SEEK_SET);

    binaryWriteByte(file, (unsigned char)(graphicsOffsetValue & 0xFF));
    binaryWriteByte(file, (unsigned char)((graphicsOffsetValue >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((graphicsOffsetValue >> 16) & 0xFF));

    embFile_seek(file, 0x00, SEEK_END);

    /* Writing all colors */
    clearImage(image);

    int x, y;
    yFactor = 32.0 / height;
    xFactor = 42.0 / width;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        x = roundDouble((st.x - bounds.left) * xFactor) + 3;
        y = roundDouble((st.y - bounds.top) * yFactor) + 3;
        image[y][x] = 1;
    }
    writeImage(file, image);

    /* Writing each individual color */
    for (i = 0; i < currentThreadCount; i++) {
        clearImage(image);
        for (i = 0; i < pattern->stitchList->count; i++) {
            st = pattern->stitchList->stitch[i];
            x = roundDouble((st.x - bounds.left) * xFactor) + 3;
            y = roundDouble((st.y - bounds.top) * yFactor) + 3;
            if (st.flags & STOP) {
                break;
            }
            image[y][x] = 1;
        }
        writeImage(file, image);
    }
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writePec(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    embPattern_flipVertical(pattern); /* TODO: There needs to be a matching flipVertical() call after the write to ensure multiple writes from the same pattern work properly */
    embPattern_fixColorCount(pattern);
    embPattern_correctForMaxStitchLength(pattern, 12.7, 204.7);
    embPattern_scale(pattern, 10.0);

    binaryWriteBytes(file, "#PEC0001", 8);

    writePecStitches(pattern, file, fileName);

    return 1;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readPel(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish readPel */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writePel(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writePel */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readPem(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish ReadPem */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writePem(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writePem */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readPes(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int pecstart, numColors, x;

    embFile_seek(file, 8, SEEK_SET);
    pecstart = binaryReadInt32(file);

    embFile_seek(file, pecstart + 48, SEEK_SET);
    numColors = embFile_getc(file) + 1;
    for (x = 0; x < numColors; x++) {
        embPattern_addThread(pattern, pecThreads[(unsigned char)embFile_getc(file)]);
    }

    embFile_seek(file, pecstart + 532, SEEK_SET);
    readPecStitches(pattern, file, fileName);

    embPattern_flipVertical(pattern);

    return 1;
}

/* static void readPESHeader(EmbFile* file, EmbPattern* pattern) {
       char* signature = readString(8);
            if(strcmp(signature, "#PES0100") {
                readPESHeaderV10();
            } else if(strcmp(signature, "#PES0090") {
                readPESHeaderV9();
            } else if(strcmp(signature, "#PES0080") {
                readPESHeaderV8();
            } else if(strcmp(signature, "#PES0070") {
                readPESHeaderV7();
            } else if(strcmp(signature, "#PES0060") {
                readPESHeaderV6();
            } else if(strcmp(signature, "#PES0056"){
                readPESHeaderV5();
            } else if(strcmp(signature, "#PES0055") {
               readPESHeaderV5();
                 } else if(strcmp(signature, "#PES0050") {
                readPESHeaderV5();
                 } else if(strcmp(signature, "#PES0040") {
                readPESHeaderV4();
                 } else if(strcmp(signature, "#PES0030") {
                readPESHeaderDefault();
                 } else if(strcmp(signature, "#PES0022") {
                readPESHeaderDefault();
                 } else if(strcmp(signature, "#PES0020") {
                readPESHeaderDefault();
                 } else if(strcmp(signature, "#PES0001") {
                readPESHeaderDefault();
                 } else
            if(strcmp(signature, "#PEC0001") {
                //PEC needs to go straight to reading, no default.
            } else {
                readPESHeaderDefault();
            }
        }
    }

static void readPESHeaderDefault()  {
    int pecStart = readInt32LE();
    skip(pecStart - readPosition);
}

    static void readDescriptions()  {
        int DesignStringLength = readInt8();
        String DesignName = readString(DesignStringLength);
        pattern.setName(DesignName);
        int categoryStringLength = readInt8();
        String Category = readString(categoryStringLength);
        pattern.setCategory(Category);
        int authorStringLength = readInt8();
        String Author = readString(authorStringLength);
        pattern.setAuthor(Author);
        int keywordsStringLength = readInt8();
        String keywords = readString(keywordsStringLength);
        pattern.setKeywords(keywords);
        int commentsStringLength = readInt8();
        String Comments = readString(commentsStringLength);
        pattern.setComments(Comments);
    }

    static void readPESHeaderV4()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(pecStart - readPosition);
    }

    static void readPESHeaderV5()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(24);//36 v6
        int fromImageStringLength = readInt8();
        skip(fromImageStringLength);
        skip(24);
        int numberOfProgrammableFillPatterns = readInt16LE();
        if (numberOfProgrammableFillPatterns != 0) {
            seek(pecStart);
            return;
        }
        int numberOfMotifPatterns = readInt16LE();
        if (numberOfMotifPatterns != 0) {
            seek(pecStart);
            return;
        }
        int featherPatternCount = readInt16LE();
        if (featherPatternCount != 0) {
            seek(pecStart);
            return;
        }
        int numberOfColors = readInt16LE();
        for (int i = 0; i < numberOfColors; i++) {
            readThread();
        }
        seek(pecStart);
    }

    static void readPESHeaderV6()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(36);
        int fromImageStringLength = readInt8();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(24);
        int numberOfProgrammableFillPatterns = readInt16LE();
        if (numberOfProgrammableFillPatterns != 0) {
            seek(pecStart);
            return;
        }
        int numberOfMotifPatterns = readInt16LE();
        if (numberOfMotifPatterns != 0) {
            seek(pecStart);
            return;
        }
        int featherPatternCount = readInt16LE();
        if (featherPatternCount != 0) {
            seek(pecStart);
            return;
        }
        int numberOfColors = readInt16LE();
        for (int i = 0; i < numberOfColors; i++) {
            readThread();
        }
        seek(pecStart);
    }
    
    static void readPESHeaderV7()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(36);
        int fromImageStringLength = readInt8();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(24);
        int numberOfProgrammableFillPatterns = readInt16LE();
        if (numberOfProgrammableFillPatterns != 0) {
            seek(pecStart);
            return;
        }
        int numberOfMotifPatterns = readInt16LE();
        if (numberOfMotifPatterns != 0) {
            seek(pecStart);
            return;
        }
        int featherPatternCount = readInt16LE();
        if (featherPatternCount != 0) {
            seek(pecStart);
            return;
        }
        int numberOfColors = readInt16LE();
        for (int i = 0; i < numberOfColors; i++) {
            readThread();
        }
        seek(pecStart);
    }
    
    static void readPESHeaderV8()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(38);
        int fromImageStringLength = readInt8();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(26);
        int numberOfProgrammableFillPatterns = readInt16LE();
        if (numberOfProgrammableFillPatterns != 0) {
            seek(pecStart);
            return;
        }
        int numberOfMotifPatterns = readInt16LE();
        if (numberOfMotifPatterns != 0) {
            seek(pecStart);
            return;
        }
        int featherPatternCount = readInt16LE();
        if (featherPatternCount != 0) {
            seek(pecStart);
            return;
        }
        int numberOfColors = readInt16LE();
        for (int i = 0; i < numberOfColors; i++) {
            readThread();
        }
        seek(pecStart);
    }

    static void readPESHeaderV9()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(14);
        int hoopNameStringLength = readInt8();
        String hoopNameString = readString(hoopNameStringLength);
        if (hoopNameString.length() != 0) {
            pattern.setMetadata("hoop_name", hoopNameString);
        }
        skip(30);
        int fromImageStringLength = readInt8();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(34);
        int numberOfProgrammableFillPatterns = readInt16LE();
        if (numberOfProgrammableFillPatterns != 0) {
            seek(pecStart);
            return;
        }
        int numberOfMotifPatterns = readInt16LE();
        if (numberOfMotifPatterns != 0) {
            seek(pecStart);
            return;
        }
        int featherPatternCount = readInt16LE();
        if (featherPatternCount != 0) {
            seek(pecStart);
            return;
        }
        int numberOfColors = readInt16LE();
        for (int i = 0; i < numberOfColors; i++) {
            readThread();
        }
        seek(pecStart);
    }

    static void readPESHeaderV10()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(14);
        int hoopNameStringLength = readInt8();
        String hoopNameString = readString(hoopNameStringLength);
        if (hoopNameString.length() != 0) {
            pattern.setMetadata("hoop_name", hoopNameString);
        }
        skip(38);
        int fromImageStringLength = readInt8();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(34);
        int numberOfProgrammableFillPatterns = readInt16LE();
        if (numberOfProgrammableFillPatterns != 0) {
            seek(pecStart);
            return;
        }
        int numberOfMotifPatterns = readInt16LE();
        if (numberOfMotifPatterns != 0) {
            seek(pecStart);
            return;
        }
        int featherPatternCount = readInt16LE();
        if (featherPatternCount != 0) {
            seek(pecStart);
            return;
        }
        int numberOfColors = readInt16LE();
        for (int i = 0; i < numberOfColors; i++) {
            readThread();
        }
        seek(pecStart);
    }
    
    static void readThread() {
        int color_code_length = readInt8();
        String color_code = readString(color_code_length);
        int red = readInt8();
        int green = readInt8();
        int blue = readInt8();
        skip(5);
        int descriptionStringLength = readInt8();
        String description = readString(descriptionStringLength);

        int brandStringLength = readInt8();
        String brand = readString(brandStringLength);

        int threadChartStringLength = readInt8();
        String threadChart = readString(threadChartStringLength);

        int color = (red & 0xFF) << 16 | (green & 0xFF) << 8 | (blue & 0xFF);
        pattern.add(new EmbThread(color, description, color_code, brand, threadChart));
    }
*/
static void pesWriteSewSegSection(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    /* TODO: pointer safety */
    short* colorInfo = 0;
    int flag = 0;
    int count = 0;
    int colorCode = -1;
    int stitchType = 0;
    int blockCount = 0;
    int colorCount = 0;
    int newColorCode = 0;
    int colorInfoIndex = 0;
    int i;
    EmbRect bounds = embPattern_calcBoundingBox(pattern);
    EmbColor color;
    EmbStitch st;

    /* TODO: why is this repeated below? */
    /*
    for (i=0; i<pattern->stitchList->count; i++) {
        j = i;
        flag = st.flags;
        color = pattern->threads->thread[st.color].color;
        newColorCode = embThread_findNearestColor_fromThread(color, (EmbThread*)pecThreads, pecThreadCount);
        if (newColorCode != colorCode) {
            colorCount++;
            colorCode = newColorCode;
        }
        while (i<pattern->stitchList->count && (flag == st.flags)) {
            st = pattern->stitchList->stitch[i];
            count++;
            i++;
        }
        blockCount++;
        i = j;
    }
    */

    binaryWriteShort(file, (short)blockCount); /* block count */
    binaryWriteUShort(file, 0xFFFF);
    binaryWriteShort(file, 0x00);

    binaryWriteShort(file, 0x07); /* string length */
    binaryWriteBytes(file, "CSewSeg", 7);

    colorInfo = (short*)calloc(colorCount * 2, sizeof(short));

    colorCode = -1;
    blockCount = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        flag = st.flags;
        color = pattern->threads->thread[st.color].color;
        newColorCode = embThread_findNearestColor_fromThread(color, (EmbThread*)pecThreads, pecThreadCount);
        if (newColorCode != colorCode) {
            colorInfo[colorInfoIndex++] = (short)blockCount;
            colorInfo[colorInfoIndex++] = (short)newColorCode;
            colorCode = newColorCode;
        }
        /* TODO: check if this has an off-by-one error */
        for (count = 0; flag == st.flags; count++) {
            st = pattern->stitchList->stitch[i + count];
        }

        /* 1 for jump, 0 for normal */
        stitchType = flag & JUMP;
        binaryWriteShort(file, (short)stitchType);
        /* color code */
        binaryWriteShort(file, (short)colorCode);
        /* stitches in block */
        binaryWriteShort(file, (short)count);
        for (; flag == st.flags && i < pattern->stitchList->count; i++) {
            st = pattern->stitchList->stitch[i];
            binaryWriteShort(file, (short)(st.x - bounds.left));
            binaryWriteShort(file, (short)(st.y + bounds.top));
        }
        if (i < pattern->stitchList->count) {
            binaryWriteUShort(file, 0x8003);
        }
        blockCount++;
    }
    binaryWriteShort(file, (short)colorCount);
    for (i = 0; i < colorCount; i++) {
        binaryWriteShort(file, colorInfo[i * 2]);
        binaryWriteShort(file, colorInfo[i * 2 + 1]);
    }
    binaryWriteInt(file, 0);
    if (colorInfo) {
        free(colorInfo);
        colorInfo = 0;
    }
}

static void pesWriteEmbOneSection(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    /* TODO: pointer safety */
    int i;
    int hoopHeight = 1800, hoopWidth = 1300;
    EmbRect bounds;
    binaryWriteShort(file, 0x07); /* string length */
    binaryWriteBytes(file, "CEmbOne", 7);
    bounds = embPattern_calcBoundingBox(pattern);

    binaryWriteShort(file, 0);
    binaryWriteShort(file, 0);
    binaryWriteShort(file, 0);
    binaryWriteShort(file, 0);

    binaryWriteShort(file, 0);
    binaryWriteShort(file, 0);
    binaryWriteShort(file, 0);
    binaryWriteShort(file, 0);

    /* AffineTransform */
    binaryWriteFloat(file, 1.0f);
    binaryWriteFloat(file, 0.0f);
    binaryWriteFloat(file, 0.0f);
    binaryWriteFloat(file, 1.0f);
    binaryWriteFloat(file, (float)((embRect_width(bounds) - hoopWidth) / 2));
    binaryWriteFloat(file, (float)((embRect_height(bounds) + hoopHeight) / 2));

    binaryWriteShort(file, 1);
    binaryWriteShort(file, 0); /* Translate X */
    binaryWriteShort(file, 0); /* Translate Y */
    binaryWriteShort(file, (short)embRect_width(bounds));
    binaryWriteShort(file, (short)embRect_height(bounds));

    for (i = 0; i < 8; i++) {
        binaryWriteByte(file, 0);
    }

    /*WriteSubObjects(br, pes, SubBlocks); */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writePes(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int pecLocation;

    embPattern_flipVertical(pattern);
    embPattern_scale(pattern, 10.0);
    binaryWriteBytes(file, "#PES0001", 8);
    /* WRITE PECPointer 32 bit int */
    binaryWriteInt(file, 0x00);

    binaryWriteShort(file, 0x01);
    binaryWriteShort(file, 0x01);

    /* Write object count */
    binaryWriteUShort(file, 0x01);
    binaryWriteUShort(file, 0xFFFF); /* command */
    binaryWriteUShort(file, 0x00); /* unknown */

    pesWriteEmbOneSection(pattern, file, fileName);
    pesWriteSewSegSection(pattern, file, fileName);

    pecLocation = embFile_tell(file);
    embFile_seek(file, 0x08, SEEK_SET);
    binaryWriteByte(file, (unsigned char)(pecLocation & 0xFF));
    binaryWriteByte(file, (unsigned char)(pecLocation >> 8) & 0xFF);
    binaryWriteByte(file, (unsigned char)(pecLocation >> 16) & 0xFF);
    embFile_seek(file, 0x00, SEEK_END);
    writePecStitches(pattern, file, fileName);
    return 1;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readPhb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned int fileOffset;
    short colorCount;
    int i;

    embFile_seek(file, 0x71, SEEK_SET);
    colorCount = binaryReadInt16(file);

    for (i = 0; i < colorCount; i++) {
        EmbThread t = pecThreads[(int)binaryReadByte(file)];
        embPattern_addThread(pattern, t);
    }

    /* TODO: check that file begins with #PHB */
    embFile_seek(file, 0x54, SEEK_SET);
    fileOffset = 0x52;
    fileOffset += binaryReadUInt32(file);

    embFile_seek(file, fileOffset, SEEK_SET);
    fileOffset += binaryReadUInt32(file) + 2;

    embFile_seek(file, fileOffset, SEEK_SET);
    fileOffset += binaryReadUInt32(file);

    embFile_seek(file, fileOffset + 14, SEEK_SET); /* 28 */

    colorCount = (short)binaryReadByte(file);
    for (i = 0; i < colorCount; i++) {
        binaryReadByte(file);
    }
    binaryReadInt32(file); /* bytes to end of file */
    embFile_seek(file, 17, SEEK_CUR);
    readPecStitches(pattern, file, fileName);

    embPattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhb */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writePhb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writePhb */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readPhc(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int colorChanges, version, bytesInSection2;
    unsigned short pecOffset, bytesInSection, bytesInSection3;
    char pecAdd;
    EmbThread t;
    int i;

    embFile_seek(file, 0x07, SEEK_SET);
    version = binaryReadByte(file) - 0x30; /* converting from ansi number */
    embFile_seek(file, 0x4D, SEEK_SET);
    colorChanges = binaryReadUInt16(file);

    for (i = 0; i < colorChanges; i++) {
        t = pecThreads[(int)binaryReadByte(file)];
        embPattern_addThread(pattern, t);
    }
    embFile_seek(file, 0x2B, SEEK_SET);
    pecAdd = binaryReadByte(file);
    binaryReadUInt32(file); /* file length */
    pecOffset = binaryReadUInt16(file);
    embFile_seek(file, pecOffset + pecAdd, SEEK_SET);
    bytesInSection = binaryReadUInt16(file);
    embFile_seek(file, bytesInSection, SEEK_CUR);
    bytesInSection2 = binaryReadUInt32(file);
    embFile_seek(file, bytesInSection2, SEEK_CUR);
    bytesInSection3 = binaryReadUInt16(file);
    embFile_seek(file, bytesInSection3 + 0x12, SEEK_CUR);

    readPecStitches(pattern, file, fileName);

    embPattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhc */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writePhc(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writePhc */
}

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

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readRgb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i, numberOfColors;
    EmbThread t;

    embFile_seek(file, 0x00, SEEK_END);
    numberOfColors = embFile_tell(file) / 4;

    embArray_free(pattern->threads);
    pattern->threads = embArray_create(EMB_THREAD);

    embFile_seek(file, 0x00, SEEK_SET);
    for (i = 0; i < numberOfColors; i++) {
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        t.catalogNumber = "";
        t.description = "";
        binaryReadByte(file);
        embPattern_addThread(pattern, t);
    }
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeRgb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;
    EmbColor c;

    for (i = 0; i < pattern->threads->count; i++) {
        c = pattern->threads->thread[i].color;
        binaryWriteByte(file, c.r);
        binaryWriteByte(file, c.g);
        binaryWriteByte(file, c.b);
        binaryWriteByte(file, 0);
    }
    return 1;
}

static char sewDecode(unsigned char inputByte)
{
    /* TODO: fix return statement */
    return (inputByte >= 0x80) ? (char)(-~(inputByte - 1)) : (char)inputByte;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readSew(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i, flags, numberOfColors, fileLength;
    char dx, dy, thisStitchIsJump = 0;

    embFile_seek(file, 0x00, SEEK_END);
    fileLength = embFile_tell(file);
    embFile_seek(file, 0x00, SEEK_SET);
    numberOfColors = binaryReadByte(file);
    numberOfColors += (binaryReadByte(file) << 8);

    for (i = 0; i < numberOfColors; i++) {
        embPattern_addThread(pattern, jefThreads[binaryReadInt16(file)]);
    }
    embFile_seek(file, 0x1D78, SEEK_SET);

    for (i = 0; embFile_tell(file) < fileLength; i++) {
        unsigned char b0 = binaryReadByte(file);
        unsigned char b1 = binaryReadByte(file);

        flags = NORMAL;
        if (thisStitchIsJump) {
            flags = TRIM;
            thisStitchIsJump = 0;
        }
        if (b0 == 0x80) {
            if (b1 == 1) {
                b0 = binaryReadByte(file);
                b1 = binaryReadByte(file);
                flags = STOP;
            } else if ((b1 == 0x02) || (b1 == 0x04)) {
                thisStitchIsJump = 1;
                b0 = binaryReadByte(file);
                b1 = binaryReadByte(file);
                flags = TRIM;
            } else if (b1 == 0x10) {
                break;
            }
        }
        dx = sewDecode(b0);
        dy = sewDecode(b1);
        if (abs(dx) == 127 || abs(dy) == 127) {
            thisStitchIsJump = 1;
            flags = TRIM;
        }

        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    printf("current position: %ld\n", embFile_tell(file));

    return 1;
}

static void sewEncode(unsigned char* b, char dx, char dy, int flags)
{
    if (!b) {
        embLog("ERROR: format-exp.c expEncode(), b argument is null\n");
        return;
    }
    if (flags == STOP) {
        b[0] = 0x80;
        b[1] = 1;
        b[2] = dx;
        b[3] = dy;
    } else if (flags == END) {
        b[0] = 0x80;
        b[1] = 0x10;
        b[2] = 0;
        b[3] = 0;
    } else if (flags == TRIM || flags == JUMP) {
        b[0] = 0x80;
        b[1] = 2;
        b[2] = dx;
        b[3] = dy;
    } else {
        b[0] = dx;
        b[1] = dy;
    }
}
/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeSew(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int colorlistSize, minColors, i, thr;
    EmbStitch st;
    EmbColor col;
    double dx = 0.0, dy = 0.0, xx = 0.0, yy = 0.0;
    unsigned char b[4];

    colorlistSize = pattern->threads->count;

    minColors = EMB_MAX_2(pattern->threads->count, 6);
    binaryWriteInt(file, 0x74 + (minColors * 4));
    binaryWriteInt(file, 0x0A);

    for (i = 0; i < pattern->threads->count; i++) {
        col = pattern->threads->thread[i].color;
        thr = embThread_findNearestColor_fromThread(col, jefThreads, 79);
        binaryWriteInt(file, thr);
    }

    for (i = 0; i < (minColors - colorlistSize); i++) {
        binaryWriteInt(file, 0x0D);
    }

    for (i = 2; i < 7538; i++) {
        embFile_print(file, " ");
    }

    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        sewEncode(b, (char)roundDouble(dx), (char)roundDouble(dy), st.flags);
        if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
            embFile_write(b, 1, 4, file);
        } else {
            embFile_write(b, 1, 2, file);
        }
    }
    return 1;
}

/*****************************************
 * SHV Colors
 ****************************************/
static const int shvThreadCount = 42;
static const EmbThread shvThreads[] = {
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 255 }, "Blue", "TODO:CATALOG_NUMBER" },
    { { 51, 204, 102 }, "Green", "TODO:CATALOG_NUMBER" },
    { { 255, 0, 0 }, "Red", "TODO:CATALOG_NUMBER" },
    { { 255, 0, 255 }, "Purple", "TODO:CATALOG_NUMBER" },
    { { 255, 255, 0 }, "Yellow", "TODO:CATALOG_NUMBER" },
    { { 127, 127, 127 }, "Grey", "TODO:CATALOG_NUMBER" },
    { { 51, 154, 255 }, "Light Blue", "TODO:CATALOG_NUMBER" },
    { { 0, 255, 0 }, "Light Green", "TODO:CATALOG_NUMBER" },
    { { 255, 127, 0 }, "Orange", "TODO:CATALOG_NUMBER" },
    { { 255, 160, 180 }, "Pink", "TODO:CATALOG_NUMBER" },
    { { 153, 75, 0 }, "Brown", "TODO:CATALOG_NUMBER" },
    { { 255, 255, 255 }, "White", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 255, 127, 127 }, "Light Red", "TODO:CATALOG_NUMBER" },
    { { 255, 127, 255 }, "Light Purple", "TODO:CATALOG_NUMBER" },
    { { 255, 255, 153 }, "Light Yellow", "TODO:CATALOG_NUMBER" },
    { { 192, 192, 192 }, "Light Grey", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 255, 165, 65 }, "Light Orange", "TODO:CATALOG_NUMBER" },
    { { 255, 204, 204 }, "Light Pink", "TODO:CATALOG_NUMBER" },
    { { 175, 90, 10 }, "Light Brown", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 127 }, "Dark Blue", "TODO:CATALOG_NUMBER" },
    { { 0, 127, 0 }, "Dark Green", "TODO:CATALOG_NUMBER" },
    { { 127, 0, 0 }, "Dark Red", "TODO:CATALOG_NUMBER" },
    { { 127, 0, 127 }, "Dark Purple", "TODO:CATALOG_NUMBER" },
    { { 200, 200, 0 }, "Dark Yellow", "TODO:CATALOG_NUMBER" },
    { { 60, 60, 60 }, "Dark Gray", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 232, 63, 0 }, "Dark Orange", "TODO:CATALOG_NUMBER" },
    { { 255, 102, 122 }, "Dark Pink", "TODO:CATALOG_NUMBER" }
};

static char shvDecode(unsigned char inputByte)
{
    if (inputByte >= 0x80) {
        return (char)-((unsigned char)((~inputByte) + 1));
    }
    return ((char)inputByte);
}

static short shvDecodeShort(unsigned short inputByte)
{
    if (inputByte > 0x8000) {
        return (short)-((unsigned short)((~inputByte) + 1));
    }
    return ((short)inputByte);
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readShv(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;
    char inJump = 0;
    unsigned char fileNameLength, designWidth, designHeight;
    char halfDesignWidth, halfDesignHeight, halfDesignWidth2, halfDesignHeight2;
    char* headerText = "Embroidery disk created using software licensed from Viking Sewing Machines AB, Sweden";
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

    embFile_seek(file, strlen(headerText), SEEK_SET);
    fileNameLength = binaryReadUInt8(file);
    embFile_seek(file, fileNameLength, SEEK_CUR);
    designWidth = binaryReadUInt8(file);
    designHeight = binaryReadUInt8(file);
    halfDesignWidth = binaryReadUInt8(file);
    halfDesignHeight = binaryReadUInt8(file);
    halfDesignWidth2 = binaryReadUInt8(file);
    halfDesignHeight2 = binaryReadUInt8(file);
    if ((designHeight % 2) == 1) {
        embFile_seek(file, ((designHeight + 1) * designWidth) / 2, SEEK_CUR);
    } else {
        embFile_seek(file, (designHeight * designWidth) / 2, SEEK_CUR);
    }
    numberOfColors = binaryReadUInt8(file);
    magicCode = binaryReadUInt16(file);
    binaryReadByte(file);
    something = binaryReadInt32(file);
    left = binaryReadInt16(file);
    top = binaryReadInt16(file);
    right = binaryReadInt16(file);
    bottom = binaryReadInt16(file);

    something2 = binaryReadByte(file);
    numberOfSections = binaryReadUInt8(file);
    something3 = binaryReadByte(file);

    for (i = 0; i < numberOfColors; i++) {
        unsigned int stitchCount, colorNumber;
        stitchCount = binaryReadUInt32BE(file);
        colorNumber = binaryReadUInt8(file);
        embPattern_addThread(pattern, shvThreads[colorNumber % 43]);
        stitchesPerColor[i] = stitchCount;
        embFile_seek(file, 9, SEEK_CUR);
    }

    embFile_seek(file, -2, SEEK_CUR);

    for (i = 0; !embFile_eof(file); i++) {
        unsigned char b0, b1;
        int flags;
        if (inJump) {
            flags = JUMP;
        } else {
            flags = NORMAL;
        }
        b0 = binaryReadUInt8(file);
        b1 = binaryReadUInt8(file);
        if (stitchesSinceChange >= stitchesPerColor[currColorIndex]) {
            embPattern_addStitchRel(pattern, 0, 0, STOP, 1);
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
                sx = binaryReadUInt8(file);
                sx = (unsigned short)(sx << 8 | binaryReadUInt8(file));
                sy = binaryReadUInt8(file);
                sy = (unsigned short)(sy << 8 | binaryReadUInt8(file));
                flags = TRIM;
                inJump = 1;
                embPattern_addStitchRel(pattern, shvDecodeShort(sx) / 10.0, shvDecodeShort(sy) / 10.0, flags, 1);
                continue;
            }
        }
        dx = shvDecode(b0);
        dy = shvDecode(b1);
        stitchesSinceChange++;
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    embFile_close(file);
    embPattern_end(pattern);
    embPattern_flipVertical(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeShv(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeShv */
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readSst(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int fileLength;

    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_seek(file, 0, SEEK_END);
    fileLength = embFile_tell(file);
    embFile_seek(file, 0xA0, SEEK_SET); /* skip the all zero header */
    while (embFile_tell(file) < fileLength) {
        int stitchType = NORMAL;

        int b1 = (int)binaryReadByte(file);
        int b2 = (int)binaryReadByte(file);
        unsigned char commandByte = binaryReadByte(file);

        if (commandByte == 0x04) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
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
        embPattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }

    return 1; /*TODO: finish readSst */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeSst(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeSst */
}

typedef struct SubDescriptor_ {
    int someNum; /* TODO: better variable naming */
    int someInt; /* TODO: better variable naming */
    int someOtherInt; /* TODO: better variable naming */
    char* colorCode;
    char* colorName;
} SubDescriptor;

typedef struct StxThread_ {
    char* colorCode;
    char* colorName;
    char* sectionName;
    SubDescriptor* subDescriptors;
    EmbColor stxColor;
} StxThread;

static int stxReadThread(StxThread* thread, EmbFile* file)
{
    int j, colorNameLength, sectionNameLength;
    int somethingSomething, somethingSomething2, somethingElse, numberOfOtherDescriptors; /* TODO: determine what these represent */
    int codeLength = 0;
    char* codeBuff = 0;
    char* codeNameBuff = 0;
    char* sectionNameBuff = 0;
    EmbColor col;
    unsigned char whatIsthis; /* TODO: determine what this represents */

    if (!thread) {
        embLog("ERROR: format-stx.c stxReadThread(), thread argument is null\n");
        return 0;
    }
    if (!file) {
        embLog("ERROR: format-stx.c stxReadThread(), file argument is null\n");
        return 0;
    }

    codeLength = binaryReadUInt8(file);
    codeBuff = (char*)malloc(codeLength);
    if (!codeBuff) {
        embLog("ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeBuff\n");
        return 0;
    }
    binaryReadBytes(file, (unsigned char*)codeBuff, codeLength); /* TODO: check return value */
    thread->colorCode = codeBuff;
    colorNameLength = binaryReadUInt8(file);
    codeNameBuff = (char*)malloc(colorNameLength);
    if (!codeNameBuff) {
        embLog("ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeNameBuff\n");
        return 0;
    }
    binaryReadBytes(file, (unsigned char*)codeNameBuff, colorNameLength); /* TODO: check return value */
    thread->colorName = codeNameBuff;

    col.r = binaryReadUInt8(file);
    col.b = binaryReadUInt8(file);
    col.g = binaryReadUInt8(file);

    whatIsthis = binaryReadUInt8(file);

    sectionNameLength = binaryReadUInt8(file);
    sectionNameBuff = (char*)malloc(sectionNameLength);
    if (!sectionNameBuff) {
        embLog("ERROR: format-stx.c stxReadThread(), unable to allocate memory for sectionNameBuff\n");
        return 0;
    }
    binaryReadBytes(file, (unsigned char*)sectionNameBuff, sectionNameLength); /* TODO: check return value */
    thread->sectionName = sectionNameBuff;

    somethingSomething = binaryReadInt32(file);
    somethingSomething2 = binaryReadInt32(file);
    somethingElse = binaryReadInt32(file);
    numberOfOtherDescriptors = binaryReadInt16(file);

    thread->subDescriptors = (SubDescriptor*)malloc(sizeof(SubDescriptor) * numberOfOtherDescriptors);
    if (!thread->subDescriptors) {
        embLog("ERROR: format-stx.c stxReadThread(), unable to allocate memory for thread->subDescriptors\n");
        return 0;
    }
    for (j = 0; j < numberOfOtherDescriptors; j++) {
        SubDescriptor sd;
        char *subCodeBuff, *subColorNameBuff;
        int subCodeLength, subColorNameLength;

        sd.someNum = binaryReadInt16(file);
        /* Debug.Assert(sd.someNum == 1); TODO: review */
        sd.someInt = binaryReadInt32(file);
        subCodeLength = binaryReadUInt8(file);
        subCodeBuff = (char*)malloc(subCodeLength);
        if (!subCodeBuff) {
            embLog("ERROR: format-stx.c stxReadThread(), unable to allocate memory for subCodeBuff\n");
            return 0;
        }
        binaryReadBytes(file, (unsigned char*)subCodeBuff, subCodeLength); /* TODO: check return value */
        sd.colorCode = subCodeBuff;
        subColorNameLength = binaryReadUInt8(file);
        subColorNameBuff = (char*)malloc(subColorNameLength);
        if (!subColorNameBuff) {
            embLog("ERROR: format-stx.c stxReadThread(), unable to allocate memory for subColorNameBuff\n");
            return 0;
        }
        binaryReadBytes(file, (unsigned char*)subColorNameBuff, subColorNameLength); /* TODO: check return value */
        sd.colorName = subColorNameBuff;
        sd.someOtherInt = binaryReadInt32(file);
        thread->subDescriptors[j] = sd;
    }
    return 1;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readStx(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i, threadCount;
    unsigned char* gif = 0;
    /* public Bitmap Image; */
    StxThread* stxThreads = 0;
    unsigned char headerBytes[7];
    char* header = 0;
    char filetype[4], version[5];
    int paletteLength, imageLength, something1, stitchDataOffset, something3, threadDescriptionOffset, stitchCount, left, right, colors;
    int val1, val2, val3, val4, val5, val6;

    int vala1, vala2, vala3, vala4, vala5, vala6;
    int bottom, top;

    binaryReadBytes(file, headerBytes, 7); /* TODO: check return value */
    header = (char*)headerBytes;

    memcpy(filetype, &header[0], 3);
    memcpy(version, &header[3], 4);
    filetype[3] = '\0';
    version[4] = '\0';
    binaryReadByte(file);
    paletteLength = binaryReadInt32(file);
    imageLength = binaryReadInt32(file);
    something1 = binaryReadInt32(file);
    stitchDataOffset = binaryReadInt32(file);
    something3 = binaryReadInt32(file);
    threadDescriptionOffset = binaryReadInt32(file);
    stitchCount = binaryReadInt32(file);
    colors = binaryReadInt32(file);
    right = binaryReadInt16(file);
    left = binaryReadInt16(file);
    bottom = binaryReadInt16(file);
    top = binaryReadInt16(file);

    gif = (unsigned char*)malloc(imageLength);
    if (!gif) {
        embLog("ERROR: format-stx.c readStx(), unable to allocate memory for gif\n");
        return 0;
    }
    binaryReadBytes(file, gif, imageLength); /* TODO: check return value */
    /*Stream s2 = new MemoryStream(gif); TODO: review */
    /*Image = new Bitmap(s2); TODO: review */

    threadCount = binaryReadInt16(file);
    stxThreads = (StxThread*)malloc(sizeof(StxThread) * threadCount);
    if (!stxThreads) {
        embLog("ERROR: format-stx.c readStx(), unable to allocate memory for stxThreads\n");
        return 0;
    }
    for (i = 0; i < threadCount; i++) {
        EmbThread t;
        StxThread st;
        stxReadThread(&st, file);

        t.color.r = st.stxColor.r;
        t.color.g = st.stxColor.g;
        t.color.b = st.stxColor.b;
        t.description = st.colorName;
        t.catalogNumber = st.colorCode;
        embPattern_addThread(pattern, t);
        stxThreads[i] = st;
    }

    binaryReadInt32(file);
    binaryReadInt32(file);
    binaryReadInt32(file);
    binaryReadInt16(file);
    binaryReadUInt8(file);

    val1 = binaryReadInt16(file);
    val2 = binaryReadInt16(file);
    val3 = binaryReadInt16(file);
    val4 = binaryReadInt16(file);

    val5 = binaryReadInt16(file); /* 0 */
    val6 = binaryReadInt16(file); /* 0 */

    vala1 = binaryReadInt16(file);
    vala2 = binaryReadInt16(file);
    vala3 = binaryReadInt16(file);
    vala4 = binaryReadInt16(file);
    vala5 = binaryReadInt16(file); /* 0 */
    vala6 = binaryReadInt16(file); /* 0 */

    binaryReadInt32(file); /* 0 */
    binaryReadInt32(file); /* 0 */

    /* br.BaseStream.Position = stitchDataOffset; TODO: review */
    for (i = 1; i < stitchCount;) {
        char b0 = binaryReadByte(file);
        char b1 = binaryReadByte(file);
        if (b0 == -128) {
            switch (b1) {
            case 1:
                b0 = binaryReadByte(file);
                b1 = binaryReadByte(file);
                /*embPattern_addStitchRel(b0, b1, STOP); TODO: review */

                i++;
                break;
            case 2:
                b0 = binaryReadByte(file);
                b1 = binaryReadByte(file);
                embPattern_addStitchRel(pattern, b0 / 10.0, b1 / 10.0, JUMP, 1);
                i++;
                break;
            case -94:
                /* TODO: Is this a syncronize? If so document it in the comments. */
                break;
            default:
                /*Debugger.Break(); TODO: review */
                break;
            }
        } else {
            embPattern_addStitchRel(pattern, b0 / 10.0, b1 / 10.0, NORMAL, 1);
            i++;
        }
    }

    embPattern_flipVertical(pattern);
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeStx(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeStx */
}

static int decodeT01RecordFlags(unsigned char b2)
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

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readT01(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[3];

    embPattern_loadExternalColorFile(pattern, fileName);

    while (embFile_read(b, 1, 3, file) == 3) {
        int flags;
        int x = 0;
        int y = 0;
        if (b[0] & 0x01)
            x += 1;
        if (b[0] & 0x02)
            x -= 1;
        if (b[0] & 0x04)
            x += 9;
        if (b[0] & 0x08)
            x -= 9;
        if (b[0] & 0x80)
            y += 1;
        if (b[0] & 0x40)
            y -= 1;
        if (b[0] & 0x20)
            y += 9;
        if (b[0] & 0x10)
            y -= 9;
        if (b[1] & 0x01)
            x += 3;
        if (b[1] & 0x02)
            x -= 3;
        if (b[1] & 0x04)
            x += 27;
        if (b[1] & 0x08)
            x -= 27;
        if (b[1] & 0x80)
            y += 3;
        if (b[1] & 0x40)
            y -= 3;
        if (b[1] & 0x20)
            y += 27;
        if (b[1] & 0x10)
            y -= 27;
        if (b[2] & 0x04)
            x += 81;
        if (b[2] & 0x08)
            x -= 81;
        if (b[2] & 0x20)
            y += 81;
        if (b[2] & 0x10)
            y -= 81;
        flags = decodeT01RecordFlags(b[2]);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        if (flags == END)
            break;
    }

    return 1;
}

static void encode_t01_record(EmbFile* file, int x, int y, int flags)
{
    char b[4];
    b[0] = b[1] = b[2] = 0;

    /* cannot encode values > +121 or < -121. */
    if (x > 121 || x < -121) {
        embLog("ERROR: format-t01.c encode_t01_record(), x is not in valid range [-121,121] , x =");
        /* embLog_print("%d\n", x); */
    }
    if (y > 121 || y < -121) {
        embLog("ERROR: format-t01.c encode_t01_record(), y is not in valid range [-121,121] , y =");
        /* embLog_print("%d\n", y); */
    }

    if (x >= +41) {
        b[2] += 1 << 2;
        x -= 81;
    }
    if (x <= -41) {
        b[2] += 1 << 3;
        x += 81;
    }
    if (x >= +14) {
        b[1] += 1 << 2;
        x -= 27;
    }
    if (x <= -14) {
        b[1] += 1 << 3;
        x += 27;
    }
    if (x >= +5) {
        b[0] += 1 << 2;
        x -= 9;
    }
    if (x <= -5) {
        b[0] += 1 << 3;
        x += 9;
    }
    if (x >= +2) {
        b[1] += 1 << 0;
        x -= 3;
    }
    if (x <= -2) {
        b[1] += 1 << 1;
        x += 3;
    }
    if (x >= +1) {
        b[0] += 1 << 0;
        x -= 1;
    }
    if (x <= -1) {
        b[0] += 1 << 1;
        x += 1;
    }
    if (x != 0) {
        embLog("ERROR: format-dst.c encode_t01_record(), x should be zero yet x = %d\n");
    }
    if (y >= +41) {
        b[2] += 1 << 5;
        y -= 81;
    }
    if (y <= -41) {
        b[2] += 1 << 4;
        y += 81;
    }
    if (y >= +14) {
        b[1] += 1 << 5;
        y -= 27;
    }
    if (y <= -14) {
        b[1] += 1 << 4;
        y += 27;
    }
    if (y >= +5) {
        b[0] += 1 << 5;
        y -= 9;
    }
    if (y <= -5) {
        b[0] += 1 << 4;
        y += 9;
    }
    if (y >= +2) {
        b[1] += 1 << 7;
        y -= 3;
    }
    if (y <= -2) {
        b[1] += 1 << 6;
        y += 3;
    }
    if (y >= +1) {
        b[0] += 1 << 7;
        y -= 1;
    }
    if (y <= -1) {
        b[0] += 1 << 6;
        y += 1;
    }
    if (y != 0) {
        embLog("ERROR: format-dst.c encode_t01_record(), y should be zero yet y = %d\n");
    }

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

    embFile_write(b, 1, 3, file);
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeT01(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbRect boundingRect;
    int xx, yy, dx, dy, i;
    EmbStitch st;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    boundingRect = embPattern_calcBoundingBox(pattern);

    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = roundDouble(st.x * 10.0) - xx;
        dy = roundDouble(st.y * 10.0) - yy;
        xx = roundDouble(st.x * 10.0);
        yy = roundDouble(st.y * 10.0);
        encode_t01_record(file, dx, dy, st.flags);
    }
    return 1;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readT09(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[3];

    embFile_seek(file, 0x0C, SEEK_SET);

    while (embFile_read(b, 1, 3, file) == 3) {
        int stitchType = NORMAL;
        int b1 = b[0];
        int b2 = b[1];
        unsigned char commandByte = b[2];
        if (commandByte == 0x00) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        if (commandByte & 0x10)
            stitchType = STOP;
        if (commandByte & 0x20)
            b1 = -b1;
        if (commandByte & 0x40)
            b2 = -b2;

        embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeT09(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeT09 */
}

static int decodeTapRecordFlags(unsigned char b2)
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

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readTap(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[3];

    embPattern_loadExternalColorFile(pattern, fileName);

    while (embFile_read(b, 1, 3, file) == 3) {
        int flags;
        int x = 0;
        int y = 0;
        if (b[0] & 0x01)
            x += 1;
        if (b[0] & 0x02)
            x -= 1;
        if (b[0] & 0x04)
            x += 9;
        if (b[0] & 0x08)
            x -= 9;
        if (b[0] & 0x80)
            y += 1;
        if (b[0] & 0x40)
            y -= 1;
        if (b[0] & 0x20)
            y += 9;
        if (b[0] & 0x10)
            y -= 9;
        if (b[1] & 0x01)
            x += 3;
        if (b[1] & 0x02)
            x -= 3;
        if (b[1] & 0x04)
            x += 27;
        if (b[1] & 0x08)
            x -= 27;
        if (b[1] & 0x80)
            y += 3;
        if (b[1] & 0x40)
            y -= 3;
        if (b[1] & 0x20)
            y += 27;
        if (b[1] & 0x10)
            y -= 27;
        if (b[2] & 0x04)
            x += 81;
        if (b[2] & 0x08)
            x -= 81;
        if (b[2] & 0x20)
            y += 81;
        if (b[2] & 0x10)
            y -= 81;
        flags = decodeTapRecordFlags(b[2]);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        if (flags == END)
            break;
    }

    return 1;
}

static void encode_tap_record(EmbFile* file, int x, int y, int flags)
{
    char b0, b1, b2;
    b0 = b1 = b2 = 0;

    /* cannot encode values > +121 or < -121. */
    if (x > 121 || x < -121)
        embLog("ERROR: format-tap.c encode_tap_record(), x is not in valid range [-121,121] , x =\n");
    if (y > 121 || y < -121)
        embLog("ERROR: format-tap.c encode_tap_record(), y is not in valid range [-121,121] , y =\n");

    if (x >= +41) {
        b2 += 1 << 2;
        x -= 81;
    }
    if (x <= -41) {
        b2 += 1 << 3;
        x += 81;
    }
    if (x >= +14) {
        b1 += 1 << 2;
        x -= 27;
    }
    if (x <= -14) {
        b1 += 1 << 3;
        x += 27;
    }
    if (x >= +5) {
        b0 += 1 << 2;
        x -= 9;
    }
    if (x <= -5) {
        b0 += 1 << 3;
        x += 9;
    }
    if (x >= +2) {
        b1 += 1 << 0;
        x -= 3;
    }
    if (x <= -2) {
        b1 += 1 << 1;
        x += 3;
    }
    if (x >= +1) {
        b0 += 1 << 0;
        x -= 1;
    }
    if (x <= -1) {
        b0 += 1 << 1;
        x += 1;
    }
    if (x != 0) {
        embLog("ERROR: format-tap.c encode_tap_record(), x should be zero yet x =\n");
    }
    if (y >= +41) {
        b2 += 1 << 5;
        y -= 81;
    }
    if (y <= -41) {
        b2 += 1 << 4;
        y += 81;
    }
    if (y >= +14) {
        b1 += 1 << 5;
        y -= 27;
    }
    if (y <= -14) {
        b1 += 1 << 4;
        y += 27;
    }
    if (y >= +5) {
        b0 += 1 << 5;
        y -= 9;
    }
    if (y <= -5) {
        b0 += 1 << 4;
        y += 9;
    }
    if (y >= +2) {
        b1 += 1 << 7;
        y -= 3;
    }
    if (y <= -2) {
        b1 += 1 << 6;
        y += 3;
    }
    if (y >= +1) {
        b0 += 1 << 7;
        y -= 1;
    }
    if (y <= -1) {
        b0 += 1 << 6;
        y += 1;
    }
    if (y != 0) {
        embLog("ERROR: format-tap.c encode_tap_record(), y should be zero yet y =\n");
    }

    b2 |= (char)3;

    if (flags & END) {
        b0 = 0;
        b1 = 0;
        b2 = 0xF3;
    }
    if (flags & (JUMP | TRIM)) {
        b2 = (char)(b2 | 0x83);
    }
    if (flags & STOP) {
        b2 = (char)(b2 | 0xC3);
    }

    binaryWriteByte(file, (unsigned char)b0);
    binaryWriteByte(file, (unsigned char)b1);
    binaryWriteByte(file, (unsigned char)b2);
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeTap(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbRect boundingRect;
    int xx, yy, dx, dy, i;
    EmbStitch st;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    boundingRect = embPattern_calcBoundingBox(pattern);
    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = roundDouble(st.x * 10.0) - xx;
        dy = roundDouble(st.y * 10.0) - yy;
        xx = roundDouble(st.x * 10.0);
        yy = roundDouble(st.y * 10.0);
        encode_tap_record(file, dx, dy, st.flags);
    }
    return 1;
}

#define NOTFRM 0x00080000

typedef struct ThredHeader_ /* thred file header */
{
    unsigned int sigVersion; /* signature and version */
    unsigned int length; /* length of ThredHeader + length of stitch data */
    unsigned short numStiches; /* number of stitches */
    unsigned short hoopSize; /* size of hoop */
    unsigned short reserved[7]; /* reserved for expansion */
} ThredHeader;

typedef struct ThredExtension_ /* thred v1.0 file header extension */
{
    float hoopX; /* hoop size x dimension in 1/6 mm units */
    float hoopY; /* hoop size y dimension in 1/6 mm units */
    float stitchGranularity; /* stitches per millimeter--not implemented */
    char creatorName[50]; /* name of the file creator */
    char modifierName[50]; /* name of last file modifier */
    char auxFormat; /* auxillary file format, 0=PCS,1=DST,2=PES */
    char reserved[31]; /* reserved for expansion */
} ThredExtension;

/*
bit definitions for attributes of stitch
0-3     stitch color
4-14    form pointer
15-18   spares
19      not a form stitch
20      center walk stitch
21      edge walk stitch
22      underlay stitch
23      knot stitch
24      feather stitch
25-27   layer
28      spare
29-30   stitch type 00=not a form stitch, 01=form fill, 10=form border fill, 11=applique stitches
31      set for user edited stitches
*/

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readThr(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    ThredHeader header;
    unsigned char r, g, b;
    int currentColor, i;
    EmbThread thread;

    header.sigVersion = binaryReadUInt32(file);
    header.length = binaryReadUInt32(file);
    header.numStiches = binaryReadUInt16(file);
    header.hoopSize = binaryReadUInt16(file);
    header.reserved[0] = binaryReadUInt16(file);
    header.reserved[1] = binaryReadUInt16(file);
    header.reserved[2] = binaryReadUInt16(file);
    header.reserved[3] = binaryReadUInt16(file);
    header.reserved[4] = binaryReadUInt16(file);
    header.reserved[5] = binaryReadUInt16(file);
    header.reserved[6] = binaryReadUInt16(file);

    if ((header.sigVersion & 0xffffff) == 0x746872) {
        unsigned int verVar = (header.sigVersion & 0xff000000) >> 24;
        switch (verVar) {
        case 0:
            break;
        case 1:
        case 2:
            embFile_seek(file, 144, SEEK_CUR); /* skip the file header extension */
            break;
        default:
            return 0; /* unsuported version */
        }
    }

    currentColor = -1;
    for (i = 0; i < header.numStiches; i++) {
        int type = NORMAL;
        float x = binaryReadFloat(file) / 10.0f;
        float y = binaryReadFloat(file) / 10.0f;
        unsigned int color = binaryReadUInt32(file);

        if ((int)(color & 0xF) != currentColor) {
            currentColor = (int)color & 0xF;
            embPattern_changeColor(pattern, currentColor);
            type = STOP | TRIM;
        }
        embPattern_addStitchAbs(pattern, x, y, type, 0);
    }
    embFile_seek(file, 16, SEEK_CUR); /* skip bitmap name (16 chars) */

    r = binaryReadByte(file);
    g = binaryReadByte(file);
    b = binaryReadByte(file);
    binaryReadByte(file);

    for (i = 0; i < 16; i++) {
        thread.description = NULL;
        thread.catalogNumber = NULL;
        thread.color.r = binaryReadByte(file);
        thread.color.g = binaryReadByte(file);
        thread.color.b = binaryReadByte(file);
        binaryReadByte(file);
        embPattern_addThread(pattern, thread);
    }
    /*  64 bytes of rgbx(4 bytes) colors (16 custom colors) */
    /*  16 bytes of thread size (ascii representation ie. '4') */

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeThr(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i, stitchCount;
    unsigned char version = 0;
    ThredHeader header;
    ThredExtension extension;
    char bitmapName[16];
    EmbStitch st;
    EmbColor c;

    stitchCount = pattern->stitchList->count;

    memset(&header, 0, sizeof(ThredHeader));
    header.sigVersion = 0x746872 | (version << 24);
    header.length = stitchCount * 12 + 16;
    if (version == 1 || version == 2) {
        header.length = header.length + sizeof(ThredHeader);
    }
    header.numStiches = (unsigned short)stitchCount; /* number of stitches in design */
    header.hoopSize = 5;

    binaryWriteUInt(file, header.sigVersion);
    binaryWriteUInt(file, header.length);
    binaryWriteUShort(file, header.numStiches);
    binaryWriteUShort(file, header.hoopSize);
    binaryWriteUShort(file, header.reserved[0]);
    binaryWriteUShort(file, header.reserved[1]);
    binaryWriteUShort(file, header.reserved[2]);
    binaryWriteUShort(file, header.reserved[3]);
    binaryWriteUShort(file, header.reserved[4]);
    binaryWriteUShort(file, header.reserved[5]);
    binaryWriteUShort(file, header.reserved[6]);

    if (version == 1 || version == 2) {
        memset(&extension, 0, sizeof(ThredExtension));
        extension.auxFormat = 1;
        extension.hoopX = 640;
        extension.hoopY = 640;

        binaryWriteFloat(file, extension.hoopX);
        binaryWriteFloat(file, extension.hoopY);
        binaryWriteFloat(file, extension.stitchGranularity);
        binaryWriteBytes(file, extension.creatorName, 50);
        binaryWriteBytes(file, extension.modifierName, 50);
        binaryWriteByte(file, extension.auxFormat);
        binaryWriteBytes(file, extension.reserved, 31);
    }

    /* write stitches */
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        binaryWriteFloat(file, (float)(st.x * 10.0));
        binaryWriteFloat(file, (float)(st.y * 10.0));
        binaryWriteUInt(file, NOTFRM | (st.color & 0x0F));
    }
    binaryWriteBytes(file, bitmapName, 16);
    /* background color */
    binaryWriteByte(file, 0xFF); /* r */
    binaryWriteByte(file, 0xFF); /* g */
    binaryWriteByte(file, 0xFF); /* b */
    binaryWriteByte(file, 0x00);

    for (i = 0; i < pattern->threads->count; i++) {
        c = pattern->threads->thread[i].color;
        binaryWriteByte(file, c.r);
        binaryWriteByte(file, c.g);
        binaryWriteByte(file, c.b);
        binaryWriteByte(file, 0);
        if (i >= 16)
            break;
    }

    /* write remaining colors if not yet 16 */
    for (; i < 16; i++) {
        binaryWriteUInt(file, 0);
    }

#if 0
    /* write custom colors */
    for (i=0; i<pattern->threads->count; i++) {
        c = pattern->threads->thread[i].color;
        binaryWriteByte(file, c.r);
        binaryWriteByte(file, c.g);
        binaryWriteByte(file, c.b);
        binaryWriteByte(file, 0);
        if (i >= 16) break;
    }

    /* write remaining colors if not yet 16 */
    for (; i < 16; i++) {
        binaryWriteUInt(file, 0);
    }
#endif

    for (i = 0; i < 16; i++) {
        binaryWriteByte(file, '4');
    }

    return 1;
}

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

/**
 * 
 */

static void encode_u00_stitch(EmbStitch st, unsigned char *data)
{
    char dx, dy;
    dx = (char)roundDouble(10.0*st.x);
    dy = (char)roundDouble(10.0*st.y);
    data[2] = dx;
    data[1] = dy;
    data[0] = 0;
    if (dx < 0.0) {
        data[0] |= 0x20;
    }
    if (dy < 0.0) {
        data[0] |= 0x40;
    }
    switch (st.flags) {
    case JUMP:
        data[0] |= 0x10;
        break;
    case STOP:
        data[0] |= 0x01;
        break;
    case END:
        data[0] = 0xF8;
        break;
    case NORMAL:
    default:
        break;
    }
}

static EmbStitch decode_u00_stitch(unsigned char *data)
{
    EmbStitch st;
    st.flags = NORMAL;
    if (data[0] == 0xF8 || data[0] == 0x87 || data[0] == 0x91) {
        st.flags = END;
    }
    if ((data[0] & 0x0F) == 0) {
        st.flags = NORMAL;
    } else if ((data[0] & 0x1f) == 1) {
        st.flags = JUMP;
    } else if ((data[0] & 0x0F) > 0) {
        st.flags = STOP;
    }

    st.x = data[2]/10.0;
    st.y = data[1]/10.0;
    if ((data[0] & 0x20) > 0)
        st.x *= -1.0;
    if ((data[0] & 0x40) > 0)
        st.y *= -1.0;
    return st;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readU00(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbThread t;
    EmbStitch st;
    unsigned char b[4], i;

    /* 16 3byte RGB's start @ 0x08 followed by 14 bytes between 0 and 15 with index of color for each color change */
    embFile_seek(file, 0x08, SEEK_SET);

    for (i = 0; i < 16; i++) {
        embFile_read(b, 1, 3, file);
        t.color = embColor_fromStr(b);
        embPattern_addThread(pattern, t);
    }

    embFile_seek(file, 0x100, SEEK_SET);
    while (embFile_read(b, 1, 3, file) == 3) {
        st = decode_u00_stitch(b);
        if (st.flags == END) {
            break;
        }
        embPattern_addStitchRel(pattern, st.x, st.y, st.flags, 1);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeU00(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[4], i;

    embFile_pad(file, ' ', 8);

    for (i = 0; i < pattern->threads->count; i++) {
        embColor_toStr(pattern->threads->thread[i].color, b);
        embFile_write(b, 1, 3, file);
    }

    /* this should pad to 512 bytes */
    embFile_pad(file, ' ', 0x100 - 3*pattern->threads->count - 8);

    for (i = 0; i < pattern->stitchList->count; i++) {
        encode_u00_stitch(pattern->stitchList->stitch[i], b);
        embFile_write(b, 1, 3, file);
    }
    return 1;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readU01(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return readU00(pattern, file, fileName);
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeU01(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return writeU00(pattern, file, fileName);
}

static const unsigned char vipDecodingTable[] = {
    0x2E, 0x82, 0xE4, 0x6F, 0x38, 0xA9, 0xDC, 0xC6, 0x7B, 0xB6, 0x28, 0xAC, 0xFD, 0xAA, 0x8A, 0x4E,
    0x76, 0x2E, 0xF0, 0xE4, 0x25, 0x1B, 0x8A, 0x68, 0x4E, 0x92, 0xB9, 0xB4, 0x95, 0xF0, 0x3E, 0xEF,
    0xF7, 0x40, 0x24, 0x18, 0x39, 0x31, 0xBB, 0xE1, 0x53, 0xA8, 0x1F, 0xB1, 0x3A, 0x07, 0xFB, 0xCB,
    0xE6, 0x00, 0x81, 0x50, 0x0E, 0x40, 0xE1, 0x2C, 0x73, 0x50, 0x0D, 0x91, 0xD6, 0x0A, 0x5D, 0xD6,
    0x8B, 0xB8, 0x62, 0xAE, 0x47, 0x00, 0x53, 0x5A, 0xB7, 0x80, 0xAA, 0x28, 0xF7, 0x5D, 0x70, 0x5E,
    0x2C, 0x0B, 0x98, 0xE3, 0xA0, 0x98, 0x60, 0x47, 0x89, 0x9B, 0x82, 0xFB, 0x40, 0xC9, 0xB4, 0x00,
    0x0E, 0x68, 0x6A, 0x1E, 0x09, 0x85, 0xC0, 0x53, 0x81, 0xD1, 0x98, 0x89, 0xAF, 0xE8, 0x85, 0x4F,
    0xE3, 0x69, 0x89, 0x03, 0xA1, 0x2E, 0x8F, 0xCF, 0xED, 0x91, 0x9F, 0x58, 0x1E, 0xD6, 0x84, 0x3C,
    0x09, 0x27, 0xBD, 0xF4, 0xC3, 0x90, 0xC0, 0x51, 0x1B, 0x2B, 0x63, 0xBC, 0xB9, 0x3D, 0x40, 0x4D,
    0x62, 0x6F, 0xE0, 0x8C, 0xF5, 0x5D, 0x08, 0xFD, 0x3D, 0x50, 0x36, 0xD7, 0xC9, 0xC9, 0x43, 0xE4,
    0x2D, 0xCB, 0x95, 0xB6, 0xF4, 0x0D, 0xEA, 0xC2, 0xFD, 0x66, 0x3F, 0x5E, 0xBD, 0x69, 0x06, 0x2A,
    0x03, 0x19, 0x47, 0x2B, 0xDF, 0x38, 0xEA, 0x4F, 0x80, 0x49, 0x95, 0xB2, 0xD6, 0xF9, 0x9A, 0x75,
    0xF4, 0xD8, 0x9B, 0x1D, 0xB0, 0xA4, 0x69, 0xDB, 0xA9, 0x21, 0x79, 0x6F, 0xD8, 0xDE, 0x33, 0xFE,
    0x9F, 0x04, 0xE5, 0x9A, 0x6B, 0x9B, 0x73, 0x83, 0x62, 0x7C, 0xB9, 0x66, 0x76, 0xF2, 0x5B, 0xC9,
    0x5E, 0xFC, 0x74, 0xAA, 0x6C, 0xF1, 0xCD, 0x93, 0xCE, 0xE9, 0x80, 0x53, 0x03, 0x3B, 0x97, 0x4B,
    0x39, 0x76, 0xC2, 0xC1, 0x56, 0xCB, 0x70, 0xFD, 0x3B, 0x3E, 0x52, 0x57, 0x81, 0x5D, 0x56, 0x8D,
    0x51, 0x90, 0xD4, 0x76, 0xD7, 0xD5, 0x16, 0x02, 0x6D, 0xF2, 0x4D, 0xE1, 0x0E, 0x96, 0x4F, 0xA1,
    0x3A, 0xA0, 0x60, 0x59, 0x64, 0x04, 0x1A, 0xE4, 0x67, 0xB6, 0xED, 0x3F, 0x74, 0x20, 0x55, 0x1F,
    0xFB, 0x23, 0x92, 0x91, 0x53, 0xC8, 0x65, 0xAB, 0x9D, 0x51, 0xD6, 0x73, 0xDE, 0x01, 0xB1, 0x80,
    0xB7, 0xC0, 0xD6, 0x80, 0x1C, 0x2E, 0x3C, 0x83, 0x63, 0xEE, 0xBC, 0x33, 0x25, 0xE2, 0x0E, 0x7A,
    0x67, 0xDE, 0x3F, 0x71, 0x14, 0x49, 0x9C, 0x92, 0x93, 0x0D, 0x26, 0x9A, 0x0E, 0xDA, 0xED, 0x6F,
    0xA4, 0x89, 0x0C, 0x1B, 0xF0, 0xA1, 0xDF, 0xE1, 0x9E, 0x3C, 0x04, 0x78, 0xE4, 0xAB, 0x6D, 0xFF,
    0x9C, 0xAF, 0xCA, 0xC7, 0x88, 0x17, 0x9C, 0xE5, 0xB7, 0x33, 0x6D, 0xDC, 0xED, 0x8F, 0x6C, 0x18,
    0x1D, 0x71, 0x06, 0xB1, 0xC5, 0xE2, 0xCF, 0x13, 0x77, 0x81, 0xC5, 0xB7, 0x0A, 0x14, 0x0A, 0x6B,
    0x40, 0x26, 0xA0, 0x88, 0xD1, 0x62, 0x6A, 0xB3, 0x50, 0x12, 0xB9, 0x9B, 0xB5, 0x83, 0x9B, 0x37
};

static int vipDecodeByte(unsigned char b)
{
    if (b >= 0x80)
        return (-(unsigned char)(~b + 1));
    return b;
}

static int vipDecodeStitchType(unsigned char b)
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

static unsigned char* vipDecompressData(unsigned char* input, int compressedInputLength, int decompressedContentLength)
{
    unsigned char* decompressedData = (unsigned char*)malloc(decompressedContentLength);
    if (!decompressedData) {
        embLog("ERROR: format-vip.c vipDecompressData(), cannot allocate memory for decompressedData\n");
        return 0;
    }
    husExpand((unsigned char*)input, decompressedData, compressedInputLength, 10);
    return decompressedData;
}

typedef struct VipHeader_ {
    int magicCode;
    int numberOfStitches;
    int numberOfColors;
    short postitiveXHoopSize;
    short postitiveYHoopSize;
    short negativeXHoopSize;
    short negativeYHoopSize;
    int attributeOffset;
    int xOffset;
    int yOffset;
    unsigned char stringVal[8];
    short unknown;
    int colorLength;
} VipHeader;

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readVip(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int fileLength;
    int i;
    unsigned char prevByte = 0;
    unsigned char *attributeData = 0, *decodedColors = 0, *attributeDataDecompressed = 0;
    unsigned char *xData = 0, *xDecompressed = 0, *yData = 0, *yDecompressed = 0;
    VipHeader header;

    embFile_seek(file, 0x0, SEEK_END);
    fileLength = embFile_tell(file);
    embFile_seek(file, 0x00, SEEK_SET);
    header.magicCode = binaryReadInt32(file);
    header.numberOfStitches = binaryReadInt32(file);
    header.numberOfColors = binaryReadInt32(file);

    header.postitiveXHoopSize = binaryReadInt16(file);
    header.postitiveYHoopSize = binaryReadInt16(file);
    header.negativeXHoopSize = binaryReadInt16(file);
    header.negativeYHoopSize = binaryReadInt16(file);

    header.attributeOffset = binaryReadInt32(file);
    header.xOffset = binaryReadInt32(file);
    header.yOffset = binaryReadInt32(file);

    /*stringVal = (unsigned char*)malloc(sizeof(unsigned char)*8); TODO: review this and uncomment or remove
        if(!stringVal) { embLog("ERROR: format-vip.c readVip(), cannot allocate memory for stringVal\n"); return 0; }
     */

    binaryReadBytes(file, header.stringVal, 8); /* TODO: check return value */

    header.unknown = binaryReadInt16(file);

    header.colorLength = binaryReadInt32(file);
    decodedColors = (unsigned char*)malloc(header.numberOfColors * 4);
    if (!decodedColors) {
        embLog("ERROR: format-vip.c readVip(), cannot allocate memory for decodedColors\n");
        return 0;
    }
    for (i = 0; i < header.numberOfColors * 4; ++i) {
        unsigned char inputByte = binaryReadByte(file);
        unsigned char tmpByte = (unsigned char)(inputByte ^ vipDecodingTable[i]);
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
        embPattern_addThread(pattern, thread);
    }
    embFile_seek(file, header.attributeOffset, SEEK_SET);
    attributeData = (unsigned char*)malloc(header.xOffset - header.attributeOffset);
    if (!attributeData) {
        embLog("ERROR: format-vip.c readVip(), cannot allocate memory for attributeData\n");
        return 0;
    }
    binaryReadBytes(file, attributeData, header.xOffset - header.attributeOffset); /* TODO: check return value */
    attributeDataDecompressed = vipDecompressData(attributeData, header.xOffset - header.attributeOffset, header.numberOfStitches);

    embFile_seek(file, header.xOffset, SEEK_SET);
    xData = (unsigned char*)malloc(header.yOffset - header.xOffset);
    if (!xData) {
        embLog("ERROR: format-vip.c readVip(), cannot allocate memory for xData\n");
        return 0;
    }
    binaryReadBytes(file, xData, header.yOffset - header.xOffset); /* TODO: check return value */
    xDecompressed = vipDecompressData(xData, header.yOffset - header.xOffset, header.numberOfStitches);

    embFile_seek(file, header.yOffset, SEEK_SET);
    yData = (unsigned char*)malloc(fileLength - header.yOffset);
    if (!yData) {
        embLog("ERROR: format-vip.c readVip(), cannot allocate memory for yData\n");
        return 0;
    }
    binaryReadBytes(file, yData, fileLength - header.yOffset); /* TODO: check return value */
    yDecompressed = vipDecompressData(yData, fileLength - header.yOffset, header.numberOfStitches);

    for (i = 0; i < header.numberOfStitches; i++) {
        embPattern_addStitchRel(pattern,
            vipDecodeByte(xDecompressed[i]) / 10.0,
            vipDecodeByte(yDecompressed[i]) / 10.0,
            vipDecodeStitchType(attributeDataDecompressed[i]), 1);
    }
    embPattern_addStitchRel(pattern, 0, 0, END, 1);

    free(attributeData);
    free(xData);
    free(yData);
    free(attributeDataDecompressed);
    free(xDecompressed);
    free(yDecompressed);

    return 1;
}

static unsigned char* vipCompressData(unsigned char* input, int decompressedInputSize, int* compressedSize)
{
    unsigned char* compressedData = (unsigned char*)malloc(sizeof(unsigned char) * decompressedInputSize * 2);
    if (!compressedData) {
        embLog("ERROR: format-vip.c vipCompressData(), cannot allocate memory for compressedData\n");
        return 0;
    }
    *compressedSize = husCompress(input, (unsigned long)decompressedInputSize, compressedData, 10, 0);
    return compressedData;
}

static unsigned char vipEncodeByte(double f)
{
    return (unsigned char)(int)roundDouble(f);
}

static unsigned char vipEncodeStitchType(int st)
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

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeVip(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor, attributeSize = 0,
                                              xCompressedSize = 0, yCompressedSize = 0;
    EmbVector previous;
    EmbStitch st;
    int flags = 0, i;
    unsigned char *xValues, *yValues, *attributeValues, *attributeCompressed = 0,
                                                        *xCompressed = 0, *yCompressed = 0, *decodedColors = 0, *encodedColors = 0,
                                                        prevByte = 0;

    stitchCount = pattern->stitchList->count;
    minColors = pattern->threads->count;
    decodedColors = (unsigned char*)malloc(minColors << 2);
    if (!decodedColors)
        return 0;
    encodedColors = (unsigned char*)malloc(minColors << 2);
    if (encodedColors) /* TODO: review this line. It looks clearly wrong. If not, note why. */
    {
        free(decodedColors);
        decodedColors = 0;
        return 0;
    }
    /* embPattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */

    patternColor = minColors;
    if (minColors > 24)
        minColors = 24;

    binaryWriteUInt(file, 0x0190FC5D);
    binaryWriteUInt(file, stitchCount);
    binaryWriteUInt(file, minColors);

    boundingRect = embPattern_calcBoundingBox(pattern);
    binaryWriteShort(file, (short)roundDouble(boundingRect.right * 10.0));
    binaryWriteShort(file, (short)-roundDouble(boundingRect.top * 10.0 - 1.0));
    binaryWriteShort(file, (short)roundDouble(boundingRect.left * 10.0));
    binaryWriteShort(file, (short)-roundDouble(boundingRect.bottom * 10.0 - 1.0));

    binaryWriteUInt(file, 0x38 + (minColors << 3));

    xValues = (unsigned char*)malloc(sizeof(unsigned char) * (stitchCount));
    yValues = (unsigned char*)malloc(sizeof(unsigned char) * (stitchCount));
    attributeValues = (unsigned char*)malloc(sizeof(unsigned char) * (stitchCount));
    if (xValues && yValues && attributeValues) {
        previous.x = 0.0;
        previous.y = 0.0;
        for (i = 0; i < pattern->stitchList->count; i++) {
            st = pattern->stitchList->stitch[i];
            xValues[i] = vipEncodeByte((st.x - previous.x) * 10.0);
            yValues[i] = vipEncodeByte((st.y - previous.y) * 10.0);
            previous.x = st.x;
            previous.y = st.y;
            attributeValues[i] = vipEncodeStitchType(st.flags);
        }
        attributeCompressed = vipCompressData(attributeValues, stitchCount, &attributeSize);
        xCompressed = vipCompressData(xValues, stitchCount, &xCompressedSize);
        yCompressed = vipCompressData(yValues, stitchCount, &yCompressedSize);

        binaryWriteUInt(file, (unsigned int)(0x38 + (minColors << 3) + attributeSize));
        binaryWriteUInt(file, (unsigned int)(0x38 + (minColors << 3) + attributeSize + xCompressedSize));
        binaryWriteUInt(file, 0x00000000);
        binaryWriteUInt(file, 0x00000000);
        binaryWriteUShort(file, 0x0000);

        binaryWriteInt(file, minColors << 2);

        for (i = 0; i < minColors; i++) {
            int byteChunk = i << 2;
            EmbColor currentColor = pattern->threads->thread[i].color;
            decodedColors[byteChunk] = currentColor.r;
            decodedColors[byteChunk + 1] = currentColor.g;
            decodedColors[byteChunk + 2] = currentColor.b;
            decodedColors[byteChunk + 3] = 0x01;
        }

        for (i = 0; i < minColors << 2; ++i) {
            unsigned char tmpByte = (unsigned char)(decodedColors[i] ^ vipDecodingTable[i]);
            prevByte = (unsigned char)(tmpByte ^ prevByte);
            binaryWriteByte(file, prevByte);
        }
        for (i = 0; i <= minColors; i++) {
            binaryWriteInt(file, 1);
        }
        binaryWriteUInt(file, 0); /* string length */
        binaryWriteShort(file, 0);
        binaryWriteBytes(file, (char*)attributeCompressed, attributeSize);
        binaryWriteBytes(file, (char*)xCompressed, xCompressedSize);
        binaryWriteBytes(file, (char*)yCompressed, yCompressedSize);
    }

    if (attributeCompressed)
        free(attributeCompressed);
    if (xCompressed)
        free(xCompressed);
    if (yCompressed)
        free(yCompressed);

    if (attributeValues)
        free(attributeValues);
    if (xValues)
        free(xValues);
    if (yValues)
        free(yValues);

    if (decodedColors)
        free(decodedColors);
    if (encodedColors)
        free(encodedColors);

    return 1;
}

static unsigned char* vp3ReadString(EmbFile* file)
{
    int stringLength = 0;
    unsigned char* charString = 0;
    if (!file) {
        embLog("ERROR: format-vp3.c vp3ReadString(), file argument is null\n");
        return 0;
    }
    stringLength = binaryReadInt16BE(file);
    charString = (unsigned char*)malloc(stringLength);
    if (!charString) {
        embLog("ERROR: format-vp3.c vp3ReadString(), cannot allocate memory for charString\n");
        return 0;
    }
    binaryReadBytes(file, charString, stringLength); /* TODO: check return value */
    return charString;
}

static int vp3Decode(unsigned char inputByte)
{
    if (inputByte > 0x80) {
        return (int)-((unsigned char)((~inputByte) + 1));
    }
    return ((int)inputByte);
}

static short vp3DecodeInt16(unsigned short inputByte)
{
    if (inputByte > 0x8000) {
        return -((short)((~inputByte) + 1));
    }
    return ((short)inputByte);
}

typedef struct _vp3Hoop {
    int right;
    int bottom;
    int left;
    int top;
    int threadLength;
    char unknown2;
    unsigned char numberOfColors;
    unsigned short unknown3;
    int unknown4;
    int numberOfBytesRemaining;

    int xOffset;
    int yOffset;

    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;

    /* Centered hoop dimensions */
    int right2;
    int left2;
    int bottom2;
    int top2;

    int width;
    int height;
} vp3Hoop;

static vp3Hoop vp3ReadHoopSection(EmbFile* file)
{
    vp3Hoop hoop;

    if (!file) {
        embLog("ERROR: format-vp3.c vp3ReadHoopSection(), file argument is null\n");
        hoop.bottom = 0;
        hoop.left = 0;
        hoop.right = 0;
        hoop.top = 0;
        return hoop;
    }

    hoop.right = binaryReadInt32BE(file);
    hoop.bottom = binaryReadInt32BE(file);
    hoop.left = binaryReadInt32BE(file);
    hoop.top = binaryReadInt32BE(file);

    hoop.threadLength = binaryReadInt32(file); /* yes, it seems this is _not_ big endian */
    hoop.unknown2 = binaryReadByte(file);
    hoop.numberOfColors = binaryReadByte(file);
    hoop.unknown3 = binaryReadInt16BE(file);
    hoop.unknown4 = binaryReadInt32BE(file);
    hoop.numberOfBytesRemaining = binaryReadInt32BE(file);

    hoop.xOffset = binaryReadInt32BE(file);
    hoop.yOffset = binaryReadInt32BE(file);

    hoop.byte1 = binaryReadByte(file);
    hoop.byte2 = binaryReadByte(file);
    hoop.byte3 = binaryReadByte(file);

    /* Centered hoop dimensions */
    hoop.right2 = binaryReadInt32BE(file);
    hoop.left2 = binaryReadInt32BE(file);
    hoop.bottom2 = binaryReadInt32BE(file);
    hoop.top2 = binaryReadInt32BE(file);

    hoop.width = binaryReadInt32BE(file);
    hoop.height = binaryReadInt32BE(file);
    return hoop;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readVp3(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char magicString[5];
    unsigned char some;
    unsigned char* softwareVendorString = 0;
    unsigned char v1;
    /* unsigned char v2, ..., v18; */
    unsigned char* anotherSoftwareVendorString = 0;
    int numberOfColors;
    long colorSectionOffset;
    unsigned char magicCode[6];
    short someShort;
    unsigned char someByte;
    int bytesRemainingInFile;
    unsigned char* fileCommentString = 0; /* some software writes used settings here */
    int hoopConfigurationOffset;
    unsigned char* anotherCommentString = 0;
    int i;

    binaryReadBytes(file, magicString, 5); /* %vsm% */ /* TODO: check return value */

    some = binaryReadByte(file); /* 0 */
    softwareVendorString = vp3ReadString(file);
    someShort = binaryReadInt16(file);
    someByte = binaryReadByte(file);
    bytesRemainingInFile = binaryReadInt32(file);
    fileCommentString = vp3ReadString(file);
    hoopConfigurationOffset = (int)embFile_tell(file);

    vp3ReadHoopSection(file);

    anotherCommentString = vp3ReadString(file);

    /* TODO: review v1 thru v18 variables and use emb_unused() if needed */
    for (i = 0; i < 18; i++) {
        v1 = binaryReadByte(file);
    }

    binaryReadBytes(file, magicCode, 6); /* 0x78 0x78 0x55 0x55 0x01 0x00 */ /* TODO: check return value */

    anotherSoftwareVendorString = vp3ReadString(file);

    numberOfColors = binaryReadInt16BE(file);
    embLog("ERROR: format-vp3.c Number of Colors: %d\n" /*, numberOfColors */);
    colorSectionOffset = (int)embFile_tell(file);

    for (i = 0; i < numberOfColors; i++) {
        EmbThread t;
        char tableSize;
        int startX, startY, offsetToNextColorX, offsetToNextColorY;
        unsigned char *threadColorNumber, *colorName, *threadVendor;
        int unknownThreadString, numberOfBytesInColor;

        embFile_seek(file, colorSectionOffset, SEEK_SET);
        embLog("ERROR: format-vp3.c Color Check Byte #1: 0 == %d\n" /*, binaryReadByte(file)*/);
        embLog("ERROR: format-vp3.c Color Check Byte #2: 5 == %d\n" /*, binaryReadByte(file)*/);
        embLog("ERROR: format-vp3.c Color Check Byte #3: 0 == %d\n" /*, binaryReadByte(file)*/);
        colorSectionOffset = binaryReadInt32BE(file);
        colorSectionOffset += embFile_tell(file);
        startX = binaryReadInt32BE(file);
        startY = binaryReadInt32BE(file);
        embPattern_addStitchAbs(pattern, startX / 1000.0, -startY / 1000.0, JUMP, 1);

        tableSize = binaryReadByte(file);
        binaryReadByte(file);
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        embPattern_addThread(pattern, t);
        embFile_seek(file, 6 * tableSize - 1, SEEK_CUR);

        threadColorNumber = vp3ReadString(file);
        colorName = vp3ReadString(file);
        threadVendor = vp3ReadString(file);

        offsetToNextColorX = binaryReadInt32BE(file);
        offsetToNextColorY = binaryReadInt32BE(file);

        unknownThreadString = binaryReadInt16BE(file);
        embFile_seek(file, unknownThreadString, SEEK_CUR);
        numberOfBytesInColor = binaryReadInt32BE(file);
        embFile_seek(file, 0x3, SEEK_CUR);
        while (embFile_tell(file) < colorSectionOffset - 1) {
            int lastFilePosition = embFile_tell(file);

            int x = vp3Decode(binaryReadByte(file));
            int y = vp3Decode(binaryReadByte(file));
            if (x == 0x80) {
                switch (y) {
                case 0x00:
                case 0x03:
                    break;
                case 0x01:
                    x = vp3DecodeInt16(binaryReadUInt16BE(file));
                    y = vp3DecodeInt16(binaryReadUInt16BE(file));
                    binaryReadInt16BE(file);
                    embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, TRIM, 1);
                    break;
                default:
                    break;
                }
            } else {
                embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, NORMAL, 1);
            }

            if (embFile_tell(file) == lastFilePosition) {
                embLog("ERROR: format-vp3.c could not read stitch block in entirety\n");
                return 0;
            }
        }
        if (i + 1 < numberOfColors)
            embPattern_addStitchRel(pattern, 0, 0, STOP, 1);
    }

    embPattern_flipVertical(pattern);

    return 1;
}

void vp3WriteStringLen(EmbFile* file, const char* str, int len)
{
    binaryWriteUShortBE(file, len);
    binaryWriteBytes(file, str, len);
}

void vp3WriteString(EmbFile* file, const char* str)
{
    vp3WriteStringLen(file, str, strlen(str));
}

void vp3PatchByteCount(EmbFile* file, int offset, int adjustment)
{
    int currentPos = embFile_tell(file);
    embFile_seek(file, offset, SEEK_SET);
    embLog("Patching byte count: \n" /*, currentPos - offset + adjustment */);
    binaryWriteIntBE(file, currentPos - offset + adjustment);
    embFile_seek(file, currentPos, SEEK_SET);
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeVp3(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbRect bounds;
    int remainingBytesPos, remainingBytesPos2;
    int colorSectionStitchBytes;
    int first = 1, i;
    int numberOfColors = 0;
    EmbColor color = { 0xFE, 0xFE, 0xFE };
    EmbStitch st;

    bounds = embPattern_calcBoundingBox(pattern);

    embPattern_correctForMaxStitchLength(pattern, 3200.0, 3200.0); /* VP3 can encode signed 16bit deltas */

    embPattern_flipVertical(pattern);

    binaryWriteBytes(file, "%vsm%", 5);
    binaryWriteByte(file, 0);
    vp3WriteString(file, "Embroidermodder");
    binaryWriteByte(file, 0);
    binaryWriteByte(file, 2);
    binaryWriteByte(file, 0);

    remainingBytesPos = embFile_tell(file);
    binaryWriteInt(file, 0); /* placeholder */
    vp3WriteString(file, "");
    binaryWriteIntBE(file, bounds.right * 1000);
    binaryWriteIntBE(file, bounds.bottom * 1000);
    binaryWriteIntBE(file, bounds.left * 1000);
    binaryWriteIntBE(file, bounds.top * 1000);
    binaryWriteInt(file, 0); /* this would be some (unknown) function of thread length */
    binaryWriteByte(file, 0);

    numberOfColors = 0;

    int flag;
    EmbColor newColor;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];

        /* pointer = mainPointer; */
        flag = st.flags;
        newColor = pattern->threads->thread[st.color].color;
        if (newColor.r != color.r || newColor.g != color.g || newColor.b != color.b) {
            numberOfColors++;
            color.r = newColor.r;
            color.g = newColor.g;
            color.b = newColor.b;
        } else if (flag & END || flag & STOP) {
            numberOfColors++;
        }

        while (flag == pattern->stitchList->stitch[i].flags) {
            i++;
        }
        /* mainPointer = pointer; */
    }

    binaryWriteByte(file, numberOfColors);
    binaryWriteByte(file, 12);
    binaryWriteByte(file, 0);
    binaryWriteByte(file, 1);
    binaryWriteByte(file, 0);
    binaryWriteByte(file, 3);
    binaryWriteByte(file, 0);

    remainingBytesPos2 = embFile_tell(file);
    binaryWriteInt(file, 0); /* placeholder */

    binaryWriteIntBE(file, 0); /* origin X */
    binaryWriteIntBE(file, 0); /* origin Y */
    binaryWriteByte(file, 0);
    binaryWriteByte(file, 0);
    binaryWriteByte(file, 0);

    binaryWriteIntBE(file, bounds.right * 1000);
    binaryWriteIntBE(file, bounds.bottom * 1000);
    binaryWriteIntBE(file, bounds.left * 1000);
    binaryWriteIntBE(file, bounds.top * 1000);

    binaryWriteIntBE(file, (bounds.right - bounds.left) * 1000);
    binaryWriteIntBE(file, (bounds.bottom - bounds.top) * 1000);

    vp3WriteString(file, "");
    binaryWriteShortBE(file, 25700);
    binaryWriteIntBE(file, 4096);
    binaryWriteIntBE(file, 0);
    binaryWriteIntBE(file, 0);
    binaryWriteIntBE(file, 4096);

    binaryWriteBytes(file, "xxPP\x01\0", 6);
    vp3WriteString(file, "");
    binaryWriteShortBE(file, numberOfColors);

    for (i = 0; i < pattern->stitchList->count; i++) {
        char colorName[8] = { 0 };
        double lastX, lastY;
        int colorSectionLengthPos;
        EmbStitch s;
        int lastColor;

        if (!first) {
            binaryWriteByte(file, 0);
        }
        binaryWriteByte(file, 0);
        binaryWriteByte(file, 5);
        binaryWriteByte(file, 0);

        colorSectionLengthPos = embFile_tell(file);
        binaryWriteInt(file, 0); /* placeholder */

        /* pointer = mainPointer; */
        color = pattern->threads->thread[st.color].color;

        if (first && (st.flags & JUMP) && pattern->stitchList->stitch[i + 1].flags & JUMP) {
            i++;
        }

        s = pattern->stitchList->stitch[i];
        embLog("format-vp3.c DEBUG %d, %lf, %lf\n" /*, s.flags, s.x, s.y */);
        binaryWriteIntBE(file, s.x * 1000);
        binaryWriteIntBE(file, -s.y * 1000);
        /* pointer = pointer->next; */

        first = 0;

        lastX = s.x;
        lastY = s.y;
        lastColor = s.color;

        binaryWriteByte(file, 1);
        binaryWriteByte(file, 0);

        embLog("format-vp3.c writeVp3(), switching to color (%d, %d, %d)\n" /*, color.r, color.g, color.b */);
        binaryWriteByte(file, color.r);
        binaryWriteByte(file, color.g);
        binaryWriteByte(file, color.b);

        binaryWriteByte(file, 0);
        binaryWriteByte(file, 0);
        binaryWriteByte(file, 0);
        binaryWriteByte(file, 5);
        binaryWriteByte(file, 40);

        vp3WriteString(file, "");

        sprintf(colorName, "#%02x%02x%02x", color.b, color.g, color.r);

        vp3WriteString(file, colorName);
        vp3WriteString(file, "");

        binaryWriteIntBE(file, 0);
        binaryWriteIntBE(file, 0);

        vp3WriteStringLen(file, "\0", 1);

        colorSectionStitchBytes = embFile_tell(file);
        binaryWriteInt(file, 0); /* placeholder */

        binaryWriteByte(file, 10);
        binaryWriteByte(file, 246);
        binaryWriteByte(file, 0);

        for (i = 0; i < pattern->stitchList->count; i++) {
            int dx, dy;

            EmbStitch s = pattern->stitchList->stitch[i];
            if (s.color != lastColor) {
                break;
            }
            if (s.flags & END || s.flags & STOP) {
                break;
            }
            dx = (s.x - lastX) * 10;
            dy = (s.y - lastY) * 10;
            lastX = lastX + dx / 10.0; /* output is in ints, ensure rounding errors do not sum up */
            lastY = lastY + dy / 10.0;

            if (dx < -127 || dx > 127 || dy < -127 || dy > 127) {
                binaryWriteByte(file, 128);
                binaryWriteByte(file, 1);
                binaryWriteShortBE(file, dx);
                binaryWriteShortBE(file, dy);
                binaryWriteByte(file, 128);
                binaryWriteByte(file, 2);
            } else {
                binaryWriteByte(file, dx);
                binaryWriteByte(file, dy);
            }
        }

        vp3PatchByteCount(file, colorSectionStitchBytes, -4);
        vp3PatchByteCount(file, colorSectionLengthPos, -3);
        /* mainPointer = pointer; */
    }

    vp3PatchByteCount(file, remainingBytesPos2, -4);
    vp3PatchByteCount(file, remainingBytesPos, -4);

    embPattern_flipVertical(pattern);

    return 1;
}

static char xxxDecodeByte(unsigned char inputByte)
{
    if (inputByte >= 0x80)
        return (char)((-~inputByte) - 1);
    return ((char)inputByte);
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readXxx(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b0, b1;
    int dx = 0, dy = 0;
    int flags, numberOfColors, paletteOffset, i;
    char endOfStream = 0;
    char thisStitchJump = 0;
    EmbThread thread;
    EmbStitch st;

    embFile_seek(file, 0x27, SEEK_SET);
    numberOfColors = binaryReadInt16(file);
    embFile_seek(file, 0xFC, SEEK_SET);
    paletteOffset = binaryReadInt32(file);
    embFile_seek(file, paletteOffset + 6, SEEK_SET);

    for (i = 0; i < numberOfColors; i++) {
        binaryReadByte(file);
        thread.color.r = binaryReadByte(file);
        thread.color.g = binaryReadByte(file);
        thread.color.b = binaryReadByte(file);
        embPattern_addThread(pattern, thread);
    }
    embFile_seek(file, 0x100, SEEK_SET);

    for (i = 0; !endOfStream && embFile_tell(file) < paletteOffset; i++) {
        flags = NORMAL;
        if (thisStitchJump)
            flags = TRIM;
        thisStitchJump = 0;
        b0 = binaryReadByte(file);
        b1 = binaryReadByte(file);

        if (b0 == 0x7E || b0 == 0x7D) /* TODO: ARE THERE OTHER BIG JUMP CODES? */
        {
            dx = b1 + (binaryReadByte(file) << 8);
            dx = ((short)dx);
            dy = binaryReadInt16(file);
            flags = TRIM;
        } else if (b0 == 0x7F) {
            if (b1 != 0x17 && b1 != 0x46 && b1 >= 8) /* TODO: LOOKS LIKE THESE CODES ARE IN THE HEADER */
            {
                b0 = 0;
                b1 = 0;
                thisStitchJump = 1;
                flags = STOP;
            } else if (b1 == 1) {
                flags = TRIM;
                b0 = binaryReadByte(file);
                b1 = binaryReadByte(file);
            } else {
                continue;
            }
            dx = xxxDecodeByte(b0);
            dy = xxxDecodeByte(b1);
        } else {
            dx = xxxDecodeByte(b0);
            dy = xxxDecodeByte(b1);
        }
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    /*
    lastStitch = pattern->stitchList;
    secondLast = 0;
    if (lastStitch)
 {
        while (lastStitch->next)
        {
            secondLast = lastStitch;
            lastStitch = lastStitch->next;
        }
        if((!pattern->stitchList) && lastStitch->stitch.flags == STOP && secondLast)
        {
            free(lastStitch);
            lastStitch = 0;
            secondLast->next = NULL;
            embPattern_changeColor(pattern, pattern->currentColorIndex - 1);
        }
    }
    
    Is this trimming the last stitch... and?
    */

    return 1;
}

static void xxxEncodeStop(EmbFile* file, EmbStitch s)
{
    binaryWriteByte(file, (unsigned char)0x7F);
    binaryWriteByte(file, (unsigned char)(s.color + 8));
}

static void xxxEncodeStitch(EmbFile* file, double deltaX, double deltaY, int flags)
{
    if ((flags & (JUMP | TRIM)) && (fabs(deltaX) > 124 || fabs(deltaY) > 124)) {
        binaryWriteByte(file, 0x7E);
        binaryWriteShort(file, (short)deltaX);
        binaryWriteShort(file, (short)deltaY);
    } else {
        /* TODO: Verify this works after changing this to unsigned char */
        binaryWriteByte(file, (unsigned char)roundDouble(deltaX));
        binaryWriteByte(file, (unsigned char)roundDouble(deltaY));
    }
}

static void xxxEncodeDesign(EmbFile* file, EmbPattern* p)
{
    double thisX = 0.0f;
    double thisY = 0.0f;
    double previousX, previousY, deltaX, deltaY;
    EmbStitch s;
    int i;

    if (p->stitchList) {
        thisX = (float)p->stitchList->stitch[0].x;
        thisY = (float)p->stitchList->stitch[0].y;
    } else {
        return;
    }

    for (i = 0; i < p->stitchList->count; i++) {
        s = p->stitchList->stitch[i];
        previousX = thisX;
        previousY = thisY;
        thisX = s.x;
        thisY = s.y;
        deltaX = thisX - previousX;
        deltaY = thisY - previousY;
        if (s.flags & STOP) {
            xxxEncodeStop(file, s);
        } else if (s.flags & END) {
        } else {
            xxxEncodeStitch(file, deltaX * 10.0f, deltaY * 10.0f, s.flags);
        }
    }
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeXxx(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;
    EmbRect rect;
    EmbColor c;
    int endOfStitches;

    embPattern_correctForMaxStitchLength(pattern, 124, 127);

    for (i = 0; i < 0x17; i++) {
        binaryWriteByte(file, 0x00);
    }
    binaryWriteUInt(file, (unsigned int)pattern->stitchList->count);
    for (i = 0; i < 0x0C; i++) {
        binaryWriteByte(file, 0x00);
    }
    binaryWriteUShort(file, (unsigned short)pattern->threads->count);
    binaryWriteShort(file, 0x0000);

    rect = embPattern_calcBoundingBox(pattern);
    binaryWriteShort(file, (short)(embRect_width(rect) * 10.0));
    binaryWriteShort(file, (short)(embRect_height(rect) * 10.0));

    binaryWriteShort(file, (short)(embRect_width(rect) / 2.0 * 10)); /*TODO: xEnd from start point x=0 */
    binaryWriteShort(file, (short)(embRect_height(rect) / 2.0 * 10)); /*TODO: yEnd from start point y=0 */
    binaryWriteShort(file, (short)(embRect_width(rect) / 2.0 * 10)); /*TODO: left from start x = 0     */
    binaryWriteShort(file, (short)(embRect_height(rect) / 2.0 * 10)); /*TODO: bottom from start y = 0   */
    for (i = 0; i < 0xC5; i++) {
        binaryWriteByte(file, 0x00);
    }
    binaryWriteInt(file, 0x0000); /* place holder for end of stitches */

    xxxEncodeDesign(file, pattern);

    endOfStitches = embFile_tell(file);

    embFile_seek(file, 0xFC, SEEK_SET);

    binaryWriteUInt(file, endOfStitches);

    embFile_seek(file, 0, SEEK_END);

    binaryWriteByte(file, 0x7F); /* is this really correct? */
    binaryWriteByte(file, 0x7F);
    binaryWriteByte(file, 0x03);
    binaryWriteByte(file, 0x14);
    binaryWriteByte(file, 0x00);
    binaryWriteByte(file, 0x00);

    for (i = 0; i < 22; i++) {
        if (i < pattern->threads->count) {
            c = pattern->threads->thread[i].color;
            binaryWriteByte(file, 0x00);
            binaryWriteByte(file, c.r);
            binaryWriteByte(file, c.g);
            binaryWriteByte(file, c.b);
        } else {
            binaryWriteUInt(file, 0x01000000);
        }
    }

    binaryWriteByte(file, 0x00);
    binaryWriteByte(file, 0x01);
    return 1;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readZsk(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char b[3];
    int stitchType;
    unsigned char colorNumber;
    EmbThread t;

    embFile_seek(file, 0x230, SEEK_SET);
    colorNumber = binaryReadUInt8(file);
    while (colorNumber != 0) {
        t.color.r = binaryReadUInt8(file);
        t.color.g = binaryReadUInt8(file);
        t.color.b = binaryReadUInt8(file);
        t.catalogNumber = "";
        t.description = "";
        embPattern_addThread(pattern, t);
        embFile_seek(file, 0x48, SEEK_CUR);
        colorNumber = binaryReadUInt8(file);
    }
    embFile_seek(file, 0x2E, SEEK_CUR);

    while (embFile_read(b, 1, 3, file) == 3) {
        stitchType = NORMAL;
        if (b[0] & 0x4) {
            b[2] = -b[2];
        }
        if (b[0] & 0x8) {
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
                stitchType = STOP; /* TODO: need to determine what b[1] is used for.*/
                embPattern_changeColor(pattern, colorNumber - 1);
            }
            b[1] = 0;
            b[2] = 0;
        }
        embPattern_addStitchRel(pattern, b[1] / 10.0, b[2] / 10.0, stitchType, 0);
    }

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeZsk(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeZsk */
}

