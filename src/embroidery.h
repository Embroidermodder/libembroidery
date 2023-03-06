#ifndef LIBEMBROIDERY_HEADER__
#define LIBEMBROIDERY_HEADER__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBEMBROIDERY_EMBEDDED_VERSION
#define LIBEMBROIDERY_EMBEDDED_VERSION 0
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

#define EMB_ARRAY               0
#define EMB_ARC                 1
#define EMB_CIRCLE              2
#define EMB_DIM_DIAMETER        3
#define EMB_DIM_LEADER          4
#define EMB_ELLIPSE             5
#define EMB_FLAG                6
#define EMB_LINE                7
#define EMB_IMAGE               8
#define EMB_PATH                9
#define EMB_POINT               10
#define EMB_POLYGON             11
#define EMB_POLYLINE            12
#define EMB_RECT                13
#define EMB_SPLINE              14
#define EMB_STITCH              15
#define EMB_TEXT_SINGLE         16
#define EMB_TEXT_MULTI          17
#define EMB_VECTOR              18

#define EMBFORMAT_UNSUPPORTED    0
#define EMBFORMAT_STITCHONLY     1
#define EMBFORMAT_OBJECTONLY     2
#define EMBFORMAT_STCHANDOBJ     3 /* binary operation: 1+2=3 */

#define numberOfFormats         61

#define CHUNK_SIZE                  128

#define EMB_MAX_LAYERS               10
#define MAX_THREADS                 256
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

/* TYPEDEFS AND STRUCTS
 *******************************************************************/

typedef float EmbReal;

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
    EmbReal x;
    EmbReal y;
} EmbVector;

/**
 * The basic array type.
 */
typedef struct EmbArray_ EmbArray;

typedef struct EmbImage_ {
    EmbVector position;
    EmbVector dimensions;
    unsigned char* data;
    int width;
    int height;
    char path[200];
    char name[200];
} EmbImage;

typedef struct EmbBlock_ {
    EmbVector position;
} EmbBlock;

typedef struct EmbAlignedDim_ {
    EmbVector position;
} EmbAlignedDim;

typedef struct EmbAngularDim_ {
    EmbVector position;
} EmbAngularDim;

typedef struct EmbArcLengthDim_ {
    EmbVector position;
} EmbArcLengthDim;

typedef struct EmbDiameterDim_ {
    EmbVector position;
} EmbDiameterDim;

typedef struct EmbLeaderDim_ {
    EmbVector position;
} EmbLeaderDim;

typedef struct EmbLinearDim_ {
    EmbVector position;
} EmbLinearDim;

typedef struct EmbOrdinateDim_ {
    EmbVector position;
} EmbOrdinateDim;

typedef struct EmbRadiusDim_ {
    EmbVector position;
} EmbRadiusDim;

typedef struct EmbInfiniteLine_ {
    EmbVector position;
} EmbInfiniteLine;

typedef struct EmbRay_ {
    EmbVector position;
} EmbRay;

typedef struct EmbTextMulti_ {
    EmbVector position;
    char text[200];
} EmbTextMulti;

typedef struct EmbTextSingle_ {
    EmbVector position;
    char text[200];
} EmbTextSingle;

typedef struct EmbTime_
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
} EmbTime;


typedef struct EmbPoint_
{
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

typedef struct EmbPath_
{
    EmbArray* pointList;
    EmbArray* flagList;
    int lineType;
    EmbColor color;
} EmbPath;

typedef struct EmbStitch_
{
    int flags; /* uses codes defined above */
    EmbReal x; /* absolute position (not relative) */
    EmbReal y; /* positive is up, units are in mm  */
    int color; /* color number for this stitch */
    /* TODO: this should be called colorIndex since it is not an EmbColor */
} EmbStitch;

typedef struct EmbThread_
{
    EmbColor color;
    char description[50];
    char catalogNumber[30];
} EmbThread;

typedef struct thread_color_ {
    char name[22];
    unsigned int hex_code;
    int manufacturer_code;
} thread_color;

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
    EmbReal top;
    EmbReal left;
    EmbReal bottom;
    EmbReal right;
    EmbReal rotation;
    EmbReal radius;
    int lineType;
    EmbColor color;
} EmbRect;

typedef struct EmbCircle_
{
    EmbVector center;
    EmbReal radius;
    int lineType;
    EmbColor color;
} EmbCircle;

typedef EmbPath EmbPolygon;
typedef EmbPath EmbPolyline;
typedef int EmbFlag;

typedef struct EmbSatinOutline_
{
    int length;
    EmbArray* side1;
    EmbArray* side2;
} EmbSatinOutline;

typedef struct EmbEllipse_
{
    EmbVector center;
    EmbVector radius;
    EmbReal rotation;
    int lineType;
    EmbColor color;
} EmbEllipse;

typedef struct EmbBezier_ {
    EmbVector start;
    EmbVector control1;
    EmbVector control2;
    EmbVector end;
} EmbBezier;

typedef struct EmbSpline_ {
    EmbArray *beziers;
    int lineType;
    EmbColor color;
} EmbSpline;

typedef struct LSYSTEM {
    char axiom;
    char *alphabet;
    char *constants;
    char **rules;
} L_system;

typedef struct EmbGeometry_ {
    union {
        EmbArc arc;
        EmbCircle circle;
        EmbColor color;
        EmbEllipse ellipse;
        int flag;
        EmbLine line;
        EmbPath path;
        EmbPoint point;
        EmbPolygon polygon;
        EmbPolyline polyline;
        EmbRect rect;
        EmbSpline spline;
    } object;
    int type;
    int lineType;
    EmbColor color;
} EmbGeometry;

struct EmbArray_ {
    EmbArc *arc;
    EmbCircle *circle;
    EmbColor *color;
	EmbEllipse *ellipse;
	int *flag;
	EmbLine *line;
	EmbPath *path;
	EmbPoint *point;
	EmbPolygon *polygon;
	EmbPolyline *polyline;
	EmbRect *rect;
	EmbSpline *spline;
	EmbStitch *stitch;
	EmbThread thread[MAX_THREADS];
	EmbVector *vector;
    int count;
    int length;
    int type;
};

typedef struct EmbLayer_
{
    char name[100];
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
} EmbLayer;

typedef struct EmbPattern_
{
    unsigned int dstJumpsPerTrim;
    EmbVector home;
    EmbReal hoop_width;
    EmbReal hoop_height;

    EmbThread thread_list[MAX_THREADS];
    int n_threads;

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
    EmbLayer layer[EMB_MAX_LAYERS];

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
EMB_PUBLIC void testMain(int level);
EMB_PUBLIC int convert(const char *inf, const char *outf);

EMB_PUBLIC EmbColor embColor_make(unsigned char r, unsigned char g, unsigned char b);
EMB_PUBLIC EmbColor* embColor_create(unsigned char r, unsigned char g, unsigned char b);
EMB_PUBLIC EmbColor embColor_fromHexStr(char* val);
EMB_PUBLIC int embColor_distance(EmbColor a, EmbColor b);

EMB_PUBLIC EmbArray* embArray_create(int type);
EMB_PUBLIC int embArray_resize(EmbArray *g);
EMB_PUBLIC void embArray_copy(EmbArray *dst, EmbArray *src);
EMB_PUBLIC int embArray_addArc(EmbArray* g, EmbArc arc);
EMB_PUBLIC int embArray_addCircle(EmbArray* g, EmbCircle circle);
EMB_PUBLIC int embArray_addEllipse(EmbArray* g, EmbEllipse ellipse);
EMB_PUBLIC int embArray_addFlag(EmbArray* g, int flag);
EMB_PUBLIC int embArray_addLine(EmbArray* g, EmbLine line);
EMB_PUBLIC int embArray_addRect(EmbArray* g, EmbRect rect);
EMB_PUBLIC int embArray_addPath(EmbArray* g, EmbPath p);
EMB_PUBLIC int embArray_addPoint(EmbArray* g, EmbPoint p);
EMB_PUBLIC int embArray_addPolygon(EmbArray* g, EmbPolygon p);
EMB_PUBLIC int embArray_addPolyline(EmbArray* g, EmbPolyline p);
/* EMB_PUBLIC int embArray_addSpline(EmbArray* g, EmbSpline p); */
EMB_PUBLIC int embArray_addStitch(EmbArray* g, EmbStitch st);
EMB_PUBLIC int embArray_addThread(EmbArray* g, EmbThread p);
EMB_PUBLIC int embArray_addVector(EmbArray* g, EmbVector);
EMB_PUBLIC void embArray_free(EmbArray* p);

EMB_PUBLIC EmbLine embLine_make(EmbReal x1, EmbReal y1, EmbReal x2, EmbReal y2);

EMB_PUBLIC void embLine_normalVector(EmbLine line, EmbVector* result, int clockwise);
EMB_PUBLIC EmbVector embLine_intersectionPoint(EmbLine line1, EmbLine line2);

EMB_PUBLIC int embThread_findNearestColor(EmbColor color, EmbArray* colors, int mode);
EMB_PUBLIC int embThread_findNearestColor_fromThread(EmbColor color, EmbThread* colors, int length);
EMB_PUBLIC EmbThread embThread_getRandom(void);

EMB_PUBLIC void embVector_normalize(EmbVector vector, EmbVector* result);
EMB_PUBLIC void embVector_multiply(EmbVector vector, EmbReal magnitude, EmbVector* result);
EMB_PUBLIC EmbVector embVector_add(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbVector embVector_average(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbVector embVector_subtract(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbReal embVector_dot(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbReal embVector_cross(EmbVector v1, EmbVector v2);
EMB_PUBLIC void embVector_transpose_product(EmbVector v1, EmbVector v2, EmbVector* result);
EMB_PUBLIC EmbReal embVector_length(EmbVector vector);
EMB_PUBLIC EmbReal embVector_relativeX(EmbVector a1, EmbVector a2, EmbVector a3);
EMB_PUBLIC EmbReal embVector_relativeY(EmbVector a1, EmbVector a2, EmbVector a3);
EMB_PUBLIC EmbReal embVector_angle(EmbVector v);
EMB_PUBLIC EmbReal embVector_distance(EmbVector a, EmbVector b);
EMB_PUBLIC EmbVector embVector_unit(EmbReal angle);

EMB_PUBLIC EmbArc embArc_init(void);
EMB_PUBLIC char embArc_clockwise(EmbArc arc);

EMB_PUBLIC void getArcCenter(EmbArc arc, EmbVector *arcCenter);
EMB_PUBLIC char getArcDataFromBulge(EmbReal bulge,
                         EmbArc *arc,
                         EmbReal* arcCenterX,        EmbReal* arcCenterY,
                         EmbReal* radius,            EmbReal* diameter,
                         EmbReal* chord,
                         EmbReal* chordMidX,         EmbReal* chordMidY,
                         EmbReal* sagitta,           EmbReal* apothem,
                         EmbReal* incAngleInDegrees, char*   clockwise);

EMB_PUBLIC EmbCircle embCircle_init(void);
EMB_PUBLIC int getCircleCircleIntersections(
     EmbCircle c0, EmbCircle c1, EmbVector *v0, EmbVector *v1);
EMB_PUBLIC int getCircleTangentPoints(
     EmbCircle c, EmbVector p, EmbVector *v0, EmbVector *v1);

EMB_PUBLIC EmbEllipse embEllipse_init(void);
EMB_PUBLIC EmbEllipse embEllipse_make(EmbReal cx, EmbReal cy, EmbReal rx, EmbReal ry);
EMB_PUBLIC EmbReal embEllipse_diameterX(EmbEllipse ellipse);
EMB_PUBLIC EmbReal embEllipse_diameterY(EmbEllipse ellipse);
EMB_PUBLIC EmbReal embEllipse_width(EmbEllipse ellipse);
EMB_PUBLIC EmbReal embEllipse_height(EmbEllipse ellipse);
EMB_PUBLIC EmbReal embEllipse_area(EmbEllipse ellipse);
EMB_PUBLIC EmbReal embEllipse_perimeter(EmbEllipse ellipse);

EMB_PUBLIC EmbImage embImage_create(int, int);
EMB_PUBLIC void embImage_read(EmbImage *image, char *fname);
EMB_PUBLIC int embImage_write(EmbImage *image, char *fname);
EMB_PUBLIC void embImage_free(EmbImage *image);

EMB_PUBLIC EmbRect embRect_init(void);
EMB_PUBLIC EmbReal embRect_area(EmbRect);

EMB_PUBLIC int threadColor(const char*, int brand);
EMB_PUBLIC int threadColorNum(unsigned int color, int brand);
EMB_PUBLIC const char* threadColorName(unsigned int color, int brand);

EMB_PUBLIC void embTime_initNow(EmbTime* t);
EMB_PUBLIC EmbTime embTime_time(EmbTime* t);

EMB_PUBLIC void embSatinOutline_generateSatinOutline(EmbArray* lines, EmbReal thickness, EmbSatinOutline* result);
EMB_PUBLIC EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, EmbReal density);

EMB_PUBLIC EmbGeometry *embGeometry_init(int type_in);
EMB_PUBLIC void embGeometry_free(EmbGeometry *obj);
EMB_PUBLIC void embGeometry_move(EmbGeometry *obj, EmbVector delta);
EMB_PUBLIC EmbRect embGeometry_boundingRect(EmbGeometry *obj);
EMB_PUBLIC void embGeometry_vulcanize(EmbGeometry *obj);

EMB_PUBLIC EmbPattern* embPattern_create(void);
EMB_PUBLIC void embPattern_hideStitchesOverLength(EmbPattern* p, int length);
EMB_PUBLIC void embPattern_fixColorCount(EmbPattern* p);
EMB_PUBLIC int embPattern_addThread(EmbPattern* p, EmbThread thread);
EMB_PUBLIC void embPattern_addStitchAbs(EmbPattern* p, EmbReal x, EmbReal y, int flags, int isAutoColorIndex);
EMB_PUBLIC void embPattern_addStitchRel(EmbPattern* p, EmbReal dx, EmbReal dy, int flags, int isAutoColorIndex);
EMB_PUBLIC void embPattern_changeColor(EmbPattern* p, int index);
EMB_PUBLIC void embPattern_free(EmbPattern* p);
EMB_PUBLIC void embPattern_scale(EmbPattern* p, EmbReal scale);
EMB_PUBLIC EmbReal embPattern_totalStitchLength(EmbPattern *pattern);
EMB_PUBLIC EmbReal embPattern_minimumStitchLength(EmbPattern *pattern);
EMB_PUBLIC EmbReal embPattern_maximumStitchLength(EmbPattern *pattern);
EMB_PUBLIC void embPattern_lengthHistogram(EmbPattern *pattern, int *bin, int NUMBINS);
EMB_PUBLIC int embPattern_realStitches(EmbPattern *pattern);
EMB_PUBLIC int embPattern_jumpStitches(EmbPattern *pattern);
EMB_PUBLIC int embPattern_trimStitches(EmbPattern *pattern);
EMB_PUBLIC EmbRect embPattern_calcBoundingBox(EmbPattern* p);
EMB_PUBLIC void embPattern_flipHorizontal(EmbPattern* p);
EMB_PUBLIC void embPattern_flipVertical(EmbPattern* p);
EMB_PUBLIC void embPattern_flip(EmbPattern* p, int horz, int vert);
EMB_PUBLIC void embPattern_combineJumpStitches(EmbPattern* p);
EMB_PUBLIC void embPattern_correctForMaxStitchLength(EmbPattern* p, EmbReal maxStitchLength, EmbReal maxJumpLength);
EMB_PUBLIC void embPattern_center(EmbPattern* p);
EMB_PUBLIC void embPattern_loadExternalColorFile(EmbPattern* p, const char* fileName);
EMB_PUBLIC void embPattern_convertGeometry(EmbPattern* p);
EMB_PUBLIC void embPattern_designDetails(EmbPattern *p);
EMB_PUBLIC EmbPattern *embPattern_combine(EmbPattern *p1, EmbPattern *p2);
EMB_PUBLIC int embPattern_color_count(EmbPattern *pattern, EmbColor startColor);
EMB_PUBLIC void embPattern_end(EmbPattern* p);
EMB_PUBLIC void embPattern_crossstitch(EmbPattern *pattern, EmbImage *, int threshhold);
EMB_PUBLIC void embPattern_horizontal_fill(EmbPattern *pattern, EmbImage *, int threshhold);
EMB_PUBLIC int embPattern_render(EmbPattern *pattern, char *fname);
EMB_PUBLIC int embPattern_simulate(EmbPattern *pattern, char *fname);

EMB_PUBLIC void embPattern_addCircleAbs(EmbPattern* p, EmbCircle obj);
EMB_PUBLIC void embPattern_addEllipseAbs(EmbPattern* p, EmbEllipse obj);
EMB_PUBLIC void embPattern_addLineAbs(EmbPattern* p, EmbLine obj);
EMB_PUBLIC void embPattern_addPathAbs(EmbPattern* p, EmbPath obj);
EMB_PUBLIC void embPattern_addPointAbs(EmbPattern* p, EmbPoint obj);
EMB_PUBLIC void embPattern_addPolygonAbs(EmbPattern* p, EmbPolygon obj);
EMB_PUBLIC void embPattern_addPolylineAbs(EmbPattern* p, EmbPolyline obj);
EMB_PUBLIC void embPattern_addRectAbs(EmbPattern* p, EmbRect obj);

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
extern const EmbReal embConstantPi;
extern const EmbThread husThreads[];
extern const EmbThread jefThreads[];
extern const EmbThread shvThreads[];
extern const EmbThread pcmThreads[];
extern const EmbThread pecThreads[];
extern const unsigned char _dxfColorTable[][3];
extern EmbThread black_thread;
extern const unsigned char vipDecodingTable[];

/* VARIABLES
 ******************************************************************************/

extern int emb_error;
extern int emb_verbose;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBEMBROIDERY_HEADER__ */

