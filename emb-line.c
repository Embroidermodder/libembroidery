#include "embroidery.h"
#include <stdlib.h>
#include <math.h>

/* Returns an EmbLine. It is created on the stack. */
EmbLine embLine_make(double x1, double y1, double x2, double y2)
{
    EmbLine line;
    line.x1 = x1;
    line.y1 = y1;
    line.x2 = x2;
    line.y2 = y2;
    return line;
}

/*! Finds the normalized vector perpendicular (clockwise) to the line
 * given by v1->v2 (normal to the line) */
void embLine_normalVector(EmbLine line, EmbVector* result, int clockwise)
{
    double temp;
    if (!result) {
        embLog_error("emb-line.c embLine_normalVector(), result argument is null\n");
        return;
    }
    result->x = line.x2 - line.x1;
    result->y = line.y2 - line.y1;
    embVector_normalize(*result, result);
    temp = result->x;
    result->x = result->y;
    result->y = -temp;
    if (!clockwise) {
        result->x = -result->x;
        result->y = -result->y;
    }
}

/**
 * Finds the intersection of two lines given by v1->v2 and v3->v4
 * and sets the value in the result variable.
 */
unsigned char embLine_intersectionPoint(EmbLine line1, EmbLine line2, EmbVector* result)
{
    double tolerence = 1e-10;
    double A2 = line1.y2 - line1.y1;
    double B2 = line1.x1 - line1.x2;
    double C2 = A2 * line1.x1 + B2 * line1.y1;

    double A1 = line2.y2 - line2.y1;
    double B1 = line2.x1 - line2.x2;
    double C1 = A1 * line2.x1 + B1 * line2.y1;

    double det = A1 * B2 - A2 * B1;

    if (!result) {
        embLog_error("emb-line.c embLine_intersectionPoint(), result argument is null\n");
        return 0;
    }
    /*TODO: The code below needs revised since division by zero can still occur */
    if (fabs(det) < tolerence) {
        embLog_error("Intersecting lines cannot be parallel.\n");
        return 0;
    }
    result->x = (B2 * C1 - B1 * C2) / det;
    result->y = (A1 * C2 - A2 * C1) / det;
    return 1;
}

