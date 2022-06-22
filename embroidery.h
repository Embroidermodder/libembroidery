#ifndef LIBEMBROIDERY_HEADER__
#define LIBEMBROIDERY_HEADER__

#ifdef __cplusplus
extern "C" {
#endif

/* MACROS
 *****************************************************************************/

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

#define CHUNK_SIZE                  128

#define EMBFORMAT_MAXEXT              3
/* maximum length of extension without dot */
#define EMBFORMAT_MAXDESC            50
/* the longest possible description string length */

#define MAX_STITCHES             1000000

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

typedef struct EmbArray_ EmbArray;

/**
 * Does it make sense to have lineType for a point?
 */
typedef struct EmbPointObject_
{
    EmbVector point;
    int lineType;
    EmbColor color;
} EmbPointObject;

typedef struct EmbLine_
{
    EmbVector start;
    EmbVector end;
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
    const char name[100];
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

/* absolute position (not relative) */
typedef struct EmbArc_
{
    EmbVector start;
    EmbVector mid;
    EmbVector end;
    int lineType;
    EmbColor color;
} EmbArc;

typedef struct EmbRect_
{
    double top;
    double left;
    double bottom;
    double right;
} EmbRect;

typedef struct EmbCircle_
{
    EmbVector center;
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

typedef struct EmbImage_ {
    int pixel_width;
    int pixel_height;
    float width;
    float height;
    EmbColor *color;
    EmbVector offset;
} EmbImage;

/**
 * Only one of the pointers is used at a time so this should be a union.
 */
struct EmbArray_ {
    EmbArc *arc;
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
} EmbPattern;

typedef struct EmbFormatList_
{
    char extension[2 + EMBFORMAT_MAXEXT];
    char description[EMBFORMAT_MAXDESC];
    char reader_state;
    char writer_state;
    int type;
    int color_only;
    int check_for_color_file;
    int write_external_color_file;
} EmbFormatList;

/* Function Declarations
*****************************************************************************/
EMB_PUBLIC int lindenmayer_system(L_system L, char* state, int iteration, int complete);
EMB_PUBLIC int hilbert_curve(EmbPattern *pattern, int iterations);

EMB_PUBLIC int emb_identify_format(const char *ending);

EMB_PUBLIC EmbArray* embArray_create(int type);
EMB_PUBLIC int embArray_resize(EmbArray *g);
EMB_PUBLIC void embArray_copy(EmbArray *dst, EmbArray *src);
EMB_PUBLIC int embArray_addArc(EmbArray* g, EmbArc arc);
EMB_PUBLIC int embArray_addCircle(EmbArray* g, EmbCircle circle, int lineType, EmbColor color);
EMB_PUBLIC int embArray_addEllipse(EmbArray* g, EmbEllipse circle, double rotation, int lineType, EmbColor color);
EMB_PUBLIC int embArray_addFlag(EmbArray* g, int flag);
EMB_PUBLIC int embArray_addLine(EmbArray* g, EmbLineObject line);
EMB_PUBLIC int embArray_addRect(EmbArray* g, EmbRect rect, int lineType, EmbColor color);
EMB_PUBLIC int embArray_addPath(EmbArray* g, EmbPathObject *p);
EMB_PUBLIC int embArray_addPoint(EmbArray* g, EmbPointObject *p);
EMB_PUBLIC int embArray_addPolygon(EmbArray* g, EmbPolygonObject *p);
EMB_PUBLIC int embArray_addPolyline(EmbArray* g, EmbPolylineObject *p);
/* EMB_PUBLIC int embArray_addSpline(EmbArray* g, EmbSplineObject *p); */
EMB_PUBLIC int embArray_addStitch(EmbArray* g, EmbStitch st);
EMB_PUBLIC int embArray_addThread(EmbArray* g, EmbThread p);
EMB_PUBLIC int embArray_addVector(EmbArray* g, EmbVector);
EMB_PUBLIC void embArray_free(EmbArray* p);

EMB_PUBLIC EmbLine embLine_make(double x1, double y1, double x2, double y2);

EMB_PUBLIC void embLine_normalVector(EmbLine line, EmbVector* result, int clockwise);
EMB_PUBLIC EmbVector embLine_intersectionPoint(EmbLine line1, EmbLine line2);

EMB_PUBLIC int embThread_findNearestColor(EmbColor color, EmbArray* colors, int mode);
EMB_PUBLIC int embThread_findNearestColor_fromThread(EmbColor color, EmbThread* colors, int length);
EMB_PUBLIC EmbThread embThread_getRandom(void);

EMB_PUBLIC void embVector_normalize(EmbVector vector, EmbVector* result);
EMB_PUBLIC void embVector_multiply(EmbVector vector, double magnitude, EmbVector* result);
EMB_PUBLIC void embVector_add(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC void embVector_average(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC void embVector_subtract(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC float embVector_dot(EmbVector v1, EmbVector v2);
EMB_PUBLIC float embVector_cross(EmbVector v1, EmbVector v2);
EMB_PUBLIC void embVector_transpose_product(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC float embVector_length(EmbVector vector);
EMB_PUBLIC float embVector_relativeX(EmbVector a1, EmbVector a2, EmbVector a3);
EMB_PUBLIC float embVector_relativeY(EmbVector a1, EmbVector a2, EmbVector a3);
EMB_PUBLIC float embVector_angle(EmbVector v);
EMB_PUBLIC float embVector_distance(EmbVector a, EmbVector b);
EMB_PUBLIC EmbVector embVector_unit(float angle);

EMB_PUBLIC int embImage_read(char *fname, EmbImage *a, int width, int height);
EMB_PUBLIC void embImage_write(char *fname, EmbImage *a);

EMB_PUBLIC void testMain(int level);
EMB_PUBLIC int convert(const char *inf, const char *outf);

EMB_PUBLIC char isArcClockwise(EmbArc arc);
EMB_PUBLIC void getArcCenter(EmbArc arc, EmbVector *arcCenter);
EMB_PUBLIC char getArcDataFromBulge(double bulge,
                         EmbArc *arc,
                         double* arcCenterX,        double* arcCenterY,
                         double* radius,            double* diameter,
                         double* chord,
                         double* chordMidX,         double* chordMidY,
                         double* sagitta,           double* apothem,
                         double* incAngleInDegrees, char*   clockwise);

EMB_PUBLIC int getCircleCircleIntersections(
     EmbCircle c0, EmbCircle c1, EmbVector *v0, EmbVector *v1);
EMB_PUBLIC int getCircleTangentPoints(
     EmbCircle c, EmbVector p, EmbVector *v0, EmbVector *v1);

EMB_PUBLIC EmbColor embColor_make(unsigned char r, unsigned char g, unsigned char b);
EMB_PUBLIC EmbColor* embColor_create(unsigned char r, unsigned char g, unsigned char b);
EMB_PUBLIC EmbColor embColor_fromHexStr(char* val);
EMB_PUBLIC int embColor_distance(EmbColor a, EmbColor b);

EMB_PUBLIC EmbImage *embImage_create(int, int);
EMB_PUBLIC void embImage_free(EmbImage *image);

EMB_PUBLIC double embEllipse_diameterX(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_diameterY(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_width(EmbEllipse ellipse);
EMB_PUBLIC double embEllipse_height(EmbEllipse ellipse);

EMB_PUBLIC EmbEllipseObject embEllipseObject_make(double cx, double cy, double rx, double ry);

EMB_PUBLIC int threadColor(const char*, int brand);
EMB_PUBLIC int threadColorNum(unsigned int color, int brand);
EMB_PUBLIC const char* threadColorName(unsigned int color, int brand);

EMB_PUBLIC void embTime_initNow(EmbTime* t);
EMB_PUBLIC EmbTime embTime_time(EmbTime* t);

EMB_PUBLIC EmbSettings embSettings_init(void);

EMB_PUBLIC EmbVector embSettings_home(EmbSettings* settings);
EMB_PUBLIC void embSettings_setHome(EmbSettings* settings, EmbVector point);

EMB_PUBLIC void embSatinOutline_generateSatinOutline(EmbArray* lines, double thickness, EmbSatinOutline* result);
EMB_PUBLIC EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, double density);

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
EMB_PUBLIC void embPattern_convertGeometry(EmbPattern* p);
EMB_PUBLIC void embPattern_designDetails(EmbPattern *p);
EMB_PUBLIC EmbPattern *embPattern_combine(EmbPattern *p1, EmbPattern *p2);
EMB_PUBLIC int embPattern_color_count(EmbPattern *pattern, EmbColor startColor);
EMB_PUBLIC void embPattern_end(EmbPattern* p);
EMB_PUBLIC void embPattern_crossstitch(EmbPattern *pattern, EmbImage *image, int threshhold);
EMB_PUBLIC void embPattern_horizontal_fill(EmbPattern *pattern, EmbImage *image, int threshhold);
EMB_PUBLIC int embPattern_render(EmbPattern *pattern, EmbImage *image, char *fname);
EMB_PUBLIC int embPattern_simulate(EmbPattern *pattern, EmbImage *image, char *fname);

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

EMB_PUBLIC char embPattern_read(EmbPattern *pattern, const char* fileName, int format);
EMB_PUBLIC char embPattern_write(EmbPattern *pattern, const char* fileName, int format);

EMB_PUBLIC char embPattern_readAuto(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char embPattern_writeAuto(EmbPattern *pattern, const char* fileName);

EMB_PUBLIC void report(int result, char *label);
EMB_PUBLIC int full_test_matrix(char *fname);

/* NON-MACRO CONSTANTS
 ******************************************************************************/

extern EmbFormatList formatTable[numberOfFormats];
extern const int pecThreadCount;
extern const int shvThreadCount;
extern const double embConstantPi;
extern const EmbThread husThreads[];
extern const EmbThread jefThreads[];
extern const EmbThread shvThreads[];
extern const EmbThread pcmThreads[];
extern const EmbThread pecThreads[];
extern const unsigned char _dxfColorTable[][3];
extern EmbThread black_thread;
extern const unsigned char csd_decryptArray[];
extern const unsigned char max_header[];
extern const char imageWithFrame[38][48];
extern const unsigned char vipDecodingTable[];

/* VARIABLES
 ******************************************************************************/

extern int emb_error;
extern int emb_verbose;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBEMBROIDERY_HEADER__ */

