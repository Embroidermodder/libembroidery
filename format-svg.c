#define ARDUINO 1

/**
 * Writes out a \a color to the EmbFile* \a file in hex format without using
 * printf or varadic functions (for embedded systems).
 */
static void writeColor(EmbFile* file, EmbColor color)
{
    char str[8];
    const char hex[] = "0123456789ABCDEF";
    str[0] = '#';
    str[1] = hex[color.r % 16];
    str[2] = hex[color.r / 16];
    str[3] = hex[color.g % 16];
    str[4] = hex[color.g / 16];
    str[5] = hex[color.b % 16];
    str[6] = hex[color.b / 16];
    str[7] = 0;
    embFile_print(file, str);
}

static void writePoint(EmbFile* file, double x, double y, int space)
{
    if (space) {
        embFile_print(file, " ");
    }
    writeFloat(file, x);
    embFile_print(file, ",");
    writeFloat(file, y);
}

void writeFloat(EmbFile* file, float number)
{
    /* TODO: fix bugs in embFloatToArray */
    /*    char buffer[30];
    embFloatToArray(buffer, number, 1.0e-7, 3, 5);
    embFile_print(file, buffer);*/
    fprintf(file->file, "%f", number);
}

#if ARDUINO
int readSvg(EmbPattern *pattern, EmbFile *file, const char *fileName)
{
    return 0;
}


int writeSvg(EmbPattern *pattern, EmbFile *file, const char *fileName)
{
    return 0;
}

#else
/* path flag codes */
#define LINETO                         0
#define MOVETO                         1
#define BULGETOCONTROL                 2
#define BULGETOEND                     4
#define ELLIPSETORAD                   8
#define ELLIPSETOEND                   16
#define CUBICTOCONTROL1                32
#define CUBICTOCONTROL2                64
#define CUBICTOEND                     128
#define QUADTOCONTROL                  256
#define QUADTOEND                      512

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

static void writePoint(EmbFile* file, double x, double y, int space);
static void writeColor(EmbFile* file, EmbColor color);
static void writeCircles(EmbPattern* pattern, EmbFile* file);
static void writeEllipse(EmbPattern* pattern, EmbFile* file);
static void writePoints(EmbPattern* pattern, EmbFile* file);
static void writePolygons(EmbPattern* pattern, EmbFile* file);
static void writePolylines(EmbPattern* pattern, EmbFile* file);
static void writeStitchList(EmbPattern* pattern, EmbFile* file);

/**
 * Tests for the presense of a string \a s in the supplied
 * \a array.
 *
 * The end of the array is marked by an empty string.
 *
 * @return 0 if not present 1 if present.
 */
static int stringInArray(const char* s, const char** array)
{
    int i;
    for (i = 0; array[i][0]; i++) {
        if (!strcmp(s, array[i])) {
            return 1;
        }
    }
    return 0;
}

/**
 * Function is similar to the Unix utility tr.
 *
 * Character for character replacement in strings.
 * Takes a string \a s and for every character in the
 * \a from string replace with the corresponding character
 * in the \a to string.
 *
 * For example: ("test", "tb", "..") -> ".es."
 */
static void charReplace(char* s, const char* from, const char* to)
{
    int i;
    for (; *s; s++) {
        for (i = 0; from[i]; i++) {
            if (*s == from[i]) {
                *s = to[i];
            }
        }
    }
}

static const char* svg_all_tokens[] = {
    /* Catch All Properties */
    "audio-level", "buffered-rendering", "color", "color-rendering", "direction",
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

typedef struct SvgAttribute_ {
    char* name;
    char* value;
} SvgAttribute;

typedef struct SvgAttributeList_ {
    SvgAttribute attribute;
    struct SvgAttributeList_* next;
} SvgAttributeList;

typedef struct SvgElement_ {
    char* name;
    SvgAttributeList* attributeList;
    SvgAttributeList* lastAttribute;
} SvgElement;

static int svgCreator;

static int svgExpect;
static int svgMultiValue;

static SvgElement* currentElement;
static char* currentAttribute;
static char* currentValue;

#define ELEMENT_XML               0
#define ELEMENT_A                 1
#define ELEMENT_ANIMATE           2
#define ELEMENT_ANIMATE_COLOR     3
#define ELEMENT_ANIMATE_MOTION    4
#define ELEMENT_ANIMATE_TRANSFORM 5
#define ELEMENT_ANIMATION         6
#define ELEMENT_AUDIO             7
#define ELEMENT_CIRCLE            8
#define ELEMENT_DEFS              9
#define ELEMENT_DESC              10
#define ELEMENT_DISCARD           11
#define ELEMENT_ELLIPSE           12
#define ELEMENT_FONT              13
#define ELEMENT_FONT_FACE         14
#define ELEMENT_FONT_FACE_SRC     15
#define ELEMENT_FONT_FACE_URI     16
#define ELEMENT_FOREIGN_OBJECT    17
#define ELEMENT_G                 18
#define ELEMENT_GLYPH             19
#define ELEMENT_HANDLER           20
#define ELEMENT_HKERN             21
#define ELEMENT_IMAGE             22
#define ELEMENT_LINE              23
#define ELEMENT_LINEAR_GRADIENT   24
#define ELEMENT_LISTENER          25
#define ELEMENT_METADATA          26
#define ELEMENT_MISSING_GLYPH     27
#define ELEMENT_MPATH             28
#define ELEMENT_PATH              29
#define ELEMENT_POLYGON           30
#define ELEMENT_POLYLINE          31
#define ELEMENT_PREFETCH          32
#define ELEMENT_RADIAL_GRADIENT   33
#define ELEMENT_RECT              34
#define ELEMENT_SCRIPT            35
#define ELEMENT_SET               36
#define ELEMENT_SOLID_COLOR       37
#define ELEMENT_STOP              38
#define ELEMENT_SVG               39
#define ELEMENT_SWITCH            40
#define ELEMENT_TBREAK            41
#define ELEMENT_TEXT              42
#define ELEMENT_TEXT_AREA         43
#define ELEMENT_TITLE             44
#define ELEMENT_TSPAN             45
#define ELEMENT_USE               46
#define ELEMENT_VIDEO             47
#define ELEMENT_UNKNOWN           48

static const char* svg_element_tokens[] = {
    "?xml", "a", "animate", "animateColor", "animateMotion", "animateTransform", "animation",
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

static const char* svg_media_property_tokens[] = {
    "audio-level", "buffered-rendering", "display", "image-rendering",
    "pointer-events", "shape-rendering", "text-rendering", "viewport-fill",
    "viewport-fill-opacity", "visibility", "\0"
};

static const char* svg_property_tokens[] = {
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

EmbColor svgColorToEmbColor(char* colorStr)
{
    EmbColor c;
    char* pEnd = 0;
    int i, length, percent;

    /* Trim out any junk spaces */
    length = 0;
    for (i=0; colorStr[i]; i++) {
        if (colorStr[i] == ' ' || colorStr[i] == '\t') continue;
        if (colorStr[i] == '\n' || colorStr[i] == '\r') continue;
        if (colorStr[i] == '%') percent = 1;
        colorStr[length] = colorStr[i];
        length++;
    }
    colorStr[length] = 0;

    /* SVGTiny1.2 Spec Section 11.13.1 syntax for color values */
    if (colorStr[0] == '#') {
        if (length == 7) {
            /* Six digit hex — #rrggbb */
            c = embColor_fromHexStr(colorStr+1);
        }
        else {
            /* Three digit hex — #rgb */
           /* Convert the 3 digit hex to a six digit hex */
            char hex[7];
            hex[0] = colorStr[1];
            hex[1] = colorStr[1];
            hex[2] = colorStr[2];
            hex[3] = colorStr[2];
            hex[4] = colorStr[3];
            hex[5] = colorStr[3];
            hex[6] = 0;

            c = embColor_fromHexStr(hex);
        }
    } else if (percent) {
        /* Float functional — rgb(R%, G%, B%) */
        charReplace(colorStr, "rgb,()%", "      ");
        c.r = (unsigned char)round(255.0 / 100.0 * strtod(colorStr, &pEnd));
        c.g = (unsigned char)round(255.0 / 100.0 * strtod(pEnd, &pEnd));
        c.b = (unsigned char)round(255.0 / 100.0 * strtod(pEnd, &pEnd));
    } else if (length > 3 && colorStr[0] == 'r' && colorStr[1] == 'g' && colorStr[2] == 'b') {
        /* Integer functional — rgb(rrr, ggg, bbb) */
        charReplace(colorStr, "rgb,()", "     ");
        c.r = (unsigned char)strtol(colorStr, &pEnd, 10);
        c.g = (unsigned char)strtol(pEnd, &pEnd, 10);
        c.b = (unsigned char)strtol(pEnd, &pEnd, 10);
    } else {
        /* Color keyword */
        int tableColor = threadColor(&c, colorStr, SVG_Colors);
        if (!tableColor) {
            printf("SVG color string not found: %s.\n", colorStr);
        }
    }

    free(colorStr);
    /* Returns black if all else fails */
    return c;
}

static int svgPathCmdToEmbPathFlag(char cmd)
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
    /*else if(toUpper(cmd) == 'BB') return BULGETOEND; */ /* NOTE: This is not part of the SVG spec, but hopefully Bulges will be added to the SVG spec someday */
    /*else { embLog("ERROR: format-svg.c svgPathCmdToEmbPathFlag(), unknown command '%c'\n", cmd); return MOVETO; } */

    return LINETO;
}

SvgAttribute svgAttribute_create(const char* name, const char* value)
{
    SvgAttribute attribute;
    char* modValue = 0;

    modValue = emb_strdup((char*)value);
    charReplace(modValue, "\"'/,", "    ");
    attribute.name = emb_strdup((char*)name);
    attribute.value = modValue;
    return attribute;
}

void svgElement_addAttribute(SvgElement* element, SvgAttribute data)
{
    if (!element) {
        embLog("ERROR: format-svg.c svgElement_addAttribute(), element argument is null.");
        return;
    }

    if (!(element->attributeList)) {
        element->attributeList = (SvgAttributeList*)malloc(sizeof(SvgAttributeList));
        if (!(element->attributeList)) {
            embLog("ERROR: format-svg.c svgElement_addAttribute(), cannot allocate memory for element->attributeList.");
            return;
        }
        element->attributeList->attribute = data;
        element->attributeList->next = 0;
        element->lastAttribute = element->attributeList;
        element->lastAttribute->next = 0;
    } else {
        SvgAttributeList* pointerLast = element->lastAttribute;
        SvgAttributeList* list = (SvgAttributeList*)malloc(sizeof(SvgAttributeList));
        if (!list) {
            embLog("ERROR: format-svg.c svgElement_addAttribute(), cannot allocate memory for list.");
            return;
        }
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
    if (!element)
        return;

    list = element->attributeList;

    while (list) {
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
    if (!element) {
        embLog("ERROR: format-svg.c svgElement_create(), cannot allocate memory for element\n");
        return 0;
    }
    element->name = emb_strdup((char*)name);
    if (!element->name) {
        embLog("ERROR: format-svg.c svgElement_create(), element->name is null\n");
        return 0;
    }
    element->attributeList = 0;
    element->lastAttribute = 0;
    return element;
}

char* svgAttribute_getValue(SvgElement* element, const char* name)
{
    SvgAttributeList* pointer = 0;

    if (!element) {
        embLog("ERROR: format-svg.c svgAttribute_getValue(), element argument is null\n");
        return "none";
    }
    if (!name) {
        embLog("ERROR: format-svg.c svgAttribute_getValue(), name argument is null\n");
        return "none";
    }
    if (!element->attributeList) { /* TODO: error */
        return "none";
    }

    pointer = element->attributeList;
    while (pointer) {
        if (!strcmp(pointer->attribute.name, name)) {
            return pointer->attribute.value;
        }
        pointer = pointer->next;
    }

    return "none";
}

void svgAddToPattern(EmbPattern* p)
{
    const char* buff = 0;
    EmbPointObject test;
    EmbColor color;
    EmbPathObject* path;

    if (!p) {
        embLog("ERROR: format-svg.c svgAddToPattern(), p argument is null\n");
        return;
    }
    if (!currentElement) {
        return;
    }

    buff = currentElement->name;
    if (!buff) {
        return;
    }

    if (!strcmp(buff, "?xml")) {
    } else if (!strcmp(buff, "a")) {
    } else if (!strcmp(buff, "animate")) {
    } else if (!strcmp(buff, "animateColor")) {
    } else if (!strcmp(buff, "animateMotion")) {
    } else if (!strcmp(buff, "animateTransform")) {
    } else if (!strcmp(buff, "animation")) {
    } else if (!strcmp(buff, "audio")) {
    } else if (!strcmp(buff, "circle")) {
        embPattern_addCircleObjectAbs(p, atof(svgAttribute_getValue(currentElement, "cx")),
            atof(svgAttribute_getValue(currentElement, "cy")),
            atof(svgAttribute_getValue(currentElement, "r")));
    } else if (!strcmp(buff, "defs")) {
    } else if (!strcmp(buff, "desc")) {
    } else if (!strcmp(buff, "discard")) {
    } else if (!strcmp(buff, "ellipse")) {
        embPattern_addEllipseObjectAbs(p, atof(svgAttribute_getValue(currentElement, "cx")),
            atof(svgAttribute_getValue(currentElement, "cy")),
            atof(svgAttribute_getValue(currentElement, "rx")),
            atof(svgAttribute_getValue(currentElement, "ry")));
    } else if (!strcmp(buff, "font")) {
    } else if (!strcmp(buff, "font-face")) {
    } else if (!strcmp(buff, "font-face-src")) {
    } else if (!strcmp(buff, "font-face-uri")) {
    } else if (!strcmp(buff, "foreignObject")) {
    } else if (!strcmp(buff, "g")) {
    } else if (!strcmp(buff, "glyph")) {
    } else if (!strcmp(buff, "handler")) {
    } else if (!strcmp(buff, "hkern")) {
    } else if (!strcmp(buff, "image")) {
    } else if (!strcmp(buff, "line")) {
        char* x1 = svgAttribute_getValue(currentElement, "x1");
        char* y1 = svgAttribute_getValue(currentElement, "y1");
        char* x2 = svgAttribute_getValue(currentElement, "x2");
        char* y2 = svgAttribute_getValue(currentElement, "y2");

        /* If the starting and ending points are the same, it is a point */
        if (!strcmp(x1, x2) && !strcmp(y1, y2))
            embPattern_addPointObjectAbs(p, atof(x1), atof(y1));
        else
            embPattern_addLineObjectAbs(p, atof(x1), atof(y1), atof(x2), atof(y2));
    } else if (!strcmp(buff, "linearGradient")) {
    } else if (!strcmp(buff, "listener")) {
    } else if (!strcmp(buff, "metadata")) {
    } else if (!strcmp(buff, "missing-glyph")) {
    } else if (!strcmp(buff, "mpath")) {
    } else if (!strcmp(buff, "path")) {
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
        if (!pathbuff) {
            embLog("ERROR: format-svg.c svgAddToPattern(), cannot allocate memory for pathbuff\n");
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
                pathbuff[pos++] = (char)c; /* add a more char */
                break;

            case ' ':
            case ',':

                /*printf("    ,'%s'    ~POS=%d  ~TRIP=%d  ~[pos]=%d\n", pathbuff,pos,trip, pathbuff[pos]);*/
                if (pos > 0) { /* append float to array, if it not yet stored */
                    pathbuff[pos] = 0;
                    pos = 0;
                    printf("    ,val:%s\n", pathbuff);
                    pathData[++trip] = atof(pathbuff);
                }
                break;

            case '-':

                if (pos > 0) { /* append float to array, if it not yet stored */
                    pathbuff[pos] = 0;
                    pos = 0;
                    printf("    -val:%s\n", pathbuff);
                    pathData[++trip] = atof(pathbuff);
                }
                pathbuff[pos++] = (char)c; /* add a more char */
                break;

            default:
                /*** ASSUMED ANY COMMAND FOUND ***/

                if (pos > 0) { /* just make sure: append float to array, if it not yet stored */
                    pathbuff[pos] = 0;
                    pos = 0;
                    printf("    >val:%s\n", pathbuff);
                    pathData[++trip] = atof(pathbuff);
                }

                /**** Compose Point List ****/

                /* below "while" is for avoid loosing last 'z' command that maybe never accomodated. */
                pendingTask = 1;
                if (i == last - 1) {
                    pendingTask = 2;
                }

                while (pendingTask > 0) {
                    pendingTask -= 1;

                    /* Check wether prior command need to be saved */
                    if (trip >= 0) {
                        trip = -1;
                        reset = -1;

                        relative = 0; /* relative to prior coordinate point or absolute coordinate? */

                        if (cmd == 'M') {
                            xx = pathData[0];
                            yy = pathData[1];
                            fx = xx;
                            fy = yy;
                        } else if (cmd == 'm') {
                            xx = pathData[0];
                            yy = pathData[1];
                            fx = xx;
                            fy = yy;
                            relative = 1;
                        } else if (cmd == 'L') {
                            xx = pathData[0];
                            yy = pathData[1];
                        } else if (cmd == 'l') {
                            xx = pathData[0];
                            yy = pathData[1];
                            relative = 1;
                        } else if (cmd == 'H') {
                            xx = pathData[0];
                            yy = ly;
                        } else if (cmd == 'h') {
                            xx = pathData[0];
                            yy = ly;
                            relative = 1;
                        } else if (cmd == 'V') {
                            xx = lx;
                            yy = pathData[1];
                        } else if (cmd == 'v') {
                            xx = lx;
                            yy = pathData[1];
                            relative = 1;
                        } else if (cmd == 'C') {
                            xx = pathData[4];
                            yy = pathData[5];
                            cx1 = pathData[0];
                            cy1 = pathData[1];
                            cx2 = pathData[2];
                            cy2 = pathData[3];
                        } else if (cmd == 'c') {
                            xx = pathData[4];
                            yy = pathData[5];
                            cx1 = pathData[0];
                            cy1 = pathData[1];
                            cx2 = pathData[2];
                            cy2 = pathData[3];
                            relative = 1;
                        }
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
                        else if (cmd == 'Z') {
                            xx = fx;
                            yy = fy;
                        } else if (cmd == 'z') {
                            xx = fx;
                            yy = fy;
                        }

                        if (!pointList && !flagList) {
                            pointList = embArray_create(EMB_POINT);
                            flagList = embArray_create(EMB_FLAG);
                        }
                        test.point.x = xx;
                        test.point.y = yy;
                        embArray_addPoint(pointList, &test);
                        embArray_addFlag(flagList, svgPathCmdToEmbPathFlag(cmd));
                        lx = xx;
                        ly = yy;

                        pathbuff[0] = (char)cmd; /* set the command for compare */
                        pathbuff[1] = 0;
                        pos = 0;

                        printf("*prior:%s (%f, %f,  %f, %f,     %f,%f,  %f) \n", pathbuff,
                            pathData[0],
                            pathData[1],
                            pathData[2],
                            pathData[3],
                            pathData[4],
                            pathData[5],
                            pathData[6]);
                    }

                    /* assign new command */
                    if (trip == -1 && reset == -1) {
                        pathbuff[0] = (char)c; /* set the command for compare */
                        pathbuff[1] = 0;

                        printf("cmd:%s\n", pathbuff);
                        cmd = c;
                        if (c>='A' && c<='Z') {
                            c += 'a' - 'A';
                        }
                        int resetValues[] = {
                          /*a  b  c  d  e  f  g  h  i  j  k  l  m */
                            7,-1, 6,-1,-1,-1,-1, 1,-1,-1,-1, 2, 2,
                          /*n  o  p  q  r  s  t  u  v  w  x  y  z */
                           -1,-1,-1, 4,-1, 4, 2,-1, 1,-1,-1,-1, 0
                        };
                        if (c>='a' && c<='z') {
                            reset = resetValues[c-'a'];
                            if (c=='m') numMoves++;
                        }
                        if (reset < 0) {
                            embLog("ERROR: format-svg.c svgAddToPattern(), %s is not a valid svg path command, skipping...");
                            embLog(pathbuff);
                            trip = -1;
                            break;
                        }
                    }
                    /* avoid loosing 'z' command that maybe never accomodated. */
                    if (i == last - 1) {
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
                    embLog("ERROR: format-svg.c svgAddToPattern(), cannot re-allocate memory for pathbuff\n");
                    return;
                }
            }
        }
        free(pathbuff);

        /* TODO: subdivide numMoves > 1 */

        color = svgColorToEmbColor(svgAttribute_getValue(currentElement, "stroke"));
        path->pointList = pointList;
        path->flagList = flagList;
        path->color = color;
        path->lineType = 1;
        embPattern_addPathObjectAbs(p, path);
    } else if (!strcmp(buff, "polygon") || !strcmp(buff, "polyline")) {
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
        if (!polybuff) {
            embLog("ERROR: format-svg.c svgAddToPattern(), cannot allocate memory for polybuff\n");
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
                if (odd) {
                    odd = 0;
                    xx = atof(polybuff);
                } else {
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
            if (pos >= size - 1) {
                /* increase polybuff length - leave room for 0 */
                size *= 2;
                polybuff = (char*)realloc(polybuff, size);
                if (!polybuff) {
                    embLog("ERROR: format-svg.c svgAddToPattern(), cannot re-allocate memory for polybuff\n");
                    return;
                }
            }
        }
        free(polybuff);
        polybuff = 0;

        if (!strcmp(buff, "polygon")) {
            EmbPolygonObject polygonObj;
            polygonObj.pointList = pointList;
            polygonObj.color = svgColorToEmbColor(svgAttribute_getValue(currentElement, "stroke"));
            polygonObj.lineType = 1; /* TODO: use lineType enum */
            embPattern_addPolygonObjectAbs(p, &polygonObj);
        } else /* polyline */
        {
            EmbPolylineObject* polylineObj;
            polylineObj->pointList = pointList;
            polylineObj->color = svgColorToEmbColor(svgAttribute_getValue(currentElement, "stroke"));
            polylineObj->lineType = 1; /* TODO: use lineType enum */
            embPattern_addPolylineObjectAbs(p, polylineObj);
        }
    } else if (!strcmp(buff, "prefetch")) {
    } else if (!strcmp(buff, "radialGradient")) {
    } else if (!strcmp(buff, "rect")) {
        embPattern_addRectObjectAbs(p, atof(svgAttribute_getValue(currentElement, "x")),
            atof(svgAttribute_getValue(currentElement, "y")),
            atof(svgAttribute_getValue(currentElement, "width")),
            atof(svgAttribute_getValue(currentElement, "height")));
    } else if (!strcmp(buff, "script")) {
    } else if (!strcmp(buff, "set")) {
    } else if (!strcmp(buff, "solidColor")) {
    } else if (!strcmp(buff, "stop")) {
    } else if (!strcmp(buff, "svg")) {
    } else if (!strcmp(buff, "switch")) {
    } else if (!strcmp(buff, "tbreak")) {
    } else if (!strcmp(buff, "text")) {
    } else if (!strcmp(buff, "textArea")) {
    } else if (!strcmp(buff, "title")) {
    } else if (!strcmp(buff, "tspan")) {
    } else if (!strcmp(buff, "use")) {
    } else if (!strcmp(buff, "video")) {
    }

    svgElement_free(currentElement);
    currentElement = 0;
}

static int svgIsElement(const char* buff)
{
    if (stringInArray(buff, svg_element_tokens)) {
        return SVG_ELEMENT;
    }

    /* Attempt to identify the program that created the SVG file. This should be in a comment at that occurs before the svg element. */
    else if (!strcmp(buff, "Embroidermodder")) {
        svgCreator = SVG_CREATOR_EMBROIDERMODDER;
    } else if (!strcmp(buff, "Illustrator")) {
        svgCreator = SVG_CREATOR_ILLUSTRATOR;
    } else if (!strcmp(buff, "Inkscape")) {
        svgCreator = SVG_CREATOR_INKSCAPE;
    }

    return SVG_NULL;
}

static char svgIsMediaProperty(const char* buff)
{
    if (stringInArray(buff, svg_media_property_tokens)) {
        return SVG_MEDIA_PROPERTY;
    }
    return SVG_NULL;
}

static char svgIsProperty(const char* buff)
{
    if (stringInArray(buff, svg_property_tokens)) {
        return SVG_PROPERTY;
    }
    return SVG_NULL;
}

/* attribute tokens */

static const char* xmlTokens[] = { "encoding", "standalone", "version", "/", "\0" };

static const char* linkTokens[] = {
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

static const char* animateTokens[] = {
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

static const char* animateColorTokens[] = {
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

static const char* animateMotionTokens[] = {
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

static const char* animateTransformTokens[] = {
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

static const char* animationTokens[] = {
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

static const char* audioTokens[] = {
        "about", "begin", "class", "content", "datatype", "dur", "end",
        "externalResourcesRequired", "fill", "id", "max", "min", "property",
        "rel", "repeatCount", "repeatDur", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "restart", "rev", "role", "syncBehavior", "syncMaster", "syncTolerance",
        "systemLanguage", "type", "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

static const char* circleTokens[] = {
        "about", "class", "content", "cx", "cy", "datatype", "focusHighlight",
        "focusable", "id", "nav-down", "nav-down-left", "nav-down-right",
        "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
        "nav-up-left", "nav-up-right", "property", "r", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "transform", "typeof", "xml:base", "xml:id", "xml:lang", "xml:space",
        "/", "\0"
    };

static const char* defsTokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "resource", "rev", "role", "typeof", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };

static const char* descTokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

static const char* discardTokens[] = {
        "about", "begin", "class", "content", "datatype", "id", "property",
        "rel", "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
        "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };

static const char* ellipseTokens[] = {
        "about", "class", "content", "cx", "cy", "datatype", "focusHighlight",
        "focusable", "id", "nav-down", "nav-down-left", "nav-down-right",
        "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
        "nav-up-left", "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "rx", "ry", "systemLanguage", "transform", "typeof",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

static const char* fontTokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "horiz-adv-x", "horiz-origin-x", "id", "property", "rel", "resource",
        "rev", "role", "typeof", "xml:base", "xml:id", "xml:lang", "xml:space",
        "/", "\0"
    };

static const char* fontFaceTokens[] = {
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

static const char* fontFaceSrcTokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "resource", "rev", "role", "typeof", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };

static const char* fontFaceUriTokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "id", "property", "rel", "resource", "rev", "role",
        "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title",
        "xlink:type", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };

static const char* foreignObjectTokens[] = {
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

static const char* groupTokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "focusHighlight", "focusable", "id", "nav-down", "nav-down-left",
        "nav-down-right", "nav-left", "nav-next", "nav-prev", "nav-right",
        "nav-up", "nav-up-left", "nav-up-right", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "transform", "typeof", "xml:base", "xml:id", "xml:lang", "xml:space",
        "/", "\0"
    };

static const char* glyphTokens[] = {
        "about", "arabic-form", "class", "content", "d", "datatype",
        "glyph-name", "horiz-adv-x", "id", "lang", "property", "rel",
        "resource", "rev", "role", "typeof", "unicode", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };

static const char* handlerTokens[] = {
        "about", "class", "content", "datatype", "ev:event",
        "externalResourcesRequired", "id", "property", "rel", "resource",
        "rev", "role", "type", "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

static const char* hkernTokens[] = {
        "about", "class", "content", "datatype", "g1", "g2", "id", "k",
        "property", "rel", "resource", "rev", "role", "typeof", "u1", "u2",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

static const char* imageTokens[] = {
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

static const char* lineTokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "id", "nav-down", "nav-down-left", "nav-down-right", "nav-left",
        "nav-next", "nav-prev", "nav-right", "nav-up", "nav-up-left",
        "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "systemLanguage", "transform", "typeof", "x1", "x2",
        "xml:base", "xml:id", "xml:lang", "xml:space", "y1", "y2", "/", "\0"
    };

static const char* linearGradientTokens[] = {
        "about", "class", "content", "datatype", "gradientUnits", "id",
        "property", "rel", "resource", "rev", "role", "typeof", "x1", "x2",
        "xml:base", "xml:id", "xml:lang", "xml:space", "y1", "y2", "/", "\0"
    };

static const char* listenerTokens[] = {
        "about", "class", "content", "datatype", "defaultAction", "event",
        "handler", "id", "observer", "phase", "propagate", "property", "rel",
        "resource", "rev", "role", "target", "typeof", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };

static const char* metadataTokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

static const char* missingGlyphTokens[] = {
        "about", "class", "content", "d", "datatype", "horiz-adv-x", "id",
        "property", "rel", "resource", "rev", "role", "typeof", "xml:base",
        "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

static const char* mpathTokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "resource", "rev", "role", "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

static const char* pathTokens[] = {
        "about", "class", "content", "d", "datatype", "focusHighlight",
        "focusable", "id", "nav-down", "nav-down-left", "nav-down-right",
        "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
        "nav-up-left", "nav-up-right", "pathLength", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "transform", "typeof", "xml:base", "xml:id", "xml:lang", "xml:space",
        "/", "\0"
    };

static const char* polygonTokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "id", "nav-down", "nav-down-left", "nav-down-right", "nav-left",
        "nav-next", "nav-prev", "nav-right", "nav-up", "nav-up-left",
        "nav-up-right", "points", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "systemLanguage", "transform", "typeof", "xml:base",
        "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

static const char* polylineTokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "id", "nav-down", "nav-down-left", "nav-down-right", "nav-left",
        "nav-next", "nav-prev", "nav-right", "nav-up", "nav-up-left",
        "nav-up-right", "points", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "systemLanguage", "transform", "typeof", "xml:base",
        "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

static const char* prefetchTokens[] = {
        "about", "bandwidth", "class", "content", "datatype", "id",
        "mediaCharacterEncoding", "mediaContentEncodings", "mediaSize",
        "mediaTime", "property", "rel", "resource", "rev", "role", "typeof",
        "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
        "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };

static const char* radialGradientTokens[] = {
        "about", "class", "content", "cx", "cy", "datatype", "gradientUnits",
        "id", "property", "r", "rel", "resource", "rev", "role", "typeof",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

static const char* rectTokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "height", "id", "nav-down", "nav-down-left", "nav-down-right",
        "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
        "nav-up-left", "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "rx", "ry", "systemLanguage", "transform", "typeof",
        "width", "x", "xml:base", "xml:id", "xml:lang", "xml:space", "y",
        "/", "\0"
    };

static const char* scriptTokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "id", "property", "rel", "resource", "rev", "role", "type", "typeof",
        "xlink:actuate", "xlink:arcrole", "xlink:href", "xlink:role",
        "xlink:show", "xlink:title", "xlink:type", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };

static const char* setTokens[] = {
        "about", "attributeName", "attributeType", "begin", "class", "content",
        "datatype", "dur", "end", "fill", "id", "max", "min", "property", "rel",
        "repeatCount", "repeatDur", "requiredExtensions", "requiredFeatures",
        "requiredFonts", "requiredFormats", "resource", "rev", "role",
        "systemLanguage", "to", "typeof", "xlink:actuate", "xlink:arcrole",
        "xlink:href", "xlink:role", "xlink:show", "xlink:title", "xlink:type",
        "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

#define SOLIDCOLOR_ATTR        1
#define STOP_ATTR              2
#define SVG_ATTR               2
#define SWITCH_ATTR            3
#define TBREAK_ATTR            4
#define TEXT_ATTR              5
#define TEXTAREA_ATTR          6
#define TITLE_ATTR             7
#define TSPAN_ATTR             8
#define USE_ATTR               9
#define VIDEO_ATTR             10

static const char* solidColorTokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "resource", "rev", "role", "typeof", "xml:base", "xml:id", "xml:lang",
        "xml:space", "/", "\0"
    };

static const char* stopTokens[] = {
        "about", "class", "content", "datatype", "id", "offset", "property",
        "rel", "resource", "rev", "role", "typeof", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };


static const char* svgTokens[] = {
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

static const char* inkscape_tokens[] = {
        "xmlns:dc", "xmlns:cc", "xmlns:rdf", "xmlns:svg", "xmlns", "\0"
    };

static char svgIsSvgAttribute(const char* buff)
{
    if (stringInArray(buff, svgTokens))
        return SVG_ATTRIBUTE;

    if (svgCreator == SVG_CREATOR_INKSCAPE) {
        if (stringInArray(buff, inkscape_tokens))
            return SVG_ATTRIBUTE;
    }

    embLog("format-svg.c svgIsSvgAttribute(), unknown:");
    embLog(buff);
    return SVG_NULL;
}

static const char* switchTokens[] = {
        "about", "class", "content", "datatype", "externalResourcesRequired",
        "focusHighlight", "focusable", "id", "nav-down", "nav-down-left",
        "nav-down-right", "nav-left", "nav-next", "nav-prev", "nav-right",
        "nav-up", "nav-up-left", "nav-up-right", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "transform", "typeof", "xml:base", "xml:id", "xml:lang", "xml:space",
        "/", "\0"
    };

static const char* tbreakTokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

static const char* textTokens[] = {
        "about", "class", "content", "datatype", "editable", "focusHighlight",
        "focusable", "id", "nav-down", "nav-down-left", "nav-down-right",
        "nav-left", "nav-next", "nav-prev", "nav-right", "nav-up",
        "nav-up-left", "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "rotate", "systemLanguage", "transform", "typeof", "x",
        "xml:base", "xml:id", "xml:lang", "xml:space", "y", "/", "\0"
    };

static const char* textAreaTokens[] = {
        "about", "class", "content", "datatype", "editable", "focusHighlight",
        "focusable", "height", "id", "nav-down", "nav-down-left",
        "nav-down-right", "nav-left", "nav-next", "nav-prev", "nav-right",
        "nav-up", "nav-up-left", "nav-up-right", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "transform", "typeof", "width", "x", "xml:base", "xml:id", "xml:lang",
        "xml:space", "y", "/", "\0"
    };

static const char* titleTokens[] = {
        "about", "class", "content", "datatype", "id", "property", "rel",
        "requiredExtensions", "requiredFeatures", "requiredFonts",
        "requiredFormats", "resource", "rev", "role", "systemLanguage",
        "typeof", "xml:base", "xml:id", "xml:lang", "xml:space", "/", "\0"
    };

static const char* tspanTokens[] = {
        "about", "class", "content", "datatype", "focusHighlight", "focusable",
        "id", "nav-down", "nav-down-left", "nav-down-right", "nav-left",
        "nav-next", "nav-prev", "nav-right", "nav-up", "nav-up-left",
        "nav-up-right", "property", "rel", "requiredExtensions",
        "requiredFeatures", "requiredFonts", "requiredFormats", "resource",
        "rev", "role", "systemLanguage", "typeof", "xml:base", "xml:id",
        "xml:lang", "xml:space", "/", "\0"
    };

static const char* useTokens[] = {
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

static const char* videoTokens[] = {
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

static int svgIsCatchAllAttribute(const char* buff)
{
    if (stringInArray(buff, svg_all_tokens))
        return SVG_CATCH_ALL;

    return SVG_NULL;
}

static char svgHasAttribute(const char *buff, const char *tokens[], const char *errormsg)
{
    if (stringInArray(buff, tokens)) {
        return SVG_ATTRIBUTE;
    }
    else {
        embLog("format-svg.c ");
        embLog(errormsg);
        embLog("attribute unknown:");
        embLog(buff);
    }

    return SVG_NULL;
}

static char identify_element(const char *token)
{
    char id;
    for (id=0; id < ELEMENT_UNKNOWN; id++) {
        if (!strcmp(svg_element_tokens[id], token)) {
            break;
        }
    }
    return id;
}

/* Triple pointer: this could be confusing to a new programmer to the project.
 *
 * This could be a 0-1 matrix of element against attribute.
 */
const char **token_lists[] = {
    xmlTokens, linkTokens, animateTokens, animateColorTokens, animateMotionTokens,
    animateTransformTokens, animationTokens, audioTokens, circleTokens, defsTokens,
    descTokens, discardTokens, ellipseTokens, fontTokens, fontFaceTokens,
    fontFaceSrcTokens, fontFaceUriTokens, foreignObjectTokens, groupTokens,
    glyphTokens, handlerTokens, hkernTokens, imageTokens, lineTokens,
    linearGradientTokens, listenerTokens, metadataTokens, missingGlyphTokens,
    mpathTokens, pathTokens, polygonTokens, polylineTokens, prefetchTokens,
    radialGradientTokens, rectTokens, scriptTokens, setTokens, solidColorTokens,
    stopTokens, svgTokens, switchTokens, tbreakTokens, textTokens, textAreaTokens,
    titleTokens, tspanTokens, useTokens, videoTokens
};

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
        if (!currentElement) {
            embLog("There is no current element but the parser expects one.");
            return;
        }
        char token = identify_element(currentElement->name);
        
        switch (token) {
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
            advance = svgIsProperty(buff);
            break;        
        case ELEMENT_ANIMATION:
        case ELEMENT_AUDIO:
        case ELEMENT_IMAGE:
        case ELEMENT_METADATA:
        case ELEMENT_TITLE:
        case ELEMENT_VIDEO:
            advance = svgIsMediaProperty(buff);
            break;
        default:
            break;
        }

        if (!advance) {
            if (token == ELEMENT_XML) {
                advance = svgHasAttribute(buff, xmlTokens, "?xml");
            }
            else if (token == ELEMENT_SVG) {
                advance = svgIsSvgAttribute(buff);
            }
            else if (token != ELEMENT_UNKNOWN) {
                advance = svgHasAttribute(buff, token_lists[token], svg_element_tokens[token]);
            }
        }

        if (advance) {
            printf("ATTRIBUTE:\n");
            svgExpect = SVG_EXPECT_VALUE;
            free(currentAttribute);
            currentAttribute = emb_strdup(buff);
        }
    } else if (svgExpect == SVG_EXPECT_VALUE) {
        int last = strlen(buff) - 1;
        printf("VALUE:\n");

        /* single-value */
        if ((buff[0] == '"' || buff[0] == '\'') && (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') && !svgMultiValue) {
            svgExpect = SVG_EXPECT_ATTRIBUTE;
            svgElement_addAttribute(currentElement, svgAttribute_create(currentAttribute, buff));
        } else /* multi-value */
        {
            svgMultiValue = 1;
            if (!currentValue) {
                currentValue = emb_strdup(buff);
                if (!currentValue) { /*TODO: error */
                    return;
                }
            } else {
                char* tmp = 0;
                tmp = emb_strdup(currentValue);
                free(currentValue);
                currentValue = 0;
                currentValue = (char*)malloc(strlen(buff) + strlen(tmp) + 2);
                if (!currentValue) {
                    embLog("ERROR: format-svg.c svgProcess(), cannot allocate memory for currentValue\n");
                    return;
                }
                if (currentValue)
                    memset(currentValue, 0, strlen(buff) + strlen(tmp) + 2);
                strcat(currentValue, tmp);
                strcat(currentValue, " ");
                strcat(currentValue, buff);
                free(tmp);
                tmp = 0;
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
        puts(buff);
    }

    if (c == '>') {
        svgExpect = SVG_EXPECT_NULL;
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readSvg(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int size = 1024;
    int pos;
    int c = 0, i;
    char* buff = 0;
    EmbStitch st;

    buff = (char*)malloc(size);
    if (!buff) {
        embLog("ERROR: format-svg.c readSvg(), cannot allocate memory for buff\n");
        return 0;
    }

    svgCreator = SVG_CREATOR_NULL;

    svgExpect = SVG_EXPECT_NULL;
    svgMultiValue = 0;

    currentElement = 0;
    currentAttribute = 0;
    currentValue = 0;

    /* Pre-flip incase of multiple reads on the same pattern */
    embPattern_flipVertical(pattern);

        pos = 0;
        do {
            c = embFile_getc(file);
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
                    embLog("ERROR: format-svg.c readSvg(), cannot re-allocate memory for buff.");
                    return 0;
                }
            }
        } while (c != EOF);

    free(buff);
    free(currentAttribute);
    free(currentValue);

    embPattern_writeAuto(pattern, "object_summary.svg");

    /* Flip the pattern since SVG Y+ is down and libembroidery Y+ is up. */
    embPattern_flipVertical(pattern);

    return 1; /*TODO: finish readSvg */
}

static void writeCircles(EmbPattern* pattern, EmbFile* file)
{
    int i;
    EmbColor color;
    EmbCircle circle;
    if (pattern->circles) {
        for (i = 0; i < pattern->circles->count; i++) {
            circle = pattern->circles->circle[i].circle;
            color = pattern->circles->circle[i].color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<circle stroke-width=\"0.2\" stroke=\"");
            writeColor(file, color);
            embFile_print(file, "\" fill=\"none\" cx=\"");
            writeFloat(file, circle.center.x);
            embFile_print(file, "\" cy=\"");
            writeFloat(file, circle.center.y);
            embFile_print(file, "\" r=\"");
            writeFloat(file, circle.radius);
            embFile_print(file, "\" />");
        }
    }
}

static void writeEllipses(EmbPattern* pattern, EmbFile* file)
{
    int i;
    EmbColor color;
    EmbEllipse ellipse;
    if (pattern->ellipses) {
        for (i = 0; i < pattern->ellipses->count; i++) {
            ellipse = pattern->ellipses->ellipse[i].ellipse;
            color = pattern->ellipses->ellipse[i].color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<ellipse stroke-width=\"0.2\" stroke=\"");
            writeColor(file, color);
            embFile_print(file, "\" fill=\"none\" cx=\"");
            writeFloat(file, ellipse.center.x);
            embFile_print(file, "\" cy=\"");
            writeFloat(file, ellipse.center.y);
            embFile_print(file, "\" rx=\"");
            writeFloat(file, ellipse.radius.x);
            embFile_print(file, "\" ry=\"");
            writeFloat(file, ellipse.radius.y);
            embFile_print(file, "\" />");
        }
    }
}

static void writeLines(EmbPattern* pattern, EmbFile* file)
{
    int i;
    EmbColor color;
    EmbLine line;
    if (pattern->lines) {
        for (i = 0; i < pattern->lines->count; i++) {
            EmbLine line = pattern->lines->line[i].line;
            color = pattern->lines->line[i].color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<line stroke-width=\"0.2\" stroke=\"");
            writeColor(file, color);
            embFile_print(file, "\" fill=\"none\" x1=\"");
            writeFloat(file, line.start.x);
            embFile_print(file, "\" y1=\"");
            writeFloat(file, line.start.y);
            embFile_print(file, "\" x2=\"");
            writeFloat(file, line.end.x);
            embFile_print(file, "\" y2=\"");
            writeFloat(file, line.end.y);
            embFile_print(file, "\" />");
        }
    }
}

static void writePoints(EmbPattern* pattern, EmbFile* file)
{
    int i;
    EmbColor color;
    EmbVector point;
    if (pattern->points) {
        for (i = 0; i < pattern->points->count; i++) {
            point = pattern->points->point[i].point;
            color = pattern->points->point[i].color;
            /* See SVG Tiny 1.2 Spec:
             * Section 9.5 The 'line' element
             * Section C.6 'path' element implementation notes */
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<line stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"");
            writeColor(file, color);
            embFile_print(file, "\" fill=\"none\" x1=\"");
            writeFloat(file, point.x);
            embFile_print(file, "\" y1=\"");
            writeFloat(file, point.y);
            embFile_print(file, "\" x2=\"");
            writeFloat(file, point.x);
            embFile_print(file, "\" y2=\"");
            writeFloat(file, point.y);
            embFile_print(file, "\" />");
        }
    }
}

static void writePolygons(EmbPattern* pattern, EmbFile* file)
{
    int i, j;
    EmbColor color;
    EmbArray* pointList;
    if (pattern->polygons) {
        for (i = 0; i < pattern->polygons->count; i++) {
            pointList = pattern->polygons->polygon[i]->pointList;
            color = pattern->polygons->polygon[i]->color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<polygon stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"");
            writeColor(file, color);
            embFile_print(file, "\" fill=\"none\" points=\"");
            writePoint(file, pointList->point[0].point.x, pointList->point[0].point.y, 0);
            for (j = 1; j < pointList->count; j++) {
                writePoint(file, pointList->point[j].point.x, pointList->point[j].point.y, 1);
            }
            embFile_print(file, "\"/>");
        }
    }
}

static void writePolylines(EmbPattern* pattern, EmbFile* file)
{
    int i, j;
    EmbArray* pointList;
    EmbColor color;
    if (pattern->polylines) {
        for (i = 0; i < pattern->polylines->count; i++) {
            pointList = pattern->polylines->polyline[i]->pointList;
            color = pattern->polylines->polyline[i]->color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"");
            writeColor(file, color);
            embFile_print(file, "\" fill=\"none\" points=\"");
            writePoint(file, pointList->point[0].point.x, pointList->point[0].point.y, 0);
            for (j = 1; j < pointList->count; j++) {
                writePoint(file, pointList->point[j].point.x, pointList->point[j].point.y, 1);
            }
            embFile_print(file, "\"/>");
        }
    }
}

static void writeRects(EmbPattern* pattern, EmbFile* file)
{
    int i;
    EmbRect rect;
    EmbColor color;
    if (pattern->rects) {
        for (i = 0; i < pattern->rects->count; i++) {
            rect = pattern->rects->rect[i].rect;
            color = pattern->rects->rect[i].color;
            /* TODO: use proper thread width for stoke-width rather than just 0.2 */
            embFile_print(file, "\n<rect stroke-width=\"0.2\" stroke=\"");
            writeColor(file, color);
            embFile_print(file, "\" fill=\"none\" x=\"");
            writeFloat(file, embRect_x(rect));
            embFile_print(file, "\" y=\"");
            writeFloat(file, embRect_y(rect));
            embFile_print(file, "\" width=\"");
            writeFloat(file, embRect_width(rect));
            embFile_print(file, "\" height=\"");
            writeFloat(file, embRect_height(rect));
            embFile_print(file, "\" />");
        }
    }
}

static void writeStitchList(EmbPattern* pattern, EmbFile* file)
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
        for (i = 0; i < pattern->stitchList->count; i++) {
            st = pattern->stitchList->stitch[i];
            if (st.flags == NORMAL && !isNormal) {
                isNormal = 1;
                color = pattern->threads->thread[st.color].color;
                /* TODO: use proper thread width for stoke-width rather than just 0.2 */
                embFile_print(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"");
                writeColor(file, color);
                embFile_print(file, "\" fill=\"none\" points=\"");
                writePoint(file, st.x, st.y, 0);
            } else if (st.flags == NORMAL && isNormal) {
                writePoint(file, st.x, st.y, 1);
            } else if (st.flags != NORMAL && isNormal) {
                isNormal = 0;
                embFile_print(file, "\"/>");
            }
        }
    }
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeSvg(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbRect boundingRect;

    /* Pre-flip the pattern since SVG Y+ is down and libembroidery Y+ is up. */
    embPattern_flipVertical(pattern);

    boundingRect = embPattern_calcBoundingBox(pattern);
    embFile_print(file, "<?xml version=\"1.0\"?>\n");
    embFile_print(file, "<!-- Embroidermodder 2 SVG Embroidery File -->\n");
    embFile_print(file, "<!-- http://embroidermodder.github.io -->\n");
    embFile_print(file, "<svg ");

    /* TODO: See the SVG Tiny Version 1.2 Specification Section 7.14.
     *       Until all of the formats and API is stable, the width, height and viewBox attributes need to be left unspecified.
     *       If the attribute values are incorrect, some applications wont open it at all.
     */
    embFile_print(file, "viewBox=\"");
    writeFloat(file, boundingRect.left);
    embFile_print(file, " ");
    writeFloat(file, boundingRect.top);
    embFile_print(file, " ");
    writeFloat(file, embRect_width(boundingRect));
    embFile_print(file, " ");
    writeFloat(file, embRect_height(boundingRect));
    embFile_print(file, "\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.2\" baseProfile=\"tiny\">");

    /*TODO: Low Priority: Indent output properly. */

    writeCircles(pattern, file);
    writeEllipses(pattern, file);
    writeLines(pattern, file);
    writePoints(pattern, file);
    writePolygons(pattern, file);
    writePolylines(pattern, file);
    writeRects(pattern, file);
    writeStitchList(pattern, file);

    embFile_print(file, "\n</svg>\n");

    /* Reset the pattern so future writes(regardless of format) are not flipped */
    embPattern_flipVertical(pattern);

    return 1;
}

#endif

#undef ARDUINO
