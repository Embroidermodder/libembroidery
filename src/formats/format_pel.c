/*
 * PEL FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"

/**

\subsection Brother Embroidery Format (.pel)
\addindex pel
\addindex Brother

The Brother pel format is stitch-only.
 */

/* ---------------------------------------------------------------- */
/* format pel */

char
readPel(EmbPattern *pattern, FILE *file)
{
    puts("ERROR: readPel is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish readPel */
}

char
writePel(EmbPattern *pattern, FILE *file)
{
    puts("ERROR: writePel is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writePel */
}
