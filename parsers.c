/*
 * This file is part of libembroidery.
 *
 * Copyright 2021 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * This file contains parsers for the more complex markup languages
 * dealt with by the library.
 */

#include "embroidery.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int svg_parser(char *s, char **token_table)
{
    return 0;
}

int svgCreator;

int svgExpect;
int svgMultiValue;

SvgElement* currentElement;
char* currentAttribute;
char* currentValue;

const char *svg_element_tokens[] = {
    "a", "animate", "animateColor", "animateMotion", "animateTransform", "animation",
    "audio", "circle", "defs", "desc", "discard", "ellipse",
    "font", "font-face", "font-face-src", "font-face-uri", "foreignObject",
    "g", "glyph", "handler", "hkern", "image", "line", "linearGradient", "listener",
    "metadata", "missing-glyph", "mpath", "path", "polygon", "polyline", "prefetch",
    "radialGradient", "rect", "script", "set", "solidColor", "stop", "svg", "switch",
    "tbreak", "text", "textArea", "title", "tspan", "use", "video", "\0"
    /* "altGlyph", "altGlyphDef", "altGlyphItem", "clipPath", "color-profile", "cursor",
     * "feBlend", "feColorMatrix", "feComponentTransfer", "feComposite", "feConvolveMatrix",
     * "feDiffuseLighting", "feDisplacementMap", "feDistantLight", "feFlood",
     * "feFuncA", "feFuncB", "feFuncG", "feFuncR", "feGaussianBlur", "feImage",
     * "feMerge", "feMergeNode", "feMorphology", "feOffset", "fePointLight",
     * "feSpecularLighting", "feSpotLight", "feTile", "feTurbulence", "filter",
     * "font-face-format", "font-face-name", "glyphRef", "marker", "mask",
     * "pattern", "style", "symbol", "textPath", "tref", "view", "vkern"
     * TODO: not implemented SVG Full 1.1 Spec Elements */
};

const char *svg_media_property_tokens[] = {
    "audio-level", "buffered-rendering", "display", "image-rendering",
    "pointer-events", "shape-rendering", "text-rendering", "viewport-fill",
    "viewport-fill-opacity", "visibility", "\0"
};

const char *svg_property_tokens[] = {
    "audio-level", "buffered-rendering", "color", "color-rendering", "direction",
    "display", "display-align", "fill", "fill-opacity", "fill-rule",
    "font-family", "font-size", "font-style", "font-variant", "font-weight",
    "image-rendering", "line-increment", "opacity", "pointer-events",
    "shape-rendering", "solid-color", "solid-opacity", "stop-color",
    "stop-opacity", "stroke", "stroke-dasharray", "stroke-linecap", "stroke-linejoin",
    "stroke-miterlimit", "stroke-opacity", "stroke-width", "text-align",
    "text-anchor", "text-rendering", "unicode-bidi", "vector-effect",
    "viewport-fill", "viewport-fill-opacity", "visibility", "\0"
};

EmbColor svgColorToEmbColor(char* colorString)
{
    EmbColor c;
    char* pEnd = 0;
    char* colorStr = copy_trim(colorString); /* Trim out any junk spaces */
    int length = strlen(colorStr);
    int tableColor;

    /* SVGTiny1.2 Spec Section 11.13.1 syntax for color values */
    if (length == 7 && colorStr[0] == '#') /* Six digit hex — #rrggbb */
    {
        c = embColor_fromHexStr(lTrim(colorStr, '#'));
    }
    else if (length == 4 && colorStr[0] == '#') /* Three digit hex — #rgb */
    {
        /* Convert the 3 digit hex to a six digit hex */
        char hex[7];
        sprintf(hex, "%c%c%c%c%c%c", colorStr[1], colorStr[1], colorStr[2],
            colorStr[2], colorStr[3], colorStr[3]);

        c = embColor_fromHexStr(hex);
    }
    else if (strstr(colorStr, "%")) /* Float functional — rgb(R%, G%, B%) */
    {
        charReplace(colorStr, "rgb,()%", "      ");
        c.r = (unsigned char)round(255.0/100.0 * strtod(colorStr, &pEnd));
        c.g = (unsigned char)round(255.0/100.0 * strtod(pEnd,     &pEnd));
        c.b = (unsigned char)round(255.0/100.0 * strtod(pEnd,     &pEnd));
    }
    else if (length > 3 && startsWith("rgb", colorStr)) /* Integer functional — rgb(rrr, ggg, bbb) */
    {
        charReplace(colorStr, "rgb,()", "     ");
        c.r = (unsigned char)strtol(colorStr, &pEnd, 10);
        c.g = (unsigned char)strtol(pEnd,     &pEnd, 10);
        c.b = (unsigned char)strtol(pEnd,     &pEnd, 10);
    }
    else /* Color keyword */
    {
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

    free(colorStr);
    /* Returns black if all else fails */
    return c;
}

int svgPathCmdToEmbPathFlag(char cmd)
{
    /* TODO: This function needs some work */
    /*
    if     (toUpper(cmd) == 'M') return MOVETO;
    else if (toUpper(cmd) == 'L') return LINETO;
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
    /*else { printf("ERROR: format-svg.c svgPathCmdToEmbPathFlag(), unknown command '%c'\n", cmd); return MOVETO; } */

    return LINETO;
}

SvgAttribute svgAttribute_create(const char* name, const char* value) {
    SvgAttribute attribute;
    char* modValue = 0;
    modValue = emb_strdup(value);
    charReplace(modValue, "\"'/,", "    ");
    attribute.name = emb_strdup(name);
    attribute.value = modValue;
    return attribute;
}

void svgElement_addAttribute(SvgElement* element, SvgAttribute data) {
    if (!element) {
        printf("ERROR: format-svg.c svgElement_addAttribute(), element argument is null\n");
        return;
    }
    if (!(element->attributeList)) {
        element->attributeList = (SvgAttributeList*)malloc(sizeof(SvgAttributeList));
        if (!(element->attributeList)) { printf("ERROR: format-svg.c svgElement_addAttribute(), cannot allocate memory for element->attributeList\n"); return; }
        element->attributeList->attribute = data;
        element->attributeList->next = 0;
        element->lastAttribute = element->attributeList;
        element->lastAttribute->next = 0;
    } else {
        SvgAttributeList* pointerLast = element->lastAttribute;
        SvgAttributeList* list = (SvgAttributeList*)malloc(sizeof(SvgAttributeList));
        if (!list) { printf("ERROR: format-svg.c svgElement_addAttribute(), cannot allocate memory for list\n"); return; }
        list->attribute = data;
        list->next = 0;
        pointerLast->next = list;
        element->lastAttribute = list;
    }
}

void svgElement_free(SvgElement* element) {
    SvgAttributeList* list;
    SvgAttributeList* nextList;
    if (!element) {
        return;
    }
    list = element->attributeList;
    while (list) {
        free(list->attribute.name);
        free(list->attribute.value);
        nextList = list->next;
        free(list);
        list = nextList;
    }

    element->lastAttribute = 0;
    free(element->name);
    free(element);
}

SvgElement* svgElement_create(const char* name) {
    SvgElement* element = 0;
    element = (SvgElement*)malloc(sizeof(SvgElement));
    if (!element) {
        printf("ERROR: format-svg.c svgElement_create(), cannot allocate memory for element\n");
        return 0;
    }
    element->name = emb_strdup(name);
    if (!element->name) {
        printf("ERROR: format-svg.c svgElement_create(), element->name is null\n");
        return 0;
    }
    element->attributeList = 0;
    element->lastAttribute = 0;
    return element;
}

char* svgAttribute_getValue(SvgElement* element, const char* name) {
    SvgAttributeList* pointer = 0;
    if (!element) { 
        printf("ERROR: format-svg.c svgAttribute_getValue(), element argument is null\n"); 
        return (char *)"none"; 
    }
    if (!name) { 
        printf("ERROR: format-svg.c svgAttribute_getValue(), name argument is null\n");
        return (char *)"none"; 
    }
    if (!element->attributeList) { 
        /* TODO: error */ 
        return (char *)"none"; 
    }
    pointer = element->attributeList;
    while (pointer) {
        if (!strcmp(pointer->attribute.name, name)) { return pointer->attribute.value; }
        pointer = pointer->next;
    }
    return "none";
}

void svgAddToPattern(EmbPattern* p) {
    const char* buff = 0;
    if (!p) {
        printf("ERROR: format-svg.c svgAddToPattern(), p argument is null\n");
        return;
    }
    if (!currentElement) {
        return;
    }
    buff = currentElement->name;
    if (!buff) {
        return;
    }
    if (!strcmp(buff, "?xml")) { }
    else if (!strcmp(buff, "a"))                {  }
    else if (!strcmp(buff, "animate"))          {  }
    else if (!strcmp(buff, "animateColor"))     {  }
    else if (!strcmp(buff, "animateMotion"))    {  }
    else if (!strcmp(buff, "animateTransform")) {  }
    else if (!strcmp(buff, "animation"))        {  }
    else if (!strcmp(buff, "audio"))            {  }
    else if (!strcmp(buff, "circle")) {
        embPattern_addCircleObjectAbs(p, atof(svgAttribute_getValue(currentElement, "cx")),
                                         atof(svgAttribute_getValue(currentElement, "cy")),
                                         atof(svgAttribute_getValue(currentElement, "r")));
    } else if (!strcmp(buff, "defs")) {

    } else if (!strcmp(buff, "desc"))             {  

    } else if (!strcmp(buff, "discard"))          {  }
    else if (!strcmp(buff, "ellipse")) {
        embPattern_addEllipseObjectAbs(p, atof(svgAttribute_getValue(currentElement, "cx")),
                                          atof(svgAttribute_getValue(currentElement, "cy")),
                                          atof(svgAttribute_getValue(currentElement, "rx")),
                                          atof(svgAttribute_getValue(currentElement, "ry")));
    } else if (!strcmp(buff, "font"))             {  

    } else if (!strcmp(buff, "font-face"))        {  }
    else if (!strcmp(buff, "font-face-src"))    {  }
    else if (!strcmp(buff, "font-face-uri"))    {  }
    else if (!strcmp(buff, "foreignObject"))    {  }
    else if (!strcmp(buff, "g"))                {  }
    else if (!strcmp(buff, "glyph"))            {  }
    else if (!strcmp(buff, "handler"))          {  }
    else if (!strcmp(buff, "hkern"))            {  }
    else if (!strcmp(buff, "image"))            {  }
    else if (!strcmp(buff, "line")) {
        char* x1 = svgAttribute_getValue(currentElement, "x1");
        char* y1 = svgAttribute_getValue(currentElement, "y1");
        char* x2 = svgAttribute_getValue(currentElement, "x2");
        char* y2 = svgAttribute_getValue(currentElement, "y2");

        /* If the starting and ending points are the same, it is a point */
        if (!strcmp(x1, x2) && !strcmp(y1, y2)) {
            embPattern_addPointObjectAbs(p, atof(x1), atof(y1));
        } else {
            embPattern_addLineObjectAbs(p, atof(x1), atof(y1), atof(x2), atof(y2));
        }
    } else if (!strcmp(buff, "linearGradient"))   {  }
    else if (!strcmp(buff, "listener"))         {  }
    else if (!strcmp(buff, "metadata"))         {  }
    else if (!strcmp(buff, "missing-glyph"))    {  }
    else if (!strcmp(buff, "mpath"))            {  }
    else if (!strcmp(buff, "path"))
    {
        /* TODO: finish */

        char* pointStr = svgAttribute_getValue(currentElement, "d");
        char* mystrok = svgAttribute_getValue(currentElement, "stroke");

        int last = strlen(pointStr);
        int size = 32;
        int i = 0;
        int pos = 0;
        /* An odometer aka 'tripometer' used for stepping thru the pathData */
        int trip = -1;
        /* count of float[] that has been filled.
         * 0 = first item of array
         * -1 = not filled = empty array
         */
        int reset = -1;
        EmbVector position, f_point, l_point, c1_point, c2_point;
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
        int cmd = 0;
        double pathData[7];
        unsigned int numMoves = 0;
        int pendingTask = 0;
        int relative = 0;

        EmbColor color;
        EmbArray* pointList = 0;
        EmbArray* flagList;
        EmbPathObject *path;

        char* pathbuff = 0;
        pathbuff = (char*)malloc(size);
        if (!pathbuff) {
            printf("ERROR: format-svg.c svgAddToPattern(), cannot allocate memory for pathbuff\n");
            return;
        }

        printf("stroke:%s\n", mystrok);

        /* M44.219,26.365c0,10.306-8.354,18.659-18.652,18.659c-10.299,0-18.663-8.354-18.663-18.659c0-10.305,8.354-18.659,18.659-18.659C35.867,7.707,44.219,16.06,44.219,26.365z */
        for (i = 0; i < last; i++) {
            char c = pointStr[i];
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

                    /* below "while" is for avoid loosing last 'z'
                     * command that maybe never accomodated.
                     */
                    pendingTask = 1; if (i==last-1) {pendingTask = 2;}

                    while (pendingTask > 0) {
                        pendingTask -= 1;

                    /* Check wether prior command need to be saved */
                    if (trip>=0) {
                        EmbPointObject test;
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
                        test.point = position;
                        embArray_addPoint(pointList, &test);
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
                    if (trip == -1 && reset == -1)
                    {
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
                            printf("ERROR: format-svg.c svgAddToPattern(), %s is not a valid svg path command, skipping...\n", pathbuff);
                            trip = -1;
                            reset = -1;
                        }
                    }
                    /* avoid loosing 'z' command that maybe never accomodated. */
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
                if (!pathbuff) { printf("ERROR: format-svg.c svgAddToPattern(), cannot re-allocate memory for pathbuff\n"); return; }
            }
        }
        free(pathbuff);

        /* TODO: subdivide numMoves > 1 */

        color = svgColorToEmbColor(svgAttribute_getValue(currentElement, "stroke"));
        
        path = (EmbPathObject *)malloc(sizeof(EmbPathObject));
        path->pointList = pointList;
        path->flagList = flagList;
        path->color = color;
        path->lineType = 1;
        embPattern_addPathObjectAbs(p, path);
    } else if (!strcmp(buff, "polygon") ||
            !strcmp(buff, "polyline")) {
        char* pointStr = svgAttribute_getValue(currentElement, "points");
        int last = strlen(pointStr);
        int size = 32;
        int i = 0;
        int pos = 0;
        unsigned char odd = 1;
        double xx = 0.0;
        double yy = 0.0;

        EmbArray* pointList = 0;

        char* polybuff = 0;
        polybuff = (char*)malloc(size);
        if (!polybuff) {
            printf("ERROR: format-svg.c svgAddToPattern(), cannot allocate memory for polybuff\n");
            return;
        }
        for (i = 0; i < last; i++) {
            char c = pointStr[i];
            switch (c) {
                case ' ':
                    if (pos == 0)
                        break;
                    polybuff[pos] = 0;
                    pos = 0;
                    /*Compose Point List */
                    if (odd)
                    {
                        odd = 0;
                        xx = atof(polybuff);
                    }
                    else
                    {
                        EmbPointObject a;
                        odd = 1;
                        yy = atof(polybuff);

                        if (!pointList) {
                            pointList = embArray_create(EMB_POINT);
                        }
                        a.point.x = xx;
                        a.point.y = yy;
                        embArray_addPoint(pointList, &a);
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
                if (!polybuff) { printf("ERROR: format-svg.c svgAddToPattern(), cannot re-allocate memory for polybuff\n"); return; }
            }
        }
        free(polybuff);

        if (!strcmp(buff, "polygon")) {
            EmbPolygonObject* polygonObj;
            polygonObj = (EmbPolygonObject*)malloc(sizeof(EmbPolygonObject));
            polygonObj->pointList = pointList;
            polygonObj->color = svgColorToEmbColor(svgAttribute_getValue(currentElement, "stroke"));
            polygonObj->lineType = 1; /* TODO: use lineType enum */
            embPattern_addPolygonObjectAbs(p, polygonObj);
        } else { /* polyline */
            EmbPolylineObject* polylineObj;
            polylineObj = (EmbPolylineObject*)malloc(sizeof(EmbPolylineObject));
            polylineObj->pointList = pointList;
            polylineObj->color = svgColorToEmbColor(svgAttribute_getValue(currentElement, "stroke"));
            polylineObj->lineType = 1; /* TODO: use lineType enum */
            embPattern_addPolylineObjectAbs(p, polylineObj);
        }
    }
    else if (!strcmp(buff, "prefetch")) {

    } else if (!strcmp(buff, "radialGradient")) {

    } else if (!strcmp(buff, "rect")) {
        embPattern_addRectObjectAbs(p, 
            atof(svgAttribute_getValue(currentElement, "x")),
            atof(svgAttribute_getValue(currentElement, "y")),
            atof(svgAttribute_getValue(currentElement, "width")),
            atof(svgAttribute_getValue(currentElement, "height")));
    } else if (!strcmp(buff, "script"))           {  

    } else if (!strcmp(buff, "set")) {  }
    else if (!strcmp(buff, "solidColor")) {  }
    else if (!strcmp(buff, "stop"))             {  }
    else if (!strcmp(buff, "svg"))              {  }
    else if (!strcmp(buff, "switch"))           {  }
    else if (!strcmp(buff, "tbreak"))           {  }
    else if (!strcmp(buff, "text"))             {  }
    else if (!strcmp(buff, "textArea"))         {  }
    else if (!strcmp(buff, "title"))            {  }
    else if (!strcmp(buff, "tspan"))            {  }
    else if (!strcmp(buff, "use"))              {  }
    else if (!strcmp(buff, "video"))            {  }

    svgElement_free(currentElement);
}

int svgIsElement(const char* buff) {
    if (stringInArray(buff, svg_element_tokens)) {
        return SVG_ELEMENT;
    }
    /* Attempt to identify the program that created the SVG file. This should be in a comment at that occurs before the svg element. */
    else if (!strcmp(buff, "Embroidermodder"))     { svgCreator = SVG_CREATOR_EMBROIDERMODDER; }
    else if (!strcmp(buff, "Illustrator"))         { svgCreator = SVG_CREATOR_ILLUSTRATOR; }
    else if (!strcmp(buff, "Inkscape"))            { svgCreator = SVG_CREATOR_INKSCAPE; }

    return SVG_NULL;
}

int svgIsMediaProperty(const char* buff) {
    if (stringInArray(buff, svg_media_property_tokens)) {
        return SVG_MEDIA_PROPERTY;
    }
    return SVG_NULL;
}

int svgIsProperty(const char* buff) {
    if (stringInArray(buff, svg_property_tokens)) {
        return SVG_PROPERTY;
    }
    return SVG_NULL;
}

int svgIsXmlAttribute(const char* buff) {
    const char *tokens[] = {"encoding", "standalone", "version", "/", "\0"};
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsXmlAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsLinkAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content",
        "datatype", "externalResourcesRequired", "focusHighlight",
        "focusable", "id", "nav-down", "nav-down-left",
        "nav-down-right", "nav-left", "nav-next", "nav-prev",
        "nav-right", "nav-up", "nav-up-left", "nav-up-right",
        "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats",
        "resource", "rev", "role", "systemLanguage", "target",
        "transform", "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title",
        "xlink:type", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsLinkAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsAnimateAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "accumulate", "additive", "attributeName", "attributeType",
        "begin", "by", "calcMode", "class", "content", "datatype", "dur", "end",
        "fill", "from", "id", "keySplines", "keyTimes", "max", "min", "property",
        "rel", "repeatCount", "repeatDur", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "restart", "rev", "role", "systemLanguage", "to", "typeof", "values",
        "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
        "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsAnimateAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsAnimateColorAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "accumulate", "additive", "attributeName", "attributeType",
        "begin", "by", "calcMode", "class", "content", "datatype", "dur",
        "end", "fill", "from", "id",
        "keySplines", "keyTimes", "max", "min", "property", "rel",
        "repeatCount", "repeatDur", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats",
        "resource", "restart", "rev", "role", "systemLanguage",
        "to", "typeof", "values", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title",
        "xlink:type", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsAnimateColorAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsAnimateMotionAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "accumulate", "additive", "begin", "by", "calcMode", "class",
        "content", "datatype", "dur", "end", "fill", "from", "id", "keyPoints",
        "keySplines", "keyTimes", "max", "min", "origin", "path", "property",
        "rel", "repeatCount", "repeatDur", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "restart", "rev", "role", "rotate", "systemLanguage", "to", "typeof",
        "values", "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
        "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsAnimateMotionAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsAnimateTransformAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "accumulate", "additive", "attributeName", "attributeType",
        "begin", "by", "calcMode", "class", "content", "datatype", "dur", "end",
        "fill", "from", "id", "keySplines", "keyTimes", "max", "min",
        "property", "rel", "repeatCount", "repeatDur", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "restart", "rev", "role", "systemLanguage", "to", "type", "typeof",
        "values", "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
        "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsAnimateTransformAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsAnimationAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "begin", "class", "content", "datatype", "dur", "end",
        "externalResourcesRequired", "fill", "focusHighlight", "focusable",
        "height", "id", "initialVisibility", "max", "min", "nav-down",
        "nav-down-left", "nav-down-right", "nav-left", "nav-next", "nav-prev",
        "nav-right", "nav-up", "nav-up-left", "nav-up-right",
        "preserveAspectRatio", "property", "rel", "repeatCount", "repeatDur",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "restart", "rev", "role", "syncBehavior",
        "syncMaster", "syncTolerance", "systemLanguage", "transform", "typeof",
        "width", "x", "xlink:actuate", "xlink:arcrole", "xlink:href",
        "xlink:role", "xlink:show", "xlink:title", "xlink:type", "xml:base",
        "xml:id", "xml:lang", "xml:space", "y", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsAnimationAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsAudioAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "begin", "class", "content", "datatype", "dur", "end",
        "externalResourcesRequired", "fill", "id", "max", "min", "property",
        "rel", "repeatCount", "repeatDur", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "restart", "rev", "role", "syncBehavior", "syncMaster", "syncTolerance",
        "systemLanguage", "type", "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsAudioAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsCircleAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "cx", "cy", "datatype", "focusHighlight",
        "focusable", "id", "nav-down", "nav-down-left", "nav-down-right",
        "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
        "nav-up-left", "nav-up-right", "property", "r", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "transform", "typeof", "xml:base", "xml:id", "xml:lang", "xml:space",
        "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsCircleAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsDefsAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "resource", "rev", "role", "typeof", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsDefsAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsDescAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    printf("format-svg.c svgIsDescAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsDiscardAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "begin", "class", "content", "datatype", "id", "property",
        "rel", "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
        "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    printf("format-svg.c svgIsDiscardAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsEllipseAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "cx", "cy", "datatype", "focusHighlight",
        "focusable", "id", "nav-down", "nav-down-left", "nav-down-right",
        "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
        "nav-up-left", "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "rx", "ry", "systemLanguage", "transform", "typeof",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsEllipseAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsFontAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "horiz-adv-x", "horiz-origin-x", "id", "property", "rel", "resource",
        "rev", "role", "typeof", "xml:base", "xml:id", "xml:lang", "xml:space",
        "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsFontAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsFontFaceAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "accent-height", "alphabetic", "ascent", "bbox", "cap-height",
        "class", "content", "datatype", "descent", "externalResourcesRequired",
        "font-family", "font-stretch", "font-style", "font-variant",
        "font-weight", "hanging", "id", "ideographic", "mathematical",
        "overline-position", "overline-thickness", "panose-1", "property",
        "rel", "resource", "rev", "role", "slope", "stemh", "stemv",
        "strikethrough-position", "strikethrough-thickness", "typeof",
        "underline-position", "underline-thickness", "unicode-range",
        "units-per-em", "widths", "x-height", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    printf("format-svg.c svgIsFontFaceAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsFontFaceSrcAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "resource", "rev", "role", "typeof", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsFontFaceSrcAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsFontFaceUriAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "id", "property", "rel", "resource", "rev", "role",
        "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title",
        "xlink:type", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsFontFaceUriAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsForeignObjectAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "focusHighlight", "focusable", "height", "id", "nav-down",
        "nav-down-left", "nav-down-right", "nav-left", "nav-next",
        "nav-prev", "nav-right", "nav-up", "nav-up-left", "nav-up-right",
        "property", "rel", "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "transform", "typeof", "width", "x", "xlink:actuate",
        "xlink:arcrole", "xlink:href", "xlink:role", "xlink:show",
        "xlink:title", "xlink:type", "xml:base", "xml:id",
        "xml:lang", "xml:space", "y", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsForeignObjectAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsGroupAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "focusHighlight", "focusable", "id", "nav-down", "nav-down-left",
        "nav-down-right", "nav-left", "nav-next", "nav-prev", "nav-right",
        "nav-up", "nav-up-left", "nav-up-right", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "transform", "typeof", "xml:base", "xml:id", "xml:lang", "xml:space",
        "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsGroupAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsGlyphAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "arabic-form", "class", "content", "d", "datatype",
        "glyph-name", "horiz-adv-x", "id", "lang", "property", "rel",
        "resource", "rev", "role", "typeof", "unicode", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsGlyphAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsHandlerAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "ev:event",
        "externalResourcesRequired", "id", "property", "rel", "resource",
        "rev", "role", "type", "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsHandlerAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsHKernAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "g1", "g2", "id", "k",
        "property", "rel", "resource", "rev", "role", "typeof", "u1", "u2",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsHKernAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsImageAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "focusHighlight", "focusable", "height", "id", "nav-down",
        "nav-down-left", "nav-down-right", "nav-left", "nav-next", "nav-prev",
        "nav-right", "nav-up", "nav-up-left", "nav-up-right", "opacity",
        "preserveAspectRatio", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "systemLanguage", "transform", "type", "typeof", "width",
        "x", "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
        "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
        "xml:lang", "xml:space", "y", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsImageAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsLineAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "id", "nav-down", "nav-down-left", "nav-down-right", "nav-left",
        "nav-next", "nav-prev", "nav-right", "nav-up", "nav-up-left",
        "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "systemLanguage", "transform", "typeof", "x1", "x2",
        "xml:base", "xml:id", "xml:lang", "xml:space", "y1", "y2", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsLineAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsLinearGradientAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "gradientUnits", "id",
        "property", "rel", "resource", "rev", "role", "typeof", "x1", "x2",
        "xml:base", "xml:id", "xml:lang", "xml:space", "y1", "y2", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsLinearGradientAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsListenerAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "defaultAction", "event",
        "handler", "id", "observer", "phase", "propagate", "property", "rel",
        "resource", "rev", "role", "target", "typeof", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsListenerAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsMetadataAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsMetadataAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsMissingGlyphAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "d", "datatype", "horiz-adv-x", "id",
        "property", "rel", "resource", "rev", "role", "typeof", "xml:base",
        "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsMissingGlyphAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsMPathAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "resource", "rev", "role", "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsMPathAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsPathAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "d", "datatype", "focusHighlight",
        "focusable", "id", "nav-down", "nav-down-left", "nav-down-right",
        "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
        "nav-up-left", "nav-up-right", "pathLength", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "transform", "typeof", "xml:base", "xml:id", "xml:lang", "xml:space",
        "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsPathAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsPolygonAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "id", "nav-down", "nav-down-left", "nav-down-right", "nav-left",
        "nav-next", "nav-prev", "nav-right", "nav-up", "nav-up-left",
        "nav-up-right", "points", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "systemLanguage", "transform", "typeof", "xml:base",
        "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsPolygonAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsPolylineAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "id", "nav-down", "nav-down-left", "nav-down-right", "nav-left",
        "nav-next", "nav-prev", "nav-right", "nav-up", "nav-up-left",
        "nav-up-right", "points", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "systemLanguage", "transform", "typeof", "xml:base",
        "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsPolylineAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsPrefetchAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "bandwidth", "class", "content", "datatype", "id",
        "mediaCharacterEncoding", "mediaContentEncodings", "mediaSize",
        "mediaTime", "property", "rel", "resource", "rev", "role", "typeof",
        "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
        "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsPrefetchAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsRadialGradientAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "cx", "cy", "datatype", "gradientUnits",
        "id", "property", "r", "rel", "resource", "rev", "role", "typeof",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsRadialGradientAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsRectAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "height", "id", "nav-down", "nav-down-left", "nav-down-right",
        "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
        "nav-up-left", "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "rx", "ry", "systemLanguage", "transform", "typeof",
        "width", "x", "xml:base", "xml:id", "xml:lang", "xml:space", "y",
        "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsRectAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsScriptAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "id", "property", "rel", "resource", "rev", "role", "type", "typeof",
        "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
        "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };   
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsScriptAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsSetAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "attributeName", "attributeType", "begin", "class", "content",
        "datatype", "dur", "end", "fill", "id", "max", "min", "property", "rel",
        "repeatCount", "repeatDur", "requiredExtensions", "requiredFeatures",
        "requiredFonts", "requiredFormats", "resource", "rev", "role",
        "systemLanguage", "to", "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsSetAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsSolidColorAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "resource", "rev", "role", "typeof", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsSolidColorAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsStopAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "offset", "property",
        "rel", "resource", "rev", "role", "typeof", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsStopAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsSvgAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "baseProfile", "class", "content", "contentScriptType",
        "datatype", "externalResourcesRequired", "focusHighlight", "focusable",
        "height", "id", "nav-down", "nav-down-left", "nav-down-right",
        "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
        "nav-up-left", "nav-up-right", "playbackOrder", "preserveAspectRatio",
        "property", "rel", "resource", "rev", "role", "snapshotTime",
        "syncBehaviorDefault", "syncToleranceDefault", "timelineBegin",
        "typeof", "version", "viewBox", "width", "xml:base", "xml:id",
        "xml:lang", "xml:space", "zoomAndPan", "/", "\0"
    };
    const char *inkscape_tokens[] = {
        "xmlns:dc", "xmlns:cc", "xmlns:rdf", "xmlns:svg", "xmlns", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    if (svgCreator == SVG_CREATOR_INKSCAPE) {
        if (stringInArray(buff, inkscape_tokens)) {
            return SVG_ATTRIBUTE;
        }
    }
    printf("format-svg.c svgIsSvgAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsSwitchAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "focusHighlight", "focusable", "id", "nav-down", "nav-down-left",
        "nav-down-right", "nav-left", "nav-next", "nav-prev", "nav-right",
        "nav-up", "nav-up-left", "nav-up-right", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "transform", "typeof", "xml:base", "xml:id", "xml:lang", "xml:space",
        "/", "\0"
    };    
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsSwitchAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsTBreakAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsTBreakAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsTextAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "editable", "focusHighlight",
        "focusable", "id", "nav-down", "nav-down-left", "nav-down-right",
        "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
        "nav-up-left", "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "rotate", "systemLanguage", "transform", "typeof", "x",
        "xml:base", "xml:id", "xml:lang", "xml:space", "y", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsTextAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsTextAreaAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "editable", "focusHighlight",
        "focusable", "height", "id", "nav-down", "nav-down-left",
        "nav-down-right", "nav-left", "nav-next", "nav-prev", "nav-right",
        "nav-up", "nav-up-left", "nav-up-right", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "transform", "typeof", "width", "x", "xml:base", "xml:id", "xml:lang",
        "xml:space", "y", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsTextAreaAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsTitleAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsTitleAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsTSpanAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "id", "nav-down", "nav-down-left", "nav-down-right", "nav-left",
        "nav-next", "nav-prev", "nav-right", "nav-up", "nav-up-left",
        "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "systemLanguage", "typeof", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsTSpanAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsUseAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "focusHighlight", "focusable", "id", "nav-down", "nav-down-left",
        "nav-down-right", "nav-left", "nav-next", "nav-prev", "nav-right",
        "nav-up", "nav-up-left", "nav-up-right", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "transform", "typeof", "x", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "y", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsUseAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}

int svgIsVideoAttribute(const char* buff) {
    const char *tokens[] = {
        "about", "begin", "class", "content", "datatype", "dur", "end",
        "externalResourcesRequired", "fill", "focusHighlight", "focusable",
        "height", "id", "initialVisibility", "max", "min", "nav-down",
        "nav-down-left", "nav-down-right", "nav-left", "nav-next", "nav-prev",
        "nav-right", "nav-up", "nav-up-left", "nav-up-right", "overlay",
        "preserveAspectRatio", "property", "rel", "repeatCount", "repeatDur",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "restart", "rev", "role", "syncBehavior",
        "syncMaster", "syncTolerance", "systemLanguage", "transform",
        "transformBehavior", "type", "typeof", "width", "x", "xlink:actuate",
        "xlink:arcrole", "xlink:href", "xlink:role", "xlink:show",
        "xlink:title", "xlink:type", "xml:base", "xml:id", "xml:lang",
        "xml:space", "y", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    printf("format-svg.c svgIsVideoAttribute(), unknown: %s\n", buff);
    return SVG_NULL;
}


int svgIsCatchAllAttribute(const char* buff) {
    const char *tokens[] = {
        /* Catch All Properties */
        "audio-level", "buffered-rendering", "color", "color-rendering",
        "direction", "display", "display-align", "fill",
        "fill-opacity", "fill-rule", "font-family", "font-size", "font-style",
        "font-variant", "font-weight", "image-rendering", "line-increment",
        "opacity", "pointer-events", "shape-rendering", "solid-color",
        "solid-opacity", "stop-color", "stop-opacity", "stroke",
        "stroke-dasharray", "stroke-linecap", "stroke-linejoin",
        "stroke-miterlimit", "stroke-opacity", "stroke-width",
        "text-align", "text-anchor", "text-rendering", "unicode-bidi",
        "vector-effect", "viewport-fill", "viewport-fill-opacity", "visibility",
        /* Catch All Attributes */
        "about", "accent-height", "accumulate", "additive",
        "alphabetic", "arabic-form", "ascent", "attributeName", "attributeType",
        "bandwidth", "baseProfile", "bbox", "begin", "by", "calcMode",
        "cap-height", "class", "content", "contentScriptType", "cx", "cy",
        "d", "datatype", "defaultAction", "descent", "dur", "editable",
        "end", "ev:event", "event", "externalResourcesRequired",
        "focusHighlight", "focusable", "font-family", "font-stretch",
        "font-style", "font-variant", "font-weight", "from", "g1", "g2",
        "glyph-name", "gradientUnits", "handler", "hanging", "height",
        "horiz-adv-x", "horiz-origin-x", "id", "ideographic",
        "initialVisibility", "k", "keyPoints", "keySplines", "keyTimes",
        "lang", "mathematical", "max", "mediaCharacterEncoding",
        "mediaContentEncodings", "mediaSize", "mediaTime", "min",
        "nav-down", "nav-down-left", "nav-down-right", "nav-left", "nav-next",
        "nav-prev", "nav-right", "nav-up", "nav-up-left", "nav-up-right",
        "observer", "offset", "origin", "overlay", "overline-position",
        "overline-thickness", "panose-1", "path", "pathLength", "phase",
        "playbackOrder", "points", "preserveAspectRatio", "propagate",
        "property", "r", "rel", "repeatCount", "repeatDur",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "restart", "rev", "role", "rotate",
        "rx", "ry", "slope", "snapshotTime", "stemh", "stemv",
        "strikethrough-position", "strikethrough-thickness", "syncBehavior",
        "syncBehaviorDefault", "syncMaster", "syncTolerance",
        "syncToleranceDefault", "systemLanguage", "target", "timelineBegin",
        "to", "transform", "transformBehavior", "type", "typeof", "u1", "u2",
        "underline-position", "underline-thickness", "unicode", "unicode-range",
        "units-per-em", "values", "version", "viewBox", "width", "widths",
        "x", "x-height", "x1", "x2", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "y", "y1", "y2",
        "zoomAndPan", "/", "\0"
    };
    if (stringInArray(buff, tokens)) {
        return SVG_CATCH_ALL;
    }
    return SVG_NULL;
}

void svgProcess(int c, const char* buff)
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
            currentElement = svgElement_create(buff);
        } else {
            return;
        }
    } else if (svgExpect == SVG_EXPECT_ATTRIBUTE) {
        char advance = 0;
        const char* name = 0;
        if (!currentElement) {
            /* TODO: error */
            return;
        }
        name = currentElement->name;
        if (!strcmp(name, "?xml")) {
            if (!advance) {
                advance = (char)svgIsXmlAttribute(buff);
            }
        } else if (!strcmp(name, "a")) {
            if (!advance) {
                advance = (char)svgIsProperty(buff);
            }
            if (!advance) {
                advance = (char)svgIsLinkAttribute(buff);
            }
        } else if (!strcmp(name, "animate")) {
            if (!advance) {
                advance = (char)svgIsAnimateAttribute(buff);
            }
        } else if (!strcmp(name, "animateColor")) {
            if (!advance) {
                advance = (char)svgIsAnimateColorAttribute(buff);
            }
        } else if (!strcmp(name, "animateMotion")) {
            if (!advance) {
                advance = (char)svgIsAnimateMotionAttribute(buff);
            }
        } else if (!strcmp(name, "animateTransform")) {
            if (!advance) {
                advance = (char)svgIsAnimateTransformAttribute(buff);
            }
        } else if (!strcmp(name, "animation")) {
            if (!advance) {
                advance = (char)svgIsMediaProperty(buff);
            }
            if (!advance) {
                advance = (char)svgIsAnimationAttribute(buff);
            }
        } else if (!strcmp(name, "audio")) {
            if (!advance) { advance = (char)svgIsMediaProperty(buff); }
            if (!advance) { advance = (char)svgIsAudioAttribute(buff); }
        } else if (!strcmp(name, "circle")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsCircleAttribute(buff); }
        } else if (!strcmp(name, "defs")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsDefsAttribute(buff); }
        } else if (!strcmp(name, "desc")) {
            if (!advance) { advance = (char)svgIsMediaProperty(buff); }
            if (!advance) { advance = (char)svgIsDescAttribute(buff); }
        }
        else if (!strcmp(name, "discard")) {
            if (!advance) { advance = (char)svgIsDiscardAttribute(buff); }
        } else if (!strcmp(name, "ellipse")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsEllipseAttribute(buff); }
        } else if (!strcmp(name, "font")) {
            if (!advance) { advance = (char)svgIsFontAttribute(buff); }
        } else if (!strcmp(name, "font-face")) {
            if (!advance) { advance = (char)svgIsFontFaceAttribute(buff); }
        } else if (!strcmp(name, "font-face-src")) {
            if (!advance) { advance = (char)svgIsFontFaceSrcAttribute(buff); }
        } else if (!strcmp(name, "font-face-uri")) {
            if (!advance) { advance = (char)svgIsFontFaceUriAttribute(buff); }
        } else if (!strcmp(name, "foreignObject")) {
            if (!advance) {
                advance = (char)svgIsProperty(buff); }
            if (!advance) {
                advance = (char)svgIsForeignObjectAttribute(buff); }
        } else if (!strcmp(name, "g")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsGroupAttribute(buff); }
        } else if (!strcmp(name, "glyph")) {
            if (!advance) { advance = (char)svgIsGlyphAttribute(buff); }
        } else if (!strcmp(name, "handler")) {
            if (!advance) { advance = (char)svgIsHandlerAttribute(buff); }
        } else if (!strcmp(name, "hkern")) {
            if (!advance) { advance = (char)svgIsHKernAttribute(buff); }
        } else if (!strcmp(name, "image")) {
            if (!advance) { advance = (char)svgIsMediaProperty(buff); }
            if (!advance) { advance = (char)svgIsImageAttribute(buff); }
        } else if (!strcmp(name, "line")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsLineAttribute(buff); }
        } else if (!strcmp(name, "linearGradient")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsLinearGradientAttribute(buff); }
        } else if (!strcmp(name, "listener")) {
            if (!advance) { advance = (char)svgIsListenerAttribute(buff); }
        } else if (!strcmp(name, "metadata")) {
            if (!advance) { advance = (char)svgIsMediaProperty(buff); }
            if (!advance) { advance = (char)svgIsMetadataAttribute(buff); }
        } else if (!strcmp(name, "missing-glyph")) {
            if (!advance) { advance = (char)svgIsMissingGlyphAttribute(buff); }
        } else if (!strcmp(name, "mpath")) {
            if (!advance) { advance = (char)svgIsMPathAttribute(buff); }
        } else if (!strcmp(name, "path")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsPathAttribute(buff); }
        } else if (!strcmp(name, "polygon")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsPolygonAttribute(buff); }
        } else if (!strcmp(name, "polyline")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsPolylineAttribute(buff); }
        } else if (!strcmp(name, "prefetch")) {
            if (!advance) { advance = (char)svgIsPrefetchAttribute(buff); }
        } else if (!strcmp(name, "radialGradient")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsRadialGradientAttribute(buff); }
        } else if (!strcmp(name, "rect")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsRectAttribute(buff); }
        } else if (!strcmp(name, "script")) {
            if (!advance) { advance = (char)svgIsScriptAttribute(buff); }
        } else if (!strcmp(name, "set")) {
            if (!advance) { advance = (char)svgIsSetAttribute(buff); }
        } else if (!strcmp(name, "solidColor")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsSolidColorAttribute(buff); }
        } else if (!strcmp(name, "stop")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsStopAttribute(buff); }
        } else if (!strcmp(name, "svg")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsSvgAttribute(buff); }
        } else if (!strcmp(name, "switch")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsSwitchAttribute(buff); }
        } else if (!strcmp(name, "tbreak")) {
            if (!advance) { advance = (char)svgIsTBreakAttribute(buff); }
        } else if (!strcmp(name, "text")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsTextAttribute(buff); }
        } else if (!strcmp(name, "textArea")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsTextAreaAttribute(buff); }
        } else if (!strcmp(name, "title")) {
            if (!advance) { advance = (char)svgIsMediaProperty(buff); }
            if (!advance) { advance = (char)svgIsTitleAttribute(buff); }
        } else if (!strcmp(name, "tspan")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsTSpanAttribute(buff); }
        } else if (!strcmp(name, "use")) {
            if (!advance) { advance = (char)svgIsProperty(buff); }
            if (!advance) { advance = (char)svgIsUseAttribute(buff); }
        } else if (!strcmp(name, "video")) {
            if (!advance) { advance = (char)svgIsMediaProperty(buff); }
            if (!advance) { advance = (char)svgIsVideoAttribute(buff); }
        }
        if (advance) {
            printf("ATTRIBUTE:\n");
            svgExpect = SVG_EXPECT_VALUE;
            free(currentAttribute);
            currentAttribute = 0;
            currentAttribute = emb_strdup(buff);
        }
    } else if (svgExpect == SVG_EXPECT_VALUE) {
        int last = strlen(buff) - 1;
        printf("VALUE:\n");

        /* single-value */
        if ((buff[0] == '"' || buff[0] == '\'') && (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') && !svgMultiValue) {
            svgExpect = SVG_EXPECT_ATTRIBUTE;
            svgElement_addAttribute(currentElement, svgAttribute_create(currentAttribute, buff));
        } else { /* multi-value */
            svgMultiValue = 1;
            if (!currentValue) {
                currentValue = emb_strdup(buff);
                if (!currentValue) { /*TODO: error */ return; }
            } else {
                char* tmp = 0;
                tmp = emb_strdup(currentValue);
                free(currentValue);
                currentValue = 0;
                currentValue = (char*)malloc(strlen(buff) + strlen(tmp) + 2);
                if (!currentValue) { printf("ERROR: format-svg.c svgProcess(), cannot allocate memory for currentValue\n"); return; }
                if (currentValue) memset(currentValue, 0, strlen(buff) + strlen(tmp) + 2);
                strcat(currentValue, tmp);
                strcat(currentValue, " ");
                strcat(currentValue, buff);
                free(tmp);
            }
            if (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') {
                svgMultiValue = 0;
                svgExpect = SVG_EXPECT_ATTRIBUTE;
                svgElement_addAttribute(currentElement, svgAttribute_create(currentAttribute, currentValue));
                free(currentValue);
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

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readSvg(EmbPattern* pattern, const char* fileName) {
    FILE* file = 0;
    int size = 1024;
    int pos, c, i;
    char* buff = 0;

    if (!pattern) {
        printf("ERROR: format-svg.c readSvg(), pattern argument is null\n");
        return 0;
    }
    if (!fileName) {
        printf("ERROR: format-svg.c readSvg(), fileName argument is null\n");
        return 0;
    }
    buff = (char*)malloc(size);
    if (!buff) {
        printf("ERROR: format-svg.c readSvg(), cannot allocate memory for buff\n");
        return 0;
    }
    svgCreator = SVG_CREATOR_NULL;
    svgExpect = SVG_EXPECT_NULL;
    svgMultiValue = 0;

    currentElement = 0;
    currentAttribute = 0;
    currentValue = 0;
    
    if (EMB_DEBUG) {
        puts("OVERRIDDEN: readSvg is disabled during testing");
        return 1;
    }

    /* Pre-flip incase of multiple reads on the same pattern */
    embPattern_flipVertical(pattern);

    file = fopen(fileName, "r");
    if (file) {
        pos = 0;
        do {
            c = fgetc(file);
            switch (c) {
                case '<':
                    if (svgExpect == SVG_EXPECT_NULL) {
                        svgAddToPattern(pattern);
                        svgExpect = SVG_EXPECT_ELEMENT;
                    }
                case '>':
                    if (pos == 0) /* abnormal case that may occur in svg element where '>' is all by itself */
                    {
                        /*TODO: log a warning about this absurdity! */
                        svgExpect = SVG_EXPECT_ELEMENT;
                        break;
                    }
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
                    printf("ERROR: format-svg.c readSvg(), cannot re-allocate memory for buff\n");
                    return 0;
                }
            }
        }
        while(c != EOF);
        fclose(file);
    }
    free(buff);
    free(currentAttribute);
    free(currentValue);

    /*TODO: remove this summary after testing is complete */
    printf("OBJECT SUMMARY:\n");
    if (pattern->circles) {
        for (i = 0; i < pattern->circles->count; i++) {
            EmbCircle c = pattern->circles->circle[i].circle;
            printf("circle %f %f %f\n", c.centerX, c.centerY, c.radius);
        }
    }
    if (pattern->ellipses) {
        for (i = 0; i < pattern->ellipses->count; i++) {
            EmbEllipse e = pattern->ellipses->ellipse[i].ellipse;
            printf("ellipse %f %f %f %f\n", e.centerX, e.centerY, e.radiusX, e.radiusY);
        }
    }
    if (pattern->lines) {
        for (i = 0; i < pattern->lines->count; i++) {
            EmbLine li = pattern->lines->line[i].line;
            printf("line %f %f %f %f\n", li.x1, li.y1, li.x2, li.y2);
        }
    }
    if (pattern->points) {
        for (i = 0; i < pattern->points->count; i++) {
            EmbPoint po = pattern->points->point[i].point;
            printf("point %f %f\n", po.x, po.y);
        }
    }
    if (pattern->polygons) {
        for (i = 0; i < pattern->polylines->count; i++) {
            int vertices = pattern->polygons->polygon[i]->pointList->count;
            printf("polygon %d\n", vertices);
        }
    }
    if (pattern->polylines) {
        for (i = 0; i < pattern->polylines->count; i++) {
            int vertices = pattern->polylines->polyline[i]->pointList->count;
            printf("polyline %d\n", vertices);
        }
    }
    if (pattern->rects) {
        for (i = 0; i < pattern->rects->count; i++) {
            EmbRect r = pattern->rects->rect[i].rect;
            printf("rect %f %f %f %f\n", embRect_x(r), embRect_y(r), embRect_width(r), embRect_height(r));
        }
    }

    /* Flip the pattern since SVG Y+ is down and libembroidery Y+ is up. */
    embPattern_flipVertical(pattern);

    return 1; /*TODO: finish readSvg */
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeSvg(EmbPattern* pattern, const char* fileName) {
    FILE* file = 0;
    EmbRect boundingRect;
    EmbPoint point;
    EmbRect rect;
    EmbColor color;
    int i, j;
    char isNormal, tmpX[32], tmpY[32];

    if (!validateWritePattern(pattern, fileName, "writeSvg")) {
        return 0;
    }

    file = fopen(fileName, "w");
    if (!file) {
        puts("ERROR: failed to open file.");
        return 0;
    }
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
    fprintf(file, "viewBox=\"%f %f %f %f\" ",
            boundingRect.left,
            boundingRect.top,
            embRect_width(boundingRect),
            embRect_height(boundingRect)); */

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

    /* write circles */
    if (pattern->circles) {
        for (i = 0; i < pattern->circles->count; i++) {
            EmbCircle circle = pattern->circles->circle[i].circle;
            EmbColor color = pattern->circles->circle[i].color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file, "\n<circle stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" cx=\"%f\" cy=\"%f\" r=\"%f\" />",
                        color.r,
                        color.g,
                        color.b,
                        circle.centerX,
                        circle.centerY,
                        circle.radius);
        }
    }

    /* write ellipses */
    if (pattern->ellipses) {
        for (i = 0; i < pattern->ellipses->count; i++) {
            EmbEllipse ellipse = pattern->ellipses->ellipse[i].ellipse;
            color = pattern->ellipses->ellipse[i].color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file, "\n<ellipse stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" />",
                        color.r,
                        color.g,
                        color.b,
                        ellipse.centerX,
                        ellipse.centerY,
                        ellipse.radiusX,
                        ellipse.radiusY);
        }
    }

    /* write lines */
    if (pattern->lines) {
        for (i = 0; i < pattern->lines->count; i++) {
            EmbLine line = pattern->lines->line[i].line;
            color = pattern->lines->line[i].color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file,
                "\n<line stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />",
                color.r, color.g, color.b,
                line.x1, line.y1, line.x2, line.y2);
        }
    }

    /* write points */
    if (pattern->points) {
        for (i = 0; i < pattern->points->count; i++) {
            point = pattern->points->point[i].point;
            color = pattern->points->point[i].color;
            /* See SVG Tiny 1.2 Spec:
             * Section 9.5 The 'line' element
             * Section C.6 'path' element implementation notes */
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            fprintf(file,
                "\n<line stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />",
                color.r, color.g, color.b,
                point.x, point.y, point.x, point.y);
        }
    }

    /* write polygons */
    if (pattern->polygons) {
        for (i = 0; i < pattern->polygons->count; i++) {
            EmbArray *pointList = pattern->polygons->polygon[i]->pointList;
            color = pattern->polygons->polygon[i]->color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
                fprintf(file, "\n<polygon stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"%s,%s",
                    color.r, color.g, color.b,
                    emb_optOut(pointList->point[0].point.x, tmpX),
                    emb_optOut(pointList->point[0].point.y, tmpY));
            for (j=1; j < pointList->count; j++) {
                fprintf(file, " %s,%s",
                    emb_optOut(pointList->point[j].point.x, tmpX),
                    emb_optOut(pointList->point[j].point.y, tmpY));
            }
            fprintf(file, "\"/>");
        }
    }

    /* write polylines */
    if (pattern->polylines) {
        for (i = 0; i < pattern->polylines->count; i++) {
            EmbArray *pointList = pattern->polylines->polyline[i]->pointList;
            color = pattern->polylines->polyline[i]->color;
            /* TODO: use proper thread width for stoke-width rather
             * than just 0.2.
             */
            fprintf(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"%s,%s",
                    color.r,
                    color.g,
                    color.b,
                    emb_optOut(pointList->point[0].point.x, tmpX),
                    emb_optOut(pointList->point[0].point.y, tmpY));
            for (j=1; j < pointList->count; j++) {
                fprintf(file, " %s,%s",
                    emb_optOut(pointList->point[j].point.x, tmpX),
                    emb_optOut(pointList->point[j].point.y, tmpY));
            }
            fprintf(file, "\"/>");
        }
    }

    /* write rects */
    if (pattern->rects) {
        for (i = 0; i < pattern->rects->count; i++) {
            rect = pattern->rects->rect[i].rect;
            color = pattern->rects->rect[i].color;
            /* TODO: use proper thread width for stoke-width rather
             * than just 0.2.
             */
            fprintf(file, "\n<rect stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" />",
                color.r, color.g, color.b,
                embRect_x(rect), embRect_y(rect), embRect_width(rect), embRect_height(rect));
        }
    }

    isNormal = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st = pattern->stitchList->stitch[i];
        /* TODO:
         * #ifdef SVG_DEBUG for Josh which outputs
         * JUMPS/TRIMS instead of chopping them out.
         */
        if (st.flags == NORMAL && !isNormal) {
            isNormal = 1;
            color = pattern->threads->thread[st.color].color;
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
    fclose(file);

    /* Reset the pattern so future writes(regardless of format)
     * are not flipped.
     */
    embPattern_flipVertical(pattern);

    return 1;
}

