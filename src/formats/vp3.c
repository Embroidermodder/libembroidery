/*
 * VP3 FORMAT
 * Pfaff Embroidery Format (.vp3)
 *
 * The Pfaff vp3 format is stitch-only.
 */

#include <stdlib.h>
#include <string.h>

#include "embroidery.h"

uint8_t *vp3ReadString(FILE *file)
{
    short stringLength;
    uint8_t *charString = 0;
    if (!file) {
        printf("ERROR: format-vp3.c vp3ReadString(), file argument is null\n");
        return 0;
    }
    stringLength = emb_read_i16be(file);
    charString = (uint8_t *) malloc(stringLength);
    if (!charString) {
        printf
            ("ERROR: format-vp3.c vp3ReadString(), cannot allocate memory for charString\n");
        return 0;
    }
    fread(charString, 1, stringLength, file);   /* TODO: check return value */
    return charString;
}

int vp3Decode(uint8_t inputByte)
{
    if (inputByte > 0x80) {
        return (int)-((uint8_t) ((~inputByte) + 1));
    }
    return ((int)inputByte);
}

short vp3DecodeInt16(uint16_t inputByte)
{
    if (inputByte > 0x8000) {
        return -((int16_t) ((~inputByte) + 1));
    }
    return ((int16_t) inputByte);
}

vp3Hoop vp3ReadHoopSection(FILE *file)
{
    vp3Hoop hoop;

    if (!file) {
        printf
            ("ERROR: format-vp3.c vp3ReadHoopSection(), file argument is null\n");
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

    hoop.right = emb_read_i32be(file);
    hoop.bottom = emb_read_i32be(file);
    hoop.left = emb_read_i32be(file);
    hoop.top = emb_read_i32be(file);

    /* yes, it seems this is _not_ big endian */
    hoop.threadLength = emb_read_i32(file);
    hoop.unknown2 = (char)fgetc(file);
    hoop.numberOfColors = (char)fgetc(file);
    hoop.unknown3 = emb_read_i16be(file);
    hoop.unknown4 = emb_read_i32be(file);
    hoop.numberOfBytesRemaining = emb_read_i32be(file);

    hoop.xOffset = emb_read_i32be(file);
    hoop.yOffset = emb_read_i32be(file);

    hoop.byte1 = (char)fgetc(file);
    hoop.byte2 = (char)fgetc(file);
    hoop.byte3 = (char)fgetc(file);

    /* Centered hoop dimensions */
    hoop.right2 = emb_read_i32be(file);
    hoop.left2 = emb_read_i32be(file);
    hoop.bottom2 = emb_read_i32be(file);
    hoop.top2 = emb_read_i32be(file);

    hoop.width = emb_read_i32be(file);
    hoop.height = emb_read_i32be(file);
    return hoop;
}

int8_t readVp3(EmbPattern *pattern, FILE *file)
{
    uint8_t magicString[5];
    uint8_t some;
    uint8_t *softwareVendorString = 0;
    /* uint8_t v2, ..., v18; */
    uint8_t *anotherSoftwareVendorString = 0;
    int numberOfColors;
    long colorSectionOffset;
    uint8_t magicCode[6];
    short someShort;
    uint8_t someByte;
    int bytesRemainingInFile, hoopConfigurationOffset;
    uint8_t *fileCommentString = 0;     /* some software writes used settings here */
    uint8_t *anotherCommentString = 0;
    int i;

    fread(magicString, 1, 5, file);     /* %vsm% *//* TODO: check return value */
    some = emb_read_i8(file);         /* 0 */
    softwareVendorString = vp3ReadString(file);
    someShort = emb_read_i16(file);
    someByte = emb_read_i8(file);
    bytesRemainingInFile = emb_read_i32(file);
    fileCommentString = vp3ReadString(file);
    hoopConfigurationOffset = (int)ftell(file);
    
    vp3ReadHoopSection(file);

    anotherCommentString = vp3ReadString(file);
    if (emb_verbose > 0) {
        printf("softwareVendorString = \"%s\"\n", softwareVendorString);
        printf("hoopConfigurationOffset = %d\n", hoopConfigurationOffset);
        printf("anotherCommentString = \"%s\"\n", anotherCommentString);
    }
    safe_free(softwareVendorString);
    safe_free(anotherCommentString);

    /* TODO: review v1 thru v18 variables and use emb_unused() if needed */
    for (i = 0; i < 18; i++) {
        uint8_t v1;
        v1 = (char)fgetc(file);
        if (emb_verbose > 1) {
            printf("v%d = %d\n", i, v1);
        }
    }

    /* TODO: check return value */
    /* 0x78 0x78 0x55 0x55 0x01 0x00 */
    if (fread(magicCode, 1, 6, file) != 6) {
        puts("ERROR: Failed to read magicCode.");
        return 0;
    }

    anotherSoftwareVendorString = vp3ReadString(file);
    if (emb_verbose > 0) {
        printf("anotherSoftwareVendorString = \"%s\"\n", anotherSoftwareVendorString);
    }
    safe_free(anotherSoftwareVendorString);

    numberOfColors = emb_read_i16be(file);
    colorSectionOffset = (int)ftell(file);

    for (i = 0; i < numberOfColors; i++) {
        EmbThread t;
        int8_t tableSize;
        int startX, startY, offsetToNextColorX, offsetToNextColorY;
        uint8_t *threadColorNumber, *colorName, *threadVendor;
        int unknownThreadString, numberOfBytesInColor;

        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        fseek(file, colorSectionOffset, SEEK_SET);
        printf("ERROR: format-vp3.c Color Check Byte #1: 0 == %d\n",
               (char)fgetc(file));
        printf("ERROR: format-vp3.c Color Check Byte #2: 5 == %d\n",
               (char)fgetc(file));
        printf("ERROR: format-vp3.c Color Check Byte #3: 0 == %d\n",
               (char)fgetc(file));
        colorSectionOffset = emb_read_i32be(file);
        colorSectionOffset += ftell(file);
        startX = emb_read_i32be(file);
        startY = emb_read_i32be(file);
        emb_add_stitch_abs(pattern, startX / 1000.0, -startY / 1000.0, JUMP, 1);

        tableSize = (char)fgetc(file);
        fseek(file, 1, SEEK_CUR);
        embColor_read(file, &(t.color), 3);
        emb_add_thread(pattern, t);
        fseek(file, 6 * tableSize - 1, SEEK_CUR);

        threadColorNumber = vp3ReadString(file);
        colorName = vp3ReadString(file);
        threadVendor = vp3ReadString(file);

        offsetToNextColorX = emb_read_i32be(file);
        offsetToNextColorY = emb_read_i32be(file);

        unknownThreadString = emb_read_i16be(file);
        fseek(file, unknownThreadString, SEEK_CUR);
        numberOfBytesInColor = emb_read_i32be(file);
        fseek(file, 0x3, SEEK_CUR);

        if (emb_verbose > 1) {
            printf("number of bytes in color: %d\n", numberOfBytesInColor);
            printf("thread color number: %s\n", threadColorNumber);
            printf("offset to next color x: %d\n", offsetToNextColorX);
            printf("offset to next color y: %d\n", offsetToNextColorY);
            printf("color name: %s\n", colorName);
            printf("thread vendor: %s\n", threadVendor);
            printf("fileCommentString: %s\n", fileCommentString);
        }

        safe_free(threadColorNumber);
        safe_free(colorName);
        safe_free(threadVendor);

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
                case 0x01:{
                        readIn = emb_read_i16be(file);
                        x = vp3DecodeInt16(readIn);
                        readIn = emb_read_i16be(file);
                        y = vp3DecodeInt16(readIn);
                        fseek(file, 2, SEEK_CUR);
                        emb_add_stitch(pattern, x / 10.0, y / 10.0, TRIM, 1);
                        break;
                    }
                default:
                    break;
                }
            } else {
                emb_add_stitch(pattern, x / 10.0, y / 10.0, NORMAL, 1);
            }

            if (ftell(file) == lastFilePosition) {
                printf
                    ("ERROR: format-vp3.c could not read stitch block in entirety\n");
                return 0;
            }
        }
        if (i + 1 < numberOfColors) {
            emb_add_stitch(pattern, 0, 0, STOP, 1);
        }
    }
    safe_free(fileCommentString);
    emb_flip_vertical(pattern);
    return 1;
}

void vp3WriteStringLen(FILE *file, const int8_t *str, int len)
{
    emb_write_u16be(file, len);
    fwrite(str, 1, len, file);
}

void vp3WriteString(FILE *file, const int8_t *str)
{
    vp3WriteStringLen(file, str, strlen(str));
}

void vp3PatchByteCount(FILE *file, int offset, int adjustment)
{
    int currentPos = ftell(file);
    fseek(file, offset, SEEK_SET);
    printf("Patching byte count: %d\n", currentPos - offset + adjustment);
    emb_write_i32be(file, currentPos - offset + adjustment);
    fseek(file, currentPos, SEEK_SET);
}

int8_t writeVp3(EmbPattern *pattern, FILE *file)
{
    EmbRect bounds;
    int remainingBytesPos, remainingBytesPos2;
    int colorSectionStitchBytes, first = 1, i, numberOfColors;
    EmbColor color;
    color.r = 0xFE;
    color.g = 0xFE;
    color.b = 0xFE;

    bounds = emb_bounds(pattern);

    emb_correctForMaxStitchLength(pattern, 3200.0, 3200.0);    /* VP3 can encode signed 16bit deltas */

    emb_flip_vertical(pattern);

    fwrite("%vsm%\0", 1, 6, file);
    vp3WriteString(file, "Embroidermodder");
    fwrite("\x00\x02\x00", 1, 3, file);

    remainingBytesPos = ftell(file);
    emb_write_i32(file, 0);     /* placeholder */
    vp3WriteString(file, "");
    emb_write_i32be(file, (bounds.x + bounds.w) * 1000);
    emb_write_i32be(file, (bounds.y + bounds.h) * 1000);
    emb_write_i32be(file, bounds.x * 1000);
    emb_write_i32be(file, bounds.y * 1000);
    emb_write_i32(file, 0);     /* this would be some (unknown) function of thread length */
    fputc(0, file);

    numberOfColors = emb_color_count(pattern, color);
    fputc(numberOfColors, file);
    fwrite("\x0C\x00\x01\x00\x03\x00", 1, 6, file);

    remainingBytesPos2 = ftell(file);
    emb_write_i32(file, 0);     /* placeholder */

    emb_write_i32be(file, 0);   /* origin X */
    emb_write_i32be(file, 0);   /* origin Y */
    fpad(file, 0, 3);

    emb_write_i32be(file, (bounds.x + bounds.w) * 1000);
    emb_write_i32be(file, (bounds.y + bounds.h) * 1000);
    emb_write_i32be(file, bounds.x * 1000);
    emb_write_i32be(file, bounds.y * 1000);

    emb_write_i32be(file, bounds.w * 1000);
    emb_write_i32be(file, bounds.h * 1000);

    vp3WriteString(file, "");
    emb_write_i16be(file, 25700);
    emb_write_i32be(file, 4096);
    emb_write_i32be(file, 0);
    emb_write_i32be(file, 0);
    emb_write_i32be(file, 4096);

    fwrite("xxPP\x01\0", 1, 6, file);
    vp3WriteString(file, "");
    emb_write_i16be(file, numberOfColors);

    for (i = 0; i < pattern->stitch_list->count; i++) {
        int8_t colorName[8] = { 0 };
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
        emb_write_i32(file, 0); /* placeholder */

        /*
           pointer = mainPointer;
           color = pattern->thread_list->thread[pointer->stitch.color].color;

           if (first && pointer->stitch.flags & JUMP && pointer->next->stitch.flags & JUMP) {
           pointer = pointer->next;
           }

           s = pointer->stitch;
         */
        if (emb_verbose > 1) {
            printf("%d\n", j);
            printf("format-vp3.c DEBUG %d, %f, %f\n", s.flags, s.x, s.y);
        }
        emb_write_i32be(file, s.x * 1000);
        emb_write_i32be(file, -s.y * 1000);
        /* pointer = pointer->next; */

        first = 0;

        lastX = s.x;
        lastY = s.y;
        lastColor = s.color;
        if (emb_verbose > 1) {
            printf("last %f %f %d\n", lastX, lastY, lastColor);
        }

        fwrite("\x01\x00", 1, 2, file);

        printf
            ("format-vp3.c writeVp3(), switching to color (%d, %d, %d)\n",
             color.r, color.g, color.b);
        embColor_write(file, color, 4);

        fwrite("\x00\x00\x05", 1, 3, file);
        fputc(40, file);

        vp3WriteString(file, "");

        sprintf(colorName, "#%02x%02x%02x", color.b, color.g, color.r);

        vp3WriteString(file, colorName);
        vp3WriteString(file, "");

        emb_write_i32be(file, 0);
        emb_write_i32be(file, 0);

        vp3WriteStringLen(file, "\0", 1);

        colorSectionStitchBytes = ftell(file);
        emb_write_i32(file, 0); /* placeholder */

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
           emb_write_i16be(file, dx);
           emb_write_i16be(file, dy);
           fputc(128, file);
           fputc(2, file);
           }
           else {
           int8_t b[2];
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

    emb_flip_vertical(pattern);
    return 0;
}
