#include "embroidery.h"
#include <math.h>
#include <stdlib.h>

/**
 * Finds the unit length vector \a result in the same direction as \a vector.
 */
void embVector_normalize(EmbVector vector, EmbVector* result)
{
    double length = embVector_getLength(vector);

    if (!result) {
        printf("ERROR: emb-vector.c embVector_normalize(), result argument is null\n");
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
        printf("ERROR: emb-vector.c embVector_multiply(), result argument is null\n");
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
        printf("ERROR: emb-vector.c embVector_add(), result argument is null\n");
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
        printf("ERROR: emb-vector.c embVector_add(), result argument is null\n");
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
        printf("ERROR: emb-vector.c embVector_subtract(), result argument is null\n");
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
        printf("ERROR: emb-vector.c embVector_transpose_product(), result argument is null\n");
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

