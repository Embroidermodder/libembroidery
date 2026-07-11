#include "embroidery.h"

#if 0
/* a pattern
 * Returns StitchBlock*
 */
StitchBlock *BreakIntoColorBlocks(EmbPattern *pattern)
{
    int i;
    int sa2 = new StitchBlock();
    int oldColor = pattern->stitch_list->stitch[0].color;
    int color = pattern.ColorList[oldColor];
    sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch s = pattern->stitch_list->stitch[i];
        if (s.color != oldColor) {
            yield return sa2;
            sa2 = new StitchBlock();
            color = pattern.ColorList[s.ColorIndex];
            sa2.Thread = new Thread(color.Red, color.Blue, color.Green);
            oldColor = s.ColorIndex;
        }
        int vs = new VectorStitch { Xy = new Point(s.X, s.Y), Color =
                s.ColorIndex
        };
        sa2.Stitches.Add(vs);
    }
    yield return sa2;
}

/* a blocks
 * Returns StitchBlock*
 */
StitchBlock *BreakIntoSeparateObjects(EmbStitchBlock *blocks)
{
    int i, block;
    EmbReal previousAngle = 0.0;
    for (block = 0; block < blocks->length; block++) {
        int stitches = new List < VectorStitch > ();
        block.Stitches[0].Type = VectorStitchType.Contour;
        block.Stitches[block.Stitches.Count - 1].Type =
            VectorStitchType.Contour;

        for (int i = 0; i < block.Stitches.Count - 2; i++) {    /* step 0 */
            EmbReal dx =
                (emb_vector_relativeX
                 (block.Stitches[i].Xy, block.Stitches[i + 1].Xy,
                  block.Stitches[i + 2].Xy));
            block.Stitches[i + 1].Type =
                dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
            block.Stitches[i].Angle =
                GetAngle(block.Stitches[i], block.Stitches[i + 1]);
            stitches.Add(block.Stitches[i].Clone());
            if (i > 0) {
                if ((block.Stitches[i].Type == VectorStitchType.Contour)
                    && fabs(block.Stitches[i].Angle -
                            previousAngle) > (20 / 180 * embConstantPi)) {
                    yield return new StitchBlock {
                        Stitches = stitches,
                            Angle = stitches.Average(x =
                                                     >x.Angle),
                            Thread =
                            new Thread(block.Thread.Red,
                                       block.Thread.Blue, block.Thread.Green)
                    };
                    stitches = new List < VectorStitch > ();

                }
            }
        }

        /* step 1 */
        for (i = 1; i < sa.Stitches.Count - 3; i++) {
            if (sa.Stitches[i + 1].Type == VectorStitchType.Contour) {
                float dy = emb_vector_relativeY(sa[i + 1].XY,
                                                sa[i + 2].XY,
                                                sa[i + 3].XY);
                float dy2 = emb_vector_relativeY(sa[i].XY, sa[i + 1].XY,
                                                 sa[i + 2].XY);
                float dy3 = emb_vector_relativeY(sa[i + 2].XY,
                                                 sa[i + 3].XY,
                                                 sa[i + 4].XY);
                if (dy)
                    if (sa.Stitches[i - 1].Type ==
                        VectorStitchType.Run
                        || sa.Stitches[i + 1].Type == VectorStitchType.Run) {
                        sa.Stitches[i].Type = VectorStitchType.Tatami;
                    } else {
                        sa.Stitches[i].Type = VectorStitchType.Satin;
                    }
            }
        }
    }
}

/* a stitchData
 * Returns StitchObject*
 */
StitchObject *FindOutline(EmbStitchBlock *stitchData)
{
    int currColorIndex = 0, sa;
    int pOdd = new List < Point > ();
    int pEven = new List < Point > ();
    for (sa = 0; sa < stitchData->count; sa++) {
        if (sa.Stitches.Count > 0) {
            sa.Stitches[0].Type = VectorStitchType.Contour;
            sa.Stitches[sa.Stitches.Count - 1].Type = VectorStitchType.Contour;
            /* step 0 */
            for (int i = 0; i < sa.Stitches.Count - 2; i++) {
                float dx =
                    (GetRelativeX(sa.Stitches[i].Xy, sa.Stitches[i + 1].Xy,
                                  sa.Stitches[i + 2].Xy));
                sa.Stitches[i + 1].Type =
                    dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour;
                sa.Stitches[i].Angle =
                    emb_vector_angle(sa.Stitches[i], sa.Stitches[i + 1]);
            }
            /* step 1 */
            for (int i = 1; i < sa.Stitches.Count - 3; i++) {
                if (sa.Stitches[i + 1].Type == VectorStitchType.Contour) {
                    float dy = emb_vector_relativeY(sa[i + 1].XY,
                                                    sa[i + 2].XY,
                                                    sa[i + 3].XY);
                    float dy2 = emb_vector_relativeY(sa[i].XY,
                                                     sa[i + 1].XY,
                                                     sa[i + 2].XY);
                    float dy3 = emb_vector_relativeY(sa[i + 2].XY,
                                                     sa[i + 3].XY,
                                                     sa[i + 4].XY);
                    if (dy)
                        if (sa.Stitches[i - 1].Type ==
                            VectorStitchType.Run
                            || sa.Stitches[i +
                                           1].Type == VectorStitchType.Run) {
                            sa.Stitches[i].Type = VectorStitchType.Tatami;
                        } else {
                            sa.Stitches[i].Type = VectorStitchType.Satin;
                        }
                }
            }
        }

        int oddEven = 0;
        foreach(VectorStitch t in sa.Stitches) {
            if ((t.Type == VectorStitchType.Contour)
                && (oddEven % 2) == 0) {
                pEven.Add(t.Xy);

                oddEven++;
            } else if ((t.Type == VectorStitchType.Contour)
                       && (oddEven % 2) == 1) {
                pOdd.Add(t.Xy);
                oddEven++;
            }
        }
        currColorIndex++;
        int so = new StitchObject { SideOne = pEven, SideTwo =
                pOdd, ColorIndex = currColorIndex
        };
        yield return so;
        pEven = new List < Point > ();
        pOdd = new List < Point > ();
        /* break; */
    }
}

/* a p
 * Returns EmbPattern
 */
EmbPattern DrawGraphics(EmbPattern p)
{
    int stitchData = BreakIntoColorBlocks(p);

    int outBlock =
        new List < StitchBlock > (BreakIntoSeparateObjects(stitchData));
    foreach(var block in stitchData) {
        foreach(var stitch in block.Stitches) {
            if (stitch.Angle != 0) {
                int aaa = 1;
            }
        }
    }
    int xxxxx = outBlock;
    int objectsFound = FindOutline(stitchData);
    int outPattern = new Pattern();
    outPattern.AddColor(new Thread(255, 0, 0, "none", "None"));
    int colorIndex = outPattern.ColorList.Count - 1;
    int r = new Random();
    foreach(StitchObject stitchObject in objectsFound) {
        if (stitchObject.SideOne.Count > 1 && stitchObject.SideTwo.Count > 1) {
            outPattern.AddColor(new
                                Thread((byte) (r.Next() % 256),
                                       (byte) (r.Next() % 256),
                                       (byte) (r.Next() % 256),
                                       "none", "None"));
            colorIndex++;
            outPattern.AddStitchRelative(0, 0, StitchTypes.Stop);
            int points = stitchObject.Generate2(75);
            foreach(var point in points) {
                outPattern.AddStitchAbsolute(point.X, point.Y,
                                             StitchTypes.Normal);
            }
            break;
            StitchObject stitchObject = objectsFound[1];
            ))
                if (stitchObject.SideOne.Count > 0) {
                outPattern.stitch_list.Add(new
                                           Stitch
                                           (stitchObject.SideOne
                                            [0].X,
                                            stitchObject.SideOne
                                            [0].Y,
                                            StitchType.Jump, colorIndex));
            }
            foreach(Point t in stitchObject.SideOne) {

                outPattern.stitch_list.Add(new Stitch(t.X, t.Y,
                                                      StitchType.Normal,
                                                      colorIndex));
            }
            foreach(Point t in stitchObject.SideTwo) {
                outPattern.stitch_list.Add(new Stitch(t.X, t.Y,
                                                      StitchType.Normal,
                                                      colorIndex));
            }
            break;
        }
    }
    outPattern.AddStitchRelative(0, 0, StitchTypes.End);
    return outPattern;
    /*
       return (SimplifyOutline(outPattern));
     */
}

/* a pattern
 * Returns EmbPattern
 */
EmbPattern SimplifyOutline(EmbPattern pattern) {
    int v = new Vertices();
    v.AddRange(pattern.stitch_list.
               Select(point = >new Vector2(point.X, point.Y)));
    int output = SimplifyTools.DouglasPeuckerSimplify(v, 10);
    int patternOut = new Pattern();
    foreach(var color in pattern.ColorList) {
        patternOut.AddColor(color);
    }

    foreach(var vertex in output) {
        patternOut.AddStitchAbsolute(vertex.X, vertex.Y, StitchTypes.Normal);
    }
    patternOut.AddStitchRelative(0, 0, StitchTypes.End);
    return patternOut;
}

bool[]_usePt;
EmbReal _distanceTolerance;

/* Removes all collinear points on the polygon.
 *
 * a vertices
 * a collinearityTolerance
 * Returns Vertices
 */
Vertices CollinearSimplify(Vertices vertices, float collinearityTolerance) {
    /* We can't simplify polygons under 3 vertices */
    if (vertices.Count < 3)
        return vertices;

    int simplified = new Vertices();

    for (int i = 0; i < vertices.Count; i++) {
        int prevId = vertices.PreviousIndex(i);
        int nextId = vertices.NextIndex(i);

        Vector2 prev = vertices[prevId];
        Vector2 current = vertices[i];
        Vector2 next = vertices[nextId];

        /* If they collinear, continue */
        if (emb_vector_collinear
            (ref prev, ref current, ref next, collinearityTolerance))
            continue;

        simplified.Add(current);
    }

    return simplified;
}

/* vertices
 * Returns Vertices
 *
 * Removes all collinear points on the polygon. Has a default bias of 0.
 *
 * param vertices: The polygon that needs simplification.
 * returns: A simplified polygon.
 */
Vertices CollinearSimplify(Vertices vertices) {
    return CollinearSimplify(vertices, 0);
}

/* vertices
 * a distanceTolerance
 * Returns Vertices
 *
 * Ramer-Douglas-Peucker polygon simplification algorithm.
 * This is the general recursive version that does not use the
 * speed-up technique by using the Melkman convex hull.
 * If you pass in 0, it will remove all collinear points.
 *
 * \todo Ramer-Douglas-Peucker citation
 */
Vertices DouglasPeuckerSimplify(Vertices vertices, float distanceTolerance) {
    _distanceTolerance = distanceTolerance;

    _usePt = new bool[vertices.Count];
    for (int i = 0; i < vertices.Count; i++) {
        _usePt[i] = true;
    }
    SimplifySection(vertices, 0, vertices.Count - 1);
    int result = new Vertices();
    result.AddRange(vertices.Where((t, i) = >_usePt[i]));
    return result;
}

/*  vertices a i a j */
void SimplifySection(Vertices vertices, int i, int j) {
    if ((i + 1) == j)
        return;

    Vector2 a = vertices[i];
    Vector2 b = vertices[j];
    EmbReal maxDistance = -1.0;
    int maxIndex = i;
    for (int k = i + 1; k < j; k++) {
        EmbReal distance = DistancePointLine(vertices[k], a, b);

        if (distance > maxDistance) {
            maxDistance = distance;
            maxIndex = k;
        }
    }
    if (maxDistance <= _distanceTolerance) {
        for (int k = i + 1; k < j; k++) {
            _usePt[k] = 0;
        }
    } else {
        SimplifySection(vertices, i, maxIndex);
        SimplifySection(vertices, maxIndex, j);
    }
}

/* p a a a b
 * Returns EmbReal
 */
EmbReal DistancePointLine(EmbVector p, EmbVector a, EmbVector b) {
    /* if start == end, then use point-to-point distance */
    if (a.X == b.X && a.Y == b.Y)
        return DistancePointPoint(p, a);

    /* otherwise use comp.graphics.algorithms Frequently Asked Questions method */
    /* (1)               AC dot AB
       r =   ---------
       ||AB||^2

       r has the following meaning:
       r=0 Point = A
       r=1 Point = B
       r<0 Point is on the backward extension of AB
       r>1 Point is on the forward extension of AB
       0<r<1 Point is interior to AB
     */

    EmbReal r = ((p.X - a.X) * (b.X - a.X) + (p.Y - a.Y) * (b.Y - a.Y))
        / ((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y));

    if (r <= 0.0)
        return DistancePointPoint(p, a);
    if (r >= 1.0)
        return DistancePointPoint(p, b);

    /* (2)
       (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)
       s = -----------------------------
       Curve^2

       Then the distance from C to Point = |s|*Curve.
     */

    EmbReal s = ((a.Y - p.Y) * (b.X - a.X) - (a.X - p.X) * (b.Y - a.Y))
        / ((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y));

    return fabs(s) *
        sqrt(((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y)));
}

/* vertices a areaTolerance
 * Returns public
 *
 * From physics2d.net.
 */
public Vertices ReduceByArea(Vertices vertices, float areaTolerance) {
    if (vertices.Count <= 3)
        return vertices;

    if (areaTolerance < 0) {
        throw new ArgumentOutOfRangeException("areaTolerance",
                                              "must be equal to or greater then zero.");
    }

    int result = new Vertices();
    Vector2 v3;
    Vector2 v1 = vertices[vertices.Count - 2];
    Vector2 v2 = vertices[vertices.Count - 1];
    areaTolerance *= 2;
    for (int index = 0; index < vertices.Count; ++index, v2 = v3) {
        if (index == vertices.Count - 1) {
            if (result.Count == 0) {
                throw new
                    ArgumentOutOfRangeException("areaTolerance",
                                                "The tolerance is too high!");
            }
            v3 = result[0];
        } else {
            v3 = vertices[index];
        }
        float old1, old2, new1;
        MathUtils.Cross(ref v1, ref v2, out old1);
        MathUtils.Cross(ref v2, ref v3, out old2);
        MathUtils.Cross(ref v1, ref v3, out new1);
        if (fabs(new1 - (old1 + old2)) > areaTolerance) {
            result.Add(v2);
            v1 = v2;
        }
    }
    return result;
}

/* vertices a tolerance
 *
 * From Eric Jordan's convex decomposition library.
 * Merges all parallel edges in the list of vertices.
 */
void
 MergeParallelEdges(EmbArray * vertices, float tolerance) {
    int i;
    if (vertices.Count <= 3) {
        /* Can't do anything useful here to a triangle. */
        return;
    }

    int mergeMe = new bool[vertices.Count];
    int newNVertices = vertices.Count;

    /* Gather points to process */
    for (i = 0; i < vertices->count; i++) {
        EmbVector delta0, delta1;
        int lower = (i == 0) ? (vertices.Count - 1) : (i - 1);
        int upper = (i == vertices.Count - 1) ? (0) : (i + 1);

        delta0 = emb_vector_subtract(vertices[i], vertices[lower]);
        delta1 = emb_vector_subtract(vertices[upper], vertices[i]);
        float norm0 = emb_vector_length(delta0);
        float norm1 = emb_vector_length(delta0);

        if (!(norm0 > 0.0f && norm1 > 0.0f) && newNVertices > 3) {
            /* Merge identical points */
            mergeMe[i] = 1;
            newNVertices--;
        }

        delta0 = emb_vector_normalize(delta0);
        delta1 = emb_vector_normalize(delta1);
        float cross = emb_vector_cross(delta0, delta1);
        float dot = emb_vector_dot(delta0, delta1);

        if (fabs(cross) < tolerance && dot > 0 && newNVertices > 3) {
            mergeMe[i] = 1;
            newNVertices--;
        } else {
            mergeMe[i] = 0;
        }
    }

    if (newNVertices == vertices.Count || newNVertices == 0)
        return;

    int currIndex = 0;

    /* Copy the vertices to a new list and clear the old */
    int oldVertices = new Vertices(vertices);
    vertices.Clear();

    for (i = 0; i < oldVertices.Count; i++) {
        if (mergeMe[i] || newNVertices == 0 || currIndex == newNVertices)
            continue;

        vertices.Add(oldVertices[i]);
        currIndex++;
    }
}
#endif

void embPolygon_reduceByDistance(EmbArray * vertices, EmbArray * simplified,
                                 float distance);
void embPolygon_reduceByNth(EmbArray * vertices, EmbArray * out, int nth);

/* vertices a simplified a distance
 *
 * Reduces the polygon by distance.
 *
 * This is a non-destructive function, so the caller is responsible for
 * freeing "vertices" if they choose to keep "simplified".
 */
void embPolygon_reduceByDistance(EmbArray * vertices, EmbArray * simplified,
                                 float distance) {
    int i;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->count < 3) {
        emb_array_copy(simplified, vertices);
        return;
    }

    for (i = 0; i < vertices->count; i++) {
        EmbVector delta;
        int nextId = (i + 1) % vertices->count;

        delta =
            emb_vector_subtract(vertices->geometry[nextId].object.vector,
                                vertices->geometry[i].object.vector);

        /* If they are closer than the distance, continue */
        if (emb_vector_length(delta) < distance) {
            continue;
        }

        emb_array_addVector(simplified, vertices->geometry[i].object.vector);
    }
}

/* vertices a out a nth
 *
 * Reduces the polygon by removing the Nth vertex in the vertices list.
 * This is a non-destructive function, so the caller is responsible for
 * freeing vertices if they choose to keep out.
 */
void
 embPolygon_reduceByNth(EmbArray * vertices, EmbArray * out, int nth) {
    int i;
    /* We can't simplify polygons under 3 vertices */
    if (vertices->count < 3) {
        emb_array_copy(out, vertices);
        return;
    }

    for (i = 0; i < vertices->count; i++) {
        if (i != nth) {
            emb_array_addVector(out, vertices->geometry[i].object.vector);
        }
    }
}
