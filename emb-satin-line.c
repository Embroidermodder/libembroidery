#include "embroidery.h"
#include <math.h>
#include <stdlib.h>

void embSatinOutline_generateSatinOutline(EmbArray *lines, double thickness, EmbSatinOutline* result)
{
    int i;
    EmbSatinOutline outline;
    double halfThickness = thickness / 2.0;
    int intermediateOutlineCount = 2 * lines->count - 2;
    embArray_create(outline.side1, EMB_VECTOR);
    if (!outline.side1) {
        embLog_error("emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for outline->side1\n");
        return;
    }
    embArray_create(outline.side2, EMB_VECTOR);
    if (!outline.side2) {
        embLog_error("emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for outline->side2\n");
        return;
    }

    for (i = 1; i < lines->count; i++) {
        int j = (i - 1) * 2;
        EmbVector v1;
        EmbVector temp;

        EmbLine line;
        line.x1 = lines->vector[i - 1].x;
        line.y1 = lines->vector[i - 1].y;
        line.x2 = lines->vector[i].x;
        line.y2 = lines->vector[i].y;

        embLine_normalVector(line, &v1, 1);

        embVector_multiply(v1, halfThickness, &temp);
        embVector_add(temp, lines->vector[i - 1], &temp);
        embArray_addVector(outline.side1, temp);
        embVector_add(temp, lines->vector[i], &temp);
        embArray_addVector(outline.side1, temp);

        embVector_multiply(v1, -halfThickness, &temp);
        embVector_add(temp, lines->vector[i - 1], &temp);
        embArray_addVector(outline.side2, temp);
        embVector_add(temp, lines->vector[i], &temp);
        embArray_addVector(outline.side2, temp);
    }

    if (!result) {
        embLog_error("emb-satin-line.c embSatinOutline_generateSatinOutline(), result argument is null\n");
        return;
    }
    embArray_create(result->side1, EMB_VECTOR);
    if (!result->side1) {
        embLog_error("emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side1\n");
        return;
    }
    embArray_create(result->side2, EMB_VECTOR);
    if (!result->side2) {
        embLog_error("emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side2\n");
        return;
    }

    embArray_addVector(result->side1, outline.side1->vector[0]);
    embArray_addVector(result->side2, outline.side2->vector[0]);

    EmbLine line1, line2;
    EmbVector out;
    for (i = 3; i < intermediateOutlineCount; i += 2) {
        line1.x1 = outline.side1->vector[i - 3].x;
        line1.y1 = outline.side1->vector[i - 3].y;
        line1.x2 = outline.side1->vector[i - 2].x;
        line1.y2 = outline.side1->vector[i - 2].y;
        line2.x1 = outline.side1->vector[i - 1].x;
        line2.y1 = outline.side1->vector[i - 1].y;
        line2.x2 = outline.side1->vector[i].x;
        line2.y2 = outline.side1->vector[i].y;
        embLine_intersectionPoint(line1, line2, &out);
        embArray_addVector(result->side1, out);

        line1.x1 = outline.side2->vector[i - 3].x;
        line1.y1 = outline.side2->vector[i - 3].y;
        line1.x2 = outline.side2->vector[i - 2].x;
        line1.y2 = outline.side2->vector[i - 2].y;
        line2.x1 = outline.side2->vector[i - 1].x;
        line2.y1 = outline.side2->vector[i - 1].y;
        line2.x2 = outline.side2->vector[i].x;
        line2.y2 = outline.side2->vector[i].y;
        embLine_intersectionPoint(line1, line2, &out);
        embArray_addVector(result->side2, out);
    }

    embArray_addVector(result->side1, outline.side1->vector[2 * lines->count - 3]);
    embArray_addVector(result->side2, outline.side2->vector[2 * lines->count - 3]);
    result->length = lines->count;
}

EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, double density)
{
    int i, j;
    EmbVector currTop, currBottom, topDiff, bottomDiff, midDiff;
    EmbVector midLeft, midRight, topStep, bottomStep;
    EmbArray* stitches = 0;

    if (!result) {
        embLog_error("emb-satin-line.c embSatinOutline_renderStitches(), result argument is null\n");
        return 0;
    }

    if (result->length > 0) {
        for (j = 0; j < result->length - 1; j++) {
            embVector_subtract(result->side1->vector[j+1], result->side1->vector[j], &topDiff);
            embVector_subtract(result->side2->vector[j+1], result->side2->vector[j], &bottomDiff);

            embVector_average(result->side1->vector[j], result->side2->vector[j], &midLeft);
            embVector_average(result->side1->vector[j+1], result->side2->vector[j+1], &midRight);

            embVector_subtract(midLeft, midRight, &midDiff);
            double midLength = embVector_getLength(midDiff);

            int numberOfSteps = (int)(midLength * density / 200);
            embVector_multiply(topDiff, 1.0/numberOfSteps, &topStep);
            embVector_multiply(bottomDiff, 1.0/numberOfSteps, &bottomStep);
            currTop = result->side1->vector[j];
            currBottom = result->side2->vector[j];

            for (i = 0; i < numberOfSteps; i++) {
                if (!stitches) {
                    embArray_create(stitches, EMB_VECTOR);
                }
                embArray_addVector(stitches, currTop);
                embArray_addVector(stitches, currBottom);
                embVector_add(currTop, topStep, &currTop);
                embVector_add(currBottom, bottomStep, &currBottom);
            }
        }
        embArray_addVector(stitches, currTop);
        embArray_addVector(stitches, currBottom);
    }
    return stitches;
}

