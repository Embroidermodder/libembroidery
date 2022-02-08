/*
 * This file is part of libembroidery.
 *
 * Copyright 2021-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "embroidery.h"

#define EMB_BIG_ENDIAN                          0
#define EMB_LITTLE_ENDIAN                       1

#define ENDIAN_HOST                             EMB_LITTLE_ENDIAN

#define EMB_BIT_0            0x01
#define EMB_BIT_1            0x02
#define EMB_BIT_2            0x04
#define EMB_BIT_3            0x08
#define EMB_BIT_4            0x10
#define EMB_BIT_5            0x20
#define EMB_BIT_6            0x40
#define EMB_BIT_7            0x80

#define ELEMENT_XML               0
#define ELEMENT_A                 1
#define ELEMENT_ANIMATE           2
#define ELEMENT_ANIMATE_COLOR     3
#define ELEMENT_ANIMATE_MOTION    4
#define ELEMENT_ANIMATE_TRANSFORM 5
#define ELEMENT_ANIMATION         6
#define ELEMENT_AUDIO             7
#define ELEMENT_CIRCLE            8
#define ELEMENT_DEFS              9
#define ELEMENT_DESC              10
#define ELEMENT_DISCARD           11
#define ELEMENT_ELLIPSE           12
#define ELEMENT_FONT              13
#define ELEMENT_FONT_FACE         14
#define ELEMENT_FONT_FACE_SRC     15
#define ELEMENT_FONT_FACE_URI     16
#define ELEMENT_FOREIGN_OBJECT    17
#define ELEMENT_G                 18
#define ELEMENT_GLYPH             19
#define ELEMENT_HANDLER           20
#define ELEMENT_HKERN             21
#define ELEMENT_IMAGE             22
#define ELEMENT_LINE              23
#define ELEMENT_LINEAR_GRADIENT   24
#define ELEMENT_LISTENER          25
#define ELEMENT_METADATA          26
#define ELEMENT_MISSING_GLYPH     27
#define ELEMENT_MPATH             28
#define ELEMENT_PATH              29
#define ELEMENT_POLYGON           30
#define ELEMENT_POLYLINE          31
#define ELEMENT_PREFETCH          32
#define ELEMENT_RADIAL_GRADIENT   33
#define ELEMENT_RECT              34
#define ELEMENT_SCRIPT            35
#define ELEMENT_SET               36
#define ELEMENT_SOLID_COLOR       37
#define ELEMENT_STOP              38
#define ELEMENT_SVG               39
#define ELEMENT_SWITCH            40
#define ELEMENT_TBREAK            41
#define ELEMENT_TEXT              42
#define ELEMENT_TEXT_AREA         43
#define ELEMENT_TITLE             44
#define ELEMENT_TSPAN             45
#define ELEMENT_USE               46
#define ELEMENT_VIDEO             47
#define ELEMENT_UNKNOWN           48

/* same order as flag_list, to use in jump table */
#define FLAG_TO                       0
#define FLAG_TO_SHORT                 1
#define FLAG_HELP                     2
#define FLAG_HELP_SHORT               3
#define FLAG_FORMATS                  4
#define FLAG_FORMATS_SHORT            5
#define FLAG_QUIET                    6
#define FLAG_QUIET_SHORT              7
#define FLAG_VERBOSE                  8
#define FLAG_VERBOSE_SHORT            9
#define FLAG_VERSION                 10
#define FLAG_VERSION_SHORT           11
#define FLAG_CIRCLE                  12
#define FLAG_CIRCLE_SHORT            13
#define FLAG_ELLIPSE                 14
#define FLAG_ELLIPSE_SHORT           15
#define FLAG_LINE                    16
#define FLAG_LINE_SHORT              17
#define FLAG_POLYGON                 18
#define FLAG_POLYGON_SHORT           19
#define FLAG_POLYLINE                20
#define FLAG_POLYLINE_SHORT          21
#define FLAG_RENDER                  22
#define FLAG_RENDER_SHORT            23
#define FLAG_SATIN                   24
#define FLAG_SATIN_SHORT             25
#define FLAG_STITCH                  26
#define FLAG_STITCH_SHORT            27
#define FLAG_TEST                    28
#define FLAG_FULL_TEST_SUITE         29
#define FLAG_HILBERT_CURVE           30
#define FLAG_SIERPINSKI_TRIANGLE     31
#define FLAG_FILL                    32
#define FLAG_FILL_SHORT              33
#define FLAG_IMAGE_WIDTH             34
#define FLAG_IMAGE_HEIGHT            35
#define FLAG_SIMULATE                36
#define NUM_FLAGS                    37

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

/**
Type of sector
*/
#define CompoundFileSector_MaxRegSector 0xFFFFFFFA
#define CompoundFileSector_DIFAT_Sector 0xFFFFFFFC
#define CompoundFileSector_FAT_Sector   0xFFFFFFFD
#define CompoundFileSector_EndOfChain   0xFFFFFFFE
#define CompoundFileSector_FreeSector   0xFFFFFFFF

/**
Type of directory object
*/
#define ObjectTypeUnknown   0x00 /*!< Probably unallocated    */
#define ObjectTypeStorage   0x01 /*!< a directory type object */
#define ObjectTypeStream    0x02 /*!< a file type object      */
#define ObjectTypeRootEntry 0x05 /*!< the root entry          */

/**
Special values for Stream Identifiers
*/
#define CompoundFileStreamId_MaxRegularStreamId 0xFFFFFFFA /*!< All real stream Ids are less than this */
#define CompoundFileStreamId_NoStream           0xFFFFFFFF /*!< There is no valid stream Id            */

#define SVG_CREATOR_NULL              0
#define SVG_CREATOR_EMBROIDERMODDER   1
#define SVG_CREATOR_ILLUSTRATOR       2
#define SVG_CREATOR_INKSCAPE          3

#define SVG_EXPECT_NULL               0
#define SVG_EXPECT_ELEMENT            1
#define SVG_EXPECT_ATTRIBUTE          2
#define SVG_EXPECT_VALUE              3

/*  SVG_TYPES
 *  ---------
 */
#define SVG_NULL                      0
#define SVG_ELEMENT                   1
#define SVG_PROPERTY                  2
#define SVG_MEDIA_PROPERTY            3
#define SVG_ATTRIBUTE                 4
#define SVG_CATCH_ALL                 5

#define RED_TERM_COLOR      "\x1B[0;31m"
#define GREEN_TERM_COLOR    "\x1B[0;32m"
#define YELLOW_TERM_COLOR   "\x1B[1;33m"
#define RESET_TERM_COLOR       "\033[0m"

/* INTERNAL STRUCTS AND ENUMS
 *******************************************************************/

/* double-indirection file allocation table references */
typedef struct _bcf_file_difat
{
    unsigned int fatSectorCount;
    unsigned int fatSectorEntries[109];
    unsigned int sectorSize;
} bcf_file_difat;

typedef struct _bcf_file_fat
{
    int          fatEntryCount;
    unsigned int fatEntries[255]; /* maybe make this dynamic */
    unsigned int numberOfEntriesInFatSector;
} bcf_file_fat;

typedef struct _bcf_directory_entry
{
    char                         directoryEntryName[32];
    unsigned short               directoryEntryNameLength;
    unsigned char                objectType;
    unsigned char                colorFlag;
    unsigned int                 leftSiblingId;
    unsigned int                 rightSiblingId;
    unsigned int                 childId;
    unsigned char                CLSID[16];
    unsigned int                 stateBits;
    EmbTime                      creationTime;
    EmbTime                      modifiedTime;
    unsigned int                 startingSectorLocation;
    unsigned long                streamSize; /* should be long long but in our case we shouldn't need it, and hard to support on c89 cross platform */
    unsigned int                 streamSizeHigh; /* store the high int of streamsize */
    struct _bcf_directory_entry* next;
} bcf_directory_entry;

typedef struct _bcf_directory
{
    bcf_directory_entry* dirEntries;
    unsigned int         maxNumberOfDirectoryEntries;
    /* TODO: possibly add a directory tree in the future */

} bcf_directory;

typedef struct _bcf_file_header
{
    unsigned char  signature[8];
    unsigned char  CLSID[16]; /* TODO: this should be a separate type */
    unsigned short minorVersion;
    unsigned short majorVersion;
    unsigned short byteOrder;
    unsigned short sectorShift;
    unsigned short miniSectorShift;
    unsigned short reserved1;
    unsigned int   reserved2;
    unsigned int   numberOfDirectorySectors;
    unsigned int   numberOfFATSectors;
    unsigned int   firstDirectorySectorLocation;
    unsigned int   transactionSignatureNumber;
    unsigned int   miniStreamCutoffSize;
    unsigned int   firstMiniFATSectorLocation;
    unsigned int   numberOfMiniFatSectors;
    unsigned int   firstDifatSectorLocation;
    unsigned int   numberOfDifatSectors;
} bcf_file_header;

typedef struct _bcf_file
{
    bcf_file_header header;   /*! The header for the CompoundFile */
    bcf_file_difat* difat;    /*! The "Double Indirect FAT" for the CompoundFile */
    bcf_file_fat* fat;        /*! The File Allocation Table for the Compound File */
    bcf_directory* directory; /*! The directory for the CompoundFile */
} bcf_file;

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

typedef struct SvgAttribute_
{
    char* name;
    char* value;
} SvgAttribute;

/* INTERNAL FUNCTION PROTOTYPES
 *******************************************************************/

static float binaryReadFloat(FILE* file);
static void binaryReadString(FILE* file, char *buffer, int maxLength);
static void binaryReadUnicodeString(FILE* file, char *buffer, const int stringLength);

static void binaryWriteShort(FILE* file, short data);
static void binaryWriteShortBE(FILE* file, short data);
static void binaryWriteUShort(FILE* file, unsigned short data);
static void binaryWriteUShortBE(FILE* file, unsigned short data);
static void binaryWriteInt(FILE* file, int data);
static void binaryWriteIntBE(FILE* file, int data);
static void binaryWriteUInt(FILE* file, unsigned int data);
static void binaryWriteUIntBE(FILE* file, unsigned int data);
static void binaryWriteFloat(FILE* file, float data);

static void charReplace(char *s, const char *from, const char *to);
static int stringInArray(const char *s, const char **array);

static char startsWith(const char* pre, const char* str);

static void fpad(FILE *f, char c, int n);
static char *copy_trim(char const *s);
static void inplace_trim(char *s);
static char* emb_optOut(double num, char* str);

static void write_24bit(FILE* file, int);
static int check_header_present(FILE* file, int minimum_header_length);

static short fread_int16(FILE* f);
static unsigned short fread_uint16(FILE* f);
static int fread_int32(FILE* f);
static unsigned int fread_uint32(FILE* f);
static short fread_int16_be(FILE* f);
static unsigned short fread_uint16_be(FILE* f);
static int fread_int32_be(FILE* f);
static unsigned int fread_uint32_be(FILE* f);
static void fwrite_nbytes(FILE* f, void *p, int bytes);
static void fwrite_nbytes_be(FILE* f, void *p, int bytes);

static bcf_file_difat* bcf_difat_create(FILE* file, unsigned int fatSectors, const unsigned int sectorSize);
static unsigned int readFullSector(FILE* file, bcf_file_difat* bcfFile, unsigned int* numberOfDifatEntriesStillToRead);
static unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat);
static void bcf_file_difat_free(bcf_file_difat* difat);

static bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize);
static void loadFatFromSector(bcf_file_fat* fat, FILE* file);
static void bcf_file_fat_free(bcf_file_fat** fat);

static bcf_directory_entry* CompoundFileDirectoryEntry(FILE* file);
static bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries);
static void readNextSector(FILE* file, bcf_directory* dir);
static void bcf_directory_free(bcf_directory** dir);

static bcf_file_header bcfFileHeader_read(FILE* file);
static int bcfFileHeader_isValid(bcf_file_header header);

static int bcfFile_read(FILE* file, bcf_file* bcfFile);
static FILE* GetFile(bcf_file* bcfFile, FILE* file, char* fileToFind);
static void bcf_file_free(bcf_file* bcfFile);

static void readPecStitches(EmbPattern* pattern, FILE* file);
static void writePecStitches(EmbPattern* pattern, FILE* file, const char* filename);

static int emb_readline(FILE* file, char *line, int maxLength);

static int decodeNewStitch(unsigned char value);

static void pfaffEncode(FILE* file, int x, int y, int flags);
static double pfaffDecode(unsigned char a1, unsigned char a2, unsigned char a3);

static unsigned char mitEncodeStitch(double value);
static int mitDecodeStitch(unsigned char value);

static int encode_tajima_ternary(unsigned char b[3], int x, int y);
static void decode_tajima_ternary(unsigned char b[3], int *x, int *y);

static void encode_t01_record(unsigned char b[3], int x, int y, int flags);
static int decode_t01_record(unsigned char b[3], int *x, int *y, int *flags);

static void embColor_read(FILE *file, EmbColor *c, int toRead);
static void embColor_write(FILE *file, EmbColor c, int toWrite);

void testTangentPoints(EmbCircle c, EmbVector p, EmbVector *t0, EmbVector *t1);
void printArcResults(double bulge, EmbArc arc,
                     double centerX,   double centerY,
                     double radius,    double diameter,
                     double chord,
                     double chordMidX, double chordMidY,
                     double sagitta,   double apothem,
                     double incAngle,  char   clockwise);
static void report(int result, char *label);
int create_test_file_1(const char* outf);
int create_test_file_2(const char* outf);
int testEmbCircle(void);
int testEmbCircle_2(void);
int testGeomArc(void);
int testThreadColor(void);
int testEmbFormat(void);
int full_test_matrix(char *fname);

/* DATA 
 *******************************************************************/

EmbThread black_thread = { { 0, 0, 0 }, "Black", "Black" };

static const char *flag_list[] = {
    "--to",
    "-t",
    "--help",
    "-h",
    "--formats",
    "-F",
    "--quiet",
    "-q",
    "--verbose",
    "-V",
    "--version",
    "-v",
    "--circle",
    "-c",
    "--ellipse",
    "-e",
    "--line",
    "-l",
    "--polyline",
    "-P",
    "--polygon",
    "-p",
    "--render",
    "-r",
    "--satin",
    "-s",
    "--stitch",
    "-S",
    "--test",
    "--full-test-suite",
    "--hilbert-curve",
    "--sierpinski-triangle",
    "--fill",
    "-f",
    "--image-width",
    "--image-height",
    "--simulate"
};

static const char *version_string = "embroider v0.1";
static const char *welcome_message = "EMBROIDER\n"
    "    A command line program for machine embroidery.\n"
    "    Copyright 2013-2022 The Embroidermodder Team\n"
    "    Licensed under the terms of the zlib license.\n"
    "\n"
    "    https://github.com/Embroidermodder/libembroidery\n"
    "    https://embroidermodder.org\n";

static EmbColor black = {0,0,0};

/* CODE SECTION
 *******************************************************************/

#include "compress.c"
#include "formats.c"
#include "parsers.c"
#include "thread-color.c"
#include "utility.c"

/* ENCODING
 *******************************************************************
 * The functions in this file are grouped together to aid the developer's
 * understanding of the similarities between the file formats. This also helps
 * reduce errors between reimplementation of the same idea.
 *
 * For example: the Tajima ternary encoding of positions is used by at least 4
 * formats and the only part that changes is the flag encoding.
 */

int decode_t01_record(unsigned char b[3], int *x, int *y, int *flags) {
    decode_tajima_ternary(b, x, y);

    if (b[2] == 0xF3) {
        *flags = END;
    }
    else {
        switch (b[2] & 0xC3) {
        case 0x03:
            *flags = NORMAL;
            break;
        case 0x83:
            *flags = TRIM;
            break;
        case 0xC3:
            *flags = STOP;
            break;
        default:
            *flags = NORMAL;
            break;
        }
    }
    return 1;
}

void encode_t01_record(unsigned char b[3], int x, int y, int flags) {
    if (!encode_tajima_ternary(b, x, y)) {
        return;
    }

    b[2] |= (unsigned char)3;
    if (flags & END) {
        b[0] = 0;
        b[1] = 0;
        b[2] = 0xF3;
    }
    if (flags & (JUMP | TRIM)) {
        b[2] = (unsigned char)(b[2] | 0x83);
    }
    if (flags & STOP) {
        b[2] = (unsigned char)(b[2] | 0xC3);
    }
}

int encode_tajima_ternary(unsigned char b[3], int x, int y)
{
    b[0] = 0;
    b[1] = 0;
    b[2] = 0;

    /* cannot encode values > +121 or < -121. */
    if (x > 121 || x < -121) {
        printf("ERROR: format-t01.c encode_record(), ");
        printf("x is not in valid range [-121,121] , x = %d\n", x);
        return 0;
    }
    if (y > 121 || y < -121) {
        printf("ERROR: format-t01.c encode_record(), ");
        printf("y is not in valid range [-121,121] , y = %d\n", y);
        return 0;
    }

    if (x >= +41) {
        b[2] |= EMB_BIT_2;
        x -= 81;
    }
    if (x <= -41) {
        b[2] |= EMB_BIT_3;
        x += 81;
    }
    if (x >= +14) {
        b[1] |= EMB_BIT_2;
        x -= 27;
    }
    if (x <= -14) {
        b[1] |= EMB_BIT_3;
        x += 27;
    }
    if (x >= +5) {
        b[0] |= EMB_BIT_2;
        x -= 9;
    }
    if (x <= -5) {
        b[0] |= EMB_BIT_3;
        x += 9;
    }
    if (x >= +2) {
        b[1] |= EMB_BIT_0;
        x -= 3;
    }
    if (x <= -2) {
        b[1] |= EMB_BIT_1;
        x += 3;
    }
    if (x >= +1) {
        b[0] |= EMB_BIT_0;
        x -= 1;
    }
    if (x <= -1) {
        b[0] |= EMB_BIT_1;
        x += 1;
    }
    if (x != 0) {
        printf("ERROR: format-dst.c encode_record(), ");
        printf("x should be zero yet x = %d\n", x);
        return 0;
    }
    if (y >= +41) {
        b[2] |= EMB_BIT_5;
        y -= 81;
    }
    if (y <= -41) {
        b[2] |= EMB_BIT_4;
        y += 81;
    }
    if (y >= +14) {
        b[1] |= EMB_BIT_5;
        y -= 27;
    }
    if (y <= -14) {
        b[1] |= EMB_BIT_4;
        y += 27;
    }
    if (y >= +5) {
        b[0] |= EMB_BIT_5;
        y -= 9;
    }
    if (y <= -5) {
        b[0] |= EMB_BIT_4;
        y += 9;
    }
    if (y >= +2) {
        b[1] |= EMB_BIT_7;
        y -= 3;
    }
    if (y <= -2) {
        b[1] |= EMB_BIT_6;
        y += 3;
    }
    if (y >= +1) {
        b[0] |= EMB_BIT_7;
        y -= 1;
    }
    if (y <= -1) {
        b[0] |= EMB_BIT_6;
        y += 1;
    }
    if (y != 0) {
        printf("ERROR: format-dst.c encode_record(), ");
        printf("y should be zero yet y = %d\n", y);
        return 0;
    }
    return 1;
}

void decode_tajima_ternary(unsigned char b[3], int *x, int *y)
{
    *x = 0;
    *y = 0;
    if (b[0] & EMB_BIT_0) {
        *x += 1;
    }
    if (b[0] & EMB_BIT_1) {
        *x -= 1;
    }
    if (b[0] & EMB_BIT_2) {
        *x += 9;
    }
    if (b[0] & EMB_BIT_3) {
        *x -= 9;
    }
    if (b[0] & EMB_BIT_7) {
        *y += 1;
    }
    if (b[0] & EMB_BIT_6) {
        *y -= 1;
    }
    if (b[0] & EMB_BIT_5) {
        *y += 9;
    }
    if (b[0] & EMB_BIT_4) {
        *y -= 9;
    }
    if (b[1] & EMB_BIT_0) {
        *x += 3;
    }
    if (b[1] & EMB_BIT_1) {
        *x -= 3;
    }
    if (b[1] & EMB_BIT_2) {
        *x += 27;
    }
    if (b[1] & EMB_BIT_3) {
        *x -= 27;
    }
    if (b[1] & EMB_BIT_7) {
        *y += 3;
    }
    if (b[1] & EMB_BIT_6) {
        *y -= 3;
    }
    if (b[1] & EMB_BIT_5) {
        *y += 27;
    }
    if (b[1] & EMB_BIT_4) {
        *y -= 27;
    }
    if (b[2] & EMB_BIT_2) {
        *x += 81;
    }
    if (b[2] & EMB_BIT_3) {
        *x -= 81;
    }
    if (b[2] & EMB_BIT_5) {
        *y += 81;
    }
    if (b[2] & EMB_BIT_4) {
        *y -= 81;
    }
}

void pfaffEncode(FILE* file, int dx, int dy, int flags)
{
    unsigned char flagsToWrite = 0;

    if (!file) { printf("ERROR: format-pcs.c pcsEncode(), file argument is null\n"); return; }

    write_24bit(file, dx);
    write_24bit(file, dy);

    if (flags & STOP)
    {
        flagsToWrite |= 0x01;
    }
    if (flags & TRIM)
    {
        flagsToWrite |= 0x04;
    }
    fwrite(&flagsToWrite, 1, 1, file);
}

double pfaffDecode(unsigned char a1, unsigned char a2, unsigned char a3) {
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res) & 0x7FFFFF) - 1));
    }
    return res;
}

unsigned char mitEncodeStitch(double value) {
    if (value < 0) {
        return 0x80 | (unsigned char)(-value);
    }
    return (unsigned char)value;
}

int mitDecodeStitch(unsigned char value) {
    if (value & 0x80) {
        return -(value & 0x1F);
    }
    return value;
}

int decodeNewStitch(unsigned char value) {
    return (int)value;
}

/* FILLS
 *******************************************************************/

const char *rules[] = {"+BF-AFA-FB+", "-AF+BFB+FA-"};

L_system hilbert_curve_l_system = {
    'A', "AB", "F+-", (char**)rules
};

int max_stitches = 100000;

/* This is a slow generation algorithm */
int lindenmayer_system(L_system L, char *state, int iterations, int complete)
{
    /* We know that the full length of the curve has to fit within
     * the number of stitches and we can cancel consecutive +-, -+
     * etc.
     *

Potential reference:

@book{Prusinkiewicz1996Mar,
    author = {Prusinkiewicz, Przemyslaw and Lindenmayer, Aristid and Hanan, J. S. and Fracchia, F. D. and Fowler, D. R. and de Boer, M. J. M. and Mercer, L.},
    title = {{The Algorithmic Beauty of Plants (The Virtual Laboratory)}},
    year = {1996},
    month = {Mar},
    publisher = {Springer}
}
     */
    char *new_state;
    int j;

    if (complete == 0) {
        state[0] = L.axiom;
        state[1] = 0;
        lindenmayer_system(L, state, iterations, complete+1);
        return 0;
    }

    new_state = state + max_stitches*5;

    new_state[0] = 0;

    /* replace letters using rules by copying to new_state */
    for (j=0; j < (int)strlen(state); j++) {
        if (state[j] >= 'A' && state[j] < 'F') {
            strcat(new_state, L.rules[state[j]-'A']);
        }
        if (state[j] == 'F') {
            strcat(new_state, "F");
        }
        if (state[j] == '+') {
            strcat(new_state, "+");
        }
        if (state[j] == '-') {
            strcat(new_state, "-");
        }
    }
    memcpy(state, new_state, strlen(new_state)+1);

    if (complete < iterations) {
        lindenmayer_system(L, state, iterations, complete+1);
    }
    return 0;
}

int hilbert_curve(EmbPattern *pattern, int iterations)
{
    /*
    https://en.wikipedia.org/wiki/Hilbert_curve

    Using the Lindenmayer System, so we can save work across
    different functions.
    */
    char *state;
    int i, position[2], direction;
    double scale = 1.0;

    /* Make the n-th iteration. */
    state = malloc(max_stitches*10);
    lindenmayer_system(hilbert_curve_l_system, state, iterations, 0);

    /* Convert to an embroidery pattern. */
    position[0] = 0;
    position[1] = 0;
    direction = 0;

    for (i = 0; i < (int)strlen(state); i++) {
        if (state[i] == '+') {
            direction = (direction + 1) % 4;
            continue;
        }
        if (state[i] == '-') {
            direction = (direction + 3) % 4;
            continue;
        }
        if (state[i] == 'F') {
            int flags = NORMAL;
            switch (direction) {
            case 0:
            default:
                position[0]--;
                break;
            case 1:
                position[1]++;
                break;
            case 2:
                position[0]++;
                break;
            case 3:
                position[1]--;
                break;
            }
            embPattern_addStitchAbs(pattern, position[0]*scale, position[1]*scale, flags, 0);
        }
    }
    free(state);
    embPattern_end(pattern);
    return 0;
}

/* using the "paper folding" method (find citation) */
void generate_dragon_curve(char *state, int iterations)
{
    int i, length;
    if (iterations == 1) {
        state[0] = 'R';
        state[1] = 0;
        return;
    }
    length = strlen(state);
    for (i=length-1; i>=0; i--) {
        state[2*i+1] = state[i];
        if (i%2 == 0) {
            state[2*i] = 'R';
        } else {
            state[2*i] = 'L';
        }
    }
    state[2*length+1] = 0;
    generate_dragon_curve(state, iterations-1);
}

int dragon_curve(int iterations)
{
    char *state;
    if (iterations > 10) {
        puts("The dragon curve is only supported up to 10 iterations.");
        return 0;
    }
    state = malloc(1<<(iterations+1));
    generate_dragon_curve(state, iterations);
    free(state);
    return 1;
}

#if 0
StitchBlock* BreakIntoColorBlocks(EmbPattern *pattern)
{
    int i;
    int sa2 = new StitchBlock();
    int oldColor = pattern->stitchList->stitch[0].color;
    int color = pattern.ColorList[oldColor];
    sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch s = pattern->stitchList->stitch[i];
        if (s.color != oldColor) {
            yield return sa2;
            sa2 = new StitchBlock();
            color = pattern.ColorList[s.ColorIndex];
            sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
            oldColor = s.ColorIndex;
        }
        int vs = new VectorStitch { Xy = new Point(s.X, s.Y), Color = s.ColorIndex };
        sa2.Stitches.Add(vs);
    }
    yield return sa2;
}



StitchBlock * BreakIntoSeparateObjects(EmbStitchBlock* blocks)
{
    int i, block;
    double previousAngle = 0.0;
    for (block=0; block<blocks->length; block++) {
        int stitches = new List<VectorStitch>();
        block.Stitches[0].Type = VectorStitchType.Contour;
        block.Stitches[block.Stitches.Count - 1].Type = VectorStitchType.Contour;

        for (int i = 0; i < block.Stitches.Count - 2; i++) { /* step 0 */
            double dx = (embVector_relativeX(block.Stitches[i].Xy, block.Stitches[i + 1].Xy, block.Stitches[i + 2].Xy));
            block.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
            block.Stitches[i].Angle = GetAngle(block.Stitches[i], block.Stitches[i + 1]);
            stitches.Add(block.Stitches[i].Clone());
            if (i > 0) {
                if ((block.Stitches[i].Type == VectorStitchType.Contour) && fabs(block.Stitches[i].Angle - previousAngle) > (20/180*embConstantPi)) {
                    yield return
                        new StitchBlock
                            {
                                Stitches = stitches,
                                Angle = stitches.Average(x => x.Angle),
                                Thread = new Thread(block.Thread.Red, block.Thread.Blue, block.Thread.Green)
                            };
                    stitches = new List<VectorStitch>();

                }
            }
        }

        /* step 1 */
        for (i = 1; i < sa.Stitches.Count - 3; i++) {
            if (sa.Stitches[i + 1].Type == VectorStitchType.Contour) {
                float dy = embVector_relativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY);
                float dy2 = embVector_relativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY);
                float dy3 = embVector_relativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY);
                if (dy)
                if (sa.Stitches[i - 1].Type == VectorStitchType.Run || sa.Stitches[i + 1].Type == VectorStitchType.Run) {
                    sa.Stitches[i].Type = VectorStitchType.Tatami;
                }
                else {
                    sa.Stitches[i].Type = VectorStitchType.Satin;
                }
            }
        }
    }
}

StitchObject * FindOutline(EmbStitchBlock* stitchData)
{
    int currColorIndex = 0, sa;
    int pOdd = new List<Point>();
    int pEven = new List<Point>();
    for (sa=0; sa<stitchData->count; sa++) {
        if (sa.Stitches.Count > 0) {
            sa.Stitches[0].Type = VectorStitchType.Contour;
            sa.Stitches[sa.Stitches.Count - 1].Type = VectorStitchType.Contour;
            /* step 0 */
            for (int i = 0; i < sa.Stitches.Count - 2; i++) {
                float dx = (GetRelativeX(sa.Stitches[i].Xy, sa.Stitches[i + 1].Xy, sa.Stitches[i + 2].Xy));
                sa.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
                sa.Stitches[i].Angle = embVector_angle(sa.Stitches[i], sa.Stitches[i + 1]);
            }
            /* step 1 */
            for (int i = 1; i < sa.Stitches.Count - 3; i++) {
                if (sa.Stitches[i + 1].Type == VectorStitchType.Contour) {
                    float dy = embVector_relativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY);
                    float dy2 = embVector_relativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY);
                    float dy3 = embVector_relativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY);
                    if (dy)
                    if (sa.Stitches[i - 1].Type == VectorStitchType.Run || sa.Stitches[i + 1].Type == VectorStitchType.Run) {
                        sa.Stitches[i].Type = VectorStitchType.Tatami;
                    }
                    else {
                        sa.Stitches[i].Type = VectorStitchType.Satin;
                    }
                }
            }
        }


        int oddEven = 0;
        foreach (VectorStitch t in sa.Stitches) {
            if ((t.Type == VectorStitchType.Contour) && (oddEven % 2) == 0) {
                pEven.Add(t.Xy);

                oddEven++;
            }
            else if ((t.Type == VectorStitchType.Contour) && (oddEven % 2) == 1) {
                pOdd.Add(t.Xy);
                oddEven++;
            }
        }
        currColorIndex++;
        int so = new StitchObject { SideOne = pEven, SideTwo = pOdd, ColorIndex = currColorIndex };
        yield return so;
        pEven = new List<Point>();
        pOdd = new List<Point>();
        /* break; */
    }
}

EmbPattern DrawGraphics(EmbPattern p) {
    int stitchData = BreakIntoColorBlocks(p);

    int outBlock = new List<StitchBlock>(BreakIntoSeparateObjects(stitchData));
    foreach(var block in stitchData) {
        foreach (var stitch in block.Stitches) {
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
    foreach (StitchObject stitchObject in objectsFound) {
        if (stitchObject.SideOne.Count > 1 && stitchObject.SideTwo.Count > 1) {
            outPattern.AddColor(new Thread((byte) (r.Next()%256), (byte) (r.Next()%256), (byte) (r.Next()%256),
                                           "none", "None"));
            colorIndex++;
            outPattern.AddStitchRelative(0, 0, StitchTypes.Stop);
            int points = stitchObject.Generate2(75);
            foreach (var point in points) {
                outPattern.AddStitchAbsolute(point.X, point.Y, StitchTypes.Normal);
            }
            break;
            StitchObject stitchObject = objectsFound[1];))
            if (stitchObject.SideOne.Count > 0) {
                outPattern.StitchList.Add(new Stitch(stitchObject.SideOne[0].X, stitchObject.SideOne[0].Y,
                                                     StitchType.Jump, colorIndex));
            }
            foreach (Point t in stitchObject.SideOne) {
            
                outPattern.StitchList.Add(new Stitch(t.X, t.Y,
                                                     StitchType.Normal, colorIndex));
            }
            foreach (Point t in stitchObject.SideTwo) {
                outPattern.StitchList.Add(new Stitch(t.X, t.Y,
                                                     StitchType.Normal, colorIndex));
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

EmbPattern SimplifyOutline(EmbPattern pattern)
{
    int v = new Vertices();
    v.AddRange(pattern.StitchList.Select(point => new Vector2(point.X, point.Y)));
    int output = SimplifyTools.DouglasPeuckerSimplify(v, 10);
    int patternOut = new Pattern();
    foreach (var color in pattern.ColorList)
    {
        patternOut.AddColor(color);
    }

    foreach (var vertex in output)
    {
        patternOut.AddStitchAbsolute(vertex.X, vertex.Y, StitchTypes.Normal);
    }
    patternOut.AddStitchRelative(0, 0, StitchTypes.End);
    return patternOut;
}

bool[] _usePt;
double _distanceTolerance;

/* Removes all collinear points on the polygon. */
Vertices CollinearSimplify(Vertices vertices, float collinearityTolerance)
{
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
        if (embVector_collinear(ref prev, ref current, ref next, collinearityTolerance))
            continue;

        simplified.Add(current);
    }

    return simplified;
}


/* Removes all collinear points on the polygon.
 * Has a default bias of 0
 *
 * param vertices: The polygon that needs simplification.
 * returns: A simplified polygon.
 */
Vertices CollinearSimplify(Vertices vertices)
{
    return CollinearSimplify(vertices, 0);
}

/*
 * Ramer-Douglas-Peucker polygon simplification algorithm.
 * This is the general recursive version that does not use the
 * speed-up technique by using the Melkman convex hull.
 * If you pass in 0, it will remove all collinear points.
 */
Vertices DouglasPeuckerSimplify(Vertices vertices, float distanceTolerance)
{
    _distanceTolerance = distanceTolerance;

    _usePt = new bool[vertices.Count];
    for (int i = 0; i < vertices.Count; i++)
    {
        _usePt[i] = true;
    }
    SimplifySection(vertices, 0, vertices.Count - 1);
    int result = new Vertices();
    result.AddRange(vertices.Where((t, i) => _usePt[i]));
    return result;
}

void SimplifySection(Vertices vertices, int i, int j)
{
    if ((i + 1) == j)
        return;

    Vector2 a = vertices[i];
    Vector2 b = vertices[j];
    double maxDistance = -1.0;
    int maxIndex = i;
    for (int k = i + 1; k < j; k++)
    {
        double distance = DistancePointLine(vertices[k], a, b);

        if (distance > maxDistance)
        {
            maxDistance = distance;
            maxIndex = k;
        }
    }
    if (maxDistance <= _distanceTolerance) {
        for (int k = i + 1; k < j; k++) {
            _usePt[k] = 0;
        }
    }
    else {
        SimplifySection(vertices, i, maxIndex);
        SimplifySection(vertices, maxIndex, j);
    }
}

double DistancePointLine(EmbVector p, EmbVector a, EmbVector b)
{
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

    double r = ((p.X - a.X) * (b.X - a.X) + (p.Y - a.Y) * (b.Y - a.Y))
               /
               ((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y));

    if (r <= 0.0) return DistancePointPoint(p, a);
    if (r >= 1.0) return DistancePointPoint(p, b);


    /* (2)
                    (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)
                s = -----------------------------
                                Curve^2

                Then the distance from C to Point = |s|*Curve.
    */

    double s = ((a.Y - p.Y) * (b.X - a.X) - (a.X - p.X) * (b.Y - a.Y))
               /
               ((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y));

    return fabs(s) * sqrt(((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y)));
}

/ * From physics2d.net * /
public static Vertices ReduceByArea(Vertices vertices, float areaTolerance)
{
    if (vertices.Count <= 3)
        return vertices;

    if (areaTolerance < 0)
    {
        throw new ArgumentOutOfRangeException("areaTolerance", "must be equal to or greater then zero.");
    }

    int result = new Vertices();
    Vector2 v3;
    Vector2 v1 = vertices[vertices.Count - 2];
    Vector2 v2 = vertices[vertices.Count - 1];
    areaTolerance *= 2;
    for (int index = 0; index < vertices.Count; ++index, v2 = v3)
    {
        if (index == vertices.Count - 1)
        {
            if (result.Count == 0)
            {
                throw new ArgumentOutOfRangeException("areaTolerance", "The tolerance is too high!");
            }
            v3 = result[0];
        }
        else
        {
            v3 = vertices[index];
        }
        float old1, old2, new1;
        MathUtils.Cross(ref v1, ref v2, out old1);
        MathUtils.Cross(ref v2, ref v3, out old2);
        MathUtils.Cross(ref v1, ref v3, out new1);
        if (fabs(new1 - (old1 + old2)) > areaTolerance)
        {
            result.Add(v2);
            v1 = v2;
        }
    }
    return result;
}

/* From Eric Jordan's convex decomposition library.
 * Merges all parallel edges in the list of vertices.
 */
void MergeParallelEdges(EmbArray *vertices, float tolerance)
{
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

        embVector_subtract(vertices[i], vertices[lower], &delta0);
        embVector_subtract(vertices[upper], vertices[i], &delta1);
        float norm0 = embVector_length(delta0);
        float norm1 = embVector_length(delta0);

        if (!(norm0 > 0.0f && norm1 > 0.0f) && newNVertices > 3) {
            /* Merge identical points */
            mergeMe[i] = 1;
            newNVertices--;
        }

        embVector_normalize(delta0, &delta0);
        embVector_normalize(delta1, &delta1);
        float cross = embVector_cross(delta0, delta1);
        float dot = embVector_dot(delta0, delta1);

        if (fabs(cross) < tolerance && dot > 0 && newNVertices > 3) {
            mergeMe[i] = 1;
            newNVertices--;
        }
        else {
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
        if (mergeMe[i] || newNVertices == 0 || currIndex == newNVertices)
            continue;

        vertices.Add(oldVertices[i]);
        currIndex++;
    }
}
#endif

void embPolygon_reduceByDistance(EmbArray *vertices, EmbArray *simplified, float distance);
void embPolygon_reduceByNth(EmbArray *vertices, EmbArray *out, int nth);

/* Reduces the polygon by distance.
 *
 * This is a non-destructive function, so the caller is responsible for
 * freeing "vertices" if they choose to keep "simplified".
 */
void embPolygon_reduceByDistance(EmbArray *vertices, EmbArray *simplified, float distance)
{
    int i;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->count < 3) {
        embArray_copy(simplified, vertices);
        return;
    }

    for (i = 0; i < vertices->count; i++) {
        EmbVector delta;
        int nextId = (i + 1) % vertices->count;

        embVector_subtract(vertices->vector[nextId], vertices->vector[i], &delta);

        /* If they are closer than the distance, continue */
        if (embVector_length(delta) < distance) {
            continue;
        }

        embArray_addVector(simplified, vertices->vector[i]);
    }
}

/* Reduces the polygon by removing the Nth vertex in the vertices list.
 * This is a non-destructive function, so the caller is responsible for
 * freeing vertices if they choose to keep out.
 */
void embPolygon_reduceByNth(EmbArray *vertices, EmbArray *out, int nth)
{
    int i;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->count < 3) {
        embArray_copy(out, vertices);
        return;
    }

    for (i=0; i<vertices->count; i++) {
        if (i!=nth) {
            embArray_addVector(out, vertices->vector[i]);
        }
    }
}

/* IMAGES
 *******************************************************************/

/* PPM Images
 * ----------
 *
 * Basic read/write support for images, so we can convert
 * to any other format we need using imagemagick.
 *
 * We only support P3 ASCII ppm, that is the original, 8 bits per channel.
 *
 * This also allows support for making animations using ffmpeg/avconv
 * of the stitching process.
 */

EmbImage * embImage_create(int width, int height)
{
    int i;
    EmbImage *image;
    image = (EmbImage*)malloc(sizeof(EmbImage));
    image->pixel_width = width;
    image->pixel_height = height;
    image->offset.x = 0.0;
    image->offset.y = 0.0;
    image->color = (EmbColor*)malloc(sizeof(EmbColor)*width*height);
    for (i=0; i<width*height; i++) {
        image->color[i].r = 255;
        image->color[i].g = 255;
        image->color[i].b = 255;
    }
    return image;
}

void embImage_free(EmbImage *image)
{
    free(image->color);
    free(image);
}

/*
 */
int read_ppm_image(char *fname, EmbImage *a)
{
    int i, state;
    FILE *f;
    char header[2];
    f = fopen(fname, "r");
    if (!f) {
        return 0;
    }
    a->pixel_width = 100;
    a->pixel_height = 75;
    state = 0;
    while (fread(header, 1, 1, f) == 1) {
        /* state machine for dealing with the header */
        if (header[0] == '\n') {
            state++;
        }
        if (state == 4) {
            break;
        }
    }
    for (i=0; i<a->pixel_width * a->pixel_height; i++) {
        embColor_read(f, &(a->color[i]), 3);
    }
    fclose(f);
    return 1;
}


/*
 * This function should work, combine with:
 *    $ convert example.ppm example.png
 */
void write_ppm_image(char *fname, EmbImage *a)
{
    int i, j;
    FILE *f;
    char header[100];
    f = fopen(fname, "w");
    if (!f) {
        printf("Failed to open file: %s\n", fname);
        return;
    }
    sprintf(header, "P3\n# Generated by libembroidery 0.1\n%d %d\n%d\n", a->pixel_width, a->pixel_height, 255);
    fputs(header, f);
    for (i=0; i<a->pixel_height; i++) {
        for (j=0; j<a->pixel_width; j++) {
            fprintf(f, "%d %d %d ",
                a->color[j+i*a->pixel_width].r,
                a->color[j+i*a->pixel_width].g,
                a->color[j+i*a->pixel_width].b);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}


/*
 *
 */
float image_diff(EmbImage *a, EmbImage* b)
{
    int i, j;
    float total;
    total = 0.0;
    for (i=0; i<a->pixel_width; i++) {
        for (j=0; j<a->pixel_height; j++) {
            total += embColor_distance(
                a->color[i+j*a->pixel_width],
                b->color[i+j*b->pixel_width]
            );
        }
    }
    return total;
}

/* Render Line
 * -----------
 * 
 */

int render_line(EmbLine line, EmbImage *image, EmbColor color) {
    EmbVector diff, pos, offset;
    int i;
    float pix_w, pix_h;
    offset.x = 10.0;
    offset.y = 0.0;
    embVector_subtract(line.end, line.start, &diff);
    pix_w = image->width / image->pixel_width;
    pix_h = image->height / image->pixel_height;
    for (i = 0; i < 1000; i++) {
        int x, y;
        pos.x = line.start.x + 0.001*i*diff.x + offset.x;
        pos.y = line.start.y + 0.001*i*diff.y + offset.y;
        x = (int)round(pos.x / pix_w);
        y = (int)round(pos.y / pix_h);
        if (x >= 0 && x < image->pixel_width)
        if (y >= 0 && y < image->pixel_height) {
            image->color[x+y*image->pixel_width] = color;
        }
    }
    return 1;
}

/* Basic Render
 * ------------
 * This is a simple algorithm that steps through the stitches and
 * then for each line calls render_line.
 *
 * The caller is responsible for the memory in p.
 */

int embImage_render(EmbPattern *p, float width, float height, char *fname) {
    int i;
    EmbImage *image;
    EmbColor black = {0, 0, 0};
    image = embImage_create(100, 100);
    image->width = width;
    image->height = height;
    for (i=1; i < p->stitchList->count; i++)  {
        EmbLine line;
        line.start.x = p->stitchList->stitch[i-1].x;
        line.start.y = p->stitchList->stitch[i-1].y;
        line.end.x = p->stitchList->stitch[i].x;
        line.end.y = p->stitchList->stitch[i].y;
        render_line(line, image, black); /* HACK: st.color); */
    }
    write_ppm_image(fname, image);
    embImage_free(image);
    return 0;
}

/* EPS style render
 *
 *
 */

int render_postscript(EmbPattern *pattern, EmbImage *image) {
    puts("Postscript rendering not supported, defaulting to ppm.");
    embImage_render(pattern, image->width, image->height, "default.ppm");
    return 1;
}

/* Simulate the stitching of a pattern, using the image for rendering
 * hints about how to represent the pattern.
 */
int embImage_simulate(EmbPattern *pattern, float width, float height, char *fname) {
    embImage_render(pattern, width, height, fname);
    return 0;
}

/* GENERATORS
 *******************************************************************/

int svg_generator(char *s, char **token_table)
{
    return 0;
}

/* TESTS
 *******************************************************************/

static void
report(int result, char *label)
{
    printf("%s Test...%*c", label, (int)(20-strlen(label)), ' ');
    if (result) {
        printf(RED_TERM_COLOR "[FAIL] [CODE=%d]\n" RESET_TERM_COLOR, result);
    }
    else {
        printf(GREEN_TERM_COLOR "[PASS]\n" RESET_TERM_COLOR);
    }
}

void testMain(int level)
{
    EmbPattern *pattern = embPattern_create();
    EmbImage *image = embImage_create(100, 100);
    int circleResult = testEmbCircle();
    int threadResult = testThreadColor();
    int formatResult = testEmbFormat();
    int arcResult = testGeomArc();
    int create1Result = create_test_file_1("test01.csv");
    int create2Result = create_test_file_2("test02.csv");
    int svg1Result = convert("test01.csv", "test01.svg");
    int svg2Result = convert("test02.csv", "test02.svg");
    int dst1Result = convert("test01.csv", "test01.dst");
    int dst2Result = convert("test02.csv", "test02.dst");
    int hilbertCurveResult = hilbert_curve(pattern, 3);
    int renderResult = embImage_render(pattern, 20.0, 20.0, "hilbert_level_3.ppm");
    int simulateResult = embImage_simulate(pattern, 20.0, 20.0, "hilbert_level_3.avi");

    puts("SUMMARY OF RESULTS");
    puts("------------------");
    report(circleResult, "Tangent Point");
    report(threadResult, "Thread");
    report(formatResult, "Format");
    report(arcResult, "Arc");
    report(create1Result, "Create CSV 1");
    report(create2Result, "Create CSV 2");
    report(svg1Result, "Convert CSV-SVG 1");
    report(svg2Result, "Convert CSV-SVG 2");
    report(dst1Result, "Convert CSV-DST 1");
    report(dst2Result, "Convert CSV-DST 2");
    report(hilbertCurveResult, "Generating Hilbert Curve");
    report(renderResult, "Rendering Hilbert Curve");
    report(simulateResult, "Simulating Hilbert Curve");
    
    embImage_free(image);
    embPattern_free(pattern);
    if (level > 0) {
        puts("More expensive tests.");
        full_test_matrix("test_matrix.txt");
    }
}

void testTangentPoints(EmbCircle c, EmbVector p, EmbVector *t0, EmbVector *t1)
{
    emb_error = 0;
    t0->x = 0.0;
    t0->y = 0.0;
    t1->x = 0.0;
    t1->y = 0.0;
    if (!getCircleTangentPoints(c, p, t0, t1)) {
        printf("Error calculating tangent points.\n");
        emb_error = 1;
    }
    else {
        printf("Circle : cr=%f, cx=%f, cy=%f\n"
               "Point  : px=%f, py=%f\n"
               "Tangent: tx0=%f, ty0=%f\n"
               "Tangent: tx1=%f, ty1=%f\n\n",
               c.radius, c.center.x, c.center.y,
               p.x, p.y,
               t0->x, t0->y,
               t1->x, t1->y);
    }
}

float embVector_distance(EmbVector p, EmbVector q)
{
    EmbVector delta;
    embVector_subtract(p, q, &delta);
    return embVector_length(delta);
}

int testEmbCircle(void) {
    double error;
    double epsilon = 1e-3;
    EmbVector p0, p1;
    /* Problem */
    EmbCircle c1 = {0.0, 0.0, 3.0};
    /* Solution */
    EmbVector t0 = {2.2500, 1.9843};
    EmbVector t1 = {2.2500, -1.9843};
    EmbVector p = {4.0, 0.0};
    /* Test */
    testTangentPoints(c1, p, &p0, &p1);
    error = embVector_distance(p0, t0) + embVector_distance(p1, t1);
    if (error > epsilon) {
        printf("Error larger than tolerance, circle test 1: %f.\n\n", error);
        return 16;
    }

    return 0;
}

int testEmbCircle_2(void) {
    double error;
    double epsilon = 1e-3;
    EmbVector p0, p1;
    EmbCircle c2 = {20.1762, 10.7170, 6.8221};
    /* Solution */
    EmbVector s0 = {19.0911, 17.4522};
    EmbVector s1 = {26.4428, 13.4133};
    EmbVector p = {24.3411, 18.2980};
    /* Test */
    testTangentPoints(c2, p, &p0, &p1);
    error = embVector_distance(p0, s0) + embVector_distance(p1, s1);
    if (error > epsilon) {
        printf("Error larger than tolerance, circle test 2: %f.\n\n", error);
        return 17;
    }

    return 0;
}

void printArcResults(double bulge, EmbArc arc,
                     double centerX,   double centerY,
                     double radius,    double diameter,
                     double chord,
                     double chordMidX, double chordMidY,
                     double sagitta,   double apothem,
                     double incAngle,  char   clockwise) {
    fprintf(stdout, "bulge     = %f\n"
                    "startX    = %f\n"
                    "startY    = %f\n"
                    "endX      = %f\n"
                    "endY      = %f\n"
                    "midX      = %f\n"
                    "midY      = %f\n"
                    "centerX   = %f\n"
                    "centerY   = %f\n"
                    "radius    = %f\n"
                    "diameter  = %f\n"
                    "chord     = %f\n"
                    "chordMidX = %f\n"
                    "chordMidY = %f\n"
                    "sagitta   = %f\n"
                    "apothem   = %f\n"
                    "incAngle  = %f\n"
                    "clockwise = %d\n"
                    "\n",
                    bulge,
                    arc.start.x,
                    arc.start.y,
                    arc.end.x,
                    arc.end.y,
                    arc.mid.x,
                    arc.mid.y,
                    centerX,
                    centerY,
                    radius,
                    diameter,
                    chord,
                    chordMidX,
                    chordMidY,
                    sagitta,
                    apothem,
                    incAngle,
                    clockwise);
}

int testGeomArc(void) {
    EmbArc arc;
    EmbVector center, chordMid;
    double bulge, radius, diameter, chord, sagitta, apothem, incAngle;
    char clockwise;

    fprintf(stdout, "Clockwise Test:\n");
    bulge = -0.414213562373095;
    arc.start.x = 1.0;
    arc.start.y = 0.0;
    arc.end.x   = 2.0;
    arc.end.y   = 1.0;
    if (getArcDataFromBulge(bulge, &arc,
                           &(center.x),   &(center.y),
                           &radius,    &diameter,
                           &chord,
                           &(chordMid.x), &(chordMid.y),
                           &sagitta,   &apothem,
                           &incAngle,  &clockwise)) {
        printArcResults(bulge, arc, center.x, center.y,
                        radius, diameter,
                        chord,
                        chordMid.x, chordMid.y,
                        sagitta,   apothem,
                        incAngle,  clockwise);
    }

    fprintf(stdout, "Counter-Clockwise Test:\n");
    bulge  = 2.414213562373095;
    arc.start.x = 4.0;
    arc.start.y = 0.0;
    arc.end.x   = 5.0;
    arc.end.y   = 1.0;
    if (getArcDataFromBulge(bulge, &arc,
                           &(center.x),   &(center.y),
                           &radius,    &diameter,
                           &chord,
                           &(chordMid.x), &(chordMid.y),
                           &sagitta,   &apothem,
                           &incAngle,  &clockwise)) {
        printArcResults(bulge, arc, center.x, center.y,
                        radius,    diameter,
                        chord,
                        chordMid.x, chordMid.y,
                        sagitta,   apothem,
                        incAngle,  clockwise);
    }

    return 0;
}

int testThreadColor(void) {
    unsigned int tColor = 0xFFD25F00;
    int          tBrand = Sulky_Rayon;
    int          tNum   = threadColorNum(tColor, tBrand);
    const char*  tName  = threadColorName(tColor, tBrand);

    printf("Color : 0x%X\n"
           "Brand : %d\n"
           "Num   : %d\n"
           "Name  : %s\n\n",
            tColor,
            tBrand,
            tNum, /* Solution: 1833 */
            tName); /* Solution: Pumpkin Pie */
    return 0;
}

int testEmbFormat(void) {
    const char*  tName = "example.zsk";
    int format = emb_identify_format(tName);

    printf("Filename   : %s\n"
           "Extension  : %s\n"
           "Description: %s\n"
           "Reader     : %c\n"
           "Writer     : %c\n"
           "Type       : %d\n\n",
            tName,
            formatTable[format].extension,
            formatTable[format].description,
            formatTable[format].reader_state,
            formatTable[format].writer_state,
            formatTable[format].type);

    if (strcmp(formatTable[format].extension, ".zsk")) return 20;
    if (strcmp(formatTable[format].description, "ZSK USA Embroidery Format")) {
            return 21;
    }
    if (formatTable[format].reader_state != 'U') return 22;
    if (formatTable[format].writer_state != ' ') return 23;
    if (formatTable[format].type != 1) return 24;
    return 0;
}

int create_test_file_1(const char* outf) {
    int i;
    EmbPattern* p;
    EmbStitch st;

    p = embPattern_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    /* 10mm circle */
    for (i = 0; i < 20; i++) {
        embPattern_addStitchRel(p, 0.0, 1.0, JUMP, 0);
    }
    for (i = 0; i < 200; i++) {
        st.x = 10 + 10 * sin(i * (0.03141592));
        st.y = 10 + 10 * cos(i * (0.03141592));
        st.flags = NORMAL;
        st.color = 0;
        embPattern_addStitchAbs(p, st.x, st.y, st.flags, st.color);
    }

    embPattern_addThread(p, black_thread);
    embPattern_end(p);

    if (!embPattern_writeAuto(p, outf)) {
        return 16;
    }

    embPattern_free(p);
    return 0;
}

int create_test_file_2(const char* outf) {
    int i;
    EmbPattern* p;
    EmbStitch st;

    p = embPattern_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    /* sin wave */
    for (i = 0; i < 100; i++) {
        st.x = 10 + 10 * sin(i * (0.5 / 3.141592));
        st.y = 10 + i * 0.1;
        st.flags = NORMAL;
        st.color = 0;
        embPattern_addStitchAbs(p, st.x, st.y, st.flags, st.color);
    }

    embPattern_addThread(p, black_thread);
    embPattern_end(p);

    if (!embPattern_writeAuto(p, outf)) {
        return 16;
    }

    embPattern_free(p);
    return 0;
}

/* TODO: Add capability for converting multiple files of various types to a single format. 
Currently, we only convert a single file to multiple formats. */
/* the only difference in main() between new and current is these lines

    init_embroidery();
    close_embroidery();
*/

#if 0
int testThreadColor(void) {
    unsigned int tColor = 0xFFD25F00;
    EmbColor c;
    c.r = 0xD2;
    c.g = 0x5F;
    c.b = 0x00;
    int tBrand = Sulky_Rayon;
    int tNum = threadColorNum(c, tBrand);
    char tName[50];
    threadColorName(tName, c, tBrand);

    printf("Color : 0x%X\n"
           "Brand : %d\n"
           "Num   : %d\n"
           "Name  : %s\n\n",
        tColor,
        tBrand,
        tNum, /* Solution: 1833 */
        tName); /* Solution: Pumpkin Pie */
    return 0;
}
#endif

/*
 * Table of from/to for formats. What conversions after a from A to B conversion
 * leave a file with the same render?
 *
 * Add command "--full-test-suite" for this full matrix.
 */

int full_test_matrix(char *fname) {
    int i, j, success, ntests;
    FILE *f;
    f = fopen(fname, "wb");
    if (!f) {
        puts("ERROR: full_test_matrix(fname) failed to open file.");
        return 1;
    }

    success = 0;
    ntests = (numberOfFormats - 1)*(numberOfFormats - 5);
    for (i = 0; i < numberOfFormats; i++) {
        char fname[100];
        if (formatTable[i].color_only) {
            continue;
        }
        snprintf(fname, 30, "test01%s", formatTable[i].extension);
        create_test_file_1(fname);
        /* p3_render(b); */
        for (j=0; j < numberOfFormats; j++) {
            char fname_converted[100];
            int result;
            if (i == j) {
                continue;
            }
            printf("\n");
            snprintf(fname_converted, 30, "test01_%02d_converted%s",
                    i, formatTable[j].extension);
            printf("Attempting: %s %s\n", fname, fname_converted);
            result = convert(fname, fname_converted);
            /* p3_render(b); */
            /*
            int d = image_distance(a, b);
            fprintf(f, "%d %d ", i, j);
            */
            if (!result) {
                fprintf(f, "PASS");
                success++;
            } else {
                fprintf(f, "FAIL");
            }
            fprintf(f, " %d %d\n%f%%\n", i, j, 100*success/(1.0*ntests));
        }
    }

    fclose(f);
    return 0;
}

static void usage(void)
{
    puts(welcome_message);
    /* construct from tables above somehow, like how getopt_long works,
     * but we're avoiding that for compatibility
     * (C90, standard libraries only) */
    puts("Usage: embroider [OPTIONS] fileToRead... \n");
    puts("");
    puts("Conversion:");
    puts("    -t, --to        Convert all files given to the format specified");
    puts("                    by the arguments to the flag, for example:");
    puts("                        $ embroider -t dst input.pes");
    puts("                    would convert \"input.pes\" to \"input.dst\"");
    puts("                    in the same directory the program runs in.");
    puts("");
    puts("                    The accepted input formats are (TO BE DETERMINED).");
    puts("                    The accepted output formats are (TO BE DETERMINED).");
    puts("");
    puts("Output:");
    puts("    -h, --help       Print this message.");
    puts("    -F, --formats     Print help on the formats that embroider can deal with.");
    puts("    -q, --quiet      Only print fatal errors.");
    puts("    -V, --verbose    Print everything that has reporting.");
    puts("    -v, --version    Print the version.");
    puts("");
    puts("Graphics:");
    puts("    -c, --circle     Add a circle defined by the arguments given to the current pattern.");
    puts("    -e, --ellipse    Add a circle defined by the arguments given to the current pattern.");
    puts("    -l, --line       Add a line defined by the arguments given to the current pattern.");
    puts("    -P, --polyline   Add a polyline.");
    puts("    -p, --polygon    Add a polygon.");
    puts("    -r, --render     Create an image in PPM format of what the embroidery should look like.");
    puts("    -s, --satin      Fill the current geometry with satin stitches according");
    puts("                     to the defined algorithm.");
    puts("    -S, --stitch     Add a stitch defined by the arguments given to the current pattern.");
    puts("");
    puts("Quality Assurance:");
    puts("        --test       Run the basic test suite.");
    puts("        --full-test-suite  Run all tests, even those we expect to fail.");
}

static void formats(void)
{
    const char* extension = 0;
    const char* description = 0;
    char readerState;
    char writerState;
    int numReaders = 0;
    int numWriters = 0;
    int i;
    puts("List of Formats");
    puts("---------------");
    puts("");
    puts("    KEY");
    puts("    'S' = Yes, and is considered stable.");
    puts("    'U' = Yes, but may be unstable.");
    puts("    ' ' = No.");
    puts("");
    printf("  Format   Read    Write   Description\n");
    printf("|________|_______|_______|____________________________________________________|\n");
    printf("|        |       |       |                                                    |\n");

    for (i = 0; i < numberOfFormats; i++) {
        extension = formatTable[i].extension;
        description = formatTable[i].description;
        readerState = formatTable[i].reader_state;
        writerState = formatTable[i].writer_state;

        numReaders += readerState != ' '? 1 : 0;
        numWriters += writerState != ' '? 1 : 0;
        printf("|  %-4s  |   %c   |   %c   |  %-49s |\n", extension, readerState, writerState, description);
    }

    printf("|________|_______|_______|____________________________________________________|\n");
    printf("|        |       |       |                                                    |\n");
    printf("| Total: |  %3d  |  %3d  |                                                    |\n", numReaders, numWriters);
    printf("|________|_______|_______|____________________________________________________|\n");
    puts("");
}

/* TODO: Add capability for converting multiple files of various types to a single format. Currently, we only convert a single file to multiple formats. */
static int command_line_interface(int argc, char* argv[])
{
    EmbPattern *current_pattern = embPattern_create();
    float width, height;
    int i, j, flags, result;
    if (argc == 1) {
        usage();
        return 0;
    }

    width = 10.0;
    height = 10.0;

    flags = argc-1;
    for (i=1; i < argc; i++) {
        result = -1;
        /* identify what flag index the user may have entered */
        for (j=0; j < NUM_FLAGS; j++) {
            if (!strcmp(flag_list[j], argv[i])) {
                result = j;
                break;
            }
        }
        /* apply the flag */
        switch (result) {
        case FLAG_TO:
            /* the next argument is the format we're converting to */
            puts("This flag is not implemented.");
            break;
        case FLAG_HELP:
        case FLAG_HELP_SHORT:
            usage();
            break;
        case FLAG_FORMATS:
        case FLAG_FORMATS_SHORT:
            formats();
            break;
        case FLAG_QUIET:
        case FLAG_QUIET_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_VERBOSE:
        case FLAG_VERBOSE_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_CIRCLE:
        case FLAG_CIRCLE_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_ELLIPSE:
        case FLAG_ELLIPSE_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_LINE:
        case FLAG_LINE_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_POLYGON:
        case FLAG_POLYGON_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_POLYLINE:
        case FLAG_POLYLINE_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_SATIN:
        case FLAG_SATIN_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_STITCH:
        case FLAG_STITCH_SHORT:
            puts("This flag is not implemented.");
            break;
        case FLAG_SIERPINSKI_TRIANGLE:
            puts("This flag is not implemented.");
            break;
        case FLAG_FILL:
            puts("This flag is not implemented.");
            break;
        case FLAG_IMAGE_WIDTH:
            if (i + 1 < argc) {
                i++;
                width = atof(argv[i]);
            }
            else {
                puts("The image width flag requires an argument.");
                break;
            }
            break;
        case FLAG_IMAGE_HEIGHT:
            if (i + 1 < argc) {
                i++;
                height = atof(argv[i]);
            }
            else {
                puts("The image width flag requires an argument.");
                break;
            }
            break;
        case FLAG_RENDER:
        case FLAG_RENDER_SHORT:
            if (i + 1 < argc) {
                /* the user appears to have entered a filename after render */
                i++;
                if (argv[i][0] == '-') {
                    /* they haven't, use the default name */
                    puts("Defaulting to the output name 'output.ppm'.");
                    embImage_render(current_pattern, width, height, "output.ppm");
                    i--;
                }
                else {
                    /* they have, use the user-supplied name */
                    embImage_render(current_pattern, width, height, argv[i]);
                }
            }
            else {
                puts("Defaulting to the output name 'output.ppm'.");
                embImage_render(current_pattern, width, height, "output.ppm");
            }
            break;
        case FLAG_SIMULATE:
            if (i + 1 < argc) {
                /* the user appears to have entered a filename after render */
                i++;
                if (argv[i][0] == '-') {
                    /* they haven't, use the default name */
                    puts("Defaulting to the output name 'output.avi'.");
                    embImage_simulate(current_pattern, width, height, "output.avi");
                    i--;
                }
                else {
                    /* they have, use the user-supplied name */
                    embImage_simulate(current_pattern, width, height, argv[i]);
                }
            }
            else {
                puts("Defaulting to the output name 'output.avi'.");
                embImage_simulate(current_pattern, width, height, "output.avi");
            }
            break;
        case FLAG_VERSION:
        case FLAG_VERSION_SHORT:
            puts(version_string);
            break;
        case FLAG_HILBERT_CURVE:
            current_pattern = embPattern_create();
            hilbert_curve(current_pattern, 3);
            break;
        case FLAG_TEST:
            testMain(0);
            break;
        case FLAG_FULL_TEST_SUITE:
            testMain(1);
            break;
        default:
            flags--;
            break;
        }
    }

    /* No flags set: default to simple from-to conversion. */
    if (!flags && argc == 3) {
        convert(argv[1], argv[2]);
    }
    else {
        puts("Please enter an output format for your file, see --help.");
    }
    embPattern_free(current_pattern);
    return 0;
}

#ifdef LIBEMBROIDERY_CLI
int main(int argc, char* argv[])
{
    return command_line_interface(argc, argv);
}
#endif


