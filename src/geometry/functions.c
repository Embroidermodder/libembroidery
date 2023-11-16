/*
 * BASIC FUNCTIONS
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../embroidery.h"

/* round is C99 and we're committed to C90 so here's a replacement.
 */
int
emb_round(EmbReal x)
{
    EmbReal y = floor(x);
    if (fabs(x-y) > 0.5) {
        return (int)ceil(x);
    }
    return (int)y;
}

EmbReal
radians(EmbReal degree)
{
    return degree*embConstantPi/180.0;
}

EmbReal
degrees(EmbReal radian)
{
    return radian*180.0/embConstantPi;
}
