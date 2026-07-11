/**
 * @file bitmap_cache.c
 *
 * The Bitmap Cache Embroidery Format (.bmc)
 *
 * We don't know much about this format. \todo Find a source.
 */

#include "embroidery.h"

int8_t readBmc(EmbPattern *pattern, FILE *file)
{
    puts("ERROR: readBmc is not supported.");
    printf("Cannot read %p %p\n", pattern, file);
    return 0;                   /*TODO: finish readBmc */
}

int8_t writeBmc(EmbPattern *pattern, FILE *file)
{
    puts("writeBmc is not implemented");
    printf("Cannot write %p %p\n", pattern, file);
    return 0;                   /*TODO: finish writeBmc */
}
