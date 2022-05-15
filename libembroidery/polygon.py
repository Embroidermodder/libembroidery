#!/usr/bin/env python3

r"""
    Embroidermodder 2.

    ------------------------------------------------------------

    Copyright 2013-2022 The Embroidermodder Team
    Embroidermodder 2 is Open Source Software.
    See LICENSE for licensing terms.

    ------------------------------------------------------------

    The Polygon class definition file.
"""

import math

from embroidermodder.geometry.tools import Vector, Pen
from embroidermodder.geometry.line import Line
from embroidermodder.geometry.path import Path

from embroidermodder.utility import (
    set_prompt_prefix, clear_selection, translate
)


class Polygon():
    r"""
    The Polygon class definition.

    Needs to support the features available in the SVG spec.
    """
    def __init__(self, x=0, y=0, pen=Pen(), path=Path()):
        " . "
        self.x = x
        self.y = y
        self.path = path
        self.rotation = 0.0
        self.scale = 1.0
        self.type = "Polygon"
        self.selectable = True
        self.grip_index = -1
        self.pen = pen
        self.update_path(path)
        self.normal_path = Path()
        self.points = []

        # Prompt version.
        clearSelection()
        self.center = Vector(math.nan, math.nan)
        self.side1 = Vector(math.nan, math.nan)
        self.side2 = Vector(math.nan, math.nan)
        self.point_i = Vector(math.nan, math.nan)
        self.point_c = Vector(math.nan, math.nan)
        self.poly_type = "Inscribed"
        self.num_sides = 4
        self.mode = "NUM_SIDES"
        set_prompt_prefix(translate("Enter int of sides")
            + " " + str(self.num_sides) + "}: ")

    def copy(self):
        " Return a copy of the object. "
        return Polygon(x=self.x, y=self.y,
            rgb=self.pen.rgb, line_type=self.pen.line_type,
            line_weight=self.line_weight)

    def update_path(self, p):
        " . "
        self.normal_path = p
        closed_path = self.normal_path
        closed_path.close_sub_path()
        reverse_path = closed_path.toReversed()
        reverse_path.connect_path(closed_path)
        self.set_object_path(reverse_path)

    def paint(self, painter, option, widget):
        " . "
        obj_scene = Scene()
        if not obj_scene:
            return

        paint_pen = Pen()
        painter.set_pen(paint_pen)
        self.update_rubber(painter)
        if "State_Selected" in option.state:
            paint_pen.set_style("dashed")
        if obj_scene.property("ENABLE_LWT"):
            paint_pen = line_weight_pen()
        painter.set_pen(paint_pen)

        if self.normal_path.element_count():
            painter.drawPath(self.normal_path)
            zero = self.normal_path.element_at(0)
            last = self.normal_path.element_at(self.normal_path.element_count()-1)
            painter.draw_line(Vector(zero.x, zero.y), Vector(last.x, last.y))

    def update_rubber(self, painter):
        " . "
        if self.rubber_mode == "Polygon":
            setObjectPos(object_rubber_point("POLYGON_POINT_0"))

            numStr = object_rubber_text("POLYGON_NUM_POINTS")
            if numStr.isNull():
                return
            num, ok = numStr.toInt()
            if not ok:
                return

            rubber_path = Path()
            point0 = map_from_scene(object_rubber_point("POLYGON_POINT_0"))
            rubber_path.move_to(point0)
            for i in range(1, num+1):
                appendStr = "POLYGON_POINT_" + str(i)
                appendPoint = map_from_scene(object_rubber_point(appendStr))
                rubber_path.line_to(appendPoint)

            # rubber_path.line_to(0,0)
            self.update_path(rubber_path)

            # Ensure the path isn't updated until the int of points is changed again.
            set_object_rubberText("POLYGON_NUM_POINTS", "")

        elif self.rubber_mode == "Inscribe":
            self.setObjectPos(object_rubber_point("POLYGON_CENTER"))

            num_sides = object_rubber_point("POLYGON_NUM_SIDES").x()

            inscribe_point = map_from_scene(object_rubber_point("POLYGON_INSCRIBE_POINT"))
            inscribe_line = Line(Vector(0,0), inscribe_point)
            inscribe_angle = inscribe_line.angle()
            inscribe_inc = 360.0/num_sides

            if painter:
                draw_rubber_line(inscribe_line, painter, "VIEW_COLOR_CROSSHAIR")

            inscribe_path = Path()
            # First Point
            inscribe_path.move_to(inscribe_point)
            # Remaining Points
            for i in range(1, num_sides):
                inscribe_line.set_angle(inscribe_angle + inscribe_inc*i)
                inscribe_path.line_to(inscribe_line.p2())

            self.update_path(inscribe_path)

        elif self.rubber_mode == "Circumscribe":
            self.setObjectPos(object_rubber_point("POLYGON_CENTER"))

            num_sides = object_rubber_point("POLYGON_NUM_SIDES").x()

            circumscribe_point = map_from_scene(object_rubber_point("POLYGON_CIRCUMSCRIBE_POINT"))
            circumscribe_line = Line(Vector(0,0), circumscribe_point)
            circumscribe_angle = circumscribe_line.angle()
            circumscribe_inc = 360.0/num_sides

            if painter:
                draw_rubber_line(circumscribe_line, painter, "VIEW_COLOR_CROSSHAIR")

            circumscribe_path = Path()
            # First Point
            prev = Line(circumscribe_line.p2(), Vector(0,0))
            prev = prev.normal_vector()
            circumscribe_line.set_angle(circumscribe_angle + circumscribe_inc)
            perp = Line(circumscribe_line.p2(), Vector(0,0))
            perp = perp.normal_vector()
            # HACK perp.intersects(prev, &iPoint);
            iPoint = perp.p1()
            circumscribe_path.move_to(iPoint)
            # Remaining Points
            for i in range(2, num_sides+1):
                prev = perp
                circumscribe_line.set_angle(circumscribe_angle + circumscribe_inc*i)
                perp = Line(circumscribe_line.p2(), Vector(0,0))
                perp = perp.normal_vector()
                # HACK perp.intersects(prev, &iPoint);
                iPoint = perp.p1()
                circumscribe_path.line_to(iPoint)
            self.update_path(circumscribe_path)

        elif self.rubber_mode == "GRIP":
            if painter:
                elem_count = self.normal_path.element_count()
                grip_point = object_rubber_point("GRIP_POINT")
                if grip_index == -1:
                    grip_index = find_index(grip_point)
                if grip_index == -1:
                    return

                m = 0
                n = 0

                if not grip_index:
                    m = elem_count-1
                    n = 1
                elif grip_index == elem_count-1:
                    m = elem_count-2
                    n = 0
                else:
                    m = grip_index-1
                    n = grip_index+1
                em = self.normal_path.element_at(m)
                en = self.normal_path.element_at(n)
                emPoint = Vector(em.x, em.y)
                enPoint = Vector(en.x, en.y)
                painter.draw_line(emPoint, map_from_scene(object_rubber_point("")))
                painter.draw_line(enPoint, map_from_scene(object_rubber_point("")))

                rub_line = Line(map_from_scene(grip_point),
                                map_from_scene(object_rubber_point("")))
                draw_rubber_line(rub_line, painter, "VIEW_COLOR_CROSSHAIR")

    def vulcanize(self):
        " . "
        debug_message("PolygonObject vulcanize()")
        update_rubber()

        set_object_rubber_mode(OBJ_RUBBER_OFF)

        if not self.normal_path.element_count():
            label = translate("Empty Polygon Error")
            description = translate("The polygon added contains no points. The command that created this object has flawed logic.")
            critical(0, label, description)

    def mouse_snap_point(self, mouse_point):
        " Returns the closest snap point to the mouse point. "
        element = self.normal_path.element_at(0)
        closest_point = map_to_scene(Vector(element.x, element.y))
        closest_dist = Line(mouse_point, closest_point).length()
        elem_count = self.normal_path.element_count()
        for i in range(elem_count):
            element = self.normal_path.element_at(i)
            elem_point = map_to_scene(element.x, element.y)
            elem_dist = Line(mouse_point, elem_point).length()
            if elem_dist < closest_dist:
                closest_point = elem_point
                closest_dist = elem_dist

        return closest_point

    def all_grip_points(self):
        " . "
        grip_points = []
        for i in range(normal_path.element_count()):
            element = self.normal_path.element_at(i)
            grip_points += [map_to_scene(element.x, element.y)]

        return grip_points

    def find_index(self, point):
        r"Find the closest index to the supplied point."
        elem_count = self.normal_path.element_count()
        # NOTE: Points here are in item coordinates.
        item_point = map_from_scene(point)
        for i in range(elem_count):
            e = self.normal_path.element_at(i)
            elem_point = Vector(e.x, e.y)
            if item_point == elem_point:
                return i

        return -1

    def find_index_2(self, point):
        r"Find the closest index to the supplied point."
        index = -1
        max_distance = 1.0
        for i in range(len(self.points)):
            if (self.points[i].subtract(point)).length() < max_distance:
                index = i
                max_distance = (self.points[i].subtract(point)).length()
        return index

    def grip_edit(self, before, after):
        " . "
        self.grip_index = self.find_index(before)
        if self.grip_index == -1:
            return
        a_vector = map_from_scene(after)
        self.normal_path.set_element_position_at(self.grip_index, a_vector)
        self.update_path(normal_path)
        self.grip_index = -1

    def object_copy_path(self):
        " . "
        return self.normal_path

    def object_save_path(self):
        " . "
        closed_path = self.normal_path
        closed_path.close_sub_path()
        s = self.scale
        trans = 0
        trans.rotate(self.rotation)
        trans.scale(s,s)
        return trans.map(closed_path)

    def click(self, x, y):
        vector = Vector(x, y)
        if self.mode == "NUM_SIDES":
            #Do nothing, the prompt controls this.
            debug_message("NUM_SIDES mode")

        elif self.mode == "CENTER_PT":
            self.center = vector
            self.mode = "poly_type"
            append_prompt_history()
            set_prompt_prefix(translate("Specify polygon type [Inscribed in circle/Circumscribed around circle]") + " " + self.poly_type + "}: ")

        elif self.mode == "poly_type":
            #Do nothing, the prompt controls this.
            debug_message("poly_type mode")

        elif self.mode == "INSCRIBE":
            self.point_i = vector
            self.rubber_points["POLYGON_INSCRIBE_POINT"] = self.point_i
            self.vulcanize()
            append_prompt_history()

        elif self.mode == "CIRCUMSCRIBE":
            self.point_c = vector
            self.rubber_points["POLYGON_CIRCUMSCRIBE_POINT"] = self.point_c
            self.vulcanize()
            append_prompt_history()

        elif self.mode == "DISTANCE":
            # Do nothing, the prompt controls this.
            debug_message("mode DISTANCE")

        elif self.mode == "SIDE_LEN":
            todo("POLYGON", "Sidelength mode")
            debug_message("mode SIDE LEN")

    def prompt(self, cmd):
        if self.mode == "NUM_SIDES":
            if str == "" and self.num_sides >= 3 and self.num_sides <= 1024:
                set_prompt_prefix(translate("Specify center point or [Sidelength]: "))
                self.mode = "CENTER_PT"

            else:
                tmp = int(cmd)
                if math.isnan(tmp) or (not isInt(tmp)) or tmp < 3 or tmp > 1024:
                    alert(translate("Requires an integer between 3 and 1024."))
                    set_prompt_prefix(translate("Enter number of sides") + " " + self.num_sides.toString() + "}: ")

                else:
                    self.num_sides = tmp
                    set_prompt_prefix(translate("Specify center point or [Sidelength]: "))
                    self.mode = "CENTER_PT"

        elif self.mode == "CENTER_PT":
            if cmd[0] == "S" or cmd == "SIDELENGTH":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "SIDE_LEN"
                set_prompt_prefix(translate("Specify start point: "))

            else:
                vector = vector_from_str(cmd)
                if not vector:
                    alert(translate("Point or option keyword required."))
                    set_prompt_prefix(translate("Specify center point or [Sidelength]: "))

                else:
                    self.center = vector
                    self.mode = "poly_type"
                    set_prompt_prefix(translate("Specify polygon type [Inscribed in circle/Circumscribed around circle]") + " " + self.poly_type + "}: ")

        elif self.mode == "poly_type":
            if cmd == "INSCRIBED"[len(cmd)]:
                # TODO: Probably should add additional translate calls here.
                self.mode = "INSCRIBE"
                self.poly_type = "Inscribed"
                set_prompt_prefix(translate("Specify polygon corner point or [Distance]: "))
                addRubber("POLYGON")
                self.rubber_mode = "POLYGON_INSCRIBE"
                self.rubber_points["POLYGON_CENTER"] = self.find_center()
                self.rubber_points["POLYGON_NUM_SIDES"] = (self.num_sides, 0)

            elif cmd == "CIRCUMSCRIBED"[len(cmd)]:
                # TODO: Probably should add additional translate calls here.
                self.mode = "CIRCUMSCRIBE"
                self.poly_type = "Circumscribed"
                set_prompt_prefix(translate("Specify polygon side point or [Distance]: "))
                addRubber("POLYGON")
                self.rubber_mode = "POLYGON_CIRCUMSCRIBE"
                self.rubber_points["POLYGON_CENTER"] = self.find_center()
                self.rubber_points["POLYGON_NUM_SIDES"] = (self.num_sides, 0)

            elif str == "":
                if self.poly_type == "Inscribed":
                    self.mode = "INSCRIBE"
                    set_prompt_prefix(translate("Specify polygon corner point or [Distance]: "))
                    addRubber("POLYGON")
                    self.rubber_mode = "POLYGON_INSCRIBE"
                    self.rubber_points["POLYGON_CENTER"] = self.find_center()
                    self.rubber_points["POLYGON_NUM_SIDES"] = (self.num_sides, 0)

                elif self.poly_type == "Circumscribed":
                    self.mode = "CIRCUMSCRIBE"
                    set_prompt_prefix(translate("Specify polygon side point or [Distance]: "))
                    addRubber("POLYGON")
                    self.rubber_mode = "POLYGON_CIRCUMSCRIBE"
                    self.rubber_points["POLYGON_CENTER"] = self.center
                    self.rubber_points["POLYGON_NUM_SIDES"] = (self.num_sides, 0)

                else:
                    error("POLYGON", translate("Polygon type is not Inscribed or Circumscribed."))

            else:
                alert(translate("Invalid option keyword."))
                set_prompt_prefix(translate("Specify polygon type [Inscribed in circle/Circumscribed around circle]") + " " + self.poly_type + "}: ")

        elif self.mode == "INSCRIBE":
            if str == "D" or cmd == "DISTANCE":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "DISTANCE"
                set_prompt_prefix(translate("Specify distance: "))

            else:
                vector = vector_from_str(cmd)
                if not vector:
                    alert(translate("Point or option keyword required."))
                    set_prompt_prefix(translate("Specify polygon corner point or [Distance]: "))

                else:
                    self.point_i = vector
                    self.rubber_points["POLYGON_INSCRIBE_POINT"] = self.point_i
                    self.vulcanize()
                    return

        elif self.mode == "CIRCUMSCRIBE":
            if cmd[0] == "D" or cmd == "DISTANCE":
                # TODO: Probably should add additional qsTr calls here.
                self.mode = "DISTANCE"
                set_prompt_prefix(translate("Specify distance: "))
            else:
                vector = vector_from_str(cmd)
                if not vector:
                    alert(translate("Point or option keyword required."))
                    set_prompt_prefix(translate("Specify polygon side point or [Distance]: "))

                else:
                    self.point_c = vector
                    self.rubber_points["POLYGON_CIRCUMSCRIBE_POINT"] = self.point_c
                    self.vulcanize()

        elif self.mode == "DISTANCE":
            if math.isnan(cmd):
                alert(translate("Requires valid numeric distance."))
                set_prompt_prefix(translate("Specify distance: "))

            else:
                if self.poly_type == "Inscribed":
                    self.point_i.x = self.center.x
                    self.point_i.y = self.center.y + int(cmd)
                    self.rubber_points["POLYGON_INSCRIBE_POINT"] = self.point_i
                    self.vulcanize()

                elif self.poly_type == "Circumscribed":
                    self.point_c.x = self.center.x
                    self.point_c.y = self.center.y + int(cmd)
                    self.rubber_points["POLYGON_CIRCUMSCRIBE_POINT"] = self.point_c
                    self.vulcanize()

                else:
                    description = translate("Polygon type is not Inscribed or Circumscribed.")
                    error("POLYGON", description)

        elif self.mode == "SIDE_LEN":
            todo("POLYGON", "Sidelength mode")

    def find_center(self):
        r"Loop over all points and add the supplied offset."
        center = Vector(0.0, 0.0)
        for i in range(len(self.points)):
            center += self.points[i]
        return center / len(self.points)

    def translate(self, vector):
        r"Loop over all points and add the supplied offset."
        for i in range(len(self.points)):
            self.points[i] = vector + self.points[i]
