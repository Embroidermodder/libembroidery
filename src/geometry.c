/**
 * @file unsorted.c
 */

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <limits.h>

#include "embroidery.h"

/*
 * Script section
 */

static EmbPattern *focussed_pattern = NULL;

/* . */
bool valid_rgb(float r, float g, float b)
{
    if (isnan(r)) {
        return false;
    }
    if (isnan(g)) {
        return false;
    }
    if (isnan(b)) {
        return false;
    }
    if (r < 0 || r > 255) {
        return false;
    }
    if (g < 0 || g > 255) {
        return false;
    }
    if (b < 0 || b > 255) {
        return false;
    }
    return true;
}

/* This version of string_array_length does not protect against the END_SYMBOL
 * missing, because it is only to be used for compiled in constant tables.
 *
 * For string tables edited during run time, the END_SYMBOL is checked for during loops.
 */
int table_length(char *s[])
{
    int i;
    for (i = 0; i < 1000; i++) {
        if (s[i][0] == END_SYMBOL[0]) {
            if (!strncmp(s[i], END_SYMBOL, MAX_STRING_LENGTH)) {
                break;
            }
        }
    }
    if (i == 1000) {
        puts("ERROR: Table is missing END_SYMBOL.");
        return 1000;
    }
    return i;
}

/* . */
uint8_t *load_file(char *fname)
{
    FILE *f = fopen(fname, "r");
    if (!f) {
        printf("ERROR: Failed to open \"%s\".\n", fname);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    size_t length = ftell(f);
    uint8_t *data = malloc(length + 1);
    fseek(f, 0, SEEK_SET);
    if (!read_n_bytes(f, data, length)) {
        fclose(f);
        return NULL;
    }
    fclose(f);
    return data;
}

/* . */
bool int32_underflow(int64_t a, int64_t b)
{
    int64_t c;
    assert(LLONG_MAX > INT_MAX);
    c = (int64_t) a - b;
    if (c < INT_MIN || c > INT_MAX) {
        return true;
    }
    return false;
}

/* . */
bool int32_overflow(int64_t a, int64_t b)
{
    int64_t c;
    assert(LLONG_MAX > INT_MAX);
    c = (int64_t) a + b;
    if (c < INT_MIN || c > INT_MAX) {
        return true;
    }
    return false;
}

/* . */
int round_to_multiple(bool roundUp, int numToRound, int multiple)
{
    if (multiple == 0) {
        return numToRound;
    }
    int remainder = numToRound % multiple;
    if (remainder == 0) {
        return numToRound;
    }

    if (numToRound < 0 && roundUp) {
        return numToRound - remainder;
    }
    if (roundUp) {
        return numToRound + multiple - remainder;
    }
    /* else round down */
    if (numToRound < 0 && !roundUp) {
        return numToRound - multiple - remainder;
    }
    return numToRound - remainder;
}

/* Formats each message with a timestamp. */
void debug_message(const int8_t *msg, ...)
{
    int8_t buffer[MAX_STRING_LENGTH], fname[MAX_STRING_LENGTH];
    time_t t;
    struct tm *tm_info;
    sprintf(fname, "debug.log");
    FILE *f = fopen(fname, "a");
    if (!f) {
        printf("Failed to write to debug.log.");
        return;
    }
    t = time(NULL);
    tm_info = localtime(&t);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(f, "%s ", buffer);

    va_list args;
    va_start(args, msg);
    vfprintf(f, msg, args);
    va_end(args);

    fprintf(f, "\n");
    fclose(f);
}

/* . */
bool valid_file_format(char *fileName)
{
    if (emb_identify_format(fileName) >= 0) {
        return true;
    }
    return false;
}

/*
 * Libembroidery 1.0.0-alpha
 * https://www.libembroidery.org
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright 2018-2025 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * -----------------------------------------------------------------------------
 *
 * Only uses source from this directory or standard C libraries,
 * not including POSIX headers like unistd since this library
 * needs to support non-POSIX systems like Windows.
 *
 * -----------------------------------------------------------------------------
 *
 * The Geometry System
 */

const int8_t *justify_options[] = {
    "Left",
    "Center",
    "Right",
    "Aligned",
    "Middle",
    "Fit",
    "Top Left",
    "Top Center",
    "Top Right",
    "Middle Left",
    "Middle Center",
    "Middle Right",
    "Bottom Left",
    "Bottom Center",
    "Bottom Right",
    END_SYMBOL
};

const int8_t *emb_error_desc[] = {
    "No error.",
    "Wrong type: this is unsupported usage.",
    "Division by zero.",
    "Unfinished."
};

/* Translate a geometric object by the vector "delta". */
void emb_geometry_move(EmbGeometry *obj, EmbVector delta)
{
    switch (obj->type) {
    case EMB_ARC:{
            EmbArc *arc = &(obj->object.arc);
            arc->start = emb_vector_add(arc->start, delta);
            arc->mid = emb_vector_add(arc->mid, delta);
            arc->end = emb_vector_add(arc->end, delta);
            return;
        }
    case EMB_CIRCLE:{
            EmbCircle *circle = &(obj->object.circle);
            circle->center = emb_vector_add(circle->center, delta);
            return;
        }
    default:
        break;
    }
}


/* . */
EmbReal emb_apothem(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    case EMB_ARC:{
            *error = EMB_NO_ERR;
            EmbReal radius = emb_radius(g, error);
            if (*error) {
                return 0.0;
            }
            EmbReal sagitta = emb_sagitta(g, error);
            if (*error) {
                return 0.0;
            }
            return fabs(radius - sagitta);
        }
    default:
        *error = EMB_WRONG_TYPE_ERR;
        break;
    }
    return 0.0;
}

/* FIXME */
EmbReal emb_sagitta(EmbGeometry *g, EmbError *error)
{
    *error = EMB_UNFINISHED_ERR;
    return 0.0;
}

/* FIXME */
EmbVector emb_start(EmbGeometry *g, EmbError *error)
{
    *error = EMB_UNFINISHED_ERR;
    return emb_vector(0.0, 0.0);
}

/* FIXME */
EmbVector emb_end_point(EmbGeometry *g, EmbError *error)
{
    *error = EMB_UNFINISHED_ERR;
    return emb_vector(0.0, 0.0);
}

/* FIXME */
EmbReal emb_width(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    switch (g->type) {
    case EMB_CIRCLE:{
            return 2.0f * g->object.circle.radius;
        }
    case EMB_ELLIPSE:{
            return 2.0f * g->object.ellipse.radius.x;
        }
    default:
        *error = EMB_WRONG_TYPE_ERR;
        break;
    }
    return 1.0;
}

/* FIXME: finish all types. */
EmbReal emb_height(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    switch (g->type) {
    case EMB_CIRCLE:{
            return 2.0f * g->object.circle.radius;
        }
    case EMB_ELLIPSE:{
            return 2.0f * g->object.ellipse.radius.y;
        }
    default:
        *error = EMB_WRONG_TYPE_ERR;
        break;
    }
    return 1.0;
}

/* FIXME: finish all types. */
EmbReal emb_radius(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    switch (g->type) {
    case EMB_ARC:{
            EmbReal incAngle = emb_included_angle(g, error);
            EmbReal chord = emb_vector_length(emb_chord(g, error));
            return fabs(chord / (2.0 * sin(incAngle / 2.0)));
        }
    default:
        *error = EMB_WRONG_TYPE_ERR;
        break;
    }
    return 1.0;
}

/* FIXME */
EmbReal emb_radius_major(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    switch (g->type) {
    default:
        *error = EMB_WRONG_TYPE_ERR;
        break;
    }
    return 1.0;
}

/* FIXME */
EmbReal emb_radius_minor(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    switch (g->type) {
    default:
        break;
    }
    return 1.0;
}

/* FIXME */
EmbReal emb_diameter_major(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    switch (g->type) {
    default:
        break;
    }
    return 1.0;
}

/* FIXME */
EmbReal emb_diameter_minor(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    default:
        break;
    }
    return 1.0;
}

/* FIXME */
EmbReal emb_diameter(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    default:
        break;
    }
    return 1.0;
}

/* . */
EmbVector emb_quadrant(EmbGeometry *geometry, int degrees, EmbError *error)
{
    EmbVector v;
    EmbReal radius = 1.0;
    v.x = 0.0;
    v.y = 0.0;
    switch (geometry->type) {
    case EMB_CIRCLE:{
            v = geometry->object.circle.center;
            radius = geometry->object.circle.radius;
            break;
        }
    case EMB_ELLIPSE:{
            v = geometry->object.ellipse.center;
            if (degrees % 180 == 0) {
                radius = geometry->object.ellipse.radius.x;
            } else {
                radius = geometry->object.ellipse.radius.y;
            }
            break;
        }
    default:
        break;
    }
    EmbReal rot = radians( /* rotation() + */ degrees);
    v.x += radius * cos(rot);
    v.y += radius * sin(rot);
    return v;
}

/* . */
EmbReal emb_angle(EmbGeometry *geometry, EmbError *error)
{
    EmbVector v = emb_vector_subtract(geometry->object.line.end,
                                      geometry->object.line.start);
    EmbReal angle = emb_vector_angle(v) /* - rotation() */ ;
    return fmod(angle + 360.0, 360.0);
}

/* . */
EmbReal emb_start_angle(EmbGeometry *geometry, EmbError *error)
{
    switch (geometry->type) {
    case EMB_ARC:{
            *error = EMB_NO_ERR;
            EmbVector center = emb_arc_center(geometry->object.arc, error);
            if (*error) {
                return 0.0;
            }
            EmbVector v = emb_vector_subtract(center,
                                              geometry->object.arc.start);
            EmbReal angle = emb_vector_angle(v) /* - rotation() */ ;
            return fmod(angle + 360.0, 360.0);
        }
    default:
        break;
    }
    return 0.0f;
}

/* . */
EmbReal emb_end_angle(EmbGeometry *geometry, EmbError *error)
{
    switch (geometry->type) {
    case EMB_ARC:{
            *error = EMB_NO_ERR;
            EmbVector center = emb_arc_center(geometry->object.arc, error);
            if (*error) {
                return 0.0;
            }
            EmbVector v = emb_vector_subtract(center,
                                              geometry->object.arc.end);
            EmbReal angle = emb_vector_angle(v) /* - rotation() */ ;
            return fmod(angle + 360.0, 360.0);
        }
    default:
        break;
    }
    return 0.0f;
}

/* . */
EmbReal emb_arc_length(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    case EMB_ARC:{
            *error = EMB_NO_ERR;
            EmbReal radius = emb_radius(g, error);
            if (*error) {
                return 0.0;
            }
            EmbReal angle = emb_included_angle(g, error);
            if (*error) {
                return 0.0;
            }
            return radians(angle) * radius;
        }
    default:
        break;
    }
    return 0.0;
}

/* . */
EmbReal emb_area(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    case EMB_ARC:{
            /* Area of a circular segment */
            *error = EMB_NO_ERR;
            EmbReal r = emb_radius(g, error);
            if (*error) {
                return 0.0;
            }
            EmbReal theta = emb_included_angle(g, error);
            if (*error) {
                return 0.0;
            }
            theta = radians(theta);
            return ((r * r) / 2) * (theta - sin(theta));
        }
    case EMB_CIRCLE:{
            EmbReal r = g->object.circle.radius;
            return embConstantPi * r * r;
        }
    case EMB_RECT:
        return g->object.rect.w * g->object.rect.h;
    case EMB_IMAGE:
    default:
        break;
    }
    /* The area of most objects defaults to the area of the rectangle described by the
     * object's width and height.
     */
    EmbReal width = emb_width(g, error);
    if (*error) {
        return 0.0;
    }
    EmbReal height = emb_height(g, error);
    if (*error) {
        return 0.0;
    }
    return fabs(width * height);
}

/* . */
EmbVector emb_chord(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    case EMB_ARC:
    case EMB_LINE:
    case EMB_PATH:
    case EMB_POLYLINE:{
            *error = EMB_NO_ERR;
            EmbVector start = emb_start(g, error);
            if (*error) {
                return emb_vector(0.0, 0.0);
            }
            EmbVector end = emb_end_point(g, error);
            if (*error) {
                return emb_vector(0.0, 0.0);
            }
            return emb_vector_subtract(end, start);
        }
    default:
        *error = EMB_WRONG_TYPE_ERR;
        break;
    }
    return emb_vector(0.0, 0.0);
}

/* . */
EmbReal emb_included_angle(EmbGeometry *g, EmbError *error)
{
    switch (g->type) {
    case EMB_ARC:{
            /* Properties of a Circle - Get the Included Angle - Reference: ASD9 */
            *error = EMB_NO_ERR;
            EmbReal chord = emb_chord_length(g, error);
            if (*error) {
                return 0.0;
            }
            EmbReal rad = emb_radius(g, error);
            if (*error) {
                return 0.0;
            }
            if (chord <= 0 || rad <= 0) {
                /* Prevents division by zero and non-existant circles. */
                *error = EMB_DIV_ZERO_ERR;
                return 0.0;
            }

            /* NOTE: Due to floating point rounding errors, we need to clamp the
             * quotient so it is in the range [-1, 1]
             * If the quotient is out of that range, then the result of asin()
             * will be NaN.
             */
            EmbReal quotient = chord / (2.0 * rad);
            quotient = EMB_MIN(1.0, quotient);
            /* NOTE: 0 rather than -1 since we are enforcing a positive chord and
             * radius
             */
            quotient = EMB_MAX(0.0, quotient);

            return degrees(2.0 * asin(quotient));
        }
    default:
        break;
    }
    return 0.0;
}

/* . */
int8_t emb_clockwise(EmbGeometry *geometry, EmbError *error)
{
    switch (geometry->type) {
    case EMB_ARC:{
            /* NOTE: Y values are inverted here on purpose. */
            geometry->object.arc.start.y = -geometry->object.arc.start.y;
            geometry->object.arc.mid.y = -geometry->object.arc.start.y;
            geometry->object.arc.end.y = -geometry->object.arc.end.y;
            return emb_arc_clockwise(*geometry);
        }
    default:
        break;
    }
    return 0;
}

/* . */
EmbError emb_set_start_angle(EmbGeometry *geometry, EmbReal angle)
{
    printf("%f\n", angle);
    switch (geometry->type) {
    case EMB_ARC:{
            /* TODO: ArcObject setObjectStartAngle */
            break;
        }
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
EmbError emb_set_end_angle(EmbGeometry *geometry, EmbReal angle)
{
    printf("%f\n", angle);
    switch (geometry->type) {
    case EMB_ARC:{
            /* TODO: ArcObject setObjectEndAngle */
            break;
        }
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
EmbError emb_set_start_point(EmbGeometry *geometry, EmbVector point)
{
    switch (geometry->type) {
    case EMB_ARC:{
            geometry->object.arc.start = point;
            /* calculateData(); */
            break;
        }
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
EmbError emb_set_mid_point(EmbGeometry *geometry, EmbVector point)
{
    switch (geometry->type) {
    case EMB_ARC:{
            geometry->object.arc.mid = point;
            /* calculateData(); */
            break;
        }
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
EmbError emb_set_end_point(EmbGeometry *geometry, EmbVector point)
{
    switch (geometry->type) {
    case EMB_ARC:{
            geometry->object.arc.end = point;
            /* calculateData(); */
            break;
        }
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
EmbError emb_set_radius(EmbGeometry *g, EmbReal radius)
{
    switch (g->type) {
    case EMB_ARC:{
            EmbVector delta;
            float rad;
            if (radius <= 0.0f) {
                rad = 0.0000001f;
            } else {
                rad = radius;
            }

            EmbError error = EMB_NO_ERR;
            EmbVector center = emb_arc_center(g->object.arc, &error);
            if (error) {
                return error;
            }
            EmbReal delta_length;

            delta = emb_vector_subtract(g->object.arc.start, center);
            delta_length = emb_vector_length(delta);
            delta = emb_vector_scale(delta, rad / delta_length);
            g->object.arc.start = emb_vector_add(center, delta);

            delta = emb_vector_subtract(g->object.arc.mid, center);
            delta_length = emb_vector_length(delta);
            delta = emb_vector_scale(delta, rad / delta_length);
            g->object.arc.mid = emb_vector_add(center, delta);

            delta = emb_vector_subtract(g->object.arc.end, center);
            delta_length = emb_vector_length(delta);
            delta = emb_vector_scale(delta, rad / delta_length);
            g->object.arc.end = emb_vector_add(center, delta);
            return EMB_NO_ERR;
        }
    case EMB_CIRCLE:
        g->object.circle.radius = radius;
        return EMB_NO_ERR;
    default:
        break;
    }
    return EMB_WRONG_TYPE_ERR;
}

/* . */
EmbError emb_set_diameter(EmbGeometry *geometry, EmbReal diameter)
{
    switch (geometry->type) {
    case EMB_CIRCLE:{
            geometry->object.circle.radius = diameter / 2.0;
            /* FIXME: updatePath(); */
            break;
        }
    default:
        break;
    }
    return EMB_NO_ERR;
}

/*
 * Sets the area of the geometry if that is meaningful, otherwise
 * return EMB_WRONG_TYPE_ERR.
 */
EmbError emb_set_area(EmbGeometry *geometry, EmbReal area)
{
    switch (geometry->type) {
    case EMB_CIRCLE:{
            EmbReal radius = sqrt(area / embConstantPi);
            emb_set_radius(geometry, radius);
            return EMB_NO_ERR;
        }
    default:
        break;
    }
    return EMB_WRONG_TYPE_ERR;
}

/*
 * Sets the circumference of the geometry if that is meaningful, otherwise
 * return EMB_WRONG_TYPE_ERR.
 */
EmbError emb_set_circumference(EmbGeometry *geometry, EmbReal circumference)
{
    switch (geometry->type) {
    case EMB_CIRCLE:{
            EmbReal diameter = circumference / embConstantPi;
            emb_set_diameter(geometry, diameter);
            return EMB_NO_ERR;
        }
    default:
        break;
    }
    return EMB_WRONG_TYPE_ERR;
}

/* . */
EmbError emb_set_radius_major(EmbGeometry *geometry, EmbReal radius)
{
    emb_set_diameter_major(geometry, radius * 2.0);
    return EMB_NO_ERR;
}

/* . */
EmbError emb_set_radius_minor(EmbGeometry *geometry, EmbReal radius)
{
    emb_set_diameter_minor(geometry, radius * 2.0);
    return EMB_NO_ERR;
}

/* . */
EmbError emb_set_diameter_major(EmbGeometry *geometry, EmbReal diameter)
{
    switch (geometry->type) {
    case EMB_ELLIPSE:
        /* FIXME: Identify longer axis and replace. */
        geometry->object.ellipse.radius.x = diameter;
        break;
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
EmbError emb_set_diameter_minor(EmbGeometry *geometry, EmbReal diameter)
{
    switch (geometry->type) {
    case EMB_ELLIPSE:
        /* FIXME: Identify longer axis and replace. */
        geometry->object.ellipse.radius.x = diameter;
        break;
    default:
        break;
    }
    return EMB_NO_ERR;
}

/* . */
void emb_geometry_path(EmbGeometry *geometry, int8_t *path, EmbError *error)
{
}

/* . */
EmbReal emb_circumference(EmbGeometry *geometry, EmbError *error)
{
    switch (geometry->type) {
    case EMB_CIRCLE:{
            return 2.0 * embConstantPi * geometry->object.circle.radius;
        }
    default:
        break;
    }
    return 1.0;
}

/* Our generic object interface backends to each individual type.
 * The caller defines what the type is.
 */
EmbGeometry *emb_init(int type_in)
{
    EmbGeometry *obj = (EmbGeometry *) malloc(sizeof(EmbGeometry));
    obj->type = type_in;
    obj->color.r = 0;
    obj->color.g = 0;
    obj->color.b = 0;

    /*
       // QGraphicsItem* parent
       debug_message("BaseObject Constructor()");

       objPen.setCapStyle(RoundCap);
       objPen.setJoinStyle(RoundJoin);
       lwtPen.setCapStyle(RoundCap);
       lwtPen.setJoinStyle(RoundJoin);

       objID = QDateTime::currentMSecsSinceEpoch();
     */

    switch (obj->type) {
    case EMB_ARC:{
            /*
               obj = emb_arc(1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
               emb_arc_init(EmbArc arc_in, uint32_t rgb, int lineType)
               arc = arc_in;

               setFlag(ItemIsSelectable, true);

               calculateArcData(arc);

               setColor(rgb);
               setLineType(lineType);
               setLineWeight(0.35); //TODO: pass in proper lineweight
               setPen(objPen);
             */
            break;
        }
    }
    return obj;
}

/* Free the memory occupied by a non-stitch geometry object.
 *
 * Pointer to geometry memory.
 */
void emb_geometry_free(EmbGeometry *obj)
{
    switch (obj->type) {
    case EMB_ARC:{
            return;
        }
    case EMB_CIRCLE:{
            return;
        }
    case EMB_ELLIPSE:{
            return;
        }
    default:
        return;
    }
}

/* Calculate the bounding box of geometry a obj based on what kind of
 * geometric object it is.
 *
 * obj A pointer to the geometry memory.
 * Returns an EmbRect, the bounding box in the same scale as the input geometry.
 *
 * In the case of a failure the bounding box returned is always the unit square
 * with top left corner at (0, 0).
 */
EmbRect emb_boundingRect(EmbGeometry *obj)
{
    EmbRect r;
    if (obj->type == EMB_ARC) {
        /*
           arcRect.setWidth(radius*2.0);
           arcRect.setHeight(radius*2.0);
           arcRect.moveCenter(EmbVector(0,0));
           setRect(arcRect);
         */
    }
    r.y = 0.0;
    r.x = 0.0;
    r.w = 1.0;
    r.h = 1.0;
    /*
       "Base"
       //If gripped, force this object to be drawn even if it is offscreen
       if (objectRubberMode() == OBJ_RUBBER_GRIP)
       return scene()->sceneRect();
       return path().boundingRect();
     */
    return r;
}

void emb_set_color(EmbGeometry *obj, EmbColor color)
{
    obj->color = color;
    /*
       objPen.setColor(color);
       lwtPen.setColor(color);
     */
}

void emb_set_color_rgb(EmbGeometry *obj, uint32_t rgb)
{
    printf("%p", obj);
    printf("%d", rgb);
    /*
       objPen.setColor(QColor(rgb));
       lwtPen.setColor(QColor(rgb));
     */
}

void emb_set_linetype(EmbGeometry *obj, int lineType)
{
    printf("%p %d\n", obj, lineType);
    /*
       objPen.setStyle(lineType);
       lwtPen.setStyle(lineType);
     */
}

void emb_set_line_weight(EmbGeometry *obj, float lineWeight)
{
    printf("%p %f\n", obj, lineWeight);
    /*
       objPen.setWidthF(0); //NOTE: The objPen will always be cosmetic

       if (lineWeight < 0) {
       if (lineWeight == OBJ_LWT_BYLAYER) {
       lwtPen.setWidthF(0.35); //TODO: getLayerLineWeight
       }
       else if (lineWeight == OBJ_LWT_BYBLOCK) {
       lwtPen.setWidthF(0.35); //TODO: getBlockLineWeight
       }
       else {
       QMessageBox::warning(0, translate("Error - Negative Lineweight"),
       translate("Lineweight: %1")
       .arg(std::string().setNum(lineWeight)));
       debug_message("Lineweight cannot be negative! Inverting sign.");
       lwtPen.setWidthF(-lineWeight);
       }
       }
       else {
       lwtPen.setWidthF(lineWeight);
       }
     */
}

EmbVector emb_base_rubber_point(EmbGeometry *obj, const int8_t *key)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    printf("%p %s\n", obj, key);
    /*
       if (objRubberPoints.contains(key)) {
       return objRubberPoints.value(key);
       }

       QGraphicsScene* gscene = scene();
       if (gscene) {
       return scene()->attribute("SCENE_QSNAP_POINT").toPointF();
       }
     */
    return v;
}

const int8_t *emb_base_rubber_text(EmbGeometry *obj, const int8_t *key)
{
    printf("%p %s\n", obj, key);
    /*
       if (objRubberTexts.contains(key))
       return objRubberTexts.value(key);
     */
    return "";
}

/*
 * TODO: pass in proper lineweight
void dim_leader_init(EmbLine line, uint32_t rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Leader Dimension");

    setFlag(ItemIsSelectable, true);

    curved = false;
    filled = true;
    setEndPoint1(x1, y1);
    setEndPoint2(x2, y2);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35);
    setPen(objPen);
}
*/

/*
void
emb_dimleader_set_end_point_1(EmbVector endPt1)
{
    EmbVector endPt2 = objectEndPoint2();
    EmbVector delta = emb_vector_subtract(endPt2, endPt1);
    setRotation(0);
    setLine(0, 0, dx, dy);
    setPos(endPt1);
    updateLeader();
}

void
dimleader_set_end_point_2(EmbVector endPt2)
{
    EmbVector delta;
    EmbVector endPt1 = scenePos();
    emb_vector_subtract(endPt2, endPt1, &delta);
    setRotation(0);
    setLine(0, 0, delta.x, delta.y);
    setPos(endPt1);
    updateLeader();
}

EmbVector
dimleader_end_point_1()
{
    return scenePos();
}

EmbVector
dimleader_objectEndPoint2()
{
    EmbLine lyne = line();
    float rot = radians(rotation());
    EmbVector point2;
    point2.x = lyne.x2()*scale();
    point2.y = lyne.y2()*scale();
    EmbVector rot = emb_vector_rotate(point2, alpha);

    return (scenePos() + rot);
}

EmbVector dimleader_objectMidPoint()
{
    EmbVector mp = line().pointAt(0.5) * scale();
    float alpha = radians(rotation());
    EmbVector rotMid = emb_vector_rotate(mp, alpha);
    return scenePos() + rotMid;
}

float dimleader_objectAngle()
{
    return fmodf(line().angle() - rotation(), 360.0);
}

//TODO: Make arrow style, angle, length and line angle and length customizable.
void
dimleader_updateLeader()
{
    int arrowStyle = Closed;
    float arrowStyleAngle = 15.0;
    float arrowStyleLength = 1.0;
    float lineStyleAngle = 45.0;
    float lineStyleLength = 1.0;

    EmbLine lyne = line();
    float angle = lyne.angle();
    EmbVector ap0 = lyne.p1();
    EmbVector lp0 = lyne.p2();

    //Arrow
    EmbLine lynePerp(lyne.pointAt(arrowStyleLength/lyne.length()) ,lp0);
    lynePerp.setAngle(angle + 90);
    EmbLine lyne1(ap0, lp0);
    EmbLine lyne2(ap0, lp0);
    lyne1.setAngle(angle + arrowStyleAngle);
    lyne2.setAngle(angle - arrowStyleAngle);
    EmbVector ap1;
    EmbVector ap2;
    lynePerp.intersects(lyne1, &ap1);
    lynePerp.intersects(lyne2, &ap2);

    //Math Diagram
    //                 .(ap1)                     .(lp1)
    //                /|                         /|
    //               / |                        / |
    //              /  |                       /  |
    //             /   |                      /   |
    //            /    |                     /    |
    //           /     |                    /     |
    //          /      |                   /      |
    //         /       |                  /       |
    //        /+(aSA)  |                 /+(lSA)  |
    // (ap0)./__(aSL)__|__________(lp0)./__(lSL)__|
    //       \ -(aSA)  |                \ -(lSA)  |
    //        \        |                 \        |
    //         \       |                  \       |
    //          \      |                   \      |
    //           \     |                    \     |
    //            \    |                     \    |
    //             \   |                      \   |
    //              \  |                       \  |
    //               \ |                        \ |
    //                \|                         \|
    //                 .(ap2)                     .(lp2)

    if (arrowStyle == Open) {
        arrowStylePath = QPainterPath();
        arrowStylePath.moveTo(ap1);
        arrowStylePath.lineTo(ap0);
        arrowStylePath.lineTo(ap2);
        arrowStylePath.lineTo(ap0);
        arrowStylePath.lineTo(ap1);
    }
    else if (arrowStyle == Closed) {
        arrowStylePath = QPainterPath();
        arrowStylePath.moveTo(ap1);
        arrowStylePath.lineTo(ap0);
        arrowStylePath.lineTo(ap2);
        arrowStylePath.lineTo(ap1);
    }
    else if (arrowStyle == Dot) {
        arrowStylePath = QPainterPath();
        arrowStylePath.addEllipse(ap0, arrowStyleLength, arrowStyleLength);
    }
    else if (arrowStyle == Box) {
        arrowStylePath = QPainterPath();
        float side = EmbLine(ap1, ap2).length();
        EmbRect ar0(0, 0, side, side);
        ar0.moveCenter(ap0);
        arrowStylePath.addRect(ar0);
    }
    else if (arrowStyle == Tick) {
    }

    lineStylePath = QPainterPath();
    lineStylePath.moveTo(ap0);
    lineStylePath.lineTo(lp0);
}
*/

void emb_ellipse_main(void)
{
    /*
       initCommand();
       clearSelection();
       view.ui_mode = "ELLIPSE_MODE_MAJORDIAMETER_MINORRADIUS";
       global.point1 = zero_vector;
       global.point2 = zero_vector;
       global.point3 = zero_vector;
     */
}

/*
void emb_ellipse(float centerX, float centerY, float width, float height, uint32_t rgb, QGraphicsItem* parent)
{
    debug_message("EllipseObject Constructor()");
    init(centerX, centerY, width, height, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void emb_ellipse(EllipseObject* obj, QGraphicsItem* parent)
{
    debug_message("EllipseObject Constructor()");
    if (obj) {
        init(obj->objectCenterX(), obj->objectCenterY(), obj->objectWidth(), obj->objectHeight(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
    }
}

void image_init(EmbRect rect, uint32_t rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Image");

    setFlag(ItemIsSelectable, true);

    setRect(rect);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void image_setRect(float x, float y, float w, float h)
{
    setPos(x, y);
    setRect(0, 0, w, h);
    updatePath();
}

EmbVector image_objectTopLeft()
{
    float alpha = radians(rotation());
    EmbVector tl = rect().topRight() * scale();
    EmbVector ptlrot = emb_vector_rotate(tl, alpha);
    return scenePos() + ptlrot;
}

EmbVector image_objectTopRight()
{
    float alpha = radians(rotation());
    EmbVector tr = rect().topRight() * scale();
    EmbVector ptrrot = emb_vector_rotate(tr, alpha);
    return scenePos() + ptrrot;
}

EmbVector image_objectBottomLeft()
{
    float alpha = radians(rotation());
    EmbVector bl = rect().topRight() * scale();
    EmbVector pblrot = emb_vector_rotate(bl, alpha);
    return scenePos() + pblrot;
}

EmbVector image_objectBottomRight()
{
    float alpha = radians(rotation());
    EmbVector br = rect().topRight() * scale();
    EmbVector pbrrot = emb_vector_rotate(br, alpha);
    return scenePos() + pbrrot;
}

//Command: Line

float global = {}; //Required

void
emb_line_init(void)
{
    initCommand();
    clearSelection();
    global.firstRun = true;
    global.first.x = NaN;
    global.first.y = NaN;
    global.prev.x = NaN;
    global.prev.y = NaN;
}

void
emb_line_init(EmbLine line_in, uint32_t rgb, PenStyle lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Line");

    line = line_in;

    setFlag(ItemIsSelectable, true);

    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void
emb_line_set_endpoint1(EmbVector point1)
{
    float dx = line.start.x - point1.x;
    float dy = line.start.y - point1.y;
    setRotation(0);
    setScale(1);
    setLine(0, 0, dx, dy);
    setPos(point1);
}

void
emb_line_set_endpoint2(EmbVector point1)
{
    float dx = line.end.x - point1.x;
    float dy = line.end.y - point1.y;
    setRotation(0);
    setScale(1);
    setLine(0, 0, dx, dy);
    setPos(point1);
}

EmbVector
emb_line_EndPoint2()
{
    EmbLine lyne = line();
    float alpha = radians(rotation());
    EmbVector point2;
    point2.x = lyne.x2()*scale();
    point2.y = lyne.y2()*scale();
    EmbVector rotEnd = emb_vector_rotate(point2, alpha);

    return scenePos() + rotEnd;
}

EmbVector
emb_line_MidPoint()
{
    EmbLine lyne = line();
    EmbVector mp = lyne.pointAt(0.5) * scale();
    float alpha = radians(rotation());
    EmbVector rotMid = emb_vector_rotate(mp, alpha);

    return scenePos() + rotMid;
}

float
emb_line_angle()
{
    return fmodf(line().angle() - rotation(), 360.0);
}

path_PathObject(float x, float y, const QPainterPath p, uint32_t rgb, QGraphicsItem* parent)
{
    debug_message("PathObject Constructor()");
    init(x, y, p, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

path_PathObject(PathObject* obj, QGraphicsItem* parent)
{
    debug_message("PathObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void path_init(float x, float y, const QPainterPath& p, uint32_t rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Path");

    setFlag(ItemIsSelectable, true);

    updatePath(p);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void point_init(float x, float y, uint32_t rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Point");

    setFlag(ItemIsSelectable, true);

    setRect(-0.00000001, -0.00000001, 0.00000002, 0.00000002);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

void
emb_polygon(float x, float y, const QPainterPath& p, uint32_t rgb, QGraphicsItem* parent)
{
    debug_message("PolygonObject Constructor()");
    init(x, y, p, rgb, SolidLine); //TODO: getCurrentLineType
}

void
polygon_PolygonObject(PolygonObject* obj, QGraphicsItem* parent)
{
    debug_message("PolygonObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void
emb_polygon_init(float x, float y, const QPainterPath& p, uint32_t rgb, PenStyle lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Polygon");

    setFlag(ItemIsSelectable, true);

    gripIndex = -1;
    updatePath(p);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
}

int polygon_findIndex(EmbVector point)
{
    int i = 0;
    int elemCount = normalPath.elementCount();
    //NOTE: Points here are in item coordinates
    EmbVector itemPoint = mapFromScene(point);
    for (i = 0; i < elemCount; i++) {
        QPainterPath::Element e = normalPath.elementAt(i);
        EmbVector elemPoint = EmbVector(e.x, e.y);
        if (itemPoint == elemPoint) return i;
    }
    return -1;
}

void
emb_polyline(float x, float y, const QPainterPath& p, uint32_t rgb, QGraphicsItem* parent)
{
    debug_message("PolylineObject Constructor()");
    init(x, y, p, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void
emb_polyline(EmbPolyline* obj, QGraphicsItem* parent)
{
    debug_message("PolylineObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void embPolyline_init(float x, float y, QPainterPath *p, uint32_t rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Polyline");

    setFlag(ItemIsSelectable, true);

    gripIndex = -1;
    updatePath(p);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
}

int
embPolyline_findIndex(const EmbVector& point)
{
    int elemCount = normalPath.elementCount();
    //NOTE: Points here are in item coordinates
    EmbVector itemPoint = mapFromScene(point);
    for (int i = 0; i < elemCount; i++) {
        QPainterPath::Element e = normalPath.elementAt(i);
        EmbVector elemPoint = EmbVector(e.x, e.y);
        if (itemPoint == elemPoint) return i;
    }
    return -1;
}

void
rect_init(EmbRect rect, uint32_t rgb, PenStyle lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Rectangle");

    setFlag(ItemIsSelectable, true);

    setRect(x, y, w, h);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
}

EmbVector
rect_topLeft()
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    float alpha = radians(rotation());
    EmbVector tl = rect().topLeft() * scale();
    EmbVector ptlrot = emb_vector_rotate(t1, alpha);
    return scenePos() + ptlrot;
    return v;
}

EmbVector
rect_topRight()
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    float alpha = radians(rotation());
    EmbVector tr = rect().topRight() * scale();
    EmbVector ptlrot = emb_vector_rotate(t1, alpha);
    return scenePos() + ptrrot;
    return v;
}
*/

EmbVector embRect_bottomLeft(EmbRect rect)
{
    printf("%f", rect.x);
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    /*
       float alpha = radians(rotation());
       EmbVector bl = rect().bottomLeft() * scale();
       EmbVector pblrot = emb_vector_rotate(b1, alpha);
       return scenePos() + pblrot;
     */
    return v;
}

EmbVector embRect_bottomRight(EmbRect rect)
{
    printf("%f", rect.x);
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    /*
       float alpha = radians(rotation());
       EmbVector br = rect().bottomRight() * scale();
       EmbVector pbrrot = emb_vector_rotate(br, alpha);
       return scenePos() + pbrrot;
     */
    return v;
}

/*
 * BASIC FUNCTIONS
 */

/* round is C99 and we're committed to C90 so here's a replacement.
 */
int emb_round(EmbReal x)
{
    EmbReal y = floor(x);
    if (fabs(x - y) > 0.5) {
        return (int)ceil(x);
    }
    return (int)y;
}

EmbReal radians(EmbReal degree)
{
    return degree * embConstantPi / 180.0;
}

EmbReal degrees(EmbReal radian)
{
    return radian * 180.0 / embConstantPi;
}


/* .
 */
EmbRect emb_rect(EmbReal x, EmbReal y, EmbReal w, EmbReal h)
{
    EmbRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return rect;
}

//NOTE: This void should be used to interpret various object types and save them as polylines for stitchOnly formats.
/*
void
save_to_polyline(EmbPattern* pattern, const EmbVector& objPos, const QPainterPath& objPath, const int8_t* layer, const QColor& color, const int8_t* lineType, const int8_t* lineWeight)
{
    float startX = objPos.x();
    float startY = objPos.y();
    EmbArray *pointList = emb_array_create(EMB_POINT);
    EmbPoint lastPoint;
    QPainterPath::Element element;
    for (int i = 0; i < objPath.elementCount(); ++i) {
        element = objPath.elementAt(i);
        if (pointList->count == 0) {
            lastPoint.position.x = element.x + startX;
            lastPoint.position.y = -(element.y + startY);
            emb_array_addPoint(pointList, lastPoint);
        }
        else {
            lastPoint.position.x += element.x + startX;
            lastPoint.position.y += -(element.y + startY);
        }
    }

    EmbPolyline polyObject;
    polyObject.pointList = pointList;
    polyObject.color.r = color.red();
    polyObject.color.g = color.green();
    polyObject.color.b = color.blue();
    //TODO: proper lineType
    emb_addPolylineAbs(pattern, polyObject);
}

void textSingle_TextSingleObject(const int8_t* str, float x, float y, uint32_t rgb, QGraphicsItem* parent)
{
    debug_message("TextSingleObject Constructor()");
    init(str, x, y, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void textSingle_TextSingleObject(TextSingleObject* obj, QGraphicsItem* parent)
{
    debug_message("TextSingleObject Constructor()");
    if (obj) {
        setTextFont(obj->objTextFont);
        setTextSize(obj->objTextSize);
        setRotation(obj->rotation());
        setTextBackward(obj->objTextBackward);
        setTextUpsideDown(obj->objTextUpsideDown);
        setTextStyle(obj->objTextBold, obj->objTextItalic, obj->objTextUnderline, obj->objTextStrikeOut, obj->objTextOverline);
        init(obj->objText, obj->objectX(), obj->objectY(), obj->objectColorRGB(), SolidLine); //TODO: getCurrentLineType
        setScale(obj->scale());
    }
}

void textSingle_init(const int8_t* str, float x, float y, uint32_t rgb, int lineType)
{
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Single Line Text");

    setFlag(ItemIsSelectable, true);

    objTextJustify = "Left"; //TODO: set the justification properly

    setText(str);
    setPos(x,y);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}

std::stringList text_single_objectTextJustifyList()
{
    std::stringList justifyList;
    justifyList << "Left" << "Center" << "Right" << "Middle";
    // TODO: << "Fit" << "Aligned";
    justifyList << "Top Left" << "Top Center" << "Top Right";
    justifyList << "Middle Left" << "Middle Center" << "Middle Right";
    justifyList << "Bottom Left" << "Bottom Center" << "Bottom Right";
    return justifyList;
}

void textSingle_setText(const int8_t* str)
{
    objText = str;
    QPainterPath textPath;
    QFont font;
    font.setFamily(objTextFont);
    font.setPointSizeF(objTextSize);
    font.setBold(objTextBold);
    font.setItalic(objTextItalic);
    font.setUnderline(objTextUnderline);
    font.setStrikeOut(objTextStrikeOut);
    font.setOverline(objTextOverline);
    textPath.addText(0, 0, font, str);

    //Translate the path based on the justification
    EmbRect jRect = textPath.boundingRect();
    if (objTextJustify == "Left") {
        textPath.translate(-jRect.left(), 0);
    }
    else if (objTextJustify == "Center") {
        textPath.translate(-jRect.center().x(), 0);
    }
    else if (objTextJustify == "Right") {
        textPath.translate(-jRect.right(), 0);
    }
    else if (objTextJustify == "Aligned") {

    } //TODO: TextSingleObject Aligned Justification
    else if (objTextJustify == "Middle") {
        textPath.translate(-jRect.center()); }
    else if (objTextJustify == "Fit") {

    } //TODO: TextSingleObject Fit Justification
    else if (objTextJustify == "Top Left") {
        textPath.translate(-jRect.topLeft());
    }
    else if (objTextJustify == "Top Center") {
        textPath.translate(-jRect.center().x(), -jRect.top());
    }
    else if (objTextJustify == "Top Right") {
        textPath.translate(-jRect.topRight());
    }
    else if (objTextJustify == "Middle Left") {
        textPath.translate(-jRect.left(), -jRect.top()/2.0);
    }
    else if (objTextJustify == "Middle Center") { textPath.translate(-jRect.center().x(), -jRect.top()/2.0); }
    else if (objTextJustify == "Middle Right")  { textPath.translate(-jRect.right(), -jRect.top()/2.0); }
    else if (objTextJustify == "Bottom Left")   { textPath.translate(-jRect.bottomLeft()); }
    else if (objTextJustify == "Bottom Center") { textPath.translate(-jRect.center().x(), -jRect.bottom()); }
    else if (objTextJustify == "Bottom Right")  { textPath.translate(-jRect.bottomRight()); }

    //Backward or Upside Down
    if (objTextBackward || objTextUpsideDown) {
        float horiz = 1.0;
        float vert = 1.0;
        if (objTextBackward) horiz = -1.0;
        if (objTextUpsideDown) vert = -1.0;

        QPainterPath flippedPath;

        QPainterPath::Element element;
        QPainterPath::Element P2;
        QPainterPath::Element P3;
        QPainterPath::Element P4;
        for (int i = 0; i < textPath.elementCount(); ++i) {
            element = textPath.elementAt(i);
            if (element.isMoveTo()) {
                flippedPath.moveTo(horiz * element.x, vert * element.y);
            }
            else if (element.isLineTo()) {
                flippedPath.lineTo(horiz * element.x, vert * element.y);
            }
            else if (element.isCurveTo()) {
                                              // start point P1 is not needed
                P2 = textPath.elementAt(i);   // control point
                P3 = textPath.elementAt(i+1); // control point
                P4 = textPath.elementAt(i+2); // end point

                flippedPath.cubicTo(horiz * P2.x, vert * P2.y,
                                    horiz * P3.x, vert * P3.y,
                                    horiz * P4.x, vert * P4.y);
            }
        }
        objTextPath = flippedPath;
    }
    else {
        objTextPath = textPath;
    }

    //Add the grip point to the shape path
    QPainterPath gripPath = objTextPath;
    gripPath.connectPath(objTextPath);
    gripPath.addRect(-0.00000001, -0.00000001, 0.00000002, 0.00000002);
    setPath(gripPath);
}
*/

void textSingle_setJustify(EmbGeometry *g, const int8_t *justify)
{
    printf("%p, %s\n", g, justify);
    /*
       // Verify the string is a valid option
       objTextJustify = "Left";
       if ((justify == "Left") || (justify == "Center") || (justify == "Right")
       || (justify == "Aligned") || (justify == "Middle") || (justify == "Fit")
       || (justify == "Top Left") || (justify == "Top Center") || (justify == "Top Right")
       || (justify == "Middle Left") || (justify == "Middle Center") || (justify == "Middle Right")
       || (justify == "Bottom Left") || (justify == "Bottom Center") || (justify == "Bottom Right")) {
       objTextJustify = justify;
       }
       setText(objText);
     */
}

/* . */
int emb_backwards(EmbGeometry *g, EmbError *error)
{
    /*
       objTextBackward = value;
       setText(objText);
     */
    *error = EMB_NO_ERR;
    return 0;
}

int emb_bold(EmbGeometry *g, EmbError *error)
{
    /*
       objTextBold = val;
       setText(objText);
     */
    *error = EMB_NO_ERR;
    return 0;
}

int emb_bulge(EmbGeometry *g, EmbError *error)
{
    *error = EMB_NO_ERR;
    return 0;
}

EmbReal emb_chord_length(EmbGeometry *g, EmbError *error)
{
    EmbVector v = emb_chord(g, error);
    if (*error) {
        return 0.0;
    }
    *error = EMB_NO_ERR;
    return emb_vector_length(v);
}

EmbReal emb_chord_angle(EmbGeometry *g, EmbError *error)
{
    return 0.0;
}

#if 0
case EMB_CHORDANGLE:{
    EmbVector delta = emb_chord(g, EMB_CHORD).v;
    v = script_real(emb_vector_angle(delta));
    break;
}

case EMB_CHORDMID:{
    v = emb_chord(g, EMB_CHORD);
    v.v = emb_vector_scale(v.v, 0.5);
    break;
}

case EMB_DIAMETER:{
    v = emb_radius(g, error);
    v.r = fabs(v.r * 2.0);
    break;
}

case EMB_INCANGLE:{
    EmbReal bulge = emb_bulge(g, EMB_BULGE).r;
    v = script_real(atan(bulge) * 4.0);
    break;
}

case EMB_FONT:{
    /*
       objTextFont = font;
       setText(objText);
     */
    break;
}

case EMB_ITALIC:{
    /*
       objTextItalic = val;
       setText(objText);
     */
    break;
}

case EMB_SAGITTA:{
    EmbReal chord = emb_chord(g);
    ScriptValue bulge = emb_bulge(g, EMB_BULGE);
    return script_real(fabs((chord / 2.0) * bulge.r));
}

case EMB_STRIKEOUT:{
    /*
       objTextStrikeOut = val;
       setText(objText);
     */
    break;
}

case EMB_OVERLINE:{
    /*
       objTextOverline = val;
       setText(objText);
     */
    break;
}

case EMB_UNDERLINE:{
    /*
       objTextUnderline = val;
       setText(objText);
     */
    break;
}

case EMB_UPSIDEDOWN:{
    /*
       objTextUpsideDown = value;
       setText(objText);
     */
    break;
}

case EMB_SIZE:{
    /*
       objTextSize = value;
       setText(objText);
     */
    break;
}

case EMB_PERIMETER:{
    break;
}

default:
break;
}

return v;
}

/* */
int emb_gset(EmbGeometry *g, int attribute, ScriptValue value)
{
    printf("%d\n", value.type);
    switch (g->type) {
    case EMB_BOLD:{
            /*
               objTextBold = val;
               setText(objText);
             */
            break;
        }
    case EMB_ITALIC:{
            /*
               objTextItalic = val;
               setText(objText);
             */
            break;
        }
    case EMB_UNDERLINE:{
            /*
               objTextUnderline = val;
               setText(objText);
             */
            break;
        }
    case EMB_STRIKEOUT:{
            /*
               objTextStrikeOut = val;
               setText(objText);
             */
            break;
        }
    case EMB_OVERLINE:{
            /*
               objTextOverline = val;
               setText(objText);
             */
            break;
        }
    case EMB_BACKWARDS:{
            /*
               objTextBackward = val;
               setText(objText);
             */
            break;
        }
    case EMB_UPSIDEDOWN:{
            /*
               objTextUpsideDown = val;
               setText(objText);
             */
            break;
        }
    case EMB_SAGITTA:{
            if (g->type != EMB_ARC) {
                /* ERROR */
                return 0;
            }
            break;
        }
    case EMB_BULGE:{
            if (g->type != EMB_ARC) {
                /* ERROR */
                return 0;
            }
            break;
        }
    case EMB_SIZE:{
            /*
               objTextSize = value;
               setText(objText);
             */
            break;
        }
    case EMB_PERIMETER:{
            /* TODO: Use Ramanujan's approximation here. */
            break;
        }
    case EMB_AREA:{
            /* TODO: look up a formula for ellipses. */
            break;
        }
    default:
        break;
    }
    return 0;
}
#endif

/* Finds the location of the first non-whitespace character
 * in the string and returns it.
 */
int string_whitespace(const int8_t *s)
{
    int i;
    for (i = 0; i < 200; i++) {
        if (s[i] == ' ')
            continue;
        if (s[i] == '\t')
            continue;
        if (s[i] == '\r')
            continue;
        if (s[i] == '\n')
            continue;
        return i;
    }
    return i;
}

/* Note that our version of strlen can tell us that
 * the string is not null-terminated by returning -1.
 */
int embstr_len(EmbString src)
{
    int i;
    for (i = 0; i < 200; i++) {
        if (src[i] == 0) {
            return i;
        }
    }
    return -1;
}

/*
 */
int string_rchar(const int8_t *s, int8_t c)
{
    int i;
    int n = embstr_len(s);
    for (i = n - 1; i >= 0; i--) {
        if (s[i] == c) {
            return i;
        }
    }
    return 0;
}

/* ENCODING SECTION
 * ----------------------------------------------------------------------------
 *
 * The functions in this section are grouped together to aid the developer's
 * understanding of the similarities between the file formats. This also helps
 * reduce errors between reimplementation of the same idea.
 *
 * For example: the Tajima ternary encoding of positions is used by at least 4
 * formats and the only part that changes is the flag encoding.
 *
 * Converts a 6 digit hex string (I.E. "00FF00")
 * into an EmbColor and returns it.
 *
 * a val 6 byte code describing the color as a hex string, doesn't require null termination.
 * Returns EmbColor the same color as our internal type.
 */
EmbColor embColor_fromHexStr(char *val)
{
    EmbColor color;
    int8_t r[3];
    int8_t g[3];
    int8_t b[3];

    r[0] = val[0];
    r[1] = val[1];
    r[2] = 0;

    g[0] = val[2];
    g[1] = val[3];
    g[2] = 0;

    b[0] = val[4];
    b[1] = val[5];
    b[2] = 0;

    color.r = (uint8_t) strtol(r, 0, 16);
    color.g = (uint8_t) strtol(g, 0, 16);
    color.b = (uint8_t) strtol(b, 0, 16);
    return color;
}

EmbColor embColor_make(uint8_t red, uint8_t green, uint8_t blue)
{
    EmbColor c;
    c.r = red;
    c.b = green;
    c.g = blue;
    return c;
}

/* Swap two bytes' positions. */
void emb_swap(char *a, int i, int j)
{
    int8_t tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

/* Checks that there are enough bytes to interpret the header,
 * stops possible segfaults when reading in the header bytes.
 *
 * Returns 0 if there aren't enough, or the length of the file
 * if there are.
 */
int check_header_present(FILE *file, int minimum_header_length)
{
    int length;
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (length < minimum_header_length) {
        return 0;
    }
    return length;
}

/* sectorSize based on the bcfFile version. */
uint32_t sectorSize(bcf_file *bcfFile)
{
    /* version 3 uses 512 byte */
    if (bcfFile->header.majorVersion == 3) {
        return 512;
    }
    return 4096;
}

/* . */
int haveExtraDIFATSectors(bcf_file *file)
{
    return (int)(entriesInDifatSector(file->difat) > 0);
}

/* . */
int seekToSector(bcf_file *bcfFile, FILE *file, const uint32_t sector)
{
    uint32_t offset = sector * sectorSize(bcfFile) + sectorSize(bcfFile);
    return fseek(file, offset, SEEK_SET);
}

/* . */
void parseDIFATSectors(FILE *file, bcf_file *bcfFile)
{
    uint32_t difatEntriesToRead =
        bcfFile->header.numberOfFATSectors - difatEntriesInHeader;
    uint32_t difatSectorNumber = bcfFile->header.firstDifatSectorLocation;
    while ((difatSectorNumber != CompoundFileSector_EndOfChain)
           && (difatEntriesToRead > 0)) {
        seekToSector(bcfFile, file, difatSectorNumber);
        difatSectorNumber =
            readFullSector(file, bcfFile->difat, &difatEntriesToRead);
    }
}

/* . */
int bcfFile_read(FILE *file, bcf_file *bcfFile)
{
    uint32_t i, numberOfDirectoryEntriesPerSector;
    uint32_t directorySectorToReadFrom;

    bcfFile->header = bcfFileHeader_read(file);
    if (memcmp
        (bcfFile->header.signature, "\xd0\xcf\x11\xe0\xa1\xb1\x1a\xe1",
         8) != 0) {
        printf("bad header signature\n");
        printf("Failed to parse header\n");
        return 0;
    }

    bcfFile->difat =
        bcf_difat_create(file, bcfFile->header.numberOfFATSectors,
                         sectorSize(bcfFile));
    if (haveExtraDIFATSectors(bcfFile)) {
        parseDIFATSectors(file, bcfFile);
    }

    bcfFile->fat = bcfFileFat_create(sectorSize(bcfFile));
    for (i = 0; i < bcfFile->header.numberOfFATSectors; ++i) {
        uint32_t fatSectorNumber = bcfFile->difat->fatSectorEntries[i];
        seekToSector(bcfFile, file, fatSectorNumber);
        loadFatFromSector(bcfFile->fat, file);
    }

    numberOfDirectoryEntriesPerSector =
        sectorSize(bcfFile) / sizeOfDirectoryEntry;
    bcfFile->directory =
        CompoundFileDirectory(numberOfDirectoryEntriesPerSector);
    directorySectorToReadFrom = bcfFile->header.firstDirectorySectorLocation;
    while (directorySectorToReadFrom != CompoundFileSector_EndOfChain) {
        seekToSector(bcfFile, file, directorySectorToReadFrom);
        readNextSector(file, bcfFile->directory);
        directorySectorToReadFrom =
            bcfFile->fat->fatEntries[directorySectorToReadFrom];
    }

    return 1;
}

/* Get the File object. */
void *GetFile(bcf_file *bcfFile, FILE *file, int8_t *fileToFind)
{
    int filesize, sectorSize, currentSector;
    int sizeToWrite, currentSize, totalSectors, i, j;
    FILE *fileOut = tmpfile();
    bcf_directory_entry *pointer = bcfFile->directory->dirEntries;
    while (pointer) {
        if (!strcmp(fileToFind, pointer->directoryEntryName)) {
            break;
        }
        pointer = pointer->next;
    }
    filesize = pointer->streamSize;
    sectorSize = bcfFile->difat->sectorSize;
    currentSize = 0;
    currentSector = pointer->startingSectorLocation;
    totalSectors = (int)ceil((float)filesize / sectorSize);
    for (i = 0; i < totalSectors; i++) {
        seekToSector(bcfFile, file, currentSector);
        sizeToWrite = filesize - currentSize;
        if (sectorSize < sizeToWrite) {
            sizeToWrite = sectorSize;
        }
        for (j = 0; j < sizeToWrite; j++) {
            int8_t input;
            if (fread(&input, 1, 1, file) != 1) {
                /* TODO: Needs an error code. */
                puts("ERROR: GetFile failed to read byte.");
                return fileOut;
            }
            if (fwrite(&input, 1, 1, fileOut) != 1) {
                /* TODO: Needs an error code. */
                puts("ERROR: GetFile failed to read byte.");
                return fileOut;
            }
        }
        currentSize += sizeToWrite;
        currentSector = bcfFile->fat->fatEntries[currentSector];
    }
    return fileOut;
}

/* . */
void bcf_file_free(bcf_file *bcfFile)
{
    safe_free(bcfFile->difat);
    safe_free(bcfFile->fat);
    bcf_directory_free(&bcfFile->directory);
    safe_free(bcfFile);
}

/* . */
bcf_file_difat *bcf_difat_create(FILE *file, uint32_t fatSectors,
                                 const uint32_t sectorSize)
{
    uint32_t i;
    bcf_file_difat *difat = 0;
    uint32_t sectorRef;

    difat = (bcf_file_difat *) malloc(sizeof(bcf_file_difat));
    if (!difat) {
        printf
            ("ERROR: compound-file-difat.c bcf_difat_create(), cannot allocate memory for difat\n");
        return NULL;
    }

    difat->sectorSize = sectorSize;
    if (fatSectors > difatEntriesInHeader) {
        fatSectors = difatEntriesInHeader;
    }

    for (i = 0; i < fatSectors; ++i) {
        sectorRef = emb_read_i32(file);
        difat->fatSectorEntries[i] = sectorRef;
    }
    difat->fatSectorCount = fatSectors;
    for (i = fatSectors; i < difatEntriesInHeader; ++i) {
        sectorRef = emb_read_i32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf
                ("ERROR: compound-file-difat.c bcf_difat_create(), Unexpected sector value %x at DIFAT[%d]\n",
                 sectorRef, i);
        }
    }
    return difat;
}

/* . */
uint32_t entriesInDifatSector(bcf_file_difat *fat)
{
    return (fat->sectorSize -
            sizeOfChainingEntryAtEndOfDifatSector) / sizeOfDifatEntry;
}

/* . */
uint32_t
readFullSector(FILE *file,
               bcf_file_difat *bcfFile, uint32_t *difatEntriesToRead)
{
    uint32_t i;
    uint32_t sectorRef;
    uint32_t nextDifatSectorInChain;
    uint32_t entriesToReadInThisSector = 0;
    if (*difatEntriesToRead > entriesInDifatSector(bcfFile)) {
        entriesToReadInThisSector = entriesInDifatSector(bcfFile);
        *difatEntriesToRead -= entriesToReadInThisSector;
    } else {
        entriesToReadInThisSector = *difatEntriesToRead;
        *difatEntriesToRead = 0;
    }

    for (i = 0; i < entriesToReadInThisSector; ++i) {
        sectorRef = emb_read_i32(file);
        bcfFile->fatSectorEntries[bcfFile->fatSectorCount] = sectorRef;
        bcfFile->fatSectorCount++;
    }
    for (i = entriesToReadInThisSector; i < entriesInDifatSector(bcfFile); ++i) {
        sectorRef = emb_read_i32(file);
        if (sectorRef != CompoundFileSector_FreeSector) {
            printf("ERROR: compound-file-difat.c readFullSector(), ");
            printf("Unexpected sector value %x at DIFAT[%d]]\n", sectorRef, i);
        }
    }
    nextDifatSectorInChain = emb_read_i32(file);
    return nextDifatSectorInChain;
}

/* . */
void parseDirectoryEntryName(FILE *file, bcf_directory_entry *dir)
{
    int i;
    for (i = 0; i < 32; ++i) {
        uint16_t unicodechar = emb_read_i16(file);
        if (unicodechar != 0x0000) {
            dir->directoryEntryName[i] = (char)unicodechar;
        }
    }
}

/* . */
bcf_directory *CompoundFileDirectory(const uint32_t maxNumberOfDirectoryEntries)
{
    bcf_directory *dir = (bcf_directory *) malloc(sizeof(bcf_directory));
    if (!dir) {
        printf
            ("ERROR: compound-file-directory.c CompoundFileDirectory(), cannot allocate memory for dir\n");
        return NULL;
    }                           /* TODO: avoid crashing. null pointer will be accessed */
    dir->maxNumberOfDirectoryEntries = maxNumberOfDirectoryEntries;
    dir->dirEntries = 0;
    return dir;
}

/* . */
EmbTime parseTime(FILE *file)
{
    EmbTime returnVal;
    uint32_t ft_low, ft_high;
    /*embTime_time(&returnVal); TODO: use embTime_time() rather than time(). */
    ft_low = emb_read_i32(file);
    ft_high = emb_read_i32(file);
    printf("%u %u\n", ft_low, ft_high);
    /* TODO: translate to actual date time */
    returnVal.day = 1;
    returnVal.hour = 2;
    returnVal.minute = 3;
    returnVal.month = 4;
    returnVal.second = 5;
    returnVal.year = 6;
    return returnVal;
}

/* . */
bcf_directory_entry *CompoundFileDirectoryEntry(FILE *file)
{
    int i;
    const int guidSize = 16;
    bcf_directory_entry *dir = malloc(sizeof(bcf_directory_entry));
    if (dir == NULL) {
        printf
            ("ERROR: compound-file-directory.c CompoundFileDirectoryEntry(), cannot allocate memory for dir\n");
        return NULL;
    }
    memset(dir->directoryEntryName, 0, 32);
    parseDirectoryEntryName(file, dir);
    dir->next = 0;
    dir->directoryEntryNameLength = emb_read_u16(file);
    dir->objectType = (uint8_t) fgetc(file);
    if ((dir->objectType != ObjectTypeStorage)
        && (dir->objectType != ObjectTypeStream)
        && (dir->objectType != ObjectTypeRootEntry)) {
        printf("ERROR: compound-file-directory.c CompoundFileDirectoryEntry()");
        printf(", unexpected object type: %d\n", dir->objectType);
        return NULL;
    }
    dir->colorFlag = (uint8_t) fgetc(file);
    dir->leftSiblingId = emb_read_i32(file);
    dir->rightSiblingId = emb_read_i32(file);
    dir->childId = emb_read_i32(file);
    if (fread(dir->CLSID, 1, guidSize, file) < guidSize) {
        printf("ERROR: Failed to read guidSize bytes for CLSID");
        return dir;
    }
    dir->stateBits = emb_read_i32(file);
    for (i = 0; i < 6; i++) {
        dir->creationTime[i] = emb_read_i32(file);
    }
    for (i = 0; i < 6; i++) {
        dir->modifiedTime[i] = emb_read_i32(file);
    }
    dir->startingSectorLocation = emb_read_i32(file);
    /* StreamSize should really be __int64 or long long,
     * but for our uses we should never run into an issue */
    dir->streamSize = emb_read_i32(file);
    /* top portion of int64 */
    dir->streamSizeHigh = emb_read_i32(file);
    return dir;
}

/* . */
void readNextSector(FILE *file, bcf_directory *dir)
{
    uint32_t i;
    for (i = 0; i < dir->maxNumberOfDirectoryEntries; ++i) {
        bcf_directory_entry *dirEntry = CompoundFileDirectoryEntry(file);
        bcf_directory_entry *pointer = dir->dirEntries;
        if (!pointer) {
            dir->dirEntries = dirEntry;
        } else {
            while (pointer) {
                if (!pointer->next) {
                    pointer->next = dirEntry;
                    break;
                }
                pointer = pointer->next;
            }
        }
    }
}

/* . */
void bcf_directory_free(bcf_directory **dir)
{
    bcf_directory *dirptr;
    bcf_directory_entry *pointer;
    if (dir == NULL) {
        return;
    }
    dirptr = *dir;
    pointer = dirptr->dirEntries;
    while (pointer) {
        bcf_directory_entry *entryToFree;
        entryToFree = pointer;
        pointer = pointer->next;
        safe_free(entryToFree);
    }
    safe_free(*dir);
}

/* . */
bcf_file_fat *bcfFileFat_create(const uint32_t sectorSize)
{
    bcf_file_fat *fat = (bcf_file_fat *) malloc(sizeof(bcf_file_fat));
    if (!fat) {
        printf("ERROR: compound-file-fat.c bcfFileFat_create(), ");
        printf("cannot allocate memory for fat\n");
        return NULL;
    }
    fat->numberOfEntriesInFatSector = sectorSize / sizeOfFatEntry;
    fat->fatEntryCount = 0;
    return fat;
}

/* . */
void loadFatFromSector(bcf_file_fat *fat, FILE *file)
{
    uint32_t i;
    uint32_t current_fat_entries = fat->fatEntryCount;
    uint32_t newSize = current_fat_entries + fat->numberOfEntriesInFatSector;
    for (i = current_fat_entries; i < newSize; ++i) {
        fat->fatEntries[i] = emb_read_i32(file);
    }
    fat->fatEntryCount = newSize;
}

/* . */
bcf_file_header bcfFileHeader_read(FILE *file)
{
    bcf_file_header header;
    if (fread(header.signature, 1, 8, file) < 8) {
        puts("ERROR: failed to read signature bytes from bcf file.");
        return header;
    }
    if (fread(header.CLSID, 1, 16, file) < 16) {
        puts("ERROR: failed to read CLSID bytes from bcf file.");
        return header;
    }
    header.minorVersion = emb_read_u16(file);
    header.majorVersion = emb_read_u16(file);
    header.byteOrder = emb_read_u16(file);
    header.sectorShift = emb_read_u16(file);
    header.miniSectorShift = emb_read_u16(file);
    header.reserved1 = emb_read_u16(file);
    header.reserved2 = emb_read_i32(file);
    header.numberOfDirectorySectors = emb_read_i32(file);
    header.numberOfFATSectors = emb_read_i32(file);
    header.firstDirectorySectorLocation = emb_read_i32(file);
    header.transactionSignatureNumber = emb_read_i32(file);
    header.miniStreamCutoffSize = emb_read_i32(file);
    header.firstMiniFATSectorLocation = emb_read_i32(file);
    header.numberOfMiniFatSectors = emb_read_i32(file);
    header.firstDifatSectorLocation = emb_read_i32(file);
    header.numberOfDifatSectors = emb_read_i32(file);
    return header;
}

/* . */
int
emb_generate_satin_outline(EmbArray *lines, EmbReal thickness,
                           EmbSatinOutline *result)
{
    int i;
    EmbLine line1, line2;
    EmbSatinOutline outline;
    EmbVector out;
    EmbVector v1;
    EmbVector temp;
    EmbLine line;

    EmbReal halfThickness = thickness / 2.0;
    int intermediateOutlineCount = 2 * lines->count - 2;
    outline.side1 = emb_array_create(EMB_VECTOR);
    if (!outline.side1) {
        printf
            ("ERROR: emb_generate_satin_outline(), cannot allocate memory for outline->side1\n");
        return 0;
    }
    outline.side2 = emb_array_create(EMB_VECTOR);
    if (!outline.side2) {
        printf
            ("ERROR: emb_generate_satin_outline(), cannot allocate memory for outline->side2\n");
        return 0;
    }

    for (i = 1; i < lines->count; i++) {
        line.start = lines->geometry[i - 1].object.vector;
        line.end = lines->geometry[i].object.vector;

        v1 = emb_line_normal(line, 1);

        temp = emb_vector_scale(v1, halfThickness);
        temp = emb_vector_add(temp, lines->geometry[i - 1].object.vector);
        emb_array_addVector(outline.side1, temp);
        temp = emb_vector_add(temp, lines->geometry[i].object.vector);
        emb_array_addVector(outline.side1, temp);

        temp = emb_vector_scale(v1, -halfThickness);
        temp = emb_vector_add(temp, lines->geometry[i - 1].object.vector);
        emb_array_addVector(outline.side2, temp);
        temp = emb_vector_add(temp, lines->geometry[i].object.vector);
        emb_array_addVector(outline.side2, temp);
    }

    if (!result) {
        printf
            ("ERROR: emb_generate_satin_outline(), result argument is null\n");
        return 0;
    }
    result->side1 = emb_array_create(EMB_VECTOR);
    if (!result->side1) {
        printf
            ("ERROR: emb_generate_satin_outline(), cannot allocate memory for result->side1\n");
        return 0;
    }
    result->side2 = emb_array_create(EMB_VECTOR);
    if (!result->side2) {
        printf
            ("ERROR: emb_generate_satin_outline(), cannot allocate memory for result->side2\n");
        return 0;
    }

    emb_array_addVector(result->side1,
                        outline.side1->geometry[0].object.vector);
    emb_array_addVector(result->side2,
                        outline.side2->geometry[0].object.vector);

    for (i = 3; i < intermediateOutlineCount; i += 2) {
        int emb_error = 0;
        line1.start = outline.side1->geometry[i - 3].object.vector;
        line1.end = outline.side1->geometry[i - 2].object.vector;
        line2.start = outline.side1->geometry[i - 1].object.vector;
        line2.end = outline.side1->geometry[i].object.vector;
        out = emb_line_intersection(line1, line2, &emb_error);
        if (emb_error) {
            puts("No intersection point.");
        }
        emb_array_addVector(result->side1, out);

        line1.start = outline.side2->geometry[i - 3].object.vector;
        line1.end = outline.side2->geometry[i - 2].object.vector;
        line2.start = outline.side2->geometry[i - 1].object.vector;
        line2.end = outline.side2->geometry[i].object.vector;
        out = emb_line_intersection(line1, line2, &emb_error);
        if (emb_error) {
            puts("No intersection point.");
        }
        emb_array_addVector(result->side2, out);
    }

    emb_array_addVector(result->side1,
                        outline.side1->geometry[2 * lines->count -
                                                3].object.vector);
    emb_array_addVector(result->side2,
                        outline.side2->geometry[2 * lines->count -
                                                3].object.vector);
    result->length = lines->count;
    return 1;
}

/* . */
EmbArray *emb_satin_outline_render(EmbSatinOutline *result, EmbReal density)
{
    int i, j;
    EmbVector currTop, currBottom, topDiff, bottomDiff, midDiff;
    EmbVector midLeft, midRight, topStep, bottomStep;
    EmbArray *stitches = 0;
    int numberOfSteps;
    EmbReal midLength;

    if (!result) {
        printf("ERROR: emb_satin_outline_render(), result argument is null\n");
        return 0;
    }

    if (result->length > 0) {
        for (j = 0; j < result->length - 1; j++) {
            EmbGeometry *g10 = &(result->side1->geometry[j + 0]);
            EmbGeometry *g11 = &(result->side1->geometry[j + 1]);
            EmbGeometry *g20 = &(result->side2->geometry[j + 0]);
            EmbGeometry *g21 = &(result->side2->geometry[j + 1]);
            topDiff =
                emb_vector_subtract(g10->object.vector, g11->object.vector);
            bottomDiff =
                emb_vector_subtract(g21->object.vector, g20->object.vector);

            midLeft =
                emb_vector_average(g10->object.vector, g20->object.vector);
            midRight =
                emb_vector_average(g11->object.vector, g21->object.vector);

            midDiff = emb_vector_subtract(midLeft, midRight);
            midLength = emb_vector_length(midDiff);

            numberOfSteps = (int)(midLength * density / 200);
            topStep = emb_vector_scale(topDiff, 1.0 / numberOfSteps);
            bottomStep = emb_vector_scale(bottomDiff, 1.0 / numberOfSteps);
            currTop = g10->object.vector;
            currBottom = g20->object.vector;

            for (i = 0; i < numberOfSteps; i++) {
                if (!stitches) {
                    stitches = emb_array_create(EMB_VECTOR);
                }
                emb_array_addVector(stitches, currTop);
                emb_array_addVector(stitches, currBottom);
                currTop = emb_vector_add(currTop, topStep);
                currBottom = emb_vector_add(currBottom, bottomStep);
            }
        }
        emb_array_addVector(stitches, currTop);
        emb_array_addVector(stitches, currBottom);
    }
    return stitches;
}

/* . */
void write_24bit(FILE *file, int x)
{
    uint8_t a[4];
    a[0] = (uint8_t) 0;
    a[1] = (uint8_t) (x & 0xFF);
    a[2] = (uint8_t) ((x >> 8) & 0xFF);
    a[3] = (uint8_t) ((x >> 16) & 0xFF);
    fwrite(a, 1, 4, file);
}


/* . */
void binaryReadString(FILE *file, int8_t *buffer, int maxLength)
{
    int i = 0;
    while (i < maxLength) {
        buffer[i] = (char)fgetc(file);
        if (buffer[i] == '\0') {
            break;
        }
        i++;
    }
}

/* . */
void binaryReadUnicodeString(FILE *file, int8_t *buffer, const int stringLength)
{
    int i = 0;
    for (i = 0; i < stringLength * 2; i++) {
        int8_t input = (char)fgetc(file);
        if (input != 0) {
            buffer[i] = input;
        }
    }
}

/*
 * Tests for the presence of a string a s in the supplied
 * a array.
 *
 * The end of the array is marked by an empty string.
 *
 * Returns 0 if not present 1 if present.
 */
int stringInArray(const int8_t *s, const int8_t **array)
{
    int i;
    for (i = 0; embstr_len(array[i]); i++) {
        if (!strncmp(s, array[i], 200)) {
            return 1;
        }
    }
    return 0;
}

/* . */
int emb_readline(FILE *file, int8_t *line, int maxLength)
{
    int i;
    int8_t c;
    for (i = 0; i < maxLength - 1; i++) {
        if (!fread(&c, 1, 1, file)) {
            break;
        }
        if (c == '\r') {
            if (fread(&c, 1, 1, file) != 1) {
                /* Incomplete Windows-style line ending. */
                break;
            }
            if (c != '\n') {
                fseek(file, -1L, SEEK_CUR);
            }
            break;
        }
        if (c == '\n') {
            break;
        }
        *line = c;
        line++;
    }
    *line = 0;
    return i;
}

/* TODO: description */

/* Get the trim bounds object. */
void
get_trim_bounds(char const *s, int8_t const **firstWord,
                int8_t const **trailingSpace)
{
    int8_t const *lastWord = 0;
    *firstWord = lastWord = s + string_whitespace(s);
    do {
        *trailingSpace = lastWord + string_whitespace(lastWord);
        lastWord = *trailingSpace + string_whitespace(*trailingSpace);
    } while (*lastWord != '\0');
}

/* . */
int8_t *copy_trim(char const *s)
{
    int8_t const *firstWord = 0, *trailingSpace = 0;
    int8_t *result = 0;
    size_t newLength;

    get_trim_bounds(s, &firstWord, &trailingSpace);
    newLength = trailingSpace - firstWord;

    result = (char *)malloc(newLength + 1);
    memcpy(result, firstWord, newLength);
    result[newLength] = '\0';
    return result;
}

/* Optimizes the number (a num) for output to a text file and returns
 * it as a string (a str).
 */
int8_t *emb_optOut(EmbReal num, int8_t *str)
{
    int8_t *str_end;
    /* Convert the number to a string */
    sprintf(str, "%.10f", num);
    /* Remove trailing zeroes */
    str_end = str + embstr_len(str);
    while (*--str_end == '0') ;
    str_end[1] = 0;
    /* Remove the decimal point if it happens to be an integer */
    if (*str_end == '.') {
        *str_end = 0;
    }
    return str;
}

/* . */
void embTime_initNow(EmbTime *t)
{
    printf("%d", t->year);
    /*
       time_t rawtime;
       struct tm* timeinfo;
       time(&rawtime);
       timeinfo = localtime(&rawtime);

       t->year   = timeinfo->tm_year;
       t->month  = timeinfo->tm_mon;
       t->day    = timeinfo->tm_mday;
       t->hour   = timeinfo->tm_hour;
       t->minute = timeinfo->tm_min;
       t->second = timeinfo->tm_sec;
     */
}

/* . */
EmbTime embTime_time(EmbTime *t)
{
    int divideByZero = 0;
    divideByZero = divideByZero / divideByZero;
    /* TODO: wrap time() from time.h and verify it works consistently */

    return *t;
}

/* a points a n_points a width a tolerence
 *
 * Remove points that lie in the middle of two short stitches that could
 * be one longer stitch. Repeat until none are found.
 */
static void
join_short_stitches(int *points, int *n_points, int width, int tolerence)
{
    int found = 1;
    while (found > 0) {
        int i;
        found = 0;
        for (i = *n_points - 2; i >= 0; i--) {
            int st1 = points[i + 1] % width - points[i] % width;
            int st2 = points[i + 2] % width - points[i + 1] % width;
            int same_line = (points[i + 1] / width == points[i] / width)
                && (points[i + 2] / width == points[i + 1] / width);
            if (st1 < tolerence && st2 < tolerence && same_line) {
                found++;
                break;
            }
        }
        if (found) {
            /* Remove the point. */
            i++;
            for (; i < *n_points; i++) {
                points[i] = points[i + 1];
            }
            (*n_points)--;
        }
    }
}

/* a image a n_points a subsample_width a subsample_height
 * a threshold
 * Returns int*
 *
 * Identify darker pixels to put stitches in.
 */
static int *threshold_method(EmbImage *image, int *n_points,
                             int subsample_width, int subsample_height,
                             int threshold)
{
    int i, j;
    int *points;
    int height = image->height;
    int width = image->width;
    points = (int *)malloc((height / subsample_height)
                           * (width / subsample_width) * sizeof(int));
    *n_points = 0;
    for (i = 0; i < height / subsample_height; i++)
        for (j = 0; j < width / subsample_width; j++) {
            EmbColor color;
            int index = subsample_height * i * width + subsample_width * j;
            color.r = image->data[3 * index + 0];
            color.g = image->data[3 * index + 1];
            color.b = image->data[3 * index + 2];
            if (color.r + color.g + color.b < threshold) {
                points[*n_points] = index;
                (*n_points)++;
            }
        }
    return points;
}

/* a points a n_points a width a bias
 *
 * Greedy Algorithm
 * ----------------
 * For each point in the list find the shortest distance to
 * any possible neighbour, then perform a swap to make that
 * neighbour the next item in the list.
 *
 * To make the stitches lie more on one axis than the other
 * bias the distance operator to prefer horizontal direction.
 */
static void greedy_algorithm(int *points, int n_points, int width, EmbReal bias)
{
    int i, j;
    printf("points[0] = %d\n", points[0]);
    printf("n_points = %d\n", n_points);
    printf("width = %d\n", width);
    printf("bias = %f\n", bias);

    for (i = 0; i < n_points - 1; i++) {
        int stor;
        EmbReal shortest = 1.0e20;
        int next = i + 1;
        /* Find nearest neighbour. */
        int x1 = points[i] % width;
        int y1 = points[i] / width;
        for (j = i + 1; j < n_points; j++) {
            int x, y;
            EmbReal distance;
            x = x1 - (points[j] % width);
            if (x * x > shortest) {
                continue;
            }
            y = y1 - (points[j] / width);
            distance = x * x + bias * y * y;
            if (distance < shortest) {
                next = j;
                shortest = distance;
            }
        }
        if (i % 100 == 0) {
            printf("%2.1f%%\n", (100.0 * i) / (1.0 * n_points));
        }
        /* swap points */
        stor = points[next];
        points[next] = points[i + 1];
        points[i + 1] = stor;
    }
}

/* a pattern a points a n_points
 * a scale a width a height
 */
static void
save_points_to_pattern(EmbPattern *pattern, int *points, int n_points,
                       EmbReal scale, int width, int height)
{
    int i;
    for (i = 0; i < n_points; i++) {
        int x, y;
        x = points[i] % width;
        y = height - points[i] / width;
        emb_add_stitch_abs(pattern, scale * x, scale * y, NORMAL, 0);
    }
}

/* a pattern a image a threshhold
 *
 * Uses a threshhold method to determine where to put
 * lines in the fill.
 *
 * Needs to pass a "donut test", i.e. an image with black pixels where:
 *     10 < x*x + y*y < 20
 * over the area (-30, 30) x (-30, 30).
 *
 * Use render then image difference to see how well it passes.
 */
void emb_horizontal_fill(EmbPattern *pattern, EmbImage *image, int threshhold)
{
    /* Size of the crosses in millimeters. */
    EmbReal scale = 0.1;
    int sample_w = 3;
    int sample_h = 3;
    EmbReal bias = 1.2;
    int *points;
    int n_points;

    points = threshold_method(image, &n_points, sample_w, sample_h, threshhold);
    greedy_algorithm(points, n_points, image->width, bias);
    join_short_stitches(points, &n_points, image->width, 40);
    save_points_to_pattern(pattern, points, n_points, scale, image->width,
                           image->height);

    emb_end(pattern);
    safe_free(points);
}

/* a pattern a image a threshhold
 *
 * Uses a threshhold method to determine where to put
 * crosses in the fill.
 *
 * To improve this, we can remove the vertical stitches when two crosses
 * neighbour. Currently the simple way to do this is to chain crosses
 * that are neighbours exactly one ahead.
 */
void emb_crossstitch(EmbPattern *pattern, EmbImage *image, int threshhold)
{
    int i;
    /* Size of the crosses in millimeters. */
    EmbReal scale = 0.1;
    int sample_w = 5;
    int sample_h = 5;
    EmbReal bias = 1.0;
    int *points;
    int n_points;
    int width = 1000;
    points = threshold_method(image, &n_points, sample_w, sample_h, threshhold);
    greedy_algorithm(points, n_points, width, bias);

    for (i = 0; i < n_points; i++) {
        EmbReal x, y;
        x = points[i] % width;
        y = points[i] / width;
        printf("%f %f\n", x, y);
        emb_add_stitch_abs(pattern, scale * x, scale * y, NORMAL, 0);
        emb_add_stitch_abs(pattern, scale * (x + sample_w),
                          scale * (y + sample_h), NORMAL, 0);
        emb_add_stitch_abs(pattern, scale * x, scale * (y + sample_h),
                          NORMAL, 0);
        emb_add_stitch_abs(pattern, scale * (x + sample_w), scale * y,
                          NORMAL, 0);
    }

    emb_end(pattern);
}


/* p1 a p2
 * Returns EmbPattern*
 */
EmbPattern *emb_combine(EmbPattern * p1, EmbPattern * p2) {
    int i;
    EmbPattern *out = emb_create();
    for (i = 0; i < p1->stitch_list->count; i++) {
        emb_array_addStitch(out->stitch_list, p1->stitch_list->stitch[i]);
    }
    for (i = 0; i < p2->stitch_list->count; i++) {
        emb_array_addStitch(out->stitch_list, p2->stitch_list->stitch[i]);
    }
    /* These need to be merged, not appended. */
    for (i = 0; i < p1->thread_list->count; i++) {
        emb_add_thread(out, p1->thread_list->thread[i]);
    }
    for (i = 0; i < p2->thread_list->count; i++) {
        emb_add_thread(out, p2->thread_list->thread[i]);
    }
    return out;
}


/* Check that the pointer isn't NULL before freeing. */
void safe_free(void *data)
{
    if (data) {
        free(data);
        data = 0;
    }
}

uint8_t char_to_lower(uint8_t a) {
    if (a >= 'A' && a <= 'Z') {
        a = a - 'A' + 'a';
    }
    return a;
}

/* Render the pattern a p to the file with name a fname.
 * Return whether it was successful as an int.
 *
 * Basic Render
 * ------------
 *
 * Backends rendering to nanosvg/stb_image.
 *
 * The caller is responsible for the memory in p.
 */
int emb_render(EmbPattern * p, int8_t * fname)
{
    printf("Cannot render %p, %s\n", p, fname);
/*
    const int8_t *tmp_fname = "libembroidery_temp.svg";
    NSVGimage *image = NULL;
    NSVGrasterizer rast;
    uint8_t *img_data = NULL;
    emb_writeAuto(p, tmp_fname);
    image = nsvgParseFromFile(tmp_fname, "px", 96.0f);
    img_data = malloc(4*image->width*image->height);
    nsvgRasterize(
        &rast,
        image,
        0, 0, 1,
        img_data,
        image->width,
        image->height,
        4*image->width);
    stbi_write_png(
         fname,
         image->width,
        image->height,
        4,
        img_data,
        4*image->width);
*/
    return 0;
}

/* Simulate the stitching of a pattern, using the image for rendering
 * hints about how to represent the pattern.
 */
int emb_simulate(EmbPattern * pattern, int8_t * fname)
{
    emb_render(pattern, fname);
    return 0;
}


/* . */
EmbVector scale_and_rotate(EmbVector v, double scale, double angle) {
    EmbVector w;
    double rot = radians(angle);
    double cosRot = cos(rot);
    double sinRot = sin(rot);
    w.x = v.x * scale;
    w.y = v.y * scale;
    w.x = w.x * cosRot - w.y * sinRot;
    w.y = w.x * sinRot + w.y * cosRot;
    return w;
}
