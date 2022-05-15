#!/usr/bin/env python3

r"""
    Embroidermodder 2.

    ------------------------------------------------------------

    Copyright 2013-2022 The Embroidermodder Team
    Embroidermodder 2 is Open Source Software.
    See LICENSE for licensing terms.

    ------------------------------------------------------------

"""

from math import radians, degrees

from embroidermodder.geometry.path import Path
from embroidermodder.geometry.tools import Pen, Vector, closest_vector
from embroidermodder.geometry.line import Line

from embroidermodder.utility import debug_message


class Arc():
    r"""
    The Arc class definition.
    """
    def __init__(self, start, mid, end,
                 pen=Pen(rgb="#FFFFFF", line_type="solid", line_weight=0.35),
                 path=Path(),
                 rotation=0.0):
        " ."
        self.pen = pen
        self.lwt_pen = pen
        self.start = start
        self.mid = mid
        self.end = end
        self.type = "Arc"
        self.rotation = rotation
        self.scale = 1.0
        self.center = Vector(0.0, 0.0)
        self.rubber_mode = "RUBBER_OFF"
        self.start_angle = 0.0
        self.end_angle = 0.0
        self.radius = 0.0
        self.path = path
        self.update()

    def update(self):
        " ."
        self.start_angle = (self.end - self.start).angle()
        self.end_angle = (self.start - self.end).angle()
        self.radius = self.get_radius()
        self.center = self.get_center()

        self.set_position(center)

        self.radius = Line(self.center, self.mid).length()
        self.update_rect(radius)
        self.updatePath()

    def center(self):
        " ."
        return self.scene_position

    def get_radius(self):
        " ."
        return Rect().width()/2.0*self.scale

    def set_start_angle(self, angle):
        " Alter the start angle. "
        self.update()

    def set_end_angle(self, angle):
        " Alter the end angle. "
        self.update()

    def set_start_point(self, point):
        " Alter the start point. "
        self.start = point
        self.update()

    def set_mid_point(self, point):
        " Alter the middle point. "
        self.mid = point
        self.update()

    def set_end_point(self, point):
        " Alter the end point. "
        self.end = point
        self.update()

    def update_rubber(self, painter):
        r"""Update the rubber points to match the current data.
        # TODO: Arc Rubber Modes
        # TODO: self.update_rubber() gripping for Arc
        """
        debug_message("Update rubber.")
        self.update()

    def copy(self):
        """
        Create a copy of the current Arc  from the perspective
        of the scene.
        """
        debug_message("Arc copy()")
        return Arc(self.start, self.mid, self.end,
            pen=self.pen, rotation=self.rotation)

    def update_rect(self, radius):
        " . "
        arc_rect = Rect()
        arc_rect.set_width(radius*2.0)
        arc_rect.set_height(radius*2.0)
        arc_rect.move_center(Vector(0,0))
        set_rect(arc_rect)

    def set_radius(self, radius):
        " . "
        self.update()

        if radius <= 0:
            radius = 0.0000001

        start_line = Line(self.center, self.start)
        mid_line = Line(self.center, self.mid)
        end_line = Line(self.center, self.end)
        start_line.set_length(radius)
        mid_line.set_length(radius)
        end_line.set_length(radius)
        self.start = start_line.p2()
        self.mid = mid_line.p2()
        self.end = end_line.p2()

        self.update()

    def start_angle(self):
        " The start angle from the perspective of the render. "
        angle = Line(self.scene_position, self.start).angle()
        return math.fmod(angle, 360.0)

    def end_angle(self):
        " The end angle from the perspective of the render. "
        angle = Line(self.scene_position, self.end).angle()
        return math.fmod(angle, 360.0)

    def start_point(self):
        " The start point from the perspective of the render. "
        rot = scale_and_rotate(self.start, self.scale, radians(self.rotation))
        return self.scene_position + rot

    def mid_point(self):
        " The mid point from the perspective of the render. "
        rot = scale_and_rotate(self.middle, self.scale, radians(self.rotation))
        return self.scene_position + rot

    def end_point(self):
        " The end point from the perspective of the render. "
        rot = scale_and_rotate(self.end, self.scale, radians(self.rotation))
        return self.scene_position + rot

    def area():
        " Area of a circular segment. "
        r = Radius()
        theta = radians(IncludedAngle())
        return ((r*r)/2)*(theta - sin(theta))

    def arc_length(self):
        " . "
        return radians(self.included_angle())*Radius()

    def chord(self):
        " . "
        return Line(self.start, self.end).length()

    def included_angle(self):
        """
        NOTE:
        Due to floating point rounding errors, we need to clamp the
        quotient so it is in the range [-1, 1].
        If the quotient is out of that range, then the result of asin()
        will be NaN.
        """
        chord = self.chord()
        rad = self.radius()
        if chord <= 0 or rad <= 0:
            return 0
        # Prevents division by zero and non-existent circles.

        quotient = chord/(2.0*rad)
        if quotient > 1.0:
            quotient = 1.0
        if quotient < 0.0:
            quotient = 0.0
        """
        NOTE: 0 rather than -1 since we are enforcing a positive chord
        and radius.
        """
        return degrees(2.0*asin(quotient))
        # Properties of a Circle - Get the Included Angle - Reference: ASD9.

    def clockwise():
        " . "
        arc = Arc(
            self.start.x, -self.start.y,
            self.mid.x, -self.mid.y,
            self.end.x, -self.end.y
        )
        # NOTE: Y values are inverted here on purpose.
        return arc.clockwise()

    def update_path(self):
        " . "
        self.update()
        self.start_angle = self.start_angle + self.rotation
        self.span_angle = self.included_angle()

        if self.clockwise():
            self.span_angle = -self.span_angle

        rect = self.bounding_rect()
        self.path = [
            ["arc_move_to", rect, self.start_angle],
            ["arc_to", rect, self.start_angle, self.span_angle],
            # NOTE: Reverse the path so that the inside area
            # isn't considered part of the arc.
            ["arc_to", rect, self.start_angle+self.span_angle, -self.span_angle]
        ]

    def paint(self, painter, option, widget):
        " . "
        obj_scene = scene()
        if not obj_scene:
            return

        paint_pen = Pen()
        painter.set_pen(paint_pen)
        self.update_rubber(painter)
        if option.state == "State_Selected":
            paint_pen.set_style("dashed")
        if obj_scene.property("ENABLE_LWT").to_bool():
            paint_pen = self.lwt_pen
        painter.set_pen(paint_pen)

        start_angle = (start_angle() + self.rotation)*16
        span_angle = self.included_angle()*16

        if self.clockwise():
            span_angle = -span_angle

        rad = self.radius()
        paint_rect = Rect(-rad, -rad, rad*2.0, rad*2.0)
        painter.draw_arc(paint_rect, start_angle, span_angle)

    def vulcanize(self):
        " . "
        debug_message("Arc vulcanize()")
        self.update_rubber()
        self.rubber_mode = "RUBBER_OFF"

    def mouse_snap_point(self, mouse_point):
        " Returns the closest snap point to the mouse point. "
        snap_points = self.all_grip_points()
        return closest_vector(snap_points, mouse_point)

    def all_grip_points(self):
        " . "
        self.update()
        return [self.center, self.start, self.mid, self.end]

    def grip_edit(self, before, after):
        " TODO: grip_edit() for Arc. "
        return
