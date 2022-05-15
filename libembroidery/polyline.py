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
from embroidermodder.geometry.vector import Vector, vector_from_str
from embroidermodder.geometry.line import Line

from embroidermodder.utility import (set_prompt_prefix, clear_selection,
    translate, todo)


class Polyline():
    r"""
    This is necessarily a class because we need the same
    functions for other geometry objects and supporting SVG means
    supporting every geometry object supported natively by it.

    We should be able to initialise using an existing one, maybe
    a copy() function?
    """
    def __init__(self, x, y, rgb="black", p=0, line_weight=0.35,
           line_type="solid"):
        r"""
        Needs to work with the libembroidery polyline, if that's wrapped
        in a class then this class extends that one and we call

        super().__init__()

        here.

        Some of the functions here can then be ported to libembroidery.
        """
        debug_message("Polyline.__init__()")
        self.path = p
        self.position = Vector(x, y)
        self.pen = Pen(rgb=rgb, line_type=line_type, line_weight=line_weight)
        self.rotation = 0.0
        self.scale = 1.0
        self.type = "Polyline"
        self.selectable = 1
        self.grip_index = -1
        self.update_path(p)
        self.normal_path = Path()

        clearSelection()
        self.first_run = True
        self.first = Vector(math.nan, math.nan)
        self.prev = Vector(math.nan, math.nan)
        self.num = 0
        set_prompt_prefix(translate("Specify first point: "))

    def update(self, p):
        r"""
        This is a straight translation and I'm not sure what
        it's doing -- Robin
        """
        self.normal_path = p
        self.reverse_path = self.normal_path.reverse()
        self.reverse_path.connect(self.normal_path)
        self.path = self.reverse_path

    def paint(self, painter, option, widget):
        r"""
        """
        obj_scene = scene()
        if not obj_scene:
            return
        paintPen = pen()
        painter.pen = paintPen
        painter.update_rubber()

        if option.state & QStyle_State_Selected:
            paintPen.set_style(Qt_DashLine)
        if obj_scene.property("ENABLE_LWT").toBool():
            paintPen = lineWeightPen()
        painter.set_pen(paintPen)

        painter.drawPath(normalPath)

        if obj_scene.property("ENABLE_LWT").toBool() and obj_scene.property("ENABLE_REAL").toBool():
            realRender(painter, normalPath)

    def update_rubber(self, painter):
        self.rubber_mode = objectrubber_mode()
        if self.rubber_mode == "OBJ_RUBBER_POLYLINE":
            setObjectPos(objectRubberPoint("POLYLINE_POINT_0"))

            rubberLine = Line (normalPath.currentPosition(), map_from_scene(objectRubberPoint("")))
            if painter:
                drawRubberLine(rubberLine, painter, "VIEW_COLOR_CROSSHAIR")

            ok = 0
            numStr = objectRubberText("POLYLINE_NUM_POINTS")
            if numStr.isNull():
                return
            num = numStr.toInt(ok)
            if not ok:
                return

            appendStr = ""
            rubberPath = Path()
            for i in range(1, num+1):
                appendStr = "POLYLINE_POINT_" + "".setNum(i)
                appendPoint = map_from_scene(objectRubberPoint(appendStr))
                rubberPath.line_to(appendPoint)

            update_path(rubberPath)

            # Ensure the path isn't updated until
            # the number of points is changed again.
            setObjectRubberText("POLYLINE_NUM_POINTS", "")

        elif self.rubber_mode == "OBJ_RUBBER_GRIP":
            if painter:
                elemCount = normalPath.element_count()
                gripPoint = objectRubberPoint("GRIP_POINT")
                if gripIndex == -1:
                    gripIndex = findIndex(gripPoint)
                if gripIndex == -1:
                    return

                if not gripIndex:
                    # First
                    ef = normalPath.element_at(1)
                    efPoint = Vector(ef.x, ef.y)
                    painter.drawLine(efPoint, map_from_scene(objectRubberPoint("")))

                elif gripIndex == elemCount-1:
                    # Last
                    el = normalPath.element_at(gripIndex-1)
                    elPoint = Vector(el.x, el.y)
                    painter.drawLine(elPoint, map_from_scene(objectRubberPoint("")))

                else:
                    # Middle
                    em = normalPath.element_at(gripIndex-1)
                    en = normalPath.element_at(gripIndex+1)
                    emPoint = Vector(em.x, em.y)
                    enPoint = Vector(en.x, en.y)
                    painter.drawLine(emPoint, map_from_scene(objectRubberPoint("")))
                    painter.drawLine(enPoint, map_from_scene(objectRubberPoint("")))

                rubLine = Line(map_from_scene(gripPoint), map_from_scene(objectRubberPoint("")))
                drawRubberLine(rubLine, painter, "VIEW_COLOR_CROSSHAIR")

    def vulcanize(self):
        " . "
        debug_message("PolylineObject vulcanize()")
        self.update_rubber()

        setObjectrubber_mode(OBJ_RUBBER_OFF)

        if not normalPath.element_count():
            Qmessage_box_critical(0, QObject_tr("Empty Polyline Error"), QObject_tr("The polyline added contains no points. The command that created this object has flawed logic."))

    def mouse_snap_point(self, mouse_point):
        " Returns the closest snap point to the mouse point. "
        element = normalPath.element_at(0)
        closestPoint = mapToScene(Vector(element.x, element.y))
        closestDist = Line(mouse_point, closestPoint).length()
        elemCount = normalPath.element_count()
        for i in range(elemCount):
            element = normalPath.element_at(i)
            elemPoint = mapToScene(element.x, element.y)
            elemDist = Line(mouse_point, elemPoint).length()

            if elemDist < closestDist:
                closestPoint = elemPoint
                closestDist = elemDist

        return closestPoint

    def all_grip_points(self):
        gripPoints = []
        for i in range(normalPath.element_count()):
            element = normalPath.element_at(i)
            gripPoints += [mapToScene(element.x, element.y)]

        return gripPoints

    def PolyfindIndex(self, point):
        " . "
        elemCount = normalPath.element_count()
        # NOTE: Points here are in item coordinates.
        itemPoint = map_from_scene(point)
        for i in range(elemCount):
            e = normalPath.element_at(i)
            elemPoint = Vector(e.x, e.y)
            if itemPoint == elemPoint:
                return i

        return -1

    def Polygrip_edit(self, before, after):
        gripIndex = findIndex(before)
        if gripIndex == -1:
            return
        a = map_from_scene(after)
        normalPath.setElementPositionAt(gripIndex, a.x(), a.y())
        update_path(normalPath)
        gripIndex = -1

    def PolyobjectCopyPath():
        return normalPath

    def PolyobjectSavePath():
        s = self.scale
        trans = 0
        trans.rotate(self.rotation)
        trans.scale(s,s)
        return trans.map(normalPath)

    def click(self, x, y):
        if self.first_run:
            self.first_run = False
            self.first = Vector(x, y)
            self.prev = Vector(x, y)
            add_rubber("POLYLINE")
            set_rubber_mode("POLYLINE")
            set_rubber_point("POLYLINE_POINT_0", self.first)
            append_prompt_history()
            set_prompt_prefix(translate("Specify next point or [Undo]: "))
        else:
            self.num += 1
            set_rubber_point(f"POLYLINE_POINT_{num}", Vector(x, y))
            set_rubber_text("POLYLINE_NUM_POINTS", str(num))
            spare_rubber("POLYLINE")
            append_prompt_history()
            self.prevX = x
            self.prevY = y

    def a_click(self, x, y):
        " . "
        if self.first_run:
            add_rubber("LINE")
            set_rubber_mode("LINE")
            set_rubber_point("LINE_START", self.first)
            append_prompt_history()
            set_prompt_prefix(translate("Specify next point or [Undo]: "))

        else:
            set_rubber_point("LINE_END", x, y)
            vulcanize()
            add_rubber("LINE")
            set_rubber_mode("LINE")
            set_rubber_point("LINE_START", x, y)
            append_prompt_history()
            self.prevX = x
            self.prevY = y

    def prompt(self, cmd):
        if self.first_run:
            vector = vector_from_str(cmd)
            if not vector:
                alert(translate("Invalid point."))
                set_prompt_prefix(translate("Specify first point: "))
            else:
                self.first_run = false
                self.first = vector
                self.prev = self.first
                add_rubber("POLYLINE")
                set_rubber_mode("POLYLINE")
                set_rubber_point("POLYLINE_POINT_0", self.first)
                set_prompt_prefix(translate("Specify next point or [Undo]: "))

        else:
            if cmd == "U" or cmd == "UNDO":
                #TODO: Probably should add additional qsTr calls here.
                todo("POLYLINE", "prompt() for UNDO")
            else:
                vector = vector_from_str(cmd)
                if not vector:
                    alert(translate("Point or option keyword required."))
                    set_prompt_prefix(translate("Specify next point or [Undo]: "))
                else:
                    self.num += 1
                    set_rubber_point(f"POLYLINE_POINT_{num}", x, y)
                    set_rubber_text("POLYLINE_NUM_POINTS", str(num))
                    spare_rubber("POLYLINE")
                    self.prev = vector
                    set_prompt_prefix(translate("Specify next point or [Undo]: "))

    def a_prompt(self, cmd):
        " . "
        if self.first_run:
            vector = vector_from_str(cmd)
            if not vector:
                alert(translate("Invalid point."))
                set_prompt_prefix(translate("Specify first point: "))
            else:
                self.first_run = false
                self.first = vector
                self.prev = self.first
                add_rubber("LINE")
                set_rubber_mode("LINE")
                set_rubber_point("LINE_START", self.first)
                set_prompt_prefix(translate("Specify next point or [Undo]: "))
        else:
            if cmd == "U" or cmd == "UNDO":
                # TODO: Probably should add additional qsTr calls here.
                todo("LINE", "prompt() for UNDO")
            else:
                vector = vector_from_str(cmd)
                if not vector:
                    alert(translate("Point or option keyword required."))
                    set_prompt_prefix(translate("Specify next point or [Undo]: "))
                else:
                    set_rubber_point("LINE_END", vector)
                    vulcanize()
                    add_rubber("LINE")
                    set_rubber_mode("LINE")
                    set_rubber_point("LINE_START", vector)
                    self.prev = vector
                    set_prompt_prefix(translate("Specify next point or [Undo]: "))

    def copy(self):
        " . "
        return Polyline()

    def copy_path(self):
        " . "
        return self.normal_path

    def save_path(self):
        " . "
        return self.normal_path

    def find_index(self, point):
        " . "
        return point

    def update_rubber(self, painter = 0):
        " . "
        return

    def vulcanize(self):
        " . "
        return

    def mouse_snap_point(self, mouse_point):
        " . "
        return

    def all_grip_points():
        " . "
        return

    def grip_edit(self, before, after):
        " . "
        return

    def paint(self, painter, options, widget):
        " . "
        return

    def update_path(p):
        " . "
        return

    def a__init__(self):
        r" . "
        self.first_run = True
        self.rubber = "NOT SET"
        self.base  = Vector(math.nan, math.nan)
        self.dest = Vector(math.nan, math.nan)
        self.delta = Vector(math.nan, math.nan)
        self.rubber_mode = "LINE"
        self.rubber_points = {}

        if numSelected() <= 0:
            #TODO: Prompt to select objects if nothing is preselected
            alert(translate("Preselect objects before invoking the move command."))
            return
            message_box("information", translate("Move Preselect"), translate("Preselect objects before invoking the move command."))
        else:
            set_prompt_prefix(translate("Specify base point: "))

    def a_click(self, x, y):
        r" . "
        if self.first_run:
            self.first_run = False
            self.base = Vector(x, y)
            self.rubber = "LINE"
            self.rubber_mode = "LINE"
            self.rubber_points["LINE_START"] = self.base
            preview_on("SELECTED", "MOVE", self.base, 0)
            append_prompt_history()
            set_prompt_prefix(translate("Specify destination point: "))
        else:
            self.dest = Vector(x, y)
            self.delta = self.dest.subtract(self.base)
            move_selected(self.delta)
            preview_off()

    def a_prompt(self, user_string):
        r" . "
        if self.first_run:
            vector = vector_from_str(user_string)
            if not vector:
                alert(translate("Invalid point."))
                set_prompt_prefix(translate("Specify base point: "))
            else:
                self.first_run = False
                self.base = vector
                self.rubber = "LINE"
                self.rubber_mode = "LINE"
                self.rubber_points["LINE_START"] = self.base
                preview_on("SELECTED", "MOVE", self.base, 0)
                set_prompt_prefix(translate("Specify destination point: "))

        else:
            vector = vector_from_str(user_string)
            if not vector:
                alert(translate("Invalid point."))
                set_prompt_prefix(translate("Specify destination point: "))
            else:
                self.dest = vector
                self.delta = self.dest.subtract(self.base)
                move_selected(self.delta)
                preview_off()
