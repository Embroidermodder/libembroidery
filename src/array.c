/*
 * This file is part of libembroidery.
 *
 * Copyright 2018-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * ---------------------------------------------------------
 *
 * The array management for libembroidery's arrays.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "embroidery_internal.h"

EmbArray*
embArray_create(int type)
{
    int i;
    EmbArray *a;
    a = (EmbArray*)malloc(sizeof(EmbArray));
    a->type = type;
    a->length = CHUNK_SIZE;
    a->count = 0;
    switch (type) {
    case EMB_STITCH:
        a->stitch = (EmbStitch*)malloc(CHUNK_SIZE*sizeof(EmbStitch));
        break;
    case EMB_THREAD:
        a->thread = (EmbThread*)malloc(CHUNK_SIZE*sizeof(EmbThread));
        break;
    default:
        a->geometry = (EmbGeometry*)malloc(CHUNK_SIZE*sizeof(EmbGeometry));
        break;
    }
    return a;
}

int
embArray_resize(EmbArray *a)
{
    int i;
    if (a->count < a->length) {
        return 1;
    }
    a->length += CHUNK_SIZE;
    a->geometry = (EmbGeometry *)realloc(a->geometry, a->length*sizeof(EmbGeometry));
    if (!a->geometry) {
        /* TODO: Error reporting */
        return 0;
    }
    return 1;
}

void embArray_copy(EmbArray *dst, EmbArray *src)
{
    dst = embArray_create(src->type);
    dst->length = src->length;
    dst->count = src->count;
    embArray_resize(dst);
    /* BUG: Potential failure to copy path memory, only copy pointers? */

    switch (dst->type) {
    case EMB_STITCH:
        memcpy(dst->stitch, src->stitch, sizeof(EmbStitch)*src->count);
        break;
    case EMB_THREAD:
        memcpy(dst->thread, src->thread, sizeof(EmbThread)*src->count);
        break;
    default:
        memcpy(dst->geometry, src->geometry, sizeof(EmbGeometry)*src->count);
        break;
    }
}

int
embArray_addArc(EmbArray *a, EmbArc b)
{
    a->count++;
    if (!embArray_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.arc = b;
    a->geometry[a->count - 1].type = EMB_ARC;
    return 1;
}

int
embArray_addCircle(EmbArray *a, EmbCircle b)
{
    a->count++;
    if (!embArray_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.circle = b;
    a->geometry[a->count - 1].type = EMB_CIRCLE;
    return 1;
}

int
embArray_addEllipse(EmbArray *a, EmbEllipse b)
{
    a->count++;
    if (!embArray_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.ellipse = b;
    a->geometry[a->count - 1].type = EMB_ELLIPSE;
    return 1;
}

int
embArray_addFlag(EmbArray *a, EmbFlag b)
{
    a->count++;
    if (!embArray_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].flag = b;
    a->geometry[a->count - 1].type = EMB_FLAG;
    return 1;
}

int
embArray_addLine(EmbArray *a, EmbLine b)
{
    a->count++;
    if (!embArray_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.line = b;
    a->geometry[a->count - 1].type = EMB_LINE;
    return 1;
}

int
embArray_addPath(EmbArray *a, EmbPath b)
{
    a->count++;
    if (!embArray_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.path.pointList = embArray_create(EMB_POINT);
    if (!a->geometry[a->count - 1].object.path.pointList) {
        /* TODO: Error reporting */
        return 0;
    }
    a->geometry[a->count - 1].type = EMB_PATH;
    return 1;
}

int
embArray_addPoint(EmbArray *a, EmbPoint b)
{
    a->count++;
    if (!embArray_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.point = b;
    a->geometry[a->count - 1].type = EMB_POINT;
    return 1;
}

int
embArray_addPolyline(EmbArray *a, EmbPolyline b)
{
    a->count++;
    if (!embArray_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.polyline.pointList = embArray_create(EMB_POINT);
    if (!a->geometry[a->count - 1].object.polyline.pointList) {
        /* TODO: Error reporting */
        return 0;
    }
    a->geometry[a->count - 1].type = EMB_POLYLINE;
    return 1;
}

int
embArray_addPolygon(EmbArray *a, EmbPolygon b)
{
    a->count++;
    if (!embArray_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.polygon.pointList = embArray_create(EMB_POINT);
    if (!a->geometry[a->count - 1].object.polygon.pointList) {
        /* TODO: Error reporting */
        return 0;
    }
    a->geometry[a->count - 1].type = EMB_POLYGON;
    return 1;
}

int
embArray_addRect(EmbArray *a, EmbRect b)
{
    a->count++;
    if (!embArray_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.rect = b;
    a->geometry[a->count - 1].type = EMB_RECT;
    return 1;
}

int
embArray_addStitch(EmbArray *a, EmbStitch b)
{
    a->count++;
    if (!embArray_resize(a)) {
        return 0;
    }
    a->stitch[a->count - 1] = b;
    return 1;
}

int
embArray_addVector(EmbArray *a, EmbVector b)
{
    a->count++;
    if (!embArray_resize(a)) {
        return 0;
    }
    a->geometry[a->count - 1].object.vector = b;
    a->geometry[a->count - 1].type = EMB_VECTOR;
    return 1;
}

void
embArray_free(EmbArray* a)
{
    int i;
    if (!a) {
        return;
    }
    switch (a->type) {
    case EMB_STITCH:
        free(a->stitch);
        break;
    case EMB_THREAD:
        free(a->thread);
        break;
    default:
        for (i = 0; i < a->count; i++) {
            EmbGeometry g = a->geometry[i];
            switch (a->geometry[i].type) {
            case EMB_PATH: {
                embArray_free(g.object.path.pointList);
                break;
            }
            case EMB_POLYGON: {
                embArray_free(g.object.polygon.pointList);
                break;
            }
            case EMB_POLYLINE: {
                embArray_free(g.object.polyline.pointList);
                break;
            }
            default:
                break;
            }
        }
        free(a->geometry);
        break;
    }
    free(a);
}

