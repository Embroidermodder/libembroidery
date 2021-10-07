#include "embroidery.h"
#include <stdio.h>

char *strcat(char *dest, const char *src);
char *strrchr(const char *ptr, int);

void * malloc(size_t);
void * realloc(void *, size_t);
void free(void *);

double fabs(double);
double sqrt(double);
double cos(double);
double sin(double);
double atan2(double, double);

#if ARDUINO
/*TODO: arduino embTime includes */
#else
#include <time.h>
#endif

struct EmbFile_ {
    FILE *file;
};

/* float-indirection file allocation table references */
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

/* STATIC FUNCTION PROTOTYPES
 *
 * For functions that can be declared static and inlined automatically
 * that won't be called by users through embroidery.h.
 */

static int embFile_read(void *ptr, int a, int b, EmbFile *stream);
static int embFile_write(void *ptr, int a, int b, EmbFile *stream);
static int embFile_seek(EmbFile *stream, int offset, int flags);
static int embFile_tell(EmbFile *stream);

static int dereference_int(int p);
static int double_dereference_int(int table, int entry);
static int get_str(char *s, int p);

static EmbColor embColor_fromStr(unsigned char *b);
static void embColor_toStr(EmbColor c, unsigned char *b);

static char binaryReadByte(EmbFile* file);
static int binaryReadBytes(EmbFile* file, unsigned char* destination, int count);
static short binaryReadInt16(EmbFile* file);
static int binaryReadInt32(EmbFile* file);
static unsigned char binaryReadUInt8(EmbFile* file);
static unsigned short binaryReadUInt16(EmbFile* file);
static unsigned int binaryReadUInt32(EmbFile* file);
static short binaryReadInt16BE(EmbFile* file); /* Big endian version */
static unsigned short binaryReadUInt16BE(EmbFile* file); /* Big endian version */
static int binaryReadInt32BE(EmbFile* file);   /* Big endian version */
static unsigned int binaryReadUInt32BE(EmbFile* file);
static float binaryReadFloat(EmbFile* file);
static void binaryReadString(EmbFile* file, char *buffer, int maxLength);

static void binaryWriteByte(EmbFile* file, unsigned char data);
static void binaryWriteBytes(EmbFile* file, const char* data, int size);
static void binaryWriteShort(EmbFile* file, short data);
static void binaryWriteShortBE(EmbFile* file, short data);
static void binaryWriteUShort(EmbFile* file, unsigned short data);
static void binaryWriteUShortBE(EmbFile* file, unsigned short data);
static void binaryWriteInt(EmbFile* file, int data);
static void binaryWriteIntBE(EmbFile* file, int data);
static void binaryWriteUInt(EmbFile* file, unsigned int data);
static void binaryWriteUIntBE(EmbFile* file, unsigned int data);
static void binaryWriteFloat(EmbFile* file, float data);

static void writeFloat(EmbFile* file, float number);
static void writeFloatWrap(EmbFile* file, char *prefix, float number, char *suffix);
static void writeFloatAttribute(EmbFile* file, char *attribute, float number);

static int roundDouble(float src);
static void writeInt(EmbFile *, int, int);
static void writeFloat(EmbFile *, float);

static void embPointerToArray(char *buffer, void* pointer, int maxDigits);
static void embIntToArray(char *buffer, int number, int maxDigits);
static void embFloatToArray(char *buffer, float number, float tolerence, int before, int after);

static void husExpand(unsigned char* input, unsigned char* output, int compressedSize, int _269);
static int husCompress(unsigned char* _266, unsigned long _inputSize, unsigned char* _267, int _269, int _235);
 
static void readPecStitches(EmbPattern* pattern, EmbFile* file, const char* fileName);
static void writePecStitches(EmbPattern* pattern, EmbFile* file, const char* filename);

static char string_in_table(char *buff, int table);
static EmbThread load_thread(int, int);

static void embLog(const char* str);
static void embTime_initNow(EmbTime* t);
static EmbTime embTime_time(EmbTime* t);

static char read100(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char write100(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char read10o(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char write10o(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readBro(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeBro(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readCol(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeCol(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readCsd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeCsd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readCsv(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeCsv(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readDat(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeDat(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readDsb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeDsb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readDst(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeDst(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readDsz(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeDsz(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readDxf(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeDxf(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readEdr(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeEdr(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readEmd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeEmd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readExp(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeExp(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readExy(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeExy(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readFxy(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeFxy(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readGt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeGt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readHus(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeHus(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readInb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeInb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readInf(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeInf(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readJef(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeJef(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readKsm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeKsm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readMax(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeMax(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readMit(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeMit(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readNew(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeNew(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readOfm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeOfm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPcd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePcd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPcm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePcm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPcq(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePcq(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPcs(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePcs(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPec(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePec(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPes(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePes(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPhb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePhb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPhc(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePhc(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPlt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePlt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readRgb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeRgb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readSew(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeSew(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readShv(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeShv(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readSst(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeSst(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readStx(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeStx(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readSvg(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeSvg(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readT01(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeT01(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readT09(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeT09(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readTap(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeTap(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readThr(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeThr(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readTxt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeTxt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readU00(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeU00(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readU01(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeU01(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readVip(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeVip(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readVp3(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeVp3(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readXxx(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeXxx(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readZsk(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeZsk(EmbPattern *pattern, EmbFile* file, const char* fileName);

static char identify_element(char *token);
static void print_log_string(int offset);

static int encode_dst_ternary(int *, unsigned char *);
static void decode_dst_ternary(int *, unsigned char *);

static void writePoint(EmbFile* file, float x, float y, int space);
static void write_svg_color(EmbFile* file, EmbColor color);
static void writeCircles(EmbPattern* p, EmbFile* file);
static void writeEllipse(EmbPattern* p, EmbFile* file);
static void writePoints(EmbPattern* p, EmbFile* file);
static void writePolygons(EmbPattern* p, EmbFile* file);
static void writePolylines(EmbPattern* p, EmbFile* file);
static void writeStitchList(EmbPattern* p, EmbFile* file);

static EmbFile* embFile_open(const char* fileName, const char* mode, int optional);
static int embFile_readline(EmbFile* stream, char *, int);
static int embFile_close(EmbFile* stream);
static EmbFile* embFile_tmpfile(void);
static void embFile_print(EmbFile* stream, char*);
static void embFile_pad(EmbFile *f, char, int);

static int bcfFile_read(EmbFile* file, bcf_file* bcfFile);
static EmbFile* GetFile(bcf_file* bcfFile, EmbFile* file, char* fileToFind);
static void bcf_file_free(bcf_file* bcfFile);

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
static EmbFile *datafile;
static EmbFile *memory;

/* Flag Defines
 */

#define EMB_BIG_ENDIAN                 0
#define EMB_LITTLE_ENDIAN              1

/* These mirror the first table in libembroidery_data.asm. */
#define svg_property_token_table       0
#define svg_attribute_token_table      4
#define svg_token_lists                8
#define brand_codes                    12
#define image_frame                    16
#define csv_header                     20
#define max_header                     24
#define vip_decoding_table             28
#define format_list                    32
#define write_csv_error_0              36
#define read_csv_error_0               40
#define read_csv_error_1               44
#define read_csv_error_2               48
#define svg_token_table                52
#define inkscape_token_table           56
#define svg_element_token_table        60
#define svg_media_property_token_table 64
#define stitch_labels                  68
#define dxf_version_year               72
#define dxf_version_r                  76
#define table_lengths                  80

#define brand_codes_length             24
#define thread_type_length             35
#define thread_color_offset            30
#define thread_code                    33

/* path flag codes */
#define LINETO                         0
#define MOVETO                         1
#define BULGETOCONTROL                 2
#define BULGETOEND                     4
#define ELLIPSETORAD                   8
#define ELLIPSETOEND                   16
#define CUBICTOCONTROL1                32
#define CUBICTOCONTROL2                64
#define CUBICTOEND                     128
#define QUADTOCONTROL                  256
#define QUADTOEND                      512

#define SVG_CREATOR_NULL               0
#define SVG_CREATOR_EMBROIDERMODDER    1
#define SVG_CREATOR_ILLUSTRATOR        2
#define SVG_CREATOR_INKSCAPE           3

#define SVG_EXPECT_NULL                0
#define SVG_EXPECT_ELEMENT             1
#define SVG_EXPECT_ATTRIBUTE           2
#define SVG_EXPECT_VALUE               3

/* SVG_TYPES */
#define SVG_NULL                       0
#define SVG_ELEMENT                    1
#define SVG_PROPERTY                   2
#define SVG_MEDIA_PROPERTY             3
#define SVG_ATTRIBUTE                  4
#define SVG_CATCH_ALL                  5

/**
Type of sector
*/
#define CompoundFileSector_MaxRegSector 0xFFFFFFFA
#define CompoundFileSector_DIFAT_Sector 0xFFFFFFFC
#define CompoundFileSector_FAT_Sector 0xFFFFFFFD
#define CompoundFileSector_EndOfChain 0xFFFFFFFE
#define CompoundFileSector_FreeSector 0xFFFFFFFF

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
#define CSV_MODE_COMMENT          1
#define CSV_MODE_VARIABLE         2
#define CSV_MODE_THREAD           3
#define CSV_MODE_STITCH           4

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

/* Global Constants
 */

/* Detect endianness, if running on a big endian machine
 * then the first byte of the short 0x0001 is 0x00 since it
 * reads left to right.
 *
 * So if the code is written for a little endian machine
 * and this detects big endian then we do the same casting
 * and then swap the byte order.
 */
short wordExample = 0x0001;
char *endianTest = (char*)&wordExample;

static EmbColor black = { 0, 0, 0 };

/*******************************************************************************
 * CODE SECTION
 */

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

static int dereference_int(int p)
{
    int out;
    embFile_seek(datafile, p, SEEK_SET);
    embFile_read(&out, 4, 1, datafile);
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

static int string_length(char *a);
static int string_equal(char *a, char *b);
static void memory_copy(void *a, void *b, int length);
static void string_copy(char *a, char *b);

static void memory_set(void *ptr, int p, int length)
{
    int i;
    for (i=0; i<length; i++) {
        ((char *)ptr)[i] = p;
    }
}

static int get_str(char *s, int p)
{
    int i;
    embFile_seek(datafile, p, SEEK_SET);
    for (i=0; i<MAX_STRING_LENGTH; i++) {
        embFile_read(s+i, 1, 1, datafile);
        if (!s[i]) {
            return 1;
        }
    }
    return 0;
}

static int string_length(char *a)
{
    int i;
    for (i=0; i<MAX_STRING_LENGTH; i++) {
        if (a[i] == 0) {
            return i;
        }
    }
    return MAX_STRING_LENGTH;
}

static int string_equal(char *a, char *b)
{
    int i;
    for (i=0; i< MAX_STRING_LENGTH; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
        if (!a[i]) {
            break;
        }
    }
    if (!b[i] && i < MAX_STRING_LENGTH) {
        return 1;
    }
    return 0;
}

static void memory_copy(void *a, void *b, int length)
{
    int i;
    length = emb_min_int(length, MAX_STRING_LENGTH);
    for (i=0; i<length; i++) {
        ((char *)a)[i] = ((char *)b)[i];
    }
}

static void string_copy(char *a, char *b)
{
    memory_copy(a, b, string_length(b));
    a[string_length(b)] = 0;
}

/* ARDUINO TODO:
 * SD File read() doesn't appear to return the same way as fread().
 * This will need work.
 * ARDUINO TODO: Implement inoFile_write. */
static int embFile_read(void *ptr, int a, int b, EmbFile *stream)
{
#ifdef ARDUINO
    return inoFile_read(ptr, a, b, stream);
#else
    return fread(ptr, a, b, stream->file);
#endif
}

static int embFile_write(void *ptr, int a, int b, EmbFile *stream)
{
#ifdef ARDUINO
    return inoFile_write(ptr, a, b, stream);
#else
    return fwrite(ptr, a, b, stream->file);
#endif
}

static int embFile_seek(EmbFile *stream, int offset, int origin)
{
#ifdef ARDUINO
    return inoFile_seek(stream, offet, origin);
#else
    return fseek(stream->file, offset, origin);
#endif
}

static int embFile_tell(EmbFile *stream)
{
#ifdef ARDUINO
    return inoFile_tell(stream);
#else
    return ftell(stream->file);
#endif
}

EmbArray* embArray_create(int type)
{
    EmbArray* p;
    p = (EmbArray*)malloc(sizeof(EmbArray));
    p->type = type;
    p->length = CHUNK_SIZE;
    p->count = 0;
    switch (p->type) {
    case EMB_ARC:
        p->arc = (EmbArc*)malloc(CHUNK_SIZE * sizeof(EmbArc));
        break;
    case EMB_CIRCLE:
        p->circle = (EmbCircle*)malloc(CHUNK_SIZE * sizeof(EmbCircle));
        break;
    case EMB_ELLIPSE:
        p->ellipse = (EmbEllipse*)malloc(CHUNK_SIZE * sizeof(EmbEllipse));
        break;
    case EMB_FLAG:
        p->flag = (int*)malloc(CHUNK_SIZE * sizeof(int));
        break;
    case EMB_PATH:
        p->path = (EmbPathObject**)malloc(CHUNK_SIZE * sizeof(EmbPathObject*));
        break;
    case EMB_POINT:
        p->point = (EmbVector*)malloc(CHUNK_SIZE * sizeof(EmbVector));
        break;
    case EMB_LINE:
        p->line = (EmbLine*)malloc(CHUNK_SIZE * sizeof(EmbLine));
        break;
    case EMB_POLYGON:
        p->polygon = (EmbPolygonObject**)malloc(CHUNK_SIZE * sizeof(EmbPolygonObject*));
        break;
    case EMB_POLYLINE:
        p->polyline = (EmbPolylineObject**)malloc(CHUNK_SIZE * sizeof(EmbPolylineObject*));
        break;
    case EMB_RECT:
        p->rect = (EmbRect*)malloc(CHUNK_SIZE * sizeof(EmbRect));
        break;
    case EMB_SPLINE:
        p->spline = (EmbSplineObject*)malloc(CHUNK_SIZE * sizeof(EmbSplineObject));
        break;
    case EMB_STITCH:
        p->stitch = (EmbStitch*)malloc(CHUNK_SIZE * sizeof(EmbStitch));
        break;
    case EMB_THREAD:
        p->thread = (EmbThread*)malloc(CHUNK_SIZE * sizeof(EmbThread));
        break;
    case EMB_VECTOR:
        p->vector = (EmbVector*)malloc(CHUNK_SIZE * sizeof(EmbVector));
        break;
    default:
        break;
    }
    switch (p->type) {
    case EMB_ARC:
    case EMB_CIRCLE:
    case EMB_POINT:
    case EMB_LINE:
    case EMB_RECT:
        p->color = (EmbColor*)malloc(CHUNK_SIZE * sizeof(EmbColor));
        if (!p->color)
            return 0;
        p->flag = (int*)malloc(CHUNK_SIZE * sizeof(int));
        if (!p->flag)
            return 0;
        break;
    case EMB_ELLIPSE:
        p->color = (EmbColor*)malloc(CHUNK_SIZE * sizeof(EmbColor));
        if (!p->color)
            return 0;
        p->flag = (int*)malloc(CHUNK_SIZE * sizeof(int));
        if (!p->flag)
            return 0;
        p->floats = (float*)malloc(CHUNK_SIZE * sizeof(float));
        if (!p->floats)
            return 0;
        break;
    default:
        break;
    }
    return p;
}

int embArray_resize(EmbArray* p)
{
    if (p->count < p->length)
        return 1;
    p->length += CHUNK_SIZE;
    switch (p->type) {
    case EMB_ARC:
        p->arc = realloc(p->arc, p->length * sizeof(EmbArc));
        if (!p->arc)
            return 1;
        break;
    case EMB_CIRCLE:
        p->circle = realloc(p->circle, p->length * sizeof(EmbCircle));
        if (!p->circle)
            return 1;
        break;
    case EMB_ELLIPSE:
        p->ellipse = realloc(p->ellipse, p->length * sizeof(EmbEllipse));
        if (!p->ellipse)
            return 1;
        break;
    case EMB_FLAG:
        p->flag = realloc(p->flag, p->length * sizeof(int));
        if (!p->flag)
            return 1;
        break;
    case EMB_PATH:
        p->path = realloc(p->path, p->length * sizeof(EmbPathObject*));
        if (!p->path)
            return 1;
        break;
    case EMB_POINT:
        p->point = realloc(p->point, p->length * sizeof(EmbVector));
        if (!p->point)
            return 1;
        break;
    case EMB_LINE:
        p->line = realloc(p->line, p->length * sizeof(EmbLine));
        if (!p->line)
            return 1;
        break;
    case EMB_POLYGON:
        p->polygon = realloc(p->polygon, p->length * sizeof(EmbPolygonObject*));
        if (!p->polygon)
            return 1;
        break;
    case EMB_POLYLINE:
        p->polyline = realloc(p->polyline, p->length * sizeof(EmbPolylineObject*));
        if (!p->polyline)
            return 1;
        break;
    case EMB_RECT:
        p->rect = realloc(p->rect, p->length * sizeof(EmbRect));
        if (!p->rect)
            return 1;
        break;
    case EMB_SPLINE:
        p->spline = realloc(p->spline, p->length * sizeof(EmbSplineObject));
        if (!p->spline)
            return 1;
        break;
    case EMB_STITCH:
        p->stitch = realloc(p->stitch, CHUNK_SIZE * sizeof(EmbStitch));
        if (!p->stitch)
            return 1;
        break;
    case EMB_THREAD:
        p->thread = realloc(p->thread, CHUNK_SIZE * sizeof(EmbThread));
        if (!p->thread)
            return 1;
        break;
    case EMB_VECTOR:
        p->vector = realloc(p->vector, CHUNK_SIZE * sizeof(EmbVector));
        if (!p->vector)
            return 1;
        break;
    default:
        break;
    }
    switch (p->type) {
    case EMB_ARC:
    case EMB_CIRCLE:
    case EMB_POINT:
    case EMB_LINE:
    case EMB_RECT:
        p->color = realloc(p->color, p->length * sizeof(EmbColor));
        if (!p->color)
            return 1;
        p->flag = realloc(p->flag, p->length * sizeof(int));
        if (!p->flag)
            return 1;
        break;
    case EMB_ELLIPSE:
        p->color = realloc(p->color, p->length * sizeof(EmbColor));
        if (!p->color)
            return 1;
        p->flag = realloc(p->flag, p->length * sizeof(int));
        if (!p->flag)
            return 1;
        p->floats = realloc(p->floats, p->length * sizeof(float));
        if (!p->floats)
            return 1;
        break;
    default:
        break;
    }
    return 0;
}

int embArray_addArc(EmbArray* p, EmbArc arc, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->arc[p->count - 1] = arc;
    p->flag[p->count - 1] = lineType;
    p->color[p->count - 1] = color;
    return 1;
}

int embArray_addCircle(EmbArray* p, EmbCircle circle, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->circle[p->count - 1] = circle;
    p->flag[p->count - 1] = lineType;
    p->color[p->count - 1] = color;
    return 1;
}

int embArray_addEllipse(EmbArray* p,
    EmbEllipse ellipse, float rotation, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->ellipse[p->count - 1] = ellipse;
    p->floats[p->count - 1] = rotation;
    p->flag[p->count - 1] = lineType;
    p->color[p->count - 1] = color;
    return 1;
}

int embArray_addFlag(EmbArray* p, int flag)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->flag[p->count - 1] = flag;
    return 1;
}

int embArray_addLine(EmbArray* p, EmbLine line, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->line[p->count - 1] = line;
    p->flag[p->count - 1] = lineType;
    p->color[p->count - 1] = color;
    return 1;
}

int embArray_addPath(EmbArray* p, EmbPathObject* path)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->path[p->count - 1] = (EmbPathObject*)malloc(sizeof(EmbPathObject));
    if (!p->path[p->count - 1]) {
        embLog("ERROR: emb-polygon.c embArray_create(), cannot allocate memory for heapPolygonObj\n");
        return 0;
    }
    p->path[p->count - 1] = path;
    return 1;
}

int embArray_addPoint(EmbArray* p, EmbVector point, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->point[p->count - 1] = point;
    p->flag[p->count - 1] = lineType;
    p->color[p->count - 1] = color;
    return 1;
}

int embArray_addPolygon(EmbArray* p, EmbPolygonObject* polygon)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->polygon[p->count - 1] = (EmbPolygonObject*)malloc(sizeof(EmbPolygonObject));
    if (!p->polygon[p->count - 1]) {
        embLog("ERROR: emb-polygon.c embArray_create(), cannot allocate memory for heapPolygonObj\n");
        return 0;
    }
    p->polygon[p->count - 1] = polygon;
    return 1;
}

int embArray_addPolyline(EmbArray* p, EmbPolylineObject* polyline)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->polyline[p->count - 1] = (EmbPolylineObject*)malloc(sizeof(EmbPolylineObject));
    if (!p->polyline[p->count - 1]) {
        embLog("ERROR: embArray_create(), cannot allocate memory for heapPolylineObj\n");
        return 0;
    }
    p->polyline[p->count - 1] = polyline;
    return 1;
}

int embArray_addRect(EmbArray* p,
    EmbRect rect, int lineType, EmbColor color)
{
    if (!p) {
        p = embArray_create(EMB_RECT);
        if (!p) {
            return 0;
        }
    }

    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->rect[p->count - 1] = rect;
    p->flag[p->count - 1] = lineType;
    p->color[p->count - 1] = color;
    return 1;
}

int embArray_addStitch(EmbArray* p, EmbStitch st)
{
    if (!p) {
        p = embArray_create(EMB_STITCH);
        if (!p) {
            return 0;
        }
    }
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->stitch[p->count - 1] = st;
    return 1;
}

int embArray_addThread(EmbArray* p, EmbThread thread)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->thread[p->count - 1] = thread;
    return 1;
}

int embArray_addVector(EmbArray* p, EmbVector vector)
{
    if (!p) {
        p = embArray_create(EMB_VECTOR);
        if (!p) {
            return 0;
        }
    }
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->vector[p->count - 1] = vector;
    return 1;
}

void embArray_free(EmbArray* p)
{
    int i;
    if (!p)
        return;

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
    switch (p->type) {
    case EMB_ARC:
    case EMB_CIRCLE:
    case EMB_POINT:
    case EMB_LINE:
    case EMB_RECT:
        free(p->color);
        free(p->flag);
        break;
    case EMB_ELLIPSE:
        free(p->color);
        free(p->flag);
        free(p->floats);
    default:
        break;
    }
    free(p);
}

void husExpand(unsigned char* input, unsigned char* output, int compressedSize, int compressionType)
{
    /* TODO: find and analyse some HUS encoded files and DST equivalents */
    output = (unsigned char*)malloc(compressedSize + 1);
}

int husCompress(unsigned char* input, unsigned long _inputSize, unsigned char* output, int compressionType, int outputSize)
{
    /* TODO: find and analyse some HUS encoded files and DST equivalents */
    output = (unsigned char*)malloc(outputSize + 1);
    return 0;
}

static char binaryReadByte(EmbFile* file)
{
    char c;
    embFile_read(&c, 1, 1, file);
    return c;
}

static int binaryReadBytes(EmbFile* file, unsigned char* destination, int count)
{
    return (int)embFile_read((char*)destination, 1, count, file);
}

/* Deal with endianness
 * -----------------------------------------------------------------------------
 */

static void two_char_order(unsigned char *s, char endianness)
{
    unsigned char c;
    if (endianTest[0] != endianness) {
        c = s[0];
        s[0] = s[1];
        s[1] = c;
    }
}

static void four_char_order(unsigned char *s, unsigned char endianness)
{
    unsigned char c;
    if (endianTest[0] != endianness) {
        c = s[0];
        s[0] = s[3];
        s[3] = c;
        c = s[1];
        s[1] = s[2];
        s[2] = c;
    }
}

/* Read to int types
 * -----------------------------------------------------------------------------
 */

static short binaryReadInt16(EmbFile* file)
{
    embFile_read(embBuffer, 1, 2, file);
    two_char_order(embBuffer, EMB_LITTLE_ENDIAN);
    return *((short *)embBuffer);
}

static int binaryReadInt32(EmbFile* file)
{
    embFile_read(embBuffer, 1, 4, file);
    four_char_order(embBuffer, EMB_LITTLE_ENDIAN);
    return *((int *)embBuffer);
}

static unsigned char binaryReadUInt8(EmbFile* file)
{
    unsigned char c;
    embFile_read(&c, 1, 1, file);
    return c;
}

static unsigned short binaryReadUInt16(EmbFile* file)
{
    embFile_read(embBuffer, 1, 2, file);
    two_char_order(embBuffer, EMB_LITTLE_ENDIAN);
    return *((unsigned short *)embBuffer);
}

static unsigned int binaryReadUInt32(EmbFile* file)
{
    embFile_read(embBuffer, 1, 4, file);
    four_char_order(embBuffer, EMB_LITTLE_ENDIAN);
    return *((unsigned int *)embBuffer);
}

/* Big endian version */
static short binaryReadInt16BE(EmbFile* file)
{
    embFile_read(embBuffer, 1, 2, file);
    two_char_order(embBuffer, EMB_BIG_ENDIAN);
    return *((short *)embBuffer);
}

/* Big endian version */
static unsigned short binaryReadUInt16BE(EmbFile* file)
{
    embFile_read(embBuffer, 1, 2, file);
    two_char_order(embBuffer, EMB_BIG_ENDIAN);
    return *((unsigned short *)embBuffer);
}

/* Big endian version */
static int binaryReadInt32BE(EmbFile* file)
{
    embFile_read(embBuffer, 1, 4, file);
    four_char_order(embBuffer, EMB_BIG_ENDIAN);
    return *((int *)embBuffer);
}

/* Big endian version */
static unsigned int binaryReadUInt32BE(EmbFile* file)
{
    embFile_read(embBuffer, 1, 4, file);
    four_char_order(embBuffer, EMB_BIG_ENDIAN);
    return *((unsigned int *)embBuffer);
}

static void binaryReadString(EmbFile* file, char* buffer, int maxLength)
{
    int i;
    for (i=0; i < maxLength; i++) {
        embFile_read(buffer+i, 1, 1, file);
        if (!buffer[i])
            break;
    }
}

static float binaryReadFloat(EmbFile* file)
{
    float a;
    int idata = binaryReadInt32(file);
    memory_copy(&a, &idata, 4);
    return a;
}

static void binaryWriteByte(EmbFile* file, unsigned char data)
{
    embFile_write(&data, 1, 1, file);
}

static void binaryWriteBytes(EmbFile* file, const char* data, int size)
{
    embFile_write((char*)data, 1, size, file);
}

static void binaryWriteShort(EmbFile* file, short data)
{
    memory_copy(embBuffer, (unsigned char *)(&data), 2);
    two_char_order(embBuffer, EMB_LITTLE_ENDIAN);
    embFile_write(embBuffer, 1, 2, file);
}

static void binaryWriteShortBE(EmbFile* file, short data)
{
    memory_copy(embBuffer, (unsigned char *)(&data), 2);
    two_char_order(embBuffer, EMB_BIG_ENDIAN);
    embFile_write(embBuffer, 1, 2, file);
}

static void binaryWriteUShort(EmbFile* file, unsigned short data)
{
    memory_copy(embBuffer, (unsigned char *)(&data), 2);
    two_char_order(embBuffer, EMB_LITTLE_ENDIAN);
    embFile_write(embBuffer, 1, 2, file);
}

static void binaryWriteUShortBE(EmbFile* file, unsigned short data)
{
    memory_copy(embBuffer, (unsigned char *)(&data), 2);
    two_char_order(embBuffer, EMB_BIG_ENDIAN);
    embFile_write(embBuffer, 1, 2, file);
}

static void binaryWriteInt(EmbFile* file, int data)
{
    memory_copy(embBuffer, (unsigned char *)(&data), 4);
    four_char_order(embBuffer, EMB_LITTLE_ENDIAN);
    embFile_write(embBuffer, 1, 2, file);
}

static void binaryWriteIntBE(EmbFile* file, int data)
{
    memory_copy(embBuffer, (unsigned char *)(&data), 4);
    four_char_order(embBuffer, EMB_BIG_ENDIAN);
    embFile_write(embBuffer, 1, 2, file);
}

static void binaryWriteUInt(EmbFile* file, unsigned int data)
{
    memory_copy(embBuffer, (unsigned char *)(&data), 4);
    four_char_order(embBuffer, EMB_LITTLE_ENDIAN);
    embFile_write(embBuffer, 1, 2, file);
}

static void binaryWriteUIntBE(EmbFile* file, unsigned int data)
{
    memory_copy(embBuffer, (unsigned char *)(&data), 4);
    four_char_order(embBuffer, EMB_BIG_ENDIAN);
    embFile_write(embBuffer, 1, 2, file);
}

static void binaryWriteFloat(EmbFile* file, float data)
{
    int idata;
    memory_copy(&idata, &data, 4);
    binaryWriteUInt(file, idata);
}

static int emb_ceil(float src)
{
    return (int)(src)+1;
}

static int emb_floor(float src)
{
    return (int)(src);
}

/* Rounds a float (src) and returns it as an int.
 *
 * We assume that the source is within.
 */
static int roundDouble(float src)
{
    if (src < 0.0) {
        return emb_ceil(src - 0.5);
    }
    return emb_floor(src + 0.5);
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

/* Replacing the %d in *printf functionality.
 */
static void embPointerToArray(char* buffer, void* pointer, int maxDigits)
{
    unsigned int i, value;
    value = (unsigned long int)pointer;
    for (i = 0; i < maxDigits - 1; i++) {
        buffer[i] = ' ';
    }
    buffer[maxDigits - 1] = 0;
    for (; i >= 0; i--) {
        buffer[i] = (value % 16) - '0';
        if (buffer[i] > '9')
            buffer[i] += 'A' - '9';
        value /= 16;
        if (value == 0)
            break;
    }
    buffer += i;
}

/* Replacing the %d in *printf functionality.
 *
 * Accounts for the sign of the 
 */
static void embIntToArray(char* buffer, int number, int maxDigits)
{
    int i, j, sign;
    unsigned int unumber;
    sign = 0;
    unumber = number;
    if (number < 0.0) {
        unumber = -number;
        sign = 1;
    }
    for (i = 0; i < maxDigits - 2; i++) {
        buffer[i] = ' ';
    }
    buffer[maxDigits - 1] = 0;
    for (i = maxDigits - 2; i >= 0; i--) {
        printf("%s %d %d\n", buffer, i, unumber);
        buffer[i] = (char)(unumber % 10) + '0';
        unumber = unumber / 10;
        if (unumber == 0)
            break;
    }
    if (sign) {
        buffer[i] = '-';
    }
    /* left shift to the front of the buffer so the buffer doesn't change
     * size in later use
     */
    for (j = 0; j < maxDigits - i; j++) {
        buffer[j] = buffer[i + j];
    }
}

static void writeInt(EmbFile* file, int n, int m)
{
    char buffer[30];
    embIntToArray(buffer, n, m);
    embFile_print(file, buffer);
}

/* Replacing the %f in *printf functionality.
 */
static void embFloatToArray(char* buffer, float number, float tolerence, int before, int after)
{
    int i, maxDigits, j;
    float t;
    float afterPos[] = { 1.0e-1, 1.0e-2, 1.0e-3, 1.0e-4, 1.0e-5, 1.0e-6, 1.0e-7, 1.0e-8 };
    float beforePos[] = { 1.0, 1.0e1, 1.0e2, 1.0e3, 1.0e4, 1.0e5, 1.0e6, 1.0e7, 1.0e8 };
    maxDigits = before + after + 1;
    for (i = 0; i < maxDigits - 1; i++) {
        buffer[i] = ' ';
    }
    buffer[maxDigits - 1] = 0;
    for (i = before - 1; i >= 0; i--) {
        t = 0.0;
        for (j = 0; j < 9; j++) {
            t += beforePos[i];
            printf("%s %d %d %f %f\n", buffer, i, j, t, number);
            if ((number - tolerence > t) && (t + beforePos[i] > number + tolerence)) {
                buffer[before - 1 - i] = j + '1';
                number -= (j + 1) * beforePos[i];
                break;
            }
        }
    }
    buffer[before] = '.';
    for (i = 0; i < after; i++) {
        t = 0.0;
        for (j = 0; j < 9; j++) {
            t += afterPos[i];
            printf("%s %d %d %f %f\n", buffer, i, j, t, number);
            if ((number - tolerence > t) && (t + afterPos[i] > number + tolerence)) {
                buffer[before + 1 + i] = j + '1';
                number -= (j + 1) * afterPos[i];
                break;
            }
        }
    }
    buffer[before + 1 + after] = 0;
    /* lTrim(buffer, ' '); */
}

/* puts() abstraction. Uses Serial.print() on ARDUINO */
static void embLog(const char* str)
{
#if ARDUINO
    inoLog_serial(str);
    inoLog_serial("\n");
#else
    puts(str);
#endif
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
        embLog("Arc and Bulge direction do not match.\n");
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
       a stated (float) tolerence value would help.
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
        embLog("ERROR: embLine_normalVector(), result==0\n");
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
    float tolerence, det;
    tolerence = 1e-10;
    embVector_subtract(line1.end, line1.start, &D2);
    C.y = embVector_cross(line1.start, D2);

    embVector_subtract(line2.end, line2.start, &D1);
    C.x = embVector_cross(line2.start, D1);

    det = embVector_cross(D1, D2);

    if (!result) {
        embLog("ERROR: embLine_intersectionPoint(), result==0\n");
        return 0;
    }
    /*TODO: The code below needs revised since division by zero can still occur */
    if (fabs(det) < tolerence) {
        embLog("ERROR: Intersecting lines cannot be parallel.\n");
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
        embLog("ERROR: embVector_normalize(), result==0\n");
        return;
    }
    result->x = vector.x / length;
    result->y = vector.y / length;
}

/**
 * The scalar multiple \a magnatude of a vector \a vector. Returned as
 * \a result.
 */
void embVector_multiply(EmbVector vector, float magnitude, EmbVector* result)
{
    if (!result) {
        embLog("ERROR: embVector_multiply(), result==0\n");
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
        embLog("ERROR: embVector_add(), result==0\n");
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
        embLog("ERROR: embVector_average(), result==0\n");
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
        embLog("ERROR: embVector_subtract(), result==0\n");
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
void embVector_transposeProduct(EmbVector v1, EmbVector v2, EmbVector* result)
{
    if (!result) {
        embLog("ERROR: embVector_transpose_product(), result==0\n");
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
    EmbPattern* p = 0;
    p = (EmbPattern*)malloc(sizeof(EmbPattern));
    if (!p) {
        embLog("ERROR: embPattern_create(), unable to allocate memory for p\n");
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
    p->lastPosition.x = 0.0;
    p->lastPosition.y = 0.0;

    return p;
}

void embPattern_hideStitchesOverLength(EmbPattern* p, int length)
{
    float prevX, prevY;
    int i;
    EmbStitch st;

    if (!p) {
        embLog("ERROR: embPattern_hideStitchesOverLength(), p==0\n");
        return;
    }

    prevX = 0;
    prevY = 0;
    for (i = 0; i < p->stitchList->count; i++) {
        st = p->stitchList->stitch[i];
        if ((fabs(st.x - prevX) > length) || (fabs(st.y - prevY) > length)) {
            st.flags |= TRIM;
            st.flags &= ~NORMAL;
        }
        prevX = st.x;
        prevY = st.y;
    }
}

int embPattern_addThread(EmbPattern* p, EmbThread thread)
{
    if (!p) {
        embLog("ERROR: embPattern_addThread(), p==0\n");
        return 0;
    }
    if (!p->threads) {
        p->threads = embArray_create(EMB_THREAD);
    }
    embArray_addThread(p->threads, thread);
    return 1;
}

void embPattern_fixColorCount(EmbPattern* p)
{
    /* fix color count to be max of color index. */
    int maxColorIndex = 0, i;

    if (!p) {
        embLog("ERROR: embPattern_fixColorCount(), p==0\n");
        return;
    }
    for (i = 0; i < p->stitchList->count; i++) {
        maxColorIndex = emb_max_int(maxColorIndex, p->stitchList->stitch[i].color);
    }
    while (p->threads->count <= maxColorIndex) {
        embPattern_addThread(p, embThread_getRandom());
    }
    /*
    while (p->threadLists->count > (maxColorIndex + 1)) {
        TODO: erase last color    p->threadList.pop_back();
    }
    */
}

/*! Copies all of the EmbStitchList data to EmbPolylineObjectList data for pattern (\a p). */
void embPattern_copyStitchListToPolylines(EmbPattern* p)
{
    EmbVector point;
    int breakAtFlags, i;
    EmbStitch st;

    if (!p) {
        embLog("ERROR: embPattern_copyStitchListToPolylines(), p==0\n");
        return;
    }

    breakAtFlags = (STOP | JUMP | TRIM);

    for (i = 0; i < p->stitchList->count; i++) {
        EmbArray* pointList;
        EmbColor color;
        pointList = 0;
        for (i = 0; i < p->stitchList->count; i++) {
            st = p->stitchList->stitch[i];
            if (st.flags & breakAtFlags) {
                break;
            }
            if (!(st.flags & JUMP)) {
                if (!pointList) {
                    pointList = embArray_create(EMB_POINT);
                    color = p->threads->thread[st.color].color;
                }
                point.x = st.x;
                point.y = st.y;
                embArray_addPoint(pointList, point, 0, color);
            }
        }

        /* NOTE: Ensure empty polylines are not created. This is critical. */
        if (pointList) {
            EmbPolylineObject* currentPolyline = (EmbPolylineObject*)malloc(sizeof(EmbPolylineObject));
            if (!currentPolyline) {
                embLog("ERROR: embPattern_copyStitchListToPolylines(), cannot allocate memory for currentPolyline\n");
                return;
            }
            currentPolyline->pointList = pointList;
            currentPolyline->color = color;
            currentPolyline->lineType = 1;
            /* TODO: Determine what the correct value should be. */

            if (!p->polylines) {
                p->polylines = embArray_create(EMB_POLYLINE);
            }
            embArray_addPolyline(p->polylines, currentPolyline);
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
        embLog("ERROR: embPattern_copyPolylinesToStitchList(), p==0\n");
        return;
    }
    if (!p->polylines) {
        embLog("ERROR: embPattern_copyPolylinesToStitchList(), p==0\n");
        return;
    }
    for (i = 0; i < p->polylines->count; i++) {
        EmbPolylineObject* currentPoly = 0;
        EmbArray* currentPointList = 0;
        EmbThread thread;

        currentPoly = p->polylines->polyline[i];
        if (!currentPoly) {
            embLog("ERROR: embPattern_copyPolylinesToStitchList(), currentPoly is null\n");
            return;
        }
        currentPointList = currentPoly->pointList;
        if (!currentPointList) {
            embLog("ERROR: embPattern_copyPolylinesToStitchList(), currentPointList is null\n");
            return;
        }

        string_copy(thread.catalogNumber, "NULL");
        thread.color = currentPoly->color;
        string_copy(thread.description, "NULL");
        embPattern_addThread(p, thread);

        if (!firstObject) {
            embPattern_addStitchAbs(p, currentPointList->point[0].x, currentPointList->point[0].y, TRIM, 1);
            embPattern_addStitchRel(p, 0.0, 0.0, STOP, 1);
        }

        embPattern_addStitchAbs(p, currentPointList->point[0].x, currentPointList->point[0].y, JUMP, 1);
        for (j = 1; j < currentPointList->count; j++) {
            embPattern_addStitchAbs(p, currentPointList->point[j].x, currentPointList->point[j].y, NORMAL, 1);
        }
        firstObject = 0;
    }
}

/*! Moves all of the EmbStitchList data to EmbPolylineObjectList data for pattern (\a p). */
void embPattern_moveStitchListToPolylines(EmbPattern* p)
{
    if (!p) {
        embLog("ERROR: embPattern_moveStitchListToPolylines(), p==0\n");
        return;
    }
    embPattern_copyStitchListToPolylines(p);
    /* Free the stitchList and threadList since their data has now been transferred to polylines */
    embArray_free(p->stitchList);
    embArray_free(p->threads);
}

/*! Moves all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
void embPattern_movePolylinesToStitchList(EmbPattern* p)
{
    if (!p) {
        embLog("ERROR: embPattern_movePolylinesToStitchList(), p==0\n");
        return;
    }
    embPattern_copyPolylinesToStitchList(p);
    embArray_free(p->polylines);
}

/*! Adds a stitch to the pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
void embPattern_addStitchAbs(EmbPattern* p, float x, float y, int flags, int isAutoColorIndex)
{
    EmbStitch s;
    EmbVector home;

    if (!p || !p->stitchList) {
        embLog("ERROR: embPattern_addStitchAbs(), p==0\n");
        return;
    }

    if (flags & END) {
        if (p->stitchList->count == 0) {
            return;
        }
        /* Prevent unnecessary multiple END stitches */
        if (p->stitchList->stitch[p->stitchList->count - 1].flags & END) {
            embLog("ERROR: embPattern_addStitchAbs(), found multiple END stitches\n");
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

    /* NOTE: If the stitchList is empty, we will create it before adding stitches to it.
     * The first coordinate will be the HOME position. */
    if (!p->stitchList) {
        /* NOTE: Always HOME the machine before starting any stitching */
        home = embSettings_home(&(p->settings));
        s.x = home.x;
        s.y = home.y;
        s.flags = JUMP;
        s.color = p->currentColorIndex;
        p->stitchList = embArray_create(EMB_STITCH);
        embArray_addStitch(p->stitchList, s);
    }

    s.x = x;
    s.y = y;
    s.flags = flags;
    s.color = p->currentColorIndex;
    embArray_addStitch(p->stitchList, s);
    p->lastPosition.x = s.x;
    p->lastPosition.y = s.y;
}

/*! Adds a stitch to the pattern (\a p) at the relative position (\a dx,\a dy) to the previous stitch. Positive y is up. Units are in millimeters. */
void embPattern_addStitchRel(EmbPattern* p, float dx, float dy, int flags, int isAutoColorIndex)
{
    EmbVector home;
    float x, y;

    if (!p) {
        embLog("ERROR: embPattern_addStitchRel(), p==0\n");
        return;
    }
    if (p->stitchList) {
        x = p->lastPosition.x + dx;
        y = p->lastPosition.y + dy;
    } else {
        /* NOTE: The stitchList is empty, so add it to the HOME position.
         * The embStitchList_create function will ensure the first coordinate is at the HOME position. */
        home = embSettings_home(&(p->settings));
        x = home.x + dx;
        y = home.y + dy;
    }
    embPattern_addStitchAbs(p, x, y, flags, isAutoColorIndex);
}

void embPattern_changeColor(EmbPattern* p, int index)
{
    if (!p) {
        embLog("ERROR: embPattern_changeColor(), p==0\n");
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
        embLog("ERROR: embPattern_read(), unsupported read file type:");
        embLog(fileName);
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
        embLog("ERROR: embPattern_write(), unsupported write file type:");
        embLog(fileName);
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
        embLog("ERROR: embPattern_scale(), p==0\n");
        return;
    }

    for (i = 0; i < p->stitchList->count; i++) {
        p->stitchList->stitch[i].x *= scale;
        p->stitchList->stitch[i].y *= scale;
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
        embLog("ERROR: embPattern_calcBoundingBox(), p==0\n");
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

    for (i = 0; i < p->stitchList->count; i++) {
        /* If the point lies outside of the accumulated bounding
        * rectangle, then inflate the bounding rect to include it. */
        pt = p->stitchList->stitch[i];
        if (!(pt.flags & TRIM)) {
            boundingRect.left = emb_min_float(boundingRect.left, pt.x);
            boundingRect.top = emb_min_float(boundingRect.top, pt.y);
            boundingRect.right = emb_max_float(boundingRect.right, pt.x);
            boundingRect.bottom = emb_max_float(boundingRect.bottom, pt.y);
        }
    }

    if (p->arcs) {
        /* TODO: embPattern_calcBoundingBox for arcs, for now just checks the start point */
        for (i = 0; i < p->arcs->count; i++) {
            EmbArc arc = p->arcs->arc[i];
            boundingRect.left = emb_min_float(boundingRect.left, arc.start.x);
            boundingRect.top = emb_min_float(boundingRect.top, arc.start.y);
            boundingRect.right = emb_max_float(boundingRect.right, arc.start.x);
            boundingRect.bottom = emb_max_float(boundingRect.bottom, arc.start.y);
        }
    }

    if (p->circles) {
        for (i = 0; i < p->circles->count; i++) {
            EmbCircle circle = p->circles->circle[i];
            boundingRect.left = emb_min_float(boundingRect.left, circle.center.x - circle.radius);
            boundingRect.top = emb_min_float(boundingRect.top, circle.center.y - circle.radius);
            boundingRect.right = emb_max_float(boundingRect.right, circle.center.x + circle.radius);
            boundingRect.bottom = emb_max_float(boundingRect.bottom, circle.center.y + circle.radius);
        }
    }

    if (p->ellipses) {
        for (i = 0; i < p->ellipses->count; i++) {
            /* TODO: account for rotation */
            EmbEllipse ellipse = p->ellipses->ellipse[i];
            boundingRect.left = emb_min_float(boundingRect.left, ellipse.center.x - ellipse.radius.x);
            boundingRect.top = emb_min_float(boundingRect.top, ellipse.center.y - ellipse.radius.y);
            boundingRect.right = emb_max_float(boundingRect.right, ellipse.center.x + ellipse.radius.x);
            boundingRect.bottom = emb_max_float(boundingRect.bottom, ellipse.center.y + ellipse.radius.y);
        }
    }

    if (p->lines) {
        for (i = 0; i < p->lines->count; i++) {
            EmbLine line = p->lines->line[i];
            boundingRect.left = emb_min_float(boundingRect.left, emb_min_float(line.start.x, line.end.x));
            boundingRect.top = emb_min_float(boundingRect.top, emb_min_float(line.start.y, line.end.y));
            boundingRect.right = emb_max_float(boundingRect.right, emb_max_float(line.start.x, line.end.x));
            boundingRect.bottom = emb_max_float(boundingRect.bottom, emb_max_float(line.start.y, line.end.y));
        }
    }

    if (p->points) {
        for (i = 0; i < p->points->count; i++) {
            EmbVector point = p->points->point[i];
            boundingRect.left = emb_min_float(boundingRect.left, point.x);
            boundingRect.top = emb_min_float(boundingRect.top, point.y);
            boundingRect.right = emb_max_float(boundingRect.right, point.x);
            boundingRect.bottom = emb_max_float(boundingRect.bottom, point.y);
        }
    }

    if (p->polygons) {
        for (i = 0; i < p->polygons->count; i++) {
            EmbArray* polygon;
            polygon = p->polygons->polygon[i]->pointList;
            for (j = 0; j < polygon->count; j++) {
                boundingRect.left = emb_min_float(boundingRect.left, polygon[i].vector[j].x);
                boundingRect.top = emb_min_float(boundingRect.top, polygon[i].vector[j].y);
                boundingRect.right = emb_max_float(boundingRect.right, polygon[i].vector[j].x);
                boundingRect.bottom = emb_max_float(boundingRect.bottom, polygon[i].vector[j].y);
            }
        }
    }

    if (p->polylines) {
        for (i = 0; i < p->polylines->count; i++) {
            EmbArray* polyline;
            polyline = p->polylines->polyline[i]->pointList;
            for (j = 0; j < polyline->count; j++) {
                boundingRect.left = emb_min_float(boundingRect.left, polyline[i].vector[j].x);
                boundingRect.top = emb_min_float(boundingRect.top, polyline[i].vector[j].y);
                boundingRect.right = emb_max_float(boundingRect.right, polyline[i].vector[j].x);
                boundingRect.bottom = emb_max_float(boundingRect.bottom, polyline[i].vector[j].y);
            }
        }
    }

    if (p->rects) {
        for (i = 0; i < p->rects->count; i++) {
            EmbRect rect = p->rects->rect[i];
            /* TODO: other points */
            boundingRect.left = emb_min_float(boundingRect.left, rect.left);
            boundingRect.top = emb_min_float(boundingRect.top, rect.left);
            boundingRect.right = emb_max_float(boundingRect.right, rect.left);
            boundingRect.bottom = emb_max_float(boundingRect.bottom, rect.left);
        }
    }

    if (p->splines) {
        for (i = 0; i < p->splines->count; i++) {
            bezier = p->splines->spline[i].bezier;
            /* TODO: other points */
            boundingRect.left = emb_min_float(boundingRect.left, bezier.start.x);
            boundingRect.top = emb_min_float(boundingRect.top, bezier.start.y);
            boundingRect.right = emb_max_float(boundingRect.right, bezier.start.x);
            boundingRect.bottom = emb_max_float(boundingRect.bottom, bezier.start.y);
        }
    }

    return boundingRect;
}

/*! Flips the entire pattern (\a p) horizontally about the y-axis. */
void embPattern_flipHorizontal(EmbPattern* p)
{
    if (!p) {
        embLog("ERROR: embPattern_flipHorizontal(), p==0\n");
        return;
    }
    embPattern_flip(p, 1, 0);
}

/*! Flips the entire pattern (\a p) vertically about the x-axis. */
void embPattern_flipVertical(EmbPattern* p)
{
    if (!p) {
        embLog("ERROR: embPattern_flipVertical(), p==0\n");
        return;
    }
    embPattern_flip(p, 0, 1);
}

/*! Flips the entire pattern (\a p) horizontally about the x-axis if (\a horz) is true.
 *  Flips the entire pattern (\a p) vertically about the y-axis if (\a vert) is true. */
void embPattern_flip(EmbPattern* p, int horz, int vert)
{
    int i, j;
    /* EmbVector flip; */

    if (!p) {
        embLog("ERROR: embPattern_flip(), p==0\n");
        return;
    }

    /*
    flip.x = 1.0;
    flip.y = 1.0;
    if (horz) {
        flip.x = -1.0;
    }
    if (vert) {
        flip.y = -1.0;
    }
    
    then use embVector_product
    */

    if (p->stitchList) {
        for (i = 0; i < p->stitchList->count; i++) {
            if (horz) {
                p->stitchList->stitch[i].x *= -1.0;
            }
            if (vert) {
                p->stitchList->stitch[i].y *= -1.0;
            }
        }
    }

    if (p->arcs) {
        for (i = 0; i < p->arcs->count; i++) {
            if (horz) {
                p->arcs->arc[i].start.x *= -1.0;
                p->arcs->arc[i].mid.x *= -1.0;
                p->arcs->arc[i].end.x *= -1.0;
            }
            if (vert) {
                p->arcs->arc[i].start.y *= -1.0;
                p->arcs->arc[i].mid.y *= -1.0;
                p->arcs->arc[i].end.y *= -1.0;
            }
        }
    }

    if (p->circles) {
        for (i = 0; i < p->circles->count; i++) {
            if (horz) {
                p->circles->circle[i].center.x *= -1.0;
            }
            if (vert) {
                p->circles->circle[i].center.y *= -1.0;
            }
        }
    }

    if (p->ellipses) {
        for (i = 0; i < p->ellipses->count; i++) {
            if (horz) {
                p->ellipses->ellipse[i].center.x *= -1.0;
            }
            if (vert) {
                p->ellipses->ellipse[i].center.y *= -1.0;
            }
        }
    }

    if (p->lines) {
        for (i = 0; i < p->lines->count; i++) {
            if (horz) {
                p->lines->line[i].start.x *= -1.0;
                p->lines->line[i].end.x *= -1.0;
            }
            if (vert) {
                p->lines->line[i].start.y *= -1.0;
                p->lines->line[i].end.y *= -1.0;
            }
        }
    }

    if (p->paths) {
        for (i = 0; i < p->paths->count; i++) {
            EmbArray* path = p->paths->path[i]->pointList;
            for (j = 0; j < path->count; j++) {
                if (horz) {
                    path->point[j].x *= -1.0;
                }
                if (vert) {
                    path->point[j].y *= -1.0;
                }
            }
        }
    }

    if (p->points) {
        for (i = 0; i < p->points->count; i++) {
            if (horz) {
                p->points->point[i].x *= -1.0;
            }
            if (vert) {
                p->points->point[i].y *= -1.0;
            }
        }
    }

    if (p->polygons) {
        for (i = 0; i < p->polygons->count; i++) {
            EmbArray* polygon;
            polygon = p->polygons->polygon[i]->pointList;
            for (j = 0; j < polygon->count; j++) {
                if (horz) {
                    polygon->point[j].x *= -1.0;
                }
                if (vert) {
                    polygon->point[j].y *= -1.0;
                }
            }
        }
    }

    if (p->polylines) {
        for (i = 0; i < p->polylines->count; i++) {
            EmbArray* polyline;
            polyline = p->polylines->polygon[i]->pointList;
            for (j = 0; j < polyline->count; j++) {
                if (horz) {
                    polyline->point[j].x *= -1.0;
                }
                if (vert) {
                    polyline->point[j].y *= -1.0;
                }
            }
        }
    }

    if (p->rects) {
        for (i = 0; i < p->rects->count; i++) {
            if (horz) {
                p->rects->rect[i].left *= -1.0;
                p->rects->rect[i].right *= -1.0;
            }
            if (vert) {
                p->rects->rect[i].top *= -1.0;
                p->rects->rect[i].bottom *= -1.0;
            }
        }
    }

    if (p->splines) {
        for (i = 0; i < p->splines->count; i++) {
            /* TODO: embPattern_flip for splines */
        }
    }
}

/* Does this need a tolerence to stop really long jumps?
 */
void embPattern_combineJumpStitches(EmbPattern* p)
{
    int jump = 0, i, j;
    EmbStitch st;

    if (!p) {
        embLog("ERROR: embPattern_combineJumpStitches(), p==0\n");
        return;
    }

    j = 0;
    for (i = 0; i < p->stitchList->count; i++) {
        st = p->stitchList->stitch[i];
        p->stitchList->stitch[j] = st;
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
    p->stitchList->count = j + 1;
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
        embLog("ERROR: embPattern_correctForMaxStitchLength(), p==0\n");
        return;
    }
    if (p->stitchList->count > 1) {
        newList = embArray_create(EMB_STITCH);
        embArray_addStitch(newList, p->stitchList->stitch[0]);
        for (i = 1; i < p->stitchList->count; i++) {
            st.x = p->stitchList->stitch[i - 1].x;
            st.y = p->stitchList->stitch[i - 1].y;
            diff.x = p->stitchList->stitch[i].x - st.x;
            diff.y = p->stitchList->stitch[i].y - st.y;
            maxXY = embVector_getLength(diff);
            if (maxXY > maxStitchLength) {
                if (p->stitchList->stitch[i].flags & (JUMP | TRIM))
                    maxLen = maxJumpLength;
                else
                    maxLen = maxStitchLength;

                splits = (int)emb_ceil((float)maxXY / maxLen);

                if (splits > 1) {
                    embVector_multiply(diff, (float)(1.0 / splits), &add);

                    for (j = 1; j < splits; j++) {
                        EmbStitch s;
                        s = p->stitchList->stitch[i - 1];
                        s.x += add.x * j;
                        s.y += add.y * j;
                        embArray_addStitch(newList, s);
                    }
                }
            }
            embArray_addStitch(newList, p->stitchList->stitch[i]);
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
        embLog("ERROR: embPattern_center(), p==0\n");
        return;
    }
    boundingRect = embPattern_calcBoundingBox(p);

    moveLeft = (int)(boundingRect.left - (embRect_width(boundingRect) / 2.0));
    moveTop = (int)(boundingRect.top - (embRect_height(boundingRect) / 2.0));

    for (i = 0; i < p->stitchList->count; i++) {
        s = p->stitchList->stitch[i];
        s.x -= moveLeft;
        s.y -= moveTop;
    }
}

/* TODO: Description needed. */
void embPattern_loadExternalColorFile(EmbPattern* p, const char* fileName)
{
    char *dotPos, *extractName;
    char hasRead;

    extractName = (char*)malloc(string_length(fileName) + 5);
    if (!extractName) {
        embLog("ERROR: embPattern_loadExternalColorFile(), cannot allocate memory for extractName\n");
        return;
    }

    hasRead = 0;
    string_copy(extractName, fileName);
    dotPos = strrchr(fileName, '.');
    *dotPos = 0;
    strcat(extractName, ".edr");
    hasRead = embPattern_readAuto(p, extractName);
    if (!hasRead) {
        string_copy(extractName, fileName);
        *dotPos = 0;
        strcat(extractName, ".rgb");
        hasRead = embPattern_readAuto(p, extractName);
    }
    if (!hasRead) {
        string_copy(extractName, fileName);
        *dotPos = 0;
        strcat(extractName, ".col");
        hasRead = embPattern_readAuto(p, extractName);
    }
    if (!hasRead) {
        string_copy(extractName, fileName);
        *dotPos = 0;
        strcat(extractName, ".inf");
        hasRead = embPattern_readAuto(p, extractName);
    }
    free(extractName);
}

/*! Frees all memory allocated in the pattern (\a p). */
void embPattern_free(EmbPattern* p)
{
    if (!p) {
        embLog("ERROR: embPattern_free(), p==0\n");
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
void embPattern_addCircleObjectAbs(EmbPattern* p, float cx, float cy, float r)
{
    EmbCircle circle;
    circle.center.x = cx;
    circle.center.y = cy;
    circle.radius = r;

    if (!p) {
        embLog("ERROR: embPattern_addCircleObjectAbs(), p==0\n");
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
void embPattern_addEllipseObjectAbs(EmbPattern* p, float cx, float cy, float rx, float ry)
{
    EmbEllipse ellipse;
    ellipse.center.x = cx;
    ellipse.center.y = cy;
    ellipse.radius.x = rx;
    ellipse.radius.y = ry;

    if (!p) {
        embLog("ERROR: embPattern_addEllipseObjectAbs(), p==0\n");
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
void embPattern_addLineObjectAbs(EmbPattern* p, float x1, float y1, float x2, float y2)
{
    EmbLine line;
    line.start.x = x1;
    line.start.y = y1;
    line.end.x = x2;
    line.end.y = y2;

    if (!p) {
        embLog("ERROR: embPattern_addLineObjectAbs(), p==0\n");
        return;
    }
    if (!p->lines) {
        p->lines = embArray_create(EMB_LINE);
    }
    embArray_addLine(p->lines, line, 0, black);
}

void embPattern_addPathObjectAbs(EmbPattern* p, EmbPathObject* obj)
{
    if (!p) {
        embLog("ERROR: embPattern_addPathObjectAbs(), p==0\n");
        return;
    }
    if (!obj) {
        embLog("ERROR: embPattern_addPathObjectAbs(), obj==0\n");
        return;
    }
    if (!obj->pointList) {
        embLog("ERROR: embPattern_addPathObjectAbs(), obj->pointList is empty\n");
        return;
    }

    if (!p->paths) {
        p->paths = embArray_create(EMB_PATH);
    }
    embArray_addPath(p->paths, obj);
}

/*! Adds a point object to pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
void embPattern_addPointObjectAbs(EmbPattern* p, float x, float y)
{
    EmbVector point;
    point.x = x;
    point.y = y;

    if (!p) {
        embLog("ERROR: embPattern_addPointObjectAbs(), p==0\n");
        return;
    }
    if (!p->points) {
        p->points = embArray_create(EMB_POINT);
    }
    embArray_addPoint(p->points, point, 0, black);
}

void embPattern_addPolygonObjectAbs(EmbPattern* p, EmbPolygonObject* obj)
{
    if (!p) {
        embLog("ERROR: embPattern_addPolygonObjectAbs(), p==0\n");
        return;
    }
    if (!obj) {
        embLog("ERROR: embPattern_addPolygonObjectAbs(), obj==0\n");
        return;
    }
    if (!obj->pointList) {
        embLog("ERROR: embPattern_addPolygonObjectAbs(), obj->pointList is empty\n");
        return;
    }

    if (!p->polygons) {
        p->polygons = embArray_create(EMB_POLYGON);
    }
    embArray_addPolygon(p->polygons, obj);
}

void embPattern_addPolylineObjectAbs(EmbPattern* p, EmbPolylineObject* obj)
{
    if (!p) {
        embLog("ERROR: embPattern_addPolylineObjectAbs(), p==0\n");
        return;
    }
    if (!obj) {
        embLog("ERROR: embPattern_addPolylineObjectAbs(), obj==0\n");
        return;
    }
    if (!obj->pointList) {
        embLog("ERROR: embPattern_addPolylineObjectAbs(), obj->pointList is empty\n");
        return;
    }

    if (!p->polylines) {
        p->polylines = embArray_create(EMB_POLYLINE);
    }
    embArray_addPolyline(p->polylines, obj);
}

static void embPattern_colorBlock16(EmbPattern *pattern, EmbFile *file)
{
    int i;

    /* write remaining colors to reach 16 */
    memory_set(embBuffer, 0, 16*4);

    for (i = 0; i < pattern->threads->count; i++) {
        embColor_toStr(pattern->threads->thread[i].color, embBuffer+4*i);
    }

    embFile_write(embBuffer, 1, 16*4, file);
}

/**
 * Adds a rectangle object to pattern (\a p) at the absolute position
 * (\a x,\a y) with a width of (\a w) and a height of (\a h).
 * Positive y is up. Units are in millimeters.
 */
void embPattern_addRectObjectAbs(EmbPattern* p, float x, float y, float w, float h)
{
    EmbRect rect;
    rect.left = x;
    rect.top = y;
    rect.right = x + w;
    rect.bottom = y + h;

    if (!p) {
        embLog("ERROR: embPattern_addRectObjectAbs(), p==0\n");
        return;
    }
    if (!p->rects) {
        p->rects = embArray_create(EMB_RECT);
    }
    embArray_addRect(p->rects, rect, 0, black);
}

/* Initializes and returns an EmbSettings */
EmbSettings embSettings_init(void)
{
    EmbSettings settings;
    settings.dstJumpsPerTrim = 6;
    settings.home.x = 0.0;
    settings.home.y = 0.0;
    return settings;
}

/* Returns the home position stored in settings as an EmbVector. */
EmbVector embSettings_home(EmbSettings* settings)
{
    return settings->home;
}

/* Sets the home position stored in settings to an EmbPoint point.
 * You will rarely ever need to use this. */
void embSettings_setHome(EmbSettings* settings, EmbVector point)
{
    settings->home = point;
}

/* TODO:
 * 1. Add tests for functions to embroider_main.c.
 * 2. Incorporate the last 4 functions #if 0'ed out.
 * 3. Add flags to trigger the use of these algorithms to embroider.
 */

void embArray_resample(EmbArray *a, EmbArray *usePt)
{
    EmbArray *b;
    int i;
    b = embArray_create(a->type);
    /* could support other types */
    for (i=0; i<a->count; i++) {
        if (usePt->flag[i]) {
            embArray_addVector(b, a->vector[i]);
        }
    }
    embArray_free(a);
    a = b;
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
    VectorStitch vs;
    EmbArray *sa2 = new StitchBlock();
    oldColor = pattern.StitchList[0].ColorIndex;
    color = pattern.ColorList[oldColor];
    sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
    for (i=0; i<pattern->stitches->count; i++) {
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
    for (j=0; j<blocks->count; j++) {
        block = blocks[j];
        EmbArray *stitches = new List<VectorStitch>();
        block.Stitches[0].Type = VectorStitchType.Contour;
        block.Stitches[block.Stitches->count - 1].Type = VectorStitchType.Contour;

        for (i = 0; i < block.Stitches->count - 2; i++) { /* step 0 */
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
        for (i = 1; i < pattern->stitches->count - 3; i++) {
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
#if 0
    int currColorIndex = 0, oddEven, i;
    float dx, dy, dy2, dy3;
    EmbArray *pOdd = new List<Point>();
    EmbArray *pEven = new List<Point>();
    foreach (StitchBlock sa in stitchData) {
        if (sa.Stitches->count > 0) {
            sa.Stitches[0].Type = VectorStitchType.Contour;
            sa.Stitches[sa.Stitches->count - 1].Type = VectorStitchType.Contour;
            /* step 0 */
            for (i = 0; i < sa.Stitches->count - 2; i++) {
                dx = (GetRelativeX(sa.Stitches[i].Xy, sa.Stitches[i + 1].Xy, sa.Stitches[i + 2].Xy));
                sa.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
                sa.Stitches[i].Angle = GetAngle(sa.Stitches[i], sa.Stitches[i + 1]);
            }
            /* step 1 */
            for (i = 1; i < sa.Stitches->count - 3; i++) {
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
    int colorIndex = outPattern.ColorList->count - 1;

    foreach (StitchObject stitchObject in objectsFound) {
        if (stitchObject.SideOne->count > 1 && stitchObject.SideTwo->count > 1) {
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
            if (stitchObject.SideOne->count > 0) {
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
#if 0
    int color;
    var v = new Vertices();
    v.AddRange(pattern.StitchList.Select(point => new Vector2(point.X, point.Y)));
    output = SimplifyTools.DouglasPeuckerSimplify(v, 10);
    patternOut = embPattern_create();
    for (color=0; color<pattern->threads->count; color++) {
        
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
    if (vertices->count < 3) {
        return 0;
    }

    usePt = embArray_create(EMB_FLAG);

    for (i = 0; i < vertices->count; i++) {
        prevId = (i-1+vertices->count) % vertices->count;
        nextId = (i+1) % vertices->count;

        prev = vertices->vector[prevId];
        current = vertices->vector[i];
        next = vertices->vector[nextId];

        /* If they collinear, continue */
        if (embVector_collinear(prev, current, next, collinearityTolerance)) {
            embArray_addFlag(usePt, 0);
        }
        else {
            embArray_addFlag(usePt, 1);
        }
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
    for (i = 0; i < vertices->count; i++) {
        embArray_addFlag(_usePt, 1);
    }
    embPolygon_simplifySection(vertices, _usePt, 0, vertices->count - 1, distanceTolerance);
    embArray_resample(vertices, _usePt);
    embArray_free(_usePt);
    return 1;
}

void embPolygon_simplifySection(EmbArray *vertices, EmbArray *_usePt, int i, int j, float distanceTolerance)
{
    int k, maxIndex;
    EmbVector a, b;
    float maxDistance, distance;
    if ((i + 1) == j)
        return;

    a = vertices->vector[i];
    b = vertices->vector[j];
    maxDistance = -1.0;
    maxIndex = i;
    for (k = i + 1; k < j; k++) {
        distance = embVector_distancePointLine(vertices->vector[k], a, b);

        if (distance > maxDistance) {
            maxDistance = distance;
            maxIndex = k;
        }
    }
    if (maxDistance <= distanceTolerance) {
        for (k = i + 1; k < j; k++) {
            _usePt->flag[k] = 0;
        }
    }
    else {
        embPolygon_simplifySection(vertices, _usePt, i, maxIndex, distanceTolerance);
        embPolygon_simplifySection(vertices, _usePt, maxIndex, j, distanceTolerance);
    }
}

/**
 * Find the distance from (\a p) to the line from (\a a) to (\a b) by
 * finding the length of the normal from ab (extended to an infinte line)
 * to p.
 */
float embVector_distancePointLine(EmbVector p, EmbVector a, EmbVector b)
{
    float r, curve2, s, tolerence;
    EmbVector pa, ba;

    tolerence = 0.00001;
    embVector_subtract(b, a, &ba);
    /* if start == end, then use point-to-point distance */
    if (fabs(ba.x) < tolerence && fabs(ba.y) < tolerence) {
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
    if (vertices->count <= 3) {
        return 0;
    }

    if (areaTolerance < 0) {
        embLog("areaTolerence must be greater than or equal to zero.");
        return 0;
    }

    result = embArray_create(EMB_VECTOR);
    v1 = vertices->vector[vertices->count - 2];
    v2 = vertices->vector[vertices->count - 1];
    areaTolerance *= 2;
    for (index = 0; index < vertices->count; ++index, v2 = v3) {
        if (index == vertices->count - 1) {
            if (result->count == 0) {
                embLog("The areaTolerance is too high.");
                return 0;
            }
            v3 = result->vector[0];
        }
        else {
            v3 = vertices->vector[index];
        }
        old1 = embVector_cross(v1, v2);
        old2 = embVector_cross(v2, v3);
        new1 = embVector_cross(v1, v3);
        if (fabs(new1 - (old1 + old2)) > areaTolerance) {
            embArray_addVector(result, v2);
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
    EmbVector d0, d1;
    float norm0, norm1, cross, dot;
    EmbArray *usePoints;
    if (vertices->count <= 3) {
        return; /* Can't do anything useful here to a triangle */
    }

    usePoints = embArray_create(EMB_FLAG);
    newNVertices = vertices->count;

    /* Gather points to process */
    for (i = 0; i < vertices->count; ++i) {
        lower = (i+vertices->count-1) % vertices->count;
        upper = (i+1)% vertices->count;

        embVector_subtract(vertices->vector[i], vertices->vector[lower], &d0);
        embVector_subtract(vertices->vector[upper], vertices->vector[i], &d1);
        norm0 = embVector_getLength(d0);
        norm1 = embVector_getLength(d1);

        if (!(norm0 > 0.0f && norm1 > 0.0f) && newNVertices > 3) {
            /* Merge identical points */
            embArray_addFlag(usePoints, 0);
            --newNVertices;
            continue;
        }

        embVector_multiply(d0, 1.0/norm0, &d0);
        embVector_multiply(d1, 1.0/norm1, &d1);
        cross = embVector_cross(d0, d1);
        dot = embVector_dot(d0, d1);

        if (fabs(cross) < tolerance && dot > 0 && newNVertices > 3) {
            embArray_addFlag(usePoints, 0);
            --newNVertices;
        }
        else {
            embArray_addFlag(usePoints, 1);
        }
    }

    if (newNVertices == vertices->count || newNVertices == 0) {
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
    /* We can't simplify polygons under 3 vertices */
    if (vertices->count < 3) return 0;

    usePoints = embArray_create(EMB_FLAG);

    for (i = 0; i < vertices->count; i++) {
        nextId = (i + 1) % vertices->count;

        vdist = embVector_distance(vertices->vector[i], vertices->vector[nextId]);

        /* If they are closer than the distance, do not use the i-th point */
        if (vdist < distance) {
            embArray_addFlag(usePoints, 0);
        }
        else {
            embArray_addFlag(usePoints, 1);
        }
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
    if (vertices->count < 3)
        return 0;

    /* Vertex is not present */
    if (nth >= vertices->count)
        return 0;

    /* This isn't an array of vectors. */
    if (vertices->type != EMB_VECTOR)
        return 0;

    /* Shift everything left one place then reduce the count. */
    for (i = nth; i < vertices->count - 1; i++) {
        vertices->vector[i] = vertices->vector[i + 1];
    }
    vertices->count--;

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
    int intermediateOutlineCount = 2 * lines->count - 2;
    outline.side1 = embArray_create(EMB_VECTOR);
    if (!outline.side1) {
        embLog("ERROR: embSatinOutline_generateSatinOutline() embArray_create()\n");
        return;
    }
    outline.side2 = embArray_create(EMB_VECTOR);
    if (!outline.side2) {
        embLog("ERROR: embSatinOutline_generateSatinOutline() embArray_create()\n");
        return;
    }

    for (i = 1; i < lines->count; i++) {
        j = (i - 1) * 2;
        line.start = lines->vector[j - 1];
        line.end = lines->vector[j];

        embLine_normalVector(line, &v1, 1);

        embVector_multiply(v1, halfThickness, &temp);
        embVector_add(temp, lines->vector[j - 1], &temp);
        embArray_addVector(outline.side1, temp);
        embVector_add(temp, lines->vector[j], &temp);
        embArray_addVector(outline.side1, temp);

        embVector_multiply(v1, -halfThickness, &temp);
        embVector_add(temp, lines->vector[j - 1], &temp);
        embArray_addVector(outline.side2, temp);
        embVector_add(temp, lines->vector[j], &temp);
        embArray_addVector(outline.side2, temp);
    }

    if (!result) {
        embLog("ERROR: embSatinOutline_generateSatinOutline(), result==0\n");
        return;
    }
    result->side1 = embArray_create(EMB_VECTOR);
    if (!result->side1) {
        embLog("ERROR: embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side1\n");
        return;
    }
    result->side2 = embArray_create(EMB_VECTOR);
    if (!result->side2) {
        embLog("ERROR: embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side2\n");
        return;
    }

    embArray_addVector(result->side1, outline.side1->vector[0]);
    embArray_addVector(result->side2, outline.side2->vector[0]);

    for (i = 3; i < intermediateOutlineCount; i += 2) {
        line1.start = outline.side1->vector[i - 3];
        line1.end = outline.side1->vector[i - 2];
        line2.start = outline.side1->vector[i - 1];
        line2.end = outline.side1->vector[i];
        embLine_intersectionPoint(line1, line2, &temp);
        embArray_addVector(result->side1, temp);

        line1.start = outline.side2->vector[i - 3];
        line1.end = outline.side2->vector[i - 2];
        line2.start = outline.side2->vector[i - 1];
        line2.end = outline.side2->vector[i];
        embLine_intersectionPoint(line1, line2, &temp);
        embArray_addVector(result->side2, temp);
    }

    embArray_addVector(result->side1, outline.side1->vector[2 * lines->count - 3]);
    embArray_addVector(result->side2, outline.side2->vector[2 * lines->count - 3]);
    result->length = lines->count;
}

EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, float density)
{
    int i, j, numberOfSteps;
    EmbVector currTop, currBottom, topDiff, bottomDiff, midDiff;
    EmbVector midLeft, midRight, topStep, bottomStep;
    EmbArray* stitches = 0;
    float midLength;

    if (!result) {
        embLog("ERROR: embSatinOutline_renderStitches(), result==0\n");
        return 0;
    }

    if (result->length > 0) {
        for (j = 0; j < result->length - 1; j++) {
            embVector_subtract(result->side1->vector[j + 1], result->side1->vector[j], &topDiff);
            embVector_subtract(result->side2->vector[j + 1], result->side2->vector[j], &bottomDiff);

            embVector_average(result->side1->vector[j], result->side2->vector[j], &midLeft);
            embVector_average(result->side1->vector[j + 1], result->side2->vector[j + 1], &midRight);

            embVector_subtract(midLeft, midRight, &midDiff);
            midLength = embVector_getLength(midDiff);

            numberOfSteps = (int)(midLength * density / 200);
            embVector_multiply(topDiff, 1.0 / numberOfSteps, &topStep);
            embVector_multiply(bottomDiff, 1.0 / numberOfSteps, &bottomStep);
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

static bcf_file_difat* bcf_difat_create(EmbFile* file, unsigned int fatSectors, const unsigned int sectorSize);
static unsigned int readFullSector(EmbFile* file, bcf_file_difat* bcfFile, unsigned int* numberOfDifatEntriesStillToRead);
static unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat);
static void bcf_file_difat_free(bcf_file_difat* difat);

static bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize);
static void loadFatFromSector(bcf_file_fat* fat, EmbFile* file);
static void bcf_file_fat_free(bcf_file_fat* fat);

static bcf_directory_entry* CompoundFileDirectoryEntry(EmbFile* file);
static bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries);
static void readNextSector(EmbFile* file, bcf_directory* dir);
static void bcf_directory_free(bcf_directory* dir);

static bcf_file_header bcfFileHeader_read(EmbFile* file);
static int bcfFileHeader_isValid(bcf_file_header header);

int numberOfFormats = 61;

/*! Constant representing the number of Double Indirect FAT entries in a single header */
static const unsigned int NumberOfDifatEntriesInHeader = 109;
static const unsigned int sizeOfFatEntry = sizeof(unsigned int);
static const unsigned int sizeOfDifatEntry = 4;
static const unsigned int sizeOfChainingEntryAtEndOfDifatSector = 4;
static const unsigned int sizeOfDirectoryEntry = 128;
/* static const int supportedMinorVersion = 0x003E;
static const int littleEndianByteOrderMark = 0xFFFE; */

static char *embpattern_write_error_no_stitches = "ERROR: embPattern_write(), pattern contains no stitches\n";
static char *embpattern_write_error_open_file = "ERROR: embPattern_write(), failed to open file\n";
static char *error_format_not_supported = "ERROR: This format is not implemented.";

int embPattern_write(EmbPattern* pattern, const char* fileName, int format)
{
    EmbFile *file;
    int r;

    if (!fileName) {
        embLog("ERROR: ");
        embLog(fileName);
        embLog("(), fileName==0\n");
        return 0;
    }

    if (!pattern->stitchList) {
        embLog(embpattern_write_error_no_stitches);
        return 0;
    }

    if (!pattern->stitchList->count) {
        embLog(embpattern_write_error_no_stitches);
        return 0;
    }

    /* Check for an END stitch and add one if it is not present */
    if (pattern->stitchList->stitch[pattern->stitchList->count - 1].flags != END) {
        embPattern_addStitchRel(pattern, 0, 0, END, 1);
    }

    file = embFile_open(fileName, "wb", 0);
    if (!file) {
        embLog(embpattern_write_error_open_file);
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
        embLog(error_format_not_supported);
        break;
    case EMB_FORMAT_BMC:
        embLog(error_format_not_supported);
        break;
    case EMB_FORMAT_BRO:
        r = writeBro(pattern, file, fileName);
        break;
    case EMB_FORMAT_CND:
        embLog(error_format_not_supported);
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
        embLog(error_format_not_supported);
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
        embLog(error_format_not_supported);
        break;
    case EMB_FORMAT_FXY:
        r = writeFxy(pattern, file, fileName);
        break;
    case EMB_FORMAT_GC:
        /* Smoothie G-Code */
        embLog(error_format_not_supported);
        break;
    case EMB_FORMAT_GNC:
        embLog(error_format_not_supported);
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
        embLog(error_format_not_supported);
        break;
    case EMB_FORMAT_PEM:
        embLog(error_format_not_supported);
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
        embLog("Emb format not recognised.");
        break;
    }

    if (!r) {
        return r;
    }

    embFile_close(file);
    return 0;
}

int embPattern_read(EmbPattern* pattern, const char* fileName, int format)
{
    EmbFile *file;
    int r;

    if (!pattern) {
        embLog("ERROR: embPattern_read(), pattern==0\n");
        return 0;
    }
    if (!fileName) {
        embLog("ERROR: embPattern_read(), fileName==0\n");
        return 0;
    }

    file = embFile_open(fileName, "rb", 0);
    if (!file) {
        embLog("ERROR: embPattern_read(), failed to open file\n");
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
        embLog(error_format_not_supported);
        break;
    case EMB_FORMAT_BMC:
        embLog(error_format_not_supported);
        break;
    case EMB_FORMAT_BRO:
        r = readBro(pattern, file, fileName);
        break;
    case EMB_FORMAT_CND:
        embLog(error_format_not_supported);
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
        embLog(error_format_not_supported);
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
        embLog(error_format_not_supported);
        break;
    case EMB_FORMAT_FXY:
        r = readFxy(pattern, file, fileName);
        break;
    case EMB_FORMAT_GC:
        /* Smoothie G-Code */
        embLog(error_format_not_supported);
        break;
    case EMB_FORMAT_GNC:
        embLog(error_format_not_supported);
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
        embLog(error_format_not_supported);
        break;
    case EMB_FORMAT_PEM:
        embLog(error_format_not_supported);
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
        embLog("Emb format not recognised.");
        break;
    }

    if (!r) {
        return r;
    }

    embFile_close(file);

    /* Check for an END stitch and add one if it is not present */
    if (pattern->stitchList->stitch[pattern->stitchList->count - 1].flags != END) {
        embPattern_addStitchRel(pattern, 0, 0, END, 1);
    }

    return 1;
}

/**
 * TODO: documentation.
 */
EmbFile* embFile_open(const char* fileName, const char* mode, int optional)
{
#ifdef ARDUINO
    return inoFile_open(fileName, mode);
#else
    EmbFile* eFile = 0;
    FILE* oFile = fopen(fileName, mode);
    if (!oFile) {
        if (!optional) {
            embLog("ERROR: Cannot open the fileName in the given mode.");
            embLog(fileName);
            embLog(mode);
        }
        return 0;
    }

    eFile = (EmbFile*)malloc(sizeof(EmbFile));
    if (!eFile) {
        if (!optional) {
            embLog("ERROR: Cannot allocate memory for EmbFile with arguments:");
            embLog(fileName);
            embLog(mode);
        }
        fclose(oFile);
        return 0;
    }

    eFile->file = oFile;
    return eFile;
#endif
}

/**
 * TODO: documentation.
 */
int embFile_close(EmbFile* stream)
{
#ifdef ARDUINO
    return inoFile_close(stream);
#else /* ARDUINO */
    int retVal = fclose(stream->file);
    free(stream);
    return retVal;
#endif /* ARDUINO */
}

/**
 * TODO: documentation.
 * ISSUE: the last line may get cut off in certain cases.
 * ISSUE: how are blank lines dealt with?
 */
static int embFile_readline(EmbFile* stream, char* line, int maxLength)
{
    int i, pass;
    char c;
    pass = 1;
    for (i = 0; i < maxLength - 1; i++) {
        if (!embFile_read(&c, 1, 1, stream)) {
            pass = 0;
            break;
        }
        if (c == '\r') {
            if (!embFile_read(&c, 1, 1, stream)) {
                pass = 0;
                break;
            }
            if (c != '\n') {
                embFile_seek(stream, -1L, SEEK_CUR);
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
 * TODO: documentation.
 */
void embFile_pad(EmbFile* stream, char c, int n)
{
    int i;
    for (i=0; i<n; i++) {
        embFile_write(&c, 1, 1, stream);
    }
}

/**
 * TODO: documentation.
 */
EmbFile* embFile_tmpfile(void)
{
#ifdef ARDUINO
    return inoFile_tmpfile();
#else
    EmbFile* eFile = 0;
    FILE* tFile = tmpfile();
    if (!tFile)
        return 0;

    eFile = (EmbFile*)malloc(sizeof(EmbFile));
    if (!eFile) {
        fclose(tFile);
        return 0;
    }

    eFile->file = tFile;
    return eFile;
#endif
}

/**
 * TODO: documentation.
 */
void embFile_print(EmbFile* stream, char* str)
{
    embFile_write(str, 1, string_length(str), stream);
}

/**
 * TODO: documentation.
 */
static unsigned int sectorSize(bcf_file* bcfFile)
{
    /* version 3 uses 512 byte */
    if (bcfFile->header.majorVersion == 3) {
        return 512;
    }
    return 4096;
}

/**
 * TODO: documentation.
 */
static int haveExtraDIFATSectors(bcf_file* file)
{
    return (int)(numberOfEntriesInDifatSector(file->difat) > 0);
}

/**
 * TODO: documentation.
 */
static int seekToOffset(EmbFile* file, const unsigned int offset)
{
    return embFile_seek(file, offset, SEEK_SET);
}

/**
 * TODO: documentation.
 */
static int seekToSector(bcf_file* bcfFile, EmbFile* file, const unsigned int sector)
{
    unsigned int offset = sector * sectorSize(bcfFile) + sectorSize(bcfFile);
    return seekToOffset(file, offset);
}

/**
 * TODO: documentation.
 */
static void parseDIFATSectors(EmbFile* file, bcf_file* bcfFile)
{
    unsigned int numberOfDifatEntriesStillToRead = bcfFile->header.numberOfFATSectors - NumberOfDifatEntriesInHeader;
    unsigned int difatSectorNumber = bcfFile->header.firstDifatSectorLocation;
    while ((difatSectorNumber != CompoundFileSector_EndOfChain) && (numberOfDifatEntriesStillToRead > 0)) {
        seekToSector(bcfFile, file, difatSectorNumber);
        difatSectorNumber = readFullSector(file, bcfFile->difat, &numberOfDifatEntriesStillToRead);
    }
}

/**
 * TODO: documentation.
 */
int bcfFile_read(EmbFile* file, bcf_file* bcfFile)
{
    unsigned int i, numberOfDirectoryEntriesPerSector, directorySectorToReadFrom;

    bcfFile->header = bcfFileHeader_read(file);
    if (!bcfFileHeader_isValid(bcfFile->header)) {
        embLog("Failed to parse header\n");
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

/**
 * TODO: documentation.
 */
EmbFile* GetFile(bcf_file* bcfFile, EmbFile* file, char* fileToFind)
{
    int filesize, sectorSize, currentSector, sizeToWrite, currentSize, totalSectors, i;
    char* input = 0;
    EmbFile* fileOut = embFile_tmpfile();
    bcf_directory_entry* pointer = bcfFile->directory->dirEntries;
    while (pointer) {
        if (string_equal(fileToFind, pointer->directoryEntryName))
            break;
        pointer = pointer->next;
    }
    filesize = pointer->streamSize;
    sectorSize = bcfFile->difat->sectorSize;
    input = (char*)malloc(sectorSize);
    if (!input) {
        embLog("ERROR: GetFile(), cannot allocate memory for input\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    currentSize = 0;
    currentSector = pointer->startingSectorLocation;
    totalSectors = (int)emb_ceil((float)filesize / sectorSize);
    for (i = 0; i < totalSectors; i++) {
        seekToSector(bcfFile, file, currentSector);
        sizeToWrite = filesize - currentSize;
        if (sectorSize < sizeToWrite) {
            sizeToWrite = sectorSize;
        }
        embFile_read(input, 1, sizeToWrite, file);
        embFile_write(input, 1, sizeToWrite, fileOut);
        currentSize += sizeToWrite;
        currentSector = bcfFile->fat->fatEntries[currentSector];
    }
    free(input);
    input = 0;
    return fileOut;
}

/**
 * TODO: documentation.
 */
void bcf_file_free(bcf_file* bcfFile)
{
    bcf_file_difat_free(bcfFile->difat);
    bcfFile->difat = 0;
    bcf_file_fat_free(bcfFile->fat);
    bcfFile->fat = 0;
    bcf_directory_free(bcfFile->directory);
    bcfFile->directory = 0;
    free(bcfFile);
    bcfFile = 0;
}

/**
 * TODO: documentation.
 */
bcf_file_difat* bcf_difat_create(EmbFile* file, unsigned int fatSectors, const unsigned int sectorSize)
{
    unsigned int i;
    bcf_file_difat* difat = 0;
    unsigned int sectorRef;

    difat = (bcf_file_difat*)malloc(sizeof(bcf_file_difat));
    if (!difat) {
        embLog("ERROR: bcf_difat_create(), cannot allocate memory for difat\n");
    } /* TODO: avoid crashing. null pointer will be accessed */

    difat->sectorSize = sectorSize;
    if (fatSectors > NumberOfDifatEntriesInHeader) {
        fatSectors = NumberOfDifatEntriesInHeader;
    }

    for (i = 0; i < fatSectors; ++i) {
        sectorRef = binaryReadUInt32(file);
        difat->fatSectorEntries[i] = sectorRef;
    }
    difat->fatSectorCount = fatSectors;
    for (i = fatSectors; i < NumberOfDifatEntriesInHeader; ++i) {
        sectorRef = binaryReadUInt32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            embLog("ERROR: bcf_difat_create(), Unexpected sector value\n");
            /* TODO " %x at DIFAT[%d]\n", sectorRef, i); */
        }
    }
    return difat;
}

/**
 * TODO: documentation.
 */
unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat)
{
    return (fat->sectorSize - sizeOfChainingEntryAtEndOfDifatSector) / sizeOfDifatEntry;
}

/**
 * TODO: documentation.
 */
unsigned int readFullSector(EmbFile* file, bcf_file_difat* bcfFile, unsigned int* numberOfDifatEntriesStillToRead)
{
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
        sectorRef = binaryReadUInt32(file);
        bcfFile->fatSectorEntries[bcfFile->fatSectorCount] = sectorRef;
        bcfFile->fatSectorCount++;
    }
    for (i = entriesToReadInThisSector; i < numberOfEntriesInDifatSector(bcfFile); ++i) {
        sectorRef = binaryReadUInt32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            embLog("ERROR: readFullSector(), Unexpected sector value");
            /* TODO: end of message: %x at DIFAT[%d]]\n", sectorRef, i); */
        }
    }
    nextDifatSectorInChain = binaryReadUInt32(file);
    return nextDifatSectorInChain;
}

/**
 * TODO: documentation.
 */
void bcf_file_difat_free(bcf_file_difat* difat)
{
    free(difat);
}

/**
 * TODO: documentation.
 */
static void parseDirectoryEntryName(EmbFile* file, bcf_directory_entry* dir)
{
    int i;
    unsigned short unicodechar;
    for (i = 0; i < 32; ++i) {
        unicodechar = binaryReadUInt16(file);
        if (unicodechar != 0x0000) {
            dir->directoryEntryName[i] = (char)unicodechar;
        }
    }
}

/**
 * TODO: documentation.
 */
bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries)
{
    bcf_directory* dir = (bcf_directory*)malloc(sizeof(bcf_directory));
    if (!dir) {
        embLog("ERROR: CompoundFileDirectory(), cannot allocate memory for dir\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    dir->maxNumberOfDirectoryEntries = maxNumberOfDirectoryEntries;
    dir->dirEntries = 0;
    return dir;
}

/**
 * TODO: documentation.
 */
EmbTime parseTime(EmbFile* file)
{
    EmbTime returnVal;
#if 0
    unsigned int ft_low, ft_high;
    /*embTime_time(&returnVal); TODO: use embTime_time() rather than time(). */
    ft_low = binaryReadInt32(file);
    ft_high = binaryReadInt32(file);
    /* TODO: translate to actual date time */
#endif
    returnVal.year = 1000; /* for testing */
    return returnVal;
}

/**
 * TODO: documentation.
 */
bcf_directory_entry* CompoundFileDirectoryEntry(EmbFile* file)
{
    bcf_directory_entry* dir = (bcf_directory_entry*)malloc(sizeof(bcf_directory_entry));
    if (!dir) {
        embLog("ERROR: CompoundFileDirectoryEntry(), cannot allocate memory for dir\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    memory_set(dir->directoryEntryName, 0, 32);
    parseDirectoryEntryName(file, dir);
    dir->next = 0;
    dir->directoryEntryNameLength = binaryReadUInt16(file);
    dir->objectType = (unsigned char)binaryReadByte(file);
    if ((dir->objectType != ObjectTypeStorage) && (dir->objectType != ObjectTypeStream) && (dir->objectType != ObjectTypeRootEntry)) {
        embLog("ERROR: CompoundFileDirectoryEntry(), unexpected object type:\n");
        /* TODO: "%d\n", dir->objectType); */
        return 0;
    }
    dir->colorFlag = (unsigned char)binaryReadByte(file);
    dir->leftSiblingId = binaryReadUInt32(file);
    dir->rightSiblingId = binaryReadUInt32(file);
    dir->childId = binaryReadUInt32(file);
    /* guidSize = 16 */
    embFile_read(dir->CLSID, 1, 16, file);
    dir->stateBits = binaryReadUInt32(file);
    dir->creationTime = parseTime(file);
    dir->modifiedTime = parseTime(file);
    dir->startingSectorLocation = binaryReadUInt32(file);
    dir->streamSize = binaryReadUInt32(file); /* This should really be __int64 or long long, but for our uses we should never run into an issue */
    dir->streamSizeHigh = binaryReadUInt32(file); /* top portion of int64 */
    return dir;
}

/**
 * TODO: documentation.
 */
void readNextSector(EmbFile* file, bcf_directory* dir)
{
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

/**
 * TODO: documentation.
 */
void bcf_directory_free(bcf_directory* dir)
{
    bcf_directory_entry* pointer = dir->dirEntries;
    bcf_directory_entry* entryToFree = 0;
    while (pointer) {
        entryToFree = pointer;
        pointer = pointer->next;
        free(entryToFree);
    }
    if (dir) {
        free(dir);
    }
}

/**
 * TODO: documentation.
 */
bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize)
{
    bcf_file_fat* fat = (bcf_file_fat*)malloc(sizeof(bcf_file_fat));
    if (!fat) {
        embLog("ERROR: bcfFileFat_create(), cannot allocate memory for fat\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    fat->numberOfEntriesInFatSector = sectorSize / sizeOfFatEntry;
    fat->fatEntryCount = 0;
    return fat;
}

/**
 * TODO: documentation.
 */
void loadFatFromSector(bcf_file_fat* fat, EmbFile* file)
{
    unsigned int i;
    unsigned int currentNumberOfFatEntries = fat->fatEntryCount;
    unsigned int newSize = currentNumberOfFatEntries + fat->numberOfEntriesInFatSector;
    for (i = currentNumberOfFatEntries; i < newSize; ++i) {
        unsigned int fatEntry = binaryReadUInt32(file);
        fat->fatEntries[i] = fatEntry;
    }
    fat->fatEntryCount = newSize;
}

/**
 * TODO: documentation.
 */
void bcf_file_fat_free(bcf_file_fat* fat)
{
    free(fat);
    fat = 0;
}

/**
 * TODO: documentation.
 */
bcf_file_header bcfFileHeader_read(EmbFile* file)
{
    bcf_file_header header;
    embFile_read(header.signature, 1, 8, file);
    embFile_read(header.CLSID, 1, 16, file);
    header.minorVersion = binaryReadUInt16(file);
    header.majorVersion = binaryReadUInt16(file);
    header.byteOrder = binaryReadUInt16(file);
    header.sectorShift = binaryReadUInt16(file);
    header.miniSectorShift = binaryReadUInt16(file);
    header.reserved1 = binaryReadUInt16(file);
    header.reserved2 = (unsigned int)binaryReadUInt32(file);
    header.numberOfDirectorySectors = (unsigned int)binaryReadUInt32(file);
    header.numberOfFATSectors = (unsigned int)binaryReadUInt32(file);
    header.firstDirectorySectorLocation = (unsigned int)binaryReadUInt32(file);
    header.transactionSignatureNumber = (unsigned int)binaryReadUInt32(file);
    header.miniStreamCutoffSize = (unsigned int)binaryReadUInt32(file);
    header.firstMiniFATSectorLocation = (unsigned int)binaryReadUInt32(file);
    header.numberOfMiniFatSectors = (unsigned int)binaryReadUInt32(file);
    header.firstDifatSectorLocation = (unsigned int)binaryReadUInt32(file);
    header.numberOfDifatSectors = (unsigned int)binaryReadUInt32(file);
    return header;
}

/**
 * TODO: documentation.
 */
int bcfFileHeader_isValid(bcf_file_header header)
{
    if (!string_equal(header.signature, "\xd0\xcf\x11\xe0\xa1\xb1\x1a\xe1")) {
        embLog("bad header signature\n");
        return 0;
    }
    return 1;
}

/**
 * TODO: documentation.
 */
int embFormat_getExtension(const char* fileName, char* ending)
{
    int i;
    const char* offset;

    if (!fileName) {
        embLog("ERROR: embFormat_getExtension(), fileName==0\n");
        return 0;
    }

    if (string_length(fileName) == 0) {
        return 0;
    }

    offset = strrchr(fileName, '.');
    if (offset == 0) {
        return 0;
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
    embFile_seek(datafile, out+59*format, SEEK_SET);
    embFile_read(embBuffer, 1, 59, datafile);
    
    memory_copy(f.extension, (char *)embBuffer, 6);
    memory_copy(f.description, (char *)(embBuffer+6), 50);
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

    embLog("ERROR: embReaderWriter_getByFileName(), unsupported file type:");
    embLog(ending);
    return -1;
}

static char read100(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static char write100(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish write100 */
}

static char read10o(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[3];

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
            break;
        }
        embPattern_addStitchRel(pattern, st.x, st.y, st.flags, 1);
    }

    return 1;
}

static char write10o(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish write10o */
}

static char readBro(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char x55;
    short unknown[5];
    char name[8];
    int stitchType;

    embPattern_loadExternalColorFile(pattern, fileName);

    x55 = binaryReadByte(file);
    unknown[0] = binaryReadInt16(file); /* TODO: determine what this unknown data is */

    embFile_read(name, 1, 8, file);
    unknown[1] = binaryReadInt16(file); /* TODO: determine what this unknown data is */
    unknown[2] = binaryReadInt16(file); /* TODO: determine what this unknown data is */
    unknown[3] = binaryReadInt16(file); /* TODO: determine what this unknown data is */
    unknown[4] = binaryReadInt16(file);
    
    printf("Determine what these are %d %d %d %d %d\n",
        unknown[0], unknown[1], unknown[2], unknown[3], unknown[4]);

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

    return 1;
}

static char writeBro(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeBro */
}

static char readCol(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int nColors, i;
    int num, blue, green, red;
    EmbThread t;
    char line[30];

    embArray_free(pattern->threads);
    pattern->threads = embArray_create(EMB_THREAD);

    embFile_readline(file, line, 30);
    nColors = atoi(line);
    if (nColors < 1) {
        embLog("ERROR: Number of colors is zero.");
        return 0;
    }
    for (i = 0; i < nColors; i++) {
        embFile_readline(file, line, 30);
        if (string_length(line) < 1) {
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
        string_copy(t.catalogNumber, "NULL");
        string_copy(t.description, "NULL");
        embPattern_addThread(pattern, t);
    }
    return 1;
}

static char writeCol(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;

    sprintf((char*)embBuffer, "%d\r\n", pattern->threads->count);
    embFile_print(file, embBuffer);
    for (i = 0; i < pattern->threads->count; i++) {
        EmbColor c;
        c = pattern->threads->thread[i].color;
        sprintf((char*)embBuffer, "%d,%d,%d,%d\r\n", i, (int)c.r, (int)c.g, (int)c.b);
        embFile_print(file, embBuffer);
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

static char readCsd(EmbPattern* pattern, EmbFile* file, const char* fileName)
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
    /* save embFile function calls by loading in a chunk */
    embFile_read(embBuffer, 1, 16*4, file);
    for (i = 0; i < 16; i++) {
        EmbThread thread;
        thread.color.r = DecodeCsdByte(embFile_tell(file), embBuffer[3*i+0], type);
        thread.color.g = DecodeCsdByte(embFile_tell(file), embBuffer[3*i+1], type);
        thread.color.b = DecodeCsdByte(embFile_tell(file), embBuffer[3*i+2], type);
        string_copy(thread.catalogNumber, "");
        string_copy(thread.description, "");
        embPattern_addThread(pattern, thread);
    }
    unknown1 = DecodeCsdByte(embFile_tell(file), embBuffer[3*16+0], type);
    unknown2 = DecodeCsdByte(embFile_tell(file), embBuffer[3*16+1], type);

    for (i = 0; i < 14; i++) {
        colorOrder[i] = (unsigned char)DecodeCsdByte(embFile_tell(file), embBuffer[3*16+2+i], type);
    }
    for (i = 0; !endOfStream; i++) {
        char negativeX, negativeY;
        embFile_read(embBuffer, 1, 3, file);
        unsigned char b0 = DecodeCsdByte(embFile_tell(file), embBuffer[0], type);
        unsigned char b1 = DecodeCsdByte(embFile_tell(file), embBuffer[1], type);
        unsigned char b2 = DecodeCsdByte(embFile_tell(file), embBuffer[2], type);

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
                embLog("Invalid color change detected\n");
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

    return 1;
}

static char writeCsd(EmbPattern* pattern, EmbFile* file, const char* fileName)
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
        embLog("ERROR: csvStrToStitchFlag(), str==0\n");
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

static char readCsv(EmbPattern* pattern, EmbFile* file, const char* fileName)
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
    float xx = 0.0;
    float yy = 0.0;
    unsigned char r = 0, g = 0, b = 0;
    char* buff = 0;

    buff = (char*)malloc(size);
    if (!buff) {
        print_log_string(read_csv_error_0);
        return 0;
    }

    pos = 0;
    while (embFile_read(&c, 1, 1, file)) {
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
                print_log_string(read_csv_error_1);
                return 0;
            }
            break;
        }
        if (pos >= size - 1) {
            size *= 2;
            buff = (char*)realloc(buff, size);
            if (!buff) {
                print_log_string(read_csv_error_2);
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
                if (string_equal(buff, "#")) {
                    csvMode = CSV_MODE_COMMENT;
                } else if (string_equal(buff, ">")) {
                    csvMode = CSV_MODE_VARIABLE;
                } else if (string_equal(buff, "$")) {
                    csvMode = CSV_MODE_THREAD;
                } else if (string_equal(buff, "*")) {
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
                    /* TODO */
                    string_copy(t.description, "NULL");
                    string_copy(t.catalogNumber, "NULL");
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
    }

    /* if not enough colors defined, fill in random colors */
    while (pattern->threads->count < numColorChanges) {
        embPattern_addThread(pattern, embThread_getRandom());
    }

    free(buff);

    return 1;
}

/* Copy a block of bytes from the datafile to the elected file
 * if length == 0 use null termination to end copy, otherwise
 * copy length bytes.
 */
static void string_to_file(EmbFile *file, int offset, int length)
{
    char ch = 1;
    int i;
    embFile_seek(datafile, dereference_int(offset), SEEK_SET);
    if (length == 0) {
        while (ch) {
            embFile_read(&ch, 1, 1, datafile);
            if (ch) {
                embFile_write(&ch, 1, 1, file);
            }
        }
    }
    else {
        for (i=0; i<length; i++) {
            embFile_read(&ch, 1, 1, datafile);
            embFile_write(&ch, 1, 1, file);
        }
    }
}

/* 
 */
static void print_log_string(int offset)
{
    int i;
    /* acts as an error number */
    printf("%d\n", offset);
    get_str((char*)embBuffer, offset);
    embLog((char*)embBuffer);
}

static char writeCsv(EmbPattern* pattern, EmbFile* file, const char* fileName)
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
        print_log_string(write_csv_error_0);
        return 0;
    }

    /* write header */
    string_to_file(file, csv_header, 0);

    /* write variables */
    embFile_print(file, "\"#\",\"[VAR_NAME]\",\"[VAR_VALUE]\"\n");
    embFile_print(file, "\">\",\"STITCH_COUNT:\",\"");
    writeInt(file, stitchCount, 6);
    embFile_print(file, "\"\n");
    embFile_print(file, "\">\",\"THREAD_COUNT:\",\"");
    writeInt(file, threadCount, 6);
    embFile_print(file, "\"\n");
    writeFloatWrap(file, "\">\",\"EXTENTS_LEFT:\",\"", boundingRect.left, "\"\n");
    writeFloatWrap(file, "\">\",\"EXTENTS_TOP:\",\"", boundingRect.top, "\"\n");
    writeFloatWrap(file, "\">\",\"EXTENTS_RIGHT:\",\"", boundingRect.right, "\"\n");
    writeFloatWrap(file, "\">\",\"EXTENTS_BOTTOM:\",\"", boundingRect.bottom, "\"\n");
    writeFloatWrap(file, "\">\",\"EXTENTS_WIDTH:\",\"", embRect_width(boundingRect), "\"\n");
    writeFloatWrap(file, "\">\",\"EXTENTS_HEIGHT:\",\"", embRect_height(boundingRect), "\"\n");
    embFile_print(file, "\n");

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

static char readDat(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

    return 1;
}

static char writeDat(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeDat */
}

static char readDsb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[4];
    unsigned char header[512];
    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_read(header, 1, 512, file);

    embFile_seek(file, 0x200, SEEK_SET);
    while (embFile_read(b, 1, 3, file) == 3) {
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

static char writeDsb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeDsb */
}

/* .DST (Tajima) embroidery file read/write routines
 * Format comments are thanks to tspilman@dalcoathletic.com who's
 * notes appeared at http://www.wotsit.org under Tajima Format.
 */

static void encode_record(EmbFile* file, int *dx, int flags)
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

    embFile_write(b, 1, 3, file);
}

/*convert 2 characters into 1 int for case statement */
/*#define cci(s) (s[0]*256+s[1]) */
#define cci(c1, c2) (c1 * 256 + c2)

static void set_dst_variable(EmbPattern* pattern, char* var, char* val)
{
    unsigned int i;
    EmbThread t;

    for (i = 0; i <= (unsigned int)string_length(var); i++) {
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
        if (string_length(val) != 6) {
            /*pattern->messages.add("Warning: in DST file read, PD is not 6 characters, but ",(int)string_length(val)); */
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
        string_copy(t.description, "NULL");
        string_copy(t.catalogNumber, "NULL");
        embPattern_addThread(pattern, t);
        break;
    default:
        /* unknown field, just save it. */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    }
}

static char readDst(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char var[3]; /* temporary storage variable name */
    char val[512]; /* temporary storage variable value */
    int valpos;
    unsigned char b[3];
    char header[512 + 1];
    int i = 0;
    int flags; /* for converting stitches from file encoding */

    /* TODO: review commented code below
    pattern->clear();
    pattern->set_variable("file_name",filename);
    */

    embPattern_loadExternalColorFile(pattern, fileName);
    embFile_read(header, 1, 512, file);

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
                    memory_copy(val, &header[valpos], (size_t)(i - valpos));
                    val[i - valpos] = '\0';
                    set_dst_variable(pattern, var, val);
                    break;
                }
            }
        }
    }

    while (embFile_read(b, 1, 3, file) == 3) {
        int x[2];
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

static char writeDst(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbRect boundingRect;
    int pos[2], dx[2], flags, i, ax, ay, mx, my;
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
    if(string_length(la)>16) la[16]='\0';

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
    if (pd == 0 || string_length(pd) != 6) {
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
    pos[0] = 0;
    pos[1] = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx[0] = roundDouble(st.x * 10.0) - pos[0];
        dx[1] = roundDouble(st.y * 10.0) - pos[1];
        pos[0] = roundDouble(st.x * 10.0);
        pos[1] = roundDouble(st.y * 10.0);
        encode_record(file, dx, st.flags);
    }
    /* finish file with a terminator character */
    embFile_write("\xA1\0\0", 1, 3, file);
    return 1;
}

static char readDsz(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    embPattern_loadExternalColorFile(pattern, fileName);

    embFile_seek(file, 0x200, SEEK_SET);
    while (embFile_read(embBuffer, 1, 3, file) == 3) {
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

static char writeDsz(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeDsz */
}

static char readDxf(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

    embFile_seek(file, 0L, SEEK_END);

    fileLength = embFile_tell(file);
    embFile_seek(file, 0L, SEEK_SET);

    while (embFile_tell(file) < fileLength) {
        embFile_readline(file, (char *)embBuffer, 1000);
        /*printf("%s\n", buff);*/
        if ((string_equal((char *)embBuffer, "HEADER")) || (string_equal((char *)embBuffer, "CLASSES")) || (string_equal((char *)embBuffer, "TABLES")) || (string_equal((char *)embBuffer, "BLOCKS")) || (string_equal((char *)embBuffer, "ENTITIES")) || (string_equal((char *)embBuffer, "OBJECTS")) || (string_equal((char *)embBuffer, "THUMBNAILIMAGE"))) {
            section = embBuffer;
            printf("SECTION:%s\n", embBuffer);
        }
        if (string_equal((char *)embBuffer, "ENDSEC")) {
            section = "";
            printf("ENDSEC:%s\n", embBuffer);
        }
        if ((string_equal((char *)embBuffer, "ARC")) || (string_equal((char *)embBuffer, "CIRCLE")) || (string_equal((char *)embBuffer, "ELLIPSE")) || (string_equal((char *)embBuffer, "LINE")) || (string_equal((char *)embBuffer, "LWPOLYLINE")) || (string_equal((char *)embBuffer, "POINT"))) {
            entityType = embBuffer;
        }
        if (string_equal((char *)embBuffer, "EOF")) {
            eof = 1;
        }

        if (string_equal((char *)section, "HEADER")) {
            if (string_equal((char *)embBuffer, "$ACADVER")) {
                embFile_readline(file, (char *)embBuffer, 1000);
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
            if (string_equal((char *)embBuffer, "ENDTAB")) {
                tableName = NULL;
            }

            if (tableName == NULL) {
                if (string_equal((char *)embBuffer, "2")) /* Table Name */
                {
                    embFile_readline(file, tableName, 1000);
                }
            } else if (string_equal(tableName, "LAYER")) {
                /* Common Group Codes for Tables */
                if (string_equal((char *)embBuffer, "5")) /* Handle */
                {
                    embFile_readline(file, (char *)embBuffer, 1000);
                    continue;
                } else if (string_equal((char *)embBuffer, "330")) /* Soft Pointer */
                {
                    embFile_readline(file, (char *)embBuffer, 1000);
                    continue;
                } else if (string_equal((char *)embBuffer, "100")) /* Subclass Marker */
                {
                    embFile_readline(file, (char *)embBuffer, 1000);
                    continue;
                } else if (string_equal((char *)embBuffer, "70")) /* Number of Entries in Table */
                {
                    embFile_readline(file, (char *)embBuffer, 1000);
                    continue;
                }
                /* The meaty stuff */
                else if (string_equal((char *)embBuffer, "2")) /* Layer Name */
                {
                    embFile_readline(file, layerName, 1000);
                } else if (string_equal((char *)embBuffer, "62")) /* Color Number */
                {
                    embFile_readline(file, (char *)embBuffer, 1000);
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
            if (string_equal((char *)embBuffer, "5")) /* Handle */
            {
                embFile_readline(file, (char *)embBuffer, 1000);
                continue;
            } else if (string_equal((char *)embBuffer, "330")) /* Soft Pointer */
            {
                embFile_readline(file, (char *)embBuffer, 1000);
                continue;
            } else if (string_equal((char *)embBuffer, "100")) /* Subclass Marker */
            {
                embFile_readline(file, (char *)embBuffer, 1000);
                continue;
            } else if (string_equal((char *)embBuffer, "8")) /* Layer Name */
            {
                embFile_readline(file, (char *)embBuffer, 1000);
                /* embPattern_changeColor(pattern, colorIndexMap[buff]); TODO: port to C */
                continue;
            }

            if (string_equal(entityType, "LWPOLYLINE")) {
                /* The not so important group codes */
                if (string_equal(embBuffer, "90")) /* Vertices */
                {
                    embFile_readline(file, (char*)embBuffer, 1000);
                    continue;
                } else if (string_equal(embBuffer, "70")) /* Polyline Flag */
                {
                    embFile_readline(file, (char*)embBuffer, 1000);
                    continue;
                }
                /* TODO: Try to use the widths at some point */
                else if (string_equal(embBuffer, "40")) /* Starting Width */
                {
                    embFile_readline(file, (char*)embBuffer, 1000);
                    continue;
                } else if (string_equal(embBuffer, "41")) /* Ending Width */
                {
                    embFile_readline(file, (char*)embBuffer, 1000);
                    continue;
                } else if (string_equal(embBuffer, "43")) /* Constant Width */
                {
                    embFile_readline(file, (char*)embBuffer, 1000);
                    continue;
                }
                /* The meaty stuff */
                else if (string_equal((char*)embBuffer, "42")) /* Bulge */
                {
                    embFile_readline(file, embBuffer, 1000);
                    bulge = atof(embBuffer);
                    bulgeFlag = 1;
                } else if (string_equal((char*)embBuffer, "10")) /* X */
                {
                    embFile_readline(file, (char*)embBuffer, 1000);
                    x = atof(embBuffer);
                } else if (string_equal((char*)embBuffer, "20")) /* Y */
                {
                    embFile_readline(file, (char*)embBuffer, 1000);
                    y = atof(embBuffer);

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
                } else if (string_equal(embBuffer, "0")) {
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
        embLog("ERROR: readDxf(), missing EOF at end of DXF file\n");
    }
    return eof;
}

static char writeDxf(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeDxf */
}

static char readEdr(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int nColors, i;
    EmbThread t;

    embFile_seek(file, 0x00, SEEK_END);
    nColors = embFile_tell(file) / 4;
    embFile_seek(file, 0x00, SEEK_SET);

    embArray_free(pattern->threads);

    for (i = 0; i < nColors; i++) {
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        string_copy(t.catalogNumber, "NULL");
        string_copy(t.description, "NULL");
        binaryReadByte(file);
        embPattern_addThread(pattern, t);
    }
    return 1;
}

static char writeEdr(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static char readEmd(EmbPattern* pattern, EmbFile* file, const char* fileName)
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
                break;
            } else {
                continue;
            }
        }
        dx = emdDecode(b0);
        dy = emdDecode(b1);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

static char writeEmd(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static char readExp(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char dx = 0, dy = 0;
    int flags = 0;

    embPattern_loadExternalColorFile(pattern, fileName);

    while (embFile_read(embBuffer, 1, 2, file) != 2) {
        flags = NORMAL;
        if (embBuffer[0] == 0x80) {
            if (embBuffer[1] & 1) {
                if (embFile_read(embBuffer, 1, 2, file) != 2) break;
                flags = STOP;
            } else if ((embBuffer[1] == 2) || (embBuffer[1] == 4) || embBuffer[1] == 6) {
                flags = TRIM;
                if (embBuffer[1] == 2)
                    flags = NORMAL;
                if (embFile_read(embBuffer, 1, 2, file) != 2) break;
            } else if (embBuffer[1] == 0x80) {
                if (embFile_read(embBuffer, 1, 2, file) != 2) break;
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

static char writeExp(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    float xx, yy;
    int i;

    /* write stitches */
    xx = yy = 0.0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st;
        float dx, dy;
        st = pattern->stitchList->stitch[i];
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        expEncode(embBuffer, (char)roundDouble(dx), (char)roundDouble(dy), st.flags);
        if ((embBuffer[0] == 0x80) &&
            ((embBuffer[1] == 1) || (embBuffer[1] == 2) || (embBuffer[1] == 4) || (embBuffer[1] == 0x10))) {
            embFile_write(embBuffer, 1, 4, file);
        } else {
            embFile_write(embBuffer, 1, 2, file);
        }
    }
    embFile_print(file, "\x1a");
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

static char readExy(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[3];

    embPattern_loadExternalColorFile(pattern, fileName);

    embFile_seek(file, 0x100, SEEK_SET);

    while (embFile_read(b, 1, 3, file) == 3) {
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

static char writeExy(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeExy */
}

static char readFxy(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    embPattern_loadExternalColorFile(pattern, fileName);
    /* TODO: review for combining code.
     * This line appears to be the only difference from the GT format. */
    embFile_seek(file, 0x100, SEEK_SET);

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

static char writeFxy(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeFxy */
}

static char readGt(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    embPattern_loadExternalColorFile(pattern, fileName);
    /* TODO: review for combining code.
     * This line appears to be the only difference from the FXY format. */
    embFile_seek(file, 0x200, SEEK_SET);

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

static char writeGt(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static unsigned char* husDecompressData(unsigned char* input, int compressedInputLength, int decompressedContentLength)
{
    unsigned char* decompressedData = (unsigned char*)malloc(sizeof(unsigned char) * decompressedContentLength);
    if (!decompressedData) {
        embLog("ERROR: husDecompressData(), malloc()\n");
        return 0;
    }
    husExpand((unsigned char*)input, decompressedData, compressedInputLength, 10);
    return decompressedData;
}

static unsigned char* husCompressData(unsigned char* input, int decompressedInputSize, int* compressedSize)
{
    unsigned char* compressedData = (unsigned char*)malloc(sizeof(unsigned char) * decompressedInputSize * 2);
    if (!compressedData) {
        embLog("ERROR: husCompressData(), malloc()\n");
        return 0;
    }
    *compressedSize = husCompress(input, (unsigned long)decompressedInputSize, compressedData, 10, 0);
    return compressedData;
}

static char husDecodeByte(unsigned char b)
{
    return (char)b;
}

static unsigned char husEncodeByte(float f)
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

static char readHus(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int fileLength, i, magicCode, numberOfStitches, nColors;
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
    nColors = binaryReadInt32(file);

    postitiveXHoopSize = binaryReadInt16(file);
    postitiveYHoopSize = binaryReadInt16(file);
    negativeXHoopSize = binaryReadInt16(file);
    negativeYHoopSize = binaryReadInt16(file);

    attributeOffset = binaryReadInt32(file);
    xOffset = binaryReadInt32(file);
    yOffset = binaryReadInt32(file);

    stringVal = (unsigned char*)malloc(sizeof(unsigned char) * 8);
    if (!stringVal) {
        embLog("ERROR: readHus(), malloc()\n");
        return 0;
    }
    binaryReadBytes(file, stringVal, 8); /* TODO: check return value */

    binaryReadInt16(file);
    for (i = 0; i < nColors; i++) {
        EmbThread t;
        int pos = binaryReadInt16(file);
        t = load_thread(hus_thread, pos);
        embPattern_addThread(pattern, t);
    }

    attributeData = (unsigned char*)malloc(sizeof(unsigned char) * (xOffset - attributeOffset + 1));
    if (!attributeData) {
        embLog("ERROR: readHus(), malloc()\n");
        return 0;
    }
    binaryReadBytes(file, attributeData, xOffset - attributeOffset); /* TODO: check return value */
    attributeDataDecompressed = husDecompressData(attributeData, xOffset - attributeOffset, numberOfStitches + 1);

    xData = (unsigned char*)malloc(sizeof(unsigned char) * (yOffset - xOffset + 1));
    if (!xData) {
        embLog("ERROR: readHus(), malloc()\n");
        return 0;
    }
    binaryReadBytes(file, xData, yOffset - xOffset); /* TODO: check return value */
    xDecompressed = husDecompressData(xData, yOffset - xOffset, numberOfStitches);

    yData = (unsigned char*)malloc(sizeof(unsigned char) * (fileLength - yOffset + 1));
    if (!yData) {
        embLog("ERROR: readHus(), malloc()\n");
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

    free(stringVal);
    free(xData);
    free(yData);
    free(attributeData);
    if (xDecompressed) {
        free(xDecompressed);
    }
    if (yDecompressed) {
        free(yDecompressed);
    }
    if (attributeDataDecompressed) {
        free(attributeDataDecompressed);
    }

    return 1;
}

static char writeHus(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor;
    int attributeSize, xCompressedSize, yCompressedSize, i;
    float previousX, previousY;
    unsigned char *xValues = 0, *yValues = 0, *attributeValues = 0;
    unsigned char *attributeCompressed = 0, *xCompressed = 0, *yCompressed = 0;
    EmbStitch st;

    stitchCount = pattern->stitchList->count;
    /* embPattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */
    patternColor = pattern->threads->count;
    minColors = emb_min_int(24, patternColor);
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
        embLog("ERROR: writeHus(), malloc()\n");
        return 0;
    }
    yValues = (unsigned char*)malloc(sizeof(unsigned char) * (stitchCount));
    if (!yValues) {
        embLog("ERROR: writeHus(), malloc()\n");
        return 0;
    }
    attributeValues = (unsigned char*)malloc(sizeof(unsigned char) * (stitchCount));
    if (!attributeValues) {
        embLog("ERROR: writeHus(), malloc()\n");
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
        short color_index = (short)embThread_findNearestColor(pattern->threads->thread[i].color, hus_thread);
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

static char readInb(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static char writeInb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeInb */
}

static char readInf(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int nColors, i;

    embFile_seek(file, 12L, SEEK_SET);
    nColors = binaryReadUInt32BE(file);

    embArray_free(pattern->threads);
    pattern->threads = embArray_create(EMB_THREAD);

    for (i = 0; i < nColors; i++) {
        char colorType[50];
        char colorDescription[50];
        EmbThread t;
        embFile_read(embBuffer, 1, 4, file);
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        string_copy(t.catalogNumber, "NULL");
        string_copy(t.description, "NULL");
        embPattern_addThread(pattern, t);
        binaryReadUInt16(file);
        binaryReadString(file, colorType, 50);
        binaryReadString(file, colorDescription, 50);
    }
    return 1;
}

static char writeInf(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i, bytesRemaining;

    binaryWriteUIntBE(file, 0x01);
    binaryWriteUIntBE(file, 0x08);
    /* write place holder offset */
    binaryWriteUIntBE(file, 0x00);
    binaryWriteUIntBE(file, pattern->threads->count);

    for (i = 0; i < pattern->threads->count; i++) {
        EmbColor c;
        c = pattern->threads->thread[i].color;
        sprintf((char*)embBuffer, "RGB(%d,%d,%d)", (int)c.r, (int)c.g, (int)c.b);
        binaryWriteUShortBE(file, (unsigned short)(14 + string_length(embBuffer))); /* record length */
        binaryWriteUShortBE(file, (unsigned short)i); /* record number */
        binaryWriteByte(file, c.r);
        binaryWriteByte(file, c.g);
        binaryWriteByte(file, c.b);
        binaryWriteUShortBE(file, (unsigned short)i); /* needle number */
        binaryWriteBytes(file, "RGB\0", 4);
        embFile_print(file, embBuffer);
        binaryWriteByte(file, 0);
    }
    embFile_seek(file, -8, SEEK_END);
    bytesRemaining = embFile_tell(file);
    embFile_seek(file, 8, SEEK_SET);
    binaryWriteUIntBE(file, bytesRemaining);
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
        embLog("ERROR: jefSetHoopFromId(), pattern==0\n");
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

static char readJef(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int stitchOffset, formatFlags, nColors, numberOfStitchs;
    int hoopSize, i;
    struct hoop_padding bounds, rectFrom110x110, rectFrom50x50, rectFrom200x140, rect_from_custom;
    int stitchCount;
    char date[8], time[8];
    unsigned char b[2];
    char dx = 0, dy = 0;
    int flags = 0;

    stitchOffset = binaryReadInt32(file);
    formatFlags = binaryReadInt32(file); /* TODO: find out what this means */

    binaryReadBytes(file, (unsigned char*)date, 8); /* TODO: check return value */
    binaryReadBytes(file, (unsigned char*)time, 8); /* TODO: check return value */
    nColors = binaryReadInt32(file);
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

    for (i = 0; i < nColors; i++) {
        EmbThread t;
        t = load_thread(jef_thread, binaryReadInt32(file) % 79);
        embPattern_addThread(pattern, t);
    }
    embFile_seek(file, stitchOffset, SEEK_SET);
    stitchCount = 0;
    while (stitchCount < numberOfStitchs + 100) {
        flags = NORMAL;
        if (!embFile_read(b, 1, 2, file)) {
            break;
        }
        if (b[0] == 0x80) {
            if (b[1] & 1) {
                if (!embFile_read(b, 1, 2, file)) {
                    break;
                }
                flags = STOP;
            } else if ((b[1] == 2) || (b[1] == 4) || b[1] == 6) {
                flags = TRIM;
                if (!embFile_read(b, 1, 2, file)) {
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

static char writeJef(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int colorlistSize, minColors, designWidth, designHeight, i;
    EmbRect boundingRect;
    EmbTime time;
    EmbStitch st;
    float dx = 0.0, dy = 0.0, xx = 0.0, yy = 0.0;
    unsigned char b[4];

    embPattern_correctForMaxStitchLength(pattern, 12.7, 12.7);

    colorlistSize = pattern->threads->count;
    minColors = emb_max_float(colorlistSize, 6);
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
    binaryWriteInt(file, pattern->stitchList->count + emb_max_float(0, (6 - colorlistSize) * 2) + 1);

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

    for (i = 0; i < pattern->threads->count; i++) {
        int j = embThread_findNearestColor(pattern->threads->thread[i].color, jef_thread);
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

static char readKsm(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static char writeKsm(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    float xx, yy, dx, dy;
    int i;

    embFile_pad(file, 0, 0x200);

    /* write stitches */
    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st;
        unsigned char b[4];
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

static float maxDecode(unsigned char a1, unsigned char a2, unsigned char a3)
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
        embLog("ERROR: maxEncode(), file==0\n");
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

static char readMax(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[8];
    float dx, dy;
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

static char writeMax(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;

    string_to_file(file, max_header, 0xD5);
    for (i = 0; i < pattern->stitchList->count; i++) {
        float x, y;
        EmbStitch st;
        st = pattern->stitchList->stitch[i];
        x = roundDouble(st.x * 10.0);
        y = roundDouble(st.y * 10.0);
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

static char readMit(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static char writeMit(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbStitch st;
    float xx, yy, dx, dy;
    int i;

    embPattern_correctForMaxStitchLength(pattern, 0x1F, 0x1F);
    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        dx = st.x - xx;
        dy = st.y - yy;
        xx = st.x;
        yy = st.y;
        embBuffer[0] = mitEncodeStitch(dx);
        embBuffer[1] = mitEncodeStitch(dy);
        embFile_write(embBuffer, 1, 2, file);
    }
    return 1;
}

static char decodeNewStitch(unsigned char value)
{
    return (int)value;
}

static char readNew(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static char writeNew(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeNew */
}

static char* ofmReadLibrary(EmbFile* file)
{
    int stringLength = 0;
    char* libraryName = 0;
    /* FF FE FF */
    unsigned char leadIn[3];

    binaryReadBytes(file, leadIn, 3); /* TODO: check return value */
    stringLength = binaryReadByte(file);
    libraryName = (char*)malloc(sizeof(char) * stringLength * 2);
    if (!libraryName) {
        embLog("ERROR: ofmReadLibrary(), unable to allocate memory for libraryName\n");
        return 0;
    }
    binaryReadBytes(file, (unsigned char*)libraryName, stringLength * 2); /* TODO: check return value */
    return libraryName;
}

static int ofmReadClass(EmbFile* file)
{
    int len;
    char* s = 0;

    binaryReadInt16(file);
    len = binaryReadInt16(file);

    s = (char*)malloc(sizeof(char) * len + 1);
    if (!s) {
        embLog("ERROR: ofmReadClass(), malloc()\n");
        return 0;
    }
    binaryReadBytes(file, (unsigned char*)s, len); /* TODO: check return value */
    s[len] = '\0';
    if (string_equal(s, "CExpStitch"))
        return 0x809C;
    if (string_equal(s, "CColorChange"))
        return 0xFFFF;
    return 0;
}

static void ofmReadBlockHeader(EmbFile* file)
{
    int val[10]; /* TODO: determine what these represent */
    unsigned char len;
    unsigned short short1;
    /* TODO: determine what these 3 variables represent */
    short unknown1 = 0;
    short unknown2 = 0;
    int unknown3 = 0, i;

    unknown1 = binaryReadInt16(file);
    unknown2 = (short)binaryReadInt32(file);
    unknown3 = binaryReadInt16(file);

    embFile_read(embBuffer, 1, 3, file);
    /* int v = binaryReadBytes(3); TODO: review */
    len = binaryReadUInt8(file);
    embFile_read(embBuffer, 1, 2*len, file);
    /* TODO: check return value here */
    embFile_read(embBuffer, 1, 42, file);
    /* 0, 0, 0, 0, 1, 1, 1, 0, 64, 64 */
    for (i=0; i<10; i++) {
        val[i] = binaryReadInt32(file);
    }
    short1 = binaryReadInt16(file); /*  0 */
}

static void ofmReadColorChange(EmbFile* file, EmbPattern* pattern)
{
    ofmReadBlockHeader(file);
    embPattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
}

static void ofmReadThreads(EmbFile* file, EmbPattern* p)
{
    int i, nColors, stringLen, numberOfLibraries;
    char* primaryLibraryName = 0;
    char* expandedString = 0;

    /* Magic Code: FF FE FF 00
     * Number of colors: 2 bytes signed short
     */
    embFile_read(embBuffer, 1, 4, file);

    nColors = binaryReadInt16(file);
    embFile_read(embBuffer, 1, 2, file);
    stringLen = binaryReadInt16(file);
    expandedString = (char*)malloc(stringLen);
    if (!expandedString) {
        embLog("ERROR: ofmReadThreads(), malloc()\n");
        return;
    }
    binaryReadBytes(file, (unsigned char*)expandedString, stringLen); /* TODO: check return value */
    for (i = 0; i < nColors; i++) {
        EmbThread thread;
        char colorNumberText[10];
        int threadLibrary = 0, colorNameLength, colorNumber;
        char* colorName = 0;
        unsigned char color[3];
        embFile_read(color, 1, 3, file);
        binaryReadByte(file);
        threadLibrary = binaryReadInt16(file);
        binaryReadInt16(file);
        colorNumber = binaryReadInt32(file);
        binaryReadByte(file);
        binaryReadInt16(file);
        colorNameLength = binaryReadByte(file);
        colorName = (char*)malloc(colorNameLength * 2);
        if (!colorName) {
            embLog("ERROR: ofmReadThreads(), malloc()\n");
            return;
        }
        binaryReadBytes(file, (unsigned char*)colorName, colorNameLength * 2); /* TODO: check return value */
        binaryReadInt16(file);
        /* itoa(colorNumber, colorNumberText, 10); TODO: never use itoa, it's non-standard, use sprintf:
           http://stackoverflow.com/questions/5242524/converting-int-to-string-in-c */
        thread.color = embColor_fromStr(color);
        string_copy(thread.catalogNumber, colorNumberText);
        string_copy(thread.description, colorName);
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

static float ofmDecode(unsigned char b1, unsigned char b2)
{
    float val = (float)(short)(b1 << 8 | b2);
    return val;
}

static void ofmReadExpanded(EmbFile* file, EmbPattern* p)
{
    int i, numberOfStitches = 0;

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

static char readOfm(EmbPattern* pattern, EmbFile* file, const char* fileName)
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
        embLog("ERROR: readOfm(), malloc()\n");
        return 0;
    }
    bcfFile_read(fileCompound, bcfFile);
    file = GetFile(bcfFile, fileCompound, "EdsIV Object");
    bcf_file_free(bcfFile);
    embFile_seek(file, 0x1C6, SEEK_SET);
    ofmReadThreads(file, pattern);
    embFile_seek(file, 0x110, SEEK_CUR);
    binaryReadInt32(file);
    classNameLength = binaryReadInt16(file);
    s = (char*)malloc(sizeof(char) * classNameLength);
    if (!s) {
        embLog("ERROR: readOfm(), malloc()\n");
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

static char writeOfm(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static void pcdEncode(EmbFile* file, int dx, int dy, int flags)
{
    unsigned char flagsToWrite = 0;

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

static char readPcd(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char allZeroColor = 1;
    int i;
    unsigned char b[9];
    float dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount = 0;

    embFile_read(embBuffer, 1, 2, file);
    version = embBuffer[0];
    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * and 3 for PCS with large hoop (115x120) */
    hoopSize = embBuffer[1];
    colorCount = binaryReadInt16(file);

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        embFile_read(embBuffer, 1, 4, file);
        t.color = embColor_fromStr(embBuffer);
        string_copy(t.catalogNumber, "NULL");
        string_copy(t.description, "NULL");
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
        dx = pcdDecode(b[1], b[2], b[3]);
        dy = pcdDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

static char writePcd(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;

    binaryWriteByte(file, (unsigned char)'2');
    binaryWriteByte(file, 3); /* TODO: select hoop size defaulting to Large PCS hoop */
    binaryWriteUShort(file, (unsigned short)pattern->threads->count);

    embPattern_colorBlock16(pattern, file);

    binaryWriteUShort(file, (unsigned short)pattern->stitchList->count);
    /* write stitches */
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st;
        st = pattern->stitchList->stitch[i];
        pcdEncode(file, roundDouble(st.x * 10.0), roundDouble(st.y * 10.0), st.flags);
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

static char readPcm(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i = 0;
    unsigned char b[9];
    float dx = 0, dy = 0;
    int flags = 0, st = 0;

    embFile_seek(file, 4, SEEK_SET);

    for (i = 0; i < 16; i++) {
        EmbThread t;
        int colorNumber;
        embFile_read(embBuffer, 1, 2, file);
        /* zero followed by colorNumber */
        colorNumber = embBuffer[1];
        t = load_thread(pcm_thread, colorNumber);
        embPattern_addThread(pattern, t);
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

static char writePcm(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static void pcqEncode(EmbFile* file, int dx, int dy, int flags)
{
    unsigned char flagsToWrite = 0;

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

static char readPcq(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    float dx = 0, dy = 0;
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
        string_copy(t.catalogNumber, "NULL");
        string_copy(t.description, "NULL");
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

static char writePcq(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;

    embFile_write("2\x03", 1, 2, file);
    /* TODO: select hoop size defaulting to Large PCS hoop */
    binaryWriteUShort(file, (unsigned short)pattern->threads->count);

    embPattern_colorBlock16(pattern, file);

    binaryWriteUShort(file, (unsigned short)pattern->stitchList->count);
    /* write stitches */
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st;
        st = pattern->stitchList->stitch[i];
        pcqEncode(file, roundDouble(st.x * 10.0), roundDouble(st.y * 10.0), st.flags);
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

static void pcsEncode(EmbFile* file, int dx, int dy, int flags)
{
    unsigned char flagsToWrite = 0;

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

static char readPcs(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i, st;
    unsigned char allZeroColor, version, hoopSize;
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

    allZeroColor = 1;
    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        string_copy(t.catalogNumber, "NULL");
        string_copy(t.description, "NULL");
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
        int flags;
        float dx, dy;
        unsigned char b[9];
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

static EmbThread load_thread(int thread_table, int index)
{
    EmbThread t;
    int out;
    out = double_dereference_int(brand_codes, thread_table);
    embFile_seek(datafile, out+35*index, SEEK_SET);
    embFile_read(embBuffer, 1, 35, datafile);
    t.color.r = embBuffer[30];
    t.color.g = embBuffer[31];
    t.color.b = embBuffer[32];
    string_copy(t.catalogNumber, "TODO:HUS_CODE");
    string_copy(t.description, embBuffer);
    return t;    
}

static char writePcs(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;

    /* TODO: select hoop size defaulting to Large PCS hoop */
    embFile_write("2\x03", 1, 2, file);
    binaryWriteUShort(file, (unsigned short)pattern->threads->count);

    embPattern_colorBlock16(pattern, file);

    binaryWriteUShort(file, (unsigned short)pattern->stitchList->count);
    /* write stitches */
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st;
        st = pattern->stitchList->stitch[i];
        pcsEncode(file, roundDouble(st.x * 10.0), roundDouble(st.y * 10.0), st.flags);
    }
    return 1;
}

void readPecStitches(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int stitchNumber = 0;

    while (embFile_read(embBuffer, 1, 2, file) == 2) {
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

static void pecEncodeJump(EmbFile* file, int x, int types)
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

static void pecEncodeStop(EmbFile* file, unsigned char val)
{
    embFile_write("\xFE\xB0", 1, 2, file);
    embFile_write(&val, 1, 1, file);
}

static char readPec(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned int graphicsOffset;
    unsigned char colorChanges;
    int i;

    embFile_seek(file, 0x38, SEEK_SET);
    colorChanges = (unsigned char)binaryReadByte(file);
    for (i = 0; i <= colorChanges; i++) {
        embPattern_addThread(pattern, load_thread(pec_thread, binaryReadByte(file) % 65));
    }

    /* Get Graphics offset */
    embFile_seek(file, 0x20A, SEEK_SET);

    graphicsOffset = (unsigned int)(binaryReadUInt8(file));
    graphicsOffset |= (binaryReadUInt8(file) << 8);
    graphicsOffset |= (binaryReadUInt8(file) << 16);

    /* \x31\xFF\xF0 */
    embFile_read(embBuffer, 1, 3, file);
    /* Get X and Y size in .1 mm
     * 0x210 <- what is this?
     * x size signed short
     * y size signed short */
    embFile_read(embBuffer, 1, 4, file);
 
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
    float thisX = 0.0;
    float thisY = 0.0;
    unsigned char stopCode = 2;
    EmbStitch s;
    int deltaX, deltaY, i;

    for (i = 0; i < p->stitchList->count; i++) {
        s = p->stitchList->stitch[i];

        deltaX = roundDouble(s.x - thisX);
        deltaY = roundDouble(s.y - thisY);
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
    embFile_seek(datafile, out, SEEK_SET);
    embFile_read(image, 1, 48*38, datafile);
}

static void writeImage(EmbFile* file, unsigned char image[][48])
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

void writePecStitches(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbStitch st;
    EmbRect bounds;
    unsigned char image[38][48];
    int i, currentThreadCount, graphicsOffsetLocation, graphicsOffsetValue, height, width, x, y;
    float xFactor, yFactor;
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
    embFile_write("LA:", 1, 3, file);

    while (start < dotPos) {
        binaryWriteByte(file, (unsigned char)*start);
        start++;
    }
    embFile_pad(file, 0x20, 16-(int)(dotPos - start));
    binaryWriteByte(file, 0x0D);
    embFile_pad(file, 0x20, 12);
    embFile_write("\xFF\x00\x06\x26", 1, 4, file);

    embFile_pad(file, 0x20, 12);
    currentThreadCount = pattern->threads->count;
    binaryWriteByte(file, (unsigned char)(currentThreadCount - 1));

    for (i = 0; i < currentThreadCount; i++) {
        binaryWriteByte(file, (unsigned char)embThread_findNearestColor(pattern->threads->thread[i].color, pec_thread));
    }
    embFile_pad(file, 0x20, (int)(0x1CF - currentThreadCount));
    embFile_pad(file, 0, 2);

    graphicsOffsetLocation = embFile_tell(file);
    /* placeholder bytes to be overwritten */
    embFile_pad(file, 0, 3);

    embFile_write("\x31\xFF\xF0", 1, 3, file);

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

    yFactor = 32.0 / height;
    xFactor = 42.0 / width;
    for (i = 0; i < pattern->stitchList->count; i++) {
        int x, y;
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

static char writePec(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    /* TODO: There needs to be a matching flipVertical() call after the write
     * to ensure multiple writes from the same pattern work properly */
    embPattern_flipVertical(pattern);
    embPattern_fixColorCount(pattern);
    embPattern_correctForMaxStitchLength(pattern, 12.7, 204.7);
    embPattern_scale(pattern, 10.0);

    binaryWriteBytes(file, "#PEC0001", 8);

    writePecStitches(pattern, file, fileName);

    return 1;
}

static char readPes(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int pecstart, numColors, x;

    embFile_seek(file, 8, SEEK_SET);
    pecstart = binaryReadInt32(file);

    embFile_seek(file, pecstart + 48, SEEK_SET);
    embFile_read(embBuffer, 1, 1, file);
    numColors = embBuffer[0] + 1;
    embFile_read(embBuffer, 1, numColors, file);
    for (x = 0; x < numColors; x++) {
        embPattern_addThread(pattern, load_thread(pec_thread, embBuffer[x]));
    }

    embFile_seek(file, pecstart + 532, SEEK_SET);
    readPecStitches(pattern, file, fileName);

    embPattern_flipVertical(pattern);

    return 1;
}

static const char pesVersionTable[16][9] = {
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
static void readPESHeader(EmbFile* file, EmbPattern* pattern)
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
    embFile_seek(file, 4, SEEK_CUR);
    readDescriptions();
    skip(pecStart - readPosition);
}

    static void readPESHeaderV5()  {
        int pecStart = binaryReadInt32();
        embFile_seek(file, 4, SEEK_CUR);
        readDescriptions();
        embFile_seek(file, 24, SEEK_CUR);//36 v6
        int fromImageStringLength = binaryReadByte();
        skip(fromImageStringLength);
        embFile_seek(file, 24, SEEK_CUR);
        int nProgrammableFills = binaryReadInt16();
        if (nProgrammableFills != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int nMotifs = binaryReadInt16();
        if (nMotifs != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int featherPatternCount = binaryReadInt16();
        if (featherPatternCount != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int nColors = binaryReadInt16();
        for (int i = 0; i < nColors; i++) {
            readThread();
        }
        embFile_seek(file, pecStart, SEEK_SET);
    }

    static void readPESHeaderV6()  {
        int pecStart = binaryReadInt32();
        embFile_seek(file, 4, SEEK_CUR);
        readDescriptions();
        embFile_seek(file, 36, SEEK_CUR);
        int fromImageStringLength = binaryReadByte();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        embFile_seek(file, 24, SEEK_CUR);
        int nProgrammableFills = binaryReadInt16();
        if (nProgrammableFills != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int nMotifs = binaryReadInt16();
        if (nMotifs != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int featherPatternCount = binaryReadInt16();
        if (featherPatternCount != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int nColors = binaryReadInt16();
        for (int i = 0; i < nColors; i++) {
            readThread();
        }
        embFile_seek(file, pecStart, SEEK_SET);
    }
    
    static void readPESHeaderV7()  {
        int pecStart = binaryReadInt32();
        embFile_seek(file, 4, SEEK_CUR);
        readDescriptions();
        embFile_seek(file, 36, SEEK_CUR);
        int fromImageStringLength = binaryReadByte();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        embFile_seek(file, 24, SEEK_CUR);
        int nProgrammableFills = binaryReadInt16();
        if (nProgrammableFills != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int nMotifs = binaryReadInt16();
        if (nMotifs != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int featherPatternCount = binaryReadInt16();
        if (featherPatternCount != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int nColors = binaryReadInt16();
        for (int i = 0; i < nColors; i++) {
            readThread();
        }
        embFile_seek(file, pecStart, SEEK_SET);
    }
    
    static void readPESHeaderV8()  {
        int pecStart = binaryReadInt32();
        embFile_seek(file, 4, SEEK_CUR);
        readDescriptions();
        embFile_seek(file, 38, SEEK_CUR);
        int fromImageStringLength = binaryReadByte();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(26);
        int nProgrammableFills = binaryReadInt16();
        if (nProgrammableFills != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int nMotifs = binaryReadInt16();
        if (nMotifs != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int featherPatternCount = binaryReadInt16();
        if (featherPatternCount != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int nColors = binaryReadInt16();
        for (int i = 0; i < nColors; i++) {
            readThread();
        }
        embFile_seek(file, pecStart, SEEK_SET);
    }

    static void readPESHeaderV9()  {
        int pecStart = binaryReadInt32();
        embFile_seek(file, 4, SEEK_CUR);
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
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int nMotifs = binaryReadInt16();
        if (nMotifs != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int featherPatternCount = binaryReadInt16();
        if (featherPatternCount != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int nColors = binaryReadInt16();
        for (int i = 0; i < nColors; i++) {
            readThread();
        }
        embFile_seek(file, pecStart, SEEK_SET);
    }

    static void readPESHeaderV10()  {
        int pecStart = binaryReadInt32();
        embFile_seek(file, 4, SEEK_CUR);
        readDescriptions();
        skip(14);
        int hoopNameStringLength = binaryReadByte();
        String hoopNameString = readString(hoopNameStringLength);
        if (hoopNameString.length() != 0) {
            pattern.setMetadata("hoop_name", hoopNameString);
        }
        embFile_seek(file, 38, SEEK_CUR);
        int fromImageStringLength = binaryReadByte();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(34);
        int nProgrammableFills = binaryReadInt16();
        if (nProgrammableFills != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int nMotifs = binaryReadInt16();
        if (nMotifs != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int featherPatternCount = binaryReadInt16();
        if (featherPatternCount != 0) {
            embFile_seek(file, pecStart, SEEK_SET);
            return;
        }
        int nColors = binaryReadInt16();
        for (int i = 0; i < nColors; i++) {
            readThread();
        }
        embFile_seek(file, pecStart, SEEK_SET);
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
        newColorCode = embThread_findNearestColor_fromThread(color, pec_thread);
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
        newColorCode = embThread_findNearestColor(color, pec_thread);
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
    for (i = 0; i < 2*colorCount; i++) {
        binaryWriteShort(file, colorInfo[i]);
    }
    binaryWriteInt(file, 0);
    if (colorInfo) {
        free(colorInfo);
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

static char writePes(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static char readPhb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned int fileOffset;
    short colorCount;
    int i;

    embFile_seek(file, 0x71, SEEK_SET);
    colorCount = binaryReadInt16(file);

    for (i = 0; i < colorCount; i++) {
        EmbThread t = load_thread(pec_thread, (int)binaryReadByte(file));
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

static char writePhb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writePhb */
}

static char readPhc(EmbPattern* pattern, EmbFile* file, const char* fileName)
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
        t = load_thread(pec_thread, (int)binaryReadByte(file));
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

static char writePhc(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writePhc */
}

static char readPlt(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    float x, y;
    float scalingFactor = 40;
    char input[512];

    embPattern_loadExternalColorFile(pattern, fileName);
    /* TODO: replace all scanf code */
    /* readline needs not to stop at \n, check the file format definition */
    while (!embFile_readline(file, input, 511)) {
        if (input[0] == 'P' && input[1] == 'D') {
            /* TODO: replace all scanf code */
            if (sscanf(input, "PD%f,%f;", &x, &y) < 2) {
                break;
            }
            embPattern_addStitchAbs(pattern, x / scalingFactor, y / scalingFactor, NORMAL, 1);
        } else if (input[0] == 'P' && input[1] == 'U') {
            /* TODO: replace all scanf code */
            if (sscanf(input, "PU%f,%f;", &x, &y) < 2) {
                break;
            }
            embPattern_addStitchAbs(pattern, x / scalingFactor, y / scalingFactor, STOP, 1);
        }
    }
    return 1;
}

static char writePlt(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    /* TODO: pointer safety */
    float scalingFactor = 40;
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

static char readRgb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbThread t;

    embArray_free(pattern->threads);
    pattern->threads = embArray_create(EMB_THREAD);

    string_copy(t.catalogNumber, "NULL");
    string_copy(t.description, "NULL");
    while (embFile_read(embBuffer, 1, 4, file) == 4) {
        t.color = embColor_fromStr(embBuffer);
        embPattern_addThread(pattern, t);
    }
    return 1;
}

static char writeRgb(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;

    embBuffer[3] = 0;
    for (i = 0; i < pattern->threads->count; i++) {
        embColor_toStr(pattern->threads->thread[i].color, embBuffer);
        embFile_write(embBuffer, 1, 4, file);
    }
    return 1;
}

static char sewDecode(unsigned char inputByte)
{
    /* TODO: fix return statement */
    return (inputByte >= 0x80) ? (char)(-~(inputByte - 1)) : (char)inputByte;
}

static char readSew(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i, flags, nColors, fileLength;
    char dx, dy, thisStitchIsJump = 0;

    embFile_seek(file, 0x00, SEEK_END);
    fileLength = embFile_tell(file);
    embFile_seek(file, 0x00, SEEK_SET);
    nColors = binaryReadByte(file);
    nColors += (binaryReadByte(file) << 8);

    for (i = 0; i < nColors; i++) {
        EmbThread t;
        t = load_thread(jef_thread, binaryReadInt16(file));
        embPattern_addThread(pattern, t);
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
static char writeSew(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int colorlistSize, minColors, i;
    float xx, yy;

    colorlistSize = pattern->threads->count;

    minColors = emb_max_int(pattern->threads->count, 6);
    binaryWriteInt(file, 0x74 + (minColors * 4));
    binaryWriteInt(file, 0x0A);

    for (i = 0; i < pattern->threads->count; i++) {
        int thr;
        EmbColor col;
        col = pattern->threads->thread[i].color;
        thr = embThread_findNearestColor(col, jef_thread);
        binaryWriteInt(file, thr);
    }

    embFile_pad(file, 0x0D, (minColors - colorlistSize));
    embFile_pad(file, ' ', 7536);

    xx = 0.0;
    yy = 0.0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        unsigned char b[4];
        float dx, dy;
        EmbStitch st;
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

static char readShv(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

    embFile_seek(file, string_length(headerText), SEEK_SET);
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
    nColors = binaryReadUInt8(file);
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

    for (i = 0; i < nColors; i++) {
        EmbThread t;
        unsigned int stitchCount, colorNumber;
        stitchCount = binaryReadUInt32BE(file);
        colorNumber = binaryReadUInt8(file);
        t = load_thread(shv_thread, colorNumber % 43);
        embPattern_addThread(pattern, t);
        stitchesPerColor[i] = stitchCount;
        embFile_seek(file, 9, SEEK_CUR);
    }

    embFile_seek(file, -2, SEEK_CUR);

    while (1) {
        unsigned char b0, b1;
        int flags;
        if (inJump) {
            flags = JUMP;
        } else {
            flags = NORMAL;
        }
        if (embFile_read(embBuffer, 1, 2, file) != 2) break;
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

static char writeShv(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeShv */
}

static char readSst(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static char writeSst(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static char stxReadThread(StxThread* thread, EmbFile* file)
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
        embLog("ERROR: stxReadThread(), thread==0\n");
        return 0;
    }
    if (!file) {
        embLog("ERROR: stxReadThread(), file==0\n");
        return 0;
    }

    codeLength = binaryReadUInt8(file);
    codeBuff = (char*)malloc(codeLength);
    if (!codeBuff) {
        embLog("ERROR: stxReadThread(), malloc()\n");
        return 0;
    }
    binaryReadBytes(file, (unsigned char*)codeBuff, codeLength); /* TODO: check return value */
    thread->colorCode = codeBuff;
    colorNameLength = binaryReadUInt8(file);
    codeNameBuff = (char*)malloc(colorNameLength);
    if (!codeNameBuff) {
        embLog("ERROR: stxReadThread(), malloc()\n");
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
        embLog("ERROR: stxReadThread(), malloc()\n");
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
        embLog("ERROR: stxReadThread(), malloc()\n");
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
            embLog("ERROR: stxReadThread(), malloc()\n");
            return 0;
        }
        binaryReadBytes(file, (unsigned char*)subCodeBuff, subCodeLength); /* TODO: check return value */
        sd.colorCode = subCodeBuff;
        subColorNameLength = binaryReadUInt8(file);
        subColorNameBuff = (char*)malloc(subColorNameLength);
        if (!subColorNameBuff) {
            embLog("ERROR: stxReadThread(), malloc()\n");
            return 0;
        }
        binaryReadBytes(file, (unsigned char*)subColorNameBuff, subColorNameLength); /* TODO: check return value */
        sd.colorName = subColorNameBuff;
        sd.someOtherInt = binaryReadInt32(file);
        thread->subDescriptors[j] = sd;
    }
    return 1;
}

static char readStx(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i, threadCount;
    unsigned char* gif = 0;
    /* public bitmap Image; */
    StxThread* stxThreads = 0;
    unsigned char headerBytes[7];
    char* header = 0;
    char filetype[4], version[5];
    int paletteLength, imageLength, something1, stitchDataOffset, something3, threadDescriptionOffset, stitchCount, left, right, colors;
    int val[6], vala[6];
    int bottom, top;

    binaryReadBytes(file, headerBytes, 7); /* TODO: check return value */
    header = (char*)headerBytes;

    memory_copy(filetype, &header[0], 3);
    memory_copy(version, &header[3], 4);
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
    /*Image = new bitmap(s2); TODO: review */

    threadCount = binaryReadInt16(file);
    stxThreads = (StxThread*)malloc(sizeof(StxThread) * threadCount);
    if (!stxThreads) {
        embLog("ERROR: readStx(), malloc()\n");
        return 0;
    }
    for (i = 0; i < threadCount; i++) {
        EmbThread t;
        StxThread st;
        stxReadThread(&st, file);

        t.color.r = st.stxColor.r;
        t.color.g = st.stxColor.g;
        t.color.b = st.stxColor.b;
        string_copy(t.description, st.colorName);
        string_copy(t.catalogNumber, st.colorCode);
        embPattern_addThread(pattern, t);
        stxThreads[i] = st;
    }

    embFile_read(embBuffer, 1, 15, file);

    for (i=0; i<6; i++) {
        val[i] = binaryReadInt16(file);
    }
    /* last two val[4] = 0, val[5] = 0 */

    for (i=0; i<6; i++) {
        vala[i] = binaryReadInt16(file);
    }
    /* last two vala[4] = 0, vala[5] = 0 */

    embFile_read(embBuffer, 1, 8, file);

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

static char writeStx(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static char readT01(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[3];

    embPattern_loadExternalColorFile(pattern, fileName);

    while (embFile_read(b, 1, 3, file) == 3) {
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

static char writeT01(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbRect boundingRect;
    int pos[2], i;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    boundingRect = embPattern_calcBoundingBox(pattern);

    pos[0] = 0;
    pos[1] = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        char b[4];
        int dx[2];
        EmbStitch st;
        st = pattern->stitchList->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx[0] = roundDouble(st.x * 10.0) - pos[0];
        dx[1] = roundDouble(st.y * 10.0) - pos[1];
        pos[0] = roundDouble(st.x * 10.0);
        pos[1] = roundDouble(st.y * 10.0);
        
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

        embFile_write(b, 1, 3, file);
    }
    return 1;
}

static char readT09(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    embFile_seek(file, 0x0C, SEEK_SET);

    while (embFile_read(embBuffer, 1, 3, file) == 3) {
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

static char writeT09(EmbPattern* pattern, EmbFile* file, const char* fileName)
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
        embLog("ERROR: encode_dst_ternary(), x is not in valid range [-121,121]\n");
        return 0;
    }
    if (x[1] > 121 || x[1] < -121) {
        embLog("ERROR: encode_dst_ternary(), y is not in valid range [-121,121]\n");
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
        embLog("ERROR: encode_tap_record(), x!=0\n");
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
        embLog("ERROR: encode_tap_record(), y!=0\n");
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

static char readTap(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[3];

    embPattern_loadExternalColorFile(pattern, fileName);

    while (embFile_read(b, 1, 3, file) == 3) {
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

static char writeTap(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbRect boundingRect;
    int pos[2], i;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    boundingRect = embPattern_calcBoundingBox(pattern);

    pos[0] = 0;
    pos[1] = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        unsigned char b[3];
        int dx[2];
        EmbStitch st;
        st = pattern->stitchList->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx[0] = roundDouble(st.x * 10.0) - pos[0];
        dx[1] = roundDouble(st.y * 10.0) - pos[1];
        pos[0] = roundDouble(st.x * 10.0);
        pos[1] = roundDouble(st.y * 10.0);

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

        embFile_write(b, 1, 3, file);
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

static char readThr(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    ThredHeader header;
    EmbColor c;
    EmbThread thread;
    int currentColor, i;

    header.sigVersion = binaryReadUInt32(file);
    header.length = binaryReadUInt32(file);
    header.numStiches = binaryReadUInt16(file);
    header.hoopSize = binaryReadUInt16(file);
    for (i=0; i<7; i++) {
        header.reserved[i] = binaryReadUInt16(file);
    }

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

    embFile_read(embBuffer, 1, 4, file);
    c = embColor_fromStr(embBuffer);

    string_copy(thread.description, "NULL");
    string_copy(thread.catalogNumber, "NULL");
    embFile_read(embBuffer, 1, 16*4, file);
    for (i = 0; i < 16; i++) {
        thread.color = embColor_fromStr(embBuffer+4*i);
        embPattern_addThread(pattern, thread);
    }
    /*  64 bytes of rgbx(4 bytes) colors (16 custom colors) */
    /*  16 bytes of thread size (ascii representation ie. '4') */

    return 1;
}

static char writeThr(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i, stitchCount;
    unsigned char version = 0;
    ThredHeader header;
    ThredExtension extension;
    char bitmapName[16];
    EmbStitch st;
    EmbColor c;

    stitchCount = pattern->stitchList->count;

    memory_set(&header, 0, sizeof(ThredHeader));
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
        memory_set(&extension, 0, sizeof(ThredExtension));
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
    embFile_read("\xFF\xFF\xFF\x00", 1, 4, file);

    embPattern_colorBlock16(pattern, file);

    embFile_pad(file, '4', 16);

    return 1;
}

static char readTxt(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish readTxt */
}

static char writeTxt(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;

    writeInt(file, pattern->stitchList->count, 6);
    embFile_print(file, "\n");

    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st;
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

static char readU00(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;

    /* 16 3byte RGB's start @ 0x08 followed by 14 bytes between 0 and 15 with index of color for each color change */
    embFile_seek(file, 0x08, SEEK_SET);

    for (i = 0; i < 16; i++) {
        EmbThread t;
        embFile_read(embBuffer, 1, 3, file);
        t.color = embColor_fromStr(embBuffer);
        embPattern_addThread(pattern, t);
    }

    embFile_seek(file, 0x100, SEEK_SET);
    while (embFile_read(embBuffer, 1, 3, file) == 3) {
        EmbStitch st;
        st = decode_u00_stitch(embBuffer);
        if (st.flags == END) {
            break;
        }
        embPattern_addStitchRel(pattern, st.x, st.y, st.flags, 1);
    }

    return 1;
}

static char writeU00(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[4], i;

    embFile_pad(file, ' ', 8);

    for (i = 0; i < pattern->threads->count; i++) {
        embColor_toStr(pattern->threads->thread[i].color, b);
        embFile_write(b, 1, 3, file);
    }

    /* this should pad to 256 bytes */
    embFile_pad(file, ' ', 0x100 - 3*pattern->threads->count - 8);

    for (i = 0; i < pattern->stitchList->count; i++) {
        encode_u00_stitch(pattern->stitchList->stitch[i], b);
        embFile_write(b, 1, 3, file);
    }
    return 1;
}

static char readU01(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return readU00(pattern, file, fileName);
}

static char writeU01(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

static unsigned char* vipDecompressData(unsigned char* input, int compressedInputLength, int decompressedContentLength)
{
    unsigned char* decompressedData = (unsigned char*)malloc(decompressedContentLength);
    if (!decompressedData) {
        embLog("ERROR: vipDecompressData(), malloc()\n");
        return 0;
    }
    husExpand((unsigned char*)input, decompressedData, compressedInputLength, 10);
    return decompressedData;
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

static char readVip(EmbPattern* pattern, EmbFile* file, const char* fileName)
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
    header.nColors = binaryReadInt32(file);

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
    decodedColors = (unsigned char*)malloc(header.nColors * 4);
    if (!decodedColors) {
        embLog("ERROR: format-vip.c readVip(), cannot allocate memory for decodedColors\n");
        return 0;
    }

    embFile_seek(datafile, vip_decoding_table, SEEK_SET);
    embFile_read(embBuffer, 1, header.nColors*4, datafile);
    for (i = 0; i < header.nColors * 4; ++i) {
        unsigned char inputByte = binaryReadByte(file);
        unsigned char tmpByte = (unsigned char)(inputByte ^ embBuffer[i]);
        decodedColors[i] = (unsigned char)(tmpByte ^ prevByte);
        prevByte = inputByte;
    }
    for (i = 0; i < header.nColors; i++) {
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

static unsigned char vipEncodeByte(float f)
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

static char writeVip(EmbPattern* pattern, EmbFile* file, const char* fileName)
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

        embFile_seek(datafile, vip_decoding_table, SEEK_SET);
        embFile_read(embBuffer, 1, minColors << 2, datafile);
        for (i = 0; i < minColors << 2; ++i) {
            unsigned char tmpByte = (unsigned char)(decodedColors[i] ^ embBuffer[i]);
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
        embLog("ERROR: vp3ReadString(), file==0\n");
        return 0;
    }
    stringLength = binaryReadInt16BE(file);
    charString = (unsigned char*)malloc(stringLength);
    if (!charString) {
        embLog("ERROR: vp3ReadString(), malloc()\n");
        return 0;
    }
    binaryReadBytes(file, charString, stringLength); /* TODO: check return value */
    return charString;
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

static vp3Hoop vp3ReadHoopSection(EmbFile* file)
{
    vp3Hoop hoop;

    if (!file) {
        embLog("ERROR: vp3ReadHoopSection(), file==0\n");
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
    hoop.nColors = binaryReadByte(file);
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

static char readVp3(EmbPattern* pattern, EmbFile* file, const char* fileName)
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
    someShort = binaryReadInt16(file);
    someByte = binaryReadByte(file);
    bytesRemainingInFile = binaryReadInt32(file);
    fileCommentString = vp3ReadString(file);
    hoopConfigurationOffset = (int)embFile_tell(file);

    vp3ReadHoopSection(file);

    anotherCommentString = vp3ReadString(file);

    /* TODO: review v1 thru v18 variables and use emb_unused() if needed */
    embFile_read(v1, 1, 18, file);
    printf("determine what these 18 variables are: ");
    for (i=0; i<18; i++) {
        printf("%c\n", v1[i]);
    }

    binaryReadBytes(file, magicCode, 6);
    if (!(magicCode[5] == 0 && string_equal("\x78\x78\x55\x55\x01", magicCode))) {
        return 0;
    }

    anotherSoftwareVendorString = vp3ReadString(file);

    nColors = binaryReadInt16BE(file);
    embLog("ERROR: Number of Colors: %d\n" /*, nColors */);
    colorSectionOffset = (int)embFile_tell(file);

    for (i = 0; i < nColors; i++) {
        EmbThread t;
        char tableSize;
        int startX, startY, offsetToNextColorX, offsetToNextColorY;
        unsigned char *threadColorNumber, *colorName, *threadVendor;
        int unknownThreadString, numberOfBytesInColor;

        embFile_seek(file, colorSectionOffset, SEEK_SET);
        embFile_read(embBuffer, 1, 3, file);
        embLog("ERROR: Color Check Byte #1: 0 == %d\n");
        embLog("ERROR: Color Check Byte #2: 5 == %d\n");
        embLog("ERROR: Color Check Byte #3: 0 == %d\n");
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
        if (i + 1 < nColors)
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
    vp3WriteStringLen(file, str, string_length(str));
}

void vp3PatchByteCount(EmbFile* file, int offset, int adjustment)
{
    int currentPos = embFile_tell(file);
    embFile_seek(file, offset, SEEK_SET);
    embLog("Patching byte count: \n" /*, currentPos - offset + adjustment */);
    binaryWriteIntBE(file, currentPos - offset + adjustment);
    embFile_seek(file, currentPos, SEEK_SET);
}

static char writeVp3(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbRect bounds;
    EmbStitch st;
    int remainingBytesPos, remainingBytesPos2, colorSectionStitchBytes,
        first, i, nColors, flag;
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

    remainingBytesPos = embFile_tell(file);
    binaryWriteInt(file, 0); /* placeholder */
    vp3WriteString(file, "");
    binaryWriteIntBE(file, bounds.right * 1000);
    binaryWriteIntBE(file, bounds.bottom * 1000);
    binaryWriteIntBE(file, bounds.left * 1000);
    binaryWriteIntBE(file, bounds.top * 1000);
    binaryWriteInt(file, 0); /* this would be some (unknown) function of thread length */
    binaryWriteByte(file, 0);

    nColors = 0;

    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];

        /* pointer = mainPointer; */
        flag = st.flags;
        newColor = pattern->threads->thread[st.color].color;
        if (newColor.r != color.r || newColor.g != color.g || newColor.b != color.b) {
            nColors++;
            color.r = newColor.r;
            color.g = newColor.g;
            color.b = newColor.b;
        } else if (flag & END || flag & STOP) {
            nColors++;
        }

        while (flag == pattern->stitchList->stitch[i].flags) {
            i++;
        }
        /* mainPointer = pointer; */
    }

    binaryWriteByte(file, nColors);
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
    binaryWriteShortBE(file, nColors);

    for (i = 0; i < pattern->stitchList->count; i++) {
        char colorName[8] = { 0 };
        float lastX, lastY;
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

static char readXxx(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[4];
    unsigned char b0, b1;
    int dx = 0, dy = 0;
    int flags, nColors, paletteOffset, i;
    char endOfStream = 0;
    char thisStitchJump = 0;
    EmbThread thread;
    EmbStitch st;

    embFile_seek(file, 0x27, SEEK_SET);
    nColors = binaryReadInt16(file);
    embFile_seek(file, 0xFC, SEEK_SET);
    paletteOffset = binaryReadInt32(file);
    embFile_seek(file, paletteOffset + 6, SEEK_SET);

    for (i = 0; i < nColors; i++) {
        embFile_read(b, 1, 4, file);
        thread.color = embColor_fromStr(b);
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

static void xxxEncodeStitch(EmbFile* file, float deltaX, float deltaY, int flags)
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
    float thisX = 0.0f;
    float thisY = 0.0f;
    float previousX, previousY, deltaX, deltaY;
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

static char writeXxx(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char i;
    EmbRect rect;
    EmbColor c;
    int endOfStitches;
    unsigned char b[4];

    embPattern_correctForMaxStitchLength(pattern, 124, 127);

    embFile_pad(file, 0, 0x17);
    binaryWriteUInt(file, (unsigned int)pattern->stitchList->count);
    embFile_pad(file, 0, 0x0C);
    binaryWriteUShort(file, (unsigned short)pattern->threads->count);
    embFile_pad(file, 0, 2);

    rect = embPattern_calcBoundingBox(pattern);
    binaryWriteShort(file, (short)(embRect_width(rect) * 10.0));
    binaryWriteShort(file, (short)(embRect_height(rect) * 10.0));

    binaryWriteShort(file, (short)(embRect_width(rect) / 2.0 * 10)); /*TODO: xEnd from start point x=0 */
    binaryWriteShort(file, (short)(embRect_height(rect) / 2.0 * 10)); /*TODO: yEnd from start point y=0 */
    binaryWriteShort(file, (short)(embRect_width(rect) / 2.0 * 10)); /*TODO: left from start x = 0     */
    binaryWriteShort(file, (short)(embRect_height(rect) / 2.0 * 10)); /*TODO: bottom from start y = 0   */
    embFile_pad(file, 0, 0xC5);
    binaryWriteInt(file, 0x0000); /* place holder for end of stitches */

    xxxEncodeDesign(file, pattern);

    endOfStitches = embFile_tell(file);

    embFile_seek(file, 0xFC, SEEK_SET);

    binaryWriteUInt(file, endOfStitches);

    embFile_seek(file, 0, SEEK_END);

    /* Is this really correct? */
    embFile_write("\x7F\x7F\x03\x14\x00\x00", 1, 6, file);

    for (i = 0; i < 22; i++) {
        if (i < pattern->threads->count) {
            b[0] = 0;
            embColor_toStr(pattern->threads->thread[i].color, b+1);
            embFile_write(b, 1, 4, file);
        } else {
            binaryWriteUInt(file, 0x01000000);
        }
    }

    embFile_write("\x00\x01", 1, 2, file);
    return 1;
}

static char readZsk(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    char b[3];
    int stitchType;
    unsigned char colorNumber;
    EmbThread t;

    embFile_seek(file, 0x230, SEEK_SET);
    colorNumber = binaryReadUInt8(file);
    while (colorNumber != 0) {
        embFile_read(b, 1, 3, file);
        t.color = embColor_fromStr(b);
        string_copy(t.catalogNumber, "NULL");
        string_copy(t.description, "NULL");
        embPattern_addThread(pattern, t);
        embFile_seek(file, 0x48, SEEK_CUR);
        embFile_read(&colorNumber, 1, 1, file);
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

static char writeZsk(EmbPattern* pattern, EmbFile* file, const char* fileName)
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
 * Writes out a color to the EmbFile* file in hex format without using
 * printf or varadic functions (for embedded systems).
 */
static void write_svg_color(EmbFile *file, EmbColor color)
{
    char hex[] = "0123456789ABCDEF";
    embFile_print(file, "stroke=\"#");
    embFile_write(hex + (color.r % 16), 1, 1, file);
    embFile_write(hex + (color.r / 16), 1, 1, file);
    embFile_write(hex + (color.g % 16), 1, 1, file);
    embFile_write(hex + (color.g / 16), 1, 1, file);
    embFile_write(hex + (color.b % 16), 1, 1, file);
    embFile_write(hex + (color.b / 16), 1, 1, file);
    embFile_print(file, "\" ");
}

static void writePoint(EmbFile* file, float x, float y, int space)
{
    if (space) {
        embFile_print(file, " ");
    }
    /*    char buffer[30];
    embFloatToArray(buffer, number, 1.0e-7, 3, 5);
    embFile_print(file, buffer);*/
    fprintf(file->file, "%f,%f", x, y);
}

void writeFloat(EmbFile* file, float number)
{
    /* TODO: fix bugs in embFloatToArray */
    /*    char buffer[30];
    embFloatToArray(buffer, number, 1.0e-7, 3, 5);
    embFile_print(file, buffer);*/
    sprintf(embBuffer, "%f", number);
    embFile_print(file, embBuffer);
}

void writeFloatWrap(EmbFile* file, char *prefix, float number, char *suffix)
{
    embFile_print(file, prefix);
    writeFloat(file, number);
    embFile_print(file, suffix);
}

void writeFloatAttribute(EmbFile* file, char *attribute, float number)
{
    embFile_print(file, attribute);
    writeFloatWrap(file, "=\"", number, "\" ");
}

typedef struct SvgAttribute_ {
    char* name;
    char* value;
} SvgAttribute;

typedef struct SvgAttributeList_ {
    SvgAttribute attribute;
    struct SvgAttributeList_* next;
} SvgAttributeList;

typedef struct SvgElement_ {
    char* name;
    SvgAttributeList* attributeList;
    SvgAttributeList* lastAttribute;
} SvgElement;

static int svgCreator;

static int svgExpect;
static int svgMultiValue;

static SvgElement* currentElement;
static char* currentAttribute;
static char* currentValue;

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
        c.r = (unsigned char)roundDouble(255.0 / 100.0 * atof(r));
        c.g = (unsigned char)roundDouble(255.0 / 100.0 * atof(g));
        c.b = (unsigned char)roundDouble(255.0 / 100.0 * atof(b));
    } else if (intfunc) {
        /* Integer functional - rgb(rrr, ggg, bbb), by now it is stored in r, g and b. */
        c.r = (unsigned char)atoi(r);
        c.g = (unsigned char)atoi(g);
        c.b = (unsigned char)atoi(b);
    } else {
        /* Color keyword */
        int tableColor = threadColor(&c, colorStr, SVG_Colors);
        if (!tableColor) {
            printf("SVG color string not found: %s.\n", colorStr);
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
    /*else { embLog("ERROR: svgPathCmdToEmbPathFlag(), unknown command '%c'\n", cmd); return MOVETO; } */

    return LINETO;
}

SvgAttribute svgAttribute_create(const char* name, const char* value)
{
    int i, j;
    SvgAttribute attribute;
    char *modValue;

    modValue = malloc(string_length(value) + 1);
    string_copy(modValue, value);
    j = 0;
    for (i=0; i<string_length(value); i++) {
        if (value[i] == '"') continue;
        if (value[i] == '\'') continue;
        if (value[i] == '/') continue;
        if (value[i] == ',') continue;
        modValue[j] = value[i];
    }
    string_copy(attribute.name, name);
    attribute.value = modValue;
    return attribute;
}

void svgElement_addAttribute(SvgElement* element, SvgAttribute data)
{
    if (!element) {
        embLog("ERROR: svgElement_addAttribute(), element==0.");
        return;
    }

    if (!(element->attributeList)) {
        element->attributeList = (SvgAttributeList*)malloc(sizeof(SvgAttributeList));
        if (!(element->attributeList)) {
            embLog("ERROR: svgElement_addAttribute(), cannot allocate memory for element->attributeList.");
            return;
        }
        element->attributeList->attribute = data;
        element->attributeList->next = 0;
        element->lastAttribute = element->attributeList;
        element->lastAttribute->next = 0;
    } else {
        SvgAttributeList* pointerLast = element->lastAttribute;
        SvgAttributeList* list = (SvgAttributeList*)malloc(sizeof(SvgAttributeList));
        if (!list) {
            embLog("ERROR: svgElement_addAttribute(), cannot allocate memory for list.");
            return;
        }
        list->attribute = data;
        list->next = 0;
        pointerLast->next = list;
        element->lastAttribute = list;
    }
}

void svgElement_free(SvgElement* element)
{
    SvgAttributeList* list = 0;
    SvgAttributeList* nextList = 0;
    if (!element)
        return;

    list = element->attributeList;

    while (list) {
        free(list->attribute.name);
        list->attribute.name = 0;
        free(list->attribute.value);
        list->attribute.value = 0;
        nextList = list->next;
        free(list);
        list = nextList;
    }

    element->lastAttribute = 0;
    free(element->name);
    free(element);
}

SvgElement* svgElement_create(const char* name)
{
    SvgElement* element = 0;

    element = (SvgElement*)malloc(sizeof(SvgElement));
    if (!element) {
        embLog("ERROR: svgElement_create(), cannot allocate memory for element\n");
        return 0;
    }
    /* switch the element index */
/*    element->name = emb_strdup((char*)name); */
    if (!element->name) {
        embLog("ERROR: svgElement_create(), element->name is null\n");
        return 0;
    }
    element->attributeList = 0;
    element->lastAttribute = 0;
    return element;
}

char* svgAttribute_getValue(SvgElement* element, const char* name)
{
    SvgAttributeList* pointer = 0;

    if (!element) {
        embLog("ERROR: svgAttribute_getValue(), element==0\n");
        return "none";
    }
    if (!name) {
        embLog("ERROR: svgAttribute_getValue(), name==0\n");
        return "none";
    }
    if (!element->attributeList) { /* TODO: error */
        return "none";
    }

    pointer = element->attributeList;
    while (pointer) {
        if (string_equal(pointer->attribute.name, name)) {
            return pointer->attribute.value;
        }
        pointer = pointer->next;
    }

    return "none";
}

void svgAddToPattern(EmbPattern* p)
{
    const char* buff = 0;
    EmbVector test;
    EmbColor color;
    EmbPathObject* path;

    if (!p) {
        embLog("ERROR: svgAddToPattern(), p==0\n");
        return;
    }
    if (!currentElement) {
        return;
    }

    char token = identify_element(currentElement->name);

    switch (token) {
    case ELEMENT_XML:
    case ELEMENT_A:
    case ELEMENT_ANIMATE:
    case ELEMENT_ANIMATE_COLOR:
    case ELEMENT_ANIMATE_MOTION:
    case ELEMENT_ANIMATE_TRANSFORM:
    case ELEMENT_ANIMATION:
    case ELEMENT_AUDIO:
        break;
    case ELEMENT_CIRCLE:
        {
        float cx, cy, r;
        cx = atof(svgAttribute_getValue(currentElement, "cx"));
        cy = atof(svgAttribute_getValue(currentElement, "cy"));
        r = atof(svgAttribute_getValue(currentElement, "r"));
        embPattern_addCircleObjectAbs(p, cx, cy, r);
        }
        break;
    case ELEMENT_DEFS:
    case ELEMENT_DESC:
    case ELEMENT_DISCARD:
        break;
    case ELEMENT_ELLIPSE:
        {
        float cx, cy, rx, ry;
        cx = atof(svgAttribute_getValue(currentElement, "cx"));
        cy = atof(svgAttribute_getValue(currentElement, "cy"));
        rx = atof(svgAttribute_getValue(currentElement, "rx"));
        ry = atof(svgAttribute_getValue(currentElement, "ry"));
        embPattern_addEllipseObjectAbs(p, cx, cy, rx, ry);
        }
        break;
    case ELEMENT_FONT:
    case ELEMENT_FONT_FACE:
    case ELEMENT_FONT_FACE_SRC:
    case ELEMENT_FONT_FACE_URI:
    case ELEMENT_FOREIGN_OBJECT:
    case ELEMENT_G:
    case ELEMENT_GLYPH:
    case ELEMENT_HANDLER:
    case ELEMENT_HKERN:
    case ELEMENT_IMAGE:
        break;
    case ELEMENT_LINE:
        {
        char* x1 = svgAttribute_getValue(currentElement, "x1");
        char* y1 = svgAttribute_getValue(currentElement, "y1");
        char* x2 = svgAttribute_getValue(currentElement, "x2");
        char* y2 = svgAttribute_getValue(currentElement, "y2");

        /* If the starting and ending points are the same, it is a point */
        if (string_equal(x1, x2) && string_equal(y1, y2)) {
            embPattern_addPointObjectAbs(p, atof(x1), atof(y1));
        }
        else {
            embPattern_addLineObjectAbs(p, atof(x1), atof(y1), atof(x2), atof(y2));
        }
        }
        break;
    case ELEMENT_LINEAR_GRADIENT:
    case ELEMENT_LISTENER:
    case ELEMENT_METADATA:
    case ELEMENT_MISSING_GLYPH:
    case ELEMENT_MPATH:
        break;
    case ELEMENT_PATH:
        {
        /* TODO: finish */

        char* pointStr = svgAttribute_getValue(currentElement, "d");
        char* mystrok = svgAttribute_getValue(currentElement, "stroke");

        int last = string_length(pointStr);
        int size = 32;
        int i = 0;
        int j = 0;
        int pos = 0;
        /* An odometer aka 'tripometer' used for stepping thru the pathData */
        int trip = -1; /* count of float[] that has been filled. 0=first item of array, -1=not filled = empty array */
        int reset = -1;
        float xx = 0.0;
        float yy = 0.0;
        float fx = 0.0;
        float fy = 0.0;
        float lx = 0.0;
        float ly = 0.0;
        float cx1 = 0.0, cx2 = 0.0;
        float cy1 = 0.0, cy2 = 0.0;
        int cmd = 0;
        float pathData[7];
        unsigned int numMoves = 0;
        int pendingTask = 0;
        int relative = 0;

        EmbArray* pointList = 0;
        EmbArray* flagList;

        char* pathbuff = 0;
        pathbuff = (char*)malloc(size);
        if (!pathbuff) {
            embLog("ERROR: svgAddToPattern(), cannot allocate memory for pathbuff\n");
            return;
        }

        printf("stroke:%s\n", mystrok);

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

                /*printf("    ,'%s'    ~POS=%d  ~TRIP=%d  ~[pos]=%d\n", pathbuff,pos,trip, pathbuff[pos]);*/
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

                /* below "while" is for avoid loosing last 'z' command that maybe never accomodated. */
                pendingTask = 1;
                if (i == last - 1) {
                    pendingTask = 2;
                }

                while (pendingTask > 0) {
                    pendingTask -= 1;

                    /* Check wether prior command need to be saved */
                    if (trip >= 0) {
                        trip = -1;
                        reset = -1;

                        relative = 0; /* relative to prior coordinate point or absolute coordinate? */

                        if (cmd == 'M') {
                            xx = pathData[0];
                            yy = pathData[1];
                            fx = xx;
                            fy = yy;
                        } else if (cmd == 'm') {
                            xx = pathData[0];
                            yy = pathData[1];
                            fx = xx;
                            fy = yy;
                            relative = 1;
                        } else if (cmd == 'L') {
                            xx = pathData[0];
                            yy = pathData[1];
                        } else if (cmd == 'l') {
                            xx = pathData[0];
                            yy = pathData[1];
                            relative = 1;
                        } else if (cmd == 'H') {
                            xx = pathData[0];
                            yy = ly;
                        } else if (cmd == 'h') {
                            xx = pathData[0];
                            yy = ly;
                            relative = 1;
                        } else if (cmd == 'V') {
                            xx = lx;
                            yy = pathData[1];
                        } else if (cmd == 'v') {
                            xx = lx;
                            yy = pathData[1];
                            relative = 1;
                        } else if (cmd == 'C') {
                            xx = pathData[4];
                            yy = pathData[5];
                            cx1 = pathData[0];
                            cy1 = pathData[1];
                            cx2 = pathData[2];
                            cy2 = pathData[3];
                        } else if (cmd == 'c') {
                            xx = pathData[4];
                            yy = pathData[5];
                            cx1 = pathData[0];
                            cy1 = pathData[1];
                            cx2 = pathData[2];
                            cy2 = pathData[3];
                            relative = 1;
                        }
                        /*
                            else if(cmd == 'S') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 's') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 'Q') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 'q') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 'T') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 't') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 'A') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 'a') { xx = pathData[0]; yy = pathData[1]; }
                            */
                        else if (cmd == 'Z') {
                            xx = fx;
                            yy = fy;
                        } else if (cmd == 'z') {
                            xx = fx;
                            yy = fy;
                        }

                        if (!pointList && !flagList) {
                            pointList = embArray_create(EMB_POINT);
                            flagList = embArray_create(EMB_FLAG);
                        }
                        test.x = xx;
                        test.y = yy;
                        embArray_addPoint(pointList, test, 0, black);
                        embArray_addFlag(flagList, svgPathCmdToEmbPathFlag(cmd));
                        lx = xx;
                        ly = yy;

                        pathbuff[0] = (char)cmd; /* set the command for compare */
                        pathbuff[1] = 0;
                        pos = 0;

                        printf("*prior:%s (%f, %f,  %f, %f,     %f,%f,  %f) \n", pathbuff,
                            pathData[0],
                            pathData[1],
                            pathData[2],
                            pathData[3],
                            pathData[4],
                            pathData[5],
                            pathData[6]);
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
                            embLog("ERROR: svgAddToPattern(), %s is not a valid svg path command, skipping...");
                            embLog(pathbuff);
                            trip = -1;
                            break;
                        }
                    }
                    /* avoid loosing 'z' command that maybe never accomodated. */
                    if (i == last - 1) {
                        trip = 2;
                    }
                } /* while pendingTask */

                break;
            }
            if (pos >= size - 1) {
                /* increase pathbuff length - leave room for 0 */
                size *= 2;
                pathbuff = (char*)realloc(pathbuff, size);
                if (!pathbuff) {
                    embLog("ERROR: svgAddToPattern(), cannot re-allocate memory for pathbuff\n");
                    return;
                }
            }
        }
        free(pathbuff);

        /* TODO: subdivide numMoves > 1 */

        color = svgColorToEmbColor(svgAttribute_getValue(currentElement, "stroke"));
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
        char* pointStr = svgAttribute_getValue(currentElement, "points");
        int last = string_length(pointStr);
        int size = 32;
        int i = 0;
        int pos = 0;
        unsigned char odd = 1;
        float xx = 0.0;
        float yy = 0.0;

        EmbArray* pointList = 0;

        char* polybuff = 0;
        polybuff = (char*)malloc(size);
        if (!polybuff) {
            embLog("ERROR: svgAddToPattern(), cannot allocate memory for polybuff\n");
            return;
        }

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
                    xx = atof(polybuff);
                } else {
                    odd = 1;
                    yy = atof(polybuff);

                    if (!pointList) {
                        pointList = embArray_create(EMB_POINT);
                    }
                    EmbVector a;
                    a.x = xx;
                    a.y = yy;
                    embArray_addPoint(pointList, a, 0, black);
                }

                break;
            default:
                polybuff[pos++] = (char)c;
                break;
            }
            if (pos >= size - 1) {
                /* increase polybuff length - leave room for 0 */
                size *= 2;
                polybuff = (char*)realloc(polybuff, size);
                if (!polybuff) {
                    embLog("ERROR: svgAddToPattern(), cannot re-allocate memory for polybuff\n");
                    return;
                }
            }
        }
        free(polybuff);

        if (token == ELEMENT_POLYGON) {
            EmbPolygonObject polygonObj;
            polygonObj.pointList = pointList;
            polygonObj.color = svgColorToEmbColor(svgAttribute_getValue(currentElement, "stroke"));
            polygonObj.lineType = 1; /* TODO: use lineType enum */
            embPattern_addPolygonObjectAbs(p, &polygonObj);
        }
        else { /* polyline */
            EmbPolylineObject* polylineObj;
            polylineObj->pointList = pointList;
            polylineObj->color = svgColorToEmbColor(svgAttribute_getValue(currentElement, "stroke"));
            polylineObj->lineType = 1; /* TODO: use lineType enum */
            embPattern_addPolylineObjectAbs(p, polylineObj);
        }

        }
        break;
    case ELEMENT_PREFETCH:
    case ELEMENT_RADIAL_GRADIENT:
    case ELEMENT_RECT:
        {
        float x1, y1, width, height;
        x1 = atof(svgAttribute_getValue(currentElement, "x"));
        y1 = atof(svgAttribute_getValue(currentElement, "y"));
        width = atof(svgAttribute_getValue(currentElement, "width"));
        height = atof(svgAttribute_getValue(currentElement, "height"));
        embPattern_addRectObjectAbs(p, x1, y1, width, height);
        }
        break;
    case ELEMENT_SCRIPT:
    case ELEMENT_SET:
    case ELEMENT_SOLID_COLOR:
    case ELEMENT_STOP:
    case ELEMENT_SVG:
    case ELEMENT_SWITCH:
    case ELEMENT_TBREAK:
    case ELEMENT_TEXT:
    case ELEMENT_TEXT_AREA:
    case ELEMENT_TITLE:
    case ELEMENT_TSPAN:
    case ELEMENT_USE:
    case ELEMENT_VIDEO:
    case ELEMENT_UNKNOWN:
    default:
        break;
    }

    svgElement_free(currentElement);
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

static char string_in_table(char *buff, int table)
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

    embLog("svgIsSvgAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

static int svgIsCatchAllAttribute(const char* buff)
{
    int out;
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

    embLog("");
    embLog(errormsg);
    embLog("attribute unknown:");
    embLog(buff);

    return SVG_NULL;
}


static char identify_element(char *token)
{
    int offset;
    char id;
    for (id=0; id < ELEMENT_UNKNOWN; id++) {
        offset = dereference_int(svg_element_token_table);
        get_str(embBuffer, offset + 4*id);
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
            printf("ELEMENT:\n");
            svgExpect = SVG_EXPECT_ATTRIBUTE;
            currentElement = svgElement_create(buff);
        } else {
            return;
        }
    } else if (svgExpect == SVG_EXPECT_ATTRIBUTE) {
        char advance = 0;
        if (!currentElement) {
            embLog("There is no current element but the parser expects one.");
            return;
        }
        char token = identify_element(currentElement->name);
        
        switch (token) {
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
            if (token == ELEMENT_XML) {
                int xmlTokens = double_dereference_int(svg_token_lists, 0);
                advance = svgHasAttribute(buff, xmlTokens, "?xml");
            }
            else if (token == ELEMENT_SVG) {
                advance = svgIsSvgAttribute(buff);
            }
            else if (token != ELEMENT_UNKNOWN) {
                char element_token[30];
                int out2;
                int out = double_dereference_int(svg_token_lists, token);
                out2 = dereference_int(svg_element_token_table);
                get_str(element_token, out2+4*token);
                
                advance = svgHasAttribute(buff, out, element_token);
            }
        }

        if (advance) {
            printf("ATTRIBUTE:\n");
            svgExpect = SVG_EXPECT_VALUE;
            free(currentAttribute);
            string_copy(currentAttribute, buff);
        }
    } else if (svgExpect == SVG_EXPECT_VALUE) {
        int last = string_length(buff) - 1;
        printf("VALUE:\n");

        /* single-value */
        if ((buff[0] == '"' || buff[0] == '\'') && (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') && !svgMultiValue) {
            svgExpect = SVG_EXPECT_ATTRIBUTE;
            svgElement_addAttribute(currentElement, svgAttribute_create(currentAttribute, buff));
        } else /* multi-value */
        {
            svgMultiValue = 1;
            if (!currentValue) {
                string_copy(currentValue, buff);
                if (!currentValue) { /*TODO: error */
                    return;
                }
            } else {
                string_copy((char *)embBuffer, currentValue);
                currentValue = realloc(string_length(buff) + string_length((char *)embBuffer) + 2, 1);
                if (!currentValue) {
                    embLog("ERROR: svgProcess(), cannot allocate memory for currentValue\n");
                    return;
                }
                if (currentValue) {
                    memory_set(currentValue, 0, string_length(buff) + string_length(embBuffer) + 2);
                }
                strcat(currentValue, embBuffer);
                strcat(currentValue, " ");
                strcat(currentValue, buff);
            }

            if (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') {
                svgMultiValue = 0;
                svgExpect = SVG_EXPECT_ATTRIBUTE;
                svgElement_addAttribute(currentElement, svgAttribute_create(currentAttribute, currentValue));
                free(currentValue);
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
static char readSvg(EmbPattern* p, EmbFile* file, const char* fileName)
{
    int size = 1024;
    int pos;
    int c = 0;
    char* buff = 0;

    buff = (char*)malloc(size);
    if (!buff) {
        embLog("ERROR: readSvg(), cannot allocate memory for buff\n");
        return 0;
    }

    svgCreator = SVG_CREATOR_NULL;

    svgExpect = SVG_EXPECT_NULL;
    svgMultiValue = 0;

    currentElement = 0;
    currentAttribute = 0;
    currentValue = 0;

    /* Pre-flip incase of multiple reads on the same p */
    embPattern_flipVertical(p);

    pos = 0;
    while (embFile_read(&c, 1, 1, file)) {
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
        if (pos >= size - 1) {
            /* increase buff length - leave room for 0 */
            size *= 2;
            buff = (char*)realloc(buff, size);
            if (!buff) {
                embLog("ERROR: readSvg(), cannot re-allocate memory for buff.");
                return 0;
            }
        }
    }

    free(buff);
    free(currentAttribute);
    free(currentValue);

    embPattern_writeAuto(p, "object_summary.svg");

    /* Flip the p since SVG Y+ is down and libembroidery Y+ is up. */
    embPattern_flipVertical(p);

    return 1; /*TODO: finish readSvg */
}

static void writeCircles(EmbPattern* p, EmbFile* file)
{
    int i;
    EmbCircle circle;
    if (p->circles) {
        for (i = 0; i < p->circles->count; i++) {
            circle = p->circles->circle[i];
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<circle stroke-width=\"0.2\" fill=\"none\" ");
            write_svg_color(file, p->circles->color[i]);
            writeFloatAttribute(file, "cx", circle.center.x);
            writeFloatAttribute(file, "cy", circle.center.y);
            writeFloatAttribute(file, "r", circle.radius);
            embFile_print(file, "/>");
        }
    }
}

static void writeEllipses(EmbPattern* p, EmbFile* file)
{
    if (p->ellipses) {
        int i;
        for (i = 0; i < p->ellipses->count; i++) {
            EmbEllipse ellipse;
            ellipse = p->ellipses->ellipse[i];
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<ellipse stroke-width=\"0.2\" fill=\"none\" ");
            write_svg_color(file, p->ellipses->color[i]);
            writeFloatAttribute(file, "cx", ellipse.center.x);
            writeFloatAttribute(file, "cy", ellipse.center.y);
            writeFloatAttribute(file, "rx", ellipse.radius.x);
            writeFloatAttribute(file, "ry", ellipse.radius.y);
            embFile_print(file, "/>");
        }
    }
}

static void writeLines(EmbPattern* p, EmbFile* file)
{
    if (p->lines) {
        int i;
        for (i = 0; i < p->lines->count; i++) {
            EmbLine line = p->lines->line[i];
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<line stroke-width=\"0.2\" fill=\"none\" ");
            write_svg_color(file, p->lines->color[i]);
            writeFloatAttribute(file, "x1", line.start.x);
            writeFloatAttribute(file, "y1", line.start.y);
            writeFloatAttribute(file, "x2", line.end.x);
            writeFloatAttribute(file, "y2", line.end.y);
            embFile_print(file, " />");
        }
    }
}

static void writePoints(EmbPattern* p, EmbFile* file)
{
    if (p->points) {
        int i;
        for (i = 0; i < p->points->count; i++) {
            EmbVector point;
            point = p->points->point[i];
            /* See SVG Tiny 1.2 Spec:
             * Section 9.5 The 'line' element
             * Section C.6 'path' element implementation notes */
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<line stroke-linecap=\"round\" stroke-width=\"0.2\" fill=\"none\" ");
            write_svg_color(file, p->points->color[i]);
            writeFloatAttribute(file, "x1", point.x);
            writeFloatAttribute(file, "y1", point.y);
            writeFloatAttribute(file, "x2", point.x);
            writeFloatAttribute(file, "y2", point.y);
            embFile_print(file, " />");
        }
    }
}

static void writePolygons(EmbPattern* p, EmbFile* file)
{
    int i, j;
    EmbArray* pointList;
    if (p->polygons) {
        for (i = 0; i < p->polygons->count; i++) {
            pointList = p->polygons->polygon[i]->pointList;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<polygon stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" fill=\"none\" ");
            write_svg_color(file, p->polygons->polygon[i]->color);
            embFile_print(file, "points=\"");
            writePoint(file, pointList->point[0].x, pointList->point[0].y, 0);
            for (j = 1; j < pointList->count; j++) {
                writePoint(file, pointList->point[j].x, pointList->point[j].y, 1);
            }
            embFile_print(file, "\" />");
        }
    }
}

static void writePolylines(EmbPattern* p, EmbFile* file)
{
    int i, j;
    EmbArray* pointList;
    EmbColor color;
    if (p->polylines) {
        for (i = 0; i < p->polylines->count; i++) {
            pointList = p->polylines->polyline[i]->pointList;
            color = p->polylines->polyline[i]->color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" ");
            write_svg_color(file, color);
            embFile_print(file, "fill=\"none\" points=\"");
            writePoint(file, pointList->point[0].x, pointList->point[0].y, 0);
            for (j = 1; j < pointList->count; j++) {
                writePoint(file, pointList->point[j].x, pointList->point[j].y, 1);
            }
            embFile_print(file, "\" />");
        }
    }
}

static void writeRects(EmbPattern* p, EmbFile* file)
{
    int i;
    EmbRect rect;
    if (p->rects) {
        for (i = 0; i < p->rects->count; i++) {
            rect = p->rects->rect[i];
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<rect stroke-width=\"0.2\" fill=\"none\" ");
            write_svg_color(file, p->rects->color[i]);
            writeFloatAttribute(file, "x", embRect_x(rect));
            writeFloatAttribute(file, "y", embRect_y(rect));
            writeFloatAttribute(file, "width", embRect_width(rect));
            writeFloatAttribute(file, "height", embRect_height(rect));
            embFile_print(file, " />");
        }
    }
}

static void writeStitchList(EmbPattern* p, EmbFile* file)
{
    /*TODO: Low Priority Optimization:
     *      Make sure that the line length that is output doesn't exceed 1000 characters. */
    int i;
    char isNormal;
    EmbColor color;
    EmbStitch st;
    if (p->stitchList) {
        /*TODO: #ifdef SVG_DEBUG for Josh which outputs JUMPS/TRIMS instead of chopping them out */
        isNormal = 0;
        for (i = 0; i < p->stitchList->count; i++) {
            st = p->stitchList->stitch[i];
            if (st.flags == NORMAL && !isNormal) {
                isNormal = 1;
                color = p->threads->thread[st.color].color;
                /* TODO: use proper thread width for stoke-width rather than just 0.2 */
                embFile_print(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" ");
                write_svg_color(file, color);
                embFile_print(file, "fill=\"none\" points=\"");
                writePoint(file, st.x, st.y, 0);
            } else if (st.flags == NORMAL && isNormal) {
                writePoint(file, st.x, st.y, 1);
            } else if (st.flags != NORMAL && isNormal) {
                isNormal = 0;
                embFile_print(file, "\"/>");
            }
        }
    }
}

static char writeSvg(EmbPattern* p, EmbFile* file, const char* fileName)
{
    EmbRect boundingRect;

    /* Pre-flip the p since SVG Y+ is down and libembroidery Y+ is up. */
    embPattern_flipVertical(p);

    boundingRect = embPattern_calcBoundingBox(p);
    embFile_print(file,
        "<?xml version=\"1.0\"?>\n" \
        "<!-- Embroidermodder 2 SVG Embroidery File -->\n" \
        "<!-- http://embroidermodder.github.io -->\n" \
        "<svg viewBox=\"");

    /* TODO: See the SVG Tiny Version 1.2 Specification Section 7.14.
     *       Until all of the formats and API is stable, the width, height and viewBox attributes need to be left unspecified.
     *       If the attribute values are incorrect, some applications wont open it at all.
     */
    writeFloatWrap(file, "", boundingRect.left, " ");
    writeFloatWrap(file, "", boundingRect.top, " ");
    writeFloatWrap(file, "", embRect_width(boundingRect), " ");
    writeFloatWrap(file, "", embRect_height(boundingRect),
        "\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.2\" baseProfile=\"tiny\">");

    /*TODO: Low Priority: Indent output properly. */

    writeCircles(p, file);
    writeEllipses(p, file);
    writeLines(p, file);
    writePoints(p, file);
    writePolygons(p, file);
    writePolylines(p, file);
    writeRects(p, file);
    writeStitchList(p, file);

    embFile_print(file, "\n</svg>\n");

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
    int currentClosestValue, closestIndex, i, out, length;

    currentClosestValue = 256 * 256 * 3;
    closestIndex = -1;

    length = dereference_int(table_lengths);
    out = dereference_int(thread_table);
    for (i = 0; i < length; i++) {
        int delta;
        EmbColor c;
        embFile_seek(datafile, out+35*i, SEEK_SET);
        embFile_read(embBuffer, 1, 35, datafile);
        c.r = embBuffer[30];
        c.g = embBuffer[31];
        c.b = embBuffer[32];
        delta = embColor_distance(color, c);

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
    c.color.r = rand() % 256;
    c.color.g = rand() % 256;
    c.color.b = rand() % 256;
    string_copy(c.description, "random");
    string_copy(c.catalogNumber, "NULL");
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
    int out, length, i;
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

const char* threadColorName(EmbColor color, int brand)
{
    int length, i;
    length = double_dereference_int(table_lengths, brand);

    for (i=0; i<length; i++) {
        EmbThread t = load_thread(brand, i);
        if (embColor_equal(t.color, color)) {
            return t.description;
        }
    }

    return "COLOR NOT FOUND";
}

int init_embroidery(void)
{
    datafile = embFile_open("libembroidery_data.bin", "rb", 0);
    memory = embFile_open("libembroidery_memory.bin", "wb+", 0);
    return 0;
}

int close_embroidery(void)
{
    embFile_close(datafile);
    embFile_close(memory);
    return 0;
}

