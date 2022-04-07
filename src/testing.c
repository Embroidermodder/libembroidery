/*
 * This file is part of libembroidery.
 *
 * Copyright 2018-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "embroidery.h"

#define RED_TERM_COLOR      "\x1B[0;31m"
#define GREEN_TERM_COLOR    "\x1B[0;32m"
#define YELLOW_TERM_COLOR   "\x1B[1;33m"
#define RESET_TERM_COLOR       "\033[0m"

int create_test_file_3(const char *);

void report(int result, char *label)
{
    printf("%s Test...%*c", label, (int)(20-strlen(label)), ' ');
    if (result) {
        printf(RED_TERM_COLOR "[FAIL] [CODE=%d]\n" RESET_TERM_COLOR, result);
    }
    else {
        printf(GREEN_TERM_COLOR "[PASS]\n" RESET_TERM_COLOR);
    }
}

void testMain(int level)
{
    EmbPattern *pattern = embPattern_create();
    EmbImage *image = embImage_create(100, 100);
    int overall = 0;
    int circleResult = testEmbCircle();
    int threadResult = testThreadColor();
    int formatResult = testEmbFormat();
    int arcResult = testGeomArc();
    int create1Result = create_test_file_1("test01.csv");
    int create2Result = create_test_file_2("test02.csv");
    int create3Result = create_test_file_3("test03.csv");
    int svg1Result = convert("test01.csv", "test01.svg");
    int svg2Result = convert("test02.csv", "test02.svg");
    int svg3Result = convert("test03.csv", "test03.svg");
    int dst1Result = convert("test01.csv", "test01.dst");
    int dst2Result = convert("test02.csv", "test02.dst");
    int dst3Result = convert("test03.csv", "test03.dst");
    int hilbertCurveResult = hilbert_curve(pattern, 3);
    int renderResult = embImage_render(pattern, 20.0, 20.0, "hilbert_level_3.ppm");
    int simulateResult = embImage_simulate(pattern, 20.0, 20.0, "hilbert_level_3.avi");

    overall += circleResult;
    overall += threadResult;
    overall += formatResult;
    overall += arcResult;
    overall += create1Result;
    overall += create2Result;
    overall += create3Result;
    overall += svg1Result;
    overall += svg2Result;
    overall += svg3Result;
    overall += dst1Result;
    overall += dst2Result;
    overall += dst3Result;

    if (emb_verbose >= 0) {
        puts("SUMMARY OF RESULTS");
        puts("------------------");
        report(circleResult, "Tangent Point");
        report(threadResult, "Thread");
        report(formatResult, "Format");
        report(arcResult, "Arc");
        report(create1Result, "Create CSV 1");
        report(create2Result, "Create CSV 2");
        report(create3Result, "Create CSV 3");
        report(svg1Result, "Convert CSV-SVG 1");
        report(svg2Result, "Convert CSV-SVG 2");
        report(svg3Result, "Convert CSV-SVG 3");
        report(dst1Result, "Convert CSV-DST 1");
        report(dst2Result, "Convert CSV-DST 2");
        report(dst3Result, "Convert CSV-DST 3");
        report(hilbertCurveResult, "Generating Hilbert Curve");
        report(renderResult, "Rendering Hilbert Curve");
        report(simulateResult, "Simulating Hilbert Curve");
    }
    
    embImage_free(image);
    embPattern_free(pattern);
    if (level > 0) {
        puts("More expensive tests.");
        full_test_matrix("test_matrix.txt");
    }
    if (overall == 0) {
        puts("PASS");
    }
    else {
        puts("FAIL");
    }
}

void testTangentPoints(EmbCircle c, EmbVector p, EmbVector *t0, EmbVector *t1)
{
    emb_error = 0;
    t0->x = 0.0;
    t0->y = 0.0;
    t1->x = 0.0;
    t1->y = 0.0;
    if (!getCircleTangentPoints(c, p, t0, t1)) {
        printf("Error calculating tangent points.\n");
        emb_error = 1;
    }
    else {
        if (emb_verbose > 0) {
            printf("Circle : cr=%f, cx=%f, cy=%f\n"
               "Point  : px=%f, py=%f\n"
               "Tangent: tx0=%f, ty0=%f\n"
               "Tangent: tx1=%f, ty1=%f\n\n",
               c.radius, c.center.x, c.center.y,
               p.x, p.y,
               t0->x, t0->y,
               t1->x, t1->y);
        }
    }
}

float embVector_distance(EmbVector p, EmbVector q)
{
    EmbVector delta;
    embVector_subtract(p, q, &delta);
    return embVector_length(delta);
}

int testEmbCircle(void) {
    double error;
    double epsilon = 1e-3;
    EmbVector p0, p1;
    /* Problem */
    EmbCircle c1 = {{0.0, 0.0}, 3.0};
    /* Solution */
    EmbVector t0 = {2.2500, 1.9843};
    EmbVector t1 = {2.2500, -1.9843};
    EmbVector p = {4.0, 0.0};
    /* Test */
    testTangentPoints(c1, p, &p0, &p1);
    error = embVector_distance(p0, t0) + embVector_distance(p1, t1);
    if (error > epsilon) {
        printf("Error larger than tolerance, circle test 1: %f.\n\n", error);
        return 16;
    }

    return 0;
}

int testEmbCircle_2(void) {
    double error;
    double epsilon = 1e-3;
    EmbVector p0, p1;
    EmbCircle c2 = {{20.1762, 10.7170}, 6.8221};
    /* Solution */
    EmbVector s0 = {19.0911, 17.4522};
    EmbVector s1 = {26.4428, 13.4133};
    EmbVector p = {24.3411, 18.2980};
    /* Test */
    testTangentPoints(c2, p, &p0, &p1);
    error = embVector_distance(p0, s0) + embVector_distance(p1, s1);
    if (error > epsilon) {
        printf("Error larger than tolerance, circle test 2: %f.\n\n", error);
        return 17;
    }

    return 0;
}

void printArcResults(double bulge, EmbArc arc,
                     double centerX,   double centerY,
                     double radius,    double diameter,
                     double chord,
                     double chordMidX, double chordMidY,
                     double sagitta,   double apothem,
                     double incAngle,  char   clockwise) {
    fprintf(stdout, "bulge     = %f\n"
                    "startX    = %f\n"
                    "startY    = %f\n"
                    "endX      = %f\n"
                    "endY      = %f\n"
                    "midX      = %f\n"
                    "midY      = %f\n"
                    "centerX   = %f\n"
                    "centerY   = %f\n"
                    "radius    = %f\n"
                    "diameter  = %f\n"
                    "chord     = %f\n"
                    "chordMidX = %f\n"
                    "chordMidY = %f\n"
                    "sagitta   = %f\n"
                    "apothem   = %f\n"
                    "incAngle  = %f\n"
                    "clockwise = %d\n"
                    "\n",
                    bulge,
                    arc.start.x,
                    arc.start.y,
                    arc.end.x,
                    arc.end.y,
                    arc.mid.x,
                    arc.mid.y,
                    centerX,
                    centerY,
                    radius,
                    diameter,
                    chord,
                    chordMidX,
                    chordMidY,
                    sagitta,
                    apothem,
                    incAngle,
                    clockwise);
}

int testGeomArc(void) {
    EmbArc arc;
    EmbVector center, chordMid;
    double bulge, radius, diameter, chord, sagitta, apothem, incAngle;
    char clockwise;

    bulge = -0.414213562373095;
    arc.start.x = 1.0;
    arc.start.y = 0.0;
    arc.end.x   = 2.0;
    arc.end.y   = 1.0;
    if (getArcDataFromBulge(bulge, &arc,
                           &(center.x),   &(center.y),
                           &radius,    &diameter,
                           &chord,
                           &(chordMid.x), &(chordMid.y),
                           &sagitta,   &apothem,
                           &incAngle,  &clockwise)) {
        if (emb_verbose > 0) {
            fprintf(stdout, "Clockwise Test:\n");
            printArcResults(bulge, arc, center.x, center.y,
                        radius, diameter,
                        chord,
                        chordMid.x, chordMid.y,
                        sagitta,   apothem,
                        incAngle,  clockwise);
        }
    }

    bulge  = 2.414213562373095;
    arc.start.x = 4.0;
    arc.start.y = 0.0;
    arc.end.x   = 5.0;
    arc.end.y   = 1.0;
    if (getArcDataFromBulge(bulge, &arc,
                           &(center.x),   &(center.y),
                           &radius,    &diameter,
                           &chord,
                           &(chordMid.x), &(chordMid.y),
                           &sagitta,   &apothem,
                           &incAngle,  &clockwise)) {
        if (emb_verbose > 0) {
            fprintf(stdout, "Counter-Clockwise Test:\n");
            printArcResults(bulge, arc, center.x, center.y,
                        radius,    diameter,
                        chord,
                        chordMid.x, chordMid.y,
                        sagitta,   apothem,
                        incAngle,  clockwise);
        }
    }

    return 0;
}

int testThreadColor(void) {
    unsigned int tColor = 0xFFD25F00;
    int          tBrand = Sulky_Rayon;
    int          tNum   = threadColorNum(tColor, tBrand);
    const char*  tName  = threadColorName(tColor, tBrand);

    if (emb_verbose > 0) {
        printf("Color : 0x%X\n"
           "Brand : %d\n"
           "Num   : %d\n"
           "Name  : %s\n\n",
            tColor,
            tBrand,
            tNum, /* Solution: 1833 */
            tName); /* Solution: Pumpkin Pie */
    }
    return 0;
}

int testEmbFormat(void) {
    const char*  tName = "example.zsk";
    int format = emb_identify_format(tName);

    if (emb_verbose > 0) {
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
    }

    if (strcmp(formatTable[format].extension, ".zsk")) return 20;
    if (strcmp(formatTable[format].description, "ZSK USA Embroidery Format")) {
            return 21;
    }
    if (formatTable[format].reader_state != 'U') return 22;
    if (formatTable[format].writer_state != ' ') return 23;
    if (formatTable[format].type != 1) return 24;
    return 0;
}

int
create_test_file_1(const char* outf)
{
    int i;
    EmbPattern* p;
    EmbStitch st;

    p = embPattern_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    /* 10mm circle */
    for (i = 0; i < 20; i++) {
        embPattern_addStitchRel(p, 0.0, 1.0, JUMP, 0);
    }
    for (i = 0; i < 200; i++) {
        st.x = 10 + 10 * sin(i * (0.03141592));
        st.y = 10 + 10 * cos(i * (0.03141592));
        st.flags = NORMAL;
        st.color = 0;
        embPattern_addStitchAbs(p, st.x, st.y, st.flags, st.color);
    }

    embPattern_addThread(p, black_thread);
    embPattern_end(p);

    if (!embPattern_writeAuto(p, outf)) {
        return 16;
    }

    embPattern_free(p);
    return 0;
}

int
create_test_file_2(const char* outf)
{
    int i;
    EmbPattern* p;
    EmbStitch st;

    p = embPattern_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    /* sin wave */
    for (i = 0; i < 100; i++) {
        st.x = 10 + 10 * sin(i * (0.5 / 3.141592));
        st.y = 10 + i * 0.1;
        st.flags = NORMAL;
        st.color = 0;
        embPattern_addStitchAbs(p, st.x, st.y, st.flags, st.color);
    }

    embPattern_addThread(p, black_thread);
    embPattern_end(p);

    if (!embPattern_writeAuto(p, outf)) {
        return 16;
    }

    embPattern_free(p);
    return 0;
}

int
create_test_file_3(const char* outf)
{
    EmbPattern* p;

    p = embPattern_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    embPattern_addCircleObjectAbs(p, 10.0, 1.0, 5.0);

    embPattern_addThread(p, black_thread);
    embPattern_convertGeometry(p);
    embPattern_end(p);

    if (!embPattern_writeAuto(p, outf)) {
        return 16;
    }

    embPattern_free(p);
    return 0;
}


/* TODO: Add capability for converting multiple files of various types to a single format. 
Currently, we only convert a single file to multiple formats. */
#if 0
int testThreadColor(void) {
    unsigned int tColor = 0xFFD25F00;
    EmbColor c;
    c.r = 0xD2;
    c.g = 0x5F;
    c.b = 0x00;
    int tBrand = Sulky_Rayon;
    int tNum = threadColorNum(c, tBrand);
    char tName[50];
    threadColorName(tName, c, tBrand);

    printf("Color : 0x%X\n"
           "Brand : %d\n"
           "Num   : %d\n"
           "Name  : %s\n\n",
        tColor,
        tBrand,
        tNum, /* Solution: 1833 */
        tName); /* Solution: Pumpkin Pie */
    return 0;
}
#endif

/*
 * Table of from/to for formats. What conversions after a from A to B conversion
 * leave a file with the same render?
 *
 * Add command "--full-test-suite" for this full matrix.
 */

int full_test_matrix(char *fname) {
    int i, j, success, ntests;
    FILE *f;
    f = fopen(fname, "wb");
    if (!f) {
        puts("ERROR: full_test_matrix(fname) failed to open file.");
        return 1;
    }

    success = 0;
    ntests = (numberOfFormats - 1)*(numberOfFormats - 5);
    for (i = 0; i < numberOfFormats; i++) {
        char fname[100];
        if (formatTable[i].color_only) {
            continue;
        }
        snprintf(fname, 30, "test01%s", formatTable[i].extension);
        create_test_file_1(fname);
        for (j=0; j < numberOfFormats; j++) {
            EmbPattern *pattern = 0;
            char fname_converted[100];
            char fname_image[100];
            int result;
            snprintf(fname_converted, 30, "test01_%s_converted_to%s",
                formatTable[i].extension+1, formatTable[j].extension);
            snprintf(fname_image, 30, "test01_%s_converted_to%s.ppm",
                formatTable[i].extension+1, formatTable[j].extension+1);
            printf("Attempting: %s %s\n", fname, fname_converted);
            result = convert(fname, fname_converted);
            embPattern_read(pattern, fname_converted, j);
            embImage_render(pattern, 20.0, 20.0, fname_image);
            embPattern_free(pattern);
            fprintf(f, "%d %d %f%% ", i, j, 100*success/(1.0*ntests));
            if (!result) {
                fprintf(f, "PASS\n");
                success++;
            } else {
                fprintf(f, "FAIL\n");
            }
        }
    }

    fclose(f);
    return 0;
}

