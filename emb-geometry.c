#include "embroidery.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const double embConstantPi = 3.1415926535;

/* Returns an EmbArcObject. It is created on the stack. */
EmbArcObject embArcObject_make(double sx, double sy, double mx, double my, double ex, double ey)
{
    EmbArcObject stackArcObj;
    stackArcObj.arc.startX = sx;
    stackArcObj.arc.startY = sy;
    stackArcObj.arc.midX   = mx;
    stackArcObj.arc.midY   = my;
    stackArcObj.arc.endX   = ex;
    stackArcObj.arc.endY   = ey;
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
    double edge1 = (arc.midX-arc.startX)*(arc.midY+arc.startY);
    double edge2 = (arc.endX-arc.midX)*(arc.endY+arc.midY);
    double edge3 = (arc.startX-arc.endX)*(arc.startY+arc.endY);
    if (edge1 + edge2 + edge3 >= 0.0) {
        return 1;
    }
    return 0;
}

/* Calculates the CenterPoint of the Arc */
void getArcCenter(EmbArc arc, EmbVector* arcCenter)
{
    double ax = arc.midX - arc.startX;
    double ay = arc.midY - arc.startY;
    double aAngleInRadians = atan2(ay, ax);
    double aMidX = (arc.midX + arc.startX)/2.0;
    double aMidY = (arc.midY + arc.startY)/2.0;

    double paAngleInRadians = aAngleInRadians + radians(90.0);
    double pax = cos(paAngleInRadians);
    double pay = sin(paAngleInRadians);
    double aPerpX = aMidX + pax;
    double aPerpY = aMidY + pay;

    double bx = arc.endX - arc.midX;
    double by = arc.endY - arc.midY;
    double bAngleInRadians = atan2(by, bx);
    double bMidX = (arc.endX + arc.midX)/2.0;
    double bMidY = (arc.endY + arc.midY)/2.0;

    double pbAngleInRadians = bAngleInRadians + radians(90.0);
    double pbx = cos(pbAngleInRadians);
    double pby = sin(pbAngleInRadians);
    double bPerpX = bMidX + pbx;
    double bPerpY = bMidY + pby;

    EmbLine line1;
    EmbLine line2;
    line1 = embLine_make(aMidX, aMidY, aPerpX, aPerpY);
    line2 = embLine_make(bMidX, bMidY, bPerpX, bPerpY);
    embLine_intersectionPoint(line1, line2, arcCenter);
}

/* Calculates Arc Geometry from Bulge Data.
 * Returns false if there was an error calculating the data. */
char getArcDataFromBulge(double bulge,
                         double arcStartX,          double arcStartY,
                         double arcEndX,            double arcEndY,
                         /* returned data */
                         double* arcMidX,           double* arcMidY,
                         double* arcCenterX,        double* arcCenterY,
                         double* radius,            double* diameter,
                         double* chord,
                         double* chordMidX,         double* chordMidY,
                         double* sagitta,           double* apothem,
                         double* incAngleInDegrees, char*   clockwise)
{
    double incAngleInRadians;
    double chordAngleInRadians;
    double sagittaAngleInRadians;
    double w, h, fx ,fy, dx, dy;
    EmbArc arc;
    EmbVector arcCenter;

    /* Confirm the direction of the Bulge */
    if(bulge >= 0.0) { *clockwise = 0; }
    else             { *clockwise = 1; }

    /* Calculate the Included Angle in Radians */
    incAngleInRadians = atan(bulge)*4.0;

    /* Calculate the Chord */
    w = fabs(arcStartX-arcEndX);
    h = fabs(arcStartY-arcEndY);
    *chord = sqrt(w*w + h*h);

    /* Calculate the Radius */
    *radius = fabs(*chord / (2.0 * sin(incAngleInRadians / 2.0)));

    /* Calculate the Diameter */
    *diameter = fabs(*radius * 2.0);

    /* Calculate the Sagitta */
    *sagitta = fabs((*chord / 2.0) * bulge);

    /* Calculate the Apothem */
    *apothem = fabs(*radius - *sagitta);

    /* Calculate the Chord MidPoint */
    *chordMidX = (arcStartX + arcEndX) / 2.0;
    *chordMidY = (arcStartY + arcEndY) / 2.0;

    /* Calculate the Chord Angle (from arcStart to arcEnd) */
    dx = arcEndX - arcStartX;
    dy = arcEndY - arcStartY;
    chordAngleInRadians = atan2(dy, dx);

    /* Calculate the Sagitta Angle (from chordMid to arcMid) */
    if(*clockwise) sagittaAngleInRadians = chordAngleInRadians + radians(90.0);
    else           sagittaAngleInRadians = chordAngleInRadians - radians(90.0);

    /* Calculate the Arc MidPoint */
    fx = *sagitta * cos(sagittaAngleInRadians);
    fy = *sagitta * sin(sagittaAngleInRadians);
    *arcMidX = *chordMidX + fx;
    *arcMidY = *chordMidY + fy;

    arc.startX = arcStartX;
    arc.startY = arcStartY;
    arc.midX = *arcMidX;
    arc.midY = *arcMidY;
    arc.endX = arcEndX;
    arc.endY = arcEndY;
    getArcCenter(arc, &arcCenter);
    *arcCenterX = arcCenter.x;
    *arcCenterY = arcCenter.y;

    /* Convert the Included Angle from Radians to Degrees */
    *incAngleInDegrees = degrees(incAngleInRadians);

    /* Confirm the direction of the Arc, it should match the Bulge */
    if (*clockwise != isArcClockwise(arc)) {
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
int getCircleCircleIntersections(EmbCircle c0, EmbCircle c1,
                                 /* Intersection Point */
                                 double* px3, double* py3,
                                 /* Intersection Point */
                                 double* px4, double* py4)
{
    double a, h, px2, py2, mx, my;
    double dx = c1.centerX-c0.centerX;
    double dy = c1.centerY-c0.centerY;
    double d = sqrt(dx*dx + dy*dy); /* Distance between centers */

    /*Circles share centers. This results in division by zero,
      infinite solutions or one circle being contained within the other. */
    if(d == 0.0)
        return 0;
    /* Circles do not touch each other */
    else if(d > (c0.radius + c1.radius))
        return 0;
    /* One circle is contained within the other */
    else if(d < (c0.radius - c1.radius))
        return 0;

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
    px2 = c0.centerX + (dx * a/d);
    py2 = c0.centerY + (dy * a/d);

    /* Tangent circles have only one intersection

       TODO: using == in floating point arithmetic
       doesn't account for the machine accuracy, having
       a stated (double) tolerence value would help.
    */
    if(d == (c0.radius + c1.radius))
    {
        *px3 = *py4 = px2;
        *py3 = *py4 = py2;
        return 1;
    }

    /* Get the perpendicular slope by multiplying by the negative reciprocal
     * Then multiply by the h offset in relation to d to get the actual offsets */
    mx = -(dy * h/d);
    my =  (dx * h/d);

    /* Add the offsets to point p2 to obtain the intersection points */
    *px3 = px2 + mx;
    *py3 = py2 + my;
    *px4 = px2 - mx;
    *py4 = py2 - my;

    return 1;
}

/****************************************************************
 * Calculates the tangent points on circle from a given point.
 * Returns true if the given point lies outside the circle.
 * Returns false if the given point is inside the circle.
 ****************************************************************/
int getCircleTangentPoints(EmbCircle c,
                           /* Point to determine tangency */
                           double  px,  double  py,
                           /* Tangent Point 0 */
                           double* tx0, double* ty0,
                           /* Tangent Point 1 */
                           double* tx1, double* ty1)
{
    double pr;
    double dx  = px-c.centerX;
    double dy  = py-c.centerY;
    double hyp = sqrt(dx*dx + dy*dy); /* Distance to center of circle */
	EmbCircle p;
    /* Point is inside the circle */
    if (hyp < c.radius)
        return 0;
    /* Point is lies on the circle, so there is only one tangent point */
    else if(hyp == c.centerY)
    {
        *tx0 = *tx1 = px;
        *ty0 = *ty1 = py;
        return 1;
    }

    /* Since the tangent lines are always perpendicular to the radius, so
     * we can use the Pythagorean theorem to solve for the missing side */
    pr = sqrt((hyp*hyp) - (c.radius*c.radius));

    p.centerX = px;
    p.centerY = py;
   	p.radius = pr;
    return getCircleCircleIntersections(c, p,
                                        tx0, ty0,
                                        tx1, ty1);
}

double embEllipse_diameterX(EmbEllipse ellipse)
{
    return ellipse.radiusX * 2.0;
}

double embEllipse_diameterY(EmbEllipse ellipse)
{
    return ellipse.radiusY * 2.0;
}

double embEllipse_width(EmbEllipse ellipse)
{
    return ellipse.radiusX * 2.0;
}

double embEllipse_height(EmbEllipse ellipse)
{
    return ellipse.radiusY * 2.0;
}

/* Returns an EmbEllipseObject. It is created on the stack. */
EmbEllipseObject embEllipseObject_make(double cx, double cy, double rx, double ry)
{
    EmbEllipseObject stackEllipseObj;
    stackEllipseObj.ellipse.centerX = cx;
    stackEllipseObj.ellipse.centerY = cy;
    stackEllipseObj.ellipse.radiusX = rx;
    stackEllipseObj.ellipse.radiusY = ry;
    return stackEllipseObj;
}

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
    double length = embVector_getLength(vector);

    if (!result) {
        embLog_error("emb-vector.c embVector_normalize(), result argument is null\n");
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
        embLog_error("emb-vector.c embVector_multiply(), result argument is null\n");
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
        embLog_error("emb-vector.c embVector_add(), result argument is null\n");
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
        embLog_error("emb-vector.c embVector_add(), result argument is null\n");
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
        embLog_error("emb-vector.c embVector_subtract(), result argument is null\n");
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
 * Since we aren't using full vector algebra here, all vectors are "vertical".
 * so this is like the product v1^{T} I_{2} v2 for our vectors \a v1 and \v2
 * so a "component-wise product". The result is stored at the pointer \a result.
 *
 * That is
 *      (1 0) (a) = (xa)
 * (x y)(0 1) (b)   (yb)
 */
void embVector_transpose_product(EmbVector v1, EmbVector v2, EmbVector* result)
{
    if (!result) {
        embLog_error("emb-vector.c embVector_transpose_product(), result argument is null\n");
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

