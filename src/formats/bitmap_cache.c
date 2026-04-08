/* The Bitmap Cache Embroidery Format (.bmc)
 *
 * We don't know much about this format. \todo Find a source.
 */

#include "embroidery.h"

char readBmc(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: readBmc is not supported.");
        printf("Cannot read %p %p\n", pattern, file);
        return 0;               /*TODO: finish readBmc */
}

char writeBmc(EmbPattern *pattern, FILE *file)
{
        puts("writeBmc is not implemented");
        printf("Cannot write %p %p\n", pattern, file);
        return 0;               /*TODO: finish writeBmc */
}
