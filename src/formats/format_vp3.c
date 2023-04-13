/*
 * VP3 FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../embroidery_internal.h"

unsigned char*
vp3ReadString(FILE* file)
{
    short stringLength;
    unsigned char* charString = 0;
    if (!file) { printf("ERROR: format-vp3.c vp3ReadString(), file argument is null\n"); return 0; }
    embInt_read(file, ".", &stringLength, EMB_INT16_BIG);
    charString = (unsigned char*)malloc(stringLength);
    if (!charString) { printf("ERROR: format-vp3.c vp3ReadString(), cannot allocate memory for charString\n"); return 0; }
    fread(charString, 1, stringLength, file); /* TODO: check return value */
    return charString;
}

int
vp3Decode(unsigned char inputByte)
{
    if (inputByte > 0x80) {
        return (int)-((unsigned char)((~inputByte) + 1));
    }
    return ((int)inputByte);
}

short
vp3DecodeInt16(unsigned short inputByte)
{
    if (inputByte > 0x8000) {
        return -((short) ((~inputByte) + 1));
    }
    return ((short)inputByte);
}

vp3Hoop
vp3ReadHoopSection(FILE* file)
{
    vp3Hoop hoop;

    if (!file) { 
        printf("ERROR: format-vp3.c vp3ReadHoopSection(), file argument is null\n");
        hoop.bottom = 0;
        hoop.left = 0;
        hoop.right = 0;
        hoop.top = 0;
        hoop.threadLength = 0;
        hoop.unknown2 = 0;
        hoop.numberOfColors = 0;
        hoop.unknown3 = 0;
        hoop.unknown4 = 0;
        hoop.numberOfBytesRemaining = 0;

        hoop.xOffset = 0;
        hoop.yOffset = 0;

        hoop.byte1 = 0;
        hoop.byte2 = 0;
        hoop.byte3 = 0;
        hoop.right2 = 0;
        hoop.left2 = 0;
        hoop.bottom2 = 0;
        hoop.top2 = 0;
        hoop.height = 0;
        hoop.width = 0;
        return hoop; 
    }

    embInt_read(file, "hoop right", &(hoop.right), EMB_INT32_BIG);
    embInt_read(file, "hoop bottom", &(hoop.bottom), EMB_INT32_BIG);
    embInt_read(file, "hoop left", &(hoop.left), EMB_INT32_BIG);
    embInt_read(file, "hoop top", &(hoop.top), EMB_INT32_BIG);

    /* yes, it seems this is _not_ big endian */
    embInt_read(file, "thread length", &(hoop.threadLength), EMB_INT32_LITTLE);
    hoop.unknown2 = (char)fgetc(file);
    hoop.numberOfColors = (char)fgetc(file);
    embInt_read(file, "unknown3", &(hoop.unknown3), EMB_INT16_BIG);
    embInt_read(file, "unknown4", &(hoop.unknown4), EMB_INT32_BIG);
    embInt_read(file, "bytes remaining", &(hoop.numberOfBytesRemaining), EMB_INT32_BIG);

    embInt_read(file, "x offset", &(hoop.xOffset), EMB_INT32_BIG);
    embInt_read(file, "y offset", &(hoop.yOffset), EMB_INT32_BIG);

    hoop.byte1 = (char)fgetc(file);
    hoop.byte2 = (char)fgetc(file);
    hoop.byte3 = (char)fgetc(file);

    /* Centered hoop dimensions */
    embInt_read(file, "hoop right2", &(hoop.right2), EMB_INT32_BIG);
    embInt_read(file, "hoop left2", &(hoop.left2), EMB_INT32_BIG);
    embInt_read(file, "hoop bottom2", &(hoop.bottom2), EMB_INT32_BIG);
    embInt_read(file, "hoop top2", &(hoop.top2), EMB_INT32_BIG);

    hoop.width = fread_int32_be(file);
    hoop.height = fread_int32_be(file);
    return hoop;
}

char
readVp3(EmbPattern* pattern, FILE* file)
{
    unsigned char magicString[5];
    unsigned char some;
    unsigned char* softwareVendorString = 0;
    /* unsigned char v2, ..., v18; */
    unsigned char* anotherSoftwareVendorString = 0;
    int numberOfColors;
    long colorSectionOffset;
    unsigned char magicCode[6];
    short someShort;
    unsigned char someByte;
    int bytesRemainingInFile, hoopConfigurationOffset;
    unsigned char* fileCommentString = 0; /* some software writes used settings here */
    unsigned char* anotherCommentString = 0;
    int i;

    fread(magicString, 1, 5, file); /* %vsm% */ /* TODO: check return value */
    some = (char)fgetc(file); /* 0 */
    softwareVendorString = vp3ReadString(file);
    embInt_read(file, "someShort", &someShort, EMB_INT16_LITTLE);
    someByte = (char)fgetc(file);
    embInt_read(file, ".", &bytesRemainingInFile, EMB_INT32_LITTLE);
    fileCommentString = vp3ReadString(file);
    hoopConfigurationOffset = (int)ftell(file);

    vp3ReadHoopSection(file);

    anotherCommentString = vp3ReadString(file);

    /* TODO: review v1 thru v18 variables and use emb_unused() if needed */
    for (i = 0; i < 18; i++) {
        unsigned char v1;
        v1 = (char)fgetc(file);
        if (emb_verbose>1) {
            printf("v%d = %d\n", i, v1);
        }
    }

    fread(magicCode, 1, 6, file); /* 0x78 0x78 0x55 0x55 0x01 0x00 */ /* TODO: check return value */

    anotherSoftwareVendorString = vp3ReadString(file);

    embInt_read(file, ".", &numberOfColors, EMB_INT16_BIG);
    colorSectionOffset = (int)ftell(file);
    if (emb_verbose>1) {
        puts("LIBEMBROIDERY DEBUG");
        puts("Format vp3");
        printf("    some: %d\n", some);
        printf("    softwareVendorString: %s\n", softwareVendorString);
        printf("    someByte: %d\n", someByte);
        printf("    bytesRemainingInFile: %d\n", bytesRemainingInFile);
        printf("    hoop config offset: %d\n", hoopConfigurationOffset);
        printf("    another comment string: %s\n", anotherCommentString);
        printf("    another software vendor string: %s\n", anotherSoftwareVendorString);
        printf("    number of colors: %d\n", numberOfColors);
        printf("    color section offset: %ld\n", colorSectionOffset);
    }

    for (i = 0; i < numberOfColors; i++) {
        EmbThread t;
        char tableSize;
        int startX, startY, offsetToNextColorX, offsetToNextColorY;
        unsigned char* threadColorNumber, *colorName, *threadVendor;
        int unknownThreadString, numberOfBytesInColor;

        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        fseek(file, colorSectionOffset, SEEK_SET);
        printf("ERROR: format-vp3.c Color Check Byte #1: 0 == %d\n", (char)fgetc(file));
        printf("ERROR: format-vp3.c Color Check Byte #2: 5 == %d\n", (char)fgetc(file));
        printf("ERROR: format-vp3.c Color Check Byte #3: 0 == %d\n", (char)fgetc(file));
        embInt_read(file, ".", &colorSectionOffset, EMB_INT32_BIG);
        colorSectionOffset += ftell(file);
        embInt_read(file, ".", &startX, EMB_INT32_BIG);
        embInt_read(file, ".", &startY, EMB_INT32_BIG);
        embPattern_addStitchAbs(pattern, startX / 1000.0, -startY / 1000.0, JUMP, 1);

        tableSize = (char)fgetc(file);
        fseek(file, 1, SEEK_CUR);
        embColor_read(file, &(t.color), 3);
        embPattern_addThread(pattern, t);
        fseek(file, 6*tableSize - 1, SEEK_CUR);

        threadColorNumber = vp3ReadString(file);
        colorName = vp3ReadString(file);
        threadVendor = vp3ReadString(file);

        offsetToNextColorX = fread_int32_be(file);
        offsetToNextColorY = fread_int32_be(file);

        embInt_read(file, "unknown thread string", &unknownThreadString, EMB_INT16_BIG);
        fseek(file, unknownThreadString, SEEK_CUR);
        numberOfBytesInColor = fread_int32_be(file);
        fseek(file, 0x3, SEEK_CUR);
        
        if (emb_verbose>1) {
            printf("number of bytes in color: %d\n", numberOfBytesInColor);
            printf("thread color number: %s\n", threadColorNumber);
            printf("offset to next color x: %d\n", offsetToNextColorX);
            printf("offset to next color y: %d\n", offsetToNextColorY);
            printf("color name: %s\n", colorName);
            printf("thread vendor: %s\n", threadVendor);
            printf("fileCommentString: %s\n", fileCommentString);
        }

        while (ftell(file) < colorSectionOffset - 1) {
            int lastFilePosition = ftell(file);
            int x = vp3Decode((char)fgetc(file));
            int y = vp3Decode((char)fgetc(file));
            short readIn;
            if (x == 0x80) {
                switch (y) {
                    case 0x00:
                    case 0x03:
                        break;
                    case 0x01:
                        embInt_read(file, ".", &readIn, EMB_INT16_BIG);
                        x = vp3DecodeInt16(readIn);
                        embInt_read(file, ".", &readIn, EMB_INT16_BIG);
                        y = vp3DecodeInt16(readIn);
                        fseek(file, 2, SEEK_CUR);
                        embPattern_addStitchRel(pattern, x/ 10.0, y / 10.0, TRIM, 1);
                        break;
                    default:
                        break;
                }
            } else {
                embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, NORMAL, 1);
            }

            if (ftell(file) == lastFilePosition) {
                printf("ERROR: format-vp3.c could not read stitch block in entirety\n");
                return 0;
            }
        }
        if (i + 1 < numberOfColors) {
            embPattern_addStitchRel(pattern, 0, 0, STOP, 1);
        }
    }
    embPattern_flipVertical(pattern);
    return 1;
}

void
vp3WriteStringLen(FILE* file, const char* str, int len)
{
    binaryWriteUShortBE(file, len);
    fwrite(str, 1, len, file);
}

void
vp3WriteString(FILE* file, const char* str)
{
    vp3WriteStringLen(file, str, strlen(str));
}

void
vp3PatchByteCount(FILE* file, int offset, int adjustment)
{
    int currentPos = ftell(file);
    fseek(file, offset, SEEK_SET);
    printf("Patching byte count: %d\n", currentPos - offset + adjustment);
    binaryWriteIntBE(file, currentPos - offset + adjustment);
    fseek(file, currentPos, SEEK_SET);
}

char
writeVp3(EmbPattern* pattern, FILE* file)
{
    short a;
    EmbRect bounds;
    int a_int, remainingBytesPos, remainingBytesPos2;
    int colorSectionStitchBytes, first = 1, i, numberOfColors;
    EmbColor color;
    color.r = 0xFE;
    color.g = 0xFE;
    color.b = 0xFE;

    bounds = embPattern_calcBoundingBox(pattern);

    embPattern_correctForMaxStitchLength(pattern, 3200.0, 3200.0); /* VP3 can encode signed 16bit deltas */

    embPattern_flipVertical(pattern);

    fwrite("%vsm%\0", 1, 6, file);
    vp3WriteString(file, "Embroidermodder");
    fwrite("\x00\x02\x00", 1, 3, file);

    remainingBytesPos = ftell(file);
    binaryWriteInt(file, 0); /* placeholder */
    vp3WriteString(file, "");
    binaryWriteIntBE(file, bounds.right * 1000);
    binaryWriteIntBE(file, bounds.bottom * 1000);
    binaryWriteIntBE(file, bounds.left * 1000);
    binaryWriteIntBE(file, bounds.top * 1000);
    binaryWriteInt(file, 0); /* this would be some (unknown) function of thread length */
    fputc(0, file);

    numberOfColors = embPattern_color_count(pattern, color);
    fputc(numberOfColors, file);
    fwrite("\x0C\x00\x01\x00\x03\x00", 1, 6, file);

    remainingBytesPos2 = ftell(file);
    binaryWriteInt(file, 0); /* placeholder */

    binaryWriteIntBE(file, 0); /* origin X */
    binaryWriteIntBE(file, 0); /* origin Y */
    fpad(file, 0, 3);

    binaryWriteIntBE(file, bounds.right * 1000);
    binaryWriteIntBE(file, bounds.bottom * 1000);
    binaryWriteIntBE(file, bounds.left * 1000);
    binaryWriteIntBE(file, bounds.top * 1000);

    binaryWriteIntBE(file, (bounds.right - bounds.left) * 1000);
    binaryWriteIntBE(file, (bounds.bottom - bounds.top) * 1000);

    vp3WriteString(file, "");
    a = 25700;
    embInt_write(file, ".", &a, EMB_INT16_BIG);
    a_int = 4096;
    embInt_write(file, ".", &a_int, EMB_INT32_BIG);
    a_int = 0;
    embInt_write(file, ".", &a_int, EMB_INT32_BIG);
    embInt_write(file, ".", &a_int, EMB_INT32_BIG);
    a_int = 4096;
    embInt_write(file, ".", &a_int, EMB_INT32_BIG);

    fwrite("xxPP\x01\0", 1, 6, file);
    vp3WriteString(file, "");
    embInt_write(file, ".", &numberOfColors, EMB_INT16_BIG);

    for (i=0; i<pattern->stitch_list->count; i++) {
        char colorName[8] = { 0 };
        EmbReal lastX, lastY;
        int colorSectionLengthPos, j;
        EmbStitch s;
        int lastColor;

        j = 0;
        s.x = 0.0;
        s.y = 0.0;
        s.color = 0;
        s.flags = 0;

        if (!first) {
            fputc(0, file);
        }
        fputc(0, file);
        fputc(5, file);
        fputc(0, file);

        colorSectionLengthPos = ftell(file);
        binaryWriteInt(file, 0); /* placeholder */

        /*
        pointer = mainPointer;
        color = pattern->thread_list->thread[pointer->stitch.color].color;

        if (first && pointer->stitch.flags & JUMP && pointer->next->stitch.flags & JUMP) {
            pointer = pointer->next;
        }

        s = pointer->stitch;
        */
        if (emb_verbose>1) {
            printf("%d\n", j);
            printf("format-vp3.c DEBUG %d, %f, %f\n", s.flags, s.x, s.y);
        }
        binaryWriteIntBE(file, s.x * 1000);
        binaryWriteIntBE(file, -s.y * 1000);
        /* pointer = pointer->next; */

        first = 0;

        lastX = s.x;
        lastY = s.y;
        lastColor = s.color;
        if (emb_verbose>1) {
            printf("last %f %f %d\n", lastX, lastY, lastColor);
        }

        fwrite("\x01\x00", 1, 2, file);

        printf("format-vp3.c writeVp3(), switching to color (%d, %d, %d)\n", color.r, color.g, color.b);
        embColor_write(file, color, 4);

        fwrite("\x00\x00\x05", 1, 3, file);
        fputc(40, file);

        vp3WriteString(file, "");

        sprintf(colorName, "#%02x%02x%02x", color.b, color.g, color.r);

        vp3WriteString(file, colorName);
        vp3WriteString(file, "");

        binaryWriteIntBE(file, 0);
        binaryWriteIntBE(file, 0);

        vp3WriteStringLen(file, "\0", 1);

        colorSectionStitchBytes = ftell(file);
        binaryWriteInt(file, 0); /* placeholder */

        fputc(10, file);
        fputc(246, file);
        fputc(0, file);

        /*
        for (j=i; j<pattern->stitch_list->count; j++) {
        while (pointer) {
            short dx, dy;

            EmbStitch s = pointer->stitch;
            if (s.color != lastColor) {
                break;
            }
            if (s.flags & END || s.flags & STOP) {
                break;
            }
            dx = (s.x - lastX) * 10;
            dy = (s.y - lastY) * 10;
            // output is in ints, ensure rounding errors do not sum up.
            lastX = lastX + dx / 10.0;
            lastY = lastY + dy / 10.0;

            if (dx < -127 || dx > 127 || dy < -127 || dy > 127) {
                fputc(128, file);
                fputc(1, file);
                embInt_write(file, ".", &dx, EMB_INT16_BIG);
                embInt_write(file, ".", &dy, EMB_INT16_BIG);
                fputc(128, file);
                fputc(2, file);
            }
            else {
                char b[2];
                b[0] = dx;
                b[1] = dy;
                fwrite(b, 1, 2, file);
            }

            pointer = pointer->next;
        }
        */

        vp3PatchByteCount(file, colorSectionStitchBytes, -4);
        vp3PatchByteCount(file, colorSectionLengthPos, -3);

        /* mainPointer = pointer; */
    }

    vp3PatchByteCount(file, remainingBytesPos2, -4);
    vp3PatchByteCount(file, remainingBytesPos, -4);

    embPattern_flipVertical(pattern);
    return 0;
}
