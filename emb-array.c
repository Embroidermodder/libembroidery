EmbArray* embArray_create(int type)
{
    EmbArray* p;
    p = (EmbArray*)malloc(sizeof(EmbArray));
    p->type = type;
    p->length = CHUNK_SIZE;
    p->count = 0;
    switch (p->type) {
    case EMB_ARC:
        p->arc = (EmbArc*)malloc(CHUNK_SIZE * sizeof(EmbArc));
        break;
    case EMB_CIRCLE:
        p->circle = (EmbCircle*)malloc(CHUNK_SIZE * sizeof(EmbCircle));
        break;
    case EMB_ELLIPSE:
        p->ellipse = (EmbEllipse*)malloc(CHUNK_SIZE * sizeof(EmbEllipse));
        break;
    case EMB_FLAG:
        p->flag = (int*)malloc(CHUNK_SIZE * sizeof(int));
        break;
    case EMB_PATH:
        p->path = (EmbPathObject**)malloc(CHUNK_SIZE * sizeof(EmbPathObject*));
        break;
    case EMB_POINT:
        p->point = (EmbVector*)malloc(CHUNK_SIZE * sizeof(EmbVector));
        break;
    case EMB_LINE:
        p->line = (EmbLine*)malloc(CHUNK_SIZE * sizeof(EmbLine));
        break;
    case EMB_POLYGON:
        p->polygon = (EmbPolygonObject**)malloc(CHUNK_SIZE * sizeof(EmbPolygonObject*));
        break;
    case EMB_POLYLINE:
        p->polyline = (EmbPolylineObject**)malloc(CHUNK_SIZE * sizeof(EmbPolylineObject*));
        break;
    case EMB_RECT:
        p->rect = (EmbRect*)malloc(CHUNK_SIZE * sizeof(EmbRect));
        break;
    case EMB_SPLINE:
        p->spline = (EmbSplineObject*)malloc(CHUNK_SIZE * sizeof(EmbSplineObject));
        break;
    case EMB_STITCH:
        p->stitch = (EmbStitch*)malloc(CHUNK_SIZE * sizeof(EmbStitch));
        break;
    case EMB_THREAD:
        p->thread = (EmbThread*)malloc(CHUNK_SIZE * sizeof(EmbThread));
        break;
    case EMB_VECTOR:
        p->vector = (EmbVector*)malloc(CHUNK_SIZE * sizeof(EmbVector));
        break;
    default:
        break;
    }
    switch (p->type) {
    case EMB_ARC:
    case EMB_CIRCLE:
    case EMB_POINT:
    case EMB_LINE:
    case EMB_RECT:
        p->color = (EmbColor*)malloc(CHUNK_SIZE * sizeof(EmbColor));
        if (!p->color)
            return 0;
        p->flag = (int*)malloc(CHUNK_SIZE * sizeof(int));
        if (!p->flag)
            return 0;
        break;
    case EMB_ELLIPSE:
        p->color = (EmbColor*)malloc(CHUNK_SIZE * sizeof(EmbColor));
        if (!p->color)
            return 0;
        p->flag = (int*)malloc(CHUNK_SIZE * sizeof(int));
        if (!p->flag)
            return 0;
        p->floats = (float*)malloc(CHUNK_SIZE * sizeof(float));
        if (!p->floats)
            return 0;
        break;
    default:
        break;
    }
    return p;
}

int embArray_resize(EmbArray* p)
{
    if (p->count < p->length)
        return 1;
    p->length += CHUNK_SIZE;
    switch (p->type) {
    case EMB_ARC:
        p->arc = realloc(p->arc, p->length * sizeof(EmbArc));
        if (!p->arc)
            return 1;
        break;
    case EMB_CIRCLE:
        p->circle = realloc(p->circle, p->length * sizeof(EmbCircle));
        if (!p->circle)
            return 1;
        break;
    case EMB_ELLIPSE:
        p->ellipse = realloc(p->ellipse, p->length * sizeof(EmbEllipse));
        if (!p->ellipse)
            return 1;
        break;
    case EMB_FLAG:
        p->flag = realloc(p->flag, p->length * sizeof(int));
        if (!p->flag)
            return 1;
        break;
    case EMB_PATH:
        p->path = realloc(p->path, p->length * sizeof(EmbPathObject*));
        if (!p->path)
            return 1;
        break;
    case EMB_POINT:
        p->point = realloc(p->point, p->length * sizeof(EmbVector));
        if (!p->point)
            return 1;
        break;
    case EMB_LINE:
        p->line = realloc(p->line, p->length * sizeof(EmbLine));
        if (!p->line)
            return 1;
        break;
    case EMB_POLYGON:
        p->polygon = realloc(p->polygon, p->length * sizeof(EmbPolygonObject*));
        if (!p->polygon)
            return 1;
        break;
    case EMB_POLYLINE:
        p->polyline = realloc(p->polyline, p->length * sizeof(EmbPolylineObject*));
        if (!p->polyline)
            return 1;
        break;
    case EMB_RECT:
        p->rect = realloc(p->rect, p->length * sizeof(EmbRect));
        if (!p->rect)
            return 1;
        break;
    case EMB_SPLINE:
        p->spline = realloc(p->spline, p->length * sizeof(EmbSplineObject));
        if (!p->spline)
            return 1;
        break;
    case EMB_STITCH:
        p->stitch = realloc(p->stitch, CHUNK_SIZE * sizeof(EmbStitch));
        if (!p->stitch)
            return 1;
        break;
    case EMB_THREAD:
        p->thread = realloc(p->thread, CHUNK_SIZE * sizeof(EmbThread));
        if (!p->thread)
            return 1;
        break;
    case EMB_VECTOR:
        p->vector = realloc(p->vector, CHUNK_SIZE * sizeof(EmbVector));
        if (!p->vector)
            return 1;
        break;
    default:
        break;
    }
    switch (p->type) {
    case EMB_ARC:
    case EMB_CIRCLE:
    case EMB_POINT:
    case EMB_LINE:
    case EMB_RECT:
        p->color = realloc(p->color, p->length * sizeof(EmbColor));
        if (!p->color)
            return 1;
        p->flag = realloc(p->flag, p->length * sizeof(int));
        if (!p->flag)
            return 1;
        break;
    case EMB_ELLIPSE:
        p->color = realloc(p->color, p->length * sizeof(EmbColor));
        if (!p->color)
            return 1;
        p->flag = realloc(p->flag, p->length * sizeof(int));
        if (!p->flag)
            return 1;
        p->floats = realloc(p->floats, p->length * sizeof(float));
        if (!p->floats)
            return 1;
        break;
    default:
        break;
    }
    return 0;
}

int embArray_addArc(EmbArray* p, EmbArc arc, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->arc[p->count - 1] = arc;
    p->flag[p->count - 1] = lineType;
    p->color[p->count - 1] = color;
    return 1;
}

int embArray_addCircle(EmbArray* p, EmbCircle circle, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->circle[p->count - 1] = circle;
    p->flag[p->count - 1] = lineType;
    p->color[p->count - 1] = color;
    return 1;
}

int embArray_addEllipse(EmbArray* p,
    EmbEllipse ellipse, float rotation, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->ellipse[p->count - 1] = ellipse;
    p->floats[p->count - 1] = rotation;
    p->flag[p->count - 1] = lineType;
    p->color[p->count - 1] = color;
    return 1;
}

int embArray_addFlag(EmbArray* p, int flag)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->flag[p->count - 1] = flag;
    return 1;
}

int embArray_addLine(EmbArray* p, EmbLine line, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->line[p->count - 1] = line;
    p->flag[p->count - 1] = lineType;
    p->color[p->count - 1] = color;
    return 1;
}

int embArray_addPath(EmbArray* p, EmbPathObject* path)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->path[p->count - 1] = (EmbPathObject*)malloc(sizeof(EmbPathObject));
    if (!p->path[p->count - 1]) {
        embLog("ERROR: emb-polygon.c embArray_create(), cannot allocate memory for heapPolygonObj\n");
        return 0;
    }
    p->path[p->count - 1] = path;
    return 1;
}

int embArray_addPoint(EmbArray* p, EmbVector point, int lineType, EmbColor color)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->point[p->count - 1] = point;
    p->flag[p->count - 1] = lineType;
    p->color[p->count - 1] = color;
    return 1;
}

int embArray_addPolygon(EmbArray* p, EmbPolygonObject* polygon)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->polygon[p->count - 1] = (EmbPolygonObject*)malloc(sizeof(EmbPolygonObject));
    if (!p->polygon[p->count - 1]) {
        embLog("ERROR: emb-polygon.c embArray_create(), cannot allocate memory for heapPolygonObj\n");
        return 0;
    }
    p->polygon[p->count - 1] = polygon;
    return 1;
}

int embArray_addPolyline(EmbArray* p, EmbPolylineObject* polyline)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->polyline[p->count - 1] = (EmbPolylineObject*)malloc(sizeof(EmbPolylineObject));
    if (!p->polyline[p->count - 1]) {
        embLog("ERROR: emb-polyline.c embArray_create(), cannot allocate memory for heapPolylineObj\n");
        return 0;
    }
    p->polyline[p->count - 1] = polyline;
    return 1;
}

int embArray_addRect(EmbArray* p,
    EmbRect rect, int lineType, EmbColor color)
{
    if (!p) {
        p = embArray_create(EMB_RECT);
        if (!p) {
            return 0;
        }
    }

    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->rect[p->count - 1] = rect;
    p->flag[p->count - 1] = lineType;
    p->color[p->count - 1] = color;
    return 1;
}

int embArray_addStitch(EmbArray* p, EmbStitch st)
{
    if (!p) {
        p = embArray_create(EMB_STITCH);
        if (!p) {
            return 0;
        }
    }
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->stitch[p->count - 1] = st;
    return 1;
}

int embArray_addThread(EmbArray* p, EmbThread thread)
{
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->thread[p->count - 1] = thread;
    return 1;
}

int embArray_addVector(EmbArray* p, EmbVector vector)
{
    if (!p) {
        p = embArray_create(EMB_VECTOR);
        if (!p) {
            return 0;
        }
    }
    p->count++;
    if (!embArray_resize(p))
        return 0;
    p->vector[p->count - 1] = vector;
    return 1;
}

void embArray_free(EmbArray* p)
{
    int i;
    if (!p)
        return;

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
        for (i = 0; i < p->count; i++) {
            embArray_free(p->path[i]->pointList);
        }
        free(p->path);
        break;
    case EMB_POINT:
        free(p->point);
        break;
    case EMB_POLYGON:
        for (i = 0; i < p->count; i++) {
            embArray_free(p->polygon[i]->pointList);
        }
        free(p->polygon);
        break;
    case EMB_POLYLINE:
        for (i = 0; i < p->count; i++) {
            embArray_free(p->polyline[i]->pointList);
        }
        free(p->polyline);
        break;
    case EMB_RECT:
        free(p->rect);
        break;
    case EMB_SPLINE:
        free(p->spline);
        break;
    case EMB_STITCH:
        free(p->stitch);
        break;
    case EMB_THREAD:
        free(p->thread);
        break;
    case EMB_VECTOR:
        free(p->vector);
        break;
    default:
        break;
    }
    switch (p->type) {
    case EMB_ARC:
    case EMB_CIRCLE:
    case EMB_POINT:
    case EMB_LINE:
    case EMB_RECT:
        free(p->color);
        free(p->flag);
        break;
    case EMB_ELLIPSE:
        free(p->color);
        free(p->flag);
        free(p->floats);
    default:
        break;
    }
    free(p);
}

