/*
 * ELLIPSE GEOMETRY
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
EmbEllipse
embEllipse_init(void)
{
    EmbEllipse ellipse;
    ellipse.center.x = 0.0;
    ellipse.center.y = 0.0;
    ellipse.radius.x = 1.0;
    ellipse.radius.y = 2.0;
    ellipse.rotation = 0.0;
    ellipse.lineType = 0;
    ellipse.color = black_thread.color;
    return ellipse;
}

/*
 */
EmbReal
embEllipse_area(EmbEllipse ellipse)
{

}

/*
 */
EmbReal
embEllipse_perimeter(EmbEllipse ellipse)
{

}


EmbReal
embEllipse_diameterX(EmbEllipse ellipse)
{
    return ellipse.radius.x * 2.0;
}

EmbReal
embEllipse_diameterY(EmbEllipse ellipse)
{
    return ellipse.radius.y * 2.0;
}

EmbReal
embEllipse_width(EmbEllipse ellipse)
{
    return ellipse.radius.x * 2.0;
}

EmbReal
embEllipse_height(EmbEllipse ellipse)
{
    return ellipse.radius.y * 2.0;
}
