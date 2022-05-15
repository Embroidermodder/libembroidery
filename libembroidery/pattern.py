#!/usr/bin/env python3

r"""
    Embroidermodder 2.

    -----

    Copyright 2013-2022 The Embroidermodder Team
    Embroidermodder 2 is Open Source Software.
    See LICENSE for licensing terms.

    -----

    The Pattern class definition file.
"""

from libembroidery.tools import (convert, debug_message)


class Pattern():
    r"""
    While we're working out how to interface libembroidery
    and embroidermodder the Pattern is almost completely detatched from
    the python binding.

    We only interact with it by calling the libembroidery convert function
    to make it so we only need to import formats other than SVG and export
    to formats other than SVG.

    This leads to a few areas of repeated code that will have to do for now.
    The most important is that SVG needs to be parsable by both embroidermodder
    in Python and libembroidery in C.
    """
    def __init__(self, fname=""):
        r"""
        .
        """
        debug_message("")
        if len(fname) > 0:
            self.open(fname)

    def open(self, fname):
        r"""
        Open the file called fname and load the data to
        .
        """
        debug_message("")

    def save(self, fname):
        r"""
        .
        """
        debug_message("")

    def save_as(self, fname):
        r"""
        .
        """
        self.save("buffer_QFXZ.svg")
        convert("buffer_QFXZ.svg", fname)

    def read(fname, fformat=-1):
        " . "
        if fformat >= 0:
            embCurrent_readAuto(fname)
        else:
            embCurrent_read(fname, fformat)


    def write(fname, fformat=-1):
        " . "
        if fformat >= 0:
            embCurrent_writeAuto(fname)
        else:
            embCurrent_write(fname, fformat)


    def addCircle(x, y, radius, absolute=True):
        " Add a circle to the pattern. "
        embCurrent_addCircleObjectAbs(x, y, radius)


    def addEllipse(x, y, rx, ry, absolute=True):
        " Add an ellipse to the pattern. "
        embCurrent_addEllipseObjectAbs(x, y, rx, ry)


    def addThread(color, absolute=True):
        " Add a thread to the pattern. "
        embCurrent_addThread(color)


    def addStitch(x, y, flags, color, absolute=True):
        " Add a stitch to the pattern. "
        embCurrent_addStitchAbs(x, y, flags, color)


    def end():
        " Place END symbol. "
        embCurrent_end()


    def create():
        " Create the current pattern memory. "
        embCurrent_create()


    def free():
        " Free the current pattern memory. "
        embCurrent_free()
