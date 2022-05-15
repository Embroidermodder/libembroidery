#!/usr/bin/env python3

r"""
    Embroidermodder 2.

    ------------------------------------------------------------

    Copyright 2013-2022 The Embroidermodder Team
    Embroidermodder 2 is Open Source Software.
    See LICENSE for licensing terms.

    ------------------------------------------------------------

"""

import math

from embroidermodder.geometry.pen import Pen
from embroidermodder.geometry.vector import Vector
from embroidermodder.geometry.line import Line

class PolylineArray():
    " . "
    def __init__(self):
        " . "
        #Report number of pre-selected objects
        self.test1 = 0
        self.test2 = 0
        set_prompt_prefix("Number of Objects Selected: " + numSelected().toString())
        append_prompt_history()

        mirrorSelected(0,0,0,1)

        #selectAll();
        #rotateSelected(0,0,90);

        #Polyline & Polygon Testing

        offset_x = 0.0
        offset_y = 0.0

        polyline_array = []
        polyline_array.push(1.0 + offset_x)
        polyline_array.push(1.0 + offset_y)
        polyline_array.push(1.0 + offset_x)
        polyline_array.push(2.0 + offset_y)
        polyline_array.push(2.0 + offset_x)
        polyline_array.push(2.0 + offset_y)
        polyline_array.push(2.0 + offset_x)
        polyline_array.push(3.0 + offset_y)
        polyline_array.push(3.0 + offset_x)
        polyline_array.push(3.0 + offset_y)
        polyline_array.push(3.0 + offset_x)
        polyline_array.push(2.0 + offset_y)
        polyline_array.push(4.0 + offset_x)
        polyline_array.push(2.0 + offset_y)
        polyline_array.push(4.0 + offset_x)
        polyline_array.push(1.0 + offset_y)
        addPolyline(polyline_array)

        offset_x = 5.0
        offset_y = 0.0

        polygon_array = []
        polygon_array.push(1.0 + offset_x)
        polygon_array.push(1.0 + offset_y)
        polygon_array.push(1.0 + offset_x)
        polygon_array.push(2.0 + offset_y)
        polygon_array.push(2.0 + offset_x)
        polygon_array.push(2.0 + offset_y)
        polygon_array.push(2.0 + offset_x)
        polygon_array.push(3.0 + offset_y)
        polygon_array.push(3.0 + offset_x)
        polygon_array.push(3.0 + offset_y)
        polygon_array.push(3.0 + offset_x)
        polygon_array.push(2.0 + offset_y)
        polygon_array.push(4.0 + offset_x)
        polygon_array.push(2.0 + offset_y)
        polygon_array.push(4.0 + offset_x)
        polygon_array.push(1.0 + offset_y)
        addPolygon(polygon_array)
