/*
 * 100 FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
 *
\subsection janome-jef-format Janome Embroidery Format (.jef)
\addindex jef
\addindex Janome

Stitch Only Format.
 */

int
jefGetHoopSize(int width, int height)
{
    if (width < 50 && height < 50) {
        return HOOP_50X50;
    }
    if (width < 110 && height < 110) {
        return HOOP_110X110;
    }
    if (width < 140 && height < 200) {
        return HOOP_140X200;
    }
    return ((int) HOOP_110X110);
}

char
jefDecode(unsigned char inputByte) {
    if (inputByte >= 0x80) {
        return (char) ((-~inputByte) - 1);
    }
    return ((char) inputByte);
}

void
jefSetHoopFromId(EmbPattern* pattern, int hoopCode)
{
    if (!pattern) {
        printf("ERROR: format-jef.c jefSetHoopFromId(), pattern argument is null\n");
        return;
    }
    switch (hoopCode) {
        case HOOP_126X110:
            pattern->hoop_height = 126.0;
            pattern->hoop_width = 110.0;
            break;
        case HOOP_50X50:
            pattern->hoop_height = 50.0;
            pattern->hoop_width = 50.0;
            break;
        case HOOP_110X110:
            pattern->hoop_height = 110.0;
            pattern->hoop_width = 110.0;
            break;
        case HOOP_140X200:
            pattern->hoop_height = 140.0;
            pattern->hoop_width = 200.0;
            break;
        case HOOP_230X200:
            pattern->hoop_height = 230.0;
            pattern->hoop_width = 200.0;
            break;
    }
}

struct hoop_padding
{
    int left;
    int right;
    int top;
    int bottom;
};

void
read_hoop(FILE *file, struct hoop_padding *hoop, char *label)
{
    if (emb_verbose>1) {
        printf("%s\n", label);
    }
    embInt_read(file, "    left", &(hoop->left), EMB_INT32_LITTLE);
    embInt_read(file, "    top", &(hoop->top), EMB_INT32_LITTLE);
    embInt_read(file, "    right", &(hoop->right), EMB_INT32_LITTLE);
    embInt_read(file, "    bottom", &(hoop->bottom), EMB_INT32_LITTLE);
}

char
readJef(EmbPattern* pattern, FILE* file) {
    int stitchOffset, formatFlags, numberOfColors, numberOfStitchs;
    int hoopSize, i, stitchCount;
    struct hoop_padding bounds, rectFrom110x110;
    struct hoop_padding rectFrom50x50, rectFrom200x140, rect_from_custom;
    char date[8], time[8];

    embInt_read(file, "stitchOffset", &stitchOffset, EMB_INT32_LITTLE);
    embInt_read(file, "formatFlags", &formatFlags, EMB_INT32_LITTLE); /* TODO: find out what this means */

    fread((unsigned char*) date, 1, 8, file); /* TODO: check return value */
    fread((unsigned char*) time, 1, 8, file); /* TODO: check return value */
    embInt_read(file, "numberOfColors", &numberOfColors, EMB_INT32_LITTLE);
    embInt_read(file, "numberOfStitchs", &numberOfStitchs, EMB_INT32_LITTLE);
    embInt_read(file, "hoopSize", &hoopSize, EMB_INT32_LITTLE);
    jefSetHoopFromId(pattern, hoopSize);
    if (numberOfStitchs > MAX_STITCHES) {
        numberOfStitchs = MAX_STITCHES;
        puts("ERROR: this file is corrupted or has too many stitches.");
        return 0;
    }
    if (emb_verbose>1) {
        printf("format flags = %d\n", formatFlags);
        printf("number of colors = %d\n", numberOfColors);
        printf("number of stitches = %d\n", numberOfStitchs);
    }

    read_hoop(file, &bounds, "bounds");
    read_hoop(file, &rectFrom110x110, "rectFrom110x110");
    read_hoop(file, &rectFrom50x50, "rectFrom50x50");
    read_hoop(file, &rectFrom200x140, "rectFrom200x140");
    read_hoop(file, &rect_from_custom, "rect_from_custom");

    for (i = 0; i < numberOfColors; i++) {
        int thread_num;
        embInt_read(file, "thread_num", &thread_num, EMB_INT32_LITTLE);
        embPattern_addThread(pattern, jefThreads[thread_num % 79]);
    }
    fseek(file, stitchOffset, SEEK_SET);
    stitchCount = 0;
    while (stitchCount < numberOfStitchs + 100) {
        unsigned char b[2];
        char dx = 0, dy = 0;
        int flags = NORMAL;
        if (fread(b, 1, 2, file) != 2) {
            break;
        }
        
        if (b[0] == 0x80) {
            if (b[1] & 1) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                flags = STOP;
            }
            else if ((b[1] == 2) || (b[1] == 4) || b[1] == 6) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                flags = TRIM;
            }
            else if (b[1] == 0x10) {
                embPattern_addStitchRel(pattern, 0.0, 0.0, END, 1);
                break;
            }
        }
        dx = jefDecode(b[0]);
        dy = jefDecode(b[1]);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
        stitchCount++;
    }
    return 1;
}

void
jefEncode(unsigned char* b, char dx, char dy, int flags) {
    if (!b) {
        printf("ERROR: format-jef.c expEncode(), b argument is null\n");
        return;
    }
    if (flags == STOP) {
        b[0] = 0x80;
        b[1] = 1;
        b[2] = dx;
        b[3] = dy;
    } else if (flags == END) {
        b[0] = 0x80;
        b[1] = 0x10;
        b[2] = 0;
        b[3] = 0;
    } else if (flags == TRIM || flags == JUMP) {
        b[0] = 0x80;
        b[1] = 2;
        b[2] = dx;
        b[3] = dy;
    } else {
        b[0] = dx;
        b[1] = dy;
    }
}

char
writeJef(EmbPattern* pattern, FILE* file)
{
    int colorlistSize, minColors, designWidth, designHeight, i;
    EmbRect boundingRect;
    EmbTime time;
    EmbReal width, height;
    int data;
    EmbVector pos;

    embPattern_correctForMaxStitchLength(pattern, 12.7, 12.7);

    colorlistSize = pattern->thread_list->count;
    minColors = EMB_MAX(colorlistSize, 6);
    binaryWriteInt(file, 0x74 + (minColors * 4));
    binaryWriteInt(file, 0x0A);

    embTime_initNow(&time);

    fprintf(file, "%04d%02d%02d%02d%02d%02d", (int)(time.year + 1900),
            (int)(time.month + 1), (int)(time.day), (int)(time.hour),
            (int)(time.minute), (int)(time.second));
    fpad(file, 0, 2);
    embInt_write(file, ".", &(pattern->thread_list->count), EMB_INT32_LITTLE);
    data = pattern->stitch_list->count + EMB_MAX(0, (6 - colorlistSize) * 2) + 1;
    embInt_write(file, ".", &data, EMB_INT32_LITTLE);

    boundingRect = embPattern_calcBoundingBox(pattern);
    width = boundingRect.right - boundingRect.left;
    height = boundingRect.bottom - boundingRect.top;
    designWidth = (int)(width * 10.0);
    designHeight = (int)(height * 10.0);

    binaryWriteInt(file, jefGetHoopSize(designWidth, designHeight));

    /* Distance from center of Hoop */
    binaryWriteInt(file, (int) (designWidth / 2));  /* left */
    binaryWriteInt(file, (int) (designHeight / 2)); /* top */
    binaryWriteInt(file, (int) (designWidth / 2));  /* right */
    binaryWriteInt(file, (int) (designHeight / 2)); /* bottom */

    /* Distance from default 110 x 110 Hoop */
    if (EMB_MIN(550 - designWidth / 2, 550 - designHeight / 2) >= 0) {
        binaryWriteInt(file, EMB_MAX(-1, 550 - designWidth / 2));  /* left */
        binaryWriteInt(file, EMB_MAX(-1, 550 - designHeight / 2)); /* top */
        binaryWriteInt(file, EMB_MAX(-1, 550 - designWidth / 2));  /* right */
        binaryWriteInt(file, EMB_MAX(-1, 550 - designHeight / 2)); /* bottom */
    } else {
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
    }

    /* Distance from default 50 x 50 Hoop */
    if (EMB_MIN(250 - designWidth / 2, 250 - designHeight / 2) >= 0) {
        binaryWriteInt(file, (int) EMB_MAX(-1, 250 - designWidth / 2));  /* left */
        binaryWriteInt(file, (int) EMB_MAX(-1, 250 - designHeight / 2)); /* top */
        binaryWriteInt(file, (int) EMB_MAX(-1, 250 - designWidth / 2));  /* right */
        binaryWriteInt(file, (int) EMB_MAX(-1, 250 - designHeight / 2)); /* bottom */
    } else {
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
    }

    /* Distance from default 140 x 200 Hoop */
    binaryWriteInt(file, (int) (700 - designWidth / 2));   /* left */
    binaryWriteInt(file, (int) (1000 - designHeight / 2)); /* top */
    binaryWriteInt(file, (int) (700 - designWidth / 2));   /* right */
    binaryWriteInt(file, (int) (1000 - designHeight / 2)); /* bottom */

    /* repeated Distance from default 140 x 200 Hoop */
    /* TODO: Actually should be distance to custom hoop */
    binaryWriteInt(file, (int) (630 - designWidth / 2));  /* left */
    binaryWriteInt(file, (int) (550 - designHeight / 2)); /* top */
    binaryWriteInt(file, (int) (630 - designWidth / 2));  /* right */
    binaryWriteInt(file, (int) (550 - designHeight / 2)); /* bottom */

    for (i = 0; i < pattern->thread_list->count; i++) {
        int j = embThread_findNearestThread(pattern->thread_list->thread[i].color, (EmbThread *)jefThreads, 79);
        binaryWriteInt(file, j);
    }

    for (i = 0; i < (minColors - colorlistSize); i++) {
        int a = 0x0D;
        binaryWriteInt(file, a);
    }

    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        unsigned char b[4];
        EmbStitch st;
        char dx, dy;
        b[0] = 0;
        b[1] = 0;
        b[2] = 0;
        b[3] = 0;
        st = pattern->stitch_list->stitch[i];
        dx = (char)emb_round(10.0*(st.x - pos.x));
        dy = (char)emb_round(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;
        jefEncode(b, dx, dy, st.flags);
        if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
            fwrite(b, 1, 4, file);
        } else {
            fwrite(b, 1, 2, file);
        }
    }
    return 1;
}

