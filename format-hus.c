#include "embroidery.h"
#include "embroidery-internal.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

/*****************************************
 * HUS Colors
 ****************************************/
static const EmbThread husThreads[] = {
{{   0,   0,   0 }, "Black",        "TODO:HUS_CATALOG_NUMBER"},
{{   0,   0, 255 }, "Blue",         "TODO:HUS_CATALOG_NUMBER"},
{{   0, 255,   0 }, "Light Green",  "TODO:HUS_CATALOG_NUMBER"},
{{ 255,   0,   0 }, "Red",          "TODO:HUS_CATALOG_NUMBER"},
{{ 255,   0, 255 }, "Purple",       "TODO:HUS_CATALOG_NUMBER"},
{{ 255, 255,   0 }, "Yellow",       "TODO:HUS_CATALOG_NUMBER"},
{{ 127, 127, 127 }, "Gray",         "TODO:HUS_CATALOG_NUMBER"},
{{  51, 154, 255 }, "Light Blue",   "TODO:HUS_CATALOG_NUMBER"},
{{  51, 204, 102 }, "Green",        "TODO:HUS_CATALOG_NUMBER"},
{{ 255, 127,   0 }, "Orange",       "TODO:HUS_CATALOG_NUMBER"},
{{ 255, 160, 180 }, "Pink",         "TODO:HUS_CATALOG_NUMBER"},
{{ 153,  75,   0 }, "Brown",        "TODO:HUS_CATALOG_NUMBER"},
{{ 255, 255, 255 }, "White",        "TODO:HUS_CATALOG_NUMBER"},
{{   0,   0, 127 }, "Dark Blue",    "TODO:HUS_CATALOG_NUMBER"},
{{   0, 127,   0 }, "Dark Green",   "TODO:HUS_CATALOG_NUMBER"},
{{ 127,   0,   0 }, "Dark Red",     "TODO:HUS_CATALOG_NUMBER"},
{{ 255, 127, 127 }, "Light Red",    "TODO:HUS_CATALOG_NUMBER"},
{{ 127,   0, 127 }, "Dark Purple",  "TODO:HUS_CATALOG_NUMBER"},
{{ 255, 127, 255 }, "Light Purple", "TODO:HUS_CATALOG_NUMBER"},
{{ 200, 200,   0 }, "Dark Yellow",  "TODO:HUS_CATALOG_NUMBER"},
{{ 255, 255, 153 }, "Light Yellow", "TODO:HUS_CATALOG_NUMBER"},
{{  60,  60,  60 }, "Dark Gray",    "TODO:HUS_CATALOG_NUMBER"},
{{ 192, 192, 192 }, "Light Gray",   "TODO:HUS_CATALOG_NUMBER"},
{{ 232,  63,   0 }, "Dark Orange",  "TODO:HUS_CATALOG_NUMBER"},
{{ 255, 165,  65 }, "Light Orange", "TODO:HUS_CATALOG_NUMBER"},
{{ 255, 102, 122 }, "Dark Pink",    "TODO:HUS_CATALOG_NUMBER"},
{{ 255, 204, 204 }, "Light Pink",   "TODO:HUS_CATALOG_NUMBER"},
{{ 115,  40,   0 }, "Dark Brown",   "TODO:HUS_CATALOG_NUMBER"},
{{ 175,  90,  10 }, "Light Brown",  "TODO:HUS_CATALOG_NUMBER"}
};

static int husDecodeStitchType(unsigned char b)
{
    switch(b)
    {
        case 0x80:
            return NORMAL;
        case 0x81:
            return JUMP;
        case 0x84:
            return STOP;
        case 0x90:
            return END;
        default:
            return NORMAL;
    }
}

static unsigned char* husDecompressData(unsigned char* input, int compressedInputLength, int decompressedContentLength)
{
    unsigned char* decompressedData = (unsigned char*)malloc(sizeof(unsigned char)*decompressedContentLength);
    if(!decompressedData) { printf("ERROR: format-hus.c husDecompressData(), cannot allocate memory for decompressedData\n"); return 0; }
    hus_decompress((char*)input, compressedInputLength, decompressedData, &decompressedContentLength);
    return decompressedData;
}

static unsigned char* husCompressData(unsigned char* input, int decompressedInputSize, int* compressedSize)
{
    unsigned char* compressedData = (unsigned char*)malloc(sizeof(unsigned char)*decompressedInputSize*2);
    if(!compressedData) { printf("ERROR: format-hus.c husCompressData(), cannot allocate memory for compressedData\n"); return 0; }
    hus_compress((char*)input, decompressedInputSize, compressedData, compressedSize);
    return compressedData;
}

static int husDecodeByte(unsigned char b)
{
    return (char)b;
}

static unsigned char husEncodeByte(double f)
{
    return (unsigned char)(int)roundDouble(f);
}

static unsigned char husEncodeStitchType(int st)
{
    switch(st)
    {
        case NORMAL:
            return (0x80);
        case JUMP:
        case TRIM:
            return (0x81);
        case STOP:
            return (0x84);
        case END:
            return (0x90);
        default:
            return (0x80);
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readHus(EmbPattern* pattern, const char* fileName)
{
    int fileLength;
    int magicCode, numberOfStitches, numberOfColors;
    int postitiveXHoopSize, postitiveYHoopSize, negativeXHoopSize, negativeYHoopSize;

    int attributeOffset, xOffset, yOffset;
    unsigned char* attributeData = 0;
    unsigned char* attributeDataDecompressed = 0;

    unsigned char* xData = 0;
    unsigned char* xDecompressed = 0;

    unsigned char* yData = 0;
    unsigned char* yDecompressed = 0;
    unsigned char* stringVal = 0;
    int unknown, i = 0;
    EmbFile* file = 0;

    if (!validateReadPattern(pattern, fileName, "readHus")) return 0;

    file = embFile_open(fileName, "rb", 0);
    if(!file)
        return 0;

    embFile_seek(file, 0x00, SEEK_END);
    fileLength = embFile_tell(file);
    embFile_seek(file, 0x00, SEEK_SET);

    magicCode = binaryReadInt32(file);
    numberOfStitches = binaryReadInt32(file);
    numberOfColors = binaryReadInt32(file);

    postitiveXHoopSize = binaryReadInt16(file);
    postitiveYHoopSize = binaryReadInt16(file);
    negativeXHoopSize = binaryReadInt16(file);
    negativeYHoopSize = binaryReadInt16(file);

    attributeOffset = binaryReadInt32(file);
    xOffset = binaryReadInt32(file);
    yOffset = binaryReadInt32(file);

    stringVal = (unsigned char*)malloc(sizeof(unsigned char)*8);
    if(!stringVal) { printf("ERROR: format-hus.c readHus(), cannot allocate memory for stringVal\n"); return 0; }
    binaryReadBytes(file, stringVal, 8); /* TODO: check return value */

    unknown = binaryReadInt16(file);
    for(i = 0; i < numberOfColors; i++)
    {
        int pos = binaryReadInt16(file);
        embPattern_addThread(pattern, husThreads[pos]);
    }

    attributeData = (unsigned char*)malloc(sizeof(unsigned char)*(xOffset - attributeOffset + 1));
    if(!attributeData) { printf("ERROR: format-hus.c readHus(), cannot allocate memory for attributeData\n"); return 0; }
    binaryReadBytes(file, attributeData, xOffset - attributeOffset); /* TODO: check return value */
    attributeDataDecompressed = husDecompressData(attributeData, xOffset - attributeOffset, numberOfStitches + 1);

    xData = (unsigned char*)malloc(sizeof(unsigned char)*(yOffset - xOffset + 1));
    if(!xData) { printf("ERROR: format-hus.c readHus(), cannot allocate memory for xData\n"); return 0; }
    binaryReadBytes(file, xData, yOffset - xOffset); /* TODO: check return value */
    xDecompressed = husDecompressData(xData, yOffset - xOffset, numberOfStitches);

    yData = (unsigned char*)malloc(sizeof(unsigned char)*(fileLength - yOffset + 1));
    if(!yData) { printf("ERROR: format-hus.c readHus(), cannot allocate memory for yData\n"); return 0; }
    binaryReadBytes(file, yData, fileLength - yOffset); /* TODO: check return value */
    yDecompressed = husDecompressData(yData, fileLength - yOffset, numberOfStitches);

    for(i = 0; i < numberOfStitches; i++)
    {
        embPattern_addStitchRel(pattern,
                                husDecodeByte(xDecompressed[i]) / 10.0,
                                husDecodeByte(yDecompressed[i]) / 10.0,
                                husDecodeStitchType(attributeDataDecompressed[i]), 1);
    }

    if(stringVal) { free(stringVal); stringVal = 0; }
    if(xData) { free(xData); xData = 0; }
    if(xDecompressed) { free(xDecompressed); xDecompressed = 0; }
    if(yData) { free(yData); yData = 0; }
    if(yDecompressed) { free(yDecompressed); yDecompressed = 0; }
    if(attributeData) { free(attributeData); attributeData = 0; }
    if(attributeDataDecompressed) { free(attributeDataDecompressed); attributeDataDecompressed = 0; }

    embFile_close(file);

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeHus(EmbPattern* pattern, const char* fileName)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor;
    int attributeSize, xCompressedSize, yCompressedSize, i;
    double previousX, previousY;
    unsigned char* xValues = 0, *yValues = 0, *attributeValues = 0;
    unsigned char* attributeCompressed = 0, *xCompressed = 0, *yCompressed = 0;
    EmbStitch st;
    EmbFile* file;

    if (!validateWritePattern(pattern, fileName, "writeHus")) return 0;

    file = embFile_open(fileName, "wb", 0);
    if(!file) {
        return 0;
    }
    
    stitchCount = pattern->stitchList->count;
    /* embPattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */
    minColors = pattern->threads->count;
    patternColor = minColors;
    if(minColors > 24) minColors = 24;
    binaryWriteUInt(file, 0x00C8AF5B);
    binaryWriteUInt(file, stitchCount);
    binaryWriteUInt(file, minColors);

    boundingRect = embPattern_calcBoundingBox(pattern);
    binaryWriteShort(file, (short) roundDouble(boundingRect.right * 10.0));
    binaryWriteShort(file, (short) -roundDouble(boundingRect.top * 10.0 - 1.0));
    binaryWriteShort(file, (short) roundDouble(boundingRect.left * 10.0));
    binaryWriteShort(file, (short) -roundDouble(boundingRect.bottom * 10.0 - 1.0));

    binaryWriteUInt(file, 0x2A + 2 * minColors);

    xValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if(!xValues) { printf("ERROR: format-hus.c writeHus(), cannot allocate memory for xValues\n"); return 0; }
    yValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if(!yValues) { printf("ERROR: format-hus.c writeHus(), cannot allocate memory for yValues\n"); return 0; }
    attributeValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if(!attributeValues) { printf("ERROR: format-hus.c writeHus(), cannot allocate memory for attributeValues\n"); return 0; }

    previousX = 0.0;
    previousY = 0.0;
    for (i=0; i<pattern->stitchList->count; i++) {
        xValues[i] = husEncodeByte((st.x - previousX) * 10.0);
        previousX = st.x;
        yValues[i] = husEncodeByte((st.y - previousY) * 10.0);
        previousY = st.y;
        attributeValues[i] = husEncodeStitchType(st.flags);
    }
    attributeCompressed = husCompressData(attributeValues, stitchCount, &attributeSize);
    xCompressed = husCompressData(xValues, stitchCount, &xCompressedSize);
    yCompressed = husCompressData(yValues, stitchCount, &yCompressedSize);
    /* TODO: error if husCompressData returns zero? */

    binaryWriteUInt(file, (unsigned int) (0x2A + 2 * patternColor + attributeSize));
    binaryWriteUInt(file, (unsigned int) (0x2A + 2 * patternColor + attributeSize + xCompressedSize));
    binaryWriteUInt(file, 0x00000000);
    binaryWriteUInt(file, 0x00000000);
    binaryWriteUShort(file, 0x0000);

    for (i = 0; i < patternColor; i++) {
        short color_index = (short)embThread_findNearestColor_fromThread(pattern->threads->thread[i].color, husThreads, 29);
        binaryWriteShort(file, color_index);
    }

    binaryWriteBytes(file, (char*) attributeCompressed, attributeSize);
    binaryWriteBytes(file, (char*) xCompressed, xCompressedSize);
    binaryWriteBytes(file, (char*) yCompressed, yCompressedSize);

    free(xValues);
    free(xCompressed);
    free(yValues);
    free(yCompressed);
    free(attributeValues);
    free(attributeCompressed);

    embFile_close(file);
    return 1;
}

