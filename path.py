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

from embroidermodder.utility import (
    translate, clear_selection, debug_message, error, alert,
    set_prompt_prefix
)


class Path():
    """
    The Path class definition.

    TODO: make paths similar to polylines.
    Review and implement any missing functions/members.
    """

    def __init__(self, command="", data=[],
                 pen=Pen(rgb="#FFFFFF", line_type="solid", line_weight=0.35)):
        "."
        self.type = "Path"
        self.normal_path = 0
        self.pen = pen

        clear_selection()
        self.first_run = True
        self.first = Vector(math.nan, math.nan)
        self.prev = Vector(math.nan, math.nan)
        self.promptPrefix = translate("Specify start point: ")
        if data != []:
            self.data = data
        elif command != "":
            self.data = path_from_command(command)
        self.update(p)

    def copy(self):
        " . "
        debug_message("PathObject copy()")
        # TODO: getCurrentLineType
        return Path(data=self.data, pen=self.pen)

    def update(self, p):
        " . "
        normal_path = p
        reverse_path = normal_path.to_reversed()
        reverse_path.connect_path(normal_path)
        self.setPath(reverse_path)

    def paint(self, painter, option, widget):
        " . "
        obj_scene = self.scene
        if not obj_scene:
            return

        paint_pen = Pen()
        painter.set_pen(paint_pen)
        self.update_rubber(painter)
        if "State_Selected" in option.state:
            paint_pen.set_style("dashed")
        if obj_scene.property("ENABLE_LWT"):
            paint_pen = lineWeightPen()
        painter.set_pen(paint_pen)

        painter.draw_path(objectPath())

    def update_rubber(self, painter):
        """
        TODO: Path Rubber Modes.

        TODO: self.update_rubber() gripping for PathObject.
        """
        return

    def vulcanize(self):
        debug_message("PathObject vulcanize()")
        self.update_rubber()

        self.rubber_mode = "RUBBER_OFF"

        if not normalPath.element_count():
            error(0,
                  translate("Empty Path Error"),
                  translate("The path added contains no points. The command that created this object has flawed logic."))

    def mouse_snap_point(self, mouse_point):
        " Returns the closest snap point to the mouse point. "
        return self.scenePos()

    def all_grip_points(self):
        " TODO: loop thru all path Elements and return their points. "
        gripPoints = [self.scenePos()]
        return gripPoints

    def grip_edit(before, after):
        " TODO: grip_edit() for PathObject."
        return

    def copy_path(self):
        " . "
        return normalPath

    def save_path(self):
        " . "
        s = self.scale
        trans = 0
        trans.rotate(self.rotation)
        trans.scale(s,s)
        return trans.map(normalPath)

    def click(self, x, y):
        " . "
        if self.first_run:
            self.first_run = False
            self.first = Vector(x, y)
            self.prev = Vector(x, y)
            addPath(x,y)
            append_prompt_history()
            set_prompt_prefix(translate("Specify next point or [Arc/Undo]: "))
        else:
            append_prompt_history()
            appendline_toPath(x, y)
            self.prev = Vector(x, y)

    def prompt(self, cmd):
        " . "
        if str == "A" or cmd == "ARC":
            # TODO: Probably should add additional qsTr calls here.
            todo("PATH", "prompt() for ARC")

        elif str == "U" or cmd == "UNDO":
            # TODO: Probably should add additional qsTr calls here.
            todo("PATH", "prompt() for UNDO")

        else:
            strList = str.split(",")
            if math.math.isnan(strList[0]) or math.math.isnan(strList[1]):
                alert(translate("Point or option keyword required."))
                set_prompt_prefix(translate("Specify next point or [Arc/Undo]: "))

            else:
                x = float(strList[0])
                y = float(strList[1])
                if self.first_run:
                    self.first_run = False
                    self.first = Vector(x, y)
                    self.prev = Vector(x, y)
                    addPath(x, y)
                    set_prompt_prefix(translate("Specify next point or [Arc/Undo]: "))
                else:
                    appendline_toPath(x,y)
                    self.prev = Vector(x, y)

    def setObjectPos(self, point):
        " . "
        self.position = point
