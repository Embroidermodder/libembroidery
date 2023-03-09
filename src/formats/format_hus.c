/*
 * 100 FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <math.h>

#include "../embroidery_internal.h"


/* ---------------------------------------------------------------- */
/* format hus */

int husDecodeStitchType(unsigned char b)
{
    switch(b) {
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

unsigned char*
husDecompressData(unsigned char* input, int compressedInputLength, int decompressedContentLength)
{
    char* decompressedData = (char*)malloc(sizeof(char)*decompressedContentLength);
    if (!decompressedData) { printf("ERROR: husDecompressData(), cannot allocate memory for decompressedData\n"); return 0; }
    hus_decompress((char*)input, compressedInputLength, decompressedData, &decompressedContentLength);
    return (unsigned char *)decompressedData;
}

unsigned char*
husCompressData(unsigned char* input, int decompressedInputSize, int* compressedSize)
{
    char* compressedData = (char*)malloc(sizeof(char)*decompressedInputSize*2);
    if (!compressedData) { printf("ERROR: husCompressData(), cannot allocate memory for compressedData\n"); return 0; }
    hus_compress((char*)input, decompressedInputSize, compressedData, compressedSize);
    return (unsigned char *)compressedData;
}

int
husDecodeByte(unsigned char b)
{
    return (char)b;
}

unsigned char
husEncodeByte(EmbReal f)
{
    return (unsigned char)(int)emb_round(f);
}

unsigned char
husEncodeStitchType(int st)
{
    switch(st) {
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

char
readHus(EmbPattern* pattern, FILE* file)
{
    int fileLength;
    int magicCode, numberOfStitches, numberOfColors;
    int positiveXHoopSize, positiveYHoopSize, negativeXHoopSize, negativeYHoopSize;
    int attributeOffset, xOffset, yOffset;
    unsigned char *attributeData, *xData , *yData;
    unsigned char* attributeDataDecompressed = 0;
    unsigned char* xDecompressed = 0;
    unsigned char* yDecompressed = 0;
    unsigned char* stringVal = 0;

    int unknown, i = 0;

    puts("ERROR: Overridden. readHus is not implemented for now.");
    return 0;

    fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x00, SEEK_SET);

    embInt_read(file, "magicCode", &magicCode, EMB_INT32_LITTLE);
    embInt_read(file, "numberOfStitchs", &numberOfStitches, EMB_INT32_LITTLE);
    embInt_read(file, "numberOfColors", &numberOfColors, EMB_INT32_LITTLE);

    /* These should be put in the EmbPattern. */
    embInt_read(file, "+X HoopSize", &positiveXHoopSize, EMB_INT16_LITTLE);
    embInt_read(file, "+Y HoopSize", &positiveYHoopSize, EMB_INT16_LITTLE);
    embInt_read(file, "-X HoopSize", &negativeXHoopSize, EMB_INT16_LITTLE);
    embInt_read(file, "-Y HoopSize", &negativeYHoopSize, EMB_INT16_LITTLE);

    embInt_read(file, "attributeOffset", &attributeOffset, EMB_INT32_LITTLE);
    embInt_read(file, "xOffset", &xOffset, EMB_INT32_LITTLE);
    embInt_read(file, "yOffset", &yOffset, EMB_INT32_LITTLE);

    stringVal = (unsigned char*)malloc(sizeof(unsigned char)*8);
    if (!stringVal) {
        printf("ERROR: format-hus.c readHus(), cannot allocate memory for stringVal\n");
        return 0;
    }
    fread(stringVal, 1, 8, file); /* TODO: check return value */

    embInt_read(file, "unknown", &unknown, EMB_INT16_LITTLE);
    for (i = 0; i < numberOfColors; i++) {
        short pos;
        embInt_read(file, "pos", &pos, EMB_INT16_LITTLE);
        embPattern_addThread(pattern, husThreads[pos]);
    }

    attributeData = (unsigned char*)malloc(sizeof(unsigned char)*(xOffset - attributeOffset + 1));
    if (!attributeData) {
        printf("ERROR: format-hus.c readHus(), cannot allocate memory for attributeData\n");
        return 0;
    }
    fread(attributeData, 1, xOffset - attributeOffset, file); /* TODO: check return value */
    attributeDataDecompressed = husDecompressData(attributeData, xOffset - attributeOffset, numberOfStitches + 1);

    xData = (unsigned char*)malloc(sizeof(unsigned char)*(yOffset - xOffset + 1));
    if (!xData) {
        printf("ERROR: format-hus.c readHus(), cannot allocate memory for xData\n");
        return 0;
    }
    fread(xData, 1, yOffset - xOffset, file); /* TODO: check return value */
    xDecompressed = husDecompressData(xData, yOffset - xOffset, numberOfStitches);

    yData = (unsigned char*)malloc(sizeof(unsigned char)*(fileLength - yOffset + 1));
    if (!yData) {
        printf("ERROR: format-hus.c readHus(), cannot allocate memory for yData\n");
        return 0;
    }
    fread(yData, 1, fileLength - yOffset, file); /* TODO: check return value */
    yDecompressed = husDecompressData(yData, fileLength - yOffset, numberOfStitches);

    for (i = 0; i < numberOfStitches; i++) {
        int flag;
        EmbVector v;
        v.x = husDecodeByte(xDecompressed[i]) / 10.0;
        v.y = husDecodeByte(yDecompressed[i]) / 10.0;
        flag = husDecodeStitchType(attributeDataDecompressed[i]);
        embPattern_addStitchRel(pattern, v.x, v.y, flag, 1);
    }

    safe_free(stringVal);
    safe_free(xData);
    safe_free(xDecompressed);
    safe_free(yData);
    safe_free(yDecompressed);
    safe_free(attributeData);
    safe_free(attributeDataDecompressed);

    return 1;
}

char
writeHus(EmbPattern* pattern, FILE* file)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor, attributeSize, xCompressedSize, yCompressedSize, i;
    EmbReal previousX, previousY;
    short right, top, bottom, left;
    unsigned int code, colors, offset1, offset2;
    unsigned char *xValues = 0, *yValues = 0, *attributeValues = 0,
        *attributeCompressed = 0, *xCompressed = 0, *yCompressed = 0;
    
    stitchCount = pattern->stitch_list->count;
    /* embPattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */
    minColors = pattern->thread_list->count;
    patternColor = minColors;
    if (minColors > 24) minColors = 24;
    code = 0x00C8AF5B;
    embInt_write(file, "code", &code, EMB_INT32_LITTLE);
    embInt_write(file, "stitchCount", &stitchCount, EMB_INT32_LITTLE);
    embInt_write(file, "minColors", &minColors, EMB_INT32_LITTLE);

    boundingRect = embPattern_calcBoundingBox(pattern);
    right = (short) emb_round(boundingRect.right * 10.0);
    top = (short) -emb_round(boundingRect.top * 10.0);
    left = (short) emb_round(boundingRect.left * 10.0);
    bottom = (short) -emb_round(boundingRect.bottom * 10.0);
    embInt_write(file, "right", &right, EMB_INT16_LITTLE);
    embInt_write(file, "top", &top, EMB_INT16_LITTLE);
    embInt_write(file, "left", &left, EMB_INT16_LITTLE);
    embInt_write(file, "bottom", &bottom, EMB_INT16_LITTLE);

    colors = 0x2A + 2 * minColors;
    embInt_write(file, ".", &colors, EMB_INT32_LITTLE);

    xValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if (!xValues) {
        printf("ERROR: format-hus.c writeHus(), cannot allocate memory for xValues\n");
        return 0;
    }
    yValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if (!yValues) {
        printf("ERROR: format-hus.c writeHus(), cannot allocate memory for yValues\n");
        return 0;
    }
    attributeValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if (!attributeValues) {
        printf("ERROR: format-hus.c writeHus(), cannot allocate memory for attributeValues\n");
        return 0;
    }

    previousX = 0.0;
    previousY = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st;
        st = pattern->stitch_list->stitch[i];
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

    offset1 = (unsigned int) (0x2A + 2 * patternColor + attributeSize);
    offset2 = (unsigned int) (0x2A + 2 * patternColor + attributeSize + xCompressedSize);
    embInt_write(file, "offset1", &offset1, EMB_INT32_LITTLE);
    embInt_write(file, "offset2", &offset2, EMB_INT32_LITTLE);
    fpad(file, 0, 10);

    for (i = 0; i < patternColor; i++) {
        short color_index = (short)embThread_findNearestThread(pattern->thread_list->thread[i].color, (EmbThread*)husThreads, 29);
        embInt_write(file, ".", &color_index, EMB_INT16_LITTLE);
    }

    fwrite(attributeCompressed, 1, attributeSize, file);
    fwrite(xCompressed, 1, xCompressedSize, file);
    fwrite(yCompressed, 1, yCompressedSize, file);

    safe_free(xValues);
    safe_free(xCompressed);
    safe_free(yValues);
    safe_free(yCompressed);
    safe_free(attributeValues);
    safe_free(attributeCompressed);

    return 1;
}
