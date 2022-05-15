#!/usr/bin/env python3

r"""
    Embroidermodder 2.

    ------------------------------------------------------------

    Copyright 2013-2022 The Embroidermodder Team
    Embroidermodder 2 is Open Source Software.
    See LICENSE for licensing terms.

    ------------------------------------------------------------

    The SVG geometry objects class definitions.

    Design primatives that come pre-loaded that aren't part of the
    SVG spec are in config/design_primatives.py.
"""

from embroidermodder.geometry.tools import (
    Pen, Vector, vector_from_str, closest_vector
)
from embroidermodder.geometry.line import Line
from embroidermodder.geometry.rect import Rect
from embroidermodder.geometry.arc import Arc
from embroidermodder.geometry.circle import Circle
from embroidermodder.geometry.ellipse import Ellipse
from embroidermodder.geometry.parametric import Parametric
from embroidermodder.geometry.textsingle import TextSingle
from embroidermodder.geometry.text import Text
from embroidermodder.geometry.polygon import Polygon
from embroidermodder.geometry.polyline import Polyline
from embroidermodder.geometry.polylinearray import PolylineArray
