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

from idna import valid_contexto

from embroidermodder.geometry.pen import Pen
from embroidermodder.geometry.vector import Vector
from embroidermodder.geometry.line import Line

from embroidermodder.utility import (
    clear_selection, translate, todo, error,
    append_prompt_history, set_prompt_prefix
)


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
    def __init__(self, center, width, height,
                 pen=Pen(rgb="#FFFFFF", line_type="solid", line_weight=0.35)):
        self.type = "Ellipse"
        self.selectable = 1
        self.width = width
        self.height = height
        self.position = center
        self.pen = pen
        self.update_path()
        self.rubberPoints = {}

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
            if math.isnan(self.x1):
                self.point1 = point
                add_rubber("ELLIPSE")
                self.rubber_mode = "ELLIPSE_LINE"
                self.rubberPoints["ELLIPSE_LINE_POINT1"] = point
                append_prompt_history()
                set_prompt_prefix(translate("Specify first axis end point: "))

            elif math.isnan(self.x2):
                self.point2 = point
                self.cx = (self.x1 + self.x2)/2.0
                self.cy = (self.y1 + self.y2)/2.0
                self.width = calculateDistance(self.x1, self.y1, self.x2, self.y2)
                self.rot = calculate_angle(self.x1, self.y1, self.x2, self.y2)
                self.rubber_mode = "MAJORDIAMETER_MINORRADIUS"
                self.rubberPoints["ELLIPSE_AXIS1_POINT1"] = Vector(self.x1, self.y1)
                self.rubberPoints["ELLIPSE_AXIS1_POINT2"] = Vector(self.x2, self.y2)
                self.rubberPoints["ELLIPSE_CENTER"] = Vector(self.cx, self.cy)
                self.rubberPoints["ELLIPSE_WIDTH"] = Vector(self.width, 0)
                self.rubberPoints["ELLIPSE_ROT"] = Vector(self.rot, 0)
                append_prompt_history()
                set_prompt_prefix(translate("Specify second axis end point or [Rotation]: "))

            elif math.isnan(self.x3):
                self.x3 = x
                self.y3 = y
                self.height = perpendicularDistance(self.x3, self.y3, self.x1, self.y1, self.x2, self.y2)*2.0
                self.rubberPoints["ELLIPSE_AXIS2_POINT2"] = Vector(self.x3, self.y3)
                self.vulcanize()
                append_prompt_history()
                return

            else:
                error("ELLIPSE", translate("This should never happen."))

        elif self.mode == "MAJORRADIUS_MINORRADIUS":
            if math.isnan(self.x1):
                self.x1 = x
                self.y1 = y
                self.cx = self.x1
                self.cy = self.y1
                addRubber("ELLIPSE")
                set_rubber_mode("ELLIPSE_LINE")
                self.rubberPoints["ELLIPSE_LINE_POINT1"] = Vector(self.x1, self.y1)
                self.rubberPoints["ELLIPSE_CENTER"] = Vector(self.cx, self.cy)
                append_prompt_history()
                set_prompt_prefix(translate("Specify first axis end point: "))

            elif math.isnan(self.x2):
                self.x2 = x
                self.y2 = y
                self.width = calculateDistance(self.cx, self.cy, self.x2, self.y2)*2.0
                self.rot = calculate_angle(self.x1, self.y1, self.x2, self.y2)
                self.rubber_mode = "MAJORRADIUS_MINORRADIUS"
                self.rubberPoints["ELLIPSE_AXIS1_POINT2"] = Vector(self.x2, self.y2)
                self.rubberPoints["ELLIPSE_WIDTH"] = Vector(self.width, 0)
                self.rubberPoints["ELLIPSE_ROT"] = Vector(self.rot, 0)
                append_prompt_history()
                set_prompt_prefix(translate("Specify second axis end point or [Rotation]: "))

            elif math.isnan(self.x3):
                self.x3 = x
                self.y3 = y
                self.height = perpendicularDistance(self.x3, self.y3, self.cx, self.cy, self.x2, self.y2)*2.0
                self.rubberPoints["ELLIPSE_AXIS2_POINT2"] = Vector(self.x3, self.y3)
                self.vulcanize()
                append_prompt_history()
                return

            else:
                error("ELLIPSE", translate("This should never happen."))

        elif self.mode == "ELLIPSE_ROTATION":
            if math.isnan(self.x1):
                error("ELLIPSE", translate("This should never happen."))

            elif math.isnan(self.x2):
                error("ELLIPSE", translate("This should never happen."))

            elif math.isnan(self.x3):
                angle = calculate_angle(self.cx, self.cy, x, y)
                self.height = cos(angle*math.pi/180.0)*self.width
                addEllipse(self.cx, self.cy, self.width, self.height, self.rot, false)
                append_prompt_history()
                return

    def prompt(self, cmd):
        if self.mode == "MAJORDIAMETER_MINORRADIUS":
            if math.isnan(self.x1):
                if str == "C" or cmd == "CENTER":
                    #TODO: Probably should add additional qsTr calls here.
                    self.mode = self.mode_MAJORRADIUS_MINORRADIUS
                    set_prompt_prefix(translate("Specify center point: "))
                else:
                    strList = str.split(",")
                    if math.isnan(strList[0]) or math.isnan(strList[1]):
                        alert(translate("Point or option keyword required."))
                        set_prompt_prefix(translate("Specify first axis start point or [Center]: "))
 
                    else:
                        self.x1 = float(strList[0])
                        self.y1 = float(strList[1])
                        addRubber("ELLIPSE")
                        set_rubber_mode("ELLIPSE_LINE")
                        self.rubberPoints["ELLIPSE_LINE_POINT1"] = Vector(self.x1, self.y1)
                        set_prompt_prefix(translate("Specify first axis end point: "))

            elif math.isnan(self.x2):
                strList = str.split(",")
                if math.isnan(strList[0]) or math.isnan(strList[1]):
                    alert(translate("Invalid point."))
                    set_prompt_prefix(translate("Specify first axis end point: "))

                else:
                    self.x2 = float(strList[0])
                    self.y2 = float(strList[1])
                    self.cx = (self.x1 + self.x2)/2.0
                    self.cy = (self.y1 + self.y2)/2.0
                    self.width = calculateDistance(self.x1, self.y1, self.x2, self.y2)
                    self.rot = calculate_angle(self.x1, self.y1, self.x2, self.y2)
                    set_rubber_mode("ELLIPSE_MAJORDIAMETER_MINORRADIUS")
                    self.rubberPoints["ELLIPSE_AXIS1_POINT1"] = Vector(self.x1, self.y1)
                    self.rubberPoints["ELLIPSE_AXIS1_POINT2"] = Vector(self.x2, self.y2)
                    self.rubberPoints["ELLIPSE_CENTER"] = Vector(self.cx, self.cy)
                    self.rubberPoints["ELLIPSE_WIDTH"] = Vector(self.width, 0)
                    self.rubberPoints["ELLIPSE_ROT"] = Vector(self.rot, 0)
                    set_prompt_prefix(translate("Specify second axis end point or [Rotation]: "))

            elif math.isnan(self.x3):
                if str == "R" or cmd == "ROTATION":
                    #TODO: Probably should add additional qsTr calls here.
                    self.mode = self.mode_ELLIPSE_ROTATION
                    set_prompt_prefix(translate("Specify rotation: "))
                else:
                    strList = str.split(",")
                    if math.isnan(strList[0]) or math.isnan(strList[1]):
                        alert(translate("Point or option keyword required."))
                        set_prompt_prefix(translate("Specify second axis end point or [Rotation]: "))
 
                    else:
                        self.x3 = float(strList[0])
                        self.y3 = float(strList[1])
                        self.height = perpendicularDistance(self.x3, self.y3, self.x1, self.y1, self.x2, self.y2)*2.0
                        self.rubberPoints["ELLIPSE_AXIS2_POINT2"] = Vector(self.x3, self.y3)
                        vulcanize()
                        return

        elif self.mode == "MAJORRADIUS_MINORRADIUS":
            if math.isnan(self.x1):
                strList = str.split(",")
                if math.isnan(strList[0]) or math.isnan(strList[1]):
                    alert(translate("Invalid point."))
                    set_prompt_prefix(translate("Specify center point: "))
                else:
                    self.x1 = float(strList[0])
                    self.y1 = float(strList[1])
                    self.cx = self.x1
                    self.cy = self.y1
                    addRubber("ELLIPSE")
                    self.rubber_mode = "ELLIPSE_LINE"
                    self.rubberPoints["ELLIPSE_LINE_POINT1"] = Vector(self.x1, self.y1)
                    self.rubberPoints["ELLIPSE_CENTER"] = Vector(self.cx, self.cy)
                    set_prompt_prefix(translate("Specify first axis end point: "))

            elif math.isnan(self.x2):
                strList = str.split(",")
                if math.isnan(strList[0]) or math.isnan(strList[1]):
                    alert(translate("Invalid point."))
                    set_prompt_prefix(translate("Specify first axis end point: "))

                else:
                    self.x2 = float(strList[0])
                    self.y2 = float(strList[1])
                    self.width = calculateDistance(self.x1, self.y1, self.x2, self.y2)*2.0
                    self.rot = calculate_angle(self.x1, self.y1, self.x2, self.y2)
                    set_rubber_mode("ELLIPSE_MAJORRADIUS_MINORRADIUS")
                    self.rubberPoints["ELLIPSE_AXIS1_POINT2"] = Vector(self.x2, self.y2)
                    self.rubberPoints["ELLIPSE_WIDTH"] = Vector(self.width, 0)
                    self.rubberPoints["ELLIPSE_ROT"] = Vector(self.rot, 0)
                    set_prompt_prefix(translate("Specify second axis end point or [Rotation]: "))

            elif math.isnan(self.x3):
                if str == "R" or cmd == "ROTATION":
                    # TODO: Probably should add additional qsTr calls here.
                    self.mode = self.mode_ELLIPSE_ROTATION
                    set_prompt_prefix(translate("Specify ellipse rotation: "))
                else:
                    strList = str.split(",")
                    if math.isnan(strList[0]) or math.isnan(strList[1]):
                        alert(translate("Point or option keyword required."))
                        set_prompt_prefix(translate("Specify second axis end point or [Rotation]: "))
                    else:
                        self.x3 = float(strList[0])
                        self.y3 = float(strList[1])
                        self.height = perpendicularDistance(self.x3, self.y3, self.x1, self.y1, self.x2, self.y2)*2.0
                        self.rubberPoints["ELLIPSE_AXIS2_POINT2"] = Vector(self.x3, self.y3)
                        vulcanize()
                        return

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
                    addEllipse(self.cx, self.cy, self.width, self.height, self.rot, False)

    def copy(self, obj, parent):
        " TODO: getCurrentLineType "
        debug_message("Ellipse Constructor()")
        ellipse = Ellipse(self.objectCenter().x(), self.objectCenter().y(), self.objectWidth(), self.objectHeight(), self.objectColorRGB(), Qt_SolidLine)
        setRotation(self.rotation())
        return ellipse

    def set_Size(self, width, height):
        elRect = Rect()
        elRect.setWidth(width)
        elRect.setHeight(height)
        elRect.move_center(Vector(0,0))
        setRect(elRect)

    def set_RadiusMajor(radius):
        set_DiameterMajor(radius*2.0)

    def set_RadiusMinor(radius):
        set_diameter_minor(radius*2.0)

    def set_DiameterMajor(diameter):
        elRect = Rect()
        if elRect.width() > elRect.height():
            elRect.setWidth(diameter)
        else:
            elRect.setHeight(diameter)

        elRect.move_center(Vector(0, 0))
        setRect(elRect)

    def set_diameter_minor(diameter):
        elRect = Rect()
        if elRect.width() < elRect.height():
            elRect.setWidth(diameter)
        else:
            elRect.setHeight(diameter)
        elRect.move_center(Vector(0, 0))
        setRect(elRect)

    def Quadrant0(self):
        v.x = self.width()/2.0
        v.y = 0.0
        v = rotate_vector(v, radians(self.rotation))
        return self.center + v

    def Quadrant90(self):
        v.x = Height()/2.0
        v.y = 0.0
        v = rotate_vector(v, radians(self.rotation+90.0))
        return self.center + v

    def Quadrant180():
        v.x = Width()/2.0
        v.y = 0.0
        v = rotate_vector(v, radians(self.rotation+180.0))
        return self.center + v

    def Quadrant270():
        v.x = Height()/2.0
        v.y = 0.0
        v = rotate_vector(v, radians(self.rotation+270.0))
        return self.center + v

    def update_path(self):
        path = []
        r = Rect()
        path += ["arc_move_to", Vector(r, 0)]
        path += ["arc_to", Vector(r, 0), 360]
        # NOTE: Reverse the path so that the inside
        # area isn't considered part of the ellipse.
        path += ["arc_to", Vector(r, 0), -360]
        self.data = path

    def paint(self, painter, option, widget):
        obj_scene = scene()
        if not obj_scene:
            return

        paint_pen = pen()
        painter.set_pen(paint_pen)
        update_rubber(painter)
        if option.state == "State Selected":
            paint_pen.set_style("dashed")
        if obj_scene.property("ENABLE_LWT").toBool():
            paint_pen = lineWeightPen()
        painter.set_pen(paint_pen)

        painter.drawEllipse(Rect())

    def update_rubber(self, painter):
        if self.rubber_mode == "LINE":
            sceneLinePoint1 = self.rubberPoint("ELLIPSE_LINE_POINT1")
            sceneLinePoint2 = self.rubberPoint("ELLIPSE_LINE_POINT2")
            itemLinePoint1 = map_from_scene(sceneLinePoint1)
            itemLinePoint2 = map_from_scene(sceneLinePoint2)
            itemLine = Line(itemLinePoint1, itemLinePoint2)
            if painter:
                drawRubberLine(itemLine, painter, "VIEW_COLOR_CROSSHAIR")
            update_path()

        elif self.rubber_mode == "MAJORDIAMETER_MINORRADIUS":
            sceneAxis1Point1 = self.rubberPoint("ELLIPSE_AXIS1_POINT1")
            sceneAxis1Point2 = self.rubberPoint("ELLIPSE_AXIS1_POINT2")
            sceneCenterPoint = self.rubberPoint("ELLIPSE_CENTER")
            sceneAxis2Point2 = self.rubberPoint("ELLIPSE_AXIS2_POINT2")
            ellipseWidth = self.rubberPoint("ELLIPSE_WIDTH").x()
            ellipseRot = self.rubberPoint("ELLIPSE_ROT").x()

            # TODO: incorporate perpendicularDistance() into libembroidery.
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
            setRotation(-ellipseRot)

            itemCenterPoint = map_from_scene(sceneCenterPoint)
            itemAxis2Point2 = map_from_scene(sceneAxis2Point2)
            itemLine = Line(itemCenterPoint, itemAxis2Point2)
            if painter:
                drawRubberLine(itemLine, painter, "VIEW_COLOR_CROSSHAIR")
            update_path()

        elif self.rubber_mode == "MAJORRADIUS_MINORRADIUS":
            sceneAxis1Point2 = self.rubberPoint("ELLIPSE_AXIS1_POINT2")
            sceneCenterPoint = self.rubberPoint("ELLIPSE_CENTER")
            sceneAxis2Point2 = self.rubberPoint("ELLIPSE_AXIS2_POINT2")
            ellipseWidth = self.rubberPoint("ELLIPSE_WIDTH").x()
            ellipseRot = self.rubberPoint("ELLIPSE_ROT").x()

            # TODO: incorporate perpendicularDistance() into libembroidery.
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
            setRotation(-ellipseRot)

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
            self.quadrant0(),
            self.quadrant90(),
            self.quadrant180(),
            self.quadrant270()
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
        trans.scale(s,s)
        return trans.map(path)
