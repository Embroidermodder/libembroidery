/*
 * Husqvarna Viking Embroidery Format (.shv)
 * The Husqvarna Viking shv format is stitch-only.
 */

#include <string.h>

#include "embroidery.h"

int8_t shvDecode(uint8_t inputByte)
{
    if (inputByte >= 0x80) {
        return (char)-((uint8_t) ((~inputByte) + 1));
    }
    return ((char)inputByte);
}

short shvDecodeShort(uint16_t inputByte)
{
    if (inputByte > 0x8000) {
        return (int16_t) - ((uint16_t) ((~inputByte) + 1));
    }
    return ((int16_t) inputByte);
}

int8_t readShv(EmbPattern *pattern, FILE *file)
{
    int i;
    int8_t inJump = 0;
    uint8_t fileNameLength, designWidth, designHeight;
    int8_t halfDesignWidth, halfDesignHeight, halfDesignWidth2,
        halfDesignHeight2;
    int8_t *headerText =
        "Embroidery disk created using software licensed from Viking Sewing Machines AB, Sweden";
    int8_t dx = 0, dy = 0;
    int8_t numberOfColors;
    uint16_t magicCode;
    int something;
    short left, top, right, bottom;
    int8_t something2, numberOfSections, something3;
    int stitchesPerColor[256];
    int stitchesSinceChange = 0;
    int currColorIndex = 0;
    uint16_t sx, sy;

    if (!check_header_present(file, 25)) {
        return 0;
    }

    fseek(file, strlen(headerText), SEEK_SET);
    fileNameLength = fgetc(file);
    fseek(file, fileNameLength, SEEK_CUR);
    designWidth = fgetc(file);
    designHeight = fgetc(file);
    halfDesignWidth = emb_read_i8(file);
    halfDesignHeight = emb_read_i8(file);
    halfDesignWidth2 = emb_read_i8(file);
    halfDesignHeight2 = emb_read_i8(file);
    if ((designHeight % 2) == 1) {
        fseek(file, ((designHeight + 1) * designWidth) / 2, SEEK_CUR);
    } else {
        fseek(file, (designHeight * designWidth) / 2, SEEK_CUR);
    }
    numberOfColors = fgetc(file);
    magicCode = emb_read_u16(file);
    fseek(file, 1, SEEK_CUR);
    something = emb_read_i32(file);
    left = emb_read_i16(file);
    top = emb_read_u16(file);
    right = emb_read_u16(file);
    bottom = emb_read_u16(file);
    something2 = emb_read_i8(file);
    numberOfSections = emb_read_i8(file);
    something3 = emb_read_i8(file);
    for (i = 0; i < numberOfColors; i++) {
        uint32_t stitchCount, colorNumber;
        stitchCount = emb_read_i32be(file);
        colorNumber = fgetc(file);
        emb_add_thread(pattern, shv_colors[colorNumber % 43]);
        stitchesPerColor[i] = stitchCount;
        fseek(file, 9, SEEK_CUR);
    }

    fseek(file, -2, SEEK_CUR);

    for (i = 0; !feof(file); i++) {
        uint8_t b0, b1;
        int flags;
        flags = NORMAL;
        if (inJump) {
            flags = JUMP;
        }
        b0 = fgetc(file);
        b1 = fgetc(file);
        if (stitchesSinceChange >= stitchesPerColor[currColorIndex]) {
            emb_add_stitch(pattern, 0, 0, STOP, 1);
            currColorIndex++;
            stitchesSinceChange = 0;
        }
        if (b0 == 0x80) {
            stitchesSinceChange++;
            if (b1 == 3) {
                continue;
            } else if (b1 == 0x02) {
                inJump = 0;
                continue;
            } else if (b1 == 0x01) {
                stitchesSinceChange += 2;
                sx = fgetc(file);
                sx = (uint16_t) (sx << 8 | fgetc(file));
                sy = fgetc(file);
                sy = (uint16_t) (sy << 8 | fgetc(file));
                flags = TRIM;
                inJump = 1;
                emb_add_stitch(pattern,
                                  shvDecodeShort(sx) / 10.0,
                                  shvDecodeShort(sy) / 10.0, flags, 1);
                continue;
            }
        }
        dx = shvDecode(b0);
        dy = shvDecode(b1);
        stitchesSinceChange++;
        emb_add_stitch(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    emb_flip_vertical(pattern);

    return 1;
}

int8_t writeShv(EmbPattern *pattern, FILE *file)
{
    puts("writeShv not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void *)pattern, (void *)file);
    }
    return 0;                   /*TODO: finish writeShv */
}

