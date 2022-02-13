/*
 * This file is part of libembroidery.
 *
 * Copyright 2018-2022 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * This file contains all the read and write functions for the
 * library.
 */

char embPattern_read(EmbPattern* pattern, const char *fileName, int format) {
    int result;
    FILE *file;
    result = 0;
    if (!pattern) {
        printf("ERROR: embPattern_read(), pattern argument is null.\n");
        return 0;
    }
    if (!fileName) {
        printf("ERROR: embPattern_read(), fileName argument is null.\n");
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        printf("ERROR: Failed to open file with name: %s.\n", fileName);
        return 0;
    }
    if (formatTable[format].check_for_color_file) {
        embPattern_loadExternalColorFile(pattern, fileName);
    }
    switch (format) {
    case EMB_FORMAT_100:
        result = read100(pattern, file);
        break;
    case EMB_FORMAT_10O:
        result = read10o(pattern, file);
        break;
    case EMB_FORMAT_ART:
        result = readArt(pattern, file);
        break;
    case EMB_FORMAT_BMC:
        result = readBmc(pattern, file);
        break;
    case EMB_FORMAT_BRO:
        result = readBro(pattern, file);
        break;
    case EMB_FORMAT_CND:
        result = readCnd(pattern, file);
        break;
    case EMB_FORMAT_COL:
        result = readCol(pattern, file);
        break;
    case EMB_FORMAT_CSD:
        result = readCsd(pattern, file);
        break;
    case EMB_FORMAT_CSV:
        result = readCsv(pattern, file);
        break;
    case EMB_FORMAT_DAT:
        result = readDat(pattern, file);
        break;
    case EMB_FORMAT_DEM:
        result = readDem(pattern, file);
        break;
    case EMB_FORMAT_DSB:
        result = readDsb(pattern, file);
        break;
    case EMB_FORMAT_DST:
        result = readDst(pattern, file);
        break;
    case EMB_FORMAT_DSZ:
        result = readDsz(pattern, file);
        break;
    case EMB_FORMAT_DXF:
        result = readDxf(pattern, file);
        break;
    case EMB_FORMAT_EDR:
        result = readEdr(pattern, file);
        break;
    case EMB_FORMAT_EMD:
        result = readEmd(pattern, file);
        break;
    case EMB_FORMAT_EXP:
        result = readExp(pattern, file);
        break;
    case EMB_FORMAT_EXY:
        result = readExy(pattern, file);
        break;
    case EMB_FORMAT_EYS:
        result = readEys(pattern, file);
        break;
    case EMB_FORMAT_FXY:
        result = readFxy(pattern, file);
        break;
    case EMB_FORMAT_GC:
        result = readGc(pattern, file);
        break;
    case EMB_FORMAT_GNC:
        result = readGnc(pattern, file);
        break;
    case EMB_FORMAT_GT:
        result = readGt(pattern, file);
        break;
    case EMB_FORMAT_HUS:
        result = readHus(pattern, file);
        break;
    case EMB_FORMAT_INB:
        result = readInb(pattern, file);
        break;
    case EMB_FORMAT_INF:
        result = readInf(pattern, file);
        break;
    case EMB_FORMAT_JEF:
        result = readJef(pattern, file);
        break;
    case EMB_FORMAT_KSM:
        result = readKsm(pattern, file);
        break;
    case EMB_FORMAT_MAX:
        result = readMax(pattern, file);
        break;
    case EMB_FORMAT_MIT:
        result = readMit(pattern, file);
        break;
    case EMB_FORMAT_NEW:
        result = readNew(pattern, file);
        break;
    case EMB_FORMAT_OFM:
        result = readOfm(pattern, file);
        break;
    case EMB_FORMAT_PCD:
        result = readPcd(pattern, fileName, file);
        break;
    case EMB_FORMAT_PCM:
        result = readPcm(pattern, file);
        break;
    case EMB_FORMAT_PCQ:
        result = readPcq(pattern, fileName, file);
        break;
    case EMB_FORMAT_PCS:
        result = readPcs(pattern, fileName, file);
        break;
    case EMB_FORMAT_PEC:
        result = readPec(pattern, fileName, file);
        break;
    case EMB_FORMAT_PEL:
        result = readPel();
        break;
    case EMB_FORMAT_PEM:
        result = readPem();
        break;
    case EMB_FORMAT_PES:
        result = readPes(pattern, fileName, file);
        break;
    case EMB_FORMAT_PHB:
        result = readPhb(pattern, file);
        break;
    case EMB_FORMAT_PHC:
        result = readPhc(pattern, file);
        break;
    case EMB_FORMAT_PLT:
        result = readPlt(pattern, file);
        break;
    case EMB_FORMAT_RGB:
        result = readRgb(pattern, file);
        break;
    case EMB_FORMAT_SEW:
        result = readSew(pattern, file);
        break;
    case EMB_FORMAT_SHV:
        result = readShv(pattern, file);
        break;
    case EMB_FORMAT_SST:
        result = readSst(pattern, file);
        break;
    case EMB_FORMAT_STX:
        result = readStx(pattern, file);
        break;
    case EMB_FORMAT_SVG:
        result = readSvg(pattern, file);
        break;
    case EMB_FORMAT_T01:
        result = readT01(pattern, file);
        break;
    case EMB_FORMAT_T09:
        result = readT09(pattern, file);
        break;
    case EMB_FORMAT_TAP:
        result = readTap(pattern, file);
        break;
    case EMB_FORMAT_THR:
        result = readThr(pattern, file);
        break;
    case EMB_FORMAT_TXT:
        result = readTxt(pattern, file);
        break;
    case EMB_FORMAT_U00:
        result = readU00(pattern, file);
        break;
    case EMB_FORMAT_U01:
        result = readU01(pattern, file);
        break;
    case EMB_FORMAT_VIP:
        result = readVip(pattern, file);
        break;
    case EMB_FORMAT_VP3:
        result = readVp3(pattern, file);
        break;
    case EMB_FORMAT_XXX:
        result = readXxx(pattern, file);
        break;
    case EMB_FORMAT_ZSK:
        result = readZsk(pattern, file);
        break;
    default:
        break;
    }
    fclose(file);
    if (!formatTable[format].color_only) {
        embPattern_end(pattern);
    }
    return result;
}

char embPattern_write(EmbPattern* pattern, const char *fileName, int format) {
    FILE *file;
    int result = 0;
    if (!pattern) {
        printf("ERROR: embPattern_write(), pattern argument is null\n");
        return 0;
    }
    if (!fileName) {
        printf("ERROR: embPattern_write(), fileName argument is null\n");
        return 0;
    }
    if (pattern->stitchList->count == 0) {
        printf("ERROR: embPattern_write(), pattern contains no stitches\n");
        return 0;
    }
    if (!formatTable[format].color_only) {
        embPattern_end(pattern);
    }

    file = fopen(fileName, "wb");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 0;
    }
    switch (format) {
    case EMB_FORMAT_100:
        result = write100();
        break;
    case EMB_FORMAT_10O:
        result = write10o();
        break;
    case EMB_FORMAT_ART:
        result = writeArt(pattern, file);
        break;
    case EMB_FORMAT_BMC:
        result = writeBmc(pattern, file);
        break;
    case EMB_FORMAT_BRO:
        result = writeBro(pattern, file);
        break;
    case EMB_FORMAT_CND:
        result = writeCnd(pattern, file);
        break;
    case EMB_FORMAT_COL:
        result = writeCol(pattern, file);
        break;
    case EMB_FORMAT_CSD:
        result = writeCsd(pattern, file);
        break;
    case EMB_FORMAT_CSV:
        result = writeCsv(pattern, file);
        break;
    case EMB_FORMAT_DAT:
        result = writeDat(pattern, file);
        break;
    case EMB_FORMAT_DEM:
        result = writeDem(pattern, file);
        break;
    case EMB_FORMAT_DSB:
        result = writeDsb(pattern, file);
        break;
    case EMB_FORMAT_DST:
        result = writeDst(pattern, file);
        break;
    case EMB_FORMAT_DSZ:
        result = writeDsz(pattern, file);
        break;
    case EMB_FORMAT_DXF:
        result = writeDxf(pattern, file);
        break;
    case EMB_FORMAT_EDR:
        result = writeEdr(pattern, file);
        break;
    case EMB_FORMAT_EMD:
        result = writeEmd(pattern, file);
        break;
    case EMB_FORMAT_EXP:
        result = writeExp(pattern, file);
        break;
    case EMB_FORMAT_EXY:
        result = writeExy(pattern, file);
        break;
    case EMB_FORMAT_EYS:
        result = writeEys(pattern, file);
        break;
    case EMB_FORMAT_FXY:
        result = writeFxy(pattern, file);
        break;
    case EMB_FORMAT_GC:
        result = writeGc(pattern, file);
        break;
    case EMB_FORMAT_GNC:
        result = writeGnc(pattern, file);
        break;
    case EMB_FORMAT_GT:
        result = writeGt(pattern, file);
        break;
    case EMB_FORMAT_HUS:
        result = writeHus(pattern, file);
        break;
    case EMB_FORMAT_INB:
        result = writeInb(pattern, file);
        break;
    case EMB_FORMAT_INF:
        result = writeInf(pattern, file);
        break;
    case EMB_FORMAT_JEF:
        result = writeJef(pattern, file);
        break;
    case EMB_FORMAT_KSM:
        result = writeKsm(pattern, file);
        break;
    case EMB_FORMAT_MAX:
        result = writeMax(pattern, file);
        break;
    case EMB_FORMAT_MIT:
        result = writeMit(pattern, file);
        break;
    case EMB_FORMAT_NEW:
        result = writeNew(pattern, file);
        break;
    case EMB_FORMAT_OFM:
        result = writeOfm(pattern, file);
        break;
    case EMB_FORMAT_PCD:
        result = writePcd(pattern, file);
        break;
    case EMB_FORMAT_PCM:
        result = writePcm(pattern, file);
        break;
    case EMB_FORMAT_PCQ:
        result = writePcq(pattern, file);
        break;
    case EMB_FORMAT_PCS:
        result = writePcs(pattern, file);
        break;
    case EMB_FORMAT_PEC:
        result = writePec(pattern, fileName, file);
        break;
    case EMB_FORMAT_PEL:
        result = writePel();
        break;
    case EMB_FORMAT_PEM:
        result = writePem();
        break;
    case EMB_FORMAT_PES:
        result = writePes(pattern, fileName, file);
        break;
    case EMB_FORMAT_PHB:
        result = writePhb();
        break;
    case EMB_FORMAT_PHC:
        result = writePhc();
        break;
    case EMB_FORMAT_PLT:
        result = writePlt(pattern, file);
        break;
    case EMB_FORMAT_RGB:
        result = writeRgb(pattern, file);
        break;
    case EMB_FORMAT_SEW:
        result = writeSew(pattern, file);
        break;
    case EMB_FORMAT_SHV:
        result = writeShv();
        break;
    case EMB_FORMAT_SST:
        result = writeSst();
        break;
    case EMB_FORMAT_STX:
        result = writeStx();
        break;
    case EMB_FORMAT_SVG:
        result = writeSvg(pattern, file);
        break;
    case EMB_FORMAT_T01:
        result = writeT01(pattern, file);
        break;
    case EMB_FORMAT_T09:
        result = writeT09(pattern, file);
        break;
    case EMB_FORMAT_TAP:
        result = writeTap(pattern, file);
        break;
    case EMB_FORMAT_THR:
        result = writeThr(pattern, file);
        break;
    case EMB_FORMAT_TXT:
        result = writeTxt(pattern, file);
        break;
    case EMB_FORMAT_U00:
        result = writeU00();
        break;
    case EMB_FORMAT_U01:
        result = writeU01();
        break;
    case EMB_FORMAT_VIP:
        result = writeVip(pattern, file);
        break;
    case EMB_FORMAT_VP3:
        result = writeVp3(pattern, file);
        break;
    case EMB_FORMAT_XXX:
        result = writeXxx(pattern, file);
        break;
    case EMB_FORMAT_ZSK:
        result = writeZsk(pattern, file);
        break;
    default:
        break;
    }
    if (formatTable[format].write_external_color_file) {
        char externalFileName[1000];
        int stub_length;
        strcpy(externalFileName, fileName);
        stub_length = strlen(fileName)-strlen(formatTable[format].extension);
        externalFileName[stub_length] = 0;
        strcat(externalFileName, ".rgb");
        embPattern_write(pattern, externalFileName, EMB_FORMAT_RGB);
    }
    fclose(file);
    return result;
}

char embPattern_readAuto(EmbPattern* pattern, const char* fileName) {
    int format = emb_identify_format(fileName);
    if (format < 0) {
        printf("ERROR: convert(), unsupported read file type: %s\n", fileName);
        embPattern_free(pattern);
        return 0;
    }
    return embPattern_read(pattern, fileName, format);
}

char embPattern_writeAuto(EmbPattern* pattern, const char* fileName) {
    int format = emb_identify_format(fileName);
    if (format < 0) {
        printf("ERROR: convert(), unsupported write file type: %s\n", fileName);
        embPattern_free(pattern);
        return 0;
    }
    return embPattern_write(pattern, fileName, format);
}

/* ---------------------------------------------------------------- */
/* 100 format */

static char read100(EmbPattern* pattern, FILE* file) {
    unsigned char b[4];

    while (fread(b, 1, 4, file) == 4) {
        int x, y;
        int stitchType;
        stitchType = NORMAL;
        x = (b[2] > 0x80) ? -(b[2] - 0x80) : b[2];
        y = (b[3] > 0x80) ? -(b[3] - 0x80) : b[3];
        /*if (!(b[0] & 0xFC)) stitchType = JUMP; TODO: review & fix */
        if (!(b[0] & 0x01)) stitchType = STOP;
        if (b[0] == 0x1F) stitchType = END;
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }
    return 1;
}

static char write100(void) {
    puts("ERROR: write100 is not implemented.");
    
    /*
    int x, y;
    int stitchType;
    unsigned char b[4];

    TODO:
    while (1) {
        stitchType = NORMAL;
        x = (b[2] > 0x80) ? -(b[2] - 0x80) : b[2];
        y = (b[3] > 0x80) ? -(b[3] - 0x80) : b[3];
        if (st.flags & JUMP) {
            ?
        }
        if (st.flags & STOP) {
            ?
        }
        if (st.flags & END) {
            ?
        }
        // if (!(b[0] & 0xFC)) stitchType = JUMP; TODO: review & fix
        if (!(b[0] & 0x01)) stitchType = STOP;
        if (b[0] == 0x1F) stitchType = END;
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
        fwrite(b, 1, 4, file);
    }
    */
    return 1;
}

/* ---------------------------------------------------------------- */
/* 10o format */

static char read10o(EmbPattern* pattern, FILE* file) {
    unsigned char b[3];
    while (fread(b, 1, 3, file) == 3) {
        int x, y;
        int stitchType = NORMAL;
        unsigned char ctrl = b[0];
        y = b[1];
        x = b[2];
        if (ctrl & 0x20) {
            x = -x;
        }
        if (ctrl & 0x40) {
            y = -y;
        }
        if (ctrl & 0x01) {
            stitchType = TRIM;
        }
        if ((ctrl & 0x5) == 5) {
            stitchType = STOP;
        }
        if (ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }
    return 1;
}

static char write10o(void) {
    puts("ERROR: write10o is not implemented.");
    /*
    TODO:
    while (1) {
        int x, y;
        int stitchType = NORMAL;
        unsigned char ctrl = (unsigned char)fgetc(file);
        if (feof(file))
            break;
        y = fgetc(file);
        if (feof(file))
            break;
        x = fgetc(file);
        if (feof(file))
            break;
        if (ctrl & 0x20)
            x = -x;
        if (ctrl & 0x40)
            y = -y;
        if (ctrl & 0x01)
            stitchType = TRIM;
        if ((ctrl & 0x5) == 5)
        {
            stitchType = STOP;
        }
        if (ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87)
        {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
        fwrite(b, 1, 4, file);
    }
    */
    puts("Write10o is not supported currently.");
    return 0; /*TODO: finish write10o */
}

/* ---------------------------------------------------------------- */
/* art format */

static char readArt(EmbPattern* pattern, FILE* file)
{
    puts("readArt is not implemented");
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readArt */
}

static char writeArt(EmbPattern* pattern, FILE* file)
{
    puts("writeArt is not implemented");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeArt */
}

/* ---------------------------------------------------------------- */
/* bmc format */

static char readBmc(EmbPattern* pattern, FILE* file) {
    puts("readBmc is not implemented");
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readBmc */
}

static char writeBmc(EmbPattern* pattern, FILE* file) {
    puts("writeBmc is not implemented");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeBmc */
}

/* ---------------------------------------------------------------- */
/* bro format */

static char readBro(EmbPattern* pattern, FILE* file) {
    unsigned char x55;
    short unknown1, unknown2, unknown3, unknown4, moreBytesToEnd;
    char name[8];
    int stitchType;
    fread(&x55, 1, 1, file);
    /* TODO: determine what this unknown data is */
    fread(&unknown1, 2, 1, file);

    fread(name, 1, 8, file);
    /* TODO: determine what this unknown data is */
    fread(&unknown2, 2, 1, file);
    /* TODO: determine what this unknown data is */
    fread(&unknown3, 2, 1, file);
    /* TODO: determine what this unknown data is */
    fread(&unknown4, 2, 1, file);
    fread(&moreBytesToEnd, 2, 1, file);

    fseek(file, 0x100, SEEK_SET);

    while (!feof(file)) {
        short b1, b2;
        stitchType = NORMAL;
        b1 = (unsigned char)fgetc(file);
        b2 = (unsigned char)fgetc(file);
        if (b1 == -128) {
            unsigned char bCode = (unsigned char)fgetc(file);
            fread(&b1, 2, 1, file);
            fread(&b2, 2, 1, file);
            /* Embird uses 0x02 and Wilcom uses 0xE1 */
            if (bCode == 0x02 || bCode == 0xE1) {
                stitchType = STOP;
            } else if (bCode == 3) {
                stitchType = TRIM;
            } else if (bCode == 0x7E) {
                embPattern_addStitchRel(pattern, 0, 0, END, 1);
                break;
            }
        }
        embPattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }
    return 1;
}

static char writeBro(EmbPattern* pattern, FILE* file) {
    puts("writeBro is not implemented");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeBro */
}

/* ---------------------------------------------------------------- */
/* cnd format */

static char readCnd(EmbPattern* pattern, FILE* file) {
    puts("readCnd is not implemented");
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readCnd */
}

static char writeCnd(EmbPattern* pattern, FILE* file) {
    puts("writeCnd is not implemented");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeCnd */
}

/* ---------------------------------------------------------------- */
/* col format */

static char readCol(EmbPattern* pattern, FILE* file) {
    int numberOfColors, i;
    int num, blue, green, red;
    EmbThread t;
    char line[30];

    embArray_free(pattern->threads);
    pattern->threads = embArray_create(EMB_THREAD);

    emb_readline(file, line, 30);
    numberOfColors = atoi(line);
    if (numberOfColors < 1) {
        printf("ERROR: Number of colors is zero.");
        return 0;
    }
    for (i = 0; i < numberOfColors; i++) {
        emb_readline(file, line, 30);
        if (strlen(line) < 1) {
            printf("ERROR: Empty line in col file.");
            return 0;
        }
        /* TODO: replace all scanf code */
        if (sscanf(line,"%d,%d,%d,%d", &num, &blue, &green, &red) != 4) {
            break;
        }
        t.color.r = (unsigned char)red;
        t.color.g = (unsigned char)green;
        t.color.b = (unsigned char)blue;
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        embPattern_addThread(pattern, t);
    }
    return 1;
}

static char writeCol(EmbPattern* pattern, FILE* file)
{
    int i;

    fprintf(file, "%d\r\n", pattern->threads->count);
    for (i = 0; i < pattern->threads->count; i++) {
        EmbColor c;
        c = pattern->threads->thread[i].color;
        fprintf(file, "%d,%d,%d,%d\r\n", i, (int)c.r, (int)c.g, (int)c.b);
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/* csd format */

#define CsdSubMaskSize  479
#define CsdXorMaskSize  501
#define DEBUG 0

static char _subMask[CsdSubMaskSize];
static char _xorMask[CsdXorMaskSize];

static void BuildDecryptionTable(int seed) {
    int i;
    const int mul1 = 0x41C64E6D;
    const int add1 = 0x3039;

    for (i = 0; i < CsdSubMaskSize; i++) {
        seed *= mul1;
        seed += add1;
        _subMask[i] = (char) ((seed >> 16) & 0xFF);
    }
    for (i = 0; i < CsdXorMaskSize; i++) {
        seed *= mul1;
        seed += add1;
        _xorMask[i] = (char) ((seed >> 16) & 0xFF);
    }
}

static unsigned char DecodeCsdByte(long fileOffset, 
        unsigned char val, int type) {
    static const unsigned char _decryptArray[] = {
          0x43, 0x6E, 0x72, 0x7A, 0x76, 0x6C, 0x61, 0x6F, 0x7C, 0x29, 0x5D, 0x62, 0x60, 0x6E, 0x61, 0x62, 0x20
        , 0x41, 0x66, 0x6A, 0x3A, 0x35, 0x5A, 0x63, 0x7C, 0x37, 0x3A, 0x2A, 0x25, 0x24, 0x2A, 0x33, 0x00, 0x10
        , 0x14, 0x03, 0x72, 0x4C, 0x48, 0x42, 0x08, 0x7A, 0x5E, 0x0B, 0x6F, 0x45, 0x47, 0x5F, 0x40, 0x54, 0x5C
        , 0x57, 0x55, 0x59, 0x53, 0x3A, 0x32, 0x6F, 0x53, 0x54, 0x50, 0x5C, 0x4A, 0x56, 0x2F, 0x2F, 0x62, 0x2C
        , 0x22, 0x65, 0x25, 0x28, 0x38, 0x30, 0x38, 0x22, 0x2B, 0x25, 0x3A, 0x6F, 0x27, 0x38, 0x3E, 0x3F, 0x74
        , 0x37, 0x33, 0x77, 0x2E, 0x30, 0x3D, 0x34, 0x2E, 0x32, 0x2B, 0x2C, 0x0C, 0x18, 0x42, 0x13, 0x16, 0x0A
        , 0x15, 0x02, 0x0B, 0x1C, 0x1E, 0x0E, 0x08, 0x60, 0x64, 0x0D, 0x09, 0x51, 0x25, 0x1A, 0x18, 0x16, 0x19
        , 0x1A, 0x58, 0x10, 0x14, 0x5B, 0x08, 0x15, 0x1B, 0x5F, 0xD5, 0xD2, 0xAE, 0xA3, 0xC1, 0xF0, 0xF4, 0xE8
        , 0xF8, 0xEC, 0xA6, 0xAB, 0xCD, 0xF8, 0xFD, 0xFB, 0xE2, 0xF0, 0xFE, 0xFA, 0xF5, 0xB5, 0xF7, 0xF9, 0xFC
        , 0xB9, 0xF5, 0xEF, 0xF4, 0xF8, 0xEC, 0xBF, 0xC3, 0xCE, 0xD7, 0xCD, 0xD0, 0xD7, 0xCF, 0xC2, 0xDB, 0xA4
        , 0xA0, 0xB0, 0xAF, 0xBE, 0x98, 0xE2, 0xC2, 0x91, 0xE5, 0xDC, 0xDA, 0xD2, 0x96, 0xC4, 0x98, 0xF8, 0xC9
        , 0xD2, 0xDD, 0xD3, 0x9E, 0xDE, 0xAE, 0xA5, 0xE2, 0x8C, 0xB6, 0xAC, 0xA3, 0xA9, 0xBC, 0xA8, 0xA6, 0xEB
        , 0x8B, 0xBF, 0xA1, 0xAC, 0xB5, 0xA3, 0xBB, 0xB6, 0xA7, 0xD8, 0xDC, 0x9A, 0xAA, 0xF9, 0x82, 0xFB, 0x9D
        , 0xB9, 0xAB, 0xB3, 0x94, 0xC1, 0xA0, 0x8C, 0x8B, 0x8E, 0x95, 0x8F, 0x87, 0x99, 0xE7, 0xE1, 0xA3, 0x83
        , 0x8B, 0xCF, 0xA3, 0x85, 0x9D, 0x83, 0xD4, 0xB7, 0x83, 0x84, 0x91, 0x97, 0x9F, 0x88, 0x8F, 0xDD, 0xAD
        , 0x90
    };
    int newOffset;

    fileOffset = fileOffset - 1;
    if (type != 0) {
        int final;
        int fileOffsetHigh = (int) (fileOffset & 0xFFFFFF00);
        int fileOffsetLow = (int) (fileOffset & 0xFF);

        newOffset = fileOffsetLow;
        fileOffsetLow = fileOffsetHigh;
        final = fileOffsetLow%0x300;
        if (final != 0x100 && final != 0x200) {
            newOffset = _decryptArray[newOffset] | fileOffsetHigh;
        } else if (final != 0x100 && final == 0x200) {
            if (newOffset == 0) {
                fileOffsetHigh = fileOffsetHigh - 0x100;
            }
            newOffset = _decryptArray[newOffset] | fileOffsetHigh;
        } else if (newOffset != 1 && newOffset != 0) {
            newOffset = _decryptArray[newOffset] | fileOffsetHigh;
        } else {
            fileOffsetHigh = fileOffsetHigh - 0x100;
            newOffset = _decryptArray[newOffset] | fileOffsetHigh;
        }
    } else {
        newOffset = (int) fileOffset;
    }
    return ((unsigned char) ((unsigned char)
        (val ^ _xorMask[newOffset%CsdXorMaskSize]) -
            _subMask[newOffset%CsdSubMaskSize]));
}

static char readCsd(EmbPattern* pattern, FILE* file) {
    int i, type = 0;
    unsigned char identifier[8];
    unsigned char unknown1, unknown2;
    char dx = 0, dy = 0;
    int colorChange = -1;
    int flags;
    unsigned char colorOrder[14];

    fread(identifier, 1, 8, file);
    /* TODO: check return value */

    if (identifier[0] != 0x7C && identifier[2] != 0xC3) {
        type = 1;
    }
    if (type == 0) {
        BuildDecryptionTable(0xC);
    } else {
        BuildDecryptionTable(identifier[0]);
    }

    for (i = 0; i < 16; i++) {
        EmbThread thread;
        thread.color.r = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        thread.color.g = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        thread.color.b = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        strcpy(thread.catalogNumber, "");
        strcpy(thread.description, "");
        embPattern_addThread(pattern, thread);
    }
    unknown1 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
    unknown2 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
    if (DEBUG) {
        printf("unknown bytes to decode: %c %c", unknown1, unknown2);
    }

    for (i = 0; i < 14; i++) {
        colorOrder[i] = (unsigned char) DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
    }
    for (i = 0; !feof(file); i++) {
        char negativeX, negativeY;
        unsigned char b0 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        unsigned char b1 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);
        unsigned char b2 = DecodeCsdByte(ftell(file), (unsigned char)fgetc(file), type);

        if (b0 == 0xF8 || b0 == 0x87 || b0 == 0x91) {
            break;
        }
        negativeX = ((b0 & 0x20) > 0);
        negativeY = ((b0 & 0x40) > 0);
        b0 = (unsigned char)(b0 & (0xFF ^ 0xE0));

        if ((b0 & 0x1F) == 0) {
            flags = NORMAL;
        } else if ((b0 & 0x0C) > 0) {
            flags = STOP;
            if (colorChange >= 14) {
                printf("Invalid color change detected\n");
            }
            embPattern_changeColor(pattern, colorOrder[colorChange  % 14]);
            colorChange += 1;
        } else if ((b0 & 0x1F) > 0) {
            flags = TRIM;
        } else {
            flags = NORMAL;
        }
        dx = (char) b2;
        dy = (char) b1;
        if (negativeX) { 
            dx = (char) -dx;
        }
        if (negativeY) { 
            dy = (char) -dy;
        }
        if (flags == STOP) {
            embPattern_addStitchRel(pattern, 0, 0, flags, 1);
        } else {
            embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
        }
    }
    return 1;
}

static char writeCsd(EmbPattern* pattern, FILE* file) {
    puts("writeCsd is not implemented.");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeCsd */
}

/* ---------------------------------------------------------------- */
/* csv format */

static char* csvStitchFlagToStr(int flags) {
    switch (flags) {
    case NORMAL:
        return "STITCH";
        break;
    case JUMP:
        return "JUMP";
        break;
    case TRIM:
        return "TRIM";
        break;
    case STOP:
        return "COLOR";
        break;
    case END:
        return "END";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}

static int csvStrToStitchFlag(const char* str)
{
    if (!str) {
        printf("ERROR: format-csv.c csvStrToStitchFlag(), str argument is null\n");
        return -1;
    }
    if (!strcmp(str, "STITCH")) {
        return NORMAL;
    } else if (!strcmp(str, "JUMP")) {
        return JUMP;
    } else if (!strcmp(str, "TRIM")) {
        return TRIM;
    } else if (!strcmp(str, "COLOR")) {
        return STOP;
    } else if (!strcmp(str, "END")) {
        return END;
    } else if (!strcmp(str, "UNKNOWN")) {
        return STOP;
    }
    return -1;
}

static char readCsv(EmbPattern* pattern, FILE* file) {
    int numColorChanges = 0;
    int size = 1024;
    int pos = 0;
    int c = 0;
    int cellNum = 0;
    int process = 0;
    int csvMode = CSV_MODE_NULL;
    int expect = CSV_EXPECT_QUOTE1;
    int flags = 0;
    double xx = 0.0;
    double yy = 0.0;
    unsigned char r = 0, g = 0, b = 0;
    char buff[100];

    pos = 0;
    while (!feof(file)) {
        c = fgetc(file);
        switch(c) {
            case '"':
                if (expect == CSV_EXPECT_QUOTE1) {
                    expect = CSV_EXPECT_QUOTE2;
                } else if (expect == CSV_EXPECT_QUOTE2) {
                    expect = CSV_EXPECT_COMMA;
                }
                break;
            case ',':
                if (expect == CSV_EXPECT_COMMA) {
                    process = 1;
                }
                break;
            case '\n':
                if (expect == CSV_EXPECT_COMMA) {
                    process = 1;
                } else if (expect == CSV_EXPECT_QUOTE1) {
                        /* Do Nothing. We encountered a blank line. */
                } else {
                    printf("ERROR: format-csv.c readCsv(), premature newline\n");
                    return 0;
                }
                break;
            default:
                break;
        }

        if (process) {
            buff[pos] = 0;
            pos = 0;
            process = 0;
            cellNum++;
            expect = CSV_EXPECT_QUOTE1;
                if (csvMode == CSV_MODE_NULL) {
                    if     (!strcmp(buff, "#")) {
                        csvMode = CSV_MODE_COMMENT;
                    } else if (!strcmp(buff, ">")) {
                        csvMode = CSV_MODE_VARIABLE;
                    } else if (!strcmp(buff, "$")) {
                        csvMode = CSV_MODE_THREAD;
                    } else if (!strcmp(buff, "*")) {
                        csvMode = CSV_MODE_STITCH;
                    } else {/* TODO: error */
                        return 0;
                    }
                } else if (csvMode == CSV_MODE_COMMENT) {
                    /* Do Nothing */
                } else if (csvMode == CSV_MODE_VARIABLE) {
                    /* Do Nothing */
                } else if (csvMode == CSV_MODE_THREAD) {
                    if (cellNum == 2) {
                        /* Do Nothing. Ignore Thread Number */
                    } else if (cellNum == 3) {
                        r = (unsigned char)atoi(buff);
                    } else if (cellNum == 4) {
                        g = (unsigned char)atoi(buff);
                    } else if (cellNum == 5) {
                        b = (unsigned char)atoi(buff);
                    } else if (cellNum == 6) {
                        /* TODO: Thread Description */
                    } else if (cellNum == 7) {
                        /* TODO: Thread Catalog Number */
                        EmbThread t;
                        t.color.r = r;
                        t.color.g = g;
                        t.color.b = b;
                        strcpy(t.description, "TODO:DESCRIPTION");
                        strcpy(t.catalogNumber, "TODO:CATALOG_NUMBER");
                        embPattern_addThread(pattern, t);
                        csvMode = CSV_MODE_NULL;
                        cellNum = 0;
                    } else {
                        /* TODO: error */
                        return 0;
                    }
                } else if (csvMode == CSV_MODE_STITCH) {
                    /* printf("%s\n", buff); */
                    if (cellNum == 2) {
                        flags = csvStrToStitchFlag(buff);
                        if (flags == STOP) {
                            numColorChanges++;
                        }
                    } else if (cellNum == 3) {
                        xx = atof(buff);
                    } else if (cellNum == 4) {
                        yy = atof(buff);
                        /* printf("%d %d %f %f\n", 
                            pattern->stitchList->count, flags, xx, yy); */
                        embPattern_addStitchAbs(pattern, xx, yy, flags, 1);
                        csvMode = CSV_MODE_NULL;
                        cellNum = 0;
                    } else {
                        /* TODO: error */
                        return 0;
                    }
                }
                if (c == '\n') {
                    csvMode = CSV_MODE_NULL;
                    cellNum = 0;
                }
            } else {
                if (expect == CSV_EXPECT_QUOTE2 && c != '"') {
                    buff[pos++] = (char)c;
                }
            }
    }

    return 1;
}

static char writeCsv(EmbPattern* pattern, FILE* file) {
    EmbRect boundingRect;
    int i;

    boundingRect = embPattern_calcBoundingBox(pattern);

    /* write header */
    fprintf(file, "\"#\",\"Embroidermodder 2 CSV Embroidery File\"\n");
    fprintf(file, "\"#\",\"http://embroidermodder.github.io\"\n");
    fprintf(file, "\n");
    fprintf(file, "\"#\",\"General Notes:\"\n");
    fprintf(file, "\"#\",\"This file can be read by Excel or LibreOffice as CSV (Comma Separated Value) or with a text editor.\"\n");
    fprintf(file, "\"#\",\"Lines beginning with # are comments.\"\n");
    fprintf(file, "\"#\",\"Lines beginning with > are variables: [VAR_NAME], [VAR_VALUE]\"\n");
    fprintf(file, "\"#\",\"Lines beginning with $ are threads: [THREAD_NUMBER], [RED], [GREEN], [BLUE], [DESCRIPTION], [CATALOG_NUMBER]\"\n");
    fprintf(file, "\"#\",\"Lines beginning with * are stitch entries: [STITCH_TYPE], [X], [Y]\"\n");
    fprintf(file, "\n");
    fprintf(file, "\"#\",\"Stitch Entry Notes:\"\n");
    fprintf(file, "\"#\",\"STITCH instructs the machine to move to the position [X][Y] and then make a stitch.\"\n");
    fprintf(file, "\"#\",\"JUMP instructs the machine to move to the position [X][Y] without making a stitch.\"\n");
    fprintf(file, "\"#\",\"TRIM instructs the machine to cut the thread before moving to the position [X][Y] without making a stitch.\"\n");
    fprintf(file, "\"#\",\"COLOR instructs the machine to stop temporarily so that the user can change to a different color thread before resuming.\"\n");
    fprintf(file, "\"#\",\"END instructs the machine that the design is completed and there are no further instructions.\"\n");
    fprintf(file, "\"#\",\"UNKNOWN encompasses instructions that may not be supported currently.\"\n");
    fprintf(file, "\"#\",\"[X] and [Y] are absolute coordinates in millimeters (mm).\"\n");
    fprintf(file, "\n");

    /* write variables */
    fprintf(file,"\"#\",\"[VAR_NAME]\",\"[VAR_VALUE]\"\n");
    fprintf(file, "\">\",\"STITCH_COUNT:\",\"%u\"\n", (unsigned int)pattern->stitchList->count);
    fprintf(file, "\">\",\"THREAD_COUNT:\",\"%u\"\n", (unsigned int)pattern->threads->count);
    fprintf(file, "\">\",\"EXTENTS_LEFT:\",\"%f\"\n",   boundingRect.left);
    fprintf(file, "\">\",\"EXTENTS_TOP:\",\"%f\"\n",    boundingRect.top);
    fprintf(file, "\">\",\"EXTENTS_RIGHT:\",\"%f\"\n",  boundingRect.right);
    fprintf(file, "\">\",\"EXTENTS_BOTTOM:\",\"%f\"\n", boundingRect.bottom);
    fprintf(file, "\">\",\"EXTENTS_WIDTH:\",\"%f\"\n",  embRect_width(boundingRect));
    fprintf(file, "\">\",\"EXTENTS_HEIGHT:\",\"%f\"\n", embRect_height(boundingRect));
    fprintf(file,"\n");

    /* write colors */
    fprintf(file, "\"#\",\"[THREAD_NUMBER]\",\"[RED]\",\"[GREEN]\",");
    fprintf(file, "\"[BLUE]\",\"[DESCRIPTION]\",\"[CATALOG_NUMBER]\"\n");
    
    for (i = 0; i < pattern->threads->count; i++) {
        EmbThread thr;
        thr = pattern->threads->thread[i];
        /* TODO: fix segfault that backtraces here when 
            libembroidery-convert from dst to csv. */
        fprintf(file, "\"$\",\"%d\",\"%d\",\"%d\",\"%d\",\"%s\",\"%s\"\n",
            i+1,
            (int)thr.color.r,
            (int)thr.color.g,
            (int)thr.color.b,
            thr.description,
            thr.catalogNumber);
    }
    fprintf(file, "\n");

    /* write stitches */
    fprintf(file, "\"#\",\"[STITCH_TYPE]\",\"[X]\",\"[Y]\"\n");
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch s = pattern->stitchList->stitch[i];
        fprintf(file, "\"*\",\"%s\",\"%f\",\"%f\"\n",
            csvStitchFlagToStr(s.flags), s.x, s.y);
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/* dat format */

static char readDat(EmbPattern* pattern, FILE* file)
{
    unsigned char b0;
    int fileLength, stitchesRemaining, b1, b2, stitchType;

    fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    if (fileLength < 0x100) {
        puts("ERROR: dat file too short to contain header.");
        return 0;
    }
    fseek(file, 0x02, SEEK_SET);
    stitchesRemaining = fread_uint16(file);
    if (EMB_DEBUG) {
        printf("stitchesRemaining: %d", stitchesRemaining);
    }
    fseek(file, 0x100, SEEK_SET);

    while (!feof(file)) {
        b1 = (int)fgetc(file);
        b2 = (int)fgetc(file);
        b0 = fgetc(file);

        stitchType = NORMAL;

        if ((b0 & 0x02) == 0) stitchType = TRIM;

        if (b0 == 0x87)
        {
            stitchType = STOP;
        }
        if (b0 == 0xF8)
        {
            break;
        }
        if (b1 >= 0x80)
        {
            b1 = -(b1 & 0x7F);
        }
        if (b2 >= 0x80)
        {
            b2 = -(b2 & 0x7F);
        }
        embPattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }

    return 1;
}

static char writeDat(EmbPattern* pattern, FILE* file)
{
    int i;
    fpad(file, 0x00, 0x100);
    for (i=0; i<pattern->stitchList->count; i++) {
        unsigned char b[3];
        EmbStitch st = pattern->stitchList->stitch[i];
        b[0] = 0;
        b[1] = 0;
        b[2] = 0;
        if (st.flags == STOP) {
            b[2] = 0x87;
        }
        if (st.flags == END) {
            b[2] |= 0xF8;
        }
        else {
            if (st.flags != TRIM) {
                b[2] |= 0x02;
            }
        }
        /* TODO: check that this works */
        if (st.x < 0) {
            b[0] = st.x+0xFF;
        }
        if (st.y < 0) {
            b[1] = st.y+0xFF;
        }
        fwrite(b, 1, 3, file);
    }
    return 1; /*TODO: finish writeDat */
}

/* ---------------------------------------------------------------- */
/* format dem */

static char readDem(EmbPattern* pattern, FILE* file)
{
    puts("readDem is not implemented.");
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readDem */
}

static char writeDem(EmbPattern* pattern, FILE* file)
{
    puts("writeDem is not implemented.");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeDem */
}

/* ---------------------------------------------------------------- */
/* format dsb */

static char readDsb(EmbPattern* pattern, FILE* file) {
    char header[512+1];
    unsigned char buffer[3];

    fread(header, 1, 512, file);

    while (fread(buffer, 1, 3, file) == 3) {
        int x, y;
        unsigned char ctrl;
        int stitchType = NORMAL;

        ctrl = buffer[0];
        y = buffer[1];
        x = buffer[2];
        if (ctrl & 0x01) stitchType = TRIM;
        if (ctrl & 0x20) x = -x;
        if (ctrl & 0x40) y = -y;
        /* ctrl & 0x02 - Speed change? */ /* TODO: review this line */
        /* ctrl & 0x04 - Clutch? */       /* TODO: review this line */
        if ((ctrl & 0x05) == 0x05) {
            stitchType = STOP;
        }
        if (ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }
    return 1;
}

static char writeDsb(EmbPattern* pattern, FILE* file) {
    puts("writeDsb is not implemented");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeDsb */
}

/* ---------------------------------------------------------------- */
/* format dst */

/* .DST (Tajima) embroidery file read/write routines
 * Format comments are thanks to tspilman@dalcoathletic.com who's
 * notes appeared at http://www.wotsit.org under Tajima Format.
 */

static int decode_record_flags(unsigned char b2)
{
    if (b2 == 0xF3) {
        return END;
    }
    if (b2 & 0x40) {
        return STOP;
    }
    if (b2 & 0x80) {
        return JUMP;
    }
    return NORMAL;
}

/* TODO: review this then remove since emb-pattern.c has a similar function */
/* void combineJumpStitches(EmbPattern* p, int jumpsPerTrim)
{
    if (!p) { printf("ERROR: format-dst.c combineJumpStitches(), p argument is null\n"); return; }
    EmbStitchList* pointer = p->stitchList;
    int jumpCount = 0;
    EmbStitchList* jumpListStart = 0;
    char needleDown = 0;
    while(pointer)
    {
        if ((pointer->stitch.flags & JUMP) && !(pointer->stitch.flags & STOP))
        {
            if (jumpCount == 0)
            {
                jumpListStart = pointer;
            }
            jumpCount++;
            if (needleDown && jumpCount >= jumpsPerTrim)
            {
                EmbStitchList* removePointer = jumpListStart->next;
                jumpListStart->stitch.x = pointer->stitch.x;
                jumpListStart->stitch.y = pointer->stitch.y;
                jumpListStart->stitch.flags |= TRIM;
                jumpListStart->next = pointer;

                jumpCount-=2;
                for (; jumpCount > 0; jumpCount--)
                {
                    EmbStitchList* tempPointer = removePointer->next;
                    jumpListStart->stitch.flags |= removePointer->stitch.flags;
                    free(removePointer);
                    removePointer = 0;
                    removePointer = tempPointer;
                }
                jumpCount = 0;
                needleDown = 0;
            }
        }
        else
        {
            if (pointer->stitch.flags == NORMAL)
            {
                needleDown = 1;
                jumpCount = 0;
            }
        }
        pointer = pointer->next;
    }
}
*/

static void encode_record(FILE* file, int x, int y, int flags)
{
    unsigned char b[3];
    encode_tajima_ternary(b, x, y);

    b[2] |= 0x03;

    if (flags & END) {
        /* 0b10001101 = -13 = 0x8D */
        b[0] = 0;
        b[1] = 0;
        b[2] = 0x8D;
    }

    /* make the variable v configurable for the pattern */
    if (flags & TRIM) {
        int dx, dy, i, v = 5;
        dx = x/v;
        dy = y/v;
        for (i = 1; i < v; i++) {
            encode_record(file, dx, dy, JUMP);
        }
        encode_record(file, x - (dx * (v - 1)), y - (dy * (v - 1)), JUMP);
        return;
    }
    if (flags & (JUMP | TRIM)) {
        b[2] = (char) (b[2] | 0x83);
    }
    if (flags & STOP) {
        b[2] = (char) (b[2] | 0xC3);
    }

    fwrite(b, 1, 3, file);
}

/*convert 2 characters into 1 int for case statement */
/*#define cci(s) (s[0]*256+s[1]) */
#define cci(c1,c2) (c1*256+c2)

static void set_dst_variable(EmbPattern* pattern, char* var, char* val) {
    unsigned int i;
    EmbThread t;
    for (i = 0; i <= (unsigned int)strlen(var); i++) {
        /* uppercase the var */
        if (var[i] >= 'a' && var[i] <= 'z') {
            var[i] += 'A' - 'a';
        }
    }

    /* macro converts 2 characters to 1 int, allows case statement... */
    switch(cci(var[0],var[1]))
    {
    case cci('L','A'): /* Design Name (LA) */
        /*pattern->set_variable("Design_Name",val); TODO: review this line. */
        break;
    case cci('S','T'): /* Stitch count, 7 digits padded by leading 0's */
    case cci('C','O'): /* Color change count, 3 digits padded by leading 0's */
    case cci('+','X'): /* Design extents (+/-X,+/-Y), 5 digits padded by leading 0's */
    case cci('-','X'):
    case cci('+','Y'):
    case cci('-','Y'):
        /* don't store these variables, they are recalculated at save */
        break;
    case cci('A','X'): /* Relative coordinates of last point, 6 digits, padded with leading spaces, first char may be +/- */
    case cci('A','Y'):
    case cci('M','X'): /* Coordinates of last point in previous file of multi-volume design, 6 digits, padded with leading spaces, first char may be +/- */
    case cci('M','Y'):
        /* store these variables as-is, they will be converted to numbers and back at save; */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    case cci('P','D'):
        /* store this string as-is, it will be saved as-is, 6 characters */
        if (strlen(val) != 6)
        {
            /*pattern->messages.add("Warning: in DST file read, 
                PD is not 6 characters, but ",(int)strlen(val)); */
        }
        /*pattern->set_variable(var,val);*/
        break;
        /* Begin extended fields section */
    case cci('A','U'): /* Author string, arbitrary length */
    case cci('C','P'): /* Copyright string, arbitrary length */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
        /*Thread Color: #RRGGBB,Description,Catalog Number (1st field RGB 
            hex values, 2nd&3rd fields optional arbitrary length) */
    case cci('T','C'): 
        /* TODO: review these lines below.
        description=split_cell_str(val,2);
        catalog_number=split_cell_str(val,3);
        */
        t.color = embColor_fromHexStr(val);
        strcpy(t.description, "");
        strcpy(t.catalogNumber, "");
        embPattern_addThread(pattern, t);
        break;
    default:
        /* unknown field, just save it. */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    }
}

/*
    * The header seems to contain information about the design.
    * Seems to be ASCII text delimited by 0x0D (carriage returns).
    * This must be in the file for most new software or hardware
    * to consider it a good file! This is much more important
    * than I originally believed. The header is 125 bytes in
    * length and padded out by 0x20 to 512 bytes total.
    * All entries in the header seem to be 2 ASCII characters
    * followed by a colon, then it's value trailed by a carriage return.
    *
    * char LA[16+1];  First is the 'LA' entry, which is the design name with no
    *                 path or extension information. The blank is 16 characters
    *                 in total, but the name must not be longer that 8 characters
    *                 and padded out with 0x20.
    *
    * char ST[7+1];   Next is the stitch count ST, this is a 7 digit number
    *                 padded by leading zeros. This is the total stitch count
    *                 including color changes, jumps, nups, and special records.
    *
    * char CO[3+1];   Next, is CO or colors, a 3 digit number padded by leading
    *                 zeros. This is the number of color change records in the file.
    *
    * char POSX[5+1]; Next is +X or the positive X extent in centimeters, a 5
    *                 digit non-decimal number padded by leading zeros.
    *
    * char NEGX[5+1]; Following is the -X or the negative X extent in millimeters,
    *                 a 5 digit non-decimal number padded by leading zeros.
    *
    * char POSY[5+1]; Again, the +Y extents.
    *
    * char NEGY[5+1]; Again, the -Y extents.
    *
    * char AX[6+1];   AX and AY should express the relative coordinates of the
    * char AY[6+1];   last point from the start point in 0.1 mm. If the start
    *                 and last points are the same, the coordinates are (0,0).
    *
    * char MX[6+1];   MX and MY should express coordinates of the last point of
    * char MY[6+1];   the previous file for a multi-volume design. A multi-
    *                 volume design means a design consisted of two or more files.
    *                 This was used for huge designs that can not be stored in a
    *                 single paper tape roll. It is not used so much (almost
    *                 never) nowadays.
    *
    * char PD[9+1];   PD is also storing some information for multi-volume design.
    */
static char readDst(EmbPattern* pattern, FILE* file) {
    char var[3];   /* temporary storage variable name */
    char val[512]; /* temporary storage variable value */
    int valpos;
    unsigned char b[3];
    char header[512 + 1];
    int i = 0, flags;

    /* TODO: review commented code below
    pattern->clear();
    pattern->set_variable("file_name",filename);
    */

    fread(header, 1, 512, file);

    /*TODO:It would probably be a good idea to 
        validate file before accepting it. */
    /* fill variables from header fields */
    for (i = 0; i < 512; i++) {
        if (header[i] == ':' && i > 1) {
            var[0] = header[i - 2];
            var[1] = header[i - 1];
            var[2] = '\0';
            valpos = i + 1;
            for (i++; i < 512; i++)
            {
                /* don't accept : without CR because there's a bug below: i-valpos must be > 0 which is not the case if the : is before the third character. */
                if (header[i] == 13/*||header[i]==':'*/) { /* 0x0d = carriage return */
                    /* : indicates another variable, CR was missing! */
                    if (header[i] == ':') {
                        i -= 2;
                    }
                    strncpy(val, &header[valpos], (size_t)(i - valpos));
                    val[i - valpos] = '\0';
                    set_dst_variable(pattern, var, val);
                    break;
                }
            }
        }
    }

    while(fread(b, 1, 3, file) == 3) {
        int x, y;
        decode_tajima_ternary(b, &x, &y);
        flags = decode_record_flags(b[2]);
        if (flags == END) {
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
    }

    /* combineJumpStitches(pattern, 5); */
    return 1;
}

static char writeDst(EmbPattern* pattern, FILE* file) {
    EmbRect boundingRect;
    int xx, yy, i, ax, ay, mx, my;
    char pd[10];
    EmbStitch st;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    /* TODO: make sure that pattern->threads->count
     * defaults to 1 in new patterns */
    boundingRect = embPattern_calcBoundingBox(pattern);
    /* TODO: review the code below
    if (pattern->get_variable("design_name") != NULL) {
        char *la = stralloccopy(pattern->get_variable("design_name"));
        if (strlen(la)>16) la[16]='\0';

        fprintf(file,"LA:%-16s\x0d",la);
        free(la);
    }
    */
    fprintf(file, "LA:%-16s\x0d", "Untitled");
    fprintf(file, "ST:%7d\x0d", pattern->stitchList->count);
    /* number of color changes, not number of colors! */
    fprintf(file, "CO:%3d\x0d", pattern->threads->count - 1); 
    fprintf(file,
        "+X:%5d\x0d"
        "-X:%5d\x0d"
        "+Y:%5d\x0d"
        "-Y:%5d\x0d",
        (int)(boundingRect.right * 10.0),
        (int)(fabs(boundingRect.left) * 10.0),
        (int)(boundingRect.bottom * 10.0),
        (int)(fabs(boundingRect.top) * 10.0));

    ax = ay = mx = my = 0;
    /* TODO: review the code below */
    /*ax=pattern->get_variable_int("ax"); */ /* will return 0 if not defined */
    /*ay=pattern->get_variable_int("ay"); */
    /*mx=pattern->get_variable_int("mx"); */
    /*my=pattern->get_variable_int("my"); */

    /*pd=pattern->get_variable("pd");*/ /* will return null pointer if not defined */
   /* pd = 0;
    if (pd == 0 || strlen(pd) != 6) { */
        /* pd is not valid, so fill in a default consisting of "******" */
        strcpy(pd, "******");
    /*}*/
    fprintf(file,
        "AX:+%5d\x0d"
        "AY:+%5d\x0d"
        "MX:+%5d\x0d"
        "MY:+%5d\x0d"
        "PD:%6s\x0d\x1a",
        ax, ay, mx, my, pd);

    /* pad out header to proper length */
    fpad(file, ' ', 512-125);

    /* write stitches */
    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        int dx, dy;
        st = pattern->stitchList->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)round(st.x * 10.0) - xx;
        dy = (int)round(st.y * 10.0) - yy;
        xx = (int)round(st.x * 10.0);
        yy = (int)round(st.y * 10.0);
        if (emb_verbose > 0) {
            printf("%d %f %f %d %d %d %d %d\n", i, st.x, st.y, dx, dy, xx, yy, st.flags);
        }
        encode_record(file, dx, dy, st.flags);
    }

    /* Finish file with a terminator character and two zeros to
     * keep the post header part a multiple of three.
     */
    fwrite("\xa1\0\0", 1, 3, file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format dsz */

static char readDsz(EmbPattern* pattern, FILE* file) {
    unsigned char b[3];

    fseek(file, 0x200, SEEK_SET);
    while (fread(b, 1, 3, file) == 3) {
        int x, y;
        unsigned char ctrl;
        int stitchType = NORMAL;

        y = b[0];
        x = b[1];
        ctrl = b[2];
        if (ctrl & 0x01) {
            stitchType = TRIM;
        }
        if (ctrl & 0x20) {
            y = -y;
        }
        if (ctrl & 0x40) {
            x = -x;
        }
        if (ctrl & 0x0E) {
            /*
            TODO: Add back if head number is added to the library 
            int headNumber = (ctrl & 0x0E) >> 1;
            */
            stitchType = STOP;
        }
        if (ctrl & 0x10) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x  / 10.0, y  / 10.0, stitchType, 1);
    }
    return 1;
}

static char writeDsz(EmbPattern* pattern, FILE* file) {
    puts("writeDsz is not implemented.");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeDsz */
}

/* ---------------------------------------------------------------- */
/* format dxf */

static void readLine(FILE* file, char *str)
{
    int i;
    int past_leading_spaces;

    /* Remove leading spaces. */
    past_leading_spaces = 0;
    for (i=0; i<254; i++) {
        if (feof(file)) {
            str[i] = 0;
            break;
        }
        str[i] = fgetc(file);
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = 0;
            break;
        }
        if (str[i] == ' ') {
            if (!past_leading_spaces) {
                i--;
            }
        }
        else {
            past_leading_spaces = 0;
        }
    }
}

static char readDxf(EmbPattern* pattern, FILE* file)
{
    char dxfVersion[255];
    char section[255];
    char tableName[255];
    char layerName[255];
    char entityType[255];
    /*char layerColorHash[100][8]; */ /* hash <layerName, EmbColor> */

    int eof = 0; /* End Of File */

    char buff[255];
    EmbVector prev, pos, first;
    double bulge = 0.0;
    char firstStitch = 1;
    char bulgeFlag = 0;
    int fileLength = 0;
    first.x = 0.0;
    first.y = 0.0;
    pos.x = 0.0;
    pos.y = 0.0;
    prev.x = 0.0;
    prev.y = 0.0;
   
    puts("overriding dxf. Unimplemented for now.");
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0;

    fseek(file, 0L, SEEK_END);

    fileLength = ftell(file);
    fseek(file, 0L, SEEK_SET);

    while(ftell(file) < fileLength)
    {
        readLine(file, buff);
        /*printf("%s\n", buff);*/
        if ( (!strcmp(buff, "HEADER"))   ||
            (!strcmp(buff, "CLASSES"))  ||
            (!strcmp(buff, "TABLES"))   ||
            (!strcmp(buff, "BLOCKS"))   ||
            (!strcmp(buff, "ENTITIES")) ||
            (!strcmp(buff, "OBJECTS"))  ||
            (!strcmp(buff, "THUMBNAILIMAGE")))
        {
            strcpy(section, buff);
            printf("SECTION:%s\n", buff);
        }
        if (!strcmp(buff, "ENDSEC"))
        {
            strcpy(section, "");
            printf("ENDSEC:%s\n", buff);
        }
        if ( (!strcmp(buff, "ARC"))        ||
            (!strcmp(buff, "CIRCLE"))     ||
            (!strcmp(buff, "ELLIPSE"))    ||
            (!strcmp(buff, "LINE"))       ||
            (!strcmp(buff, "LWPOLYLINE")) ||
            (!strcmp(buff, "POINT")))
        {
            strcpy(entityType, buff);
        }
        if (!strcmp(buff, "EOF"))
        {
            eof = 1;
        }

        if (!strcmp(section, "HEADER"))
        {
            if (!strcmp(buff, "$ACADVER"))
            {
                readLine(file, buff);
                readLine(file, dxfVersion);
                /* TODO: Allow these versions when POLYLINE is handled. */
                if ((!strcmp(dxfVersion, DXF_VERSION_R10))
                || (!strcmp(dxfVersion, DXF_VERSION_R11))
                || (!strcmp(dxfVersion, DXF_VERSION_R12))
                || (!strcmp(dxfVersion, DXF_VERSION_R13))) {
                    return 0;
                }
            }
        }
        else if (!strcmp(section,"TABLES"))
        {
            if (!strcmp(buff,"ENDTAB")) {
                tableName[0] = 0;
            }

            if (tableName[0] == 0) {
                if (!strcmp(buff,"2")) { /* Table Name */
                    readLine(file, tableName);
                }
            }
            else if (!strcmp(tableName, "LAYER"))
            {
                /* Common Group Codes for Tables */
                if (!strcmp(buff,"5")) /* Handle */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"330")) /* Soft Pointer */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"100")) /* Subclass Marker */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"70")) /* Number of Entries in Table */
                {
                    readLine(file, buff);
                    continue;
                }
                /* The meaty stuff */
                else if (!strcmp(buff,"2")) /* Layer Name */
                {
                    readLine(file, layerName);
                }
                else if (!strcmp(buff,"62")) /* Color Number */
                {
                    unsigned char colorNum;
                    EmbColor* co;

                    readLine(file, buff);
                    colorNum = atoi(buff);

                    colorNum = atoi(buff);
                    co = embColor_create(_dxfColorTable[colorNum][0], _dxfColorTable[colorNum][1], _dxfColorTable[colorNum][2]);
                    if (!co) { 
                        /* TODO: error allocating memory for EmbColor */  
                        return 0; 
                    }
                    printf("inserting:%s,%d,%d,%d\n", layerName, co->r, co->g, co->b);
                    /* TODO: fix this with a lookup finish this 
                    if (embHash_insert(layerColorHash, emb_strdup(layerName), co))
                    {
                         TODO: log error: failed inserting into layerColorHash
                    }
                */
                    layerName[0] = 0;
                }
            }
        }
        else if (!strcmp(section,"ENTITIES"))
        {
            /* Common Group Codes for Entities */
            if (!strcmp(buff, "5")) /* Handle */
            {
                readLine(file, buff);
                continue;
            }
            else if (!strcmp(buff, "330")) /* Soft Pointer */
            {
                readLine(file, buff);
                continue;
            }
            else if (!strcmp(buff, "100")) /* Subclass Marker */
            {
                readLine(file, buff);
                continue;
            }
            else if (!strcmp(buff, "8")) /* Layer Name */
            {
                readLine(file, buff);
                /* embPattern_changeColor(pattern, colorIndexMap[buff]); TODO: port to C */
                continue;
            }

            if (!strcmp(entityType,"LWPOLYLINE")) {
                /* The not so important group codes */
                if (!strcmp(buff, "90")) /* Vertices */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"70")) /* Polyline Flag */
                {
                    readLine(file, buff);
                    continue;
                }
                /* TODO: Try to use the widths at some point */
                else if (!strcmp(buff,"40")) /* Starting Width */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"41")) /* Ending Width */
                {
                    readLine(file, buff);
                    continue;
                }
                else if (!strcmp(buff,"43")) /* Constant Width */
                {
                    readLine(file, buff);
                    continue;
                }
                /* The meaty stuff */
                else if (!strcmp(buff,"42")) /* Bulge */
                {
                    readLine(file, buff);
                    bulge = atof(buff);
                    bulgeFlag = 1;
                }
                else if (!strcmp(buff,"10")) /* X */
                {
                    readLine(file, buff);
                    pos.x = atof(buff);
                }
                else if (!strcmp(buff,"20")) /* Y */
                {
                    readLine(file, buff);
                    pos.y = atof(buff);

                    if (bulgeFlag) {
                        EmbArc arc;
                        bulgeFlag = 0;
                        arc.start = prev;
                        arc.end = pos;
                        if (!getArcDataFromBulge(bulge, &arc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {
                            /*TODO: error */
                            return 0;
                        }
                        if (firstStitch) {
                            /* embPattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        }
                        /* embPattern_addStitchAbs(pattern, x, y, ARC, 1); TODO: Add arcTo point to embPath pointList */
                    }
                    else {
                        /*if (firstStitch) embPattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        /*else            embPattern_addStitchAbs(pattern, x, y, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
                    }
                    prev = pos;
                    if (firstStitch) {
                        first = pos;
                        firstStitch = 0;
                    }
                }
                else if (!strcmp(buff,"0")) {
                    entityType[0] = 0;
                    firstStitch = 1;
                    if (bulgeFlag) {
                        EmbArc arc;
                        bulgeFlag = 0;
                        arc.start = prev;
                        arc.end = first;
                        if (!getArcDataFromBulge(bulge, &arc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {
                            /*TODO: error */
                            return 0;
                        }
                        prev = arc.start;
                        /* embPattern_addStitchAbs(pattern, prevX, prevY, ARC, 1); TODO: Add arcTo point to embPath pointList */
                    }
                    else
                    {
                        /* embPattern_addStitchAbs(pattern, firstX, firstY, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
                    }
                }
            } /* end LWPOLYLINE */
        } /* end ENTITIES section */
    } /* end while loop */


    /*
    EmbColor* testColor = 0;
    testColor = embHash_value(layerColorHash, "OMEGA");
    if (!testColor) printf("NULL POINTER!!!!!!!!!!!!!!\n");
    else printf("LAYERCOLOR: %d,%d,%d\n", testColor->r, testColor->g, testColor->b);
    */

    if (!eof)
    {
        /* NOTE: The EOF item must be present at the end of file to be considered a valid DXF file. */
        printf("ERROR: format-dxf.c readDxf(), missing EOF at end of DXF file\n");
    }
    return eof;
}

static char writeDxf(EmbPattern* pattern, FILE* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeDxf */
}

/* ---------------------------------------------------------------- */
/* format edr */

static char readEdr(EmbPattern* pattern, FILE* file) {
    int numberOfColors, i;

    fseek(file, 0x00, SEEK_END);
    numberOfColors = ftell(file) / 4;
    fseek(file, 0x00, SEEK_SET);

    embArray_free(pattern->threads);

    for (i = 0; i < numberOfColors; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        embPattern_addThread(pattern, t);
    }
    return 1;
}

static char writeEdr(EmbPattern* pattern, FILE* file) {
    int i;
    for (i = 0; i < pattern->threads->count; i++) {
        embColor_write(file, pattern->threads->thread[i].color, 4);
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/* format emd */

static char emdDecode(unsigned char inputByte) {
    if (inputByte >= 0x80) {
        return (-~inputByte) - 1;
    }
    return inputByte;
}

static char readEmd(EmbPattern* pattern, FILE* file) {
    unsigned char b[2];
    unsigned char jemd0[6]; /* TODO: more descriptive name */
    int width, height, colors, length;

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    if (length < 0x30) {
        puts("File invalid: shorter than the header.");
        return 0;
    }
    fseek(file, 0, SEEK_SET);

    fread(jemd0, 1, 6, file); /* TODO: check return value */
    width = fread_int16(file);
    height = fread_int16(file);
    colors = fread_int16(file);

    printf("width: %d\nheight: %d\ncolors: %d\n", width, height, colors);

    fseek(file, 0x30, SEEK_SET);

    while (!feof(file)) {
        char dx, dy;
        int flags = NORMAL;
        fread(b, 1, 2, file);

            if (b[0] == 0x80) {
                if (b[1] == 0x2A) {
                    embPattern_addStitchRel(pattern, 0, 0, STOP, 1);
                    continue;
                } else if (b[1] == 0x80) {
                    fread(b, 1, 2, file);
                    flags = TRIM;
                } else if (b[1] == 0xFD) {
                    embPattern_addStitchRel(pattern, 0, 0, END, 1);
                    break;
                } else {
                    continue;
                }
            }
            dx = emdDecode(b[0]);
            dy = emdDecode(b[1]);
            embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

static char writeEmd(EmbPattern* pattern, FILE* file) {
    puts("writeEmd not implemented.");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeEmd */
}

/* ---------------------------------------------------------------- */
/* format exp */

static char expDecode(unsigned char a1) {
    return (a1 > 0x80) ? ((-~a1) - 1) : a1;
}

static char readExp(EmbPattern* pattern, FILE* file) {
    unsigned char b[2];

    while (fread(b, 1, 2, file) == 2) {
        char dx = 0, dy = 0;
        int flags = NORMAL;
        if (b[0] == 0x80) {
            if (b[1] == 0x01) {
                if (fread(b, 1, 2, file) != 2) break;
                /* b0=0x00 and b1=0x00, but accept any, 
                not worth crashing over. */
                flags = STOP;
            } else if (b[1] == 0x04) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                flags = JUMP;
            } else if (b[1] == 0x80) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                /* b0=0x07 and b1=0x00, but accept any, 
                not worth crashing over. */
                flags = TRIM;
            }
        }
        dx = expDecode(b[0]);
        dy = expDecode(b[1]);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

static char writeExp(EmbPattern* pattern, FILE* file) {
    double xx, yy;
    int i;

    /* write stitches */
    xx = 0.0;
    yy = 0.0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        char b[4];
        char dx, dy;
        EmbStitch st = pattern->stitchList->stitch[i];
        dx = (char)round(st.x * 10.0 - xx);
        dy = (char)round(st.y * 10.0 - yy);
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        switch (st.flags) {
            case STOP:
                b[0] = (char)(0x80);
                b[1] = 0x01;
                b[2] = 0x00;
                b[3] = 0x00;
                fwrite(b, 1, 4, file);
                break;
            case JUMP:
                b[0] = (char)(0x80);
                b[1] = 0x04;
                b[2] = dx;
                b[3] = dy;
                fwrite(b, 1, 4, file);
                break;
            case TRIM:
                b[0] = (char)(0x80);
                b[1] = (char)(0x80);
                b[2] = 0x07;
                b[3] = 0x00;
                fwrite(b, 1, 4, file);
                break;
            default: /* STITCH */
                b[0] = dx;
                b[1] = dy;
                fwrite(b, 1, 2, file);
                break;
        }
    }
    fprintf(file, "\x1a");
    return 1;
}

/* ---------------------------------------------------------------- */
/* format exy */

int decode_exy_flags(unsigned char b2) {
    int returnCode = 0;
    if (b2 == 0xF3) {
        return (END);
    }
    if ((b2 & 0xC3) == 0xC3) {
        return TRIM | STOP;
    }
    if (b2 & 0x80) {
        returnCode |= TRIM;
    }
    if (b2 & 0x40) {
        returnCode |= STOP;
    }
    return returnCode;
}

static char readExy(EmbPattern* pattern, FILE* file) {
    unsigned char b[3];

    fseek(file, 0x100, SEEK_SET);
    while (fread(b, 1, 3, file) == 3) {
        int flags, x, y;
        decode_tajima_ternary(b, &x, &y);
        flags = decode_exy_flags(b[2]);
        if (flags & END) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
    }
    return 1;
}

static char writeExy(EmbPattern* pattern, FILE* file) {
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeExy */
}

/* ---------------------------------------------------------------- */
/* format eys */

static char readEys(EmbPattern* pattern, FILE* file) {
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readEys */
}

static char writeEys(EmbPattern* pattern, FILE* file) {
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeEys */
}

/* ---------------------------------------------------------------- */
/* format fxy */

static char readFxy(EmbPattern* pattern, FILE* file) {
    /* TODO: review for combining code. This line appears 
        to be the only difference from the GT format. */
    fseek(file, 0x100, SEEK_SET);

    while (!feof(file)) {
        int stitchType = NORMAL;
        int b1 = fgetc(file);
        int b2 = fgetc(file);
        unsigned char commandByte = (unsigned char)fgetc(file);

        if (commandByte == 0x91) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        if ((commandByte & 0x01) == 0x01)
            stitchType = TRIM;
        if ((commandByte & 0x02) == 0x02)
            stitchType = STOP;
        if ((commandByte & 0x20) == 0x20)
            b1 = -b1;
        if ((commandByte & 0x40) == 0x40)
            b2 = -b2;
        embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    return 1;
}

static char writeFxy(EmbPattern* pattern, FILE* file) {
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeFxy */
}

/* ---------------------------------------------------------------- */
/* format gc */

/* Smoothie G-Code */

static char readGc(EmbPattern* pattern, FILE* file) {
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readGc */
}

static char writeGc(EmbPattern* pattern, FILE* file) {
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeGc */
}

/* ---------------------------------------------------------------- */
/* format gnc */

static char readGnc(EmbPattern* pattern, FILE* file)
{
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readGnc */
}

static char writeGnc(EmbPattern* pattern, FILE* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeGnc */
}

/* ---------------------------------------------------------------- */
/* format gt */

static char readGt(EmbPattern* pattern, FILE* file) {
    /* TODO: review for combining code. This line appears 
        to be the only difference from the FXY format. */
    fseek(file, 0x200, SEEK_SET);

    while (!feof(file)) {
        int stitchType = NORMAL;
        int b1 = fgetc(file);
        int b2 = fgetc(file);
        unsigned char commandByte = (unsigned char)fgetc(file);

        if (commandByte == 0x91) {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        if ((commandByte & 0x01) == 0x01) {
            stitchType = TRIM;
        }
        if ((commandByte & 0x02) == 0x02) {
            stitchType = STOP;
        }
        if ((commandByte & 0x20) == 0x20) {
            b1 = -b1;
        }
        if ((commandByte & 0x40) == 0x40) {
            b2 = -b2;
        }
        embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    return 1;
}

static char writeGt(EmbPattern* pattern, FILE* file) {
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeGt */
}

/* ---------------------------------------------------------------- */
/* format hus */

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
    char* decompressedData = (char*)malloc(sizeof(char)*decompressedContentLength);
    if (!decompressedData) { printf("ERROR: format-hus.c husDecompressData(), cannot allocate memory for decompressedData\n"); return 0; }
    hus_decompress((char*)input, compressedInputLength, decompressedData, &decompressedContentLength);
    return (unsigned char *)decompressedData;
}

static unsigned char* husCompressData(unsigned char* input, int decompressedInputSize, int* compressedSize)
{
    char* compressedData = (char*)malloc(sizeof(char)*decompressedInputSize*2);
    if (!compressedData) { printf("ERROR: format-hus.c husCompressData(), cannot allocate memory for compressedData\n"); return 0; }
    hus_compress((char*)input, decompressedInputSize, compressedData, compressedSize);
    return (unsigned char *)compressedData;
}

static int husDecodeByte(unsigned char b)
{
    return (char)b;
}

static unsigned char husEncodeByte(double f)
{
    return (unsigned char)(int)round(f);
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

static char readHus(EmbPattern* pattern, FILE* file)
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

    puts("Overridden. readHus is not implemented for now.");
    return 0;

    fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x00, SEEK_SET);

    magicCode = fread_int32(file);
    if (EMB_DEBUG) {
        printf("magicCode: %d\n", magicCode);
    }
    numberOfStitches = fread_int32(file);
    numberOfColors = fread_int32(file);

    positiveXHoopSize = fread_int16(file);
    positiveYHoopSize = fread_int16(file);
    negativeXHoopSize = fread_int16(file);
    negativeYHoopSize = fread_int16(file);
    if (EMB_DEBUG) {
        printf("these should be put in the EmbPattern:\n");
        printf("%d\n", positiveXHoopSize);
        printf("%d\n", positiveYHoopSize);
        printf("%d\n", negativeXHoopSize);
        printf("%d\n", negativeYHoopSize);
    }

    attributeOffset = fread_int32(file);
    xOffset = fread_int32(file);
    yOffset = fread_int32(file);

    stringVal = (unsigned char*)malloc(sizeof(unsigned char)*8);
    if (!stringVal) {
        printf("ERROR: format-hus.c readHus(), cannot allocate memory for stringVal\n");
        return 0;
    }
    fread(stringVal, 1, 8, file); /* TODO: check return value */

    unknown = fread_int16(file);
    if (EMB_DEBUG) {
        printf("TODO: identify this unknown variable: %d\n", unknown);
    }
    for (i = 0; i < numberOfColors; i++)
    {
        int pos = fread_int16(file);
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

    for (i = 0; i < numberOfStitches; i++)
    {
        embPattern_addStitchRel(pattern,
                                husDecodeByte(xDecompressed[i]) / 10.0,
                                husDecodeByte(yDecompressed[i]) / 10.0,
                                husDecodeStitchType(attributeDataDecompressed[i]), 1);
    }

    if (stringVal) { free(stringVal); }
    free(xData);
    if (xDecompressed) { free(xDecompressed); }
    free(yData);
    if (yDecompressed) { free(yDecompressed); }
    free(attributeData);
    if (attributeDataDecompressed) { free(attributeDataDecompressed); }

    return 1;
}

static char writeHus(EmbPattern* pattern, FILE* file)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor, attributeSize, xCompressedSize, yCompressedSize, i;
    double previousX, previousY;
    short right, top, bottom, left;
    unsigned int code, colors, offset1, offset2;
    unsigned char *xValues = 0, *yValues = 0, *attributeValues = 0,
        *attributeCompressed = 0, *xCompressed = 0, *yCompressed = 0;
    
    stitchCount = pattern->stitchList->count;
    /* embPattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */
    minColors = pattern->threads->count;
    patternColor = minColors;
    if (minColors > 24) minColors = 24;
    code = 0x00C8AF5B;
    fwrite_int(file, &code, EMB_INT32_LITTLE);
    fwrite_int(file, &stitchCount, EMB_INT32_LITTLE);
    fwrite_int(file, &minColors, EMB_INT32_LITTLE);

    boundingRect = embPattern_calcBoundingBox(pattern);
    right = (short) round(boundingRect.right * 10.0);
    top = (short) -round(boundingRect.top * 10.0);
    left = (short) round(boundingRect.left * 10.0);
    bottom = (short) -round(boundingRect.bottom * 10.0);
    fwrite_int(file, &right, EMB_INT16_LITTLE);
    fwrite_int(file, &top, EMB_INT16_LITTLE);
    fwrite_int(file, &left, EMB_INT16_LITTLE);
    fwrite_int(file, &bottom, EMB_INT16_LITTLE);

    colors = 0x2A + 2 * minColors;
    fwrite_int(file, &colors, EMB_INT32_LITTLE);

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
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st;
        st = pattern->stitchList->stitch[i];
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
    fwrite_int(file, &offset1, EMB_INT32_LITTLE);
    fwrite_int(file, &offset2, EMB_INT32_LITTLE);
    fpad(file, 0, 10);

    for (i = 0; i < patternColor; i++) {
        short color_index = (short)embThread_findNearestColor_fromThread(pattern->threads->thread[i].color, (EmbThread*)husThreads, 29);
        fwrite_int(file, &color_index, EMB_INT16_LITTLE);
    }

    fwrite(attributeCompressed, 1, attributeSize, file);
    fwrite(xCompressed, 1, xCompressedSize, file);
    fwrite(yCompressed, 1, yCompressedSize, file);

    free(xValues);
    free(xCompressed);
    free(yValues);
    free(yCompressed);
    free(attributeValues);
    free(attributeCompressed);

    return 1;
}

/* ---------------------------------------------------------------- */
/* format inb */

static char readInb(EmbPattern* pattern, FILE* file)
{
    /* TODO: determine what this represents */
    unsigned char fileDescription[8], nullVal, bytesUnknown[300];
    int stitchCount, x, y, i, fileLength;
    short width, height, colorCount, unknown3, unknown2,
        nullbyte, left, right, top, bottom, imageWidth, imageHeight;

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fread(fileDescription, 1, 8, file); /* TODO: check return value */
    nullVal = (char)fgetc(file);
    fread_int16(file);
    stitchCount = fread_int32(file);
    width = fread_int16(file);
    height = fread_int16(file);
    colorCount = fread_int16(file);
    unknown3 = fread_int16(file);
    unknown2 = fread_int16(file);
    imageWidth = fread_int16(file);
    imageHeight = fread_int16(file);
    fread(bytesUnknown, 1, 300, file); /* TODO: check return value */
    nullbyte = fread_int16(file);
    left = fread_int16(file);
    right = fread_int16(file);
    top = fread_int16(file);
    bottom = fread_int16(file);
    if (EMB_DEBUG) {
        printf("nullVal:                 %c\n", nullVal);
        printf("stitchCount:             %d\n", stitchCount);
        printf("width:                   %d\n", width);
        printf("height:                  %d\n", height);
        printf("colorCount:              %d\n", colorCount);
        printf("Identify the purpose of:\n");
        printf("    unknown3:            %d\n", unknown3);
        printf("    unknown2:            %d\n", unknown2);
        printf("imageWidth:              %d\n", imageWidth);
        printf("imageHeight:             %d\n", imageHeight);
        printf("This should be null:     %d\n", nullbyte);
        printf("right:                   %d\n", right);
        printf("left:                    %d\n", left);
        printf("bottom:                  %d\n", bottom);
        printf("top:                     %d\n", top);
    }

    fseek(file, 0x2000, SEEK_SET);
    /* Calculate stitch count since header has been seen to be blank */
    stitchCount = (int)((fileLength - 0x2000) / 3);
    for (i = 0; i < stitchCount; i++) {
        unsigned char type;
        int stitch = NORMAL;
        x = (char)fgetc(file);
        y = (char)fgetc(file);
        type = (char)fgetc(file);
        if ((type & 0x40) > 0)
            x = -x;
        if ((type & 0x10) > 0)
            y = -y;
        if ((type & 1) > 0)
            stitch = STOP;
        if ((type & 2) > 0)
            stitch = TRIM;
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitch, 1);
    }
    embPattern_flipVertical(pattern);

    return 1;
}

static char writeInb(EmbPattern* pattern, FILE* file)
{
    puts("writeInb not implemented.");
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeInb */
}

/* ---------------------------------------------------------------- */
/* format inf */

static char readInf(EmbPattern* pattern, FILE* file)
{
    int numberOfColors, i;
    char colorType[50];
    char colorDescription[50];
    EmbThread t;

    fseek(file, 12, SEEK_CUR);
    numberOfColors = fread_uint32_be(file);

    embArray_free(pattern->threads);
    pattern->threads = embArray_create(EMB_THREAD);

    for (i = 0; i < numberOfColors; i++) {
        fseek(file, 4, SEEK_CUR);
        embColor_read(file, &(t.color), 3);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        embPattern_addThread(pattern, t);
        fseek(file, 2, SEEK_CUR);
        binaryReadString(file, colorType, 50);
        binaryReadString(file, colorDescription, 50);
    }
    return 1;
}

static char writeInf(EmbPattern* pattern, FILE* file) {
    int i, bytesRemaining;
    
    binaryWriteUIntBE(file, 0x01);
    binaryWriteUIntBE(file, 0x08);
    /* write place holder offset */
    binaryWriteUIntBE(file, 0x00);
    binaryWriteUIntBE(file, pattern->threads->count);

    for (i = 0; i < pattern->threads->count; i++) {
        char buffer[50];
        EmbColor c;
        c = pattern->threads->thread[i].color;
        sprintf(buffer, "RGB(%d,%d,%d)", (int)c.r, (int)c.g, (int)c.b);
        /* record length */
        binaryWriteUShortBE(file, (unsigned short)(14 + strlen(buffer))); 
        binaryWriteUShortBE(file, (unsigned short)i); /* record number */
        embColor_write(file, c, 3);
        binaryWriteUShortBE(file, (unsigned short)i); /* needle number */
        fwrite("RGB\0", 1, 4, file);
        fprintf(file, "%s", buffer);
        fwrite("\0", 1, 1, file);
    }
    /* It appears that there should be a pad here otherwise it clips into
     * the color description. */
    fpad(file, 0, 8);
    fseek(file, -8, SEEK_END);
    bytesRemaining = ftell(file);
    fseek(file, 8, SEEK_SET);
    binaryWriteUIntBE(file, bytesRemaining);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format jef */

static int jefGetHoopSize(int width, int height) {
    if (width < 50 && height < 50) {
        return HOOP_50X50;
    }
    if (width < 110 && height < 110) {
        return HOOP_110X110;
    }
    if (width < 140 && height < 200) {
        return HOOP_140X200;
    }
    return ((int) HOOP_110X110);
}

static char jefDecode(unsigned char inputByte) {
    if (inputByte >= 0x80) {
        return (char) ((-~inputByte) - 1);
    }
    return ((char) inputByte);
}

static void jefSetHoopFromId(EmbPattern* pattern, int hoopCode) {
    if (!pattern) {
        printf("ERROR: format-jef.c jefSetHoopFromId(), pattern argument is null\n");
        return;
    }
    switch (hoopCode) {
        case HOOP_126X110:
            pattern->hoop.height = 126.0;
            pattern->hoop.width = 110.0;
            break;
        case HOOP_50X50:
            pattern->hoop.height = 50.0;
            pattern->hoop.width = 50.0;
            break;
        case HOOP_110X110:
           pattern->hoop.height = 110.0;
            pattern->hoop.width = 110.0;
            break;
        case HOOP_140X200:
            pattern->hoop.height = 140.0;
            pattern->hoop.width = 200.0;
            break;
        case HOOP_230X200:
            pattern->hoop.height = 230.0;
            pattern->hoop.width = 200.0;
            break;
    }
}

struct hoop_padding
{
    int left;
    int right;
    int top;
    int bottom;
};

void read_hoop(FILE *file, struct hoop_padding *hoop, char *label)
{
    hoop->left = fread_int32(file);
    hoop->top = fread_int32(file);
    hoop->right = fread_int32(file);
    hoop->bottom = fread_int32(file);
    if (EMB_DEBUG) {
        printf("%s\n", label);
        printf("    left:      %d\n", hoop->left);
        printf("    top:       %d\n", hoop->top);
        printf("    right:     %d\n", hoop->right);
        printf("    bottom:    %d\n", hoop->bottom);
    }
}

static char readJef(EmbPattern* pattern, FILE* file) {
    int stitchOffset, formatFlags, numberOfColors, numberOfStitchs;
    int hoopSize, i, stitchCount;
    struct hoop_padding bounds, rectFrom110x110;
    struct hoop_padding rectFrom50x50, rectFrom200x140, rect_from_custom;
    char date[8], time[8];

    stitchOffset = fread_int32(file);
    formatFlags = fread_int32(file); /* TODO: find out what this means */

    fread((unsigned char*) date, 1, 8, file); /* TODO: check return value */
    fread((unsigned char*) time, 1, 8, file); /* TODO: check return value */
    numberOfColors = fread_int32(file);
    numberOfStitchs = fread_int32(file);
    hoopSize = fread_int32(file);
    jefSetHoopFromId(pattern, hoopSize);
    if (numberOfStitchs > MAX_STITCHES) {
        numberOfStitchs = MAX_STITCHES;
        puts("ERROR: this file is corrupted or has too many stitches.");
        return 0;
    }
    if (EMB_DEBUG) {
        printf("format flags = %d\n", formatFlags);
        printf("number of colors = %d\n", numberOfColors);
        printf("number of stitches = %d\n", numberOfStitchs);
    }

    read_hoop(file, &bounds, "bounds");
    read_hoop(file, &rectFrom110x110, "rectFrom110x110");
    read_hoop(file, &rectFrom50x50, "rectFrom50x50");
    read_hoop(file, &rectFrom200x140, "rectFrom200x140");
    read_hoop(file, &rect_from_custom, "rect_from_custom");

    for (i = 0; i < numberOfColors; i++) {
        embPattern_addThread(pattern, jefThreads[fread_int32(file) % 79]);
    }
    fseek(file, stitchOffset, SEEK_SET);
    stitchCount = 0;
    while (stitchCount < numberOfStitchs + 100) {
        unsigned char b[2];
        char dx = 0, dy = 0;
        int flags = NORMAL;
        if (fread(b, 1, 2, file) != 2) {
            break;
        }
        
        if (b[0] == 0x80) {
            if (b[1] & 1) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                flags = STOP;
            }
            else if ((b[1] == 2) || (b[1] == 4) || b[1] == 6) {
                if (fread(b, 1, 2, file) != 2) {
                    break;
                }
                flags = TRIM;
            }
            else if (b[1] == 0x10) {
                embPattern_addStitchRel(pattern, 0.0, 0.0, END, 1);
                break;
            }
        }
        dx = jefDecode(b[0]);
        dy = jefDecode(b[1]);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
        stitchCount++;
    }
    return 1;
}

static void jefEncode(unsigned char* b, char dx, char dy, int flags) {
    if (!b) {
        printf("ERROR: format-jef.c expEncode(), b argument is null\n");
        return;
    }
    if (flags == STOP) {
        b[0] = 0x80;
        b[1] = 1;
        b[2] = dx;
        b[3] = dy;
    } else if (flags == END) {
        b[0] = 0x80;
        b[1] = 0x10;
        b[2] = 0;
        b[3] = 0;
    } else if (flags == TRIM || flags == JUMP) {
        b[0] = 0x80;
        b[1] = 2;
        b[2] = dx;
        b[3] = dy;
    } else {
        b[0] = dx;
        b[1] = dy;
    }
}

static char writeJef(EmbPattern* pattern, FILE* file)
{
    int colorlistSize, minColors, designWidth, designHeight, i;
    EmbRect boundingRect;
    EmbTime time;
    EmbStitch st;
    int data;
    double dx = 0.0, dy = 0.0, xx = 0.0, yy = 0.0;
    unsigned char b[4];

    embPattern_correctForMaxStitchLength(pattern, 12.7, 12.7);

    colorlistSize = pattern->threads->count;
    minColors = embMaxInt(colorlistSize, 6);
    binaryWriteInt(file, 0x74 + (minColors * 4));
    binaryWriteInt(file, 0x0A);

    embTime_initNow(&time);

    fprintf(file, "%04d%02d%02d%02d%02d%02d", (int)(time.year + 1900),
            (int)(time.month + 1), (int)(time.day), (int)(time.hour),
            (int)(time.minute), (int)(time.second));
    fpad(file, 0, 2);
    fwrite_int(file, &(pattern->threads->count), EMB_INT32_LITTLE);
    data = pattern->stitchList->count + embMaxInt(0, (6 - colorlistSize) * 2) + 1;
    fwrite_int(file, &data, EMB_INT32_LITTLE);

    boundingRect = embPattern_calcBoundingBox(pattern);

    designWidth = (int)(embRect_width(boundingRect) * 10.0);
    designHeight = (int)(embRect_width(boundingRect) * 10.0);

    binaryWriteInt(file, jefGetHoopSize(designWidth, designHeight));

    /* Distance from center of Hoop */
    binaryWriteInt(file, (int) (designWidth / 2));  /* left */
    binaryWriteInt(file, (int) (designHeight / 2)); /* top */
    binaryWriteInt(file, (int) (designWidth / 2));  /* right */
    binaryWriteInt(file, (int) (designHeight / 2)); /* bottom */

    /* Distance from default 110 x 110 Hoop */
    if (embMinDouble(550 - designWidth / 2, 550 - designHeight / 2) >= 0) {
        binaryWriteInt(file, embMaxInt(-1, 550 - designWidth / 2));  /* left */
        binaryWriteInt(file, embMaxInt(-1, 550 - designHeight / 2)); /* top */
        binaryWriteInt(file, embMaxInt(-1, 550 - designWidth / 2));  /* right */
        binaryWriteInt(file, embMaxInt(-1, 550 - designHeight / 2)); /* bottom */
    } else {
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
    }

    /* Distance from default 50 x 50 Hoop */
    if (embMinDouble(250 - designWidth / 2, 250 - designHeight / 2) >= 0) {
        binaryWriteInt(file, (int) embMaxInt(-1, 250 - designWidth / 2));  /* left */
        binaryWriteInt(file, (int) embMaxInt(-1, 250 - designHeight / 2)); /* top */
        binaryWriteInt(file, (int) embMaxInt(-1, 250 - designWidth / 2));  /* right */
        binaryWriteInt(file, (int) embMaxInt(-1, 250 - designHeight / 2)); /* bottom */
    } else {
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
    }

    /* Distance from default 140 x 200 Hoop */
    binaryWriteInt(file, (int) (700 - designWidth / 2));   /* left */
    binaryWriteInt(file, (int) (1000 - designHeight / 2)); /* top */
    binaryWriteInt(file, (int) (700 - designWidth / 2));   /* right */
    binaryWriteInt(file, (int) (1000 - designHeight / 2)); /* bottom */

    /* repeated Distance from default 140 x 200 Hoop */
    /* TODO: Actually should be distance to custom hoop */
    binaryWriteInt(file, (int) (630 - designWidth / 2));  /* left */
    binaryWriteInt(file, (int) (550 - designHeight / 2)); /* top */
    binaryWriteInt(file, (int) (630 - designWidth / 2));  /* right */
    binaryWriteInt(file, (int) (550 - designHeight / 2)); /* bottom */

    for (i = 0; i < pattern->threads->count; i++) {
        int j = embThread_findNearestColor_fromThread(pattern->threads->thread[i].color, (EmbThread *)jefThreads, 79);
        binaryWriteInt(file, j);
    }

    for (i = 0; i < (minColors - colorlistSize); i++) {
        binaryWriteInt(file, 0x0D);
    }

    for (i = 0; i < pattern->stitchList->count; i++) {
        b[0] = 0;
        b[1] = 0;
        b[2] = 0;
        b[3] = 0;
        st = pattern->stitchList->stitch[i];
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        jefEncode(b, (char)round(dx), (char)round(dy), st.flags);
        if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
            fwrite(b, 1, 4, file);
        } else {
            fwrite(b, 1, 2, file);
        }
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/* format ksm */

static void ksmEncode(unsigned char* b, char dx, char dy, int flags) {
    if (!b) {
        printf("ERROR: format-ksm.c ksmEncode(), b argument is null\n");
        return;
    }
    /* TODO: How to encode JUMP stitches? JUMP must be handled. 
    Also check this for the EXP format since it appears to be similar */
    if (flags == TRIM) {
        b[0] = 128;
        b[1] = 2;
        b[2] = dx;
        b[3] = dy;
    } else if (flags == STOP) {
        b[0] = 128;
        b[1] = 1;
        b[2] = dx;
        b[3] = dy;
    } else {
        b[0] = dx;
        b[1] = dy;
    }
}

static char readKsm(EmbPattern* pattern, FILE* file) {
    int prevStitchType = NORMAL;
    char b[3];
    fseek(file, 0x200, SEEK_SET);
    while (fread(b, 1, 3, file) == 3) {
        int flags = NORMAL;

        if (((prevStitchType & 0x08) == 0x08) && (b[2] & 0x08) == 0x08) {
            flags = STOP;
        } else if ((b[2] & 0x1F) != 0) {
            flags = TRIM;
        }
        prevStitchType = b[2];
        if (b[2] & 0x40) {
            b[1] = -b[1];
        }
        if (b[2] & 0x20) {
            b[0] = -b[0];
        }
        embPattern_addStitchRel(pattern, b[1] / 10.0, b[0] / 10.0, flags, 1);
    }
    return 1;
}

static char writeKsm(EmbPattern* pattern, FILE* file) {
    double xx, yy;
    int i;
    unsigned char b[4];

    fpad(file, 0, 0x200);
    /* write stitches */
    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        double dx, dy;
        EmbStitch st = pattern->stitchList->stitch[i];
        dx = st.x - xx;
        dy = st.y - yy;
        xx = st.x;
        yy = st.y;
        ksmEncode(b, (char)(dx * 10.0), (char)(dy * 10.0), st.flags);
        fprintf(file, "%c%c", b[0], b[1]);
    }
    fprintf(file, "\x1a");
    return 1;
}

/* ---------------------------------------------------------------- */
/* format max */

/* Pfaff MAX embroidery file format */

static char readMax(EmbPattern* pattern, FILE* file) {
    unsigned char b[8];

    fseek(file, 0xD5, SEEK_SET);
    /* stitchCount = fread_uint32(file); CHECK IF THIS IS PRESENT */
    /* READ STITCH RECORDS */
    while (fread(b, 1, 8, file) == 8) {
        double dx, dy;
        int flags;
        flags = NORMAL;
        dx = pfaffDecode(b[0], b[1], b[2]);
        dy = pfaffDecode(b[4], b[5], b[6]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    embPattern_flipVertical(pattern);
    return 1;
}

static char writeMax(EmbPattern* pattern, FILE* file) {
    int i;
    unsigned char header[] = {
        0x56,0x43,0x53,0x4D,0xFC,0x03,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,
        0xF6,0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x05,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x33,0x37,0x38,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4D,0x61,0x64,0x65,0x69,0x72,0x61,0x20,
        0x52,0x61,0x79,0x6F,0x6E,0x20,0x34,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x01,0x38,0x09,0x31,0x33,0x30,0x2F,0x37,0x30,0x35,0x20,0x48,0xFA,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00 };
    double x, y;
    EmbStitch st;

    fwrite(header, 1, 0xD5, file);
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        x = (int)round(st.x * 10.0);
        y = (int)round(st.y * 10.0);
        write_24bit(file, x);
        write_24bit(file, y);
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/* format mit */

static char readMit(EmbPattern* pattern, FILE* file) {
    unsigned char data[2];

    while (fread(data, 1, 2, file) == 2) {
        int x = mitDecodeStitch(data[0]);
        int y = mitDecodeStitch(data[1]);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, NORMAL, 1);
    }
    return 1;
}

static char writeMit(EmbPattern* pattern, FILE* file) {
    double xx, yy;
    int i;

    embPattern_correctForMaxStitchLength(pattern, 0x1F, 0x1F);
    xx = 0;
    yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        unsigned char b[2];
        EmbStitch st = pattern->stitchList->stitch[i];
        b[0] = mitEncodeStitch(st.x - xx);
        b[1] = mitEncodeStitch(st.y - yy);
        xx = st.x;
        yy = st.y;
        fwrite(b, 1, 2, file);
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/* format new */

static char readNew(EmbPattern* pattern, FILE* file) {
    unsigned int stitchCount;
    unsigned char data[3];

    stitchCount = fread_uint16(file);
    if (EMB_DEBUG) {
        printf("stitch count = %d\n", stitchCount);
    }
    while (fread(data, 1, 3, file) == 3) {
        int x = decodeNewStitch(data[0]);
        int y = decodeNewStitch(data[1]);
        int flag = NORMAL;
        char val = data[2];
        if (data[2] & 0x40) {
            x = -x;
        }
        if (data[2] & 0x20) {
            y = -y;
        }
        if (data[2] & 0x10) {
            flag = TRIM;
        }
        if (data[2] & 0x01) {
            flag = JUMP;
        }
        if ((val & 0x1E) == 0x02) {
            flag = STOP;
        }
        /* Unknown values, possibly TRIM
        155 = 1001 1011 = 0x9B
        145 = 1001 0001 = 0x91
        */
        /*val = (data[2] & 0x1C);
        if (val != 0 && data[2] != 0x9B && data[2] != 0x91)
        {
            int z = 1;
        }*/
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flag, 1);
    }

    return 1;
}

static char writeNew(EmbPattern* pattern, FILE* file) {
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeNew */
}

/* ---------------------------------------------------------------- */
/* format ofm */

static char* ofmReadLibrary(FILE* file)
{
    int stringLength = 0;
    char* libraryName = 0;
    /* FF FE FF */
    unsigned char leadIn[3];

    if (!file) { printf("ERROR: format-ofm.c ofmReadLibrary(), file argument is null\n"); return 0; }

    fread(leadIn, 1, 3, file); /* TODO: check return value */
    stringLength = (char)fgetc(file);
    libraryName = (char*)malloc(sizeof(char) * stringLength * 2);
    if (!libraryName) { printf("ERROR: format-ofm.c ofmReadLibrary(), unable to allocate memory for libraryName\n"); return 0; }
    fread((unsigned char*)libraryName, 1, stringLength * 2, file); /* TODO: check return value */
    return libraryName;
}

static int ofmReadClass(FILE* file)
{
    int len;
    char* s = 0;

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadClass(), file argument is null\n");
        return 0;
    }

    fread_int16(file);
    len = fread_int16(file);

    s = (char*)malloc(sizeof(char) * len + 1);
    if (!s) {
        printf("ERROR: format-ofm.c ofmReadClass(), unable to allocate memory for s\n");
        return 0;
    }
    fread((unsigned char*)s, 1, len, file);
    /* TODO: check return value */
    s[len] = '\0';
    if (strcmp(s, "CExpStitch") == 0) {
        return 0x809C;
    }
    if (strcmp(s, "CColorChange") == 0) {
        return 0xFFFF;
    }
    return 0;
}

static void ofmReadBlockHeader(FILE* file)
{
    int val[10], i; /* TODO: determine what these represent */
    unsigned char len;
    char* s = 0;
    unsigned short short1;
    short unknown1, unknown2;
    /* TODO: determine what the unknown variables represent */
    int unknown3;
    /* TODO: determine what this represents */
    
    if (!file) {
        printf("ERROR: format-ofm.c ofmReadBlockHeader(), file argument is null\n");
        return;
    }

    unknown1 = fread_int16(file);
    unknown2 = (short)fread_int32(file);
    unknown3 = fread_int32(file);
    if (EMB_DEBUG) {
        printf("unknown1 = %d\n", unknown1);
        printf("unknown2 = %d\n", unknown2);
        printf("unknown3 = %d\n", unknown3);
    }

    /* int v = fread(&v, 1, 3, file)?; TODO: review */
    fread_int16(file);
    (char)fgetc(file);
    len = (char)fgetc(file);
    s = (char*)malloc(2 * len);
    if (!s) { printf("ERROR: format-ofm.c ofmReadBlockHeader(), unable to allocate memory for s\n"); return; }
    fread((unsigned char *)s, 1, 2 * len, file);
    /* TODO: check return value */
    /* 0, 0, 0, 0, 1, 1, 1, 0, 64, 64 */
    for (i=0; i<10; i++) {
        val[i] = fread_int32(file);
        if (EMB_DEBUG) {
            printf("val[%d] = %d\n", i, val[i]);
        }
    }
    short1 = fread_int16(file); /*  0 */
    if (EMB_DEBUG) {
        printf("short1 = %d\n", short1);
    }
}

static void ofmReadColorChange(FILE* file, EmbPattern* pattern)
{
    if (!file) { printf("ERROR: format-ofm.c ofmReadColorChange(), file argument is null\n"); return; }
    if (!pattern) { printf("ERROR: format-ofm.c ofmReadColorChange(), pattern argument is null\n"); return; }

    ofmReadBlockHeader(file);
    embPattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
}

static void ofmReadThreads(FILE* file, EmbPattern* p)
{
    int i, numberOfColors, stringLen, numberOfLibraries;
    char* primaryLibraryName = 0;
    char* expandedString = 0;

    if (!file) {
        printf("ERROR: format-ofm.c ofmReadThreads(), file argument is null\n");
        return;
    }
    if (!p) {
        printf("ERROR: format-ofm.c ofmReadThreads(), p argument is null\n");
        return;
    }

    /* FF FE FF 00 */
    fread_int32(file);

    numberOfColors = fread_int16(file);

    fread_int16(file);
    fread_int16(file);
    stringLen = fread_int16(file);
    expandedString = (char*)malloc(stringLen);
    if (!expandedString) { printf("ERROR: format-ofm.c ofmReadThreads(), unable to allocate memory for expandedString\n"); return; }
    fread((unsigned char*)expandedString, 1, stringLen, file);
    /* TODO: check return value */
    for (i = 0; i < numberOfColors; i++) {
        EmbThread thread;
        char colorNumberText[11], colorName[512];
        int threadLibrary, colorNameLength, colorNumber;
        embColor_read(file, &(thread.color), 4);
        threadLibrary = fread_int16(file);
        fseek(file, 2, SEEK_CUR);
        colorNumber = fread_int32(file);
        fseek(file, 3, SEEK_CUR);
        colorNameLength = (char)fgetc(file);
        fread(colorName, 1, colorNameLength*2, file);
        if (EMB_DEBUG) {
            printf("threadLibrary = %d\n", threadLibrary);
            printf("colorNumber = %d\n", colorNumber);
        }
        /* TODO: check return value */
        fseek(file, 2, SEEK_CUR);
        sprintf(colorNumberText, "%10d", colorNumber);
        strcpy(thread.catalogNumber, colorNumberText);
        strcpy(thread.description, colorName);
        embPattern_addThread(p, thread);
    }
    fseek(file, 2, SEEK_CUR);
    primaryLibraryName = ofmReadLibrary(file);
    numberOfLibraries = fread_int16(file);

    if (EMB_DEBUG) {
        printf("primary library name: %s\n", primaryLibraryName);
    }

    for (i = 0; i < numberOfLibraries; i++)
    {
        /*libraries.Add( TODO: review */
        char* libName = ofmReadLibrary(file);
        free(libName);
    }
}

static double ofmDecode(unsigned char b1, unsigned char b2)
{
    double val = (double)(short)(b1 << 8 | b2);
    return val;
}

static void ofmReadExpanded(FILE* file, EmbPattern* p)
{
    int i, numberOfStitches = 0;

    if (!file) { printf("ERROR: format-ofm.c ofmReadExpanded(), file argument is null\n"); return; }
    if (!p) { printf("ERROR: format-ofm.c ofmReadExpanded(), p argument is null\n"); return; }

    ofmReadBlockHeader(file);
    numberOfStitches = fread_int32(file);

    for (i = 0; i < numberOfStitches; i++)
    {
        unsigned char stitch[5];
        fread(stitch, 1, 5, file); /* TODO: check return value */
        if (stitch[0] == 0)
        {
            embPattern_addStitchAbs(p, ofmDecode(stitch[1], stitch[2]) / 10.0, ofmDecode(stitch[3], stitch[4]) / 10.0, i == 0 ? JUMP : NORMAL, 1);
        }
        else if (stitch[0] == 32)
        {
            embPattern_addStitchAbs(p, ofmDecode(stitch[1], stitch[2]) / 10.0, ofmDecode(stitch[3], stitch[4]) / 10.0, i == 0 ? TRIM : NORMAL, 1);
        }
    }
}

static char readOfm(EmbPattern* pattern, FILE* fileCompound)
{
    int unknownCount, key = 0, classNameLength;
    char* s = 0;
    FILE *file;
    bcf_file* bcfFile = 0;

    if (EMB_DEBUG) {
        puts("Overridden during development.");
        return 0;
    }

    bcfFile = (bcf_file*)malloc(sizeof(bcf_file));
    if (!bcfFile) { printf("ERROR: format-ofm.c readOfm(), unable to allocate memory for bcfFile\n"); return 0; }
    bcfFile_read(fileCompound, bcfFile);
    file = GetFile(bcfFile, fileCompound, "EdsIV Object");
    bcf_file_free(bcfFile);
    bcfFile = 0;
    fseek(file, 0x1C6, SEEK_SET);
    ofmReadThreads(file, pattern);
    fseek(file, 0x110, SEEK_CUR);
    fread_int32(file);
    classNameLength = fread_int16(file);
    s = (char*)malloc(sizeof(char) * classNameLength);
    if (!s) { printf("ERROR: format-ofm.c readOfm(), unable to allocate memory for s\n"); return 0; }
    fread((unsigned char*)s, 1, classNameLength, file); /* TODO: check return value */
    unknownCount = fread_int16(file);
    /* TODO: determine what unknown count represents */
    if (EMB_DEBUG) {
        printf("unknownCount = %d\n", unknownCount);
    }

    fread_int16(file);
    key = ofmReadClass(file);
    while(1)
    {
        if (key == 0xFEFF)
        {
            break;
        }
        if (key == 0x809C)
        {
            ofmReadExpanded(file, pattern);
        }
        else
        {
            ofmReadColorChange(file, pattern);
        }
        key = fread_uint16(file);
        if (key == 0xFFFF)
        {
            ofmReadClass(file);
        }
    }

    embPattern_flip(pattern, 1, 1);

    return 1;
}

static char writeOfm(EmbPattern* pattern, FILE* file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeOfm */
}

/* ---------------------------------------------------------------- */
/* format pcd */

static char readPcd(EmbPattern* pattern, const char *fileName, FILE* file) {
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    double dx = 0, dy = 0;
    int st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount = 0;

    version = (char)fgetc(file);
    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * 3 for PCS with large hoop (115x120)
     */
    hoopSize = (char)fgetc(file);
    colorCount = fread_uint16(file);
    if (EMB_DEBUG) {
        printf("version: %d\n", version);
        printf("hoop size: %d\n", hoopSize);
        printf("color count: %d\n", colorCount);
    }

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        embPattern_addThread(pattern, t);
    }
    if (allZeroColor) {
        embPattern_loadExternalColorFile(pattern, fileName);
    }
    st = fread_uint16(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        int flags;
        if (fread(b, 1, 9, file) != 9) {
            break;
        }
        flags = NORMAL;
        if (b[8] & 0x01) {
            flags = STOP;
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
        /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[1], b[2], b[3]);
        dy = pfaffDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

static char writePcd(EmbPattern* pattern, FILE* file) {
    int i;

    /* TODO: select hoop size defaulting to Large PCS hoop */
    fwrite("2\x03", 1, 2, file);
    binaryWriteUShort(file, (unsigned short)pattern->threads->count);
    for (i = 0; i < pattern->threads->count; i++) {
        EmbColor color = pattern->threads->thread[i].color;
        embColor_write(file, color, 4);
    }

    fpad(file, 0, 4*(16-i));
    /* write remaining colors to reach 16 */

    binaryWriteUShort(file, (unsigned short)pattern->stitchList->count);
    /* write stitches */
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st = pattern->stitchList->stitch[i];
        pfaffEncode(file, (int)round(st.x * 10.0), (int)round(st.y * 10.0), st.flags);
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/* format pcm */

static char readPcm(EmbPattern* pattern, FILE* file) {
    int i = 0, st;
    double dx = 0, dy = 0;
    int header_size = 16*2+6;

    if (EMB_DEBUG) {
        printf("TODO: check header_size %d\n", header_size);
    }

    fseek(file, 4, SEEK_SET);
    for (i = 0; i < 16; i++) {
        int colorNumber;
        (void)fgetc(file); /* zero */
        colorNumber = fgetc(file);
        embPattern_addThread(pattern, pcmThreads[colorNumber]);
    }
    st = fread_uint16_be(file);
    st = embMinInt(st, MAX_STITCHES);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        int flags;
        unsigned char b[9];
        flags = NORMAL;
        if (fread(b, 1, 9, file) != 9) {
            break;
        }
        if (b[8] & 0x01) {
            flags = STOP;
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
        /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[2], b[1], b[0]);
        dy = pfaffDecode(b[6], b[5], b[4]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

static char writePcm(EmbPattern* pattern, FILE* file) {
    puts("overridden, defaulting to dst");
    writeDst(pattern, file);
    return 0; /*TODO: finish writePcm */
}

/* ---------------------------------------------------------------- */
/* format pcq */

static char readPcq(EmbPattern* pattern, const char* fileName, FILE* file)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    double dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount;

    version = (char)fgetc(file);
    hoopSize = (char)fgetc(file);
    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * 3 for PCS with large hoop (115x120)
     */
    colorCount = fread_uint16(file);
    if (EMB_DEBUG) {
        printf("version: %d\n", version);
        printf("hoop size: %d\n", hoopSize);
        printf("color count: %d\n", colorCount);
    }

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        embPattern_addThread(pattern, t);
    }
    if (allZeroColor) {
        embPattern_loadExternalColorFile(pattern, fileName);
    }
    st = fread_uint16(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
        flags = NORMAL;
        if (fread(b, 1, 9, file) != 9) {
            break;
        }

        if (b[8] & 0x01) {
            flags = STOP;
        }
        else if (b[8] & 0x04) {
            flags = TRIM;
        }
        else if (b[8] != 0) {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[1], b[2], b[3]);
        dy = pfaffDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

static char writePcq(EmbPattern* pattern, FILE* file)
{
    int i;

    /* TODO: select hoop size defaulting to Large PCS hoop */
    fwrite("2\x03", 1, 2, file);
    binaryWriteUShort(file, (unsigned short)pattern->threads->count);
    for (i = 0; i < pattern->threads->count; i++) {
        EmbColor color = pattern->threads->thread[i].color;
        embColor_write(file, color, 4);
    }

    /* write remaining colors to reach 16 */
    fpad(file, 0, (16-i)*4);

    binaryWriteUShort(file, (unsigned short)pattern->stitchList->count);
    /* write stitches */
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st = pattern->stitchList->stitch[i];
        pfaffEncode(file, (int)round(st.x * 10.0), (int)round(st.y * 10.0), st.flags);
    }
    return 1;
}


/* ---------------------------------------------------------------- */
/* format pcs */

static char readPcs(EmbPattern* pattern, const char* fileName, FILE* file)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    double dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount;

    version = (char)fgetc(file);
    hoopSize = (char)fgetc(file);  /* 0 for PCD, 1 for PCQ (MAXI), 2 for PCS with small hoop(80x80), */
                                      /* and 3 for PCS with large hoop (115x120) */

    switch(hoopSize)
    {
        case 2:
            pattern->hoop.width = 80.0;
            pattern->hoop.height = 80.0;
            break;
        case 3:
            pattern->hoop.width = 115;
            pattern->hoop.height = 120.0;
            break;
    }

    colorCount = fread_uint16(file);
    if (EMB_DEBUG) {
        printf("version: %d\n", version);
        printf("hoop size: %d\n", hoopSize);
        printf("color count: %d\n", colorCount);
    }

    for (i = 0; i < colorCount; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        if (t.color.r || t.color.g || t.color.b) {
            allZeroColor = 0;
        }
        embPattern_addThread(pattern, t);
    }
    if (allZeroColor) {
        embPattern_loadExternalColorFile(pattern, fileName);
    }
    st = fread_uint16(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++)
    {
        flags = NORMAL;
        if (fread(b, 1, 9, file) != 9)
            break;

        if (b[8] & 0x01)
        {
            flags = STOP;
        }
        else if (b[8] & 0x04)
        {
            flags = TRIM;
        }
        else if (b[8] != 0)
        {
            /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pfaffDecode(b[1], b[2], b[3]);
        dy = pfaffDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }

    return 1;
}

static char writePcs(EmbPattern* pattern, FILE* file)
{
    int i;

    /* TODO: select hoop size defaulting to Large PCS hoop */
    fwrite("2\x03", 1, 2, file);
    binaryWriteUShort(file, (unsigned short)pattern->threads->count);
    for (i = 0; i < pattern->threads->count; i++) {
        EmbColor color = pattern->threads->thread[i].color;
        embColor_write(file, color, 4);
    }

    /* write remaining colors to reach 16 */
    fpad(file, 0, 4*(16-i));

    binaryWriteUShort(file, (unsigned short)pattern->stitchList->count);
    /* write stitches */
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st = pattern->stitchList->stitch[i];
        pfaffEncode(file, (int)round(st.x * 10.0), (int)round(st.y * 10.0), st.flags);
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/* format pec */

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

void readPecStitches(EmbPattern* pattern, FILE* file) {
    FILE *f = file;
    unsigned char b[2];

    while (fread(b, 1, 2, f)==2) {
        int val1 = (int)b[0];
        int val2 = (int)b[1];

        int stitchType = NORMAL;
        if (b[0] == 0xFF && b[1] == 0x00) {
            embPattern_end(pattern);
            return;
        }
        if (b[0] == 0xFE && b[1] == 0xB0) {
            (void)fgetc(f);
            embPattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
            continue;
        }
        /* High bit set means 12-bit offset, otherwise 7-bit signed delta */
        if (val1 & 0x80) {
            if (val1 & 0x20) stitchType = TRIM;
            if (val1 & 0x10) stitchType = JUMP;
            val1 = ((val1 & 0x0F) << 8) + val2;

            /* Signed 12-bit arithmetic */
            if (val1 & 0x800) {
                val1 -= 0x1000;
            }
        }
        else if (val1 >= 0x40) {
            val1 -= 0x80;
        }
        if (val2 & 0x80) {
            if (val2 & 0x20) stitchType = TRIM;
            if (val2 & 0x10) stitchType = JUMP;
            val2 = ((val2 & 0x0F) << 8) + fgetc(file);

            /* Signed 12-bit arithmetic */
            if (val2 & 0x800) {
                val2 -= 0x1000;
            }
        }
        else if (val2 >= 0x40) {
            val2 -= 0x80;
        }

        embPattern_addStitchRel(pattern, val1 / 10.0,
                val2 / 10.0, stitchType, 1);
    }
}

static void pecEncodeJump(FILE* file, int x, int types) {
    int outputVal = abs(x) & 0x7FF;
    unsigned int orPart = 0x80;
    unsigned char toWrite;

    if (!file) { 
        printf("ERROR: format-pec.c pecEncodeJump(), file argument is null\n");
        return; 
    }
    if (types & TRIM) {
        orPart |= 0x20;
    }
    if (types & JUMP) {
        orPart |= 0x10;
    }
    if (x < 0) {
        outputVal = (x + 0x1000) & 0x7FF;
        outputVal |= 0x800;
    }
    toWrite = (unsigned char)(((outputVal >> 8) & 0x0F) | orPart);
    fwrite(&toWrite, 1, 1, file);
    toWrite = (unsigned char)(outputVal & 0xFF);
    fwrite(&toWrite, 1, 1, file);
}

static void pecEncodeStop(FILE* file, unsigned char val)
{
    if (!file) {
        printf("ERROR: format-pec.c pecEncodeStop(), file argument is null\n");
        return;
    }
    fwrite("\xFE\xB0", 1, 2, file);
    fwrite(&val, 1, 1, file);
}

static char readPec(EmbPattern* pattern, const char *fileName, FILE* file) {
    unsigned int graphicsOffset;
    unsigned char colorChanges;
    int i;

    if (EMB_DEBUG) {
        printf("fileName: %s\n", fileName);
    }

    if (!check_header_present(file, 0x20A))
        return 0;

    fseek(file, 0x38, SEEK_SET);
    colorChanges = (unsigned char)(char)fgetc(file);
    for (i = 0; i <= colorChanges; i++) {
        embPattern_addThread(pattern, pecThreads[(char)fgetc(file) % 65]);
    }

    /* Get Graphics offset */
    fseek(file, 0x20A, SEEK_SET);

    graphicsOffset = (unsigned int)(fgetc(file));
    graphicsOffset |= (fgetc(file) << 8);
    graphicsOffset |= (fgetc(file) << 16);

    (void)(char)fgetc(file); /* 0x31 */
    (void)(char)fgetc(file); /* 0xFF */
    (void)(char)fgetc(file); /* 0xF0 */
    /* Get X and Y size in .1 mm */
    /* 0x210 */
    fread_int16(file); /* x size */
    fread_int16(file); /* y size */

    fread_int16(file); /* 0x01E0 */
    fread_int16(file); /* 0x01B0 */
    fread_int16(file); /* distance left from start */
    fread_int16(file); /* distance up from start */

    /* Begin Stitch Data */
    /* 0x21C */
    /*unsigned int end = graphicsOffset + 0x208; */
    readPecStitches(pattern, file);
    embPattern_flipVertical(pattern);
    return 1;
}

static void pecEncode(FILE* file, EmbPattern* p) {
    double thisX = 0.0;
    double thisY = 0.0;
    unsigned char stopCode = 2;
    int i;

    if (!file) {
        printf("ERROR: format-pec.c pecEncode(), file argument is null\n");
        return;
    }
    if (!p) {
        printf("ERROR: format-pec.c pecEncode(), p argument is null\n");
        return;
    }

    for (i = 0; i < p->stitchList->count; i++) {
        int deltaX, deltaY;
        EmbStitch s = p->stitchList->stitch[i];

        deltaX = (int)round(s.x - thisX);
        deltaY = (int)round(s.y - thisY);
        thisX += (double)deltaX;
        thisY += (double)deltaY;

        if (s.flags & STOP) {
            pecEncodeStop(file, stopCode);
            if (stopCode == (unsigned char)2) {
                stopCode = (unsigned char)1;
            } else {
                stopCode = (unsigned char)2;
            }
        } else if (s.flags & END) {
            fwrite("\xFF", 1, 1, file);
            break;
        } else if (deltaX < 63 && deltaX > -64 && deltaY < 63 && deltaY > -64 && (!(s.flags & (JUMP | TRIM)))) {
            unsigned char out[2];
            if (deltaX < 0) {
                out[0] = (unsigned char)(deltaX + 0x80);
            }
            else {
                out[0] = (unsigned char)deltaX;
            }
            if (deltaY < 0) {
                out[1] = (unsigned char)(deltaY + 0x80);
            }
            else {
                out[1] = (unsigned char)deltaY;
            }
            fwrite(out, 1, 2, file);
        } else {
            pecEncodeJump(file, deltaX, s.flags);
            pecEncodeJump(file, deltaY, s.flags);
        }
    }
}

static void writeImage(FILE* file, unsigned char image[][48]) {
    int i, j;

    if (!file) {
        printf("ERROR: format-pec.c writeImage(), file argument is null\n");
        return;
    }
    for (i = 0; i < 38; i++) {
        for (j = 0; j < 6; j++) {
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

void writePecStitches(EmbPattern* pattern, FILE* file, const char *fileName) {
    EmbRect bounds;
    unsigned char image[38][48], toWrite;
    int i, j, flen, graphicsOffsetLocation;
    int graphicsOffsetValue, height, width;
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
    fwrite("LA:", 1, 3, file);
    flen = (int)(dotPos - start);

    while (start < dotPos) {
        fwrite(start, 1, 1, file);
        start++;
    }
    fpad(file, 0x20, 16-flen);
    fwrite("\x0D", 1, 1, file);
    fpad(file, 0x20, 12);
    fwrite("\xff\x00\x06\x26", 1, 4, file);

    fpad(file, 0x20, 12);
    toWrite = (unsigned char)(pattern->threads->count-1);
    fwrite(&toWrite, 1, 1, file);

    for (i = 0; i < pattern->threads->count; i++) {
        EmbColor thr = pattern->threads->thread[i].color;
        unsigned char color = (unsigned char)
            embThread_findNearestColor_fromThread(thr, 
            (EmbThread*)pecThreads, pecThreadCount);
        fwrite(&color, 1, 1, file);
    }
    fpad(file, 0x20, (int)(0x1CF - pattern->threads->count));
    fpad(file, 0x00, 2);

    graphicsOffsetLocation = ftell(file);
    /* placeholder bytes to be overwritten */
    fpad(file, 0x00, 3);

    fwrite("\x31\xff\xf0", 1, 3, file);

    bounds = embPattern_calcBoundingBox(pattern);

    height = (int)round(embRect_height(bounds));
    width = (int)round(embRect_width(bounds));
    /* write 2 byte x size */
    binaryWriteShort(file, (short)width);
    /* write 2 byte y size */
    binaryWriteShort(file, (short)height);

    /* Write 4 miscellaneous int16's */
    fwrite("\x01\xe0\x01\xb0", 1, 4, file);

    binaryWriteUShortBE(file, (unsigned short)(0x9000 | -(int)round(bounds.left)));
    binaryWriteUShortBE(file, (unsigned short)(0x9000 | -(int)round(bounds.top)));

    pecEncode(file, pattern);
    graphicsOffsetValue = ftell(file) - graphicsOffsetLocation + 2;
    fseek(file, graphicsOffsetLocation, SEEK_SET);

    fputc((unsigned char)(graphicsOffsetValue & 0xFF), file);
    fputc((unsigned char)((graphicsOffsetValue >> 8) & 0xFF), file);
    fputc((unsigned char)((graphicsOffsetValue >> 16) & 0xFF), file);

    fseek(file, 0x00, SEEK_END);

    /* Writing all colors */
    memcpy(image, imageWithFrame, 48*38);

    yFactor = 32.0 / height;
    xFactor = 42.0 / width;
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st = pattern->stitchList->stitch[i];
        int x = (int)round((st.x - bounds.left) * xFactor) + 3;
        int y = (int)round((st.y - bounds.top) * yFactor) + 3;
        if (x<=0 || x>48) continue;
        if (y<=0 || y>38) continue;
        image[y][x] = 1;
    }
    writeImage(file, image);

    /* Writing each individual color */
    j = 0;
    for (i = 0; i < pattern->threads->count; i++) {
        memcpy(image, imageWithFrame, 48*38);
        for (; j < pattern->stitchList->count; j++) {
            EmbStitch st = pattern->stitchList->stitch[j];
            int x = (int)round((st.x - bounds.left) * xFactor) + 3;
            int y = (int)round((st.y - bounds.top) * yFactor) + 3;
            if (x<=0 || x>48) continue;
            if (y<=0 || y>38) continue;
            if (st.flags & STOP) {
                break;
            }
            image[y][x] = 1;
        }
        writeImage(file, image);
    }
}

static char writePec(EmbPattern* pattern, const char* fileName, FILE* file) {
    /* TODO: There needs to be a matching flipVertical() call after the write 
        to ensure multiple writes from the same pattern work properly */
    embPattern_flipVertical(pattern); 
    embPattern_fixColorCount(pattern);
    embPattern_correctForMaxStitchLength(pattern, 12.7, 204.7);
    embPattern_scale(pattern, 10.0);
    fwrite("#PEC0001", 1, 8, file);
    writePecStitches(pattern, file, fileName);
    return 1;
}


/* ---------------------------------------------------------------- */
/* format pel */

static char readPel(void) {
    puts("ERROR: readPel is not implemented.");
    return 0; /*TODO: finish readPel */
}

static char writePel(void) {
    puts("ERROR: writePel is not implemented.");
    return 0; /*TODO: finish writePel */
}

/* ---------------------------------------------------------------- */
/* format pem */

static char readPem(void)
{
    puts("ERROR: readPem is not implemented.");
    return 0; /*TODO: finish ReadPem */
}

static char writePem(void)
{
    puts("ERROR: writePem is not implemented.");
    return 0; /*TODO: finish writePem */
}

/* ---------------------------------------------------------------- */
/* format pes */

#define PES0001         0
#define PES0020         1
#define PES0022         2
#define PES0030         3
#define PES0040         4
#define PES0050         5
#define PES0055         6
#define PES0056         7
#define PES0060         8
#define PES0070         9
#define PES0080        10
#define PES0090        11
#define PES0100        12
#define N_PES_VERSIONS 13

static char *pes_version_strings[] = {
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

static int pes_version = PES0001;

static void readPESHeaderV5(FILE* file, EmbPattern* pattern);
static void readPESHeaderV6(FILE* file, EmbPattern* pattern);
static void readPESHeaderV7(FILE* file, EmbPattern* pattern);
static void readPESHeaderV8(FILE* file, EmbPattern* pattern);
static void readPESHeaderV9(FILE* file, EmbPattern* pattern);
static void readPESHeaderV10(FILE* file, EmbPattern* pattern);

static void readDescriptions(FILE* file, EmbPattern* pattern);
static void readHoopName(FILE* file, EmbPattern* pattern);
static void readImageString(FILE* file, EmbPattern* pattern);
static void readProgrammableFills(FILE* file, EmbPattern* pattern);
static void readMotifPatterns(FILE* file, EmbPattern* pattern);
static void readFeatherPatterns(FILE* file, EmbPattern* pattern);
static void readThreads(FILE* file, EmbPattern* pattern);

static void fskip(FILE* file, int n)
{
    fseek(file, n, SEEK_CUR);
}

static char readPes(EmbPattern* pattern, const char *fileName, FILE* file) {
    int pecstart, numColors, x, version, i;
    char signature[9];
    fread(signature, 1, 8, file);
    signature[8] = 0;
    pecstart = fread_int32(file);

    version = 0;
    for (i=0; i<N_PES_VERSIONS; i++) {
        if (!strcmp(signature, pes_version_strings[i])) {
            version = i;
            break;
        }
    }

    if (version >= PES0040) {
        fskip(file, 4);
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

    if (EMB_DEBUG) {
        printf("debug information for reading fileName: %s\n", fileName);
        printf("pecstart = %d\n", pecstart);
    }

    /* fseek(file, pecstart + 48, SEEK_SET);
     * This seems wrong based on the readPESHeader functions. */
    fseek(file, pecstart, SEEK_SET);

    numColors = fgetc(file) + 1;
    for (x = 0; x < numColors; x++) {
        unsigned int color_index = fgetc(file);
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

static void readDescriptions(FILE *file, EmbPattern* pattern)
{
    int DesignStringLength;
    int categoryStringLength;
    int authorStringLength;
    int keywordsStringLength;
    int commentsStringLength;
    /*
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

static void readPESHeaderV5(FILE *file, EmbPattern* pattern)
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

static void readPESHeaderV6(FILE *file, EmbPattern* pattern)
{
    fseek(file, 36, SEEK_CUR);
    readImageString(file, pattern);
    fseek(file, 24, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

static void readPESHeaderV7(FILE *file, EmbPattern* pattern)
{
    fseek(file, 36, SEEK_CUR);
    readImageString(file, pattern);
    fseek(file, 24, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}
    
static void readPESHeaderV8(FILE *file, EmbPattern* pattern)
{
    fseek(file, 38, SEEK_CUR);
    readImageString(file, pattern);
    fseek(file, 26, SEEK_CUR);
    readProgrammableFills(file, pattern);
    readMotifPatterns(file, pattern);
    readFeatherPatterns(file, pattern);
    readThreads(file, pattern);
}

static void readPESHeaderV9(FILE *file, EmbPattern* pattern)
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

static void readPESHeaderV10(FILE *file, EmbPattern* pattern)
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

static void readHoopName(FILE* file, EmbPattern* pattern)
{
    int hoopNameStringLength = fgetc(file);
    /*
    String hoopNameString = readString(hoopNameStringLength);
    if (hoopNameString.length() != 0) {
        pattern.setMetadata("hoop_name", hoopNameString);
    }
    */
}

static void readImageString(FILE* file, EmbPattern* pattern)
{
    int fromImageStringLength = fgetc(file);
    /*
    String fromImageString = readString(fromImageStringLength);
    if (fromImageString.length() != 0) {
        pattern.setMetadata("image_file", fromImageString);
    }
    */
}

static void readProgrammableFills(FILE* file, EmbPattern* pattern) {
    int numberOfProgrammableFillPatterns = fread_int16(file);
    if (numberOfProgrammableFillPatterns != 0) {
        return;
    }
}

static void readMotifPatterns(FILE* file, EmbPattern* pattern) {
    int numberOfMotifPatterns = fread_int16(file);
    if (numberOfMotifPatterns != 0) {
        return;
    }
}

static void readFeatherPatterns(FILE* file, EmbPattern* pattern) {
    int featherPatternCount = fread_int16(file);
    if (featherPatternCount != 0) {
        return;
    }
}
    
static void readThreads(FILE* file, EmbPattern* pattern) {
    int numberOfColors, i;
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
        fskip(file, 5);
        descriptionStringLength = fgetc(file);
        /* strcpy(thread.description, readString(descriptionStringLength)); */

        brandStringLength = fgetc(file);
        /* strcpy(thread.brand, readString(brandStringLength)); */

        threadChartStringLength = fgetc(file);
        /* strcpy(thread.threadChart, readString(threadChartStringLength)); */

        embPattern_addThread(pattern, thread);
    }
}


static void pesWriteSewSegSection(EmbPattern* pattern, FILE* file) {
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

    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbColor color;
        EmbStitch st = pattern->stitchList->stitch[i];
        flag = st.flags;
        if (st.color < pattern->threads->count) {
            color = pattern->threads->thread[st.color].color;
        }
        else {
            color = pecThreads[0].color;
        }
        newColorCode = embThread_findNearestColor_fromThread(color, (EmbThread*)pecThreads, pecThreadCount);
        if (newColorCode != colorCode) {
            colorCount++;
            colorCode = newColorCode;
        }
        while (i < pattern->stitchList->count && (flag == st.flags)) {
            st = pattern->stitchList->stitch[i];
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
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbColor color;
        EmbStitch st;
        st = pattern->stitchList->stitch[i];
        j = i;
        flag = st.flags;
        color = pattern->threads->thread[st.color].color;
        newColorCode = embThread_findNearestColor_fromThread(color, (EmbThread*)pecThreads, pecThreadCount);
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
        while (j < pattern->stitchList->count && (flag == st.flags)) {
            st = pattern->stitchList->stitch[j];
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
        while (j < pattern->stitchList->count && (flag == st.flags)) {
            st = pattern->stitchList->stitch[j];
            binaryWriteShort(file, (short)(st.x - bounds.left));
            binaryWriteShort(file, (short)(st.y + bounds.top));
        }
        if (j < pattern->stitchList->count ) {
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
    if (colorInfo) {
        free(colorInfo);
    }
}

static void pesWriteEmbOneSection(EmbPattern* pattern, FILE* file) {
    /* TODO: pointer safety */
    int i;
    float x;
    int hoopHeight = 1800, hoopWidth = 1300;
    EmbRect bounds;
    binaryWriteShort(file, 0x07); /* string length */
    fwrite("CEmbOne", 1, 7, file);
    bounds = embPattern_calcBoundingBox(pattern);

    binaryWriteShort(file, 0);
    binaryWriteShort(file, 0);
    binaryWriteShort(file, 0);
    binaryWriteShort(file, 0);

    binaryWriteShort(file, 0);
    binaryWriteShort(file, 0);
    binaryWriteShort(file, 0);
    binaryWriteShort(file, 0);

    /* AffineTransform */
    x = 1.0;
    fwrite_int(file, &x, EMB_INT32_LITTLE);
    x = 0.0;
    fwrite_int(file, &x, EMB_INT32_LITTLE);
    x = 0.0;
    fwrite_int(file, &x, EMB_INT32_LITTLE);
    x = 1.0;
    fwrite_int(file, &x, EMB_INT32_LITTLE);
    x = (float)((embRect_width(bounds) - hoopWidth) / 2);
    fwrite_int(file, &x, EMB_INT32_LITTLE);
    x = (float)((embRect_height(bounds) + hoopHeight) / 2);
    fwrite_int(file, &x, EMB_INT32_LITTLE);

    binaryWriteShort(file, 1);
    binaryWriteShort(file, 0); /* Translate X */
    binaryWriteShort(file, 0); /* Translate Y */
    binaryWriteShort(file, (short)embRect_width(bounds));
    binaryWriteShort(file, (short)embRect_height(bounds));

    fpad(file, 0, 8);
    /*WriteSubObjects(br, pes, SubBlocks); */
}

static char writePes(EmbPattern* pattern,  const char *fileName, FILE* file) {
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


/* ---------------------------------------------------------------- */
/* format phb */

static char readPhb(EmbPattern* pattern, FILE* file)
{
    unsigned int fileOffset;
    short colorCount;
    int i;

    fseek(file, 0x71, SEEK_SET);
    colorCount = fread_int16(file);

    for (i = 0; i < colorCount; i++)
    {
        EmbThread t = pecThreads[fgetc(file)];
        embPattern_addThread(pattern, t);
    }

    /* TODO: check that file begins with #PHB */
    fseek(file, 0x54, SEEK_SET);
    fileOffset = 0x52;
    fileOffset += fread_uint32(file);

    fseek(file, fileOffset, SEEK_SET);
    fileOffset += fread_uint32(file) + 2;

    fseek(file, fileOffset, SEEK_SET);
    fileOffset += fread_uint32(file);

    fseek(file, fileOffset + 14, SEEK_SET); /* 28 */

    colorCount = (short)(char)fgetc(file);
    for (i = 0; i <  colorCount; i++)
    {
        (char)fgetc(file);
    }
    fread_int32(file); /* bytes to end of file */
    fread_int32(file);
    (char)fgetc(file);

    fread_int16(file);
    fread_int16(file);
    fread_int16(file);
    fread_int16(file);
    fread_int16(file);
    fread_int16(file);
    readPecStitches(pattern, file);

    embPattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhb */
}

static char writePhb(void)
{
    puts("ERROR: writePhb is not implemented.");
    return 0; /*TODO: finish writePhb */
}

/* ---------------------------------------------------------------- */
/* format phc */

static char readPhc(EmbPattern* pattern, FILE* file)
{
    int colorChanges, version, bytesInSection2;
    unsigned short pecOffset, bytesInSection, bytesInSection3;
    char pecAdd;
    int i;

    fseek(file, 0x07, SEEK_SET);
    version = (char)fgetc(file) - 0x30; /* converting from ansi number */
    fseek(file, 0x4D, SEEK_SET);
    colorChanges = fread_uint16(file);

    for (i = 0; i < colorChanges; i++)
    {
        EmbThread t = pecThreads[(int)(char)fgetc(file)];
        embPattern_addThread(pattern, t);
    }
    fseek(file, 0x2B, SEEK_SET);
    pecAdd = (char)fgetc(file);
    fread_uint32(file); /* file length */
    pecOffset = fread_uint16(file);
    fseek(file, pecOffset + pecAdd, SEEK_SET);
    bytesInSection = fread_uint16(file);
    fseek(file, bytesInSection, SEEK_CUR);
    bytesInSection2 = fread_uint32(file);
    fseek(file, bytesInSection2, SEEK_CUR);
    bytesInSection3 = fread_uint16(file);
    fseek(file, bytesInSection3 + 0x12, SEEK_CUR);

    if (EMB_DEBUG) {
        printf("version: %d\n", version);
    }

    readPecStitches(pattern, file);

    embPattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhc */
}

static char writePhc(void)
{
    puts("ERROR: writePhc is not implemented.");
    return 0; /*TODO: finish writePhc */
}

/* ---------------------------------------------------------------- */
/* format plt */

static char readPlt(EmbPattern* pattern, FILE* file) {
    double x, y;
    double scalingFactor = 40;
    char input[512];

    /* TODO: replace all scanf code */
    while (emb_readline(file, input, 511)) {
        if (input[0] == 'P' && input[1] == 'D') {
            /* TODO: replace all scanf code */
            if (sscanf(input, "PD%lf,%lf;", &x, &y) < 2) {
                break;
            }
            embPattern_addStitchAbs(pattern, x / scalingFactor,
                            y / scalingFactor, NORMAL, 1);
        } else if (input[0] == 'P' && input[1] == 'U') {
            /* TODO: replace all scanf code */
            if (sscanf(input, "PU%lf,%lf;", &x, &y) < 2) {
                break;
            }
            embPattern_addStitchAbs(pattern, x / scalingFactor,
                    y / scalingFactor, STOP, 1);
        }
    }
    return 1;
}

static char writePlt(EmbPattern* pattern, FILE* file) {
    /* TODO: pointer safety */
    double scalingFactor = 40;
    char firstStitchOfBlock = 1;
    int i;

    fprintf(file, "IN;");
    fprintf(file, "ND;");

    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch stitch;
        stitch = pattern->stitchList->stitch[i];
        if (stitch.flags & STOP) {
            firstStitchOfBlock = 1;
        }
        if (firstStitchOfBlock) {
            fprintf(file, "PU%f,%f;", stitch.x * scalingFactor,
                    stitch.y * scalingFactor);
            fprintf(file, "ST0.00,0.00;");
            fprintf(file, "SP0;");
            fprintf(file, "HT0;");
            fprintf(file, "HS0;");
            fprintf(file, "TT0;");
            fprintf(file, "TS0;");
            firstStitchOfBlock = 0;
        } else {
            fprintf(file, "PD%f,%f;", stitch.x * scalingFactor,
                stitch.y * scalingFactor);
        }
    }
    fprintf(file, "PU0.0,0.0;");
    fprintf(file, "PU0.0,0.0;");
    return 1; /*TODO: finish WritePlt */
}

/* ---------------------------------------------------------------- */
/* format rgb */

static char readRgb(EmbPattern* pattern, FILE* file) {
    int i, numberOfColors;

    fseek(file, 0x00, SEEK_END);
    numberOfColors = ftell(file) / 4;

    embArray_free(pattern->threads);
    pattern->threads = embArray_create(EMB_THREAD);

    fseek(file, 0x00, SEEK_SET);
    for (i = 0; i < numberOfColors; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 4);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        embPattern_addThread(pattern, t);
    }
    return 1;
}

static char writeRgb(EmbPattern* pattern, FILE* file) {
    int i;

    for (i = 0; i < pattern->threads->count; i++) {
        unsigned char b[4];
        EmbColor c = pattern->threads->thread[i].color;
        b[0] = c.r;
        b[1] = c.g;
        b[2] = c.b;
        b[3] = 0;
        fwrite(b, 1, 4, file);
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/* format sew */

static char sewDecode(unsigned char inputByte) {
    /* TODO: fix return statement */
    return (inputByte >= 0x80) ? (char) (-~(inputByte - 1)) : (char) inputByte;
}

static char readSew(EmbPattern* pattern, FILE* file) {
    int i, flags, numberOfColors, fileLength;
    char dx, dy, thisStitchIsJump = 0;

    fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x00, SEEK_SET);
    numberOfColors = fgetc(file);
    numberOfColors += (fgetc(file) << 8);
    

    for (i = 0; i < numberOfColors; i++) {
        int color = fread_int16(file);
        embPattern_addThread(pattern, jefThreads[color%78]);
    }
    fseek(file, 0x1D78, SEEK_SET);

    for (i = 0; ftell(file) < fileLength; i++) {
        unsigned char b[2];
        fread(b, 1, 2, file);

        flags = NORMAL;
        if (thisStitchIsJump) {
            flags = TRIM;
            thisStitchIsJump = 0;
        }
        if (b[0] == 0x80) {
            if (b[1] == 1) {
                fread(b, 1, 2, file);
                flags = STOP;
            } else if ((b[1] == 0x02) || (b[1] == 0x04)) {
                thisStitchIsJump = 1;
                fread(b, 1, 2, file);
                flags = TRIM;
            } else if (b[1] == 0x10) {
               break;
            }
        }
        dx = sewDecode(b[0]);
        dy = sewDecode(b[1]);
        if (abs(dx) == 127 || abs(dy) == 127) {
            thisStitchIsJump = 1;
            flags = TRIM;
        }
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    printf("current position: %ld\n", ftell(file));
    return 1;
}

static char writeSew(EmbPattern* pattern, FILE* file) {
    int i;
    double xx = 0.0, yy = 0.0;
    binaryWriteShort(file, pattern->threads->count);

    if (EMB_DEBUG) {
        printf("Debugging Information\n");
        printf("number of colors = %d\n", pattern->threads->count);
        printf("number of stitches = %d\n", pattern->stitchList->count);
    }

    for (i = 0; i < pattern->threads->count; i++) {
        short thr;
        EmbColor col;
        col = pattern->threads->thread[i].color;
        thr = embThread_findNearestColor_fromThread(col, (EmbThread *)jefThreads, 79);
        binaryWriteShort(file, thr);
    }
    fpad(file, 0, 0x1D78 - 2 - pattern->threads->count * 2);

    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st;
        unsigned char b[4];
        double dx, dy;
        st = pattern->stitchList->stitch[i];
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        if (st.flags & STOP) {
            b[0] = 0x80;
            b[1] = 0x01;
            b[2] = (char)round(dx);
            b[3] = (char)round(dy);
            fwrite(b, 1, 4, file);
        } else if (st.flags & END) {
            b[0] = 0x80;
            b[1] = 0x10;
            b[2] = 0;
            b[3] = 0;
            fwrite(b, 1, 4, file);
        } else if ((st.flags & TRIM) || (st.flags & JUMP)) {
            b[0] = 0x80;
            b[1] = 2;
            b[2] = (char)round(dx);
            b[3] = (char)round(dy);
            fwrite(b, 1, 4, file);
        } else {
            b[0] = (char)round(dx);
            b[1] = (char)round(dy);
            fwrite(b, 1, 2, file);
        }
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/* format shv */

static char shvDecode(unsigned char inputByte)
{
    if (inputByte >= 0x80)
    {
        return (char)-((unsigned char)((~inputByte) + 1));
    }
    return ((char)inputByte);
}

static short shvDecodeShort(unsigned short inputByte)
{
    if (inputByte > 0x8000)
    {
        return (short)-((unsigned short)((~inputByte) + 1));
    }
    return ((short)inputByte);
}

static char readShv(EmbPattern* pattern, FILE* file)
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
    short left,top,right,bottom;
    char something2, numberOfSections, something3;
    int stitchesPerColor[256];
    int stitchesSinceChange = 0;
    int currColorIndex = 0;
    unsigned short sx, sy;

    if (!check_header_present(file, 25)) {
        return 0;
    }

    fseek(file, strlen(headerText), SEEK_SET);
    fileNameLength = fgetc(file);
    fseek(file, fileNameLength, SEEK_CUR);
    designWidth = fgetc(file);
    designHeight = fgetc(file);
    halfDesignWidth = fgetc(file);
    halfDesignHeight = fgetc(file);
    halfDesignWidth2 = fgetc(file);
    halfDesignHeight2 = fgetc(file);
    if ((designHeight % 2) == 1)
    {
        fseek(file, ((designHeight + 1)*designWidth)/2, SEEK_CUR);
    }
    else
    {
        fseek(file, (designHeight*designWidth)/2, SEEK_CUR);
    }
    numberOfColors = fgetc(file);
    magicCode = fread_uint16(file);
    (char)fgetc(file);
    something = fread_int32(file);
    left = fread_int16(file);
    top = fread_int16(file);
    right = fread_int16(file);
    bottom = fread_int16(file);

    something2 = (char)fgetc(file);
    numberOfSections = fgetc(file);
    something3 = (char)fgetc(file);
    
    if (EMB_DEBUG) {
        printf("magicCode: %d\n", magicCode);
        printf("something: %d\n", something);
        printf("halfDesignWidth: %d\n", halfDesignWidth);
        printf("halfDesignHeight: %d\n", halfDesignHeight);
        printf("halfDesignWidth2: %d\n", halfDesignWidth2);
        printf("halfDesignHeight2: %d\n", halfDesignHeight2);
        printf("left: %d\n", left);
        printf("top: %d\n", top);
        printf("right: %d\n", right);
        printf("bottom: %d\n", bottom);
        printf("something2: %d\n", something2);
        printf("number of sections: %d\n", numberOfSections);
        printf("something3: %d\n", something3);
    }
        
    for (i = 0; i < numberOfColors; i++)
    {
        unsigned int stitchCount, colorNumber;
        stitchCount = fread_uint32_be(file);
        colorNumber = fgetc(file);
        embPattern_addThread(pattern, shvThreads[colorNumber % 43]);
        stitchesPerColor[i] = stitchCount;
        fseek(file, 9, SEEK_CUR);
    }

    fseek(file, -2, SEEK_CUR);
    
    for (i = 0; !feof(file); i++)
    {
        unsigned char b0, b1;
        int flags;
        if (inJump)
        {
            flags = JUMP;
        }
        else
        {
            flags = NORMAL;
        }
        b0 = fgetc(file);
        b1 = fgetc(file);
        if (stitchesSinceChange >= stitchesPerColor[currColorIndex]) 
        {
            embPattern_addStitchRel(pattern, 0, 0, STOP, 1);
            currColorIndex++;
            stitchesSinceChange = 0; 
        }
        if (b0 == 0x80)
        {
            stitchesSinceChange++;
            if (b1 == 3)
            {
                continue;
            }
            else if (b1 == 0x02)
            {
                inJump = 0;
                continue;
            }
            else if (b1 == 0x01)
            {
        stitchesSinceChange += 2;
                sx = fgetc(file);
                sx = (unsigned short)(sx << 8 | fgetc(file));
                sy = fgetc(file);
                sy = (unsigned short)(sy << 8 | fgetc(file));
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
    embPattern_flipVertical(pattern);

    return 1;
}

static char writeShv(void)
{
    puts("writeShv not implemented.");
    return 0; /*TODO: finish writeShv */
}

/* ---------------------------------------------------------------- */
/* format sst */

static char readSst(EmbPattern* pattern, FILE* file)
{
    int fileLength;

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0xA0, SEEK_SET); /* skip the all zero header */
    while(ftell(file) < fileLength)
    {
        int stitchType = NORMAL;

        int b1 = fgetc(file);
        int b2 = fgetc(file);
        unsigned char commandByte = (unsigned char)fgetc(file);

        if (commandByte == 0x04)
        {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }

        if ((commandByte & 0x01) == 0x01)
            stitchType = STOP;
        if ((commandByte & 0x02) == 0x02)
            stitchType = JUMP;
        if ((commandByte & 0x10) != 0x10)
            b2 = -b2;
        if ((commandByte & 0x40) == 0x40)
            b1 = -b1;
        embPattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }

    return 1; /*TODO: finish readSst */
}

static char writeSst(void)
{
    return 0; /*TODO: finish writeSst */
}

/* ---------------------------------------------------------------- */
/* format stx */

typedef struct SubDescriptor_
{
    int someNum;      /* TODO: better variable naming */
    int someInt;      /* TODO: better variable naming */
    int someOtherInt; /* TODO: better variable naming */
    char* colorCode;
    char* colorName;
} SubDescriptor;

typedef struct StxThread_
{
    char* colorCode;
    char* colorName;
    char* sectionName;
    SubDescriptor* subDescriptors;
    EmbColor stxColor;
} StxThread;

static int stxReadThread(StxThread* thread, FILE* file)
{
    int j, colorNameLength, sectionNameLength;
    int somethingSomething, somethingSomething2, somethingElse, numberOfOtherDescriptors; /* TODO: determine what these represent */
    int codeLength = 0;
    char* codeBuff = 0;
    char* codeNameBuff = 0;
    EmbColor col;
    char* sectionNameBuff = 0;
    unsigned char whatIsthis; /* TODO: determine what this represents */

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

    col.r = fgetc(file);
    col.b = fgetc(file);
    col.g = fgetc(file);

    whatIsthis = fgetc(file);
    if (EMB_DEBUG) {
        printf("col red: %d\n", col.r);
        printf("col green: %d\n", col.g);
        printf("col blue: %d\n", col.b);
        printf("what is this: %d\n", whatIsthis);
    }

    sectionNameLength = fgetc(file);
    sectionNameBuff = (char*)malloc(sectionNameLength);
    if (!sectionNameBuff) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for sectionNameBuff\n");
        return 0;
    }
    fread((unsigned char*)sectionNameBuff, 1, sectionNameLength, file); /* TODO: check return value */
    thread->sectionName = sectionNameBuff;

    somethingSomething = fread_int32(file);
    somethingSomething2 = fread_int32(file);
    somethingElse = fread_int32(file);
    numberOfOtherDescriptors = fread_int16(file);
    if (EMB_DEBUG) {
        printf("somethingSomething: %d", somethingSomething);
        printf("somethingSomething2: %d", somethingSomething2);
        printf("somethingElse: %d", somethingElse);
        printf("numberOfOtherDescriptors: %d", numberOfOtherDescriptors);
    }

    thread->subDescriptors = (SubDescriptor*)malloc(sizeof(SubDescriptor) * numberOfOtherDescriptors);
    if (!thread->subDescriptors) { printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for thread->subDescriptors\n"); return 0; }
    for (j = 0; j < numberOfOtherDescriptors; j++) {
        SubDescriptor sd;
        char* subCodeBuff, *subColorNameBuff;
        int subCodeLength, subColorNameLength;

        sd.someNum = fread_int16(file);
        /* Debug.Assert(sd.someNum == 1); TODO: review */
        sd.someInt = fread_int32(file);
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
        sd.someOtherInt = fread_int32(file);
        thread->subDescriptors[j] = sd;
    }
    return 1;
}

static char readStx(EmbPattern* pattern, FILE* file)
{
    int i, threadCount;
    unsigned char* gif = 0;
    /* public Bitmap Image; */
    StxThread* stxThreads = 0;
    unsigned char headerBytes[7];
    char* header = 0;
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
    (char)fgetc(file);
    /* bytes 15- */
    paletteLength = fread_int32(file);
    imageLength = fread_int32(file);
    something1 = fread_int32(file);
    stitchDataOffset = fread_int32(file);
    something3 = fread_int32(file);
    threadDescriptionOffset = fread_int32(file);
    stitchCount = fread_int32(file);
    colors = fread_int32(file);
    right = fread_int16(file);
    left = fread_int16(file);
    bottom = fread_int16(file);
    top = fread_int16(file);
    if (EMB_DEBUG) {
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

    fread_int32(file);
    fread_int32(file);
    fread_int32(file);
    fread_int16(file);
    fgetc(file);

    for (i = 0; i < 12; i++) {
        val[i] = fread_int16(file);
        if (EMB_DEBUG) {
            printf("identify val[%d] = %d", i, val[i]);
        }
    }
    if (EMB_DEBUG) {
        puts("val[4] == val[5] == 0");
        puts("val[10] == val[11] == 0");
    }
    fread_int32(file); /* 0 */
    fread_int32(file); /* 0 */
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

static char writeStx(void) {
    puts("ERROR: writeStx is not implemented.");
    return 0; /*TODO: finish writeStx */
}

/* ---------------------------------------------------------------- */
/* svg format */


/* ---------------------------------------------------------------- */
/* t01 format */

static char readT01(EmbPattern* pattern, FILE* file) {
    unsigned char b[3];

    while (fread(b, 1, 3, file) == 3) {
        int flags, x, y;
        decode_t01_record(b, &flags, &x, &y);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        if (flags == END) {
            break;
        }
    }
    return 1;
}

static char writeT01(EmbPattern* pattern, FILE* file) {
    EmbRect boundingRect;
    int xx, yy, i;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    boundingRect = embPattern_calcBoundingBox(pattern);
    if (EMB_DEBUG) {
        printf("bounding rectangle with top %f not used ", boundingRect.top);
        printf("in the function writeT01\n");
    }
    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        unsigned char b[3];
        int dx, dy;
        EmbStitch st = pattern->stitchList->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)round(st.x * 10.0) - xx;
        dy = (int)round(st.y * 10.0) - yy;
        xx = (int)round(st.x * 10.0);
        yy = (int)round(st.y * 10.0);
        encode_t01_record(b, dx, dy, st.flags);
        fwrite(b, 1, 3, file);
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/* t09 format */

static char readT09(EmbPattern* pattern, FILE* file) {
    unsigned char b[3];

    fseek(file, 0x0C, SEEK_SET);

    while (fread(b, 1, 3, file) == 3) {
        int stitchType = NORMAL;
        int b1 = b[0];
        int b2 = b[1];
        unsigned char commandByte = b[2];
        if (commandByte == 0x00) {
            break;
        }
        if (commandByte & 0x10) {
            stitchType = STOP;
        }
        if (commandByte & 0x20) {
            b1 = -b1;
        }
        if (commandByte & 0x40) {
            b2 = -b2;
        }
        embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1);
    }
    return 1;
}

static char writeT09(EmbPattern* pattern, FILE* file) {
    int i, xx, yy;
    fpad(file, 0x00, 0x0C);

    for (i = 0; i < pattern->stitchList->count; i++) {
        unsigned char b[3];
        int dx, dy;
        EmbStitch st = pattern->stitchList->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)round(st.x * 10.0) - xx;
        dy = (int)round(st.y * 10.0) - yy;
        xx = (int)round(st.x * 10.0);
        yy = (int)round(st.y * 10.0);

        b[0] = dx;
        b[1] = dy;
        b[2] = 0;
        if (st.flags & NORMAL) {
            /* guessing based on T01 here */
            b[2] |= 0x03;
        }
        /* inferred from readT09 */
        if (st.flags & STOP) {
            b[2] |= 0x10;
        }
        if (xx < 0) {
            b[0] = -dx;
            b[2] |= 0x20;
        }
        if (yy < 0) {
            b[0] = -dy;
            b[2] |= 0x40;
        }
        fwrite(b, 1, 3, file);
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/* tap format */
void encode_tap_record(FILE* file, int x, int y, int flags) {
    unsigned char b[3];
    encode_tajima_ternary(b, x, y);

    b[2] |= (char)3;
    if (flags & END) {
        b[0] = 0;
        b[1] = 0;
        b[2] = 0xF3;
    }
    if (flags & (JUMP | TRIM)) {
        b[2] = (char)(b[2] | 0x83);
    }
    if (flags & STOP) {
        b[2] = (char)(b[2] | 0xC3);
    }
    fwrite(b, 1, 3, file);
}

int decode_tap_record_flags(unsigned char b2) {
    if (b2 == 0xF3) {
        return END;
    }
    switch (b2 & 0xC3) {
        case 0x03:
            return NORMAL;
        case 0x83:
            return TRIM;
        case 0xC3:
            return STOP;
        default:
            return NORMAL;
    }
}

static char readTap(EmbPattern* pattern, FILE* file) {
    unsigned char b[3];

    while (fread(b, 1, 3, file) == 3) {
        int flags, x, y;
        decode_tajima_ternary(b, &x, &y);
        flags = decode_tap_record_flags(b[2]);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        if (flags == END) {
            break;
        }
    }
    return 1;
}

static char writeTap(EmbPattern* pattern, FILE* file) {
    int xx, yy, dx, dy, i;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st = pattern->stitchList->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)round(st.x * 10.0) - xx;
        dy = (int)round(st.y * 10.0) - yy;
        xx = (int)round(st.x * 10.0);
        yy = (int)round(st.y * 10.0);
        encode_tap_record(file, dx, dy, st.flags);
    }
    return 1;
}

/* ---------------------------------------------------------------- */
/* thr format */

#define NOTFRM 0x00080000

typedef struct ThredHeader_     /* thred file header */
{
    unsigned int sigVersion;    /* signature and version */
    unsigned int length;        /* length of ThredHeader + length of stitch data */
    unsigned short numStiches;  /* number of stitches */
    unsigned short hoopSize;    /* size of hoop */
    unsigned short reserved[7]; /* reserved for expansion */
} ThredHeader;

typedef struct ThredExtension_  /* thred v1.0 file header extension */
{
    float hoopX;                /* hoop size x dimension in 1/6 mm units */
    float hoopY;                /* hoop size y dimension in 1/6 mm units */
    float stitchGranularity;    /* stitches per millimeter--not implemented */
    char creatorName[50];       /* name of the file creator */
    char modifierName[50];      /* name of last file modifier */
    char auxFormat;             /* auxiliary file format, 0=PCS,1=DST,2=PES */
    char reserved[31];          /* reserved for expansion */
} ThredExtension;

/*
 * bit definitions for attributes of stitch
 * 0-3     stitch color
 * 4-14    form pointer
 * 15-18   spares
 * 19      not a form stitch
 * 20      center walk stitch
 * 21      edge walk stitch
 * 22      underlay stitch
 * 23      knot stitch
 * 24      feather stitch
 * 25-27   layer
 * 28      spare
 * 29-30   stitch type
 *             00=not a form stitch,
 *             01=form fill,
 *             10=form border fill,
 *             11=applique stitches
 * 31      set for user edited stitches
 */

static char readThr(EmbPattern* pattern, FILE* file) {
    ThredHeader header;
    EmbColor background;
    int currentColor;
    int i;

    header.sigVersion  = fread_uint32(file);
    header.length      = fread_uint32(file);
    header.numStiches  = fread_uint16(file);
    header.hoopSize    = fread_uint16(file);
    header.reserved[0] = fread_uint16(file);
    header.reserved[1] = fread_uint16(file);
    header.reserved[2] = fread_uint16(file);
    header.reserved[3] = fread_uint16(file);
    header.reserved[4] = fread_uint16(file);
    header.reserved[5] = fread_uint16(file);
    header.reserved[6] = fread_uint16(file);

    if ((header.sigVersion & 0xffffff) == 0x746872) {
        unsigned int verVar = (header.sigVersion & 0xff000000) >> 24;
        switch (verVar) {
            case 0:
                break;
            case 1:
            case 2:
                /* skip the file header extension */
                fseek(file, 144, SEEK_CUR); 
                break;
            default:
                return 0; /* unsupported version */
        }
    }
    currentColor = -1;
    for (i = 0; i < header.numStiches; i++) {
        int type = NORMAL;
        float x, y;
        unsigned int color;
        fread_int(file, &x, EMB_INT32_LITTLE);
        fread_int(file, &y, EMB_INT32_LITTLE);
        fread_int(file, &color, EMB_INT32_LITTLE);
        x /= 10.0;
        y /= 10.0;

        if ((int)(color & 0xF) != currentColor) {
            currentColor = (int)color & 0xF;
            embPattern_changeColor(pattern, currentColor);
            type = STOP | TRIM;
        }
        embPattern_addStitchAbs(pattern, x, y, type, 0);
    }
    fseek(file, 16, SEEK_CUR); /* skip bitmap name (16 chars) */

    embColor_read(file, &background, 4);
    if (EMB_DEBUG) {
        printf("background: %c %c %c\n", background.r, background.g, background.b);
    }
    for (i = 0; i < 16; i++) {
        EmbThread thread;
        strcpy(thread.description, "NULL");
        strcpy(thread.catalogNumber, "NULL");
        embColor_read(file, &(thread.color), 4);
        embPattern_addThread(pattern, thread);
    }
    /*  64 bytes of rgbx(4 bytes) colors (16 custom colors) */
    /*  16 bytes of thread size (ascii representation ie. '4') */
    return 1;
}

static char writeThr(EmbPattern* pattern, FILE* file) {
    int i, stitchCount;
    unsigned char version = 0;
    ThredHeader header;
    ThredExtension extension;
    char bitmapName[16];

    stitchCount = pattern->stitchList->count;

    memset(&header, 0, sizeof(ThredHeader));
    header.sigVersion = 0x746872 | (version << 24);
    header.length = stitchCount * 12 + 16;
    if (version == 1 || version == 2) {
        header.length = header.length + sizeof(ThredHeader);
    }
    header.numStiches = (unsigned short)stitchCount; /* number of stitches in design */
    header.hoopSize = 5;

    binaryWriteUInt(file, header.sigVersion);
    binaryWriteUInt(file, header.length);
    binaryWriteUShort(file, header.numStiches);
    binaryWriteUShort(file, header.hoopSize);
    binaryWriteUShort(file, header.reserved[0]);
    binaryWriteUShort(file, header.reserved[1]);
    binaryWriteUShort(file, header.reserved[2]);
    binaryWriteUShort(file, header.reserved[3]);
    binaryWriteUShort(file, header.reserved[4]);
    binaryWriteUShort(file, header.reserved[5]);
    binaryWriteUShort(file, header.reserved[6]);

    if (version == 1 || version == 2) {
        memset(&extension, 0, sizeof(ThredExtension));
        extension.auxFormat = 1;
        extension.hoopX = 640;
        extension.hoopY = 640;

        fwrite_int(file, &(extension.hoopX), EMB_INT32_LITTLE);
        fwrite_int(file, &(extension.hoopY), EMB_INT32_LITTLE);
        fwrite_int(file, &(extension.stitchGranularity), EMB_INT32_LITTLE);
        fwrite(extension.creatorName, 1, 50, file);
        fwrite(extension.modifierName, 1, 50, file);
        fputc(extension.auxFormat, file);
        fwrite(extension.reserved, 1, 31, file);
    }

    /* write stitches */
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st = pattern->stitchList->stitch[i];
        float x, y;
        x = (float)(st.x * 10.0);
        y = (float)(st.y * 10.0);
        fwrite_int(file, &x, EMB_INT32_LITTLE);
        fwrite_int(file, &y, EMB_INT32_LITTLE);
        binaryWriteUInt(file, NOTFRM | (st.color & 0x0F));
    }
    fwrite(bitmapName, 1, 16, file);
    /* background color */
    fwrite("\xFF\xFF\xFF\x00", 1, 4, file);

    for (i = 0; i < pattern->threads->count; i++) {
        EmbColor c = pattern->threads->thread[i].color;
        embColor_write(file, c, 4);
        if (i >= 16) break;
    }

    /* write remaining colors if not yet 16 */
    fpad(file, 0, 4*(16-i));

    fpad(file, '4', 16);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format txt */

static char readTxt(EmbPattern* pattern, FILE* file) {
    char line[100];
    int stated_count, i;
    emb_readline(file, line, 99);
    stated_count = atoi(line);
    for (i=0; i<stated_count; i++) {
        EmbStitch st;
        char *p, *x, *y, *color, *flags;
        int state = 0;
        emb_readline(file, line, 99);
        for (p=line; *p; p++) {
            if (*p == ',' || *p == ' ') {
                *p = 0;
                switch (state) {
                case 0:
                    y = p+1;
                    break;
                case 1:
                    color = p+7;
                    break;
                case 2:
                    flags = p+7;
                    break;
                default:
                    break;
                }
                state++;
            }
        }
        st.x = atof(line);
        st.y = atof(y);
        st.color = atoi(color);
        st.flags = atoi(flags);
        embPattern_addStitchAbs(pattern, st.x, st.y, st.flags, st.color);
    }
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0; /*TODO: finish readTxt */
}

static char writeTxt(EmbPattern* pattern, FILE* file) {
    int i;
    fprintf(file, "%u\n", (unsigned int) pattern->stitchList->count);

    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch s = pattern->stitchList->stitch[i];
        fprintf(file, "%.1f,%.1f color:%i flags:%i\n", 
                s.x, s.y, s.color, s.flags);
    }
    return 1;
}


/* ---------------------------------------------------------------- */
/* format u00 */

static char readU00(EmbPattern* pattern, FILE* file) {
    int i;
    char dx = 0, dy = 0;
    int flags = NORMAL;
    unsigned char b[3];

    if (!check_header_present(file, 0x100)) {
        return 0;
    }

    /* 16 3byte RGB's start @ 0x08 followed by 14 bytes between 
        0 and 15 with index of color for each color change */
    fseek(file, 0x08, SEEK_SET);
    for (i = 0; i < 16; i++) {
        EmbThread t;
        embColor_read(file, &(t.color), 3);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        embPattern_addThread(pattern, t);
    }

    fseek(file, 0x100, SEEK_SET);
    while (fread(b, 1, 3, file) == 3) {
        char negativeX , negativeY;

        if (b[0] == 0xF8 || b[0] == 0x87 || b[0] == 0x91) {
            break;
        }
        if ((b[0] & 0x0F) == 0) {
            flags = NORMAL;
        } else if ((b[0] & 0x1f) == 1) {
            flags = JUMP;
        } else if ((b[0] & 0x0F) > 0) {
            flags = STOP;
        }
        negativeX = ((b[0] & 0x20) > 0);
        negativeY = ((b[0] & 0x40) > 0);

        dx = (char) b[2];
        dy = (char) b[1];
        if (negativeX) {
            dx = (char) -dx;
        }
        if (negativeY) {
            dy = (char) -dy;
        }
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

static char writeU00(void) {
    puts("writeU00 not implemented.");
    return 0; /*TODO: finish WriteU00 */
}

/* ---------------------------------------------------------------- */
/* format u01 */

/* TODO: AFAIK this is a duplicate of U00. Review for differences and merge files and handle accordingly. */

static char readU01(EmbPattern* pattern, FILE* file) {
    int fileLength, negativeX = 0, negativeY = 0, flags = NORMAL;
    char dx, dy;
    unsigned char data[3];

    if (!check_header_present(file, 0x100)) {
        return 0;
    }

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x100, SEEK_SET);
    
    if (EMB_DEBUG) {
        printf("file length: %d\n", fileLength);
    }

    while (fread(data, 1, 3, file) == 3) {
        if (data[0] == 0xF8 || data[0] == 0x87 || data[0] == 0x91) {
            break;
        }
        if ((data[0] & 0x0F) == 0) {
            flags = NORMAL;
        } else if ((data[0] & 0x1f) == 1) {
            flags = JUMP;
        } else if ((data[0] & 0x0F) > 0) {
            flags = STOP;
        }
        negativeX = ((data[0] & 0x20) > 0);
        negativeY = ((data[0] & 0x40) > 0);

        dx = (char) data[2];
        dy = (char) data[1];
        if (negativeX) {
            dx = (char) -dx;
        }
        if (negativeY) {
            dy = (char) -dy;
        }
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    return 1;
}

static char writeU01(void) {
    return 0; /*TODO: finish writeU01 */
}

/* ---------------------------------------------------------------- */
/* format vip */

static const unsigned char vipDecodingTable[] = {
        0x2E, 0x82, 0xE4, 0x6F, 0x38, 0xA9, 0xDC, 0xC6, 0x7B, 0xB6, 0x28, 0xAC, 0xFD, 0xAA, 0x8A, 0x4E,
        0x76, 0x2E, 0xF0, 0xE4, 0x25, 0x1B, 0x8A, 0x68, 0x4E, 0x92, 0xB9, 0xB4, 0x95, 0xF0, 0x3E, 0xEF,
        0xF7, 0x40, 0x24, 0x18, 0x39, 0x31, 0xBB, 0xE1, 0x53, 0xA8, 0x1F, 0xB1, 0x3A, 0x07, 0xFB, 0xCB,
        0xE6, 0x00, 0x81, 0x50, 0x0E, 0x40, 0xE1, 0x2C, 0x73, 0x50, 0x0D, 0x91, 0xD6, 0x0A, 0x5D, 0xD6,
        0x8B, 0xB8, 0x62, 0xAE, 0x47, 0x00, 0x53, 0x5A, 0xB7, 0x80, 0xAA, 0x28, 0xF7, 0x5D, 0x70, 0x5E,
        0x2C, 0x0B, 0x98, 0xE3, 0xA0, 0x98, 0x60, 0x47, 0x89, 0x9B, 0x82, 0xFB, 0x40, 0xC9, 0xB4, 0x00,
        0x0E, 0x68, 0x6A, 0x1E, 0x09, 0x85, 0xC0, 0x53, 0x81, 0xD1, 0x98, 0x89, 0xAF, 0xE8, 0x85, 0x4F,
        0xE3, 0x69, 0x89, 0x03, 0xA1, 0x2E, 0x8F, 0xCF, 0xED, 0x91, 0x9F, 0x58, 0x1E, 0xD6, 0x84, 0x3C,
        0x09, 0x27, 0xBD, 0xF4, 0xC3, 0x90, 0xC0, 0x51, 0x1B, 0x2B, 0x63, 0xBC, 0xB9, 0x3D, 0x40, 0x4D,
        0x62, 0x6F, 0xE0, 0x8C, 0xF5, 0x5D, 0x08, 0xFD, 0x3D, 0x50, 0x36, 0xD7, 0xC9, 0xC9, 0x43, 0xE4,
        0x2D, 0xCB, 0x95, 0xB6, 0xF4, 0x0D, 0xEA, 0xC2, 0xFD, 0x66, 0x3F, 0x5E, 0xBD, 0x69, 0x06, 0x2A,
        0x03, 0x19, 0x47, 0x2B, 0xDF, 0x38, 0xEA, 0x4F, 0x80, 0x49, 0x95, 0xB2, 0xD6, 0xF9, 0x9A, 0x75,
        0xF4, 0xD8, 0x9B, 0x1D, 0xB0, 0xA4, 0x69, 0xDB, 0xA9, 0x21, 0x79, 0x6F, 0xD8, 0xDE, 0x33, 0xFE,
        0x9F, 0x04, 0xE5, 0x9A, 0x6B, 0x9B, 0x73, 0x83, 0x62, 0x7C, 0xB9, 0x66, 0x76, 0xF2, 0x5B, 0xC9,
        0x5E, 0xFC, 0x74, 0xAA, 0x6C, 0xF1, 0xCD, 0x93, 0xCE, 0xE9, 0x80, 0x53, 0x03, 0x3B, 0x97, 0x4B,
        0x39, 0x76, 0xC2, 0xC1, 0x56, 0xCB, 0x70, 0xFD, 0x3B, 0x3E, 0x52, 0x57, 0x81, 0x5D, 0x56, 0x8D,
        0x51, 0x90, 0xD4, 0x76, 0xD7, 0xD5, 0x16, 0x02, 0x6D, 0xF2, 0x4D, 0xE1, 0x0E, 0x96, 0x4F, 0xA1,
        0x3A, 0xA0, 0x60, 0x59, 0x64, 0x04, 0x1A, 0xE4, 0x67, 0xB6, 0xED, 0x3F, 0x74, 0x20, 0x55, 0x1F,
        0xFB, 0x23, 0x92, 0x91, 0x53, 0xC8, 0x65, 0xAB, 0x9D, 0x51, 0xD6, 0x73, 0xDE, 0x01, 0xB1, 0x80,
        0xB7, 0xC0, 0xD6, 0x80, 0x1C, 0x2E, 0x3C, 0x83, 0x63, 0xEE, 0xBC, 0x33, 0x25, 0xE2, 0x0E, 0x7A,
        0x67, 0xDE, 0x3F, 0x71, 0x14, 0x49, 0x9C, 0x92, 0x93, 0x0D, 0x26, 0x9A, 0x0E, 0xDA, 0xED, 0x6F,
        0xA4, 0x89, 0x0C, 0x1B, 0xF0, 0xA1, 0xDF, 0xE1, 0x9E, 0x3C, 0x04, 0x78, 0xE4, 0xAB, 0x6D, 0xFF,
        0x9C, 0xAF, 0xCA, 0xC7, 0x88, 0x17, 0x9C, 0xE5, 0xB7, 0x33, 0x6D, 0xDC, 0xED, 0x8F, 0x6C, 0x18,
        0x1D, 0x71, 0x06, 0xB1, 0xC5, 0xE2, 0xCF, 0x13, 0x77, 0x81, 0xC5, 0xB7, 0x0A, 0x14, 0x0A, 0x6B,
        0x40, 0x26, 0xA0, 0x88, 0xD1, 0x62, 0x6A, 0xB3, 0x50, 0x12, 0xB9, 0x9B, 0xB5, 0x83, 0x9B, 0x37
    };

static int vipDecodeByte(unsigned char b) {
    if (b >= 0x80) return (-(unsigned char) (~b + 1));
    return b;
}

static int vipDecodeStitchType(unsigned char b) {
    switch (b) {
        case 0x80:
            return NORMAL;
        case 0x81:
            return TRIM;
        case 0x84:
            return STOP;
        case 0x90:
            return END;
        default:
            return NORMAL;
    }
}

static unsigned char* vipDecompressData(unsigned char* input, int compressedInputLength, int decompressedContentLength) {
    unsigned char* decompressedData = (unsigned char*)malloc(decompressedContentLength);
    if (!decompressedData) {
        printf("ERROR: format-vip.c vipDecompressData(), cannot allocate memory for decompressedData\n");
        return 0;
    }
    hus_decompress((char*)input, compressedInputLength, (char *)decompressedData, &decompressedContentLength);
    return decompressedData;
}

typedef struct VipHeader_ {
    int magicCode;
    int numberOfStitches;
    int numberOfColors;
    short postitiveXHoopSize;
    short postitiveYHoopSize;
    short negativeXHoopSize;
    short negativeYHoopSize;
    int attributeOffset;
    int xOffset;
    int yOffset;
    unsigned char stringVal[8];
    short unknown;
    int colorLength;
} VipHeader;

static char readVip(EmbPattern* pattern, FILE* file)
{
    int fileLength;
    int i;
    unsigned char prevByte = 0;
    unsigned char *attributeData = 0, *decodedColors = 0;
    unsigned char *attributeDataDecompressed = 0;
    unsigned char *xData = 0, *xDecompressed = 0, *yData = 0, *yDecompressed = 0;
    VipHeader header;

    fileLength = check_header_present(file, 32);
    if (!fileLength) {
        printf("ERROR: file shorter than header.");
        return 0;
    }

    fread_int(file, &(header.magicCode), EMB_INT32_LITTLE);
    fread_int(file, &(header.numberOfStitches), EMB_INT32_LITTLE);
    fread_int(file, &(header.numberOfColors), EMB_INT32_LITTLE);

    fread_int(file, &(header.postitiveXHoopSize), EMB_INT16_LITTLE);
    fread_int(file, &(header.postitiveYHoopSize), EMB_INT16_LITTLE);
    fread_int(file, &(header.negativeXHoopSize), EMB_INT16_LITTLE);
    fread_int(file, &(header.negativeYHoopSize), EMB_INT16_LITTLE);
    fread_int(file, &(header.attributeOffset), EMB_INT32_LITTLE);
    fread_int(file, &(header.xOffset), EMB_INT32_LITTLE);
    fread_int(file, &(header.yOffset), EMB_INT32_LITTLE);

    fread(header.stringVal, 1, 8, file); /* TODO: check return value */

    fread_int(file, &(header.unknown), EMB_INT16_LITTLE);

    fread_int(file, &(header.colorLength), EMB_INT32_LITTLE);
    decodedColors = (unsigned char*)malloc(header.numberOfColors*4);
    if (!decodedColors) {
        printf("ERROR: format-vip.c readVip(), ");
        printf("cannot allocate memory for decodedColors\n");
        return 0;
    }
    for (i = 0; i < header.numberOfColors*4; ++i) {
        unsigned char inputByte = (char)fgetc(file);
        unsigned char tmpByte = (unsigned char) (inputByte ^ vipDecodingTable[i]);
        decodedColors[i] = (unsigned char) (tmpByte ^ prevByte);
        prevByte = inputByte;
    }
    for (i = 0; i < header.numberOfColors; i++) {
        EmbThread thread;
        int startIndex = i << 2;
        thread.color.r = decodedColors[startIndex];
        thread.color.g = decodedColors[startIndex + 1];
        thread.color.b = decodedColors[startIndex + 2];
        /* printf("%d\n", decodedColors[startIndex + 3]); */
        embPattern_addThread(pattern, thread);
    }
    fseek(file, header.attributeOffset, SEEK_SET);
    attributeData = (unsigned char*)malloc(header.xOffset - header.attributeOffset);
    if (!attributeData) {
        printf("ERROR: format-vip.c readVip(), cannot allocate memory for attributeData\n");
        return 0;
    }
    fread(attributeData, 1, header.xOffset - header.attributeOffset, file); /* TODO: check return value */
    attributeDataDecompressed = vipDecompressData(attributeData, header.xOffset - header.attributeOffset, header.numberOfStitches);

    fseek(file, header.xOffset, SEEK_SET);
    xData = (unsigned char*)malloc(header.yOffset - header.xOffset);
    if (!xData) { 
        printf("ERROR: format-vip.c readVip(), cannot allocate memory for xData\n");
        return 0;
    }
    fread(xData, 1, header.yOffset - header.xOffset, file); /* TODO: check return value */
    xDecompressed = vipDecompressData(xData, header.yOffset - header.xOffset, header.numberOfStitches);

    fseek(file, header.yOffset, SEEK_SET);
    yData = (unsigned char*)malloc(fileLength - header.yOffset);
    if (!yData) { printf("ERROR: format-vip.c readVip(), cannot allocate memory for yData\n"); return 0; }
    fread(yData, 1, fileLength - header.yOffset, file); /* TODO: check return value */
    yDecompressed = vipDecompressData(yData, fileLength - header.yOffset, header.numberOfStitches);

    for (i = 0; i < header.numberOfStitches; i++) {
        embPattern_addStitchRel(pattern,
                    vipDecodeByte(xDecompressed[i]) / 10.0,
                    vipDecodeByte(yDecompressed[i]) / 10.0,
                    vipDecodeStitchType(attributeDataDecompressed[i]), 1);
    }
    embPattern_addStitchRel(pattern, 0, 0, END, 1);

    free(attributeData);
    free(xData);
    free(yData);
    free(attributeDataDecompressed);
    free(xDecompressed);
    free(yDecompressed);
    return 1;
}

static unsigned char* vipCompressData(unsigned char* input, int decompressedInputSize, int* compressedSize) {
    unsigned char* compressedData = (unsigned char*)malloc(decompressedInputSize*2);
    if (!compressedData) {
        printf("ERROR: format-vip.c vipCompressData(), cannot allocate memory for compressedData\n");
        return 0;
    }
    hus_compress((char*)input, decompressedInputSize, (char *)compressedData, compressedSize);
    return compressedData;
}

static unsigned char vipEncodeByte(double f) {
    return (unsigned char)(int)round(f);
}

static unsigned char vipEncodeStitchType(int st) {
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

static char writeVip(EmbPattern* pattern, FILE* file) {
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor;
    int attributeSize = 0;
    int xCompressedSize = 0;
    int yCompressedSize = 0;
    double previousX = 0;
    double previousY = 0;
    unsigned char* xValues = 0, *yValues = 0, *attributeValues = 0;
    double xx = 0.0;
    double yy = 0.0;
    int flags = 0;
    int i = 0;
    unsigned char* attributeCompressed = 0, *xCompressed = 0;
    unsigned char* yCompressed = 0, *decodedColors = 0, *encodedColors = 0;
    unsigned char prevByte = 0;

    puts("VIP not yet implemented.");
    return 0;

    stitchCount = pattern->stitchList->count;
    minColors = pattern->threads->count;
    decodedColors = (unsigned char*)malloc(minColors << 2);
    if (!decodedColors) {
        return 0;
    }
    encodedColors = (unsigned char*)malloc(minColors << 2);
    if (!encodedColors) {
        free(decodedColors);
        return 0;
    }
    /* embPattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */

    patternColor = minColors;
    if (EMB_DEBUG) {
        printf("patternColor: %d\n", patternColor);
    }
    if (minColors > 24) {
        minColors = 24;
    }
    binaryWriteUInt(file, 0x0190FC5D);
    binaryWriteUInt(file, stitchCount);
    binaryWriteUInt(file, minColors);

    boundingRect = embPattern_calcBoundingBox(pattern);
    binaryWriteShort(file, (short) round(boundingRect.right * 10.0));
    binaryWriteShort(file, (short) -round(boundingRect.top * 10.0 - 1.0));
    binaryWriteShort(file, (short) round(boundingRect.left * 10.0));
    binaryWriteShort(file, (short) -round(boundingRect.bottom * 10.0 - 1.0));

    binaryWriteUInt(file, 0x38 + (minColors << 3));

    xValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    yValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    attributeValues = (unsigned char*)malloc(sizeof(unsigned char)*(stitchCount));
    if (xValues && yValues && attributeValues) {
        for (i = 0; i < pattern->stitchList->count; i++) {
            EmbStitch st;
            st = pattern->stitchList->stitch[i];
            xx = st.x;
            yy = st.y;
            flags = st.flags;
            xValues[i] = vipEncodeByte((xx - previousX) * 10.0);
            previousX = xx;
            yValues[i] = vipEncodeByte((yy - previousY) * 10.0);
            previousY = yy;
            attributeValues[i] = vipEncodeStitchType(flags);
        }
        attributeCompressed = vipCompressData(attributeValues, stitchCount, &attributeSize);
        xCompressed = vipCompressData(xValues, stitchCount, &xCompressedSize);
        yCompressed = vipCompressData(yValues, stitchCount, &yCompressedSize);

        binaryWriteUInt(file, (unsigned int) (0x38 + (minColors << 3) + attributeSize));
        binaryWriteUInt(file, (unsigned int) (0x38 + (minColors << 3) + attributeSize + xCompressedSize));
        binaryWriteUInt(file, 0x00000000);
        binaryWriteUInt(file, 0x00000000);
        binaryWriteUShort(file, 0x0000);

        binaryWriteInt(file, minColors << 2);

        for (i = 0; i < minColors; i++) {
            int byteChunk = i << 2;
            EmbColor currentColor = pattern->threads->thread[i].color;
            decodedColors[byteChunk] = currentColor.r;
            decodedColors[byteChunk + 1] = currentColor.g;
            decodedColors[byteChunk + 2] = currentColor.b;
            decodedColors[byteChunk + 3] = 0x01;
        }

        for (i = 0; i < minColors << 2; ++i) {
            unsigned char tmpByte = (unsigned char) (decodedColors[i] ^ vipDecodingTable[i]);
            prevByte = (unsigned char) (tmpByte ^ prevByte);
            fputc(prevByte, file);
        }
        for (i = 0; i <= minColors; i++) {
            binaryWriteInt(file, 1);
        }
        binaryWriteUInt(file, 0); /* string length */
        binaryWriteShort(file, 0);
        fwrite((char*) attributeCompressed, 1, attributeSize, file);
        fwrite((char*) xCompressed, 1, xCompressedSize, file);
        fwrite((char*) yCompressed, 1, yCompressedSize, file);
    }

    if (attributeCompressed) {
        free(attributeCompressed);
    }
    if (xCompressed) {
        free(xCompressed);
    }
    if (yCompressed) {
        free(yCompressed);
    }
    if (attributeValues) {
        free(attributeValues);
    }
    if (xValues) {
        free(xValues);
    }
    if (yValues) {
        free(yValues);
    }
    free(decodedColors);
    free(encodedColors);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format vp3 */



static unsigned char* vp3ReadString(FILE* file)
{
    short stringLength;
    unsigned char* charString = 0;
    if (!file) { printf("ERROR: format-vp3.c vp3ReadString(), file argument is null\n"); return 0; }
    fread_int(file, &stringLength, EMB_INT16_BIG);
    charString = (unsigned char*)malloc(stringLength);
    if (!charString) { printf("ERROR: format-vp3.c vp3ReadString(), cannot allocate memory for charString\n"); return 0; }
    fread(charString, 1, stringLength, file); /* TODO: check return value */
    return charString;
}

static int vp3Decode(unsigned char inputByte)
{
    if (inputByte > 0x80)
    {
        return (int)-((unsigned char)((~inputByte) + 1));
    }
    return ((int)inputByte);
}

static short vp3DecodeInt16(unsigned short inputByte)
{
    if (inputByte > 0x8000)
    {
        return -((short) ((~inputByte) + 1));
    }
    return ((short)inputByte);
}

typedef struct _vp3Hoop
{
    int right;
    int bottom;
    int left;
    int top;
    int threadLength;
    char unknown2;
    unsigned char numberOfColors;
    unsigned short unknown3;
    int unknown4;
    int numberOfBytesRemaining;

    int xOffset;
    int yOffset;

    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;

    /* Centered hoop dimensions */
    int right2;
    int left2;
    int bottom2;
    int top2;

    int width;
    int height;
} vp3Hoop;

static vp3Hoop vp3ReadHoopSection(FILE* file)
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

    hoop.right = fread_int32_be(file);
    hoop.bottom = fread_int32_be(file);
    hoop.left = fread_int32_be(file);
    hoop.top = fread_int32_be(file);

    hoop.threadLength = fread_int32(file); /* yes, it seems this is _not_ big endian */
    hoop.unknown2 = (char)fgetc(file);
    hoop.numberOfColors = (char)fgetc(file);
    fread_int(file, &(hoop.unknown3), EMB_INT16_BIG);
    fread_int(file, &(hoop.unknown4), EMB_INT32_BIG);
    fread_int(file, &(hoop.numberOfBytesRemaining), EMB_INT32_BIG);

    fread_int(file, &(hoop.xOffset), EMB_INT32_BIG);
    fread_int(file, &(hoop.yOffset), EMB_INT32_BIG);

    hoop.byte1 = (char)fgetc(file);
    hoop.byte2 = (char)fgetc(file);
    hoop.byte3 = (char)fgetc(file);

    /* Centered hoop dimensions */
    hoop.right2 = fread_int32_be(file);
    hoop.left2 = fread_int32_be(file);
    hoop.bottom2 = fread_int32_be(file);
    hoop.top2 = fread_int32_be(file);

    hoop.width = fread_int32_be(file);
    hoop.height = fread_int32_be(file);
    return hoop;
}

static char readVp3(EmbPattern* pattern, FILE* file) {
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
    fread_int(file, &someShort, EMB_INT16_LITTLE);
    someByte = (char)fgetc(file);
    fread_int(file, &bytesRemainingInFile, EMB_INT32_LITTLE);
    fileCommentString = vp3ReadString(file);
    hoopConfigurationOffset = (int)ftell(file);

    vp3ReadHoopSection(file);

    anotherCommentString = vp3ReadString(file);

    /* TODO: review v1 thru v18 variables and use emb_unused() if needed */
    for (i = 0; i < 18; i++) {
        unsigned char v1;
        v1 = (char)fgetc(file);
        if (EMB_DEBUG) {
            printf("v%d = %d\n", i, v1);
        }
    }

    fread(magicCode, 1, 6, file); /* 0x78 0x78 0x55 0x55 0x01 0x00 */ /* TODO: check return value */

    anotherSoftwareVendorString = vp3ReadString(file);

    fread_int(file, &numberOfColors, EMB_INT16_BIG);
    colorSectionOffset = (int)ftell(file);
    if (EMB_DEBUG) {
        puts("LIBEMBROIDERY DEBUG");
        puts("Format vp3");
        printf("    some: %d\n", some);
        printf("    softwareVendorString: %s\n", softwareVendorString);
        printf("    someShort: %d\n", someShort);
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
        fread_int(file, &colorSectionOffset, EMB_INT32_BIG);
        colorSectionOffset += ftell(file);
        fread_int(file, &startX, EMB_INT32_BIG);
        fread_int(file, &startY, EMB_INT32_BIG);
        embPattern_addStitchAbs(pattern, startX / 1000.0, -startY / 1000.0, JUMP, 1);

        tableSize = (char)fgetc(file);
        (char)fgetc(file);
        embColor_read(file, &(t.color), 3);
        embPattern_addThread(pattern, t);
        fseek(file, 6*tableSize - 1, SEEK_CUR);

        threadColorNumber = vp3ReadString(file);
        colorName = vp3ReadString(file);
        threadVendor = vp3ReadString(file);

        offsetToNextColorX = fread_int32_be(file);
        offsetToNextColorY = fread_int32_be(file);

        unknownThreadString = fread_int16_be(file);
        fseek(file, unknownThreadString, SEEK_CUR);
        numberOfBytesInColor = fread_int32_be(file);
        fseek(file, 0x3, SEEK_CUR);
        
        if (EMB_DEBUG) {
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
            if (x == 0x80) {
                switch (y) {
                    case 0x00:
                    case 0x03:
                        break;
                    case 0x01:
                        x = vp3DecodeInt16(fread_uint16_be(file));
                        y = vp3DecodeInt16(fread_uint16_be(file));
                        fread_int16_be(file);
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

void vp3WriteStringLen(FILE* file, const char* str, int len) {
    binaryWriteUShortBE(file, len);
    fwrite(str, 1, len, file);
}

void vp3WriteString(FILE* file, const char* str) {
    vp3WriteStringLen(file, str, strlen(str));
}

void vp3PatchByteCount(FILE* file, int offset, int adjustment) {
    int currentPos = ftell(file);
    fseek(file, offset, SEEK_SET);
    printf("Patching byte count: %d\n", currentPos - offset + adjustment);
    binaryWriteIntBE(file, currentPos - offset + adjustment);
    fseek(file, currentPos, SEEK_SET);
}

static char writeVp3(EmbPattern* pattern, FILE* file) {
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
#if 0
    short a;
    int a_int;
    EmbRect bounds;
    int remainingBytesPos, remainingBytesPos2;
    int colorSectionStitchBytes;
    int first = 1;
    int numberOfColors = 0;
    EmbColor color = embColor_make(0xFE, 0xFE, 0xFE);
    EmbStitchList *mainPointer = 0, *pointer = 0;

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
    fputc(0);

    numberOfColors = 0;

    mainPointer = pattern->stitchList;
    while(mainPointer)
    {
        int flag;
        EmbColor newColor;

        pointer = mainPointer;
        flag = pointer->stitch.flags;
        newColor = pattern->threads->thread[pointer->stitch.color].color;
        if (embColor_distance(newColor, color) != 0) {
            numberOfColors++;
            color = newColor;
        }
        else if (flag & END || flag & STOP) {
            numberOfColors++;
        }

        while(pointer && (flag == pointer->stitch.flags)) {
            pointer = pointer->next;
        }
        mainPointer = pointer;
    }

    fputc(numberOfColors);
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
    fwrite_int(file, &a, EMB_INT16_BIG);
    a_int = 4096;
    fwrite_int(file, &a_int, EMB_INT32_BIG);
    a_int = 0;
    fwrite_int(file, &a_int, EMB_INT32_BIG);
    fwrite_int(file, &a_int, EMB_INT32_BIG);
    a_int = 4096;
    fwrite_int(file, &a_int, EMB_INT32_BIG);

    fwrite("xxPP\x01\0", 1, 6, file);
    vp3WriteString(file, "");
    fwrite_int(file, &numberOfColors, EMB_INT16_BIG);

    mainPointer = pattern->stitchList;
    while(mainPointer)
    {
        char colorName[8] = { 0 };
        double lastX, lastY;
        int colorSectionLengthPos;
        EmbStitch s;
        int lastColor;

        if (!first)
        {
            fputc(0, file);
        }
        fputc(0, file);
        fputc(5, file);
        fputc(0, file);

        colorSectionLengthPos = ftell(file);
        binaryWriteInt(file, 0); /* placeholder */

        pointer = mainPointer;
        color = pattern->threads->thread[pointer->stitch.color].color;

        if (first && pointer->stitch.flags & JUMP && pointer->next->stitch.flags & JUMP)
        {
            pointer = pointer->next;
        }

        s = pointer->stitch;
        printf("format-vp3.c DEBUG %d, %lf, %lf\n", s.flags, s.x, s.y);
        binaryWriteIntBE(file, s.x * 1000);
        binaryWriteIntBE(file, -s.y * 1000);
        pointer = pointer->next;

        first = 0;

        lastX = s.x;
        lastY = s.y;
        lastColor = s.color;

        fputc(1);
        fputc(0);

        printf("format-vp3.c writeVp3(), switching to color (%d, %d, %d)\n", color.r, color.g, color.b);
        embColor_write(file, color, 4);

        fputc(0);
        fputc(0);
        fputc(5);
        fputc(40);

        vp3WriteString(file, "");

        sprintf(colorName, "#%02x%02x%02x", color.b, color.g, color.r);

        vp3WriteString(file, colorName);
        vp3WriteString(file, "");

        binaryWriteIntBE(file, 0);
        binaryWriteIntBE(file, 0);

        vp3WriteStringLen(file, "\0", 1);

        colorSectionStitchBytes = ftell(file);
        binaryWriteInt(file, 0); /* placeholder */

        fputc(10);
        fputc(246);
        fputc(0);

        while(pointer)
        {
            short dx, dy;

            EmbStitch s = pointer->stitch;
            if (s.color != lastColor)
            {
                break;
            }
            if (s.flags & END || s.flags & STOP)
            {
                break;
            }
            dx = (s.x - lastX) * 10;
            dy = (s.y - lastY) * 10;
            lastX = lastX + dx / 10.0; /* output is in ints, ensure rounding errors do not sum up */
            lastY = lastY + dy / 10.0;

            if (dx < -127 || dx > 127 || dy < -127 || dy > 127)
            {
                fputc(128);
                fputc(1);
                fwrite_int(file, &dx, EMB_INT16_BIG);
                fwrite_int(file, &dy, EMB_INT16_BIG);
                fputc(128);
                fputc(2);
            }
            else
            {
                char b[2];
                b[0] = dx;
                b[1] = dy;
                fwrite(b, 1, 2, file);
            }

            pointer = pointer->next;
        }

        vp3PatchByteCount(file, colorSectionStitchBytes, -4);
        vp3PatchByteCount(file, colorSectionLengthPos, -3);

        mainPointer = pointer;
    }

    vp3PatchByteCount(file, remainingBytesPos2, -4);
    vp3PatchByteCount(file, remainingBytesPos, -4);

    embPattern_flipVertical(pattern);
#endif
    puts("ERROR: vp3 format is not supported.");
    return 0;
}

/* ---------------------------------------------------------------- */
/* format xxx */

static char xxxDecodeByte(unsigned char inputByte) {
    if (inputByte >= 0x80) {
        return (char) ((-~inputByte) - 1);
    }
    return ((char) inputByte);
}

static char readXxx(EmbPattern* pattern, FILE* file) {
    int dx = 0, dy = 0, numberOfColors, paletteOffset, i;
    char thisStitchJump = 0;

    if (EMB_DEBUG) {
        puts("readXxx has been overridden.");
        return 0;
    }

    fseek(file, 0x27, SEEK_SET);
    fread_int(file, &numberOfColors, EMB_INT16_LITTLE);
    fseek(file, 0xFC, SEEK_SET);
    fread_int(file, &paletteOffset, EMB_INT32_LITTLE);
    fseek(file, paletteOffset + 6, SEEK_SET);

    for (i = 0; i < numberOfColors; i++) {
        EmbThread thread;
        strcpy(thread.catalogNumber, "NULL");
        strcpy(thread.description, "NULL");
        (char)fgetc(file);
        embColor_read(file, &(thread.color), 3);
        embPattern_addThread(pattern, thread);
    }
    fseek(file, 0x100, SEEK_SET);

    for (i = 0; !feof(file) && ftell(file) < paletteOffset; i++) {
        unsigned char b0, b1;
        int flags;
        flags = NORMAL;
        if (thisStitchJump) flags = TRIM;
        thisStitchJump = 0;
        b0 = (char)fgetc(file);
        b1 = (char)fgetc(file);
        /* TODO: ARE THERE OTHER BIG JUMP CODES? */
        if (b0 == 0x7E || b0 == 0x7D) {
            dx = b1 + ((char)fgetc(file) << 8);
            dx = ((short) dx);
            dy = fread_int16(file);
            flags = TRIM;
        } else if (b0 == 0x7F) {
            /* TODO: LOOKS LIKE THESE CODES ARE IN THE HEADER */
            if (b1 != 0x17 && b1 != 0x46 && b1 >= 8) { 
                b0 = 0;
                b1 = 0;
                thisStitchJump = 1;
                flags = STOP;
            } else if (b1 == 1) {
                flags = TRIM;
                b0 = (char)fgetc(file);
                b1 = (char)fgetc(file);
            } else {
                continue;
            }
            dx = xxxDecodeByte(b0);
            dy = xxxDecodeByte(b1);
        } else {
            dx = xxxDecodeByte(b0);
            dy = xxxDecodeByte(b1);
        }
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    /* TODO: check end of pattern for multiple STOPs */
    return 1;
}

static void xxxEncodeStop(FILE* file, EmbStitch s) {
    fputc((unsigned char)0x7F, file);
    fputc((unsigned char)(s.color + 8), file);
}

static void xxxEncodeStitch(FILE* file, 
        double deltaX, double deltaY, int flags) {
    if ((flags & (JUMP | TRIM)) && (fabs(deltaX) > 124 || fabs(deltaY) > 124)) {
        fputc(0x7E, file);
        /* Does this cast work right? */
        binaryWriteShort(file, (short)deltaX);
        binaryWriteShort(file, (short)deltaY);
    } else {
        /* TODO: Verify this works after changing this to unsigned char */
        fputc((unsigned char)round(deltaX), file);
        fputc((unsigned char)round(deltaY), file);
    }
}

static void xxxEncodeDesign(FILE* file, EmbPattern* p) {
    int i;
    double thisX = 0.0f;
    double thisY = 0.0f;

    if (p->stitchList->count > 0) {
        thisX = (float)p->stitchList->stitch[0].x;
        thisY = (float)p->stitchList->stitch[0].y;
    }
    for (i = 0; i < p->stitchList->count; i++) {
        EmbStitch s = p->stitchList->stitch[i];
        double deltaX, deltaY;
        double previousX = thisX;
        double previousY = thisY;
        thisX = s.x;
        thisY = s.y;
        deltaX = thisX - previousX;
        deltaY = thisY - previousY;
        if (s.flags & STOP) {
            xxxEncodeStop(file, s);
        } else if (s.flags & END) {
        } else {
            xxxEncodeStitch(file, deltaX * 10.0f, deltaY * 10.0f, s.flags);
        }
    }
}

static char writeXxx(EmbPattern* pattern, FILE* file) {
    int i;
    EmbRect rect;
    int endOfStitches;

    embPattern_correctForMaxStitchLength(pattern, 124, 127);

    fpad(file, 0, 0x17);
    binaryWriteUInt(file, (unsigned int)pattern->stitchList->count);
    fpad(file, 0, 0x0C);
    binaryWriteUShort(file, (unsigned short)pattern->threads->count);
    binaryWriteShort(file, 0x0000);

    rect = embPattern_calcBoundingBox(pattern);
    binaryWriteShort(file, (short)(embRect_width(rect) * 10.0));
    binaryWriteShort(file, (short)(embRect_height(rect) * 10.0));

    /*TODO: xEnd from start point x=0 */
    binaryWriteShort(file, (short)(embRect_width(rect) / 2.0 * 10));
    /*TODO: yEnd from start point y=0 */
    binaryWriteShort(file, (short)(embRect_height(rect) / 2.0 * 10));
    /*TODO: left from start x = 0     */
    binaryWriteShort(file, (short)(embRect_width(rect)/2.0 * 10));
    /*TODO: bottom from start y = 0   */
    binaryWriteShort(file, (short)(embRect_height(rect)/2.0 * 10));
    fpad(file, 0, 0xC5);
    binaryWriteInt(file, 0x0000); /* place holder for end of stitches */
    xxxEncodeDesign(file, pattern);
    endOfStitches = ftell(file);
    fseek(file, 0xFC, SEEK_SET);
    binaryWriteUInt(file, endOfStitches);
    fseek(file, 0, SEEK_END);
    /* is this really correct? */
    fwrite("\x7F\x7F\x03\x14\x00\x00", 1, 6, file);

    for (i = 0; i < pattern->threads->count; i++) {
        fputc(0x00, file);
        fputc(pattern->threads->thread[i].color.r, file);
        fputc(pattern->threads->thread[i].color.g, file);
        fputc(pattern->threads->thread[i].color.b, file);
    }
    for (i = 0; i < (22 - pattern->threads->count); i++) {
        binaryWriteUInt(file, 0x01000000);
    }
    fwrite("\x00\x01", 1, 2, file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format zsk */

static char readZsk(EmbPattern* pattern, FILE* file) {
    char b[3];
    int stitchType;
    unsigned char colorNumber;
    
    fseek(file, 0, SEEK_END);
    if (ftell(file) < 0x230) {
        return 0;
    }
    
    fseek(file, 0x230, SEEK_SET);
    colorNumber = fgetc(file);
    while (colorNumber != 0) {
        EmbThread t;
        embColor_read(file, &(t.color), 3);
        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        embPattern_addThread(pattern, t);
        fseek(file, 0x48, SEEK_CUR);
        colorNumber = fgetc(file);
    }
    fseek(file, 0x2E, SEEK_CUR);

    while (fread(b, 1, 3, file) == 3) {
        stitchType = NORMAL;
        if (b[0] & 0x4) {
            b[2] = -b[2];
        }
        if (b[0] & 0x8) {
            b[1] = -b[1];
        }
        if (b[0] & 0x02) {
            stitchType = JUMP;
        }
        if (b[0] & 0x20) {
            if (b[1] == 2) {
                stitchType = TRIM;
            } else if (b[1] == -1) {
                break;
            } else {
                if (b[2] != 0) {
                    colorNumber = b[2];
                }
                /* TODO: need to determine what b[1] is used for.*/
                stitchType = STOP; 
                embPattern_changeColor(pattern, colorNumber - 1);
            }
            b[1] = 0;
            b[2] = 0;
        }
        embPattern_addStitchRel(pattern, b[1] / 10.0,
            b[2] / 10.0, stitchType, 0);
    }

    return 1;
}

static char writeZsk(EmbPattern* pattern, FILE* file) {
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0; /*TODO: finish writeZsk */
}

/* ---------------------------------------------------------------- */

