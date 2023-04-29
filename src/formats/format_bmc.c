/*
 * BMC FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
 * \file format_bmc.c The Bitmap Cache Embroidery Format (.bmc)
 * \addindex bmc
 * \addindex Bitmap Cache
 * 
 * We don't know much about this format. \todo Find a source.
 */

char
readBmc(EmbPattern* pattern, FILE* file)
{
    puts("readBmc is not implemented");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish readBmc */
}

char
writeBmc(EmbPattern* pattern, FILE* file)
{
    puts("writeBmc is not implemented");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeBmc */
}

