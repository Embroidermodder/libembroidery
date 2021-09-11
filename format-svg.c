#include "embroidery.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* path flag codes */
#define LINETO             0
#define MOVETO             1
#define BULGETOCONTROL     2
#define BULGETOEND         4
#define ELLIPSETORAD       8
#define ELLIPSETOEND      16
#define CUBICTOCONTROL1   32
#define CUBICTOCONTROL2   64
#define CUBICTOEND       128
#define QUADTOCONTROL    256
#define QUADTOEND        512

/**
 * EMBEDDED SYSTEMS OPTIMIZATION
 *
 * All tokens as unsigned char, that way we can store the subsets of strings
 * in the smaller unsigned char array form.
 */
#define TOKEN_AUDIO_LEVEL              0
#define TOKEN_BUFFERED_AUDIO_RENDERING 1
#define TOKEN_COLOR                    2
#define TOKEN_COLOR_RENDERING          3
#define TOKEN_DIRECTION                4
#define TOKEN_DISPLAY                  5
#define TOKEN_DISPLAY_ALIGN            6
#define TOKEN_FILL                     7
#define TOKEN_FILL_OPACITY             8
#define TOKEN_FILL_RULE                9
#define TOKEN_FONT_FAMILY              11
#define TOKEN_FONT_SIZE                12
#define TOKEN_FONT_STYLE               13
#define TOKEN_FONT_VARIANT             14
#define TOKEN_FONT_WEIGHT              15
#define TOKEN_IMAGE_RENDERING          16
#define TOKEN_LINE_INCREMENT           17
#define TOKEN_OPACITY                  18
#define TOKEN_POINTER_EVENTS           19
#define TOKEN_SHAPE_RENDERING          20
#define TOKEN_SOLID_COLOR              21
#define TOKEN_ZOOM_AND_PAN             21

#define SVG_CREATOR_NULL               0
#define SVG_CREATOR_EMBROIDERMODDER    1
#define SVG_CREATOR_ILLUSTRATOR        2
#define SVG_CREATOR_INKSCAPE           3

#define SVG_EXPECT_NULL                0
#define SVG_EXPECT_ELEMENT             1
#define SVG_EXPECT_ATTRIBUTE           2
#define SVG_EXPECT_VALUE               3

/* SVG_TYPES */
#define SVG_NULL                       0
#define SVG_ELEMENT                    1
#define SVG_PROPERTY                   2
#define SVG_MEDIA_PROPERTY             3
#define SVG_ATTRIBUTE                  4
#define SVG_CATCH_ALL                  5

static void writeDouble(EmbFile *file, double num);
static void writeColor(EmbFile *file, EmbColor color);
static void writeCircles(EmbPattern *pattern, EmbFile *file);
static void writeEllipse(EmbPattern *pattern, EmbFile *file);
static void writePoints(EmbPattern *pattern, EmbFile *file);
static void writePolygons(EmbPattern *pattern, EmbFile *file);
static void writePolylines(EmbPattern *pattern, EmbFile *file);
static void writeStitchList(EmbPattern *pattern, EmbFile *file);

static const char *svg_all_tokens[] = {
    /* Catch All Properties */
    "audio-level", "buffered-rendering", "color", "color-rendering",  "direction",
    "display", "display-align", "fill", "fill-opacity", "fill-rule",
    "font-family", "font-size", "font-style", "font-variant", "font-weight",
    "image-rendering", "line-increment", "opacity", "pointer-events", "shape-rendering",
    "solid-color", "solid-opacity", "stop-color", "stop-opacity", "stroke",
    "stroke-dasharray", "stroke-linecap", "stroke-linejoin",
    "stroke-miterlimit", "stroke-opacity", "stroke-width",
    "text-align", "text-anchor", "text-rendering", "unicode-bidi",
    "vector-effect", "viewport-fill", "viewport-fill-opacity", "visibility",
    /* Catch All Attributes */
    "about", "accent-height", "accumulate", "additive", "alphabetic",
    "arabic-form", "ascent", "attributeName", "attributeType", "bandwidth",
    "baseProfile", "bbox", "begin", "by", "calcMode",
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

typedef struct SvgAttribute_
{
    char* name;
    char* value;
} SvgAttribute;

typedef struct SvgAttributeList_
{
    SvgAttribute attribute;
    struct SvgAttributeList_* next;
} SvgAttributeList;

typedef struct SvgElement_
{
    char* name;
    SvgAttributeList* attributeList;
    SvgAttributeList* lastAttribute;
} SvgElement;

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
     * TODO: not implemented SVG Full 1.1 Spec Elements
     */
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

    /* SVGTiny1.2 Spec Section 11.13.1 syntax for color values */
    if(length == 7 && colorStr[0] == '#') /* Six digit hex — #rrggbb */
    {
        c = embColor_fromHexStr(lTrim(colorStr, '#'));
    }
    else if(length == 4 && colorStr[0] == '#') /* Three digit hex — #rgb */
    {
        /* Convert the 3 digit hex to a six digit hex */
        char hex[7];
        sprintf(hex, "%c%c%c%c%c%c", colorStr[1], colorStr[1], colorStr[2],
            colorStr[2], colorStr[3], colorStr[3]);

        c = embColor_fromHexStr(hex);
    }
    else if(strstr(colorStr, "%")) /* Float functional — rgb(R%, G%, B%) */
    {
        charReplace(colorStr, "rgb,()%", "      ");
        c.r = (unsigned char)round(255.0/100.0 * strtod(colorStr, &pEnd));
        c.g = (unsigned char)round(255.0/100.0 * strtod(pEnd,     &pEnd));
        c.b = (unsigned char)round(255.0/100.0 * strtod(pEnd,     &pEnd));
    }
    else if(length > 3 && startsWith("rgb", colorStr)) /* Integer functional — rgb(rrr, ggg, bbb) */
    {
        charReplace(colorStr, "rgb,()", "     ");
        c.r = (unsigned char)strtol(colorStr, &pEnd, 10);
        c.g = (unsigned char)strtol(pEnd,     &pEnd, 10);
        c.b = (unsigned char)strtol(pEnd,     &pEnd, 10);
    }
    else /* Color keyword */
    {
        int tableColor = threadColor(colorStr, SVG_Colors);
        if (tableColor < 0) {
            printf("SVG color string not found: %s.\n", colorStr);
        }
        else {
            c.r = (tableColor/256)%16;
            c.g = (tableColor/16)%16;
            c.b = tableColor%16;
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
    else if(toUpper(cmd) == 'L') return LINETO;
    else if(toUpper(cmd) == 'C') return CUBICTOCONTROL1;
    else if(toUpper(cmd) == 'CC') return CUBICTOCONTROL2;
    else if(toUpper(cmd) == 'CCC') return CUBICTOEND;
    else if(toUpper(cmd) == 'A') return ELLIPSETORAD;
    else if(toUpper(cmd) == 'AA') return ELLIPSETOEND;
    else if(toUpper(cmd) == 'Q') return QUADTOCONTROL;
    else if(toUpper(cmd) == 'QQ') return QUADTOEND;
    else if(toUpper(cmd) == 'Z') return LINETO;
    */

    /*else if(toUpper(cmd) == 'B') return BULGETOCONTROL; */ /* NOTE: This is not part of the SVG spec, but hopefully Bulges will be added to the SVG spec someday */
    /*else if(toUpper(cmd) == 'BB') return BULGETOEND; */   /* NOTE: This is not part of the SVG spec, but hopefully Bulges will be added to the SVG spec someday */
    /*else { embLog("ERROR: format-svg.c svgPathCmdToEmbPathFlag(), unknown command '%c'\n", cmd); return MOVETO; } */

    return LINETO;
}

SvgAttribute svgAttribute_create(const char* name, const char* value)
{
    SvgAttribute attribute;
    char* modValue = 0;

    modValue = emb_strdup((char *)value);
    charReplace(modValue, "\"'/,", "    ");
    attribute.name = emb_strdup((char *)name);
    attribute.value = modValue;
    return attribute;
}

void svgElement_addAttribute(SvgElement* element, SvgAttribute data)
{
    if (!element) {
        embLog("ERROR: format-svg.c svgElement_addAttribute(), element argument is null.");
        return;
    }

    if(!(element->attributeList))
    {
        element->attributeList = (SvgAttributeList*)malloc(sizeof(SvgAttributeList));
        if(!(element->attributeList)) { embLog("ERROR: format-svg.c svgElement_addAttribute(), cannot allocate memory for element->attributeList."); return; }
        element->attributeList->attribute = data;
        element->attributeList->next = 0;
        element->lastAttribute = element->attributeList;
        element->lastAttribute->next = 0;
    }
    else
    {
        SvgAttributeList* pointerLast = element->lastAttribute;
        SvgAttributeList* list = (SvgAttributeList*)malloc(sizeof(SvgAttributeList));
        if(!list) { embLog("ERROR: format-svg.c svgElement_addAttribute(), cannot allocate memory for list."); return; }
        list->attribute = data;
        list->next = 0;
        pointerLast->next = list;
        element->lastAttribute = list;
    }
}

void svgElement_free(SvgElement* element)
{
    SvgAttributeList* list = 0;
    SvgAttributeList* nextList = 0;
    if(!element) return;

    list = element->attributeList;

    while(list)
    {
        free(list->attribute.name);
        list->attribute.name = 0;
        free(list->attribute.value);
        list->attribute.value = 0;
        nextList = list->next;
        free(list);
        list = nextList;
    }

    element->lastAttribute = 0;
    free(element->name);
    free(element);
}

SvgElement* svgElement_create(const char* name)
{
    SvgElement* element = 0;

    element = (SvgElement*)malloc(sizeof(SvgElement));
    if(!element) { embLog("ERROR: format-svg.c svgElement_create(), cannot allocate memory for element\n"); return 0; }
    element->name = emb_strdup((char *)name);
    if(!element->name) { embLog("ERROR: format-svg.c svgElement_create(), element->name is null\n"); return 0; }
    element->attributeList = 0;
    element->lastAttribute = 0;
    return element;
}

char* svgAttribute_getValue(SvgElement* element, const char* name)
{
    SvgAttributeList* pointer = 0;

    if(!element) { embLog("ERROR: format-svg.c svgAttribute_getValue(), element argument is null\n"); return "none"; }
    if(!name) { embLog("ERROR: format-svg.c svgAttribute_getValue(), name argument is null\n"); return "none"; }
    if(!element->attributeList) { /* TODO: error */ return "none"; }

    pointer = element->attributeList;
    while(pointer)
    {
        if(!strcmp(pointer->attribute.name, name)) { return pointer->attribute.value; }
        pointer = pointer->next;
    }

    return "none";
}

void svgAddToPattern(EmbPattern* p)
{
    const char* buff = 0;
    EmbPointObject test;
    EmbColor color;
    EmbPathObject *path;

    if(!p) { embLog("ERROR: format-svg.c svgAddToPattern(), p argument is null\n"); return; }
    if(!currentElement) { return; }

    buff = currentElement->name;
    if(!buff) { return; }

    if     (!strcmp(buff, "?xml"))             {  }
    else if(!strcmp(buff, "a"))                {  }
    else if(!strcmp(buff, "animate"))          {  }
    else if(!strcmp(buff, "animateColor"))     {  }
    else if(!strcmp(buff, "animateMotion"))    {  }
    else if(!strcmp(buff, "animateTransform")) {  }
    else if(!strcmp(buff, "animation"))        {  }
    else if(!strcmp(buff, "audio"))            {  }
    else if(!strcmp(buff, "circle"))
    {
        embPattern_addCircleObjectAbs(p, atof(svgAttribute_getValue(currentElement, "cx")),
                                         atof(svgAttribute_getValue(currentElement, "cy")),
                                         atof(svgAttribute_getValue(currentElement, "r")));
    }
    else if(!strcmp(buff, "defs"))             {  }
    else if(!strcmp(buff, "desc"))             {  }
    else if(!strcmp(buff, "discard"))          {  }
    else if(!strcmp(buff, "ellipse"))
    {
        embPattern_addEllipseObjectAbs(p, atof(svgAttribute_getValue(currentElement, "cx")),
                                          atof(svgAttribute_getValue(currentElement, "cy")),
                                          atof(svgAttribute_getValue(currentElement, "rx")),
                                          atof(svgAttribute_getValue(currentElement, "ry")));
    }
    else if(!strcmp(buff, "font"))             {  }
    else if(!strcmp(buff, "font-face"))        {  }
    else if(!strcmp(buff, "font-face-src"))    {  }
    else if(!strcmp(buff, "font-face-uri"))    {  }
    else if(!strcmp(buff, "foreignObject"))    {  }
    else if(!strcmp(buff, "g"))                {  }
    else if(!strcmp(buff, "glyph"))            {  }
    else if(!strcmp(buff, "handler"))          {  }
    else if(!strcmp(buff, "hkern"))            {  }
    else if(!strcmp(buff, "image"))            {  }
    else if(!strcmp(buff, "line"))
    {
        char* x1 = svgAttribute_getValue(currentElement, "x1");
        char* y1 = svgAttribute_getValue(currentElement, "y1");
        char* x2 = svgAttribute_getValue(currentElement, "x2");
        char* y2 = svgAttribute_getValue(currentElement, "y2");

        /* If the starting and ending points are the same, it is a point */
        if(!strcmp(x1, x2) && !strcmp(y1, y2))
            embPattern_addPointObjectAbs(p, atof(x1), atof(y1));
        else
            embPattern_addLineObjectAbs(p, atof(x1), atof(y1), atof(x2), atof(y2));
    }
    else if(!strcmp(buff, "linearGradient"))   {  }
    else if(!strcmp(buff, "listener"))         {  }
    else if(!strcmp(buff, "metadata"))         {  }
    else if(!strcmp(buff, "missing-glyph"))    {  }
    else if(!strcmp(buff, "mpath"))            {  }
    else if(!strcmp(buff, "path"))
    {
        /* TODO: finish */

        char* pointStr = svgAttribute_getValue(currentElement, "d");
        char* mystrok = svgAttribute_getValue(currentElement, "stroke");

        int last = strlen(pointStr);
        int size = 32;
        int i = 0;
        int j = 0;
        int pos = 0;
        /* An odometer aka 'tripometer' used for stepping thru the pathData */
        int trip = -1; /* count of float[] that has been filled. 0=first item of array, -1=not filled = empty array */
        int reset = -1;
        double xx = 0.0;
        double yy = 0.0;
        double fx = 0.0;
        double fy = 0.0;
        double lx = 0.0;
        double ly = 0.0;
        double cx1 = 0.0, cx2 = 0.0;
        double cy1 = 0.0, cy2 = 0.0;
        int cmd = 0;
        double pathData[7];
        unsigned int numMoves = 0;
        int pendingTask = 0;
        int relative = 0;

        EmbArray* pointList = 0;
        EmbArray* flagList;

        char* pathbuff = 0;
        pathbuff = (char*)malloc(size);
        if(!pathbuff) { embLog("ERROR: format-svg.c svgAddToPattern(), cannot allocate memory for pathbuff\n"); return; }

        printf("stroke:%s\n", mystrok);

        /* M44.219,26.365c0,10.306-8.354,18.659-18.652,18.659c-10.299,0-18.663-8.354-18.663-18.659c0-10.305,8.354-18.659,18.659-18.659C35.867,7.707,44.219,16.06,44.219,26.365z */
        for(i = 0; i < last; i++)
        {
            char c = pointStr[i];
            switch(c)
            {
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
                    if(pos > 0) {         /* append float to array, if it not yet stored */
                        pathbuff[pos] = 0;
                        pos = 0;
                        printf("    ,val:%s\n", pathbuff);
                        pathData[++trip] = atof(pathbuff);
                    }
                    break;

                case '-':

                    if(pos > 0) {         /* append float to array, if it not yet stored */
                        pathbuff[pos] = 0;
                        pos = 0;
                        printf("    -val:%s\n", pathbuff);
                        pathData[++trip] = atof(pathbuff);
                    }
                    pathbuff[pos++] = (char)c;                  /* add a more char */
                    break;

                default:
                    /*** ASSUMED ANY COMMAND FOUND ***/


                    if(pos > 0) {         /* just make sure: append float to array, if it not yet stored */
                        pathbuff[pos] = 0;
                        pos = 0;
                        printf("    >val:%s\n", pathbuff);
                        pathData[++trip] = atof(pathbuff);
                    }

                    /**** Compose Point List ****/

                    /* below "while" is for avoid loosing last 'z' command that maybe never accomodated. */
                    pendingTask = 1; if (i==last-1) {pendingTask = 2;}

                    while (pendingTask > 0)
                    {
                        pendingTask -= 1;

                    /* Check wether prior command need to be saved */
                    if(trip>=0)
                    {
                            trip = -1;
                            reset = -1;

                            relative = 0; /* relative to prior coordinate point or absolute coordinate? */

                            if     (cmd == 'M') { xx = pathData[0]; yy = pathData[1]; fx = xx; fy = yy; }
                            else if(cmd == 'm') { xx = pathData[0]; yy = pathData[1]; fx = xx; fy = yy; relative=1; }
                            else if(cmd == 'L') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 'l') { xx = pathData[0]; yy = pathData[1]; relative=1;}
                            else if(cmd == 'H') { xx = pathData[0]; yy = ly; }
                            else if(cmd == 'h') { xx = pathData[0]; yy = ly; relative=1;}
                            else if(cmd == 'V') { xx = lx;          yy = pathData[1]; }
                            else if(cmd == 'v') { xx = lx;          yy = pathData[1]; relative=1;}
                            else if(cmd == 'C') { xx = pathData[4]; yy = pathData[5]; cx1 = pathData[0]; cy1 = pathData[1]; cx2 = pathData[2]; cy2 = pathData[3]; }
                            else if(cmd == 'c') { xx = pathData[4]; yy = pathData[5]; cx1 = pathData[0]; cy1 = pathData[1]; cx2 = pathData[2]; cy2 = pathData[3]; relative=1;}
                            /*
                            else if(cmd == 'S') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 's') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 'Q') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 'q') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 'T') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 't') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 'A') { xx = pathData[0]; yy = pathData[1]; }
                            else if(cmd == 'a') { xx = pathData[0]; yy = pathData[1]; }
                            */
                            else if(cmd == 'Z') { xx = fx;          yy = fy; }
                            else if(cmd == 'z') { xx = fx;          yy = fy; }

                            if (!pointList && !flagList) {
                                pointList = embArray_create(EMB_POINT);
                                flagList = embArray_create(EMB_FLAG);
                            }
                            test.point.x = xx;
                            test.point.y = yy;
                            embArray_addPoint(pointList, &test);
                            embArray_addFlag(flagList, svgPathCmdToEmbPathFlag(cmd));
                            lx = xx; ly = yy;

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
                    if(trip == -1 && reset == -1)
                    {
                        pathbuff[0] = (char)c;                  /* set the command for compare */
                        pathbuff[1] = 0;

                        printf("cmd:%s\n", pathbuff);
                        if     (!strcmp(pathbuff, "M")) { cmd = 'M'; reset = 2; numMoves++; }
                        else if(!strcmp(pathbuff, "m")) { cmd = 'm'; reset = 2; numMoves++; }
                        else if(!strcmp(pathbuff, "L")) { cmd = 'L'; reset = 2; }
                        else if(!strcmp(pathbuff, "l")) { cmd = 'l'; reset = 2; }
                        else if(!strcmp(pathbuff, "C")) { cmd = 'C'; reset = 6; }
                        else if(!strcmp(pathbuff, "c")) { cmd = 'c'; reset = 6; }
                        else if(!strcmp(pathbuff, "H")) { cmd = 'H'; reset = 1; }
                        else if(!strcmp(pathbuff, "h")) { cmd = 'h'; reset = 1; }
                        else if(!strcmp(pathbuff, "V")) { cmd = 'V'; reset = 1; }
                        else if(!strcmp(pathbuff, "v")) { cmd = 'v'; reset = 1; }
                        else if(!strcmp(pathbuff, "S")) { cmd = 'S'; reset = 4; }
                        else if(!strcmp(pathbuff, "s")) { cmd = 's'; reset = 4; }
                        else if(!strcmp(pathbuff, "Q")) { cmd = 'Q'; reset = 4; }
                        else if(!strcmp(pathbuff, "q")) { cmd = 'q'; reset = 4; }
                        else if(!strcmp(pathbuff, "T")) { cmd = 'T'; reset = 2; }
                        else if(!strcmp(pathbuff, "t")) { cmd = 't'; reset = 2; }
                        else if(!strcmp(pathbuff, "A")) { cmd = 'A'; reset = 7; }
                        else if(!strcmp(pathbuff, "a")) { cmd = 'a'; reset = 7; }
                        else if(!strcmp(pathbuff, "Z")) { cmd = 'Z'; reset = 0; }
                        else if(!strcmp(pathbuff, "z")) { cmd = 'z'; reset = 0; }
                        else {
                            embLog("ERROR: format-svg.c svgAddToPattern(), %s is not a valid svg path command, skipping...");
                            embLog(pathbuff);
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
            if(pos >= size - 1)
            {
                /* increase pathbuff length - leave room for 0 */
                size *= 2;
                pathbuff = (char*)realloc(pathbuff, size);
                if(!pathbuff) { embLog("ERROR: format-svg.c svgAddToPattern(), cannot re-allocate memory for pathbuff\n"); return; }
            }
        }
        free(pathbuff);
        pathbuff = 0;

        /* TODO: subdivide numMoves > 1 */

        color = svgColorToEmbColor(svgAttribute_getValue(currentElement, "stroke"));
        path->pointList = pointList;
        path->flagList = flagList;
        path->color = color;
        path->lineType = 1;
        embPattern_addPathObjectAbs(p, path);
    }
    else if(!strcmp(buff, "polygon") ||
            !strcmp(buff, "polyline"))
    {
        char* pointStr = svgAttribute_getValue(currentElement, "points");
        int last = strlen(pointStr);
        int size = 32;
        int i = 0;
        int c = 0;
        int pos = 0;
        unsigned char odd = 1;
        double xx = 0.0;
        double yy = 0.0;

        EmbArray* pointList = 0;

        char* polybuff = 0;
        polybuff = (char*)malloc(size);
        if(!polybuff) { embLog("ERROR: format-svg.c svgAddToPattern(), cannot allocate memory for polybuff\n"); return; }

        for(i = 0; i < last; i++)
        {
            char c = pointStr[i];
            switch(c)
            {
                case ' ':
                    if(pos == 0)
                        break;
                    polybuff[pos] = 0;
                    pos = 0;
                    /*Compose Point List */
                    if(odd)
                    {
                        odd = 0;
                        xx = atof(polybuff);
                    }
                    else
                    {
                        odd = 1;
                        yy = atof(polybuff);

                        if (!pointList) {
                            pointList = embArray_create(EMB_POINT);
                        }
                        EmbPointObject a;
                        a.point.x = xx;
                        a.point.y = yy;
                        embArray_addPoint(pointList, &a);
                    }

                    break;
                default:
                    polybuff[pos++] = (char)c;
                    break;
            }
            if(pos >= size - 1)
            {
                /* increase polybuff length - leave room for 0 */
                size *= 2;
                polybuff = (char*)realloc(polybuff, size);
                if(!polybuff) { embLog("ERROR: format-svg.c svgAddToPattern(), cannot re-allocate memory for polybuff\n"); return; }
            }
        }
        free(polybuff);
        polybuff = 0;

        if(!strcmp(buff, "polygon"))
        {
            EmbPolygonObject polygonObj;
            polygonObj.pointList = pointList;
            polygonObj.color = svgColorToEmbColor(svgAttribute_getValue(currentElement, "stroke"));
            polygonObj.lineType = 1; /* TODO: use lineType enum */
            embPattern_addPolygonObjectAbs(p, &polygonObj);
        }
        else /* polyline */
        {
            EmbPolylineObject* polylineObj;
            polylineObj->pointList = pointList;
            polylineObj->color = svgColorToEmbColor(svgAttribute_getValue(currentElement, "stroke"));
            polylineObj->lineType = 1; /* TODO: use lineType enum */
            embPattern_addPolylineObjectAbs(p, polylineObj);
        }
    }
    else if(!strcmp(buff, "prefetch"))         {  }
    else if(!strcmp(buff, "radialGradient"))   {  }
    else if(!strcmp(buff, "rect"))
    {
        embPattern_addRectObjectAbs(p, atof(svgAttribute_getValue(currentElement, "x")),
                                       atof(svgAttribute_getValue(currentElement, "y")),
                                       atof(svgAttribute_getValue(currentElement, "width")),
                                       atof(svgAttribute_getValue(currentElement, "height")));
    }
    else if(!strcmp(buff, "script"))           {  }
    else if(!strcmp(buff, "set"))              {  }
    else if(!strcmp(buff, "solidColor"))       {  }
    else if(!strcmp(buff, "stop"))             {  }
    else if(!strcmp(buff, "svg"))              {  }
    else if(!strcmp(buff, "switch"))           {  }
    else if(!strcmp(buff, "tbreak"))           {  }
    else if(!strcmp(buff, "text"))             {  }
    else if(!strcmp(buff, "textArea"))         {  }
    else if(!strcmp(buff, "title"))            {  }
    else if(!strcmp(buff, "tspan"))            {  }
    else if(!strcmp(buff, "use"))              {  }
    else if(!strcmp(buff, "video"))            {  }

    svgElement_free(currentElement);
    currentElement = 0;
}

int svgIsElement(const char* buff)
{
    if (stringInArray(buff, svg_element_tokens)) { return SVG_ELEMENT; }

    /* Attempt to identify the program that created the SVG file. This should be in a comment at that occurs before the svg element. */
    else if (!strcmp(buff, "Embroidermodder"))     { svgCreator = SVG_CREATOR_EMBROIDERMODDER; }
    else if (!strcmp(buff, "Illustrator"))         { svgCreator = SVG_CREATOR_ILLUSTRATOR; }
    else if (!strcmp(buff, "Inkscape"))            { svgCreator = SVG_CREATOR_INKSCAPE; }

    return SVG_NULL;
}

int svgIsMediaProperty(const char* buff)
{
    if (stringInArray(buff, svg_media_property_tokens)) { return SVG_MEDIA_PROPERTY; }
    return SVG_NULL;
}

int svgIsProperty(const char* buff)
{
    if (stringInArray(buff, svg_property_tokens)) { return SVG_PROPERTY; }
    return SVG_NULL;
}

int svgIsXmlAttribute(const char* buff)
{
    const char *tokens[] = {"encoding", "standalone", "version", "/", "\0"};
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsXmlAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsLinkAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsLinkAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsAnimateAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsAnimateAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsAnimateColorAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsAnimateColorAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsAnimateMotionAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsAnimateMotionAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsAnimateTransformAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsAnimateTransformAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsAnimationAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsAnimationAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsAudioAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsAudioAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsCircleAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsCircleAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsDefsAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "resource", "rev", "role", "typeof", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsDefsAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsDescAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsDescAttribute(), unknown:");
    embLog(buff);
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

    embLog("format-svg.c svgIsDiscardAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsEllipseAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "cx", "cy", "datatype", "focusHighlight",
        "focusable", "id", "nav-down", "nav-down-left", "nav-down-right",
        "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
        "nav-up-left", "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "rx", "ry", "systemLanguage", "transform", "typeof",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsEllipseAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsFontAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "horiz-adv-x", "horiz-origin-x", "id", "property", "rel", "resource",
        "rev", "role", "typeof", "xml:base", "xml:id", "xml:lang", "xml:space",
        "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsFontAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsFontFaceAttribute(const char* buff)
{
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

    embLog("format-svg.c svgIsFontFaceAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsFontFaceSrcAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "resource", "rev", "role", "typeof", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsFontFaceSrcAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsFontFaceUriAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "id", "property", "rel", "resource", "rev", "role",
        "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title",
        "xlink:type", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsFontFaceUriAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsForeignObjectAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsForeignObjectAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsGroupAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsGroupAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsGlyphAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "arabic-form", "class", "content", "d", "datatype",
        "glyph-name", "horiz-adv-x", "id", "lang", "property", "rel",
        "resource", "rev", "role", "typeof", "unicode", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsGlyphAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsHandlerAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "ev:event",
        "externalResourcesRequired", "id", "property", "rel", "resource",
        "rev", "role", "type", "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsHandlerAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsHKernAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "g1", "g2", "id", "k",
        "property", "rel", "resource", "rev", "role", "typeof", "u1", "u2",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;
    
    embLog("format-svg.c svgIsHKernAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsImageAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsImageAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsLineAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "id", "nav-down", "nav-down-left", "nav-down-right", "nav-left",
        "nav-next", "nav-prev", "nav-right", "nav-up", "nav-up-left",
        "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "systemLanguage", "transform", "typeof", "x1", "x2",
        "xml:base", "xml:id", "xml:lang", "xml:space", "y1", "y2", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsLineAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsLinearGradientAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "gradientUnits", "id",
        "property", "rel", "resource", "rev", "role", "typeof", "x1", "x2",
        "xml:base", "xml:id", "xml:lang", "xml:space", "y1", "y2", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsLinearGradientAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsListenerAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "defaultAction", "event",
        "handler", "id", "observer", "phase", "propagate", "property", "rel",
        "resource", "rev", "role", "target", "typeof", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsListenerAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsMetadataAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsMetadataAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsMissingGlyphAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "d", "datatype", "horiz-adv-x", "id",
        "property", "rel", "resource", "rev", "role", "typeof", "xml:base",
        "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsMissingGlyphAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsMPathAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "resource", "rev", "role", "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsMPathAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsPathAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsPathAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsPolygonAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "id", "nav-down", "nav-down-left", "nav-down-right", "nav-left",
        "nav-next", "nav-prev", "nav-right", "nav-up", "nav-up-left",
        "nav-up-right", "points", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "systemLanguage", "transform", "typeof", "xml:base",
        "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsPolygonAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsPolylineAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "id", "nav-down", "nav-down-left", "nav-down-right", "nav-left",
        "nav-next", "nav-prev", "nav-right", "nav-up", "nav-up-left",
        "nav-up-right", "points", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "systemLanguage", "transform", "typeof", "xml:base",
        "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsPolylineAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsPrefetchAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "bandwidth", "class", "content", "datatype", "id",
        "mediaCharacterEncoding", "mediaContentEncodings", "mediaSize",
        "mediaTime", "property", "rel", "resource", "rev", "role", "typeof",
        "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
        "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsPrefetchAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsRadialGradientAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "cx", "cy", "datatype", "gradientUnits",
        "id", "property", "r", "rel", "resource", "rev", "role", "typeof",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsRadialGradientAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsRectAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsRectAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsScriptAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "id", "property", "rel", "resource", "rev", "role", "type", "typeof",
        "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
        "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };   
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsScriptAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsSetAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "attributeName", "attributeType", "begin", "class", "content",
        "datatype", "dur", "end", "fill", "id", "max", "min", "property", "rel",
        "repeatCount", "repeatDur", "requiredExtensions", "requiredFeatures",
        "requiredFonts", "requiredFormats", "resource", "rev", "role",
        "systemLanguage", "to", "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsSetAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

#define SVG_SOLIDCOLOR_ATTRIBUTE  1
#define SVG_STOP_ATTRIBUTE        2
#define SVG_SVG_ATTRIBUTE        2
#define SVG_SWITCH_ATTRIBUTE     3
#define SVG_TBREAK_ATTRIBUTE     4
#define SVG_TEXT_ATTRIBUTE       5
#define SVG_TEXTAREA_ATTRIBUTE   6
#define SVG_TITLE_ATTRIBUTE      7
#define SVG_TSPAN_ATTRIBUTE      8
#define SVG_USE_ATTRIBUTE        9
#define SVG_VIDEO_ATTRIBUTE      10

int svgIsSolidColorAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "resource", "rev", "role", "typeof", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsSolidColorAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsStopAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "offset", "property",
        "rel", "resource", "rev", "role", "typeof", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsStopAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsSvgAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    if(svgCreator == SVG_CREATOR_INKSCAPE) {
        if (stringInArray(buff, inkscape_tokens))
            return SVG_ATTRIBUTE;
    }

    embLog("format-svg.c svgIsSvgAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsSwitchAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsSwitchAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsTBreakAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsTBreakAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsTextAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "editable", "focusHighlight",
        "focusable", "id", "nav-down", "nav-down-left", "nav-down-right",
        "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
        "nav-up-left", "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "rotate", "systemLanguage", "transform", "typeof", "x",
        "xml:base", "xml:id", "xml:lang", "xml:space", "y", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsTextAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsTextAreaAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsTextAreaAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsTitleAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsTitleAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsTSpanAttribute(const char* buff)
{
    const char *tokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "id", "nav-down", "nav-down-left", "nav-down-right", "nav-left",
        "nav-next", "nav-prev", "nav-right", "nav-up", "nav-up-left",
        "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "systemLanguage", "typeof", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsTSpanAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsUseAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsUseAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

int svgIsVideoAttribute(const char* buff)
{
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
    if (stringInArray(buff, tokens))
        return SVG_ATTRIBUTE;

    embLog("format-svg.c svgIsVideoAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}


int svgIsCatchAllAttribute(const char* buff)
{
    if (stringInArray(buff, svg_all_tokens))
        return SVG_CATCH_ALL;

    return SVG_NULL;
}

void svgProcess(int c, const char* buff)
{
    if(svgExpect == SVG_EXPECT_ELEMENT)
    {
        char advance = 0;
        if(buff[0] == '/') { return; }

        advance = (char)svgIsElement(buff);

        if(advance) { printf("ELEMENT:\n"); svgExpect = SVG_EXPECT_ATTRIBUTE; currentElement = svgElement_create(buff); }
        else        { return; }
    }
    else if(svgExpect == SVG_EXPECT_ATTRIBUTE)
    {
        char advance = 0;
        const char* name = 0;
        if(!currentElement) { /* TODO: error */ return; }
        name = currentElement->name;

        if(!strcmp(name, "?xml"))
        {
            if(!advance) { advance = (char)svgIsXmlAttribute(buff); }
        }
        else if(!strcmp(name, "a"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsLinkAttribute(buff); }
        }
        else if(!strcmp(name, "animate"))
        {
            if(!advance) { advance = (char)svgIsAnimateAttribute(buff); }
        }
        else if(!strcmp(name, "animateColor"))
        {
            if(!advance) { advance = (char)svgIsAnimateColorAttribute(buff); }
        }
        else if(!strcmp(name, "animateMotion"))
        {
            if(!advance) { advance = (char)svgIsAnimateMotionAttribute(buff); }
        }
        else if(!strcmp(name, "animateTransform"))
        {
            if(!advance) { advance = (char)svgIsAnimateTransformAttribute(buff); }
        }
        else if(!strcmp(name, "animation"))
        {
            if(!advance) { advance = (char)svgIsMediaProperty(buff); }
            if(!advance) { advance = (char)svgIsAnimationAttribute(buff); }
        }
        else if(!strcmp(name, "audio"))
        {
            if(!advance) { advance = (char)svgIsMediaProperty(buff); }
            if(!advance) { advance = (char)svgIsAudioAttribute(buff); }
        }
        else if(!strcmp(name, "circle"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsCircleAttribute(buff); }
        }
        else if(!strcmp(name, "defs"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsDefsAttribute(buff); }
        }
        else if(!strcmp(name, "desc"))
        {
            if(!advance) { advance = (char)svgIsMediaProperty(buff); }
            if(!advance) { advance = (char)svgIsDescAttribute(buff); }
        }
        else if(!strcmp(name, "discard"))
        {
            if(!advance) { advance = (char)svgIsDiscardAttribute(buff); }
        }
        else if(!strcmp(name, "ellipse"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsEllipseAttribute(buff); }
        }
        else if(!strcmp(name, "font"))
        {
            if(!advance) { advance = (char)svgIsFontAttribute(buff); }
        }
        else if(!strcmp(name, "font-face"))
        {
            if(!advance) { advance = (char)svgIsFontFaceAttribute(buff); }
        }
        else if(!strcmp(name, "font-face-src"))
        {
            if(!advance) { advance = (char)svgIsFontFaceSrcAttribute(buff); }
        }
        else if(!strcmp(name, "font-face-uri"))
        {
            if(!advance) { advance = (char)svgIsFontFaceUriAttribute(buff); }
        }
        else if(!strcmp(name, "foreignObject"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsForeignObjectAttribute(buff); }
        }
        else if(!strcmp(name, "g"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsGroupAttribute(buff); }
        }
        else if(!strcmp(name, "glyph"))
        {
            if(!advance) { advance = (char)svgIsGlyphAttribute(buff); }
        }
        else if(!strcmp(name, "handler"))
        {
            if(!advance) { advance = (char)svgIsHandlerAttribute(buff); }
        }
        else if(!strcmp(name, "hkern"))
        {
            if(!advance) { advance = (char)svgIsHKernAttribute(buff); }
        }
        else if(!strcmp(name, "image"))
        {
            if(!advance) { advance = (char)svgIsMediaProperty(buff); }
            if(!advance) { advance = (char)svgIsImageAttribute(buff); }
        }
        else if(!strcmp(name, "line"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsLineAttribute(buff); }
        }
        else if(!strcmp(name, "linearGradient"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsLinearGradientAttribute(buff); }
        }
        else if(!strcmp(name, "listener"))
        {
            if(!advance) { advance = (char)svgIsListenerAttribute(buff); }
        }
        else if(!strcmp(name, "metadata"))
        {
            if(!advance) { advance = (char)svgIsMediaProperty(buff); }
            if(!advance) { advance = (char)svgIsMetadataAttribute(buff); }
        }
        else if(!strcmp(name, "missing-glyph"))
        {
            if(!advance) { advance = (char)svgIsMissingGlyphAttribute(buff); }
        }
        else if(!strcmp(name, "mpath"))
        {
            if(!advance) { advance = (char)svgIsMPathAttribute(buff); }
        }
        else if(!strcmp(name, "path"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsPathAttribute(buff); }
        }
        else if(!strcmp(name, "polygon"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsPolygonAttribute(buff); }
        }
        else if(!strcmp(name, "polyline"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsPolylineAttribute(buff); }
        }
        else if(!strcmp(name, "prefetch"))
        {
            if(!advance) { advance = (char)svgIsPrefetchAttribute(buff); }
        }
        else if(!strcmp(name, "radialGradient"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsRadialGradientAttribute(buff); }
        }
        else if(!strcmp(name, "rect"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsRectAttribute(buff); }
        }
        else if(!strcmp(name, "script"))
        {
            if(!advance) { advance = (char)svgIsScriptAttribute(buff); }
        }
        else if(!strcmp(name, "set"))
        {
            if(!advance) { advance = (char)svgIsSetAttribute(buff); }
        }
        else if(!strcmp(name, "solidColor"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsSolidColorAttribute(buff); }
        }
        else if(!strcmp(name, "stop"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsStopAttribute(buff); }
        }
        else if(!strcmp(name, "svg"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsSvgAttribute(buff); }
        }
        else if(!strcmp(name, "switch"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsSwitchAttribute(buff); }
        }
        else if(!strcmp(name, "tbreak"))
        {
            if(!advance) { advance = (char)svgIsTBreakAttribute(buff); }
        }
        else if(!strcmp(name, "text"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsTextAttribute(buff); }
        }
        else if(!strcmp(name, "textArea"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsTextAreaAttribute(buff); }
        }
        else if(!strcmp(name, "title"))
        {
            if(!advance) { advance = (char)svgIsMediaProperty(buff); }
            if(!advance) { advance = (char)svgIsTitleAttribute(buff); }
        }
        else if(!strcmp(name, "tspan"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsTSpanAttribute(buff); }
        }
        else if(!strcmp(name, "use"))
        {
            if(!advance) { advance = (char)svgIsProperty(buff); }
            if(!advance) { advance = (char)svgIsUseAttribute(buff); }
        }
        else if(!strcmp(name, "video"))
        {
            if(!advance) { advance = (char)svgIsMediaProperty(buff); }
            if(!advance) { advance = (char)svgIsVideoAttribute(buff); }
        }

        if(advance)
        {
            printf("ATTRIBUTE:\n");
            svgExpect = SVG_EXPECT_VALUE;
            free(currentAttribute);
            currentAttribute = 0;
            currentAttribute = emb_strdup(buff);
        }
    }
    else if(svgExpect == SVG_EXPECT_VALUE)
    {
        int last = strlen(buff) - 1;
        printf("VALUE:\n");

        /* single-value */
        if((buff[0] == '"' || buff[0] == '\'') && (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') && !svgMultiValue)
        {
            svgExpect = SVG_EXPECT_ATTRIBUTE;
            svgElement_addAttribute(currentElement, svgAttribute_create(currentAttribute, buff));
        }
        else /* multi-value */
        {
            svgMultiValue = 1;
            if(!currentValue)
            {
                currentValue = emb_strdup(buff);
                if(!currentValue) { /*TODO: error */ return; }
            }
            else
            {
                char* tmp = 0;
                tmp = emb_strdup(currentValue);
                free(currentValue);
                currentValue = 0;
                currentValue = (char*)malloc(strlen(buff) + strlen(tmp) + 2);
                if(!currentValue) { embLog("ERROR: format-svg.c svgProcess(), cannot allocate memory for currentValue\n"); return; }
                if(currentValue) memset(currentValue, 0, strlen(buff) + strlen(tmp) + 2);
                strcat(currentValue, tmp);
                strcat(currentValue, " ");
                strcat(currentValue, buff);
                free(tmp);
                tmp = 0;
            }

            if(buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') {
                svgMultiValue = 0;
                svgExpect = SVG_EXPECT_ATTRIBUTE;
                svgElement_addAttribute(currentElement, svgAttribute_create(currentAttribute, currentValue));
                free(currentValue);
            }
        }
    }

    if (svgExpect != SVG_EXPECT_NULL) {
        puts(buff);
    }

    if (c == '>') {
        svgExpect = SVG_EXPECT_NULL;
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readSvg(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file = 0;
    int size = 1024;
    int pos;
    int c = 0, i;
    char* buff = 0;
    EmbStitch st;

    if(!pattern) { embLog("ERROR: format-svg.c readSvg(), pattern argument is null\n"); return 0; }
    if(!fileName) { embLog("ERROR: format-svg.c readSvg(), fileName argument is null\n"); return 0; }

    buff = (char*)malloc(size);
    if(!buff) { embLog("ERROR: format-svg.c readSvg(), cannot allocate memory for buff\n"); return 0; }

    svgCreator = SVG_CREATOR_NULL;

    svgExpect = SVG_EXPECT_NULL;
    svgMultiValue = 0;

    currentElement = 0;
    currentAttribute = 0;
    currentValue = 0;

    /* Pre-flip incase of multiple reads on the same pattern */
    embPattern_flipVertical(pattern);

    file = embFile_open(fileName, "r", 0);
    if(file)
    {
        pos = 0;
        do
        {
            c = embFile_getc(file);
            switch(c)
            {
                case '<':
                    if(svgExpect == SVG_EXPECT_NULL)
                    {
                        svgAddToPattern(pattern);
                        svgExpect = SVG_EXPECT_ELEMENT;
                    }
                case '>':
                    if(pos == 0) /* abnormal case that may occur in svg element where '>' is all by itself */
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
                    if(pos == 0)
                        break;
                    buff[pos] = 0;
                    pos = 0;
                    svgProcess(c, buff);
                    break;
                default:
                    buff[pos++] = (char)c;
                    break;
            }
            if(pos >= size - 1)
            {
                /* increase buff length - leave room for 0 */
                size *= 2;
                buff = (char*)realloc(buff, size);
                if (!buff) {
                    embLog("ERROR: format-svg.c readSvg(), cannot re-allocate memory for buff.");
                    return 0;
                }
            }
        }
        while(c != EOF);
        embFile_close(file);
    }
    free(buff);
    free(currentAttribute);
    free(currentValue);

    writeSvg(pattern, "object_summary.svg");

    /* Flip the pattern since SVG Y+ is down and libembroidery Y+ is up. */
    embPattern_flipVertical(pattern);

    return 1; /*TODO: finish readSvg */
}

/*! Optimizes the number (\a num) for output to a text file and writes
 *  it to the EmbFile* \a file */
static void writeDouble(EmbFile *file, double num)
{
    char str[32];
    sprintf(str, "%.10f", num);
    rTrim(str, '0');
    rTrim(str, '.');
    embFile_puts(file, str);
}

/**
 * Writes out a \a color to the EmbFile* \a file in hex format without using
 * printf or varadic functions (for embedded systems).
 */
static void writeColor(EmbFile *file, EmbColor color)
{
    char str[8];
    const char hex[] = "0123456789ABCDEF";
    str[0] = '#';
    str[1] = hex[color.r%16];
    str[2] = hex[color.r/16];
    str[3] = hex[color.g%16];
    str[4] = hex[color.g/16];
    str[5] = hex[color.b%16];
    str[6] = hex[color.b/16];
    str[7] = 0;
    embFile_puts(file, str);
}

static void writePoint(EmbFile *file, double x, double y, int space)
{
    if (space) {
        embFile_puts(file, " ");    
    }
    writeDouble(file, x);
    embFile_puts(file, ",");
    writeDouble(file, y);
}


static void writeCircles(EmbPattern *pattern, EmbFile *file)
{
    int i;
    EmbColor color;
    EmbCircle circle;
    if (pattern->circles) {
        for (i=0; i<pattern->circles->count; i++) {
            circle = pattern->circles->circle[i].circle;
            color = pattern->circles->circle[i].color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_puts(file, "\n<circle stroke-width=\"0.2\" stroke=\"");
            writeColor(file, color);
            embFile_puts(file, "\" fill=\"none\" cx=\"");
            embFile_printf(file, "%f\" cy=\"%f\" r=\"%f",
                        circle.center.x,
                        circle.center.y,
                        circle.radius);
            embFile_puts(file, "\" />");
        }
    }
}

static void writeEllipses(EmbPattern *pattern, EmbFile *file)
{
    int i;
    EmbColor color;
    EmbEllipse ellipse;
    if (pattern->ellipses) {
        for (i=0; i<pattern->ellipses->count; i++) {
            ellipse = pattern->ellipses->ellipse[i].ellipse;
            color = pattern->ellipses->ellipse[i].color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_printf(file, "\n<ellipse stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" />",
                        color.r,
                        color.g,
                        color.b,
                        ellipse.center.x,
                        ellipse.center.y,
                        ellipse.radius.x,
                        ellipse.radius.y);
        }
    }
}

static void writeLines(EmbPattern *pattern, EmbFile *file)
{
    int i;
    EmbColor color;
    EmbLine line;
    if (pattern->lines) {
        for (i=0; i<pattern->lines->count; i++) {
            EmbLine line = pattern->lines->line[i].line;
            color = pattern->lines->line[i].color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_printf(file,
                "\n<line stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />",
                color.r, color.g, color.b,
                line.start.x, line.start.y, line.end.x, line.end.y);
        }
    }
}

static void writePoints(EmbPattern *pattern, EmbFile *file)
{
    int i;
    EmbColor color;
    EmbVector point;
    if (pattern->points) {
        for (i=0; i<pattern->points->count; i++) {
            point = pattern->points->point[i].point;
            color = pattern->points->point[i].color;
            /* See SVG Tiny 1.2 Spec:
             * Section 9.5 The 'line' element
             * Section C.6 'path' element implementation notes */
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_puts(file, "\n<line stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"");
            writeColor(file, color);
            embFile_printf(file, "\" fill=\"none\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />",
                point.x, point.y, point.x, point.y);
        }
    }
}

static void writePolygons(EmbPattern *pattern, EmbFile *file)
{
    int i, j;
    EmbColor color;
    EmbArray *pointList;
    if (pattern->polygons) {
        for (i=0; i<pattern->polygons->count; i++) {
            pointList = pattern->polygons->polygon[i]->pointList;
            color = pattern->polygons->polygon[i]->color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
                embFile_printf(file, "\n<polygon stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"",
                    color.r, color.g, color.b);
            writePoint(file, pointList->point[0].point.x, pointList->point[0].point.y, 0);
            for (j=1; j<pointList->count; j++) {
                writePoint(file, pointList->point[j].point.x, pointList->point[j].point.y, 1);
            }
            embFile_puts(file, "\"/>");
        }
    }
}

static void writePolylines(EmbPattern *pattern, EmbFile *file)
{
    int i, j;
    EmbArray *pointList;
    EmbColor color;
    if (pattern->polylines) {
        for (i=0; i<pattern->polylines->count; i++) {
            pointList = pattern->polylines->polyline[i]->pointList;
            color = pattern->polylines->polyline[i]->color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_puts(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"");
            writeColor(file, color);
            embFile_puts(file, "\" fill=\"none\" points=\"");
            writePoint(file, pointList->point[0].point.x, pointList->point[0].point.y, 0);
            for (j=1; j<pointList->count; j++) {
                writePoint(file, pointList->point[j].point.x, pointList->point[j].point.y, 1);
            }
            embFile_puts(file, "\"/>");
        }
    }
}

static void writeRects(EmbPattern *pattern, EmbFile *file)
{
    int i;
    EmbRect rect;
    EmbColor color;
    if (pattern->rects) {
        for (i=0; i<pattern->rects->count; i++) {
            rect = pattern->rects->rect[i].rect;
            color = pattern->rects->rect[i].color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_puts(file, "\n<rect stroke-width=\"0.2\" stroke=\"");
            writeColor(file, color);
            embFile_puts(file, "\" fill=\"none\" x=\"");
            writeDouble(file, embRect_x(rect));
            embFile_puts(file, "\" y=\"");
            writeDouble(file, embRect_y(rect));
            embFile_puts(file, "\" width=\"");
            writeDouble(file, embRect_width(rect));
            embFile_puts(file, "\" height=\"");
            writeDouble(file, embRect_height(rect));
            embFile_puts(file, "\" />");
        }
    }
}

static void writeStitchList(EmbPattern *pattern, EmbFile *file)
{
    /*TODO: Low Priority Optimization:
     *      Make sure that the line length that is output doesn't exceed 1000 characters. */
    int i;
    char isNormal;
    EmbColor color;
    EmbStitch st;
    if (pattern->stitchList) {
        /*TODO: #ifdef SVG_DEBUG for Josh which outputs JUMPS/TRIMS instead of chopping them out */
        isNormal = 0;
        for (i=0; i<pattern->stitchList->count; i++) {
            st = pattern->stitchList->stitch[i];
            if (st.flags == NORMAL && !isNormal) {
                isNormal = 1;
                color = pattern->threads->thread[st.color].color;
                /* TODO: use proper thread width for stoke-width rather than just 0.2 */
                embFile_puts(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"");
                writeColor(file, color);
                embFile_puts(file, "\" fill=\"none\" points=\"");
                writePoint(file, st.x, st.y, 0);
            }
            else if(st.flags == NORMAL && isNormal)
            {
                writePoint(file, st.x, st.y, 1);
            }
            else if(st.flags != NORMAL && isNormal)
            {
                isNormal = 0;
                embFile_puts(file, "\"/>");
            }
        }
    }
}
 
/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeSvg(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file;
    EmbRect boundingRect;

    if (!pattern) {
        embLog("ERROR: format-svg.c writeSvg(), pattern argument is null.");
        return 0;
    }
    if (!fileName) {
        embLog("ERROR: format-svg.c writeSvg(), fileName argument is null.");
        return 0;
    }

    file = embFile_open(fileName, "w", 0);
    if (!file) return 0;

    /* Pre-flip the pattern since SVG Y+ is down and libembroidery Y+ is up. */
    embPattern_flipVertical(pattern);

    boundingRect = embPattern_calcBoundingBox(pattern);
    embFile_puts(file, "<?xml version=\"1.0\"?>\n");
    embFile_puts(file, "<!-- Embroidermodder 2 SVG Embroidery File -->\n");
    embFile_puts(file, "<!-- http://embroidermodder.github.io -->\n");
    embFile_puts(file, "<svg ");

    /* TODO: See the SVG Tiny Version 1.2 Specification Section 7.14.
    *       Until all of the formats and API is stable, the width, height and viewBox attributes need to be left unspecified.
    *       If the attribute values are incorrect, some applications wont open it at all.
    embFile_printf(file, "viewBox=\"%f %f %f %f\" ",
            boundingRect.left,
            boundingRect.top,
            embRect_width(boundingRect),
            embRect_height(boundingRect)); */

    embFile_puts(file, "xmlns=\"http://www.w3.org/2000/svg\" version=\"1.2\" baseProfile=\"tiny\">");

    /*TODO: Low Priority: Indent output properly. */

    writeCircles(pattern, file);
    writeEllipses(pattern, file);
    writeLines(pattern, file);
    writePoints(pattern, file);
    writePolygons(pattern, file);
    writePolylines(pattern, file);
    writeRects(pattern, file);
    writeStitchList(pattern, file);

    embFile_puts(file, "\n</svg>\n");
    embFile_close(file);

    /* Reset the pattern so future writes(regardless of format) are not flipped */
    embPattern_flipVertical(pattern);

    return 1;
}

