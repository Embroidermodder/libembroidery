#include <math.h>

#include "embroidery.h"

/* Finds the normalized vector perpendicular (clockwise) to the line
 * given by v1->v2 (normal to the line) */
EmbVector emb_line_normal(EmbLine line, int clockwise)
{
    EmbVector result;
    EmbReal temp;
    result = emb_vector_subtract(line.end, line.start);
    result = emb_vector_normalize(result);
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
EmbVector emb_line_toVector(EmbLine line)
{
    return emb_vector_subtract(line.end, line.start);
}

/*
 * Finds the intersection of two lines given by v1->v2 and v3->v4
 * and sets the value in the result variable.
 */
EmbVector
emb_line_intersection(EmbLine line1, EmbLine line2, int *emb_error)
{
    EmbReal det, C2, C1, tolerance;
    EmbVector vec1, vec2, result;
    *emb_error = 0;
    vec1 = emb_line_toVector(line1);
    vec2 = emb_line_toVector(line2);
    C2 = emb_vector_cross(line1.start, vec1);
    C1 = emb_vector_cross(line2.start, vec2);

    tolerance = 1e-10;
    det = emb_vector_cross(vec2, vec1);

    if (fabs(det) < tolerance) {
        /* Default to the origin when an error is thrown. */
        *emb_error = 1;
        result.x = 0.0;
        result.y = 0.0;
        return result;
    }
    result.x = (vec2.x * C2 - vec1.x * C1) / det;
    result.y = (vec2.y * C2 - vec1.y * C1) / det;
    return result;
}
