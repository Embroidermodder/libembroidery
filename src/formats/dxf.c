/* Drawing Exchange Format (.dxf)
 * Graphics format for drawing files designed and used by AudoDesk for their AutoCAD program. \cite{dxf_reference}
 */

#include <stdlib.h>
#include <string.h>

#include "embroidery.h"

void
readLine(FILE* file, char *str)
{
    int i;
    int past_leading_spaces;

    /* Remove leading spaces. */
    past_leading_spaces = 0;
    for (i=0; i<254; i++) {
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
        }
        else {
            past_leading_spaces = 0;
        }
    }
}

/* Use parsing library here. Write down full DXF grammar. */
char
readDxf(EmbPattern* pattern, FILE* file)
{
    EmbString dxfVersion;
    EmbString section;
    EmbString tableName;
    EmbString layerName;
    EmbString entityType;
    /*char layerColorHash[100][8]; */ /* hash <layerName, EmbColor> */

    REPORT_PTR(pattern);

    int eof = 0; /* End Of File */

    EmbString buff;
    EmbVector prev, pos, first;
    EmbReal bulge = 0.0f;
    REPORT_FLOAT(bulge);
    char firstStitch = 1;
    printf("%c\n", firstStitch);
    char bulgeFlag = 0;
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
        /*printf("%s\n", buff);*/
        if ((!strcmp(buff, "HEADER"))   ||
            (!strcmp(buff, "CLASSES"))  ||
            (!strcmp(buff, "TABLES"))   ||
            (!strcmp(buff, "BLOCKS"))   ||
            (!strcmp(buff, "ENTITIES")) ||
            (!strcmp(buff, "OBJECTS"))  ||
            (!strcmp(buff, "THUMBNAILIMAGE"))) {
            strcpy(section, buff);
            printf("SECTION:%s\n", buff);
        }
        if (!strcmp(buff, "ENDSEC")) {
            strcpy(section, "");
            printf("ENDSEC:%s\n", buff);
        }
        if ( (!strcmp(buff, "ARC")) ||
            (!strcmp(buff, "CIRCLE")) ||
            (!strcmp(buff, "ELLIPSE")) ||
            (!strcmp(buff, "LINE")) ||
            (!strcmp(buff, "LWPOLYLINE")) ||
            (!strcmp(buff, "POINT"))) {
            strcpy(entityType, buff);
        }
        if (!strcmp(buff, "EOF")) {
            eof = 1;
        }

        if (!strcmp(section, "HEADER")) {
            if (!strcmp(buff, "$ACADVER"))
            {
                readLine(file, buff);
                readLine(file, dxfVersion);
                /* TODO: Allow these versions when POLYLINE is handled. */
                if ((!strcmp(dxfVersion, DXF_VERSION_R10))
                || (!strcmp(dxfVersion, DXF_VERSION_R11))
                || (!strcmp(dxfVersion, DXF_VERSION_R12))
                || (!strcmp(dxfVersion, DXF_VERSION_R13))) {
                    return 0;
                }
            }
        }
        else if (!strcmp(section,"TABLES")) {
            if (!strcmp(buff,"ENDTAB")) {
                tableName[0] = 0;
            }

            if (tableName[0] == 0) {
                if (!strcmp(buff,"2")) { /* Table Name */
                    readLine(file, tableName);
                }
            }
            else if (!strcmp(tableName, "LAYER"))
            {
                /* Common Group Codes for Tables */
                if (!strcmp(buff,"5")) /* Handle */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"330")) /* Soft Pointer */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"100")) /* Subclass Marker */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"70")) /* Number of Entries in Table */
                {
                    readLine(file, buff);
                    continue;
                }
                /* The meaty stuff */
                else if (!strcmp(buff,"2")) /* Layer Name */
                {
                    readLine(file, layerName);
                }
                else if (!strcmp(buff,"62")) /* Color Number */
                {
                    unsigned char colorNum;
                    EmbColor co;

                    readLine(file, buff);
                    colorNum = atoi(buff);

        /* Why is this here twice? */
                    colorNum = atoi(buff);
                    co = dxf_colors[colorNum].color;
                    printf("inserting:%s,%d,%d,%d\n", layerName, co.r, co.g, co.b);
                    /* TODO: fix this with a lookup finish this
                    if (embHash_insert(layerColorHash, emb_strdup(layerName), co))
                    {
                         TODO: log error: failed inserting into layerColorHash
                    }
                    */
                    layerName[0] = 0;
                }
            }
        }
        else if (!strcmp(section,"ENTITIES")) {
            /* Common Group Codes for Entities */
            if (!strcmp(buff, "5")) /* Handle */
            {
                readLine(file, buff);
                continue;
            }
            else if (!strcmp(buff, "330")) /* Soft Pointer */
            {
                readLine(file, buff);
                continue;
            }
            else if (!strcmp(buff, "100")) /* Subclass Marker */
            {
                readLine(file, buff);
                continue;
            }
            else if (!strcmp(buff, "8")) /* Layer Name */
            {
                readLine(file, buff);
                /* emb_pattern_changeColor(pattern, colorIndexMap[buff]); TODO: port to C */
                continue;
            }

            if (!strcmp(entityType,"LWPOLYLINE")) {
                /* The not so important group codes */
                if (!strcmp(buff, "90")) /* Vertices */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"70")) /* Polyline Flag */
                {
                    readLine(file, buff);
                    continue;
                }
                /* TODO: Try to use the widths at some point */
                else if (!strcmp(buff,"40")) /* Starting Width */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"41")) /* Ending Width */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"43")) /* Constant Width */
                {
                    readLine(file, buff);
                    continue;
                }
                /* The meaty stuff */
                else if (!strcmp(buff,"42")) /* Bulge */
                {
                    readLine(file, buff);
                    bulge = atof(buff);
                    bulgeFlag = 1;
                    printf("bulgeFlag %d\n", bulgeFlag);
                }
                else if (!strcmp(buff,"10")) /* X */
                {
                    readLine(file, buff);
                    pos.x = atof(buff);
                }
                else if (!strcmp(buff,"20")) /* Y */
                {
#if 0
                    readLine(file, buff);
                    pos.y = atof(buff);

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
                    }
                    else {
                        /*if (firstStitch) emb_pattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        /*else            emb_pattern_addStitchAbs(pattern, x, y, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
                    }
                    prev = pos;
                    if (firstStitch) {
                        first = pos;
                        firstStitch = 0;
                    }
#endif
                }
                else if (!strcmp(buff,"0")) {
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
                    }
                    else {
                        /* emb_pattern_addStitchAbs(pattern, firstX, firstY, NORMAL, 1);
                         * TODO: Add lineTo point to embPath pointList */
                    }
#endif
                }
            } /* end LWPOLYLINE */
        } /* end ENTITIES section */
    } /* end while loop */

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
        printf("ERROR: format-dxf.c readDxf(), missing EOF at end of DXF file\n");
    }
    return eof;
}

char
writeDxf(EmbPattern* pattern, FILE* file)
{
    puts("ERROR: writeDxf not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeDxf */
}

