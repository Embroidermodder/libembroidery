/*
 * LIBEMBROIDERY HEADER
 * This file is part of libembroidery.
 *
 * Copyright 2018-2024 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * -----------------------------------------------------------------------------
 *
 * Note that all new defines start with "EMB_", all functions with "emb" and all
 * typedefs with "Emb" to protect against namespace pollution. (INCOMPLETE)
 */

#ifndef EMB_LIBRARY_HEADER__
#define EMB_LIBRARY_HEADER__

#ifdef __cplusplus
extern "C" {
#endif

#define EMB_LIB_VERSION_MAJOR          1
#define EMB_LIB_VERSION_MINOR          0
#define EMB_LIB_VERSION_PATCH          0
#define EMB_LIB_VERSION_TAG      "alpha"

/* MACROS
 *****************************************************************************
 *
 * Machine codes for stitch flags.
 * These all represent distinct bits as some of them can be combined on some
 * machines.
 *
 * Missing change color?
 *
 * Stitch to (x, y). */
#define NORMAL                      0x00
/* Move to (x, y). */
#define JUMP                        0x01
/* Trim and move to (x, y). */
#define TRIM                        0x02
/* Pause machine for a thread change. */
#define STOP                        0x04
/* Add a sequin at the current co-ordinates. */
#define SEQUIN                      0x08
/* end of program */
#define END                         0x10

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

#define EMBFORMAT_UNSUPPORTED                   0
#define EMBFORMAT_STITCHONLY                    1
#define EMBFORMAT_OBJECTONLY                    2
#define EMBFORMAT_STCHANDOBJ                    3 /* binary operation: 1+2=3 */

#define numberOfFormats                        61

#define CHUNK_SIZE                            128

#define EMB_MAX_LAYERS                         10
#define MAX_THREADS                           256
#define EMBFORMAT_MAXEXT                        3
/* maximum length of extension without dot */
#define EMBFORMAT_MAXDESC                      50
/* the longest possible description string length */
#define MAX_STITCHES                      1000000

/* Libembroidery's handling of integer types.
 */
#define EMB_BIG_ENDIAN                          0
#define EMB_LITTLE_ENDIAN                       1

/* Most machines are little endian (including the developer's), so default to
 * that.
 */
#define ENDIAN_HOST             EMB_LITTLE_ENDIAN

#define EMB_INT16_BIG                           2
#define EMB_INT16_LITTLE                        3
#define EMB_INT32_BIG                           4
#define EMB_INT32_LITTLE                        5

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
#define ObjectTypeUnknown   0x00 /*!< Probably unallocated    */
#define ObjectTypeStorage   0x01 /*!< a directory type object */
#define ObjectTypeStream    0x02 /*!< a file type object      */
#define ObjectTypeRootEntry 0x05 /*!< the root entry          */

/**
 * Special values for Stream Identifiers
 */
#define CompoundFileStreamId_MaxRegularStreamId 0xFFFFFFFA /*!< All real stream Ids are less than this */
#define CompoundFileStreamId_NoStream           0xFFFFFFFF /*!< There is no valid stream Id            */

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

/* INTERNAL DEFINES */
#define RED_TERM_COLOR      "\x1B[0;31m"
#define GREEN_TERM_COLOR    "\x1B[0;32m"
#define YELLOW_TERM_COLOR   "\x1B[1;33m"
#define RESET_TERM_COLOR       "\033[0m"

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

/* same order as flag_list, to use in jump table */
#define FLAG_TO                        0
#define FLAG_TO_SHORT                  1
#define FLAG_HELP                      2
#define FLAG_HELP_SHORT                3
#define FLAG_FORMATS                   4
#define FLAG_FORMATS_SHORT             5
#define FLAG_QUIET                     6
#define FLAG_QUIET_SHORT               7
#define FLAG_VERBOSE                   8
#define FLAG_VERBOSE_SHORT             9
#define FLAG_VERSION                  10
#define FLAG_VERSION_SHORT            11
#define FLAG_CIRCLE                   12
#define FLAG_CIRCLE_SHORT             13
#define FLAG_ELLIPSE                  14
#define FLAG_ELLIPSE_SHORT            15
#define FLAG_LINE                     16
#define FLAG_LINE_SHORT               17
#define FLAG_POLYGON                  18
#define FLAG_POLYGON_SHORT            19
#define FLAG_POLYLINE                 20
#define FLAG_POLYLINE_SHORT           21
#define FLAG_RENDER                   22
#define FLAG_RENDER_SHORT             23
#define FLAG_SATIN                    24
#define FLAG_SATIN_SHORT              25
#define FLAG_STITCH                   26
#define FLAG_STITCH_SHORT             27
#define FLAG_TEST                     28
#define FLAG_FULL_TEST_SUITE          29
#define FLAG_CONVERT_TEST             30
#define FLAG_HILBERT_CURVE            31
#define FLAG_SIERPINSKI_TRIANGLE      32
#define FLAG_FILL                     33
#define FLAG_FILL_SHORT               34
#define FLAG_SIMULATE                 35
#define FLAG_COMBINE                  36
#define FLAG_CROSS_STITCH             37
#define NUM_FLAGS                     38

/* LANGUAGES */
#define LANG_SVG                       0
#define LANG_PS                        1
#define LANG_PROMPT                    2

/* COMMANDS
 *
 * These identifiers are subject to change since they are in alphabetical order
 * and the numbers are increasing.
 *
 * Note that GUI-only commands are present here because this is for operations
 * available in all frontends.
 *
 * The actuator uses
 */
#define EMB_CMD_ABOUT                  0
#define EMB_CMD_ARC                    1
#define EMB_CMD_CIRCLE                 2
#define EMB_CMD_DIM_LEADER             3
#define EMB_CMD_ELLIPSE                4
#define EMB_CMD_HORIZONTAL_DIMENSION   6
#define EMB_CMD_IMAGE                  7
#define EMB_CMD_INFINITE_LINE          8
#define EMB_CMD_LINE                   9
#define EMB_CMD_PATH                  10
#define EMB_CMD_POINT                 11
#define EMB_CMD_POLYGON               12
#define EMB_CMD_POLYLINE              13
#define EMB_CMD_RAY                   14
#define EMB_CMD_RECTANGLE             15
#define EMB_CMD_REGULAR_POLYGON       16
#define EMB_CMD_ROUNDED_RECTANGLE     17
#define EMB_CMD_RUBBER                18
#define EMB_CMD_SLOT                  19
#define EMB_CMD_TEXT_MULTI            20
#define EMB_CMD_TEXT_SINGLE           21
#define EMB_CMD_ADD_TO_SELECTION      22
#define EMB_CMD_TRIANGLE              23
#define EMB_CMD_VERTICAL_DIMENSION    24
#define EMB_CMD_ALERT                 25
#define EMB_CMD_ALLOW_RUBBER          26
#define EMB_CMD_APPEND_HISTORY        27
#define EMB_CMD_CALCULATE_ANGLE       28
#define EMB_CMD_CALCULATE_DISTANCE    29
#define EMB_CMD_CHANGELOG             30
#define EMB_CMD_CLEAR_RUBBER          31
#define EMB_CMD_CLEAR_SELECTION       32
#define EMB_CMD_COPY                  33
#define EMB_CMD_COPY_SELECTED         34
#define EMB_CMD_CUT                   35
#define EMB_CMD_CUT_SELECTED          36
#define EMB_CMD_DAY                   37
#define EMB_CMD_DEBUG                 38
#define EMB_CMD_DELETE_SELECTED       39
#define EMB_CMD_DESIGN_DETAILS        40
#define EMB_CMD_DO_NOTHING            41
#define EMB_CMD_END                   42
#define EMB_CMD_ERROR                 43
#define EMB_CMD_HELP                  44
#define EMB_CMD_ICON                             45
#define EMB_CMD_INIT                             51
#define EMB_CMD_MESSAGEBOX                       52
#define EMB_CMD_MIRROR_SELECTED                  53
#define EMB_CMD_MOUSE_X                          54
#define EMB_CMD_MOUSE_Y                          55
#define EMB_CMD_MOVE_SELECTED                    56
#define EMB_CMD_NEW                              57
#define EMB_CMD_NIGHT                            58
#define EMB_CMD_NUM_SELECTED                     59
#define EMB_CMD_OPEN                             60
#define EMB_CMD_PAN_UP                           61
#define EMB_CMD_PASTE                            62
#define EMB_CMD_PASTE_SELECTED                   63
#define EMB_CMD_PERPENDICULAR_DISTANCE           64
#define EMB_CMD_PLATFORM                         65
#define EMB_CMD_PREVIEW_OFF                      66
#define EMB_CMD_PREVIEW_ON                       67
#define EMB_CMD_PRINT                            68
#define EMB_CMD_PRINT_AREA                       69
#define EMB_CMD_QSNAP_X                          70
#define EMB_CMD_QSNAP_Y                          71
#define EMB_CMD_EXIT                             72
#define EMB_CMD_REDO                             73
#define EMB_CMD_ROTATE_SELECTED                  74
#define EMB_CMD_RUBBER                           75
#define EMB_CMD_SCALE_SELECTED                   76
#define EMB_CMD_SELECT_ALL                       77
#define EMB_CMD_SETTINGS_DIALOG                  78
#define EMB_CMD_SET                              79
#define EMB_CMD_SPARE_RUBBER                     80
#define EMB_CMD_TIP_OF_THE_DAY                   81
#define EMB_CMD_TODO                             82
#define EMB_CMD_UNDO                             83
#define EMB_CMD_VERSION                          84
#define EMB_CMD_VULCANIZE                        85
#define EMB_CMD_WHATS_THIS                       86
#define EMB_CMD_WINDOW                           87
#define EMB_CMD_ZOOM                             88
#define EMB_CMD_TEST                             89
#define EMB_CMD_SLEEP                            90
#define EMB_CMD_LAYER_EDITOR                     91
#define EMB_CMD_MAKE_LAYER_CURRENT               92
#define EMB_CMD_TEXT                             93
#define EMB_CMD_LAYER_PREVIOUS                   94
#define EMB_CMD_SAVE                             95
#define EMB_CMD_SAVEAS                           96
#define EMB_CMD_LAYERS                           97
#define EMB_CMD_LAYER_SELECTOR                   98
#define EMB_CMD_TREBLECLEF                       99
#define EMB_CMD_COLOR_SELECTOR                  100
#define EMB_CMD_LINE_TYPE_SELECTOR              101
#define EMB_CMD_LINE_WEIGHT_SELECTOR            102
#define EMB_CMD_HIDE_ALL_LAYERS                 103
#define EMB_CMD_ADD_HEART                       104
#define EMB_CMD_ADD_SINGLE_LINE_TEXT            105
#define EMB_CMD_SHOW_ALL_LAYERS                 106
#define EMB_CMD_FREEZE_ALL_LAYERS               107
#define EMB_CMD_THAW_ALL_LAYERS                 108
#define EMB_CMD_LOCK_ALL_LAYERS                 109
#define EMB_CMD_UNLOCK_ALL_LAYERS               110
#define EMB_CMD_ADD_DOLPHIN                     111
#define EMB_CMD_ADD_DISTANCE                    112
#define EMB_CMD_LOCATE_POINT                    113
#define EMB_CMD_QUICKSELECT                     114
#define EMB_CMD_SPELLCHECK                      115
#define EMB_CMD_DISTANCE                        116
#define EMB_CMD_MOVE                            117
#define EMB_CMD_QUICKLEADER                     118
#define EMB_CMD_RGB                             119
#define EMB_CMD_ROTATE                          120
#define EMB_CMD_SANDBOX                         121
#define EMB_CMD_ADD_SNOWFLAKE                   122
#define EMB_CMD_ADD_STAR                        123
#define EMB_CMD_DELETE                          124
#define EMB_CMD_SCALE                           125
#define EMB_CMD_SINGLE_LINE_TEXT                126
#define EMB_CMD_SYSWINDOWS                      127
#define EMB_CMD_ENABLE                          128
#define EMB_CMD_DISABLE                         129
#define EMB_CMD_SET_COLOR                       130
#define EMB_CMD_SET_BACKGROUND_COLOR            131
#define EMB_CMD_SET_CROSSHAIR_COLOR             132
#define EMB_CMD_SET_CURSOR_SHAPE                133
#define EMB_CMD_SET_GRID_COLOR                  134
#define EMB_CMD_SET_PROMPT_PREFIX               135
#define EMB_CMD_SET_RUBBER_FILTER               136
#define EMB_CMD_SET_RUBBER_MODE                 137
#define EMB_CMD_SET_RUBBER_POINT                138
#define EMB_CMD_SET_RUBBER_TEXT                 139
#define EMB_CMD_TEXT_BOLD                       140
#define EMB_CMD_TEXT_ITALIC                     141
#define EMB_CMD_TEXT_UNDERLINE                  142
#define EMB_CMD_TEXT_OVERLINE                   143
#define EMB_CMD_TEXT_STRIKEOUT                  144
#define EMB_CMD_WINDOW_TILE                     145
#define EMB_CMD_WINDOW_NEXT                     146
#define EMB_CMD_WINDOW_PREVIOUS                 147
#define EMB_CMD_WINDOW_CASCADE                  148
#define EMB_CMD_WINDOW_CLOSE                    149
#define EMB_CMD_WINDOW_CLOSE_ALL                150
#define EMB_CMD_ZOOM_ALL                        151
#define EMB_CMD_ZOOM_IN                         152
#define EMB_CMD_ZOOM_OUT                        153
#define EMB_CMD_ZOOM_CENTER                     154
#define EMB_CMD_ZOOM_SELECTED                   155
#define EMB_CMD_ZOOM_SCALE                      156
#define EMB_CMD_ZOOM_DYNAMIC                    157
#define EMB_CMD_ZOOM_PREVIOUS                   158
#define EMB_CMD_ZOOM_REAL_TIME                  159
#define EMB_CMD_ZOOM_WINDOW                     160
#define EMB_CMD_ZOOM_EXTENTS                    161
#define EMB_CMD_PAN_DOWN                        162
#define EMB_CMD_PAN_LEFT                        163
#define EMB_CMD_PAN_RIGHT                       164
#define EMB_CMD_PAN_POINT                       165
#define EMB_CMD_PAN_REAL_TIME                   166
#define N_COMMANDS                              167

/* Point identifiers. */
#define EMB_VECTOR_ARC_START_POINT                0
#define EMB_VECTOR_ARC_MID_POINT                  1
#define EMB_VECTOR_ARC_END_POINT                  2
#define EMB_VECTOR_ARC_POSITION                   3

/* Real Identifiers */
#define EMB_REAL_ARC_RADIUS                       0
#define EMB_REAL_START_ANGLE                      1
#define EMB_REAL_END_ANGLE                        2
#define EMB_REAL_ARC_DIAMETER                     3
#define EMB_REAL_ARC_AREA                         4
#define EMB_REAL_ARC_CIRCUMFERENCE                5
#define EMB_REAL_ARC_LENGTH                       6
#define EMB_REAL_CHORD                            7
#define EMB_REAL_TEXT                             8
#define EMB_REAL_TEXT_FONT                        9
#define EMB_REAL_TEXT_JUSTIFY                    10
#define EMB_REAL_TEXT_SIZE                       11
#define EMB_REAL_RADIUS_MAJOR                    12
#define EMB_REAL_RADIUS_MINOR                    13
#define EMB_REAL_DIAMETER_MAJOR                  14
#define EMB_REAL_DIAMETER_MINOR                  15
#define EMB_REAL_LENGTH                          16
#define EMB_REAL_AREA                            17
#define EMB_REAL_ANGLE                           18
#define EMB_REAL_WIDTH                           19
#define EMB_REAL_HEIGHT                          20

/* UTILITY MACROS
 * --------------
 */
#define EMB_MIN(A, B) (((A) < (B)) ? (A) : (B))
#define EMB_MAX(A, B) (((A) > (B)) ? (A) : (B))

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

/* TYPEDEFS AND STRUCTS
 *******************************************************************/

/* Should some platform need a different precision, this is typedef-ed
 * and used in place of all real types where possible.
 */
typedef float EmbReal;

/* EmbColor uses the light primaries: red, green, blue in that order. */
typedef struct EmbColor_
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
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
    unsigned char  signature[8];
    unsigned char  CLSID[16];
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
    bcf_file_header header;   /*! The header for the CompoundFile */
    bcf_file_difat* difat;    /*! The "Double Indirect FAT" for the CompoundFile */
    bcf_file_fat* fat;        /*! The File Allocation Table for the Compound File */
    bcf_directory* directory; /*! The directory for the CompoundFile */
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
    unsigned char numberOfColors;
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
    int someNum;      /*! \todo better variable naming */
    int someInt;      /*! \todo better variable naming */
    int someOtherInt; /*! \todo better variable naming */
    char* colorCode;
    char* colorName;
} SubDescriptor;

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
    unsigned char stringVal[8];
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

/* . */
typedef struct EmbImage_ {
    EmbVector position;
    EmbVector dimensions;
    unsigned char* data;
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

/* . */
typedef struct EmbStitch_
{
    int flags; /*! uses codes defined above */
    EmbReal x; /*! absolute position (not relative) */
    EmbReal y; /*! positive is up, units are in mm  */
    int color; /*! color number for this stitch */
    /*! \todo this should be called colorIndex since it is not an EmbColor */
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
    EmbReal top;
    EmbReal left;
    EmbReal bottom;
    EmbReal right;
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
typedef struct EmbEllipse_
{
    EmbVector center;
    EmbVector radius;
    EmbReal rotation;
} EmbEllipse;

/* . */
typedef struct EmbBezier_ {
    EmbVector start;
    EmbVector control1;
    EmbVector control2;
    EmbVector end;
} EmbBezier;

/* . */
typedef struct EmbSpline_ {
    EmbArray *beziers;
} EmbSpline;

/* . */
typedef struct LSYSTEM {
    char axiom;
    char *alphabet;
    char *constants;
    char **rules;
} L_system;

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
typedef struct EmbPattern_
{
    unsigned int dstJumpsPerTrim;
    EmbVector home;
    EmbReal hoop_width;
    EmbReal hoop_height;
    EmbArray *thread_list;
    EmbArray *stitch_list;
    EmbArray *geometry;
    EmbLayer layer[EMB_MAX_LAYERS];
    int currentColorIndex;
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

/* Function Declarations
*****************************************************************************/
EMB_PUBLIC int lindenmayer_system(L_system L, char* state, int iteration, int complete);
EMB_PUBLIC int hilbert_curve(EmbPattern *pattern, int iterations);

EMB_PUBLIC int emb_identify_format(const char *ending);
EMB_PUBLIC int convert(const char *inf, const char *outf);

EMB_PUBLIC void emb_processor(char *state, const char *program, int program_length);
EMB_PUBLIC int emb_compiler(const char *program, int language, char *compiled_program);
EMB_PUBLIC void emb_actuator(const char *program, int language);

EMB_PUBLIC EmbColor embColor_make(unsigned char r, unsigned char g, unsigned char b);
EMB_PUBLIC EmbColor embColor_fromHexStr(char* val);
EMB_PUBLIC int embColor_distance(EmbColor a, EmbColor b);

EMB_PUBLIC EmbArray* emb_array_create(int type);
EMB_PUBLIC int emb_array_resize(EmbArray *g);
EMB_PUBLIC void emb_array_copy(EmbArray *dst, EmbArray *src);
EMB_PUBLIC int emb_array_addArc(EmbArray* g, EmbArc arc);
EMB_PUBLIC int emb_array_addCircle(EmbArray* g, EmbCircle circle);
EMB_PUBLIC int emb_array_addEllipse(EmbArray* g, EmbEllipse ellipse);
EMB_PUBLIC int emb_array_addFlag(EmbArray* g, int flag);
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
EMB_PUBLIC EmbVector emb_line_intersectionPoint(EmbLine line1, EmbLine line2);

EMB_PUBLIC int embThread_findNearestColor(EmbColor color, EmbColor* colors, int n_colors);
EMB_PUBLIC int embThread_findNearestThread(EmbColor color, EmbThread* threads, int n_threads);
EMB_PUBLIC EmbThread embThread_getRandom(void);

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

EMB_PUBLIC EmbReal emb_get_real(EmbGeometry *g, int id);
EMB_PUBLIC EmbVector emb_get_vector(EmbGeometry *g, int id);
EMB_PUBLIC int emb_get_int(EmbGeometry *g, int id);

EMB_PUBLIC void emb_set_real(EmbGeometry *g, int id, EmbReal r);
EMB_PUBLIC void emb_set_vector(EmbGeometry *g, int id, EmbVector v);
EMB_PUBLIC void emb_set_int(EmbGeometry *g, int id, int i);

EMB_PUBLIC EmbArc emb_arc_init(void);
EMB_PUBLIC char emb_arc_clockwise(EmbArc arc);
EMB_PUBLIC EmbVector emb_arc_center(EmbArc arc);
EMB_PUBLIC EmbReal emb_arc_radius(EmbArc arc);
EMB_PUBLIC EmbReal emb_arc_diameter(EmbArc arc);
EMB_PUBLIC EmbReal emb_arc_chord(EmbArc arc);
EMB_PUBLIC EmbVector emb_arc_chordMid(EmbArc arc);
EMB_PUBLIC EmbReal emb_arc_sagitta(EmbArc arc);
EMB_PUBLIC EmbReal emb_arc_apothem(EmbArc arc);
EMB_PUBLIC EmbReal emb_arc_incAngle(EmbArc arc);
EMB_PUBLIC EmbReal emb_arc_bulge(EmbArc arc);

EMB_PUBLIC EmbCircle emb_circle_init(EmbReal x, EmbReal y, EmbReal r);
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

EMB_PUBLIC EmbRect embRect_init(void);
EMB_PUBLIC EmbReal embRect_area(EmbRect);

EMB_PUBLIC int threadColor(const char*, int brand);
EMB_PUBLIC int threadColorNum(unsigned int color, int brand);
EMB_PUBLIC const char* threadColorName(unsigned int color, int brand);

EMB_PUBLIC void embTime_initNow(EmbTime* t);
EMB_PUBLIC EmbTime embTime_time(EmbTime* t);

EMB_PUBLIC void embSatinOutline_generateSatinOutline(EmbArray* lines,
    EmbReal thickness, EmbSatinOutline* result);
EMB_PUBLIC EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result,
    EmbReal density);

EMB_PUBLIC EmbGeometry *embGeometry_init(int type_in);
EMB_PUBLIC void embGeometry_free(EmbGeometry *obj);
EMB_PUBLIC void embGeometry_move(EmbGeometry *obj, EmbVector delta);
EMB_PUBLIC EmbRect embGeometry_boundingRect(EmbGeometry *obj);
EMB_PUBLIC void embGeometry_vulcanize(EmbGeometry *obj);

EMB_PUBLIC EmbPattern* emb_pattern_create(void);
EMB_PUBLIC void emb_pattern_hideStitchesOverLength(EmbPattern* p, int length);
EMB_PUBLIC void emb_pattern_fixColorCount(EmbPattern* p);
EMB_PUBLIC int emb_pattern_addThread(EmbPattern* p, EmbThread thread);
EMB_PUBLIC void emb_pattern_addStitchAbs(EmbPattern* p, EmbReal x, EmbReal y,
    int flags, int isAutoColorIndex);
EMB_PUBLIC void emb_pattern_addStitchRel(EmbPattern* p, EmbReal dx, EmbReal dy, int flags, int isAutoColorIndex);
EMB_PUBLIC void emb_pattern_changeColor(EmbPattern* p, int index);
EMB_PUBLIC void emb_pattern_free(EmbPattern* p);
EMB_PUBLIC void emb_pattern_scale(EmbPattern* p, EmbReal scale);
EMB_PUBLIC EmbReal emb_pattern_totalStitchLength(EmbPattern *pattern);
EMB_PUBLIC EmbReal emb_pattern_minimumStitchLength(EmbPattern *pattern);
EMB_PUBLIC EmbReal emb_pattern_maximumStitchLength(EmbPattern *pattern);
EMB_PUBLIC void emb_pattern_lengthHistogram(EmbPattern *pattern, int *bin, int NUMBINS);
EMB_PUBLIC int emb_pattern_realStitches(EmbPattern *pattern);
EMB_PUBLIC int emb_pattern_jumpStitches(EmbPattern *pattern);
EMB_PUBLIC int emb_pattern_trimStitches(EmbPattern *pattern);
EMB_PUBLIC EmbRect emb_pattern_calcBoundingBox(EmbPattern* p);
EMB_PUBLIC void emb_pattern_flipHorizontal(EmbPattern* p);
EMB_PUBLIC void emb_pattern_flipVertical(EmbPattern* p);
EMB_PUBLIC void emb_pattern_flip(EmbPattern* p, int horz, int vert);
EMB_PUBLIC void emb_pattern_combineJumpStitches(EmbPattern* p);
EMB_PUBLIC void emb_pattern_correctForMaxStitchLength(EmbPattern* p, EmbReal maxStitchLength, EmbReal maxJumpLength);
EMB_PUBLIC void emb_pattern_center(EmbPattern* p);
EMB_PUBLIC void emb_pattern_loadExternalColorFile(EmbPattern* p, const char* fileName);
EMB_PUBLIC void emb_pattern_convertGeometry(EmbPattern* p);
EMB_PUBLIC void emb_pattern_designDetails(EmbPattern *p);
EMB_PUBLIC EmbPattern *emb_pattern_combine(EmbPattern *p1, EmbPattern *p2);
EMB_PUBLIC int emb_pattern_color_count(EmbPattern *pattern, EmbColor startColor);
EMB_PUBLIC void emb_pattern_end(EmbPattern* p);
EMB_PUBLIC void emb_pattern_crossstitch(EmbPattern *pattern, EmbImage *, int threshhold);
EMB_PUBLIC void emb_pattern_horizontal_fill(EmbPattern *pattern, EmbImage *, int threshhold);
EMB_PUBLIC int emb_pattern_render(EmbPattern *pattern, char *fname);
EMB_PUBLIC int emb_pattern_simulate(EmbPattern *pattern, char *fname);

EMB_PUBLIC void emb_pattern_addCircleAbs(EmbPattern* p, EmbCircle obj);
EMB_PUBLIC void emb_pattern_addEllipseAbs(EmbPattern* p, EmbEllipse obj);
EMB_PUBLIC void emb_pattern_addLineAbs(EmbPattern* p, EmbLine obj);
EMB_PUBLIC void emb_pattern_addPathAbs(EmbPattern* p, EmbPath obj);
EMB_PUBLIC void emb_pattern_addPointAbs(EmbPattern* p, EmbPoint obj);
EMB_PUBLIC void emb_pattern_addPolygonAbs(EmbPattern* p, EmbPolygon obj);
EMB_PUBLIC void emb_pattern_addPolylineAbs(EmbPattern* p, EmbPolyline obj);
EMB_PUBLIC void emb_pattern_addRectAbs(EmbPattern* p, EmbRect obj);

EMB_PUBLIC void emb_pattern_copyStitchListToPolylines(EmbPattern* pattern);
EMB_PUBLIC void emb_pattern_copyPolylinesToStitchList(EmbPattern* pattern);
EMB_PUBLIC void emb_pattern_moveStitchListToPolylines(EmbPattern* pattern);
EMB_PUBLIC void emb_pattern_movePolylinesToStitchList(EmbPattern* pattern);

EMB_PUBLIC char emb_pattern_read(EmbPattern *pattern, const char* fileName, int format);
EMB_PUBLIC char emb_pattern_write(EmbPattern *pattern, const char* fileName, int format);

EMB_PUBLIC char emb_pattern_readAuto(EmbPattern *pattern, const char* fileName);
EMB_PUBLIC char emb_pattern_writeAuto(EmbPattern *pattern, const char* fileName);

EMB_PUBLIC int emb_round(EmbReal x);
EMB_PUBLIC EmbReal radians(EmbReal degree);
EMB_PUBLIC EmbReal degrees(EmbReal radian);

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
extern const char imageWithFrame[38][48];


/* VARIABLES
 ******************************************************************************/

/* Error code storage for optional control flow blocking.
 *
 * This is potentially not thread-safe beacuse it is set by functions called
 * asyncronously and is global. If we only ever add to the variable then
 * an error cannot be missed because then at most one call per thread can
 * resolve before the check is performed and the status isn't overridden.
 */
extern int emb_error;

/* Verbosity level. */
extern int emb_verbose;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBEMBROIDERY_HEADER__ */

