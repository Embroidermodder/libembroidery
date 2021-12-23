#ifndef LIBEMBROIDERY_HEADER__
#define LIBEMBROIDERY_HEADER__

#ifdef __cplusplus
extern "C" {
#endif

/* MACROS
 * ------
 * This first section is shared between the assembly versions and the
 * portable C version.
 *****************************************************************************/

#define EMB_DEBUG               1

#define EMB_BIT_0            0x01
#define EMB_BIT_1            0x02
#define EMB_BIT_2            0x04
#define EMB_BIT_3            0x08
#define EMB_BIT_4            0x10
#define EMB_BIT_5            0x20
#define EMB_BIT_6            0x40
#define EMB_BIT_7            0x80

/* Machine codes for stitch flags */
#define NORMAL                  0 /* stitch to (x, y) */
#define JUMP                    1 /* move to (x, y) */
#define TRIM                    2 /* trim + move to (x, y) */
#define STOP                    4 /* pause machine for thread change */
#define SEQUIN                  8 /* sequin */
#define END                     16 /* end of program */

/* Format identifiers */
#define EMB_FORMAT_100          0
#define EMB_FORMAT_10O          1
#define EMB_FORMAT_ART          2
#define EMB_FORMAT_BMC          3
#define EMB_FORMAT_BRO          4
#define EMB_FORMAT_CND          5
#define EMB_FORMAT_COL          6
#define EMB_FORMAT_CSD          7
#define EMB_FORMAT_CSV          8
#define EMB_FORMAT_DAT          9
#define EMB_FORMAT_DEM          10
#define EMB_FORMAT_DSB          11
#define EMB_FORMAT_DST          12
#define EMB_FORMAT_DSZ          13
#define EMB_FORMAT_DXF          14
#define EMB_FORMAT_EDR          15
#define EMB_FORMAT_EMD          16
#define EMB_FORMAT_EXP          17
#define EMB_FORMAT_EXY          18
#define EMB_FORMAT_EYS          19
#define EMB_FORMAT_FXY          20
#define EMB_FORMAT_GC           21
#define EMB_FORMAT_GNC          22
#define EMB_FORMAT_GT           23
#define EMB_FORMAT_HUS          24
#define EMB_FORMAT_INB          25
#define EMB_FORMAT_INF          26
#define EMB_FORMAT_JEF          27
#define EMB_FORMAT_KSM          28
#define EMB_FORMAT_MAX          29
#define EMB_FORMAT_MIT          30
#define EMB_FORMAT_NEW          31
#define EMB_FORMAT_OFM          32
#define EMB_FORMAT_PCD          33
#define EMB_FORMAT_PCM          34
#define EMB_FORMAT_PCQ          35
#define EMB_FORMAT_PCS          36
#define EMB_FORMAT_PEC          37
#define EMB_FORMAT_PEL          38
#define EMB_FORMAT_PEM          39
#define EMB_FORMAT_PES          40
#define EMB_FORMAT_PHB          41
#define EMB_FORMAT_PHC          42
#define EMB_FORMAT_PLT          43
#define EMB_FORMAT_RGB          44
#define EMB_FORMAT_SEW          45
#define EMB_FORMAT_SHV          46
#define EMB_FORMAT_SST          47
#define EMB_FORMAT_STX          48
#define EMB_FORMAT_SVG          49
#define EMB_FORMAT_T01          50
#define EMB_FORMAT_T09          51
#define EMB_FORMAT_TAP          52
#define EMB_FORMAT_THR          53
#define EMB_FORMAT_TXT          54
#define EMB_FORMAT_U00          55
#define EMB_FORMAT_U01          56
#define EMB_FORMAT_VIP          57
#define EMB_FORMAT_VP3          58
#define EMB_FORMAT_XXX          59
#define EMB_FORMAT_ZSK          60

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

/* Thread color */
#define Arc_Polyester           0
#define Arc_Rayon               1
#define CoatsAndClark_Rayon     2
#define Exquisite_Polyester     3
#define Fufu_Polyester          4
#define Fufu_Rayon              5
#define Hemingworth_Polyester   6
#define Isacord_Polyester       7
#define Isafil_Rayon            8
#define Marathon_Polyester      9
#define Marathon_Rayon          10
#define Madeira_Polyester       11
#define Madeira_Rayon           12
#define Metro_Polyester         13
#define Pantone                 14
#define RobisonAnton_Polyester  15
#define RobisonAnton_Rayon      16
#define Sigma_Polyester         17
#define Sulky_Rayon             18
#define ThreadArt_Rayon         19
#define ThreadArt_Polyester     20
#define ThreaDelight_Polyester  21
#define Z102_Isacord_Polyester  22
#define SVG_Colors              23
#define hus_thread              24
#define jef_thread              25
#define pcm_thread              26
#define pec_thread              27
#define shv_thread              28
#define dxf_color               29

#define EMB_ARC                 0
#define EMB_CIRCLE              1
#define EMB_ELLIPSE             2
#define EMB_FLAG                3
#define EMB_LINE                4
#define EMB_PATH                5
#define EMB_POINT               6
#define EMB_POLYGON             7
#define EMB_POLYLINE            8 
#define EMB_RECT                9
#define EMB_SPLINE              10
#define EMB_STITCH              11
#define EMB_THREAD              12
#define EMB_VECTOR              13
#define EMB_CHAR                14
#define EMB_ARRAY               15

#define EMBFORMAT_UNSUPPORTED   0
#define EMBFORMAT_STITCHONLY    1
#define EMBFORMAT_OBJECTONLY    2
#define EMBFORMAT_STCHANDOBJ    3 /* binary operation: 1+2=3 */

#define numberOfFormats         61

/* path flag codes */
#define LINETO             0
#define MOVETO             1
#define BULGETOCONTROL     2
#define BULGETOEND         4
#define ELLIPSETORAD       8
#define ELLIPSETOEND      16
#define CUBICTOCONTROL1   32
#define CUBICTOCONTROL2   64
#define CUBICTOEND       128
#define QUADTOCONTROL    256
#define QUADTOEND        512

#define CHUNK_SIZE 128

#define EMBFORMAT_MAXEXT 3  /* maximum length of extension without dot */
#define EMBFORMAT_MAXDESC 50  /* the longest possible description string length */

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

/*
 *  Structure sizes
 *  These can be obtained by calling sizeof in C, but for assembly we need these
 *  to be explicitly calculated.
 *  ---------------------------------------------------------------------------
 *
 *  EmbTime uses 6 unsigned ints, 1 for each of (year, month, day, hour, minute,
 *  second) in that order.
 */
#define EmbTime_size      (6*8)

/*  EmbArray uses 3 of the integers used as pointers for a file_id, size and
 *  and 1 unsigned char for a type.
 */
#define EmbArray_size     (3*8+1)

/* EmbColor uses the light primaries: red, green, blue in that order.
 * unsigned char[3];
 */
#define EmbColor_size      3

/*  The basic type to represent points absolutely or represent directions.
 *
 *  Positive y is up, units are in mm.
 *
 *  EmbVector (float x, y);
 */
#define EmbVector_size     (2*4)

/*  EmbPoint has... */
#define EmbPoint_size      (EmbVector_size + 1 + EmbColor_size)

#ifndef __LIBEMBROIDERY_ASM__

#include <stdio.h>

#if defined(_WIN32) && !defined(WIN32)
#define WIN32
#endif

/* When building a shared library,
* use the proper export keyword depending on the compiler */
#define EMB_PUBLIC
#if defined(LIBEMBROIDERY_SHARED)
    #undef EMB_PUBLIC
    #if defined(__WIN32__) || defined(WIN32)
        #define EMB_PUBLIC __declspec(dllexport)
    #else
        #define EMB_PUBLIC __attribute__ ((visibility("default")))
    #endif
#endif

/* STRUCTS
*****************************************************************************/

typedef struct SvgAttribute_
{
    char* name;
    char* value;
} SvgAttribute;

typedef struct SvgAttributeList_
{
    SvgAttribute attribute;
    struct SvgAttributeList_* next;
} SvgAttributeList;

typedef struct SvgElement_
{
    char* name;
    SvgAttributeList* attributeList;
    SvgAttributeList* lastAttribute;
} SvgElement;

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

/**
 * EmbColor uses the light primaries: red, green, blue in that order.
 */
typedef struct EmbColor_
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} EmbColor;

/**
 * The basic type to represent points absolutely or represent directions.
 *
 * Positive y is up, units are in mm.
 */
typedef struct EmbVector_
{
    double x;
    double y;
} EmbVector;

typedef struct EmbVector_ EmbPoint;
typedef struct EmbArray_ EmbArray;

/**
 * Does it make sense to have lineType for a point?
 */
typedef struct EmbPointObject_
{
    EmbPoint point;
    int lineType;
    EmbColor color;
} EmbPointObject;

/**
 * TODO: convert to EmbVector start, end;
 */
typedef struct EmbLine_
{
    double x1;
    double y1;
    double x2;
    double y2;
} EmbLine;

typedef struct EmbLineObject_
{
    EmbLine line;
    int lineType;
    EmbColor color;
} EmbLineObject;

typedef struct EmbLayer_
{
    EmbColor color;
    const char* name;
} EmbLayer;

typedef struct EmbPathObject_
{
    EmbArray* pointList;
    EmbArray* flagList;
    int lineType;
    EmbColor color;
} EmbPathObject;

typedef struct EmbStitch_
{
    int flags; /* uses codes defined above */
    double x; /* absolute position (not relative) */
    double y; /* positive is up, units are in mm  */
    int color; /* color number for this stitch */
    /* TODO: this should be called colorIndex since it is not an EmbColor */
} EmbStitch;

typedef struct EmbThread_
{
    EmbColor color;
    char description[50];
    char catalogNumber[30];
} EmbThread;

typedef struct EmbHoop_
{
    double width;
    double height;
} EmbHoop;

typedef struct thread_color_ {
    char name[22];
    unsigned int hex_code;
    int manufacturer_code;
} thread_color;

typedef struct EmbTime_
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
} EmbTime;

typedef struct EmbEllipse_
{
    double centerX;
    double centerY;
    double radiusX;
    double radiusY;
} EmbEllipse;

typedef struct EmbArc_
{
    double startX;  /* absolute position (not relative) */
    double startY;
    double midX;    /* absolute position (not relative) */
    double midY;
    double endX;    /* absolute position (not relative) */
    double endY;
} EmbArc;

typedef struct EmbArcObject_
{
    EmbArc arc;
    int lineType;
    EmbColor color;
} EmbArcObject;

typedef struct EmbRect_
{
    double top;
    double left;
    double bottom;
    double right;
} EmbRect;

typedef struct EmbCircle_
{
    double centerX;
    double centerY;
    double radius;
} EmbCircle;

typedef struct EmbCircleObject_
{
    EmbCircle circle;
    int lineType;
    EmbColor color;
    int count;
    int length;
} EmbCircleObject;

typedef struct EmbRectObject_
{
    EmbRect rect;
    double rotation;
    double radius;
    int lineType;
    EmbColor color;
} EmbRectObject;

typedef struct EmbPolygonObject_
{
    EmbArray* pointList;
    int lineType;
    EmbColor color;
} EmbPolygonObject;

typedef struct EmbSatinOutline_
{
    int length;
    EmbArray* side1;
    EmbArray* side2;
} EmbSatinOutline;

typedef struct EmbEllipseObject_
{
    EmbEllipse ellipse;
    double rotation;
    int lineType;
    EmbColor color;
} EmbEllipseObject;

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

typedef struct EmbPolylineObject_
{
    EmbArray* pointList;
    int lineType;
    EmbColor color;
} EmbPolylineObject;

typedef struct EmbSettings_ {
    unsigned int dstJumpsPerTrim;
    EmbPoint home;
} EmbSettings;

typedef struct EmbBezier_ {
    double startX;
    double startY;
    double control1X;
    double control1Y;
    double control2X;
    double control2Y;
    double endX;
    double endY;
} EmbBezier;

typedef struct EmbSplineObject_ {
    EmbBezier bezier;
    struct EmbSplineObject_* next;
    int lineType;
    EmbColor color;
} EmbSplineObject;

typedef struct LSYSTEM {
    char axiom;
    char *alphabet;
    char *constants;
    char **rules;
} L_system;

/**
 * Only one of the pointers is used at a time so this should be a union.
 */
struct EmbArray_ {
    EmbArcObject *arc;
    EmbCircleObject *circle;
    EmbColor *color;
    EmbEllipseObject *ellipse;
    int *flag;
    EmbPathObject **path;
    EmbPointObject *point;
    EmbLineObject *line;
    EmbPolygonObject **polygon;
    EmbPolylineObject **polyline;
    EmbRectObject *rect;
    EmbSplineObject *spline;
    EmbStitch *stitch;
    EmbThread *thread;
    EmbVector *vector;
    int count;
    int length;
    int type;
};

typedef struct EmbPattern_
{
    EmbSettings settings;
    EmbHoop hoop;

    EmbArray* stitchList;
    EmbArray* threads;
    EmbArray* arcs;
    EmbArray* circles;
    EmbArray* ellipses;
    EmbArray* lines;
    EmbArray* paths;
    EmbArray* points;
    EmbArray* polygons;
    EmbArray* polylines;
    EmbArray* rects;
    EmbArray* splines;

    int currentColorIndex;
    double lastX;
    double lastY;
} EmbPattern;

typedef struct EmbFormatList_
{
    char extension[2 + EMBFORMAT_MAXEXT];
    char description[EMBFORMAT_MAXDESC];
    char reader_state;
    char writer_state;
    int type;
    char (*reader)(EmbPattern*, const char*);
    char (*writer)(EmbPattern*, const char*);
} EmbFormatList;

/* Function Declarations
*****************************************************************************/
EMB_PUBLIC double embMinDouble(double, double);
EMB_PUBLIC double embMaxDouble(double, double);

EMB_PUBLIC int lindenmayer_system(L_system L, char* state, int iteration, int complete);
EMB_PUBLIC int hilbert_curve(int iterations);

EMB_PUBLIC int embMinInt(int, int);
EMB_PUBLIC int embMaxInt(int, int);

EMB_PUBLIC int emb_identify_format(const char *ending);

EMB_PUBLIC EmbArray* embArray_create(int type);
EMB_PUBLIC int embArray_resize(EmbArray *g);
EMB_PUBLIC int embArray_addArc(EmbArray* g, EmbArc arc, int lineType, EmbColor color);
EMB_PUBLIC int embArray_addCircle(EmbArray* g, EmbCircle circle, int lineType, EmbColor color);
EMB_PUBLIC int embArray_addEllipse(EmbArray* g, EmbEllipse circle, double rotation, int lineType, EmbColor color);
EMB_PUBLIC int embArray_addFlag(EmbArray* g, int flag);
EMB_PUBLIC int embArray_addLine(EmbArray* g, EmbLineObject line);
EMB_PUBLIC int embArray_addRect(EmbArray* g, EmbRect rect, int lineType, EmbColor color);
EMB_PUBLIC int embArray_addPath(EmbArray* g, EmbPathObject *p);
EMB_PUBLIC int embArray_addPoint(EmbArray* g, EmbPointObject *p);
EMB_PUBLIC int embArray_addPolygon(EmbArray* g, EmbPolygonObject *p);
EMB_PUBLIC int embArray_addPolyline(EmbArray* g, EmbPolylineObject *p);
EMB_PUBLIC int embArray_addSpline(EmbArray* g, EmbSplineObject *p);
EMB_PUBLIC int embArray_addStitch(EmbArray* g, EmbStitch st);
EMB_PUBLIC int embArray_addThread(EmbArray* g, EmbThread p);
EMB_PUBLIC int embArray_addVector(EmbArray* g, EmbVector);
EMB_PUBLIC void embArray_free(EmbArray* p);

EMB_PUBLIC EmbLine embLine_make(double x1, double y1, double x2, double y2);

EMB_PUBLIC void embLine_normalVector(EmbLine line, EmbVector* result, int clockwise);
EMB_PUBLIC unsigned char embLine_intersectionPoint(EmbLine line1, EmbLine line2, EmbVector* result);

EMB_PUBLIC EmbPathObject* embPathObject_create(
    EmbArray* pointList, EmbArray* flagList, EmbColor color, int lineType);
EMB_PUBLIC void embPathObject_free(EmbPathObject* pointer);

EMB_PUBLIC int embThread_findNearestColor(EmbColor color, EmbArray* colors, int mode);
EMB_PUBLIC int embThread_findNearestColor_fromThread(EmbColor color, EmbThread* colors, int length);
EMB_PUBLIC EmbThread embThread_getRandom(void);

EMB_PUBLIC void embVector_normalize(EmbVector vector, EmbVector* result);
EMB_PUBLIC void embVector_multiply(EmbVector vector, double magnitude, EmbVector* result);
EMB_PUBLIC void embVector_add(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC void embVector_average(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC void embVector_subtract(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC double embVector_dot(EmbVector v1, EmbVector v2);
EMB_PUBLIC void embVector_transpose_product(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC double embVector_getLength(EmbVector vector);

EMB_PUBLIC void testMain(int level);
EMB_PUBLIC int convert(const char *inf, const char *outf);

char binaryReadByte(FILE* file);
int binaryReadBytes(FILE* file, unsigned char* destination, int count);
float binaryReadFloat(FILE* file);
void binaryReadString(FILE* file, char *buffer, int maxLength);
void binaryReadUnicodeString(FILE* file, char *buffer, const int stringLength);

void binaryWriteByte(FILE* file, unsigned char data);
void binaryWriteBytes(FILE* file, const char* data, int size);
void binaryWriteShort(FILE* file, short data);
void binaryWriteShortBE(FILE* file, short data);
void binaryWriteUShort(FILE* file, unsigned short data);
void binaryWriteUShortBE(FILE* file, unsigned short data);
void binaryWriteInt(FILE* file, int data);
void binaryWriteIntBE(FILE* file, int data);
void binaryWriteUInt(FILE* file, unsigned int data);
void binaryWriteUIntBE(FILE* file, unsigned int data);
void binaryWriteFloat(FILE* file, float data);

extern void charReplace(char *s, const char *from, const char *to);
extern int stringInArray(const char *s, const char **array);

int roundDouble(double src);
char startsWith(const char* pre, const char* str);

void fpad(FILE *f, char c, int n);
char* rTrim(char* const str, char junk);
char* lTrim(char* const str, char junk);
char *copy_trim(char const *s);
void inplace_trim(char *s);
char* emb_optOut(double num, char* str);
char* emb_strdup(const char* src);

int hus_compress(char* input, int size, char* output, int *out_size);
int hus_decompress(char* input, int size, char* output, int *out_size);

EMB_PUBLIC EmbArcObject embArcObject_make(double sx, double sy, double mx, double my, double ex, double ey);
EMB_PUBLIC EmbArcObject* embArcObject_create(double sx, double sy, double mx, double my, double ex, double ey);

char isArcClockwise(EmbArc arc);
void getArcCenter(EmbArc arc, EmbVector *arcCenter);
char getArcDataFromBulge(double bulge,
                         double arcStartX,          double arcStartY,
                         double arcEndX,            double arcEndY,
                         /* returned data */
                         double* arcMidX,           double* arcMidY,
                         double* arcCenterX,        double* arcCenterY,
                         double* radius,            double* diameter,
                         double* chord,
                         double* chordMidX,         double* chordMidY,
                         double* sagitta,           double* apothem,
                         double* incAngleInDegrees, char*   clockwise);

EMB_PUBLIC int getCircleCircleIntersections(
      EmbCircle c0, EmbCircle c1,
      /* Intersection Point */
      double* px3, double* py3,
      /* Intersection Point */
      double* px4, double* py4);
EMB_PUBLIC int getCircleTangentPoints(
     EmbCircle c,
     /* Point to determine tangency */
     double  px,  double  py,
     /* Tangent Point 0 */
     double* tx0, double* ty0,
     /* Tangent Point 1 */
     double* tx1, double* ty1);

EMB_PUBLIC EmbColor embColor_make(unsigned char r, unsigned char g, unsigned char b);
EMB_PUBLIC EmbColor* embColor_create(unsigned char r, unsigned char g, unsigned char b);
EMB_PUBLIC EmbColor embColor_fromHexStr(char* val);
EMB_PUBLIC int embColor_distance(EmbColor a, EmbColor b);
void embColor_read(FILE *file, EmbColor *c, int toRead);
void embColor_write(FILE *file, EmbColor c, int toWrite);

EMB_PUBLIC double embEllipse_diameterX(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_diameterY(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_width(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_height(EmbEllipse ellipse);

EMB_PUBLIC EmbEllipseObject embEllipseObject_make(double cx, double cy, double rx, double ry);

int validateWritePattern(EmbPattern* pattern, const char* fileName, const char *function);
int validateReadPattern(EmbPattern* pattern, const char* fileName, const char *function);

EMB_PUBLIC short fread_int16(FILE* f);
EMB_PUBLIC unsigned short fread_uint16(FILE* f);
EMB_PUBLIC int fread_int32(FILE* f);
EMB_PUBLIC unsigned int fread_uint32(FILE* f);
EMB_PUBLIC short fread_int16_be(FILE* f);
EMB_PUBLIC unsigned short fread_uint16_be(FILE* f);
EMB_PUBLIC int fread_int32_be(FILE* f);
EMB_PUBLIC unsigned int fread_uint32_be(FILE* f);
EMB_PUBLIC void fwrite_nbytes(FILE* f, void *p, int bytes);
EMB_PUBLIC void fwrite_nbytes_be(FILE* f, void *p, int bytes);

bcf_file_difat* bcf_difat_create(FILE* file, unsigned int fatSectors, const unsigned int sectorSize);
unsigned int readFullSector(FILE* file, bcf_file_difat* bcfFile, unsigned int* numberOfDifatEntriesStillToRead);
unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat);
void bcf_file_difat_free(bcf_file_difat* difat);

bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize);
void loadFatFromSector(bcf_file_fat* fat, FILE* file);
void bcf_file_fat_free(bcf_file_fat** fat);

bcf_directory_entry* CompoundFileDirectoryEntry(FILE* file);
bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries);
void readNextSector(FILE* file, bcf_directory* dir);
void bcf_directory_free(bcf_directory** dir);

bcf_file_header bcfFileHeader_read(FILE* file);
int bcfFileHeader_isValid(bcf_file_header header);

int bcfFile_read(FILE* file, bcf_file* bcfFile);
FILE* GetFile(bcf_file* bcfFile, FILE* file, char* fileToFind);
void bcf_file_free(bcf_file* bcfFile);

int threadColor(const char*, int brand);
int threadColorNum(unsigned int color, int brand);
const char* threadColorName(unsigned int color, int brand);

EMB_PUBLIC void embTime_initNow(EmbTime* t);
EMB_PUBLIC EmbTime embTime_time(EmbTime* t);

EMB_PUBLIC EmbPoint embPoint_make(double x, double y);

EMB_PUBLIC EmbPointObject embPointObject_make(double x, double y);
EMB_PUBLIC EmbPointObject* embPointObject_create(double x, double y);

EMB_PUBLIC EmbSettings embSettings_init(void);

EMB_PUBLIC EmbPoint embSettings_home(EmbSettings* settings);
EMB_PUBLIC void embSettings_setHome(EmbSettings* settings, EmbPoint point);

EMB_PUBLIC EmbPolygonObject* embPolygonObject_create(
    EmbArray* pointList, EmbColor color, int lineType);
EMB_PUBLIC void embPolygonObject_free(EmbPolygonObject* pointer);
EMB_PUBLIC EmbPolylineObject* embPolylineObject_create(
    EmbArray* pointList, EmbColor color, int lineType);
EMB_PUBLIC void embPolylineObject_free(EmbPolylineObject* pointer);

EMB_PUBLIC void embSatinOutline_generateSatinOutline(EmbArray* lines, double thickness, EmbSatinOutline* result);
EMB_PUBLIC EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, double density);

EMB_PUBLIC double embRect_x(EmbRect rect);
EMB_PUBLIC double embRect_y(EmbRect rect);
EMB_PUBLIC double embRect_width(EmbRect rect);
EMB_PUBLIC double embRect_height(EmbRect rect);

EMB_PUBLIC void embRect_setX(EmbRect* rect, double x);
EMB_PUBLIC void embRect_setY(EmbRect* rect, double y);
EMB_PUBLIC void embRect_setWidth(EmbRect* rect, double w);
EMB_PUBLIC void embRect_setHeight(EmbRect* rect, double h);

EMB_PUBLIC void embRect_setCoords(EmbRect* rect, double x1, double y1, double x2, double y2);
EMB_PUBLIC void embRect_setRect(EmbRect* rect, double x, double y, double w, double h);

EMB_PUBLIC EmbRectObject embRectObject_make(double x, double y, double w, double h);

EMB_PUBLIC EmbPattern* embPattern_create(void);
EMB_PUBLIC void embPattern_hideStitchesOverLength(EmbPattern* p, int length);
EMB_PUBLIC void embPattern_fixColorCount(EmbPattern* p);
EMB_PUBLIC int embPattern_addThread(EmbPattern* p, EmbThread thread);
EMB_PUBLIC void embPattern_addStitchAbs(EmbPattern* p, double x, double y, int flags, int isAutoColorIndex);
EMB_PUBLIC void embPattern_addStitchRel(EmbPattern* p, double dx, double dy, int flags, int isAutoColorIndex);
EMB_PUBLIC void embPattern_changeColor(EmbPattern* p, int index);
EMB_PUBLIC void embPattern_free(EmbPattern* p);
EMB_PUBLIC void embPattern_scale(EmbPattern* p, double scale);
EMB_PUBLIC EmbRect embPattern_calcBoundingBox(EmbPattern* p);
EMB_PUBLIC void embPattern_flipHorizontal(EmbPattern* p);
EMB_PUBLIC void embPattern_flipVertical(EmbPattern* p);
EMB_PUBLIC void embPattern_flip(EmbPattern* p, int horz, int vert);
EMB_PUBLIC void embPattern_combineJumpStitches(EmbPattern* p);
EMB_PUBLIC void embPattern_correctForMaxStitchLength(EmbPattern* p, double maxStitchLength, double maxJumpLength);
EMB_PUBLIC void embPattern_center(EmbPattern* p);
EMB_PUBLIC void embPattern_loadExternalColorFile(EmbPattern* p, const char* fileName);
EMB_PUBLIC void embPattern_end(EmbPattern* p);

EMB_PUBLIC void embPattern_addCircleObjectAbs(EmbPattern* p, double cx, double cy, double r);
EMB_PUBLIC void embPattern_addEllipseObjectAbs(EmbPattern* p, double cx, double cy, double rx, double ry); /* TODO: ellipse rotation */
EMB_PUBLIC void embPattern_addLineObjectAbs(EmbPattern* p, double x1, double y1, double x2, double y2);
EMB_PUBLIC void embPattern_addPathObjectAbs(EmbPattern* p, EmbPathObject* obj);
EMB_PUBLIC void embPattern_addPointObjectAbs(EmbPattern* p, double x, double y);
EMB_PUBLIC void embPattern_addPolygonObjectAbs(EmbPattern* p, EmbPolygonObject* obj);
EMB_PUBLIC void embPattern_addPolylineObjectAbs(EmbPattern* p, EmbPolylineObject* obj);
EMB_PUBLIC void embPattern_addRectObjectAbs(EmbPattern* p, double x, double y, double w, double h);

EMB_PUBLIC void embPattern_copyStitchListToPolylines(EmbPattern* pattern);
EMB_PUBLIC void embPattern_copyPolylinesToStitchList(EmbPattern* pattern);
EMB_PUBLIC void embPattern_moveStitchListToPolylines(EmbPattern* pattern);
EMB_PUBLIC void embPattern_movePolylinesToStitchList(EmbPattern* pattern);

EMB_PUBLIC int embPattern_read(EmbPattern* pattern, const char* fileName);
EMB_PUBLIC int embPattern_write(EmbPattern* pattern, const char* fileName);

EMB_PUBLIC char read100(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char write100(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char read10o(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char write10o(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readArt(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeArt(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readBmc(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeBmc(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readBro(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeBro(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readCnd(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeCnd(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readCol(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeCol(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readCsd(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeCsd(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readCsv(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeCsv(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readDat(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeDat(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readDem(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeDem(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readDsb(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeDsb(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readDst(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeDst(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readDsz(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeDsz(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readDxf(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeDxf(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readEdr(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeEdr(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readEmd(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeEmd(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readExp(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeExp(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readExy(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeExy(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readEys(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeEys(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readFxy(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeFxy(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readGc(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeGc(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readGnc(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeGnc(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readGt(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeGt(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readHus(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeHus(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readInb(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeInb(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readInf(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeInf(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readJef(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeJef(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readKsm(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeKsm(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readMax(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeMax(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readMit(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeMit(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readNew(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeNew(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readOfm(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeOfm(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readPcd(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writePcd(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readPcm(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writePcm(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readPcq(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writePcq(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readPcs(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writePcs(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readPec(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writePec(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readPel(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writePel(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readPem(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writePem(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readPes(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writePes(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readPhb(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writePhb(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readPhc(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writePhc(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readPlt(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writePlt(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readRgb(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeRgb(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readSew(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeSew(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readShv(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeShv(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readSst(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeSst(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readStx(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeStx(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readSvg(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeSvg(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readT01(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeT01(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readT09(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeT09(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readTap(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeTap(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readThr(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeThr(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readTxt(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeTxt(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readU00(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeU00(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readU01(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeU01(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readVip(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeVip(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readVp3(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeVp3(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readXxx(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeXxx(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char readZsk(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char writeZsk(EmbPattern *pattern, const char* fileName);

void readPecStitches(EmbPattern* pattern, FILE* file);
void writePecStitches(EmbPattern* pattern, FILE* file, const char* filename);

/* NON-MACRO CONSTANTS
 ******************************************************************************/

/*! Constant representing the number of Double Indirect FAT entries in a single header */
EMB_PUBLIC extern EmbFormatList formatTable[];
extern const unsigned int NumberOfDifatEntriesInHeader;
extern const int pecThreadCount;
extern const EmbThread pecThreads[];
extern const char imageWithFrame[38][48];
extern const EmbThread jefThreads[];
extern const int shvThreadCount;
extern const EmbThread shvThreads[];
extern const double embConstantPi;

int emb_readline(FILE* file, char *line, int maxLength);

int encode_tajima_ternary(unsigned char b[3], int x, int y);
void decode_tajima_ternary(unsigned char b[3], int *x, int *y);
void encode_t01_record(unsigned char b[3], int x, int y, int flags);
int decode_t01_record(unsigned char b[3], int *x, int *y, int *flags);

#else

/*
 * Flag Defines
 * ------------
 * These mirror the first table in libembroidery_data.asm.
 */
#define svg_property_token_table   0*4
#define svg_attribute_token_table  1*4
#define svg_token_lists            2*4
#define brand_codes                3*4
#define image_frame                4*4
#define csv_header                 5*4
#define max_header                 6*4
#define csd_decoding_table         7*4
#define vip_decoding_table         8*4
#define format_list                9*4
#define svg_token_table            10*4
#define inkscape_token_table       11*4
#define svg_element_token_table    12*4
#define svg_media_property_token_table    13*4
#define stitch_labels              14*4
#define dxf_version_r              15*4
#define table_lengths              16*4

#define error_emb_sqrt             17
#define error_emb_atan2            18
#define error_hus_expand           19
#define error_hus_compress         20
#define error_arc_data             21
#define error_format_not_supported 22
#define error_line_intersection    23
#define error_line_parallel        24
#define error_normalize            25
#define error_pattern_no_stitches  26
#define error_pattern_open_file    27
#define error_vector_add           28
#define error_vector_average       29
#define error_vector_component_product    30
#define error_vector_multiply      31
#define error_vector_normal        32
#define error_vector_subtract      33
#define error_hide_stitches_no_pattern    35
#define error_fix_color_count_no_pattern    36
#define error_copy_stitch_list_no_pattern    37
#define error_copy_polylines_no_point_list    38
#define error_move_stitch_list_no_pattern    39
#define error_add_stitch_abs_no_pattern    40
#define error_add_stitch_abs_multiple_end    41
#define error_add_stitch_rel_no_pattern    42
#define error_change_color_no_pattern    43
#define error_pattern_read_unsupported    44
#define error_pattern_write_unsupported    45
#define error_pattern_scale    46
#define error_bounding_box_no_pattern    47
#define error_flip_horizontal_no_pattern    48
#define error_flip_vertical_no_pattern    49
#define error_flip_no_pattern    50
#define error_combine_jump_stitches    51
#define error_pattern_max_stitch_length    52
#define error_pattern_center    53
#define error_add_circle    54
#define error_add_ellipse    55
#define error_add_line    56
#define error_add_path    57
#define error_add_path_obj    58
#define error_add_path_obj_empty    59
#define error_add_point    60
#define error_add_polygon_abs    61
#define error_add_polygon_abs_obj    62
#define error_add_polygon_abs_empty    63
#define error_add_polyline_abs    64
#define error_add_polyline_abs_obj    65
#define error_add_polyline_abs_empty    66
#define error_add_rect    67
#define error_generate_satin_array_create    68
#define error_generate_satin_result_memory    69
#define error_render_stitches_result_memory    70
#define error_read_no_pattern    71
#define error_read_no_filename    72
#define error_read_cannot_open    73
#define error_cannot_open    74
#define error_bcf_difat_sector_value    76
#define error_read_sector_value    77
#define error_bcf_fat_create    78
#define error_col_empty_line    79
#define error_compound_unexpected_object_type    82
#define error_csv_string    83
#define error_format_get_extension    84
#define error_no_colors 85
#define error_read_dxf  86
#define error_unsupported   87
#define error_hus_decompress_data 88
#define error_hus_compress_data   89
#define error_read_hus  90
#define error_write_hus 91
#define error_jef_hoop_no_pattern 92
#define error_max_encode_no_file  93
#define error_ofm_threads_library_name   94
#define error_ofm_threads_color_name  95
#define error_stx_thread_no_thread    97
#define error_stx_thread_no_file  98
#define error_encode_dst_x_out_of_range  102
#define error_encode_dst_y_out_of_range  103
#define error_encode_tap_x  104
#define error_encode_tap_y  105
#define error_vp3_read_string_file    113
#define error_vp3_read_hoop_no_file   115
#define error_number_of_colors 116
#define error_check_color_byte_1  117
#define error_check_color_byte_2  118
#define error_check_color_byte_3  119
#define error_format_vp3_cannot_read  120
#define error_svg_add_attribute_no_element  121
#define error_svg_create_element_null 125
#define error_svg_get_value_no_element   126
#define error_svg_get_value_no_name    127
#define error_svg_add_no_pattern    128
#define error_svg_add_invalid_path    130
#define error_svg_add_realloc 131
#define error_read_svg        133
#define error_write_csv_0     134
#define error_read_csv_0      135
#define error_read_csv_1      136
#define error_read_csv_2      137

#define brand_codes_length    24
#define thread_type_length    35
#define thread_color_offset   30
#define thread_code           33

#define CSV_EXPECT_NULL       0
#define CSV_EXPECT_QUOTE1     1
#define CSV_EXPECT_QUOTE2     2
#define CSV_EXPECT_COMMA      3

#define CSV_MODE_NULL         0
#define CSV_MODE_COMMENT      '#'
#define CSV_MODE_VARIABLE     '>'
#define CSV_MODE_THREAD       '$'
#define CSV_MODE_STITCH       '*'

/* DXF Version Identifiers */
#define DXF_VERSION_R10       0
#define DXF_VERSION_R11       1
#define DXF_VERSION_R12       2
#define DXF_VERSION_R13       3
#define DXF_VERSION_R14       4
#define DXF_VERSION_R15       5
#define DXF_VERSION_R18       6
#define DXF_VERSION_R21       7
#define DXF_VERSION_R24       8
#define DXF_VERSION_R27       9

#define DXF_VERSION_2000      0
#define DXF_VERSION_2002      1
#define DXF_VERSION_2004      2
#define DXF_VERSION_2006      3
#define DXF_VERSION_2007      4
#define DXF_VERSION_2009      5
#define DXF_VERSION_2010      6
#define DXF_VERSION_2013      7

#define MAX_LAYERS            16
#define MAX_LAYER_NAME_LENGTH 30

#define HOOP_126X110          0
#define HOOP_110X110          1
#define HOOP_50X50            2
#define HOOP_140X200          3
#define HOOP_230X200          4

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBEMBROIDERY_HEADER__ */

