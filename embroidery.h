/*
 * LIBEMBROIDERY HEADER
 * version 1.0.0-alpha
 * This file is part of libembroidery.
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 * Copyright 2018-2025 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * -----------------------------------------------------------------------------
 *
 * Note that all new defines start with "EMB_", all functions with "emb" and all
 * typedefs with "Emb" to protect against namespace pollution. (INCOMPLETE)

Libembroidery v1.0.0-alpha
==========================

Introduction
------------

It is advised that new progammers to our project and people using
libembroidery for non-trivial integrations into their own project start by
reading this file and the header. This library has one header and it does a lot
of heavy lifting to keep libembroidery from having non-standard dependencies and
reducing the number of functions in the API to keep upgrading to future versions
trivial.

If the header does not change outside of comments (and version data) then
users of the library have to change nothing to upgrade their code. If only
constants change then it is likely they won't have to change their code.

Data Storage
------------

The approach here is to make our code friendly towards being included in
embedded, desktop and mobile applications. By making more data managed as
compiler directives we reduce the overall code footprint.

To protect against namespace pollution in more object oriented environments
like mobile applications all new defines start with `EMB_`, all functions
with `emb` and all typedefs with `Emb` . (INCOMPLETE)

A fixed number is always a #define and any list of constant strings is stored
as a `const char *[]` and has identifier integers for each entry. For example
formats have various data associated with them, to access the extension for 
the filetype CSV we can use `emb_ext[EMB_FORMAT_CSV]`.

Geometry System
---------------

Our geometry is designed on supporting 3 key systems which are generally more
complex than what is needed for embroidery. They are DXF, SVG and PostScript.
Each has it's own model for geometry and attempting to support them is the
most complex task involved in writing software to support embroidery. They
are chosen based on the reasoning that each has something to contribute
PostScript is the language of printers, SVG a language of graphic designers
with good open-source support and DXF the language of hardware design.

We want to support: people that want to use their existing embroidery
machines, other software embroidery projects, open-hardware development,
existing graphic designers that want to translate their designs to
embroidery and existing machine embroidery businesses that want to extend
what they can do. Supporting 3 graphical systems is necessary to do this.

Our approach to allow more freedom in altering how we do this without
effecting all these users too much across versions is to assign all
attributes an identifier and all geometric types accross these systems an
identifier. Then we can seperate each task as a task accross the matrix
combinations of these.

### EXAMPLE: GETTING AN ATTRIBUTE

The attribute `EMB_ATTR_AREA` and the geometry
`EMB_CIRCLE` are a valid combination and a user can determine this
in their program by calling `emb_prop_get(EMB_ATTR_AREA, EMB_CIRCLE)` asking
the question "If I attempt to get the area of a circle, is that something
that libembroidery can do?". In this case, it is and it returns 1.

Then to get the area we know that it is a real number and therefore we use
the real number version of getting an attribute of a geometric object:
`emb_ggetr`. Calling `emb_ggetr` on this combination like
`emb_ggetr(circle, EMB_ATTR_AREA)` will return the area calculated from
the radius stored as `circle->object->circle.radius`.

### EXAMPLE: SETTING AN ATTRIBUTE

From the previous example

The Header
----------

The header will be commented to guide you through how the header
works and uses a view on dependency to order everything into:

1. `#include`s
2. `#define`s
3. `typedef`s
4. function prototypes
5. `extern`al data

If you wish to add to this file please use the appropriate section.

Testing
-------

Formats
-------

## DXF

Based on the DraftSight color table. It doesn't appear to be authoratitive
and there isn't much said in the official manual about colors 8-255:
[manual](http://images.autodesk.com/adsk/files/autocad_2012_pdf_dxf-reference_enu.pdf).

A possible "standard" solution here is to use xterm ESC color codes with the first
8 overridden for compatibility. That way a curious user may be able to guess
and be _almost_ right. See this script for how simple those codes are:
[codes](https://gist.github.com/hSATAC/1095100).

The first 8 are:

```
    {   0,   0,   0 }, //   '0' (BYBLOCK)    
    { 255,   0,   0 }, //   '1' (red)        
    { 255, 255,   0 }, //   '2' (yellow)     
    {   0, 255,   0 }, //   '3' (green)      
    {   0, 255, 255 }, //   '4' (cyan)       
    {   0,   0, 255 }, //   '5' (blue)       
    { 255,   0, 255 }, //   '6' (magenta)    
    { 255, 255, 255 }, //   '7' (white)      
    { 128, 128, 128 }, //   '8' (dark gray)
    { 192, 192, 192 }, //   '9' (light gray)
```

## SVG

Converted from the table at:
[w3 standard](https://www.w3.org/TR/SVGb/types.html#ColorKeywords)
NOTE: This supports both UK and US English names, so the repeated values aren't an error.

# Report pattern

Report_pattern function that prints everything we know about the pattern at this
point including details specific to the manufacturer like hoop size. Rather
than scattershot details reported by each pattern.

 */

#ifndef EMB_LIBRARY_HEADER__
#define EMB_LIBRARY_HEADER__

#ifndef EMB_EMBEDDED_MODE__
#define EMB_EMBEDDED_MODE__ 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if (EMB_EMBEDDED_MODE__ != 1)
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <inttypes.h>
#endif

/* Version elements */
#define EMB_LIB_VERSION_MAJOR          1
#define EMB_LIB_VERSION_MINOR          0
#define EMB_LIB_VERSION_PATCH          0
#define EMB_LIB_VERSION_TAG      "alpha"

/* Memory allocation sizes */
#define MAX_ARGS                      10
#define MAX_TABLE_LENGTH             500
#define CHUNK_SIZE                   128
#define MAX_PATTERN_VARIABLES         20

/* MACROS
 *****************************************************************************
 *
 * Machine codes for stitch flags.
 * These all represent distinct bits as some of them can be combined on some
 * machines.
 *
 * Missing change color?
 */
#define NORMAL                      0x00    /* Stitch to (x, y). */
#define JUMP                        0x01    /* Move to (x, y). */
#define TRIM                        0x02    /* Trim and move to (x, y). */
#define STOP                        0x04    /* Pause machine for a thread change. */
#define SEQUIN                      0x08    /* Add a sequin at the current co-ordinates. */
#define END                         0x10    /* End of program. */

/* Format identifiers */
#define EMB_FORMAT_100                 0
#define EMB_FORMAT_10O                 1
#define EMB_FORMAT_ART                 2
#define EMB_FORMAT_BMC                 3
#define EMB_FORMAT_BRO                 4
#define EMB_FORMAT_CND                 5
#define EMB_FORMAT_COL                 6
#define EMB_FORMAT_CSD                 7
#define EMB_FORMAT_CSV                 8
#define EMB_FORMAT_DAT                 9
#define EMB_FORMAT_DEM                10
#define EMB_FORMAT_DSB                11
#define EMB_FORMAT_DST                12
#define EMB_FORMAT_DSZ                13
#define EMB_FORMAT_DXF                14
#define EMB_FORMAT_EDR                15
#define EMB_FORMAT_EMD                16
#define EMB_FORMAT_EXP                17
#define EMB_FORMAT_EXY                18
#define EMB_FORMAT_EYS                19
#define EMB_FORMAT_FXY                20
#define EMB_FORMAT_GC                 21
#define EMB_FORMAT_GNC                22
#define EMB_FORMAT_GT                 23
#define EMB_FORMAT_HUS                24
#define EMB_FORMAT_INB                25
#define EMB_FORMAT_INF                26
#define EMB_FORMAT_JEF                27
#define EMB_FORMAT_KSM                28
#define EMB_FORMAT_MAX                29
#define EMB_FORMAT_MIT                30
#define EMB_FORMAT_NEW                31
#define EMB_FORMAT_OFM                32
#define EMB_FORMAT_PCD                33
#define EMB_FORMAT_PCM                34
#define EMB_FORMAT_PCQ                35
#define EMB_FORMAT_PCS                36
#define EMB_FORMAT_PEC                37
#define EMB_FORMAT_PEL                38
#define EMB_FORMAT_PEM                39
#define EMB_FORMAT_PES                40
#define EMB_FORMAT_PHB                41
#define EMB_FORMAT_PHC                42
#define EMB_FORMAT_PLT                43
#define EMB_FORMAT_RGB                44
#define EMB_FORMAT_SEW                45
#define EMB_FORMAT_SHV                46
#define EMB_FORMAT_SST                47
#define EMB_FORMAT_STX                48
#define EMB_FORMAT_SVG                49
#define EMB_FORMAT_T01                50
#define EMB_FORMAT_T09                51
#define EMB_FORMAT_TAP                52
#define EMB_FORMAT_THR                53
#define EMB_FORMAT_TXT                54
#define EMB_FORMAT_U00                55
#define EMB_FORMAT_U01                56
#define EMB_FORMAT_VIP                57
#define EMB_FORMAT_VP3                58
#define EMB_FORMAT_XXX                59
#define EMB_FORMAT_ZSK                60

/* EmbGeometry types, should include all of the possible rendering types
 * for EmbroiderModder and internal types for stitch processing (like
 * fills).
 */
#define EMB_ARRAY                      0
#define EMB_ARC                        1
#define EMB_CIRCLE                     2
#define EMB_DIM_DIAMETER               3
#define EMB_DIM_LEADER                 4
#define EMB_ELLIPSE                    5
#define EMB_FLAG                       6
#define EMB_LINE                       7
#define EMB_IMAGE                      8
#define EMB_PATH                       9
#define EMB_POINT                     10
#define EMB_POLYGON                   11
#define EMB_POLYLINE                  12
#define EMB_RECT                      13
#define EMB_SPLINE                    14
#define EMB_STITCH                    15
#define EMB_TEXT_SINGLE               16
#define EMB_TEXT_MULTI                17
#define EMB_VECTOR                    18
#define EMB_THREAD                    19

#define EMB_NO_ERR                     0
#define EMB_WRONG_TYPE_ERR             1
#define EMB_DIV_ZERO_ERR               2
#define EMB_UNFINISHED_ERR             3

#define EMBFORMAT_UNSUPPORTED          0
#define EMBFORMAT_STITCHONLY           1
#define EMBFORMAT_OBJECTONLY           2
#define EMBFORMAT_STCHANDOBJ           3 /* binary operation: 1+2=3 */

#define numberOfFormats               61

#define EMB_MAX_LAYERS                10
#define MAX_THREADS                  256
#define MAX_STRING_LENGTH            200
#define EMBFORMAT_MAXEXT               3
/* maximum length of extension without dot */
#define EMBFORMAT_MAXDESC             50
/* the longest possible description string length */
#define MAX_STITCHES             1000000

/* Libembroidery's handling of integer types.
 */
#define EMB_LITTLE_ENDIAN              0
#define EMB_BIG_ENDIAN                 1

/* Most machines are little endian (including the developer's), so default to
 * that.
 */
#define ENDIAN_HOST    EMB_LITTLE_ENDIAN

/* LANGUAGES */
#define LANG_SVG                       0
#define LANG_PS                        1
#define LANG_PROMPT                    2

/* Identifiers for different PES versions. */
#define PES0001                     0
#define PES0020                     1
#define PES0022                     2
#define PES0030                     3
#define PES0040                     4
#define PES0050                     5
#define PES0055                     6
#define PES0056                     7
#define PES0060                     8
#define PES0070                     9
#define PES0080                    10
#define PES0090                    11
#define PES0100                    12
#define N_PES_VERSIONS             13

/**
 * Type of sector
 * Compound File Sector (CFS)
 */
#define CompoundFileSector_MaxRegSector 0xFFFFFFFA
#define CompoundFileSector_DIFAT_Sector 0xFFFFFFFC
#define CompoundFileSector_FAT_Sector   0xFFFFFFFD
#define CompoundFileSector_EndOfChain   0xFFFFFFFE
#define CompoundFileSector_FreeSector   0xFFFFFFFF

/**
 * Type of directory object
 */
#define ObjectTypeUnknown   0x00 /* Probably unallocated    */
#define ObjectTypeStorage   0x01 /* a directory type object */
#define ObjectTypeStream    0x02 /* a file type object      */
#define ObjectTypeRootEntry 0x05 /* the root entry          */

/**
 * Special values for Stream Identifiers
 */
#define CompoundFileStreamId_MaxRegularStreamId 0xFFFFFFFA /* All real stream Ids are less than this */
#define CompoundFileStreamId_NoStream           0xFFFFFFFF /* There is no valid stream Id            */

#define ELEMENT_XML              0
#define ELEMENT_A                1
#define ELEMENT_ANIMATE          2
#define ELEMENT_ANIMATECOLOR     3
#define ELEMENT_ANIMATEMOTION    4
#define ELEMENT_ANIMATETRANSFORM 5
#define ELEMENT_ANIMATION        6
#define ELEMENT_AUDIO            7
#define ELEMENT_CIRCLE           8
#define ELEMENT_DEFS             9
#define ELEMENT_DESC            10
#define ELEMENT_DISCARD         11
#define ELEMENT_ELLIPSE         12
#define ELEMENT_FONT            13
#define ELEMENT_FONT_FACE       14
#define ELEMENT_FONT_FACE_SRC   15
#define ELEMENT_FONT_FACE_URI   16
#define ELEMENT_FOREIGN_OBJECT  17
#define ELEMENT_G               18
#define ELEMENT_GLYPH           19
#define ELEMENT_HANDLER         20
#define ELEMENT_HKERN           21
#define ELEMENT_IMAGE           22
#define ELEMENT_LINE            23
#define ELEMENT_LINEAR_GRADIENT 24
#define ELEMENT_LISTENER        25
#define ELEMENT_METADATA        26
#define ELEMENT_MISSING_GLYPH   27
#define ELEMENT_MPATH           28
#define ELEMENT_PATH            29
#define ELEMENT_POLYGON         30
#define ELEMENT_POLYLINE        31
#define ELEMENT_PREFETCH        32
#define ELEMENT_RADIAL_GRADIENT 33
#define ELEMENT_RECT            34
#define ELEMENT_SCRIPT          35
#define ELEMENT_SET             36
#define ELEMENT_SOLID_COLOR     37
#define ELEMENT_STOP            38
#define ELEMENT_SVG             39
#define ELEMENT_SWITCH          40
#define ELEMENT_TBREAK          41
#define ELEMENT_TEXT            42
#define ELEMENT_TEXT_AREA       43
#define ELEMENT_TITLE           44
#define ELEMENT_TSPAN           45
#define ELEMENT_USE             46
#define ELEMENT_VIDEO                 47

#define HOOP_126X110                   0
#define HOOP_110X110                   1
#define HOOP_50X50                     2
#define HOOP_140X200                   3
#define HOOP_230X200                   4

/* DXF Version Identifiers */
#define DXF_VERSION_R10         "AC1006"
#define DXF_VERSION_R11         "AC1009"
#define DXF_VERSION_R12         "AC1009"
#define DXF_VERSION_R13         "AC1012"
#define DXF_VERSION_R14         "AC1014"
#define DXF_VERSION_R15         "AC1015"
#define DXF_VERSION_R18         "AC1018"
#define DXF_VERSION_R21         "AC1021"
#define DXF_VERSION_R24         "AC1024"
#define DXF_VERSION_R27         "AC1027"

#define DXF_VERSION_2000        "AC1015"
#define DXF_VERSION_2002        "AC1015"
#define DXF_VERSION_2004        "AC1018"
#define DXF_VERSION_2006        "AC1018"
#define DXF_VERSION_2007        "AC1021"
#define DXF_VERSION_2009        "AC1021"
#define DXF_VERSION_2010        "AC1024"
#define DXF_VERSION_2013        "AC1027"

#define SVG_CREATOR_NULL               0
#define SVG_CREATOR_EMBROIDERMODDER    1
#define SVG_CREATOR_ILLUSTRATOR        2
#define SVG_CREATOR_INKSCAPE           3

#define SVG_EXPECT_NULL                0
#define SVG_EXPECT_ELEMENT             1
#define SVG_EXPECT_ATTRIBUTE           2
#define SVG_EXPECT_VALUE               3

/*  SVG_TYPES
 *  ---------
 */
#define SVG_NULL                      0
#define SVG_ELEMENT                   1
#define SVG_PROPERTY                  2
#define SVG_MEDIA_PROPERTY            3
#define SVG_ATTRIBUTE                 4
#define SVG_CATCH_ALL                 5

/* path flag codes */
#define LINETO                     0x000
#define MOVETO                     0x001
#define BULGETOCONTROL             0x002
#define BULGETOEND                 0x004
#define ELLIPSETORAD               0x008
#define ELLIPSETOEND               0x010
#define CUBICTOCONTROL1            0x020
#define CUBICTOCONTROL2            0x040
#define CUBICTOEND                 0x080
#define QUADTOCONTROL              0x100
#define QUADTOEND                  0x200

/* Brand identifiers. */
#define EMB_BRAND_DXF                  0
#define EMB_BRAND_HUS                  1
#define EMB_BRAND_JEF                  2
#define EMB_BRAND_SHV                  3
#define EMB_BRAND_PCM                  4
#define EMB_BRAND_PEC                  5
#define EMB_BRAND_SVG                  6

/* Justification */
#define EMB_JUST_LEFT                  0
#define EMB_JUST_CENTER                1
#define EMB_JUST_RIGHT                 2
#define EMB_JUST_ALIGNED               3
#define EMB_JUST_MIDDLE                4
#define EMB_JUST_FIT                   5
#define EMB_JUST_TOPLEFT               6
#define EMB_JUST_TOPCENTER             7
#define EMB_JUST_TOPRIGHT              8
#define EMB_JUST_MIDLEFT               9
#define EMB_JUST_MIDCENTER            10
#define EMB_JUST_MIDRIGHT             11
#define EMB_JUST_BOTLEFT              12
#define EMB_JUST_BOTCENTER            13
#define EMB_JUST_BOTRIGHT             14

/* UTILITY MACROS
 * --------------
 */
#define EMB_MIN(A, B)     (((A) < (B)) ? (A) : (B))
#define EMB_MAX(A, B)     (((A) > (B)) ? (A) : (B))

/* COMPILATION SETTINGS
 * --------------------
 */
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

#if (EMB_EMBEDDED_MODE__ != 1)
/* TYPEDEFS AND STRUCTS
 *******************************************************************/

/* Should some platform need a different precision, this is typedef-ed
 * and used in place of all real types where possible.
 */
typedef float EmbReal;

typedef uint8_t EmbError;

/* EmbColor uses the light primaries: red, green, blue in that order. */
typedef struct EmbColor_
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} EmbColor;

/* The basic type to represent points absolutely or represent directions.
 *
 * Positive y is up, units are in mm.
 */
typedef struct EmbVector_
{
    EmbReal x;
    EmbReal y;
} EmbVector;

/* For our internal string library.
 *
 * Note that we cannot use this for any larger amount of data,
 * it's to ensure that the cap on the size is fixed at 200.
 */
typedef char EmbString[200];

/* To help new developers understand why we use "void *",
 * when it is widely not recommended within C++.
 *
 * libembroidery is a low-level library: we need to do bit-level
 * and untyped calculations. Thinking "memory location" not
 * "untyped pointer" helped me (Robin).
 */
typedef void *EmbMem;

/* The basic array type. */
typedef struct EmbArray_ EmbArray;

/* . */
typedef struct EmbTime_
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
} EmbTime;

/* . */
typedef struct EmbImage_ {
    EmbVector position;
    EmbVector dimensions;
    uint8_t* data;
    int width;
    int height;
    EmbString path;
    EmbString name;
} EmbImage;

/* . */
typedef struct EmbBlock_ {
    EmbVector position;
} EmbBlock;

/* . */
typedef struct EmbAlignedDim_ {
    EmbVector position;
} EmbAlignedDim;

/* . */
typedef struct EmbAngularDim_ {
    EmbVector position;
} EmbAngularDim;

/* . */
typedef struct EmbArcLengthDim_ {
    EmbVector position;
} EmbArcLengthDim;

/* . */
typedef struct EmbDiameterDim_ {
    EmbVector position;
} EmbDiameterDim;

/* . */
typedef struct EmbLeaderDim_ {
    EmbVector position;
} EmbLeaderDim;

/* . */
typedef struct EmbLinearDim_ {
    EmbVector position;
} EmbLinearDim;

/* . */
typedef struct EmbOrdinateDim_ {
    EmbVector position;
} EmbOrdinateDim;

/* . */
typedef struct EmbRadiusDim_ {
    EmbVector position;
} EmbRadiusDim;

/* . */
typedef struct EmbInfiniteLine_ {
    EmbVector position;
} EmbInfiniteLine;

/* . */
typedef struct EmbRay_ {
    EmbVector position;
} EmbRay;

/* . */
typedef struct EmbTextMulti_ {
    EmbVector position;
    EmbString text;
} EmbTextMulti;

/* . */
typedef struct EmbTextSingle_ {
    EmbVector position;
    EmbString text;
} EmbTextSingle;

/* . */
typedef struct EmbPoint_
{
    EmbVector position;
    int lineType;
    EmbColor color;
} EmbPoint;

/* . */
typedef struct EmbLine_
{
    EmbVector start;
    EmbVector end;
    int lineType;
    EmbColor color;
} EmbLine;

/* . */
typedef struct EmbPath_
{
    EmbArray* pointList;
    EmbArray* flagList;
    int lineType;
    EmbColor color;
} EmbPath;

/* \todo `color` should be called colorIndex since it is not an EmbColor. */
typedef struct EmbStitch_
{
    int flags; /* uses codes defined above */
    EmbReal x; /* absolute position (not relative) */
    EmbReal y; /* positive is up, units are in mm  */
    int color; /* color number for this stitch */
} EmbStitch;

/* . */
typedef struct EmbThread_
{
    EmbColor color;
    EmbString description;
    EmbString catalogNumber;
} EmbThread;

/* . */
typedef struct thread_color_ {
    EmbString name;
    unsigned int hex_code;
    int manufacturer_code;
} thread_color;

/* absolute position (not relative) */
typedef struct EmbArc_
{
    EmbVector start;
    EmbVector mid;
    EmbVector end;
} EmbArc;

/* . */
typedef struct EmbRect_
{
    EmbReal x;
    EmbReal y;
    EmbReal w;
    EmbReal h;
    EmbReal rotation;
    EmbReal radius;
} EmbRect;

/* . */
typedef struct EmbCircle_
{
    EmbVector center;
    EmbReal radius;
} EmbCircle;

/* . */
typedef EmbPath EmbPolygon;

/* . */
typedef EmbPath EmbPolyline;

/* . */
typedef int EmbFlag;

/* . */
typedef struct EmbSatinOutline_
{
    int length;
    EmbArray* side1;
    EmbArray* side2;
} EmbSatinOutline;

/* . */
typedef struct EmbDimLeader_ {
    EmbVector start;
    EmbVector end;
    int arrow_style;
    int line_style;
    EmbColor color;
} EmbDimLeader;

/* Ellipse object. */
typedef struct EmbEllipse_
{
    EmbVector center; /* */
    EmbVector radius; /* Represents the major and minor axes. */
    EmbReal rotation; /* Determines the direction of the direction of the first axis given. */
} EmbEllipse;

/* . */
typedef struct EmbBezier_ {
    EmbVector start;       /* */
    EmbVector control1;    /* */
    EmbVector control2;    /* */
    EmbVector end;         /* */
} EmbBezier;

/* . */
typedef struct EmbSpline_ {
    EmbArray *beziers;
} EmbSpline;

/* . */
typedef struct EmbGeometry_ {
    union {
        EmbArc arc;
        EmbCircle circle;
        EmbColor color;
        EmbEllipse ellipse;
        EmbLine line;
        EmbPath path;
        EmbPoint point;
        EmbPolygon polygon;
        EmbPolyline polyline;
        EmbRect rect;
        EmbSpline spline;
        EmbVector vector;
    } object;
    int flag;
    int type;
    int lineType;
    EmbColor color;
} EmbGeometry;

/* . */
typedef char EmbStringTable[MAX_TABLE_LENGTH][MAX_STRING_LENGTH];

/* . */
typedef struct LabelledVector_ {
    EmbString key;
    EmbVector vector;
} LabelledVector;

/* . */
typedef struct StringMap_ {
    EmbString key;
    EmbString value;
} StringMap;

/* . */
typedef struct IntMap_ {
    int key;
    int value;
} IntMap;

/* . */
typedef struct EmbVectorList_ {
    EmbVector *data;
    int count;
    int size;
} EmbVectorList;

/* . */
typedef struct EmbIdList_ {
    int32_t *data;
    int count;
    int size;
} EmbIdList;

/* . */
struct EmbArray_ {
    EmbGeometry *geometry;
    EmbStitch *stitch;
    EmbThread *thread;
    int count;
    int length;
    int type;
};

/* . */
typedef struct EmbLayer_
{
    char name[100];
    EmbArray *geometry;
} EmbLayer;

/* . */
typedef struct Design_ {
    char *command;
    float lower;
    float upper;
    int num_points;
    int min_points;
    int max_points;
    float xscale;
    float yscale;
    char *parameter;
    char *x;
    char *y;
} Design;

#define END_SYMBOL            "__END__"

/* The pattern type variable denotes the type that was read in and uses the
 * EMB_FORMAT contants. Changing this type directly would break how data is
 * interpreted,
 */
typedef struct EmbPattern_
{
    int type;
    unsigned int dstJumpsPerTrim;
    EmbVector home;
    EmbReal hoop_width;
    EmbReal hoop_height;
    EmbArray *thread_list;
    EmbArray *stitch_list;
    EmbArray *geometry;
    EmbLayer layer[EMB_MAX_LAYERS];
    int currentColorIndex;

    EmbString design_name;
    EmbString category;
    EmbString author;
    EmbString keywords;
    EmbString comments;
} EmbPattern;

/* . */
typedef struct EmbFormatList_
{
    EmbString extension;
    EmbString description;
    char reader_state;
    char writer_state;
    int type;
    int color_only;
    int check_for_color_file;
    int write_external_color_file;
} EmbFormatList;

/* Thread colors that are subject to change are loaded at runtime,
 * allowing us to update them as they change.
 *
 * However, in-builts that use indicies like the DXF, SVG or HUS
 * tables are compiled in. This should help with embedded compatibility
 * in both cases.
 */
typedef struct BRAND {
    thread_color *codes;
    int length;
    EmbString label;
} EmbBrand;

/* . */
typedef struct EmbStackElement_ {
    int data_type;
    int attribute;
    int i;
    float r;
    char s[100];
} EmbStackElement;

/* This uses about 100kb per instance because it's not dynamic. */
typedef struct EmbStack_ {
    EmbStackElement stack[1000];
    int position;
} EmbStack;

/* double-indirection file allocation table references */
typedef struct _bcf_file_difat
{
    unsigned int fatSectorCount;
    unsigned int fatSectorEntries[109];
    unsigned int sectorSize;
} bcf_file_difat;

/* . */
typedef struct _bcf_file_fat
{
    int          fatEntryCount;
    unsigned int fatEntries[255]; /* maybe make this dynamic */
    unsigned int numberOfEntriesInFatSector;
} bcf_file_fat;

/* . */
typedef struct _bcf_directory_entry
{
    char directoryEntryName[32];
    unsigned short directoryEntryNameLength;
    uint8_t objectType;
    uint8_t colorFlag;
    unsigned int leftSiblingId;
    unsigned int                 rightSiblingId;
    unsigned int                 childId;
    uint8_t                CLSID[16];
    unsigned int                 stateBits;
    uint32_t creationTime[6];
    uint32_t modifiedTime[6];
    unsigned int                 startingSectorLocation;
    /* streamSize should be long long but in our case we shouldn't need it,
     * and hard to support on c89 cross platform. */
    unsigned long                streamSize;
    /* Store the high int of streamsize. */
    unsigned int                 streamSizeHigh;
    struct _bcf_directory_entry* next;
} bcf_directory_entry;

/* TODO: possibly add a directory tree in the future.
 */
typedef struct _bcf_directory
{
    bcf_directory_entry* dirEntries;
    unsigned int         maxNumberOfDirectoryEntries;
} bcf_directory;

/* TODO: CLSID should be a separate type.
 */
typedef struct _bcf_file_header
{
    uint8_t  signature[8];
    uint8_t  CLSID[16];
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

/* . */
typedef struct _bcf_file
{
    bcf_file_header header;   /* The header for the CompoundFile */
    bcf_file_difat* difat;    /* The "Double Indirect FAT" for the CompoundFile */
    bcf_file_fat* fat;        /* The File Allocation Table for the Compound File */
    bcf_directory* directory; /* The directory for the CompoundFile */
} bcf_file;

/* . */
typedef struct _vp3Hoop
{
    int right;
    int bottom;
    int left;
    int top;
    int threadLength;
    char unknown2;
    uint8_t numberOfColors;
    unsigned short unknown3;
    int unknown4;
    int numberOfBytesRemaining;

    int xOffset;
    int yOffset;

    uint8_t byte1;
    uint8_t byte2;
    uint8_t byte3;

    /* Centered hoop dimensions */
    int right2;
    int left2;
    int bottom2;
    int top2;

    int width;
    int height;
} vp3Hoop;

/* . */
typedef struct ThredHeader_     /* thred file header */
{
    unsigned int sigVersion;    /* signature and version */
    unsigned int length;        /* length of ThredHeader + length of stitch data */
    unsigned short numStiches;  /* number of stitches */
    unsigned short hoopSize;    /* size of hoop */
    unsigned short reserved[7]; /* reserved for expansion */
} ThredHeader;

/* . */
typedef struct ThredExtension_  /* thred v1.0 file header extension */
{
    float hoopX;                /* hoop size x dimension in 1/6 mm units */
    float hoopY;                /* hoop size y dimension in 1/6 mm units */
    float stitchGranularity;    /* stitches per millimeter--not implemented */
    char creatorName[50];       /* name of the file creator */
    char modifierName[50];      /* name of last file modifier */
    char auxFormat;             /* auxiliary file format, 0=PCS,1=DST,2=PES */
    char reserved[31];          /* reserved for expansion */
} ThredExtension;

/* . */
typedef struct SubDescriptor_
{
    int someNum;      /* \todo better variable naming */
    int someInt;      /* \todo better variable naming */
    int someOtherInt; /* \todo better variable naming */
    char* colorCode;
    char* colorName;
} SubDescriptor;

/* . */
typedef struct VipHeader_ {
    int magicCode;
    int numberOfStitches;
    int numberOfColors;
    short postitiveXHoopSize;
    short postitiveYHoopSize;
    short negativeXHoopSize;
    short negativeYHoopSize;
    int attributeOffset;
    int xOffset;
    int yOffset;
    uint8_t stringVal[8];
    short unknown;
    int colorLength;
} VipHeader;

/* . */
typedef enum
{
    CSV_EXPECT_NULL,
    CSV_EXPECT_QUOTE1,
    CSV_EXPECT_QUOTE2,
    CSV_EXPECT_COMMA
} CSV_EXPECT;

/* . */
typedef enum
{
    CSV_MODE_NULL,
    CSV_MODE_COMMENT,
    CSV_MODE_VARIABLE,
    CSV_MODE_THREAD,
    CSV_MODE_STITCH
} CSV_MODE;

/* . */
typedef struct StxThread_
{
    char* colorCode;
    char* colorName;
    char* sectionName;
    SubDescriptor* subDescriptors;
    EmbColor stxColor;
} StxThread;

/* . */
typedef struct SvgAttribute_
{
    char* name;
    char* value;
} SvgAttribute;

/* . */
typedef struct Huffman {
    int default_value;
    int lengths[1000];
    int nlengths;
    int table[1000];
    int table_width;
    int ntable;
} huffman;

/* . */
typedef struct Compress {
    int bit_position;
    char *input_data;
    int input_length;
    int bits_total;
    int block_elements;
    huffman character_length_huffman;
    huffman character_huffman;
    huffman distance_huffman;
} compress;

/* Function Declarations
 *****************************************************************************/
EMB_PUBLIC void to_flag(char **argv, int argc, int i);
EMB_PUBLIC void formats(void);
EMB_PUBLIC int emb_identify_format(const char *ending);
EMB_PUBLIC int convert(const char *inf, const char *outf);

EMB_PUBLIC EmbVector emb_vector(EmbReal x, EmbReal y);

EMB_PUBLIC char read_n_bytes(FILE *file, uint8_t *data, unsigned int length);
EMB_PUBLIC bool string_equal(char *a, const char *b);
EMB_PUBLIC int parse_floats(const char *line, float result[], int n);
EMB_PUBLIC int parse_vector(const char *line, EmbVector *v);
EMB_PUBLIC bool valid_rgb(float r, float g, float b);
EMB_PUBLIC int table_length(char *s[]);
EMB_PUBLIC uint8_t *load_file(char *fname);
EMB_PUBLIC bool int32_underflow(int64_t a, int64_t b);
EMB_PUBLIC bool int32_overflow(int64_t a, int64_t b);
EMB_PUBLIC int round_to_multiple(bool roundUp, int numToRound, int multiple);
EMB_PUBLIC void debug_message(const char *msg, ...);
EMB_PUBLIC bool valid_file_format(char *fileName);
EMB_PUBLIC int get_id(char *data[], char *label);

/* Scripting */
EMB_PUBLIC void execute_postscript(EmbStack *stack, char line[200]);
EMB_PUBLIC int emb_repl(void);
EMB_PUBLIC void emb_processor(char *state, const char *program, int program_length);
EMB_PUBLIC int emb_compiler(const char *program, int language, char *compiled_program);
EMB_PUBLIC void emb_actuator(EmbPattern *pattern, const char *program, int language);

/* Colors */
EMB_PUBLIC EmbColor embColor_make(uint8_t r, uint8_t g, uint8_t b);
EMB_PUBLIC EmbColor embColor_fromHexStr(char* val);
EMB_PUBLIC int embColor_distance(EmbColor a, EmbColor b);

/* Arrays */
EMB_PUBLIC EmbArray* emb_array_create(int type);
EMB_PUBLIC int emb_array_resize(EmbArray *g);
EMB_PUBLIC void emb_array_copy(EmbArray *dst, EmbArray *src);
EMB_PUBLIC int emb_array_add_geometry(EmbArray *a, EmbGeometry g);
EMB_PUBLIC int emb_array_add_arc(EmbArray* g, EmbArc arc);
EMB_PUBLIC int emb_array_add_circle(EmbArray* g, EmbCircle circle);
EMB_PUBLIC int emb_array_add_ellipse(EmbArray* g, EmbEllipse ellipse);
EMB_PUBLIC int emb_array_add_flag(EmbArray* g, int flag);
EMB_PUBLIC int emb_array_addLine(EmbArray* g, EmbLine line);
EMB_PUBLIC int emb_array_addRect(EmbArray* g, EmbRect rect);
EMB_PUBLIC int emb_array_addPath(EmbArray* g, EmbPath p);
EMB_PUBLIC int emb_array_addPoint(EmbArray* g, EmbPoint p);
EMB_PUBLIC int emb_array_addPolygon(EmbArray* g, EmbPolygon p);
EMB_PUBLIC int emb_array_addPolyline(EmbArray* g, EmbPolyline p);
/* EMB_PUBLIC int emb_array_addSpline(EmbArray* g, EmbSpline p); */
EMB_PUBLIC int emb_array_addStitch(EmbArray* g, EmbStitch st);
EMB_PUBLIC int emb_array_addThread(EmbArray* g, EmbThread p);
EMB_PUBLIC int emb_array_addVector(EmbArray* g, EmbVector);
EMB_PUBLIC void emb_array_free(EmbArray* p);

EMB_PUBLIC EmbLine emb_line_make(EmbReal x1, EmbReal y1, EmbReal x2, EmbReal y2);

EMB_PUBLIC EmbVector emb_line_normalVector(EmbLine line, int clockwise);
EMB_PUBLIC EmbVector emb_line_intersectionPoint(EmbLine line1, EmbLine line2, int *error_code);

EMB_PUBLIC int emb_find_nearest_color(EmbColor color, EmbColor* colors, int n_colors);
EMB_PUBLIC int emb_find_nearest_thread(EmbColor color, EmbThread* threads, int n_threads);
EMB_PUBLIC EmbThread emb_get_random_thread(void);

EMB_PUBLIC EmbVector emb_vector_normalize(EmbVector vector);
EMB_PUBLIC EmbVector emb_vector_scale(EmbVector vector, EmbReal magnitude);
EMB_PUBLIC EmbVector emb_vector_add(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbVector emb_vector_average(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbVector emb_vector_subtract(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbReal emb_vector_dot(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbReal emb_vector_cross(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbVector emb_vector_transpose_product(EmbVector v1, EmbVector v2);
EMB_PUBLIC EmbReal emb_vector_length(EmbVector vector);
EMB_PUBLIC EmbReal emb_vector_relativeX(EmbVector a1, EmbVector a2, EmbVector a3);
EMB_PUBLIC EmbReal emb_vector_relativeY(EmbVector a1, EmbVector a2, EmbVector a3);
EMB_PUBLIC EmbReal emb_vector_angle(EmbVector v);
EMB_PUBLIC EmbReal emb_vector_distance(EmbVector a, EmbVector b);
EMB_PUBLIC EmbVector emb_vector_unit(EmbReal angle);

EMB_PUBLIC EmbGeometry emb_arc(EmbReal, EmbReal, EmbReal, EmbReal, EmbReal, EmbReal);
EMB_PUBLIC char emb_arc_clockwise(EmbGeometry arc);

EMB_PUBLIC EmbGeometry emb_circle(EmbReal x, EmbReal y, EmbReal r);
EMB_PUBLIC int getCircleCircleIntersections(
     EmbCircle c0, EmbCircle c1, EmbVector *v0, EmbVector *v1);
EMB_PUBLIC int getCircleTangentPoints(
     EmbCircle c, EmbVector p, EmbVector *v0, EmbVector *v1);

EMB_PUBLIC EmbEllipse embEllipse_init(void);
EMB_PUBLIC EmbEllipse embEllipse_make(EmbReal cx, EmbReal cy, EmbReal rx, EmbReal ry);
EMB_PUBLIC EmbReal embEllipse_diameterX(EmbEllipse ellipse);
EMB_PUBLIC EmbReal embEllipse_diameterY(EmbEllipse ellipse);
EMB_PUBLIC EmbReal embEllipse_area(EmbEllipse ellipse);
EMB_PUBLIC EmbReal embEllipse_perimeter(EmbEllipse ellipse);

EMB_PUBLIC EmbImage embImage_create(int, int);
EMB_PUBLIC void embImage_read(EmbImage *image, char *fname);
EMB_PUBLIC int embImage_write(EmbImage *image, char *fname);
EMB_PUBLIC void embImage_free(EmbImage *image);

EMB_PUBLIC EmbRect emb_rect(EmbReal, EmbReal, EmbReal, EmbReal);
EMB_PUBLIC EmbReal embRect_area(EmbRect);

EMB_PUBLIC int threadColor(const char*, int brand);
EMB_PUBLIC int threadColorNum(unsigned int color, int brand);
EMB_PUBLIC const char* threadColorName(unsigned int color, int brand);

EMB_PUBLIC void embTime_initNow(EmbTime* t);
EMB_PUBLIC EmbTime embTime_time(EmbTime* t);

EMB_PUBLIC int emb_generate_satin_outline(EmbArray* lines,
    EmbReal thickness, EmbSatinOutline* result);
EMB_PUBLIC EmbArray* emb_satin_outline_render(EmbSatinOutline* result,
    EmbReal density);

EMB_PUBLIC EmbGeometry *emb_geometry_init(int type_in);
EMB_PUBLIC void emb_geometry_free(EmbGeometry *obj);
EMB_PUBLIC void emb_geometry_move(EmbGeometry *obj, EmbVector delta);
EMB_PUBLIC EmbRect embGeometry_boundingRect(EmbGeometry *obj);
EMB_PUBLIC void emb_vulcanize(EmbGeometry *obj);

EMB_PUBLIC EmbPattern* emb_pattern_create(void);
EMB_PUBLIC void emb_pattern_hideStitchesOverLength(EmbPattern* p, int length);
EMB_PUBLIC void emb_pattern_fixColorCount(EmbPattern* p);
EMB_PUBLIC int emb_pattern_addThread(EmbPattern* p, EmbThread thread);
EMB_PUBLIC void emb_pattern_addStitchAbs(EmbPattern* p, EmbReal x, EmbReal y,
    int flags, int isAutoColorIndex);
EMB_PUBLIC void emb_pattern_addStitchRel(EmbPattern* p, EmbReal dx, EmbReal dy, int flags, int isAutoColorIndex);
EMB_PUBLIC void emb_pattern_changeColor(EmbPattern* p, int index);
EMB_PUBLIC void emb_pattern_free(EmbPattern* p);
EMB_PUBLIC void emb_pattern_print(EmbPattern *pattern);
EMB_PUBLIC void emb_pattern_scale(EmbPattern* p, EmbReal scale);
EMB_PUBLIC EmbReal emb_pattern_shortest_stitch(EmbPattern *pattern);
EMB_PUBLIC EmbReal emb_pattern_longest_stitch(EmbPattern *pattern);
EMB_PUBLIC void emb_pattern_lengthHistogram(EmbPattern *pattern, int *bin, int NUMBINS);
EMB_PUBLIC int emb_pattern_realStitches(EmbPattern *pattern);
EMB_PUBLIC int emb_pattern_jumpStitches(EmbPattern *pattern);
EMB_PUBLIC int emb_pattern_trimStitches(EmbPattern *pattern);
EMB_PUBLIC EmbRect emb_pattern_bounds(EmbPattern* p);
EMB_PUBLIC void emb_pattern_flipHorizontal(EmbPattern* p);
EMB_PUBLIC void emb_pattern_flipVertical(EmbPattern* p);
EMB_PUBLIC void emb_pattern_flip(EmbPattern* p, int horz, int vert);
EMB_PUBLIC void emb_pattern_combineJumpStitches(EmbPattern* p);
EMB_PUBLIC void emb_pattern_correctForMaxStitchLength(EmbPattern* p, EmbReal maxStitchLength, EmbReal maxJumpLength);
EMB_PUBLIC void emb_pattern_center(EmbPattern* p);
EMB_PUBLIC void emb_pattern_loadExternalColorFile(EmbPattern* p, const char* fileName);
EMB_PUBLIC void emb_pattern_convertGeometry(EmbPattern* p);
EMB_PUBLIC void emb_pattern_details(EmbPattern *p);
EMB_PUBLIC EmbPattern *emb_pattern_combine(EmbPattern *p1, EmbPattern *p2);
EMB_PUBLIC int emb_pattern_color_count(EmbPattern *pattern, EmbColor startColor);
EMB_PUBLIC void emb_pattern_end(EmbPattern* p);
EMB_PUBLIC void emb_pattern_crossstitch(EmbPattern *pattern, EmbImage *, int threshhold);
EMB_PUBLIC void emb_pattern_horizontal_fill(EmbPattern *pattern, EmbImage *, int threshhold);
EMB_PUBLIC int emb_pattern_render(EmbPattern *pattern, char *fname);
EMB_PUBLIC int emb_pattern_simulate(EmbPattern *pattern, char *fname);

EMB_PUBLIC void emb_add_circle(EmbPattern* p, EmbCircle obj);
EMB_PUBLIC void emb_add_ellipse(EmbPattern* p, EmbEllipse obj);
EMB_PUBLIC void emb_add_line(EmbPattern* p, EmbLine obj);
EMB_PUBLIC void emb_add_path(EmbPattern* p, EmbPath obj);
EMB_PUBLIC void emb_pattern_addPointAbs(EmbPattern* p, EmbPoint obj);
EMB_PUBLIC void emb_pattern_addPolygonAbs(EmbPattern* p, EmbPolygon obj);
EMB_PUBLIC void emb_pattern_addPolylineAbs(EmbPattern* p, EmbPolyline obj);
EMB_PUBLIC void emb_pattern_addRectAbs(EmbPattern* p, EmbRect obj);

EMB_PUBLIC void emb_copy_stitches_to_polylines(EmbPattern* pattern);
EMB_PUBLIC void emb_copy_polylines_to_stitches(EmbPattern* pattern);
EMB_PUBLIC void emb_move_stitches_to_polylines(EmbPattern* pattern);
EMB_PUBLIC void emb_move_polylines_to_stitches(EmbPattern* pattern);

EMB_PUBLIC char emb_pattern_read(EmbPattern *pattern, const char* fileName, int format);
EMB_PUBLIC char emb_pattern_write(EmbPattern *pattern, const char* fileName, int format);

EMB_PUBLIC char emb_pattern_readAuto(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char emb_pattern_writeAuto(EmbPattern *pattern, const char* fileName);

EMB_PUBLIC int emb_round(EmbReal x);
EMB_PUBLIC EmbReal radians(EmbReal degree);
EMB_PUBLIC EmbReal degrees(EmbReal radian);

/* ---------------------------------- Geometry ----------------------------- */

EMB_PUBLIC int emb_pattern_real_count(EmbPattern *pattern);
EMB_PUBLIC int emb_pattern_count_type(EmbPattern *pattern, int flags);
EMB_PUBLIC void emb_color_histogram(EmbPattern *pattern, int **bins);
EMB_PUBLIC void emb_length_histogram(EmbPattern *pattern, int *bins);
EMB_PUBLIC double emb_total_thread_length(EmbPattern *pattern);
EMB_PUBLIC double emb_total_thread_of_color(EmbPattern *pattern, int thread_index);

EMB_PUBLIC int emb_approx(EmbVector point1, EmbVector point2);

EMB_PUBLIC EmbVector scale_and_rotate(EmbVector v, double angle, double scale);

/* Get attributes */
EMB_PUBLIC EmbReal emb_angle(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_arc_length(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_area(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbVector emb_center(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbVector emb_chord(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_chord_length(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_diameter(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_diameter_major(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_diameter_minor(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbVector emb_end(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_height(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_radius(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_radius_major(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_radius_minor(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_sagitta(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbVector emb_start(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_width(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbVector emb_quadrant(EmbGeometry *geometry, int degrees, EmbError *error);
EMB_PUBLIC EmbReal emb_start_angle(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_end_angle(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_included_angle(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC char emb_clockwise(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_circumference(EmbGeometry *geometry, EmbError *error);
EMB_PUBLIC EmbReal emb_included_angle(EmbGeometry *geometry, EmbError *error);

/* Set attributes */
EMB_PUBLIC EmbError emb_set_area(EmbGeometry *geometry, EmbReal area);
EMB_PUBLIC EmbError emb_set_start_angle(EmbGeometry *geometry, EmbReal angle);
EMB_PUBLIC EmbError emb_set_end_angle(EmbGeometry *geometry, EmbReal angle);
EMB_PUBLIC EmbError emb_set_start_point(EmbGeometry *geometry, EmbVector point);
EMB_PUBLIC EmbError emb_set_mid_point(EmbGeometry *geometry, EmbVector point);
EMB_PUBLIC EmbError emb_set_end_point(EmbGeometry *geometry, EmbVector point);
EMB_PUBLIC EmbError emb_set_diameter(EmbGeometry *geometry, EmbReal diameter);
EMB_PUBLIC EmbError emb_set_circumference(EmbGeometry *geometry, EmbReal circumference);
EMB_PUBLIC EmbError emb_set_radius(EmbGeometry *geometry, EmbReal radius);
EMB_PUBLIC EmbError emb_set_radius_major(EmbGeometry *geometry, EmbReal radius);
EMB_PUBLIC EmbError emb_set_radius_minor(EmbGeometry *geometry, EmbReal radius);
EMB_PUBLIC EmbError emb_set_diameter_major(EmbGeometry *geometry, EmbReal diameter);
EMB_PUBLIC EmbError emb_set_diameter_minor(EmbGeometry *geometry, EmbReal diameter);

EMB_PUBLIC char *emb_get_svg_token(char *svg, char token[MAX_STRING_LENGTH]);
EMB_PUBLIC char *emb_get_svg_vector(char *svg, EmbVector *v);

/* Internal function declarations.
 * ----------------------------------------------------------------------------
 * TODO: UTF-8 support.
 */
EMB_PUBLIC int string_rchar(const char *s1, char c);
EMB_PUBLIC void char_ptr_to_string(char *dst, char *src);

/* Utility Functions: merge first three with string library */
EMB_PUBLIC int stringInArray(const char *s, const char **array);
EMB_PUBLIC char *copy_trim(char const *s);
EMB_PUBLIC char* emb_optOut(EmbReal num, char* str);
EMB_PUBLIC void safe_free(void *data);

/* DIFAT functions */
EMB_PUBLIC unsigned int entriesInDifatSector(bcf_file_difat* fat);
EMB_PUBLIC bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize);
EMB_PUBLIC void loadFatFromSector(bcf_file_fat* fat, FILE* file);
EMB_PUBLIC void bcf_file_fat_free(bcf_file_fat** fat);
EMB_PUBLIC bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries);
EMB_PUBLIC void bcf_directory_free(bcf_directory** dir);
EMB_PUBLIC unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat);
void bcf_file_difat_free(bcf_file_difat* difat);
bcf_file_header bcfFileHeader_read(FILE* file);
int bcfFileHeader_isValid(bcf_file_header header);
void bcf_file_free(bcf_file* bcfFile);

double emb_stitch_length(EmbStitch prev_st, EmbStitch st);

int emb_readline(FILE* file, char *line, int maxLength);

int16_t emb_read_i16(FILE* f);
uint16_t emb_read_u16(FILE* f);
int32_t emb_read_i32(FILE* f);
uint32_t emb_read_u32(FILE* f);
int16_t emb_read_i16be(FILE* f);
uint16_t emb_read_u16be(FILE* f);
int32_t emb_read_i32be(FILE* f);
uint32_t emb_read_u32be(FILE* f);

void emb_write_i16(FILE* f, int16_t data);
void emb_write_u16(FILE* f, uint16_t data);
void emb_write_i32(FILE* f, int32_t data);
void emb_write_u32(FILE* f, uint32_t data);
void emb_write_i16be(FILE* f, int16_t data);
void emb_write_u16be(FILE* f, uint16_t data);
void emb_write_i32be(FILE* f, int32_t data);
void emb_write_u32be(FILE* f, uint32_t data);

void embColor_read(void *f, EmbColor *c, int toRead);
void embColor_write(void *f, EmbColor c, int toWrite);

/* Encoding/decoding and compression functions. */
int hus_compress(char* input, int size, char* output, int *out_size);
int hus_decompress(char* input, int size, char* output, int *out_size);

void huffman_build_table(huffman *h);
int *huffman_table_lookup(huffman *h, int byte_lookup, int *lengths);

int compress_get_bits(compress *c, int length);
int compress_pop(compress *c, int bit_count);
int compress_read_variable_length(compress *c);
void compress_load_character_length_huffman(compress *c);
void compress_load_character_huffman(compress *c);
void compress_load_distance_huffman(compress *c);
void compress_load_block(compress *c);
int compress_get_token(compress *c);
int compress_get_position(compress *c);

/* Function Declarations */
void readPecStitches(EmbPattern* pattern, FILE* file);
void writePecStitches(EmbPattern* pattern, FILE* file, const char* filename);

void pfaffEncode(FILE* file, int x, int y, int flags);

int read_bytes(FILE *file, int n, char *str);
int write_bytes(FILE *file, int n, char *str);

int bcfFile_read(FILE* file, bcf_file* bcfFile);
void* GetFile(bcf_file* bcfFile, FILE* file, char* fileToFind);

void binaryReadString(FILE* file, char *buffer, int maxLength);
void binaryReadUnicodeString(FILE* file, char *buffer, const int stringLength);

void fpad(FILE* f, char c, int n);

void write_24bit(FILE* file, int);
int check_header_present(FILE* file, int minimum_header_length);

bcf_file_difat* bcf_difat_create(FILE* file, unsigned int fatSectors, const unsigned int sectorSize);
unsigned int readFullSector(FILE* file, bcf_file_difat* bcfFile, unsigned int* numberOfDifatEntriesStillToRead);
bcf_directory_entry* CompoundFileDirectoryEntry(FILE* file);
void readNextSector(FILE* file, bcf_directory* dir);

void write_24bit(FILE* file, int);

EmbReal pfaffDecode(uint8_t a1, uint8_t a2, uint8_t a3);

int decodeNewStitch(uint8_t value);

uint8_t mitEncodeStitch(EmbReal value);
int mitDecodeStitch(uint8_t value);

void encode_t01_record(uint8_t b[3], int x, int y, int flags);
int decode_t01_record(uint8_t b[3], int *x, int *y, int *flags);

int encode_tajima_ternary(uint8_t b[3], int x, int y);
void decode_tajima_ternary(uint8_t b[3], int *x, int *y);

/* NON-MACRO CONSTANTS
 ******************************************************************************/

extern EmbFormatList formatTable[numberOfFormats];
extern const EmbReal embConstantPi;
extern EmbBrand brand_codes[100];
extern EmbThread black_thread;
extern int emb_verbose;
extern const char *version_string;
extern const char *emb_error_desc[];
extern const EmbThread dxf_colors[];
extern const EmbThread jef_colors[];
extern const EmbThread hus_colors[];
extern const EmbThread pcm_colors[];
extern const EmbThread pec_colors[];
extern const EmbThread shv_colors[];
extern const char imageWithFrame[38][48];

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBEMBROIDERY_HEADER__ */

#ifdef LIBEMBROIDERY_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>

/*
 * Script section
 */

static EmbPattern *focussed_pattern = NULL;

/* Tests if char * matches a fixed string, often from compiled-in program
 * data.
 */
bool
string_equal(char *a, const char *b)
{
    return (strncmp(a, b, MAX_STRING_LENGTH) == 0);
}

/* . */
int
parse_floats(const char *line, float result[], int n)
{
    char substring[MAX_STRING_LENGTH];
    const char *c;
    int i = 0;
    int pos = 0;
    for (c=line; *c; c++) {
        substring[pos] = *c;
        if (*c == ',' || *c == ' ') {
            substring[pos] = 0;
            result[i] = atof(substring);
            pos = 0;
            i++;
            if (i > n-1) {
                return -1;
            }
        }
        else {
            pos++;
        }
    }
    substring[pos] = 0;
    result[i] = atof(substring);
    return i+1;
}

int
parse_vector(const char *line, EmbVector *v)
{
    float v_[2];
    if (parse_floats(line, v_, 2) == 2) {
        return 0;
    }
    v->x = v_[0];
    v->y = v_[1];
    return 1;
}

/* . */
bool
valid_rgb(float r, float g, float b)
{
    if (isnan(r)) {
        return false;
    }
    if (isnan(g)) {
        return false;
    }
    if (isnan(b)) {
        return false;
    }
    if (r < 0 || r > 255) {
        return false;
    }
    if (g < 0 || g > 255) {
        return false;
    }
    if (b < 0 || b > 255) {
        return false;
    }
    return true;
}

/* This version of string_array_length does not protect against the END_SYMBOL
 * missing, because it is only to be used for compiled in constant tables.
 *
 * For string tables edited during run time, the END_SYMBOL is checked for during loops.
 */
int
table_length(char *s[])
{
    int i;
    for (i=0; i<1000; i++) {
        if (s[i][0] == END_SYMBOL[0]) {
            if (!strncmp(s[i], END_SYMBOL, MAX_STRING_LENGTH)) {
                break;
            }
        }
    }
    if (i == 1000) {
        puts("ERROR: Table is missing END_SYMBOL.");
        return 1000;
    }
    return i;
}

/* . */
unsigned char *
load_file(char *fname)
{
    FILE *f = fopen(fname, "r");
    if (!f) {
        printf("ERROR: Failed to open \"%s\".\n", fname);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    size_t length = ftell(f);
    unsigned char *data = malloc(length+1);
    fseek(f, 0, SEEK_SET);
    if (!read_n_bytes(f, data, length)) {
        fclose(f);
        return NULL;
    }
    fclose(f);
    return data;
}


/* . */
bool
int32_underflow(int64_t a, int64_t b)
{
    int64_t c;
    assert(LLONG_MAX>INT_MAX);
    c = (int64_t)a-b;
    if (c < INT_MIN || c > INT_MAX) {
        return true;
    }
    return false;
}

/* . */
bool
int32_overflow(int64_t a, int64_t b)
{
    int64_t c;
    assert(LLONG_MAX>INT_MAX);
    c = (int64_t)a+b;
    if (c < INT_MIN || c > INT_MAX) {
        return true;
    }
    return false;
}

/* . */
int
round_to_multiple(bool roundUp, int numToRound, int multiple)
{
    if (multiple == 0) {
        return numToRound;
    }
    int remainder = numToRound % multiple;
    if (remainder == 0) {
        return numToRound;
    }

    if (numToRound < 0 && roundUp) {
        return numToRound - remainder;
    }
    if (roundUp) {
        return numToRound + multiple - remainder;
    }
    /* else round down */
    if (numToRound < 0 && !roundUp) {
        return numToRound - multiple - remainder;
    }
    return numToRound - remainder;
}

/* Formats each message with a timestamp. */
void
debug_message(const char *msg, ...)
{
    char buffer[MAX_STRING_LENGTH], fname[MAX_STRING_LENGTH];
    time_t t;
    struct tm* tm_info;
    sprintf(fname, "debug.log");
    FILE *f = fopen(fname, "a");
    if (!f) {
        printf("Failed to write to debug.log.");
        return;
    }
    t = time(NULL);
    tm_info = localtime(&t);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(f, "%s ", buffer);

    va_list args;
    va_start(args, msg);
    vfprintf(f, msg, args);
    va_end(args);

    fprintf(f, "\n");
    fclose(f);
}

/* . */
bool
valid_file_format(char *fileName)
{
    if (emb_identify_format(fileName) >= 0) {
        return true;
    }
    return false;
}

/*
 * Compression algorithms used in machine embroidery file formats.
 *
 * Only uses source from this directory or standard C libraries,
 * not including POSIX headers like unistd since this library
 * needs to support non-POSIX systems like Windows.
 *
 * -----------------------------------------------------------------------------
 *
 * This is section on compression is a work in progress.
 *
 * Thanks to Jason Weiler for describing the binary formats of the HUS and
 * VIP formats at:
 *
 * http://www.jasonweiler.com/HUSandVIPFileFormatInfo.html
 *
 * Further thanks to github user tatarize for solving the mystery of the
 * compression in:
 *
 * https://github.com/EmbroidePy/pyembroidery
 *
 * with a description of that work here:
 *
 * https://stackoverflow.com/questions/7852670/greenleaf-archive-library
 *
 * This is based on their work.
 */

int huffman_lookup_data[2];

/*!
 * Compress data "data" of length "length" to "output" with length "output_length".
 * Returns whether it was successful as an int.
 *
 * This avoids the now unnecessary compression by placing a
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

/* These next 2 functions represent the Huffman class in tartarize's code.
 */
void
huffman_build_table(huffman *h)
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

/* Lookup a byte_lookup in huffman table a h return result
 * as two bytes using the memory huffman_lookup_data.
 */
int *huffman_lookup(huffman h, int byte_lookup)
{
    int *out = huffman_lookup_data;
    if (h.table_width == 0) {
        out[0] = h.default_value;
        out[1] = 0;
        return out;
    }
    out[0] = h.table[byte_lookup >> (16-h.table_width)];
    out[1] = h.lengths[out[0]];
    return out;
}

/* These functions represent the EmbCompress class. */
void compress_init()
{

}

/* Return bits from compress struct pointed to by "c" of length "length". */
int
compress_get_bits(compress *c, int length)
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

/* a c a bit_count . Returns.
 */
int
compress_pop(compress *c, int bit_count)
{
    int value = compress_get_bits(c, bit_count);
    c->bit_position += bit_count;
    return value;
}

/* a c a bit_count. Returns.
 */
int
compress_peek(compress *c, int bit_count)
{
    return compress_get_bits(c, bit_count);
}

/* a c. Returns.
 */
int
compress_read_variable_length(compress *c)
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

/* a c  . Returns.
 */
void
compress_load_character_length_huffman(compress *c)
{
    int count;
    count = compress_pop(c, 5);
    if (count == 0) {
        c->character_length_huffman.default_value = compress_pop(c, 5);
    }
    else {
        int i;
        for (i = 0; i < count; i++) {
            c->character_length_huffman.lengths[i] = 0;
        }
        for (i = 0; i < count; i++) {
            if (i==3) {
                i += compress_pop(c, 2);
            }
            c->character_length_huffman.lengths[i] = compress_read_variable_length(c);
        }
    }
    huffman_build_table(&(c->character_length_huffman));
}

/* Load character table to compress struct a c. Returns nothing.
 */
void
compress_load_character_huffman(compress *c)
{
    int count;
    count = compress_pop(c, 9);
    if (count == 0) {
        c->character_huffman.default_value = compress_pop(c, 9);
    }
    else {
        int i = 0;
        while (i < count) {
            int *h = huffman_lookup(c->character_length_huffman,
                compress_peek(c, 16));
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
                c->character_huffman.lengths[i] = h[0] - 2;
                i++;
            }
        }
    }
    huffman_build_table(&(c->character_huffman));
}

/* a c . Returns nothing.
 */
void
compress_load_distance_huffman(compress *c)
{
    int count;
    count = compress_pop(c, 5);
    if (count == 0) {
        c->distance_huffman.default_value = compress_pop(c, 5);
    }
    else {
        int i;
        for (i = 0; i < count; i++) {
            c->distance_huffman.lengths[i] = compress_read_variable_length(c);
        }
    }
    huffman_build_table(&(c->distance_huffman));
}

/* a c . Returns nothing.
 */
void
compress_load_block(compress *c)
{
    c->block_elements = compress_pop(c, 16);
    compress_load_character_length_huffman(c);
    compress_load_character_huffman(c);
    compress_load_distance_huffman(c);
}

/* a c . Returns the token as an int.
 */
int
compress_get_token(compress *c)
{
    int *h;
    if (c->block_elements <= 0) {
        compress_load_block(c);
    }
    c->block_elements--;
    h = huffman_lookup(c->character_huffman, compress_peek(c, 16));
    c->bit_position += h[1];
    return h[0];
}

/* a c . Returns the position as an int.
 */
int
compress_get_position(compress *c)
{
    int *h, v;
    h = huffman_lookup(c->distance_huffman, compress_peek(c, 16));
    c->bit_position += h[1];
    if (h[0] == 0) {
        return 0;
    }
    v = h[0] - 1;
    v = (1<<v) + compress_pop(c, v);
    return v;
}

/* a data a length a output a output_length .
 * Returns whether the decompression was successful.
 */
int
hus_decompress(char *data, int length, char *output, int *output_length)
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
    safe_free(c);
    return 0;
}

/*!
 * \file data.c
 * \brief Thread colors referred to by machine files.
 *
 * Libembroidery 1.0.0-alpha
 * https://www.libembroidery.org
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright 2018-2025 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * -----------------------------------------------------------------------------
 *
 * Data
 */

const EmbThread arc_polyester_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread arc_rayon_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread coats_and_clark_rayon_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"},
};

const EmbThread dxf_colors[] = {
    {{0, 0, 0}, "BYBLOCK", "0"},
    {{255, 0, 0}, "red", "1"},
    {{255, 255, 0}, "yellow", "2"},
    {{0, 255, 0}, "green", "3"},
    {{0, 255, 255}, "cyan", "4"},
    {{0, 0, 255}, "blue", "5"},
    {{255, 0, 255}, "magenta", "6"},
    {{255, 255, 255}, "white", "7"},
    {{128, 128, 128}, "darkgray", "8"},
    {{192, 192, 192}, "lightgray", "9"},
    {{255, 0, 0}, "unknown", "10"},
    {{255, 127, 127}, "unknown", "11"},
    {{204, 0, 0}, "unknown", "12"},
    {{204, 102, 102}, "unknown", "13"},
    {{153, 0, 0}, "unknown", "14"},
    {{153, 76, 76}, "unknown", "15"},
    {{127, 0, 0}, "unknown", "16"},
    {{127, 63, 63}, "unknown", "17"},
    {{76, 0, 0}, "unknown", "18"},
    {{76, 38, 38}, "unknown", "19"},
    {{255, 63, 0}, "unknown", "20"},
    {{255, 159, 127}, "unknown", "21"},
    {{204, 51, 0}, "unknown", "22"},
    {{204, 127, 102}, "unknown", "23"},
    {{153, 38, 0}, "unknown", "24"},
    {{153, 95, 76}, "unknown", "25"},
    {{127, 31, 0}, "unknown", "26"},
    {{127, 79, 63}, "unknown", "27"},
    {{76, 19, 0}, "unknown", "28"},
    {{76, 47, 38}, "unknown", "29"},
    {{255, 127, 0}, "unknown", "30"},
    {{255, 191, 127}, "unknown", "31"},
    {{204, 102, 0}, "unknown", "32"},
    {{204, 153, 102}, "unknown", "33"},
    {{153, 76, 0}, "unknown", "34"},
    {{153, 114, 76}, "unknown", "35"},
    {{127, 63, 0}, "unknown", "36"},
    {{127, 95, 63}, "unknown", "37"},
    {{76, 38, 0}, "unknown", "38"},
    {{76, 57, 38}, "unknown", "39"},
    {{255, 191, 0}, "unknown", "40"},
    {{255, 223, 127}, "unknown", "41"},
    {{204, 153, 0}, "unknown", "42"},
    {{204, 178, 102}, "unknown", "43"},
    {{153, 114, 0}, "unknown", "44"},
    {{153, 133, 76}, "unknown", "45"},
    {{127, 95, 0}, "unknown", "46"},
    {{127, 111, 63}, "unknown", "47"},
    {{76, 57, 0}, "unknown", "48"},
    {{76, 66, 38}, "unknown", "49"},
    {{255, 255, 0}, "unknown", "50"},
    {{255, 255, 127}, "unknown", "51"},
    {{204, 204, 0}, "unknown", "52"},
    {{204, 204, 102}, "unknown", "53"},
    {{153, 153, 0}, "unknown", "54"},
    {{153, 153, 76}, "unknown", "55"},
    {{127, 127, 0}, "unknown", "56"},
    {{127, 127, 63}, "unknown", "57"},
    {{76, 76, 0}, "unknown", "58"},
    {{76, 76, 38}, "unknown", "59"},
    {{191, 255, 0}, "unknown", "60"},
    {{223, 255, 127}, "unknown", "61"},
    {{153, 204, 0}, "unknown", "62"},
    {{178, 204, 102}, "unknown", "63"},
    {{114, 153, 0}, "unknown", "64"},
    {{133, 153, 76}, "unknown", "65"},
    {{95, 127, 0}, "unknown", "66"},
    {{111, 127, 63}, "unknown", "67"},
    {{57, 76, 0}, "unknown", "68"},
    {{66, 76, 38}, "unknown", "69"},
    {{127, 255, 0}, "unknown", "70"},
    {{191, 255, 127}, "unknown", "71"},
    {{102, 204, 0}, "unknown", "72"},
    {{153, 204, 102}, "unknown", "73"},
    {{76, 153, 0}, "unknown", "74"},
    {{114, 153, 76}, "unknown", "75"},
    {{63, 127, 0}, "unknown", "76"},
    {{95, 127, 63}, "unknown", "77"},
    {{38, 76, 0}, "unknown", "78"},
    {{57, 76, 38}, "unknown", "79"},
    {{63, 255, 0}, "unknown", "80"},
    {{159, 255, 127}, "unknown", "81"},
    {{51, 204, 0}, "unknown", "82"},
    {{127, 204, 102}, "unknown", "83"},
    {{38, 153, 0}, "unknown", "84"},
    {{95, 153, 76}, "unknown", "85"},
    {{31, 127, 0}, "unknown", "86"},
    {{79, 127, 63}, "unknown", "87"},
    {{19, 76, 0}, "unknown", "88"},
    {{47, 76, 38}, "unknown", "89"},
    {{0, 255, 0}, "unknown", "90"},
    {{127, 255, 127}, "unknown", "91"},
    {{0, 204, 0}, "unknown", "92"},
    {{102, 204, 102}, "unknown", "93"},
    {{0, 153, 0}, "unknown", "94"},
    {{76, 153, 76}, "unknown", "95"},
    {{0, 127, 0}, "unknown", "96"},
    {{63, 127, 63}, "unknown", "97"},
    {{0, 76, 0}, "unknown", "98"},
    {{38, 76, 38}, "unknown", "99"},
    {{0, 255, 63}, "unknown", "100"},
    {{127, 255, 159}, "unknown", "101"},
    {{0, 204, 51}, "unknown", "102"},
    {{102, 204, 127}, "unknown", "103"},
    {{0, 153, 38}, "unknown", "104"},
    {{76, 153, 95}, "unknown", "105"},
    {{0, 127, 31}, "unknown", "106"},
    {{63, 127, 79}, "unknown", "107"},
    {{0, 76, 19}, "unknown", "108"},
    {{38, 76, 47}, "unknown", "109"},
    {{0, 255, 127}, "unknown", "110"},
    {{127, 255, 191}, "unknown", "111"},
    {{0, 204, 102}, "unknown", "112"},
    {{102, 204, 153}, "unknown", "113"},
    {{0, 153, 76}, "unknown", "114"},
    {{76, 153, 114}, "unknown", "115"},
    {{0, 127, 63}, "unknown", "116"},
    {{63, 127, 95}, "unknown", "117"},
    {{0, 76, 38}, "unknown", "118"},
    {{38, 76, 57}, "unknown", "119"},
    {{0, 255, 191}, "unknown", "120"},
    {{127, 255, 223}, "unknown", "121"},
    {{0, 204, 153}, "unknown", "122"},
    {{102, 204, 178}, "unknown", "123"},
    {{0, 153, 114}, "unknown", "124"},
    {{76, 153, 133}, "unknown", "125"},
    {{0, 127, 95}, "unknown", "126"},
    {{63, 127, 111}, "unknown", "127"},
    {{0, 76, 57}, "unknown", "128"},
    {{38, 76, 66}, "unknown", "129"},
    {{0, 255, 255}, "unknown", "130"},
    {{127, 255, 255}, "unknown", "131"},
    {{0, 204, 204}, "unknown", "132"},
    {{102, 204, 204}, "unknown", "133"},
    {{0, 153, 153}, "unknown", "134"},
    {{76, 153, 153}, "unknown", "135"},
    {{0, 127, 127}, "unknown", "136"},
    {{63, 127, 127}, "unknown", "137"},
    {{0, 76, 76}, "unknown", "138"},
    {{38, 76, 76}, "unknown", "139"},
    {{0, 191, 255}, "unknown", "140"},
    {{127, 223, 255}, "unknown", "141"},
    {{0, 153, 204}, "unknown", "142"},
    {{102, 178, 204}, "unknown", "143"},
    {{0, 114, 153}, "unknown", "144"},
    {{76, 133, 153}, "unknown", "145"},
    {{0, 95, 127}, "unknown", "146"},
    {{63, 111, 127}, "unknown", "147"},
    {{0, 57, 76}, "unknown", "148"},
    {{38, 66, 76}, "unknown", "149"},
    {{0, 127, 255}, "unknown", "150"},
    {{127, 191, 255}, "unknown", "151"},
    {{0, 102, 204}, "unknown", "152"},
    {{102, 153, 204}, "unknown", "153"},
    {{0, 76, 153}, "unknown", "154"},
    {{76, 114, 153}, "unknown", "155"},
    {{0, 63, 127}, "unknown", "156"},
    {{63, 95, 127}, "unknown", "157"},
    {{0, 38, 76}, "unknown", "158"},
    {{38, 57, 76}, "unknown", "159"},
    {{0, 63, 255}, "unknown", "160"},
    {{127, 159, 255}, "unknown", "161"},
    {{0, 51, 204}, "unknown", "162"},
    {{102, 127, 204}, "unknown", "163"},
    {{0, 38, 153}, "unknown", "164"},
    {{76, 95, 153}, "unknown", "165"},
    {{0, 31, 127}, "unknown", "166"},
    {{63, 79, 127}, "unknown", "167"},
    {{0, 19, 76}, "unknown", "168"},
    {{38, 47, 76}, "unknown", "169"},
    {{0, 0, 255}, "unknown", "170"},
    {{127, 127, 255}, "unknown", "171"},
    {{0, 0, 204}, "unknown", "172"},
    {{102, 102, 204}, "unknown", "173"},
    {{0, 0, 153}, "unknown", "174"},
    {{76, 76, 153}, "unknown", "175"},
    {{0, 0, 127}, "unknown", "176"},
    {{63, 63, 127}, "unknown", "177"},
    {{0, 0, 76}, "unknown", "178"},
    {{38, 38, 76}, "unknown", "179"},
    {{63, 0, 255}, "unknown", "180"},
    {{159, 127, 255}, "unknown", "181"},
    {{51, 0, 204}, "unknown", "182"},
    {{127, 102, 204}, "unknown", "183"},
    {{38, 0, 153}, "unknown", "184"},
    {{95, 76, 153}, "unknown", "185"},
    {{31, 0, 127}, "unknown", "186"},
    {{79, 63, 127}, "unknown", "187"},
    {{19, 0, 76}, "unknown", "188"},
    {{47, 38, 76}, "unknown", "189"},
    {{127, 0, 255}, "unknown", "190"},
    {{191, 127, 255}, "unknown", "191"},
    {{102, 0, 204}, "unknown", "192"},
    {{153, 102, 204}, "unknown", "193"},
    {{76, 0, 153}, "unknown", "194"},
    {{114, 76, 153}, "unknown", "195"},
    {{63, 0, 127}, "unknown", "196"},
    {{95, 63, 127}, "unknown", "197"},
    {{38, 0, 76}, "unknown", "198"},
    {{57, 38, 76}, "unknown", "199"},
    {{191, 0, 255}, "unknown", "200"},
    {{223, 127, 255}, "unknown", "201"},
    {{153, 0, 204}, "unknown", "202"},
    {{178, 102, 204}, "unknown", "203"},
    {{114, 0, 153}, "unknown", "204"},
    {{133, 76, 153}, "unknown", "205"},
    {{95, 0, 127}, "unknown", "206"},
    {{111, 63, 127}, "unknown", "207"},
    {{57, 0, 76}, "unknown", "208"},
    {{66, 38, 76}, "unknown", "209"},
    {{255, 0, 255}, "unknown", "210"},
    {{255, 127, 255}, "unknown", "211"},
    {{204, 0, 204}, "unknown", "212"},
    {{204, 102, 204}, "unknown", "213"},
    {{153, 0, 153}, "unknown", "214"},
    {{153, 76, 153}, "unknown", "215"},
    {{127, 0, 127}, "unknown", "216"},
    {{127, 63, 127}, "unknown", "217"},
    {{76, 0, 76}, "unknown", "218"},
    {{76, 38, 76}, "unknown", "219"},
    {{255, 0, 191}, "unknown", "220"},
    {{255, 127, 223}, "unknown", "221"},
    {{204, 0, 153}, "unknown", "222"},
    {{204, 102, 178}, "unknown", "223"},
    {{153, 0, 114}, "unknown", "224"},
    {{153, 76, 133}, "unknown", "225"},
    {{127, 0, 95}, "unknown", "226"},
    {{127, 63, 111}, "unknown", "227"},
    {{76, 0, 57}, "unknown", "228"},
    {{76, 38, 66}, "unknown", "229"},
    {{255, 0, 127}, "unknown", "230"},
    {{255, 127, 191}, "unknown", "231"},
    {{204, 0, 102}, "unknown", "232"},
    {{204, 102, 153}, "unknown", "233"},
    {{153, 0, 76}, "unknown", "234"},
    {{153, 76, 114}, "unknown", "235"},
    {{127, 0, 63}, "unknown", "236"},
    {{127, 63, 95}, "unknown", "237"},
    {{76, 0, 38}, "unknown", "238"},
    {{76, 38, 57}, "unknown", "239"},
    {{255, 0, 63}, "unknown", "240"},
    {{255, 127, 159}, "unknown", "241"},
    {{204, 0, 51}, "unknown", "242"},
    {{204, 102, 127}, "unknown", "243"},
    {{153, 0, 38}, "unknown", "244"},
    {{153, 76, 95}, "unknown", "245"},
    {{127, 0, 31}, "unknown", "246"},
    {{127, 63, 79}, "unknown", "247"},
    {{76, 0, 19}, "unknown", "248"},
    {{76, 38, 47}, "unknown", "249"},
    {{51, 51, 51}, "unknown", "250"},
    {{91, 91, 91}, "unknown", "251"},
    {{132, 132, 132}, "unknown", "252"},
    {{173, 173, 173}, "unknown", "253"},
    {{214, 214, 214}, "unknown", "254"},
    {{255, 255, 255}, "unknown", "255"},
    {{0, 0, 0}, "BYLAYER", "256"}
};

const EmbThread exquisite_polyester_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread fufu_polyester_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread fufu_rayon_colors[] = {
    {{252, 227, 0}, "Medium Yellow U", "543"},
    {{0, 0, 0}, "105C FIXME", "287"},
    {{0, 0, 0}, "108C FIXME", "544"},
    {{0, 0, 0}, "109C FIXME", "546"},
    {{0, 0, 0}, "122C FIXME", "522"},
    {{0, 0, 0}, "123C FIXME", "523"},
    {{0, 0, 0}, "124C FIXME", "502"},
    {{0, 0, 0}, "124C FIXME", "503"},
    {{0, 0, 0}, "125C FIXME", "562"},
    {{0, 0, 0}, "127C FIXME", "5205"},
    {{0, 0, 0}, "128C FIXME", "521"},
    {{0, 0, 0}, "129C FIXME", "501"},
    {{0, 0, 0}, "131C FIXME", "512"},
    {{0, 0, 0}, "136C FIXME", "532"},
    {{0, 0, 0}, "137C FIXME", "525"},
    {{0, 0, 0}, "137C FIXME", "533"},
    {{0, 0, 0}, "139C FIXME", "514"},
    {{0, 0, 0}, "140C FIXME", "564"},
    {{0, 0, 0}, "141C FIXME", "560"},
    {{0, 0, 0}, "144C FIXME", "711"},
    {{0, 0, 0}, "147C FIXME", "844"}
};

const EmbThread hemingworth_polyester_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread hus_colors[] = {
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 255}, "Blue", "TODO"},
    {{0, 255, 0}, "Light Green", "TODO"},
    {{255, 0, 0}, "Red", "TODO"},
    {{255, 0, 255}, "Purple", "TODO"},
    {{255, 255, 0}, "Yellow", "TODO"},
    {{127, 127, 127}, "Gray", "TODO"},
    {{51, 154, 255}, "Light Blue", "TODO"},
    {{51, 204, 102}, "Green", "TODO"},
    {{255, 127, 0}, "Orange", "TODO"},
    {{255, 160, 180}, "Pink", "TODO"},
    {{153, 75, 0}, "Brown", "TODO"},
    {{255, 255, 255}, "White", "TODO"},
    {{0, 0, 127}, "Dark Blue", "TODO"},
    {{0, 127, 0}, "Dark Green", "TODO"},
    {{127, 0, 0}, "Dark Red", "TODO"},
    {{255, 127, 127}, "Light Red", "TODO"},
    {{127, 0, 127}, "Dark Purple", "TODO"},
    {{255, 127, 255}, "Light Purple", "TODO"},
    {{200, 200, 0}, "Dark Yellow", "TODO"},
    {{255, 255, 153}, "Light Yellow", "TODO"},
    {{60, 60, 60}, "Dark Gray", "TODO"},
    {{192, 192, 192}, "Light Gray", "TODO"},
    {{232, 63, 0}, "Dark Orange", "TODO"},
    {{255, 165, 65}, "Light Orange", "TODO"},
    {{255, 102, 122}, "Dark Pink", "TODO"},
    {{255, 204, 204}, "Light Pink", "TODO"},
    {{115, 40, 0}, "Dark Brown", "TODO"},
    {{175, 90, 10}, "Light Brown", "TODO"}
};

const EmbThread isacord_polyester_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread isafil_rayon_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread jef_colors[] = {
    {{0, 0, 0}, "Placeholder", "000"},
    {{0, 0, 0}, "Black", "002"},
    {{255, 255, 255}, "White", "001"},
    {{255, 255, 23}, "Yellow", "204"},
    {{255, 102, 0}, "Orange", "203"},
    {{47, 89, 51}, "OliveGreen", "219"},
    {{35, 115, 54}, "Green", "226"},
    {{101, 194, 200}, "Sky", "217"},
    {{171, 90, 150}, "Purple", "208"},
    {{246, 105, 160}, "Pink", "201"},
    {{255, 0, 0}, "Red", "225"},
    {{177, 112, 78}, "Brown", "214"},
    {{11, 47, 132}, "Blue", "207"},
    {{228, 195, 93}, "Gold", "003"},
    {{72, 26, 5}, "DarkBrown", "205"},
    {{172, 156, 199}, "PaleViolet", "209"},
    {{252, 242, 148}, "PaleYellow", "210"},
    {{249, 153, 183}, "PalePink", "211"},
    {{250, 179, 129}, "Peach", "212"},
    {{201, 164, 128}, "Beige", "213"},
    {{151, 5, 51}, "WineRed", "215"},
    {{160, 184, 204}, "PaleSky", "216"},
    {{127, 194, 28}, "YellowGreen", "218"},
    {{229, 229, 229}, "SilverGray", "220"},
    {{136, 155, 155}, "Gray", "221"},
    {{152, 214, 189}, "PaleAqua", "227"},
    {{178, 225, 227}, "BabyBlue", "228"},
    {{54, 139, 160}, "PowderBlue", "229"},
    {{79, 131, 171}, "BrightBlue", "230"},
    {{56, 106, 145}, "SlateBlue", "231"},
    {{7, 22, 80}, "NavyBlue", "232"},
    {{249, 153, 162}, "SalmonPink", "233"},
    {{249, 103, 107}, "Coral", "234"},
    {{227, 49, 31}, "BurntOrange", "235"},
    {{226, 161, 136}, "Cinnamon", "236"},
    {{181, 148, 116}, "Umber", "237"},
    {{228, 207, 153}, "Blond", "238"},
    {{255, 203, 0}, "Sunflower", "239"},
    {{225, 173, 212}, "OrchidPink", "240"},
    {{195, 0, 126}, "PeonyPurple", "241"},
    {{128, 0, 75}, "Burgundy", "242"},
    {{84, 5, 113}, "RoyalPurple", "243"},
    {{177, 5, 37}, "CardinalRed", "244"},
    {{202, 224, 192}, "OpalGreen", "245"},
    {{137, 152, 86}, "MossGreen", "246"},
    {{92, 148, 26}, "MeadowGreen", "247"},
    {{0, 49, 20}, "DarkGreen", "248"},
    {{93, 174, 148}, "Aquamarine", "249"},
    {{76, 191, 143}, "EmeraldGreen", "250"},
    {{0, 119, 114}, "PeacockGreen", "251"},
    {{89, 91, 97}, "DarkGray", "252"},
    {{255, 255, 242}, "IvoryWhite", "253"},
    {{177, 88, 24}, "Hazel", "254"},
    {{203, 138, 7}, "Toast", "255"},
    {{152, 108, 128}, "Salmon", "256"},
    {{152, 105, 45}, "CocoaBrown", "257"},
    {{77, 52, 25}, "Sienna", "258"},
    {{76, 51, 11}, "Sepia", "259"},
    {{51, 32, 10}, "DarkSepia", "260"},
    {{82, 58, 151}, "VioletBlue", "261"},
    {{13, 33, 126}, "BlueInk", "262"},
    {{30, 119, 172}, "SolaBlue", "263"},
    {{178, 221, 83}, "GreenDust", "264"},
    {{243, 54, 137}, "Crimson", "265"},
    {{222, 100, 158}, "FloralPink", "266"},
    {{152, 65, 97}, "Wine", "267"},
    {{76, 86, 18}, "OliveDrab", "268"},
    {{76, 136, 31}, "Meadow", "269"},
    {{228, 222, 121}, "Mustard", "270"},
    {{203, 138, 26}, "YellowOcher", "271"},
    {{203, 162, 28}, "OldGold", "272"},
    {{255, 152, 5}, "HoneyDew", "273"},
    {{252, 178, 87}, "Tangerine", "274"},
    {{255, 229, 5}, "CanaryYellow", "275"},
    {{240, 51, 31}, "Vermilion", "202"},
    {{26, 132, 45}, "BrightGreen", "206"},
    {{56, 108, 174}, "OceanBlue", "222"},
    {{227, 196, 180}, "BeigeGray", "223"},
    {{227, 172, 129}, "Bamboo", "224"}
};

const EmbThread madeira_polyester_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread madeira_rayon_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread marathon_polyester_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread marathon_rayon_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread metro_polyester_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread pantone_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread pcm_colors[] = {
    {{0, 0, 0}, "1", "PCMColor1"},
    {{0, 0, 128}, "2", "PCMColor2"},
    {{0, 0, 255}, "3", "PCMColor3"},
    {{0, 128, 128}, "4", "PCMColor4"},
    {{0, 255, 255}, "5", "PCMColor5"},
    {{128, 0, 128}, "6", ""},
    {{255, 0, 255}, "7", ""},
    {{128, 0, 0}, "8", ""},
    {{255, 0, 0}, "9", ""},
    {{0, 128, 0}, "10", ""},
    {{0, 255, 0}, "11", ""},
    {{128, 128, 0}, "12", ""},
    {{255, 255, 0}, "13", ""},
    {{128, 128, 128}, "14", ""},
    {{192, 192, 192}, "15", ""},
    {{255, 255, 255}, "16", ""}
};

const EmbThread pec_colors[] = {
    {{0, 0, 0}, "Unknown", "0"},
    {{14, 31, 124}, "Prussian Blue", "1"},
    {{10, 85, 163}, "Blue", "2"},
    {{0, 135, 119}, "Teal Green", "3"},
    {{75, 107, 175}, "Cornflower Blue", "4"},
    {{237, 23, 31}, "Red", "5"},
    {{209, 92, 0}, "Reddish Brown", "6"},
    {{145, 54, 151}, "Magenta", "7"},
    {{228, 154, 203}, "Light Lilac", "8"},
    {{145, 95, 172}, "Lilac", "9"},
    {{158, 214, 125}, "Mint Green", "10"},
    {{232, 169, 0}, "Deep Gold", "11"},
    {{254, 186, 53}, "Orange", "12"},
    {{255, 255, 0}, "Yellow", "13"},
    {{112, 188, 31}, "Lime Green", "14"},
    {{186, 152, 0}, "Brass", "15"},
    {{168, 168, 168}, "Silver", "16"},
    {{125, 111, 0}, "Russet Brown", "17"},
    {{255, 255, 179}, "Cream Brown", "18"},
    {{79, 85, 86}, "Pewter", "19"},
    {{0, 0, 0}, "Black", "20"},
    {{11, 61, 145}, "Ultramarine", "21"},
    {{7, 113, 118}, "Royal Purple", "22"},
    {{41, 49, 51}, "Dark Gray", "23"},
    {{2, 161, 49}, "Dark Brown", "24"},
    {{246, 74, 138}, "DeepRose", "25"},
    {{178, 118, 36}, "Light Brown", "26"},
    {{252, 187, 197}, "Salmon Pink", "27"},
    {{15, 227, 127}, "Vermillion", "28"},
    {{240, 240, 240}, "White", "29"},
    {{106, 28, 138}, "Violet", "30"},
    {{168, 221, 196}, "Seacrest", "31"},
    {{37, 132, 187}, "Sky Blue", "32"},
    {{254, 179, 67}, "Pumpkin", "33"},
    {{255, 243, 107}, "Cream Yellow", "34"},
    {{208, 166, 96}, "Khaki", "35"},
    {{209, 84, 0}, "Clay Brown", "36"},
    {{102, 186, 73}, "Leaf Green", "37"},
    {{19, 74, 70}, "Peacock Blue", "38"},
    {{135, 135, 135}, "Gray", "39"},
    {{216, 204, 198}, "Warm Gray", "40"},
    {{4, 53, 103}, "Dark Olive", "41"},
    {{253, 217, 222}, "Flesh Pink", "42"},
    {{249, 147, 188}, "Pink", "43"},
    {{0, 56, 34}, "Deep Green", "44"},
    {{178, 175, 212}, "Lavender", "45"},
    {{104, 106, 176}, "Wisteria Violet", "46"},
    {{239, 227, 185}, "Beige", "47"},
    {{247, 56, 102}, "Carmine", "48"},
    {{181, 75, 100}, "Amber Red", "49"},
    {{19, 43, 26}, "Olive Green", "50"},
    {{12, 113, 86}, "Dark Fuschia", "51"},
    {{254, 158, 50}, "Tangerine", "52"},
    {{168, 222, 235}, "Light Blue", "53"},
    {{0, 103, 62}, "Emerald Green", "54"},
    {{78, 41, 144}, "Purple", "55"},
    {{47, 126, 32}, "Moss Green", "56"},
    {{255, 204, 204}, "Flesh Pink", "57"},
    {{255, 217, 17}, "Harvest Gold", "58"},
    {{9, 91, 166}, "Electric Blue", "59"},
    {{240, 249, 112}, "Lemon Yellow", "60"},
    {{227, 243, 91}, "Fresh Green", "61"},
    {{255, 153, 0}, "Orange", "62"},
    {{255, 240, 141}, "Cream Yellow", "63"},
    {{255, 200, 200}, "Applique", "64"}
};

const EmbThread robison_anton_polyester_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread robison_anton_rayon_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread shv_colors[] = {
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 255}, "Blue", "TODO"},
    {{51, 204, 102}, "Green", "TODO"},
    {{255, 0, 0}, "Red", "TODO"},
    {{255, 0, 255}, "Purple", "TODO"},
    {{255, 255, 0}, "Yellow", "TODO"},
    {{127, 127, 127}, "Grey", "TODO"},
    {{51, 154, 255}, "Light Blue", "TODO"},
    {{0, 255, 0}, "Light Green", "TODO"},
    {{255, 127, 0}, "Orange", "TODO"},
    {{255, 160, 180}, "Pink", "TODO"},
    {{153, 75, 0}, "Brown", "TODO"},
    {{255, 255, 255}, "White", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{255, 127, 127}, "Light Red", "TODO"},
    {{255, 127, 255}, "Light Purple", "TODO"},
    {{255, 255, 153}, "Light Yellow", "TODO"},
    {{192, 192, 192}, "Light Grey", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{255, 165, 65}, "Light Orange", "TODO"},
    {{255, 204, 204}, "Light Pink", "TODO"},
    {{175, 90, 10}, "Light Brown", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 127}, "Dark Blue", "TODO"},
    {{0, 127, 0}, "Dark Green", "TODO"},
    {{127, 0, 0}, "Dark Red", "TODO"},
    {{127, 0, 127}, "Dark Purple", "TODO"},
    {{200, 200, 0}, "Dark Yellow", "TODO"},
    {{60, 60, 60}, "Dark Gray", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{0, 0, 0}, "Black", "TODO"},
    {{232, 63, 0}, "Dark Orange", "TODO"},
    {{255, 102, 122}, "Dark Pink", "TODO"}
};

const EmbThread sigma_polyester_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread sulky_rayon_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread svg_colors[] = {
    {{240, 248, 255}, "aliceblue", "0"},
    {{250, 235, 215}, "antiquewhite", "1"},
    {{0, 255, 255}, "aqua", "2"},
    {{127, 255, 212}, "aquamarine", "3"},
    {{240, 255, 255}, "azure", "4"},
    {{245, 245, 220}, "beige", "5"},
    {{255, 228, 196}, "bisque", "6"},
    {{0, 0, 0}, "black", "7"},
    {{255, 235, 205}, "blanchedalmond", "8"},
    {{0, 0, 255}, "blue", "9"},
    {{138, 43, 226}, "blueviolet", "10"},
    {{165, 42, 42}, "brown", "11"},
    {{222, 184, 27}, "burlywood", "12"},
    {{95, 158, 160}, "cadetblue", "13"},
    {{127, 255, 0}, "chartreuse", "14"},
    {{210, 45, 30}, "chocolate", "15"},
    {{255, 127, 14}, "coral", "16"},
    {{28, 95, 237}, "cornflowerblue", "17"},
    {{255, 248, 220}, "cornsilk", "18"},
    {{220, 14, 60}, "crimson", "19"},
    {{0, 255, 255}, "cyan", "20"},
    {{0, 0, 139}, "darkblue", "21"},
    {{0, 139, 139}, "darkcyan", "22"},
    {{184, 26, 11}, "darkgoldenrod", "23"},
    {{169, 169, 169}, "darkgray", "24"},
    {{0, 28, 0}, "darkgreen", "25"},
    {{169, 169, 169}, "darkgrey", "26"},
    {{189, 183, 107}, "darkkhaki", "27"},
    {{139, 0, 139}, "darkmagenta", "28"},
    {{13, 107, 47}, "darkolivegreen", "29"},
    {{255, 140, 0}, "darkorange", "30"},
    {{63, 14, 204}, "darkorchid", "31"},
    {{139, 0, 0}, "darkred", "32"},
    {{233, 60, 122}, "darksalmon", "33"},
    {{143, 188, 143}, "darkseagreen", "34"},
    {{30, 61, 139}, "darkslateblue", "35"},
    {{47, 79, 79}, "darkslategray", "36"},
    {{47, 79, 79}, "darkslategrey", "37"},
    {{0, 206, 209}, "darkturquoise", "38"},
    {{94, 0, 211}, "darkviolet", "39"},
    {{255, 14, 93}, "deeppink", "40"},
    {{0, 191, 255}, "deepskyblue", "41"},
    {{45, 45, 45}, "dimgray", "42"},
    {{45, 45, 45}, "dimgrey", "43"},
    {{30, 90, 255}, "dodgerblue", "44"},
    {{178, 10, 10}, "firebrick", "45"},
    {{255, 250, 240}, "floralwhite", "46"},
    {{10, 139, 10}, "forestgreen", "47"},
    {{255, 0, 255}, "fuchsia", "48"},
    {{220, 220, 220}, "gainsboro", "49"},
    {{248, 248, 255}, "ghostwhite", "50"},
    {{255, 215, 0}, "gold", "51"},
    {{218, 165, 14}, "goldenrod", "52"},
    {{14, 14, 14}, "gray", "53"},
    {{14, 14, 14}, "grey", "54"},
    {{0, 14, 0}, "green", "55"},
    {{173, 255, 47}, "greenyellow", "56"},
    {{240, 255, 240}, "honeydew", "57"},
    {{255, 45, 180}, "hotpink", "58"},
    {{205, 92, 92}, "indianred", "59"},
    {{75, 0, 10}, "indigo", "60"},
    {{255, 255, 240}, "ivory", "61"},
    {{240, 230, 140}, "khaki", "62"},
    {{230, 230, 250}, "lavender", "63"},
    {{255, 240, 245}, "lavenderblush", "64"},
    {{124, 252, 0}, "lawngreen", "65"},
    {{255, 250, 205}, "lemonchiffon", "66"},
    {{173, 216, 230}, "lightblue", "67"},
    {{240, 14, 14}, "lightcoral", "68"},
    {{224, 255, 255}, "lightcyan", "69"},
    {{250, 250, 210}, "lightgoldenrodyellow", "70"},
    {{211, 211, 211}, "lightgray", "71"},
    {{90, 238, 90}, "lightgreen", "72"},
    {{211, 211, 211}, "lightgrey", "73"},
    {{255, 182, 193}, "lightpink", "74"},
    {{255, 160, 122}, "lightsalmon", "75"},
    {{14, 178, 170}, "lightseagreen", "76"},
    {{27, 206, 250}, "lightskyblue", "77"},
    {{77, 58, 63}, "lightslategray", "78"},
    {{77, 58, 63}, "lightslategrey", "79"},
    {{176, 196, 222}, "lightsteelblue", "80"},
    {{255, 255, 224}, "lightyellow", "81"},
    {{0, 255, 0}, "lime", "82"},
    {{14, 205, 14}, "limegreen", "83"},
    {{250, 240, 230}, "linen", "84"},
    {{255, 0, 255}, "magenta", "85"},
    {{14, 0, 0}, "maroon", "86"},
    {{42, 205, 170}, "mediumaquamarine", "87"},
    {{0, 0, 205}, "mediumblue", "88"},
    {{186, 13, 211}, "mediumorchid", "89"},
    {{93, 46, 219}, "mediumpurple", "90"},
    {{60, 179, 47}, "mediumseagreen", "91"},
    {{123, 44, 238}, "mediumslateblue", "92"},
    {{0, 250, 154}, "mediumspringgreen", "93"},
    {{30, 209, 204}, "mediumturquoise", "94"},
    {{199, 15, 13}, "mediumvioletred", "95"},
    {{13, 13, 46}, "midnightblue", "96"},
    {{245, 255, 250}, "mintcream", "97"},
    {{255, 228, 225}, "mistyrose", "98"},
    {{255, 228, 181}, "moccasin", "99"},
    {{255, 222, 173}, "navajowhite", "100"},
    {{0, 0, 14}, "navy", "101"},
    {{253, 245, 230}, "oldlace", "102"},
    {{14, 14, 0}, "olive", "103"},
    {{107, 142, 11}, "olivedrab", "104"},
    {{255, 165, 0}, "orange", "105"},
    {{255, 45, 0}, "orangered", "106"},
    {{218, 46, 214}, "orchid", "107"},
    {{238, 232, 170}, "palegoldenrod", "109"},
    {{62, 251, 62}, "palegreen", "110"},
    {{175, 238, 238}, "paleturquoise", "111"},
    {{219, 46, 93}, "palevioletred", "112"},
    {{255, 239, 213}, "papayawhip", "113"},
    {{255, 218, 185}, "peachpuff", "114"},
    {{205, 13, 63}, "peru", "115"},
    {{255, 192, 203}, "pink", "116"},
    {{221, 160, 221}, "plum", "117"},
    {{176, 224, 230}, "powderblue", "118"},
    {{14, 0, 14}, "purple", "119"},
    {{255, 0, 0}, "red", "120"},
    {{188, 143, 143}, "rosybrown", "121"},
    {{29, 45, 225}, "royalblue", "122"},
    {{139, 45, 13}, "saddlebrown", "123"},
    {{250, 14, 30}, "salmon", "124"},
    {{244, 164, 60}, "sandybrown", "125"},
    {{46, 139, 27}, "seagreen", "126"},
    {{255, 245, 238}, "seashell", "127"},
    {{160, 10, 45}, "sienna", "128"},
    {{192, 192, 192}, "silver", "129"},
    {{27, 206, 235}, "skyblue", "130"},
    {{106, 90, 205}, "slateblue", "131"},
    {{46, 14, 90}, "slategray", "132"},
    {{46, 14, 90}, "slategrey", "133"},
    {{255, 250, 250}, "snow", "134"},
    {{0, 255, 127}, "springgreen", "135"},
    {{46, 10, 180}, "steelblue", "136"},
    {{210, 180, 140}, "tan", "137"},
    {{0, 14, 14}, "teal", "138"},
    {{216, 191, 216}, "thistle", "139"},
    {{255, 63, 47}, "tomato", "140"},
    {{28, 224, 208}, "turquoise", "141"},
    {{238, 10, 238}, "violet", "142"},
    {{245, 222, 179}, "wheat", "143"},
    {{255, 255, 255}, "white", "144"},
    {{245, 245, 245}, "whitesmoke", "145"},
    {{255, 255, 0}, "yellow", "146"},
    {{154, 205, 14}, "yellowgreen", "147"},
};

const EmbThread thread_art_polyester_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread thread_art_rayon_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread threadelight_polyester_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

const EmbThread z102_isacord_polyester_colors[] = {
    {{0, 0, 0}, "TODO", "TODO"}
};

/*
 * Libembroidery 1.0.0-alpha
 * https://www.libembroidery.org
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright 2018-2025 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * -----------------------------------------------------------------------------
 *
 * Formats
 */

/* For debugging purposes. */
#define REPORT_VALUE(X, TYPE) \
    if (emb_verbose>1) { \
        printf(#X ": %" #TYPE "\n", X); \
    }
#define REPORT_INT(X)          REPORT_VALUE(X, d)
#define REPORT_FLOAT(X)        REPORT_VALUE(X, f)
#define REPORT_STR(X)          REPORT_VALUE(X, s)
#define REPORT_PTR(X)          REPORT_VALUE(X, p)

/* Automating reporting as part of loading a value.
 *
 * NOTE: declarations are kept seperate because in C90 we may need to
 * seperate all declarations to the start of the scope they sit in.
 */
#define LOAD_U8(FILE, X) \
    if (fread(&X, 1, 1, FILE) != 1) { \
        puts("ERROR: failed to read single byte from file."); \
    } \
    REPORT_INT(X)
#define LOAD_I8(FILE, X) LOAD_U8(FILE, X)

#define LOAD_U16(FILE, X) \
    X = emb_read_u16(FILE); \
    REPORT_INT(X)
#define LOAD_I16(FILE, X) \
    X = emb_read_i16(FILE); \
    REPORT_INT(X)
#define LOAD_U32(FILE, X) \
    X = emb_read_u32(FILE); \
    REPORT_INT(X)
#define LOAD_I32(FILE, X) \
    X = emb_read_i32(FILE); \
    REPORT_INT(X)

#define LOAD_U16_BE(FILE, X) \
    X = emb_read_u16be(FILE); \
    REPORT_INT(X)
#define LOAD_I16_BE(FILE, X) \
    X = emb_read_i16be(FILE); \
    REPORT_INT(X)
#define LOAD_U32_BE(FILE, X) \
    X = emb_read_u32be(FILE); \
    REPORT_INT(X)
#define LOAD_I32_BE(FILE, X) \
    X = emb_read_i32be(FILE); \
    REPORT_INT(X)

char read100(EmbPattern *pattern, FILE* file);
char write100(EmbPattern *pattern, FILE* file);
char read10o(EmbPattern *pattern, FILE* file);
char write10o(EmbPattern *pattern, FILE* file);
char readArt(EmbPattern *pattern, FILE* file);
char writeArt(EmbPattern *pattern, FILE* file);
char readBmc(EmbPattern *pattern, FILE* file);
char writeBmc(EmbPattern *pattern, FILE* file);
char readBro(EmbPattern *pattern, FILE* file);
char writeBro(EmbPattern *pattern, FILE* file);
char readCnd(EmbPattern *pattern, FILE* file);
char writeCnd(EmbPattern *pattern, FILE* file);
char readCol(EmbPattern *pattern, FILE* file);
char writeCol(EmbPattern *pattern, FILE* file);
char readCsd(EmbPattern *pattern, FILE* file);
char writeCsd(EmbPattern *pattern, FILE* file);
char readCsv(EmbPattern *pattern, FILE* file);
char writeCsv(EmbPattern *pattern, FILE* file);
char readDat(EmbPattern *pattern, FILE* file);
char writeDat(EmbPattern *pattern, FILE* file);
char readDem(EmbPattern *pattern, FILE* file);
char writeDem(EmbPattern *pattern, FILE* file);
char readDsb(EmbPattern *pattern, FILE* file);
char writeDsb(EmbPattern *pattern, FILE* file);
char readDst(EmbPattern *pattern, FILE* file);
char writeDst(EmbPattern *pattern, FILE* file);
char readDsz(EmbPattern *pattern, FILE* file);
char writeDsz(EmbPattern *pattern, FILE* file);
char readDxf(EmbPattern *pattern, FILE* file);
char writeDxf(EmbPattern *pattern, FILE* file);
char readEdr(EmbPattern *pattern, FILE* file);
char writeEdr(EmbPattern *pattern, FILE* file);
char readEmd(EmbPattern *pattern, FILE* file);
char writeEmd(EmbPattern *pattern, FILE* file);
char readExp(EmbPattern *pattern, FILE* file);
char writeExp(EmbPattern *pattern, FILE* file);
char readExy(EmbPattern *pattern, FILE* file);
char writeExy(EmbPattern *pattern, FILE* file);
char readEys(EmbPattern *pattern, FILE* file);
char writeEys(EmbPattern *pattern, FILE* file);
char readFxy(EmbPattern *pattern, FILE* file);
char writeFxy(EmbPattern *pattern, FILE* file);
char readGc(EmbPattern *pattern, FILE* file);
char writeGc(EmbPattern *pattern, FILE* file);
char readGnc(EmbPattern *pattern, FILE* file);
char writeGnc(EmbPattern *pattern, FILE* file);
char readGt(EmbPattern *pattern, FILE* file);
char writeGt(EmbPattern *pattern, FILE* file);
char readHus(EmbPattern *pattern, FILE* file);
char writeHus(EmbPattern *pattern, FILE* file);
char readInb(EmbPattern *pattern, FILE* file);
char writeInb(EmbPattern *pattern, FILE* file);
char readInf(EmbPattern *pattern, FILE* file);
char writeInf(EmbPattern *pattern, FILE* file);
char readJef(EmbPattern *pattern, FILE* file);
char writeJef(EmbPattern *pattern, FILE* file);
char readKsm(EmbPattern *pattern, FILE* file);
char writeKsm(EmbPattern *pattern, FILE* file);
char readMax(EmbPattern *pattern, FILE* file);
char writeMax(EmbPattern *pattern, FILE* file);
char readMit(EmbPattern *pattern, FILE* file);
char writeMit(EmbPattern *pattern, FILE* file);
char readNew(EmbPattern *pattern, FILE* file);
char writeNew(EmbPattern *pattern, FILE* file);
char readOfm(EmbPattern *pattern, FILE* file);
char writeOfm(EmbPattern *pattern, FILE* file);
char readPcd(EmbPattern *pattern, const char *fileName, FILE* file);
char writePcd(EmbPattern *pattern, FILE* file);
char readPcm(EmbPattern *pattern, FILE* file);
char writePcm(EmbPattern *pattern, FILE* file);
char readPcq(EmbPattern *pattern, const char *fileName, FILE* file);
char writePcq(EmbPattern *pattern, FILE* file);
char readPcs(EmbPattern *pattern, const char *fileName, FILE* file);
char writePcs(EmbPattern *pattern, FILE* file);
char readPec(EmbPattern *pattern, const char *fileName, FILE* file);
char writePec(EmbPattern *pattern, const char *fileName,  FILE* file);
char readPel(EmbPattern *pattern, FILE* file);
char writePel(EmbPattern *pattern, FILE* file);
char readPem(EmbPattern *pattern, FILE* file);
char writePem(EmbPattern *pattern, FILE* file);
char readPes(EmbPattern *pattern, const char *fileName, FILE* file);
char writePes(EmbPattern *pattern, const char *fileName, FILE* file);
char readPhb(EmbPattern *pattern, FILE* file);
char writePhb(EmbPattern *pattern, FILE* file);
char readPhc(EmbPattern *pattern, FILE* file);
char writePhc(EmbPattern *pattern, FILE* file);
char readPlt(EmbPattern *pattern, FILE* file);
char writePlt(EmbPattern *pattern, FILE* file);
char readRgb(EmbPattern *pattern, FILE* file);
char writeRgb(EmbPattern *pattern, FILE* file);
char readSew(EmbPattern *pattern, FILE* file);
char writeSew(EmbPattern *pattern, FILE* file);
char readShv(EmbPattern *pattern, FILE* file);
char writeShv(EmbPattern *pattern, FILE* file);
char readSst(EmbPattern *pattern, FILE* file);
char writeSst(EmbPattern *pattern, FILE* file);
char readStx(EmbPattern *pattern, FILE* file);
char writeStx(EmbPattern *pattern, FILE* file);
char readSvg(EmbPattern *pattern, FILE* file);
char writeSvg(EmbPattern *pattern, FILE* file);
char readT01(EmbPattern *pattern, FILE* file);
char writeT01(EmbPattern *pattern, FILE* file);
char readT09(EmbPattern *pattern, FILE* file);
char writeT09(EmbPattern *pattern, FILE* file);
char readTap(EmbPattern *pattern, FILE* file);
char writeTap(EmbPattern *pattern, FILE* file);
char readThr(EmbPattern *pattern, FILE* file);
char writeThr(EmbPattern *pattern, FILE* file);
char readTxt(EmbPattern *pattern, FILE* file);
char writeTxt(EmbPattern *pattern, FILE* file);
char readU00(EmbPattern *pattern, FILE* file);
char writeU00(EmbPattern *pattern, FILE* file);
char readU01(EmbPattern *pattern, FILE* file);
char writeU01(EmbPattern *pattern, FILE* file);
char readVip(EmbPattern *pattern, FILE* file);
char writeVip(EmbPattern *pattern, FILE* file);
char readVp3(EmbPattern *pattern, FILE* file);
char writeVp3(EmbPattern *pattern, FILE* file);
char readXxx(EmbPattern *pattern, FILE* file);
char writeXxx(EmbPattern *pattern, FILE* file);
char readZsk(EmbPattern *pattern, FILE* file);
char writeZsk(EmbPattern *pattern, FILE* file);

int read_descriptions(FILE* file, EmbPattern* pattern);
void readHoopName(FILE* file, EmbPattern* pattern);
void readImageString(FILE* file, EmbPattern* pattern);
void readProgrammableFills(FILE* file, EmbPattern* pattern);
void readMotifPatterns(FILE* file, EmbPattern* pattern);
void readFeatherPatterns(FILE* file, EmbPattern* pattern);
void readThreads(FILE* file, EmbPattern* pattern);

void readPESHeaderV5(FILE* file, EmbPattern* pattern);
void readPESHeaderV6(FILE* file, EmbPattern* pattern);
void readPESHeaderV7(FILE* file, EmbPattern* pattern);
void readPESHeaderV8(FILE* file, EmbPattern* pattern);
void readPESHeaderV9(FILE* file, EmbPattern* pattern);
void readPESHeaderV10(FILE* file, EmbPattern* pattern);

unsigned char toyota_position_encode(EmbReal a);
EmbReal toyota_position_decode(unsigned char a);

const int shvThreadCount = 42;
const int pecThreadCount = 65;

/* WARNING: Not unicode safe. */
unsigned char char_to_lower(unsigned char a);

/* Get extension from file name. */
int
emb_fname_extension(const char *fileName, char ending[5])
{
    int i;

    if (!fileName) {
        puts("ERROR: emb_fname_extension(), fileName argument is null.\n");
        return 0;
    }

    if (fileName[0] == 0) {
        puts("ERROR: emb_fname_extension(), fileName argument is an empty string.\n");
        return 0;
    }

    int offset = string_rchar(fileName, '.');
    if (offset == 0) {
        puts("ERROR: emb_fname_extension(), filename has no stub.\n");
        return 0;
    }

    i = 0;
    while (fileName[offset+i]) {
        ending[i] = char_to_lower(fileName[offset+i]);
        i++;
    }
    ending[i] = 0; /* terminate the string */
    return 1;
}

/* Identify format from the file name. */
int
emb_identify_format(const char *fileName)
{
    int i;
    char ending[5];
    if (!emb_fname_extension(fileName, ending)) {
        puts("Failed to isolate the extension of the supplied fileName.");
        return -1;
    }
    for (i = 0; i < numberOfFormats; i++) {
        if (!strncmp(ending, formatTable[i].extension, 10)) {
            return i;
        }
    }
    return -1;
}

/* . */
char
read_n_bytes(FILE *file, unsigned char *data, unsigned int length)
{
    if (fread(data, 1, length, file) != length) {
        printf("ERROR: failed to read %d bytes from file.", length);
        return 0;
    }
    return 1;
}

/* . */
char
emb_pattern_read(EmbPattern* pattern, const char *fileName, int format)
{
    int result;
    FILE *file;
    result = 0;
    if (!pattern) {
        printf("ERROR: emb_pattern_read(), pattern argument is null.\n");
        return 0;
    }
    if (!fileName) {
        printf("ERROR: emb_pattern_read(), fileName argument is null.\n");
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        if ((format != EMB_FORMAT_EDR) &&
            (format != EMB_FORMAT_RGB) &&
            (format != EMB_FORMAT_COL) &&
            (format != EMB_FORMAT_INF)) {
            printf("ERROR: Failed to open file with name: %s.\n", fileName);
        }
        return 0;
    }
    if (formatTable[format].check_for_color_file) {
        emb_pattern_loadExternalColorFile(pattern, fileName);
    }
    switch (format) {
    case EMB_FORMAT_100:
        result = read100(pattern, file);
        break;
    case EMB_FORMAT_10O:
        result = read10o(pattern, file);
        break;
    case EMB_FORMAT_ART:
        result = readArt(pattern, file);
        break;
    case EMB_FORMAT_BMC:
        result = readBmc(pattern, file);
        break;
    case EMB_FORMAT_BRO:
        result = readBro(pattern, file);
        break;
    case EMB_FORMAT_CND:
        result = readCnd(pattern, file);
        break;
    case EMB_FORMAT_COL:
        result = readCol(pattern, file);
        break;
    case EMB_FORMAT_CSD:
        result = readCsd(pattern, file);
        break;
    case EMB_FORMAT_CSV:
        result = readCsv(pattern, file);
        break;
    case EMB_FORMAT_DAT:
        result = readDat(pattern, file);
        break;
    case EMB_FORMAT_DEM:
        result = readDem(pattern, file);
        break;
    case EMB_FORMAT_DSB:
        result = readDsb(pattern, file);
        break;
    case EMB_FORMAT_DST:
        result = readDst(pattern, file);
        break;
    case EMB_FORMAT_DSZ:
        result = readDsz(pattern, file);
        break;
    case EMB_FORMAT_DXF:
        result = readDxf(pattern, file);
        break;
    case EMB_FORMAT_EDR:
        result = readEdr(pattern, file);
        break;
    case EMB_FORMAT_EMD:
        result = readEmd(pattern, file);
        break;
    case EMB_FORMAT_EXP:
        result = readExp(pattern, file);
        break;
    case EMB_FORMAT_EXY:
        result = readExy(pattern, file);
        break;
    case EMB_FORMAT_EYS:
        result = readEys(pattern, file);
        break;
    case EMB_FORMAT_FXY:
        result = readFxy(pattern, file);
        break;
    case EMB_FORMAT_GC:
        result = readGc(pattern, file);
        break;
    case EMB_FORMAT_GNC:
        result = readGnc(pattern, file);
        break;
    case EMB_FORMAT_GT:
        result = readGt(pattern, file);
        break;
    case EMB_FORMAT_HUS:
        result = readHus(pattern, file);
        break;
    case EMB_FORMAT_INB:
        result = readInb(pattern, file);
        break;
    case EMB_FORMAT_INF:
        result = readInf(pattern, file);
        break;
    case EMB_FORMAT_JEF:
        result = readJef(pattern, file);
        break;
    case EMB_FORMAT_KSM:
        result = readKsm(pattern, file);
        break;
    case EMB_FORMAT_MAX:
        result = readMax(pattern, file);
        break;
    case EMB_FORMAT_MIT:
        result = readMit(pattern, file);
        break;
    case EMB_FORMAT_NEW:
        result = readNew(pattern, file);
        break;
    case EMB_FORMAT_OFM:
        result = readOfm(pattern, file);
        break;
    case EMB_FORMAT_PCD:
        result = readPcd(pattern, fileName, file);
        break;
    case EMB_FORMAT_PCM:
        result = readPcm(pattern, file);
        break;
    case EMB_FORMAT_PCQ:
        result = readPcq(pattern, fileName, file);
        break;
    case EMB_FORMAT_PCS:
        result = readPcs(pattern, fileName, file);
        break;
    case EMB_FORMAT_PEC:
        result = readPec(pattern, fileName, file);
        break;
    case EMB_FORMAT_PEL:
        result = readPel(pattern, file);
        break;
    case EMB_FORMAT_PEM:
        result = readPem(pattern, file);
        break;
    case EMB_FORMAT_PES:
        result = readPes(pattern, fileName, file);
        break;
    case EMB_FORMAT_PHB:
        result = readPhb(pattern, file);
        break;
    case EMB_FORMAT_PHC:
        result = readPhc(pattern, file);
        break;
    case EMB_FORMAT_PLT:
        result = readPlt(pattern, file);
        break;
    case EMB_FORMAT_RGB:
        result = readRgb(pattern, file);
        break;
    case EMB_FORMAT_SEW:
        result = readSew(pattern, file);
        break;
    case EMB_FORMAT_SHV:
        result = readShv(pattern, file);
        break;
    case EMB_FORMAT_SST:
        result = readSst(pattern, file);
        break;
    case EMB_FORMAT_STX:
        result = readStx(pattern, file);
        break;
    case EMB_FORMAT_SVG:
        result = readSvg(pattern, file);
        break;
    case EMB_FORMAT_T01:
        result = readT01(pattern, file);
        break;
    case EMB_FORMAT_T09:
        result = readT09(pattern, file);
        break;
    case EMB_FORMAT_TAP:
        result = readTap(pattern, file);
        break;
    case EMB_FORMAT_THR:
        result = readThr(pattern, file);
        break;
    case EMB_FORMAT_TXT:
        result = readTxt(pattern, file);
        break;
    case EMB_FORMAT_U00:
        result = readU00(pattern, file);
        break;
    case EMB_FORMAT_U01:
        result = readU01(pattern, file);
        break;
    case EMB_FORMAT_VIP:
        result = readVip(pattern, file);
        break;
    case EMB_FORMAT_VP3:
        result = readVp3(pattern, file);
        break;
    case EMB_FORMAT_XXX:
        result = readXxx(pattern, file);
        break;
    case EMB_FORMAT_ZSK:
        result = readZsk(pattern, file);
        break;
    default:
        break;
    }
    fclose(file);
    if (!formatTable[format].color_only) {
        emb_pattern_end(pattern);
    }
    return result;
}

/* . */
char
emb_pattern_write(EmbPattern* pattern, const char *fileName, int format)
{
    FILE *file;
    int result = 0;
    if (!pattern) {
        printf("ERROR: emb_pattern_write(), pattern argument is null\n");
        return 0;
    }
    if (!fileName) {
        printf("ERROR: emb_pattern_write(), fileName argument is null\n");
        return 0;
    }
    if (pattern->stitch_list->count == 0) {
        printf("ERROR: emb_pattern_write(), pattern contains no stitches\n");
        return 0;
    }
    if (!formatTable[format].color_only) {
        emb_pattern_end(pattern);
    }

    file = fopen(fileName, "wb");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 0;
    }
    switch (format) {
    case EMB_FORMAT_100:
        result = write100(pattern, file);
        break;
    case EMB_FORMAT_10O:
        result = write10o(pattern, file);
        break;
    case EMB_FORMAT_ART:
        result = writeArt(pattern, file);
        break;
    case EMB_FORMAT_BMC:
        result = writeBmc(pattern, file);
        break;
    case EMB_FORMAT_BRO:
        result = writeBro(pattern, file);
        break;
    case EMB_FORMAT_CND:
        result = writeCnd(pattern, file);
        break;
    case EMB_FORMAT_COL:
        result = writeCol(pattern, file);
        break;
    case EMB_FORMAT_CSD:
        result = writeCsd(pattern, file);
        break;
    case EMB_FORMAT_CSV:
        result = writeCsv(pattern, file);
        break;
    case EMB_FORMAT_DAT:
        result = writeDat(pattern, file);
        break;
    case EMB_FORMAT_DEM:
        result = writeDem(pattern, file);
        break;
    case EMB_FORMAT_DSB:
        result = writeDsb(pattern, file);
        break;
    case EMB_FORMAT_DST:
        result = writeDst(pattern, file);
        break;
    case EMB_FORMAT_DSZ:
        result = writeDsz(pattern, file);
        break;
    case EMB_FORMAT_DXF:
        result = writeDxf(pattern, file);
        break;
    case EMB_FORMAT_EDR:
        result = writeEdr(pattern, file);
        break;
    case EMB_FORMAT_EMD:
        result = writeEmd(pattern, file);
        break;
    case EMB_FORMAT_EXP:
        result = writeExp(pattern, file);
        break;
    case EMB_FORMAT_EXY:
        result = writeExy(pattern, file);
        break;
    case EMB_FORMAT_EYS:
        result = writeEys(pattern, file);
        break;
    case EMB_FORMAT_FXY:
        result = writeFxy(pattern, file);
        break;
    case EMB_FORMAT_GC:
        result = writeGc(pattern, file);
        break;
    case EMB_FORMAT_GNC:
        result = writeGnc(pattern, file);
        break;
    case EMB_FORMAT_GT:
        result = writeGt(pattern, file);
        break;
    case EMB_FORMAT_HUS:
        result = writeHus(pattern, file);
        break;
    case EMB_FORMAT_INB:
        result = writeInb(pattern, file);
        break;
    case EMB_FORMAT_INF:
        result = writeInf(pattern, file);
        break;
    case EMB_FORMAT_JEF:
        result = writeJef(pattern, file);
        break;
    case EMB_FORMAT_KSM:
        result = writeKsm(pattern, file);
        break;
    case EMB_FORMAT_MAX:
        result = writeMax(pattern, file);
        break;
    case EMB_FORMAT_MIT:
        result = writeMit(pattern, file);
        break;
    case EMB_FORMAT_NEW:
        result = writeNew(pattern, file);
        break;
    case EMB_FORMAT_OFM:
        result = writeOfm(pattern, file);
        break;
    case EMB_FORMAT_PCD:
        result = writePcd(pattern, file);
        break;
    case EMB_FORMAT_PCM:
        result = writePcm(pattern, file);
        break;
    case EMB_FORMAT_PCQ:
        result = writePcq(pattern, file);
        break;
    case EMB_FORMAT_PCS:
        result = writePcs(pattern, file);
        break;
    case EMB_FORMAT_PEC:
        result = writePec(pattern, fileName, file);
        break;
    case EMB_FORMAT_PEL:
        result = writePel(pattern, file);
        break;
    case EMB_FORMAT_PEM:
        result = writePem(pattern, file);
        break;
    case EMB_FORMAT_PES:
        result = writePes(pattern, fileName, file);
        break;
    case EMB_FORMAT_PHB:
        result = writePhb(pattern, file);
        break;
    case EMB_FORMAT_PHC:
        result = writePhc(pattern, file);
        break;
    case EMB_FORMAT_PLT:
        result = writePlt(pattern, file);
        break;
    case EMB_FORMAT_RGB:
        result = writeRgb(pattern, file);
        break;
    case EMB_FORMAT_SEW:
        result = writeSew(pattern, file);
        break;
    case EMB_FORMAT_SHV:
        result = writeShv(pattern, file);
        break;
    case EMB_FORMAT_SST:
        result = writeSst(pattern, file);
        break;
    case EMB_FORMAT_STX:
        result = writeStx(pattern, file);
        break;
    case EMB_FORMAT_SVG:
        result = writeSvg(pattern, file);
        break;
    case EMB_FORMAT_T01:
        result = writeT01(pattern, file);
        break;
    case EMB_FORMAT_T09:
        result = writeT09(pattern, file);
        break;
    case EMB_FORMAT_TAP:
        result = writeTap(pattern, file);
        break;
    case EMB_FORMAT_THR:
        result = writeThr(pattern, file);
        break;
    case EMB_FORMAT_TXT:
        result = writeTxt(pattern, file);
        break;
    case EMB_FORMAT_U00:
        result = writeU00(pattern, file);
        break;
    case EMB_FORMAT_U01:
        result = writeU01(pattern, file);
        break;
    case EMB_FORMAT_VIP:
        result = writeVip(pattern, file);
        break;
    case EMB_FORMAT_VP3:
        result = writeVp3(pattern, file);
        break;
    case EMB_FORMAT_XXX:
        result = writeXxx(pattern, file);
        break;
    case EMB_FORMAT_ZSK:
        result = writeZsk(pattern, file);
        break;
    default:
        break;
    }
    if (formatTable[format].write_external_color_file) {
        char externalFileName[1000];
        int stub_length;
        strncpy(externalFileName, fileName, 200);
        stub_length = strlen(fileName) - strlen(formatTable[format].extension);
        externalFileName[stub_length] = 0;
        strcat(externalFileName, ".rgb");
        emb_pattern_write(pattern, externalFileName, EMB_FORMAT_RGB);
    }
    fclose(file);
    return result;
}

/* . */
char
emb_pattern_readAuto(EmbPattern* pattern, const char* fileName)
{
    int format = emb_identify_format(fileName);
    if (format < 0) {
        printf("ERROR: convert(), unsupported read file type: %s\n", fileName);
        emb_pattern_free(pattern);
        return 0;
    }
    return emb_pattern_read(pattern, fileName, format);
}

/* . */
char
emb_pattern_writeAuto(EmbPattern* pattern, const char* fileName)
{
    int format = emb_identify_format(fileName);
    printf("emb_pattern_writeAuto %d %s\n", format, fileName);
    if (format < 0) {
        printf("ERROR: convert(), unsupported write file type: %s\n", fileName);
        emb_pattern_free(pattern);
        return 0;
    }
    return emb_pattern_write(pattern, fileName, format);
}

/*
 * TO DO: NEEDS ERROR REPORTING.
 */
unsigned char
toyota_position_encode(EmbReal x)
{
    if (x < 0.0) {
        return 0x80 + (-((char)emb_round(10.0*x)));
    }
    return (unsigned char)emb_round(10.0*x);
}

/*
 * .
 */
EmbReal
toyota_position_decode(unsigned char a)
{
    if (a > 0x80) {
        return - 0.1 * (a - 0x80);
    }
    return 0.1 * a;
}

/* The Toyota 100 format is a stitch-only format that uses an external color
 * file.
 *
 * The stitch encoding is in 4 byte chunks.
 */
char
read100(EmbPattern *pattern, FILE* file)
{
    unsigned char b[10];
    while (fread(b, 1, 3, file) == 3) {
        EmbStitch st;
        st.x = toyota_position_decode(b[2]);
        st.y = toyota_position_decode(b[3]);
        st.flags = NORMAL;
        /*
        if (!(b[0] & 0xFC)) {
            st.flags = JUMP;
            TODO: review & fix
        }
        */
        if (!(b[0] & 0x01)) {
            st.flags = STOP;
        }
        if (b[0] == 0x1F) {
            st.flags = END;
        }

        emb_pattern_addStitchRel(pattern, st.x, st.y, st.flags, 1);
    }
    return 1;
}

char
write100(EmbPattern *pattern, FILE* file)
{
    int i;
    EmbVector position;

    position = pattern->home;
    for (i=0; i<pattern->stitch_list->count; i++) {
        unsigned char b[10];
        EmbStitch st = pattern->stitch_list->stitch[i];

        EmbVector delta;
        delta.x = st.x - position.x;
        delta.y = st.y - position.y;
        position = emb_vector_add(position, delta);
        b[0] = 0;
        b[1] = 0;
        b[2] = toyota_position_encode(delta.x);
        b[3] = toyota_position_encode(delta.y);
        if (!(st.flags & STOP)) {
            b[0] |= 0x01;
        }
        if (st.flags & END) {
            b[0] = 0x1F;
        }

        if (fwrite(b, 1, 4, file) != 4) {
            return 0;
        }
    }
    return 1;
}

/* The Toyota 10o format is a stitch-only format that uses an external color
 * file.
 *
 * The stitch encoding is in 3 byte chunks.
 */
char
read10o(EmbPattern *pattern, FILE* file)
{
    unsigned char b[10];
    while (fread(b, 1, 3, file) == 3) {
        EmbStitch st;

        unsigned char ctrl = b[0];
        st.y = 0.1 * b[1];
        st.x = 0.1 * b[2];
        st.flags = NORMAL;

        if (ctrl & 0x20) {
            st.x = -st.x;
        }
        if (ctrl & 0x40) {
            st.y = -st.y;
        }
        if (ctrl & 0x01) {
            st.flags = TRIM;
        }
        if ((ctrl & 0x5) == 5) {
            st.flags = STOP;
        }
        if (ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87) {
            st.flags = END;
        }

        emb_pattern_addStitchRel(pattern, st.x, st.y, st.flags, 1);
    }
    return 1;
}

/* . */
char
write10o(EmbPattern *pattern, FILE* file)
{
    int i;
    for (i=0; i<pattern->stitch_list->count; i++) {
        unsigned char b[10];
        EmbStitch st = pattern->stitch_list->stitch[i];

        b[0] = 0;
        b[1] = 0;
        b[2] = 0;
        if (st.x < 0) {
            b[2] |= 0x20;
            b[0] = -st.x;
        }
        else {
            b[0] = st.x;
        }
        if (st.y < 0) {
            b[2] |= 0x40;
            b[1] = -st.y;
        }
        else {
            b[1] = st.y;
        }
        if (st.flags == TRIM) {
            b[2] |= 1;
        }
        if (st.flags == STOP) {
            b[2] |= 5;
        }
        if (st.flags == END) {
            b[2] = 0xF8;
        }

        if (fwrite(b, 1, 3, file) != 3) {
            return 0;
        }
    }
    return 1;
}

/* The Bernina Embroidery Format (.art)
 *
 * We don't know much about this format. \todo Find a source.
 */
char
readArt(EmbPattern *pattern, FILE* file)
{
    puts("ERROR: readArt is not supported yet.");
    printf("Cannot read %p %p\n", pattern, file);
    return 0;
}

char
writeArt(EmbPattern * pattern, FILE* file)
{
    puts("ERROR: writeArt is not supported yet.");
    printf("Cannot write %p %p\n", pattern, file);
    return 0;
}

/* The Bitmap Cache Embroidery Format (.bmc)
 *
 * We don't know much about this format. \todo Find a source.
 */
char
readBmc(EmbPattern* pattern , FILE* file)
{
    puts("ERROR: readBmc is not supported.");
    printf("Cannot read %p %p\n", pattern, file);
    return 0; /*TODO: finish readBmc */
}

char
writeBmc(EmbPattern* pattern , FILE* file)
{
    puts("writeBmc is not implemented");
    printf("Cannot write %p %p\n", pattern, file);
    return 0; /*TODO: finish writeBmc */
}

/* The Bits and Volts Embroidery Format (.bro)
 *
 * The Bits and Volts bro format is a stitch-only format that
 * uses an external color file.
 *
 * The header is 256 bytes.
 * There's a series of unknown variables in the header.
 *
 * The stitch list uses a variable length encoding which is
 * 2 bytes for any stitch.
 */
char
readBro(EmbPattern* pattern, FILE* file)
{
    unsigned char header[19];
    unsigned char *ptr = header;
    if (fread(header, 1, 19, file) != 19) {
        return 0;
    }
    /* TODO: determine what this unknown data is.
     * In positions 0x0-0x4, 0xC-0xC+0x8
     */
    ptr += 3;
    char *name = (char*)ptr; /* 8 chars long */
    printf("readBro: %s\n", name);

    fseek(file, 0x100, SEEK_SET);

    while (!feof(file)) {
        short b1, b2;
        int stitchType = NORMAL;
        b1 = (unsigned char)fgetc(file);
        b2 = (unsigned char)fgetc(file);
        if (b1 == -128) {
            unsigned char bCode = (unsigned char)fgetc(file);
            if (fread(&b1, 2, 1, file) != 1) {
                puts("ERROR");
                return 0;
            }
            if (fread(&b2, 2, 1, file) != 1) {
                puts("ERROR");
                return 0;
            }
            /* Embird uses 0x02 and Wilcom uses 0xE1 */
            if (bCode == 0x02 || bCode == 0xE1) {
                stitchType = STOP;
            } else if (bCode == 3) {
                stitchType = TRIM;
            } else if (bCode == 0x7E) {
                emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
                break;
            }
        }
        emb_pattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }
    return 1;
}

char
writeBro(EmbPattern* pattern , FILE* file)
{
    puts("writeBro is not implemented");
    printf("Cannot write %p %p\n", pattern, file);
    return 0; /*TODO: finish writeBro */
}

/* The Melco Embroidery Format (.cnd)
 *
 * The Melco cnd format is a stitch-only format.
 *
 * We don't know much about this format.
 *
 * \todo Find a source.
 */
char
readCnd(EmbPattern* pattern , FILE* file)
{
    puts("readCnd is not implemented");
    printf("Cannot read %p %p\n", pattern, file);
    return 0; /*TODO: finish readCnd */
}

char
writeCnd(EmbPattern* pattern , FILE* file)
{
    puts("writeCnd is not implemented");
    printf("Cannot write %p %p\n", pattern, file);
    return 0; /*TODO: finish writeCnd */
}

/* The Embroidery Thread Color Format (.col)
 *
 * An external color file format for formats that do not record
 * their own colors.
 *
 * It is a human-readable format that has a header that is
 * a single line containing only the number of threads in decimal
 * followed by the windows line break "\r\n".
 *
 * Then the rest of the file is a comma seperated value list of
 * all threads with 4 values per line: the index of the thread
 * then the red, green and blue channels of the color in that order.
 *
 * ## Example
 *
 * If we had a pattern called "example" with four colors:
 * black, red, magenta and cyan in that order then the file is
 * (with the white space written out):
 *
 *    example.col
 *
 *    4\r\n
 *    0,0,0,0\r\n
 *    1,255,0,0\r\n
 *    2,0,255,0\r\n
 *    3,0,0,255\r\n
 */
char
readCol(EmbPattern* pattern, FILE* file)
{
    int numberOfColors, i;
    int num, blue, green, red;
    EmbThread t;
    char line[30];

    pattern->thread_list->count = 0;

    emb_readline(file, line, 30);
    numberOfColors = atoi(line);
    if (numberOfColors < 1) {
        printf("ERROR: Number of colors is zero.");
        return 0;
    }
    for (i = 0; i < numberOfColors; i++) {
        emb_readline(file, line, 30);
        if (line[0] == 0) {
            printf("ERROR: Empty line in col file.");
            return 0;
        }
        /* TODO: replace all scanf code */
        if (sscanf(line,"%d,%d,%d,%d", &num, &blue, &green, &red) != 4) {
            break;
        }
        t.color.r = (unsigned char)red;
        t.color.g = (unsigned char)green;
        t.color.b = (unsigned char)blue;
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        emb_pattern_addThread(pattern, t);
    }
    return 1;
}

char
writeCol(EmbPattern* pattern, FILE* file)
{
    int i;

    fprintf(file, "%d\r\n", pattern->thread_list->count);
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c;
        c = pattern->thread_list->thread[i].color;
        fprintf(file, "%d,%d,%d,%d\r\n", i, (int)c.r, (int)c.g, (int)c.b);
    }
    return 1;
}

/* The Singer Embroidery Format (.csd)
 *
 * Stitch Only Format.
 */
#define CsdSubMaskSize  479
#define CsdXorMaskSize  501

char _subMask[CsdSubMaskSize];
char _xorMask[CsdXorMaskSize];

const unsigned char csd_decryptArray[] = {
    0x43, 0x6E, 0x72, 0x7A, 0x76, 0x6C, 0x61, 0x6F, 0x7C, 0x29, 0x5D, 0x62, 0x60, 0x6E, 0x61, 0x62,
    0x20, 0x41, 0x66, 0x6A, 0x3A, 0x35, 0x5A, 0x63, 0x7C, 0x37, 0x3A, 0x2A, 0x25, 0x24, 0x2A, 0x33,
    0x00, 0x10, 0x14, 0x03, 0x72, 0x4C, 0x48, 0x42, 0x08, 0x7A, 0x5E, 0x0B, 0x6F, 0x45, 0x47, 0x5F,
    0x40, 0x54, 0x5C, 0x57, 0x55, 0x59, 0x53, 0x3A, 0x32, 0x6F, 0x53, 0x54, 0x50, 0x5C, 0x4A, 0x56,
    0x2F, 0x2F, 0x62, 0x2C, 0x22, 0x65, 0x25, 0x28, 0x38, 0x30, 0x38, 0x22, 0x2B, 0x25, 0x3A, 0x6F,
    0x27, 0x38, 0x3E, 0x3F, 0x74, 0x37, 0x33, 0x77, 0x2E, 0x30, 0x3D, 0x34, 0x2E, 0x32, 0x2B, 0x2C,
    0x0C, 0x18, 0x42, 0x13, 0x16, 0x0A, 0x15, 0x02, 0x0B, 0x1C, 0x1E, 0x0E, 0x08, 0x60, 0x64, 0x0D,
    0x09, 0x51, 0x25, 0x1A, 0x18, 0x16, 0x19, 0x1A, 0x58, 0x10, 0x14, 0x5B, 0x08, 0x15, 0x1B, 0x5F,
    0xD5, 0xD2, 0xAE, 0xA3, 0xC1, 0xF0, 0xF4, 0xE8, 0xF8, 0xEC, 0xA6, 0xAB, 0xCD, 0xF8, 0xFD, 0xFB,
    0xE2, 0xF0, 0xFE, 0xFA, 0xF5, 0xB5, 0xF7, 0xF9, 0xFC, 0xB9, 0xF5, 0xEF, 0xF4, 0xF8, 0xEC, 0xBF,
    0xC3, 0xCE, 0xD7, 0xCD, 0xD0, 0xD7, 0xCF, 0xC2, 0xDB, 0xA4, 0xA0, 0xB0, 0xAF, 0xBE, 0x98, 0xE2,
    0xC2, 0x91, 0xE5, 0xDC, 0xDA, 0xD2, 0x96, 0xC4, 0x98, 0xF8, 0xC9, 0xD2, 0xDD, 0xD3, 0x9E, 0xDE,
    0xAE, 0xA5, 0xE2, 0x8C, 0xB6, 0xAC, 0xA3, 0xA9, 0xBC, 0xA8, 0xA6, 0xEB, 0x8B, 0xBF, 0xA1, 0xAC,
    0xB5, 0xA3, 0xBB, 0xB6, 0xA7, 0xD8, 0xDC, 0x9A, 0xAA, 0xF9, 0x82, 0xFB, 0x9D, 0xB9, 0xAB, 0xB3,
    0x94, 0xC1, 0xA0, 0x8C, 0x8B, 0x8E, 0x95, 0x8F, 0x87, 0x99, 0xE7, 0xE1, 0xA3, 0x83, 0x8B, 0xCF,
    0xA3, 0x85, 0x9D, 0x83, 0xD4, 0xB7, 0x83, 0x84, 0x91, 0x97, 0x9F, 0x88, 0x8F, 0xDD, 0xAD, 0x90
};


void
BuildDecryptionTable(int seed) {
    int i;
    const int mul1 = 0x41C64E6D;
    const int add1 = 0x3039;

    for (i = 0; i < CsdSubMaskSize; i++) {
        seed *= mul1;
        seed += add1;
        _subMask[i] = (char) ((seed >> 16) & 0xFF);
    }
    for (i = 0; i < CsdXorMaskSize; i++) {
        seed *= mul1;
        seed += add1;
        _xorMask[i] = (char) ((seed >> 16) & 0xFF);
    }
}

unsigned char
DecodeCsdByte(long fileOffset, unsigned char val, int type)
{
    int newOffset;

    fileOffset = fileOffset - 1;
    if (type != 0) {
        int final;
        int fileOffsetHigh = (int) (fileOffset & 0xFFFFFF00);
        int fileOffsetLow = (int) (fileOffset & 0xFF);

        newOffset = fileOffsetLow;
        fileOffsetLow = fileOffsetHigh;
        final = fileOffsetLow%0x300;
        if (final != 0x100 && final != 0x200) {
            newOffset = csd_decryptArray[newOffset] | fileOffsetHigh;
        } else if (final != 0x100 && final == 0x200) {
            if (newOffset == 0) {
                fileOffsetHigh = fileOffsetHigh - 0x100;
            }
            newOffset = csd_decryptArray[newOffset] | fileOffsetHigh;
        } else if (newOffset != 1 && newOffset != 0) {
            newOffset = csd_decryptArray[newOffset] | fileOffsetHigh;
        } else {
            fileOffsetHigh = fileOffsetHigh - 0x100;
            newOffset = csd_decryptArray[newOffset] | fileOffsetHigh;
        }
    }
    else {
        newOffset = (int) fileOffset;
    }
    return ((unsigned char) ((unsigned char)
        (val ^ _xorMask[newOffset%CsdXorMaskSize]) -
            _subMask[newOffset%CsdSubMaskSize]));
}

char
readCsd(EmbPattern* pattern, FILE* file)
{
    int i, type = 0;
    unsigned char identifier[8];
    unsigned char unknown1, unknown2;
    char dx = 0, dy = 0;
    int colorChange = -1;
    int flags;
    unsigned char colorOrder[14];

    if (fread(identifier, 1, 8, file) != 8) {
        puts("ERROR");
        return 0;
    }
    /* TODO: check return value */

    if (identifier[0] != 0x7C && identifier[2] != 0xC3) {
        type = 1;
    }
    if (type == 0) {
        BuildDecryptionTable(0xC);
    }
    else {
        BuildDecryptionTable(identifier[0]);
    }

    for (i = 0; i < 16; i++) {
        EmbThread thread;
        thread.color.r = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        thread.color.g = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        thread.color.b = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        strcpy(thread.catalogNumber, "");
        strcpy(thread.description, "");
        emb_pattern_addThread(pattern, thread);
    }
    unknown1 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
    unknown2 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
    if (emb_verbose>1) {
        printf("unknown bytes to decode: %c %c", unknown1, unknown2);
    }

    for (i = 0; i < 14; i++) {
        colorOrder[i] = (unsigned char) DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
    }
    for (i = 0; !feof(file); i++) {
        char negativeX, negativeY;
        unsigned char b0 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        unsigned char b1 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        unsigned char b2 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);

        if (b0 == 0xF8 || b0 == 0x87 || b0 == 0x91) {
            break;
        }
        negativeX = ((b0 & 0x20) > 0);
        negativeY = ((b0 & 0x40) > 0);
        b0 = (unsigned char)(b0 & (0xFF ^ 0xE0));

        if ((b0 & 0x1F) == 0) {
            flags = NORMAL;
        } else if ((b0 & 0x0C) > 0) {
            flags = STOP;
            if (colorChange >= 14) {
                printf("Invalid color change detected\n");
            }
            emb_pattern_changeColor(pattern, colorOrder[colorChange  % 14]);
            colorChange += 1;
        } else if ((b0 & 0x1F) > 0) {
            flags = TRIM;
        } else {
            flags = NORMAL;
        }
        dx = (char) b2;
        dy = (char) b1;
        if (negativeX) {
            dx = (char) -dx;
        }
        if (negativeY) {
            dy = (char) -dy;
        }
        if (flags == STOP) {
            emb_pattern_addStitchRel(pattern, 0, 0, flags, 1);
        } else {
            emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }
    }
    return 1;
}

char
writeCsd(EmbPattern* pattern, FILE* file) {
    puts("writeCsd is not implemented.");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeCsd */
}

/* Comma Separated Values (.csv)
 *
 * Comma Seperated Values files aren't a universal system, here we aim to
 * offer a broad support. The dialect is detected based on the opening lines,
 * as each manufacturer should label their CSV files there.
 *
 * ## Embroidermodder 2.0 CSV Dialect
 *
 * Our own version has the identifier comment line:
 *
 * | Control Symbol | Type | Description |
 * |---|---|
 * | `#` | `COMMENT` | |
 * | `>` | `VARIABLE` | To store records of a pattern's width, height etc. This means that data stored in the header of say a .dst file is preserved. |
 * | `$` | `THREAD` | |
 * | `*` | `STITCH` | |
 * | `*` | `JUMP` | |
 * | `*` | `COLOR` | To change a color: used for trim as well |
 * | `*` | `END` | To end a pattern. |
 * | `*` | `UNKNOWN` | For any feature that we can't identify.
 *
 * ## EmBird CSV Dialect
 *
 */
char*
csvStitchFlagToStr(int flags)
{
    switch (flags) {
    case NORMAL:
        return "STITCH";
        break;
    case JUMP:
        return "JUMP";
        break;
    case TRIM:
        return "TRIM";
        break;
    case STOP:
        return "COLOR";
        break;
    case END:
        return "END";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}

int
csvStrToStitchFlag(const char* str)
{
    if (!str) {
        printf("ERROR: format-csv.c csvStrToStitchFlag(), str argument is null\n");
        return -1;
    }
    if (!strncmp(str, "STITCH", 10)) {
        return NORMAL;
    }
    if (!strncmp(str, "JUMP", 10)) {
        return JUMP;
    }
    if (!strncmp(str, "TRIM", 10)) {
        return TRIM;
    }
    if (!strncmp(str, "COLOR", 10)) {
        return STOP;
    }
    if (!strncmp(str, "END", 10)) {
        return END;
    }
    if (!strncmp(str, "UNKNOWN", 10)) {
        return STOP;
    }
    return -1;
}

char
readCsv(EmbPattern* pattern, FILE* file)
{
    int numColorChanges = 0;
    int pos = 0;
    int c = 0;
    int cellNum = 0;
    int process = 0;
    int csvMode = CSV_MODE_NULL;
    int expect = CSV_EXPECT_QUOTE1;
    int flags = 0;
    EmbReal xx = 0.0;
    EmbReal yy = 0.0;
    unsigned char r = 0, g = 0, b = 0;
    EmbString buff;

    pos = 0;
    while (!feof(file)) {
        c = fgetc(file);
        switch(c) {
            case '"':
                if (expect == CSV_EXPECT_QUOTE1) {
                    expect = CSV_EXPECT_QUOTE2;
                } else if (expect == CSV_EXPECT_QUOTE2) {
                    expect = CSV_EXPECT_COMMA;
                }
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
                    printf("ERROR: format-csv.c readCsv(), premature newline\n");
                    return 0;
                }
                break;
            default:
                break;
        }

        if (process) {
            buff[pos] = 0;
            pos = 0;
            process = 0;
            cellNum++;
            expect = CSV_EXPECT_QUOTE1;
                if (csvMode == CSV_MODE_NULL) {
                    if     (!strcmp(buff, "#")) {
                        csvMode = CSV_MODE_COMMENT;
                    } else if (!strcmp(buff, ">")) {
                        csvMode = CSV_MODE_VARIABLE;
                    } else if (!strcmp(buff, "$")) {
                        csvMode = CSV_MODE_THREAD;
                    } else if (!strcmp(buff, "*")) {
                        csvMode = CSV_MODE_STITCH;
                    } else {/* TODO: error */
                        return 0;
                    }
                } else if (csvMode == CSV_MODE_COMMENT) {
                    /* Do Nothing */
                } else if (csvMode == CSV_MODE_VARIABLE) {
                    /* Do Nothing */
                } else if (csvMode == CSV_MODE_THREAD) {
                    if (cellNum == 2) {
                        /* Do Nothing. Ignore Thread Number */
                    } else if (cellNum == 3) {
                        r = (unsigned char)atoi(buff);
                    } else if (cellNum == 4) {
                        g = (unsigned char)atoi(buff);
                    } else if (cellNum == 5) {
                        b = (unsigned char)atoi(buff);
                    } else if (cellNum == 6) {
                        /* TODO: Thread Description */
                    } else if (cellNum == 7) {
                        /* TODO: Thread Catalog Number */
                        EmbThread t;
                        t.color.r = r;
                        t.color.g = g;
                        t.color.b = b;
                        strcpy(t.description, "TODO:DESCRIPTION");
                        strcpy(t.catalogNumber, "TODO:CATALOG_NUMBER");
                        emb_pattern_addThread(pattern, t);
                        csvMode = CSV_MODE_NULL;
                        cellNum = 0;
                    } else {
                        /* TODO: error */
                        return 0;
                    }
                } else if (csvMode == CSV_MODE_STITCH) {
                    /* printf("%s\n", buff); */
                    if (cellNum == 2) {
                        flags = csvStrToStitchFlag(buff);
                        if (flags == STOP) {
                            numColorChanges++;
                        }
                    } else if (cellNum == 3) {
                        xx = atof(buff);
                    } else if (cellNum == 4) {
                        yy = atof(buff);
                        /* printf("%d %d %f %f\n",
                            pattern->stitch_list->count, flags, xx, yy); */
                        emb_pattern_addStitchAbs(pattern, xx, yy, flags, 1);
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
                if (expect == CSV_EXPECT_QUOTE2 && c != '"') {
                    buff[pos++] = (char)c;
                }
            }
    }

    return 1;
}

char
writeCsv(EmbPattern* pattern, FILE* file)
{
    EmbRect boundingRect;
    int i;

    boundingRect = emb_pattern_bounds(pattern);

    fprintf(file, "\"#\",\"Embroidermodder 2 CSV Embroidery File\"\n");
    fprintf(file, "\"#\",\"http://embroidermodder.github.io\"\n");
    fprintf(file, "\"#\",\" \"\n");
    fprintf(file, "\"#\",\"General Notes:\"\n");
    fprintf(file, "\"#\",\"This file can be read by Excel or LibreOffice as CSV (Comma Separated Value) or with a text editor.\"\n");
    fprintf(file, "\"#\",\"Lines beginning with # are comments.\"\n");
    fprintf(file, "\"#\",\"Lines beginning with > are variables: [VAR_NAME], [VAR_VALUE]\"\n");
    fprintf(file, "\"#\",\"Lines beginning with $ are threads: [THREAD_NUMBER], [RED], [GREEN], [BLUE], [DESCRIPTION], [CATALOG_NUMBER]\"\n");
    fprintf(file, "\"#\",\"Lines beginning with * are stitch entries: [STITCH_TYPE], [X], [Y]\"\n");
    fprintf(file, "\"#\",\" \"\n");
    fprintf(file, "\"#\",\"Stitch Entry Notes:\"\n");
    fprintf(file, "\"#\",\"STITCH instructs the machine to move to the position [X][Y] and then make a stitch.\"\n");
    fprintf(file, "\"#\",\"JUMP instructs the machine to move to the position [X][Y] without making a stitch.\"\n");
    fprintf(file, "\"#\",\"TRIM instructs the machine to cut the thread before moving to the position [X][Y] without making a stitch.\"\n");
    fprintf(file, "\"#\",\"COLOR instructs the machine to stop temporarily so that the user can change to a different color thread before resuming.\"\n");
    fprintf(file, "\"#\",\"END instructs the machine that the design is completed and there are no further instructions.\"\n");
    fprintf(file, "\"#\",\"UNKNOWN encompasses instructions that may not be supported currently.\"\n");
    fprintf(file, "\"#\",\"[X] and [Y] are absolute coordinates in millimeters (mm).\"\n");
    fprintf(file, "\"#\",\" \"\n");

    /* write variables */
    fprintf(file,"\"#\",\"[VAR_NAME]\",\"[VAR_VALUE]\"\n");
    fprintf(file, "\">\",\"STITCH_COUNT:\",\"%u\"\n", (unsigned int)pattern->stitch_list->count);
    fprintf(file, "\">\",\"THREAD_COUNT:\",\"%u\"\n", (unsigned int)pattern->thread_list->count);
    fprintf(file, "\">\",\"EXTENTS_LEFT:\",\"%f\"\n", boundingRect.x);
    fprintf(file, "\">\",\"EXTENTS_TOP:\",\"%f\"\n", boundingRect.y);
    fprintf(file, "\">\",\"EXTENTS_RIGHT:\",\"%f\"\n", boundingRect.x + boundingRect.w);
    fprintf(file, "\">\",\"EXTENTS_BOTTOM:\",\"%f\"\n", boundingRect.y + boundingRect.h);
    fprintf(file, "\">\",\"EXTENTS_WIDTH:\",\"%f\"\n", boundingRect.w);
    fprintf(file, "\">\",\"EXTENTS_HEIGHT:\",\"%f\"\n", boundingRect.h);
    fprintf(file,"\n");

    /* write colors */
    fprintf(file, "\"#\",\"[THREAD_NUMBER]\",\"[RED]\",\"[GREEN]\",");
    fprintf(file, "\"[BLUE]\",\"[DESCRIPTION]\",\"[CATALOG_NUMBER]\"\n");

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbThread thr = pattern->thread_list->thread[i];
        /* TODO: fix segfault that backtraces here when
            libembroidery-convert from dst to csv. */
        fprintf(file, "\"$\",\"%d\",\"%d\",\"%d\",\"%d\",\"%s\",\"%s\"\n",
            i+1,
            (int)thr.color.r,
            (int)thr.color.g,
            (int)thr.color.b,
            thr.description,
            thr.catalogNumber);
    }
    fprintf(file, "\n");

    /* write stitches */
    fprintf(file, "\"#\",\"[STITCH_TYPE]\",\"[X]\",\"[Y]\"\n");
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch s = pattern->stitch_list->stitch[i];
        fprintf(file, "\"*\",\"%s\",\"%f\",\"%f\"\n",
            csvStitchFlagToStr(s.flags), s.x, s.y);
    }
    return 1;
}

/* The Barudan Embroidery Format (.dat)
 *
 * Stitch Only Format.
 */
char
readDat(EmbPattern* pattern, FILE* file)
{
    unsigned char b0;
    int fileLength, stitchesRemaining, b1, b2, stitchType;

    fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    if (fileLength < 0x100) {
        puts("ERROR: dat file too short to contain header.");
        return 0;
    }
    fseek(file, 0x02, SEEK_SET);
    LOAD_U16(file, stitchesRemaining)
    fseek(file, 0x100, SEEK_SET);

    while (!feof(file)) {
        b1 = (int)fgetc(file);
        b2 = (int)fgetc(file);
        b0 = fgetc(file);

        stitchType = NORMAL;

        if ((b0 & 0x02) == 0) stitchType = TRIM;

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
        emb_pattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }

    return 1;
}

char
writeDat(EmbPattern* pattern, FILE* file)
{
    int i;
    fpad(file, 0x00, 0x100);
    for (i=0; i<pattern->stitch_list->count; i++) {
        unsigned char b[3];
        EmbStitch st = pattern->stitch_list->stitch[i];
        b[0] = 0;
        b[1] = 0;
        b[2] = 0;
        if (st.flags == STOP) {
            b[2] = 0x87;
        }
        if (st.flags == END) {
            b[2] |= 0xF8;
        }
        else {
            if (st.flags != TRIM) {
                b[2] |= 0x02;
            }
        }
        /* TODO: check that this works */
        if (st.x < 0) {
            b[0] = st.x+0xFF;
        }
        if (st.y < 0) {
            b[1] = st.y+0xFF;
        }
        fwrite(b, 1, 3, file);
    }
    return 1; /*TODO: finish writeDat */
}

/* The Melco Embroidery Format (.dem)
 *
 * Stitch Only Format
 */
char
readDem(EmbPattern* pattern, FILE* file)
{
    puts("readDem is not implemented.");
    puts("Overridden, defaulting to dst.");
    return readDst(pattern, file); /*TODO: finish readDem */
}

char
writeDem(EmbPattern* pattern, FILE* file)
{
    puts("writeDem is not implemented.");
    puts("Overridden, defaulting to dst.");
    return writeDst(pattern, file); /*TODO: finish writeDem */
}

/* The Barudan Embroidery Format (.dsb)
 *
 * Stitch Only Format.
 * [X] Basic Read Support
 * [o] Basic Write Support
 * [o] Well Tested Read
 * [o] Well Tested Write
 */
char
readDsb(EmbPattern* pattern, FILE* file)
{
    char header[512+1];
    unsigned char buffer[3];

    if (fread(header, 1, 512, file) != 512) {
        puts("ERROR");
        return 0;
    }

    while (fread(buffer, 1, 3, file) == 3) {
        int x, y;
        unsigned char ctrl;
        int stitchType = NORMAL;

        ctrl = buffer[0];
        y = buffer[1];
        x = buffer[2];
        if (ctrl & 0x01) stitchType = TRIM;
        if (ctrl & 0x20) x = -x;
        if (ctrl & 0x40) y = -y;
        /* ctrl & 0x02 - Speed change? */ /* TODO: review this line */
        /* ctrl & 0x04 - Clutch? */       /* TODO: review this line */
        if ((ctrl & 0x05) == 0x05) {
            stitchType = STOP;
        }
        if (ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87) {
            emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }
    return 1;
}

char
writeDsb(EmbPattern* pattern, FILE* file)
{
    puts("writeDsb is not implemented");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeDsb */
}

/*
 * # Tajima Embroidery Format (.dst)
 * .DST (Tajima) embroidery file read/write routines
 * Format comments are thanks to tspilman@dalcoathletic.com who's
 * notes appeared at http://www.wotsit.org under Tajima Format.
 *
 * Stitch Only Format.
 * [X] Basic Read Support
 * [X] Basic Write Support
 * [ ] Well Tested Read
 * [ ] Well Tested Write
 *
 * Other references: \cite kde_tajima , \cite acatina .
 *
 * ## Header
 *
 * The header contains general information about the design. It is in lines of ASCII, so
 * if you open a DST file as a text file, it's the only part that's easy to read. The
 * line ending symbol is  `0x0D}. The header is necessary for the file to be read by
 * most softwares and hardwares.
 *
 * The header is 125 bytes of data followed by padding spaces to make it 512 bytes
 * in total.
 *
 * The lines are as follows.
 *
 * | *Label* | *Size* | *Description* | *Example* |
 * |----|----|----|----|
 * | `LA:` | 17 | The design name with no path or extension. The space reserved is 16 characters, but the name must not be longer than 8 and be padded to 16 with spaces (0x20). | `"LA:Star            "` |
 * | `ST:` | 8 | The stitch count. An integer in the format `%07d`, that is: a 7 digit number padded by leading zeros. This is the total accross all possible stitch flags. | |
 * | `CO:` | 4 | The number of color changes (not to be confused with thread count, an all black design we would have the record \textbf{000}). An integer in the format  `%03d`, that is: a 3 digit number padded by leading zeros. | |
 * | `+X:` | 6 | The extent of the pattern in the postitive x direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit number padded by leading zeros. | |
 * | `-X:` | 6 | The extent of the pattern in the negative x direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit integer padded by leading zeros. | |
 * | `+Y:` | 6 | The extent of the pattern in the postitive y direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit integer padded by leading zeros. | |
 * | `-Y:` | 6 | The extent of the pattern in the negative y direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit integer padded by leading zeros. | |
 * | `AX:` | 7 | The difference of the end from the start in the x direction in 0.1mm, the first char should be the sign, followed by an integer in the format `%05d`, that is: a 5 digit integer padded by leading zeros. | |
 * | `AY:` | 7 | The difference of the end from the start in the y direction in 0.1mm, the first char should be the sign, followed by an integer in the format `%05d`, that is: a 5 digit integer padded by leading zeros. | |
 * | `MX:` | 7 | The x co-ordinate of the last point in the previous file should the design span multiple files. Like AX, it is the sign, followed by a 5 digit integer. If we have a one file design set it to zero. | |
 * | `MY:` | 7 | The y co-ordinate of the last point in the previous file should the design span multiple files. Like AY, it is the sign, followed by a 5 digit integer. If we have a one file design set it to zero. | |
 * | `PD:` | 10 | Information about multivolume designs. | |
 *
 * ### Stitch Data
 *
 * Uses 3 byte per stitch encoding with the format as follows:
 *
 * | *Bit* | *7* | *6* | *5* | *4* | *3* | *2* | *1* | *0* |
 * |-------|-----|-----|-----|-----|-----|-----|-----|-----|
 * | Byte 0 | y+1 | y-1 | y+9 | y-9 | x-9 | x+9 | x-1 | x+1 |
 * | Byte 1 | y+3 | y-3 | y+27 | y-27 | x-27 | x+27 | x-3 | x+3 |
 * | Byte 2 | jump | color change | y+81 | y-81 | x-81 | x+81 | set | set |
 *
 * T01 and Tap appear to use Tajima Ternary.
 *
 * Where the stitch type is determined as:
 * 
 * * Normal Stitch `0b00000011 0x03`
 * * Jump Stitch `0b10000011 0x83`
 * * Stop/Change Color `0b11000011 0xC3`
 * * End Design `0b11110011 0xF3`
 *
 * Inclusive or'ed with the last byte.
 *
 * Note that the max stitch length is the largest sum of $1+3+9+27+81=121$
 * where the unit length is 0.1mm so 12.1mm. The coordinate system is right handed.
 *
 */
int
decode_record_flags(unsigned char b2)
{
    if (b2 == 0xF3) {
        return END;
    }
    if (b2 & 0x40) {
        return STOP;
    }
    if (b2 & 0x80) {
        return JUMP;
    }
    return NORMAL;
}

/* TODO: review this then remove since emb-pattern.c has a similar function */
/*
void
combine_jump_stitches(EmbPattern* p, int jumpsPerTrim)
{
    if (!p) {
        printf("ERROR: format-dst.c combineJumpStitches(), p argument is null\n");
        return;
    }
    Embstitch_list* pointer = p->stitch_list;
    int jumpCount = 0;
    Embstitch_list* jumpListStart = 0;
    char needleDown = 0;
    while (pointer) {
        if ((pointer->stitch.flags & JUMP) && !(pointer->stitch.flags & STOP)) {
            if (jumpCount == 0)
            {
                jumpListStart = pointer;
            }
            jumpCount++;
            if (needleDown && jumpCount >= jumpsPerTrim)
            {
                Embstitch_list* removePointer = jumpListStart->next;
                jumpListStart->stitch.x = pointer->stitch.x;
                jumpListStart->stitch.y = pointer->stitch.y;
                jumpListStart->stitch.flags |= TRIM;
                jumpListStart->next = pointer;

                jumpCount-=2;
                for (; jumpCount > 0; jumpCount--)
                {
                    Embstitch_list* tempPointer = removePointer->next;
                    jumpListStart->stitch.flags |= removePointer->stitch.flags;
                    safe_free(removePointer);
                    removePointer = 0;
                    removePointer = tempPointer;
                }
                jumpCount = 0;
                needleDown = 0;
            }
        }
        else {
            if (pointer->stitch.flags == NORMAL)
            {
                needleDown = 1;
                jumpCount = 0;
            }
        }
        pointer = pointer->next;
    }
}
*/

void
encode_record(FILE* file, int x, int y, int flags)
{
    unsigned char b[3];
    encode_tajima_ternary(b, x, y);

    b[2] |= 0x03;

    if (flags & END) {
        /* 0b10001101 = -13 = 0x8D */
        b[0] = 0;
        b[1] = 0;
        b[2] = 0x8D;
    }

    /* make the variable v configurable for the pattern */
    if (flags & TRIM) {
        int dx, dy, i, v = 5;
        dx = x/v;
        dy = y/v;
        for (i = 1; i < v; i++) {
            encode_record(file, dx, dy, JUMP);
        }
        encode_record(file, x - (dx * (v - 1)), y - (dy * (v - 1)), JUMP);
        return;
    }
    if (flags & (JUMP | TRIM)) {
        b[2] = (char) (b[2] | 0x83);
    }
    if (flags & STOP) {
        b[2] = (char) (b[2] | 0xC3);
    }

    fwrite(b, 1, 3, file);
}

/*convert 2 characters into 1 int for case statement */
/*#define cci(s) (s[0]*256+s[1]) */
#define cci(c1, c2) (c1*256+c2)

void
set_dst_variable(EmbPattern* pattern, char* var, char* val) {
    unsigned int i;
    EmbThread t;
    for (i = 0; i <= (unsigned int)strlen(var); i++) {
        /* uppercase the var */
        if (var[i] >= 'a' && var[i] <= 'z') {
            var[i] += 'A' - 'a';
        }
    }

    /* macro converts 2 characters to 1 int, allows case statement... */
    switch(cci(var[0],var[1])) {
    case cci('L','A'): /* Design Name (LA) */
        /*pattern->set_variable("Design_Name",val); TODO: review this line. */
        break;
    case cci('S','T'): /* Stitch count, 7 digits padded by leading 0's */
    case cci('C','O'): /* Color change count, 3 digits padded by leading 0's */
    case cci('+','X'): /* Design extents (+/-X,+/-Y), 5 digits padded by leading 0's */
    case cci('-','X'):
    case cci('+','Y'):
    case cci('-','Y'):
        /* don't store these variables, they are recalculated at save */
        break;
    case cci('A','X'): /* Relative coordinates of last point, 6 digits, padded with leading spaces, first char may be +/- */
    case cci('A','Y'):
    case cci('M','X'): /* Coordinates of last point in previous file of multi-volume design, 6 digits, padded with leading spaces, first char may be +/- */
    case cci('M','Y'):
        /* store these variables as-is, they will be converted to numbers and back at save; */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    case cci('P','D'):
        /* store this string as-is, it will be saved as-is, 6 characters */
        if (strlen(val) != 6) {
            /*pattern->messages.add("Warning: in DST file read,
                PD is not 6 characters, but ",(int)strlen(val)); */
        }
        /*pattern->set_variable(var,val);*/
        break;
        /* Begin extended fields section */
    case cci('A','U'): /* Author string, arbitrary length */
    case cci('C','P'): /* Copyright string, arbitrary length */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
        /*Thread Color: #RRGGBB,Description,Catalog Number (1st field RGB
            hex values, 2nd&3rd fields optional arbitrary length) */
    case cci('T','C'):
        /* TODO: review these lines below.
        description=split_cell_str(val,2);
        catalog_number=split_cell_str(val,3);
        */
        t.color = embColor_fromHexStr(val);
        strcpy(t.description, "");
        strcpy(t.catalogNumber, "");
        emb_pattern_addThread(pattern, t);
        break;
    default:
        /* unknown field, just save it. */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    }
}

/*
 * The header seems to contain information about the design.
 * Seems to be ASCII text delimited by 0x0D (carriage returns).
 * This must be in the file for most new software or hardware
 * to consider it a good file! This is much more important
 * than I originally believed. The header is 125 bytes in
 * length and padded out by 0x20 to 512 bytes total.
 * All entries in the header seem to be 2 ASCII characters
 * followed by a colon, then it's value trailed by a carriage return.
 *
 * char LA[16+1];  First is the 'LA' entry, which is the design name with no
 *                 path or extension information. The blank is 16 characters
 *                 in total, but the name must not be longer that 8 characters
 *                 and padded out with 0x20.
 *
 * char ST[7+1];   Next is the stitch count ST, this is a 7 digit number
 *                 padded by leading zeros. This is the total stitch count
 *                 including color changes, jumps, nups, and special records.
 *
 * char CO[3+1];   Next, is CO or colors, a 3 digit number padded by leading
 *                 zeros. This is the number of color change records in the file.
 *
 * char POSX[5+1]; Next is +X or the positive X extent in centimeters, a 5
 *                 digit non-decimal number padded by leading zeros.
 *
 * char NEGX[5+1]; Following is the -X or the negative X extent in millimeters,
 *                 a 5 digit non-decimal number padded by leading zeros.
 *
 * char POSY[5+1]; Again, the +Y extents.
 *
 * char NEGY[5+1]; Again, the -Y extents.
 *
 * char AX[6+1];   AX and AY should express the relative coordinates of the
 * char AY[6+1];   last point from the start point in 0.1 mm. If the start
 *                 and last points are the same, the coordinates are (0,0).
 *
 * char MX[6+1];   MX and MY should express coordinates of the last point of
 * char MY[6+1];   the previous file for a multi-volume design. A multi-
 *                 volume design means a design consisted of two or more files.
 *                 This was used for huge designs that can not be stored in a
 *                 single paper tape roll. It is not used so much (almost
 *                 never) nowadays.
 *
 * char PD[9+1];   PD is also storing some information for multi-volume design.
 */
char
readDst(EmbPattern* pattern, FILE* file) {
    char var[3];   /* temporary storage variable name */
    char val[512]; /* temporary storage variable value */
    int valpos;
    unsigned char b[3];
    char header[512 + 1];
    int i = 0, flags;

    /* TODO: review commented code below
    pattern->clear();
    pattern->set_variable("file_name",filename);
    */

    if (fread(header, 1, 512, file) != 512) {
        puts("ERROR: Failed to read header bytes.");
        return 0;
    }

    /*TODO:It would probably be a good idea to
        validate file before accepting it. */
    /* fill variables from header fields */
    for (i = 0; i < 512; i++) {
        if (header[i] == ':' && i > 1) {
            var[0] = header[i - 2];
            var[1] = header[i - 1];
            var[2] = '\0';
            valpos = i + 1;
            for (i++; i < 512; i++)
            {
                /* don't accept : without CR because there's a bug below: i-valpos must be > 0 which is not the case if the : is before the third character. */
                if (header[i] == 13/*||header[i]==':'*/) { /* 0x0d = carriage return */
                    /* : indicates another variable, CR was missing! */
                    if (header[i] == ':') {
                        i -= 2;
                    }
                    /* TODO: used to be strncpy, make sure this is a safe substitution. */
                    memcpy(val, &header[valpos], (size_t)(i - valpos));
                    val[i - valpos] = '\0';
                    set_dst_variable(pattern, var, val);
                    break;
                }
            }
        }
    }

    while (fread(b, 1, 3, file) == 3) {
        int x, y;
        decode_tajima_ternary(b, &x, &y);
        flags = decode_record_flags(b[2]);
        if (flags == END) {
            break;
        }
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
    }

    /* combine_jump_stitches(pattern, 5); */
    return 1;
}

char
writeDst(EmbPattern* pattern, FILE* file)
{
    EmbRect boundingRect;
    int i, ax, ay, mx, my;
    EmbVector pos;
    EmbString pd;

    emb_pattern_correctForMaxStitchLength(pattern, 12.1f, 12.1f);

    /* TODO: make sure that pattern->thread_list->count
     * defaults to 1 in new patterns */
    boundingRect = emb_pattern_bounds(pattern);
    /* TODO: review the code below
    if (pattern->get_variable("design_name") != NULL) {
        char *la = stralloccopy(pattern->get_variable("design_name"));
        if (strlen(la)>16) la[16]='\0';

        fprintf(file,"LA:%-16s\x0d",la);
        safe_free(la);
    }
    */
    fprintf(file, "LA:%-16s\x0d", "Untitled");
    fprintf(file, "ST:%7d\x0d", pattern->stitch_list->count);
    /* number of color changes, not number of colors! */
    fprintf(file, "CO:%3d\x0d", pattern->thread_list->count - 1);
    fprintf(file,
        "+X:%5d\x0d"
        "-X:%5d\x0d"
        "+Y:%5d\x0d"
        "-Y:%5d\x0d",
        (int)((boundingRect.x + boundingRect.w) * 10.0),
        (int)(fabs(boundingRect.x) * 10.0),
        (int)((boundingRect.y + boundingRect.h) * 10.0),
        (int)(fabs(boundingRect.y) * 10.0));

    ax = ay = mx = my = 0;
    /* TODO: review the code below */
    /*ax=pattern->get_variable_int("ax"); */ /* will return 0 if not defined */
    /*ay=pattern->get_variable_int("ay"); */
    /*mx=pattern->get_variable_int("mx"); */
    /*my=pattern->get_variable_int("my"); */

    /*pd=pattern->get_variable("pd");*/ /* will return null pointer if not defined */
   /* pd = 0;
    if (pd == 0 || strlen(pd) != 6) { */
        /* pd is not valid, so fill in a default consisting of "******" */
        strcpy(pd, "******");
    /*}*/
    fprintf(file,
        "AX:+%5d\x0d"
        "AY:+%5d\x0d"
        "MX:+%5d\x0d"
        "MY:+%5d\x0d"
        "PD:%6s\x0d\x1a",
        ax, ay, mx, my, pd);

    /* pad out header to proper length */
    fpad(file, ' ', 512-125);

    /* write stitches */
    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st;
        int dx, dy;
        st = pattern->stitch_list->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)emb_round(10.0f * (st.x - pos.x));
        dy = (int)emb_round(10.0f * (st.y - pos.y));
        pos.x += 0.1f * dx;
        pos.y += 0.1f * dy;
        if (emb_verbose > 0) {
            printf("%d %f %f %d %d %f %f %d\n", i, st.x, st.y, dx, dy, pos.x, pos.y, st.flags);
        }
        encode_record(file, dx, dy, st.flags);
    }

    /* Finish file with a terminator character and two zeros to
     * keep the post header part a multiple of three.
     */
    fwrite("\xa1\0\0", 1, 3, file);
    return 1;
}

/* ZSK USA Embroidery Format (.dsz)
 *
 * The ZSK USA dsz format is stitch-only.
 */

char
readDsz(EmbPattern* pattern, FILE* file)
{
    unsigned char b[3];

    fseek(file, 0x200, SEEK_SET);
    while (fread(b, 1, 3, file) == 3) {
        int x, y;
        unsigned char ctrl;
        int stitchType = NORMAL;

        y = b[0];
        x = b[1];
        ctrl = b[2];
        if (ctrl & 0x01) {
            stitchType = TRIM;
        }
        if (ctrl & 0x20) {
            y = -y;
        }
        if (ctrl & 0x40) {
            x = -x;
        }
        if (ctrl & 0x0E) {
            /*
            TODO: Add back if head number is added to the library
            int headNumber = (ctrl & 0x0E) >> 1;
            */
            stitchType = STOP;
        }
        if (ctrl & 0x10) {
            emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        emb_pattern_addStitchRel(pattern, x  / 10.0f, y  / 10.0f, stitchType, 1);
    }
    return 1;
}

/* WARNING: this is untested.
 * This is based on the readDsz function.
 */
char
writeDsz(EmbPattern* pattern, FILE* file)
{
    int i;
    EmbVector delta;
    EmbVector start;
    fpad(file, ' ', 200);
    start.x = 0.0;
    start.y = 0.0;
    for (i=0; i<pattern->stitch_list->count; i++) {
        EmbVector pos;
        EmbStitch st;
        unsigned char b[3];
        st = pattern->stitch_list->stitch[i];
        pos.x = st.x;
        pos.y = st.y;
        delta = emb_vector_subtract(pos, start);
        b[2] = 0;
        if (st.flags & TRIM) {
            b[2] |= 0x01;
        }
        if (10.0*delta.x < 0.0) {
            b[2] |= 0x20;
        }
        if (10.0*delta.y < 0.0) {
            b[2] |= 0x40;
        }
        if (st.flags & STOP) {
            b[2] |= 0x0E;
        }
        if (st.flags & END) {
            b[2] |= 0x10;
        }
        b[0] = emb_round(10.0*delta.x);
        b[1] = emb_round(10.0*delta.y);
        fwrite(b, 1, 3, file);
    }
    return 1;
}

/* Drawing Exchange Format (.dxf)
 * Graphics format for drawing files designed and used by AudoDesk for their AutoCAD program. \cite{dxf_reference}
 */
void
readLine(FILE* file, char *str)
{
    int i;
    int past_leading_spaces;

    /* Remove leading spaces. */
    past_leading_spaces = 0;
    for (i=0; i<254; i++) {
        if (feof(file)) {
            str[i] = 0;
            break;
        }
        str[i] = fgetc(file);
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = 0;
            break;
        }
        if (str[i] == ' ') {
            if (!past_leading_spaces) {
                i--;
            }
        }
        else {
            past_leading_spaces = 0;
        }
    }
}

/* Use parsing library here. Write down full DXF grammar. */
char
readDxf(EmbPattern* pattern, FILE* file)
{
    EmbString dxfVersion;
    EmbString section;
    EmbString tableName;
    EmbString layerName;
    EmbString entityType;
    /*char layerColorHash[100][8]; */ /* hash <layerName, EmbColor> */

    REPORT_PTR(pattern);

    int eof = 0; /* End Of File */

    EmbString buff;
    EmbVector prev, pos, first;
    EmbReal bulge = 0.0f;
    REPORT_FLOAT(bulge);
    char firstStitch = 1;
    printf("%c\n", firstStitch);
    char bulgeFlag = 0;
    int fileLength = 0;
    first.x = 0.0f;
    first.y = 0.0f;
    pos.x = 0.0f;
    pos.y = 0.0f;
    prev.x = 0.0f;
    prev.y = 0.0f;
    printf("%f %f %f\n", prev.x, pos.x, first.x);

    fseek(file, 0L, SEEK_END);

    fileLength = ftell(file);
    fseek(file, 0L, SEEK_SET);

    while (ftell(file) < fileLength) {
        readLine(file, buff);
        /*printf("%s\n", buff);*/
        if ((!strcmp(buff, "HEADER"))   ||
            (!strcmp(buff, "CLASSES"))  ||
            (!strcmp(buff, "TABLES"))   ||
            (!strcmp(buff, "BLOCKS"))   ||
            (!strcmp(buff, "ENTITIES")) ||
            (!strcmp(buff, "OBJECTS"))  ||
            (!strcmp(buff, "THUMBNAILIMAGE"))) {
            strcpy(section, buff);
            printf("SECTION:%s\n", buff);
        }
        if (!strcmp(buff, "ENDSEC")) {
            strcpy(section, "");
            printf("ENDSEC:%s\n", buff);
        }
        if ( (!strcmp(buff, "ARC")) ||
            (!strcmp(buff, "CIRCLE")) ||
            (!strcmp(buff, "ELLIPSE")) ||
            (!strcmp(buff, "LINE")) ||
            (!strcmp(buff, "LWPOLYLINE")) ||
            (!strcmp(buff, "POINT"))) {
            strcpy(entityType, buff);
        }
        if (!strcmp(buff, "EOF")) {
            eof = 1;
        }

        if (!strcmp(section, "HEADER")) {
            if (!strcmp(buff, "$ACADVER"))
            {
                readLine(file, buff);
                readLine(file, dxfVersion);
                /* TODO: Allow these versions when POLYLINE is handled. */
                if ((!strcmp(dxfVersion, DXF_VERSION_R10))
                || (!strcmp(dxfVersion, DXF_VERSION_R11))
                || (!strcmp(dxfVersion, DXF_VERSION_R12))
                || (!strcmp(dxfVersion, DXF_VERSION_R13))) {
                    return 0;
                }
            }
        }
        else if (!strcmp(section,"TABLES")) {
            if (!strcmp(buff,"ENDTAB")) {
                tableName[0] = 0;
            }

            if (tableName[0] == 0) {
                if (!strcmp(buff,"2")) { /* Table Name */
                    readLine(file, tableName);
                }
            }
            else if (!strcmp(tableName, "LAYER"))
            {
                /* Common Group Codes for Tables */
                if (!strcmp(buff,"5")) /* Handle */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"330")) /* Soft Pointer */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"100")) /* Subclass Marker */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"70")) /* Number of Entries in Table */
                {
                    readLine(file, buff);
                    continue;
                }
                /* The meaty stuff */
                else if (!strcmp(buff,"2")) /* Layer Name */
                {
                    readLine(file, layerName);
                }
                else if (!strcmp(buff,"62")) /* Color Number */
                {
                    unsigned char colorNum;
                    EmbColor co;

                    readLine(file, buff);
                    colorNum = atoi(buff);

        /* Why is this here twice? */
                    colorNum = atoi(buff);
                    co = dxf_colors[colorNum].color;
                    printf("inserting:%s,%d,%d,%d\n", layerName, co.r, co.g, co.b);
                    /* TODO: fix this with a lookup finish this
                    if (embHash_insert(layerColorHash, emb_strdup(layerName), co))
                    {
                         TODO: log error: failed inserting into layerColorHash
                    }
                    */
                    layerName[0] = 0;
                }
            }
        }
        else if (!strcmp(section,"ENTITIES")) {
            /* Common Group Codes for Entities */
            if (!strcmp(buff, "5")) /* Handle */
            {
                readLine(file, buff);
                continue;
            }
            else if (!strcmp(buff, "330")) /* Soft Pointer */
            {
                readLine(file, buff);
                continue;
            }
            else if (!strcmp(buff, "100")) /* Subclass Marker */
            {
                readLine(file, buff);
                continue;
            }
            else if (!strcmp(buff, "8")) /* Layer Name */
            {
                readLine(file, buff);
                /* emb_pattern_changeColor(pattern, colorIndexMap[buff]); TODO: port to C */
                continue;
            }

            if (!strcmp(entityType,"LWPOLYLINE")) {
                /* The not so important group codes */
                if (!strcmp(buff, "90")) /* Vertices */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"70")) /* Polyline Flag */
                {
                    readLine(file, buff);
                    continue;
                }
                /* TODO: Try to use the widths at some point */
                else if (!strcmp(buff,"40")) /* Starting Width */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"41")) /* Ending Width */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"43")) /* Constant Width */
                {
                    readLine(file, buff);
                    continue;
                }
                /* The meaty stuff */
                else if (!strcmp(buff,"42")) /* Bulge */
                {
                    readLine(file, buff);
                    bulge = atof(buff);
                    bulgeFlag = 1;
                    printf("bulgeFlag %d\n", bulgeFlag);
                }
                else if (!strcmp(buff,"10")) /* X */
                {
                    readLine(file, buff);
                    pos.x = atof(buff);
                }
                else if (!strcmp(buff,"20")) /* Y */
                {
#if 0
                    readLine(file, buff);
                    pos.y = atof(buff);

                    if (bulgeFlag) {
                        EmbArc arc;
                        bulgeFlag = 0;
                        arc.start = prev;
                        arc.end = pos;
                /*TODO: error */
                /*
                        if (!getArcDataFromBulge(bulge, &arc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {
                            return 0;
                        }
                */
                return 0;
                        if (firstStitch) {
                            /* emb_pattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        }
                        /* emb_pattern_addStitchAbs(pattern, x, y, ARC, 1); TODO: Add arcTo point to embPath pointList */
                    }
                    else {
                        /*if (firstStitch) emb_pattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        /*else            emb_pattern_addStitchAbs(pattern, x, y, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
                    }
                    prev = pos;
                    if (firstStitch) {
                        first = pos;
                        firstStitch = 0;
                    }
#endif
                }
                else if (!strcmp(buff,"0")) {
#if 0
                    entityType[0] = 0;
                    firstStitch = 1;
                    if (bulgeFlag) {
                        EmbArc arc;
                        bulgeFlag = 0;
                        arc.start = prev;
                        arc.end = first;
                        /* TODO: error */
                        /*
                        if (!getArcDataFromBulge(bulge, &arc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {
                            return 0;
                        }
                        */
                        return 0;
                        prev = arc.start;
                        /* emb_pattern_addStitchAbs(pattern, prevX, prevY, ARC, 1);
                         * TODO: Add arcTo point to embPath pointList */
                    }
                    else {
                        /* emb_pattern_addStitchAbs(pattern, firstX, firstY, NORMAL, 1);
                         * TODO: Add lineTo point to embPath pointList */
                    }
#endif
                }
            } /* end LWPOLYLINE */
        } /* end ENTITIES section */
    } /* end while loop */

    /*
    EmbColor* testColor = 0;
    testColor = embHash_value(layerColorHash, "OMEGA");
    if (!testColor) {
        printf("NULL POINTER!\n");
    }
    else {
        printf("LAYERCOLOR: %d,%d,%d\n", testColor->r, testColor->g, testColor->b);
    }
    */

    if (!eof) {
        /* NOTE: The EOF item must be present at the end of file to be considered a valid DXF file. */
        printf("ERROR: format-dxf.c readDxf(), missing EOF at end of DXF file\n");
    }
    return eof;
}

char
writeDxf(EmbPattern* pattern, FILE* file)
{
    puts("ERROR: writeDxf not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeDxf */
}

/* Embird Embroidery Format (.edr)
 * Stitch Only Format
 */
char
readEdr(EmbPattern* pattern, FILE* file)
{
    /* appears identical to readRgb, so backends to that */
    return readRgb(pattern, file);
}

char
writeEdr(EmbPattern* pattern, FILE* file)
{
    /* appears identical to writeRgb, so backends to that */
    return writeRgb(pattern, file);
}

/* The Elna Embroidery Format (.emd)
 * Stitch Only Format.
 */

char
emdDecode(unsigned char inputByte)
{
    if (inputByte >= 0x80) {
        return (-~inputByte) - 1;
    }
    return inputByte;
}

/* . */
char
readEmd(EmbPattern* pattern, FILE* file)
{
    unsigned char b[2];
    unsigned char jemd0[6]; /* TODO: more descriptive name */
    int width, height, colors, length;

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    if (length < 0x30) {
        puts("File invalid: shorter than the header.");
        return 0;
    }
    fseek(file, 0, SEEK_SET);

    if (fread(jemd0, 1, 6, file) != 6) {
        puts("ERROR: Failed to read 6 bytes for jemd0");
        return 0;
    }
    width = emb_read_i16(file);
    height = emb_read_i16(file);
    colors = emb_read_i16(file);
    printf("%d %d %d\n", width, height, colors);

    fseek(file, 0x30, SEEK_SET);

    while (!feof(file)) {
        char dx, dy;
        int flags = NORMAL;
        if (fread(b, 1, 2, file) != 2) {
            puts("ERROR: Failed to read 2 bytes for stitch.");
            return 0;
        }
        
        if (b[0] == 0x80) {
            if (b[1] == 0x2A) {
                emb_pattern_addStitchRel(pattern, 0, 0, STOP, 1);
                continue;
            }
            else if (b[1] == 0x80) {
                if (fread(b, 1, 2, file) != 2) {
                    puts("ERROR: Failed to read 2 bytes for stitch.");
                    return 0;
                }
                flags = TRIM;
            }
            else if (b[1] == 0xFD) {
                emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
                break;
            }
            else {
                continue;
            }
        }
        dx = emdDecode(b[0]);
        dy = emdDecode(b[1]);
        emb_pattern_addStitchRel(pattern, dx / 10.0f, dy / 10.0f, flags, 1);
    }
    return 1;
}

char
writeEmd(EmbPattern* pattern, FILE* file)
{
    puts("writeEmd not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeEmd */
}

/* Melco Embroidery Format (.exp)
 * Stitch Only Format.
 */

char
expDecode(unsigned char a1)
{
    return (a1 > 0x80) ? ((-~a1) - 1) : a1;
}

char
readExp(EmbPattern* pattern, FILE* file)
{
    unsigned char b[2];

    while (fread(b, 1, 2, file) == 2) {
        char dx = 0, dy = 0;
        int flags = NORMAL;
        if (b[0] == 0x80) {
            if (b[1] == 0x01) {
                if (fread(b, 1, 2, file) != 2) break;
                /* b0=0x00 and b1=0x00, but accept any,
                not worth crashing over. */
                flags = STOP;
            } else if (b[1] == 0x04) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                flags = JUMP;
            } else if (b[1] == 0x80) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                /* b0=0x07 and b1=0x00, but accept any,
                not worth crashing over. */
                flags = TRIM;
            }
        }
        dx = expDecode(b[0]);
        dy = expDecode(b[1]);
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writeExp(EmbPattern* pattern, FILE* file)
{
    EmbVector pos;
    int i;

    /* write stitches */
    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        char b[4];
        char dx, dy;
        EmbStitch st = pattern->stitch_list->stitch[i];
        dx = (char)emb_round(10.0*(st.x - pos.x));
        dy = (char)emb_round(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;
        switch (st.flags) {
        case STOP:
            b[0] = (char)(0x80);
            b[1] = 0x01;
            b[2] = 0x00;
            b[3] = 0x00;
            fwrite(b, 1, 4, file);
            break;
        case JUMP:
            b[0] = (char)(0x80);
            b[1] = 0x04;
            b[2] = dx;
            b[3] = dy;
            fwrite(b, 1, 4, file);
            break;
        case TRIM:
            b[0] = (char)(0x80);
            b[1] = (char)(0x80);
            b[2] = 0x07;
            b[3] = 0x00;
            fwrite(b, 1, 4, file);
            break;
        default: /* STITCH */
            b[0] = dx;
            b[1] = dy;
            fwrite(b, 1, 2, file);
            break;
        }
    }
    fprintf(file, "\x1a");
    return 1;
}

/* Eltac Embroidery Format (.exy)
 * Stitch Only Format.
 */
int
decode_exy_flags(unsigned char b2)
{
    int returnCode = 0;
    if (b2 == 0xF3) {
        return (END);
    }
    if ((b2 & 0xC3) == 0xC3) {
        return TRIM | STOP;
    }
    if (b2 & 0x80) {
        returnCode |= TRIM;
    }
    if (b2 & 0x40) {
        returnCode |= STOP;
    }
    return returnCode;
}

char
readExy(EmbPattern* pattern, FILE* file)
{
    unsigned char b[3];

    fseek(file, 0x100, SEEK_SET);
    while (fread(b, 1, 3, file) == 3) {
        int flags, x, y;
        decode_tajima_ternary(b, &x, &y);
        flags = decode_exy_flags(b[2]);
        if (flags & END) {
            emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
    }
    return 1;
}

char
writeExy(EmbPattern* pattern, FILE* file)
{
    puts("ERROR: writeExy has not been finished.");
    REPORT_PTR(pattern);
    REPORT_PTR(file);
    return 0; /*TODO: finish writeExy */
}

/* Sierra Expanded Embroidery Format (.eys)
 * Stitch Only Format.
 * Smoothie G-Code Embroidery Format (.fxy)?
 */
char
readEys(EmbPattern* pattern , FILE* file)
{
    puts("ERROR: readEys and not been finished.");
    REPORT_PTR(pattern);
    REPORT_PTR(file);
    return 0; /*TODO: finish readEys */
}

char
writeEys(EmbPattern* pattern , FILE* file)
{
    puts("ERROR: writeEys and not been finished.");
    REPORT_PTR(pattern);
    REPORT_PTR(file);
    return 0; /*TODO: finish writeEys */
}

/* Fortron Embroidery Format (.fxy)
 * Stitch Only Format.
 */
char
readFxy(EmbPattern* pattern, FILE* file)
{
    /* TODO: review for combining code. This line appears
        to be the only difference from the GT format. */
    fseek(file, 0x100, SEEK_SET);

    while (!feof(file)) {
        int stitchType = NORMAL;
        int b1 = fgetc(file);
        int b2 = fgetc(file);
        unsigned char commandByte = (unsigned char)fgetc(file);

        if (commandByte == 0x91) {
            emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
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
        emb_pattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    return 1;
}

char
writeFxy(EmbPattern* pattern, FILE* file)
{
    puts("Overridden, defaulting to dst.");
    printf("%p %p\n", pattern, file);
    return 0; /*TODO: finish writeFxy */
}

/*
 * Smoothie G-Code
 *
 * Main Reference:
 *     Machinery's Handbook Guide
 *     A Guide to Tables, Formulas, & More in the 31st Edition
 *     by John Milton Amiss, Franklin D. Jones and Henry Ryffel
 */
char
readGc(EmbPattern* pattern , FILE* file)
{
    puts("ERROR: readGc and not been finished.");
    printf("%p %p\n", pattern, file);
    return 0; /*TODO: finish readGc */
}

char
writeGc(EmbPattern* pattern , FILE* file)
{
    puts("ERROR: writeGc and not been finished.");
    printf("%p %p\n", pattern, file);
    return 0; /*TODO: finish writeGc */
}

/*
 * Great Notions Embroidery Format (.gnc)
 * Stitch Only Format.
 */
/* TODO: finish readGnc */
char
readGnc(EmbPattern* pattern , FILE* file)
{
    puts("ERROR: readGnc and not been finished.");
    printf("%p %p\n", pattern, file);
    return 0;
}

/* TODO: finish writeGnc */
char
writeGnc(EmbPattern* pattern , FILE* file)
{
    puts("ERROR: writeGnc and not been finished.");
    printf("%p %p\n", pattern, file);
    return 0;
}

/*
 * Gold Thread Embroidery Format (.gt)
 * Stitch Only Format.
 */
char
readGt(EmbPattern* pattern, FILE* file)
{
    /* TODO: review for combining code. This line appears
        to be the only difference from the FXY format. */
    fseek(file, 0x200, SEEK_SET);

    while (!feof(file)) {
        int stitchType = NORMAL;
        int b1 = fgetc(file);
        int b2 = fgetc(file);
        unsigned char commandByte = (unsigned char)fgetc(file);

        if (commandByte == 0x91) {
            emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        if ((commandByte & 0x01) == 0x01) {
            stitchType = TRIM;
        }
        if ((commandByte & 0x02) == 0x02) {
            stitchType = STOP;
        }
        if ((commandByte & 0x20) == 0x20) {
            b1 = -b1;
        }
        if ((commandByte & 0x40) == 0x40) {
            b2 = -b2;
        }
        emb_pattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    return 1;
}

char
writeGt(EmbPattern* pattern, FILE* file)
{
    puts("ERROR: gt not supported in write mode.");
    printf("%p %p\n", pattern, file);
    return 0; /*TODO: finish writeGt */
}

/* Husqvarna Viking Embroidery Format (.hus)
 *
 * Stitch Only Format.
 */
int
husDecodeStitchType(unsigned char b)
{
    switch(b) {
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

unsigned char*
husDecompressData(unsigned char* input, int compressedInputLength, int decompressedContentLength)
{
    char* decompressedData = (char*)malloc(sizeof(char)*decompressedContentLength);
    if (!decompressedData) {
        printf("ERROR: husDecompressData(), cannot allocate memory for decompressedData\n");
        return 0;
    }
    hus_decompress((char*)input, compressedInputLength, decompressedData, &decompressedContentLength);
    return (unsigned char *)decompressedData;
}

unsigned char*
husCompressData(unsigned char* input, int decompressedInputSize, int* compressedSize)
{
    char* compressedData = (char*)malloc(sizeof(char)*decompressedInputSize*2);
    if (!compressedData) {
        printf("ERROR: husCompressData(), cannot allocate memory for compressedData\n");
        return 0;
    }
    hus_compress((char*)input, decompressedInputSize, compressedData, compressedSize);
    return (unsigned char *)compressedData;
}

int
husDecodeByte(unsigned char b)
{
    return (char)b;
}

unsigned char
husEncodeByte(EmbReal f)
{
    return (unsigned char)(int)emb_round(f);
}

unsigned char
husEncodeStitchType(int st)
{
    switch(st) {
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

char
readHus(EmbPattern* pattern, FILE* file)
{
    int fileLength;
    int magicCode, numberOfStitches, numberOfColors;
    int positiveXHoopSize, positiveYHoopSize, negativeXHoopSize, negativeYHoopSize;
    int attributeOffset, xOffset, yOffset;
    unsigned char *attributeData, *xData , *yData;
    unsigned char* attributeDataDecompressed = 0;
    unsigned char* xDecompressed = 0;
    unsigned char* yDecompressed = 0;
    unsigned char* stringVal = 0;

    int unknown, i = 0;

    fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x00, SEEK_SET);

    magicCode = emb_read_i32(file);
    numberOfStitches = emb_read_i32(file);
    numberOfColors = emb_read_i32(file);

    /* These should be put in the EmbPattern. */
    positiveXHoopSize = emb_read_i16(file);
    positiveYHoopSize = emb_read_i16(file);
    negativeXHoopSize = emb_read_i16(file);
    negativeYHoopSize = emb_read_i16(file);
    
    attributeOffset = emb_read_i32(file);
    xOffset = emb_read_i32(file);
    yOffset = emb_read_i32(file);

    REPORT_INT(magicCode)
    REPORT_INT(numberOfStitches)
    REPORT_INT(numberOfColors)
    REPORT_INT(positiveXHoopSize)
    REPORT_INT(positiveYHoopSize)
    REPORT_INT(negativeXHoopSize)
    REPORT_INT(negativeYHoopSize)
    REPORT_INT(attributeOffset)
    REPORT_INT(xOffset)
    REPORT_INT(yOffset)

    stringVal = (unsigned char*)malloc(sizeof(unsigned char)*8);
    if (!stringVal) {
        printf("ERROR: format-hus.c readHus(), cannot allocate memory for stringVal\n");
        return 0;
    }
    size_t size = 8;
    if (fread(stringVal, 1, size, file) != size) {
        puts("Ran out of bytes before full file read.");
        return 0;
    }

    unknown = emb_read_i16(file);
    printf("unknown: %d\n", unknown);
    for (i = 0; i < numberOfColors; i++) {
        short pos = emb_read_i16(file);
        emb_pattern_addThread(pattern, hus_colors[pos]);
    }

    attributeData = (unsigned char*)malloc(sizeof(unsigned char)*(xOffset - attributeOffset + 1));
    if (!attributeData) {
        printf("ERROR: format-hus.c readHus(), cannot allocate memory for attributeData\n");
        return 0;
    }
    size = xOffset - attributeOffset;
    if (fread(attributeData, 1, size, file) != size) {
        puts("Ran out of bytes before full file read.");
        return 0;
    }
    attributeDataDecompressed = husDecompressData(attributeData, size, numberOfStitches + 1);

    xData = (unsigned char*)malloc(sizeof(unsigned char)*(yOffset - xOffset + 1));
    if (!xData) {
        printf("ERROR: format-hus.c readHus(), cannot allocate memory for xData\n");
        return 0;
    }
    size = yOffset - xOffset;
    if (fread(xData, 1, size, file) != size) {
        puts("Ran out of bytes before full file read.");
        return 0;
    }
    xDecompressed = husDecompressData(xData, size, numberOfStitches);

    yData = (unsigned char*)malloc(sizeof(unsigned char)*(fileLength - yOffset + 1));
    if (!yData) {
        printf("ERROR: format-hus.c readHus(), cannot allocate memory for yData\n");
        return 0;
    }
    size = fileLength - yOffset;
    if (fread(yData, 1, size, file) != size) {
        puts("Ran out of bytes before full file read.");
        return 0;
    }
    yDecompressed = husDecompressData(yData, size, numberOfStitches);

    for (i = 0; i < numberOfStitches; i++) {
        int flag;
        EmbVector v;
        v.x = husDecodeByte(xDecompressed[i]) / 10.0;
        v.y = husDecodeByte(yDecompressed[i]) / 10.0;
        flag = husDecodeStitchType(attributeDataDecompressed[i]);
        emb_pattern_addStitchRel(pattern, v.x, v.y, flag, 1);
    }

    safe_free(stringVal);
    safe_free(xData);
    safe_free(xDecompressed);
    safe_free(yData);
    safe_free(yDecompressed);
    safe_free(attributeData);
    safe_free(attributeDataDecompressed);

    return 1;
}

char
writeHus(EmbPattern* pattern, FILE* file)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor, attributeSize, xCompressedSize, yCompressedSize, i;
    EmbReal previousX, previousY;
    short right, top, bottom, left;
    unsigned int code, colors, offset1, offset2;
    unsigned char *xValues = 0, *yValues = 0, *attributeValues = 0,
        *attributeCompressed = 0, *xCompressed = 0, *yCompressed = 0;

    stitchCount = pattern->stitch_list->count;
    /* emb_pattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */
    minColors = pattern->thread_list->count;
    patternColor = minColors;
    if (minColors > 24) minColors = 24;
    code = 0x00C8AF5B;
    emb_write_i32(file, code);
    emb_write_i32(file, stitchCount);
    emb_write_i32(file, minColors);

    boundingRect = emb_pattern_bounds(pattern);
    right = (int16_t) emb_round((boundingRect.w + boundingRect.x) * 10.0);
    top = (int16_t) -emb_round(boundingRect.y * 10.0);
    left = (int16_t) emb_round(boundingRect.x * 10.0);
    bottom = (int16_t) -emb_round((boundingRect.h + boundingRect.y) * 10.0);
    emb_write_i16(file, right);
    emb_write_i16(file, top);
    emb_write_i16(file, left);
    emb_write_i16(file, bottom);

    colors = 0x2A + 2 * minColors;
    emb_write_i32(file, colors);

    xValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if (!xValues) {
        printf("ERROR: format-hus.c writeHus(), cannot allocate memory for xValues\n");
        return 0;
    }
    yValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if (!yValues) {
        printf("ERROR: format-hus.c writeHus(), cannot allocate memory for yValues\n");
        return 0;
    }
    attributeValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if (!attributeValues) {
        printf("ERROR: format-hus.c writeHus(), cannot allocate memory for attributeValues\n");
        return 0;
    }

    previousX = 0.0;
    previousY = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st;
        st = pattern->stitch_list->stitch[i];
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

    offset1 = (unsigned int) (0x2A + 2 * patternColor + attributeSize);
    offset2 = (unsigned int) (0x2A + 2 * patternColor + attributeSize + xCompressedSize);
    emb_write_i32(file, offset1);
    emb_write_i32(file, offset2);
    fpad(file, 0, 10);

    for (i = 0; i < patternColor; i++) {
        short color_index = (int16_t)emb_find_nearest_thread(pattern->thread_list->thread[i].color, (EmbThread*)hus_colors, 29);
        emb_write_i16(file, color_index);
    }

    fwrite(attributeCompressed, 1, attributeSize, file);
    fwrite(xCompressed, 1, xCompressedSize, file);
    fwrite(yCompressed, 1, yCompressedSize, file);

    safe_free(xValues);
    safe_free(xCompressed);
    safe_free(yValues);
    safe_free(yCompressed);
    safe_free(attributeValues);
    safe_free(attributeCompressed);

    return 1;
}

/*
 * Inbro Embroidery Format (.inb)
 * Stitch Only Format.
 */
char
readInb(EmbPattern* pattern, FILE* file)
{
    /* TODO: determine what this represents */
    unsigned char fileDescription[8], nullVal, bytesUnknown[300];
    int stitchCount, x, y, i, fileLength;
    short width, height, colorCount, unknown3, unknown2,
        nullbyte, left, right, top, bottom, imageWidth, imageHeight;

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fread(fileDescription, 1, 8, file); /* TODO: check return value */
    LOAD_U8(file, nullVal)
    fgetc(file);
    fgetc(file);
    LOAD_I32(file, stitchCount)
    LOAD_I16(file, width)
    LOAD_I16(file, height)
    LOAD_I16(file, colorCount)
    LOAD_I16(file, unknown3)
    LOAD_I16(file, unknown2)
    LOAD_I16(file, imageWidth)
    LOAD_I16(file, imageHeight)
    fread(bytesUnknown, 1, 300, file); /* TODO: check return value */
    LOAD_I16(file, nullbyte)
    LOAD_I16(file, left)
    LOAD_I16(file, right)
    LOAD_I16(file, top)
    LOAD_I16(file, bottom)

    fseek(file, 0x2000, SEEK_SET);
    /* Calculate stitch count since header has been seen to be blank */
    stitchCount = (int)((fileLength - 0x2000) / 3);
    for (i = 0; i < stitchCount; i++) {
        unsigned char type;
        int stitch = NORMAL;
        x = (char)fgetc(file);
        y = (char)fgetc(file);
        type = (char)fgetc(file);
        if ((type & 0x40) > 0)
            x = -x;
        if ((type & 0x10) > 0)
            y = -y;
        if ((type & 1) > 0)
            stitch = STOP;
        if ((type & 2) > 0)
            stitch = TRIM;
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitch, 1);
    }
    emb_pattern_flipVertical(pattern);

    return 1;
}

char
writeInb(EmbPattern* pattern, FILE* file)
{
    puts("ERROR: writeInb not implemented.");
    REPORT_PTR(pattern)
    REPORT_PTR(file)
    return 0; /*TODO: finish writeInb */
}

/*
 * Embroidery Color Format (.inf)
 *
 * Stitch Only Format.
 */

char
readInf(EmbPattern* pattern, FILE* file)
{
    int nColors, i;
    char colorType[50];
    char colorDescription[50];
    EmbThread t;

    fseek(file, 12, SEEK_CUR);
    nColors = emb_read_i32be(file);

    pattern->thread_list->count = 0;

    for (i = 0; i < nColors; i++) {
        fseek(file, 4, SEEK_CUR);
        embColor_read(file, &(t.color), 3);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        emb_pattern_addThread(pattern, t);
        fseek(file, 2, SEEK_CUR);
        binaryReadString(file, colorType, 50);
        binaryReadString(file, colorDescription, 50);
    }
    return 1;
}

char
writeInf(EmbPattern* pattern, FILE* file)
{
    int i, bytesRemaining;

    emb_write_u32be(file, 0x01);
    emb_write_u32be(file, 0x08);
    /* write place holder offset */
    emb_write_u32be(file, 0x00);
    emb_write_u32be(file, pattern->thread_list->count);

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbString buffer;
        unsigned short record_length, record_number, needle_number;
        EmbColor c;
        c = pattern->thread_list->thread[i].color;
        sprintf(buffer, "RGB(%d,%d,%d)", (int)c.r, (int)c.g, (int)c.b);
        record_length = 14 + strlen(buffer);
        record_number = i;
        needle_number = i;
        emb_write_i16be(file, record_length);
        emb_write_i16be(file, record_number);
        embColor_write(file, c, 3);
        emb_write_i16be(file, needle_number);
        fwrite("RGB\0", 1, 4, file);
        fprintf(file, "%s", buffer);
        fwrite("\0", 1, 1, file);
    }
    /* It appears that there should be a pad here otherwise it clips into
     * the color description. */
    fpad(file, 0, 8);
    fseek(file, -8, SEEK_END);
    bytesRemaining = ftell(file);
    fseek(file, 8, SEEK_SET);
    emb_write_u32be(file, bytesRemaining);
    return 1;
}

/*
 * Janome Embroidery Format (.jef)
 * Stitch Only Format.
 */
int
jefGetHoopSize(int width, int height)
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
    return ((int) HOOP_110X110);
}

char
jefDecode(unsigned char inputByte) {
    if (inputByte >= 0x80) {
        return (char) ((-~inputByte) - 1);
    }
    return ((char) inputByte);
}

void
jefSetHoopFromId(EmbPattern* pattern, int hoopCode)
{
    if (!pattern) {
        printf("ERROR: format-jef.c jefSetHoopFromId(), pattern argument is null\n");
        return;
    }
    switch (hoopCode) {
    case HOOP_126X110:
        pattern->hoop_height = 126.0;
        pattern->hoop_width = 110.0;
        break;
    case HOOP_50X50:
        pattern->hoop_height = 50.0;
        pattern->hoop_width = 50.0;
        break;
    case HOOP_110X110:
        pattern->hoop_height = 110.0;
        pattern->hoop_width = 110.0;
        break;
    case HOOP_140X200:
        pattern->hoop_height = 140.0;
        pattern->hoop_width = 200.0;
        break;
    default:
    case HOOP_230X200:
        pattern->hoop_height = 230.0;
        pattern->hoop_width = 200.0;
        break;
    }
}

struct hoop_padding
{
    int left;
    int right;
    int top;
    int bottom;
};

void
read_hoop(FILE* file, struct hoop_padding *hoop, char *label)
{
    if (emb_verbose>1) {
        printf("%s\n", label);
    }
    hoop->left = emb_read_i32(file);
    hoop->top = emb_read_i32(file);
    hoop->right = emb_read_i32(file);
    hoop->bottom = emb_read_i32(file);
}

char
readJef(EmbPattern* pattern, FILE* file)
{
    int stitchOffset, formatFlags, numberOfColors, numberOfStitchs;
    int hoopSize, i, stitchCount;
    struct hoop_padding bounds, rectFrom110x110;
    struct hoop_padding rectFrom50x50, rectFrom200x140, rect_from_custom;
    EmbString date;
    EmbString time;

    stitchOffset = emb_read_i32(file);
    formatFlags = emb_read_i32(file); /* TODO: find out what this means */

    fread(date, 1, 8, file); /* TODO: check return value */
    fread(time, 1, 8, file); /* TODO: check return value */
    numberOfColors = emb_read_i32(file);
    numberOfStitchs = emb_read_i32(file);
    hoopSize = emb_read_i32(file);
    jefSetHoopFromId(pattern, hoopSize);
    if (numberOfStitchs > MAX_STITCHES) {
        numberOfStitchs = MAX_STITCHES;
        puts("ERROR: this file is corrupted or has too many stitches.");
        return 0;
    }
    if (emb_verbose>1) {
        printf("format flags = %d\n", formatFlags);
        printf("number of colors = %d\n", numberOfColors);
        printf("number of stitches = %d\n", numberOfStitchs);
    }

    read_hoop(file, &bounds, "bounds");
    read_hoop(file, &rectFrom110x110, "rectFrom110x110");
    read_hoop(file, &rectFrom50x50, "rectFrom50x50");
    read_hoop(file, &rectFrom200x140, "rectFrom200x140");
    read_hoop(file, &rect_from_custom, "rect_from_custom");

    for (i = 0; i < numberOfColors; i++) {
        int thread_num = emb_read_i32(file);
        emb_pattern_addThread(pattern, jef_colors[thread_num % 79]);
    }
    fseek(file, stitchOffset, SEEK_SET);
    stitchCount = 0;
    while (stitchCount < numberOfStitchs + 100) {
        unsigned char b[2];
        char dx = 0, dy = 0;
        int flags = NORMAL;
        if (fread(b, 1, 2, file) != 2) {
            break;
        }

        if (b[0] == 0x80) {
            if (b[1] & 1) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                flags = STOP;
            }
            else if ((b[1] == 2) || (b[1] == 4) || b[1] == 6) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                flags = TRIM;
            }
            else if (b[1] == 0x10) {
                emb_pattern_addStitchRel(pattern, 0.0, 0.0, END, 1);
                break;
            }
        }
        dx = jefDecode(b[0]);
        dy = jefDecode(b[1]);
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
        stitchCount++;
    }
    return 1;
}

void
jefEncode(unsigned char* b, char dx, char dy, int flags)
{
    if (!b) {
        printf("ERROR: format-jef.c expEncode(), b argument is null\n");
        return;
    }
    if (flags == STOP) {
        b[0] = 0x80;
        b[1] = 1;
        b[2] = dx;
        b[3] = dy;
    }
    else if (flags == END) {
        b[0] = 0x80;
        b[1] = 0x10;
        b[2] = 0;
        b[3] = 0;
    }
    else if (flags == TRIM || flags == JUMP) {
        b[0] = 0x80;
        b[1] = 2;
        b[2] = dx;
        b[3] = dy;
    }
    else {
        b[0] = dx;
        b[1] = dy;
    }
}

char
writeJef(EmbPattern* pattern, FILE* file)
{
    int colorlistSize, minColors, designWidth, designHeight, i;
    EmbRect boundingRect;
    EmbTime time;
    EmbReal width, height;
    int data;
    EmbVector pos;

    emb_pattern_correctForMaxStitchLength(pattern, 12.7, 12.7);

    colorlistSize = pattern->thread_list->count;
    minColors = EMB_MAX(colorlistSize, 6);
    emb_write_i32(file, 0x74 + (minColors * 4));
    emb_write_i32(file, 0x0A);

    embTime_initNow(&time);

    fprintf(file, "%04d%02d%02d%02d%02d%02d", (int)(time.year + 1900),
            (int)(time.month + 1), (int)(time.day), (int)(time.hour),
            (int)(time.minute), (int)(time.second));
    fpad(file, 0, 2);
    emb_write_i32(file, pattern->thread_list->count);
    data = pattern->stitch_list->count + EMB_MAX(0, (6 - colorlistSize) * 2) + 1;
    emb_write_i32(file, data);

    boundingRect = emb_pattern_bounds(pattern);
    width = boundingRect.w;
    height = boundingRect.h;
    designWidth = (int)(width * 10.0);
    designHeight = (int)(height * 10.0);

    emb_write_i32(file, jefGetHoopSize(designWidth, designHeight));

    /* Distance from center of Hoop */
    emb_write_i32(file, (int) (designWidth / 2));  /* left */
    emb_write_i32(file, (int) (designHeight / 2)); /* top */
    emb_write_i32(file, (int) (designWidth / 2));  /* right */
    emb_write_i32(file, (int) (designHeight / 2)); /* bottom */

    /* Distance from default 110 x 110 Hoop */
    if (EMB_MIN(550 - designWidth / 2, 550 - designHeight / 2) >= 0) {
        emb_write_i32(file, EMB_MAX(-1, 550 - designWidth / 2));  /* left */
        emb_write_i32(file, EMB_MAX(-1, 550 - designHeight / 2)); /* top */
        emb_write_i32(file, EMB_MAX(-1, 550 - designWidth / 2));  /* right */
        emb_write_i32(file, EMB_MAX(-1, 550 - designHeight / 2)); /* bottom */
    } else {
        emb_write_i32(file, -1);
        emb_write_i32(file, -1);
        emb_write_i32(file, -1);
        emb_write_i32(file, -1);
    }

    /* Distance from default 50 x 50 Hoop */
    if (EMB_MIN(250 - designWidth / 2, 250 - designHeight / 2) >= 0) {
        emb_write_i32(file, (int) EMB_MAX(-1, 250 - designWidth / 2));  /* left */
        emb_write_i32(file, (int) EMB_MAX(-1, 250 - designHeight / 2)); /* top */
        emb_write_i32(file, (int) EMB_MAX(-1, 250 - designWidth / 2));  /* right */
        emb_write_i32(file, (int) EMB_MAX(-1, 250 - designHeight / 2)); /* bottom */
    } else {
        emb_write_i32(file, -1);
        emb_write_i32(file, -1);
        emb_write_i32(file, -1);
        emb_write_i32(file, -1);
    }

    /* Distance from default 140 x 200 Hoop */
    emb_write_i32(file, (int) (700 - designWidth / 2));   /* left */
    emb_write_i32(file, (int) (1000 - designHeight / 2)); /* top */
    emb_write_i32(file, (int) (700 - designWidth / 2));   /* right */
    emb_write_i32(file, (int) (1000 - designHeight / 2)); /* bottom */

    /* repeated Distance from default 140 x 200 Hoop */
    /* TODO: Actually should be distance to custom hoop */
    emb_write_i32(file, (int) (630 - designWidth / 2));  /* left */
    emb_write_i32(file, (int) (550 - designHeight / 2)); /* top */
    emb_write_i32(file, (int) (630 - designWidth / 2));  /* right */
    emb_write_i32(file, (int) (550 - designHeight / 2)); /* bottom */

    for (i = 0; i < pattern->thread_list->count; i++) {
        int j = emb_find_nearest_thread(pattern->thread_list->thread[i].color, (EmbThread *)jef_colors, 79);
        emb_write_i32(file, j);
    }

    for (i = 0; i < (minColors - colorlistSize); i++) {
        int a = 0x0D;
        emb_write_i32(file, a);
    }

    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned char b[4];
        EmbStitch st;
        char dx, dy;
        b[0] = 0;
        b[1] = 0;
        b[2] = 0;
        b[3] = 0;
        st = pattern->stitch_list->stitch[i];
        dx = (char)emb_round(10.0*(st.x - pos.x));
        dy = (char)emb_round(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;
        jefEncode(b, dx, dy, st.flags);
        if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
            fwrite(b, 1, 4, file);
        } else {
            fwrite(b, 1, 2, file);
        }
    }
    return 1;
}

/*
\subsection pfaff-ksm-format Pfaff professional Design format (.ksm)

Stitch Only Format.
 */

void
ksmEncode(unsigned char* b, char dx, char dy, int flags)
{
    if (!b) {
        printf("ERROR: format-ksm.c ksmEncode(), b argument is null\n");
        return;
    }
    /* TODO: How to encode JUMP stitches? JUMP must be handled.
    Also check this for the EXP format since it appears to be similar */
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

char
readKsm(EmbPattern* pattern, FILE* file)
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
        if (b[2] & 0x40) {
            b[1] = -b[1];
        }
        if (b[2] & 0x20) {
            b[0] = -b[0];
        }
        emb_pattern_addStitchRel(pattern, b[1] / 10.0, b[0] / 10.0, flags, 1);
    }
    return 1;
}

char
writeKsm(EmbPattern* pattern, FILE* file)
{
    EmbVector pos;
    int i;

    fpad(file, 0, 0x200);
    /* write stitches */
    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned char b[4];
        char dx, dy;
        EmbStitch st = pattern->stitch_list->stitch[i];
        dx = (char)(10.0*(st.x - pos.x));
        dy = (char)(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;
        ksmEncode(b, dx, dy, st.flags);
        fprintf(file, "%c%c", b[0], b[1]);
    }
    fprintf(file, "\x1a");
    return 1;
}

/* Pfaff Embroidery Format (.max)
 * Stitch Only Format.
 */
const unsigned char max_header[] = {
    0x56,0x43,0x53,0x4D,0xFC,0x03,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,
    0xF6,0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x05,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x33,0x37,0x38,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4D,0x61,0x64,0x65,0x69,0x72,0x61,0x20,
    0x52,0x61,0x79,0x6F,0x6E,0x20,0x34,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x01,0x38,0x09,0x31,0x33,0x30,0x2F,0x37,0x30,0x35,0x20,0x48,0xFA,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00
};


/* ---------------------------------------------------------------- */
/* format max */

/* Pfaff MAX embroidery file format */
char
readMax(EmbPattern* pattern, FILE* file)
{
    unsigned char b[8];

    fseek(file, 0xD5, SEEK_SET);
    /* stitchCount = emb_read_i32(file); CHECK IF THIS IS PRESENT */
    /* READ STITCH RECORDS */
    while (fread(b, 1, 8, file) == 8) {
        EmbReal dx, dy;
        int flags;
        flags = NORMAL;
        dx = pfaffDecode(b[0], b[1], b[2]);
        dy = pfaffDecode(b[4], b[5], b[6]);
        emb_pattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    emb_pattern_flipVertical(pattern);
    return 1;
}

char
writeMax(EmbPattern* pattern, FILE* file)
{
    int i;
    EmbReal x, y;
    EmbStitch st;

    fwrite(max_header, 1, 0xD5, file);
    for (i = 0; i < pattern->stitch_list->count; i++) {
        st = pattern->stitch_list->stitch[i];
        x = (int)emb_round(st.x * 10.0);
        y = (int)emb_round(st.y * 10.0);
        write_24bit(file, x);
        write_24bit(file, y);
    }
    return 1;
}

/* Mitsubishi Embroidery Format (.mit)
 *
 * Stitch Only Format.
 */
char
readMit(EmbPattern* pattern, FILE* file)
{
    unsigned char data[2];

    while (fread(data, 1, 2, file) == 2) {
        int x = mitDecodeStitch(data[0]);
        int y = mitDecodeStitch(data[1]);
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, NORMAL, 1);
    }
    return 1;
}

char
writeMit(EmbPattern* pattern, FILE* file)
{
    EmbReal xx, yy;
    int i;

    emb_pattern_correctForMaxStitchLength(pattern, 0x1F, 0x1F);
    xx = 0;
    yy = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned char b[2];
        EmbStitch st = pattern->stitch_list->stitch[i];
        b[0] = mitEncodeStitch(st.x - xx);
        b[1] = mitEncodeStitch(st.y - yy);
        xx = st.x;
        yy = st.y;
        fwrite(b, 1, 2, file);
    }
    return 1;
}

/* Ameco Embroidery Format (.new)
 *
 * Stitch Only Format.
 */
char
readNew(EmbPattern* pattern, FILE* file)
{
    unsigned int stitchCount;
    unsigned char data[3];

    LOAD_I16(file, stitchCount)
    while (fread(data, 1, 3, file) == 3) {
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
        if (val != 0 && data[2] != 0x9B && data[2] != 0x91) {
            int z = 1;
        }*/
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, flag, 1);
    }

    return 1;
}

/* . */
char
writeNew(EmbPattern* pattern, FILE* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeNew */
}

/* Melco Embroidery Format (.ofm)
 *
 * Stitch Only Format.
 */
char*
ofmReadLibrary(FILE* file)
{
    int stringLength = 0;
    char* libraryName = 0;
    /* FF FE FF */
    unsigned char leadIn[3];

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadLibrary(), file argument is null\n");
        return 0;
    }

    fread(leadIn, 1, 3, file); /* TODO: check return value */
    unsigned char a;
    fread(&a, 1, 1, file);
    stringLength = a;
    libraryName = (char*)malloc(sizeof(char) * stringLength * 2);
    if (!libraryName) {
        printf("ERROR: format-ofm.c ofmReadLibrary(), unable to allocate memory for libraryName\n");
        return 0;
    }
    fread((unsigned char*)libraryName, 1, stringLength * 2, file); /* TODO: check return value */
    return libraryName;
}

static int
ofmReadClass(FILE* file)
{
    int len;
    EmbString s;

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadClass(), file argument is null\n");
        return 0;
    }

    emb_read_i16(file);
    len = emb_read_i16(file);

    fread((unsigned char*)s, 1, len, file);
    /* TODO: check return value */
    s[len] = '\0';
    if (!strcmp(s, "CExpStitch")) {
        return 0x809C;
    }
    if (!strcmp(s, "CColorChange")) {
        return 0xFFFF;
    }
    return 0;
}

void
ofmReadBlockHeader(FILE* file)
{
    int val[10], i; /* TODO: determine what these represent */
    unsigned char len;
    char* s = 0;
    unsigned short short1;
    short unknown1;
    /* TODO: determine what the unknown variables represent */
    int unknown3, unknown2;
    /* TODO: determine what this represents */

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadBlockHeader(), file argument is null\n");
        return;
    }

    LOAD_I16(file, unknown1)
    LOAD_I32(file, unknown2)
    LOAD_I32(file, unknown3)

    /* int v = fread(&v, 1, 3, file)?; TODO: review */
    emb_read_i16(file);
    fseek(file, 1, SEEK_CUR);
    len = (char)fgetc(file);
    s = (char*)malloc(2 * len);
    if (!s) {
        printf("ERROR: format-ofm.c ofmReadBlockHeader(), unable to allocate memory for s\n");
        return;
    }
    fread((unsigned char *)s, 1, 2 * len, file);
    /* TODO: check return value */
    /* 0, 0, 0, 0, 1, 1, 1, 0, 64, 64 */
    for (i=0; i<10; i++) {
        val[i] = emb_read_i32(file);
        printf("%d", val[i]);
    }
    LOAD_I16(file, short1) /*  0 */
}

/* . */
void
ofmReadColorChange(FILE* file, EmbPattern* pattern)
{
    if (!file) {
        printf("ERROR: format-ofm.c ofmReadColorChange(), file argument is null\n");
        return;
    }
    if (!pattern) {
        printf("ERROR: format-ofm.c ofmReadColorChange(), pattern argument is null\n");
        return;
    }

    ofmReadBlockHeader(file);
    emb_pattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
}

void
ofmReadThreads(FILE* file, EmbPattern* p)
{
    int i, numberOfColors, stringLen, numberOfLibraries;
    char* primaryLibraryName = 0;
    char* expandedString = 0;

    if (!file) {
        printf("ERROR: ofm_read_threads(), file argument is null\n");
        return;
    }
    if (!p) {
        printf("ERROR: ofm_read_threads(), p argument is null\n");
        return;
    }

    /* FF FE FF 00 */
    fseek(file, 4, SEEK_CUR);

    numberOfColors = emb_read_i16(file);

    fseek(file, 4, SEEK_CUR);
    stringLen = emb_read_i16(file);
    expandedString = (char*)malloc(stringLen);
    if (!expandedString) {
        printf("ERROR: format-ofm.c ofm_read_threads(), unable to allocate memory for expandedString\n");
        return;
    }
    fread((unsigned char*)expandedString, 1, stringLen, file);
    /* TODO: check return value */
    for (i = 0; i < numberOfColors; i++) {
        EmbThread thread;
        char colorNumberText[11], colorName[512];
        int threadLibrary, colorNameLength, colorNumber;
        embColor_read(file, &(thread.color), 4);
        LOAD_I16(file, threadLibrary)
        fseek(file, 2, SEEK_CUR);
        LOAD_I32(file, colorNumber)
        fseek(file, 3, SEEK_CUR);
        LOAD_I8(file, colorNameLength)
        fread(colorName, 1, colorNameLength*2, file);
        /* TODO: check return value */
        fseek(file, 2, SEEK_CUR);
        sprintf(colorNumberText, "%10d", colorNumber);
        strcpy(thread.catalogNumber, colorNumberText);
        strcpy(thread.description, colorName);
        emb_pattern_addThread(p, thread);
    }
    fseek(file, 2, SEEK_CUR);
    primaryLibraryName = ofmReadLibrary(file);
    numberOfLibraries = emb_read_i16(file);

    if (emb_verbose>1) {
        printf("primary library name: %s\n", primaryLibraryName);
    }

    for (i = 0; i < numberOfLibraries; i++) {
        /*libraries.Add( TODO: review */
        char* libName = ofmReadLibrary(file);
        safe_free(libName);
    }
}

EmbReal
ofmDecode(unsigned char b1, unsigned char b2)
{
    EmbReal val = (EmbReal)(int16_t)(b1 << 8 | b2);
    return val;
}

void
ofmReadExpanded(FILE* file, EmbPattern* p)
{
    int i, numberOfStitches = 0;

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadExpanded(), file argument is null\n");
        return;
    }
    if (!p) {
        printf("ERROR: format-ofm.c ofmReadExpanded(), p argument is null\n");
        return;
    }

    ofmReadBlockHeader(file);
    numberOfStitches = emb_read_i32(file);

    for (i = 0; i < numberOfStitches; i++) {
        unsigned char stitch[5];
        fread(stitch, 1, 5, file); /* TODO: check return value */
        if (stitch[0] == 0) {
            EmbReal x = ofmDecode(stitch[1], stitch[2]) / 10.0;
            EmbReal y = ofmDecode(stitch[3], stitch[4]) / 10.0;
            emb_pattern_addStitchAbs(p, x, y, i == 0 ? JUMP : NORMAL, 1);
        }
        else if (stitch[0] == 32) {
            EmbReal x = ofmDecode(stitch[1], stitch[2]) / 10.0;
            EmbReal y = ofmDecode(stitch[3], stitch[4]) / 10.0;
            emb_pattern_addStitchAbs(p, x, y, i == 0 ? TRIM : NORMAL, 1);
        }
    }
}

char
readOfm(EmbPattern* pattern, FILE* fileCompound)
{
    int unknownCount, key = 0, classNameLength;
    char* s = 0;
    FILE* file;
    bcf_file* bcfFile = 0;

    if (emb_verbose>1) {
        puts("Overridden during development.");
        return 0;
    }

    bcfFile = (bcf_file*)malloc(sizeof(bcf_file));
    if (!bcfFile) {
        printf("ERROR: format-ofm.c readOfm(), unable to allocate memory for bcfFile\n");
        return 0;
    }
    bcfFile_read(fileCompound, bcfFile);
    file = GetFile(bcfFile, fileCompound, "EdsIV Object");
    bcf_file_free(bcfFile);
    bcfFile = 0;
    fseek(file, 0x1C6, SEEK_SET);
    ofmReadThreads(file, pattern);
    fseek(file, 0x110, SEEK_CUR);
    fseek(file, 0x4, SEEK_CUR); /* EMB_INT32_LITTLE */
    classNameLength = emb_read_i16(file);
    s = (char*)malloc(sizeof(char) * classNameLength);
    if (!s) {
        printf("ERROR: format-ofm.c readOfm(), unable to allocate memory for s\n");
        return 0;
    }
    fread((unsigned char*)s, 1, classNameLength, file); /* TODO: check return value */
    unknownCount = emb_read_i16(file);
    /* TODO: determine what unknown count represents */
    if (emb_verbose>1) {
        printf("unknownCount = %d\n", unknownCount);
    }

    emb_read_i16(file);
    key = ofmReadClass(file);
    while (1) {
        if (key == 0xFEFF) {
            break;
        }
        if (key == 0x809C) {
            ofmReadExpanded(file, pattern);
        }
        else {
            ofmReadColorChange(file, pattern);
        }
        LOAD_U16(file, key)
        if (key == 0xFFFF) {
            ofmReadClass(file);
        }
    }

    emb_pattern_flip(pattern, 1, 1);

    return 1;
}

char
writeOfm(EmbPattern* pattern, FILE* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeOfm */
}

/* Pfaff PCD File Format (.pcd)
 *
 * Stitch Only Format.
 *
 * The format uses a signed 3 byte-length number type.
 *
 * See the description here ([5](5)) for the overview of the format.
 *
 * For an example of the format see ([11](11)).
 *
 */
char
readPcd(EmbPattern* pattern, const char *fileName, FILE* file)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    EmbReal dx = 0, dy = 0;
    int st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount = 0;

    version = (char)fgetc(file);
    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * 3 for PCS with large hoop (115x120)
     */
    hoopSize = (char)fgetc(file);
    LOAD_U16(file, colorCount)
    if (emb_verbose>1) {
        printf("version: %d\n", version);
        printf("hoop size: %d\n", hoopSize);
    }

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        emb_pattern_addThread(pattern, t);
    }
    if (allZeroColor) {
        emb_pattern_loadExternalColorFile(pattern, fileName);
    }
    LOAD_U16(file, st)
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        int flags;
        if (fread(b, 1, 9, file) != 9) {
            break;
        }
        flags = NORMAL;
        if (b[8] & 0x01) {
            flags = STOP;
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
        /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[1], b[2], b[3]);
        dy = pfaffDecode(b[5], b[6], b[7]);
        emb_pattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writePcd(EmbPattern* pattern, FILE* file)
{
    int i;

    /* TODO: select hoop size defaulting to Large PCS hoop */
    fwrite("2\x03", 1, 2, file);
    emb_write_u16(file, (unsigned short)pattern->thread_list->count);
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor color = pattern->thread_list->thread[i].color;
        embColor_write(file, color, 4);
    }

    fpad(file, 0, 4*(16-i));
    /* write remaining colors to reach 16 */

    emb_write_u16(file, (unsigned short)pattern->stitch_list->count);
    /* write stitches */
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        pfaffEncode(file, (int)emb_round(st.x * 10.0), (int)emb_round(st.y * 10.0), st.flags);
    }
    return 1;
}

/*
 * Pfaff Embroidery Format (.pcm)
 *
 * The Pfaff pcm format is stitch-only.
 */
char
readPcm(EmbPattern* pattern, FILE* file)
{
    int i = 0, st;
    EmbReal dx = 0, dy = 0;
    int header_size = 16*2+6;

    if (emb_verbose>1) {
        printf("TODO: check header_size %d\n", header_size);
    }

    fseek(file, 4, SEEK_SET);
    for (i = 0; i < 16; i++) {
        int colorNumber;
        (void)fgetc(file); /* zero */
        colorNumber = fgetc(file);
        emb_pattern_addThread(pattern, pcm_colors[colorNumber]);
    }
    st = emb_read_i16be(file);
    st = EMB_MIN(st, MAX_STITCHES);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        int flags;
        unsigned char b[9];
        flags = NORMAL;
        if (fread(b, 1, 9, file) != 9) {
            break;
        }
        if (b[8] & 0x01) {
            flags = STOP;
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
        /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[2], b[1], b[0]);
        dy = pfaffDecode(b[6], b[5], b[4]);
        emb_pattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writePcm(EmbPattern* pattern, FILE* file)
{
    puts("overridden, defaulting to dst");
    writeDst(pattern, file);
    return 0; /*TODO: finish writePcm */
}

/*
 * Pfaff Embroidery Format (.pcq)
 *
 * The Pfaff pcq format is stitch-only.
 */
char
readPcq(EmbPattern* pattern, const char* fileName, FILE* file)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    EmbReal dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount;

    version = (char)fgetc(file);
    hoopSize = (char)fgetc(file);
    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * 3 for PCS with large hoop (115x120)
     */
    LOAD_U16(file, colorCount)
    if (emb_verbose>1) {
        printf("version: %d\n", version);
        printf("hoop size: %d\n", hoopSize);
    }

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        emb_pattern_addThread(pattern, t);
    }
    if (allZeroColor) {
        emb_pattern_loadExternalColorFile(pattern, fileName);
    }
    LOAD_U16(file, st)
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        flags = NORMAL;
        if (fread(b, 1, 9, file) != 9) {
            break;
        }

        if (b[8] & 0x01) {
            flags = STOP;
        }
        else if (b[8] & 0x04) {
            flags = TRIM;
        }
        else if (b[8] != 0) {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[1], b[2], b[3]);
        dy = pfaffDecode(b[5], b[6], b[7]);
        emb_pattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writePcq(EmbPattern* pattern, FILE* file)
{
    int i;

    /* TODO: select hoop size defaulting to Large PCS hoop */
    fwrite("2\x03", 1, 2, file);
    emb_write_u16(file, (unsigned short)pattern->thread_list->count);
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor color = pattern->thread_list->thread[i].color;
        embColor_write(file, color, 4);
    }

    /* write remaining colors to reach 16 */
    fpad(file, 0, (16-i)*4);

    emb_write_u16(file, (unsigned short)pattern->stitch_list->count);
    /* write stitches */
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        pfaffEncode(file, (int)emb_round(st.x * 10.0), (int)emb_round(st.y * 10.0), st.flags);
    }
    return 1;
}

/*
 * Pfaff Embroidery Format (.pcs)
 *
 * The Pfaff pcs format is stitch-only.
 */
char
readPcs(EmbPattern* pattern, const char* fileName, FILE* file)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    EmbReal dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount;

    version = (char)fgetc(file);

    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * 3 for PCS with large hoop (115x120)
     */
    hoopSize = (char)fgetc(file);
    switch(hoopSize) {
        case 2:
            pattern->hoop_width = 80.0;
            pattern->hoop_height = 80.0;
            break;
        case 3:
            pattern->hoop_width = 115.0;
            pattern->hoop_height = 120.0;
            break;
    }

    LOAD_U16(file, colorCount)
    if (emb_verbose>1) {
        printf("version: %d\n", version);
        printf("hoop size: %d\n", hoopSize);
        printf("color count: %d\n", colorCount);
    }

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        emb_pattern_addThread(pattern, t);
    }
    if (allZeroColor) {
        emb_pattern_loadExternalColorFile(pattern, fileName);
    }
    LOAD_U16(file, st)
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        flags = NORMAL;
        if (fread(b, 1, 9, file) != 9)
            break;

        if (b[8] & 0x01) {
            flags = STOP;
        }
        else if (b[8] & 0x04) {
            flags = TRIM;
        }
        else if (b[8] != 0) {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[1], b[2], b[3]);
        dy = pfaffDecode(b[5], b[6], b[7]);
        emb_pattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

char
writePcs(EmbPattern* pattern, FILE* file)
{
    int i;

    /* TODO: select hoop size defaulting to Large PCS hoop */
    fwrite("2\x03", 1, 2, file);
    emb_write_u16(file, (unsigned short)pattern->thread_list->count);
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor color = pattern->thread_list->thread[i].color;
        embColor_write(file, color, 4);
    }

    /* write remaining colors to reach 16 */
    /* fpad(file, 0, 4*(16-i)); */

    emb_write_u16(file, (unsigned short)pattern->stitch_list->count);
    /* write stitches */
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        pfaffEncode(file, (int)emb_round(st.x * 10.0), (int)emb_round(st.y * 10.0), st.flags);
    }
    return 1;
}

/*
 * Brother Embroidery Format (.pec)
 * The Brother pec format is stitch-only.
 */
void
readPecStitches(EmbPattern* pattern, FILE* file)
{
    void *f = file;
    unsigned char b[2];

    while (fread(b, 1, 2, f)==2) {
        int val1 = (int)b[0];
        int val2 = (int)b[1];

        int stitchType = NORMAL;
        if (b[0] == 0xFF && b[1] == 0x00) {
            emb_pattern_end(pattern);
            return;
        }
        if (b[0] == 0xFE && b[1] == 0xB0) {
            (void)fgetc(f);
            emb_pattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
            continue;
        }
        /* High bit set means 12-bit offset, otherwise 7-bit signed delta */
        if (val1 & 0x80) {
            if (val1 & 0x20) stitchType = TRIM;
            if (val1 & 0x10) stitchType = JUMP;
            val1 = ((val1 & 0x0F) << 8) + val2;

            /* Signed 12-bit arithmetic */
            if (val1 & 0x800) {
                val1 -= 0x1000;
            }
        }
        else if (val1 >= 0x40) {
            val1 -= 0x80;
        }
        if (val2 & 0x80) {
            if (val2 & 0x20) stitchType = TRIM;
            if (val2 & 0x10) stitchType = JUMP;
            val2 = ((val2 & 0x0F) << 8) + fgetc(file);

            /* Signed 12-bit arithmetic */
            if (val2 & 0x800) {
                val2 -= 0x1000;
            }
        }
        else if (val2 >= 0x40) {
            val2 -= 0x80;
        }

        emb_pattern_addStitchRel(pattern, val1 / 10.0,
                val2 / 10.0, stitchType, 1);
    }
}

void
pecEncodeJump(FILE* file, int x, int types)
{
    int outputVal = abs(x) & 0x7FF;
    unsigned int orPart = 0x80;
    unsigned char toWrite;

    if (!file) {
        printf("ERROR: format-pec.c pecEncodeJump(), file argument is null\n");
        return;
    }
    if (types & TRIM) {
        orPart |= 0x20;
    }
    if (types & JUMP) {
        orPart |= 0x10;
    }
    if (x < 0) {
        outputVal = (x + 0x1000) & 0x7FF;
        outputVal |= 0x800;
    }
    toWrite = (unsigned char)(((outputVal >> 8) & 0x0F) | orPart);
    fwrite(&toWrite, 1, 1, file);
    toWrite = (unsigned char)(outputVal & 0xFF);
    fwrite(&toWrite, 1, 1, file);
}

void
pecEncodeStop(FILE* file, unsigned char val)
{
    if (!file) {
        printf("ERROR: format-pec.c pecEncodeStop(), file argument is null\n");
        return;
    }
    fwrite("\xFE\xB0", 1, 2, file);
    fwrite(&val, 1, 1, file);
}

char
readPec(EmbPattern* pattern, const char *fileName, FILE* file)
{
    unsigned int graphicsOffset;
    unsigned char colorChanges;
    int i;

    if (emb_verbose>1) {
        printf("fileName: %s\n", fileName);
    }

    if (!check_header_present(file, 0x20A)) {
        return 0;
    }

    fseek(file, 0x38, SEEK_SET);
    colorChanges = (unsigned char)(char)fgetc(file);
    for (i = 0; i <= colorChanges; i++) {
        emb_pattern_addThread(pattern, pec_colors[(char)fgetc(file) % 65]);
    }

    /* Get Graphics offset */
    fseek(file, 0x20A, SEEK_SET);

    graphicsOffset = (unsigned int)(fgetc(file));
    graphicsOffset |= (fgetc(file) << 8);
    graphicsOffset |= (fgetc(file) << 16);
    REPORT_INT(graphicsOffset)

    (void)(char)fgetc(file); /* 0x31 */
    (void)(char)fgetc(file); /* 0xFF */
    (void)(char)fgetc(file); /* 0xF0 */
    /* Get X and Y size in .1 mm */
    /* 0x210 */
    emb_read_i16(file); /* x size */
    emb_read_i16(file); /* y size */

    emb_read_i16(file); /* 0x01E0 */
    emb_read_i16(file); /* 0x01B0 */
    emb_read_i16(file); /* distance left from start */
    emb_read_i16(file); /* distance up from start */

    /* Begin Stitch Data */
    /* 0x21C */
    /*unsigned int end = graphicsOffset + 0x208; */
    readPecStitches(pattern, file);
    emb_pattern_flipVertical(pattern);
    return 1;
}

void
pecEncode(FILE* file, EmbPattern* p)
{
    EmbReal thisX = 0.0;
    EmbReal thisY = 0.0;
    unsigned char stopCode = 2;
    int i;

    if (!file) {
        printf("ERROR: format-pec.c pecEncode(), file argument is null\n");
        return;
    }
    if (!p) {
        printf("ERROR: format-pec.c pecEncode(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitch_list->count; i++) {
        int deltaX, deltaY;
        EmbStitch s = p->stitch_list->stitch[i];

        deltaX = (int)emb_round(s.x - thisX);
        deltaY = (int)emb_round(s.y - thisY);
        thisX += (EmbReal)deltaX;
        thisY += (EmbReal)deltaY;

        if (s.flags & STOP) {
            pecEncodeStop(file, stopCode);
            if (stopCode == (unsigned char)2) {
                stopCode = (unsigned char)1;
            } else {
                stopCode = (unsigned char)2;
            }
        } else if (s.flags & END) {
            fwrite("\xFF", 1, 1, file);
            break;
        } else if (deltaX < 63 && deltaX > -64 && deltaY < 63 && deltaY > -64 && (!(s.flags & (JUMP | TRIM)))) {
            unsigned char out[2];
            if (deltaX < 0) {
                out[0] = (unsigned char)(deltaX + 0x80);
            }
            else {
                out[0] = (unsigned char)deltaX;
            }
            if (deltaY < 0) {
                out[1] = (unsigned char)(deltaY + 0x80);
            }
            else {
                out[1] = (unsigned char)deltaY;
            }
            fwrite(out, 1, 2, file);
        }
        else {
            pecEncodeJump(file, deltaX, s.flags);
            pecEncodeJump(file, deltaY, s.flags);
        }
    }
}

void writeImage(FILE* file, unsigned char image[][48]);

void
writePecStitches(EmbPattern* pattern, FILE* file, const char *fileName)
{
    EmbRect bounds;
    unsigned char image[38][48], toWrite;
    int i, j, flen, graphicsOffsetLocation;
    int graphicsOffsetValue, height, width;
    EmbReal xFactor, yFactor;
    const char* forwardSlashPos = fileName + string_rchar(fileName, '/');
    const char* backSlashPos = fileName + string_rchar(fileName, '\\');
    const char* dotPos = fileName + string_rchar(fileName, '.');
    const char* start = 0;

    start = fileName;
    if (forwardSlashPos) {
        start = forwardSlashPos + 1;
    }
    if (backSlashPos && backSlashPos > start) {
        start = backSlashPos + 1;
    }
    fwrite("LA:", 1, 3, file);
    flen = (int)(dotPos - start);

    while (start < dotPos) {
        fwrite(start, 1, 1, file);
        start++;
    }
    fpad(file, 0x20, 16-flen);
    fwrite("\x0D", 1, 1, file);
    fpad(file, 0x20, 12);
    fwrite("\xff\x00\x06\x26", 1, 4, file);

    fpad(file, 0x20, 12);
    toWrite = (unsigned char)(pattern->thread_list->count-1);
    fwrite(&toWrite, 1, 1, file);

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor thr = pattern->thread_list->thread[i].color;
        unsigned char color = (unsigned char)
            emb_find_nearest_thread(thr,
            (EmbThread*)pec_colors, pecThreadCount);
        fwrite(&color, 1, 1, file);
    }
    fpad(file, 0x20, (int)(0x1CF - pattern->thread_list->count));
    fpad(file, 0x00, 2);

    graphicsOffsetLocation = ftell(file);
    /* placeholder bytes to be overwritten */
    fpad(file, 0x00, 3);

    fwrite("\x31\xff\xf0", 1, 3, file);

    bounds = emb_pattern_bounds(pattern);

    height = (int)emb_round(bounds.h);
    width = (int)emb_round(bounds.w);
    unsigned short top = (unsigned short)(0x9000 | -(int)emb_round(bounds.x));
    unsigned short bottom = (unsigned short)(0x9000 | -(int)emb_round(bounds.y));
    /* write 2 byte x size */
    emb_write_i16(file, width);
    /* write 2 byte y size */
    emb_write_i16(file, height);

    /* Write 4 miscellaneous int16's */
    fwrite("\x01\xe0\x01\xb0", 1, 4, file);

    /* CHECK: is this really big endian? */
    emb_write_i16be(file, top);
    emb_write_i16be(file, bottom);

    pecEncode(file, pattern);
    graphicsOffsetValue = ftell(file) - graphicsOffsetLocation + 2;
    fseek(file, graphicsOffsetLocation, SEEK_SET);

    fputc((unsigned char)(graphicsOffsetValue & 0xFF), file);
    fputc((unsigned char)((graphicsOffsetValue >> 8) & 0xFF), file);
    fputc((unsigned char)((graphicsOffsetValue >> 16) & 0xFF), file);

    fseek(file, 0x00, SEEK_END);

    /* Writing all colors */
    memcpy(image, imageWithFrame, 48*38);

    yFactor = 32.0 / height;
    xFactor = 42.0 / width;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        int x = (int)emb_round((st.x - bounds.x) * xFactor) + 3;
        int y = (int)emb_round((st.y - bounds.y) * yFactor) + 3;
        if (x<=0 || x>48) continue;
        if (y<=0 || y>38) continue;
        image[y][x] = 1;
    }
    writeImage(file, image);

    /* Writing each individual color */
    j = 0;
    for (i = 0; i < pattern->thread_list->count; i++) {
        memcpy(image, imageWithFrame, 48*38);
        for (; j < pattern->stitch_list->count; j++) {
            EmbStitch st = pattern->stitch_list->stitch[j];
            int x = (int)emb_round((st.x - bounds.x) * xFactor) + 3;
            int y = (int)emb_round((st.y - bounds.y) * yFactor) + 3;
            if (x<=0 || x>48) continue;
            if (y<=0 || y>38) continue;
            if (st.flags & STOP) {
                break;
            }
            image[y][x] = 1;
        }
        writeImage(file, image);
    }
}

char
writePec(EmbPattern* pattern, const char* fileName, FILE* file)
{
    /* TODO: There needs to be a matching flipVertical() call after the write
        to ensure multiple writes from the same pattern work properly */
    emb_pattern_flipVertical(pattern);
    emb_pattern_fixColorCount(pattern);
    emb_pattern_correctForMaxStitchLength(pattern, 12.7, 204.7);
    emb_pattern_scale(pattern, 10.0);
    fwrite("#PEC0001", 1, 8, file);
    writePecStitches(pattern, file, fileName);
    return 1;
}

/*
 * Brother Embroidery Format (.pel)
 * The Brother pel format is stitch-only.
 */
char
readPel(EmbPattern *pattern, FILE* file)
{
    puts("ERROR: readPel is not implemented.");
    printf("%p, %p\n", pattern, file);
    return 0; /*TODO: finish readPel */
}

char
writePel(EmbPattern * pattern, FILE* file)
{
    puts("ERROR: writePel is not implemented.");
    printf("%p, %p\n", pattern, file);
    return 0; /*TODO: finish writePel */
}

/*
 * Brother Embroidery Format (.pem)
 * The Brother pem format is stitch-only.
 */
char
readPem(EmbPattern *pattern, FILE* file)
{
    puts("ERROR: readPem is not implemented.");
    printf("%p, %p\n", pattern, file);
    return 0; /*TODO: finish ReadPem */
}

char
writePem(EmbPattern *pattern, FILE* file)
{
    puts("ERROR: writePem is not implemented.");
    printf("%p, %p\n", pattern, file);
    return 0; /*TODO: finish writePem */
}

/*
 * Brother Embroidery Format (.pes)
 * The Brother pes format is stitch-only.
 */

const char *pes_version_strings[] = {
    "#PES0001",
    "#PES0020",
    "#PES0022",
    "#PES0030",
    "#PES0040",
    "#PES0050",
    "#PES0055",
    "#PES0056",
    "#PES0060",
    "#PES0070",
    "#PES0080",
    "#PES0090",
    "#PES0100",
};

/* ---------------------------------------------------------------- */
/* format pes */

int pes_version = PES0001;

char
readPes(EmbPattern* pattern, const char *fileName, FILE* file)
{
    printf("%s", fileName);
    int pecstart, numColors, x, version, i;
    char signature[9];
    if (fread(signature, 1, 8, file) != 8) {
        puts("ERROR PES: failed to read signature.");
        return 0;
    }
    signature[8] = 0;
    pecstart = emb_read_i32(file);

    version = 0;
    for (i=0; i<N_PES_VERSIONS; i++) {
        if (!strcmp(signature, pes_version_strings[i])) {
            version = i;
            break;
        }
    }

    if (version >= PES0040) {
        fseek(file, 0x10, SEEK_SET);
        if (!read_descriptions(file, pattern)) {
            puts("ERROR PES: failed to read descriptions.");
            return 0;
        }
    }

    switch (version) {
    case PES0100:
        readPESHeaderV10(file, pattern);
        break;
    case PES0090:
        readPESHeaderV9(file, pattern);
        break;
    case PES0080:
        readPESHeaderV8(file, pattern);
        break;
    case PES0070:
        readPESHeaderV7(file, pattern);
        break;
    case PES0060:
        readPESHeaderV6(file, pattern);
        break;
    case PES0056:
    case PES0055:
    case PES0050:
        readPESHeaderV5(file, pattern);
        break;
    default:
        break;
    }

    /* fseek(file, pecstart + 48, SEEK_SET);
     * This seems wrong based on the readPESHeader functions. */
    fseek(file, pecstart, SEEK_SET);

    numColors = fgetc(file) + 1;
    for (x = 0; x < numColors; x++) {
        int color_index = fgetc(file);
        if (color_index >= pecThreadCount) {
            color_index = 0;
        }
        emb_pattern_addThread(pattern, pec_colors[color_index]);
    }

    fseek(file, pecstart + 528, SEEK_SET);
    readPecStitches(pattern, file);

    emb_pattern_flipVertical(pattern);

    return 1;
}

int
read_descriptions(FILE* file, EmbPattern* pattern)
{
    size_t n;
    n = (size_t)fgetc(file);
    if (fread(pattern->design_name, 1, n, file) != n) {
        return 0;
    }
    n = (size_t)fgetc(file);
    if (fread(pattern->category, 1, n, file) != n) {
        return 0;
    }
    n = (size_t)fgetc(file);
    if (fread(pattern->author, 1, n, file) != n) {
        return 0;
    }
    n = (size_t)fgetc(file);
    if (fread(pattern->keywords, 1, n, file) != n) {
        return 0;
    }
    n = (size_t)fgetc(file);
    if (fread(pattern->comments, 1, n, file) != n) {
        return 0;
    }
    return 1;
}

void
readPESHeaderV5(FILE* file, EmbPattern* pattern)
{
    int fromImageStringLength;
    fseek(file, 24, SEEK_CUR);
    fromImageStringLength = fgetc(file);
    fseek(file, fromImageStringLength, SEEK_CUR);
    fseek(file, 24, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV6(FILE* file, EmbPattern* pattern)
{
    fseek(file, 36, SEEK_CUR);
    readImageString(file, pattern);
    fseek(file, 24, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV7(FILE* file, EmbPattern* pattern)
{
    fseek(file, 36, SEEK_CUR);
    readImageString(file, pattern);
    fseek(file, 24, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV8(FILE* file, EmbPattern* pattern)
{
    fseek(file, 38, SEEK_CUR);
    readImageString(file, pattern);
    fseek(file, 26, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV9(FILE* file, EmbPattern* pattern)
{
    fseek(file, 14, SEEK_CUR);
    readHoopName(file, pattern);
    fseek(file, 30, SEEK_CUR);
    readImageString(file, pattern);
    fseek(file, 34, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV10(FILE* file, EmbPattern* pattern)
{
    fseek(file, 14, SEEK_CUR);
    readHoopName(file, pattern);
    fseek(file, 38, SEEK_CUR);
    readImageString(file, pattern);
    fseek(file, 34, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readHoopName(FILE* file, EmbPattern* pattern)
{
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    /*
    int hoopNameStringLength = fgetc(file);
    EmbString hoopNameString = readString(hoopNameStringLength);
    if (hoopNameString.length() != 0) {
        pattern.setMetadata("hoop_name", hoopNameString);
    }
    */
}

void
readImageString(FILE* file, EmbPattern* pattern)
{
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    /*
    int fromImageStringLength = fgetc(file);
    EmbString fromImageString = readString(fromImageStringLength);
    if (fromImageString.length() != 0) {
        pattern.setMetadata("image_file", fromImageString);
    }
    */
}

void
readProgrammableFills(FILE* file, EmbPattern* pattern)
{
    int numberOfProgrammableFillPatterns;
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    numberOfProgrammableFillPatterns = emb_read_i16(file);
    if (numberOfProgrammableFillPatterns != 0) {
        return;
    }
}

void
readMotifPatterns(FILE* file, EmbPattern* pattern)
{
    int numberOfMotifPatterns;
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    numberOfMotifPatterns = emb_read_i16(file);
    if (numberOfMotifPatterns != 0) {
        return;
    }
}

void
readFeatherPatterns(FILE* file, EmbPattern* pattern)
{
    int featherPatternCount;
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    featherPatternCount = emb_read_i16(file);
    if (featherPatternCount != 0) {
        return;
    }
}

void
readThreads(FILE* file, EmbPattern* pattern)
{
    int numberOfColors, i;
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    numberOfColors = emb_read_i16(file);
    for (i=0; i<numberOfColors; i++) {
        EmbThread thread;
        int color_code_length;
        int descriptionStringLength;
        int brandStringLength;
        int threadChartStringLength;
        color_code_length = fgetc(file);
        /* strcpy(thread.color_code, readString(color_code_length)); */
        thread.color.r = fgetc(file);
        thread.color.g = fgetc(file);
        thread.color.b = fgetc(file);
        fseek(file, 5, SEEK_CUR);
        descriptionStringLength = fgetc(file);
        /* strcpy(thread.description, readString(descriptionStringLength)); */

        brandStringLength = fgetc(file);
        /* strcpy(thread.brand, readString(brandStringLength)); */

        threadChartStringLength = fgetc(file);
        /* strcpy(thread.threadChart, readString(threadChartStringLength)); */

        if (emb_verbose > 1) {
            printf("color code length: %d\n", color_code_length);
            printf("description string length: %d\n", descriptionStringLength);
            printf("brand string length: %d\n", brandStringLength);
            printf("thread chart string length: %d\n", threadChartStringLength);
        }
        emb_pattern_addThread(pattern, thread);
    }
}


void
pesWriteSewSegSection(EmbPattern* pattern, FILE* file)
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
    int i, j;
    EmbRect bounds = emb_pattern_bounds(pattern);

    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbColor color;
        EmbStitch st = pattern->stitch_list->stitch[i];
        flag = st.flags;
        if (st.color < pattern->thread_list->count) {
            color = pattern->thread_list->thread[st.color].color;
        }
        else {
            color = pec_colors[0].color;
        }
        newColorCode = emb_find_nearest_thread(color, (EmbThread*)pec_colors, pecThreadCount);
        if (newColorCode != colorCode) {
            colorCount++;
            colorCode = newColorCode;
        }
        while (i < pattern->stitch_list->count && (flag == st.flags)) {
            st = pattern->stitch_list->stitch[i];
            count++;
            i++;
        }
        blockCount++;
    }

    emb_write_i16(file, (int16_t)blockCount); /* block count */
    emb_write_u16(file, 0xFFFF);
    emb_write_i16(file, 0x00);

    emb_write_i16(file, 0x07); /* string length */
    fwrite("CSewSeg", 1, 7, file);

    if (colorCount > 1000) {
        puts("Color count exceeds 1000 this is likely an error. Truncating to 1000.");
        colorCount = 1000;
    }

    colorInfo = (short *) calloc(colorCount * 2, sizeof(int16_t));
    colorCode = -1;
    blockCount = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbColor color;
        EmbStitch st;
        st = pattern->stitch_list->stitch[i];
        j = i;
        flag = st.flags;
        color = pattern->thread_list->thread[st.color].color;
        newColorCode = emb_find_nearest_thread(color, (EmbThread*)pec_colors, pecThreadCount);
        if (newColorCode != colorCode) {
            if (colorInfoIndex+2 > colorCount * 2) {
                puts("Ran out of memory for color info.");
                break;
            }
            colorInfo[colorInfoIndex++] = (int16_t)blockCount;
            colorInfo[colorInfoIndex++] = (int16_t)newColorCode;
            colorCode = newColorCode;
        }
        count = 0;
        while (j < pattern->stitch_list->count && (flag == st.flags)) {
            st = pattern->stitch_list->stitch[j];
            count++;
            j++;
        }
        if (flag & JUMP) {
            stitchType = 1;
        }
        else {
            stitchType = 0;
        }

        emb_write_i16(file, (int16_t)stitchType); /* 1 for jump, 0 for normal */
        emb_write_i16(file, (int16_t)colorCode); /* color code */
        emb_write_i16(file, (int16_t)count); /* stitches in block */
        for (j = i; j < pattern->stitch_list->count; ++j) {
            st = pattern->stitch_list->stitch[j];
            if (st.flags != flag) {
                break;
            }
            emb_write_i16(file, (int16_t)(st.x - bounds.x));
            emb_write_i16(file, (int16_t)(st.y + bounds.y));
        }
        if (j < pattern->stitch_list->count ) {
            emb_write_u16(file, 0x8003);
        }
        blockCount++;
        i = j;
    }
    emb_write_i16(file, (int16_t)colorCount);
    for (i = 0; i < colorCount; i++) {
        emb_write_i16(file, colorInfo[i * 2]);
        emb_write_i16(file, colorInfo[i * 2 + 1]);
    }
    emb_write_i32(file, 0);
    safe_free(colorInfo);
}

void
pesWriteEmbOneSection(EmbPattern* pattern, FILE* file)
{
    /* TODO: pointer safety */
    //float x, width, height;
    int hoopHeight = 1800, hoopWidth = 1300;
    EmbRect bounds;
    emb_write_i16(file, 0x07); /* string length */
    fwrite("CEmbOne", 1, 7, file);
    bounds = emb_pattern_bounds(pattern);

    fpad(file, 0, 16);

    /* AffineTransform */
    emb_write_i32(file, 1.0);
    emb_write_i32(file, 0.0);
    emb_write_i32(file, 0.0);
    emb_write_i32(file, 1.0);
    emb_write_i32(file, (float)((bounds.w - hoopWidth) / 2));
    emb_write_i32(file, (float)((bounds.h + hoopHeight) / 2));

    emb_write_i16(file, 1);
    emb_write_i16(file, 0); /* Translate X */
    emb_write_i16(file, 0); /* Translate Y */
    emb_write_i16(file, (int16_t)bounds.w);
    emb_write_i16(file, (int16_t)bounds.h);

    fpad(file, 0, 8);
    /*WriteSubObjects(br, pes, SubBlocks); */
}

char
writePes(EmbPattern* pattern,  const char *fileName, FILE* file)
{
    int pecLocation;
    emb_pattern_flipVertical(pattern);
    emb_pattern_scale(pattern, 10.0);
    fwrite("#PES0001", 1, 8, file);
    /* WRITE PECPointer 32 bit int */
    emb_write_i32(file, 0x00);

    emb_write_i16(file, 0x01);
    emb_write_i16(file, 0x01);

    /* Write object count */
    emb_write_i16(file, 0x01);
    emb_write_u16(file, 0xFFFF); /* command */
    emb_write_i16(file, 0x00); /* unknown */

    pesWriteEmbOneSection(pattern, file);
    pesWriteSewSegSection(pattern, file);

    pecLocation = ftell(file);
    fseek(file, 0x08, SEEK_SET);
    fputc((unsigned char)(pecLocation & 0xFF), file);
    fputc((unsigned char)(pecLocation >> 8) & 0xFF, file);
    fputc((unsigned char)(pecLocation >> 16) & 0xFF, file);
    fseek(file, 0x00, SEEK_END);
    writePecStitches(pattern, file, fileName);
    return 1;
}

/*
 * Brother Embroidery Format (.phb)
 * The Brother phb format is stitch-only.
 */

char
readPhb(EmbPattern* pattern, FILE* file)
{
    unsigned int fileOffset;
    short colorCount;
    int i;

    fseek(file, 0x71, SEEK_SET);
    colorCount = emb_read_i16(file);

    for (i = 0; i < colorCount; i++) {
        EmbThread t = pec_colors[fgetc(file)];
        emb_pattern_addThread(pattern, t);
    }

    /* TODO: check that file begins with #PHB */
    fseek(file, 0x54, SEEK_SET);
    fileOffset = 0x52;
    fileOffset += emb_read_i32(file);

    fseek(file, fileOffset, SEEK_SET);
    fileOffset += emb_read_i32(file) + 2;

    fseek(file, fileOffset, SEEK_SET);
    fileOffset += emb_read_i32(file);

    fseek(file, fileOffset + 14, SEEK_SET); /* 28 */

    colorCount = (int16_t)(char)fgetc(file);
    for (i = 0; i <  colorCount; i++) {
        char stor;
        stor = (char)fgetc(file);
        if (emb_verbose>1) {
            printf("stor: %d\n", stor);
        }
    }
    fseek(file, 4, SEEK_CUR); /* bytes to end of file */
    fseek(file, 17, SEEK_CUR);

    readPecStitches(pattern, file);

    emb_pattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhb */
}

char
writePhb(EmbPattern* pattern, FILE* file)
{
    puts("ERROR: writePhb is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writePhb */
}

/*
 * Brother Embroidery Format (.phc)
 * The Brother phc format is stitch-only.
 */

char
readPhc(EmbPattern* pattern, FILE* file)
{
    int colorChanges, version, bytesInSection2;
    unsigned int fileLength;
    unsigned short pecOffset, bytesInSection, bytesInSection3;
    char pecAdd;
    int i;

    fseek(file, 0x07, SEEK_SET);
    version = (char)fgetc(file) - 0x30; /* converting from ansi number */
    fseek(file, 0x4D, SEEK_SET);
    LOAD_U16(file, colorChanges)

    for (i = 0; i < colorChanges; i++) {
        EmbThread t = pec_colors[(int)(char)fgetc(file)];
        emb_pattern_addThread(pattern, t);
    }
    fseek(file, 0x2B, SEEK_SET);
    pecAdd = (char)fgetc(file);
    LOAD_I32(file, fileLength)
    LOAD_U16(file, pecOffset)
    fseek(file, pecOffset + pecAdd, SEEK_SET);
    LOAD_U16(file, bytesInSection)
    fseek(file, bytesInSection, SEEK_CUR);
    bytesInSection2 = emb_read_i32(file);
    fseek(file, bytesInSection2, SEEK_CUR);
    LOAD_U16(file, bytesInSection3)
    fseek(file, bytesInSection3 + 0x12, SEEK_CUR);

    if (emb_verbose>1) {
        printf("version: %d\n", version);
    }

    readPecStitches(pattern, file);

    emb_pattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhc */
}

char
writePhc(EmbPattern* pattern, FILE* file)
{
    puts("ERROR: writePhc is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writePhc */
}

/*
 * AutoCAD Embroidery Format (.plt)
 * The AutoCAD plt format is stitch-only.
 */
char
readPlt(EmbPattern* pattern, FILE* file)
{
    EmbReal x, y;
    EmbReal scalingFactor = 40;
    char input[512];

    /* TODO: replace all scanf code */
    while (emb_readline(file, input, 511)) {
        if (input[0] == 'P' && input[1] == 'D') {
            /* TODO: replace all scanf code */
            if (sscanf(input, "PD%f,%f;", &x, &y) < 2) {
                break;
            }
            emb_pattern_addStitchAbs(pattern, x / scalingFactor,
                            y / scalingFactor, NORMAL, 1);
        } else if (input[0] == 'P' && input[1] == 'U') {
            /* TODO: replace all scanf code */
            if (sscanf(input, "PU%f,%f;", &x, &y) < 2) {
                break;
            }
            emb_pattern_addStitchAbs(pattern, x / scalingFactor,
                    y / scalingFactor, STOP, 1);
        }
    }
    return 1;
}

char
writePlt(EmbPattern* pattern, FILE* file) {
    /* TODO: pointer safety */
    EmbReal scalingFactor = 40;
    char firstStitchOfBlock = 1;
    int i;

    fprintf(file, "IN;");
    fprintf(file, "ND;");

    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch stitch;
        stitch = pattern->stitch_list->stitch[i];
        if (stitch.flags & STOP) {
            firstStitchOfBlock = 1;
        }
        if (firstStitchOfBlock) {
            fprintf(file, "PU%f,%f;", stitch.x * scalingFactor,
                    stitch.y * scalingFactor);
            fprintf(file, "ST0.00,0.00;");
            fprintf(file, "SP0;");
            fprintf(file, "HT0;");
            fprintf(file, "HS0;");
            fprintf(file, "TT0;");
            fprintf(file, "TS0;");
            firstStitchOfBlock = 0;
        } else {
            fprintf(file, "PD%f,%f;", stitch.x * scalingFactor,
                stitch.y * scalingFactor);
        }
    }
    fprintf(file, "PU0.0,0.0;");
    fprintf(file, "PU0.0,0.0;");
    return 1; /*TODO: finish WritePlt */
}

/*
 * RGB Color File (.rgb)
 * The RGB format is a color-only format to act as an external color file for other formats.
 */
char
readRgb(EmbPattern* pattern, FILE* file)
{
    int i, numberOfColors;

    fseek(file, 0x00, SEEK_END);
    numberOfColors = ftell(file) / 4;

    pattern->thread_list->count = 0;

    printf("numberOfColors: %d\n", numberOfColors);

    fseek(file, 0x00, SEEK_SET);
    for (i = 0; i < numberOfColors; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        emb_pattern_addThread(pattern, t);
    }
    return 1;
}

char
writeRgb(EmbPattern* pattern, FILE* file)
{
    int i;
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c = pattern->thread_list->thread[i].color;
        embColor_write(file, c, 4);
    }
    return 1;
}

/*
 * Janome Embroidery Format (.sew)
 * The Janome sew format is stitch-only.
 */

char
sewDecode(unsigned char inputByte)
{
    /* TODO: fix return statement */
    return (inputByte >= 0x80) ? (char) (-~(inputByte - 1)) : (char) inputByte;
}

char
readSew(EmbPattern* pattern, FILE* file)
{
    int i, flags, numberOfColors, fileLength;
    char dx, dy, thisStitchIsJump = 0;

    fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x00, SEEK_SET);
    numberOfColors = fgetc(file);
    numberOfColors += (fgetc(file) << 8);


    for (i = 0; i < numberOfColors; i++) {
        int color = emb_read_i16(file);
        emb_pattern_addThread(pattern, jef_colors[color%78]);
    }
    fseek(file, 0x1D78, SEEK_SET);

    for (i = 0; ftell(file) < fileLength; i++) {
        unsigned char b[2];
        fread(b, 1, 2, file);

        flags = NORMAL;
        if (thisStitchIsJump) {
            flags = TRIM;
            thisStitchIsJump = 0;
        }
        if (b[0] == 0x80) {
            if (b[1] == 1) {
                fread(b, 1, 2, file);
                flags = STOP;
            }
            else if ((b[1] == 0x02) || (b[1] == 0x04)) {
                thisStitchIsJump = 1;
                fread(b, 1, 2, file);
                flags = TRIM;
            }
            else if (b[1] == 0x10) {
               break;
            }
        }
        dx = sewDecode(b[0]);
        dy = sewDecode(b[1]);
        if (abs(dx) == 127 || abs(dy) == 127) {
            thisStitchIsJump = 1;
            flags = TRIM;
        }
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    printf("current position: %ld\n", ftell(file));
    return 1;
}

char
writeSew(EmbPattern* pattern, FILE* file)
{
    int i;
    EmbReal xx = 0.0, yy = 0.0;
    emb_write_i16(file, pattern->thread_list->count);

    if (emb_verbose>1) {
        printf("Debugging Information\n");
        printf("number of colors = %d\n", pattern->thread_list->count);
        printf("number of stitches = %d\n", pattern->stitch_list->count);
    }

    for (i = 0; i < pattern->thread_list->count; i++) {
        short thr;
        EmbColor col;
        col = pattern->thread_list->thread[i].color;
        thr = emb_find_nearest_thread(col, (EmbThread *)jef_colors, 79);
        emb_write_i16(file, thr);
    }
    fpad(file, 0, 0x1D78 - 2 - pattern->thread_list->count * 2);

    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st;
        unsigned char b[4];
        char dx, dy;
        st = pattern->stitch_list->stitch[i];
        dx = (char)emb_round(10.0*(st.x - xx));
        dy = (char)emb_round(10.0*(st.y - yy));
        xx += 0.1*dx;
        yy += 0.1*dy;
        if (st.flags & STOP) {
            b[0] = 0x80;
            b[1] = 0x01;
            b[2] = dx;
            b[3] = dy;
            fwrite(b, 1, 4, file);
        }
        else if (st.flags & END) {
            b[0] = 0x80;
            b[1] = 0x10;
            b[2] = 0;
            b[3] = 0;
            fwrite(b, 1, 4, file);
        }
        else if ((st.flags & TRIM) || (st.flags & JUMP)) {
            b[0] = 0x80;
            b[1] = 2;
            b[2] = dx;
            b[3] = dy;
            fwrite(b, 1, 4, file);
        }
        else {
            b[0] = dx;
            b[1] = dy;
            fwrite(b, 1, 2, file);
        }
    }
    return 1;
}

/*
 * Husqvarna Viking Embroidery Format (.shv)
 * The Husqvarna Viking shv format is stitch-only.
 */
char
shvDecode(unsigned char inputByte)
{
    if (inputByte >= 0x80) {
        return (char)-((unsigned char)((~inputByte) + 1));
    }
    return ((char)inputByte);
}

short shvDecodeShort(unsigned short inputByte)
{
    if (inputByte > 0x8000) {
        return (int16_t)-((unsigned short)((~inputByte) + 1));
    }
    return ((int16_t)inputByte);
}

char
readShv(EmbPattern* pattern, FILE* file)
{
    int i;
    char inJump = 0;
    unsigned char fileNameLength, designWidth, designHeight;
    char halfDesignWidth, halfDesignHeight, halfDesignWidth2, halfDesignHeight2;
    char* headerText = "Embroidery disk created using software licensed from Viking Sewing Machines AB, Sweden";
    char dx = 0, dy = 0;
    char numberOfColors;
    unsigned short magicCode;
    int something;
    short left,top,right,bottom;
    char something2, numberOfSections, something3;
    int stitchesPerColor[256];
    int stitchesSinceChange = 0;
    int currColorIndex = 0;
    unsigned short sx, sy;

    if (!check_header_present(file, 25)) {
        return 0;
    }

    fseek(file, strlen(headerText), SEEK_SET);
    fileNameLength = fgetc(file);
    fseek(file, fileNameLength, SEEK_CUR);
    designWidth = fgetc(file);
    designHeight = fgetc(file);
    LOAD_I8(file, halfDesignWidth)
    LOAD_I8(file, halfDesignHeight)
    LOAD_I8(file, halfDesignWidth2)
    LOAD_I8(file, halfDesignHeight2)
    if ((designHeight % 2) == 1) {
        fseek(file, ((designHeight + 1)*designWidth)/2, SEEK_CUR);
    }
    else {
        fseek(file, (designHeight*designWidth)/2, SEEK_CUR);
    }
    numberOfColors = fgetc(file);
    LOAD_U16(file, magicCode)
    fseek(file, 1, SEEK_CUR);
    LOAD_I32(file, something)
    LOAD_I16(file, left)
    LOAD_U16(file, top)
    LOAD_U16(file, right)
    LOAD_U16(file, bottom)

    LOAD_I8(file, something2)
    LOAD_I8(file, numberOfSections)
    LOAD_I8(file, something3)

    for (i = 0; i < numberOfColors; i++) {
        unsigned int stitchCount, colorNumber;
        stitchCount = emb_read_i32be(file);
        colorNumber = fgetc(file);
        emb_pattern_addThread(pattern, shv_colors[colorNumber % 43]);
        stitchesPerColor[i] = stitchCount;
        fseek(file, 9, SEEK_CUR);
    }

    fseek(file, -2, SEEK_CUR);

    for (i = 0; !feof(file); i++) {
        unsigned char b0, b1;
        int flags;
        flags = NORMAL;
        if (inJump) {
            flags = JUMP;
        }
        b0 = fgetc(file);
        b1 = fgetc(file);
        if (stitchesSinceChange >= stitchesPerColor[currColorIndex]) {
            emb_pattern_addStitchRel(pattern, 0, 0, STOP, 1);
            currColorIndex++;
            stitchesSinceChange = 0;
        }
        if (b0 == 0x80) {
            stitchesSinceChange++;
            if (b1 == 3) {
                continue;
            }
            else if (b1 == 0x02) {
                inJump = 0;
                continue;
            }
            else if (b1 == 0x01) {
                stitchesSinceChange += 2;
                sx = fgetc(file);
                sx = (unsigned short)(sx << 8 | fgetc(file));
                sy = fgetc(file);
                sy = (unsigned short)(sy << 8 | fgetc(file));
                flags = TRIM;
                inJump = 1;
                emb_pattern_addStitchRel(pattern, shvDecodeShort(sx) / 10.0, shvDecodeShort(sy) / 10.0, flags, 1);
                continue;
            }
        }
        dx = shvDecode(b0);
        dy = shvDecode(b1);
    stitchesSinceChange++;
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    emb_pattern_flipVertical(pattern);

    return 1;
}

char
writeShv(EmbPattern* pattern, FILE* file)
{
    puts("writeShv not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeShv */
}

/*
 * Sunstar Embroidery Format (.sst)
 * The Sunstar sst format is stitch-only.
 */
char
readSst(EmbPattern* pattern, FILE* file)
{
    int fileLength;

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0xA0, SEEK_SET); /* skip the all zero header */
    while (ftell(file) < fileLength) {
        int stitchType = NORMAL;

        int b1 = fgetc(file);
        int b2 = fgetc(file);
        unsigned char commandByte = (unsigned char)fgetc(file);

        if (commandByte == 0x04) {
            emb_pattern_addStitchRel(pattern, 0, 0, END, 1);
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
        emb_pattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }

    return 1; /*TODO: finish readSst */
}

char
writeSst(EmbPattern* pattern, FILE* file)
{
    int i;
    int head_length = 0xA0;
    for (i=0; i<head_length; i++) {
        fprintf(file, " ");
    }
    for (i=0; i<pattern->stitch_list->count; i++) {
        printf(".");
    }
    return 0; /*TODO: finish writeSst */
}

/*
 * Data Stitch Embroidery Format (.stx)
 * The Data Stitch stx format is stitch-only.
 */
int
stxReadThread(StxThread* thread, FILE* file)
{
    int j, colorNameLength, sectionNameLength;
    int somethingSomething, somethingSomething2, somethingElse, numberOfOtherDescriptors; /* TODO: determine what these represent */
    int codeLength = 0;
    char* codeBuff = 0;
    char* codeNameBuff = 0;
    EmbColor col;
    char* sectionNameBuff = 0;

    if (!thread) {
        printf("ERROR: format-stx.c stxReadThread(), thread argument is null\n");
        return 0;
    }
    if (!file) { printf("ERROR: format-stx.c stxReadThread(), file argument is null\n"); return 0; }

    codeLength = fgetc(file);
    codeBuff = (char*)malloc(codeLength);
    if (!codeBuff) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeBuff\n");
        return 0;
    }
    /* TODO: check return value */
    fread(codeBuff, 1, codeLength, file);
    thread->colorCode = codeBuff;
    colorNameLength = fgetc(file);
    codeNameBuff = (char*)malloc(colorNameLength);
    if (!codeNameBuff) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeNameBuff\n");
        return 0;
    }
    fread((unsigned char*)codeNameBuff, 1, colorNameLength, file); /* TODO: check return value */
    thread->colorName = codeNameBuff;

    embColor_read(file, &col, 4);
    if (emb_verbose>1) {
        printf("col red: %d\n", col.r);
        printf("col green: %d\n", col.g);
        printf("col blue: %d\n", col.b);
    }

    sectionNameLength = fgetc(file);
    sectionNameBuff = (char*)malloc(sectionNameLength);
    if (!sectionNameBuff) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for sectionNameBuff\n");
        return 0;
    }
    fread((unsigned char*)sectionNameBuff, 1, sectionNameLength, file); /* TODO: check return value */
    thread->sectionName = sectionNameBuff;

    LOAD_I32(file, somethingSomething)
    LOAD_I32(file, somethingSomething2)
    LOAD_I32(file, somethingElse)
    LOAD_I16(file, numberOfOtherDescriptors)

    thread->subDescriptors = (SubDescriptor*)malloc(sizeof(SubDescriptor) * numberOfOtherDescriptors);
    if (!thread->subDescriptors) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for thread->subDescriptors\n");
        return 0;
    }
    for (j = 0; j < numberOfOtherDescriptors; j++) {
        SubDescriptor sd;
        char* subCodeBuff, *subColorNameBuff;
        int subCodeLength, subColorNameLength;

        sd.someNum = emb_read_i16(file);
        /* Debug.Assert(sd.someNum == 1); TODO: review */
        sd.someInt = emb_read_i32(file);
        subCodeLength = fgetc(file);
        subCodeBuff = (char*)malloc(subCodeLength);
        if (!subCodeBuff) {
            printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for subCodeBuff\n");
            return 0;
        }
        fread((unsigned char*)subCodeBuff, 1, subCodeLength, file); /* TODO: check return value */
        sd.colorCode = subCodeBuff;
        subColorNameLength = fgetc(file);
        subColorNameBuff = (char*)malloc(subColorNameLength);
        if (!subColorNameBuff) {
            printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for subColorNameBuff\n");
            return 0;
        }
        fread((unsigned char*)subColorNameBuff, 1, subColorNameLength, file); /* TODO: check return value */
        sd.colorName = subColorNameBuff;
        sd.someOtherInt = emb_read_i32(file);
        thread->subDescriptors[j] = sd;
    }
    return 1;
}

char
readStx(EmbPattern* pattern, FILE* file)
{
    int i, threadCount;
    unsigned char* gif = 0;
    /* public Bitmap Image; */
    StxThread* stxThreads = 0;
    unsigned char headerBytes[7];
    char* header = 0;
    char stor;
    char filetype[4], version[5];
    int paletteLength, imageLength, something1, stitchDataOffset, something3;
    int threadDescriptionOffset, stitchCount, left, right, colors;
    int val[12];
    int bottom, top;

    if (!check_header_present(file, 15)) {
        puts("ERROR: header is not present.");
        return 0;
    }

    /* bytes 0-6 */
    if (!read_n_bytes(file, headerBytes, 7)) {
        return 0;
    }
    header = (char*)headerBytes;

    /* bytes 7-9 */
    memcpy(filetype, &header[0], 3);
    /* bytes 10-13 */
    memcpy(version, &header[3], 4);
    filetype[3] = '\0';
    version[4] = '\0';
    /* byte 14 */
    stor = (char)fgetc(file);
    if (emb_verbose>1) {
        printf("stor: %d\n", stor);
    }

    /* bytes 15- */
    LOAD_I32(file, paletteLength)
    LOAD_I32(file, imageLength)
    LOAD_I32(file, something1)
    LOAD_I32(file, stitchDataOffset)
    LOAD_I32(file, something3)
    LOAD_I32(file, threadDescriptionOffset)
    LOAD_I32(file, stitchCount)
    LOAD_I32(file, colors)
    LOAD_I16(file, right)
    LOAD_I16(file, left)
    LOAD_I16(file, bottom)
    LOAD_I16(file, top)

    gif = (unsigned char*)malloc(imageLength);
    if (!gif) {
        printf("ERROR: format-stx.c readStx(), unable to allocate memory for gif\n");
        return 0;
    }
    if (!read_n_bytes(file, gif, imageLength)) {
        return 0;
    }
    /*Stream s2 = new MemoryStream(gif); TODO: review */
    /*Image = new Bitmap(s2); TODO: review */

    threadCount = emb_read_i16(file);
    stxThreads = (StxThread*)malloc(sizeof(StxThread) * threadCount);
    if (!stxThreads) {
        printf("ERROR: format-stx.c readStx(), unable ");
        printf("to allocate memory for stxThreads\n");
        return 0;
    }
    for (i = 0; i < threadCount; i++) {
        EmbThread t;
        StxThread st;
        stxReadThread(&st, file);

        t.color = st.stxColor;
        strcpy(t.description, st.colorName);
        strcpy(t.catalogNumber, st.colorCode);
        emb_pattern_addThread(pattern, t);
        stxThreads[i] = st;
    }

    fseek(file, 15, SEEK_CUR);

    for (i = 0; i < 12; i++) {
        val[i] = emb_read_i16(file);
        if (emb_verbose>1) {
            printf("identify val[%d] = %d", i, val[i]);
        }
    }
    if (emb_verbose>1) {
        puts("val[4] == val[5] == 0");
        puts("val[10] == val[11] == 0");
    }
    fseek(file, 8, SEEK_CUR); /* 0 0 */
    /* br.BaseStream.Position = stitchDataOffset; TODO: review */
    for (i = 1; i < stitchCount; ) {
        char b0 = (char)fgetc(file);
        char b1 = (char)fgetc(file);
        if (b0 == -128) {
            switch (b1) {
                case 1:
                    b0 = (char)fgetc(file);
                    b1 = (char)fgetc(file);
                    /*emb_pattern_addStitchRel(b0, b1, STOP); TODO: review */

                    i++;
                    break;
                case 2:
                    b0 = (char)fgetc(file);
                    b1 = (char)fgetc(file);
                    emb_pattern_addStitchRel(pattern, b0 / 10.0,
                        b1 / 10.0, JUMP, 1);
                    i++;
                    break;
                case -94:
                    /* TODO: Is this a synchronize?
                        If so document it in the comments. */
                    break;
                default:
                    /*Debugger.Break(); TODO: review */
                    break;
            }
        } else {
            emb_pattern_addStitchRel(pattern, b0 / 10.0, b1 / 10.0, NORMAL, 1);
            i++;
        }
    }
    emb_pattern_flipVertical(pattern);
    return 1;
}

char
writeStx(EmbPattern* pattern, FILE* file)
{
    puts("ERROR: writeStx is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeStx */
}

/*
 * Scalable Vector Graphics (.svg)
 * The scalable vector graphics (SVG) format is a graphics format maintained by ...
 */
int svgCreator;

int svgExpect;
int svgMultiValue;

int current_element_id;
SvgAttribute attributeList[1000];
int n_attributes = 0;
char currentAttribute[1000];
char currentValue[1000];

int svg_identify_element(char *buff);

#if 0
EmbColor
svgColorToEmbColor(char* colorString)
{
    EmbColor c;
    char* pEnd = 0;
    char* colorStr = copy_trim(colorString); /* Trim out any junk spaces */
    int length = strlen(colorStr);
    int tableColor;

    /* SVGTiny1.2 Spec Section 11.13.1 syntax for color values */
    if (length == 7 && colorStr[0] == '#') /* Six digit hex — #rrggbb */ {
        while (*colorStr=='#' && *colorStr!=0) {
            colorStr++;
        }
        c = embColor_fromHexStr(colorStr);
    }
    else if (length == 4 && colorStr[0] == '#') /* Three digit hex — #rgb */ {
        /* Convert the 3 digit hex to a six digit hex */
        char hex[7];
        sprintf(hex, "%c%c%c%c%c%c", colorStr[1], colorStr[1], colorStr[2],
            colorStr[2], colorStr[3], colorStr[3]);

        c = embColor_fromHexStr(hex);
    }
    else if (strstr(colorStr, "%")) /* Float functional — rgb(R%, G%, B%) */ {
        char *s = colorStr;
        /* replace characters we aren't using with spaces */
        for (; *s; s++) {
            if (*s == 'r' || *s == 'g' || *s == 'b' || *s == ','
                || *s == '(' || *s == ')' || *s == '%') {
                *s = ' ';
            }
        }
        c.r = (unsigned char)emb_round(255.0/100.0 * strtod(colorStr, &pEnd));
        c.g = (unsigned char)emb_round(255.0/100.0 * strtod(pEnd,     &pEnd));
        c.b = (unsigned char)emb_round(255.0/100.0 * strtod(pEnd,     &pEnd));
    }
    else if (length > 3 && colorStr[0] == 'r' && colorStr[1] == 'g' && colorStr[2] == 'b') {
        /* Integer functional — rgb(rrr, ggg, bbb) */
        char *s = colorStr;
        /* replace characters we aren't using with spaces */
        for (; *s; s++) {
            if (*s == 'r' || *s == 'g' || *s == 'b' || *s == ','
                || *s == '(' || *s == ')') {
                *s = ' ';
            }
        }
        c.r = (unsigned char)strtol(colorStr, &pEnd, 10);
        c.g = (unsigned char)strtol(pEnd,     &pEnd, 10);
        c.b = (unsigned char)strtol(pEnd,     &pEnd, 10);
    }
    else /* Color keyword */ {
        tableColor = threadColor(colorStr, SVG_Colors);
        if (tableColor < 0) {
            printf("SVG color string not found: %s.\n", colorStr);
            c.r = 0;
            c.g = 0;
            c.b = 0;
        }
        else {
            c.r = (tableColor >> 16) & 0xFF;
            c.g = (tableColor >> 8) & 0xFF;
            c.b = tableColor & 0xFF;
        }
    }

    safe_free(colorStr);
    /* Returns black if all else fails */
    return c;
}

int
toUpper(char cmd)
{
    if (cmd >= 'a' && cmd <= 'z') {
        return cmd - 'a' + 'A';
    }
    return cmd;
}

int svgPathCmdToEmbPathFlag(char cmd)
{
    /* TODO: This function needs some work */
    if     (toUpper(cmd) == 'M') return MOVETO;
    else if (toUpper(cmd) == 'L') return LINETO;
    /*
    else if (toUpper(cmd) == 'C') return CUBICTOCONTROL1;
    else if (toUpper(cmd) == 'CC') return CUBICTOCONTROL2;
    else if (toUpper(cmd) == 'CCC') return CUBICTOEND;
    else if (toUpper(cmd) == 'A') return ELLIPSETORAD;
    else if (toUpper(cmd) == 'AA') return ELLIPSETOEND;
    else if (toUpper(cmd) == 'Q') return QUADTOCONTROL;
    else if (toUpper(cmd) == 'QQ') return QUADTOEND;
    else if (toUpper(cmd) == 'Z') return LINETO;
    */

    /*else if (toUpper(cmd) == 'B') return BULGETOCONTROL; */ /* NOTE: This is not part of the SVG spec, but hopefully Bulges will be added to the SVG spec someday */
    /*else if (toUpper(cmd) == 'BB') return BULGETOEND; */   /* NOTE: This is not part of the SVG spec, but hopefully Bulges will be added to the SVG spec someday */
    /*else { printf("ERROR: svgPathCmdToEmbPathFlag(), unknown command '%c'\n", cmd); return MOVETO; } */

    return LINETO;
}

char* svgAttribute_getValue(const char* name) {
    int i;
    for (i=0; i<n_attributes; i++) {
        if (!strcmp(attributeList[i].name, name)) {
            return attributeList[i].value;
        }
    }
    return "none";
}

void
parse_circle(EmbPattern *p)
{
    EmbCircle circle;
    circle.center.x = atof(svgAttribute_getValue("cx"));
    circle.center.y = atof(svgAttribute_getValue("cy"));
    circle.radius = atof(svgAttribute_getValue("r"));
    emb_add_circle(p, circle);
}

void
parse_ellipse(EmbPattern *p)
{
    EmbEllipse ellipse;
    ellipse.center.x = atof(svgAttribute_getValue("cx"));
    ellipse.center.y = atof(svgAttribute_getValue("cy"));
    ellipse.radius.x = atof(svgAttribute_getValue("rx"));
    ellipse.radius.y = atof(svgAttribute_getValue("ry"));
    emb_add_ellipse(p, ellipse);
}

void
parse_line(EmbPattern *p)
{
    char *x1, *x2, *y1, *y2;
    x1 = svgAttribute_getValue("x1");
    y1 = svgAttribute_getValue("y1");
    x2 = svgAttribute_getValue("x2");
    y2 = svgAttribute_getValue("y2");

    /* If the starting and ending points are the same, it is a point */
    if (!strcmp(x1, x2) && !strcmp(y1, y2)) {
        EmbPoint point;
        point.position.x = atof(x1);
        point.position.y = atof(y1);
        emb_pattern_addPointAbs(p, point);
    }
    else {
        EmbLine line;
        line.start.x = atof(x1);
        line.start.y = atof(y1);
        line.end.x = atof(x2);
        line.end.y = atof(y2);
        emb_add_line(p, line);
    }

}

void
parse_path(EmbPattern *p)
{
    /* TODO: finish */
    EmbVector position, f_point, l_point, c1_point, c2_point;
    int cmd, i, pos, reset, trip;
    EmbReal pathData[7];
    unsigned int numMoves;
    EmbColor color;
    EmbArray* flagList = 0;
    EmbPath path;
    char* pointStr = svgAttribute_getValue("d");
    char* mystrok = svgAttribute_getValue("stroke");
    int last = strlen(pointStr);
    int size = 32;
    int pendingTask = 0;
    int relative = 0;
    char* pathbuff = 0;

    EmbArray* pointList = 0;
    pos = 0;
    /* An odometer aka 'tripometer' used for stepping thru the pathData */
    trip = -1;
    /* count of float[] that has been filled.
     * 0 = first item of array
     * -1 = not filled = empty array
     */
    reset = -1;
    position.x = 0.0;
    position.y = 0.0;
    f_point.x = 0.0;
    f_point.y = 0.0;
    l_point.x = 0.0;
    l_point.y = 0.0;
    c1_point.x = 0.0;
    c1_point.y = 0.0;
    c2_point.x = 0.0;
    c2_point.y = 0.0;
    cmd = 0;
    numMoves = 0;

    pathbuff = (char*)malloc(size);
    if (!pathbuff) {
        printf("ERROR: svgAddToPattern(), cannot allocate memory for pathbuff\n");
        return;
    }

    printf("stroke:%s\n", mystrok);

    for (i = 0; i < last; i++) {
        char c = pointStr[i];
        if (emb_verbose>1) {
            printf("relative %d\n", relative);
            printf("c1.x %f\n", c1_point.x);
            printf("c2.x %f\n", c2_point.x);
        }
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
                pathbuff[pos++] = (char)c;                  /* add a more char */
                break;

            case ' ':
            case ',':

                /*printf("    ,'%s'    ~POS=%d  ~TRIP=%d  ~[pos]=%d\n", pathbuff,pos,trip, pathbuff[pos]);*/
                if (pos > 0) {         /* append float to array, if it not yet stored */
                    pathbuff[pos] = 0;
                    pos = 0;
                    printf("    ,val:%s\n", pathbuff);
                    pathData[++trip] = atof(pathbuff);
                }
                break;

            case '-':

                if (pos > 0) {
                    /* append float to array, if it not yet stored */
                    pathbuff[pos] = 0;
                    pos = 0;
                    printf("    -val:%s\n", pathbuff);
                    pathData[++trip] = atof(pathbuff);
                }
                pathbuff[pos++] = (char)c;
                /* add a more char */
                break;

            default:
                    /*** ASSUMED ANY COMMAND FOUND ***/


                    if (pos > 0) {
                        /* just make sure: append float to array,
                         * if it not yet stored
                         */
                        pathbuff[pos] = 0;
                        pos = 0;
                        printf("    >val:%s\n", pathbuff);
                        pathData[++trip] = atof(pathbuff);
                    }

                    /**** Compose Point List ****/

                    /* below "while" is for avoid losing last 'z'
                     * command that maybe never accommodated.
                     */
                    pendingTask = 1; if (i==last-1) {pendingTask = 2;}

                    while (pendingTask > 0) {
                        pendingTask -= 1;

                    /* Check whether prior command need to be saved */
                    if (trip>=0) {
                        EmbPoint test;
                        trip = -1;
                        reset = -1;

                        relative = 0;
                        /* relative to prior coordinate point
                         * or absolute coordinate? */

                        if (cmd >= 'a' && cmd <= 'z') {
                            relative = 1;
                        }

                        if (cmd == 'M' || cmd == 'm') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                            f_point = position;
                        }
                        else if (cmd == 'L' || cmd == 'l') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'H' || cmd == 'h') {
                            position.x = pathData[0];
                            position.y = l_point.y;
                        }
                        else if (cmd == 'V'  || cmd == 'v') {
                            position.x = l_point.x;
                            position.y = pathData[1];
                        }
                        else if (cmd == 'C' || cmd == 'c') {
                            position.x = pathData[4];
                            position.y = pathData[5];
                            c1_point.x = pathData[0];
                            c1_point.y = pathData[1];
                            c2_point.x = pathData[2];
                            c2_point.y = pathData[3];
                        }
                        /*
                        else if (cmd == 'S') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 's') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'Q') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'q') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'T') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 't') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'A') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'a') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        */
                        else if (cmd == 'Z' || cmd == 'z') {
                            position = f_point;
                        }

                        if (!pointList && !flagList) {
                            pointList = emb_array_create(EMB_POINT);
                            flagList = emb_array_create(EMB_FLAG);
                        }
                        test.position = position;
                        emb_array_addPoint(pointList, test);
                        emb_array_add_flag(flagList, svgPathCmdToEmbPathFlag(cmd));
                        l_point = position;

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
                        /* set the command for compare */
                        pathbuff[0] = (char)c;
                        pathbuff[1] = 0;

                        printf("cmd:%s\n", pathbuff);
                        if (c == 'M' || c == 'm' || c == 'L' || c == 'l') {
                            cmd = c;
                            reset = 2;
                            numMoves++;
                        }
                        else if (c == 'C' || c == 'c') {
                            cmd = c;
                            reset = 6;
                        }
                        else if (c == 'H' || c == 'h' || c == 'V' || c == 'v') {
                            cmd = c;
                            reset = 1;
                        }
                        else if (c == 'S' || c == 's' || c == 'Q' || c == 'q') {
                            cmd = c;
                            reset = 4;
                        }
                        else if (c == 'T' || c == 't') {
                            cmd = c;
                            reset = 2;
                        }
                        else if (c == 'A' || c == 'a') {
                            cmd = c;
                            reset = 7;
                        }
                        else if (c == 'Z' || c == 'z') {
                            cmd = c;
                            reset = 0;
                        }
                        else {
                            printf("ERROR: svgAddToPattern(), %s is not a valid svg path command, skipping...\n", pathbuff);
                            trip = -1;
                            reset = -1;
                        }
                    }
                    /* avoid losing 'z' command that maybe never accommodated. */
                        if (i==last-1) {
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
                printf("ERROR: svgAddToPattern(), cannot re-allocate memory for pathbuff\n");
                return;
            }
        }
    }
    safe_free(pathbuff);

    /* TODO: subdivide numMoves > 1 */

    color = svgColorToEmbColor(svgAttribute_getValue("stroke"));

    path.pointList = pointList;
    path.flagList = flagList;
    path.color = color;
    path.lineType = 1;
    emb_add_path(p, path);
}

EmbArray *
parse_pointlist(EmbPattern *p)
{
    char* pointStr = svgAttribute_getValue("points");
    int last = strlen(pointStr);
    int size = 32;
    int i = 0;
    int pos = 0;
    unsigned char odd = 1;
    EmbReal xx = 0.0;
    EmbReal yy = 0.0;

    EmbArray* pointList = 0;

    char* polybuff = 0;

    if (emb_verbose > 1) {
        printf("Called with %p\n", (void*)p);
    }

    polybuff = (char*)malloc(size);
    if (!polybuff) {
        printf("ERROR: svgAddToPattern(), cannot allocate memory for polybuff\n");
        return pointList;
    }
    for (i = 0; i < last; i++) {
        char c = pointStr[i];
        switch (c) {
            case ' ':
                if (pos == 0) {
                    break;
                }
                polybuff[pos] = 0;
                pos = 0;
                /*Compose Point List */
                if (odd) {
                    odd = 0;
                    xx = atof(polybuff);
                }
                else {
                    EmbPoint a;
                    odd = 1;
                    yy = atof(polybuff);

                    if (!pointList) {
                        pointList = emb_array_create(EMB_POINT);
                    }
                    a.position.x = xx;
                    a.position.y = yy;
                    emb_array_addPoint(pointList, a);
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
                 printf("ERROR: svgAddToPattern(), cannot re-allocate memory for polybuff\n");
                 return NULL;
             }
        }
    }
    safe_free(polybuff);
    return pointList;
}

void
parse_polygon(EmbPattern *p)
{
    if (emb_verbose > 1) {
        printf("Called with %p\n", (void*)p);
    }
    /*
    EmbPolygonObject polygonObj;
    polygonObj.pointList = emb_array_create(EMB_POINT);
    BROKEN: polygonObj.pointList = parse_pointlist(p);
    polygonObj.color = svgColorToEmbColor(svgAttribute_getValue("stroke"));
    polygonObj.lineType = 1; TODO: use lineType enum
    emb_pattern_addPolygonObjectAbs(p, &polygonObj);
    */
}

void
parse_polyline(EmbPattern *p)
{
    if (emb_verbose > 1) {
        printf("Called with %p\n", (void*)p);
    }
    /* BROKEN
    EmbPolylineObject* polylineObj;
    polylineObj = (EmbPolylineObject*)malloc(sizeof(EmbPolylineObject));
    polylineObj->pointList = parse_pointlist(p);
    polylineObj->color = svgColorToEmbColor(svgAttribute_getValue("stroke"));
    polylineObj->lineType = 1; TODO: use lineType enum
    emb_pattern_addPolylineObjectAbs(p, polylineObj);
    */
}

void
parse_rect(EmbPattern *p)
{
    EmbRect rect;
    float width, height;
    rect.x = atof(svgAttribute_getValue("x"));
    rect.y = atof(svgAttribute_getValue("y"));
    width = atof(svgAttribute_getValue("width"));
    height = atof(svgAttribute_getValue("height"));
    rect.right = rect.x + width;
    rect.bottom = rect.y + height;
    emb_pattern_addRectAbs(p, rect);
}

void
svgAddToPattern(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: svgAddToPattern(), p argument is null\n");
        return;
    }
    switch (current_element_id) {
    case ELEMENT_CIRCLE:
        parse_circle(p);
        break;
    case ELEMENT_ELLIPSE:
        parse_ellipse(p);
        break;
    case ELEMENT_LINE:
        parse_line(p);
        break;
    case ELEMENT_PATH:
        parse_path(p);
        break;
    case ELEMENT_POLYGON:
        parse_polygon(p);
        break;
    case ELEMENT_POLYLINE:
        parse_polygon(p);
        break;
    case ELEMENT_RECT:
        parse_rect(p);
        break;
    default:
        break;
    }
}

int svg_identify_element(char *buff)
{
    int i;
    for (i=0; svg_element_tokens[i][0]; i++) {
        if (!strcmp(buff, svg_element_tokens[i])) {
            return i;
        }
    }
    return -1;
}

int svgIsElement(const char* buff) {
    if (stringInArray(buff, svg_element_tokens)) {
        return SVG_ELEMENT;
    }
    /* Attempt to identify the program that created the SVG file.
     * This should be in a comment at that occurs before the svg element. */
    else if (!strcmp(buff, "Embroidermodder")) {
        svgCreator = SVG_CREATOR_EMBROIDERMODDER;
    }
    else if (!strcmp(buff, "Illustrator")) {
        svgCreator = SVG_CREATOR_ILLUSTRATOR;
    }
    else if (!strcmp(buff, "Inkscape")) {
        svgCreator = SVG_CREATOR_INKSCAPE;
    }

    return SVG_NULL;
}

/*
int
svgIsSvgAttribute(const char* buff)
{
    const char *inkscape_tokens[] = {
        "xmlns:dc", "xmlns:cc", "xmlns:rdf", "xmlns:svg", "xmlns", "\0"
    };
    if (stringInArray(buff, svg_attribute_tokens)) {
        return SVG_ATTRIBUTE;
    }
    if (svgCreator == SVG_CREATOR_INKSCAPE) {
        if (stringInArray(buff, inkscape_tokens)) {
            return SVG_ATTRIBUTE;
        }
    }
    printf("svgIsSvgAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}
*/

void
svgProcess(int c, const char* buff)
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
            current_element_id = svg_identify_element((char*)buff);
        } else {
            return;
        }
    } else if (svgExpect == SVG_EXPECT_ATTRIBUTE) {
        char advance = 0;
        switch (current_element_id) {
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
            if (stringInArray(buff, svg_property_tokens)) {
                advance = SVG_PROPERTY;
            }
            break;
        case ELEMENT_ANIMATION:
        case ELEMENT_AUDIO:
        case ELEMENT_DESC:
        case ELEMENT_IMAGE:
        case ELEMENT_METADATA:
        case ELEMENT_TITLE:
        case ELEMENT_VIDEO:
            if (stringInArray(buff, svg_media_property_tokens)) {
                advance = SVG_MEDIA_PROPERTY;
            }
            break;
            default: break;
        }
        if (!advance) {
            if (stringInArray(buff, (const char **)svg_attribute_table[current_element_id])) {
                advance = SVG_ATTRIBUTE;
            }
            printf("ERROR %s not found in svg_attribute_table[%d].\n",
                buff, current_element_id);
        }
        if (advance) {
            printf("ATTRIBUTE:\n");
            svgExpect = SVG_EXPECT_VALUE;
            strcpy(currentAttribute, buff);
        }
    } else if (svgExpect == SVG_EXPECT_VALUE) {
        int last = strlen(buff) - 1;
        printf("VALUE:\n");

        /* single-value */
        if ((buff[0] == '"' || buff[0] == '\'') && (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') && !svgMultiValue) {
            svgExpect = SVG_EXPECT_ATTRIBUTE;
            strcpy(attributeList[n_attributes].name, currentAttribute);
            strcpy(attributeList[n_attributes].value, buff);
            n_attributes++;
        } else { /* multi-value */
            svgMultiValue = 1;
            if (strlen(currentValue)==0) {
                strcpy(currentValue, buff);
            }
            else {
                strcat(currentValue, " ");
                strcat(currentValue, buff);
            }
            if (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') {
                svgMultiValue = 0;
                svgExpect = SVG_EXPECT_ATTRIBUTE;
                strcpy(attributeList[n_attributes].name, currentAttribute);
                strcpy(attributeList[n_attributes].value, currentValue);
                n_attributes++;
            }
        }
    }
    if (svgExpect != SVG_EXPECT_NULL) {
        printf("%s\n", buff);
    }
    if (c == '>') {
        svgExpect = SVG_EXPECT_NULL;
    }
}
#endif

/* . */
char
readSvg(EmbPattern* pattern, FILE* file)
{
    REPORT_PTR(pattern)
    REPORT_PTR(file)
#if 0
    int size, pos, i;
    char* buff = 0, c;
    size = 1024;

    for (i=0; i<1000; i++) {
        attributeList[i].name = (char*)malloc(size);
        attributeList[i].value = (char*)malloc(size);
    }

    buff = (char*)malloc(size);
    if (!buff) {
        printf("ERROR: readSvg(), cannot allocate memory for buff\n");
        return 0;
    }
    svgCreator = SVG_CREATOR_NULL;
    svgExpect = SVG_EXPECT_NULL;
    svgMultiValue = 0;

    currentAttribute[0] = 0;
    currentValue[0] = 0;

    /* Pre-flip in case of multiple reads on the same pattern */
    emb_pattern_flipVertical(pattern);

    pos = 0;
    while (fread(&c, 1, 1, file)) {
        switch (c) {
        case '<':
            if (svgExpect == SVG_EXPECT_NULL) {
                svgAddToPattern(pattern);
                svgExpect = SVG_EXPECT_ELEMENT;
            }
            break;
        case '>':
            /* abnormal case that may occur in svg element where '>' is all by itself */
            if (pos == 0) {
                /*TODO: log a warning about this absurdity! */
                svgExpect = SVG_EXPECT_ELEMENT;
            }
            break;
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
                printf("ERROR: readSvg(), cannot re-allocate memory for buff\n");
                return 0;
            }
        }
    }

    safe_free(buff);

    if (emb_verbose>1) {
        printf("OBJECT SUMMARY:\n");
        if (pattern->circles) {
            for (i = 0; i < pattern->circles->count; i++) {
                EmbCircle c = pattern->circles->circle[i];
                printf("circle %f %f %f\n", c.center.x, c.center.y, c.radius);
            }
        }
        if (pattern->ellipses) {
            for (i = 0; i < pattern->ellipses->count; i++) {
                EmbEllipse e = pattern->ellipses->ellipse[i];
                printf("ellipse %f %f %f %f\n", e.center.x, e.center.y, e.radius.x, e.radius.y);
            }
        }
        if (pattern->geometry) {
            for (i = 0; i < pattern->geometry->count; i++) {
                EmbLine li = pattern->geometry->geometry[i].object.line;
                printf("line %f %f %f %f\n", li.start.x, li.start.y, li.end.x, li.end.y);
            }
        }
        if (pattern->points) {
            for (i = 0; i < pattern->points->count; i++) {
                EmbVector po = pattern->points->point[i].position;
                printf("point %f %f\n", po.x, po.y);
            }
        }
        if (pattern->polygons) {
            for (i = 0; i < pattern->polygons->count; i++) {
                EmbArray *verts = pattern->polygons->polygon[i].pointList;
                printf("polygon %d\n", verts->count);
            }
        }
        if (pattern->polylines) {
            for (i = 0; i < pattern->polylines->count; i++) {
                EmbArray * verts = pattern->polylines->polyline[i].pointList;
                printf("polyline %d\n", verts->count);
            }
        }
        if (pattern->rects) {
            for (i = 0; i < pattern->rects->count; i++) {
                EmbRect r = pattern->rects->rect[i];
                printf("rect %f %f %f %f\n", r.x, r.y, r.w, r.h);
            }
        }
    }

    for (i=0; i<1000; i++) {
        safe_free(attributeList[i].name);
        safe_free(attributeList[i].value);
    }
    /* Flip the pattern since SVG Y+ is down and libembroidery Y+ is up. */
    emb_pattern_flipVertical(pattern);
#endif
    return 1; /*TODO: finish readSvg */
}

/*! Writes the data from a pattern to a file with the given a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char
writeSvg(EmbPattern* pattern, FILE* file)
{
    EmbRect boundingRect;
    EmbRect rect;
    EmbColor color;
    int i, j;
    char isNormal, tmpX[32], tmpY[32];
    EmbRect border;

    /* Pre-flip the pattern since SVG Y+ is down and libembroidery Y+ is up. */
    emb_pattern_flipVertical(pattern);
    boundingRect = emb_pattern_bounds(pattern);
    fprintf(file, "<?xml version=\"1.0\"?>\n");
    fprintf(file, "<!-- Embroidermodder 2 SVG Embroidery File -->\n");
    fprintf(file, "<!-- http://embroidermodder.github.io -->\n");
    fprintf(file, "<svg ");

    /* TODO: See the SVG Tiny Version 1.2 Specification Section 7.14.
    *       Until all of the formats and API is stable, the width, height and viewBox attributes need to be left unspecified.
    *       If the attribute values are incorrect, some applications wont open it at all.
    */

    /* Add a margin of 10%. */
    border = boundingRect;
    border.x *= 10.0;
    border.y *= 10.0;
    border.w *= 10.0;
    border.h *= 10.0;
    border.x -= 0.1 * border.w;
    border.w += 0.2 * border.w;
    border.y -= 0.1 * border.h;
    border.h += 0.2 * border.h;
    /* Sanity check here? */
    fprintf(file, "viewBox=\"%f %f %f %f\" ",
            border.x, border.y, border.w, border.h);

    fprintf(file, "xmlns=\"http://www.w3.org/2000/svg\" version=\"1.2\" baseProfile=\"tiny\">");
    fprintf(file, "\n<g transform=\"scale(10)\">");
    /*TODO: Low Priority Optimization:
    *      Using %g in embFile_printf just doesn't work good enough at trimming trailing zeroes.
    *      It's precision refers to significant digits, not decimal places (which is what we want).
    *      We need to roll our own function for trimming trailing zeroes to keep
    *      the precision as high as possible if needed, but help reduce file size also. */

    /*TODO: Low Priority Optimization:
    *      Make sure that the line length that is output doesn't exceed 1000 characters. */

    /*TODO: Low Priority: Indent output properly. */

    /* write circles, ellipses and lines */
    for (i = 0; i < pattern->geometry->count; i++) {
        EmbGeometry g = pattern->geometry->geometry[i];
        switch (g.type) {
        case EMB_CIRCLE: {
            EmbCircle circle = g.object.circle;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file, "\n<circle stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" cx=\"%f\" cy=\"%f\" r=\"%f\" />",
                g.color.r,
                g.color.g,
                g.color.b,
                circle.center.x,
                circle.center.y,
                circle.radius);
            break;
        }
        case EMB_ELLIPSE: {
            EmbEllipse ellipse = g.object.ellipse;
            color = g.color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file, "\n<ellipse stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" />",
                        color.r,
                        color.g,
                        color.b,
                        ellipse.center.x,
                        ellipse.center.y,
                        ellipse.radius.x,
                        ellipse.radius.y);
            break;
        }
        case EMB_LINE: {
            EmbLine line = g.object.line;
            color = g.color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file,
                "\n<line stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />",
                color.r, color.g, color.b,
                line.start.x, line.start.y, line.end.x, line.end.y);
            break;
        }
        case EMB_POINT: {
            EmbPoint p = g.object.point;
            /* See SVG Tiny 1.2 Spec:
             * Section 9.5 The 'line' element
             * Section C.6 'path' element implementation notes */
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file,
                "\n<line stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />",
                p.color.r, p.color.g, p.color.b,
                p.position.x, p.position.y, p.position.x, p.position.y);
            break;
        }
        case EMB_POLYGON: {
            EmbArray *pointList = g.object.polygon.pointList;
            color = g.object.color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
                fprintf(file, "\n<polygon stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"%s,%s",
                    color.r, color.g, color.b,
                    emb_optOut(pointList->geometry[0].object.point.position.x, tmpX),
                    emb_optOut(pointList->geometry[0].object.point.position.y, tmpY));
            for (j=1; j < pointList->count; j++) {
                fprintf(file, " %s,%s",
                    emb_optOut(pointList->geometry[j].object.point.position.x, tmpX),
                    emb_optOut(pointList->geometry[j].object.point.position.y, tmpY));
            }
            fprintf(file, "\"/>");
            break;
        }
        case EMB_POLYLINE: {
            EmbArray *pointList = g.object.polyline.pointList;
            color = g.object.polyline.color;
            /* TODO: use proper thread width for stoke-width rather
             * than just 0.2.
             */
            fprintf(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"%s,%s",
                    color.r,
                    color.g,
                    color.b,
                    emb_optOut(pointList->geometry[0].object.point.position.x, tmpX),
                    emb_optOut(pointList->geometry[0].object.point.position.y, tmpY));
            for (j=1; j < pointList->count; j++) {
                fprintf(file, " %s,%s",
                    emb_optOut(pointList->geometry[j].object.point.position.x, tmpX),
                    emb_optOut(pointList->geometry[j].object.point.position.y, tmpY));
            }
            fprintf(file, "\"/>");
            break;
        }
        case EMB_RECT: {
            rect = g.object.rect;
            color = g.object.color;
            /* TODO: use proper thread width for stoke-width rather
             * than just 0.2.
             */
            fprintf(file, "\n<rect stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" />",
                color.r, color.g, color.b,
                rect.x, rect.y, rect.w, rect.h);
            break;
        }
        default:
            break;
        }
    }

    isNormal = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* TODO:
         * #ifdef SVG_DEBUG for Josh which outputs
         * JUMPS/TRIMS instead of chopping them out.
         */
        if (st.flags == NORMAL && !isNormal) {
            isNormal = 1;
            color = pattern->thread_list->thread[st.color].color;
            /* TODO: use proper thread width for stoke-width rather
             * than just 0.2.
             */
              fprintf(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"%s,%s",
                                color.r,
                                color.g,
                                color.b,
                                emb_optOut(st.x, tmpX),
                                emb_optOut(st.y, tmpY));
            }
            else if (st.flags == NORMAL && isNormal)
            {
                fprintf(file, " %s,%s", emb_optOut(st.x, tmpX), emb_optOut(st.y, tmpY));
            }
            else if (st.flags != NORMAL && isNormal)
            {
                isNormal = 0;
                fprintf(file, "\"/>");
            }
    }
    fprintf(file, "\n</g>\n</svg>\n");

    /* Reset the pattern so future writes(regardless of format)
     * are not flipped.
     */
    emb_pattern_flipVertical(pattern);

    return 1;
}

/*
 * Pfaff Embroidery Format (.t01)
 * The Pfaff t01 format is stitch-only.
 */

char
readT01(EmbPattern* pattern, FILE* file)
{
    unsigned char b[3];

    while (fread(b, 1, 3, file) == 3) {
        int flags, x, y;
        decode_t01_record(b, &flags, &x, &y);
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        if (flags == END) {
            break;
        }
    }
    return 1;
}

char
writeT01(EmbPattern* pattern, FILE* file)
{
    EmbRect boundingRect;
    int i;
    EmbVector pos;

    emb_pattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    boundingRect = emb_pattern_bounds(pattern);
    if (emb_verbose>1) {
        printf("bounding rectangle with top %f not used ", boundingRect.x);
        printf("in the function writeT01\n");
    }
    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned char b[3];
        int dx, dy;
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)emb_round(10.0*(st.x - pos.x));
        dy = (int)emb_round(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;
        encode_t01_record(b, dx, dy, st.flags);
        fwrite(b, 1, 3, file);
    }
    return 1;
}

/*
 * Pfaff Embroidery Format (.t09)
 * The Pfaff t09 format is stitch-only.
 */

char
readT09(EmbPattern* pattern, FILE* file)
{
    unsigned char b[3];

    fseek(file, 0x0C, SEEK_SET);

    while (fread(b, 1, 3, file) == 3) {
        int stitchType = NORMAL;
        int b1 = b[0];
        int b2 = b[1];
        unsigned char commandByte = b[2];
        if (commandByte == 0x00) {
            break;
        }
        if (commandByte & 0x10) {
            stitchType = STOP;
        }
        if (commandByte & 0x20) {
            b1 = -b1;
        }
        if (commandByte & 0x40) {
            b2 = -b2;
        }
        emb_pattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    return 1;
}

char
writeT09(EmbPattern* pattern, FILE* file)
{
    int i;
    EmbVector pos;
    fpad(file, 0x00, 0x0C);

    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned char b[3];
        int dx, dy;
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)emb_round(10.0*(st.x - pos.x));
        dy = (int)emb_round(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;

        b[0] = dx;
        b[1] = dy;
        b[2] = 0;
        if (st.flags & NORMAL) {
            /* guessing based on T01 here */
            b[2] |= 0x03;
        }
        /* inferred from readT09 */
        if (st.flags & STOP) {
            b[2] |= 0x10;
        }
        if (dx < 0) {
            b[0] = -dx;
            b[2] |= 0x20;
        }
        if (dy < 0) {
            b[0] = -dy;
            b[2] |= 0x40;
        }
        fwrite(b, 1, 3, file);
    }
    return 1;
}

/*
 * Happy Embroidery Format (.tap)
 * The Happy tap format is stitch-only.
 */

void
encode_tap_record(FILE* file, int x, int y, int flags)
{
    unsigned char b[3];
    encode_tajima_ternary(b, x, y);

    b[2] |= (char)3;
    if (flags & END) {
        b[0] = 0;
        b[1] = 0;
        b[2] = 0xF3;
    }
    if (flags & (JUMP | TRIM)) {
        b[2] = (char)(b[2] | 0x83);
    }
    if (flags & STOP) {
        b[2] = (char)(b[2] | 0xC3);
    }
    fwrite(b, 1, 3, file);
}

int
decode_tap_record_flags(unsigned char b2)
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

char
readTap(EmbPattern* pattern, FILE* file) {
    unsigned char b[3];

    while (fread(b, 1, 3, file) == 3) {
        int flags, x, y;
        decode_tajima_ternary(b, &x, &y);
        flags = decode_tap_record_flags(b[2]);
        emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        if (flags == END) {
            break;
        }
    }
    return 1;
}

char
writeTap(EmbPattern* pattern, FILE* file)
{
    int i;
    EmbVector pos;

    emb_pattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        int dx, dy;
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)emb_round(10.0*(st.x - pos.x));
        dy = (int)emb_round(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;
        encode_tap_record(file, dx, dy, st.flags);
    }
    return 1;
}

/*
 * ThredWorks Embroidery Format (.thr)
 * The ThreadWorks thr format is stitch-only.
 *
 * bit definitions for attributes of stitch
 * 0-3     stitch color
 * 4-14    form pointer
 * 15-18   spares
 * 19      not a form stitch
 * 20      center walk stitch
 * 21      edge walk stitch
 * 22      underlay stitch
 * 23      knot stitch
 * 24      feather stitch
 * 25-27   layer
 * 28      spare
 * 29-30   stitch type
 *             00=not a form stitch,
 *             01=form fill,
 *             10=form border fill,
 *             11=applique stitches
 * 31      set for user edited stitches
 */
char
readThr(EmbPattern* pattern, FILE* file)
{
    ThredHeader header;
    EmbColor background;
    int currentColor;
    int i;

    header.sigVersion = emb_read_i32(file);
    header.length = emb_read_i32(file);
    header.numStiches = emb_read_i16(file);
    LOAD_U16(file, header.hoopSize)
    for (i=0; i<7; i++) {
        header.reserved[i] = emb_read_u16(file);
        printf("header.reserved[%d] = %d\n", i, header.reserved[i]);
    }

    if ((header.sigVersion & 0xffffff) == 0x746872) {
        unsigned int verVar = (header.sigVersion & 0xff000000) >> 24;
        switch (verVar) {
            case 0:
                break;
            case 1:
            case 2:
                /* skip the file header extension */
                fseek(file, 144, SEEK_CUR);
                break;
            default:
                return 0; /* unsupported version */
        }
    }
    currentColor = -1;
    for (i = 0; i < header.numStiches; i++) {
        int type = NORMAL;
        float x, y;
        unsigned int color;
        x = emb_read_i32(file);
        y = emb_read_i32(file);
        color = emb_read_i32(file);
        x /= 10.0;
        y /= 10.0;

        if ((int)(color & 0xF) != currentColor) {
            currentColor = (int)color & 0xF;
            emb_pattern_changeColor(pattern, currentColor);
            type = STOP | TRIM;
        }
        emb_pattern_addStitchAbs(pattern, x, y, type, 0);
    }
    fseek(file, 16, SEEK_CUR); /* skip bitmap name (16 chars) */

    embColor_read(file, &background, 4);
    if (emb_verbose>1) {
        printf("background: %c %c %c\n", background.r, background.g, background.b);
    }
    for (i = 0; i < 16; i++) {
        EmbThread thread;
        strcpy(thread.description, "NULL");
        strcpy(thread.catalogNumber, "NULL");
        embColor_read(file, &(thread.color), 4);
        emb_pattern_addThread(pattern, thread);
    }
    /*  64 bytes of rgbx(4 bytes) colors (16 custom colors) */
    /*  16 bytes of thread size (ascii representation ie. '4') */
    return 1;
}

char
writeThr(EmbPattern* pattern, FILE* file)
{
    int i, stitchCount;
    unsigned char version = 0;
    ThredHeader header;
    ThredExtension extension;
    char bitmapName[16];

    stitchCount = pattern->stitch_list->count;

    memset(&header, 0, sizeof(ThredHeader));
    header.sigVersion = 0x746872 | (version << 24);
    header.length = stitchCount * 12 + 16;
    if (version == 1 || version == 2) {
        header.length = header.length + sizeof(ThredHeader);
    }
    header.numStiches = (unsigned short)stitchCount; /* number of stitches in design */
    header.hoopSize = 5;

    emb_write_u32(file, header.sigVersion);
    emb_write_u32(file, header.length);
    emb_write_u16(file, header.numStiches);
    emb_write_u16(file, header.hoopSize);
    for (i=0; i<7; i++) {
        emb_write_u16(file, header.reserved[i]);
    }

    if (version == 1 || version == 2) {
        memset(&extension, 0, sizeof(ThredExtension));
        extension.auxFormat = 1;
        extension.hoopX = 640;
        extension.hoopY = 640;

        emb_write_i32(file, extension.hoopX);
        emb_write_i32(file, extension.hoopY);
        emb_write_i32(file, extension.stitchGranularity);
        fwrite(extension.creatorName, 1, 50, file);
        fwrite(extension.modifierName, 1, 50, file);
        fputc(extension.auxFormat, file);
        fwrite(extension.reserved, 1, 31, file);
    }

    /* write stitches */
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned int NOTFRM = 0x00080000;
        EmbStitch st = pattern->stitch_list->stitch[i];
        float x, y;
        x = (float)(st.x * 10.0);
        y = (float)(st.y * 10.0);
        emb_write_i32(file, x);
        emb_write_i32(file, y);
        emb_write_u32(file, NOTFRM | (st.color & 0x0F));
    }
    fwrite(bitmapName, 1, 16, file);
    /* background color */
    fwrite("\xFF\xFF\xFF\x00", 1, 4, file);

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c = pattern->thread_list->thread[i].color;
        embColor_write(file, c, 4);
        if (i >= 16) break;
    }

    /* write remaining colors if not yet 16 */
    fpad(file, 0, 4*(16-i));

    fpad(file, '4', 16);
    return 1;
}

/*
 * Text File (.txt)
 * The txt format is stitch-only and isn't associated with a specific company.
 */
char
readTxt(EmbPattern* pattern, FILE* file)
{
    EmbString line;
    int stated_count, i;
    emb_readline(file, line, 99);
    stated_count = atoi(line);
    for (i=0; i<stated_count; i++) {
        EmbStitch st;
        char *p, *y, *color, *flags;
        int state = 0;
        emb_readline(file, line, 99);
        p = line;
        y = line;
        color = line;
        flags = line;
        for (p=line; *p; p++) {
            if (*p == ',' || *p == ' ') {
                *p = 0;
                switch (state) {
                case 0:
                    y = p+1;
                    break;
                case 1:
                    color = p+7;
                    break;
                case 2:
                    flags = p+7;
                    break;
                default:
                    break;
                }
                state++;
            }
        }
        st.x = atof(line);
        st.y = atof(y);
        st.color = atoi(color);
        st.flags = atoi(flags);
        emb_pattern_addStitchAbs(pattern, st.x, st.y, st.flags, st.color);
    }
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readTxt */
}

char
writeTxt(EmbPattern* pattern, FILE* file)
{
    int i;
    fprintf(file, "%u\n", (unsigned int) pattern->stitch_list->count);

    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch s = pattern->stitch_list->stitch[i];
        fprintf(file, "%.1f,%.1f color:%i flags:%i\n",
                s.x, s.y, s.color, s.flags);
    }
    return 1;
}

/*
 * Barudan Embroidery Format (.u00)
 * The Barudan u00 format is stitch-only.
 */
char
readU00(EmbPattern* pattern, FILE* file)
{
    int i;
    char dx = 0, dy = 0;
    int flags = NORMAL;
    unsigned char b[3];

    if (!check_header_present(file, 0x100)) {
        return 0;
    }

    /* 16 3byte RGB's start @ 0x08 followed by 14 bytes between
        0 and 15 with index of color for each color change */
    fseek(file, 0x08, SEEK_SET);
    for (i = 0; i < 16; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 3);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        emb_pattern_addThread(pattern, t);
    }

    fseek(file, 0x100, SEEK_SET);
    while (fread(b, 1, 3, file) == 3) {
        char negativeX , negativeY;

        if (b[0] == 0xF8 || b[0] == 0x87 || b[0] == 0x91) {
            break;
        }
        if ((b[0] & 0x0F) == 0) {
            flags = NORMAL;
        } else if ((b[0] & 0x1f) == 1) {
            flags = JUMP;
        } else if ((b[0] & 0x0F) > 0) {
            flags = STOP;
        }
        negativeX = ((b[0] & 0x20) > 0);
        negativeY = ((b[0] & 0x40) > 0);

        dx = (char) b[2];
        dy = (char) b[1];
        if (negativeX) {
            dx = (char) -dx;
        }
        if (negativeY) {
            dy = (char) -dy;
        }
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writeU00(EmbPattern* pattern, FILE* file)
{
    puts("writeU00 not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish WriteU00 */
}

/*
 * Barudan Embroidery Format (.u01)
 * The Barudan u01 format is stitch-only.
 *
 * TODO: AFAIK this is a duplicate of U00. Review for differences and merge
 * files and handle accordingly.
 */
char
readU01(EmbPattern* pattern, FILE* file)
{
    int fileLength, negativeX = 0, negativeY = 0, flags = NORMAL;
    char dx, dy;
    unsigned char data[3];

    if (!check_header_present(file, 0x100)) {
        return 0;
    }

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x100, SEEK_SET);

    if (emb_verbose>1) {
        printf("file length: %d\n", fileLength);
    }

    while (fread(data, 1, 3, file) == 3) {
        if (data[0] == 0xF8 || data[0] == 0x87 || data[0] == 0x91) {
            break;
        }
        if ((data[0] & 0x0F) == 0) {
            flags = NORMAL;
        } else if ((data[0] & 0x1f) == 1) {
            flags = JUMP;
        } else if ((data[0] & 0x0F) > 0) {
            flags = STOP;
        }
        negativeX = ((data[0] & 0x20) > 0);
        negativeY = ((data[0] & 0x40) > 0);

        dx = (char) data[2];
        dy = (char) data[1];
        if (negativeX) {
            dx = (char) -dx;
        }
        if (negativeY) {
            dy = (char) -dy;
        }
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

char
writeU01(EmbPattern* pattern, FILE* file)
{
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeU01 */
}

/*
 * Pfaff Embroidery Format (.vip). The vip format is stitch-only.
 */

const unsigned char vipDecodingTable[] = {
    0x2E, 0x82, 0xE4, 0x6F, 0x38, 0xA9, 0xDC, 0xC6, 0x7B, 0xB6, 0x28, 0xAC, 0xFD, 0xAA, 0x8A, 0x4E,
    0x76, 0x2E, 0xF0, 0xE4, 0x25, 0x1B, 0x8A, 0x68, 0x4E, 0x92, 0xB9, 0xB4, 0x95, 0xF0, 0x3E, 0xEF,
    0xF7, 0x40, 0x24, 0x18, 0x39, 0x31, 0xBB, 0xE1, 0x53, 0xA8, 0x1F, 0xB1, 0x3A, 0x07, 0xFB, 0xCB,
    0xE6, 0x00, 0x81, 0x50, 0x0E, 0x40, 0xE1, 0x2C, 0x73, 0x50, 0x0D, 0x91, 0xD6, 0x0A, 0x5D, 0xD6,
    0x8B, 0xB8, 0x62, 0xAE, 0x47, 0x00, 0x53, 0x5A, 0xB7, 0x80, 0xAA, 0x28, 0xF7, 0x5D, 0x70, 0x5E,
    0x2C, 0x0B, 0x98, 0xE3, 0xA0, 0x98, 0x60, 0x47, 0x89, 0x9B, 0x82, 0xFB, 0x40, 0xC9, 0xB4, 0x00,
    0x0E, 0x68, 0x6A, 0x1E, 0x09, 0x85, 0xC0, 0x53, 0x81, 0xD1, 0x98, 0x89, 0xAF, 0xE8, 0x85, 0x4F,
    0xE3, 0x69, 0x89, 0x03, 0xA1, 0x2E, 0x8F, 0xCF, 0xED, 0x91, 0x9F, 0x58, 0x1E, 0xD6, 0x84, 0x3C,
    0x09, 0x27, 0xBD, 0xF4, 0xC3, 0x90, 0xC0, 0x51, 0x1B, 0x2B, 0x63, 0xBC, 0xB9, 0x3D, 0x40, 0x4D,
    0x62, 0x6F, 0xE0, 0x8C, 0xF5, 0x5D, 0x08, 0xFD, 0x3D, 0x50, 0x36, 0xD7, 0xC9, 0xC9, 0x43, 0xE4,
    0x2D, 0xCB, 0x95, 0xB6, 0xF4, 0x0D, 0xEA, 0xC2, 0xFD, 0x66, 0x3F, 0x5E, 0xBD, 0x69, 0x06, 0x2A,
    0x03, 0x19, 0x47, 0x2B, 0xDF, 0x38, 0xEA, 0x4F, 0x80, 0x49, 0x95, 0xB2, 0xD6, 0xF9, 0x9A, 0x75,
    0xF4, 0xD8, 0x9B, 0x1D, 0xB0, 0xA4, 0x69, 0xDB, 0xA9, 0x21, 0x79, 0x6F, 0xD8, 0xDE, 0x33, 0xFE,
    0x9F, 0x04, 0xE5, 0x9A, 0x6B, 0x9B, 0x73, 0x83, 0x62, 0x7C, 0xB9, 0x66, 0x76, 0xF2, 0x5B, 0xC9,
    0x5E, 0xFC, 0x74, 0xAA, 0x6C, 0xF1, 0xCD, 0x93, 0xCE, 0xE9, 0x80, 0x53, 0x03, 0x3B, 0x97, 0x4B,
    0x39, 0x76, 0xC2, 0xC1, 0x56, 0xCB, 0x70, 0xFD, 0x3B, 0x3E, 0x52, 0x57, 0x81, 0x5D, 0x56, 0x8D,
    0x51, 0x90, 0xD4, 0x76, 0xD7, 0xD5, 0x16, 0x02, 0x6D, 0xF2, 0x4D, 0xE1, 0x0E, 0x96, 0x4F, 0xA1,
    0x3A, 0xA0, 0x60, 0x59, 0x64, 0x04, 0x1A, 0xE4, 0x67, 0xB6, 0xED, 0x3F, 0x74, 0x20, 0x55, 0x1F,
    0xFB, 0x23, 0x92, 0x91, 0x53, 0xC8, 0x65, 0xAB, 0x9D, 0x51, 0xD6, 0x73, 0xDE, 0x01, 0xB1, 0x80,
    0xB7, 0xC0, 0xD6, 0x80, 0x1C, 0x2E, 0x3C, 0x83, 0x63, 0xEE, 0xBC, 0x33, 0x25, 0xE2, 0x0E, 0x7A,
    0x67, 0xDE, 0x3F, 0x71, 0x14, 0x49, 0x9C, 0x92, 0x93, 0x0D, 0x26, 0x9A, 0x0E, 0xDA, 0xED, 0x6F,
    0xA4, 0x89, 0x0C, 0x1B, 0xF0, 0xA1, 0xDF, 0xE1, 0x9E, 0x3C, 0x04, 0x78, 0xE4, 0xAB, 0x6D, 0xFF,
    0x9C, 0xAF, 0xCA, 0xC7, 0x88, 0x17, 0x9C, 0xE5, 0xB7, 0x33, 0x6D, 0xDC, 0xED, 0x8F, 0x6C, 0x18,
    0x1D, 0x71, 0x06, 0xB1, 0xC5, 0xE2, 0xCF, 0x13, 0x77, 0x81, 0xC5, 0xB7, 0x0A, 0x14, 0x0A, 0x6B,
    0x40, 0x26, 0xA0, 0x88, 0xD1, 0x62, 0x6A, 0xB3, 0x50, 0x12, 0xB9, 0x9B, 0xB5, 0x83, 0x9B, 0x37
};

int
vipDecodeByte(unsigned char b)
{
    if (b >= 0x80) return (-(unsigned char) (~b + 1));
    return b;
}

int
vipDecodeStitchType(unsigned char b)
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

unsigned char*
vipDecompressData(unsigned char* input, int compressedInputLength, int decompressedContentLength)
{
    unsigned char* decompressedData = (unsigned char*)malloc(decompressedContentLength);
    if (!decompressedData) {
        printf("ERROR: format-vip.c vipDecompressData(), cannot allocate memory for decompressedData\n");
        return 0;
    }
    hus_decompress((char*)input, compressedInputLength, (char *)decompressedData, &decompressedContentLength);
    return decompressedData;
}

char
readVip(EmbPattern* pattern, FILE* file)
{
    int fileLength;
    int i;
    unsigned char prevByte = 0;
    unsigned char *attributeData = 0, *decodedColors = 0;
    unsigned char *attributeDataDecompressed = 0;
    unsigned char *xData = 0, *xDecompressed = 0, *yData = 0, *yDecompressed = 0;
    VipHeader header;

    fileLength = check_header_present(file, 32);
    if (!fileLength) {
        printf("ERROR: file shorter than header.");
        return 0;
    }

    header.magicCode = emb_read_i32(file);
    header.numberOfStitches = emb_read_i32(file);
    header.numberOfColors = emb_read_i32(file);

    header.postitiveXHoopSize = emb_read_i16(file);
    header.postitiveYHoopSize = emb_read_i16(file);
    header.negativeXHoopSize = emb_read_i16(file);
    header.negativeYHoopSize = emb_read_i16(file);
    header.attributeOffset = emb_read_i32(file);
    header.xOffset = emb_read_i32(file);
    header.yOffset = emb_read_i32(file);

    if (!read_n_bytes(file, header.stringVal, 8)) {
        return 0;
    }

    header.unknown = emb_read_i16(file);

    header.colorLength = emb_read_i32(file);
    decodedColors = (unsigned char*)malloc(header.numberOfColors*4);
    if (!decodedColors) {
        printf("ERROR: format-vip.c readVip(), ");
        printf("cannot allocate memory for decodedColors\n");
        return 0;
    }
    for (i = 0; i < header.numberOfColors*4; ++i) {
        unsigned char inputByte = (char)fgetc(file);
        unsigned char tmpByte = (unsigned char) (inputByte ^ vipDecodingTable[i]);
        decodedColors[i] = (unsigned char) (tmpByte ^ prevByte);
        prevByte = inputByte;
    }
    for (i = 0; i < header.numberOfColors; i++) {
        EmbThread thread;
        int startIndex = i << 2;
        thread.color.r = decodedColors[startIndex];
        thread.color.g = decodedColors[startIndex + 1];
        thread.color.b = decodedColors[startIndex + 2];
        /* printf("%d\n", decodedColors[startIndex + 3]); */
        emb_pattern_addThread(pattern, thread);
    }
    fseek(file, header.attributeOffset, SEEK_SET);
    attributeData = (unsigned char*)malloc(header.xOffset - header.attributeOffset);
    if (!attributeData) {
        printf("ERROR: format-vip.c readVip(), cannot allocate memory for attributeData\n");
        return 0;
    }
    fread(attributeData, 1, header.xOffset - header.attributeOffset, file); /* TODO: check return value */
    attributeDataDecompressed = vipDecompressData(attributeData, header.xOffset - header.attributeOffset, header.numberOfStitches);

    fseek(file, header.xOffset, SEEK_SET);
    xData = (unsigned char*)malloc(header.yOffset - header.xOffset);
    if (!xData) {
        printf("ERROR: format-vip.c readVip(), cannot allocate memory for xData\n");
        return 0;
    }
    fread(xData, 1, header.yOffset - header.xOffset, file); /* TODO: check return value */
    xDecompressed = vipDecompressData(xData, header.yOffset - header.xOffset, header.numberOfStitches);

    fseek(file, header.yOffset, SEEK_SET);
    yData = (unsigned char*)malloc(fileLength - header.yOffset);
    if (!yData) { printf("ERROR: format-vip.c readVip(), cannot allocate memory for yData\n"); return 0; }
    fread(yData, 1, fileLength - header.yOffset, file); /* TODO: check return value */
    yDecompressed = vipDecompressData(yData, fileLength - header.yOffset, header.numberOfStitches);

    for (i = 0; i < header.numberOfStitches; i++) {
        emb_pattern_addStitchRel(pattern,
                    vipDecodeByte(xDecompressed[i]) / 10.0,
                    vipDecodeByte(yDecompressed[i]) / 10.0,
                    vipDecodeStitchType(attributeDataDecompressed[i]), 1);
    }
    emb_pattern_addStitchRel(pattern, 0, 0, END, 1);

    safe_free(attributeData);
    safe_free(xData);
    safe_free(yData);
    safe_free(attributeDataDecompressed);
    safe_free(xDecompressed);
    safe_free(yDecompressed);
    return 1;
}

unsigned char*
vipCompressData(unsigned char* input, int decompressedInputSize, int* compressedSize)
{
    unsigned char* compressedData = (unsigned char*)malloc(decompressedInputSize*2);
    if (!compressedData) {
        printf("ERROR: format-vip.c vipCompressData(), cannot allocate memory for compressedData\n");
        return 0;
    }
    hus_compress((char*)input, decompressedInputSize, (char *)compressedData, compressedSize);
    return compressedData;
}

unsigned char
vipEncodeByte(EmbReal f)
{
    return (unsigned char)(int)emb_round(f);
}

unsigned char
vipEncodeStitchType(int st)
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

char
writeVip(EmbPattern* pattern, FILE* file)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor;
    int attributeSize = 0;
    int xCompressedSize = 0;
    int yCompressedSize = 0;
    EmbReal previousX = 0;
    EmbReal previousY = 0;
    unsigned char* xValues = 0, *yValues = 0, *attributeValues = 0;
    EmbReal xx = 0.0;
    EmbReal yy = 0.0;
    int flags = 0;
    int i = 0;
    unsigned char* attributeCompressed = 0, *xCompressed = 0;
    unsigned char* yCompressed = 0, *decodedColors = 0, *encodedColors = 0;
    unsigned char prevByte = 0;

    puts("VIP not yet implemented.");
    return 0;

    stitchCount = pattern->stitch_list->count;
    minColors = pattern->thread_list->count;
    decodedColors = (unsigned char*)malloc(minColors << 2);
    if (!decodedColors) {
        return 0;
    }
    encodedColors = (unsigned char*)malloc(minColors << 2);
    if (!encodedColors) {
        safe_free(decodedColors);
        return 0;
    }
    /* emb_pattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */

    patternColor = minColors;
    if (emb_verbose>1) {
        printf("patternColor: %d\n", patternColor);
    }
    if (minColors > 24) {
        minColors = 24;
    }
    emb_write_u32(file, 0x0190FC5D);
    emb_write_u32(file, stitchCount);
    emb_write_u32(file, minColors);

    boundingRect = emb_pattern_bounds(pattern);
    emb_write_i16(file, (int16_t) emb_round((boundingRect.x+boundingRect.w) * 10.0));
    emb_write_i16(file, (int16_t) -emb_round(boundingRect.y * 10.0 - 1.0));
    emb_write_i16(file, (int16_t) emb_round(boundingRect.x * 10.0));
    emb_write_i16(file, (int16_t) -emb_round((boundingRect.y+boundingRect.h) * 10.0 - 1.0));

    emb_write_u32(file, 0x38 + (minColors << 3));

    xValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    yValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    attributeValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if (xValues && yValues && attributeValues) {
        for (i = 0; i < pattern->stitch_list->count; i++) {
            EmbStitch st;
            st = pattern->stitch_list->stitch[i];
            xx = st.x;
            yy = st.y;
            flags = st.flags;
            xValues[i] = vipEncodeByte((xx - previousX) * 10.0);
            previousX = xx;
            yValues[i] = vipEncodeByte((yy - previousY) * 10.0);
            previousY = yy;
            attributeValues[i] = vipEncodeStitchType(flags);
        }
        attributeCompressed = vipCompressData(attributeValues, stitchCount, &attributeSize);
        xCompressed = vipCompressData(xValues, stitchCount, &xCompressedSize);
        yCompressed = vipCompressData(yValues, stitchCount, &yCompressedSize);

        emb_write_u32(file, (unsigned int) (0x38 + (minColors << 3) + attributeSize));
        emb_write_u32(file, (unsigned int) (0x38 + (minColors << 3) + attributeSize + xCompressedSize));
        emb_write_u32(file, 0x00000000);
        emb_write_u32(file, 0x00000000);
        emb_write_u16(file, 0x0000);

        emb_write_i32(file, minColors << 2);

        for (i = 0; i < minColors; i++) {
            int byteChunk = i << 2;
            EmbColor currentColor = pattern->thread_list->thread[i].color;
            decodedColors[byteChunk] = currentColor.r;
            decodedColors[byteChunk + 1] = currentColor.g;
            decodedColors[byteChunk + 2] = currentColor.b;
            decodedColors[byteChunk + 3] = 0x01;
        }

        for (i = 0; i < minColors << 2; ++i) {
            unsigned char tmpByte = (unsigned char) (decodedColors[i] ^ vipDecodingTable[i]);
            prevByte = (unsigned char) (tmpByte ^ prevByte);
            fputc(prevByte, file);
        }
        for (i = 0; i <= minColors; i++) {
            emb_write_i32(file, 1);
        }
        emb_write_u32(file, 0); /* string length */
        emb_write_i16(file, 0);
        fwrite((char*) attributeCompressed, 1, attributeSize, file);
        fwrite((char*) xCompressed, 1, xCompressedSize, file);
        fwrite((char*) yCompressed, 1, yCompressedSize, file);
    }

    safe_free(attributeCompressed);
    safe_free(xCompressed);
    safe_free(yCompressed);
    safe_free(attributeValues);
    safe_free(xValues);
    safe_free(yValues);
    safe_free(decodedColors);
    safe_free(encodedColors);
    return 1;
}

/*
 * VP3 FORMAT
 * Pfaff Embroidery Format (.vp3)
 *
 * The Pfaff vp3 format is stitch-only.
 */
unsigned char*
vp3ReadString(FILE* file)
{
    short stringLength;
    unsigned char* charString = 0;
    if (!file) {
        printf("ERROR: format-vp3.c vp3ReadString(), file argument is null\n");
        return 0;
    }
    stringLength = emb_read_i16be(file);
    charString = (unsigned char*)malloc(stringLength);
    if (!charString) {
        printf("ERROR: format-vp3.c vp3ReadString(), cannot allocate memory for charString\n");
        return 0;
    }
    fread(charString, 1, stringLength, file); /* TODO: check return value */
    return charString;
}

int
vp3Decode(unsigned char inputByte)
{
    if (inputByte > 0x80) {
        return (int)-((unsigned char)((~inputByte) + 1));
    }
    return ((int)inputByte);
}

short
vp3DecodeInt16(unsigned short inputByte)
{
    if (inputByte > 0x8000) {
        return -((int16_t) ((~inputByte) + 1));
    }
    return ((int16_t)inputByte);
}

vp3Hoop
vp3ReadHoopSection(FILE* file)
{
    vp3Hoop hoop;

    if (!file) {
        printf("ERROR: format-vp3.c vp3ReadHoopSection(), file argument is null\n");
        hoop.bottom = 0;
        hoop.left = 0;
        hoop.right = 0;
        hoop.top = 0;
        hoop.threadLength = 0;
        hoop.unknown2 = 0;
        hoop.numberOfColors = 0;
        hoop.unknown3 = 0;
        hoop.unknown4 = 0;
        hoop.numberOfBytesRemaining = 0;

        hoop.xOffset = 0;
        hoop.yOffset = 0;

        hoop.byte1 = 0;
        hoop.byte2 = 0;
        hoop.byte3 = 0;
        hoop.right2 = 0;
        hoop.left2 = 0;
        hoop.bottom2 = 0;
        hoop.top2 = 0;
        hoop.height = 0;
        hoop.width = 0;
        return hoop;
    }

    hoop.right = emb_read_i32be(file);
    hoop.bottom = emb_read_i32be(file);
    hoop.left = emb_read_i32be(file);
    hoop.top = emb_read_i32be(file);

    /* yes, it seems this is _not_ big endian */
    hoop.threadLength = emb_read_i32(file);
    hoop.unknown2 = (char)fgetc(file);
    hoop.numberOfColors = (char)fgetc(file);
    hoop.unknown3 = emb_read_i16be(file);
    hoop.unknown4 = emb_read_i32be(file);
    hoop.numberOfBytesRemaining = emb_read_i32be(file);

    hoop.xOffset = emb_read_i32be(file);
    hoop.yOffset = emb_read_i32be(file);

    hoop.byte1 = (char)fgetc(file);
    hoop.byte2 = (char)fgetc(file);
    hoop.byte3 = (char)fgetc(file);

    /* Centered hoop dimensions */
    hoop.right2 = emb_read_i32be(file);
    hoop.left2 = emb_read_i32be(file);
    hoop.bottom2 = emb_read_i32be(file);
    hoop.top2 = emb_read_i32be(file);

    hoop.width = emb_read_i32be(file);
    hoop.height = emb_read_i32be(file);
    return hoop;
}

char
readVp3(EmbPattern* pattern, FILE* file)
{
    unsigned char magicString[5];
    unsigned char some;
    unsigned char* softwareVendorString = 0;
    /* unsigned char v2, ..., v18; */
    unsigned char* anotherSoftwareVendorString = 0;
    int numberOfColors;
    long colorSectionOffset;
    unsigned char magicCode[6];
    short someShort;
    unsigned char someByte;
    int bytesRemainingInFile, hoopConfigurationOffset;
    unsigned char* fileCommentString = 0; /* some software writes used settings here */
    unsigned char* anotherCommentString = 0;
    int i;

    fread(magicString, 1, 5, file); /* %vsm% */ /* TODO: check return value */
    LOAD_I8(file, some) /* 0 */
    softwareVendorString = vp3ReadString(file);
    REPORT_STR(softwareVendorString)
    LOAD_I16(file, someShort)
    LOAD_I8(file, someByte)
    LOAD_I32(file, bytesRemainingInFile)
    fileCommentString = vp3ReadString(file);
    hoopConfigurationOffset = (int)ftell(file);
    REPORT_INT(hoopConfigurationOffset);

    vp3ReadHoopSection(file);

    anotherCommentString = vp3ReadString(file);
    REPORT_STR(anotherCommentString);

    /* TODO: review v1 thru v18 variables and use emb_unused() if needed */
    for (i = 0; i < 18; i++) {
        unsigned char v1;
        v1 = (char)fgetc(file);
        if (emb_verbose>1) {
            printf("v%d = %d\n", i, v1);
        }
    }

    /* TODO: check return value */
    /* 0x78 0x78 0x55 0x55 0x01 0x00 */
    if (fread(magicCode, 1, 6, file) != 6) {
        puts("ERROR: Failed to read magicCode.");
        return 0;
    }

    anotherSoftwareVendorString = vp3ReadString(file);
    REPORT_STR(anotherSoftwareVendorString);

    numberOfColors = emb_read_i16be(file);
    colorSectionOffset = (int)ftell(file);

    for (i = 0; i < numberOfColors; i++) {
        EmbThread t;
        char tableSize;
        int startX, startY, offsetToNextColorX, offsetToNextColorY;
        unsigned char* threadColorNumber, *colorName, *threadVendor;
        int unknownThreadString, numberOfBytesInColor;

        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        fseek(file, colorSectionOffset, SEEK_SET);
        printf("ERROR: format-vp3.c Color Check Byte #1: 0 == %d\n", (char)fgetc(file));
        printf("ERROR: format-vp3.c Color Check Byte #2: 5 == %d\n", (char)fgetc(file));
        printf("ERROR: format-vp3.c Color Check Byte #3: 0 == %d\n", (char)fgetc(file));
        colorSectionOffset = emb_read_i32be(file);
        colorSectionOffset += ftell(file);
        startX = emb_read_i32be(file);
        startY = emb_read_i32be(file);
        emb_pattern_addStitchAbs(pattern, startX / 1000.0, -startY / 1000.0, JUMP, 1);

        tableSize = (char)fgetc(file);
        fseek(file, 1, SEEK_CUR);
        embColor_read(file, &(t.color), 3);
        emb_pattern_addThread(pattern, t);
        fseek(file, 6*tableSize - 1, SEEK_CUR);

        threadColorNumber = vp3ReadString(file);
        colorName = vp3ReadString(file);
        threadVendor = vp3ReadString(file);

        offsetToNextColorX = emb_read_i32be(file);
        offsetToNextColorY = emb_read_i32be(file);

        unknownThreadString = emb_read_i16be(file);
        fseek(file, unknownThreadString, SEEK_CUR);
        numberOfBytesInColor = emb_read_i32be(file);
        fseek(file, 0x3, SEEK_CUR);

        if (emb_verbose>1) {
            printf("number of bytes in color: %d\n", numberOfBytesInColor);
            printf("thread color number: %s\n", threadColorNumber);
            printf("offset to next color x: %d\n", offsetToNextColorX);
            printf("offset to next color y: %d\n", offsetToNextColorY);
            printf("color name: %s\n", colorName);
            printf("thread vendor: %s\n", threadVendor);
            printf("fileCommentString: %s\n", fileCommentString);
        }

        while (ftell(file) < colorSectionOffset - 1) {
            int lastFilePosition = ftell(file);
            int x = vp3Decode((char)fgetc(file));
            int y = vp3Decode((char)fgetc(file));
            short readIn;
            if (x == 0x80) {
                switch (y) {
                    case 0x00:
                    case 0x03:
                        break;
                    case 0x01: {
                        readIn = emb_read_i16be(file);
                        x = vp3DecodeInt16(readIn);
                        readIn = emb_read_i16be(file);
                        y = vp3DecodeInt16(readIn);
                        fseek(file, 2, SEEK_CUR);
                        emb_pattern_addStitchRel(pattern, x/ 10.0, y / 10.0, TRIM, 1);
                        break;
                    }
                    default:
                        break;
                }
            } else {
                emb_pattern_addStitchRel(pattern, x / 10.0, y / 10.0, NORMAL, 1);
            }

            if (ftell(file) == lastFilePosition) {
                printf("ERROR: format-vp3.c could not read stitch block in entirety\n");
                return 0;
            }
        }
        if (i + 1 < numberOfColors) {
            emb_pattern_addStitchRel(pattern, 0, 0, STOP, 1);
        }
    }
    emb_pattern_flipVertical(pattern);
    return 1;
}

void
vp3WriteStringLen(FILE* file, const char* str, int len)
{
    emb_write_u16be(file, len);
    fwrite(str, 1, len, file);
}

void
vp3WriteString(FILE* file, const char* str)
{
    vp3WriteStringLen(file, str, strlen(str));
}

void
vp3PatchByteCount(FILE* file, int offset, int adjustment)
{
    int currentPos = ftell(file);
    fseek(file, offset, SEEK_SET);
    printf("Patching byte count: %d\n", currentPos - offset + adjustment);
    emb_write_i32be(file, currentPos - offset + adjustment);
    fseek(file, currentPos, SEEK_SET);
}

char
writeVp3(EmbPattern* pattern, FILE* file)
{
    EmbRect bounds;
    int remainingBytesPos, remainingBytesPos2;
    int colorSectionStitchBytes, first = 1, i, numberOfColors;
    EmbColor color;
    color.r = 0xFE;
    color.g = 0xFE;
    color.b = 0xFE;

    bounds = emb_pattern_bounds(pattern);

    emb_pattern_correctForMaxStitchLength(pattern, 3200.0, 3200.0); /* VP3 can encode signed 16bit deltas */

    emb_pattern_flipVertical(pattern);

    fwrite("%vsm%\0", 1, 6, file);
    vp3WriteString(file, "Embroidermodder");
    fwrite("\x00\x02\x00", 1, 3, file);

    remainingBytesPos = ftell(file);
    emb_write_i32(file, 0); /* placeholder */
    vp3WriteString(file, "");
    emb_write_i32be(file, (bounds.x + bounds.w) * 1000);
    emb_write_i32be(file, (bounds.y + bounds.h) * 1000);
    emb_write_i32be(file, bounds.x * 1000);
    emb_write_i32be(file, bounds.y * 1000);
    emb_write_i32(file, 0); /* this would be some (unknown) function of thread length */
    fputc(0, file);

    numberOfColors = emb_pattern_color_count(pattern, color);
    fputc(numberOfColors, file);
    fwrite("\x0C\x00\x01\x00\x03\x00", 1, 6, file);

    remainingBytesPos2 = ftell(file);
    emb_write_i32(file, 0); /* placeholder */

    emb_write_i32be(file, 0); /* origin X */
    emb_write_i32be(file, 0); /* origin Y */
    fpad(file, 0, 3);

    emb_write_i32be(file, (bounds.x + bounds.w) * 1000);
    emb_write_i32be(file, (bounds.y + bounds.h) * 1000);
    emb_write_i32be(file, bounds.x * 1000);
    emb_write_i32be(file, bounds.y * 1000);

    emb_write_i32be(file, bounds.w * 1000);
    emb_write_i32be(file, bounds.h * 1000);

    vp3WriteString(file, "");
    emb_write_i16be(file, 25700);
    emb_write_i32be(file, 4096);
    emb_write_i32be(file, 0);
    emb_write_i32be(file, 0);
    emb_write_i32be(file, 4096);

    fwrite("xxPP\x01\0", 1, 6, file);
    vp3WriteString(file, "");
    emb_write_i16be(file, numberOfColors);

    for (i=0; i<pattern->stitch_list->count; i++) {
        char colorName[8] = { 0 };
        EmbReal lastX, lastY;
        int colorSectionLengthPos, j;
        EmbStitch s;
        int lastColor;

        j = 0;
        s.x = 0.0;
        s.y = 0.0;
        s.color = 0;
        s.flags = 0;

        if (!first) {
            fputc(0, file);
        }
        fputc(0, file);
        fputc(5, file);
        fputc(0, file);

        colorSectionLengthPos = ftell(file);
        emb_write_i32(file, 0); /* placeholder */

        /*
        pointer = mainPointer;
        color = pattern->thread_list->thread[pointer->stitch.color].color;

        if (first && pointer->stitch.flags & JUMP && pointer->next->stitch.flags & JUMP) {
            pointer = pointer->next;
        }

        s = pointer->stitch;
        */
        if (emb_verbose>1) {
            printf("%d\n", j);
            printf("format-vp3.c DEBUG %d, %f, %f\n", s.flags, s.x, s.y);
        }
        emb_write_i32be(file, s.x * 1000);
        emb_write_i32be(file, -s.y * 1000);
        /* pointer = pointer->next; */

        first = 0;

        lastX = s.x;
        lastY = s.y;
        lastColor = s.color;
        if (emb_verbose>1) {
            printf("last %f %f %d\n", lastX, lastY, lastColor);
        }

        fwrite("\x01\x00", 1, 2, file);

        printf("format-vp3.c writeVp3(), switching to color (%d, %d, %d)\n", color.r, color.g, color.b);
        embColor_write(file, color, 4);

        fwrite("\x00\x00\x05", 1, 3, file);
        fputc(40, file);

        vp3WriteString(file, "");

        sprintf(colorName, "#%02x%02x%02x", color.b, color.g, color.r);

        vp3WriteString(file, colorName);
        vp3WriteString(file, "");

        emb_write_i32be(file, 0);
        emb_write_i32be(file, 0);

        vp3WriteStringLen(file, "\0", 1);

        colorSectionStitchBytes = ftell(file);
        emb_write_i32(file, 0); /* placeholder */

        fputc(10, file);
        fputc(246, file);
        fputc(0, file);

        /*
        for (j=i; j<pattern->stitch_list->count; j++) {
        while (pointer) {
            short dx, dy;

            EmbStitch s = pointer->stitch;
            if (s.color != lastColor) {
                break;
            }
            if (s.flags & END || s.flags & STOP) {
                break;
            }
            dx = (s.x - lastX) * 10;
            dy = (s.y - lastY) * 10;
            // output is in ints, ensure rounding errors do not sum up.
            lastX = lastX + dx / 10.0;
            lastY = lastY + dy / 10.0;

            if (dx < -127 || dx > 127 || dy < -127 || dy > 127) {
                fputc(128, file);
                fputc(1, file);
                emb_write_i16be(file, dx);
                emb_write_i16be(file, dy);
                fputc(128, file);
                fputc(2, file);
            }
            else {
                char b[2];
                b[0] = dx;
                b[1] = dy;
                fwrite(b, 1, 2, file);
            }

            pointer = pointer->next;
        }
        */

        vp3PatchByteCount(file, colorSectionStitchBytes, -4);
        vp3PatchByteCount(file, colorSectionLengthPos, -3);

        /* mainPointer = pointer; */
    }

    vp3PatchByteCount(file, remainingBytesPos2, -4);
    vp3PatchByteCount(file, remainingBytesPos, -4);

    emb_pattern_flipVertical(pattern);
    return 0;
}

/*
 * Singer Embroidery Format (.xxx)
 * The Singer xxx format is stitch-only.
 */

char
xxxDecodeByte(unsigned char inputByte)
{
    if (inputByte >= 0x80) {
        return (char) ((-~inputByte) - 1);
    }
    return ((char) inputByte);
}

char
readXxx(EmbPattern* pattern, FILE* file)
{
    int dx = 0, dy = 0, numberOfColors, paletteOffset, i;
    char thisStitchJump = 0;

    if (emb_verbose>1) {
        puts("readXxx has been overridden.");
        return 0;
    }

    fseek(file, 0x27, SEEK_SET);
    numberOfColors = emb_read_i16(file);
    fseek(file, 0xFC, SEEK_SET);
    paletteOffset = emb_read_i32(file);
    fseek(file, paletteOffset + 6, SEEK_SET);

    for (i = 0; i < numberOfColors; i++) {
        EmbThread thread;
        strcpy(thread.catalogNumber, "NULL");
        strcpy(thread.description, "NULL");
        fseek(file, 1, SEEK_CUR);
        embColor_read(file, &(thread.color), 3);
        emb_pattern_addThread(pattern, thread);
    }
    fseek(file, 0x100, SEEK_SET);

    for (i = 0; !feof(file) && ftell(file) < paletteOffset; i++) {
        unsigned char b0, b1;
        int flags;
        flags = NORMAL;
        if (thisStitchJump) flags = TRIM;
        thisStitchJump = 0;
        b0 = (char)fgetc(file);
        b1 = (char)fgetc(file);
        /* TODO: ARE THERE OTHER BIG JUMP CODES? */
        if (b0 == 0x7E || b0 == 0x7D) {
            dx = b1 + ((char)fgetc(file) << 8);
            dx = ((int16_t) dx);
            dy = emb_read_i16(file);
            flags = TRIM;
        } else if (b0 == 0x7F) {
            /* TODO: LOOKS LIKE THESE CODES ARE IN THE HEADER */
            if (b1 != 0x17 && b1 != 0x46 && b1 >= 8) {
                b0 = 0;
                b1 = 0;
                thisStitchJump = 1;
                flags = STOP;
            } else if (b1 == 1) {
                flags = TRIM;
                b0 = (char)fgetc(file);
                b1 = (char)fgetc(file);
            } else {
                continue;
            }
            dx = xxxDecodeByte(b0);
            dy = xxxDecodeByte(b1);
        } else {
            dx = xxxDecodeByte(b0);
            dy = xxxDecodeByte(b1);
        }
        emb_pattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    /* TODO: check end of pattern for multiple STOPs */
    return 1;
}

void
xxxEncodeStop(FILE* file, EmbStitch s)
{
    fputc((unsigned char)0x7F, file);
    fputc((unsigned char)(s.color + 8), file);
}

void
xxxEncodeStitch(FILE* file, EmbReal deltaX, EmbReal deltaY, int flags)
{
    if ((flags & (JUMP | TRIM)) && (fabs(deltaX) > 124 || fabs(deltaY) > 124)) {
        fputc(0x7E, file);
        /* Does this cast work right? */
        emb_write_i16(file, (int16_t)deltaX);
        emb_write_i16(file, (int16_t)deltaY);
    } else {
        /* TODO: Verify this works after changing this to unsigned char */
        fputc((unsigned char)emb_round(deltaX), file);
        fputc((unsigned char)emb_round(deltaY), file);
    }
}

void
xxxEncodeDesign(FILE* file, EmbPattern* p)
{
    int i;
    EmbReal thisX = 0.0f;
    EmbReal thisY = 0.0f;

    if (p->stitch_list->count > 0) {
        thisX = (float)p->stitch_list->stitch[0].x;
        thisY = (float)p->stitch_list->stitch[0].y;
    }
    for (i = 0; i < p->stitch_list->count; i++) {
        EmbStitch s = p->stitch_list->stitch[i];
        EmbReal deltaX, deltaY;
        EmbReal previousX = thisX;
        EmbReal previousY = thisY;
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

char
writeXxx(EmbPattern* pattern, FILE* file)
{
    int i;
    EmbRect rect;
    int endOfStitches;
    EmbReal width, height;
    //short to_write;
    //unsigned int n_stitches;
    //unsigned short n_threads;

    emb_pattern_correctForMaxStitchLength(pattern, 124, 127);

    fpad(file, 0, 0x17);
    emb_write_i32(file, (unsigned int)pattern->stitch_list->count);

    fpad(file, 0, 0x0C);
    emb_write_i16(file, (unsigned short)pattern->thread_list->count);

    fpad(file, 0, 0x02);

    rect = emb_pattern_bounds(pattern);
    width = rect.w;
    height = rect.h;
    emb_write_i16(file, (int16_t)(width * 10.0));
    emb_write_i16(file, (int16_t)(height * 10.0));

    /* TODO: xEnd from start point x=0 */
    emb_write_i16(file, (int16_t)(width / 2.0 * 10));
    /* TODO: yEnd from start point y=0 */
    emb_write_i16(file, (int16_t)(height / 2.0 * 10));
    /* TODO: left from start x = 0 */
    emb_write_i16(file, (int16_t)(width / 2.0 * 10));
    /* TODO: bottom from start y = 0 */
    emb_write_i16(file, (int16_t)(height / 2.0 * 10));

    fpad(file, 0, 0xC5);

    /* place holder for end of stitches */
    emb_write_i32(file, 0x0000);
    xxxEncodeDesign(file, pattern);
    endOfStitches = ftell(file);
    fseek(file, 0xFC, SEEK_SET);
    emb_write_u32(file, endOfStitches);
    fseek(file, 0, SEEK_END);
    /* is this really correct? */
    fwrite("\x7F\x7F\x03\x14\x00\x00", 1, 6, file);

    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c = pattern->thread_list->thread[i].color;
        fputc(0x00, file);
        embColor_write(file, c, 3);
    }
    for (i = 0; i < (22 - pattern->thread_list->count); i++) {
        emb_write_u32(file, 0x01000000);
    }
    fwrite("\x00\x01", 1, 2, file);
    return 1;
}

/*
 * ZSK FORMAT
 *
 * The ZSK USA Embroidery Format (.zsk)
 * The ZSK USA zsk format is stitch-only.
 */

char
readZsk(EmbPattern* pattern, FILE* file)
{
    char b[3];
    unsigned char colorNumber;

    fseek(file, 0, SEEK_END);
    if (ftell(file) < 0x230) {
        return 0;
    }

    fseek(file, 0x230, SEEK_SET);
    colorNumber = fgetc(file);
    while (colorNumber != 0) {
        EmbThread t;
        embColor_read(file, &(t.color), 3);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        emb_pattern_addThread(pattern, t);
        fseek(file, 0x48, SEEK_CUR);
        colorNumber = fgetc(file);
    }
    fseek(file, 0x2E, SEEK_CUR);

    while (fread(b, 1, 3, file) == 3) {
        int stitchType = NORMAL;
        if (b[0] & 0x04) {
            b[2] = -b[2];
        }
        if (b[0] & 0x08) {
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
                /* TODO: need to determine what b[1] is used for.*/
                stitchType = STOP;
                emb_pattern_changeColor(pattern, colorNumber - 1);
            }
            b[1] = 0;
            b[2] = 0;
        }
        emb_pattern_addStitchRel(pattern, b[1] / 10.0,
            b[2] / 10.0, stitchType, 0);
    }

    return 1;
}

/* based on the readZsk function */
char
writeZsk(EmbPattern* pattern, FILE* file)
{
    int i;
    fpad(file, 0x00, 0x230);

    fprintf(file, "%c", pattern->thread_list->count);
    for (i=pattern->thread_list->count; i>0; i--) {
        EmbThread t = pattern->thread_list->thread[i-1];
        embColor_write(file, t.color, 3);
        fpad(file, 0x00, 0x48);
        fprintf(file, "%c", i-1);
    }

    fpad(file, 0x00, 0x2E);

    for (i=0; i<pattern->stitch_list->count; i++) {
        EmbStitch st;
        unsigned char b[3];
        st = pattern->stitch_list->stitch[i];
        b[0] = 0;
        b[1] = st.x;
        b[2] = st.y;
        if (st.flags & JUMP) {
            b[0] |= 0x02;
        }
        if (st.x < 0) {
            b[0] |= 0x08;
            b[1] = -st.x;
        }
        if (st.y < 0) {
            b[0] |= 0x04;
            b[2] = -st.y;
        }
        if (st.flags & TRIM) {
            b[0] |= 0x20;
            b[1] = 0x00;
            b[2] = 0x00;
        }
        if (st.flags & STOP) {
            b[0] |= 0x20;
            b[1] = 0x00;
            b[2] = st.color;
        }
        if (st.flags & END) {
            b[0] |= 0x20;
            b[1] = 0x80;
            b[2] = 0x00;
            fwrite(b, 1, 3, file);
            break;
        }
        fwrite(b, 1, 3, file);
    }
    return 1;
}


/*
 * Libembroidery 1.0.0-alpha
 * https://www.libembroidery.org
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright 2018-2025 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * -----------------------------------------------------------------------------
 *
 * Only uses source from this directory or standard C libraries,
 * not including POSIX headers like unistd since this library
 * needs to support non-POSIX systems like Windows.
 *
 * -----------------------------------------------------------------------------
 *
 * The Geometry System
 */

extern EmbReal epsilon;

const char *justify_options[] = {
    "Left",
    "Center",
    "Right",
    "Aligned",
    "Middle",
    "Fit",
    "Top Left",
    "Top Center",
    "Top Right",
    "Middle Left",
    "Middle Center",
    "Middle Right",
    "Bottom Left",
    "Bottom Center",
    "Bottom Right",
    END_SYMBOL
};

const char *emb_error_desc[] = {
    "No error.",
    "Wrong type: this is unsupported usage.",
    "Division by zero.",
    "Unfinished."
};

/* Create an EmbVector from data. */
EmbVector
emb_vector(EmbReal x, EmbReal y)
{
    EmbVector v;
    v.x = x;
    v.y = y;
    return v;
}

/* Finds the unit length vector a result in the same direction as a vector. */
EmbVector
emb_vector_normalize(EmbVector vector)
{
    EmbVector result;
    EmbReal length = emb_vector_length(vector);
    result.x = vector.x / length;
    result.y = vector.y / length;
    return result;
}

/* The scalar multiple a magnitude of a vector. Returned as a vector. */
EmbVector
emb_vector_scale(EmbVector vector, EmbReal magnitude)
{
    EmbVector result;
    result.x = vector.x * magnitude;
    result.y = vector.y * magnitude;
    return result;
}

/* The sum of two vectors returned as a vector. */
EmbVector
emb_vector_add(EmbVector a, EmbVector b)
{
    EmbVector result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

/* The average of two vectors returned as a vector. */
EmbVector
emb_vector_average(EmbVector a, EmbVector b)
{
    EmbVector result;
    result.x = 0.5*(a.x + b.x);
    result.y = 0.5*(a.y + b.y);
    return result;
}

/* The difference between two vectors returned as a result. */
EmbVector
emb_vector_subtract(EmbVector v1, EmbVector v2)
{
    EmbVector result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    return result;
}

/* The dot product of two vectors returned as a EmbReal. */
EmbReal
emb_vector_dot(EmbVector a, EmbVector b)
{
    return a.x * b.x + a.y * b.y;
}

/*
 * The "cross product" as vectors a and b returned as a real value.
 *
 * Technically, this is the magnitude of the cross product when the
 * embroidery is placed in the z=0 plane (since the cross product is defined for
 * 3-dimensional vectors).
 */
EmbReal
emb_vector_cross(EmbVector a, EmbVector b)
{
    return a.x * b.y - a.y * b.x;
}

/*
 * Since we aren't using full 3D vector algebra here, all vectors are "vertical".
 * so this is like the product v1^{T} I_{2} v2 for our vectors a v1 and v2
 * so a "component-wise product". The result is stored at the pointer a result.
 */
EmbVector
emb_vector_transpose_product(EmbVector v1, EmbVector v2)
{
    EmbVector result;
    result.x = v1.x * v2.x;
    result.y = v1.y * v2.y;
    return result;
}

/* The length or absolute value of the vector a vector. */
EmbReal
emb_vector_length(EmbVector vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

/* The x-component of the vector. */
EmbReal
emb_vector_relativeX(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    b = emb_vector_subtract(a1, a2);
    c = emb_vector_subtract(a3, a2);
    return emb_vector_dot(b, c);
}

/* The y-component of the vector. */
EmbReal
emb_vector_relativeY(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    b = emb_vector_subtract(a1, a2);
    c = emb_vector_subtract(a3, a2);
    return emb_vector_cross(b, c);
}

/* The angle, measured anti-clockwise from the x-axis, of a vector v. */
EmbReal
emb_vector_angle(EmbVector v)
{
    return atan2(v.y, v.x);
}

/* The unit vector in the direction a angle. */
EmbVector
emb_vector_unit(EmbReal alpha)
{
    EmbVector a;
    a.x = cos(alpha);
    a.y = sin(alpha);
    return a;
}

/* The distance between vectors "a" and "b" returned as a real value. */
EmbReal
emb_vector_distance(EmbVector a, EmbVector b)
{
    EmbVector delta = emb_vector_subtract(a, b);
    return emb_vector_length(delta);
}

/* Translate a geometric object by the vector "delta". */
void
emb_geometry_move(EmbGeometry *obj, EmbVector delta)
{
    switch (obj->type) {
    case EMB_ARC: {
        EmbArc *arc = &(obj->object.arc);
        arc->start = emb_vector_add(arc->start, delta);
        arc->mid = emb_vector_add(arc->mid, delta);
        arc->end = emb_vector_add(arc->end, delta);
        return;
    }
    case EMB_CIRCLE: {
        EmbCircle *circle = &(obj->object.circle);
        circle->center = emb_vector_add(circle->center, delta);
        return;
    }
    default:
        break;
    }
}

/* Approximate equals for vectors. */
int
emb_approx(EmbVector point1, EmbVector point2)
{
    return (emb_vector_distance(point1, point2) < epsilon);
}

/* . */
EmbReal
emb_apothem(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    case EMB_ARC: {
        *error = EMB_NO_ERR;
        EmbReal radius = emb_radius(g, error);
        if (*error) {
            return 0.0;
        }
        EmbReal sagitta = emb_sagitta(g, error);
        if (*error) {
            return 0.0;
        }
        return fabs(radius - sagitta);
    }
    default:
        *error = EMB_WRONG_TYPE_ERR;
        break;
    }
    return 0.0;
}

/* FIXME */
EmbReal
emb_sagitta(EmbGeometry *g, EmbError *error)
{
   *error = EMB_UNFINISHED_ERR;
   return 0.0;
}

/* FIXME */
EmbVector
emb_start(EmbGeometry *g, EmbError *error)
{
   *error = EMB_UNFINISHED_ERR;
   return emb_vector(0.0, 0.0);
}

/* FIXME */
EmbVector
emb_end(EmbGeometry *g, EmbError *error)
{
   *error = EMB_UNFINISHED_ERR;
   return emb_vector(0.0, 0.0);
}

/* FIXME */
EmbReal
emb_width(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    switch (g->type) {
    case EMB_CIRCLE: {
        return 2.0f * g->object.circle.radius;
    }
    case EMB_ELLIPSE: {
        return 2.0f * g->object.ellipse.radius.x;
    }
    default:
        *error = EMB_WRONG_TYPE_ERR;
        break;
    }
    return 1.0;
}

/* FIXME: finish all types. */
EmbReal
emb_height(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    switch (g->type) {
    case EMB_CIRCLE: {
        return 2.0f * g->object.circle.radius;
    }
    case EMB_ELLIPSE: {
        return 2.0f * g->object.ellipse.radius.y;
    }
    default:
        *error = EMB_WRONG_TYPE_ERR;
        break;
    }
    return 1.0;
}

/* FIXME: finish all types. */
EmbReal
emb_radius(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    switch (g->type) {
    case EMB_ARC: {
        EmbReal incAngle = emb_included_angle(g, error);
        EmbReal chord = emb_vector_length(emb_chord(g, error));
        return fabs(chord / (2.0 * sin(incAngle / 2.0)));
    }
    default:
        *error = EMB_WRONG_TYPE_ERR;
        break;
    }
    return 1.0;
}

/* FIXME */
EmbReal
emb_radius_major(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    switch (g->type) {
    default:
        *error = EMB_WRONG_TYPE_ERR;
        break;
    }
    return 1.0;
}

/* FIXME */
EmbReal
emb_radius_minor(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    switch (g->type) {
    default:
        break;
    }
    return 1.0;
}

/* FIXME */
EmbReal
emb_diameter_major(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    switch (g->type) {
    default:
        break;
    }
    return 1.0;
}

/* FIXME */
EmbReal
emb_diameter_minor(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    default:
        break;
    }
    return 1.0;
}

/* FIXME */
EmbReal
emb_diameter(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    default:
        break;
    }
    return 1.0;
}

/* . */
EmbVector
emb_quadrant(EmbGeometry *geometry, int degrees, EmbError *error)
{
    EmbVector v;
    EmbReal radius = 1.0;
    v.x = 0.0;
    v.y = 0.0;
    switch (geometry->type) {
    case EMB_CIRCLE: {
        v = geometry->object.circle.center;
        radius = geometry->object.circle.radius;
        break;
    }
    case EMB_ELLIPSE: {
        v = geometry->object.ellipse.center;
        if (degrees % 180 == 0) {
            radius = geometry->object.ellipse.radius.x;
        }
        else {
            radius = geometry->object.ellipse.radius.y;
        }
        break;
    }
    default:
        break;
    }
    EmbReal rot = radians(/* rotation() + */ degrees);
    v.x += radius * cos(rot);
    v.y += radius * sin(rot);
    return v;
}

/* . */
EmbReal
emb_angle(EmbGeometry *geometry, EmbError *error)
{
    EmbVector v = emb_vector_subtract(geometry->object.line.end, geometry->object.line.start);
    EmbReal angle = emb_vector_angle(v) /* - rotation() */;
    return fmod(angle+360.0, 360.0);
}

/* . */
EmbReal
emb_start_angle(EmbGeometry *geometry, EmbError *error)
{
    switch (geometry->type) {
    case EMB_ARC: {
        *error = EMB_NO_ERR;
        EmbVector center = emb_center(geometry, error);
        if (*error) {
            return 0.0;
        }
        EmbVector v = emb_vector_subtract(center, geometry->object.arc.start);
        EmbReal angle = emb_vector_angle(v) /* - rotation() */;
        return fmod(angle+360.0, 360.0);
    }
    default:
        break;
    }
    return 0.0f;
}

/* . */
EmbReal
emb_end_angle(EmbGeometry *geometry, EmbError *error)
{
    switch (geometry->type) {
    case EMB_ARC: {
        *error = EMB_NO_ERR;
        EmbVector center = emb_center(geometry, error);
        if (*error) {
            return 0.0;
        }
        EmbVector v = emb_vector_subtract(center, geometry->object.arc.end);
        EmbReal angle = emb_vector_angle(v) /* - rotation() */;
        return fmod(angle+360.0, 360.0);
    }
    default:
        break;
    }
    return 0.0f;
}

/* . */
EmbReal
emb_arc_length(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    case EMB_ARC: {
        *error = EMB_NO_ERR;
        EmbReal radius = emb_radius(g, error);
        if (*error) {
            return 0.0;
        }
        EmbReal angle = emb_included_angle(g, error);
        if (*error) {
            return 0.0;
        }
        return radians(angle) * radius;
    }
    default:
        break;
    }
    return 0.0;
}

/* . */
EmbReal
emb_area(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    case EMB_ARC: {
        /* Area of a circular segment */
        *error = EMB_NO_ERR;
        EmbReal r = emb_radius(g, error);
        if (*error) {
            return 0.0;
        }
        EmbReal theta = emb_included_angle(g, error);
        if (*error) {
            return 0.0;
        }
        theta = radians(theta);
        return ((r*r)/2) * (theta - sin(theta));
    }
    case EMB_CIRCLE: {
        EmbReal r = g->object.circle.radius;
        return embConstantPi * r * r;
    }
    case EMB_RECT:
        return g->object.rect.w * g->object.rect.h;
    case EMB_IMAGE:
    default:
        break;
    }
    /* The area of most objects defaults to the area of the rectangle described by the
     * object's width and height.
     */
    EmbReal width = emb_width(g, error);
    if (*error) {
        return 0.0;
    }
    EmbReal height = emb_height(g, error);
    if (*error) {
        return 0.0;
    }
    return fabs(width * height);
}

/* FIXME */
EmbVector
emb_center(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    case EMB_ARC: {
/* FIXME: Calculates the CenterPoint of the Arc */

    #if 0
    EmbArc arc = g.object.arc;
    int emb_error = 0;
    EmbVector center;
    EmbVector a_vec, b_vec, aMid_vec, bMid_vec, aPerp_vec, bPerp_vec, pa, pb;
    EmbLine line1, line2;
    EmbReal paAngleInRadians, pbAngleInRadians;
    a_vec = emb_vector_subtract(arc.mid, arc.start);
    aMid_vec = emb_vector_average(arc.mid, arc.start);

    paAngleInRadians = emb_vector_angle(a_vec) + (embConstantPi/2.0);
    pa = emb_vector_unit(paAngleInRadians);
    aPerp_vec = emb_vector_add(aMid_vec, pa);

    b_vec = emb_vector_subtract(arc.end, arc.mid);
    bMid_vec = emb_vector_average(arc.end, arc.mid);

    pbAngleInRadians = emb_vector_angle(b_vec) + (embConstantPi/2.0);
    pb = emb_vector_unit(pbAngleInRadians);
    bPerp_vec = emb_vector_add(bMid_vec, pb);

    line1.start = aMid_vec;
    line1.end = aPerp_vec;
    line2.start = bMid_vec;
    line2.end = bPerp_vec;
    center = emb_line_intersectionPoint(line1, line2, &emb_error);
        if (emb_error) {
            puts("ERROR: no intersection, cannot find arcCenter.");
        }
        return center;
    #endif
        *error = EMB_UNFINISHED_ERR;
        break;
    }
    default:
        *error = EMB_WRONG_TYPE_ERR;
        break;
    }
    return emb_vector(0.0, 0.0);
}

/* . */
EmbVector
emb_chord(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    case EMB_ARC:
    case EMB_LINE:
    case EMB_PATH:
    case EMB_POLYLINE: {
        *error = EMB_NO_ERR;
        EmbVector start = emb_start(g, error);
        if (*error) {
            return emb_vector(0.0, 0.0);
        }
        EmbVector end = emb_end(g, error);
        if (*error) {
            return emb_vector(0.0, 0.0);
        }
        return emb_vector_subtract(end, start);
    }
    default:
        *error = EMB_WRONG_TYPE_ERR;
        break;
    }
    return emb_vector(0.0, 0.0);
}

/* . */
EmbReal
emb_included_angle(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    case EMB_ARC: {
        /* Properties of a Circle - Get the Included Angle - Reference: ASD9 */
        *error = EMB_NO_ERR;
        EmbReal chord = emb_chord_length(g, error);
        if (*error) {
            return 0.0;
        }
        EmbReal rad = emb_radius(g, error);
        if (*error) {
            return 0.0;
        }
        if (chord <= 0 || rad <= 0) {
            /* Prevents division by zero and non-existant circles. */
            *error = EMB_DIV_ZERO_ERR;
            return 0.0;
        }

        /* NOTE: Due to floating point rounding errors, we need to clamp the
         * quotient so it is in the range [-1, 1]
         * If the quotient is out of that range, then the result of asin()
         * will be NaN.
         */
        EmbReal quotient = chord/(2.0*rad);
        quotient = EMB_MIN(1.0, quotient);
        /* NOTE: 0 rather than -1 since we are enforcing a positive chord and
         * radius
         */
        quotient = EMB_MAX(0.0, quotient);

        return degrees(2.0*asin(quotient));
    }
    default:
        break;
    }
    return 0.0;
}

/* . */
char
emb_clockwise(EmbGeometry *geometry, EmbError *error)
{
    switch (geometry->type) {
    case EMB_ARC: {
        /* NOTE: Y values are inverted here on purpose. */
        geometry->object.arc.start.y = -geometry->object.arc.start.y;
        geometry->object.arc.mid.y = -geometry->object.arc.start.y;
        geometry->object.arc.end.y = -geometry->object.arc.end.y;
        return emb_arc_clockwise(*geometry);
    }
    default:
        break;
    }
    return 0;
}

/* . */
EmbError
emb_set_start_angle(EmbGeometry *geometry, EmbReal angle)
{
    printf("%f\n", angle);
    switch (geometry->type) {
    case EMB_ARC: {
        /* TODO: ArcObject setObjectStartAngle */
        break;
    }
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
EmbError
emb_set_end_angle(EmbGeometry *geometry, EmbReal angle)
{
    printf("%f\n", angle);
    switch (geometry->type) {
    case EMB_ARC: {
        /* TODO: ArcObject setObjectEndAngle */
        break;
    }
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
EmbError
emb_set_start_point(EmbGeometry *geometry, EmbVector point)
{
    switch (geometry->type) {
    case EMB_ARC: {
        geometry->object.arc.start = point;
        /* calculateData(); */
        break;
    }
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
EmbError
emb_set_mid_point(EmbGeometry *geometry, EmbVector point)
{
    switch (geometry->type) {
    case EMB_ARC: {
        geometry->object.arc.mid = point;
        /* calculateData(); */
        break;
    }
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
EmbError
emb_set_end_point(EmbGeometry *geometry, EmbVector point)
{
    switch (geometry->type) {
    case EMB_ARC: {
        geometry->object.arc.end = point;
        /* calculateData(); */
        break;
    }
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
EmbError
emb_set_radius(EmbGeometry *g, EmbReal radius)
{
    switch (g->type) {
    case EMB_ARC: {
        EmbVector delta;
        float rad;
        if (radius <= 0.0f) {
            rad = 0.0000001f;
        }
        else {
            rad = radius;
        }

        EmbError error = EMB_NO_ERR;
        EmbVector center = emb_center(g, &error);
        if (error) {
            return error;
        }
        EmbReal delta_length;

        delta = emb_vector_subtract(g->object.arc.start, center);
        delta_length = emb_vector_length(delta);
        delta = emb_vector_scale(delta, rad/delta_length);
        g->object.arc.start = emb_vector_add(center, delta);

        delta = emb_vector_subtract(g->object.arc.mid, center);
        delta_length = emb_vector_length(delta);
        delta = emb_vector_scale(delta, rad/delta_length);
        g->object.arc.mid = emb_vector_add(center, delta);

        delta = emb_vector_subtract(g->object.arc.end, center);
        delta_length = emb_vector_length(delta);
        delta = emb_vector_scale(delta, rad/delta_length);
        g->object.arc.end = emb_vector_add(center, delta);
        return EMB_NO_ERR;
    }
    case EMB_CIRCLE:
        g->object.circle.radius = radius;
        return EMB_NO_ERR;
    default:
        break;
    }
    return EMB_WRONG_TYPE_ERR;
}

/* . */
EmbError
emb_set_diameter(EmbGeometry *geometry, EmbReal diameter)
{
    switch (geometry->type) {
    case EMB_CIRCLE: {
        geometry->object.circle.radius = diameter / 2.0;
        /* FIXME: updatePath(); */
        break;
    }
    default:
        break;
    }
    return EMB_NO_ERR;
}

/*
 * Sets the area of the geometry if that is meaningful, otherwise
 * return EMB_WRONG_TYPE_ERR.
 */
EmbError
emb_set_area(EmbGeometry *geometry, EmbReal area)
{
    switch (geometry->type) {
    case EMB_CIRCLE: {
        EmbReal radius = sqrt(area / embConstantPi);
        emb_set_radius(geometry, radius);
        return EMB_NO_ERR;
    }
    default:
        break;
    }
    return EMB_WRONG_TYPE_ERR;
}

/*
 * Sets the circumference of the geometry if that is meaningful, otherwise
 * return EMB_WRONG_TYPE_ERR.
 */
EmbError
emb_set_circumference(EmbGeometry *geometry, EmbReal circumference)
{
    switch (geometry->type) {
    case EMB_CIRCLE: {
        EmbReal diameter = circumference / embConstantPi;
        emb_set_diameter(geometry, diameter);
        return EMB_NO_ERR;
    }
    default:
        break;
    }
    return EMB_WRONG_TYPE_ERR;
}

/* . */
EmbError
emb_set_radius_major(EmbGeometry *geometry, EmbReal radius)
{
    emb_set_diameter_major(geometry, radius*2.0);
    return EMB_NO_ERR;
}

/* . */
EmbError
emb_set_radius_minor(EmbGeometry *geometry, EmbReal radius)
{
    emb_set_diameter_minor(geometry, radius*2.0);
    return EMB_NO_ERR;
}

/* . */
EmbError
emb_set_diameter_major(EmbGeometry *geometry, EmbReal diameter)
{
    switch (geometry->type) {
    case EMB_ELLIPSE:
        /* FIXME: Identify longer axis and replace. */
        geometry->object.ellipse.radius.x = diameter;
        break;
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
EmbError
emb_set_diameter_minor(EmbGeometry *geometry, EmbReal diameter)
{
    switch (geometry->type) {
    case EMB_ELLIPSE:
        /* FIXME: Identify longer axis and replace. */
        geometry->object.ellipse.radius.x = diameter;
        break;
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
void
emb_geometry_path(EmbGeometry *geometry, char *path, EmbError *error)
{
}

#if 0
/* . */
QColor
emb_color(EmbGeometry *geometry)
{
    return data.objPen.color();
}

/* . */
QRgb
emb_color_rgb(EmbGeometry *geometry)
{
    return data.objPen.color().rgb();
}

/* . */
Qt::PenStyle
emb_line_type(EmbGeometry *geometry)
{
    return data.objPen.style();
}

/* . */
EmbReal
emb_line_weight(EmbGeometry *geometry)
{
    return data.lwtPen.widthF();
}

/* . */
EmbVector
emb_rubber_point(EmbGeometry *geometry, const char *key)
{
    return ;
}

/* . */
QString
emb_rubber_text(EmbGeometry *geometry, const char *key)
{
    return ;
}

/* . */
EmbVector
emb_pos(EmbGeometry *geometry)
{
    return scenePos();
}

/* . */
EmbReal
emb_x(EmbGeometry *geometry)
{
    return scenePos().x();
}

/* . */
EmbReal
emb_y(EmbGeometry *geometry)
{
    return scenePos().y();
}

/* . */
EmbVector
emb_center(EmbGeometry *geometry)
{
    return ;
}

/* . */
EmbReal
emb_center_x(EmbGeometry *geometry)
{
    return scenePos().x();
}

/* . */
EmbReal
emb_center_y(EmbGeometry *geometry)
{
    return scenePos().y();
}

/* . */
EmbReal
emb_radius(EmbGeometry *geometry)
{
    return rect().width()/2.0*scale();
}

/* . */
EmbReal
emb_diameter(EmbGeometry *geometry)
{
    return rect().width()*scale();
}
#endif

/* . */
EmbReal
emb_circumference(EmbGeometry *geometry, EmbError *error)
{
    switch (geometry->type) {
    case EMB_CIRCLE: {
        return 2.0 * embConstantPi * geometry->object.circle.radius;
    }
    default:
        break;
    }
    return 1.0;
}

#if 0
/* . */
EmbVector
emb_end_point_1(EmbGeometry *geometry)
{
    return emb_pos(geometry);
}

/* . */
EmbVector
emb_end_point_2(EmbGeometry *geometry)
{
    return emb_pos(geometry);
}

/* . */
EmbVector
emb_start_point(EmbGeometry *geometry)
{
    return ;
}

/* . */
EmbVector
emb_mid_point(EmbGeometry *geometry)
{
    return ;
}

/* . */
EmbVector
emb_end_point(EmbGeometry *geometry)
{
    return ;
}

/* . */
EmbVector
emb_delta(EmbGeometry *geometry)
{
    return objectEndPoint2(geometry) - objectEndPoint1(geometry);
}

/* . */
EmbVector
top_left(EmbGeometry *geometry)
{
}

/* . */
EmbVector
top_right(EmbGeometry *geometry)
{
}

/* . */
EmbVector
bottom_left(EmbGeometry *geometry)
{
}

/* . */
EmbVector
bottom_right(EmbGeometry *geometry)
{
}

/* . */
void
update_rubber(QPainter* painter);
{
}

/* . */
void
update_rubber_grip(QPainter *painter);
{
}

/* . */
void
update_leader(EmbGeometry *geometry);
{
}

/* . */
void
update_path(EmbGeometry *geometry);
{
}

/* . */
void
update_path(const QPainterPath& p);
{
}

/* . */
void
update_arc_rect(EmbReal radius);
{
}

/* . */
EmbReal
emb_length(EmbGeometry *geometry)
{
    return line().length()*scale();
}

/* . */
void
emb_set_end_point_1(EmbGeometry *geometry, const QPointF& endPt1)
{
}

/* . */
void
emb_set_end_point_1(EmbGeometry *geometry, EmbReal x1, EmbReal y1)
{
}

/* . */
void
emb_set_end_point_2(EmbGeometry *geometry, QPointF endPt2)
{
}

/* . */
void
emb_set_end_point_2(EmbGeometry *geometry, EmbReal x2, EmbReal y2)
{
}

/* . */
void
emb_set_x1(EmbReal x)
{
    emb_set_EndPoint1(x, objectEndPoint1().y());
}

/* . */
void
emb_set_y1(EmbReal y)
{
    emb_set_EndPoint1(objectEndPoint1().x(), y);
}

/* . */
void
emb_set_x2(EmbReal x)
{
    emb_set_EndPoint2(x, objectEndPoint2().y());
}

/* . */
void
emb_set_y2(EmbReal y)
{
    emb_set_EndPoint2(objectEndPoint2().x(), y);
}

/* . */
QRectF
emb_rect(EmbGeometry *geometry)
{
    return path().boundingRect();
}

/* . */
void
emb_setRect(const QRectF& r)
{
    QPainterPath p;
    p.addRect(r);
    setPath(p);
}

/* . */
void
emb_setRect(EmbReal x, EmbReal y, EmbReal w, EmbReal h)
{
    QPainterPath p;
    p.addRect(x,y,w,h);
    setPath(p);
}

/* . */
QLineF line(EmbGeometry *geometry)
{
    return data.objLine;
}

/* . */
void
emb_setLine(const QLineF& li)
{
    QPainterPath p;
    p.moveTo(li.p1());
    p.lineTo(li.p2());
    setPath(p);
    data.objLine = li;
}

/* . */
void
emb_set_line(EmbReal x1, EmbReal y1, EmbReal x2, EmbReal y2)
{
    QPainterPath p;
    p.moveTo(x1, y1);
    p.lineTo(x2, y2);
    setPath(p);
    data.objLine.setLine(x1,y1,x2,y2);
}

/* . */
void
emb_set_pos(QPointF point)
{
    setPos(point.x(), point.y());
}

/* . */
void
emb_set_pos(EmbGeometry *geometry, EmbReal x, EmbReal y)
{
    setPos(x, y);
}

/* . */
void
emb_set_x(EmbGeometry *geometry, EmbReal x)
{
    emb_set_pos(geometry, x, emb_y(geometry));
}

/* . */
void
emb_set_y(EmbGeometry *geometry, EmbReal y)
{
    emb_set_pos(geometry, emb_x(geometry), y);
}

/* . */
void emb_set_Rect(EmbReal x1, EmbReal y1, EmbReal x2, EmbReal y2)
{
}

/* . */
virtual QRectF boundingRect(EmbGeometry *geometry)
{
}

/* . */
virtual QPainterPath shape(EmbGeometry *geometry)
{ return path(); }

/* . */
void
emb_set_Color(const QColor& color)
{
}

/* . */
void
emb_set_ColorRGB(QRgb rgb)
{
}

/* . */
void
emb_set_LineType(Qt::PenStyle lineType)
{
}

/* . */
void
emb_set_LineWeight(EmbReal lineWeight)
{
}

/* . */
void
emb_set_Path(const QPainterPath& p)
{
    setPath(p);
}

/* . */
void
emb_set_rubber_mode(int mode)
{
    data.objRubberMode = mode;
}

/* . */
void
emb_set_rubber_point(const QString& key, const QPointF& point)
{
    data.objRubberPoints.insert(key, point);
}

/* . */
void
emb_set_rubber_text(const QString& key, const QString& txt)
{
    data.objRubberTexts.insert(key, txt);
}

/* . */
void
draw_rubber_line(const QLineF& rubLine, QPainter* painter = 0, const char* colorFromScene = 0)
{
}

/* . */
QPen
lineWeightPen(EmbGeometry *geometry)
{
    return data.lwtPen;
}

/* . */
void emb_real_render(QPainter* painter, const QPainterPath& renderPath)
{
}

/* . */
void
emb_set_center(EmbVector point)
{
}

/* . */
void
emb_set_center(const QPointF& center)
{
}

/* . */
void
emb_set_center_x(EmbGeometry *geometry, EmbReal centerX)
{
}

/* . */
void
emb_set_center_y(EmbGeometry *geometry, EmbReal centerY)
{
}

/* . */
void
emb_calculate_data(EmbGeometry *geometry)
{
}

/* . */
void
emb_set_size(EmbGeometry *geometry, EmbReal width, EmbReal height)
{
}

/* . */
QPainterPath
emb_object_copy_path(EmbGeometry *geometry)
{
}

/* . */
QPainterPath
emb_object_save_path(EmbGeometry *geometry)
{
}

/* . */
QList<QPainterPath>
emb_object_save_path_list(EmbGeometry *geometry)
{
    return subPathList();
}

/* . */
QList<QPainterPath>
emb_sub_path_list(EmbGeometry *geometry)
{
    return;
}

#endif

/* Our generic object interface backends to each individual type.
 * The caller defines what the type is.
 */
EmbGeometry *
emb_init(int type_in)
{
    EmbGeometry *obj = (EmbGeometry*)malloc(sizeof(EmbGeometry));
    obj->type = type_in;
    obj->color.r = 0;
    obj->color.g = 0;
    obj->color.b = 0;

    /*
    // QGraphicsItem* parent
    debug_message("BaseObject Constructor()");

    objPen.setCapStyle(RoundCap);
    objPen.setJoinStyle(RoundJoin);
    lwtPen.setCapStyle(RoundCap);
    lwtPen.setJoinStyle(RoundJoin);

    objID = QDateTime::currentMSecsSinceEpoch();
    */

    switch (obj->type) {
    case EMB_ARC: {
        /*
        obj = emb_arc(1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
        emb_arc_init(EmbArc arc_in, unsigned int rgb, int lineType)
        arc = arc_in;

        setFlag(ItemIsSelectable, true);

        calculateArcData(arc);

        setColor(rgb);
        setLineType(lineType);
        setLineWeight(0.35); //TODO: pass in proper lineweight
        setPen(objPen);
        */
        break;
    }
    }
    return obj;
}

/* Free the memory occupied by a non-stitch geometry object.
 *
 * Pointer to geometry memory.
 */
void
emb_free(EmbGeometry *obj)
{
    switch (obj->type) {
    case EMB_ARC: {
        return;
    }
    case EMB_CIRCLE: {
        return;
    }
    case EMB_ELLIPSE: {
        return;
    }
    default:
        return;
    }
}

/* Calculate the bounding box of geometry a obj based on what kind of
 * geometric object it is.
 *
 * obj A pointer to the geometry memory.
 * Returns an EmbRect, the bounding box in the same scale as the input geometry.
 *
 * In the case of a failure the bounding box returned is always the unit square
 * with top left corner at (0, 0).
 */
EmbRect
emb_boundingRect(EmbGeometry *obj)
{
    EmbRect r;
    if (obj->type == EMB_ARC) {
        /*
        arcRect.setWidth(radius*2.0);
        arcRect.setHeight(radius*2.0);
        arcRect.moveCenter(EmbVector(0,0));
        setRect(arcRect);
        */
    }
    r.y = 0.0;
    r.x = 0.0;
    r.w = 1.0;
    r.h = 1.0;
    /*
    "Base"
    //If gripped, force this object to be drawn even if it is offscreen
    if (objectRubberMode() == OBJ_RUBBER_GRIP)
        return scene()->sceneRect();
    return path().boundingRect();
    */
    return r;
}

/*
 * Create an arc from data.
 *
 * ------------------------------------------------------------
 *
 * The EmbArc is implicitly an elliptical arc not a circular one
 * because of our need to cover all of the SVG spec. Note that
 * the circlar arcs are a subset of the elliptical arcs.
 *
 * TODO: some of these formulae may assume that the arc is circular,
 * correct for elliptic versions.
 *
 * Returns an EmbGeometry. It is created on the stack.
 *
 * Note that the default arc is the semicircular arc of the circle of radius
 * arc.
 */
EmbGeometry
emb_arc(EmbReal x1, EmbReal y1, EmbReal x2, EmbReal y2, EmbReal x3, EmbReal y3)
{
    EmbGeometry g;
    g.object.arc.start = emb_vector(x1, y1);
    g.object.arc.mid = emb_vector(x2, y2);
    g.object.arc.end = emb_vector(x3, y3);
    g.type = EMB_ARC;
    return g;
}

/* Calculus based approach at determining whether a polygon is clockwise or counterclockwise.
 * Returns true if arc is clockwise.
 */
char
emb_arc_clockwise(EmbGeometry g)
{
    if (g.type != EMB_ARC) {
        return 0;
    }
    EmbArc arc = g.object.arc;
    EmbReal edge1 = (arc.mid.x-arc.start.x) * (arc.mid.y+arc.start.y);
    EmbReal edge2 = (arc.end.x-arc.mid.x) * (arc.end.y+arc.mid.y);
    EmbReal edge3 = (arc.start.x-arc.end.x) * (arc.start.y+arc.end.y);
    if (edge1 + edge2 + edge3 >= 0.0) {
        return 1;
    }
    return 0;
}

/* Calculates Arc Geometry from Bulge Data.
 * Returns false if there was an error calculating the data.
    Calculate the Sagitta Angle (from chordMid to arcMid)
    if (*clockwise) sagittaAngleInRadians = chordAngleInRadians + radians(90.0);
    else           sagittaAngleInRadians = chordAngleInRadians - radians(90.0);

    Calculate the Arc MidPoint
    fx = emb_arc_sagitta(arc) * cos(sagittaAngleInRadians);
    fy = emb_arc_sagitta(arc) * sin(sagittaAngleInRadians);
    arc->mid.x = *chordMidX + fx;
    arc->mid.y = *chordMidY + fy;

    Convert the Included Angle from Radians to Degrees
    *incAngleInDegrees = degrees(incAngleInRadians);

    return 1;
}
 */

EmbError
emb_set_center(EmbGeometry *g, EmbVector point)
{
    switch (g->type) {
    case EMB_ARC: {
        EmbError error = EMB_NO_ERR;
        EmbVector delta;
        EmbVector old_center = emb_center(g, &error);
        delta = emb_vector_subtract(point, old_center);
        g->object.arc.start = emb_vector_add(g->object.arc.start, delta);
        g->object.arc.mid = emb_vector_add(g->object.arc.mid, delta);
        g->object.arc.end = emb_vector_add(g->object.arc.end, delta);
        break;
    }
    default:
        break;
    }
    return EMB_NO_ERR;
}

void
emb_set_color(EmbGeometry *obj, EmbColor color)
{
    obj->color = color;
    /*
    objPen.setColor(color);
    lwtPen.setColor(color);
    */
}

void
emb_set_color_rgb(EmbGeometry *obj, unsigned int rgb)
{
    printf("%p", obj);
    printf("%d", rgb);
    /*
    objPen.setColor(QColor(rgb));
    lwtPen.setColor(QColor(rgb));
    */
}

void
emb_set_linetype(EmbGeometry *obj, int lineType)
{
    printf("%p %d\n", obj, lineType);
    /*
    objPen.setStyle(lineType);
    lwtPen.setStyle(lineType);
    */
}

void
emb_set_line_weight(EmbGeometry *obj, float lineWeight)
{
    printf("%p %f\n", obj, lineWeight);
    /*
    objPen.setWidthF(0); //NOTE: The objPen will always be cosmetic

    if (lineWeight < 0) {
        if (lineWeight == OBJ_LWT_BYLAYER) {
            lwtPen.setWidthF(0.35); //TODO: getLayerLineWeight
        }
        else if (lineWeight == OBJ_LWT_BYBLOCK) {
            lwtPen.setWidthF(0.35); //TODO: getBlockLineWeight
        }
        else {
            QMessageBox::warning(0, translate("Error - Negative Lineweight"),
                                    translate("Lineweight: %1")
                                    .arg(std::string().setNum(lineWeight)));
            debug_message("Lineweight cannot be negative! Inverting sign.");
            lwtPen.setWidthF(-lineWeight);
        }
    }
    else {
        lwtPen.setWidthF(lineWeight);
    }
    */
}

EmbVector
emb_base_rubber_point(EmbGeometry *obj, const char *key)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    printf("%p %s\n", obj, key);
    /*
    if (objRubberPoints.contains(key)) {
        return objRubberPoints.value(key);
    }

    QGraphicsScene* gscene = scene();
    if (gscene) {
        return scene()->attribute("SCENE_QSNAP_POINT").toPointF();
    }
    */
    return v;
}

const char *
emb_base_rubber_text(EmbGeometry *obj, const char *key)
{
    printf("%p %s\n", obj, key);
    /*
    if (objRubberTexts.contains(key))
        return objRubberTexts.value(key);
    */
    return "";
}

/*
 */
void
emb_circle_main(void)
{
    /*
    initCommand();
    clearSelection();
    view.ui_mode = "CIRCLE_MODE_1P_RAD";
    global.point1 = emb_vector(0.0, 0.0);
    global.point2 = emb_vector(0.0, 0.0);
    global.point3 = emb_vector(0.0, 0.0);
    */
}

/*
 * TODO: getCurrentLineType
void
emb_circle_init(EmbVector center, float radius, unsigned int rgb)
{
    if (n_views == 0) {
        return;
    }

    View view = views[settings.pattern_index];

    debug_message("CircleObject Constructor()");
    init(centerX, centerY, radius, rgb, Qt::SolidLine);
}
*/

/* TODO: getCurrentLineType
void
emb_circle_init(EmbGeometry* obj)
{
    debug_message("CircleObject Constructor()");
    if (obj) {
        init(obj->objectCenterX(), obj->objectCenterY(), obj->objectRadius(), obj->objectColorRGB(), Qt::SolidLine);
        setRotation(obj->rotation());
    }
}
*/

/*
 */
void
emb_circle_set_area(EmbCircle *circle, float area)
{
    circle->radius = sqrt(area / embConstantPi);
}

/*
 * TODO: pass in proper lineweight
void dim_leader_init(EmbLine line, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Leader Dimension");

    setFlag(ItemIsSelectable, true);

    curved = false;
    filled = true;
    setEndPoint1(x1, y1);
    setEndPoint2(x2, y2);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35);
    setPen(objPen);
}
*/

/*
void
emb_dimleader_set_end_point_1(EmbVector endPt1)
{
    EmbVector endPt2 = objectEndPoint2();
    EmbVector delta = emb_vector_subtract(endPt2, endPt1);
    setRotation(0);
    setLine(0, 0, dx, dy);
    setPos(endPt1);
    updateLeader();
}

void
dimleader_set_end_point_2(EmbVector endPt2)
{
    EmbVector delta;
    EmbVector endPt1 = scenePos();
    emb_vector_subtract(endPt2, endPt1, &delta);
    setRotation(0);
    setLine(0, 0, delta.x, delta.y);
    setPos(endPt1);
    updateLeader();
}

EmbVector
dimleader_end_point_1()
{
    return scenePos();
}

EmbVector
dimleader_objectEndPoint2()
{
    EmbLine lyne = line();
    float rot = radians(rotation());
    EmbVector point2;
    point2.x = lyne.x2()*scale();
    point2.y = lyne.y2()*scale();
    EmbVector rot = emb_vector_rotate(point2, alpha);

    return (scenePos() + rot);
}

EmbVector dimleader_objectMidPoint()
{
    EmbVector mp = line().pointAt(0.5) * scale();
    float alpha = radians(rotation());
    EmbVector rotMid = emb_vector_rotate(mp, alpha);
    return scenePos() + rotMid;
}

float dimleader_objectAngle()
{
    return fmodf(line().angle() - rotation(), 360.0);
}

//TODO: Make arrow style, angle, length and line angle and length customizable.
void
dimleader_updateLeader()
{
    int arrowStyle = Closed;
    float arrowStyleAngle = 15.0;
    float arrowStyleLength = 1.0;
    float lineStyleAngle = 45.0;
    float lineStyleLength = 1.0;

    EmbLine lyne = line();
    float angle = lyne.angle();
    EmbVector ap0 = lyne.p1();
    EmbVector lp0 = lyne.p2();

    //Arrow
    EmbLine lynePerp(lyne.pointAt(arrowStyleLength/lyne.length()) ,lp0);
    lynePerp.setAngle(angle + 90);
    EmbLine lyne1(ap0, lp0);
    EmbLine lyne2(ap0, lp0);
    lyne1.setAngle(angle + arrowStyleAngle);
    lyne2.setAngle(angle - arrowStyleAngle);
    EmbVector ap1;
    EmbVector ap2;
    lynePerp.intersects(lyne1, &ap1);
    lynePerp.intersects(lyne2, &ap2);

    //Math Diagram
    //                 .(ap1)                     .(lp1)
    //                /|                         /|
    //               / |                        / |
    //              /  |                       /  |
    //             /   |                      /   |
    //            /    |                     /    |
    //           /     |                    /     |
    //          /      |                   /      |
    //         /       |                  /       |
    //        /+(aSA)  |                 /+(lSA)  |
    // (ap0)./__(aSL)__|__________(lp0)./__(lSL)__|
    //       \ -(aSA)  |                \ -(lSA)  |
    //        \        |                 \        |
    //         \       |                  \       |
    //          \      |                   \      |
    //           \     |                    \     |
    //            \    |                     \    |
    //             \   |                      \   |
    //              \  |                       \  |
    //               \ |                        \ |
    //                \|                         \|
    //                 .(ap2)                     .(lp2)

    if (arrowStyle == Open) {
        arrowStylePath = QPainterPath();
        arrowStylePath.moveTo(ap1);
        arrowStylePath.lineTo(ap0);
        arrowStylePath.lineTo(ap2);
        arrowStylePath.lineTo(ap0);
        arrowStylePath.lineTo(ap1);
    }
    else if (arrowStyle == Closed) {
        arrowStylePath = QPainterPath();
        arrowStylePath.moveTo(ap1);
        arrowStylePath.lineTo(ap0);
        arrowStylePath.lineTo(ap2);
        arrowStylePath.lineTo(ap1);
    }
    else if (arrowStyle == Dot) {
        arrowStylePath = QPainterPath();
        arrowStylePath.addEllipse(ap0, arrowStyleLength, arrowStyleLength);
    }
    else if (arrowStyle == Box) {
        arrowStylePath = QPainterPath();
        float side = EmbLine(ap1, ap2).length();
        EmbRect ar0(0, 0, side, side);
        ar0.moveCenter(ap0);
        arrowStylePath.addRect(ar0);
    }
    else if (arrowStyle == Tick) {
    }

    lineStylePath = QPainterPath();
    lineStylePath.moveTo(ap0);
    lineStylePath.lineTo(lp0);
}
*/

void
emb_ellipse_main(void)
{
    /*
    initCommand();
    clearSelection();
    view.ui_mode = "ELLIPSE_MODE_MAJORDIAMETER_MINORRADIUS";
    global.point1 = zero_vector;
    global.point2 = zero_vector;
    global.point3 = zero_vector;
    */
}

/*
void emb_ellipse(float centerX, float centerY, float width, float height, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("EllipseObject Constructor()");
    init(centerX, centerY, width, height, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void emb_ellipse(EllipseObject* obj, QGraphicsItem* parent)
{
    debug_message("EllipseObject Constructor()");
    if (obj) {
        init(obj->objectCenterX(), obj->objectCenterY(), obj->objectWidth(), obj->objectHeight(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
    }
}

void image_init(EmbRect rect, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Image");

    setFlag(ItemIsSelectable, true);

    setRect(rect);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void image_setRect(float x, float y, float w, float h)
{
    setPos(x, y);
    setRect(0, 0, w, h);
    updatePath();
}

EmbVector image_objectTopLeft()
{
    float alpha = radians(rotation());
    EmbVector tl = rect().topRight() * scale();
    EmbVector ptlrot = emb_vector_rotate(tl, alpha);
    return scenePos() + ptlrot;
}

EmbVector image_objectTopRight()
{
    float alpha = radians(rotation());
    EmbVector tr = rect().topRight() * scale();
    EmbVector ptrrot = emb_vector_rotate(tr, alpha);
    return scenePos() + ptrrot;
}

EmbVector image_objectBottomLeft()
{
    float alpha = radians(rotation());
    EmbVector bl = rect().topRight() * scale();
    EmbVector pblrot = emb_vector_rotate(bl, alpha);
    return scenePos() + pblrot;
}

EmbVector image_objectBottomRight()
{
    float alpha = radians(rotation());
    EmbVector br = rect().topRight() * scale();
    EmbVector pbrrot = emb_vector_rotate(br, alpha);
    return scenePos() + pbrrot;
}

//Command: Line

float global = {}; //Required

void
emb_line_init(void)
{
    initCommand();
    clearSelection();
    global.firstRun = true;
    global.first.x = NaN;
    global.first.y = NaN;
    global.prev.x = NaN;
    global.prev.y = NaN;
}

void
emb_line_init(EmbLine line_in, unsigned int rgb, PenStyle lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Line");

    line = line_in;

    setFlag(ItemIsSelectable, true);

    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void
emb_line_set_endpoint1(EmbVector point1)
{
    float dx = line.start.x - point1.x;
    float dy = line.start.y - point1.y;
    setRotation(0);
    setScale(1);
    setLine(0, 0, dx, dy);
    setPos(point1);
}

void
emb_line_set_endpoint2(EmbVector point1)
{
    float dx = line.end.x - point1.x;
    float dy = line.end.y - point1.y;
    setRotation(0);
    setScale(1);
    setLine(0, 0, dx, dy);
    setPos(point1);
}

EmbVector
emb_line_EndPoint2()
{
    EmbLine lyne = line();
    float alpha = radians(rotation());
    EmbVector point2;
    point2.x = lyne.x2()*scale();
    point2.y = lyne.y2()*scale();
    EmbVector rotEnd = emb_vector_rotate(point2, alpha);

    return scenePos() + rotEnd;
}

EmbVector
emb_line_MidPoint()
{
    EmbLine lyne = line();
    EmbVector mp = lyne.pointAt(0.5) * scale();
    float alpha = radians(rotation());
    EmbVector rotMid = emb_vector_rotate(mp, alpha);

    return scenePos() + rotMid;
}

float
emb_line_angle()
{
    return fmodf(line().angle() - rotation(), 360.0);
}

path_PathObject(float x, float y, const QPainterPath p, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("PathObject Constructor()");
    init(x, y, p, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

path_PathObject(PathObject* obj, QGraphicsItem* parent)
{
    debug_message("PathObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void path_init(float x, float y, const QPainterPath& p, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Path");

    setFlag(ItemIsSelectable, true);

    updatePath(p);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void point_init(float x, float y, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Point");

    setFlag(ItemIsSelectable, true);

    setRect(-0.00000001, -0.00000001, 0.00000002, 0.00000002);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void
emb_polygon(float x, float y, const QPainterPath& p, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("PolygonObject Constructor()");
    init(x, y, p, rgb, SolidLine); //TODO: getCurrentLineType
}

void
polygon_PolygonObject(PolygonObject* obj, QGraphicsItem* parent)
{
    debug_message("PolygonObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void
emb_polygon_init(float x, float y, const QPainterPath& p, unsigned int rgb, PenStyle lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Polygon");

    setFlag(ItemIsSelectable, true);

    gripIndex = -1;
    updatePath(p);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
}

int polygon_findIndex(EmbVector point)
{
    int i = 0;
    int elemCount = normalPath.elementCount();
    //NOTE: Points here are in item coordinates
    EmbVector itemPoint = mapFromScene(point);
    for (i = 0; i < elemCount; i++) {
        QPainterPath::Element e = normalPath.elementAt(i);
        EmbVector elemPoint = EmbVector(e.x, e.y);
        if (itemPoint == elemPoint) return i;
    }
    return -1;
}

void
emb_polyline(float x, float y, const QPainterPath& p, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("PolylineObject Constructor()");
    init(x, y, p, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void
emb_polyline(EmbPolyline* obj, QGraphicsItem* parent)
{
    debug_message("PolylineObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void embPolyline_init(float x, float y, QPainterPath *p, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Polyline");

    setFlag(ItemIsSelectable, true);

    gripIndex = -1;
    updatePath(p);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
}

int
embPolyline_findIndex(const EmbVector& point)
{
    int elemCount = normalPath.elementCount();
    //NOTE: Points here are in item coordinates
    EmbVector itemPoint = mapFromScene(point);
    for (int i = 0; i < elemCount; i++) {
        QPainterPath::Element e = normalPath.elementAt(i);
        EmbVector elemPoint = EmbVector(e.x, e.y);
        if (itemPoint == elemPoint) return i;
    }
    return -1;
}

void
rect_init(EmbRect rect, unsigned int rgb, PenStyle lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Rectangle");

    setFlag(ItemIsSelectable, true);

    setRect(x, y, w, h);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
}

EmbVector
rect_topLeft()
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    float alpha = radians(rotation());
    EmbVector tl = rect().topLeft() * scale();
    EmbVector ptlrot = emb_vector_rotate(t1, alpha);
    return scenePos() + ptlrot;
    return v;
}

EmbVector
rect_topRight()
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    float alpha = radians(rotation());
    EmbVector tr = rect().topRight() * scale();
    EmbVector ptlrot = emb_vector_rotate(t1, alpha);
    return scenePos() + ptrrot;
    return v;
}
*/

EmbVector
embRect_bottomLeft(EmbRect rect)
{
    printf("%f", rect.x);
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    /*
    float alpha = radians(rotation());
    EmbVector bl = rect().bottomLeft() * scale();
    EmbVector pblrot = emb_vector_rotate(b1, alpha);
    return scenePos() + pblrot;
    */
    return v;
}

EmbVector
embRect_bottomRight(EmbRect rect)
{
    printf("%f", rect.x);
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    /*
    float alpha = radians(rotation());
    EmbVector br = rect().bottomRight() * scale();
    EmbVector pbrrot = emb_vector_rotate(br, alpha);
    return scenePos() + pbrrot;
    */
    return v;
}

/*
    View view = views[settings.pattern_index];

    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "CIRCLE");

    setFlag(ItemIsSelectable, true);

    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
    updatePath();
 */
EmbGeometry
emb_circle(EmbReal x, EmbReal y, EmbReal radius)
{
    EmbGeometry g;
    g.object.circle.center.x = x;
    g.object.circle.center.y = y;
    g.object.circle.radius = radius;
    g.type = EMB_CIRCLE;
    g.color.r = 0;
    g.color.g = 0;
    g.color.b = 0;
    g.lineType = 0;
    return g;
}

/* Computational Geometry for Circles */

/* Returns true if the circles intersect.
 * Returns false if the circles do not intersect.
 */
int
getCircleCircleIntersections(EmbCircle c0, EmbCircle c1,
                             EmbVector *p0, EmbVector *p1)
{
    EmbVector delta;
    EmbReal a, h, px2, py2, mx, my, d;
    /* Distance between centers */
    delta = emb_vector_subtract(c1.center, c0.center);
    d = emb_vector_length(delta);

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
       a stated (EmbReal) tolerance value would help.
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

/* Returns true if the given point lies outside the circle.
 * Returns false if the given point is inside the circle.
 */
int
getCircleTangentPoints(EmbCircle c, EmbVector point, EmbVector *t0, EmbVector *t1)
{
    EmbCircle p;
    EmbReal hyp;
    /* Distance to center of circle */
    hyp = emb_vector_distance(point, c.center);
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

/*
 */
EmbEllipse
emb_ellipse_init(void)
{
    EmbEllipse ellipse;
    ellipse.center.x = 0.0;
    ellipse.center.y = 0.0;
    ellipse.radius.x = 1.0;
    ellipse.radius.y = 2.0;
    ellipse.rotation = 0.0;
    return ellipse;
}

/* . */
EmbReal
emb_ellipse_diameterX(EmbEllipse ellipse)
{
    return ellipse.radius.x * 2.0;
}

EmbReal
emb_ellipse_diameterY(EmbEllipse ellipse)
{
    return ellipse.radius.y * 2.0;
}

/*
void emb_ellipse_init(EmbEllipse ellipse, unsigned int rgb, int lineType)
{
    printf("%f %d %d", ellipse.radius.x, rgb, lineType);
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Ellipse");

    setFlag(ItemIsSelectable, true);

    setSize(width, height);
    setCenter(centerX, centerY);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
    updatePath();
}
*/

void
emb_ellipse_setSize(float width, float height)
{
    printf("%f %f", width, height);
    /*
    EmbRect elRect = rect();
    elRect.setWidth(width);
    elRect.setHeight(height);
    elRect.moveCenter(EmbVector(0,0));
    setRect(elRect);
    */
}

/*
 * BASIC FUNCTIONS
 */

/* round is C99 and we're committed to C90 so here's a replacement.
 */
int
emb_round(EmbReal x)
{
    EmbReal y = floor(x);
    if (fabs(x-y) > 0.5) {
        return (int)ceil(x);
    }
    return (int)y;
}

EmbReal
radians(EmbReal degree)
{
    return degree*embConstantPi/180.0;
}

EmbReal
degrees(EmbReal radian)
{
    return radian*180.0/embConstantPi;
}

/* Finds the normalized vector perpendicular (clockwise) to the line
 * given by v1->v2 (normal to the line) */
EmbVector
emb_line_normalVector(EmbLine line, int clockwise)
{
    EmbVector result;
    EmbReal temp;
    result = emb_vector_subtract(line.end, line.start);
    result = emb_vector_normalize(result);
    temp = result.x;
    result.x = result.y;
    result.y = -temp;
    if (!clockwise) {
        result.x = -result.x;
        result.y = -result.y;
    }
    return result;
}

/* Returns the vector that is the same length as the line, in the same
 * direction.
 */
EmbVector
emb_line_toVector(EmbLine line)
{
    return emb_vector_subtract(line.end, line.start);
}

/*
 * Finds the intersection of two lines given by v1->v2 and v3->v4
 * and sets the value in the result variable.
 */
EmbVector
emb_line_intersectionPoint(EmbLine line1, EmbLine line2, int *emb_error)
{
    EmbReal det, C2, C1, tolerance;
    EmbVector vec1, vec2, result;
    *emb_error = 0;
    vec1 = emb_line_toVector(line1);
    vec2 = emb_line_toVector(line2);
    C2 = emb_vector_cross(line1.start, vec1);
    C1 = emb_vector_cross(line2.start, vec2);

    tolerance = 1e-10;
    det = emb_vector_cross(vec2, vec1);

    if (fabs(det) < tolerance) {
        /* Default to the origin when an error is thrown. */
        *emb_error = 1;
        result.x = 0.0;
        result.y = 0.0;
        return result;
    }
    result.x = (vec2.x * C2 - vec1.x * C1) / det;
    result.y = (vec2.y * C2 - vec1.y * C1) / det;
    return result;
}

/* .
 */
EmbRect
emb_rect(EmbReal x, EmbReal y, EmbReal w, EmbReal h)
{
    EmbRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return rect;
}

//NOTE: This void should be used to interpret various object types and save them as polylines for stitchOnly formats.
/*
void
save_to_polyline(EmbPattern* pattern, const EmbVector& objPos, const QPainterPath& objPath, const char* layer, const QColor& color, const char* lineType, const char* lineWeight)
{
    float startX = objPos.x();
    float startY = objPos.y();
    EmbArray *pointList = emb_array_create(EMB_POINT);
    EmbPoint lastPoint;
    QPainterPath::Element element;
    for (int i = 0; i < objPath.elementCount(); ++i) {
        element = objPath.elementAt(i);
        if (pointList->count == 0) {
            lastPoint.position.x = element.x + startX;
            lastPoint.position.y = -(element.y + startY);
            emb_array_addPoint(pointList, lastPoint);
        }
        else {
            lastPoint.position.x += element.x + startX;
            lastPoint.position.y += -(element.y + startY);
        }
    }

    EmbPolyline polyObject;
    polyObject.pointList = pointList;
    polyObject.color.r = color.red();
    polyObject.color.g = color.green();
    polyObject.color.b = color.blue();
    //TODO: proper lineType
    emb_pattern_addPolylineAbs(pattern, polyObject);
}

void textSingle_TextSingleObject(const char* str, float x, float y, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("TextSingleObject Constructor()");
    init(str, x, y, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void textSingle_TextSingleObject(TextSingleObject* obj, QGraphicsItem* parent)
{
    debug_message("TextSingleObject Constructor()");
    if (obj) {
        setTextFont(obj->objTextFont);
        setTextSize(obj->objTextSize);
        setRotation(obj->rotation());
        setTextBackward(obj->objTextBackward);
        setTextUpsideDown(obj->objTextUpsideDown);
        setTextStyle(obj->objTextBold, obj->objTextItalic, obj->objTextUnderline, obj->objTextStrikeOut, obj->objTextOverline);
        init(obj->objText, obj->objectX(), obj->objectY(), obj->objectColorRGB(), SolidLine); //TODO: getCurrentLineType
        setScale(obj->scale());
    }
}

void textSingle_init(const char* str, float x, float y, unsigned int rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Single Line Text");

    setFlag(ItemIsSelectable, true);

    objTextJustify = "Left"; //TODO: set the justification properly

    setText(str);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

std::stringList text_single_objectTextJustifyList()
{
    std::stringList justifyList;
    justifyList << "Left" << "Center" << "Right" << "Middle";
    // TODO: << "Fit" << "Aligned";
    justifyList << "Top Left" << "Top Center" << "Top Right";
    justifyList << "Middle Left" << "Middle Center" << "Middle Right";
    justifyList << "Bottom Left" << "Bottom Center" << "Bottom Right";
    return justifyList;
}

void textSingle_setText(const char* str)
{
    objText = str;
    QPainterPath textPath;
    QFont font;
    font.setFamily(objTextFont);
    font.setPointSizeF(objTextSize);
    font.setBold(objTextBold);
    font.setItalic(objTextItalic);
    font.setUnderline(objTextUnderline);
    font.setStrikeOut(objTextStrikeOut);
    font.setOverline(objTextOverline);
    textPath.addText(0, 0, font, str);

    //Translate the path based on the justification
    EmbRect jRect = textPath.boundingRect();
    if (objTextJustify == "Left") {
        textPath.translate(-jRect.left(), 0);
    }
    else if (objTextJustify == "Center") {
        textPath.translate(-jRect.center().x(), 0);
    }
    else if (objTextJustify == "Right") {
        textPath.translate(-jRect.right(), 0);
    }
    else if (objTextJustify == "Aligned") {

    } //TODO: TextSingleObject Aligned Justification
    else if (objTextJustify == "Middle") {
        textPath.translate(-jRect.center()); }
    else if (objTextJustify == "Fit") {

    } //TODO: TextSingleObject Fit Justification
    else if (objTextJustify == "Top Left") {
        textPath.translate(-jRect.topLeft());
    }
    else if (objTextJustify == "Top Center") {
        textPath.translate(-jRect.center().x(), -jRect.top());
    }
    else if (objTextJustify == "Top Right") {
        textPath.translate(-jRect.topRight());
    }
    else if (objTextJustify == "Middle Left") {
        textPath.translate(-jRect.left(), -jRect.top()/2.0);
    }
    else if (objTextJustify == "Middle Center") { textPath.translate(-jRect.center().x(), -jRect.top()/2.0); }
    else if (objTextJustify == "Middle Right")  { textPath.translate(-jRect.right(), -jRect.top()/2.0); }
    else if (objTextJustify == "Bottom Left")   { textPath.translate(-jRect.bottomLeft()); }
    else if (objTextJustify == "Bottom Center") { textPath.translate(-jRect.center().x(), -jRect.bottom()); }
    else if (objTextJustify == "Bottom Right")  { textPath.translate(-jRect.bottomRight()); }

    //Backward or Upside Down
    if (objTextBackward || objTextUpsideDown) {
        float horiz = 1.0;
        float vert = 1.0;
        if (objTextBackward) horiz = -1.0;
        if (objTextUpsideDown) vert = -1.0;

        QPainterPath flippedPath;

        QPainterPath::Element element;
        QPainterPath::Element P2;
        QPainterPath::Element P3;
        QPainterPath::Element P4;
        for (int i = 0; i < textPath.elementCount(); ++i) {
            element = textPath.elementAt(i);
            if (element.isMoveTo()) {
                flippedPath.moveTo(horiz * element.x, vert * element.y);
            }
            else if (element.isLineTo()) {
                flippedPath.lineTo(horiz * element.x, vert * element.y);
            }
            else if (element.isCurveTo()) {
                                              // start point P1 is not needed
                P2 = textPath.elementAt(i);   // control point
                P3 = textPath.elementAt(i+1); // control point
                P4 = textPath.elementAt(i+2); // end point

                flippedPath.cubicTo(horiz * P2.x, vert * P2.y,
                                    horiz * P3.x, vert * P3.y,
                                    horiz * P4.x, vert * P4.y);
            }
        }
        objTextPath = flippedPath;
    }
    else {
        objTextPath = textPath;
    }

    //Add the grip point to the shape path
    QPainterPath gripPath = objTextPath;
    gripPath.connectPath(objTextPath);
    gripPath.addRect(-0.00000001, -0.00000001, 0.00000002, 0.00000002);
    setPath(gripPath);
}
*/

void
textSingle_setJustify(EmbGeometry *g, const char *justify)
{
    printf("%p, %s\n", g, justify);
    /*
    // Verify the string is a valid option
    objTextJustify = "Left";
    if ((justify == "Left") || (justify == "Center") || (justify == "Right")
        || (justify == "Aligned") || (justify == "Middle") || (justify == "Fit")
        || (justify == "Top Left") || (justify == "Top Center") || (justify == "Top Right")
        || (justify == "Middle Left") || (justify == "Middle Center") || (justify == "Middle Right")
        || (justify == "Bottom Left") || (justify == "Bottom Center") || (justify == "Bottom Right")) {
        objTextJustify = justify;
    }
    setText(objText);
    */
}

/* . */
int
emb_backwards(EmbGeometry *g, EmbError *error)
{
    /*
    objTextBackward = value;
    setText(objText);
    */
    *error = EMB_NO_ERR;
    return 0;
}

int
emb_bold(EmbGeometry *g, EmbError *error)
{
    /*
    objTextBold = val;
    setText(objText);
    */
    *error = EMB_NO_ERR;
    return 0;
}

int
emb_bulge(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    return 0;
}

EmbReal
emb_chord_length(EmbGeometry *g, EmbError *error)
{
    EmbVector v = emb_chord(g, error);
    if (*error) {
        return 0.0;
    }
    *error = EMB_NO_ERR;
    return emb_vector_length(v);
}

EmbReal
emb_chord_angle(EmbGeometry *g, EmbError *error)
{
    return 0.0;
}

#if 0
    case EMB_CHORDANGLE: {
        EmbVector delta = emb_chord(g, EMB_CHORD).v;
        v = script_real(emb_vector_angle(delta));
        break;
    }
    case EMB_CHORDMID: {
        v = emb_chord(g, EMB_CHORD);
        v.v = emb_vector_scale(v.v, 0.5);
        break;
    }
    case EMB_DIAMETER: {
        v = emb_radius(g, error);
        v.r = fabs(v.r * 2.0);
        break;
    }
    case EMB_INCANGLE: {
        EmbReal bulge = emb_bulge(g, EMB_BULGE).r;
        v = script_real(atan(bulge)*4.0);
        break;
    }
    case EMB_FONT: {
        /*
        objTextFont = font;
        setText(objText);
        */
        break;
    }
    case EMB_ITALIC: {
        /*
        objTextItalic = val;
        setText(objText);
        */
        break;
    }
    case EMB_SAGITTA: {
        EmbReal chord = emb_chord(g);
        ScriptValue bulge = emb_bulge(g, EMB_BULGE);
        return script_real(fabs((chord / 2.0) * bulge.r));
    }
    case EMB_STRIKEOUT: {
        /*
        objTextStrikeOut = val;
        setText(objText);
        */
        break;
    }
    case EMB_OVERLINE: {
        /*
        objTextOverline = val;
        setText(objText);
        */
        break;
    }
    case EMB_UNDERLINE: {
        /*
        objTextUnderline = val;
        setText(objText);
        */
        break;
    }
    case EMB_UPSIDEDOWN: {
        /*
        objTextUpsideDown = value;
        setText(objText);
        */
        break;
    }
    case EMB_SIZE: {
        /*
        objTextSize = value;
        setText(objText);
        */
        break;
    }
    case EMB_PERIMETER: {
        break;
    }
    default:
        break;
    }
    return v;
}

/* */
int
emb_gset(EmbGeometry *g, int attribute, ScriptValue value)
{
    printf("%d\n", value.type);
    switch (g->type) {
    case EMB_BOLD: {
        /*
        objTextBold = val;
        setText(objText);
        */
        break;
    }
    case EMB_ITALIC: {
        /*
        objTextItalic = val;
        setText(objText);
        */
        break;
    }
    case EMB_UNDERLINE: {
        /*
        objTextUnderline = val;
        setText(objText);
        */
        break;
    }
    case EMB_STRIKEOUT: {
        /*
        objTextStrikeOut = val;
        setText(objText);
        */
        break;
    }
    case EMB_OVERLINE: {
        /*
        objTextOverline = val;
        setText(objText);
        */
        break;
    }
    case EMB_BACKWARDS: {
        /*
        objTextBackward = val;
        setText(objText);
        */
        break;
    }
    case EMB_UPSIDEDOWN: {
        /*
        objTextUpsideDown = val;
        setText(objText);
        */
        break;
    }
    case EMB_SAGITTA: {
        if (g->type != EMB_ARC) {
            /* ERROR */
            return 0;
        }
        break;
    }
    case EMB_BULGE: {
        if (g->type != EMB_ARC) {
            /* ERROR */
            return 0;
        }
        break;
    }
    case EMB_SIZE: {
        /*
        objTextSize = value;
        setText(objText);
        */
        break;
    }
    case EMB_PERIMETER: {
        /* TODO: Use Ramanujan's approximation here. */
        break;
    }
    case EMB_AREA: {
        /* TODO: look up a formula for ellipses. */
        break;
    }
    default:
        break;
    }
    return 0;
}
#endif

/*
 * Libembroidery 1.0.0-alpha
 * https://www.libembroidery.org
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright 2018-2025 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * -----------------------------------------------------------------------------
 *
 * The EmbPattern struct memory management and storage.
 *
 * Only uses source from this directory or standard C libraries,
 * not including POSIX headers like unistd since this library
 * needs to support non-POSIX systems like Windows.
 */

/* Internal Data
 * ----------------------------------------------------------------------------
 *
 * This file contains all the read and write functions for the
 * library.
 *
 * .. todo::
 *    This list needs reviewed in case some stitch
 *    formats also can contain object data (EMBFORMAT_STCHANDOBJ). *
 */
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

const char *version_string = "embroider v0.1";

const int NUMBINS = 10;

EmbReal epsilon = 0.000000001;

EmbThread black_thread = { { 0, 0, 0 }, "Black", "Black" };
int emb_verbose = 0;

const EmbReal embConstantPi = 3.1415926535;

/* Constant representing the number of EmbReal Indirect FAT
 * entries in a single header */
const unsigned int difatEntriesInHeader = 109;
const unsigned int sizeOfFatEntry = sizeof(unsigned int);
const unsigned int sizeOfDifatEntry = 4;
const unsigned int sizeOfChainingEntryAtEndOfDifatSector = 4;
const unsigned int sizeOfDirectoryEntry = 128;
/*
const int supportedMinorVersion = 0x003E;
const int littleEndianByteOrderMark = 0xFFFE;
*/

/* Converted from the table at:
 *     https://www.w3.org/TR/SVGb/types.html#ColorKeywords
 * NOTE: This supports both UK and US English names, so the repeated values
 * aren't an error.
 */
thread_color svg_color_codes[200] = {
    {"aliceblue", 0xFFf0f8ff, 0},
    {"antiquewhite", 0xFFfaebd7, 1},
    {"aqua", 0xFF00ffff, 2},
    {"aquamarine", 0xFF7fffd4, 3},
    {"azure", 0xFFf0ffff, 4},
    {"beige", 0xFFf5f5dc, 5},
    {"bisque", 0xFFffe4c4, 6},
    {"black", 0xFF000000, 7},
    {"blanchedalmond", 0xFFffebcd, 8},
    {"blue", 0xFF0000ff, 9},
    {"blueviolet", 0xFF8a2be2, 10},
    {"brown", 0xFFa52a2a, 11},
    {"burlywood", 0xFFdeb81b, 12},
    {"cadetblue", 0xFF5f9ea0, 13},
    {"chartreuse", 0xFF7fff00, 14},
    {"chocolate", 0xFFd22d1e, 15},
    {"coral", 0xFFFF7f0e, 16},
    {"cornflowerblue", 0xFF1c5fed, 17},
    {"cornsilk", 0xFFfff8dc, 18},
    {"crimson", 0xFFdc0e3c, 19},
    {"cyan", 0xFF00ffff, 20},
    {"darkblue", 0xFF00008b, 21},
    {"darkcyan", 0xFF008b8b, 22},
    {"darkgoldenrod", 0xFFb81a0b, 23},
    {"darkgray", 0xFFa9a9a9, 24},
    {"darkgreen", 0xFF001c00, 25},
    {"darkgrey", 0xFFa9a9a9, 26},
    {"darkkhaki", 0xFFbdb76b, 27},
    {"darkmagenta", 0xFF8b008b, 28},
    {"darkolivegreen", 0xFF0d6b2f, 29},
    {"darkorange", 0xFFff8c00, 30},
    {"darkorchid", 0xFF3f0ecc, 31},
    {"darkred", 0xFF8b0000, 32},
    {"darksalmon", 0xFFe93c7a, 33},
    {"darkseagreen", 0xFF8fbc8f, 34},
    {"darkslateblue", 0xFF1e3d8b, 35},
    {"darkslategray", 0xFF2f4f4f, 36},
    {"darkslategrey", 0xFF2f4f4f, 37},
    {"darkturquoise", 0xFF00ced1, 38},
    {"darkviolet", 0xFF5e00d3, 39},
    {"deeppink", 0xFFff0e5d, 40},
    {"deepskyblue", 0xFF00bfff, 41},
    {"dimgray", 0xFF2d2d2d, 42},
    {"dimgrey", 0xFF2d2d2d, 43},
    {"dodgerblue", 0xFF1e5aff, 44},
    {"firebrick", 0xFFb20a0a, 45},
    {"floralwhite", 0xFFfffaf0, 46},
    {"forestgreen", 0xFF0a8b0a, 47},
    {"fuchsia", 0xFFff00ff, 48},
    {"gainsboro", 0xFFdcdcdc, 49},
    {"ghostwhite", 0xFFf8f8ff, 50},
    {"gold", 0xFFffd700, 51},
    {"goldenrod", 0xFFdaa50e, 52},
    {"gray", 0xFF0e0e0e, 53},
    {"grey", 0xFF0e0e0e, 54},
    {"green", 0xFF000e00, 55},
    {"greenyellow", 0xFFadff2f, 56},
    {"honeydew", 0xFFf0fff0, 57},
    {"hotpink", 0xFFff2db4, 58},
    {"indianred", 0xFFcd5c5c, 59},
    {"indigo", 0xFF4b000a, 60},
    {"ivory", 0xFFfffff0, 61},
    {"khaki", 0xFFf0e68c, 62},
    {"lavender", 0xFFe6e6fa, 63},
    {"lavenderblush", 0xFFfff0f5, 64},
    {"lawngreen", 0xFF7cfc00, 65},
    {"lemonchiffon", 0xFFfffacd, 66},
    {"lightblue", 0xFFadd8e6, 67},
    {"lightcoral", 0xFFf00e0e, 68},
    {"lightcyan", 0xFFe0ffff, 69},
    {"lightgoldenrodyellow", 0xFFfafad2, 70},
    {"lightgray", 0xFFd3d3d3, 71},
    {"lightgreen", 0xFF5aee5a, 72},
    {"lightgrey", 0xFFd3d3d3, 73},
    {"lightpink", 0xFFffb6c1, 74},
    {"lightsalmon", 0xFFffa07a, 75},
    {"lightseagreen", 0xFF0eb2aa, 76},
    {"lightskyblue", 0xFF1bcefa, 77},
    {"lightslategray", 0xFF4d3a3f, 78},
    {"lightslategrey", 0xFF4d3a3f, 79},
    {"lightsteelblue", 0xFFb0c4de, 80},
    {"lightyellow", 0xFFffffe0, 81},
    {"lime", 0xFF00ff00, 82},
    {"limegreen", 0xFF0ecd0e, 83},
    {"linen", 0xFFfaf0e6, 84},
    {"magenta", 0xFFff00ff, 85},
    {"maroon", 0xFF0e0000, 86},
    {"mediumaquamarine", 0xFF2acdaa, 87},
    {"mediumblue", 0xFF0000cd, 88},
    {"mediumorchid", 0xFFba0dd3, 89},
    {"mediumpurple", 0xFF5d2edb, 90},
    {"mediumseagreen", 0xFF3cb32f, 91},
    {"mediumslateblue", 0xFF7b2cee, 92},
    {"mediumspringgreen", 0xFF00fa9a, 93},
    {"mediumturquoise", 0xFF1ed1cc, 94},
    {"mediumvioletred", 0xFFc70f0d, 95},
    {"midnightblue", 0xFF0d0d2e, 96},
    {"mintcream", 0xFFf5fffa, 97},
    {"mistyrose", 0xFFffe4e1, 98},
    {"moccasin", 0xFFffe4b5, 99},
    {"navajowhite", 0xFFffdead, 100},
    {"navy", 0xFF00000e, 101},
    {"oldlace", 0xFFfdf5e6, 102},
    {"olive", 0xFF0e0e00, 103},
    {"olivedrab", 0xFF6b8e0b, 104},
    {"orange", 0xFFffa500, 105},
    {"orangered", 0xFFff2d00, 106},
    {"orchid", 0xFFda2ed6, 107},
    {"palegoldenrod", 0xFFeee8aa, 109},
    {"palegreen", 0xFF3efb3e, 110},
    {"paleturquoise", 0xFFafeeee, 111},
    {"palevioletred", 0xFFdb2e5d, 112},
    {"papayawhip", 0xFFffefd5, 113},
    {"peachpuff", 0xFFffdab9, 114},
    {"peru", 0xFFcd0d3f, 115},
    {"pink", 0xFFffc0cb, 116},
    {"plum", 0xFFdda0dd, 117},
    {"powderblue", 0xFFb0e0e6, 118},
    {"purple", 0xFF0e000e, 119},
    {"red", 0xFFff0000, 120},
    {"rosybrown", 0xFFbc8f8f, 121},
    {"royalblue", 0xFF1d2de1, 122},
    {"saddlebrown", 0xFF8b2d0d, 123},
    {"salmon", 0xFFfa0e1e, 124},
    {"sandybrown", 0xFFf4a43c, 125},
    {"seagreen", 0xFF2e8b1b, 126},
    {"seashell", 0xFFfff5ee, 127},
    {"sienna", 0xFFa00a2d, 128},
    {"silver", 0xFFc0c0c0, 129},
    {"skyblue", 0xFF1bceeb, 130},
    {"slateblue", 0xFF6a5acd, 131},
    {"slategray", 0xFF2e0e5a, 132},
    {"slategrey", 0xFF2e0e5a, 133},
    {"snow", 0xFFfffafa, 134},
    {"springgreen", 0xFF00ff7f, 135},
    {"steelblue", 0xFF2e0ab4, 136},
    {"tan", 0xFFd2b48c, 137},
    {"teal", 0xFF000e0e, 138},
    {"thistle", 0xFFd8bfd8, 139},
    {"tomato", 0xFFff3f2f, 140},
    {"turquoise", 0xFF1ce0d0, 141},
    {"violet", 0xFFee0aee, 142},
    {"wheat", 0xFFf5deb3, 143},
    {"white", 0xFFffffff, 144},
    {"whitesmoke", 0xFFf5f5f5, 145},
    {"yellow", 0xFFffff00, 146},
    {"yellowgreen", 0xFF9acd0e, 147},
    {"END", 0, -1}
};


EmbBrand brand_codes[100] = {
    {svg_color_codes, 100, "DXF"},
    {svg_color_codes, 100, "HUS"},
    {svg_color_codes, 100, "JEF"},
    {svg_color_codes, 100, "SHV"},
    {svg_color_codes, 100, "PCM"},
    {svg_color_codes, 100, "PEC"},
    {svg_color_codes, 200, "Scalable Vector Graphics"}
};

/* Finds the location of the first non-whitespace character
 * in the string and returns it.
 */
int
string_whitespace(const char *s)
{
    int i;
    for (i=0; i<200; i++) {
        if (s[i] == ' ') continue;
        if (s[i] == '\t') continue;
        if (s[i] == '\r') continue;
        if (s[i] == '\n') continue;
        return i;
    }
    return i;
}

/* Note that our version of strlen can tell us that
 * the string is not null-terminated by returning -1.
 */
int
string_len(const char *src)
{
    int i;
    for (i=0; i<200; i++) {
        if (src[i] == 0) {
            return i;
        }
    }
    return -1;
}

/*
 */
int
string_rchar(const char *s, char c)
{
	int i;
	int n = string_len(s);
	for (i=n-1; i>=0; i--) {
		if (s[i] == c) {
			return i;
		}
	}
	return 0;
}

/* ENCODING SECTION
 * ----------------------------------------------------------------------------
 *
 * The functions in this section are grouped together to aid the developer's
 * understanding of the similarities between the file formats. This also helps
 * reduce errors between reimplementation of the same idea.
 *
 * For example: the Tajima ternary encoding of positions is used by at least 4
 * formats and the only part that changes is the flag encoding.
 *
 * Converts a 6 digit hex string (I.E. "00FF00")
 * into an EmbColor and returns it.
 *
 * a val 6 byte code describing the color as a hex string, doesn't require null termination.
 * Returns EmbColor the same color as our internal type.
 */
EmbColor
embColor_fromHexStr(char* val)
{
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

EmbColor
embColor_make(unsigned char red, unsigned char green, unsigned char blue)
{
    EmbColor c;
    c.r = red;
    c.b = green;
    c.g = blue;
    return c;
}

/* Swap two bytes' positions. */
void
emb_swap(char *a, int i, int j)
{
    char tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

/* Deal with endianness of the host machine. */
void
fix_endian(char *a, int bytes, int endian)
{
    if (endian != ENDIAN_HOST) {
        if (bytes == 2) {
            emb_swap(a, 0, 1);
        }
        if (bytes == 4) {
            emb_swap(a, 0, 3);
            emb_swap(a, 1, 2);
        }
    }
}

/* Read a little-endian signed 16-bit integer. */
int16_t
emb_read_i16(FILE* f)
{
    char data[2];
    if (fread(data, 1, 2, f) != 2) {
        puts("ERROR: Failed to read a int16_t.");
        return 0;
    }
    fix_endian(data, 2, EMB_LITTLE_ENDIAN);
    return *((int16_t*)data);
}

/* Read a little-endian unsigned 16-bit integer. */
uint16_t
emb_read_u16(FILE* f)
{
    char data[2];
    if (fread(data, 1, 2, f) != 2) {
        puts("ERROR: Failed to read a uint16_t.");
        return 0;
    }
    fix_endian(data, 2, EMB_LITTLE_ENDIAN);
    return *((uint16_t*)data);
}

/* Read a little-endian signed 32-bit integer. */
int32_t
emb_read_i32(FILE* f)
{
    char data[4];
    if (fread(data, 1, 4, f) != 4) {
        puts("ERROR: Failed to read a int32_t.");
        return 0;
    }
    fix_endian(data, 4, EMB_LITTLE_ENDIAN);
    return *((int32_t*)data);
}

/* Read a little-endian unsigned 32-bit integer. */
uint32_t
emb_read_u32(FILE* f)
{
    char data[4];
    if (fread(data, 1, 4, f) != 4) {
        puts("ERROR: Failed to read a uint32_t.");
        return 0;
    }
    fix_endian(data, 4, EMB_LITTLE_ENDIAN);
    return *((uint32_t*)data);
}

/* Read a big-endian signed 16-bit integer. */
int16_t
emb_read_i16be(FILE* f)
{
    char data[2];
    if (fread(data, 1, 2, f) != 2) {
        puts("ERROR: Failed to read a int16_t.");
        return 0;
    }
    fix_endian(data, 2, EMB_BIG_ENDIAN);
    return *((int16_t*)data);
}

/* Read a big-endian unsigned 16-bit integer. */
uint16_t
emb_read_u16be(FILE* f)
{
    char data[2];
    if (fread(data, 1, 2, f) != 2) {
        puts("ERROR: Failed to read a uint16_t.");
        return 0;
    }
    fix_endian(data, 2, EMB_BIG_ENDIAN);
    return *((uint16_t*)data);
}

/* Read a big-endian signed 32-bit integer. */
int32_t
emb_read_i32be(FILE* f)
{
    char data[4];
    if (fread(data, 1, 4, f) != 4) {
        puts("ERROR: Failed to read a int32_t.");
        return 0;
    }
    fix_endian(data, 4, EMB_BIG_ENDIAN);
    return *((int32_t*)data);
}

/* Read a big-endian unsigned 32-bit integer. */
uint32_t
emb_read_u32be(FILE* f)
{
    char data[4];
    if (fread(data, 1, 4, f) != 4) {
        puts("ERROR: Failed to read a uint32_t.");
        return 0;
    }
    fix_endian(data, 4, EMB_BIG_ENDIAN);
    return *((uint32_t*)data);
}

/* a b a x a y a flags .
 *
 * \todo remove the unused return argument.
 */
int
decode_t01_record(unsigned char b[3], int *x, int *y, int *flags)
{
    decode_tajima_ternary(b, x, y);

    if (b[2] == 0xF3) {
        *flags = END;
        return 1;
    }
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
    return 1;
}

/* Encode into bytes a b the values of the x-position a x,
 * y-position a y and the a flags.
 */
void
encode_t01_record(unsigned char b[3], int x, int y, int flags)
{
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

/* Encode the signed ternary of the tajima format into
 * a b the position values a x and a y.
 *
 * If the values of a x or a y fall outside of the
 * valid range of -121 and +121 then it returns 0 and
 * 1.
 */
int
encode_tajima_ternary(unsigned char b[3], int x, int y)
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

/* Decode the signed ternary of the tajima format from
 * a b to the position values a x and a y.
 *
 * There is no return argument.
 */
void
decode_tajima_ternary(unsigned char b[3], int *x, int *y)
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

/* a file a dx a dy a flags
 */
void pfaffEncode(FILE* file, int dx, int dy, int flags)
{
    unsigned char flagsToWrite = 0;

    if (!file) {
        printf("ERROR: format-pcs.c pcsEncode(), file argument is null\n");
        return;
    }

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

/* Decode the bytes a a1, a a2 and a a3 .
 * Returns the EmbReal floating-point value.
 */
EmbReal
pfaffDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res) & 0x7FFFFF) - 1));
    }
    return 1.0f * res;
}

/*  * a value
 * Returns unsigned char
 */
unsigned char
mitEncodeStitch(EmbReal value)
{
    if (value < 0) {
        return 0x80 | (unsigned char)(-value);
    }
    return (unsigned char)value;
}

/*  * a value
 * Returns int
 */
int
mitDecodeStitch(unsigned char value)
{
    if (value & 0x80) {
        return -(value & 0x1F);
    }
    return value;
}

/*  * a value
 * Returns int
 */
int
decodeNewStitch(unsigned char value)
{
    return (int)value;
}

/* . */
void
fpad(FILE* file, char c, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        fwrite(&c, 1, 1, file);
    }
}

/* . */
void
emb_write_i16(FILE* f, int16_t data)
{
    char *b = (char*)(&data);
    fix_endian(b, 2, EMB_LITTLE_ENDIAN);
    fwrite(b, 1, 2, f);
}

/* . */
void
emb_write_u16(FILE* f, uint16_t data)
{
    char *b = (char*)(&data);
    fix_endian(b, 2, EMB_LITTLE_ENDIAN);
    fwrite(b, 1, 2, f);
}

/* . */
void
emb_write_i16be(FILE* f, int16_t data)
{
    char *b = (char*)(&data);
    fix_endian(b, 2, EMB_BIG_ENDIAN);
    fwrite(b, 1, 2, f);
}

/* . */
void
emb_write_u16be(FILE* f, uint16_t data)
{
    char *b = (char*)(&data);
    fix_endian(b, 2, EMB_BIG_ENDIAN);
    fwrite(b, 1, 2, f);
}

/* . */
void
emb_write_i32(FILE* f, int32_t data)
{
    char *b = (char*)(&data);
    fix_endian(b, 4, EMB_LITTLE_ENDIAN);
    fwrite(b, 1, 4, f);
}

/* . */
void
emb_write_u32(FILE* f, uint32_t data)
{
    char *b = (char*)(&data);
    fix_endian(b, 4, EMB_LITTLE_ENDIAN);
    fwrite(b, 1, 4, f);
}

/* . */
void
emb_write_i32be(FILE* f, int32_t data)
{
    char *b = (char*)(&data);
    fix_endian(b, 4, EMB_BIG_ENDIAN);
    fwrite(b, 1, 4, f);
}

/* . */
void
emb_write_u32be(FILE* f, uint32_t data)
{
    char *b = (char*)(&data);
    fix_endian(b, 4, EMB_BIG_ENDIAN);
    fwrite(b, 1, 4, f);
}

/* end of encoding section. */

/* The array management for libembroidery's arrays.
 */

/* Allocates memory for an EmbArray of the type determined by
 * the argument a type.
 */
EmbArray*
emb_array_create(int type)
{
    EmbArray *a;
    a = (EmbArray*)malloc(sizeof(EmbArray));
    a->type = type;
    a->length = CHUNK_SIZE;
    a->count = 0;
    switch (type) {
    case EMB_STITCH:
        a->stitch = (EmbStitch*)malloc(CHUNK_SIZE*sizeof(EmbStitch));
        break;
    case EMB_THREAD:
        a->thread = (EmbThread*)malloc(CHUNK_SIZE*sizeof(EmbThread));
        break;
    default:
        a->geometry = (EmbGeometry*)malloc(CHUNK_SIZE*sizeof(EmbGeometry));
        break;
    }
    return a;
}

/* Resizes the array a a to be CHUNK_SIZE entries longer
 * if and only if the amount of room left is less than
 * 3 entries.
 */
int
emb_array_resize(EmbArray *a)
{
    if (a->count < a->length - 3) {
        return 1;
    }
    a->length += CHUNK_SIZE;
    switch (a->type) {
    case EMB_STITCH:
        a->stitch = (EmbStitch*)realloc(a->stitch, a->length*sizeof(EmbStitch));
        if (!a->stitch) {
            /* TODO: Error reporting */
            return 0;
        }
        break;
    case EMB_THREAD:
        a->thread = (EmbThread*)realloc(a->thread, a->length*sizeof(EmbThread));
        if (!a->thread) {
            /* TODO: Error reporting */
            return 0;
        }
        break;
    default:
        a->geometry = (EmbGeometry *)realloc(a->geometry, a->length*sizeof(EmbGeometry));
        if (!a->geometry) {
            /* TODO: Error reporting */
            return 0;
        }
        break;
    }

    return 1;
}

/* Copies all entries in the EmbArray struct from a src to a dst.
 */
void
emb_array_copy(EmbArray *dst, EmbArray *src)
{
    dst = emb_array_create(src->type);
    dst->length = src->length;
    dst->count = src->count;
    emb_array_resize(dst);
    /* BUG: Potential failure to copy path memory, only copy pointers? */

    switch (dst->type) {
    case EMB_STITCH:
        memcpy(dst->stitch, src->stitch, sizeof(EmbStitch)*src->count);
        break;
    case EMB_THREAD:
        memcpy(dst->thread, src->thread, sizeof(EmbThread)*src->count);
        break;
    default:
        memcpy(dst->geometry, src->geometry, sizeof(EmbGeometry)*src->count);
        break;
    }
}

/* Add a circle a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_add_circle(EmbArray *a, EmbCircle b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.circle = b;
    a->geometry[a->count - 1].type = EMB_CIRCLE;
    return 1;
}

/* Add an ellipse a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_add_ellipse(EmbArray *a, EmbEllipse b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.ellipse = b;
    a->geometry[a->count - 1].type = EMB_ELLIPSE;
    return 1;
}

/* Add a flag a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_add_flag(EmbArray *a, EmbFlag b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].flag = b;
    a->geometry[a->count - 1].type = EMB_FLAG;
    return 1;
}

/* Add a line a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addLine(EmbArray *a, EmbLine b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.line = b;
    a->geometry[a->count - 1].type = EMB_LINE;
    return 1;
}

/* Add a path a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addPath(EmbArray *a, EmbPath b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.path = b;
    a->geometry[a->count - 1].type = EMB_PATH;
    return 1;
}

/* Add a point a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addPoint(EmbArray *a, EmbPoint b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.point = b;
    a->geometry[a->count - 1].type = EMB_POINT;
    return 1;
}

/* Add a polyline a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addPolyline(EmbArray *a, EmbPolyline b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.polyline = b;
    a->geometry[a->count - 1].type = EMB_POLYLINE;
    return 1;
}

/* Add a polygon a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addPolygon(EmbArray *a, EmbPolygon b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.polygon = b;
    a->geometry[a->count - 1].type = EMB_POLYGON;
    return 1;
}

/* Add a rectangle a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addRect(EmbArray *a, EmbRect b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.rect = b;
    a->geometry[a->count - 1].type = EMB_RECT;
    return 1;
}

/* Add a stitch a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addStitch(EmbArray *a, EmbStitch b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->stitch[a->count - 1] = b;
    return 1;
}


/* Add a generic geometry to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_add_geometry(EmbArray *a, EmbGeometry g)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1] = g;
    return 1;
}

/* Add a vector a b to the EmbArray a a and it returns if the
 * element was successfully added.
 */
int
emb_array_addVector(EmbArray *a, EmbVector b)
{
    a->count++;
    if (!emb_array_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.vector = b;
    a->geometry[a->count - 1].type = EMB_VECTOR;
    return 1;
}

/* Free the memory of EmbArray a a, recursively if necessary.
 */
void
emb_array_free(EmbArray* a)
{
    if (!a) {
        return;
    }
    switch (a->type) {
    case EMB_STITCH:
        safe_free(a->stitch);
        break;
    case EMB_THREAD:
        safe_free(a->thread);
        break;
    default: {
        int i;
        for (i = 0; i < a->count; i++) {
            EmbGeometry g = a->geometry[i];
            switch (a->geometry[i].type) {
            case EMB_PATH: {
                emb_array_free(g.object.path.pointList);
                break;
            }
            case EMB_POLYGON: {
                emb_array_free(g.object.polygon.pointList);
                break;
            }
            case EMB_POLYLINE: {
                emb_array_free(g.object.polyline.pointList);
                break;
            }
            default:
                break;
            }
        }
        safe_free(a->geometry);
        break;
    }
    }
    safe_free(a);
}

/* Print the vector "v2 with the name "label". */
void emb_vector_print(EmbVector v, char *label)
{
    printf("%sX = %f\n", label, v.x);
    printf("%sY = %f\n", label, v.y);
}

/* Print the arc "arc". */
void emb_arc_print(EmbArc arc)
{
    emb_vector_print(arc.start, "start");
    emb_vector_print(arc.mid, "middle");
    emb_vector_print(arc.end, "end");
}

/* Checks that there are enough bytes to interpret the header,
 * stops possible segfaults when reading in the header bytes.
 *
 * Returns 0 if there aren't enough, or the length of the file
 * if there are.
 */
int
check_header_present(FILE* file, int minimum_header_length)
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

/* sectorSize based on the bcfFile version. */
unsigned int
sectorSize(bcf_file* bcfFile)
{
    /* version 3 uses 512 byte */
    if (bcfFile->header.majorVersion == 3) {
        return 512;
    }
    return 4096;
}

/* . */
int
haveExtraDIFATSectors(bcf_file* file)
{
    return (int)(entriesInDifatSector(file->difat) > 0);
}

/* . */
int
seekToSector(bcf_file* bcfFile, FILE* file, const unsigned int sector)
{
    unsigned int offset = sector * sectorSize(bcfFile) + sectorSize(bcfFile);
    return fseek(file, offset, SEEK_SET);
}

/* . */
void
parseDIFATSectors(FILE* file, bcf_file* bcfFile)
{
    unsigned int difatEntriesToRead = bcfFile->header.numberOfFATSectors - difatEntriesInHeader;
    unsigned int difatSectorNumber = bcfFile->header.firstDifatSectorLocation;
    while ((difatSectorNumber != CompoundFileSector_EndOfChain) && (difatEntriesToRead > 0)) {
        seekToSector(bcfFile, file, difatSectorNumber);
        difatSectorNumber = readFullSector(file, bcfFile->difat, &difatEntriesToRead);
    }
}

/* . */
int
bcfFile_read(FILE* file, bcf_file* bcfFile)
{
    unsigned int i, numberOfDirectoryEntriesPerSector;
    unsigned int directorySectorToReadFrom;

    bcfFile->header = bcfFileHeader_read(file);
    if (memcmp(bcfFile->header.signature, "\xd0\xcf\x11\xe0\xa1\xb1\x1a\xe1", 8) != 0) {
        printf("bad header signature\n");
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

/* Get the File object. */
void*
GetFile(bcf_file* bcfFile, FILE* file, char* fileToFind)
{
    int filesize, sectorSize, currentSector;
    int sizeToWrite, currentSize, totalSectors, i, j;
    FILE* fileOut = tmpfile();
    bcf_directory_entry* pointer = bcfFile->directory->dirEntries;
    while (pointer) {
        if (!strcmp(fileToFind, pointer->directoryEntryName)) {
            break;
        }
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
            if (fread(&input, 1, 1, file) != 1) {
                /* TODO: Needs an error code. */
                puts("ERROR: GetFile failed to read byte.");
                return fileOut;
            }
            if (fwrite(&input, 1, 1, fileOut) != 1) {
                /* TODO: Needs an error code. */
                puts("ERROR: GetFile failed to read byte.");
                return fileOut;
            }
        }
        currentSize += sizeToWrite;
        currentSector = bcfFile->fat->fatEntries[currentSector];
    }
    return fileOut;
}

/* . */
void
bcf_file_free(bcf_file* bcfFile)
{
    safe_free(bcfFile->difat);
    safe_free(bcfFile->fat);
    bcf_directory_free(&bcfFile->directory);
    safe_free(bcfFile);
}

/* . */
bcf_file_difat*
bcf_difat_create(FILE* file, unsigned int fatSectors, const unsigned int sectorSize)
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
    if (fatSectors > difatEntriesInHeader) {
        fatSectors = difatEntriesInHeader;
    }

    for (i = 0; i < fatSectors; ++i) {
        sectorRef = emb_read_i32(file);
        difat->fatSectorEntries[i] = sectorRef;
    }
    difat->fatSectorCount = fatSectors;
    for (i = fatSectors; i < difatEntriesInHeader; ++i) {
        sectorRef = emb_read_i32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf("ERROR: compound-file-difat.c bcf_difat_create(), Unexpected sector value %x at DIFAT[%d]\n", sectorRef, i);
        }
    }
    return difat;
}

/* . */
unsigned int
entriesInDifatSector(bcf_file_difat* fat)
{
    return (fat->sectorSize - sizeOfChainingEntryAtEndOfDifatSector) / sizeOfDifatEntry;
}

/* . */
unsigned int
readFullSector(
    FILE* file,
    bcf_file_difat* bcfFile,
    unsigned int* difatEntriesToRead)
{
    unsigned int i;
    unsigned int sectorRef;
    unsigned int nextDifatSectorInChain;
    unsigned int entriesToReadInThisSector = 0;
    if (*difatEntriesToRead > entriesInDifatSector(bcfFile)) {
        entriesToReadInThisSector = entriesInDifatSector(bcfFile);
        *difatEntriesToRead -= entriesToReadInThisSector;
    }
    else {
        entriesToReadInThisSector = *difatEntriesToRead;
        *difatEntriesToRead = 0;
    }

    for (i = 0; i < entriesToReadInThisSector; ++i) {
        sectorRef = emb_read_i32(file);
        bcfFile->fatSectorEntries[bcfFile->fatSectorCount] = sectorRef;
        bcfFile->fatSectorCount++;
    }
    for (i = entriesToReadInThisSector; i < entriesInDifatSector(bcfFile); ++i) {
        sectorRef = emb_read_i32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf("ERROR: compound-file-difat.c readFullSector(), ");
            printf("Unexpected sector value %x at DIFAT[%d]]\n", sectorRef, i);
        }
    }
    nextDifatSectorInChain = emb_read_i32(file);
    return nextDifatSectorInChain;
}

/* . */
void
parseDirectoryEntryName(FILE* file, bcf_directory_entry* dir)
{
    int i;
    for (i = 0; i < 32; ++i) {
        uint16_t unicodechar = emb_read_i16(file);
        if (unicodechar != 0x0000) {
            dir->directoryEntryName[i] = (char)unicodechar;
        }
    }
}

/* . */
bcf_directory*
CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries)
{
    bcf_directory* dir = (bcf_directory*)malloc(sizeof(bcf_directory));
    if (!dir) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectory(), cannot allocate memory for dir\n");
        return NULL;
    } /* TODO: avoid crashing. null pointer will be accessed */
    dir->maxNumberOfDirectoryEntries = maxNumberOfDirectoryEntries;
    dir->dirEntries = 0;
    return dir;
}

/* . */
EmbTime
parseTime(FILE* file)
{
    EmbTime returnVal;
    unsigned int ft_low, ft_high;
    /*embTime_time(&returnVal); TODO: use embTime_time() rather than time(). */
    ft_low = emb_read_i32(file);
    ft_high = emb_read_i32(file);
    printf("%u %u\n", ft_low, ft_high);
    /* TODO: translate to actual date time */
    returnVal.day = 1;
    returnVal.hour = 2;
    returnVal.minute = 3;
    returnVal.month = 4;
    returnVal.second = 5;
    returnVal.year = 6;
    return returnVal;
}

/* . */
bcf_directory_entry*
CompoundFileDirectoryEntry(FILE* file)
{
    int i;
    const int guidSize = 16;
    bcf_directory_entry* dir = malloc(sizeof(bcf_directory_entry));
    if (dir == NULL) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectoryEntry(), cannot allocate memory for dir\n");
        return NULL;
    }
    memset(dir->directoryEntryName, 0, 32);
    parseDirectoryEntryName(file, dir);
    dir->next = 0;
    dir->directoryEntryNameLength = emb_read_u16(file);
    dir->objectType = (unsigned char)fgetc(file);
    if ((dir->objectType != ObjectTypeStorage) && (dir->objectType != ObjectTypeStream) && (dir->objectType != ObjectTypeRootEntry)) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectoryEntry()");
        printf(", unexpected object type: %d\n", dir->objectType);
        return NULL;
    }
    dir->colorFlag = (unsigned char)fgetc(file);
    dir->leftSiblingId = emb_read_i32(file);
    dir->rightSiblingId = emb_read_i32(file);
    dir->childId = emb_read_i32(file);
    if (fread(dir->CLSID, 1, guidSize, file) < guidSize) {
        printf("ERROR: Failed to read guidSize bytes for CLSID");
        return dir;
    }
    dir->stateBits = emb_read_i32(file);
    for (i=0; i<6; i++) {
        dir->creationTime[i] = emb_read_i32(file);
    }
    for (i=0; i<6; i++) {
        dir->modifiedTime[i] = emb_read_i32(file);
    }
    dir->startingSectorLocation = emb_read_i32(file);
    /* StreamSize should really be __int64 or long long,
     * but for our uses we should never run into an issue */
    dir->streamSize = emb_read_i32(file);
    /* top portion of int64 */
    dir->streamSizeHigh = emb_read_i32(file);
    return dir;
}

/* . */
void
readNextSector(FILE* file, bcf_directory* dir)
{
    unsigned int i;
    for (i = 0; i < dir->maxNumberOfDirectoryEntries; ++i) {
        bcf_directory_entry* dirEntry = CompoundFileDirectoryEntry(file);
        bcf_directory_entry* pointer = dir->dirEntries;
        if (!pointer) {
            dir->dirEntries = dirEntry;
        }
        else {
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

/* . */
void
bcf_directory_free(bcf_directory** dir)
{
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
        safe_free(entryToFree);
    }
    safe_free(*dir);
}

/* . */
bcf_file_fat*
bcfFileFat_create(const unsigned int sectorSize)
{
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

/* . */
void
loadFatFromSector(bcf_file_fat* fat, FILE* file)
{
    unsigned int i;
    unsigned int current_fat_entries = fat->fatEntryCount;
    unsigned int newSize = current_fat_entries + fat->numberOfEntriesInFatSector;
    for (i = current_fat_entries; i < newSize; ++i) {
        fat->fatEntries[i] = emb_read_i32(file);
    }
    fat->fatEntryCount = newSize;
}

/* . */
bcf_file_header
bcfFileHeader_read(FILE* file)
{
    bcf_file_header header;
    if (fread(header.signature, 1, 8, file) < 8) {
        puts("ERROR: failed to read signature bytes from bcf file.");
        return header;
    }
    if (fread(header.CLSID, 1, 16, file) < 16) {
        puts("ERROR: failed to read CLSID bytes from bcf file.");
        return header;
    }
    header.minorVersion = emb_read_u16(file);
    header.majorVersion = emb_read_u16(file);
    header.byteOrder = emb_read_u16(file);
    header.sectorShift = emb_read_u16(file);
    header.miniSectorShift = emb_read_u16(file);
    header.reserved1 = emb_read_u16(file);
    header.reserved2 = emb_read_i32(file);
    header.numberOfDirectorySectors = emb_read_i32(file);
    header.numberOfFATSectors = emb_read_i32(file);
    header.firstDirectorySectorLocation = emb_read_i32(file);
    header.transactionSignatureNumber = emb_read_i32(file);
    header.miniStreamCutoffSize = emb_read_i32(file);
    header.firstMiniFATSectorLocation = emb_read_i32(file);
    header.numberOfMiniFatSectors = emb_read_i32(file);
    header.firstDifatSectorLocation = emb_read_i32(file);
    header.numberOfDifatSectors = emb_read_i32(file);
    return header;
}

/* . */
int
emb_generate_satin_outline(EmbArray *lines, EmbReal thickness, EmbSatinOutline* result)
{
    int i;
    EmbLine line1, line2;
    EmbSatinOutline outline;
    EmbVector out;
    EmbVector v1;
    EmbVector temp;
    EmbLine line;

    EmbReal halfThickness = thickness / 2.0;
    int intermediateOutlineCount = 2 * lines->count - 2;
    outline.side1 = emb_array_create(EMB_VECTOR);
    if (!outline.side1) {
        printf("ERROR: emb_generate_satin_outline(), cannot allocate memory for outline->side1\n");
        return 0;
    }
    outline.side2 = emb_array_create(EMB_VECTOR);
    if (!outline.side2) {
        printf("ERROR: emb_generate_satin_outline(), cannot allocate memory for outline->side2\n");
        return 0;
    }

    for (i = 1; i < lines->count; i++) {
        line.start = lines->geometry[i - 1].object.vector;
        line.end = lines->geometry[i].object.vector;

        v1 = emb_line_normalVector(line, 1);

        temp = emb_vector_scale(v1, halfThickness);
        temp = emb_vector_add(temp, lines->geometry[i-1].object.vector);
        emb_array_addVector(outline.side1, temp);
        temp = emb_vector_add(temp, lines->geometry[i].object.vector);
        emb_array_addVector(outline.side1, temp);

        temp = emb_vector_scale(v1, -halfThickness);
        temp = emb_vector_add(temp, lines->geometry[i - 1].object.vector);
        emb_array_addVector(outline.side2, temp);
        temp = emb_vector_add(temp, lines->geometry[i].object.vector);
        emb_array_addVector(outline.side2, temp);
    }

    if (!result) {
        printf("ERROR: emb_generate_satin_outline(), result argument is null\n");
        return 0;
    }
    result->side1 = emb_array_create(EMB_VECTOR);
    if (!result->side1) {
        printf("ERROR: emb_generate_satin_outline(), cannot allocate memory for result->side1\n");
        return 0;
    }
    result->side2 = emb_array_create(EMB_VECTOR);
    if (!result->side2) {
        printf("ERROR: emb_generate_satin_outline(), cannot allocate memory for result->side2\n");
        return 0;
    }

    emb_array_addVector(result->side1, outline.side1->geometry[0].object.vector);
    emb_array_addVector(result->side2, outline.side2->geometry[0].object.vector);

    for (i = 3; i < intermediateOutlineCount; i += 2) {
        int emb_error = 0;
        line1.start = outline.side1->geometry[i - 3].object.vector;
        line1.end = outline.side1->geometry[i - 2].object.vector;
        line2.start = outline.side1->geometry[i - 1].object.vector;
        line2.end = outline.side1->geometry[i].object.vector;
        out = emb_line_intersectionPoint(line1, line2, &emb_error);
        if (emb_error) {
            puts("No intersection point.");
        }
        emb_array_addVector(result->side1, out);

        line1.start = outline.side2->geometry[i - 3].object.vector;
        line1.end = outline.side2->geometry[i - 2].object.vector;
        line2.start = outline.side2->geometry[i - 1].object.vector;
        line2.end = outline.side2->geometry[i].object.vector;
        out = emb_line_intersectionPoint(line1, line2, &emb_error);
        if (emb_error) {
            puts("No intersection point.");
        }
        emb_array_addVector(result->side2, out);
    }

    emb_array_addVector(result->side1, outline.side1->geometry[2 * lines->count - 3].object.vector);
    emb_array_addVector(result->side2, outline.side2->geometry[2 * lines->count - 3].object.vector);
    result->length = lines->count;
    return 1;
}

/* . */
EmbArray*
emb_satin_outline_render(EmbSatinOutline* result, EmbReal density)
{
    int i, j;
    EmbVector currTop, currBottom, topDiff, bottomDiff, midDiff;
    EmbVector midLeft, midRight, topStep, bottomStep;
    EmbArray* stitches = 0;
    int numberOfSteps;
    EmbReal midLength;

    if (!result) {
        printf("ERROR: emb_satin_outline_render(), result argument is null\n");
        return 0;
    }

    if (result->length > 0) {
        for (j = 0; j < result->length - 1; j++) {
            EmbGeometry *g10 = &(result->side1->geometry[j+0]);
            EmbGeometry *g11 = &(result->side1->geometry[j+1]);
            EmbGeometry *g20 = &(result->side2->geometry[j+0]);
            EmbGeometry *g21 = &(result->side2->geometry[j+1]);
            topDiff = emb_vector_subtract(g10->object.vector, g11->object.vector);
            bottomDiff = emb_vector_subtract(g21->object.vector, g20->object.vector);

            midLeft = emb_vector_average(g10->object.vector, g20->object.vector);
            midRight = emb_vector_average(g11->object.vector, g21->object.vector);

            midDiff = emb_vector_subtract(midLeft, midRight);
            midLength = emb_vector_length(midDiff);

            numberOfSteps = (int)(midLength * density / 200);
            topStep = emb_vector_scale(topDiff, 1.0/numberOfSteps);
            bottomStep = emb_vector_scale(bottomDiff, 1.0/numberOfSteps);
            currTop = g10->object.vector;
            currBottom = g20->object.vector;

            for (i = 0; i < numberOfSteps; i++) {
                if (!stitches) {
                    stitches = emb_array_create(EMB_VECTOR);
                }
                emb_array_addVector(stitches, currTop);
                emb_array_addVector(stitches, currBottom);
                currTop = emb_vector_add(currTop, topStep);
                currBottom = emb_vector_add(currBottom, bottomStep);
            }
        }
        emb_array_addVector(stitches, currTop);
        emb_array_addVector(stitches, currBottom);
    }
    return stitches;
}

/* . */
void
write_24bit(FILE* file, int x)
{
    unsigned char a[4];
    a[0] = (unsigned char)0;
    a[1] = (unsigned char)(x & 0xFF);
    a[2] = (unsigned char)((x >> 8) & 0xFF);
    a[3] = (unsigned char)((x >> 16) & 0xFF);
    fwrite(a, 1, 4, file);
}

/* . */
int
embColor_distance(EmbColor a, EmbColor b)
{
    int t;
    t = (a.r-b.r)*(a.r-b.r);
    t += (a.g-b.g)*(a.g-b.g);
    t += (a.b-b.b)*(a.b-b.b);
    return t;
}

/* . */
void
embColor_read(void *f, EmbColor *c, int toRead)
{
    unsigned char b[4];
    if (fread(b, 1, toRead, f) < (unsigned int)toRead) {
        puts("ERROR: Failed to read embColor bytes.");
        return;
    }
    c->r = b[0];
    c->g = b[1];
    c->b = b[2];
}

/* . */
void
embColor_write(void *f, EmbColor c, int toWrite)
{
    unsigned char b[4];
    b[0] = c.r;
    b[1] = c.g;
    b[2] = c.b;
    b[3] = 0;
    fwrite(b, 1, toWrite, f);
}

/* Returns the closest color to the required color based on
 * a list of available threads. The algorithm is a simple least
 * squares search against the list. If the (square of) Euclidean 3-dimensional
 * distance between the points in (red, green, blue) space is smaller
 * then the index is saved and the remaining index is returned to the
 * caller.
 *
 * color:  The EmbColor color to match.
 * colors: The EmbThreadList pointer to start the search at.
 * mode:   Is the argument an array of threads (0) or colors (1)?
 * Returns closestIndex: The entry in the ThreadList that matches.
 */
int
emb_find_nearest_color(EmbColor color, EmbColor *color_list, int n_colors)
{
    int currentClosestValue = 256*256*3;
    int closestIndex = -1, i;
    for (i = 0; i < n_colors; i++) {
        int delta = embColor_distance(color, color_list[i]);

        if (delta <= currentClosestValue) {
            currentClosestValue = delta;
            closestIndex = i;
        }
    }
    return closestIndex;
}

/* The maximum distance. */
int
emb_find_nearest_thread(EmbColor color, EmbThread *thread_list, int n_threads)
{
    int currentClosestValue = 256*256*3;
    int closestIndex = -1, i;
    for (i = 0; i < n_threads; i++) {
        int delta = embColor_distance(color, thread_list[i].color);

        if (delta <= currentClosestValue) {
            currentClosestValue = delta;
            closestIndex = i;
        }
    }
    return closestIndex;
}

/*
 * Returns a random thread color, useful in filling in cases where the
 * actual color of the thread doesn't matter but one needs to be declared
 * to test or render a pattern.
 *
 * Returns c: The resulting color.
 */
EmbThread
emb_get_random_thread(void)
{
    EmbThread c;
    c.color.r = rand()%256;
    c.color.g = rand()%256;
    c.color.b = rand()%256;
    strcpy(c.description, "random");
    strcpy(c.catalogNumber, "");
    return c;
}

/* . */
void
binaryReadString(FILE* file, char* buffer, int maxLength)
{
    int i = 0;
    while (i < maxLength) {
        buffer[i] = (char)fgetc(file);
        if (buffer[i] == '\0') {
            break;
        }
        i++;
    }
}

/* . */
void
binaryReadUnicodeString(FILE* file, char *buffer, const int stringLength)
{
    int i = 0;
    for (i = 0; i < stringLength * 2; i++) {
        char input = (char)fgetc(file);
        if (input != 0) {
            buffer[i] = input;
        }
    }
}

/*
 * Tests for the presence of a string a s in the supplied
 * a array.
 *
 * The end of the array is marked by an empty string.
 *
 * Returns 0 if not present 1 if present.
 */
int
stringInArray(const char *s, const char **array)
{
    int i;
    for (i = 0; string_len(array[i]); i++) {
        if (!strncmp(s, array[i], 200)) {
            return 1;
        }
    }
    return 0;
}

/* . */
int
emb_readline(FILE* file, char *line, int maxLength)
{
    int i;
    char c;
    for (i = 0; i < maxLength-1; i++) {
        if (!fread(&c, 1, 1, file)) {
            break;
        }
        if (c == '\r') {
            if (fread(&c, 1, 1, file) != 1) {
                /* Incomplete Windows-style line ending. */
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
    return i;
}

/* TODO: description */

/* Get the trim bounds object. */
void
get_trim_bounds(char const *s, char const **firstWord, char const **trailingSpace)
{
    char const* lastWord = 0;
    *firstWord = lastWord = s + string_whitespace(s);
    do {
        *trailingSpace = lastWord + string_whitespace(lastWord);
        lastWord = *trailingSpace + string_whitespace(*trailingSpace);
    } while (*lastWord != '\0');
}

/* . */
char*
copy_trim(char const *s)
{
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

/* Optimizes the number (a num) for output to a text file and returns
 * it as a string (a str).
 */
char*
emb_optOut(EmbReal num, char* str)
{
    char *str_end;
    /* Convert the number to a string */
    sprintf(str, "%.10f", num);
    /* Remove trailing zeroes */
    str_end = str + string_len(str);
    while (*--str_end == '0');
    str_end[1] = 0;
    /* Remove the decimal point if it happens to be an integer */
    if (*str_end == '.') {
        *str_end = 0;
    }
    return str;
}

/* . */
void
embTime_initNow(EmbTime* t)
{
    printf("%d", t->year);
    /*
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
    */
}

/* . */
EmbTime
embTime_time(EmbTime* t)
{
    int divideByZero = 0;
    divideByZero = divideByZero/divideByZero;
    /* TODO: wrap time() from time.h and verify it works consistently */

    return *t;
}

/* . */
void
formats(void)
{
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
		if (formatTable[i].reader_state != ' ') {
			numReaders++;
		}
		if (formatTable[i].writer_state != ' ') {
			numWriters++;
		}
        printf("|  %-4s  |   %c   |   %c   |  %-49s |\n",
     		formatTable[i].extension,
			formatTable[i].reader_state,
			formatTable[i].writer_state,
			formatTable[i].description);
    }

    printf("|________|_______|_______|____________________________________________________|\n");
    printf("|        |       |       |                                                    |\n");
    printf("| Total: |  %3d  |  %3d  |                                                    |\n", numReaders, numWriters);
    printf("|________|_______|_______|____________________________________________________|\n");
    puts("");
}

/* . */
void
to_flag(char **argv, int argc, int i)
{
    if (i + 2 < argc) {
        int j;
        EmbString output_fname;
        int format;
        sprintf(output_fname, "example.%s", argv[i+1]);
        format = emb_identify_format(output_fname);
        if (format < 0) {
            puts("Error: format unrecognised.");
        }
        for (j=i+2; j<argc; j++) {
            int length = string_len(argv[j]);
            output_fname[0] = 0;
            strcpy(output_fname, argv[j]);
            output_fname[length-4] = 0;
            strcat(output_fname, formatTable[format].extension);
            printf("Converting %s to %s.\n",
                argv[j], output_fname);
            convert(argv[j], output_fname);
        }
    }
    else {
        puts("Usage of the to flag is:");
        puts("    embroider -t FORMAT FILE(S)");
        puts("but it appears you entered less than 3 arguments to embroider.");
    }
}

/* a points a n_points a width a tolerence
 *
 * Remove points that lie in the middle of two short stitches that could
 * be one longer stitch. Repeat until none are found.
 */
static void
join_short_stitches(int *points, int *n_points, int width, int tolerence)
{
    int found = 1;
    while (found > 0) {
        int i;
        found = 0;
        for (i=*n_points-2; i>=0; i--) {
            int st1 = points[i+1]%width - points[i]%width;
            int st2 = points[i+2]%width - points[i+1]%width;
            int same_line = (points[i+1]/width == points[i]/width)
                            && (points[i+2]/width == points[i+1]/width);
            if (st1 < tolerence && st2 < tolerence && same_line) {
                found++;
                break;
            }
        }
        if (found) {
            /* Remove the point. */
            i++;
            for (; i<*n_points; i++) {
                points[i] = points[i+1];
            }
            (*n_points)--;
        }
    }
}

/* a image a n_points a subsample_width a subsample_height
 * a threshold
 * Returns int*
 *
 * Identify darker pixels to put stitches in.
 */
static int *
threshold_method(EmbImage *image, int *n_points,
    int subsample_width, int subsample_height, int threshold)
{
    int i, j;
    int *points;
    int height = image->height;
    int width = image->width;
    points = (int *)malloc((height/subsample_height)
        *(width/subsample_width) * sizeof(int));
    *n_points = 0;
    for (i=0; i<height/subsample_height; i++)
    for (j=0; j<width/subsample_width; j++) {
        EmbColor color;
        int index = subsample_height*i*width+subsample_width*j;
        color.r = image->data[3*index+0];
        color.g = image->data[3*index+1];
        color.b = image->data[3*index+2];
        if (color.r+color.g+color.b < threshold) {
            points[*n_points] = index;
            (*n_points)++;
        }
    }
    return points;
}

/* a points a n_points a width a bias
 *
 * Greedy Algorithm
 * ----------------
 * For each point in the list find the shortest distance to
 * any possible neighbour, then perform a swap to make that
 * neighbour the next item in the list.
 *
 * To make the stitches lie more on one axis than the other
 * bias the distance operator to prefer horizontal direction.
 */
static void
greedy_algorithm(int *points, int n_points, int width, EmbReal bias)
{
    int i, j;
    printf("points[0] = %d\n", points[0]);
    printf("n_points = %d\n", n_points);
    printf("width = %d\n", width);
    printf("bias = %f\n", bias);

    for (i=0; i<n_points-1; i++) {
        int stor;
        EmbReal shortest = 1.0e20;
        int next = i+1;
        /* Find nearest neighbour. */
        int x1 = points[i]%width;
        int y1 = points[i]/width;
        for (j=i+1; j<n_points; j++) {
            int x, y;
            EmbReal distance;
            x = x1 - (points[j]%width);
            if (x*x > shortest) {
                continue;
            }
            y = y1 - (points[j]/width);
            distance = x*x + bias*y*y;
            if (distance < shortest) {
                next = j;
                shortest = distance;
            }
        }
        if (i%100 == 0) {
            printf("%2.1f%%\n", (100.0*i)/(1.0*n_points));
        }
        /* swap points */
        stor = points[next];
        points[next] = points[i+1];
        points[i+1] = stor;
    }
}

/* a pattern a points a n_points
 * a scale a width a height
 */
static void
save_points_to_pattern(
    EmbPattern *pattern, int *points, int n_points, EmbReal scale, int width, int height)
{
    int i;
    for (i=0; i<n_points; i++) {
        int x, y;
        x = points[i]%width;
        y = height - points[i]/width;
        emb_pattern_addStitchAbs(pattern, scale*x, scale*y, NORMAL, 0);
    }
}

/* a pattern a image a threshhold
 *
 * Uses a threshhold method to determine where to put
 * lines in the fill.
 *
 * Needs to pass a "donut test", i.e. an image with black pixels where:
 *     10 < x*x + y*y < 20
 * over the area (-30, 30) x (-30, 30).
 *
 * Use render then image difference to see how well it passes.
 */
void
emb_pattern_horizontal_fill(EmbPattern *pattern, EmbImage *image, int threshhold)
{
    /* Size of the crosses in millimeters. */
    EmbReal scale = 0.1;
    int sample_w = 3;
    int sample_h = 3;
    EmbReal bias = 1.2;
    int *points;
    int n_points;

    points = threshold_method(image, &n_points, sample_w, sample_h, threshhold);
    greedy_algorithm(points, n_points, image->width, bias);
    join_short_stitches(points, &n_points, image->width, 40);
    save_points_to_pattern(pattern, points, n_points, scale, image->width, image->height);

    emb_pattern_end(pattern);
    safe_free(points);
}

/* a pattern a image a threshhold
 *
 * Uses a threshhold method to determine where to put
 * crosses in the fill.
 *
 * To improve this, we can remove the vertical stitches when two crosses
 * neighbour. Currently the simple way to do this is to chain crosses
 * that are neighbours exactly one ahead.
 */
void
emb_pattern_crossstitch(EmbPattern *pattern, EmbImage *image, int threshhold)
{
    int i;
    /* Size of the crosses in millimeters. */
    EmbReal scale = 0.1;
    int sample_w = 5;
    int sample_h = 5;
    EmbReal bias = 1.0;
    int *points;
    int n_points;
    int width = 1000;
    points = threshold_method(image, &n_points, sample_w, sample_h, threshhold);
    greedy_algorithm(points, n_points, width, bias);

    for (i=0; i<n_points; i++) {
        EmbReal x, y;
        x = points[i]%width;
        y = points[i]/width;
        printf("%f %f\n", x, y);
        emb_pattern_addStitchAbs(pattern, scale*x, scale*y, NORMAL, 0);
        emb_pattern_addStitchAbs(pattern, scale*(x+sample_w), scale*(y+sample_h), NORMAL, 0);
        emb_pattern_addStitchAbs(pattern, scale*x, scale*(y+sample_h), NORMAL, 0);
        emb_pattern_addStitchAbs(pattern, scale*(x+sample_w), scale*y, NORMAL, 0);
    }

    emb_pattern_end(pattern);
}

#if 0
/* a pattern
 * Returns StitchBlock*
 */
StitchBlock*
BreakIntoColorBlocks(EmbPattern *pattern)
{
    int i;
    int sa2 = new StitchBlock();
    int oldColor = pattern->stitch_list->stitch[0].color;
    int color = pattern.ColorList[oldColor];
    sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch s = pattern->stitch_list->stitch[i];
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

/* a blocks
 * Returns StitchBlock*
 */
StitchBlock *
BreakIntoSeparateObjects(EmbStitchBlock* blocks)
{
    int i, block;
    EmbReal previousAngle = 0.0;
    for (block=0; block<blocks->length; block++) {
        int stitches = new List<VectorStitch>();
        block.Stitches[0].Type = VectorStitchType.Contour;
        block.Stitches[block.Stitches.Count - 1].Type = VectorStitchType.Contour;

        for (int i = 0; i < block.Stitches.Count - 2; i++) { /* step 0 */
            EmbReal dx = (emb_vector_relativeX(block.Stitches[i].Xy, block.Stitches[i + 1].Xy, block.Stitches[i + 2].Xy));
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
                float dy = emb_vector_relativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY);
                float dy2 = emb_vector_relativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY);
                float dy3 = emb_vector_relativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY);
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

/* a stitchData
 * Returns StitchObject*
 */
StitchObject *
FindOutline(EmbStitchBlock* stitchData)
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
                sa.Stitches[i].Angle = emb_vector_angle(sa.Stitches[i], sa.Stitches[i + 1]);
            }
            /* step 1 */
            for (int i = 1; i < sa.Stitches.Count - 3; i++) {
                if (sa.Stitches[i + 1].Type == VectorStitchType.Contour) {
                    float dy = emb_vector_relativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY);
                    float dy2 = emb_vector_relativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY);
                    float dy3 = emb_vector_relativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY);
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

/* a p
 * Returns EmbPattern
 */
EmbPattern
DrawGraphics(EmbPattern p)
{
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
                outPattern.stitch_list.Add(new Stitch(stitchObject.SideOne[0].X, stitchObject.SideOne[0].Y,
                                                     StitchType.Jump, colorIndex));
            }
            foreach (Point t in stitchObject.SideOne) {

                outPattern.stitch_list.Add(new Stitch(t.X, t.Y,
                                                     StitchType.Normal, colorIndex));
            }
            foreach (Point t in stitchObject.SideTwo) {
                outPattern.stitch_list.Add(new Stitch(t.X, t.Y,
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

/* a pattern
 * Returns EmbPattern
 */
EmbPattern
SimplifyOutline(EmbPattern pattern)
{
    int v = new Vertices();
    v.AddRange(pattern.stitch_list.Select(point => new Vector2(point.X, point.Y)));
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
EmbReal _distanceTolerance;

/* Removes all collinear points on the polygon.
 *
 * a vertices
 * a collinearityTolerance
 * Returns Vertices
 */
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
        if (emb_vector_collinear(ref prev, ref current, ref next, collinearityTolerance))
            continue;

        simplified.Add(current);
    }

    return simplified;
}

/* vertices
 * Returns Vertices
 *
 * Removes all collinear points on the polygon. Has a default bias of 0.
 *
 * param vertices: The polygon that needs simplification.
 * returns: A simplified polygon.
 */
Vertices
CollinearSimplify(Vertices vertices)
{
    return CollinearSimplify(vertices, 0);
}

/* vertices
 * a distanceTolerance
 * Returns Vertices
 *
 * Ramer-Douglas-Peucker polygon simplification algorithm.
 * This is the general recursive version that does not use the
 * speed-up technique by using the Melkman convex hull.
 * If you pass in 0, it will remove all collinear points.
 *
 * \todo Ramer-Douglas-Peucker citation
 */
Vertices
DouglasPeuckerSimplify(Vertices vertices, float distanceTolerance)
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

/*  vertices a i a j */
void
SimplifySection(Vertices vertices, int i, int j)
{
    if ((i + 1) == j)
        return;

    Vector2 a = vertices[i];
    Vector2 b = vertices[j];
    EmbReal maxDistance = -1.0;
    int maxIndex = i;
    for (int k = i + 1; k < j; k++)
    {
        EmbReal distance = DistancePointLine(vertices[k], a, b);

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

/* p a a a b
 * Returns EmbReal
 */
EmbReal
DistancePointLine(EmbVector p, EmbVector a, EmbVector b)
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

    EmbReal r = ((p.X - a.X) * (b.X - a.X) + (p.Y - a.Y) * (b.Y - a.Y))
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

    EmbReal s = ((a.Y - p.Y) * (b.X - a.X) - (a.X - p.X) * (b.Y - a.Y))
               /
               ((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y));

    return fabs(s) * sqrt(((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y)));
}

/* vertices a areaTolerance
 * Returns public
 *
 * From physics2d.net.
 */
public Vertices
ReduceByArea(Vertices vertices, float areaTolerance)
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

/* vertices a tolerance
 *
 * From Eric Jordan's convex decomposition library.
 * Merges all parallel edges in the list of vertices.
 */
void
MergeParallelEdges(EmbArray *vertices, float tolerance)
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

        delta0 = emb_vector_subtract(vertices[i], vertices[lower]);
        delta1 = emb_vector_subtract(vertices[upper], vertices[i]);
        float norm0 = emb_vector_length(delta0);
        float norm1 = emb_vector_length(delta0);

        if (!(norm0 > 0.0f && norm1 > 0.0f) && newNVertices > 3) {
            /* Merge identical points */
            mergeMe[i] = 1;
            newNVertices--;
        }

        delta0 = emb_vector_normalize(delta0);
        delta1 = emb_vector_normalize(delta1);
        float cross = emb_vector_cross(delta0, delta1);
        float dot = emb_vector_dot(delta0, delta1);

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

/* vertices a simplified a distance
 *
 * Reduces the polygon by distance.
 *
 * This is a non-destructive function, so the caller is responsible for
 * freeing "vertices" if they choose to keep "simplified".
 */
void embPolygon_reduceByDistance(EmbArray *vertices, EmbArray *simplified, float distance)
{
    int i;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->count < 3) {
        emb_array_copy(simplified, vertices);
        return;
    }

    for (i = 0; i < vertices->count; i++) {
        EmbVector delta;
        int nextId = (i + 1) % vertices->count;

        delta = emb_vector_subtract(
            vertices->geometry[nextId].object.vector,
            vertices->geometry[i].object.vector);

        /* If they are closer than the distance, continue */
        if (emb_vector_length(delta) < distance) {
            continue;
        }

        emb_array_addVector(simplified, vertices->geometry[i].object.vector);
    }
}

/* vertices a out a nth
 *
 * Reduces the polygon by removing the Nth vertex in the vertices list.
 * This is a non-destructive function, so the caller is responsible for
 * freeing vertices if they choose to keep out.
 */
void
embPolygon_reduceByNth(EmbArray *vertices, EmbArray *out, int nth)
{
    int i;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->count < 3) {
        emb_array_copy(out, vertices);
        return;
    }

    for (i=0; i<vertices->count; i++) {
        if (i!=nth) {
            emb_array_addVector(out, vertices->geometry[i].object.vector);
        }
    }
}

/* p1 a p2
 * Returns EmbPattern*
 */
EmbPattern *
emb_pattern_combine(EmbPattern *p1, EmbPattern *p2)
{
    int i;
    EmbPattern *out = emb_pattern_create();
    for (i=0; i<p1->stitch_list->count; i++) {
        emb_array_addStitch(out->stitch_list, p1->stitch_list->stitch[i]);
    }
    for (i=0; i<p2->stitch_list->count; i++) {
        emb_array_addStitch(out->stitch_list, p2->stitch_list->stitch[i]);
    }
    /* These need to be merged, not appended. */
    for (i=0; i<p1->thread_list->count; i++) {
        emb_pattern_addThread(out, p1->thread_list->thread[i]);
    }
    for (i=0; i<p2->thread_list->count; i++) {
        emb_pattern_addThread(out, p2->thread_list->thread[i]);
    }
    return out;
}

/* p a arc a thread_index a style
 */
void
emb_pattern_stitchArc(EmbPattern *p, EmbArc arc, int thread_index, int style)
{
    printf("DEBUG stitchArc (unfinished): %f %f %d %d\n",
        p->home.x, arc.start.x, thread_index, style);
}

/* p a circle a thread_index a style
 *
 * style determines:
 *     stitch density
 *     fill pattern
 *     outline or fill
 *
 * For now it's a straight fill of 1000 stitches of the whole object by
 * default.
 *
 * Consider the intersection of a line in direction "d" that passes through
 * the disc with center "c", radius "r". The start and end points are:
 *
 *     $(c-r(d/|d|), c + r(d/|d|))$
 *
 * Lines that are above and below this with an even seperation $s$ can be
 * found by taking the point on the line to be c+sn where the $n$ is the
 * unit normal vector to $d$ and the vector to be $d$ again. The
 * intersection points are therefore a right angled triangle, with one side
 * r, another s and the third the length to be solved, by Pythagoras we
 * have:
 *
 *    $(c + sn - \sqrt{r^2-s^2}(d/|d|), c + sn + \sqrt{r^2-s^2}(d/|d|))$
 *
 * repeating this process gives us all the end points and the fill only
 * alters these lines by splitting the ones longer than some tolerence.
 */
void
emb_pattern_stitchCircle(EmbPattern *p, EmbCircle circle, int thread_index, int style)
{
    float s;
    float seperation = 0.1;
    EmbVector direction = {1.0, 1.0};
    EmbVector normal = {-1.0, 1.0};
    direction = emb_vector_normalize(direction);
    normal = emb_vector_normalize(normal);
    printf("style %d\n", style);
    for (s=-circle.radius; s<circle.radius; s += seperation) {
        EmbLine line;
        float length = sqrt(circle.radius*circle.radius - s*s);
        EmbVector scaled = emb_vector_scale(normal, s);
        line.start = emb_vector_add(circle.center, scaled);
        scaled = emb_vector_scale(direction, length);
        line.start = emb_vector_subtract(line.start, scaled);
        scaled = emb_vector_scale(normal, s);
        line.end = emb_vector_add(circle.center, scaled);
        scaled = emb_vector_scale(direction, length);
        line.end = emb_vector_add(line.end, scaled);
        /* Split long stitches here. */
        emb_pattern_addStitchAbs(p, line.start.x, line.start.y, NORMAL, thread_index);
        emb_pattern_addStitchAbs(p, line.end.x, line.end.y, NORMAL, thread_index);
    }
}

/* a p a ellipse a thread_index a style
 *
 * \todo finish stitchEllipse
 */
void
emb_pattern_stitchEllipse(EmbPattern *p, EmbEllipse ellipse, int thread_index, int style)
{
    printf("DEBUG stitchEllipse: %f %f %d %d\n",
        p->home.x, ellipse.center.x, thread_index, style);
}

/*a p a rect a thread_index a style
 *
 * \todo finish stitch path
 */
void
emb_pattern_stitchPath(EmbPattern *p, EmbPath path, int thread_index, int style)
{
    printf("DEBUG stitchPath: %f %d %d %d\n",
        p->home.x, path.pointList->count, thread_index, style);
}

/*a p a rect a thread_index a style
 *
 * \todo finish stitch polygon
 */
void
emb_pattern_stitchPolygon(EmbPattern *p, EmbPolygon polygon, int thread_index, int style)
{
    printf("DEBUG stitchPolygon: %f %d %d %d\n",
        p->home.x, polygon.pointList->count, thread_index, style);
}

/* a p a rect a thread_index a style
 *
 * \todo finish stitch polyline
 */
void
emb_pattern_stitchPolyline(EmbPattern *p, EmbPolyline polyline, int thread_index, int style)
{
    printf("DEBUG stitchPolyline: %f %d %d %d\n",
        p->home.x, polyline.pointList->count, thread_index, style);
}

/* a p a rect a thread_index a style
 *
 * Here we just stitch the rectangle in the direction of it's longer side.
 */
void
emb_pattern_stitchRect(EmbPattern *p, EmbRect rect, int thread_index, int style)
{
    EmbReal seperation = 0.1;
    if (style > 0) {
        puts("WARNING: Only style 0 has been implimented.");
    }
    if (rect.w > rect.h) {
        float s;
        for (s=rect.y; s<rect.y + rect.h; s += seperation) {
            /* Split long stitches here. */
            emb_pattern_addStitchAbs(p, rect.y, s, NORMAL, thread_index);
            emb_pattern_addStitchAbs(p, rect.y + rect.h, s, NORMAL, thread_index);
        }
    }
    else {
        float s;
        for (s=rect.x; s<rect.x + rect.w; s += seperation) {
            /* Split long stitches here. */
            emb_pattern_addStitchAbs(p, s, rect.x, NORMAL, thread_index);
            emb_pattern_addStitchAbs(p, s, rect.x + rect.w, NORMAL, thread_index);
        }
    }
}

/* a p a rect a thread_index a style
 */
void
emb_pattern_stitchText(EmbPattern *p, EmbRect rect, int thread_index, int style)
{
    printf("DEBUG: %f %f %d %d",
        p->home.x, rect.y, thread_index, style);
}

/* a p
 */
void
emb_pattern_convertGeometry(EmbPattern* p)
{
    int i;
    for (i=0; i<p->geometry->count; i++) {
        EmbGeometry g = p->geometry->geometry[i];
        switch (g.type) {
        case EMB_ARC: {
            /* To Do make the thread up here. */
            emb_pattern_stitchArc(p, g.object.arc, 0, 0);
            break;
        }
        case EMB_CIRCLE: {
            /* To Do make the thread up here. */
            emb_pattern_stitchCircle(p, g.object.circle, 0, 0);
            break;
        }
        case EMB_ELLIPSE: {
            /* To Do make the thread up here. */
            emb_pattern_stitchEllipse(p, g.object.ellipse, 0, 0);
            break;
        }
        case EMB_RECT: {
            /* To Do make the thread up here. */
            emb_pattern_stitchRect(p, g.object.rect, 0, 0);
            break;
        }
        default:
            break;
        }
    }
    /* Now ignore the geometry when writing. */
    p->geometry->count = 0;
}

/*
 * Frame for PES formats
 */
const char imageWithFrame[38][48] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

/* Check that the pointer isn't NULL before freeing. */
void
safe_free(void *data)
{
    if (data) {
        free(data);
        data = 0;
    }
}

unsigned char
char_to_lower(unsigned char a)
{
    if (a >= 'A' && a <= 'Z') {
        a = a - 'A' + 'a';
    }
    return a;
}

/* This file contains all the read and write functions for the
 * library.
 *
 * This backends to the stb libraries and nanosvg library.
 *
 * Use Python PEP7 for coding style.
 *
 * Write a PES embedded a image to the given a file pointer.
 */
void
writeImage(FILE* file, unsigned char image[][48])
{
    int i, j;

    if (!file) {
        printf("ERROR: format-pec.c writeImage(), file argument is null\n");
        return;
    }
    for (i = 0; i < 38; i++) {
        for (j = 0; j < 6; j++) {
            int offset = j * 8;
            unsigned char output = 0;
            output |= (unsigned char)(image[i][offset] != 0);
            output |= (unsigned char)(image[i][offset + 1] != (unsigned char)0) << 1;
            output |= (unsigned char)(image[i][offset + 2] != (unsigned char)0) << 2;
            output |= (unsigned char)(image[i][offset + 3] != (unsigned char)0) << 3;
            output |= (unsigned char)(image[i][offset + 4] != (unsigned char)0) << 4;
            output |= (unsigned char)(image[i][offset + 5] != (unsigned char)0) << 5;
            output |= (unsigned char)(image[i][offset + 6] != (unsigned char)0) << 6;
            output |= (unsigned char)(image[i][offset + 7] != (unsigned char)0) << 7;
            fwrite(&output, 1, 1, file);
        }
    }
}

/* The distance between the arrays a and b of length size. */
float
image_diff(unsigned char *a, unsigned char *b, int size)
{
    int i;
    float total = 0.0;
    for (i=0; i<size; i++) {
        int diff = a[i] - b[i];
        total += diff*diff;
    }
    return total;
}

/* Render the pattern a p to the file with name a fname.
 * Return whether it was successful as an int.
 *
 * Basic Render
 * ------------
 *
 * Backends rendering to nanosvg/stb_image.
 *
 * The caller is responsible for the memory in p.
 */
int
emb_pattern_render(EmbPattern *p, char *fname)
{
    printf("Cannot render %p, %s\n", p, fname);
/*
    const char *tmp_fname = "libembroidery_temp.svg";
    NSVGimage *image = NULL;
    NSVGrasterizer rast;
    unsigned char *img_data = NULL;
    emb_pattern_writeAuto(p, tmp_fname);
    image = nsvgParseFromFile(tmp_fname, "px", 96.0f);
    img_data = malloc(4*image->width*image->height);
    nsvgRasterize(
        &rast,
        image,
        0, 0, 1,
        img_data,
        image->width,
        image->height,
        4*image->width);
    stbi_write_png(
         fname,
         image->width,
        image->height,
        4,
        img_data,
        4*image->width);
*/
    return 0;
}

/* Simulate the stitching of a pattern, using the image for rendering
 * hints about how to represent the pattern.
 */
int
emb_pattern_simulate(EmbPattern *pattern, char *fname)
{
    emb_pattern_render(pattern, fname);
    return 0;
}

/* . */
EmbImage
embImage_create(int width, int height)
{
    EmbImage image;
    image.width = width;
    image.height = height;
    image.data = malloc(4*width*height);
    return image;

}

/* . */
void
embImage_read(EmbImage *image, char *fname)
{
    printf("%d, %s\n", image->width, fname);
    /*
    int channels_in_file;
    image->data = stbi_load(
        fname,
        &(image->width),
        &(image->height),
        &channels_in_file,
        3);
    */
}

/* . */
int
embImage_write(EmbImage *image, char *fname)
{
    printf("%d, %s\n", image->width, fname);
    /*
    return stbi_write_png(
         fname,
         image->width,
        image->height,
        4,
        image->data,
        4*image->width);
*/
    return 0;
}

/* . */
void
embImage_free(EmbImage *image)
{
    safe_free(image->data);
}

/* The file is for the management of the main struct: EmbPattern.
 *
 * Returns a pointer to an EmbPattern. It is created on the heap.
 * The caller is responsible for freeing the allocated memory with
 * emb_pattern_free().
 *
 * Returns EmbPattern*
 */
EmbPattern*
emb_pattern_create(void)
{
    EmbPattern* p = (EmbPattern*)malloc(sizeof(EmbPattern));
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_create(), ");
        printf("unable to allocate memory for p\n");
        return 0;
    }
    p->dstJumpsPerTrim = 6;
    p->home.x = 0.0;
    p->home.y = 0.0;
    p->currentColorIndex = 0;
    p->stitch_list = emb_array_create(EMB_STITCH);
    p->thread_list = emb_array_create(EMB_THREAD);
    p->hoop_height = 0.0;
    p->hoop_width = 0.0;
    p->geometry = emb_array_create(EMB_LINE);
    return p;
}

/* a p a length
 */
void
emb_pattern_hideStitchesOverLength(EmbPattern* p, int length)
{
    EmbVector prev;
    int i;
    prev.x = 0.0;
    prev.y = 0.0;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_hideStitchesOverLength(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->stitch_list->count; i++) {
        if ((fabs(p->stitch_list->stitch[i].x - prev.x) > length)
         || (fabs(p->stitch_list->stitch[i].y - prev.y) > length)) {
            p->stitch_list->stitch[i].flags |= TRIM;
            p->stitch_list->stitch[i].flags &= ~NORMAL;
        }
        prev.x = p->stitch_list->stitch[i].x;
        prev.y = p->stitch_list->stitch[i].y;
    }
}

/* a pattern a thread
 * Returns int
 */
int
emb_pattern_addThread(EmbPattern *pattern, EmbThread thread)
{
    if (pattern->thread_list->count + 1 > pattern->thread_list->length) {
        if (!emb_array_resize(pattern->thread_list)) {
            return 0;
        }
    }
    pattern->thread_list->thread[pattern->thread_list->count] = thread;
    pattern->thread_list->count++;
    return 1;
}

/* a p
 */
void
emb_pattern_fixColorCount(EmbPattern* p)
{
    /* fix color count to be max of color index. */
    int maxColorIndex = 0, i;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_fixColorCount(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->stitch_list->count; i++) {
/*        printf("%d %d\n", list->stitch.color, maxColorIndex);*/
        maxColorIndex = EMB_MAX(maxColorIndex, p->stitch_list->stitch[i].color);
    }
    if (p->thread_list->count == 0 || maxColorIndex == 0) {
        emb_pattern_addThread(p, black_thread);
    }
    else {
        if (maxColorIndex > 0) {
            while (p->thread_list->count <= maxColorIndex) {
/*        printf("%d %d\n", p->n_threads, maxColorIndex);*/
                emb_pattern_addThread(p, emb_get_random_thread());
            }
        }
    }
    /*
    while (p->threadLists->count > (maxColorIndex + 1)) {
        TODO: erase last color    p->threadList.pop_back();
    }
    */
}

/* Copies all of the Embstitch_list data to
 * EmbPolylineObjectList data for pattern (a p).
 */
void
emb_pattern_copystitch_listToPolylines(EmbPattern* p)
{
    int breakAtFlags, i;
    EmbPoint point;
    EmbColor color;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_copystitch_listToPolylines(), ");
        printf("p argument is null\n");
        return;
    }

    breakAtFlags = (STOP | JUMP | TRIM);

    for (i = 0; i < p->stitch_list->count; i++) {
        EmbArray *pointList = 0;
        for (; i < p->stitch_list->count; i++) {
            EmbStitch st = p->stitch_list->stitch[i];
            if (st.flags & breakAtFlags) {
                break;
            }
            if (!(st.flags & JUMP)) {
                if (!pointList) {
                    pointList = emb_array_create(EMB_POINT);
                    color = p->thread_list->thread[st.color].color;
                }
                point.position.x = st.x;
                point.position.y = st.y;
                emb_array_addPoint(pointList, point);
            }
        }

        /* NOTE: Ensure empty polylines are not created. This is critical. */
        if (pointList) {
            EmbPolyline currentPolyline;
            currentPolyline.pointList = pointList;
            currentPolyline.color = color;
            /* TODO: Determine what the correct value should be */
            currentPolyline.lineType = 1;

            emb_array_addPolyline(p->geometry, currentPolyline);
        }
    }
}

/* Copies all of the EmbPolylineObjectList data to Embstitch_list
 * data for pattern (a p).
 */
void
emb_pattern_copyPolylinesTostitch_list(EmbPattern* p)
{
    int firstObject = 1, i, j;
    /*int currentColor = polyList->polylineObj->color TODO: polyline color */

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_copyPolylinesTostitch_list(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->geometry->count; i++) {
        EmbPolyline currentPoly;
        EmbArray* currentPointList;
        EmbThread thread;

        if (p->geometry->geometry[i].type != EMB_POLYLINE) {
            continue;
        }

        currentPoly = p->geometry->geometry[i].object.polyline;
        currentPointList = currentPoly.pointList;

        strcpy(thread.catalogNumber, "");
        thread.color = currentPoly.color;
        strcpy(thread.description, "");
        emb_pattern_addThread(p, thread);

        if (!firstObject) {
            emb_pattern_addStitchAbs(p,
                currentPointList->geometry[0].object.point.position.x,
                currentPointList->geometry[0].object.point.position.y, TRIM, 1);
            emb_pattern_addStitchRel(p, 0.0, 0.0, STOP, 1);
        }

        emb_pattern_addStitchAbs(p,
            currentPointList->geometry[0].object.point.position.x,
            currentPointList->geometry[0].object.point.position.y,
            JUMP,
            1);
        for (j = 1; j < currentPointList->count; j++) {
            EmbVector v = currentPointList->geometry[j].object.point.position;
            emb_pattern_addStitchAbs(p, v.x, v.y, NORMAL, 1);
        }
        firstObject = 0;
    }
    emb_pattern_addStitchRel(p, 0.0, 0.0, END, 1);
}

/* Moves all of the Embstitch_list data to EmbPolylineObjectList
 * data for pattern (a p).
 */
void
emb_pattern_movestitch_listToPolylines(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_movestitch_listToPolylines(), p argument is null\n");
        return;
    }
    emb_pattern_copystitch_listToPolylines(p);
    /* Free the stitch_list and threadList since their data has now been transferred to polylines */
    p->stitch_list->count = 0;
    p->thread_list->count = 0;
}

/* Moves all of the EmbPolylineObjectList data to Embstitch_list
 * data for pattern (a p).
 */
void
emb_pattern_movePolylinesTostitch_list(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_movePolylinesTostitch_list(), p argument is null\n");
        return;
    }
    emb_pattern_copyPolylinesTostitch_list(p);
}

/* Adds a stitch to the pattern (a p) at the absolute position
 * (a x,a y). Positive y is up. Units are in millimeters.
 */
void
emb_pattern_addStitchAbs(EmbPattern* p, EmbReal x, EmbReal y,
                            int flags, int isAutoColorIndex)
{
    EmbStitch s;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addStitchAbs(), ");
        printf("p argument is null\n");
        return;
    }

    if (flags & END) {
        if (p->stitch_list->count == 0) {
            return;
        }
        /* Prevent unnecessary multiple END stitches */
        if (p->stitch_list->stitch[p->stitch_list->count - 1].flags & END) {
            printf("ERROR: emb-pattern.c emb_pattern_addStitchAbs(), found multiple END stitches\n");
            return;
        }
        emb_pattern_fixColorCount(p);
        /* HideStitchesOverLength(127); TODO: fix or remove this */
    }

    if (flags & STOP) {
        if (p->stitch_list->count == 0) {
            return;
        }
        if (isAutoColorIndex) {
            p->currentColorIndex++;
        }
    }

    /* NOTE: If the stitch_list is empty, we will create it before adding
        stitches to it. The first coordinate will be the HOME position. */
    if (p->stitch_list->count == 0) {
        /* NOTE: Always HOME the machine before starting any stitching */
        EmbStitch h;
        h.x = p->home.x;
        h.y = p->home.y;
        h.flags = JUMP;
        h.color = p->currentColorIndex;
        emb_array_addStitch(p->stitch_list, h);
    }
    s.x = x;
    s.y = y;
    s.flags = flags;
    s.color = p->currentColorIndex;
    emb_array_addStitch(p->stitch_list, s);
}

/* Adds a stitch to the pattern (a p) at the relative position
 * (a dx,a dy) to the previous stitch. Positive y is up.
 * Units are in millimeters.
 */
void
emb_pattern_addStitchRel(EmbPattern* p, EmbReal dx, EmbReal dy,
                            int flags, int isAutoColorIndex)
{
    EmbReal x, y;
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addStitchRel(), p argument is null\n");
        return;
    }
    if (p->stitch_list->count > 0) {
        EmbStitch st = p->stitch_list->stitch[p->stitch_list->count - 1];
        x = st.x + dx;
        y = st.y + dy;
    } else {
        /* NOTE: The stitch_list is empty, so add it to the HOME position.
         * The embstitch_list_create function will ensure the first coordinate is at the HOME position. */
        x = p->home.x + dx;
        y = p->home.y + dy;
    }
    emb_pattern_addStitchAbs(p, x, y, flags, isAutoColorIndex);
}

/* Change the currentColorIndex of pattern a p to a index.
 */
void
emb_pattern_changeColor(EmbPattern* p, int index)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_changeColor(), p argument is null\n");
        return;
    }
    p->currentColorIndex = index;
}

/* Very simple scaling of the x and y axis for every point.
 * Doesn't insert or delete stitches to preserve density.
 */
void
emb_pattern_scale(EmbPattern* p, EmbReal scale)
{
    int i;
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_scale(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitch_list->count; i++) {
        p->stitch_list->stitch[i].x *= scale;
        p->stitch_list->stitch[i].y *= scale;
    }
}

/* Returns an EmbRect that encapsulates all stitches and objects in the
 * pattern (a p).
 */
EmbRect
emb_pattern_bounds(EmbPattern* p)
{
    EmbRect r;
    EmbStitch pt;
    int i, j;

    r.x = 0.0;
    r.y = 0.0;
    r.w = 1.0;
    r.h = 1.0;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_bounds(), ");
        printf("p argument is null\n");
        return r;
    }

    /* Calculate the bounding rectangle.  It's needed for smart repainting. */
    /* TODO: Come back and optimize this mess so that after going thru all objects
     * and stitches, if the rectangle isn't reasonable, then return a default rect
     */
    if ((p->stitch_list->count == 0) && (p->geometry->count == 0)) {
        return r;
    }
    r.x = -99999.0;
    r.y = -99999.0;
    double right = 99999.0;
    double bottom = 99999.0;

    for (i = 0; i < p->stitch_list->count; i++) {
        /* If the point lies outside of the accumulated bounding
         * rectangle, then inflate the bounding rect to include it. */
        pt = p->stitch_list->stitch[i];
        if (!(pt.flags & TRIM)) {
            r.x = EMB_MAX(r.x, pt.x);
            r.y = EMB_MAX(r.y, pt.y);
            right = EMB_MIN(right, pt.x);
            bottom = EMB_MIN(bottom, pt.y);
        }
    }

    for (i = 0; i < p->geometry->count; i++) {
        EmbGeometry g = p->geometry->geometry[i];
        switch (g.type) {
        case EMB_ARC: {
            /* TODO: emb_pattern_calcBoundingBox for arcs,
            for now just checks the start point */
            EmbArc arc = g.object.arc;
            r.x = EMB_MIN(r.x, arc.start.x);
            r.y = EMB_MIN(r.y, arc.start.y);
            right = EMB_MAX(right, arc.start.x);
            bottom = EMB_MAX(bottom, arc.start.y);
            break;
        }
        case EMB_CIRCLE: {
            EmbCircle circle = g.object.circle;
            r.x = EMB_MIN(r.x, circle.center.x - circle.radius);
            r.y = EMB_MIN(r.y, circle.center.y - circle.radius);
            right = EMB_MAX(right, circle.center.x + circle.radius);
            bottom = EMB_MAX(bottom, circle.center.y + circle.radius);
            break;
        }
        case EMB_ELLIPSE: {
            /* TODO: account for rotation */
            EmbEllipse ellipse = g.object.ellipse;
            r.x = EMB_MIN(r.x, ellipse.center.x - ellipse.radius.x);
            r.y = EMB_MIN(r.y, ellipse.center.y - ellipse.radius.y);
            right = EMB_MAX(right, ellipse.center.x + ellipse.radius.x);
            bottom = EMB_MAX(bottom, ellipse.center.y + ellipse.radius.y);
            break;
        }
        case EMB_LINE: {
            EmbLine line = g.object.line;
            r.x = EMB_MIN(r.x, line.start.x);
            r.x = EMB_MIN(r.x, line.end.x);
            r.y = EMB_MIN(r.y, line.start.y);
            r.y = EMB_MIN(r.y, line.end.y);
            right = EMB_MAX(right, line.start.x);
            right = EMB_MAX(right, line.end.x);
            bottom = EMB_MAX(bottom, line.start.y);
            bottom = EMB_MAX(bottom, line.end.y);
            break;
        }
        case EMB_POINT: {
            EmbVector point = g.object.point.position;
            r.x = EMB_MIN(r.x, point.x);
            r.y = EMB_MIN(r.y, point.y);
            right = EMB_MAX(right, point.x);
            bottom = EMB_MAX(bottom, point.y);
            break;
        }
        case EMB_POLYGON: {
            EmbArray *polygon = g.object.polygon.pointList;
            for (j=0; j < polygon->count; j++) {
                /* TODO: emb_pattern_calcBoundingBox for polygons */
            }
            break;
        }
        case EMB_POLYLINE: {
            EmbArray *polyline = g.object.polyline.pointList;
            for (j=0; j < polyline->count; j++) {
                /* TODO: emb_pattern_calcBoundingBox for polylines */
            }
            break;
        }
        case EMB_RECT: {
            EmbRect rect = g.object.rect;
            r.x = EMB_MIN(r.x, rect.x);
            r.y = EMB_MIN(r.y, rect.y);
            right = EMB_MAX(right, r.x + rect.w);
            bottom = EMB_MAX(bottom, r.y + rect.h);
            break;
        }
        case EMB_SPLINE: {
            /* EmbBezier bezier;
            bezier = p->splines->spline[i].bezier; */
            /* TODO: emb_pattern_calcBoundingBox for splines */
            break;
        }
        default:
            break;
        }
    }

    r.w = right - r.x;
    r.h = bottom - r.y;

    return r;
}

/* Flips the entire pattern (a p) horizontally about the y-axis.
 */
void
emb_pattern_flipHorizontal(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_flipHorizontal(), ");
        printf("p argument is null\n");
        return;
    }
    emb_pattern_flip(p, 1, 0);
}

/* Flips the entire pattern (a p) vertically about the x-axis.
 */
void
emb_pattern_flipVertical(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_flipVertical(), ");
        printf("p argument is null\n");
        return;
    }
    emb_pattern_flip(p, 0, 1);
}

/* Flips the entire pattern (a p) horizontally about the x-axis if (a horz) is true.
 *  Flips the entire pattern (a p) vertically about the y-axis if (a vert) is true.
 */
void
emb_pattern_flip(EmbPattern* p, int horz, int vert)
{
    int i, j;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_flip(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitch_list->count; i++) {
        if (horz) {
            p->stitch_list->stitch[i].x *= -1.0;
        }
        if (vert) {
            p->stitch_list->stitch[i].y *= -1.0;
        }
    }

    for (i = 0; i < p->geometry->count; i++) {
        EmbGeometry *g = &(p->geometry->geometry[i]);
        switch (g->type) {
        case EMB_ARC: {
            if (horz) {
                g->object.arc.start.x *= -1.0;
                g->object.arc.mid.x *= -1.0;
                g->object.arc.end.x *= -1.0;
            }
            if (vert) {
                g->object.arc.start.y *= -1.0;
                g->object.arc.mid.y *= -1.0;
                g->object.arc.end.y *= -1.0;
            }
            break;
        }
        case EMB_LINE: {
            if (horz) {
                g->object.line.start.x *= -1.0;
                g->object.line.end.x *= -1.0;
            }
            if (vert) {
                g->object.line.start.y *= -1.0;
                g->object.line.end.y *= -1.0;
            }
            break;
        }
        case EMB_CIRCLE: {
            if (horz) {
                g->object.circle.center.x *= -1.0;
            }
            if (vert) {
                g->object.circle.center.y *= -1.0;
            }
            break;
        }
        case EMB_ELLIPSE:
            if (horz) {
                g->object.ellipse.center.x *= -1.0;
            }
            if (vert) {
                g->object.ellipse.center.y *= -1.0;
            }
            break;
        case EMB_PATH: {
            EmbArray *point_list = g->object.path.pointList;
            for (j=0; j < point_list->count; j++) {
                if (horz) {
                    point_list->geometry[j].object.point.position.x *= -1.0;
                }
                if (vert) {
                    point_list->geometry[j].object.point.position.y *= -1.0;
                }
            }
            break;
        }
        case EMB_POINT:
            if (horz) {
                g->object.point.position.x *= -1.0;
            }
            if (vert) {
                g->object.point.position.y *= -1.0;
            }
            break;
        case EMB_POLYGON: {
            EmbArray *point_list = g->object.polygon.pointList;
            for (j=0; j < point_list->count; j++) {
                if (horz) {
                    point_list->geometry[i].object.point.position.x *= -1.0;
                }
                if (vert) {
                    point_list->geometry[i].object.point.position.y *= -1.0;
                }
            }
            break;
        }
        case EMB_POLYLINE: {
            EmbArray *point_list = g->object.polygon.pointList;
            for (j=0; j < point_list->count; j++) {
                if (horz) {
                    point_list->geometry[j].object.point.position.x *= -1.0;
                }
                if (vert) {
                    point_list->geometry[j].object.point.position.y *= -1.0;
                }
            }
            break;
        }
        case EMB_RECT: {
            if (horz) {
                g->object.rect.x *= -1.0;
                g->object.rect.y *= -1.0;
            }
            if (vert) {
                g->object.rect.w *= -1.0;
                g->object.rect.h *= -1.0;
            }
            break;
        }
        case EMB_SPLINE:
            /* TODO */
            break;
        default:
            break;
        }
    }
}

/* a p
 */
void
emb_pattern_combineJumpStitches(EmbPattern* p)
{
    int jumpCount = 0, i;
    EmbArray *newList;
    EmbStitch j;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_combineJumpStitches(), ");
        printf("p argument is null\n");
        return;
    }
    newList = emb_array_create(EMB_STITCH);
    for (i = 0; i < p->stitch_list->count; i++) {
        EmbStitch st = p->stitch_list->stitch[i];
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
                emb_array_addStitch(newList, j);
            }
            emb_array_addStitch(newList, st);
        }
    }
    emb_array_free(p->stitch_list);
    p->stitch_list = newList;
}

/* \todo The params determine the max XY movement rather than the length.
 * They need renamed or clarified further.
 */
void
emb_pattern_correctForMaxStitchLength(EmbPattern* p,
                        EmbReal maxStitchLength, EmbReal maxJumpLength)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_correctForMaxStitchLength(), ");
        printf("p argument is null\n");
        return;
    }
    if (p->stitch_list->count > 1) {
        int i, j, splits;
        EmbReal maxXY, maxLen, addX, addY;
        EmbArray *newList = emb_array_create(EMB_STITCH);
        for (i=1; i < p->stitch_list->count; i++) {
            EmbStitch st = p->stitch_list->stitch[i];
            EmbReal xx = st.x;
            EmbReal yy = st.y;
            EmbReal dx = p->stitch_list->stitch[i-1].x - xx;
            EmbReal dy = p->stitch_list->stitch[i-1].y - yy;
            if ((fabs(dx) > maxStitchLength) || (fabs(dy) > maxStitchLength)) {
                maxXY = EMB_MAX(fabs(dx), fabs(dy));
                if (st.flags & (JUMP | TRIM)) {
                    maxLen = maxJumpLength;
                } else {
                    maxLen = maxStitchLength;
                }
                splits = (int)ceil((EmbReal)maxXY / maxLen);

                if (splits > 1) {
                    addX = (EmbReal)dx / splits;
                    addY = (EmbReal)dy / splits;

                    for (j = 1; j < splits; j++) {
                        EmbStitch s;
                        s = st;
                        s.x = xx + addX * j;
                        s.y = yy + addY * j;
                        emb_array_addStitch(newList, s);
                    }
                }
            }
            emb_array_addStitch(newList, st);
        }
        emb_array_free(p->stitch_list);
        p->stitch_list = newList;
    }
    emb_pattern_end(p);
}

/* Center the pattern a p.
 */
void
emb_pattern_center(EmbPattern* p)
{
    /* TODO: review this. currently not used in anywhere.
        Also needs to handle various design objects */
    int moveLeft, moveTop, i;
    EmbRect boundingRect;
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_center(), p argument is null\n");
        return;
    }
    boundingRect = emb_pattern_bounds(p);

    moveLeft = (int)(boundingRect.x - boundingRect.w / 2.0);
    moveTop = (int)(boundingRect.y - boundingRect.h / 2.0);

    for (i = 0; i < p->stitch_list->count; i++) {
        p->stitch_list->stitch[i].x -= moveLeft;
        p->stitch_list->stitch[i].y -= moveTop;
    }
}

/* TODO: Description needed.
 */
void
emb_pattern_loadExternalColorFile(EmbPattern* p, const char* fileName)
{
    int hasRead, stub_len, format;
    char extractName[200];

    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_loadExternalColorFile(), p argument is null\n");
        return;
    }
    if (!fileName) {
        printf("ERROR: emb-pattern.c emb_pattern_loadExternalColorFile(), fileName argument is null\n");
        return;
    }

    strcpy(extractName, fileName);
    format = emb_identify_format(fileName);
    stub_len = string_len(fileName) - string_len(formatTable[format].extension);
    extractName[stub_len] = 0;
    strcat(extractName, ".edr");
    hasRead = emb_pattern_read(p, extractName, EMB_FORMAT_EDR);
    if (!hasRead) {
        extractName[stub_len] = 0;
        strcat(extractName,".rgb");
        hasRead = emb_pattern_read(p, extractName, EMB_FORMAT_RGB);
    }
    if (!hasRead) {
        extractName[stub_len] = 0;
        strcat(extractName,".col");
        hasRead = emb_pattern_read(p, extractName, EMB_FORMAT_COL);
    }
    if (!hasRead) {
        extractName[stub_len] = 0;
        strcat(extractName,".inf");
        hasRead = emb_pattern_read(p, extractName, EMB_FORMAT_INF);
    }
}

/* Frees all memory allocated in the pattern (a p).
 */
void
emb_pattern_free(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_free(), p argument is null\n");
        return;
    }
    emb_array_free(p->stitch_list);
    emb_array_free(p->thread_list);
    emb_array_free(p->geometry);
    safe_free(p);
}

/*
 */
void
emb_add_geometry(EmbPattern* p, EmbGeometry g)
{
    emb_array_add_geometry(p->geometry, g);
}

/* Adds a circle object to pattern (a p) with its center at the absolute
 * position (a cx,a cy) with a radius of (a r). Positive y is up.
 * Units are in millimeters.
 */
void
emb_add_circle(EmbPattern* p, EmbCircle circle)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_add_circle(), p argument is null\n");
        return;
    }

    EmbGeometry g;
    g.object.circle = circle;
    g.type = EMB_CIRCLE;
    emb_array_add_geometry(p->geometry, g);
}

/* Adds an ellipse object to pattern (a p) with its center at the
 * absolute position (a cx,a cy) with radii of (a rx,a ry). Positive y is up.
 * Units are in millimeters.
 */
void
emb_add_ellipse(EmbPattern* p, EmbEllipse ellipse)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addEllipseObjectAbs(), p argument is null\n");
        return;
    }

    emb_array_add_ellipse(p->geometry, ellipse);
}

/* Adds a line object to pattern (a p) starting at the absolute position
 * (a x1,a y1) and ending at the absolute position (a x2,a y2).
 * Positive y is up. Units are in millimeters.
 */
void
emb_add_line(EmbPattern* p, EmbLine line)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addLineObjectAbs(), p argument is null\n");
        return;
    }

    emb_array_addLine(p->geometry, line);
}

/* .
 */
void
emb_add_path(EmbPattern* p, EmbPath obj)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addPathObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj.pointList) {
        printf("ERROR: emb-pattern.c emb_pattern_addPathObjectAbs(), obj->pointList is empty\n");
        return;
    }

    emb_array_addPath(p->geometry, obj);
}

/*! Adds a point object to pattern (a p) at the absolute position (a x,a y). Positive y is up. Units are in millimeters. */
void
emb_pattern_addPointAbs(EmbPattern* p, EmbPoint obj)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addPointObjectAbs(), p argument is null\n");
        return;
    }

    emb_array_addPoint(p->geometry, obj);
}

void
emb_pattern_addPolygonAbs(EmbPattern* p, EmbPolygon obj)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addPolygonObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj.pointList) {
        printf("ERROR: emb-pattern.c emb_pattern_addPolygonObjectAbs(), obj->pointList is empty\n");
        return;
    }

    emb_array_addPolygon(p->geometry, obj);
}

void
emb_pattern_addPolylineObjectAbs(EmbPattern* p, EmbPolyline obj)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addPolylineObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj.pointList) {
        printf("ERROR: emb-pattern.c emb_pattern_addPolylineObjectAbs(), obj->pointList is empty\n");
        return;
    }
    emb_array_addPolyline(p->geometry, obj);
}

/* Adds a rectangle object to pattern (a p) at the absolute position
 * (a x,a y) with a width of (a w) and a height of (a h).
 * Positive y is up. Units are in millimeters.
 */
void
emb_pattern_addRectAbs(EmbPattern* p, EmbRect rect)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_pattern_addRectObjectAbs(), p argument is null\n");
        return;
    }
    emb_array_addRect(p->geometry, rect);
}

/* . */
void
emb_pattern_end(EmbPattern *p)
{
    if (p->stitch_list->count == 0) {
        return;
    }
    /* Check for an END stitch and add one if it is not present */
    if (p->stitch_list->stitch[p->stitch_list->count-1].flags != END) {
        emb_pattern_addStitchRel(p, 0, 0, END, 1);
    }
}

/*
 *
 */
int
convert(const char *inf, const char *outf)
{
    EmbPattern* p = 0;
    int reader, writer;

    reader = emb_identify_format(inf);
    writer = emb_identify_format(outf);

    p = emb_pattern_create();
    if (!p) {
        printf("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    if (!emb_pattern_read(p, inf, reader)) {
        printf("ERROR: convert(), reading file was unsuccessful: %s\n", inf);
        emb_pattern_free(p);
        return 1;
    }

    if (formatTable[reader].type == EMBFORMAT_OBJECTONLY) {
        if (formatTable[writer].type == EMBFORMAT_STITCHONLY) {
            emb_pattern_movePolylinesTostitch_list(p);
        }
    }

    if (!emb_pattern_write(p, outf, writer)) {
        printf("ERROR: convert(), writing file %s was unsuccessful\n", outf);
        emb_pattern_free(p);
        return 1;
    }

    emb_pattern_free(p);
    return 0;
}

/* The Pattern Properties
 * -----------------------------------------------------------------------------
 */
int
emb_pattern_color_count(EmbPattern *pattern, EmbColor startColor)
{
    int numberOfColors = 0, i;
    EmbColor color = startColor;
    for (i=0; i<pattern->stitch_list->count; i++) {
        EmbColor newColor;
        EmbStitch st;

        st = pattern->stitch_list->stitch[i];

        newColor = pattern->thread_list->thread[st.color].color;
        if (embColor_distance(newColor, color) != 0) {
            numberOfColors++;
            color = newColor;
        }
        else if (st.flags & END || st.flags & STOP) {
            numberOfColors++;
        }

        while (pattern->stitch_list->stitch[i+1].flags == st.flags) {
            i++;
            if (i >= pattern->stitch_list->count-2) {
                break;
            }
        }
    }
    return numberOfColors;
}

/*
 * Print out pattern details.
 */
void
emb_pattern_details(EmbPattern *pattern)
{
    int colors, num_stitches, real_stitches, jump_stitches, trim_stitches;
    int unknown_stitches;
    EmbRect bounds;
    float thread_usage;
    float minimum_length;
    float maximum_length;

    // colors = emb_pattern_color_count(pattern);
    colors = 1;
    num_stitches = pattern->stitch_list->count;
    real_stitches = emb_pattern_realStitches(pattern);
    jump_stitches = emb_pattern_jumpStitches(pattern);
    trim_stitches = emb_pattern_trimStitches(pattern);
    unknown_stitches = 0; // emb_pattern_unknownStitches(pattern);
    bounds = emb_pattern_bounds(pattern);
    thread_usage = emb_total_thread_length(pattern);
    minimum_length = emb_pattern_shortest_stitch(pattern);
    maximum_length = emb_pattern_longest_stitch(pattern);

    /* Print Report */
    printf("Design Details\n");
    printf("--------------\n");
    printf("real_stitches: %d\n", real_stitches);
    printf("trim_stitches: %d\n", trim_stitches);
    printf("unknown_stitches: %d\n", unknown_stitches);
    printf("total_stitches: %d\n", num_stitches);
    printf("num_colors: %d\n", pattern->thread_list->count);

    printf("Total thread usage: %f mm\n", thread_usage);
    printf("Shortest stitch: %f mm\n", minimum_length);
    printf("Longest stitch: %f mm\n", maximum_length);

    printf("Stitches: %d\n", num_stitches);
    printf("Colors: %d\n", colors);
    printf("Jumps: %d\n", jump_stitches);

    printf("Top: %f mm\n", bounds.y);
    printf("Left: %f mm\n", bounds.x);
    printf("Bottom: %f mm\n", bounds.h + bounds.y);
    printf("Right: %f mm\n", bounds.w + bounds.x);
    printf("Width: %f mm\n", bounds.w);
    printf("Height: %f mm\n", bounds.h);
    printf("\n");

    /*
    EmbReal minx = 0.0, maxx = 0.0, miny = 0.0, maxy = 0.0;
    int number_of_minlength_stitches = 0;
    int number_of_maxlength_stitches = 0;

    EmbReal xx = 0.0, yy = 0.0;
    EmbReal length = 0.0;

    if (num_stitches == 0) {
        QMessageBox::warning(this, tr("No Design Loaded"), tr("<b>A design needs to be loaded or created before details can be determined.</b>"));
        return;
    }
    QVector<EmbReal> stitchLengths;

    EmbReal binSize = max_stitchlength / NUMBINS;

    QString str;
    int i;
    for (i = 0; i < NUMBINS; i++) {
        str += QString::number(binSize * (i), 'f', 1) + " - " + QString::number(binSize * (i+1), 'f', 1) + " mm: " +  QString::number(bin[i]) + "\n\n";
    }

    grid->addWidget(new QLabel(tr("\nStitch Distribution: \n")),9,0,1,2);
    grid->addWidget(new QLabel(str), 10, 0, 1, 1);
    grid->addWidget(new QLabel(tr("\nThread Length By Color: \n")),11,0,1,2);
    int currentRow = 12;

    int i;
    for (i = 0; i < num_colors; i++) {
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

    QDialogButtonBox buttonbox(Qt::Horizontal, &dialog);
    QPushButton button(&dialog);
    button.setText("Ok");
    buttonbox.addButton(&button, QDialogButtonBox::AcceptRole);
    buttonbox.setCenterButtons(true);
    connect(&buttonbox, SIGNAL(accepted()), &dialog, SLOT(accept()));

    grid->addWidget(&buttonbox, currentRow, 0, 1, 2);
*/
}

/* . */
void
emb_pattern_print(EmbPattern *pattern)
{
    EmbArray *sts = pattern->stitch_list;
    int i;
    for (i = 0; i < sts->count; i++) {
        printf("%d: %f %f %d\n",
            i, sts->stitch[i].x, sts->stitch[i].y, sts->stitch[i].flags);
    }
}

void
emb_pattern_lengthHistogram(EmbPattern *pattern, int *bin, int NUMBINS)
{
    int i;
    float max_stitch_length = emb_pattern_longest_stitch(pattern);
    EmbArray *sts = pattern->stitch_list;
    for (i = 0; i <= NUMBINS; i++) {
        bin[i] = 0;
    }

    for (i = 1; i < sts->count; i++) {
        EmbStitch st_prev = sts->stitch[i-1];
        EmbStitch st = sts->stitch[i];
        if ((st.flags == NORMAL) & (st_prev.flags == NORMAL)) {
            float length = emb_stitch_length(st_prev, st);
            bin[(int)(floor(NUMBINS*length/max_stitch_length))]++;
        }
    }
}

int
emb_pattern_realStitches(EmbPattern *pattern)
{
    int i;
    EmbArray *sts = pattern->stitch_list;
    int real_stitches = 0;
    for (i = 0; i < sts->count; i++) {
        if (!(sts->stitch[i].flags & (JUMP | TRIM | END))) {
            real_stitches++;
        }
    }
    return real_stitches;
}

int
emb_pattern_jumpStitches(EmbPattern *pattern)
{
    int i;
    EmbArray *sts = pattern->stitch_list;
    int jump_stitches = 0;
    for (i = 0; i < sts->count; i++) {
        if (sts->stitch[i].flags & JUMP) {
            jump_stitches++;
        }
    }
    return jump_stitches;
}

int
emb_pattern_trimStitches(EmbPattern *pattern)
{
    int i;
    EmbArray *sts = pattern->stitch_list;
    int trim_stitches = 0;
    for (i = 0; i < sts->count; i++) {
        if (sts->stitch[i].flags & TRIM) {
            trim_stitches++;
        }
    }
    return trim_stitches;
}

/* The Thread Management System
 * -----------------------------------------------------------------------------
 */
int
threadColor(const char *name, int brand)
{
    int i;
    for (i = 0; brand_codes[brand].codes[i].manufacturer_code >= 0; i++) {
        if (!strcmp(brand_codes[brand].codes[i].name, name)) {
            return brand_codes[brand].codes[i].hex_code;
        }
    }
    return -1;
}

int
threadColorNum(unsigned int color, int brand)
{
    int i;
    for (i = 0; brand_codes[brand].codes[i].manufacturer_code >= 0; i++) {
        if (brand_codes[brand].codes[i].hex_code == color) {
            return brand_codes[brand].codes[i].manufacturer_code;
        }
    }

    return -1;
}

const char*
threadColorName(unsigned int color, int brand)
{
    int i;
    for (i = 0; brand_codes[brand].codes[i].manufacturer_code >= 0; i++) {
        if (brand_codes[brand].codes[i].hex_code == color) {
            return brand_codes[brand].codes[i].name;
        }
    }

    return "COLOR NOT FOUND";
}

/* . */
EmbVector
scale_and_rotate(EmbVector v, double scale, double angle)
{
    EmbVector w;
    double rot = radians(angle);
    double cosRot = cos(rot);
    double sinRot = sin(rot);
    w.x = v.x * scale;
    w.y = v.y * scale;
    w.x = w.x * cosRot - w.y * sinRot;
    w.y = w.x * sinRot + w.y * cosRot;
    return w;    
}


/* Get the position as a vector from the stitch. */
EmbVector
emb_st_pos(EmbStitch st)
{
    return emb_vector(st.x, st.y);
}

/* Length of stitch starting of "prev_st" and ending at "st". */
double
emb_stitch_length(EmbStitch prev_st, EmbStitch st)
{
    EmbVector pos = emb_st_pos(st);
    EmbVector prev_pos = emb_st_pos(prev_st);
    double length = emb_vector_distance(pos, prev_pos);
    return length;
}

/* Returns the number of real stitches in a pattern.
 * We consider SEQUIN to be a real stitch in this count.
 */
int
emb_pattern_real_count(EmbPattern *pattern)
{
    int i;
    int total = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        if (!(st.flags & (JUMP | TRIM))) {
            total++;
        }
    }
    return total;
}

/* The length of the longest stitch in the pattern. */
EmbReal
emb_pattern_longest_stitch(EmbPattern *pattern)
{
    if (pattern->stitch_list->count < 2) {
        return 0.0;
    }

    int i;
    EmbReal max_stitch = 0.0;
    EmbStitch prev_st = pattern->stitch_list->stitch[0];
    for (i = 1; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
            double length = emb_stitch_length(st, prev_st);
            if (length > max_stitch) {
                max_stitch = length;
            }
        }
        prev_st = st;
    }
    return max_stitch;    
}

/* The length of the shortest stitch in the pattern. */
EmbReal
emb_pattern_shortest_stitch(EmbPattern *pattern)
{
    if (pattern->stitch_list->count < 2) {
        return 0.0;
    }

    int i;
    EmbReal min_stitch = 1.0e10;
    EmbStitch prev_st = pattern->stitch_list->stitch[0];
    for (i = 1; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
            double length = emb_stitch_length(st, prev_st);
            if (length < min_stitch) {
                min_stitch = length;
            }
        }
        prev_st = st;
    }
    return min_stitch;    
}

/* Returns the number of stitches in a pattern that are of any of the types
 * or-ed together in "flag". For example to count the total number of
 * TRIM and STOP stitches use:
 *
 *     emb_pattern_count_type(pattern, TRIM | STOP);
 */
int
emb_pattern_count_type(EmbPattern *pattern, int flag)
{
    int i;
    int total = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        if (st.flags & flag) {
            total++;
        }
    }
    return total;
}

/* . */
void
emb_length_histogram(EmbPattern *pattern, int *bins)
{
    if (pattern->stitch_list->count < 2) {
        return;
    }

    int i;
    for (i = 0; i <= NUMBINS; i++) {
        bins[i] = 0;
    }

    double max_stitchlength = emb_pattern_longest_stitch(pattern);
    EmbStitch prev_st = pattern->stitch_list->stitch[0];
    for (i = 1; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
            double length = emb_stitch_length(st, prev_st);
            int bin_number = (int)floor(NUMBINS*length/max_stitchlength);
            bins[bin_number]++;
        }
        prev_st = st;
    }
}

/* . */
void
emb_color_histogram(EmbPattern *pattern, int **bins)
{
    if (pattern->stitch_list->count < 2) {
        return;
    }

    int i, j;
    for (j = 0; j < pattern->thread_list->count; j++)
    for (i = 0; i <= NUMBINS; i++) {
        bins[j][i] = 0;
    }

    double max_stitchlength = emb_pattern_longest_stitch(pattern);
    EmbStitch prev_st = pattern->stitch_list->stitch[0];
    for (i = 1; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* Can't count first normal stitch. */
        if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
            double length = emb_stitch_length(st, prev_st);
            int bin_number = (int)floor(NUMBINS*length/max_stitchlength);
            bins[0][bin_number]++;
        }
        prev_st = st;
    }
}

/* . */
double
emb_total_thread_length(EmbPattern *pattern)
{
    if (pattern->stitch_list->count < 2) {
        return 0.0;
    }

    int i;
    double total = 0.0;
    EmbStitch prev_st = pattern->stitch_list->stitch[0];
    for (i = 1; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* Can't count first normal stitch. */
        if (st.flags == NORMAL) {
            total += emb_stitch_length(st, prev_st);
        }
        prev_st = st;
    }
    return total;
}

/* FIXME. */
double
emb_total_thread_of_color(EmbPattern *pattern, int thread_index)
{
    if (pattern->stitch_list->count < 2) {
        return 0.0;
    }

    int i;
    double total = 0.0;
    EmbStitch prev_st = pattern->stitch_list->stitch[0];
    for (i = 1; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* Can't count first normal stitch. */
        if (st.color == thread_index)
        if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
            total += emb_stitch_length(st, prev_st);
        }
        prev_st = st;
    }
    return total;
}

/* TODO: test this. */
char *
emb_get_svg_token(char *svg, char token[MAX_STRING_LENGTH])
{
    if (*svg == ' ') {
        svg++;
    }
    if (*svg == 0) {
        return NULL;
    }
    int i;
    for (i=0; i < MAX_STRING_LENGTH; i++) {
        token[i] = svg[i];
        if (token[i] == ' ') {
            token[i] = 0;
            svg += i;
            return svg;
        }
    }
    return NULL;
}

/* */
char *
emb_get_svg_vector(char *svg, EmbVector *v)
{
    char token[MAX_STRING_LENGTH];
    svg = emb_get_svg_token(svg, token);
    if (!svg) {
        return NULL;
    }
    v->x = atof(token);
    svg = emb_get_svg_token(svg, token);
    if (!svg) {
        return NULL;
    }
    v->y = atof(token);
    return svg;
}

#endif

