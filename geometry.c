/*
 * GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

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
/*
 * ARC GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * ------------------------------------------------------------
 *
 * Use Python's PEP7 style guide.
 *     https://peps.python.org/pep-0007/
 *
 * ------------------------------------------------------------
 *
 * The EmbArc is implicitly an elliptical arc not a circular one
 * because of our need to cover all of the SVG spec. Note that
 * the circlar arcs are a subset of the elliptical arcs.
 *
 * TODO: some of these formulae may assume that the arc is circular,
 * correct for elliptic versions.
 */

/* Returns an EmbArcObject. It is created on the stack.
 *
 * Note that the default arc is the semicircular arc of the circle of radius
 * arc.
 */
EmbArc
embArc_init(void)
{
    EmbArc arc;
    arc.start.x = 0.0;
    arc.start.y = -1.0;
    arc.mid.x = 1.0;
    arc.mid.y = 0.0;
    arc.end.x = 0.0;
    arc.end.y = 1.0;
    return arc;
}

/* Calculus based approach at determining whether a polygon is clockwise or counterclockwise.
 * Returns true if arc is clockwise. */
char
embArc_clockwise(EmbArc arc)
{
    EmbReal edge1 = (arc.mid.x-arc.start.x)*(arc.mid.y+arc.start.y);
    EmbReal edge2 = (arc.end.x-arc.mid.x)*(arc.end.y+arc.mid.y);
    EmbReal edge3 = (arc.start.x-arc.end.x)*(arc.start.y+arc.end.y);
    if (edge1 + edge2 + edge3 >= 0.0) {
        return 1;
    }
    return 0;
}

/* Calculates the CenterPoint of the Arc */
EmbVector
embArc_center(EmbArc arc)
{
    EmbVector center;
    EmbVector a_vec, b_vec, aMid_vec, bMid_vec, aPerp_vec, bPerp_vec, pa, pb;
    EmbLine line1, line2;
    EmbReal paAngleInRadians, pbAngleInRadians;
    a_vec = embVector_subtract(arc.mid, arc.start);
    aMid_vec = embVector_average(arc.mid, arc.start);

    paAngleInRadians = embVector_angle(a_vec) + (embConstantPi/2.0);
    pa = embVector_unit(paAngleInRadians);
    aPerp_vec = embVector_add(aMid_vec, pa);

    b_vec = embVector_subtract(arc.end, arc.mid);
    bMid_vec = embVector_average(arc.end, arc.mid);

    pbAngleInRadians = embVector_angle(b_vec) + (embConstantPi/2.0);
    pb = embVector_unit(pbAngleInRadians);
    bPerp_vec = embVector_add(bMid_vec, pb);

    line1.start = aMid_vec;
    line1.end = aPerp_vec;
    line2.start = bMid_vec;
    line2.end = bPerp_vec;
    center = embLine_intersectionPoint(line1, line2);
    if (emb_error) {
        puts("ERROR: no intersection, cannot find arcCenter.");
    }
    return center;
}

/* Calculate the Radius */
EmbReal
embArc_radius(EmbArc arc)
{
    EmbReal incAngle = embArc_incAngle(arc);
    EmbReal chord = embArc_chord(arc);
    return fabs(chord / (2.0 * sin(incAngle / 2.0)));
}

/* Calculate the Diameter */
EmbReal
embArc_diameter(EmbArc arc)
{
    return fabs(embArc_radius(arc) * 2.0);
}

/* Calculate the Chord Angle (from arc.start to arc.end). */
EmbReal
embArc_chordAngle(EmbArc arc)
{
    EmbVector delta = embVector_subtract(arc.end, arc.start);
    return atan2(delta.y, delta.x);
}

/* . */
EmbReal
embArc_chord(EmbArc arc)
{
    return embVector_distance(arc.start, arc.end);
}

/* Calculate the Chord MidPoint. */
EmbVector
embArc_chordMid(EmbArc arc)
{
    return embVector_scale(embVector_add(arc.start, arc.end), 0.5);
}

/* Calculate the Sagitta. */
EmbReal
embArc_sagitta(EmbArc arc)
{
    EmbReal chord = embArc_chord(arc);
    EmbReal bulge = embArc_bulge(arc);
    return fabs((chord / 2.0) * bulge);
}

/* Calculate the Apothem */
EmbReal
embArc_apothem(EmbArc arc)
{
    return fabs(embArc_radius(arc) - embArc_sagitta(arc));
}

/* Calculate the Included Angle. */
EmbReal
embArc_incAngle(EmbArc arc)
{
    return atan(embArc_bulge(arc))*4.0;
}

/* TODO: fixme */
EmbReal
embArc_bulge(EmbArc arc)
{
    return 1.0;
}

/* Calculates Arc Geometry from Bulge Data.
 * Returns false if there was an error calculating the data.
    Calculate the Sagitta Angle (from chordMid to arcMid)
    if (*clockwise) sagittaAngleInRadians = chordAngleInRadians + radians(90.0);
    else           sagittaAngleInRadians = chordAngleInRadians - radians(90.0);

    Calculate the Arc MidPoint
    fx = embArc_sagitta(arc) * cos(sagittaAngleInRadians);
    fy = embArc_sagitta(arc) * sin(sagittaAngleInRadians);
    arc->mid.x = *chordMidX + fx;
    arc->mid.y = *chordMidY + fy;

    Convert the Included Angle from Radians to Degrees
    *incAngleInDegrees = degrees(incAngleInRadians);

    return 1;
}
 */

void
embArc_setCenter(EmbArc *arc, EmbVector point)
{
    EmbVector delta;
    EmbVector old_center = embArc_center(*arc);
    delta = embVector_subtract(point, old_center);
    arc->start = embVector_add(arc->start, delta);
    arc->mid = embVector_add(arc->mid, delta);
    arc->end = embVector_add(arc->end, delta);
}

void
embArc_setRadius(EmbArc *arc, float radius)
{
    EmbVector delta;
    float rad;
    if (radius <= 0.0f) {
        rad = 0.0000001f;
    }
    else {
        rad = radius;
    }

    EmbVector center = embArc_center(*arc);
    double delta_length;

    delta = embVector_subtract(arc->start, center);
    delta_length = embVector_length(delta);
    delta = embVector_scale(delta, rad/delta_length);
    arc->start = embVector_add(center, delta);

    delta = embVector_subtract(arc->mid, center);
    delta_length = embVector_length(delta);
    delta = embVector_scale(delta, rad/delta_length);
    arc->mid = embVector_add(center, delta);

    delta = embVector_subtract(arc->end, center);
    delta_length = embVector_length(delta);
    delta = embVector_scale(delta, rad/delta_length);
    arc->end = embVector_add(center, delta);
}

void
embArc_setStartAngle(EmbArc *arc, float angle)
{
    printf("%f %f", arc->start.x, angle);
    //TODO: ArcObject setStartAngle
}

void
embArc_setEndAngle(EmbArc *arc, float angle)
{
    printf("%f %f", arc->start.x, angle);
    //TODO: ArcObject setEndAngle
}

EmbReal
embArc_startAngle(EmbArc arc)
{
    EmbVector delta;
    EmbVector center = embArc_center(arc);
    delta = embVector_subtract(arc.end, center);
    float angle = embVector_angle(delta);
    return fmodf(angle, 360.0);
}

EmbReal
embArc_endAngle(EmbArc arc)
{
    EmbVector delta;
    EmbVector center = embArc_center(arc);
    delta = embVector_subtract(arc.end, center);
    float angle = embVector_angle(delta);
    return fmodf(angle, 360.0);
}

EmbReal
embArc_area(EmbArc arc)
{
    printf("%f", arc.start.x);
    /*
    // Area of a circular segment
    float r = objectRadius();
    float theta = radians(objectIncludedAngle());
    return ((r*r)/2)*(theta - sin(theta));
    */
    return 0.0;
}

EmbReal
embArc_arcLength(EmbArc arc)
{
    printf("%f", arc.start.x);
    /*
    return radians(objectIncludedAngle())*objectRadius();
    */
    return 0.0;
}

EmbReal
embArc_includedAngle(EmbArc arc)
{
    printf("%f", arc.start.x);
    /*
    float chord = objectChord();
    float rad = objectRadius();
    if (chord <= 0 || rad <= 0) return 0; //Prevents division by zero and non-existant circles

    //NOTE: Due to floating point rounding errors, we need to clamp the quotient so it is in the range [-1, 1]
    //      If the quotient is out of that range, then the result of asin() will be NaN.
    float quotient = chord/(2.0*rad);
    if (quotient > 1.0) {
        quotient = 1.0;
    }
    if (quotient < 0.0) {
        quotient = 0.0;
    }
    // NOTE: 0 rather than -1 since we are enforcing a positive chord and radius
    return degrees(2.0*asin(quotient));
    // Properties of a Circle - Get the Included Angle - Reference: ASD9
    */
    return 0.0;
}

char Arc_clockwise()
{
    /*
    // NOTE: Y values are inverted here on purpose
    EmbArc arc2 = arc;
    arc2.start.y *= -1.0;
    arc2.mid.y *= -1.0;
    arc2.end.y *= -1.0;

    return embArc_clockwise(arc2);
    */
    return 0;
}

void embArc_updatePath(EmbArc arc)
{
    printf("%f", arc.start.x);
    /*
    float startAngle = (objectStartAngle() + rotation());
    float spanAngle = objectIncludedAngle();

    if (objectClockwise()) {
        spanAngle = -spanAngle;
    }

    QPainterPath path;
    path.arcMoveTo(rect(), startAngle);
    path.arcTo(rect(), startAngle, spanAngle);
    //NOTE: Reverse the path so that the inside area isn't considered part of the arc
    path.arcTo(rect(), startAngle+spanAngle, -spanAngle);
    setPath(path);
    */
}

void embArc_paint(void)
{
    // QPainter* painter, QStyleOptionGraphicsItem* option, QWidget* widget
    /*
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    float startAngle = (objectStartAngle() + rotation())*16;
    float spanAngle = objectIncludedAngle()*16;

    if (objectClockwise())
        spanAngle = -spanAngle;

    float rad = objectRadius();
    EmbRect paintRect(-rad, -rad, rad*2.0, rad*2.0);
    painter->drawArc(paintRect, startAngle, spanAngle);
    */
}

void embArc_updateRubber(EmbArc arc, int pattern, int layer, int index)
{
    //TODO: Arc Rubber Modes

    //TODO: updateRubber() gripping for ArcObject

}

// Returns the closest snap point to the mouse point
EmbVector embArc_mouseSnapPoint(EmbArc arc, EmbVector mousePoint)
{
    printf("%f", arc.start.x);
    printf("%f", mousePoint.x);
    /*
    EmbVector center = objectCenter();
    EmbVector start  = objectStartPoint();
    EmbVector mid    = objectMidPoint();
    EmbVector end    = objectEndPoint();

    float cntrDist  = EmbLine(mousePoint, center).length();
    float startDist = EmbLine(mousePoint, start).length();
    float midDist   = EmbLine(mousePoint, mid).length();
    float endDist   = EmbLine(mousePoint, end).length();

    float minDist = std::min(std::min(cntrDist, startDist), std::min(midDist, endDist));

    if     (minDist == cntrDist)  return center;
    else if (minDist == startDist) return start;
    else if (minDist == midDist)   return mid;
    else if (minDist == endDist)   return end;

    return scenePos();
    */
    return mousePoint;
}

/*
std::vector<EmbVector> embArc_allGripPoints(EmbArc arc)
{
    EmbVector center = embArc_center(arc);
    std::vector<EmbVector> gripPoints = {center, arc.start, arc.mid, arc.end};
    return gripPoints;
}
*/

void embArc_gripEdit(EmbArc *arc, EmbVector before, EmbVector after)
{
    printf("%f %f %f", arc->start.x, before.x, after.x);
    // TODO: gripEdit() for ArcObject
}

void set_object_color(EmbGeometry *obj, EmbColor color)
{
    obj->color = color;
    /*
    objPen.setColor(color);
    lwtPen.setColor(color);
    */
}

void embGeometry_setColorRGB(EmbGeometry *obj, unsigned int rgb)
{
    printf("%d", rgb);
    /*
    objPen.setColor(QColor(rgb));
    lwtPen.setColor(QColor(rgb));
    */
}

void embGeometry_setLineType(EmbGeometry *obj, int lineType)
{
    printf("%d", lineType);
    /*
    objPen.setStyle(lineType);
    lwtPen.setStyle(lineType);
    */
}

void embGeometry_setLineWeight(EmbGeometry *obj, float lineWeight)
{
    printf("%f", lineWeight);
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

EmbVector
Base_objectRubberPoint(EmbGeometry *obj, const char *key)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    printf("%s", key);
    /*
    if (objRubberPoints.contains(key)) {
        return objRubberPoints.value(key);
    }

    QGraphicsScene* gscene = scene();
    if (gscene) {
        return scene()->property("SCENE_QSNAP_POINT").toPointF();
    }
    */
    return v;
}

const char *
Base_objectRubberText(EmbGeometry *obj, const char *key)
{
    printf("%s", key);
    /*
    if (objRubberTexts.contains(key))
        return objRubberTexts.value(key);
    */
    return "";
}

/*
void embGeometry_drawRubberLine(const EmbLine& rubLine, QPainter* painter, const char* colorFromScene)
{
    if (painter) {
        QGraphicsScene* objScene = scene();
        if (!objScene) return;
        QPen colorPen = objPen;
        colorPen.setColor(QColor(objScene->property(colorFromScene).toUInt()));
        painter->setPen(colorPen);
        painter->drawLine(rubLine);
        painter->setPen(objPen);
    }
}

void embGeometry_realRender(QPainter* painter, const QPainterPath& renderPath)
{
    QColor color1 = objectColor();       //lighter color
    QColor color2  = color1.darker(150); //darker color

    //If we have a dark color, lighten it
    int darkness = color1.lightness();
    int threshold = 32; //TODO: This number may need adjusted or maybe just add it to settings.
    if (darkness < threshold) {
        color2 = color1;
        if (!darkness) { color1 = QColor(threshold, threshold, threshold); } //lighter() does not affect pure black
        else          { color1 = color2.lighter(100 + threshold); }
    }

    int count = renderPath.elementCount();
    for (int i = 0; i < count-1; ++i) {
        QPainterPath::Element elem = renderPath.elementAt(i);
        QPainterPath::Element next = renderPath.elementAt(i+1);

        if (next.isMoveTo()) continue;

        QPainterPath elemPath;
        elemPath.moveTo(elem.x, elem.y);
        elemPath.lineTo(next.x, next.y);

        QPen renderPen(QColor(0,0,0,0));
        renderPen.setWidthF(0);
        painter->setPen(renderPen);
        QPainterPathStroker stroker;
        stroker.setWidth(0.35);
        stroker.setCapStyle(RoundCap);
        stroker.setJoinStyle(RoundJoin);
        QPainterPath realPath = stroker.createStroke(elemPath);
        painter->drawPath(realPath);

        QLinearGradient grad(elemPath.pointAtPercent(0.5), elemPath.pointAtPercent(0.0));
        grad.setColorAt(0, color1);
        grad.setColorAt(1, color2);
        grad.setSpread(QGradient::ReflectSpread);

        painter->fillPath(realPath, QBrush(grad));
    }
}

void embCircle_main()
{
    initCommand();
    clearSelection();
    view.ui_mode = "CIRCLE_MODE_1P_RAD";
    global.x1 = NaN;
    global.y1 = NaN;
    global.x2 = NaN;
    global.y2 = NaN;
    global.x3 = NaN;
    global.y3 = NaN;
    setPromptPrefix(translate("Specify center point for circle or [3P/2P/Ttr (tan tan radius)]: "));
}
*/

void embCircle_prompt(const char *str)
{
    /*
    if (view.ui_mode == "CIRCLE_MODE_1P_RAD") {
        if (std::isnan(global.x1)) {
            if (str == "2P") {
                //TODO: Probably should add additional qsTr calls here.
                view.ui_mode = "CIRCLE_MODE_2P";
                setPromptPrefix(translate("Specify first end point of circle's diameter: "));
            }
            else if (str == "3P") {
                view.ui_mode = "CIRCLE_MODE_3P";
                setPromptPrefix(translate("Specify first point of circle: "));
            }
            else if (str == "T" || str == "TTR")  {
                view.ui_mode = "CIRCLE_MODE_TTR";
                setPromptPrefix(translate("Specify point on object for first tangent of circle: "));
            }
            else {
                std::vector<std::string> strList = str.split(",");
                if (std::isnan(strList[0]) || isnan(strList[1])) {
                    alert(translate("Point or option keyword required."));
                    setPromptPrefix(translate("Specify center point for circle or [3P/2P/Ttr (tan tan radius)]: "));
                }
                else {
                    global.x1 = Number(strList[0]);
                    global.y1 = Number(strList[1]);
                    global.cx = global.x1;
                    global.cy = global.y1;
                    addRubber("CIRCLE");
                    setRubberMode("CIRCLE_1P_RAD");
                    setRubberPoint("CIRCLE_CENTER", global.cx, global.cy);
                    setPromptPrefix(translate("Specify radius of circle or [Diameter]: "));
                }
            }
        }
        else {
            if (str == "D" || str == "DIAMETER") {
                //TODO: Probably should add additional translate calls here.
                view.ui_mode = "CIRCLE_MODE_1P_DIA";
                setRubberMode("CIRCLE_1P_DIA");
                setPromptPrefix(translate("Specify diameter of circle: "));
            }
            else {
                float num = Number(str);
                if (std::isnan(num)) {
                    alert(translate("Requires numeric radius, point on circumference, or \"D\"."));
                    setPromptPrefix(translate("Specify radius of circle or [Diameter]: "));
                }
                else {
                    global.rad = num;
                    global.x2 = global.x1 + global.rad;
                    global.y2 = global.y1;
                    setRubberPoint("CIRCLE_RADIUS", global.x2, global.y2);
                    vulcanize();
                    endCommand();
                }
            }
        }
    }
    else if (view.ui_mode == MODE_1P_DIA) {
        if (std::isnan(global.x1)) {
            error("CIRCLE", translate("This should never happen."));
        }
        if (std::isnan(global.x2)) {
            float num = Number(str);
            if (std::isnan(num)) {
                alert(translate("Requires numeric distance or second point."));
                setPromptPrefix(translate("Specify diameter of circle: "));
            }
            else {
                global.dia = num;
                global.x2 = global.x1 + global.dia;
                global.y2 = global.y1;
                setRubberPoint("CIRCLE_DIAMETER", global.x2, global.y2);
                vulcanize();
                endCommand();
            }
        }
        else {
            error("CIRCLE", translate("This should never happen."));
        }
    }
    else if (view.ui_mode == MODE_2P) {
        if (std::isnan(global.x1)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify first end point of circle's diameter: "));
            }
            else {
                global.x1 = Number(strList[0]);
                global.y1 = Number(strList[1]);
                addRubber("CIRCLE");
                setRubberMode("CIRCLE_2P");
                setRubberPoint("CIRCLE_TAN1", global.x1, global.y1);
                setPromptPrefix(translate("Specify second end point of circle's diameter: "));
            }
        }
        else if (std::isnan(global.x2)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify second end point of circle's diameter: "));
            }
            else {
                global.x2 = Number(strList[0]);
                global.y2 = Number(strList[1]);
                setRubberPoint("CIRCLE_TAN2", global.x2, global.y2);
                vulcanize();
                endCommand();
            }
        }
        else {
            error("CIRCLE", translate("This should never happen."));
        }
    }
    else if (view.ui_mode == MODE_3P) {
        if (std::isnan(global.x1)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify first point of circle: "));
            }
            else {
                global.x1 = Number(strList[0]);
                global.y1 = Number(strList[1]);
                setPromptPrefix(translate("Specify second point of circle: "));
            }
        }
        else if (std::isnan(global.x2)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify second point of circle: "));
            }
            else {
                global.x2 = Number(strList[0]);
                global.y2 = Number(strList[1]);
                addRubber("CIRCLE");
                setRubberMode("CIRCLE_3P");
                setRubberPoint("CIRCLE_TAN1", global.x1, global.y1);
                setRubberPoint("CIRCLE_TAN2", global.x2, global.y2);
                setPromptPrefix(translate("Specify third point of circle: "));
            }
        }
        else if (std::isnan(global.x3)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify third point of circle: "));
            }
            else {
                global.x3 = Number(strList[0]);
                global.y3 = Number(strList[1]);
                setRubberPoint("CIRCLE_TAN3", global.x3, global.y3);
                vulcanize();
                endCommand();
            }
        }
        else {
            error("CIRCLE", translate("This should never happen."));
        }

    }
    else if (view.ui_mode == MODE_TTR) {
        todo("CIRCLE", "prompt() for TTR");
    }
    */
}

/*
void embCircle_CircleObject(EmbVector center, float radius, unsigned int rgb)
{
    if (n_views == 0) {
        return;
    }

    View view = views[settings.pattern_index];

    debug_message("CircleObject Constructor()");
    init(centerX, centerY, radius, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void embCircle_CircleObject(EmbCircle* obj)
{
    debug_message("CircleObject Constructor()");
    if (obj) {
        init(obj->objectCenterX(), obj->objectCenterY(), obj->objectRadius(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
    }
}

void embCircle_init(EmbVector center, float radius, unsigned int rgb, int lineType)
{
    if (n_views == 0) {
        return;
    }

    View view = views[settings.pattern_index];

    setData(OBJ_TYPE, type);
    setData(OBJ_NAME, "CIRCLE");

    setFlag(ItemIsSelectable, true);

    setRadius(radius);
    setCenter(centerX, centerY);
    setColor(rgb);
    setLineType(lineType);
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objectPen());
    updatePath();
}

void embCircle_setDiameter(EmbCircle *circle, float diameter)
{
    if (n_views == 0) {
        return;
    }

    View view = views[settings.pattern_index];

    circle->radius = diameter*0.5;
    EmbRect circRect;
    circRect.setWidth(diameter);
    circRect.setHeight(diameter);
    circRect.moveCenter(EmbVector(0,0));
    setRect(circRect);
    updatePath();
}
*/

void embCircle_setArea(EmbCircle *circle, float area)
{
    circle->radius = sqrt(area / embConstantPi);
}

void embCircle_setCircumference(EmbCircle *circle, float circumference)
{
    circle->radius = circumference / (2.0*embConstantPi);
}

/*
void embCircle_updatePath()
{
    QPainterPath path;
    EmbRect r = rect();
    //Add the center point
    path.addRect(-0.00000001, -0.00000001, 0.00000002, 0.00000002);
    //Add the circle
    path.arcMoveTo(r, 0);
    path.arcTo(r, 0, 360);
    //NOTE: Reverse the path so that the inside area isn't considered part of the circle
    path.arcTo(r, 0, -360);
    setPath(path);
}

void embCircle_paint(QPainter* painter)
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

void embCircle_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_CIRCLE_1P_RAD) {
        EmbVector sceneCenterPoint = objectRubberPoint("CIRCLE_CENTER");
        EmbVector sceneQSnapPoint = objectRubberPoint("CIRCLE_RADIUS");
        EmbVector itemCenterPoint = mapFromScene(sceneCenterPoint);
        EmbVector itemQSnapPoint = mapFromScene(sceneQSnapPoint);
        EmbLine itemLine(itemCenterPoint, itemQSnapPoint);
        setCenter(sceneCenterPoint);
        EmbLine sceneLine(sceneCenterPoint, sceneQSnapPoint);
        float radius = sceneLine.length();
        setRadius(radius);
        if (painter) drawRubberLine(itemLine, painter, VIEW_COLOR_CROSSHAIR);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_CIRCLE_1P_DIA) {
        EmbVector sceneCenterPoint = objectRubberPoint("CIRCLE_CENTER");
        EmbVector sceneQSnapPoint = objectRubberPoint("CIRCLE_DIAMETER");
        EmbVector itemCenterPoint = mapFromScene(sceneCenterPoint);
        EmbVector itemQSnapPoint = mapFromScene(sceneQSnapPoint);
        EmbLine itemLine(itemCenterPoint, itemQSnapPoint);
        setCenter(sceneCenterPoint);
        EmbLine sceneLine(sceneCenterPoint, sceneQSnapPoint);
        float diameter = sceneLine.length();
        setDiameter(diameter);
        if (painter) drawRubberLine(itemLine, painter, VIEW_COLOR_CROSSHAIR);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_CIRCLE_2P) {
        EmbVector sceneTan1Point = objectRubberPoint("CIRCLE_TAN1");
        EmbVector sceneQSnapPoint = objectRubberPoint("CIRCLE_TAN2");
        EmbLine sceneLine(sceneTan1Point, sceneQSnapPoint);
        setCenter(sceneLine.pointAt(0.5));
        float diameter = sceneLine.length();
        setDiameter(diameter);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_CIRCLE_3P) {
        EmbVector sceneTan1Point = objectRubberPoint("CIRCLE_TAN1");
        EmbVector sceneTan2Point = objectRubberPoint("CIRCLE_TAN2");
        EmbVector sceneTan3Point = objectRubberPoint("CIRCLE_TAN3");

        float sceneCenterX;
        float sceneCenterY;
        EmbArc arc;
        EmbVector sceneCenter;
        arc.start.x = sceneTan1Point.x();
        arc.start.y = sceneTan1Point.y();
        arc.mid.x = sceneTan2Point.x();
        arc.mid.y = sceneTan2Point.y();
        arc.end.x = sceneTan3Point.x();
        arc.end.y = sceneTan3Point.y();
        embArc_center(arc, &sceneCenter);
        EmbVector sceneCenterPoint(sceneCenter.x, sceneCenter.y);
        EmbLine sceneLine(sceneCenterPoint, sceneTan3Point);
        setCenter(sceneCenterPoint);
        float radius = sceneLine.length();
        setRadius(radius);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if (gripPoint == objectCenter()) {
                painter->drawEllipse(rect().translated(mapFromScene(objectRubberPoint(std::string()))-mapFromScene(gripPoint)));
            }
            else {
                float gripRadius = EmbLine(objectCenter(), objectRubberPoint(std::string())).length();
                painter->drawEllipse(EmbVector(), gripRadius, gripRadius);
            }

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
        }
    }
}

// Returns the closest snap point to the mouse point
EmbVector Circle_mouseSnapPoint(EmbVector& mousePoint)
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
std::vector<EmbVector> Circle_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << objectCenter() << objectQuadrant0() << objectQuadrant90() << objectQuadrant180() << objectQuadrant270();
    return gripPoints;
}
*/

/*
void embCircle_gripEdit(EmbVector& before, EmbVector& after)
{
    if (before == objectCenter()) {
        EmbVector delta = after-before;
        moveBy(delta.x(), delta.y());
    }
    else {
        setRadius(EmbLine(objectCenter(), after).length());
    }
}
*/

/*
QPainterPath Circle_objectSavePath()
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

/*
void dim_leader_init(EmbLine line, unsigned int rgb, int lineType)
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
    setLineWeight(0.35); //TODO: pass in proper lineweight
    setPen(objPen);
}
*/

/*
void dimleader_setEndPoint1(EmbVector endPt1)
{
    EmbVector delta;
    EmbVector endPt2 = objectEndPoint2();
    embVector_subtract(endPt2, endPt1, &delta);
    setRotation(0);
    setLine(0, 0, dx, dy);
    setPos(endPt1);
    updateLeader();
}
*/

/*
void dimleader_setEndPoint2(EmbVector endPt2)
{
    EmbVector delta;
    EmbVector endPt1 = scenePos();
    embVector_subtract(endPt2, endPt1, &delta);
    setRotation(0);
    setLine(0, 0, delta.x, delta.y);
    setPos(endPt1);
    updateLeader();
}
*/

/*
EmbVector dimleader_objectEndPoint1()
{
    return scenePos();
}
*/

/*
EmbVector dimleader_objectEndPoint2()
{
    EmbLine lyne = line();
    float rot = radians(rotation());
    EmbVector point2;
    point2.x = lyne.x2()*scale();
    point2.y = lyne.y2()*scale();
    EmbVector rot = embVector_rotate(point2, alpha);

    return (scenePos() + rot);
}

EmbVector dimleader_objectMidPoint()
{
    EmbVector mp = line().pointAt(0.5) * scale();
    float alpha = radians(rotation());
    EmbVector rotMid = embVector_rotate(mp, alpha);
    return scenePos() + rotMid;
}

float dimleader_objectAngle()
{
    return fmodf(line().angle() - rotation(), 360.0);
}

void dimleader_updateLeader()
{
    int arrowStyle = Closed; //TODO: Make this customizable
    float arrowStyleAngle = 15.0; //TODO: Make this customizable
    float arrowStyleLength = 1.0; //TODO: Make this customizable
    float lineStyleAngle = 45.0; //TODO: Make this customizable
    float lineStyleLength = 1.0; //TODO: Make this customizable

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

void dimleader_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) {
        return;
    }

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected) {
        paintPen.setStyle(Qt::DashLine);
    }
    if (objScene->property("ENABLE_LWT").toBool()) {
        paintPen = lineWeightPen();
    }
    painter->setPen(paintPen);

    painter->drawPath(lineStylePath);
    painter->drawPath(arrowStylePath);

    if (filled) {
        painter->fillPath(arrowStylePath, objectColor());
    }
}

void dimleader_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_DIMLEADER_LINE) {
        EmbVector sceneStartPoint = objectRubberPoint("DIMLEADER_LINE_START");
        EmbVector sceneQSnapPoint = objectRubberPoint("DIMLEADER_LINE_END");

        setEndPoint1(sceneStartPoint);
        setEndPoint2(sceneQSnapPoint);
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if (gripPoint == objectEndPoint1())
                painter->drawLine(line().p2(), mapFromScene(objectRubberPoint(std::string())));
            else if (gripPoint == objectEndPoint2())
                painter->drawLine(line().p1(), mapFromScene(objectRubberPoint(std::string())));
            else if (gripPoint == objectMidPoint())
                painter->drawLine(line().translated(mapFromScene(objectRubberPoint(std::string()))-mapFromScene(gripPoint)));
        }
    }
}

// Returns the closest snap point to the mouse point
EmbVector dimleader_mouseSnapPoint(const EmbVector& mousePoint)
{
    EmbVector endPoint1 = objectEndPoint1();
    EmbVector endPoint2 = objectEndPoint2();
    EmbVector midPoint  = objectMidPoint();

    float end1Dist = EmbLine(mousePoint, endPoint1).length();
    float end2Dist = EmbLine(mousePoint, endPoint2).length();
    float midDist  = EmbLine(mousePoint, midPoint).length();

    float minDist = std::min(end1Dist, end2Dist);

    if (curved)
        minDist = std::min(minDist, midDist);

    if     (minDist == end1Dist) return endPoint1;
    else if (minDist == end2Dist) return endPoint2;
    else if (minDist == midDist)  return midPoint;

    return scenePos();
}

std::vector<EmbVector> embDimLeader_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << objectEndPoint1() << objectEndPoint2();
    if (curved) {
        gripPoints << objectMidPoint();
    }
    return gripPoints;
}
*/

/*
void embDimLeader_gripEdit(const EmbVector before, const EmbVector after)
{
    if (before == objectEndPoint1()) {
        setEndPoint1(after);
    }
    else if (before == objectEndPoint2()) {
        setEndPoint2(after);
    }
    else if (before == objectMidPoint()) {
        EmbVector delta = embVector_subtract(after, before);
        moveBy(delta);
    }
}
*/

void embEllipse_main()
{
    /*
    initCommand();
    clearSelection();
    view.ui_mode = "ELLIPSE_MODE_MAJORDIAMETER_MINORRADIUS";
    global.x1 = NaN;
    global.y1 = NaN;
    global.x2 = NaN;
    global.y2 = NaN;
    global.x3 = NaN;
    global.y3 = NaN;
    setPromptPrefix(translate("Specify first axis start point or [Center]: "));
    */
}

void embEllipse_click(float x, float y)
{
    printf("%f %f", x, y);
    /*
    if (view.ui_mode == MODE_MAJORDIAMETER_MINORRADIUS) {
        if (std::isnan(global.x1)) {
            global.x1 = x;
            global.y1 = y;
            addRubber("ELLIPSE");
            setRubberMode("ELLIPSE_LINE");
            setRubberPoint("ELLIPSE_LINE_POINT1", global.x1, global.y1);
            appendPromptHistory();
            setPromptPrefix(translate("Specify first axis end point: "));
        }
        else if (std::isnan(global.x2)) {
            global.x2 = x;
            global.y2 = y;
            global.cx = (global.x1 + global.x2)/2.0;
            global.cy = (global.y1 + global.y2)/2.0;
            global.width = calculateDistance(global.x1, global.y1, global.x2, global.y2);
            global.rot = calculateAngle(global.x1, global.y1, global.x2, global.y2);
            setRubberMode("ELLIPSE_MAJORDIAMETER_MINORRADIUS");
            setRubberPoint("ELLIPSE_AXIS1_POINT1", global.x1, global.y1);
            setRubberPoint("ELLIPSE_AXIS1_POINT2", global.x2, global.y2);
            setRubberPoint("ELLIPSE_CENTER", global.cx, global.cy);
            setRubberPoint("ELLIPSE_WIDTH", global.width, 0);
            setRubberPoint("ELLIPSE_ROT", global.rot, 0);
            appendPromptHistory();
            setPromptPrefix(translate("Specify second axis end point or [Rotation]: "));
        }
        else if (std::isnan(global.x3)) {
            global.x3 = x;
            global.y3 = y;
            global.height = perpendicularDistance(global.x3, global.y3, global.x1, global.y1, global.x2, global.y2)*2.0;
            setRubberPoint("ELLIPSE_AXIS2_POINT2", global.x3, global.y3);
            vulcanize();
            appendPromptHistory();
            endCommand();
        }
        else {
            error("ELLIPSE", translate("This should never happen."));
        }
    }
    else if (view.ui_mode == MODE_MAJORRADIUS_MINORRADIUS) {
        if (std::isnan(global.x1)) {
            global.x1 = x;
            global.y1 = y;
            global.cx = global.x1;
            global.cy = global.y1;
            addRubber("ELLIPSE");
            setRubberMode("ELLIPSE_LINE");
            setRubberPoint("ELLIPSE_LINE_POINT1", global.x1, global.y1);
            setRubberPoint("ELLIPSE_CENTER", global.cx, global.cy);
            appendPromptHistory();
            setPromptPrefix(translate("Specify first axis end point: "));
        }
        else if (std::isnan(global.x2)) {
            global.x2 = x;
            global.y2 = y;
            global.width = calculateDistance(global.cx, global.cy, global.x2, global.y2)*2.0;
            global.rot = calculateAngle(global.x1, global.y1, global.x2, global.y2);
            setRubberMode("ELLIPSE_MAJORRADIUS_MINORRADIUS");
            setRubberPoint("ELLIPSE_AXIS1_POINT2", global.x2, global.y2);
            setRubberPoint("ELLIPSE_WIDTH", global.width, 0);
            setRubberPoint("ELLIPSE_ROT", global.rot, 0);
            appendPromptHistory();
            setPromptPrefix(translate("Specify second axis end point or [Rotation]: "));
        }
        else if (std::isnan(global.x3)) {
            global.x3 = x;
            global.y3 = y;
            global.height = perpendicularDistance(global.x3, global.y3, global.cx, global.cy, global.x2, global.y2)*2.0;
            setRubberPoint("ELLIPSE_AXIS2_POINT2", global.x3, global.y3);
            vulcanize();
            appendPromptHistory();
            endCommand();
        }
        else {
            error("ELLIPSE", translate("This should never happen."));
        }
    }
    else if (view.ui_mode == MODE_ELLIPSE_ROTATION) {
        if (std::isnan(global.x1)) {
            error("ELLIPSE", translate("This should never happen."));
        }
        else if (std::isnan(global.x2)) {
            error("ELLIPSE", translate("This should never happen."));
        }
        else if (std::isnan(global.x3)) {
            float angle = calculateAngle(global.cx, global.cy, x, y);
            global.height = cos(angle*Math.PI/180.0)*global.width;
            addEllipse(global.cx, global.cy, global.width, global.height, global.rot, false);
            appendPromptHistory();
            endCommand();
        }
    }
    */
}

/*
void prompt(const char *str)
{
    if (mode == MAJORDIAMETER_MINORRADIUS) {
        if (std::isnan(global.x1)) {
            if (str == "C" || str == "CENTER") {
                view.ui_mode = MODE_MAJORRADIUS_MINORRADIUS;
                setPromptPrefix(translate("Specify center point: "));
            }
            else {
                std::vector<std::string> strList = str.split(",");
                if (std::isnan(strList[0]) || isnan(strList[1])) {
                    alert(translate("Point or option keyword required."));
                    setPromptPrefix(translate("Specify first axis start point or [Center]: "));
                }
                else {
                    global.x1 = Number(strList[0]);
                    global.y1 = Number(strList[1]);
                    addRubber("ELLIPSE");
                    setRubberMode("ELLIPSE_LINE");
                    setRubberPoint("ELLIPSE_LINE_POINT1", global.x1, global.y1);
                    setPromptPrefix(translate("Specify first axis end point: "));
                }
            }
        }
        else if (std::isnan(global.x2)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify first axis end point: "));
            }
            else {
                global.x2 = Number(strList[0]);
                global.y2 = Number(strList[1]);
                global.cx = (global.x1 + global.x2)/2.0;
                global.cy = (global.y1 + global.y2)/2.0;
                global.width = calculateDistance(global.x1, global.y1, global.x2, global.y2);
                global.rot = calculateAngle(global.x1, global.y1, global.x2, global.y2);
                setRubberMode("ELLIPSE_MAJORDIAMETER_MINORRADIUS");
                setRubberPoint("ELLIPSE_AXIS1_POINT1", global.x1, global.y1);
                setRubberPoint("ELLIPSE_AXIS1_POINT2", global.x2, global.y2);
                setRubberPoint("ELLIPSE_CENTER", global.cx, global.cy);
                setRubberPoint("ELLIPSE_WIDTH", global.width, 0);
                setRubberPoint("ELLIPSE_ROT", global.rot, 0);
                setPromptPrefix(translate("Specify second axis end point or [Rotation]: "));
            }
        }
        else if (std::isnan(global.x3)) {
            if (str == "R" || str == "ROTATION") {//TODO: Probably should add additional qsTr calls here.
                view.ui_mode = MODE_ELLIPSE_ROTATION;
                setPromptPrefix(translate("Specify rotation: "));
            }
            else {
                std::vector<std::string> strList = str.split(",");
                if (std::isnan(strList[0]) || isnan(strList[1])) {
                    alert(translate("Point or option keyword required."));
                    setPromptPrefix(translate("Specify second axis end point or [Rotation]: "));
                }
                else {
                    global.x3 = Number(strList[0]);
                    global.y3 = Number(strList[1]);
                    global.height = perpendicularDistance(global.x3, global.y3, global.x1, global.y1, global.x2, global.y2)*2.0;
                    setRubberPoint("ELLIPSE_AXIS2_POINT2", global.x3, global.y3);
                    vulcanize();
                    endCommand();
                }
            }
        }
    }
    else if (mode == MAJORRADIUS_MINORRADIUS) {
        if (std::isnan(global.x1)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify center point: "));
            }
            else {
                global.x1 = Number(strList[0]);
                global.y1 = Number(strList[1]);
                global.cx = global.x1;
                global.cy = global.y1;
                addRubber("ELLIPSE");
                setRubberMode("ELLIPSE_LINE");
                setRubberPoint("ELLIPSE_LINE_POINT1", global.x1, global.y1);
                setRubberPoint("ELLIPSE_CENTER", global.cx, global.cy);
                setPromptPrefix(translate("Specify first axis end point: "));
            }
        }
        else if (std::isnan(global.x2)) {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Invalid point."));
                setPromptPrefix(translate("Specify first axis end point: "));
            }
            else {
                global.x2 = Number(strList[0]);
                global.y2 = Number(strList[1]);
                global.width = calculateDistance(global.x1, global.y1, global.x2, global.y2)*2.0;
                global.rot = calculateAngle(global.x1, global.y1, global.x2, global.y2);
                setRubberMode("ELLIPSE_MAJORRADIUS_MINORRADIUS");
                setRubberPoint("ELLIPSE_AXIS1_POINT2", global.x2, global.y2);
                setRubberPoint("ELLIPSE_WIDTH", global.width, 0);
                setRubberPoint("ELLIPSE_ROT", global.rot, 0);
                setPromptPrefix(translate("Specify second axis end point or [Rotation]: "));
            }
        }
        else if (std::isnan(global.x3)) {
            if (str == "R" || str == "ROTATION") {
                view.ui_mode = MODE_ELLIPSE_ROTATION;
                setPromptPrefix(translate("Specify ellipse rotation: "));
            }
            else {
                std::vector<std::string> strList = str.split(",");
                if (std::isnan(strList[0]) || isnan(strList[1])) {
                    alert(translate("Point or option keyword required."));
                    setPromptPrefix(translate("Specify second axis end point or [Rotation]: "));
                }
                else {
                    global.x3 = Number(strList[0]);
                    global.y3 = Number(strList[1]);
                    global.height = perpendicularDistance(global.x3, global.y3, global.x1, global.y1, global.x2, global.y2)*2.0;
                    setRubberPoint("ELLIPSE_AXIS2_POINT2", global.x3, global.y3);
                    vulcanize();
                    endCommand();
                }
            }
        }
    }
    else if (view.ui_mode == MODE_ELLIPSE_ROTATION) {
        if (std::isnan(global.x1)) {
            error("ELLIPSE", translate("This should never happen."));
        }
        else if (std::isnan(global.x2)) {
            error("ELLIPSE", translate("This should never happen."));
        }
        else if (std::isnan(global.x3)) {
            if (std::isnan(str)) {
                alert(translate("Invalid angle. Input a numeric angle or pick a point."));
                setPromptPrefix(translate("Specify rotation: "));
            }
            else {
                float angle = Number(str);
                global.height = cos(angle*Math.PI/180.0)*global.width;
                addEllipse(global.cx, global.cy, global.width, global.height, global.rot, false);
                endCommand();
            }
        }
    }
}
*/

/*
void embEllipse_EllipseObject(float centerX, float centerY, float width, float height, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("EllipseObject Constructor()");
    init(centerX, centerY, width, height, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}
*/

/*
void embEllipse_EllipseObject(EllipseObject* obj, QGraphicsItem* parent)
{
    debug_message("EllipseObject Constructor()");
    if (obj) {
        init(obj->objectCenterX(), obj->objectCenterY(), obj->objectWidth(), obj->objectHeight(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
    }
}
*/

/*
void image_init(EmbRect rect, unsigned int rgb, int lineType)
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
*/

/*
void image_setRect(float x, float y, float w, float h)
{
    setPos(x, y);
    setRect(0, 0, w, h);
    updatePath();
}
*/

/*
EmbVector image_objectTopLeft()
{
    float alpha = radians(rotation());
    EmbVector tl = rect().topRight() * scale();
    EmbVector ptlrot = embVector_rotate(tl, alpha);
    return scenePos() + ptlrot;
}
*/

/*
EmbVector image_objectTopRight()
{
    float alpha = radians(rotation());
    EmbVector tr = rect().topRight() * scale();
    EmbVector ptrrot = embVector_rotate(tr, alpha);
    return scenePos() + ptrrot;
}
*/

/*
EmbVector image_objectBottomLeft()
{
    float alpha = radians(rotation());
    EmbVector bl = rect().topRight() * scale();
    EmbVector pblrot = embVector_rotate(bl, alpha);
    return scenePos() + pblrot;
}
*/

/*
EmbVector image_objectBottomRight()
{
    float alpha = radians(rotation());
    EmbVector br = rect().topRight() * scale();
    EmbVector pbrrot = embVector_rotate(br, alpha);
    return scenePos() + pbrrot;
}
*/

/*
void image_updatePath()
{
    QPainterPath path;
    EmbRect r = rect();
    path.moveTo(r.bottomLeft());
    path.lineTo(r.bottomRight());
    path.lineTo(r.topRight());
    path.lineTo(r.topLeft());
    path.lineTo(r.bottomLeft());
    //NOTE: Reverse the path so that the inside area isn't considered part of the rectangle
    path.lineTo(r.topLeft());
    path.lineTo(r.topRight());
    path.lineTo(r.bottomRight());
    path.moveTo(r.bottomLeft());
    setPath(path);
}
*/

/*
void image_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawRect(rect());
}
*/

/*
void image_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_IMAGE) {
        EmbVector sceneStartPoint = objectRubberPoint("IMAGE_START");
        EmbVector sceneEndPoint = objectRubberPoint("IMAGE_END");
        float x = sceneStartPoint.x();
        float y = sceneStartPoint.y();
        float w = sceneEndPoint.x() - sceneStartPoint.x();
        float h = sceneEndPoint.y() - sceneStartPoint.y();
        setRect(x,y,w,h);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        //TODO: updateRubber() gripping for ImageObject
    }
}
*/

/*
// Returns the closest snap point to the mouse point
EmbVector image_mouseSnapPoint(const EmbVector& mousePoint)
{
    EmbVector ptl = objectTopLeft();     //Top Left Corner QSnap
    EmbVector ptr = objectTopRight();    //Top Right Corner QSnap
    EmbVector pbl = objectBottomLeft();  //Bottom Left Corner QSnap
    EmbVector pbr = objectBottomRight(); //Bottom Right Corner QSnap

    float ptlDist = EmbLine(mousePoint, ptl).length();
    float ptrDist = EmbLine(mousePoint, ptr).length();
    float pblDist = EmbLine(mousePoint, pbl).length();
    float pbrDist = EmbLine(mousePoint, pbr).length();

    float minDist = std::min(std::min(ptlDist, ptrDist), std::min(pblDist, pbrDist));

    if     (minDist == ptlDist) return ptl;
    else if (minDist == ptrDist) return ptr;
    else if (minDist == pblDist) return pbl;
    else if (minDist == pbrDist) return pbr;

    return scenePos();
}

std::vector<EmbVector> image_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << objectTopLeft() << objectTopRight() << objectBottomLeft() << objectBottomRight();
    return gripPoints;
}

void image_gripEdit(const EmbVector& before, const EmbVector& after)
{
    //TODO: gripEdit() for ImageObject
}

[Menu]
Name=Draw
Position=0

[ToolBar]
Name=Draw
Position=0

[Tips]
ToolTip=&Line
StatusTip=Creates straight line segments:  LINE

[Prompt]
Alias=L, LINE

//Command: Line

float global = {}; //Required
global.firstRun;
global.firstX;
global.firstY;
global.prevX;
global.prevY;
*/

/*
void line_main()
{
    initCommand();
    clearSelection();
    global.firstRun = true;
    global.firstX = NaN;
    global.firstY = NaN;
    global.prevX = NaN;
    global.prevY = NaN;
    setPromptPrefix(translate("Specify first point: "));
}
*/

/*
void
line_click(EmbVector p)
{
    if (global.firstRun) {
        global.firstRun = false;
        global.firstX = p.x;
        global.firstY = p.y;
        global.prevX = p.x;
        global.prevY = p.y;
        addRubber("LINE");
        setRubberMode("LINE");
        setRubberPoint("LINE_START", global.firstX, global.firstY);
        appendPromptHistory();
        setPromptPrefix(translate("Specify next point or [Undo]: "));
    }
    else {
        setRubberPoint("LINE_END", x, y);
        vulcanize();
        addRubber("LINE");
        setRubberMode("LINE");
        setRubberPoint("LINE_START", x, y);
        appendPromptHistory();
        global.prevX = x;
        global.prevY = y;
    }
}
*/

/*
void
line_prompt(const char *str)
{
    if (global.firstRun) {
        std::vector<std::string> strList = str.split(",");
        if (std::isnan(strList[0]) || isnan(strList[1])) {
            alert(translate("Invalid point."));
            setPromptPrefix(translate("Specify first point: "));
        }
        else {
            global.firstRun = false;
            global.firstX = Number(strList[0]);
            global.firstY = Number(strList[1]);
            global.prevX = global.firstX;
            global.prevY = global.firstY;
            addRubber("LINE");
            setRubberMode("LINE");
            setRubberPoint("LINE_START", global.firstX, global.firstY);
            setPromptPrefix(translate("Specify next point or [Undo]: "));
        }
    }
    else {
        if (str == "U" || str == "UNDO") {
            todo("LINE", "prompt() for UNDO");
        }
        else {
            std::vector<std::string> strList = str.split(",");
            if (std::isnan(strList[0]) || isnan(strList[1])) {
                alert(translate("Point or option keyword required."));
                setPromptPrefix(translate("Specify next point or [Undo]: "));
            }
            else {
                float x = Number(strList[0]);
                float y = Number(strList[1]);
                setRubberPoint("LINE_END", x, y);
                vulcanize();
                addRubber("LINE");
                setRubberMode("LINE");
                setRubberPoint("LINE_START", x, y);
                global.prevX = x;
                global.prevY = y;
                setPromptPrefix(translate("Specify next point or [Undo]: "));
            }
        }
    }
}
*/

/*
void line_init(EmbLine line_in, unsigned int rgb, PenStyle lineType)
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
*/

/*
void line_setEndPoint1(EmbVector point1)
{
    float dx = line.start.x - point1.x;
    float dy = line.start.y - point1.y;
    setRotation(0);
    setScale(1);
    setLine(0, 0, dx, dy);
    setPos(point1);
}
*/

/*
void line_setEndPoint2(EmbVector point1)
{
    float dx = line.end.x - point1.x;
    float dy = line.end.y - point1.y;
    setRotation(0);
    setScale(1);
    setLine(0, 0, dx, dy);
    setPos(point1);
}
*/

/*
EmbVector line_objectEndPoint2()
{
    EmbLine lyne = line();
    float alpha = radians(rotation());
    EmbVector point2;
    point2.x = lyne.x2()*scale();
    point2.y = lyne.y2()*scale();
    EmbVector rotEnd = embVector_rotate(point2, alpha);

    return scenePos() + rotEnd;
}
*/

/*
EmbVector line_objectMidPoint()
{
    EmbLine lyne = line();
    EmbVector mp = lyne.pointAt(0.5) * scale();
    float alpha = radians(rotation());
    EmbVector rotMid = embVector_rotate(mp, alpha);

    return scenePos() + rotMid;
}
*/

/*
float line_objectAngle()
{
    return std::fmodf(line().angle() - rotation(), 360.0);
}
*/

/*
void line_paint(QPainter* painter, QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  {
        paintPen.setStyle(Qt::DashLine);
    }
    if (objScene->property(ENABLE_LWT).toBool()) {
        paintPen = lineWeightPen();
    }
    painter->setPen(paintPen);

    if (objectRubberMode() != OBJ_RUBBER_LINE) painter->drawLine(line());

    if (objScene->property(ENABLE_LWT).toBool() && objScene->property("ENABLE_REAL").toBool()) {
        realRender(painter, path());
    }
}

void line_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_LINE) {
        EmbVector sceneStartPoint = objectRubberPoint("LINE_START");
        EmbVector sceneQSnapPoint = objectRubberPoint("LINE_END");

        setEndPoint1(sceneStartPoint);
        setEndPoint2(sceneQSnapPoint);

        drawRubberLine(line(), painter, VIEW_COLOR_CROSSHAIR);
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if     (gripPoint == objectEndPoint1()) painter->drawLine(line().p2(), mapFromScene(objectRubberPoint(std::string())));
            else if (gripPoint == objectEndPoint2()) painter->drawLine(line().p1(), mapFromScene(objectRubberPoint(std::string())));
            else if (gripPoint == objectMidPoint())  painter->drawLine(line().translated(mapFromScene(objectRubberPoint(std::string()))-mapFromScene(gripPoint)));

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
        }
    }
}
*/

/*
// Returns the closest snap point to the mouse point
EmbVector line_mouseSnapPoint(EmbVector& mousePoint)
{
    EmbVector endPoint1 = objectEndPoint1();
    EmbVector endPoint2 = objectEndPoint2();
    EmbVector midPoint  = objectMidPoint();

    float end1Dist = EmbLine(mousePoint, endPoint1).length();
    float end2Dist = EmbLine(mousePoint, endPoint2).length();
    float midDist  = EmbLine(mousePoint, midPoint).length();

    float minDist = std::min(std::min(end1Dist, end2Dist), midDist);

    if     (minDist == end1Dist) return endPoint1;
    else if (minDist == end2Dist) return endPoint2;
    else if (minDist == midDist)  return midPoint;

    return scenePos();
}

std::vector<EmbVector> line_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << objectEndPoint1() << objectEndPoint2() << objectMidPoint();
    return gripPoints;
}

void line_gripEdit(EmbVector& before, EmbVector& after)
{
    if     (before == objectEndPoint1()) { setEndPoint1(after); }
    else if (before == objectEndPoint2()) { setEndPoint2(after); }
    else if (before == objectMidPoint())  { EmbVector delta = after-before; moveBy(delta.x(), delta.y()); }
}

QPainterPath line_objectSavePath()
{
    QPainterPath path;
    path.lineTo(objectDeltaX(), objectDeltaY());
    return path;
}

path_PathObject(float x, float y, const QPainterPath p, unsigned int rgb, QGraphicsItem* parent)
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

void path_init(float x, float y, const QPainterPath& p, unsigned int rgb, int lineType)
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

void path_updatePath(const QPainterPath& p)
{
    normalPath = p;
    QPainterPath reversePath = normalPath.toReversed();
    reversePath.connectPath(normalPath);
    setPath(reversePath);
}

void path_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawPath(objectPath());
}

void path_updateRubber(QPainter* painter)
{
    //TODO: Path Rubber Modes

    //TODO: updateRubber() gripping for PathObject

}

// Returns the closest snap point to the mouse point
EmbVector path_mouseSnapPoint(const EmbVector& mousePoint)
{
    return scenePos();
}

std::vector<EmbVector> path_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << scenePos(); //TODO: loop thru all path Elements and return their points
    return gripPoints;
}

void path_gripEdit(const EmbVector& before, const EmbVector& after)
{
    //TODO: gripEdit() for PathObject
}

QPainterPath path_objectCopyPath()
{
    return normalPath;
}

QPainterPath path_objectSavePath()
{
    float s = scale();
    QTransform trans;
    trans.rotate(rotation());
    trans.scale(s,s);
    return trans.map(normalPath);
}

void point_init(float x, float y, unsigned int rgb, int lineType)
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

void point_paint(QPainter* painter, QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawPoint(0,0);
}

void point_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if (gripPoint == scenePos()) {
                EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
                drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
            }
        }
    }
}

// Returns the closest snap point to the mouse point
EmbVector point_mouseSnapPoint(EmbVector& mousePoint)
{
    return scenePos();
}

std::vector<EmbVector> point_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << scenePos();
    return gripPoints;
}

void point_gripEdit(EmbVector& before, EmbVector& after)
{
    if (before == scenePos()) { EmbVector delta = after-before; moveBy(delta.x(), delta.y()); }
}

QPainterPath point_objectSavePath()
{
    QPainterPath path;
    path.addRect(-0.00000001, -0.00000001, 0.00000002, 0.00000002);
    return path;
}

void polygon_PolygonObject(float x, float y, const QPainterPath& p, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("PolygonObject Constructor()");
    init(x, y, p, rgb, SolidLine); //TODO: getCurrentLineType
}

void polygon_PolygonObject(PolygonObject* obj, QGraphicsItem* parent)
{
    debug_message("PolygonObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void polygon_init(float x, float y, const QPainterPath& p, unsigned int rgb, PenStyle lineType)
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

void polygon_updatePath(const QPainterPath& p)
{
    normalPath = p;
    QPainterPath closedPath = normalPath;
    closedPath.closeSubpath();
    QPainterPath reversePath = closedPath.toReversed();
    reversePath.connectPath(closedPath);
    setPath(reversePath);
}

void polygon_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    if (normalPath.elementCount()) {
        painter->drawPath(normalPath);
        QPainterPath::Element zero = normalPath.elementAt(0);
        QPainterPath::Element last = normalPath.elementAt(normalPath.elementCount()-1);
        painter->drawLine(EmbVector(zero.x, zero.y), EmbVector(last.x, last.y));
    }
}

void polygon_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_POLYGON) {
        setPos(objectRubberPoint("POLYGON_POINT_0"));

        bool ok = false;
        const char *numStr = objectRubberText("POLYGON_NUM_POINTS");
        if (numStr.isNull()) return;
        int num = numStr.toInt(&ok);
        if (!ok) return;

        const char *appendStr;
        QPainterPath rubberPath;
        rubberPath.moveTo(mapFromScene(objectRubberPoint("POLYGON_POINT_0")));
        for (int i = 1; i <= num; i++) {
            appendStr = "POLYGON_POINT_" + std::string().setNum(i);
            EmbVector appendPoint = mapFromScene(objectRubberPoint(appendStr));
            rubberPath.lineTo(appendPoint);
        }
        //rubberPath.lineTo(0,0);
        updatePath(rubberPath);

        //Ensure the path isn't updated until the number of points is changed again
        setRubberText("POLYGON_NUM_POINTS", std::string());
    }
    else if (rubberMode == OBJ_RUBBER_POLYGON_INSCRIBE) {
        setPos(objectRubberPoint("POLYGON_CENTER"));

        quint16 numSides = objectRubberPoint("POLYGON_NUM_SIDES").x();

        EmbVector inscribePoint = mapFromScene(objectRubberPoint("POLYGON_INSCRIBE_POINT"));
        EmbLine inscribeLine = EmbLine(EmbVector(0,0), inscribePoint);
        float inscribeAngle = inscribeLine.angle();
        float inscribeInc = 360.0/numSides;

        if (painter) drawRubberLine(inscribeLine, painter, VIEW_COLOR_CROSSHAIR);

        QPainterPath inscribePath;
        //First Point
        inscribePath.moveTo(inscribePoint);
        //Remaining Points
        for (int i = 1; i < numSides; i++) {
            inscribeLine.setAngle(inscribeAngle + inscribeInc*i);
            inscribePath.lineTo(inscribeLine.p2());
        }
        updatePath(inscribePath);
    }
    else if (rubberMode == OBJ_RUBBER_POLYGON_CIRCUMSCRIBE) {
        setPos(objectRubberPoint("POLYGON_CENTER"));

        quint16 numSides = objectRubberPoint("POLYGON_NUM_SIDES").x();

        EmbVector circumscribePoint = mapFromScene(objectRubberPoint("POLYGON_CIRCUMSCRIBE_POINT"));
        EmbLine circumscribeLine = EmbLine(EmbVector(0,0), circumscribePoint);
        float circumscribeAngle = circumscribeLine.angle();
        float circumscribeInc = 360.0/numSides;

        if (painter) drawRubberLine(circumscribeLine, painter, VIEW_COLOR_CROSSHAIR);

        QPainterPath circumscribePath;
        //First Point
        EmbLine prev(circumscribeLine.p2(), EmbVector(0,0));
        prev = prev.normalVector();
        circumscribeLine.setAngle(circumscribeAngle + circumscribeInc);
        EmbLine perp(circumscribeLine.p2(), EmbVector(0,0));
        perp = perp.normalVector();
        EmbVector iPoint;
        perp.intersects(prev, &iPoint);
        circumscribePath.moveTo(iPoint);
        //Remaining Points
        for (int i = 2; i <= numSides; i++) {
            prev = perp;
            circumscribeLine.setAngle(circumscribeAngle + circumscribeInc*i);
            perp = EmbLine(circumscribeLine.p2(), EmbVector(0,0));
            perp = perp.normalVector();
            perp.intersects(prev, &iPoint);
            circumscribePath.lineTo(iPoint);
        }
        updatePath(circumscribePath);
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            int elemCount = normalPath.elementCount();
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if (gripIndex == -1) gripIndex = findIndex(gripPoint);
            if (gripIndex == -1) return;

            int m = 0;
            int n = 0;

            if (!gripIndex) {
                m = elemCount-1;
                n = 1;
            }
            else if (gripIndex == elemCount-1) {
                m = elemCount-2;
                n = 0;
            }
            else {
                m = gripIndex-1;
                n = gripIndex+1;
            }
            QPainterPath::Element em = normalPath.elementAt(m);
            QPainterPath::Element en = normalPath.elementAt(n);
            EmbVector emPoint = EmbVector(em.x, em.y);
            EmbVector enPoint = EmbVector(en.x, en.y);
            painter->drawLine(emPoint, mapFromScene(objectRubberPoint(std::string())));
            painter->drawLine(enPoint, mapFromScene(objectRubberPoint(std::string())));

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
        }
    }
}

// Returns the closest snap point to the mouse point
EmbVector polygon_mouseSnapPoint(const EmbVector& mousePoint)
{
    QPainterPath::Element element = normalPath.elementAt(0);
    EmbVector closestPoint = mapToScene(EmbVector(element.x, element.y));
    float closestDist = EmbLine(mousePoint, closestPoint).length();
    int elemCount = normalPath.elementCount();
    for (int i = 0; i < elemCount; ++i) {
        element = normalPath.elementAt(i);
        EmbVector elemPoint = mapToScene(element.x, element.y);
        float elemDist = EmbLine(mousePoint, elemPoint).length();
        if (elemDist < closestDist) {
            closestPoint = elemPoint;
            closestDist = elemDist;
        }
    }
    return closestPoint;
}

std::vector<EmbVector> polygon_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    QPainterPath::Element element;
    for (int i = 0; i < normalPath.elementCount(); ++i) {
        element = normalPath.elementAt(i);
        gripPoints << mapToScene(element.x, element.y);
    }
    return gripPoints;
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

void polygon_gripEdit(const EmbVector& before, const EmbVector& after)
{
    gripIndex = findIndex(before);
    if (gripIndex == -1) return;
    EmbVector a = mapFromScene(after);
    normalPath.setElementPositionAt(gripIndex, a.x(), a.y());
    updatePath(normalPath);
    gripIndex = -1;
}

QPainterPath polygon_objectCopyPath()
{
    return normalPath;
}

QPainterPath polygon_objectSavePath()
{
    QPainterPath closedPath = normalPath;
    closedPath.closeSubpath();
    float s = scale();
    QTransform trans;
    trans.rotate(rotation());
    trans.scale(s,s);
    return trans.map(closedPath);
}

void embPolyline_PolylineObject(float x, float y, const QPainterPath& p, unsigned int rgb, QGraphicsItem* parent)
{
    debug_message("PolylineObject Constructor()");
    init(x, y, p, rgb, Qt::SolidLine); //TODO: getCurrentLineType
}

void embPolyline_PolylineObject(PolylineObject* obj, QGraphicsItem* parent)
{
    debug_message("PolylineObject Constructor()");
    if (obj) {
        init(obj->objectX(), obj->objectY(), obj->objectCopyPath(), obj->objectColorRGB(), Qt::SolidLine); //TODO: getCurrentLineType
        setRotation(obj->rotation());
        setScale(obj->scale());
    }
}

void embPolyline_init(float x, float y, QPainterPath *p, unsigned int rgb, int lineType)
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

void embPolyline_updatePath(const QPainterPath& p)
{
    normalPath = p;
    QPainterPath reversePath = normalPath.toReversed();
    reversePath.connectPath(normalPath);
    setPath(reversePath);
}

void embPolyline_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawPath(normalPath);

    if (objScene->property(ENABLE_LWT).toBool() && objScene->property(ENABLE_REAL).toBool()) { realRender(painter, normalPath); }
}

void embPolyline_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_POLYLINE) {
        setPos(objectRubberPoint("POLYLINE_POINT_0"));

        EmbLine rubberLine(normalPath.currentPosition(), mapFromScene(objectRubberPoint(std::string())));
        if (painter) drawRubberLine(rubberLine, painter, VIEW_COLOR_CROSSHAIR);

        bool ok = false;
        const char *numStr = objectRubberText("POLYLINE_NUM_POINTS");
        if (numStr.isNull()) return;
        int num = numStr.toInt(&ok);
        if (!ok) return;

        const char *appendStr;
        QPainterPath rubberPath;
        for (int i = 1; i <= num; i++) {
            appendStr = "POLYLINE_POINT_" + std::string().setNum(i);
            EmbVector appendPoint = mapFromScene(objectRubberPoint(appendStr));
            rubberPath.lineTo(appendPoint);
        }
        updatePath(rubberPath);

        //Ensure the path isn't updated until the number of points is changed again
        setRubberText("POLYLINE_NUM_POINTS", std::string());
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            int elemCount = normalPath.elementCount();
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            if (gripIndex == -1) gripIndex = findIndex(gripPoint);
            if (gripIndex == -1) return;

            if (!gripIndex) { //First
                QPainterPath::Element ef = normalPath.elementAt(1);
                EmbVector efPoint = EmbVector(ef.x, ef.y);
                painter->drawLine(efPoint, mapFromScene(objectRubberPoint(std::string())));
            }
            else if (gripIndex == elemCount-1) { //Last
                QPainterPath::Element el = normalPath.elementAt(gripIndex-1);
                EmbVector elPoint = EmbVector(el.x, el.y);
                painter->drawLine(elPoint, mapFromScene(objectRubberPoint(std::string())));
            }
            else { //Middle
                QPainterPath::Element em = normalPath.elementAt(gripIndex-1);
                QPainterPath::Element en = normalPath.elementAt(gripIndex+1);
                EmbVector emPoint = EmbVector(em.x, em.y);
                EmbVector enPoint = EmbVector(en.x, en.y);
                painter->drawLine(emPoint, mapFromScene(objectRubberPoint(std::string())));
                painter->drawLine(enPoint, mapFromScene(objectRubberPoint(std::string())));
            }

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
        }
    }
}

// Returns the closest snap point to the mouse point
EmbVector embPolyline_mouseSnapPoint(const EmbVector& mousePoint)
{
    QPainterPath::Element element = normalPath.elementAt(0);
    EmbVector closestPoint = mapToScene(EmbVector(element.x, element.y));
    float closestDist = EmbLine(mousePoint, closestPoint).length();
    int elemCount = normalPath.elementCount();
    for (int i = 0; i < elemCount; ++i) {
        element = normalPath.elementAt(i);
        EmbVector elemPoint = mapToScene(element.x, element.y);
        float elemDist = EmbLine(mousePoint, elemPoint).length();
        if (elemDist < closestDist) {
            closestPoint = elemPoint;
            closestDist = elemDist;
        }
    }
    return closestPoint;
}

std::vector<EmbVector> embPolyline_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    QPainterPath::Element element;
    for (int i = 0; i < normalPath.elementCount(); ++i) {
        element = normalPath.elementAt(i);
        gripPoints << mapToScene(element.x, element.y);
    }
    return gripPoints;
}

int embPolyline_findIndex(const EmbVector& point)
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

void embPolyline_gripEdit(const EmbVector& before, const EmbVector& after)
{
    gripIndex = findIndex(before);
    if (gripIndex == -1) return;
    EmbVector a = mapFromScene(after);
    normalPath.setElementPositionAt(gripIndex, a.x(), a.y());
    updatePath(normalPath);
    gripIndex = -1;
}

QPainterPath embPolyline_objectCopyPath()
{
    return normalPath;
}

QPainterPath embPolyline_objectSavePath()
{
    float s = scale();
    QTransform trans;
    trans.rotate(rotation());
    trans.scale(s,s);
    return trans.map(normalPath);
}

void rect_init(EmbRect rect, unsigned int rgb, PenStyle lineType)
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

void rect_setRect(float x, float y, float w, float h)
{
    setPos(x, y);
    setRect(0, 0, w, h);
    updatePath();
}

EmbVector rect_objectTopLeft()
{
    float alpha = radians(rotation());
    EmbVector tl = rect().topLeft() * scale();
    EmbVector ptlrot = embVector_rotate(t1, alpha);
    return scenePos() + ptlrot;
}

EmbVector rect_objectTopRight()
{
    float alpha = radians(rotation());
    EmbVector tr = rect().topRight() * scale();
    EmbVector ptlrot = embVector_rotate(t1, alpha);
    return scenePos() + ptrrot;
}
*/

EmbVector embRect_bottomLeft(EmbRect rect)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    /*
    float alpha = radians(rotation());
    EmbVector bl = rect().bottomLeft() * scale();
    EmbVector pblrot = embVector_rotate(b1, alpha);
    return scenePos() + pblrot;
    */
    return v;
}

EmbVector embRect_bottomRight(EmbRect rect)
{
    EmbVector v;
    v.x = 0.0;
    v.y = 0.0;
    /*
    float alpha = radians(rotation());
    EmbVector br = rect().bottomRight() * scale();
    EmbVector pbrrot = embVector_rotate(br, alpha);
    return scenePos() + pbrrot;
    */
    return v;
}

/*
void embRect_updatePath()
{
    QPainterPath path;
    EmbRect r = rect();
    path.moveTo(r.bottomLeft());
    path.lineTo(r.bottomRight());
    path.lineTo(r.topRight());
    path.lineTo(r.topLeft());
    path.lineTo(r.bottomLeft());
    //NOTE: Reverse the path so that the inside area isn't considered part of the rectangle
    path.lineTo(r.topLeft());
    path.lineTo(r.topRight());
    path.lineTo(r.bottomRight());
    path.moveTo(r.bottomLeft());
    setPath(path);
}

void rect_paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsScene* objScene = scene();
    if (!objScene) return;

    QPen paintPen = pen();
    painter->setPen(paintPen);
    updateRubber(painter);
    if (option->state & QStyle::State_Selected)  { paintPen.setStyle(Qt::DashLine); }
    if (objScene->property(ENABLE_LWT).toBool()) { paintPen = lineWeightPen(); }
    painter->setPen(paintPen);

    painter->drawRect(rect());
}
*/

/*
void rect_updateRubber(QPainter* painter)
{
    int rubberMode = objectRubberMode();
    if (rubberMode == OBJ_RUBBER_RECTANGLE) {
        EmbVector sceneStartPoint = objectRubberPoint("RECTANGLE_START");
        EmbVector sceneEndPoint = objectRubberPoint("RECTANGLE_END");
        float x = sceneStartPoint.x();
        float y = sceneStartPoint.y();
        float w = sceneEndPoint.x() - sceneStartPoint.x();
        float h = sceneEndPoint.y() - sceneStartPoint.y();
        setRect(x,y,w,h);
        updatePath();
    }
    else if (rubberMode == OBJ_RUBBER_GRIP) {
        if (painter) {
            //TODO: Make this work with rotation & scaling
            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            EmbVector after = objectRubberPoint(std::string());
            EmbVector delta = after-gripPoint;
            if (gripPoint == objectTopLeft()) {
                painter->drawPolygon(mapFromScene(EmbRect(after.x(), after.y(), objectWidth()-delta.x(), objectHeight()-delta.y())));
            }
            else if (gripPoint == objectTopRight()) {
                painter->drawPolygon(mapFromScene(EmbRect(objectTopLeft().x(), objectTopLeft().y()+delta.y(), objectWidth()+delta.x(), objectHeight()-delta.y())));
            }
            else if (gripPoint == objectBottomLeft()) {
                painter->drawPolygon(mapFromScene(EmbRect(objectTopLeft().x()+delta.x(), objectTopLeft().y(), objectWidth()-delta.x(), objectHeight()+delta.y())));
            }
            else if (gripPoint == objectBottomRight()) {
                painter->drawPolygon(mapFromScene(EmbRect(objectTopLeft().x(), objectTopLeft().y(), objectWidth()+delta.x(), objectHeight()+delta.y())));
            }

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);

            EmbVector gripPoint = objectRubberPoint("GRIP_POINT");
            EmbVector after = objectRubberPoint(std::string());
            EmbVector delta = after-gripPoint;

            EmbLine rubLine(mapFromScene(gripPoint), mapFromScene(objectRubberPoint(std::string())));
            drawRubberLine(rubLine, painter, VIEW_COLOR_CROSSHAIR);
        }
    }
}

// Returns the closest snap point to the mouse point
EmbVector rect_mouseSnapPoint(const EmbVector& mousePoint)
{
    EmbVector ptl = objectTopLeft();     //Top Left Corner QSnap
    EmbVector ptr = objectTopRight();    //Top Right Corner QSnap
    EmbVector pbl = objectBottomLeft();  //Bottom Left Corner QSnap
    EmbVector pbr = objectBottomRight(); //Bottom Right Corner QSnap

    float ptlDist = EmbLine(mousePoint, ptl).length();
    float ptrDist = EmbLine(mousePoint, ptr).length();
    float pblDist = EmbLine(mousePoint, pbl).length();
    float pbrDist = EmbLine(mousePoint, pbr).length();

    float minDist = std::min(std::min(ptlDist, ptrDist), std::min(pblDist, pbrDist));

    if     (minDist == ptlDist) return ptl;
    else if (minDist == ptrDist) return ptr;
    else if (minDist == pblDist) return pbl;
    else if (minDist == pbrDist) return pbr;

    return scenePos();
}

std::vector<EmbVector> rect_allGripPoints()
{
    std::vector<EmbVector> gripPoints;
    gripPoints << objectTopLeft() << objectTopRight() << objectBottomLeft() << objectBottomRight();
    return gripPoints;
}

void rect_gripEdit(const EmbVector& before, const EmbVector& after)
{
    EmbVector delta = after-before;
    if (before == objectTopLeft()) {
        setRect(after.x(), after.y(), objectWidth()-delta.x(), objectHeight()-delta.y());
    }
    else if (before == objectTopRight()) {
        setRect(objectTopLeft().x(), objectTopLeft().y()+delta.y(), objectWidth()+delta.x(), objectHeight()-delta.y());
    }
    else if (before == objectBottomLeft()) {
        setRect(objectTopLeft().x()+delta.x(), objectTopLeft().y(), objectWidth()-delta.x(), objectHeight()+delta.y());
    }
    else if (before == objectBottomRight()) {
        setRect(objectTopLeft().x(), objectTopLeft().y(), objectWidth()+delta.x(), objectHeight()+delta.y());
    }
}

QPainterPath rect_objectSavePath()
{
    QPainterPath path;
    EmbRect r = rect();
    path.moveTo(r.bottomLeft());
    path.lineTo(r.bottomRight());
    path.lineTo(r.topRight());
    path.lineTo(r.topLeft());
    path.lineTo(r.bottomLeft());

    float s = scale();
    QTransform trans;
    trans.rotate(rotation());
    trans.scale(s,s);
    return trans.map(path);
}
*/
/*
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * GEOMETRY
 */

/*
 */
EmbCircle
embCircle_init(void)
{
    EmbCircle circle;
    circle.center.x = 0.0;
    circle.center.y = 0.0;
    circle.radius = 1.0;
    return circle;
}

/*
 */
EmbReal
embCircle_area(EmbCircle circle)
{
    return embConstantPi * circle.radius * circle.radius;
}

/*
 */
EmbReal
embCircle_circumference(EmbCircle circle)
{
    return embConstantPi * circle.radius * circle.radius;
}

/* Computational Geometry for Circles */

/****************************************************************
 * Calculates the intersection points of two overlapping circles.
 * Returns true if the circles intersect.
 * Returns false if the circles do not intersect.
 ****************************************************************/
int
getCircleCircleIntersections(EmbCircle c0, EmbCircle c1,
                             EmbVector *p0, EmbVector *p1)
{
    EmbVector delta;
    EmbReal a, h, px2, py2, mx, my, d;
    /* Distance between centers */
    delta = embVector_subtract(c1.center, c0.center);
    d = embVector_length(delta);

    /*Circles share centers. This results in division by zero,
      infinite solutions or one circle being contained within the other. */
    if (d == 0.0) {
        return 0;
    } else if (d > (c0.radius + c1.radius)) {
        /* Circles do not touch each other */
        return 0;
    } else if (d < (c0.radius - c1.radius)) {
        /* One circle is contained within the other */
        return 0;
    }
    /*
     * Considering the two right triangles p0p2p3 and p1p2p3 we can write:
     * a^2 + h^2 = r0^2 and b^2 + h^2 = r1^2
     *
     * BEGIN PROOF
     *
     * Remove h^2 from the equation by setting them equal to themselves:
     *     r0^2 - a^2 = r1^2 - b^2
     * Substitute b with (d - a) since it is proven that d = a + b:
     *     r0^2 - a^2 = r1^2 - (d - a)^2
     * Complete the square:
     *     r0^2 - a^2 = r1^2 - (d^2 -2da + a^2)
     * Subtract r1^2 from both sides:
     *     r0^2 - r1^2 - a^2 = -(d^2 -2da + a^2)
     * Invert the signs:
     *     r0^2 - r1^2 - a^2 = -d^2 + 2da - a^2
     * Adding a^2 to each side cancels them out:
     *     r0^2 - r1^2 = -d^2 + 2da
     * Add d^2 to both sides to shift it to the other side:
     *     r0^2 - r1^2 + d^2 = 2da
     * Divide by 2d to finally solve for a:
     *     a = (r0^2 - r1^2 + d^2)/ (2d)
     *
     * END PROOF
     */

    a = ((c0.radius*c0.radius) - (c1.radius*c1.radius) + (d*d)) / (2.0 * d);
    /* Solve for h by substituting a into a^2 + h^2 = r0^2 */
    h = sqrt((c0.radius*c0.radius) - (a*a));

    /*Find point p2 by adding the a offset in relation to line d to point p0 */
    px2 = c0.center.x + (delta.x * a/d);
    py2 = c0.center.y + (delta.y * a/d);

    /* Tangent circles have only one intersection

       TODO: using == in floating point arithmetic
       doesn't account for the machine accuracy, having
       a stated (EmbReal) tolerance value would help.
    */
    if (d == (c0.radius + c1.radius)) {
        p0->x = px2;
        p0->y = py2;
        p1->x = px2;
        p1->y = py2;
        return 1;
    }

    /* Get the perpendicular slope by multiplying by the negative reciprocal
     * Then multiply by the h offset in relation to d to get the actual offsets */
    mx = -(delta.y * h/d);
    my =  (delta.x * h/d);

    /* Add the offsets to point p2 to obtain the intersection points */
    p0->x = px2 + mx;
    p0->y = py2 + my;
    p1->x = px2 - mx;
    p1->y = py2 - my;

    return 1;
}

/****************************************************************
 * Calculates the tangent points on circle from a given point.
 * Returns true if the given point lies outside the circle.
 * Returns false if the given point is inside the circle.
 ****************************************************************/
int
getCircleTangentPoints(EmbCircle c, EmbVector point, EmbVector *t0, EmbVector *t1)
{
    EmbCircle p;
    EmbReal hyp;
    /* Distance to center of circle */
    hyp = embVector_distance(point, c.center);
    /* Point is inside the circle */
    if (hyp < c.radius) {
        return 0;
    } else if (hyp == c.center.y) {
        /* Point is lies on the circle, so there is only one tangent point */
        *t0 = point;
        *t1 = point;
        return 1;
    }

    /* Since the tangent lines are always perpendicular to the radius, so
     * we can use the Pythagorean theorem to solve for the missing side */
    p.center = point;
    p.radius = sqrt((hyp*hyp) - (c.radius*c.radius));
    return getCircleCircleIntersections(c, p, t0, t1);
}
/*
 * ELLIPSE GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

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
/*
 * BASIC FUNCTIONS
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

/* round is C99 and we're committed to C90 so here's a replacement.
 */
int
emb_round(EmbReal x)
{
    EmbReal y = floor(x);
    if (fabs(x-y) > 0.5) {
        return (int)ceil(x);
    }
    return (int)y;
}

EmbReal
radians(EmbReal degree)
{
    return degree*embConstantPi/180.0;
}

EmbReal
degrees(EmbReal radian)
{
    return radian*180.0/embConstantPi;
}
/*
 * LINE GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

/* Finds the normalized vector perpendicular (clockwise) to the line
 * given by v1->v2 (normal to the line) */
EmbVector
embLine_normalVector(EmbLine line, int clockwise)
{
    EmbVector result;
    EmbReal temp;
    result = embVector_subtract(line.end, line.start);
    result = embVector_normalize(result);
    temp = result.x;
    result.x = result.y;
    result.y = -temp;
    if (!clockwise) {
        result.x = -result.x;
        result.y = -result.y;
    }
    return result;
}

/* Returns the vector that is the same length as the line, in the same
 * direction.
 */
EmbVector
embLine_toVector(EmbLine line)
{
    return embVector_subtract(line.end, line.start);
}

/*
 * Finds the intersection of two lines given by v1->v2 and v3->v4
 * and sets the value in the result variable.
 */
EmbVector
embLine_intersectionPoint(EmbLine line1, EmbLine line2)
{
    EmbReal det, C2, C1, tolerance;
    EmbVector vec1, vec2, result;
    emb_error = 0;
    vec1 = embLine_toVector(line1);
    vec2 = embLine_toVector(line2);
    C2 = embVector_cross(line1.start, vec1);
    C1 = embVector_cross(line2.start, vec2);

    tolerance = 1e-10;
    det = embVector_cross(vec2, vec1);

    if (fabs(det) < tolerance) {
        emb_error = 1;
        return result;
    }
    result.x = (vec2.x * C2 - vec1.x * C1) / det;
    result.y = (vec2.y * C2 - vec1.y * C1) / det;
    return result;
}
/*
 * PATH GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */


/*
 * POLYGON GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

/*
 * POLYLINE GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

/*
 * RECT GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

/*
 */
EmbRect
embRect_init(void)
{
    EmbRect rect;
    rect.left = 0.0;
    rect.top = 0.0;
    rect.right = 1.0;
    rect.bottom = 1.0;
    return rect;
}

EmbReal
embRect_area(EmbRect rect)
{
    return (rect.bottom - rect.top) * (rect.right - rect.left);
}
/*
 * TEXT GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

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
/*
 * VECTOR ALGEBRA
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

/**
 * Finds the unit length vector \a result in the same direction as \a vector.
 *
 * Equivalent to:
 *
 * \f[
 *       \mathbf{u} = \frac{v}{|\mathbf{v}|}
 * \f]
 *
 * \todo make result return argument.
 */
EmbVector
embVector_normalize(EmbVector vector)
{
    EmbVector result;
    EmbReal length = embVector_length(vector);
    result.x = vector.x / length;
    result.y = vector.y / length;
    return result;
}

/**
 * The scalar multiple \a magnitude of a vector \a vector. Returned as
 * \a result.
 *
 * \todo make result return argument.
 */
EmbVector
embVector_scale(EmbVector vector, EmbReal magnitude)
{
    EmbVector result;
    result.x = vector.x * magnitude;
    result.y = vector.y * magnitude;
    return result;
}

/**
 * The sum of vectors \a a and \a b returned as a vector.
 *
 * Equivalent to:
 *
 * \f[
 *       \mathbf{c} = \mathbf{a} + \mathbf{b}
 *                  = \begin{pmatrix} a_{x} + b_{x} \\ a_{y}+b_{y} \end{pmatrix}
 * \f]
 */
EmbVector
embVector_add(EmbVector a, EmbVector b)
{
    EmbVector result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

/**
 * The average of vectors \a v1 and \a v2 returned as a vector.
 *
 * Equivalent to:
 *
 * \f[
 *       \mathbf{c} = \frac{\mathbf{a} + \mathbf{b}}{2}
 *                  = \begin{pmatrix} \frac{a_{x} + b_{x}}{2} \\ \frac{a_{y}+b_{y}}{2} \end{pmatrix}
 * \f]
 */
EmbVector
embVector_average(EmbVector a, EmbVector b)
{
    EmbVector result;
    result.x = 0.5*(a.x + b.x);
    result.y = 0.5*(a.y + b.y);
    return result;
}

/**
 * The difference between vectors \a v1 and \a v2 returned as \a result.
 *
 * Equivalent to:
 *
 * \f[
 *       \mathbf{c} = \mathbf{a} - \mathbf{b}
 *                  = \begin{pmatrix} a_{x} - b_{x} \\ a_{y}-b_{y} \end{pmatrix}
 * \f]
 */
EmbVector
embVector_subtract(EmbVector v1, EmbVector v2)
{
    EmbVector result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    return result;
}

/**
 * The dot product as vectors \a v1 and \a v2 returned as a EmbReal.
 *
 * Equivalent to:
 *
 * \f[
 *       c = \mathbf{a} \cdot \mathbf{b}
 *         = a_x b_x + a_y b_y
 * \f]
 */
EmbReal
embVector_dot(EmbVector a, EmbVector b)
{
    return a.x * b.x + a.y * b.y;
}

/**
 * @brief The "cross product" as vectors \a a and \a b returned as a real value.
 *
 * Technically, this is the magnitude of the cross product when the
 * embroidery is placed in the z=0 plane (since the cross product is defined for
 * 3-dimensional vectors). That is:
 *
 * \f[
 *       |c| = \left| \begin{pmatrix} a_x \\ a_y \\ 0 \end{pmatrix} \times \begin{pmatrix} b_x \\ b_y \\ 0 \end{pmatrix}\right|
 *           = \left| \begin{pmatrix} 0 \\ 0 \\ a_x b_y - a_y b_x \end{pmatrix} \right|
 *           = a_x b_y - a_y b_x
 * \f]
 */
EmbReal
embVector_cross(EmbVector a, EmbVector b)
{
    return a.x * b.y - a.y * b.x;
}

/**
 * Since we aren't using full vector algebra here, all vectors are "vertical".
 * so this is like the product v1^{T} I_{2} v2 for our vectors \a v1 and \v2
 * so a "component-wise product". The result is stored at the pointer \a result.
 *
 * That is
 *      (1 0) (a) = (xa)
 * (x y)(0 1) (b)   (yb)
 */
EmbVector
embVector_transpose_product(EmbVector v1, EmbVector v2)
{
    EmbVector result;
    result.x = v1.x * v2.x;
    result.y = v1.y * v2.y;
    return result;
}

/**
 * The length or absolute value of the vector \a vector.
 *
 * Equivalent to:
 *
 * \f[
 *       |v| = \sqrt{v_{x}^{2} + v_{y}^{2}}
 * \f]
 */
EmbReal
embVector_length(EmbVector vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

/**
 * The x-component of the vector
 */
EmbReal
embVector_relativeX(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    b = embVector_subtract(a1, a2);
    c = embVector_subtract(a3, a2);
    return embVector_dot(b, c);
}

/**
 * The y-component of the vector
 */
EmbReal
embVector_relativeY(EmbVector a1, EmbVector a2, EmbVector a3)
{
    EmbVector b, c;
    b = embVector_subtract(a1, a2);
    c = embVector_subtract(a3, a2);
    return embVector_cross(b, c);
}

/**
 * The angle, measured anti-clockwise from the x-axis, of a vector v.
 */
EmbReal
embVector_angle(EmbVector v)
{
    return atan2(v.y, v.x);
}

/**
 * The unit vector in the direction \a angle.
 *
 * \f[
 *       \mathbf{a}_{\alpha} = \begin{pmatrix} \cos(\alpha) \\ \sin(\alpha) \end{pmatrix}
 * \f]
 */
EmbVector
embVector_unit(EmbReal alpha)
{
    EmbVector a;
    a.x = cos(alpha);
    a.y = sin(alpha);
    return a;
}

/**
 * The distance between \a a and \a b returned as a real value.
 *
 * \f[
 *      d = \left|\mathbf{a}-\mathbf{b}\right|
 *        = \sqrt{(a_x-b_x)^{2} + (a_y-b_y)^{2}}
 * \f]
 */
EmbReal
embVector_distance(EmbVector a, EmbVector b)
{
    EmbVector delta = embVector_subtract(a, b);
    return embVector_length(delta);
}
