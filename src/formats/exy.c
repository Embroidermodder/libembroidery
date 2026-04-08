/* Eltac Embroidery Format (.exy)
 * Stitch Only Format.
 */

#include "embroidery.h"

int decode_exy_flags(unsigned char b2)
{
        int returnCode = 0;
        if (b2 == 0xF3) {
                return (END);
        }
        if ((b2 & 0xC3) == 0xC3) {
                return TRIM | STOP;
        }
        if (b2 & 0x80) {
                returnCode |= TRIM;
        }
        if (b2 & 0x40) {
                returnCode |= STOP;
        }
        return returnCode;
}

char readExy(EmbPattern *pattern, FILE *file)
{
        unsigned char b[3];

        fseek(file, 0x100, SEEK_SET);
        while (fread(b, 1, 3, file) == 3) {
                int flags, x, y;
                decode_tajima_ternary(b, &x, &y);
                flags = decode_exy_flags(b[2]);
                if (flags & END) {
                        embp_addStitchRel(pattern, 0, 0, END, 1);
                        break;
                }
                embp_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        }
        return 1;
}

char writeExy(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: writeExy has not been finished.");
        REPORT_PTR(pattern);
        REPORT_PTR(file);
        return 0;               /*TODO: finish writeExy */
}
