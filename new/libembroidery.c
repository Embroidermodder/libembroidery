#include "embroidery.h"

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define EMB_BIG_ENDIAN                          0
#define EMB_LITTLE_ENDIAN                       1

#define ENDIAN_HOST                             EMB_LITTLE_ENDIAN

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
    unsigned long                streamSize;
    /* streamSize should be long long but in our case we shouldn't need it,
     * and hard to support on c89 cross platform */
    unsigned int                 streamSizeHigh; /* store the high int of streamsize */
} bcf_directory_entry;

typedef struct _bcf_file
{
    /*! The header for the CompoundFile */
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

    /*! The "Double Indirect FAT" for the CompoundFile */
    /* float-indirection file allocation table references */
    unsigned int fatSectorCount;
    unsigned int fatSectorEntries[109];
    unsigned int sectorSize;

    /*! The File Allocation Table for the Compound File */
    int          fatEntryCount;
    unsigned int fatEntries[255]; /* maybe make this dynamic */
    unsigned int numberOfEntriesInFatSector;

    /* TODO: switch this to an FILE* tmpfile */
    bcf_directory_entry *dirEntries;
    unsigned int        maxNumberOfDirectoryEntries;
    /* TODO: possibly add a directory tree in the future */
} bcf_file;

/* STATIC FUNCTION PROTOTYPES
 *
 * For functions that can be declared static and inlined automatically
 * that won't be called by users through embroidery.h.
 */

static int dereference_int(int p);
static int double_dereference_int(int table, int entry);
static int get_str(char *s, int p);

static EmbColor embColor_fromStr(unsigned char *b);
static void embColor_toStr(EmbColor c, unsigned char *b);
static void write_svg_color(FILE* file, EmbColor color);

static int husExpand(FILE* input, FILE* output, int mode);
static int husCompress(FILE* input, FILE* output, int mode);
 
static void readPecStitches(EmbPattern* pattern, FILE* file, const char* fileName);
static void writePecStitches(EmbPattern* pattern, FILE* file, const char* filename);

static char string_in_table(const char *buff, int table);
static EmbThread load_thread(int, int);

static void embTime_initNow(EmbTime* t);
static EmbTime embTime_time(EmbTime* t);

static char read100(EmbPattern *pattern, FILE* file, const char* fileName);
static char write100(EmbPattern *pattern, FILE* file, const char* fileName);
static char read10o(EmbPattern *pattern, FILE* file, const char* fileName);
static char write10o(EmbPattern *pattern, FILE* file, const char* fileName);
static char readBro(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeBro(EmbPattern *pattern, FILE* file, const char* fileName);
static char readCol(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeCol(EmbPattern *pattern, FILE* file, const char* fileName);
static char readCsd(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeCsd(EmbPattern *pattern, FILE* file, const char* fileName);
static char readCsv(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeCsv(EmbPattern *pattern, FILE* file, const char* fileName);
static char readDat(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeDat(EmbPattern *pattern, FILE* file, const char* fileName);
static char readDsb(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeDsb(EmbPattern *pattern, FILE* file, const char* fileName);
static char readDst(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeDst(EmbPattern *pattern, FILE* file, const char* fileName);
static char readDsz(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeDsz(EmbPattern *pattern, FILE* file, const char* fileName);
static char readDxf(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeDxf(EmbPattern *pattern, FILE* file, const char* fileName);
static char readEdr(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeEdr(EmbPattern *pattern, FILE* file, const char* fileName);
static char readEmd(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeEmd(EmbPattern *pattern, FILE* file, const char* fileName);
static char readExp(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeExp(EmbPattern *pattern, FILE* file, const char* fileName);
static char readExy(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeExy(EmbPattern *pattern, FILE* file, const char* fileName);
static char readFxy(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeFxy(EmbPattern *pattern, FILE* file, const char* fileName);
static char readGt(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeGt(EmbPattern *pattern, FILE* file, const char* fileName);
static char readHus(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeHus(EmbPattern *pattern, FILE* file, const char* fileName);
static char readInb(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeInb(EmbPattern *pattern, FILE* file, const char* fileName);
static char readInf(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeInf(EmbPattern *pattern, FILE* file, const char* fileName);
static char readJef(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeJef(EmbPattern *pattern, FILE* file, const char* fileName);
static char readKsm(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeKsm(EmbPattern *pattern, FILE* file, const char* fileName);
static char readMax(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeMax(EmbPattern *pattern, FILE* file, const char* fileName);
static char readMit(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeMit(EmbPattern *pattern, FILE* file, const char* fileName);
static char readNew(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeNew(EmbPattern *pattern, FILE* file, const char* fileName);
static char readOfm(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeOfm(EmbPattern *pattern, FILE* file, const char* fileName);
static char readPcd(EmbPattern *pattern, FILE* file, const char* fileName);
static char writePcd(EmbPattern *pattern, FILE* file, const char* fileName);
static char readPcm(EmbPattern *pattern, FILE* file, const char* fileName);
static char writePcm(EmbPattern *pattern, FILE* file, const char* fileName);
static char readPcq(EmbPattern *pattern, FILE* file, const char* fileName);
static char writePcq(EmbPattern *pattern, FILE* file, const char* fileName);
static char readPcs(EmbPattern *pattern, FILE* file, const char* fileName);
static char writePcs(EmbPattern *pattern, FILE* file, const char* fileName);
static char readPec(EmbPattern *pattern, FILE* file, const char* fileName);
static char writePec(EmbPattern *pattern, FILE* file, const char* fileName);
static char readPes(EmbPattern *pattern, FILE* file, const char* fileName);
static char writePes(EmbPattern *pattern, FILE* file, const char* fileName);
static char readPhb(EmbPattern *pattern, FILE* file, const char* fileName);
static char writePhb(EmbPattern *pattern, FILE* file, const char* fileName);
static char readPhc(EmbPattern *pattern, FILE* file, const char* fileName);
static char writePhc(EmbPattern *pattern, FILE* file, const char* fileName);
static char readPlt(EmbPattern *pattern, FILE* file, const char* fileName);
static char writePlt(EmbPattern *pattern, FILE* file, const char* fileName);
static char readRgb(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeRgb(EmbPattern *pattern, FILE* file, const char* fileName);
static char readSew(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeSew(EmbPattern *pattern, FILE* file, const char* fileName);
static char readShv(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeShv(EmbPattern *pattern, FILE* file, const char* fileName);
static char readSst(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeSst(EmbPattern *pattern, FILE* file, const char* fileName);
static char readStx(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeStx(EmbPattern *pattern, FILE* file, const char* fileName);
static char readSvg(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeSvg(EmbPattern *pattern, FILE* file, const char* fileName);
static char readT01(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeT01(EmbPattern *pattern, FILE* file, const char* fileName);
static char readT09(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeT09(EmbPattern *pattern, FILE* file, const char* fileName);
static char readTap(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeTap(EmbPattern *pattern, FILE* file, const char* fileName);
static char readThr(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeThr(EmbPattern *pattern, FILE* file, const char* fileName);
static char readTxt(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeTxt(EmbPattern *pattern, FILE* file, const char* fileName);
static char readU00(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeU00(EmbPattern *pattern, FILE* file, const char* fileName);
static char readU01(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeU01(EmbPattern *pattern, FILE* file, const char* fileName);
static char readVip(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeVip(EmbPattern *pattern, FILE* file, const char* fileName);
static char readVp3(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeVp3(EmbPattern *pattern, FILE* file, const char* fileName);
static char readXxx(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeXxx(EmbPattern *pattern, FILE* file, const char* fileName);
static char readZsk(EmbPattern *pattern, FILE* file, const char* fileName);
static char writeZsk(EmbPattern *pattern, FILE* file, const char* fileName);

static int encode_dst_ternary(int *, unsigned char *);
static void decode_dst_ternary(int *, unsigned char *);

/* FILE* */
static void embFile_read_string(FILE* file, char* buffer, int maxLength);
static FILE* embFile_open(const char* fileName, const char* mode, int optional);
static int embFile_readline(FILE* file, char *, int);
static void embFile_pad(FILE* f, char, int);
static void embfile_copy(FILE* f, int offset, FILE* out, int length);
static void embFile_readInt(FILE* file, void* data, int bytes);
static void embFile_readInt_be(FILE* file, void* data, int bytes);
static void embFile_writeInt(FILE* file, void* data, int bytes);
static void embFile_writeInt_be(FILE* file, void* data, int bytes);

static int bcfFile_read(FILE* file);
static FILE* GetFile(bcf_file* bcfFile, FILE* file, char* fileToFind);

static char identify_element(char *token);

void embArray_resample(EmbArray *a, EmbArray *usePt);
float GetRelativeX(EmbVector a1, EmbVector a2, EmbVector a3);
float GetRelativeY(EmbVector a1, EmbVector a2, EmbVector a3);
float GetAngle(EmbVector a, EmbVector b);
void embPattern_breakIntoColorBlocks(EmbPattern *pattern);
int embPolygon_breakIntoSeparateObjects(EmbArray *blocks);
int FindOutline(EmbArray *stitchData, EmbArray *result);
void embPolygon_simplifySection(EmbArray *vertices, EmbArray *_usePt, int i, int j, float distanceTolerance);
float embVector_distancePointLine(EmbVector p, EmbVector a, EmbVector b);
int embVector_collinear(EmbVector a1, EmbVector a2, EmbVector a3, float collinearity_tolerance);

/* Global Variables
 */

static unsigned char embBuffer[1024];
static FILE* datafile;
static FILE* memory[100];
static EmbArray arrays[100];
static EmbPattern patterns[3];
static int memory_files = 0;
static int active_patterns = 0;
static int random_state = 37;

/* Flag Defines
 */

/* These mirror the first table in libembroidery_data.asm. */
#define svg_property_token_table                (0*4)
#define svg_attribute_token_table               (1*4)
#define svg_token_lists                         (2*4)
#define brand_codes                             (3*4)
#define image_frame                             (4*4)
#define csv_header                              (5*4)
#define max_header                              (6*4)
#define csd_decoding_table                      (7*4)
#define vip_decoding_table                      (8*4)
#define format_list                             (9*4)
#define svg_token_table                         (10*4)
#define inkscape_token_table                    (11*4)
#define svg_element_token_table                 (12*4)
#define svg_media_property_token_table          (13*4)
#define stitch_labels                           (14*4)
#define dxf_version_r                           (15*4)
#define table_lengths                           (16*4)

#define brand_codes_length                      24
#define thread_type_length                      35
#define thread_color_offset                     30
#define thread_code                             33

/* path flag codes */
#define LINETO                                  0
#define MOVETO                                  1
#define BULGETOCONTROL                          2
#define BULGETOEND                              4
#define ELLIPSETORAD                            8
#define ELLIPSETOEND                            16
#define CUBICTOCONTROL1                         32
#define CUBICTOCONTROL2                         64
#define CUBICTOEND                              128
#define QUADTOCONTROL                           256
#define QUADTOEND                               512

#define SVG_CREATOR_NULL                        0
#define SVG_CREATOR_EMBROIDERMODDER             1
#define SVG_CREATOR_ILLUSTRATOR                 2
#define SVG_CREATOR_INKSCAPE                    3

#define SVG_EXPECT_NULL                         0
#define SVG_EXPECT_ELEMENT                      1
#define SVG_EXPECT_ATTRIBUTE                    2
#define SVG_EXPECT_VALUE                        3

/* SVG_TYPES */
#define SVG_NULL                                0
#define SVG_ELEMENT                             1
#define SVG_PROPERTY                            2
#define SVG_MEDIA_PROPERTY                      3
#define SVG_ATTRIBUTE                           4
#define SVG_CATCH_ALL                           5

/**
Type of sector
*/
#define CompoundFileSector_MaxRegSector         0xFFFFFFFA
#define CompoundFileSector_DIFAT_Sector         0xFFFFFFFC
#define CompoundFileSector_FAT_Sector           0xFFFFFFFD
#define CompoundFileSector_EndOfChain           0xFFFFFFFE
#define CompoundFileSector_FreeSector           0xFFFFFFFF

/**
Type of directory object
*/
#define ObjectTypeUnknown 0x00 /*!< Probably unallocated    */
#define ObjectTypeStorage 0x01 /*!< a directory type object */
#define ObjectTypeStream 0x02 /*!< a file type object      */
#define ObjectTypeRootEntry 0x05 /*!< the root entry          */

/**
Special values for Stream Identifiers
*/
#define CompoundFileStreamId_MaxRegularStreamId 0xFFFFFFFA /*!< All real stream Ids are less than this */
#define CompoundFileStreamId_NoStream 0xFFFFFFFF /*!< There is no valid stream Id            */

#define CSV_EXPECT_NULL           0
#define CSV_EXPECT_QUOTE1         1
#define CSV_EXPECT_QUOTE2         2
#define CSV_EXPECT_COMMA          3

#define CSV_MODE_NULL             0
#define CSV_MODE_COMMENT          '#'
#define CSV_MODE_VARIABLE         '>'
#define CSV_MODE_THREAD           '$'
#define CSV_MODE_STITCH           '*'

/* DXF Version Identifiers */
#define DXF_VERSION_R10           0
#define DXF_VERSION_R11           1
#define DXF_VERSION_R12           2
#define DXF_VERSION_R13           3
#define DXF_VERSION_R14           4
#define DXF_VERSION_R15           5
#define DXF_VERSION_R18           6
#define DXF_VERSION_R21           7
#define DXF_VERSION_R24           8
#define DXF_VERSION_R27           9

#define DXF_VERSION_2000          0
#define DXF_VERSION_2002          1
#define DXF_VERSION_2004          2
#define DXF_VERSION_2006          3
#define DXF_VERSION_2007          4
#define DXF_VERSION_2009          5
#define DXF_VERSION_2010          6
#define DXF_VERSION_2013          7

#define MAX_LAYERS                16
#define MAX_LAYER_NAME_LENGTH     30

#define HOOP_126X110              0
#define HOOP_110X110              1
#define HOOP_50X50                2
#define HOOP_140X200              3
#define HOOP_230X200              4

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

static EmbColor black = { 0, 0, 0 };

/*******************************************************************************
 * CODE SECTION
 */
 
static void binaryWriteByte(FILE* f, char b)
{
    fwrite(&b, 1, 1, f);
}

static void binaryWriteBytes(FILE* f, char *b, int n)
{
    fwrite(b, 1, n, f);
}

static void binaryWriteInt(FILE* f, int b)
{
    embFile_writeInt(f, &b, 4);
}

static void binaryWriteUInt(FILE* f, unsigned int b)
{
    embFile_writeInt(f, &b, 4);
}

static void binaryWriteShort(FILE* f, short b)
{
    embFile_writeInt(f, &b, 2);
}

static void binaryWriteUShort(FILE* f, unsigned short b)
{
    embFile_writeInt(f, &b, 2);
}

static void binaryWriteFloat(FILE* f, float fl)
{
    embFile_writeInt(f, &fl, 4);
}

static char binaryReadByte(FILE* f)
{
    char b;
    fread(&b, 1, 1, f);
    return b;
}

static char binaryReadBytes(FILE* f, char *s, int n)
{
    fread(s, 1, n, f);
}

static char binaryReadUInt8(FILE* f)
{
    unsigned char b;
    fread(&b, 1, 1, f);
    return b;
}

static float binaryReadFloat(FILE* f)
{
    float fl;
    fread(&fl, 4, 1, f);
    return fl;
}

static int bit(unsigned char a, int n)
{
    return ((a & (1 << n)) / (1 << n));
}

static int emb_min_int(int a, int b)
{
    if (a<b) return a;
    return b;
}

static int emb_max_int(int a, int b)
{
    if (a>b) return a;
    return b;
}

static float emb_min_float(float a, float b)
{
    if (a<b) return a;
    return b;
}

static float emb_max_float(float a, float b)
{
    if (a>b) return a;
    return b;
}

/* This is the same as the algorithm in the embedded system
 * version to give better consistency. Whereas other libm
 * replacements aren't because we can well approximate them.
 */
int random_int(void)
{
    /* Linear something RNG, need to look up better constants
     * all possible outputs happen (1, 999), one at a time.
     * Not 0, so the result is offset.
     *
     * Note that gcd(37, 1000) = gcd(39, 1000) = 1. 
     */
    random_state = (39*random_state)%1000;
    return random_state - 1;
}

static int dereference_int(int p)
{
    int out;
    fseek(datafile, p, SEEK_SET);
    fread(&out, 4, 1, datafile);
    return out;
}

static int double_dereference_int(int table, int entry)
{
    int out;
    out = dereference_int(table);
    out = dereference_int(out+4*entry);
    return out;
}

#define MAX_STRING_LENGTH       1024

/* These use void * so the sign of the char array has no effect as they are cast
 * to char * internally.
 */
static int string_equal(const void *a, const void *b);

static int get_str(char *s, int p)
{
    int i;
    fseek(datafile, p, SEEK_SET);
    for (i=0; i<MAX_STRING_LENGTH; i++) {
        fread(s+i, 1, 1, datafile);
        if (!s[i]) {
            return 1;
        }
    }
    return 0;
}

static int string_equal(const void *a, const void *b)
{
    return !strcmp(a, b);
}

static void make_directory(const char *dir, int mode)
{
#ifdef _WIN32
    mkdir(dir);
#else
    mkdir(dir, mode);
#endif
}

EmbArray* embArray_create(int type)
{
    int sizes[] = {
        sizeof(EmbArc), sizeof(EmbCircle), sizeof(EmbEllipse),
        sizeof(int), sizeof(EmbLine), sizeof(EmbPathObject),
        sizeof(EmbPoint), sizeof(EmbPolygonObject),
        sizeof(EmbPolylineObject), sizeof(EmbRect), sizeof(EmbSplineObject),
        sizeof(EmbStitch), sizeof(EmbThread), sizeof(EmbVector),
        sizeof(char), sizeof(EmbArray)
    };
    char fname[40];
    EmbArray* p;
    p = arrays+memory_files;
    p->type = type;
    p->length = 0;
    p->size = sizes[type];
    p->file_id = memory_files;
    memory_files++;
    memory[p->file_id] = tmpfile();
    return p;
}

int embArray_add(EmbArray *p, void *data)
{
    fseek(memory[p->file_id], p->length*p->size, SEEK_SET);
    fwrite(data, p->size, 1, memory[p->file_id]);
    p->length++;
    return 1;    
}

int embArray_get(EmbArray *p, void *data, int i)
{
    fseek(memory[p->file_id], i*p->size, SEEK_SET);
    fread(data, p->size, 1, memory[p->file_id]);
    return 1;    
}

int embArray_set(EmbArray *p, void *data, int i)
{
    fseek(memory[p->file_id], i*p->size, SEEK_SET);
    fwrite(data, p->size, 1, memory[p->file_id]);
    return 1;    
}

static void embArray_read(FILE* file, EmbArray *a, int offset, int n)
{
    int i;
    void *data = (void*)embBuffer;
    fseek(file, offset, SEEK_SET);
    for (i=0; i<n; i++) {
        fread(data, a->size, 1, file);
        embArray_set(a, data, i);
    }
}

static void embArray_write(FILE* file, EmbArray *a, int offset, int n)
{
    int i;
    void *data = (void*)embBuffer;
    fseek(file, offset, SEEK_SET);
    for (i=0; i<n; i++) {
        embArray_get(a, data, i);
        fwrite(data, a->size, 1, file);
    }
}

void embArray_free(EmbArray* p)
{
    /* delete file, will be automatic for TMPFILE */
    fclose(memory[p->file_id]);
}

int husExpand(FILE* input, FILE* output, int compressionType)
{
    /* TODO: find and analyse some HUS encoded files and DST equivalents */
    return 0;
}

int husCompress(FILE* input, FILE* output, int compressionType)
{
    /* TODO: find and analyse some HUS encoded files and DST equivalents */

    return 0;
}

#if ENDIAN_HOST == EMB_LITTLE_ENDIAN

static void embFile_readInt(FILE* file, void* data, int bytes)
{
    fread(data, 1, bytes, file);
}

static void embFile_readInt_be(FILE* file, void* data, int bytes)
{
    char *a = (char*)data, c;
    fread(data, 1, bytes, file);
    if (bytes==2) {
        c = a[0];
        a[0] = a[1];
        a[1] = c;
    }
    else {
        c = a[0];
        a[0] = a[3];
        a[3] = c;
        c = a[1];
        a[1] = a[2];
        a[2] = c;
    }
}

static void embFile_writeInt(FILE* file, void* data, int bytes)
{
    fwrite(data, bytes, 1, file);
}

static void embFile_writeInt_be(FILE* file, void* data, int bytes)
{
    char *a = (char *)data, c;
    if (bytes==2) {
        c = a[0];
        a[0] = a[1];
        a[1] = c;
    }
    else {
        c = a[0];
        a[0] = a[3];
        a[3] = c;
        c = a[1];
        a[1] = a[2];
        a[2] = c;
    }
    fwrite(a, 1, bytes, file);
}

#else

static void embFile_readInt(FILE* file, void* data, int bytes)
{
    char *a = (char*)data, c;
    fread(data, 1, bytes, file);
    if (bytes==2) {
        c = a[0];
        a[0] = a[1];
        a[1] = c;
    }
    else {
        c = a[0];
        a[0] = a[3];
        a[3] = c;
        c = a[1];
        a[1] = a[2];
        a[2] = c;
    }
}

static void embFile_readInt_be(FILE* file, void* data, int bytes)
{
    fread(data, 1, bytes, file);
}

static void embFile_writeInt(FILE* file, void* data, int bytes)
{
    char *a = (char *)data, c;
    if (bytes==2) {
        c = a[0];
        a[0] = a[1];
        a[1] = c;
    }
    else {
        c = a[0];
        a[0] = a[3];
        a[3] = c;
        c = a[1];
        a[1] = a[2];
        a[2] = c;
    }
    fwrite(a, 1, bytes, file);
}

static void embFile_writeInt_be(FILE* file, void* data, int bytes)
{
    fwrite(data, bytes, 1, file);
}

#endif

static void binaryReadString(FILE* file, char* buffer, int maxLength)
{
    int i;
    for (i=0; i < maxLength; i++) {
        fread(buffer+i, 1, 1, file);
        if (!buffer[i])
            break;
    }
}

static void embTime_initNow(EmbTime* t)
{
#if ARDUINO
/*TODO: arduino embTime_initNow */
#else
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    t->year = timeinfo->tm_year;
    t->month = timeinfo->tm_mon;
    t->day = timeinfo->tm_mday;
    t->hour = timeinfo->tm_hour;
    t->minute = timeinfo->tm_min;
    t->second = timeinfo->tm_sec;
#endif /* ARDUINO */
}

static EmbTime embTime_time(EmbTime* t)
{
#if ARDUINO
/*TODO: arduino embTime_time */
#else

    int divideByZero = 0;
    divideByZero = divideByZero / divideByZero;
    /*TODO: wrap time() from time.h and verify it works consistently */

#endif /* ARDUINO */
    return *t;
}

/* Converts a 6 digit hex string (I.E. "00FF00") into an
 * EmbColor and returns it. */
EmbColor embColor_fromHexStr(char* val)
{
    int i;
    EmbColor color;
    for (i = 0; i < 6; i++) {
        if (val[i] >= 'A' && val[i] <= 'F') {
            val[i] = '9' + val[i] - 'A' + 1;
        }
        val[i] -= '0';
    }

    color.r = val[0] * 16 + val[1];
    color.g = val[2] * 16 + val[3];
    color.b = val[4] * 16 + val[5];
    return color;
}

static const float embConstantPi = 3.1415926535;

float radians(float degree)
{
    return degree * embConstantPi / 180.0;
}

float degrees(float radian)
{
    return radian * 180.0 / embConstantPi;
}

/* Calculus based approach at determining whether a polygon is clockwise or counterclockwise.
 * Returns true if arc is clockwise. */
char isArcClockwise(EmbArc arc)
{
    float edge1 = (arc.mid.x - arc.start.x) * (arc.mid.y + arc.start.y);
    float edge2 = (arc.end.x - arc.mid.x) * (arc.end.y + arc.mid.y);
    float edge3 = (arc.start.x - arc.end.x) * (arc.start.y + arc.end.y);
    if (edge1 + edge2 + edge3 >= 0.0) {
        return 1;
    }
    return 0;
}

/* Calculates the CenterPoint of the Arc */
void getArcCenter(EmbArc arc, EmbVector* arcCenter)
{
    EmbVector a, b, pa, pb;
    EmbLine line1, line2;
    embVector_subtract(arc.mid, arc.start, &a);
    embVector_average(arc.mid, arc.start, &(line1.start));
    embVector_normalVector(a, &pa, 0);
    embVector_add(line1.start, pa, &(line1.end));

    embVector_subtract(arc.end, arc.mid, &b);
    embVector_average(arc.end, arc.mid, &(line2.start));
    embVector_normalVector(b, &pb, 0);
    embVector_add(line2.start, pb, &(line2.end));

    embLine_intersectionPoint(line1, line2, arcCenter);
}

/* Calculates Arc Geometry from Bulge Data.
 * Returns false if there was an error calculating the data. */
char getArcDataFromBulge(float bulge, EmbArc* arc, EmbVector* arcCenter,
    float* radius, float* diameter, float* chord,
    EmbVector* chordMid,
    float* sagitta, float* apothem,
    float* incAngleInDegrees, char* clockwise)
{
    EmbVector f, diff;
    float incAngleInRadians;
    float chordAngleInRadians;
    float sagittaAngleInRadians;

    if (bulge >= 0.0) {
        *clockwise = 0;
    } else {
        *clockwise = 1;
    }

    /* Calculate the Included Angle in Radians */
    incAngleInRadians = atan2(bulge, 1.0) * 4.0;

    embVector_subtract(arc->end, arc->start, &diff);
    *chord = embVector_getLength(diff);

    *radius = fabs(*chord / (2.0 * sin(incAngleInRadians / 2.0)));
    *diameter = *radius * 2.0;
    *sagitta = fabs((*chord / 2.0) * bulge);
    *apothem = fabs(*radius - *sagitta);

    embVector_average(arc->start, arc->end, chordMid);

    chordAngleInRadians = atan2(diff.y, diff.x);

    if (*clockwise) {
        sagittaAngleInRadians = chordAngleInRadians + radians(90.0);
    } else {
        sagittaAngleInRadians = chordAngleInRadians - radians(90.0);
    }

    f.x = *sagitta * cos(sagittaAngleInRadians);
    f.y = *sagitta * sin(sagittaAngleInRadians);
    embVector_add(*chordMid, f, &(arc->mid));

    getArcCenter(*arc, arcCenter);

    *incAngleInDegrees = degrees(incAngleInRadians);

    /* Confirm the direction of the Arc, it should match the Bulge */
    if (*clockwise != isArcClockwise(*arc)) {
        puts("error_arc_data");
        return 0;
    }

    return 1;
}

/****************************************************************
 * Calculates the intersection points of two overlapping circles.
 * Returns true if the circles intersect.
 * Returns false if the circles do not intersect.
 ****************************************************************/
int getCircleCircleIntersections(EmbCircle c0, EmbCircle c1, EmbVector* p3, EmbVector* p4)
{
    EmbVector diff, p2, m;
    float a, h, d;
    embVector_subtract(c1.center, c0.center, &diff);
    d = embVector_getLength(diff); /* Distance between centers */

    /*Circles share centers. This results in division by zero,
      infinite solutions or one circle being contained within the other. */
    if (d == 0.0) {
        return 0;
    }
    /* Circles do not touch each other */
    else if (d > (c0.radius + c1.radius)) {
        return 0;
    }
    /* One circle is contained within the other */
    else if (d < (c0.radius - c1.radius)) {
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

    a = ((c0.radius * c0.radius) - (c1.radius * c1.radius) + (d * d)) / (2.0 * d);
    /* Solve for h by substituting a into a^2 + h^2 = r0^2 */
    h = sqrt((c0.radius * c0.radius) - (a * a));

    /*Find point p2 by adding the a offset in relation to line d to point p0 */

    embVector_multiply(diff, a / d, &p2);
    embVector_add(c0.center, p2, &p2);

    /* Tangent circles have only one intersection

       TODO: using == in floating point arithmetic
       doesn't account for the machine accuracy, having
       a stated (float) tolerance value would help.
    */
    if (d == (c0.radius + c1.radius)) {
        *p3 = *p4 = p2;
        return 1;
    }

    /* Get the perpendicular slope by multiplying by the negative reciprocal
     * Then multiply by the h offset in relation to d to get the actual offsets */
    m.x = -(diff.y * h / d);
    m.y = (diff.x * h / d);

    /* Add the offsets to point p2 to obtain the intersection points */
    embVector_add(p2, m, p3);
    embVector_subtract(p2, m, p4);

    return 1;
}

/****************************************************************
 * Calculates the tangent points on circle from a given point.
 * Returns true if the given point lies outside the circle.
 * Returns false if the given point is inside the circle.
 ****************************************************************/
int getCircleTangentPoints(EmbCircle c, EmbVector point, EmbVector* t0, EmbVector* t1)
{
    EmbCircle p;
    EmbVector diff;
    float hyp;
    embVector_subtract(point, c.center, &diff);
    hyp = embVector_getLength(diff); /* Distance to center of circle */

    /* Point is inside the circle */
    if (hyp < c.radius) {
        return 0;
    }
    /* Point is lies on the circle, so there is only one tangent point */
    else if (hyp == c.center.y) {
        *t0 = *t1 = point;
        return 1;
    }

    /* Since the tangent lines are always perpendicular to the radius, so
     * we can use the Pythagorean theorem to solve for the missing side */
    p.radius = sqrt((hyp * hyp) - (c.radius * c.radius));
    p.center = point;
    return getCircleCircleIntersections(c, p, t0, t1);
}

float embEllipse_diameterX(EmbEllipse ellipse)
{
    return ellipse.radius.x * 2.0;
}

float embEllipse_diameterY(EmbEllipse ellipse)
{
    return ellipse.radius.y * 2.0;
}

float embEllipse_width(EmbEllipse ellipse)
{
    return ellipse.radius.x * 2.0;
}

float embEllipse_height(EmbEllipse ellipse)
{
    return ellipse.radius.y * 2.0;
}

void embVector_normalVector(EmbVector dir, EmbVector* result, int clockwise)
{
    float temp;
    embVector_normalize(dir, result);
    temp = result->x;
    result->x = result->y;
    result->y = -temp;
    if (!clockwise) {
        embVector_multiply(*result, -1.0, result);
    }
}

/*! Finds the normalized vector perpendicular (clockwise) to the line
 * given by v1->v2 (normal to the line) */
void embLine_normalVector(EmbLine line, EmbVector* result, int clockwise)
{
    if (!result) {
        puts("error_vector_normal");
        return;
    }
    embVector_subtract(line.end, line.end, result);
    embVector_normalVector(*result, result, clockwise);
}

/**
 * Finds the intersection of two lines given by v1->v2 and v3->v4
 * and sets the value in the result variable.
 */
unsigned char embLine_intersectionPoint(EmbLine line1, EmbLine line2, EmbVector* result)
{
    EmbVector D1, D2, C;
    float tolerance, det;
    tolerance = 1e-10;
    embVector_subtract(line1.end, line1.start, &D2);
    C.y = embVector_cross(line1.start, D2);

    embVector_subtract(line2.end, line2.start, &D1);
    C.x = embVector_cross(line2.start, D1);

    det = embVector_cross(D1, D2);

    if (!result) {
        puts("error_line_intersection");
        return 0;
    }
    /*TODO: The code below needs revised since division by zero can still occur */
    if (fabs(det) < tolerance) {
        puts("error_line_parallel");
        return 0;
    }
    result->x = D2.x * C.x - D1.x * C.y;
    result->y = D2.y * C.x - D1.y * C.y;
    embVector_multiply(*result, 1.0 / det, result);
    return 1;
}

float embRect_x(EmbRect rect)
{
    return rect.left;
}

float embRect_y(EmbRect rect)
{
    return rect.top;
}

float embRect_width(EmbRect rect)
{
    return rect.right - rect.left;
}

float embRect_height(EmbRect rect)
{
    return rect.bottom - rect.top;
}

/* Sets the left edge of the rect to x. The right edge is not modified. */
void embRect_setX(EmbRect* rect, float x)
{
    rect->left = x;
}

/* Sets the top edge of the rect to y. The bottom edge is not modified. */
void embRect_setY(EmbRect* rect, float y)
{
    rect->top = y;
}

/* Sets the width of the rect to w. The right edge is modified. The left edge is not modified. */
void embRect_setWidth(EmbRect* rect, float w)
{
    rect->right = rect->left + w;
}

/* Sets the height of the rect to h. The bottom edge is modified. The top edge is not modified. */
void embRect_setHeight(EmbRect* rect, float h)
{
    rect->bottom = rect->top + h;
}

void embRect_setCoords(EmbRect* rect, float x1, float y1, float x2, float y2)
{
    rect->left = x1;
    rect->top = y1;
    rect->right = x2;
    rect->bottom = y2;
}

void embRect_setRect(EmbRect* rect, float x, float y, float w, float h)
{
    rect->left = x;
    rect->top = y;
    rect->right = x + w;
    rect->bottom = y + h;
}

/**
 * Finds the unit length vector \a result in the same direction as \a vector.
 */
void embVector_normalize(EmbVector vector, EmbVector* result)
{
    float length;
    length = embVector_getLength(vector);

    if (!result) {
        puts("error_normalize");
        return;
    }
    result->x = vector.x / length;
    result->y = vector.y / length;
}

/**
 * The scalar multiple \a magnitude of a vector \a vector. Returned as
 * \a result.
 */
void embVector_multiply(EmbVector vector, float magnitude, EmbVector* result)
{
    if (!result) {
        puts("error_vector_multiply");
        return;
    }
    result->x = vector.x * magnitude;
    result->y = vector.y * magnitude;
}

/**
 * The sum of vectors \a v1 and \a v2 returned as \a result.
 */
void embVector_add(EmbVector v1, EmbVector v2, EmbVector* result)
{
    if (!result) {
        puts("error_vector_add");
        return;
    }
    result->x = v1.x + v2.x;
    result->y = v1.y + v2.y;
}

/**
 * The average of vectors \a v1 and \a v2 returned as \a result.
 */
void embVector_average(EmbVector v1, EmbVector v2, EmbVector* result)
{
    if (!result) {
        puts("error_vector_average");
        return;
    }
    result->x = (v1.x + v2.x) / 2.0;
    result->y = (v1.y + v2.y) / 2.0;
}

/**
 * The difference between vectors \a v1 and \a v2 returned as \a result.
 */
void embVector_subtract(EmbVector v1, EmbVector v2, EmbVector* result)
{
    if (!result) {
        puts("error_vector_subtract");
        return;
    }
    result->x = v1.x - v2.x;
    result->y = v1.y - v2.y;
}

/**
 * The dot product as vectors \a v1 and \a v2 returned as a float.
 *
 * That is
 * (x)   (a) = xa+yb
 * (y) . (b)
 */
float embVector_dot(EmbVector v1, EmbVector v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

/**
 * The Euclidean distance between points v1 and v2, aka |v2-v1|.
 */
float embVector_distance(EmbVector v1, EmbVector v2)
{
    EmbVector v3;
    embVector_subtract(v1, v2, &v3);
    return sqrt(embVector_dot(v3, v3));
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
void embVector_component_product(EmbVector v1, EmbVector v2, EmbVector* result)
{
    if (!result) {
        puts("error_vector_component_product");
        return;
    }
    result->x = v1.x * v2.x;
    result->y = v1.y * v2.y;
}

/**
 * The length or absolute value of the vector \a vector. 
 */
float embVector_getLength(EmbVector vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

/**
 * The length or absolute value of the vector \a vector. 
 */
float embVector_cross(EmbVector a, EmbVector b)
{
    return a.x * b.y - a.y * b.x;
}

/*! Returns a pointer to an EmbPattern. It is created on the heap.
 * The caller is responsible for freeing the allocated memory with
 * embPattern_free(). */
EmbPattern* embPattern_create(void)
{
    EmbPattern* p;
    p = patterns+active_patterns;
    active_patterns++;
    if (!p) {
        puts("Ran out of memory for active patterns.");
        return 0;
    }

    strcpy(p->name, "Untitled");
    p->currentColorIndex = 0;
    p->stitchList = embArray_create(EMB_STITCH);
    p->threads = embArray_create(EMB_THREAD);
    p->hoop.height = 0.0;
    p->hoop.width = 0.0;
    p->arcs = embArray_create(EMB_ARC);
    p->circles = embArray_create(EMB_CIRCLE);
    p->ellipses = embArray_create(EMB_ELLIPSE);
    p->lines = embArray_create(EMB_LINE);
    p->paths = embArray_create(EMB_PATH);
    p->points = embArray_create(EMB_POINT);
    p->polygons = embArray_create(EMB_POLYGON);
    p->polylines = embArray_create(EMB_POLYLINE);
    p->rects = embArray_create(EMB_RECT);
    p->splines = embArray_create(EMB_SPLINE);
    p->ax = 0;
    p->ay = 0;
    p->mx = 0;
    p->my = 0;
    p->lastPosition.x = 0.0;
    p->lastPosition.y = 0.0;
    p->dstJumpsPerTrim = 6;
    p->home.x = 0.0;
    p->home.y = 0.0;

    return p;
}

void embPattern_hideStitchesOverLength(EmbPattern* p, int length)
{
    float prevX, prevY;
    int i;
    EmbStitch st;

    if (!p) {
        puts("embPattern_hideStitchesOverLength: no pattern in memory.");
        return;
    }

    prevX = 0;
    prevY = 0;
    for (i = 0; i < p->stitchList->length; i++) {
        embArray_get(p->stitchList, &st, i);
        if ((fabs(st.x - prevX) > length) || (fabs(st.y - prevY) > length)) {
            st.flags |= TRIM;
            st.flags &= ~NORMAL;
        }
        prevX = st.x;
        prevY = st.y;
        embArray_set(p->stitchList, &st, i);
    }
}

int embPattern_addThread(EmbPattern* p, EmbThread thread)
{
    embArray_add(p->threads, &thread);
    return 1;
}

void embPattern_fixColorCount(EmbPattern* p)
{
    /* fix color count to be max of color index. */
    int maxColorIndex = 0, i;

    if (!p) {
        puts("embPattern_fixColorCount: no pattern in memory.");
        return;
    }
    for (i = 0; i < p->stitchList->length; i++) {
        EmbStitch st;
        embArray_get(p->stitchList, &st, i);
        maxColorIndex = emb_max_int(maxColorIndex, st.color);
    }
    while (p->threads->length <= maxColorIndex) {
        embPattern_addThread(p, embThread_getRandom());
    }
    /*
    while (p->threadLists->length > (maxColorIndex + 1)) {
        TODO: erase last color    p->threadList.pop_back();
    }
    */
}

/*! Copies all of the EmbStitchList data to EmbPolylineObjectList data for pattern (\a p). */
void embPattern_copyStitchListToPolylines(EmbPattern* p)
{
    EmbPointObject point;
    int breakAtFlags, i;
    EmbStitch st;

    if (!p) {
        puts("error_copy_stitch_list_no_pattern");
        return;
    }

    breakAtFlags = (STOP | JUMP | TRIM);

    for (i = 0; i < p->stitchList->length; i++) {
        EmbArray* pointList;
        EmbColor color;
        pointList = 0;
        for (i = 0; i < p->stitchList->length; i++) {
            embArray_get(p->stitchList, &st, i);
            if (st.flags & breakAtFlags) {
                break;
            }
            if (!(st.flags & JUMP)) {
                if (!pointList) {
                    EmbThread t;
                    embArray_get(p->threads, &t, st.color);
                    pointList = embArray_create(EMB_POINT);
                    color = t.color;
                }
                point.x = st.x;
                point.y = st.y;
                point.lineType = 0;
                point.color = color;
                embArray_add(pointList, &point);
            }
        }

        /* NOTE: Ensure empty polylines are not created. This is critical. */
        if (pointList) {
            EmbPolylineObject currentPolyline;
            currentPolyline.pointList = pointList;
            currentPolyline.color = color;
            currentPolyline.lineType = 1;
            /* TODO: Determine what the correct value should be. */

            if (!p->polylines) {
                p->polylines = embArray_create(EMB_POLYLINE);
            }
            embArray_add(p->polylines, &currentPolyline);
        }
        embArray_free(pointList);
    }
}

/*! Copies all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
void embPattern_copyPolylinesToStitchList(EmbPattern* p)
{
    int firstObject = 1, i, j;
    /*int currentColor = polyList->polylineObj->color TODO: polyline color */

    if (!p) {
        puts("ERROR: embPattern_copyPolylinesToStitchList(), p==0\n");
        return;
    }
    if (!p->polylines) {
        puts("ERROR: embPattern_copyPolylinesToStitchList(), p==0\n");
        return;
    }
    for (i = 0; i < p->polylines->length; i++) {
        EmbPolylineObject currentPoly;
        EmbArray* currentPointList;
        EmbThread thread;

        embArray_get(p->polylines, &currentPoly, i);
        currentPointList = currentPoly.pointList;
        if (!currentPointList) {
            puts("ERROR: embPattern_copyPolylinesToStitchList(), currentPointList is null\n");
            return;
        }

        strcpy(thread.catalogNumber, "NULL");
        thread.color = currentPoly.color;
        strcpy(thread.description, "NULL");
        embPattern_addThread(p, thread);

        EmbVector v;
        if (!firstObject) {
            embArray_get(currentPointList, &v, 0);
            embPattern_addStitchAbs(p, v.x, v.y, TRIM, 1);
            embPattern_addStitchRel(p, 0.0, 0.0, STOP, 1);
        }

        embArray_get(currentPointList, &v, 0);
        embPattern_addStitchAbs(p, v.x, v.y, JUMP, 1);
        for (j = 1; j < currentPointList->length; j++) {
            embArray_get(currentPointList, &v, j);
            embPattern_addStitchAbs(p, v.x, v.y, NORMAL, 1);
        }
        firstObject = 0;
    }
}

/*! Moves all of the EmbStitchList data to EmbPolylineObjectList data for pattern (\a p). */
void embPattern_moveStitchListToPolylines(EmbPattern* p)
{
    if (!p) {
        puts("ERROR: embPattern_moveStitchListToPolylines(), p==0\n");
        return;
    }
    embPattern_copyStitchListToPolylines(p);
    /* Free the stitchList and threadList since their data has now been transferred to polylines */
    embArray_free(p->stitchList);
}

/*! Moves all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
void embPattern_movePolylinesToStitchList(EmbPattern* p)
{
    if (!p) {
        puts("ERROR: embPattern_movePolylinesToStitchList(), p==0\n");
        return;
    }
    embPattern_copyPolylinesToStitchList(p);
    embArray_free(p->polylines);
}

/*! Adds a stitch to the pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
void embPattern_addStitchAbs(EmbPattern* p, float x, float y, int flags, int isAutoColorIndex)
{
    EmbStitch s;

    if (!p || !p->stitchList) {
        puts("ERROR: embPattern_addStitchAbs(), p==0\n");
        return;
    }

    if (flags & END) {
        if (p->stitchList->length == 0) {
            return;
        }
        /* Prevent unnecessary multiple END stitches */
        embArray_get(p->stitchList, &s, p->stitchList->length - 1);
        if (s.flags & END) {
            puts("ERROR: embPattern_addStitchAbs(), found multiple END stitches\n");
            return;
        }

        embPattern_fixColorCount(p);

        /* HideStitchesOverLength(127); TODO: fix or remove this */
    }

    if (flags & STOP) {
        if (p->stitchList->length == 0) {
            return;
        }
        if (isAutoColorIndex) {
            p->currentColorIndex++;
        }
    }

    /* NOTE: If the stitchList is empty, we will create it before adding stitches to it.
     * The first coordinate will be the HOME position. */
    if (!p->stitchList) {
        /* NOTE: Always HOME the machine before starting any stitching */
        s.x = p->home.x;
        s.y = p->home.y;
        s.flags = JUMP;
        s.color = p->currentColorIndex;
        p->stitchList = embArray_create(EMB_STITCH);
        embArray_add(p->stitchList, &s);
    }

    s.x = x;
    s.y = y;
    s.flags = flags;
    s.color = p->currentColorIndex;
    embArray_add(p->stitchList, &s);
    p->lastPosition.x = s.x;
    p->lastPosition.y = s.y;
}

/*! Adds a stitch to the pattern (\a p) at the relative position (\a dx,\a dy) to the previous stitch. Positive y is up. Units are in millimeters. */
void embPattern_addStitchRel(EmbPattern* p, float dx, float dy, int flags, int isAutoColorIndex)
{
    EmbVector home;
    float x, y;

    if (!p) {
        puts("ERROR: embPattern_addStitchRel(), p==0\n");
        return;
    }
    if (p->stitchList) {
        x = p->lastPosition.x + dx;
        y = p->lastPosition.y + dy;
    } else {
        /* NOTE: The stitchList is empty, so add it to the HOME position.
         * The embStitchList_create function will ensure the first coordinate is at the HOME position. */
        x = p->home.x + dx;
        y = p->home.y + dy;
    }
    embPattern_addStitchAbs(p, x, y, flags, isAutoColorIndex);
}

void embPattern_changeColor(EmbPattern* p, int index)
{
    if (!p) {
        puts("ERROR: embPattern_changeColor(), p==0\n");
        return;
    }
    p->currentColorIndex = index;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int embPattern_readAuto(EmbPattern* pattern, const char* fileName) /* TODO: Write test case using this convenience function. */
{
    int reader;

    reader = embReaderWriter_getByFileName(fileName);
    if (reader < 0) {
        printf("ERROR: embPattern_read(), unsupported read file type: %s\n", fileName);
        return 0;
    }

    return embPattern_read(pattern, fileName, reader);
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int embPattern_writeAuto(EmbPattern* pattern, const char* fileName) /* TODO: Write test case using this convenience function. */
{
    int writer;

    writer = embReaderWriter_getByFileName(fileName);
    if (writer < 0) {
        printf("ERROR: embPattern_write(), unsupported write file type: %s\n", fileName);
        return 0;
    }

    return embPattern_write(pattern, fileName, writer);
}

/* Very simple scaling of the x and y axis for every point.
* Doesn't insert or delete stitches to preserve density. */
void embPattern_scale(EmbPattern* p, float scale)
{
    int i;

    if (!p) {
        puts("ERROR: embPattern_scale(), p==0\n");
        return;
    }

    for (i = 0; i < p->stitchList->length; i++) {
        EmbStitch st;
        embArray_get(p->stitchList, &st, i);
        st.x *= scale;
        st.y *= scale;
        embArray_set(p->stitchList, &st, i);
    }
}

/*! Returns an EmbRect that encapsulates all stitches and objects in the pattern (\a p). */
EmbRect embPattern_calcBoundingBox(EmbPattern* p)
{
    EmbRect boundingRect;
    EmbStitch pt;
    EmbBezier bezier;
    int i, j;

    boundingRect.left = 0;
    boundingRect.right = 0;
    boundingRect.top = 0;
    boundingRect.bottom = 0;

    if (!p || !p->stitchList) {
        puts("ERROR: embPattern_calcBoundingBox(), p==0\n");
        return boundingRect;
    }

    /* Calculate the bounding rectangle.  It's needed for smart repainting. */
    /* TODO: Come back and optimize this mess so that after going thru all objects
            and stitches, if the rectangle isn't reasonable, then return a default rect */
    if (!p->stitchList && !(p->arcs || p->circles || p->ellipses || p->lines || p->points || p->polygons || p->polylines || p->rects || p->splines)) {
        boundingRect.top = 0.0;
        boundingRect.left = 0.0;
        boundingRect.bottom = 1.0;
        boundingRect.right = 1.0;
        return boundingRect;
    }
    boundingRect.left = 99999.0;
    boundingRect.top = 99999.0;
    boundingRect.right = -99999.0;
    boundingRect.bottom = -99999.0;

    for (i = 0; i < p->stitchList->length; i++) {
        /* If the point lies outside of the accumulated bounding
        * rectangle, then inflate the bounding rect to include it. */
        embArray_get(p->stitchList, &pt, i);
        if (!(pt.flags & TRIM)) {
            boundingRect.left = emb_min_float(boundingRect.left, pt.x);
            boundingRect.top = emb_min_float(boundingRect.top, pt.y);
            boundingRect.right = emb_max_float(boundingRect.right, pt.x);
            boundingRect.bottom = emb_max_float(boundingRect.bottom, pt.y);
        }
    }

    /* TODO: embPattern_calcBoundingBox for arcs, for now just checks the start point */
    for (i = 0; i < p->arcs->length; i++) {
        EmbArc arc;
        embArray_get(p->arcs, &arc, i);
        boundingRect.left = emb_min_float(boundingRect.left, arc.start.x);
        boundingRect.top = emb_min_float(boundingRect.top, arc.start.y);
        boundingRect.right = emb_max_float(boundingRect.right, arc.start.x);
        boundingRect.bottom = emb_max_float(boundingRect.bottom, arc.start.y);
    }

    for (i = 0; i < p->circles->length; i++) {
        EmbCircle circle;
        embArray_get(p->circles, &circle, i);
        boundingRect.left = emb_min_float(boundingRect.left, circle.center.x - circle.radius);
        boundingRect.top = emb_min_float(boundingRect.top, circle.center.y - circle.radius);
        boundingRect.right = emb_max_float(boundingRect.right, circle.center.x + circle.radius);
        boundingRect.bottom = emb_max_float(boundingRect.bottom, circle.center.y + circle.radius);
    }

    for (i = 0; i < p->ellipses->length; i++) {
        /* TODO: account for rotation */
        EmbEllipse ellipse;
        embArray_get(p->ellipses, &ellipse, i);
        boundingRect.left = emb_min_float(boundingRect.left, ellipse.center.x - ellipse.radius.x);
        boundingRect.top = emb_min_float(boundingRect.top, ellipse.center.y - ellipse.radius.y);
        boundingRect.right = emb_max_float(boundingRect.right, ellipse.center.x + ellipse.radius.x);
        boundingRect.bottom = emb_max_float(boundingRect.bottom, ellipse.center.y + ellipse.radius.y);
    }

    for (i = 0; i < p->lines->length; i++) {
        EmbLine line;
        embArray_get(p->lines, &line, i);
        boundingRect.left = emb_min_float(boundingRect.left, emb_min_float(line.start.x, line.end.x));
        boundingRect.top = emb_min_float(boundingRect.top, emb_min_float(line.start.y, line.end.y));
        boundingRect.right = emb_max_float(boundingRect.right, emb_max_float(line.start.x, line.end.x));
        boundingRect.bottom = emb_max_float(boundingRect.bottom, emb_max_float(line.start.y, line.end.y));
    }

    for (i = 0; i < p->points->length; i++) {
        EmbPointObject point;
        embArray_get(p->points, &point, i);
        boundingRect.left = emb_min_float(boundingRect.left, point.x);
        boundingRect.top = emb_min_float(boundingRect.top, point.y);
        boundingRect.right = emb_max_float(boundingRect.right, point.x);
        boundingRect.bottom = emb_max_float(boundingRect.bottom, point.y);
    }

    for (i = 0; i < p->polygons->length; i++) {
        EmbPolygonObject* polygon;
        embArray_get(p->polygons, &polygon, i);
        for (j = 0; j < polygon->pointList->length; j++) {
            EmbVector v;
            embArray_get(polygon->pointList, &v, j);
            boundingRect.left = emb_min_float(boundingRect.left, v.x);
            boundingRect.top = emb_min_float(boundingRect.top, v.y);
            boundingRect.right = emb_max_float(boundingRect.right, v.x);
            boundingRect.bottom = emb_max_float(boundingRect.bottom, v.y);
        }
    }

    for (i = 0; i < p->polylines->length; i++) {
        EmbPolylineObject* polyline;
        embArray_get(p->polylines, &polyline, i);
        for (j = 0; j < polyline->pointList->length; j++) {
            EmbVector v;
            embArray_get(polyline->pointList, &v, j);
            boundingRect.left = emb_min_float(boundingRect.left, v.x);
            boundingRect.top = emb_min_float(boundingRect.top, v.y);
            boundingRect.right = emb_max_float(boundingRect.right, v.x);
            boundingRect.bottom = emb_max_float(boundingRect.bottom, v.y);
        }
    }

    for (i = 0; i < p->rects->length; i++) {
        EmbRect rect;
        embArray_get(p->rects, &rect, i);
        /* TODO: other points */
        boundingRect.left = emb_min_float(boundingRect.left, rect.left);
        boundingRect.top = emb_min_float(boundingRect.top, rect.left);
        boundingRect.right = emb_max_float(boundingRect.right, rect.left);
        boundingRect.bottom = emb_max_float(boundingRect.bottom, rect.left);
    }

    for (i = 0; i < p->splines->length; i++) {
        embArray_get(p->splines, &bezier, i);
        /* TODO: other points */
        boundingRect.left = emb_min_float(boundingRect.left, bezier.start.x);
        boundingRect.top = emb_min_float(boundingRect.top, bezier.start.y);
        boundingRect.right = emb_max_float(boundingRect.right, bezier.start.x);
        boundingRect.bottom = emb_max_float(boundingRect.bottom, bezier.start.y);
    }

    return boundingRect;
}

/*! Flips the entire pattern (\a p) horizontally about the y-axis. */
void embPattern_flipHorizontal(EmbPattern* p)
{
    if (!p) {
        puts("ERROR: embPattern_flipHorizontal(), p==0\n");
        return;
    }
    embPattern_flip(p, 1, 0);
}

/*! Flips the entire pattern (\a p) vertically about the x-axis. */
void embPattern_flipVertical(EmbPattern* p)
{
    if (!p) {
        puts("ERROR: embPattern_flipVertical(), p==0\n");
        return;
    }
    embPattern_flip(p, 0, 1);
}

/*! Flips the entire pattern (\a p) horizontally about the x-axis if (\a horz) is true.
 *  Flips the entire pattern (\a p) vertically about the y-axis if (\a vert) is true. */
void embPattern_flip(EmbPattern* p, int horz, int vert)
{
    int i, j;
    EmbVector flip;

    if (!p) {
        puts("ERROR: embPattern_flip(), p==0\n");
        return;
    }

    flip.x = 1.0;
    flip.y = 1.0;
    if (horz) {
        flip.x = -1.0;
    }
    if (vert) {
        flip.y = -1.0;
    }

    for (i = 0; i < p->stitchList->length; i++) {
        EmbStitch st;
        embArray_get(p->stitchList, &st, i);
        st.x *= flip.x;
        st.y *= flip.y;
        embArray_get(p->stitchList, &st, i);
    }

    for (i = 0; i < p->arcs->length; i++) {
        EmbArc arc;
        embArray_get(p->arcs, &arc, i);
        embVector_component_product(arc.start, flip, &(arc.start));
        embVector_component_product(arc.mid, flip, &(arc.mid));
        embVector_component_product(arc.end, flip, &(arc.end));
        embArray_set(p->arcs, &arc, i);
    }

    for (i = 0; i < p->circles->length; i++) {
        EmbCircle circle;
        embArray_get(p->circles, &circle, i);
        embVector_component_product(circle.center, flip, &(circle.center));
        embArray_set(p->circles, &circle, i);
    }

    for (i = 0; i < p->ellipses->length; i++) {
        EmbEllipse ellipse;
        embArray_get(p->ellipses, &ellipse, i);
        embVector_component_product(ellipse.center, flip, &(ellipse.center));
        embArray_set(p->ellipses, &ellipse, i);
    }

    for (i = 0; i < p->lines->length; i++) {
        EmbLine line;
        embArray_get(p->lines, &line, j);
        embVector_component_product(line.start, flip, &(line.start));
        embVector_component_product(line.end, flip, &(line.end));
        embArray_set(p->lines, &line, j);
    }

    if (p->paths) {
        for (i = 0; i < p->paths->length; i++) {
            EmbPathObject* path;
            embArray_get(p->paths, &path, i);
            for (j = 0; j < path->pointList->length; j++) {
                EmbVector point;
                embArray_get(path->pointList, &point, j);
                embVector_component_product(point, flip, &point);
                embArray_set(path->pointList, &point, j);
            }
        }
    }

    if (p->points) {
        for (i = 0; i < p->points->length; i++) {
            EmbPointObject point;
            embArray_get(p->points, &point, i);
            point.x *= flip.x;
            point.y *= flip.y;
            embArray_set(p->points, &point, i);
        }
    }

    if (p->polygons) {
        for (i = 0; i < p->polygons->length; i++) {
            EmbPolygonObject* polygon;
            embArray_get(p->polygons, polygon, i);
            for (j = 0; j < polygon->pointList->length; j++) {
                EmbVector point;
                embArray_get(polygon->pointList, &point, j);
                embVector_component_product(point, flip, &point);
                embArray_set(polygon->pointList, &point, j);
            }
        }
    }

    if (p->polylines) {
        for (i = 0; i < p->polylines->length; i++) {
            EmbPolylineObject* polyline;
            embArray_get(p->polylines, polyline, i);
            for (j = 0; j < polyline->pointList->length; j++) {
                EmbVector point;
                embArray_get(polyline->pointList, &point, j);
                embVector_component_product(point, flip, &point);
                embArray_set(polyline->pointList, &point, j);
            }
        }
    }

    if (p->rects) {
        for (i = 0; i < p->rects->length; i++) {
            EmbRect rect;
            embArray_get(p->rects, &rect, j);
            rect.left *= flip.x;
            rect.right *= flip.x;
            rect.top *= flip.y;
            rect.bottom *= flip.y;
            embArray_set(p->rects, &rect, j);
        }
    }

    if (p->splines) {
        for (i = 0; i < p->splines->length; i++) {
            /* TODO: embPattern_flip for splines */
        }
    }
}

/* Does this need a tolerance to stop really long jumps?
 */
void embPattern_combineJumpStitches(EmbPattern* p)
{
    int jump = 0, i, j;
    EmbStitch st;

    if (!p) {
        puts("ERROR: embPattern_combineJumpStitches(), p==0\n");
        return;
    }

    j = 0;
    for (i = 0; i < p->stitchList->length; i++) {
        embArray_get(p->stitchList, &st, i);
        embArray_set(p->stitchList, &st, j);
        if (st.flags & JUMP) {
            if (jump == 0) {
                j++;
                jump = 1;
            }
        } else {
            j++;
            jump = 0;
        }
    }
    p->stitchList->length = j + 1;
}

/* TODO: The params determine the max XY movement rather than the length.
 * They need renamed or clarified further. */
void embPattern_correctForMaxStitchLength(EmbPattern* p, float maxStitchLength, float maxJumpLength)
{
    int j = 0, splits, i;
    float maxXY, maxLen;
    EmbVector st, diff, add;
    EmbArray* newList;

    if (!p) {
        puts("ERROR: embPattern_correctForMaxStitchLength(), p==0\n");
        return;
    }
    if (p->stitchList->length > 1) {
        EmbStitch stitch;
        newList = embArray_create(EMB_STITCH);
        embArray_get(p->stitchList, &stitch, 0);
        embArray_add(newList, &stitch);
        for (i = 1; i < p->stitchList->length; i++) {
            EmbStitch st1, st2;
            embArray_get(p->stitchList, &st1, i - 1);
            embArray_get(p->stitchList, &st2, i);
            st.x = st1.x;
            st.y = st1.y;
            diff.x = st2.x - st.x;
            diff.y = st2.y - st.y;
            maxXY = embVector_getLength(diff);
            if (maxXY > maxStitchLength) {
                if (st2.flags & (JUMP | TRIM))
                    maxLen = maxJumpLength;
                else
                    maxLen = maxStitchLength;

                splits = (int)ceil((float)maxXY / maxLen);

                if (splits > 1) {
                    embVector_multiply(diff, (float)(1.0 / splits), &add);

                    for (j = 1; j < splits; j++) {
                        EmbStitch s;
                        s = st1;
                        s.x += add.x * j;
                        s.y += add.y * j;
                        embArray_add(newList, &s);
                    }
                }
            }
            embArray_add(newList, &st2);
        }
        embArray_free(p->stitchList);
        p->stitchList = newList;
    }
}

void embPattern_center(EmbPattern* p)
{
    /* TODO: review this. currently not used in anywhere. Also needs to handle various design objects */
    int moveLeft, moveTop, i;
    EmbRect boundingRect;
    EmbStitch s;

    if (!p) {
        puts("ERROR: embPattern_center(), p==0\n");
        return;
    }
    boundingRect = embPattern_calcBoundingBox(p);

    moveLeft = (int)(boundingRect.left - (embRect_width(boundingRect) / 2.0));
    moveTop = (int)(boundingRect.top - (embRect_height(boundingRect) / 2.0));

    for (i = 0; i < p->stitchList->length; i++) {
        embArray_get(p->stitchList, &s, i);
        s.x -= moveLeft;
        s.y -= moveTop;
        embArray_set(p->stitchList, &s, i);
    }
}

/* TODO: Description needed. */
void embPattern_loadExternalColorFile(EmbPattern* p, const char* fileName)
{
    char *dotPos;
    char hasRead;
    char *buffer = (char*)embBuffer;

    hasRead = 0;
    strcpy(buffer, (char*)fileName);
    dotPos = buffer + strlen(buffer);
    while (*dotPos != '.') {
        dotPos--;
    }
    strcpy(dotPos, ".edr");
    hasRead = embPattern_readAuto(p, buffer);
    if (!hasRead) {
        strcpy(buffer, (char*)fileName);
        strcpy(dotPos, ".rgb");
        hasRead = embPattern_readAuto(p, buffer);
    }
    if (!hasRead) {
        strcpy(buffer, fileName);
        strcpy(dotPos, ".col");
        hasRead = embPattern_readAuto(p, buffer);
    }
    if (!hasRead) {
        strcpy(buffer, fileName);
        strcpy(dotPos, ".inf");
        hasRead = embPattern_readAuto(p, buffer);
    }
}

/*! Frees all memory allocated in the pattern (\a p). */
void embPattern_free(EmbPattern* p)
{
    embArray_free(p->stitchList);
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
}

/*! Adds a circle object to pattern (\a p) with its center at the absolute
 * position (\a cx,\a cy) with a radius of (\a r). Positive y is up.
 * Units are in millimeters. */
void embPattern_addCircleObjectAbs(EmbPattern* p, float cx, float cy, float r, int lineType, EmbColor color)
{
    EmbCircle circle;
    circle.center.x = cx;
    circle.center.y = cy;
    circle.radius = r;
    circle.lineType = 0;
    circle.color = color;

    if (!p) {
        puts("ERROR: embPattern_addCircleObjectAbs(), p==0\n");
        return;
    }
    embArray_add(p->circles, &circle);
}

/*! Adds an ellipse object to pattern (\a p) with its center at the
 * absolute position (\a cx,\a cy) with radii of (\a rx,\a ry). Positive y is up.
 * Units are in millimeters. */
void embPattern_addEllipseObjectAbs(EmbPattern* p, float cx, float cy, float rx, float ry, float rotation, int lineType, EmbColor color)
{
    EmbEllipse ellipse;
    ellipse.center.x = cx;
    ellipse.center.y = cy;
    ellipse.radius.x = rx;
    ellipse.radius.y = ry;
    ellipse.rotation = rotation;
    ellipse.lineType = lineType;
    ellipse.color = black;

    if (!p) {
        puts("ERROR: embPattern_addEllipseObjectAbs(), p==0\n");
        return;
    }
    embArray_add(p->ellipses, &ellipse);
}

/*! Adds a line object to pattern (\a p) starting at the absolute position
 * (\a x1,\a y1) and ending at the absolute position (\a x2,\a y2).
 * Positive y is up. Units are in millimeters.
 */
void embPattern_addLineObjectAbs(EmbPattern* p, float x1, float y1, float x2, float y2, int lineType, EmbColor color)
{
    EmbLine line;
    line.start.x = x1;
    line.start.y = y1;
    line.end.x = x2;
    line.end.y = y2;
    line.lineType = lineType;
    line.color = color;

    if (!p) {
        puts("ERROR: embPattern_addLineObjectAbs(), p==0\n");
        return;
    }
    embArray_add(p->lines, &line);
}

void embPattern_addPathObjectAbs(EmbPattern* p, EmbPathObject* obj)
{
    if (!p) {
        puts("ERROR: embPattern_addPathObjectAbs(), p==0\n");
        return;
    }
    if (!obj) {
        puts("ERROR: embPattern_addPathObjectAbs(), obj==0\n");
        return;
    }
    if (!obj->pointList) {
        puts("ERROR: embPattern_addPathObjectAbs(), obj->pointList is empty\n");
        return;
    }

    embArray_add(p->paths, obj);
}

/*! Adds a point object to pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
void embPattern_addPointObjectAbs(EmbPattern* p, float x, float y, int lineType, EmbColor color)
{
    EmbPointObject point;
    point.x = x;
    point.y = y;
    point.lineType = lineType;
    point.color = color;

    if (!p) {
        puts("ERROR: embPattern_addPointObjectAbs(), p==0\n");
        return;
    }
    embArray_add(p->points, &point);
}

void embPattern_addPolygonObjectAbs(EmbPattern* p, EmbPolygonObject* obj)
{
    if (!p) {
        puts("ERROR: embPattern_addPolygonObjectAbs(), p==0\n");
        return;
    }
    if (!obj) {
        puts("ERROR: embPattern_addPolygonObjectAbs(), obj==0\n");
        return;
    }
    if (!obj->pointList) {
        puts("ERROR: embPattern_addPolygonObjectAbs(), obj->pointList is empty\n");
        return;
    }

    embArray_add(p->polygons, obj);
}

void embPattern_addPolylineObjectAbs(EmbPattern* p, EmbPolylineObject* obj)
{
    if (!p) {
        puts("ERROR: embPattern_addPolylineObjectAbs(), p==0\n");
        return;
    }
    if (!obj) {
        puts("ERROR: embPattern_addPolylineObjectAbs(), obj==0\n");
        return;
    }
    if (!obj->pointList) {
        puts("ERROR: embPattern_addPolylineObjectAbs(), obj->pointList is empty\n");
        return;
    }

    embArray_add(p->polylines, obj);
}

static void embPattern_colorBlock16(EmbPattern *pattern, FILE* file)
{
    int i;

    /* write remaining colors to reach 16 */
    memset(embBuffer, 0, 16*4);

    for (i = 0; i < pattern->threads->length; i++) {
        EmbThread t;
        embArray_get(pattern->threads, &t, i);
        embColor_toStr(t.color, embBuffer+4*i);
    }

    fwrite(embBuffer, 1, 16*4, file);
}

/**
 * Adds a rectangle object to pattern (\a p) at the absolute position
 * (\a x,\a y) with a width of (\a w) and a height of (\a h).
 * Positive y is up. Units are in millimeters.
 */
void embPattern_addRectObjectAbs(EmbPattern* p, float x, float y, float w, float h, int lineType, EmbColor color)
{
    EmbRect rect;
    rect.left = x;
    rect.top = y;
    rect.right = x + w;
    rect.bottom = y + h;
    rect.lineType = 0;
    rect.color = color;

    if (!p) {
        puts("ERROR: embPattern_addRectObjectAbs(), p==0\n");
        return;
    }
    embArray_add(p->rects, &rect);
}

void embArray_resample(EmbArray *a, EmbArray *usePt)
{
    int i, j, flag;
    j = 0;
    for (i=0; i<a->length; i++) {
        embArray_get(usePt, &flag, i);
        if (flag) {
            void *data;
            embArray_get(a, data, i);
            embArray_set(a, data, j);
            j++;
        }
    }
    a->length = j;
}

int embVector_collinear(EmbVector a1, EmbVector a2, EmbVector a3, float collinearity_tolerance)
{
    EmbVector c21, c31;
    float angle;

    embVector_subtract(a2, a1, &c21);
    embVector_subtract(a3, a1, &c31);
    angle = GetAngle(c21, c31);
    return angle < collinearity_tolerance;
}

float GetRelativeX(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector c12, c32;
    embVector_subtract(a1, a2, &c12);
    embVector_subtract(a3, a2, &c32);
    return embVector_dot(c12, c32);
}

float GetRelativeY(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector c12, c32;
    embVector_subtract(a1, a2, &c12);
    embVector_subtract(a3, a2, &c32);
    return embVector_cross(c12, c32);
}

float GetAngle(EmbVector a, EmbVector b)
{
    EmbVector h;
    embVector_subtract(a, b, &h);
    return atan2(h.x, h.y);
}

void embPattern_breakIntoColorBlocks(EmbPattern *pattern)
{
#if 0
    EmbColor color;
    int oldColor, i;
    EmbArray *sa2;
    VectorStitch vs;
    sa2 = new StitchBlock();
    oldColor = pattern.StitchList[0].ColorIndex;
    color = pattern.ColorList[oldColor];
    sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
    for (i=0; i<pattern->stitches->length; i++) {
        s = pattern->stitches->stitch[i];
        if (s.ColorIndex != oldColor) {
            yield return sa2;
            sa2 = new StitchBlock();
            color = pattern.ColorList[s.ColorIndex];
            sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
            oldColor = s.ColorIndex;
        }
        vs = new VectorStitch { Xy = new Point(s.X, s.Y), Color = s.ColorIndex };
        sa2.Stitches.Add(vs);
    }
    yield return sa2;
#endif
}

int embPolygon_breakIntoSeparateObjects(EmbArray *blocks)
{
#if 0
    int i, j;
    float dx, dy, dy2, dy3;
    float previousAngle = 0.0;
    for (j=0; j<blocks->length; j++) {
        block = blocks[j];
        EmbArray *stitches = new List<VectorStitch>();
        block.Stitches[0].Type = VectorStitchType.Contour;
        block.Stitches[block.Stitches->length - 1].Type = VectorStitchType.Contour;

        for (i = 0; i < block.Stitches->length - 2; i++) { /* step 0 */
            dx = (GetRelativeX(block.Stitches[i].Xy, block.Stitches[i + 1].Xy, block.Stitches[i + 2].Xy));
            block.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
            block.Stitches[i].Angle = GetAngle(block.Stitches[i], block.Stitches[i + 1]);
            stitches.Add(block.Stitches[i].Clone());
            if (i > 0) {
                if ((block.Stitches[i].Type == VectorStitchType.Contour) && Math.Abs(block.Stitches[i].Angle - previousAngle) > (20/180*embConstantPi))
                {
                    yield return
                        new StitchBlock {
                                Stitches = stitches,
                                Angle = stitches.Average(x => x.Angle),
                                Thread = new Thread(block.Thread.Red, block.Thread.Blue, block.Thread.Green)
                            };
                    stitches = new List<VectorStitch>();
                }
            }
        }

        /* step 1 */
        for (i = 1; i < pattern->stitches->length - 3; i++) {
            if (pattern->stitches->stitch[i + 1].type == VectorStitchType.Contour) {
                dy = GetRelativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY);
                dy2 = GetRelativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY);
                dy3 = GetRelativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY);
                /* if(dy) */
                if (sa.Stitches[i - 1].Type == VectorStitchType.Run || sa.Stitches[i + 1].Type == VectorStitchType.Run)
                {
                    sa.Stitches[i].Type = VectorStitchType.Tatami;
                }
                else {
                    sa.Stitches[i].Type = VectorStitchType.Satin;
                }
            }
        }
    }
#endif
    return 1;
}

int FindOutline(EmbArray *stitchData, EmbArray *result)
{
    int currColorIndex = 0, oddEven, i;
    float dx, dy, dy2, dy3;
#if 0
    EmbArray *pOdd = new List<Point>();
    EmbArray *pEven = new List<Point>();
    foreach (StitchBlock sa in stitchData) {
        if (sa.Stitches->length > 0) {
            sa.Stitches[0].Type = VectorStitchType.Contour;
            sa.Stitches[sa.Stitches->length - 1].Type = VectorStitchType.Contour;
            /* step 0 */
            for (i = 0; i < sa.Stitches->length - 2; i++) {
                dx = (GetRelativeX(sa.Stitches[i].Xy, sa.Stitches[i + 1].Xy, sa.Stitches[i + 2].Xy));
                sa.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
                sa.Stitches[i].Angle = GetAngle(sa.Stitches[i], sa.Stitches[i + 1]);
            }
            /* step 1 */
            for (i = 1; i < sa.Stitches->length - 3; i++) {
                if (sa.Stitches[i + 1].Type == VectorStitchType.Contour) {
                    dy = GetRelativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY);
                    dy2 = GetRelativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY);
                    dy3 = GetRelativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY);
                    /* if(dy) */
                    if (sa.Stitches[i - 1].Type == VectorStitchType.Run || sa.Stitches[i + 1].Type == VectorStitchType.Run)
                    {
                        sa.Stitches[i].Type = VectorStitchType.Tatami;
                    }
                    else {
                        sa.Stitches[i].Type = VectorStitchType.Satin;
                    }
                }
            }
        }


        oddEven = 0;
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
        EmbArray *so = new StitchObject { SideOne = pEven, SideTwo = pOdd, ColorIndex = currColorIndex };
        yield return so;
        pEven = new List<Point>();
        pOdd = new List<Point>();
        /* break; */
    }
#endif
    return 1;
}

int DrawGraphics(EmbPattern p)
{
#if 0
    var stitchData = BreakIntoColorBlocks(p);

    /*
    var outBlock = new List<StitchBlock>(BreakIntoSeparateObjects(stitchData));
    foreach(var block in stitchData) {
        foreach (var stitch in block.Stitches) {
            if(stitch.Angle != 0) {
                int aaa = 1;
            }
        }
    }
    */
    /* var xxxxx = outBlock; */
    EmbArray *objectsFound = FindOutline(stitchData);
    EmbArray *outPattern = new Pattern();
    outPattern.AddColor(new Thread(255, 0, 0, "none", "None"));
    int colorIndex = outPattern.ColorList->length - 1;

    foreach (StitchObject stitchObject in objectsFound) {
        if (stitchObject.SideOne->length > 1 && stitchObject.SideTwo->length > 1) {
            outPattern.AddColor(new Thread((byte) (rand()%256), (byte) (rand()%256), (byte) (rand()%256),
                                           "none", "None"));
            colorIndex++;
            outPattern.AddStitchRelative(0, 0, StitchTypes.Stop);
            var points = stitchObject.Generate2(75);
            foreach (var point in points)
            {
                outPattern.AddStitchAbsolute(point.X, point.Y, StitchTypes.Normal);
            }
            /*
            break;
            Point t;
            StitchObject stitchObject = objectsFound[1];
            if (stitchObject.SideOne->length > 0) {
                outPattern.StitchList.Add(new Stitch(stitchObject.SideOne[0].x, stitchObject.SideOne[0].y,
                                                     StitchType.Jump, colorIndex));
            }
            foreach (t in stitchObject.SideOne) {
                outPattern.StitchList.Add(new Stitch(t.x, t.y, StitchType.Normal, colorIndex));
            }
            foreach (t in stitchObject.SideTwo) {
                outPattern.StitchList.Add(new Stitch(t.x, t.y, StitchType.Normal, colorIndex));
            }
            break;
            */
        }
    }
    outPattern.AddStitchRelative(0, 0, StitchTypes.End);
    /* return (SimplifyOutline(outPattern)); */
#endif
    return 0;
}

int SimplifyOutline(EmbPattern *pattern, EmbPattern *patternOut)
{
    int color;
#if 0
    var v = new Vertices();
    v.AddRange(pattern.StitchList.Select(point => new Vector2(point.X, point.Y)));
    output = SimplifyTools.DouglasPeuckerSimplify(v, 10);
    patternOut = embPattern_create();
    for (color=0; color<pattern->threads->length; color++) {
        
        embPattern_addThread(patternOut, pattern->threads->thread[color]);
    }

    foreach (var vertex in output) {
        patternOut.AddStitchAbsolute(vertex.X, vertex.Y, StitchTypes.Normal);
    }
#endif
    return 1;
}


/**
 * Removes all collinear points on the polygon. Has a default bias of 0.
 *
 * @param vertices The polygon that needs simplification.
 * @param collinearityTolerence How close a point can be to collinear before it is removed.
 * @returns A simplified polygon in the same EmbArray.
 */
int embPolygon_collinearSimplify(EmbArray *vertices, float collinearityTolerance)
{
    int i, prevId, nextId;
    EmbVector prev, current, next;
    EmbArray *usePt;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->length < 3) {
        return 0;
    }

    usePt = embArray_create(EMB_FLAG);

    for (i = 0; i < vertices->length; i++) {
        int flag;
        prevId = (i-1+vertices->length) % vertices->length;
        nextId = (i+1) % vertices->length;

        embArray_get(vertices, &prev, prevId);
        embArray_get(vertices, &current, i);
        embArray_get(vertices, &next, nextId);

        flag = 1;
        if (embVector_collinear(prev, current, next, collinearityTolerance)) {
            flag = 0;
        }
        embArray_add(usePt, &flag);
    }

    embArray_resample(vertices, usePt);
    embArray_free(usePt);
    return 1;
}

/**
 * Ramer-Douglas-Peucker polygon simplification algorithm. This is the general recursive version that does not use the
 * speed-up technique by using the Melkman convex hull.
 * If you pass in 0, it will remove all collinear points
 */
int embPolygon_DouglasPeuckerSimplify(EmbArray *vertices, float distanceTolerance)
{
    int i;
    EmbArray *_usePt;

    _usePt = embArray_create(EMB_FLAG);
    for (i = 0; i < vertices->length; i++) {
        int flag = 1;
        embArray_add(_usePt, &flag);
    }
    embPolygon_simplifySection(vertices, _usePt, 0, vertices->length - 1, distanceTolerance);
    embArray_resample(vertices, _usePt);
    embArray_free(_usePt);
    return 1;
}

void embPolygon_simplifySection(EmbArray *vertices, EmbArray *_usePt, int i, int j, float distanceTolerance)
{
    int k, maxIndex;
    EmbVector a, b, c;
    float maxDistance, distance;
    if ((i + 1) == j)
        return;

    embArray_get(vertices, &a, i);
    embArray_get(vertices, &b, j);
    maxDistance = -1.0;
    maxIndex = i;
    for (k = i + 1; k < j; k++) {
        embArray_get(vertices, &c, k);
        distance = embVector_distancePointLine(c, a, b);

        if (distance > maxDistance) {
            maxDistance = distance;
            maxIndex = k;
        }
    }
    if (maxDistance <= distanceTolerance) {
        for (k = i + 1; k < j; k++) {
            int flag = 0;
            embArray_set(_usePt, &flag, k);
        }
    }
    else {
        embPolygon_simplifySection(vertices, _usePt, i, maxIndex, distanceTolerance);
        embPolygon_simplifySection(vertices, _usePt, maxIndex, j, distanceTolerance);
    }
}

/**
 * Find the distance from (\a p) to the line from (\a a) to (\a b) by
 * finding the length of the normal from ab (extended to an infinite line)
 * to p.
 */
float embVector_distancePointLine(EmbVector p, EmbVector a, EmbVector b)
{
    float r, curve2, s, tolerance;
    EmbVector pa, ba;

    tolerance = 0.00001;
    embVector_subtract(b, a, &ba);
    /* if start == end, then use point-to-point distance */
    if (fabs(ba.x) < tolerance && fabs(ba.y) < tolerance) {
        return embVector_distance(p, a);
    }

    /* otherwise use comp.graphics.algorithms Frequently Asked Questions method */
    /*(1)     	      AC dot AB
                r =   ---------
                      ||AB||^2

                r has the following meaning:
                r=0 Point = A
                r=1 Point = B
                r<0 Point is on the backward extension of AB
                r>1 Point is on the forward extension of AB
                0<r<1 Point is interior to AB
    */

    embVector_subtract(p, a, &pa);
    curve2 = embVector_dot(ba, ba);
    r = embVector_dot(pa, ba) / curve2;

    if (r <= 0.0) return embVector_distance(p, a);
    if (r >= 1.0) return embVector_distance(p, b);

    /*(2)
                    (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)
                s = -----------------------------
                                Curve^2

                Then the distance from C to Point = |s|*Curve.
    */

    s = (pa.x * ba.y - pa.y * ba.x) / curve2;

    return fabs(s) * sqrt(curve2);
}

/* From physics2d.net */
int embPolygon_reduceByArea(EmbArray *vertices, EmbArray *result, float areaTolerance)
{
    float old1, old2, new1;
    int index;
    EmbVector v1, v2, v3;
    if (vertices->length <= 3) {
        return 0;
    }

    if (areaTolerance < 0) {
        puts("areaTolerence must be greater than or equal to zero.");
        return 0;
    }

    result = embArray_create(EMB_VECTOR);
    embArray_get(vertices, &v1, vertices->length - 2); 
    embArray_get(vertices, &v2, vertices->length - 1); 
    areaTolerance *= 2;
    for (index = 0; index < vertices->length; ++index, v2 = v3) {
        if (index == vertices->length - 1) {
            if (result->length == 0) {
                puts("The areaTolerance is too high.");
                return 0;
            }
            embArray_get(vertices, &v3, 0); 
        }
        else {
            embArray_get(vertices, &v3, index); 
        }
        old1 = embVector_cross(v1, v2);
        old2 = embVector_cross(v2, v3);
        new1 = embVector_cross(v1, v3);
        if (fabs(new1 - (old1 + old2)) > areaTolerance) {
            embArray_add(result, &v2);
            v1 = v2;
        }
    }
    return 1;
}

/**
 * From Eric Jordan's convex decomposition library
 * Merges all parallel edges in the list of vertices
 */
void MergeParallelEdges(EmbArray *vertices, float tolerance)
{
    int lower, upper, i, newNVertices;
    EmbVector d0, d1, a, b, c;
    float norm0, norm1, cross, dot;
    EmbArray *usePoints;
    if (vertices->length <= 3) {
        return; /* Can't do anything useful here to a triangle */
    }

    usePoints = embArray_create(EMB_FLAG);
    newNVertices = vertices->length;

    /* Gather points to process */
    for (i = 0; i < vertices->length; ++i) {
        lower = (i+vertices->length-1) % vertices->length;
        upper = (i+1)% vertices->length;

        embArray_get(vertices, &a, lower);
        embArray_get(vertices, &b, i);
        embArray_get(vertices, &c, upper);

        embVector_subtract(b, a, &d0);
        embVector_subtract(c, b, &d1);
        norm0 = embVector_getLength(d0);
        norm1 = embVector_getLength(d1);

        int flag = 0;
        if (!(norm0 > 0.0f && norm1 > 0.0f) && newNVertices > 3) {
            /* Merge identical points */
            embArray_add(usePoints, &flag);
            --newNVertices;
            continue;
        }

        embVector_multiply(d0, 1.0/norm0, &d0);
        embVector_multiply(d1, 1.0/norm1, &d1);
        cross = embVector_cross(d0, d1);
        dot = embVector_dot(d0, d1);

        if (fabs(cross) < tolerance && dot > 0 && newNVertices > 3) {
            flag = 0;
            --newNVertices;
        }
        else {
            flag = 1;
        }
        embArray_add(usePoints, &flag);
    }

    if (newNVertices == vertices->length || newNVertices == 0) {
        embArray_free(usePoints);
        return;
    }

    embArray_resample(vertices, usePoints);
    embArray_free(usePoints);
}

/* Reduces the polygon by distance. */
int embPolygon_reduceByDistance(EmbArray *vertices, float distance)
{
    int i, nextId;
    float vdist;
    EmbArray *usePoints;
    EmbVector a, b;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->length < 3) return 0;

    usePoints = embArray_create(EMB_FLAG);

    for (i = 0; i < vertices->length; i++) {
        nextId = (i + 1) % vertices->length;

        embArray_get(vertices, &a, i);
        embArray_get(vertices, &b, nextId);
        vdist = embVector_distance(a, b);

        /* If they are closer than the distance, do not use the i-th point */
        int flag;
        if (vdist < distance) {
            flag = 0;
        }
        else {
            flag = 1;
        }
        embArray_add(usePoints, &flag);
    }

    embArray_resample(vertices, usePoints);
    embArray_free(usePoints);
    return 1;
}

/* Reduces the polygon by removing the Nth vertex in the vertices list. */
int embPolygon_reduceByNth(EmbArray* vertices, int nth)
{
    int i;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->length < 3)
        return 0;

    /* Vertex is not present */
    if (nth >= vertices->length)
        return 0;

    /* This isn't an array of vectors. */
    if (vertices->type != EMB_VECTOR)
        return 0;

    /* Shift everything left one place then reduce the count. */
    for (i = nth; i < vertices->length - 1; i++) {
        EmbVector v;
        embArray_get(vertices, &v, i+1);
        embArray_set(vertices, &v, i);
    }
    vertices->length--;

    /* success, trust the data in vertices */
    return 1;
}

void embSatinOutline_generateSatinOutline(EmbArray* lines, float thickness, EmbSatinOutline* result)
{
    int i, j;
    EmbSatinOutline outline;
    EmbVector v1, temp;
    EmbLine line, line1, line2;
    float halfThickness = thickness / 2.0;
    int intermediateOutlineCount = 2 * lines->length - 2;
    outline.side1 = embArray_create(EMB_VECTOR);
    if (!outline.side1) {
        puts("ERROR: embSatinOutline_generateSatinOutline() embArray_create()\n");
        return;
    }
    outline.side2 = embArray_create(EMB_VECTOR);
    if (!outline.side2) {
        puts("ERROR: embSatinOutline_generateSatinOutline() embArray_create()\n");
        return;
    }

    for (i = 1; i < lines->length; i++) {
        j = (i - 1) * 2;
        embArray_get(lines, &(line.start), j - 1);
        embArray_get(lines, &(line.end), j);

        embLine_normalVector(line, &v1, 1);

        embVector_multiply(v1, halfThickness, &temp);
        embVector_add(temp, line.start, &temp);
        embArray_add(outline.side1, &temp);
        embVector_add(temp, line.end, &temp);
        embArray_add(outline.side1, &temp);

        embVector_multiply(v1, -halfThickness, &temp);
        embVector_add(temp, line.start, &temp);
        embArray_add(outline.side2, &temp);
        embVector_add(temp, line.end, &temp);
        embArray_add(outline.side2, &temp);
    }

    if (!result) {
        puts("ERROR: embSatinOutline_generateSatinOutline(), result==0\n");
        return;
    }
    result->side1 = embArray_create(EMB_VECTOR);
    result->side2 = embArray_create(EMB_VECTOR);

    EmbVector a;
    embArray_get(outline.side1, &a, 0);
    embArray_add(result->side1, &a);
    embArray_get(outline.side2, &a, 0);
    embArray_add(result->side2, &a);

    for (i = 3; i < intermediateOutlineCount; i += 2) {
        embArray_get(outline.side1, &(line1.start), i - 3);
        embArray_get(outline.side1, &(line1.end), i - 2);
        embArray_get(outline.side1, &(line2.start), i - 1);
        embArray_get(outline.side1, &(line2.end), i);
        embLine_intersectionPoint(line1, line2, &temp);
        embArray_add(result->side1, &temp);

        embArray_get(outline.side2, &(line1.start), i - 3);
        embArray_get(outline.side2, &(line1.end), i - 2);
        embArray_get(outline.side2, &(line2.start), i - 1);
        embArray_get(outline.side2, &(line2.end), i);
        embLine_intersectionPoint(line1, line2, &temp);
        embArray_add(result->side2, &temp);
    }

    embArray_get(outline.side1, &a, 2*lines->length - 3);
    embArray_add(result->side1, &a);
    embArray_get(outline.side2, &a, 2*lines->length - 3);
    embArray_add(result->side2, &a);
    result->length = lines->length;
}

EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, float density)
{
    int i, j, numberOfSteps;
    EmbVector currTop, currBottom, topDiff, bottomDiff, midDiff;
    EmbVector midLeft, midRight, topStep, bottomStep;
    EmbVector a, b, c;
    EmbArray* stitches = 0;
    float midLength;

    if (!result) {
        puts("ERROR: embSatinOutline_renderStitches(), result==0\n");
        return 0;
    }

    if (result->length > 0) {
        for (j = 0; j < result->length - 1; j++) {
            embArray_get(result->side1, &a, j + 1);
            embArray_get(result->side1, &b, j);
            embVector_subtract(a, b, &topDiff);
            embArray_get(result->side2, &a, j + 1);
            embArray_get(result->side2, &b, j);
            embVector_subtract(a, b, &bottomDiff);

            embArray_get(result->side1, &a, j);
            embArray_get(result->side2, &b, j);
            embVector_average(a, b, &midLeft);
            embArray_get(result->side1, &a, j + 1);
            embArray_get(result->side2, &b, j + 1);
            embVector_average(a, b, &midRight);

            embVector_subtract(midLeft, midRight, &midDiff);
            midLength = embVector_getLength(midDiff);

            numberOfSteps = (int)(midLength * density / 200);
            embVector_multiply(topDiff, 1.0 / numberOfSteps, &topStep);
            embVector_multiply(bottomDiff, 1.0 / numberOfSteps, &bottomStep);
            embArray_get(result->side1, &currTop, j);
            embArray_get(result->side2, &currBottom, j);

            for (i = 0; i < numberOfSteps; i++) {
                if (!stitches) {
                    stitches = embArray_create(EMB_VECTOR);
                }
                embArray_add(stitches, &currTop);
                embArray_add(stitches, &currBottom);
                embVector_add(currTop, topStep, &currTop);
                embVector_add(currBottom, bottomStep, &currBottom);
            }
        }
        embArray_add(stitches, &currTop);
        embArray_add(stitches, &currBottom);
    }
    return stitches;
}

static unsigned int readFullSector(FILE* file, unsigned int* numberOfDifatEntriesStillToRead);
static void CompoundFileDirectoryEntry(bcf_directory_entry *dir, FILE* file);
static void readNextSector(FILE* file);

/*! Constant representing the number of Double Indirect FAT entries in a single header */
static const unsigned int NumberOfDifatEntriesInHeader = 109;
static const unsigned int sizeOfFatEntry = sizeof(unsigned int);
static const unsigned int sizeOfDifatEntry = 4;
static const unsigned int sizeOfChainingEntryAtEndOfDifatSector = 4;
static const unsigned int sizeOfDirectoryEntry = 128;
/* static const int supportedMinorVersion = 0x003E;
static const int littleEndianByteOrderMark = 0xFFFE; */

int embPattern_write(EmbPattern* pattern, const char* fileName, int format)
{
    FILE* file;
    int r;

    if (!fileName) {
        printf("ERROR: %s(), fileName==0\n", fileName);
        return 0;
    }

    if (!pattern->stitchList->length) {
        puts("error_pattern_no_stitches");
        return 0;
    }

    /* Check for an END stitch and add one if it is not present */
    EmbStitch st;
    embArray_get(pattern->stitchList, &st, pattern->stitchList->length - 1);
    if (st.flags != END) {
        embPattern_addStitchRel(pattern, 0, 0, END, 1);
    }

    file = embFile_open(fileName, "wb", 0);
    if (!file) {
        puts("error_pattern_open_file");
        return 0;    
    }

    r = 0;
    switch (format) {
    case EMB_FORMAT_100:
        r = write100(pattern, file, fileName);
        break;
    case EMB_FORMAT_10O:
        r = write10o(pattern, file, fileName);
        break;
    case EMB_FORMAT_ART:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_BMC:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_BRO:
        r = writeBro(pattern, file, fileName);
        break;
    case EMB_FORMAT_CND:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_COL:
        r = writeCol(pattern, file, fileName);
        break;
    case EMB_FORMAT_CSD:
        r = writeCsd(pattern, file, fileName);
        break;
    case EMB_FORMAT_CSV:
        r = writeCsv(pattern, file, fileName);
        break;
    case EMB_FORMAT_DAT:
        r = writeDat(pattern, file, fileName);
        break;
    case EMB_FORMAT_DEM:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_DSB:
        r = writeDsb(pattern, file, fileName);
        break;
    case EMB_FORMAT_DST:
        r = writeDst(pattern, file, fileName);
        break;
    case EMB_FORMAT_DSZ:
        r = writeDsz(pattern, file, fileName);
        break;
    case EMB_FORMAT_DXF:
        r = writeDxf(pattern, file, fileName);
        break;
    case EMB_FORMAT_EDR:
        r = writeEdr(pattern, file, fileName);
        break;
    case EMB_FORMAT_EMD:
        r = writeEmd(pattern, file, fileName);
        break;
    case EMB_FORMAT_EXP:
        r = writeExp(pattern, file, fileName);
        break;
    case EMB_FORMAT_EXY:
        r = writeExy(pattern, file, fileName);
        break;
    case EMB_FORMAT_EYS:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_FXY:
        r = writeFxy(pattern, file, fileName);
        break;
    case EMB_FORMAT_GC:
        /* Smoothie G-Code */
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_GNC:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_GT: 
        r = writeGt(pattern, file, fileName);
        break;
    case EMB_FORMAT_HUS:
        r = writeHus(pattern, file, fileName);
        break;
    case EMB_FORMAT_INB:
        r = writeInb(pattern, file, fileName);
        break;
    case EMB_FORMAT_INF:
        r = writeInf(pattern, file, fileName);
        break;
    case EMB_FORMAT_JEF:
        r = writeJef(pattern, file, fileName);
        break;
    case EMB_FORMAT_KSM:
        r = writeKsm(pattern, file, fileName);
        break;
    case EMB_FORMAT_MAX:
        r = writeMax(pattern, file, fileName);
        break;
    case EMB_FORMAT_MIT:
        r = writeMit(pattern, file, fileName);
        break;
    case EMB_FORMAT_NEW:
        r = writeNew(pattern, file, fileName);
        break;
    case EMB_FORMAT_OFM:
        r = writeOfm(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCD:
        r = writePcd(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCM:
        r = writePcm(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCQ:
        r = writePcq(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCS:
        r = writePcs(pattern, file, fileName);
        break;
    case EMB_FORMAT_PEC:
        r = writePec(pattern, file, fileName);
        break;
    case EMB_FORMAT_PEL:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_PEM:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_PES:
        r = writePes(pattern, file, fileName);
        break;
    case EMB_FORMAT_PHB:
        r = writePhb(pattern, file, fileName);
        break;
    case EMB_FORMAT_PHC:
        r = writePhc(pattern, file, fileName);
        break;
    case EMB_FORMAT_PLT:
        r = writePlt(pattern, file, fileName);
        break;
    case EMB_FORMAT_RGB:
        r = writeRgb(pattern, file, fileName);
        break;
    case EMB_FORMAT_SEW:
        r = writeSew(pattern, file, fileName);
        break;
    case EMB_FORMAT_SHV:
        r = writeShv(pattern, file, fileName);
        break;
    case EMB_FORMAT_SST:
        r = writeSst(pattern, file, fileName);
        break;
    case EMB_FORMAT_STX:
        r = writeStx(pattern, file, fileName);
        break;
    case EMB_FORMAT_SVG:
        r = writeSvg(pattern, file, fileName);
        break;
    case EMB_FORMAT_T01:
        r = writeT01(pattern, file, fileName);
        break;
    case EMB_FORMAT_T09:
        r = writeT09(pattern, file, fileName);
        break;
    case EMB_FORMAT_TAP:
        r = writeTap(pattern, file, fileName);
        break;
    case EMB_FORMAT_THR:
        r = writeThr(pattern, file, fileName);
        break;
    case EMB_FORMAT_TXT:
        r = writeTxt(pattern, file, fileName);
        break;
    case EMB_FORMAT_U00:
        r = writeU00(pattern, file, fileName);
        break;
    case EMB_FORMAT_U01:
        r = writeU01(pattern, file, fileName);
        break;
    case EMB_FORMAT_VIP:
        r = writeVip(pattern, file, fileName);
        break;
    case EMB_FORMAT_VP3:
        r = writeVp3(pattern, file, fileName);
        break;
    case EMB_FORMAT_XXX:
        r = writeXxx(pattern, file, fileName);
        break;
    case EMB_FORMAT_ZSK:
        r = writeZsk(pattern, file, fileName);
        break;
    default:
        puts("Emb format not recognised.");
        break;
    }

    if (!r) {
        return r;
    }

    fclose(file);
    return 0;
}

int embPattern_read(EmbPattern* pattern, const char* fileName, int format)
{
    FILE* file;
    int r;

    if (!pattern) {
        puts("ERROR: embPattern_read(), pattern==0\n");
        return 0;
    }
    if (!fileName) {
        puts("ERROR: embPattern_read(), fileName==0\n");
        return 0;
    }

    file = embFile_open(fileName, "rb", 0);
    if (!file) {
        puts("ERROR: embPattern_read(), failed to open file\n");
        return 0;
    }

    r = 0;
    switch (format) {
    case EMB_FORMAT_100:
        r = read100(pattern, file, fileName);
        break;
    case EMB_FORMAT_10O:
        r = read10o(pattern, file, fileName);
        break;
    case EMB_FORMAT_ART:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_BMC:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_BRO:
        r = readBro(pattern, file, fileName);
        break;
    case EMB_FORMAT_CND:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_COL:
        r = readCol(pattern, file, fileName);
        break;
    case EMB_FORMAT_CSD:
        r = readCsd(pattern, file, fileName);
        break;
    case EMB_FORMAT_CSV:
        r = readCsv(pattern, file, fileName);
        break;
    case EMB_FORMAT_DAT:
        r = readDat(pattern, file, fileName);
        break;
    case EMB_FORMAT_DEM:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_DSB:
        r = readDsb(pattern, file, fileName);
        break;
    case EMB_FORMAT_DST:
        r = readDst(pattern, file, fileName);
        break;
    case EMB_FORMAT_DSZ:
        r = readDsz(pattern, file, fileName);
        break;
    case EMB_FORMAT_DXF:
        r = readDxf(pattern, file, fileName);
        break;
    case EMB_FORMAT_EDR:
        r = readEdr(pattern, file, fileName);
        break;
    case EMB_FORMAT_EMD:
        r = readEmd(pattern, file, fileName);
        break;
    case EMB_FORMAT_EXP:
        r = readExp(pattern, file, fileName);
        break;
    case EMB_FORMAT_EXY:
        r = readExy(pattern, file, fileName);
        break;
    case EMB_FORMAT_EYS:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_FXY:
        r = readFxy(pattern, file, fileName);
        break;
    case EMB_FORMAT_GC:
        /* Smoothie G-Code */
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_GNC:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_GT:
        r = readGt(pattern, file, fileName);
        break;
    case EMB_FORMAT_HUS:
        r = readHus(pattern, file, fileName);
        break;
    case EMB_FORMAT_INB:
        r = readInb(pattern, file, fileName);
        break;
    case EMB_FORMAT_INF:
        r = readInf(pattern, file, fileName);
        break;
    case EMB_FORMAT_JEF:
        r = readJef(pattern, file, fileName);
        break;
    case EMB_FORMAT_KSM:
        r = readKsm(pattern, file, fileName);
        break;
    case EMB_FORMAT_MAX:
        r = readMax(pattern, file, fileName);
        break;
    case EMB_FORMAT_MIT:
        r = readMit(pattern, file, fileName);
        break;
    case EMB_FORMAT_NEW:
        r = readNew(pattern, file, fileName);
        break;
    case EMB_FORMAT_OFM:
        r = readOfm(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCD:
        r = readPcd(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCM:
        r = readPcm(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCQ:
        r = readPcq(pattern, file, fileName);
        break;
    case EMB_FORMAT_PCS:
        r = readPcs(pattern, file, fileName);
        break;
    case EMB_FORMAT_PEC:
        r = readPec(pattern, file, fileName);
        break;
    case EMB_FORMAT_PEL:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_PEM:
        puts("error_format_not_supported");
        break;
    case EMB_FORMAT_PES:
        r = readPes(pattern, file, fileName);
        break;
    case EMB_FORMAT_PHB:
        r = readPhb(pattern, file, fileName);
        break;
    case EMB_FORMAT_PHC:
        r = readPhc(pattern, file, fileName);
        break;
    case EMB_FORMAT_PLT:
        r = readPlt(pattern, file, fileName);
        break;
    case EMB_FORMAT_RGB:
        r = readRgb(pattern, file, fileName);
        break;
    case EMB_FORMAT_SEW:
        r = readSew(pattern, file, fileName);
        break;
    case EMB_FORMAT_SHV:
        r = readShv(pattern, file, fileName);
        break;
    case EMB_FORMAT_SST:
        r = readSst(pattern, file, fileName);
        break;
    case EMB_FORMAT_STX:
        r = readStx(pattern, file, fileName);
        break;
    case EMB_FORMAT_SVG:
        r = readSvg(pattern, file, fileName);
        break;
    case EMB_FORMAT_T01:
        r = readT01(pattern, file, fileName);
        break;
    case EMB_FORMAT_T09:
        r = readT09(pattern, file, fileName);
        break;
    case EMB_FORMAT_TAP:
        r = readTap(pattern, file, fileName);
        break;
    case EMB_FORMAT_THR:
        r = readThr(pattern, file, fileName);
        break;
    case EMB_FORMAT_TXT:
        r = readTxt(pattern, file, fileName);
        break;
    case EMB_FORMAT_U00:
        r = readU00(pattern, file, fileName);
        break;
    case EMB_FORMAT_U01:
        r = readU01(pattern, file, fileName);
        break;
    case EMB_FORMAT_VIP:
        r = readVip(pattern, file, fileName);
        break;
    case EMB_FORMAT_VP3:
        r = readVp3(pattern, file, fileName);
        break;
    case EMB_FORMAT_XXX:
        r = readXxx(pattern, file, fileName);
        break;
    case EMB_FORMAT_ZSK:
        r = readZsk(pattern, file, fileName);
        break;
    default:
        puts("Emb format not recognised.");
        break;
    }

    if (!r) {
        return r;
    }

    fclose(file);

    /* Check for an END stitch and add one if it is not present */
    EmbStitch st;
    embArray_get(pattern->stitchList, &st, pattern->stitchList->length - 1);
    if (st.flags != END) {
        embPattern_addStitchRel(pattern, 0, 0, END, 1);
    }

    return 1;
}

/**
 * TODO: documentation.
 */
FILE* embFile_open(const char* fileName, const char* mode, int optional)
{
    FILE* oFile;
    oFile = fopen(fileName, mode);

    if (!oFile) {
        if (!optional) {
            printf("ERROR: Cannot open the fileName (%s) in the given mode (%s).", fileName, mode);
        }
        return 0;
    }
    return oFile;
}

/**
 * TODO: documentation.
 * ISSUE: the last line may get cut off in certain cases.
 * ISSUE: how are blank lines dealt with?
 */
static int embFile_readline(FILE* file, char* line, int maxLength)
{
    int i, pass;
    char c;
    pass = 1;
    for (i = 0; i < maxLength - 1; i++) {
        if (!fread(&c, 1, 1, file)) {
            pass = 0;
            break;
        }
        if (c == '\r') {
            if (!fread(&c, 1, 1, file)) {
                pass = 0;
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
    return pass;
}

/**
 * Pad the FILE* file with n bytes all with value c.
 */
void embFile_pad(FILE* file, char c, int n)
{
    int i;
    for (i=0; i<n; i++) {
        fwrite(&c, 1, 1, file);
    }
}

/**
 * Copy a block of bytes from FILE* in to FILE* out, if the length argument
 * n is 0 then use null termination (i.e. a c string) otherwise copy that many
 * bytes.
 */
void embFile_copy(FILE* in, int offset, FILE* out, int n)
{
    fseek(in, offset, SEEK_SET);
    if (n==0) {
        char c = 1;
        while (c) {
            fread(&c, 1, 1, in);
            fwrite(&c, 1, 1, out);
        }
    }
    else {
        char c;
        int i;
        for (i=0; i<n; i++) {
            fread(&c, 1, 1, in);
            fwrite(&c, 1, 1, out);
        }
    }
}

bcf_file BcfFile;

/**
 * TODO: documentation.
 */
static int seekToSector(FILE* file, const unsigned int sector)
{
    unsigned int offset = (sector + 1) * BcfFile.sectorSize;
    return fseek(file, offset, SEEK_SET);
}

/**
 * TODO: documentation.
 */
int bcfFile_read(FILE* file)
{
    unsigned int i, numberOfDirectoryEntriesPerSector, directorySectorToReadFrom, fatSectors;

    fread(BcfFile.signature, 1, 8, file);
    fread(BcfFile.CLSID, 1, 16, file);
    embFile_readInt(file, &(BcfFile.minorVersion), 2);
    embFile_readInt(file, &(BcfFile.majorVersion), 2);
    embFile_readInt(file, &(BcfFile.byteOrder), 2);
    embFile_readInt(file, &(BcfFile.sectorShift), 2);
    embFile_readInt(file, &(BcfFile.miniSectorShift), 2);
    embFile_readInt(file, &(BcfFile.reserved1), 2);
    embFile_readInt(file, &(BcfFile.reserved2), 4);
    embFile_readInt(file, &(BcfFile.numberOfDirectorySectors), 4);
    embFile_readInt(file, &(BcfFile.numberOfFATSectors), 4);
    embFile_readInt(file, &(BcfFile.firstDirectorySectorLocation), 4);
    embFile_readInt(file, &(BcfFile.transactionSignatureNumber), 4);
    embFile_readInt(file, &(BcfFile.miniStreamCutoffSize), 4);
    embFile_readInt(file, &(BcfFile.firstMiniFATSectorLocation), 4);
    embFile_readInt(file, &(BcfFile.numberOfMiniFatSectors), 4);
    embFile_readInt(file, &(BcfFile.firstDifatSectorLocation), 4);
    embFile_readInt(file, &(BcfFile.numberOfDifatSectors), 4);

    /* version 3 uses 512 byte */
    if (BcfFile.majorVersion == 3) {
        BcfFile.sectorSize = 512;
    }
    BcfFile.sectorSize = 4096;

    if (!string_equal(BcfFile.signature, "\xd0\xcf\x11\xe0\xa1\xb1\x1a\xe1")) {
        puts("Failed to parse header\n");
        puts("bad header signature\n");
        return 0;
    }

    BcfFile.fatSectorCount = emb_min_int(BcfFile.numberOfFATSectors, NumberOfDifatEntriesInHeader);

    for (i = 0; i < BcfFile.fatSectorCount; i++) {
        embFile_readInt(file, BcfFile.fatSectorEntries + i, 4);
    }

    for (i = fatSectors; i < NumberOfDifatEntriesInHeader; ++i) {
        unsigned int sectorRef;
        embFile_readInt(file, &sectorRef, 4);
        if (sectorRef != CompoundFileSector_FreeSector) {
            puts("ERROR: bcf_difat_create(), Unexpected sector value\n");
            /* TODO " %x at DIFAT[%d]\n", sectorRef, i); */
        }
    }

    /* parse DIFAT sectors */
    if (BcfFile.sectorSize > sizeOfChainingEntryAtEndOfDifatSector) {
        unsigned int numberOfDifatEntriesStillToRead = BcfFile.numberOfFATSectors - NumberOfDifatEntriesInHeader;
        unsigned int difatSectorNumber = BcfFile.firstDifatSectorLocation;
        while ((difatSectorNumber != CompoundFileSector_EndOfChain) && (numberOfDifatEntriesStillToRead > 0)) {
            seekToSector(file, difatSectorNumber);
            difatSectorNumber = readFullSector(file, &numberOfDifatEntriesStillToRead);
        }
    }

    BcfFile.numberOfEntriesInFatSector = BcfFile.sectorSize / sizeOfFatEntry;
    BcfFile.fatEntryCount = 0;
    for (i = 0; i < BcfFile.numberOfFATSectors; ++i) {
        unsigned int j, fatEntries_current, newSize;
        unsigned int fatSectorNumber = BcfFile.fatSectorEntries[i];
        seekToSector(file, fatSectorNumber);

        /* load fat from sector */
        fatEntries_current = BcfFile.fatEntryCount;
        newSize = fatEntries_current + BcfFile.numberOfEntriesInFatSector;
        for (j = fatEntries_current; j < newSize; ++j) {
            embFile_readInt(file, BcfFile.fatEntries + j, 4);
        }
        BcfFile.fatEntryCount = newSize;
    }

    /* numberOfDirectoryEntriesPerSector = BcfFile.sectorSize / sizeOfDirectoryEntry;
    CompoundFileDirectory(numberOfDirectoryEntriesPerSector); */
    directorySectorToReadFrom = BcfFile.firstDirectorySectorLocation;
    while (directorySectorToReadFrom != CompoundFileSector_EndOfChain) {
        seekToSector(file, directorySectorToReadFrom);
        readNextSector(file);
        directorySectorToReadFrom = BcfFile.fatEntries[directorySectorToReadFrom];
    }

    return 1;
}

/**
 * TODO: documentation.
 */
FILE* GetFile(bcf_file* bcfFile, FILE* file, char* fileToFind)
{
    int filesize, currentSector, sizeToWrite, currentSize, totalSectors, i;
    char input;
    FILE* fileOut = tmpfile();
    for (i=0; i<BcfFile.maxNumberOfDirectoryEntries; i++) {
        if (string_equal(fileToFind, BcfFile.dirEntries[i].directoryEntryName))
            break;
    }
    filesize = BcfFile.dirEntries[i].streamSize;

    currentSize = 0;
    currentSector = BcfFile.dirEntries[i].startingSectorLocation;
    totalSectors = (int)ceil((float)filesize / BcfFile.sectorSize);
    for (i = 0; i < totalSectors; i++) {
        seekToSector(file, currentSector);
        sizeToWrite = emb_min_int(filesize - currentSize, BcfFile.sectorSize);
        fread(&input, 1, sizeToWrite, file);
        fwrite(&input, 1, sizeToWrite, fileOut);
        currentSize += sizeToWrite;
        currentSector = BcfFile.fatEntries[currentSector];
    }
    return fileOut;
}

/**
 * TODO: documentation.
 */
unsigned int readFullSector(FILE* file, unsigned int* numberOfDifatEntriesStillToRead)
{
    unsigned int i, sectorRef, nextDifatSectorInChain;
    unsigned int entriesToReadInThisSector = 0, entriesInDifat;

    entriesInDifat = (BcfFile.sectorSize - sizeOfChainingEntryAtEndOfDifatSector) / sizeOfDifatEntry;

    if (*numberOfDifatEntriesStillToRead > entriesInDifat) {
        entriesToReadInThisSector = entriesInDifat;
        *numberOfDifatEntriesStillToRead -= entriesToReadInThisSector;
    }
    else {
        entriesToReadInThisSector = *numberOfDifatEntriesStillToRead;
        *numberOfDifatEntriesStillToRead = 0;
    }

    for (i = 0; i < entriesToReadInThisSector; ++i) {
        embFile_readInt(file, &sectorRef, 4);
        BcfFile.fatSectorEntries[BcfFile.fatSectorCount] = sectorRef;
        BcfFile.fatSectorCount++;
    }
    for (i = entriesToReadInThisSector; i < entriesInDifat; ++i) {
        embFile_readInt(file, &sectorRef, 4);
        if (sectorRef != CompoundFileSector_FreeSector) {
            puts("ERROR: readFullSector(), Unexpected sector value");
            /* TODO: end of message: %x at DIFAT[%d]]\n", sectorRef, i); */
        }
    }
    embFile_readInt(file, &nextDifatSectorInChain, 4);
    return nextDifatSectorInChain;
}

/**
 * TODO: documentation.
 */
static void parseDirectoryEntryName(FILE* file, bcf_directory_entry* dir)
{
    int i;
    unsigned short unicodechar;
    for (i = 0; i < 32; ++i) {
        embFile_readInt(file, &unicodechar, 2);
        if (unicodechar != 0x0000) {
            dir->directoryEntryName[i] = (char)unicodechar;
        }
    }
}

/**
 * TODO: documentation.
 */
EmbTime parseTime(FILE* file)
{
    EmbTime returnVal;
#if 0
    unsigned int ft_low, ft_high;
    /*embTime_time(&returnVal); TODO: use embTime_time() rather than time(). */
    embFile_readInt(file, &ft_low, 4);
    embFile_readInt(file, &ft_high, 4);
    /* TODO: translate to actual date time */
#endif
    returnVal.year = 1000; /* for testing */
    return returnVal;
}

/**
 * TODO: documentation.
 */
void CompoundFileDirectoryEntry(bcf_directory_entry *dir, FILE* file)
{
    memset(dir->directoryEntryName, 0, 32);
    parseDirectoryEntryName(file, dir);
    embFile_readInt(file, &(dir->directoryEntryNameLength), 2);
    dir->objectType = (unsigned char)binaryReadByte(file);
    if ((dir->objectType != ObjectTypeStorage) && (dir->objectType != ObjectTypeStream) && (dir->objectType != ObjectTypeRootEntry)) {
        puts("ERROR: CompoundFileDirectoryEntry(), unexpected object type:\n");
        /* TODO: "%d\n", dir->objectType); */
    }
    dir->colorFlag = (unsigned char)binaryReadByte(file);
    embFile_readInt(file, &(dir->leftSiblingId), 4);
    embFile_readInt(file, &(dir->rightSiblingId), 4);
    embFile_readInt(file, &(dir->childId), 4);
    /* guidSize = 16 */
    fread(dir->CLSID, 1, 16, file);
    embFile_readInt(file, &(dir->stateBits), 4);
    dir->creationTime = parseTime(file);
    dir->modifiedTime = parseTime(file);
    embFile_readInt(file, &(dir->startingSectorLocation), 4);
    embFile_readInt(file, &(dir->streamSize), 4); /* This should really be __int64 or long long, but for our uses we should never run into an issue */
    embFile_readInt(file, &(dir->streamSizeHigh), 4); /* top portion of int64 */
}

/**
 * TODO: documentation.
 */
void readNextSector(FILE* file)
{
    unsigned int i;
    for (i = 0; i < BcfFile.maxNumberOfDirectoryEntries; ++i) {
        CompoundFileDirectoryEntry(BcfFile.dirEntries + i, file);
    }
}

/**
 * TODO: documentation.
 */
int embFormat_getExtension(const char* fileName, char* ending)
{
    int i;
    const char* offset;

    if (!fileName) {
        puts("ERROR: embFormat_getExtension(), fileName==0\n");
        return 0;
    }

    if (strlen(fileName) == 0) {
        return 0;
    }

    offset = fileName + strlen(fileName);
    while (*offset != '.') {
        offset--;
    }

    for (i=0; offset[i]; i++) {
        ending[i] = offset[i];
        if (offset[i] >= 'A' && offset[i] <= 'Z') {
            ending[i] -= 'A' + 'a';
        }
    }
    ending[i] = 0; /* terminate the string */

    return 1;
}

EmbFormatList embFormat_data(int format)
{
    EmbFormatList f;
    int out;
    out = dereference_int(format_list);
    fseek(datafile, out+59*format, SEEK_SET);
    fread(embBuffer, 1, 59, datafile);
    
    memcpy(f.extension, (char *)embBuffer, 6);
    memcpy(f.description, (char *)(embBuffer+6), 50);
    f.reader = embBuffer[56];
    f.writer = embBuffer[57];
    f.type = embBuffer[58];

    return f;
}

/**
 * Returns a pointer to an EmbReaderWriter if the \a fileName is a supported file type.
 */
int embReaderWriter_getByFileName(const char* fileName)
{
    int i;
    char ending[10];

    if (!embFormat_getExtension(fileName, ending)) {
        return -1;
    }

    /* checks the first character to see if it is the end symbol */
    for (i = 0; i < 61; i++) {
        EmbFormatList f;
        f = embFormat_data(i);
        if (string_equal(ending, f.extension)) {
            return i;
        }
    }

    printf("ERROR: embReaderWriter_getByFileName(), unsupported file type: %s\n", ending);
    return -1;
}

static char read100(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b[4];
    EmbStitch st;

    embPattern_loadExternalColorFile(pattern, fileName);
    while (fread(b, 1, 4, file) == 4) {
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

static char write100(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish write100 */
}

static char read10o(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b[3];

    embPattern_loadExternalColorFile(pattern, fileName);

    while (fread(b, 1, 3, file) == 3) {
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
            break;
        }
        embPattern_addStitchRel(pattern, st.x, st.y, st.flags, 1);
    }

    return 1;
}

static char write10o(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish write10o */
}

static char readBro(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char x55;
    char b[2];
    short unknown[5];
    char name[8];
    int stitchType;

    embPattern_loadExternalColorFile(pattern, fileName);

    fread(&x55, 1, 1, file);
    embFile_readInt(file, unknown, 2); /* TODO: determine what this unknown data is */

    fread(name, 1, 8, file);
    embFile_readInt(file, unknown+1, 2); /* TODO: determine what this unknown data is */
    embFile_readInt(file, unknown+2, 2); /* TODO: determine what this unknown data is */
    embFile_readInt(file, unknown+3, 2); /* TODO: determine what this unknown data is */
    embFile_readInt(file, unknown+4, 2);

    fseek(file, 0x100, SEEK_SET);

    while (fread(b, 1, 2, file) == 2) {
        short b1, b2;
        stitchType = NORMAL;
        b1 = b[0];
        b2 = b[1];
        if (b1 == -128) {
            unsigned char bCode;
            fread(&bCode, 1, 1, file);
            embFile_readInt(file, &b1, 2);
            embFile_readInt(file, &b2, 2);
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

    return 1;
}

static char writeBro(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeBro */
}

static char readCol(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int nColors, i;
    int num, blue, green, red;
    EmbThread t;
    char line[30];

    pattern->threads->length = 0;

    embFile_readline(file, line, 30);
    nColors = atoi(line);
    if (nColors < 1) {
        puts("ERROR: Number of colors is zero.");
        return 0;
    }
    for (i = 0; i < nColors; i++) {
        embFile_readline(file, line, 30);
        if (strlen(line) < 1) {
            puts("ERROR: Empty line in col file.");
            return 0;
        }
        /* Acts as a sscanf call. */
        char *blue = line;
        char *green = line;
        char *red = line;
        int cur = 0;
        for (i=0; i<30; i++) {
            if (line[i]==',') {
                line[i] = 0;
                switch (cur) {
                case 0:
                    blue = line+i+1;
                    cur++;
                    break;
                case 1:
                    green = line+i+1;
                    cur++;
                    break;
                case 2:
                    red = line+i+1;
                    cur++;
                    break;
                default:
                    break;
                }
            }
        }
        if (cur != 3) {
            break;
        }
        t.color.r = (unsigned char)atoi(red);
        t.color.g = (unsigned char)atoi(green);
        t.color.b = (unsigned char)atoi(blue);
        /* sscanf call finishes here */
        strcpy(t.catalogNumber, "NULL");
        strcpy(t.description, "NULL");
        embPattern_addThread(pattern, t);
    }
    return 1;
}

static char writeCol(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i;
    fprintf(file, "%ld\r\n", pattern->threads->length);
    for (i = 0; i < pattern->threads->length; i++) {
        EmbThread t;
        EmbColor c;
        embArray_get(pattern->threads, &t, i);
        c = t.color;
        fprintf(file, "%d,%d,%d,%d\r\n", i, (int)c.r, (int)c.g, (int)c.b);
    }
    return 1;
}

static FILE* csd_sub_mask;
static FILE* csd_xor_mask;

#define CsdSubMaskSize 479
#define CsdXorMaskSize 501

static void BuildDecryptionTable(int seed)
{
    int i;
    const int mul1 = 0x41C64E6D;
    const int add1 = 0x3039;
    char c;

    for (i = 0; i < CsdSubMaskSize; i++) {
        seed *= mul1;
        seed += add1;
        c = (char)((seed >> 16) & 0xFF);
        fwrite(&c, 1, 1, csd_sub_mask);
    }
    for (i = 0; i < CsdXorMaskSize; i++) {
        seed *= mul1;
        seed += add1;
        c = (char)((seed >> 16) & 0xFF);
        fwrite(&c, 1, 1, csd_xor_mask);
    }
}

static unsigned char DecodeCsdByte(long fileOffset, unsigned char val, int type)
{
    int newOffset, csd_table;
    char _xorMask, _subMask;

    csd_table = dereference_int(csd_decoding_table);
    get_str(embBuffer, csd_table);

    fileOffset = fileOffset - 1;
    if (type != 0) {
        int final;
        int fileOffsetHigh = (int)(fileOffset & 0xFFFFFF00);
        int fileOffsetLow = (int)(fileOffset & 0xFF);

        newOffset = fileOffsetLow;
        fileOffsetLow = fileOffsetHigh;
        final = fileOffsetLow % 0x300;
        if (final != 0x100 && final != 0x200) {
            newOffset = embBuffer[newOffset] | fileOffsetHigh;
        } else if (final != 0x100 && final == 0x200) {
            if (newOffset == 0) {
                fileOffsetHigh = fileOffsetHigh - 0x100;
            }
            newOffset = embBuffer[newOffset] | fileOffsetHigh;
        } else if (newOffset != 1 && newOffset != 0) {
            newOffset = embBuffer[newOffset] | fileOffsetHigh;
        } else {
            fileOffsetHigh = fileOffsetHigh - 0x100;
            newOffset = embBuffer[newOffset] | fileOffsetHigh;
        }
    } else {
        newOffset = (int)fileOffset;
    }

    fseek(csd_xor_mask, newOffset % CsdXorMaskSize, SEEK_SET);
    fread(&_xorMask, 1, 1, csd_xor_mask);

    fseek(csd_sub_mask, newOffset % CsdSubMaskSize, SEEK_SET);
    fread(&_subMask, 1, 1, csd_sub_mask);

    return (unsigned char)(val ^ _xorMask) - _subMask;
}

static char readCsd(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i, type = 0;
    unsigned char identifier[8];
    unsigned char unknown1, unknown2;
    char dx = 0, dy = 0;
    int colorChange = -1;
    int flags;
    char endOfStream = 0;
    unsigned char colorOrder[14];

    csd_sub_mask = tmpfile();
    csd_xor_mask = tmpfile();

    binaryReadBytes(file, identifier, 8); /* TODO: check return value */

    if (identifier[0] != 0x7C && identifier[2] != 0xC3) {
        type = 1;
    }
    if (type == 0) {
        BuildDecryptionTable(0xC);
    } else {
        BuildDecryptionTable(identifier[0]);
    }
    /* save FILE* function calls by loading in a chunk */
    fread(embBuffer, 1, 16*4, file);
    for (i = 0; i < 16; i++) {
        EmbThread thread;
        thread.color.r = DecodeCsdByte(ftell(file), embBuffer[3*i+0], type);
        thread.color.g = DecodeCsdByte(ftell(file), embBuffer[3*i+1], type);
        thread.color.b = DecodeCsdByte(ftell(file), embBuffer[3*i+2], type);
        strcpy(thread.catalogNumber, "");
        strcpy(thread.description, "");
        embPattern_addThread(pattern, thread);
    }
    unknown1 = DecodeCsdByte(ftell(file), embBuffer[3*16+0], type);
    unknown2 = DecodeCsdByte(ftell(file), embBuffer[3*16+1], type);

    for (i = 0; i < 14; i++) {
        colorOrder[i] = (unsigned char)DecodeCsdByte(ftell(file), embBuffer[3*16+2+i], type);
    }
    for (i = 0; !endOfStream; i++) {
        char negativeX, negativeY;
        fread(embBuffer, 1, 3, file);
        unsigned char b0 = DecodeCsdByte(ftell(file), embBuffer[0], type);
        unsigned char b1 = DecodeCsdByte(ftell(file), embBuffer[1], type);
        unsigned char b2 = DecodeCsdByte(ftell(file), embBuffer[2], type);

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
                puts("Invalid color change detected\n");
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

    fclose(csd_xor_mask);
    fclose(csd_sub_mask);

    return 1;
}

static char writeCsd(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeCsd */
}

static const char* csvStitchFlagToStr(int flags)
{
    int i, p;
    switch (flags) {
    case NORMAL:
        i = 0;
        break;
    case JUMP:
        i = 1;
        break;
    case TRIM:
        i = 2;
        break;
    case STOP:
        i = 3;
        break;
    case END:
        i = 4;
        break;
    default:
        i = 5;
        break;
    }
    p = double_dereference_int(stitch_labels, i);
    get_str((char*)embBuffer, p);
    return (char*)embBuffer;
}

static char csvStrToStitchFlag(const char* str)
{
    int i, p;
    char out[] = {NORMAL, JUMP, TRIM, STOP, END};
    if (!str) {
        puts("ERROR: csvStrToStitchFlag(), str==0\n");
        return -1;
    }
    for (i=0; i<5; i++) {
        p = double_dereference_int(stitch_labels, i);
        get_str((char*)embBuffer, p);
        if (string_equal(str, (char*)embBuffer)) {
            return out[i];
        }
    }
    return -1;
}

static char readCsv(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int numColorChanges, pos, cellNum, process, csvMode, expect, flags;
    float xx, yy;
    unsigned char r = 0, g = 0, b = 0;
    char c;
    char* buff = (char*)embBuffer;

    numColorChanges = 0;
    pos = 0;
    cellNum = 0;
    process = 0;
    csvMode = CSV_MODE_NULL;
    expect = CSV_EXPECT_QUOTE1;
    flags = 0;
    while (fread(&c, 1, 1, file)) {
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
                puts("error_read_csv_1");
                return 0;
            }
            break;
        }

        if (process) {
            buff[pos] = 0;
            pos = 0;
            process = 0;
            cellNum++;
            expect = CSV_EXPECT_QUOTE1;
            if (csvMode == CSV_MODE_NULL) {
                csvMode = buff[0];
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
                    /* TODO */
                    strcpy(t.description, "NULL");
                    strcpy(t.catalogNumber, "NULL");
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
                    if (flags == END)
                        break;
                } else if (cellNum == 3) {
                    xx = atof(buff);
                } else if (cellNum == 4) {
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
                buff[pos++] = c;
        }
    }

    /* if not enough colors defined, fill in random colors */
    while (pattern->threads->length < numColorChanges) {
        embPattern_addThread(pattern, embThread_getRandom());
    }

    return 1;
}

/* Copy a block of bytes from the datafile to the elected file
 * if length == 0 use null termination to end copy, otherwise
 * copy length bytes.
 */
static void string_to_file(FILE* file, int offset, int length)
{
    char ch = 1;
    int i;
    fseek(datafile, dereference_int(offset), SEEK_SET);
    if (length == 0) {
        while (ch) {
            fread(&ch, 1, 1, datafile);
            if (ch) {
                fwrite(&ch, 1, 1, file);
            }
        }
    }
    else {
        for (i=0; i<length; i++) {
            fread(&ch, 1, 1, datafile);
            fwrite(&ch, 1, 1, file);
        }
    }
}

static char writeCsv(EmbPattern* pattern, FILE* file, const char* fileName)
{
    EmbStitch st;
    EmbRect boundingRect;
    EmbThread thr;
    int i;
    int stitchCount = 0;

    stitchCount = pattern->stitchList->length;

    boundingRect = embPattern_calcBoundingBox(pattern);

    if (!stitchCount) {
        puts("error_write_csv_0");
        return 0;
    }

    /* write header */
    string_to_file(file, csv_header, 0);

    /* write variables */
    fprintf(file, "\"#\",\"[VAR_NAME]\",\"[VAR_VALUE]\"\n");
    fprintf(file, "\">\",\"STITCH_COUNT:\",\"%d\"\n", stitchCount);
    fprintf(file, "\">\",\"THREAD_COUNT:\",\"%ld\"\n", pattern->threads->length);
    fprintf(file, "\">\",\"EXTENTS_LEFT:\",\"%1.5f\"\n", boundingRect.left);
    fprintf(file, "\">\",\"EXTENTS_TOP:\",\"%1.5f\"\n", boundingRect.top);
    fprintf(file, "\">\",\"EXTENTS_RIGHT:\",\"%1.5f\"\n", boundingRect.right);
    fprintf(file, "\">\",\"EXTENTS_BOTTOM:\",\"%1.5f\"\n", boundingRect.bottom);
    fprintf(file, "\">\",\"EXTENTS_WIDTH:\",\"%1.5f\"\n", embRect_width(boundingRect));
    fprintf(file, "\">\",\"EXTENTS_HEIGHT:\",\"%1.5f\"\n", embRect_height(boundingRect));
    fprintf(file, "\n");

    /* write colors */
    fprintf(file, "\"#\",\"[THREAD_NUMBER]\",\"[RED]\",\"[GREEN]\",\"[BLUE]\",\"[DESCRIPTION]\",\"[CATALOG_NUMBER]\"\n");
    for (i = 0; i < pattern->threads->length; i++) {
        EmbColor c;
        embArray_get(pattern->threads, &thr, i);
        c = thr.color;
        /* TODO: fix segfault that backtraces here when libembroidery-convert from dst to csv. */
        fprintf(file, "\"$\",\"%d\",\"%d\",\"%d\",\"%d\",\"%s\",\"%s\"\n",
            i+1, (int)c.r, (int)c.g, (int)c.b, thr.description, thr.catalogNumber);
    }
    fprintf(file, "\n");

    /* write stitches */
    fprintf(file, "\"#\",\"[STITCH_TYPE]\",\"[X]\",\"[Y]\"\n");
    for (i = 0; i < pattern->stitchList->length; i++) {
        embArray_get(pattern->stitchList, &st, i);
        fprintf(file, "\"*\",\"%s\",\"%1.5f\",\"%1.5f\"\n",
            csvStitchFlagToStr(st.flags), st.x, st.y);
    }

    return 1;
}

static char readDat(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b0;
    short stitchesRemaining;
    int fileLength, b1, b2, stitchType;

    embPattern_loadExternalColorFile(pattern, fileName);
    fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x02, SEEK_SET);
    embFile_readInt(file, &stitchesRemaining, 2);
    fseek(file, 0x100, SEEK_SET);

    while (ftell(file) < fileLength) {
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

    return 1;
}

static char writeDat(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeDat */
}

static char readDsb(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b[4];
    unsigned char header[512];
    embPattern_loadExternalColorFile(pattern, fileName);
    fread(header, 1, 512, file);

    fseek(file, 0x200, SEEK_SET);
    while (fread(b, 1, 3, file) == 3) {
        int x, y;
        unsigned char ctrl;
        int stitchType = NORMAL;

        ctrl = b[0];
        y = b[1];
        x = b[2];

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
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }
    return 1;
}

static char writeDsb(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeDsb */
}

/* .DST (Tajima) embroidery file read/write routines
 * Format comments are thanks to tspilman@dalcoathletic.com who's
 * notes appeared at http://www.wotsit.org under Tajima Format.
 */

static void encode_record(FILE* file, int *dx, int flags)
{
    unsigned char b[3];

    encode_dst_ternary(dx, b);

    b[2] |= (char)3;

    if (flags & END) {
        b[0] = 0;
        b[1] = 0;
        b[2] = (char)-13;
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

    fwrite(b, 1, 3, file);
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
        strcpy(t.description, "NULL");
        strcpy(t.catalogNumber, "NULL");
        embPattern_addThread(pattern, t);
        break;
    default:
        /* unknown field, just save it. */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    }
}

static char readDst(EmbPattern* pattern, FILE* file, const char* fileName)
{
    char var[3]; /* temporary storage variable name */
    unsigned char b[3];
    int i, valpos;
    char *header, *val;

    header = (char*)embBuffer;
    val = (char*)(embBuffer+512);

    /* TODO: review commented code below
    pattern->clear();
    pattern->set_variable("file_name",filename);
    */

    embPattern_loadExternalColorFile(pattern, fileName);
    fread(header, 1, 512, file);

    /* TODO: It would probably be a good idea to validate file before accepting it. */

    /* Fill variables from header fields.
     * See the section on Tajima dst format in the manual for details.
     */
    for (i = 0; i < 512; i++) {
        if (header[i] == ':' && i > 1) {
            var[0] = header[i - 2];
            var[1] = header[i - 1];
            var[2] = '\0';
            valpos = i + 1;
            for (i++; i < 512; i++) {
                /* don't accept : without CR because there's a bug below:
                 * i-valpos must be > 0 which is not the case if
                 * the : is before the third character. */
                if (header[i] == 13 /*||header[i]==':'*/) /* 0x0d = carriage return */
                {
                    if (header[i] == ':') /* : indicates another variable, CR was missing! */
                    {
                        i -= 2;
                    }
                    memcpy(val, &header[valpos], (size_t)(i - valpos));
                    val[i - valpos] = '\0';
                    set_dst_variable(pattern, var, val);
                    break;
                }
            }
        }
    }

    while (fread(b, 1, 3, file) == 3) {
        int x[2], flags;
        if (b[2] == 0xF3) {
            break;
        }
        decode_dst_ternary(x, b);
        flags = (bit(b[2], 8) * JUMP) | (bit(b[2], 7) * STOP);
        embPattern_addStitchRel(pattern, x[0] / 10.0, x[1] / 10.0, flags, 1);
    }

    /* embPattern_combineJumpStitches(pattern, 5); */
    return 1;
}

static char writeDst(EmbPattern* pattern, FILE* file, const char* fileName)
{
    EmbRect boundingRect;
    int pos[2], dx[2], i;
    EmbStitch st;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    /* TODO: make sure that pattern->threads->length defaults to 1 in new patterns */
    boundingRect = embPattern_calcBoundingBox(pattern);

    /* pad to 16 char */
    int namelen = strlen(pattern->name);
    for (i=namelen; i<16; i++) {
        pattern->name[i] = ' ';
    }
    pattern->name[16] = 0;
    fprintf(file, "LA:");
    fprintf(file, pattern->name);
    fprintf(file, "\x0d");

    /* TODO: check that the number of characters adds to 125, or pad
    correctly. */
    fprintf(file, "ST:%d\x0d", pattern->stitchList->length);
    fprintf(file, "CO:%d\x0d", pattern->threads->length - 1); /* number of color changes, not number of colors! */
    fprintf(file, "+X:%d\x0d", (int)(boundingRect.right * 10.0));
    fprintf(file, "-X:%d\x0d", (int)(fabs(boundingRect.left) * 10.0));
    fprintf(file, "+Y:%d\x0d", (int)(boundingRect.bottom * 10.0));
    fprintf(file, "-Y:%d\x0d", (int)(fabs(boundingRect.top) * 10.0));

    /* TODO: review the code below */
    /* will return null pointer if not defined */
    if (pattern->pd[0] == 0 || strlen(pattern->pd) != 6) {
        /* pd is not valid, so fill in a default consisting of "******" */
        strcpy(pattern->pd, "******");
    }
    fprintf(file, "AX:+%d\x0d", pattern->ax); /* will return 0 if not defined */
    fprintf(file, "AY:+%d\x0d", pattern->ay);
    fprintf(file, "MX:+%d\x0d", pattern->mx);
    fprintf(file, "MY:+%d\x0d", pattern->my);
    fprintf(file, "PD:%s\x0d", pattern->pd); /* 6 char, swap for embFile_write */
    fprintf(file, "\x1a"); /* 0x1a is the code for end of section. */

    embFile_pad(file, ' ', 512-125);

    /* write stitches */
    pos[0] = 0;
    pos[1] = 0;
    for (i = 0; i < pattern->stitchList->length; i++) {
        embArray_get(pattern->stitchList, &st, i);
        /* convert from mm to 0.1mm for file format */
        dx[0] = (int)round(st.x * 10.0) - pos[0];
        dx[1] = (int)round(st.y * 10.0) - pos[1];
        pos[0] = (int)round(st.x * 10.0);
        pos[1] = (int)round(st.y * 10.0);
        encode_record(file, dx, st.flags);
    }
    /* finish file with a terminator character */
    fwrite("\xA1\0\0", 1, 3, file);
    return 1;
}

static char readDsz(EmbPattern* pattern, FILE* file, const char* fileName)
{
    embPattern_loadExternalColorFile(pattern, fileName);

    fseek(file, 0x200, SEEK_SET);
    while (fread(embBuffer, 1, 3, file) == 3) {
        int x, y;
        unsigned char ctrl;
        int stitchType = NORMAL;

        y = embBuffer[0];
        x = embBuffer[1];
        ctrl = embBuffer[2];

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
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }

    return 1;
}

static char writeDsz(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeDsz */
}

static char readDxf(EmbPattern* pattern, FILE* file, const char* fileName)
{
    char* dxfVersion = "";
    char* section = "";
    char* tableName = "";
    char* layerName = "";
    char* entityType = "";
    /* layer_names uses the same indexing as the EmbColor array, no need for hash table
    char layer_names[MAX_LAYERS][MAX_LAYER_NAME_LENGTH];
    */
    int eof = 0; /* End Of File */

    float bulge = 0.0, firstX = 0.0, firstY = 0.0, x = 0.0, y, prevX = 0.0, prevY = 0.0;
    char firstStitch = 1;
    char bulgeFlag = 0;
    int fileLength = 0;
    char *buffer = (char*)embBuffer;

    fseek(file, 0L, SEEK_END);

    fileLength = ftell(file);
    fseek(file, 0L, SEEK_SET);

    while (ftell(file) < fileLength) {
        embFile_readline(file, buffer, 1000);
        if ((string_equal(buffer, "HEADER")) || (string_equal(buffer, "CLASSES")) || (string_equal(buffer, "TABLES")) || (string_equal(buffer, "BLOCKS")) || (string_equal(buffer, "ENTITIES")) || (string_equal(buffer, "OBJECTS")) || (string_equal(buffer, "THUMBNAILIMAGE"))) {
            section = buffer;
            printf("SECTION: %s\n", buffer);
        }
        if (string_equal(buffer, "ENDSEC")) {
            section = "";
            printf("ENDSEC: %s\n", buffer);
        }
        if ((string_equal(buffer, "ARC")) || (string_equal(buffer, "CIRCLE")) || (string_equal(buffer, "ELLIPSE")) || (string_equal(buffer, "LINE")) || (string_equal(buffer, "LWPOLYLINE")) || (string_equal(buffer, "POINT"))) {
            entityType = buffer;
        }
        if (string_equal(buffer, "EOF")) {
            eof = 1;
        }

        if (string_equal((char *)section, "HEADER")) {
            if (string_equal(buffer, "$ACADVER")) {
                embFile_readline(file, buffer, 1000);
                embFile_readline(file, dxfVersion, 1000);
                /* TODO: Allow these versions when POLYLINE is handled. */
                /*
                if ((string_equal(dxfVersion, DXF_VERSION_R10))
                    || (string_equal(dxfVersion, DXF_VERSION_R11))
                    || (string_equal(dxfVersion, DXF_VERSION_R12))
                    || (string_equal(dxfVersion, DXF_VERSION_R13)))
                    return 0;
                */
            }
        } else if (string_equal((char *)section, "TABLES")) {
            if (string_equal(buffer, "ENDTAB")) {
                tableName = NULL;
            }

            if (tableName == NULL) {
                if (string_equal(buffer, "2")) /* Table Name */
                {
                    embFile_readline(file, tableName, 1000);
                }
            } else if (string_equal(tableName, "LAYER")) {
                /* Common Group Codes for Tables */
                if (string_equal(buffer, "5")) /* Handle */
                {
                    embFile_readline(file, buffer, 1000);
                    continue;
                } else if (string_equal(buffer, "330")) /* Soft Pointer */
                {
                    embFile_readline(file, buffer, 1000);
                    continue;
                } else if (string_equal(buffer, "100")) /* Subclass Marker */
                {
                    embFile_readline(file, buffer, 1000);
                    continue;
                } else if (string_equal(buffer, "70")) /* Number of Entries in Table */
                {
                    embFile_readline(file, buffer, 1000);
                    continue;
                }
                /* The meaty stuff */
                else if (string_equal(buffer, "2")) /* Layer Name */
                {
                    embFile_readline(file, layerName, 1000);
                } else if (string_equal(buffer, "62")) /* Color Number */
                {
                    embFile_readline(file, buffer, 1000);
                    /*
                    TODO: finish this
                    unsigned char colorNum = atoi(buff);
                    EmbColor co;
                    read _dxfColorTable
                    co.r = embBuffer[3*colorNum+0];
                    co.g = embBuffer[3*colorNum+1];
                    co.b = embBuffer[3*colorNum+2];
                    printf("inserting:%s,%d,%d,%d\n", layerName, co.r, co.g, co.b);
                    if (embHash_insert(layer_names[i], emb_strdup(layerName), &co)) {
                         TODO: log error: failed inserting into layerColorHash
                    }
                    */
                    layerName = NULL;
                }
            }
        } else if (string_equal(section, "ENTITIES")) {
            /* Common Group Codes for Entities */
            if (string_equal(buffer, "5")) /* Handle */
            {
                embFile_readline(file, buffer, 1000);
                continue;
            } else if (string_equal(buffer, "330")) /* Soft Pointer */
            {
                embFile_readline(file, buffer, 1000);
                continue;
            } else if (string_equal(buffer, "100")) /* Subclass Marker */
            {
                embFile_readline(file, buffer, 1000);
                continue;
            } else if (string_equal(buffer, "8")) /* Layer Name */
            {
                embFile_readline(file, buffer, 1000);
                /* embPattern_changeColor(pattern, colorIndexMap[buff]); TODO: port to C */
                continue;
            }

            if (string_equal(entityType, "LWPOLYLINE")) {
                /* The not so important group codes */
                if (string_equal(buffer, "90")) /* Vertices */
                {
                    embFile_readline(file, buffer, 1000);
                    continue;
                } else if (string_equal(buffer, "70")) /* Polyline Flag */
                {
                    embFile_readline(file, buffer, 1000);
                    continue;
                }
                /* TODO: Try to use the widths at some point */
                else if (string_equal(buffer, "40")) /* Starting Width */
                {
                    embFile_readline(file, buffer, 1000);
                    continue;
                } else if (string_equal(buffer, "41")) /* Ending Width */
                {
                    embFile_readline(file, buffer, 1000);
                    continue;
                } else if (string_equal(buffer, "43")) /* Constant Width */
                {
                    embFile_readline(file, buffer, 1000);
                    continue;
                }
                /* The meaty stuff */
                else if (string_equal(buffer, "42")) /* Bulge */
                {
                    embFile_readline(file, buffer, 1000);
                    bulge = atof(buffer);
                    bulgeFlag = 1;
                } else if (string_equal(buffer, "10")) /* X */
                {
                    embFile_readline(file, buffer, 1000);
                    x = atof(buffer);
                } else if (string_equal(buffer, "20")) /* Y */
                {
                    embFile_readline(file, buffer, 1000);
                    y = atof(buffer);

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
                } else if (string_equal(buffer, "0")) {
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
        puts("ERROR: readDxf(), missing EOF at end of DXF file\n");
    }
    return eof;
}

static char writeDxf(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeDxf */
}

static char readEdr(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b[4];

    pattern->threads->length = 0;

    while (fread(b, 1, 4, file) == 4) {
        EmbThread t;
        t.color = embColor_fromStr(b);
        strcpy(t.catalogNumber, "NULL");
        strcpy(t.description, "NULL");
        embPattern_addThread(pattern, t);
    }
    return 1;
}

static char writeEdr(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b[4];
    int i;

    b[3] = 0;
    for (i = 0; i < pattern->threads->length; i++) {
        EmbThread t;
        embArray_get(pattern->threads, &t, i);
        embColor_toStr(t.color, b);
        fwrite(b, 1, 4, file);
    }
    return 1;
}

static char emdDecode(unsigned char inputByte)
{
    return (inputByte >= 0x80) ? ((-~inputByte) - 1) : inputByte; /* TODO: eliminate ternary return statement */
}

static char readEmd(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b[2], jemd0[6]; /* TODO: more descriptive name */
    char dx, dy;
    int flags, i;
    short width, height, colors;

    embPattern_loadExternalColorFile(pattern, fileName);

    binaryReadBytes(file, jemd0, 6); /* TODO: check return value */
    embFile_readInt(file, &width, 2);
    embFile_readInt(file, &height, 2);
    embFile_readInt(file, &colors, 2);

    fseek(file, 0x30, SEEK_SET);

    while (fread(b, 1, 2, file) == 2) {
        flags = NORMAL;

        if (b[0] == 0x80) {
            if (b[1] == 0x2A) {
                embPattern_addStitchRel(pattern, 0, 0, STOP, 1);
                continue;
            } else if (b[1] == 0x80) {
                fread(b, 1, 2, file);
                flags = TRIM;
            } else if (b[1] == 0xFD) {
                break;
            } else {
                continue;
            }
        }
        dx = emdDecode(b[0]);
        dy = emdDecode(b[1]);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

static char writeEmd(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeEmd */
}

static char expDecode(unsigned char a1)
{
    return (a1 > 0x80) ? ((-~a1) - 1) : a1;
}

static void expEncode(unsigned char* b, char dx, char dy, int flags)
{
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

static char readExp(EmbPattern* pattern, FILE* file, const char* fileName)
{
    char dx = 0, dy = 0;
    int flags = 0;

    embPattern_loadExternalColorFile(pattern, fileName);

    while (fread(embBuffer, 1, 2, file) != 2) {
        flags = NORMAL;
        if (embBuffer[0] == 0x80) {
            if (embBuffer[1] & 1) {
                if (fread(embBuffer, 1, 2, file) != 2) break;
                flags = STOP;
            } else if ((embBuffer[1] == 2) || (embBuffer[1] == 4) || embBuffer[1] == 6) {
                flags = TRIM;
                if (embBuffer[1] == 2)
                    flags = NORMAL;
                if (fread(embBuffer, 1, 2, file) != 2) break;
            } else if (embBuffer[1] == 0x80) {
                if (fread(embBuffer, 1, 2, file) != 2) break;
                /* Seems to be b0=0x07 and b1=0x00
                 * Maybe used as extension functions */
                embBuffer[0] = 0;
                embBuffer[1] = 0;
                flags = TRIM;
            }
        }
        dx = expDecode(embBuffer[0]);
        dy = expDecode(embBuffer[1]);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

static char writeExp(EmbPattern* pattern, FILE* file, const char* fileName)
{
    float xx, yy;
    int i;

    /* write stitches */
    xx = yy = 0.0;
    for (i = 0; i < pattern->stitchList->length; i++) {
        EmbStitch st;
        float dx, dy;
        embArray_get(pattern->stitchList, &st, i);
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        expEncode(embBuffer, (char)round(dx), (char)round(dy), st.flags);
        if ((embBuffer[0] == 0x80) &&
            ((embBuffer[1] == 1) || (embBuffer[1] == 2) || (embBuffer[1] == 4) || (embBuffer[1] == 0x10))) {
            fwrite(embBuffer, 1, 4, file);
        } else {
            fwrite(embBuffer, 1, 2, file);
        }
    }
    fprintf(file, "\x1a");
    return 1;
}

static char exyDecodeFlags(unsigned char b2)
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

static char readExy(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b[3];

    embPattern_loadExternalColorFile(pattern, fileName);

    fseek(file, 0x100, SEEK_SET);

    while (fread(b, 1, 3, file) == 3) {
        int flags;
        int x[2];
        decode_dst_ternary(x, b);
        flags = exyDecodeFlags(b[2]);
        if (flags & END) {
            break;
        }
        embPattern_addStitchRel(pattern, x[0] / 10.0, x[1] / 10.0, flags, 1);
    }

    return 1;
}

static char writeExy(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeExy */
}

static char readFxy(EmbPattern* pattern, FILE* file, const char* fileName)
{
    embPattern_loadExternalColorFile(pattern, fileName);
    /* TODO: review for combining code.
     * This line appears to be the only difference from the GT format. */
    fseek(file, 0x100, SEEK_SET);

    while (1) {
        int stitchType = NORMAL;
        int b1 = (int)binaryReadByte(file);
        int b2 = (int)binaryReadByte(file);
        unsigned char commandByte = binaryReadByte(file);

        if (commandByte == 0x91) {
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

    return 1;
}

static char writeFxy(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeFxy */
}

static char readGt(EmbPattern* pattern, FILE* file, const char* fileName)
{
    embPattern_loadExternalColorFile(pattern, fileName);
    /* TODO: review for combining code.
     * This line appears to be the only difference from the FXY format. */
    fseek(file, 0x200, SEEK_SET);

    while (1) {
        int stitchType = NORMAL;
        int b1 = (int)binaryReadByte(file);
        int b2 = (int)binaryReadByte(file);
        unsigned char commandByte = binaryReadByte(file);

        if (commandByte == 0x91) {
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

    return 1;
}

static char writeGt(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeGt */
}

static short husDecode(unsigned char a1, unsigned char a2)
{
    unsigned short res = (a2 << 8) + a1;
    if (res >= 0x8000) {
        return ((-~res) - 1);
    }
    return res;
}

static char husDecodeStitchType(unsigned char b)
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

static char husDecodeByte(unsigned char b)
{
    return (char)b;
}

static unsigned char husEncodeByte(float f)
{
    return (unsigned char)round(f);
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

static char readHus(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int fileLength, i, magicCode, numberOfStitches, nColors;
    short postitiveXHoopSize, postitiveYHoopSize, negativeXHoopSize, negativeYHoopSize;
    int attributeOffset, xOffset, yOffset;
    FILE* attributeData = tmpfile();
    FILE* attributeDataDecompressed = tmpfile();
    FILE* xData = tmpfile();
    FILE* yDecompressed = tmpfile();
    FILE* yData = tmpfile();
    FILE* xDecompressed = tmpfile();

    fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x00, SEEK_SET);

    embFile_readInt(file, &magicCode, 4);
    embFile_readInt(file, &numberOfStitches, 4);
    embFile_readInt(file, &nColors, 4);

    embFile_readInt(file, &postitiveXHoopSize, 2);
    embFile_readInt(file, &postitiveYHoopSize, 2);
    embFile_readInt(file, &negativeXHoopSize, 2);
    embFile_readInt(file, &negativeYHoopSize, 2);

    embFile_readInt(file, &attributeOffset, 4);
    embFile_readInt(file, &xOffset, 4);
    embFile_readInt(file, &yOffset, 4);

    binaryReadBytes(file, embBuffer, 8); /* TODO: check return value */

    fread(embBuffer, 1, 2, file);
    for (i = 0; i < nColors; i++) {
        EmbThread t;
        short pos;
        embFile_readInt(file, &pos, 2);
        t = load_thread(hus_thread, pos);
        embPattern_addThread(pattern, t);
    }

    embFile_copy(file, attributeOffset, attributeData, xOffset - attributeOffset); /* TODO: check return value */
    husExpand(attributeData, attributeDataDecompressed, 10);

    embFile_copy(file, xOffset, attributeData, yOffset - xOffset); /* TODO: check return value */
    husExpand(xData, xDecompressed, 10);

    embFile_copy(file, yOffset, attributeData, fileLength - attributeOffset); /* TODO: check return value */
    husExpand(yData, yDecompressed, 10);

    fclose(xData);
    fclose(yData);
    fclose(attributeData);

    fseek(xDecompressed, 0, SEEK_SET);
    fseek(yDecompressed, 0, SEEK_SET);
    fseek(attributeDataDecompressed, 0, SEEK_SET);
    for (i = 0; i < numberOfStitches; i++) {
        unsigned char c;
        float x, y;
        int attribute;
        fread(&c, 1, 1, xDecompressed);
        x = husDecodeByte(c);
        fread(&c, 1, 1, yDecompressed);
        y = husDecodeByte(c);
        fread(&c, 1, 1, attributeDataDecompressed);
        attribute = husDecodeStitchType(c);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, attribute, 1);
    }

    fclose(xDecompressed);
    fclose(yDecompressed);
    fclose(attributeDataDecompressed);

    return 1;
}

static char writeHus(EmbPattern* pattern, FILE* file, const char* fileName)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor;
    int attributeSize, xCompressedSize, yCompressedSize, i;
    float previousX, previousY;
    FILE* xValues;
    FILE* yValues;
    FILE* attributeValues;
    FILE* xCompressed;
    FILE* yCompressed;
    FILE* attributeCompressed;
    EmbStitch st;

    stitchCount = pattern->stitchList->length;
    /* embPattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */
    patternColor = pattern->threads->length;
    minColors = emb_min_int(24, patternColor);
    binaryWriteUInt(file, 0x00C8AF5B);
    binaryWriteUInt(file, stitchCount);
    binaryWriteUInt(file, minColors);

    boundingRect = embPattern_calcBoundingBox(pattern);
    binaryWriteShort(file, (short)round(boundingRect.right * 10.0));
    binaryWriteShort(file, (short)-round(boundingRect.top * 10.0 - 1.0));
    binaryWriteShort(file, (short)round(boundingRect.left * 10.0));
    binaryWriteShort(file, (short)-round(boundingRect.bottom * 10.0 - 1.0));

    binaryWriteUInt(file, 0x2A + 2 * minColors);

    previousX = 0.0;
    previousY = 0.0;
    for (i = 0; i < pattern->stitchList->length; i++) {
        unsigned x, y, attribute;
        embArray_get(pattern->stitchList, &st, i);
        x = husEncodeByte((st.x - previousX) * 10.0);
        fwrite(&x, 1, 1, xValues);
        previousX = st.x;
        y = husEncodeByte((st.y - previousY) * 10.0);
        fwrite(&y, 1, 1, yValues);
        previousY = st.y;
        attribute = husEncodeStitchType(st.flags);
        fwrite(&attribute, 1, 1, attributeValues);
    }
    attributeSize = husCompress(attributeValues, attributeCompressed, 10);
    xCompressedSize = husCompress(xValues, xCompressed, 10);
    yCompressedSize = husCompress(yValues, yCompressed, 10);
    /* TODO: error if husCompressData returns zero? */

    binaryWriteUInt(file, (unsigned int)(0x2A + 2 * patternColor + attributeSize));
    binaryWriteUInt(file, (unsigned int)(0x2A + 2 * patternColor + attributeSize + xCompressedSize));
    embFile_pad(file, 0, 10);

    for (i = 0; i < patternColor; i++) {
        EmbThread t;
        embArray_get(pattern->threads, &t, i);
        short color_index = (short)embThread_findNearestColor(t.color, hus_thread);
        binaryWriteShort(file, color_index);
    }

    embFile_copy(attributeCompressed, 0, file, attributeSize);
    embFile_copy(xCompressed, 0, file, xCompressedSize);
    embFile_copy(yCompressed, 0, file, yCompressedSize);

    fclose(xValues);
    fclose(xCompressed);
    fclose(yValues);
    fclose(yCompressed);
    fclose(attributeValues);
    fclose(attributeCompressed);
    return 1;
}

static char readInb(EmbPattern* pattern, FILE* file, const char* fileName)
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
    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    binaryReadBytes(file, fileDescription, 8); /* TODO: check return value */
    nullVal = binaryReadByte(file);
    fread(embBuffer, 1, 2, file);
    embFile_readInt(file, &stitchCount, 4);
    embFile_readInt(file, &width, 2);
    embFile_readInt(file, &height, 2);
    embFile_readInt(file, &colorCount, 2);
    embFile_readInt(file, &unknown3, 2);
    embFile_readInt(file, &unknown2, 2);
    embFile_readInt(file, &imageWidth, 2);
    embFile_readInt(file, &imageHeight, 2);
    binaryReadBytes(file, bytesUnknown, 300); /* TODO: check return value */
    embFile_readInt(file, &nullbyte, 2);
    embFile_readInt(file, &left, 2);
    embFile_readInt(file, &right, 2);
    embFile_readInt(file, &top, 2);
    embFile_readInt(file, &bottom, 2);
    fseek(file, 0x2000, SEEK_SET);
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

static char writeInb(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeInb */
}

static char readInf(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int nColors, i;

    fseek(file, 12L, SEEK_SET);
    embFile_readInt_be(file, &nColors, 4);

    pattern->threads->length = 0;

    for (i = 0; i < nColors; i++) {
        char colorType[50];
        char colorDescription[50];
        EmbThread t;
        fread(embBuffer, 1, 4, file);
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        strcpy(t.catalogNumber, "NULL");
        strcpy(t.description, "NULL");
        embPattern_addThread(pattern, t);
        fread(embBuffer, 1, 2, file);
        binaryReadString(file, colorType, 50);
        binaryReadString(file, colorDescription, 50);
    }
    return 1;
}

static char writeInf(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i, bytesRemaining;
    unsigned int uint;
    char *buffer = (char*)embBuffer;

    uint = 0x01;
    embFile_writeInt_be(file, &uint, 4);
    uint = 0x08;
    embFile_writeInt_be(file, &uint, 4);
    /* write place holder offset */
    uint = 0x00;
    embFile_writeInt_be(file, &uint, 4);
    embFile_writeInt_be(file, &(pattern->threads->length), 4);

    for (i = 0; i < pattern->threads->length; i++) {
        EmbColor c;
        EmbThread t;
        unsigned short sh;
        embArray_get(pattern->threads, &t, i);
        c = t.color;
        sh = (unsigned short)(14 + strlen(buffer));
        embFile_writeInt_be(file, &sh, 2); /* record length */
        sh = (unsigned short)i;
        embFile_writeInt_be(file, &sh, 2); /* record number */
        binaryWriteByte(file, c.r);
        binaryWriteByte(file, c.g);
        binaryWriteByte(file, c.b);
        sh = (unsigned short)i;
        embFile_writeInt_be(file, &sh, 2); /* needle number */
        fwrite("RGB\0", 1, 4, file);
        /* Find an inf file format description to see
         * why RGB appears twice in a row.
         */
        fprintf(file, "RGB(%d,%d,%d)", (int)c.r, (int)c.b, (int)c.g);
        binaryWriteByte(file, 0);
    }
    fseek(file, -8, SEEK_END);
    bytesRemaining = ftell(file);
    fseek(file, 8, SEEK_SET);
    embFile_writeInt_be(file, &bytesRemaining, 4);
    return 1;
}

static char jefGetHoopSize(int width, int height)
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
        puts("ERROR: jefSetHoopFromId(), pattern==0\n");
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

struct hoop_padding readRectangle(FILE* file)
{
    struct hoop_padding r;
    embFile_readInt(file, &(r.left), 4);
    embFile_readInt(file, &(r.top), 4);
    embFile_readInt(file, &(r.right), 4);
    embFile_readInt(file, &(r.bottom), 4);
    return r;
}

static char readJef(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int stitchOffset, formatFlags, nColors, numberOfStitchs;
    int hoopSize, i;
    struct hoop_padding bounds, rectFrom110x110, rectFrom50x50, rectFrom200x140, rect_from_custom;
    int stitchCount;
    char date[8], time[8];
    unsigned char b[2];
    char dx = 0, dy = 0;
    int flags = 0;

    embFile_readInt(file, &stitchOffset, 4);
    embFile_readInt(file, &formatFlags, 4); /* TODO: find out what this means */

    binaryReadBytes(file, (unsigned char*)date, 8); /* TODO: check return value */
    binaryReadBytes(file, (unsigned char*)time, 8); /* TODO: check return value */
    embFile_readInt(file, &nColors, 4);
    embFile_readInt(file, &numberOfStitchs, 4);
    embFile_readInt(file, &hoopSize, 4);
    jefSetHoopFromId(pattern, hoopSize);

    bounds = readRectangle(file);
    rectFrom110x110 = readRectangle(file);
    rectFrom50x50 = readRectangle(file);
    rectFrom200x140 = readRectangle(file);
    rect_from_custom = readRectangle(file);

    for (i = 0; i < nColors; i++) {
        EmbThread t;
        int thread_number;
        embFile_readInt(file, &thread_number, 4);
        t = load_thread(jef_thread, thread_number % 79);
        embPattern_addThread(pattern, t);
    }
    fseek(file, stitchOffset, SEEK_SET);
    stitchCount = 0;
    while (stitchCount < numberOfStitchs + 100) {
        flags = NORMAL;
        if (!fread(b, 1, 2, file)) {
            break;
        }
        if (b[0] == 0x80) {
            if (b[1] & 1) {
                if (!fread(b, 1, 2, file)) {
                    break;
                }
                flags = STOP;
            } else if ((b[1] == 2) || (b[1] == 4) || b[1] == 6) {
                flags = TRIM;
                if (!fread(b, 1, 2, file)) {
                    break;
                }
            } else if (b[1] == 0x10) {
                break;
            }
        }
        dx = jefDecode(b[0]);
        dy = jefDecode(b[1]);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

static void jefEncode(unsigned char* b, char dx, char dy, int flags)
{
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

static char writeJef(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int colorlistSize, minColors, designWidth, designHeight, i;
    EmbRect boundingRect;
    EmbTime time;
    EmbStitch st;
    float dx = 0.0, dy = 0.0, xx = 0.0, yy = 0.0;
    unsigned char b[4];

    embPattern_correctForMaxStitchLength(pattern, 12.7, 12.7);

    colorlistSize = pattern->threads->length;
    minColors = emb_max_float(colorlistSize, 6);
    binaryWriteInt(file, 0x74 + (minColors * 4));
    binaryWriteInt(file, 0x0A);

    embTime_initNow(&time);

    fprintf(file, "%04d%02d%02d%02d%02d%02d",
        (int)(time.year + 1900),
        (int)(time.month + 1),
        (int)(time.day),
        (int)(time.hour),
        (int)(time.minute),
        (int)(time.second));
    binaryWriteByte(file, 0x00);
    binaryWriteByte(file, 0x00);
    binaryWriteInt(file, pattern->threads->length);
    binaryWriteInt(file, pattern->stitchList->length + emb_max_float(0, (6 - colorlistSize) * 2) + 1);

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
    if (emb_min_float(550 - designWidth / 2, 550 - designHeight / 2) >= 0) {
        binaryWriteInt(file, emb_max_float(-1, 550 - designWidth / 2)); /* left */
        binaryWriteInt(file, emb_max_float(-1, 550 - designHeight / 2)); /* top */
        binaryWriteInt(file, emb_max_float(-1, 550 - designWidth / 2)); /* right */
        binaryWriteInt(file, emb_max_float(-1, 550 - designHeight / 2)); /* bottom */
    } else {
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
    }

    /* Distance from default 50 x 50 Hoop */
    if (emb_min_float(250 - designWidth / 2, 250 - designHeight / 2) >= 0) {
        binaryWriteInt(file, (int)emb_max_float(-1, 250 - designWidth / 2)); /* left */
        binaryWriteInt(file, (int)emb_max_float(-1, 250 - designHeight / 2)); /* top */
        binaryWriteInt(file, (int)emb_max_float(-1, 250 - designWidth / 2)); /* right */
        binaryWriteInt(file, (int)emb_max_float(-1, 250 - designHeight / 2)); /* bottom */
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

    for (i = 0; i < pattern->threads->length; i++) {
        EmbThread t;
        embArray_get(pattern->threads, &t, i);
        int j = embThread_findNearestColor(t.color, jef_thread);
        binaryWriteInt(file, j);
    }

    for (i = 0; i < (minColors - colorlistSize); i++) {
        binaryWriteInt(file, 0x0D);
    }

    for (i = 0; i < pattern->stitchList->length; i++) {
        embArray_get(pattern->stitchList, &st, i);
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        jefEncode(b, (char)round(dx), (char)round(dy), st.flags);
        if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
            fwrite(b, 1, 4, file);
        } else {
            fwrite(b, 1, 2, file);
        }
    }
    return 1;
}

static void ksmEncode(unsigned char* b, char dx, char dy, int flags)
{
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

static char readKsm(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int prevStitchType = NORMAL;
    char b[3];

    fseek(file, 0x200, SEEK_SET);

    while (fread(b, 1, 3, file) == 3) {
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

static char writeKsm(EmbPattern* pattern, FILE* file, const char* fileName)
{
    EmbVector pos, diff;
    int i;

    embFile_pad(file, 0, 0x200);

    /* write stitches */
    pos.x = pos.y = 0;
    for (i = 0; i < pattern->stitchList->length; i++) {
        EmbStitch st;
        unsigned char b[4];
        embArray_get(pattern->stitchList, &st, i);
        diff.x = st.x - pos.x;
        diff.y = st.y - pos.y;
        pos.x = st.x;
        pos.y = st.y;
        ksmEncode(b, (char)(diff.x * 10.0), (char)(diff.y * 10.0), st.flags);
        fwrite(b, 1, 2, file);
    }
    fprintf(file, "\x1a");
    return 1;
}

/* Pfaff MAX embroidery file format */

static float maxDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res)&0x7FFFFF) - 1));
    }
    return res;
}

static void maxEncode(FILE* file, int x, int y)
{
    if (!file) {
        puts("error_max_encode_no_file");
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

static char readMax(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b[8];
    float dx, dy;
    int i, flags, stitchCount;

    fseek(file, 0xD5, SEEK_SET);
    embFile_readInt(file, &stitchCount, 4);

    /* READ STITCH RECORDS */
    for (i = 0; i < stitchCount; i++) {
        flags = NORMAL;
        if (fread(b, 1, 8, file) != 8)
            break;

        dx = maxDecode(b[0], b[1], b[2]);
        dy = maxDecode(b[4], b[5], b[6]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    embPattern_flipVertical(pattern);

    return 1;
}

static char writeMax(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i;

    string_to_file(file, max_header, 0xD5);
    for (i = 0; i < pattern->stitchList->length; i++) {
        float x, y;
        EmbStitch st;
        embArray_get(pattern->stitchList, &st, i);
        x = (int)round(st.x * 10.0);
        y = (int)round(st.y * 10.0);
        maxEncode(file, x, y);
    }
    return 1;
}

static char mitDecodeStitch(unsigned char value)
{
    if (value & 0x80) {
        return -(value & 0x1F);
    }
    return value;
}

static char readMit(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char data[2];

    /* embPattern_loadExternalColorFile(pattern, fileName); TODO: review this and uncomment or remove it */

    while (binaryReadBytes(file, data, 2) == 2) {
        float x, y;
        x = mitDecodeStitch(data[0]) / 10.0;
        y = mitDecodeStitch(data[1]) / 10.0;
        embPattern_addStitchRel(pattern, x, y, NORMAL, 1);
    }

    return 1;
}

static unsigned char mitEncodeStitch(float value)
{
    if (value < 0) {
        return 0x80 | (unsigned char)(-value);
    }
    return (unsigned char)value;
}

static char writeMit(EmbPattern* pattern, FILE* file, const char* fileName)
{
    EmbStitch st;
    EmbVector pos, diff;
    int i;

    embPattern_correctForMaxStitchLength(pattern, 0x1F, 0x1F);
    pos.x = pos.y = 0;
    for (i = 0; i < pattern->stitchList->length; i++) {
        embArray_get(pattern->stitchList, &st, i);
        diff.x = st.x - pos.x;
        diff.y = st.y - pos.y;
        pos.x = st.x;
        pos.y = st.y;
        embBuffer[0] = mitEncodeStitch(diff.x);
        embBuffer[1] = mitEncodeStitch(diff.y);
        fwrite(embBuffer, 1, 2, file);
    }
    return 1;
}

static char decodeNewStitch(unsigned char value)
{
    return (int)value;
}

static char readNew(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned int stitchCount;
    unsigned char data[3];

    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_readInt(file, &stitchCount, 2);
    while (binaryReadBytes(file, data, 3) == 3) {
        int x = decodeNewStitch(data[0]);
        int y = decodeNewStitch(data[1]);
        int flag = NORMAL;
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
        if ((data[2] & 0x1E) == 0x02) {
            flag = STOP;
        }
        /* Unknown values, possibly TRIM
        155 = 1001 1011 = 0x9B
        145 = 1001 0001 = 0x91
        */
        /*char val = (data[2] & 0x1C);
        if(val != 0 && data[2] != 0x9B && data[2] != 0x91)
        {
            int z = 1;
        }*/
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flag, 1);
    }

    return 1;
}

static char writeNew(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeNew */
}

static char* ofmReadLibrary(FILE* file)
{
    int stringLength = 0;
    /* FF FE FF */
    unsigned char leadIn[3];

    binaryReadBytes(file, leadIn, 3); /* TODO: check return value */
    stringLength = binaryReadByte(file);
    fread(embBuffer, 1, stringLength * 2, file); /* TODO: check return value */
    return embBuffer;
}

static int ofmReadClass(FILE* file)
{
    int len;
    char* s = (char*)embBuffer;

    fread(embBuffer, 1, 2, file);
    embFile_readInt(file, &len, 2);

    binaryReadBytes(file, (unsigned char*)s, len); /* TODO: check return value */
    s[len] = '\0';
    if (string_equal(s, "CExpStitch"))
        return 0x809C;
    if (string_equal(s, "CColorChange"))
        return 0xFFFF;
    return 0;
}

static void ofmReadBlockHeader(FILE* file)
{
    int val[10]; /* TODO: determine what these represent */
    unsigned char len;
    unsigned short short1;
    /* TODO: determine what these 3 variables represent */
    short unknown1 = 0;
    short unknown2 = 0;
    int unknown3 = 0, i;

    embFile_readInt(file, &unknown1, 2);
    embFile_readInt(file, &i, 4);
    unknown2 = (short)i;
    embFile_readInt(file, &unknown3, 2);

    fread(embBuffer, 1, 3, file);
    /* int v = binaryReadBytes(3); TODO: review */
    len = binaryReadUInt8(file);
    fread(embBuffer, 1, 2*len, file);
    /* TODO: check return value here */
    fread(embBuffer, 1, 42, file);
    /* 0, 0, 0, 0, 1, 1, 1, 0, 64, 64 */
    for (i=0; i<10; i++) {
        embFile_readInt(file, val+i, 4);
    }
    embFile_readInt(file, &short1, 2); /*  0 */
}

static void ofmReadColorChange(FILE* file, EmbPattern* pattern)
{
    ofmReadBlockHeader(file);
    embPattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
}

static void ofmReadThreads(FILE* file, EmbPattern* p)
{
    int i, numberOfLibraries;
    char* primaryLibraryName = 0;
    char* expandedString;
    short nColors, stringLen;

    /* Magic Code: FF FE FF 00
     * Number of colors: 2 bytes signed short
     */
    fread(embBuffer, 1, 4, file);

    embFile_readInt(file, &nColors, 2);
    fread(embBuffer, 1, 2, file);
    embFile_readInt(file, &stringLen, 2);
    expandedString = (char*)embBuffer;
    binaryReadBytes(file, (unsigned char*)expandedString, stringLen); /* TODO: check return value */
    for (i = 0; i < nColors; i++) {
        EmbThread thread;
        char colorNumberText[10];
        short threadLibrary = 0;
        unsigned char colorNameLength;
        int colorNumber;
        char* colorName = 0;
        unsigned char color[3];
        fread(color, 1, 3, file);
        fread(embBuffer, 1, 1, file);
        embFile_readInt(file, &threadLibrary, 2);
        fread(embBuffer, 1, 2, file);
        embFile_readInt(file, &colorNumber, 4);
        fread(embBuffer, 1, 3, file);
        colorNameLength = binaryReadByte(file);
        colorName = (char*)embBuffer;
        binaryReadBytes(file, (unsigned char*)colorName, colorNameLength * 2); /* TODO: check return value */
        fread(embBuffer, 1, 2, file);
        sprintf(colorNumberText, "%d", colorNumber);
        thread.color = embColor_fromStr(color);
        strcpy(thread.catalogNumber, colorNumberText);
        strcpy(thread.description, colorName);
        embPattern_addThread(p, thread);
    }
    fread(embBuffer, 1, 2, file);
    primaryLibraryName = ofmReadLibrary(file);
    embFile_readInt(file, &numberOfLibraries, 2);
    for (i = 0; i < numberOfLibraries; i++) {
        /*libraries.Add( TODO: review */
        char* libName = ofmReadLibrary(file);
    }
}

static float ofmDecode(unsigned char b1, unsigned char b2)
{
    float val = (float)(short)(b1 << 8 | b2);
    return val;
}

static void ofmReadExpanded(FILE* file, EmbPattern* p)
{
    int i, numberOfStitches = 0;

    ofmReadBlockHeader(file);
    embFile_readInt(file, &numberOfStitches, 4);

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

static char readOfm(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int unknownCount = 0;
    short key = 0;
    short classNameLength;
    char* s = 0;
    FILE* fileCompound = 0;

    fileCompound = embFile_open(fileName, "rb", 0);
    if (!fileCompound)
        return 0;

    bcfFile_read(fileCompound);
    file = GetFile(&BcfFile, fileCompound, "EdsIV Object");
    /* BcfFile.directory.maxEntries = 0; */

    fseek(file, 0x1C6, SEEK_SET);
    ofmReadThreads(file, pattern);
    fseek(file, 0x110, SEEK_CUR);
    fread(embBuffer, 1, 4, file);
    embFile_readInt(file, &classNameLength, 2);
    s = (char*)embBuffer;
    binaryReadBytes(file, (unsigned char*)embBuffer, classNameLength); /* TODO: check return value */
    embFile_readInt(file, &unknownCount, 2); /* TODO: determine what unknown count represents */

    fread(embBuffer, 1, 2, file);
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
        embFile_readInt(file, &key, 2);
        if (key == 0xFFFF) {
            ofmReadClass(file);
        }
    }

    fclose(fileCompound);

    embPattern_flip(pattern, 1, 1);

    return 1;
}

static char writeOfm(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeOfm */
}

static float pcdDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res)&0x7FFFFF) - 1));
    }
    return res;
}

static char readPcd(EmbPattern* pattern, FILE* file, const char* fileName)
{
    char allZeroColor = 1;
    int i;
    unsigned char b[9];
    float dx = 0, dy = 0;
    int flags = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount = 0, st = 0;

    fread(embBuffer, 1, 2, file);
    version = embBuffer[0];
    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * and 3 for PCS with large hoop (115x120) */
    hoopSize = embBuffer[1];
    embFile_readInt(file, &colorCount, 2);

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        fread(embBuffer, 1, 4, file);
        t.color = embColor_fromStr(embBuffer);
        strcpy(t.catalogNumber, "NULL");
        strcpy(t.description, "NULL");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        embPattern_addThread(pattern, t);
    }
    if (allZeroColor)
        embPattern_loadExternalColorFile(pattern, fileName);
    embFile_readInt(file, &st, 2);
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
        dx = pcdDecode(b[1], b[2], b[3]);
        dy = pcdDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

static void pcEncode(FILE* file, int dx, int dy, int flags);

static char writePcd(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i;
    unsigned short sh;

    binaryWriteByte(file, (unsigned char)'2');
    binaryWriteByte(file, 3); /* TODO: select hoop size defaulting to Large PCS hoop */
    sh = (unsigned short)pattern->threads->length;
    embFile_writeInt(file, &sh, 2);

    embPattern_colorBlock16(pattern, file);

    sh = (unsigned short)pattern->stitchList->length;
    embFile_writeInt(file, &sh, 2);
    /* write stitches */
    for (i = 0; i < pattern->stitchList->length; i++) {
        EmbStitch st;
        embArray_get(pattern->stitchList, &st, i);
        pcEncode(file, (int)round(st.x * 10.0), (int)round(st.y * 10.0), st.flags);
    }
    return 1;
}

static float pcmDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res)&0x7FFFFF) - 1));
    }
    return res;
}

static char readPcm(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i = 0;
    unsigned char b[9];
    float dx = 0, dy = 0;
    int flags = 0, st = 0;

    fseek(file, 4, SEEK_SET);

    for (i = 0; i < 16; i++) {
        EmbThread t;
        int colorNumber;
        fread(embBuffer, 1, 2, file);
        /* zero followed by colorNumber */
        colorNumber = embBuffer[1];
        t = load_thread(pcm_thread, colorNumber);
        embPattern_addThread(pattern, t);
    }
    embFile_readInt_be(file, &st, 2);
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
        dx = pcmDecode(b[2], b[1], b[0]);
        dy = pcmDecode(b[6], b[5], b[4]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

static char writePcm(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writePcm */
}

static float pcqDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res)&0x7FFFFF) - 1));
    }
    return res;
}

static char readPcq(EmbPattern* pattern, FILE* file, const char* fileName)
{
    char allZeroColor = 1;
    unsigned char b[9];
    float dx = 0, dy = 0;
    int i, flags = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount, st;
    EmbThread t;

    version = binaryReadByte(file);
    hoopSize = binaryReadByte(file);
    /* 0 for PCD, 1 for PCQ (MAXI), 2 for PCS with small hoop(80x80), */
    /* and 3 for PCS with large hoop (115x120) */
    embFile_readInt(file, &colorCount, 2);

    for (i = 0; i < colorCount; i++) {
        fread(b, 1, 4, file);
        t.color = embColor_fromStr(b);
        strcpy(t.catalogNumber, "NULL");
        strcpy(t.description, "NULL");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        embPattern_addThread(pattern, t);
    }
    if (allZeroColor)
        embPattern_loadExternalColorFile(pattern, fileName);
    embFile_readInt(file, &st, 2);
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
        dx = pcqDecode(b[1], b[2], b[3]);
        dy = pcqDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

static char writePcq(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i;
    unsigned short sh;

    fwrite("2\x03", 1, 2, file);
    /* TODO: select hoop size defaulting to Large PCS hoop */
    sh = (unsigned short)pattern->threads->length;
    embFile_writeInt(file, &sh, 2);

    embPattern_colorBlock16(pattern, file);

    sh = (unsigned short)pattern->stitchList->length;
    embFile_writeInt(file, &sh, 2);
    /* write stitches */
    for (i = 0; i < pattern->stitchList->length; i++) {
        EmbStitch st;
        embArray_get(pattern->stitchList, &st, i);
        pcEncode(file, (int)round(st.x * 10.0), (int)round(st.y * 10.0), st.flags);
    }
    return 1;
}

static float pcsDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res)&0x7FFFFF) - 1));
    }
    return res;
}

static void pcEncode(FILE* file, int dx, int dy, int flags)
{
    unsigned char toWrite[9];

    toWrite[0] = 0;
    toWrite[1] = dx & 0xFF;
    toWrite[2] = (dx >> 8) & 0xFF;
    toWrite[3] = (dx >> 16) & 0xFF;

    toWrite[4] = 0;
    toWrite[5] = dy & 0xFF;
    toWrite[6] = (dy >> 8) & 0xFF;
    toWrite[7] = (dy >> 16) & 0xFF;
    
    toWrite[8] = 0;
    if (flags & STOP) {
        toWrite[8] |= 0x01;
    }
    if (flags & TRIM) {
        toWrite[8] |= 0x04;
    }
    fwrite(toWrite, 1, 9, file);
}

static char readPcs(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i;
    unsigned char allZeroColor, version, hoopSize;
    unsigned short colorCount, st;

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

    embFile_readInt(file, &colorCount, 2);

    allZeroColor = 1;
    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        strcpy(t.catalogNumber, "NULL");
        strcpy(t.description, "NULL");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        embPattern_addThread(pattern, t);
        binaryReadByte(file);
    }

    if (allZeroColor) {
        embPattern_loadExternalColorFile(pattern, fileName);
    }

    embFile_readInt(file, &st, 2);

    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        int flags;
        float dx, dy;
        unsigned char b[9];
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
        dx = pcsDecode(b[1], b[2], b[3]);
        dy = pcsDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

static EmbThread load_thread(int thread_table, int index)
{
    EmbThread t;
    int out;
    char loads[36];
    out = double_dereference_int(brand_codes, thread_table);
    fseek(datafile, out+35*index, SEEK_SET);
    fread(loads, 1, 35, datafile);
    t.color.r = loads[30];
    t.color.g = loads[31];
    t.color.b = loads[32];
    strcpy(t.catalogNumber, "TODO:HUS_CODE");
    strcpy(t.description, (char *)loads);
    return t;    
}

static char writePcs(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i;
    unsigned short sh;

    /* TODO: select hoop size defaulting to Large PCS hoop */
    fwrite("2\x03", 1, 2, file);
    sh = (unsigned short)pattern->threads->length;
    embFile_writeInt(file, &sh, 2);

    embPattern_colorBlock16(pattern, file);

    sh = (unsigned short)pattern->stitchList->length;
    embFile_writeInt(file, &sh, 2);
    /* write stitches */
    for (i = 0; i < sh; i++) {
        EmbStitch st;
        embArray_get(pattern->stitchList, &st, i);
        pcEncode(file, (int)round(st.x * 10.0), (int)round(st.y * 10.0), st.flags);
    }
    return 1;
}

void readPecStitches(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int stitchNumber = 0;

    while (fread(embBuffer, 1, 2, file) == 2) {
        int val1 = (int)embBuffer[0];
        int val2 = (int)embBuffer[1];

        int stitchType = NORMAL;
        if (val1 == 0xFF && val2 == 0x00) {
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

static void pecEncodeJump(FILE* file, int x, int types)
{
    int outputVal = abs(x) & 0x7FF;
    unsigned int orPart = 0x80;

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

static void pecEncodeStop(FILE* file, unsigned char val)
{
    fwrite("\xFE\xB0", 1, 2, file);
    fwrite(&val, 1, 1, file);
}

static char readPec(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned int graphicsOffset;
    unsigned char colorChanges;
    int i;

    fseek(file, 0x38, SEEK_SET);
    fread(&colorChanges, 1, 1, file);
    for (i = 0; i <= colorChanges; i++) {
        unsigned char c;
        fread(&c, 1, 1, file);        
        embPattern_addThread(pattern, load_thread(pec_thread, c % 65));
    }

    /* Get Graphics offset */
    fseek(file, 0x20A, SEEK_SET);

    graphicsOffset = (unsigned int)(binaryReadUInt8(file));
    graphicsOffset |= (binaryReadUInt8(file) << 8);
    graphicsOffset |= (binaryReadUInt8(file) << 16);

    /* \x31\xFF\xF0 */
    fread(embBuffer, 1, 3, file);
    /* Get X and Y size in .1 mm
     * 0x210 <- what is this?
     * x size signed short
     * y size signed short */
    fread(embBuffer, 1, 4, file);
 
    fread(embBuffer, 1, 2, file); /* 0x01E0 */
    fread(embBuffer, 1, 2, file); /* 0x01B0 */
    fread(embBuffer, 1, 2, file); /* distance left from start */
    fread(embBuffer, 1, 2, file); /* distance up from start */

    /* Begin Stitch Data */
    /* 0x21C */
    /*unsigned int end = graphicsOffset + 0x208; */
    readPecStitches(pattern, file, fileName);

    embPattern_flipVertical(pattern);

    return 1;
}

static void pecEncode(FILE* file, EmbPattern* p)
{
    float thisX = 0.0;
    float thisY = 0.0;
    unsigned char stopCode = 2;
    EmbStitch s;
    int deltaX, deltaY, i;

    for (i = 0; i < p->stitchList->length; i++) {
        embArray_get(p->stitchList, &s, i);

        deltaX = (int)round(s.x - thisX);
        deltaY = (int)round(s.y - thisY);
        thisX += (float)deltaX;
        thisY += (float)deltaY;

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
    int out;
    out = dereference_int(image_frame);
    fseek(datafile, out, SEEK_SET);
    fread(image, 1, 48*38, datafile);
}

static void writeImage(FILE* file, unsigned char image[][48])
{
    int i, j;

    for (i = 0; i < 38; i++) {
        for (j = 0; j < 6; j++) {
            int offset = j * 8;
            unsigned char output = 0;
            output |= 0x01 * (image[i][offset] != 0);
            output |= 0x02 * (image[i][offset + 1] != 0);
            output |= 0x04 * (image[i][offset + 2] != 0);
            output |= 0x08 * (image[i][offset + 3] != 0);
            output |= 0x10 * (image[i][offset + 4] != 0);
            output |= 0x20 * (image[i][offset + 5] != 0);
            output |= 0x40 * (image[i][offset + 6] != 0);
            output |= 0x40 * (image[i][offset + 7] != 0);
            binaryWriteByte(file, output);
        }
    }
}

void writePecStitches(EmbPattern* pattern, FILE* file, const char* fileName)
{
    EmbStitch st;
    EmbRect bounds;
    unsigned char image[38][48];
    int i, currentThreadCount, graphicsOffsetLocation, graphicsOffsetValue, height, width, x, y;
    float xFactor, yFactor;
    char* slashPos, *backslashPos, *dotPos, *start;
    slashPos = (char*)fileName+strlen(fileName);
    while (slashPos > fileName && *slashPos != '/') {
        slashPos--;
    }
    backslashPos = (char*)fileName+strlen(fileName);
    while (backslashPos > fileName && *backslashPos != '\\') {
        backslashPos--;
    }
    dotPos = (char*)fileName+strlen(fileName);
    while (dotPos > fileName && *dotPos != '.') {
        dotPos--;
    }

    start = (char*)fileName;
    if (slashPos > fileName) {
        start = slashPos + 1;
    }
    if (backslashPos > fileName) {
        start = backslashPos + 1;
    }

    fwrite("LA:", 1, 3, file);

    while (start < dotPos) {
        binaryWriteByte(file, (unsigned char)*start);
        start++;
    }
    embFile_pad(file, 0x20, 16-(int)(dotPos - start));
    binaryWriteByte(file, 0x0D);
    embFile_pad(file, 0x20, 12);
    fwrite("\xFF\x00\x06\x26", 1, 4, file);

    embFile_pad(file, 0x20, 12);
    currentThreadCount = pattern->threads->length;
    binaryWriteByte(file, (unsigned char)(currentThreadCount - 1));

    for (i = 0; i < currentThreadCount; i++) {
        EmbThread t;
        embArray_get(pattern->threads, &t, i);
        binaryWriteByte(file, (unsigned char)embThread_findNearestColor(t.color, pec_thread));
    }
    embFile_pad(file, 0x20, (int)(0x1CF - currentThreadCount));
    embFile_pad(file, 0, 2);

    graphicsOffsetLocation = ftell(file);
    /* placeholder bytes to be overwritten */
    embFile_pad(file, 0, 3);

    fwrite("\x31\xFF\xF0", 1, 3, file);

    bounds = embPattern_calcBoundingBox(pattern);

    height = (int)round(embRect_height(bounds));
    width = (int)round(embRect_width(bounds));
    /* write 2 byte x size */
    binaryWriteShort(file, (short)width);
    /* write 2 byte y size */
    binaryWriteShort(file, (short)height);

    /* Write 4 miscellaneous int16's */
    binaryWriteShort(file, (short)0x1E0);
    binaryWriteShort(file, (short)0x1B0);

    short sh = (unsigned short)(0x9000 | -(int)round(bounds.left));
    embFile_writeInt_be(file, &sh, 2);
    sh = (unsigned short)(0x9000 | -(int)round(bounds.top));
    embFile_writeInt_be(file, &sh, 2);

    pecEncode(file, pattern);
    graphicsOffsetValue = ftell(file) - graphicsOffsetLocation + 2;
    fseek(file, graphicsOffsetLocation, SEEK_SET);

    binaryWriteByte(file, (unsigned char)(graphicsOffsetValue & 0xFF));
    binaryWriteByte(file, (unsigned char)((graphicsOffsetValue >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((graphicsOffsetValue >> 16) & 0xFF));

    fseek(file, 0x00, SEEK_END);

    /* Writing all colors */
    clearImage(image);

    yFactor = 32.0 / height;
    xFactor = 42.0 / width;
    for (i = 0; i < pattern->stitchList->length; i++) {
        int x, y;
        embArray_get(pattern->stitchList, &st, i);
        x = (int)round((st.x - bounds.left) * xFactor) + 3;
        y = (int)round((st.y - bounds.top) * yFactor) + 3;
        image[y][x] = 1;
    }
    writeImage(file, image);

    /* Writing each individual color */
    for (i = 0; i < currentThreadCount; i++) {
        clearImage(image);
        for (i = 0; i < pattern->stitchList->length; i++) {
            embArray_get(pattern->stitchList, &st, i);
            x = (int)round((st.x - bounds.left) * xFactor) + 3;
            y = (int)round((st.y - bounds.top) * yFactor) + 3;
            if (st.flags & STOP) {
                break;
            }
            image[y][x] = 1;
        }
        writeImage(file, image);
    }
}

static char writePec(EmbPattern* pattern, FILE* file, const char* fileName)
{
    /* TODO: There needs to be a matching flipVertical() call after the write
     * to ensure multiple writes from the same pattern work properly */
    embPattern_flipVertical(pattern);
    embPattern_fixColorCount(pattern);
    embPattern_correctForMaxStitchLength(pattern, 12.7, 204.7);
    embPattern_scale(pattern, 10.0);

    fprintf(file, "#PEC0001");

    writePecStitches(pattern, file, fileName);

    return 1;
}

static char readPes(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int numColors, x;
    short pecstart;

    fseek(file, 8, SEEK_SET);
    embFile_readInt(file, &pecstart, 4);

    fseek(file, pecstart + 48, SEEK_SET);
    fread(embBuffer, 1, 1, file);
    numColors = embBuffer[0] + 1;
    fread(embBuffer, 1, numColors, file);
    for (x = 0; x < numColors; x++) {
        embPattern_addThread(pattern, load_thread(pec_thread, embBuffer[x]));
    }

    fseek(file, pecstart + 532, SEEK_SET);
    readPecStitches(pattern, file, fileName);

    embPattern_flipVertical(pattern);

    return 1;
}

static const char *pesVersionTable[] = {
    "#PES0100",
    "#PES0090",
    "#PES0080",
    "#PES0070",
    "#PES0060",
    "#PES0056",
    "#PES0055",
    "#PES0050",
    "#PES0040",
    "#PES0030",
    "#PES0022",
    "#PES0020",
    "#PES0001",
    "#PEC0001",
    0
};

/*
static void readPESHeader(FILE* file, EmbPattern* pattern)
{
    char* signature = readString(8);
    if (strcmp(signature, "#PES0100") {
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

static void readPESHeaderDefault()
{
    int pecStart = binaryReadInt32();
    skip(pecStart - readPosition);
}

static void readDescriptions()
{
    int DesignStringLength = binaryReadByte();
    String DesignName = readString(DesignStringLength);
    pattern.setName(DesignName);
    int categoryStringLength = binaryReadByte();
    String Category = readString(categoryStringLength);
    pattern.setCategory(Category);
    int authorStringLength = binaryReadByte();
    String Author = readString(authorStringLength);
    pattern.setAuthor(Author);
    int keywordsStringLength = binaryReadByte();
    String keywords = readString(keywordsStringLength);
    pattern.setKeywords(keywords);
    int commentsStringLength = binaryReadByte();
    String Comments = readString(commentsStringLength);
    pattern.setComments(Comments);
}

static void readPESHeaderV4()
{
    int pecStart = binaryReadInt32();
    fseek(file, 4, SEEK_CUR);
    readDescriptions();
    skip(pecStart - readPosition);
}

    static void readPESHeaderV5()  {
        int pecStart = binaryReadInt32();
        fseek(file, 4, SEEK_CUR);
        readDescriptions();
        fseek(file, 24, SEEK_CUR);//36 v6
        int fromImageStringLength = binaryReadByte();
        skip(fromImageStringLength);
        fseek(file, 24, SEEK_CUR);
        int nProgrammableFills = binaryReadInt16();
        if (nProgrammableFills != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int nMotifs = binaryReadInt16();
        if (nMotifs != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int featherPatternCount = binaryReadInt16();
        if (featherPatternCount != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int nColors = binaryReadInt16();
        for (int i = 0; i < nColors; i++) {
            readThread();
        }
        fseek(file, pecStart, SEEK_SET);
    }

    static void readPESHeaderV6()  {
        int pecStart = binaryReadInt32();
        fseek(file, 4, SEEK_CUR);
        readDescriptions();
        fseek(file, 36, SEEK_CUR);
        int fromImageStringLength = binaryReadByte();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        fseek(file, 24, SEEK_CUR);
        int nProgrammableFills = binaryReadInt16();
        if (nProgrammableFills != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int nMotifs = binaryReadInt16();
        if (nMotifs != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int featherPatternCount = binaryReadInt16();
        if (featherPatternCount != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int nColors = binaryReadInt16();
        for (int i = 0; i < nColors; i++) {
            readThread();
        }
        fseek(file, pecStart, SEEK_SET);
    }
    
    static void readPESHeaderV7()  {
        int pecStart = binaryReadInt32();
        fseek(file, 4, SEEK_CUR);
        readDescriptions();
        fseek(file, 36, SEEK_CUR);
        int fromImageStringLength = binaryReadByte();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        fseek(file, 24, SEEK_CUR);
        int nProgrammableFills = binaryReadInt16();
        if (nProgrammableFills != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int nMotifs = binaryReadInt16();
        if (nMotifs != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int featherPatternCount = binaryReadInt16();
        if (featherPatternCount != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int nColors = binaryReadInt16();
        for (int i = 0; i < nColors; i++) {
            readThread();
        }
        fseek(file, pecStart, SEEK_SET);
    }
    
    static void readPESHeaderV8()  {
        int pecStart = binaryReadInt32();
        fseek(file, 4, SEEK_CUR);
        readDescriptions();
        fseek(file, 38, SEEK_CUR);
        int fromImageStringLength = binaryReadByte();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(26);
        int nProgrammableFills = binaryReadInt16();
        if (nProgrammableFills != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int nMotifs = binaryReadInt16();
        if (nMotifs != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int featherPatternCount = binaryReadInt16();
        if (featherPatternCount != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int nColors = binaryReadInt16();
        for (int i = 0; i < nColors; i++) {
            readThread();
        }
        fseek(file, pecStart, SEEK_SET);
    }

    static void readPESHeaderV9()  {
        int pecStart = binaryReadInt32();
        fseek(file, 4, SEEK_CUR);
        readDescriptions();
        skip(14);
        int hoopNameStringLength = binaryReadByte();
        String hoopNameString = readString(hoopNameStringLength);
        if (hoopNameString.length() != 0) {
            pattern.setMetadata("hoop_name", hoopNameString);
        }
        skip(30);
        int fromImageStringLength = binaryReadByte();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(34);
        int nProgrammableFills = binaryReadInt16();
        if (nProgrammableFills != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int nMotifs = binaryReadInt16();
        if (nMotifs != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int featherPatternCount = binaryReadInt16();
        if (featherPatternCount != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int nColors = binaryReadInt16();
        for (int i = 0; i < nColors; i++) {
            readThread();
        }
        fseek(file, pecStart, SEEK_SET);
    }

    static void readPESHeaderV10()  {
        int pecStart = binaryReadInt32();
        fseek(file, 4, SEEK_CUR);
        readDescriptions();
        skip(14);
        int hoopNameStringLength = binaryReadByte();
        String hoopNameString = readString(hoopNameStringLength);
        if (hoopNameString.length() != 0) {
            pattern.setMetadata("hoop_name", hoopNameString);
        }
        fseek(file, 38, SEEK_CUR);
        int fromImageStringLength = binaryReadByte();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(34);
        int nProgrammableFills = binaryReadInt16();
        if (nProgrammableFills != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int nMotifs = binaryReadInt16();
        if (nMotifs != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int featherPatternCount = binaryReadInt16();
        if (featherPatternCount != 0) {
            fseek(file, pecStart, SEEK_SET);
            return;
        }
        int nColors = binaryReadInt16();
        for (int i = 0; i < nColors; i++) {
            readThread();
        }
        fseek(file, pecStart, SEEK_SET);
    }
    
    static void readThread() {
        int color_code_length = binaryReadByte();
        String color_code = readString(color_code_length);
        int red = binaryReadByte();
        int green = binaryReadByte();
        int blue = binaryReadByte();
        skip(5);
        int descriptionStringLength = binaryReadByte();
        String description = readString(descriptionStringLength);

        int brandStringLength = binaryReadByte();
        String brand = readString(brandStringLength);

        int threadChartStringLength = binaryReadByte();
        String threadChart = readString(threadChartStringLength);

        int color = (red & 0xFF) << 16 | (green & 0xFF) << 8 | (blue & 0xFF);
        pattern.add(new EmbThread(color, description, color_code, brand, threadChart));
    }
*/
static void pesWriteSewSegSection(EmbPattern* pattern, FILE* file, const char* fileName)
{
    /* TODO: pointer safety */
    FILE* colorInfo;
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
    EmbStitch st;

    /* TODO: why is this repeated below? */
    /*
    for (i=0; i<pattern->stitchList->length; i++) {
        j = i;
        flag = st.flags;
        embArray_get(pattern->threads, &t, st.color);
        newColorCode = embThread_findNearestColor_fromThread(t.color, pec_thread);
        if (newColorCode != colorCode) {
            colorCount++;
            colorCode = newColorCode;
        }
        while (i<pattern->stitchList->length && (flag == st.flags)) {
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

    colorInfo = tmpfile();
    for (i=0; i<colorCount*2; i++) {
        short s = 0;
        fwrite(&s, sizeof(short), 1, colorInfo);
    }

    colorCode = -1;
    blockCount = 0;
    for (i = 0; i < pattern->stitchList->length; i++) {
        EmbThread t;
        embArray_get(pattern->stitchList, &st, i);
        flag = st.flags;
        embArray_get(pattern->threads, &t, st.color);
        newColorCode = embThread_findNearestColor(t.color, pec_thread);
        if (newColorCode != colorCode) {
            short s;
            s = (short)blockCount;
            fwrite(&s, sizeof(short), 1, colorInfo);
            s = (short)newColorCode;
            fwrite(&s, sizeof(short), 1, colorInfo);
            colorCode = newColorCode;
        }
        /* TODO: check if this has an off-by-one error */
        for (count = 0; flag == st.flags; count++) {
            embArray_get(pattern->stitchList, &st, i + count);
        }

        /* 1 for jump, 0 for normal */
        stitchType = flag & JUMP;
        binaryWriteShort(file, (short)stitchType);
        /* color code */
        binaryWriteShort(file, (short)colorCode);
        /* stitches in block */
        binaryWriteShort(file, (short)count);
        for (; flag == st.flags && i < pattern->stitchList->length; i++) {
            embArray_get(pattern->stitchList, &st, i);
            binaryWriteShort(file, (short)(st.x - bounds.left));
            binaryWriteShort(file, (short)(st.y + bounds.top));
        }
        if (i < pattern->stitchList->length) {
            binaryWriteUShort(file, 0x8003);
        }
        blockCount++;
    }
    binaryWriteShort(file, (short)colorCount);
    embFile_copy(colorInfo, 0, file, 2*colorCount*sizeof(short));
    binaryWriteInt(file, 0);
    fclose(colorInfo);
}

static void pesWriteEmbOneSection(EmbPattern* pattern, FILE* file, const char* fileName)
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

static char writePes(EmbPattern* pattern, FILE* file, const char* fileName)
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

    pecLocation = ftell(file);
    fseek(file, 0x08, SEEK_SET);
    binaryWriteByte(file, (unsigned char)(pecLocation & 0xFF));
    binaryWriteByte(file, (unsigned char)(pecLocation >> 8) & 0xFF);
    binaryWriteByte(file, (unsigned char)(pecLocation >> 16) & 0xFF);
    fseek(file, 0x00, SEEK_END);
    writePecStitches(pattern, file, fileName);
    return 1;
}

static char readPhb(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned int fileOffset;
    short colorCount;
    int i;
    unsigned int intin;

    fseek(file, 0x71, SEEK_SET);
    embFile_readInt(file, &colorCount, 2);

    for (i = 0; i < colorCount; i++) {
        EmbThread t = load_thread(pec_thread, (int)binaryReadByte(file));
        embPattern_addThread(pattern, t);
    }

    /* TODO: check that file begins with #PHB */
    fseek(file, 0x54, SEEK_SET);
    embFile_readInt(file, &fileOffset, 4);
    fileOffset += 0x52;

    fseek(file, fileOffset, SEEK_SET);
    embFile_readInt(file, &intin, 4);
    fileOffset += intin + 2;

    fseek(file, fileOffset, SEEK_SET);
    embFile_readInt(file, &intin, 4);
    fileOffset += intin;

    fseek(file, fileOffset + 14, SEEK_SET); /* 28 */

    colorCount = (short)binaryReadByte(file);
    for (i = 0; i < colorCount; i++) {
        binaryReadByte(file);
    }
    fread(embBuffer, 1, 4, file); /* bytes to end of file */
    fseek(file, 17, SEEK_CUR);
    readPecStitches(pattern, file, fileName);

    embPattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhb */
}

static char writePhb(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writePhb */
}

static char readPhc(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int version, bytesInSection2;
    unsigned short pecOffset, bytesInSection, bytesInSection3, colorChanges;
    char pecAdd;
    EmbThread t;
    int i;

    fseek(file, 0x07, SEEK_SET);
    version = binaryReadByte(file) - 0x30; /* converting from ansi number */
    fseek(file, 0x4D, SEEK_SET);
    embFile_readInt(file, &colorChanges, 2);

    for (i = 0; i < colorChanges; i++) {
        t = load_thread(pec_thread, (int)binaryReadByte(file));
        embPattern_addThread(pattern, t);
    }
    fseek(file, 0x2B, SEEK_SET);
    pecAdd = binaryReadByte(file);
    int fileLength;
    embFile_readInt(file, &fileLength, 4);
    embFile_readInt(file, &pecOffset, 2);
    fseek(file, pecOffset + pecAdd, SEEK_SET);
    embFile_readInt(file, &bytesInSection, 2);
    fseek(file, bytesInSection, SEEK_CUR);
    embFile_readInt(file, &bytesInSection2, 4);
    fseek(file, bytesInSection2, SEEK_CUR);
    embFile_readInt(file, &bytesInSection3, 2);
    fseek(file, bytesInSection3 + 0x12, SEEK_CUR);

    readPecStitches(pattern, file, fileName);

    embPattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhc */
}

static char writePhc(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writePhc */
}

static char readPlt(EmbPattern* pattern, FILE* file, const char* fileName)
{
    float scalingFactor = 40;
    char input[512];

    embPattern_loadExternalColorFile(pattern, fileName);

    /* readline needs not to stop at \n, check the file format definition */
    while (!embFile_readline(file, input, 511)) {
        if (input[0] == 'P') {
            int flags, i, success;
            char *x_str, *y_str;
            float x, y;
            if (input[1] == 'D') flags = NORMAL;
            else if (input[1] == 'U') flags = STOP;
            else break;
            /* acts as sscanf call */
            x_str = input+2;
            for (i=0; i<511; i++) {
                if (input[i] == ',') {
                    input[i] = 0;
                    y_str = input+i+1;
                }
                if (input[i] == ';') {
                    input[i] = 0;
                    success = 1;
                }
            }
            if (!success) {
                break;
            }
            x = atof(x_str);
            y = atof(y_str);

            embPattern_addStitchAbs(pattern, x / scalingFactor, y / scalingFactor, flags, 1);
        }
    }
    return 1;
}

static char writePlt(EmbPattern* pattern, FILE* file, const char* fileName)
{
    /* TODO: pointer safety */
    float scalingFactor = 40;
    EmbStitch stitch;
    int i;
    char firstStitchOfBlock = 1;

    fprintf(file, "IN;ND;");

    for (i = 0; i < pattern->stitchList->length; i++) {
        embArray_get(pattern->stitchList, &stitch, i);
        if (stitch.flags & STOP) {
            firstStitchOfBlock = 1;
        }
        if (firstStitchOfBlock) {
            fprintf(file, "PU%1.5f,%1.5f", stitch.x * scalingFactor, stitch.y * scalingFactor);
            fprintf(file, ";ST0.00,0.00;SP0;HT0;HS0;TT0;TS0;");
            firstStitchOfBlock = 0;
        } else {
            fprintf(file, "PD%1.5f,%1.5f;", stitch.x * scalingFactor, stitch.y * scalingFactor);
        }
    }
    fprintf(file, "PU0.0,0.0;PU0.0,0.0;");

    return 1; /*TODO: finish WritePlt */
}

static char readRgb(EmbPattern* pattern, FILE* file, const char* fileName)
{
    EmbThread t;
    pattern->threads->length = 0;
    strcpy(t.catalogNumber, "NULL");
    strcpy(t.description, "NULL");
    while (fread(embBuffer, 1, 4, file) == 4) {
        t.color = embColor_fromStr(embBuffer);
        embPattern_addThread(pattern, t);
    }
    return 1;
}

static char writeRgb(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i;

    embBuffer[3] = 0;
    for (i = 0; i < pattern->threads->length; i++) {
        EmbThread t;
        embArray_get(pattern->threads, &t, i);
        embColor_toStr(t.color, embBuffer);
        fwrite(embBuffer, 1, 4, file);
    }
    return 1;
}

static char sewDecode(unsigned char inputByte)
{
    /* TODO: fix return statement */
    return (inputByte >= 0x80) ? (char)(-~(inputByte - 1)) : (char)inputByte;
}

static char readSew(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i, flags, nColors, fileLength;
    char dx, dy, thisStitchIsJump = 0;

    fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x00, SEEK_SET);
    nColors = binaryReadByte(file);
    nColors += (binaryReadByte(file) << 8);

    for (i = 0; i < nColors; i++) { 
    
        EmbThread t;
        short thread_number;
        embFile_readInt(file, &thread_number, 2);
        t = load_thread(jef_thread, thread_number);
        embPattern_addThread(pattern, t);
    }
    fseek(file, 0x1D78, SEEK_SET);

    for (i = 0; ftell(file) < fileLength; i++) {
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
    printf("current position: %d\n", (int)ftell(file));

    return 1;
}

static void sewEncode(unsigned char* b, char dx, char dy, int flags)
{
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
static char writeSew(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int colorlistSize, minColors, i;
    float xx, yy;

    colorlistSize = pattern->threads->length;

    minColors = emb_max_int(pattern->threads->length, 6);
    binaryWriteInt(file, 0x74 + (minColors * 4));
    binaryWriteInt(file, 0x0A);

    for (i = 0; i < pattern->threads->length; i++) {
        int thr;
        EmbThread t;
        embArray_get(pattern->threads, &t, i);
        thr = embThread_findNearestColor(t.color, jef_thread);
        binaryWriteInt(file, thr);
    }

    embFile_pad(file, 0x0D, (minColors - colorlistSize));
    embFile_pad(file, ' ', 7536);

    xx = 0.0;
    yy = 0.0;
    for (i = 0; i < pattern->stitchList->length; i++) {
        unsigned char b[4];
        float dx, dy;
        EmbStitch st;
        embArray_get(pattern->stitchList, &st, i);
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        sewEncode(b, (char)round(dx), (char)round(dy), st.flags);
        if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
            fwrite(b, 1, 4, file);
        } else {
            fwrite(b, 1, 2, file);
        }
    }
    return 1;
}

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

static char readShv(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i;
    char inJump = 0;
    unsigned char fileNameLength, designWidth, designHeight;
    char halfDesignWidth, halfDesignHeight, halfDesignWidth2, halfDesignHeight2;
    char* headerText = "Embroidery disk created using software licensed from Viking Sewing Machines AB, Sweden";
    char dx = 0, dy = 0;
    char nColors;
    unsigned short magicCode;
    int something;
    short left, top, right, bottom;
    char something2, numberOfSections, something3;
    int stitchesPerColor[256];
    int stitchesSinceChange = 0;
    int currColorIndex = 0;
    unsigned short sx, sy;

    fseek(file, strlen(headerText), SEEK_SET);
    fileNameLength = binaryReadUInt8(file);
    fseek(file, fileNameLength, SEEK_CUR);
    designWidth = binaryReadUInt8(file);
    designHeight = binaryReadUInt8(file);
    halfDesignWidth = binaryReadUInt8(file);
    halfDesignHeight = binaryReadUInt8(file);
    halfDesignWidth2 = binaryReadUInt8(file);
    halfDesignHeight2 = binaryReadUInt8(file);
    if ((designHeight % 2) == 1) {
        fseek(file, ((designHeight + 1) * designWidth) / 2, SEEK_CUR);
    } else {
        fseek(file, (designHeight * designWidth) / 2, SEEK_CUR);
    }
    nColors = binaryReadUInt8(file);
    embFile_readInt(file, &magicCode, 2);
    binaryReadByte(file);
    embFile_readInt(file, &something, 4);
    embFile_readInt(file, &left, 2);
    embFile_readInt(file, &top, 2);
    embFile_readInt(file, &right, 2);
    embFile_readInt(file, &bottom, 2);

    something2 = binaryReadByte(file);
    numberOfSections = binaryReadUInt8(file);
    something3 = binaryReadByte(file);

    for (i = 0; i < nColors; i++) {
        EmbThread t;
        unsigned int stitchCount, colorNumber;
        embFile_readInt_be(file, &stitchCount, 4);
        colorNumber = binaryReadUInt8(file);
        t = load_thread(shv_thread, colorNumber % 43);
        embPattern_addThread(pattern, t);
        stitchesPerColor[i] = stitchCount;
        fseek(file, 9, SEEK_CUR);
    }

    fseek(file, -2, SEEK_CUR);

    while (1) {
        unsigned char b0, b1;
        int flags;
        if (inJump) {
            flags = JUMP;
        } else {
            flags = NORMAL;
        }
        if (fread(embBuffer, 1, 2, file) != 2) break;
        b0 = embBuffer[0];
        b1 = embBuffer[1];
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

    embPattern_flipVertical(pattern);

    return 1;
}

static char writeShv(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeShv */
}

static char readSst(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int fileLength;

    embPattern_loadExternalColorFile(pattern, fileName);
    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0xA0, SEEK_SET); /* skip the all zero header */
    while (ftell(file) < fileLength) {
        int stitchType = NORMAL;

        int b1 = (int)binaryReadByte(file);
        int b2 = (int)binaryReadByte(file);
        unsigned char commandByte = binaryReadByte(file);

        if (commandByte == 0x04) {
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

static char writeSst(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeSst */
}

typedef struct SubDescriptor_ {
    int someNum; /* TODO: better variable naming */
    int someInt; /* TODO: better variable naming */
    int someOtherInt; /* TODO: better variable naming */
    char colorCode[40];
    char colorName[40];
} SubDescriptor;

typedef struct StxThread_ {
    char colorCode[40];
    char colorName[40];
    char sectionName[40];
    SubDescriptor subDescriptors[10];
    EmbColor stxColor;
} StxThread;

static char stxReadThread(StxThread* thread, FILE* file)
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
        puts("ERROR: stxReadThread(), thread==0\n");
        return 0;
    }
    if (!file) {
        puts("ERROR: stxReadThread(), file==0\n");
        return 0;
    }

    codeLength = binaryReadUInt8(file);
    fread(thread->colorCode, 1, codeLength, file); /* TODO: check return value */
    colorNameLength = binaryReadUInt8(file);
    fread(thread->colorName, 1, colorNameLength, file); /* TODO: check return value */

    col.r = binaryReadUInt8(file);
    col.b = binaryReadUInt8(file);
    col.g = binaryReadUInt8(file);

    whatIsthis = binaryReadUInt8(file);

    sectionNameLength = binaryReadUInt8(file);
    fread(thread->sectionName, 1, sectionNameLength, file); /* TODO: check return value */

    embFile_readInt(file, &somethingSomething, 4);
    embFile_readInt(file, &somethingSomething2, 4);
    embFile_readInt(file, &somethingElse, 4);
    embFile_readInt(file, &numberOfOtherDescriptors, 2);

    if (numberOfOtherDescriptors >= 10) {
        puts("Ran of out memory for descriptors.");
        return 0;
    }
    for (j = 0; j < numberOfOtherDescriptors; j++) {
        SubDescriptor sd;
        unsigned char subCodeLength, subColorNameLength;

        embFile_readInt(file, &(sd.someNum), 2);
        /* Debug.Assert(sd.someNum == 1); TODO: review */
        embFile_readInt(file, &(sd.someInt), 4);
        subCodeLength = binaryReadUInt8(file);
        fread(sd.colorCode, 1, subCodeLength, file); /* TODO: check return value */
        subColorNameLength = binaryReadUInt8(file);
        fread(sd.colorName, 1, subColorNameLength, file); /* TODO: check return value */
        embFile_readInt(file, &(sd.someOtherInt), 4);
        thread->subDescriptors[j] = sd;
    }
    return 1;
}

static char readStx(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i, threadCount;
    unsigned char* gif = 0;
    /* public bitmap Image; */
    StxThread stxThreads[100];
    unsigned char headerBytes[7];
    char* header = 0;
    char filetype[4], version[5];
    int paletteLength, imageLength, something1, stitchDataOffset, something3, threadDescriptionOffset, stitchCount, left, right, colors;
    int val[6], vala[6];
    int bottom, top;

    binaryReadBytes(file, headerBytes, 7); /* TODO: check return value */
    header = (char*)headerBytes;

    memcpy(filetype, &header[0], 3);
    memcpy(version, &header[3], 4);
    filetype[3] = '\0';
    version[4] = '\0';
    binaryReadByte(file);
    embFile_readInt(file, &paletteLength, 4);
    embFile_readInt(file, &imageLength, 4);
    embFile_readInt(file, &something1, 4);
    embFile_readInt(file, &stitchDataOffset, 4);
    embFile_readInt(file, &something3, 4);
    embFile_readInt(file, &threadDescriptionOffset, 4);
    embFile_readInt(file, &stitchCount, 4);
    embFile_readInt(file, &colors, 4);
    embFile_readInt(file, &right, 2);
    embFile_readInt(file, &left, 2);
    embFile_readInt(file, &bottom, 2);
    embFile_readInt(file, &top, 2);

    /* gif */
    fread(embBuffer, 1, imageLength, file); /* TODO: check return value */
    /*Stream s2 = new MemoryStream(gif); TODO: review */
    /*Image = new bitmap(s2); TODO: review */

    embFile_readInt(file, &threadCount, 2);
    for (i = 0; i < threadCount; i++) {
        EmbThread t;
        StxThread st;
        stxReadThread(&st, file);

        t.color = st.stxColor;
        strcpy(t.description, st.colorName);
        strcpy(t.catalogNumber, st.colorCode);
        embPattern_addThread(pattern, t);
        stxThreads[i] = st;
    }

    fread(embBuffer, 1, 15, file);

    for (i=0; i<6; i++) {
        embFile_readInt(file, val+i, 2);
    }
    /* last two val[4] = 0, val[5] = 0 */

    for (i=0; i<6; i++) {
        embFile_readInt(file, vala+i, 2);
    }
    /* last two vala[4] = 0, vala[5] = 0 */

    fread(embBuffer, 1, 8, file);

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
                /* TODO: Is this a synchronize? If so document it in the comments. */
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

static char writeStx(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeStx */
}

static char decodeT01RecordFlags(unsigned char b2)
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

static char readT01(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b[3];

    embPattern_loadExternalColorFile(pattern, fileName);

    while (fread(b, 1, 3, file) == 3) {
        int flags;
        int x[2];
        decode_dst_ternary(x, b);
        flags = decodeT01RecordFlags(b[2]);
        embPattern_addStitchRel(pattern, x[0] / 10.0, x[1] / 10.0, flags, 1);
        if (flags == END)
            break;
    }

    return 1;
}

static char writeT01(EmbPattern* pattern, FILE* file, const char* fileName)
{
    EmbRect boundingRect;
    int pos[2], i;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    boundingRect = embPattern_calcBoundingBox(pattern);

    pos[0] = 0;
    pos[1] = 0;
    for (i = 0; i < pattern->stitchList->length; i++) {
        unsigned char b[4];
        int dx[2];
        EmbStitch st;
        embArray_get(pattern->stitchList, &st, i);
        /* convert from mm to 0.1mm for file format */
        dx[0] = (int)round(st.x * 10.0) - pos[0];
        dx[1] = (int)round(st.y * 10.0) - pos[1];
        pos[0] = (int)round(st.x * 10.0);
        pos[1] = (int)round(st.y * 10.0);
        
        encode_dst_ternary(dx, b);

        b[2] |= (char)3;

        if (st.flags & END) {
            b[0] = 0;
            b[1] = 0;
            b[2] = 0xF3;
        }
        if (st.flags & (JUMP | TRIM)) {
            b[2] = (char)(b[2] | 0x83);
        }
        if (st.flags & STOP) {
            b[2] = (char)(b[2] | 0xC3);
        }

        fwrite(b, 1, 3, file);
    }
    return 1;
}

static char readT09(EmbPattern* pattern, FILE* file, const char* fileName)
{
    fseek(file, 0x0C, SEEK_SET);

    while (fread(embBuffer, 1, 3, file) == 3) {
        int stitchType = NORMAL;
        int b1 = embBuffer[0];
        int b2 = embBuffer[1];
        if (embBuffer[2] == 0x00) {
            break;
        }
        if (embBuffer[2] & 0x10)
            stitchType = STOP;
        if (embBuffer[2] & 0x20)
            b1 = -b1;
        if (embBuffer[2] & 0x40)
            b2 = -b2;

        embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }

    return 1;
}

static char writeT09(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeT09 */
}

static char decodeTapRecordFlags(unsigned char b2)
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

static int encode_dst_ternary(int *x, unsigned char *b)
{
    /* cannot encode values > +121 or < -121. */
    if (x[0] > 121 || x[0] < -121) {
        puts("ERROR: encode_dst_ternary(), x is not in valid range [-121,121]\n");
        return 0;
    }
    if (x[1] > 121 || x[1] < -121) {
        puts("ERROR: encode_dst_ternary(), y is not in valid range [-121,121]\n");
        return 0;
    }

    if (x[0] >= +41) {
        b[2] |= 1 << 2;
        x[0] -= 81;
    }
    if (x[0] <= -41) {
        b[2] |= 1 << 3;
        x[0] += 81;
    }
    if (x[0] >= +14) {
        b[1] |= 1 << 2;
        x[0] -= 27;
    }
    if (x[0] <= -14) {
        b[1] |= 1 << 3;
        x[0] += 27;
    }
    if (x[0] >= +5) {
        b[0] |= 1 << 2;
        x[0] -= 9;
    }
    if (x[0] <= -5) {
        b[0] |= 1 << 3;
        x[0] += 9;
    }
    if (x[0] >= +2) {
        b[1] |= 1 << 0;
        x[0] -= 3;
    }
    if (x[0] <= -2) {
        b[1] |= 1 << 1;
        x[0] += 3;
    }
    if (x[0] >= +1) {
        b[0] |= 1 << 0;
        x[0] -= 1;
    }
    if (x[0] <= -1) {
        b[0] |= 1 << 1;
        x[0] += 1;
    }
    if (x[0] != 0) {
        puts("ERROR: encode_tap_record(), x!=0\n");
        return 0;
    }
    if (x[1] >= +41) {
        b[2] |= 1 << 5;
        x[1] -= 81;
    }
    if (x[1] <= -41) {
        b[2] |= 1 << 4;
        x[1] += 81;
    }
    if (x[1] >= +14) {
        b[1] |= 1 << 5;
        x[1] -= 27;
    }
    if (x[1] <= -14) {
        b[1] |= 1 << 4;
        x[1] += 27;
    }
    if (x[1] >= +5) {
        b[0] |= 1 << 5;
        x[1] -= 9;
    }
    if (x[1] <= -5) {
        b[0] |= 1 << 4;
        x[1] += 9;
    }
    if (x[1] >= +2) {
        b[1] |= 1 << 7;
        x[1] -= 3;
    }
    if (x[1] <= -2) {
        b[1] |= 1 << 6;
        x[1] += 3;
    }
    if (x[1] >= +1) {
        b[0] |= 1 << 7;
        x[1] -= 1;
    }
    if (x[1] <= -1) {
        b[0] |= 1 << 6;
        x[1] += 1;
    }
    if (x[1] != 0) {
        puts("ERROR: encode_tap_record(), y!=0\n");
        return 0;
    }
    return 1;
}

/* A version of the stitch decoding with less branching,
 * the BIT macro returns either 0 or 1 based on the value
 * of that bit and then is multiplied by what value that represents.
 */
static void decode_dst_ternary(int *x, unsigned char *b)
{
    x[0]  =     bit(b[0], 0) - bit(b[0], 1);
    x[0] +=  9*(bit(b[0], 2) - bit(b[0], 3));
    x[1]  =     bit(b[0], 7) - bit(b[0], 6);
    x[1] +=  9*(bit(b[0], 5) - bit(b[0], 4));
    x[0] +=  3*(bit(b[1], 0) - bit(b[1], 1));
    x[0] += 27*(bit(b[1], 2) - bit(b[1], 3));
    x[1] +=  3*(bit(b[1], 7) - bit(b[1], 6));
    x[1] += 27*(bit(b[1], 5) - bit(b[1], 4));
    x[0] += 81*(bit(b[2], 2) - bit(b[2], 3));
    x[1] += 81*(bit(b[2], 5) - bit(b[2], 4));
}

static char readTap(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b[3];

    embPattern_loadExternalColorFile(pattern, fileName);

    while (fread(b, 1, 3, file) == 3) {
        int flags;
        int x[2];
        decode_dst_ternary(x, b);
        flags = decodeTapRecordFlags(b[2]);
        embPattern_addStitchRel(pattern, x[0] / 10.0, x[1] / 10.0, flags, 1);
        if (flags == END)
            break;
    }

    return 1;
}

static char writeTap(EmbPattern* pattern, FILE* file, const char* fileName)
{
    EmbRect boundingRect;
    int pos[2], i;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    boundingRect = embPattern_calcBoundingBox(pattern);

    pos[0] = 0;
    pos[1] = 0;
    for (i = 0; i < pattern->stitchList->length; i++) {
        unsigned char b[3];
        int dx[2];
        EmbStitch st;
        embArray_get(pattern->stitchList, &st, i);
        /* convert from mm to 0.1mm for file format */
        dx[0] = (int)round(st.x * 10.0) - pos[0];
        dx[1] = (int)round(st.y * 10.0) - pos[1];
        pos[0] = (int)round(st.x * 10.0);
        pos[1] = (int)round(st.y * 10.0);

        encode_dst_ternary(dx, b);

        b[2] |= (char)3;

        if (st.flags & END) {
            b[0] = 0;
            b[1] = 0;
            b[2] = 0xF3;
        }
        if (st.flags & (JUMP | TRIM)) {
            b[2] = (char)(b[2] | 0x83);
        }
        if (st.flags & STOP) {
            b[2] = (char)(b[2] | 0xC3);
        }

        fwrite(b, 1, 3, file);
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
    char auxFormat; /* auxiliary file format, 0=PCS,1=DST,2=PES */
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

static char readThr(EmbPattern* pattern, FILE* file, const char* fileName)
{
    ThredHeader header;
    /* EmbColor c; */
    EmbThread thread;
    int currentColor, i;

    embFile_readInt(file, &header.sigVersion, 4);
    embFile_readInt(file, &header.length, 4);
    embFile_readInt(file, &header.numStiches , 2);
    embFile_readInt(file, &header.hoopSize, 2);
    for (i=0; i<7; i++) {
        embFile_readInt(file, header.reserved + i, 2);
    }

    if ((header.sigVersion & 0xffffff) == 0x746872) {
        unsigned int verVar = (header.sigVersion & 0xff000000) >> 24;
        switch (verVar) {
        case 0:
            break;
        case 1:
        case 2:
            fseek(file, 144, SEEK_CUR); /* skip the file header extension */
            break;
        default:
            return 0; /* unsupported version */
        }
    }

    currentColor = -1;
    for (i = 0; i < header.numStiches; i++) {
        int type = NORMAL;
        float x = binaryReadFloat(file) / 10.0f;
        float y = binaryReadFloat(file) / 10.0f;
        unsigned int color;
        embFile_readInt(file, &color, 4);

        if ((int)(color & 0xF) != currentColor) {
            currentColor = (int)color & 0xF;
            embPattern_changeColor(pattern, currentColor);
            type = STOP | TRIM;
        }
        embPattern_addStitchAbs(pattern, x, y, type, 0);
    }
    fseek(file, 16, SEEK_CUR); /* skip bitmap name (16 chars) */

    fread(embBuffer, 1, 4, file);
    /* background color: c = embColor_fromStr(embBuffer); */

    strcpy(thread.description, "NULL");
    strcpy(thread.catalogNumber, "NULL");
    fread(embBuffer, 1, 16*4, file);
    for (i = 0; i < 16; i++) {
        thread.color = embColor_fromStr(embBuffer+4*i);
        embPattern_addThread(pattern, thread);
    }
    /*  64 bytes of rgbx(4 bytes) colors (16 custom colors) */
    /*  16 bytes of thread size (ascii representation ie. '4') */

    return 1;
}

static char writeThr(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i, stitchCount;
    unsigned char version = 0;
    ThredHeader header;
    ThredExtension extension;
    char bitmapName[16];
    EmbStitch st;

    stitchCount = pattern->stitchList->length;

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
    for (i=0; i<7; i++) {
        binaryWriteUShort(file, header.reserved[i]);
    }

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
    for (i = 0; i < pattern->stitchList->length; i++) {
        embArray_get(pattern->stitchList, &st, i);
        binaryWriteFloat(file, (float)(st.x * 10.0));
        binaryWriteFloat(file, (float)(st.y * 10.0));
        binaryWriteUInt(file, NOTFRM | (st.color & 0x0F));
    }
    binaryWriteBytes(file, bitmapName, 16);
    /* background color */
    fread("\xFF\xFF\xFF\x00", 1, 4, file);

    embPattern_colorBlock16(pattern, file);

    embFile_pad(file, '4', 16);

    return 1;
}

static char readTxt(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish readTxt */
}

static char writeTxt(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i;
    fprintf(file, "%d\n", pattern->stitchList->length);

    for (i = 0; i < pattern->stitchList->length; i++) {
        EmbStitch st;
        embArray_get(pattern->stitchList, &st, i);
        fprintf(file, "%.1f,%.1f color:%i flags:%i\n", st.x, st.y, st.color, st.flags);
    }
    return 1;
}

static void encode_u00_stitch(EmbStitch st, unsigned char *data)
{
    char dx, dy;
    dx = (char)round(10.0*st.x);
    dy = (char)round(10.0*st.y);
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

static char readU00(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int i;

    /* 16 3byte RGB's start @ 0x08 followed by 14 bytes between 0 and 15 with index of color for each color change */
    fseek(file, 0x08, SEEK_SET);

    for (i = 0; i < 16; i++) {
        EmbThread t;
        fread(embBuffer, 1, 3, file);
        t.color = embColor_fromStr(embBuffer);
        embPattern_addThread(pattern, t);
    }

    fseek(file, 0x100, SEEK_SET);
    while (fread(embBuffer, 1, 3, file) == 3) {
        EmbStitch st;
        st = decode_u00_stitch(embBuffer);
        if (st.flags == END) {
            break;
        }
        embPattern_addStitchRel(pattern, st.x, st.y, st.flags, 1);
    }

    return 1;
}

static char writeU00(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b[4];
    int i;

    embFile_pad(file, ' ', 8);

    for (i = 0; i < pattern->threads->length; i++) {
        EmbThread t;
        embArray_get(pattern->threads, &t, i);
        embColor_toStr(t.color, b);
        fwrite(b, 1, 3, file);
    }

    /* this should pad to 256 bytes */
    embFile_pad(file, ' ', 0x100 - 3*pattern->threads->length - 8);

    for (i = 0; i < pattern->stitchList->length; i++) {
        EmbStitch st;
        embArray_get(pattern->stitchList, &st, i);
        encode_u00_stitch(st, b);
        fwrite(b, 1, 3, file);
    }
    return 1;
}

static char readU01(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return readU00(pattern, file, fileName);
}

static char writeU01(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return writeU00(pattern, file, fileName);
}

static char vipDecodeByte(unsigned char b)
{
    if (b >= 0x80)
        return (-(unsigned char)(~b + 1));
    return b;
}

static char vipDecodeStitchType(unsigned char b)
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

typedef struct VipHeader_ {
    int magicCode;
    int numberOfStitches;
    int nColors;
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

static char readVip(EmbPattern* pattern, FILE* file, const char* fileName)
{
    int fileLength;
    int i;
    unsigned char prevByte = 0;
    FILE* attributeData;
    FILE* attributeDataDecompressed;
    FILE* decodedColors;
    FILE* xData;
    FILE* xDecompressed;
    FILE* yData;
    FILE* yDecompressed;
    VipHeader header;

    fseek(file, 0x0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x00, SEEK_SET);
    embFile_readInt(file, &(header.magicCode), 4);
    embFile_readInt(file, &(header.numberOfStitches), 4);
    embFile_readInt(file, &(header.nColors), 4);

    embFile_readInt(file, &(header.postitiveXHoopSize), 2);
    embFile_readInt(file, &(header.postitiveYHoopSize), 2);
    embFile_readInt(file, &(header.negativeXHoopSize), 2);
    embFile_readInt(file, &(header.negativeYHoopSize), 2);

    embFile_readInt(file, &(header.attributeOffset), 4);
    embFile_readInt(file, &(header.xOffset), 4);
    embFile_readInt(file, &(header.yOffset), 4);

    /*stringVal = embBuffer; TODO: review this and uncomment or remove
     */

    binaryReadBytes(file, header.stringVal, 8); /* TODO: check return value */

    embFile_readInt(file, &(header.unknown), 2);
    embFile_readInt(file, &(header.colorLength), 4);

    fseek(datafile, vip_decoding_table, SEEK_SET);
    fread(embBuffer, 1, header.nColors*4, datafile);
    for (i = 0; i < header.nColors * 4; ++i) {
        unsigned char inputByte = binaryReadByte(file);
        unsigned char tmpByte = (unsigned char)(inputByte ^ embBuffer[i]);
        unsigned char c = (unsigned char)(tmpByte ^ prevByte);
        fwrite(&c, 1, 1, decodedColors);
        prevByte = inputByte;
    }
    for (i = 0; i < header.nColors; i++) {
        EmbThread thread;
        int startIndex = i << 2;
        fseek(decodedColors, startIndex, SEEK_SET);
        fread(&(thread.color.r), 1, 1, decodedColors);
        fread(&(thread.color.g), 1, 1, decodedColors);
        fread(&(thread.color.b), 1, 1, decodedColors);
        /* printf("%d\n", decodedColors[startIndex + 3]); */
        embPattern_addThread(pattern, thread);
    }

    embFile_copy(file, header.attributeOffset, attributeData, header.xOffset - header.attributeOffset); /* TODO: check return value */
    husExpand(attributeData, attributeDataDecompressed, 10);

    embFile_copy(file, header.xOffset, xData, header.yOffset - header.xOffset); /* TODO: check return value */
    husExpand(xData, xDecompressed, 10);

    embFile_copy(file, header.yOffset, yData, fileLength - header.yOffset); /* TODO: check return value */
    husExpand(yData, yDecompressed, 10);

    for (i = 0; i < header.numberOfStitches; i++) {
        unsigned char cx, cy, catt;
        float x, y;
        int attribute;
        fread(&cx, 1, 1, xDecompressed);
        fread(&cy, 1, 1, yDecompressed);
        fread(&catt, 1, 1, attributeDataDecompressed);
        x = vipDecodeByte(cx);
        y = vipDecodeByte(cy);
        attribute = vipDecodeStitchType(catt);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, attribute, 1);
    }

    fclose(attributeData);
    fclose(xData);
    fclose(yData);
    fclose(attributeDataDecompressed);
    fclose(xDecompressed);
    fclose(yDecompressed);

    return 1;
}

static unsigned char vipEncodeByte(float f)
{
    return (unsigned char)round(f);
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

static char writeVip(EmbPattern* pattern, FILE* file, const char* fileName)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor, attributeSize = 0,
        xCompressedSize = 0, yCompressedSize = 0;
    EmbVector previous;
    EmbStitch st;
    int i;
    FILE* xValues;
    FILE* yValues;
    FILE* attributeValues;
    FILE* xCompressed;
    FILE* yCompressed;
    FILE* attributeCompressed;
    FILE* decodedColors;
    unsigned char prevByte = 0;

    stitchCount = pattern->stitchList->length;
    minColors = pattern->threads->length;
    /* embPattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */

    patternColor = minColors;
    if (minColors > 24)
        minColors = 24;

    binaryWriteUInt(file, 0x0190FC5D);
    binaryWriteUInt(file, stitchCount);
    binaryWriteUInt(file, minColors);

    boundingRect = embPattern_calcBoundingBox(pattern);
    binaryWriteShort(file, (short)round(boundingRect.right * 10.0));
    binaryWriteShort(file, (short)-round(boundingRect.top * 10.0 - 1.0));
    binaryWriteShort(file, (short)round(boundingRect.left * 10.0));
    binaryWriteShort(file, (short)-round(boundingRect.bottom * 10.0 - 1.0));

    binaryWriteUInt(file, 0x38 + (minColors << 3));

    previous.x = 0.0;
    previous.y = 0.0;
    for (i = 0; i < pattern->stitchList->length; i++) {
        unsigned char c;
        embArray_get(pattern->stitchList, &st, i);
        c = vipEncodeByte((st.x - previous.x) * 10.0);
        fwrite(&c, 1, 1, xValues);
        c = vipEncodeByte((st.y - previous.y) * 10.0);
        fwrite(&c, 1, 1, yValues);
        previous.x = st.x;
        previous.y = st.y;
        c = vipEncodeStitchType(st.flags);
        fwrite(&c, 1, 1, attributeValues);
    }
    attributeSize = husCompress(attributeValues, attributeCompressed, 10);
    xCompressedSize = husCompress(xValues, xCompressed, 10);
    yCompressedSize = husCompress(yValues, yCompressed, 10);

    binaryWriteUInt(file, (unsigned int)(0x38 + (minColors << 3) + attributeSize));
    binaryWriteUInt(file, (unsigned int)(0x38 + (minColors << 3) + attributeSize + xCompressedSize));
    embFile_pad(file, 0, 10);

    binaryWriteInt(file, minColors << 2);

    for (i = 0; i < minColors; i++) {
        EmbThread t;
        int byteChunk = i << 2;
        embArray_get(pattern->threads, &t, i);
        binaryWriteByte(decodedColors, t.color.r);
        binaryWriteByte(decodedColors, t.color.g);
        binaryWriteByte(decodedColors, t.color.b);
        binaryWriteByte(decodedColors, 0x01);
    }

    fseek(datafile, vip_decoding_table, SEEK_SET);
    fread(embBuffer, 1, minColors << 2, datafile);
    for (i = 0; i < minColors << 2; ++i) {
        unsigned char color;
        fread(&color, 1, 1, decodedColors);
        unsigned char tmpByte = (unsigned char)(color ^ embBuffer[i]);
        prevByte = (unsigned char)(tmpByte ^ prevByte);
        binaryWriteByte(file, prevByte);
    }
    for (i = 0; i <= minColors; i++) {
        binaryWriteInt(file, 1);
    }
    binaryWriteUInt(file, 0); /* string length */
    binaryWriteShort(file, 0);
    embFile_copy(attributeCompressed, 0, file, attributeSize);
    embFile_copy(xCompressed, 0, file, xCompressedSize);
    embFile_copy(yCompressed, 0, file, yCompressedSize);

    fclose(attributeCompressed);
    fclose(xCompressed);
    fclose(yCompressed);
    fclose(attributeValues);
    fclose(xValues);
    fclose(yValues);
    fclose(decodedColors);

    return 1;
}

static unsigned char* vp3ReadString(FILE* file)
{
    short stringLength;
    if (!file) {
        puts("ERROR: vp3ReadString(), file==0\n");
        return 0;
    }
    embFile_readInt_be(file, &stringLength, 2);
    fread(embBuffer, 1, stringLength, file); /* TODO: check return value */
    return embBuffer;
}

static char vp3Decode(unsigned char inputByte)
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
    unsigned char nColors;
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

static vp3Hoop vp3ReadHoopSection(FILE* file)
{
    vp3Hoop hoop;

    if (!file) {
        puts("ERROR: vp3ReadHoopSection(), file==0\n");
        hoop.bottom = 0;
        hoop.left = 0;
        hoop.right = 0;
        hoop.top = 0;
        return hoop;
    }

    embFile_readInt_be(file, &(hoop.right), 4);
    embFile_readInt_be(file, &(hoop.left), 4);
    embFile_readInt_be(file, &(hoop.bottom), 4);
    embFile_readInt_be(file, &(hoop.top), 4);

    embFile_readInt(file, &hoop.threadLength, 4); /* yes, it seems this is _not_ big endian */
    hoop.unknown2 = binaryReadByte(file);
    hoop.nColors = binaryReadByte(file);
    embFile_readInt_be(file, &(hoop.unknown3), 2);
    embFile_readInt_be(file, &(hoop.unknown4), 4);
    embFile_readInt_be(file, &(hoop.numberOfBytesRemaining), 4);

    embFile_readInt_be(file, &(hoop.xOffset), 4);
    embFile_readInt_be(file, &(hoop.yOffset), 4);

    hoop.byte1 = binaryReadByte(file);
    hoop.byte2 = binaryReadByte(file);
    hoop.byte3 = binaryReadByte(file);

    /* Centered hoop dimensions */
    embFile_readInt_be(file, &(hoop.right2), 4);
    embFile_readInt_be(file, &(hoop.left2), 4);
    embFile_readInt_be(file, &(hoop.bottom2), 4);
    embFile_readInt_be(file, &(hoop.top2), 4);

    embFile_readInt_be(file, &(hoop.width), 4);
    embFile_readInt_be(file, &(hoop.height), 4);
    return hoop;
}

static char readVp3(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char magicString[5];
    unsigned char some;
    unsigned char* softwareVendorString = 0;
    unsigned char v1[18];
    unsigned char* anotherSoftwareVendorString = 0;
    int nColors;
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
    embFile_readInt(file, &someShort, 2);
    someByte = binaryReadByte(file);
    embFile_readInt(file, &bytesRemainingInFile, 4);
    fileCommentString = vp3ReadString(file);
    hoopConfigurationOffset = (int)ftell(file);

    vp3ReadHoopSection(file);

    anotherCommentString = vp3ReadString(file);

    /* TODO: review v1 thru v18 variables and use emb_unused() if needed */
    fread(v1, 1, 18, file);

    binaryReadBytes(file, magicCode, 6);
    if (!(magicCode[5] == 0 && string_equal("\x78\x78\x55\x55\x01", magicCode))) {
        return 0;
    }

    anotherSoftwareVendorString = vp3ReadString(file);

    embFile_readInt_be(file, &nColors, 2);
    puts("ERROR: Number of Colors: %d\n" /*, nColors */);
    colorSectionOffset = (int)ftell(file);

    for (i = 0; i < nColors; i++) {
        EmbThread t;
        char tableSize;
        int startX, startY, offsetToNextColorX, offsetToNextColorY;
        unsigned char *threadColorNumber, *colorName, *threadVendor;
        int unknownThreadString;

        fseek(file, colorSectionOffset, SEEK_SET);
        fread(embBuffer, 1, 3, file);
        puts("ERROR: Color Check Byte #1: 0 == %d\n");
        puts("ERROR: Color Check Byte #2: 5 == %d\n");
        puts("ERROR: Color Check Byte #3: 0 == %d\n");
        embFile_readInt_be(file, &colorSectionOffset, 4);
        colorSectionOffset += ftell(file);
        embFile_readInt_be(file, &startX, 4);
        embFile_readInt_be(file, &startY, 4);
        embPattern_addStitchAbs(pattern, startX / 1000.0, -startY / 1000.0, JUMP, 1);

        tableSize = binaryReadByte(file);
        binaryReadByte(file);
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        embPattern_addThread(pattern, t);
        fseek(file, 6 * tableSize - 1, SEEK_CUR);

        threadColorNumber = vp3ReadString(file);
        colorName = vp3ReadString(file);
        threadVendor = vp3ReadString(file);

        embFile_readInt_be(file, &offsetToNextColorX, 4);
        embFile_readInt_be(file, &offsetToNextColorY, 4);

        embFile_readInt_be(file, &unknownThreadString, 2);
        fseek(file, unknownThreadString, SEEK_CUR);
        /*
        embFile_readInt_be(file, &numberOfBytesInColor, 4);
        fseek(file, 0x3, SEEK_CUR);
        */
        fseek(file, 0x7, SEEK_CUR);
        while (ftell(file) < colorSectionOffset - 1) {
            int lastFilePosition = ftell(file);

            int x = vp3Decode(binaryReadByte(file));
            int y = vp3Decode(binaryReadByte(file));
            if (x == 0x80) {
                switch (y) {
                case 0x00:
                case 0x03:
                    break;
                case 0x01:
                    {
                    unsigned short sh;
                    embFile_readInt_be(file, &sh, 2);
                    x = vp3DecodeInt16(sh);
                    embFile_readInt_be(file, &sh, 2);
                    y = vp3DecodeInt16(sh);
                    fread(embBuffer, 1, 2, file); /* binaryReadInt16BE(file); */
                    embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, TRIM, 1);
                    }
                    break;
                default:
                    break;
                }
            } else {
                embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, NORMAL, 1);
            }

            if (ftell(file) == lastFilePosition) {
                puts("ERROR: format-vp3.c could not read stitch block in entirety\n");
                return 0;
            }
        }
        if (i + 1 < nColors)
            embPattern_addStitchRel(pattern, 0, 0, STOP, 1);
    }

    embPattern_flipVertical(pattern);

    return 1;
}

void vp3WriteStringLen(FILE* file, const char* str, int len)
{
    short sh = (short)len;
    embFile_writeInt_be(file, &sh, 2);
    fwrite(str, 1, len, file);
}

void vp3WriteString(FILE* file, const char* str)
{
    vp3WriteStringLen(file, str, strlen(str));
}

void vp3PatchByteCount(FILE* file, int offset, int adjustment)
{
    int i;
    int currentPos = ftell(file);
    fseek(file, offset, SEEK_SET);
    i = currentPos - offset + adjustment;
    puts("Patching byte count: \n" /*, i */);
    embFile_writeInt_be(file, &i, 4);
    fseek(file, currentPos, SEEK_SET);
}

static char writeVp3(EmbPattern* pattern, FILE* file, const char* fileName)
{
    EmbRect bounds;
    EmbStitch st;
    int remainingBytesPos, remainingBytesPos2, colorSectionStitchBytes,
        first, i, flag, intout;
    short nColors;
    EmbColor newColor, color = { 0xFE, 0xFE, 0xFE };
    first = 1;
    nColors = 0;

    bounds = embPattern_calcBoundingBox(pattern);

    embPattern_correctForMaxStitchLength(pattern, 3200.0, 3200.0); /* VP3 can encode signed 16bit deltas */

    embPattern_flipVertical(pattern);

    binaryWriteBytes(file, "%vsm%", 5);
    binaryWriteByte(file, 0);
    vp3WriteString(file, "Embroidermodder");
    binaryWriteByte(file, 0);
    binaryWriteByte(file, 2);
    binaryWriteByte(file, 0);

    remainingBytesPos = ftell(file);
    binaryWriteInt(file, 0); /* placeholder */
    vp3WriteString(file, "");
    intout = bounds.right * 1000;
    embFile_writeInt_be(file, &intout, 4);
    intout = bounds.bottom * 1000;
    embFile_writeInt_be(file, &intout, 4);
    intout = bounds.left * 1000;
    embFile_writeInt_be(file, &intout, 4);
    intout = bounds.top * 1000;
    embFile_writeInt_be(file, &intout, 4);
    binaryWriteInt(file, 0); /* this would be some (unknown) function of thread length */
    binaryWriteByte(file, 0);

    nColors = 0;

    for (i = 0; i < pattern->stitchList->length; i++) {
        embArray_get(pattern->stitchList, &st, i);

        /* pointer = mainPointer; */
        flag = st.flags;
        EmbThread t;
        embArray_get(pattern->threads, &t, st.color);
        newColor = t.color;
        if (newColor.r != color.r || newColor.g != color.g || newColor.b != color.b) {
            nColors++;
            color = newColor;
        } else if (flag & END || flag & STOP) {
            nColors++;
        }

        while (flag == st.flags) {
            i++;
            embArray_get(pattern->stitchList, &st, i);
        }
        /* mainPointer = pointer; */
    }

    binaryWriteByte(file, nColors);
    fwrite("\x0C\x00\x01\x00\x03\x00", 1, 6, file);

    remainingBytesPos2 = ftell(file);
    embFile_pad(file, 0, 4); /* placeholder */

    embFile_pad(file, 0, 4); /* origin X */
    embFile_pad(file, 0, 4); /* origin Y */
    embFile_pad(file, 0, 3);

    intout = bounds.right * 1000;
    embFile_writeInt_be(file, &intout, 4);
    intout = bounds.bottom * 1000;
    embFile_writeInt_be(file, &intout, 4);
    intout = bounds.left * 1000;
    embFile_writeInt_be(file, &intout, 4);
    intout = bounds.top * 1000;
    embFile_writeInt_be(file, &intout, 4);

    intout = (bounds.right - bounds.left) * 1000;
    embFile_writeInt_be(file, &intout, 4);
    intout = (bounds.bottom - bounds.top) * 1000;
    embFile_writeInt_be(file, &intout, 4); 

    vp3WriteString(file, "");
    short sh = 25700;
    embFile_writeInt_be(file, &sh, 2);
    intout = 4096;
    embFile_writeInt_be(file, &intout, 4);
    embFile_pad(file, 0, 8);
    embFile_writeInt_be(file, &intout, 4);

    fwrite("xxPP\x01\0", 1, 6, file);
    vp3WriteString(file, "");
    embFile_writeInt_be(file, &nColors, 2);

    for (i = 0; i < pattern->stitchList->length; i++) {
        char colorName[8] = { 0 };
        float lastX, lastY;
        int colorSectionLengthPos;
        EmbStitch s, s1;
        int lastColor;

        if (!first) {
            binaryWriteByte(file, 0);
        }
        binaryWriteByte(file, 0);
        binaryWriteByte(file, 5);
        binaryWriteByte(file, 0);

        colorSectionLengthPos = ftell(file);
        binaryWriteInt(file, 0); /* placeholder */

        /* pointer = mainPointer; */
        EmbThread t;
        embArray_get(pattern->threads, &t, st.color);
        color = t.color;

        embArray_get(pattern->stitchList, &s1, i);
        if (first && (st.flags & JUMP) && s1.flags & JUMP) {
            i++;
        }

        embArray_get(pattern->stitchList, &s, i);
        printf("format-vp3.c DEBUG %d, %lf, %lf\n", s.flags, s.x, s.y);
        intout = s.x*1000;
        embFile_writeInt_be(file, &intout, 4);
        intout = -s.y*1000;
        embFile_writeInt_be(file, &intout, 4);
        /* pointer = pointer->next; */

        first = 0;

        lastX = s.x;
        lastY = s.y;
        lastColor = s.color;

        binaryWriteByte(file, 1);
        binaryWriteByte(file, 0);

        printf("format-vp3.c writeVp3(), switching to color (%d, %d, %d)\n", color.r, color.g, color.b);
        binaryWriteByte(file, color.r);
        binaryWriteByte(file, color.g);
        binaryWriteByte(file, color.b);

        binaryWriteByte(file, 0);
        binaryWriteByte(file, 0);
        binaryWriteByte(file, 0);
        binaryWriteByte(file, 5);
        binaryWriteByte(file, 40);

        vp3WriteString(file, "");
        
        char hex[] = "0123456789ABCDEF";
        colorName[0] = '#';
        colorName[1] = hex[color.b % 16];
        colorName[2] = hex[color.b / 16];
        colorName[3] = hex[color.g % 16];
        colorName[4] = hex[color.g / 16];
        colorName[5] = hex[color.r % 16];
        colorName[6] = hex[color.r / 16];
        colorName[7] = 0;

        vp3WriteString(file, colorName);
        vp3WriteString(file, "");

        embFile_pad(file, 0, 8);

        vp3WriteStringLen(file, "\0", 1);

        colorSectionStitchBytes = ftell(file);
        binaryWriteInt(file, 0); /* placeholder */

        binaryWriteByte(file, 10);
        binaryWriteByte(file, 246);
        binaryWriteByte(file, 0);

        for (i = 0; i < pattern->stitchList->length; i++) {
            short dx, dy;

            EmbStitch s;
            embArray_get(pattern->stitchList, &s, i);

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
                embFile_writeInt_be(file, &dx, 2);
                embFile_writeInt_be(file, &dy, 2);
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

static char readXxx(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b[4], b0, b1;
    int flags, paletteOffset, i;
    short nColors, dx, dy;
    char endOfStream = 0, thisStitchJump = 0;
    EmbThread thread;

    fseek(file, 0x27, SEEK_SET);
    embFile_readInt(file, &nColors, 2);
    fseek(file, 0xFC, SEEK_SET);
    embFile_readInt(file, &paletteOffset, 4);
    fseek(file, paletteOffset + 6, SEEK_SET);

    for (i = 0; i < nColors; i++) {
        fread(b, 1, 4, file);
        thread.color = embColor_fromStr(b);
        embPattern_addThread(pattern, thread);
    }
    fseek(file, 0x100, SEEK_SET);

    dx = 0;
    dy = 0;
    for (i = 0; !endOfStream && ftell(file) < paletteOffset; i++) {
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
            embFile_readInt(file, &dy, 2);
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
            lastStitch = 0;
            secondLast->next = NULL;
            embPattern_changeColor(pattern, pattern->currentColorIndex - 1);
        }
    }
    
    Is this trimming the last stitch... and?
    */

    return 1;
}

static void xxxEncodeStop(FILE* file, EmbStitch s)
{
    binaryWriteByte(file, (unsigned char)0x7F);
    binaryWriteByte(file, (unsigned char)(s.color + 8));
}

static void xxxEncodeStitch(FILE* file, float deltaX, float deltaY, int flags)
{
    if ((flags & (JUMP | TRIM)) && (fabs(deltaX) > 124 || fabs(deltaY) > 124)) {
        binaryWriteByte(file, 0x7E);
        binaryWriteShort(file, (short)deltaX);
        binaryWriteShort(file, (short)deltaY);
    } else {
        /* TODO: Verify this works after changing this to unsigned char */
        binaryWriteByte(file, (unsigned char)round(deltaX));
        binaryWriteByte(file, (unsigned char)round(deltaY));
    }
}

static void xxxEncodeDesign(FILE* file, EmbPattern* p)
{
    float thisX = 0.0f;
    float thisY = 0.0f;
    float previousX, previousY, deltaX, deltaY;
    int i;

    if (p->stitchList) {
        EmbStitch s;
        embArray_get(p->stitchList, &s, 0);
        thisX = s.x;
        thisY = s.y;
    } else {
        return;
    }

    for (i = 0; i < p->stitchList->length; i++) {
        EmbStitch s;
        embArray_get(p->stitchList, &s, i);
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
        embArray_set(p->stitchList, &s, i);
    }
}

static char writeXxx(EmbPattern* pattern, FILE* file, const char* fileName)
{
    char i;
    EmbRect rect;
    int endOfStitches;
    unsigned char b[4];
    short sh;

    embPattern_correctForMaxStitchLength(pattern, 124, 127);

    embFile_pad(file, 0, 0x17);
    binaryWriteUInt(file, (unsigned int)pattern->stitchList->length);
    embFile_pad(file, 0, 0x0C);
    binaryWriteUShort(file, (unsigned short)pattern->threads->length);
    embFile_pad(file, 0, 2);

    rect = embPattern_calcBoundingBox(pattern);
    sh = (short)(embRect_width(rect) * 10.0);
    embFile_writeInt(file, &sh, 2);
    sh = (short)(embRect_height(rect) * 10.0);
    embFile_writeInt(file, &sh, 2);

    sh = (short)(embRect_width(rect) / 2.0 * 10);
    embFile_writeInt(file, &sh, 2); /*TODO: xEnd from start point x=0 */
    sh = (short)(embRect_height(rect) / 2.0 * 10);
    embFile_writeInt(file, &sh, 2); /*TODO: yEnd from start point y=0 */
    sh = (short)(embRect_width(rect) / 2.0 * 10);
    embFile_writeInt(file, &sh, 2); /*TODO: left from start x = 0     */
    sh = (short)(embRect_height(rect) / 2.0 * 10);
    embFile_writeInt(file, &sh, 2); /*TODO: bottom from start y = 0   */
    embFile_pad(file, 0, 0xC5);
    binaryWriteInt(file, 0x0000); /* place holder for end of stitches */

    xxxEncodeDesign(file, pattern);

    endOfStitches = ftell(file);

    fseek(file, 0xFC, SEEK_SET);

    binaryWriteUInt(file, endOfStitches);

    fseek(file, 0, SEEK_END);

    /* Is this really correct? */
    fwrite("\x7F\x7F\x03\x14\x00\x00", 1, 6, file);

    for (i = 0; i < 22; i++) {
        if (i < pattern->threads->length) {
            EmbThread t;
            embArray_get(pattern->threads, &t, i);
            b[0] = 0;
            embColor_toStr(t.color, b+1);
            fwrite(b, 1, 4, file);
        } else {
            binaryWriteUInt(file, 0x01000000);
        }
    }

    fwrite("\x00\x01", 1, 2, file);
    return 1;
}

static char readZsk(EmbPattern* pattern, FILE* file, const char* fileName)
{
    unsigned char b[3];
    int stitchType;
    unsigned char colorNumber;
    EmbThread t;

    fseek(file, 0x230, SEEK_SET);
    colorNumber = binaryReadUInt8(file);
    while (colorNumber != 0) {
        fread(b, 1, 3, file);
        t.color = embColor_fromStr(b);
        strcpy(t.catalogNumber, "NULL");
        strcpy(t.description, "NULL");
        embPattern_addThread(pattern, t);
        fseek(file, 0x48, SEEK_CUR);
        fread(&colorNumber, 1, 1, file);
    }
    fseek(file, 0x2E, SEEK_CUR);

    while (fread(b, 1, 3, file) == 3) {
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
            } else if (b[1] == 0x80) {
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

static char writeZsk(EmbPattern* pattern, FILE* file, const char* fileName)
{
    return 0; /*TODO: finish writeZsk */
}

static EmbColor embColor_fromStr(unsigned char *b)
{
    EmbColor c;
    c.r = b[0];
    c.g = b[1];
    c.b = b[2];
    return c;
}

static void embColor_toStr(EmbColor c, unsigned char *b)
{
    b[0] = c.r;
    b[1] = c.g;
    b[2] = c.b;
}

/**
 * Writes out a color to the FILE* file in hex format without using
 * printf or varadic functions (for embedded systems).
 */
static void write_svg_color(FILE* file, EmbColor color)
{
    char hex[] = "0123456789ABCDEF";
    fprintf(file, "stroke=\"#");
    fwrite(hex + (color.r % 16), 1, 1, file);
    fwrite(hex + (color.r / 16), 1, 1, file);
    fwrite(hex + (color.g % 16), 1, 1, file);
    fwrite(hex + (color.g / 16), 1, 1, file);
    fwrite(hex + (color.b % 16), 1, 1, file);
    fwrite(hex + (color.b / 16), 1, 1, file);
    fprintf(file, "\" ");
}

static int svgCreator;
static int svgExpect;
static int svgMultiValue;
static int svgAttributes = 0;
static int element_set = 0;
static char currentElementToken;
static FILE* attributes;
static FILE* currentValue;
static char currentElementName[30];
static char currentAttribute[30];

EmbColor svgColorToEmbColor(char* colorStr)
{
    EmbColor c;
    char ch, *r, *g, *b;
    int i, length, percent, hash, intfunc;

    /* Trim out any junk spaces, remove the rgb() function, parentheses and commas.
     * TODO: create a state variable the replace percent, hash, intfunc, default for color keyword.
     */
    length = 0;
    percent = 0;
    hash = 0;
    intfunc = 0;
    r = colorStr;
    g = 0;
    b = 0;
    if (colorStr[0] == 'r' && colorStr[1] == 'g' && colorStr[2] == 'b') {
        intfunc = 1;
        colorStr += 3;
    }
    for (i=0; colorStr[i]; i++) {
        ch = colorStr[i];
        if (!hash) {
            if (ch == '(' || ch == ')') continue;
        }
        if (ch == ',') {
            /* we have commas, so replace them with zeros and split into r, g, b */
            if (g == 0) {
                g = colorStr + length + 1;
            }
            else {
                b = colorStr + length + 1;
            }
            ch = 0;
        }
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') continue;
        if (ch == '%') {
            percent = 1;
            continue;
        }
        if (ch == '#') {
            hash = 1;
            continue;
        }
        colorStr[length] = ch;
        length++;
    }
    colorStr[length] = 0;

    /* SVGTiny1.2 Spec Section 11.13.1 syntax for color values */
    if (hash) {
        if (length == 3) {
            /* Three digit hex - #rgb */
            /* Convert the 3 digit hex to a six digit hex */
            colorStr[4] = colorStr[2];
            colorStr[5] = colorStr[2];
            colorStr[2] = colorStr[1];
            colorStr[3] = colorStr[1];
            colorStr[1] = colorStr[0];
            colorStr[6] = 0;
        }
        c = embColor_fromHexStr(colorStr);
    } else if (percent) {
        /* Float functional - rgb(R%, G%, B%), by now it is stored in r, g and b */
        c.r = (unsigned char)round(255.0 / 100.0 * atof((char*)r));
        c.g = (unsigned char)round(255.0 / 100.0 * atof((char*)g));
        c.b = (unsigned char)round(255.0 / 100.0 * atof((char*)b));
    } else if (intfunc) {
        /* Integer functional - rgb(rrr, ggg, bbb), by now it is stored in r, g and b. */
        c.r = (unsigned char)atoi((char*)r);
        c.g = (unsigned char)atoi((char*)g);
        c.b = (unsigned char)atoi((char*)b);
    } else {
        /* Color keyword */
        int tableColor = threadColor(&c, colorStr, SVG_Colors);
        if (!tableColor) {
            printf("SVG color string not found: %s\n", colorStr);
        }
    }

    /* Returns black if all else fails */
    return c;
}

static int svgPathCmdToEmbPathFlag(char cmd)
{
    /* TODO: This function needs some work */
    /*
    if     (toUpper(cmd) == 'M') return MOVETO;
    else if(toUpper(cmd) == 'L') return LINETO;
    else if(toUpper(cmd) == 'C') return CUBICTOCONTROL1;
    else if(toUpper(cmd) == 'CC') return CUBICTOCONTROL2;
    else if(toUpper(cmd) == 'CCC') return CUBICTOEND;
    else if(toUpper(cmd) == 'A') return ELLIPSETORAD;
    else if(toUpper(cmd) == 'AA') return ELLIPSETOEND;
    else if(toUpper(cmd) == 'Q') return QUADTOCONTROL;
    else if(toUpper(cmd) == 'QQ') return QUADTOEND;
    else if(toUpper(cmd) == 'Z') return LINETO;
    */

    /*else if(toUpper(cmd) == 'B') return BULGETOCONTROL; */ /* NOTE: This is not part of the SVG spec, but hopefully Bulges will be added to the SVG spec someday */
    /*else if(toUpper(cmd) == 'BB') return BULGETOEND; */ /* NOTE: This is not part of the SVG spec, but hopefully Bulges will be added to the SVG spec someday */
    /*else { puts("ERROR: svgPathCmdToEmbPathFlag(), unknown command '%c'\n", cmd); return MOVETO; } */

    return LINETO;
}

void svgElement_addAttribute(const char* name, const char* value)
{
    int i;
    if (!element_set) {
        puts("ERROR: svgElement_addAttribute(), no recognised element.");
        return;
    }

    fwrite(name, 1, strlen(name), attributes);
    embFile_pad(attributes, 0, 50-strlen(name));

    for (i=0; i<strlen(value); i++) {
        char c = value[i];
        if (c == '"' || c == '\'' || c == '/' || c == ',') continue;
        fwrite(&c, 1, 1, attributes);
    }

    embFile_pad(attributes, 0, 950-strlen(value));
    svgAttributes++;
}

char* svgAttribute_getValue(const char* name)
{
    if (!element_set) {
        puts("ERROR: svgAttribute_getValue(), element==0\n");
        return "none";
    }
    if (!name) {
        puts("ERROR: svgAttribute_getValue(), name==0\n");
        return "none";
    }

    int i;
    for (i=0; i<svgAttributes; i++) {
        fread((char*)embBuffer, 1, 1000, attributes);
        if (string_equal((char*)embBuffer, name)) {
            return embBuffer+50;
        }
    }
    return 0;
}

void svgAddToPattern(EmbPattern* p)
{
    EmbPointObject test;
    EmbColor color;
    EmbPathObject* path;

    if (!p) {
        puts("ERROR: svgAddToPattern(), p==0\n");
        return;
    }

    currentElementToken = identify_element(currentElementName);

    switch (currentElementToken) {
    case ELEMENT_CIRCLE:
        {
        float cx, cy, r;
        cx = atof(svgAttribute_getValue("cx"));
        cy = atof(svgAttribute_getValue("cy"));
        r = atof(svgAttribute_getValue("r"));
        embPattern_addCircleObjectAbs(p, cx, cy, r, 0, black);
        }
        break;
    case ELEMENT_ELLIPSE:
        {
        float cx, cy, rx, ry;
        cx = atof(svgAttribute_getValue("cx"));
        cy = atof(svgAttribute_getValue("cy"));
        rx = atof(svgAttribute_getValue("rx"));
        ry = atof(svgAttribute_getValue("ry"));
        embPattern_addEllipseObjectAbs(p, cx, cy, rx, ry, 0.0, 0, black);
        }
        break;
    case ELEMENT_LINE:
        {
        char* x1 = svgAttribute_getValue("x1");
        char* y1 = svgAttribute_getValue("y1");
        char* x2 = svgAttribute_getValue("x2");
        char* y2 = svgAttribute_getValue("y2");
        
        float x1_f = atof(x1);
        float y1_f = atof(y1);
        float x2_f = atof(x2);
        float y2_f = atof(y2);

        /* If the starting and ending points are the same, it is a point */
        if (string_equal(x1, x2) && string_equal(y1, y2)) {
            embPattern_addPointObjectAbs(p, x1_f, y1_f, 0, black);
        }
        else {
            embPattern_addLineObjectAbs(p, x1_f, y1_f, x2_f, y2_f, 0, black);
        }
        }
        break;
    case ELEMENT_PATH:
        {
        /* TODO: finish */

        char* pointStr = svgAttribute_getValue("d");
        char* mystrok = svgAttribute_getValue("stroke");

        int last = strlen(pointStr);
        int size = 32;
        int i = 0;
        int pos = 0;
        /* An odometer aka 'tripometer' used for stepping thru the pathData */
        int trip = -1; /* count of float[] that has been filled. 0=first item of array, -1=not filled = empty array */
        int reset = -1;
        EmbVector position, f, l, c1, c2;
        int cmd = 0;
        float pathData[7];
        unsigned int numMoves = 0;
        int pendingTask = 0;
        int relative = 0;
        position.x = 0.0;
        position.y = 0.0;
        f = position;
        l = position;
        c1 = position;
        c2 = position;

        EmbArray* pointList = 0;
        EmbArray* flagList;

        char* pathbuff = (char*)embBuffer;
        if (!pathbuff) {
            puts("ERROR: svgAddToPattern(), cannot allocate memory for pathbuff\n");
            return;
        }

        printf("stroke: %s", mystrok);

        /* M44.219,26.365c0,10.306-8.354,18.659-18.652,18.659c-10.299,0-18.663-8.354-18.663-18.659c0-10.305,8.354-18.659,18.659-18.659C35.867,7.707,44.219,16.06,44.219,26.365z */
        for (i = 0; i < last; i++) {
            char c = pointStr[i];
            switch (c) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                pathbuff[pos++] = (char)c; /* add a more char */
                break;

            case ' ':
            case ',':

                printf("    ,'%s'    ~POS=%d  ~TRIP=%d  ~[pos]=%d\n", pathbuff,pos,trip, pathbuff[pos]);
                if (pos > 0) { /* append float to array, if it not yet stored */
                    pathbuff[pos] = 0;
                    pos = 0;
                    printf("    ,val:%s\n", pathbuff);
                    pathData[++trip] = atof(pathbuff);
                }
                break;

            case '-':

                if (pos > 0) { /* append float to array, if it not yet stored */
                    pathbuff[pos] = 0;
                    pos = 0;
                    printf("    -val:%s\n", pathbuff);
                    pathData[++trip] = atof(pathbuff);
                }
                pathbuff[pos++] = (char)c; /* add a more char */
                break;

            default:
                /*** ASSUMED ANY COMMAND FOUND ***/

                if (pos > 0) { /* just make sure: append float to array, if it not yet stored */
                    pathbuff[pos] = 0;
                    pos = 0;
                    printf("    >val:%s\n", pathbuff);
                    pathData[++trip] = atof(pathbuff);
                }

                /**** Compose Point List ****/

                /* below "while" is for avoid losing last 'z' command that maybe never accommodated. */
                pendingTask = 1;
                if (i == last - 1) {
                    pendingTask = 2;
                }

                while (pendingTask > 0) {
                    pendingTask -= 1;

                    /* Check whether prior command need to be saved */
                    if (trip >= 0) {
                        trip = -1;
                        reset = -1;

                        relative = 0; /* relative to prior coordinate point or absolute coordinate? */

                        if (cmd == 'M') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                            f = position;
                        } else if (cmd == 'm') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                            f = position;
                            relative = 1;
                        } else if (cmd == 'L') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        } else if (cmd == 'l') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                            relative = 1;
                        } else if (cmd == 'H') {
                            position.x = pathData[0];
                            position.y = l.y;
                        } else if (cmd == 'h') {
                            position.x = pathData[0];
                            position.y = l.y;
                            relative = 1;
                        } else if (cmd == 'V') {
                            position.x = l.x;
                            position.y = pathData[1];
                        } else if (cmd == 'v') {
                            position.x = l.x;
                            position.y = pathData[1];
                            relative = 1;
                        } else if (cmd == 'C') {
                            position.x = pathData[4];
                            position.y = pathData[5];
                            c1.x = pathData[0];
                            c1.y = pathData[1];
                            c2.x = pathData[2];
                            c2.y = pathData[3];
                        } else if (cmd == 'c') {
                            position.x = pathData[4];
                            position.y = pathData[5];
                            c1.x = pathData[0];
                            c1.y = pathData[1];
                            c2.x = pathData[2];
                            c2.y = pathData[3];
                            relative = 1;
                        }
                        /*
                            else if(cmd == 'S') { position.x = pathData[0]; position.y = pathData[1]; }
                            else if(cmd == 's') { position.x = pathData[0]; position.y = pathData[1]; }
                            else if(cmd == 'Q') { position.x = pathData[0]; position.y = pathData[1]; }
                            else if(cmd == 'q') { position.x = pathData[0]; position.y = pathData[1]; }
                            else if(cmd == 'T') { position.x = pathData[0]; position.y = pathData[1]; }
                            else if(cmd == 't') { position.x = pathData[0]; position.y = pathData[1]; }
                            else if(cmd == 'A') { position.x = pathData[0]; position.y = pathData[1]; }
                            else if(cmd == 'a') { position.x = pathData[0]; position.y = pathData[1]; }
                            */
                        else if (cmd == 'Z') {
                            position = f;
                        } else if (cmd == 'z') {
                            position = f;
                        }

                        if (!pointList && !flagList) {
                            pointList = embArray_create(EMB_POINT);
                            flagList = embArray_create(EMB_FLAG);
                        }
                        test.x = position.x;
                        test.y = position.y;
                        test.lineType = 0;
                        test.color = black;
                        int flag = svgPathCmdToEmbPathFlag(cmd);
                        embArray_add(pointList, &test);
                        embArray_add(flagList, &flag);
                        l = position;

                        pathbuff[0] = (char)cmd; /* set the command for compare */
                        pathbuff[1] = 0;
                        pos = 0;

                        /*
                        printf("*prior:%s (%f, %f,  %f, %f,     %f,%f,  %f) \n", pathbuff,
                            pathData[0],
                            pathData[1],
                            pathData[2],
                            pathData[3],
                            pathData[4],
                            pathData[5],
                            pathData[6]); */
                    }

                    /* assign new command */
                    if (trip == -1 && reset == -1) {
                        pathbuff[0] = (char)c; /* set the command for compare */
                        pathbuff[1] = 0;

                        printf("cmd:%s\n", pathbuff);
                        cmd = c;
                        if (c>='A' && c<='Z') {
                            c += 'a' - 'A';
                        }
                        int resetValues[] = {
                          /*a  b  c  d  e  f  g  h  i  j  k  l  m */
                            7,-1, 6,-1,-1,-1,-1, 1,-1,-1,-1, 2, 2,
                          /*n  o  p  q  r  s  t  u  v  w  x  y  z */
                           -1,-1,-1, 4,-1, 4, 2,-1, 1,-1,-1,-1, 0
                        };
                        if (c>='a' && c<='z') {
                            reset = resetValues[c-'a'];
                            if (c=='m') numMoves++;
                        }
                        if (reset < 0) {
                            printf("ERROR: svgAddToPattern(), %s is not a valid svg path command, skipping...\n", pathbuff);
                            trip = -1;
                            break;
                        }
                    }
                    /* avoid losing 'z' command that maybe never accommodated. */
                    if (i == last - 1) {
                        trip = 2;
                    }
                } /* while pendingTask */

                break;
            }
            if (pos >= size - 1) {
                /* increase pathbuff length - leave room for 0 */
                if (!pathbuff) {
                    puts("error_svg_add_realloc");
                    return;
                }
            }
        }

        /* TODO: subdivide numMoves > 1 */

        color = svgColorToEmbColor(svgAttribute_getValue("stroke"));
        path->pointList = pointList;
        path->flagList = flagList;
        path->color = color;
        path->lineType = 1;
        embPattern_addPathObjectAbs(p, path);
        }
        break;
    case ELEMENT_POLYGON:
    case ELEMENT_POLYLINE:
    {
        char* pointStr = svgAttribute_getValue("points");
        int last = strlen(pointStr);
        int size = 32;
        int i = 0;
        int pos = 0;
        unsigned char odd = 1;
        EmbPointObject a;
        a.x = 0.0;
        a.y = 0.0;

        EmbArray* pointList = 0;

        /* if this goes over, switch the embArray_create(EMB_CHAR) */
        char* polybuff = (char*)embBuffer;

        for (i = 0; i < last; i++) {
            char c = pointStr[i];
            switch (c) {
            case ' ':
                if (pos == 0)
                    break;
                polybuff[pos] = 0;
                pos = 0;
                /*Compose Point List */
                if (odd) {
                    odd = 0;
                    a.x = atof(polybuff);
                } else {
                    odd = 1;
                    a.y = atof(polybuff);

                    if (!pointList) {
                        pointList = embArray_create(EMB_POINT);
                    }
                    a.lineType = 0;
                    a.color = black;
                    embArray_add(pointList, &a);
                }

                break;
            default:
                polybuff[pos++] = (char)c;
                if (pos == 1024) {
                    puts("Buffer overflow: polybuff.");
                    return;
                }
                break;
            }
        }

        char *s = svgAttribute_getValue("stroke");
        if (currentElementToken == ELEMENT_POLYGON) {
            EmbPolygonObject polygonObj;
            polygonObj.pointList = pointList;
            polygonObj.color = svgColorToEmbColor(s);
            polygonObj.lineType = 1; /* TODO: use lineType enum */
            embArray_add(p->polygons, &polygonObj);
        }
        else { /* polyline */
            EmbPolylineObject polylineObj;
            polylineObj.pointList = pointList;
            polylineObj.color = svgColorToEmbColor(s);
            polylineObj.lineType = 1; /* TODO: use lineType enum */
            embArray_add(p->polylines, &polylineObj);
        }

        }
        break;
    case ELEMENT_RECT:
        {
        float x1, y1, width, height;
        x1 = atof(svgAttribute_getValue("x"));
        y1 = atof(svgAttribute_getValue("y"));
        width = atof(svgAttribute_getValue("width"));
        height = atof(svgAttribute_getValue("height"));
        embPattern_addRectObjectAbs(p, x1, y1, width, height, 0, black);
        }
        break;
    default:
        break;
    }
}

static int svgIsElement(const char* buff)
{
    if (string_in_table(buff, svg_element_token_table)) {
        return SVG_ELEMENT;
    }

    /* Attempt to identify the program that created the SVG file. This should be in a comment at that occurs before the svg element. */
    else if (string_equal(buff, "Embroidermodder")) {
        svgCreator = SVG_CREATOR_EMBROIDERMODDER;
    } else if (string_equal(buff, "Illustrator")) {
        svgCreator = SVG_CREATOR_ILLUSTRATOR;
    } else if (string_equal(buff, "Inkscape")) {
        svgCreator = SVG_CREATOR_INKSCAPE;
    }

    return SVG_NULL;
}

static char svgIsMediaProperty(const char* buff)
{
    if (string_in_table(buff, svg_media_property_token_table)) {
        return SVG_MEDIA_PROPERTY;
    }
    return SVG_NULL;
}

static char svgIsProperty(const char* buff)
{
    if (string_in_table(buff, svg_property_token_table)) {
        return SVG_PROPERTY;
    }
    return SVG_NULL;
}

static char string_in_table(const char *buff, int table)
{
    int out;
    out = dereference_int(table);
    embBuffer[0] = 1;
    while (embBuffer[0]) {
        get_str((char *)embBuffer, out);
        if (string_equal((char *)embBuffer, buff)) {
            return 1;
        }
        out += 4;
    }
    return 0;
}

static char svgIsSvgAttribute(const char* buff)
{
    if (string_in_table(buff, svg_token_table)) {
        return SVG_ATTRIBUTE;
    }

    if (svgCreator == SVG_CREATOR_INKSCAPE) {
        if (string_in_table(buff, inkscape_token_table)) {
            return SVG_ATTRIBUTE;
        }
    }

    printf("svgIsSvgAttribute(), unknown:%s\n", buff);
    return SVG_NULL;
}

static int svgIsCatchAllAttribute(const char* buff)
{
    if (string_in_table(buff, svg_property_token_table)) {
        return SVG_CATCH_ALL;
    }
    if (svgCreator == SVG_CREATOR_INKSCAPE) {
        if (string_in_table(buff, svg_attribute_token_table)) {
            return SVG_CATCH_ALL;
        }
    }

    return SVG_NULL;
}

static char svgHasAttribute(const char *buff, int out, const char *errormsg)
{
    if (string_in_table(buff, out)) {
        return SVG_ATTRIBUTE;
    }

    printf("%s attribute unknown: %s", errormsg, buff);

    return SVG_NULL;
}


static char identify_element(char *token)
{
    int offset;
    char id;
    for (id=0; id < ELEMENT_UNKNOWN; id++) {
        offset = dereference_int(svg_element_token_table);
        get_str((char*)embBuffer, offset + 4*id);
        if (string_equal(embBuffer, token)) {
            break;
        }
    }
    return id;
}

void svgProcess(int c, const char* buff)
{
    if (svgExpect == SVG_EXPECT_ELEMENT) {
        char advance = 0;
        if (buff[0] == '/') {
            return;
        }

        advance = (char)svgIsElement(buff);

        if (advance) {
            puts("ELEMENT:\n");
            svgExpect = SVG_EXPECT_ATTRIBUTE;
            element_set = 1;
            svgAttributes = 0;
            if (attributes) {
                fclose(attributes);
            }
            attributes = tmpfile();
            strcpy(currentElementName, buff);
        } else {
            return;
        }
    } else if (svgExpect == SVG_EXPECT_ATTRIBUTE) {
        char advance = 0;
        if (!element_set) {
            puts("There is no current element but the parser expects one.");
            return;
        }
        currentElementToken = identify_element(currentElementName);
        
        switch (currentElementToken) {
        case ELEMENT_A:
        case ELEMENT_CIRCLE:
        case ELEMENT_DEFS:
        case ELEMENT_ELLIPSE:
        case ELEMENT_FOREIGN_OBJECT:
        case ELEMENT_G:
        case ELEMENT_LINE:
        case ELEMENT_LINEAR_GRADIENT:
        case ELEMENT_PATH:
        case ELEMENT_POLYGON:
        case ELEMENT_POLYLINE:
        case ELEMENT_RADIAL_GRADIENT:
        case ELEMENT_RECT:
        case ELEMENT_SOLID_COLOR:
        case ELEMENT_STOP:
        case ELEMENT_SVG:
        case ELEMENT_SWITCH:
        case ELEMENT_TEXT:
        case ELEMENT_TEXT_AREA:
        case ELEMENT_TSPAN:
        case ELEMENT_USE:
            advance = svgIsProperty(buff);
            break;        
        case ELEMENT_ANIMATION:
        case ELEMENT_AUDIO:
        case ELEMENT_IMAGE:
        case ELEMENT_METADATA:
        case ELEMENT_TITLE:
        case ELEMENT_VIDEO:
            advance = svgIsMediaProperty(buff);
            break;
        default:
            break;
        }

        if (!advance) {
            if (currentElementToken == ELEMENT_XML) {
                int xmlTokens = double_dereference_int(svg_token_lists, 0);
                advance = svgHasAttribute(buff, xmlTokens, "?xml");
            }
            else if (currentElementToken == ELEMENT_SVG) {
                advance = svgIsSvgAttribute(buff);
            }
            else if (currentElementToken != ELEMENT_UNKNOWN) {
                char element_token[30];
                int out2;
                int out = double_dereference_int(svg_token_lists, currentElementToken);
                out2 = dereference_int(svg_element_token_table);
                get_str(element_token, out2+4*currentElementToken);
                
                advance = svgHasAttribute(buff, out, element_token);
            }
        }

        if (advance) {
            puts("ATTRIBUTE:\n");
            svgExpect = SVG_EXPECT_VALUE;
            strcpy(currentAttribute, buff);
        }
    } else if (svgExpect == SVG_EXPECT_VALUE) {
        int last = strlen(buff) - 1;
        puts("VALUE:\n");

        /* single-value */
        if ((buff[0] == '"' || buff[0] == '\'') && (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') && !svgMultiValue) {
            svgExpect = SVG_EXPECT_ATTRIBUTE;
            svgElement_addAttribute(currentAttribute, buff);
        } else /* multi-value */
        {
            svgMultiValue = 1;
            if (!currentValue) {
                strcpy(currentValue, buff);
            } else {
                char *buffer = (char*)embBuffer;
                int length;
                strcpy(buffer, currentValue);
                length = strlen(buff) + strlen(buffer) + 2;
                if (!currentValue) {
                    puts("ERROR: svgProcess(), cannot allocate memory for currentValue\n");
                    return;
                }
                strcpy(currentValue, buffer);
                strcpy(currentValue+strlen(buffer), " ");
                strcpy(currentValue+strlen(buffer)+1, buff);
            }

            if (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') {
                svgMultiValue = 0;
                svgExpect = SVG_EXPECT_ATTRIBUTE;
                svgElement_addAttribute(currentAttribute, currentValue);
            }
        }
    }

    if (svgExpect != SVG_EXPECT_NULL) {
        puts(buff);
    }

    if (c == '>') {
        svgExpect = SVG_EXPECT_NULL;
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a p.
 *  Returns \c true if successful, otherwise returns \c false. */
static char readSvg(EmbPattern* p, FILE* file, const char* fileName)
{
    int pos;
    char c;
    char* buff = (char*)embBuffer;

    svgCreator = SVG_CREATOR_NULL;
    svgExpect = SVG_EXPECT_NULL;
    svgMultiValue = 0;
    element_set = 0;

    /* Pre-flip in case of multiple reads on the same p */
    embPattern_flipVertical(p);

    pos = 0;
    while (fread(&c, 1, 1, file)) {
        switch (c) {
        case '<':
            if (svgExpect == SVG_EXPECT_NULL) {
                svgAddToPattern(p);
                svgExpect = SVG_EXPECT_ELEMENT;
            }
        case '>':
            if (pos == 0) { /* abnormal case that may occur in svg element where '>' is all by itself */
                /*TODO: log a warning about this absurdity! */
                svgExpect = SVG_EXPECT_ELEMENT;
                break;
            }
        case ' ':
        case '\t':
        case '\r':
        case '\n':
        case '=':
            if (pos == 0)
                break;
            buff[pos] = 0;
            pos = 0;
            svgProcess(c, buff);
            break;
        default:
            buff[pos++] = (char)c;
            break;
        }
        if (pos >= 1024) {
            puts("ERROR: readSvg(), buffer overflow.");
            return 0;
        }
    }

    /* Flip the p since SVG Y+ is down and libembroidery Y+ is up. */
    embPattern_flipVertical(p);

    return 1; /*TODO: finish readSvg */
}

static char writeSvg(EmbPattern* p, FILE* file, const char* fileName)
{
    int i;
    EmbRect boundingRect;

    /* Pre-flip the p since SVG Y+ is down and libembroidery Y+ is up. */
    embPattern_flipVertical(p);

    boundingRect = embPattern_calcBoundingBox(p);
    fprintf(file,
        "<?xml version=\"1.0\"?>\n" \
        "<!-- Embroidermodder 2 SVG Embroidery File -->\n" \
        "<!-- http://embroidermodder.github.io -->\n" \
        "<svg viewBox=\"%1.5f %1.5f %1.5f %1.5f\" " \
        "xmlns=\"http://www.w3.org/2000/svg\" version=\"1.2\" baseProfile=\"tiny\">",
        boundingRect.left, boundingRect.top, embRect_width(boundingRect),
        embRect_height(boundingRect));

    /* TODO: See the SVG Tiny Version 1.2 Specification Section 7.14.
     *       Until all of the formats and API is stable, the width, height and viewBox attributes need to be left unspecified.
     *       If the attribute values are incorrect, some applications wont open it at all.
     */

    /*TODO: Low Priority: Indent output properly. */

    for (i = 0; i < p->circles->length; i++) {
        EmbCircle c;
        embArray_get(p->circles, &c, i);
        /* TODO: use proper thread width for stoke-width rather than just 0.2 */
        fprintf(file, "\n<circle stroke-width=\"0.2\" fill=\"none\" ");
        write_svg_color(file, c.color);
        fprintf(file, " cx=\"%1.5f\" cy=\"%1.5f\" r=\"%1.5f\" />", c.center.x, c.center.y, c.radius);
    }

    for (i = 0; i < p->ellipses->length; i++) {
        EmbEllipse e;
        embArray_get(p->ellipses, &e, i);
        /* TODO: use proper thread width for stoke-width rather than just 0.2 */
        fprintf(file, "\n<ellipse stroke-width=\"0.2\" fill=\"none\" ");
        write_svg_color(file, e.color);
        fprintf(file, " cx=\"%1.5f\" cy=\"%1.5f\" rx=\"%1.5f\" ry=\"%1.5f\" />",
            e.center.x, e.center.y, e.radius.x, e.radius.y);
    }

    for (i = 0; i < p->lines->length; i++) {
        EmbLine line;
        embArray_get(p->lines, &line, i);
        /* TODO: use proper thread width for stoke-width rather than just 0.2 */
        fprintf(file, "\n<line stroke-width=\"0.2\" fill=\"none\" ");
        write_svg_color(file, line.color);
        fprintf(file, "x1=\"%1.5f\" y1=\"%1.5f\" x2=\"%1.5f\" y2=\"%1.5f\" />",
            line.start.x, line.start.y, line.end.x, line.end.y);
    }

    for (i = 0; i < p->points->length; i++) {
        EmbPointObject point;
        embArray_get(p->points, &point, i);
        /* See SVG Tiny 1.2 Spec:
         * Section 9.5 The 'line' element
         * Section C.6 'path' element implementation notes */
        /* TODO: use proper thread width for stoke-width rather than just 0.2 */
        fprintf(file, "\n<line stroke-linecap=\"round\" stroke-width=\"0.2\" fill=\"none\" ");
        write_svg_color(file, point.color);
        fprintf(file, "x1=\"%1.5f\" y1=\"%1.5f\" x2=\"%1.5f\" y2=\"%1.5f\" />",
            point.x, point.y, point.x, point.y);
    }

    for (i = 0; i < p->polygons->length; i++) {
        int j;
        EmbPolygonObject polygon;
        EmbVector v;
        embArray_get(p->polygons, &polygon, i);
        /* TODO: use proper thread width for stoke-width rather than just 0.2 */
        fprintf(file, "\n<polygon stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" fill=\"none\" ");
        write_svg_color(file, polygon.color);
        embArray_get(polygon.pointList, &v, 0);
        fprintf(file, "points=\"%1.5f,%1.5f", v.x, v.y);
        for (j = 1; j < polygon.pointList->length; j++) {
            embArray_get(polygon.pointList, &v, j);
            fprintf(file, " %1.5f,%1.5f", v.x, v.y);
        }
        fprintf(file, "\" />");
    }

    for (i = 0; i < p->polylines->length; i++) {
        int j;
        EmbPolylineObject polyline;
        EmbVector v;
        embArray_get(p->polylines, &polyline, i);
        /* TODO: use proper thread width for stoke-width rather than just 0.2 */
        fprintf(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" ");
        write_svg_color(file, polyline.color);
        fprintf(file, "fill=\"none\" ");
        embArray_get(polyline.pointList, &v, 0);
        fprintf(file, "points=\"%1.5f,%1.5f", v.x, v.y);
        for (j = 1; j < polyline.pointList->length; j++) {
            embArray_get(polyline.pointList, &v, j);
            fprintf(file, " %1.5f,%1.5f", v.x, v.y);
        }
        fprintf(file, "\" />");
    }

    for (i = 0; i < p->rects->length; i++) {
        EmbRect rect;
        embArray_get(p->rects, &rect, i);
        /* TODO: use proper thread width for stoke-width rather than just 0.2 */
        fprintf(file, "\n<rect stroke-width=\"0.2\" fill=\"none\" ");
        write_svg_color(file, rect.color);
        fprintf(file, "x=\"%1.5f\" y=\"%1.5f\" width=\"%1.5f\" height=\"%1.5f\" />",
            embRect_x(rect), embRect_y(rect), embRect_width(rect), embRect_height(rect));
    }

    int isNormal = 0;
    for (i = 0; i < p->stitchList->length; i++) {
        /*TODO: Low Priority Optimization:
         *      Make sure that the line length that is output doesn't exceed 1000 characters. */
        EmbStitch st;
        /*TODO: #ifdef SVG_DEBUG for Josh which outputs JUMPS/TRIMS instead of chopping them out */
        embArray_get(p->stitchList, &st, i);
        if (st.flags == NORMAL && !isNormal) {
            EmbThread t;
            isNormal = 1;
            embArray_get(p->threads, &t, st.color);
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" ");
            write_svg_color(file, t.color);
            fprintf(file, "fill=\"none\" points=\"%1.5f,%1.5f",  st.x, st.y);
        } else if (st.flags == NORMAL && isNormal) {
            fprintf(file, " %1.5f,%1.5f", st.x, st.y);
        } else if (st.flags != NORMAL && isNormal) {
            isNormal = 0;
            fprintf(file, "\"/>");
        }
    }

    fprintf(file, "\n</svg>\n");

    /* Reset the p so future writes(regardless of format) are not flipped */
    embPattern_flipVertical(p);

    return 1;
}

static int embColor_distance(EmbColor a, EmbColor b)
{
    int d;
    d = (a.r - b.r) * (a.r - b.r);
    d += (a.g - b.g) * (a.g - b.g);
    d += (a.b - b.b) * (a.b - b.b);
    return d;
}

int embThread_findNearestColor(EmbColor color, int thread_table)
{
    int currentClosestValue, closestIndex, i, length;

    currentClosestValue = 256 * 256 * 3;
    closestIndex = -1;
    length = double_dereference_int(table_lengths, thread_table);

    for (i = 0; i < length; i++) {
        int delta;
        EmbThread t;
        t = load_thread(thread_table, i);
        delta = embColor_distance(color, t.color);

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
EmbThread embThread_getRandom(void)
{
    EmbThread c;
    c.color.r = random_int() % 256;
    c.color.g = random_int() % 256;
    c.color.b = random_int() % 256;
    strcpy(c.description, "random");
    strcpy(c.catalogNumber, "NULL");
    return c;
}

int embColor_equal(EmbColor a, EmbColor b)
{
    return (a.r == b.r) && (a.g == b.g) && (a.b == b.b);
}


int threadColor(EmbColor *c, const char* name, int brand)
{
    int length, i;
    length = double_dereference_int(table_lengths, brand);
    *c = black;

    for (i=0; i<length; i++) {
        EmbThread t = load_thread(brand, i);
        if (string_equal(t.description, name)) {
            *c = t.color;
            return 1;
        }
    }

    return 0;
}

int threadColorNum(EmbColor color, int brand)
{
    int length, i;
    length = double_dereference_int(table_lengths, brand);

    for (i=0; i<length; i++) {
        EmbThread t = load_thread(brand, i);
        if (embColor_equal(t.color, color)) {
            /* return t.catalogNumber; */
            return 0;
        }
    }

    return -1;
}

void threadColorName(char *result, EmbColor color, int brand)
{
    int length, i;
    length = double_dereference_int(table_lengths, brand);

    for (i=0; i<length; i++) {
        EmbThread t = load_thread(brand, i);
        if (embColor_equal(t.color, color)) {
            strcpy(result, t.description);
            return;
        }
    }

    strcpy(result, "COLOR NOT FOUND");
}

/* For now we are assuming that there is only one pattern loaded at a time.
 * Therefore the arrays shifted to the file "libembroidery_memory.bin" can
 * be assumed to be for this active pattern pattern.
 */
int init_embroidery(void)
{
    datafile = embFile_open("libembroidery_data.bin", "rb", 0);

    /* Detect endianness, if running on a big endian machine
     * then the first byte of the short 0x0001 is 0x00 since it
     * reads left to right.
     *
     * The code is compiled for one mode or another, so if the host
     * machine does not match this, return 0.
     */
    short wordExample = 0x0001;
    char *endianTest = (char*)&wordExample;

    #if ENDIAN_HOST == EMB_LITTLE_ENDIAN
    if (endianTest[0] == EMB_BIG_ENDIAN) {
        return 0;
    }
    #else
    if (endianTest[0] == EMB_LITTLE_ENDIAN) {
        return 0;
    }
    #endif
    return 1;
}

int close_embroidery(void)
{
    fclose(datafile);
    return 0;
}

