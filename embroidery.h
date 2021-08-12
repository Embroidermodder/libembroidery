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
    #if defined(__WIN32__)
        #define EMB_PUBLIC __declspec(dllexport)
    #else
        #define EMB_PUBLIC __attribute__ ((visibility("default")))
    #endif
#endif

#ifdef ARDUINO
#include "utility/ino-logging.h"
#include "utility/ino-file.h"
#else
typedef struct EmbFile_
{
    FILE* file;
} EmbFile;
#endif /* ARDUINO */

#include "hashtable.h"

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

/* Machine codes for stitch flags */
#define NORMAL              0 /* stitch to (xx, yy) */
#define JUMP                1 /* move to(xx, yy) */
#define TRIM                2 /* trim + move to(xx, yy) */
#define STOP                4 /* pause machine for thread change */
#define SEQUIN              8 /* sequin */
#define END                 16 /* end of program */

#define CHUNK_SIZE 128

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

#define EMB_ARC         0
#define EMB_CIRCLE      1
#define EMB_ELLIPSE     2
#define EMB_LINE        3
#define EMB_POINT       4
#define EMB_POLYGON     5
#define EMB_POLYLINE    6
#define EMB_RECT        7
#define EMB_SPLINE      8

#define PI 3.1415926535

#define EMBFORMAT_UNSUPPORTED 0
#define EMBFORMAT_STITCHONLY  1
#define EMBFORMAT_OBJECTONLY  2
#define EMBFORMAT_STCHANDOBJ  3 /* binary operation: 1+2=3 */

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

typedef struct EmbColor_
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} EmbColor;

/* TODO: EmbVector should just be a typedef of EmbPoint since internally, they are the same.
         In cases where it represents vector data, then the name can be used to avoid confusion.
         */
typedef struct EmbVector_
{
    double X;
    double Y;
} EmbVector;

typedef struct EmbVectorList_
{
    EmbVector vector;
    struct EmbVectorList_* next;
} EmbVectorList;

typedef int EmbFlag;

typedef struct EmbFlagList_
{
    int flag;
    struct EmbFlagList_* next;
} EmbFlagList;

typedef struct EmbPoint_
{
    double xx; /* absolute position (not relative) */
    double yy; /* positive is up, units are in mm  */
} EmbPoint;

typedef struct EmbPointList_
{
    EmbPoint point;
    struct EmbPointList_* next;
} EmbPointList;

typedef struct EmbPointObject_
{
    EmbPoint point;
    int lineType;
    EmbColor color;
} EmbPointObject;

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

typedef struct EmbLineObjectList_
{
    EmbLineObject lineObj;
    struct EmbLineObjectList_* next;
} EmbLineObjectList;

typedef struct EmbLayer_
{
    EmbColor color;
    const char* name;
} EmbLayer;

typedef struct EmbPathObject_
{
    EmbPointList* pointList;
    EmbFlagList* flagList;
    int lineType;
    EmbColor color;
} EmbPathObject;

typedef struct EmbPathObjectList_
{
    EmbPathObject* pathObj;
    struct EmbPathObjectList_* next;
} EmbPathObjectList;

typedef struct EmbStitch_
{
    int flags; /* uses codes defined above */
    double xx; /* absolute position (not relative) */
    double yy; /* positive is up, units are in mm  */
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

typedef struct EmbThreadList_
{
    EmbThread thread;
    struct EmbThreadList_* next;
} EmbThreadList;

typedef struct EmbHoop_
{
    double width;
    double height;
} EmbHoop;

typedef HashTable EmbHash;

typedef struct EmbFormatList_
{
    char extension[2 + EMBFORMAT_MAXEXT];
    char description[EMBFORMAT_MAXDESC];
    char reader;
    char writer;
    int type;
} EmbFormatList;

typedef struct thread_color_ {
    char name[20];
    unsigned int hex_code;
    int manufacturer_code;
} thread_color;

typedef struct EmbPointObjectList_
{
    EmbPointObject pointObj;
    struct EmbPointObjectList_* next;
} EmbPointObjectList;

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

typedef struct EmbRect_
{
    double top;
    double left;
    double bottom;
    double right;
} EmbRect;

typedef struct EmbArcObject_
{
    EmbArc arc;
    int lineType;
    EmbColor color;
} EmbArcObject;

typedef struct EmbArcObjectList_
{
    EmbArcObject arcObj;
    struct EmbArcObjectList_* next;
} EmbArcObjectList;

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

typedef struct EmbRectObjectList_
{
    EmbRectObject rectObj;
    struct EmbRectObjectList_* next;
} EmbRectObjectList;

typedef struct EmbPolygonObject_
{
    EmbPointList* pointList;
    int lineType;
    EmbColor color;
} EmbPolygonObject;

typedef struct EmbPolygonObjectList_
{
    EmbPolygonObject* polygonObj;
    struct EmbPolygonObjectList_* next;
} EmbPolygonObjectList;

typedef struct EmbSatinOutline_
{
    int length;
    EmbVector* side1;
    EmbVector* side2;
} EmbSatinOutline;


typedef struct EmbEllipseObject_
{
    EmbEllipse ellipse;
    double rotation;
    int lineType;
    EmbColor color;
} EmbEllipseObject;

typedef struct EmbEllipseObjectList_
{
    EmbEllipseObject ellipseObj;
    struct EmbEllipseObjectList_* next;
} EmbEllipseObjectList;

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
    EmbPointList* pointList;
    int lineType;
    EmbColor color;
} EmbPolylineObject;

typedef struct EmbPolylineObjectList_ {
    EmbPolylineObject* polylineObj;
    struct EmbPolylineObjectList_* next;
} EmbPolylineObjectList;

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

/* A list of bezier curves is a B-spline */
typedef struct EmbSplineObjectList_ {
    EmbSplineObject splineObj;
    struct EmbSplineObjectList_* next;
} EmbSplineObjectList; /* TODO: This struct/file needs reworked to work internally similar to polylines */

typedef struct EmbGeometryArray_ {
    EmbArcObject *arc;
    EmbCircleObject *circle;
    EmbEllipseObject *ellipse;
    EmbPointObject *point;
    EmbLineObject *line;
    EmbPolygonObject *polygon;
    EmbPolylineObject *polyline;
    EmbRectObject *rect;
    EmbSplineObject *spline;
    int count;
    int length;
    int type;
} EmbGeometryArray;

typedef struct EmbPattern_
{
    EmbSettings settings;
    EmbHoop hoop;
    EmbStitchList* stitchList;
    EmbThreadList* threadList;

    EmbArcObjectList* arcObjList;
    EmbGeometryArray* circles;
    EmbEllipseObjectList* ellipseObjList;
    EmbLineObjectList* lineObjList;
    EmbPathObjectList* pathObjList;
    EmbPointObjectList* pointObjList;
    EmbPolygonObjectList* polygonObjList;
    EmbPolylineObjectList* polylineObjList;
    EmbRectObjectList* rectObjList;
    EmbSplineObjectList* splineObjList;

    EmbStitchList* lastStitch;
    EmbThreadList* lastThread;

    EmbArcObjectList* lastArcObj;
    EmbEllipseObjectList* lastEllipseObj;
    EmbLineObjectList* lastLineObj;
    EmbPathObjectList* lastPathObj;
    EmbPointObjectList* lastPointObj;
    EmbPolygonObjectList* lastPolygonObj;
    EmbPolylineObjectList* lastPolylineObj;
    EmbRectObjectList* lastRectObj;
    EmbSplineObjectList* lastSplineObj;

    int currentColorIndex;
    double lastX;
    double lastY;
} EmbPattern;

typedef struct EmbReaderWriter_ {
    int (*reader)(EmbPattern*, const char*);
    int (*writer)(EmbPattern*, const char*);
} EmbReaderWriter;

/* Function Declarations
*****************************************************************************/
EMB_PUBLIC double embMinDouble(double, double);
EMB_PUBLIC double embMaxDouble(double, double);

EMB_PUBLIC int embMinInt(int, int);
EMB_PUBLIC int embMaxInt(int, int);

EMB_PUBLIC int embGeometryArray_create(EmbGeometryArray *g, int type);
EMB_PUBLIC int embGeometryArray_resize(EmbGeometryArray *g);
EMB_PUBLIC int embGeometryArray_addArc(EmbGeometryArray* g, EmbArc arc, int lineType, EmbColor color);
EMB_PUBLIC int embGeometryArray_addCircle(EmbGeometryArray* g, EmbCircle circle, int lineType, EmbColor color);
EMB_PUBLIC void embGeometryArray_free(EmbGeometryArray* p);

EMB_PUBLIC double embLine_x1(EmbLine line);
EMB_PUBLIC double embLine_y1(EmbLine line);
EMB_PUBLIC double embLine_x2(EmbLine line);
EMB_PUBLIC double embLine_y2(EmbLine line);

EMB_PUBLIC EmbLineObject embLineObject_make(double x1, double y1, double x2, double y2);
EMB_PUBLIC EmbLineObject* embLineObject_create(double x1, double y1, double x2, double y2);

EMB_PUBLIC EmbLineObjectList* embLineObjectList_create(EmbLineObject data);
EMB_PUBLIC EmbLineObjectList* embLineObjectList_add(EmbLineObjectList* pointer, EmbLineObject data);
EMB_PUBLIC int embLineObjectList_count(EmbLineObjectList* pointer);
EMB_PUBLIC int embLineObjectList_empty(EmbLineObjectList* pointer);
EMB_PUBLIC void embLineObjectList_free(EmbLineObjectList* pointer);

EMB_PUBLIC void embLine_normalVector(EmbVector vector1, EmbVector vector2, EmbVector* result, int clockwise);
EMB_PUBLIC void embLine_intersectionPoint(EmbVector v1, EmbVector v2, EmbVector v3, EmbVector v4, EmbVector* result);

void getLineIntersection(double  lineAx1,    double  lineAy1,
                         double  lineAx2,    double  lineAy2,
                         double  lineBx1,    double  lineBy1,
                         double  lineBx2,    double  lineBy2,
                         double *intersectX, double *intersectY);

EMB_PUBLIC EmbPathObject* embPathObject_create(EmbPointList* pointList, EmbFlagList* flagList, EmbColor color, int lineType);
EMB_PUBLIC void embPathObject_free(EmbPathObject* pointer);


EMB_PUBLIC EmbPathObjectList* embPathObjectList_create(EmbPathObject* data);
EMB_PUBLIC EmbPathObjectList* embPathObjectList_add(EmbPathObjectList* pointer, EmbPathObject* data);
EMB_PUBLIC int embPathObjectList_count(EmbPathObjectList* pointer);
EMB_PUBLIC int embPathObjectList_empty(EmbPathObjectList* pointer);
EMB_PUBLIC void embPathObjectList_free(EmbPathObjectList* pointer);

EMB_PUBLIC EmbStitchList* embStitchList_create(EmbStitch data);
EMB_PUBLIC EmbStitchList* embStitchList_add(EmbStitchList* pointer, EmbStitch data);
EMB_PUBLIC int embStitchList_count(EmbStitchList* pointer);
EMB_PUBLIC int embStitchList_empty(EmbStitchList* pointer);
EMB_PUBLIC void embStitchList_free(EmbStitchList* pointer);
EMB_PUBLIC EmbStitch embStitchList_getAt(EmbStitchList* pointer, int num);

EMB_PUBLIC int embThread_findNearestColor(EmbColor color, EmbThreadList* colors);
EMB_PUBLIC int embThread_findNearestColorInArray(EmbColor color, EmbThread* colorArray, int count);
EMB_PUBLIC EmbThread embThread_getRandom(void);

EMB_PUBLIC EmbThreadList* embThreadList_create(EmbThread data);
EMB_PUBLIC EmbThreadList* embThreadList_add(EmbThreadList* pointer, EmbThread data);
EMB_PUBLIC int embThreadList_count(EmbThreadList* pointer);
EMB_PUBLIC int embThreadList_empty(EmbThreadList* pointer);
EMB_PUBLIC void embThreadList_free(EmbThreadList* pointer);
EMB_PUBLIC EmbThread embThreadList_getAt(EmbThreadList* pointer, int num);

EMB_PUBLIC void embVector_normalize(EmbVector vector, EmbVector* result);
EMB_PUBLIC void embVector_multiply(EmbVector vector, double magnitude, EmbVector* result);
EMB_PUBLIC void embVector_add(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC void embVector_average(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC void embVector_subtract(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC double embVector_dot(EmbVector v1, EmbVector v2);
EMB_PUBLIC void embVector_transpose_product(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC double embVector_getLength(EmbVector vector);

EMB_PUBLIC EmbVectorList* embVectorList_create(EmbVector data);
EMB_PUBLIC EmbVectorList* embVectorList_add(EmbVectorList* pointer, EmbVector data);
EMB_PUBLIC int embVectorList_count(EmbVectorList* pointer);
EMB_PUBLIC int embVectorList_empty(EmbVectorList* pointer);
EMB_PUBLIC void embVectorList_free(EmbVectorList* pointer);

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

EMB_PUBLIC double embHoop_width(EmbHoop hoop);
EMB_PUBLIC double embHoop_height(EmbHoop hoop);

EMB_PUBLIC EmbHash* embHash_create(void);
EMB_PUBLIC void embHash_free(EmbHash* hash);

EMB_PUBLIC int embHash_contains(const EmbHash* hash, const void* key);
EMB_PUBLIC int embHash_insert(EmbHash* hash, const void* key, void* value);
EMB_PUBLIC void* embHash_value(const EmbHash* hash, const void* key);
EMB_PUBLIC void embHash_remove(EmbHash* hash, const void *key);
EMB_PUBLIC void embHash_clear(EmbHash* hash);
EMB_PUBLIC int embHash_empty(const EmbHash* hash);
EMB_PUBLIC long embHash_count(const EmbHash* hash);
EMB_PUBLIC void embHash_rehash(EmbHash* hash, long numOfBuckets);

extern EmbFormatList formatTable[100];
extern int numberOfFormats;

EMB_PUBLIC int embFormat_getExtension(const char* fileName, char *ending);
EMB_PUBLIC const char* embFormat_extensionFromName(const char* fileName);
EMB_PUBLIC const char* embFormat_descriptionFromName(const char* fileName);
EMB_PUBLIC char embFormat_readerStateFromName(const char* fileName);
EMB_PUBLIC char embFormat_writerStateFromName(const char* fileName);
EMB_PUBLIC int embFormat_typeFromName(const char* fileName);

void husExpand(unsigned char* input, unsigned char* output, int compressedSize, int _269);
int husCompress(unsigned char* _266, unsigned long _inputSize, unsigned char* _267, int _269, int _235);

EMB_PUBLIC EmbArcObject embArcObject_make(double sx, double sy, double mx, double my, double ex, double ey);
EMB_PUBLIC EmbArcObject* embArcObject_create(double sx, double sy, double mx, double my, double ex, double ey);

EMB_PUBLIC EmbArcObjectList* embArcObjectList_add(EmbArcObjectList* pointer, EmbArcObject data);
EMB_PUBLIC int embArcObjectList_count(EmbArcObjectList* pointer);
EMB_PUBLIC int embArcObjectList_empty(EmbArcObjectList* pointer);
EMB_PUBLIC void embArcObjectList_free(EmbArcObjectList* pointer);

char isArcClockwise(double startx, double starty,
      double midx,   double midy,
      double endx,   double endy);

void getArcCenter(double  arcStartX,  double  arcStartY,
                  double  arcMidX,    double  arcMidY,
                  double  arcEndX,    double  arcEndY,
                  /* returned data */
                  double *arcCenterX, double *arcCenterY);

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
      /* The circle */
      EmbCircle c0, EmbCircle c1,
      /* Intersection Point */
      double* px3, double* py3,
      /* Intersection Point */
      double* px4, double* py4);

EMB_PUBLIC int getCircleTangentPoints(
     /* The circle */
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

EMB_PUBLIC double embEllipse_centerX(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_centerY(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_radiusX(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_radiusY(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_diameterX(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_diameterY(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_width(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_height(EmbEllipse ellipse);

EMB_PUBLIC EmbEllipseObject embEllipseObject_make(double cx, double cy, double rx, double ry);
EMB_PUBLIC EmbEllipseObject* embEllipseObject_create(double cx, double cy, double rx, double ry);

EMB_PUBLIC EmbEllipseObjectList* embEllipseObjectList_create(EmbEllipseObject data);
EMB_PUBLIC EmbEllipseObjectList* embEllipseObjectList_add(EmbEllipseObjectList* pointer, EmbEllipseObject data);
EMB_PUBLIC int embEllipseObjectList_count(EmbEllipseObjectList* pointer);
EMB_PUBLIC int embEllipseObjectList_empty(EmbEllipseObjectList* pointer);
EMB_PUBLIC void embEllipseObjectList_free(EmbEllipseObjectList* pointer);

int validateWritePattern(EmbPattern* pattern, const char* fileName, const char *function);
int validateReadPattern(EmbPattern* pattern, const char* fileName, const char *function);

EMB_PUBLIC EmbFile* embFile_open(const char* fileName, const char* mode);
EMB_PUBLIC int embFile_close(EmbFile* stream);
EMB_PUBLIC int embFile_eof(EmbFile* stream);
EMB_PUBLIC int embFile_getc(EmbFile* stream);
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

EMB_PUBLIC EmbFlagList* embFlagList_create(EmbFlag data);
EMB_PUBLIC EmbFlagList* embFlagList_add(EmbFlagList* pointer, EmbFlag data);
EMB_PUBLIC int embFlagList_count(EmbFlagList* pointer);
EMB_PUBLIC int embFlagList_empty(EmbFlagList* pointer);
EMB_PUBLIC void embFlagList_free(EmbFlagList* pointer);

EMB_PUBLIC void embLog_print(const char* format, ...);
EMB_PUBLIC void embLog_error(const char* format, ...);

int threadColor(const char*, int brand);
int threadColorNum(unsigned int color, int brand);
const char* threadColorName(unsigned int color, int brand);

EMB_PUBLIC void embTime_initNow(EmbTime* t);
EMB_PUBLIC EmbTime embTime_time(EmbTime* t);

EMB_PUBLIC double embPoint_x(EmbPoint point);
EMB_PUBLIC double embPoint_y(EmbPoint point);
EMB_PUBLIC EmbPoint embPoint_make(double x, double y);

EMB_PUBLIC EmbPointList* embPointList_create(double x, double y);
EMB_PUBLIC EmbPointList* embPointList_add(EmbPointList* pointer, EmbPoint data);
EMB_PUBLIC int embPointList_count(EmbPointList* pointer);
EMB_PUBLIC int embPointList_empty(EmbPointList* pointer);
EMB_PUBLIC void embPointList_free(EmbPointList* pointer);

EMB_PUBLIC EmbPointObject embPointObject_make(double x, double y);
EMB_PUBLIC EmbPointObject* embPointObject_create(double x, double y);

EMB_PUBLIC EmbPointObjectList* embPointObjectList_create(EmbPointObject data);
EMB_PUBLIC EmbPointObjectList* embPointObjectList_add(EmbPointObjectList* pointer, EmbPointObject data);
EMB_PUBLIC int embPointObjectList_count(EmbPointObjectList* pointer);
EMB_PUBLIC int embPointObjectList_empty(EmbPointObjectList* pointer);
EMB_PUBLIC void embPointObjectList_free(EmbPointObjectList* pointer);

EMB_PUBLIC int embSplineObjectList_count(EmbSplineObjectList* pointer);
EMB_PUBLIC int embSplineObjectList_empty(EmbSplineObjectList* pointer);

EMB_PUBLIC EmbSettings embSettings_init(void);

EMB_PUBLIC EmbPoint embSettings_home(EmbSettings* settings);
EMB_PUBLIC void embSettings_setHome(EmbSettings* settings, EmbPoint point);

EMB_PUBLIC EmbPolygonObject* embPolygonObject_create(EmbPointList* pointList, EmbColor color, int lineType);
EMB_PUBLIC void embPolygonObject_free(EmbPolygonObject* pointer);

EMB_PUBLIC EmbPolygonObjectList* embPolygonObjectList_create(EmbPolygonObject* data);
EMB_PUBLIC EmbPolygonObjectList* embPolygonObjectList_add(EmbPolygonObjectList* pointer, EmbPolygonObject* data);
EMB_PUBLIC int embPolygonObjectList_count(EmbPolygonObjectList* pointer);
EMB_PUBLIC int embPolygonObjectList_empty(EmbPolygonObjectList* pointer);
EMB_PUBLIC void embPolygonObjectList_free(EmbPolygonObjectList* pointer);

EMB_PUBLIC void embSatinOutline_generateSatinOutline(EmbVector lines[], int numberOfPoints, double thickness, EmbSatinOutline* result);
EMB_PUBLIC EmbVectorList* embSatinOutline_renderStitches(EmbSatinOutline* result, double density);

EMB_PUBLIC EmbPolylineObject* embPolylineObject_create(EmbPointList* pointList, EmbColor color, int lineType);
EMB_PUBLIC void embPolylineObject_free(EmbPolylineObject* pointer);

EMB_PUBLIC EmbPolylineObjectList* embPolylineObjectList_create(EmbPolylineObject* data);
EMB_PUBLIC EmbPolylineObjectList* embPolylineObjectList_add(EmbPolylineObjectList* pointer, EmbPolylineObject* data);
EMB_PUBLIC int embPolylineObjectList_count(EmbPolylineObjectList* pointer);
EMB_PUBLIC int embPolylineObjectList_empty(EmbPolylineObjectList* pointer);
EMB_PUBLIC void embPolylineObjectList_free(EmbPolylineObjectList* pointer);

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
EMB_PUBLIC EmbRectObject* embRectObject_create(double x, double y, double w, double h);

EMB_PUBLIC EmbRectObjectList* embRectObjectList_create(EmbRectObject data);
EMB_PUBLIC EmbRectObjectList* embRectObjectList_add(EmbRectObjectList* pointer, EmbRectObject data);
EMB_PUBLIC int embRectObjectList_count(EmbRectObjectList* pointer);
EMB_PUBLIC int embRectObjectList_empty(EmbRectObjectList* pointer);
EMB_PUBLIC void embRectObjectList_free(EmbRectObjectList* pointer);

EMB_PUBLIC EmbReaderWriter* embReaderWriter_getByFileName(const char* fileName);

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

#define READER_WRITER(type) \
    int read##type(EmbPattern *pattern, const char *fileName); \
    int write##type(EmbPattern *pattern, const char *fileName);

#ifdef ARDUINO /* ARDUINO TODO: This is temporary. Remove when complete. */

READER_WRITER(Exp)

#else /* ARDUINO TODO: This is temporary. Remove when complete. */

READER_WRITER(100)
READER_WRITER(10o)
READER_WRITER(Art)
READER_WRITER(Bmc)
READER_WRITER(Bro)
READER_WRITER(Cnd)
READER_WRITER(Col)
READER_WRITER(Csd)
READER_WRITER(Csv)
READER_WRITER(Dat)
READER_WRITER(Dem)
READER_WRITER(Dsb)
READER_WRITER(Dst)
READER_WRITER(Dsz)
READER_WRITER(Dxf)
READER_WRITER(Edr)
READER_WRITER(Emd)
READER_WRITER(Exp)
READER_WRITER(Exy)
READER_WRITER(Eys)
READER_WRITER(Fxy)
READER_WRITER(Gc)
READER_WRITER(Gnc)
READER_WRITER(Gt)
READER_WRITER(Hus)
READER_WRITER(Inb)
READER_WRITER(Inf)
READER_WRITER(Jef)
READER_WRITER(Ksm)
READER_WRITER(Max)
READER_WRITER(Mit)
READER_WRITER(New)
READER_WRITER(Ofm)
READER_WRITER(Pcd)
READER_WRITER(Pcm)
READER_WRITER(Pcq)
READER_WRITER(Pcs)
READER_WRITER(Pec)
READER_WRITER(Pel)
READER_WRITER(Pem)
READER_WRITER(Pes)
READER_WRITER(Phb)
READER_WRITER(Phc)
READER_WRITER(Plt)
READER_WRITER(Rgb)
READER_WRITER(Sew)
READER_WRITER(Shv)
READER_WRITER(Sst)
READER_WRITER(Stx)
READER_WRITER(Svg)
READER_WRITER(T01)
READER_WRITER(T09)
READER_WRITER(Tap)
READER_WRITER(Thr)
READER_WRITER(Txt)
READER_WRITER(U00)
READER_WRITER(U01)
READER_WRITER(Vip)
READER_WRITER(Vp3)
READER_WRITER(Xxx)
READER_WRITER(Zsk)

void readPecStitches(EmbPattern* pattern, EmbFile* file);
void writePecStitches(EmbPattern* pattern, EmbFile* file, const char* filename);

#endif /* ARDUINO TODO: This is temporary. Remove when complete. */

#undef READER_WRITER

/* NON-MACRO CONSTANTS
******************************************************************************/

/*! Constant representing the number of Double Indirect FAT entries in a single header */
extern const unsigned int NumberOfDifatEntriesInHeader;
extern const int pecThreadCount;
extern const EmbThread pecThreads[];
extern const char imageWithFrame[38][48];
extern const EmbThread jefThreads[];
extern const int shvThreadCount;
extern const EmbThread shvThreads[];

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBEMBROIDERY_HEADER__ */

