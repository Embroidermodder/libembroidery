#include <math.h>

#include "embroidery.h"

extern EmbReal epsilon;

/* Create an EmbVector from data. */
EmbVector emb_vector(EmbReal x, EmbReal y)
{
    EmbVector v;
    v.x = x;
    v.y = y;
    return v;
}

/* Print the vector "v2 with the name "label". */
void emb_vector_print(EmbVector v, int8_t *label)
{
    printf("%sX = %f\n", label, v.x);
    printf("%sY = %f\n", label, v.y);
}

/* Finds the unit length vector a result in the same direction as a vector. */
EmbVector emb_vector_normalize(EmbVector vector)
{
    EmbVector result;
    EmbReal length = emb_vector_length(vector);
    result.x = vector.x / length;
    result.y = vector.y / length;
    return result;
}

/* The scalar multiple a magnitude of a vector. Returned as a vector. */
EmbVector emb_vector_scale(EmbVector vector, EmbReal magnitude)
{
    EmbVector result;
    result.x = vector.x * magnitude;
    result.y = vector.y * magnitude;
    return result;
}

/* The sum of two vectors returned as a vector. */
EmbVector emb_vector_add(EmbVector a, EmbVector b)
{
    EmbVector result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

/* The average of two vectors returned as a vector. */
EmbVector emb_vector_average(EmbVector a, EmbVector b)
{
    EmbVector result;
    result.x = 0.5 * (a.x + b.x);
    result.y = 0.5 * (a.y + b.y);
    return result;
}

/* The difference between two vectors returned as a result. */
EmbVector emb_vector_subtract(EmbVector v1, EmbVector v2)
{
    EmbVector result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    return result;
}

/* The dot product of two vectors returned as a EmbReal. */
EmbReal emb_vector_dot(EmbVector a, EmbVector b)
{
    return a.x * b.x + a.y * b.y;
}

/*
 * The "cross product" as vectors a and b returned as a real value.
 *
 * Technically, this is the magnitude of the cross product when the
 * embroidery is placed in the z=0 plane (since the cross product is defined for
 * 3-dimensional vectors).
 */
EmbReal emb_vector_cross(EmbVector a, EmbVector b)
{
    return a.x * b.y - a.y * b.x;
}

/*
 * Since we aren't using full 3D vector algebra here, all vectors are "vertical".
 * so this is like the product v1^{T} I_{2} v2 for our vectors a v1 and v2
 * so a "component-wise product". The result is stored at the pointer a result.
 */
EmbVector emb_vector_transpose_product(EmbVector v1, EmbVector v2)
{
    EmbVector result;
    result.x = v1.x * v2.x;
    result.y = v1.y * v2.y;
    return result;
}

/* The length or absolute value of the vector a vector. */
EmbReal emb_vector_length(EmbVector vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

/* The x-component of the vector. */
EmbReal emb_vector_relativeX(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    b = emb_vector_subtract(a1, a2);
    c = emb_vector_subtract(a3, a2);
    return emb_vector_dot(b, c);
}

/* The y-component of the vector. */
EmbReal emb_vector_relativeY(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    b = emb_vector_subtract(a1, a2);
    c = emb_vector_subtract(a3, a2);
    return emb_vector_cross(b, c);
}

/* The angle, measured anti-clockwise from the x-axis, of a vector v. */
EmbReal emb_vector_angle(EmbVector v)
{
    return atan2(v.y, v.x);
}

/* The unit vector in the direction a angle. */
EmbVector emb_vector_unit(EmbReal alpha)
{
    EmbVector a;
    a.x = cos(alpha);
    a.y = sin(alpha);
    return a;
}

/* The distance between vectors "a" and "b" returned as a real value. */
EmbReal emb_vector_distance(EmbVector a, EmbVector b)
{
    EmbVector delta = emb_vector_subtract(a, b);
    return emb_vector_length(delta);
}

/* Approximate equals for vectors. */
int emb_approx(EmbVector point1, EmbVector point2)
{
    return (emb_vector_distance(point1, point2) < epsilon);
}

