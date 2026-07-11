/*
 * Sunstar Embroidery Format (.sst)
 * The Sunstar sst format is stitch-only.
 */

#include "embroidery.h"

int8_t readSst(EmbPattern *pattern, FILE *file)
{
    int fileLength;

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0xA0, SEEK_SET);        /* skip the all zero header */
    while (ftell(file) < fileLength) {
        int stitchType = NORMAL;

        int b1 = fgetc(file);
        int b2 = fgetc(file);
        uint8_t commandByte = (uint8_t) fgetc(file);

        if (commandByte == 0x04) {
            emb_add_stitch(pattern, 0, 0, END, 1);
            break;
        }

        if ((commandByte & 0x01) == 0x01)
            stitchType = STOP;
        if ((commandByte & 0x02) == 0x02)
            stitchType = JUMP;
        if ((commandByte & 0x10) != 0x10)
            b2 = -b2;
        if ((commandByte & 0x40) == 0x40)
            b1 = -b1;
        emb_add_stitch(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }

    return 1;                   /*TODO: finish readSst */
}

int8_t writeSst(EmbPattern *pattern, FILE *file)
{
    int i;
    int head_length = 0xA0;
    for (i = 0; i < head_length; i++) {
        fprintf(file, " ");
    }
    for (i = 0; i < pattern->stitch_list->count; i++) {
        printf(".");
    }
    return 0;                   /*TODO: finish writeSst */
}
