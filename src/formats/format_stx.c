/*
 * STX FORMAT
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
\subsection Data Stitch Embroidery Format (.stx)
\addindex stx

The Data Stitch stx format is stitch-only.

 */

int
stxReadThread(StxThread* thread, FILE* file)
{
    int j, colorNameLength, sectionNameLength;
    int somethingSomething, somethingSomething2, somethingElse, numberOfOtherDescriptors; /* TODO: determine what these represent */
    int codeLength = 0;
    char* codeBuff = 0;
    char* codeNameBuff = 0;
    EmbColor col;
    char* sectionNameBuff = 0;

    if (!thread) {
        printf("ERROR: format-stx.c stxReadThread(), thread argument is null\n");
        return 0;
    }
    if (!file) { printf("ERROR: format-stx.c stxReadThread(), file argument is null\n"); return 0; }

    codeLength = fgetc(file);
    codeBuff = (char*)malloc(codeLength);
    if (!codeBuff) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeBuff\n");
        return 0;
    }
    /* TODO: check return value */
    fread(codeBuff, 1, codeLength, file);
    thread->colorCode = codeBuff;
    colorNameLength = fgetc(file);
    codeNameBuff = (char*)malloc(colorNameLength);
    if (!codeNameBuff) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeNameBuff\n");
        return 0;
    }
    fread((unsigned char*)codeNameBuff, 1, colorNameLength, file); /* TODO: check return value */
    thread->colorName = codeNameBuff;

    embColor_read(file, &col, 4);
    if (emb_verbose>1) {
        printf("col red: %d\n", col.r);
        printf("col green: %d\n", col.g);
        printf("col blue: %d\n", col.b);
    }

    sectionNameLength = fgetc(file);
    sectionNameBuff = (char*)malloc(sectionNameLength);
    if (!sectionNameBuff) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for sectionNameBuff\n");
        return 0;
    }
    fread((unsigned char*)sectionNameBuff, 1, sectionNameLength, file); /* TODO: check return value */
    thread->sectionName = sectionNameBuff;

    embInt_read(file, ".", &somethingSomething, EMB_INT32_LITTLE);
    embInt_read(file, ".", &somethingSomething2, EMB_INT32_LITTLE);
    embInt_read(file, ".", &somethingElse, EMB_INT32_LITTLE);
    numberOfOtherDescriptors = fread_int16(file);
    if (emb_verbose>1) {
        printf("somethingSomething: %d", somethingSomething);
        printf("somethingSomething2: %d", somethingSomething2);
        printf("somethingElse: %d", somethingElse);
        printf("numberOfOtherDescriptors: %d", numberOfOtherDescriptors);
    }

    thread->subDescriptors = (SubDescriptor*)malloc(sizeof(SubDescriptor) * numberOfOtherDescriptors);
    if (!thread->subDescriptors) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for thread->subDescriptors\n");
        return 0;
    }
    for (j = 0; j < numberOfOtherDescriptors; j++) {
        SubDescriptor sd;
        char* subCodeBuff, *subColorNameBuff;
        int subCodeLength, subColorNameLength;

        sd.someNum = fread_int16(file);
        /* Debug.Assert(sd.someNum == 1); TODO: review */
        embInt_read(file, ".", &(sd.someInt), EMB_INT32_LITTLE);
        subCodeLength = fgetc(file);
        subCodeBuff = (char*)malloc(subCodeLength);
        if (!subCodeBuff) {
            printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for subCodeBuff\n");
            return 0;
        }
        fread((unsigned char*)subCodeBuff, 1, subCodeLength, file); /* TODO: check return value */
        sd.colorCode = subCodeBuff;
        subColorNameLength = fgetc(file);
        subColorNameBuff = (char*)malloc(subColorNameLength);
        if (!subColorNameBuff) {
            printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for subColorNameBuff\n");
            return 0;
        }
        fread((unsigned char*)subColorNameBuff, 1, subColorNameLength, file); /* TODO: check return value */
        sd.colorName = subColorNameBuff;
        embInt_read(file, ".", &(sd.someOtherInt), EMB_INT32_LITTLE);
        thread->subDescriptors[j] = sd;
    }
    return 1;
}

char
readStx(EmbPattern* pattern, FILE* file)
{
    int i, threadCount;
    unsigned char* gif = 0;
    /* public Bitmap Image; */
    StxThread* stxThreads = 0;
    unsigned char headerBytes[7];
    char* header = 0;
    char stor;
    char filetype[4], version[5];
    int paletteLength, imageLength, something1, stitchDataOffset, something3;
    int threadDescriptionOffset, stitchCount, left, right, colors;
    int val[12];
    int bottom, top;

    if (!check_header_present(file, 15)) {
        puts("ERROR: header is not present.");
        return 0;
    }

    /* bytes 0-6 */
    fread(headerBytes, 1, 7, file); /* TODO: check return value */
    header = (char*)headerBytes;

    /* bytes 7-9 */
    memcpy(filetype, &header[0], 3); 
    /* bytes 10-13 */
    memcpy(version, &header[3], 4);
    filetype[3] = '\0';
    version[4] = '\0';
    /* byte 14 */
    stor = (char)fgetc(file);
    if (emb_verbose>1) {
        printf("stor: %d\n", stor);
    }
    /* bytes 15- */
    embInt_read(file, ".", &paletteLength, EMB_INT32_LITTLE);
    embInt_read(file, ".", &imageLength, EMB_INT32_LITTLE);
    embInt_read(file, ".", &something1, EMB_INT32_LITTLE);
    embInt_read(file, ".", &stitchDataOffset, EMB_INT32_LITTLE);
    embInt_read(file, ".", &something3, EMB_INT32_LITTLE);
    embInt_read(file, ".", &threadDescriptionOffset, EMB_INT32_LITTLE);
    embInt_read(file, ".", &stitchCount, EMB_INT32_LITTLE);
    embInt_read(file, ".", &colors, EMB_INT32_LITTLE);
    embInt_read(file, ".", &right, EMB_INT16_LITTLE);
    embInt_read(file, ".", &left, EMB_INT16_LITTLE);
    embInt_read(file, ".", &bottom, EMB_INT16_LITTLE);
    embInt_read(file, ".", &top, EMB_INT16_LITTLE);
    if (emb_verbose>1) {
        printf("paletteLength:           %d\n", paletteLength);
        printf("imageLength:             %d\n", imageLength);
        printf("something1:              %d\n", something1);
        printf("stitchDataOffset:        %d\n", stitchDataOffset);
        printf("something3:              %d\n", something3);
        printf("threadDescriptionOffset: %d\n", threadDescriptionOffset);
        printf("stitchCount:             %d\n", stitchCount);
        printf("colors:                  %d\n", colors);
        printf("right:                   %d\n", right);
        printf("left:                    %d\n", left);
        printf("bottom:                  %d\n", bottom);
        printf("top:                     %d\n", top);
    }

    gif = (unsigned char*)malloc(imageLength);
    if (!gif) { 
        printf("ERROR: format-stx.c readStx(), unable to allocate memory for gif\n"); 
        return 0;
    }
    fread(gif, 1, imageLength, file); /* TODO: check return value */
    /*Stream s2 = new MemoryStream(gif); TODO: review */
    /*Image = new Bitmap(s2); TODO: review */

    threadCount = fread_int16(file);
    stxThreads = (StxThread*)malloc(sizeof(StxThread) * threadCount);
    if (!stxThreads) {
        printf("ERROR: format-stx.c readStx(), unable ");
        printf("to allocate memory for stxThreads\n"); 
        return 0;
    }
    for (i = 0; i < threadCount; i++) {
        EmbThread t;
        StxThread st;
        stxReadThread(&st, file);

        t.color = st.stxColor;
        strcpy(t.description, st.colorName);
        strcpy(t.catalogNumber, st.colorCode);
        embPattern_addThread(pattern, t);
        stxThreads[i] = st;
    }

    fseek(file, 15, SEEK_CUR);

    for (i = 0; i < 12; i++) {
        embInt_read(file, ".", val+i, EMB_INT16_LITTLE);
        if (emb_verbose>1) {
            printf("identify val[%d] = %d", i, val[i]);
        }
    }
    if (emb_verbose>1) {
        puts("val[4] == val[5] == 0");
        puts("val[10] == val[11] == 0");
    }
    fseek(file, 8, SEEK_CUR); /* 0 0 */
    /* br.BaseStream.Position = stitchDataOffset; TODO: review */
    for (i = 1; i < stitchCount; ) {
        char b0 = (char)fgetc(file);
        char b1 = (char)fgetc(file);
        if (b0 == -128) {
            switch (b1) {
                case 1:
                    b0 = (char)fgetc(file);
                    b1 = (char)fgetc(file);
                    /*embPattern_addStitchRel(b0, b1, STOP); TODO: review */

                    i++;
                    break;
                case 2:
                    b0 = (char)fgetc(file);
                    b1 = (char)fgetc(file);
                    embPattern_addStitchRel(pattern, b0 / 10.0, 
                        b1 / 10.0, JUMP, 1);
                    i++;
                    break;
                case -94:
                    /* TODO: Is this a synchronize? 
                        If so document it in the comments. */
                    break;
                default:
                    /*Debugger.Break(); TODO: review */
                    break;
            }
        } else {
            embPattern_addStitchRel(pattern, b0 / 10.0, b1 / 10.0, NORMAL, 1);
            i++;
        }
    }
    embPattern_flipVertical(pattern);
    return 1;
}

char
writeStx(EmbPattern* pattern, FILE* file)
{
    puts("ERROR: writeStx is not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void*)pattern, (void*)file);
    }
    return 0; /*TODO: finish writeStx */
}
