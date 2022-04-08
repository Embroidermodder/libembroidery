#!/usr/bin/env python3

"""
Python Module for libembroidery.

Copyright 2018-2022 The Embroidermodder Team
Licensed under the terms of the zlib license.
"""

from libembcore import command

class Pattern():
    """
    EmbPattern wrapper, extends the Pattern class defined
    in libembcore which is how it interacts with the C memory structure.
    """
    def __init__(self):
        "Calls EmbPattern_create."
        self.home = [0.0, 0.0]
        return self

    def read(self, fname, fformat=-1):
        "."
        if fformat < 0:
            fformat = self.identify_format(fname)
        return

    def write(self, fname, fformat=-1):
        "."
        if fformat < 0:
            fformat = self.identify_format(fname)
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

    def convert_geometry(self, args):
        "."
        return

    def design_details(self, args):
        "."
        return

    def end(self, args):
        "."
        return

    def addCircleObjectAbs(self, args):
        "."
        return

    def addEllipseObjectAbs(self, args):
        "."
        return

    def addLineObjectAbs(self, args):
        "."
        return

    def addPathObjectAbs(self, args):
        "."
        return

    def addPointObjectAbs(self, args):
        "."
        return

    def addPolygonObjectAbs(self, args):
        "."
        return

    def addPolylineObjectAbs(self, args):
        "."
        return

    def add_rect(self, args):
        "."
        return

    def copy_stitch_listToPolylines(self, args):
        "."
        return

    def copy_polylinesToStitchList(self, args):
        "."
        return

    def move_stitchListToPolylines(self, args):
        "."
        return

    def move_polylinesToStitchList(self, args):
        "."
        return

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
