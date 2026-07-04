/*
 * EmbVector tests.
 */

#include <math.h>

#include "embroidery.h"
#include "test.h"

static EmbReal tolerence = 0.000001;

/* Test that emb_vector_add works correctly. */
int test_vadd(const int8_t *data)
{
        int8_t *ptr;
        EmbVector v1;
        EmbVector v2;
        EmbVector result;
        int error;
        ptr = get_vector(data, &v1, &error);
        ptr = get_vector(ptr, &v2, &error);
        ptr = get_vector(ptr, &result, &error);
        if (error) {
                printf("test_vadd called with %f %f %f %f %f %f\n",
                       v1.x, v1.y, v2.x, v2.y, result.x, result.y);
                printf("ERROR: Failed to parse test data \"%s\".\n", data);
                return 1;
        }
        EmbVector testResult = emb_vector_add(v1, v2);
        double xerror = fabs(testResult.x - result.x);
        double yerror = fabs(testResult.y - result.y);
        if ((tolerence < xerror) || (tolerence < yerror)) {
                printf("Error calculating vector sum with tolerence %f.\n",
                       tolerence);
                printf("errors: %f %f\n", xerror, yerror);
                return 1;
        }
        return 0;
}

/* Test that emb_vector_subtract works correctly. */
int test_vsubtract(const int8_t *data)
{
        int8_t *ptr;
        EmbVector v1;
        EmbVector v2;
        EmbVector result;
        int error = 0;
        ptr = get_vector(data, &v1, &error);
        ptr = get_vector(ptr, &v2, &error);
        ptr = get_vector(ptr, &result, &error);
        if (error) {
                printf
                    ("ERROR: Failed to parse test data \"%s %f %f %f %f %f %f\".\n",
                     data, v1.x, v1.y, v2.x, v2.y, result.x, result.y);
                return 1;
        }
        EmbVector testResult = emb_vector_subtract(v1, v2);
        double xerror = fabs(testResult.x - result.x);
        double yerror = fabs(testResult.y - result.y);
        if ((tolerence < xerror) || (tolerence < yerror)) {
                printf
                    ("Error calculating vector difference with tolerence %f.\n",
                     tolerence);
                printf("errors: %f %f\n", xerror, yerror);
                return 1;
        }
        return 0;
}

/* Test that emb_vector_subtract works correctly. */
int test_vnormalize(const int8_t *data)
{
        int8_t *ptr;
        EmbVector v;
        EmbVector result;
        int error = 0;
        ptr = get_vector(data, &v, &error);
        ptr = get_vector(ptr, &result, &error);
        if (error) {
                printf("ERROR: Failed to parse test data \"%s\".\n", data);
                return 1;
        }
        return 0;
}
