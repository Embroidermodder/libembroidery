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
 *
 * Equivalent to:
 *
 * \f[
 *       \mathbf{u} = \frac{v}{|\mathbf{v}|}
 * \f]
 *
 * \todo make result return argument.
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
 *
 * \todo make result return argument.
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
 * The sum of vectors \a a and \a b returned as a vector.
 *
 * Equivalent to:
 *
 * \f[
 *       \mathbf{c} = \mathbf{a} + \mathbf{b}
 *                  = \begin{pmatrix} a_{x} + b_{x} \\ a_{y}+b_{y} \end{pmatrix}
 * \f]
 */
EmbVector
embVector_add(EmbVector a, EmbVector b)
{
    EmbVector result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

/**
 * The average of vectors \a v1 and \a v2 returned as a vector.
 *
 * Equivalent to:
 *
 * \f[
 *       \mathbf{c} = \frac{\mathbf{a} + \mathbf{b}}{2}
 *                  = \begin{pmatrix} \frac{a_{x} + b_{x}}{2} \\ \frac{a_{y}+b_{y}}{2} \end{pmatrix}
 * \f]
 */
EmbVector
embVector_average(EmbVector a, EmbVector b)
{
    EmbVector result;
    result.x = 0.5*(a.x + b.x);
    result.y = 0.5*(a.y + b.y);
    return result;
}

/**
 * The difference between vectors \a v1 and \a v2 returned as \a result.
 *
 * Equivalent to:
 *
 * \f[
 *       \mathbf{c} = \mathbf{a} - \mathbf{b}
 *                  = \begin{pmatrix} a_{x} - b_{x} \\ a_{y}-b_{y} \end{pmatrix}
 * \f]
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
 * Equivalent to:
 *
 * \f[
 *       c = \mathbf{a} \cdot \mathbf{b}
 *         = a_x b_x + a_y b_y
 * \f]
 */
EmbReal
embVector_dot(EmbVector a, EmbVector b)
{
    return a.x * b.x + a.y * b.y;
}

/**
 * @brief The "cross product" as vectors \a a and \a b returned as a real value.
 *
 * Technically, this is the magnitude of the cross product when the
 * embroidery is placed in the z=0 plane (since the cross product is defined for
 * 3-dimensional vectors). That is:
 *
 * \f[
 *       |c| = \left| \begin{pmatrix} a_x \\ a_y \\ 0 \end{pmatrix} \times \begin{pmatrix} b_x \\ b_y \\ 0 \end{pmatrix}\right|
 *           = \left| \begin{pmatrix} 0 \\ 0 \\ a_x b_y - a_y b_x \end{pmatrix} \right|
 *           = a_x b_y - a_y b_x
 * \f]
 */
EmbReal
embVector_cross(EmbVector a, EmbVector b)
{
    return a.x * b.y - a.y * b.x;
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
 *
 * Equivalent to:
 *
 * \f[
 *       |v| = \sqrt{v_{x}^{2} + v_{y}^{2}}
 * \f]
 */
EmbReal
embVector_length(EmbVector vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

/**
 * The x-component of the vector 
 */
EmbReal
embVector_relativeX(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    b = embVector_subtract(a1, a2);
    c = embVector_subtract(a3, a2);
    return embVector_dot(b, c);
}

/**
 * The y-component of the vector 
 */
EmbReal
embVector_relativeY(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    b = embVector_subtract(a1, a2);
    c = embVector_subtract(a3, a2);
    return embVector_cross(b, c);
}

/**
 * The angle, measured anti-clockwise from the x-axis, of a vector v.
 */
EmbReal
embVector_angle(EmbVector v)
{
    return atan2(v.y, v.x);
}

/**
 * The unit vector in the direction \a angle.
 *
 * \f[
 *       \mathbf{a}_{\alpha} = \begin{pmatrix} \cos(\alpha) \\ \sin(\alpha) \end{pmatrix}
 * \f]
 */
EmbVector
embVector_unit(EmbReal alpha)
{
    EmbVector a;
    a.x = cos(alpha);
    a.y = sin(alpha);
    return a;
}

/**
 * The distance between \a a and \a b returned as a real value.
 *
 * \f[
 *      d = \left|\mathbf{a}-\mathbf{b}\right|
 *        = \sqrt{(a_x-b_x)^{2} + (a_y-b_y)^{2}}
 * \f]
 */
EmbReal
embVector_distance(EmbVector a, EmbVector b)
{
    EmbVector delta = embVector_subtract(a, b);
    return embVector_length(delta);
}
