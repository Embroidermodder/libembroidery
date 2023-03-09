/*
 * COL FORMAT
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

char
readCol(EmbPattern* pattern, FILE* file)
{
    int numberOfColors, i;
    int num, blue, green, red;
    EmbThread t;
    char line[30];

    pattern->thread_list->count = 0;

    emb_readline(file, line, 30);
    numberOfColors = atoi(line);
    if (numberOfColors < 1) {
        printf("ERROR: Number of colors is zero.");
        return 0;
    }
    for (i = 0; i < numberOfColors; i++) {
        emb_readline(file, line, 30);
        if (strlen(line) < 1) {
            printf("ERROR: Empty line in col file.");
            return 0;
        }
        /* TODO: replace all scanf code */
        if (sscanf(line,"%d,%d,%d,%d", &num, &blue, &green, &red) != 4) {
            break;
        }
        t.color.r = (unsigned char)red;
        t.color.g = (unsigned char)green;
        t.color.b = (unsigned char)blue;
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        embPattern_addThread(pattern, t);
    }
    return 1;
}

char
writeCol(EmbPattern* pattern, FILE* file)
{
    int i;

    fprintf(file, "%d\r\n", pattern->thread_list->count);
    for (i = 0; i < pattern->thread_list->count; i++) {
        EmbColor c;
        c = pattern->thread_list->thread[i].color;
        fprintf(file, "%d,%d,%d,%d\r\n", i, (int)c.r, (int)c.g, (int)c.b);
    }
    return 1;
}
