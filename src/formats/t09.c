/*
 * Pfaff Embroidery Format (.t09)
 * The Pfaff t09 format is stitch-only.
 */

#include "embroidery.h"

int8_t readT09(EmbPattern *pattern, FILE *file)
{
    uint8_t b[3];

    fseek(file, 0x0C, SEEK_SET);

    while (fread(b, 1, 3, file) == 3) {
        int stitchType = NORMAL;
        int b1 = b[0];
        int b2 = b[1];
        uint8_t commandByte = b[2];
        if (commandByte == 0x00) {
            break;
        }
        if (commandByte & 0x10) {
            stitchType = STOP;
        }
        if (commandByte & 0x20) {
            b1 = -b1;
        }
        if (commandByte & 0x40) {
            b2 = -b2;
        }
        emb_add_stitch(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    return 1;
}

int8_t writeT09(EmbPattern *pattern, FILE *file)
{
    int i;
    EmbVector pos;
    fpad(file, 0x00, 0x0C);

    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        uint8_t b[3];
        int dx, dy;
        EmbStitch st = pattern->stitch_list->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)emb_round(10.0 * (st.x - pos.x));
        dy = (int)emb_round(10.0 * (st.y - pos.y));
        pos.x += 0.1 * dx;
        pos.y += 0.1 * dy;

        b[0] = dx;
        b[1] = dy;
        b[2] = 0;
        if (st.flags & NORMAL) {
            /* guessing based on T01 here */
            b[2] |= 0x03;
        }
        /* inferred from readT09 */
        if (st.flags & STOP) {
            b[2] |= 0x10;
        }
        if (dx < 0) {
            b[0] = -dx;
            b[2] |= 0x20;
        }
        if (dy < 0) {
            b[0] = -dy;
            b[2] |= 0x40;
        }
        fwrite(b, 1, 3, file);
    }
    return 1;
}
