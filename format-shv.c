#include "embroidery.h"
#include <string.h>

/*****************************************
 * SHV Colors
 ****************************************/
const int shvThreadCount = 42;
const EmbThread shvThreads[] = {
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 255 }, "Blue", "TODO:CATALOG_NUMBER" },
    { { 51, 204, 102 }, "Green", "TODO:CATALOG_NUMBER" },
    { { 255, 0, 0 }, "Red", "TODO:CATALOG_NUMBER" },
    { { 255, 0, 255 }, "Purple", "TODO:CATALOG_NUMBER" },
    { { 255, 255, 0 }, "Yellow", "TODO:CATALOG_NUMBER" },
    { { 127, 127, 127 }, "Grey", "TODO:CATALOG_NUMBER" },
    { { 51, 154, 255 }, "Light Blue", "TODO:CATALOG_NUMBER" },
    { { 0, 255, 0 }, "Light Green", "TODO:CATALOG_NUMBER" },
    { { 255, 127, 0 }, "Orange", "TODO:CATALOG_NUMBER" },
    { { 255, 160, 180 }, "Pink", "TODO:CATALOG_NUMBER" },
    { { 153, 75, 0 }, "Brown", "TODO:CATALOG_NUMBER" },
    { { 255, 255, 255 }, "White", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 255, 127, 127 }, "Light Red", "TODO:CATALOG_NUMBER" },
    { { 255, 127, 255 }, "Light Purple", "TODO:CATALOG_NUMBER" },
    { { 255, 255, 153 }, "Light Yellow", "TODO:CATALOG_NUMBER" },
    { { 192, 192, 192 }, "Light Grey", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 255, 165, 65 }, "Light Orange", "TODO:CATALOG_NUMBER" },
    { { 255, 204, 204 }, "Light Pink", "TODO:CATALOG_NUMBER" },
    { { 175, 90, 10 }, "Light Brown", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 127 }, "Dark Blue", "TODO:CATALOG_NUMBER" },
    { { 0, 127, 0 }, "Dark Green", "TODO:CATALOG_NUMBER" },
    { { 127, 0, 0 }, "Dark Red", "TODO:CATALOG_NUMBER" },
    { { 127, 0, 127 }, "Dark Purple", "TODO:CATALOG_NUMBER" },
    { { 200, 200, 0 }, "Dark Yellow", "TODO:CATALOG_NUMBER" },
    { { 60, 60, 60 }, "Dark Gray", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 0, 0, 0 }, "Black", "TODO:CATALOG_NUMBER" },
    { { 232, 63, 0 }, "Dark Orange", "TODO:CATALOG_NUMBER" },
    { { 255, 102, 122 }, "Dark Pink", "TODO:CATALOG_NUMBER" }
};

static char shvDecode(unsigned char inputByte)
{
    if (inputByte >= 0x80) {
        return (char)-((unsigned char)((~inputByte) + 1));
    }
    return ((char)inputByte);
}

static short shvDecodeShort(unsigned short inputByte)
{
    if (inputByte > 0x8000) {
        return (short)-((unsigned short)((~inputByte) + 1));
    }
    return ((short)inputByte);
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
static int readShv(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    int i;
    char inJump = 0;
    unsigned char fileNameLength, designWidth, designHeight;
    char halfDesignWidth, halfDesignHeight, halfDesignWidth2, halfDesignHeight2;
    char* headerText = "Embroidery disk created using software licensed from Viking Sewing Machines AB, Sweden";
    char dx = 0, dy = 0;
    char numberOfColors;
    unsigned short magicCode;
    int something;
    short left, top, right, bottom;
    char something2, numberOfSections, something3;
    int stitchesPerColor[256];
    int stitchesSinceChange = 0;
    int currColorIndex = 0;
    unsigned short sx, sy;

    embFile_seek(file, strlen(headerText), SEEK_SET);
    fileNameLength = binaryReadUInt8(file);
    embFile_seek(file, fileNameLength, SEEK_CUR);
    designWidth = binaryReadUInt8(file);
    designHeight = binaryReadUInt8(file);
    halfDesignWidth = binaryReadUInt8(file);
    halfDesignHeight = binaryReadUInt8(file);
    halfDesignWidth2 = binaryReadUInt8(file);
    halfDesignHeight2 = binaryReadUInt8(file);
    if ((designHeight % 2) == 1) {
        embFile_seek(file, ((designHeight + 1) * designWidth) / 2, SEEK_CUR);
    } else {
        embFile_seek(file, (designHeight * designWidth) / 2, SEEK_CUR);
    }
    numberOfColors = binaryReadUInt8(file);
    magicCode = binaryReadUInt16(file);
    binaryReadByte(file);
    something = binaryReadInt32(file);
    left = binaryReadInt16(file);
    top = binaryReadInt16(file);
    right = binaryReadInt16(file);
    bottom = binaryReadInt16(file);

    something2 = binaryReadByte(file);
    numberOfSections = binaryReadUInt8(file);
    something3 = binaryReadByte(file);

    for (i = 0; i < numberOfColors; i++) {
        unsigned int stitchCount, colorNumber;
        stitchCount = binaryReadUInt32BE(file);
        colorNumber = binaryReadUInt8(file);
        embPattern_addThread(pattern, shvThreads[colorNumber % 43]);
        stitchesPerColor[i] = stitchCount;
        embFile_seek(file, 9, SEEK_CUR);
    }

    embFile_seek(file, -2, SEEK_CUR);

    for (i = 0; !embFile_eof(file); i++) {
        unsigned char b0, b1;
        int flags;
        if (inJump) {
            flags = JUMP;
        } else {
            flags = NORMAL;
        }
        b0 = binaryReadUInt8(file);
        b1 = binaryReadUInt8(file);
        if (stitchesSinceChange >= stitchesPerColor[currColorIndex]) {
            embPattern_addStitchRel(pattern, 0, 0, STOP, 1);
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
                sx = binaryReadUInt8(file);
                sx = (unsigned short)(sx << 8 | binaryReadUInt8(file));
                sy = binaryReadUInt8(file);
                sy = (unsigned short)(sy << 8 | binaryReadUInt8(file));
                flags = TRIM;
                inJump = 1;
                embPattern_addStitchRel(pattern, shvDecodeShort(sx) / 10.0, shvDecodeShort(sy) / 10.0, flags, 1);
                continue;
            }
        }
        dx = shvDecode(b0);
        dy = shvDecode(b1);
        stitchesSinceChange++;
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    embFile_close(file);
    embPattern_end(pattern);
    embPattern_flipVertical(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
static int writeShv(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish writeShv */
}

