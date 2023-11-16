/*
 * TEXT GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../embroidery.h"


//NOTE: This void should be used to interpret various object types and save them as polylines for stitchOnly formats.
/*
void save_toPolyline(EmbPattern* pattern, const EmbVector& objPos, const QPainterPath& objPath, const std::string& layer, const QColor& color, const std::string& lineType, const std::string& lineWeight)
{
    float startX = objPos.x();
    float startY = objPos.y();
    EmbArray *pointList = embArray_create(EMB_POINT);
    EmbPoint lastPoint;
    QPainterPath::Element element;
    for (int i = 0; i < objPath.elementCount(); ++i) {
        element = objPath.elementAt(i);
        if (pointList->count == 0) {
            lastPoint.position.x = element.x + startX;
            lastPoint.position.y = -(element.y + startY);
            embArray_addPoint(pointList, lastPoint);
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
    embPattern_addPolylineAbs(pattern, polyObject);
}

void textSingle_TextSingleObject(const std::string& str, float x, float y, unsigned int rgb, QGraphicsItem* parent)
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

void textSingle_init(const std::string& str, float x, float y, unsigned int rgb, int lineType)
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
*/

/*
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
*/

/*
void textSingle_setText(const std::string& str)
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

void
textSingle_setTextFont(const char *font)
{
    /*
    objTextFont = font;
    setText(objText);
    */
}

void
textSingle_setJustify(const char *justify)
{
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

void textSingle_setTextSize(float size)
{
    /*
    objTextSize = size;
    setText(objText);
    */
}

void textSingle_setTextStyle(char bold, char italic, char under, char strike, char over)
{
    printf("%d %d %d %d %d", bold, italic, under, strike, over);
    /*
    objTextBold = bold;
    objTextItalic = italic;
    objTextUnderline = under;
    objTextStrikeOut = strike;
    objTextOverline = over;
    setText(objText);
    */
}

void textSingle_setTextBold(char val)
{
    printf("%d", val);
    /*
    objTextBold = val;
    setText(objText);
    */
}

void textSingle_setTextItalic(char val)
{
    printf("%d", val);
    /*
    objTextItalic = val;
    setText(objText);
    */
}

void textSingle_setTextUnderline(char val)
{
    printf("%d", val);
    /*
    objTextUnderline = val;
    setText(objText);
    */
}

void textSingle_setTextStrikeOut(char val)
{
    printf("%d", val);
    /*
    objTextStrikeOut = val;
    setText(objText);
    */
}

void textSingle_setTextOverline(char val)
{
    printf("%d", val);
    /*
    objTextOverline = val;
    setText(objText);
    */
}

void textSingle_setTextBackward(char val)
{
    printf("%d", val);
    /*
    objTextBackward = val;
    setText(objText);
    */
}

void textSingle_setTextUpsideDown(char val)
{
    printf("%d", val);
    /*
    objTextUpsideDown = val;
    setText(objText);
    */
}

void textSingle_paint() // QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    /*
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).tochar()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawPath(objTextPath);
    */
}

void textSingle_updateRubber() // QPainter* painter)
{
    /*
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_TEXTSINGLE) {
        setTextFont(objectRubberText("TEXT_FONT"));
        setTextJustify(objectRubberText("TEXT_JUSTIFY"));
        setPos(objectRubberPoint("TEXT_POINT"));
        EmbVector hr = objectRubberPoint("TEXT_HEIGHT_ROTATION");
        setTextSize(hr.x());
        setRotation(hr.y());
        setText(objectRubberText("TEXT_RAPID"));
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if (gripPoint == scenePos()) {
                painter->drawPath(objectPath().translated(mapFromScene(objectRubberPoint(std::string()))-mapFromScene(gripPoint)));
            }

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
        }
    }
    */
}

// Returns the closest snap point to the mouse point
EmbVector textSingle_mouseSnapPoint(EmbVector mousePoint)
{
    EmbVector v = {0.0, 0.0};
    printf("%f %f", mousePoint.x, mousePoint.y);
    //return scenePos();
    return v;
}

/*
std::vector<EmbVector> textSingle_allGripPoints()
{
    std::vector<EmbVector> gripPoints = {};
    // scenePos();
    return gripPoints;
}
*/

void textSingle_gripEdit(EmbVector before, EmbVector after)
{
    printf("%f %f", before.x, after.x);
    /*
    if (before == scenePos()) {
        EmbVector delta = after-before;
        moveBy(delta.x(), delta.y());
    }
    */
}

/*
std::vector<QPainterPath> text_single_subPathList()
{
    float s = scale();
    QTransform trans;
    trans.rotate(rotation());
    trans.scale(s,s);

    std::vector<QPainterPath> pathList;

    QPainterPath path = objTextPath;

    QPainterPath::Element element;
    std::vector<int> pathMoves;
    int numMoves = 0;

    for (int i = 0; i < path.elementCount(); i++) {
        element = path.elementAt(i);
        if (element.isMoveTo()) {
            pathMoves << i;
            numMoves++;
        }
    }

    pathMoves << path.elementCount();

    for (int p = 0; p < pathMoves.size()-1 && p < numMoves; p++) {
        QPainterPath subPath;
        for (int i = pathMoves.value(p); i < pathMoves.value(p+1); i++) {
            element = path.elementAt(i);
            if (element.isMoveTo()) {
                subPath.moveTo(element.x, element.y);
            }
            else if (element.isLineTo()) {
                subPath.lineTo(element.x, element.y);
            }
            else if (element.isCurveTo()) {
                subPath.cubicTo(path.elementAt(i  ).x, path.elementAt(i  ).y,  //control point 1
                                path.elementAt(i+1).x, path.elementAt(i+1).y,  //control point 2
                                path.elementAt(i+2).x, path.elementAt(i+2).y); //end point
            }
        }
        pathList.append(trans.map(subPath));
    }

    return pathList;
}
*/
