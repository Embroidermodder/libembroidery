/* 
 * This file is part of libembroidery.
 *
 * Copyright 2018-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * This file contains all the read and write functions for the
 * library.
 *
 * Management of the main struct: EmbPattern.
 *******************************************************************/

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "embroidery.h"
#include "embroidery-internal.h"

/*! Returns a pointer to an EmbPattern. It is created on the heap.
 * The caller is responsible for freeing the allocated memory with
 * embPattern_free(). */
EmbPattern* embPattern_create(void) {
    EmbPattern* p = 0;
    p = (EmbPattern*)malloc(sizeof(EmbPattern));
    if (!p) { 
        printf("ERROR: emb-pattern.c embPattern_create(), ");
        printf("unable to allocate memory for p\n");
        return 0;
    }
    p->settings = embSettings_init();
    p->currentColorIndex = 0;
    p->stitchList = embArray_create(EMB_STITCH);
    p->threads = embArray_create(EMB_THREAD);
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
    return p;
}

void embPattern_hideStitchesOverLength(EmbPattern* p, int length) {
    double prevX = 0;
    double prevY = 0;
    int i;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_hideStitchesOverLength(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->stitchList->count; i++) {
        if ((fabs(p->stitchList->stitch[i].x - prevX) > length)
         || (fabs(p->stitchList->stitch[i].y - prevY) > length)) {
            p->stitchList->stitch[i].flags |= TRIM;
            p->stitchList->stitch[i].flags &= ~NORMAL;
        }
        prevX = p->stitchList->stitch[i].x;
        prevY = p->stitchList->stitch[i].y;
    }
}

int embPattern_addThread(EmbPattern* p, EmbThread thread) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addThread(), ");
        printf("p argument is null\n");
        return 0;
    }
    if (!p->threads) {
        p->threads = embArray_create(EMB_THREAD);
    }
    embArray_addThread(p->threads, thread);
    return 1;
}

void embPattern_fixColorCount(EmbPattern* p) {
    /* fix color count to be max of color index. */
    int maxColorIndex = 0, i;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_fixColorCount(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->stitchList->count; i++) {
/*        printf("%d %d\n", list->stitch.color, maxColorIndex);*/
        maxColorIndex = EMB_MAX(maxColorIndex, p->stitchList->stitch[i].color);
    }
    if (p->threads->count == 0 || maxColorIndex == 0) {
        embPattern_addThread(p, black_thread);
    }
    else {
        if (maxColorIndex > 0) {
            while (p->threads->count <= maxColorIndex) {
/*        printf("%d %d\n", p->threads->count, maxColorIndex);*/
                embPattern_addThread(p, embThread_getRandom());
            }
        }
    }
    /*
    while (p->threadLists->count > (maxColorIndex + 1)) {
        TODO: erase last color    p->threadList.pop_back();
    }
    */
}

/*! Copies all of the EmbStitchList data to 
    EmbPolylineObjectList data for pattern (\a p). */
void embPattern_copyStitchListToPolylines(EmbPattern* p) {
    int breakAtFlags, i;
    EmbPointObject point;
    EmbColor color;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_copyStitchListToPolylines(), ");
        printf("p argument is null\n");
        return;
    }

#ifdef EMB_DEBUG_JUMP
    breakAtFlags = (STOP | TRIM);
#else /* EMB_DEBUG_JUMP */
    breakAtFlags = (STOP | JUMP | TRIM);
#endif /* EMB_DEBUG_JUMP */

    for (i = 0; i < p->stitchList->count; i++) {
        EmbArray *pointList = 0;
        for (; i < p->stitchList->count; i++) {
            EmbStitch st = p->stitchList->stitch[i];
            if (st.flags & breakAtFlags) {
                break;
            }
            if (!(st.flags & JUMP)) {
                if (!pointList) {
                    pointList = embArray_create(EMB_POINT);
                    color = p->threads->thread[st.color].color;
                }
                point.point.x = st.x;
                point.point.y = st.y;
                embArray_addPoint(pointList, &point);
            }
        }

        /* NOTE: Ensure empty polylines are not created. This is critical. */
        if (pointList) {
            EmbPolylineObject* currentPolyline = 
                (EmbPolylineObject*)malloc(sizeof(EmbPolylineObject));
            if (!currentPolyline) {
                printf("ERROR: emb-pattern.c embPattern_copyStitchListToPolylines(), cannot allocate memory for currentPolyline\n");
                return;
            }
            currentPolyline->pointList = pointList;
            currentPolyline->color = color;
            /* TODO: Determine what the correct value should be */
            currentPolyline->lineType = 1;

            if (!p->polylines) {
                p->polylines = embArray_create(EMB_POLYLINE);
            }
            embArray_addPolyline(p->polylines, currentPolyline);
        }
    }
}

/*! Copies all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
void embPattern_copyPolylinesToStitchList(EmbPattern* p) {
    int firstObject = 1, i, j;
    /*int currentColor = polyList->polylineObj->color TODO: polyline color */

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), ");
        printf("p argument is null\n");
        return;
    }
    if (!p->polylines) {
        printf("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), p argument is null\n");
        return;
    }
    for (i = 0; i < p->polylines->count; i++) {
        EmbPolylineObject* currentPoly = 0;
        EmbArray* currentPointList = 0;
        EmbThread thread;

        currentPoly = p->polylines->polyline[i];
        if (!currentPoly) { 
            printf("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), currentPoly is null\n");
            return;
        }
        currentPointList = currentPoly->pointList;
        if (!currentPointList) {
            printf("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), currentPointList is null\n");
            return;
        }

        strcpy(thread.catalogNumber, "");
        thread.color = currentPoly->color;
        strcpy(thread.description, "");
        embPattern_addThread(p, thread);

        if (!firstObject) {
            embPattern_addStitchAbs(p, currentPointList->point[0].point.x, currentPointList->point[0].point.y, TRIM, 1);
            embPattern_addStitchRel(p, 0.0, 0.0, STOP, 1);
        }

        embPattern_addStitchAbs(p, currentPointList->point[0].point.x, currentPointList->point[0].point.y, JUMP, 1);
        for (j = 1; j < currentPointList->count; j++) { 
            embPattern_addStitchAbs(p, currentPointList->point[j].point.x, currentPointList->point[j].point.y, NORMAL, 1);
        }
        firstObject = 0;
    }
    embPattern_addStitchRel(p, 0.0, 0.0, END, 1);
}

/*! Moves all of the EmbStitchList data to EmbPolylineObjectList data for pattern (\a p). */
void embPattern_moveStitchListToPolylines(EmbPattern* p) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_moveStitchListToPolylines(), p argument is null\n");
        return;
    }
    embPattern_copyStitchListToPolylines(p);
    /* Free the stitchList and threadList since their data has now been transferred to polylines */
    p->stitchList->count = 0;
    p->threads->count = 0;
}

/*! Moves all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
void embPattern_movePolylinesToStitchList(EmbPattern* p) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_movePolylinesToStitchList(), p argument is null\n");
        return;
    }
    embPattern_copyPolylinesToStitchList(p);
    embArray_free(p->polylines);
}

/*! Adds a stitch to the pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
void embPattern_addStitchAbs(EmbPattern* p, double x, double y, 
                            int flags, int isAutoColorIndex) {
    EmbStitch s;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addStitchAbs(), ");
        printf("p argument is null\n");
        return;
    }

    if (flags & END) {
        if (p->stitchList->count == 0) {
            return;
        }
        /* Prevent unnecessary multiple END stitches */
        if (p->stitchList->stitch[p->stitchList->count - 1].flags & END) {
            printf("ERROR: emb-pattern.c embPattern_addStitchAbs(), found multiple END stitches\n");
            return;
        }
        embPattern_fixColorCount(p);
        /* HideStitchesOverLength(127); TODO: fix or remove this */
    }

    if (flags & STOP) {
        if (p->stitchList->count == 0) {
            return;
        }
        if (isAutoColorIndex) {
            p->currentColorIndex++;
        }
    }

    /* NOTE: If the stitchList is empty, we will create it before adding 
        stitches to it. The first coordinate will be the HOME position. */
    if (p->stitchList->count == 0) {
        /* NOTE: Always HOME the machine before starting any stitching */
        EmbVector home = embSettings_home(&(p->settings));
        EmbStitch h;
        h.x = home.x;
        h.y = home.y;
        h.flags = JUMP;
        h.color = p->currentColorIndex;
        embArray_addStitch(p->stitchList, h);
    }
    s.x = x;
    s.y = y;
    s.flags = flags;
    s.color = p->currentColorIndex;
    embArray_addStitch(p->stitchList, s);
}

/*! Adds a stitch to the pattern (\a p) at the relative position (\a dx,\a dy) 
    to the previous stitch. Positive y is up. Units are in millimeters. */
void embPattern_addStitchRel(EmbPattern* p, double dx, double dy, 
                            int flags, int isAutoColorIndex) {
    double x, y;
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addStitchRel(), p argument is null\n");
        return;
    }
    if (p->stitchList->count > 0) {
        EmbStitch st = p->stitchList->stitch[p->stitchList->count - 1];
        x = st.x + dx;
        y = st.y + dy;
    } else {
        /* NOTE: The stitchList is empty, so add it to the HOME position.
         * The embStitchList_create function will ensure the first coordinate is at the HOME position. */
        EmbVector home = embSettings_home(&(p->settings));
        x = home.x + dx;
        y = home.y + dy;
    }
    embPattern_addStitchAbs(p, x, y, flags, isAutoColorIndex);
}

void embPattern_changeColor(EmbPattern* p, int index)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_changeColor(), p argument is null\n");
        return;
    }
    p->currentColorIndex = index;
}

/* Very simple scaling of the x and y axis for every point.
* Doesn't insert or delete stitches to preserve density. */
void embPattern_scale(EmbPattern* p, double scale) {
    int i;
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_scale(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitchList->count; i++) {
        p->stitchList->stitch[i].x *= scale;
        p->stitchList->stitch[i].y *= scale;
    }
}

/*! Returns an EmbRect that encapsulates all stitches and objects in the pattern (\a p). */
EmbRect embPattern_calcBoundingBox(EmbPattern* p) {
    EmbRect r;
    EmbStitch pt;
    EmbArc arc;
    EmbCircle circle;
    EmbEllipse ellipse;
    EmbLine line;
    EmbVector point;
    EmbArray *polygon;
    EmbArray *polyline;
    int i, j;

    r.left = 0;
    r.right = 0;
    r.top = 0;
    r.bottom = 0;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_calcBoundingBox(), ");
        printf("p argument is null\n");
        return r;
    }

    /* Calculate the bounding rectangle.  It's needed for smart repainting. */
    /* TODO: Come back and optimize this mess so that after going thru all objects
            and stitches, if the rectangle isn't reasonable, then return a default rect */
    if (p->stitchList->count == 0 &&
        !(p->arcs || p->circles || p->ellipses || p->lines || p->points ||
        p->polygons || p->polylines || p->rects || p->splines)) {
        r.top = 0.0;
        r.left = 0.0;
        r.bottom = 1.0;
        r.right = 1.0;
        return r;
    }
    r.left = 99999.0;
    r.top =  99999.0;
    r.right = -99999.0;
    r.bottom = -99999.0;

    for (i = 0; i < p->stitchList->count; i++) {
        /* If the point lies outside of the accumulated bounding
        * rectangle, then inflate the bounding rect to include it. */
        pt = p->stitchList->stitch[i];
        if (!(pt.flags & TRIM)) {
            r.left = EMB_MIN(r.left, pt.x);
            r.top = EMB_MIN(r.top, pt.y);
            r.right = EMB_MAX(r.right, pt.x);
            r.bottom = EMB_MAX(r.bottom, pt.y);
        }
    }

    if (p->arcs) {
        /* TODO: embPattern_calcBoundingBox for arcs, 
            for now just checks the start point */
        for (i = 0; i < p->arcs->count; i++) {
            arc = p->arcs->arc[i].arc;
            r.left = EMB_MIN(r.left, arc.start.x);
            r.top = EMB_MIN(r.top, arc.start.y);
            r.right = EMB_MAX(r.right, arc.start.x);
            r.bottom = EMB_MAX(r.bottom, arc.start.y);
        }
    }

    if (p->circles) {
        for (i = 0; i < p->circles->count; i++) {
            circle = p->circles->circle[i].circle;
            r.left = EMB_MIN(r.left, circle.center.x - circle.radius);
            r.top = EMB_MIN(r.top, circle.center.y - circle.radius);
            r.right = EMB_MAX(r.right, circle.center.x + circle.radius);
            r.bottom = EMB_MAX(r.bottom, circle.center.y + circle.radius);
        }
    }

    if (p->ellipses) {
        for (i = 0; i < p->ellipses->count; i++) {
            /* TODO: account for rotation */
            ellipse = p->ellipses->ellipse[i].ellipse;
            r.left = EMB_MIN(r.left, ellipse.centerX - ellipse.radiusX);
            r.top = EMB_MIN(r.top, ellipse.centerY - ellipse.radiusY);
            r.right = EMB_MAX(r.right, ellipse.centerX + ellipse.radiusX);
            r.bottom = EMB_MAX(r.bottom, ellipse.centerY + ellipse.radiusY);
        }
    }

    if (p->lines) {
        for (i = 0; i < p->lines->count; i++) {
            line = p->lines->line[i].line;
            r.left = EMB_MIN(r.left, line.start.x);
            r.left = EMB_MIN(r.left, line.end.x);
            r.top = EMB_MIN(r.top, line.start.y);
            r.top = EMB_MIN(r.top, line.end.y);
            r.right = EMB_MAX(r.right, line.start.x);
            r.right = EMB_MAX(r.right, line.end.x);
            r.bottom = EMB_MAX(r.bottom, line.start.y);
            r.bottom = EMB_MAX(r.bottom, line.end.y);
        }
    }

    if (p->points) {
        for (i = 0; i < p->points->count; i++) {
            point = p->points->point[i].point;
            r.left = EMB_MIN(r.left, point.x);
            r.top = EMB_MIN(r.top, point.y);
            r.right = EMB_MAX(r.right, point.x);
            r.bottom = EMB_MAX(r.bottom, point.y);
        }
    }

    if (p->polygons) {
        for (i = 0; i < p->polygons->count; i++) {
            polygon = p->polygons->polygon[i]->pointList;
            for (j=0; j < polygon->count; j++) {
                /* TODO: embPattern_calcBoundingBox for polygons */
            }
        }
    }

    if (p->polylines) {
        for (i = 0; i < p->polylines->count; i++) {
            polyline = p->polylines->polyline[i]->pointList;
            for (j=0; j < polyline->count; j++) {
                /* TODO: embPattern_calcBoundingBox for polylines */
            }
        }
    }

    if (p->rects) {
        EmbRect rect;
        for (i = 0; i < p->rects->count; i++) {
            rect = p->rects->rect[i].rect;
            r.left = EMB_MIN(r.left, rect.left);
            r.top = EMB_MIN(r.top, rect.top);
            r.right = EMB_MAX(r.right, rect.right);
            r.bottom = EMB_MAX(r.bottom, rect.bottom);
        }
    }

    if (p->splines) {
        for (i = 0; i < p->splines->count; i++) {
            /* EmbBezier bezier;
            bezier = p->splines->spline[i].bezier; */
            /* TODO: embPattern_calcBoundingBox for splines */
        }
    }
    return r;
}

/*! Flips the entire pattern (\a p) horizontally about the y-axis. */
void embPattern_flipHorizontal(EmbPattern* p) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_flipHorizontal(), ");
        printf("p argument is null\n");
        return;
    }
    embPattern_flip(p, 1, 0);
}

/*! Flips the entire pattern (\a p) vertically about the x-axis. */
void embPattern_flipVertical(EmbPattern* p) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_flipVertical(), ");
        printf("p argument is null\n");
        return;
    }
    embPattern_flip(p, 0, 1);
}

/*! Flips the entire pattern (\a p) horizontally about the x-axis if (\a horz) is true.
 *  Flips the entire pattern (\a p) vertically about the y-axis if (\a vert) is true. */
void embPattern_flip(EmbPattern* p, int horz, int vert) {
    int i, j;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_flip(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitchList->count; i++) {
        if (horz) {
            p->stitchList->stitch[i].x *= -1.0;
        }
        if (vert) {
            p->stitchList->stitch[i].y *= -1.0;
        }
    }

    if (p->arcs) {
        for (i = 0; i < p->arcs->count; i++) {
            if (horz) {
                p->arcs->arc[i].arc.start.x *= -1.0;
                p->arcs->arc[i].arc.mid.x *= -1.0;
                p->arcs->arc[i].arc.end.x *= -1.0;
            }
            if (vert) {
                p->arcs->arc[i].arc.start.y *= -1.0;
                p->arcs->arc[i].arc.mid.y *= -1.0;
                p->arcs->arc[i].arc.end.y *= -1.0;
            }
        }
    }

    if (p->circles) {
        for (i = 0; i < p->circles->count; i++) {
            if (horz) { p->circles->circle[i].circle.center.x *= -1.0; }
            if (vert) { p->circles->circle[i].circle.center.y *= -1.0; }
        }
    }

    if (p->ellipses) {
        for (i = 0; i < p->ellipses->count; i++) {
            if (horz) { p->ellipses->ellipse[i].ellipse.centerX *= -1.0; }
            if (vert) { p->ellipses->ellipse[i].ellipse.centerY *= -1.0; }
        }
    }

    if (p->lines) {
        for (i = 0; i < p->lines->count; i++) {
            if (horz) {
                p->lines->line[i].line.start.x *= -1.0;
                p->lines->line[i].line.end.x *= -1.0;
            }
            if (vert) {
                p->lines->line[i].line.start.y *= -1.0;
                p->lines->line[i].line.end.y *= -1.0;
            }
        }
    }

    if (p->paths) {
        for (i = 0; i < p->paths->count; i++) {
            EmbArray *path = p->paths->path[i]->pointList;
            for (j=0; j < path->count; j++) {
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
        for (i = 0; i < p->points->count; i++) {
            if (horz) {
                p->points->point[i].point.x *= -1.0;
            }
            if (vert) {
                p->points->point[i].point.y *= -1.0;
            }
        }
    }

    if (p->polygons) {
        for (i = 0; i < p->polygons->count; i++) {
            EmbArray *polygon;
            polygon = p->polygons->polygon[i]->pointList;
            for (j=0; j < polygon->count; j++) {
                if (horz) { polygon->point[j].point.x *= -1.0; }
                if (vert) { polygon->point[j].point.y *= -1.0; }
            }
        }
    }

    if (p->polylines) {
        for (i = 0; i < p->polylines->count; i++) {
            EmbArray *polyline;
            polyline = p->polylines->polygon[i]->pointList;
            for (j=0; j < polyline->count; j++) {
                if (horz) { polyline->point[j].point.x *= -1.0; }
                if (vert) { polyline->point[j].point.y *= -1.0; }
            }
        }
    }

    if (p->rects) {
        for (i = 0; i < p->rects->count; i++) {
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
        for (i = 0; i < p->splines->count; i++) {
            /* TODO: embPattern_flip for splines */
        }
    }
}

void embPattern_combineJumpStitches(EmbPattern* p) {
    int jumpCount = 0, i;
    EmbArray *newList;
    EmbStitch j;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_combineJumpStitches(), ");
        printf("p argument is null\n");
        return;
    }
    newList = embArray_create(EMB_STITCH);
    for (i = 0; i < p->stitchList->count; i++) {
        EmbStitch st = p->stitchList->stitch[i];
        if (st.flags & JUMP) {
            if (jumpCount == 0) {
                j = st;
            } else {
                j.x += st.x;
                j.y += st.y;
            }
            jumpCount++;
        } else {
            if (jumpCount > 0) {
                embArray_addStitch(newList, j);
            }
            embArray_addStitch(newList, st);
        }
    }
    embArray_free(p->stitchList);
    p->stitchList = newList;
}

/*TODO: The params determine the max XY movement rather than the length. 
    They need renamed or clarified further. */
void embPattern_correctForMaxStitchLength(EmbPattern* p, 
                        double maxStitchLength, double maxJumpLength) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_correctForMaxStitchLength(), ");
        printf("p argument is null\n");
        return;
    }
    if (p->stitchList->count > 1) {
        int i, j, splits;
        double maxXY, maxLen, addX, addY;
        EmbArray *newList = embArray_create(EMB_STITCH);
        for (i=1; i < p->stitchList->count; i++) {
            EmbStitch st = p->stitchList->stitch[i];
            double xx = st.x;
            double yy = st.y;
            double dx = p->stitchList->stitch[i-1].x - xx;
            double dy = p->stitchList->stitch[i-1].y - yy;
            if ((fabs(dx) > maxStitchLength) || (fabs(dy) > maxStitchLength)) {
                maxXY = EMB_MAX(fabs(dx), fabs(dy));
                if (st.flags & (JUMP | TRIM)) {
                    maxLen = maxJumpLength;
                } else {
                    maxLen = maxStitchLength;
                }
                splits = (int)ceil((double)maxXY / maxLen);

                if (splits > 1) {
                    addX = (double)dx / splits;
                    addY = (double)dy / splits;

                    for (j = 1; j < splits; j++) {
                        EmbStitch s;
                        s = st;
                        s.x = xx + addX * j;
                        s.y = yy + addY * j;
                        embArray_addStitch(newList, s);
                    }
                }
            }
            embArray_addStitch(newList, st);
        }
        embArray_free(p->stitchList);
        p->stitchList = newList;
    }
    embPattern_end(p);
}

void embPattern_center(EmbPattern* p) {
    /* TODO: review this. currently not used in anywhere. 
        Also needs to handle various design objects */
    int moveLeft, moveTop, i;
    EmbRect boundingRect;
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_center(), p argument is null\n");
        return;
    }
    boundingRect = embPattern_calcBoundingBox(p);

    moveLeft = (int)(boundingRect.left - (embRect_width(boundingRect) / 2.0));
    moveTop = (int)(boundingRect.top - (embRect_height(boundingRect) / 2.0));

    for (i = 0; i < p->stitchList->count; i++) {
        p->stitchList->stitch[i].x -= moveLeft;
        p->stitchList->stitch[i].y -= moveTop;
    }
}

/*TODO: Description needed. */
void embPattern_loadExternalColorFile(EmbPattern* p, const char* fileName) {
    int hasRead, stub_len, format;
    char extractName[200];

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_loadExternalColorFile(), p argument is null\n");
        return;
    }
    if (!fileName) {
        printf("ERROR: emb-pattern.c embPattern_loadExternalColorFile(), fileName argument is null\n");
        return;
    }

    strcpy(extractName, fileName);
    format = emb_identify_format(fileName);
    stub_len = strlen(fileName) - strlen(formatTable[format].extension);
    extractName[stub_len] = 0;
    strcat(extractName, ".edr");
    hasRead = embPattern_read(p, extractName, EMB_FORMAT_EDR);
    if (!hasRead) {
        extractName[stub_len] = 0;
        strcat(extractName,".rgb");
        hasRead = embPattern_read(p, extractName, EMB_FORMAT_RGB);
    }
    if (!hasRead) {
        extractName[stub_len] = 0;
        strcat(extractName,".col");
        hasRead = embPattern_read(p, extractName, EMB_FORMAT_COL);
    }
    if (!hasRead) {
        extractName[stub_len] = 0;
        strcat(extractName,".inf");
        hasRead = embPattern_read(p, extractName, EMB_FORMAT_INF);
    }
}

/*! Frees all memory allocated in the pattern (\a p). */
void embPattern_free(EmbPattern* p) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_free(), p argument is null\n");
        return;
    }
    embArray_free(p->stitchList);
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
}

/*! Adds a circle object to pattern (\a p) with its center at the absolute
 * position (\a cx,\a cy) with a radius of (\a r). Positive y is up.
 * Units are in millimeters. */
void embPattern_addCircleObjectAbs(EmbPattern* p, double cx, double cy, double r) {
    EmbCircle circle;
    circle.center.x = cx;
    circle.center.y = cy;
    circle.radius = r;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addCircleObjectAbs(), p argument is null\n");
        return;
    }
    if (p->circles == 0) {
         p->circles = embArray_create(EMB_CIRCLE);
    }
    embArray_addCircle(p->circles, circle, 0, black_thread.color);
}

/*! Adds an ellipse object to pattern (\a p) with its center at the
 * absolute position (\a cx,\a cy) with radii of (\a rx,\a ry). Positive y is up.
 * Units are in millimeters. */
void embPattern_addEllipseObjectAbs(EmbPattern* p, double cx, double cy,
                                    double rx, double ry) {
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
    embArray_addEllipse(p->ellipses, ellipse, 0.0, 0, black_thread.color);
}

/*! Adds a line object to pattern (\a p) starting at the absolute position
 * (\a x1,\a y1) and ending at the absolute position (\a x2,\a y2).
 * Positive y is up. Units are in millimeters.
 */
void embPattern_addLineObjectAbs(EmbPattern* p, double x1, double y1, double x2, double y2) {
    EmbLineObject lineObj;
    lineObj.line = embLine_make(x1, y1, x2, y2);
    lineObj.lineType = 0;
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
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj) {
        printf("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), obj argument is null\n");
        return;
    }
    if (!obj->pointList) {
        printf("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), obj->pointList is empty\n");
        return;
    }
    if (!p->paths) {
        p->paths = embArray_create(EMB_PATH);
    }
    embArray_addPath(p->paths, obj);
}

/*! Adds a point object to pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
void embPattern_addPointObjectAbs(EmbPattern* p, double x, double y) {
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

void embPattern_addPolygonObjectAbs(EmbPattern* p, EmbPolygonObject* obj) {
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj) {
        printf("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), obj argument is null\n");
        return;
    }
    if (!obj->pointList) {
        printf("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), obj->pointList is empty\n");
        return;
    }

    if (!p->polygons) {
        p->polygons = embArray_create(EMB_POLYGON);
    }
    embArray_addPolygon(p->polygons, obj);
}

void embPattern_addPolylineObjectAbs(EmbPattern* p, EmbPolylineObject* obj) {
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
void embPattern_addRectObjectAbs(EmbPattern* p, double x, double y, double w, double h) {
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
    embArray_addRect(p->rects, rect, 0, black_thread.color);
}

void embPattern_end(EmbPattern *p) {
    if (p->stitchList->count == 0) {
        return;
    }
    /* Check for an END stitch and add one if it is not present */
    if (p->stitchList->stitch[p->stitchList->count-1].flags != END) {
        embPattern_addStitchRel(p, 0, 0, END, 1);
    }
}
