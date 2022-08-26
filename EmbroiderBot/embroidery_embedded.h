/*
 * EmbroiderBot
 * Copyright 2021-2022 The Embroidermodder Team
 * Distributed under the terms of the zlib license (see LICENSE).
 */

/* The Macro library is crucial to keeping the executable size under
 * 32kb and suitable for Arduino Uno.
 *
 * If a function is expressible as one or two lines of code, by
 * expressing it as a macro:
 *     o if it is never called then it uses no storage
 *     o if it is called then it uses as much, if not less storage
 *     o it cuts the call/return overhead
 *
 * For longer functions it is less storage to have have the function
 * not be a macro, unless the likelihood that it is called is low.
 *
 * For example we could have a macro system that interprets file types
 * conditionally, so if the user needs DST and JEF but no others then we
 * can just have DST_READ, DST_WRITE, JEF_READ, JEF_WRITE as macros and
 * therefore all the other formats aren't compiled in.
 * 
 */

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

#define EMB_MIN(A, B) \
    ((A < B) ? (A) : (B))
#define EMB_MAX(A, B) \
    ((A > B) ? (A) : (B))
#define EMB_ABS(A, B) \
    ((A < 0.0) ? (-A) : (A))

#define FREAD16(file, data) \
    fread(&data, 2, 1, file)
#define FWRITE16(file, data) \
    fwrite(&data, 2, 1, file)
#define FREAD32(file, data) \
    fread(&data, 4, 1, file)
#define FWRITE32(file, data) \
    fwrite(&data, 4, 1, file)

#define FREAD_INT16_BE(file, data) \
    FREAD16(file, data); \
    reverse_byte_order(&data, 2)
#define FWRITE_INT16_BE(file, data) \
    FWRITE16(file, data); \
    reverse_byte_order(&data, 2)
#define FREAD_INT32_BE(file, data) \
    FREAD32(file, data); \
    reverse_byte_order(&data, 4)
#define FWRITE_INT32_BE(file, data) \
    FREAD16(file, data); \
    reverse_byte_order(&data, 4)

#define embPattern_flipHorizontal(p) \
    embPattern_flip(p, 1, 0)
#define embPattern_flipVertical(p) \
    embPattern_flip(p, 0, 1)

#define embColor_distance(a, b) \
    ( \
        (a.r - b.r) * (a.r - b.r) \
      + (a.g - b.g) * (a.g - b.g) \
      + (a.b - b.b) * (a.b - b.b) \
    )

#define embColor_equal(a, b) \
    (embColor_distance(a,b)!=0)

/*
 * The "cross product", i.e. the z value of the cross product where
 * the 2-vector is the first two entries of the 3-vectors of a normal
 * cross product.
 */
#define embVector_cross(v1, v2) \
    (v1.x*v2.y - v1.y*v2.x)

/*
 * The length or absolute value of the vector \a vector.
 *
 * (EmbVector vector) returns float
 */
#define embVector_getLength(a) \
    (sqrt(a.x*a.x+a.y*a.y))

#define embVector_angle(v1) \
    (atan2(v1.y, v1.x))

/*
 * The sum of vectors \a v1 and \a v2 returned as \a out.
 */
#define embVector_add(out, v1, v2) \
    out.x = v1.x + v2.x; \
    out.y = v1.y + v2.y;

/* Finds the unit length vector \a result
 * in the same direction as \a vector.
 */
#define embVector_normalize(out, vector) \
    { \
        float length = embVector_getLength(vector); \
        \
        out.x = vector.x / length; \
        out.y = vector.y / length; \
    }

/*
 * The average of vectors \a v1 and \a v2 returned as \a result.
 */
#define embVector_average(out, v1, v2) \
    out.x = (v1.x+v2.x)/2.0; \
    out.y = (v1.y+v2.y)/2.0;

/*
 * The dot product as vectors \a v1 and \a v2 returned as a float.
 *
 * That is
 * (x)   (a) = xa+yb
 * (y) . (b)
 *
 * (EmbVector v1, EmbVector v2) returns float
 */
#define embVector_dot(v1, v2) \
    (v1.x*v2.x + v1.y*v2.y)

/*
 * The Euclidean distance between points v1 and v2, aka |v2-v1|.
 *
 * (EmbVector v1, EmbVector v2) returns float
 */
#define embVector_distance(v1, v2) \
    (sqrt( \
          (v1.x - v2.x) * (v1.x - v2.x) \
        + (v1.y - v2.y) * (v1.y - v2.y) \
    ))

/*
 * Since we aren't using full 3-vector algebra here, all vectors are "vertical".
 * so this is like the product v1^{T} I_{2} v2 for our vectors \a v1 and \v2
 * so a "component-wise product". The result is stored at the pointer \a result.
 *
 * That is
 *      (1 0) (a) = (xa)
 * (x y)(0 1) (b)   (yb)
 *
 * (EmbVector v1, EmbVector v2, EmbVector* result)
 */
#define embVector_component_product(out, v1, v2) \
    out.x = v1.x * v2.x; \
    out.y = v1.y * v2.y;

/*
 * The scalar multiple \a magnitude of a vector \a vector.
 * Returned as \a result.
 *
 * (EmbVector vector, float magnitude, EmbVector* result)
 */
#define embVector_multiply(out, a, c) \
    out.x = a.x*c; \
    out.y = a.y*c;

/*
 * The difference between vectors \a v1 and \a v2 returned as \a result.
 *
 * (EmbVector result, EmbVector v1, EmbVector v2)
 */
#define embVector_subtract(out, v1, v2) \
    out.x = v1.x - v2.x; \
    out.y = v1.y - v2.y;

#define unit_vector(out, angle) \
    out.x = cos(angle); \
    out.y = sin(angle);

#define rotate_vector(rotv, a, angle) \
    { \
        unit_vector(u, angle) \
        rot.x = a.x*u.x - a.y*u.y; \
        rot.y = a.x*u.y + a.y*u.x; \
    }

#define scale_vector(newa, a, scale) \
    newa.x = a.x * scale; \
    newa.y = a.y * scale;

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

/**
 * The basic array type.
 */
typedef struct EmbArray_ EmbArray;

typedef struct EmbLayer_
{
    EmbColor color;
    const char name[100];
} EmbLayer;

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
    double rotation;
    double radius;
    int lineType;
    EmbColor color;
} EmbRect;

typedef struct EmbCircle_
{
    EmbVector center;
    double radius;
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
    double rotation;
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
	EmbThread *thread;
	EmbVector *vector;
    int count;
    int length;
    int type;
};

typedef struct EmbPattern_
{
    unsigned int dstJumpsPerTrim;
    EmbVector home;
    double hoop_width;
    double hoop_height;

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

/* Function prototypes */
void reverse_byte_order(void *data, int bytes);

EmbColor embColor_fromHexStr(char* val);

/* global data */
extern int emb_error;


