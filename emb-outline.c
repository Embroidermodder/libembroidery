#include "embroidery.h"
#include <math.h>

/* TODO: Add to CMakeLists.txt and libembroidery.pri when this is C89 complete.
 * This code isn't incorporated in the library or embroider currently.
 *
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
 *
 * _usePt needs malloc/free, perhaps EmbArray flags?
 */

int *_usePt;
double _distanceTolerance;

double LineLength(EmbVector a1, EmbVector a2)
{
    return sqrt(pow(a2.x - a1.x, 2) + pow(a2.y - a1.y, 2));
}

double embVector_distancePointPoint(EmbVector p, EmbVector2 p2)
{
    double dx = p.x - p2.x;
    double dy = p.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

float GetRelativeX(EmbVector a1, EmbVector a2, EmbVector a3)
{
    return ((a1.x - a2.x) * (a3.x - a2.x) + (a1.y - a2.y) * (a3.y - a2.y));
}

float GetRelativeY(EmbVector a1, EmbVector a2, EmbVector a3)
{
    return ((a1.x - a2.x) * (a3.y - a2.y) - (a1.y - a2.y) * (a3.x - a2.x));
}

double GetAngle(EmbVector a, EmbVector b)
{
    return atan2(a.x - b.x, a.y - b.y);
}

void embPattern_breakIntoColorBlocks(EmbPattern *pattern)
{
    EmbColor color;
    int oldColor, i;
    VectorStitch vs;
    var sa2 = new StitchBlock();
    oldColor = pattern.StitchList[0].ColorIndex;
    color = pattern.ColorList[oldColor];
    sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
    for (i=0; i<pattern->stitches->count; i++) {
        s = pattern->stitches->stitch[i];
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
}

int embPolygon_breakIntoSeparateObjects(EmbStitchBlock* blocks)
{
    int i, j;
    double dx, dy, dy2, dy3;
    double previousAngle = 0.0;
    for (j=0; j<blocks->count; j++) {
        block = blocks[j];
        var stitches = new List<VectorStitch>();
        block.Stitches[0].Type = VectorStitchType.Contour;
        block.Stitches[block.Stitches.Count - 1].Type = VectorStitchType.Contour;

        for (i = 0; i < block.Stitches.Count - 2; i++) { /* step 0 */
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
}

StitchObject * FindOutline(EmbStitchBlock* stitchData)
{
    int currColorIndex = 0, oddEven, i;
    float dx, dy, dy2, dy3;
    var pOdd = new List<Point>();
    var pEven = new List<Point>();
    foreach (StitchBlock sa in stitchData)
    {
        if (sa.Stitches.Count > 0)
        {
            sa.Stitches[0].Type = VectorStitchType.Contour;
            sa.Stitches[sa.Stitches.Count - 1].Type = VectorStitchType.Contour;
            /* step 0 */
            for (i = 0; i < sa.Stitches.Count - 2; i++) {
                dx = (GetRelativeX(sa.Stitches[i].Xy, sa.Stitches[i + 1].Xy, sa.Stitches[i + 2].Xy));
                sa.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
                sa.Stitches[i].Angle = GetAngle(sa.Stitches[i], sa.Stitches[i + 1]);
            }
            /* step 1 */
            for (i = 1; i < sa.Stitches.Count - 3; i++) {
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
}

EmbPattern DrawGraphics(EmbPattern p)
{
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
    int colorIndex = outPattern.ColorList.Count - 1;
    var r = new Random();
    foreach (StitchObject stitchObject in objectsFound) {
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
            /*
            break;
            Point t;
            StitchObject stitchObject = objectsFound[1];
            if (stitchObject.SideOne.Count > 0) {
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
}

void SimplifyOutline(EmbPattern pattern)
{
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

    var simplified = new Vertices();

    for (i = 0; i < vertices->count; i++) {
        prevId = vertices.PreviousIndex(i);
        nextId = vertices.NextIndex(i);

        prev = vertices[prevId];
        current = vertices[i];
        next = vertices[nextId];

        /* If they collinear, continue */
        if (MathUtils.Collinear(&prev, &current, &next, collinearityTolerance)) {
            continue;
        }

        simplified.Add(current);
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
    return CollinearSimplify(vertices, 0);
}

/**
 * Ramer-Douglas-Peucker polygon simplification algorithm. This is the general recursive version that does not use the
 * speed-up technique by using the Melkman convex hull.
 * If you pass in 0, it will remove all collinear points
 */
int embPolygon_DouglasPeuckerSimplify(EmbArray *vertices, float distanceTolerance)
{
    int i;
    EmbArray *_usePt;
    _distanceTolerance = distanceTolerance;

    _usePt = embArray_create(EMB_FLAG);
    for (i = 0; i < vertices->count; i++) {
        _usePt[i] = 1;
    }
    embPolygon_simplifySection(vertices, 0, vertices.Count - 1);
    var result = new Vertices();
    result.AddRange(vertices.Where((t, i) => _usePt[i]));
    return 1;
}

void embPolygon_simplifySection(EmbArray *vertices, int i, int j)
{
    int k, maxIndex;
    EmbArray a, b;
    double maxDistance, distance;
    if ((i + 1) == j)
        return;

    a = vertices[i];
    b = vertices[j];
    maxDistance = -1.0;
    maxIndex = i;
    for (k = i + 1; k < j; k++) {
        distance = DistancePointLine(vertices[k], a, b);

        if (distance > maxDistance) {
            maxDistance = distance;
            maxIndex = k;
        }
    }
    if (maxDistance <= _distanceTolerance) {
        for (k = i + 1; k < j; k++) {
            _usePt[k] = 0;
        }
    }
    else {
        SimplifySection(vertices, i, maxIndex);
        SimplifySection(vertices, maxIndex, j);
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
        return embVector_DistancePointPoint(p, a);
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

    if (r <= 0.0) return embVector_distancePointPoint(p, a);
    if (r >= 1.0) return embVector_distancePointPoint(p, b);

    /*(2)
                    (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)
                s = -----------------------------
                                Curve^2

                Then the distance from C to Point = |s|*Curve.
    */

    s = (pa.x * ba.y - pa.y * ba.x) / curve2;

    return fabs(s) * sqrt(curve2);
}

/* From physics2d.net */
int embPolygon_reduceByArea(EmbArray *vertices, float areaTolerance)
{
    float old1, old2, new1;
    int index;
    EmbVector v1, v2, v3;
    EmbArray *result;
    if (vertices->count <= 3) {
        return 0;
    }

    if (areaTolerance < 0) {
        throw new ArgumentOutOfRangeException("areaTolerance", "must be equal to or greater then zero.");
    }

    result = new Vertices();
    v1 = vertices[vertices.Count - 2];
    v2 = vertices[vertices.Count - 1];
    areaTolerance *= 2;
    for (index = 0; index < vertices.Count; ++index, v2 = v3) {
        if (index == vertices.Count - 1) {
            if (result->count == 0) {
                throw new ArgumentOutOfRangeException("areaTolerance", "The tolerance is too high!");
            }
            v3 = result[0];
        }
        else {
            v3 = vertices[index];
        }
        old1 = embVector_cross(v1, v2);
        old2 = embVector_cross(v2, v3);
        new1 = embVector_cross(v1, v3);
        if (fabs(new1 - (old1 + old2)) > areaTolerance) {
            embArray_addVector(result, v2);
            v1 = v2;
        }
    }
    return result;
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
    EmbArray *mergeMe;
    if (vertices->count <= 3) {
        return; /* Can't do anything useful here to a triangle */
    }

    mergeMe = embVector_create(EMB_FLAG);
    newNVertices = vertices->count;

    /* Gather points to process */
    for (i = 0; i < vertices->count; ++i) {
        lower = (i+vertices->count-1) % vertices->count;
        upper = (i+1)% vertices->count;

        embVector_subtract(vertices[i], vertices[lower], &d0);
        embVector_subtract(vertices[upper], vertices[i], &d1);
        norm0 = embVector_getLength(d0);
        norm1 = embVector_getLength(d1);

        if (!(norm0 > 0.0f && norm1 > 0.0f) && newNVertices > 3) {
            /* Merge identical points */
            embArray_addFlag(mergeMe, 1);
            --newNVertices;
            continue;
        }

        embVector_multiply(d0, 1.0/norm0, &d0);
        embVector_multiply(d1, 1.0/norm1, &d1);
        cross = embVector_cross(d0, d1); /* dx0 * dy1 - dx1 * dy0; */
        dot = embVector_dot(d0, d1);

        if (fabs(cross) < tolerance && dot > 0 && newNVertices > 3) {
            embArray_addFlag(mergeMe, 1);
            --newNVertices;
        }
        else {
            embArray_addFlag(mergeMe, 0);
        }
    }

    if (newNVertices == vertices->count || newNVertices == 0) {
        return;
    }

    currIndex = 0;

    /* Copy the vertices to a new list and clear the old */
    var oldVertices = new Vertices(vertices);
    vertices.Clear();

    for (i = 0; i < oldVertices.Count; ++i) {
        if (mergeMe[i] || newNVertices == 0 || currIndex == newNVertices)
            continue;

        vertices.Add(oldVertices[i]);
        ++currIndex;
    }
}

/* Reduces the polygon by distance. */
int embPolygon_reduceByDistance(EmbArray *vertices, float distance)
{
    int i, nextId;
    double vdist;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->count < 3) return 0;

    simplified = new Vertices();

    for (i = 0; i < vertices->count; i++) {
        nextId = vertices.NextIndex(i);

        vdist = embDistancePointPoint(vertices[i], vertices[nextId]);

        /* If they are closer than the distance, continue */
        if (vdist < distance) {
            continue;
        }

        embArray_addVector(simplified, current);
    }

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
