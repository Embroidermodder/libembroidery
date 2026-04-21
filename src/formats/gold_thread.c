/**
 * @file gt.c
 *
 * Gold Thread Embroidery Format (.gt)
 * Stitch Only Format.
 */

#include "embroidery.h"

char readGt(EmbPattern *pattern, FILE *file)
{
        /* TODO: review for combining code. This line appears
           to be the only difference from the FXY format. */
        fseek(file, 0x200, SEEK_SET);

        while (!feof(file)) {
                int stitchType = NORMAL;
                int b1 = fgetc(file);
                int b2 = fgetc(file);
                unsigned char commandByte = (unsigned char)fgetc(file);

                if (commandByte == 0x91) {
                        embp_addStitchRel(pattern, 0, 0, END, 1);
                        break;
                }
                if ((commandByte & 0x01) == 0x01) {
                        stitchType = TRIM;
                }
                if ((commandByte & 0x02) == 0x02) {
                        stitchType = STOP;
                }
                if ((commandByte & 0x20) == 0x20) {
                        b1 = -b1;
                }
                if ((commandByte & 0x40) == 0x40) {
                        b2 = -b2;
                }
                embp_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
        }
        return 1;
}

char writeGt(EmbPattern *pattern, FILE *file)
{
        puts("ERROR: gt not supported in write mode.");
        printf("%p %p\n", pattern, file);
        return 0;               /*TODO: finish writeGt */
}
