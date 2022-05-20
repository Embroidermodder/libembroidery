#!/usr/bin/env python3

r"""
    Embroidermodder 2.

    ------------------------------------------------------------

    Copyright 2013-2022 The Embroidermodder Team
    Embroidermodder 2 is Open Source Software.
    See LICENSE for licensing terms.

    ------------------------------------------------------------

    The Ellipse class definition file.
"""

import math

from libembroidery.tools import (
    alert, clear_selection, debug_message, translate, todo, error,
    append_prompt_history, set_prompt_prefix, Pen, Vector, vector_from_str,
    add_rubber, closest_vector
)
from libembroidery.line import Line
from libembroidery.rect import Rect


class Ellipse():
    r"""
    The Ellipse class definition.

    Path SavePath() const

    def Center(): return scenePos()
    def RadiusMajor():  return max(rect().width(), rect().height())/2.0*scale()
    def RadiusMinor(): return min(rect().width(), rect().height())/2.0*scale()
    def DiameterMajor(): return max(rect().width(), rect().height())*scale()
    def diameter_minor(): return min(rect().width(), rect().height())*scale()
    def Width(): return rect().width()*scale()
    def Height(): return rect().height()*scale()

    def set_Size(width, height)
    def set_RadiusMajor(radius)
    def set_RadiusMinor(radius)
    def set_DiameterMajor(diameter)
    def set_diameter_minor(diameter)
    """
    def __init__(self, center, width, height, pen=Pen()):
        r"."
        self.type = "Ellipse"
        self.selectable = 1
        self.width = width
        self.height = height
        self.position = center
        self.pen = pen
        self.update_path()
        self.rubber_points = {}

        clear_selection()
        self.mode = "MAJORDIAMETER_MINORRADIUS"
        self.point1 = Vector(math.nan, math.nan)
        self.point2 = Vector(math.nan, math.nan)
        self.point3 = Vector(math.nan, math.nan)
        set_prompt_prefix(
            translate("Specify first axis start point or [Center]: ")
        )

    def click(self, point):
        if self.mode == "MAJORDIAMETER_MINORRADIUS":
            if math.isnan(self.point1.x):
                self.point1 = point
                add_rubber("ELLIPSE")
                self.rubber_mode = "ELLIPSE_LINE"
                self.rubber_points["ELLIPSE_LINE_POINT1"] = point
                append_prompt_history()
                set_prompt_prefix(translate("Specify first axis end point: "))

            elif math.isnan(self.point2.x):
                self.point2 = point
                self.cx = (self.x1 + self.x2)/2.0
                self.cy = (self.y1 + self.y2)/2.0
                self.width = Line(self.point1, self.point2).length()
                self.rot = Line(self.point1, self.point2).angle()
                self.rubber_mode = "MAJORDIAMETER_MINORRADIUS"
                self.rubber_points["ELLIPSE_AXIS1_POINT1"] = self.point1
                self.rubber_points["ELLIPSE_AXIS1_POINT2"] = self.point2
                self.rubber_points["ELLIPSE_CENTER"] = Vector(self.cx, self.cy)
                self.rubber_points["ELLIPSE_WIDTH"] = Vector(self.width, 0)
                self.rubber_points["ELLIPSE_ROT"] = Vector(self.rot, 0)
                append_prompt_history()
                set_prompt_prefix(translate("Specify second axis end point or [Rotation]: "))

            elif math.isnan(self.point3.x):
                self.point3 = point
                self.height = perpendicular_distance(self.point3, self.point1, self.point2)*2.0
                self.rubber_points["ELLIPSE_AXIS2_POINT2"] = point
                self.vulcanize()
                append_prompt_history()

            else:
                error("ELLIPSE", translate("This should never happen."))

        elif self.mode == "MAJORRADIUS_MINORRADIUS":
            if math.isnan(self.point1.x):
                self.point1 = point
                self.center = point
                add_rubber("ELLIPSE")
                self.rubber_mode = "ELLIPSE_LINE"
                self.rubber_points["ELLIPSE_LINE_POINT1"] = point
                self.rubber_points["ELLIPSE_CENTER"] = self.center
                append_prompt_history()
                set_prompt_prefix(translate("Specify first axis end point: "))

            elif math.isnan(self.point2.x):
                self.point2 = point
                self.width = Line(self.center, self.point2).length()*2.0
                self.rot = Line(self.point1, self.point2).angle()
                self.rubber_mode = "MAJORRADIUS_MINORRADIUS"
                self.rubber_points["ELLIPSE_AXIS1_POINT2"] = self.point2
                self.rubber_points["ELLIPSE_WIDTH"] = Vector(self.width, 0)
                self.rubber_points["ELLIPSE_ROT"] = Vector(self.rot, 0)
                append_prompt_history()
                prefix = translate("Specify second axis end point or [Rotation]: ")
                set_prompt_prefix(prefix)

            elif math.isnan(self.point3.x):
                self.point3 = point
                self.height = perpendicular_distance(self.point3, self.center, self.point2)*2.0
                self.rubber_points["ELLIPSE_AXIS2_POINT2"] = point
                self.vulcanize()
                append_prompt_history()

            else:
                error("ELLIPSE", translate("This should never happen."))

        elif self.mode == "ELLIPSE_ROTATION":
            if math.isnan(self.point1.x):
                error("ELLIPSE", translate("This should never happen."))

            elif math.isnan(self.point2.x):
                error("ELLIPSE", translate("This should never happen."))

            elif math.isnan(self.point3.x):
                angle = calculate_angle(self.center, point)
                self.height = math.cos(angle*math.pi/180.0)*self.width
                add_ellipse(self.center, self.width, self.height, self.rot, False)
                append_prompt_history()

    def prompt(self, cmd):
        if self.mode == "MAJORDIAMETER_MINORRADIUS":
            if math.isnan(self.point1.x):
                if cmd == "C" or cmd == "CENTER":
                    # TODO: Probably should add additional qsTr calls here.
                    self.mode = self.mode_MAJORRADIUS_MINORRADIUS
                    set_prompt_prefix(translate("Specify center point: "))
                else:
                    vector = vector_from_str(cmd)
                    if not vector:
                        alert(translate("Point or option keyword required."))
                        prefix = translate("Specify first axis start point or [Center]: ")
                        set_prompt_prefix(prefix)
 
                    else:
                        self.point1 = vector
                        add_rubber("ELLIPSE")
                        self.rubber_mode = "ELLIPSE_LINE"
                        self.rubber_points["ELLIPSE_LINE_POINT1"] = self.point1
                        set_prompt_prefix(translate("Specify first axis end point: "))

            elif math.isnan(self.point2.x):
                vector = vector_from_str(cmd)
                if not vector:
                    alert(translate("Invalid point."))
                    prefix = translate("Specify first axis end point: ")
                    set_prompt_prefix(prefix)

                else:
                    self.point2 = vector
                    self.cx = (self.x1 + self.x2)/2.0
                    self.cy = (self.y1 + self.y2)/2.0
                    self.width = Line(self.point1, self.point2).length()
                    self.rot = Line(self.point1, self.point2).angle()
                    self.rubber_mode = "ELLIPSE_MAJORDIAMETER_MINORRADIUS"
                    self.rubber_points["ELLIPSE_AXIS1_POINT1"] = self.point1
                    self.rubber_points["ELLIPSE_AXIS1_POINT2"] = self.point2
                    self.rubber_points["ELLIPSE_CENTER"] = self.center
                    self.rubber_points["ELLIPSE_WIDTH"] = Vector(self.width, 0)
                    self.rubber_points["ELLIPSE_ROT"] = Vector(self.rot, 0)
                    prefix = translate("Specify second axis end point or [Rotation]: ")
                    set_prompt_prefix(prefix)

            elif math.isnan(self.x3):
                if cmd == "R" or cmd == "ROTATION":
                    # TODO: Probably should add additional qsTr calls here.
                    self.mode = "ROTATION"
                    set_prompt_prefix(translate("Specify rotation: "))
                else:
                    vector = vector_from_str(cmd)
                    if not vector:
                        alert(translate("Point or option keyword required."))
                        set_prompt_prefix(translate("Specify second axis end point or [Rotation]: "))
 
                    else:
                        self.x3 = vector.x
                        self.y3 = vector.y
                        self.height = perpendicular_distance(self.x3, self.y3, self.x1, self.y1, self.x2, self.y2)*2.0
                        self.rubber_points["ELLIPSE_AXIS2_POINT2"] = Vector(self.x3, self.y3)
                        self.vulcanize()

        elif self.mode == "MAJORRADIUS_MINORRADIUS":
            if math.isnan(self.x1):
                vector = vector_from_str(cmd)
                if not vector:
                    alert(translate("Invalid point."))
                    set_prompt_prefix(translate("Specify center point: "))
                else:
                    self.x1 = vector.x
                    self.y1 = vector.y
                    self.cx = self.x1
                    self.cy = self.y1
                    add_rubber("ELLIPSE")
                    self.rubber_mode = "ELLIPSE_LINE"
                    self.rubber_points["ELLIPSE_LINE_POINT1"] = Vector(self.x1, self.y1)
                    self.rubber_points["ELLIPSE_CENTER"] = Vector(self.cx, self.cy)
                    set_prompt_prefix(translate("Specify first axis end point: "))

            elif math.isnan(self.x2):
                vector = vector_from_str(cmd)
                if not vector:
                    alert(translate("Invalid point."))
                    set_prompt_prefix(translate("Specify first axis end point: "))

                else:
                    self.point2 = vector
                    line = Line(self.point1, self.point2)
                    self.width = line.length()*2.0
                    self.rot = line.angle()
                    self.rubber_mode = "ELLIPSE_MAJORRADIUS_MINORRADIUS"
                    self.rubber_points["ELLIPSE_AXIS1_POINT2"] = Vector(self.x2, self.y2)
                    self.rubber_points["ELLIPSE_WIDTH"] = Vector(self.width, 0)
                    self.rubber_points["ELLIPSE_ROT"] = Vector(self.rot, 0)
                    set_prompt_prefix(translate("Specify second axis end point or [Rotation]: "))

            elif math.isnan(self.x3):
                if cmd == "R" or cmd == "ROTATION":
                    # TODO: Probably should add additional qsTr calls here.
                    self.mode = self.mode_ELLIPSE_ROTATION
                    set_prompt_prefix(translate("Specify ellipse rotation: "))
                else:
                    vector = vector_from_str(cmd)
                    if not vector:
                        alert(translate("Point or option keyword required."))
                        set_prompt_prefix(translate("Specify second axis end point or [Rotation]: "))
                    else:
                        self.x3 = vector.x
                        self.y3 = vector.y
                        self.height = perpendicular_distance(self.x3, self.y3, self.x1, self.y1, self.x2, self.y2)*2.0
                        self.rubber_points["ELLIPSE_AXIS2_POINT2"] = Vector(self.x3, self.y3)
                        self.vulcanize()

        elif self.mode == "ELLIPSE_ROTATION":
            if math.isnan(self.x1):
                error("ELLIPSE", translate("This should never happen."))
            elif math.isnan(self.x2):
                error("ELLIPSE", translate("This should never happen."))
            elif math.isnan(self.x3):
                if math.isnan(cmd):
                    alert(translate("Invalid angle. Input a numeric angle or pick a point."))
                    set_prompt_prefix(translate("Specify rotation: "))
                else:
                    angle = float(cmd)
                    self.height = math.cos(angle*math.pi/180.0)*self.width
                    add_ellipse(self.cx, self.cy, self.width, self.height, self.rot, False)

    def copy(self):
        " TODO: getCurrentLineType "
        debug_message("Ellipse Constructor()")
        return Ellipse(self.center, self.width, self.height,
                       pen=self.pen, rotation=self.rotation)

    def set_Size(self, width, height):
        r"."
        elRect = Rect()
        elRect.setWidth(width)
        elRect.setHeight(height)
        elRect.move_center(Vector(0, 0))
        setRect(elRect)

    def set_RadiusMajor(self, radius):
        r"."
        self.set_DiameterMajor(radius*2.0)

    def set_RadiusMinor(self, radius):
        r"."
        self.set_diameter_minor(radius*2.0)

    def set_DiameterMajor(self, diameter):
        r"."
        elRect = Rect()
        if elRect.width() > elRect.height():
            elRect.setWidth(diameter)
        else:
            elRect.setHeight(diameter)

        elRect.move_center(Vector(0, 0))
        setRect(elRect)

    def set_diameter_minor(self, diameter):
        r"."
        elRect = Rect()
        if elRect.width < elRect.height:
            elRect.setWidth(diameter)
        else:
            elRect.setHeight(diameter)
        elRect.move_center(Vector(0, 0))
        setRect(elRect)

    def quadrant(self, angle):
        r"."
        v = Vector(self.width()/2.0, 0.0)
        v.rotate(math.radians(self.rotation+angle))
        return self.center + v

    def update_path(self):
        r"."
        path = []
        r = Rect()
        path += ["arc_move_to", Vector(r, 0)]
        path += ["arc_to", Vector(r, 0), 360]
        # NOTE: Reverse the path so that the inside
        # area isn't considered part of the ellipse.
        path += ["arc_to", Vector(r, 0), -360]
        self.data = path

    def paint(self, painter, option, widget):
        r"."
        obj_scene = scene()
        if not obj_scene:
            return

        paint_pen = Pen()
        painter.set_pen(paint_pen)
        self.update_rubber(painter)
        if option.state == "State Selected":
            paint_pen.set_style("dashed")
        if obj_scene.property("ENABLE_LWT").to_bool():
            paint_pen = self.lwt_pen
        painter.set_pen(paint_pen)

        painter.draw_ellipse(Rect())

    def update_rubber(self, painter):
        r"."
        if self.rubber_mode == "LINE":
            scene_line_point_1 = self.rubber_points["ELLIPSE_LINE_POINT1"]
            scene_line_point_2 = self.rubber_points["ELLIPSE_LINE_POINT2"]
            itemLinePoint1 = map_from_scene(scene_line_point_1)
            itemLinePoint2 = map_from_scene(scene_line_point_2)
            itemLine = Line(itemLinePoint1, itemLinePoint2)
            if painter:
                drawRubberLine(itemLine, painter, "VIEW_COLOR_CROSSHAIR")
            self.update_path()

        elif self.rubber_mode == "MAJORDIAMETER_MINORRADIUS":
            sceneAxis1Point1 = self.rubberPoint("ELLIPSE_AXIS1_POINT1")
            sceneAxis1Point2 = self.rubberPoint("ELLIPSE_AXIS1_POINT2")
            sceneCenterPoint = self.rubberPoint("ELLIPSE_CENTER")
            sceneAxis2Point2 = self.rubberPoint("ELLIPSE_AXIS2_POINT2")
            ellipseWidth = self.rubberPoint("ELLIPSE_WIDTH").x()
            ellipseRot = self.rubberPoint("ELLIPSE_ROT").x()

            # TODO: incorporate perpendicular_distance() into libembroidery.
            px = sceneAxis2Point2.x()
            py = sceneAxis2Point2.y()
            x1 = sceneAxis1Point1.x()
            y1 = sceneAxis1Point1.y()
            line = Line(sceneAxis1Point1, sceneAxis1Point2)
            norm = line.normalVector()
            dx = px-x1
            dy = py-y1
            norm.translate(dx, dy)
            # HACK: this isn't in all versions of Qt 5 in the same place?
            # norm.intersects(line, &iPoint)
            iPoint = line.p1()
            ellipseHeight = Line(px, py, iPoint.x(), iPoint.y()).length()*2.0

            setPos(sceneCenterPoint)
            set_Size(ellipseWidth, ellipseHeight)
            self.rotation = -ellipseRot

            itemCenterPoint = map_from_scene(sceneCenterPoint)
            itemAxis2Point2 = map_from_scene(sceneAxis2Point2)
            itemLine = Line(itemCenterPoint, itemAxis2Point2)
            if painter:
                drawRubberLine(itemLine, painter, "VIEW_COLOR_CROSSHAIR")
            self.update_path()

        elif self.rubber_mode == "MAJORRADIUS_MINORRADIUS":
            sceneAxis1Point2 = self.rubberPoint("ELLIPSE_AXIS1_POINT2")
            sceneCenterPoint = self.rubberPoint("ELLIPSE_CENTER")
            sceneAxis2Point2 = self.rubberPoint("ELLIPSE_AXIS2_POINT2")
            ellipseWidth = self.rubberPoint("ELLIPSE_WIDTH").x()
            ellipseRot = self.rubberPoint("ELLIPSE_ROT").x()

            # TODO: incorporate perpendicular_distance() into libembroidery.
            px = sceneAxis2Point2.x()
            py = sceneAxis2Point2.y()
            x1 = sceneCenterPoint.x()
            y1 = sceneCenterPoint.y()
            line = Line(sceneCenterPoint, sceneAxis1Point2)
            norm = line.normalVector()
            dx = px-x1
            dy = py-y1
            norm.translate(dx, dy)
            # HACK
            # norm.intersects(line, &iPoint);
            iPoint = line.p1()
            ellipseHeight = Line(px, py, iPoint.x(), iPoint.y()).length()*2.0

            setPos(sceneCenterPoint)
            set_Size(ellipseWidth, ellipseHeight)
            self.rotation = -ellipseRot

            itemCenterPoint = map_from_scene(sceneCenterPoint)
            itemAxis2Point2 = map_from_scene(sceneAxis2Point2)
            itemLine = Line(itemCenterPoint, itemAxis2Point2)
            if painter:
                drawRubberLine(itemLine, painter, "VIEW_COLOR_CROSSHAIR")
            self.update_path()

        elif self.rubber_mode == "GRIP":
            todo("TODO: self.update_rubber() gripping for Ellipse.")

    def vulcanize(self):
        " . "
        debug_message("Ellipse vulcanize()")
        self.update_rubber()
        self.rubber_mode = "RUBBER_OFF"

    def mouse_snap_point(self, mouse_point):
        " Returns the closest snap point to the mouse point. "
        all_points = self.all_grip_points()
        return closest_vector(all_points, mouse_point)

    def all_grip_points(self):
        " . "
        return [
            self.center(),
            self.quadrant(0),
            self.quadrant(90),
            self.quadrant(180),
            self.quadrant(270)
        ]

    def grip_edit(self, before, after):
        " TODO: grip_edit() for Ellipse. "

    def save_path(self):
        r = Rect()
        path.arc_move_to(r, 0)
        path.arc_to(r, 0, 360)

        s = self.scale
        trans = 0
        trans.rotate(self.rotation)
        trans.scale(s, s)
        return trans.map(path)
