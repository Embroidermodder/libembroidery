/*
 * This file is part of libembroidery.
 *
 * Copyright 2021 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * This file contains all the read and write functions for the
 * library.
 */

#include "embroidery.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>

char read100(EmbPattern *pattern, const char* fileName);
char write100(EmbPattern *pattern, const char* fileName);
char read10o(EmbPattern *pattern, const char* fileName);
char write10o(EmbPattern *pattern, const char* fileName);
char readArt(EmbPattern *pattern, const char* fileName);
char writeArt(EmbPattern *pattern, const char* fileName);
char readBmc(EmbPattern *pattern, const char* fileName);
char writeBmc(EmbPattern *pattern, const char* fileName);
char readBro(EmbPattern *pattern, const char* fileName);
char writeBro(EmbPattern *pattern, const char* fileName);
char readCnd(EmbPattern *pattern, const char* fileName);
char writeCnd(EmbPattern *pattern, const char* fileName);
char readCol(EmbPattern *pattern, const char* fileName);
char writeCol(EmbPattern *pattern, const char* fileName);
char readCsd(EmbPattern *pattern, const char* fileName);
char writeCsd(EmbPattern *pattern, const char* fileName);
char readCsv(EmbPattern *pattern, const char* fileName);
char writeCsv(EmbPattern *pattern, const char* fileName);
char readDat(EmbPattern *pattern, const char* fileName);
char writeDat(EmbPattern *pattern, const char* fileName);
char readDem(EmbPattern *pattern, const char* fileName);
char writeDem(EmbPattern *pattern, const char* fileName);
char readDsb(EmbPattern *pattern, const char* fileName);
char writeDsb(EmbPattern *pattern, const char* fileName);
char readDst(EmbPattern *pattern, const char* fileName);
char writeDst(EmbPattern *pattern, const char* fileName);
char readDsz(EmbPattern *pattern, const char* fileName);
char writeDsz(EmbPattern *pattern, const char* fileName);
char readDxf(EmbPattern *pattern, const char* fileName);
char writeDxf(EmbPattern *pattern, const char* fileName);
char readEdr(EmbPattern *pattern, const char* fileName);
char writeEdr(EmbPattern *pattern, const char* fileName);
char readEmd(EmbPattern *pattern, const char* fileName);
char writeEmd(EmbPattern *pattern, const char* fileName);
char readExp(EmbPattern *pattern, const char* fileName);
char writeExp(EmbPattern *pattern, const char* fileName);
char readExy(EmbPattern *pattern, const char* fileName);
char writeExy(EmbPattern *pattern, const char* fileName);
char readEys(EmbPattern *pattern, const char* fileName);
char writeEys(EmbPattern *pattern, const char* fileName);
char readFxy(EmbPattern *pattern, const char* fileName);
char writeFxy(EmbPattern *pattern, const char* fileName);
char readGc(EmbPattern *pattern, const char* fileName);
char writeGc(EmbPattern *pattern, const char* fileName);
char readGnc(EmbPattern *pattern, const char* fileName);
char writeGnc(EmbPattern *pattern, const char* fileName);
char readGt(EmbPattern *pattern, const char* fileName);
char writeGt(EmbPattern *pattern, const char* fileName);
char readHus(EmbPattern *pattern, const char* fileName);
char writeHus(EmbPattern *pattern, const char* fileName);
char readInb(EmbPattern *pattern, const char* fileName);
char writeInb(EmbPattern *pattern, const char* fileName);
char readInf(EmbPattern *pattern, const char* fileName);
char writeInf(EmbPattern *pattern, const char* fileName);
char readJef(EmbPattern *pattern, const char* fileName);
char writeJef(EmbPattern *pattern, const char* fileName);
char readKsm(EmbPattern *pattern, const char* fileName);
char writeKsm(EmbPattern *pattern, const char* fileName);
char readMax(EmbPattern *pattern, const char* fileName);
char writeMax(EmbPattern *pattern, const char* fileName);
char readMit(EmbPattern *pattern, const char* fileName);
char writeMit(EmbPattern *pattern, const char* fileName);
char readNew(EmbPattern *pattern, const char* fileName);
char writeNew(EmbPattern *pattern, const char* fileName);
char readOfm(EmbPattern *pattern, const char* fileName);
char writeOfm(EmbPattern *pattern, const char* fileName);
char readPcd(EmbPattern *pattern, const char* fileName);
char writePcd(EmbPattern *pattern, const char* fileName);
char readPcm(EmbPattern *pattern, const char* fileName);
char writePcm(EmbPattern *pattern, const char* fileName);
char readPcq(EmbPattern *pattern, const char* fileName);
char writePcq(EmbPattern *pattern, const char* fileName);
char readPcs(EmbPattern *pattern, const char* fileName);
char writePcs(EmbPattern *pattern, const char* fileName);
char readPec(EmbPattern *pattern, const char* fileName);
char writePec(EmbPattern *pattern, const char* fileName);
char readPel(EmbPattern *pattern, const char* fileName);
char writePel(EmbPattern *pattern, const char* fileName);
char readPem(EmbPattern *pattern, const char* fileName);
char writePem(EmbPattern *pattern, const char* fileName);
char readPes(EmbPattern *pattern, const char* fileName);
char writePes(EmbPattern *pattern, const char* fileName);
char readPhb(EmbPattern *pattern, const char* fileName);
char writePhb(EmbPattern *pattern, const char* fileName);
char readPhc(EmbPattern *pattern, const char* fileName);
char writePhc(EmbPattern *pattern, const char* fileName);
char readPlt(EmbPattern *pattern, const char* fileName);
char writePlt(EmbPattern *pattern, const char* fileName);
char readRgb(EmbPattern *pattern, const char* fileName);
char writeRgb(EmbPattern *pattern, const char* fileName);
char readSew(EmbPattern *pattern, const char* fileName);
char writeSew(EmbPattern *pattern, const char* fileName);
char readShv(EmbPattern *pattern, const char* fileName);
char writeShv(EmbPattern *pattern, const char* fileName);
char readSst(EmbPattern *pattern, const char* fileName);
char writeSst(EmbPattern *pattern, const char* fileName);
char readStx(EmbPattern *pattern, const char* fileName);
char writeStx(EmbPattern *pattern, const char* fileName);
char readSvg(EmbPattern *pattern, const char* fileName);
char writeSvg(EmbPattern *pattern, const char* fileName);
char readT01(EmbPattern *pattern, const char* fileName);
char writeT01(EmbPattern *pattern, const char* fileName);
char readT09(EmbPattern *pattern, const char* fileName);
char writeT09(EmbPattern *pattern, const char* fileName);
char readTap(EmbPattern *pattern, const char* fileName);
char writeTap(EmbPattern *pattern, const char* fileName);
char readThr(EmbPattern *pattern, const char* fileName);
char writeThr(EmbPattern *pattern, const char* fileName);
char readTxt(EmbPattern *pattern, const char* fileName);
char writeTxt(EmbPattern *pattern, const char* fileName);
char readU00(EmbPattern *pattern, const char* fileName);
char writeU00(EmbPattern *pattern, const char* fileName);
char readU01(EmbPattern *pattern, const char* fileName);
char writeU01(EmbPattern *pattern, const char* fileName);
char readVip(EmbPattern *pattern, const char* fileName);
char writeVip(EmbPattern *pattern, const char* fileName);
char readVp3(EmbPattern *pattern, const char* fileName);
char writeVp3(EmbPattern *pattern, const char* fileName);
char readXxx(EmbPattern *pattern, const char* fileName);
char writeXxx(EmbPattern *pattern, const char* fileName);
char readZsk(EmbPattern *pattern, const char* fileName);
char writeZsk(EmbPattern *pattern, const char* fileName);

char embPattern_read(EmbPattern* pattern, const char* fileName, int format) {
    switch (format) {
    case EMB_FORMAT_100:
        return read100(pattern, fileName);
    case EMB_FORMAT_10O:
        return read10o(pattern, fileName);
    case EMB_FORMAT_ART:
        return readArt(pattern, fileName);
    case EMB_FORMAT_BMC:
        return readBmc(pattern, fileName);
    case EMB_FORMAT_BRO:
        return readBro(pattern, fileName);
    case EMB_FORMAT_CND:
        return readCnd(pattern, fileName);
    case EMB_FORMAT_COL:
        return readCol(pattern, fileName);
    case EMB_FORMAT_CSD:
        return readCsd(pattern, fileName);
    case EMB_FORMAT_CSV:
        return readCsv(pattern, fileName);
    case EMB_FORMAT_DAT:
        return readDat(pattern, fileName);
    case EMB_FORMAT_DEM:
        return readDem(pattern, fileName);
    case EMB_FORMAT_DSB:
        return readDsb(pattern, fileName);
    case EMB_FORMAT_DST:
        return readDst(pattern, fileName);
    case EMB_FORMAT_DSZ:
        return readDsz(pattern, fileName);
    case EMB_FORMAT_DXF:
        return readDxf(pattern, fileName);
    case EMB_FORMAT_EDR:
        return readEdr(pattern, fileName);
    case EMB_FORMAT_EMD:
        return readEmd(pattern, fileName);
    case EMB_FORMAT_EXP:
        return readExp(pattern, fileName);
    case EMB_FORMAT_EXY:
        return readExy(pattern, fileName);
    case EMB_FORMAT_EYS:
        return readEys(pattern, fileName);
    case EMB_FORMAT_FXY:
        return readFxy(pattern, fileName);
    case EMB_FORMAT_GC:
        return readGc(pattern, fileName);
    case EMB_FORMAT_GNC:
        return readGnc(pattern, fileName);
    case EMB_FORMAT_GT:
        return readGt(pattern, fileName);
    case EMB_FORMAT_HUS:
        return readHus(pattern, fileName);
    case EMB_FORMAT_INB:
        return readInb(pattern, fileName);
    case EMB_FORMAT_INF:
        return readInf(pattern, fileName);
    case EMB_FORMAT_JEF:
        return readJef(pattern, fileName);
    case EMB_FORMAT_KSM:
        return readKsm(pattern, fileName);
    case EMB_FORMAT_MAX:
        return readMax(pattern, fileName);
    case EMB_FORMAT_MIT:
        return readMit(pattern, fileName);
    case EMB_FORMAT_NEW:
        return readNew(pattern, fileName);
    case EMB_FORMAT_OFM:
        return readOfm(pattern, fileName);
    case EMB_FORMAT_PCD:
        return readPcd(pattern, fileName);
    case EMB_FORMAT_PCM:
        return readPcm(pattern, fileName);
    case EMB_FORMAT_PCQ:
        return readPcq(pattern, fileName);
    case EMB_FORMAT_PCS:
        return readPcs(pattern, fileName);
    case EMB_FORMAT_PEC:
        return readPec(pattern, fileName);
    case EMB_FORMAT_PEL:
        return readPel(pattern, fileName);
    case EMB_FORMAT_PEM:
        return readPem(pattern, fileName);
    case EMB_FORMAT_PES:
        return readPes(pattern, fileName);
    case EMB_FORMAT_PHB:
        return readPhb(pattern, fileName);
    case EMB_FORMAT_PHC:
        return readPhc(pattern, fileName);
    case EMB_FORMAT_PLT:
        return readPlt(pattern, fileName);
    case EMB_FORMAT_RGB:
        return readRgb(pattern, fileName);
    case EMB_FORMAT_SEW:
        return readSew(pattern, fileName);
    case EMB_FORMAT_SHV:
        return readShv(pattern, fileName);
    case EMB_FORMAT_SST:
        return readSst(pattern, fileName);
    case EMB_FORMAT_STX:
        return readStx(pattern, fileName);
    case EMB_FORMAT_SVG:
        return readSvg(pattern, fileName);
    case EMB_FORMAT_T01:
        return readT01(pattern, fileName);
    case EMB_FORMAT_T09:
        return readT09(pattern, fileName);
    case EMB_FORMAT_TAP:
        return readTap(pattern, fileName);
    case EMB_FORMAT_THR:
        return readThr(pattern, fileName);
    case EMB_FORMAT_TXT:
        return readTxt(pattern, fileName);
    case EMB_FORMAT_U00:
        return readU00(pattern, fileName);
    case EMB_FORMAT_U01:
        return readU01(pattern, fileName);
    case EMB_FORMAT_VIP:
        return readVip(pattern, fileName);
    case EMB_FORMAT_VP3:
        return readVp3(pattern, fileName);
    case EMB_FORMAT_XXX:
        return readXxx(pattern, fileName);
    case EMB_FORMAT_ZSK:
        return readZsk(pattern, fileName);
    default:
        break;
    }
    return 0;
}

char embPattern_write(EmbPattern* pattern, const char* fileName, int format) {
    switch (format) {
    case EMB_FORMAT_100:
        return write100(pattern, fileName);
    case EMB_FORMAT_10O:
        return write10o(pattern, fileName);
    case EMB_FORMAT_ART:
        return writeArt(pattern, fileName);
    case EMB_FORMAT_BMC:
        return writeBmc(pattern, fileName);
    case EMB_FORMAT_BRO:
        return writeBro(pattern, fileName);
    case EMB_FORMAT_CND:
        return writeCnd(pattern, fileName);
    case EMB_FORMAT_COL:
        return writeCol(pattern, fileName);
    case EMB_FORMAT_CSD:
        return writeCsd(pattern, fileName);
    case EMB_FORMAT_CSV:
        return writeCsv(pattern, fileName);
    case EMB_FORMAT_DAT:
        return writeDat(pattern, fileName);
    case EMB_FORMAT_DEM:
        return writeDem(pattern, fileName);
    case EMB_FORMAT_DSB:
        return writeDsb(pattern, fileName);
    case EMB_FORMAT_DST:
        return writeDst(pattern, fileName);
    case EMB_FORMAT_DSZ:
        return writeDsz(pattern, fileName);
    case EMB_FORMAT_DXF:
        return writeDxf(pattern, fileName);
    case EMB_FORMAT_EDR:
        return writeEdr(pattern, fileName);
    case EMB_FORMAT_EMD:
        return writeEmd(pattern, fileName);
    case EMB_FORMAT_EXP:
        return writeExp(pattern, fileName);
    case EMB_FORMAT_EXY:
        return writeExy(pattern, fileName);
    case EMB_FORMAT_EYS:
        return writeEys(pattern, fileName);
    case EMB_FORMAT_FXY:
        return writeFxy(pattern, fileName);
    case EMB_FORMAT_GC:
        return writeGc(pattern, fileName);
    case EMB_FORMAT_GNC:
        return writeGnc(pattern, fileName);
    case EMB_FORMAT_GT:
        return writeGt(pattern, fileName);
    case EMB_FORMAT_HUS:
        return writeHus(pattern, fileName);
    case EMB_FORMAT_INB:
        return writeInb(pattern, fileName);
    case EMB_FORMAT_INF:
        return writeInf(pattern, fileName);
    case EMB_FORMAT_JEF:
        return writeJef(pattern, fileName);
    case EMB_FORMAT_KSM:
        return writeKsm(pattern, fileName);
    case EMB_FORMAT_MAX:
        return writeMax(pattern, fileName);
    case EMB_FORMAT_MIT:
        return writeMit(pattern, fileName);
    case EMB_FORMAT_NEW:
        return writeNew(pattern, fileName);
    case EMB_FORMAT_OFM:
        return writeOfm(pattern, fileName);
    case EMB_FORMAT_PCD:
        return writePcd(pattern, fileName);
    case EMB_FORMAT_PCM:
        return writePcm(pattern, fileName);
    case EMB_FORMAT_PCQ:
        return writePcq(pattern, fileName);
    case EMB_FORMAT_PCS:
        return writePcs(pattern, fileName);
    case EMB_FORMAT_PEC:
        return writePec(pattern, fileName);
    case EMB_FORMAT_PEL:
        return writePel(pattern, fileName);
    case EMB_FORMAT_PEM:
        return writePem(pattern, fileName);
    case EMB_FORMAT_PES:
        return writePes(pattern, fileName);
    case EMB_FORMAT_PHB:
        return writePhb(pattern, fileName);
    case EMB_FORMAT_PHC:
        return writePhc(pattern, fileName);
    case EMB_FORMAT_PLT:
        return writePlt(pattern, fileName);
    case EMB_FORMAT_RGB:
        return writeRgb(pattern, fileName);
    case EMB_FORMAT_SEW:
        return writeSew(pattern, fileName);
    case EMB_FORMAT_SHV:
        return writeShv(pattern, fileName);
    case EMB_FORMAT_SST:
        return writeSst(pattern, fileName);
    case EMB_FORMAT_STX:
        return writeStx(pattern, fileName);
    case EMB_FORMAT_SVG:
        return writeSvg(pattern, fileName);
    case EMB_FORMAT_T01:
        return writeT01(pattern, fileName);
    case EMB_FORMAT_T09:
        return writeT09(pattern, fileName);
    case EMB_FORMAT_TAP:
        return writeTap(pattern, fileName);
    case EMB_FORMAT_THR:
        return writeThr(pattern, fileName);
    case EMB_FORMAT_TXT:
        return writeTxt(pattern, fileName);
    case EMB_FORMAT_U00:
        return writeU00(pattern, fileName);
    case EMB_FORMAT_U01:
        return writeU01(pattern, fileName);
    case EMB_FORMAT_VIP:
        return writeVip(pattern, fileName);
    case EMB_FORMAT_VP3:
        return writeVp3(pattern, fileName);
    case EMB_FORMAT_XXX:
        return writeXxx(pattern, fileName);
    case EMB_FORMAT_ZSK:
        return writeZsk(pattern, fileName);
    default:
        break;
    }
    return 0;
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

char read100(EmbPattern* pattern, const char* fileName) {
    FILE* file;
    unsigned char b[4];

    if (!validateReadPattern(pattern, fileName, "read100")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 0;
    }
    embPattern_loadExternalColorFile(pattern, fileName);
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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char write100(EmbPattern* pattern, const char* fileName) {
    FILE *file;
    /*
    int x, y;
    int stitchType;
    unsigned char b[4];
    */

    if (!validateWritePattern(pattern, fileName, "write100")) {
        printf("Failed to validate file with name: %s.", fileName);
        return 0;
    }

    file = fopen(fileName, "wb");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 0;
    }

    /*
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
    fclose(file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* 10o format */

char read10o(EmbPattern* pattern, const char* fileName) {
    FILE* file;
    if (!validateReadPattern(pattern, fileName, "read10o")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 0;
    }
    embPattern_loadExternalColorFile(pattern, fileName);
    while (1) {
        int x, y;
        int stitchType = NORMAL;
        unsigned char ctrl = (unsigned char)fgetc(file);
        if (feof(file)) {
            break;
        }
        y = fgetc(file);
        if (feof(file)) {
            break;
        }
        x = fgetc(file);
        if (feof(file)) {
            break;
        }
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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char write10o(EmbPattern* pattern, const char* fileName) {
    FILE *file;
    if (!validateWritePattern(pattern, fileName, "write10o")) {
        printf("Failed to validate file with name: %s.", fileName);
        return 0;
    }
    file = fopen(fileName, "wb");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 0;
    }

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
    fclose(file);
    puts("Write10o is not supported currently.");
    return 0; /*TODO: finish write10o */
}

/* ---------------------------------------------------------------- */
/* art format */

char readArt(EmbPattern* pattern, const char* fileName)
{
    if (!validateReadPattern(pattern, fileName, "readArt")) return 0;

    embPattern_end(pattern);

    puts("readArt is not implimented");
    return 0; /*TODO: finish readArt */
}

char writeArt(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeArt")) return 0;

    /* TODO: fopen() needs to occur here after the check for no stitches */

    puts("writeArt is not implimented");
    return 0; /*TODO: finish writeArt */
}

/* ---------------------------------------------------------------- */
/* bmc format */

char readBmc(EmbPattern* pattern, const char* fileName) {
    if (!validateReadPattern(pattern, fileName, "readBmc")) {
        return 0;
    }
    embPattern_end(pattern);
    puts("readBmc is not implimented");
    return 0; /*TODO: finish readBmc */
}

char writeBmc(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeBmc")) {
        return 0;
    }
    /* TODO: fopen() needs to occur here 
        after the check for no stitches */
    puts("writeBmc is not implimented");
    return 0; /*TODO: finish writeBmc */
}

/* ---------------------------------------------------------------- */
/* bro format */

char readBro(EmbPattern* pattern, const char* fileName) {
    unsigned char x55;
    short unknown1, unknown2, unknown3, unknown4, moreBytesToEnd;
    char name[8];
    int stitchType;
    FILE* file;

    if (!validateReadPattern(pattern, fileName, "readBro")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 0;
    }
    embPattern_loadExternalColorFile(pattern, fileName);
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

    while (1) {
        short b1, b2;
        stitchType = NORMAL;
        b1 = (unsigned char)fgetc(file);
        b2 = (unsigned char)fgetc(file);
        if (b1 == -128) {
            unsigned char bCode = (unsigned char)fgetc(file);
            fread(&b1, 2, 1, file);
            fread(&b2, 2, 1, file);
            if (bCode == 2) {
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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeBro(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeBro")) {
        return 0;
    }
    /* TODO: fopen() needs to occur here 
        after the check for no stitches */

    puts("writeBro is not implimented");
    return 0; /*TODO: finish writeBro */
}

/* ---------------------------------------------------------------- */
/* cnd format */

char readCnd(EmbPattern* pattern, const char* fileName) {
    if (!validateReadPattern(pattern, fileName, "readCnd")) {
        return 0;
    }
    puts("readCnd is not implimented");
    return 0; /*TODO: finish readCnd */
}

char writeCnd(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeCnd")) {
        return 0;
    }
    /* TODO: fopen() needs to occur here 
        after the check for no stitches */

    puts("writeCnd is not implimented");
    return 0; /*TODO: finish writeCnd */
}

/* ---------------------------------------------------------------- */
/* col format */

char readCol(EmbPattern* pattern, const char* fileName) {
    int numberOfColors, i;
    FILE* file;
    int num, blue, green, red;
    EmbThread t;
    char line[30];

    if (!validateReadPattern(pattern, fileName, "readCol")) {
        return 0;
    }
    file = fopen(fileName, "r");
    if (!file) {
        return 0;
    }
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
    fclose(file);
    return 1;
}

char writeCol(EmbPattern* pattern, const char* fileName)
{
    FILE* file = 0;
    int i;
    EmbColor c;

    if (!validateWritePattern(pattern, fileName, "writeCol")) return 0;

    file = fopen(fileName, "w");
    if (!file) {
        printf("ERROR: format-col.c writeCol(), ");
        printf("cannot open %s for writing\n", fileName);
        return 0;
    }
    fprintf(file, "%d\r\n", pattern->threads->count);
    for (i = 0; i < pattern->threads->count; i++) {
        c = pattern->threads->thread[i].color;
        fprintf(file, "%d,%d,%d,%d\r\n", i, (int)c.r, (int)c.g, (int)c.b);
    }
    fclose(file);
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

char readCsd(EmbPattern* pattern, const char* fileName) {
    int i, type = 0;
    unsigned char identifier[8];
    unsigned char unknown1, unknown2;
    char dx = 0, dy = 0;
    int colorChange = -1;
    int flags;
    char endOfStream = 0;
    FILE* file;
    unsigned char colorOrder[14];

    if (!validateReadPattern(pattern, fileName, "readCsd")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        puts("Error: failed to open file.");
        return 0;
    }
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
    for (i = 0; !endOfStream; i++) {
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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeCsd(EmbPattern* pattern, const char* fileName) {
    FILE *file;

    if (!validateWritePattern(pattern, fileName, "writeCsd")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        puts("ERROR: Failed to open file.");
        return 0;
    }


    fclose(file);

    puts("writeCsd is not implimented.");
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
        return -1;
    }
    return -1;
}

char readCsv(EmbPattern* pattern, const char* fileName) {
    FILE* file = 0;
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
    char* buff = 0;

    if (!validateReadPattern(pattern, fileName, "readCsv")) return 0;

    buff = (char*)malloc(size);
    if (!buff) {
        printf("ERROR: format-csv.c readCsv(), ");
        printf("unable to allocate memory for buff\n");
        return 0;
    }

    file = fopen(fileName, "r");
    if (!file) {
        printf("ERROR: failed to open file with name %s.", fileName);
        free(buff);
        return 0;
    }

    pos = 0;
    do {
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
        if (pos >= size - 1) {
            size *= 2;
            buff = (char*)realloc(buff, size);
            if (!buff) {
                printf("ERROR: format-csv.c readCsv(), ");
                printf("cannot re-allocate memory for buff\n");
                return 0;
            }
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
        while(c != EOF);
        fclose(file);
    free(buff);
    embPattern_end(pattern);
    return 1;
}

char writeCsv(EmbPattern* pattern, const char* fileName) {
    FILE* file;
    EmbRect boundingRect;
    int i;

    if (!validateWritePattern(pattern, fileName, "writeCsv")) {
        printf("ERROR: Failed to validate pattern.");
        return 0;
    }

    boundingRect = embPattern_calcBoundingBox(pattern);

    file = fopen(fileName, "w");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 0;
    }

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
    fclose(file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* dat format */

char readDat(EmbPattern* pattern, const char* fileName)
{
    unsigned char b0;
    int fileLength, stitchesRemaining, b1, b2, stitchType;
    FILE* file;

    if (!validateReadPattern(pattern, fileName, "readDat")) return 0;

    file = fopen(fileName, "rb");
    if (!file) {
        puts("ERROR: cannot open file.");
        return 0;
    }

    embPattern_loadExternalColorFile(pattern, fileName);
    fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x02, SEEK_SET);
    stitchesRemaining = fread_uint16(file);
    fseek(file, 0x100, SEEK_SET);

    while(ftell(file) < fileLength)
    {
        b1 = (int)fgetc(file);
        b2 = (int)fgetc(file);
        b0 = fgetc(file);

        stitchType = NORMAL;
        stitchesRemaining--;

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
    fclose(file);

    embPattern_end(pattern);

    return 1;
}

char writeDat(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeDat")) return 0;

    /* TODO: fopen() needs to occur here after the check for no stitches */

    puts("writeDat is not implimented.");
    return 0; /*TODO: finish writeDat */
}

/* ---------------------------------------------------------------- */
/* format dem */

char readDem(EmbPattern* pattern, const char* fileName)
{
    if (!validateReadPattern(pattern, fileName, "readDem"))
        return 0;

    embPattern_end(pattern);

    puts("readDem is not implimented.");
    return 0; /*TODO: finish readDem */
}

char writeDem(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeDem"))
        return 0;

    /* TODO: fopen() needs to occur here after the check for no
    stitches */

    puts("writeDem is not implimented.");
    return 0; /*TODO: finish writeDem */
}

/* ---------------------------------------------------------------- */
/* format dsb */

char readDsb(EmbPattern* pattern, const char* fileName) {
    FILE* file = 0;
    char header[512+1];
    unsigned char buffer[3];

    if (!validateReadPattern(pattern, fileName, "readDsb")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        puts("ERROR: failed to open file.");
        return 0;
    }
    embPattern_loadExternalColorFile(pattern, fileName);
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
    fclose(file);
    return 1;
}

char writeDsb(EmbPattern* pattern, const char* fileName) {
    FILE* file;
    if (!validateWritePattern(pattern, fileName, "writeDsb")) {
        return 0;
    }
    file = fopen(fileName, "wb");
    if (!file) {
        puts("ERROR: failed to open file.");
        return 0;
    }
    fclose(file);
    puts("writeDsb is not implimented");
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
    int returnCode = 0;
    if (b2 == 0xF3)
    {
        return END;
    }
    if (b2 & 0x80)
    {
        returnCode |= JUMP;
    }
    if (b2 & 0x40)
    {
        returnCode |= STOP;
    }
    return returnCode;
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
char readDst(EmbPattern* pattern, const char* fileName) {
    char var[3];   /* temporary storage variable name */
    char val[512]; /* temporary storage variable value */
    int valpos;
    unsigned char b[3];
    char header[512 + 1];
    FILE* file = 0;
    int i = 0, flags;

    /* TODO: review commented code below
    pattern->clear();
    pattern->set_variable("file_name",filename);
    */

    if (!validateReadPattern(pattern, fileName, "readDst")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    embPattern_loadExternalColorFile(pattern, fileName);
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

    fclose(file);
    embPattern_end(pattern);
    /* combineJumpStitches(pattern, 5); */
    return 1;
}

char writeDst(EmbPattern* pattern, const char* fileName) {
    EmbRect boundingRect;
    FILE* file;
    int xx, yy, i, ax, ay, mx, my;
    char pd[10];
    EmbStitch st;

    if (!validateWritePattern(pattern, fileName, "writeDst")) {
        return 0;
    }
    file = fopen(fileName, "wb");
    if (!file) {
        return 0;
    }
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
        printf("%d %f %f %d %d %d %d\n", i, st.x, st.y, dx, dy, xx, yy);
        encode_record(file, dx, dy, st.flags);
    }

    /* Finish file with a terminator character and two zeros to
     * keep the post header part a multiple of three.
     */
    fwrite("\xa1\0\0", 1, 3, file);
    fclose(file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format dsz */

char readDsz(EmbPattern* pattern, const char* fileName) {
    FILE* file;
    unsigned char b[3];
    if (!validateReadPattern(pattern, fileName, "readDsz")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    embPattern_loadExternalColorFile(pattern, fileName);

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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeDsz(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeDsz")) {
        return 0;
    }
    /* TODO: fopen() needs to occur here 
        after the check for no stitches */

    puts("writeDsz is not implimented.");
    return 0; /*TODO: finish writeDsz */
}

/* ---------------------------------------------------------------- */
/* format dxf */

char* readLine(FILE* file)
{
    char str[255];
    /* TODO: replace all scanf code */
    fscanf(file, "%s", str);
    return lTrim(str, ' ');
}

char readDxf(EmbPattern* pattern, const char* fileName)
{
    FILE* file = 0;
    char* buff = "";
    char* dxfVersion = "";
    char* section = "";
    char* tableName = "";
    char* layerName = "";
    char* entityType = "";
    /*char layerColorHash[100][8]; */ /* hash <layerName, EmbColor> */

    int eof = 0; /* End Of File */

    double bulge = 0.0, firstX = 0.0, firstY = 0.0, x = 0.0, y, prevX = 0.0, prevY = 0.0;
    char firstStitch = 1;
    char bulgeFlag = 0;
    int fileLength = 0;

    if (!validateReadPattern(pattern, fileName, "readDxf"))
        return 0;

    file = fopen(fileName, "r");
    if (!file)
    {
        printf("ERROR: format-dxf.c readDxf(), cannot open %s for reading\n", fileName);
        return 0;
    }

    fseek(file, 0L, SEEK_END);

    fileLength = ftell(file);
    fseek(file, 0L, SEEK_SET);

    while(ftell(file) < fileLength)
    {
        buff = readLine(file);
        /*printf("%s\n", buff);*/
        if ( (!strcmp(buff, "HEADER"))   ||
            (!strcmp(buff, "CLASSES"))  ||
            (!strcmp(buff, "TABLES"))   ||
            (!strcmp(buff, "BLOCKS"))   ||
            (!strcmp(buff, "ENTITIES")) ||
            (!strcmp(buff, "OBJECTS"))  ||
            (!strcmp(buff, "THUMBNAILIMAGE")))
        {
            section = buff;
            printf("SECTION:%s\n", buff);
        }
        if (!strcmp(buff, "ENDSEC"))
        {
            section = "";
            printf("ENDSEC:%s\n", buff);
        }
        if ( (!strcmp(buff, "ARC"))        ||
            (!strcmp(buff, "CIRCLE"))     ||
            (!strcmp(buff, "ELLIPSE"))    ||
            (!strcmp(buff, "LINE"))       ||
            (!strcmp(buff, "LWPOLYLINE")) ||
            (!strcmp(buff, "POINT")))
        {
            entityType = buff;
        }
        if (!strcmp(buff, "EOF"))
        {
            eof = 1;
        }

        if (!strcmp(section, "HEADER"))
        {
            if (!strcmp(buff, "$ACADVER"))
            {
                buff = readLine(file);
                dxfVersion = readLine(file);
                /* TODO: Allow these versions when POLYLINE is handled. */
                if ((!strcmp(dxfVersion, DXF_VERSION_R10))
                || (!strcmp(dxfVersion, DXF_VERSION_R11))
                || (!strcmp(dxfVersion, DXF_VERSION_R12))
                || (!strcmp(dxfVersion, DXF_VERSION_R13)))
                    return 0;
            }
        }
        else if (!strcmp(section,"TABLES"))
        {
            if (!strcmp(buff,"ENDTAB"))
            {
                tableName = NULL;
            }

            if (tableName == NULL)
            {
                if (!strcmp(buff,"2")) /* Table Name */
                {
                    tableName = readLine(file);
                }
            }
            else if (!strcmp(tableName, "LAYER"))
            {
                /* Common Group Codes for Tables */
                if (!strcmp(buff,"5")) /* Handle */
                {
                    buff = readLine(file);
                    continue;
                }
                else if (!strcmp(buff,"330")) /* Soft Pointer */
                {
                    buff = readLine(file);
                    continue;
                }
                else if (!strcmp(buff,"100")) /* Subclass Marker */
                {
                    buff = readLine(file);
                    continue;
                }
                else if (!strcmp(buff,"70")) /* Number of Entries in Table */
                {
                    buff = readLine(file);
                    continue;
                }
                /* The meaty stuff */
                else if (!strcmp(buff,"2")) /* Layer Name */
                {
                    layerName = readLine(file);
                }
                else if (!strcmp(buff,"62")) /* Color Number */
                {
                    unsigned char colorNum;
                    EmbColor* co;

                    buff = readLine(file);
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
                    layerName = NULL;
                }
            }
        }
        else if (!strcmp(section,"ENTITIES"))
        {
            /* Common Group Codes for Entities */
            if (!strcmp(buff, "5")) /* Handle */
            {
                buff = readLine(file);
                continue;
            }
            else if (!strcmp(buff, "330")) /* Soft Pointer */
            {
                buff = readLine(file);
                continue;
            }
            else if (!strcmp(buff, "100")) /* Subclass Marker */
            {
                buff = readLine(file);
                continue;
            }
            else if (!strcmp(buff, "8")) /* Layer Name */
            {
                buff = readLine(file);
                /* embPattern_changeColor(pattern, colorIndexMap[buff]); TODO: port to C */
                continue;
            }

            if (!strcmp(entityType,"LWPOLYLINE"))
            {
                double* arcMidX = 0;
                double* arcMidY = 0;
                /* The not so important group codes */
                if (!strcmp(buff, "90")) /* Vertices */
                {
                    buff = readLine(file);
                    continue;
                }
                else if (!strcmp(buff,"70")) /* Polyline Flag */
                {
                    buff = readLine(file);
                    continue;
                }
                /* TODO: Try to use the widths at some point */
                else if (!strcmp(buff,"40")) /* Starting Width */
                {
                    buff = readLine(file);
                    continue;
                }
                else if (!strcmp(buff,"41")) /* Ending Width */
                {
                    buff = readLine(file);
                    continue;
                }
                else if (!strcmp(buff,"43")) /* Constant Width */
                {
                    buff = readLine(file);
                    continue;
                }
                /* The meaty stuff */
                else if (!strcmp(buff,"42")) /* Bulge */
                {
                    buff = readLine(file);
                    bulge = atof(buff);
                    bulgeFlag = 1;
                }
                else if (!strcmp(buff,"10")) /* X */
                {
                    buff = readLine(file);
                    x = atof(buff);
                }
                else if (!strcmp(buff,"20")) /* Y */
                {
                    buff = readLine(file);
                    y = atof(buff);

                    if (bulgeFlag)
                    {
                        bulgeFlag = 0;
                        if (!getArcDataFromBulge(bulge, prevX, prevY, x, y, arcMidX, arcMidY, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
                        {
                            /*TODO: error */
                            return 0;
                        }
                        if (firstStitch)
                        {
                            /* embPattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        }
                        /* embPattern_addStitchAbs(pattern, x, y, ARC, 1); TODO: Add arcTo point to embPath pointList */
                    }
                    else
                    {
                        /*if (firstStitch) embPattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
                        /*else            embPattern_addStitchAbs(pattern, x, y, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
                    }
                    prevX = x;
                    prevY = y;
                    if (firstStitch)
                    {
                        firstX = x;
                        firstY = y;
                        firstStitch = 0;
                    }
                }
                else if (!strcmp(buff,"0"))
                {
                    entityType = NULL;
                    firstStitch = 1;
                    if (bulgeFlag)
                    {
                        bulgeFlag = 0;
                        if (!getArcDataFromBulge(bulge, prevX, prevY, firstX, firstY, arcMidX, arcMidY, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
                        {
                            /*TODO: error */
                            return 0;
                        }
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

    fclose(file);

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

char writeDxf(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeDxf"))
        return 0;

    return 0; /*TODO: finish writeDxf */
}

/* ---------------------------------------------------------------- */
/* format edr */

char readEdr(EmbPattern* pattern, const char* fileName) {
    int numberOfColors, i;
    FILE* file;

    if (!validateReadPattern(pattern, fileName, "readEdr")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }

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
    fclose(file);
    return 1;
}

char writeEdr(EmbPattern* pattern, const char* fileName) {
    FILE* file;
    int i;

    if (!validateWritePattern(pattern, fileName, "writeEdr")) {
        return 0;
    }

    file = fopen(fileName, "wb");
    if (!file) {
        return 0;
    }

    for (i = 0; i < pattern->threads->count; i++) {
        embColor_write(file, pattern->threads->thread[i].color, 4);
    }
    fclose(file);
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

char readEmd(EmbPattern* pattern, const char* fileName) {
    unsigned char b[2];
    char dx = 0, dy = 0;
    int flags = NORMAL;
    char endOfStream = 0;
    unsigned char jemd0[6]; /* TODO: more descriptive name */
    int width, height, colors;
    int i;
    FILE* file;

    if (!validateReadPattern(pattern, fileName, "readEmd")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    embPattern_loadExternalColorFile(pattern, fileName);

    fread(jemd0, 1, 6, file); /* TODO: check return value */
    width = fread_int16(file);
    height = fread_int16(file);
    colors = fread_int16(file);

    printf("width: %d\nheight: %d\ncolors: %d\n", width, height, colors);

    fseek(file, 0x30, SEEK_SET);

    for (i = 0; !endOfStream; i++) {
            flags = NORMAL;
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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeEmd(EmbPattern* pattern, const char* fileName) {
    FILE *file;
    if (!validateWritePattern(pattern, fileName, "writeEmd")) {
        return 0;
    }
    file = fopen(fileName, "wb");
    if (!file) {
        puts("ERROR: Failed to open file.");
        return 0;
    }
    fclose(file);
    puts("writeEmd not implimented.");
    return 0; /*TODO: finish writeEmd */
}

/* ---------------------------------------------------------------- */
/* format exp */

static char expDecode(unsigned char a1) {
    return (a1 > 0x80) ? ((-~a1) - 1) : a1;
}

char readExp(EmbPattern* pattern, const char* fileName) {
    FILE* file;
    unsigned char b[2];

    if (!validateReadPattern(pattern, fileName, "readExp")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    embPattern_loadExternalColorFile(pattern, fileName);

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
    fclose(file);

    embPattern_end(pattern);

    return 1;
}

char writeExp(EmbPattern* pattern, const char* fileName) {
    FILE* file;
    double xx, yy;
    int i;

    if (!validateWritePattern(pattern, fileName, "writeExp")) {
        return 0;
    }
    file = fopen(fileName, "wb");
    if (!file) {
        puts("ERROR: writeExp failed to open file.");
        return 0;
    }
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
    fclose(file);
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

char readExy(EmbPattern* pattern, const char* fileName) {
    unsigned char b[3];
    FILE* file;

    if (!validateReadPattern(pattern, fileName, "readExy")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    embPattern_loadExternalColorFile(pattern, fileName);
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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeExy(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeExy")) {
        return 0;
    }
    /* TODO: fopen() needs to occur here 
        after the check for no stitches */
    return 0; /*TODO: finish writeExy */
}

/* ---------------------------------------------------------------- */
/* format eys */

char readEys(EmbPattern* pattern, const char* fileName) {
    if (!validateReadPattern(pattern, fileName, "readEys")) {
        return 0;
    }
    return 0; /*TODO: finish readEys */
}

char writeEys(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeEys")) {
        return 0;
    }
    /* TODO: fopen() needs to occur here 
        after the check for no stitches */
    return 0; /*TODO: finish writeEys */
}

/* ---------------------------------------------------------------- */
/* format fxy */

char readFxy(EmbPattern* pattern, const char* fileName) {
    FILE* file;
    if (!validateReadPattern(pattern, fileName, "readFxy")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    embPattern_loadExternalColorFile(pattern, fileName);
    /* TODO: review for combining code. This line appears 
        to be the only difference from the GT format. */
    fseek(file, 0x100, SEEK_SET);

    while (1) {
        int stitchType = NORMAL;
        int b1 = (int)binaryReadByte(file);
        int b2 = (int)binaryReadByte(file);
        unsigned char commandByte = binaryReadByte(file);

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
    fclose(file);

    embPattern_end(pattern);

    return 1;
}

char writeFxy(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeFxy")) return 0;

    /* TODO: fopen() needs to occur here
        after the check for no stitches */

    return 0; /*TODO: finish writeFxy */
}

/* ---------------------------------------------------------------- */
/* format gc */

/* Smoothie G-Code */

char readGc(EmbPattern* pattern, const char* fileName) {
    if (!validateReadPattern(pattern, fileName, "readGc")) {
        return 0;
    }
    embPattern_end(pattern);
    return 0; /*TODO: finish readGc */
}

char writeGc(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeGc")) {
        return 0;
    }
    /* TODO: fopen() needs to occur here after the check for no stitches */
    return 0; /*TODO: finish writeGc */
}

/* ---------------------------------------------------------------- */
/* format gnc */

char readGnc(EmbPattern* pattern, const char* fileName)
{
    if (!validateReadPattern(pattern, fileName, "readGnc")) {
        return 0;
    }

    embPattern_end(pattern);

    return 0; /*TODO: finish readGnc */
}

char writeGnc(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeGnc")) {
        return 0;
    }

    /* TODO: fopen() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writeGnc */
}

/* ---------------------------------------------------------------- */
/* format gt */

char readGt(EmbPattern* pattern, const char* fileName) {
    FILE* file;

    if (!validateReadPattern(pattern, fileName, "readGt")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    embPattern_loadExternalColorFile(pattern, fileName);
    /* TODO: review for combining code. This line appears 
        to be the only difference from the FXY format. */
    fseek(file, 0x200, SEEK_SET);

    while (1) {
        int stitchType = NORMAL;
        int b1 = (int)binaryReadByte(file);
        int b2 = (int)binaryReadByte(file);
        unsigned char commandByte = binaryReadByte(file);

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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeGt(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeGt")) {
        return 0;
    }
    /* TODO: fopen() needs to occur 
        here after the check for no stitches */

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

char readHus(EmbPattern* pattern, const char* fileName)
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
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readHus")) return 0;

    file = fopen(fileName, "rb");
    if (!file) {
        puts("ERROR: Failed to open file.");
        return 0;
    }

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
    binaryReadBytes(file, stringVal, 8); /* TODO: check return value */

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

    fclose(file);

    embPattern_end(pattern);

    return 1;
}

char writeHus(EmbPattern* pattern, const char* fileName)
{
    EmbRect boundingRect;
    int stitchCount, minColors, patternColor, attributeSize, xCompressedSize, yCompressedSize, i;
    double previousX, previousY;
    short right, top, bottom, left;
    unsigned int code, colors, offset1, offset2;
    unsigned char *xValues = 0, *yValues = 0, *attributeValues = 0,
        *attributeCompressed = 0, *xCompressed = 0, *yCompressed = 0;
    EmbStitch st;
    FILE* file;

    if (!validateWritePattern(pattern, fileName, "writeHus")) return 0;

    file = fopen(fileName, "wb");
    if (!file) {
        puts("ERROR: Failed to open file.");
        return 0;
    }
    
    stitchCount = pattern->stitchList->count;
    /* embPattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */
    minColors = pattern->threads->count;
    patternColor = minColors;
    if (minColors > 24) minColors = 24;
    code = 0x00C8AF5B;
    fwrite_nbytes(file, &code, 4);
    fwrite_nbytes(file, &stitchCount, 4);
    fwrite_nbytes(file, &minColors, 4);

    boundingRect = embPattern_calcBoundingBox(pattern);
    right = (short) round(boundingRect.right * 10.0);
    top = (short) -round(boundingRect.top * 10.0);
    left = (short) round(boundingRect.left * 10.0);
    bottom = (short) -round(boundingRect.bottom * 10.0);
    fwrite_nbytes(file, &right, 2);
    fwrite_nbytes(file, &top, 2);
    fwrite_nbytes(file, &left, 2);
    fwrite_nbytes(file, &bottom, 2);

    colors = 0x2A + 2 * minColors;
    fwrite_nbytes(file, &colors, 4);

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
    fwrite_nbytes(file, &offset1, 4);
    fwrite_nbytes(file, &offset2, 4);
    fpad(file, 0, 10);

    for (i = 0; i < patternColor; i++) {
        short color_index = (short)embThread_findNearestColor_fromThread(pattern->threads->thread[i].color, husThreads, 29);
        fwrite_nbytes(file, &color_index, 2);
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

    fclose(file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format inb */

char readInb(EmbPattern* pattern, const char* fileName)
{
    FILE* file;
    /* TODO: determine what this represents */
    unsigned char fileDescription[8], nullVal, bytesUnknown[300];
    int stitchCount, x, y, i, fileLength;
    short width, height, colorCount, unknown3, unknown2,
        nullbyte, left, right, top, bottom, imageWidth, imageHeight;

    if (!validateReadPattern(pattern, fileName, "readInb")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }

    embPattern_loadExternalColorFile(pattern, fileName);
    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    binaryReadBytes(file, fileDescription, 8); /* TODO: check return value */
    nullVal = binaryReadByte(file);
    fread_int16(file);
    stitchCount = fread_int32(file);
    width = fread_int16(file);
    height = fread_int16(file);
    colorCount = fread_int16(file);
    unknown3 = fread_int16(file);
    unknown2 = fread_int16(file);
    imageWidth = fread_int16(file);
    imageHeight = fread_int16(file);
    binaryReadBytes(file, bytesUnknown, 300); /* TODO: check return value */
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
        x = binaryReadByte(file);
        y = binaryReadByte(file);
        type = binaryReadByte(file);
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
    fclose(file);

    embPattern_end(pattern);
    embPattern_flipVertical(pattern);

    return 1;
}

char writeInb(EmbPattern* pattern, const char* fileName)
{
    FILE *file;

    if (!validateWritePattern(pattern, fileName, "writeInb"))
        return 0;

    file = fopen(fileName, "w");
    if (!file) return 0;

    fclose(file);

    puts("writeInb not implimented.");
    return 0; /*TODO: finish writeInb */
}

/* ---------------------------------------------------------------- */
/* format inf */

char readInf(EmbPattern* pattern, const char* fileName)
{
    int numberOfColors, i;
    FILE* file;
    char colorType[50];
    char colorDescription[50];
    EmbThread t;

    if (!validateReadPattern(pattern, fileName, "readInf")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
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
    fclose(file);
    return 1;
}

char writeInf(EmbPattern* pattern, const char* fileName) {
    int i, bytesRemaining;
    FILE* file;

    if (!validateWritePattern(pattern, fileName, "writeInf")) {
        return 0;
    }
    file = fopen(fileName, "wb");
    if (!file) {
        return 0;
    }
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
        fprintf(file, buffer);
        fwrite("\0", 1, 1, file);
    }
    /* It appears that there should be a pad here otherwise it clips into
     * the color description. */
    fpad(file, 0, 8);
    fseek(file, -8, SEEK_END);
    bytesRemaining = ftell(file);
    fseek(file, 8, SEEK_SET);
    binaryWriteUIntBE(file, bytesRemaining);
    fclose(file);
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

char readJef(EmbPattern* pattern, const char* fileName) {
    int stitchOffset, formatFlags, numberOfColors, numberOfStitchs;
    int hoopSize, i;
    struct hoop_padding bounds, rectFrom110x110;
    struct hoop_padding rectFrom50x50, rectFrom200x140, rect_from_custom;
    int stitchCount;
    char date[8], time[8];

    FILE* file = 0;

    unsigned char b0 = 0, b1 = 0;
    char dx = 0, dy = 0;
    int flags = 0;

    if (!validateReadPattern(pattern, fileName, "readJef")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }

    stitchOffset = fread_int32(file);
    formatFlags = fread_int32(file); /* TODO: find out what this means */

    binaryReadBytes(file, (unsigned char*) date, 8); /* TODO: check return value */
    binaryReadBytes(file, (unsigned char*) time, 8); /* TODO: check return value */
    numberOfColors = fread_int32(file);
    numberOfStitchs = fread_int32(file);
    hoopSize = fread_int32(file);
    jefSetHoopFromId(pattern, hoopSize);

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
        flags = NORMAL;
        b0 = (unsigned char)fgetc(file);
        if (feof(file)) {
            break;
        }
        b1 = (unsigned char)fgetc(file);
        if (feof(file)) {
            break;
        }
        if (b0 == 0x80) {
            if (b1 & 1) {
                b0 = (unsigned char)fgetc(file);
                if (feof(file))
                    break;
                b1 = (unsigned char)fgetc(file);
                if (feof(file))
                    break;
                flags = STOP;
            }
            else if ((b1 == 2) || (b1 == 4) || b1 == 6) {
                flags = TRIM;
                b0 = (unsigned char)fgetc(file);
                if (feof(file)) {
                    break;
                }
                b1 = (unsigned char)fgetc(file);
                if (feof(file)) {
                    break;
                }
            }
            else if (b1 == 0x10) {
                embPattern_addStitchRel(pattern, 0.0, 0.0, END, 1);
                break;
            }
        }
        dx = jefDecode(b0);
        dy = jefDecode(b1);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    fclose(file);

    embPattern_end(pattern);
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

char writeJef(EmbPattern* pattern, const char* fileName)
{
    int colorlistSize, minColors, designWidth, designHeight, i;
    EmbRect boundingRect;
    FILE* file = 0;
    EmbTime time;
    EmbStitch st;
    double dx = 0.0, dy = 0.0, xx = 0.0, yy = 0.0;
    unsigned char b[4];

    if (!validateWritePattern(pattern, fileName, "writeJef")) {
        return 0;
    }

    file = fopen(fileName, "wb");
    if (!file) return 0;

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
    fwrite_nbytes(file, &(pattern->threads->count), 4);
    int data = pattern->stitchList->count + embMaxInt(0, (6 - colorlistSize) * 2) + 1;
    fwrite_nbytes(file, &data, 4);

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
    fclose(file);
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

char readKsm(EmbPattern* pattern, const char* fileName) {
    int prevStitchType = NORMAL;
    char b[3];
    FILE* file;
    if (!validateReadPattern(pattern, fileName, "readKsm")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        puts("ERROR: cannot open file.");
        return 0;
    }
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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeKsm(EmbPattern* pattern, const char* fileName) {
    FILE* file = 0;
    double xx, yy;
    int i;
    unsigned char b[4];

    if (!validateWritePattern(pattern, fileName, "writeKsm")) {
        return 0;
    }
    file = fopen(fileName, "wb");
    if (!file) {
        puts("ERROR: cannot open file.");
        return 0;
    }
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
    fclose(file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format max */

/* Pfaff MAX embroidery file format */

char readMax(EmbPattern* pattern, const char* fileName) {
    int i, flags, stitchCount;
    FILE* file;

    if (!validateReadPattern(pattern, fileName, "readMax")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    fseek(file, 0xD5, SEEK_SET);
    stitchCount = fread_uint32(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < stitchCount; i++) {
        unsigned char b[8];
        double dx, dy;
        flags = NORMAL;
        if (fread(b, 1, 8, file) != 8) {
            break;
        }
        dx = maxDecode(b[0], b[1], b[2]);
        dy = maxDecode(b[4], b[5], b[6]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    fclose(file);
    embPattern_end(pattern);
    embPattern_flipVertical(pattern);
    return 1;
}

char writeMax(EmbPattern* pattern, const char* fileName) {
    FILE* file;
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

    if (!validateWritePattern(pattern, fileName, "writeMax"))
        return 0;

    file = fopen(fileName, "wb");
    if (!file) {
        return 0;
    }

    fwrite(header, 1, 0xD5, file);
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        x = (int)round(st.x * 10.0);
        y = (int)round(st.y * 10.0);
        maxEncode(file, x, y);
    }
    fclose(file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format mit */

char readMit(EmbPattern* pattern, const char* fileName) {
    unsigned char data[2];
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readMit")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        puts("ERROR: Failed to open file.");
        return 0;
    }

    embPattern_loadExternalColorFile(pattern, fileName);

    while (fread(data, 1, 2, file) == 2) {
        int x = mitDecodeStitch(data[0]);
        int y = mitDecodeStitch(data[1]);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, NORMAL, 1);
    }
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeMit(EmbPattern* pattern, const char* fileName) {
    FILE* file = 0;
    double xx, yy;
    int i;

    if (!validateWritePattern(pattern, fileName, "writeMit")) {
        return 0;
    }
    file = fopen(fileName, "wb");
    if (!file) {
        puts("ERROR: Failed to open file.");
        return 0;
    }
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
    fclose(file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format new */

char readNew(EmbPattern* pattern, const char* fileName) {
    unsigned int stitchCount;
    unsigned char data[3];
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readNew")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    embPattern_loadExternalColorFile(pattern, fileName);
    stitchCount = fread_uint16(file);
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

    fclose(file);
    embPattern_end(pattern);

    return 1;
}

char writeNew(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeNew")) {
        return 0;
    }

    /* TODO: fopen() needs to occur 
    here after the check for no stitches */

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

    binaryReadBytes(file, leadIn, 3); /* TODO: check return value */
    stringLength = binaryReadByte(file);
    libraryName = (char*)malloc(sizeof(char) * stringLength * 2);
    if (!libraryName) { printf("ERROR: format-ofm.c ofmReadLibrary(), unable to allocate memory for libraryName\n"); return 0; }
    binaryReadBytes(file, (unsigned char*)libraryName, stringLength * 2); /* TODO: check return value */
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
    binaryReadBytes(file, (unsigned char*)s, len);
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

    /* int v = binaryReadBytes(3); TODO: review */
    fread_int16(file);
    binaryReadByte(file);
    len = binaryReadByte(file);
    s = (char*)malloc(2 * len);
    if (!s) { printf("ERROR: format-ofm.c ofmReadBlockHeader(), unable to allocate memory for s\n"); return; }
    binaryReadBytes(file, (unsigned char *)s, 2 * len);
    /* TODO: check return value */
    /* 0, 0, 0, 0, 1, 1, 1, 0, 64, 64 */
    for (i=0; i<10; i++) {
        val[i] = fread_int32(file);
        if (EMB_DEBUG) {
            printf("val[%d] = %d\n", i, val[i]);
        }
    }
    short1 = fread_int16(file); /*  0 */
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
    binaryReadBytes(file, (unsigned char*)expandedString, stringLen);
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
        colorNameLength = binaryReadByte(file);
        fread(colorName, 1, colorNameLength*2, file);
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
        binaryReadBytes(file, stitch, 5); /* TODO: check return value */
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

char readOfm(EmbPattern* pattern, const char* fileName)
{
    int unknownCount = 0;
    int key = 0, classNameLength;
    char* s = 0;
    FILE* fileCompound = 0;
    FILE* file = 0;
    bcf_file* bcfFile = 0;

    if (!validateReadPattern(pattern, fileName, "readOfm")) {
        return 0;
    }

    fileCompound = fopen(fileName, "rb");
    if (!fileCompound) return 0;

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
    binaryReadBytes(file, (unsigned char*)s, classNameLength); /* TODO: check return value */
    unknownCount = fread_int16(file); /* TODO: determine what unknown count represents */

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

    fclose(fileCompound);
    fclose(file);

    embPattern_end(pattern);
    embPattern_flip(pattern, 1, 1);

    return 1;
}

char writeOfm(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeOfm")) {
        return 0;
    }

    /* TODO: fopen() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writeOfm */
}

/* ---------------------------------------------------------------- */
/* format pcd */

char readPcd(EmbPattern* pattern, const char* fileName) {
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    double dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount = 0;
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readPcd")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    version = binaryReadByte(file);
    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * 3 for PCS with large hoop (115x120)
     */
    hoopSize = binaryReadByte(file);
    colorCount = fread_uint16(file);

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
        } else if (b[8] & 0x04) {
            flags = TRIM;
        } else if (b[8] != 0) {
        /* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
        }
        dx = pcdDecode(b[1], b[2], b[3]);
        dy = pcdDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    fclose(file);
    embPattern_end(pattern);

    return 1;
}

char writePcd(EmbPattern* pattern, const char* fileName) {
    FILE* file = 0;
    int i;
    unsigned char colorCount;
    double xx = 0.0, yy = 0.0;

    if (!validateWritePattern(pattern, fileName, "writePcd")) {
        return 0;
    }
    file = fopen(fileName, "wb");
    if (!file) {
        return 0;
    }
    binaryWriteByte(file, (unsigned char)'2');
    /* TODO: select hoop size defaulting to Large PCS hoop */
    binaryWriteByte(file, 3);
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
        pcdEncode(file, (int)round(st.x * 10.0), (int)round(st.y * 10.0), st.flags);
    }
    fclose(file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format pcm */

static double pcmDecode(unsigned char a1, unsigned char a2, unsigned char a3) {
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF) {
        return (-((~(res) & 0x7FFFFF) - 1));
    }
    return res;
}

char readPcm(EmbPattern* pattern, const char* fileName) {
    int i = 0;
    unsigned char b[9];
    double dx = 0, dy = 0;
    int flags = 0, st = 0;
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readPcm")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    fseek(file, 4, SEEK_SET);
    for (i = 0; i < 16; i++) {
        int colorNumber;
        (void)fgetc(file); /* zero */
        colorNumber = fgetc(file);
        embPattern_addThread(pattern, pcmThreads[colorNumber]);
    }
    st = fread_uint16_be(file);
    /* READ STITCH RECORDS */
    for (i = 0; i < st; i++) {
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
        dx = pcmDecode(b[2], b[1], b[0]);
        dy = pcmDecode(b[6], b[5], b[4]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    fclose(file);
    embPattern_end(pattern);

    return 1;
}

char writePcm(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writePcm")) {
        return 0;
    }

/* TODO: fopen() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writePcm */
}

/* ---------------------------------------------------------------- */
/* format pcq */

static double pcqDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF)
    {
        return (-((~(res) & 0x7FFFFF) - 1));
    }
    return res;
}

static void pcqEncode(FILE* file, int dx, int dy, int flags)
{
    unsigned char b[9];

    b[0] = 0;
    b[1] = (unsigned char)(dx & 0xFF);
    b[2] = (unsigned char)((dx >> 8) & 0xFF);
    b[3] = (unsigned char)((dx >> 16) & 0xFF);

    b[4] = 0;
    b[5] = (unsigned char)(dy & 0xFF);
    b[6] = (unsigned char)((dy >> 8) & 0xFF);
    b[7] = (unsigned char)((dy >> 16) & 0xFF);

    b[8] = 0;
    if (flags & STOP) {
        b[8] |= 0x01;
    }
    if (flags & TRIM) {
        b[8] |= 0x04;
    }
    fwrite(b, 1, 9, file);
}

char readPcq(EmbPattern* pattern, const char* fileName)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    double dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount;
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readPcq")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }

    version = binaryReadByte(file);
    hoopSize = binaryReadByte(file);
    /* 0 for PCD
     * 1 for PCQ (MAXI)
     * 2 for PCS with small hoop(80x80)
     * 3 for PCS with large hoop (115x120)
     */
    colorCount = fread_uint16(file);

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
        dx = pcqDecode(b[1], b[2], b[3]);
        dy = pcqDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    fclose(file);
    embPattern_end(pattern);

    return 1;
}

char writePcq(EmbPattern* pattern, const char* fileName)
{
    FILE* file = 0;
    int i;

    if (!validateWritePattern(pattern, fileName, "writePcq")) {
        return 0;
    }

    file = fopen(fileName, "wb");
    if (!file) return 0;

    binaryWriteByte(file, (unsigned char)'2');
    binaryWriteByte(file, 3); /* TODO: select hoop size defaulting to Large PCS hoop */
    binaryWriteUShort(file, (unsigned short)pattern->threads->count);
    for (i = 0; i < pattern->threads->count; i++) {
        EmbColor color = pattern->threads->thread[i].color;
        unsigned char b[4];
        b[0] = color.r;
        b[1] = color.g;
        b[2] = color.b;
        b[3] = 0;
        fread(b, 1, 4, file);
    }

    /* write remaining colors to reach 16 */
    fpad(file, 0, (16-i)*4);

    binaryWriteUShort(file, (unsigned short)pattern->stitchList->count);
    /* write stitches */
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st = pattern->stitchList->stitch[i];
        pcqEncode(file, (int)round(st.x * 10.0), (int)round(st.y * 10.0), st.flags);
    }
    fclose(file);
    return 1;
}


/* ---------------------------------------------------------------- */
/* format pcs */

static double pcsDecode(unsigned char a1, unsigned char a2, unsigned char a3)
{
    int res = a1 + (a2 << 8) + (a3 << 16);
    if (res > 0x7FFFFF)
    {
        return (-((~(res) & 0x7FFFFF) - 1));
    }
    return res;
}

static void pcsEncode(FILE* file, int dx, int dy, int flags)
{
    unsigned char flagsToWrite = 0;

    if (!file) { printf("ERROR: format-pcs.c pcsEncode(), file argument is null\n"); return; }

    binaryWriteByte(file, (unsigned char)0);
    binaryWriteByte(file, (unsigned char)(dx & 0xFF));
    binaryWriteByte(file, (unsigned char)((dx >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((dx >> 16) & 0xFF));

    binaryWriteByte(file, (unsigned char)0);
    binaryWriteByte(file, (unsigned char)(dy & 0xFF));
    binaryWriteByte(file, (unsigned char)((dy >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((dy >> 16) & 0xFF));
    if (flags & STOP)
    {
        flagsToWrite |= 0x01;
    }
    if (flags & TRIM)
    {
        flagsToWrite |= 0x04;
    }
    binaryWriteByte(file, flagsToWrite);
}

char readPcs(EmbPattern* pattern, const char* fileName)
{
    char allZeroColor = 1;
    int i = 0;
    unsigned char b[9];
    double dx = 0, dy = 0;
    int flags = 0, st = 0;
    unsigned char version, hoopSize;
    unsigned short colorCount;
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readPcs")) return 0;

    file = fopen(fileName, "rb");
    if (!file)
        return 0;

    version = binaryReadByte(file);
    hoopSize = binaryReadByte(file);  /* 0 for PCD, 1 for PCQ (MAXI), 2 for PCS with small hoop(80x80), */
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
        dx = pcsDecode(b[1], b[2], b[3]);
        dy = pcsDecode(b[5], b[6], b[7]);
        embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    fclose(file);
    embPattern_end(pattern);

    return 1;
}

char writePcs(EmbPattern* pattern, const char* fileName)
{
    FILE* file = 0;
    int i;

    if (!validateWritePattern(pattern, fileName, "writePcs")) {
        return 0;
    }

    file = fopen(fileName, "wb");
    if (!file)
        return 0;

    binaryWriteByte(file, (unsigned char)'2');
    binaryWriteByte(file, 3); /* TODO: select hoop size defaulting to Large PCS hoop */
    binaryWriteUShort(file, (unsigned short)pattern->threads->count);
    for (i = 0; i < pattern->threads->count; i++) {
        EmbColor color = pattern->threads->thread[i].color;
        binaryWriteByte(file, color.r);
        binaryWriteByte(file, color.g);
        binaryWriteByte(file, color.b);
        binaryWriteByte(file, 0);
    }

    for (; i < 16; i++)
    {
        binaryWriteUInt(file, 0); /* write remaining colors to reach 16 */
    }

    binaryWriteUShort(file, (unsigned short)pattern->stitchList->count);
    /* write stitches */
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st = pattern->stitchList->stitch[i];
        pcsEncode(file, (int)round(st.x * 10.0), (int)round(st.y * 10.0), st.flags);
    }
    fclose(file);
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
    int stitchNumber = 0;

    while (!feof(f)) {
        int val1 = (int)(unsigned char)fgetc(f);
        int val2 = (int)(unsigned char)fgetc(f);

        int stitchType = NORMAL;
        if (val1 == 0xFF && val2 == 0x00) {
            embPattern_end(pattern);
            break;
        }
        if (val1 == 0xFE && val2 == 0xB0) {
            (void)fgetc(f);
            embPattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1);
            stitchNumber++;
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

            val2 = fgetc(file);
        } else if (val1 >= 0x40) {
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
        } else if (val2 >= 0x40) {
            val2 -= 0x80;
        }
        embPattern_addStitchRel(pattern, val1 / 10.0,
                val2 / 10.0, stitchType, 1);
        stitchNumber++;
    }
}

static void pecEncodeJump(FILE* file, int x, int types) {
    int outputVal = abs(x) & 0x7FF;
    unsigned int orPart = 0x80;

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
        outputVal = x + 0x1000 & 0x7FF;
        outputVal |= 0x800;
    }
    binaryWriteByte(file, (unsigned char)(((outputVal >> 8) & 0x0F) | orPart));
    binaryWriteByte(file, (unsigned char)(outputVal & 0xFF));
}

static void pecEncodeStop(FILE* file, unsigned char val)
{
    if (!file) {
        printf("ERROR: format-pec.c pecEncodeStop(), file argument is null\n");
        return;
    }
    binaryWriteByte(file, 0xFE);
    binaryWriteByte(file, 0xB0);
    binaryWriteByte(file, val);
}

char readPec(EmbPattern* pattern, const char* fileName) {
    unsigned int graphicsOffset;
    unsigned char colorChanges;
    int i;
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readPec")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    fseek(file, 0x38, SEEK_SET);
    colorChanges = (unsigned char)binaryReadByte(file);
    for (i = 0; i <= colorChanges; i++) {
        embPattern_addThread(pattern, pecThreads[binaryReadByte(file) % 65]);
    }

    /* Get Graphics offset */
    fseek(file, 0x20A, SEEK_SET);

    graphicsOffset = (unsigned int)(fgetc(file));
    graphicsOffset |= (fgetc(file) << 8);
    graphicsOffset |= (fgetc(file) << 16);

    (void)binaryReadByte(file); /* 0x31 */
    (void)binaryReadByte(file); /* 0xFF */
    (void)binaryReadByte(file); /* 0xF0 */
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
    fclose(file);
    embPattern_end(pattern);
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
            binaryWriteByte(file, 0xFF);
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

void writePecStitches(EmbPattern* pattern,
    FILE* file, const char* fileName) {
    EmbRect bounds;
    unsigned char image[38][48];
    int i, j, flen, currentThreadCount, graphicsOffsetLocation;
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
        binaryWriteByte(file, (unsigned char)*start);
        start++;
    }
    fpad(file, 0x20, 16-flen);
    binaryWriteByte(file, 0x0D);
    fpad(file, 0x20, 12);
    fwrite("\xff\x00\x06\x26", 1, 4, file);

    fpad(file, 0x20, 12);
    currentThreadCount = pattern->threads->count;
    binaryWriteByte(file, (unsigned char)(currentThreadCount-1));

    for (i = 0; i < currentThreadCount; i++) {
        EmbColor thr = pattern->threads->thread[i].color;
        unsigned char color = (unsigned char)
            embThread_findNearestColor_fromThread(thr, 
            (EmbThread*)pecThreads, pecThreadCount);
        fwrite(&color, 1, 1, file);
    }
    fpad(file, 0x20, (int)(0x1CF - currentThreadCount));
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

    binaryWriteByte(file, (unsigned char)(graphicsOffsetValue & 0xFF));
    binaryWriteByte(file, (unsigned char)((graphicsOffsetValue >> 8) & 0xFF));
    binaryWriteByte(file, (unsigned char)((graphicsOffsetValue >> 16) & 0xFF));

    fseek(file, 0x00, SEEK_END);

    /* Writing all colors */
    memcpy(image, imageWithFrame, 48*38);

    yFactor = 32.0 / height;
    xFactor = 42.0 / width;
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st = pattern->stitchList->stitch[i];
        int x = (int)round((st.x - bounds.left) * xFactor) + 3;
        int y = (int)round((st.y - bounds.top) * yFactor) + 3;
        image[y][x] = 1;
    }
    writeImage(file, image);

    /* Writing each individual color */
    j = 0;
    for (i = 0; i < currentThreadCount; i++) {
        memcpy(image, imageWithFrame, 48*38);
        for (; j < pattern->stitchList->count; j++) {
            EmbStitch st = pattern->stitchList->stitch[j];
            int x = (int)round((st.x - bounds.left) * xFactor) + 3;
            int y = (int)round((st.y - bounds.top) * yFactor) + 3;
            if (st.flags & STOP) {
                break;
            }
            image[y][x] = 1;
        }
        writeImage(file, image);
    }
}

char writePec(EmbPattern* pattern, const char* fileName) {
    FILE* file = 0;
    if (!validateWritePattern(pattern, fileName, "writePec")) {
        return 0;
    }
    file = fopen(fileName, "wb");
    if (!file) {
        return 0;
    }
    /* TODO: There needs to be a matching flipVertical() call after the write 
        to ensure multiple writes from the same pattern work properly */
    embPattern_flipVertical(pattern); 
    embPattern_fixColorCount(pattern);
    embPattern_correctForMaxStitchLength(pattern, 12.7, 204.7);
    embPattern_scale(pattern, 10.0);
    fwrite("#PEC0001", 1, 8, file);
    writePecStitches(pattern, file, fileName);
    fclose(file);
    return 1;
}


/* ---------------------------------------------------------------- */
/* format pel */

char readPel(EmbPattern* pattern, const char* fileName) {
    if (!pattern) {
        printf("ERROR: format-pel.c readPel(), pattern argument is null\n");
        return 0;
    }
    if (!fileName) {
        printf("ERROR: format-pel.c readPel(), fileName argument is null\n");
        return 0;
    }
    return 0; /*TODO: finish readPel */
}

char writePel(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writePel")) {
        return 0;
    }
    /* TODO: fopen() needs to occur here 
        after the check for no stitches */
    return 0; /*TODO: finish writePel */
}

/* ---------------------------------------------------------------- */
/* format pem */

char readPem(EmbPattern* pattern, const char* fileName)
{
    if (!validateReadPattern(pattern, fileName, "readPem")) {
        return 0;
    }
    return 0; /*TODO: finish ReadPem */
}

char writePem(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writePem")) {
        return 0;
    }

    /* TODO: fopen() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writePem */
}

/* ---------------------------------------------------------------- */
/* format pes */

char readPes(EmbPattern* pattern, const char* fileName) {
    int pecstart, numColors, x;
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readPes")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    fseek(file, 8, SEEK_SET);
    pecstart = fread_int32(file);

    fseek(file, pecstart + 48, SEEK_SET);
    numColors = fgetc(file) + 1;
    for (x = 0; x < numColors; x++) {
        embPattern_addThread(pattern, pecThreads[
                (unsigned char) fgetc(file)]);
    }

    fseek(file, pecstart + 528, SEEK_SET);
    readPecStitches(pattern, file);

    fclose(file);
    embPattern_end(pattern);
    embPattern_flipVertical(pattern);

    return 1;
}

/* static void readPESHeader(FILE* file, EmbPattern* pattern) {
       char* signature = readString(8);
            if (strcmp(signature, "#PES0100") {
                readPESHeaderV10();
            } else if (strcmp(signature, "#PES0090") {
                readPESHeaderV9();
            } else if (strcmp(signature, "#PES0080") {
                readPESHeaderV8();
            } else if (strcmp(signature, "#PES0070") {
                readPESHeaderV7();
            } else if (strcmp(signature, "#PES0060") {
                readPESHeaderV6();
            } else if (strcmp(signature, "#PES0056"){
                readPESHeaderV5();
            } else if (strcmp(signature, "#PES0055") {
               readPESHeaderV5();
                 } else if (strcmp(signature, "#PES0050") {
                readPESHeaderV5();
                 } else if (strcmp(signature, "#PES0040") {
                readPESHeaderV4();
                 } else if (strcmp(signature, "#PES0030") {
                readPESHeaderDefault();
                 } else if (strcmp(signature, "#PES0022") {
                readPESHeaderDefault();
                 } else if (strcmp(signature, "#PES0020") {
                readPESHeaderDefault();
                 } else if (strcmp(signature, "#PES0001") {
                readPESHeaderDefault();
                 } else
            if (strcmp(signature, "#PEC0001") {
                //PEC needs to go straight to reading, no default.
            } else {
                readPESHeaderDefault();
            }
        }
    }

    static void readPESHeaderDefault()  {
        int pecStart = readInt32LE();
        skip(pecStart - readPosition);
    }

    static void readDescriptions()  {
        int DesignStringLength = readInt8();
        String DesignName = readString(DesignStringLength);
        pattern.setName(DesignName);
        int categoryStringLength = readInt8();
        String Category = readString(categoryStringLength);
        pattern.setCategory(Category);
        int authorStringLength = readInt8();
        String Author = readString(authorStringLength);
        pattern.setAuthor(Author);
        int keywordsStringLength = readInt8();
        String keywords = readString(keywordsStringLength);
        pattern.setKeywords(keywords);
        int commentsStringLength = readInt8();
        String Comments = readString(commentsStringLength);
        pattern.setComments(Comments);
    }

    static void readPESHeaderV4()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(pecStart - readPosition);
    }

    static void readPESHeaderV5()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(24);//36 v6
        int fromImageStringLength = readInt8();
        skip(fromImageStringLength);
        skip(24);
        int numberOfProgrammableFillPatterns = readInt16LE();
        if (numberOfProgrammableFillPatterns != 0) {
            seek(pecStart);
            return;
        }
        int numberOfMotifPatterns = readInt16LE();
        if (numberOfMotifPatterns != 0) {
            seek(pecStart);
            return;
        }
        int featherPatternCount = readInt16LE();
        if (featherPatternCount != 0) {
            seek(pecStart);
            return;
        }
        int numberOfColors = readInt16LE();
        for (int i = 0; i < numberOfColors; i++) {
            readThread();
        }
        seek(pecStart);
    }

    static void readPESHeaderV6()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(36);
        int fromImageStringLength = readInt8();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(24);
        int numberOfProgrammableFillPatterns = readInt16LE();
        if (numberOfProgrammableFillPatterns != 0) {
            seek(pecStart);
            return;
        }
        int numberOfMotifPatterns = readInt16LE();
        if (numberOfMotifPatterns != 0) {
            seek(pecStart);
            return;
        }
        int featherPatternCount = readInt16LE();
        if (featherPatternCount != 0) {
            seek(pecStart);
            return;
        }
        int numberOfColors = readInt16LE();
        for (int i = 0; i < numberOfColors; i++) {
            readThread();
        }
        seek(pecStart);
    }
    
    static void readPESHeaderV7()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(36);
        int fromImageStringLength = readInt8();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(24);
        int numberOfProgrammableFillPatterns = readInt16LE();
        if (numberOfProgrammableFillPatterns != 0) {
            seek(pecStart);
            return;
        }
        int numberOfMotifPatterns = readInt16LE();
        if (numberOfMotifPatterns != 0) {
            seek(pecStart);
            return;
        }
        int featherPatternCount = readInt16LE();
        if (featherPatternCount != 0) {
            seek(pecStart);
            return;
        }
        int numberOfColors = readInt16LE();
        for (int i = 0; i < numberOfColors; i++) {
            readThread();
        }
        seek(pecStart);
    }
    
    static void readPESHeaderV8()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(38);
        int fromImageStringLength = readInt8();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(26);
        int numberOfProgrammableFillPatterns = readInt16LE();
        if (numberOfProgrammableFillPatterns != 0) {
            seek(pecStart);
            return;
        }
        int numberOfMotifPatterns = readInt16LE();
        if (numberOfMotifPatterns != 0) {
            seek(pecStart);
            return;
        }
        int featherPatternCount = readInt16LE();
        if (featherPatternCount != 0) {
            seek(pecStart);
            return;
        }
        int numberOfColors = readInt16LE();
        for (int i = 0; i < numberOfColors; i++) {
            readThread();
        }
        seek(pecStart);
    }

    static void readPESHeaderV9()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(14);
        int hoopNameStringLength = readInt8();
        String hoopNameString = readString(hoopNameStringLength);
        if (hoopNameString.length() != 0) {
            pattern.setMetadata("hoop_name", hoopNameString);
        }
        skip(30);
        int fromImageStringLength = readInt8();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(34);
        int numberOfProgrammableFillPatterns = readInt16LE();
        if (numberOfProgrammableFillPatterns != 0) {
            seek(pecStart);
            return;
        }
        int numberOfMotifPatterns = readInt16LE();
        if (numberOfMotifPatterns != 0) {
            seek(pecStart);
            return;
        }
        int featherPatternCount = readInt16LE();
        if (featherPatternCount != 0) {
            seek(pecStart);
            return;
        }
        int numberOfColors = readInt16LE();
        for (int i = 0; i < numberOfColors; i++) {
            readThread();
        }
        seek(pecStart);
    }

    static void readPESHeaderV10()  {
        int pecStart = readInt32LE();
        skip(4);
        readDescriptions();
        skip(14);
        int hoopNameStringLength = readInt8();
        String hoopNameString = readString(hoopNameStringLength);
        if (hoopNameString.length() != 0) {
            pattern.setMetadata("hoop_name", hoopNameString);
        }
        skip(38);
        int fromImageStringLength = readInt8();
        String fromImageString = readString(fromImageStringLength);
        if (fromImageString.length() != 0) {
            pattern.setMetadata("image_file", fromImageString);
        }
        skip(34);
        int numberOfProgrammableFillPatterns = readInt16LE();
        if (numberOfProgrammableFillPatterns != 0) {
            seek(pecStart);
            return;
        }
        int numberOfMotifPatterns = readInt16LE();
        if (numberOfMotifPatterns != 0) {
            seek(pecStart);
            return;
        }
        int featherPatternCount = readInt16LE();
        if (featherPatternCount != 0) {
            seek(pecStart);
            return;
        }
        int numberOfColors = readInt16LE();
        for (int i = 0; i < numberOfColors; i++) {
            readThread();
        }
        seek(pecStart);
    }
    
    static void readThread() {
        int color_code_length = readInt8();
        String color_code = readString(color_code_length);
        int red = readInt8();
        int green = readInt8();
        int blue = readInt8();
        skip(5);
        int descriptionStringLength = readInt8();
        String description = readString(descriptionStringLength);

        int brandStringLength = readInt8();
        String brand = readString(brandStringLength);

        int threadChartStringLength = readInt8();
        String threadChart = readString(threadChartStringLength);

        int color = (red & 0xFF) << 16 | (green & 0xFF) << 8 | (blue & 0xFF);
        pattern.add(new EmbThread(color, description, color_code, brand, threadChart));
    }
*/

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
    EmbColor color;

    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st = pattern->stitchList->stitch[i];
        flag = st.flags;
        color = pattern->threads->thread[st.color].color;
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
    binaryWriteBytes(file, "CSewSeg", 7);

    colorInfo = (short *) calloc(colorCount * 2, sizeof(short));
    colorCode = -1;
    blockCount = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st;
        st = pattern->stitchList->stitch[i];
        j = i;
        flag = st.flags;
        color = pattern->threads->thread[st.color].color;
        newColorCode = embThread_findNearestColor_fromThread(color, (EmbThread*)pecThreads, pecThreadCount);
        if (newColorCode != colorCode) {
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
    int hoopHeight = 1800, hoopWidth = 1300;
    EmbRect bounds;
    binaryWriteShort(file, 0x07); /* string length */
    binaryWriteBytes(file, "CEmbOne", 7);
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
    binaryWriteFloat(file, 1.0f);
    binaryWriteFloat(file, 0.0f);
    binaryWriteFloat(file, 0.0f);
    binaryWriteFloat(file, 1.0f);
    binaryWriteFloat(file, (float)((embRect_width(bounds) - hoopWidth) / 2));
    binaryWriteFloat(file, (float)((embRect_height(bounds) + hoopHeight) / 2));

    binaryWriteShort(file, 1);
    binaryWriteShort(file, 0); /* Translate X */
    binaryWriteShort(file, 0); /* Translate Y */
    binaryWriteShort(file, (short)embRect_width(bounds));
    binaryWriteShort(file, (short)embRect_height(bounds));

    for (i = 0; i < 8; i++) {
        binaryWriteByte(file, 0);
    }
    /*WriteSubObjects(br, pes, SubBlocks); */
}

char writePes(EmbPattern* pattern, const char* fileName) {
    int pecLocation;
    FILE* file = 0;

    if (!validateWritePattern(pattern, fileName, "writePes")) {
        return 0;
    }

    file = fopen(fileName, "wb");
    if (!file) {
        return 0;
    }
    embPattern_flipVertical(pattern);
    embPattern_scale(pattern, 10.0);
    binaryWriteBytes(file, "#PES0001", 8);
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
    binaryWriteByte(file, (unsigned char)(pecLocation & 0xFF));
    binaryWriteByte(file, (unsigned char)(pecLocation >> 8) & 0xFF);
    binaryWriteByte(file, (unsigned char)(pecLocation >> 16) & 0xFF);
    fseek(file, 0x00, SEEK_END);
    writePecStitches(pattern, file, fileName);
    fclose(file);
    return 1;
}


/* ---------------------------------------------------------------- */
/* format phb */

char readPhb(EmbPattern* pattern, const char* fileName)
{
    unsigned int fileOffset;
    short colorCount;
    FILE* file = 0;
    int i;

    if (!pattern) { printf("ERROR: format-phb.c readPhb(), pattern argument is null\n"); return 0; }
    if (!fileName) { printf("ERROR: format-phb.c readPhb(), fileName argument is null\n"); return 0; }

    file = fopen(fileName, "rb");
    if (!file)
        return 0;

    fseek(file, 0x71, SEEK_SET);
    colorCount = fread_int16(file);

    for (i = 0; i < colorCount; i++)
    {
        EmbThread t = pecThreads[(int)binaryReadByte(file)];
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

    colorCount = (short)binaryReadByte(file);
    for (i = 0; i <  colorCount; i++)
    {
        binaryReadByte(file);
    }
    fread_int32(file); /* bytes to end of file */
    fread_int32(file);
    binaryReadByte(file);

    fread_int16(file);
    fread_int16(file);
    fread_int16(file);
    fread_int16(file);
    fread_int16(file);
    fread_int16(file);
    readPecStitches(pattern, file);
    fclose(file);

    embPattern_end(pattern);
    embPattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhb */
}

char writePhb(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writePhb")) {
        return 0;
    }

    /* TODO: fopen() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writePhb */
}

/* ---------------------------------------------------------------- */
/* format phc */

char readPhc(EmbPattern* pattern, const char* fileName)
{
    int colorChanges, version, bytesInSection2;
    unsigned short pecOffset, bytesInSection, bytesInSection3;
    char pecAdd;
    FILE* file = 0;
    int i;

    if (!pattern) { printf("ERROR: format-phc.c readPhc(), pattern argument is null\n"); return 0; }
    if (!fileName) { printf("ERROR: format-phc.c readPhc(), fileName argument is null\n"); return 0; }

    file = fopen(fileName, "rb");
    if (!file) return 0;

    fseek(file, 0x07, SEEK_SET);
    version = binaryReadByte(file) - 0x30; /* converting from ansi number */
    fseek(file, 0x4D, SEEK_SET);
    colorChanges = fread_uint16(file);

    for (i = 0; i < colorChanges; i++)
    {
        EmbThread t = pecThreads[(int)binaryReadByte(file)];
        embPattern_addThread(pattern, t);
    }
    fseek(file, 0x2B, SEEK_SET);
    pecAdd = binaryReadByte(file);
    fread_uint32(file); /* file length */
    pecOffset = fread_uint16(file);
    fseek(file, pecOffset + pecAdd, SEEK_SET);
    bytesInSection = fread_uint16(file);
    fseek(file, bytesInSection, SEEK_CUR);
    bytesInSection2 = fread_uint32(file);
    fseek(file, bytesInSection2, SEEK_CUR);
    bytesInSection3 = fread_uint16(file);
    fseek(file, bytesInSection3 + 0x12, SEEK_CUR);

    readPecStitches(pattern, file);
    fclose(file);
    embPattern_end(pattern);

    embPattern_flipVertical(pattern);
    return 1; /*TODO: finish ReadPhc */
}

char writePhc(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writePhc")) {
        return 0;
    }

    /* TODO: fopen() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writePhc */
}

/* ---------------------------------------------------------------- */
/* format plt */

char readPlt(EmbPattern* pattern, const char* fileName) {
    double x, y;
    double scalingFactor = 40;
    char input[512];
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readPlt")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        printf("ERROR: format-plt.c readPlt(), ");
        printf("cannot open %s for reading\n", fileName);
        return 0;
    }

    embPattern_loadExternalColorFile(pattern, fileName);
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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writePlt(EmbPattern* pattern, const char* fileName) {
    /* TODO: pointer safety */
    double scalingFactor = 40;
    char firstStitchOfBlock = 1;
    FILE* file;
    int i;

    if (!validateWritePattern(pattern, fileName, "writePlt")) {
        return 0;
    }
    file = fopen(fileName, "w");
    if (!file) {
        return 0;
    }
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
    fclose(file);
    return 1; /*TODO: finish WritePlt */
}

/* ---------------------------------------------------------------- */
/* format rgb */

char readRgb(EmbPattern* pattern, const char* fileName) {
    int i, numberOfColors;
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readRgb")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
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
    fclose(file);
    return 1;
}

char writeRgb(EmbPattern* pattern, const char* fileName) {
    int i;
    FILE* file = 0;

    if (!validateWritePattern(pattern, fileName, "readRgb"))
        return 0;

    file = fopen(fileName, "wb");
    if (!file)
        return 0;

    for (i = 0; i < pattern->threads->count; i++) {
        unsigned char b[4];
        EmbColor c = pattern->threads->thread[i].color;
        b[0] = c.r;
        b[1] = c.g;
        b[2] = c.b;
        b[3] = 0;
        fwrite(b, 1, 4, file);
    }
    fclose(file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format sew */

static char sewDecode(unsigned char inputByte) {
    /* TODO: fix return statement */
    return (inputByte >= 0x80) ? (char) (-~(inputByte - 1)) : (char) inputByte;
}

char readSew(EmbPattern* pattern, const char* fileName) {
    FILE* file;
    int i, flags, numberOfColors, fileLength;
    char dx, dy, thisStitchIsJump = 0;

    if (!validateReadPattern(pattern, fileName, "readSew")) {
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    fseek(file, 0x00, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x00, SEEK_SET);
    numberOfColors = fgetc(file);
    numberOfColors += (fgetc(file) << 8);

    for (i = 0; i < numberOfColors; i++) {
        embPattern_addThread(pattern, jefThreads[fread_int16(file)]);
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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

static void sewEncode(unsigned char* b, char dx, char dy, int flags) {
    if (!b) {
        printf("ERROR: format-exp.c expEncode(), b argument is null\n");
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
        b[2] = 0;
        b[3] = 0;
    }
}

char writeSew(EmbPattern* pattern, const char* fileName) {
    int colorlistSize, minColors, i, thr;
    FILE* file;
    EmbStitch st;
    EmbColor col;
    double dx = 0.0, dy = 0.0, xx = 0.0, yy = 0.0;
    unsigned char b[4];

    if (!validateWritePattern(pattern, fileName, "writeSew")) {
        return 0;
    }
    file = fopen(fileName, "wb");
    if (!file) {
        return 0;
    }
    colorlistSize = pattern->threads->count;

    minColors = embMaxInt(pattern->threads->count, 6);
    binaryWriteInt(file, 0x74 + (minColors * 4));
    binaryWriteInt(file, 0x0A);

    for (i = 0; i < pattern->threads->count; i++) {
        col = pattern->threads->thread[i].color;
        thr = embThread_findNearestColor_fromThread(col, (EmbThread *)jefThreads, 79);
        binaryWriteInt(file, thr);
    }

    for (i = 0; i < (minColors - colorlistSize); i++) {
        binaryWriteInt(file, 0x0D);
    }

    fpad(file, ' ', 7536);

    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        sewEncode(b, (char)round(dx), (char)round(dy), st.flags);
        if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
            fwrite(b, 1, 4, file);
        } else {
            fwrite(b, 1, 2, file);
        }
    }
    fclose(file);
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

char readShv(EmbPattern* pattern, const char* fileName)
{
    FILE* file = 0;
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

    if (!validateReadPattern(pattern, fileName, "readShv"))
        return 0;

    file = fopen(fileName, "rb");
    if (!file) return 0;

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
    binaryReadByte(file);
    something = fread_int32(file);
    left = fread_int16(file);
    top = fread_int16(file);
    right = fread_int16(file);
    bottom = fread_int16(file);

    something2 = binaryReadByte(file);
    numberOfSections = fgetc(file);
    something3 = binaryReadByte(file);
        
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
    fclose(file);
    embPattern_end(pattern);
    embPattern_flipVertical(pattern);

    return 1;
}

char writeShv(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeShv"))
        return 0;

    /* TODO: fopen() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writeShv */
}

/* ---------------------------------------------------------------- */
/* format sst */

char readSst(EmbPattern* pattern, const char* fileName)
{
    int fileLength;
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readSst"))
        return 0;

    file = fopen(fileName, "rb");
    if (!file)
        return 0;

    embPattern_loadExternalColorFile(pattern, fileName);
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

    fclose(file);
    embPattern_end(pattern);

    return 1; /*TODO: finish readSst */
}

char writeSst(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeSst"))
        return 0;

    /* TODO: fopen() needs to occur here after the check for no stitches */

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
    char* sectionNameBuff = 0;
    EmbColor col;
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
    binaryReadBytes(file, (unsigned char*)codeNameBuff, colorNameLength); /* TODO: check return value */
    thread->colorName = codeNameBuff;

    col.r = fgetc(file);
    col.b = fgetc(file);
    col.g = fgetc(file);

    whatIsthis = fgetc(file);

    sectionNameLength = fgetc(file);
    sectionNameBuff = (char*)malloc(sectionNameLength);
    if (!sectionNameBuff) {
        printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for sectionNameBuff\n");
        return 0;
    }
    binaryReadBytes(file, (unsigned char*)sectionNameBuff, sectionNameLength); /* TODO: check return value */
    thread->sectionName = sectionNameBuff;

    somethingSomething = fread_int32(file);
    somethingSomething2 = fread_int32(file);
    somethingElse = fread_int32(file);
    numberOfOtherDescriptors = fread_int16(file);

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
        binaryReadBytes(file, (unsigned char*)subCodeBuff, subCodeLength); /* TODO: check return value */
        sd.colorCode = subCodeBuff;
        subColorNameLength = fgetc(file);
        subColorNameBuff = (char*)malloc(subColorNameLength);
        if (!subColorNameBuff) {
            printf("ERROR: format-stx.c stxReadThread(), unable to allocate memory for subColorNameBuff\n");
            return 0;
        }
        binaryReadBytes(file, (unsigned char*)subColorNameBuff, subColorNameLength); /* TODO: check return value */
        sd.colorName = subColorNameBuff;
        sd.someOtherInt = fread_int32(file);
        thread->subDescriptors[j] = sd;
    }
    return 1;
}

char readStx(EmbPattern* pattern, const char* fileName)
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
    FILE* file = 0;

    if (!pattern) {
        printf("ERROR: format-stx.c readStx(), pattern argument is null\n");
        return 0;
    }
    if (!fileName) {
        printf("ERROR: format-stx.c readStx(), fileName argument is null\n");
        return 0;
    }
    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    binaryReadBytes(file, headerBytes, 7); /* TODO: check return value */
    header = (char*)headerBytes;

    memcpy(filetype, &header[0], 3);
    memcpy(version, &header[3], 4);
    filetype[3] = '\0';
    version[4] = '\0';
    binaryReadByte(file);
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
    binaryReadBytes(file, gif, imageLength); /* TODO: check return value */
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
        char b0 = binaryReadByte(file);
        char b1 = binaryReadByte(file);
        if (b0 == -128) {
            switch (b1) {
                case 1:
                    b0 = binaryReadByte(file);
                    b1 = binaryReadByte(file);
                    /*embPattern_addStitchRel(b0, b1, STOP); TODO: review */

                    i++;
                    break;
                case 2:
                    b0 = binaryReadByte(file);
                    b1 = binaryReadByte(file);
                    embPattern_addStitchRel(pattern, b0 / 10.0, 
                        b1 / 10.0, JUMP, 1);
                    i++;
                    break;
                case -94:
                    /* TODO: Is this a syncronize? 
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
    fclose(file);
    embPattern_end(pattern);
    embPattern_flipVertical(pattern);
    return 1;
}

char writeStx(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeStx")) {
        return 0;
    }

    /* TODO: fopen() needs to occur 
        here after the check for no stitches */

    return 0; /*TODO: finish writeStx */
}

/* ---------------------------------------------------------------- */
/* svg format */


/* ---------------------------------------------------------------- */
/* t01 format */

char readT01(EmbPattern* pattern, const char* fileName) {
    unsigned char b[3];
    FILE* file;

    if (!pattern) {
        printf("ERROR: format-t01.c readt01(), pattern argument is null\n");
        return 0;
    }
    if (!fileName) {
        printf("ERROR: format-t01.c readt01(), fileName argument is null\n");
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        puts("ERROR: cannot open file.");
        return 0;
    }

    embPattern_loadExternalColorFile(pattern, fileName);

    while (fread(b, 1, 3, file) == 3) {
        int flags, x, y;
        decode_t01_record(b, &flags, &x, &y);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        if (flags == END) {
            break;
        }
    }
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeT01(EmbPattern* pattern, const char* fileName) {
    EmbRect boundingRect;
    FILE* file;
    int xx, yy, i;

    if (!validateWritePattern(pattern, fileName, "writeT01")) {
        return 0;
    }
    file = fopen(fileName, "wb");
    if (!file) {
        puts("ERROR: failed to open file.");
        return 0;
    }
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
    fclose(file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* t09 format */

char readT09(EmbPattern* pattern, const char* fileName) {
    unsigned char b[3];
    FILE* file;

    if (!validateReadPattern(pattern, fileName, "readT09")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeT09(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeT09")) {
        return 0;
    }
    /* TODO: fopen() needs to occur here 
        after the check for no stitches */

    puts("writeT09 is not implimented.");
    return 0; /*TODO: finish writeT09 */
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

char readTap(EmbPattern* pattern, const char* fileName) {
    unsigned char b[3];
    FILE* file = 0;

    if (!pattern) {
        puts("ERROR: format-tap.c readTap(), pattern argument is null.");
        return 0;
    }
    if (!fileName) {
        puts("ERROR: format-tap.c readTap(), fileName argument is null.");
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        puts("ERROR: format-tap.c cannot open file for reading.");
        return 0;
    }

    embPattern_loadExternalColorFile(pattern, fileName);

    while (fread(b, 1, 3, file) == 3) {
        int flags, x, y;
        decode_tajima_ternary(b, &x, &y);
        flags = decode_tap_record_flags(b[2]);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
        if (flags == END) {
            break;
        }
    }
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeTap(EmbPattern* pattern, const char* fileName) {
    FILE* file;
    int xx, yy, dx, dy, i;
    if (!validateWritePattern(pattern, fileName, "writeTap")) {
        return 0;
    }

    file = fopen(fileName, "wb");
    if (!file) {
        puts("ERROR: writeTap failed to open file.");
        return 0;
    }

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
    fclose(file);
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
    char auxFormat;             /* auxillary file format, 0=PCS,1=DST,2=PES */
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

char readThr(EmbPattern* pattern, const char* fileName) {
    ThredHeader header;
    unsigned char r, g, b;
    int currentColor;
    int i;
    FILE* file = 0;

    if (!pattern) {
        printf("ERROR: format-thr.c readThr(), pattern argument is null\n");
        return 0;
    }
    if (!fileName) {
        printf("ERROR: format-thr.c readThr(), fileName argument is null\n");
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file)
        return 0;

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
                return 0; /* unsuported version */
        }
    }
    currentColor = -1;
    for (i = 0; i < header.numStiches; i++) {
        int type = NORMAL;
        float x = binaryReadFloat(file) / 10.0f;
        float y = binaryReadFloat(file) / 10.0f;
        unsigned int color = fread_uint32(file);

        if ((int)(color & 0xF) != currentColor) {
            currentColor = (int)color & 0xF;
            embPattern_changeColor(pattern, currentColor);
            type = STOP | TRIM;
        }
        embPattern_addStitchAbs(pattern, x, y, type, 0);
    }
    fseek(file, 16, SEEK_CUR); /* skip bitmap name (16 chars) */

    r = binaryReadByte(file);
    g = binaryReadByte(file);
    b = binaryReadByte(file);
    binaryReadByte(file);
    if (EMB_DEBUG) {
        printf("background: %c %c %c\n", r, g, b);
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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeThr(EmbPattern* pattern, const char* fileName) {
    int i, stitchCount;
    unsigned char version = 0;
    ThredHeader header;
    ThredExtension extension;
    char bitmapName[16];
    FILE* file = 0;

    if (!validateWritePattern(pattern, fileName, "writeThr")) {
        return 0;
    }

    stitchCount = pattern->stitchList->count;

    file = fopen(fileName, "wb");
    if (!file) {
        return 0;
    }
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

        binaryWriteFloat(file, extension.hoopX);
        binaryWriteFloat(file, extension.hoopY);
        binaryWriteFloat(file, extension.stitchGranularity);
        fwrite(extension.creatorName, 1, 50, file);
        fwrite(extension.modifierName, 1, 50, file);
        binaryWriteByte(file, extension.auxFormat);
        fwrite(extension.reserved, 1, 31, file);
    }

    /* write stitches */
    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch st = pattern->stitchList->stitch[i];
        binaryWriteFloat(file, (float)(st.x * 10.0));
        binaryWriteFloat(file, (float)(st.y * 10.0));
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
    fclose(file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format txt */

char readTxt(EmbPattern* pattern, const char* fileName) {
    if (!validateReadPattern(pattern, fileName, "readTxt")) {
        return 0;
    }
    return 0; /*TODO: finish readTxt */
}

char writeTxt(EmbPattern* pattern, const char* fileName) {
    int i;
    FILE* file = 0;
    if (!validateWritePattern(pattern, fileName, "writeTxt")) {
        return 0;
    }
    file = fopen(fileName, "w");
    if (!file) {
        return 0;
    }
    fprintf(file, "%u\n", (unsigned int) pattern->stitchList->count);

    for (i = 0; i < pattern->stitchList->count; i++) {
        EmbStitch s = pattern->stitchList->stitch[i];
        fprintf(file, "%.1f,%.1f color:%i flags:%i\n", 
                s.x, s.y, s.color, s.flags);
    }
    fclose(file);
    return 1;
}


/* ---------------------------------------------------------------- */
/* format u00 */

char readU00(EmbPattern* pattern, const char* fileName) {
    int i;
    char dx = 0, dy = 0;
    int flags = NORMAL;
    char endOfStream = 0;
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readU00")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
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
    for (i = 0; !endOfStream; i++) {
        char negativeX , negativeY;
        unsigned char b0 = fgetc(file);
        unsigned char b1 = fgetc(file);
        unsigned char b2 = fgetc(file);

        if (b0 == 0xF8 || b0 == 0x87 || b0 == 0x91) {
            break;
        }
        if ((b0 & 0x0F) == 0) {
            flags = NORMAL;
        } else if ((b0 & 0x1f) == 1) {
            flags = JUMP;
        } else if ((b0 & 0x0F) > 0) {
            flags = STOP;
        }
        negativeX = ((b0 & 0x20) > 0);
        negativeY = ((b0 & 0x40) > 0);

        dx = (char) b2;
        dy = (char) b1;
        if (negativeX) {
            dx = (char) -dx;
        }
        if (negativeY) {
            dy = (char) -dy;
        }
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeU00(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeU00")) {
        return 0;
    }
    /* TODO: fopen() needs to occur here 
        after the check for no stitches */
    return 0; /*TODO: finish WriteU00 */
}

/* ---------------------------------------------------------------- */
/* format u01 */

/* TODO: AFAIK this is a duplicate of U00. Review for differences and merge files and handle accordingly. */

char readU01(EmbPattern* pattern, const char* fileName) {
    int fileLength, negativeX = 0, negativeY = 0, flags = NORMAL;
    char dx, dy;
    unsigned char data[3];
    FILE* file = 0;

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x100, SEEK_SET);
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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

char writeU01(EmbPattern* pattern, const char* fileName) {
    if (!validateWritePattern(pattern, fileName, "writeU01")) {
        return 0;
    }
    /* TODO: fopen() needs to occur here 
        after the check for no stitches */
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
    char* decompressedData = (char*)malloc(decompressedContentLength);
    if (!decompressedData) {
        printf("ERROR: format-vip.c vipDecompressData(), cannot allocate memory for decompressedData\n");
        return 0;
    }
    hus_decompress((char*)input, compressedInputLength, decompressedData, &decompressedContentLength);
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

char readVip(EmbPattern* pattern, const char* fileName)
{
    int fileLength;
    int i;
    unsigned char prevByte = 0;
    unsigned char *attributeData = 0, *decodedColors = 0;
    unsigned char *attributeDataDecompressed = 0;
    unsigned char *xData = 0, *xDecompressed = 0, *yData = 0, *yDecompressed = 0;
    VipHeader header;
    FILE* file = 0;

    if (!validateReadPattern(pattern, fileName, "readVip")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) return 0;

    fseek(file, 0x0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0x00, SEEK_SET);
    header.magicCode = fread_int32(file);
    header.numberOfStitches = fread_int32(file);
    header.numberOfColors = fread_int32(file);

    header.postitiveXHoopSize = fread_int16(file);
    header.postitiveYHoopSize = fread_int16(file);
    header.negativeXHoopSize = fread_int16(file);
    header.negativeYHoopSize = fread_int16(file);
    header.attributeOffset = fread_int32(file);
    header.xOffset = fread_int32(file);
    header.yOffset = fread_int32(file);

    binaryReadBytes(file, header.stringVal, 8); /* TODO: check return value */

    header.unknown = fread_int16(file);

    header.colorLength = fread_int32(file);
    decodedColors = (unsigned char*)malloc(header.numberOfColors*4);
    if (!decodedColors) {
        printf("ERROR: format-vip.c readVip(), ");
        printf("cannot allocate memory for decodedColors\n");
        return 0;
    }
    for (i = 0; i < header.numberOfColors*4; ++i) {
        unsigned char inputByte = binaryReadByte(file);
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
    binaryReadBytes(file, attributeData, header.xOffset - header.attributeOffset); /* TODO: check return value */
    attributeDataDecompressed = vipDecompressData(attributeData, header.xOffset - header.attributeOffset, header.numberOfStitches);

    fseek(file, header.xOffset, SEEK_SET);
    xData = (unsigned char*)malloc(header.yOffset - header.xOffset);
    if (!xData) { 
        printf("ERROR: format-vip.c readVip(), cannot allocate memory for xData\n");
        return 0;
    }
    binaryReadBytes(file, xData, header.yOffset - header.xOffset); /* TODO: check return value */
    xDecompressed = vipDecompressData(xData, header.yOffset - header.xOffset, header.numberOfStitches);

    fseek(file, header.yOffset, SEEK_SET);
    yData = (unsigned char*)malloc(fileLength - header.yOffset);
    if (!yData) { printf("ERROR: format-vip.c readVip(), cannot allocate memory for yData\n"); return 0; }
    binaryReadBytes(file, yData, fileLength - header.yOffset); /* TODO: check return value */
    yDecompressed = vipDecompressData(yData, fileLength - header.yOffset, header.numberOfStitches);

    for (i = 0; i < header.numberOfStitches; i++) {
        embPattern_addStitchRel(pattern,
                    vipDecodeByte(xDecompressed[i]) / 10.0,
                    vipDecodeByte(yDecompressed[i]) / 10.0,
                    vipDecodeStitchType(attributeDataDecompressed[i]), 1);
    }
    embPattern_addStitchRel(pattern, 0, 0, END, 1);

    fclose(file);

    free(attributeData);
    free(xData);
    free(yData);
    free(attributeDataDecompressed);
    free(xDecompressed);
    free(yDecompressed);
    return 1;
}

static unsigned char* vipCompressData(unsigned char* input, int decompressedInputSize, int* compressedSize) {
    char* compressedData = (char*)malloc(decompressedInputSize*2);
    if (!compressedData) {
        printf("ERROR: format-vip.c vipCompressData(), cannot allocate memory for compressedData\n");
        return 0;
    }
    hus_compress((char*)input, decompressedInputSize, compressedData, compressedSize);
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

char writeVip(EmbPattern* pattern, const char* fileName) {
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
    FILE* file = 0;

    if (!validateWritePattern(pattern, fileName, "writeVip")) {
        return 0;
    }
    file = fopen(fileName, "wb");
    if (!file) {
        return 0;
    }
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
            binaryWriteByte(file, prevByte);
        }
        for (i = 0; i <= minColors; i++) {
            binaryWriteInt(file, 1);
        }
        binaryWriteUInt(file, 0); /* string length */
        binaryWriteShort(file, 0);
        binaryWriteBytes(file, (char*) attributeCompressed, attributeSize);
        binaryWriteBytes(file, (char*) xCompressed, xCompressedSize);
        binaryWriteBytes(file, (char*) yCompressed, yCompressedSize);
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
    fclose(file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format vp3 */



static unsigned char* vp3ReadString(FILE* file)
{
    int stringLength = 0;
    unsigned char* charString = 0;
    if (!file) { printf("ERROR: format-vp3.c vp3ReadString(), file argument is null\n"); return 0; }
    stringLength = fread_int16_be(file);
    charString = (unsigned char*)malloc(stringLength);
    if (!charString) { printf("ERROR: format-vp3.c vp3ReadString(), cannot allocate memory for charString\n"); return 0; }
    binaryReadBytes(file, charString, stringLength); /* TODO: check return value */
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
    hoop.unknown2 = binaryReadByte(file);
    hoop.numberOfColors = binaryReadByte(file);
    hoop.unknown3 = fread_int16_be(file);
    hoop.unknown4 = fread_int32_be(file);
    hoop.numberOfBytesRemaining = fread_int32_be(file);

    hoop.xOffset = fread_int32_be(file);
    hoop.yOffset = fread_int32_be(file);

    hoop.byte1 = binaryReadByte(file);
    hoop.byte2 = binaryReadByte(file);
    hoop.byte3 = binaryReadByte(file);

    /* Centered hoop dimensions */
    hoop.right2 = fread_int32_be(file);
    hoop.left2 = fread_int32_be(file);
    hoop.bottom2 = fread_int32_be(file);
    hoop.top2 = fread_int32_be(file);

    hoop.width = fread_int32_be(file);
    hoop.height = fread_int32_be(file);
    return hoop;
}

char readVp3(EmbPattern* pattern, const char* fileName) {
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

    FILE* file = 0;
    if (!validateReadPattern(pattern, fileName, "readVp3")) { 
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    binaryReadBytes(file, magicString, 5); /* %vsm% */ /* TODO: check return value */
    some = binaryReadByte(file); /* 0 */
    softwareVendorString = vp3ReadString(file);
    someShort = fread_int16(file);
    someByte = binaryReadByte(file);
    bytesRemainingInFile = fread_int32(file);
    fileCommentString = vp3ReadString(file);
    hoopConfigurationOffset = (int)ftell(file);

    vp3ReadHoopSection(file);

    anotherCommentString = vp3ReadString(file);

    /* TODO: review v1 thru v18 variables and use emb_unused() if needed */
    for (i = 0; i < 18; i++) {
        unsigned char v1;
        v1 = binaryReadByte(file);
    }

    binaryReadBytes(file, magicCode, 6); /* 0x78 0x78 0x55 0x55 0x01 0x00 */ /* TODO: check return value */

    anotherSoftwareVendorString = vp3ReadString(file);

    numberOfColors = fread_int16_be(file);
    printf("ERROR: format-vp3.c Number of Colors: %d\n", numberOfColors);
    colorSectionOffset = (int)ftell(file);

    for (i = 0; i < numberOfColors; i++) {
        EmbThread t;
        char tableSize;
        int startX, startY, offsetToNextColorX, offsetToNextColorY;
        unsigned char* threadColorNumber, *colorName, *threadVendor;
        int unknownThreadString, numberOfBytesInColor;

        strcpy(t.catalogNumber, "");
        strcpy(t.description, "");
        fseek(file, colorSectionOffset, SEEK_SET);
        printf("ERROR: format-vp3.c Color Check Byte #1: 0 == %d\n", binaryReadByte(file));
        printf("ERROR: format-vp3.c Color Check Byte #2: 5 == %d\n", binaryReadByte(file));
        printf("ERROR: format-vp3.c Color Check Byte #3: 0 == %d\n", binaryReadByte(file));
        colorSectionOffset = fread_int32_be(file);
        colorSectionOffset += ftell(file);
        startX = fread_int32_be(file);
        startY = fread_int32_be(file);
        embPattern_addStitchAbs(pattern, startX / 1000.0, -startY / 1000.0, JUMP, 1);

        tableSize = binaryReadByte(file);
        binaryReadByte(file);
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
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
        while (ftell(file) < colorSectionOffset - 1) {
            int lastFilePosition = ftell(file);
            int x = vp3Decode(binaryReadByte(file));
            int y = vp3Decode(binaryReadByte(file));
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
    fclose(file);
    embPattern_end(pattern);
    embPattern_flipVertical(pattern);
    return 1;
}

void vp3WriteStringLen(FILE* file, const char* str, int len) {
    binaryWriteUShortBE(file, len);
    binaryWriteBytes(file, str, len);
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

char writeVp3(EmbPattern* pattern, const char* fileName) {
#if 0
    EmbFile *file = 0;
    EmbRect bounds;
    int remainingBytesPos, remainingBytesPos2;
    int colorSectionStitchBytes;
    int first = 1;
    int numberOfColors = 0;
    EmbColor color = embColor_make(0xFE, 0xFE, 0xFE);
    EmbStitchList *mainPointer = 0, *pointer = 0;

    if (!validateWritePattern(pattern, fileName, "writeVp3")) {
        return 0;
    }

    bounds = embPattern_calcBoundingBox(pattern);

    file = fopen(fileName, "wb");
    if (!file) return 0;

    embPattern_correctForMaxStitchLength(pattern, 3200.0, 3200.0); /* VP3 can encode signed 16bit deltas */

    embPattern_flipVertical(pattern);

    binaryWriteBytes(file, "%vsm%", 5);
    binaryWriteByte(file, 0);
    vp3WriteString(file, "Embroidermodder");
    binaryWriteByte(file, 0);
    binaryWriteByte(file, 2);
    binaryWriteByte(file, 0);

    remainingBytesPos = ftell(file);
    binaryWriteInt(file, 0); /* placeholder */
    vp3WriteString(file, "");
    binaryWriteIntBE(file, bounds.right * 1000);
    binaryWriteIntBE(file, bounds.bottom * 1000);
    binaryWriteIntBE(file, bounds.left * 1000);
    binaryWriteIntBE(file, bounds.top * 1000);
    binaryWriteInt(file, 0); /* this would be some (unknown) function of thread length */
    binaryWriteByte(file, 0);

    numberOfColors = 0;

    mainPointer = pattern->stitchList;
    while(mainPointer)
    {
        int flag;
        EmbColor newColor;

        pointer = mainPointer;
        flag = pointer->stitch.flags;
        newColor = pattern->threads->thread[pointer->stitch.color].color;
        if (newColor.r != color.r || newColor.g != color.g || newColor.b != color.b)
        {
            numberOfColors++;
            color.r = newColor.r;
            color.g = newColor.g;
            color.b = newColor.b;
        }
        else if (flag & END || flag & STOP)
        {
            numberOfColors++;
        }

        while(pointer && (flag == pointer->stitch.flags))
        {
            pointer = pointer->next;
        }
        mainPointer = pointer;
    }

    binaryWriteByte(file, numberOfColors);
    binaryWriteByte(file, 12);
    binaryWriteByte(file, 0);
    binaryWriteByte(file, 1);
    binaryWriteByte(file, 0);
    binaryWriteByte(file, 3);
    binaryWriteByte(file, 0);

    remainingBytesPos2 = ftell(file);
    binaryWriteInt(file, 0); /* placeholder */

    binaryWriteIntBE(file, 0); /* origin X */
    binaryWriteIntBE(file, 0); /* origin Y */
    binaryWriteByte(file, 0);
    binaryWriteByte(file, 0);
    binaryWriteByte(file, 0);

    binaryWriteIntBE(file, bounds.right * 1000);
    binaryWriteIntBE(file, bounds.bottom * 1000);
    binaryWriteIntBE(file, bounds.left * 1000);
    binaryWriteIntBE(file, bounds.top * 1000);

    binaryWriteIntBE(file, (bounds.right - bounds.left) * 1000);
    binaryWriteIntBE(file, (bounds.bottom - bounds.top) * 1000);

    vp3WriteString(file, "");
    binaryWriteShortBE(file, 25700);
    binaryWriteIntBE(file, 4096);
    binaryWriteIntBE(file, 0);
    binaryWriteIntBE(file, 0);
    binaryWriteIntBE(file, 4096);

    binaryWriteBytes(file, "xxPP\x01\0", 6);
    vp3WriteString(file, "");
    binaryWriteShortBE(file, numberOfColors);

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
            binaryWriteByte(file, 0);
        }
        binaryWriteByte(file, 0);
        binaryWriteByte(file, 5);
        binaryWriteByte(file, 0);

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

        binaryWriteByte(file, 1);
        binaryWriteByte(file, 0);

        printf("format-vp3.c writeVp3(), switching to color (%d, %d, %d)\n", color.r, color.g, color.b);
        binaryWriteByte(file, color.r);
        binaryWriteByte(file, color.g);
        binaryWriteByte(file, color.b);

        binaryWriteByte(file, 0);
        binaryWriteByte(file, 0);
        binaryWriteByte(file, 0);
        binaryWriteByte(file, 5);
        binaryWriteByte(file, 40);

        vp3WriteString(file, "");

        sprintf(colorName, "#%02x%02x%02x", color.b, color.g, color.r);

        vp3WriteString(file, colorName);
        vp3WriteString(file, "");

        binaryWriteIntBE(file, 0);
        binaryWriteIntBE(file, 0);

        vp3WriteStringLen(file, "\0", 1);

        colorSectionStitchBytes = ftell(file);
        binaryWriteInt(file, 0); /* placeholder */

        binaryWriteByte(file, 10);
        binaryWriteByte(file, 246);
        binaryWriteByte(file, 0);

        while(pointer)
        {
            int dx, dy;

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
                binaryWriteByte(file, 128);
                binaryWriteByte(file, 1);
                binaryWriteShortBE(file, dx);
                binaryWriteShortBE(file, dy);
                binaryWriteByte(file, 128);
                binaryWriteByte(file, 2);
            }
            else
            {
                binaryWriteByte(file, dx);
                binaryWriteByte(file, dy);
            }

            pointer = pointer->next;
        }

        vp3PatchByteCount(file, colorSectionStitchBytes, -4);
        vp3PatchByteCount(file, colorSectionLengthPos, -3);

        mainPointer = pointer;
    }

    vp3PatchByteCount(file, remainingBytesPos2, -4);
    vp3PatchByteCount(file, remainingBytesPos, -4);

    fclose(file);

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

char readXxx(EmbPattern* pattern, const char* fileName) {
    FILE* file = 0;
    int dx = 0, dy = 0, numberOfColors, paletteOffset, i;
    char endOfStream = 0;
    char thisStitchJump = 0;

    if (!validateReadPattern(pattern, fileName, "readXxx")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }

    fseek(file, 0x27, SEEK_SET);
    numberOfColors = fread_int16(file);
    fseek(file, 0xFC, SEEK_SET);
    paletteOffset = fread_int32(file);
    fseek(file, paletteOffset + 6, SEEK_SET);

    for (i = 0; i < numberOfColors; i++) {
        EmbThread thread;
        strcpy(thread.catalogNumber, "NULL");
        strcpy(thread.description, "NULL");
        binaryReadByte(file);
        thread.color.r = binaryReadByte(file);
        thread.color.g = binaryReadByte(file);
        thread.color.b = binaryReadByte(file);
        embPattern_addThread(pattern, thread);
    }
    fseek(file, 0x100, SEEK_SET);

    for (i = 0; !endOfStream && ftell(file) < paletteOffset; i++) {
        unsigned char b0, b1;
        int flags;
        flags = NORMAL;
        if (thisStitchJump) flags = TRIM;
        thisStitchJump = 0;
        b0 = binaryReadByte(file);
        b1 = binaryReadByte(file);
        /* TODO: ARE THERE OTHER BIG JUMP CODES? */
        if (b0 == 0x7E || b0 == 0x7D) {
            dx = b1 + (binaryReadByte(file) << 8);
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
                b0 = binaryReadByte(file);
                b1 = binaryReadByte(file);
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
    fclose(file);
    embPattern_end(pattern);
    return 1;
}

static void xxxEncodeStop(FILE* file, EmbStitch s) {
    binaryWriteByte(file, (unsigned char)0x7F);
    binaryWriteByte(file, (unsigned char)(s.color + 8));
}

static void xxxEncodeStitch(FILE* file, 
        double deltaX, double deltaY, int flags) {
    if ((flags & (JUMP | TRIM)) && (fabs(deltaX) > 124 || fabs(deltaY) > 124)) {
        binaryWriteByte(file, 0x7E);
        binaryWriteShort(file, (short)deltaX);
        binaryWriteShort(file, (short)deltaY);
    } else {
        /* TODO: Verify this works after changing this to unsigned char */
        binaryWriteByte(file, (unsigned char)round(deltaX));
        binaryWriteByte(file, (unsigned char)round(deltaY));
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

char writeXxx(EmbPattern* pattern, const char* fileName) {
    FILE* file = 0;
    int i;
    EmbRect rect;
    int endOfStitches;
    int curColor = 0;

    if (!validateWritePattern(pattern, fileName, "writeXxx")) {
        return 0;
    }

    file = fopen(fileName, "wb");
    if (!file) return 0;

    embPattern_correctForMaxStitchLength(pattern, 124, 127);

    for (i = 0; i < 0x17; i++) {
        binaryWriteByte(file, 0x00);
    }
    binaryWriteUInt(file, (unsigned int)pattern->stitchList->count);
    for (i = 0; i < 0x0C; i++) {
        binaryWriteByte(file, 0x00);
    }
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
    for (i = 0; i < 0xC5; i++) {
        binaryWriteByte(file, 0x00);
    }
    binaryWriteInt(file, 0x0000); /* place holder for end of stitches */
    xxxEncodeDesign(file, pattern);
    endOfStitches = ftell(file);
    fseek(file, 0xFC, SEEK_SET);
    binaryWriteUInt(file, endOfStitches);
    fseek(file, 0, SEEK_END);
    binaryWriteByte(file, 0x7F); /* is this really correct? */
    binaryWriteByte(file, 0x7F);
    binaryWriteByte(file, 0x03);
    binaryWriteByte(file, 0x14);
    binaryWriteByte(file, 0x00);
    binaryWriteByte(file, 0x00);

    for (i = 0; i < pattern->threads->count; i++) {
        binaryWriteByte(file, 0x00);
        binaryWriteByte(file, pattern->threads->thread[i].color.r);
        binaryWriteByte(file, pattern->threads->thread[i].color.g);
        binaryWriteByte(file, pattern->threads->thread[i].color.b);
        curColor++;
    }
    for (i = 0; i < (22 - curColor); i++) {
        binaryWriteUInt(file, 0x01000000);
    }
    binaryWriteByte(file, 0x00);
    binaryWriteByte(file, 0x01);
    fclose(file);
    return 1;
}

/* ---------------------------------------------------------------- */
/* format zsk */

char readZsk(EmbPattern* pattern, const char* fileName) {
    char b[3];
    FILE* file = 0;
    int stitchType;
    unsigned char colorNumber;
    if (!validateReadPattern(pattern, fileName, "readZsk")) {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (!file) {
        return 0;
    }
    fseek(file, 0x230, SEEK_SET);
    colorNumber = fgetc(file);
    while (colorNumber != 0) {
        EmbThread t;
        t.color.r = fgetc(file);
        t.color.g = fgetc(file);
        t.color.b = fgetc(file);
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
    fclose(file);
    embPattern_end(pattern);

    return 1;
}

char writeZsk(EmbPattern* pattern, const char* fileName) {
    FILE *file;
    if (!validateWritePattern(pattern, fileName, "writeZsk")) {
        return 0;
    }

    file = fopen(fileName, "wb");
    if (!file) {
        return 0;
    }

    fclose(file);

    return 0; /*TODO: finish writeZsk */
}

/* ---------------------------------------------------------------- */

