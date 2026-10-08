#include "emb-vector.h"
#include "emb-logging.h"
#include <math.h>
#include <stdlib.h>

EmbVector embVector(double x, double y)
{
    EmbVector v;
    v.X = x;
    v.Y = y;
    return v;
}

double embVector_dot(EmbVector a, EmbVector b)
{
    return a.X * b.X + a.Y * b.Y;
}

EmbVector embVector_subtract(EmbVector a, EmbVector b)
{
    return embVector(a.X - b.X, a.Y - b.Y);
}

EmbVector embVector_average(EmbVector a, EmbVector b)
{
    return embVector(0.5 * (a.X + b.X), 0.5 * (a.Y + b.Y));
}

EmbVector embVector_scale(EmbVector v, double factor)
{
    return embVector(v.X * factor, v.Y * factor);
}

EmbVector embVector_normalize(EmbVector vector)
{
    double length = embVector_getLength(vector);
    return embVector_scale(vector, 1.0 / length);
}

EmbVector embVector_add(EmbVector v1, EmbVector v2)
{
    EmbVector result;
    result.X = v1.X + v2.X;
    result.Y = v1.Y + v2.Y;
    return result;
}

double embVector_getLength(EmbVector vector)
{
    return sqrt(vector.X * vector.X + vector.Y * vector.Y);
}

EmbVectorList* embVectorList_create(EmbVector data)
{
    EmbVectorList* pointer = (EmbVectorList*)malloc(sizeof(EmbVectorList));
    if(!pointer) { embLog_error("emb-vector.c embVectorList_create(), cannot allocate memory for pointer\n"); return 0; }
    pointer->vector = data;
    pointer->next = 0;
    return pointer;
}

EmbVectorList* embVectorList_add(EmbVectorList* pointer, EmbVector data)
{
    if(!pointer) { embLog_error("emb-vector.c embVectorList_add(), pointer argument is null\n"); return 0; }
    if(pointer->next) { embLog_error("emb-vector.c embVectorList_add(), pointer->next should be null\n"); return 0; }
    pointer->next = (EmbVectorList*)malloc(sizeof(EmbVectorList));
    if(!pointer->next) { embLog_error("emb-vector.c embVectorList_add(), cannot allocate memory for pointer->next\n"); return 0; }
    pointer = pointer->next;
    pointer->vector = data;
    pointer->next = 0;
    return pointer;
}

int embVectorList_count(EmbVectorList* pointer)
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

int embVectorList_empty(EmbVectorList* pointer)
{
    if(!pointer)
        return 1;
    return 0;
}

void embVectorList_free(EmbVectorList* pointer)
{
    while(pointer)
    {
        EmbVectorList* temp = pointer;
        pointer = pointer->next;
        free(temp);
        temp = 0;
    }
}

/* kate: bom off; indent-mode cstyle; indent-width 4; replace-trailing-space-save on; */
