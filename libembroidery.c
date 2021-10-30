#include "embroidery.h"

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define EMB_BIG_ENDIAN                          0
#define EMB_LITTLE_ENDIAN                       1

#define ENDIAN_HOST                             EMB_LITTLE_ENDIAN

static EmbColor black = {0,0,0};

/* TODO: This list needs reviewed in case some stitch formats also can contain object data (EMBFORMAT_STCHANDOBJ). */

EmbFormatList formatTable[numberOfFormats] = {
    {".10o", "Toyota Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY, read10o, write10o},
    {".100", "Toyota Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY, read100, write100},
    {".art", "Bernina Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY, readArt, writeArt},
    {".bmc", "Bitmap Cache Embroidery Format",     ' ', ' ', EMBFORMAT_STITCHONLY, readBmc, writeBmc},
    {".bro", "Bits & Volts Embroidery Format",     'U', ' ', EMBFORMAT_STITCHONLY, readBro, writeBro},
    {".cnd", "Melco Embroidery Format",            ' ', ' ', EMBFORMAT_STITCHONLY, readCnd, writeCnd},
    {".col", "Embroidery Thread Color Format",     'U', 'U', EMBFORMAT_STITCHONLY, readCol, writeCol},
    {".csd", "Singer Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY, readCsd, writeCsd},
    {".csv", "Comma Separated Values Format",      'U', 'U', EMBFORMAT_STITCHONLY, readCsv, writeCsv},
    {".dat", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, readDat, writeDat},
    {".dem", "Melco Embroidery Format",            ' ', ' ', EMBFORMAT_STITCHONLY, readDem, writeDem},
    {".dsb", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, readDsb, writeDsb},
    {".dst", "Tajima Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, readDst, writeDst},
    {".dsz", "ZSK USA Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, readDsz, writeDsz},
    {".dxf", "Drawing Exchange Format",            ' ', ' ', EMBFORMAT_OBJECTONLY, readDxf, writeDxf},
    {".edr", "Embird Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, readEdr, writeEdr},
    {".emd", "Elna Embroidery Format",             'U', ' ', EMBFORMAT_STITCHONLY, readEmd, writeEmd},
    {".exp", "Melco Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, readExp, writeExp},
    {".exy", "Eltac Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, readExy, writeExy},
    {".eys", "Sierra Expanded Embroidery Format",  ' ', ' ', EMBFORMAT_STITCHONLY, readEys, writeEys},
    {".fxy", "Fortron Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, readFxy, writeFxy},
    {".gc",  "Smoothie G-Code Format",             ' ', ' ', EMBFORMAT_STITCHONLY, readGc, writeGc},
    {".gnc", "Great Notions Embroidery Format",    ' ', ' ', EMBFORMAT_STITCHONLY, readGnc, writeGnc},
    {".gt",  "Gold Thread Embroidery Format",      'U', ' ', EMBFORMAT_STITCHONLY, readGt, writeGt},
    {".hus", "Husqvarna Viking Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY, readHus, writeHus},
    {".inb", "Inbro Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, readInb, writeInb},
    {".inf", "Embroidery Color Format",            'U', 'U', EMBFORMAT_STITCHONLY, readInf, writeInf},
    {".jef", "Janome Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, readJef, writeJef},
    {".ksm", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, readKsm, writeKsm},
    {".max", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, readMax, writeMax},
    {".mit", "Mitsubishi Embroidery Format",       'U', ' ', EMBFORMAT_STITCHONLY, readMit, writeMit},
    {".new", "Ameco Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, readNew, writeNew},
    {".ofm", "Melco Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, readOfm, writeOfm},
    {".pcd", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, readPcd, writePcd},
    {".pcm", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, readPcm, writePcm},
    {".pcq", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, readPcq, writePcq},
    {".pcs", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, readPcs, writePcs},
    {".pec", "Brother Embroidery Format",          'U', 'U', EMBFORMAT_STITCHONLY, readPec, writePec},
    {".pel", "Brother Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY, readPel, writePel},
    {".pem", "Brother Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY, readPem, writePem},
    {".pes", "Brother Embroidery Format",          'U', 'U', EMBFORMAT_STITCHONLY, readPes, writePes},
    {".phb", "Brother Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, readPhb, writePhb},
    {".phc", "Brother Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, readPhc, writePhc},
    {".plt", "AutoCAD Plot Drawing Format",        'U', 'U', EMBFORMAT_STITCHONLY, readPlt, writePlt},
    {".rgb", "RGB Embroidery Format",              'U', 'U', EMBFORMAT_STITCHONLY, readRgb, writeRgb},
    {".sew", "Janome Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, readSew, writeSew},
    {".shv", "Husqvarna Viking Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY, readShv, writeShv},
    {".sst", "Sunstar Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, readSst, writeSst},
    {".stx", "Data Stitch Embroidery Format",      'U', ' ', EMBFORMAT_STITCHONLY, readStx, writeStx},
    {".svg", "Scalable Vector Graphics",           'U', 'U', EMBFORMAT_OBJECTONLY, readSvg, writeSvg},
    {".t01", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, readT01, writeT01},
    {".t09", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, readT09, writeT09},
    {".tap", "Happy Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, readTap, writeTap},
    {".thr", "ThredWorks Embroidery Format",       'U', 'U', EMBFORMAT_STITCHONLY, readThr, writeThr},
    {".txt", "Text File",                          ' ', 'U', EMBFORMAT_STITCHONLY, readTxt, writeTxt},
    {".u00", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, readU00, writeU00},
    {".u01", "Barudan Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY, readU01, writeU01},
    {".vip", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY, readVip, writeVip},
    {".vp3", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY, readVp3, writeVp3},
    {".xxx", "Singer Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY, readXxx, writeXxx},
    {".zsk", "ZSK USA Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY, readZsk, writeZsk}
};

const unsigned int NumberOfDifatEntriesInHeader = 109;
const unsigned int sizeOfFatEntry = sizeof(unsigned int);
static const unsigned int sizeOfDifatEntry = 4;
static const unsigned int sizeOfChainingEntryAtEndOfDifatSector = 4;
static const unsigned int sizeOfDirectoryEntry = 128;
static const int supportedMinorVersion = 0x003E;
static const int littleEndianByteOrderMark = 0xFFFE;

const double embConstantPi = 3.1415926535;

/* Returns an EmbArcObject. It is created on the stack. */
EmbArcObject embArcObject_make(double sx, double sy, double mx, double my, double ex, double ey)
{
    EmbArcObject stackArcObj;
    stackArcObj.arc.startX = sx;
    stackArcObj.arc.startY = sy;
    stackArcObj.arc.midX   = mx;
    stackArcObj.arc.midY   = my;
    stackArcObj.arc.endX   = ex;
    stackArcObj.arc.endY   = ey;
    return stackArcObj;
}

double radians(double degree)
{
    return degree*embConstantPi/180.0;
}

double degrees(double radian)
{
    return radian*180.0/embConstantPi;
}

/* Calculus based approach at determining whether a polygon is clockwise or counterclockwise.
 * Returns true if arc is clockwise. */
char isArcClockwise(EmbArc arc)
{
    double edge1 = (arc.midX-arc.startX)*(arc.midY+arc.startY);
    double edge2 = (arc.endX-arc.midX)*(arc.endY+arc.midY);
    double edge3 = (arc.startX-arc.endX)*(arc.startY+arc.endY);
    if (edge1 + edge2 + edge3 >= 0.0) {
        return 1;
    }
    return 0;
}

/* Calculates the CenterPoint of the Arc */
void getArcCenter(EmbArc arc, EmbVector* arcCenter)
{
    double ax = arc.midX - arc.startX;
    double ay = arc.midY - arc.startY;
    double aAngleInRadians = atan2(ay, ax);
    double aMidX = (arc.midX + arc.startX)/2.0;
    double aMidY = (arc.midY + arc.startY)/2.0;

    double paAngleInRadians = aAngleInRadians + radians(90.0);
    double pax = cos(paAngleInRadians);
    double pay = sin(paAngleInRadians);
    double aPerpX = aMidX + pax;
    double aPerpY = aMidY + pay;

    double bx = arc.endX - arc.midX;
    double by = arc.endY - arc.midY;
    double bAngleInRadians = atan2(by, bx);
    double bMidX = (arc.endX + arc.midX)/2.0;
    double bMidY = (arc.endY + arc.midY)/2.0;

    double pbAngleInRadians = bAngleInRadians + radians(90.0);
    double pbx = cos(pbAngleInRadians);
    double pby = sin(pbAngleInRadians);
    double bPerpX = bMidX + pbx;
    double bPerpY = bMidY + pby;

    EmbLine line1;
    EmbLine line2;
    line1 = embLine_make(aMidX, aMidY, aPerpX, aPerpY);
    line2 = embLine_make(bMidX, bMidY, bPerpX, bPerpY);
    embLine_intersectionPoint(line1, line2, arcCenter);
}

/* Calculates Arc Geometry from Bulge Data.
 * Returns false if there was an error calculating the data. */
char getArcDataFromBulge(double bulge,
                         double arcStartX,          double arcStartY,
                         double arcEndX,            double arcEndY,
                         /* returned data */
                         double* arcMidX,           double* arcMidY,
                         double* arcCenterX,        double* arcCenterY,
                         double* radius,            double* diameter,
                         double* chord,
                         double* chordMidX,         double* chordMidY,
                         double* sagitta,           double* apothem,
                         double* incAngleInDegrees, char*   clockwise)
{
    double incAngleInRadians;
    double chordAngleInRadians;
    double sagittaAngleInRadians;
    double w, h, fx ,fy, dx, dy;
    EmbArc arc;
    EmbVector arcCenter;

    /* Confirm the direction of the Bulge */
    if(bulge >= 0.0) { *clockwise = 0; }
    else             { *clockwise = 1; }

    /* Calculate the Included Angle in Radians */
    incAngleInRadians = atan(bulge)*4.0;

    /* Calculate the Chord */
    w = fabs(arcStartX-arcEndX);
    h = fabs(arcStartY-arcEndY);
    *chord = sqrt(w*w + h*h);

    /* Calculate the Radius */
    *radius = fabs(*chord / (2.0 * sin(incAngleInRadians / 2.0)));

    /* Calculate the Diameter */
    *diameter = fabs(*radius * 2.0);

    /* Calculate the Sagitta */
    *sagitta = fabs((*chord / 2.0) * bulge);

    /* Calculate the Apothem */
    *apothem = fabs(*radius - *sagitta);

    /* Calculate the Chord MidPoint */
    *chordMidX = (arcStartX + arcEndX) / 2.0;
    *chordMidY = (arcStartY + arcEndY) / 2.0;

    /* Calculate the Chord Angle (from arcStart to arcEnd) */
    dx = arcEndX - arcStartX;
    dy = arcEndY - arcStartY;
    chordAngleInRadians = atan2(dy, dx);

    /* Calculate the Sagitta Angle (from chordMid to arcMid) */
    if(*clockwise) sagittaAngleInRadians = chordAngleInRadians + radians(90.0);
    else           sagittaAngleInRadians = chordAngleInRadians - radians(90.0);

    /* Calculate the Arc MidPoint */
    fx = *sagitta * cos(sagittaAngleInRadians);
    fy = *sagitta * sin(sagittaAngleInRadians);
    *arcMidX = *chordMidX + fx;
    *arcMidY = *chordMidY + fy;

    arc.startX = arcStartX;
    arc.startY = arcStartY;
    arc.midX = *arcMidX;
    arc.midY = *arcMidY;
    arc.endX = arcEndX;
    arc.endY = arcEndY;
    getArcCenter(arc, &arcCenter);
    *arcCenterX = arcCenter.x;
    *arcCenterY = arcCenter.y;

    /* Convert the Included Angle from Radians to Degrees */
    *incAngleInDegrees = degrees(incAngleInRadians);

    /* Confirm the direction of the Arc, it should match the Bulge */
    if (*clockwise != isArcClockwise(arc)) {
        fprintf(stderr, "Arc and Bulge direction do not match.\n");
        return 0;
    }

    return 1;
}

/* Computational Geometry for Circles */

/****************************************************************
 * Calculates the intersection points of two overlapping circles.
 * Returns true if the circles intersect.
 * Returns false if the circles do not intersect.
 ****************************************************************/
int getCircleCircleIntersections(EmbCircle c0, EmbCircle c1,
                                 /* Intersection Point */
                                 double* px3, double* py3,
                                 /* Intersection Point */
                                 double* px4, double* py4)
{
    double a, h, px2, py2, mx, my;
    double dx = c1.centerX-c0.centerX;
    double dy = c1.centerY-c0.centerY;
    double d = sqrt(dx*dx + dy*dy); /* Distance between centers */

    /*Circles share centers. This results in division by zero,
      infinite solutions or one circle being contained within the other. */
    if(d == 0.0)
        return 0;
    /* Circles do not touch each other */
    else if(d > (c0.radius + c1.radius))
        return 0;
    /* One circle is contained within the other */
    else if(d < (c0.radius - c1.radius))
        return 0;

    /*
     * Considering the two right triangles p0p2p3 and p1p2p3 we can write:
     * a^2 + h^2 = r0^2 and b^2 + h^2 = r1^2
     *
     * BEGIN PROOF
     *
     * Remove h^2 from the equation by setting them equal to themselves:
     *     r0^2 - a^2 = r1^2 - b^2
     * Substitute b with (d - a) since it is proven that d = a + b:
     *     r0^2 - a^2 = r1^2 - (d - a)^2
     * Complete the square:
     *     r0^2 - a^2 = r1^2 - (d^2 -2da + a^2)
     * Subtract r1^2 from both sides:
     *     r0^2 - r1^2 - a^2 = -(d^2 -2da + a^2)
     * Invert the signs:
     *     r0^2 - r1^2 - a^2 = -d^2 + 2da - a^2
     * Adding a^2 to each side cancels them out:
     *     r0^2 - r1^2 = -d^2 + 2da
     * Add d^2 to both sides to shift it to the other side:
     *     r0^2 - r1^2 + d^2 = 2da
     * Divide by 2d to finally solve for a:
     *     a = (r0^2 - r1^2 + d^2)/ (2d)
     *
     * END PROOF
     */

    a = ((c0.radius*c0.radius) - (c1.radius*c1.radius) + (d*d)) / (2.0 * d);
    /* Solve for h by substituting a into a^2 + h^2 = r0^2 */
    h = sqrt((c0.radius*c0.radius) - (a*a));

    /*Find point p2 by adding the a offset in relation to line d to point p0 */
    px2 = c0.centerX + (dx * a/d);
    py2 = c0.centerY + (dy * a/d);

    /* Tangent circles have only one intersection

       TODO: using == in floating point arithmetic
       doesn't account for the machine accuracy, having
       a stated (double) tolerence value would help.
    */
    if(d == (c0.radius + c1.radius))
    {
        *px3 = *py4 = px2;
        *py3 = *py4 = py2;
        return 1;
    }

    /* Get the perpendicular slope by multiplying by the negative reciprocal
     * Then multiply by the h offset in relation to d to get the actual offsets */
    mx = -(dy * h/d);
    my =  (dx * h/d);

    /* Add the offsets to point p2 to obtain the intersection points */
    *px3 = px2 + mx;
    *py3 = py2 + my;
    *px4 = px2 - mx;
    *py4 = py2 - my;

    return 1;
}

/****************************************************************
 * Calculates the tangent points on circle from a given point.
 * Returns true if the given point lies outside the circle.
 * Returns false if the given point is inside the circle.
 ****************************************************************/
int getCircleTangentPoints(EmbCircle c,
                           /* Point to determine tangency */
                           double  px,  double  py,
                           /* Tangent Point 0 */
                           double* tx0, double* ty0,
                           /* Tangent Point 1 */
                           double* tx1, double* ty1)
{
    double pr;
    double dx  = px-c.centerX;
    double dy  = py-c.centerY;
    double hyp = sqrt(dx*dx + dy*dy); /* Distance to center of circle */
	EmbCircle p;
    /* Point is inside the circle */
    if (hyp < c.radius)
        return 0;
    /* Point is lies on the circle, so there is only one tangent point */
    else if(hyp == c.centerY)
    {
        *tx0 = *tx1 = px;
        *ty0 = *ty1 = py;
        return 1;
    }

    /* Since the tangent lines are always perpendicular to the radius, so
     * we can use the Pythagorean theorem to solve for the missing side */
    pr = sqrt((hyp*hyp) - (c.radius*c.radius));

    p.centerX = px;
    p.centerY = py;
   	p.radius = pr;
    return getCircleCircleIntersections(c, p,
                                        tx0, ty0,
                                        tx1, ty1);
}

/* Returns an EmbColor. It is created on the stack. */
EmbColor embColor_make(unsigned char r, unsigned char g, unsigned char b)
{
    EmbColor stackColor;
    stackColor.r = r;
    stackColor.g = g;
    stackColor.b = b;
    return stackColor;
}

/* Returns a pointer to an EmbColor. It is created on the heap. The caller is responsible for freeing the allocated memory. */
EmbColor* embColor_create(unsigned char r, unsigned char g, unsigned char b)
{
    EmbColor* heapColor = (EmbColor*)malloc(sizeof(EmbColor));
    if(!heapColor) { printf("ERROR: emb-color.c embColor_create(), cannot allocate memory for heapColor\n"); return 0; }
    heapColor->r = r;
    heapColor->g = g;
    heapColor->b = b;
    return heapColor;
}

/* Converts a 6 digit hex string (I.E. "00FF00") into an EmbColor and returns it. */
EmbColor embColor_fromHexStr(char* val)
{
    EmbColor color;
    char r[3];
    char g[3];
    char b[3];

    r[0] = val[0];
    r[1] = val[1];
    r[2] = 0;

    g[0] = val[2];
    g[1] = val[3];
    g[2] = 0;

    b[0] = val[4];
    b[1] = val[5];
    b[2] = 0;

    color.r = (unsigned char)strtol(r, 0, 16);
    color.g = (unsigned char)strtol(g, 0, 16);
    color.b = (unsigned char)strtol(b, 0, 16);
    return color;
}

double embEllipse_diameterX(EmbEllipse ellipse)
{
    return ellipse.radiusX * 2.0;
}

double embEllipse_diameterY(EmbEllipse ellipse)
{
    return ellipse.radiusY * 2.0;
}

double embEllipse_width(EmbEllipse ellipse)
{
    return ellipse.radiusX * 2.0;
}

double embEllipse_height(EmbEllipse ellipse)
{
    return ellipse.radiusY * 2.0;
}

/* Returns an EmbEllipseObject. It is created on the stack. */
EmbEllipseObject embEllipseObject_make(double cx, double cy, double rx, double ry)
{
    EmbEllipseObject stackEllipseObj;
    stackEllipseObj.ellipse.centerX = cx;
    stackEllipseObj.ellipse.centerY = cy;
    stackEllipseObj.ellipse.radiusX = rx;
    stackEllipseObj.ellipse.radiusY = ry;
    return stackEllipseObj;
}

/* Returns an EmbLine. It is created on the stack. */
EmbLine embLine_make(double x1, double y1, double x2, double y2)
{
    EmbLine line;
    line.x1 = x1;
    line.y1 = y1;
    line.x2 = x2;
    line.y2 = y2;
    return line;
}

/*! Finds the normalized vector perpendicular (clockwise) to the line
 * given by v1->v2 (normal to the line) */
void embLine_normalVector(EmbLine line, EmbVector* result, int clockwise)
{
    double temp;
    if (!result) {
        printf("ERROR: emb-line.c embLine_normalVector(), result argument is null\n");
        return;
    }
    result->x = line.x2 - line.x1;
    result->y = line.y2 - line.y1;
    embVector_normalize(*result, result);
    temp = result->x;
    result->x = result->y;
    result->y = -temp;
    if (!clockwise) {
        result->x = -result->x;
        result->y = -result->y;
    }
}

/**
 * Finds the intersection of two lines given by v1->v2 and v3->v4
 * and sets the value in the result variable.
 */
unsigned char embLine_intersectionPoint(EmbLine line1, EmbLine line2, EmbVector* result)
{
    double tolerence = 1e-10;
    double A2 = line1.y2 - line1.y1;
    double B2 = line1.x1 - line1.x2;
    double C2 = A2 * line1.x1 + B2 * line1.y1;

    double A1 = line2.y2 - line2.y1;
    double B1 = line2.x1 - line2.x2;
    double C1 = A1 * line2.x1 + B1 * line2.y1;

    double det = A1 * B2 - A2 * B1;

    if (!result) {
        printf("ERROR: emb-line.c embLine_intersectionPoint(), result argument is null\n");
        return 0;
    }
    /*TODO: The code below needs revised since division by zero can still occur */
    if (fabs(det) < tolerence) {
        printf("ERROR: Intersecting lines cannot be parallel.\n");
        return 0;
    }
    result->x = (B2 * C1 - B1 * C2) / det;
    result->y = (A1 * C2 - A2 * C1) / det;
    return 1;
}

void husExpand(unsigned char* input, unsigned char* output, int compressedSize, int _269) {}
int husCompress(unsigned char* _266, unsigned long _inputSize, unsigned char* _267, int _269, int _235) { return 0; }

EmbArray* embArray_create(int type)
{
    EmbArray *p;
    p = (EmbArray*)malloc(sizeof(EmbArray));
    p->type = type;
    p->length = CHUNK_SIZE;
    p->count = 0;
    switch (p->type) {
    case EMB_ARC:
        p->arc = (EmbArcObject*)malloc(CHUNK_SIZE*sizeof(EmbArcObject));
        break;
    case EMB_CIRCLE:
        p->circle = (EmbCircleObject*)malloc(CHUNK_SIZE*sizeof(EmbCircleObject));
        break;
    case EMB_ELLIPSE:
        p->ellipse = (EmbEllipseObject*)malloc(CHUNK_SIZE*sizeof(EmbEllipseObject));
        break;
    case EMB_FLAG:
        p->flag = (int*)malloc(CHUNK_SIZE*sizeof(int));
        break;
    case EMB_PATH:
        p->path = (EmbPathObject**)malloc(CHUNK_SIZE*sizeof(EmbPathObject));
        break;
    case EMB_POINT:
        p->point = (EmbPointObject*)malloc(CHUNK_SIZE*sizeof(EmbPointObject));
        break;
    case EMB_LINE:
        p->line = (EmbLineObject*)malloc(CHUNK_SIZE*sizeof(EmbLineObject));
        break;
    case EMB_POLYGON:
        p->polygon = (EmbPolygonObject**)malloc(CHUNK_SIZE*sizeof(EmbPolygonObject*));
        break;
    case EMB_POLYLINE:
        p->polyline = (EmbPolylineObject**)malloc(CHUNK_SIZE*sizeof(EmbPolylineObject*));
        break;
    case EMB_RECT:
        p->rect = (EmbRectObject*)malloc(CHUNK_SIZE*sizeof(EmbRectObject));
        break;
    case EMB_SPLINE:
        p->spline = (EmbSplineObject*)malloc(CHUNK_SIZE*sizeof(EmbSplineObject));
        break;
    case EMB_STITCH:
        p->stitch = (EmbStitch*)malloc(CHUNK_SIZE*sizeof(EmbStitch));
        break;
    case EMB_THREAD:
        p->thread = (EmbThread*)malloc(CHUNK_SIZE*sizeof(EmbThread));
        break;
    case EMB_VECTOR:
        p->vector = (EmbVector*)malloc(CHUNK_SIZE*sizeof(EmbVector));
        break;
    default:
        break;
    }
    return p;
}

int embArray_resize(EmbArray *p)
{
    if (p->count < p->length) return 1;
    p->length += CHUNK_SIZE;
    switch (p->type) {
    case EMB_ARC:
        p->arc = realloc(p->arc, p->length*sizeof(EmbArcObject));
        if (!p->arc) return 1;
        break;
    case EMB_CIRCLE:
        p->circle = realloc(p->circle, p->length*sizeof(EmbCircleObject));
        if (!p->circle) return 1;
        break;
    case EMB_ELLIPSE:
        p->ellipse = realloc(p->ellipse, p->length*sizeof(EmbEllipseObject));
        if (!p->ellipse) return 1;
        break;
    case EMB_FLAG:
        p->flag = realloc(p->flag, p->length*sizeof(int));
        if (!p->flag) return 1;
        break;
    case EMB_PATH:
        p->path = realloc(p->path, p->length*sizeof(EmbPathObject*));
        if (!p->path) return 1;
        break;
    case EMB_POINT:
        p->point = realloc(p->point, p->length*sizeof(EmbPointObject));
        if (!p->point) return 1;
        break;
    case EMB_LINE:
        p->line = realloc(p->line, p->length*sizeof(EmbLineObject));
        if (!p->line) return 1;
        break;
    case EMB_POLYGON:
        p->polygon = realloc(p->polygon, p->length*sizeof(EmbPolygonObject*));
        if (!p->polygon) return 1;
        break;
    case EMB_POLYLINE:
        p->polyline = realloc(p->polyline, p->length*sizeof(EmbPolylineObject*));
        if (!p->polyline) return 1;
        break;
    case EMB_RECT:
        p->rect = realloc(p->rect, p->length*sizeof(EmbRectObject));
        if (!p->rect) return 1;
        break;
    case EMB_SPLINE:
        p->spline = realloc(p->spline, p->length*sizeof(EmbSplineObject));
        if (!p->spline) return 1;
        break;
    case EMB_STITCH:
        p->stitch = realloc(p->stitch, CHUNK_SIZE*sizeof(EmbStitch));
        if (!p->stitch) return 1;
        break;
    case EMB_THREAD:
        p->thread = realloc(p->thread, CHUNK_SIZE*sizeof(EmbThread));
        if (!p->thread) return 1;
        break;
    case EMB_VECTOR:
        p->vector = realloc(p->vector, CHUNK_SIZE*sizeof(EmbVector));
        if (!p->vector) return 1;
        break;
    default:
        break;
    }
    return 0;
}

int embArray_addArc(EmbArray* p, EmbArc arc, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->arc[p->count - 1].arc = arc;
    p->arc[p->count - 1].lineType = lineType;
    p->arc[p->count - 1].color = color;
    return 1;
}

int embArray_addCircle(EmbArray* p, EmbCircle circle, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->circle[p->count - 1].circle = circle;
    p->circle[p->count - 1].lineType = lineType;
    p->circle[p->count - 1].color = color;
    return 1;
}

int embArray_addEllipse(EmbArray* p,
    EmbEllipse ellipse, double rotation, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->ellipse[p->count - 1].ellipse = ellipse;
    p->ellipse[p->count - 1].rotation = rotation;
    p->ellipse[p->count - 1].lineType = lineType;
    p->ellipse[p->count - 1].color = color;
    return 1;
}

int embArray_addFlag(EmbArray* p, int flag)
{
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->flag[p->count - 1] = flag;
    return 1;
}

int embArray_addLine(EmbArray* p, EmbLineObject line)
{
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->line[p->count - 1] = line;
    return 1;
}

int embArray_addPath(EmbArray* p, EmbPathObject *path)
{
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->path[p->count - 1] = (EmbPathObject*)malloc(sizeof(EmbPathObject));
    if (!p->path[p->count - 1]) {
        printf("ERROR: emb-polygon.c embArray_create(), cannot allocate memory for heapPolygonObj\n");
        return 0;
    }
    p->path[p->count - 1] = path;
    return 1;
}

int embArray_addPoint(EmbArray* p, EmbPointObject *point)
{
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->point[p->count - 1] = *point;
    return 1;
}

int embArray_addPolygon(EmbArray* p, EmbPolygonObject *polygon)
{
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->polygon[p->count - 1] = (EmbPolygonObject*)malloc(sizeof(EmbPolygonObject));
    if (!p->polygon[p->count - 1]) {
        printf("ERROR: emb-polygon.c embArray_create(), cannot allocate memory for heapPolygonObj\n");
        return 0;
    }
    p->polygon[p->count - 1] = polygon;
    return 1;
}

int embArray_addPolyline(EmbArray* p, EmbPolylineObject *polyline)
{
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->polyline[p->count - 1] = (EmbPolylineObject*)malloc(sizeof(EmbPolylineObject));
    if (!p->polyline[p->count - 1]) {
        printf("ERROR: emb-polyline.c embArray_create(), cannot allocate memory for heapPolylineObj\n");
        return 0;
    }
    p->polyline[p->count - 1] = polyline;
    return 1;
}

int embArray_addRect(EmbArray* p,
    EmbRect rect, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->rect[p->count - 1].rect = rect;
    p->rect[p->count - 1].lineType = lineType;
    p->rect[p->count - 1].color = color;
    return 1;
}

int embArray_addStitch(EmbArray* p,
    double x, double y, int flag, int color)
{
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->stitch[p->count - 1].x = x;
    p->stitch[p->count - 1].y = y;
    p->stitch[p->count - 1].flags = flag;
    p->stitch[p->count - 1].color = color;
    return 1;
}

int embArray_addThread(EmbArray* p, EmbThread thread)
{
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->thread[p->count - 1] = thread;
    return 1;
}

int embArray_addVector(EmbArray* p, EmbVector vector)
{
    p->count++;
    if (!embArray_resize(p)) return 0;
    p->vector[p->count - 1] = vector;
    return 1;
}

void embArray_free(EmbArray* p)
{
    int i;
    if (!p) return;

    switch (p->type) {
    case EMB_ARC:
        free(p->arc);
        break;
    case EMB_CIRCLE:
        free(p->circle);
        break;
    case EMB_ELLIPSE:
        free(p->ellipse);
        break;
    case EMB_FLAG:
        free(p->flag);
        break;
    case EMB_LINE:
        free(p->line);
        break;
    case EMB_PATH:
        for (i=0; i<p->count; i++) {
            embArray_free(p->path[i]->pointList);
        }
        free(p->path);
        break;
    case EMB_POINT:
        free(p->point);
        break;
    case EMB_POLYGON:
        for (i=0; i<p->count; i++) {
            embArray_free(p->polygon[i]->pointList);
        }
        free(p->polygon);
        break;
    case EMB_POLYLINE:
        for (i=0; i<p->count; i++) {
            embArray_free(p->polyline[i]->pointList);
        }
        free(p->polygon);
        break;
    case EMB_RECT:
        free(p->rect);
        break;
    case EMB_SPLINE:
        free(p->spline);
        break;
    case EMB_STITCH:
        free(p->stitch);
        break;
    case EMB_THREAD:
        free(p->thread);
        break;
    case EMB_VECTOR:
        free(p->vector);
        break;
    default:
        break;
    }
    free(p);
    p = 0;
}

/**
 * Argument validator and stitchList checker.
 * Saves making these 4 checks seperately for every file type.
 */
int validateWritePattern(EmbPattern *pattern, const char* fileName, const char *function)
{
    if (!pattern) {
        printf("ERROR: %s(), pattern argument is null\n", function);
        return 0;
    }
    if (!fileName) {
        printf("ERROR: %s(), fileName argument is null\n", function);
        return 0;
    }

    if (!embStitchList_count(pattern->stitchList)) {
        printf("ERROR: %s(), pattern contains no stitches\n", function);
        return 0;
    }
    
    /* Check for an END stitch and add one if it is not present */
    if (pattern->lastStitch->stitch.flags != END) {
        embPattern_addStitchRel(pattern, 0, 0, END, 1);
    }

    return 1;
}

/**
 * Argument validator for reading patterns.
 */
int validateReadPattern(EmbPattern *pattern, const char* fileName, const char *function)
{
    if (!pattern) {
        printf("ERROR: %s(), pattern argument is null\n", function);
        return 0;
    }
    if (!fileName) {
        printf("ERROR: %s(), fileName argument is null\n", function);
        return 0;
    }
    return 1;
}

EmbFile* embFile_open(const char* fileName, const char* mode, int optional)
{
    EmbFile* eFile = 0;
    FILE* oFile = fopen(fileName, mode);
    if (!oFile) {
        if (!optional) {
            printf("ERROR: Cannot open %s in mode %s.", fileName, mode);
        }
        return 0;
    }

    eFile = (EmbFile*)malloc(sizeof(EmbFile));
    if (!eFile) {
        if (!optional) {
            printf("ERROR: Cannot allocate memory for EmbFile with arguments (%s, %s, 0).",
                fileName, mode);
        }
        fclose(oFile);
        return 0;
    }

    eFile->file = oFile;
    return eFile;
}

int embFile_close(EmbFile* stream)
{
    int retVal = fclose(stream->file);
    free(stream);
    return retVal;
}

char embFile_getc(EmbFile* stream)
{
    return fgetc(stream->file);
}

void embFile_readline(EmbFile* stream, char *line, int maxLength)
{
    int state = 0, i;
    char c;
    for (i=0; i<maxLength-1; i++) {
        c = embFile_getc(stream);
        if (feof(stream->file)) {
            break;
        }
        if (c == '\r') {
            c = embFile_getc(stream);
            if (c != '\n') {
                embFile_seek(stream, -1L, SEEK_CUR);
            }
            break;
        }
        if (c == '\n') {
            break;
        }
        *line = c;
        line++;
        c = embFile_getc(stream);
    }
    *line = 0;
}

size_t embFile_read(void* ptr, size_t size, size_t nmemb, EmbFile* stream)
{
    return fread(ptr, size, nmemb, stream->file);
}

size_t embFile_write(const void* ptr, size_t size, size_t nmemb, EmbFile* stream)
{
    return fwrite(ptr, size, nmemb, stream->file);
}

int embFile_seek(EmbFile* stream, long offset, int origin)
{
    return fseek(stream->file, offset, origin);
}

long embFile_tell(EmbFile* stream)
{
    return ftell(stream->file);
}

EmbFile* embFile_tmpfile(void)
{
    EmbFile* eFile = 0;
    FILE* tFile = tmpfile();
    if (!tFile)
        return 0;

    eFile = (EmbFile*)malloc(sizeof(EmbFile));
    if (!eFile) {
        fclose(tFile);
        return 0;
    }

    eFile->file = tFile;
    return eFile;
}

int embFile_putc(int ch, EmbFile* stream)
{
    return fputc(ch, stream->file);
}

int embFile_printf(EmbFile* stream, const char* format, ...)
{
    int retVal;
    va_list args;
    va_start(args, format);
    retVal = vfprintf(stream->file, format, args);
    va_end(args);
    return retVal;
}

static unsigned int sectorSize(bcf_file* bcfFile)
{
    /* version 3 uses 512 byte */
    if (bcfFile->header.majorVersion == 3) {
        return 512;
    } else if (bcfFile->header.majorVersion == 4) {
        return 4096;
    }
    return 4096;
}

static int haveExtraDIFATSectors(bcf_file* file)
{
    return (int)(numberOfEntriesInDifatSector(file->difat) > 0);
}

static int seekToOffset(EmbFile* file, const unsigned int offset)
{
    return embFile_seek(file, offset, SEEK_SET);
}

static int seekToSector(bcf_file* bcfFile, EmbFile* file, const unsigned int sector)
{
    unsigned int offset = sector * sectorSize(bcfFile) + sectorSize(bcfFile);
    return seekToOffset(file, offset);
}

static void parseDIFATSectors(EmbFile* file, bcf_file* bcfFile)
{
    unsigned int numberOfDifatEntriesStillToRead = bcfFile->header.numberOfFATSectors - NumberOfDifatEntriesInHeader;
    unsigned int difatSectorNumber = bcfFile->header.firstDifatSectorLocation;
    while ((difatSectorNumber != CompoundFileSector_EndOfChain) && (numberOfDifatEntriesStillToRead > 0)) {
        seekToSector(bcfFile, file, difatSectorNumber);
        difatSectorNumber = readFullSector(file, bcfFile->difat, &numberOfDifatEntriesStillToRead);
    }
}

int bcfFile_read(EmbFile* file, bcf_file* bcfFile)
{
    unsigned int i, numberOfDirectoryEntriesPerSector, directorySectorToReadFrom;

    bcfFile->header = bcfFileHeader_read(file);
    if (!bcfFileHeader_isValid(bcfFile->header)) {
        printf("Failed to parse header\n");
        return 0;
    }

    bcfFile->difat = bcf_difat_create(file, bcfFile->header.numberOfFATSectors, sectorSize(bcfFile));
    if (haveExtraDIFATSectors(bcfFile)) {
        parseDIFATSectors(file, bcfFile);
    }

    bcfFile->fat = bcfFileFat_create(sectorSize(bcfFile));
    for (i = 0; i < bcfFile->header.numberOfFATSectors; ++i) {
        unsigned int fatSectorNumber = bcfFile->difat->fatSectorEntries[i];
        seekToSector(bcfFile, file, fatSectorNumber);
        loadFatFromSector(bcfFile->fat, file);
    }

    numberOfDirectoryEntriesPerSector = sectorSize(bcfFile) / sizeOfDirectoryEntry;
    bcfFile->directory = CompoundFileDirectory(numberOfDirectoryEntriesPerSector);
    directorySectorToReadFrom = bcfFile->header.firstDirectorySectorLocation;
    while (directorySectorToReadFrom != CompoundFileSector_EndOfChain) {
        seekToSector(bcfFile, file, directorySectorToReadFrom);
        readNextSector(file, bcfFile->directory);
        directorySectorToReadFrom = bcfFile->fat->fatEntries[directorySectorToReadFrom];
    }

    return 1;
}

EmbFile* GetFile(bcf_file* bcfFile, EmbFile* file, char* fileToFind)
{
    int filesize, sectorSize, currentSector, sizeToWrite, currentSize, totalSectors, i;
    char* input = 0;
    EmbFile* fileOut = embFile_tmpfile();
    bcf_directory_entry* pointer = bcfFile->directory->dirEntries;
    while (pointer) {
        if (strcmp(fileToFind, pointer->directoryEntryName) == 0)
            break;
        pointer = pointer->next;
    }
    filesize = pointer->streamSize;
    sectorSize = bcfFile->difat->sectorSize;
    input = (char*)malloc(sectorSize);
    if (!input) {
        printf("ERROR: compound-file.c GetFile(), cannot allocate memory for input\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    currentSize = 0;
    currentSector = pointer->startingSectorLocation;
    totalSectors = (int)ceil((float)filesize / sectorSize);
    for (i = 0; i < totalSectors; i++) {
        seekToSector(bcfFile, file, currentSector);
        sizeToWrite = filesize - currentSize;
        if (sectorSize < sizeToWrite) {
            sizeToWrite = sectorSize;
        }
        embFile_read(input, 1, sizeToWrite, file);
        embFile_write(input, 1, sizeToWrite, fileOut);
        currentSize += sizeToWrite;
        currentSector = bcfFile->fat->fatEntries[currentSector];
    }
    free(input);
    input = 0;
    return fileOut;
}

void bcf_file_free(bcf_file* bcfFile)
{
    bcf_file_difat_free(bcfFile->difat);
    bcfFile->difat = 0;
    bcf_file_fat_free(bcfFile->fat);
    bcfFile->fat = 0;
    bcf_directory_free(bcfFile->directory);
    bcfFile->directory = 0;
    free(bcfFile);
    bcfFile = 0;
}

bcf_file_difat* bcf_difat_create(EmbFile* file, unsigned int fatSectors, const unsigned int sectorSize)
{
    unsigned int i;
    bcf_file_difat* difat = 0;
    unsigned int sectorRef;

    difat = (bcf_file_difat*)malloc(sizeof(bcf_file_difat));
    if (!difat) {
        printf("ERROR: compound-file-difat.c bcf_difat_create(), cannot allocate memory for difat\n");
    } /* TODO: avoid crashing. null pointer will be accessed */

    difat->sectorSize = sectorSize;
    if (fatSectors > NumberOfDifatEntriesInHeader) {
        fatSectors = NumberOfDifatEntriesInHeader;
    }

    for (i = 0; i < fatSectors; ++i) {
        sectorRef = binaryReadUInt32(file);
        difat->fatSectorEntries[i] = sectorRef;
    }
    difat->fatSectorCount = fatSectors;
    for (i = fatSectors; i < NumberOfDifatEntriesInHeader; ++i) {
        sectorRef = binaryReadUInt32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf("ERROR: compound-file-difat.c bcf_difat_create(), Unexpected sector value %x at DIFAT[%d]\n", sectorRef, i);
        }
    }
    return difat;
}

unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat)
{
    return (fat->sectorSize - sizeOfChainingEntryAtEndOfDifatSector) / sizeOfDifatEntry;
}

unsigned int readFullSector(EmbFile* file, bcf_file_difat* bcfFile, unsigned int* numberOfDifatEntriesStillToRead)
{
    unsigned int i;
    unsigned int sectorRef;
    unsigned int nextDifatSectorInChain;
    unsigned int entriesToReadInThisSector = 0;
    if (*numberOfDifatEntriesStillToRead > numberOfEntriesInDifatSector(bcfFile)) {
        entriesToReadInThisSector = numberOfEntriesInDifatSector(bcfFile);
        *numberOfDifatEntriesStillToRead -= entriesToReadInThisSector;
    } else {
        entriesToReadInThisSector = *numberOfDifatEntriesStillToRead;
        *numberOfDifatEntriesStillToRead = 0;
    }

    for (i = 0; i < entriesToReadInThisSector; ++i) {
        sectorRef = binaryReadUInt32(file);
        bcfFile->fatSectorEntries[bcfFile->fatSectorCount] = sectorRef;
        bcfFile->fatSectorCount++;
    }
    for (i = entriesToReadInThisSector; i < numberOfEntriesInDifatSector(bcfFile); ++i) {
        sectorRef = binaryReadUInt32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf("ERROR: compound-file-difat.c readFullSector(), Unexpected sector value %x at DIFAT[%d]]\n", sectorRef, i);
        }
    }
    nextDifatSectorInChain = binaryReadUInt32(file);
    return nextDifatSectorInChain;
}

void bcf_file_difat_free(bcf_file_difat* difat)
{
    free(difat);
    difat = 0;
}

static void parseDirectoryEntryName(EmbFile* file, bcf_directory_entry* dir)
{
    int i;
    unsigned short unicodechar;
    for (i = 0; i < 32; ++i) {
        unicodechar = binaryReadUInt16(file);
        if (unicodechar != 0x0000) {
            dir->directoryEntryName[i] = (char)unicodechar;
        }
    }
}

static void readCLSID(EmbFile* file, bcf_directory_entry* dir)
{
    int i;
    unsigned char scratch;
    const int guidSize = 16;
    for (i = 0; i < guidSize; ++i) {
        scratch = binaryReadByte(file);
        dir->CLSID[i] = scratch;
    }
}

bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries)
{
    bcf_directory* dir = (bcf_directory*)malloc(sizeof(bcf_directory));
    if (!dir) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectory(), cannot allocate memory for dir\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    dir->maxNumberOfDirectoryEntries = maxNumberOfDirectoryEntries;
    dir->dirEntries = 0;
    return dir;
}

EmbTime parseTime(EmbFile* file)
{
    EmbTime returnVal;
    unsigned int ft_low, ft_high;
    /*embTime_time(&returnVal); TODO: use embTime_time() rather than time(). */
    ft_low = binaryReadInt32(file);
    ft_high = binaryReadInt32(file);
    /* TODO: translate to actual date time */
    return returnVal;
}

bcf_directory_entry* CompoundFileDirectoryEntry(EmbFile* file)
{
    bcf_directory_entry* dir = (bcf_directory_entry*)malloc(sizeof(bcf_directory_entry));
    if (!dir) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectoryEntry(), cannot allocate memory for dir\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    memset(dir->directoryEntryName, 0, 32);
    parseDirectoryEntryName(file, dir);
    dir->next = 0;
    dir->directoryEntryNameLength = binaryReadUInt16(file);
    dir->objectType = (unsigned char)binaryReadByte(file);
    if ((dir->objectType != ObjectTypeStorage) && (dir->objectType != ObjectTypeStream) && (dir->objectType != ObjectTypeRootEntry)) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectoryEntry(), unexpected object type: %d\n", dir->objectType);
        return 0;
    }
    dir->colorFlag = (unsigned char)binaryReadByte(file);
    dir->leftSiblingId = binaryReadUInt32(file);
    dir->rightSiblingId = binaryReadUInt32(file);
    dir->childId = binaryReadUInt32(file);
    readCLSID(file, dir);
    dir->stateBits = binaryReadUInt32(file);
    dir->creationTime = parseTime(file);
    dir->modifiedTime = parseTime(file);
    dir->startingSectorLocation = binaryReadUInt32(file);
    dir->streamSize = binaryReadUInt32(file); /* This should really be __int64 or long long, but for our uses we should never run into an issue */
    dir->streamSizeHigh = binaryReadUInt32(file); /* top portion of int64 */
    return dir;
}

void readNextSector(EmbFile* file, bcf_directory* dir)
{
    unsigned int i;
    for (i = 0; i < dir->maxNumberOfDirectoryEntries; ++i) {
        bcf_directory_entry* dirEntry = CompoundFileDirectoryEntry(file);
        bcf_directory_entry* pointer = dir->dirEntries;
        if (!pointer) {
            dir->dirEntries = dirEntry;
        } else {
            while (pointer) {
                if (!pointer->next) {
                    pointer->next = dirEntry;
                    break;
                }
                pointer = pointer->next;
            }
        }
    }
}

void bcf_directory_free(bcf_directory* dir)
{
    bcf_directory_entry* pointer = dir->dirEntries;
    bcf_directory_entry* entryToFree = 0;
    while (pointer) {
        entryToFree = pointer;
        pointer = pointer->next;
        free(entryToFree);
        entryToFree = 0;
    }
    if (dir) {
        free(dir);
        dir = 0;
    }
}

bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize)
{
    bcf_file_fat* fat = (bcf_file_fat*)malloc(sizeof(bcf_file_fat));
    if (!fat) {
        printf("ERROR: compound-file-fat.c bcfFileFat_create(), cannot allocate memory for fat\n");
    } /* TODO: avoid crashing. null pointer will be accessed */
    fat->numberOfEntriesInFatSector = sectorSize / sizeOfFatEntry;
    fat->fatEntryCount = 0;
    return fat;
}

void loadFatFromSector(bcf_file_fat* fat, EmbFile* file)
{
    unsigned int i;
    unsigned int currentNumberOfFatEntries = fat->fatEntryCount;
    unsigned int newSize = currentNumberOfFatEntries + fat->numberOfEntriesInFatSector;
    for (i = currentNumberOfFatEntries; i < newSize; ++i) {
        unsigned int fatEntry = binaryReadUInt32(file);
        fat->fatEntries[i] = fatEntry;
    }
    fat->fatEntryCount = newSize;
}

void bcf_file_fat_free(bcf_file_fat* fat)
{
    free(fat);
    fat = 0;
}

bcf_file_header bcfFileHeader_read(EmbFile* file)
{
    bcf_file_header header;
    binaryReadBytes(file, header.signature, 8);
    binaryReadBytes(file, header.CLSID, 16);
    header.minorVersion = binaryReadUInt16(file);
    header.majorVersion = binaryReadUInt16(file);
    header.byteOrder = binaryReadUInt16(file);
    header.sectorShift = binaryReadUInt16(file);
    header.miniSectorShift = binaryReadUInt16(file);
    header.reserved1 = binaryReadUInt16(file);
    header.reserved2 = (unsigned int)binaryReadUInt32(file);
    header.numberOfDirectorySectors = (unsigned int)binaryReadUInt32(file);
    header.numberOfFATSectors = (unsigned int)binaryReadUInt32(file);
    header.firstDirectorySectorLocation = (unsigned int)binaryReadUInt32(file);
    header.transactionSignatureNumber = (unsigned int)binaryReadUInt32(file);
    header.miniStreamCutoffSize = (unsigned int)binaryReadUInt32(file);
    header.firstMiniFATSectorLocation = (unsigned int)binaryReadUInt32(file);
    header.numberOfMiniFatSectors = (unsigned int)binaryReadUInt32(file);
    header.firstDifatSectorLocation = (unsigned int)binaryReadUInt32(file);
    header.numberOfDifatSectors = (unsigned int)binaryReadUInt32(file);
    return header;
}

int bcfFileHeader_isValid(bcf_file_header header)
{
    if (memcmp(header.signature, "\xd0\xcf\x11\xe0\xa1\xb1\x1a\xe1", 8) != 0) {
        printf("bad header signature\n");
        return 0;
    }
    return 1;
}

/**************************************************/
/* EmbFormatList                                  */
/**************************************************/

int embFormat_getExtension(const char *fileName, char *ending)
{
    int i;
    const char *offset;

    if (!fileName) {
        printf("ERROR: emb-format.c embFormat_getExtension(), fileName argument is null\n");
        return 0;
    }

    if (strlen(fileName) == 0) {
        return 0;
    }
    
    offset = strrchr(fileName, '.');
    if (offset==0) {
        return 0;
    }

    i = 0;
    while (offset[i] != '\0') {
        ending[i] = (char)tolower(offset[i]);
        ++i;
    }
    ending[i] = 0; /* terminate the string */

    return 1;
}

#if 0

struct StitchBlock
{
    IThread Thread { get; set; }
    double Angle { get; set; }
    List<VectorStitch> Stitches { get; set; }
}

double LineLength(EmbPoint a1, EmbPoint a2)
{
    return sqrt(pow(a2.x - a1.x, 2) + pow(a2.y - a1.y, 2));
}

double DistancePointPoint(Vector2 p, Vector2 p2)
{
    double dx = p.X - p2.X;
    double dy = p.Y - p2.X;
    return sqrt(dx * dx + dy * dy);
}

float GetRelativeX(EmbPoint a1, EmbPoint a2, Point a3)
{
    return ((a1.X - a2.X) * (a3.X - a2.X) + (a1.Y - a2.Y) * (a3.Y - a2.Y));
}

float GetRelativeY(EmbPoint a1, EmbPoint a2, EmbPoint a3)
{
    return ((a1.X - a2.X) * (a3.Y - a2.Y) - (a1.Y - a2.Y) * (a3.X - a2.X));
}

double GetAngle(VectorStitch vs, VectorStitch vs2)
{
    return atan((vs2.Xy.X - vs.Xy.X)/(vs2.Xy.Y - vs.Xy.Y));
}

StitchBlock* BreakIntoColorBlocks(EmbPattern pattern)
{
    var sa2 = new StitchBlock();
    int oldColor = pattern.StitchList[0].ColorIndex;
    var color = pattern.ColorList[oldColor];
    sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
    foreach (Stitch s in pattern.stitchList)
    {
        if (s.ColorIndex != oldColor)
        {
            yield return sa2;
            sa2 = new StitchBlock();
            color = pattern.ColorList[s.ColorIndex];
            sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
            oldColor = s.ColorIndex;
        }
        var vs = new VectorStitch { Xy = new Point(s.X, s.Y), Color = s.ColorIndex };
        sa2.Stitches.Add(vs);
    }
    yield return sa2;
}



StitchBlock * BreakIntoSeparateObjects(EmbStitchBlock* blocks)
{
    double previousAngle = 0.0;
    foreach (var block in blocks)
    {
        var stitches = new List<VectorStitch>();
        block.Stitches[0].Type = VectorStitchType.Contour;
        block.Stitches[block.Stitches.Count - 1].Type = VectorStitchType.Contour;

        for (int i = 0; i < block.Stitches.Count - 2; i++) // step 0
        {
            double dx = (GetRelativeX(block.Stitches[i].Xy, block.Stitches[i + 1].Xy, block.Stitches[i + 2].Xy));
            block.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
            block.Stitches[i].Angle = GetAngle(block.Stitches[i], block.Stitches[i + 1]);
            stitches.Add(block.Stitches[i].Clone());
            if (i > 0)
            {
                if ((block.Stitches[i].Type == VectorStitchType.Contour) && Math.Abs(block.Stitches[i].Angle - previousAngle) > (20/180*embConstantPi))
                {
                    yield return
                        new StitchBlock
                            {
                                Stitches = stitches,
                                Angle = stitches.Average(x => x.Angle),
                                Thread = new Thread(block.Thread.Red, block.Thread.Blue, block.Thread.Green)
                            };
                    stitches = new List<VectorStitch>();

                }
            }
        }

        //for (int i = 1; i < sa.Stitches.Count - 3; i++) // step 1
        //{
        //    if (sa.Stitches[i + 1].Type == VectorStitchType.Contour)
        //    {
        //        //float dy = GetRelativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY);
        //        //float dy2 = GetRelativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY);
        //        //float dy3 = GetRelativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY);
        //        //if(dy)
        //        if (sa.Stitches[i - 1].Type == VectorStitchType.Run || sa.Stitches[i + 1].Type == VectorStitchType.Run)
        //        {
        //            sa.Stitches[i].Type = VectorStitchType.Tatami;
        //        }
        //        else
        //        {
        //            sa.Stitches[i].Type = VectorStitchType.Satin;
        //        }
        //    }
        //}
    }
}

StitchObject * FindOutline(EmbStitchBlock* stitchData)
{
    int currColorIndex = 0;
    var pOdd = new List<Point>();
    var pEven = new List<Point>();
    foreach (StitchBlock sa in stitchData)
    {
        if (sa.Stitches.Count > 0)
        {
            sa.Stitches[0].Type = VectorStitchType.Contour;
            sa.Stitches[sa.Stitches.Count - 1].Type = VectorStitchType.Contour;
            for (int i = 0; i < sa.Stitches.Count - 2; i++) // step 0
            {
                float dx = (GetRelativeX(sa.Stitches[i].Xy, sa.Stitches[i + 1].Xy, sa.Stitches[i + 2].Xy));
                sa.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
                sa.Stitches[i].Angle = GetAngle(sa.Stitches[i], sa.Stitches[i + 1]);
            }
            //for (int i = 1; i < sa.Stitches.Count - 3; i++) // step 1
            //{
            //    if (sa.Stitches[i + 1].Type == VectorStitchType.Contour)
            //    {
            //        //float dy = GetRelativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY);
            //        //float dy2 = GetRelativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY);
            //        //float dy3 = GetRelativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY);
            //        //if(dy)
            //        if (sa.Stitches[i - 1].Type == VectorStitchType.Run || sa.Stitches[i + 1].Type == VectorStitchType.Run)
            //        {
            //            sa.Stitches[i].Type = VectorStitchType.Tatami;
            //        }
            //        else
            //        {
            //            sa.Stitches[i].Type = VectorStitchType.Satin;
            //        }
            //    }
            //}
        }


        int oddEven = 0;
        foreach (VectorStitch t in sa.Stitches)
        {
            if ((t.Type == VectorStitchType.Contour) && (oddEven % 2) == 0)
            {
                pEven.Add(t.Xy);

                oddEven++;
            }
            else if ((t.Type == VectorStitchType.Contour) && (oddEven % 2) == 1)
            {
                pOdd.Add(t.Xy);
                oddEven++;
            }
        }
        currColorIndex++;
        var so = new StitchObject { SideOne = pEven, SideTwo = pOdd, ColorIndex = currColorIndex };
        yield return so;
        pEven = new List<Point>();
        pOdd = new List<Point>();
        //break;
    }
}

EmbPattern DrawGraphics(EmbPattern p)
{
    var stitchData = BreakIntoColorBlocks(p);


    //var outBlock = new List<StitchBlock>(BreakIntoSeparateObjects(stitchData));
    //foreach(var block in stitchData)
    //{
    //    foreach (var stitch in block.Stitches)
    //    {
    //        if(stitch.Angle != 0)
    //        {
    //            int aaa = 1;
    //        }
    //    }
    //}
    //var xxxxx = outBlock;
    var objectsFound = FindOutline(stitchData);
    var outPattern = new Pattern();
    outPattern.AddColor(new Thread(255, 0, 0, "none", "None"));
    int colorIndex = outPattern.ColorList.Count - 1;
    var r = new Random();
    foreach (StitchObject stitchObject in objectsFound)
    {
        if (stitchObject.SideOne.Count > 1 && stitchObject.SideTwo.Count > 1)
        {
            outPattern.AddColor(new Thread((byte) (r.Next()%256), (byte) (r.Next()%256), (byte) (r.Next()%256),
                                           "none", "None"));
            colorIndex++;
            outPattern.AddStitchRelative(0, 0, StitchTypes.Stop);
            var points = stitchObject.Generate2(75);
            foreach (var point in points)
            {
                outPattern.AddStitchAbsolute(point.X, point.Y, StitchTypes.Normal);
            }
            //break;
            //StitchObject stitchObject = objectsFound[1];))
            //////if (stitchObject.SideOne.Count > 0)
            //////{
            //////    outPattern.StitchList.Add(new Stitch(stitchObject.SideOne[0].X, stitchObject.SideOne[0].Y,
            //////                                         StitchType.Jump, colorIndex));
            //////}
            //////foreach (Point t in stitchObject.SideOne)
            //////{
            //////    outPattern.StitchList.Add(new Stitch(t.X, t.Y,
            //////                                         StitchType.Normal, colorIndex));
            //////}
            //////foreach (Point t in stitchObject.SideTwo)
            //////{
            //////    outPattern.StitchList.Add(new Stitch(t.X, t.Y,
            //////                                         StitchType.Normal, colorIndex));
            //////}
            //break;
        }
    }
    outPattern.AddStitchRelative(0, 0, StitchTypes.End);
    return outPattern;
    //return (SimplifyOutline(outPattern));
}

EmbPattern SimplifyOutline(EmbPattern pattern)
{
    var v = new Vertices();
    v.AddRange(pattern.StitchList.Select(point => new Vector2(point.X, point.Y)));
    var output = SimplifyTools.DouglasPeuckerSimplify(v, 10);
    var patternOut = new Pattern();
    foreach (var color in pattern.ColorList)
    {
        patternOut.AddColor(color);
    }

    foreach (var vertex in output)
    {
        patternOut.AddStitchAbsolute(vertex.X, vertex.Y, StitchTypes.Normal);
    }
    patternOut.AddStitchRelative(0, 0, StitchTypes.End);
    return patternOut;
}

bool[] _usePt;
double _distanceTolerance;

/* Removes all collinear points on the polygon. */
Vertices CollinearSimplify(Vertices vertices, float collinearityTolerance)
{
    /* We can't simplify polygons under 3 vertices */
    if (vertices.Count < 3)
        return vertices;

    var simplified = new Vertices();

    for (int i = 0; i < vertices.Count; i++)
    {
        int prevId = vertices.PreviousIndex(i);
        int nextId = vertices.NextIndex(i);

        Vector2 prev = vertices[prevId];
        Vector2 current = vertices[i];
        Vector2 next = vertices[nextId];

        /* If they collinear, continue */
        if (MathUtils.Collinear(ref prev, ref current, ref next, collinearityTolerance))
            continue;

        simplified.Add(current);
    }

    return simplified;
}

/// <summary>
/// Removes all collinear points on the polygon.
/// Has a default bias of 0
/// </summary>
/// <param name="vertices">The polygon that needs simplification.</param>
/// <returns>A simplified polygon.</returns>
Vertices CollinearSimplify(Vertices vertices)
{
    return CollinearSimplify(vertices, 0);
}

/// Ramer-Douglas-Peucker polygon simplification algorithm. This is the general recursive version that does not use the
/// speed-up technique by using the Melkman convex hull.
/// If you pass in 0, it will remove all collinear points
Vertices DouglasPeuckerSimplify(Vertices vertices, float distanceTolerance)
{
    _distanceTolerance = distanceTolerance;

    _usePt = new bool[vertices.Count];
    for (int i = 0; i < vertices.Count; i++)
    {
        _usePt[i] = true;
    }
    SimplifySection(vertices, 0, vertices.Count - 1);
    var result = new Vertices();
    result.AddRange(vertices.Where((t, i) => _usePt[i]));
    return result;
}

void SimplifySection(Vertices vertices, int i, int j)
{
    if ((i + 1) == j)
        return;

    Vector2 a = vertices[i];
    Vector2 b = vertices[j];
    double maxDistance = -1.0;
    int maxIndex = i;
    for (int k = i + 1; k < j; k++)
    {
        double distance = DistancePointLine(vertices[k], a, b);

        if (distance > maxDistance)
        {
            maxDistance = distance;
            maxIndex = k;
        }
    }
    if (maxDistance <= _distanceTolerance)
    {
        for (int k = i + 1; k < j; k++)
        {
            _usePt[k] = false;
        }
    }
    else
    {
        SimplifySection(vertices, i, maxIndex);
        SimplifySection(vertices, maxIndex, j);
    }
}

double DistancePointLine(EmbPoint p, EmbPoint a, EmbPoint b)
{
    /* if start == end, then use point-to-point distance */
    if (a.X == b.X && a.Y == b.Y)
        return DistancePointPoint(p, a);

    // otherwise use comp.graphics.algorithms Frequently Asked Questions method
    /*(1)     	      AC dot AB
                r =   ---------
                      ||AB||^2

                r has the following meaning:
                r=0 Point = A
                r=1 Point = B
                r<0 Point is on the backward extension of AB
                r>1 Point is on the forward extension of AB
                0<r<1 Point is interior to AB
    */

    double r = ((p.X - a.X) * (b.X - a.X) + (p.Y - a.Y) * (b.Y - a.Y))
               /
               ((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y));

    if (r <= 0.0) return DistancePointPoint(p, a);
    if (r >= 1.0) return DistancePointPoint(p, b);


    /*(2)
                    (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)
                s = -----------------------------
                                Curve^2

                Then the distance from C to Point = |s|*Curve.
    */

    double s = ((a.Y - p.Y) * (b.X - a.X) - (a.X - p.X) * (b.Y - a.Y))
               /
               ((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y));

    return Math.Abs(s) * Math.Sqrt(((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y)));
}

/* From physics2d.net */
public static Vertices ReduceByArea(Vertices vertices, float areaTolerance)
{
    if (vertices.Count <= 3)
        return vertices;

    if (areaTolerance < 0)
    {
        throw new ArgumentOutOfRangeException("areaTolerance", "must be equal to or greater then zero.");
    }

    var result = new Vertices();
    Vector2 v3;
    Vector2 v1 = vertices[vertices.Count - 2];
    Vector2 v2 = vertices[vertices.Count - 1];
    areaTolerance *= 2;
    for (int index = 0; index < vertices.Count; ++index, v2 = v3)
    {
        if (index == vertices.Count - 1)
        {
            if (result.Count == 0)
            {
                throw new ArgumentOutOfRangeException("areaTolerance", "The tolerance is too high!");
            }
            v3 = result[0];
        }
        else
        {
            v3 = vertices[index];
        }
        float old1;
        MathUtils.Cross(ref v1, ref v2, out old1);
        float old2;
        MathUtils.Cross(ref v2, ref v3, out old2);
        float new1;
        MathUtils.Cross(ref v1, ref v3, out new1);
        if (Math.Abs(new1 - (old1 + old2)) > areaTolerance)
        {
            result.Add(v2);
            v1 = v2;
        }
    }
    return result;
}

/* From Eric Jordan's convex decomposition library */
/* Merges all parallel edges in the list of vertices */
public static void MergeParallelEdges(Vertices vertices, float tolerance)
{
    if (vertices.Count <= 3)
        return; /* Can't do anything useful here to a triangle */

    var mergeMe = new bool[vertices.Count];
    int newNVertices = vertices.Count;

    /* Gather points to process */
    for (int i = 0; i < vertices.Count; ++i)
    {
        int lower = (i == 0) ? (vertices.Count - 1) : (i - 1);
        int middle = i;
        int upper = (i == vertices.Count - 1) ? (0) : (i + 1);

        float dx0 = vertices[middle].X - vertices[lower].X;
        float dy0 = vertices[middle].Y - vertices[lower].Y;
        float dx1 = vertices[upper].Y - vertices[middle].X;
        float dy1 = vertices[upper].Y - vertices[middle].Y;
        var norm0 = (float)Math.Sqrt(dx0 * dx0 + dy0 * dy0);
        var norm1 = (float)Math.Sqrt(dx1 * dx1 + dy1 * dy1);

        if (!(norm0 > 0.0f && norm1 > 0.0f) && newNVertices > 3)
        {
            /* Merge identical points */
            mergeMe[i] = true;
            --newNVertices;
        }

        dx0 /= norm0;
        dy0 /= norm0;
        dx1 /= norm1;
        dy1 /= norm1;
        float cross = dx0 * dy1 - dx1 * dy0;
        float dot = dx0 * dx1 + dy0 * dy1;

        if (Math.Abs(cross) < tolerance && dot > 0 && newNVertices > 3)
        {
            mergeMe[i] = true;
            --newNVertices;
        }
        else
            mergeMe[i] = false;
    }

    if (newNVertices == vertices.Count || newNVertices == 0)
        return;

    int currIndex = 0;

    /* Copy the vertices to a new list and clear the old */
    var oldVertices = new Vertices(vertices);
    vertices.Clear();

    for (int i = 0; i < oldVertices.Count; ++i)
    {
        if (mergeMe[i] || newNVertices == 0 || currIndex == newNVertices)
            continue;

        vertices.Add(oldVertices[i]);
        ++currIndex;
    }
}

/* Reduces the polygon by distance. */
Vertices ReduceByDistance(Vertices vertices, float distance)
{
    /* We can't simplify polygons under 3 vertices */
    if (vertices.Count < 3)
        return vertices;

    distance *= distance;

    var simplified = new Vertices();

    for (int i = 0; i < vertices.Count; i++)
    {
        int nextId = vertices.NextIndex(i);

        Vector2 current = vertices[i];
        Vector2 next = vertices[nextId];

        /* If they are closer than the distance, continue */
        if ((next - current).LengthSquared() <= distance)
            continue;

        simplified.Add(current);
    }

    return simplified;
}

/* Reduces the polygon by removing the Nth vertex in the vertices list. */
Vertices ReduceByNth(Vertices vertices, int nth)
{
    /* We can't simplify polygons under 3 vertices */
    if (vertices.Count < 3)
        return vertices;

    if (nth == 0)
        return vertices;

    var result = new Vertices(vertices.Count);
    result.AddRange(vertices.Where((t, i) => i%nth != 0));

    return result;
}
#endif

/*! Returns a pointer to an EmbPattern. It is created on the heap.
 * The caller is responsible for freeing the allocated memory with
 * embPattern_free(). */
EmbPattern* embPattern_create(void)
{
    EmbPattern* p = 0;
    p = (EmbPattern*)malloc(sizeof(EmbPattern));
    if(!p) { printf("ERROR: emb-pattern.c embPattern_create(), unable to allocate memory for p\n"); return 0; }

    p->settings = embSettings_init();
    p->currentColorIndex = 0;
    p->stitchList = 0;
    p->threads = 0;
    p->hoop.height = 0.0;
    p->hoop.width = 0.0;
    p->arcs = 0;
    p->circles = 0;
    p->ellipses = 0;
    p->lines = 0;
    p->paths = 0;
    p->points = 0;
    p->polygons = 0;
    p->polylines = 0;
    p->rects = 0;
    p->splines = 0;

    p->lastStitch = 0;

    p->lastX = 0.0;
    p->lastY = 0.0;

    return p;
}

void embPattern_hideStitchesOverLength(EmbPattern* p, int length)
{
    double prevX = 0;
    double prevY = 0;
    EmbStitchList* pointer = 0;

    if(!p) { printf("ERROR: emb-pattern.c embPattern_hideStitchesOverLength(), p argument is null\n"); return; }
    pointer = p->stitchList;
    while(pointer)
    {
        if((fabs(pointer->stitch.x - prevX) > length) || (fabs(pointer->stitch.y - prevY) > length))
        {
            pointer->stitch.flags |= TRIM;
            pointer->stitch.flags &= ~NORMAL;
        }
        prevX = pointer->stitch.x;
        prevY = pointer->stitch.y;
        pointer = pointer->next;
    }
}

int embPattern_addThread(EmbPattern* p, EmbThread thread)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addThread(), p argument is null\n");
        return 0;
    }
    if (!p->threads) {
        p->threads = embArray_create(EMB_THREAD);
    }
    embArray_addThread(p->threads, thread);
    return 1;
}

void embPattern_fixColorCount(EmbPattern* p)
{
    /* fix color count to be max of color index. */
    int maxColorIndex = 0;
    EmbStitchList* list = 0;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_fixColorCount(), p argument is null\n");
        return;
    }
    list = p->stitchList;
    while (list) {
        maxColorIndex = embMaxInt(maxColorIndex, list->stitch.color);
        list = list->next;
    }
    while (p->threads->count <= maxColorIndex) {
        embPattern_addThread(p, embThread_getRandom());
    }
    /*
    while (p->threadLists->count > (maxColorIndex + 1)) {
        TODO: erase last color    p->threadList.pop_back();
    }
    */
}

/*! Copies all of the EmbStitchList data to EmbPolylineObjectList data for pattern (\a p). */
void embPattern_copyStitchListToPolylines(EmbPattern* p)
{
    EmbStitchList* stList = 0;
    int breakAtFlags;

    if(!p) { printf("ERROR: emb-pattern.c embPattern_copyStitchListToPolylines(), p argument is null\n"); return; }

#ifdef EMB_DEBUG_JUMP
    breakAtFlags = (STOP | TRIM);
#else /* EMB_DEBUG_JUMP */
    breakAtFlags = (STOP | JUMP | TRIM);
#endif /* EMB_DEBUG_JUMP */

    stList = p->stitchList;
    while(stList)
    {
        EmbArray *pointList;
        EmbColor color;
        while(stList)
        {
            if(stList->stitch.flags & breakAtFlags)
            {
                break;
            }
            if(!(stList->stitch.flags & JUMP))
            {
                if (!pointList)
                {
                    pointList = embArray_create(EMB_POINT);
                    color = p->threads->thread[stList->stitch.color].color;
                }
                EmbPointObject point;
                point.point.x = stList->stitch.x;
                point.point.y = stList->stitch.y;
                embArray_addPoint(pointList, &point);
            }
            stList = stList->next;
        }

        /* NOTE: Ensure empty polylines are not created. This is critical. */
        if(pointList)
        {
            EmbPolylineObject* currentPolyline = (EmbPolylineObject*)malloc(sizeof(EmbPolylineObject));
            if(!currentPolyline) { printf("ERROR: emb-pattern.c embPattern_copyStitchListToPolylines(), cannot allocate memory for currentPolyline\n"); return; }
            currentPolyline->pointList = pointList;
            currentPolyline->color = color;
            currentPolyline->lineType = 1; /* TODO: Determine what the correct value should be */

            if (!p->polylines) {
                p->polylines = embArray_create(EMB_POLYLINE);
            }
            embArray_addPolyline(p->polylines, currentPolyline);
        }
        if(stList)
        {
            stList = stList->next;
        }
    }
}

/*! Copies all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
void embPattern_copyPolylinesToStitchList(EmbPattern* p)
{
    int firstObject = 1, i, j;
    /*int currentColor = polyList->polylineObj->color TODO: polyline color */

    if(!p) { printf("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), p argument is null\n"); return; }
    if (!p->polylines) { printf("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), p argument is null\n"); return; }
    for (i=0; i<p->polylines->count; i++) {
        EmbPolylineObject* currentPoly = 0;
        EmbArray* currentPointList = 0;
        EmbThread thread;

        currentPoly = p->polylines->polyline[i];
        if(!currentPoly) { printf("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), currentPoly is null\n"); return; }
        currentPointList = currentPoly->pointList;
        if(!currentPointList) { printf("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), currentPointList is null\n"); return; }

        thread.catalogNumber = 0;
        thread.color = currentPoly->color;
        thread.description = 0;
        embPattern_addThread(p, thread);

        if (!firstObject) {
            embPattern_addStitchAbs(p, currentPointList->point[0].point.x, currentPointList->point[0].point.y, TRIM, 1);
            embPattern_addStitchRel(p, 0.0, 0.0, STOP, 1);
        }

        embPattern_addStitchAbs(p, currentPointList->point[0].point.x, currentPointList->point[0].point.y, JUMP, 1);
        for (j=1; j<currentPointList->count; j++) { 
            embPattern_addStitchAbs(p, currentPointList->point[j].point.x, currentPointList->point[j].point.y, NORMAL, 1);
        }
        firstObject = 0;
    }
    embPattern_addStitchRel(p, 0.0, 0.0, END, 1);
}

/*! Moves all of the EmbStitchList data to EmbPolylineObjectList data for pattern (\a p). */
void embPattern_moveStitchListToPolylines(EmbPattern* p)
{
    if(!p) { printf("ERROR: emb-pattern.c embPattern_moveStitchListToPolylines(), p argument is null\n"); return; }
    embPattern_copyStitchListToPolylines(p);
    /* Free the stitchList and threadList since their data has now been transferred to polylines */
    embStitchList_free(p->stitchList);
    p->stitchList = 0;
    p->lastStitch = 0;
    embArray_free(p->threads);
}

/*! Moves all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
void embPattern_movePolylinesToStitchList(EmbPattern* p)
{
    if(!p) { printf("ERROR: emb-pattern.c embPattern_movePolylinesToStitchList(), p argument is null\n"); return; }
    embPattern_copyPolylinesToStitchList(p);
    embArray_free(p->polylines);
}

/*! Adds a stitch to the pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
void embPattern_addStitchAbs(EmbPattern* p, double x, double y, int flags, int isAutoColorIndex)
{
    EmbStitch s;

    if(!p) { printf("ERROR: emb-pattern.c embPattern_addStitchAbs(), p argument is null\n"); return; }

    if(flags & END)
    {
        if(embStitchList_empty(p->stitchList))
            return;
        /* Prevent unnecessary multiple END stitches */
        if(p->lastStitch->stitch.flags & END)
        {
            printf("ERROR: emb-pattern.c embPattern_addStitchAbs(), found multiple END stitches\n");
            return;
        }

        embPattern_fixColorCount(p);

        /* HideStitchesOverLength(127); TODO: fix or remove this */
    }

    if(flags & STOP)
    {
        if(embStitchList_empty(p->stitchList))
            return;
        if(isAutoColorIndex)
            p->currentColorIndex++;
    }

    /* NOTE: If the stitchList is empty, we will create it before adding stitches to it. The first coordinate will be the HOME position. */
    if(embStitchList_empty(p->stitchList))
    {
        /* NOTE: Always HOME the machine before starting any stitching */
        EmbPoint home = embSettings_home(&(p->settings));
        EmbStitch h;
        h.x = home.x;
        h.y = home.y;
        h.flags = JUMP;
        h.color = p->currentColorIndex;
        p->stitchList = p->lastStitch = embStitchList_create(h);
    }

    s.x = x;
    s.y = y;
    s.flags = flags;
    s.color = p->currentColorIndex;
#ifdef ARDUINO
    inoEvent_addStitchAbs(p, s.x, s.y, s.flags, s.color);
#else /* ARDUINO */
    p->lastStitch = embStitchList_add(p->lastStitch, s);
#endif /* ARDUINO */
    p->lastX = s.x;
    p->lastY = s.y;
}

/*! Adds a stitch to the pattern (\a p) at the relative position (\a dx,\a dy) to the previous stitch. Positive y is up. Units are in millimeters. */
void embPattern_addStitchRel(EmbPattern* p, double dx, double dy, int flags, int isAutoColorIndex)
{
    double x,y;

    if(!p) { printf("ERROR: emb-pattern.c embPattern_addStitchRel(), p argument is null\n"); return; }
    if(!embStitchList_empty(p->stitchList))
    {
        x = p->lastX + dx;
        y = p->lastY + dy;
    }
    else
    {
        /* NOTE: The stitchList is empty, so add it to the HOME position. The embStitchList_create function will ensure the first coordinate is at the HOME position. */
        EmbPoint home = embSettings_home(&(p->settings));
        x = home.x + dx;
        y = home.y + dy;
    }
    embPattern_addStitchAbs(p, x, y, flags, isAutoColorIndex);
}

void embPattern_changeColor(EmbPattern* p, int index)
{
    if(!p) { printf("ERROR: emb-pattern.c embPattern_changeColor(), p argument is null\n"); return; }
    p->currentColorIndex = index;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int embPattern_read(EmbPattern* pattern, const char* fileName) /* TODO: Write test case using this convenience function. */
{
    int reader, result;

    if(!pattern) { printf("ERROR: emb-pattern.c embPattern_read(), pattern argument is null\n"); return 0; }
    if(!fileName) { printf("ERROR: emb-pattern.c embPattern_read(), fileName argument is null\n"); return 0; }

    reader = emb_identify_format(fileName);
    if(reader < 0) { printf("ERROR: emb-pattern.c embPattern_read(), unsupported read file type: %s\n", fileName); return 0; }
    result = formatTable[reader].reader(pattern, fileName);
    return result;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int embPattern_write(EmbPattern* pattern, const char* fileName) /* TODO: Write test case using this convenience function. */
{
    int writer, result;

    if(!pattern) { printf("ERROR: emb-pattern.c embPattern_write(), pattern argument is null\n"); return 0; }
    if(!fileName) { printf("ERROR: emb-pattern.c embPattern_write(), fileName argument is null\n"); return 0; }

    writer = emb_identify_format(fileName);
    if(!writer) { printf("ERROR: emb-pattern.c embPattern_write(), unsupported write file type: %s\n", fileName); return 0; }
    result = formatTable[writer].writer(pattern, fileName);
    return result;
}

/* Very simple scaling of the x and y axis for every point.
* Doesn't insert or delete stitches to preserve density. */
void embPattern_scale(EmbPattern* p, double scale)
{
    EmbStitchList* pointer = 0;

    if(!p) { printf("ERROR: emb-pattern.c embPattern_scale(), p argument is null\n"); return; }
    pointer = p->stitchList;
    while(pointer)
    {
        pointer->stitch.x *= scale;
        pointer->stitch.y *= scale;
        pointer = pointer->next;
    }
}

/*! Returns an EmbRect that encapsulates all stitches and objects in the pattern (\a p). */
EmbRect embPattern_calcBoundingBox(EmbPattern* p)
{
    EmbStitchList* pointer = 0;
    EmbRect boundingRect;
    EmbStitch pt;
    EmbBezier bezier;

    boundingRect.left = 0;
    boundingRect.right = 0;
    boundingRect.top = 0;
    boundingRect.bottom = 0;

    if(!p) { printf("ERROR: emb-pattern.c embPattern_calcBoundingBox(), p argument is null\n"); return boundingRect; }

    /* Calculate the bounding rectangle.  It's needed for smart repainting. */
    /* TODO: Come back and optimize this mess so that after going thru all objects
            and stitches, if the rectangle isn't reasonable, then return a default rect */
    if (embStitchList_empty(p->stitchList) &&
        !(p->arcs || p->circles || p->ellipses || p->lines || p->points ||
        p->polygons || p->polylines || p->rects || p->splines))
    {
        boundingRect.top = 0.0;
        boundingRect.left = 0.0;
        boundingRect.bottom = 1.0;
        boundingRect.right = 1.0;
        return boundingRect;
    }
    boundingRect.left = 99999.0;
    boundingRect.top =  99999.0;
    boundingRect.right = -99999.0;
    boundingRect.bottom = -99999.0;

    pointer = p->stitchList;
    while(pointer)
    {
        /* If the point lies outside of the accumulated bounding
        * rectangle, then inflate the bounding rect to include it. */
        pt = pointer->stitch;
        if(!(pt.flags & TRIM))
        {
            boundingRect.left = embMinDouble(boundingRect.left, pt.x);
            boundingRect.top = embMinDouble(boundingRect.top, pt.y);
            boundingRect.right = embMaxDouble(boundingRect.right, pt.x);
            boundingRect.bottom = embMaxDouble(boundingRect.bottom, pt.y);
        }
        pointer = pointer->next;
    }

    int i, j;
    if (p->arcs) {
        /* TODO: embPattern_calcBoundingBox for arcs, for now just checks the start point */
        for (i=0; i<p->arcs->count; i++) {
            EmbArc arc = p->arcs->arc[i].arc;
            boundingRect.left = embMinDouble(boundingRect.left, arc.startX);
            boundingRect.top = embMinDouble(boundingRect.top, arc.startY);
            boundingRect.right = embMaxDouble(boundingRect.right, arc.startX);
            boundingRect.bottom = embMaxDouble(boundingRect.bottom, arc.startY);
        }
    }

    if (p->circles) {
        for (i=0; i<p->circles->count; i++) {
            EmbCircle circle = p->circles->circle[i].circle;
            boundingRect.left = embMinDouble(boundingRect.left, circle.centerX - circle.radius);
            boundingRect.top = embMinDouble(boundingRect.top, circle.centerY - circle.radius);
            boundingRect.right = embMaxDouble(boundingRect.right, circle.centerX + circle.radius);
            boundingRect.bottom = embMaxDouble(boundingRect.bottom, circle.centerY + circle.radius);
        }
    }

    if (p->ellipses) {
        for (i=0; i<p->ellipses->count; i++) {
            /* TODO: account for rotation */
            EmbEllipse ellipse = p->ellipses->ellipse[i].ellipse;
            boundingRect.left = embMinDouble(boundingRect.left, ellipse.centerX - ellipse.radiusX);
            boundingRect.top = embMinDouble(boundingRect.top, ellipse.centerY - ellipse.radiusY);
            boundingRect.right = embMaxDouble(boundingRect.right, ellipse.centerX + ellipse.radiusX);
            boundingRect.bottom = embMaxDouble(boundingRect.bottom, ellipse.centerY + ellipse.radiusY);
        }
    }

    if (p->lines) {
        for (i=0; i<p->lines->count; i++) {
            EmbLine line = p->lines->line[i].line;
            boundingRect.left = embMinDouble(boundingRect.left, line.x1);
            boundingRect.left = embMinDouble(boundingRect.left, line.x2);
            boundingRect.top = embMinDouble(boundingRect.top, line.y1);
            boundingRect.top = embMinDouble(boundingRect.top, line.y2);
            boundingRect.right = embMaxDouble(boundingRect.right, line.x1);
            boundingRect.right = embMaxDouble(boundingRect.right, line.x2);
            boundingRect.bottom = embMaxDouble(boundingRect.bottom, line.y1);
            boundingRect.bottom = embMaxDouble(boundingRect.bottom, line.y2);
        }
    }

    if (p->points) {
        for (i=0; i<p->points->count; i++) {
            EmbPoint point = p->points->point[i].point;
            /* TODO: embPattern_calcBoundingBox for points */

        }
    }

    if (p->polygons) {
        for (i=0; i<p->polygons->count; i++) {
            EmbArray *polygon;
            polygon = p->polygons->polygon[i]->pointList;
            for (j=0; j<polygon->count; j++) {
                /* TODO: embPattern_calcBoundingBox for polygons */
            }
        }
    }

    if (p->polylines) {
        for (i=0; i<p->polylines->count; i++) {
            EmbArray *polyline;
            polyline = p->polylines->polyline[i]->pointList;
            for (j=0; j<polyline->count; j++) {
                /* TODO: embPattern_calcBoundingBox for polylines */
            }
        }
    }

    if (p->rects) {
        for (i=0; i<p->rects->count; i++) {
            EmbRect rect = p->rects->rect[i].rect;
            /* TODO: embPattern_calcBoundingBox for rectangles */
        }
    }

    if (p->splines) {
        for (i=0; i<p->splines->count; i++) {
            bezier = p->splines->spline[i].bezier;
            /* TODO: embPattern_calcBoundingBox for splines */

        }
    }

    return boundingRect;
}

/*! Flips the entire pattern (\a p) horizontally about the y-axis. */
void embPattern_flipHorizontal(EmbPattern* p)
{
    if(!p) { printf("ERROR: emb-pattern.c embPattern_flipHorizontal(), p argument is null\n"); return; }
    embPattern_flip(p, 1, 0);
}

/*! Flips the entire pattern (\a p) vertically about the x-axis. */
void embPattern_flipVertical(EmbPattern* p)
{
    if(!p) { printf("ERROR: emb-pattern.c embPattern_flipVertical(), p argument is null\n"); return; }
    embPattern_flip(p, 0, 1);
}

/*! Flips the entire pattern (\a p) horizontally about the x-axis if (\a horz) is true.
 *  Flips the entire pattern (\a p) vertically about the y-axis if (\a vert) is true. */
void embPattern_flip(EmbPattern* p, int horz, int vert)
{
    int i, j;
    EmbStitchList* stList = 0;

    if(!p) { printf("ERROR: emb-pattern.c embPattern_flip(), p argument is null\n"); return; }

    stList = p->stitchList;
    while(stList)
    {
        if(horz) { stList->stitch.x = -stList->stitch.x; }
        if(vert) { stList->stitch.y = -stList->stitch.y; }
        stList = stList->next;
    }

    if (p->arcs) {
        for (i=0; i<p->arcs->count; i++) {
            if (horz) {
                p->arcs->arc[i].arc.startX *= -1.0;
                p->arcs->arc[i].arc.midX *= -1.0;
                p->arcs->arc[i].arc.endX *= -1.0;
            }
            if (vert) {
                p->arcs->arc[i].arc.startY *= -1.0;
                p->arcs->arc[i].arc.midY *= -1.0;
                p->arcs->arc[i].arc.endY *= -1.0;
            }
        }
    }

    if (p->circles) {
        for (i=0; i<p->circles->count; i++) {
            if (horz) { p->circles->circle[i].circle.centerX *= -1.0; }
            if (vert) { p->circles->circle[i].circle.centerY *= -1.0; }
        }
    }

    if (p->ellipses) {
        for (i=0; i<p->ellipses->count; i++) {
            if (horz) { p->ellipses->ellipse[i].ellipse.centerX *= -1.0; }
            if (vert) { p->ellipses->ellipse[i].ellipse.centerY *= -1.0; }
        }
    }

    if (p->lines) {
        for (i=0; i<p->lines->count; i++) {
            if(horz) {
                p->lines->line[i].line.x1 *= -1.0;
                p->lines->line[i].line.x2 *= -1.0;
            }
            if (vert) {
                p->lines->line[i].line.y1 *= -1.0;
                p->lines->line[i].line.y2 *= -1.0;
            }
        }
    }

    if (p->paths) {
        for (i=0; i<p->paths->count; i++) {
            EmbArray *path = p->paths->path[i]->pointList;
            for (j=0; j<path->count; j++) {
                if (horz) {
                    path->point[j].point.x *= -1.0;
                }
                if (vert) {
                    path->point[j].point.y *= -1.0;
                }
            }
        }
    }

    if (p->points) {
        for (i=0; i<p->points->count; i++) {
            if (horz) {
                p->points->point[i].point.x *= -1.0;
            }
            if (vert) {
                p->points->point[i].point.y *= -1.0;
            }
        }
    }

    if (p->polygons) {
        for (i=0; i<p->polygons->count; i++) {
            EmbArray *polygon;
            polygon = p->polygons->polygon[i]->pointList;
            for (j=0; j<polygon->count; j++) {
                if (horz) { polygon->point[j].point.x *= -1.0; }
                if (vert) { polygon->point[j].point.y *= -1.0; }
            }
        }
    }

    if (p->polylines) {
        for (i=0; i<p->polylines->count; i++) {
            EmbArray *polyline;
            polyline = p->polylines->polygon[i]->pointList;
            for (j=0; j<polyline->count; j++) {
                if (horz) { polyline->point[j].point.x *= -1.0; }
                if (vert) { polyline->point[j].point.y *= -1.0; }
            }
        }
    }

    if (p->rects) {
        for (i=0; i<p->rects->count; i++) {
            if (horz) {
                p->rects->rect[i].rect.left *= -1.0;
                p->rects->rect[i].rect.right *= -1.0;
            }
            if (vert) {
                p->rects->rect[i].rect.top *= -1.0;
                p->rects->rect[i].rect.bottom *= -1.0;
            }
        }
    }
    
    if (p->splines) {
        for (i=0; i<p->splines->count; i++) {
            /* TODO: embPattern_flip for splines */
        }
    }
}

void embPattern_combineJumpStitches(EmbPattern* p)
{
    EmbStitchList* pointer = 0;
    int jumpCount = 0;
    EmbStitchList* jumpListStart = 0;

    if(!p) { printf("ERROR: emb-pattern.c embPattern_combineJumpStitches(), p argument is null\n"); return; }
    pointer = p->stitchList;
    while(pointer)
    {
        if(pointer->stitch.flags & JUMP)
        {
            if(jumpCount == 0)
            {
                jumpListStart = pointer;
            }
            jumpCount++;
        }
        else
        {
            if(jumpCount > 0)
            {
                EmbStitchList* removePointer = jumpListStart->next;
                jumpListStart->stitch.x = pointer->stitch.x;
                jumpListStart->stitch.y = pointer->stitch.y;
                jumpListStart->next = pointer;

                for(; jumpCount > 0; jumpCount--)
                {
                    EmbStitchList* tempPointer = removePointer->next;
                    free(removePointer);
                    removePointer = tempPointer;
                }
                jumpCount = 0;
            }
        }
        pointer = pointer->next;
    }
}

/*TODO: The params determine the max XY movement rather than the length. They need renamed or clarified further. */
void embPattern_correctForMaxStitchLength(EmbPattern* p, double maxStitchLength, double maxJumpLength)
{
    int j = 0, splits;
    double maxXY, maxLen, addX, addY;

    if(!p) { printf("ERROR: emb-pattern.c embPattern_correctForMaxStitchLength(), p argument is null\n"); return; }
    if(embStitchList_count(p->stitchList) > 1)
    {
        EmbStitchList* pointer = 0;
        EmbStitchList* prev = 0;
        prev = p->stitchList;
        pointer = prev->next;

        while(pointer)
        {
            double xx = prev->stitch.x;
            double yy = prev->stitch.y;
            double dx = pointer->stitch.x - xx;
            double dy = pointer->stitch.y - yy;
            if((fabs(dx) > maxStitchLength) || (fabs(dy) > maxStitchLength))
            {
                maxXY = embMaxDouble(fabs(dx), fabs(dy));
                if(pointer->stitch.flags & (JUMP | TRIM)) maxLen = maxJumpLength;
                else maxLen = maxStitchLength;

                splits = (int)ceil((double)maxXY / maxLen);

                if(splits > 1)
                {
                    int flagsToUse = pointer->stitch.flags;
                    int colorToUse = pointer->stitch.color;
                    addX = (double)dx / splits;
                    addY = (double)dy / splits;

                    for(j = 1; j < splits; j++)
                    {
                        EmbStitchList* item = 0;
                        EmbStitch s;
                        s.x = xx + addX * j;
                        s.y = yy + addY * j;
                        s.flags = flagsToUse;
                        s.color = colorToUse;
                        item = (EmbStitchList*)malloc(sizeof(EmbStitchList));
                        if(!item) { printf("ERROR: emb-pattern.c embPattern_correctForMaxStitchLength(), cannot allocate memory for item\n"); return; }
                        item->stitch = s;
                        item->next = pointer;
                        prev->next = item;
                        prev = item;
                    }
                }
            }
            prev = pointer;
            if(pointer)
            {
                pointer = pointer->next;
            }
        }
    }
    if(p->lastStitch && p->lastStitch->stitch.flags != END)
    {
        embPattern_addStitchAbs(p, p->lastStitch->stitch.x, p->lastStitch->stitch.y, END, 1);
    }
}

void embPattern_center(EmbPattern* p)
{
    /* TODO: review this. currently not used in anywhere. Also needs to handle various design objects */
    int moveLeft, moveTop;
    EmbRect boundingRect;
    EmbStitchList* pointer = 0;

    if(!p) { printf("ERROR: emb-pattern.c embPattern_center(), p argument is null\n"); return; }
    boundingRect = embPattern_calcBoundingBox(p);

    moveLeft = (int)(boundingRect.left - (embRect_width(boundingRect) / 2.0));
    moveTop = (int)(boundingRect.top - (embRect_height(boundingRect) / 2.0));

    pointer = p->stitchList;
    while(pointer)
    {
        EmbStitch s;
        s = pointer->stitch;
        s.x -= moveLeft;
        s.y -= moveTop;
    }
}

/*TODO: Description needed. */
void embPattern_loadExternalColorFile(EmbPattern* p, const char* fileName)
{
    char hasRead = 0;
    char extractName[200], *dotPos;

    if(!p) { printf("ERROR: emb-pattern.c embPattern_loadExternalColorFile(), p argument is null\n"); return; }
    if(!fileName) { printf("ERROR: emb-pattern.c embPattern_loadExternalColorFile(), fileName argument is null\n"); return; }

    strcat(extractName, fileName);
    dotPos = strrchr(extractName, '.');
    *dotPos = 0;
    strcat(extractName, ".edr");
    hasRead = readEdr(p, extractName);
    if (!hasRead) {
        *dotPos = 0;
        strcat(extractName,".rgb");
        hasRead = readRgb(p, extractName);
    }
    if (!hasRead) {
        *dotPos = 0;
        strcat(extractName,".col");
        hasRead = readCol(p, extractName);
    }
    if (!hasRead) {
        *dotPos = 0;
        strcat(extractName,".inf");
        hasRead = readInf(p, extractName);
    }
}

/*! Frees all memory allocated in the pattern (\a p). */
void embPattern_free(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_free(), p argument is null\n");
        return;
    }
    embStitchList_free(p->stitchList);
    p->stitchList = 0;
    p->lastStitch = 0;

    embArray_free(p->threads);
    embArray_free(p->arcs);
    embArray_free(p->circles);
    embArray_free(p->ellipses);
    embArray_free(p->lines);
    embArray_free(p->paths);
    embArray_free(p->points);
    embArray_free(p->polygons);
    embArray_free(p->polylines);
    embArray_free(p->rects);
    embArray_free(p->splines);

    free(p);
    p = 0;
}

/*! Adds a circle object to pattern (\a p) with its center at the absolute
 * position (\a cx,\a cy) with a radius of (\a r). Positive y is up.
 * Units are in millimeters. */
void embPattern_addCircleObjectAbs(EmbPattern* p, double cx, double cy, double r)
{
    EmbCircle circle = {cx, cy, r};

    if (!p) { printf("ERROR: emb-pattern.c embPattern_addCircleObjectAbs(), p argument is null\n"); return; }
    if (p->circles == 0) {
         p->circles = embArray_create(EMB_CIRCLE);
    }
    embArray_addCircle(p->circles, circle, 0, black);
}

/*! Adds an ellipse object to pattern (\a p) with its center at the
 * absolute position (\a cx,\a cy) with radii of (\a rx,\a ry). Positive y is up.
 * Units are in millimeters. */
void embPattern_addEllipseObjectAbs(EmbPattern* p, double cx, double cy, double rx, double ry)
{
    EmbEllipse ellipse;
    ellipse.centerX = cx;
    ellipse.centerY = cy;
    ellipse.radiusX = rx;
    ellipse.radiusY = ry;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addEllipseObjectAbs(), p argument is null\n");
        return;
    }
    if (!p->ellipses) {
        p->ellipses = embArray_create(EMB_ELLIPSE);
    }
    embArray_addEllipse(p->ellipses, ellipse, 0.0, 0, black);
}

/*! Adds a line object to pattern (\a p) starting at the absolute position
 * (\a x1,\a y1) and ending at the absolute position (\a x2,\a y2).
 * Positive y is up. Units are in millimeters.
 */
void embPattern_addLineObjectAbs(EmbPattern* p, double x1, double y1, double x2, double y2)
{
    EmbLineObject lineObj;
    lineObj.line = embLine_make(x1, y1, x2, y2);
    lineObj.color = embColor_make(0, 0, 0);

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addLineObjectAbs(), p argument is null\n");
        return;
    }
    if (p->circles == 0) {
         p->lines = embArray_create(EMB_LINE);
    }
    embArray_addLine(p->lines, lineObj);
}

void embPattern_addPathObjectAbs(EmbPattern* p, EmbPathObject* obj)
{
    if(!p) { printf("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), p argument is null\n"); return; }
    if(!obj) { printf("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), obj argument is null\n"); return; }
    if(!obj->pointList) { printf("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), obj->pointList is empty\n"); return; }

    if (!p->paths) {
        p->paths = embArray_create(EMB_PATH);
    }
    embArray_addPath(p->paths, obj);
}

/*! Adds a point object to pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
void embPattern_addPointObjectAbs(EmbPattern* p, double x, double y)
{
    EmbPointObject pointObj;
    pointObj.point.x = x;
    pointObj.point.y = y;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addPointObjectAbs(), p argument is null\n");
        return;
    }
    if (!p->points) {
        p->points = embArray_create(EMB_POINT);
    }
    embArray_addPoint(p->points, &pointObj);
}

void embPattern_addPolygonObjectAbs(EmbPattern* p, EmbPolygonObject* obj)
{
    if(!p) { printf("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), p argument is null\n"); return; }
    if(!obj) { printf("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), obj argument is null\n"); return; }
    if(!obj->pointList) { printf("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), obj->pointList is empty\n"); return; }

    if (!p->polygons) {
        p->polygons = embArray_create(EMB_POLYGON);
    }
    embArray_addPolygon(p->polygons, obj);
}

void embPattern_addPolylineObjectAbs(EmbPattern* p, EmbPolylineObject* obj)
{
    if (!p) { printf("ERROR: emb-pattern.c embPattern_addPolylineObjectAbs(), p argument is null\n"); return; }
    if (!obj) { printf("ERROR: emb-pattern.c embPattern_addPolylineObjectAbs(), obj argument is null\n"); return; }
    if (!obj->pointList) {
        printf("ERROR: emb-pattern.c embPattern_addPolylineObjectAbs(), obj->pointList is empty\n"); return;
    }

    if (!p->polylines) {
        p->polylines = embArray_create(EMB_POLYLINE);
    }
    embArray_addPolyline(p->polylines, obj);
}

/**
 * Adds a rectangle object to pattern (\a p) at the absolute position
 * (\a x,\a y) with a width of (\a w) and a height of (\a h).
 * Positive y is up. Units are in millimeters.
 */
void embPattern_addRectObjectAbs(EmbPattern* p, double x, double y, double w, double h)
{
    EmbRect rect;
    rect.left = x;
    rect.top = y;
    rect.right = x+w;
    rect.bottom = y+h;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addRectObjectAbs(), p argument is null\n");
        return;
    }
    if (!p->rects) {
        p->rects = embArray_create(EMB_RECT);
    }
    embArray_addRect(p->rects, rect, 0, black);
}

void embPattern_end(EmbPattern *p)
{
    /* Check for an END stitch and add one if it is not present */
    if (p->lastStitch->stitch.flags != END) {
        embPattern_addStitchRel(p, 0, 0, END, 1);
    }
}

int emb_identify_format(char *fileName)
{
    int i;
    char ending[5];
    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }

    for (i=0; i<numberOfFormats; i++) {
        if (!strcmp(ending, formatTable[i].extension)) {
            return i;
        }
    }
    return -1;
}

double embRect_x(EmbRect rect)
{
    return rect.left;
}

double embRect_y(EmbRect rect)
{
    return rect.top;
}

double embRect_width(EmbRect rect)
{
    return rect.right - rect.left;
}

double embRect_height(EmbRect rect)
{
    return rect.bottom - rect.top;
}

/* Sets the left edge of the rect to x. The right edge is not modified. */
void embRect_setX(EmbRect* rect, double x)
{
    rect->left = x;
}

/* Sets the top edge of the rect to y. The bottom edge is not modified. */
void embRect_setY(EmbRect* rect, double y)
{
    rect->top = y;
}

/* Sets the width of the rect to w. The right edge is modified. The left edge is not modified. */
void embRect_setWidth(EmbRect* rect, double w)
{
    rect->right = rect->left + w;
}

/* Sets the height of the rect to h. The bottom edge is modified. The top edge is not modified. */
void embRect_setHeight(EmbRect* rect, double h)
{
    rect->bottom = rect->top + h;
}

void embRect_setCoords(EmbRect* rect, double x1, double y1, double x2, double y2)
{
    rect->left = x1;
    rect->top = y1;
    rect->right = x2;
    rect->bottom = y2;
}

void embRect_setRect(EmbRect* rect, double x, double y, double w, double h)
{
    rect->left = x;
    rect->top = y;
    rect->right = x + w;
    rect->bottom = y + h;
}

/* Returns an EmbRectObject. It is created on the stack. */
EmbRectObject embRectObject_make(double x, double y, double w, double h)
{
    EmbRectObject stackRectObj;
    stackRectObj.rect.left = x;
    stackRectObj.rect.top = y;
    stackRectObj.rect.right = x + w;
    stackRectObj.rect.bottom = y + h;
    return stackRectObj;
}

void embSatinOutline_generateSatinOutline(EmbArray *lines, double thickness, EmbSatinOutline* result)
{
    int i;
    EmbSatinOutline outline;
    double halfThickness = thickness / 2.0;
    int intermediateOutlineCount = 2 * lines->count - 2;
    outline.side1 = embArray_create(EMB_VECTOR);
    if (!outline.side1) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for outline->side1\n");
        return;
    }
    outline.side2 = embArray_create(EMB_VECTOR);
    if (!outline.side2) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for outline->side2\n");
        return;
    }

    for (i = 1; i < lines->count; i++) {
        int j = (i - 1) * 2;
        EmbVector v1;
        EmbVector temp;

        EmbLine line;
        line.x1 = lines->vector[i - 1].x;
        line.y1 = lines->vector[i - 1].y;
        line.x2 = lines->vector[i].x;
        line.y2 = lines->vector[i].y;

        embLine_normalVector(line, &v1, 1);

        embVector_multiply(v1, halfThickness, &temp);
        embVector_add(temp, lines->vector[i - 1], &temp);
        embArray_addVector(outline.side1, temp);
        embVector_add(temp, lines->vector[i], &temp);
        embArray_addVector(outline.side1, temp);

        embVector_multiply(v1, -halfThickness, &temp);
        embVector_add(temp, lines->vector[i - 1], &temp);
        embArray_addVector(outline.side2, temp);
        embVector_add(temp, lines->vector[i], &temp);
        embArray_addVector(outline.side2, temp);
    }

    if (!result) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), result argument is null\n");
        return;
    }
    result->side1 = embArray_create(EMB_VECTOR);
    if (!result->side1) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side1\n");
        return;
    }
    result->side2 = embArray_create(EMB_VECTOR);
    if (!result->side2) {
        printf("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side2\n");
        return;
    }

    embArray_addVector(result->side1, outline.side1->vector[0]);
    embArray_addVector(result->side2, outline.side2->vector[0]);

    EmbLine line1, line2;
    EmbVector out;
    for (i = 3; i < intermediateOutlineCount; i += 2) {
        line1.x1 = outline.side1->vector[i - 3].x;
        line1.y1 = outline.side1->vector[i - 3].y;
        line1.x2 = outline.side1->vector[i - 2].x;
        line1.y2 = outline.side1->vector[i - 2].y;
        line2.x1 = outline.side1->vector[i - 1].x;
        line2.y1 = outline.side1->vector[i - 1].y;
        line2.x2 = outline.side1->vector[i].x;
        line2.y2 = outline.side1->vector[i].y;
        embLine_intersectionPoint(line1, line2, &out);
        embArray_addVector(result->side1, out);

        line1.x1 = outline.side2->vector[i - 3].x;
        line1.y1 = outline.side2->vector[i - 3].y;
        line1.x2 = outline.side2->vector[i - 2].x;
        line1.y2 = outline.side2->vector[i - 2].y;
        line2.x1 = outline.side2->vector[i - 1].x;
        line2.y1 = outline.side2->vector[i - 1].y;
        line2.x2 = outline.side2->vector[i].x;
        line2.y2 = outline.side2->vector[i].y;
        embLine_intersectionPoint(line1, line2, &out);
        embArray_addVector(result->side2, out);
    }

    embArray_addVector(result->side1, outline.side1->vector[2 * lines->count - 3]);
    embArray_addVector(result->side2, outline.side2->vector[2 * lines->count - 3]);
    result->length = lines->count;
}

EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, double density)
{
    int i, j;
    EmbVector currTop, currBottom, topDiff, bottomDiff, midDiff;
    EmbVector midLeft, midRight, topStep, bottomStep;
    EmbArray* stitches = 0;

    if (!result) {
        printf("ERROR: emb-satin-line.c embSatinOutline_renderStitches(), result argument is null\n");
        return 0;
    }

    if (result->length > 0) {
        for (j = 0; j < result->length - 1; j++) {
            embVector_subtract(result->side1->vector[j+1], result->side1->vector[j], &topDiff);
            embVector_subtract(result->side2->vector[j+1], result->side2->vector[j], &bottomDiff);

            embVector_average(result->side1->vector[j], result->side2->vector[j], &midLeft);
            embVector_average(result->side1->vector[j+1], result->side2->vector[j+1], &midRight);

            embVector_subtract(midLeft, midRight, &midDiff);
            double midLength = embVector_getLength(midDiff);

            int numberOfSteps = (int)(midLength * density / 200);
            embVector_multiply(topDiff, 1.0/numberOfSteps, &topStep);
            embVector_multiply(bottomDiff, 1.0/numberOfSteps, &bottomStep);
            currTop = result->side1->vector[j];
            currBottom = result->side2->vector[j];

            for (i = 0; i < numberOfSteps; i++) {
                if (!stitches) {
                    stitches = embArray_create(EMB_VECTOR);
                }
                embArray_addVector(stitches, currTop);
                embArray_addVector(stitches, currBottom);
                embVector_add(currTop, topStep, &currTop);
                embVector_add(currBottom, bottomStep, &currBottom);
            }
        }
        embArray_addVector(stitches, currTop);
        embArray_addVector(stitches, currBottom);
    }
    return stitches;
}

/*! Initializes and returns an EmbSettings */
EmbSettings embSettings_init(void)
{
    EmbSettings settings;
    settings.dstJumpsPerTrim = 6;
    settings.home.x = 0.0;
    settings.home.y = 0.0;
    return settings;
}

/*! Returns the home position stored in (\a settings) as an EmbPoint (\a point). */
EmbPoint embSettings_home(EmbSettings* settings)
{
    return settings->home;
}

/*! Sets the home position stored in (\a settings) to EmbPoint (\a point). You will rarely ever need to use this. */
void embSettings_setHome(EmbSettings* settings, EmbPoint point)
{
    settings->home = point;
}

EmbStitchList* embStitchList_create(EmbStitch data)
{
    EmbStitchList* heapStitchList = (EmbStitchList*)malloc(sizeof(EmbStitchList));
    if(!heapStitchList) { printf("ERROR: emb-stitch.c embStitchList_create(), cannot allocate memory for heapStitchList\n"); return 0; }
    heapStitchList->stitch = data;
    heapStitchList->next = 0;
    return heapStitchList;
}

EmbStitchList* embStitchList_add(EmbStitchList* pointer, EmbStitch data)
{
    if(!pointer) { printf("ERROR: emb-stitch.c embStitchList_add(), pointer argument is null\n"); return 0; }
    if(pointer->next) { printf("ERROR: emb-stitch.c embStitchList_add(), pointer->next should be null\n"); return 0; }
    pointer->next = (EmbStitchList*)malloc(sizeof(EmbStitchList));
    if(!pointer->next) { printf("ERROR: emb-stitch.c embStitchList_add(), cannot allocate memory for pointer->next\n"); return 0; }
    pointer = pointer->next;
    pointer->stitch = data;
    pointer->next = 0;
    return pointer;
}

EmbStitch embStitchList_getAt(EmbStitchList* pointer, int num)
{
    /* TODO: pointer safety */
    int i;
    for(i = 0; i < num; i++)
    {
        pointer = pointer->next;
    }
    return pointer->stitch;
}

/* TODO: Add a default parameter to handle returning count based on stitch flags. Currently, it includes JUMP and TRIM stitches, maybe we just want NORMAL stitches only or vice versa */
int embStitchList_count(EmbStitchList* pointer)
{
    int i = 1;
    if(!pointer) return 0;
    while(pointer->next)
    {
        pointer = pointer->next;
        i++;
    }
    return i;
}

int embStitchList_empty(EmbStitchList* pointer)
{
    if(!pointer)
        return 1;
    return 0;
}

void embStitchList_free(EmbStitchList* pointer)
{
    EmbStitchList* tempPointer = pointer;
    EmbStitchList* nextPointer = 0;
    while(tempPointer)
    {
        nextPointer = tempPointer->next;
        free(tempPointer);
        tempPointer = nextPointer;
    }
    pointer = 0;
}

/**
 * Returns the closest color to the required color based on
 * a list of available threads. The algorithm is a simple least
 * squares search against the list. If the (square of) Euclidean 3-dimensional
 * distance between the points in (red, green, blue) space is smaller
 * then the index is saved and the remaining index is returned to the
 * caller.
 *
 * @param color  The EmbColor color to match.
 * @param colors The EmbThreadList pointer to start the search at.
 * @param mode   Is the argument an array of threads (0) or colors (1)?
 * @return closestIndex The entry in the ThreadList that matches.
 */
int embThread_findNearestColor(EmbColor color, EmbArray* a, int mode)
{
    int currentClosestValue = 256*256*3;
    int closestIndex = -1, i;
    int deltaRed, deltaBlue, deltaGreen, delta;
    EmbColor c;

    for (i=0; i<a->count; i++) {
        if (mode == 0) { /* thread mode */
            c = a->thread[i].color;
        }
        else { /* color array mode */
            c = a->color[i];
        }

        deltaRed = color.r - c.r;
        deltaBlue = color.g - c.g;
        deltaGreen = color.b - c.b;
        delta = deltaRed*deltaRed + deltaBlue*deltaBlue + deltaGreen*deltaGreen;

        if (delta <= currentClosestValue) {
            currentClosestValue = delta;
            closestIndex = i;
        }
    }
    return closestIndex;
}

int embThread_findNearestColor_fromThread(EmbColor color, EmbThread* a, int length)
{
    int currentClosestValue = 256*256*3;
    int closestIndex = -1, i;
    int deltaRed, deltaBlue, deltaGreen, delta;
    EmbColor c;

    for (i=0; i<length; i++) {
        c = a[i].color;
        
        deltaRed = color.r - c.r;
        deltaBlue = color.g - c.g;
        deltaGreen = color.b - c.b;
        delta = deltaRed*deltaRed + deltaBlue*deltaBlue + deltaGreen*deltaGreen;

        if (delta <= currentClosestValue) {
            currentClosestValue = delta;
            closestIndex = i;
        }
    }
    return closestIndex;
}
/**
 * Returns a random thread color, useful in filling in cases where the
 * actual color of the thread doesn't matter but one needs to be declared
 * to test or render a pattern.
 *
 * @return c The resulting color.
 */
EmbThread embThread_getRandom(void)
{
    EmbThread c;
    c.color.r = rand()%256;
    c.color.g = rand()%256;
    c.color.b = rand()%256;
    c.description = "random";
    c.catalogNumber = "";
    return c;
}

char binaryReadByte(EmbFile* file)
{
    return (char)embFile_getc(file);
}

int binaryReadBytes(EmbFile* file, unsigned char* destination, int count)
{
    return (int) embFile_read((char*) destination, 1, count, file);
}

short binaryReadInt16(EmbFile* file)
{
    int x = embFile_getc(file);
    x = x | embFile_getc(file) << 8;
    return (short)x;
}

int binaryReadInt32(EmbFile* file)
{
    int x = embFile_getc(file);
    x = x | embFile_getc(file) << 8;
    x = x | embFile_getc(file) << 16;
    x = x | embFile_getc(file) << 24;
    return x;
}

unsigned char binaryReadUInt8(EmbFile* file)
{
    return (unsigned char)embFile_getc(file);
}

unsigned short binaryReadUInt16(EmbFile* file)
{
    return (unsigned short)(embFile_getc(file) | embFile_getc(file) << 8);
}

unsigned int binaryReadUInt32(EmbFile* file)
{
    unsigned int x = embFile_getc(file);
    x = x | embFile_getc(file) << 8;
    x = x | embFile_getc(file) << 16;
    x = x | embFile_getc(file) << 24;
    return x;
}

/* Big endian version */
short binaryReadInt16BE(EmbFile* file)
{
    short returnValue = (short)(embFile_getc(file) << 8);
    returnValue |= embFile_getc(file);
    return returnValue;
}

/* Big endian version */
unsigned short binaryReadUInt16BE(EmbFile* file)
{
    unsigned short returnValue = (unsigned short)(embFile_getc(file) << 8);
    returnValue |= embFile_getc(file);
    return returnValue;
}

/* Big endian version */
int binaryReadInt32BE(EmbFile* file)
{
    int returnValue = embFile_getc(file) << 24;
    returnValue |= embFile_getc(file) << 16;
    returnValue |= embFile_getc(file) << 8;
    returnValue |= embFile_getc(file);
    return (returnValue);
}

/* Big endian version */
unsigned int binaryReadUInt32BE(EmbFile* file)
{
    unsigned int returnValue = embFile_getc(file) << 24;
    returnValue |= embFile_getc(file) << 16;
    returnValue |= embFile_getc(file) << 8;
    returnValue |= embFile_getc(file);
    return returnValue;
}

void binaryReadString(EmbFile* file, char* buffer, int maxLength)
{
    int i = 0;
    while(i < maxLength)
    {
        buffer[i] = (char)embFile_getc(file);
        if(buffer[i] == '\0') break;
        i++;
    }
}

void binaryReadUnicodeString(EmbFile* file, char *buffer, const int stringLength)
{
    int i = 0;
    for(i = 0; i < stringLength * 2; i++)
    {
        char input = (char)embFile_getc(file);
        if(input != 0)
        {
            buffer[i] = input;
        }
    }
}

float binaryReadFloat(EmbFile* file)
{
    union
    {
        float f32;
        unsigned int u32;
    } float_int_u;
    float_int_u.u32 = embFile_getc(file);
    float_int_u.u32 |= embFile_getc(file) << 8;
    float_int_u.u32 |= embFile_getc(file) << 16;
    float_int_u.u32 |= embFile_getc(file) << 24;
    return float_int_u.f32;
}

void binaryWriteByte(EmbFile* file, unsigned char data)
{
    embFile_putc(data, file);
}

void binaryWriteBytes(EmbFile* file, const char* data, int size)
{
    embFile_write((char*)data, 1, size, file);
}

void binaryWriteShort(EmbFile* file, short data)
{
    embFile_putc(data & 0xFF, file);
    embFile_putc((data >> 8) & 0xFF, file);
}

void binaryWriteShortBE(EmbFile* file, short data)
{
    embFile_putc((data >> 8) & 0xFF, file);
    embFile_putc(data & 0xFF, file);
}

void binaryWriteUShort(EmbFile* file, unsigned short data)
{
    embFile_putc(data & 0xFF, file);
    embFile_putc((data >> 8) & 0xFF, file);
}

void binaryWriteUShortBE(EmbFile* file, unsigned short data)
{
    embFile_putc((data >> 8) & 0xFF, file);
    embFile_putc(data & 0xFF, file);
}

void binaryWriteInt(EmbFile* file, int data)
{
    embFile_putc(data & 0xFF, file);
    embFile_putc((data >> 8) & 0xFF, file);
    embFile_putc((data >> 16) & 0xFF, file);
    embFile_putc((data >> 24) & 0xFF, file);
}

void binaryWriteIntBE(EmbFile* file, int data)
{
    embFile_putc((data >> 24) & 0xFF, file);
    embFile_putc((data >> 16) & 0xFF, file);
    embFile_putc((data >> 8) & 0xFF, file);
    embFile_putc(data & 0xFF, file);
}

void binaryWriteUInt(EmbFile* file, unsigned int data)
{
    embFile_putc(data & 0xFF, file);
    embFile_putc((data >> 8) & 0xFF, file);
    embFile_putc((data >> 16) & 0xFF, file);
    embFile_putc((data >> 24) & 0xFF, file);
}

void binaryWriteUIntBE(EmbFile* file, unsigned int data)
{
    embFile_putc((data >> 24) & 0xFF, file);
    embFile_putc((data >> 16) & 0xFF, file);
    embFile_putc((data >> 8) & 0xFF, file);
    embFile_putc(data & 0xFF, file);
}

void binaryWriteFloat(EmbFile* file, float data)
{
    union
    {
        float f32;
        unsigned int u32;
    } float_int_u;
    float_int_u.f32 = data;

    embFile_putc(float_int_u.u32 & 0xFF, file);
    embFile_putc((float_int_u.u32 >> 8) & 0xFF, file);
    embFile_putc((float_int_u.u32 >> 16) & 0xFF, file);
    embFile_putc((float_int_u.u32 >> 24) & 0xFF, file);
}

double embMinDouble(double a, double b)
{
    if (a<b) return a;
    return b;
}

double embMaxDouble(double a, double b)
{
    if (a>b) return a;
    return b;
}

int embMinInt(int a, int b)
{
    if (a<b) return a;
    return b;
}

int embMaxInt(int a, int b)
{
    if (a>b) return a;
    return b;
}

/**
 * Function is similar to the Unix utility tr.
 *
 * Character for character replacement in strings.
 * Takes a string \a s and for every character in the
 * \a from string replace with the corresponding character
 * in the \a to string.
 *
 * For example: ("test", "tb", "..") -> ".es."
 */
void charReplace(char *s, const char *from, const char *to)
{
    int i;
    for (; *s; s++) {
        for (i=0; from[i]; i++) {
            if (*s == from[i]) {
                *s = to[i];
            }
        }
    }
}

/**
 * Tests for the presense of a string \a s in the supplied
 * \a array.
 *
 * The end of the array is marked by an empty string.
 *
 * @return 0 if not present 1 if present.
 */
int stringInArray(const char *s, const char **array)
{
    int i;
    for (i=0; strlen(array[i]); i++) {
        if (!strcmp(s, array[i])) {
            return 1;
        }
    }
    return 0;
}

/*! Rounds a double (\a src) and returns it as an \c int. */
int roundDouble(double src)
{
    if(src < 0.0)
        return (int) ceil(src - 0.5);
    return (int)floor(src+0.5);
}

/*! Returns \c true if string (\a str) begins with substring (\a pre), otherwise returns \c false. */
char startsWith(const char* pre, const char* str)
{
    char result = 0;
    size_t lenpre;
    size_t lenstr;
    if(!pre) { printf("ERROR: helpers-misc.c startsWith(), pre argument is null\n"); return 0; }
    if(!str) { printf("ERROR: helpers-misc.c startsWith(), str argument is null\n"); return 0; }
    lenpre = strlen(pre);
    lenstr = strlen(str);
    if(lenstr < lenpre)
        return 0;
    result = (char)strncmp(pre, str, lenpre);
    if(result == 0)
        return 1;
    return 0;
}

/*! Removes all characters from the right end of the string (\a str) that match (\a junk), moving left until a mismatch occurs. */
char* rTrim(char* const str, char junk)
{
    char* original = str + strlen(str);
    while(*--original == junk);
    *(original + 1) = '\0';
    return str;
}

/*! Removes all characters from the left end of the string (\a str) that match (\a junk), moving right until a mismatch occurs. */
char* lTrim(char* const str, char junk)
{
    char* original = str;
    char* p = original;
    int trimmed = 0;
    do
    {
        if(*original != junk || trimmed)
        {
            trimmed = 1;
            *p++ = *original;
        }
    }
    while(*original++ != '\0');
    return str;
}

/* TODO: trimming function should handle any character, not just whitespace */
static char const WHITESPACE[] = " \t\n\r";

/* TODO: description */
static void get_trim_bounds(char const *s,
                            char const **firstWord,
                            char const **trailingSpace)
{
    char const* lastWord = 0;
    *firstWord = lastWord = s + strspn(s, WHITESPACE);
    do
    {
        *trailingSpace = lastWord + strcspn(lastWord, WHITESPACE);
        lastWord = *trailingSpace + strspn(*trailingSpace, WHITESPACE);
    }
    while (*lastWord != '\0');
}

/* TODO: description */
char* copy_trim(char const *s)
{
    char const *firstWord = 0, *trailingSpace = 0;
    char* result = 0;
    size_t newLength;

    get_trim_bounds(s, &firstWord, &trailingSpace);
    newLength = trailingSpace - firstWord;

    result = (char*)malloc(newLength + 1);
    memcpy(result, firstWord, newLength);
    result[newLength] = '\0';
    return result;
}

/* TODO: description */
void inplace_trim(char* s)
{
    char const *firstWord = 0, *trailingSpace = 0;
    size_t newLength;

    get_trim_bounds(s, &firstWord, &trailingSpace);
    newLength = trailingSpace - firstWord;

    memmove(s, firstWord, newLength);
    s[newLength] = '\0';
}

/*! Optimizes the number (\a num) for output to a text file and returns it as a string (\a str). */
char* emb_optOut(double num, char* str)
{
    /* Convert the number to a string */
    sprintf(str, "%.10f", num);
    /* Remove trailing zeroes */
    rTrim(str, '0');
    /* Remove the decimal point if it happens to be an integer */
    rTrim(str, '.');
    return str;
}

/*! Duplicates the string (\a src) and returns it. It is created on the heap. The caller is responsible for freeing the allocated memory. */
char* emb_strdup(const char* src)
{
    char* dest = 0;
    if(!src) { printf("ERROR: helpers-misc.c emb_strdup(), src argument is null\n"); return 0; }
    dest = (char*)malloc(strlen(src) + 1);
    if(!dest) { printf("ERROR: helpers-misc.c emb_strdup(), cannot allocate memory\n"); }
    else { strcpy(dest, src); }
    return dest;
}

void embTime_initNow(EmbTime* t)
{
#ifdef ARDUINO
/*TODO: arduino embTime_initNow */
#else
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    t->year   = timeinfo->tm_year;
    t->month  = timeinfo->tm_mon;
    t->day    = timeinfo->tm_mday;
    t->hour   = timeinfo->tm_hour;
    t->minute = timeinfo->tm_min;
    t->second = timeinfo->tm_sec;
#endif /* ARDUINO */
}

EmbTime embTime_time(EmbTime* t)
{
#ifdef ARDUINO
/*TODO: arduino embTime_time */
#else

int divideByZero = 0;
divideByZero = divideByZero/divideByZero; /*TODO: wrap time() from time.h and verify it works consistently */

#endif /* ARDUINO */
}

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


int convert(const char *inf, const char *outf)
{
    EmbPattern* p = 0;
    int formatType, reader, writer;

    p = embPattern_create();
    if (!p) {
        printf("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    reader = emb_identify_format(inf);
    if (reader < 0) {
        printf("ERROR: convert(), unsupported read file type: %s\n", inf);
        embPattern_free(p);
        return 1;
    }
    writer = emb_identify_format(outf);
    if (writer < 0) {
        printf("ERROR: convert(), unsupported write file type: %s\n", outf);
        embPattern_free(p);
        return 1;
    }

    if (!formatTable[reader].reader(p, inf)) {
        printf("ERROR: convert(), reading file was unsuccessful: %s\n", inf);
        embPattern_free(p);
        return 1;
    }

    formatType = formatTable[reader].type;
    if (formatType == EMBFORMAT_OBJECTONLY) {
        formatType = formatTable[writer].type;
        if (formatType == EMBFORMAT_STITCHONLY) {
            embPattern_movePolylinesToStitchList(p);
        }
    }

    if (!formatTable[writer].writer(p, outf)) {
        printf("ERROR: convert(), writing file %s was unsuccessful\n", outf);
        embPattern_free(p);
        return 1;
    }

    embPattern_free(p);
    return 0;
}

