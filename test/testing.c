/*
 * Testing
 */

#include <string.h>
#include <math.h>

#include "../src/embroidery.h"

void emb_vector_print(EmbVector v, char *label);
void emb_arc_print(EmbArc a);

int test_convert_from_to(int from_, int to_);

int test_convert_csv_svg(void);
int test_convert_csv_dst(void);
int test_create_files(void);
int test_fractal_generation(void);
int test_arc_properties(void);

/*
 * Format: the first token is the function call, the next n tokens are the
 * number required by that function then the remaining tokens are the expected
 * output up to some stated tolerence.
 */
const char *tests[] = {
    "ctangent 0.001 0.0 0.0 3.0 4.0 0.0 2.25 1.9843 2.25 -1.9843",
    "extension example.zsk .zsk",
    "description example.zsk \"ZSK USA Embroidery Format\"",
    "reader example.zsk U"
};

int test_vadd(EmbVector v1, EmbVector v2, EmbVector result, EmbReal tolerence);
int test_vsubtract(EmbVector v1, EmbVector v2, EmbVector result,
    EmbReal tolerence);
int test_ctangents(EmbGeometry c, EmbVector p, EmbVector s0, EmbVector s1,
    EmbReal tolerence);

/* Currently just crash testing. */
int
test_convert(int test_case, int from, int to)
{
    EmbString fname_from;
    EmbString fname_to;
    sprintf(fname_from, "test%02d%s", test_case, formatTable[from].extension);
    sprintf(fname_to, "test%02d_out%s", test_case, formatTable[to].extension);
    printf("Converting test case %d: %s to %s.\n",
        test_case, fname_from, fname_to);
    if (create_test_file(test_case, from)) {
        return 1;
    }
    convert(fname_from, fname_to);
    return 0;
}

int
test_create_files(void)
{
    int i;
    for (i=0; i<3; i++) {
        int result = create_test_file(0, EMB_FORMAT_CSV);
        if (result) {
            return result;
        }
    }
    return 0;
}

int
test_convert_from_to(int from_, int to_)
{
    int i;
    for (i=0; i<3; i++) {
        int result = test_convert(i, from_, to_);
        if (result) {
            return result;
        }
    }
    return 0;
}

/* . */
int
test_convert_csv_svg(void)
{
    return test_convert_from_to(EMB_FORMAT_CSV, EMB_FORMAT_SVG);
}

/* . */
int
test_convert_csv_dst(void)
{
    return test_convert_from_to(EMB_FORMAT_CSV, EMB_FORMAT_SVG);
}

int
test_fractal_generation(void)
{
    EmbPattern *pattern = emb_pattern_create();
    int hilbertCurveResult = hilbert_curve(pattern, 3);
    int renderResult = emb_pattern_render(pattern, "hilbert_level_3.png");
    int simulateResult = emb_pattern_simulate(pattern, "hilbert_level_3.avi");
    printf("hilbert curve result: %d\n", hilbertCurveResult);
    printf("render result: %d\n", renderResult);
    printf("simulate result: %d\n", simulateResult);
    emb_pattern_free(pattern);
    return hilbertCurveResult;
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

/* . */
void
printArcResults(
    EmbReal bulge,
    EmbArc arc,
    EmbVector center,
    EmbReal radius,
    EmbReal diameter,
    EmbReal chord,
    EmbVector chordMid,
    EmbReal sagitta,
    EmbReal apothem,
    EmbReal incAngle,
    char clockwise)
{
    printf("test_arc:");
    emb_arc_print(arc);
    emb_vector_print(center, "center");
    emb_vector_print(chordMid, "chordMid");
    printf(
        "bulge     = %f\n"
        "radius    = %f\n"
        "diameter  = %f\n"
        "chord     = %f\n"
        "sagitta   = %f\n"
        "apothem   = %f\n"
        "incAngle  = %f\n"
        "clockwise = %d\n"
        "\n",
        bulge,
        radius,
        diameter,
        chord,
        sagitta,
        apothem,
        incAngle,
        clockwise);
}

