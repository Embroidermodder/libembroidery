#!/usr/bin/env python3

r"""
Part of libembroidery

Copyright 2022 The Embroidermodder Team
Licensed under the terms of the zlib licence.

More Pythonic version of the generated bindings
that calls the generated bindings.

All of the object orientation happens here.
"""

NORMAL = 0
JUMP = 1
END = 16
numberOfFormats = 61
# formatTable = core.formatTable

# functions
convert = core.convert
emb_identify_format = core.emb_identify_format
hilbert_curve = core.hilbert_curve

# thread data
#black_thread = core.black_thread
Sulky_Rayon = core.Sulky_Rayon

class Array():
    def __init__(self):
        self.data = core.EmbArray()

class vector():
    """
    Syntactic sugar for the users of libembrodiery's
    python bindings to make the objects more
    Pythonic and object oriented.

    EmbVector() is still what the bindings use under
    the hood, but the user can create vectors like:

    import libembroidery_interface as emb
    a = emb.vector(1.0, 3.0)

    It would help to make the EmbArrays capable of
    dealing with these second-order wrapped functions.

    For example:

    import libembroidery_interface as emb
    A = [emb.vector(1.0, x) for x in range(100)]
    B = emb.array(A)
    """
    def __init__(self, x, y):
        " . "
        self.data = core.EmbVector()
        self.data.x = x
        self.data.y = y

    def copy(self):
        " . "
        return vector(self.x, self.y)

    def length(self):
        " Syntactic sugar for v.length(). "
        return core.embVector_length(self.data)

    def difference(self, b):
        " Syntactic sugar allowing a.difference(b). "
        c = self.copy()
        c.data.x -= b.data.x
        c.data.y -= b.data.y
        return c

    def distance(self, b):
        """
        The distance between two vectors aka |a-b|.
        Callable as a.distance(b).
        """
        return self.difference(b).length()

class arc():
    """
    Syntactic sugar for EmbColor for the users of
    libembrodiery's python bindings to make the objects
    more Pythonic and object oriented.
    """
    def __init__(self, x1, y1, x2, y2, x3, y3):
        self.data = core.EmbArc()
        self.data.start.x = x1
        self.data.start.y = y1
        self.data.mid.x = x2
        self.data.mid.y = x2
        self.data.end.x = x3
        self.data.end.y = y3

class color():
    """
    Syntactic sugar for EmbColor for the users of
    libembrodiery's python bindings to make the objects
    more Pythonic and object oriented.
    """
    def __init__(self, hex=0, rgb=""):
        self.data = core.EmbColor()
        if rgb != "":
            self.data.r = rgb[0]
            self.data.g = rgb[1]
            self.data.b = rgb[2]
            return
        self.data.r = 255
        self.data.g = 255
        self.data.b = 255

class circle():
    """
    Syntactic sugar for the users of libembrodiery's
    python bindings to make the objects more
    Pythonic and object oriented.
    """
    def __init__(self, x, y, r):
        self.data = core.EmbCircle()
        self.data.center.x = x
        self.data.center.y = y
        self.data.radius = r

class ellipse():
    """
    Syntactic sugar for the users of libembrodiery's
    python bindings to make the objects more
    Pythonic and object oriented.
    """
    def __init__(self, x, y, rx, ry):
        self.data = core.EmbEllipseObject()
        self.data.center.x = x
        self.data.center.y = y
        self.data.radius.x = rx
        self.data.radius.y = ry

class path():
    """
    Syntactic sugar for the users of libembrodiery's
    python bindings to make the objects more
    Pythonic and object oriented.
    """
    def __init__(self):
        self.data = core.EmbPathObject()


class image():
    """
    Syntactic sugar for the users of libembrodiery's
    python bindings to make the objects more
    Pythonic and object oriented.
    """
    def __init__(self, w, h):
        self.data = core.EmbImage()
        self.data.width = w
        self.data.height = h

    def render(self):
        core.embImage_render(self.data)    


def read(fname, fformat=-1):
    " . "
    if fformat >= 0:
        core.embCurrent_readAuto(fname)
    else:
        core.embCurrent_read(fname, fformat)


def write(fname, fformat=-1):
    " . "
    if fformat >= 0:
        core.embCurrent_writeAuto(fname)
    else:
        core.embCurrent_write(fname, fformat)


def addCircle(x, y, radius, absolute=True):
    " Add a circle to the pattern. "
    core.embCurrent_addCircleObjectAbs(x, y, radius)


def addEllipse(x, y, rx, ry, absolute=True):
    " Add an ellipse to the pattern. "
    core.embCurrent_addEllipseObjectAbs(x, y, rx, ry)


def addThread(color, absolute=True):
    " Add a thread to the pattern. "
    core.embCurrent_addThread(color)


def addStitch(x, y, flags, color, absolute=True):
    " Add a stitch to the pattern. "
    core.embCurrent_addStitchAbs(x, y, flags, color)


def end():
    " Place END symbol. "
    core.embCurrent_end()


def create():
    " Create the current pattern memory. "
    core.embCurrent_create()


def free():
    " Free the current pattern memory. "
    core.embCurrent_free()
