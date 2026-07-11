/* Fortron Embroidery Format (.fxy)
 * Stitch Only Format.
 */

#include "embroidery.h"

int8_t readFxy(EmbPattern *pattern, FILE *file)
{
    /* TODO: review for combining code. This line appears
       to be the only difference from the GT format. */
    fseek(file, 0x100, SEEK_SET);

    while (!feof(file)) {
        int stitchType = NORMAL;
        int b1 = fgetc(file);
        int b2 = fgetc(file);
        uint8_t commandByte = (uint8_t) fgetc(file);

        if (commandByte == 0x91) {
            emb_add_stitch(pattern, 0, 0, END, 1);
            break;
        }
        if ((commandByte & 0x01) == 0x01)
            stitchType = TRIM;
        if ((commandByte & 0x02) == 0x02)
            stitchType = STOP;
        if ((commandByte & 0x20) == 0x20)
            b1 = -b1;
        if ((commandByte & 0x40) == 0x40)
            b2 = -b2;
        emb_add_stitch(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    return 1;
}

int8_t writeFxy(EmbPattern *pattern, FILE *file)
{
    puts("Overridden, defaulting to dst.");
    printf("%p %p\n", pattern, file);
    return 0;                   /*TODO: finish writeFxy */
}


