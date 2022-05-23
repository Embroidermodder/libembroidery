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

from libembroidery.tools import (
    Pen, Vector, clear_selection, set_prompt_prefix, translate,
    append_prompt_history
)


class Text():
    r"""
    .
    """
    def __init__(self, pen=Pen(), font="Arial"):
        clear_selection()
        self.modes = ["JUSTIFY", "SETFONT", "SETGEOM", "RAPID"]
        self.text = ""
        self.position = Vector(math.nan, math.nan)
        self.justify = "Left"
        self.font = font
        self.height = math.nan
        self.rotation = math.nan
        self.mode = "SETGEOM"
        self.rubber_points = {}
        self.rubber_texts = {}
        set_prompt_prefix(translate("Current font: ") + "" + self.font + "} " + translate("Text height: ") + "" +  self.height + "}")
        append_prompt_history()
        set_prompt_prefix("Specify start point of text or [Justify/Setfont]: ")

    def click(self, x, y):
        r"."
        if self.mode == "SETGEOM":
            if math.isnan(self.textX):
                self.textX = x
                self.textY = y
                addRubber("LINE")
                self.rubber_mode = "LINE"
                set_rubber_point("LINE_START", self.textX, self.textY)
                append_prompt_history()
                set_prompt_prefix("Specify text height " + text_size() + "}: ")

            elif math.isnan(self.text_height):
                self.text_height = calculate_distance(self.textX, self.textY, x, y)
                set_text_size(self.text_height)
                append_prompt_history()
                set_prompt_prefix("Specify text angle " + text_angle() + "}: ")

            elif math.isnan(self.text_rotation):
                self.text_rotation = calculate_angle(self.textX, self.textY, x, y)
                set_text_angle(self.rotation)
                append_prompt_history()
                set_prompt_prefix(translate("Enter text: "))
                self.mode = "RAPID"
                enable_prompt_rapid_fire()
                clear_rubber()
                add_rubber("TEXTSINGLE")
                self.rubber_mode = "TEXTSINGLE"
                self.rubber_points["TEXT_POINT"] = (self.textX, self.textY)
                self.rubber_points["TEXT_HEIGHT_ROTATION"] = (self.height, self.rotation)
                setRubberText("TEXT_FONT", self.textFont)
                setRubberText("TEXT_JUSTIFY", self.justify)
                setRubberText("TEXT_RAPID", self.text)

            else:
                #Do nothing, as we are in rapidFire mode now.
                debug_message(".")

    def prompt(cmd):
        " . "
        if self.mode == "JUSTIFY":
            if cmd == "C" or cmd == "CENTER":
                #TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Center"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix(translate("Specify center point of text or [Justify/Setfont]: "))

            elif cmd == "R" or cmd == "RIGHT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Right"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix(translate("Specify right-end point of text or [Justify/Setfont]: "))

            elif str == "A" or cmd == "ALIGN":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Aligned"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix(translate("Specify start point of text or [Justify/Setfont]: "))

            elif str == "M" or cmd == "MIDDLE":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Middle"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix(translate("Specify middle point of text or [Justify/Setfont]: "))

            elif str == "F" or cmd == "FIT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Fit"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix(translate("Specify start point of text or [Justify/Setfont]: "))

            elif str == "TL" or cmd == "TOPLEFT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = self.mode_SETGEOM
                self.justify = "Top Left"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix("Specify top-left point of text or [Justify/Setfont]: ")

            elif str == "TC" or cmd == "TOPCENTER":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Top Center"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix("Specify top-center point of text or [Justify/Setfont]: ")

            elif cmd == "TR" or cmd == "TOPRIGHT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Top Right"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix("Specify top-right point of text or [Justify/Setfont]: ")

            elif cmd == "ML" or cmd == "MIDDLELEFT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Middle Left"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix(translate("Specify middle-left point of text or [Justify/Setfont]: "))

            elif cmd == "MC" or cmd == "MIDDLECENTER":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Middle Center"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix(translate("Specify middle-center point of text or [Justify/Setfont]: "))

            elif cmd == "MR" or cmd == "MIDDLERIGHT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Middle Right"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix("Specify middle-right point of text or [Justify/Setfont]: ")

            elif str == "BL" or cmd == "BOTTOMLEFT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Bottom Left"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix(translate("Specify bottom-left point of text or [Justify/Setfont]: "))

            elif str == "BC" or cmd == "BOTTOMCENTER":
                #TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Bottom Center"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix(translate("Specify bottom-center point of text or [Justify/Setfont]: "))

            elif str == "BR" or cmd == "BOTTOMRIGHT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Bottom Right"
                self.rubber_texts["TEXT_JUSTIFY"] = self.justify
                set_prompt_prefix(translate("Specify bottom-right point of text or [Justify/Setfont]: "))

            else:
                alert(translate("Invalid option keyword."), msgtype="ALERT")
                set_prompt_prefix(translate("Text Justification Options [Center/Right/Align/Middle/Fit/TL/TC/TR/ML/MC/MR/BL/BC/BR]: "))

        elif self.mode == "SETFONT":
            self.mode = "SETGEOM"
            self.textFont = str
            setRubberText("TEXT_FONT", self.textFont)
            setTextFont(self.textFont)
            set_prompt_prefix(translate("Specify start point of text or [Justify/Setfont]: "))

        elif self.mode == "SETGEOM":
            if math.isnan(self.textX):
                if str == "J" or cmd == "JUSTIFY":
                    #TODO: Probably should add additional qsTr calls here.
                    self.mode = self.mode_JUSTIFY
                    set_prompt_prefix(translate("Text Justification Options [Center/Right/Align/Middle/Fit/TL/TC/TR/ML/MC/MR/BL/BC/BR]: "))

                elif str == "S" or cmd == "SETFONT":
                    # TODO: Probably should add additional qsTr calls here.
                    self.mode = self.mode_SETFONT
                    set_prompt_prefix(translate("Specify font name: "))

                else:
                    strList = str.split(",")
                    if math.isnan(strList[0]) or math.isnan(strList[1]):
                        alert(translate("Point or option keyword required."), msgtype="ALERT")
                        set_prompt_prefix(translate("Specify start point of text or [Justify/Setfont]: "))
 
                    else:
                        self.textX = float(strList[0])
                        self.textY = float(strList[1])
                        addRubber("LINE")
                        set_rubber_mode("LINE")
                        set_rubber_point("LINE_START", self.textX, self.textY)
                        set_prompt_prefix(translate("Specify text height") + " " + textSize() + "}: ")

            elif math.isnan(self.height):
                if str == "":
                    self.height = textSize()
                    set_prompt_prefix(translate("Specify text angle") + " " + textAngle() + "}: ")

                elif math.isnan(cmd):
                    alert("Requires valid numeric distance or second point.", msgtype="ALERT")
                    set_prompt_prefix(translate("Specify text height") + " " + textSize() + "}: ")

                else:
                    self.height = float(cmd)
                    set_prompt_prefix("Specify text angle " + self.angle + "}: ")


            elif math.isnan(self.rotation):
                if str == "":
                    self.rotation = self.angle
                    set_prompt_prefix(translate("Enter text: "))
                    self.mode = "RAPID"
                    enablePromptRapidFire()
                    clearRubber()
                    addRubber("TEXTSINGLE")
                    set_rubber_mode("TEXTSINGLE")
                    set_rubber_point("TEXT_POINT", self.textX, self.textY)
                    set_rubber_point("TEXT_HEIGHT_ROTATION", self.height, self.rotation)
                    setRubberText("TEXT_FONT", self.textFont)
                    setRubberText("TEXT_JUSTIFY", self.justify)
                    setRubberText("TEXT_RAPID", self.text)

                elif math.isnan(cmd):
                    debug_message("Requires valid numeric angle or second point.", msgtype="ALERT")
                    set_prompt_prefix(translate("Specify text angle") + " " + textAngle() + "}: ")

                else:
                    self.rotation = float(cmd)
                    setTextAngle(self.rotation)
                    set_prompt_prefix(translate("Enter text: "))
                    self.mode = self.mode_RAPID
                    enablePromptRapidFire()
                    clearRubber()
                    addRubber("TEXTSINGLE")
                    set_rubber_mode("TEXTSINGLE")
                    set_rubber_point("TEXT_POINT", self.textX, self.textY)
                    set_rubber_point("TEXT_HEIGHT_ROTATION", self.height, self.rotation)
                    setRubberText("TEXT_FONT", self.textFont)
                    setRubberText("TEXT_JUSTIFY", self.justify)
                    setRubberText("TEXT_RAPID", self.text)

            else:
                #Do nothing, as we are in rapidFire mode now.
                debug_message("do_nothing")

        elif self.mode == "RAPID":
            if cmd == "RAPID_ENTER":
                if self.text == "":
                    return
                else:
                    # TODO: Rather than ending the command,
                    # calculate where the next line would be and
                    # modify the x/y to the new point.
                    vulcanize()
                    return
            else:
                self.text = str
                setRubberText("TEXT_RAPID", self.text)

