#!/usr/bin/env python3

"""
Python Module for libembroidery.

Copyright 2018-2022 The Embroidermodder Team
Licensed under the terms of the zlib license.
"""

from libembcore import command

"""
embLine_make(self, args)

embLine_normalVector(self, args)
embLine_intersectionPoint(self, args)

embPathObject_create(self, args)
embPathObject_free(self, args)

embThread_findNearestColor(self, args)
embThread_findNearestColor_fromThread(self, args)
embThread_getRandom(self, args)

embVector_normalize(self, args)
embVector_multiply(self, args)
embVector_add(self, args)
embVector_average(self, args)
embVector_subtract(self, args)
embVector_dot(self, args)
embVector_cross(self, args)
embVector_transpose_product(self, args)
embVector_length(self, args)
embVector_relativeX(self, args)
embVector_relativeY(self, args)
embVector_angle(self, args)
embVector_distance(self, args)
embVector_unit(self, args)

read_ppm_image(self, args)
write_ppm_image(self, args)
image_diff(self, args)
render_line(self, args)
embImage_render(self, args)
embImage_simulate(self, args)
render_postscript(self, args)

testMain(self, args)
convert(self, args)

hus_compress(self, args)
hus_decompress(self, args)

embArcObject_make(self, args)
embArcObject_create(self, args)

isArcClockwise(self, args)
getArcCenter(self, args)
getArcDataFromBulge(self, args)

getCircleCircleIntersections(self, args)
getCircleTangentPoints(self, args)

embColor_make(self, args)
embColor_create(self, args)
embColor_fromHexStr(self, args)
embColor_distance(self, args)

embImage_create(self, args)
embImage_free(self, args)

embEllipse_diameterX(self, args)
embEllipse_diameterY(self, args)
embEllipse_width(self, args)
embEllipse_height(self, args)

embEllipseObject_make(self, args)

threadColor(self, args)
threadColorNum(self, args)
threadColorName(self, args)

embTime_initNow(self, args)
embTime_time(self, args)

embPointObject_make(self, args)
embPointObject_create(self, args)

embSettings_init(self, args)

embSettings_home(self, args)
embSettings_setHome(self, args)

embPolygonObject_create(self, args)
embPolygonObject_free(self, args)
embPolylineObject_create(self, args)
embPolylineObject_free(self, args)

embSatinOutline_generateSatinOutline(self, args)
embSatinOutline_renderStitches(self, args)

pattern_convertGeometry(self, args)
pattern_designDetails(self, args)
pattern_end(self, args)

pattern_addCircleObjectAbs(self, args)
pattern_addEllipseObjectAbs(self, args)
pattern_addLineObjectAbs(self, args)
pattern_addPathObjectAbs(self, args)
pattern_addPointObjectAbs(self, args)
pattern_addPolygonObjectAbs(self, args)
pattern_addPolylineObjectAbs(self, args)
pattern_add_rect(self, args)

pattern_copyStitchListToPolylines(self, args)
pattern_copyPolylinesToStitchList(self, args)
pattern_moveStitchListToPolylines(self, args)
pattern_movePolylinesToStitchList(self, args)
"""

class Pattern():
    """
    EmbPattern wrapper, extends the Pattern class defined
    in libembcore which is how it interacts with the C memory
    structure.
    """
    def __init__(self):
        return self

    def read(self, fname, fformat=-1):
        "."
        if fformat < 0:
            self.read_auto(self, fname)
        return

    def read_auto(self, fname):
        "."
        return

    def write(self, fname, fformat=-1):
        "."
        if fformat < 0:
            self.write_auto(self, fname)
        return

    def write_auto(self, fname):
        "."
        return

    def create(self):
        "."
        return

    def hide_stitches_over_length(self):
        "."
        return

    def calc_bounding_box(self):
        "."
        return

    def flip_horizontal(self):
        "."
        return

    def flip_vertical(self):
        "."
        return

    def flip(self):
        "."
        return

    def combine_jump_stitches(self):
        "."
        return

    def correct_for_max_stitch_length(self):
        "."
        return

    def center(self):
        "."
        return

    def load_external_color_file(self):
        "."
        return

    def fix_color_count(self):
        "."
        return

    def add_thread(self):
        "."
        return

    def add_stitch_abs(self):
        "."
        return

    def add_stitch_rel(self):
        "."
        return

    def change_color(self):
        "."
        return

    def free(self):
        "."
        return

    def scale(self, x=1.0, y=1.0):
        "Scale the entire pattern."
        return self.command("scale %f %f" % (x, y))


def lyndenmayer_system(l_system, n=4):
    "Generate a fractal given the L-system description."
    return command("lyndenmayer_system %s %d" % (l_system, n))

def hilbert_curve(n=4):
    "Generate a hilbert curve fractal for n iterations.\n"
    return command("hilbert_curve %d" % n)

def identify_format(fname):
    "Return the identifier of a file given the filename."
    return command("emb_identify_format %s" % fname)

def convert(in_file, out_file):
    "Convert ."
    return command("convert %s %s" % (in_file, out_file))
