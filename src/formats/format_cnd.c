/*
 * CND FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
 * \file format_cnd.c The Melco Embroidery Format (.cnd)
 * \addindex cnd
 * \addindex Melco
 *
 * The Melco cnd format is a stitch-only format.
 *
 * We don't know much about this format.
 *
 * \todo Find a source.
 */

char
readCnd(EmbPattern* pattern, FILE* file)
{
    puts("readCnd is not implemented");
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readCnd */
}

char
writeCnd(EmbPattern* pattern, FILE* file)
{
    puts("writeCnd is not implemented");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeCnd */
}
