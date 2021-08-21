#include "embroidery.h"
#include <stdlib.h>

int embArray_create(EmbArray *p, int type)
{
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
    default:
        break;
    }
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
        embLog_error("emb-polygon.c embArray_create(), cannot allocate memory for heapPolygonObj\n");
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
        embLog_error("emb-polygon.c embArray_create(), cannot allocate memory for heapPolygonObj\n");
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
        embLog_error("emb-polyline.c embArray_create(), cannot allocate memory for heapPolylineObj\n");
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
    default:
        break;
    }
    p = 0;
}

EmbVectorArray *embVectorArray_create()
{
    EmbVectorArray *p;
    p->length = CHUNK_SIZE;
    p->count = 0;
    p->vector = (EmbVector*)malloc(CHUNK_SIZE*sizeof(EmbVector));
    if (!p->vector) return 0;
    return p;
}

int embVectorArray_add(EmbVectorArray *p, EmbVector v)
{
    p->count++;
    if (p->count < p->length) {
        p->length += CHUNK_SIZE;
        p->vector = (EmbVector*)realloc(p->vector, p->length*sizeof(EmbVector));
        if (!p->vector) return 0;
    }
    p->vector[p->count] = v;
    return 1;

}

void embVectorArray_free(EmbVectorArray* p)
{
    free(p->vector);
}

