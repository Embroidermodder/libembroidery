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
import time

import libembroidery.tools as tools
from libembroidery.tools import (Vector, add_rubber, append_prompt_history, debug_message, set_prompt_prefix,
                                 vector_from_str)
from libembroidery.rect import Rect
from libembroidery.line import Line


class Circle():
    """
    The circle class definition.
    def Save[]:

    def setRadius(radius)
    def set_diameter(diameter)
    def set_area(area)
    def setCircumference(circumference)
    def update_rubber(QPainter* painter = 0)

    def Color(): return self.pen.color()
    def line_weight(): return self.lwt_pen.widthF()
    def []: return []
    def rubber_mode(): return objrubber_mode
    def self.rubber_point(key):
    def rubber_text(key):

    def setrubber_mode(mode)  objrubber_mode = mode
    def setself.rubber_point(key, point)  objself.rubber_points.insert(key, point)
    def setrubber_text(key, txt)  self.rubber_texts.insert(key, txt)
    def bounding_rect() const
    def shape() const  return []
    def draw_rubber_line(rubLine, painter=0, colorFromScene=0)
    def vulcanize() = 0
    mouse_snap_point(mouse_point) = 0
    QList<Vector> all_grip_points() = 0
    def grip_edit(before, after) = 0
    Line obj_line
    """
    def __init__(self, center, radius, pen=tools.Pen()):
        " . "
        tools.clear_selection()
        self.mode = "1P_RAD"
        self.point1 = Vector(math.nan, math.nan)
        self.point2 = Vector(math.nan, math.nan)
        self.point3 = Vector(math.nan, math.nan)
        self.type = "Circle"
        self.selectable = True
        self.radius = radius
        self.center = center
        self.update_path()
        self.promptPrefix = "Specify center point for circle or [3P/2P/Ttr (tan tan radius)]: "
        self.pen = pen
        self.lwt_pen = pen
        self.obj_id = "OBJ"+str(time.time())
        self.rubber_mode = "NOT SET"
        self.rubber_points = {}
        self.rubber_texts = {}
        self.update()

    def copy(self):
        " . "
        c = Circle(self.center, self.radius, pen=self.pen)
        return c

    def rect(self):
        " . "
        self.update_path()
        return self.path.bounding_rect()

    def update_path(self):
        ". "
        self.path = []

    def set_rect(self, x, y, w, h):
        """
        def set_rect(self, r):
            p = []
            p.add_rect(r)
            self.set_path(p)
        """
        p = []
        p.add_rect(x, y, w, h)
        self.set_path(p)

    def set_line(self, li):
        r"""
        p = []
        p.move_to(self.point1)
        p.line_to(self.point2)
        self.set_path(p)
        self.obj_line.set_line(self.point1, self.point2)
        """
        p = []
        p.move_to(li.p1())
        p.line_to(li.p2())
        self.set_path(p)
        self.obj_line = li

    def set_path(self, p):
        " . "
        self.path = p
        self.update()

    def set_color(self, color):
        " . "
        " . "
        self.pen.set_color(color)
        self.lwt_pen.set_color(color)

    def set_color_rgb(self, rgb):
        " . "
        self.pen.set_color(tools.Color(rgb))
        self.lwt_pen.set_color(tools.Color(rgb))

    def set_line_type(self, lineType):
        " . "
        self.pen.set_style(lineType)
        self.lwt_pen.set_style(lineType)

    def set_line_weight(self, line_weight):
        r"NOTE: The self.pen will always be cosmetic. "
        self.pen.setWidthF(0)

        if line_weight < 0:
            if line_weight == "OBJ_LWT_BYLAYER":
                self.lwt_pen.setWidthF(0.35)
                # TODO: getLayerline_weight

            elif line_weight == "OBJ_LWT_BYBLOCK":
                self.lwt_pen.setWidthF(0.35)
                # TODO: getBlockline_weight

            else:
                tools.warning(0, "Error - Negative line_weight",
                              "line_weight: %1" % line_weight)
                tools.debug_message(
                    "line_weight cannot be negative! Inverting sign."
                )
                self.lwt_pen.setWidthF(-line_weight)

        else:
            self.lwt_pen.setWidthF(line_weight)

    def rubber_point(self, key):
        " . "
        if key in self.rubber_points:
            return self.rubber_points[key]

        gscene = self.scene()
        if gscene:
            return self.scene().property("SCENE_QSNAP_POINT")
        return Vector()

    def rubber_text(self, key):
        r" . "
        if key in self.rubber_texts:
            return self.rubber_texts[key]
        return ""

    def bounding_rect(self):
        r" If gripped, force this  to be drawn even if it is offscreen. "
        if self.rubber_mode == "OBJ_RUBBER_GRIP":
            return self.scene().scene_rect()
        return Rect()

    def draw_rubber_line(self, rubLine, painter, colorFromScene):
        " . "
        if painter:
            obj_scene = self.scene()
            if obj_scene:
                color_pen = self.pen
                color_pen.set_color(
                    tools.Color(obj_scene.property(colorFromScene).toUInt())
                )
                painter.set_pen(color_pen)
                painter.draw_line(rubLine)
                painter.set_pen(self.pen)

    def real_render(self, painter, render_path):
        "lighter color"
        color1 = Color()
        color2 = color1.darker(150)
        # darker color

        # If we have a dark color, lighten it.
        darkness = color1.lightness()
        threshold = 32
        "TODO: This number may need adjusted or maybe just add it to settings."
        if darkness < threshold:
            color2 = color1
            if not darkness:
                color1 = Color(threshold, threshold, threshold)
                # lighter() does not affect pure black
            else:
                color1 = color2.lighter(100 + threshold)

        count = render_path.element_count()
        for i in range(count-1):

            elem = render_path.element_at(i)
            next = render_path.element_at(i+1)

            if next.ismove_to():
                continue

            elem_path = []
            elem_path.move_to(elem.x, elem.y)
            elem_path.line_to(next.x, next.y)

            render_pen = self.pen
            render_pen.setWidthF(0)
            painter.set_pen(render_pen)
            stroker = Painter()
            stroker.setWidth(0.35)
            stroker.setCapStyle("round-cap")
            stroker.setJoinStyle("round-join")
            realPath = stroker.createStroke(elem_path)
            painter.drawPath(realPath)

            grad = LinearGradient(elem_path.pointAtPercent(0.5),
                                  elem_path.point_at_percent(0.0))
            grad.set_colorAt(0, color1)
            grad.set_colorAt(1, color2)
            grad.setSpread("QGradientReflectSpread")

            painter.fill_path(realPath, QBrush(grad))

    def diameter(self):
        " . "
        return 2 * self.radius

    def area(self):
        " . "
        return math.pi * self.radius * self.radius

    def circumference(self):
        " . "
        return 2 * self.radius * math.pi

    def quadrant(self, angle):
        " . "
        angle = math.radians(angle)
        vector = Vector(self.radius*math.cos(angle), self.radius*math.cos(angle))
        return self.center + vector

    def set_diameter(self, diameter):
        " . "
        circ_rect = Rect()
        circ_rect.setWidth(diameter)
        circ_rect.setHeight(diameter)
        circ_rect.move_center(0, 0)
        self.rect = circ_rect
        self.update_path()

    def set_area(self, area):
        " Changes the radius to match the supplied area. "
        self.radius = math.sqrt(area/math.pi)
        self.update()

    def set_circumference(self, circumference):
        " Changes the radius to match the supplied circumference. "
        self.radius = circumference / (2.0*math.pi)
        self.update()

    def update_path(self):
        path = []
        r = Rect()
        # Add the center point.
        path.add_rect(-0.00000001, -0.00000001, 0.00000002, 0.00000002)
        # Add the circle.
        path.arcmove_to(r, 0)
        path.arcTo(r, 0, 360)
        # NOTE: Reverse the path so that the inside area isn't considered part of the circle. */
        path.arcTo(r, 0, -360)
        setPath(path)

    def paint(self, painter, option, widget):
        obj_scene = scene()
        if not obj_scene:
            return

        paintPen = pen()
        painter.set_pen(paintPen)
        update_rubber(painter)
        if "State_Selected" in option.state:
            paintPen.set_style("dashed")
        if obj_scene.property("ENABLE_LWT"):
            paintPen = line_weightPen()
        painter.set_pen(paintPen)

        painter.drawEllipse(rect())

    def update_rubber(self, painter):
        self.rubber_mode = rubber_mode()
        if self.rubber_mode == "CIRCLE_1P_RAD":
            sceneCenterPoint = self.rubber_point("CIRCLE_CENTER")
            sceneQSnapPoint = self.rubber_point("CIRCLE_RADIUS")
            itemCenterPoint = map_from_scene(sceneCenterPoint)
            itemQSnapPoint = map_from_scene(sceneQSnapPoint)
            itemLine = Line(itemCenterPoint, itemQSnapPoint)
            setPos(sceneCenterPoint)
            sceneLine = Line(sceneCenterPoint, sceneQSnapPoint)
            radius = sceneLine.length()
            setRadius(radius)
            if painter:
                draw_rubber_line(itemLine, painter, "VIEW_COLOR_CROSSHAIR")
            self.update_path()

        elif self.rubber_mode == "CIRCLE_1P_DIA":
            sceneCenterPoint = self.rubber_point("CIRCLE_CENTER")
            sceneQSnapPoint = self.rubber_point("CIRCLE_DIAMETER")
            itemCenterPoint = tools.map_from_scene(sceneCenterPoint)
            itemQSnapPoint = tools.map_from_scene(sceneQSnapPoint)
            itemLine = Line(itemCenterPoint, itemQSnapPoint)
            self.set_position(sceneCenterPoint)
            sceneLine = Line(sceneCenterPoint, sceneQSnapPoint)
            diameter = sceneLine.length()
            set_diameter(diameter)
            if painter:
                draw_rubber_line(itemLine, painter, "VIEW_COLOR_CROSSHAIR")
            self.update_path()

        elif self.rubber_mode == "CIRCLE_2P":
            sceneTan1Point = self.rubber_point("CIRCLE_TAN1")
            sceneQSnapPoint = self.rubber_point("CIRCLE_TAN2")
            sceneLine = Line(sceneTan1Point, sceneQSnapPoint)
            setPos(sceneLine.pointAt(0.5))
            diameter = sceneLine.length()
            set_diameter(diameter)
            self.update_path()

        elif self.rubber_mode == "CIRCLE_3P":
            sceneTan1Point = self.rubber_point("CIRCLE_TAN1")
            sceneTan2Point = self.rubber_point("CIRCLE_TAN2")
            sceneTan3Point = self.rubber_point("CIRCLE_TAN3")

            sceneCenter = Vector()
            arc = embArc_make(sceneTan1Point.x(), sceneTan1Point.y(),
                                sceneTan2Point.x(), sceneTan2Point.y(),
                                sceneTan3Point.x(), sceneTan3Point.y()).arc
            sceneCenter = arc.getCenter()
            sceneCenterPoint(sceneCenter.x, sceneCenter.y)
            sceneLine = Line(sceneCenterPoint, sceneTan3Point)
            setPos(sceneCenterPoint)
            radius = sceneLine.length()
            setRadius(radius)
            self.update_path()

        elif self.rubber_mode == "GRIP":
            if painter:
                gripPoint = self.rubber_point("GRIP_POINT")
                if gripPoint == self.center:
                    painter.drawEllipse(rect().translated(map_from_scene(self.rubber_point(""))-map_from_scene(gripPoint)))

                else:
                    gripRadius = Line(self.center(), self.rubber_point("")).length()
                    painter.drawEllipse(Vector(), gripRadius, gripRadius)

                rubLine = Line(map_from_scene(gripPoint), map_from_scene(self.rubber_point("")))
                draw_rubber_line(rubLine, painter, "VIEW_COLOR_CROSSHAIR")

    def vulcanize():
        debug_message("Circle vulcanize()")
        self.update_rubber()
        self.rubber_mode = "RUBBER_OFF"

    def mouse_snap_point(self, mouse_point):
        " Returns the closest snap point to the mouse point. "
        all_points = self.all_grip_points()
        return closest_vector(all_points, mouse_point)

    def all_grip_points(self):
        r"."
        return [
            self.center,
            self.quadrant(0),
            self.quadrant(90),
            self.quadrant(180),
            self.quadrant(270)
        ]

    def grip_edit(self, before, after):
        r"."
        if before == self.center:
            delta = after-before
            moveBy(delta.x(), delta.y())
        else:
            setRadius(Line(self.center(), after).length())

    def save_path(self):
        r"."
        path = []
        r = Rect()
        path.arcmove_to(r, 0)
        path.arcTo(r, 0, 360)

        s = self.scale
        trans = 0
        trans.rotate(self.rotation)
        trans.scale(s,s)
        return trans.map(path)

    def mouse_callback(self, button, state, x, y):
        if button == "LEFT_BUTTON":
            if state == "DOWN":
                pos_x = x/(0.5*window_width) - 1.0
                pos_y = -y/(0.5*window_height) + 1.0
                mouse_x = x
                mouse_y = y
                for i in range(2):
                    leaf = root.leaves[i]
                    if leaf.left < pos_x and pos_x < leaf.right:
                        if leaf.top < pos_y and pos_y < leaf.bottom:
                            action_id = i
                            break


    def click(self, x, y):
        vector = Vector(x, y)
        if self.mode == "1P_RAD":
            if math.isnan(self.point1.x):
                self.point1 = vector
                self.center = vector
                addRubber("CIRCLE")
                set_rubber_mode("CIRCLE_1P_RAD")
                set_rubber_point("CIRCLE_CENTER", self.cx, self.cy)
                append_prompt_history()
                set_prompt_prefix("Specify radius of circle or [Diameter]: ")
            else:
                self.point2 = vector
                self.rubber_points["CIRCLE_RADIUS"] = self.point2
                self.vulcanize()
                append_prompt_history()

        elif self.mode == "1P_DIA":
            if math.isnan(self.point1.x):
                message = "CIRCLE" + "This should never happen."
                debug_message(message, msgtype="ERROR")
            else:
                self.point2 = vector
                self.rubber_points["CIRCLE_DIAMETER"] = self.point2
                self.vulcanize()
                append_prompt_history()

        elif self.mode == "2P":
            if math.isnan(self.point1.x):
                self.point1 = vector
                add_rubber("CIRCLE")
                self.rubber_mode = "CIRCLE_2P"
                self.rubber_points["CIRCLE_TAN1"] = self.point1
                append_prompt_history()
                set_prompt_prefix("Specify second end point of circle's diameter: ")

            elif math.isnan(self.point2.x):
                self.point2 = vector
                self.rubber_points["CIRCLE_TAN2"] = self.point2
                self.vulcanize()
                append_prompt_history()

            else:
                message = "CIRCLE This should never happen."
                debug_message(message, msgtype="ERROR")

        elif self.mode == "3P":
            if math.isnan(self.point1.x):
                self.point1 = vector
                append_prompt_history()
                set_prompt_prefix("Specify second point on circle: ")

            elif math.isnan(self.point2.x):
                self.point2 = vector
                add_rubber("CIRCLE")
                self.rubber_mode = "CIRCLE_3P"
                self.rubber_points["CIRCLE_TAN1"] = self.point1
                self.rubber_points["CIRCLE_TAN2"] = self.point2
                append_prompt_history()
                set_prompt_prefix("Specify third point on circle: ")

            elif math.isnan(self.point3.x):
                self.point3 = vector
                self.rubber_points["CIRCLE_TAN3"] = self.point3
                self.vulcanize()
                append_prompt_history()

            else:
                message = "CIRCLE This should never happen."
                debug_message(message, msgtype="ERROR")

        elif self.mode == "TTR":
            if math.isnan(self.point1.x):
                self.point1 = vector
                append_prompt_history()
                set_prompt_prefix("Specify point on  for second tangent of circle: ")

            elif math.isnan(self.point2.x):
                self.point2 = vector
                append_prompt_history()
                set_prompt_prefix("Specify radius of circle: ")

            elif math.isnan(self.point3.x):
                self.point3 = vector
                append_prompt_history()
                set_prompt_prefix("Specify second point: ")

            else:
                debug_message("CIRCLE click() for TTR")

    def prompt(self, args, cmd):
        if self.mode == "1P_RAD":
            if math.isnan(self.point1.x):
                # TODO: Probably should add additional qsTr calls here.
                if cmd == "2P":
                    self.mode = "2P"
                    set_prompt_prefix("Specify first end point of circle's diameter: ")

                # TODO: Probably should add additional qsTr calls here.
                elif cmd == "3P":
                    self.mode = "3P"
                    set_prompt_prefix("Specify first point of circle: ")

                # TODO: Probably should add additional qsTr calls here.
                elif cmd == "T" or cmd == "TTR":
                    self.mode = "TTR"
                    set_prompt_prefix("Specify point on  for first tangent of circle: ")

                else:
                    vector = vector_from_str(cmd)
                    if not vector:
                        debug_message("Point or option keyword required.",
                                      msgtype="ALERT")
                        set_prompt_prefix("Specify center point for circle or [3P/2P/Ttr (tan tan radius)]: ")
 
                    else:
                        self.point1 = vector
                        self.center = self.point1
                        add_rubber("CIRCLE")
                        self.rubber_mode = "CIRCLE_1P_RAD"
                        self.rubber_points["CIRCLE_CENTER"] = self.center
                        set_prompt_prefix("Specify radius of circle or [Diameter]: ")

            else:
                # TODO: Probably should add additional qsTr calls here.
                if str == "D" or str == "DIAMETER":
                    self.mode = "1P_DIA"
                    self.rubber_mode = "CIRCLE_1P_DIA"
                    set_prompt_prefix("Specify diameter of circle: ")

                else:
                    num = float(cmd)
                    if math.isnan(num):
                        debug_message(
                            "Requires numeric radius, point on circumference, or \"D\".",
                            msgtype="ALERT"
                        )
                        set_prompt_prefix("Specify radius of circle or [Diameter]: ")
 
                    else:
                        self.rad = num
                        self.point2.x = self.point1.x + self.rad
                        self.point2.y = self.point1.y
                        self.rubber_points["CIRCLE_RADIUS"] = self.point2
                        self.vulcanize()

        elif self.mode == "1P_DIA":
            if math.isnan(self.point1.x):
                message = "CIRCLE This should never happen."
                debug_message(message, msgtype="ERROR")

            if math.isnan(self.point2.x):
                num = float(cmd)
                if math.isnan(num):
                    alert("Requires numeric distance or second point.")
                    set_prompt_prefix("Specify diameter of circle: ")

                else:
                    self.dia = num
                    self.point2.x = self.point1.x + self.dia
                    self.point2.y = self.point1.y
                    set_rubber_point("CIRCLE_DIAMETER", self.point2.x, self.point2.y)
                    self.vulcanize()
            else:
                message = "CIRCLE" + "This should never happen."
                debug_message(message, msgtype="ERROR")

        elif self.mode == "2P":
            if math.isnan(self.point1.x):
                vector = vector_from_str(cmd)
                if not vector:
                    alert("Invalid point.")
                    set_prompt_prefix("Specify first end point of circle's diameter: ")
                else:
                    self.point1 = vector
                    addRubber("CIRCLE")
                    self.rubber_mode = "CIRCLE_2P"
                    self.rubber_points["CIRCLE_TAN1"] = self.point1
                    set_prompt_prefix("Specify second end point of circle's diameter: ")
            elif math.isnan(self.point2.x):
                vector = vector_from_str(cmd)
                if not vector:
                    alert("Invalid point.")
                    set_prompt_prefix("Specify second end point of circle's diameter: ")
                else:
                    self.point2 = vector
                    set_rubber_point("CIRCLE_TAN2", self.point2)
                    self.vulcanize()
            else:
                message = "CIRCLE" + "This should never happen."
                debug_message(message, msgtype="ERROR")

        elif self.mode == "3P":
            vector = vector_from_str(cmd)
            if not vector:
                alert("Invalid point.")
                if math.isnan(self.point1.x):
                    set_prompt_prefix("Specify first point of circle:")
                elif math.isnan(self.point2.x):
                    set_prompt_prefix("Specify second point of circle: ")
                else:
                    set_prompt_prefix("Specify third point of circle: ")
            else:
                if math.isnan(self.point1.x):
                    self.point1 = vector
                    self.rubber_points["CIRCLE_TAN1"] = self.point1
                    set_prompt_prefix("Specify second point of circle: ")
                elif math.isnan(self.point2.x):
                    self.point2 = vector
                    addRubber("CIRCLE")
                    self.rubber_mode = "CIRCLE_3P"
                    self.rubber_points["CIRCLE_TAN2"] = self.point2
                    set_prompt_prefix("Specify third point of circle: ")
                elif math.isnan(self.point3.x):
                    self.point3 = vector
                    self.rubber_points["CIRCLE_TAN3"] = self.point3
                    self.vulcanize()
                else:
                    message = "CIRCLE" + "This should never happen."
                    debug_message(message, msgtype="ERROR")

        elif self.mode == "TTR":
            debug_message("CIRCLE prompt() for TTR")
