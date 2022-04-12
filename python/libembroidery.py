#!/usr/bin/env python3

r"""
Part of libembroidery

Copyright 2022 The Embroidermodder Team
Licensed under the terms of the zlib licence.

More Pythonic version of the generated bindings
that calls the generated bindings.

All of the object orientation happens here.
"""

import libembroidery_core as core

# Symbols we want to be passed to the interface unchanged.
NORMAL = core.NORMAL
END = core.END
numberOfFormats = core.numberOfFormats
#formatTable = core.formatTable

class array():
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

class pattern():
    """
    Syntactic sugar for the users of libembrodiery's
    python bindings to make the objects more
    Pythonic and object oriented.
    """
    def __init__(self):
        " . "
        self.data = core.EmbPattern()

    def end(self):
        " Place END symbol. "
        core.embPattern_end(self.data)
