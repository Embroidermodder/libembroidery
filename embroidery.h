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

#ifdef ARDUINO
typedef EmbPattern InoPattern;
typedef struct InoFile_ InoFile;
typedef InoFile EmbFile;

void inoEvent_addStitchAbs(InoPattern* p, float x, float y, int flags, int isAutoColorIndex);

InoFile* inoFile_open(const char* fileName, const char* mode);
int inoFile_close(InoFile* stream);
int inoFile_eof(InoFile* stream);
int inoFile_getc(InoFile* stream);
int inoFile_seek(InoFile* stream, long offset, int origin);
long inoFile_tell(InoFile* stream);
InoFile* inoFile_tmpfile(void);
int inoFile_putc(int ch, InoFile* stream);

int inoFile_printf(InoFile* stream, const char* msg);

void inoLog_serial(const char* msg);
#else
typedef struct EmbFile_
{
    FILE* file;
} EmbFile;
#endif

/* Machine codes for stitch flags */
#define NORMAL                  0 /* stitch to (x, y) */
#define JUMP                    1 /* move to (x, y) */
#define TRIM                    2 /* trim + move to (x, y) */
#define STOP                    4 /* pause machine for thread change */
#define SEQUIN                  8 /* sequin */
#define END                     16 /* end of program */

#define CHUNK_SIZE              128

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

#define EMBFORMAT_UNSUPPORTED   0
#define EMBFORMAT_STITCHONLY    1
#define EMBFORMAT_OBJECTONLY    2
#define EMBFORMAT_STCHANDOBJ    3 /* binary operation: 1+2=3 */


/* STRUCTS
 *****************************************************************************/

typedef struct EmbTime_
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
} EmbTime;

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
    float x;
    float y;
} EmbVector;

typedef struct EmbArray_ EmbArray;

/**
 * Does it make sense to have lineType for a point?
 */
/**
 * The "Object" typedefs are remarkably similar throughout,
 * could we have a single GeometryObject type that mimics the
 * .
 */
typedef struct EmbPointObject_
{
    EmbVector point;
    int lineType;
    EmbColor color;
} EmbPointObject;

/**
 * TODO: documentation.
 */
typedef struct EmbLine_
{
    EmbVector start;
    EmbVector end;
} EmbLine;

/**
 * TODO: documentation.
 */
typedef struct EmbLineObject_
{
    EmbLine line;
    int lineType;
    EmbColor color;
} EmbLineObject;

/**
 * Is this used anywhere?
 */
typedef struct EmbLayer_
{
    EmbColor color;
    const char* name;
} EmbLayer;

/**
 * 
 */
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
    float x; /* absolute position (not relative) */
    float y; /* positive is up, units are in mm  */
    int color; /* color number for this stitch */ /* TODO: this should be called colorIndex since it is not an EmbColor */
} EmbStitch;

/**
 * Improving the size of the stored data for embedded systems.
 * 
 * Store thread colors as:
 *     "\xFF\xFF\xFF" "1001" "Pure White"
 *
 * Since the color is always three characters, it doesn't need to be
 * stored with a spacing character. No manufacturer code takes more than
 * 4 chars in the current set, so we can pad them all to 4 char.
 *
 * Then zero termination sorts out the variable length of the string.
 *
 * That means that we have a single string for each data.
 *
 * This requires reworking the embThread functions.
 *
 * It also removes the need for either struct.
 */
typedef struct EmbThread_
{
    EmbColor color;
    const char* description;
    const char* catalogNumber;
} EmbThread;

/**
 * TODO: this should be merged with the EmbThread.
 */
typedef struct thread_color_ {
    const char *name;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    short manufacturer_code;
} thread_color;

typedef struct EmbHoop_
{
    float width;
    float height;
} EmbHoop;

typedef struct EmbEllipse_
{
    EmbVector center;
    EmbVector radius;
} EmbEllipse;

typedef struct EmbArc_
{
    EmbVector start;  /* absolute position (not relative) */
    EmbVector mid;    /* absolute position (not relative) */
    EmbVector end;    /* absolute position (not relative) */
} EmbArc;

typedef struct EmbArcObject_
{
    EmbArc arc;
    int lineType;
    EmbColor color;
} EmbArcObject;

typedef struct EmbRect_
{
    float top;
    float left;
    float bottom;
    float right;
} EmbRect;

typedef struct EmbCircle_
{
    EmbVector center;
    float radius;
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
    float rotation;
    float radius;
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
    float rotation;
    int lineType;
    EmbColor color;
} EmbEllipseObject;

typedef struct EmbPolylineObject_
{
    EmbArray* pointList;
    int lineType;
    EmbColor color;
} EmbPolylineObject;

typedef struct EmbSettings_ {
    unsigned int dstJumpsPerTrim;
    EmbVector home;
} EmbSettings;

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
    EmbVector lastPosition;
} EmbPattern;

typedef struct EmbFormatList_
{
    char *extension;
    char *description;
    char reader;
    char writer;
    int type;
} EmbFormatList;

/* Function Declarations
*****************************************************************************/
EMB_PUBLIC EmbArray* embArray_create(int type);
EMB_PUBLIC int embArray_resize(EmbArray *g);
EMB_PUBLIC int embArray_addArc(EmbArray* g, EmbArc arc, int lineType, EmbColor color);
EMB_PUBLIC int embArray_addCircle(EmbArray* g, EmbCircle circle, int lineType, EmbColor color);
EMB_PUBLIC int embArray_addEllipse(EmbArray* g, EmbEllipse circle, float rotation, int lineType, EmbColor color);
EMB_PUBLIC int embArray_addFlag(EmbArray* g, int flag);
EMB_PUBLIC int embArray_addLine(EmbArray* g, EmbLineObject line);
EMB_PUBLIC int embArray_addRect(EmbArray* g, EmbRect rect, int lineType, EmbColor color);
EMB_PUBLIC int embArray_addPath(EmbArray* g, EmbPathObject *p);
EMB_PUBLIC int embArray_addPoint(EmbArray* g, EmbPointObject *p);
EMB_PUBLIC int embArray_addPolygon(EmbArray* g, EmbPolygonObject *p);
EMB_PUBLIC int embArray_addPolyline(EmbArray* g, EmbPolylineObject *p);
EMB_PUBLIC int embArray_addStitch(EmbArray* g, EmbStitch st);
EMB_PUBLIC int embArray_addThread(EmbArray* g, EmbThread p);
EMB_PUBLIC int embArray_addVector(EmbArray* g, EmbVector);
EMB_PUBLIC void embArray_free(EmbArray* p);

EMB_PUBLIC EmbLine embLine_make(EmbVector start, EmbVector end);
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
EMB_PUBLIC void embVector_transposeProduct(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC float embVector_getLength(EmbVector vector);

EMB_PUBLIC int embFormat_getExtension(const char* fileName, char *ending);
EMB_PUBLIC const char* embFormat_extensionFromName(const char* fileName);
EMB_PUBLIC const char* embFormat_descriptionFromName(const char* fileName);
EMB_PUBLIC char embFormat_readerStateFromName(const char* fileName);
EMB_PUBLIC char embFormat_writerStateFromName(const char* fileName);
EMB_PUBLIC int embFormat_typeFromName(const char* fileName);

EMB_PUBLIC EmbArcObject embArcObject_make(EmbVector s, EmbVector m, EmbVector e);

EMB_PUBLIC char isArcClockwise(EmbArc arc);
EMB_PUBLIC void getArcCenter(EmbArc arc, EmbVector *arcCenter);
EMB_PUBLIC char getArcDataFromBulge(float bulge, EmbArc* arc, EmbVector* arcCenter,
    float* radius, float* diameter, float* chord, EmbVector* chordMid,
    float* sagitta, float* apothem, float* incAngleInDegrees, char* clockwise);

EMB_PUBLIC int getCircleCircleIntersections(EmbCircle c0, EmbCircle c1, EmbVector* p3, EmbVector* p4);
EMB_PUBLIC int getCircleTangentPoints(EmbCircle c, EmbVector point, EmbVector* t0, EmbVector* t1);

EMB_PUBLIC EmbColor embColor_fromHexStr(char* val);
EMB_PUBLIC int threadColor(EmbColor *c, const char*, int brand);
EMB_PUBLIC int threadColorNum(EmbColor color, int brand);
EMB_PUBLIC const char* threadColorName(EmbColor color, int brand);
EMB_PUBLIC int embThread_findNearestColor(EmbColor color, EmbArray* colors, int mode);
EMB_PUBLIC int embThread_findNearestColor_fromThread(EmbColor color, const EmbThread* colors, int length);
EMB_PUBLIC EmbThread embThread_getRandom(void);

EMB_PUBLIC float embEllipse_diameterX(EmbEllipse ellipse);
EMB_PUBLIC float embEllipse_diameterY(EmbEllipse ellipse);
EMB_PUBLIC float embEllipse_width(EmbEllipse ellipse);
EMB_PUBLIC float embEllipse_height(EmbEllipse ellipse);

EMB_PUBLIC EmbEllipseObject embEllipseObject_make(EmbVector, EmbVector);

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
EMB_PUBLIC int embFile_puts(EmbFile* stream, char *);
EMB_PUBLIC void embFile_print(EmbFile* stream, const char*);
EMB_PUBLIC void embFile_pad(EmbFile *f, char, int);

EMB_PUBLIC int bcfFile_read(EmbFile* file, bcf_file* bcfFile);
EMB_PUBLIC EmbFile* GetFile(bcf_file* bcfFile, EmbFile* file, char* fileToFind);
EMB_PUBLIC void bcf_file_free(bcf_file* bcfFile);

EMB_PUBLIC EmbSettings embSettings_init(void);

EMB_PUBLIC EmbVector embSettings_home(EmbSettings* settings);
EMB_PUBLIC void embSettings_setHome(EmbSettings* settings, EmbVector point);

EMB_PUBLIC void embSatinOutline_generateSatinOutline(EmbArray* lines, float thickness, EmbSatinOutline* result);
EMB_PUBLIC EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, float density);

EMB_PUBLIC float embRect_x(EmbRect rect);
EMB_PUBLIC float embRect_y(EmbRect rect);
EMB_PUBLIC float embRect_width(EmbRect rect);
EMB_PUBLIC float embRect_height(EmbRect rect);

EMB_PUBLIC void embRect_setX(EmbRect* rect, float x);
EMB_PUBLIC void embRect_setY(EmbRect* rect, float y);
EMB_PUBLIC void embRect_setWidth(EmbRect* rect, float w);
EMB_PUBLIC void embRect_setHeight(EmbRect* rect, float h);

EMB_PUBLIC void embRect_setCoords(EmbRect* rect, float x1, float y1, float x2, float y2);
EMB_PUBLIC void embRect_setRect(EmbRect* rect, float x, float y, float w, float h);

EMB_PUBLIC EmbRectObject embRectObject_make(float x, float y, float w, float h);

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
EMB_PUBLIC void embPattern_end(EmbPattern* p);
EMB_PUBLIC int embPattern_write(EmbPattern* pattern, const char *function, int);
EMB_PUBLIC int embPattern_read(EmbPattern* pattern, const char *function, int);
EMB_PUBLIC int embPattern_writeAuto(EmbPattern* pattern, const char *function);
EMB_PUBLIC int embPattern_readAuto(EmbPattern* pattern, const char *function);

EMB_PUBLIC void embPattern_addCircleObjectAbs(EmbPattern* p, float cx, float cy, float r);
EMB_PUBLIC void embPattern_addEllipseObjectAbs(EmbPattern* p, float cx, float cy, float rx, float ry); /* TODO: ellipse rotation */
EMB_PUBLIC void embPattern_addLineObjectAbs(EmbPattern* p, float x1, float y1, float x2, float y2);
EMB_PUBLIC void embPattern_addPathObjectAbs(EmbPattern* p, EmbPathObject* obj);
EMB_PUBLIC void embPattern_addPointObjectAbs(EmbPattern* p, float x, float y);
EMB_PUBLIC void embPattern_addPolygonObjectAbs(EmbPattern* p, EmbPolygonObject* obj);
EMB_PUBLIC void embPattern_addPolylineObjectAbs(EmbPattern* p, EmbPolylineObject* obj);
EMB_PUBLIC void embPattern_addRectObjectAbs(EmbPattern* p, float x, float y, float w, float h);

EMB_PUBLIC void embPattern_copyStitchListToPolylines(EmbPattern* pattern);
EMB_PUBLIC void embPattern_copyPolylinesToStitchList(EmbPattern* pattern);
EMB_PUBLIC void embPattern_moveStitchListToPolylines(EmbPattern* pattern);
EMB_PUBLIC void embPattern_movePolylinesToStitchList(EmbPattern* pattern);

/* NON-MACRO CONSTANTS
 ******************************************************************************/

EMB_PUBLIC extern const EmbFormatList formatTable[];
EMB_PUBLIC extern int numberOfFormats;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBEMBROIDERY_HEADER__ */

