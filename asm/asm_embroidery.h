#ifndef __LIBEMBROIDERY_HEADER_FOR_ASM__
#define __LIBEMBROIDERY_HEADER_FOR_ASM__


/*
 * Flag Defines
 * ------------
 * These mirror the first table in libembroidery_data.asm.
 */
	.equ svg_property_token_table, 0*4
	.equ svg_attribute_token_table, 1*4
	.equ svg_token_lists, 2*4
	.equ brand_codes, 3*4
	.equ image_frame, 4*4
	.equ csv_header, 5*4
	.equ max_header, 6*4
	.equ csd_decoding_table, 7*4
	.equ vip_decoding_table, 8*4
	.equ format_list, 9*4
	.equ svg_token_table, 10*4
	.equ inkscape_token_table, 11*4
	.equ svg_element_token_table, 12*4
	.equ svg_media_property_token_table, 13*4
	.equ stitch_labels, 14*4
	.equ dxf_version_r, 15*4
	.equ table_lengths, 16*4

	.equ error_emb_sqrt, 17
	.equ error_emb_atan2, 18
	.equ error_hus_expand, 19
	.equ error_hus_compress, 20
	.equ error_arc_data, 21
	.equ error_format_not_supported, 22
	.equ error_line_intersection, 23
	.equ error_line_parallel, 24
	.equ error_normalize, 25
	.equ error_pattern_no_stitches, 26
	.equ error_pattern_open_file, 27
	.equ error_vector_add, 28
	.equ error_vector_average, 29
	.equ error_vector_component_product, 30
	.equ error_vector_multiply, 31
	.equ error_vector_normal, 32
	.equ error_vector_subtract, 33
	.equ error_hide_stitches_no_pattern, 35
	.equ error_fix_color_count_no_pattern, 36
	.equ error_copy_stitch_list_no_pattern, 37
	.equ error_copy_polylines_no_point_list, 38
	.equ error_move_stitch_list_no_pattern, 39
	.equ error_add_stitch_abs_no_pattern, 40
	.equ error_add_stitch_abs_multiple_end, 41
	.equ error_add_stitch_rel_no_pattern, 42
	.equ error_change_color_no_pattern, 43
	.equ error_pattern_read_unsupported, 44
	.equ error_pattern_write_unsupported, 45
	.equ error_pattern_scale, 46
	.equ error_bounding_box_no_pattern, 47
	.equ error_flip_horizontal_no_pattern, 48
	.equ error_flip_vertical_no_pattern, 49
	.equ error_flip_no_pattern, 50
	.equ error_combine_jump_stitches, 51
	.equ error_pattern_max_stitch_length, 52
	.equ error_pattern_center, 53
	.equ error_add_circle, 54
	.equ error_add_ellipse, 55
	.equ error_add_line, 56
	.equ error_add_path, 57
	.equ error_add_path_obj, 58
	.equ error_add_path_obj_empty, 59
	.equ error_add_point, 60
	.equ error_add_polygon_abs, 61
	.equ error_add_polygon_abs_obj, 62
	.equ error_add_polygon_abs_empty, 63
	.equ error_add_polyline_abs, 64
	.equ error_add_polyline_abs_obj, 65
	.equ error_add_polyline_abs_empty, 66
	.equ error_add_rect, 67
	.equ error_generate_satin_array_create, 68
	.equ error_generate_satin_result_memory, 69
	.equ error_render_stitches_result_memory, 70
	.equ error_read_no_pattern, 71
	.equ error_read_no_filename, 72
	.equ error_read_cannot_open, 73
	.equ error_cannot_open, 74
	.equ error_bcf_difat_sector_value, 76
	.equ error_read_sector_value, 77
	.equ error_bcf_fat_create, 78
	.equ error_col_empty_line, 79
	.equ error_compound_unexpected_object_type, 82
	.equ error_csv_string, 83
	#if 0
	.equ error_format_get_extension    84
	.equ error_no_colors 85
	.equ error_read_dxf  86
	.equ error_unsupported   87
	.equ error_hus_decompress_data 88
	.equ error_hus_compress_data   89
	.equ error_read_hus  90
	.equ error_write_hus 91
	.equ error_jef_hoop_no_pattern 92
	.equ error_max_encode_no_file  93
	.equ error_ofm_threads_library_name   94
	.equ error_ofm_threads_color_name  95
	.equ error_stx_thread_no_thread    97
	.equ error_stx_thread_no_file  98
	.equ error_encode_dst_x_out_of_range  102
	.equ error_encode_dst_y_out_of_range  103
	.equ error_encode_tap_x  104
	.equ error_encode_tap_y  105
	.equ error_vp3_read_string_file    113
	.equ error_vp3_read_hoop_no_file   115
	.equ error_number_of_colors 116
	.equ error_check_color_byte_1  117
	.equ error_check_color_byte_2  118
	.equ error_check_color_byte_3  119
	.equ error_format_vp3_cannot_read  120
	.equ error_svg_add_attribute_no_element  121
	.equ error_svg_create_element_null 125
	.equ error_svg_get_value_no_element   126
	.equ error_svg_get_value_no_name, 127
	.equ error_svg_add_no_pattern, 128
	.equ error_svg_add_invalid_path, 130
	.equ error_svg_add_realloc, 131
	.equ error_read_svg, 133
	.equ error_write_csv_0, 134
	.equ error_read_csv_0, 135
	.equ error_read_csv_1, 136
	.equ error_read_csv_2, 137

	.equ brand_codes_length, 24
	.equ thread_type_length, 35
	.equ thread_color_offset, 30
	.equ thread_code, 33

/* path flag codes */
	.equ LINETO    0
	.equ MOVETO    1
	.equ BULGETOCONTROL  2
	.equ BULGETOEND   4
	.equ ELLIPSETORAD 8
	.equ ELLIPSETOEND 16
	.equ CUBICTOCONTROL1 32
	.equ CUBICTOCONTROL2 64
	.equ CUBICTOEND   128
	.equ QUADTOCONTROL   256
	.equ QUADTOEND 512

	.equ SVG_CREATOR_NULL, 0
	.equ SVG_CREATOR_EMBROIDERMODDER   1
	.equ SVG_CREATOR_ILLUSTRATOR   2
	.equ SVG_CREATOR_INKSCAPE   3

	.equ SVG_EXPECT_NULL 0
	.equ SVG_EXPECT_ELEMENT  1
	.equ SVG_EXPECT_ATTRIBUTE   2
	.equ SVG_EXPECT_VALUE    3

/*  SVG_TYPES
 *  ---------
 */
	.equ SVG_NULL, 0
	.equ SVG_ELEMENT, 1
	.equ SVG_PROPERTY, 2
	.equ SVG_MEDIA_PROPERTY, 3
	.equ SVG_ATTRIBUTE, 4
	.equ SVG_CATCH_ALL, 5

/*
 *  Type of sector
 *  --------------
 */
	.equ CompoundFileSector_MaxRegSector, 0xFFFFFFFA
	.equ CompoundFileSector_DIFAT_Sector, 0xFFFFFFFC
	.equ CompoundFileSector_FAT_Sector, 0xFFFFFFFD
	.equ CompoundFileSector_EndOfChain, 0xFFFFFFFE
	.equ CompoundFileSector_FreeSector, 0xFFFFFFFF

/*
 *  Type of directory object
 *  ------------------------
 */
	.equ ObjectTypeUnknown, 0x00 /* Probably unallocated */
	.equ ObjectTypeStorage, 0x01 /* a directory type object */
	.equ ObjectTypeStream, 0x02 /* a file type object */
	.equ ObjectTypeRootEntry, 0x05 /* the root entry */

/*
 *  Special values for Stream Identifiers
 *  -------------------------------------
 */
	.equ CompoundFileStreamId_MaxRegularStreamId 0xFFFFFFFA
	 /* < All real stream Ids are less than this */
	.equ CompoundFileStreamId_NoStream 0xFFFFFFFF
	 /* < There is no valid stream Id */

	.equ CSV_EXPECT_NULL, 0
	.equ CSV_EXPECT_QUOTE1, 1
	.equ CSV_EXPECT_QUOTE2, 2
	.equ CSV_EXPECT_COMMA, 3

	.equ CSV_MODE_NULL, 0
	.equ CSV_MODE_COMMENT, '#'
	.equ CSV_MODE_VARIABLE, '>'
	.equ CSV_MODE_THREAD, '$'
	.equ CSV_MODE_STITCH, '*'

/* DXF Version Identifiers */
	.equ DXF_VERSION_R10, `0'
	.equ DXF_VERSION_R11, `1'
	.equ DXF_VERSION_R12, `2'
	.equ DXF_VERSION_R13, `3'
	.equ DXF_VERSION_R14, `4'
	.equ DXF_VERSION_R15, `5'
	.equ DXF_VERSION_R18, `6'
	.equ DXF_VERSION_R21, `7'
	.equ DXF_VERSION_R24, `8'
	.equ DXF_VERSION_R27, `9'

	.equ DXF_VERSION_2000, 0
	.equ DXF_VERSION_2002, 1
	.equ DXF_VERSION_2004, 2
	.equ DXF_VERSION_2006, 3
	.equ DXF_VERSION_2007   4
	.equ DXF_VERSION_2009   5
	.equ DXF_VERSION_2010   6
	.equ DXF_VERSION_2013   7

	.equ MAX_LAYERS  16
	.equ MAX_LAYER_NAME_LENGTH 30

	.equ HOOP_126X110    0
	.equ HOOP_110X110    1
	.equ HOOP_50X50  2
	.equ HOOP_140X200    3
	.equ HOOP_230X200    4

	.equ ELEMENT_XML 0
	.equ ELEMENT_A   1
	.equ ELEMENT_ANIMATE 2
	.equ ELEMENT_ANIMATE_COLOR 3
	.equ ELEMENT_ANIMATE_MOTION    4
	.equ ELEMENT_ANIMATE_TRANSFORM 5
	.equ ELEMENT_ANIMATION  6
	.equ ELEMENT_AUDIO   7
	.equ ELEMENT_CIRCLE  8
	.equ ELEMENT_DEFS    9
	.equ ELEMENT_DESC    10
	.equ ELEMENT_DISCARD 11
	.equ ELEMENT_ELLIPSE 12
	.equ ELEMENT_FONT    13
	.equ ELEMENT_FONT_FACE  14
	.equ ELEMENT_FONT_FACE_SRC 15
	.equ ELEMENT_FONT_FACE_URI 16
	.equ ELEMENT_FOREIGN_OBJECT    17
	.equ ELEMENT_G   18
	.equ ELEMENT_GLYPH   19
	.equ ELEMENT_HANDLER 20
	.equ ELEMENT_HKERN   21
	.equ ELEMENT_IMAGE   22
	.equ ELEMENT_LINE    23
	.equ ELEMENT_LINEAR_GRADIENT   24
	.equ ELEMENT_LISTENER   25
	.equ ELEMENT_METADATA   26
	.equ ELEMENT_MISSING_GLYPH 27
	.equ ELEMENT_MPATH   28
	.equ ELEMENT_PATH    29
	.equ ELEMENT_POLYGON 30
	.equ ELEMENT_POLYLINE   31
	.equ ELEMENT_PREFETCH   32
	.equ ELEMENT_RADIAL_GRADIENT   33
	.equ ELEMENT_RECT    34
	.equ ELEMENT_SCRIPT  35
	.equ ELEMENT_SET 36
	.equ ELEMENT_SOLID_COLOR   37
	.equ ELEMENT_STOP    38
	.equ ELEMENT_SVG 39
	.equ ELEMENT_SWITCH, 40
	.equ ELEMENT_TBREAK, `41'
	.equ ELEMENT_TEXT, `42'
	.equ ELEMENT_TEXT_AREA, `43'
	.equ ELEMENT_TITLE, `44'
	.equ ELEMENT_TSPAN, `45'
	.equ ELEMENT_USE, `46'
	.equ ELEMENT_VIDEO, `47'
	.equ ELEMENT_UNKNOWN, `48'
dnl
dnl
/* Machine codes for stitch flags */
 	.equ NORMAL, 0 /* stitch to (x, y) */
 	.equ JUMP, 1 /* move to (x, y) */
 	.equ TRIM, 2 /* trim + move to (x, y) */
 	.equ STOP, 4 /* pause machine for thread change */
 	.equ SEQUIN, 8 /* sequin */
 	.equ END, 16 /* end of program */

/* Format identifiers */
 	.equ EMB_FORMAT_100          0
 	.equ EMB_FORMAT_10O          1
 	.equ EMB_FORMAT_ART          2
 	.equ EMB_FORMAT_BMC          3
 	.equ EMB_FORMAT_BRO          4
 	.equ EMB_FORMAT_CND          5
 	.equ EMB_FORMAT_COL          6
 	.equ EMB_FORMAT_CSD          7
 	.equ EMB_FORMAT_CSV          8
 	.equ EMB_FORMAT_DAT          9
 	.equ EMB_FORMAT_DEM          10
 	.equ EMB_FORMAT_DSB          11
 	.equ EMB_FORMAT_DST          12
 	.equ EMB_FORMAT_DSZ          13
 	.equ EMB_FORMAT_DXF          14
 	.equ EMB_FORMAT_EDR          15
 	.equ EMB_FORMAT_EMD          16
 	.equ EMB_FORMAT_EXP          17
 	.equ EMB_FORMAT_EXY          18
 	.equ EMB_FORMAT_EYS          19
 	.equ EMB_FORMAT_FXY          20
 	.equ EMB_FORMAT_GC           21
 	.equ EMB_FORMAT_GNC          22
 	.equ EMB_FORMAT_GT           23
 	.equ EMB_FORMAT_HUS          24
 	.equ EMB_FORMAT_INB          25
 	.equ EMB_FORMAT_INF          26
 	.equ EMB_FORMAT_JEF          27
 	.equ EMB_FORMAT_KSM          28
 	.equ EMB_FORMAT_MAX          29
 	.equ EMB_FORMAT_MIT          30
 	.equ EMB_FORMAT_NEW          31
 	.equ EMB_FORMAT_OFM          32
 	.equ EMB_FORMAT_PCD          33
 	.equ EMB_FORMAT_PCM          34
 	.equ EMB_FORMAT_PCQ          35
 	.equ EMB_FORMAT_PCS          36
 	.equ EMB_FORMAT_PEC          37
 	.equ EMB_FORMAT_PEL          38
 	.equ EMB_FORMAT_PEM          39
 	.equ EMB_FORMAT_PES          40
 	.equ EMB_FORMAT_PHB          41
 	.equ EMB_FORMAT_PHC          42
 	.equ EMB_FORMAT_PLT          43
	.equ EMB_FORMAT_RGB          44
	.equ EMB_FORMAT_SEW          45
	.equ EMB_FORMAT_SHV          46
	.equ EMB_FORMAT_SST          47
	.equ EMB_FORMAT_STX          48
	.equ EMB_FORMAT_SVG          49
	.equ EMB_FORMAT_T01          50
	.equ EMB_FORMAT_T09          51
	.equ EMB_FORMAT_TAP          52
	.equ EMB_FORMAT_THR, 53
	.equ EMB_FORMAT_TXT, 54
	.equ EMB_FORMAT_U00, 55
	.equ EMB_FORMAT_U01, 56
	.equ EMB_FORMAT_VIP, 57
	.equ EMB_FORMAT_VP3, 58
	.equ EMB_FORMAT_XXX, 59
	.equ EMB_FORMAT_ZSK, 60
dnl
dnl Thread color
 	.equ Arc_Polyester           0
 	.equ Arc_Rayon               1
 	.equ CoatsAndClark_Rayon     2
 	.equ Exquisite_Polyester     3
 	.equ Fufu_Polyester          4
 	.equ Fufu_Rayon              5
 	.equ Hemingworth_Polyester   6
 	.equ Isacord_Polyester       7
 	.equ Isafil_Rayon            8
 	.equ Marathon_Polyester      9
 	.equ Marathon_Rayon          10
 	.equ Madeira_Polyester       11
 	.equ Madeira_Rayon           12
 	.equ Metro_Polyester         13
 	.equ Pantone                 14
 	.equ RobisonAnton_Polyester  15
 	.equ RobisonAnton_Rayon      16
 	.equ Sigma_Polyester         17
 	.equ Sulky_Rayon             18
 	.equ ThreadArt_Rayon         19
 	.equ ThreadArt_Polyester     20
 	.equ ThreaDelight_Polyester  21
 	.equ Z102_Isacord_Polyester  22
 	.equ SVG_Colors              23
 	.equ hus_thread              24
 	.equ jef_thread              25
 	.equ pcm_thread              26
 	.equ pec_thread              27
 	.equ shv_thread              28
 	.equ dxf_color               29

 	.equ EMB_ARC, 0
 	.equ EMB_CIRCLE, 1
 	.equ EMB_ELLIPSE, 2
 	.equ EMB_FLAG, 3
 	.equ EMB_LINE, 4
 	.equ EMB_PATH, 5
 	.equ EMB_POINT, 6
 	.equ EMB_POLYGON, 7
 	.equ EMB_POLYLINE, 8 
 	.equ EMB_RECT, 9
 	.equ EMB_SPLINE, 10
 	.equ EMB_STITCH, 11
 	.equ EMB_THREAD, 12
 	.equ EMB_VECTOR, 13
 	.equ EMB_CHAR, 14
 	.equ EMB_ARRAY, 15

 	.equ EMBFORMAT_UNSUPPORTED, 0
 	.equ EMBFORMAT_STITCHONLY, 1
 	.equ EMBFORMAT_OBJECTONLY, 2
 	.equ EMBFORMAT_STCHANDOBJ, 3 /* binary operation: 1+2=3 */

	.equ numberOfFormats, 61

/*
 *  Structure sizes
 *  ---------------------------------------------------------------------------
 *
 *  EmbTime uses 6 unsigned ints, 1 for each of (year, month, day, hour, minute
 *  second) in that order.
 */
	.equ EmbTime_size, 6*8

/*  EmbArray uses 3 of the integers used as pointers for a file_id, size and
 *  and 1 unsigned char for a type.
 */
	.equ EmbArray_size, 3*8+1

/* EmbColor uses the light primaries: red, green, blue in that order.
 * unsigned char[3];
 */
	.equ EmbColor_size, 3

/*  The basic type to represent points absolutely or represent directions.
 *
 *  Positive y is up, units are in mm.
 *
 *  EmbVector (float x, y);
 */
	.equ EmbVector_size, 2*4

/*  EmbPoint has... */
	.equ EmbPoint_size, EmbVector_size + 1 + EmbColor_size

/*
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
{*/
  /*  char flags; */ /* uses codes defined above */
  /*  float x; */ /* absolute position (not relative) */
  /*  float y; */ /* positive is up, units are in mm  */
  /*  unsigned char color; */ /* color number for this stitch */ /* TODO: this should be called colorIndex since it is not an EmbColor */
/*} EmbStitch;
*/

/*
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
*/

/* absolute position (not relative) */
/*
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
*/

/*
dnl  Macros that take arguments
dnl  ---------------------------------------------------------------------------
	.equ label_counter, `0')dnl
	.equ count, `	.equ label_counter, incr(label_counter))$1')dnl
	.equ join, `$1$2')dnl
	.equ new_label, `join(`label, label_counter)')dnl
dnl
	.equ min_int, `count
	cmp	$1, $2
	jlt	new_label
	mov	$1, $2
new_label:')dnl
dnl
	.equ max_int, `count
	cmp	$1, $2
	jgt	new_label
	mov	$1, $2
new_label:')dnl
dnl
*/
#endif

#endif
