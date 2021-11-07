#include "embroidery.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int pecThreadCount = 65;
const EmbThread pecThreads[] = {
{{  0,   0,   0}, "Unknown",         ""}, /* Index  0 */
{{ 14,  31, 124}, "Prussian Blue",   ""}, /* Index  1 */
{{ 10,  85, 163}, "Blue",            ""}, /* Index  2 */
{{  0, 135, 119}, "Teal Green",      ""}, /* Index  3 */ /* TODO: Verify RGB value is correct */
{{ 75, 107, 175}, "Cornflower Blue", ""}, /* Index  4 */
{{237,  23,  31}, "Red",             ""}, /* Index  5 */
{{209,  92,   0}, "Reddish Brown",   ""}, /* Index  6 */
{{145,  54, 151}, "Magenta",         ""}, /* Index  7 */
{{228, 154, 203}, "Light Lilac",     ""}, /* Index  8 */
{{145,  95, 172}, "Lilac",           ""}, /* Index  9 */
{{158, 214, 125}, "Mint Green",      ""}, /* Index 10 */ /* TODO: Verify RGB value is correct */
{{232, 169,   0}, "Deep Gold",       ""}, /* Index 11 */
{{254, 186,  53}, "Orange",          ""}, /* Index 12 */
{{255, 255,   0}, "Yellow",          ""}, /* Index 13 */
{{112, 188,  31}, "Lime Green",      ""}, /* Index 14 */
{{186, 152,   0}, "Brass",           ""}, /* Index 15 */
{{168, 168, 168}, "Silver",          ""}, /* Index 16 */
{{125, 111,   0}, "Russet Brown",    ""}, /* Index 17 */ /* TODO: Verify RGB value is correct */
{{255, 255, 179}, "Cream Brown",     ""}, /* Index 18 */
{{ 79,  85,  86}, "Pewter",          ""}, /* Index 19 */
{{  0,   0,   0}, "Black",           ""}, /* Index 20 */
{{ 11,  61, 145}, "Ultramarine",     ""}, /* Index 21 */
{{119,   1, 118}, "Royal Purple",    ""}, /* Index 22 */
{{ 41,  49,  51}, "Dark Gray",       ""}, /* Index 23 */
{{ 42,  19,   1}, "Dark Brown",      ""}, /* Index 24 */
{{246,  74, 138}, "Deep Rose",       ""}, /* Index 25 */
{{178, 118,  36}, "Light Brown",     ""}, /* Index 26 */
{{252, 187, 197}, "Salmon Pink",     ""}, /* Index 27 */ /* TODO: Verify RGB value is correct */
{{254,  55,  15}, "Vermillion",      ""}, /* Index 28 */
{{240, 240, 240}, "White",           ""}, /* Index 29 */
{{106,  28, 138}, "Violet",          ""}, /* Index 30 */
{{168, 221, 196}, "Seacrest",        ""}, /* Index 31 */
{{ 37, 132, 187}, "Sky Blue",        ""}, /* Index 32 */
{{254, 179,  67}, "Pumpkin",         ""}, /* Index 33 */
{{255, 243, 107}, "Cream Yellow",    ""}, /* Index 34 */
{{208, 166,  96}, "Khaki",           ""}, /* Index 35 */
{{209,  84,   0}, "Clay Brown",      ""}, /* Index 36 */
{{102, 186,  73}, "Leaf Green",      ""}, /* Index 37 */
{{ 19,  74,  70}, "Peacock Blue",    ""}, /* Index 38 */
{{135, 135, 135}, "Gray",            ""}, /* Index 39 */
{{216, 204, 198}, "Warm Gray",       ""}, /* Index 40 */ /* TODO: Verify RGB value is correct */
{{ 67,  86,   7}, "Dark Olive",      ""}, /* Index 41 */
{{253, 217, 222}, "Flesh Pink",      ""}, /* Index 42 */ /* TODO: Verify RGB value is correct */
{{249, 147, 188}, "Pink",            ""}, /* Index 43 */
{{  0,  56,  34}, "Deep Green",      ""}, /* Index 44 */
{{178, 175, 212}, "Lavender",        ""}, /* Index 45 */
{{104, 106, 176}, "Wisteria Violet", ""}, /* Index 46 */
{{239, 227, 185}, "Beige",           ""}, /* Index 47 */
{{247,  56, 102}, "Carmine",         ""}, /* Index 48 */
{{181,  75, 100}, "Amber Red",       ""}, /* Index 49 */ /* TODO: Verify RGB value is correct */
{{ 19,  43,  26}, "Olive Green",     ""}, /* Index 50 */
{{199,   1,  86}, "Dark Fuschia",    ""}, /* Index 51 */ /* TODO: Verify RGB value is correct */
{{254, 158,  50}, "Tangerine",       ""}, /* Index 52 */
{{168, 222, 235}, "Light Blue",      ""}, /* Index 53 */
{{  0, 103,  62}, "Emerald Green",   ""}, /* Index 54 */ /* TODO: Verify RGB value is correct */
{{ 78,  41, 144}, "Purple",          ""}, /* Index 55 */
{{ 47, 126,  32}, "Moss Green",      ""}, /* Index 56 */
{{255, 204, 204}, "Flesh Pink",      ""}, /* Index 57 */ /* TODO: Verify RGB value is correct */ /* TODO: Flesh Pink is Index 42, is this Index incorrect? */
{{255, 217,  17}, "Harvest Gold",    ""}, /* Index 58 */
{{  9,  91, 166}, "Electric Blue",   ""}, /* Index 59 */
{{240, 249, 112}, "Lemon Yellow",    ""}, /* Index 60 */
{{227, 243,  91}, "Fresh Green",     ""}, /* Index 61 */
{{255, 153,   0}, "Orange",          ""}, /* Index 62 */ /* TODO: Verify RGB value is correct */ /* TODO: Orange is Index 12, is this Index incorrect? */
{{255, 240, 141}, "Cream Yellow",    ""}, /* Index 63 */ /* TODO: Verify RGB value is correct */ /* TODO: Cream Yellow is Index 34, is this Index incorrect? */
{{255, 200, 200}, "Applique",        ""}  /* Index 64 */
};

const char imageWithFrame[38][48] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

void readPecStitches(EmbPattern* pattern, EmbFile* file)
{
    FILE *f = file->file;
    int stitchNumber = 0;

    while (!feof(f)) {
        int val1 = (int)(unsigned char)fgetc(f);
        int val2 = (int)(unsigned char)fgetc(f);

        int stitchType = NORMAL;
        if(val1 == 0xFF && val2 == 0x00)
        {
            embPattern_end(pattern);
            break;
        }
        if(val1 == 0xFE && val2 == 0xB0)
        {
            (void)fgetc(f);
            embPattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
            stitchNumber++;
            continue;
        }
        /* High bit set means 12-bit offset, otherwise 7-bit signed delta */
        if(val1 & 0x80)
        {
            if(val1 & 0x20) stitchType = TRIM;
            if(val1 & 0x10) stitchType = JUMP;
            val1 = ((val1 & 0x0F) << 8) + val2;

            /* Signed 12-bit arithmetic */
            if(val1 & 0x800)
            {
                val1 -= 0x1000;
            }

            val2 = binaryReadUInt8(file);
        }
        else if(val1 >= 0x40)
        {
            val1 -= 0x80;
        }
        if(val2 & 0x80)
        {
            if(val2 & 0x20) stitchType = TRIM;
            if(val2 & 0x10) stitchType = JUMP;
            val2 = ((val2 & 0x0F) << 8) + binaryReadUInt8(file);

            /* Signed 12-bit arithmetic */
            if(val2 & 0x800)
            {
                val2 -= 0x1000;
            }
        }
        else if(val2 >= 0x40)
        {
            val2 -= 0x80;
        }
        embPattern_addStitchRel(pattern, val1 / 10.0, val2 / 10.0, stitchType, 1);
        stitchNumber++;
    }
}

static void pecEncodeJump(EmbFile* file, int x, int types)
{
    int outputVal = abs(x) & 0x7FF;
    unsigned int orPart = 0x80;

    if(!file) { printf("ERROR: format-pec.c pecEncodeJump(), file argument is null\n"); return; }

    if(types & TRIM)
    {
        orPart |= 0x20;
    }
    if(types & JUMP)
    {
        orPart |= 0x10;
    }

    if(x < 0)
    {
        outputVal = x + 0x1000 & 0x7FF;
        outputVal |= 0x800;
    }
    binaryWriteByte(file, (unsigned char)(((outputVal >> 8) & 0x0F) | orPart));
    binaryWriteByte(file, (unsigned char)(outputVal & 0xFF));
}

static void pecEncodeStop(EmbFile* file, unsigned char val)
{
    if(!file) { printf("ERROR: format-pec.c pecEncodeStop(), file argument is null\n"); return; }
    binaryWriteByte(file, 0xFE);
    binaryWriteByte(file, 0xB0);
    binaryWriteByte(file, val);
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readPec(EmbPattern* pattern, const char* fileName)
{
    unsigned int graphicsOffset;
    unsigned char colorChanges;
    int i;
    EmbFile* file = 0;

    if (!validateReadPattern(pattern, fileName, "readPec")) {
        return 0;
    }

    file = embFile_open(fileName, "rb", 0);
    if (!file)
        return 0;

    embFile_seek(file, 0x38, SEEK_SET);
    colorChanges = (unsigned char)binaryReadByte(file);
    for(i = 0; i <= colorChanges; i++)
    {
        embPattern_addThread(pattern, pecThreads[binaryReadByte(file) % 65]);
    }

    /* Get Graphics offset */
    embFile_seek(file, 0x20A, SEEK_SET);

    graphicsOffset = (unsigned int)(binaryReadUInt8(file));
    graphicsOffset |= (binaryReadUInt8(file) << 8);
    graphicsOffset |= (binaryReadUInt8(file) << 16);

    (void)binaryReadByte(file); /* 0x31 */
    (void)binaryReadByte(file); /* 0xFF */
    (void)binaryReadByte(file); /* 0xF0 */
    /* Get X and Y size in .1 mm */
    /* 0x210 */
    binaryReadInt16(file); /* x size */
    binaryReadInt16(file); /* y size */

    binaryReadInt16(file); /* 0x01E0 */
    binaryReadInt16(file); /* 0x01B0 */
    binaryReadInt16(file); /* distance left from start */
    binaryReadInt16(file); /* distance up from start */

    /* Begin Stitch Data */
    /* 0x21C */
    /*unsigned int end = graphicsOffset + 0x208; */
    readPecStitches(pattern, file);

    embFile_close(file);
    embPattern_end(pattern);

    embPattern_flipVertical(pattern);

    return 1;
}

static void pecEncode(EmbFile* file, EmbPattern* p)
{
    double thisX = 0.0;
    double thisY = 0.0;
    unsigned char stopCode = 2;
    EmbStitchList* list = 0;

    if (!file) {
        printf("ERROR: format-pec.c pecEncode(), file argument is null\n");
        return;
    }
    if (!p) {
        printf("ERROR: format-pec.c pecEncode(), p argument is null\n");
        return;
    }

    list = p->stitchList;
    while(list)
    {
        int deltaX, deltaY;
        EmbStitch s = list->stitch;

        deltaX = roundDouble(s.x - thisX);
        deltaY = roundDouble(s.y - thisY);
        thisX += (double)deltaX;
        thisY += (double)deltaY;

        if(s.flags & STOP)
        {
            pecEncodeStop(file, stopCode);
            if(stopCode == (unsigned char)2)
            {
                stopCode = (unsigned char)1;
            }
            else
            {
                stopCode = (unsigned char)2;
            }
        }
        else if(s.flags & END)
        {
            binaryWriteByte(file, 0xFF);
            break;
        }
        else if(deltaX < 63 && deltaX > -64 && deltaY < 63 && deltaY > -64 && (!(s.flags & (JUMP | TRIM))))
        {
            binaryWriteByte(file, (deltaX < 0) ? (unsigned char)(deltaX + 0x80) : (unsigned char)deltaX);
            binaryWriteByte(file, (deltaY < 0) ? (unsigned char)(deltaY + 0x80) : (unsigned char)deltaY);
        }
        else
        {
            pecEncodeJump(file, deltaX, s.flags);
            pecEncodeJump(file, deltaY, s.flags);
        }
        list = list->next;
    }
}

static void writeImage(FILE* file, unsigned char image[][48])
{
    int i, j;

    if(!file) { printf("ERROR: format-pec.c writeImage(), file argument is null\n"); return; }

    for(i = 0; i < 38; i++)
    {
        for(j = 0; j < 6; j++)
        {
            int offset = j * 8;
            unsigned char output = 0;
            output |= (unsigned char)(image[i][offset] != 0);
            output |= (unsigned char)(image[i][offset + 1] != (unsigned char)0) << 1;
            output |= (unsigned char)(image[i][offset + 2] != (unsigned char)0) << 2;
            output |= (unsigned char)(image[i][offset + 3] != (unsigned char)0) << 3;
            output |= (unsigned char)(image[i][offset + 4] != (unsigned char)0) << 4;
            output |= (unsigned char)(image[i][offset + 5] != (unsigned char)0) << 5;
            output |= (unsigned char)(image[i][offset + 6] != (unsigned char)0) << 6;
            output |= (unsigned char)(image[i][offset + 7] != (unsigned char)0) << 7;
            fwrite(&output, 1, 1, file);
        }
    }
}

void writePecStitches(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    EmbStitchList* tempStitches = 0;
    EmbRect bounds;
    unsigned char image[38][48];
    int i, flen, currentThreadCount, graphicsOffsetLocation, graphicsOffsetValue, height, width;
    double xFactor, yFactor;
    const char* forwardSlashPos = strrchr(fileName, '/');
    const char* backSlashPos = strrchr(fileName, '\\');
    const char* dotPos = strrchr(fileName, '.');
    const char* start = 0;

    start = fileName;
    if (forwardSlashPos) {
        start = forwardSlashPos + 1;
    }
    if (backSlashPos && backSlashPos > start) {
        start = backSlashPos + 1;
    }
    embFile_write("LA:", 1, 3, file);
    flen = (int)(dotPos - start);

    while (start < dotPos) {
        binaryWriteByte(file, (unsigned char)*start);
        start++;
    }
    embFile_pad(file, 0x20, 16-flen);
    binaryWriteByte(file, 0x0D);
    embFile_pad(file, 0x20, 12);
    embFile_write("\xff\x00\x06\x26", 1, 4, file);

    embFile_pad(file, 0x20, 12);
    currentThreadCount = pattern->threads->count;
    binaryWriteByte(file, (unsigned char)(currentThreadCount-1));

    for(i = 0; i < currentThreadCount; i++) {
        EmbColor thr = pattern->threads->thread[i].color;
        unsigned char color = (unsigned char)embThread_findNearestColor_fromThread(thr, pecThreads, pecThreadCount);
        embFile_write(&color, 1, 1, file);
    }
    embFile_pad(file, 0x20, (int)(0x1CF - currentThreadCount));
    embFile_pad(file, 0x00, 2);

    graphicsOffsetLocation = embFile_tell(file);
    /* placeholder bytes to be overwritten */
    embFile_pad(file, 0x00, 3);

    embFile_write("\x31\xff\xf0", 1, 3, file);

    bounds = embPattern_calcBoundingBox(pattern);

    height = roundDouble(embRect_height(bounds));
    width = roundDouble(embRect_width(bounds));
    /* write 2 byte x size */
    binaryWriteShort(file, (short)width);
    /* write 2 byte y size */
    binaryWriteShort(file, (short)height);

    /* Write 4 miscellaneous int16's */
    embFile_write("\x01\xe0\x01\xb0", 1, 4, file);

    binaryWriteUShortBE(file, (unsigned short)(0x9000 | -roundDouble(bounds.left)));
    binaryWriteUShortBE(file, (unsigned short)(0x9000 | -roundDouble(bounds.top)));

    pecEncode(file, pattern);
    graphicsOffsetValue = embFile_tell(file) - graphicsOffsetLocation + 2;
    embFile_seek(file, graphicsOffsetLocation, SEEK_SET);

    binaryWriteByte(file, (unsigned char)(graphicsOffsetValue & 0xFF));
    binaryWriteByte(file, (unsigned char)((graphicsOffsetValue >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((graphicsOffsetValue >> 16) & 0xFF));

    embFile_seek(file, 0x00, SEEK_END);

    /* Writing all colors */
    memcpy(image, imageWithFrame, 48*38);
    tempStitches = pattern->stitchList;

    yFactor = 32.0 / height;
    xFactor = 42.0 / width;
    while (tempStitches->next) {
        EmbStitch st = tempStitches->stitch;
        int x = roundDouble((st.x - bounds.left) * xFactor) + 3;
        int y = roundDouble((st.y - bounds.top) * yFactor) + 3;
        image[y][x] = 1;
        tempStitches = tempStitches->next;
    }
    writeImage(file->file, image);

    /* Writing each individual color */
    tempStitches = pattern->stitchList;
    for (i = 0; i < currentThreadCount; i++) {
        memcpy(image, imageWithFrame, 48*38);
        while (tempStitches->next) {
            EmbStitch st = tempStitches->stitch;
            int x = roundDouble((st.x - bounds.left) * xFactor) + 3;
            int y = roundDouble((st.y - bounds.top) * yFactor) + 3;
            if (st.flags & STOP) {
                tempStitches = tempStitches->next;
                break;
            }
            image[y][x] = 1;
            tempStitches = tempStitches->next;
        }
        writeImage(file->file, image);
    }
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writePec(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file = 0;

    if (!validateWritePattern(pattern, fileName, "writePec")) {
        return 0;
    }

    file = embFile_open(fileName, "wb", 0);
    if(!file)
        return 0;

    embPattern_flipVertical(pattern); /* TODO: There needs to be a matching flipVertical() call after the write to ensure multiple writes from the same pattern work properly */
    embPattern_fixColorCount(pattern);
    embPattern_correctForMaxStitchLength(pattern, 12.7, 204.7);
    embPattern_scale(pattern, 10.0);

    embFile_write("#PEC0001", 1, 8, file);

    writePecStitches(pattern, file, fileName);

    embFile_close(file);
    return 1;
}

