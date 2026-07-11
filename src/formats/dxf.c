/**
 * @file autodesk.c
 *
 * Drawing Exchange Format (.dxf)
 *
 * Graphics format for drawing files designed and used by AudoDesk for their AutoCAD program. \cite{dxf_reference}
 */

#include <stdlib.h>
#include <string.h>

#include "embroidery.h"

void readLine(FILE *file, int8_t *str)
{
    int i;
    int past_leading_spaces;

    /* Remove leading spaces. */
    past_leading_spaces = 0;
    for (i = 0; i < 254; i++) {
        if (feof(file)) {
            str[i] = 0;
            break;
        }
        str[i] = fgetc(file);
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = 0;
            break;
        }
        if (str[i] == ' ') {
            if (!past_leading_spaces) {
                i--;
            }
        } else {
            past_leading_spaces = 0;
        }
    }
}

/* Use parsing library here. Write down full DXF grammar. */
int8_t readDxf(EmbPattern *pattern, FILE *file)
{
    int8_t dxfVersion[100];
    int8_t section[100];
    int8_t tableName[100];
    int8_t layerName[100];
    int8_t entityType[100];
    /*char layerColorHash[100][8]; *//* hash <layerName, EmbColor> */

    if (emb_verbose > 0) {
        printf("pattern = \"%p\"\n", pattern);
    }

    int eof = 0;                /* End Of File */

    /* Max token size 100 chars. */
    int8_t buff[100];
    EmbVector prev, pos, first;
    EmbReal bulge = 0.0f;
    if (emb_verbose > 0) {
        printf("float = \"%f\"\n", bulge);
    }
    int8_t firstStitch = 1;
    printf("%c\n", firstStitch);
    int8_t bulgeFlag = 0;
    int fileLength = 0;
    first.x = 0.0f;
    first.y = 0.0f;
    pos.x = 0.0f;
    pos.y = 0.0f;
    prev.x = 0.0f;
    prev.y = 0.0f;
    printf("%f %f %f\n", prev.x, pos.x, first.x);

    fseek(file, 0L, SEEK_END);

    fileLength = ftell(file);
    fseek(file, 0L, SEEK_SET);

    while (ftell(file) < fileLength) {
        readLine(file, buff);
        /*printf("%s\n", buff); */
        if ((string_equal(buff, "HEADER")) ||
            (string_equal(buff, "CLASSES")) ||
            (string_equal(buff, "TABLES")) ||
            (string_equal(buff, "BLOCKS")) ||
            (string_equal(buff, "ENTITIES")) ||
            (string_equal(buff, "OBJECTS")) ||
            (string_equal(buff, "THUMBNAILIMAGE"))) {
            string_copy(section, buff);
            printf("SECTION:%s\n", buff);
        }
        if (string_equal(buff, "ENDSEC")) {
            section[0] = 0;
            printf("ENDSEC:%s\n", buff);
        }
        if ((string_equal(buff, "ARC")) ||
            (string_equal(buff, "CIRCLE")) ||
            (string_equal(buff, "ELLIPSE")) ||
            (string_equal(buff, "LINE")) ||
            (string_equal(buff, "LWPOLYLINE"))
            || (string_equal(buff, "POINT"))) {
            string_copy(entityType, buff);
        }
        if (string_equal(buff, "EOF")) {
            eof = 1;
        }

        if (string_equal(section, "HEADER")) {
            if (string_equal(buff, "$ACADVER")) {
                readLine(file, buff);
                readLine(file, dxfVersion);
                /* TODO: Allow these versions when POLYLINE is handled. */
                if ((string_equal(dxfVersion, DXF_VERSION_R10))
                    || (string_equal(dxfVersion, DXF_VERSION_R11))
                    || (string_equal(dxfVersion, DXF_VERSION_R12))
                    || (string_equal(dxfVersion, DXF_VERSION_R13))) {
                    return 0;
                }
            }
        } else if (string_equal(section, "TABLES")) {
            if (string_equal(buff, "ENDTAB")) {
                tableName[0] = 0;
            }

            if (tableName[0] == 0) {
                if (string_equal(buff, "2")) {  /* Table Name */
                    readLine(file, tableName);
                }
            } else if (string_equal(tableName, "LAYER")) {
                /* Common Group Codes for Tables */
                if (string_equal(buff, "5")) {  /* Handle */
                    readLine(file, buff);
                    continue;
                } else if (string_equal(buff, "330")) { /* Soft Pointer */
                    readLine(file, buff);
                    continue;
                } else if (string_equal(buff, "100")) { /* Subclass Marker */
                    readLine(file, buff);
                    continue;
                } else if (string_equal(buff, "70")) {  /* Number of Entries in Table */
                    readLine(file, buff);
                    continue;
                }
                /* The meaty stuff */
                else if (string_equal(buff, "2")) {     /* Layer Name */
                    readLine(file, layerName);
                } else if (string_equal(buff, "62")) {  /* Color Number */
                    uint8_t colorNum;
                    EmbColor co;

                    readLine(file, buff);
                    colorNum = atoi((char *)buff);

                    /* Why is this here twice? */
                    colorNum = atoi((char *)buff);
                    co = dxf_colors[colorNum].color;
                    printf("inserting:%s,%d,%d,%d\n",
                           layerName, co.r, co.g, co.b);
                    /* TODO: fix this with a lookup finish this
                       if (embHash_insert(layerColorHash, emb_strdup(layerName), co))
                       {
                       TODO: log error: failed inserting into layerColorHash
                       }
                     */
                    layerName[0] = 0;
                }
            }
        } else if (string_equal(section, "ENTITIES")) {
            /* Common Group Codes for Entities */
            if (string_equal(buff, "5")) {      /* Handle */
                readLine(file, buff);
                continue;
            } else if (string_equal(buff, "330")) {     /* Soft Pointer */
                readLine(file, buff);
                continue;
            } else if (string_equal(buff, "100")) {     /* Subclass Marker */
                readLine(file, buff);
                continue;
            } else if (string_equal(buff, "8")) {       /* Layer Name */
                readLine(file, buff);
                /* emb_pattern_changeColor(pattern, colorIndexMap[buff]); TODO: port to C */
                continue;
            }

            if (string_equal(entityType, "LWPOLYLINE")) {
                /* The not so important group codes */
                if (string_equal(buff, "90")) { /* Vertices */
                    readLine(file, buff);
                    continue;
                } else if (string_equal(buff, "70")) {  /* Polyline Flag */
                    readLine(file, buff);
                    continue;
                }
                /* TODO: Try to use the widths at some point */
                else if (string_equal(buff, "40")) {    /* Starting Width */
                    readLine(file, buff);
                    continue;
                } else if (string_equal(buff, "41")) {  /* Ending Width */
                    readLine(file, buff);
                    continue;
                } else if (string_equal(buff, "43")) {  /* Constant Width */
                    readLine(file, buff);
                    continue;
                }
                /* The meaty stuff */
                else if (string_equal(buff, "42")) {    /* Bulge */
                    readLine(file, buff);
                    bulge = atof((char *)buff);
                    bulgeFlag = 1;
                    printf("bulgeFlag %d\n", bulgeFlag);
                } else if (string_equal(buff, "10")) {  /* X */
                    readLine(file, buff);
                    pos.x = atof((char *)buff);
                } else if (string_equal(buff, "20")) {  /* Y */
#if 0
                    readLine(file, buff);
                    pos.y = atof((char *)buff);

                    if (bulgeFlag) {
                        EmbArc arc;
                        bulgeFlag = 0;
                        arc.start = prev;
                        arc.end = pos;
                        /*TODO: error */
                        /*
                           if (!getArcDataFromBulge(bulge, &arc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {
                           return 0;
                           }
                         */
                        return 0;
                        if (firstStitch) {
                            /* emb_pattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        }
                        /* emb_pattern_addStitchAbs(pattern, x, y, ARC, 1); TODO: Add arcTo point to embPath pointList */
                    } else {
                        /*if (firstStitch) emb_pattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        /*else            emb_pattern_addStitchAbs(pattern, x, y, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
                    }
                    prev = pos;
                    if (firstStitch) {
                        first = pos;
                        firstStitch = 0;
                    }
#endif
                } else if (string_equal(buff, "0")) {
#if 0
                    entityType[0] = 0;
                    firstStitch = 1;
                    if (bulgeFlag) {
                        EmbArc arc;
                        bulgeFlag = 0;
                        arc.start = prev;
                        arc.end = first;
                        /* TODO: error */
                        /*
                           if (!getArcDataFromBulge(bulge, &arc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {
                           return 0;
                           }
                         */
                        return 0;
                        prev = arc.start;
                        /* emb_pattern_addStitchAbs(pattern, prevX, prevY, ARC, 1);
                         * TODO: Add arcTo point to embPath pointList */
                    } else {
                        /* emb_pattern_addStitchAbs(pattern, firstX, firstY, NORMAL, 1);
                         * TODO: Add lineTo point to embPath pointList */
                    }
#endif
                }
            }                   /* end LWPOLYLINE */
        }                       /* end ENTITIES section */
    }                           /* end while loop */

    /*
       EmbColor* testColor = 0;
       testColor = embHash_value(layerColorHash, "OMEGA");
       if (!testColor) {
       printf("NULL POINTER!\n");
       }
       else {
       printf("LAYERCOLOR: %d,%d,%d\n", testColor->r, testColor->g, testColor->b);
       }
     */

    if (!eof) {
        /* NOTE: The EOF item must be present at the end of file to be considered a valid DXF file. */
        printf
            ("ERROR: format-dxf.c readDxf(), missing EOF at end of DXF file\n");
    }
    return eof;
}

int8_t writeDxf(EmbPattern *pattern, FILE *file)
{
    puts("ERROR: writeDxf not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void *)pattern, (void *)file);
    }
    return 0;                   /*TODO: finish writeDxf */
}
