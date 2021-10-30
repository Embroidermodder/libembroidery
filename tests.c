#include "embroidery.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#define RED_TERM_COLOR "\e[0;31m"
#define GREEN_TERM_COLOR "\e[0;32m"
#define YELLOW_TERM_COLOR "\e[1;33m"
#define RESET_TERM_COLOR "\033[0m"

static void testTangentPoints(EmbCircle c, double  px, double  py, EmbPoint *, EmbPoint *);
static int testEmbCircle(void);
static int testThreadColor(void);

static void testTangentPoints(EmbCircle c,
    double px, double py,
    EmbPoint *t0, EmbPoint *t1)
{
    double tx0 = 0.0, tx1 = 0.0, ty0 = 0.0, ty1 = 0.0;
    if(!getCircleTangentPoints(c, px, py,
                               &tx0, &ty0,
                               &tx1, &ty1)) {
        printf("Error calculating tangent points.\n");
    }
    else {
        printf("Circle : cr=%f, cx=%f, cy=%f\n"
               "Point  : px=%f, py=%f\n"
               "Tangent: tx0=%f, ty0=%f\n"
               "Tangent: tx1=%f, ty1=%f\n\n",
               c.radius, c.centerX, c.centerY,
               px, py,
               tx0, ty0,
               tx1, ty1);
        t0->x = tx0;
        t0->y = ty0;
        t1->x = tx1;
        t1->y = ty1;
    }
}

double distance(EmbPoint p, EmbPoint q)
{
    double x2 = (p.x-q.x)*(p.x-q.x);
    double y2 = (p.y-q.y)*(p.y-q.y);
    return sqrt(x2+y2);
}

int testEmbCircle(void)
{
    double epsilon = 1e-3;
    EmbPoint p0, p1;
    /* Problem */
    EmbCircle c1 = {0.0, 0.0, 3.0};
    /* Solution */
    EmbPoint t0 = {2.2500, 1.9843};
    EmbPoint t1 = {2.2500, -1.9843};
    /* Test */
    testTangentPoints(c1, 4.0, 0.0, &p0, &p1);
    if (distance(p0, t0) + distance(p1, t1) > epsilon) {
        return 16;
    }

    EmbCircle c2 = {20.1762, 10.7170, 6.8221};
    /* Solution */
    EmbPoint s0 = {19.0911, 17.4522};
    EmbPoint s1 = {26.4428, 13.4133};
    /* Test */
    testTangentPoints(c2, 24.3411, 18.2980, &p0, &p1);
    double error = distance(p0, s0) + distance(p1, s1);
    if (error > epsilon) {
        printf("Error larger than tolerence, circle test 2: %f.\n\n", error);
        return 17;
    }

    return 0;
}

static void printArcResults(double bulge,
                     double startX,    double startY,
                     double endX,      double endY,
                     double midX,      double midY,
                     double centerX,   double centerY,
                     double radius,    double diameter,
                     double chord,
                     double chordMidX, double chordMidY,
                     double sagitta,   double apothem,
                     double incAngle,  char   clockwise)
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
                    startX,
                    startY,
                    endX,
                    endY,
                    midX,
                    midY,
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

int testGeomArc(void)
{
    double bulge;
    double startX;    double startY;
    double endX;      double endY;
    /* returned data */
    double midX;      double midY;
    double centerX;   double centerY;
    double radius;    double diameter;
    double chord;
    double chordMidX; double chordMidY;
    double sagitta;   double apothem;
    double incAngle;  char   clockwise;

    fprintf(stdout, "Clockwise Test:\n");
    bulge = -0.414213562373095;
    startX = 1.0;
    startY = 0.0;
    endX   = 2.0;
    endY   = 1.0;
    if(getArcDataFromBulge(bulge,
                           startX,     startY,
                           endX,       endY,
                           /* returned data */
                           &midX,      &midY,
                           &centerX,   &centerY,
                           &radius,    &diameter,
                           &chord,
                           &chordMidX, &chordMidY,
                           &sagitta,   &apothem,
                           &incAngle,  &clockwise))
    {
        printArcResults(bulge,
                        startX,    startY,
                        endX,      endY,
                        midX,      midY,
                        centerX,   centerY,
                        radius,    diameter,
                        chord,
                        chordMidX, chordMidY,
                        sagitta,   apothem,
                        incAngle,  clockwise);
    }

    fprintf(stdout, "Counter-Clockwise Test:\n");
    bulge  = 2.414213562373095;
    startX = 4.0;
    startY = 0.0;
    endX   = 5.0;
    endY   = 1.0;
    if(getArcDataFromBulge(bulge,
                           startX,     startY,
                           endX,       endY,
                           /* returned data */
                           &midX,      &midY,
                           &centerX,   &centerY,
                           &radius,    &diameter,
                           &chord,
                           &chordMidX, &chordMidY,
                           &sagitta,   &apothem,
                           &incAngle,  &clockwise))
    {
        printArcResults(bulge,
                        startX,    startY,
                        endX,      endY,
                        midX,      midY,
                        centerX,   centerY,
                        radius,    diameter,
                        chord,
                        chordMidX, chordMidY,
                        sagitta,   apothem,
                        incAngle,  clockwise);
    }

    return 0;
}

static int testThreadColor(void)
{
    unsigned int tColor = 0xFFD25F00;
    int          tBrand = Sulky_Rayon;
    int          tNum   = threadColorNum(tColor, tBrand);
    const char*  tName  = threadColorName(tColor, tBrand);

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

    if (strcmp(formatTable[format].extension, ".zsk")) return 20;
    if (strcmp(formatTable[format].description, "ZSK USA Embroidery Format")) return 21;
    if (formatTable[format].reader_state != 'U') return 22;
    if (formatTable[format].writer_state != ' ') return 23;
    if (formatTable[format].type != 1) return 24;
    return 0;
}

static void
report(int result, char *label)
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
    int circleResult = testEmbCircle();
    int threadResult = testThreadColor();
    int formatResult = testEmbFormat();
    int arcResult = testGeomArc();
    /*
    int create1Result = create_test_file_1("test01.csv");
    int create2Result = create_test_file_2("test02.csv");
    int svg1Result = convert("test01.csv", "test01.svg");
    int svg2Result = convert("test02.csv", "test02.svg");
    int dst1Result = convert("test01.csv", "test01.dst");
    int dst2Result = convert("test02.csv", "test02.dst");
    */

    puts("SUMMARY OF RESULTS");
    puts("------------------");
    report(circleResult, "Tangent Point");
    report(threadResult, "Thread");
    report(formatResult, "Format");
    report(arcResult, "Arc");
    /*
    report(create1Result, "Create CSV 1");
    report(create2Result, "Create CSV 2");
    report(svg1Result, "Convert CSV-SVG 1");
    report(svg2Result, "Convert CSV-SVG 2");
    report(dst1Result, "Convert CSV-DST 1");
    report(dst2Result, "Convert CSV-DST 2");
    */
    
    if (level > 0) {
        puts("More expensive tests.");
        full_test_matrix("test_matrix.txt");
    }
}

#if 0
/* the new version matches the main to this point */
static void formats(void)
{
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
        EmbFormatList f;
        f = embFormat_data(i);

        numReaders += f.reader != ' ' ? 1 : 0;
        numWriters += f.writer != ' ' ? 1 : 0;
        printf("|  %-4s  |   %c   |   %c   |  %-49s |\n", f.extension, f.reader, f.writer, f.description);
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
        embArray_add(p->stitchList, &st);
    }

    EmbThread thr = { { 0, 0, 0 }, "Black", "Black" };
    embPattern_addThread(p, thr);

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
        embArray_add(p->stitchList, &st);
    }

    EmbThread thr = { { 0, 0, 0 }, "Black", "Black" };
    embPattern_addThread(p, thr);

    result = embPattern_write(p, outf, EMB_FORMAT_CSV);

    embPattern_free(p);
    return 0;
}

static int convert(const char* inf, const char* outf)
{
    EmbPattern* p;
    int reader, writer, formatType;
    
    printf("Converting %s to %s.\n", inf, outf);

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

    EmbFormatList f, g;
    f = embFormat_data(reader);
    g = embFormat_data(writer);

    if (f.type == EMBFORMAT_OBJECTONLY) {
        if (g.type == EMBFORMAT_STITCHONLY) {
            embPattern_movePolylinesToStitchList(p);
        }
    }

    embPattern_write(p, outf, writer);

    embPattern_free(p);
    return 0;
}

/* TODO: Add capability for converting multiple files of various types to a single format. Currently, we only convert a single file to multiple formats. */
/* the only difference in main() between new and current is these lines

    init_embroidery();
    close_embroidery();
*/

static int testThreadColor(void)
{
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


int create_test_csv_file(char *fname, int type)
{
    FILE *f;
    int i;
    EmbStitch st;

    f = fopen(fname, "w");

    for (i = 0; i < 100; i++) {
        switch (type) {
        case 1:
            st.x = 10 + 10 * sin(i * (0.5 / 3.141592));
            st.y = 10 + i * 0.1;
            st.flags = NORMAL;
            st.color = 0;
            break;
        default:
            st.x = 10 + 10 * sin(i * (0.5 / 3.141592));
            st.y = 10 + 10 * cos(i * (0.5 / 3.141592));
            st.flags = NORMAL;
            st.color = 0;
            break;
        }
        fprintf(f, "\n");
    }
    
    fclose(f);
    return 0;
}


/*
 * Table of from/to for formats. What conversions after a from A to B conversion
 * leave a file with the same render?
 *
 * Add command "--full-test-suite" for this full matrix.
 */

int full_test_matrix (char *fname)
{
    const char *example_files[] = {
        "example.pes", "",
        "", "",
        "", ""
    };

    FILE *f;
    f = fopen(fname, "wb");
    if (!f) {
        puts("ERROR: full_test_matrix(fname) failed to open file.");
        return 1;
    }

/*
    for (i=0; i<NUMBER_OF_EXAMPLES; i++) {
        for (j=0; j<numberOfFormats; j++) {
            create_test_file(a, script[i]);
            convert(a, b);
            p3_render(b);
            int d = image_distance(a, b);
            fprintf(f, "%d %d ", i, j);
            if (d < tolerence) {
                fprintf(f, "PASS\n");
            }
            else {
                fprintf(f, "FAIL\n");
            }
        }
    }
    */
    fclose(f);
}


