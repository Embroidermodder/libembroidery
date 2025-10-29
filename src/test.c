/*
 * Libembroidery 1.0.0-alpha
 * https://www.libembroidery.org
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright 2018-2025 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * -----------------------------------------------------------------------------
 *
 * Only uses source from this directory or standard C libraries,
 * not including POSIX headers like unistd since this library
 * needs to support non-POSIX systems like Windows.
 *
 * -----------------------------------------------------------------------------
 *
 * The Testing System
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "embroidery.h"

/* Caller wrapper for testing: note that this assumes that the error variable
 * is called "error".
 */
#define TEST(LINE) \
    LINE; \
    if (error) { \
        return error; \
    }

int verbosity = 0;

/* Debugging output */
void emb_vector_print(EmbVector v, char *label);
void emb_arc_print(EmbArc a);

/* Test groups */
EmbError all_tests(void);
EmbError arc_tests(void);
EmbError circle_tests(void);
EmbError ellipse_tests(void);
EmbError vector_tests(void);

/* Individual tests. */
EmbError test_arc_attributes(EmbGeometry arc);
EmbError test_cross(void);
EmbError test_fill(void);
EmbError test_vadd(EmbVector v1, EmbVector v2, EmbVector result, EmbReal tolerence);
EmbError test_vsubtract(EmbVector v1, EmbVector v2, EmbVector result,
    EmbReal tolerence);
EmbError test_convert(int test_case, int from, int to);

int
main(int argc, char *argv[])
{
    if (argc == 0) {
        return all_tests();
    }
    for (int i=0; i<argc; i++) {
        EmbError error = EMB_NO_ERR;
        /* Isolating test types: each uses a fail fast approach. */
        if (strncmp(argv[i], "--arc", 20)) {
            error = arc_tests();
        }
        if (strncmp(argv[i], "--vector", 20)) {
            error = vector_tests();
        }
        if (error) {
            return error;
        }
    }
    return 0;
}

EmbError
all_tests(void)
{
    EmbError error = EMB_NO_ERR;
    TEST(error = arc_tests())
    TEST(error = circle_tests())
    TEST(error = ellipse_tests())
    TEST(error = vector_tests())
    return error;
}

/* TODO: a clockwise and a anti-clockwise test. */
EmbError
arc_tests(void)
{
    EmbError error;
    EmbGeometry g = emb_arc(1.0, 0.0, 0.0, 0.0, 2.0, 1.0);
    TEST(error = test_arc_attributes(g))

    g = emb_arc(4.0, 0.0, 0.0, 0.0, 5.0, 1.0);
    TEST(error = test_arc_attributes(g))

    return EMB_NO_ERR;
}

/*
 * Testing if all arc attributes can be created without error.
 */
EmbError
test_arc_attributes(EmbGeometry g)
{
    EmbVector center, chordMid;
    EmbReal bulge, radius, diameter, chord, sagitta, apothem, incAngle;
    unsigned char clockwise;
    EmbError error = EMB_NO_ERR;
    bulge = -0.414213562373095f;
    /* bulge = emb_arc_bulge(g); */
    TEST(center = emb_center(&g, &error))
    TEST(chord = emb_vector_length(emb_chord(&g, &error)))
    TEST(radius = emb_radius(&g, &error))
    TEST(diameter = emb_diameter(&g, &error))
/* FIXME:
    TEST(chordMid = emb_chord_mid(&g, &error))
*/
    TEST(sagitta = emb_sagitta(&g, &error))
/* FIXME:
    TEST(apothem = emb_apothem(&g, &error))
    TEST(incAngle = emb_inc_angle(&g, &error))
*/
    TEST(clockwise = emb_clockwise(&g, &error))

    printf("test_arc:");
// FIXME:    emb_arc_print(g);
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

/* Circle Tangent Test */
int
test_ctangents(EmbGeometry c, EmbVector p, EmbVector s0, EmbVector s1,
    EmbReal tolerence)
{
    EmbVector p0, p1;
    if (!getCircleTangentPoints(c.object.circle, p, &p0, &p1)) {
        printf("Error calculating tangent points.\n");
        return 1;
    }

    printf("Circle : cr=%f, cx=%f, cy=%f\n"
       "Point  : px=%f, py=%f\n"
       "Tangent: tx0=%f, ty0=%f\n"
       "Tangent: tx1=%f, ty1=%f\n\n",
       c.object.circle.radius, c.object.circle.center.x, c.object.circle.center.y,
       p.x, p.y,
       p0.x, p0.y,
       p1.x, p1.y);

    double error = emb_vector_distance(p0, s0) + emb_vector_distance(p1, s1);
    if (error > tolerence) {
        printf("Error larger than tolerance, circle test 2: %f.\n\n", error);
        return 1;
    }
    return 0;
}

EmbError
circle_tests(void)
{
    EmbReal epsilon = 0.001f;
    EmbGeometry c1 = emb_circle(0.0f, 0.0f, 3.0f);
    EmbVector p = emb_vector(4.0f, 0.0f);
    /* Solution */
    EmbVector s0 = emb_vector(2.2500f, 1.9843f);
    EmbVector s1 = emb_vector(2.2500f, -1.9843f);
    int result = test_ctangents(c1, p, s0, s1, epsilon);
    if (result) {
        return result;
    }
    
    c1 = emb_circle(20.1762f, 10.7170f, 6.8221f);
    p = emb_vector(24.3411f, 18.2980f);
    /* Solution */
    s0 = emb_vector(19.0911f, 17.4522f);
    s1 = emb_vector(26.4428f, 13.4133f);
    result = test_ctangents(c1, p, s0, s1, epsilon);
    if (result) {
        return result;
    }
    return EMB_NO_ERR;
}

EmbError
ellipse_tests(void)
{
    return EMB_NO_ERR;
}

/* Conversion Testing */
EmbError
convert_tests(void)
{
    int i;
    for (i=0; i<3; i++) {
        int result = test_convert(i, EMB_FORMAT_CSV, EMB_FORMAT_DST);
        if (result) {
            return result;
        }
        result = test_convert(i, EMB_FORMAT_CSV, EMB_FORMAT_SVG);
        if (result) {
            return result;
        }
    }
    return 0;
}

/* Currently just crash testing. */
EmbError
test_convert(int test_file, int from, int to)
{
    EmbString outf;
    EmbString fname_from;
    EmbString fname_to;
    sprintf(fname_from, "test%02d%s", test_file, formatTable[from].extension);
    sprintf(fname_to, "test%02d_out%s", test_file, formatTable[to].extension);
    printf("Converting test case %d: %s to %s.\n",
        test_file, fname_from, fname_to);

    EmbPattern* p = emb_pattern_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    emb_pattern_addThread(p, black_thread);

    switch (test_file) {
	case 0: {
        int i;
        EmbStitch st;
		/* 10mm circle */
		for (i = 0; i < 20; i++) {
			emb_pattern_addStitchRel(p, 0.0, 1.0, JUMP, 0);
		}
		for (i = 0; i < 200; i++) {
			st.x = 10 + 10 * sin(i * (0.03141592));
			st.y = 10 + 10 * cos(i * (0.03141592));
			st.flags = NORMAL;
			st.color = 0;
			emb_pattern_addStitchAbs(p, st.x, st.y, st.flags, st.color);
		}
		break;
	}
	case 1: {
        int i;
        EmbStitch st;
        /* sin wave */
        for (i = 0; i < 100; i++) {
            st.x = 10 + 10 * sin(i * (0.5 / 3.141592));
            st.y = 10 + i * 0.1;
            st.flags = NORMAL;
            st.color = 0;
            emb_pattern_addStitchAbs(p, st.x, st.y, st.flags, st.color);
        }
		break;
	}
	case 2: {
        EmbGeometry circle = emb_circle(10.0f, 1.0f, 5.0f);
        emb_array_add_geometry(p->geometry, circle);
        emb_pattern_convertGeometry(p);
		break;
	}
    default: {
		puts("This case is not covered.");
		break;
	}
    }

    sprintf(outf, "test%02d%s", test_file, formatTable[to].extension);
    emb_pattern_end(p);
    if (!emb_pattern_write(p, outf, to)) {
        emb_pattern_free(p);
        return 16;
    }

    emb_pattern_free(p);

    convert(fname_from, fname_to);
    return 0;
}

/* todo test_cross_test
 *     --cross-stitch ../images/$1.png 130 $1.svg
 */
EmbError
test_cross(void)
{
    return 0;
}

/* TODO: test_render
 *    --fill ../images/$1.png 130 $1.csv
 *    --fill $1.csv $1.png
 */
EmbError
test_fill(void)
{
    return 0;
}

/*
 * todo test_fill ../images/$1.png 130 $1.svg
 *
 * todo test_cross_test
 *     --cross-stitch ../images/$1.png 130 $1.svg
 *
 * todo test_generate_render
 *     --cross-stitch ../images/$1.png 130 $1.csv
 *     --render $1.csv $1_render.png
 *
 * all_tests
 *    fill_test donut 130
 *    fill_test logo-spirals 130
 *    fill_test berries 130
 *    fill_test snow-squirrel 130
 *    fill_test great-tit 130
 *    fill_test owl 130
 *    fill_test logo 130
 *
 *    cross_test logo
 *    render_fill_test logo
 *    render_cross_test logo
 */

/*
 * Tests for accuracy of the format table lookup and identification
 */
int
format_table_tests(void)
{
    const char*  tName = "example.zsk";
    int format = emb_identify_format(tName);

    printf("Filename   : %s\n"
       "Extension  : %s\n"
       "Description: %s\n"
       "Reader     : %c\n"
       "Writer     : %c\n"
       "Type       : %d\n\n",
        tName,
        formatTable[format].extension,
        formatTable[format].description,
        formatTable[format].reader_state,
        formatTable[format].writer_state,
        formatTable[format].type);

    if (strncmp(formatTable[format].extension, ".zsk", 200)) {
        puts("In format table test the extension lookup failed.");
		return 20;
	}
    if (strncmp(formatTable[format].description, "ZSK USA Embroidery Format", 200)) {
        puts("In format table test the description lookup failed.");
        return 21;
    }
    if (formatTable[format].reader_state != 'U') {
        puts("In format table test the reader_state lookup failed.");
		return 22;
	}
    if (formatTable[format].writer_state != ' ') {
        puts("In format table test the write_state lookup failed.");
		return 23;
	}
    if (formatTable[format].type != 1) {
        puts("In format table test the type lookup failed.");
		return 24;
	}
    return 0;
}

/* TODO: test_render
 *    --fill ../images/$1.png 130 $1.csv
 *    --fill $1.csv $1.png
 */
EmbError
test_photo(void)
{
    return 0;
}

/* todo test_generate_render
 *     --cross-stitch ../images/$1.png 130 $1.csv
 *     --render $1.csv $1_render.png
 */
int
render_tests(void)
{
    return 0;
}

/* all_tests
 *    fill_test donut 130
 *    fill_test logo-spirals 130
 *    fill_test berries 130
 *    fill_test snow-squirrel 130
 *    fill_test great-tit 130
 *    fill_test owl 130
 *    fill_test logo 130
 *
 *    cross_test logo
 *    render_fill_test logo
 *    render_cross_test logo
 */

EmbError
thread_color_tests(void)
{
    unsigned int tColor = 0xFF0d6b2f;
    /*
    EmbColor c;
    c.r = 0x0D;
    c.g = 0x6B;
    c.b = 0x2F;
    */
    int tBrand = EMB_BRAND_SVG;
    int tNum = threadColorNum(tColor, tBrand);
    char tName[50];
    strncpy(tName, threadColorName(tColor, tBrand), 49);

    printf("Color : 0x%X\n"
       "Brand : %d\n"
       "Num   : %d\n"
       "Name  : %s\n\n",
        tColor,
        tBrand,
        tNum, /* Solution: 29 */
        tName); /* Solution: Dark Olive Green */
    return EMB_NO_ERR;
}

EmbError
vector_tests(void)
{
    float epsilon = 0.0000000001;
    EmbVector v1 = emb_vector(1.6, 3.21);
    EmbVector v2 = emb_vector(1.64, 3.11);
    EmbVector result_add = emb_vector(3.24, 6.32);

    if (!test_vadd(v1, v2, result_add, epsilon)) {
        return 1;
    }

    return EMB_NO_ERR;
}

/* . */
EmbError
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
EmbError
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

