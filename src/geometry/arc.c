/*
 * ARC GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../embroidery.h"

/* Returns an EmbArcObject. It is created on the stack. */
EmbArc
embArc_init(void)
{
    EmbArc arc;
    arc.start.x = 0.0;
    arc.start.y = 0.0;
    arc.mid.x = 1.0;
    arc.mid.y = 1.0;
    arc.end.x = 2.0;
    arc.end.y = 2.0;
    arc.lineType = 0;
    arc.color = black_thread.color;
    return arc;
}

/* Calculus based approach at determining whether a polygon is clockwise or counterclockwise.
 * Returns true if arc is clockwise. */
char
embArc_clockwise(EmbArc arc)
{
    EmbReal edge1 = (arc.mid.x-arc.start.x)*(arc.mid.y+arc.start.y);
    EmbReal edge2 = (arc.end.x-arc.mid.x)*(arc.end.y+arc.mid.y);
    EmbReal edge3 = (arc.start.x-arc.end.x)*(arc.start.y+arc.end.y);
    if (edge1 + edge2 + edge3 >= 0.0) {
        return 1;
    }
    return 0;
}


/* Calculates the CenterPoint of the Arc */
void
getArcCenter(EmbArc arc, EmbVector* arcCenter)
{
    EmbVector a_vec, b_vec, aMid_vec, bMid_vec, aPerp_vec, bPerp_vec, pa, pb;
    EmbLine line1, line2;
    EmbReal paAngleInRadians, pbAngleInRadians;
    embVector_subtract(arc.mid, arc.start, &a_vec);
    embVector_average(arc.mid, arc.start, &aMid_vec);

    paAngleInRadians = embVector_angle(a_vec) + radians(90.0);
    pa = embVector_unit(paAngleInRadians);
    embVector_add(aMid_vec, pa, &aPerp_vec);

    embVector_subtract(arc.end, arc.mid, &b_vec);
    embVector_average(arc.end, arc.mid, &bMid_vec);

    pbAngleInRadians = embVector_angle(b_vec) + radians(90.0);
    pb = embVector_unit(pbAngleInRadians);
    embVector_add(bMid_vec, pb, &bPerp_vec);

    line1.start = aMid_vec;
    line1.end = aPerp_vec;
    line2.start = bMid_vec;
    line2.end = bPerp_vec;
    *arcCenter = embLine_intersectionPoint(line1, line2);
    if (emb_error) {
        puts("ERROR: no intersection, cannot find arcCenter.");
    }
}

/* Calculates Arc Geometry from Bulge Data.
 * Returns false if there was an error calculating the data. */
char
getArcDataFromBulge(EmbReal bulge,
                         EmbArc *arc,
                         EmbReal* arcCenterX,        EmbReal* arcCenterY,
                         EmbReal* radius,            EmbReal* diameter,
                         EmbReal* chord,
                         EmbReal* chordMidX,         EmbReal* chordMidY,
                         EmbReal* sagitta,           EmbReal* apothem,
                         EmbReal* incAngleInDegrees, char*   clockwise)
{
    EmbReal incAngleInRadians;
    EmbReal chordAngleInRadians;
    EmbReal sagittaAngleInRadians;
    EmbReal fx ,fy, dx, dy;
    EmbVector arcCenter;

    /* Confirm the direction of the Bulge */
    if (bulge >= 0.0) { 
        *clockwise = 0;
    } else { 
        *clockwise = 1;
    }

    /* Calculate the Included Angle in Radians */
    incAngleInRadians = atan(bulge)*4.0;

    /* Calculate the Chord */
    dx = arc->end.x - arc->start.x;
    dy = arc->end.y - arc->start.y;
    *chord = sqrt(dx*dx + dy*dy);

    /* Calculate the Radius */
    *radius = fabs(*chord / (2.0 * sin(incAngleInRadians / 2.0)));

    /* Calculate the Diameter */
    *diameter = fabs(*radius * 2.0);

    /* Calculate the Sagitta */
    *sagitta = fabs((*chord / 2.0) * bulge);

    /* Calculate the Apothem */
    *apothem = fabs(*radius - *sagitta);

    /* Calculate the Chord MidPoint */
    *chordMidX = (arc->start.x + arc->end.x) / 2.0;
    *chordMidY = (arc->start.y + arc->end.y) / 2.0;

    /* Calculate the Chord Angle (from arcStart to arcEnd) */
    chordAngleInRadians = atan2(dy, dx);

    /* Calculate the Sagitta Angle (from chordMid to arcMid) */
    if (*clockwise) sagittaAngleInRadians = chordAngleInRadians + radians(90.0);
    else           sagittaAngleInRadians = chordAngleInRadians - radians(90.0);

    /* Calculate the Arc MidPoint */
    fx = *sagitta * cos(sagittaAngleInRadians);
    fy = *sagitta * sin(sagittaAngleInRadians);
    arc->mid.x = *chordMidX + fx;
    arc->mid.y = *chordMidY + fy;

    getArcCenter(*arc, &arcCenter);
    *arcCenterX = arcCenter.x;
    *arcCenterY = arcCenter.y;

    /* Convert the Included Angle from Radians to Degrees */
    *incAngleInDegrees = degrees(incAngleInRadians);

    /* Confirm the direction of the Arc, it should match the Bulge */
    if (*clockwise != embArc_clockwise(*arc)) {
        fprintf(stderr, "Arc and Bulge direction do not match.\n");
        return 0;
    }

    return 1;
}
