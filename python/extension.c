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

static PyMethodDef LibembroideryMethods[] = {
    {
        "lyndenmayer_system",
        method_lindenmayer_system,
        METH_VARARGS,
        "Generate a fractal given the L-system description."
    },
    {
        "hilbert_curve",
        method_hilbert_curve,
        METH_VARARGS | METH_KEYWORDS,
        "Generate a hilbert curve fractal for n iterations."
    },
    {
        "identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
  /*
method_embLine_make
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embLine_normalVector
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embLine_intersectionPoint

    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embPathObject_create
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embPathObject_free
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embThread_findNearestColor
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embThread_findNearestColor_fromThread
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embThread_getRandom

    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_normalize
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_multiply
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_add
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_average
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_subtract
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_dot
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_cross
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_transpose_product
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_length
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_relativeX
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_relativeY
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_angle
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_distance
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embVector_unit
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_read_ppm_image
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_write_ppm_image
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_image_diff
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_render_line
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embImage_render
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embImage_simulate
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_render_postscript
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_testMain
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_convert
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_hus_compress
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_hus_decompress

    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embArcObject_make
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embArcObject_create

    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_isArcClockwise
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_getArcCenter
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_getArcDataFromBulge

    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_getCircleCircleIntersections
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_getCircleTangentPoints

    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embColor_make
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embColor_create
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embColor_fromHexStr
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embColor_read
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embColor_write
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embColor_distance

    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embImage_create
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embImage_free
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embEllipse_diameterX
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embEllipse_diameterY
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embEllipse_width
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embEllipse_height
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embEllipseObject_make
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_threadColor
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_threadColorNum
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_threadColorName
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embTime_initNow
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embTime_time
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embPointObject_make
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embPointObject_create
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embSettings_init
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embSettings_home
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embSettings_setHome
    {
        "emb_identify_format",
        method_emb_identify_format,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
method_embPolygonObject_create
    {
        "emb_identify_format",
method_embPolygonObject_free
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embPolylineObject_create
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embPolylineObject_free
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embSatinOutline_generateSatinOutline
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embSatinOutline_renderStitches
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embRect_x
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embRect_y,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embRect_width,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embRect_height
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embRect_setX
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embRect_setY
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embRect_setWidth
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embRect_setHeight
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embRect_setCoords
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embRect_setRect
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_embRectObject_make
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_create
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_hideStitchesOverLength
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_fixColorCount
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_addThread
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_addStitchAbs
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_addStitchRel
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_changeColor
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_free
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_scale
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_calcBoundingBox
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_flipHorizontal
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_flipVertical
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_flip
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_combineJumpStitches
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_correctForMaxStitchLength
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_center
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_loadExternalColorFile
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_convertGeometry,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "pattern_details",
        method_pattern_designDetails,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
        method_pattern_end,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_addCircleObjectAbs,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_addEllipseObjectAbs,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_addLineObjectAbs,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_addPathObjectAbs,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_addPointObjectAbs,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
method_pattern_addPolygonObjectAbs,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
    {
        "emb_identify_format",
        method_pattern_addPolylineObjectAbs,
        METH_VARARGS,
        "Return the identifier of a file given the filename."
    },
*/
    {
        "pattern_add_rect_abs",
        method_pattern_add_rect,
        METH_VARARGS,
        "pattern_add_rect_abs."
    },
    {
        "pattern_copy_polyline_to_stitchlist",
        method_pattern_copyStitchListToPolylines,
        METH_VARARGS,
        "pattern_copy_polyline_to_stitchlist"
    },
    {
        "pattern_copy_polyline_to_stitchlist",
        method_pattern_copyPolylinesToStitchList,
        METH_VARARGS,
        "pattern_copy_polyline_to_stitchlist"
    },
    {
        "pattern_stitchlist_to_polylines",
        method_pattern_moveStitchListToPolylines,
        METH_VARARGS,
        "pattern_stitchlist_to_polylines"
    },
    {
        "pattern_polylines_to_stitchlist",
        method_pattern_movePolylinesToStitchList,
        METH_VARARGS,
        "pattern_polylines_to_stitchlist"
    },
    {
        "pattern_read",
        method_pattern_read,
        METH_VARARGS,
        "Read a file in based on the format identifier."
    },
    {
        "pattern_write",
        method_pattern_write,
        METH_VARARGS,
        "Write a file in based on the format identifier."
    },
    {
        "pattern_read_auto",
        method_pattern_readAuto,
        METH_VARARGS,
        "Detect the file type based on the passed filename, then read in "
        "that format."
    },
    {
        "pattern_write_auto",
        method_pattern_writeAuto,
        METH_VARARGS,
        "Detect the file type based on the passed filename, then write in "
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

/*
static PyTypeObject libembroidery_patternType = {
    PyObject_HEAD_INIT(NULL
    0, // tp_name
    0, // tp_basicsize
    0, // tp_itemsize
    0, // tp_dealloc
    0, // tp_vectorcall_offset
    0, // (tp_getattr)
    0, // (tp_setattr)
    0, // tp_as_async
    0, // tp_repr
    0, // tp_as_number
    0, // tp_as_sequence
    0, // tp_as_mapping
    0, // tp_hash
    0, // tp_call
    0, // tp_str
    0, // tp_getattro
    0, // tp_setattro
    0, // tp_as_buffer
    0, // tp_flags
    0, // tp_doc
    0, // tp_traverse
    0, // tp_clear
    0, // tp_richcompare
    0, // tp_weaklistoffset
    0, // tp_iter
    0, // tp_iternext
    0, // tp_methods
    0, // tp_members
    0, // tp_getset
    0, // tp_base
    0, // tp_dict
    0, // tp_descr_get
    0, // tp_descr_set
    0, // tp_dictoffset
    0, // tp_init
    0, // tp_alloc
    0, // tp_new
    0, // tp_free
    0, // tp_is_gc
    0, // <tp_bases>
    0, // <tp_mro>
    0, // [tp_cache]
    0, // [tp_subclasses]
    0, // [tp_weaklist]
    0, // (tp_del)
    0, // tp_finalize
    0, // tp_vectorcall			
}
*/

PyMODINIT_FUNC PyInit_libembroidery(void) {
    return PyModule_Create(&libembroiderymodule);
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
    printf("hilbert_curve(n = %d)\n", n);
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
