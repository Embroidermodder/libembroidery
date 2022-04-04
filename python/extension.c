/* Python Extension for libembroidery.
 *
 * Copyright 2018-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include "../src/embroidery.h"
#include <Python.h>

static PyObject *method_lindenmayer_system(PyObject *self, PyObject *args);
static PyObject *method_hilbert_curve(PyObject *, PyObject *, PyObject *);

static PyObject *method_emb_identify_format(PyObject *self, PyObject *args);

static PyObject *method_embLine_make(PyObject *self, PyObject *args);

static PyObject *method_embLine_normalVector(PyObject *self, PyObject *args);
static PyObject *method_embLine_intersectionPoint(PyObject *self, PyObject *args);

static PyObject *method_embPathObject_create(PyObject *self, PyObject *args);
static PyObject *method_embPathObject_free(PyObject *self, PyObject *args);

static PyObject *method_embThread_findNearestColor(PyObject *self, PyObject *args);
static PyObject *method_embThread_findNearestColor_fromThread(PyObject *self, PyObject *args);
static PyObject *method_embThread_getRandom(PyObject *self, PyObject *args);

static PyObject *method_embVector_normalize(PyObject *self, PyObject *args);
static PyObject *method_embVector_multiply(PyObject *self, PyObject *args);
static PyObject *method_embVector_add(PyObject *self, PyObject *args);
static PyObject *method_embVector_average(PyObject *self, PyObject *args);
static PyObject *method_embVector_subtract(PyObject *self, PyObject *args);
static PyObject *method_embVector_dot(PyObject *self, PyObject *args);
static PyObject *method_embVector_cross(PyObject *self, PyObject *args);
static PyObject *method_embVector_transpose_product(PyObject *self, PyObject *args);
static PyObject *method_embVector_length(PyObject *self, PyObject *args);
static PyObject *method_embVector_relativeX(PyObject *self, PyObject *args);
static PyObject *method_embVector_relativeY(PyObject *self, PyObject *args);
static PyObject *method_embVector_angle(PyObject *self, PyObject *args);
static PyObject *method_embVector_distance(PyObject *self, PyObject *args);
static PyObject *method_embVector_unit(PyObject *self, PyObject *args);

static PyObject *method_read_ppm_image(PyObject *self, PyObject *args);
static PyObject *method_write_ppm_image(PyObject *self, PyObject *args);
static PyObject *method_image_diff(PyObject *self, PyObject *args);
static PyObject *method_render_line(PyObject *self, PyObject *args);
static PyObject *method_embImage_render(PyObject *self, PyObject *args);
static PyObject *method_embImage_simulate(PyObject *self, PyObject *args);
static PyObject *method_render_postscript(PyObject *self, PyObject *args);

static PyObject *method_testMain(PyObject *self, PyObject *args);
static PyObject *method_convert(PyObject *self, PyObject *args);

static PyObject *method_hus_compress(PyObject *self, PyObject *args);
static PyObject *method_hus_decompress(PyObject *self, PyObject *args);

static PyObject *method_embArcObject_make(PyObject *self, PyObject *args);
static PyObject *method_embArcObject_create(PyObject *self, PyObject *args);

static PyObject *method_isArcClockwise(PyObject *self, PyObject *args);
static PyObject *method_getArcCenter(PyObject *self, PyObject *args);
static PyObject *method_getArcDataFromBulge(PyObject *self, PyObject *args);

static PyObject *method_getCircleCircleIntersections(PyObject *self, PyObject *args);
static PyObject *method_getCircleTangentPoints(PyObject *self, PyObject *args);

static PyObject *method_embColor_make(PyObject *self, PyObject *args);
static PyObject *method_embColor_create(PyObject *self, PyObject *args);
static PyObject *method_embColor_fromHexStr(PyObject *self, PyObject *args);
static PyObject *method_embColor_read(PyObject *self, PyObject *args);
static PyObject *method_embColor_write(PyObject *self, PyObject *args);
static PyObject *method_embColor_distance(PyObject *self, PyObject *args);

static PyObject *method_embImage_create(PyObject *self, PyObject *args);
static PyObject *method_embImage_free(PyObject *self, PyObject *args);

static PyObject *method_embEllipse_diameterX(PyObject *self, PyObject *args);
static PyObject *method_embEllipse_diameterY(PyObject *self, PyObject *args);
static PyObject *method_embEllipse_width(PyObject *self, PyObject *args);
static PyObject *method_embEllipse_height(PyObject *self, PyObject *args);

static PyObject *method_embEllipseObject_make(PyObject *self, PyObject *args);

static PyObject *method_threadColor(PyObject *self, PyObject *args);
static PyObject *method_threadColorNum(PyObject *self, PyObject *args);
static PyObject *method_threadColorName(PyObject *self, PyObject *args);

static PyObject *method_embTime_initNow(PyObject *self, PyObject *args);
static PyObject *method_embTime_time(PyObject *self, PyObject *args);

static PyObject *method_embPointObject_make(PyObject *self, PyObject *args);
static PyObject *method_embPointObject_create(PyObject *self, PyObject *args);

static PyObject *method_embSettings_init(PyObject *self, PyObject *args);

static PyObject *method_embSettings_home(PyObject *self, PyObject *args);
static PyObject *method_embSettings_setHome(PyObject *self, PyObject *args);

static PyObject *method_embPolygonObject_create(PyObject *self, PyObject *args);
static PyObject *method_embPolygonObject_free(PyObject *self, PyObject *args);
static PyObject *method_embPolylineObject_create(PyObject *self, PyObject *args);
static PyObject *method_embPolylineObject_free(PyObject *self, PyObject *args);

static PyObject *method_embSatinOutline_generateSatinOutline(PyObject *self, PyObject *args);
static PyObject *method_embSatinOutline_renderStitches(PyObject *self, PyObject *args);

static PyObject *method_embRect_x(PyObject *self, PyObject *args);
static PyObject *method_embRect_y(PyObject *self, PyObject *args);
static PyObject *method_embRect_width(PyObject *self, PyObject *args);
static PyObject *method_embRect_height(PyObject *self, PyObject *args);

static PyObject *method_embRect_setX(PyObject *self, PyObject *args);
static PyObject *method_embRect_setY(PyObject *self, PyObject *args);
static PyObject *method_embRect_setWidth(PyObject *self, PyObject *args);
static PyObject *method_embRect_setHeight(PyObject *self, PyObject *args);

static PyObject *method_embRect_setCoords(PyObject *self, PyObject *args);
static PyObject *method_embRect_setRect(PyObject *self, PyObject *args);

static PyObject *method_embRectObject_make(PyObject *self, PyObject *args);

static PyObject *method_pattern_create(PyObject *self, PyObject *args);
static PyObject *method_pattern_hideStitchesOverLength(PyObject *self, PyObject *args);
static PyObject *method_pattern_fixColorCount(PyObject *self, PyObject *args);
static PyObject *method_pattern_addThread(PyObject *self, PyObject *args);
static PyObject *method_pattern_addStitchAbs(PyObject *self, PyObject *args);
static PyObject *method_pattern_addStitchRel(PyObject *self, PyObject *args);
static PyObject *method_pattern_changeColor(PyObject *self, PyObject *args);
static PyObject *method_pattern_free(PyObject *self, PyObject *args);
static PyObject *method_pattern_scale(PyObject *self, PyObject *args);
static PyObject *method_pattern_calcBoundingBox(PyObject *self, PyObject *args);
static PyObject *method_pattern_flipHorizontal(PyObject *self, PyObject *args);
static PyObject *method_pattern_flipVertical(PyObject *self, PyObject *args);
static PyObject *method_pattern_flip(PyObject *self, PyObject *args);
static PyObject *method_pattern_combineJumpStitches(PyObject *self, PyObject *args);
static PyObject *method_pattern_correctForMaxStitchLength(PyObject *self, PyObject *args);
static PyObject *method_pattern_center(PyObject *self, PyObject *args);
static PyObject *method_pattern_loadExternalColorFile(PyObject *self, PyObject *args);
static PyObject *method_pattern_convertGeometry(PyObject *self, PyObject *args);
static PyObject *method_pattern_designDetails(PyObject *self, PyObject *args);
static PyObject *method_pattern_end(PyObject *self, PyObject *args);

static PyObject *method_pattern_addCircleObjectAbs(PyObject *self, PyObject *args);
static PyObject *method_pattern_addEllipseObjectAbs(PyObject *self, PyObject *args);
static PyObject *method_pattern_addLineObjectAbs(PyObject *self, PyObject *args);
static PyObject *method_pattern_addPathObjectAbs(PyObject *self, PyObject *args);
static PyObject *method_pattern_addPointObjectAbs(PyObject *self, PyObject *args);
static PyObject *method_pattern_addPolygonObjectAbs(PyObject *self, PyObject *args);
static PyObject *method_pattern_addPolylineObjectAbs(PyObject *self, PyObject *args);
static PyObject *method_pattern_add_rect(PyObject *self, PyObject *args);

static PyObject *method_pattern_copyStitchListToPolylines(PyObject *self, PyObject *args);
static PyObject *method_pattern_copyPolylinesToStitchList(PyObject *self, PyObject *args);
static PyObject *method_pattern_moveStitchListToPolylines(PyObject *self, PyObject *args);
static PyObject *method_pattern_movePolylinesToStitchList(PyObject *self, PyObject *args);

static PyObject *method_pattern_read(PyObject *self, PyObject *args);
static PyObject *method_pattern_write(PyObject *self, PyObject *args);

static PyObject *method_pattern_readAuto(PyObject *self, PyObject *args);
static PyObject *method_pattern_writeAuto(PyObject *self, PyObject *args);

PyDoc_STRVAR(
    lyndenmayer_system_doc,
    "lyndenmayer_system(l_system, n=4)\n"
    "--\n"
    "\n"
    "Generate a fractal given the L-system description.\n"
);

PyDoc_STRVAR(
    hilbert_curve_doc,
    "hilbert_curve(n=4)\n"
    "--\n"
    "\n"
    "Generate a hilbert curve fractal for n iterations.\n"
);

PyDoc_STRVAR(
    identify_format_doc,
    "identify_format(fname)\n"
    "--\n"
    "\n"
    "Return the identifier of a file given the filename.\n"
);

PyDoc_STRVAR(
    embLine_make_doc,
    "embLine_make(x1, y1, x2, y2)\n"
    "--\n"
    "\n"
    "Build a libembroidery line.\n"
);

static PyMethodDef LibembroideryMethods[] = {
    {
        "lyndenmayer_system",
        (PyCFunction) method_lindenmayer_system,
        METH_VARARGS,
        lyndenmayer_system_doc
    },
    {
        "hilbert_curve",
        (PyCFunction) method_hilbert_curve,
        METH_VARARGS,
        hilbert_curve_doc
    },
    {
        "identify_format",
        (PyCFunction) method_emb_identify_format,
        METH_VARARGS,
        identify_format_doc
    },
    {
        "embLine_make",
        (PyCFunction) method_embLine_make,
        METH_VARARGS,
        embLine_make_doc
    },
    {
        "embLine_normalVector",
        method_embLine_normalVector,
        METH_VARARGS,
        "Find the normal to the supplied libembroidery line."
    },
    {
        "embLine_intersectionPoint",
        method_embLine_intersectionPoint,
        METH_VARARGS,
        "Find the intersection point of two lines."
    },
    {
        "embPathObject_create",
        method_embPathObject_create,
        METH_VARARGS,
        "."
    },
    {
        "embPathObject_free",
        method_embPathObject_free,
        METH_VARARGS,
        "."
    },
    {
        "embThread_findNearestColor",
        method_embThread_findNearestColor,
        METH_VARARGS,
        "."
    },
    {
        "embThread_findNearestColor_fromThread",
        method_embThread_findNearestColor_fromThread,
        METH_VARARGS,
        "."
    },
    {
        "embThread_getRandom",
        method_embThread_getRandom,
        METH_VARARGS,
        "."
    },
    {
        "embVector_normalize",
        method_embVector_normalize,
        METH_VARARGS,
        "."
    },
    {
        "embVector_multiply",
        method_embVector_multiply,
        METH_VARARGS,
        "."
    },
    {
        "embVector_add",
        method_embVector_add,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embVector_average,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embVector_subtract,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embVector_dot,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embVector_cross,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embVector_transpose_product,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embVector_length,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embVector_relativeX,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embVector_relativeY,
        METH_VARARGS,
        "."
    },
    {
        "embVector_angle",
        method_embVector_angle,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embVector_distance,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embVector_unit,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_read_ppm_image,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_write_ppm_image,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_image_diff,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_render_line,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embImage_render,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embImage_simulate,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_render_postscript,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_testMain,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_convert,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_hus_compress,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_hus_decompress,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embArcObject_make,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_embArcObject_create,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_isArcClockwise,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_getArcCenter,
        METH_VARARGS,
        "."
    },
    {
        "emb_identify_format",
        method_getArcDataFromBulge,
        METH_VARARGS,
        "."
    },
    {
        "getCircleCircleIntersections",
        method_getCircleCircleIntersections,
        METH_VARARGS,
        "."
    },
    {
        "getCircleTangentPoints",
        method_getCircleTangentPoints,
        METH_VARARGS,
        "."
    },
    {
        "embColor_make",
        method_embColor_make,
        METH_VARARGS,
        "."
    },
    {
        "embColor_create",
        method_embColor_create,
        METH_VARARGS,
        "."
    },
    {
        "embColor_fromHexStr",
        method_embColor_fromHexStr,
        METH_VARARGS,
        "."
    },
    {
        "embColor_read",
        method_embColor_read,
        METH_VARARGS,
        "."
    },
    {
        "embColor_write",
        method_embColor_write,
        METH_VARARGS,
        "."
    },
    {
        "embColor_distance",
        method_embColor_distance,
        METH_VARARGS,
        "."
    },
    {
        "embImage_create",
        method_embImage_create,
        METH_VARARGS,
        "."
    },
    {
        "embImage_free",
        method_embImage_free,
        METH_VARARGS,
        "."
    },
    {
        "embEllipse_diameterX",
        method_embEllipse_diameterX,
        METH_VARARGS,
        "."
    },
    {
        "embEllipse_diameterY",
        method_embEllipse_diameterY,
        METH_VARARGS,
        "."
    },
    {
        "embEllipse_width",
        method_embEllipse_width,
        METH_VARARGS,
        "."
    },
    {
        "embEllipse_height",
        method_embEllipse_height,
        METH_VARARGS,
        "."
    },
    {
        "embEllipseObject_make",
        method_embEllipseObject_make,
        METH_VARARGS,
        "."
    },
    {
        "threadColor",
        method_threadColor,
        METH_VARARGS,
        "."
    },
    {
        "threadColorNum",
        method_threadColorNum,
        METH_VARARGS,
        "."
    },
    {
        "threadColorName",
        method_threadColorName,
        METH_VARARGS,
        "."
    },
    {
        "embTime_initNow",
        method_embTime_initNow,
        METH_VARARGS,
        "."
    },
    {
        "embTime_time",
        method_embTime_time,
        METH_VARARGS,
        "."
    },
    {
        "embPointObject_make",
        method_embPointObject_make,
        METH_VARARGS,
        "."
    },
    {
        "embPointObject_create",
        method_embPointObject_create,
        METH_VARARGS,
        "."
    },
    {
        "embSettings_init",
        method_embSettings_init,
        METH_VARARGS,
        "."
    },
    {
        "embSettings_home",
        method_embSettings_home,
        METH_VARARGS,
        "."
    },
    {
        "embSettings_setHome",
        method_embSettings_setHome,
        METH_VARARGS,
        "."
    },
    {
        "embPolygonObject_create",
        method_embPolygonObject_create,
        METH_VARARGS,
        "."
    },
    {
        "embPolygonObject_free",
        method_embPolygonObject_free,
        METH_VARARGS,
        "."
    },
    {
        "embPolylineObject_create",
        method_embPolylineObject_create,
        METH_VARARGS,
        "."
    },
    {
        "embPolylineObject_free",
        method_embPolylineObject_free,
        METH_VARARGS,
        "."
    },
    {
        "embSatinOutline_generateSatinOutline",
        method_embSatinOutline_generateSatinOutline,
        METH_VARARGS,
        "."
    },
    {
        "embSatinOutline_renderStitches",
        method_embSatinOutline_renderStitches,
        METH_VARARGS,
        "."
    },
    {
        "embRect_x",
        method_embRect_x,
        METH_VARARGS,
        "."
    },
    {
        "embRect_y",
        method_embRect_y,
        METH_VARARGS,
        "."
    },
    {
        "embRect_width",
        method_embRect_width,
        METH_VARARGS,
        "."
    },
    {
        "embRect_height",
        method_embRect_height,
        METH_VARARGS,
        "."
    },
    {
        "embRect_setX",
        method_embRect_setX,
        METH_VARARGS,
        "."
    },
    {
        "embRect_setY",
        method_embRect_setY,
        METH_VARARGS,
        "."
    },
    {
        "embRect_set_width",
        method_embRect_setWidth,
        METH_VARARGS,
        "."
    },
    {
        "embRect_set_height",
        method_embRect_setHeight,
        METH_VARARGS,
        "."
    },
    {
        "embRect_setCoords",
        method_embRect_setCoords,
        METH_VARARGS,
        "."
    },
    {
        "embRect_set",
        method_embRect_setRect,
        METH_VARARGS,
        "."
    },
    {
        "embRect_make",
        method_embRectObject_make,
        METH_VARARGS,
        "."
    },
    {
        NULL,
        NULL,
        0,
        NULL
    }
};

static PyMethodDef pattern_methods[] = {
    {
        "create",
        method_pattern_create,
        METH_VARARGS,
        "."
    },
    {
        "hide_stitches_over_length",
        method_pattern_hideStitchesOverLength,
        METH_VARARGS,
        "."
    },
    {
        "fix_color_count",
        method_pattern_fixColorCount,
        METH_VARARGS,
        "."
    },
    {
        "add_thread",
        method_pattern_addThread,
        METH_VARARGS,
        "."
    },
    {
        "add_stitch_abs",
        method_pattern_addStitchAbs,
        METH_VARARGS,
        "."
    },
    {
        "add_stitch_rel",
        method_pattern_addStitchRel,
        METH_VARARGS,
        "."
    },
    {
        "change_color",
        method_pattern_changeColor,
        METH_VARARGS,
        "."
    },
    {
        "free",
        method_pattern_free,
        METH_VARARGS,
        "."
    },
    {
        "scale",
        method_pattern_scale,
        METH_VARARGS,
        "."
    },
    {
        "calc_bounding_box",
        method_pattern_calcBoundingBox,
        METH_VARARGS,
        "."
    },
    {
        "flip_horizontal",
        method_pattern_flipHorizontal,
        METH_VARARGS,
        "."
    },
    {
        "flip_vertical",
        method_pattern_flipVertical,
        METH_VARARGS,
        "pattern flip vertical."
    },
    {
        "flip",
        method_pattern_flip,
        METH_VARARGS,
        "Flip the pattern."
    },
    {
        "combineJumpStitches",
        method_pattern_combineJumpStitches,
        METH_VARARGS,
        "pattern combineJump Stitches."
    },
    {
        "correctForMaxStitchLength",
        method_pattern_correctForMaxStitchLength,
        METH_VARARGS,
        "pattern correct for max stitch length."
    },
    {
        "center",
        method_pattern_center,
        METH_VARARGS,
        "."
    },
    {
        "loadExternalColorFile",
        method_pattern_loadExternalColorFile,
        METH_VARARGS,
        "."
    },
    {
        "convertGeometry",
        method_pattern_convertGeometry,
        METH_VARARGS,
        "."
    },
    {
        "details",
        method_pattern_designDetails,
        METH_VARARGS,
        "."
    },
    {
        "end",
        method_pattern_end,
        METH_VARARGS,
        "Set the end symbol on the stitchlist, stitches after this will be ignored."
    },
    {
        "add_circle_abs",
        method_pattern_addCircleObjectAbs,
        METH_VARARGS,
        "Add a circle to the pattern."
    },
    {
        "add_ellipse_abs",
        method_pattern_addEllipseObjectAbs,
        METH_VARARGS,
        "Add an ellipse to the pattern."
    },
    {
        "addLineObjectAbs",
        method_pattern_addLineObjectAbs,
        METH_VARARGS,
        "Add a line to the pattern."
    },
    {
        "addPathObjectAbs",
        method_pattern_addPathObjectAbs,
        METH_VARARGS,
        "Add a path to the pattern."
    },
    {
        "add_point_abs",
        method_pattern_addPointObjectAbs,
        METH_VARARGS,
        "Add a point to the pattern."
    },
    {
        "add_polygon_abs",
        method_pattern_addPolygonObjectAbs,
        METH_VARARGS,
        "Add a polygon to the pattern."
    },
    {
        "add_polyline_abs",
        method_pattern_addPolylineObjectAbs,
        METH_VARARGS,
        "Add a polyline to the pattern."
    },
    {
        "add_rect_abs",
        method_pattern_add_rect,
        METH_VARARGS,
        "add_rect_abs."
    },
    {
        "copy_polyline_to_stitchlist",
        method_pattern_copyStitchListToPolylines,
        METH_VARARGS,
        "copy_polyline_to_stitchlist"
    },
    {
        "copy_polyline_to_stitchlist",
        method_pattern_copyPolylinesToStitchList,
        METH_VARARGS,
        "copy_polyline_to_stitchlist"
    },
    {
        "stitchlist_to_polylines",
        method_pattern_moveStitchListToPolylines,
        METH_VARARGS,
        "stitchlist_to_polylines"
    },
    {
        "polylines_to_stitchlist",
        method_pattern_movePolylinesToStitchList,
        METH_VARARGS,
        "polylines_to_stitchlist"
    },
    {
        "read",
        method_pattern_read,
        METH_VARARGS,
        "Read a file in based on the format identifier."
    },
    {
        "write",
        method_pattern_write,
        METH_VARARGS,
        "Write a file in based on the format identifier."
    },
    {
        "read_auto",
        method_pattern_readAuto,
        METH_VARARGS,
        "Detect the file type based on the passed filename,\nthen read in "
        "that format."
    },
    {
        "write_auto",
        method_pattern_writeAuto,
        METH_VARARGS,
        "Detect the file type based on the passed filename,\nthen write in "
        "that format."
    },
    {
        NULL,
        NULL,
        0,
        NULL
    }
};

static struct PyModuleDef libembroiderymodule = {
    PyModuleDef_HEAD_INIT,
    "libembroidery",
    "The Official Python interface to the libembroidery C library.",
    -1,
    LibembroideryMethods
};

typedef struct {
    PyObject_HEAD
    EmbPattern data;
} EmbPattern_wrapped;

static PyTypeObject libembroidery_pattern_type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "libembroidery.Pattern",
    .tp_doc = "EmbPattern wrapper",
    .tp_basicsize = sizeof(EmbPattern_wrapped),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_methods = pattern_methods,
};

PyMODINIT_FUNC
PyInit_libembroidery(void)
{
    PyObject *module;
    
    module = PyModule_Create(&libembroiderymodule);
    if (module == NULL)
        return NULL;

    Py_INCREF(&libembroidery_pattern_type);
    if (PyModule_AddObject(module, "Pattern", (PyObject *) &libembroidery_pattern_type) < 0) {
        Py_DECREF(&libembroidery_pattern_type);
        Py_DECREF(module);
        return NULL;
    }

    return module;
}

static PyObject *
method_lindenmayer_system(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_hilbert_curve(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = {
        "n",
        NULL
    };
    long n;
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|i", kwlist, &n)) {
        return NULL;
    }
    printf("hilbert_curve(n = %ld)\n", n);
    EmbPattern *pattern = embPattern_create();
    hilbert_curve(pattern, n);
    embPattern_free(pattern);
    return PyLong_FromLong(1);
}

static PyObject *
method_emb_identify_format(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embLine_make(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embLine_normalVector(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embLine_intersectionPoint(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embPathObject_create(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embPathObject_free(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embThread_findNearestColor(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embThread_findNearestColor_fromThread(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embThread_getRandom(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_normalize(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_multiply(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_add(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_average(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_subtract(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_dot(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_cross(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_transpose_product(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_length(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_relativeX(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_relativeY(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_angle(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_distance(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embVector_unit(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_read_ppm_image(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_write_ppm_image(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_image_diff(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_render_line(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embImage_render(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embImage_simulate(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_render_postscript(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_testMain(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_convert(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_hus_compress(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_hus_decompress(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embArcObject_make(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embArcObject_create(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_isArcClockwise(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_getArcCenter(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_getArcDataFromBulge(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_getCircleCircleIntersections(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_getCircleTangentPoints(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embColor_make(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embColor_create(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embColor_fromHexStr(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embColor_read(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embColor_write(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embColor_distance(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embImage_create(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embImage_free(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embEllipse_diameterX(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embEllipse_diameterY(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embEllipse_width(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embEllipse_height(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embEllipseObject_make(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_threadColor(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_threadColorNum(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_threadColorName(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embTime_initNow(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embTime_time(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embPointObject_make(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embPointObject_create(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embSettings_init(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embSettings_home(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embSettings_setHome(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embPolygonObject_create(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embPolygonObject_free(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embPolylineObject_create(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embPolylineObject_free(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embSatinOutline_generateSatinOutline(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embSatinOutline_renderStitches(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embRect_x(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embRect_y(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embRect_width(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embRect_height(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embRect_setX(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embRect_setY(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embRect_setWidth(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embRect_setHeight(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embRect_setCoords(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embRect_setRect(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_embRectObject_make(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_create(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_hideStitchesOverLength(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_fixColorCount(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_addThread(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_addStitchAbs(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_addStitchRel(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_changeColor(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_free(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_scale(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_calcBoundingBox(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_flipHorizontal(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_flipVertical(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_flip(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_combineJumpStitches(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_correctForMaxStitchLength(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_center(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_loadExternalColorFile(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_convertGeometry(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_designDetails(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_end(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_addCircleObjectAbs(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_addEllipseObjectAbs(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_addLineObjectAbs(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_addPathObjectAbs(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_addPointObjectAbs(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_addPolygonObjectAbs(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_addPolylineObjectAbs(PyObject *self, PyObject *args)
{
    puts("unfinished");
    /* embPattern_addPolylineObjectAbs(); */
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_add_rect(PyObject *self, PyObject *args)
{
    puts("unfinished");
    /* embPattern_addRectObjectAbs(); */
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_copyStitchListToPolylines(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_copyPolylinesToStitchList(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_moveStitchListToPolylines(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_movePolylinesToStitchList(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_read(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_write(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_readAuto(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}

static PyObject *
method_pattern_writeAuto(PyObject *self, PyObject *args)
{
    puts("unfinished");
    return PyLong_FromLong(1);
}
