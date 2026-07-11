/**
 * @file pattern.c The file is for the management of the main struct: EmbPattern.
 * */

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "embroidery.h"

/* 
 * Returns a pointer to an EmbPattern. It is created on the heap.
 * The caller is responsible for freeing the allocated memory with
 * emb_free().
 *
 * Returns EmbPattern*
 */
EmbPattern *emb_create(void)
{
    EmbPattern *p = (EmbPattern *) malloc(sizeof(EmbPattern));
    if (!p) {
        printf("ERROR: emb-pattern.c emb_create(), ");
        printf("unable to allocate memory for p\n");
        return 0;
    }
    p->dstJumpsPerTrim = 6;
    p->home.x = 0.0;
    p->home.y = 0.0;
    p->currentColorIndex = 0;
    p->stitch_list = emb_array_create(EMB_STITCH);
    p->thread_list = emb_array_create(EMB_THREAD);
    p->hoop_height = 0.0;
    p->hoop_width = 0.0;
    p->geometry = emb_array_create(EMB_LINE);
    return p;
}

/* a p a length
 */
void emb_hideStitchesOverLength(EmbPattern * p, int length)
{
    EmbVector prev;
    int i;
    prev.x = 0.0;
    prev.y = 0.0;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_hideStitchesOverLength(), ");
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

/* a pattern a thread
 * Returns int
 */
int emb_add_thread(EmbPattern * pattern, EmbThread thread)
{
    if (pattern->thread_list->count + 1 > pattern->thread_list->length) {
        if (!emb_array_resize(pattern->thread_list)) {
            return 0;
        }
    }
    pattern->thread_list->thread[pattern->thread_list->count] = thread;
    pattern->thread_list->count++;
    return 1;
}

/* a p
 */
void emb_fix_color_count(EmbPattern * p)
{
    /* fix color count to be max of color index. */
    int maxColorIndex = 0, i;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_fix_color_count(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->stitch_list->count; i++) {
/*        printf("%d %d\n", list->stitch.color, maxColorIndex);*/
        maxColorIndex = EMB_MAX(maxColorIndex, p->stitch_list->stitch[i].color);
    }
    if (p->thread_list->count == 0 || maxColorIndex == 0) {
        emb_add_thread(p, black_thread);
    } else {
        if (maxColorIndex > 0) {
            while (p->thread_list->count <= maxColorIndex) {
/*        printf("%d %d\n", p->n_threads, maxColorIndex);*/
                emb_add_thread(p, emb_get_random_thread());
            }
        }
    }
    /*
       while (p->threadLists->count > (maxColorIndex + 1)) {
       TODO: erase last color    p->threadList.pop_back();
       }
     */
}

/* Copies all of the Embstitch_list data to
 * EmbPolylineObjectList data for pattern (a p).
 */
void emb_copystitch_listToPolylines(EmbPattern * p)
{
    int breakAtFlags, i;
    EmbPoint point;
    EmbColor color;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_copystitch_listToPolylines(), ");
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
                    pointList = emb_array_create(EMB_POINT);
                    color = p->thread_list->thread[st.color].color;
                }
                point.position.x = st.x;
                point.position.y = st.y;
                emb_array_addPoint(pointList, point);
            }
        }

        /* NOTE: Ensure empty polylines are not created. This is critical. */
        if (pointList) {
            EmbPolyline currentPolyline;
            currentPolyline.pointList = pointList;
            currentPolyline.color = color;
            /* TODO: Determine what the correct value should be */
            currentPolyline.lineType = 1;

            emb_array_addPolyline(p->geometry, currentPolyline);
        }
    }
}

/* Copies all of the EmbPolylineObjectList data to Embstitch_list
 * data for pattern (a p).
 */
void emb_copyPolylinesTostitch_list(EmbPattern * p) {
    int firstObject = 1, i, j;
    /*int currentColor = polyList->polylineObj->color TODO: polyline color */

    if (!p) {
        printf("ERROR: emb-pattern.c emb_copyPolylinesTostitch_list(), ");
        printf("p argument is null\n");
        return;
    }
    for (i = 0; i < p->geometry->count; i++) {
        EmbPolyline currentPoly;
        EmbArray *currentPointList;
        EmbThread thread;

        if (p->geometry->geometry[i].type != EMB_POLYLINE) {
            continue;
        }

        currentPoly = p->geometry->geometry[i].object.polyline;
        currentPointList = currentPoly.pointList;

        strcpy(thread.catalogNumber, "");
        thread.color = currentPoly.color;
        strcpy(thread.description, "");
        emb_add_thread(p, thread);

        if (!firstObject) {
            emb_add_stitch_abs(p,
                              currentPointList->geometry[0].object.point.
                              position.x,
                              currentPointList->geometry[0].object.point.
                              position.y, TRIM, 1);
            emb_add_stitch(p, 0.0, 0.0, STOP, 1);
        }

        emb_add_stitch_abs(p,
                          currentPointList->geometry[0].object.point.position.x,
                          currentPointList->geometry[0].object.point.position.y,
                          JUMP, 1);
        for (j = 1; j < currentPointList->count; j++) {
            EmbVector v = currentPointList->geometry[j].object.point.position;
            emb_add_stitch_abs(p, v.x, v.y, NORMAL, 1);
        }
        firstObject = 0;
    }
    emb_add_stitch(p, 0.0, 0.0, END, 1);
}

/* Moves all of the Embstitch_list data to EmbPolylineObjectList
 * data for pattern (a p).
 */
void emb_movestitch_listToPolylines(EmbPattern * p) {
    if (!p) {
        printf
            ("ERROR: emb-pattern.c emb_movestitch_listToPolylines(), p argument is null\n");
        return;
    }
    emb_copystitch_listToPolylines(p);
    /* Free the stitch_list and threadList since their data has now been transferred to polylines */
    p->stitch_list->count = 0;
    p->thread_list->count = 0;
}

/* Moves all of the EmbPolylineObjectList data to Embstitch_list
 * data for pattern (a p).
 */
void emb_movePolylinesTostitch_list(EmbPattern * p) {
    if (!p) {
        printf
            ("ERROR: emb-pattern.c emb_movePolylinesTostitch_list(), p argument is null\n");
        return;
    }
    emb_copyPolylinesTostitch_list(p);
}

/* Adds a stitch to the pattern (a p) at the absolute position
 * (a x,a y). Positive y is up. Units are in millimeters.
 */
void emb_add_stitch_abs(EmbPattern * p, EmbReal x, EmbReal y,
                   int flags, int isAutoColorIndex)
{
    EmbStitch s;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_add_stitch_abs(), ");
        printf("p argument is null\n");
        return;
    }

    if (flags & END) {
        if (p->stitch_list->count == 0) {
            return;
        }
        /* Prevent unnecessary multiple END stitches */
        if (p->stitch_list->stitch[p->stitch_list->count - 1].flags & END) {
            printf
                ("ERROR: emb-pattern.c emb_add_stitch_abs(), found multiple END stitches\n");
            return;
        }
        emb_fix_color_count(p);
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
        emb_array_addStitch(p->stitch_list, h);
    }
    s.x = x;
    s.y = y;
    s.flags = flags;
    s.color = p->currentColorIndex;
    emb_array_addStitch(p->stitch_list, s);
}

/* Adds a stitch to the pattern (a p) at the relative position
 * (a dx,a dy) to the previous stitch. Positive y is up.
 * Units are in millimeters.
 */
void emb_add_stitch(EmbPattern * p, EmbReal dx, EmbReal dy,
                   int flags, int isAutoColorIndex)
{
    EmbReal x, y;
    if (!p) {
        printf
            ("ERROR: emb-pattern.c emb_add_stitch(), p argument is null\n");
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
    emb_add_stitch_abs(p, x, y, flags, isAutoColorIndex);
}

/* Change the currentColorIndex of pattern a p to a index.
 */
void emb_changeColor(EmbPattern * p, int index)
{
    if (!p) {
        printf("ERROR: emb-pattern.c emb_changeColor(), p argument is null\n");
        return;
    }
    p->currentColorIndex = index;
}

/* Very simple scaling of the x and y axis for every point.
 * Doesn't insert or delete stitches to preserve density.
 */
void emb_scale(EmbPattern * p, EmbReal scale)
{
    int i;
    if (!p) {
        printf("ERROR: emb-pattern.c emb_scale(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitch_list->count; i++) {
        p->stitch_list->stitch[i].x *= scale;
        p->stitch_list->stitch[i].y *= scale;
    }
}

/* Returns an EmbRect that encapsulates all stitches and objects in the
 * pattern (a p).
 */
EmbRect emb_bounds(EmbPattern * p)
{
    EmbRect r;
    EmbStitch pt;
    int i, j;

    r.x = 0.0;
    r.y = 0.0;
    r.w = 1.0;
    r.h = 1.0;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_bounds(), ");
        printf("p argument is null\n");
        return r;
    }

    /* Calculate the bounding rectangle.  It's needed for smart repainting. */
    /* TODO: Come back and optimize this mess so that after going thru all objects
     * and stitches, if the rectangle isn't reasonable, then return a default rect
     */
    if ((p->stitch_list->count == 0) && (p->geometry->count == 0)) {
        return r;
    }
    r.x = -99999.0;
    r.y = -99999.0;
    double right = 99999.0;
    double bottom = 99999.0;

    for (i = 0; i < p->stitch_list->count; i++) {
        /* If the point lies outside of the accumulated bounding
         * rectangle, then inflate the bounding rect to include it. */
        pt = p->stitch_list->stitch[i];
        if (!(pt.flags & TRIM)) {
            r.x = EMB_MAX(r.x, pt.x);
            r.y = EMB_MAX(r.y, pt.y);
            right = EMB_MIN(right, pt.x);
            bottom = EMB_MIN(bottom, pt.y);
        }
    }

    for (i = 0; i < p->geometry->count; i++) {
        EmbGeometry g = p->geometry->geometry[i];
        switch (g.type) {
        case EMB_ARC:{
                /* TODO: emb_calcBoundingBox for arcs,
                   for now just checks the start point */
                EmbArc arc = g.object.arc;
                r.x = EMB_MIN(r.x, arc.start.x);
                r.y = EMB_MIN(r.y, arc.start.y);
                right = EMB_MAX(right, arc.start.x);
                bottom = EMB_MAX(bottom, arc.start.y);
                break;
            }
        case EMB_CIRCLE:{
                EmbCircle circle = g.object.circle;
                r.x = EMB_MIN(r.x, circle.center.x - circle.radius);
                r.y = EMB_MIN(r.y, circle.center.y - circle.radius);
                right = EMB_MAX(right, circle.center.x + circle.radius);
                bottom = EMB_MAX(bottom, circle.center.y + circle.radius);
                break;
            }
        case EMB_ELLIPSE:{
                /* TODO: account for rotation */
                EmbEllipse ellipse = g.object.ellipse;
                r.x = EMB_MIN(r.x, ellipse.center.x - ellipse.radius.x);
                r.y = EMB_MIN(r.y, ellipse.center.y - ellipse.radius.y);
                right = EMB_MAX(right, ellipse.center.x + ellipse.radius.x);
                bottom = EMB_MAX(bottom, ellipse.center.y + ellipse.radius.y);
                break;
            }
        case EMB_LINE:{
                EmbLine line = g.object.line;
                r.x = EMB_MIN(r.x, line.start.x);
                r.x = EMB_MIN(r.x, line.end.x);
                r.y = EMB_MIN(r.y, line.start.y);
                r.y = EMB_MIN(r.y, line.end.y);
                right = EMB_MAX(right, line.start.x);
                right = EMB_MAX(right, line.end.x);
                bottom = EMB_MAX(bottom, line.start.y);
                bottom = EMB_MAX(bottom, line.end.y);
                break;
            }
        case EMB_POINT:{
                EmbVector point = g.object.point.position;
                r.x = EMB_MIN(r.x, point.x);
                r.y = EMB_MIN(r.y, point.y);
                right = EMB_MAX(right, point.x);
                bottom = EMB_MAX(bottom, point.y);
                break;
            }
        case EMB_POLYGON:{
                EmbArray *polygon = g.object.polygon.pointList;
                for (j = 0; j < polygon->count; j++) {
                    /* TODO: emb_calcBoundingBox for polygons */
                }
                break;
            }
        case EMB_POLYLINE:{
                EmbArray *polyline = g.object.polyline.pointList;
                for (j = 0; j < polyline->count; j++) {
                    /* TODO: emb_calcBoundingBox for polylines */
                }
                break;
            }
        case EMB_RECT:{
                EmbRect rect = g.object.rect;
                r.x = EMB_MIN(r.x, rect.x);
                r.y = EMB_MIN(r.y, rect.y);
                right = EMB_MAX(right, r.x + rect.w);
                bottom = EMB_MAX(bottom, r.y + rect.h);
                break;
            }
        case EMB_SPLINE:{
                /* EmbBezier bezier;
                   bezier = p->splines->spline[i].bezier; */
                /* TODO: emb_calcBoundingBox for splines */
                break;
            }
        default:
            break;
        }
    }

    r.w = right - r.x;
    r.h = bottom - r.y;

    return r;
}

/* Flips the entire pattern (a p) horizontally about the y-axis.
 */
void emb_flip_horizontal(EmbPattern * p) {
    if (!p) {
        printf("ERROR: emb-pattern.c emb_flip_horizontal(), ");
        printf("p argument is null\n");
        return;
    }
    emb_flip(p, 1, 0);
}

/* Flips the entire pattern (a p) vertically about the x-axis.
 */
void emb_flip_vertical(EmbPattern * p) {
    if (!p) {
        printf("ERROR: emb-pattern.c emb_flip_vertical(), ");
        printf("p argument is null\n");
        return;
    }
    emb_flip(p, 0, 1);
}

/* Flips the entire pattern (a p) horizontally about the x-axis if (a horz) is true.
 *  Flips the entire pattern (a p) vertically about the y-axis if (a vert) is true.
 */
void emb_flip(EmbPattern * p, int horz, int vert) {
    int i, j;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_flip(), p argument is null\n");
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
        case EMB_ARC:{
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
        case EMB_LINE:{
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
        case EMB_CIRCLE:{
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
        case EMB_PATH:{
                EmbArray *point_list = g->object.path.pointList;
                for (j = 0; j < point_list->count; j++) {
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
        case EMB_POLYGON:{
                EmbArray *point_list = g->object.polygon.pointList;
                for (j = 0; j < point_list->count; j++) {
                    if (horz) {
                        point_list->geometry[i].object.point.position.x *= -1.0;
                    }
                    if (vert) {
                        point_list->geometry[i].object.point.position.y *= -1.0;
                    }
                }
                break;
            }
        case EMB_POLYLINE:{
                EmbArray *point_list = g->object.polygon.pointList;
                for (j = 0; j < point_list->count; j++) {
                    if (horz) {
                        point_list->geometry[j].object.point.position.x *= -1.0;
                    }
                    if (vert) {
                        point_list->geometry[j].object.point.position.y *= -1.0;
                    }
                }
                break;
            }
        case EMB_RECT:{
                if (horz) {
                    g->object.rect.x *= -1.0;
                    g->object.rect.y *= -1.0;
                }
                if (vert) {
                    g->object.rect.w *= -1.0;
                    g->object.rect.h *= -1.0;
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

/* a p
 */
void emb_combineJumpStitches(EmbPattern * p) {
    int jumpCount = 0, i;
    EmbArray *newList;
    EmbStitch j;

    if (!p) {
        printf("ERROR: emb-pattern.c emb_combineJumpStitches(), ");
        printf("p argument is null\n");
        return;
    }
    newList = emb_array_create(EMB_STITCH);
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
                emb_array_addStitch(newList, j);
            }
            emb_array_addStitch(newList, st);
        }
    }
    emb_array_free(p->stitch_list);
    p->stitch_list = newList;
}

/* \todo The params determine the max XY movement rather than the length.
 * They need renamed or clarified further.
 */
void emb_correctForMaxStitchLength(EmbPattern * p, EmbReal maxStitchLength,
                                    EmbReal maxJumpLength) {
    if (!p) {
        printf("ERROR: emb-pattern.c emb_correctForMaxStitchLength(), ");
        printf("p argument is null\n");
        return;
    }
    if (p->stitch_list->count > 1) {
        int i, j, splits;
        EmbReal maxXY, maxLen, addX, addY;
        EmbArray *newList = emb_array_create(EMB_STITCH);
        for (i = 1; i < p->stitch_list->count; i++) {
            EmbStitch st = p->stitch_list->stitch[i];
            EmbReal xx = st.x;
            EmbReal yy = st.y;
            EmbReal dx = p->stitch_list->stitch[i - 1].x - xx;
            EmbReal dy = p->stitch_list->stitch[i - 1].y - yy;
            if ((fabs(dx) > maxStitchLength)
                || (fabs(dy) > maxStitchLength)) {
                maxXY = EMB_MAX(fabs(dx), fabs(dy));
                if (st.flags & (JUMP | TRIM)) {
                    maxLen = maxJumpLength;
                } else {
                    maxLen = maxStitchLength;
                }
                splits = (int)ceil((EmbReal) maxXY / maxLen);

                if (splits > 1) {
                    addX = (EmbReal) dx / splits;
                    addY = (EmbReal) dy / splits;

                    for (j = 1; j < splits; j++) {
                        EmbStitch s;
                        s = st;
                        s.x = xx + addX * j;
                        s.y = yy + addY * j;
                        emb_array_addStitch(newList, s);
                    }
                }
            }
            emb_array_addStitch(newList, st);
        }
        emb_array_free(p->stitch_list);
        p->stitch_list = newList;
    }
    emb_end(p);
}

/* Center the pattern a p.
 */
void emb_center(EmbPattern * p) {
    /* TODO: review this. currently not used in anywhere.
       Also needs to handle various design objects */
    int moveLeft, moveTop, i;
    EmbRect boundingRect;
    if (!p) {
        printf("ERROR: emb-pattern.c emb_center(), p argument is null\n");
        return;
    }
    boundingRect = emb_bounds(p);

    moveLeft = (int)(boundingRect.x - boundingRect.w / 2.0);
    moveTop = (int)(boundingRect.y - boundingRect.h / 2.0);

    for (i = 0; i < p->stitch_list->count; i++) {
        p->stitch_list->stitch[i].x -= moveLeft;
        p->stitch_list->stitch[i].y -= moveTop;
    }
}

/* TODO: Description needed.
 */
void emb_loadExternalColorFile(EmbPattern * p, const int8_t * fileName) {
    int hasRead, stub_len, format;
    int8_t extractName[200];

    if (!p) {
        printf
            ("ERROR: emb-pattern.c emb_loadExternalColorFile(), p argument is null\n");
        return;
    }
    if (!fileName) {
        printf
            ("ERROR: emb-pattern.c emb_loadExternalColorFile(), fileName argument is null\n");
        return;
    }

    strcpy(extractName, fileName);
    format = emb_identify_format(fileName);
    stub_len = embstr_len(fileName) - embstr_len(formatTable[format].extension);
    extractName[stub_len] = 0;
    strcat(extractName, ".edr");
    hasRead = emb_read(p, extractName, EMB_FORMAT_EDR);
    if (!hasRead) {
        extractName[stub_len] = 0;
        strcat(extractName, ".rgb");
        hasRead = emb_read(p, extractName, EMB_FORMAT_RGB);
    }
    if (!hasRead) {
        extractName[stub_len] = 0;
        strcat(extractName, ".col");
        hasRead = emb_read(p, extractName, EMB_FORMAT_COL);
    }
    if (!hasRead) {
        extractName[stub_len] = 0;
        strcat(extractName, ".inf");
        hasRead = emb_read(p, extractName, EMB_FORMAT_INF);
    }
}

/* Frees all memory allocated in the pattern (a p).
 */
void emb_free(EmbPattern * p) {
    if (!p) {
        printf("ERROR: emb-pattern.c emb_free(), p argument is null\n");
        return;
    }
    emb_array_free(p->stitch_list);
    emb_array_free(p->thread_list);
    emb_array_free(p->geometry);
    safe_free(p);
}

/*
 */
void
 emb_add_geometry(EmbPattern * p, EmbGeometry g) {
    emb_array_add_geometry(p->geometry, g);
}

/* Adds a circle object to pattern (a p) with its center at the absolute
 * position (a cx,a cy) with a radius of (a r). Positive y is up.
 * Units are in millimeters.
 */
void
 emb_add_circle(EmbPattern * p, EmbCircle circle) {
    if (!p) {
        printf("ERROR: emb-pattern.c emb_add_circle(), p argument is null\n");
        return;
    }

    EmbGeometry g;
    g.object.circle = circle;
    g.type = EMB_CIRCLE;
    emb_array_add_geometry(p->geometry, g);
}

/* Adds an ellipse object to pattern (a p) with its center at the
 * absolute position (a cx,a cy) with radii of (a rx,a ry). Positive y is up.
 * Units are in millimeters.
 */
void
 emb_add_ellipse(EmbPattern * p, EmbEllipse ellipse) {
    if (!p) {
        printf
            ("ERROR: emb-pattern.c emb_addEllipseObjectAbs(), p argument is null\n");
        return;
    }

    emb_array_add_ellipse(p->geometry, ellipse);
}

/* Adds a line object to pattern (a p) starting at the absolute position
 * (a x1,a y1) and ending at the absolute position (a x2,a y2).
 * Positive y is up. Units are in millimeters.
 */
void
 emb_add_line(EmbPattern * p, EmbLine line) {
    if (!p) {
        printf
            ("ERROR: emb-pattern.c emb_addLineObjectAbs(), p argument is null\n");
        return;
    }

    emb_array_addLine(p->geometry, line);
}

/* .
 */
void
 emb_add_path(EmbPattern * p, EmbPath obj) {
    if (!p) {
        printf
            ("ERROR: emb-pattern.c emb_addPathObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj.pointList) {
        printf
            ("ERROR: emb-pattern.c emb_addPathObjectAbs(), obj->pointList is empty\n");
        return;
    }

    emb_array_addPath(p->geometry, obj);
}

/*! Adds a point object to pattern (a p) at the absolute position (a x,a y). Positive y is up. Units are in millimeters. */
void emb_addPointAbs(EmbPattern * p, EmbPoint obj) {
    if (!p) {
        printf
            ("ERROR: emb-pattern.c emb_addPointObjectAbs(), p argument is null\n");
        return;
    }

    emb_array_addPoint(p->geometry, obj);
}

void emb_addPolygonAbs(EmbPattern * p, EmbPolygon obj) {
    if (!p) {
        printf
            ("ERROR: emb-pattern.c emb_addPolygonObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj.pointList) {
        printf
            ("ERROR: emb-pattern.c emb_addPolygonObjectAbs(), obj->pointList is empty\n");
        return;
    }

    emb_array_addPolygon(p->geometry, obj);
}

void emb_addPolylineObjectAbs(EmbPattern * p, EmbPolyline obj) {
    if (!p) {
        printf
            ("ERROR: emb-pattern.c emb_addPolylineObjectAbs(), p argument is null\n");
        return;
    }
    if (!obj.pointList) {
        printf
            ("ERROR: emb-pattern.c emb_addPolylineObjectAbs(), obj->pointList is empty\n");
        return;
    }
    emb_array_addPolyline(p->geometry, obj);
}

/* Adds a rectangle object to pattern (a p) at the absolute position
 * (a x,a y) with a width of (a w) and a height of (a h).
 * Positive y is up. Units are in millimeters.
 */
void emb_addRectAbs(EmbPattern * p, EmbRect rect) {
    if (!p) {
        printf
            ("ERROR: emb-pattern.c emb_addRectObjectAbs(), p argument is null\n");
        return;
    }
    emb_array_addRect(p->geometry, rect);
}

/* . */
void emb_end(EmbPattern * p)
{
    if (p->stitch_list->count == 0) {
        return;
    }
    /* Check for an END stitch and add one if it is not present */
    if (p->stitch_list->stitch[p->stitch_list->count - 1].flags != END) {
        emb_add_stitch(p, 0, 0, END, 1);
    }
}

/*
 *
 */
int convert(const int8_t * inf, const int8_t * outf)
{
    EmbPattern *p = 0;
    int reader, writer;

    reader = emb_identify_format(inf);
    writer = emb_identify_format(outf);

    p = emb_create();
    if (!p) {
        printf("ERROR: convert(), cannot allocate memory for p\n");
        return 1;
    }

    if (!emb_read(p, inf, reader)) {
        printf("ERROR: convert(), reading file was unsuccessful: %s\n", inf);
        emb_free(p);
        return 1;
    }

    if (formatTable[reader].type == EMBFORMAT_OBJECTONLY) {
        if (formatTable[writer].type == EMBFORMAT_STITCHONLY) {
            emb_movePolylinesTostitch_list(p);
        }
    }

    if (!emb_write(p, outf, writer)) {
        printf("ERROR: convert(), writing file %s was unsuccessful\n", outf);
        emb_free(p);
        return 1;
    }

    emb_free(p);
    return 0;
}

/* The Pattern Properties
 */
int emb_color_count(EmbPattern *pattern, EmbColor startColor)
{
    int colors = 0, i;
    EmbColor color = startColor;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbColor newColor;
        EmbStitch st;

        st = pattern->stitch_list->stitch[i];

        newColor = pattern->thread_list->thread[st.color].color;
        if (embColor_distance(newColor, color) != 0) {
            colors++;
            color = newColor;
        } else if (st.flags & END || st.flags & STOP) {
            colors++;
        }

        while (pattern->stitch_list->stitch[i + 1].flags == st.flags) {
            i++;
            if (i >= pattern->stitch_list->count - 2) {
                break;
            }
        }
    }
    return colors;
}

/*
 * Print out pattern details.
 */
void emb_details(EmbPattern *pattern)
{
    int colors, num_stitches, real_stitches, jump_stitches, trim_stitches;
    int unknown_stitches;
    EmbRect bounds;
    float thread_usage;
    float minimum_length;
    float maximum_length;

    // colors = emb_color_count(pattern);
    colors = 1;
    num_stitches = pattern->stitch_list->count;
    real_stitches = emb_real_stitches(pattern);
    jump_stitches = emb_jump_stitches(pattern);
    trim_stitches = emb_trim_stitches(pattern);
    unknown_stitches = 0;       // emb_unknown_stitches(pattern);
    bounds = emb_bounds(pattern);
    thread_usage = emb_total_thread_length(pattern);
    minimum_length = emb_shortest_stitch(pattern);
    maximum_length = emb_longest_stitch(pattern);

    /* Print Report */
    printf("Design Details\n");
    printf("--------------\n");
    printf("real_stitches: %d\n", real_stitches);
    printf("trim_stitches: %d\n", trim_stitches);
    printf("unknown_stitches: %d\n", unknown_stitches);
    printf("total_stitches: %d\n", num_stitches);
    printf("num_colors: %d\n", pattern->thread_list->count);

    printf("Total thread usage: %f mm\n", thread_usage);
    printf("Shortest stitch: %f mm\n", minimum_length);
    printf("Longest stitch: %f mm\n", maximum_length);

    printf("Stitches: %d\n", num_stitches);
    printf("Colors: %d\n", colors);
    printf("Jumps: %d\n", jump_stitches);

    printf("Top: %f mm\n", bounds.y);
    printf("Left: %f mm\n", bounds.x);
    printf("Bottom: %f mm\n", bounds.h + bounds.y);
    printf("Right: %f mm\n", bounds.w + bounds.x);
    printf("Width: %f mm\n", bounds.w);
    printf("Height: %f mm\n", bounds.h);
    printf("\n");

    /*
       EmbReal minx = 0.0, maxx = 0.0, miny = 0.0, maxy = 0.0;
       int number_of_minlength_stitches = 0;
       int number_of_maxlength_stitches = 0;

       EmbReal xx = 0.0, yy = 0.0;
       EmbReal length = 0.0;

       if (num_stitches == 0) {
       QMessageBox::warning(this, tr("No Design Loaded"), tr("<b>A design needs to be loaded or created before details can be determined.</b>"));
       return;
       }
       QVector<EmbReal> stitchLengths;

       EmbReal binSize = max_stitchlength / NUMBINS;

       QString str;
       int i;
       for (i = 0; i < NUMBINS; i++) {
       str += QString::number(binSize * (i), 'f', 1) + " - " + QString::number(binSize * (i+1), 'f', 1) + " mm: " +  QString::number(bin[i]) + "\n\n";
       }

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

/* . */
void emb_print(EmbPattern *pattern)
{
    EmbArray *sts = pattern->stitch_list;
    int i;
    for (i = 0; i < sts->count; i++) {
        printf("%d: %f %f %d\n",
               i, sts->stitch[i].x, sts->stitch[i].y, sts->stitch[i].flags);
    }
}

void emb_lengthHistogram(EmbPattern *pattern, int *bin, int NUMBINS)
{
    int i;
    float max_stitch_length = emb_longest_stitch(pattern);
    EmbArray *sts = pattern->stitch_list;
    for (i = 0; i <= NUMBINS; i++) {
        bin[i] = 0;
    }

    for (i = 1; i < sts->count; i++) {
        EmbStitch st_prev = sts->stitch[i - 1];
        EmbStitch st = sts->stitch[i];
        if ((st.flags == NORMAL) & (st_prev.flags == NORMAL)) {
            float length = emb_stitch_length(st_prev, st);
            bin[(int)
                (floor(NUMBINS * length / max_stitch_length))]++;
        }
    }
}

int emb_real_stitches(EmbPattern *pattern)
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

int emb_jump_stitches(EmbPattern *pattern)
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

int emb_trim_stitches(EmbPattern *pattern)
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

/* Get the position as a vector from the stitch. */
EmbVector emb_st_pos(EmbStitch st)
{
    return emb_vector(st.x, st.y);
}

/* Length of stitch starting of "prev_st" and ending at "st". */
double emb_stitch_length(EmbStitch prev_st, EmbStitch st)
{
    EmbVector pos = emb_st_pos(st);
    EmbVector prev_pos = emb_st_pos(prev_st);
    double length = emb_vector_distance(pos, prev_pos);
    return length;
}

/* Returns the number of real stitches in a pattern.
 * We consider SEQUIN to be a real stitch in this count.
 */
int emb_real_count(EmbPattern *pattern)
{
    int i;
    int total = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        if (!(st.flags & (JUMP | TRIM))) {
            total++;
        }
    }
    return total;
}

/* The length of the longest stitch in the pattern. */
EmbReal emb_longest_stitch(EmbPattern *pattern)
{
    if (pattern->stitch_list->count < 2) {
        return 0.0;
    }

    int i;
    EmbReal max_stitch = 0.0;
    EmbStitch prev_st = pattern->stitch_list->stitch[0];
    for (i = 1; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
            double length = emb_stitch_length(st, prev_st);
            if (length > max_stitch) {
                max_stitch = length;
            }
        }
        prev_st = st;
    }
    return max_stitch;
}

/* The length of the shortest stitch in the pattern. */
EmbReal emb_shortest_stitch(EmbPattern *pattern)
{
    if (pattern->stitch_list->count < 2) {
        return 0.0;
    }

    int i;
    EmbReal min_stitch = 1.0e10;
    EmbStitch prev_st = pattern->stitch_list->stitch[0];
    for (i = 1; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
            double length = emb_stitch_length(st, prev_st);
            if (length < min_stitch) {
                min_stitch = length;
            }
        }
        prev_st = st;
    }
    return min_stitch;
}

/* Returns the number of stitches in a pattern that are of any of the types
 * or-ed together in "flag". For example to count the total number of
 * TRIM and STOP stitches use:
 *
 *     emb_count_type(pattern, TRIM | STOP);
 */
int emb_count_type(EmbPattern *pattern, int flag)
{
    int i;
    int total = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        if (st.flags & flag) {
            total++;
        }
    }
    return total;
}

/* . */
void emb_length_histogram(EmbPattern *pattern, int *bins)
{
    if (pattern->stitch_list->count < 2) {
        return;
    }

    int i;
    for (i = 0; i <= NUMBINS; i++) {
        bins[i] = 0;
    }

    double max_stitchlength = emb_longest_stitch(pattern);
    EmbStitch prev_st = pattern->stitch_list->stitch[0];
    for (i = 1; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
            double length = emb_stitch_length(st, prev_st);
            int bin_number = (int)floor(NUMBINS * length / max_stitchlength);
            bins[bin_number]++;
        }
        prev_st = st;
    }
}

/* . */
void emb_color_histogram(EmbPattern *pattern, int **bins)
{
    if (pattern->stitch_list->count < 2) {
        return;
    }

    int i, j;
    for (j = 0; j < pattern->thread_list->count; j++)
        for (i = 0; i <= NUMBINS; i++) {
            bins[j][i] = 0;
        }

    double max_stitchlength = emb_longest_stitch(pattern);
    EmbStitch prev_st = pattern->stitch_list->stitch[0];
    for (i = 1; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* Can't count first normal stitch. */
        if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
            double length = emb_stitch_length(st, prev_st);
            int bin_number = (int)floor(NUMBINS * length / max_stitchlength);
            bins[0][bin_number]++;
        }
        prev_st = st;
    }
}

/* . */
double emb_total_thread_length(EmbPattern *pattern)
{
    if (pattern->stitch_list->count < 2) {
        return 0.0;
    }

    int i;
    double total = 0.0;
    EmbStitch prev_st = pattern->stitch_list->stitch[0];
    for (i = 1; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* Can't count first normal stitch. */
        if (st.flags == NORMAL) {
            total += emb_stitch_length(st, prev_st);
        }
        prev_st = st;
    }
    return total;
}

/* FIXME. */
double emb_total_thread_of_color(EmbPattern *pattern, int thread_index)
{
    if (pattern->stitch_list->count < 2) {
        return 0.0;
    }

    int i;
    double total = 0.0;
    EmbStitch prev_st = pattern->stitch_list->stitch[0];
    for (i = 1; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* Can't count first normal stitch. */
        if (st.color == thread_index)
            if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
                total += emb_stitch_length(st, prev_st);
            }
        prev_st = st;
    }
    return total;
}
