/*
 * VECTOR ALGEBRA
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../embroidery.h"

/**
 * Finds the unit length vector \a result in the same direction as \a vector.
 */
void
embVector_normalize(EmbVector vector, EmbVector* result)
{
    EmbReal length = embVector_length(vector);

    if (!result) {
        printf("ERROR: emb-vector.c embVector_normalize(), result argument is null\n");
        return;
    }
    result->x = vector.x / length;
    result->y = vector.y / length;
}

/**
 * The scalar multiple \a magnitude of a vector \a vector. Returned as
 * \a result.
 */
void
embVector_multiply(EmbVector vector, EmbReal magnitude, EmbVector* result)
{
    if (!result) {
        printf("ERROR: emb-vector.c embVector_multiply(), result argument is null\n");
        return;
    }
    result->x = vector.x * magnitude;
    result->y = vector.y * magnitude;
}

/**
 * The sum of vectors \a v1 and \a v2 returned as a vector.
 */
EmbVector
embVector_add(EmbVector v1, EmbVector v2)
{
    EmbVector result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    return result;
}

/**
 * The average of vectors \a v1 and \a v2 returned as a vector.
 */
EmbVector
embVector_average(EmbVector v1, EmbVector v2)
{
    EmbVector result;
    result.x = 0.5*(v1.x + v2.x);
    result.y = 0.5*(v1.y + v2.y);
    return result;
}

/**
 * The difference between vectors \a v1 and \a v2 returned as \a result.
 */
EmbVector
embVector_subtract(EmbVector v1, EmbVector v2)
{
    EmbVector result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    return result;
}

/**
 * The dot product as vectors \a v1 and \a v2 returned as a EmbReal.
 *
 * That is
 * (x)   (a) = xa+yb
 * (y) . (b)
 */
float
embVector_dot(EmbVector v1, EmbVector v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

/**
 * The "cross product" as vectors \a v1 and \a v2 returned as a float.
 * Technically, this is one component only of a cross product, but in
 * our 2 dimensional framework we can use this as a scalar rather than
 * a vector in calculations.
 *
 * (a) x (c) = ad-bc
 * (b)   (d)
 */
float
embVector_cross(EmbVector v1, EmbVector v2)
{
    return v1.x * v2.y - v1.y * v2.x;
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
void
embVector_transpose_product(EmbVector v1, EmbVector v2, EmbVector* result)
{
    if (!result) {
        printf("ERROR: emb-vector.c embVector_transpose_product(), result argument is null\n");
        return;
    }
    result->x = v1.x * v2.x;
    result->y = v1.y * v2.y;
}

/**
 * The length or absolute value of the vector \a vector. 
 */
float
embVector_length(EmbVector vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

/*
 *  
 */
float
embVector_relativeX(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    b = embVector_subtract(a1, a2);
    c = embVector_subtract(a3, a2);
    return embVector_dot(b, c);
}

/*
 *  
 */
float
embVector_relativeY(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    b = embVector_subtract(a1, a2);
    c = embVector_subtract(a3, a2);
    return embVector_cross(b, c);
}

/*
 * The angle, measured anti-clockwise from the x-axis, of a vector v.
 */
float
embVector_angle(EmbVector v)
{
    return atan2(v.y, v.x);
}

/*
 *  
 */
EmbVector
embVector_unit(float angle)
{
    EmbVector a;
    a.x = cos(angle);
    a.y = sin(angle);
    return a;
}

/*
 *  
 */
float
embVector_distance(EmbVector p, EmbVector q)
{
    EmbVector delta = embVector_subtract(p, q);
    return embVector_length(delta);
}
