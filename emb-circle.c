#include "emb-circle.h"
#include "emb-logging.h"
#include <stdlib.h>
#include <math.h>

/**************************************************/
/* EmbCircle                                      */
/**************************************************/

double embCircle_centerX(EmbCircle circle)
{
    return circle.centerX;
}

double embCircle_centerY(EmbCircle circle)
{
    return circle.centerY;
}

double embCircle_radius(EmbCircle circle)
{
    return circle.radius;
}

/**************************************************/
/* EmbCircleObject                                */
/**************************************************/

/* Returns an EmbCircleObject. It is created on the stack. */
EmbCircleObject embCircleObject_make(double cx, double cy, double r)
{
    EmbCircleObject stackCircleObj;
    stackCircleObj.circle.centerX = cx;
    stackCircleObj.circle.centerY = cy;
    stackCircleObj.circle.radius  = r;
    return stackCircleObj;
}

/* Returns a pointer to an EmbCircleObject. It is created on the heap. The caller is responsible for freeing the allocated memory. */
EmbCircleObject* embCircleObject_create(double cx, double cy, double r)
{
    EmbCircleObject* heapCircleObj = (EmbCircleObject*)malloc(sizeof(EmbCircleObject));
    if(!heapCircleObj) { embLog_error("emb-circle.c embCircleObject_create(), cannot allocate memory for heapCircleObj\n"); return 0; }
    heapCircleObj->circle.centerX = cx;
    heapCircleObj->circle.centerY = cy;
    heapCircleObj->circle.radius  = r;
    return heapCircleObj;
}

/**************************************************/
/* EmbCircleObjectList                            */
/**************************************************/

EmbCircleObjectList* embCircleObjectList_create(EmbCircleObject data)
{
    EmbCircleObjectList* heapCircleObjList = (EmbCircleObjectList*)malloc(sizeof(EmbCircleObjectList));
    if(!heapCircleObjList) { embLog_error("emb-circle.c embCircleObjectList_create(), cannot allocate memory for heapCircleObjList\n"); return 0; }
    heapCircleObjList->circleObj = data;
    heapCircleObjList->next = 0;
    return heapCircleObjList;
}

EmbCircleObjectList* embCircleObjectList_add(EmbCircleObjectList* pointer, EmbCircleObject data)
{
    if(!pointer) { embLog_error("emb-circle.c embCircleObjectList_add(), pointer argument is null\n"); return 0; }
    if(pointer->next) { embLog_error("emb-circle.c embCircleObjectList_add(), pointer->next should be null\n"); return 0; }
    pointer->next = (EmbCircleObjectList*)malloc(sizeof(EmbCircleObjectList));
    if(!pointer->next) { embLog_error("emb-circle.c embCircleObjectList_add(), cannot allocate memory for pointer->next\n"); return 0; }
    pointer = pointer->next;
    pointer->circleObj = data;
    pointer->next = 0;
    return pointer;
}

int embCircleObjectList_count(EmbCircleObjectList* pointer)
{
    int i = 1;
    if(!pointer) return 0;
    while(pointer->next)
    {
        pointer = pointer->next;
        i++;
    }
    return i;
}

int embCircleObjectList_empty(EmbCircleObjectList* pointer)
{
    if(!pointer)
        return 1;
    return 0;
}

void embCircleObjectList_free(EmbCircleObjectList* pointer)
{
    EmbCircleObjectList* tempPointer = pointer;
    EmbCircleObjectList* nextPointer = 0;
    while(tempPointer)
    {
        nextPointer = tempPointer->next;
        free(tempPointer);
        tempPointer = nextPointer;
    }
    pointer = 0;
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

    EmbCircle p = {px, py, pr};
    return getCircleCircleIntersections(c, p,
                                        tx0, ty0,
                                        tx1, ty1);
}

