/* Embird Embroidery Format (.edr)
 * Stitch Only Format
 */

#include "embroidery.h"

int8_t readRgb(EmbPattern *pattern, FILE *file);
int8_t writeRgb(EmbPattern *pattern, FILE *file);

int8_t readEdr(EmbPattern *pattern, FILE *file)
{
    /* appears identical to readRgb, so backends to that */
    return readRgb(pattern, file);
}

int8_t writeEdr(EmbPattern *pattern, FILE *file)
{
    /* appears identical to writeRgb, so backends to that */
    return writeRgb(pattern, file);
}

