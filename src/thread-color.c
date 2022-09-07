/*
 * This file is part of libembroidery.
 *
 * Copyright 2018-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>

#include "embroidery.h"
#include <string.h>

const unsigned char _dxfColorTable[][3] = {{   0,   0,   0 }};
const EmbThread husThreads[] = {{{   0,   0,   0 }, "END", "END"}};
const EmbThread jefThreads[] = {{{   0,   0,   0 }, "END", "END"}};
const EmbThread shvThreads[] = {{{   0,   0,   0 }, "END", "END"}};
const EmbThread pcmThreads[] = {{{   0,   0,   0 }, "END", "END"}};
const EmbThread pecThreads[] = {{{   0,   0,   0 }, "END", "END"}};
const int shvThreadCount = 42;
const int pecThreadCount = 65;

thread_color *brand_codes[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

const char *brand_codes_files[] = {
    "arc_polyester_colors.csv",          /* 0 */
    "arc_rayon_colors.csv",              /* 1 */
    "coats_and_clark_rayon_colors.csv",  /* 2 */
    "exquisite_polyester_colors.csv",    /* 3 */
    "fufu_Polyester_colors.csv",         /* 4 */
    "fufu_Rayon_colors.csv",             /* 5 */
    "Hemingworth_Polyester_colors.csv",  /* 6 */
    "Isacord_Polyester_colors.csv",      /* 7 */
    "Isafil_Rayon_colors.csv",           /* 8 */
    "Marathon_Polyester_colors.csv",     /* 9 */
    "Marathon_Rayon_colors.csv",         /* 10 */
    "Madeira_Polyester_colors.csv",      /* 11 */
    "Madeira_Rayon_colors.csv",          /* 12 */
    "Metro_Polyester_colors.csv",        /* 13 */
    "Pantone_colors.csv",                /* 14 */
    "RobisonAnton_Polyester_colors.csv", /* 15 */
    "RobisonAnton_Rayon_colors.csv",     /* 16 */
    "Sigma_Polyester_colors.csv",        /* 17 */
    "Sulky_Rayon_colors.csv",            /* 18 */
    "ThreadArt_Rayon_colors.csv",        /* 19 */
    "ThreadArt_Polyester_colors.csv",    /* 20 */
    "ThreaDelight_Polyester_colors.csv", /* 21 */
    "Z102_Isacord_Polyester_colors.csv", /* 22 */
    "svg_color_colors.csv"               /* 23 */
};

int threadColor(const char *name, int brand)
{
    int i;
    for (i = 0; brand_codes[brand][i].manufacturer_code >= 0; i++) {
        if (!strcmp(brand_codes[brand][i].name, name)) {
            return brand_codes[brand][i].hex_code;
        }
    }
    return -1;
}

int threadColorNum(unsigned int color, int brand)
{
    int i;
    for (i = 0; brand_codes[brand][i].manufacturer_code >= 0; i++) {
        if (brand_codes[brand][i].hex_code == color) {
            return brand_codes[brand][i].manufacturer_code;
        }
    }

    return -1;
}

const char* threadColorName(unsigned int color, int brand)
{
    int i;
    for (i = 0; brand_codes[brand][i].manufacturer_code >= 0; i++) {
        if (brand_codes[brand][i].hex_code == color) {
            return brand_codes[brand][i].name;
        }
    }

    return "COLOR NOT FOUND";
}

