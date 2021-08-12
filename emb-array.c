#include "embroidery.h"
#include <stdlib.h>

int embGeometryArray_create(EmbGeometryArray *p, int type)
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
    case EMB_POINT:
        p->point = (EmbPointObject*)malloc(CHUNK_SIZE*sizeof(EmbPointObject));
        break;
    case EMB_LINE:
        p->line = (EmbLineObject*)malloc(CHUNK_SIZE*sizeof(EmbLineObject));
        break;
    case EMB_POLYGON:
        p->polygon = (EmbPolygonObject*)malloc(CHUNK_SIZE*sizeof(EmbPolygonObject));
        break;
    case EMB_POLYLINE:
        p->polyline = (EmbPolylineObject*)malloc(CHUNK_SIZE*sizeof(EmbPolylineObject));
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

int embGeometryArray_resize(EmbGeometryArray *p)
{
    if (p->count < p->length) return 1;
    p->length += CHUNK_SIZE;
    switch (p->type) {
    case EMB_ARC:
        if (realloc(p->arc, p->length*sizeof(EmbArcObject))) return 1;
        break;
    case EMB_CIRCLE:
        if (realloc(p->circle, p->length*sizeof(EmbCircleObject))) return 1;
        break;
    case EMB_ELLIPSE:
        if (realloc(p->ellipse, p->length*sizeof(EmbEllipseObject))) return 1;
        break;
    case EMB_POINT:
        if (realloc(p->point, p->length*sizeof(EmbPointObject))) return 1;
        break;
    case EMB_LINE:
        if (realloc(p->line, p->length*sizeof(EmbLineObject))) return 1;
        break;
    case EMB_POLYGON:
        if (realloc(p->polygon, p->length*sizeof(EmbPolygonObject))) return 1;
        break;
    case EMB_POLYLINE:
        if (realloc(p->polyline, p->length*sizeof(EmbPolylineObject))) return 1;
        break;
    case EMB_RECT:
        if (realloc(p->rect, p->length*sizeof(EmbRectObject))) return 1;
        break;
    case EMB_SPLINE:
        if (realloc(p->spline, p->length*sizeof(EmbSplineObject))) return 1;
    default:
        break;    
    }
    return 0;
}

int embGeometryArray_addArc(EmbGeometryArray* p, EmbArc arc, int lineType, EmbColor color)
{
    p->count++;
    if (!embGeometryArray_resize(p)) return 0;
    p->arc[p->count].arc = arc;
    p->arc[p->count].lineType = lineType;
    p->arc[p->count].color = color;
    return 1;
}

int embGeometryArray_addCircle(EmbGeometryArray* p, EmbCircle circle, int lineType, EmbColor color)
{
    p->count++;
    if (!embGeometryArray_resize(p)) return 0;
    p->circle[p->count].circle = circle;
    p->circle[p->count].lineType = lineType;
    p->circle[p->count].color = color;
    return 1;
}

void embGeometryArray_free(EmbGeometryArray* p)
{
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
    case EMB_POINT:
        free(p->point);
        break;
    case EMB_LINE:
        free(p->line);
        break;
    case EMB_POLYGON:
        free(p->polygon);
        break;
    case EMB_POLYLINE:
        free(p->polyline);
        break;
    case EMB_RECT:
        free(p->rect);
        break;
    case EMB_SPLINE:
        free(p->spline);
    default:
        break;    
    }
}

