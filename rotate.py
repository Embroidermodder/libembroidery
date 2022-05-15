#!/usr/bin/env python3

r"""
    Embroidermodder 2.

    ------------------------------------------------------------

    Copyright 2013-2022 The Embroidermodder Team
    Embroidermodder 2 is Open Source Software.
    See LICENSE for licensing terms.

    ------------------------------------------------------------

    The Rotate class definition file.

    This was here to facilitate the ROTATE command for the
    in-built console. This may not be used in the 2.0.0 version.
"""

class Rotate():
    " . "
    def __init__(self):
        " . "
        self.mode = "NORMAL"
        self.modes = ["NORMAL", "REFERENCE"]
        self.first_run = True
        self.base = Vector(math.nan, math.nan)
        self.dest = Vector(math.nan, math.nan)
        self.angle = math.nan
        self.base_r = Vector(math.nan, math.nan)
        self.dest_r = Vector(math.nan, math.nan)
        self.angle_ref = math.nan
        self.angle_new = math.nan
        self.rubber_mode = "LINE"
        self.rubber_points = {}

        if num_selected() <= 0:
            #TODO: Prompt to select objects if nothing is preselected
            message = translate("Preselect objects before invoking the rotate command.")
            alert()
            return
            message_box("information", translate("Rotate Preselect"), message)

        else:
            set_prompt_prefix(translate("Specify base point: "))

    def click(self, x, y):
        " . "
        if self.mode == "NORMAL":
            if self.first_run:
                self.first_run = False
                self.base = Vector(x, y)
                add_rubber("LINE")
                self.rubber_mode = "LINE"
                set_rubber_point("LINE_START", self.base)
                preview_on("SELECTED", "ROTATE", self.base, 0)
                append_prompt_history()
                set_prompt_prefix(translate("Specify rotation angle or [Reference]: "))
            else:
                self.dest = Vector(x, y)
                self.angle = calculate_angle(self.base, self.dest)
                append_prompt_history()
                rotate_selected(self.baseX, self.baseY, self.angle)
                preview_off()
                return

        elif self.mode == "REFERENCE":
            if math.isnan(self.base_r.x):
                self.base_r = vector
                append_prompt_history()
                add_rubber("LINE")
                self.rubber_mode = "LINE"
                self.rubber_points["LINE_START"] = self.base_r
                set_prompt_prefix(translate("Specify second point: "))

            elif math.isnan(self.dest_r.x):
                self.dest_r = vector
                self.angle_ref = calculate_angle(self.base_r, self.dest_r)
                self.rubber_points["LINE_START"] = self.base
                preview_on("SELECTED", "ROTATE", self.base, self.angle_ref)
                append_prompt_history()
                set_prompt_prefix(translate("Specify the new angle: "))

            elif math.isnan(self.angle_new):
                self.angle_new = calculate_angle(self.base, vector)
                rotate_selected(self.base, self.angle_new - self.angle_ref)
                preview_off()

    def prompt(self, cmd):
        " . "
        if self.mode == "NORMAL":
            if self.first_run:
                vector = vector_from_str(cmd)
                if math.isnan(vector.x) or math.isnan(vector.y):
                    alert(translate("Invalid point."))
                    set_prompt_prefix(translate("Specify base point: "))
                else:
                    self.first_run = False
                    self.base = vector
                    add_rubber("LINE")
                    self.rubber_mode = "LINE"
                    set_rubber_point("LINE_START", self.base)
                    preview_on("SELECTED", "ROTATE", self.base, 0)
                    set_prompt_prefix(translate("Specify rotation angle or [Reference]: "))

            else:
                if cmd[0] == "R" or cmd == "REFERENCE":
                    # TODO: Probably should add additional qsTr calls here.
                    self.mode = self.mode_REFERENCE
                    set_prompt_prefix(translate("Specify the reference angle") + " 0.00}: ")
                    clearRubber()
                    preview_off()
                else:
                    if math.isnan(cmd):
                        alert(translate("Requires valid numeric angle, second point, or option keyword."))
                        set_prompt_prefix(translate("Specify rotation angle or [Reference]: "))
                    else:
                        self.angle = float(cmd)
                        rotate_selected(self.base, self.angle)
                        preview_off()
                        return

        elif self.mode == "REFERENCE":
            if math.isnan(self.base_r.x):
                if math.isnan(cmd):
                    vector = vector_from_str(cmd)
                    if math.isnan(vector.x) or math.isnan(vector.y):
                        alert(translate("Requires valid numeric angle or two points."))
                        set_prompt_prefix(translate("Specify the reference angle") + " 0.00}: ")
                    else:
                        self.base_r = vector
                        add_rubber("LINE")
                        self.rubber_mode = "LINE"
                        self.rubber_points["LINE_START"] = self.base_r
                        set_prompt_prefix(translate("Specify second point: "))
 
                else:
                    # The base and dest values are only set
                    # here to advance the command.
                    self.base_r = Vector(0.0, 0.0)
                    self.dest_r = Vector(0.0, 0.0)
                    # The reference angle is what we will use later.
                    self.angle_ref = float(cmd)
                    add_rubber("LINE")
                    self.rubber_mode = "LINE"
                    self.rubber_points["LINE_START"] = self.base
                    preview_on("SELECTED", "ROTATE", self.base, self.angle_ref)
                    set_prompt_prefix(translate("Specify the new angle: "))

            elif math.isnan(self.dest_r.x):
                if math.isnan(cmd):
                    vector = vector_from_str(cmd)
                    if math.isnan(vector.x) or math.isnan(vector.y):
                        alert(translate("Requires valid numeric angle or two points."))
                        set_prompt_prefix(translate("Specify second point: "))
                    else:
                        self.dest_r = vector
                        self.angle_ref = calculate_angle(self.base_r, self.dest_r)
                        preview_on("SELECTED", "ROTATE", self.base, self.angle_ref)
                        set_rubber_point("LINE_START", self.base)
                        set_prompt_prefix(translate("Specify the new angle: "))

                else:
                    # The base and dest values are only set here to
                    # advance the command.
                    self.base_r = Vector(0.0, 0.0)
                    self.dest_r = Vector(0.0, 0.0)
                    # The reference angle is what we will use later.
                    self.angle_ref = float(cmd)
                    preview_on("SELECTED", "ROTATE", self.base.x, self.base.y, self.angle_ref)
                    set_prompt_prefix(translate("Specify the new angle: "))

            elif math.isnan(self.angle_new):
                if math.isnan(cmd):
                    vector = vector_from_str(cmd)
                    if math.isnan(strList[0]) or math.isnan(strList[1]):
                        alert(translate("Requires valid numeric angle or second point."))
                        set_prompt_prefix(translate("Specify the new angle: "))
                    else:
                        self.angle_new = calculate_angle(self.base, vector)
                        rotate_selected(self.base, self.angle_new - self.angle_ref)
                        preview_off()
                else:
                    self.angle_new = float(cmd)
                    rotate_selected(self.base, self.angle_new - self.angle_ref)
                    preview_off()
