#include "embroidery.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED_TERM_COLOR "\e[0;31m"
#define GREEN_TERM_COLOR "\e[0;32m"
#define YELLOW_TERM_COLOR "\e[1;33m"
#define RESET_TERM_COLOR "\033[0m"

static void usage(void);
static void formats(void);
static void testTangentPoints(EmbCircle c, EmbVector p, EmbVector*, EmbVector*);
static int testEmbCircle(void);
static int testThreadColor(void);
static void report(int result, char* label);
static void testMain(void);
static int convert(const char* inf, const char* outf);
static int create_test_file_1(const char* outf);
static int create_test_file_2(const char* outf);

static const char version_string[] = "embroider v0.1";

static void usage(void)
{
    puts("EMBROIDER");
    puts("    A command line program for machine embroidery.");
    puts("    Copyright 2013-2021 The Embroidermodder Team");
    puts("    Licensed under the terms of the zlib license.");
    puts("");
    puts("    https://github.com/Embroidermodder/libembroidery");
    puts("    https://embroidermodder.org");
    puts("");
    puts("Usage: embroider [OPTIONS] fileToRead... \n");
    puts("");
    puts("Conversion:");
    puts("    -t, -to         Convert all files given to the format specified");
    puts("                    by the arguments to the flag, for example:");
    puts("                        $ embroider -t dst input.pes");
    puts("                    would convert \"input.pes\" to \"input.dst\"");
    puts("                    in the same directory the program runs in.");
    puts("");
    puts("                    The accepted input formats are (TO BE DETERMINED).");
    puts("                    The accepted output formats are (TO BE DETERMINED).");
    puts("");
    puts("Output:");
    puts("    -h, -help       Print this message.");
    puts("    -f, -format     Print help on the formats that embroider can deal with.");
    puts("    -q, -quiet      Only print fatal errors.");
    puts("    -V, -verbose    Print everything that has reporting.");
    puts("    -v, -version    Print the version.");
    puts("");
    puts("Graphics:");
    puts("    -c, -circle     Add a circle defined by the arguments given to the current pattern.");
    puts("    -e, -ellipse    Add a circle defined by the arguments given to the current pattern.");
    puts("    -l, -line       Add a line defined by the arguments given to the current pattern.");
    puts("    -P, -polyline   Add a polyline.");
    puts("    -p, -polygon    Add a polygon.");
    puts("    -s, -satin      Fill the current geometry with satin stitches according");
    puts("                    to the defined algorithm.");
    puts("    -S, -stitch     Add a stitch defined by the arguments given to the current pattern.");
    puts("");
    puts("Quality Assurance:");
    puts("        -test       Run the test suite.");
}

static void formats(void)
{
    const char* extension = 0;
    const char* description = 0;
    char readerState;
    char writerState;
    int numReaders = 0;
    int numWriters = 0;
    int i;
    puts("List of Formats");
    puts("---------------");
    puts("");
    puts("    KEY");
    puts("    'S' = Yes, and is considered stable.");
    puts("    'U' = Yes, but may be unstable.");
    puts("    ' ' = No.");
    puts("");
    puts("  Format   Read    Write   Description\n");
    puts("|________|_______|_______|____________________________________________________|\n");
    puts("|        |       |       |                                                    |\n");

    for (i = 0; i < numberOfFormats; i++) {
        extension = formatTable[i].extension;
        description = formatTable[i].description;
        readerState = formatTable[i].reader;
        writerState = formatTable[i].writer;

        numReaders += readerState != ' ' ? 1 : 0;
        numWriters += writerState != ' ' ? 1 : 0;
        printf("|  %-4s  |   %c   |   %c   |  %-49s |\n", extension, readerState, writerState, description);
    }

    puts("|________|_______|_______|____________________________________________________|\n");
    puts("|        |       |       |                                                    |\n");
    printf("| Total: |  %3d  |  %3d  |                                                    |\n", numReaders, numWriters);
    puts("|________|_______|_______|____________________________________________________|\n");
    puts("");
}

static int create_test_file_1(const char* outf)
{
    int i, result;
    EmbPattern* p;
    EmbStitch st;

    p = embPattern_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    /* 10mm circle */
    for (i = 0; i < 100; i++) {
        st.x = 10 + 10 * sin(i * (0.5 / 3.141592));
        st.y = 10 + 10 * cos(i * (0.5 / 3.141592));
        st.flags = NORMAL;
        st.color = 0;
        embArray_addStitch(p->stitchList, st);
    }

    EmbThread thr = { { 0, 0, 0 }, "Black", "Black" };
    embArray_addThread(p->threads, thr);

    result = embPattern_write(p, outf, EMB_FORMAT_CSV);

    embPattern_free(p);
    return 0;
}

static int create_test_file_2(const char* outf)
{
    int i, result;
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
        embArray_addStitch(p->stitchList, st);
    }

    EmbThread thr = { { 0, 0, 0 }, "Black", "Black" };
    embArray_addThread(p->threads, thr);

    result = embPattern_write(p, outf, EMB_FORMAT_CSV);

    embPattern_free(p);
    return 0;
}

static int convert(const char* inf, const char* outf)
{
    EmbFile *file;
    EmbPattern* p;
    int reader, writer, formatType;

    p = embPattern_create();
    if (!p) {
        puts("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    reader = embReaderWriter_getByFileName(inf);
    if (reader < 0) {
        puts("convert(), unsupported read file type:");
        puts(inf);
        embPattern_free(p);
        return 1;
    }

    writer = embReaderWriter_getByFileName(outf);
    if (writer < 0) {
        puts("convert(), unsupported write file type:");
        puts(outf);
        embPattern_free(p);
        return 1;
    }

    embPattern_read(p, inf, reader);

    if (formatTable[reader].type == EMBFORMAT_OBJECTONLY) {
        if (formatTable[writer].type == EMBFORMAT_STITCHONLY) {
            embPattern_movePolylinesToStitchList(p);
        }
    }

    embPattern_write(p, outf, writer);

    embPattern_free(p);
    return 0;
}

/* TODO: Add capability for converting multiple files of various types to a single format. Currently, we only convert a single file to multiple formats. */

int main(int argc, const char* argv[])
{
    int i, flags;
    if (argc == 1) {
        usage();
        return 0;
    }

    init_embroidery();

    flags = argc - 1;
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-help") || !strcmp(argv[i], "-h")) {
            usage();
            continue;
        }
        if (!strcmp(argv[i], "-formats") || !strcmp(argv[i], "-f")) {
            formats();
            continue;
        }
        if (!strcmp(argv[i], "-version") || !strcmp(argv[i], "-v")) {
            puts(version_string);
            continue;
        }
        if (!strcmp(argv[i], "-test")) {
            testMain();
            continue;
        }
        flags--;
    }

    /* simple from-to conversion */
    if (!flags) {
        convert(argv[1], argv[2]);
    }

    close_embroidery();
    return 0;
}

static void testTangentPoints(EmbCircle c, EmbVector p, EmbVector* t0, EmbVector* t1)
{
    if (!getCircleTangentPoints(c, p, t0, t1)) {
        printf("Error calculating tangent points.\n");
    } else {
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

int testEmbCircle(void)
{
    float epsilon = 1e-3;
    EmbVector p0, p1;
    /* Problem */
    EmbCircle c1 = { { 0.0, 0.0 }, 3.0 };
    /* Solution */
    EmbVector t0 = { 2.2500, 1.9843 };
    EmbVector t1 = { 2.2500, -1.9843 };
    /* Test */
    EmbVector test0 = { 4.0, 0.0 };
    testTangentPoints(c1, test0, &p0, &p1);
    if (embVector_distance(p0, t0) + embVector_distance(p1, t1) > epsilon) {
        return 16;
    }

    EmbCircle c2 = { { 20.1762, 10.7170 }, 6.8221 };
    /* Solution */
    EmbVector s0 = { 19.0911, 17.4522 };
    EmbVector s1 = { 26.4428, 13.4133 };
    /* Test */
    EmbVector test1 = { 24.3411, 18.2980 };
    testTangentPoints(c2, test1, &p0, &p1);
    float error = embVector_distance(p0, s0) + embVector_distance(p1, s1);
    if (error > epsilon) {
        printf("Error larger than tolerence, circle test 2: %f.\n\n", error);
        return 17;
    }

    return 0;
}

static void printArcResults(float bulge, EmbArc arc, EmbVector center,
    float radius, float diameter, float chord, EmbVector chordMid,
    float sagitta, float apothem, float incAngle, char clockwise)
{
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
        center.x,
        center.y,
        radius,
        diameter,
        chord,
        chordMid.x,
        chordMid.y,
        sagitta,
        apothem,
        incAngle,
        clockwise);
}

int testGeomArc(void)
{
    EmbArc arc;
    EmbVector center, chordMid;
    float bulge, radius, diameter, chord, sagitta, apothem, incAngle;
    char clockwise;

    fprintf(stdout, "Clockwise Test:\n");
    bulge = -0.414213562373095;
    arc.start.x = 1.0;
    arc.start.y = 0.0;
    arc.end.x = 2.0;
    arc.end.y = 1.0;
    if (getArcDataFromBulge(bulge, &arc, &center, &radius, &diameter, &chord,
            &chordMid, &sagitta, &apothem, &incAngle, &clockwise)) {
        printArcResults(bulge, arc, center, radius, diameter,
            chord, chordMid, sagitta, apothem, incAngle, clockwise);
    }

    fprintf(stdout, "Counter-Clockwise Test:\n");
    bulge = 2.414213562373095;
    arc.start.x = 4.0;
    arc.start.y = 0.0;
    arc.end.x = 5.0;
    arc.end.y = 1.0;
    if (getArcDataFromBulge(bulge, &arc, &center, &radius, &diameter, &chord,
            &chordMid, &sagitta, &apothem, &incAngle, &clockwise)) {
        printArcResults(bulge, arc, center, radius, diameter,
            chord, chordMid, sagitta, apothem, incAngle, clockwise);
    }

    return 0;
}

static int testThreadColor(void)
{
    unsigned int tColor = 0xFFD25F00;
    EmbColor c;
    c.r = 0xD2;
    c.g = 0x5F;
    c.b = 0x00;
    int tBrand = Sulky_Rayon;
    int tNum = threadColorNum(c, tBrand);
    const char* tName = threadColorName(c, tBrand);

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

static int testEmbFormat(void)
{
    const char* tName = "example.zsk";
    int code = embReaderWriter_getByFileName(tName);
    const char* description = formatTable[code].description;
    const char *extension = formatTable[code].extension;
    char reader = formatTable[code].reader;
    char writer = formatTable[code].writer;
    int type = formatTable[code].type;

    printf("Filename   : %s\n"
           "Extension  : %s\n"
           "Description: %s\n"
           "Reader     : %c\n"
           "Writer     : %c\n"
           "Type       : %d\n\n",
        tName,
        extension,
        description,
        reader,
        writer,
        type);

    if (strcmp(extension, ".zsk"))
        return 20;
    if (strcmp(description, "ZSK USA Embroidery Format"))
        return 21;
    if (reader != 'U')
        return 22;
    if (writer != ' ')
        return 23;
    if (type != 1)
        return 24;
    return 0;
}

static void
report(int result, char* label)
{
    printf("%s Test...%*c", label, (int)(20 - strlen(label)), ' ');
    if (result) {
        printf(RED_TERM_COLOR "[FAIL] [CODE=%d]\n" RESET_TERM_COLOR, result);
    } else {
        printf(GREEN_TERM_COLOR "[PASS]\n" RESET_TERM_COLOR);
    }
}

/**
 * Note that we can use printf here because this file isn't compiled into
 * libembroidery.so.
 */
#if 0
static int embeddedFunctionsResult(void)
{
    char buffer[30];
    int dnumber;
    float fnumber;
    dnumber = 2031;
    fnumber = 12.4123;
    /* embPointerToArray(buffer, (void *)buffer, 10);
    printf("%s %p\n", buffer, (void *)buffer); */
    embIntToArray(buffer, dnumber, 10);
    printf("%s %d\n", buffer, dnumber);
    if (strcmp(buffer, "2031")) {
        return 1;
    }
    embFloatToArray(buffer, fnumber, 1.0e-7, 3, 3);
    printf("%s %f\n", buffer, fnumber);
    if (strcmp(buffer, "12.412")) {
        return 1;
    }
    return 0;
}
#endif

static void testMain(void)
{
    int circleResult = testEmbCircle();
    int threadResult = testThreadColor();
    int formatResult = testEmbFormat();
    int arcResult = testGeomArc();
    int create1Result = create_test_file_1("test01.csv");
    int create2Result = create_test_file_2("test02.csv");
    int svg1Result = convert("test01.csv", "test01.svg");
    int svg2Result = convert("test02.csv", "test02.svg");
    int dst1Result = convert("test01.csv", "test01.dst");
    int dst2Result = convert("test02.csv", "test02.dst");
    /* int embeddedResult = embeddedFunctionsResult(); */

    puts("SUMMARY OF RESULTS");
    puts("------------------");
    report(circleResult, "Tangent Point");
    report(threadResult, "Thread");
    report(formatResult, "Format");
    report(arcResult, "Arc");
    report(create1Result, "Create CSV 1");
    report(create2Result, "Create CSV 2");
    report(svg1Result, "Convert CSV-SVG 1");
    report(svg2Result, "Convert CSV-SVG 2");
    report(dst1Result, "Convert CSV-DST 1");
    report(dst2Result, "Convert CSV-DST 2");
    /* report(embeddedResult, "Embedded Functions"); */
}

