#!/usr/bin/env python3

r"""
    Embroidermodder 2.

    ------------------------------------------------------------

    Copyright 2013-2022 The Embroidermodder Team
    Embroidermodder 2 is Open Source Software.
    See LICENSE for licensing terms.

    ------------------------------------------------------------

    The Line class definition file.
"""

import math

from libembroidery.tools import (Vector, Pen, append_prompt_history,
                                 map_from_scene, debug_message,
                                 set_prompt_prefix, vector_from_str)


class Line():
    r"""
    Check for angle and length functions.
    """
    def __init__(self, pen=Pen(),
                 start=Vector(math.nan, math.nan),
                 end=Vector(math.nan, math.nan)):
        " . "
        self.pen = pen
        self.type = "Line"
        self.start = start
        self.end = end

        self.mode = "NORMAL"
        self.first_run = True
        self.base = self.start
        self.dest = self.end
        self.factor = math.nan
        self.factorRef = math.nan
        self.factor_new = math.nan

        if num_selected <= 0:
            # TODO: Prompt to select objects if nothing is preselected
            debug_message(
                "Preselect objects before invoking the scale command.",
                msgtype="ALERT"
            )
            debug_message(
                "information"
                + "Scale Preselect"
                + "Preselect objects before invoking the scale command."
            )

        else:
            set_prompt_prefix("Specify base point: ")

    def copy(self):
        " . "
        debug_message("Line.copy()")
        return Line(start=self.start, end=self.end, pen=self.pen)

    def set_start(self, start):
        r" . "
        delta = self.end - start
        self.rotation = 0.0
        self.scale = 1.0
        set_line(Vector(0, 0), delta)
        set_pos(self.start)

    def set_end(self, end):
        r" . "
        delta = end - scenePos()
        self.rotation = 0.0
        self.scale = 1.0
        set_line(Vector(0, 0), delta)
        set_pos(self.end)

    def obj_end_point_2():
        " . "
        v = Vector()
        v.x = line().x2()
        v.y = line().y2()
        v.scale(self.scale)
        v.rotate(radians(self.rotation))
        return scenePos() + v

    def mid_point(self):
        " . "
        v = self.pointAt(0.5)
        v.scale(self.scale)
        v.rotate(radians(self.rotation))
        return scenePos() + v

    def angle(self):
        " . "
        angle = line().angle() - self.rotation
        return math.fmod(angle, 360.0)

    def paint(self, painter, option, widget):
        " . "
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

        if self.rubber_mode != "RUBBER_LINE":
            painter.drawLine(line())

        if obj_scene.property("ENABLE_LWT").toBool() and obj_scene.property("ENABLE_REAL").toBool(): realRender(painter, path())

    def update_rubber(self, painter):
        if self.rubber_mode == "RUBBER_LINE":
            scene_start_point = self.rubber_point("LINE_START")
            sceneQSnapPoint = self.rubber_point("LINE_END")

            setObjectEndPoint1(scene_start_point)
            setobj_end_point_2(sceneQSnapPoint)

            draw_rubber_line(line(), painter, "VIEW_COLOR_CROSSHAIR")

        elif self.rubber_mode == "RUBBER_GRIP":
            if painter:
                gripPoint = self.rubber_point("GRIP_POINT")
                if gripPoint == objectEndPoint1():
                    painter.drawLine(line().p2(), map_from_scene(self.rubber_point("")))
                elif gripPoint == obj_end_point_2():
                    painter.drawLine(line().p1(), map_from_scene(self.rubber_point("")))
                elif gripPoint == self.mid_point():
                    painter.drawLine(line().translated(map_from_scene(self.rubber_point(""))-map_from_scene(gripPoint)))

                rubLine = Line(map_from_scene(gripPoint), map_from_scene(self.rubber_point("")))
                draw_rubber_line(rubLine, painter, "VIEW_COLOR_CROSSHAIR")

    def vulcanize(self):
        r"."
        debug_message("LineObject vulcanize()")
        self.update_rubber()
        self.rubber_mode = "RUBBER_OFF"

    def mouse_snap_point(self, mouse_point):
        " Returns the closest snap point to the mouse point. "
        all_points = self.all_grip_points()
        return closest_vector(all_points, mouse_point)

    def all_grip_points(self):
        r"."
        gripPoints = []
        gripPoints << objectEndPoint1() << obj_end_point_2() << self.mid_point()
        return gripPoints

    def grip_edit(self, before, after):
        r"."
        if before == objectEndPoint1():
            setObjectEndPoint1(after.x(), after.y())
        elif before == obj_end_point_2():
            setobj_end_point_2(after.x(), after.y())
        elif before == self.mid_point():
            delta = after-before
            moveBy(delta.x(), delta.y())

    def save_path(self):
        r"."
        path = []
        delta = self.end - self.start
        path += ["move_to", self.start]
        path += ["line_to", delta]
        return path

    def click(self, point):
        r"."
        if self.mode == "NORMAL":
            if self.first_run:
                self.first_run = False
                self.start = point
                add_rubber("LINE")
                self.rubber_mode = "LINE"
                set_rubber_point("LINE_START", self.baseX, self.baseY)
                previewOn("SELECTED", "SCALE", self.baseX, self.baseY, 1)
                append_prompt_history()
                set_prompt_prefix("Specify scale factor or [Reference]: ")

            else:
                self.end = point
                self.factor = calculate_distance(self.start, self.end)
                append_prompt_history()
                scale_selected(self.start, self.factor)
                previewOff()

        elif self.mode == "REFERENCE":
            if math.isnan(self.baseRX):
                self.baseRX = x
                self.baseRY = y
                append_prompt_history()
                addRubber("LINE")
                self.rubber_mode = "LINE"
                set_rubber_point("LINE_START", self.baseRX, self.baseRY)
                set_prompt_prefix(translate("Specify second point: "))

            elif math.isnan(self.destRX):
                self.destRX = x
                self.destRY = y
                self.factorRef = calculate_distance(self.baseRX, self.baseRY, self.destRX, self.destRY)
                if self.factorRef <= 0.0:
                    self.destRX = math.nan
                    self.destRY = math.nan
                    self.factorRef = math.nan
                    debug_message("Value must be positive and nonzero.", msgtype="ALERT")
                    set_prompt_prefix(translate("Specify second point: "))

                else:
                    append_prompt_history()
                    set_rubber_point("LINE_START", self.baseX, self.baseY)
                    previewOn("SELECTED", "SCALE", self.baseX, self.baseY, self.factorRef)
                    set_prompt_prefix("Specify new length: ")

            elif math.isnan(self.factor_new):
                self.factor_new = calculate_distance(self.baseX, self.baseY, x, y)
                if self.factor_new <= 0.0:
                    self.factor_new = math.nan
                    debug_message("Value must be positive and nonzero.", msgtype="ALERT")
                    set_prompt_prefix("Specify new length: ")
                else:
                    append_prompt_history()
                    scale_selected(self.baseX, self.baseY, self.factor_new/self.factorRef)
                    previewOff()

    def prompt(self, cmd):
        if self.mode == self.mode_NORMAL:
            if self.first_run:
                vector = vector_from_str(cmd)
                if not vector:
                    alert("Invalid point.")
                    set_prompt_prefix("Specify base point: ")

                else:
                    self.first_run = False
                    self.start = vector
                    addRubber("LINE")
                    set_rubber_mode("LINE")
                    self.rubber_points["LINE_START"] = self.start
                    previewOn("SELECTED", "SCALE", self.start, 1)
                    set_prompt_prefix("Specify scale factor or [Reference]: ")

            else:
                if str == "R" or cmd == "REFERENCE":
                    #TODO: Probably should add additional qsTr calls here.
                    self.mode = "REFERENCE"
                    set_prompt_prefix("Specify reference length 1}: ")
                    clear_rubber()
                    previewOff()

                else:
                    if math.isnan(cmd):
                        alert("Requires valid numeric distance, second point, or option keyword.")
                        set_prompt_prefix("Specify scale factor or [Reference]: ")
    
                    else:
                        self.factor = float(cmd)
                        scale_selected(self.baseX, self.baseY, self.factor)
                        previewOff()

        elif self.mode == "REFERENCE":
            if math.isnan(self.baseRX):
                if math.isnan(cmd):
                    vector = vector_from_str(cmd)
                    if not vector:
                        alert("Requires valid numeric distance or two points.")
                        set_prompt_prefix("Specify reference length 1}: ")
                    else:
                        self.baseRX = float(strList[0])
                        self.baseRY = float(strList[1])
                        addRubber("LINE")
                        set_rubber_mode("LINE")
                        set_rubber_point("LINE_START", self.baseRX, self.baseRY)
                        set_prompt_prefix(translate("Specify second point: "))
                else:
                    # The base and dest values are only set here to advance the command.
                    self.baseRX = 0.0
                    self.baseRY = 0.0
                    self.destRX = 0.0
                    self.destRY = 0.0
                    # The reference length is what we will use later.
                    self.factorRef = float(cmd)
                    if self.factorRef <= 0.0:
                        self.baseRX = math.nan
                        self.baseRY = math.nan
                        self.destRX = math.nan
                        self.destRY = math.nan
                        self.factorRef = math.nan
                        alert("Value must be positive and nonzero.")
                        set_prompt_prefix(translate("Specify reference length") + " 1}: ")
                    else:
                        addRubber("LINE")
                        set_rubber_mode("LINE")
                        set_rubber_point("LINE_START", self.baseX, self.baseY)
                        previewOn("SELECTED", "SCALE", self.baseX, self.baseY, self.factorRef)
                        set_prompt_prefix(translate("Specify new length: "))

            elif math.isnan(self.destR.x):
                if math.isnan(cmd):
                    vector = vector_from_str(cmd)
                    if not vector:
                        alert("Requires valid numeric distance or two points.")
                        set_prompt_prefix("Specify second point: ")
                    else:
                        self.destR = vector
                        self.factorRef = calculate_distance(self.baseR, self.destR)
                        if self.factorRef <= 0.0:
                            self.destR = Vector(math.nan, math.nan)
                            self.factorRef = math.nan
                            alert("Value must be positive and nonzero.")
                            set_prompt_prefix("Specify second point: ")
        
                        else:
                            set_rubber_point("LINE_START", self.base)
                            previewOn("SELECTED", "SCALE", self.base, self.factorRef)
                            set_prompt_prefix("Specify new length: ")

                else:
                    # The base and dest values are only set here to
                    # advance the command.
                    self.base_r = Vector(0.0, 0.0)
                    self.dest_r = Vector(0.0, 0.0)

                    #The reference length is what we will use later.
                    self.factorRef = float(cmd)
                    if self.factorRef <= 0.0:
                        self.dest_r = Vector(math.nan, math.nan)
                        self.factorRef = math.nan
                        alert("Value must be positive and nonzero.")
                        set_prompt_prefix("Specify second point: ")
                    else:
                        set_rubber_point("LINE_START", self.base)
                        previewOn("SELECTED", "SCALE", self.base, self.factorRef)
                        set_prompt_prefix("Specify new length: ")

            elif math.isnan(self.factor_new):
                if math.isnan(cmd):
                    vector = vector_from_str(cmd)
                    if not vector:
                        alert("Requires valid numeric distance or second point.")
                        set_prompt_prefix(translate("Specify new length: "))
                    else:
                        self.factor_new = calculate_distance(self.base, vector)
                        if self.factor_new <= 0.0:
                            self.factor_new = math.nan
                            alert("Value must be positive and nonzero.")
                            set_prompt_prefix(translate("Specify new length: "))
        
                        else:
                            scaleSelected(self.baseX, self.baseY, self.factor_new/self.factorRef)
                            previewOff()

                else:
                    self.factor_new = float(cmd)
                    if self.factor_new <= 0.0:
                        self.factor_new = math.nan
                        alert(translate("Value must be positive and nonzero."))
                        set_prompt_prefix(translate("Specify new length: "))
    
                    else:
                        scaleSelected(self.baseX, self.baseY, self.factor_new/self.factorRef)
                        previewOff()

    def a__init__(self):
        " . "
        clearSelection()
        self.x1 = math.nan
        self.y1 = math.nan
        self.x2 = math.nan
        self.y2 = math.nan
        set_prompt_prefix(translate("Specify first point: "))

    def a_click(self, x, y):
        " . "
        if math.isnan(self.x1):
            self.x1 = x
            self.y1 = y
            addRubber("LINE")
            set_rubber_mode("LINE")
            set_rubber_point("LINE_START", self.x1, self.y1)
            append_prompt_history()
            set_prompt_prefix(translate("Specify second point: "))
        else:
            append_prompt_history()
            self.x2 = x
            self.y2 = y
            reportDistance()

    def a_prompt(self, cmd):
        " . "
        strList = cmd.split(",")
        if math.isnan(self.x1):
            if math.isnan(strList[0]) or math.isnan(strList[1]):
                alert(translate("Requires numeric distance or two points."))
                set_prompt_prefix(translate("Specify first point: "))
            else:
                self.x1 = float(strList[0])
                self.y1 = float(strList[1])
                addRubber("LINE")
                set_rubber_mode("LINE")
                set_rubber_point("LINE_START", self.x1, self.y1)
                set_prompt_prefix(translate("Specify second point: "))

        else:
            if math.isnan(strList[0]) or math.isnan(strList[1]):
                alert(translate("Requires numeric distance or two points."))
                set_prompt_prefix(translate("Specify second point: "))
            else:
                self.x2 = float(strList[0])
                self.y2 = float(strList[1])
                reportDistance()

    def report_distance(self):
        r"""
        Cartesian Coordinate System reported:

                 (+)
                 90
                 |
        (-) 180__|__0 (+)
                 |
                270
                (-)
        """
        dx = self.x2 - self.x1
        dy = self.y2 - self.y1

        dist = calculate_distance(self.x1,self.y1,self.x2, self.y2)
        angle = calculate_angle(self.x1,self.y1,self.x2, self.y2)

        set_prompt_prefix(translate("Distance") + " = " + dist.toString()
            + ", " + translate("Angle") + " = " + angle.toString())
        append_prompt_history()
        set_prompt_prefix(translate("Delta X") + " = " + dx.toString() + ", "
            + translate("Delta Y") + " = " + dy.toString())
        append_prompt_history()
