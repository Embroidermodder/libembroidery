/*
 * GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "embroidery.h"

/**
 * @brief Our generic object interface backends to each individual type.
 *
 * \a type_in 
 * @return EmbGeometry* 
 */
EmbGeometry *
embGeometry_init(int type_in)
{
    EmbGeometry *obj = (EmbGeometry*)malloc(sizeof(EmbGeometry));
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
    case EMB_ARC: {
        obj->object.arc = embArc_init();
        /*
        embArc_init(EmbArc arc_in, unsigned int rgb, int lineType)
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

/**
 * @brief Free the memory occupied by a non-stitch geometry object.
 *
 * \a obj Pointer to geometry memory.
 */
void
embGeometry_free(EmbGeometry *obj)
{
    switch (obj->type) {
    case EMB_ARC: {
        return;
    }
    case EMB_CIRCLE: {
        return;
    }
    case EMB_ELLIPSE: {
        return;
    }
    default:
        return;
    }
}

/**
 * @brief Translate \a obj by the vector \a delta.
 *
 * \a obj A pointer to the geometry memory.
 * \a delta A vector in the 0.1mm scale to offset the geometry by.
 */
void
embGeometry_move(EmbGeometry *obj, EmbVector delta)
{
    switch (obj->type) {
    case EMB_ARC: {
        EmbArc *arc = &(obj->object.arc);
        arc->start = embVector_add(arc->start, delta);
        arc->mid = embVector_add(arc->mid, delta);
        arc->end = embVector_add(arc->end, delta);
        return;
    }
    case EMB_CIRCLE: {
        EmbCircle *circle = &(obj->object.circle);
        circle->center = embVector_add(circle->center, delta);
        return;
    }
    default:
        break;
    }
}

/**
 * @brief Calculate the bounding box of geometry \a obj based on what kind of
 * geometric object it is.
 *
 * \a obj A pointer to the geometry memory.
 * @return EmbRect The bounding box in the same scale as the input geometry.
 *
 * In the case of a failure the bounding box returned is always the unit square
 * with top left corner at (0, 0).
 */
EmbRect
embGeometry_boundingRect(EmbGeometry *obj)
{
    EmbRect r;
    if ((obj->type == EMB_ARC)) {
        /*
        arcRect.setWidth(radius*2.0);
        arcRect.setHeight(radius*2.0);
        arcRect.moveCenter(EmbVector(0,0));
        setRect(arcRect);
        */
    }
    r.top = 0.0;
    r.left = 0.0;
    r.bottom = 1.0;
    r.right = 1.0;
    /*
    "Base"
    //If gripped, force this object to be drawn even if it is offscreen
    if (objectRubberMode() == OBJ_RUBBER_GRIP)
        return scene()->sceneRect();
    return path().boundingRect();
    */
    return r;
}

/**
 * @brief Toggle the rubber mode of the object.
 *
 * \a obj 
 *
 * \todo Review. This could be controlled by a simple flag.
 */
void
embGeometry_vulcanize(EmbGeometry *obj)
{
    switch (obj->type) {
    case EMB_ARC:
    case EMB_CIRCLE:
    case EMB_DIM_LEADER:
    case EMB_ELLIPSE:
    case EMB_IMAGE:
    case EMB_LINE:
    case EMB_POINT:
    case EMB_RECT:
    case EMB_TEXT_SINGLE:
        /*
        updateRubber();

        setRubberMode(OBJ_RUBBER_OFF);
        */
        break;
    default:
        break;
    }
    if (obj->type == EMB_PATH) {
        /*
        updateRubber();

        setRubberMode(OBJ_RUBBER_OFF);

        if (!normalPath.elementCount())
            critical_messagebox(0, translate("Empty Path Error"), translate("The path added contains no points. The command that created this object has flawed logic."));
        */
    }
    if (obj->type == EMB_POLYGON) {
        /*
        updateRubber();

        setRubberMode(OBJ_RUBBER_OFF);

        if (!normalPath.elementCount())
            critical_messagebox(0, translate("Empty Polygon Error"), translate("The polygon added contains no points. The command that created this object has flawed logic."));
        */
    }
    if (obj->type == EMB_POLYLINE) {
        /*
        updateRubber();

        setRubberMode(OBJ_RUBBER_OFF);

        if (!normalPath.elementCount())
            critical_messagebox(0, translate("Empty embPolyline Error"), translate("The embPolyline added contains no points. The command that created this object has flawed logic."));
        */
    }
}
