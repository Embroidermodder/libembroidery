#!/usr/bin/env python3

r"""
    Libembroidery.

    -----

    Copyright 2018-2022 The Embroidermodder Team
    Libembroidery is Open Source Software.
    See LICENSE for licensing terms.

    -----

    The Path structure, needs to suport SVG path features.
"""

import math

from libembroidery.tools import (
    clear_selection, debug_message,
    set_prompt_prefix, Pen, Vector, path_from_command,
    append_prompt_history, vector_from_str
)


class Path():
    """
    The Path class definition.

    TODO: make paths similar to polylines.
    Review and implement any missing functions/members.
    """
    def __init__(self, command="", data=[], pen=Pen()):
        r"."
        self.type = "Path"
        self.normal_path = []
        self.pen = pen
        self.lwt_pen = pen

        clear_selection()
        self.first_run = True
        self.first = Vector(math.nan, math.nan)
        self.prev = Vector(math.nan, math.nan)
        self.promptPrefix = "Specify start point: "
        if data != []:
            self.data = data
        elif command != "":
            self.data = path_from_command(command)
        self.update()

    def copy(self):
        " . "
        debug_message("PathObject copy()")
        # TODO: getCurrentLineType
        return Path(data=self.data, pen=self.pen)

    def update(self):
        " . "
        self.normal_path.reverse()
        # reverse_path.connect_path(normal_path)
        # self.setPath(reverse_path)

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
            paint_pen = self.lwt_pen
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

        if not self.normal_path.element_count():
            details = (
                "The path added contains no points. "
                + "The command that created this object has flawed logic."
            )
            debug_message("Empty Path Error" + details, msgtype="ERROR")

    def mouse_snap_point(self, mouse_point):
        " Returns the closest snap point to the mouse point. "
        return self.scene_pos()

    def all_grip_points(self):
        " TODO: loop thru all path Elements and return their points. "
        gripPoints = [self.scene_pos()]
        return gripPoints

    def grip_edit(before, after):
        " TODO: grip_edit() for PathObject."
        return

    def copy_path(self):
        " . "
        return self.normal_path

    def save_path(self):
        " . "
        s = self.scale
        trans = 0
        trans.rotate(self.rotation)
        trans.scale(s, s)
        return trans.map(self.normal_path)

    def click(self, x, y):
        " . "
        if self.first_run:
            self.first_run = False
            self.first = Vector(x, y)
            self.prev = Vector(x, y)
            addPath(x, y)
            append_prompt_history()
            set_prompt_prefix("Specify next point or [Arc/Undo]: ")
        else:
            append_prompt_history()
            append_line_to_path(x, y)
            self.prev = Vector(x, y)

    def prompt(self, cmd):
        " . "
        if str == "A" or cmd == "ARC":
            # TODO: Probably should add additional qsTr calls here.
            debug_message("PATH prompt() for ARC")

        elif str == "U" or cmd == "UNDO":
            # TODO: Probably should add additional qsTr calls here.
            debug_message("PATH prompt() for UNDO")

        else:
            vector = vector_from_str(cmd)
            if not vector:
                alert("Point or option keyword required.")
                prefix = "Specify next point or [Arc/Undo]: "
                set_prompt_prefix(prefix)

            else:
                if self.first_run:
                    self.first_run = False
                    self.first = vector
                    self.prev = vector
                    add_path(vector)
                    set_prompt_prefix("Specify next point or [Arc/Undo]: ")
                else:
                    append_line_to_path(vector)
                    self.prev = vector

    def set_object_pos(self, point):
        " . "
        self.position = point