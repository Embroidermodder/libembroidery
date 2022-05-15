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

from embroidermodder.utility import (clear_selection, debug_message,
    set_prompt_prefix, translate)

class Circle():
    """
    The circle class definition.
    def SavePath():

    def setRadius(radius)
    def set_diameter(diameter)
    def set_area(area)
    def setCircumference(circumference)
    def update_rubber(QPainter* painter = 0)

    def Color(): return objPen.color()
    def LineWeight(): return lwtPen.widthF()
    def Path(): return path()
    def rubber_mode(): return objrubber_mode
    def RubberPoint(key):
    def RubberText(key):

    def setrubber_mode(mode)  objrubber_mode = mode
    def setRubberPoint(key, point)  objRubberPoints.insert(key, point)
    def setRubberText(key, txt)  objRubberTexts.insert(key, txt)
    def bounding_rect() const
    def shape() const  return path()
    def drawRubberLine(rubLine, painter=0, colorFromScene=0)
    def vulcanize() = 0
    mouse_snap_point(mouse_point) = 0
    QList<Vector> all_grip_points() = 0
    def grip_edit(before, after) = 0
    Line obj_line
    """
    def __init__(self, center, radius,
                 pen=Pen(rgb="#FFFFFF", line_type="solid", line_weight=0.35)):
        " . "
        clear_selection()
        self.mode = "1P_RAD"
        self.point1 = Vector(math.nan, math.nan)
        self.point2 = Vector(math.nan, math.nan)
        self.point3 = Vector(math.nan, math.nan)
        self.type = "Circle"
        self.selectable = True
        self.radius = radius
        self.center = center
        self.update_path()
        self.promptPrefix = translate("Specify center point for circle or [3P/2P/Ttr (tan tan radius)]: ")
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
        self.path = Path()

    def set_rect(self, x, y, w, h):
        """
        def set_rect(self, r):
            p = Path()
            p.add_rect(r)
            self.set_path(p)
        """
        p = Path()
        p.add_rect(x, y, w, h)
        self.set_path(p)

    def line():
        " . "
        return obj_line

    def set_line(self, li):
        " . "
        p = Path()
        p.move_to(li.p1())
        p.line_to(li.p2())
        self.set_path(p)
        obj_line = li

    def set_line(self):
        " . "
        p = Path()
        p.move_to(self.point1)
        p.line_to(self.point2)
        self.set_path(p)
        obj_line.set_line(point1, point2)

    def set_path(self, p):
        " . "
        self.path = p
        self.update()

    def set_color(self, color):
        " . "
        " . "
        objPen.set_color(color)
        lwtPen.set_color(color)

    def set_color_rgb(self, rgb):
        " . "
        objPen.set_color(Color(rgb))
        lwtPen.set_color(Color(rgb))

    def set_line_type(self, lineType):
        " . "
        objPen.set_style(lineType)
        lwtPen.set_style(lineType)

    def set_line_weight(self, lineWeight):
        "NOTE: The objPen will always be cosmetic. "
        objPen.setWidthF(0)

        if lineWeight < 0:
            if lineWeight == OBJ_LWT_BYLAYER:
                lwtPen.setWidthF(0.35)
                # TODO: getLayerLineWeight

            elif lineWeight == OBJ_LWT_BYBLOCK:
                lwtPen.setWidthF(0.35)
                # TODO: getBlockLineWeight

            else:
                warning(0, translate("Error - Negative Lineweight"),
                        translate("Lineweight: %1")
                                        .arg("".setNum(lineWeight)))
                debug_message("Lineweight cannot be negative! Inverting sign.")
                lwtPen.setWidthF(-lineWeight)

        else:
            lwtPen.setWidthF(lineWeight)

    def _rubber_point(self, key):
        " . "
        if key in objRubberPoints:
            return objRubberPoints[key]

        gscene = scene()
        if gscene:
            return scene().property("SCENE_QSNAP_POINT").toPointF()
        return Vector()

    def rubberText(self, key):
        " . "
        if key in objRubberTexts:
            return objRubberTexts[key]
        return ""

    def bounding_rect(self):
        " If gripped, force this  to be drawn even if it is offscreen. "
        if rubber_mode() == "OBJ_RUBBER_GRIP":
            return scene().sceneRect()
        return path().bounding_rect()

    def drawRubberLine(self, rubLine, painter, colorFromScene):
        " . "
        if painter:
            obj_scene = scene()
            if obj_scene:
                colorPen = objPen
                colorPen.set_color(Color(obj_scene.property(colorFromScene).toUInt()))
                painter.set_pen(colorPen)
                painter.drawLine(rubLine)
                painter.set_pen(objPen)

    def realRender(self, painter, render_path):
        "lighter color"
        color1 = Color();
        color2 = color1.darker(150) # /*darker color*/

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

            elem_path = Path()
            elem_path.move_to(elem.x, elem.y)
            elem_path.line_to(next.x, next.y)

            render_pen = Pen(Color(0,0,0,0))
            render_pen.setWidthF(0)
            painter.set_pen(render_pen)
            stroker = Painter()
            stroker.setWidth(0.35)
            stroker.setCapStyle("round-cap")
            stroker.setJoinStyle("round-join")
            realPath = stroker.createStroke(elem_path)
            painter.drawPath(realPath)

            grad = LinearGradient(elem_path.pointAtPercent(0.5), elem_path.pointAtPercent(0.0))
            grad.set_colorAt(0, color1)
            grad.set_colorAt(1, color2)
            grad.setSpread(QGradientReflectSpread)

            painter.fill_path(realPath, QBrush(grad))

    def diameter(self):
        " . "
        return 2 * self.radius

    def Area(self):
        " . "
        return math.pi * self.radius * self.radius

    def circumference(self):
        " . "
        return 2 * self.radius * math.pi

    def Quadrant0(self):
        " . "
        return self.center + Vector(self.radius, 0)

    def Quadrant90(self):
        " . "
        return self.center + Vector(0,-self.radius)

    def Quadrant180(self):
        " . "
        return self.center + Vector(-self.radius,0)

    def Quadrant270(self):
        " . "
        return self.center + Vector(0, self.radius)

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
        self.radius = sqrt(area/math.pi)
        self.update()

    def set_circumference(self, circumference):
        " Changes the radius to match the supplied circumference. "
        self.radius = circumference / (2.0*math.pi)
        self.update()

    def update_path(self):
        path = Path()
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
            paintPen = lineWeightPen()
        painter.set_pen(paintPen)

        painter.drawEllipse(rect())

    def update_rubber(self, painter):
        self.rubber_mode = rubber_mode()
        if self.rubber_mode == "CIRCLE_1P_RAD":
            sceneCenterPoint = RubberPoint("CIRCLE_CENTER")
            sceneQSnapPoint = RubberPoint("CIRCLE_RADIUS")
            itemCenterPoint = map_from_scene(sceneCenterPoint)
            itemQSnapPoint = map_from_scene(sceneQSnapPoint)
            itemLine = Line(itemCenterPoint, itemQSnapPoint)
            setPos(sceneCenterPoint)
            sceneLine = Line(sceneCenterPoint, sceneQSnapPoint)
            radius = sceneLine.length()
            setRadius(radius)
            if painter:
                drawRubberLine(itemLine, painter, "VIEW_COLOR_CROSSHAIR")
            update_path()

        elif self.rubber_mode == "CIRCLE_1P_DIA":
            sceneCenterPoint = RubberPoint("CIRCLE_CENTER")
            sceneQSnapPoint = RubberPoint("CIRCLE_DIAMETER")
            itemCenterPoint = map_from_scene(sceneCenterPoint)
            itemQSnapPoint = map_from_scene(sceneQSnapPoint)
            itemLine = Line(itemCenterPoint, itemQSnapPoint)
            self.set_position(sceneCenterPoint)
            sceneLine = Line(sceneCenterPoint, sceneQSnapPoint)
            diameter = sceneLine.length()
            set_diameter(diameter)
            if painter:
                drawRubberLine(itemLine, painter, "VIEW_COLOR_CROSSHAIR")
            update_path()

        elif self.rubber_mode == "CIRCLE_2P":
            sceneTan1Point = RubberPoint("CIRCLE_TAN1")
            sceneQSnapPoint = RubberPoint("CIRCLE_TAN2")
            sceneLine = Line(sceneTan1Point, sceneQSnapPoint)
            setPos(sceneLine.pointAt(0.5))
            diameter = sceneLine.length()
            set_diameter(diameter)
            update_path()

        elif self.rubber_mode == "CIRCLE_3P":
            sceneTan1Point = RubberPoint("CIRCLE_TAN1")
            sceneTan2Point = RubberPoint("CIRCLE_TAN2")
            sceneTan3Point = RubberPoint("CIRCLE_TAN3")

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
                gripPoint = RubberPoint("GRIP_POINT")
                if gripPoint == self.center:
                    painter.drawEllipse(rect().translated(map_from_scene(RubberPoint(""))-map_from_scene(gripPoint)))

                else:
                    gripRadius = Line(self.center(), RubberPoint("")).length()
                    painter.drawEllipse(Vector(), gripRadius, gripRadius)

                rubLine = Line(map_from_scene(gripPoint), map_from_scene(RubberPoint("")))
                drawRubberLine(rubLine, painter, "VIEW_COLOR_CROSSHAIR")

    def vulcanize():
        debug_message("Circle vulcanize()")
        self.update_rubber()

        setrubber_mode(OBJ_RUBBER_OFF)

    def mouse_snap_point(mouse_point):
        " Returns the closest snap point to the mouse point. "
        center = self.center
        quad0 = Quadrant0()
        quad90 = Quadrant90()
        quad180 = Quadrant180()
        quad270 = Quadrant270()

        cntrDist = Line(mouse_point, center).length()
        q0Dist = Line(mouse_point, quad0).length()
        q90Dist = Line(mouse_point, quad90).length()
        q180Dist = Line(mouse_point, quad180).length()
        q270Dist = Line(mouse_point, quad270).length()

        minDist = min(q0Dist, q90Dist, q180Dist, q270Dist, cntrDist)

        if minDist == cntrDist:
            return center
        elif minDist == q0Dist:
            return quad0
        elif minDist == q90Dist:
            return quad90
        elif minDist == q180Dist:
            return quad180
        elif minDist == q270Dist:
            return quad270

        return scenePos()

    def all_grip_points():
        gripPoints = []
        gripPoints << self.center << Quadrant0() << Quadrant90() << Quadrant180() << Quadrant270()
        return gripPoints

    def grip_edit(self, before, after):
        if before == self.center:
            delta = after-before
            moveBy(delta.x(), delta.y())
        else:
            setRadius(Line(self.center(), after).length())

    def SavePath(self):
        path = Path()
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
                set_prompt_prefix(translate("Specify radius of circle or [Diameter]: "))
            else:
                self.point2 = vector
                set_rubber_point("CIRCLE_RADIUS", self.point2.x, self.point2.y)
                vulcanize()
                append_prompt_history()

        elif self.mode == "1P_DIA":
            if math.isnan(self.point1.x):
                error("CIRCLE", translate("This should never happen."))
            else:
                self.point2 = vector
                set_rubber_point("CIRCLE_DIAMETER", self.point2.x, self.point2.y)
                vulcanize()
                append_prompt_history()

        elif self.mode == "2P":
            if math.isnan(self.point1.x):
                self.point1 = vector
                addRubber("CIRCLE")
                set_rubber_mode("CIRCLE_2P")
                set_rubber_point("CIRCLE_TAN1", self.point1.x, self.point1.y)
                append_prompt_history()
                set_prompt_prefix(translate("Specify second end point of circle's diameter: "))

            elif math.isnan(self.point2.x):
                self.point2 = vector
                set_rubber_point("CIRCLE_TAN2", self.point2.x, self.point2.y)
                vulcanize()
                append_prompt_history()

            else:
                error("CIRCLE", translate("This should never happen."))

        elif self.mode == "3P":
            if math.isnan(self.point1.x):
                self.point1 = vector
                append_prompt_history()
                set_prompt_prefix(translate("Specify second point on circle: "))

            elif math.isnan(self.point2.x):
                self.point2 = vector
                addRubber("CIRCLE")
                set_rubber_mode("CIRCLE_3P")
                set_rubber_point("CIRCLE_TAN1", self.point1.x, self.point1.y)
                set_rubber_point("CIRCLE_TAN2", self.point2.x, self.point2.y)
                append_prompt_history()
                set_prompt_prefix(translate("Specify third point on circle: "))

            elif math.isnan(self.point3.x):
                self.point3 = vector
                set_rubber_point("CIRCLE_TAN3", self.x3, self.y3)
                vulcanize()
                append_prompt_history()
                return

            else:
                error("CIRCLE", translate("This should never happen."))

        elif self.mode == "TTR":
            if math.isnan(self.point1.x):
                self.point1 = vector
                append_prompt_history()
                set_prompt_prefix(translate("Specify point on  for second tangent of circle: "))

            elif math.isnan(self.point2.x):
                self.point2 = vector
                append_prompt_history()
                set_prompt_prefix(translate("Specify radius of circle: "))

            elif math.isnan(self.point3.x):
                self.point3 = vector
                append_prompt_history()
                set_prompt_prefix(translate("Specify second point: "))

            else:
                todo("CIRCLE", "click() for TTR")

    def prompt(self, args, cmd):
        if self.mode == "1P_RAD":
            if math.isnan(self.point1.x):
                # TODO: Probably should add additional qsTr calls here.
                if cmd == "2P":
                    self.mode = "2P"
                    set_prompt_prefix(translate("Specify first end point of circle's diameter: "))

                # TODO: Probably should add additional qsTr calls here.
                elif cmd == "3P":
                    self.mode = "3P"
                    set_prompt_prefix(translate("Specify first point of circle: "))

                # TODO: Probably should add additional qsTr calls here.
                elif cmd == "T" or cmd == "TTR":
                    self.mode = "TTR"
                    set_prompt_prefix(translate("Specify point on  for first tangent of circle: "))

                else:
                    strList = str.split(",")
                    if math.isnan(strList[0]) or math.isnan(strList[1]):
                        alert(translate("Point or option keyword required."))
                        set_prompt_prefix(translate("Specify center point for circle or [3P/2P/Ttr (tan tan radius)]: "))
 
                    else:
                        self.point1.x = float(strList[0])
                        self.point1.y = float(strList[1])
                        self.cx = self.point1.x
                        self.cy = self.point1.y
                        addRubber("CIRCLE")
                        set_rubber_mode("CIRCLE_1P_RAD")
                        set_rubber_point("CIRCLE_CENTER", self.cx, self.cy)
                        set_prompt_prefix(translate("Specify radius of circle or [Diameter]: "))

            else:
                # TODO: Probably should add additional qsTr calls here.
                if str == "D" or str == "DIAMETER":
                    self.mode = circle_mode_1P_DIA
                    set_rubber_mode("CIRCLE_1P_DIA")
                    set_prompt_prefix(translate("Specify diameter of circle: "))

                else:
                    num = float(cmd)
                    if math.isnan(num):
                        alert(translate("Requires numeric radius, point on circumference, or \"D\"."))
                        set_prompt_prefix(translate("Specify radius of circle or [Diameter]: "))
 
                    else:
                        self.rad = num
                        self.point2.x = self.point1.x + self.rad
                        self.point2.y = self.point1.y
                        set_rubber_point("CIRCLE_RADIUS", self.point2.x, self.point2.y)
                        self.vulcanize()

        elif self.mode == "1P_DIA":
            if math.isnan(self.point1.x):
                error("CIRCLE", translate("This should never happen."))

            if math.isnan(self.point2.x):
                num = float(cmd)
                if math.isnan(num):
                    alert(translate("Requires numeric distance or second point."))
                    set_prompt_prefix(translate("Specify diameter of circle: "))

                else:
                    self.dia = num
                    self.point2.x = self.point1.x + self.dia
                    self.point2.y = self.point1.y
                    set_rubber_point("CIRCLE_DIAMETER", self.point2.x, self.point2.y)
                    self.vulcanize()
            else:
                error("CIRCLE", translate("This should never happen."))

        elif self.mode == "2P":
            if math.isnan(self.point1.x):
                vector = vector_from_str(cmd)
                if not vector:
                    alert(translate("Invalid point."))
                    set_prompt_prefix(translate("Specify first end point of circle's diameter: "))
                else:
                    self.point1 = vector
                    addRubber("CIRCLE")
                    self.rubber_mode = "CIRCLE_2P"
                    self.rubber_points["CIRCLE_TAN1"] = self.point1
                    set_prompt_prefix(translate("Specify second end point of circle's diameter: "))
            elif math.isnan(self.point2.x):
                vector = vector_from_str(cmd)
                if not vector:
                    alert(translate("Invalid point."))
                    set_prompt_prefix(translate("Specify second end point of circle's diameter: "))
                else:
                    self.point2 = vector
                    set_rubber_point("CIRCLE_TAN2", self.point2)
                    self.vulcanize()
            else:
                error("CIRCLE", translate("This should never happen."))

        elif self.mode == "3P":
            vector = vector_from_str(cmd)
            if not vector:
                alert(translate("Invalid point."))
                if math.isnan(self.point1.x):
                    set_prompt_prefix(translate("Specify first point of circle:"))
                elif math.isnan(self.point2.x):
                    set_prompt_prefix(translate("Specify second point of circle: "))
                else:
                    set_prompt_prefix(translate("Specify third point of circle: "))
            else:
                if math.isnan(self.point1.x):
                    self.point1 = vector
                    self.rubber_points["CIRCLE_TAN1"] = self.point1
                    set_prompt_prefix(translate("Specify second point of circle: "))
                elif math.isnan(self.point2.x):
                    self.point2 = vector
                    addRubber("CIRCLE")
                    self.rubber_mode = "CIRCLE_3P"
                    self.rubber_points["CIRCLE_TAN2"] = self.point2
                    set_prompt_prefix(translate("Specify third point of circle: "))
                elif math.isnan(self.point3.x):
                    self.point3 = vector
                    self.rubber_points["CIRCLE_TAN3"] = self.point3
                    self.vulcanize()
                else:
                    error("CIRCLE", translate("This should never happen."))

        elif self.mode == "TTR":
            todo("CIRCLE", "prompt() for TTR")
