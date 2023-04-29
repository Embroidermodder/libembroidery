/*
 * PES FORMAT
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

/**

\subsection Brother Embroidery Format (.pes)
\addindex pes
\addindex Brother

The Brother pes format is stitch-only.
 */

const char *pes_version_strings[] = {
    "#PES0001",
    "#PES0020",
    "#PES0022",
    "#PES0030",
    "#PES0040",
    "#PES0050",
    "#PES0055",
    "#PES0056",
    "#PES0060",
    "#PES0070",
    "#PES0080",
    "#PES0090",
    "#PES0100",
};


/* ---------------------------------------------------------------- */
/* format pes */

int pes_version = PES0001;

char
readPes(EmbPattern* pattern, const char *fileName, FILE* file)
{
    int pecstart, numColors, x, version, i;
    char signature[9];
    fread(signature, 1, 8, file);
    signature[8] = 0;
    embInt_read(file, "pecstart", &pecstart, EMB_INT32_LITTLE);

    version = 0;
    for (i=0; i<N_PES_VERSIONS; i++) {
        if (!strcmp(signature, pes_version_strings[i])) {
            version = i;
            break;
        }
    }

    if (version >= PES0040) {
        fseek(file, 4, SEEK_CUR);
        readDescriptions(file, pattern);
    }

    switch (version) {
    case PES0100:
        readPESHeaderV10(file, pattern);
        break;
    case PES0090:
        readPESHeaderV9(file, pattern);
        break;
    case PES0080:
        readPESHeaderV8(file, pattern);
        break;
    case PES0070:
        readPESHeaderV7(file, pattern);
        break;
    case PES0060:
        readPESHeaderV6(file, pattern);
        break;
    case PES0056:
    case PES0055:
    case PES0050:
        readPESHeaderV5(file, pattern);
        break;
    default:
        break;
    }

    if (emb_verbose>1) {
        printf("debug information for reading fileName: %s\n", fileName);
        printf("pecstart = %d\n", pecstart);
    }

    /* fseek(file, pecstart + 48, SEEK_SET);
     * This seems wrong based on the readPESHeader functions. */
    fseek(file, pecstart, SEEK_SET);

    numColors = fgetc(file) + 1;
    for (x = 0; x < numColors; x++) {
        int color_index = fgetc(file);
        if (color_index >= pecThreadCount) {
            color_index = 0;
        }
        embPattern_addThread(pattern, pecThreads[color_index]);
    }

    fseek(file, pecstart + 528, SEEK_SET);
    readPecStitches(pattern, file);

    embPattern_flipVertical(pattern);

    return 1;
}

void
readDescriptions(FILE *file, EmbPattern* pattern)
{
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    /*
    int DesignStringLength;
    int categoryStringLength;
    int authorStringLength;
    int keywordsStringLength;
    int commentsStringLength;
    DesignStringLength = fgetc();
    String DesignName = readString(DesignStringLength);
    pattern.setName(DesignName);
    categoryStringLength = fgetc();
    String Category = readString(categoryStringLength);
    pattern.setCategory(Category);
    authorStringLength = fgetc();
    String Author = readString(authorStringLength);
    pattern.setAuthor(Author);
    keywordsStringLength = fgetc();
    String keywords = readString(keywordsStringLength);
    pattern.setKeywords(keywords);
    commentsStringLength = fgetc();
    String Comments = readString(commentsStringLength);
    pattern.setComments(Comments);
    */
}

void
readPESHeaderV5(FILE *file, EmbPattern* pattern)
{
    int fromImageStringLength;
    fseek(file, 24, SEEK_CUR);
    fromImageStringLength = fgetc(file);
    fseek(file, fromImageStringLength, SEEK_CUR);
    fseek(file, 24, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV6(FILE *file, EmbPattern* pattern)
{
    fseek(file, 36, SEEK_CUR);
    readImageString(file, pattern);
    fseek(file, 24, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV7(FILE *file, EmbPattern* pattern)
{
    fseek(file, 36, SEEK_CUR);
    readImageString(file, pattern);
    fseek(file, 24, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}
    
void
readPESHeaderV8(FILE *file, EmbPattern* pattern)
{
    fseek(file, 38, SEEK_CUR);
    readImageString(file, pattern);
    fseek(file, 26, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV9(FILE *file, EmbPattern* pattern)
{
    fseek(file, 14, SEEK_CUR);
    readHoopName(file, pattern);
    fseek(file, 30, SEEK_CUR);
    readImageString(file, pattern);
    fseek(file, 34, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readPESHeaderV10(FILE *file, EmbPattern* pattern)
{
    fseek(file, 14, SEEK_CUR);
    readHoopName(file, pattern);
    fseek(file, 38, SEEK_CUR);
    readImageString(file, pattern);
    fseek(file, 34, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

void
readHoopName(FILE* file, EmbPattern* pattern)
{
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    /*
    int hoopNameStringLength = fgetc(file);
    String hoopNameString = readString(hoopNameStringLength);
    if (hoopNameString.length() != 0) {
        pattern.setMetadata("hoop_name", hoopNameString);
    }
    */
}

void
readImageString(FILE* file, EmbPattern* pattern)
{
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    /*
    int fromImageStringLength = fgetc(file);
    String fromImageString = readString(fromImageStringLength);
    if (fromImageString.length() != 0) {
        pattern.setMetadata("image_file", fromImageString);
    }
    */
}

void
readProgrammableFills(FILE* file, EmbPattern* pattern)
{
    int numberOfProgrammableFillPatterns;
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    numberOfProgrammableFillPatterns = fread_int16(file);
    if (numberOfProgrammableFillPatterns != 0) {
        return;
    }
}

void
readMotifPatterns(FILE* file, EmbPattern* pattern)
{
    int numberOfMotifPatterns;
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    numberOfMotifPatterns = fread_int16(file);
    if (numberOfMotifPatterns != 0) {
        return;
    }
}

void
readFeatherPatterns(FILE* file, EmbPattern* pattern)
{
    int featherPatternCount;
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    featherPatternCount = fread_int16(file);
    if (featherPatternCount != 0) {
        return;
    }
}
    
void
readThreads(FILE* file, EmbPattern* pattern)
{
    int numberOfColors, i;
    if (emb_verbose > 1) {
        printf("Called with: (%p, %p)", (void*)file, (void*)pattern);
    }
    numberOfColors = fread_int16(file);
    for (i=0; i<numberOfColors; i++) {
        EmbThread thread;
        int color_code_length;
        int descriptionStringLength;
        int brandStringLength;
        int threadChartStringLength;
        color_code_length = fgetc(file);
        /* strcpy(thread.color_code, readString(color_code_length)); */
        thread.color.r = fgetc(file);
        thread.color.g = fgetc(file);
        thread.color.b = fgetc(file);
        fseek(file, 5, SEEK_CUR);
        descriptionStringLength = fgetc(file);
        /* strcpy(thread.description, readString(descriptionStringLength)); */

        brandStringLength = fgetc(file);
        /* strcpy(thread.brand, readString(brandStringLength)); */

        threadChartStringLength = fgetc(file);
        /* strcpy(thread.threadChart, readString(threadChartStringLength)); */

        if (emb_verbose > 1) {
            printf("color code length: %d\n", color_code_length);
            printf("description string length: %d\n", descriptionStringLength);
            printf("brand string length: %d\n", brandStringLength);
            printf("thread chart string length: %d\n", threadChartStringLength);
        }
        embPattern_addThread(pattern, thread);
    }
}


void
pesWriteSewSegSection(EmbPattern* pattern, FILE* file) {
    /* TODO: pointer safety */
    short* colorInfo = 0;
    int flag = 0;
    int count = 0;
    int colorCode = -1;
    int stitchType = 0;
    int blockCount = 0;
    int colorCount = 0;
    int newColorCode = 0;
    int colorInfoIndex = 0;
    int i, j;
    EmbRect bounds = embPattern_calcBoundingBox(pattern);

    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbColor color;
        EmbStitch st = pattern->stitch_list->stitch[i];
        flag = st.flags;
        if (st.color < pattern->thread_list->count) {
            color = pattern->thread_list->thread[st.color].color;
        }
        else {
            color = pecThreads[0].color;
        }
        newColorCode = embThread_findNearestThread(color, (EmbThread*)pecThreads, pecThreadCount);
        if (newColorCode != colorCode) {
            colorCount++;
            colorCode = newColorCode;
        }
        while (i < pattern->stitch_list->count && (flag == st.flags)) {
            st = pattern->stitch_list->stitch[i];
            count++;
            i++;
        }
        blockCount++;
    }

    binaryWriteShort(file, (short)blockCount); /* block count */
    binaryWriteUShort(file, 0xFFFF);
    binaryWriteShort(file, 0x00);

    binaryWriteShort(file, 0x07); /* string length */
    fwrite("CSewSeg", 1, 7, file);
    
    if (colorCount > 1000) {
        puts("Color count exceeds 1000 this is likely an error. Truncating to 1000.");
        colorCount = 1000;
    }

    colorInfo = (short *) calloc(colorCount * 2, sizeof(short));
    colorCode = -1;
    blockCount = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbColor color;
        EmbStitch st;
        st = pattern->stitch_list->stitch[i];
        j = i;
        flag = st.flags;
        color = pattern->thread_list->thread[st.color].color;
        newColorCode = embThread_findNearestThread(color, (EmbThread*)pecThreads, pecThreadCount);
        if (newColorCode != colorCode) {
            if (colorInfoIndex+2 > colorCount) {
                puts("Ran out of memory for color info.");
                break;
            }
            colorInfo[colorInfoIndex++] = (short)blockCount;
            colorInfo[colorInfoIndex++] = (short)newColorCode;
            colorCode = newColorCode;
        }
        count = 0;
        while (j < pattern->stitch_list->count && (flag == st.flags)) {
            st = pattern->stitch_list->stitch[j];
            count++;
            j++;
        }
        if (flag & JUMP) {
            stitchType = 1;
        }
        else {
            stitchType = 0;
        }

        binaryWriteShort(file, (short)stitchType); /* 1 for jump, 0 for normal */
        binaryWriteShort(file, (short)colorCode); /* color code */
        binaryWriteShort(file, (short)count); /* stitches in block */
        j = i;
        while (j < pattern->stitch_list->count && (flag == st.flags)) {
            st = pattern->stitch_list->stitch[j];
            binaryWriteShort(file, (short)(st.x - bounds.left));
            binaryWriteShort(file, (short)(st.y + bounds.top));
        }
        if (j < pattern->stitch_list->count ) {
            binaryWriteUShort(file, 0x8003);
        }
        blockCount++;
        i = j;
    }
    binaryWriteShort(file, (short)colorCount);
    for (i = 0; i < colorCount; i++) {
        binaryWriteShort(file, colorInfo[i * 2]);
        binaryWriteShort(file, colorInfo[i * 2 + 1]);
    }
    binaryWriteInt(file, 0);
    safe_free(colorInfo);
}

void
pesWriteEmbOneSection(EmbPattern* pattern, FILE* file) {
    /* TODO: pointer safety */
    float x, width, height;
    int hoopHeight = 1800, hoopWidth = 1300;
    EmbRect bounds;
    binaryWriteShort(file, 0x07); /* string length */
    fwrite("CEmbOne", 1, 7, file);
    bounds = embPattern_calcBoundingBox(pattern);

    fpad(file, 0, 16);

    /* AffineTransform */
    x = 1.0;
    embInt_write(file, ".", &x, EMB_INT32_LITTLE);
    x = 0.0;
    embInt_write(file, ".", &x, EMB_INT32_LITTLE);
    x = 0.0;
    embInt_write(file, ".", &x, EMB_INT32_LITTLE);
    x = 1.0;
    embInt_write(file, ".", &x, EMB_INT32_LITTLE);
    width = bounds.right - bounds.left;
    height = bounds.bottom - bounds.top;
    x = (float)((width - hoopWidth) / 2);
    embInt_write(file, ".", &x, EMB_INT32_LITTLE);
    x = (float)((height + hoopHeight) / 2);
    embInt_write(file, ".", &x, EMB_INT32_LITTLE);

    binaryWriteShort(file, 1);
    binaryWriteShort(file, 0); /* Translate X */
    binaryWriteShort(file, 0); /* Translate Y */
    binaryWriteShort(file, (short)width);
    binaryWriteShort(file, (short)height);

    fpad(file, 0, 8);
    /*WriteSubObjects(br, pes, SubBlocks); */
}

char
writePes(EmbPattern* pattern,  const char *fileName, FILE* file)
{
    int pecLocation;
    embPattern_flipVertical(pattern);
    embPattern_scale(pattern, 10.0);
    fwrite("#PES0001", 1, 8, file);
    /* WRITE PECPointer 32 bit int */
    binaryWriteInt(file, 0x00);

    binaryWriteShort(file, 0x01);
    binaryWriteShort(file, 0x01);

    /* Write object count */
    binaryWriteShort(file, 0x01);
    binaryWriteUShort(file, 0xFFFF); /* command */
    binaryWriteShort(file, 0x00); /* unknown */

    pesWriteEmbOneSection(pattern, file);
    pesWriteSewSegSection(pattern, file);

    pecLocation = ftell(file);
    fseek(file, 0x08, SEEK_SET);
    fputc((unsigned char)(pecLocation & 0xFF), file);
    fputc((unsigned char)(pecLocation >> 8) & 0xFF, file);
    fputc((unsigned char)(pecLocation >> 16) & 0xFF, file);
    fseek(file, 0x00, SEEK_END);
    writePecStitches(pattern, file, fileName);
    return 1;
}
