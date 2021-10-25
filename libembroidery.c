#include "embroidery.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#
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

/* Returns an EmbColor. It is created on the stack. */
EmbColor embColor_make(unsigned char r, unsigned char g, unsigned char b)
{
    EmbColor stackColor;
    stackColor.r = r;
    stackColor.g = g;
    stackColor.b = b;
    return stackColor;
}

/* Returns a pointer to an EmbColor. It is created on the heap. The caller is responsible for freeing the allocated memory. */
EmbColor* embColor_create(unsigned char r, unsigned char g, unsigned char b)
{
    EmbColor* heapColor = (EmbColor*)malloc(sizeof(EmbColor));
    if(!heapColor) { embLog_error("emb-color.c embColor_create(), cannot allocate memory for heapColor\n"); return 0; }
    heapColor->r = r;
    heapColor->g = g;
    heapColor->b = b;
    return heapColor;
}

/* Converts a 6 digit hex string (I.E. "00FF00") into an EmbColor and returns it. */
EmbColor embColor_fromHexStr(char* val)
{
    EmbColor color;
    char r[3];
    char g[3];
    char b[3];

    r[0] = val[0];
    r[1] = val[1];
    r[2] = 0;

    g[0] = val[2];
    g[1] = val[3];
    g[2] = 0;

    b[0] = val[4];
    b[1] = val[5];
    b[2] = 0;

    color.r = (unsigned char)strtol(r, 0, 16);
    color.g = (unsigned char)strtol(g, 0, 16);
    color.b = (unsigned char)strtol(b, 0, 16);
    return color;
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

/* This file contains wrapper functions around Keith Pomakis' HashTable Library */

EmbHash* embHash_create(void) { return HashTableCreate(1); }
void embHash_free(EmbHash* hash) { HashTableDestroy(hash); hash = 0; }

int embHash_contains(const EmbHash* hash, const void* key) { return HashTableContainsKey(hash, key); }
int embHash_insert(EmbHash* hash, const void* key, void* value) { return HashTablePut(hash, key, value); }
void* embHash_value(const EmbHash* hash, const void* key) { return HashTableGet(hash, key); }
void embHash_remove(EmbHash* hash, const void *key) { HashTableRemove(hash, key); }
void embHash_clear(EmbHash* hash) { HashTableRemoveAll(hash); }
int embHash_empty(const EmbHash* hash) { return HashTableIsEmpty(hash); }
long embHash_count(const EmbHash* hash) { return HashTableSize(hash); }
void embHash_rehash(EmbHash* hash, long numOfBuckets) { HashTableRehash(hash, numOfBuckets); }


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

/* printf() abstraction. Uses Serial.print() on ARDUINO */
void embLog_print(const char* format, ...)
{
    /* TODO: log debug message in struct for later use */

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

/* serious errors */
void embLog_error(const char* format, ...)
{
    /* TODO: log debug message in struct for later use */

    va_list args;
    va_start(args, format);
    printf("ERROR: ");
    vprintf(format, args);
    va_end(args);
}


void husExpand(unsigned char* input, unsigned char* output, int compressedSize, int _269) {}
int husCompress(unsigned char* _266, unsigned long _inputSize, unsigned char* _267, int _269, int _235) { return 0; }
