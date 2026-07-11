/*
 * Create an arc from data.
 *
 * ------------------------------------------------------------
 *
 * The EmbArc is implicitly an elliptical arc not a circular one
 * because of our need to cover all of the SVG spec. Note that
 * the circlar arcs are a subset of the elliptical arcs.
 *
 * TODO: some of these formulae may assume that the arc is circular,
 * correct for elliptic versions.
 *
 * Returns an EmbGeometry. It is created on the stack.
 *
 * Note that the default arc is the semicircular arc of the circle of radius
 * arc.
 */

#include "embroidery.h"

EmbGeometry
emb_arc(EmbReal x1, EmbReal y1, EmbReal x2, EmbReal y2, EmbReal x3, EmbReal y3)
{
    EmbGeometry g;
    g.object.arc.start = emb_vector(x1, y1);
    g.object.arc.mid = emb_vector(x2, y2);
    g.object.arc.end = emb_vector(x3, y3);
    g.type = EMB_ARC;
    return g;
}

/* Calculus based approach at determining whether a polygon is clockwise or counterclockwise.
 * Returns true if arc is clockwise.
 */
int8_t emb_arc_clockwise(EmbGeometry g)
{
    if (g.type != EMB_ARC) {
        return 0;
    }
    EmbArc arc = g.object.arc;
    EmbReal edge1 = (arc.mid.x - arc.start.x) * (arc.mid.y + arc.start.y);
    EmbReal edge2 = (arc.end.x - arc.mid.x) * (arc.end.y + arc.mid.y);
    EmbReal edge3 = (arc.start.x - arc.end.x) * (arc.start.y + arc.end.y);
    if (edge1 + edge2 + edge3 >= 0.0) {
        return 1;
    }
    return 0;
}

/* Calculates Arc Geometry from Bulge Data.
 * Returns false if there was an error calculating the data.
    Calculate the Sagitta Angle (from chordMid to arcMid)
    if (*clockwise) sagittaAngleInRadians = chordAngleInRadians + radians(90.0);
    else           sagittaAngleInRadians = chordAngleInRadians - radians(90.0);

    Calculate the Arc MidPoint
    fx = emb_arc_sagitta(arc) * cos(sagittaAngleInRadians);
    fy = emb_arc_sagitta(arc) * sin(sagittaAngleInRadians);
    arc->mid.x = *chordMidX + fx;
    arc->mid.y = *chordMidY + fy;

    Convert the Included Angle from Radians to Degrees
    *incAngleInDegrees = degrees(incAngleInRadians);

    return 1;
}
 */

/* FIXME */
EmbVector emb_arc_center(EmbArc arc, EmbError *error)
{
    int emb_error = 0;
    EmbVector center;
    EmbVector a_vec, b_vec, aMid_vec, bMid_vec, aPerp_vec,
        bPerp_vec, pa, pb;
    EmbLine line1, line2;
    EmbReal paAngleInRadians, pbAngleInRadians;
    a_vec = emb_vector_subtract(arc.mid, arc.start);
    aMid_vec = emb_vector_average(arc.mid, arc.start);

    paAngleInRadians = emb_vector_angle(a_vec) + (embConstantPi / 2.0);
    pa = emb_vector_unit(paAngleInRadians);
    aPerp_vec = emb_vector_add(aMid_vec, pa);

    b_vec = emb_vector_subtract(arc.end, arc.mid);
    bMid_vec = emb_vector_average(arc.end, arc.mid);

    pbAngleInRadians = emb_vector_angle(b_vec) + (embConstantPi / 2.0);
    pb = emb_vector_unit(pbAngleInRadians);
    bPerp_vec = emb_vector_add(bMid_vec, pb);

    line1.start = aMid_vec;
    line1.end = aPerp_vec;
    line2.start = bMid_vec;
    line2.end = bPerp_vec;
    center = emb_line_intersection(line1, line2, &emb_error);
    if (emb_error) {
        puts("ERROR: no intersection, cannot find arcCenter.");
    }
    return center;
}

EmbError emb_arc_set_center(EmbGeometry *g, EmbVector point)
{
    EmbError error = EMB_NO_ERR;
    EmbVector delta;
    EmbVector old_center = emb_arc_center(g->object.arc, &error);
    delta = emb_vector_subtract(point, old_center);
    g->object.arc.start = emb_vector_add(g->object.arc.start, delta);
    g->object.arc.mid = emb_vector_add(g->object.arc.mid, delta);
    g->object.arc.end = emb_vector_add(g->object.arc.end, delta);
    return EMB_NO_ERR;
}

/* Print the arc "arc". */
void emb_arc_print(EmbArc arc)
{
    emb_vector_print(arc.start, "start");
    emb_vector_print(arc.mid, "middle");
    emb_vector_print(arc.end, "end");
}

