/* embroidery.i */
%module libembroidery
%{
    #define SWIG_FILE_WITH_INIT
    #include "../src/embroidery.h"
%}

%feature("autodoc", "2");
%rename(identify_format) emb_identify_format;

%rename(array_create) embArray_create;
%rename(array_resize) embArray_resize;
%rename(array_copy) embArray_copy;
%rename(array_add_arc) embArray_addArc;
%rename(array_add_circle) embArray_addCircle;
%rename(array_add_ellipse) embArray_addEllipse;
%rename(array_add_flag) embArray_addFlag;
%rename(array_add_line) embArray_addLine;
%rename(array_add_rect) embArray_addRect;
%rename(array_add_path) embArray_addPath;
%rename(array_add_point) embArray_addPoint;
%rename(array_add_polygon) embArray_addPolygon;
%rename(array_add_polyline) embArray_addPolyline;
/* %rename(array_add_spline) embArray_addSpline; */
%rename(array_add_stitch) embArray_addStitch;
%rename(array_add_thread) embArray_addThread;
%rename(array_add_vector) embArray_addVector;
%rename(array_free) embArray_free;

%rename(line_make) embLine_make;

%rename(line_normal) embLine_normalVector;
%rename(line_intersection) embLine_intersectionPoint;

%rename(thread_find_nearest_color) embThread_findNearestColor;
%rename(thread_find_nearest_thread) embThread_findNearestColor_fromThread;
%rename(thread_random) embThread_getRandom;

%rename(vector_normalize) embVector_normalize;
%rename(vector_multiply) embVector_multiply;
%rename(vector_add) embVector_add;
%rename(vector_average) embVector_average;
%rename(vector_subtract) embVector_subtract;
%rename(vector_dot) embVector_dot;
%rename(vector_cross) embVector_cross;
%rename(vector_transpose_product) embVector_transpose_product;
%rename(vector_length) embVector_length;
%rename(vector_relative_x) embVector_relativeX;
%rename(vector_relative_y) embVector_relativeY;
%rename(vector_angle) embVector_angle;
%rename(vector_distance) embVector_distance;
%rename(vector_unit) embVector_unit;

%rename(color_make) embColor_make;
%rename(color_create) embColor_create;
%rename(color_from_hex) embColor_fromHexStr;
%rename(color_from_distance) embColor_distance;

%rename(image_create) embImage_create;
%rename(image_free) embImage_free;
%rename(image_render) embImage_render;
%rename(image_simulate) embImage_simulate;

%rename(ellipse_diameter_x) embEllipse_diameterX;
%rename(ellipse_diameter_y) embEllipse_diameterY;
%rename(ellipse_width) embEllipse_width;
%rename(ellipse_height) embEllipse_height;

%rename(pattern_create) embPattern_create;
%rename(pattern_hide_stitches_over) embPattern_hideStitchesOverLength;
%rename(pattern_fix_color_count) embPattern_fixColorCount;
%rename(pattern_add_thread) embPattern_addThread;
%rename(pattern_add_stitch_abs) embPattern_addStitchAbs;
%rename(pattern_add_stitch_rel) embPattern_addStitchRel;
%rename(pattern_change_color) embPattern_changeColor;
%rename(pattern_free) embPattern_free;
%rename(pattern_scale) embPattern_scale;
%rename(pattern_bounding_box) embPattern_calcBoundingBox;
%rename(pattern_flip_hor) embPattern_flipHorizontal;
%rename(pattern_flip_ver) embPattern_flipVertical;
%rename(pattern_flip) embPattern_flip;
%rename(pattern_combine_jump_stitches) embPattern_combineJumpStitches;
%rename(pattern_correct_for_max_stitch_length) embPattern_correctForMaxStitchLength;
%rename(pattern_center) embPattern_center;
%rename(pattern_load_external_color_file) embPattern_loadExternalColorFile;
%rename(pattern_convert_geometry) embPattern_convertGeometry;
%rename(pattern_design_details) embPattern_designDetails;
%rename(pattern_combine) embPattern_combine;
%rename(pattern_color_count) embPattern_color_count;
%rename(pattern_end) embPattern_end;

%rename(pattern_add_circle) embPattern_addCircleObjectAbs;
%rename(pattern_add_ellipse) embPattern_addEllipseObjectAbs;
%rename(pattern_add_line) embPattern_addLineObjectAbs;
%rename(pattern_add_path) embPattern_addPathObjectAbs;
%rename(pattern_add_point) embPattern_addPointObjectAbs;
%rename(pattern_add_polygon) embPattern_addPolygonObjectAbs;
%rename(pattern_add_polyline) embPattern_addPolylineObjectAbs;
%rename(pattern_add_rect) embPattern_addRectObjectAbs;

%rename(pattern_copy_stitchlist_to_polylines) embPattern_copyStitchListToPolylines;
%rename(pattern_copy_polylines_to_stitchlist) embPattern_copyPolylinesToStitchList;
%rename(pattern_move_stitchlist_to_polylines) embPattern_moveStitchListToPolylines;
%rename(pattern_move_polylines_to_stitchlist) embPattern_movePolylinesToStitchList;

%rename(pattern_read) embPattern_read;
%rename(pattern_write) embPattern_write;

%rename(pattern_read_auto) embPattern_readAuto;
%rename(pattern_write_auto) embPattern_writeAuto;

%include "../src/embroidery.h"
