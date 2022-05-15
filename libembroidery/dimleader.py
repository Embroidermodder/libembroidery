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

from embroidermodder.geometry.path import Path
from embroidermodder.geometry.tools import (Pen, Vector, vector_from_str,
                                            closest_vector)
from embroidermodder.geometry.line import Line

from embroidermodder.utility import (translate, clear_selection,
                                     set_prompt_prefix, alert, debug_message, 
                                     add_rubber, append_prompt_history)


class DimLeader():
    r"""
    The DimLeader class definition.

    EndPoint1() const
    obj_end_point_2() const
    MidPoint()  const
    def X1(): return EndPoint1().x()
    def Y1(): return EndPoint1().y()
    def X2(): return obj_end_point_2().x()
    def Y2(): return obj_end_point_2().y()
    def DeltaX(): return (obj_end_point_2().x() - EndPoint1().x())
    def DeltaY(): return (obj_end_point_2().y() - EndPoint1().y())
    def Angle():
    def Length(): return line().length()

    def setEndPoint1(EmbVector v)
    def setobj_end_point_2(EmbVector v)

    def grip_edit(before, after)
    def paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)

    def update_leader()
    Path line_stylePath
    Path arrow_style_path
    arrow_style_angle
    arrow_style_length
    line_styleAngle
    line_style_length
    """
    def __init__(self, x1=math.nan, y1=math.nan, x2=math.nan, y2=math.nan,
                 pen=Pen(rgb="#000000", line_type="solid", line_weight=0.35)):
        self.point1 = Vector(x1, y1)
        self.point2 = Vector(x2, y2)
        self.type = "DimLeader"
        self.pen = pen
        self.selectable = True
        self.rubber_mode = "NOT SET"
        self.rubber_points = {}
        # NOTE: Allow this enum to evaluate false.
        self.arrow_style = ["NoArrow", "Open", "Closed", "Dot", "Box", "Tick"]
        # NOTE: Allow this enum to evaluate false.
        self.line_style = ["NoLine", "Flared", "Fletching"]
        self.curved = 0
        self.filled = 1

        # TODO: Adding the text is not complete yet.
        clear_selection()
        set_prompt_prefix(translate("Specify first point: "))
        return self

    def click(self, x, y):
        if math.isnan(self.point1.x):
            self.point1 = Vector(x, y)
            add_rubber("DIMLEADER")
            self.rubber_mode = "DIMLEADER_LINE"
            self.rubber_points["DIMLEADER_LINE_START"] = self.point1
            append_prompt_history()
            set_prompt_prefix(translate("Specify second point: "))
        else:
            self.point2 = Vector(x, y)
            self.rubber_points["DIMLEADER_LINE_END"] = self.point2
            self.vulcanize()
            append_prompt_history()

    def prompt(self, cmd):
        vector = vector_from_str(cmd)
        if math.isnan(self.point1.x):
            if not vector:
                alert(translate("Requires two points."))
                set_prompt_prefix(translate("Specify first point: "))

            else:
                self.point1 = vector
                add_rubber("DIMLEADER")
                self.rubber_mode = "DIMLEADER_LINE"
                self.rubber_points["DIMLEADER_LINE_START"] = vector
                set_prompt_prefix(translate("Specify second point: "))

        else:
            if not vector:
                alert(translate("Requires two points."))
                set_prompt_prefix(translate("Specify second point: "))
            else:
                self.point2 = vector
                self.rubber_points["DIMLEADER_LINE_END"] = self.point2
                self.vulcanize()

    def copy(self):
        " . "
        debug_message("DimLeader copy()")
        return DimLeader(
            x1=self.point1.x,
            y1=self.point1.y,
            x2=self.point2.x,
            y2=self.point2.y,
            pen=self.pen)

    def midpoint(self):
        " . "
        return Line(self.point1, self.point2).point_at(0.5)

    def angle(self):
        " . "
        angle = Line(self.point1, self.point2).angle() - self.rotation
        return math.fmod(angle, 360.0)

    def update_leader(self):
        "todo make all these constants customizable"
        arrow_style = "Closed"
        arrow_style_angle = 15.0
        arrow_style_length = 1.0
        line_styleAngle = 45.0
        line_style_length = 1.0

        lyne = Line()
        angle = lyne.angle()
        ap0 = lyne.p1()
        lp0 = lyne.p2()

        # Arrow
        lynePerp = Line(lyne.pointAt(arrow_style_length/lyne.length()), lp0)
        lynePerp.setAngle(angle + 90)
        lyne1 = Line(ap0, lp0)
        lyne2 = Line(ap0, lp0)
        lyne1.setAngle(angle + arrow_style_angle)
        lyne2.setAngle(angle - arrow_style_angle)
        # ap1
        # ap2
        # HACK: these need fixing
        # lynePerp.intersects(lyne1, &ap1)
        # lynePerp.intersects(lyne2, &ap2)

        # So they don't cause memory access problems.
        ap1 = lyne1.p1()
        ap2 = lyne2.p1()

        r"""
        Math Diagram
        *                 .(ap1)                     .(lp1)
        *                /|                         /|
        *               / |                        / |
        *              /  |                       /  |
        *             /   |                      /   |
        *            /    |                     /    |
        *           /     |                    /     |
        *          /      |                   /      |
        *         /       |                  /       |
        *        /+(aSA)  |                 /+(lSA)  |
        * (ap0)./__(aSL)__|__________(lp0)./__(lSL)__|
        *       \ -(aSA)  |                \ -(lSA)  |
        *        \        |                 \        |
        *         \       |                  \       |
        *          \      |                   \      |
        *           \     |                    \     |
        *            \    |                     \    |
        *             \   |                      \   |
        *              \  |                       \  |
        *               \ |                        \ |
        *                \|                         \|
        *                 .(ap2)                     .(lp2)
        """

        if arrow_style == "Open":
            arrow_style_path = [
                ["move_to", ap1],
                ["line_to", ap0],
                ["line_to", ap2],
                ["line_to", ap0],
                ["line_to", ap1]
            ]

        elif arrow_style == "Closed":
            arrow_style_path = [
                ["move_to", ap1],
                ["line_to", ap0],
                ["line_to", ap2],
                ["line_to", ap1]
            ]

        elif arrow_style == "Dot":
            arrow_style_path = Path()
            arrow_style_path.addEllipse(ap0, arrow_style_length, arrow_style_length)

        elif arrow_style == "Box":
            arrow_style_path = Path()
            side = Line(ap1, ap2).length()
            ar0 = Rect(0, 0, side, side)
            ar0.move_center(ap0)
            arrow_style_path.add_rect(ar0)

        elif arrow_style == "Tick":
            line_stylePath = Path()
            line_stylePath.move_to(ap0)
            line_stylePath.line_to(lp0)

    def paint(self, painter, option, widget):
        obj_scene = scene()
        if not obj_scene:
            return

        paint_pen = Pen()
        painter.set_pen(paint_pen)
        self.update_rubber(painter)
        if "QStyle_State_Selected" in option.state:
            paint_pen.set_style("dashed")
        if obj_scene.property("ENABLE_LWT").toBool():
            paint_pen = lwt_pen()
        painter.set_pen(paint_pen)

        painter.draw_path("line_stylePath")
        painter.draw_path("arrow_stylePath")

        if self.filled:
            painter.fill_path("arrow_stylePath", self.pen.rgb)

    def update_rubber(self, painter):
        if self.rubber_mode == "DIMLEADER_LINE":
            scene_start_point = self.rubber_points["DIMLEADER_LINE_START"]
            sceneQSnapPoint = self.rubber_points["DIMLEADER_LINE_END"]

            setEndPoint1(scene_start_point)
            setobj_end_point_2(sceneQSnapPoint)

        elif self.rubber_mode == "Grip":
            if painter:
                gripPoint = self.rubber_points["GRIP_POINT"]
                if gripPoint == EndPoint1():
                    painter.drawLine(line().p2(), map_from_scene(RubberPoint("")))
                elif gripPoint == obj_end_point_2():
                    painter.drawLine(line().p1(), map_from_scene(RubberPoint("")))
                elif gripPoint == MidPoint():
                    painter.drawLine(line().translated(map_from_scene(RubberPoint(""))-map_from_scene(gripPoint)))

    def vulcanize(self):
        " . "
        debug_message("DimLeader vulcanize()")
        self.update_rubber()
        self.rubber_mode = "OFF"

    def mouse_snap_point(self, mouse_point):
        " Returns the closest snap point to the mouse point. "
        all_points = self.all_grip_points()
        return closest_vector(all_points, mouse_point)

    def all_grip_points(self):
        " . "
        grip_points = [self.point1, self.point2]
        if self.curved:
            grip_points += [self.midpoint()]
        return grip_points

    def grip_edit(self, before, after):
        if before == EndPoint1():
            setEndPoint1(after)
        elif before == obj_end_point_2():
            setobj_end_point_2(after)
        elif before == MidPoint():
            delta = after-before
            moveBy(delta.x(), delta.y())
