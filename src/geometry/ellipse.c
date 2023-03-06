/*
 * ELLIPSE GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../embroidery.h"

/*
 */
EmbEllipse
embEllipse_init(void)
{
    EmbEllipse ellipse;
    ellipse.center.x = 0.0;
    ellipse.center.y = 0.0;
    ellipse.radius.x = 1.0;
    ellipse.radius.y = 2.0;
    ellipse.rotation = 0.0;
    ellipse.lineType = 0;
    ellipse.color = black_thread.color;
    return ellipse;
}

/*
 */
EmbReal
embEllipse_area(EmbEllipse ellipse)
{

}

/*
 */
EmbReal
embEllipse_perimeter(EmbEllipse ellipse)
{

}


EmbReal
embEllipse_diameterX(EmbEllipse ellipse)
{
    return ellipse.radius.x * 2.0;
}

EmbReal
embEllipse_diameterY(EmbEllipse ellipse)
{
    return ellipse.radius.y * 2.0;
}

EmbReal
embEllipse_width(EmbEllipse ellipse)
{
    return ellipse.radius.x * 2.0;
}

EmbReal
embEllipse_height(EmbEllipse ellipse)
{
    return ellipse.radius.y * 2.0;
}


/*
void embEllipse_init(EmbEllipse ellipse, unsigned int rgb, int lineType)
{
    printf("%f %d %d", ellipse.radius.x, rgb, lineType);
    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "Ellipse");

    setFlag(ItemIsSelectable, true);

    setSize(width, height);
    setCenter(centerX, centerY);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
    updatePath();
}
*/

void embEllipse_setSize(float width, float height)
{
    printf("%f %f", width, height);
    /*
    EmbRect elRect = rect();
    elRect.setWidth(width);
    elRect.setHeight(height);
    elRect.moveCenter(EmbVector(0,0));
    setRect(elRect);
    */
}

void embEllipse_setRadiusMajor(float radius)
{
    printf("%f", radius);
    /*
    setDiameterMajor(radius*2.0);
    */
}

void embEllipse_setRadiusMinor(float radius)
{
    printf("%f", radius);
    /*
    setDiameterMinor(radius*2.0);
    */
}

void embEllipse_setDiameterMajor(EmbEllipse *ellipse, float diameter)
{
    printf("%f %f", ellipse->radius.x, diameter);
    /*
    EmbRect elRect = rect();
    if (elRect.width() > elRect.height())
        elRect.setWidth(diameter);
    else
        elRect.setHeight(diameter);
    elRect.moveCenter(EmbVector(0,0));
    setRect(elRect);
    */
}

void embEllipse_setDiameterMinor(EmbEllipse *ellipse, float diameter)
{
    printf("%f %f", ellipse->center.x, diameter);
    /*
    EmbRect elRect = rect();
    if (elRect.width() < elRect.height())
        elRect.setWidth(diameter);
    else
        elRect.setHeight(diameter);
    elRect.moveCenter(EmbVector(0,0));
    setRect(elRect);
    */
}

EmbVector ellipse_objectQuadrant0(EmbEllipse *ellipse)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    printf("%f", ellipse->radius.x);
    /*
    float halfW = objectWidth()/2.0;
    float rot = radians(rotation());
    float x = halfW*cos(rot);
    float y = halfW*sin(rot);
    return objectCenter() + EmbVector(x,y);
    */
    return v;
}

EmbVector ellipse_objectQuadrant90(EmbEllipse *ellipse)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    printf("%f", ellipse->radius.x);
    /*
    float halfH = objectHeight()/2.0;
    float rot = radians(rotation()+90.0);
    float x = halfH * cos(rot);
    float y = halfH * sin(rot);
    return objectCenter() + EmbVector(x,y);
    */
    return v;
}

EmbVector ellipse_objectQuadrant180(EmbEllipse *ellipse)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    printf("%f", ellipse->radius.x);
    /*
    float halfW = objectWidth()/2.0;
    float rot = radians(rotation()+180.0);
    float x = halfW*cos(rot);
    float y = halfW*sin(rot);
    return objectCenter() + EmbVector(x,y);
    */
    return v;
}

EmbVector ellipse_objectQuadrant270(EmbEllipse *ellipse)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    printf("%f", ellipse->radius.x);
    /*
    float halfH = objectHeight()/2.0;
    float rot = radians(rotation()+270.0);
    float x = halfH*cos(rot);
    float y = halfH*sin(rot);
    return objectCenter() + EmbVector(x,y);
    */
    return v;
}

void embEllipse_updatePath()
{
    /*
    QPainterPath path;
    EmbRect r = rect();
    path.arcMoveTo(r, 0);
    path.arcTo(r, 0, 360);
    //NOTE: Reverse the path so that the inside area isn't considered part of the ellipse
    path.arcTo(r, 0, -360);
    setPath(path);
    */
}

/*
void embEllipse_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawEllipse(rect());
}
*/

/*
void embEllipse_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_ELLIPSE_LINE) {
        EmbVector sceneLinePoint1 = objectRubberPoint("ELLIPSE_LINE_POINT1");
        EmbVector sceneLinePoint2 = objectRubberPoint("ELLIPSE_LINE_POINT2");
        EmbVector itemLinePoint1  = mapFromScene(sceneLinePoint1);
        EmbVector itemLinePoint2  = mapFromScene(sceneLinePoint2);
        EmbLine itemLine(itemLinePoint1, itemLinePoint2);
        if (painter) drawRubberLine(itemLine, painter, VIEW_COLOR_CROSSHAIR);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_ELLIPSE_MAJORDIAMETER_MINORRADIUS) {
        EmbVector sceneAxis1Point1 = objectRubberPoint("ELLIPSE_AXIS1_POINT1");
        EmbVector sceneAxis1Point2 = objectRubberPoint("ELLIPSE_AXIS1_POINT2");
        EmbVector sceneCenterPoint = objectRubberPoint("ELLIPSE_CENTER");
        EmbVector sceneAxis2Point2 = objectRubberPoint("ELLIPSE_AXIS2_POINT2");
        float ellipseWidth = objectRubberPoint("ELLIPSE_WIDTH").x();
        float ellipseRot = objectRubberPoint("ELLIPSE_ROT").x();

        //TODO: incorporate perpendicularDistance() into libcgeometry
        float px = sceneAxis2Point2.x();
        float py = sceneAxis2Point2.y();
        float x1 = sceneAxis1Point1.x();
        float y1 = sceneAxis1Point1.y();
        EmbLine line(sceneAxis1Point1, sceneAxis1Point2);
        EmbLine norm = line.normalVector();
        float dx = px-x1;
        float dy = py-y1;
        norm.translate(dx, dy);
        EmbVector iPoint;
        norm.intersects(line, &iPoint);
        float ellipseHeight = EmbLine(px, py, iPoint.x(), iPoint.y()).length()*2.0;

        setCenter(sceneCenterPoint);
        setSize(ellipseWidth, ellipseHeight);
        setRotation(-ellipseRot);

        EmbVector itemCenterPoint = mapFromScene(sceneCenterPoint);
        EmbVector itemAxis2Point2 = mapFromScene(sceneAxis2Point2);
        EmbLine itemLine(itemCenterPoint, itemAxis2Point2);
        if (painter) drawRubberLine(itemLine, painter, VIEW_COLOR_CROSSHAIR);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_ELLIPSE_MAJORRADIUS_MINORRADIUS) {
        EmbVector sceneAxis1Point2 = objectRubberPoint("ELLIPSE_AXIS1_POINT2");
        EmbVector sceneCenterPoint = objectRubberPoint("ELLIPSE_CENTER");
        EmbVector sceneAxis2Point2 = objectRubberPoint("ELLIPSE_AXIS2_POINT2");
        float ellipseWidth = objectRubberPoint("ELLIPSE_WIDTH").x();
        float ellipseRot = objectRubberPoint("ELLIPSE_ROT").x();

        //TODO: incorporate perpendicularDistance() into libcgeometry
        float px = sceneAxis2Point2.x();
        float py = sceneAxis2Point2.y();
        float x1 = sceneCenterPoint.x();
        float y1 = sceneCenterPoint.y();
        EmbLine line(sceneCenterPoint, sceneAxis1Point2);
        EmbLine norm = line.normalVector();
        float dx = px-x1;
        float dy = py-y1;
        norm.translate(dx, dy);
        EmbVector iPoint;
        norm.intersects(line, &iPoint);
        float ellipseHeight = EmbLine(px, py, iPoint.x(), iPoint.y()).length()*2.0;

        setCenter(sceneCenterPoint);
        setSize(ellipseWidth, ellipseHeight);
        setRotation(-ellipseRot);

        EmbVector itemCenterPoint = mapFromScene(sceneCenterPoint);
        EmbVector itemAxis2Point2 = mapFromScene(sceneAxis2Point2);
        EmbLine itemLine(itemCenterPoint, itemAxis2Point2);
        if (painter) drawRubberLine(itemLine, painter, VIEW_COLOR_CROSSHAIR);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        //TODO: updateRubber() gripping for EllipseObject
    }
}
*/

/*
// Returns the closest snap point to the mouse point
EmbVector ellipse_mouseSnapPoint(const EmbVector& mousePoint)
{
    EmbVector center  = objectCenter();
    EmbVector quad0   = objectQuadrant0();
    EmbVector quad90  = objectQuadrant90();
    EmbVector quad180 = objectQuadrant180();
    EmbVector quad270 = objectQuadrant270();

    float cntrDist = EmbLine(mousePoint, center).length();
    float q0Dist   = EmbLine(mousePoint, quad0).length();
    float q90Dist  = EmbLine(mousePoint, quad90).length();
    float q180Dist = EmbLine(mousePoint, quad180).length();
    float q270Dist = EmbLine(mousePoint, quad270).length();

    float minDist = std::min(std::min(std::min(q0Dist, q90Dist), std::min(q180Dist, q270Dist)), cntrDist);

    if     (minDist == cntrDist) return center;
    else if (minDist == q0Dist)   return quad0;
    else if (minDist == q90Dist)  return quad90;
    else if (minDist == q180Dist) return quad180;
    else if (minDist == q270Dist) return quad270;

    return scenePos();
}
*/

/*
std::vector<EmbVector> ellipse_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << objectCenter() << objectQuadrant0() << objectQuadrant90() << objectQuadrant180() << objectQuadrant270();
    return gripPoints;
}
*/

/*
void embEllipse_gripEdit(const EmbVector& before, const EmbVector& after)
{
    //TODO: gripEdit() for EllipseObject
}
*/

/*
QPainterPath ellipse_objectSavePath()
{
    QPainterPath path;
    EmbRect r = rect();
    path.arcMoveTo(r, 0);
    path.arcTo(r, 0, 360);

    float s = scale();
    QTransform trans;
    trans.rotate(rotation());
    trans.scale(s,s);
    return trans.map(path);
}
*/
