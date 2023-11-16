/*
 * SVG FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
\subsection Scalable Vector Graphics (.svg)
\addindex svg

The scalable vector graphics (SVG) format is a graphics format
maintained by ...
 */

int svgCreator;

int svgExpect;
int svgMultiValue;

int current_element_id;
SvgAttribute attributeList[1000];
int n_attributes = 0;
char
currentAttribute[1000];
char
currentValue[1000];

#if 0
int svg_identify_element(char *buff);

EmbColor svgColorToEmbColor(char* colorString)
{
    EmbColor c;
    char* pEnd = 0;
    char* colorStr = copy_trim(colorString); /* Trim out any junk spaces */
    int length = strlen(colorStr);
    int tableColor;

    /* SVGTiny1.2 Spec Section 11.13.1 syntax for color values */
    if (length == 7 && colorStr[0] == '#') /* Six digit hex — #rrggbb */ {
        while (*colorStr=='#' && *colorStr!=0) {
            colorStr++;
        }
        c = embColor_fromHexStr(colorStr);
    }
    else if (length == 4 && colorStr[0] == '#') /* Three digit hex — #rgb */ {
        /* Convert the 3 digit hex to a six digit hex */
        char hex[7];
        sprintf(hex, "%c%c%c%c%c%c", colorStr[1], colorStr[1], colorStr[2],
            colorStr[2], colorStr[3], colorStr[3]);

        c = embColor_fromHexStr(hex);
    }
    else if (strstr(colorStr, "%")) /* Float functional — rgb(R%, G%, B%) */ {
        char *s = colorStr;
        /* replace characters we aren't using with spaces */
        for (; *s; s++) {
            if (*s == 'r' || *s == 'g' || *s == 'b' || *s == ','
                || *s == '(' || *s == ')' || *s == '%') {
                *s = ' ';
            }
        }
        c.r = (unsigned char)emb_round(255.0/100.0 * strtod(colorStr, &pEnd));
        c.g = (unsigned char)emb_round(255.0/100.0 * strtod(pEnd,     &pEnd));
        c.b = (unsigned char)emb_round(255.0/100.0 * strtod(pEnd,     &pEnd));
    }
    else if (length > 3 && colorStr[0] == 'r' && colorStr[1] == 'g' && colorStr[2] == 'b') {
        /* Integer functional — rgb(rrr, ggg, bbb) */
        char *s = colorStr;
        /* replace characters we aren't using with spaces */
        for (; *s; s++) {
            if (*s == 'r' || *s == 'g' || *s == 'b' || *s == ','
                || *s == '(' || *s == ')') {
                *s = ' ';
            }
        }
        c.r = (unsigned char)strtol(colorStr, &pEnd, 10);
        c.g = (unsigned char)strtol(pEnd,     &pEnd, 10);
        c.b = (unsigned char)strtol(pEnd,     &pEnd, 10);
    }
    else /* Color keyword */ {
        tableColor = threadColor(colorStr, SVG_Colors);
        if (tableColor < 0) {
            printf("SVG color string not found: %s.\n", colorStr);
            c.r = 0;
            c.g = 0;
            c.b = 0;
        }
        else {
            c.r = (tableColor >> 16) & 0xFF;
            c.g = (tableColor >> 8) & 0xFF;
            c.b = tableColor & 0xFF;
        }
    }

    safe_free(colorStr);
    /* Returns black if all else fails */
    return c;
}

int
toUpper(char cmd)
{
    if (cmd >= 'a' && cmd <= 'z') {
        return cmd - 'a' + 'A';
    }
    return cmd;
}

int svgPathCmdToEmbPathFlag(char cmd)
{
    /* TODO: This function needs some work */
    if     (toUpper(cmd) == 'M') return MOVETO;
    else if (toUpper(cmd) == 'L') return LINETO;
    /*
    else if (toUpper(cmd) == 'C') return CUBICTOCONTROL1;
    else if (toUpper(cmd) == 'CC') return CUBICTOCONTROL2;
    else if (toUpper(cmd) == 'CCC') return CUBICTOEND;
    else if (toUpper(cmd) == 'A') return ELLIPSETORAD;
    else if (toUpper(cmd) == 'AA') return ELLIPSETOEND;
    else if (toUpper(cmd) == 'Q') return QUADTOCONTROL;
    else if (toUpper(cmd) == 'QQ') return QUADTOEND;
    else if (toUpper(cmd) == 'Z') return LINETO;
    */

    /*else if (toUpper(cmd) == 'B') return BULGETOCONTROL; */ /* NOTE: This is not part of the SVG spec, but hopefully Bulges will be added to the SVG spec someday */
    /*else if (toUpper(cmd) == 'BB') return BULGETOEND; */   /* NOTE: This is not part of the SVG spec, but hopefully Bulges will be added to the SVG spec someday */
    /*else { printf("ERROR: svgPathCmdToEmbPathFlag(), unknown command '%c'\n", cmd); return MOVETO; } */

    return LINETO;
}

char* svgAttribute_getValue(const char* name) {
    int i;
    for (i=0; i<n_attributes; i++) {
        if (!strcmp(attributeList[i].name, name)) {
            return attributeList[i].value;
        }
    }
    return "none";
}

void
parse_circle(EmbPattern *p)
{
    EmbCircle circle;
    circle.center.x = atof(svgAttribute_getValue("cx"));
    circle.center.y = atof(svgAttribute_getValue("cy"));
    circle.radius = atof(svgAttribute_getValue("r"));
    embPattern_addCircleAbs(p, circle);
}

void
parse_ellipse(EmbPattern *p)
{
    EmbEllipse ellipse;
    ellipse.center.x = atof(svgAttribute_getValue("cx"));
    ellipse.center.y = atof(svgAttribute_getValue("cy"));
    ellipse.radius.x = atof(svgAttribute_getValue("rx"));
    ellipse.radius.y = atof(svgAttribute_getValue("ry"));
    embPattern_addEllipseAbs(p, ellipse);
}

void
parse_line(EmbPattern *p)
{
    char *x1, *x2, *y1, *y2;
    x1 = svgAttribute_getValue("x1");
    y1 = svgAttribute_getValue("y1");
    x2 = svgAttribute_getValue("x2");
    y2 = svgAttribute_getValue("y2");

    /* If the starting and ending points are the same, it is a point */
    if (!strcmp(x1, x2) && !strcmp(y1, y2)) {
        EmbPoint point;
        point.position.x = atof(x1);
        point.position.y = atof(y1);
        embPattern_addPointAbs(p, point);
    }
    else {
        EmbLine line;
        line.start.x = atof(x1);
        line.start.y = atof(y1);
        line.end.x = atof(x2);
        line.end.y = atof(y2);
        embPattern_addLineAbs(p, line);
    }

}

void
parse_path(EmbPattern *p)
{
    /* TODO: finish */
    EmbVector position, f_point, l_point, c1_point, c2_point;
    int cmd, i, pos, reset, trip;
    EmbReal pathData[7];
    unsigned int numMoves;
    EmbColor color;
    EmbArray* flagList = 0;
    EmbPath path;
    char* pointStr = svgAttribute_getValue("d");
    char* mystrok = svgAttribute_getValue("stroke");
    int last = strlen(pointStr);
    int size = 32;
    int pendingTask = 0;
    int relative = 0;
    char* pathbuff = 0;

    EmbArray* pointList = 0;
    pos = 0;
    /* An odometer aka 'tripometer' used for stepping thru the pathData */
    trip = -1;
    /* count of float[] that has been filled.
     * 0 = first item of array
     * -1 = not filled = empty array
     */
    reset = -1;
    position.x = 0.0;
    position.y = 0.0;
    f_point.x = 0.0;
    f_point.y = 0.0;
    l_point.x = 0.0;
    l_point.y = 0.0;
    c1_point.x = 0.0;
    c1_point.y = 0.0;
    c2_point.x = 0.0;
    c2_point.y = 0.0;
    cmd = 0;
    numMoves = 0;

    pathbuff = (char*)malloc(size);
    if (!pathbuff) {
        printf("ERROR: svgAddToPattern(), cannot allocate memory for pathbuff\n");
        return;
    }

    printf("stroke:%s\n", mystrok);

    for (i = 0; i < last; i++) {
        char c = pointStr[i];
        if (emb_verbose>1) {
            printf("relative %d\n", relative);
            printf("c1.x %f\n", c1_point.x);
            printf("c2.x %f\n", c2_point.x);
        }
        switch (c) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                pathbuff[pos++] = (char)c;                  /* add a more char */
                break;

            case ' ':
            case ',':

                /*printf("    ,'%s'    ~POS=%d  ~TRIP=%d  ~[pos]=%d\n", pathbuff,pos,trip, pathbuff[pos]);*/
                if (pos > 0) {         /* append float to array, if it not yet stored */
                    pathbuff[pos] = 0;
                    pos = 0;
                    printf("    ,val:%s\n", pathbuff);
                    pathData[++trip] = atof(pathbuff);
                }
                break;

            case '-':

                if (pos > 0) {
                    /* append float to array, if it not yet stored */
                    pathbuff[pos] = 0;
                    pos = 0;
                    printf("    -val:%s\n", pathbuff);
                    pathData[++trip] = atof(pathbuff);
                }
                pathbuff[pos++] = (char)c;
                /* add a more char */
                break;

            default:
                    /*** ASSUMED ANY COMMAND FOUND ***/


                    if (pos > 0) {
                        /* just make sure: append float to array,
                         * if it not yet stored
                         */
                        pathbuff[pos] = 0;
                        pos = 0;
                        printf("    >val:%s\n", pathbuff);
                        pathData[++trip] = atof(pathbuff);
                    }

                    /**** Compose Point List ****/

                    /* below "while" is for avoid losing last 'z'
                     * command that maybe never accommodated.
                     */
                    pendingTask = 1; if (i==last-1) {pendingTask = 2;}

                    while (pendingTask > 0) {
                        pendingTask -= 1;

                    /* Check whether prior command need to be saved */
                    if (trip>=0) {
                        EmbPoint test;
                        trip = -1;
                        reset = -1;

                        relative = 0;
                        /* relative to prior coordinate point
                         * or absolute coordinate? */

                        if (cmd >= 'a' && cmd <= 'z') {
                            relative = 1;
                        }

                        if (cmd == 'M' || cmd == 'm') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                            f_point = position;
                        }
                        else if (cmd == 'L' || cmd == 'l') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'H' || cmd == 'h') {
                            position.x = pathData[0];
                            position.y = l_point.y;
                        }
                        else if (cmd == 'V'  || cmd == 'v') {
                            position.x = l_point.x;
                            position.y = pathData[1];
                        }
                        else if (cmd == 'C' || cmd == 'c') {
                            position.x = pathData[4];
                            position.y = pathData[5];
                            c1_point.x = pathData[0];
                            c1_point.y = pathData[1];
                            c2_point.x = pathData[2];
                            c2_point.y = pathData[3];
                        }
                        /*
                        else if (cmd == 'S') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 's') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'Q') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'q') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'T') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 't') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'A') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        else if (cmd == 'a') {
                            position.x = pathData[0];
                            position.y = pathData[1];
                        }
                        */
                        else if (cmd == 'Z' || cmd == 'z') {
                            position = f_point;
                        }

                        if (!pointList && !flagList) {
                            pointList = embArray_create(EMB_POINT);
                            flagList = embArray_create(EMB_FLAG);
                        }
                        test.position = position;
                        embArray_addPoint(pointList, test);
                        embArray_addFlag(flagList, svgPathCmdToEmbPathFlag(cmd));
                        l_point = position;

                        pathbuff[0] = (char)cmd;                  /* set the command for compare */
                        pathbuff[1] = 0;
                        pos = 0;

                        printf("*prior:%s (%f, %f,  %f, %f,     %f,%f,  %f) \n", pathbuff,
                                pathData[0],
                                pathData[1],
                                pathData[2],
                                pathData[3],
                                pathData[4],
                                pathData[5],
                                pathData[6]
                                );

                    }

                    /* assign new command */
                    if (trip == -1 && reset == -1) {
                        /* set the command for compare */
                        pathbuff[0] = (char)c;
                        pathbuff[1] = 0;

                        printf("cmd:%s\n", pathbuff);
                        if (c == 'M' || c == 'm' || c == 'L' || c == 'l') {
                            cmd = c;
                            reset = 2;
                            numMoves++;
                        }
                        else if (c == 'C' || c == 'c') {
                            cmd = c;
                            reset = 6;
                        }
                        else if (c == 'H' || c == 'h' || c == 'V' || c == 'v') {
                            cmd = c;
                            reset = 1;
                        }
                        else if (c == 'S' || c == 's' || c == 'Q' || c == 'q') {
                            cmd = c;
                            reset = 4;
                        }
                        else if (c == 'T' || c == 't') {
                            cmd = c;
                            reset = 2;
                        }
                        else if (c == 'A' || c == 'a') {
                            cmd = c;
                            reset = 7;
                        }
                        else if (c == 'Z' || c == 'z') {
                            cmd = c;
                            reset = 0;
                        }
                        else {
                            printf("ERROR: svgAddToPattern(), %s is not a valid svg path command, skipping...\n", pathbuff);
                            trip = -1;
                            reset = -1;
                        }
                    }
                    /* avoid losing 'z' command that maybe never accommodated. */
                        if (i==last-1) {
                            trip = 2;
                        }
                    } /* while pendingTask */


                    break;
        }
        if (pos >= size - 1) {
            /* increase pathbuff length - leave room for 0 */
            size *= 2;
            pathbuff = (char*)realloc(pathbuff, size);
            if (!pathbuff) {
                printf("ERROR: svgAddToPattern(), cannot re-allocate memory for pathbuff\n");
                return;
            }
        }
    }
    safe_free(pathbuff);

    /* TODO: subdivide numMoves > 1 */

    color = svgColorToEmbColor(svgAttribute_getValue("stroke"));

    path.pointList = pointList;
    path.flagList = flagList;
    path.color = color;
    path.lineType = 1;
    embPattern_addPathAbs(p, path);
}

EmbArray *parse_pointlist(EmbPattern *p)
{
    char* pointStr = svgAttribute_getValue("points");
    int last = strlen(pointStr);
    int size = 32;
    int i = 0;
    int pos = 0;
    unsigned char odd = 1;
    EmbReal xx = 0.0;
    EmbReal yy = 0.0;

    EmbArray* pointList = 0;

    char* polybuff = 0;

    if (emb_verbose > 1) {
        printf("Called with %p\n", (void*)p);
    }

    polybuff = (char*)malloc(size);
    if (!polybuff) {
        printf("ERROR: svgAddToPattern(), cannot allocate memory for polybuff\n");
        return pointList;
    }
    for (i = 0; i < last; i++) {
        char c = pointStr[i];
        switch (c) {
            case ' ':
                if (pos == 0) {
                    break;
                }
                polybuff[pos] = 0;
                pos = 0;
                /*Compose Point List */
                if (odd) {
                    odd = 0;
                    xx = atof(polybuff);
                }
                else {
                    EmbPoint a;
                    odd = 1;
                    yy = atof(polybuff);

                    if (!pointList) {
                        pointList = embArray_create(EMB_POINT);
                    }
                    a.position.x = xx;
                    a.position.y = yy;
                    embArray_addPoint(pointList, a);
                }

                break;
            default:
                polybuff[pos++] = (char)c;
                break;
        }
        if (pos >= size - 1) {
             /* increase polybuff length - leave room for 0 */
             size *= 2;
             polybuff = (char*)realloc(polybuff, size);
             if (!polybuff) {
                 printf("ERROR: svgAddToPattern(), cannot re-allocate memory for polybuff\n");
                 return NULL;
             }
        }
    }
    safe_free(polybuff);
    return pointList;
}

void
parse_polygon(EmbPattern *p)
{
    if (emb_verbose > 1) {
        printf("Called with %p\n", (void*)p);
    }
    /*
    EmbPolygonObject polygonObj;
    polygonObj.pointList = embArray_create(EMB_POINT);
    BROKEN: polygonObj.pointList = parse_pointlist(p);
    polygonObj.color = svgColorToEmbColor(svgAttribute_getValue("stroke"));
    polygonObj.lineType = 1; TODO: use lineType enum
    embPattern_addPolygonObjectAbs(p, &polygonObj);
    */
}

void
parse_polyline(EmbPattern *p)
{
    if (emb_verbose > 1) {
        printf("Called with %p\n", (void*)p);
    }
    /* BROKEN
    EmbPolylineObject* polylineObj;
    polylineObj = (EmbPolylineObject*)malloc(sizeof(EmbPolylineObject));
    polylineObj->pointList = parse_pointlist(p);
    polylineObj->color = svgColorToEmbColor(svgAttribute_getValue("stroke"));
    polylineObj->lineType = 1; TODO: use lineType enum
    embPattern_addPolylineObjectAbs(p, polylineObj);
    */
}

void
parse_rect(EmbPattern *p)
{
    EmbRect rect;
    float width, height;
    rect.left = atof(svgAttribute_getValue("x"));
    rect.top = atof(svgAttribute_getValue("y"));
    width = atof(svgAttribute_getValue("width"));
    height = atof(svgAttribute_getValue("height"));
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;
    embPattern_addRectAbs(p, rect);
}

void
svgAddToPattern(EmbPattern* p)
{
    if (!p) {
        printf("ERROR: svgAddToPattern(), p argument is null\n");
        return;
    }
    switch (current_element_id) {
    case ELEMENT_CIRCLE:
        parse_circle(p);
        break;
    case ELEMENT_ELLIPSE:
        parse_ellipse(p);
        break;
    case ELEMENT_LINE:
        parse_line(p);
        break;
    case ELEMENT_PATH:
        parse_path(p);
        break;
    case ELEMENT_POLYGON:
        parse_polygon(p);
        break;
    case ELEMENT_POLYLINE:
        parse_polygon(p);
        break;
    case ELEMENT_RECT:
        parse_rect(p);
        break;
    default:
        break;
    }
}

int svg_identify_element(char *buff)
{
    int i;
    for (i=0; svg_element_tokens[i][0]; i++) {
        if (!strcmp(buff, svg_element_tokens[i])) {
            return i;
        }
    }
    return -1;
}

int svgIsElement(const char* buff) {
    if (stringInArray(buff, svg_element_tokens)) {
        return SVG_ELEMENT;
    }
    /* Attempt to identify the program that created the SVG file.
     * This should be in a comment at that occurs before the svg element. */
    else if (!strcmp(buff, "Embroidermodder")) {
        svgCreator = SVG_CREATOR_EMBROIDERMODDER;
    }
    else if (!strcmp(buff, "Illustrator")) {
        svgCreator = SVG_CREATOR_ILLUSTRATOR;
    }
    else if (!strcmp(buff, "Inkscape")) {
        svgCreator = SVG_CREATOR_INKSCAPE;
    }

    return SVG_NULL;
}

/*
int svgIsSvgAttribute(const char* buff) {
    const char *inkscape_tokens[] = {
        "xmlns:dc", "xmlns:cc", "xmlns:rdf", "xmlns:svg", "xmlns", "\0"
    };
    if (stringInArray(buff, svg_attribute_tokens)) {
        return SVG_ATTRIBUTE;
    }
    if (svgCreator == SVG_CREATOR_INKSCAPE) {
        if (stringInArray(buff, inkscape_tokens)) {
            return SVG_ATTRIBUTE;
        }
    }
    printf("svgIsSvgAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}
*/

void
svgProcess(int c, const char* buff)
{
    if (svgExpect == SVG_EXPECT_ELEMENT) {
        char advance = 0;
        if (buff[0] == '/') {
            return;
        }
        advance = (char)svgIsElement(buff);
        if (advance) {
            printf("ELEMENT:\n");
            svgExpect = SVG_EXPECT_ATTRIBUTE;
            current_element_id = svg_identify_element((char*)buff);
        } else {
            return;
        }
    } else if (svgExpect == SVG_EXPECT_ATTRIBUTE) {
        char advance = 0;
        switch (current_element_id) {
        case ELEMENT_A:
        case ELEMENT_CIRCLE:
        case ELEMENT_DEFS:
        case ELEMENT_ELLIPSE:
        case ELEMENT_FOREIGN_OBJECT:
        case ELEMENT_G:
        case ELEMENT_LINE:
        case ELEMENT_LINEAR_GRADIENT:
        case ELEMENT_PATH:
        case ELEMENT_POLYGON:
        case ELEMENT_POLYLINE:
        case ELEMENT_RADIAL_GRADIENT:
        case ELEMENT_RECT:
        case ELEMENT_SOLID_COLOR:
        case ELEMENT_STOP:
        case ELEMENT_SVG:
        case ELEMENT_SWITCH:
        case ELEMENT_TEXT:
        case ELEMENT_TEXT_AREA:
        case ELEMENT_TSPAN:
        case ELEMENT_USE:
            if (stringInArray(buff, svg_property_tokens)) {
                advance = SVG_PROPERTY;
            }
            break;
        case ELEMENT_ANIMATION:
        case ELEMENT_AUDIO:
        case ELEMENT_DESC:
        case ELEMENT_IMAGE:
        case ELEMENT_METADATA:
        case ELEMENT_TITLE:
        case ELEMENT_VIDEO:
            if (stringInArray(buff, svg_media_property_tokens)) {
                advance = SVG_MEDIA_PROPERTY;
            }
            break;
            default: break;
        }
        if (!advance) {
            if (stringInArray(buff, (const char **)svg_attribute_table[current_element_id])) {
                advance = SVG_ATTRIBUTE;
            }
            printf("ERROR %s not found in svg_attribute_table[%d].\n",
                buff, current_element_id);
        }
        if (advance) {
            printf("ATTRIBUTE:\n");
            svgExpect = SVG_EXPECT_VALUE;
            strcpy(currentAttribute, buff);
        }
    } else if (svgExpect == SVG_EXPECT_VALUE) {
        int last = strlen(buff) - 1;
        printf("VALUE:\n");

        /* single-value */
        if ((buff[0] == '"' || buff[0] == '\'') && (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') && !svgMultiValue) {
            svgExpect = SVG_EXPECT_ATTRIBUTE;
            strcpy(attributeList[n_attributes].name, currentAttribute);
            strcpy(attributeList[n_attributes].value, buff);
            n_attributes++;
        } else { /* multi-value */
            svgMultiValue = 1;
            if (strlen(currentValue)==0) {
                strcpy(currentValue, buff);
            }
            else {
                strcat(currentValue, " ");
                strcat(currentValue, buff);
            }
            if (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') {
                svgMultiValue = 0;
                svgExpect = SVG_EXPECT_ATTRIBUTE;
                strcpy(attributeList[n_attributes].name, currentAttribute);
                strcpy(attributeList[n_attributes].value, currentValue);
                n_attributes++;
            }
        }
    }
    if (svgExpect != SVG_EXPECT_NULL) {
        printf("%s\n", buff);
    }
    if (c == '>') {
        svgExpect = SVG_EXPECT_NULL;
    }
}
#endif


char
readSvg(EmbPattern* pattern, FILE* file) {
    int size, pos, i;
    char* buff = 0, c;
    size = 1024;

    puts("Deactived readSvg for testing.");
    return 0;

#if 0
    for (i=0; i<1000; i++) {
        attributeList[i].name = (char*)malloc(size);
        attributeList[i].value = (char*)malloc(size);
    }

    buff = (char*)malloc(size);
    if (!buff) {
        printf("ERROR: readSvg(), cannot allocate memory for buff\n");
        return 0;
    }
    svgCreator = SVG_CREATOR_NULL;
    svgExpect = SVG_EXPECT_NULL;
    svgMultiValue = 0;

    currentAttribute[0] = 0;
    currentValue[0] = 0;

    /* Pre-flip in case of multiple reads on the same pattern */
    embPattern_flipVertical(pattern);

    pos = 0;
    while (fread(&c, 1, 1, file)) {
        switch (c) {
        case '<':
            if (svgExpect == SVG_EXPECT_NULL) {
                svgAddToPattern(pattern);
                svgExpect = SVG_EXPECT_ELEMENT;
            }
            break;
        case '>':
            /* abnormal case that may occur in svg element where '>' is all by itself */
            if (pos == 0) {
                /*TODO: log a warning about this absurdity! */
                svgExpect = SVG_EXPECT_ELEMENT;
            }
            break;
        case ' ':
        case '\t':
        case '\r':
        case '\n':
        case '=':
            if (pos == 0)
                break;
            buff[pos] = 0;
            pos = 0;
            svgProcess(c, buff);
            break;
        default:
            buff[pos++] = (char)c;
            break;
        }
        if (pos >= size - 1) {
            /* increase buff length - leave room for 0 */
            size *= 2;
            buff = (char*)realloc(buff, size);
            if (!buff) {
                printf("ERROR: readSvg(), cannot re-allocate memory for buff\n");
                return 0;
            }
        }
    }

    safe_free(buff);

    if (emb_verbose>1) {
        printf("OBJECT SUMMARY:\n");
        if (pattern->circles) {
            for (i = 0; i < pattern->circles->count; i++) {
                EmbCircle c = pattern->circles->circle[i];
                printf("circle %f %f %f\n", c.center.x, c.center.y, c.radius);
            }
        }
        if (pattern->ellipses) {
            for (i = 0; i < pattern->ellipses->count; i++) {
                EmbEllipse e = pattern->ellipses->ellipse[i];
                printf("ellipse %f %f %f %f\n", e.center.x, e.center.y, e.radius.x, e.radius.y);
            }
        }
        if (pattern->geometry) {
            for (i = 0; i < pattern->geometry->count; i++) {
                EmbLine li = pattern->geometry->geometry[i].object.line;
                printf("line %f %f %f %f\n", li.start.x, li.start.y, li.end.x, li.end.y);
            }
        }
        if (pattern->points) {
            for (i = 0; i < pattern->points->count; i++) {
                EmbVector po = pattern->points->point[i].position;
                printf("point %f %f\n", po.x, po.y);
            }
        }
        if (pattern->polygons) {
            for (i = 0; i < pattern->polygons->count; i++) {
                EmbArray *verts = pattern->polygons->polygon[i].pointList;
                printf("polygon %d\n", verts->count);
            }
        }
        if (pattern->polylines) {
            for (i = 0; i < pattern->polylines->count; i++) {
                EmbArray * verts = pattern->polylines->polyline[i].pointList;
                printf("polyline %d\n", verts->count);
            }
        }
        if (pattern->rects) {
            for (i = 0; i < pattern->rects->count; i++) {
                EmbRect r = pattern->rects->rect[i];
                EmbReal width = r.right - r.left;
                EmbReal height = r.bottom - r.top;
                printf("rect %f %f %f %f\n", r.left, r.top, width, height);
            }
        }
    }

    for (i=0; i<1000; i++) {
        safe_free(attributeList[i].name);
        safe_free(attributeList[i].value);
    }
    /* Flip the pattern since SVG Y+ is down and libembroidery Y+ is up. */
    embPattern_flipVertical(pattern);
#endif
    return 1; /*TODO: finish readSvg */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char
writeSvg(EmbPattern* pattern, FILE *file)
{
    EmbRect boundingRect;
    EmbRect rect;
    EmbColor color;
    int i, j;
    char isNormal, tmpX[32], tmpY[32];
    EmbRect border;

    /* Pre-flip the pattern since SVG Y+ is down and libembroidery Y+ is up. */
    embPattern_flipVertical(pattern);
    boundingRect = embPattern_calcBoundingBox(pattern);
    fprintf(file, "<?xml version=\"1.0\"?>\n");
    fprintf(file, "<!-- Embroidermodder 2 SVG Embroidery File -->\n");
    fprintf(file, "<!-- http://embroidermodder.github.io -->\n");
    fprintf(file, "<svg ");

    /* TODO: See the SVG Tiny Version 1.2 Specification Section 7.14.
    *       Until all of the formats and API is stable, the width, height and viewBox attributes need to be left unspecified.
    *       If the attribute values are incorrect, some applications wont open it at all.
    */

    /* Add a margin of 10%. */
    border = boundingRect;
    border.left *= 10.0;
    border.right *= 10.0;
    border.top *= 10.0;
    border.bottom *= 10.0;
    border.left -= 0.1*(border.right - border.left);
    border.right += 0.1*(border.right - border.left);
    border.top -= 0.1*(border.bottom - border.top);
    border.bottom += 0.1*(border.bottom - border.top);
    /* Sanity check here? */
    fprintf(file, "viewBox=\"%f %f %f %f\" ",
            border.left, border.top,
            border.right - border.left,
            border.bottom - border.top);

    fprintf(file, "xmlns=\"http://www.w3.org/2000/svg\" version=\"1.2\" baseProfile=\"tiny\">");
    fprintf(file, "\n<g transform=\"scale(10)\">");
    /*TODO: Low Priority Optimization:
    *      Using %g in embFile_printf just doesn't work good enough at trimming trailing zeroes.
    *      It's precision refers to significant digits, not decimal places (which is what we want).
    *      We need to roll our own function for trimming trailing zeroes to keep
    *      the precision as high as possible if needed, but help reduce file size also. */

    /*TODO: Low Priority Optimization:
    *      Make sure that the line length that is output doesn't exceed 1000 characters. */

    /*TODO: Low Priority: Indent output properly. */

    /* write circles, ellipses and lines */
    for (i = 0; i < pattern->geometry->count; i++) {
        EmbGeometry g = pattern->geometry->geometry[i];
        switch (g.type) {
        case EMB_CIRCLE: {
            EmbCircle circle = g.object.circle;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file, "\n<circle stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" cx=\"%f\" cy=\"%f\" r=\"%f\" />",
                g.color.r,
                g.color.g,
                g.color.b,
                circle.center.x,
                circle.center.y,
                circle.radius);
            break;
        }
        case EMB_ELLIPSE: {
            EmbEllipse ellipse = g.object.ellipse;
            color = g.color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file, "\n<ellipse stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" />",
                        color.r,
                        color.g,
                        color.b,
                        ellipse.center.x,
                        ellipse.center.y,
                        ellipse.radius.x,
                        ellipse.radius.y);
            break;
        }
        case EMB_LINE: {
            EmbLine line = g.object.line;
            color = g.color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file,
                "\n<line stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />",
                color.r, color.g, color.b,
                line.start.x, line.start.y, line.end.x, line.end.y);
            break;
        }
        case EMB_POINT: {
            EmbPoint p = g.object.point;
            /* See SVG Tiny 1.2 Spec:
             * Section 9.5 The 'line' element
             * Section C.6 'path' element implementation notes */
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file,
                "\n<line stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />",
                p.color.r, p.color.g, p.color.b,
                p.position.x, p.position.y, p.position.x, p.position.y);
            break;
        }
        case EMB_POLYGON: {
            EmbArray *pointList = g.object.polygon.pointList;
            color = g.object.color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
                fprintf(file, "\n<polygon stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"%s,%s",
                    color.r, color.g, color.b,
                    emb_optOut(pointList->geometry[0].object.point.position.x, tmpX),
                    emb_optOut(pointList->geometry[0].object.point.position.y, tmpY));
            for (j=1; j < pointList->count; j++) {
                fprintf(file, " %s,%s",
                    emb_optOut(pointList->geometry[j].object.point.position.x, tmpX),
                    emb_optOut(pointList->geometry[j].object.point.position.y, tmpY));
            }
            fprintf(file, "\"/>");
            break;
        }
        case EMB_POLYLINE: {
            EmbArray *pointList = g.object.polyline.pointList;
            color = g.object.polyline.color;
            /* TODO: use proper thread width for stoke-width rather
             * than just 0.2.
             */
            fprintf(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"%s,%s",
                    color.r,
                    color.g,
                    color.b,
                    emb_optOut(pointList->geometry[0].object.point.position.x, tmpX),
                    emb_optOut(pointList->geometry[0].object.point.position.y, tmpY));
            for (j=1; j < pointList->count; j++) {
                fprintf(file, " %s,%s",
                    emb_optOut(pointList->geometry[j].object.point.position.x, tmpX),
                    emb_optOut(pointList->geometry[j].object.point.position.y, tmpY));
            }
            fprintf(file, "\"/>");
            break;
        }
        case EMB_RECT: {
            rect = g.object.rect;
            color = g.object.color;
            /* TODO: use proper thread width for stoke-width rather
             * than just 0.2.
             */
            fprintf(file, "\n<rect stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" />",
                color.r, color.g, color.b,
                rect.left, rect.top,
                rect.right - rect.left,
                rect.bottom - rect.top);
            break;
        }
        default:
            break;
        }
    }

    isNormal = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* TODO:
         * #ifdef SVG_DEBUG for Josh which outputs
         * JUMPS/TRIMS instead of chopping them out.
         */
        if (st.flags == NORMAL && !isNormal) {
            isNormal = 1;
            color = pattern->thread_list->thread[st.color].color;
            /* TODO: use proper thread width for stoke-width rather
             * than just 0.2.
             */
              fprintf(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"%s,%s",
                                color.r,
                                color.g,
                                color.b,
                                emb_optOut(st.x, tmpX),
                                emb_optOut(st.y, tmpY));
            }
            else if (st.flags == NORMAL && isNormal)
            {
                fprintf(file, " %s,%s", emb_optOut(st.x, tmpX), emb_optOut(st.y, tmpY));
            }
            else if (st.flags != NORMAL && isNormal)
            {
                isNormal = 0;
                fprintf(file, "\"/>");
            }
    }
    fprintf(file, "\n</g>\n</svg>\n");

    /* Reset the pattern so future writes(regardless of format)
     * are not flipped.
     */
    embPattern_flipVertical(pattern);

    return 1;
}

