#!/usr/bin/env python3

"""
Python Module for libembroidery.

Copyright 2018-2022 The Embroidermodder Team
Licensed under the terms of the zlib license.

Ideas for how to manage functions that aren't bound with equivalents.
"""

import math

"""
embPathObject_create(self, args)
embPathObject_free(self, args)

embThread_findNearestColor(self, args)
embThread_findNearestColor_fromThread(self, args)
embThread_getRandom(self, args)

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
"""

class Vector():
    """
    """
    def __init__(self, x, y):
        self.x = x
        self.y = y
        return self

    def length(self):
        "Returns the length of the vector."
        return math.sqrt(self.x*self.x + self.y*self.y)

    def normalize(self):
        "."
        length = self.length()
        self.scale(1.0/length)
    
    def scale(self, s):
        "."
        self.x *= s
        self.y *= s

def embVector_multiply(v1, v2):
    "."
    return 


def embVector_add(v1, v2):
    "."
    return Vector(v1.x+v2.x, v1.y+v2.y)


def embVector_average(v1, v2):
    "."
    return Vector((v1.x+v2.x)/2.0, (v1.y+v2.y)/2.0)


def embVector_subtract(v1, v2):
    "."
    return 


def embVector_dot(v1, v2):
    "."
    return 

def embVector_cross(v1, v2):
    "."
    return 

def embVector_transpose_product(v1, v2):
    "."
    return 

def embVector_relativeX(v1, v2):
    "."
    return 

def embVector_relativeY(v1, v2):
    "."
    return 

def embVector_angle(v1, v2):
    "."
    return 

def embVector_distance(v1, v2):
    "."
    return 

def embVector_unit(angle):
    "."
    return 


class Line():
    def __init__(self):
        return self

    def normalVector(self, args):
        return

    def intersectionPoint(self, args):
        return


class Path():
    def __init__(self):
        return self
