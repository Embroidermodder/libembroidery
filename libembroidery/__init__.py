#!/usr/bin/env python3

r"""
Part of libembroidery

Copyright 2022 The Embroidermodder Team
Licensed under the terms of the zlib licence.

More Pythonic version of the generated bindings
that calls the generated bindings.

All of the object orientation happens here.
"""

from libembroidery.tools import (
    Pen, Vector, vector_from_str, closest_vector
)
from libembroidery.line import Line
from libembroidery.rect import Rect
from libembroidery.arc import Arc
from libembroidery.circle import Circle
from libembroidery.dimleader import DimLeader
from libembroidery.ellipse import Ellipse
from libembroidery.parametric import Parametric
from libembroidery.textsingle import TextSingle
from libembroidery.text import Text
from libembroidery.polygon import Polygon
from libembroidery.polyline import Polyline
from libembroidery.polylinearray import PolylineArray

NORMAL = 0
JUMP = 1
END = 16
numberOfFormats = 61
# formatTable = formatTable