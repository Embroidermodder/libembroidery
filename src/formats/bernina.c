/* The Bernina Embroidery Format (.art)
 *
 * We don't know much about this format. \todo Find a source.
 */

#include "embroidery.h"

char readArt(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: readArt is not supported yet.");
        printf("Cannot read %p %p\n", pattern, file);
        return 0;
}

char writeArt(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: writeArt is not supported yet.");
        printf("Cannot write %p %p\n", pattern, file);
        return 0;
}
