/**
 * @file dsb.c
 */

#include "embroidery.h"

int8_t writeDst(EmbPattern *pattern, FILE *file);

const int shvThreadCount = 42;

/* The Barudan Embroidery Format (.dsb)
 *
 * Stitch Only Format.
 * [X] Basic Read Support
 * [o] Basic Write Support
 * [o] Well Tested Read
 * [o] Well Tested Write
 */
int8_t readDsb(EmbPattern *pattern, FILE *file)
{
    int8_t header[512 + 1];
    uint8_t buffer[3];

    if (fread(header, 1, 512, file) != 512) {
        puts("ERROR");
        return 0;
    }

    while (fread(buffer, 1, 3, file) == 3) {
        int x, y;
        uint8_t ctrl;
        int stitchType = NORMAL;

        ctrl = buffer[0];
        y = buffer[1];
        x = buffer[2];
        if (ctrl & 0x01)
            stitchType = TRIM;
        if (ctrl & 0x20)
            x = -x;
        if (ctrl & 0x40)
            y = -y;
        /* ctrl & 0x02 - Speed change? *//* TODO: review this line */
        /* ctrl & 0x04 - Clutch? *//* TODO: review this line */
        if ((ctrl & 0x05) == 0x05) {
            stitchType = STOP;
        }
        if (ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87) {
            emb_add_stitch(pattern, 0, 0, END, 1);
            break;
        }
        emb_add_stitch(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }
    return 1;
}

int8_t writeDsb(EmbPattern *pattern, FILE *file)
{
    puts("writeDsb is not implemented");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0;                   /*TODO: finish writeDsb */
}

