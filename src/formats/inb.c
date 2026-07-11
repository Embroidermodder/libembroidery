/*
 * Inbro Embroidery Format (.inb)
 * Stitch Only Format.
 */

#include "embroidery.h"

int8_t readInb(EmbPattern *pattern, FILE *file)
{
    /* TODO: determine what this represents */
    uint8_t fileDescription[8], nullVal, bytesUnknown[300];
    int stitchCount, x, y, i, fileLength;
    short width, height, colorCount, unknown3, unknown2,
        nullbyte, left, right, top, bottom, imageWidth, imageHeight;

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fread(fileDescription, 1, 8, file); /* TODO: check return value */
    nullVal = emb_read_u8(file);
    fgetc(file);
    fgetc(file);
    stitchCount = emb_read_i32(file);
    width = emb_read_i16(file);
    height = emb_read_i16(file);
    colorCount = emb_read_i16(file);
    unknown3 = emb_read_i16(file);
    unknown2 = emb_read_i16(file);
    imageWidth = emb_read_i16(file);
    imageHeight = emb_read_i16(file);
    fread(bytesUnknown, 1, 300, file);      /* TODO: check return value */
    nullbyte = emb_read_i16(file);
    left = emb_read_i16(file);
    right = emb_read_i16(file);
    top = emb_read_i16(file);
    bottom = emb_read_i16(file);
    fseek(file, 0x2000, SEEK_SET);
    /* Calculate stitch count since header has been seen to be blank */
    stitchCount = (int)((fileLength - 0x2000) / 3);
    for (i = 0; i < stitchCount; i++) {
        uint8_t type;
        int stitch = NORMAL;
        x = (char)fgetc(file);
        y = (char)fgetc(file);
        type = (char)fgetc(file);
        if ((type & 0x40) > 0)
            x = -x;
        if ((type & 0x10) > 0)
            y = -y;
        if ((type & 1) > 0)
            stitch = STOP;
        if ((type & 2) > 0)
            stitch = TRIM;
        emb_add_stitch(pattern, x / 10.0, y / 10.0, stitch, 1);
    }
    emb_flip_vertical(pattern);

    return 1;
}

int8_t writeInb(EmbPattern *pattern, FILE *file)
{
    puts("ERROR: writeInb not implemented.");
    if (emb_verbose > 0) {
        printf("writeInb called with %p %p\n", pattern, file);
    }
    return 0;               /*TODO: finish writeInb */
}

