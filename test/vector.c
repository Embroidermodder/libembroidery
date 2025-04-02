/*
 * Testing
 */

#include <string.h>
#include <math.h>

#include "../src/embroidery.h"

void emb_vector_print(EmbVector v, char *label);

int test_vadd(EmbVector v1, EmbVector v2, EmbVector result, EmbReal tolerence);
int test_vsubtract(EmbVector v1, EmbVector v2, EmbVector result,
    EmbReal tolerence);

int
main(void)
{
    float epsilon = 0.0000000001;
    EmbVector v1 = emb_vector(1.6, 3.21);
    EmbVector v2 = emb_vector(1.64, 3.11);
    EmbVector result_add = emb_vector(3.24, 6.32);

    if (!test_vadd(v1, v2, result_add, epsilon)) {
        return 1;
    }

    return 0;
}

/* . */
int
test_vadd(EmbVector v1, EmbVector v2, EmbVector result, EmbReal tolerence)
{
    EmbVector testResult = emb_vector_add(v1, v2);
    double xerror = fabs(testResult.x - result.x);
    double yerror = fabs(testResult.y - result.y);
    printf("errors: %f %f\n", xerror, yerror);
    if (tolerence < xerror) {
        printf("Error calculating vector sum.\n");
        return 1;
    }
    if (tolerence < yerror) {
        printf("Error calculating vector sum.\n");
        return 1;
    }
    return 0;
}

/* . */
int
test_vsubtract(EmbVector v1, EmbVector v2, EmbVector result, EmbReal tolerence)
{
    EmbVector testResult = emb_vector_subtract(v1, v2);
    double xerror = fabs(testResult.x - result.x);
    double yerror = fabs(testResult.y - result.y);
    printf("errors: %f %f\n", xerror, yerror);
    if (tolerence < xerror) {
        printf("Error calculating vector sum.\n");
        return 1;
    }
    if (tolerence < yerror) {
        printf("Error calculating vector sum.\n");
        return 1;
    }
    return 0;
}
