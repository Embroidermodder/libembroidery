/* Husqvarna Viking Embroidery Format (.hus)
 *
 * Stitch Only Format.
 */

#include <stdlib.h>

#include "embroidery.h"

int husDecodeStitchType(uint8_t b)
{
    switch (b) {
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

uint8_t *husDecompressData(uint8_t *input,
                           int compressedInputLength,
                           int decompressedContentLength)
{
    int8_t *decompressedData =
        (char *)malloc(sizeof(char) * decompressedContentLength);
    if (!decompressedData) {
        printf
            ("ERROR: husDecompressData(), cannot allocate memory for decompressedData\n");
        return 0;
    }
    hus_decompress((char *)input, compressedInputLength, decompressedData,
                   &decompressedContentLength);
    return (uint8_t *) decompressedData;
}

uint8_t *husCompressData(uint8_t *input, int decompressedInputSize,
                         int *compressedSize)
{
    int8_t *compressedData =
        (char *)malloc(sizeof(char) * decompressedInputSize * 2);
    if (!compressedData) {
        printf
            ("ERROR: husCompressData(), cannot allocate memory for compressedData\n");
        return 0;
    }
    hus_compress((char *)input, decompressedInputSize, compressedData,
                 compressedSize);
    return (uint8_t *) compressedData;
}

int husDecodeByte(uint8_t b)
{
    return (char)b;
}

uint8_t husEncodeByte(EmbReal f)
{
    return (uint8_t) (int)emb_round(f);
}

uint8_t husEncodeStitchType(int st)
{
    switch (st) {
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

int8_t readHus(EmbPattern *pattern, FILE *file)
{
    int fileLength;
    int magicCode, numberOfStitches, numberOfColors;
    int positiveXHoopSize, positiveYHoopSize, negativeXHoopSize,
        negativeYHoopSize;
    int attributeOffset, xOffset, yOffset;
    uint8_t *attributeData, *xData, *yData;
    uint8_t *attributeDataDecompressed = 0;
    uint8_t *xDecompressed = 0;
    uint8_t *yDecompressed = 0;
    uint8_t *stringVal = 0;

    int unknown, i = 0;

    fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x00, SEEK_SET);

    magicCode = emb_read_i32(file);
    numberOfStitches = emb_read_i32(file);
    numberOfColors = emb_read_i32(file);

    /* These should be put in the EmbPattern. */
    positiveXHoopSize = emb_read_i16(file);
    positiveYHoopSize = emb_read_i16(file);
    negativeXHoopSize = emb_read_i16(file);
    negativeYHoopSize = emb_read_i16(file);

    attributeOffset = emb_read_i32(file);
    xOffset = emb_read_i32(file);
    yOffset = emb_read_i32(file);

    if (emb_verbose > 0) {
        printf("magicCode = %d\n", magicCode);
        printf("numberOfStitches = %d\n", numberOfStitches);
        printf("numberOfColors = %d\n", numberOfColors);
        printf("positiveXHoopSize = %d\n", positiveXHoopSize);
        printf("positiveYHoopSize = %d\n", positiveYHoopSize);
        printf("negativeXHoopSize = %d\n", negativeXHoopSize);
        printf("negativeYHoopSize = %d\n", negativeYHoopSize);
        printf("attributeOffset = %d\n", attributeOffset);
        printf("xOffset = %d\n", xOffset);
        printf("yOffset = %d\n", yOffset);
    }
    stringVal = (uint8_t *) malloc(sizeof(uint8_t) * 8);
    if (!stringVal) {
        printf
            ("ERROR: format-hus.c readHus(), cannot allocate memory for stringVal\n");
        return 0;
    }
    size_t size = 8;
    if (fread(stringVal, 1, size, file) != size) {
        puts("Ran out of bytes before full file read.");
        return 0;
    }

    unknown = emb_read_i16(file);
    printf("unknown: %d\n", unknown);
    for (i = 0; i < numberOfColors; i++) {
        short pos = emb_read_i16(file);
        emb_add_thread(pattern, hus_colors[pos]);
    }

    attributeData =
        (uint8_t *) malloc(sizeof(uint8_t) * (xOffset - attributeOffset + 1));
    if (!attributeData) {
        printf
            ("ERROR: format-hus.c readHus(), cannot allocate memory for attributeData\n");
        return 0;
    }
    size = xOffset - attributeOffset;
    if (fread(attributeData, 1, size, file) != size) {
        puts("Ran out of bytes before full file read.");
        return 0;
    }
    attributeDataDecompressed =
        husDecompressData(attributeData, size, numberOfStitches + 1);

    xData = (uint8_t *) malloc(sizeof(uint8_t) * (yOffset - xOffset + 1));
    if (!xData) {
        printf
            ("ERROR: format-hus.c readHus(), cannot allocate memory for xData\n");
        return 0;
    }
    size = yOffset - xOffset;
    if (fread(xData, 1, size, file) != size) {
        puts("Ran out of bytes before full file read.");
        return 0;
    }
    xDecompressed = husDecompressData(xData, size, numberOfStitches);

    yData = (uint8_t *) malloc(sizeof(uint8_t) * (fileLength - yOffset + 1));
    if (!yData) {
        printf
            ("ERROR: format-hus.c readHus(), cannot allocate memory for yData\n");
        return 0;
    }
    size = fileLength - yOffset;
    if (fread(yData, 1, size, file) != size) {
        puts("Ran out of bytes before full file read.");
        return 0;
    }
    yDecompressed = husDecompressData(yData, size, numberOfStitches);

    for (i = 0; i < numberOfStitches; i++) {
        int flag;
        EmbVector v;
        v.x = husDecodeByte(xDecompressed[i]) / 10.0;
        v.y = husDecodeByte(yDecompressed[i]) / 10.0;
        flag = husDecodeStitchType(attributeDataDecompressed[i]);
        emb_add_stitch(pattern, v.x, v.y, flag, 1);
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

int8_t writeHus(EmbPattern *pattern, FILE *file)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor, attributeSize,
        xCompressedSize, yCompressedSize, i;
    EmbReal previousX, previousY;
    short right, top, bottom, left;
    uint32_t code, colors, offset1, offset2;
    uint8_t *xValues = 0, *yValues = 0, *attributeValues = 0,
        *attributeCompressed = 0, *xCompressed = 0, *yCompressed = 0;

    stitchCount = pattern->stitch_list->count;
    /* emb_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */
    minColors = pattern->thread_list->count;
    patternColor = minColors;
    if (minColors > 24)
        minColors = 24;
    code = 0x00C8AF5B;
    emb_write_i32(file, code);
    emb_write_i32(file, stitchCount);
    emb_write_i32(file, minColors);

    boundingRect = emb_bounds(pattern);
    right = (int16_t) emb_round((boundingRect.w + boundingRect.x) * 10.0);
    top = (int16_t) - emb_round(boundingRect.y * 10.0);
    left = (int16_t) emb_round(boundingRect.x * 10.0);
    bottom = (int16_t) - emb_round((boundingRect.h + boundingRect.y) * 10.0);
    emb_write_i16(file, right);
    emb_write_i16(file, top);
    emb_write_i16(file, left);
    emb_write_i16(file, bottom);

    colors = 0x2A + 2 * minColors;
    emb_write_i32(file, colors);

    xValues = (uint8_t *) malloc(sizeof(uint8_t) * (stitchCount));
    if (!xValues) {
        printf
            ("ERROR: format-hus.c writeHus(), cannot allocate memory for xValues\n");
        return 0;
    }
    yValues = (uint8_t *) malloc(sizeof(uint8_t) * (stitchCount));
    if (!yValues) {
        printf
            ("ERROR: format-hus.c writeHus(), cannot allocate memory for yValues\n");
        return 0;
    }
    attributeValues = (uint8_t *) malloc(sizeof(uint8_t) * (stitchCount));
    if (!attributeValues) {
        printf
            ("ERROR: format-hus.c writeHus(), cannot allocate memory for attributeValues\n");
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
    attributeCompressed =
        husCompressData(attributeValues, stitchCount, &attributeSize);
    xCompressed = husCompressData(xValues, stitchCount, &xCompressedSize);
    yCompressed = husCompressData(yValues, stitchCount, &yCompressedSize);
    /* TODO: error if husCompressData returns zero? */

    offset1 = (uint32_t) (0x2A + 2 * patternColor + attributeSize);
    offset2 =
        (uint32_t) (0x2A + 2 * patternColor + attributeSize + xCompressedSize);
    emb_write_i32(file, offset1);
    emb_write_i32(file, offset2);
    fpad(file, 0, 10);

    for (i = 0; i < patternColor; i++) {
        short color_index =
            (int16_t) emb_find_nearest_thread(pattern->thread_list->
                                              thread[i].color,
                                              (EmbThread *) hus_colors,
                                              29);
        emb_write_i16(file, color_index);
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
