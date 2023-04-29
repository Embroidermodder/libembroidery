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
 * Smoothie G-Code
 *
 * Main Reference:
 *     Machinery's Handbook Guide
 *     A Guide to Tables, Formulas, & More in the 31st Edition
 *     by John Milton Amiss, Franklin D. Jones and Henry Ryffel
 */

char
readGc(EmbPattern* pattern, FILE* file) {
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readGc */
}

char
writeGc(EmbPattern* pattern, FILE* file) {
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeGc */
}
