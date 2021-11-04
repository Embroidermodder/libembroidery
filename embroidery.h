#ifndef LIBEMBROIDERY_HEADER__
#define LIBEMBROIDERY_HEADER__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MACROS
*****************************************************************************/

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

/* STRUCTS
*****************************************************************************/

typedef enum
{
    SVG_CREATOR_NULL,
    SVG_CREATOR_EMBROIDERMODDER,
    SVG_CREATOR_ILLUSTRATOR,
    SVG_CREATOR_INKSCAPE
} SVG_CREATOR;

typedef enum
{
    SVG_EXPECT_NULL,
    SVG_EXPECT_ELEMENT,
    SVG_EXPECT_ATTRIBUTE,
    SVG_EXPECT_VALUE
} SVG_EXPECT;

typedef enum
{
    SVG_NULL,
    SVG_ELEMENT,
    SVG_PROPERTY,
    SVG_MEDIA_PROPERTY,
    SVG_ATTRIBUTE,
    SVG_CATCH_ALL
} SVG_TYPES;

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

typedef struct EmbFile_
{
    FILE* file;
} EmbFile;

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
    int color; /* color number for this stitch */ /* TODO: this should be called colorIndex since it is not an EmbColor */
} EmbStitch;

typedef struct EmbStitchList_
{
    struct EmbStitch_ stitch;
    struct EmbStitchList_* next;
} EmbStitchList;

typedef struct EmbThread_
{
    EmbColor color;
    const char* description;
    const char* catalogNumber;
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
    EmbStitchList* stitchList;

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

    EmbStitchList* lastStitch;

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

EMB_PUBLIC int lindenmayer_system(L_system L, char* state, int iteration);
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
EMB_PUBLIC int embArray_addStitch(EmbArray* g, double x, double y, int, int);
EMB_PUBLIC int embArray_addThread(EmbArray* g, EmbThread p);
EMB_PUBLIC int embArray_addVector(EmbArray* g, EmbVector);
EMB_PUBLIC void embArray_free(EmbArray* p);

EMB_PUBLIC EmbLine embLine_make(double x1, double y1, double x2, double y2);

EMB_PUBLIC void embLine_normalVector(EmbLine line, EmbVector* result, int clockwise);
EMB_PUBLIC unsigned char embLine_intersectionPoint(EmbLine line1, EmbLine line2, EmbVector* result);

EMB_PUBLIC EmbPathObject* embPathObject_create(
    EmbArray* pointList, EmbArray* flagList, EmbColor color, int lineType);
EMB_PUBLIC void embPathObject_free(EmbPathObject* pointer);

EMB_PUBLIC EmbStitchList* embStitchList_create(EmbStitch data);
EMB_PUBLIC EmbStitchList* embStitchList_add(EmbStitchList* pointer, EmbStitch data);
EMB_PUBLIC int embStitchList_count(EmbStitchList* pointer);
EMB_PUBLIC int embStitchList_empty(EmbStitchList* pointer);
EMB_PUBLIC void embStitchList_free(EmbStitchList* pointer);
EMB_PUBLIC EmbStitch embStitchList_getAt(EmbStitchList* pointer, int num);

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

char binaryReadByte(EmbFile* file);
int binaryReadBytes(EmbFile* file, unsigned char* destination, int count);
short binaryReadInt16(EmbFile* file);
int binaryReadInt32(EmbFile* file);
unsigned char binaryReadUInt8(EmbFile* file);
unsigned short binaryReadUInt16(EmbFile* file);
unsigned int binaryReadUInt32(EmbFile* file);
short binaryReadInt16BE(EmbFile* file); /* Big endian version */
unsigned short binaryReadUInt16BE(EmbFile* file); /* Big endian version */
int binaryReadInt32BE(EmbFile* file);   /* Big endian version */
unsigned int binaryReadUInt32BE(EmbFile* file);
float binaryReadFloat(EmbFile* file);
void binaryReadString(EmbFile* file, char *buffer, int maxLength);
void binaryReadUnicodeString(EmbFile* file, char *buffer, const int stringLength);

void binaryWriteByte(EmbFile* file, unsigned char data);
void binaryWriteBytes(EmbFile* file, const char* data, int size);
void binaryWriteShort(EmbFile* file, short data);
void binaryWriteShortBE(EmbFile* file, short data);
void binaryWriteUShort(EmbFile* file, unsigned short data);
void binaryWriteUShortBE(EmbFile* file, unsigned short data);
void binaryWriteInt(EmbFile* file, int data);
void binaryWriteIntBE(EmbFile* file, int data);
void binaryWriteUInt(EmbFile* file, unsigned int data);
void binaryWriteUIntBE(EmbFile* file, unsigned int data);
void binaryWriteFloat(EmbFile* file, float data);

extern void charReplace(char *s, const char *from, const char *to);
extern int stringInArray(const char *s, const char **array);

int roundDouble(double src);
char startsWith(const char* pre, const char* str);

char* rTrim(char* const str, char junk);
char* lTrim(char* const str, char junk);
char *copy_trim(char const *s);
void inplace_trim(char *s);
char* emb_optOut(double num, char* str);
char* emb_strdup(const char* src);

void husExpand(unsigned char* input, unsigned char* output, int compressedSize, int _269);
int husCompress(unsigned char* _266, unsigned long _inputSize, unsigned char* _267, int _269, int _235);

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

EMB_PUBLIC double embEllipse_diameterX(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_diameterY(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_width(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_height(EmbEllipse ellipse);

EMB_PUBLIC EmbEllipseObject embEllipseObject_make(double cx, double cy, double rx, double ry);

int validateWritePattern(EmbPattern* pattern, const char* fileName, const char *function);
int validateReadPattern(EmbPattern* pattern, const char* fileName, const char *function);

EMB_PUBLIC EmbFile* embFile_open(const char* fileName, const char* mode, int optional);
EMB_PUBLIC void embFile_readline(EmbFile* stream, char *, int);
EMB_PUBLIC int embFile_close(EmbFile* stream);
EMB_PUBLIC int embFile_eof(EmbFile* stream);
EMB_PUBLIC char embFile_getc(EmbFile* stream);
EMB_PUBLIC size_t embFile_read(void* ptr, size_t size, size_t nmemb, EmbFile* stream);
EMB_PUBLIC size_t embFile_write(const void* ptr, size_t size, size_t nmemb, EmbFile* stream);
EMB_PUBLIC int embFile_seek(EmbFile* stream, long offset, int origin);
EMB_PUBLIC long embFile_tell(EmbFile* stream);
EMB_PUBLIC EmbFile* embFile_tmpfile(void);
EMB_PUBLIC int embFile_putc(int ch, EmbFile* stream);

EMB_PUBLIC int embFile_printf(EmbFile* stream, const char* format, ...);

bcf_file_difat* bcf_difat_create(EmbFile* file, unsigned int fatSectors, const unsigned int sectorSize);
unsigned int readFullSector(EmbFile* file, bcf_file_difat* bcfFile, unsigned int* numberOfDifatEntriesStillToRead);
unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat);
void bcf_file_difat_free(bcf_file_difat* difat);

bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize);
void loadFatFromSector(bcf_file_fat* fat, EmbFile* file);
void bcf_file_fat_free(bcf_file_fat* fat);

bcf_directory_entry* CompoundFileDirectoryEntry(EmbFile* file);
bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries);
void readNextSector(EmbFile* file, bcf_directory* dir);
void bcf_directory_free(bcf_directory* dir);

bcf_file_header bcfFileHeader_read(EmbFile* file);
int bcfFileHeader_isValid(bcf_file_header header);

int bcfFile_read(EmbFile* file, bcf_file* bcfFile);
EmbFile* GetFile(bcf_file* bcfFile, EmbFile* file, char* fileToFind);
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

void readPecStitches(EmbPattern* pattern, EmbFile* file);
void writePecStitches(EmbPattern* pattern, EmbFile* file, const char* filename);

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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBEMBROIDERY_HEADER__ */

#if 0

THE NEW VERSION, delete parts that match

typedef struct EmbArray_ {
    int file_id;
    long size;
    long length;
    int type;
} EmbArray;

typedef struct EmbPoint_ {
    EmbVector position;
    int lineType;
    EmbColor color;
} EmbPoint;

typedef struct EmbLine_
{
    EmbVector start;
    EmbVector end;
    int lineType;
    EmbColor color;
} EmbLine;

typedef struct EmbLayer_
{
    EmbColor color;
    const char name[50];
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
    char flags; /* uses codes defined above */
    float x; /* absolute position (not relative) */
    float y; /* positive is up, units are in mm  */
    unsigned char color; /* color number for this stitch */ /* TODO: this should be called colorIndex since it is not an EmbColor */
} EmbStitch;

typedef struct EmbThread_
{
    EmbColor color;
    char description[30];
    char catalogNumber[10];
} EmbThread;

typedef struct EmbHoop_
{
    float width;
    float height;
} EmbHoop;

typedef struct EmbEllipse_
{
    EmbVector center;
    EmbVector radius;
    float rotation;
    int lineType;
    EmbColor color;
} EmbEllipse;

typedef struct EmbArc_
{
    EmbVector start;  /* absolute position (not relative) */
    EmbVector mid;    /* absolute position (not relative) */
    EmbVector end;    /* absolute position (not relative) */
    int lineType;
    EmbColor color;
} EmbArc;

typedef struct EmbRect_
{
    float top;
    float left;
    float bottom;
    float right;
    int lineType;
    EmbColor color;
} EmbRect;

typedef struct EmbCircle_
{
    EmbVector center;
    float radius;
    int lineType;
    EmbColor color;
} EmbCircle;

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

typedef struct EmbPolylineObject_
{
    EmbArray* pointList;
    int lineType;
    EmbColor color;
} EmbPolylineObject;

typedef struct EmbBezier_ {
    EmbVector start;
    EmbVector control1;
    EmbVector control2;
    EmbVector end;
} EmbBezier;

typedef struct EmbSplineObject_ {
    EmbBezier bezier;
    struct EmbSplineObject_* next;
    int lineType;
    EmbColor color;
} EmbSplineObject;

typedef struct EmbPointObject_ {
    float x;
    float y;
    int lineType;
    EmbColor color;
} EmbPointObject;

typedef struct EmbPattern_
{
    EmbHoop hoop;

    EmbArray* stitchList;
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
    EmbArray* threads;

    unsigned int dstJumpsPerTrim;
    EmbVector home;

    int ax;
    int ay;
    int mx;
    int my;
    char name[17];
    char pd[16];

    int currentColorIndex;
    EmbVector lastPosition;
} EmbPattern;

typedef struct EmbFormatList_
{
    char extension[7];
    char description[51];
    char reader;
    char writer;
    int type;
} EmbFormatList;

/* Function Declarations
*****************************************************************************/
EMB_PUBLIC int init_embroidery(void);
EMB_PUBLIC int close_embroidery(void);

EMB_PUBLIC EmbArray* embArray_create(int type);
EMB_PUBLIC int embArray_add(EmbArray *p, void *data);
EMB_PUBLIC int embArray_get(EmbArray *p, void *data, int i);
EMB_PUBLIC int embArray_set(EmbArray *p, void *data, int i);
EMB_PUBLIC void embArray_free(EmbArray* p);

EMB_PUBLIC void embLine_normalVector(EmbLine line, EmbVector* result, int clockwise);
EMB_PUBLIC unsigned char embLine_intersectionPoint(EmbLine line1, EmbLine line2, EmbVector* result);

EMB_PUBLIC void embVector_normalize(EmbVector vector, EmbVector* result);
EMB_PUBLIC void embVector_multiply(EmbVector vector, float magnitude, EmbVector* result);
EMB_PUBLIC void embVector_add(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC void embVector_average(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC void embVector_subtract(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC float embVector_distance(EmbVector v1, EmbVector v2);
EMB_PUBLIC float embVector_dot(EmbVector v1, EmbVector v2);
EMB_PUBLIC float embVector_cross(EmbVector a, EmbVector b);
EMB_PUBLIC void embVector_normalVector(EmbVector a, EmbVector *b, int clockwise);
EMB_PUBLIC void embVector_component_product(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC float embVector_getLength(EmbVector vector);

EMB_PUBLIC char isArcClockwise(EmbArc arc);
EMB_PUBLIC void getArcCenter(EmbArc arc, EmbVector *arcCenter);
EMB_PUBLIC char getArcDataFromBulge(float bulge, EmbArc* arc, EmbVector* arcCenter,
    float* radius, float* diameter, float* chord, EmbVector* chordMid,
    float* sagitta, float* apothem, float* incAngleInDegrees, char* clockwise);

EMB_PUBLIC int getCircleCircleIntersections(EmbCircle c0, EmbCircle c1, EmbVector* p3, EmbVector* p4);
EMB_PUBLIC int getCircleTangentPoints(EmbCircle c, EmbVector point, EmbVector* t0, EmbVector* t1);

EMB_PUBLIC int threadColor(EmbColor *c, const char*, int brand);
EMB_PUBLIC int threadColorNum(EmbColor color, int brand);
EMB_PUBLIC void threadColorName(char *result, EmbColor color, int brand);
EMB_PUBLIC int embThread_findNearestColor(EmbColor c, int brand);

EMB_PUBLIC void embSatinOutline_generateSatinOutline(EmbArray* lines, float thickness, EmbSatinOutline* result);
EMB_PUBLIC EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, float density);

EMB_PUBLIC EmbFormatList embFormat_data(int format);
EMB_PUBLIC int embReaderWriter_getByFileName(const char* fileName);

EMB_PUBLIC EmbPattern* embPattern_create(void);
EMB_PUBLIC void embPattern_hideStitchesOverLength(EmbPattern* p, int length);
EMB_PUBLIC void embPattern_fixColorCount(EmbPattern* p);
EMB_PUBLIC int embPattern_addThread(EmbPattern* p, EmbThread thread);
EMB_PUBLIC void embPattern_addStitchAbs(EmbPattern* p, float x, float y, int flags, int isAutoColorIndex);
EMB_PUBLIC void embPattern_addStitchRel(EmbPattern* p, float dx, float dy, int flags, int isAutoColorIndex);
EMB_PUBLIC void embPattern_changeColor(EmbPattern* p, int index);
EMB_PUBLIC void embPattern_free(EmbPattern* p);
EMB_PUBLIC void embPattern_scale(EmbPattern* p, float scale);
EMB_PUBLIC EmbRect embPattern_calcBoundingBox(EmbPattern* p);
EMB_PUBLIC void embPattern_flipHorizontal(EmbPattern* p);
EMB_PUBLIC void embPattern_flipVertical(EmbPattern* p);
EMB_PUBLIC void embPattern_flip(EmbPattern* p, int horz, int vert);
EMB_PUBLIC void embPattern_combineJumpStitches(EmbPattern* p);
EMB_PUBLIC void embPattern_correctForMaxStitchLength(EmbPattern* p, float maxStitchLength, float maxJumpLength);
EMB_PUBLIC void embPattern_center(EmbPattern* p);
EMB_PUBLIC void embPattern_loadExternalColorFile(EmbPattern* p, const char* fileName);
EMB_PUBLIC int embPattern_write(EmbPattern* pattern, const char *function, int);
EMB_PUBLIC int embPattern_read(EmbPattern* pattern, const char *function, int);
EMB_PUBLIC int embPattern_writeAuto(EmbPattern* pattern, const char *function);
EMB_PUBLIC int embPattern_readAuto(EmbPattern* pattern, const char *function);

EMB_PUBLIC void embPattern_addCircleObjectAbs(EmbPattern* p, float cx, float cy, float r, int lineType, EmbColor color);
EMB_PUBLIC void embPattern_addEllipseObjectAbs(EmbPattern* p, float cx, float cy, float rx, float ry, float rotation, int lineType, EmbColor color);
EMB_PUBLIC void embPattern_addLineObjectAbs(EmbPattern* p, float x1, float y1, float x2, float y2, int lineType, EmbColor color);
EMB_PUBLIC void embPattern_addPathObjectAbs(EmbPattern* p, EmbPathObject* obj);
EMB_PUBLIC void embPattern_addPointObjectAbs(EmbPattern* p, float x, float y, int lineType, EmbColor color);
EMB_PUBLIC void embPattern_addPolygonObjectAbs(EmbPattern* p, EmbPolygonObject* obj);
EMB_PUBLIC void embPattern_addPolylineObjectAbs(EmbPattern* p, EmbPolylineObject* obj);
EMB_PUBLIC void embPattern_addRectObjectAbs(EmbPattern* p, float x, float y, float w, float h, int lineType, EmbColor color);

EMB_PUBLIC void embPattern_copyStitchListToPolylines(EmbPattern* pattern);
EMB_PUBLIC void embPattern_copyPolylinesToStitchList(EmbPattern* pattern);
EMB_PUBLIC void embPattern_moveStitchListToPolylines(EmbPattern* pattern);
EMB_PUBLIC void embPattern_movePolylinesToStitchList(EmbPattern* pattern);

#endif

