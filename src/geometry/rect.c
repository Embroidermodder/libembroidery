/*
 * RECT GEOMETRY
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../embroidery.h"

/*
 */
EmbRect
embRect_init(void)
{
    EmbRect rect;
    rect.left = 0.0;
    rect.top = 0.0;
    rect.right = 1.0;
    rect.bottom = 1.0;
    return rect;
}

EmbReal
embRect_area(EmbRect rect)
{
    return (rect.bottom - rect.top) * (rect.right - rect.left);
}
