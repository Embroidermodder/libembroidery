/*
 * VP3 FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
 *
\subsection drawing-dxf-format Drawing Exchange Format (.dxf)
\addindex dxf
\addindex AutoCAD
\addindex AutoDesk

Graphics format for drawing files designed and used by AudoDesk for their AutoCAD program. \cite{dxf_reference

 */

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

char
readDxf(EmbPattern* pattern, FILE* file)
{
    char dxfVersion[255];
    char section[255];
    char tableName[255];
    char layerName[255];
    char entityType[255];
    /*char layerColorHash[100][8]; */ /* hash <layerName, EmbColor> */

    int eof = 0; /* End Of File */

    char buff[255];
    EmbVector prev, pos, first;
    EmbReal bulge = 0.0;
    char firstStitch = 1;
    char bulgeFlag = 0;
    int fileLength = 0;
    first.x = 0.0;
    first.y = 0.0;
    pos.x = 0.0;
    pos.y = 0.0;
    prev.x = 0.0;
    prev.y = 0.0;
   
    puts("overriding dxf. Unimplemented for now.");
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0;

    fseek(file, 0L, SEEK_END);

    fileLength = ftell(file);
    fseek(file, 0L, SEEK_SET);

    while (ftell(file) < fileLength) {
        readLine(file, buff);
        /*printf("%s\n", buff);*/
        if ( (!strcmp(buff, "HEADER"))   ||
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
        if ( (!strcmp(buff, "ARC"))        ||
            (!strcmp(buff, "CIRCLE"))     ||
            (!strcmp(buff, "ELLIPSE"))    ||
            (!strcmp(buff, "LINE"))       ||
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
                    EmbColor* co;

                    readLine(file, buff);
                    colorNum = atoi(buff);

                    colorNum = atoi(buff);
                    co = embColor_create(_dxfColorTable[colorNum][0], _dxfColorTable[colorNum][1], _dxfColorTable[colorNum][2]);
                    if (!co) { 
                        /* TODO: error allocating memory for EmbColor */  
                        return 0; 
                    }
                    printf("inserting:%s,%d,%d,%d\n", layerName, co->r, co->g, co->b);
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
                /* embPattern_changeColor(pattern, colorIndexMap[buff]); TODO: port to C */
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
                }
                else if (!strcmp(buff,"10")) /* X */
                {
                    readLine(file, buff);
                    pos.x = atof(buff);
                }
                else if (!strcmp(buff,"20")) /* Y */
                {
                    readLine(file, buff);
                    pos.y = atof(buff);

                    if (bulgeFlag) {
                        EmbArc arc;
                        bulgeFlag = 0;
                        arc.start = prev;
                        arc.end = pos;
                        if (!getArcDataFromBulge(bulge, &arc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {
                            /*TODO: error */
                            return 0;
                        }
                        if (firstStitch) {
                            /* embPattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        }
                        /* embPattern_addStitchAbs(pattern, x, y, ARC, 1); TODO: Add arcTo point to embPath pointList */
                    }
                    else {
                        /*if (firstStitch) embPattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        /*else            embPattern_addStitchAbs(pattern, x, y, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
                    }
                    prev = pos;
                    if (firstStitch) {
                        first = pos;
                        firstStitch = 0;
                    }
                }
                else if (!strcmp(buff,"0")) {
                    entityType[0] = 0;
                    firstStitch = 1;
                    if (bulgeFlag) {
                        EmbArc arc;
                        bulgeFlag = 0;
                        arc.start = prev;
                        arc.end = first;
                        if (!getArcDataFromBulge(bulge, &arc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {
                            /*TODO: error */
                            return 0;
                        }
                        prev = arc.start;
                        /* embPattern_addStitchAbs(pattern, prevX, prevY, ARC, 1); TODO: Add arcTo point to embPath pointList */
                    }
                    else
                    {
                        /* embPattern_addStitchAbs(pattern, firstX, firstY, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
                    }
                }
            } /* end LWPOLYLINE */
        } /* end ENTITIES section */
    } /* end while loop */


    /*
    EmbColor* testColor = 0;
    testColor = embHash_value(layerColorHash, "OMEGA");
    if (!testColor) printf("NULL POINTER!!!!!!!!!!!!!!\n");
    else printf("LAYERCOLOR: %d,%d,%d\n", testColor->r, testColor->g, testColor->b);
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
