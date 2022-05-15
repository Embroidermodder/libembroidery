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

from embroidermodder.geometry.vector import Vector

class Line():
    """
    Path objectSavePath() const
    def objectEndPoint1():
        return scenePos()
    def obj_end_point_2():
    def objectMidPoint():
    def objectX1():
        return objectEndPoint1().x
    def objectY1():
        return objectEndPoint1().y
    def objectX2():
        return obj_end_point_2().x
    def objectY2():
        return obj_end_point_2().y
    def objectDeltaX():
        return (obj_end_point_2().x - objectEndPoint1().x)
    def objectDeltaY():
        return (obj_end_point_2().y - objectEndPoint1().y)
    def objectAngle():
    def objectLength():
        return line().length()*scale()
    def setObjectEndPoint1(endPt1)
    def setObjectEndPoint1(x1, y1)
    def setobj_end_point_2(endPt2)
    def setobj_end_point_2(x2, y2)
    def setObjectX1(x):
        setObjectEndPoint1(x, objectEndPoint1().y())
    def setObjectY1(y):
        setObjectEndPoint1(objectEndPoint1().x(), y)
    def setObjectX2(x):
        setobj_end_point_2(x, obj_end_point_2().y())
    def setObjectY2(y):
        setobj_end_point_2(obj_end_point_2().x(), y)
    """
    def __init__(self, rgb="#FFFFFF", line_type="solid", line_weight=0.35,
                 start=Vector(math.nan, math.nan),
                 end=Vector(math.nan, math.nan)):
        " . "
        self.pen = Pen(rgb=rgb, line_type=line_type, line_weight=line_weight)
        self.type = "Line"
        self.start = start
        self.end = end

    def copy(self):
        " . "
        debug_message("Line.copy()")
        return Line(start=self.start, end=self.end,
                    rgb=self.rgb, line_type=self.line_type)

    def set_start(self, start):
        " . "
        delta = self.obj_end_point_2() - start
        self.rotation = 0.0
        self.scale = 1.0
        setLine(0, 0, delta.x, delta.y)
        setPos(x1, y1)

    def set_end(self, end):
        " . "
        delta = end - scenePos()
        self.rotation = 0.0
        self.scale = 1.0
        setLine(0, 0, delta.x, delta.y)
        setPos(endPt1.x, endPt1.y)

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

    def objectAngle(self):
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
            scene_start_point = objectRubberPoint("LINE_START")
            sceneQSnapPoint = objectRubberPoint("LINE_END")

            setObjectEndPoint1(scene_start_point)
            setobj_end_point_2(sceneQSnapPoint)

            drawRubberLine(line(), painter, "VIEW_COLOR_CROSSHAIR")

        elif self.rubber_mode == "RUBBER_GRIP":
            if painter:
                gripPoint = objectRubberPoint("GRIP_POINT")
                if gripPoint == objectEndPoint1():
                    painter.drawLine(line().p2(), map_from_scene(objectRubberPoint("")))
                elif gripPoint == obj_end_point_2():
                    painter.drawLine(line().p1(), map_from_scene(objectRubberPoint("")))
                elif gripPoint == objectMidPoint():  painter.drawLine(line().translated(map_from_scene(objectRubberPoint(""))-map_from_scene(gripPoint)))

                rubLine = Line(map_from_scene(gripPoint), map_from_scene(objectRubberPoint("")))
                drawRubberLine(rubLine, painter, "VIEW_COLOR_CROSSHAIR")

    def vulcanize():
        debug_message("LineObject vulcanize()")
        self.update_rubber()

        self.rubber_mode = "RUBBER_OFF"

    def mouse_snap_point(self, mouse_point):
        " Returns the closest snap point to the mouse point. "
        all_points = self.all_grip_points()
        return closest_vector(all_points, mouse_point)

    def all_grip_points(self):
        gripPoints = []
        gripPoints << objectEndPoint1() << obj_end_point_2() << objectMidPoint()
        return gripPoints

    def grip_edit(self, before, after):
        if before == objectEndPoint1():
            setObjectEndPoint1(after.x(), after.y())
        elif before == obj_end_point_2():
            setobj_end_point_2(after.x(), after.y())
        elif before == objectMidPoint():
            delta = after-before
            moveBy(delta.x(), delta.y())

    def save_path():
        path = Path()
        path.line_to(objectDeltaX(), objectDeltaY())
        return path

    def __init__(self):
        self.mode = "NORMAL"
        self.first_run = True
        self.baseX  = math.nan
        self.baseY  = math.nan
        self.destX  = math.nan
        self.destY  = math.nan
        self.factor = math.nan
        self.factorRef = math.nan
        self.factorNew = math.nan

        if numSelected() <= 0:
            #TODO: Prompt to select objects if nothing is preselected
            alert(translate("Preselect objects before invoking the scale command."))
            messageBox("information", translate("Scale Preselect"), translate("Preselect objects before invoking the scale command."))

        else:
            set_prompt_prefix(translate("Specify base point: "))

        def click(x, y):
            if self.mode == "NORMAL":
                if self.first_run:
                    self.first_run = false
                    self.baseX = x
                    self.baseY = y
                    addRubber("LINE")
                    self.rubber_mode = "LINE"
                    set_rubber_point("LINE_START", self.baseX, self.baseY)
                    previewOn("SELECTED", "SCALE", self.baseX, self.baseY, 1)
                    append_prompt_history()
                    set_prompt_prefix(translate("Specify scale factor or [Reference]: "))

                else:
                    self.destX = x
                    self.destY = y
                    self.factor = calculateDistance(self.baseX, self.baseY, self.destX, self.destY)
                    append_prompt_history()
                    scaleSelected(self.baseX, self.baseY, self.factor)
                    previewOff()
                    return

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
                    self.factorRef = calculateDistance(self.baseRX, self.baseRY, self.destRX, self.destRY)
                    if self.factorRef <= 0.0:
                        self.destRX    = math.nan
                        self.destRY    = math.nan
                        self.factorRef = math.nan
                        alert(translate("Value must be positive and nonzero."))
                        set_prompt_prefix(translate("Specify second point: "))
 
                    else:
                        append_prompt_history()
                        set_rubber_point("LINE_START", self.baseX, self.baseY)
                        previewOn("SELECTED", "SCALE", self.baseX, self.baseY, self.factorRef)
                        set_prompt_prefix(translate("Specify new length: "))

                elif math.isnan(self.factorNew):
                    self.factorNew = calculateDistance(self.baseX, self.baseY, x, y)
                    if self.factorNew <= 0.0:
                        self.factorNew = math.nan
                        alert(translate("Value must be positive and nonzero."))
                        set_prompt_prefix(translate("Specify new length: "))
                    else:
                        append_prompt_history()
                        scaleSelected(self.baseX, self.baseY, self.factorNew/self.factorRef)
                        previewOff()

        def prompt(self, cmd):
            if self.mode == self.mode_NORMAL:
                if self.first_run:
                    strList = str.split(",")
                    if math.isnan(strList[0]) or math.isnan(strList[1]):
                        alert(translate("Invalid point."))
                        set_prompt_prefix(translate("Specify base point: "))
 
                    else:
                        self.first_run = false
                        self.baseX = float(strList[0])
                        self.baseY = float(strList[1])
                        addRubber("LINE")
                        set_rubber_mode("LINE")
                        set_rubber_point("LINE_START", self.baseX, self.baseY)
                        previewOn("SELECTED", "SCALE", self.baseX, self.baseY, 1)
                        set_prompt_prefix(translate("Specify scale factor or [Reference]: "))

                else:
                    if str == "R" or cmd == "REFERENCE":
                        #TODO: Probably should add additional qsTr calls here.
                        self.mode = "REFERENCE"
                        set_prompt_prefix(translate("Specify reference length") + " 1}: ")
                        clearRubber()
                        previewOff()
 
                    else:
                        if math.isnan(cmd):
                            alert(translate("Requires valid numeric distance, second point, or option keyword."))
                            set_prompt_prefix(translate("Specify scale factor or [Reference]: "))
     
                        else:
                            self.factor = float(cmd)
                            scaleSelected(self.baseX, self.baseY, self.factor)
                            previewOff()
                            return

            elif self.mode == "REFERENCE":
                if math.isnan(self.baseRX):
                    if math.isnan(cmd):
                        strList = str.split(",")
                        if math.isnan(strList[0]) or math.isnan(strList[1]):
                            alert(translate("Requires valid numeric distance or two points."))
                            set_prompt_prefix(translate("Specify reference length") + " 1}: ")
                        else:
                            self.baseRX = float(strList[0])
                            self.baseRY = float(strList[1])
                            addRubber("LINE")
                            set_rubber_mode("LINE")
                            set_rubber_point("LINE_START", self.baseRX, self.baseRY)
                            set_prompt_prefix(translate("Specify second point: "))
                    else:
                        #The base and dest values are only set here to advance the command.
                        self.baseRX = 0.0
                        self.baseRY = 0.0
                        self.destRX = 0.0
                        self.destRY = 0.0
                        #The reference length is what we will use later.
                        self.factorRef = float(cmd)
                        if self.factorRef <= 0.0:
                            self.baseRX = math.nan
                            self.baseRY = math.nan
                            self.destRX = math.nan
                            self.destRY = math.nan
                            self.factorRef = math.nan
                            alert(translate("Value must be positive and nonzero."))
                            set_prompt_prefix(translate("Specify reference length") + " 1}: ")
                        else:
                            addRubber("LINE")
                            set_rubber_mode("LINE")
                            set_rubber_point("LINE_START", self.baseX, self.baseY)
                            previewOn("SELECTED", "SCALE", self.baseX, self.baseY, self.factorRef)
                            set_prompt_prefix(translate("Specify new length: "))

                elif math.isnan(self.destRX):
                    if math.isnan(cmd):
                        strList = str.split(",")
                        if math.isnan(strList[0]) or math.isnan(strList[1]):
                            alert(translate("Requires valid numeric distance or two points."))
                            set_prompt_prefix(translate("Specify second point: "))
                        else:
                            self.destRX = float(strList[0])
                            self.destRY = float(strList[1])
                            self.factorRef = calculateDistance(self.baseRX, self.baseRY, self.destRX, self.destRY)
                            if self.factorRef <= 0.0:
                                self.destRX = math.nan
                                self.destRY = math.nan
                                self.factorRef = math.nan
                                alert(translate("Value must be positive and nonzero."))
                                set_prompt_prefix(translate("Specify second point: "))
         
                            else:
                                set_rubber_point("LINE_START", self.baseX, self.baseY)
                                previewOn("SELECTED", "SCALE", self.baseX, self.baseY, self.factorRef)
                                set_prompt_prefix(translate("Specify new length: "))

                    else:
                        # The base and dest values are only set here to
                        # advance the command.
                        self.base_r = Vector(0.0, 0.0)
                        self.dest_r = Vector(0.0, 0.0)

                        #The reference length is what we will use later.
                        self.factorRef = float(cmd)
                        if self.factorRef <= 0.0:
                            self.destRX    = math.nan
                            self.destRY    = math.nan
                            self.factorRef = math.nan
                            alert(translate("Value must be positive and nonzero."))
                            set_prompt_prefix(translate("Specify second point: "))
                        else:
                            set_rubber_point("LINE_START", self.baseX, self.baseY)
                            previewOn("SELECTED", "SCALE", self.baseX, self.baseY, self.factorRef)
                            set_prompt_prefix(translate("Specify new length: "))

                elif math.isnan(self.factorNew):
                    if math.isnan(cmd):
                        strList = str.split(",")
                        if math.isnan(strList[0]) or math.isnan(strList[1]):
                            alert(translate("Requires valid numeric distance or second point."))
                            set_prompt_prefix(translate("Specify new length: "))
                        else:
                            x = float(strList[0])
                            y = float(strList[1])
                            self.factorNew = calculateDistance(self.baseX, self.baseY, x, y)
                            if self.factorNew <= 0.0:
                                self.factorNew = math.nan
                                alert(translate("Value must be positive and nonzero."))
                                set_prompt_prefix(translate("Specify new length: "))
         
                            else:
                                scaleSelected(self.baseX, self.baseY, self.factorNew/self.factorRef)
                                previewOff()
                                return

                    else:
                        self.factorNew = float(cmd)
                        if self.factorNew <= 0.0:
                            self.factorNew = math.nan
                            alert(translate("Value must be positive and nonzero."))
                            set_prompt_prefix(translate("Specify new length: "))
     
                        else:
                            scaleSelected(self.baseX, self.baseY, self.factorNew/self.factorRef)
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

        dist = calculateDistance(self.x1,self.y1,self.x2, self.y2)
        angle = calculate_angle(self.x1,self.y1,self.x2, self.y2)

        set_prompt_prefix(translate("Distance") + " = " + dist.toString()
            + ", " + translate("Angle") + " = " + angle.toString())
        append_prompt_history()
        set_prompt_prefix(translate("Delta X") + " = " + dx.toString() + ", "
            + translate("Delta Y") + " = " + dy.toString())
        append_prompt_history()
