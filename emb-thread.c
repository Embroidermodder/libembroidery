#include "embroidery.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Returns the closest color to the required color based on
 * a list of available threads. The algorithm is a simple least
 * squares search against the list. If the Euclidean 3-dimensional
 * distance between the points in (red, green, blue) space is smaller
 * then the index is saved and the remaining index is returned to the
 * caller.
 *
 * @param color  The EmbColor color to match.
 * @param colors The EmbThreadList pointer to start the search at.
 * @return closestIndex The entry in the ThreadList that matches.
 */
int embThread_findNearestColor(EmbColor color, EmbThreadList* colors)
{
    double currentClosestValue = 9999999;
    int closestIndex = -1;
    int red = color.r;
    int green = color.g;
    int blue = color.b;
    int i = 0;
    EmbThreadList* currentThreadItem = colors;

    while(currentThreadItem != NULL)
    {
        int deltaRed;
        int deltaBlue;
        int deltaGreen;
        double dist;
        EmbColor c;
        c = currentThreadItem->thread.color;

        deltaRed = red - c.r;
        deltaBlue = green - c.g;
        deltaGreen = blue - c.b;

        dist = sqrt((double)(deltaRed * deltaRed) + (deltaBlue * deltaBlue) + (deltaGreen * deltaGreen));
        if(dist <= currentClosestValue)
        {
            currentClosestValue = dist;
            closestIndex = i;
        }
        currentThreadItem = currentThreadItem->next;
        i++;
    }
    return closestIndex;
}

/**
 * Returns the closest color to the required color based on
 * an array of available threads. The algorithm is a simple least
 * squares search against the list. If the Euclidean 3-dimensional
 * distance between the points in (red, green, blue) space is smaller
 * then the index is saved and the remaining index is returned to the
 * caller.
 *
 * This is potentially an unnecessary duplicate depending on which
 * memory model is used in general. TODO: review for which function
 * is more appropriate.
 *
 * @param color      The EmbColor color to match.
 * @param colorArray The EmbThread pointer to start the search at.
 * @param count      The length of the array as an integer.
 * @return closestIndex The entry in the ThreadList that matches.
 */
int embThread_findNearestColorInArray(EmbColor color, EmbThread* colorArray, int count)
{
    double currentClosestValue = 9999999;
    int closestIndex = -1;
    int red = color.r;
    int green = color.g;
    int blue = color.b;
    int i = 0;
    for(i = 0; i < count; i++)
    {
        int deltaRed;
        int deltaBlue;
        int deltaGreen;
        double dist;
        EmbColor c;
        c = colorArray[i].color;

        deltaRed = red - c.r;
        deltaBlue = green - c.g;
        deltaGreen = blue - c.b;

        dist = sqrt((double)(deltaRed * deltaRed) + (deltaBlue * deltaBlue) + (deltaGreen * deltaGreen));
        if(dist <= currentClosestValue)
        {
            currentClosestValue = dist;
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

EmbThreadList* embThreadList_create(EmbThread data)
{
    EmbThreadList* heapThreadList = (EmbThreadList*)malloc(sizeof(EmbThreadList));
    if(!heapThreadList) { embLog_error("emb-thread.c embThreadList_create(), cannot allocate memory for heapThreadList\n"); return 0; }
    heapThreadList->thread = data;
    heapThreadList->next = 0;
    return heapThreadList;
}

EmbThreadList* embThreadList_add(EmbThreadList* pointer, EmbThread data)
{
    if(!pointer) { embLog_error("emb-thread.c embThreadList_add(), pointer argument is null\n"); return 0; }
    if(pointer->next) { embLog_error("emb-thread.c embThreadList_add(), pointer->next should be null\n"); return 0; }
    pointer->next = (EmbThreadList*)malloc(sizeof(EmbThreadList));
    if(!pointer->next) { embLog_error("emb-thread.c embThreadList_add(), cannot allocate memory for pointer->next\n"); return 0; }
    pointer = pointer->next;
    pointer->thread = data;
    pointer->next = 0;
    return pointer;
}

EmbThread embThreadList_getAt(EmbThreadList* pointer, int num)
{
    /* TODO: pointer safety */
    int i = 0;
    for(i = 0; i < num; i++)
    {
        if(pointer->next)
        {
            pointer = pointer->next;
        }
    }
    return pointer->thread;
}

int embThreadList_count(EmbThreadList* pointer)
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

int embThreadList_empty(EmbThreadList* pointer)
{
    if(!pointer)
        return 1;
    return 0;
}

void embThreadList_free(EmbThreadList* pointer)
{
    EmbThreadList* tempPointer = pointer;
    EmbThreadList* nextPointer = 0;
    while(tempPointer)
    {
        nextPointer = tempPointer->next;
        free(tempPointer);
        tempPointer = nextPointer;
    }
    pointer = 0;
}

