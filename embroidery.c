/*
 * This file is part of libembroidery.
 *
 * Copyright 2018-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "embroidery.h"

#define MAX_STITCHES             1000000

#define EMB_BIG_ENDIAN                          0
#define EMB_LITTLE_ENDIAN                       1

#define ENDIAN_HOST                             EMB_LITTLE_ENDIAN

#define EMB_INT16_BIG                           2
#define EMB_INT16_LITTLE                        3
#define EMB_INT32_BIG                           4
#define EMB_INT32_LITTLE                        5

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
#define FLAG_COMBINE                 37
#define NUM_FLAGS                    38

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

typedef struct Huffman {
    int default_value;
    int *lengths;
    int nlengths;
    int *table;
    int table_width;
    int ntable;
} huffman;

typedef struct Compress {
    int bit_position;
    char *input_data;
    int input_length;
    int bits_total;
    int block_elements;
    huffman *character_length_huffman;
    huffman *character_huffman;
    huffman *distance_huffman;
} compress;


/* INTERNAL FUNCTION PROTOTYPES
 *******************************************************************/
static void huffman_init(huffman *h, int lengths, int value);
static void huffman_build_table(huffman *h);
static void huffman_table_lookup(huffman *h, int byte_lookup, int *value, int *lengths);
static void huffman_free(huffman *h);

static int compress_get_bits(compress *c, int length);
static int compress_pop(compress *c, int bit_count);
static int compress_read_variable_length(compress *c);
static int compress_load_character_length_huffman(compress *c);
static void compress_load_character_huffman(compress *c);
static void compress_load_distance_huffman(compress *c);
static void compress_load_block(compress *c);
static int compress_get_token(compress *c);
static int compress_get_position(compress *c);

static void binaryReadString(FILE* file, char *buffer, int maxLength);
static void binaryReadUnicodeString(FILE* file, char *buffer, const int stringLength);

static void binaryWriteShort(FILE* file, short data);
static void binaryWriteUShort(FILE* file, unsigned short data);
static void binaryWriteUShortBE(FILE* file, unsigned short data);
static void binaryWriteInt(FILE* file, int data);
static void binaryWriteIntBE(FILE* file, int data);
static void binaryWriteUInt(FILE* file, unsigned int data);
static void binaryWriteUIntBE(FILE* file, unsigned int data);

static int stringInArray(const char *s, const char **array);
static void fpad(FILE *f, char c, int n);
static char *copy_trim(char const *s);
static char* emb_optOut(double num, char* str);

static void write_24bit(FILE* file, int);
static int check_header_present(FILE* file, int minimum_header_length);

static void fread_int(FILE* f, void *b, int mode);
static void fwrite_int(FILE* f, void *b, int mode);
static short fread_int16(FILE* f);
static unsigned short fread_uint16(FILE* f);
static int fread_int32(FILE* f);
static unsigned int fread_uint32(FILE* f);
static short fread_int16_be(FILE* f);
static unsigned short fread_uint16_be(FILE* f);
static int fread_int32_be(FILE* f);
static unsigned int fread_uint32_be(FILE* f);

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

static char read100(EmbPattern *pattern, FILE* file);
static char write100(EmbPattern *pattern, FILE* file);
static char read10o(EmbPattern *pattern, FILE* file);
static char write10o(EmbPattern *pattern, FILE* file);
static char readArt(EmbPattern *pattern, FILE* file);
static char writeArt(EmbPattern *pattern, FILE* file);
static char readBmc(EmbPattern *pattern, FILE* file);
static char writeBmc(EmbPattern *pattern, FILE* file);
static char readBro(EmbPattern *pattern, FILE* file);
static char writeBro(EmbPattern *pattern, FILE* file);
static char readCnd(EmbPattern *pattern, FILE* file);
static char writeCnd(EmbPattern *pattern, FILE* file);
static char readCol(EmbPattern *pattern, FILE* file);
static char writeCol(EmbPattern *pattern, FILE* file);
static char readCsd(EmbPattern *pattern, FILE* file);
static char writeCsd(EmbPattern *pattern, FILE* file);
static char readCsv(EmbPattern *pattern, FILE* file);
static char writeCsv(EmbPattern *pattern, FILE* file);
static char readDat(EmbPattern *pattern, FILE* file);
static char writeDat(EmbPattern *pattern, FILE* file);
static char readDem(EmbPattern *pattern, FILE* file);
static char writeDem(EmbPattern *pattern, FILE* file);
static char readDsb(EmbPattern *pattern, FILE* file);
static char writeDsb(EmbPattern *pattern, FILE* file);
static char readDst(EmbPattern *pattern, FILE* file);
static char writeDst(EmbPattern *pattern, FILE* file);
static char readDsz(EmbPattern *pattern, FILE* file);
static char writeDsz(EmbPattern *pattern, FILE* file);
static char readDxf(EmbPattern *pattern, FILE* file);
static char writeDxf(EmbPattern *pattern, FILE* file);
static char readEdr(EmbPattern *pattern, FILE* file);
static char writeEdr(EmbPattern *pattern, FILE* file);
static char readEmd(EmbPattern *pattern, FILE* file);
static char writeEmd(EmbPattern *pattern, FILE* file);
static char readExp(EmbPattern *pattern, FILE* file);
static char writeExp(EmbPattern *pattern, FILE* file);
static char readExy(EmbPattern *pattern, FILE* file);
static char writeExy(EmbPattern *pattern, FILE* file);
static char readEys(EmbPattern *pattern, FILE* file);
static char writeEys(EmbPattern *pattern, FILE* file);
static char readFxy(EmbPattern *pattern, FILE* file);
static char writeFxy(EmbPattern *pattern, FILE* file);
static char readGc(EmbPattern *pattern, FILE* file);
static char writeGc(EmbPattern *pattern, FILE* file);
static char readGnc(EmbPattern *pattern, FILE* file);
static char writeGnc(EmbPattern *pattern, FILE* file);
static char readGt(EmbPattern *pattern, FILE* file);
static char writeGt(EmbPattern *pattern, FILE* file);
static char readHus(EmbPattern *pattern, FILE* file);
static char writeHus(EmbPattern *pattern, FILE* file);
static char readInb(EmbPattern *pattern, FILE* file);
static char writeInb(EmbPattern *pattern, FILE* file);
static char readInf(EmbPattern *pattern, FILE* file);
static char writeInf(EmbPattern *pattern, FILE* file);
static char readJef(EmbPattern *pattern, FILE* file);
static char writeJef(EmbPattern *pattern, FILE* file);
static char readKsm(EmbPattern *pattern, FILE* file);
static char writeKsm(EmbPattern *pattern, FILE* file);
static char readMax(EmbPattern *pattern, FILE* file);
static char writeMax(EmbPattern *pattern, FILE* file);
static char readMit(EmbPattern *pattern, FILE* file);
static char writeMit(EmbPattern *pattern, FILE* file);
static char readNew(EmbPattern *pattern, FILE* file);
static char writeNew(EmbPattern *pattern, FILE* file);
static char readOfm(EmbPattern *pattern, FILE* file);
static char writeOfm(EmbPattern *pattern, FILE* file);
static char readPcd(EmbPattern *pattern, const char *fileName, FILE* file);
static char writePcd(EmbPattern *pattern, FILE* file);
static char readPcm(EmbPattern *pattern, FILE* file);
static char writePcm(EmbPattern *pattern, FILE* file);
static char readPcq(EmbPattern *pattern, const char *fileName, FILE* file);
static char writePcq(EmbPattern *pattern, FILE* file);
static char readPcs(EmbPattern *pattern, const char *fileName, FILE* file);
static char writePcs(EmbPattern *pattern, FILE* file);
static char readPec(EmbPattern *pattern, const char *fileName, FILE* file);
static char writePec(EmbPattern *pattern, const char *fileName,  FILE* file);
static char readPel(void);
static char writePel(void);
static char readPem(void);
static char writePem(void);
static char readPes(EmbPattern *pattern, const char *fileName, FILE* file);
static char writePes(EmbPattern *pattern, const char *fileName, FILE* file);
static char readPhb(EmbPattern *pattern, FILE* file);
static char writePhb(void);
static char readPhc(EmbPattern *pattern, FILE* file);
static char writePhc(void);
static char readPlt(EmbPattern *pattern, FILE* file);
static char writePlt(EmbPattern *pattern, FILE* file);
static char readRgb(EmbPattern *pattern, FILE* file);
static char writeRgb(EmbPattern *pattern, FILE* file);
static char readSew(EmbPattern *pattern, FILE* file);
static char writeSew(EmbPattern *pattern, FILE* file);
static char readShv(EmbPattern *pattern, FILE* file);
static char writeShv(void);
static char readSst(EmbPattern *pattern, FILE* file);
static char writeSst(void);
static char readStx(EmbPattern *pattern, FILE* file);
static char writeStx(void);
static char readSvg(EmbPattern *pattern, FILE* file);
static char writeSvg(EmbPattern *pattern, FILE* file);
static char readT01(EmbPattern *pattern, FILE* file);
static char writeT01(EmbPattern *pattern, FILE* file);
static char readT09(EmbPattern *pattern, FILE* file);
static char writeT09(EmbPattern *pattern, FILE* file);
static char readTap(EmbPattern *pattern, FILE* file);
static char writeTap(EmbPattern *pattern, FILE* file);
static char readThr(EmbPattern *pattern, FILE* file);
static char writeThr(EmbPattern *pattern, FILE* file);
static char readTxt(EmbPattern *pattern, FILE* file);
static char writeTxt(EmbPattern *pattern, FILE* file);
static char readU00(EmbPattern *pattern, FILE* file);
static char writeU00(void);
static char readU01(EmbPattern *pattern, FILE* file);
static char writeU01(void);
static char readVip(EmbPattern *pattern, FILE* file);
static char writeVip(EmbPattern *pattern, FILE* file);
static char readVp3(EmbPattern *pattern, FILE* file);
static char writeVp3(EmbPattern *pattern, FILE* file);
static char readXxx(EmbPattern *pattern, FILE* file);
static char writeXxx(EmbPattern *pattern, FILE* file);
static char readZsk(EmbPattern *pattern, FILE* file);
static char writeZsk(EmbPattern *pattern, FILE* file);

/* DATA 
 *******************************************************************/

EmbThread black_thread = { { 0, 0, 0 }, "Black", "Black" };

static int emb_verbose = 0;

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
    "--simulate",
    "--combine"
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

int emb_error = 0;

static size_t object_sizes[] = {
    sizeof(EmbArcObject),
    sizeof(EmbCircleObject),
    sizeof(EmbEllipseObject),
    sizeof(int),
    sizeof(EmbPathObject),
    sizeof(EmbPointObject),
    sizeof(EmbLineObject),
    sizeof(EmbPolygonObject*)
};

/* TODO: This list needs reviewed in case some stitch 
    formats also can contain object data (EMBFORMAT_STCHANDOBJ). */

EmbFormatList formatTable[numberOfFormats] = {
    {".10o", "Toyota Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".100", "Toyota Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".art", "Bernina Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".bmc", "Bitmap Cache Embroidery Format",     ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".bro", "Bits & Volts Embroidery Format",     'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".cnd", "Melco Embroidery Format",            ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".col", "Embroidery Thread Color Format",     'U', 'U', EMBFORMAT_STITCHONLY, 1, 0, 0},
    {".csd", "Singer Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".csv", "Comma Separated Values Format",      'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".dat", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".dem", "Melco Embroidery Format",            ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".dsb", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".dst", "Tajima Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".dsz", "ZSK USA Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".dxf", "Drawing Exchange Format",            ' ', ' ', EMBFORMAT_OBJECTONLY, 0, 0, 0},
    {".edr", "Embird Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, 1, 0, 0},
    {".emd", "Elna Embroidery Format",             'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".exp", "Melco Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".exy", "Eltac Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".eys", "Sierra Expanded Embroidery Format",  ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".fxy", "Fortron Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".gc",  "Smoothie G-Code Format",             ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".gnc", "Great Notions Embroidery Format",    ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".gt",  "Gold Thread Embroidery Format",      'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".hus", "Husqvarna Viking Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".inb", "Inbro Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".inf", "Embroidery Color Format",            'U', 'U', EMBFORMAT_STITCHONLY, 1, 0, 0},
    {".jef", "Janome Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".ksm", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".max", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".mit", "Mitsubishi Embroidery Format",       'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".new", "Ameco Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".ofm", "Melco Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pcd", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pcm", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pcq", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pcs", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pec", "Brother Embroidery Format",          'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pel", "Brother Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pem", "Brother Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".pes", "Brother Embroidery Format",          'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".phb", "Brother Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".phc", "Brother Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".plt", "AutoCAD Plot Drawing Format",        'U', 'U', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".rgb", "RGB Embroidery Format",              'U', 'U', EMBFORMAT_STITCHONLY, 1, 0, 0},
    {".sew", "Janome Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".shv", "Husqvarna Viking Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".sst", "Sunstar Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".stx", "Data Stitch Embroidery Format",      'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".svg", "Scalable Vector Graphics",           'U', 'U', EMBFORMAT_OBJECTONLY, 0, 0, 0},
    {".t01", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".t09", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".tap", "Happy Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 1, 0},
    {".thr", "ThredWorks Embroidery Format",       'U', 'U', EMBFORMAT_STITCHONLY, 1, 0, 0},
    {".txt", "Text File",                          ' ', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".u00", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".u01", "Barudan Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".vip", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".vp3", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".xxx", "Singer Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, 0, 0, 0},
    {".zsk", "ZSK USA Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, 0, 0, 0}
};

/*! Constant representing the number of Double Indirect FAT entries in a single header */
static const unsigned int NumberOfDifatEntriesInHeader = 109;
static const unsigned int sizeOfFatEntry = sizeof(unsigned int);
static const unsigned int sizeOfDifatEntry = 4;
static const unsigned int sizeOfChainingEntryAtEndOfDifatSector = 4;
static const unsigned int sizeOfDirectoryEntry = 128;
/*
static const int supportedMinorVersion = 0x003E;
static const int littleEndianByteOrderMark = 0xFFFE;
*/

const double embConstantPi = 3.1415926535;

static const char *svg_element_tokens[] = {
    "a", "animate", "animateColor", "animateMotion", "animateTransform", "animation",
    "audio", "circle", "defs", "desc", "discard", "ellipse",
    "font", "font-face", "font-face-src", "font-face-uri", "foreignObject",
    "g", "glyph", "handler", "hkern", "image", "line", "linearGradient", "listener",
    "metadata", "missing-glyph", "mpath", "path", "polygon", "polyline", "prefetch",
    "radialGradient", "rect", "script", "set", "solidColor", "stop", "svg", "switch",
    "tbreak", "text", "textArea", "title", "tspan", "use", "video", "\0"
    /* "altGlyph", "altGlyphDef", "altGlyphItem", "clipPath", "color-profile", "cursor",
     * "feBlend", "feColorMatrix", "feComponentTransfer", "feComposite", "feConvolveMatrix",
     * "feDiffuseLighting", "feDisplacementMap", "feDistantLight", "feFlood",
     * "feFuncA", "feFuncB", "feFuncG", "feFuncR", "feGaussianBlur", "feImage",
     * "feMerge", "feMergeNode", "feMorphology", "feOffset", "fePointLight",
     * "feSpecularLighting", "feSpotLight", "feTile", "feTurbulence", "filter",
     * "font-face-format", "font-face-name", "glyphRef", "marker", "mask",
     * "pattern", "style", "symbol", "textPath", "tref", "view", "vkern"
     * TODO: not implemented SVG Full 1.1 Spec Elements */
};

static const char *svg_media_property_tokens[] = {
    "audio-level", "buffered-rendering", "display", "image-rendering",
    "pointer-events", "shape-rendering", "text-rendering", "viewport-fill",
    "viewport-fill-opacity", "visibility", "\0"
};

static const char *svg_property_tokens[] = {
    "audio-level", "buffered-rendering", "color", "color-rendering", "direction",
    "display", "display-align", "fill", "fill-opacity", "fill-rule",
    "font-family", "font-size", "font-style", "font-variant", "font-weight",
    "image-rendering", "line-increment", "opacity", "pointer-events",
    "shape-rendering", "solid-color", "solid-opacity", "stop-color",
    "stop-opacity", "stroke", "stroke-dasharray", "stroke-linecap", "stroke-linejoin",
    "stroke-miterlimit", "stroke-opacity", "stroke-width", "text-align",
    "text-anchor", "text-rendering", "unicode-bidi", "vector-effect",
    "viewport-fill", "viewport-fill-opacity", "visibility", "\0"
};

static const char *xml_attribute_tokens[] = {
    "encoding", "standalone", "version", "/", "\0"
};

static const char *link_attribute_tokens[] = {
    "about", "class", "content", "datatype", "externalResourcesRequired",
    "focusHighlight", "focusable", "id", "nav-down", "nav-down-left",
    "nav-down-right", "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
    "nav-up-left", "nav-up-right", "property", "rel", "requiredExtensions",
    "requiredFeatures", "requiredFonts", "requiredFormats", "resource", "rev",
    "role", "systemLanguage", "target", "transform", "typeof", "xlink:actuate",
    "xlink:arcrole", "xlink:href", "xlink:role", "xlink:show", "xlink:title",
    "xlink:type", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
};

static const char *animate_attribute_tokens[] = {
    "about", "accumulate", "additive", "attributeName", "attributeType",
    "begin", "by", "calcMode", "class", "content", "datatype", "dur", "end",
    "fill", "from", "id", "keySplines", "keyTimes", "max", "min", "property",
    "rel", "repeatCount", "repeatDur", "requiredExtensions",
    "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
    "restart", "rev", "role", "systemLanguage", "to", "typeof", "values",
    "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
    "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
    "xml:lang", "xml:space", "/", "\0"
};

static const char *animate_color_attribute_tokens[] = {
    "about", "accumulate", "additive", "attributeName", "attributeType",
    "begin", "by", "calcMode", "class", "content", "datatype", "dur",
    "end", "fill", "from", "id", "keySplines", "keyTimes", "max", "min",
    "property", "rel", "repeatCount", "repeatDur", "requiredExtensions",
    "requiredFeatures", "requiredFonts", "requiredFormats",
    "resource", "restart", "rev", "role", "systemLanguage",
    "to", "typeof", "values", "xlink:actuate", "xlink:arcrole",
    "xlink:href", "xlink:role", "xlink:show", "xlink:title",
    "xlink:type", "xml:base", "xml:id", "xml:lang",
    "xml:space", "/", "\0"
};

static const char *animate_motion_attribute_tokens[] = {
    "about", "accumulate", "additive", "begin", "by", "calcMode", "class",
    "content", "datatype", "dur", "end", "fill", "from", "id", "keyPoints",
    "keySplines", "keyTimes", "max", "min", "origin", "path", "property",
    "rel", "repeatCount", "repeatDur", "requiredExtensions",
    "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
    "restart", "rev", "role", "rotate", "systemLanguage", "to", "typeof",
    "values", "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
    "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
    "xml:lang", "xml:space", "/", "\0"
};

static const char *animate_transform_attribute_tokens[] = {
    "about", "accumulate", "additive", "attributeName", "attributeType",
    "begin", "by", "calcMode", "class", "content", "datatype", "dur", "end",
    "fill", "from", "id", "keySplines", "keyTimes", "max", "min",
    "property", "rel", "repeatCount", "repeatDur", "requiredExtensions",
    "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
    "restart", "rev", "role", "systemLanguage", "to", "type", "typeof",
    "values", "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
    "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
    "xml:lang", "xml:space", "/", "\0"
};

static const char *switch_attribute_tokens[] = {
    "about", "class", "content", "datatype", "externalResourcesRequired",
    "focusHighlight", "focusable", "id", "nav-down", "nav-down-left",
    "nav-down-right", "nav-left", "nav-next", "nav-prev", "nav-right",
    "nav-up", "nav-up-left", "nav-up-right", "property", "rel",
    "requiredExtensions", "requiredFeatures", "requiredFonts",
    "requiredFormats", "resource", "rev", "role", "systemLanguage",
    "transform", "typeof", "xml:base", "xml:id", "xml:lang", "xml:space",
    "/", "\0"
};

static const char *tbreak_attribute_tokens[] = {
    "about", "class", "content", "datatype", "id", "property", "rel",
    "requiredExtensions", "requiredFeatures", "requiredFonts",
    "requiredFormats", "resource", "rev", "role", "systemLanguage",
    "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
};

static const char *text_attribute_tokens[] = {
    "about", "class", "content", "datatype", "editable", "focusHighlight",
    "focusable", "id", "nav-down", "nav-down-left", "nav-down-right",
    "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
    "nav-up-left", "nav-up-right", "property", "rel", "requiredExtensions",
    "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
    "rev", "role", "rotate", "systemLanguage", "transform", "typeof", "x",
    "xml:base", "xml:id", "xml:lang", "xml:space", "y", "/", "\0"
};

static const char *textarea_attribute_tokens[] = {
    "about", "class", "content", "datatype", "editable", "focusHighlight",
    "focusable", "height", "id", "nav-down", "nav-down-left",
    "nav-down-right", "nav-left", "nav-next", "nav-prev", "nav-right",
    "nav-up", "nav-up-left", "nav-up-right", "property", "rel",
    "requiredExtensions", "requiredFeatures", "requiredFonts",
    "requiredFormats", "resource", "rev", "role", "systemLanguage",
    "transform", "typeof", "width", "x", "xml:base", "xml:id", "xml:lang",
    "xml:space", "y", "/", "\0"
};

static const char *title_attribute_tokens[] = {
    "about", "class", "content", "datatype", "id", "property", "rel",
    "requiredExtensions", "requiredFeatures", "requiredFonts",
    "requiredFormats", "resource", "rev", "role", "systemLanguage",
    "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
};

static const char *tspan_attribute_tokens[] = {
    "about", "class", "content", "datatype", "focusHighlight", "focusable",
    "id", "nav-down", "nav-down-left", "nav-down-right", "nav-left",
    "nav-next", "nav-prev", "nav-right", "nav-up", "nav-up-left",
    "nav-up-right", "property", "rel", "requiredExtensions",
    "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
    "rev", "role", "systemLanguage", "typeof", "xml:base", "xml:id",
    "xml:lang", "xml:space", "/", "\0"
};

static const char *use_attribute_tokens[] = {
    "about", "class", "content", "datatype", "externalResourcesRequired",
    "focusHighlight", "focusable", "id", "nav-down", "nav-down-left",
    "nav-down-right", "nav-left", "nav-next", "nav-prev", "nav-right",
    "nav-up", "nav-up-left", "nav-up-right", "property", "rel",
    "requiredExtensions", "requiredFeatures", "requiredFonts",
    "requiredFormats", "resource", "rev", "role", "systemLanguage",
    "transform", "typeof", "x", "xlink:actuate", "xlink:arcrole",
    "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
    "xml:base", "xml:id", "xml:lang", "xml:space", "y", "/", "\0"
};

static const char *video_attribute_tokens[] = {
    "about", "begin", "class", "content", "datatype", "dur", "end",
    "externalResourcesRequired", "fill", "focusHighlight", "focusable",
    "height", "id", "initialVisibility", "max", "min", "nav-down",
    "nav-down-left", "nav-down-right", "nav-left", "nav-next", "nav-prev",
    "nav-right", "nav-up", "nav-up-left", "nav-up-right", "overlay",
    "preserveAspectRatio", "property", "rel", "repeatCount", "repeatDur",
    "requiredExtensions", "requiredFeatures", "requiredFonts",
    "requiredFormats", "resource", "restart", "rev", "role", "syncBehavior",
    "syncMaster", "syncTolerance", "systemLanguage", "transform",
    "transformBehavior", "type", "typeof", "width", "x", "xlink:actuate",
    "xlink:arcrole", "xlink:href", "xlink:role", "xlink:show",
    "xlink:title", "xlink:type", "xml:base", "xml:id", "xml:lang",
    "xml:space", "y", "/", "\0"
};

static const char *catch_all_tokens[] = {
    /* Catch All Properties */
    "audio-level", "buffered-rendering", "color", "color-rendering",
    "direction", "display", "display-align", "fill",
    "fill-opacity", "fill-rule", "font-family", "font-size", "font-style",
    "font-variant", "font-weight", "image-rendering", "line-increment",
    "opacity", "pointer-events", "shape-rendering", "solid-color",
    "solid-opacity", "stop-color", "stop-opacity", "stroke",
    "stroke-dasharray", "stroke-linecap", "stroke-linejoin",
    "stroke-miterlimit", "stroke-opacity", "stroke-width",
    "text-align", "text-anchor", "text-rendering", "unicode-bidi",
    "vector-effect", "viewport-fill", "viewport-fill-opacity", "visibility",
    /* Catch All Attributes */
    "about", "accent-height", "accumulate", "additive",
    "alphabetic", "arabic-form", "ascent", "attributeName", "attributeType",
    "bandwidth", "baseProfile", "bbox", "begin", "by", "calcMode",
    "cap-height", "class", "content", "contentScriptType", "cx", "cy",
    "d", "datatype", "defaultAction", "descent", "dur", "editable",
    "end", "ev:event", "event", "externalResourcesRequired",
    "focusHighlight", "focusable", "font-family", "font-stretch",
    "font-style", "font-variant", "font-weight", "from", "g1", "g2",
    "glyph-name", "gradientUnits", "handler", "hanging", "height",
    "horiz-adv-x", "horiz-origin-x", "id", "ideographic",
    "initialVisibility", "k", "keyPoints", "keySplines", "keyTimes",
    "lang", "mathematical", "max", "mediaCharacterEncoding",
    "mediaContentEncodings", "mediaSize", "mediaTime", "min",
    "nav-down", "nav-down-left", "nav-down-right", "nav-left", "nav-next",
    "nav-prev", "nav-right", "nav-up", "nav-up-left", "nav-up-right",
    "observer", "offset", "origin", "overlay", "overline-position",
    "overline-thickness", "panose-1", "path", "pathLength", "phase",
    "playbackOrder", "points", "preserveAspectRatio", "propagate",
    "property", "r", "rel", "repeatCount", "repeatDur",
    "requiredExtensions", "requiredFeatures", "requiredFonts",
    "requiredFormats", "resource", "restart", "rev", "role", "rotate",
    "rx", "ry", "slope", "snapshotTime", "stemh", "stemv",
    "strikethrough-position", "strikethrough-thickness", "syncBehavior",
    "syncBehaviorDefault", "syncMaster", "syncTolerance",
    "syncToleranceDefault", "systemLanguage", "target", "timelineBegin",
        "to", "transform", "transformBehavior", "type", "typeof", "u1", "u2",
        "underline-position", "underline-thickness", "unicode", "unicode-range",
        "units-per-em", "values", "version", "viewBox", "width", "widths",
        "x", "x-height", "x1", "x2", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "y", "y1", "y2",
        "zoomAndPan", "/", "\0"
};

/* CODE SECTION
 *******************************************************************/

#include "formats.c"
#include "thread-color.c"

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
        b[2] |= 0x04;
        x -= 81;
    }
    if (x <= -41) {
        b[2] |= 0x08;
        x += 81;
    }
    if (x >= +14) {
        b[1] |= 0x04;
        x -= 27;
    }
    if (x <= -14) {
        b[1] |= 0x08;
        x += 27;
    }
    if (x >= +5) {
        b[0] |= 0x04;
        x -= 9;
    }
    if (x <= -5) {
        b[0] |= 0x08;
        x += 9;
    }
    if (x >= +2) {
        b[1] |= 0x01;
        x -= 3;
    }
    if (x <= -2) {
        b[1] |= 0x02;
        x += 3;
    }
    if (x >= +1) {
        b[0] |= 0x01;
        x -= 1;
    }
    if (x <= -1) {
        b[0] |= 0x02;
        x += 1;
    }
    if (x != 0) {
        printf("ERROR: format-dst.c encode_record(), ");
        printf("x should be zero yet x = %d\n", x);
        return 0;
    }
    if (y >= +41) {
        b[2] |= 0x20;
        y -= 81;
    }
    if (y <= -41) {
        b[2] |= 0x10;
        y += 81;
    }
    if (y >= +14) {
        b[1] |= 0x20;
        y -= 27;
    }
    if (y <= -14) {
        b[1] |= 0x10;
        y += 27;
    }
    if (y >= +5) {
        b[0] |= 0x20;
        y -= 9;
    }
    if (y <= -5) {
        b[0] |= 0x10;
        y += 9;
    }
    if (y >= +2) {
        b[1] |= 0x80;
        y -= 3;
    }
    if (y <= -2) {
        b[1] |= 0x40;
        y += 3;
    }
    if (y >= +1) {
        b[0] |= 0x80;
        y -= 1;
    }
    if (y <= -1) {
        b[0] |= 0x40;
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
    if (b[0] & 0x01) {
        *x += 1;
    }
    if (b[0] & 0x02) {
        *x -= 1;
    }
    if (b[0] & 0x04) {
        *x += 9;
    }
    if (b[0] & 0x08) {
        *x -= 9;
    }
    if (b[0] & 0x80) {
        *y += 1;
    }
    if (b[0] & 0x40) {
        *y -= 1;
    }
    if (b[0] & 0x20) {
        *y += 9;
    }
    if (b[0] & 0x10) {
        *y -= 9;
    }
    if (b[1] & 0x01) {
        *x += 3;
    }
    if (b[1] & 0x02) {
        *x -= 3;
    }
    if (b[1] & 0x04) {
        *x += 27;
    }
    if (b[1] & 0x08) {
        *x -= 27;
    }
    if (b[1] & 0x80) {
        *y += 3;
    }
    if (b[1] & 0x40) {
        *y -= 3;
    }
    if (b[1] & 0x20) {
        *y += 27;
    }
    if (b[1] & 0x10) {
        *y -= 27;
    }
    if (b[2] & 0x04) {
        *x += 81;
    }
    if (b[2] & 0x08) {
        *x -= 81;
    }
    if (b[2] & 0x20) {
        *y += 81;
    }
    if (b[2] & 0x10) {
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

    new_state = state + MAX_STITCHES*5;

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
    state = malloc(MAX_STITCHES*10);
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

EmbPattern *embPattern_combine(EmbPattern *p1, EmbPattern *p2)
{
    EmbPattern *out = embPattern_create();
    return out;
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
    offset.x = -10.0;
    offset.y = -10.0;
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

/*
 *  Thanks to Jason Weiler for describing the binary formats of the HUS and
 *  VIP formats at:
 *
 *  http://www.jasonweiler.com/HUSandVIPFileFormatInfo.html
 *
 *  Further thanks to github user tatarize for solving the mystery of the
 *  compression in:
 *
 *  https://github.com/EmbroidePy/pyembroidery
 *
 *  with a description of that work here:
 *
 *  https://stackoverflow.com/questions/7852670/greenleaf-archive-library
 *
 *  This is based on their work.
 *******************************************************************************
 */

/* This is a work in progress.
 * ---------------------------
 */

/* This avoids the now unnecessary compression by placing a
 * minimal header of 6 bytes and using only literals in the
 * huffman compressed part (see the sources above).
 */
int hus_compress(char *data, int length, char *output, int *output_length)
{
    unsigned char *a = (unsigned char*)output;
    a[0] = length%256;
    a[1] = (length/256)%256;
    a[2] = 0x02;
    a[3] = 0xA0;
    a[4] = 0x01;
    a[5] = 0xFE;
    memcpy(output+6, data, length);
    *output_length = length+6;
    return 0;
}

/* These next 4 functions represent the Huffman class in tartarize's code.
 */
static void huffman_init(huffman *h, int lengths, int value)
{
    /* these mallocs are guessing for now */
    h->default_value = value;
    h->lengths = malloc(1000);
    h->nlengths = lengths;
    h->table = malloc(1000);
    h->ntable = 0;
    h->table_width = 0;
}

static void huffman_build_table(huffman *h)
{
    int bit_length, i, max_length, size;
    max_length = 0;
    size = 1 << h->table_width;
    for (i = 0; i < h->table_width; i++) {
        if (h->lengths[i] > max_length) {
            max_length = h->lengths[i];
        }
    }
    for (bit_length=1; bit_length<=h->table_width; bit_length++) {
        int j;
        size /= 2;
        for (j=0; j < h->nlengths; j++) {
            if (h->lengths[j] == bit_length) {
                int k;
                for (k=0; k<size; k++) {
                    h->table[h->ntable+k] = j;
                    h->ntable++;
                }
            }
        }
    }
}

static void huffman_lookup(huffman *h, int* out, int byte_lookup)
{
    if (h->table == 0) {
        out[0] = h->default_value;
        out[1] = 0;
        return;
    }
    out[0] = h->table[byte_lookup >> (16-h->table_width)];
    out[1] = h->lengths[out[0]];
}

static void huffman_free(huffman *h)
{
    free(h->table);
    free(h->lengths);
}

/* These functions represent the EmbCompress class. */
static void compress_init()
{

}

static int compress_get_bits(compress *c, int length)
{
    int i, end_pos_in_bits, start_pos_in_bytes,
        end_pos_in_bytes, value, mask_sample_bits,
        unused_bits, original;

    end_pos_in_bits = c->bit_position + length - 1;
    start_pos_in_bytes = c->bit_position / 8;
    end_pos_in_bytes = end_pos_in_bits / 8;
    value = 0;

    for (i=start_pos_in_bytes; i < end_pos_in_bytes+1; i++) {
        value <<= 8;
        if (i > c->input_length) {
            break;
        }
        value |= (c->input_data[i]) & 0xFF;
    }

    unused_bits = (7 - end_pos_in_bits) % 8;
    mask_sample_bits = (1<<length) - 1;
    original = (value >> unused_bits) & mask_sample_bits;
    return original;
}

static int compress_pop(compress *c, int bit_count)
{
    int value = compress_get_bits(c, bit_count);
    c->bit_position += bit_count;
    return value;
}

static int compress_peek(compress *c, int bit_count)
{
    return compress_get_bits(c, bit_count);
}

static int compress_read_variable_length(compress *c)
{
    int q, m, s;
    m = compress_pop(c, 3);
    if (m!=7) {
        return m;
    }
    for (q=0; q<13; q++) {
        s = compress_pop(c, 1);
        if (s) {
            m++;
        }
        else {
            break;
        }
    }
    return m;
}

static int compress_load_character_length_huffman(compress *c)
{
    int count;
    huffman h;
    count = compress_pop(c, 5);
    if (count == 0) {
        /*v = compress_pop(c, 5);*/
        /* huffman = huffman_init(huffman, v); ? */
    }
    else {
        int i;
        for (i = 0; i < count; i++) {
            h.lengths[i] = 0;
        }
        for (i = 0; i < count; i++) {
            if (i==3) {
                i += compress_pop(c, 2);
            }
            h.lengths[i] = compress_read_variable_length(c);
        }
        h.nlengths = count;
        h.default_value = 8;
        huffman_build_table(&h);
    }
    c->character_length_huffman = &h;
    return 1;
}

static void compress_load_character_huffman(compress *c)
{
    int count;
    huffman h;
    count = compress_pop(c, 9);
    if (count == 0) {
        /*
        v = compress_pop(c, 9);
        huffman = huffman(v);
        */
    }
    else {
        int i;
        for (i = 0; i < count; i++) {
            h.lengths[i] = 0;
        }
        i = 0;
        while (i < count) {
            int h[2];
            huffman_lookup(c->character_length_huffman, h, compress_peek(c, 16));
            c->bit_position += h[1];
            if (h[0]==0) {
                i += h[0];
            }
            else if (h[0]==1) {
                i += 3 + compress_pop(c, 4);
            }
            else if (h[0]==2) {
                i += 20 + compress_pop(c, 9);
            }
            else {
                c->character_huffman->lengths[i] = h[0] - 2;
                i++;
            }
        }
        huffman_build_table(c->character_huffman);
    }
}

static void compress_load_distance_huffman(compress *c)
{
    int count;
    huffman h;
    count = compress_pop(c, 5);
    if (count == 0) {
        /*
        v = compress_pop(c, 5);
        c->distance_huffman = Huffman(v);
        */
    }
    else {
        int i;
        for (i = 0; i < count; i++) {
            h.lengths[i] = 0;
        }
        for (i = 0; i < count; i++) {
            h.lengths[i] = compress_read_variable_length(c);
        }
        huffman_build_table(&h);
    }
    c->distance_huffman = &h;
}
    
static void compress_load_block(compress *c)
{
    c->block_elements = compress_pop(c, 16);
    compress_load_character_length_huffman(c);
    compress_load_character_huffman(c);
    compress_load_distance_huffman(c);
}

static int compress_get_token(compress *c)
{
    int h[2];
    if (c->block_elements <= 0) {
        compress_load_block(c);
    }
    c->block_elements--;
    huffman_lookup(c->character_huffman, h, compress_peek(c, 16));
    c->bit_position += h[1];
    return h[0];
}

static int compress_get_position(compress *c)
{
    int h[2];
    int v;
    huffman_lookup(c->distance_huffman, h, compress_peek(c, 16));
    c->bit_position += h[1];
    if (h[0] == 0) {
        return 0;
    }
    v = h[0] - 1;
    v = (1<<v) + compress_pop(c, v);
    return v;
}

int hus_decompress(char *data, int length, char *output, int *output_length)
{
    int character, i, j;
    compress *c = (compress*)malloc(sizeof(compress));
    c->bit_position = 0;
    c->input_data = data;
    c->input_length = length;
    c->bits_total = length*8;
    i = 0;
    while (c->bits_total > c->bit_position && i < *output_length) {
        /* process token */
        character = 0; /* fix this */
        if (character < 0x100) {
            output[i] = (char)character;
            i++;
        }
        else if (character == 510) {
            break;
        }
        else {
            length = character - 253;
            /* not sure about i here */
            c->bit_position = i - compress_get_position(c) - 1;
            for (j=c->bit_position; j < c->bit_position+length; j++) {
                output[i] = output[j];
                i++;
            }
        }
    }
    free(c);
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
    int overall = 0;
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

    overall += circleResult;
    overall += threadResult;
    overall += formatResult;
    overall += arcResult;
    overall += create1Result;
    overall += create2Result;
    overall += svg1Result;
    overall += svg2Result;
    overall += dst1Result;
    overall += dst2Result;

    if (emb_verbose >= 0) {
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
    }
    
    embImage_free(image);
    embPattern_free(pattern);
    if (level > 0) {
        puts("More expensive tests.");
        full_test_matrix("test_matrix.txt");
    }
    if (overall == 0) {
        puts("PASS");
    }
    else {
        puts("FAIL");
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
        if (emb_verbose > 0) {
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
        if (emb_verbose > 0) {
            fprintf(stdout, "Clockwise Test:\n");
            printArcResults(bulge, arc, center.x, center.y,
                        radius, diameter,
                        chord,
                        chordMid.x, chordMid.y,
                        sagitta,   apothem,
                        incAngle,  clockwise);
        }
    }

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
        if (emb_verbose > 0) {
            fprintf(stdout, "Counter-Clockwise Test:\n");
            printArcResults(bulge, arc, center.x, center.y,
                        radius,    diameter,
                        chord,
                        chordMid.x, chordMid.y,
                        sagitta,   apothem,
                        incAngle,  clockwise);
        }
    }

    return 0;
}

int testThreadColor(void) {
    unsigned int tColor = 0xFFD25F00;
    int          tBrand = Sulky_Rayon;
    int          tNum   = threadColorNum(tColor, tBrand);
    const char*  tName  = threadColorName(tColor, tBrand);

    if (emb_verbose > 0) {
        printf("Color : 0x%X\n"
           "Brand : %d\n"
           "Num   : %d\n"
           "Name  : %s\n\n",
            tColor,
            tBrand,
            tNum, /* Solution: 1833 */
            tName); /* Solution: Pumpkin Pie */
    }
    return 0;
}

int testEmbFormat(void) {
    const char*  tName = "example.zsk";
    int format = emb_identify_format(tName);

    if (emb_verbose > 0) {
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
    }

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

//TODO: Move majority of this code into libembroidery
/*
void embPattern_designDetails(EmbPattern *pattern)
{
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    debug_message("designDetails()");
    QString appName = QApplication::applicationName();
    QString title = "Design Details";

    EmbPattern* pattern = 0;

    //TODO: This is temporary. Generate actual pattern data from the scene.
    //======================================================
    //embPattern_read(pattern, "/mydata/embroidery-designs/KDE.EXP"); //TODO: This convenience function is messed up.

    EmbReaderWriter* reader = 0;
    int readSuccessful;
    QString tmpFileName = "/mydata/embroidery-designs/KDE.EXP";

    pattern = embPattern_create();
    if(!pattern) { printf("Could not allocate memory for embroidery pattern\n"); }

    readSuccessful = 0;
    reader = embReaderWriter_getByFileName(qPrintable(tmpFileName));
    if(!reader)
    {
        readSuccessful = 0;
        printf("Unsupported read file type\n");
    }
    else
    {
        readSuccessful = reader->reader(pattern, qPrintable(tmpFileName));
        if(!readSuccessful) printf("Reading file was unsuccessful\n");
    }
    free(reader);
    if(!readSuccessful)
    {
        embPattern_free(pattern);
    }
    //======================================================


    EmbRect bounds = embPattern_calcBoundingBox(pattern);

    int colors = 1;
    int num_stitches = 0;
    int real_stitches = 0;
    int jump_stitches = 0;
    int trim_stitches = 0;
    int unknown_stitches = 0;
    int num_colors = 0;
    double minx = 0.0, maxx = 0.0, miny = 0.0, maxy = 0.0;
    double min_stitchlength = 999.0;
    double max_stitchlength = 0.0;
    double total_stitchlength = 0.0;
    int number_of_minlength_stitches = 0;
    int number_of_maxlength_stitches = 0;

    double xx = 0.0, yy = 0.0;
    double dx = 0.0, dy = 0.0;
    double length = 0.0;

    num_colors = embThreadList_count(pattern->threadList);
    num_stitches = embStitchList_count(pattern->stitchList);
    if(num_stitches == 0)
    {
        QMessageBox::warning(this, tr("No Design Loaded"), tr("<b>A design needs to be loaded or created before details can be determined.</b>"));
        return;
    }
    QVector<double> stitchLengths;

    double totalColorLength = 0.0;
    for(int i = 0; i < num_stitches; i++)
    {
        dx = embStitchList_getAt(pattern->stitchList, i).xx - xx;
        dy = embStitchList_getAt(pattern->stitchList, i).yy - yy;
        xx = embStitchList_getAt(pattern->stitchList, i).xx;
        yy = embStitchList_getAt(pattern->stitchList, i).yy;
        length=sqrt(dx * dx + dy * dy);
        totalColorLength += length;
        if(i > 0 && embStitchList_getAt(pattern->stitchList, i-1).flags != NORMAL)
            length = 0.0; //can't count first normal stitch;
        if(!(embStitchList_getAt(pattern->stitchList, i).flags & (JUMP | TRIM)))
        {
            real_stitches++;
            if(length > max_stitchlength) { max_stitchlength = length; number_of_maxlength_stitches = 0; }
            if(length == max_stitchlength) number_of_maxlength_stitches++;
            if(length > 0 && length < min_stitchlength)
            {
                min_stitchlength = length;
                number_of_minlength_stitches = 0;
            }
            if(length == min_stitchlength) number_of_minlength_stitches++;
            total_stitchlength += length;
            if(xx < minx) minx = xx;
            if(xx > maxx) maxx = xx;
            if(yy < miny) miny = yy;
            if(yy > maxy) maxy = yy;
        }
        if(embStitchList_getAt(pattern->stitchList, i).flags & JUMP)
        {
            jump_stitches++;
        }
        if(embStitchList_getAt(pattern->stitchList, i).flags & TRIM)
        {
            trim_stitches++;
        }
        if(embStitchList_getAt(pattern->stitchList, i).flags & STOP)
        {
            stitchLengths.push_back(totalColorLength);
            totalColorLength = 0;
            colors++;
        }
        if(embStitchList_getAt(pattern->stitchList, i).flags & END)
        {
            stitchLengths.push_back(totalColorLength);
        }
    }

    //second pass to fill bins now that we know max stitch length
#define NUMBINS 10
    int bin[NUMBINS+1];
    for(int i = 0; i <= NUMBINS; i++)
    {
        bin[i]=0;
    }

    for(int i = 0; i < num_stitches; i++)
    {
        dx = embStitchList_getAt(pattern->stitchList, i).xx - xx;
        dy = embStitchList_getAt(pattern->stitchList, i).yy - yy;
        xx = embStitchList_getAt(pattern->stitchList, i).xx;
        yy = embStitchList_getAt(pattern->stitchList, i).yy;
        if(i > 0 && embStitchList_getAt(pattern->stitchList, i-1).flags == NORMAL && embStitchList_getAt(pattern->stitchList, i).flags == NORMAL)
        {
            length=sqrt(dx * dx + dy * dy);
            bin[int(floor(NUMBINS*length/max_stitchlength))]++;
        }
    }

    double binSize = max_stitchlength / NUMBINS;

    QString str;
    for(int i = 0; i < NUMBINS; i++)
    {
        str += QString::number(binSize * (i), 'f', 1) + " - " + QString::number(binSize * (i+1), 'f', 1) + " mm: " +  QString::number(bin[i]) + "\n\n";
    }

    QDialog dialog(this);

    QGridLayout* grid = new QGridLayout(this);
    grid->setSpacing(2);

    grid->addWidget(new QLabel(tr("Stitches:")),0,0,1,1);
    grid->addWidget(new QLabel(QString::number(num_stitches)), 0, 1, 1, 1);
    grid->addWidget(new QLabel(tr("Colors:")),1,0,1,1);
    grid->addWidget(new QLabel(QString::number(num_colors)), 1, 1, 1, 1);
    grid->addWidget(new QLabel(tr("Jumps:")),2,0,1,1);
    grid->addWidget(new QLabel(QString::number(jump_stitches)), 2, 1, 1, 1);
    grid->addWidget(new QLabel(tr("Top:")),3,0,1,1);
    grid->addWidget(new QLabel(QString::number(bounds.top) + " mm"), 3, 1, 1, 1);
    grid->addWidget(new QLabel(tr("Left:")),4,0,1,1);
    grid->addWidget(new QLabel(QString::number(bounds.left) + " mm"), 4, 1, 1, 1);
    grid->addWidget(new QLabel(tr("Bottom:")),5,0,1,1);
    grid->addWidget(new QLabel(QString::number(bounds.bottom) + " mm"), 5, 1, 1, 1);
    grid->addWidget(new QLabel(tr("Right:")),6,0,1,1);
    grid->addWidget(new QLabel(QString::number(bounds.right) + " mm"), 6, 1, 1, 1);
    grid->addWidget(new QLabel(tr("Width:")),7,0,1,1);
    grid->addWidget(new QLabel(QString::number((bounds.right - bounds.left)) + " mm"), 7, 1, 1, 1);
    grid->addWidget(new QLabel(tr("Height:")),8,0,1,1);
    grid->addWidget(new QLabel(QString::number((bounds.bottom - bounds.top)) + " mm"), 8, 1, 1, 1);
    grid->addWidget(new QLabel(tr("\nStitch Distribution: \n")),9,0,1,2);
    grid->addWidget(new QLabel(str), 10, 0, 1, 1);
    grid->addWidget(new QLabel(tr("\nThread Length By Color: \n")),11,0,1,2);
    int currentRow = 12;
*/
/*
    for(int i = 0; i < num_colors; i++)
    {
        QFrame *frame = new QFrame();
        frame->setGeometry(0,0,30,30);
        QPalette palette = frame->palette();
        EmbColor t = embThreadList_getAt(pattern->threadList, i).color;
        palette.setColor(backgroundRole(), QColor( t.r, t.g, t.b ) );
        frame->setPalette( palette );
        frame->setAutoFillBackground(true);
        grid->addWidget(frame, currentRow,0,1,1);
        debug_message("size: %d i: %d", stitchLengths.size(), i);
        grid->addWidget(new QLabel(QString::number(stitchLengths.at(i)) + " mm"), currentRow,1,1,1);
        currentRow++;
    }
*/
/*
    QDialogButtonBox buttonbox(Qt::Horizontal, &dialog);
    QPushButton button(&dialog);
    button.setText("Ok");
    buttonbox.addButton(&button, QDialogButtonBox::AcceptRole);
    buttonbox.setCenterButtons(true);
    connect(&buttonbox, SIGNAL(accepted()), &dialog, SLOT(accept()));

    grid->addWidget(&buttonbox, currentRow, 0, 1, 2);

    dialog.setWindowTitle(title);
    dialog.setMinimumWidth(100);
    dialog.setMinimumHeight(50);
    dialog.setLayout(grid);
    dialog.exec();
    QApplication::restoreOverrideCursor();

}
*/

void embVector_print(EmbVector v, char *label)
{
    fprintf(stdout, "%sX = %f\n", v.x);
    fprintf(stdout, "%sY = %f\n", v.y);
}

void embArc_print(EmbArc arc)
{
    embVector_print(arc.start, "start");
    embVector_print(arc.mid, "middle");
    embVector_print(arc.end, "end");
}

static void reverse_byte_order(void *b, int bytes)
{
    char swap;
    if (bytes == 2) {
        swap = *((char*)b+0);
        *((char*)b+0) = *((char*)b+1);
        *((char*)b+1) = swap;
    }
    else {
        swap = *((char*)b+0);
        *((char*)b+0) = *((char*)b+3);
        *((char*)b+3) = swap;
        swap = *((char*)b+1);
        *((char*)b+1) = *((char*)b+2);
        *((char*)b+2) = swap;
    }
}

/* Checks that there are enough bytes to interpret the header,
 * stops possible segfaults when reading in the header bytes.
 *
 * Returns 0 if there aren't enough, or the length of the file
 * if there are.
 */
static int check_header_present(FILE* file, int minimum_header_length)
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

/* Returns an EmbArcObject. It is created on the stack. */
EmbArcObject embArcObject_make(double sx, double sy, double mx,
                                double my, double ex, double ey) {
    EmbArcObject stackArcObj;
    stackArcObj.arc.start.x = sx;
    stackArcObj.arc.start.y = sy;
    stackArcObj.arc.mid.x   = mx;
    stackArcObj.arc.mid.y   = my;
    stackArcObj.arc.end.x   = ex;
    stackArcObj.arc.end.y   = ey;
    return stackArcObj;
}

double radians(double degree) {
    return degree*embConstantPi/180.0;
}

double degrees(double radian) {
    return radian*180.0/embConstantPi;
}

/* Calculus based approach at determining whether a polygon is clockwise or counterclockwise.
 * Returns true if arc is clockwise. */
char isArcClockwise(EmbArc arc) {
    double edge1 = (arc.mid.x-arc.start.x)*(arc.mid.y+arc.start.y);
    double edge2 = (arc.end.x-arc.mid.x)*(arc.end.y+arc.mid.y);
    double edge3 = (arc.start.x-arc.end.x)*(arc.start.y+arc.end.y);
    if (edge1 + edge2 + edge3 >= 0.0) {
        return 1;
    }
    return 0;
}

/* Calculates the CenterPoint of the Arc */
void getArcCenter(EmbArc arc, EmbVector* arcCenter) {
    EmbVector a_vec, b_vec, aMid_vec, bMid_vec, aPerp_vec, bPerp_vec, pa, pb;
    EmbLine line1, line2;
    double paAngleInRadians, pbAngleInRadians;
    embVector_subtract(arc.mid, arc.start, &a_vec);
    embVector_average(arc.mid, arc.start, &aMid_vec);

    paAngleInRadians = embVector_angle(a_vec) + radians(90.0);
    pa = embVector_unit(paAngleInRadians);
    embVector_add(aMid_vec, pa, &aPerp_vec);

    embVector_subtract(arc.end, arc.mid, &b_vec);
    embVector_average(arc.end, arc.mid, &bMid_vec);

    pbAngleInRadians = embVector_angle(b_vec) + radians(90.0);
    pb = embVector_unit(pbAngleInRadians);
    embVector_add(bMid_vec, pb, &bPerp_vec);

    line1.start = aMid_vec;
    line1.end = aPerp_vec;
    line2.start = bMid_vec;
    line2.end = bPerp_vec;
    *arcCenter = embLine_intersectionPoint(line1, line2);
    if (emb_error) {
        puts("ERROR: no intersection, cannot find arcCenter.");
    }
}

/* Calculates Arc Geometry from Bulge Data.
 * Returns false if there was an error calculating the data. */
char getArcDataFromBulge(double bulge,
                         EmbArc *arc,
                         double* arcCenterX,        double* arcCenterY,
                         double* radius,            double* diameter,
                         double* chord,
                         double* chordMidX,         double* chordMidY,
                         double* sagitta,           double* apothem,
                         double* incAngleInDegrees, char*   clockwise) {
    double incAngleInRadians;
    double chordAngleInRadians;
    double sagittaAngleInRadians;
    double w, h, fx ,fy, dx, dy;
    EmbVector arcCenter;

    /* Confirm the direction of the Bulge */
    if (bulge >= 0.0) { 
        *clockwise = 0;
    } else { 
        *clockwise = 1;
    }

    /* Calculate the Included Angle in Radians */
    incAngleInRadians = atan(bulge)*4.0;

    /* Calculate the Chord */
    w = fabs(arc->start.x - arc->end.x);
    h = fabs(arc->start.y - arc->end.y);
    *chord = sqrt(w*w + h*h);

    /* Calculate the Radius */
    *radius = fabs(*chord / (2.0 * sin(incAngleInRadians / 2.0)));

    /* Calculate the Diameter */
    *diameter = fabs(*radius * 2.0);

    /* Calculate the Sagitta */
    *sagitta = fabs((*chord / 2.0) * bulge);

    /* Calculate the Apothem */
    *apothem = fabs(*radius - *sagitta);

    /* Calculate the Chord MidPoint */
    *chordMidX = (arc->start.x + arc->end.x) / 2.0;
    *chordMidY = (arc->start.y + arc->end.y) / 2.0;

    /* Calculate the Chord Angle (from arcStart to arcEnd) */
    dx = arc->end.x - arc->start.x;
    dy = arc->end.y - arc->start.y;
    chordAngleInRadians = atan2(dy, dx);

    /* Calculate the Sagitta Angle (from chordMid to arcMid) */
    if (*clockwise) sagittaAngleInRadians = chordAngleInRadians + radians(90.0);
    else           sagittaAngleInRadians = chordAngleInRadians - radians(90.0);

    /* Calculate the Arc MidPoint */
    fx = *sagitta * cos(sagittaAngleInRadians);
    fy = *sagitta * sin(sagittaAngleInRadians);
    arc->mid.x = *chordMidX + fx;
    arc->mid.y = *chordMidY + fy;

    getArcCenter(*arc, &arcCenter);
    *arcCenterX = arcCenter.x;
    *arcCenterY = arcCenter.y;

    /* Convert the Included Angle from Radians to Degrees */
    *incAngleInDegrees = degrees(incAngleInRadians);

    /* Confirm the direction of the Arc, it should match the Bulge */
    if (*clockwise != isArcClockwise(*arc)) {
        fprintf(stderr, "Arc and Bulge direction do not match.\n");
        return 0;
    }

    return 1;
}

/* Computational Geometry for Circles */

/****************************************************************
 * Calculates the intersection points of two overlapping circles.
 * Returns true if the circles intersect.
 * Returns false if the circles do not intersect.
 ****************************************************************/
int getCircleCircleIntersections(EmbCircle c0, EmbCircle c1,
                                 EmbVector *p0, EmbVector *p1)
{
    EmbVector delta;
    double a, h, px2, py2, mx, my, d;
    /* Distance between centers */
    embVector_subtract(c1.center, c0.center, &delta);
    d = embVector_length(delta);

    /*Circles share centers. This results in division by zero,
      infinite solutions or one circle being contained within the other. */
    if (d == 0.0) {
        return 0;
    } else if (d > (c0.radius + c1.radius)) {
        /* Circles do not touch each other */
        return 0;
    } else if (d < (c0.radius - c1.radius)) {
        /* One circle is contained within the other */
        return 0;
    }
    /*
     * Considering the two right triangles p0p2p3 and p1p2p3 we can write:
     * a^2 + h^2 = r0^2 and b^2 + h^2 = r1^2
     *
     * BEGIN PROOF
     *
     * Remove h^2 from the equation by setting them equal to themselves:
     *     r0^2 - a^2 = r1^2 - b^2
     * Substitute b with (d - a) since it is proven that d = a + b:
     *     r0^2 - a^2 = r1^2 - (d - a)^2
     * Complete the square:
     *     r0^2 - a^2 = r1^2 - (d^2 -2da + a^2)
     * Subtract r1^2 from both sides:
     *     r0^2 - r1^2 - a^2 = -(d^2 -2da + a^2)
     * Invert the signs:
     *     r0^2 - r1^2 - a^2 = -d^2 + 2da - a^2
     * Adding a^2 to each side cancels them out:
     *     r0^2 - r1^2 = -d^2 + 2da
     * Add d^2 to both sides to shift it to the other side:
     *     r0^2 - r1^2 + d^2 = 2da
     * Divide by 2d to finally solve for a:
     *     a = (r0^2 - r1^2 + d^2)/ (2d)
     *
     * END PROOF
     */

    a = ((c0.radius*c0.radius) - (c1.radius*c1.radius) + (d*d)) / (2.0 * d);
    /* Solve for h by substituting a into a^2 + h^2 = r0^2 */
    h = sqrt((c0.radius*c0.radius) - (a*a));

    /*Find point p2 by adding the a offset in relation to line d to point p0 */
    px2 = c0.center.x + (delta.x * a/d);
    py2 = c0.center.y + (delta.y * a/d);

    /* Tangent circles have only one intersection

       TODO: using == in floating point arithmetic
       doesn't account for the machine accuracy, having
       a stated (double) tolerance value would help.
    */
    if (d == (c0.radius + c1.radius)) {
        p0->x = px2;
        p0->y = py2;
        p1->x = px2;
        p1->y = py2;
        return 1;
    }

    /* Get the perpendicular slope by multiplying by the negative reciprocal
     * Then multiply by the h offset in relation to d to get the actual offsets */
    mx = -(delta.y * h/d);
    my =  (delta.x * h/d);

    /* Add the offsets to point p2 to obtain the intersection points */
    p0->x = px2 + mx;
    p0->y = py2 + my;
    p1->x = px2 - mx;
    p1->y = py2 - my;

    return 1;
}

/****************************************************************
 * Calculates the tangent points on circle from a given point.
 * Returns true if the given point lies outside the circle.
 * Returns false if the given point is inside the circle.
 ****************************************************************/
int getCircleTangentPoints(EmbCircle c, EmbVector point, EmbVector *t0, EmbVector *t1)
{
    EmbCircle p;
    double hyp;
    /* Distance to center of circle */
    hyp = embVector_distance(point, c.center);
    /* Point is inside the circle */
    if (hyp < c.radius) {
        return 0;
    } else if (hyp == c.center.y) {
        /* Point is lies on the circle, so there is only one tangent point */
        *t0 = point;
        *t1 = point;
        return 1;
    }

    /* Since the tangent lines are always perpendicular to the radius, so
     * we can use the Pythagorean theorem to solve for the missing side */
    p.center = point;
    p.radius = sqrt((hyp*hyp) - (c.radius*c.radius));
    return getCircleCircleIntersections(c, p, t0, t1);
}

/* Returns an EmbColor. It is created on the stack. */
EmbColor embColor_make(unsigned char r, unsigned char g, unsigned char b) {
    EmbColor stackColor;
    stackColor.r = r;
    stackColor.g = g;
    stackColor.b = b;
    return stackColor;
}

/* Returns a pointer to an EmbColor. It is created on the heap. 
The caller is responsible for freeing the allocated memory. */
EmbColor* embColor_create(unsigned char r, unsigned char g, unsigned char b) {
    EmbColor* heapColor = (EmbColor*)malloc(sizeof(EmbColor));
    if (!heapColor) {
        printf("ERROR: emb-color.c embColor_create(), ");
        printf("cannot allocate memory for heapColor\n");
        return 0;
    }
    heapColor->r = r;
    heapColor->g = g;
    heapColor->b = b;
    return heapColor;
}

/* Converts a 6 digit hex string (I.E. "00FF00") 
    into an EmbColor and returns it. */
EmbColor embColor_fromHexStr(char* val) {
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

double embEllipse_diameterX(EmbEllipse ellipse) {
    return ellipse.radiusX * 2.0;
}

double embEllipse_diameterY(EmbEllipse ellipse) {
    return ellipse.radiusY * 2.0;
}

double embEllipse_width(EmbEllipse ellipse) {
    return ellipse.radiusX * 2.0;
}

double embEllipse_height(EmbEllipse ellipse) {
    return ellipse.radiusY * 2.0;
}

/* Returns an EmbEllipseObject. It is created on the stack. */
EmbEllipseObject embEllipseObject_make(double cx, double cy, 
                                        double rx, double ry) {
    EmbEllipseObject stackEllipseObj;
    stackEllipseObj.ellipse.centerX = cx;
    stackEllipseObj.ellipse.centerY = cy;
    stackEllipseObj.ellipse.radiusX = rx;
    stackEllipseObj.ellipse.radiusY = ry;
    return stackEllipseObj;
}

/* Returns an EmbLine. It is created on the stack. */
EmbLine embLine_make(double x1, double y1, double x2, double y2) {
    EmbLine line;
    line.start.x = x1;
    line.start.y = y1;
    line.end.x = x2;
    line.end.y = y2;
    return line;
}

/*! Finds the normalized vector perpendicular (clockwise) to the line
 * given by v1->v2 (normal to the line) */
void embLine_normalVector(EmbLine line, EmbVector* result, int clockwise) {
    double temp;
    if (!result) {
        printf("ERROR: emb-line.c embLine_normalVector(), ");
        printf("result argument is null\n");
        return;
    }
    embVector_subtract(line.end, line.start, result);
    embVector_normalize(*result, result);
    temp = result->x;
    result->x = result->y;
    result->y = -temp;
    if (!clockwise) {
        result->x = -result->x;
        result->y = -result->y;
    }
}

EmbVector embLine_toVector(EmbLine line)
{
    EmbVector v;
    embVector_subtract(line.end, line.start, &v);
    return v;
}

/*
 * Finds the intersection of two lines given by v1->v2 and v3->v4
 * and sets the value in the result variable.
 */
EmbVector embLine_intersectionPoint(EmbLine line1, EmbLine line2)
{
    double det, C2, C1, tolerance;
    EmbVector vec1, vec2, result;
    emb_error = 0;
    vec1 = embLine_toVector(line1);
    vec2 = embLine_toVector(line2);
    C2 = embVector_cross(line1.start, vec1);
    C1 = embVector_cross(line2.start, vec2);

    tolerance = 1e-10;
    det = embVector_cross(vec2, vec1);

    if (fabs(det) < tolerance) {
        emb_error = 1;
        return result;
    }
    result.x = (vec2.x * C2 - vec1.x * C1) / det;
    result.y = (vec2.y * C2 - vec1.y * C1) / det;
    return result;
}

EmbArray* embArray_create(int type) {
    EmbArray *p;
    p = (EmbArray*)malloc(sizeof(EmbArray));
    p->type = type;
    p->length = CHUNK_SIZE;
    p->count = 0;
    switch (p->type) {
    case EMB_ARC:
        p->arc = (EmbArcObject*)malloc(CHUNK_SIZE*sizeof(EmbArcObject));
        break;
    case EMB_CIRCLE:
        p->circle = (EmbCircleObject*)malloc(CHUNK_SIZE*sizeof(EmbCircleObject));
        break;
    case EMB_ELLIPSE:
        p->ellipse = (EmbEllipseObject*)malloc(CHUNK_SIZE*sizeof(EmbEllipseObject));
        break;
    case EMB_FLAG:
        p->flag = (int*)malloc(CHUNK_SIZE*sizeof(int));
        break;
    case EMB_PATH:
        p->path = (EmbPathObject**)malloc(CHUNK_SIZE*sizeof(EmbPathObject));
        break;
    case EMB_POINT:
        p->point = (EmbPointObject*)malloc(CHUNK_SIZE*sizeof(EmbPointObject));
        break;
    case EMB_LINE:
        p->line = (EmbLineObject*)malloc(CHUNK_SIZE*sizeof(EmbLineObject));
        break;
    case EMB_POLYGON:
        p->polygon = (EmbPolygonObject**)malloc(CHUNK_SIZE*sizeof(EmbPolygonObject*));
        break;
    case EMB_POLYLINE:
        p->polyline = (EmbPolylineObject**)malloc(CHUNK_SIZE*sizeof(EmbPolylineObject*));
        break;
    case EMB_RECT:
        p->rect = (EmbRectObject*)malloc(CHUNK_SIZE*sizeof(EmbRectObject));
        break;
    case EMB_SPLINE:
        p->spline = (EmbSplineObject*)malloc(CHUNK_SIZE*sizeof(EmbSplineObject));
        break;
    case EMB_STITCH:
        p->stitch = (EmbStitch*)malloc(CHUNK_SIZE*sizeof(EmbStitch));
        break;
    case EMB_THREAD:
        p->thread = (EmbThread*)malloc(CHUNK_SIZE*sizeof(EmbThread));
        break;
    case EMB_VECTOR:
        p->vector = (EmbVector*)malloc(CHUNK_SIZE*sizeof(EmbVector));
        break;
    default:
        break;
    }
    return p;
}

int embArray_resize(EmbArray *p) {
    if (p->count < p->length) {
        return 1;
    }
    p->length += CHUNK_SIZE;
    switch (p->type) {
    case EMB_ARC:
        p->arc = (EmbArcObject *)realloc(p->arc, p->length*sizeof(EmbArcObject));
        if (!p->arc) return 0;
        break;
    case EMB_CIRCLE:
        p->circle = (EmbCircleObject *)realloc(p->circle, p->length*sizeof(EmbCircleObject));
        if (!p->circle) return 0;
        break;
    case EMB_ELLIPSE:
        p->ellipse = (EmbEllipseObject *)realloc(p->ellipse, p->length*sizeof(EmbEllipseObject));
        if (!p->ellipse) return 0;
        break;
    case EMB_FLAG:
        p->flag = (int *)realloc(p->flag, p->length*sizeof(int));
        if (!p->flag) return 0;
        break;
    case EMB_PATH:
        p->path = (EmbPathObject **)realloc(p->path, p->length*sizeof(EmbPathObject*));
        if (!p->path) return 0;
        break;
    case EMB_POINT:
        p->point = (EmbPointObject *)realloc(p->point, p->length*sizeof(EmbPointObject));
        if (!p->point) return 0;
        break;
    case EMB_LINE:
        p->line = (EmbLineObject *)realloc(p->line, p->length*sizeof(EmbLineObject));
        if (!p->line) return 0;
        break;
    case EMB_POLYGON:
        p->polygon = (EmbPolygonObject **)realloc(p->polygon, p->length*sizeof(EmbPolygonObject*));
        if (!p->polygon) return 0;
        break;
    case EMB_POLYLINE:
        p->polyline = (EmbPolylineObject **)realloc(p->polyline, p->length*sizeof(EmbPolylineObject*));
        if (!p->polyline) return 0;
        break;
    case EMB_RECT:
        p->rect = (EmbRectObject *)realloc(p->rect, p->length*sizeof(EmbRectObject));
        if (!p->rect) return 0;
        break;
    case EMB_SPLINE:
        p->spline = (EmbSplineObject *)realloc(p->spline, p->length*sizeof(EmbSplineObject));
        if (!p->spline) return 0;
        break;
    case EMB_STITCH:
        p->stitch = (EmbStitch *)realloc(p->stitch, p->length*sizeof(EmbStitch));
        if (!p->stitch) return 0;
        break;
    case EMB_THREAD:
        p->thread = (EmbThread *)realloc(p->thread, p->length*sizeof(EmbThread));
        if (!p->thread) return 0;
        break;
    case EMB_VECTOR:
        p->vector = (EmbVector *)realloc(p->vector, p->length*sizeof(EmbVector));
        if (!p->vector) return 0;
        break;
    default:
        break;
    }
    return 1;
}

void embArray_copy(EmbArray *dst, EmbArray *src)
{
    dst = (EmbArray*)malloc(sizeof(EmbArray));
    dst->type = src->type;
    dst->length = src->length;
    dst->count = src->count;
    embArray_resize(dst);
    switch (src->type) {
    case EMB_ARC:
        memcpy(dst->arc, src->arc, sizeof(EmbArcObject)*src->count);
        break;
    case EMB_CIRCLE:
        memcpy(dst->circle, src->circle, sizeof(EmbCircleObject)*src->count);
        break;
    case EMB_ELLIPSE:
        memcpy(dst->ellipse, src->ellipse, sizeof(EmbEllipseObject)*src->count);
        break;
    case EMB_FLAG:
        memcpy(dst->flag, src->flag, sizeof(int)*src->count);
        break;
    case EMB_PATH:
        memcpy(dst->path, src->path, sizeof(EmbPathObject)*src->count);
        break;
    case EMB_POINT:
        memcpy(dst->point, src->point, sizeof(EmbPointObject)*src->count);
        break;
    case EMB_LINE:
        memcpy(dst->line, src->line, sizeof(EmbLineObject)*src->count);
        break;
    case EMB_POLYGON:
        memcpy(dst->polygon, src->polygon, sizeof(int)*src->count);
        break;
    case EMB_POLYLINE:
        memcpy(dst->polyline, src->polyline, sizeof(int)*src->count);
        break;
    case EMB_RECT:
        memcpy(dst->rect, src->rect, sizeof(int)*src->count);
        break;
    case EMB_SPLINE:
        memcpy(dst->spline, src->spline, sizeof(int)*src->count);
        break;
    case EMB_STITCH:
        memcpy(dst->stitch, src->stitch, sizeof(int)*src->count);
        break;
    case EMB_THREAD:
        memcpy(dst->thread, src->thread, sizeof(int)*src->count);
        break;
    case EMB_VECTOR:
        memcpy(dst->vector, src->vector, sizeof(int)*src->count);
        break;
    default:
        break;
    }
}

int embArray_addArc(EmbArray* p, EmbArc arc, int lineType, EmbColor color) {
    p->count++;
    if (!embArray_resize(p)) {
        return 0;
    }
    p->arc[p->count - 1].arc = arc;
    p->arc[p->count - 1].lineType = lineType;
    p->arc[p->count - 1].color = color;
    return 1;
}

int embArray_addCircle(EmbArray* p, EmbCircle circle,
                        int lineType, EmbColor color) {
    p->count++;
    if (!embArray_resize(p)) {
        return 0;
    }
    p->circle[p->count - 1].circle = circle;
    p->circle[p->count - 1].lineType = lineType;
    p->circle[p->count - 1].color = color;
    return 1;
}

int embArray_addEllipse(EmbArray* p,
    EmbEllipse ellipse, double rotation, int lineType, EmbColor color) {
    p->count++;
    if (!embArray_resize(p)) {
        return 0;
    }
    p->ellipse[p->count - 1].ellipse = ellipse;
    p->ellipse[p->count - 1].rotation = rotation;
    p->ellipse[p->count - 1].lineType = lineType;
    p->ellipse[p->count - 1].color = color;
    return 1;
}

int embArray_addFlag(EmbArray* p, int flag) {
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->flag[p->count - 1] = flag;
    return 1;
}

int embArray_addLine(EmbArray* p, EmbLineObject line) {
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->line[p->count - 1] = line;
    return 1;
}

int embArray_addPath(EmbArray* p, EmbPathObject *path) {
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->path[p->count - 1] = (EmbPathObject*)malloc(sizeof(EmbPathObject));
    if (!p->path[p->count - 1]) {
        printf("ERROR: emb-polygon.c embArray_create(), ");
        printf("cannot allocate memory for heapPolygonObj\n");
        return 0;
    }
    p->path[p->count - 1] = path;
    return 1;
}

int embArray_addPoint(EmbArray* p, EmbPointObject *point) {
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->point[p->count - 1] = *point;
    return 1;
}

int embArray_addPolygon(EmbArray* p, EmbPolygonObject *polygon) {
    p->count++;
    if (!embArray_resize(p)) {
        return 0;
    }
    p->polygon[p->count - 1] = (EmbPolygonObject*)malloc(sizeof(EmbPolygonObject));
    if (!p->polygon[p->count - 1]) {
        printf("ERROR: emb-polygon.c embArray_create(), ");
        printf("cannot allocate memory for heapPolygonObj\n");
        return 0;
    }
    p->polygon[p->count - 1] = polygon;
    return 1;
}

int embArray_addPolyline(EmbArray* p, EmbPolylineObject *polyline) {
    p->count++;
    if (!embArray_resize(p)) {
        return 0;
    }
    p->polyline[p->count - 1] = (EmbPolylineObject*)malloc(sizeof(EmbPolylineObject));
    if (!p->polyline[p->count - 1]) {
        printf("ERROR: emb-polyline.c embArray_create(), ");
        printf("cannot allocate memory for heapPolylineObj\n");
        return 0;
    }
    p->polyline[p->count - 1] = polyline;
    return 1;
}

int embArray_addRect(EmbArray* p,
    EmbRect rect, int lineType, EmbColor color) {
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->rect[p->count - 1].rect = rect;
    p->rect[p->count - 1].lineType = lineType;
    p->rect[p->count - 1].color = color;
    return 1;
}

int embArray_addStitch(EmbArray* p, EmbStitch st) {
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->stitch[p->count - 1] = st;
    return 1;
}

int embArray_addThread(EmbArray* p, EmbThread thread) {
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->thread[p->count - 1] = thread;
    return 1;
}

int embArray_addVector(EmbArray* p, EmbVector vector) {
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->vector[p->count - 1] = vector;
    return 1;
}

void embArray_free(EmbArray* p) {
    int i;
    if (!p) {
        return;
    }
    switch (p->type) {
    case EMB_ARC:
        free(p->arc);
        break;
    case EMB_CIRCLE:
        free(p->circle);
        break;
    case EMB_ELLIPSE:
        free(p->ellipse);
        break;
    case EMB_FLAG:
        free(p->flag);
        break;
    case EMB_LINE:
        free(p->line);
        break;
    case EMB_PATH:
        for (i = 0; i < p->count; i++) {
            embArray_free(p->path[i]->pointList);
        }
        free(p->path);
        break;
    case EMB_POINT:
        free(p->point);
        break;
    case EMB_POLYGON:
        for (i = 0; i < p->count; i++) {
            embArray_free(p->polygon[i]->pointList);
        }
        free(p->polygon);
        break;
    case EMB_POLYLINE:
        for (i = 0; i < p->count; i++) {
            embArray_free(p->polyline[i]->pointList);
        }
        free(p->polyline);
        break;
    case EMB_RECT:
        free(p->rect);
        break;
    case EMB_SPLINE:
        free(p->spline);
        break;
    case EMB_STITCH:
        free(p->stitch);
        break;
    case EMB_THREAD:
        free(p->thread);
        break;
    case EMB_VECTOR:
        free(p->vector);
        break;
    default:
        break;
    }
    free(p);
}

/* Read and write system for multiple byte types.
 *
 * The caller passes the function to read/write from, the
 * memory location as a void pointer and a mode identifier that describes
 * the type. This way we can abstract out the endianness of the
 * system running the library and don't have to maintain many functions,
 * just two.
 */
static void fread_int(FILE* f, void *b, int mode)
{
    int endian = mode & 0x01;
    int length = mode - endian;
    fread(b, 1, length, f);
    if (endian != ENDIAN_HOST) {
        reverse_byte_order(b, length);
    }
}

static void fwrite_int(FILE* f, void *b, int mode) {
    int endian = mode & 0x01;
    int length = mode - endian;
    if (endian != ENDIAN_HOST) {
        reverse_byte_order(b, length);
    }
    fwrite(b, 1, length, f);
}

short fread_int16(FILE* f) {
    short x;
    fread_int(f, &x, EMB_INT16_LITTLE);
    return x;
}

unsigned short fread_uint16(FILE* f) {
    unsigned short x;
    fread_int(f, &x, EMB_INT16_LITTLE);
    return x;
}

int fread_int32(FILE* f) {
    int x;
    fread_int(f, &x, EMB_INT32_LITTLE);
    return x;
}

unsigned int fread_uint32(FILE* f) {
    unsigned int x;
    fread_int(f, &x, EMB_INT32_LITTLE);
    return x;
}

short fread_int16_be(FILE* f) {
    short x;
    fread_int(f, &x, EMB_INT16_BIG);
    return x;
}

unsigned short fread_uint16_be(FILE* f) {
    unsigned short x;
    fread_int(f, &x, EMB_INT16_BIG);
    return x;
}

int fread_int32_be(FILE* f) {
    int x;
    fread_int(f, &x, EMB_INT32_BIG);
    return x;
}

unsigned int fread_uint32_be(FILE* f) {
    unsigned int x;
    fread_int(f, &x, EMB_INT32_BIG);
    return x;
}

void fpad(FILE* file, char c, int n) {
    int i;
    for (i = 0; i < n; i++) {
        fwrite(&c, 1, 1, file);
    }
}

static unsigned int sectorSize(bcf_file* bcfFile) {
    /* version 3 uses 512 byte */
    if (bcfFile->header.majorVersion == 3) {
        return 512;
    }
    return 4096;
}

static int haveExtraDIFATSectors(bcf_file* file) {
    return (int)(numberOfEntriesInDifatSector(file->difat) > 0);
}

static int seekToOffset(FILE* file, const unsigned int offset) {
    return fseek(file, offset, SEEK_SET);
}

static int seekToSector(bcf_file* bcfFile, FILE* file, const unsigned int sector) {
    unsigned int offset = sector * sectorSize(bcfFile) + sectorSize(bcfFile);
    return seekToOffset(file, offset);
}

static void parseDIFATSectors(FILE* file, bcf_file* bcfFile) {
    unsigned int numberOfDifatEntriesStillToRead = bcfFile->header.numberOfFATSectors - NumberOfDifatEntriesInHeader;
    unsigned int difatSectorNumber = bcfFile->header.firstDifatSectorLocation;
    while ((difatSectorNumber != CompoundFileSector_EndOfChain) && (numberOfDifatEntriesStillToRead > 0)) {
        seekToSector(bcfFile, file, difatSectorNumber);
        difatSectorNumber = readFullSector(file, bcfFile->difat, &numberOfDifatEntriesStillToRead);
    }
}

static int bcfFile_read(FILE* file, bcf_file* bcfFile) {
    unsigned int i, numberOfDirectoryEntriesPerSector;
    unsigned int directorySectorToReadFrom;

    bcfFile->header = bcfFileHeader_read(file);
    if (!bcfFileHeader_isValid(bcfFile->header)) {
        printf("Failed to parse header\n");
        return 0;
    }

    bcfFile->difat = bcf_difat_create(file, bcfFile->header.numberOfFATSectors, sectorSize(bcfFile));
    if (haveExtraDIFATSectors(bcfFile)) {
        parseDIFATSectors(file, bcfFile);
    }

    bcfFile->fat = bcfFileFat_create(sectorSize(bcfFile));
    for (i = 0; i < bcfFile->header.numberOfFATSectors; ++i) {
        unsigned int fatSectorNumber = bcfFile->difat->fatSectorEntries[i];
        seekToSector(bcfFile, file, fatSectorNumber);
        loadFatFromSector(bcfFile->fat, file);
    }

    numberOfDirectoryEntriesPerSector = sectorSize(bcfFile) / sizeOfDirectoryEntry;
    bcfFile->directory = CompoundFileDirectory(numberOfDirectoryEntriesPerSector);
    directorySectorToReadFrom = bcfFile->header.firstDirectorySectorLocation;
    while (directorySectorToReadFrom != CompoundFileSector_EndOfChain) {
        seekToSector(bcfFile, file, directorySectorToReadFrom);
        readNextSector(file, bcfFile->directory);
        directorySectorToReadFrom = bcfFile->fat->fatEntries[directorySectorToReadFrom];
    }

    return 1;
}

static FILE* GetFile(bcf_file* bcfFile, FILE* file, char* fileToFind) {
    int filesize, sectorSize, currentSector;
    int sizeToWrite, currentSize, totalSectors, i, j;
    FILE* fileOut = tmpfile();
    bcf_directory_entry* pointer = bcfFile->directory->dirEntries;
    while (pointer) {
        if (strcmp(fileToFind, pointer->directoryEntryName) == 0)
            break;
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
        for (j=0; j<sizeToWrite; j++) {
            char input;
            fread(&input, 1, 1, file);
            fwrite(&input, 1, 1, fileOut);
        }
        currentSize += sizeToWrite;
        currentSector = bcfFile->fat->fatEntries[currentSector];
    }
    return fileOut;
}

static void bcf_file_free(bcf_file* bcfFile)
{
    bcf_file_difat_free(bcfFile->difat);
    bcf_file_fat_free(&bcfFile->fat);
    bcf_directory_free(&bcfFile->directory);
    free(bcfFile);
}

static bcf_file_difat* bcf_difat_create(FILE* file, unsigned int fatSectors, const unsigned int sectorSize)
{
    unsigned int i;
    bcf_file_difat* difat = 0;
    unsigned int sectorRef;

    difat = (bcf_file_difat*)malloc(sizeof(bcf_file_difat));
    if (!difat) {
        printf("ERROR: compound-file-difat.c bcf_difat_create(), cannot allocate memory for difat\n");
        return NULL;
    }

    difat->sectorSize = sectorSize;
    if (fatSectors > NumberOfDifatEntriesInHeader) {
        fatSectors = NumberOfDifatEntriesInHeader;
    }

    for (i = 0; i < fatSectors; ++i) {
        sectorRef = fread_uint32(file);
        difat->fatSectorEntries[i] = sectorRef;
    }
    difat->fatSectorCount = fatSectors;
    for (i = fatSectors; i < NumberOfDifatEntriesInHeader; ++i) {
        sectorRef = fread_uint32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf("ERROR: compound-file-difat.c bcf_difat_create(), Unexpected sector value %x at DIFAT[%d]\n", sectorRef, i);
        }
    }
    return difat;
}

unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat) {
    return (fat->sectorSize - sizeOfChainingEntryAtEndOfDifatSector) / sizeOfDifatEntry;
}

unsigned int readFullSector(FILE* file, bcf_file_difat* bcfFile, 
                            unsigned int* numberOfDifatEntriesStillToRead) {
    unsigned int i;
    unsigned int sectorRef;
    unsigned int nextDifatSectorInChain;
    unsigned int entriesToReadInThisSector = 0;
    if (*numberOfDifatEntriesStillToRead > numberOfEntriesInDifatSector(bcfFile)) {
        entriesToReadInThisSector = numberOfEntriesInDifatSector(bcfFile);
        *numberOfDifatEntriesStillToRead -= entriesToReadInThisSector;
    } else {
        entriesToReadInThisSector = *numberOfDifatEntriesStillToRead;
        *numberOfDifatEntriesStillToRead = 0;
    }

    for (i = 0; i < entriesToReadInThisSector; ++i) {
        sectorRef = fread_uint32(file);
        bcfFile->fatSectorEntries[bcfFile->fatSectorCount] = sectorRef;
        bcfFile->fatSectorCount++;
    }
    for (i = entriesToReadInThisSector; i < numberOfEntriesInDifatSector(bcfFile); ++i) {
        sectorRef = fread_uint32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf("ERROR: compound-file-difat.c readFullSector(), ");
            printf("Unexpected sector value %x at DIFAT[%d]]\n", sectorRef, i);
        }
    }
    nextDifatSectorInChain = fread_uint32(file);
    return nextDifatSectorInChain;
}

void bcf_file_difat_free(bcf_file_difat* difat) {
    free(difat);
    difat = 0;
}

static void parseDirectoryEntryName(FILE* file, bcf_directory_entry* dir) {
    int i;
    for (i = 0; i < 32; ++i) {
        unsigned short unicodechar;
        fread_int(file, &unicodechar, EMB_INT16_LITTLE);
        if (unicodechar != 0x0000) {
            dir->directoryEntryName[i] = (char)unicodechar;
        }
    }
}

bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries) {
    bcf_directory* dir = (bcf_directory*)malloc(sizeof(bcf_directory));
    if (!dir) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectory(), cannot allocate memory for dir\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    dir->maxNumberOfDirectoryEntries = maxNumberOfDirectoryEntries;
    dir->dirEntries = 0;
    return dir;
}

EmbTime parseTime(FILE* file)
{
    EmbTime returnVal;
    unsigned int ft_low, ft_high;
    /*embTime_time(&returnVal); TODO: use embTime_time() rather than time(). */
    ft_low = fread_int32(file);
    ft_high = fread_int32(file);
    /* TODO: translate to actual date time */
    returnVal.day = 1;
    returnVal.hour = 2;
    returnVal.minute = 3;
    returnVal.month = 4;
    returnVal.second = 5;
    returnVal.year = 6;
    return returnVal;
}

static bcf_directory_entry* CompoundFileDirectoryEntry(FILE* file)
{
    const int guidSize = 16;
    bcf_directory_entry* dir = malloc(sizeof(bcf_directory_entry));
    if (dir == NULL) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectoryEntry(), cannot allocate memory for dir\n");
        return 0;
    }
    memset(dir->directoryEntryName, 0, 32);
    parseDirectoryEntryName(file, dir);
    dir->next = 0;
    dir->directoryEntryNameLength = fread_uint16(file);
    dir->objectType = (unsigned char)fgetc(file);
    if ((dir->objectType != ObjectTypeStorage) && (dir->objectType != ObjectTypeStream) && (dir->objectType != ObjectTypeRootEntry)) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectoryEntry()");
        printf(", unexpected object type: %d\n", dir->objectType);
        return 0;
    }
    dir->colorFlag = (unsigned char)fgetc(file);
    fread_int(file, &(dir->leftSiblingId), EMB_INT32_LITTLE);
    fread_int(file, &(dir->rightSiblingId), EMB_INT32_LITTLE);
    fread_int(file, &(dir->childId), EMB_INT32_LITTLE);
    fread(dir->CLSID, 1, guidSize, file);
    fread_int(file, &(dir->stateBits), EMB_INT32_LITTLE);
    dir->creationTime = parseTime(file);
    dir->modifiedTime = parseTime(file);
    fread_int(file, &(dir->startingSectorLocation), EMB_INT32_LITTLE);
    dir->streamSize = fread_uint32(file); /* This should really be __int64 or long long, but for our uses we should never run into an issue */
    dir->streamSizeHigh = fread_uint32(file); /* top portion of int64 */
    return dir;
}

static void readNextSector(FILE* file, bcf_directory* dir) {
    unsigned int i;
    for (i = 0; i < dir->maxNumberOfDirectoryEntries; ++i) {
        bcf_directory_entry* dirEntry = CompoundFileDirectoryEntry(file);
        bcf_directory_entry* pointer = dir->dirEntries;
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

static void bcf_directory_free(bcf_directory** dir) {
    bcf_directory *dirptr;
    bcf_directory_entry* pointer;
    if (dir == NULL){
        return;
    }
    dirptr = *dir;
    pointer = dirptr->dirEntries;
    while (pointer) {
        bcf_directory_entry* entryToFree;
        entryToFree = pointer;
        pointer = pointer->next;
        free(entryToFree);
    }
    if (*dir) {
        free(*dir);
        *dir = NULL;
    }
}

static bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize) {
    bcf_file_fat* fat = (bcf_file_fat*)malloc(sizeof(bcf_file_fat));
    if (!fat) {
        printf("ERROR: compound-file-fat.c bcfFileFat_create(), ");
        printf("cannot allocate memory for fat\n");
        return NULL;
    }
    fat->numberOfEntriesInFatSector = sectorSize / sizeOfFatEntry;
    fat->fatEntryCount = 0;
    return fat;
}

static void loadFatFromSector(bcf_file_fat* fat, FILE* file) {
    unsigned int i;
    unsigned int currentNumberOfFatEntries = fat->fatEntryCount;
    unsigned int newSize = currentNumberOfFatEntries + fat->numberOfEntriesInFatSector;
    for (i = currentNumberOfFatEntries; i < newSize; ++i) {
        unsigned int fatEntry = fread_uint32(file);
        fat->fatEntries[i] = fatEntry;
    }
    fat->fatEntryCount = newSize;
}

static void bcf_file_fat_free(bcf_file_fat** fat) {
    free(*fat);
    *fat = NULL;
}

static bcf_file_header bcfFileHeader_read(FILE* file) {
    bcf_file_header header;
    fread(header.signature, 1, 8, file);
    fread(header.CLSID, 1, 16, file);
    header.minorVersion = fread_uint16(file);
    header.majorVersion = fread_uint16(file);
    header.byteOrder = fread_uint16(file);
    header.sectorShift = fread_uint16(file);
    header.miniSectorShift = fread_uint16(file);
    header.reserved1 = fread_uint16(file);
    header.reserved2 = (unsigned int)fread_uint32(file);
    header.numberOfDirectorySectors = (unsigned int)fread_uint32(file);
    header.numberOfFATSectors = (unsigned int)fread_uint32(file);
    header.firstDirectorySectorLocation = (unsigned int)fread_uint32(file);
    header.transactionSignatureNumber = (unsigned int)fread_uint32(file);
    header.miniStreamCutoffSize = (unsigned int)fread_uint32(file);
    header.firstMiniFATSectorLocation = (unsigned int)fread_uint32(file);
    header.numberOfMiniFatSectors = (unsigned int)fread_uint32(file);
    header.firstDifatSectorLocation = (unsigned int)fread_uint32(file);
    header.numberOfDifatSectors = (unsigned int)fread_uint32(file);
    return header;
}

static int bcfFileHeader_isValid(bcf_file_header header)
{
    if (memcmp(header.signature, "\xd0\xcf\x11\xe0\xa1\xb1\x1a\xe1", 8) != 0) {
        printf("bad header signature\n");
        return 0;
    }
    return 1;
}

/**************************************************/
/* EmbFormatList                                  */
/**************************************************/
int embFormat_getExtension(const char *fileName, char *ending) {
    int i;
    const char *offset;

    if (!fileName) {
        printf("ERROR: emb-format.c embFormat_getExtension(), fileName argument is null\n");
        return 0;
    }

    if (strlen(fileName) == 0) {
        return 0;
    }
    
    offset = strrchr(fileName, '.');
    if (offset==0) {
        return 0;
    }

    i = 0;
    while (offset[i] != '\0') {
        ending[i] = (char)tolower(offset[i]);
        ++i;
    }
    ending[i] = 0; /* terminate the string */
    return 1;
}


/*! Returns a pointer to an EmbPattern. It is created on the heap.
 * The caller is responsible for freeing the allocated memory with
 * embPattern_free(). */
EmbPattern* embPattern_create(void) {
    EmbPattern* p = 0;
    p = (EmbPattern*)malloc(sizeof(EmbPattern));
    if (!p) { 
        printf("ERROR: emb-pattern.c embPattern_create(), ");
        printf("unable to allocate memory for p\n");
        return 0;
    }
    p->settings = embSettings_init();
    p->currentColorIndex = 0;
    p->stitchList = embArray_create(EMB_STITCH);
    p->threads = embArray_create(EMB_THREAD);
    p->hoop.height = 0.0;
    p->hoop.width = 0.0;
    p->arcs = 0;
    p->circles = 0;
    p->ellipses = 0;
    p->lines = 0;
    p->paths = 0;
    p->points = 0;
    p->polygons = 0;
    p->polylines = 0;
    p->rects = 0;
    p->splines = 0;
    p->lastX = 0.0;
    p->lastY = 0.0;
    return p;
}

void embPattern_hideStitchesOverLength(EmbPattern* p, int length) {
    double prevX = 0;
    double prevY = 0;
    int i;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_hideStitchesOverLength(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->stitchList->count; i++) {
        if ((fabs(p->stitchList->stitch[i].x - prevX) > length)
         || (fabs(p->stitchList->stitch[i].y - prevY) > length)) {
            p->stitchList->stitch[i].flags |= TRIM;
            p->stitchList->stitch[i].flags &= ~NORMAL;
        }
        prevX = p->stitchList->stitch[i].x;
        prevY = p->stitchList->stitch[i].y;
    }
}

int embPattern_addThread(EmbPattern* p, EmbThread thread) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addThread(), ");
        printf("p argument is null\n");
        return 0;
    }
    if (!p->threads) {
        p->threads = embArray_create(EMB_THREAD);
    }
    embArray_addThread(p->threads, thread);
    return 1;
}

void embPattern_fixColorCount(EmbPattern* p) {
    /* fix color count to be max of color index. */
    int maxColorIndex = 0, i;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_fixColorCount(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->stitchList->count; i++) {
/*        printf("%d %d\n", list->stitch.color, maxColorIndex);*/
        maxColorIndex = embMaxInt(maxColorIndex, p->stitchList->stitch[i].color);
    }
    if (p->threads->count == 0 || maxColorIndex == 0) {
        EmbThread t;
        t.color = black;
        strcpy(t.description, "Black");
        strcpy(t.catalogNumber, "000");
        embPattern_addThread(p, t);
    }
    else {
        if (maxColorIndex > 0) {
            while (p->threads->count <= maxColorIndex) {
/*        printf("%d %d\n", p->threads->count, maxColorIndex);*/
                embPattern_addThread(p, embThread_getRandom());
            }
        }
    }
    /*
    while (p->threadLists->count > (maxColorIndex + 1)) {
        TODO: erase last color    p->threadList.pop_back();
    }
    */
}

/*! Copies all of the EmbStitchList data to 
    EmbPolylineObjectList data for pattern (\a p). */
void embPattern_copyStitchListToPolylines(EmbPattern* p) {
    int breakAtFlags, i;
    EmbPointObject point;
    EmbColor color;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_copyStitchListToPolylines(), ");
        printf("p argument is null\n");
        return;
    }

#ifdef EMB_DEBUG_JUMP
    breakAtFlags = (STOP | TRIM);
#else /* EMB_DEBUG_JUMP */
    breakAtFlags = (STOP | JUMP | TRIM);
#endif /* EMB_DEBUG_JUMP */

    for (i = 0; i < p->stitchList->count; i++) {
        EmbArray *pointList = 0;
        for (; i < p->stitchList->count; i++) {
            EmbStitch st = p->stitchList->stitch[i];
            if (st.flags & breakAtFlags) {
                break;
            }
            if (!(st.flags & JUMP)) {
                if (!pointList) {
                    pointList = embArray_create(EMB_POINT);
                    color = p->threads->thread[st.color].color;
                }
                point.point.x = st.x;
                point.point.y = st.y;
                embArray_addPoint(pointList, &point);
            }
        }

        /* NOTE: Ensure empty polylines are not created. This is critical. */
        if (pointList) {
            EmbPolylineObject* currentPolyline = 
                (EmbPolylineObject*)malloc(sizeof(EmbPolylineObject));
            if (!currentPolyline) {
                printf("ERROR: emb-pattern.c embPattern_copyStitchListToPolylines(), cannot allocate memory for currentPolyline\n");
                return;
            }
            currentPolyline->pointList = pointList;
            currentPolyline->color = color;
            /* TODO: Determine what the correct value should be */
            currentPolyline->lineType = 1;

            if (!p->polylines) {
                p->polylines = embArray_create(EMB_POLYLINE);
            }
            embArray_addPolyline(p->polylines, currentPolyline);
        }
    }
}

/*! Copies all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
void embPattern_copyPolylinesToStitchList(EmbPattern* p) {
    int firstObject = 1, i, j;
    /*int currentColor = polyList->polylineObj->color TODO: polyline color */

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), ");
        printf("p argument is null\n");
        return;
    }
    if (!p->polylines) {
        printf("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), p argument is null\n");
        return;
    }
    for (i = 0; i < p->polylines->count; i++) {
        EmbPolylineObject* currentPoly = 0;
        EmbArray* currentPointList = 0;
        EmbThread thread;

        currentPoly = p->polylines->polyline[i];
        if (!currentPoly) { 
            printf("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), currentPoly is null\n");
            return;
        }
        currentPointList = currentPoly->pointList;
        if (!currentPointList) {
            printf("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), currentPointList is null\n");
            return;
        }

        strcpy(thread.catalogNumber, "");
        thread.color = currentPoly->color;
        strcpy(thread.description, "");
        embPattern_addThread(p, thread);

        if (!firstObject) {
            embPattern_addStitchAbs(p, currentPointList->point[0].point.x, currentPointList->point[0].point.y, TRIM, 1);
            embPattern_addStitchRel(p, 0.0, 0.0, STOP, 1);
        }

        embPattern_addStitchAbs(p, currentPointList->point[0].point.x, currentPointList->point[0].point.y, JUMP, 1);
        for (j = 1; j < currentPointList->count; j++) { 
            embPattern_addStitchAbs(p, currentPointList->point[j].point.x, currentPointList->point[j].point.y, NORMAL, 1);
        }
        firstObject = 0;
    }
    embPattern_addStitchRel(p, 0.0, 0.0, END, 1);
}

/*! Moves all of the EmbStitchList data to EmbPolylineObjectList data for pattern (\a p). */
void embPattern_moveStitchListToPolylines(EmbPattern* p) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_moveStitchListToPolylines(), p argument is null\n");
        return;
    }
    embPattern_copyStitchListToPolylines(p);
    /* Free the stitchList and threadList since their data has now been transferred to polylines */
    p->stitchList->count = 0;
    p->threads->count = 0;
}

/*! Moves all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
void embPattern_movePolylinesToStitchList(EmbPattern* p) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_movePolylinesToStitchList(), p argument is null\n");
        return;
    }
    embPattern_copyPolylinesToStitchList(p);
    embArray_free(p->polylines);
}

/*! Adds a stitch to the pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
void embPattern_addStitchAbs(EmbPattern* p, double x, double y, 
                            int flags, int isAutoColorIndex) {
    EmbStitch s;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addStitchAbs(), ");
        printf("p argument is null\n");
        return;
    }

    if (flags & END) {
        if (p->stitchList->count == 0) {
            return;
        }
        /* Prevent unnecessary multiple END stitches */
        if (p->stitchList->stitch[p->stitchList->count - 1].flags & END) {
            printf("ERROR: emb-pattern.c embPattern_addStitchAbs(), found multiple END stitches\n");
            return;
        }
        embPattern_fixColorCount(p);
        /* HideStitchesOverLength(127); TODO: fix or remove this */
    }

    if (flags & STOP) {
        if (p->stitchList->count == 0) {
            return;
        }
        if (isAutoColorIndex) {
            p->currentColorIndex++;
        }
    }

    /* NOTE: If the stitchList is empty, we will create it before adding 
        stitches to it. The first coordinate will be the HOME position. */
    if (p->stitchList->count == 0) {
        /* NOTE: Always HOME the machine before starting any stitching */
        EmbVector home = embSettings_home(&(p->settings));
        EmbStitch h;
        h.x = home.x;
        h.y = home.y;
        h.flags = JUMP;
        h.color = p->currentColorIndex;
        embArray_addStitch(p->stitchList, h);
    }
    s.x = x;
    s.y = y;
    s.flags = flags;
    s.color = p->currentColorIndex;
    embArray_addStitch(p->stitchList, s);
    p->lastX = s.x;
    p->lastY = s.y;
}

/*! Adds a stitch to the pattern (\a p) at the relative position (\a dx,\a dy) 
    to the previous stitch. Positive y is up. Units are in millimeters. */
void embPattern_addStitchRel(EmbPattern* p, double dx, double dy, 
                            int flags, int isAutoColorIndex) {
    double x, y;
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addStitchRel(), p argument is null\n");
        return;
    }
    if (p->stitchList->count > 0) {
        x = p->lastX + dx;
        y = p->lastY + dy;
    } else {
        /* NOTE: The stitchList is empty, so add it to the HOME position.
         * The embStitchList_create function will ensure the first coordinate is at the HOME position. */
        EmbVector home = embSettings_home(&(p->settings));
        x = home.x + dx;
        y = home.y + dy;
    }
    embPattern_addStitchAbs(p, x, y, flags, isAutoColorIndex);
}

void embPattern_changeColor(EmbPattern* p, int index)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_changeColor(), p argument is null\n");
        return;
    }
    p->currentColorIndex = index;
}

/* Very simple scaling of the x and y axis for every point.
* Doesn't insert or delete stitches to preserve density. */
void embPattern_scale(EmbPattern* p, double scale) {
    int i;
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_scale(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitchList->count; i++) {
        p->stitchList->stitch[i].x *= scale;
        p->stitchList->stitch[i].y *= scale;
    }
}

/*! Returns an EmbRect that encapsulates all stitches and objects in the pattern (\a p). */
EmbRect embPattern_calcBoundingBox(EmbPattern* p) {
    EmbRect r;
    EmbStitch pt;
    EmbArc arc;
    EmbCircle circle;
    EmbEllipse ellipse;
    EmbLine line;
    EmbVector point;
    EmbArray *polygon;
    EmbArray *polyline;
    int i, j;

    r.left = 0;
    r.right = 0;
    r.top = 0;
    r.bottom = 0;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_calcBoundingBox(), ");
        printf("p argument is null\n");
        return r;
    }

    /* Calculate the bounding rectangle.  It's needed for smart repainting. */
    /* TODO: Come back and optimize this mess so that after going thru all objects
            and stitches, if the rectangle isn't reasonable, then return a default rect */
    if (p->stitchList->count == 0 &&
        !(p->arcs || p->circles || p->ellipses || p->lines || p->points ||
        p->polygons || p->polylines || p->rects || p->splines)) {
        r.top = 0.0;
        r.left = 0.0;
        r.bottom = 1.0;
        r.right = 1.0;
        return r;
    }
    r.left = 99999.0;
    r.top =  99999.0;
    r.right = -99999.0;
    r.bottom = -99999.0;

    for (i = 0; i < p->stitchList->count; i++) {
        /* If the point lies outside of the accumulated bounding
        * rectangle, then inflate the bounding rect to include it. */
        pt = p->stitchList->stitch[i];
        if (!(pt.flags & TRIM)) {
            r.left = embMinDouble(r.left, pt.x);
            r.top = embMinDouble(r.top, pt.y);
            r.right = embMaxDouble(r.right, pt.x);
            r.bottom = embMaxDouble(r.bottom, pt.y);
        }
    }

    if (p->arcs) {
        /* TODO: embPattern_calcBoundingBox for arcs, 
            for now just checks the start point */
        for (i = 0; i < p->arcs->count; i++) {
            arc = p->arcs->arc[i].arc;
            r.left = embMinDouble(r.left, arc.start.x);
            r.top = embMinDouble(r.top, arc.start.y);
            r.right = embMaxDouble(r.right, arc.start.x);
            r.bottom = embMaxDouble(r.bottom, arc.start.y);
        }
    }

    if (p->circles) {
        for (i = 0; i < p->circles->count; i++) {
            circle = p->circles->circle[i].circle;
            r.left = embMinDouble(r.left, circle.center.x - circle.radius);
            r.top = embMinDouble(r.top, circle.center.y - circle.radius);
            r.right = embMaxDouble(r.right, circle.center.x + circle.radius);
            r.bottom = embMaxDouble(r.bottom, circle.center.y + circle.radius);
        }
    }

    if (p->ellipses) {
        for (i = 0; i < p->ellipses->count; i++) {
            /* TODO: account for rotation */
            ellipse = p->ellipses->ellipse[i].ellipse;
            r.left = embMinDouble(r.left, ellipse.centerX - ellipse.radiusX);
            r.top = embMinDouble(r.top, ellipse.centerY - ellipse.radiusY);
            r.right = embMaxDouble(r.right, ellipse.centerX + ellipse.radiusX);
            r.bottom = embMaxDouble(r.bottom, ellipse.centerY + ellipse.radiusY);
        }
    }

    if (p->lines) {
        for (i = 0; i < p->lines->count; i++) {
            line = p->lines->line[i].line;
            r.left = embMinDouble(r.left, line.start.x);
            r.left = embMinDouble(r.left, line.end.x);
            r.top = embMinDouble(r.top, line.start.y);
            r.top = embMinDouble(r.top, line.end.y);
            r.right = embMaxDouble(r.right, line.start.x);
            r.right = embMaxDouble(r.right, line.end.x);
            r.bottom = embMaxDouble(r.bottom, line.start.y);
            r.bottom = embMaxDouble(r.bottom, line.end.y);
        }
    }

    if (p->points) {
        for (i = 0; i < p->points->count; i++) {
            point = p->points->point[i].point;
            r.left = embMinDouble(r.left, point.x);
            r.top = embMinDouble(r.top, point.y);
            r.right = embMaxDouble(r.right, point.x);
            r.bottom = embMaxDouble(r.bottom, point.y);
        }
    }

    if (p->polygons) {
        for (i = 0; i < p->polygons->count; i++) {
            polygon = p->polygons->polygon[i]->pointList;
            for (j=0; j < polygon->count; j++) {
                /* TODO: embPattern_calcBoundingBox for polygons */
            }
        }
    }

    if (p->polylines) {
        for (i = 0; i < p->polylines->count; i++) {
            polyline = p->polylines->polyline[i]->pointList;
            for (j=0; j < polyline->count; j++) {
                /* TODO: embPattern_calcBoundingBox for polylines */
            }
        }
    }

    if (p->rects) {
        EmbRect rect;
        for (i = 0; i < p->rects->count; i++) {
            rect = p->rects->rect[i].rect;
            r.left = embMinDouble(r.left, rect.left);
            r.top = embMinDouble(r.top, rect.top);
            r.right = embMaxDouble(r.right, rect.right);
            r.bottom = embMaxDouble(r.bottom, rect.bottom);
        }
    }

    if (p->splines) {
        for (i = 0; i < p->splines->count; i++) {
            /* EmbBezier bezier;
            bezier = p->splines->spline[i].bezier; */
            /* TODO: embPattern_calcBoundingBox for splines */
        }
    }
    return r;
}

/*! Flips the entire pattern (\a p) horizontally about the y-axis. */
void embPattern_flipHorizontal(EmbPattern* p) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_flipHorizontal(), ");
        printf("p argument is null\n");
        return;
    }
    embPattern_flip(p, 1, 0);
}

/*! Flips the entire pattern (\a p) vertically about the x-axis. */
void embPattern_flipVertical(EmbPattern* p) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_flipVertical(), ");
        printf("p argument is null\n");
        return;
    }
    embPattern_flip(p, 0, 1);
}

/*! Flips the entire pattern (\a p) horizontally about the x-axis if (\a horz) is true.
 *  Flips the entire pattern (\a p) vertically about the y-axis if (\a vert) is true. */
void embPattern_flip(EmbPattern* p, int horz, int vert) {
    int i, j;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_flip(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitchList->count; i++) {
        if (horz) {
            p->stitchList->stitch[i].x *= -1.0;
        }
        if (vert) {
            p->stitchList->stitch[i].y *= -1.0;
        }
    }

    if (p->arcs) {
        for (i = 0; i < p->arcs->count; i++) {
            if (horz) {
                p->arcs->arc[i].arc.start.x *= -1.0;
                p->arcs->arc[i].arc.mid.x *= -1.0;
                p->arcs->arc[i].arc.end.x *= -1.0;
            }
            if (vert) {
                p->arcs->arc[i].arc.start.y *= -1.0;
                p->arcs->arc[i].arc.mid.y *= -1.0;
                p->arcs->arc[i].arc.end.y *= -1.0;
            }
        }
    }

    if (p->circles) {
        for (i = 0; i < p->circles->count; i++) {
            if (horz) { p->circles->circle[i].circle.center.x *= -1.0; }
            if (vert) { p->circles->circle[i].circle.center.y *= -1.0; }
        }
    }

    if (p->ellipses) {
        for (i = 0; i < p->ellipses->count; i++) {
            if (horz) { p->ellipses->ellipse[i].ellipse.centerX *= -1.0; }
            if (vert) { p->ellipses->ellipse[i].ellipse.centerY *= -1.0; }
        }
    }

    if (p->lines) {
        for (i = 0; i < p->lines->count; i++) {
            if (horz) {
                p->lines->line[i].line.start.x *= -1.0;
                p->lines->line[i].line.end.x *= -1.0;
            }
            if (vert) {
                p->lines->line[i].line.start.y *= -1.0;
                p->lines->line[i].line.end.y *= -1.0;
            }
        }
    }

    if (p->paths) {
        for (i = 0; i < p->paths->count; i++) {
            EmbArray *path = p->paths->path[i]->pointList;
            for (j=0; j < path->count; j++) {
                if (horz) {
                    path->point[j].point.x *= -1.0;
                }
                if (vert) {
                    path->point[j].point.y *= -1.0;
                }
            }
        }
    }

    if (p->points) {
        for (i = 0; i < p->points->count; i++) {
            if (horz) {
                p->points->point[i].point.x *= -1.0;
            }
            if (vert) {
                p->points->point[i].point.y *= -1.0;
            }
        }
    }

    if (p->polygons) {
        for (i = 0; i < p->polygons->count; i++) {
            EmbArray *polygon;
            polygon = p->polygons->polygon[i]->pointList;
            for (j=0; j < polygon->count; j++) {
                if (horz) { polygon->point[j].point.x *= -1.0; }
                if (vert) { polygon->point[j].point.y *= -1.0; }
            }
        }
    }

    if (p->polylines) {
        for (i = 0; i < p->polylines->count; i++) {
            EmbArray *polyline;
            polyline = p->polylines->polygon[i]->pointList;
            for (j=0; j < polyline->count; j++) {
                if (horz) { polyline->point[j].point.x *= -1.0; }
                if (vert) { polyline->point[j].point.y *= -1.0; }
            }
        }
    }

    if (p->rects) {
        for (i = 0; i < p->rects->count; i++) {
            if (horz) {
                p->rects->rect[i].rect.left *= -1.0;
                p->rects->rect[i].rect.right *= -1.0;
            }
            if (vert) {
                p->rects->rect[i].rect.top *= -1.0;
                p->rects->rect[i].rect.bottom *= -1.0;
            }
        }
    }

    if (p->splines) {
        for (i = 0; i < p->splines->count; i++) {
            /* TODO: embPattern_flip for splines */
        }
    }
}

void embPattern_combineJumpStitches(EmbPattern* p) {
    int jumpCount = 0, i;
    EmbArray *newList;
    EmbStitch j;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_combineJumpStitches(), ");
        printf("p argument is null\n");
        return;
    }
    newList = embArray_create(EMB_STITCH);
    for (i = 0; i < p->stitchList->count; i++) {
        EmbStitch st = p->stitchList->stitch[i];
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
                embArray_addStitch(newList, j);
            }
            embArray_addStitch(newList, st);
        }
    }
    embArray_free(p->stitchList);
    p->stitchList = newList;
}

/*TODO: The params determine the max XY movement rather than the length. 
    They need renamed or clarified further. */
void embPattern_correctForMaxStitchLength(EmbPattern* p, 
                        double maxStitchLength, double maxJumpLength) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_correctForMaxStitchLength(), ");
        printf("p argument is null\n");
        return;
    }
    if (p->stitchList->count > 1) {
        int i, j, splits;
        double maxXY, maxLen, addX, addY;
        EmbArray *newList = embArray_create(EMB_STITCH);
        for (i=1; i < p->stitchList->count; i++) {
            EmbStitch st = p->stitchList->stitch[i];
            double xx = st.x;
            double yy = st.y;
            double dx = p->stitchList->stitch[i-1].x - xx;
            double dy = p->stitchList->stitch[i-1].y - yy;
            if ((fabs(dx) > maxStitchLength) || (fabs(dy) > maxStitchLength)) {
                maxXY = embMaxDouble(fabs(dx), fabs(dy));
                if (st.flags & (JUMP | TRIM)) {
                    maxLen = maxJumpLength;
                } else {
                    maxLen = maxStitchLength;
                }
                splits = (int)ceil((double)maxXY / maxLen);

                if (splits > 1) {
                    addX = (double)dx / splits;
                    addY = (double)dy / splits;

                    for (j = 1; j < splits; j++) {
                        EmbStitch s;
                        s = st;
                        s.x = xx + addX * j;
                        s.y = yy + addY * j;
                        embArray_addStitch(newList, s);
                    }
                }
            }
            embArray_addStitch(newList, st);
        }
        embArray_free(p->stitchList);
        p->stitchList = newList;
    }
    embPattern_end(p);
}

void embPattern_center(EmbPattern* p) {
    /* TODO: review this. currently not used in anywhere. 
        Also needs to handle various design objects */
    int moveLeft, moveTop, i;
    EmbRect boundingRect;
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_center(), p argument is null\n");
        return;
    }
    boundingRect = embPattern_calcBoundingBox(p);

    moveLeft = (int)(boundingRect.left - (embRect_width(boundingRect) / 2.0));
    moveTop = (int)(boundingRect.top - (embRect_height(boundingRect) / 2.0));

    for (i = 0; i < p->stitchList->count; i++) {
        p->stitchList->stitch[i].x -= moveLeft;
        p->stitchList->stitch[i].y -= moveTop;
    }
}

/*TODO: Description needed. */
void embPattern_loadExternalColorFile(EmbPattern* p, const char* fileName) {
    int hasRead, stub_len, format;
    char extractName[200];

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_loadExternalColorFile(), p argument is null\n");
        return;
    }
    if (!fileName) {
        printf("ERROR: emb-pattern.c embPattern_loadExternalColorFile(), fileName argument is null\n");
        return;
    }

    strcpy(extractName, fileName);
    format = emb_identify_format(fileName);
    stub_len = strlen(fileName) - strlen(formatTable[format].extension);
    extractName[stub_len] = 0;
    strcat(extractName, ".edr");
    hasRead = embPattern_read(p, extractName, EMB_FORMAT_EDR);
    if (!hasRead) {
        extractName[stub_len] = 0;
        strcat(extractName,".rgb");
        hasRead = embPattern_read(p, extractName, EMB_FORMAT_RGB);
    }
    if (!hasRead) {
        extractName[stub_len] = 0;
        strcat(extractName,".col");
        hasRead = embPattern_read(p, extractName, EMB_FORMAT_COL);
    }
    if (!hasRead) {
        extractName[stub_len] = 0;
        strcat(extractName,".inf");
        hasRead = embPattern_read(p, extractName, EMB_FORMAT_INF);
    }
}

/*! Frees all memory allocated in the pattern (\a p). */
void embPattern_free(EmbPattern* p) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_free(), p argument is null\n");
        return;
    }
    embArray_free(p->stitchList);
    embArray_free(p->threads);
    embArray_free(p->arcs);
    embArray_free(p->circles);
    embArray_free(p->ellipses);
    embArray_free(p->lines);
    embArray_free(p->paths);
    embArray_free(p->points);
    embArray_free(p->polygons);
    embArray_free(p->polylines);
    embArray_free(p->rects);
    embArray_free(p->splines);

    free(p);
}

/*! Adds a circle object to pattern (\a p) with its center at the absolute
 * position (\a cx,\a cy) with a radius of (\a r). Positive y is up.
 * Units are in millimeters. */
void embPattern_addCircleObjectAbs(EmbPattern* p, double cx, double cy, double r) {
    EmbCircle circle;
    circle.center.x = cx;
    circle.center.y = cy;
    circle.radius = r;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addCircleObjectAbs(), p argument is null\n");
        return;
    }
    if (p->circles == 0) {
         p->circles = embArray_create(EMB_CIRCLE);
    }
    embArray_addCircle(p->circles, circle, 0, black);
}

/*! Adds an ellipse object to pattern (\a p) with its center at the
 * absolute position (\a cx,\a cy) with radii of (\a rx,\a ry). Positive y is up.
 * Units are in millimeters. */
void embPattern_addEllipseObjectAbs(EmbPattern* p, double cx, double cy,
                                    double rx, double ry) {
    EmbEllipse ellipse;
    ellipse.centerX = cx;
    ellipse.centerY = cy;
    ellipse.radiusX = rx;
    ellipse.radiusY = ry;
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addEllipseObjectAbs(), p argument is null\n");
        return;
    }
    if (!p->ellipses) {
        p->ellipses = embArray_create(EMB_ELLIPSE);
    }
    embArray_addEllipse(p->ellipses, ellipse, 0.0, 0, black);
}

/*! Adds a line object to pattern (\a p) starting at the absolute position
 * (\a x1,\a y1) and ending at the absolute position (\a x2,\a y2).
 * Positive y is up. Units are in millimeters.
 */
void embPattern_addLineObjectAbs(EmbPattern* p, double x1, double y1, double x2, double y2) {
    EmbLineObject lineObj;
    lineObj.line = embLine_make(x1, y1, x2, y2);
    lineObj.lineType = 0;
    lineObj.color = embColor_make(0, 0, 0);

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addLineObjectAbs(), p argument is null\n");
        return;
    }
    if (p->circles == 0) {
         p->lines = embArray_create(EMB_LINE);
    }
    embArray_addLine(p->lines, lineObj);
}

void embPattern_addPathObjectAbs(EmbPattern* p, EmbPathObject* obj)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj) {
        printf("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), obj argument is null\n");
        return;
    }
    if (!obj->pointList) {
        printf("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), obj->pointList is empty\n");
        return;
    }
    if (!p->paths) {
        p->paths = embArray_create(EMB_PATH);
    }
    embArray_addPath(p->paths, obj);
}

/*! Adds a point object to pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
void embPattern_addPointObjectAbs(EmbPattern* p, double x, double y) {
    EmbPointObject pointObj;
    pointObj.point.x = x;
    pointObj.point.y = y;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addPointObjectAbs(), p argument is null\n");
        return;
    }
    if (!p->points) {
        p->points = embArray_create(EMB_POINT);
    }
    embArray_addPoint(p->points, &pointObj);
}

void embPattern_addPolygonObjectAbs(EmbPattern* p, EmbPolygonObject* obj) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj) {
        printf("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), obj argument is null\n");
        return;
    }
    if (!obj->pointList) {
        printf("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), obj->pointList is empty\n");
        return;
    }

    if (!p->polygons) {
        p->polygons = embArray_create(EMB_POLYGON);
    }
    embArray_addPolygon(p->polygons, obj);
}

void embPattern_addPolylineObjectAbs(EmbPattern* p, EmbPolylineObject* obj) {
    if (!p) { printf("ERROR: emb-pattern.c embPattern_addPolylineObjectAbs(), p argument is null\n"); return; }
    if (!obj) { printf("ERROR: emb-pattern.c embPattern_addPolylineObjectAbs(), obj argument is null\n"); return; }
    if (!obj->pointList) {
        printf("ERROR: emb-pattern.c embPattern_addPolylineObjectAbs(), obj->pointList is empty\n"); return;
    }
    if (!p->polylines) {
        p->polylines = embArray_create(EMB_POLYLINE);
    }
    embArray_addPolyline(p->polylines, obj);
}

/**
 * Adds a rectangle object to pattern (\a p) at the absolute position
 * (\a x,\a y) with a width of (\a w) and a height of (\a h).
 * Positive y is up. Units are in millimeters.
 */
void embPattern_addRectObjectAbs(EmbPattern* p, double x, double y, double w, double h) {
    EmbRect rect;
    rect.left = x;
    rect.top = y;
    rect.right = x+w;
    rect.bottom = y+h;
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addRectObjectAbs(), p argument is null\n");
        return;
    }
    if (!p->rects) {
        p->rects = embArray_create(EMB_RECT);
    }
    embArray_addRect(p->rects, rect, 0, black);
}

void embPattern_end(EmbPattern *p) {
    if (p->stitchList->count == 0) {
        return;
    }
    /* Check for an END stitch and add one if it is not present */
    if (p->stitchList->stitch[p->stitchList->count-1].flags != END) {
        embPattern_addStitchRel(p, 0, 0, END, 1);
    }
}

int emb_identify_format(const char *fileName) {
    int i;
    char ending[5];
    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }
    for (i = 0; i < numberOfFormats; i++) {
        if (!strcmp(ending, formatTable[i].extension)) {
            return i;
        }
    }
    return -1;
}

double embRect_x(EmbRect rect) {
    return rect.left;
}

double embRect_y(EmbRect rect) {
    return rect.top;
}

double embRect_width(EmbRect rect) {
    return rect.right - rect.left;
}

double embRect_height(EmbRect rect) {
    return rect.bottom - rect.top;
}

/* Sets the left edge of the rect to x. The right edge is not modified. */
void embRect_setX(EmbRect* rect, double x) {
    rect->left = x;
}

/* Sets the top edge of the rect to y. The bottom edge is not modified. */
void embRect_setY(EmbRect* rect, double y) {
    rect->top = y;
}

/* Sets the width of the rect to w. The right edge is modified. 
    The left edge is not modified. */
void embRect_setWidth(EmbRect* rect, double w) {
    rect->right = rect->left + w;
}

/* Sets the height of the rect to h. The bottom edge is modified. 
    The top edge is not modified. */
void embRect_setHeight(EmbRect* rect, double h) {
    rect->bottom = rect->top + h;
}

void embRect_setCoords(EmbRect* rect, double x1, double y1, double x2, double y2) {
    rect->left = x1;
    rect->top = y1;
    rect->right = x2;
    rect->bottom = y2;
}

void embRect_setRect(EmbRect* rect, double x, double y, double w, double h) {
    rect->left = x;
    rect->top = y;
    rect->right = x + w;
    rect->bottom = y + h;
}

/* Returns an EmbRectObject. It is created on the stack. */
EmbRectObject embRectObject_make(double x, double y, double w, double h) {
    EmbRectObject stackRectObj;
    stackRectObj.rect.left = x;
    stackRectObj.rect.top = y;
    stackRectObj.rect.right = x + w;
    stackRectObj.rect.bottom = y + h;
    stackRectObj.rotation = 0.0;
    stackRectObj.color.r = 0;
    stackRectObj.color.g = 0;
    stackRectObj.color.b = 0;
    stackRectObj.lineType = 0;
    stackRectObj.radius = 0;
    return stackRectObj;
}

void embSatinOutline_generateSatinOutline(EmbArray *lines, double thickness, EmbSatinOutline* result) {
    int i;
    EmbLine line1, line2;
    EmbSatinOutline outline;
    EmbVector out;
    EmbVector v1;
    EmbVector temp;
    EmbLine line;

    double halfThickness = thickness / 2.0;
    int intermediateOutlineCount = 2 * lines->count - 2;
    outline.side1 = embArray_create(EMB_VECTOR);
    if (!outline.side1) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for outline->side1\n");
        return;
    }
    outline.side2 = embArray_create(EMB_VECTOR);
    if (!outline.side2) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for outline->side2\n");
        return;
    }

    for (i = 1; i < lines->count; i++) {
        line.start = lines->vector[i - 1];
        line.end = lines->vector[i];

        embLine_normalVector(line, &v1, 1);

        embVector_multiply(v1, halfThickness, &temp);
        embVector_add(temp, lines->vector[i - 1], &temp);
        embArray_addVector(outline.side1, temp);
        embVector_add(temp, lines->vector[i], &temp);
        embArray_addVector(outline.side1, temp);

        embVector_multiply(v1, -halfThickness, &temp);
        embVector_add(temp, lines->vector[i - 1], &temp);
        embArray_addVector(outline.side2, temp);
        embVector_add(temp, lines->vector[i], &temp);
        embArray_addVector(outline.side2, temp);
    }

    if (!result) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), result argument is null\n");
        return;
    }
    result->side1 = embArray_create(EMB_VECTOR);
    if (!result->side1) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side1\n");
        return;
    }
    result->side2 = embArray_create(EMB_VECTOR);
    if (!result->side2) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side2\n");
        return;
    }

    embArray_addVector(result->side1, outline.side1->vector[0]);
    embArray_addVector(result->side2, outline.side2->vector[0]);

    for (i = 3; i < intermediateOutlineCount; i += 2) {
        line1.start = outline.side1->vector[i - 3];
        line1.end = outline.side1->vector[i - 2];
        line2.start = outline.side1->vector[i - 1];
        line2.end = outline.side1->vector[i];
        out = embLine_intersectionPoint(line1, line2);
        if (emb_error) {
            puts("No intersection point.");
        }
        embArray_addVector(result->side1, out);

        line1.start = outline.side2->vector[i - 3];
        line1.end = outline.side2->vector[i - 2];
        line2.start = outline.side2->vector[i - 1];
        line2.end = outline.side2->vector[i];
        out = embLine_intersectionPoint(line1, line2);
        if (emb_error) {
            puts("No intersection point.");
        }
        embArray_addVector(result->side2, out);
    }

    embArray_addVector(result->side1, outline.side1->vector[2 * lines->count - 3]);
    embArray_addVector(result->side2, outline.side2->vector[2 * lines->count - 3]);
    result->length = lines->count;
}

EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, double density) {
    int i, j;
    EmbVector currTop, currBottom, topDiff, bottomDiff, midDiff;
    EmbVector midLeft, midRight, topStep, bottomStep;
    EmbArray* stitches = 0;
    int numberOfSteps;
    double midLength;

    if (!result) {
        printf("ERROR: emb-satin-line.c embSatinOutline_renderStitches(), result argument is null\n");
        return 0;
    }

    if (result->length > 0) {
        for (j = 0; j < result->length - 1; j++) {
            embVector_subtract(result->side1->vector[j+1], result->side1->vector[j], &topDiff);
            embVector_subtract(result->side2->vector[j+1], result->side2->vector[j], &bottomDiff);

            embVector_average(result->side1->vector[j], result->side2->vector[j], &midLeft);
            embVector_average(result->side1->vector[j+1], result->side2->vector[j+1], &midRight);

            embVector_subtract(midLeft, midRight, &midDiff);
            midLength = embVector_length(midDiff);

            numberOfSteps = (int)(midLength * density / 200);
            embVector_multiply(topDiff, 1.0/numberOfSteps, &topStep);
            embVector_multiply(bottomDiff, 1.0/numberOfSteps, &bottomStep);
            currTop = result->side1->vector[j];
            currBottom = result->side2->vector[j];

            for (i = 0; i < numberOfSteps; i++) {
                if (!stitches) {
                    stitches = embArray_create(EMB_VECTOR);
                }
                embArray_addVector(stitches, currTop);
                embArray_addVector(stitches, currBottom);
                embVector_add(currTop, topStep, &currTop);
                embVector_add(currBottom, bottomStep, &currBottom);
            }
        }
        embArray_addVector(stitches, currTop);
        embArray_addVector(stitches, currBottom);
    }
    return stitches;
}

/*! Initializes and returns an EmbSettings */
EmbSettings embSettings_init(void) {
    EmbSettings settings;
    settings.dstJumpsPerTrim = 6;
    settings.home.x = 0.0;
    settings.home.y = 0.0;
    return settings;
}

/*! Returns the home position stored in (\a settings) as an EmbPoint (\a point). */
EmbVector embSettings_home(EmbSettings* settings) {
    return settings->home;
}

/*! Sets the home position stored in (\a settings) to EmbPoint (\a point). You will rarely ever need to use this. */
void embSettings_setHome(EmbSettings* settings, EmbVector point) {
    settings->home = point;
}

void write_24bit(FILE* file, int x)
{
    unsigned char a[4];
    a[0] = (unsigned char)0;
    a[1] = (unsigned char)(x & 0xFF);
    a[2] = (unsigned char)((x >> 8) & 0xFF);
    a[3] = (unsigned char)((x >> 16) & 0xFF);
    fwrite(a, 1, 4, file);
}

int embColor_distance(EmbColor a, EmbColor b)
{
    int t;
    t = (a.r-b.r)*(a.r-b.r);
    t += (a.g-b.g)*(a.g-b.g);
    t += (a.b-b.b)*(a.b-b.b);
    return t;
}

void embColor_read(FILE *f, EmbColor *c, int toRead)
{
    unsigned char b[4];
    fread(b, 1, toRead, f);
    c->r = b[0];
    c->g = b[1];
    c->b = b[2];
}

void embColor_write(FILE *f, EmbColor c, int toWrite)
{
    unsigned char b[4];
    b[0] = c.r;
    b[1] = c.g;
    b[2] = c.b;
    b[3] = 0;
    fwrite(b, 1, toWrite, f);
}

/**
 * Returns the closest color to the required color based on
 * a list of available threads. The algorithm is a simple least
 * squares search against the list. If the (square of) Euclidean 3-dimensional
 * distance between the points in (red, green, blue) space is smaller
 * then the index is saved and the remaining index is returned to the
 * caller.
 *
 * @param color  The EmbColor color to match.
 * @param colors The EmbThreadList pointer to start the search at.
 * @param mode   Is the argument an array of threads (0) or colors (1)?
 * @return closestIndex The entry in the ThreadList that matches.
 */
int embThread_findNearestColor(EmbColor color, EmbArray* a, int mode) {
    int currentClosestValue = 256*256*3;
    int closestIndex = -1, i;
    for (i = 0; i < a->count; i++) {
        int delta;
        if (mode == 0) { /* thread mode */
            delta = embColor_distance(color, a->thread[i].color);
        } else { /* color array mode */
            delta = embColor_distance(color, a->color[i]);
        }

        if (delta <= currentClosestValue) {
            currentClosestValue = delta;
            closestIndex = i;
        }
    }
    return closestIndex;
}

int embThread_findNearestColor_fromThread(EmbColor color, EmbThread* a, int length) {
    int currentClosestValue = 256*256*3;
    int closestIndex = -1, i;

    for (i = 0; i < length; i++) {
        int delta;
        delta = embColor_distance(color, a[i].color);

        if (delta <= currentClosestValue) {
            currentClosestValue = delta;
            closestIndex = i;
        }
    }
    return closestIndex;
}

/**
 * Returns a random thread color, useful in filling in cases where the
 * actual color of the thread doesn't matter but one needs to be declared
 * to test or render a pattern.
 *
 * @return c The resulting color.
 */
EmbThread embThread_getRandom(void) {
    EmbThread c;
    c.color.r = rand()%256;
    c.color.g = rand()%256;
    c.color.b = rand()%256;
    strcpy(c.description, "random");
    strcpy(c.catalogNumber, "");
    return c;
}

void binaryReadString(FILE* file, char* buffer, int maxLength) {
    int i = 0;
    while(i < maxLength) {
        buffer[i] = (char)fgetc(file);
        if (buffer[i] == '\0') break;
        i++;
    }
}

void binaryReadUnicodeString(FILE* file, char *buffer, const int stringLength) {
    int i = 0;
    for (i = 0; i < stringLength * 2; i++) {
        char input = (char)fgetc(file);
        if (input != 0) {
            buffer[i] = input;
        }
    }
}

void binaryWriteShort(FILE* file, short data) {
    fwrite_int(file, &data, EMB_INT16_LITTLE);
}

void binaryWriteUShort(FILE* file, unsigned short data) {
    fwrite_int(file, &data, EMB_INT16_LITTLE);
}

void binaryWriteUShortBE(FILE* file, unsigned short data) {
    fwrite_int(file, &data, EMB_INT16_BIG);
}

void binaryWriteInt(FILE* file, int data) {
    fwrite_int(file, &data, EMB_INT32_LITTLE);
}

void binaryWriteIntBE(FILE* file, int data) {
    fwrite_int(file, &data, EMB_INT32_BIG);
}

void binaryWriteUInt(FILE* file, unsigned int data) {
    fwrite_int(file, &data, EMB_INT32_LITTLE);
}

void binaryWriteUIntBE(FILE* file, unsigned int data) {
    fwrite_int(file, &data, EMB_INT32_BIG);
}

double embMinDouble(double a, double b) {
    if (a<b) {
        return a;
    }
    return b;
}

double embMaxDouble(double a, double b) {
    if (a>b) {
        return a;
    }
    return b;
}

int embMinInt(int a, int b) {
    if (a<b) {
        return a;
    }
    return b;
}

int embMaxInt(int a, int b)
{
    if (a>b) {
        return a;
    }
    return b;
}

/**
 * Tests for the presence of a string \a s in the supplied
 * \a array.
 *
 * The end of the array is marked by an empty string.
 *
 * @return 0 if not present 1 if present.
 */
int stringInArray(const char *s, const char **array) {
    int i;
    for (i = 0; strlen(array[i]); i++) {
        if (!strcmp(s, array[i])) {
            return 1;
        }
    }
    return 0;
}

int emb_readline(FILE* file, char *line, int maxLength) {
    int i;
    char c;
    for (i = 0; i < maxLength-1; i++) {
        if (!fread(&c, 1, 1, file)) {
            break;
        }
        if (c == '\r') {
            fread(&c, 1, 1, file);
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

/* TODO: trimming function should handle any character, not just whitespace */
static char const WHITESPACE[] = " \t\n\r";

/* TODO: description */
static void get_trim_bounds(char const *s,
                            char const **firstWord,
                            char const **trailingSpace) {
    char const* lastWord = 0;
    *firstWord = lastWord = s + strspn(s, WHITESPACE);
    do {
        *trailingSpace = lastWord + strcspn(lastWord, WHITESPACE);
        lastWord = *trailingSpace + strspn(*trailingSpace, WHITESPACE);
    } while (*lastWord != '\0');
}

/* TODO: description */
char* copy_trim(char const *s) {
    char const *firstWord = 0, *trailingSpace = 0;
    char* result = 0;
    size_t newLength;

    get_trim_bounds(s, &firstWord, &trailingSpace);
    newLength = trailingSpace - firstWord;

    result = (char*)malloc(newLength + 1);
    memcpy(result, firstWord, newLength);
    result[newLength] = '\0';
    return result;
}

/*! Optimizes the number (\a num) for output to a text file and returns it as a string (\a str). */
char* emb_optOut(double num, char* str) {
    char *str_end;
    /* Convert the number to a string */
    sprintf(str, "%.10f", num);
    /* Remove trailing zeroes */
    str_end = str + strlen(str);
    while (*--str_end == '0');
    str_end[1] = 0;
    /* Remove the decimal point if it happens to be an integer */
    if (*str_end == '.') {
        *str_end = 0;
    }
    return str;
}

void embTime_initNow(EmbTime* t) {
#ifdef ARDUINO
/*TODO: arduino embTime_initNow */
#else
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
#endif /* ARDUINO */
}

EmbTime embTime_time(EmbTime* t) {
#ifdef ARDUINO
/*TODO: arduino embTime_time */
#else

int divideByZero = 0;
divideByZero = divideByZero/divideByZero; /*TODO: wrap time() from time.h and verify it works consistently */

#endif /* ARDUINO */
    return *t;
}

/**
 * Finds the unit length vector \a result in the same direction as \a vector.
 */
void embVector_normalize(EmbVector vector, EmbVector* result) {
    double length = embVector_length(vector);

    if (!result) {
        printf("ERROR: emb-vector.c embVector_normalize(), result argument is null\n");
        return;
    }
    result->x = vector.x / length;
    result->y = vector.y / length;
}

/**
 * The scalar multiple \a magnitude of a vector \a vector. Returned as
 * \a result.
 */
void embVector_multiply(EmbVector vector, double magnitude, EmbVector* result) {
    if (!result) {
        printf("ERROR: emb-vector.c embVector_multiply(), result argument is null\n");
        return;
    }
    result->x = vector.x * magnitude;
    result->y = vector.y * magnitude;
}

/**
 * The sum of vectors \a v1 and \a v2 returned as \a result.
 */
void embVector_add(EmbVector v1, EmbVector v2, EmbVector* result) {
    if (!result) {
        printf("ERROR: emb-vector.c embVector_add(), result argument is null\n");
        return;
    }
    result->x = v1.x + v2.x;
    result->y = v1.y + v2.y;
}

/**
 * The average of vectors \a v1 and \a v2 returned as \a result.
 */
void embVector_average(EmbVector v1, EmbVector v2, EmbVector* result) {
    if (!result) {
        printf("ERROR: emb-vector.c embVector_add(), result argument is null\n");
        return;
    }
    result->x = (v1.x + v2.x) / 2.0;
    result->y = (v1.y + v2.y) / 2.0;
}

/**
 * The difference between vectors \a v1 and \a v2 returned as \a result.
 */
void embVector_subtract(EmbVector v1, EmbVector v2, EmbVector* result) {
    if (!result) {
        printf("ERROR: emb-vector.c embVector_subtract(), result argument is null\n");
        return;
    }
    result->x = v1.x - v2.x;
    result->y = v1.y - v2.y;
}

/**
 * The dot product as vectors \a v1 and \a v2 returned as a double.
 *
 * That is
 * (x)   (a) = xa+yb
 * (y) . (b)
 */
float embVector_dot(EmbVector v1, EmbVector v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

/**
 * The "cross product" as vectors \a v1 and \a v2 returned as a float.
 * Technically, this is one component only of a cross product, but in
 * our 2 dimensional framework we can use this as a scalar rather than
 * a vector in calculations.
 *
 * (a) x (c) = ad-bc
 * (b)   (d)
 */
float embVector_cross(EmbVector v1, EmbVector v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

/**
 * Since we aren't using full vector algebra here, all vectors are "vertical".
 * so this is like the product v1^{T} I_{2} v2 for our vectors \a v1 and \v2
 * so a "component-wise product". The result is stored at the pointer \a result.
 *
 * That is
 *      (1 0) (a) = (xa)
 * (x y)(0 1) (b)   (yb)
 */
void embVector_transpose_product(EmbVector v1, EmbVector v2, EmbVector* result) {
    if (!result) {
        printf("ERROR: emb-vector.c embVector_transpose_product(), result argument is null\n");
        return;
    }
    result->x = v1.x * v2.x;
    result->y = v1.y * v2.y;
}

/**
 * The length or absolute value of the vector \a vector. 
 */
float embVector_length(EmbVector vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

/*
 *  
 */
float embVector_relativeX(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    embVector_subtract(a1, a2, &b);
    embVector_subtract(a3, a2, &c);
    return embVector_dot(b, c);
}

/*
 *  
 */
float embVector_relativeY(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    embVector_subtract(a1, a2, &b);
    embVector_subtract(a3, a2, &c);
    return embVector_cross(b, c);
}

/*
 * The angle, measured anti-clockwise from the x-axis, of a vector v.
 */
float embVector_angle(EmbVector v)
{
    return atan2(v.y, v.x);
}

/*
 *  
 */
EmbVector embVector_unit(float angle)
{
    EmbVector a;
    a.x = cos(angle);
    a.y = sin(angle);
    return a;
}

/*
 *
 */
int convert(const char *inf, const char *outf) {
    EmbPattern* p = 0;
    int reader, writer;

    p = embPattern_create();
    if (!p) {
        printf("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    if (!embPattern_readAuto(p, inf)) {
        printf("ERROR: convert(), reading file was unsuccessful: %s\n", inf);
        embPattern_free(p);
        return 1;
    }

    reader = emb_identify_format(inf);
    writer = emb_identify_format(outf);
    if (formatTable[reader].type == EMBFORMAT_OBJECTONLY) {
        if (formatTable[writer].type == EMBFORMAT_STITCHONLY) {
            embPattern_movePolylinesToStitchList(p);
        }
    }

    if (!embPattern_writeAuto(p, outf)) {
        printf("ERROR: convert(), writing file %s was unsuccessful\n", outf);
        embPattern_free(p);
        return 1;
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
        for (j=0; j < numberOfFormats; j++) {
            EmbPattern *pattern;
            char fname_converted[100];
            char fname_image[100];
            int result;
            snprintf(fname_converted, 30, "test01_%s_converted_to%s",
                formatTable[i].extension+1, formatTable[j].extension);
            snprintf(fname_image, 30, "test01_%s_converted_to%s.ppm",
                formatTable[i].extension+1, formatTable[j].extension+1);
            printf("Attempting: %s %s\n", fname, fname_converted);
            result = convert(fname, fname_converted);
            embPattern_read(pattern, fname_converted, j);
            embImage_render(pattern, 20.0, 20.0, fname_image);
            embPattern_free(pattern);
            fprintf(f, "%d %d %f%% ", i, j, 100*success/(1.0*ntests));
            if (!result) {
                fprintf(f, "PASS\n");
                success++;
            } else {
                fprintf(f, "FAIL\n");
            }
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
    puts("Modify patterns:");
    puts("    --combine        takes 3 arguments and combines the first");
    puts("                     two by placing them atop each other and");
    puts("                     outputs to the third");
    puts("                        $ embroider --combine a.dst b.dst output.dst");
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

    width = 20.0;
    height = 20.0;

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
            emb_verbose = -1;
            break;
        case FLAG_VERBOSE:
        case FLAG_VERBOSE_SHORT:
            emb_verbose = 1;
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
        case FLAG_COMBINE:
            if (i + 3 < argc) {
                EmbPattern *out;
                EmbPattern *p1 = embPattern_create();
                EmbPattern *p2 = embPattern_create();
                embPattern_readAuto(p1, argv[i+1]);
                embPattern_readAuto(p2, argv[i+2]);
                out = embPattern_combine(p1, p2);
                embPattern_writeAuto(out, argv[i+3]);
                embPattern_free(p1);
                embPattern_free(p2);
                embPattern_free(out);
            }
            else {
                puts("--combine takes 3 arguments and you have supplied <3.");
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
        if (!flags) {
            puts("Please enter an output format for your file, see --help.");
        }
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


