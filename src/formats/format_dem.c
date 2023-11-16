/*
 * DEM FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
 * \file format_dem.c The Melco Embroidery Format (.dem)
 * \addindex dem
 * \addindex Melco
 * 
 * Stitch Only Format
 */

char
readDem(EmbPattern* pattern, FILE* file)
{
    puts("readDem is not implemented.");
    puts("Overridden, defaulting to dst.");
    return readDst(pattern, file); /*TODO: finish readDem */
}

char
writeDem(EmbPattern* pattern, FILE* file)
{
    puts("writeDem is not implemented.");
    puts("Overridden, defaulting to dst.");
    return writeDst(pattern, file); /*TODO: finish writeDem */
}
