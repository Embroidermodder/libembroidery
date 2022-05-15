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

from embroidermodder.geometry.tools import Pen, Vector

from embroidermodder.utility import (clear_selection, set_prompt_prefix, translate)


class Text():
    r"""
    .
    """
    def __init__(self, pen=Pen()):
        clear_selection()
        self.modes = ["JUSTIFY", "SETFONT", "SETGEOM", "RAPID"]
        self.text = ""
        self.position = Vector(math.nan, math.nan)
        self.justify = "Left"
        self.font = textFont()
        self.height = math.nan
        self.rotation = math.nan
        self.mode = self.mode_SETGEOM
        set_prompt_prefix(translate("Current font: ") + "" + self.textFont + "} " + translate("Text height: ") + "" +  textSize() + "}")
        append_prompt_history()
        set_prompt_prefix(translate("Specify start point of text or [Justify/Setfont]: "))
        return self

    def click(x, y):
        if self.mode == "SETGEOM":
            if math.isnan(self.textX):
                self.textX = x
                self.textY = y
                addRubber("LINE")
                set_rubber_mode("LINE")
                set_rubber_point("LINE_START", self.textX, self.textY)
                append_prompt_history()
                set_prompt_prefix(translate("Specify text height") + " " + textSize() + "}: ")

            elif math.isnan(self.textHeight):
                self.textHeight = calculateDistance(self.textX, self.textY, x, y)
                setTextSize(self.textHeight)
                append_prompt_history()
                set_prompt_prefix(translate("Specify text angle") + " " + textAngle() + "}: ")

            elif math.isnan(self.textRotation):
                self.textRotation = calculate_angle(self.textX, self.textY, x, y)
                setTextAngle(self.textRotation)
                append_prompt_history()
                set_prompt_prefix(translate("Enter text: "))
                self.mode = self.mode_RAPID
                enablePromptRapidFire()
                clearRubber()
                addRubber("TEXTSINGLE")
                set_rubber_mode("TEXTSINGLE")
                set_rubber_point("TEXT_POINT", self.textX, self.textY)
                set_rubber_point("TEXT_HEIGHT_ROTATION", self.textHeight, self.textRotation)
                setRubberText("TEXT_FONT", self.textFont)
                setRubberText("TEXT_JUSTIFY", self.textJustify)
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
                self.textJustify = "Center"
                setRubberText("TEXT_JUSTIFY", self.textJustify)
                set_prompt_prefix(translate("Specify center point of text or [Justify/Setfont]: "))

            elif cmd == "R" or cmd == "RIGHT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Right"
                setRubberText("TEXT_JUSTIFY", self.justify)
                set_prompt_prefix(translate("Specify right-end point of text or [Justify/Setfont]: "))

            elif str == "A" or cmd == "ALIGN":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.justify = "Aligned"
                setRubberText("TEXT_JUSTIFY", self.justify)
                set_prompt_prefix(translate("Specify start point of text or [Justify/Setfont]: "))

            elif str == "M" or cmd == "MIDDLE":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.textJustify = "Middle"
                setRubberText("TEXT_JUSTIFY", self.textJustify)
                set_prompt_prefix(translate("Specify middle point of text or [Justify/Setfont]: "))

            elif str == "F" or cmd == "FIT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.textJustify = "Fit"
                setRubberText("TEXT_JUSTIFY", self.textJustify)
                set_prompt_prefix(translate("Specify start point of text or [Justify/Setfont]: "))

            elif str == "TL" or cmd == "TOPLEFT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = self.mode_SETGEOM
                self.textJustify = "Top Left"
                setRubberText("TEXT_JUSTIFY", self.textJustify)
                set_prompt_prefix(translate("Specify top-left point of text or [Justify/Setfont]: "))

            elif str == "TC" or cmd == "TOPCENTER":
                #TODO: Probably should add additional qsTr calls here.
                self.mode = self.mode_SETGEOM
                self.textJustify = "Top Center"
                setRubberText("TEXT_JUSTIFY", self.textJustify)
                set_prompt_prefix(translate("Specify top-center point of text or [Justify/Setfont]: "))

            elif cmd == "TR" or cmd == "TOPRIGHT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.textJustify = "Top Right"
                setRubberText("TEXT_JUSTIFY", self.textJustify)
                set_prompt_prefix(translate("Specify top-right point of text or [Justify/Setfont]: "))

            elif cmd == "ML" or cmd == "MIDDLELEFT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.textJustify = "Middle Left"
                setRubberText("TEXT_JUSTIFY", self.textJustify)
                set_prompt_prefix(translate("Specify middle-left point of text or [Justify/Setfont]: "))

            elif cmd == "MC" or cmd == "MIDDLECENTER":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.textJustify = "Middle Center"
                setRubberText("TEXT_JUSTIFY", self.textJustify)
                set_prompt_prefix(translate("Specify middle-center point of text or [Justify/Setfont]: "))

            elif cmd == "MR" or cmd == "MIDDLERIGHT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.textJustify = "Middle Right"
                setRubberText("TEXT_JUSTIFY", self.textJustify)
                set_prompt_prefix(translate("Specify middle-right point of text or [Justify/Setfont]: "))

            elif str == "BL" or cmd == "BOTTOMLEFT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.textJustify = "Bottom Left"
                setRubberText("TEXT_JUSTIFY", self.textJustify)
                set_prompt_prefix(translate("Specify bottom-left point of text or [Justify/Setfont]: "))

            elif str == "BC" or cmd == "BOTTOMCENTER":
                #TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.textJustify = "Bottom Center"
                setRubberText("TEXT_JUSTIFY", self.textJustify)
                set_prompt_prefix(translate("Specify bottom-center point of text or [Justify/Setfont]: "))

            elif str == "BR" or cmd == "BOTTOMRIGHT":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SETGEOM"
                self.textJustify = "Bottom Right"
                setRubberText("TEXT_JUSTIFY", self.textJustify)
                set_prompt_prefix(translate("Specify bottom-right point of text or [Justify/Setfont]: "))

            else:
                alert(translate("Invalid option keyword."))
                set_prompt_prefix(translate("Text Justification Options [Center/Right/Align/Middle/Fit/TL/TC/TR/ML/MC/MR/BL/BC/BR]: "))

        elif self.mode == self.mode_SETFONT:
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
                        alert(translate("Point or option keyword required."))
                        set_prompt_prefix(translate("Specify start point of text or [Justify/Setfont]: "))
 
                    else:
                        self.textX = float(strList[0])
                        self.textY = float(strList[1])
                        addRubber("LINE")
                        set_rubber_mode("LINE")
                        set_rubber_point("LINE_START", self.textX, self.textY)
                        set_prompt_prefix(translate("Specify text height") + " " + textSize() + "}: ")

            elif math.isnan(self.textHeight):
                if str == "":
                    self.textHeight = textSize()
                    set_prompt_prefix(translate("Specify text angle") + " " + textAngle() + "}: ")

                elif math.isnan(cmd):
                    alert(translate("Requires valid numeric distance or second point."))
                    set_prompt_prefix(translate("Specify text height") + " " + textSize() + "}: ")

                else:
                    self.textHeight = float(cmd)
                    setTextSize(self.textHeight)
                    set_prompt_prefix(translate("Specify text angle") + " " + textAngle() + "}: ")


            elif math.isnan(self.textRotation):
                if str == "":
                    self.textRotation = textAngle()
                    set_prompt_prefix(translate("Enter text: "))
                    self.mode = self.mode_RAPID
                    enablePromptRapidFire()
                    clearRubber()
                    addRubber("TEXTSINGLE")
                    set_rubber_mode("TEXTSINGLE")
                    set_rubber_point("TEXT_POINT", self.textX, self.textY)
                    set_rubber_point("TEXT_HEIGHT_ROTATION", self.textHeight, self.textRotation)
                    setRubberText("TEXT_FONT", self.textFont)
                    setRubberText("TEXT_JUSTIFY", self.textJustify)
                    setRubberText("TEXT_RAPID", self.text)

                elif math.isnan(cmd):
                    alert(translate("Requires valid numeric angle or second point."))
                    set_prompt_prefix(translate("Specify text angle") + " " + textAngle() + "}: ")

                else:
                    self.textRotation = float(cmd)
                    setTextAngle(self.textRotation)
                    set_prompt_prefix(translate("Enter text: "))
                    self.mode = self.mode_RAPID
                    enablePromptRapidFire()
                    clearRubber()
                    addRubber("TEXTSINGLE")
                    set_rubber_mode("TEXTSINGLE")
                    set_rubber_point("TEXT_POINT", self.textX, self.textY)
                    set_rubber_point("TEXT_HEIGHT_ROTATION", self.textHeight, self.textRotation)
                    setRubberText("TEXT_FONT", self.textFont)
                    setRubberText("TEXT_JUSTIFY", self.textJustify)
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

