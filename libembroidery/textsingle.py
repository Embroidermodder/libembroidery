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
from embroidermodder.geometry.line import Line

from embroidermodder.utility import translate

class TextSingle():
    """
    def objectSavePathList() const  return subPathList()
    def subPathList() const

    objectPos()    const  return scenePos()
      objectX()  const  return scenePos().x()
      objectY()  const  return scenePos().y()

    QStringList objectTextJustifyList() const

    def setObjectText(self, str)
    def setObjectTextFont(self, font)
    def set_object_text_justify(self, justify):
        return

    def set_object_text_size(size):
        return

    def setObjectTextStyle(bold, italic, under, strike, over):
        return

    def setObjectTextBold(val):
        return

    def setObjectTextItalic(self, val):
        return

    def setObjectTextUnderline(self, val):
        return

    def setObjectTextStrikeOut(self, val):
        return

    def setObjectTextOverline(self, val):
        return

    def setObjectTextBackward(self, val):
        return

    def setObjectTextUpsideDown(self, val):
        return

    def update_rubber(QPainter* painter = 0)
    def vulcanize()
    mouse_snap_point(mouse_point)
    QList<Vector> all_grip_points()
    def grip_edit(before, after)
    def paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
    """
    def __init__(self, x, y, text="Text Single", rgb="#FFFFFF",
                 parent=0, line_type="solid", line_weight=0.35,
                 size=16.0, font="Arial", justify="Left"):
        " . "
        debug_message("TextSingleObject Constructor()")
        self.type = "Text Single"
        self.selectable = True
        self.justify = justify
        self.text = text
        self.font = font
        self.path = Path()
        self.position = Vector(x, y)
        self.pen = Pen(rgb=rgb, line_weight=line_weight, line_type=line_type)
        self.rotation = 0.0
        self.size = size
        # TODO: "Aligned", "Fit"
        self.justify_list = [
            "Left", "Center", "Right", "Middle",
            "Top Left", "Top Center", "Top Right",
            "Middle Left", "Middle Center", "Middle Right",
            "Bottom Left", "Bottom Center", "Bottom Right"
        ]

    def copy(self, parent):
        " . "
        debug_message("TextSingleObject Constructor()")
        obj_copy = TextSingle(
            text=self.obj_text,
            font=self.font,
            scale=self.scale,
            x=self.x,
            y=self.y,
            rgb=self.rgb,
            rotation=self.rotation,
            line_type=self.line_type)
        return obj_copy

    def set_text(self):
        " . "
        objText = str
        text_path = Path()
        font = Font()
        font.setFamily(objTextFont)
        font.setPointSizeF(obj_text.size)
        font.setBold(obj_text.bold)
        font.setItalic(obj_text.italic)
        font.setUnderline(obj_text.underline)
        font.setStrikeOut(obj_text.strikeout)
        font.setOverline(obj_text.overline)
        text_path.addText(0, 0, font, str)

        # Translate the path based on the justification.
        jRect = text_path.boundingRect()
        if self.justify == "Left":
            text_path.translate(-jRect.left(), 0)
        elif self.justify == "Center":
            text_path.translate(-jRect.center().x(), 0)
        elif self.justify == "Right":
            text_path.translate(-jRect.right(), 0)
        elif self.justify == "Aligned":
            # TODO: TextSingleObject Aligned Justification
            todo(".")
        elif self.justify == "Middle":
            text_path.translate(-jRect.center())
        elif self.justify == "Fit":
            todo("TODO: TextSingleObject Fit Justification.")
        elif self.justify == "Top Left":
            text_path.translate(-jRect.top_left())
        elif self.justify == "Top Center":
            text_path.translate(-jRect.center().x(), -jRect.top())
        elif self.justify == "Top Right":
            text_path.translate(-jRect.top_right())
        elif self.justify == "Middle Left":
            text_path.translate(-jRect.left(), -jRect.top()/2.0)
        elif self.justify == "Middle Center":
            text_path.translate(-jRect.center().x(), -jRect.top()/2.0)
        elif self.justify == "Middle Right":
            text_path.translate(-jRect.right(), -jRect.top()/2.0)
        elif self.justify == "Bottom Left":
            text_path.translate(-jRect.bottom_left())
        elif self.justify == "Bottom Center":
            text_path.translate(-jRect.center().x(), -jRect.bottom())
        elif self.justify == "Bottom Right":
            text_path.translate(-jRect.bottom_right())

        # Backward or Upside Down
        if self.backward or self.upsidedown:
            horiz = 1.0
            vert = 1.0
            if self.backward:
                horiz = -1.0
            if self.upsidedown:
                vert = -1.0

            flipped_path = Path()

            element = 0
            P2 = 0
            P3 = 0
            P4 = 0
            for i in range(text_path.element_count()):
                element = text_path.element_at(i)
                if element.ismove_to():
                    flipped_path.move_to(horiz * element.x, vert * element.y)

                elif element.isline_to():
                    flipped_path.line_to(horiz * element.x, vert * element.y)

                elif element.isCurveTo():
                    # start point P1 is not needed
                    P2 = text_path.element_at(i)
                    # control point
                    P3 = text_path.element_at(i+1)
                    # control point
                    P4 = text_path.element_at(i+2)
                    # end point

                    flipped_path.cubicTo(horiz * P2.x, vert * P2.y,
                                        horiz * P3.x, vert * P3.y,
                                        horiz * P4.x, vert * P4.y)


            objTextPath = flipped_path

        else:
            objTextPath = text_path

        # Add the grip point to the shape path
        grip_path = objTextPath
        grip_path.connect_path(objTextPath)
        grip_path.add_rect(-0.00000001, -0.00000001, 0.00000002, 0.00000002)
        setObjectPath(grip_path)

    def set_font(self, font):
        " . "
        self.font = font
        setObjectText(objText)

    def set_object_text_justify(self, justify):
        " Verify the string is a valid option. "
        if justify in self.justify_list:
            self.justify = justify
        else:
            # Default
            self.justify = "Left"
        setObjectText(objText)

    def set_object_text_size(size):
        " . "
        obj_text.size = size
        setObjectText(objText)

    def setObjectTextBold(self, val):
        " . "
        obj_text.bold = val
        setObjectText(objText)

    def setObjectTextItalic(self, val):
        " . "
        obj_text.italic = val
        setObjectText(objText)

    def setObjectTextUnderline(self, val):
        " . "
        obj_text.underline = val
        setObjectText(objText)

    def setObjectTextStrikeOut(self, val):
        " . "
        obj_text.strikeout = val
        setObjectText(objText)

    def setObjectTextOverline(self, val):
        " . "
        obj_text.overline = val
        setObjectText(objText)

    def setObjectTextBackward(self, val):
        " . "
        obj_text.backward = val
        setObjectText(objText)

    def setObjectTextUpsideDown(self, val):
        " . "
        obj_text.upsidedown = val
        setObjectText(objText)

    def paint(self, painter, option, widget):
        obj_scene = scene()
        if not obj_scene:
            return

        paintPen = Pen()
        painter.set_pen(paintPen)
        update_rubber(painter)
        if "QStyle_State_Selected" in option.state:
            paintPen.set_style(Qt_DashLine)
        if obj_scene.property("ENABLE_LWT").toBool():
            paintPen = lineWeightPen()
        painter.set_pen(paintPen)

        painter.drawPath(objTextPath)

    def update_rubber(self, painter):
        if self.rubber_mode == "TEXTSINGLE":
            set_font(objectRubberText("TEXT_FONT"))
            set_object_text_justify(objectRubberText("TEXT_JUSTIFY"))
            setObjectPos(objectRubberPoint("TEXT_POINT"))
            hr = objectRubberPoint("TEXT_HEIGHT_ROTATION")
            set_object_text_size(hr.x())
            setRotation(hr.y())
            setObjectText(objectRubberText("TEXT_RAPID"))

        elif self.rubber_mode == "GRIP":
            if painter:
                gripPoint = objectRubberPoint("GRIP_POINT")
                if gripPoint == scenePos():
                    painter.drawPath(objectPath().translated(map_from_scene(objectRubberPoint(""))-map_from_scene(gripPoint)))

                rubLine = Line(map_from_scene(gripPoint), map_from_scene(objectRubberPoint("")))
                drawRubberLine(rubLine, painter, "VIEW_COLOR_CROSSHAIR")

    def vulcanize():
        debug_message("TextSingleObject vulcanize()")
        self.update_rubber()

        self.rubber_mode = "OFF"

    def mouse_snap_point(self, mouse_point):
        " Returns the closest snap point to the mouse point. "
        return scenePos()

    def all_grip_points():
        gripPoints = [scenePos()]
        return gripPoints

    def grip_edit(before, after):
        if before == scenePos():
            delta = after-before
            moveBy(delta.x(), delta.y())

    def sub_path_list(self):
        s = self.scale
        trans = 0
        trans.rotate(self.rotation)
        trans.scale(s,s)

        path_list = []
        path = objTextPath
        pathMoves = []
        numMoves = 0

        for i in range(path.element_count()):
            element = path.element_at(i)
            if element.ismove_to():
                pathMoves += [i]
                numMoves += 1

        pathMoves += [path.element_count()]

        for p in range(pathMoves.size()-1):
            #if p => numMoves:
            #    break
            for i in range(pathMoves.value(p), pathMoves.value(p+1)):
                element = path.element_at(i)
                if element.ismove_to():
                    subPath.move_to(element.x, element.y)

                elif element.isline_to():
                    subPath.line_to(element.x, element.y)

                elif element.isCurveTo():
                    # control point 1, 2, end point
                    subPath.cubicTo(
                        path.element_at(i).x, path.element_at(i).y,
                        path.element_at(i+1).x, path.element_at(i+1).y,
                        path.element_at(i+2).x, path.element_at(i+2).y
                    )

            path_list.append(trans.map(subPath))

        return path_list
