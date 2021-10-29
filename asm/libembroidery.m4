dnl MACRO LIBRARY
dnl
dnl Flag Defines
dnl ------------
dnl These mirror the first table in libembroidery_data.asm.
dnl
define(`svg_property_token_table', 0*4) dnl
define(`svg_attribute_token_table', 1*4) dnl
define(`svg_token_lists', 2*4) dnl
define(`brand_codes', 3*4) dnl
define(`image_frame', 4*4) dnl
define(`csv_header', 5*4) dnl
define(`max_header', 6*4) dnl
define(`csd_decoding_table', 7*4) dnl
define(`vip_decoding_table', 8*4) dnl
define(`format_list', 9*4) dnl
define(`svg_token_table', 10*4) dnl
define(`inkscape_token_table', 11*4) dnl
define(`svg_element_token_table', 12*4) dnl
define(`svg_media_property_token_table', 13*4) dnl
define(`stitch_labels', 14*4) dnl
define(`dxf_version_r', 15*4) dnl
define(`table_lengths', 16*4) dnl
dnl
define(`error_emb_sqrt', 17) dnl
define(`error_emb_atan2', 18) dnl
define(`error_hus_expand', 19) dnl
define(`error_hus_compress', 20) dnl
define(`error_arc_data', 21) dnl
define(`error_format_not_supported', 22) dnl
define(`error_line_intersection', 23) dnl
define(`error_line_parallel', 24) dnl
define(`error_normalize', 25) dnl
define(`error_pattern_no_stitches', 26) dnl
define(`error_pattern_open_file', 27) dnl
define(`error_vector_add', 28) dnl
define(`error_vector_average', 29) dnl
define(`error_vector_component_product', 30) dnl
define(`error_vector_multiply', 31) dnl
define(`error_vector_normal', 32) dnl
define(`error_vector_subtract', 33) dnl
define(`error_hide_stitches_no_pattern', 35) dnl
define(`error_fix_color_count_no_pattern', 36) dnl
define(`error_copy_stitch_list_no_pattern', 37) dnl
define(`error_copy_polylines_no_point_list', 38) dnl
define(`error_move_stitch_list_no_pattern', 39) dnl
define(`error_add_stitch_abs_no_pattern  40) dnl
define(`error_add_stitch_abs_multiple_end   41 dnl
define(`error_add_stitch_rel_no_pattern  42 dnl
define(`error_change_color_no_pattern 43 dnl
define(`error_pattern_read_unsupported   44 dnl
define(`error_pattern_write_unsupported  45 dnl
define(`error_pattern_scale 46 dnl
define(`error_bounding_box_no_pattern 47 dnl
define(`error_flip_horizontal_no_pattern 48 dnl
define(`error_flip_vertical_no_pattern   49 dnl
define(`error_flip_no_pattern  50 dnl
define(`error_combine_jump_stitches   51 dnl
define(`error_pattern_max_stitch_length  52 dnl
define(`error_pattern_center   53 dnl
define(`error_add_circle    54 dnl
define(`error_add_ellipse   55 dnl
define(`error_add_line  56 dnl
define(`error_add_path  57 dnl
define(`error_add_path_obj  58 dnl
define(`error_add_path_obj_empty  59 dnl
define(`error_add_point 60 dnl
define(`error_add_polygon_abs  61 dnl
define(`error_add_polygon_abs_obj 62 dnl
define(`error_add_polygon_abs_empty   63 dnl
define(`error_add_polyline_abs 64 dnl
define(`error_add_polyline_abs_obj    65 dnl
define(`error_add_polyline_abs_empty  66 dnl
define(`error_add_rect  67 dnl
define(`error_generate_satin_array_create   68 dnl
define(`error_generate_satin_result_memory  69 dnl
define(`error_render_stitches_result_memory 70 dnl
define(`error_read_no_pattern  71 dnl
define(`error_read_no_filename 72 dnl
define(`error_read_cannot_open 73 dnl
define(`error_cannot_open   74 dnl
define(`error_bcf_difat_sector_value  76 dnl
define(`error_read_sector_value   77 dnl
define(`error_bcf_fat_create   78 dnl
define(`error_col_empty_line   79 dnl
define(`error_compound_unexpected_object_type   82 dnl
define(`error_csv_string    83 dnl
define(`error_format_get_extension    84 dnl
define(`error_no_colors 85 dnl
define(`error_read_dxf  86 dnl
define(`error_unsupported   87 dnl
define(`error_hus_decompress_data 88 dnl
define(`error_hus_compress_data   89 dnl
define(`error_read_hus  90 dnl
define(`error_write_hus 91 dnl
define(`error_jef_hoop_no_pattern 92 dnl
define(`error_max_encode_no_file  93 dnl
define(`error_ofm_threads_library_name   94 dnl
define(`error_ofm_threads_color_name  95 dnl
define(`error_stx_thread_no_thread    97 dnl
define(`error_stx_thread_no_file  98 dnl
define(`error_encode_dst_x_out_of_range  102 dnl
define(`error_encode_dst_y_out_of_range  103 dnl
define(`error_encode_tap_x  104 dnl
define(`error_encode_tap_y  105 dnl
define(`error_vp3_read_string_file    113 dnl
define(`error_vp3_read_hoop_no_file   115 dnl
define(`error_number_of_colors 116 dnl
define(`error_check_color_byte_1  117 dnl
define(`error_check_color_byte_2  118 dnl
define(`error_check_color_byte_3  119 dnl
define(`error_format_vp3_cannot_read  120 dnl
define(`error_svg_add_attribute_no_element  121 dnl
define(`error_svg_create_element_null 125 dnl
define(`error_svg_get_value_no_element   126 dnl
define(`error_svg_get_value_no_name   127 dnl
define(`error_svg_add_no_pattern  128 dnl
define(`error_svg_add_invalid_path    130 dnl
define(`error_svg_add_realloc  131 dnl
define(`error_read_svg  133 dnl
define(`error_write_csv_0   134 dnl
define(`error_read_csv_0    135 dnl
define(`error_read_csv_1    136 dnl
define(`error_read_csv_2    137 dnl
 dnl
define(`brand_codes_length  24 dnl
define(`thread_type_length  35 dnl
define(`thread_color_offset 30 dnl
define(`thread_code  33 dnl

dnl /* path flag codes */ dnl
define(`LINETO    0 dnl
define(`MOVETO    1 dnl
define(`BULGETOCONTROL  2 dnl
define(`BULGETOEND   4 dnl
define(`ELLIPSETORAD 8 dnl
define(`ELLIPSETOEND 16 dnl
define(`CUBICTOCONTROL1 32 dnl
define(`CUBICTOCONTROL2 64 dnl
define(`CUBICTOEND   128 dnl
define(`QUADTOCONTROL   256 dnl
define(`QUADTOEND 512 dnl
dnl
define(`SVG_CREATOR_NULL    0 dnl
define(`SVG_CREATOR_EMBROIDERMODDER   1 dnl
define(`SVG_CREATOR_ILLUSTRATOR   2 dnl
define(`SVG_CREATOR_INKSCAPE   3 dnl
dnl
define(`SVG_EXPECT_NULL 0 dnl
define(`SVG_EXPECT_ELEMENT  1 dnl
define(`SVG_EXPECT_ATTRIBUTE   2 dnl
define(`SVG_EXPECT_VALUE    3 dnl
dnl
dnl  SVG_TYPES
dnl  ---------
define(`SVG_NULL', `0')dnl
define(`SVG_ELEMENT', `1')dnl
define(`SVG_PROPERTY', `2')dnl
define(`SVG_MEDIA_PROPERTY', `3')dnl
define(`SVG_ATTRIBUTE', `4')dnl
define(`SVG_CATCH_ALL', `5')dnl
dnl
dnl
dnl  Type of sector
dnl  --------------
define(`CompoundFileSector_MaxRegSector', 0xFFFFFFFA) dnl
define(`CompoundFileSector_DIFAT_Sector', 0xFFFFFFFC) dnl
define(`CompoundFileSector_FAT_Sector', 0xFFFFFFFD) dnl
define(`CompoundFileSector_EndOfChain', 0xFFFFFFFE) dnl
define(`CompoundFileSector_FreeSector', 0xFFFFFFFF) dnl
dnl
dnl
dnl  Type of directory object
dnl  ------------------------
define(`ObjectTypeUnknown', 0x00) dnl Probably unallocated
define(`ObjectTypeStorage', 0x01) dnl a directory type object
define(`ObjectTypeStream', 0x02) dnl a file type object
define(`ObjectTypeRootEntry', 0x05) dnl the root entry
dnl
dnl
dnl  Special values for Stream Identifiers
dnl  -------------------------------------
define(`CompoundFileStreamId_MaxRegularStreamId 0xFFFFFFFA ; < All real stream Ids are less than this dnl
define(`CompoundFileStreamId_NoStream 0xFFFFFFFF dnl There is no valid stream Id
dnl
define(`CSV_EXPECT_NULL 0 dnl
define(`CSV_EXPECT_QUOTE1  1 dnl
define(`CSV_EXPECT_QUOTE2  2 dnl
define(`CSV_EXPECT_COMMA   3 dnl
dnl
define(`CSV_MODE_NULL   0 dnl
define(`CSV_MODE_COMMENT   '#' dnl
define(`CSV_MODE_VARIABLE  '>' dnl
define(`CSV_MODE_THREAD '$' dnl
define(`CSV_MODE_STITCH '*' dnl
dnl
dnl DXF Version Identifiers
define(`DXF_VERSION_R10', `0') dnl
define(`DXF_VERSION_R11', `1') dnl
define(`DXF_VERSION_R12', `2') dnl
define(`DXF_VERSION_R13', `3') dnl
define(`DXF_VERSION_R14', `4') dnl
define(`DXF_VERSION_R15', `5') dnl
define(`DXF_VERSION_R18', `6') dnl
define(`DXF_VERSION_R21', `7') dnl
define(`DXF_VERSION_R24', `8') dnl
define(`DXF_VERSION_R27', `9') dnl
 dnl
define(`DXF_VERSION_2000   0 dnl
define(`DXF_VERSION_2002   1 dnl
define(`DXF_VERSION_2004   2 dnl
define(`DXF_VERSION_2006   3 dnl
define(`DXF_VERSION_2007   4 dnl
define(`DXF_VERSION_2009   5 dnl
define(`DXF_VERSION_2010   6 dnl
define(`DXF_VERSION_2013   7 dnl
 dnl
define(`MAX_LAYERS  16 dnl
define(`MAX_LAYER_NAME_LENGTH 30 dnl
 dnl
define(`HOOP_126X110    0 dnl
define(`HOOP_110X110    1 dnl
define(`HOOP_50X50  2 dnl
define(`HOOP_140X200    3 dnl
define(`HOOP_230X200    4 dnl
 dnl
define(`ELEMENT_XML 0 dnl
define(`ELEMENT_A   1 dnl
define(`ELEMENT_ANIMATE 2 dnl
define(`ELEMENT_ANIMATE_COLOR 3 dnl
define(`ELEMENT_ANIMATE_MOTION    4 dnl
define(`ELEMENT_ANIMATE_TRANSFORM 5 dnl
define(`ELEMENT_ANIMATION  6 dnl
define(`ELEMENT_AUDIO   7 dnl
define(`ELEMENT_CIRCLE  8 dnl
define(`ELEMENT_DEFS    9 dnl
define(`ELEMENT_DESC    10 dnl
define(`ELEMENT_DISCARD 11 dnl
define(`ELEMENT_ELLIPSE 12 dnl
define(`ELEMENT_FONT    13 dnl
define(`ELEMENT_FONT_FACE  14 dnl
define(`ELEMENT_FONT_FACE_SRC 15 dnl
define(`ELEMENT_FONT_FACE_URI 16 dnl
define(`ELEMENT_FOREIGN_OBJECT    17 dnl
define(`ELEMENT_G   18 dnl
define(`ELEMENT_GLYPH   19 dnl
define(`ELEMENT_HANDLER 20 dnl
define(`ELEMENT_HKERN   21 dnl
define(`ELEMENT_IMAGE   22 dnl
define(`ELEMENT_LINE    23 dnl
define(`ELEMENT_LINEAR_GRADIENT   24 dnl
define(`ELEMENT_LISTENER   25 dnl
define(`ELEMENT_METADATA   26 dnl
define(`ELEMENT_MISSING_GLYPH 27 dnl
define(`ELEMENT_MPATH   28 dnl
define(`ELEMENT_PATH    29 dnl
define(`ELEMENT_POLYGON 30 dnl
define(`ELEMENT_POLYLINE   31 dnl
define(`ELEMENT_PREFETCH   32 dnl
define(`ELEMENT_RADIAL_GRADIENT   33 dnl
define(`ELEMENT_RECT    34 dnl
define(`ELEMENT_SCRIPT  35 dnl
define(`ELEMENT_SET 36 dnl
define(`ELEMENT_SOLID_COLOR   37 dnl
define(`ELEMENT_STOP    38 dnl
define(`ELEMENT_SVG 39 dnl
define(`ELEMENT_SWITCH', 40 dnl
define(`ELEMENT_TBREAK', `41') dnl
define(`ELEMENT_TEXT', `42') dnl
define(`ELEMENT_TEXT_AREA', `43') dnl
define(`ELEMENT_TITLE', `44') dnl
define(`ELEMENT_TSPAN', `45') dnl
define(`ELEMENT_USE', `46') dnl
define(`ELEMENT_VIDEO', `47') dnl
define(`ELEMENT_UNKNOWN', `48') dnl
dnl
dnl
/* Machine codes for stitch flags */
 define(`NORMAL                  0 /* stitch to (x, y) */
 define(`JUMP                    1 /* move to (x, y) */
 define(`TRIM                    2 /* trim + move to (x, y) */
 define(`STOP                    4 /* pause machine for thread change */
 define(`SEQUIN                  8 /* sequin */
 define(`END                     16 /* end of program */

/* Format identifiers */
 define(`EMB_FORMAT_100          0
 define(`EMB_FORMAT_10O          1
 define(`EMB_FORMAT_ART          2
 define(`EMB_FORMAT_BMC          3
 define(`EMB_FORMAT_BRO          4
 define(`EMB_FORMAT_CND          5
 define(`EMB_FORMAT_COL          6
 define(`EMB_FORMAT_CSD          7
 define(`EMB_FORMAT_CSV          8
 define(`EMB_FORMAT_DAT          9
 define(`EMB_FORMAT_DEM          10
 define(`EMB_FORMAT_DSB          11
 define(`EMB_FORMAT_DST          12
 define(`EMB_FORMAT_DSZ          13
 define(`EMB_FORMAT_DXF          14
 define(`EMB_FORMAT_EDR          15
 define(`EMB_FORMAT_EMD          16
 define(`EMB_FORMAT_EXP          17
 define(`EMB_FORMAT_EXY          18
 define(`EMB_FORMAT_EYS          19
 define(`EMB_FORMAT_FXY          20
 define(`EMB_FORMAT_GC           21
 define(`EMB_FORMAT_GNC          22
 define(`EMB_FORMAT_GT           23
 define(`EMB_FORMAT_HUS          24
 define(`EMB_FORMAT_INB          25
 define(`EMB_FORMAT_INF          26
 define(`EMB_FORMAT_JEF          27
 define(`EMB_FORMAT_KSM          28
 define(`EMB_FORMAT_MAX          29
 define(`EMB_FORMAT_MIT          30
 define(`EMB_FORMAT_NEW          31
 define(`EMB_FORMAT_OFM          32
 define(`EMB_FORMAT_PCD          33
 define(`EMB_FORMAT_PCM          34
 define(`EMB_FORMAT_PCQ          35
 define(`EMB_FORMAT_PCS          36
 define(`EMB_FORMAT_PEC          37
 define(`EMB_FORMAT_PEL          38
 define(`EMB_FORMAT_PEM          39
 define(`EMB_FORMAT_PES          40
 define(`EMB_FORMAT_PHB          41
 define(`EMB_FORMAT_PHC          42
 define(`EMB_FORMAT_PLT          43
define(`EMB_FORMAT_RGB          44
define(`EMB_FORMAT_SEW          45
define(`EMB_FORMAT_SHV          46
define(`EMB_FORMAT_SST          47
define(`EMB_FORMAT_STX          48
define(`EMB_FORMAT_SVG          49
define(`EMB_FORMAT_T01          50
define(`EMB_FORMAT_T09          51
define(`EMB_FORMAT_TAP          52
define(`EMB_FORMAT_THR', `53')
define(`EMB_FORMAT_TXT', `54')
define(`EMB_FORMAT_U00', `55') dnl
define(`EMB_FORMAT_U01', `56') dnl
define(`EMB_FORMAT_VIP', `57') dnl
define(`EMB_FORMAT_VP3', `58') dnl
define(`EMB_FORMAT_XXX', `59') dnl
define(`EMB_FORMAT_ZSK', `60') dnl
dnl
dnl Thread color
 define(`Arc_Polyester           0
 define(`Arc_Rayon               1
 define(`CoatsAndClark_Rayon     2
 define(`Exquisite_Polyester     3
 define(`Fufu_Polyester          4
 define(`Fufu_Rayon              5
 define(`Hemingworth_Polyester   6
 define(`Isacord_Polyester       7
 define(`Isafil_Rayon            8
 define(`Marathon_Polyester      9
 define(`Marathon_Rayon          10
 define(`Madeira_Polyester       11
 define(`Madeira_Rayon           12
 define(`Metro_Polyester         13
 define(`Pantone                 14
 define(`RobisonAnton_Polyester  15
 define(`RobisonAnton_Rayon      16
 define(`Sigma_Polyester         17
 define(`Sulky_Rayon             18
 define(`ThreadArt_Rayon         19
 define(`ThreadArt_Polyester     20
 define(`ThreaDelight_Polyester  21
 define(`Z102_Isacord_Polyester  22
 define(`SVG_Colors              23
 define(`hus_thread              24
 define(`jef_thread              25
 define(`pcm_thread              26
 define(`pec_thread              27
 define(`shv_thread              28
 define(`dxf_color               29

 define(`EMB_ARC                 0
 define(`EMB_CIRCLE              1
 define(`EMB_ELLIPSE             2
 define(`EMB_FLAG                3
 define(`EMB_LINE                4
 define(`EMB_PATH                5
 define(`EMB_POINT               6
 define(`EMB_POLYGON             7
 define(`EMB_POLYLINE            8 
 define(`EMB_RECT                9
 define(`EMB_SPLINE              10
 define(`EMB_STITCH              11
 define(`EMB_THREAD              12
 define(`EMB_VECTOR              13
 define(`EMB_CHAR                14
 define(`EMB_ARRAY               15

 define(`EMBFORMAT_UNSUPPORTED   0
 define(`EMBFORMAT_STITCHONLY    1
 define(`EMBFORMAT_OBJECTONLY    2
 define(`EMBFORMAT_STCHANDOBJ    3 /* binary operation: 1+2=3 */

define(`numberOfFormats', `61')dnl
dnl
dnl  Structure sizes
dnl  ---------------------------------------------------------------------------
dnl
dnl  EmbTime uses 6 unsigned ints, 1 for each of (year, month, day, hour, minute
dnl  second) in that order.
dnl
define(`EmbTime_size', `6*8')dnl
dnl
dnl  EmbArray uses 3 of the integers used as pointers for a file_id, size and
dnl  and 1 unsigned char for a type.
dnl
define(`EmbArray_size, `3*8+1')dnl
dnl
dnl EmbColor uses the light primaries: red, green, blue in that order.
dnl unsigned char[3];
dnl
define(`EmbColor_size', `3')dnl
dnl
dnl  The basic type to represent points absolutely or represent directions.
dnl
dnl  Positive y is up, units are in mm.
dnl
dnl  EmbVector (float x, y);
define(`EmbVector_size', `2*4')dnl
dnl
dnl  EmbPoint has
dnl
define(`EmbPoint_size', `EmbVector_size + flag_size + EmbColor_size')dnl
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
dnl
typedef struct EmbThread_
{
    EmbColor color;
    char description[30];
    char catalogNumber[10];
} EmbThread;
dnl
typedef struct EmbHoop_
{
    float width;
    float height;
} EmbHoop;
dnl
typedef struct EmbEllipse_
{
    EmbVector center;
    EmbVector radius;
    float rotation;
    int lineType;
    EmbColor color;
} EmbEllipse;
dnl
typedef struct EmbArc_
{
    EmbVector start;  /* absolute position (not relative) */
    EmbVector mid;    /* absolute position (not relative) */
    EmbVector end;    /* absolute position (not relative) */
    int lineType;
    EmbColor color;
} EmbArc;
dnl
typedef struct EmbRect_
{
    float top;
    float left;
    float bottom;
    float right;
    int lineType;
    EmbColor color;
} EmbRect;
dnl
typedef struct EmbCircle_
{
    EmbVector center;
    float radius;
    int lineType;
    EmbColor color;
} EmbCircle;
dnl
typedef struct EmbPolygonObject_
{
    EmbArray* pointList;
    int lineType;
    EmbColor color;
} EmbPolygonObject;
dnl
typedef struct EmbSatinOutline_
{
    int length;
    EmbArray* side1;
    EmbArray* side2;
} EmbSatinOutline;
dnl
typedef struct EmbPolylineObject_
{
    EmbArray* pointList;
    int lineType;
    EmbColor color;
} EmbPolylineObject;
dnl
typedef struct EmbBezier_ {
    EmbVector start;
    EmbVector control1;
    EmbVector control2;
    EmbVector end;
} EmbBezier;
dnl
typedef struct EmbSplineObject_ {
    EmbBezier bezier;
    struct EmbSplineObject_* next;
    int lineType;
    EmbColor color;
} EmbSplineObject;
dnl
typedef struct EmbPointObject_ {
    float x;
    float y;
    int lineType;
    EmbColor color;
} EmbPointObject;
dnl
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
dnl
typedef struct EmbFormatList_
{
    char extension[7];
    char description[51];
    char reader;
    char writer;
    int type;
} EmbFormatList;
dnl
dnl  Macros that take arguments
dnl  ---------------------------------------------------------------------------
define(`label_counter', `0')dnl
define(`count', `define(`label_counter', incr(label_counter))$1')dnl
define(`join', `$1$2')dnl
define(`new_label', `join(`label', label_counter)')dnl
dnl
define(`min_int', `count
	cmp	$1, $2
	jlt	new_label
	mov	$1, $2
new_label:')dnl
dnl
define(`max_int', `count
	cmp	$1, $2
	jgt	new_label
	mov	$1, $2
new_label:')dnl
dnl
