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
\subsection Brother Embroidery Format (.pem)
\addindex pem
\addindex Brother

The Brother pem format is stitch-only.
 */

/* ---------------------------------------------------------------- */
/* format pem */

char
readPem(EmbPattern *pattern, FILE *file)
{
    puts("ERROR: readPem is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish ReadPem */
}

char
writePem(EmbPattern *pattern, FILE *file)
{
    puts("ERROR: writePem is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writePem */
}
