#include "embroidery.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const double embConstantPi = 3.1415926535;

/* Returns an EmbArcObject. It is created on the stack. */
EmbArcObject embArcObject_make(EmbVector s, EmbVector m, EmbVector e)
{
    EmbArcObject stackArcObj;
    stackArcObj.arc.start = s;
    stackArcObj.arc.mid = m;
    stackArcObj.arc.end = e;
    return stackArcObj;
}

double radians(double degree)
{
    return degree*embConstantPi/180.0;
}

double degrees(double radian)
{
    return radian*180.0/embConstantPi;
}

/* Calculus based approach at determining whether a polygon is clockwise or counterclockwise.
 * Returns true if arc is clockwise. */
char isArcClockwise(EmbArc arc)
{
    double edge1 = (arc.mid.x-arc.start.x)*(arc.mid.y+arc.start.y);
    double edge2 = (arc.end.x-arc.mid.x)*(arc.end.y+arc.mid.y);
    double edge3 = (arc.start.x-arc.end.x)*(arc.start.y+arc.end.y);
    if (edge1 + edge2 + edge3 >= 0.0) {
        return 1;
    }
    return 0;
}

/* Calculates the CenterPoint of the Arc */
void getArcCenter(EmbArc arc, EmbVector* arcCenter)
{
    EmbVector a, b, pa, pb;
    EmbLine line1, line2;
    embVector_subtract(arc.mid, arc.start, &a);
    embVector_average(arc.mid, arc.start, &(line1.start));
    embVector_normalVector(a, &pa, 0);
    embVector_add(line1.start, pa, &(line1.end));

    embVector_subtract(arc.end, arc.mid, &b);
    embVector_average(arc.end, arc.mid, &(line2.start));
    embVector_normalVector(b, &pb, 0);
    embVector_add(line2.start, pb, &(line2.end));

    embLine_intersectionPoint(line1, line2, arcCenter);
}

/* Calculates Arc Geometry from Bulge Data.
 * Returns false if there was an error calculating the data. */
char getArcDataFromBulge(double bulge, EmbArc *arc, EmbVector* arcCenter,
                         double* radius, double* diameter, double* chord,
                         EmbVector* chordMid,
                         double* sagitta, double* apothem,
                         double* incAngleInDegrees, char* clockwise)
{
    EmbVector f, diff;
    double incAngleInRadians;
    double chordAngleInRadians;
    double sagittaAngleInRadians;

    if (bulge >= 0.0) {
        *clockwise = 0;
    }
    else {
        *clockwise = 1;
    }

    /* Calculate the Included Angle in Radians */
    incAngleInRadians = atan(bulge)*4.0;

    embVector_subtract(arc->end, arc->start, &diff);
    *chord = embVector_getLength(diff);

    *radius = fabs(*chord / (2.0 * sin(incAngleInRadians / 2.0)));
    *diameter = *radius * 2.0;
    *sagitta = fabs((*chord / 2.0) * bulge);
    *apothem = fabs(*radius - *sagitta);

    embVector_average(arc->start, arc->end, chordMid);

    chordAngleInRadians = atan2(diff.y, diff.x);

    if (*clockwise) {
        sagittaAngleInRadians = chordAngleInRadians + radians(90.0);
    }
    else {
        sagittaAngleInRadians = chordAngleInRadians - radians(90.0);
    }

    f.x = *sagitta * cos(sagittaAngleInRadians);
    f.y = *sagitta * sin(sagittaAngleInRadians);
    embVector_add(*chordMid, f, &(arc->mid));

    getArcCenter(*arc, arcCenter);

    *incAngleInDegrees = degrees(incAngleInRadians);

    /* Confirm the direction of the Arc, it should match the Bulge */
    if (*clockwise != isArcClockwise(*arc)) {
        fprintf(stderr, "Arc and Bulge direction do not match.\n");
        return 0;
    }

    return 1;
}

/* Computational Geometry for Circles */

/****************************************************************
 * Calculates the intersection points of two overlapping circles.
 * Returns true if the circles intersect.
 * Returns false if the circles do not intersect.
 ****************************************************************/
int getCircleCircleIntersections(EmbCircle c0, EmbCircle c1, EmbVector* p3, EmbVector* p4)
{
    EmbVector diff, p2, m;
    double a, h, d;
    embVector_subtract(c1.center, c0.center, &diff);
    d = embVector_getLength(diff); /* Distance between centers */

    /*Circles share centers. This results in division by zero,
      infinite solutions or one circle being contained within the other. */
    if (d == 0.0) {
        return 0;
    }
    /* Circles do not touch each other */
    else if(d > (c0.radius + c1.radius)) {
        return 0;
    }
    /* One circle is contained within the other */
    else if(d < (c0.radius - c1.radius)) {
        return 0;
    }

    /*
     * Considering the two right triangles p0p2p3 and p1p2p3 we can write:
     * a^2 + h^2 = r0^2 and b^2 + h^2 = r1^2
     *
     * BEGIN PROOF
     *
     * Remove h^2 from the equation by setting them equal to themselves:
     *     r0^2 - a^2 = r1^2 - b^2
     * Substitute b with (d - a) since it is proven that d = a + b:
     *     r0^2 - a^2 = r1^2 - (d - a)^2
     * Complete the square:
     *     r0^2 - a^2 = r1^2 - (d^2 -2da + a^2)
     * Subtract r1^2 from both sides:
     *     r0^2 - r1^2 - a^2 = -(d^2 -2da + a^2)
     * Invert the signs:
     *     r0^2 - r1^2 - a^2 = -d^2 + 2da - a^2
     * Adding a^2 to each side cancels them out:
     *     r0^2 - r1^2 = -d^2 + 2da
     * Add d^2 to both sides to shift it to the other side:
     *     r0^2 - r1^2 + d^2 = 2da
     * Divide by 2d to finally solve for a:
     *     a = (r0^2 - r1^2 + d^2)/ (2d)
     *
     * END PROOF
     */

    a = ((c0.radius*c0.radius) - (c1.radius*c1.radius) + (d*d)) / (2.0 * d);
    /* Solve for h by substituting a into a^2 + h^2 = r0^2 */
    h = sqrt((c0.radius*c0.radius) - (a*a));

    /*Find point p2 by adding the a offset in relation to line d to point p0 */

    embVector_multiply(diff, a/d, &p2);
    embVector_add(c0.center, p2, &p2);

    /* Tangent circles have only one intersection

       TODO: using == in floating point arithmetic
       doesn't account for the machine accuracy, having
       a stated (double) tolerence value would help.
    */
    if (d == (c0.radius + c1.radius)) {
        *p3 = *p4 = p2;
        return 1;
    }

    /* Get the perpendicular slope by multiplying by the negative reciprocal
     * Then multiply by the h offset in relation to d to get the actual offsets */
    m.x = -(diff.y * h/d);
    m.y =  (diff.x * h/d);

    /* Add the offsets to point p2 to obtain the intersection points */
    embVector_add(p2, m, p3);
    embVector_subtract(p2, m, p4);

    return 1;
}

/****************************************************************
 * Calculates the tangent points on circle from a given point.
 * Returns true if the given point lies outside the circle.
 * Returns false if the given point is inside the circle.
 ****************************************************************/
int getCircleTangentPoints(EmbCircle c, EmbVector point, EmbVector* t0, EmbVector* t1)
{
    EmbCircle p;
    EmbVector diff;
    double hyp;
    embVector_subtract(point, c.center, &diff);
    hyp = embVector_getLength(diff); /* Distance to center of circle */

    /* Point is inside the circle */
    if (hyp < c.radius) {
        return 0;
    }
    /* Point is lies on the circle, so there is only one tangent point */
    else if (hyp == c.center.y) {
        *t0 = *t1 = point;
        return 1;
    }

    /* Since the tangent lines are always perpendicular to the radius, so
     * we can use the Pythagorean theorem to solve for the missing side */
    p.radius = sqrt((hyp*hyp) - (c.radius*c.radius));
    p.center = point;
    return getCircleCircleIntersections(c, p, t0, t1);
}

double embEllipse_diameterX(EmbEllipse ellipse)
{
    return ellipse.radius.x * 2.0;
}

double embEllipse_diameterY(EmbEllipse ellipse)
{
    return ellipse.radius.y * 2.0;
}

double embEllipse_width(EmbEllipse ellipse)
{
    return ellipse.radius.x * 2.0;
}

double embEllipse_height(EmbEllipse ellipse)
{
    return ellipse.radius.y * 2.0;
}

/* Returns an EmbEllipseObject. It is created on the stack. */
EmbEllipseObject embEllipseObject_make(EmbVector c, EmbVector r)
{
    EmbEllipseObject stackEllipseObj;
    stackEllipseObj.ellipse.center = c;
    stackEllipseObj.ellipse.radius = r;
    return stackEllipseObj;
}

/* Returns an EmbLine. It is created on the stack. */
EmbLine embLine_make(EmbVector start, EmbVector end)
{
    EmbLine line;
    line.start = start;
    line.end = end;
    return line;
}

void embVector_normalVector(EmbVector dir, EmbVector* result, int clockwise)
{
    double temp;
    embVector_normalize(dir, result);
    temp = result->x;
    result->x = result->y;
    result->y = -temp;
    if (!clockwise) {
        embVector_multiply(*result, -1.0, result);
    }
}

/*! Finds the normalized vector perpendicular (clockwise) to the line
 * given by v1->v2 (normal to the line) */
void embLine_normalVector(EmbLine line, EmbVector* result, int clockwise)
{
    if (!result) {
        embLog("ERROR: emb-line.c embLine_normalVector(), result argument is null\n");
        return;
    }
    embVector_subtract(line.end, line.end, result);
    embVector_normalVector(*result, result, clockwise);
}

/**
 * Finds the intersection of two lines given by v1->v2 and v3->v4
 * and sets the value in the result variable.
 */
unsigned char embLine_intersectionPoint(EmbLine line1, EmbLine line2, EmbVector* result)
{
    EmbVector D1, D2, C;
    double tolerence, det;
    tolerence = 1e-10;
    embVector_subtract(line1.end, line1.start, &D2);
    C.y = embVector_cross(line1.start, D2);

    embVector_subtract(line2.end, line2.start, &D1);
    C.x = embVector_cross(line2.start, D1);

    det = embVector_cross(D1, D2);

    if (!result) {
        embLog("ERROR: emb-line.c embLine_intersectionPoint(), result argument is null\n");
        return 0;
    }
    /*TODO: The code below needs revised since division by zero can still occur */
    if (fabs(det) < tolerence) {
        embLog("ERROR: Intersecting lines cannot be parallel.\n");
        return 0;
    }
    result->x = D2.x * C.x - D1.x * C.y;
    result->y = D2.y * C.x - D1.y * C.y;
    embVector_multiply(*result, 1.0/det, result);
    return 1;
}

double embRect_x(EmbRect rect)
{
    return rect.left;
}

double embRect_y(EmbRect rect)
{
    return rect.top;
}

double embRect_width(EmbRect rect)
{
    return rect.right - rect.left;
}

double embRect_height(EmbRect rect)
{
    return rect.bottom - rect.top;
}

/* Sets the left edge of the rect to x. The right edge is not modified. */
void embRect_setX(EmbRect* rect, double x)
{
    rect->left = x;
}

/* Sets the top edge of the rect to y. The bottom edge is not modified. */
void embRect_setY(EmbRect* rect, double y)
{
    rect->top = y;
}

/* Sets the width of the rect to w. The right edge is modified. The left edge is not modified. */
void embRect_setWidth(EmbRect* rect, double w)
{
    rect->right = rect->left + w;
}

/* Sets the height of the rect to h. The bottom edge is modified. The top edge is not modified. */
void embRect_setHeight(EmbRect* rect, double h)
{
    rect->bottom = rect->top + h;
}

void embRect_setCoords(EmbRect* rect, double x1, double y1, double x2, double y2)
{
    rect->left = x1;
    rect->top = y1;
    rect->right = x2;
    rect->bottom = y2;
}

void embRect_setRect(EmbRect* rect, double x, double y, double w, double h)
{
    rect->left = x;
    rect->top = y;
    rect->right = x + w;
    rect->bottom = y + h;
}

/* Returns an EmbRectObject. It is created on the stack. */
EmbRectObject embRectObject_make(double x, double y, double w, double h)
{
    EmbRectObject stackRectObj;
    stackRectObj.rect.left = x;
    stackRectObj.rect.top = y;
    stackRectObj.rect.right = x + w;
    stackRectObj.rect.bottom = y + h;
    return stackRectObj;
}

/**
 * Finds the unit length vector \a result in the same direction as \a vector.
 */
void embVector_normalize(EmbVector vector, EmbVector* result)
{
    double length;
    length = embVector_getLength(vector);

    if (!result) {
        embLog("ERROR: emb-vector.c embVector_normalize(), result argument is null\n");
        return;
    }
    result->x = vector.x / length;
    result->y = vector.y / length;
}

/**
 * The scalar multiple \a magnatude of a vector \a vector. Returned as
 * \a result.
 */
void embVector_multiply(EmbVector vector, double magnitude, EmbVector* result)
{
    if (!result) {
        embLog("ERROR: emb-vector.c embVector_multiply(), result argument is null\n");
        return;
    }
    result->x = vector.x * magnitude;
    result->y = vector.y * magnitude;
}

/**
 * The sum of vectors \a v1 and \a v2 returned as \a result.
 */
void embVector_add(EmbVector v1, EmbVector v2, EmbVector* result)
{
    if (!result) {
        embLog("ERROR: emb-vector.c embVector_add(), result argument is null\n");
        return;
    }
    result->x = v1.x + v2.x;
    result->y = v1.y + v2.y;
}

/**
 * The average of vectors \a v1 and \a v2 returned as \a result.
 */
void embVector_average(EmbVector v1, EmbVector v2, EmbVector* result)
{
    if (!result) {
        embLog("ERROR: emb-vector.c embVector_add(), result argument is null\n");
        return;
    }
    result->x = (v1.x + v2.x) / 2.0;
    result->y = (v1.y + v2.y) / 2.0;
}

/**
 * The difference between vectors \a v1 and \a v2 returned as \a result.
 */
void embVector_subtract(EmbVector v1, EmbVector v2, EmbVector* result)
{
    if (!result) {
        embLog("ERROR: emb-vector.c embVector_subtract(), result argument is null\n");
        return;
    }
    result->x = v1.x - v2.x;
    result->y = v1.y - v2.y;
}

/**
 * The dot product as vectors \a v1 and \a v2 returned as a double.
 *
 * That is
 * (x)   (a) = xa+yb
 * (y) . (b)
 */
double embVector_dot(EmbVector v1, EmbVector v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

/**
 * The Euclidean distance between points v1 and v2, aka |v2-v1|.
 */
double embVector_distance(EmbVector v1, EmbVector v2)
{
    EmbVector v3;
    embVector_subtract(v1, v2, &v3);
    return sqrt(embVector_dot(v3, v3));
}


/**
 * Since we aren't using full vector algebra here, all vectors are "vertical".
 * so this is like the product v1^{T} I_{2} v2 for our vectors \a v1 and \v2
 * so a "component-wise product". The result is stored at the pointer \a result.
 *
 * That is
 *      (1 0) (a) = (xa)
 * (x y)(0 1) (b)   (yb)
 */
void embVector_transposeProduct(EmbVector v1, EmbVector v2, EmbVector* result)
{
    if (!result) {
        embLog("ERROR: emb-vector.c embVector_transpose_product(), result argument is null\n");
        return;
    }
    result->x = v1.x * v2.x;
    result->y = v1.y * v2.y;
}

/**
 * The length or absolute value of the vector \a vector. 
 */
double embVector_getLength(EmbVector vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

/**
 * The length or absolute value of the vector \a vector. 
 */
double embVector_cross(EmbVector a, EmbVector b)
{
    return a.x * b.y - a.y * b.x;
}

