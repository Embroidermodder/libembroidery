#include "embroidery.h"
#include <math.h>
#include <stdlib.h>

/**
 * Test for current level of compliance with:
 *     $ gcc -ansi -pedantic -Wall -O2 -c emb-outline.c
 *
 * This needs methods as functions:
 *
 * struct StitchBlock {
 *     IThread Thread { get; set; }
 *     double Angle { get; set; }
 *     List<VectorStitch> Stitches { get; set; }
 * }
 *
 * pass EmbPattern in its place.
 */

double _distanceTolerance;
double GetRelativeX(EmbVector a1, EmbVector a2, EmbVector a3);
double GetRelativeY(EmbVector a1, EmbVector a2, EmbVector a3);
double GetAngle(EmbVector a1, EmbVector a2);
void embPattern_breakIntoColorBlocks(EmbPattern *pattern);
int embPolygon_breakIntoSeparateObjects(EmbArray *blocks);
int FindOutline(EmbArray *stitchBlocks, EmbArray *outline);
void DrawGraphics(EmbPattern *p);
void SimplifyOutline(EmbPattern *pattern);
int embPolygon_collinearSimplify(EmbArray *vertices, float collinearityTolerance);
int CollinearSimplify(EmbArray *vertices);
int embPolygon_DouglasPeuckerSimplify(EmbArray *vertices, float distanceTolerance);
void embPolygon_simplifySection(EmbArray *vertices, EmbArray *_usePt, int i, int j);
double embVector_distancePointLine(EmbVector p, EmbVector a, EmbVector b);
int embPolygon_reduceByArea(EmbArray *vertices, EmbArray *result, float areaTolerance);
void MergeParallelEdges(EmbArray *vertices, float tolerance);
int embPolygon_reduceByNth(EmbArray *vertices, int nth);
int resampleArray(EmbArray *vertices, EmbArray *_usePt);
int embPolygon_reduceByDistance(EmbArray *vertices, float distance);
int embVector_collinear(EmbVector, EmbVector, EmbVector, double);


double GetRelativeX(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector c12, c32;
    embVector_subtract(a1, a2, &c12);
    embVector_subtract(a3, a2, &c32);
    return embVector_dot(c12, c32);
}

double GetRelativeY(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector c12, c32;
    embVector_subtract(a1, a2, &c12);
    embVector_subtract(a3, a2, &c32);
    return c12.x * c32.y - c12.y * c32.x;
}

double GetAngle(EmbVector a, EmbVector b)
{
    EmbVector h;
    embVector_subtract(a, b, &h);
    return atan2(h.x, h.y);
}

void embPattern_breakIntoColorBlocks(EmbPattern *pattern)
{
    /*
    EmbColor color;
    int oldColor, i;
    EmbStitch s;
    VectorStitch vs;
    var sa2 = new StitchBlock();
    oldColor = pattern.StitchList[0].ColorIndex;
    color = pattern.ColorList[oldColor];
    sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
    for (i=0; i<pattern->stitchList->count; i++) {
        s = pattern->stitchList->stitch[i];
        if (s.ColorIndex != oldColor) {
            yield return sa2;
            sa2 = new StitchBlock();
            color = pattern.ColorList[s.ColorIndex];
            sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
            oldColor = s.ColorIndex;
        }
        vs = new VectorStitch { Xy = new Point(s.X, s.Y), Color = s.ColorIndex };
        sa2.Stitches.Add(vs);
    }
    yield return sa2;
    */
}

/**
 * Originally the argument was:
 *     EmbStitchBlock* blocks
 * In order for this to work we need an EmbArray of EmbArrays, so
 * one of the types should be EMB_ARRAY. 
 */
int embPolygon_breakIntoSeparateObjects(EmbArray *blocks)
{
#if 0
    int i, j;
    double dx, dy, dy2, dy3;
    double previousAngle = 0.0;
    EmbArray *block;
    EmbArray stitches;
    for (j=0; j<blocks->count; j++) {
        block = blocks->array[j];
        stitches = embArray(EMB_STITCH); /* new List<VectorStitch>(); */
        block->stitchList[0].type = VectorStitchType.Contour;
        block->stitchList[block->count - 1].type = VectorStitchType.Contour;

        for (i = 0; i < block.Stitches->count - 2; i++) { /* step 0 */
            dx = (GetRelativeX(block.Stitches[i].Xy, block.Stitches[i + 1].Xy, block.Stitches[i + 2].Xy));
            block.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
            block.Stitches[i].Angle = GetAngle(block.Stitches[i], block.Stitches[i + 1]);
            stitches.Add(block.Stitches[i].Clone());
            if (i > 0) {
                if ((block.Stitches[i].Type == VectorStitchType.Contour) && Math.Abs(block.Stitches[i].Angle - previousAngle) > (20/180*embConstantPi))
                {
                    yield return
                        new StitchBlock {
                                Stitches = stitches,
                                Angle = stitches.Average(x => x.Angle),
                                Thread = new Thread(block.Thread.Red, block.Thread.Blue, block.Thread.Green)
                            };
                    stitches = new List<VectorStitch>();
                }
            }
        }

        /* step 1 */
        for (i = 1; i < pattern->stitches->count - 3; i++) {
            if (pattern->stitches->stitch[i + 1].type == VectorStitchType.Contour) {
                dy = GetRelativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY);
                dy2 = GetRelativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY);
                dy3 = GetRelativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY);
                //if(dy)
                if (sa.Stitches[i - 1].Type == VectorStitchType.Run || sa.Stitches[i + 1].Type == VectorStitchType.Run)
                {
                    sa.Stitches[i].Type = VectorStitchType.Tatami;
                }
                else {
                    sa.Stitches[i].Type = VectorStitchType.Satin;
                }
            }
        }
    }
#endif
    return 0;
}

/**
 * Originally:
 *     StitchObject * FindOutline(EmbStitchBlock* stitchData)
 * 
 */
int FindOutline(EmbArray *stitchBlocks, EmbArray *outline)
{
#if 0
    int currColorIndex = 0, oddEven, i, j;
    float dx, dy, dy2, dy3;
    EmbArray sa, *pOdd, *pEven;
    pOdd = embArray_create(EMB_POINT);
    pEven = embArray_create(EMB_POINT);
    for (j=0; j<stitchBlocks->count; j++) { 
        sa = stitchBlocks->array[j];
        if (sa->count > 0) {
            sa.Stitches[0].Type = VectorStitchType.Contour;
            sa.Stitches[sa.Stitches->count - 1].Type = VectorStitchType.Contour;
            /* step 0 */
            for (i = 0; i < sa.Stitches->count - 2; i++) {
                dx = (GetRelativeX(sa.Stitches[i].Xy, sa.Stitches[i + 1].Xy, sa.Stitches[i + 2].Xy));
                sa.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
                sa.Stitches[i].Angle = GetAngle(sa.Stitches[i], sa.Stitches[i + 1]);
            }
            /* step 1 */
            for (i = 1; i < sa.Stitches->count - 3; i++) {
                if (sa.Stitches[i + 1].Type == VectorStitchType.Contour) {
                    float dy = GetRelativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY);
                    float dy2 = GetRelativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY);
                    float dy3 = GetRelativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY);
                    //if(dy)
                    if (sa.Stitches[i - 1].Type == VectorStitchType.Run || sa.Stitches[i + 1].Type == VectorStitchType.Run)
                    {
                        sa.Stitches[i].Type = VectorStitchType.Tatami;
                    }
                    else {
                        sa.Stitches[i].Type = VectorStitchType.Satin;
                    }
                }
            }
        }


        oddEven = 0;
        foreach (VectorStitch t in sa.Stitches) {
            if ((t.Type == VectorStitchType.Contour) && (oddEven % 2) == 0) {
                pEven.Add(t.Xy);
                oddEven++;
            }
            else if ((t.Type == VectorStitchType.Contour) && (oddEven % 2) == 1) {
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
    embArray_free(pOdd);
    embArray_free(pEven);
#endif
    return 0;
}

void DrawGraphics(EmbPattern *p)
{
#if 0
    var stitchData = BreakIntoColorBlocks(p);

    /*
    var outBlock = new List<StitchBlock>(BreakIntoSeparateObjects(stitchData));
    foreach(var block in stitchData) {
        foreach (var stitch in block.Stitches) {
            if(stitch.Angle != 0) {
                int aaa = 1;
            }
        }
    }
    */
    //var xxxxx = outBlock;
    var objectsFound = FindOutline(stitchData);
    var outPattern = new Pattern();
    outPattern.AddColor(new Thread(255, 0, 0, "none", "None"));
    int colorIndex = outPattern.ColorList->count - 1;
    var r = new Random();
    foreach (StitchObject stitchObject in objectsFound) {
        if (stitchObject.SideOne->count > 1 && stitchObject.SideTwo->count > 1) {
            outPattern.AddColor(new Thread((byte) (r.Next()%256), (byte) (r.Next()%256), (byte) (r.Next()%256),
                                           "none", "None"));
            colorIndex++;
            outPattern.AddStitchRelative(0, 0, StitchTypes.Stop);
            var points = stitchObject.Generate2(75);
            foreach (var point in points) {
                outPattern.AddStitchAbsolute(point.X, point.Y, StitchTypes.Normal);
            }
            /*
            break;
            Point t;
            StitchObject stitchObject = objectsFound[1];
            if (stitchObject.SideOne->count > 0) {
                outPattern.StitchList.Add(new Stitch(stitchObject.SideOne[0].x, stitchObject.SideOne[0].y,
                                                     StitchType.Jump, colorIndex));
            }
            foreach (t in stitchObject.SideOne) {
                outPattern.StitchList.Add(new Stitch(t.x, t.y, StitchType.Normal, colorIndex));
            }
            foreach (t in stitchObject.SideTwo) {
                outPattern.StitchList.Add(new Stitch(t.x, t.y, StitchType.Normal, colorIndex));
            }
            break;
            */
        }
    }
    outPattern.AddStitchRelative(0, 0, StitchTypes.End);
    return outPattern;
    /* return (SimplifyOutline(outPattern)); */
#endif
}

void SimplifyOutline(EmbPattern *pattern)
{
    /*
    var v = new Vertices();
    v.AddRange(pattern.StitchList.Select(point => new Vector2(point.X, point.Y)));
    var output = SimplifyTools.DouglasPeuckerSimplify(v, 10);
    var patternOut = new Pattern();
    foreach (var color in pattern.ColorList) {
        patternOut.AddColor(color);
    }

    foreach (var vertex in output) {
        patternOut.AddStitchAbsolute(vertex.X, vertex.Y, StitchTypes.Normal);
    }
    patternOut.AddStitchRelative(0, 0, StitchTypes.End);
    return patternOut;
    */
}

/* Removes all collinear points on the polygon. */
int embPolygon_collinearSimplify(EmbArray *vertices, float collinearityTolerance)
{
    int i, prevId, nextId;
    EmbVector prev, current, next;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->count < 3) {
        return 0;
    }

    /*
    var simplified = new Vertices();
    */

    for (i = 0; i < vertices->count; i++) {
        prevId = (i-1+vertices->count) % vertices->count;
        nextId = (i+1) % vertices->count;

        prev = vertices->vector[prevId];
        current = vertices->vector[i];
        next = vertices->vector[nextId];

        /* If they are collinear, continue */
        if (embVector_collinear(prev, current, next, collinearityTolerance)) {
            continue;
        }

        /*
        simplified.Add(current);
        */
    }

    return 1;
}

/**
 * Removes all collinear points on the polygon. Has a default bias of 0.
 *
 * @param vertices The polygon that needs simplification.
 * @returns A simplified polygon.
 */
int CollinearSimplify(EmbArray *vertices)
{
/*
    return CollinearSimplify(vertices, 0);
*/
    return 1;
}

/**
 * Ramer-Douglas-Peucker polygon simplification algorithm.
 * This is the general recursive version that does not use the
 * speed-up technique by using the Melkman convex hull.
 * If you pass in 0, it will remove all collinear points.
 */
int embPolygon_DouglasPeuckerSimplify(EmbArray *vertices, float distanceTolerance)
{
    int i;
    EmbArray *_usePt;
    _distanceTolerance = distanceTolerance;

    _usePt = embArray_create(EMB_FLAG);
    for (i = 0; i < vertices->count; i++) {
        embArray_addFlag(_usePt, 1);
    }
    embPolygon_simplifySection(vertices, _usePt, 0, vertices->count - 1);
    resampleArray(vertices, _usePt);
    return 1;
}

/* Recursive algorithm that simplifies polygons.
 *
 */
void embPolygon_simplifySection(EmbArray *vertices, EmbArray *_usePt, int i, int j)
{
    int k, maxIndex;
    EmbVector a, b;
    double maxDistance, distance;
    if ((i + 1) == j)
        return;

    a = vertices->vector[i];
    b = vertices->vector[j];
    maxDistance = -1.0;
    maxIndex = i;

    for (k = i + 1; k < j; k++) {
        distance = embVector_distancePointLine(vertices->vector[k], a, b);

        if (distance > maxDistance) {
            maxDistance = distance;
            maxIndex = k;
        }
    }
    if (maxDistance <= _distanceTolerance) {
        for (k = i + 1; k < j; k++) {
            _usePt->flag[k] = 0;
        }
    }
    else {
        embPolygon_simplifySection(vertices, _usePt, i, maxIndex);
        embPolygon_simplifySection(vertices, _usePt, maxIndex, j);
    }
    
}

/**
 * Find the distance from (\a p) to the line from (\a a) to (\a b) by
 * finding the length of the normal from ab (extended to an infinte line)
 * to p.
 */
double embVector_distancePointLine(EmbVector p, EmbVector a, EmbVector b)
{
    double r, curve2, s, tolerence;
    EmbVector pa, ba;
    
    tolerence = 0.00001;
    embVector_subtract(b, a, &ba);
    /* if start == end, then use point-to-point distance */
    if (fabs(ba.x) < tolerence && fabs(ba.y) < tolerence) {
        return embVector_distance(p, a);
    }

    /* otherwise use comp.graphics.algorithms Frequently Asked Questions method */
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

    embVector_subtract(p, a, &pa);
    curve2 = embVector_dot(ba, ba);
    r = embVector_dot(pa, ba) / curve2;

    if (r <= 0.0) return embVector_distance(p, a);
    if (r >= 1.0) return embVector_distance(p, b);

    /*(2)
                    (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)
                s = -----------------------------
                                Curve^2

                Then the distance from C to Point = |s|*Curve.
    */

    s = (pa.x * ba.y - pa.y * ba.x) / curve2;

    return fabs(s) * sqrt(curve2);
}

/**
 * From physics2d.net
 * Assumes that the caller has declared result, that way we can pass the same
 * pointer to both arguments for in-place reduction.
 */
int embPolygon_reduceByArea(EmbArray *vertices, EmbArray *result, float areaTolerance)
{
    float old1, old2, new1;
    int index;
    EmbVector v1, v2, v3;
    EmbArray *_usePt;
    if (vertices->count <= 3) {
        return 0;
    }

    if (areaTolerance < 0) {
        embLog("areaTolerance must be equal to or greater than zero.");
        return 0;
    }

    _usePt = embArray_create(EMB_FLAG);

    v1 = vertices->vector[vertices->count - 2];
    v2 = vertices->vector[vertices->count - 1];
    areaTolerance *= 2;
    for (index = 0; index < vertices->count; ++index, v2 = v3) {
        if (index == vertices->count - 1) {
            if (result->count == 0) {
                embLog("areaTolerance is too high.");
                return 0;
            }
            v3 = result->vector[0]; /* ? */
        }
        else {
            v3 = vertices->vector[index];
        }
        old1 = embVector_cross(v1, v2);
        old2 = embVector_cross(v2, v3);
        new1 = embVector_cross(v1, v3);
        if (fabs(new1 - (old1 + old2)) > areaTolerance) {
            embArray_addVector(result, v2);
            v1 = v2;
        }
    }

    resampleArray(result, _usePt);
    embArray_free(_usePt);
    return 1;
}

/**
 * From Eric Jordan's convex decomposition library
 * Merges all parallel edges in the list of vertices
 */
void MergeParallelEdges(EmbArray *vertices, float tolerance)
{
    int lower, upper, i, newNVertices, currIndex;
    EmbVector d0, d1;
    float norm0, norm1, cross, dot;
    EmbArray *_usePt;
    if (vertices->count <= 3) {
        return; /* Can't do anything useful here to a triangle */
    }

    _usePt = embArray_create(EMB_FLAG);
    newNVertices = vertices->count;

    /* Gather points to process */
    for (i = 0; i < vertices->count; ++i) {
        lower = (i+vertices->count-1) % vertices->count;
        upper = (i+1)% vertices->count;

        embVector_subtract(vertices->vector[i], vertices->vector[lower], &d0);
        embVector_subtract(vertices->vector[upper], vertices->vector[i], &d1);
        norm0 = embVector_getLength(d0);
        norm1 = embVector_getLength(d1);

        if (!(norm0 > 0.0f && norm1 > 0.0f) && newNVertices > 3) {
            /* Merge identical points */
            embArray_addFlag(_usePt, 0);
            --newNVertices;
            continue;
        }

        embVector_multiply(d0, 1.0/norm0, &d0);
        embVector_multiply(d1, 1.0/norm1, &d1);
        cross = embVector_cross(d0, d1);
        dot = embVector_dot(d0, d1);

        if (fabs(cross) < tolerance && dot > 0 && newNVertices > 3) {
            embArray_addFlag(_usePt, 0);
            --newNVertices;
        }
        else {
            embArray_addFlag(_usePt, 1);
        }
    }

    if (newNVertices == vertices->count || newNVertices == 0) {
        return;
    }

    resampleArray(vertices, _usePt);
    embArray_free(_usePt);
}

int resampleArray(EmbArray *vertices, EmbArray *_usePt)
{
    int i, j;
    j = 0;
    for (i=0; i<vertices->count; i++) {
        if (_usePt->flag[j]) {
            vertices->vector[j] = vertices->vector[i];
            j++;
        }
    }
    vertices->count = j;
    return 0;
}

/* Reduces the polygon by distance. */
int embPolygon_reduceByDistance(EmbArray *vertices, float distance)
{
    int i, nextId;
    double vdist;
    EmbArray *_usePt;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->count < 3) return 0;

    _usePt = embArray_create(EMB_FLAG);

    for (i = 0; i < vertices->count; i++) {
        nextId = (i+1) % vertices->count;

        vdist = embVector_distance(vertices->vector[i], vertices->vector[nextId]);

        if (vdist < distance) {
            embArray_addFlag(_usePt, 0);
        }
        else {
            embArray_addFlag(_usePt, 1);
        }
    }

    resampleArray(vertices, _usePt);
    return 1;
}

/* Reduces the polygon by removing the Nth vertex in the vertices list. */
int embPolygon_reduceByNth(EmbArray *vertices, int nth)
{
    int i;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->count < 3) return 0;

    /* Vertex is not present */
    if (nth >= vertices->count) return 0;

    /* This isn't an array of vectors. */
    if (vertices->type != EMB_VECTOR) return 0;

    /* Shift everything left one place then reduce the count. */
    for (i=nth; i<vertices->count - 1; i++) {
        vertices->vector[i] = vertices->vector[i+1];
    }
    vertices->count--;

    /* success, trust the data in vertices */
    return 1;
}

void embSatinOutline_generateSatinOutline(EmbArray *lines, double thickness, EmbSatinOutline* result)
{
    int i;
    EmbSatinOutline outline;
    double halfThickness = thickness / 2.0;
    int intermediateOutlineCount = 2 * lines->count - 2;
    EmbLine line1, line2;
    EmbVector out;

    outline.side1 = embArray_create(EMB_VECTOR);
    if (!outline.side1) {
        embLog("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for outline->side1\n");
        return;
    }
    outline.side2 = embArray_create(EMB_VECTOR);
    if (!outline.side2) {
        embLog("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for outline->side2\n");
        return;
    }

    for (i = 1; i < lines->count; i++) {
        int j = (i - 1) * 2;
        EmbVector v1;
        EmbVector temp;

        EmbLine line;
        line.start = lines->vector[j - 1];
        line.end = lines->vector[j];

        embLine_normalVector(line, &v1, 1);

        embVector_multiply(v1, halfThickness, &temp);
        embVector_add(temp, lines->vector[j - 1], &temp);
        embArray_addVector(outline.side1, temp);
        embVector_add(temp, lines->vector[j], &temp);
        embArray_addVector(outline.side1, temp);

        embVector_multiply(v1, -halfThickness, &temp);
        embVector_add(temp, lines->vector[j - 1], &temp);
        embArray_addVector(outline.side2, temp);
        embVector_add(temp, lines->vector[j], &temp);
        embArray_addVector(outline.side2, temp);
    }

    if (!result) {
        embLog("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), result argument is null\n");
        return;
    }
    result->side1 = embArray_create(EMB_VECTOR);
    if (!result->side1) {
        embLog("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side1\n");
        return;
    }
    result->side2 = embArray_create(EMB_VECTOR);
    if (!result->side2) {
        embLog("ERROR: emb-satin-line.c embSatinOutline_generateSatinOutline(), cannot allocate memory for result->side2\n");
        return;
    }

    embArray_addVector(result->side1, outline.side1->vector[0]);
    embArray_addVector(result->side2, outline.side2->vector[0]);

    for (i = 3; i < intermediateOutlineCount; i += 2) {
        line1.start = outline.side1->vector[i - 3];
        line1.end = outline.side1->vector[i - 2];
        line2.start = outline.side1->vector[i - 1];
        line2.end = outline.side1->vector[i];
        embLine_intersectionPoint(line1, line2, &out);
        embArray_addVector(result->side1, out);

        line1.start = outline.side2->vector[i - 3];
        line1.end = outline.side2->vector[i - 2];
        line2.start = outline.side2->vector[i - 1];
        line2.end = outline.side2->vector[i];
        embLine_intersectionPoint(line1, line2, &out);
        embArray_addVector(result->side2, out);
    }

    embArray_addVector(result->side1, outline.side1->vector[2 * lines->count - 3]);
    embArray_addVector(result->side2, outline.side2->vector[2 * lines->count - 3]);
    result->length = lines->count;
}

EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, double density)
{
    int i, j, numberOfSteps;
    EmbVector currTop, currBottom, topDiff, bottomDiff, midDiff;
    EmbVector midLeft, midRight, topStep, bottomStep;
    EmbArray* stitches = 0;
    double midLength;

    if (!result) {
        embLog("ERROR: emb-satin-line.c embSatinOutline_renderStitches(), result argument is null\n");
        return 0;
    }

    if (result->length > 0) {
        for (j = 0; j < result->length - 1; j++) {
            embVector_subtract(result->side1->vector[j+1], result->side1->vector[j], &topDiff);
            embVector_subtract(result->side2->vector[j+1], result->side2->vector[j], &bottomDiff);

            embVector_average(result->side1->vector[j], result->side2->vector[j], &midLeft);
            embVector_average(result->side1->vector[j+1], result->side2->vector[j+1], &midRight);

            embVector_subtract(midLeft, midRight, &midDiff);
            midLength = embVector_getLength(midDiff);

            numberOfSteps = (int)(midLength * density / 200);
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

