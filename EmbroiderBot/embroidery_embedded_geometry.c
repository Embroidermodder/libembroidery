/*
 * EmbroiderBot
 * Copyright 2021-2022 The Embroidermodder Team
 * Distributed under the terms of the zlib license (see LICENSE).
 */

#include "embroidery_embedded.h"

/*
 * The sum of vectors \a v1 and \a v2 returned as \a result.
 *
 * (EmbVector vector, float magnitude, EmbVector* result)
 */
void embVector_add(EmbVector a, EmbVector b, EmbVector *out)
{
  out->x = a.x + b.x;
  out->y = a.y + b.y;
}

/* Finds the unit length vector \a result
 * in the same direction as \a vector.
 *
 * (EmbVector vector, EmbVector* result)
 */
void embVector_normalize(EmbVector vector, EmbVector *result)
{
  float length;
  length = embVector_getLength(vector);

  result->x = vector.x / length;
  result->y = vector.y / length;
}

/*
 * The average of vectors \a v1 and \a v2 returned as \a result.
 *
 * (EmbVector v1, EmbVector v2, EmbVector* result)
 */
void embVector_average(EmbVector v1, EmbVector v2, EmbVector *result)
{
  result->x = (v1.x+v2.x)/2.0;
  result->y = (v1.y+v2.y)/2.0;
}

/*
 * The dot product as vectors \a v1 and \a v2 returned as a float.
 *
 * That is
 * (x)   (a) = xa+yb
 * (y) . (b)
 *
 * (EmbVector v1, EmbVector v2) returns float
 */
double embVector_dot(EmbVector v1, EmbVector v2)
{
  return v1.x*v2.x + v1.y*v2.y;
}

/*
 * The Euclidean distance between points v1 and v2, aka |v2-v1|.
 *
 * (EmbVector v1, EmbVector v2) returns float
 */
double embVector_distance(EmbVector v1, EmbVector v2)
{
  EmbVector out;
  embVector_subtract(v1, v2, &out);
  return sqrt(embVector_getLength(out));
}

/*
 * Since we aren't using full 3-vector algebra here, all vectors are "vertical".
 * so this is like the product v1^{T} I_{2} v2 for our vectors \a v1 and \v2
 * so a "component-wise product". The result is stored at the pointer \a result.
 *
 * That is
 *      (1 0) (a) = (xa)
 * (x y)(0 1) (b)   (yb)
 *
 * (EmbVector v1, EmbVector v2, EmbVector* result)
 */
void embVector_component_product(EmbVector v1, EmbVector v2, EmbVector *result)
{
  result->x = v1.x * v2.x;
  result->y = v1.y * v2.y;
}

/*
 * The "cross product", i.e. the z value of the cross product where
 * the 2-vector is the first two entries of the 3-vectors of a normal
 * cross product.
 */
double embVector_cross(EmbVector v1, EmbVector v2)
{
  return v1.x*v2.y - v1.y*v2.x;
}

/*
 * The length or absolute value of the vector \a vector.
 *
 * (EmbVector vector) returns float
 */
double embVector_getLength(EmbVector a)
{
  return sqrt(a.x*a.x+a.y*a.y);
}

/*
 * The scalar multiple \a magnitude of a vector \a vector.
 * Returned as \a result.
 *
 * (EmbVector vector, float magnitude, EmbVector* result)
 */
void embVector_multiply(EmbVector a, float c, EmbVector *out)
{
  out->x = a.x*c;
  out->y = a.y*c;
}

/*
 * The difference between vectors \a v1 and \a v2 returned as \a result.
 *
 * (EmbVector v1, EmbVector v2, EmbVector* result)
 */
void embVector_subtract(EmbVector a, EmbVector b, EmbVector *out)
{
  out->x = a.x - b.x;
  out->y = a.y - b.y;
}

EmbVector unit_vector(float angle)
{
    EmbVector u;
    u.x = cos(angle);
    u.y = sin(angle);
    return u;
}

EmbVector rotate_vector(EmbVector a, float angle)
{
    EmbVector rot;
    EmbVector u = unit_vector(angle);
    rot.x = a.x*u.x - a.y*u.y;
    rot.y = a.x*u.y + a.y*u.x;
    return rot;
}

EmbVector scale_vector(EmbVector a, float scale)
{
    a.x *= scale;
    a.y *= scale;
    return a;
}

float embVector_angle(EmbVector v1)
{
  return atan2(v1.y, v1.x);
}
