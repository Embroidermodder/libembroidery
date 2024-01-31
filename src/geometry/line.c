/*
 * LINE GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

/* Finds the normalized vector perpendicular (clockwise) to the line
 * given by v1->v2 (normal to the line) */
EmbVector
embLine_normalVector(EmbLine line, int clockwise)
{
    EmbVector result;
    EmbReal temp;
    result = embVector_subtract(line.end, line.start);
    result = embVector_normalize(result);
    temp = result.x;
    result.x = result.y;
    result.y = -temp;
    if (!clockwise) {
        result.x = -result.x;
        result.y = -result.y;
    }
    return result;
}

/* Returns the vector that is the same length as the line, in the same
 * direction.
 */
EmbVector
embLine_toVector(EmbLine line)
{
    return embVector_subtract(line.end, line.start);
}

/*
 * Finds the intersection of two lines given by v1->v2 and v3->v4
 * and sets the value in the result variable.
 */
EmbVector
embLine_intersectionPoint(EmbLine line1, EmbLine line2)
{
    EmbReal det, C2, C1, tolerance;
    EmbVector vec1, vec2, result;
    emb_error = 0;
    vec1 = embLine_toVector(line1);
    vec2 = embLine_toVector(line2);
    C2 = embVector_cross(line1.start, vec1);
    C1 = embVector_cross(line2.start, vec2);

    tolerance = 1e-10;
    det = embVector_cross(vec2, vec1);

    if (fabs(det) < tolerance) {
        emb_error = 1;
        return result;
    }
    result.x = (vec2.x * C2 - vec1.x * C1) / det;
    result.y = (vec2.y * C2 - vec1.y * C1) / det;
    return result;
}
