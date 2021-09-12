#include "embroidery.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef ARDUINO
#include "utility/ino-event.h"
#endif

static EmbColor black = { 0, 0, 0 };

/*! Returns a pointer to an EmbPattern. It is created on the heap.
 * The caller is responsible for freeing the allocated memory with
 * embPattern_free(). */
EmbPattern* embPattern_create(void)
{
    EmbPattern* p = 0;
    p = (EmbPattern*)malloc(sizeof(EmbPattern));
    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_create(), unable to allocate memory for p\n");
        return 0;
    }

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
    p->lastPosition.x = 0.0;
    p->lastPosition.y = 0.0;

    return p;
}

void embPattern_hideStitchesOverLength(EmbPattern* p, int length)
{
    double prevX, prevY;
    int i;
    EmbStitch st;

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_hideStitchesOverLength(), p argument is null\n");
        return;
    }

    prevX = 0;
    prevY = 0;
    for (i = 0; i < p->stitchList->count; i++) {
        st = p->stitchList->stitch[i];
        if ((fabs(st.x - prevX) > length) || (fabs(st.y - prevY) > length)) {
            st.flags |= TRIM;
            st.flags &= ~NORMAL;
        }
        prevX = st.x;
        prevY = st.y;
    }
}

int embPattern_addThread(EmbPattern* p, EmbThread thread)
{
    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_addThread(), p argument is null\n");
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
    int maxColorIndex = 0, i;

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_fixColorCount(), p argument is null\n");
        return;
    }
    for (i = 0; i < p->stitchList->count; i++) {
        maxColorIndex = embMaxInt(maxColorIndex, p->stitchList->stitch[i].color);
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
    EmbPointObject* point;
    int breakAtFlags;
    EmbStitch st;

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_copyStitchListToPolylines(), p argument is null\n");
        return;
    }

#ifdef EMB_DEBUG_JUMP
    breakAtFlags = (STOP | TRIM);
#else /* EMB_DEBUG_JUMP */
    breakAtFlags = (STOP | JUMP | TRIM);
#endif /* EMB_DEBUG_JUMP */
/*
    for (i = 0; i < p->stitchList->count; i++) {
        EmbArray* pointList = 0;
        EmbColor color;
        while (i < p->stitchList->count) {
            st = p->stitchList->stitch[i];
            if (st.flags & breakAtFlags) {
                break;
            }
            if (!(st.flags & JUMP)) {
                if (!pointList) {
                    pointList = embArray_create(EMB_POINT);
                    color = p->threads->thread[stList->stitch.color].color;
                }
                point = (EmbPointObject*)malloc(sizeof(EmbPointObject));
                point->point.x = st.x;
                point->point.y = st.y;
                embArray_addPoint(pointList, point);
            }
            i++;
        }

        // NOTE: Ensure empty polylines are not created. This is critical.
        if (pointList) {
            EmbPolylineObject* currentPolyline = (EmbPolylineObject*)malloc(sizeof(EmbPolylineObject));
            if (!currentPolyline) {
                embLog("ERROR: emb-pattern.c embPattern_copyStitchListToPolylines(), cannot allocate memory for currentPolyline\n");
                return;
            }
            currentPolyline->pointList = pointList;
            currentPolyline->color = color;
            currentPolyline->lineType = 1;
            // TODO: Determine what the correct value should be 

            if (!p->polylines) {
                p->polylines = embArray_create(EMB_POLYLINE);
            }
            embArray_addPolyline(p->polylines, currentPolyline);
        }
    }
    */
}

/*! Copies all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
void embPattern_copyPolylinesToStitchList(EmbPattern* p)
{
    int firstObject = 1, i, j;
    /*int currentColor = polyList->polylineObj->color TODO: polyline color */

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), p argument is null\n");
        return;
    }
    if (!p->polylines) {
        embLog("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), p argument is null\n");
        return;
    }
    for (i = 0; i < p->polylines->count; i++) {
        EmbPolylineObject* currentPoly = 0;
        EmbArray* currentPointList = 0;
        EmbThread thread;

        currentPoly = p->polylines->polyline[i];
        if (!currentPoly) {
            embLog("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), currentPoly is null\n");
            return;
        }
        currentPointList = currentPoly->pointList;
        if (!currentPointList) {
            embLog("ERROR: emb-pattern.c embPattern_copyPolylinesToStitchList(), currentPointList is null\n");
            return;
        }

        thread.catalogNumber = 0;
        thread.color = currentPoly->color;
        thread.description = 0;
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
void embPattern_moveStitchListToPolylines(EmbPattern* p)
{
    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_moveStitchListToPolylines(), p argument is null\n");
        return;
    }
    embPattern_copyStitchListToPolylines(p);
    /* Free the stitchList and threadList since their data has now been transferred to polylines */
    embArray_free(p->stitchList);
    embArray_free(p->threads);
}

/*! Moves all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
void embPattern_movePolylinesToStitchList(EmbPattern* p)
{
    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_movePolylinesToStitchList(), p argument is null\n");
        return;
    }
    embPattern_copyPolylinesToStitchList(p);
    embArray_free(p->polylines);
}

/*! Adds a stitch to the pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
void embPattern_addStitchAbs(EmbPattern* p, double x, double y, int flags, int isAutoColorIndex)
{
    EmbStitch s, h;
    EmbVector home;

    if (!p || !p->stitchList) {
        embLog("ERROR: emb-pattern.c embPattern_addStitchAbs(), p argument is null\n");
        return;
    }

    if (flags & END) {
        if (p->stitchList->count == 0) {
            return;
        }
        /* Prevent unnecessary multiple END stitches */
        if (p->stitchList->stitch[p->stitchList->count - 1].flags & END) {
            embLog("ERROR: emb-pattern.c embPattern_addStitchAbs(), found multiple END stitches\n");
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

    /* NOTE: If the stitchList is empty, we will create it before adding stitches to it. The first coordinate will be the HOME position. */
    if (!p->stitchList) {
        /* NOTE: Always HOME the machine before starting any stitching */
        home = embSettings_home(&(p->settings));
        h.x = home.x;
        h.y = home.y;
        h.flags = JUMP;
        h.color = p->currentColorIndex;
        p->stitchList = embArray_create(EMB_STITCH);
    }

    s.x = x;
    s.y = y;
    s.flags = flags;
    s.color = p->currentColorIndex;
    /* not sure why this is different on arduino */
#ifdef ARDUINO
    inoEvent_addStitchAbs(p, s.x, s.y, s.flags, s.color);
#else /* ARDUINO */
    embArray_addStitch(p->stitchList, s.x, s.y, s.flags, s.color);
#endif /* ARDUINO */
    p->lastPosition.x = s.x;
    p->lastPosition.y = s.y;
}

/*! Adds a stitch to the pattern (\a p) at the relative position (\a dx,\a dy) to the previous stitch. Positive y is up. Units are in millimeters. */
void embPattern_addStitchRel(EmbPattern* p, double dx, double dy, int flags, int isAutoColorIndex)
{
    EmbVector home;
    double x, y;

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_addStitchRel(), p argument is null\n");
        return;
    }
    if (p->stitchList) {
        x = p->lastPosition.x + dx;
        y = p->lastPosition.y + dy;
    } else {
        /* NOTE: The stitchList is empty, so add it to the HOME position.
         * The embStitchList_create function will ensure the first coordinate is at the HOME position. */
        home = embSettings_home(&(p->settings));
        x = home.x + dx;
        y = home.y + dy;
    }
    embPattern_addStitchAbs(p, x, y, flags, isAutoColorIndex);
}

void embPattern_changeColor(EmbPattern* p, int index)
{
    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_changeColor(), p argument is null\n");
        return;
    }
    p->currentColorIndex = index;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int embPattern_read(EmbPattern* pattern, const char* fileName) /* TODO: Write test case using this convenience function. */
{
    int reader, result;

    if (!validateReadPattern(pattern, fileName, "embPattern_read")) return 0;

    reader = embReaderWriter_getByFileName(fileName);
    if (reader < 0) {
        embLog("emb-pattern.c embPattern_read(), unsupported read file type:");
        embLog(fileName);
        return 0;
    }
    result = formatTable[reader].readerFunc(pattern, fileName);
    return result;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int embPattern_write(EmbPattern* pattern, const char* fileName) /* TODO: Write test case using this convenience function. */
{
    int writer, result;

    if (!validateWritePattern(pattern, fileName, "embPattern_write")) return 0;

    writer = embReaderWriter_getByFileName(fileName);
    if (writer < 0) {
        embLog("ERROR: emb-pattern.c embPattern_write(), unsupported write file type:");
        embLog(fileName);
        return 0;
    }
    result = formatTable[writer].writerFunc(pattern, fileName);
    return result;
}

/* Very simple scaling of the x and y axis for every point.
* Doesn't insert or delete stitches to preserve density. */
void embPattern_scale(EmbPattern* p, double scale)
{
    int i;

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_scale(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitchList->count; i++) {
        p->stitchList->stitch[i].x *= scale;
        p->stitchList->stitch[i].y *= scale;
    }
}

/*! Returns an EmbRect that encapsulates all stitches and objects in the pattern (\a p). */
EmbRect embPattern_calcBoundingBox(EmbPattern* p)
{
    EmbRect boundingRect;
    EmbStitch pt;
    EmbBezier bezier;
    int i, j;

    boundingRect.left = 0;
    boundingRect.right = 0;
    boundingRect.top = 0;
    boundingRect.bottom = 0;

    if (!p || !p->stitchList) {
        embLog("ERROR: emb-pattern.c embPattern_calcBoundingBox(), p argument is null\n");
        return boundingRect;
    }

    /* Calculate the bounding rectangle.  It's needed for smart repainting. */
    /* TODO: Come back and optimize this mess so that after going thru all objects
            and stitches, if the rectangle isn't reasonable, then return a default rect */
    if (!p->stitchList && !(p->arcs || p->circles || p->ellipses || p->lines || p->points || p->polygons || p->polylines || p->rects || p->splines)) {
        boundingRect.top = 0.0;
        boundingRect.left = 0.0;
        boundingRect.bottom = 1.0;
        boundingRect.right = 1.0;
        return boundingRect;
    }
    boundingRect.left = 99999.0;
    boundingRect.top = 99999.0;
    boundingRect.right = -99999.0;
    boundingRect.bottom = -99999.0;

    for (i = 0; i < p->stitchList->count; i++) {
        /* If the point lies outside of the accumulated bounding
        * rectangle, then inflate the bounding rect to include it. */
        pt = p->stitchList->stitch[i];
        if (!(pt.flags & TRIM)) {
            boundingRect.left = embMinDouble(boundingRect.left, pt.x);
            boundingRect.top = embMinDouble(boundingRect.top, pt.y);
            boundingRect.right = embMaxDouble(boundingRect.right, pt.x);
            boundingRect.bottom = embMaxDouble(boundingRect.bottom, pt.y);
        }
    }

    if (p->arcs) {
        /* TODO: embPattern_calcBoundingBox for arcs, for now just checks the start point */
        for (i = 0; i < p->arcs->count; i++) {
            EmbArc arc = p->arcs->arc[i].arc;
            boundingRect.left = embMinDouble(boundingRect.left, arc.start.x);
            boundingRect.top = embMinDouble(boundingRect.top, arc.start.y);
            boundingRect.right = embMaxDouble(boundingRect.right, arc.start.x);
            boundingRect.bottom = embMaxDouble(boundingRect.bottom, arc.start.y);
        }
    }

    if (p->circles) {
        for (i = 0; i < p->circles->count; i++) {
            EmbCircle circle = p->circles->circle[i].circle;
            boundingRect.left = embMinDouble(boundingRect.left, circle.center.x - circle.radius);
            boundingRect.top = embMinDouble(boundingRect.top, circle.center.y - circle.radius);
            boundingRect.right = embMaxDouble(boundingRect.right, circle.center.x + circle.radius);
            boundingRect.bottom = embMaxDouble(boundingRect.bottom, circle.center.y + circle.radius);
        }
    }

    if (p->ellipses) {
        for (i = 0; i < p->ellipses->count; i++) {
            /* TODO: account for rotation */
            EmbEllipse ellipse = p->ellipses->ellipse[i].ellipse;
            boundingRect.left = embMinDouble(boundingRect.left, ellipse.center.x - ellipse.radius.x);
            boundingRect.top = embMinDouble(boundingRect.top, ellipse.center.y - ellipse.radius.y);
            boundingRect.right = embMaxDouble(boundingRect.right, ellipse.center.x + ellipse.radius.x);
            boundingRect.bottom = embMaxDouble(boundingRect.bottom, ellipse.center.y + ellipse.radius.y);
        }
    }

    if (p->lines) {
        for (i = 0; i < p->lines->count; i++) {
            EmbLine line = p->lines->line[i].line;
            boundingRect.left = embMinDouble(boundingRect.left, line.start.x);
            boundingRect.left = embMinDouble(boundingRect.left, line.end.x);
            boundingRect.top = embMinDouble(boundingRect.top, line.start.y);
            boundingRect.top = embMinDouble(boundingRect.top, line.end.y);
            boundingRect.right = embMaxDouble(boundingRect.right, line.start.x);
            boundingRect.right = embMaxDouble(boundingRect.right, line.end.x);
            boundingRect.bottom = embMaxDouble(boundingRect.bottom, line.start.y);
            boundingRect.bottom = embMaxDouble(boundingRect.bottom, line.end.y);
        }
    }

    if (p->points) {
        for (i = 0; i < p->points->count; i++) {
            EmbVector point = p->points->point[i].point;
            boundingRect.left = embMinDouble(boundingRect.left, point.x);
            boundingRect.top = embMinDouble(boundingRect.top, point.y);
            boundingRect.right = embMaxDouble(boundingRect.right, point.x);
            boundingRect.bottom = embMaxDouble(boundingRect.bottom, point.y);
        }
    }

    if (p->polygons) {
        for (i = 0; i < p->polygons->count; i++) {
            EmbArray* polygon;
            polygon = p->polygons->polygon[i]->pointList;
            for (j = 0; j < polygon->count; j++) {
                /* TODO: embPattern_calcBoundingBox for polygons */
            }
        }
    }

    if (p->polylines) {
        for (i = 0; i < p->polylines->count; i++) {
            EmbArray* polyline;
            polyline = p->polylines->polyline[i]->pointList;
            for (j = 0; j < polyline->count; j++) {
                /* TODO: embPattern_calcBoundingBox for polylines */
            }
        }
    }

    if (p->rects) {
        for (i = 0; i < p->rects->count; i++) {
            EmbRect rect = p->rects->rect[i].rect;
            /* TODO: embPattern_calcBoundingBox for rectangles */
        }
    }

    if (p->splines) {
        for (i = 0; i < p->splines->count; i++) {
            bezier = p->splines->spline[i].bezier;
            /* TODO: embPattern_calcBoundingBox for splines */
        }
    }

    return boundingRect;
}

/*! Flips the entire pattern (\a p) horizontally about the y-axis. */
void embPattern_flipHorizontal(EmbPattern* p)
{
    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_flipHorizontal(), p argument is null\n");
        return;
    }
    embPattern_flip(p, 1, 0);
}

/*! Flips the entire pattern (\a p) vertically about the x-axis. */
void embPattern_flipVertical(EmbPattern* p)
{
    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_flipVertical(), p argument is null\n");
        return;
    }
    embPattern_flip(p, 0, 1);
}

/*! Flips the entire pattern (\a p) horizontally about the x-axis if (\a horz) is true.
 *  Flips the entire pattern (\a p) vertically about the y-axis if (\a vert) is true. */
void embPattern_flip(EmbPattern* p, int horz, int vert)
{
    int i, j;

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_flip(), p argument is null\n");
        return;
    }

    if (p->stitchList) {
        for (i = 0; i < p->stitchList->count; i++) {
            if (horz) {
                p->stitchList->stitch[i].x *= -1.0;
            }
            if (vert) {
                p->stitchList->stitch[i].y *= -1.0;
            }
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
            if (horz) {
                p->circles->circle[i].circle.center.x *= -1.0;
            }
            if (vert) {
                p->circles->circle[i].circle.center.y *= -1.0;
            }
        }
    }

    if (p->ellipses) {
        for (i = 0; i < p->ellipses->count; i++) {
            if (horz) {
                p->ellipses->ellipse[i].ellipse.center.x *= -1.0;
            }
            if (vert) {
                p->ellipses->ellipse[i].ellipse.center.y *= -1.0;
            }
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
            EmbArray* path = p->paths->path[i]->pointList;
            for (j = 0; j < path->count; j++) {
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
            EmbArray* polygon;
            polygon = p->polygons->polygon[i]->pointList;
            for (j = 0; j < polygon->count; j++) {
                if (horz) {
                    polygon->point[j].point.x *= -1.0;
                }
                if (vert) {
                    polygon->point[j].point.y *= -1.0;
                }
            }
        }
    }

    if (p->polylines) {
        for (i = 0; i < p->polylines->count; i++) {
            EmbArray* polyline;
            polyline = p->polylines->polygon[i]->pointList;
            for (j = 0; j < polyline->count; j++) {
                if (horz) {
                    polyline->point[j].point.x *= -1.0;
                }
                if (vert) {
                    polyline->point[j].point.y *= -1.0;
                }
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

void embPattern_combineJumpStitches(EmbPattern* p)
{
    int jump = 0, i, j;
    EmbStitch st;

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_combineJumpStitches(), p argument is null\n");
        return;
    }

    j = 0;
    for (i = 0; i < p->stitchList->count; i++) {
        st = p->stitchList->stitch[i];
        p->stitchList->stitch[j] = st;
        if (st.flags & JUMP) {
            if (jump == 0) {
                j++;
                jump = 1;
            }
        } else {
            j++;
            jump = 0;
        }
    }
    p->stitchList->count = j + 1;
}

/*TODO: The params determine the max XY movement rather than the length. They need renamed or clarified further. */
void embPattern_correctForMaxStitchLength(EmbPattern* p, double maxStitchLength, double maxJumpLength)
{
    int j = 0, splits, i;
    double maxXY, maxLen, addX, addY;

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_correctForMaxStitchLength(), p argument is null\n");
        return;
    }
    /*
    if (p->stitchList->count > 1) {
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
                        if(!item) { embLog("ERROR: emb-pattern.c embPattern_correctForMaxStitchLength(), cannot allocate memory for item\n"); return; }
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
    */
    embPattern_end(p);
}

void embPattern_center(EmbPattern* p)
{
    /* TODO: review this. currently not used in anywhere. Also needs to handle various design objects */
    int moveLeft, moveTop, i;
    EmbRect boundingRect;
    EmbStitch s;

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_center(), p argument is null\n");
        return;
    }
    boundingRect = embPattern_calcBoundingBox(p);

    moveLeft = (int)(boundingRect.left - (embRect_width(boundingRect) / 2.0));
    moveTop = (int)(boundingRect.top - (embRect_height(boundingRect) / 2.0));

    for (i = 0; i < p->stitchList->count; i++) {
        s = p->stitchList->stitch[i];
        s.x -= moveLeft;
        s.y -= moveTop;
    }
}

/*TODO: Description needed. */
void embPattern_loadExternalColorFile(EmbPattern* p, const char* fileName)
{
#ifdef ARDUINO
    return; /* TODO ARDUINO: This function leaks memory. While it isn't crucial to running the machine, it would be nice use this function, so fix it up. */
#endif /* ARDUINO */

    char hasRead = 0;
    int colorFile = 0;
    const char* dotPos = strrchr(fileName, '.');
    char* extractName = 0;

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_loadExternalColorFile(), p argument is null\n");
        return;
    }
    if (!fileName) {
        embLog("ERROR: emb-pattern.c embPattern_loadExternalColorFile(), fileName argument is null\n");
        return;
    }

    extractName = (char*)malloc(dotPos - fileName + 5);
    if (!extractName) {
        embLog("ERROR: emb-pattern.c embPattern_loadExternalColorFile(), cannot allocate memory for extractName\n");
        return;
    }
    extractName = (char*)memcpy(extractName, fileName, dotPos - fileName);
    extractName[dotPos - fileName] = '\0';
    strcat(extractName, ".edr");
    hasRead = (char)formatTable[EMB_FORMAT_EDR].readerFunc(p, extractName);
    if (!hasRead) {
        extractName = (char*)memcpy(extractName, fileName, dotPos - fileName);
        extractName[dotPos - fileName] = '\0';
        strcat(extractName, ".rgb");
        hasRead = (char)formatTable[EMB_FORMAT_RGB].readerFunc(p, extractName);
    }
    if (!hasRead) {
        extractName = (char*)memcpy(extractName, fileName, dotPos - fileName);
        extractName[dotPos - fileName] = '\0';
        strcat(extractName, ".col");
        hasRead = (char)formatTable[EMB_FORMAT_COL].readerFunc(p, extractName);
    }
    if (!hasRead) {
        extractName = (char*)memcpy(extractName, fileName, dotPos - fileName);
        extractName[dotPos - fileName] = '\0';
        strcat(extractName, ".inf");
        hasRead = (char)formatTable[EMB_FORMAT_INF].readerFunc(p, extractName);
    }
    free(extractName);
}

/*! Frees all memory allocated in the pattern (\a p). */
void embPattern_free(EmbPattern* p)
{
    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_free(), p argument is null\n");
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
void embPattern_addCircleObjectAbs(EmbPattern* p, double cx, double cy, double r)
{
    EmbCircle circle = { {cx, cy}, r };

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_addCircleObjectAbs(), p argument is null\n");
        return;
    }
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
    ellipse.center.x = cx;
    ellipse.center.y = cy;
    ellipse.radius.x = rx;
    ellipse.radius.y = ry;

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_addEllipseObjectAbs(), p argument is null\n");
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
    lineObj.line.start.x = x1;
    lineObj.line.start.y = y1;
    lineObj.line.end.x = x2;
    lineObj.line.end.y = y2;
    lineObj.color.r = 0;
    lineObj.color.g = 0;
    lineObj.color.b = 0;

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_addLineObjectAbs(), p argument is null\n");
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
        embLog("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj) {
        embLog("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), obj argument is null\n");
        return;
    }
    if (!obj->pointList) {
        embLog("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), obj->pointList is empty\n");
        return;
    }

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
        embLog("ERROR: emb-pattern.c embPattern_addPointObjectAbs(), p argument is null\n");
        return;
    }
    if (!p->points) {
        p->points = embArray_create(EMB_POINT);
    }
    embArray_addPoint(p->points, &pointObj);
}

void embPattern_addPolygonObjectAbs(EmbPattern* p, EmbPolygonObject* obj)
{
    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj) {
        embLog("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), obj argument is null\n");
        return;
    }
    if (!obj->pointList) {
        embLog("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), obj->pointList is empty\n");
        return;
    }

    if (!p->polygons) {
        p->polygons = embArray_create(EMB_POLYGON);
    }
    embArray_addPolygon(p->polygons, obj);
}

void embPattern_addPolylineObjectAbs(EmbPattern* p, EmbPolylineObject* obj)
{
    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_addPolylineObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj) {
        embLog("ERROR: emb-pattern.c embPattern_addPolylineObjectAbs(), obj argument is null\n");
        return;
    }
    if (!obj->pointList) {
        embLog("ERROR: emb-pattern.c embPattern_addPolylineObjectAbs(), obj->pointList is empty\n");
        return;
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
    rect.right = x + w;
    rect.bottom = y + h;

    if (!p) {
        embLog("ERROR: emb-pattern.c embPattern_addRectObjectAbs(), p argument is null\n");
        return;
    }
    if (!p->rects) {
        p->rects = embArray_create(EMB_RECT);
    }
    embArray_addRect(p->rects, rect, 0, black);
}

void embPattern_end(EmbPattern* p)
{
    /* Check for an END stitch and add one if it is not present */
    if (p->stitchList->stitch[p->stitchList->count - 1].flags != END) {
        embPattern_addStitchRel(p, 0, 0, END, 1);
    }
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
EmbVector embSettings_home(EmbSettings* settings)
{
    return settings->home;
}

/*! Sets the home position stored in (\a settings) to EmbPoint (\a point). You will rarely ever need to use this. */
void embSettings_setHome(EmbSettings* settings, EmbVector point)
{
    settings->home = point;
}

