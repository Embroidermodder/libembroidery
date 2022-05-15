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

from embroidermodder.geometry.tools import Pen, Vector, vector_from_str
from embroidermodder.geometry.line import Line

from embroidermodder.utility import debug_message


class Point():
    """
    Path objectSavePath() const

    objectPos() const  return scenePos()
      objectX()   const  return scenePos().x()
      objectY()   const  return scenePos().y()

    def setObjectPos(point)  setPos(point.x(), point.y())
    def setObjectPos(x, y)  setPos(x, y)
    def setObjectX(x)  setObjectPos(x, objectY())
    def setObjectY(y)  setObjectPos(objectX(), y)

    def update_rubber(QPainter* painter = 0)
    def vulcanize()
    mouse_snap_point(mouse_point)
    QList<Vector> all_grip_points()
    def grip_edit(before, after)
    """
    def __init__(self, x, y, pen=Pen()):
        " TODO: pass in proper lineweight. "
        super().__init__(self)
        self.type = "Point"
        self.position = Vector(x, y)
        self.pen = pen

        setRect(-0.00000001, -0.00000001, 0.00000002, 0.00000002)
        clear_selection()
        set_prompt_prefix(translate("Specify point: "))

    def click(self, x, y):
        " . "
        append_prompt_history()
        set_prompt_prefix("X = " + x.toString() + ", Y = " + y.toString())
        append_prompt_history()

    def prompt(self, cmd):
        " . "
        strList = str.split(",")
        if math.isnan(strList[0]) or math.isnan(strList[1]):
            alert(translate("Invalid point."))
            set_prompt_prefix(translate("Specify point: "))
        else:
            append_prompt_history()
            set_prompt_prefix("X = " + strList[0].toString() + ", Y = " + strList[1].toString())
            append_prompt_history()

    def copy(self):
        " . "
        debug_message("PointObject copy()")
        p = Point(self.x, self.y, rgb=self.rgb, line_type="solid")
        # TODO: getCurrentLineType
        setRotation(self.rotation())
        return p

    def paint(self, painter, option, widget):
        " . "
        obj_scene = scene()
        if not obj_scene:
            return

        paintPen = pen()
        painter.set_pen(paintPen)
        self.update_rubber(painter)
        if "State_Selected" in option.state:
            paintPen.set_style("dashed")
        if obj_scene.property("ENABLE_LWT"):
            paintPen = pen.line_weight()
        painter.set_pen(paintPen)

        painter.drawPoint(0,0)

    def update_rubber(painter):
        " . "
        self.rubber_mode = objectrubber_mode()
        if self.rubber_mode == "GRIP":
            if painter:
                gripPoint = self.rubber_point["GRIP_POINT"]
                if gripPoint == scenePos():
                    rubLine = Line(map_from_scene(gripPoint), map_from_scene(objectRubberPoint("")))
                    drawRubberLine(rubLine, painter, "VIEW_COLOR_CROSSHAIR")

    def vulcanize():
        " . "
        debug_message("PointObject vulcanize()")
        self.update_rubber()

        self.rubber_mode = "RUBBER_OFF"

    def mouse_snap_point(self, mouse_point):
        " Returns the closest snap point to the mouse point. "
        return self.scene_position

    def all_grip_points():
        " Returns all grip points: currently just the scene position. "
        return [self.scene_position]

    def grip_edit(self, before, after):
        " . "
        if before == self.scenePos():
            delta = after-before
            moveBy(delta.x(), delta.y())

    def save_path(self):
        " . "
        path = Path()
        path.add_rect(-0.00000001, -0.00000001, 0.00000002, 0.00000002)
        return path

    def __init__(self):
        " TODO: translate needed here when complete. "
        clearSelection()
        self.first_run = True
        set_prompt_prefix("TODO: Current point settings: PDMODE=?  PDSIZE=?")
        append_prompt_history()
        set_prompt_prefix(translate("Specify first point: "))
        return self

    def click(self, x, y):
        if self.first_run:
            self.first_run = False
            append_prompt_history()
            set_prompt_prefix(translate("Specify next point: "))
            addPoint(x,y)
        else:
            append_prompt_history()
            addPoint(x,y)

    def prompt(self, str):
        " . "
        if self.first_run:
            if str == "M" or cmd == "MODE":
                #TODO: Probably should add additional qsTr calls here.
                todo("POINT", "prompt() for PDMODE")

            elif str == "S" or cmd == "SIZE":
                #TODO: Probably should add additional qsTr calls here.
                todo("POINT", "prompt() for PDSIZE")

            vector = vector_from_str(cmd)
            if not vector:
                alert(translate("Invalid point."))
                set_prompt_prefix(translate("Specify first point: "))
            else:
                self.first_run = False
                set_prompt_prefix(translate("Specify next point: "))
                addPoint(vector)

        else:
            vector = vector_from_str(cmd)
            if not vector:
                alert(translate("Invalid point."))
                set_prompt_prefix(translate("Specify next point: "))
            else:
                set_prompt_prefix(translate("Specify next point: "))
                addPoint(vector)
