#include "../embroidery.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define RED_TERM_COLOR "\e[0;31m"
#define GREEN_TERM_COLOR "\e[0;32m"
#define YELLOW_TERM_COLOR "\e[1;33m"
#define RESET_TERM_COLOR "\033[0m"

static void usage(void);
static void formats(void);
static void testTangentPoints(EmbCircle c, double  px, double  py, EmbPoint *, EmbPoint *);
static int testEmbCircle(void);
static int testThreadColor(void);
static void report(int result, char *label);
static void testMain(void);
static int convert(const char *inf, const char *outf);

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
    printf("  Format   Read    Write   Description\n");
    printf("|________|_______|_______|____________________________________________________|\n");
    printf("|        |       |       |                                                    |\n");

    for (i=0; i<numberOfFormats; i++) {
        extension = formatTable[i].extension;
        description = formatTable[i].description;
        readerState = formatTable[i].reader;
        writerState = formatTable[i].writer;

        numReaders += readerState != ' '? 1 : 0;
        numWriters += writerState != ' '? 1 : 0;
        printf("|  %-4s  |   %c   |   %c   |  %-49s |\n", extension, readerState, writerState, description);
    }

    printf("|________|_______|_______|____________________________________________________|\n");
    printf("|        |       |       |                                                    |\n");
    printf("| Total: |  %3d  |  %3d  |                                                    |\n", numReaders, numWriters);
    printf("|________|_______|_______|____________________________________________________|\n");
    puts("");
}

static int convert(const char *inf, const char *outf)
{
    EmbPattern* p = 0;
    int formatType;
    EmbReaderWriter* reader = 0, *writer = 0;

    p = embPattern_create();
    if (!p) { 
        embLog_error("convert(), cannot allocate memory for p\n");
        return 1;
    }

    reader = embReaderWriter_getByFileName(inf);
    if (!reader) {
        embLog_error("convert(), unsupported read file type: %s\n", inf);
        embPattern_free(p);
        return 1;
    }
    if (!reader->reader(p, inf)) {
        embLog_error("convert(), reading file was unsuccessful: %s\n", inf);
        free(reader);
        embPattern_free(p);
        return 1;
    }
    free(reader);

    formatType = embFormat_typeFromName(inf);
    if (formatType == EMBFORMAT_OBJECTONLY) {
        formatType = embFormat_typeFromName(outf);
        if (formatType == EMBFORMAT_STITCHONLY) {
            embPattern_movePolylinesToStitchList(p);
        }
    }

    writer = embReaderWriter_getByFileName(outf);
    if (!writer) {
        embLog_error("convert(), unsupported write file type: %s\n", outf);
        embPattern_free(p);
        return 1;
    }
    if (!writer->writer(p, outf)) {
        embLog_error("convert(), writing file %s was unsuccessful\n", outf);
        free(writer);
        embPattern_free(p);
        return 1;
    }
    free(writer);
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

    flags = argc-1;
    for (i=1; i<argc; i++) {
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

    return 0;

}


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
    const char *extension = embFormat_extensionFromName(tName);
    const char *description = embFormat_descriptionFromName(tName);
    char reader = embFormat_readerStateFromName(tName);
    char writer = embFormat_writerStateFromName(tName);
    int type = embFormat_typeFromName(tName);

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

    if (strcmp(extension, ".zsk")) return 20;
    if (strcmp(description, "ZSK USA Embroidery Format")) return 21;
    if (reader != 'U') return 22;
    if (writer != ' ') return 23;
    if (type != 1) return 24;
    return 0;
}

static int testHash(void)
{
    EmbHash* hash = 0;
    hash = embHash_create();
    if(!hash) return 1;
    if(!embHash_empty(hash)) return 2;
    if(embHash_count(hash) != 0) return 3;

    /* insert */
    if(embHash_insert(hash, "four", (void*)4)) return 4;
    if(embHash_insert(hash, "five", (void*)5)) return 5;
    if(embHash_insert(hash, "six",  (void*)6)) return 6;
    if(embHash_count(hash) != 3) return 7;

    /* replace */
    if(embHash_insert(hash, "four",  (void*)8)) return 8;
    if(embHash_insert(hash, "five", (void*)10)) return 9;
    if(embHash_insert(hash, "six",  (void*)12)) return 10;
    if(embHash_count(hash) != 3) return 11;

    /* contains */
    if(!embHash_contains(hash, "four")) return 12;
    if(embHash_contains(hash, "empty")) return 13;

    /* remove */
    embHash_remove(hash, "four");
    if(embHash_count(hash) != 2) return 14;
    embHash_clear(hash);
    if(embHash_count(hash) != 0) return 15;

    embHash_free(hash);
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

static void testMain(void)
{
    int hashResult = testHash();
    int circleResult = testEmbCircle();
    int threadResult = testThreadColor();
    int formatResult = testEmbFormat();
    int arcResult = testGeomArc();

    puts("SUMMARY OF RESULTS");
    puts("------------------");
    report(hashResult, "Hash");
    report(circleResult, "Tangent Point");
    report(threadResult, "Thread");
    report(formatResult, "Format");
    report(arcResult, "Arc");
}

