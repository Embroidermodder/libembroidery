#include "embroidery.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Returns the closest color to the required color based on
 * a list of available threads. The algorithm is a simple least
 * squares search against the list. If the (square of) Euclidean 3-dimensional
 * distance between the points in (red, green, blue) space is smaller
 * then the index is saved and the remaining index is returned to the
 * caller.
 *
 * @param color  The EmbColor color to match.
 * @param colors The EmbThreadList pointer to start the search at.
 * @param mode   Is the argument an array of threads (0) or colors (1)?
 * @return closestIndex The entry in the ThreadList that matches.
 */
int embThread_findNearestColor(EmbColor color, EmbArray* a, int mode)
{
    int currentClosestValue = 256*256*3;
    int closestIndex = -1, i;
    int deltaRed, deltaBlue, deltaGreen, delta;
    EmbColor c;

    for (i=0; i<a->count; i++) {
        if (mode == 0) { /* thread mode */
            c = a->thread[i].color;
        }
        else { /* color array mode */
            c = a->color[i];
        }

        deltaRed = color.r - c.r;
        deltaBlue = color.g - c.g;
        deltaGreen = color.b - c.b;
        delta = deltaRed*deltaRed + deltaBlue*deltaBlue + deltaGreen*deltaGreen;

        if (delta <= currentClosestValue) {
            currentClosestValue = delta;
            closestIndex = i;
        }
    }
    return closestIndex;
}

int embThread_findNearestColor_fromThread(EmbColor color, const EmbThread* a, int length)
{
    int currentClosestValue = 256*256*3;
    int closestIndex = -1, i;
    int deltaRed, deltaBlue, deltaGreen, delta;
    EmbColor c;

    for (i=0; i<length; i++) {
        c = a[i].color;
        
        deltaRed = color.r - c.r;
        deltaBlue = color.g - c.g;
        deltaGreen = color.b - c.b;
        delta = deltaRed*deltaRed + deltaBlue*deltaBlue + deltaGreen*deltaGreen;

        if (delta <= currentClosestValue) {
            currentClosestValue = delta;
            closestIndex = i;
        }
    }
    return closestIndex;
}
/**
 * Returns a random thread color, useful in filling in cases where the
 * actual color of the thread doesn't matter but one needs to be declared
 * to test or render a pattern.
 *
 * @return c The resulting color.
 */
EmbThread embThread_getRandom(void)
{
    EmbThread c;
    c.color.r = rand()%256;
    c.color.g = rand()%256;
    c.color.b = rand()%256;
    c.description = "random";
    c.catalogNumber = "";
    return c;
}

