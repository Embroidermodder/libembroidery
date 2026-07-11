/**
 * @file sierra.c
 *
 * Sierra Expanded Embroidery Format (.eys)
 * Stitch Only Format.
 * Smoothie G-Code Embroidery Format (.fxy)?
 */

#include "embroidery.h"

int8_t readEys(EmbPattern *pattern, FILE *file)
{
    puts("ERROR: readEys and not been finished.");
    if (emb_verbose > 0) {
        printf("pattern = %p\n", pattern);
        printf("file = %p\n", file);
    }
    return 0;                   /*TODO: finish readEys */
}

int8_t writeEys(EmbPattern *pattern, FILE *file)
{
    puts("ERROR: writeEys and not been finished.");
    if (emb_verbose > 0) {
        printf("pattern = %p\n", pattern);
        printf("file = %p\n", file);
    }
    return 0;                   /*TODO: finish writeEys */
}

