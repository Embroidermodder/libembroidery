/* This list is the index of the names list, allowing us to 
 * interpret that list without storing a pointer (8 bytes)
 * instead an unsigned short (2 bytes).
 *
 * After removing the alpha channel (1 byte), the remaining table will be
 * 2 + 3 + 2 = 7 bytes per entry as opposed to 8 + 4 + 4 = 16 bytes per entry.
 */
#define EMB_LABEL_ALICE_BLUE     1
#define EMB_LABEL_ANTIQUE_WHITE  2
#define EMB_LABEL_BLUE           1


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

static EmbColor black = { 0, 0, 0 };

/**
Type of sector
*/
#define CompoundFileSector_MaxRegSector 0xFFFFFFFA
#define CompoundFileSector_DIFAT_Sector 0xFFFFFFFC
#define CompoundFileSector_FAT_Sector 0xFFFFFFFD
#define CompoundFileSector_EndOfChain 0xFFFFFFFE
#define CompoundFileSector_FreeSector 0xFFFFFFFF

/**
Type of directory object
*/
#define ObjectTypeUnknown 0x00 /*!< Probably unallocated    */
#define ObjectTypeStorage 0x01 /*!< a directory type object */
#define ObjectTypeStream 0x02 /*!< a file type object      */
#define ObjectTypeRootEntry 0x05 /*!< the root entry          */

/**
Special values for Stream Identifiers
*/
#define CompoundFileStreamId_MaxRegularStreamId 0xFFFFFFFA /*!< All real stream Ids are less than this */
#define CompoundFileStreamId_NoStream 0xFFFFFFFF /*!< There is no valid stream Id            */

/* TODO: This list needs reviewed in case some stitch formats also can contain object data (EMBFORMAT_STCHANDOBJ). */

const EmbFormatList formatTable[100] = {
    { ".10o", "Toyota Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".100", "Toyota Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".art", "Bernina Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".bmc", "Bitmap Cache Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".bro", "Bits & Volts Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".cnd", "Melco Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".col", "Embroidery Thread Color Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".csd", "Singer Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".csv", "Comma Separated Values Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".dat", "Barudan Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".dem", "Melco Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".dsb", "Barudan Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".dst", "Tajima Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".dsz", "ZSK USA Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".dxf", "Drawing Exchange Format", ' ', ' ', EMBFORMAT_OBJECTONLY },
    { ".edr", "Embird Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".emd", "Elna Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".exp", "Melco Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".exy", "Eltac Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".eys", "Sierra Expanded Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".fxy", "Fortron Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".gc", "Smoothie G-Code Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".gnc", "Great Notions Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".gt", "Gold Thread Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".hus", "Husqvarna Viking Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".inb", "Inbro Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".inf", "Embroidery Color Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".jef", "Janome Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".ksm", "Pfaff Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".max", "Pfaff Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".mit", "Mitsubishi Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".new", "Ameco Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".ofm", "Melco Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".pcd", "Pfaff Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".pcm", "Pfaff Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".pcq", "Pfaff Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".pcs", "Pfaff Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".pec", "Brother Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".pel", "Brother Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".pem", "Brother Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".pes", "Brother Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".phb", "Brother Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".phc", "Brother Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".plt", "AutoCAD Plot Drawing Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".rgb", "RGB Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".sew", "Janome Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".shv", "Husqvarna Viking Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".sst", "Sunstar Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".stx", "Data Stitch Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".svg", "Scalable Vector Graphics", 'U', 'U', EMBFORMAT_OBJECTONLY },
    { ".t01", "Pfaff Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".t09", "Pfaff Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".tap", "Happy Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".thr", "ThredWorks Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".txt", "Text File", ' ', 'U', EMBFORMAT_STITCHONLY },
    { ".u00", "Barudan Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".u01", "Barudan Embroidery Format", ' ', ' ', EMBFORMAT_STITCHONLY },
    { ".vip", "Pfaff Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { ".vp3", "Pfaff Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".xxx", "Singer Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY },
    { ".zsk", "ZSK USA Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY },
    { "END", "END", ' ', ' ', 0 }
};

#define CSV_EXPECT_NULL   0
#define CSV_EXPECT_QUOTE1 1
#define CSV_EXPECT_QUOTE2 2
#define CSV_EXPECT_COMMA  3

#define CSV_MODE_NULL     0
#define CSV_MODE_COMMENT  1
#define CSV_MODE_VARIABLE 2
#define CSV_MODE_THREAD   3
#define CSV_MODE_STITCH   4


/* DXF Version Identifiers */
#define DXF_VERSION_R10 "AC1006"
#define DXF_VERSION_R11 "AC1009"
#define DXF_VERSION_R12 "AC1009"
#define DXF_VERSION_R13 "AC1012"
#define DXF_VERSION_R14 "AC1014"
#define DXF_VERSION_R15 "AC1015"
#define DXF_VERSION_R18 "AC1018"
#define DXF_VERSION_R21 "AC1021"
#define DXF_VERSION_R24 "AC1024"
#define DXF_VERSION_R27 "AC1027"

#define DXF_VERSION_2000 "AC1015"
#define DXF_VERSION_2002 "AC1015"
#define DXF_VERSION_2004 "AC1018"
#define DXF_VERSION_2006 "AC1018"
#define DXF_VERSION_2007 "AC1021"
#define DXF_VERSION_2009 "AC1021"
#define DXF_VERSION_2010 "AC1024"
#define DXF_VERSION_2013 "AC1027"

/* Based on the DraftSight color table */
static const unsigned char _dxfColorTable[][3] = {
    { 0, 0, 0 }, /*   '0' (BYBLOCK)    */
    { 255, 0, 0 }, /*   '1' (red)        */
    { 255, 255, 0 }, /*   '2' (yellow)     */
    { 0, 255, 0 }, /*   '3' (green)      */
    { 0, 255, 255 }, /*   '4' (cyan)       */
    { 0, 0, 255 }, /*   '5' (blue)       */
    { 255, 0, 255 }, /*   '6' (magenta)    */
    { 255, 255, 255 }, /*   '7' (white)      */
    { 128, 128, 128 }, /*   '8' (dark gray)  */
    { 192, 192, 192 }, /*   '9' (light gray) */
    { 255, 0, 0 }, /*  '10' */
    { 255, 127, 127 }, /*  '11' */
    { 204, 0, 0 }, /*  '12' */
    { 204, 102, 102 }, /*  '13' */
    { 153, 0, 0 }, /*  '14' */
    { 153, 76, 76 }, /*  '15' */
    { 127, 0, 0 }, /*  '16' */
    { 127, 63, 63 }, /*  '17' */
    { 76, 0, 0 }, /*  '18' */
    { 76, 38, 38 }, /*  '19' */
    { 255, 63, 0 }, /*  '20' */
    { 255, 159, 127 }, /*  '21' */
    { 204, 51, 0 }, /*  '22' */
    { 204, 127, 102 }, /*  '23' */
    { 153, 38, 0 }, /*  '24' */
    { 153, 95, 76 }, /*  '25' */
    { 127, 31, 0 }, /*  '26' */
    { 127, 79, 63 }, /*  '27' */
    { 76, 19, 0 }, /*  '28' */
    { 76, 47, 38 }, /*  '29' */
    { 255, 127, 0 }, /*  '30' */
    { 255, 191, 127 }, /*  '31' */
    { 204, 102, 0 }, /*  '32' */
    { 204, 153, 102 }, /*  '33' */
    { 153, 76, 0 }, /*  '34' */
    { 153, 114, 76 }, /*  '35' */
    { 127, 63, 0 }, /*  '36' */
    { 127, 95, 63 }, /*  '37' */
    { 76, 38, 0 }, /*  '38' */
    { 76, 57, 38 }, /*  '39' */
    { 255, 191, 0 }, /*  '40' */
    { 255, 223, 127 }, /*  '41' */
    { 204, 153, 0 }, /*  '42' */
    { 204, 178, 102 }, /*  '43' */
    { 153, 114, 0 }, /*  '44' */
    { 153, 133, 76 }, /*  '45' */
    { 127, 95, 0 }, /*  '46' */
    { 127, 111, 63 }, /*  '47' */
    { 76, 57, 0 }, /*  '48' */
    { 76, 66, 38 }, /*  '49' */
    { 255, 255, 0 }, /*  '50' */
    { 255, 255, 127 }, /*  '51' */
    { 204, 204, 0 }, /*  '52' */
    { 204, 204, 102 }, /*  '53' */
    { 153, 153, 0 }, /*  '54' */
    { 153, 153, 76 }, /*  '55' */
    { 127, 127, 0 }, /*  '56' */
    { 127, 127, 63 }, /*  '57' */
    { 76, 76, 0 }, /*  '58' */
    { 76, 76, 38 }, /*  '59' */
    { 191, 255, 0 }, /*  '60' */
    { 223, 255, 127 }, /*  '61' */
    { 153, 204, 0 }, /*  '62' */
    { 178, 204, 102 }, /*  '63' */
    { 114, 153, 0 }, /*  '64' */
    { 133, 153, 76 }, /*  '65' */
    { 95, 127, 0 }, /*  '66' */
    { 111, 127, 63 }, /*  '67' */
    { 57, 76, 0 }, /*  '68' */
    { 66, 76, 38 }, /*  '69' */
    { 127, 255, 0 }, /*  '70' */
    { 191, 255, 127 }, /*  '71' */
    { 102, 204, 0 }, /*  '72' */
    { 153, 204, 102 }, /*  '73' */
    { 76, 153, 0 }, /*  '74' */
    { 114, 153, 76 }, /*  '75' */
    { 63, 127, 0 }, /*  '76' */
    { 95, 127, 63 }, /*  '77' */
    { 38, 76, 0 }, /*  '78' */
    { 57, 76, 38 }, /*  '79' */
    { 63, 255, 0 }, /*  '80' */
    { 159, 255, 127 }, /*  '81' */
    { 51, 204, 0 }, /*  '82' */
    { 127, 204, 102 }, /*  '83' */
    { 38, 153, 0 }, /*  '84' */
    { 95, 153, 76 }, /*  '85' */
    { 31, 127, 0 }, /*  '86' */
    { 79, 127, 63 }, /*  '87' */
    { 19, 76, 0 }, /*  '88' */
    { 47, 76, 38 }, /*  '89' */
    { 0, 255, 0 }, /*  '90' */
    { 127, 255, 127 }, /*  '91' */
    { 0, 204, 0 }, /*  '92' */
    { 102, 204, 102 }, /*  '93' */
    { 0, 153, 0 }, /*  '94' */
    { 76, 153, 76 }, /*  '95' */
    { 0, 127, 0 }, /*  '96' */
    { 63, 127, 63 }, /*  '97' */
    { 0, 76, 0 }, /*  '98' */
    { 38, 76, 38 }, /*  '99' */
    { 0, 255, 63 }, /* '100' */
    { 127, 255, 159 }, /* '101' */
    { 0, 204, 51 }, /* '102' */
    { 102, 204, 127 }, /* '103' */
    { 0, 153, 38 }, /* '104' */
    { 76, 153, 95 }, /* '105' */
    { 0, 127, 31 }, /* '106' */
    { 63, 127, 79 }, /* '107' */
    { 0, 76, 19 }, /* '108' */
    { 38, 76, 47 }, /* '109' */
    { 0, 255, 127 }, /* '110' */
    { 127, 255, 191 }, /* '111' */
    { 0, 204, 102 }, /* '112' */
    { 102, 204, 153 }, /* '113' */
    { 0, 153, 76 }, /* '114' */
    { 76, 153, 114 }, /* '115' */
    { 0, 127, 63 }, /* '116' */
    { 63, 127, 95 }, /* '117' */
    { 0, 76, 38 }, /* '118' */
    { 38, 76, 57 }, /* '119' */
    { 0, 255, 191 }, /* '120' */
    { 127, 255, 223 }, /* '121' */
    { 0, 204, 153 }, /* '122' */
    { 102, 204, 178 }, /* '123' */
    { 0, 153, 114 }, /* '124' */
    { 76, 153, 133 }, /* '125' */
    { 0, 127, 95 }, /* '126' */
    { 63, 127, 111 }, /* '127' */
    { 0, 76, 57 }, /* '128' */
    { 38, 76, 66 }, /* '129' */
    { 0, 255, 255 }, /* '130' */
    { 127, 255, 255 }, /* '131' */
    { 0, 204, 204 }, /* '132' */
    { 102, 204, 204 }, /* '133' */
    { 0, 153, 153 }, /* '134' */
    { 76, 153, 153 }, /* '135' */
    { 0, 127, 127 }, /* '136' */
    { 63, 127, 127 }, /* '137' */
    { 0, 76, 76 }, /* '138' */
    { 38, 76, 76 }, /* '139' */
    { 0, 191, 255 }, /* '140' */
    { 127, 223, 255 }, /* '141' */
    { 0, 153, 204 }, /* '142' */
    { 102, 178, 204 }, /* '143' */
    { 0, 114, 153 }, /* '144' */
    { 76, 133, 153 }, /* '145' */
    { 0, 95, 127 }, /* '146' */
    { 63, 111, 127 }, /* '147' */
    { 0, 57, 76 }, /* '148' */
    { 38, 66, 76 }, /* '149' */
    { 0, 127, 255 }, /* '150' */
    { 127, 191, 255 }, /* '151' */
    { 0, 102, 204 }, /* '152' */
    { 102, 153, 204 }, /* '153' */
    { 0, 76, 153 }, /* '154' */
    { 76, 114, 153 }, /* '155' */
    { 0, 63, 127 }, /* '156' */
    { 63, 95, 127 }, /* '157' */
    { 0, 38, 76 }, /* '158' */
    { 38, 57, 76 }, /* '159' */
    { 0, 63, 255 }, /* '160' */
    { 127, 159, 255 }, /* '161' */
    { 0, 51, 204 }, /* '162' */
    { 102, 127, 204 }, /* '163' */
    { 0, 38, 153 }, /* '164' */
    { 76, 95, 153 }, /* '165' */
    { 0, 31, 127 }, /* '166' */
    { 63, 79, 127 }, /* '167' */
    { 0, 19, 76 }, /* '168' */
    { 38, 47, 76 }, /* '169' */
    { 0, 0, 255 }, /* '170' */
    { 127, 127, 255 }, /* '171' */
    { 0, 0, 204 }, /* '172' */
    { 102, 102, 204 }, /* '173' */
    { 0, 0, 153 }, /* '174' */
    { 76, 76, 153 }, /* '175' */
    { 0, 0, 127 }, /* '176' */
    { 63, 63, 127 }, /* '177' */
    { 0, 0, 76 }, /* '178' */
    { 38, 38, 76 }, /* '179' */
    { 63, 0, 255 }, /* '180' */
    { 159, 127, 255 }, /* '181' */
    { 51, 0, 204 }, /* '182' */
    { 127, 102, 204 }, /* '183' */
    { 38, 0, 153 }, /* '184' */
    { 95, 76, 153 }, /* '185' */
    { 31, 0, 127 }, /* '186' */
    { 79, 63, 127 }, /* '187' */
    { 19, 0, 76 }, /* '188' */
    { 47, 38, 76 }, /* '189' */
    { 127, 0, 255 }, /* '190' */
    { 191, 127, 255 }, /* '191' */
    { 102, 0, 204 }, /* '192' */
    { 153, 102, 204 }, /* '193' */
    { 76, 0, 153 }, /* '194' */
    { 114, 76, 153 }, /* '195' */
    { 63, 0, 127 }, /* '196' */
    { 95, 63, 127 }, /* '197' */
    { 38, 0, 76 }, /* '198' */
    { 57, 38, 76 }, /* '199' */
    { 191, 0, 255 }, /* '200' */
    { 223, 127, 255 }, /* '201' */
    { 153, 0, 204 }, /* '202' */
    { 178, 102, 204 }, /* '203' */
    { 114, 0, 153 }, /* '204' */
    { 133, 76, 153 }, /* '205' */
    { 95, 0, 127 }, /* '206' */
    { 111, 63, 127 }, /* '207' */
    { 57, 0, 76 }, /* '208' */
    { 66, 38, 76 }, /* '209' */
    { 255, 0, 255 }, /* '210' */
    { 255, 127, 255 }, /* '211' */
    { 204, 0, 204 }, /* '212' */
    { 204, 102, 204 }, /* '213' */
    { 153, 0, 153 }, /* '214' */
    { 153, 76, 153 }, /* '215' */
    { 127, 0, 127 }, /* '216' */
    { 127, 63, 127 }, /* '217' */
    { 76, 0, 76 }, /* '218' */
    { 76, 38, 76 }, /* '219' */
    { 255, 0, 191 }, /* '220' */
    { 255, 127, 223 }, /* '221' */
    { 204, 0, 153 }, /* '222' */
    { 204, 102, 178 }, /* '223' */
    { 153, 0, 114 }, /* '224' */
    { 153, 76, 133 }, /* '225' */
    { 127, 0, 95 }, /* '226' */
    { 127, 63, 111 }, /* '227' */
    { 76, 0, 57 }, /* '228' */
    { 76, 38, 66 }, /* '229' */
    { 255, 0, 127 }, /* '230' */
    { 255, 127, 191 }, /* '231' */
    { 204, 0, 102 }, /* '232' */
    { 204, 102, 153 }, /* '233' */
    { 153, 0, 76 }, /* '234' */
    { 153, 76, 114 }, /* '235' */
    { 127, 0, 63 }, /* '236' */
    { 127, 63, 95 }, /* '237' */
    { 76, 0, 38 }, /* '238' */
    { 76, 38, 57 }, /* '239' */
    { 255, 0, 63 }, /* '240' */
    { 255, 127, 159 }, /* '241' */
    { 204, 0, 51 }, /* '242' */
    { 204, 102, 127 }, /* '243' */
    { 153, 0, 38 }, /* '244' */
    { 153, 76, 95 }, /* '245' */
    { 127, 0, 31 }, /* '246' */
    { 127, 63, 79 }, /* '247' */
    { 76, 0, 19 }, /* '248' */
    { 76, 38, 47 }, /* '249' */
    { 51, 51, 51 }, /* '250' */
    { 91, 91, 91 }, /* '251' */
    { 132, 132, 132 }, /* '252' */
    { 173, 173, 173 }, /* '253' */
    { 214, 214, 214 }, /* '254' */
    { 255, 255, 255 }, /* '255' */
    { 0, 0, 0 } /* '256' (BYLAYER) */
};

#define MAX_LAYERS 16
#define MAX_LAYER_NAME_LENGTH 30

/*****************************************
 * HUS Colors
 ****************************************/
static const int husThreadCount = 29;
static const EmbThread husThreads[] = {
    { { 0, 0, 0 }, "Black", "TODO:HUS_CATALOG_NUMBER" },
    { { 0, 0, 255 }, "Blue", "TODO:HUS_CATALOG_NUMBER" },
    { { 0, 255, 0 }, "Light Green", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 0, 0 }, "Red", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 0, 255 }, "Purple", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 255, 0 }, "Yellow", "TODO:HUS_CATALOG_NUMBER" },
    { { 127, 127, 127 }, "Gray", "TODO:HUS_CATALOG_NUMBER" },
    { { 51, 154, 255 }, "Light Blue", "TODO:HUS_CATALOG_NUMBER" },
    { { 51, 204, 102 }, "Green", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 127, 0 }, "Orange", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 160, 180 }, "Pink", "TODO:HUS_CATALOG_NUMBER" },
    { { 153, 75, 0 }, "Brown", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 255, 255 }, "White", "TODO:HUS_CATALOG_NUMBER" },
    { { 0, 0, 127 }, "Dark Blue", "TODO:HUS_CATALOG_NUMBER" },
    { { 0, 127, 0 }, "Dark Green", "TODO:HUS_CATALOG_NUMBER" },
    { { 127, 0, 0 }, "Dark Red", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 127, 127 }, "Light Red", "TODO:HUS_CATALOG_NUMBER" },
    { { 127, 0, 127 }, "Dark Purple", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 127, 255 }, "Light Purple", "TODO:HUS_CATALOG_NUMBER" },
    { { 200, 200, 0 }, "Dark Yellow", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 255, 153 }, "Light Yellow", "TODO:HUS_CATALOG_NUMBER" },
    { { 60, 60, 60 }, "Dark Gray", "TODO:HUS_CATALOG_NUMBER" },
    { { 192, 192, 192 }, "Light Gray", "TODO:HUS_CATALOG_NUMBER" },
    { { 232, 63, 0 }, "Dark Orange", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 165, 65 }, "Light Orange", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 102, 122 }, "Dark Pink", "TODO:HUS_CATALOG_NUMBER" },
    { { 255, 204, 204 }, "Light Pink", "TODO:HUS_CATALOG_NUMBER" },
    { { 115, 40, 0 }, "Dark Brown", "TODO:HUS_CATALOG_NUMBER" },
    { { 175, 90, 10 }, "Light Brown", "TODO:HUS_CATALOG_NUMBER" }
};


static const EmbThread jefThreads[] = {
    { { 0, 0, 0 }, "Black", "" },
    { { 0, 0, 0 }, "Black", "" },
    { { 255, 255, 255 }, "White", "" },
    { { 255, 255, 23 }, "Yellow", "" },
    { { 250, 160, 96 }, "Orange", "" },
    { { 92, 118, 73 }, "Olive Green", "" },
    { { 64, 192, 48 }, "Green", "" },
    { { 101, 194, 200 }, "Sky", "" },
    { { 172, 128, 190 }, "Purple", "" },
    { { 245, 188, 203 }, "Pink", "" },
    { { 255, 0, 0 }, "Red", "" },
    { { 192, 128, 0 }, "Brown", "" },
    { { 0, 0, 240 }, "Blue", "" },
    { { 228, 195, 93 }, "Gold", "" },
    { { 165, 42, 42 }, "Dark Brown", "" },
    { { 213, 176, 212 }, "Pale Violet", "" },
    { { 252, 242, 148 }, "Pale Yellow", "" },
    { { 240, 208, 192 }, "Pale Pink", "" },
    { { 255, 192, 0 }, "Peach", "" },
    { { 201, 164, 128 }, "Beige", "" },
    { { 155, 61, 75 }, "Wine Red", "" },
    { { 160, 184, 204 }, "Pale Sky", "" },
    { { 127, 194, 28 }, "Yellow Green", "" },
    { { 185, 185, 185 }, "Silver Grey", "" },
    { { 160, 160, 160 }, "Grey", "" },
    { { 152, 214, 189 }, "Pale Aqua", "" },
    { { 184, 240, 240 }, "Baby Blue", "" },
    { { 54, 139, 160 }, "Powder Blue", "" },
    { { 79, 131, 171 }, "Bright Blue", "" },
    { { 56, 106, 145 }, "Slate Blue", "" },
    { { 0, 32, 107 }, "Nave Blue", "" },
    { { 229, 197, 202 }, "Salmon Pink", "" },
    { { 249, 103, 107 }, "Coral", "" },
    { { 227, 49, 31 }, "Burnt Orange", "" },
    { { 226, 161, 136 }, "Cinnamon", "" },
    { { 181, 148, 116 }, "Umber", "" },
    { { 228, 207, 153 }, "Blonde", "" },
    { { 225, 203, 0 }, "Sunflower", "" },
    { { 225, 173, 212 }, "Orchid Pink", "" },
    { { 195, 0, 126 }, "Peony Purple", "" },
    { { 128, 0, 75 }, "Burgundy", "" },
    { { 160, 96, 176 }, "Royal Purple", "" },
    { { 192, 64, 32 }, "Cardinal Red", "" },
    { { 202, 224, 192 }, "Opal Green", "" },
    { { 137, 152, 86 }, "Moss Green", "" },
    { { 0, 170, 0 }, "Meadow Green", "" },
    { { 33, 138, 33 }, "Dark Green", "" },
    { { 93, 174, 148 }, "Aquamarine", "" },
    { { 76, 191, 143 }, "Emerald Green", "" },
    { { 0, 119, 114 }, "Peacock Green", "" },
    { { 112, 112, 112 }, "Dark Grey", "" },
    { { 242, 255, 255 }, "Ivory White", "" },
    { { 177, 88, 24 }, "Hazel", "" },
    { { 203, 138, 7 }, "Toast", "" },
    { { 247, 146, 123 }, "Salmon", "" },
    { { 152, 105, 45 }, "Cocoa Brown", "" },
    { { 162, 113, 72 }, "Sienna", "" },
    { { 123, 85, 74 }, "Sepia", "" },
    { { 79, 57, 70 }, "Dark Sepia", "" },
    { { 82, 58, 151 }, "Violet Blue", "" },
    { { 0, 0, 160 }, "Blue Ink", "" },
    { { 0, 150, 222 }, "Solar Blue", "" },
    { { 178, 221, 83 }, "Green Dust", "" },
    { { 250, 143, 187 }, "Crimson", "" },
    { { 222, 100, 158 }, "Floral Pink", "" },
    { { 181, 80, 102 }, "Wine", "" },
    { { 94, 87, 71 }, "Olive Drab", "" },
    { { 76, 136, 31 }, "Meadow", "" },
    { { 228, 220, 121 }, "Mustard", "" },
    { { 203, 138, 26 }, "Yellow Ochre", "" },
    { { 198, 170, 66 }, "Old Gold", "" },
    { { 236, 176, 44 }, "Honeydew", "" },
    { { 248, 128, 64 }, "Tangerine", "" },
    { { 255, 229, 5 }, "Canary Yellow", "" },
    { { 250, 122, 122 }, "Vermillion", "" },
    { { 107, 224, 0 }, "Bright Green", "" },
    { { 56, 108, 174 }, "Ocean Blue", "" },
    { { 227, 196, 180 }, "Beige Grey", "" },
    { { 227, 172, 129 }, "Bamboo", "" }
};

#define HOOP_126X110 0
#define HOOP_110X110 1
#define HOOP_50X50 2
#define HOOP_140X200 3
#define HOOP_230X200 4

static const int pcmThreadCount = 65;
static const EmbThread pcmThreads[] = {
    { { 0x00, 0x00, 0x00 }, "PCM Color 1", "" },
    { { 0x00, 0x00, 0x80 }, "PCM Color 2", "" },
    { { 0x00, 0x00, 0xFF }, "PCM Color 3", "" },
    { { 0x00, 0x80, 0x80 }, "PCM Color 4", "" },
    { { 0x00, 0xFF, 0xFF }, "PCM Color 5", "" },
    { { 0x80, 0x00, 0x80 }, "PCM Color 6", "" },
    { { 0xFF, 0x00, 0xFF }, "PCM Color 7", "" },
    { { 0x80, 0x00, 0x00 }, "PCM Color 8", "" },
    { { 0xFF, 0x00, 0x00 }, "PCM Color 9", "" },
    { { 0x00, 0x80, 0x00 }, "PCM Color 10", "" },
    { { 0x00, 0xFF, 0x00 }, "PCM Color 11", "" },
    { { 0x80, 0x80, 0x00 }, "PCM Color 12", "" },
    { { 0xFF, 0xFF, 0x00 }, "PCM Color 13", "" },
    { { 0x80, 0x80, 0x80 }, "PCM Color 14", "" },
    { { 0xC0, 0xC0, 0xC0 }, "PCM Color 15", "" },
    { { 0xFF, 0xFF, 0xFF }, "PCM Color 16", "" }
};


static const int pecThreadCount = 65;
static const EmbThread pecThreads[] = {
    { { 0, 0, 0 }, "Unknown", "" }, /* Index  0 */
    { { 14, 31, 124 }, "Prussian Blue", "" }, /* Index  1 */
    { { 10, 85, 163 }, "Blue", "" }, /* Index  2 */
    { { 0, 135, 119 }, "Teal Green", "" }, /* Index  3 */ /* TODO: Verify RGB value is correct */
    { { 75, 107, 175 }, "Cornflower Blue", "" }, /* Index  4 */
    { { 237, 23, 31 }, "Red", "" }, /* Index  5 */
    { { 209, 92, 0 }, "Reddish Brown", "" }, /* Index  6 */
    { { 145, 54, 151 }, "Magenta", "" }, /* Index  7 */
    { { 228, 154, 203 }, "Light Lilac", "" }, /* Index  8 */
    { { 145, 95, 172 }, "Lilac", "" }, /* Index  9 */
    { { 158, 214, 125 }, "Mint Green", "" }, /* Index 10 */ /* TODO: Verify RGB value is correct */
    { { 232, 169, 0 }, "Deep Gold", "" }, /* Index 11 */
    { { 254, 186, 53 }, "Orange", "" }, /* Index 12 */
    { { 255, 255, 0 }, "Yellow", "" }, /* Index 13 */
    { { 112, 188, 31 }, "Lime Green", "" }, /* Index 14 */
    { { 186, 152, 0 }, "Brass", "" }, /* Index 15 */
    { { 168, 168, 168 }, "Silver", "" }, /* Index 16 */
    { { 125, 111, 0 }, "Russet Brown", "" }, /* Index 17 */ /* TODO: Verify RGB value is correct */
    { { 255, 255, 179 }, "Cream Brown", "" }, /* Index 18 */
    { { 79, 85, 86 }, "Pewter", "" }, /* Index 19 */
    { { 0, 0, 0 }, "Black", "" }, /* Index 20 */
    { { 11, 61, 145 }, "Ultramarine", "" }, /* Index 21 */
    { { 119, 1, 118 }, "Royal Purple", "" }, /* Index 22 */
    { { 41, 49, 51 }, "Dark Gray", "" }, /* Index 23 */
    { { 42, 19, 1 }, "Dark Brown", "" }, /* Index 24 */
    { { 246, 74, 138 }, "Deep Rose", "" }, /* Index 25 */
    { { 178, 118, 36 }, "Light Brown", "" }, /* Index 26 */
    { { 252, 187, 197 }, "Salmon Pink", "" }, /* Index 27 */ /* TODO: Verify RGB value is correct */
    { { 254, 55, 15 }, "Vermillion", "" }, /* Index 28 */
    { { 240, 240, 240 }, "White", "" }, /* Index 29 */
    { { 106, 28, 138 }, "Violet", "" }, /* Index 30 */
    { { 168, 221, 196 }, "Seacrest", "" }, /* Index 31 */
    { { 37, 132, 187 }, "Sky Blue", "" }, /* Index 32 */
    { { 254, 179, 67 }, "Pumpkin", "" }, /* Index 33 */
    { { 255, 243, 107 }, "Cream Yellow", "" }, /* Index 34 */
    { { 208, 166, 96 }, "Khaki", "" }, /* Index 35 */
    { { 209, 84, 0 }, "Clay Brown", "" }, /* Index 36 */
    { { 102, 186, 73 }, "Leaf Green", "" }, /* Index 37 */
    { { 19, 74, 70 }, "Peacock Blue", "" }, /* Index 38 */
    { { 135, 135, 135 }, "Gray", "" }, /* Index 39 */
    { { 216, 204, 198 }, "Warm Gray", "" }, /* Index 40 */ /* TODO: Verify RGB value is correct */
    { { 67, 86, 7 }, "Dark Olive", "" }, /* Index 41 */
    { { 253, 217, 222 }, "Flesh Pink", "" }, /* Index 42 */ /* TODO: Verify RGB value is correct */
    { { 249, 147, 188 }, "Pink", "" }, /* Index 43 */
    { { 0, 56, 34 }, "Deep Green", "" }, /* Index 44 */
    { { 178, 175, 212 }, "Lavender", "" }, /* Index 45 */
    { { 104, 106, 176 }, "Wisteria Violet", "" }, /* Index 46 */
    { { 239, 227, 185 }, "Beige", "" }, /* Index 47 */
    { { 247, 56, 102 }, "Carmine", "" }, /* Index 48 */
    { { 181, 75, 100 }, "Amber Red", "" }, /* Index 49 */ /* TODO: Verify RGB value is correct */
    { { 19, 43, 26 }, "Olive Green", "" }, /* Index 50 */
    { { 199, 1, 86 }, "Dark Fuschia", "" }, /* Index 51 */ /* TODO: Verify RGB value is correct */
    { { 254, 158, 50 }, "Tangerine", "" }, /* Index 52 */
    { { 168, 222, 235 }, "Light Blue", "" }, /* Index 53 */
    { { 0, 103, 62 }, "Emerald Green", "" }, /* Index 54 */ /* TODO: Verify RGB value is correct */
    { { 78, 41, 144 }, "Purple", "" }, /* Index 55 */
    { { 47, 126, 32 }, "Moss Green", "" }, /* Index 56 */
    { { 255, 204, 204 }, "Flesh Pink", "" }, /* Index 57 */ /* TODO: Verify RGB value is correct */ /* TODO: Flesh Pink is Index 42, is this Index incorrect? */
    { { 255, 217, 17 }, "Harvest Gold", "" }, /* Index 58 */
    { { 9, 91, 166 }, "Electric Blue", "" }, /* Index 59 */
    { { 240, 249, 112 }, "Lemon Yellow", "" }, /* Index 60 */
    { { 227, 243, 91 }, "Fresh Green", "" }, /* Index 61 */
    { { 255, 153, 0 }, "Orange", "" }, /* Index 62 */ /* TODO: Verify RGB value is correct */ /* TODO: Orange is Index 12, is this Index incorrect? */
    { { 255, 240, 141 }, "Cream Yellow", "" }, /* Index 63 */ /* TODO: Verify RGB value is correct */ /* TODO: Cream Yellow is Index 34, is this Index incorrect? */
    { { 255, 200, 200 }, "Applique", "" } /* Index 64 */
};

static const char imageWithFrame[38][48] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};


/*****************************************
 * SHV Colors
 ****************************************/
static const int shvThreadCount = 42;
static const EmbThread shvThreads[] = {
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 255 }, "Blue", "TODO:CATALOG_NUMBER" },
    { { 51, 204, 102 }, "Green", "TODO:CATALOG_NUMBER" },
    { { 255, 0, 0 }, "Red", "TODO:CATALOG_NUMBER" },
    { { 255, 0, 255 }, "Purple", "TODO:CATALOG_NUMBER" },
    { { 255, 255, 0 }, "Yellow", "TODO:CATALOG_NUMBER" },
    { { 127, 127, 127 }, "Grey", "TODO:CATALOG_NUMBER" },
    { { 51, 154, 255 }, "Light Blue", "TODO:CATALOG_NUMBER" },
    { { 0, 255, 0 }, "Light Green", "TODO:CATALOG_NUMBER" },
    { { 255, 127, 0 }, "Orange", "TODO:CATALOG_NUMBER" },
    { { 255, 160, 180 }, "Pink", "TODO:CATALOG_NUMBER" },
    { { 153, 75, 0 }, "Brown", "TODO:CATALOG_NUMBER" },
    { { 255, 255, 255 }, "White", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 255, 127, 127 }, "Light Red", "TODO:CATALOG_NUMBER" },
    { { 255, 127, 255 }, "Light Purple", "TODO:CATALOG_NUMBER" },
    { { 255, 255, 153 }, "Light Yellow", "TODO:CATALOG_NUMBER" },
    { { 192, 192, 192 }, "Light Grey", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 255, 165, 65 }, "Light Orange", "TODO:CATALOG_NUMBER" },
    { { 255, 204, 204 }, "Light Pink", "TODO:CATALOG_NUMBER" },
    { { 175, 90, 10 }, "Light Brown", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 127 }, "Dark Blue", "TODO:CATALOG_NUMBER" },
    { { 0, 127, 0 }, "Dark Green", "TODO:CATALOG_NUMBER" },
    { { 127, 0, 0 }, "Dark Red", "TODO:CATALOG_NUMBER" },
    { { 127, 0, 127 }, "Dark Purple", "TODO:CATALOG_NUMBER" },
    { { 200, 200, 0 }, "Dark Yellow", "TODO:CATALOG_NUMBER" },
    { { 60, 60, 60 }, "Dark Gray", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 232, 63, 0 }, "Dark Orange", "TODO:CATALOG_NUMBER" },
    { { 255, 102, 122 }, "Dark Pink", "TODO:CATALOG_NUMBER" }
};


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


/* Triple pointer: this could be confusing to a new programmer to the project.
 *
 * This could be a 0-1 matrix of element against attribute.
 *
 * Or we can set an unsigned char index then it takes one level.
 */
static const char **token_lists[] = {
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

static const char *stitchTypeLabels[] = {
    "STITCH", "JUMP", "TRIM", "COLOR", "END", "UNKNOWN"
};

static const char csvByLine[] = \
    "\"#\",\"Embroidermodder 2 CSV Embroidery File\"\n" \
    "\"#\",\"http://embroidermodder.github.io\"\n" \
    "\n";
static const char csvNotes[] = \
    "\"#\",\"General Notes:\"\n" \
    "\"#\",\"This file can be read by Excel or LibreOffice as CSV (Comma Separated Value) or with a text editor.\"\n" \
    "\"#\",\"Lines beginning with # are comments.\"\n" \
    "\"#\",\"Lines beginning with > are variables: [VAR_NAME], [VAR_VALUE]\"\n" \
    "\"#\",\"Lines beginning with $ are threads: [THREAD_NUMBER], [RED], [GREEN], [BLUE], [DESCRIPTION], [CATALOG_NUMBER]\"\n" \
    "\"#\",\"Lines beginning with * are stitch entries: [STITCH_TYPE], [X], [Y]\"\n" \
    "\n";
static const char csvStitchEntryNotes1[] = \
    "\"#\",\"Stitch Entry Notes:\"\n" \
    "\"#\",\"STITCH instructs the machine to move to the position [X][Y] and then make a stitch.\"\n" \
    "\"#\",\"JUMP instructs the machine to move to the position [X][Y] without making a stitch.\"\n" \
    "\"#\",\"TRIM instructs the machine to cut the thread before moving to the position [X][Y] without making a stitch.\"\n";
static const char csvStitchEntryNotes2[] = \
    "\"#\",\"COLOR instructs the machine to stop temporarily so that the user can change to a different color thread before resuming.\"\n" \
    "\"#\",\"END instructs the machine that the design is completed and there are no further instructions.\"\n" \
    "\"#\",\"UNKNOWN encompasses instructions that may not be supported currently.\"\n" \
    "\"#\",\"[X] and [Y] are absolute coordinates in millimeters (mm).\"\n" \
    "\n";


static const unsigned char vipDecodingTable[] = {
    0x2E, 0x82, 0xE4, 0x6F, 0x38, 0xA9, 0xDC, 0xC6, 0x7B, 0xB6, 0x28, 0xAC, 0xFD, 0xAA, 0x8A, 0x4E,
    0x76, 0x2E, 0xF0, 0xE4, 0x25, 0x1B, 0x8A, 0x68, 0x4E, 0x92, 0xB9, 0xB4, 0x95, 0xF0, 0x3E, 0xEF,
    0xF7, 0x40, 0x24, 0x18, 0x39, 0x31, 0xBB, 0xE1, 0x53, 0xA8, 0x1F, 0xB1, 0x3A, 0x07, 0xFB, 0xCB,
    0xE6, 0x00, 0x81, 0x50, 0x0E, 0x40, 0xE1, 0x2C, 0x73, 0x50, 0x0D, 0x91, 0xD6, 0x0A, 0x5D, 0xD6,
    0x8B, 0xB8, 0x62, 0xAE, 0x47, 0x00, 0x53, 0x5A, 0xB7, 0x80, 0xAA, 0x28, 0xF7, 0x5D, 0x70, 0x5E,
    0x2C, 0x0B, 0x98, 0xE3, 0xA0, 0x98, 0x60, 0x47, 0x89, 0x9B, 0x82, 0xFB, 0x40, 0xC9, 0xB4, 0x00,
    0x0E, 0x68, 0x6A, 0x1E, 0x09, 0x85, 0xC0, 0x53, 0x81, 0xD1, 0x98, 0x89, 0xAF, 0xE8, 0x85, 0x4F,
    0xE3, 0x69, 0x89, 0x03, 0xA1, 0x2E, 0x8F, 0xCF, 0xED, 0x91, 0x9F, 0x58, 0x1E, 0xD6, 0x84, 0x3C,
    0x09, 0x27, 0xBD, 0xF4, 0xC3, 0x90, 0xC0, 0x51, 0x1B, 0x2B, 0x63, 0xBC, 0xB9, 0x3D, 0x40, 0x4D,
    0x62, 0x6F, 0xE0, 0x8C, 0xF5, 0x5D, 0x08, 0xFD, 0x3D, 0x50, 0x36, 0xD7, 0xC9, 0xC9, 0x43, 0xE4,
    0x2D, 0xCB, 0x95, 0xB6, 0xF4, 0x0D, 0xEA, 0xC2, 0xFD, 0x66, 0x3F, 0x5E, 0xBD, 0x69, 0x06, 0x2A,
    0x03, 0x19, 0x47, 0x2B, 0xDF, 0x38, 0xEA, 0x4F, 0x80, 0x49, 0x95, 0xB2, 0xD6, 0xF9, 0x9A, 0x75,
    0xF4, 0xD8, 0x9B, 0x1D, 0xB0, 0xA4, 0x69, 0xDB, 0xA9, 0x21, 0x79, 0x6F, 0xD8, 0xDE, 0x33, 0xFE,
    0x9F, 0x04, 0xE5, 0x9A, 0x6B, 0x9B, 0x73, 0x83, 0x62, 0x7C, 0xB9, 0x66, 0x76, 0xF2, 0x5B, 0xC9,
    0x5E, 0xFC, 0x74, 0xAA, 0x6C, 0xF1, 0xCD, 0x93, 0xCE, 0xE9, 0x80, 0x53, 0x03, 0x3B, 0x97, 0x4B,
    0x39, 0x76, 0xC2, 0xC1, 0x56, 0xCB, 0x70, 0xFD, 0x3B, 0x3E, 0x52, 0x57, 0x81, 0x5D, 0x56, 0x8D,
    0x51, 0x90, 0xD4, 0x76, 0xD7, 0xD5, 0x16, 0x02, 0x6D, 0xF2, 0x4D, 0xE1, 0x0E, 0x96, 0x4F, 0xA1,
    0x3A, 0xA0, 0x60, 0x59, 0x64, 0x04, 0x1A, 0xE4, 0x67, 0xB6, 0xED, 0x3F, 0x74, 0x20, 0x55, 0x1F,
    0xFB, 0x23, 0x92, 0x91, 0x53, 0xC8, 0x65, 0xAB, 0x9D, 0x51, 0xD6, 0x73, 0xDE, 0x01, 0xB1, 0x80,
    0xB7, 0xC0, 0xD6, 0x80, 0x1C, 0x2E, 0x3C, 0x83, 0x63, 0xEE, 0xBC, 0x33, 0x25, 0xE2, 0x0E, 0x7A,
    0x67, 0xDE, 0x3F, 0x71, 0x14, 0x49, 0x9C, 0x92, 0x93, 0x0D, 0x26, 0x9A, 0x0E, 0xDA, 0xED, 0x6F,
    0xA4, 0x89, 0x0C, 0x1B, 0xF0, 0xA1, 0xDF, 0xE1, 0x9E, 0x3C, 0x04, 0x78, 0xE4, 0xAB, 0x6D, 0xFF,
    0x9C, 0xAF, 0xCA, 0xC7, 0x88, 0x17, 0x9C, 0xE5, 0xB7, 0x33, 0x6D, 0xDC, 0xED, 0x8F, 0x6C, 0x18,
    0x1D, 0x71, 0x06, 0xB1, 0xC5, 0xE2, 0xCF, 0x13, 0x77, 0x81, 0xC5, 0xB7, 0x0A, 0x14, 0x0A, 0x6B,
    0x40, 0x26, 0xA0, 0x88, 0xD1, 0x62, 0x6A, 0xB3, 0x50, 0x12, 0xB9, 0x9B, 0xB5, 0x83, 0x9B, 0x37
};

char maxHeader[] = {
        0x56, 0x43, 0x53, 0x4D, 0xFC, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0xF6, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x33, 0x37, 0x38,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4D, 0x61, 0x64, 0x65, 0x69, 0x72, 0x61, 0x20,
        0x52, 0x61, 0x79, 0x6F, 0x6E, 0x20, 0x34, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x38, 0x09, 0x31, 0x33, 0x30, 0x2F, 0x37, 0x30, 0x35, 0x20, 0x48, 0xFA, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00
    };

