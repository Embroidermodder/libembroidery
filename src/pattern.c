/* 
 * This file is part of libembroidery.
 *
 * Copyright 2018-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * The file is for the management of the main struct: EmbPattern.
 *******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "embroidery_internal.h"

/*! Returns a pointer to an EmbPattern. It is created on the heap.
 * The caller is responsible for freeing the allocated memory with
 * embPattern_free(). */
EmbPattern*
embPattern_create(void)
{
    EmbPattern* p = (EmbPattern*)malloc(sizeof(EmbPattern));
    if (!p) { 
        printf("ERROR: emb-pattern.c embPattern_create(), ");
        printf("unable to allocate memory for p\n");
        return 0;
    }
    p->dstJumpsPerTrim = 6;
    p->home.x = 0.0;
    p->home.y = 0.0;
    p->currentColorIndex = 0;
    p->stitch_list = embArray_create(EMB_STITCH);
    p->thread_list = embArray_create(EMB_LINE);
    p->hoop_height = 0.0;
    p->hoop_width = 0.0;
    p->geometry = embArray_create(EMB_LINE);
    return p;
}

void
embPattern_hideStitchesOverLength(EmbPattern* p, int length)
{
    EmbVector prev;
    int i;
    prev.x = 0.0;
    prev.y = 0.0;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_hideStitchesOverLength(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->stitch_list->count; i++) {
        if ((fabs(p->stitch_list->stitch[i].x - prev.x) > length)
         || (fabs(p->stitch_list->stitch[i].y - prev.y) > length)) {
            p->stitch_list->stitch[i].flags |= TRIM;
            p->stitch_list->stitch[i].flags &= ~NORMAL;
        }
        prev.x = p->stitch_list->stitch[i].x;
        prev.y = p->stitch_list->stitch[i].y;
    }
}

int
embPattern_addThread(EmbPattern *pattern, EmbThread thread)
{
    if (pattern->thread_list->count + 1 > pattern->thread_list->length) {
        if (!embArray_resize(pattern->thread_list)) {
            return 0;
        }
    }
    pattern->thread_list->thread[pattern->thread_list->count] = thread;
    pattern->thread_list->count++;
    return 1;
}

void
embPattern_fixColorCount(EmbPattern* p)
{
    /* fix color count to be max of color index. */
    int maxColorIndex = 0, i;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_fixColorCount(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->stitch_list->count; i++) {
/*        printf("%d %d\n", list->stitch.color, maxColorIndex);*/
        maxColorIndex = EMB_MAX(maxColorIndex, p->stitch_list->stitch[i].color);
    }
    if (p->thread_list->count == 0 || maxColorIndex == 0) {
        embPattern_addThread(p, black_thread);
    }
    else {
        if (maxColorIndex > 0) {
            while (p->thread_list->count <= maxColorIndex) {
/*        printf("%d %d\n", p->n_threads, maxColorIndex);*/
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

/*! Copies all of the Embstitch_list data to 
    EmbPolylineObjectList data for pattern (\a p). */
void
embPattern_copystitch_listToPolylines(EmbPattern* p)
{
    int breakAtFlags, i;
    EmbPoint point;
    EmbColor color;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_copystitch_listToPolylines(), ");
        printf("p argument is null\n");
        return;
    }

    breakAtFlags = (STOP | JUMP | TRIM);

    for (i = 0; i < p->stitch_list->count; i++) {
        EmbArray *pointList = 0;
        for (; i < p->stitch_list->count; i++) {
            EmbStitch st = p->stitch_list->stitch[i];
            if (st.flags & breakAtFlags) {
                break;
            }
            if (!(st.flags & JUMP)) {
                if (!pointList) {
                    pointList = embArray_create(EMB_POINT);
                    color = p->thread_list->thread[st.color].color;
                }
                point.position.x = st.x;
                point.position.y = st.y;
                embArray_addPoint(pointList, point);
            }
        }

        /* NOTE: Ensure empty polylines are not created. This is critical. */
        if (pointList) {
            EmbPolyline currentPolyline;
            currentPolyline.pointList = pointList;
            currentPolyline.color = color;
            /* TODO: Determine what the correct value should be */
            currentPolyline.lineType = 1;

            embArray_addPolyline(p->geometry, currentPolyline);
        }
    }
}

/*! Copies all of the EmbPolylineObjectList data to Embstitch_list data for pattern (\a p). */
void
embPattern_copyPolylinesTostitch_list(EmbPattern* p)
{
    int firstObject = 1, i, j;
    /*int currentColor = polyList->polylineObj->color TODO: polyline color */

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_copyPolylinesTostitch_list(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->geometry->count; i++) {
        if (p->geometry->geometry[i].type != EMB_POLYLINE) {
            continue;
        }
        EmbPolyline currentPoly;
        EmbArray* currentPointList;
        EmbThread thread;

        currentPoly = p->geometry->geometry[i].object.polyline;
        currentPointList = currentPoly.pointList;

        strcpy(thread.catalogNumber, "");
        thread.color = currentPoly.color;
        strcpy(thread.description, "");
        embPattern_addThread(p, thread);

        if (!firstObject) {
            embPattern_addStitchAbs(p,
                currentPointList->geometry[0].object.point.position.x, 
                currentPointList->geometry[0].object.point.position.y, TRIM, 1);
            embPattern_addStitchRel(p, 0.0, 0.0, STOP, 1);
        }

        embPattern_addStitchAbs(p,
            currentPointList->geometry[0].object.point.position.x,
            currentPointList->geometry[0].object.point.position.y,
            JUMP,
            1);
        for (j = 1; j < currentPointList->count; j++) { 
            EmbVector v = currentPointList->geometry[j].object.point.position;
            embPattern_addStitchAbs(p, v.x, v.y, NORMAL, 1);
        }
        firstObject = 0;
    }
    embPattern_addStitchRel(p, 0.0, 0.0, END, 1);
}

/*! Moves all of the Embstitch_list data to EmbPolylineObjectList data for pattern (\a p). */
void
embPattern_movestitch_listToPolylines(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_movestitch_listToPolylines(), p argument is null\n");
        return;
    }
    embPattern_copystitch_listToPolylines(p);
    /* Free the stitch_list and threadList since their data has now been transferred to polylines */
    p->stitch_list->count = 0;
    p->thread_list->count = 0;
}

/*! Moves all of the EmbPolylineObjectList data to Embstitch_list data for pattern (\a p). */
void
embPattern_movePolylinesTostitch_list(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_movePolylinesTostitch_list(), p argument is null\n");
        return;
    }
    embPattern_copyPolylinesTostitch_list(p);
}

/*! Adds a stitch to the pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
void
embPattern_addStitchAbs(EmbPattern* p, EmbReal x, EmbReal y, 
                            int flags, int isAutoColorIndex)
{
    EmbStitch s;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addStitchAbs(), ");
        printf("p argument is null\n");
        return;
    }

    if (flags & END) {
        if (p->stitch_list->count == 0) {
            return;
        }
        /* Prevent unnecessary multiple END stitches */
        if (p->stitch_list->stitch[p->stitch_list->count - 1].flags & END) {
            printf("ERROR: emb-pattern.c embPattern_addStitchAbs(), found multiple END stitches\n");
            return;
        }
        embPattern_fixColorCount(p);
        /* HideStitchesOverLength(127); TODO: fix or remove this */
    }

    if (flags & STOP) {
        if (p->stitch_list->count == 0) {
            return;
        }
        if (isAutoColorIndex) {
            p->currentColorIndex++;
        }
    }

    /* NOTE: If the stitch_list is empty, we will create it before adding 
        stitches to it. The first coordinate will be the HOME position. */
    if (p->stitch_list->count == 0) {
        /* NOTE: Always HOME the machine before starting any stitching */
        EmbStitch h;
        h.x = p->home.x;
        h.y = p->home.y;
        h.flags = JUMP;
        h.color = p->currentColorIndex;
        embArray_addStitch(p->stitch_list, h);
    }
    s.x = x;
    s.y = y;
    s.flags = flags;
    s.color = p->currentColorIndex;
    embArray_addStitch(p->stitch_list, s);
}

/*! Adds a stitch to the pattern (\a p) at the relative position (\a dx,\a dy) 
    to the previous stitch. Positive y is up. Units are in millimeters. */
void
embPattern_addStitchRel(EmbPattern* p, EmbReal dx, EmbReal dy, 
                            int flags, int isAutoColorIndex)
{
    EmbReal x, y;
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addStitchRel(), p argument is null\n");
        return;
    }
    if (p->stitch_list->count > 0) {
        EmbStitch st = p->stitch_list->stitch[p->stitch_list->count - 1];
        x = st.x + dx;
        y = st.y + dy;
    } else {
        /* NOTE: The stitch_list is empty, so add it to the HOME position.
         * The embstitch_list_create function will ensure the first coordinate is at the HOME position. */
        x = p->home.x + dx;
        y = p->home.y + dy;
    }
    embPattern_addStitchAbs(p, x, y, flags, isAutoColorIndex);
}

void
embPattern_changeColor(EmbPattern* p, int index)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_changeColor(), p argument is null\n");
        return;
    }
    p->currentColorIndex = index;
}

/* Very simple scaling of the x and y axis for every point.
* Doesn't insert or delete stitches to preserve density. */
void
embPattern_scale(EmbPattern* p, EmbReal scale)
{
    int i;
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_scale(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitch_list->count; i++) {
        p->stitch_list->stitch[i].x *= scale;
        p->stitch_list->stitch[i].y *= scale;
    }
}

/*! Returns an EmbRect that encapsulates all stitches and objects in the pattern (\a p). */
EmbRect
embPattern_calcBoundingBox(EmbPattern* p)
{
    EmbRect r;
    EmbStitch pt;
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
    if ((p->stitch_list->count == 0) && (p->geometry->count == 0)) {
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

    for (i = 0; i < p->stitch_list->count; i++) {
        /* If the point lies outside of the accumulated bounding
        * rectangle, then inflate the bounding rect to include it. */
        pt = p->stitch_list->stitch[i];
        if (!(pt.flags & TRIM)) {
            r.left = EMB_MIN(r.left, pt.x);
            r.top = EMB_MIN(r.top, pt.y);
            r.right = EMB_MAX(r.right, pt.x);
            r.bottom = EMB_MAX(r.bottom, pt.y);
        }
    }

    for (i = 0; i < p->geometry->count; i++) {
        EmbGeometry g = p->geometry->geometry[i];
        switch (g.type) {
        case EMB_ARC: {
            /* TODO: embPattern_calcBoundingBox for arcs, 
            for now just checks the start point */
            EmbArc arc = g.object.arc;
            r.left = EMB_MIN(r.left, arc.start.x);
            r.top = EMB_MIN(r.top, arc.start.y);
            r.right = EMB_MAX(r.right, arc.start.x);
            r.bottom = EMB_MAX(r.bottom, arc.start.y);
            break;
        }
        case EMB_CIRCLE: {
            EmbCircle circle = g.object.circle;
            r.left = EMB_MIN(r.left, circle.center.x - circle.radius);
            r.top = EMB_MIN(r.top, circle.center.y - circle.radius);
            r.right = EMB_MAX(r.right, circle.center.x + circle.radius);
            r.bottom = EMB_MAX(r.bottom, circle.center.y + circle.radius);
            break;
        }
        case EMB_ELLIPSE: {
            /* TODO: account for rotation */
            EmbEllipse ellipse = g.object.ellipse;
            r.left = EMB_MIN(r.left, ellipse.center.x - ellipse.radius.x);
            r.top = EMB_MIN(r.top, ellipse.center.y - ellipse.radius.y);
            r.right = EMB_MAX(r.right, ellipse.center.x + ellipse.radius.x);
            r.bottom = EMB_MAX(r.bottom, ellipse.center.y + ellipse.radius.y);
            break;
        }
        case EMB_LINE: {
            EmbLine line = g.object.line;
            r.left = EMB_MIN(r.left, line.start.x);
            r.left = EMB_MIN(r.left, line.end.x);
            r.top = EMB_MIN(r.top, line.start.y);
            r.top = EMB_MIN(r.top, line.end.y);
            r.right = EMB_MAX(r.right, line.start.x);
            r.right = EMB_MAX(r.right, line.end.x);
            r.bottom = EMB_MAX(r.bottom, line.start.y);
            r.bottom = EMB_MAX(r.bottom, line.end.y);
            break;
        }
        case EMB_POINT: {
            EmbVector point = g.object.point.position;
            r.left = EMB_MIN(r.left, point.x);
            r.top = EMB_MIN(r.top, point.y);
            r.right = EMB_MAX(r.right, point.x);
            r.bottom = EMB_MAX(r.bottom, point.y);
            break;
        }
        case EMB_POLYGON: {
            EmbArray *polygon = g.object.polygon.pointList;
            for (j=0; j < polygon->count; j++) {
                /* TODO: embPattern_calcBoundingBox for polygons */
            }
            break;
        }
        case EMB_POLYLINE: {
            EmbArray *polyline = g.object.polyline.pointList;
            for (j=0; j < polyline->count; j++) {
                /* TODO: embPattern_calcBoundingBox for polylines */
            }
            break;
        }
        case EMB_RECT: {
            EmbRect rect = g.object.rect;
            r.left = EMB_MIN(r.left, rect.left);
            r.top = EMB_MIN(r.top, rect.top);
            r.right = EMB_MAX(r.right, rect.right);
            r.bottom = EMB_MAX(r.bottom, rect.bottom);
            break;
        }
        case EMB_SPLINE: {
            /* EmbBezier bezier;
            bezier = p->splines->spline[i].bezier; */
            /* TODO: embPattern_calcBoundingBox for splines */
            break;
        }
        default:
            break;
        }
    }

    return r;
}

/*! Flips the entire pattern (\a p) horizontally about the y-axis. */
void
embPattern_flipHorizontal(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_flipHorizontal(), ");
        printf("p argument is null\n");
        return;
    }
    embPattern_flip(p, 1, 0);
}

/*! Flips the entire pattern (\a p) vertically about the x-axis. */
void
embPattern_flipVertical(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_flipVertical(), ");
        printf("p argument is null\n");
        return;
    }
    embPattern_flip(p, 0, 1);
}

/*! Flips the entire pattern (\a p) horizontally about the x-axis if (\a horz) is true.
 *  Flips the entire pattern (\a p) vertically about the y-axis if (\a vert) is true. */
void
embPattern_flip(EmbPattern* p, int horz, int vert)
{
    int i, j;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_flip(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitch_list->count; i++) {
        if (horz) {
            p->stitch_list->stitch[i].x *= -1.0;
        }
        if (vert) {
            p->stitch_list->stitch[i].y *= -1.0;
        }
    }

    for (i = 0; i < p->geometry->count; i++) {
        EmbGeometry *g = &(p->geometry->geometry[i]);
        switch (g->type) {
        case EMB_ARC: {
            if (horz) {
                g->object.arc.start.x *= -1.0;
                g->object.arc.mid.x *= -1.0;
                g->object.arc.end.x *= -1.0;
            }
            if (vert) {
                g->object.arc.start.y *= -1.0;
                g->object.arc.mid.y *= -1.0;
                g->object.arc.end.y *= -1.0;
            }
            break;
        }
        case EMB_LINE: {
            if (horz) {
                g->object.line.start.x *= -1.0;
                g->object.line.end.x *= -1.0;
            }
            if (vert) {
                g->object.line.start.y *= -1.0;
                g->object.line.end.y *= -1.0;
            }
            break;
        }
        case EMB_CIRCLE: {
            if (horz) {
                g->object.circle.center.x *= -1.0;
            }
            if (vert) {
                g->object.circle.center.y *= -1.0;
            }
            break;
        }
        case EMB_ELLIPSE:
            if (horz) {
                g->object.ellipse.center.x *= -1.0;
            }
            if (vert) {
                g->object.ellipse.center.y *= -1.0;
            }
            break;
        case EMB_PATH: {
            EmbArray *point_list = g->object.path.pointList;
            for (j=0; j < point_list->count; j++) {
                if (horz) {
                    point_list->geometry[j].object.point.position.x *= -1.0;
                }
                if (vert) {
                    point_list->geometry[j].object.point.position.y *= -1.0;
                }
            }
            break;
        }
        case EMB_POINT:
            if (horz) {
                g->object.point.position.x *= -1.0;
            }
            if (vert) {
                g->object.point.position.y *= -1.0;
            }
            break;
        case EMB_POLYGON: {
            EmbArray *point_list = g->object.polygon.pointList;
            for (j=0; j < point_list->count; j++) {
                if (horz) {
                    point_list->geometry[i].object.point.position.x *= -1.0;
                }
                if (vert) {
                    point_list->geometry[i].object.point.position.y *= -1.0;
                }
            }
            break;
        }
        case EMB_POLYLINE: {
            EmbArray *point_list = g->object.polygon.pointList;
            for (j=0; j < point_list->count; j++) {
                if (horz) {
                    point_list->geometry[j].object.point.position.x *= -1.0;
                }
                if (vert) {
                    point_list->geometry[j].object.point.position.y *= -1.0;
                }
            }
            break;
        }
        case EMB_RECT: {
            if (horz) {
                g->object.rect.left *= -1.0;
                g->object.rect.right *= -1.0;
            }
            if (vert) {
                g->object.rect.top *= -1.0;
                g->object.rect.bottom *= -1.0;
            }
            break;
        }
        case EMB_SPLINE:
            /* TODO */
            break;
        default:
            break;
        }
    }
}

void
embPattern_combineJumpStitches(EmbPattern* p)
{
    int jumpCount = 0, i;
    EmbArray *newList;
    EmbStitch j;

    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_combineJumpStitches(), ");
        printf("p argument is null\n");
        return;
    }
    newList = embArray_create(EMB_STITCH);
    for (i = 0; i < p->stitch_list->count; i++) {
        EmbStitch st = p->stitch_list->stitch[i];
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
    embArray_free(p->stitch_list);
    p->stitch_list = newList;
}

/*TODO: The params determine the max XY movement rather than the length. 
    They need renamed or clarified further. */
void
embPattern_correctForMaxStitchLength(EmbPattern* p, 
                        EmbReal maxStitchLength, EmbReal maxJumpLength)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_correctForMaxStitchLength(), ");
        printf("p argument is null\n");
        return;
    }
    if (p->stitch_list->count > 1) {
        int i, j, splits;
        EmbReal maxXY, maxLen, addX, addY;
        EmbArray *newList = embArray_create(EMB_STITCH);
        for (i=1; i < p->stitch_list->count; i++) {
            EmbStitch st = p->stitch_list->stitch[i];
            EmbReal xx = st.x;
            EmbReal yy = st.y;
            EmbReal dx = p->stitch_list->stitch[i-1].x - xx;
            EmbReal dy = p->stitch_list->stitch[i-1].y - yy;
            if ((fabs(dx) > maxStitchLength) || (fabs(dy) > maxStitchLength)) {
                maxXY = EMB_MAX(fabs(dx), fabs(dy));
                if (st.flags & (JUMP | TRIM)) {
                    maxLen = maxJumpLength;
                } else {
                    maxLen = maxStitchLength;
                }
                splits = (int)ceil((EmbReal)maxXY / maxLen);

                if (splits > 1) {
                    addX = (EmbReal)dx / splits;
                    addY = (EmbReal)dy / splits;

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
        embArray_free(p->stitch_list);
        p->stitch_list = newList;
    }
    embPattern_end(p);
}

void
embPattern_center(EmbPattern* p)
{
    /* TODO: review this. currently not used in anywhere. 
        Also needs to handle various design objects */
    int moveLeft, moveTop, i;
    EmbRect boundingRect;
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_center(), p argument is null\n");
        return;
    }
    boundingRect = embPattern_calcBoundingBox(p);

    moveLeft = (int)(boundingRect.left - (boundingRect.right- boundingRect.left) / 2.0);
    moveTop = (int)(boundingRect.top - (boundingRect.bottom - boundingRect.top) / 2.0);

    for (i = 0; i < p->stitch_list->count; i++) {
        p->stitch_list->stitch[i].x -= moveLeft;
        p->stitch_list->stitch[i].y -= moveTop;
    }
}

/*TODO: Description needed. */
void
embPattern_loadExternalColorFile(EmbPattern* p, const char* fileName)
{
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
void
embPattern_free(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_free(), p argument is null\n");
        return;
    }
    embArray_free(p->stitch_list);
    embArray_free(p->thread_list);
    embArray_free(p->geometry);
    free(p);
}

/*! Adds a circle object to pattern (\a p) with its center at the absolute
 * position (\a cx,\a cy) with a radius of (\a r). Positive y is up.
 * Units are in millimeters. */
void
embPattern_addCircleAbs(EmbPattern* p, EmbCircle circle)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addCircleObjectAbs(), p argument is null\n");
        return;
    }

    embArray_addCircle(p->geometry, circle);
}

/*! Adds an ellipse object to pattern (\a p) with its center at the
 * absolute position (\a cx,\a cy) with radii of (\a rx,\a ry). Positive y is up.
 * Units are in millimeters. */
void
embPattern_addEllipseAbs(EmbPattern* p, EmbEllipse ellipse)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addEllipseObjectAbs(), p argument is null\n");
        return;
    }

    embArray_addEllipse(p->geometry, ellipse);
}

/*! Adds a line object to pattern (\a p) starting at the absolute position
 * (\a x1,\a y1) and ending at the absolute position (\a x2,\a y2).
 * Positive y is up. Units are in millimeters.
 */
void
embPattern_addLineAbs(EmbPattern* p, EmbLine line)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addLineObjectAbs(), p argument is null\n");
        return;
    }

    embArray_addLine(p->geometry, line);
}

void
embPattern_addPathAbs(EmbPattern* p, EmbPath obj)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj.pointList) {
        printf("ERROR: emb-pattern.c embPattern_addPathObjectAbs(), obj->pointList is empty\n");
        return;
    }

    embArray_addPath(p->geometry, obj);
}

/*! Adds a point object to pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
void
embPattern_addPointAbs(EmbPattern* p, EmbPoint obj)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addPointObjectAbs(), p argument is null\n");
        return;
    }

    embArray_addPoint(p->geometry, obj);
}

void
embPattern_addPolygonAbs(EmbPattern* p, EmbPolygon obj)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj.pointList) {
        printf("ERROR: emb-pattern.c embPattern_addPolygonObjectAbs(), obj->pointList is empty\n");
        return;
    }

    embArray_addPolygon(p->geometry, obj);
}

void
embPattern_addPolylineObjectAbs(EmbPattern* p, EmbPolyline obj)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addPolylineObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj.pointList) {
        printf("ERROR: emb-pattern.c embPattern_addPolylineObjectAbs(), obj->pointList is empty\n");
        return;
    }
    embArray_addPolyline(p->geometry, obj);
}

/**
 * Adds a rectangle object to pattern (\a p) at the absolute position
 * (\a x,\a y) with a width of (\a w) and a height of (\a h).
 * Positive y is up. Units are in millimeters.
 */
void
embPattern_addRectAbs(EmbPattern* p, EmbRect rect)
{
    if (!p) {
        printf("ERROR: emb-pattern.c embPattern_addRectObjectAbs(), p argument is null\n");
        return;
    }
    embArray_addRect(p->geometry, rect);
}

void
embPattern_end(EmbPattern *p)
{
    if (p->stitch_list->count == 0) {
        return;
    }
    /* Check for an END stitch and add one if it is not present */
    if (p->stitch_list->stitch[p->stitch_list->count-1].flags != END) {
        embPattern_addStitchRel(p, 0, 0, END, 1);
    }
}


int
embPattern_color_count(EmbPattern *pattern, EmbColor startColor)
{
    int numberOfColors = 0, i;
    EmbColor color = startColor;
    for (i=0; i<pattern->stitch_list->count; i++) {
        EmbColor newColor;
        EmbStitch st;

        st = pattern->stitch_list->stitch[i];

        newColor = pattern->thread_list->thread[st.color].color;
        if (embColor_distance(newColor, color) != 0) {
            numberOfColors++;
            color = newColor;
        }
        else if (st.flags & END || st.flags & STOP) {
            numberOfColors++;
        }

        while (pattern->stitch_list->stitch[i+1].flags == st.flags) {
            i++;
            if (i >= pattern->stitch_list->count-2) {
                break;
            }
        }
    }
    return numberOfColors;
}


void
embPattern_designDetails(EmbPattern *pattern)
{
    int colors, num_stitches, real_stitches, jump_stitches, trim_stitches;
    int unknown_stitches, num_colors;
    EmbRect bounds;

    puts("Design Details");
    bounds = embPattern_calcBoundingBox(pattern);

    colors = 1;
    num_stitches = pattern->stitch_list->count;
    real_stitches = 0;
    jump_stitches = 0;
    trim_stitches = 0;
    unknown_stitches = 0;
    bounds = embPattern_calcBoundingBox(pattern);
    
    if (emb_verbose > 1) {
        printf("colors: %d\n", colors);
        printf("num_stitches: %d\n", num_stitches);
        printf("real_stitches: %d\n", real_stitches);
        printf("jump_stitches: %d\n", jump_stitches);
        printf("trim_stitches: %d\n", trim_stitches);
        printf("unknown_stitches: %d\n", unknown_stitches);
        printf("num_colors: %d\n", pattern->thread_list->count);
        printf("bounds.left: %f\n", bounds.left);
        printf("bounds.right: %f\n", bounds.right);
        printf("bounds.top: %f\n", bounds.top);
        printf("bounds.bottom: %f\n", bounds.bottom);
    }
/*
    EmbReal minx = 0.0, maxx = 0.0, miny = 0.0, maxy = 0.0;
    EmbReal min_stitchlength = 999.0;
    EmbReal max_stitchlength = 0.0;
    EmbReal total_stitchlength = 0.0;
    int number_of_minlength_stitches = 0;
    int number_of_maxlength_stitches = 0;

    EmbReal xx = 0.0, yy = 0.0;
    EmbReal length = 0.0;

    if (num_stitches == 0) {
        QMessageBox::warning(this, tr("No Design Loaded"), tr("<b>A design needs to be loaded or created before details can be determined.</b>"));
        return;
    }
    QVector<EmbReal> stitchLengths;

    EmbReal totalColorLength = 0.0;
    int i;
    for (i = 0; i < num_stitches; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        EmbReal dx, dy;
        dx = st.x - xx;
        dy = st.y - yy;
        xx = st.x;
        yy = st.y;
        length=sqrt(dx * dx + dy * dy);
        totalColorLength += length;
        if(i > 0 && embstitch_list_getAt(pattern->stitch_list, i-1).flags != NORMAL)
            length = 0.0; //can't count first normal stitch;
        if(!(embstitch_list_getAt(pattern->stitch_list, i).flags & (JUMP | TRIM)))
        {
            real_stitches++;
            if(length > max_stitchlength) { max_stitchlength = length; number_of_maxlength_stitches = 0; }
            if(length == max_stitchlength) number_of_maxlength_stitches++;
            if(length > 0 && length < min_stitchlength)
            {
                min_stitchlength = length;
                number_of_minlength_stitches = 0;
            }
            if(length == min_stitchlength) number_of_minlength_stitches++;
            total_stitchlength += length;
            if(xx < minx) minx = xx;
            if(xx > maxx) maxx = xx;
            if(yy < miny) miny = yy;
            if(yy > maxy) maxy = yy;
        }
        if (st.flags & JUMP) {
            jump_stitches++;
        }
        if (st.flags & TRIM) {
            trim_stitches++;
        }
        if (st.flags & STOP) {
            stitchLengths.push_back(totalColorLength);
            totalColorLength = 0;
            colors++;
        }
        if (st.flags & END) {
            stitchLengths.push_back(totalColorLength);
        }
    }

    //second pass to fill bins now that we know max stitch length
#define NUMBINS 10
    int bin[NUMBINS+1];
    int i;
    for (i = 0; i <= NUMBINS; i++) {
        bin[i]=0;
    }

    for (i = 0; i < num_stitches; i++) {
        dx = embstitch_list_getAt(pattern->stitch_list, i).xx - xx;
        dy = embstitch_list_getAt(pattern->stitch_list, i).yy - yy;
        xx = embstitch_list_getAt(pattern->stitch_list, i).xx;
        yy = embstitch_list_getAt(pattern->stitch_list, i).yy;
        if(i > 0 && embstitch_list_getAt(pattern->stitch_list, i-1).flags == NORMAL && embstitch_list_getAt(pattern->stitch_list, i).flags == NORMAL)
        {
            length=sqrt(dx * dx + dy * dy);
            bin[int(floor(NUMBINS*length/max_stitchlength))]++;
        }
    }

    EmbReal binSize = max_stitchlength / NUMBINS;

    QString str;
    int i;
    for (i = 0; i < NUMBINS; i++) {
        str += QString::number(binSize * (i), 'f', 1) + " - " + QString::number(binSize * (i+1), 'f', 1) + " mm: " +  QString::number(bin[i]) + "\n\n";
    }

    puts("Stitches: %d\n", num_stitches);
    puts("Colors: %d\n", num_colors);
    puts("Jumps: %d\n", jump_stitches);
    puts("Top: %f mm", bounds.top);
    puts("Left: %f mm", bounds.left);
    puts("Bottom: %f mm", bounds.bottom);
    puts("Right: %f mm", bounds.right);
    puts("Width: %f mm", bounds.right - bounds.left);
    puts("Height: %f mm", bounds.bottom - bounds.top);
    grid->addWidget(new QLabel(tr("\nStitch Distribution: \n")),9,0,1,2);
    grid->addWidget(new QLabel(str), 10, 0, 1, 1);
    grid->addWidget(new QLabel(tr("\nThread Length By Color: \n")),11,0,1,2);
    int currentRow = 12;

    int i;
    for (i = 0; i < num_colors; i++) {
        QFrame *frame = new QFrame();
        frame->setGeometry(0,0,30,30);
        QPalette palette = frame->palette();
        EmbColor t = embThreadList_getAt(pattern->threadList, i).color;
        palette.setColor(backgroundRole(), QColor( t.r, t.g, t.b ) );
        frame->setPalette( palette );
        frame->setAutoFillBackground(true);
        grid->addWidget(frame, currentRow,0,1,1);
        debug_message("size: %d i: %d", stitchLengths.size(), i);
        grid->addWidget(new QLabel(QString::number(stitchLengths.at(i)) + " mm"), currentRow,1,1,1);
        currentRow++;
    }

    QDialogButtonBox buttonbox(Qt::Horizontal, &dialog);
    QPushButton button(&dialog);
    button.setText("Ok");
    buttonbox.addButton(&button, QDialogButtonBox::AcceptRole);
    buttonbox.setCenterButtons(true);
    connect(&buttonbox, SIGNAL(accepted()), &dialog, SLOT(accept()));

    grid->addWidget(&buttonbox, currentRow, 0, 1, 2);
*/
}


/*
 *
 */
int
convert(const char *inf, const char *outf)
{
    EmbPattern* p = 0;
    int reader, writer;

    p = embPattern_create();
    if (!p) {
        printf("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    if (!embPattern_readAuto(p, inf)) {
        printf("ERROR: convert(), reading file was unsuccessful: %s\n", inf);
        embPattern_free(p);
        return 1;
    }

    reader = emb_identify_format(inf);
    writer = emb_identify_format(outf);
    if (formatTable[reader].type == EMBFORMAT_OBJECTONLY) {
        if (formatTable[writer].type == EMBFORMAT_STITCHONLY) {
            embPattern_movePolylinesTostitch_list(p);
        }
    }

    if (!embPattern_writeAuto(p, outf)) {
        printf("ERROR: convert(), writing file %s was unsuccessful\n", outf);
        embPattern_free(p);
        return 1;
    }

    embPattern_free(p);
    return 0;
}

float embPattern_totalStitchLength(EmbPattern *pattern)
{
    EmbArray *sts = pattern->stitch_list;
    float result = 0.0;
    int i;
    for (i = 1; i < sts->count; i++) {
        EmbStitch st = sts->stitch[i];
        EmbReal length = 0.0;
        EmbVector delta;
        delta.x = sts->stitch[i].x - sts->stitch[i-1].x;
        delta.y = sts->stitch[i].y - sts->stitch[i-1].y;
        length = embVector_length(delta);
        if (sts->stitch[i].flags & NORMAL)
        if (sts->stitch[i-1].flags & NORMAL) {
            result += length;
        }
    }
    return result;
}

float embPattern_minimumStitchLength(EmbPattern *pattern)
{
    EmbArray *sts = pattern->stitch_list;
    float result = 1.0e10;
    int i;
    for (i = 1; i < sts->count; i++) {
        EmbReal length = 0.0;
        EmbVector delta;
        delta.x = sts->stitch[i].x - sts->stitch[i-1].x;
        delta.y = sts->stitch[i].y - sts->stitch[i-1].y;
        length = embVector_length(delta);
        if (sts->stitch[i].flags & NORMAL)
        if (sts->stitch[i-1].flags & NORMAL) {
            if (length < result) {
                result = length;
            }
        }
    }
    return result;
}

float embPattern_maximumStitchLength(EmbPattern *pattern)
{
    EmbArray *sts = pattern->stitch_list;
    float result = 0.0;
    int i;
    for (i = 1; i < sts->count; i++) {
        EmbReal length = 0.0;
        EmbVector delta;
        delta.x = sts->stitch[i].x - sts->stitch[i-1].x;
        delta.y = sts->stitch[i].y - sts->stitch[i-1].y;
        length = embVector_length(delta);
        if (sts->stitch[i].flags & NORMAL)
        if (sts->stitch[i-1].flags & NORMAL) {
            if (length > result) {
                result = length;
            }
        }
    }
    return result;
}

void embPattern_lengthHistogram(EmbPattern *pattern, int *bin, int NUMBINS)
{
    int i;
    float max_stitch_length = embPattern_maximumStitchLength(pattern);
    EmbArray *sts = pattern->stitch_list;
    for (i = 0; i <= NUMBINS; i++) {
        bin[i] = 0;
    }

    for (i = 1; i < sts->count; i++) {
        if (sts->stitch[i].flags & NORMAL)
        if (sts->stitch[i-1].flags & NORMAL) {
            EmbVector delta;
            delta.x = sts->stitch[i].x - sts->stitch[i-1].x;
            delta.y = sts->stitch[i].y - sts->stitch[i-1].x;
            float length = embVector_length(delta);
            bin[(int)(floor(NUMBINS*length/max_stitch_length))]++;
        }
    }
}

int embPattern_realStitches(EmbPattern *pattern)
{
    int i;
    EmbArray *sts = pattern->stitch_list;
    int real_stitches = 0;
    for (i = 0; i < sts->count; i++) {
        if (!(sts->stitch[i].flags & (JUMP | TRIM | END))) {
            real_stitches++;
        }
    }
    return real_stitches;
}

int embPattern_jumpStitches(EmbPattern *pattern)
{
    int i;
    EmbArray *sts = pattern->stitch_list;
    int jump_stitches = 0;
    for (i = 0; i < sts->count; i++) {
        if (sts->stitch[i].flags & JUMP) {
            jump_stitches++;
        }
    }
    return jump_stitches;
}


int embPattern_trimStitches(EmbPattern *pattern)
{
    int i;
    EmbArray *sts = pattern->stitch_list;
    int trim_stitches = 0;
    for (i = 0; i < sts->count; i++) {
        if (sts->stitch[i].flags & TRIM) {
            trim_stitches++;
        }
    }
    return trim_stitches;
}
