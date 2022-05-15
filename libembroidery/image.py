#!/usr/bin/env python3

r"""
    Embroidermodder 2.

    ------------------------------------------------------------

    Copyright 2013-2022 The Embroidermodder Team
    Embroidermodder 2 is Open Source Software.
    See LICENSE for licensing terms.

    ------------------------------------------------------------

"""

from embroidermodder.geometry.pen import Pen
from embroidermodder.geometry.line import Line
from embroidermodder.geometry.path import Path
from embroidermodder.geometry.rect import Rect

from embroidermodder.utility import (debug_message)


class Image():
    r"""
    The Image class definition.
    """
    def __init__(self, position, width, height, scene, fname, bg="#000000"):
        r"""
        """
        debug_message("Image Constructor()")
        self.type = "Image"
        self.selectable = True
        self.rubber_points = {}
        self.rubber_mode = "IMAGE"
        self.scene = scene
        self.position = position
        self.rect = Rect(position=self.position, size=(width, height))
        self.rgb = bg
        self.scale = 1.0
        self.rotation = 0.0
        self.pen = Pen()
        self.update_path()

    def copy(self, obj, parent):
        " . "
        debug_message("Image Constructor()")
        img = Image(self.rect.position_x, self.rect.position_y,
                    self.rect.width, self.rect.height, rgb=self.rgb,
                    line_type=self.line_type, line_weight=self.line_weight)
        img.setRotation(self.rotation())
        return img

    def area(self):
        r" Returns the area covered by the image. "
        return self.width * self.height

    def set_rect(self, position, size):
        " . "
        self.rect = Rect(position=position, size=size)
        self.update_path()

    def update_path(self):
        r""" NOTE: Reverse the path so that the inside area isn't
        considered part of the rectangle.
        """
        r = self.rect
        self.path = Path()
        self.path.move_to(r.bottom_left())
        self.path.line_to(r.bottom_right())
        self.path.line_to(r.top_right())
        self.path.line_to(r.top_left())
        self.path.line_to(r.bottom_left())
        self.path.line_to(r.top_left())
        self.path.line_to(r.top_right())
        self.path.line_to(r.bottom_right())
        self.path.move_to(r.bottom_left())

    def paint(self, painter, option, widget):
        " . "
        obj_scene = self.scene
        if not obj_scene:
            return

        paintPen = Pen()
        painter.set_pen(paintPen)
        self.update_rubber(painter)
        if "QStyle_State_Selected" in option.state:
            paintPen.set_style("dashed")
        if obj_scene.property("ENABLE_LWT").toBool():
            paintPen = self.lwt_pen()
        painter.set_pen(paintPen)

        painter.drawRect(self.rect)

    def update_rubber(self, painter):
        " . "
        if self.rubber_mode == "IMAGE":
            debug_message("IMAGE")
            scene_start_point = self.rubber_points["IMAGE_START"]
            scene_end_point = self.rubber_points["IMAGE_END"]
            x = scene_start_point.x()
            y = scene_start_point.y()
            w = scene_end_point.x() - scene_start_point.x()
            h = scene_end_point.y() - scene_start_point.y()
            self.rect = Rect(x, y, w, h)
            self.update_path()

        elif self.rubber_mode == "GRIP":
            " TODO: self.update_rubber() gripping for Image. "
            debug_message("GRIP")

    def vulcanize(self):
        " . "
        debug_message("Image vulcanize()")
        self.update_rubber()
        self.rubber_mode = "OFF"

    def mouse_snap_point(self, mouse_point):
        " Returns the closest snap point to the mouse point. "
        all_points = self.all_grip_points()
        return closest_vector(all_points, mouse_point)

    def all_grip_points(self):
        " . "
        gripPoints = [
            self.rect.top_left(),
            self.rect.top_right(),
            self.rect.bottom_left(),
            self.rect.bottom_right()
        ]
        return gripPoints

    def grip_edit(self, before, after):
        " TODO: grip_edit() for Image "
        return

    def draw(self, description):
        r"""
        This is similar to using an svg path, we can blend these systems
        later.
        int_buffer[4]
        icon = 0
        painter = 0
        QPen pen
        get_n_ints(description, int_buffer, 2)
        icon = new QPixmap(int_buffer[0], int_buffer[1])
        painter = new QPainter(icon)
        pen.setWidth(10)
        for ptr in description:
            # Other functions we can use are eraseRect, drawArc etc.
            # https://doc.qt.io/qt-5/qpainter.html
            if (strncmp(ptr, "rect", 4)==0) {
                pen.setColor(Color(QRgb(0x000000)))
                painter.set_pen(pen)
                get_n_ints(ptr+5, int_buffer, 4)
                painter.fillRect(int_buffer[0], int_buffer[1],
                    int_buffer[2], int_buffer[3], Qt_SolidPattern);

        """
        icon = ""
        return icon
