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
from embroidermodder.geometry.path import Path
from embroidermodder.geometry.vector import Vector, vector_from_str
from embroidermodder.geometry.line import Line

from embroidermodder.utility import (
    translate, clear_selection, todo, debug_message, set_prompt_prefix,
    alert
)


def vector_distance(vector_a, vector_b):
    "Find the distance between two points given as vectors."
    delta = vector_a - vector_b
    return delta.length()


class Rect():
    r" The Rect class definition. "
    def __init__(self, x, y, w, h,
                 pen=Pen(rgb="#FFFFFF", line_type="solid", line_weight=0.35)):
        r" Create a new rectangle. "
        self.type = "Rect"
        self.selectable = True
        self.scale = 1.0
        self.rotation = 0.0
        self.position = Vector(x, y)
        self.dimensions = Vector(w, h)
        self.pen = pen

        clear_selection()
        self.new_rect = True
        self.rubber_mode = "NOT SET"
        set_prompt_prefix(translate("Specify first corner point or [Chamfer/Fillet]: "))

    def width(self):
        r"Syntactic sugar for x dimension of the Rect."
        return self.dimensions.x

    def height(self):
        r"Syntactic sugar for y dimension of the Rect."
        return self.dimensions.y

    def area(self):
        r"Returns the area of the rectangle."
        return self.dimensions.x * self.dimensions.y

    def click(self, x, y):
        r"The mouse input handler for editing a Rect."
        if self.new_rect:
            self.new_rect = False
            self.x1 = x
            self.y1 = y
            addRubber("RECTANGLE")
            self.rubber_mode = "RECTANGLE"
            self.rubberPoint["RECTANGLE_START"] = Vector(x, y)
            set_prompt_prefix(translate("Specify other corner point or [Dimensions]: "))
        else:
            self.new_rect = True
            self.x2 = x
            self.y2 = y
            self.rubberPoint["RECTANGLE_END"] = Vector(x, y)
            self.vulcanize()

    def prompt(self, cmd):
        "The prompt handler for editing rectangles."
        if cmd == "C" or cmd == "CHAMFER":
            # TODO: Probably should add additional qsTr calls here.
            todo("RECTANGLE", "prompt() for CHAMFER")
        elif cmd == "D" or cmd == "DIMENSIONS":
            # TODO: Probably should add additional qsTr calls here.
            todo("RECTANGLE", "prompt() for DIMENSIONS")
        elif cmd == "F" or cmd == "FILLET":
            # TODO: Probably should add additional qsTr calls here.
            todo("RECTANGLE", "prompt() for FILLET")
        else:
            vector = vector_from_str(cmd)
            if math.isnan(strList[0]) or math.isnan(strList[1]):
                alert(translate("Invalid point."))
                set_prompt_prefix(translate("Specify first point: "))
            else:
                if self.new_rect:
                    self.new_rect = False
                    self.position = vector
                    addRubber("RECTANGLE")
                    set_rubber_mode("RECTANGLE")
                    set_rubber_point("RECTANGLE_START", vector)
                    set_prompt_prefix(translate("Specify other corner point or [Dimensions]: "))
                else:
                    self.new_rect = True
                    self.dimensions = vector - self.position
                    set_rubber_point("RECTANGLE_END", vector)
                    self.vulcanize()

    def copy(self):
        r" Make a copy of the rectangle. "
        debug_message("Rect copy()")
        # setRotation(self.rotation())
        return Rect(self.x, self.y, self.w, self.h, self.rgb, self.line_type)

    def set_rect(self, x, y, w, h):
        r" Alter all the positional data of the rectangle. "
        self.position = Vector(x, y)
        self.dimensions = Vector(w, h)
        self.update_path()

    def top_left(self):
        r" Returns the top left co-ordinate of this rect as a Vector. "
        return self.position

    def top_right(self):
        r" Returns the top right co-ordinate of this rect as a Vector. "
        vector = self.position
        vector.x += self.dimensions.x
        return vector

    def bottom_left(self):
        r" Returns the bottom left co-ordinate of this rect as a Vector. "
        vector = self.position
        vector.y += self.dimensions.y
        return vector

    def bottom_right(self):
        " Returns the bottom right co-ordinate of this rect as a Vector. "
        return self.position + self.dimensions

    def update_path(self):
        r" Update the associated path. "
        self.path = Path()
        r = Rect()
        self.path.move_to(r.bottom_left())
        self.path.line_to(r.bottom_right())
        self.path.line_to(r.top_right())
        self.path.line_to(r.top_left())
        self.path.line_to(r.bottom_left())
        # NOTE: Reverse the path so that the inside area isn't considered part
        # of the rectangle
        self.path.line_to(r.top_left())
        self.path.line_to(r.top_right())
        self.path.line_to(r.bottom_right())
        self.path.move_to(r.bottom_left())

    def paint(self, painter, option, widget):
        r" . "
        obj_scene = scene()
        if not obj_scene:
            return

        paint_pen = pen()
        painter.set_pen(paint_pen)
        self.update_rubber(painter)
        if option.state & "State_Selected)":
            paint_pen.set_style("dashed")
        if obj_scene.property("ENABLE_LWT"):
            paint_pen = lineWeightPen()
        painter.set_pen(paint_pen)

        painter.drawRect(Rect())

    def update_rubber(self, painter):
        r" . "
        if self.rubber_mode == "RECTANGLE":
            scene_start_point = self.rubberPoint["RECTANGLE_START"]
            scene_end_point = self.rubberPoint["RECTANGLE_END"]
            x = scene_start_point.x()
            y = scene_start_point.y()
            w = scene_end_point.x() - scene_start_point.x()
            h = scene_end_point.y() - scene_start_point.y()
            self.set_rect(x, y, w, h)
            self.update_path()

        elif self.rubber_mode == "GRIP":
            if painter:
                # TODO: Make this work with rotation & scaling.
                gripPoint = self.rubberPoint["GRIP_POINT"]
                after = RubberPoint("")
                delta = after-gripPoint
                if gripPoint == self.top_left():
                    painter.drawPolygon(map_from_scene(Rect(after.x(), after.y(), self.width()-delta.x(), self.height()-delta.y())))
                elif gripPoint == self.top_right():
                    painter.drawPolygon(map_from_scene(Rect(self.top_left().x(), self.top_left().y()+delta.y(), self.width()+delta.x(), self.height()-delta.y())))
                elif gripPoint == self.bottom_left():
                    painter.drawPolygon(map_from_scene(Rect(self.top_left().x()+delta.x(), self.top_left().y(), self.width()-delta.x(), self.height()+delta.y())))
                elif gripPoint == self.bottom_right():
                    painter.drawPolygon(map_from_scene(Rect(self.top_left().x(), self.top_left().y(), self.width()+delta.x(), self.height()+delta.y())))

                rubLine = Line (map_from_scene(gripPoint), map_from_scene(RubberPoint("")))
                drawRubberLine(rubLine, painter, "VIEW_COLOR_CROSSHAIR")

                gripPoint = RubberPoint("GRIP_POINT")
                after = RubberPoint("")
                delta = after-gripPoint

                rubLine = Line(map_from_scene(gripPoint), map_from_scene(RubberPoint("")))
                drawRubberLine(rubLine, painter, "VIEW_COLOR_CROSSHAIR")

    def vulcanize(self):
        r" . "
        debug_message("Rect vulcanize()")
        self.update_rubber()

        self.rubber_mode = "OBJ_RUBBER_OFF"

    def mouse_snap_point(self, mouse_point):
        r" Returns the closest snap point to the mouse point. "
        all_points = self.all_grip_points()
        return closest_vector(all_points, mouse_point)

    def all_grip_points():
        r" . "
        return [self.top_left(), self.top_right(),
            self.bottom_left(), self.bottom_right()]

    def grip_edit(self, before, after, tolerance=0.01):
        """
        The tolerance is how close the input needs to be to be considered
        a match to the given point.
        """
        delta = after-before
        if vector_distance(before, self.top_left()) < tolerance:
            self.set_rect(after.x, after.y, self.width()-delta.x, self.height()-delta.y)
        elif vector_distance(before, self.top_right()) < tolerance:
            self.set_rect(self.top_left().x(), self.top_left().y()+delta.y(), self.width()+delta.x(), self.height()-delta.y())
        elif vector_distance(before, self.bottom_left()) < tolerance:
            self.set_rect(
                self.top_left().x()+delta.x(),
                self.top_left().y(),
                self.width()-delta.x(),
                self.height()+delta.y()
            )
        elif vector_distance(before, self.bottom_right()) < tolerance:
            self.set_rect(self.top_left().x(), self.top_left().y(),
                self.width()+delta.x(), self.height()+delta.y())

    def save_path():
        ". "
        path = Path()
        r = Rect()
        path.move_to(r.bottom_left())
        path.line_to(r.bottom_right())
        path.line_to(r.top_right())
        path.line_to(r.top_left())
        path.line_to(r.bottom_left())

        s = self.scale
        trans = Transform()
        trans.rotate(self.rotation)
        trans.scale(s,s)
        return trans.map(path)
