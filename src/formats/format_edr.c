/*
 * VP3 FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

char
readEdr(EmbPattern* pattern, FILE* file)
{
    /* appears identical to readRgb, so backends to that */
    return readRgb(pattern, file);
}

char
writeEdr(EmbPattern* pattern, FILE* file)
{
    /* appears identical to writeRgb, so backends to that */
    return writeRgb(pattern, file);
}
