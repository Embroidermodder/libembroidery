/**
 * @file file.c
 */

#include <string.h>

#include "embroidery.h"

/* WARNING: Not unicode safe. */
uint8_t char_to_lower(uint8_t a);

/*
 * Formats
 */

int8_t read100(EmbPattern * pattern, FILE * file);
int8_t write100(EmbPattern * pattern, FILE * file);
int8_t read10o(EmbPattern * pattern, FILE * file);
int8_t write10o(EmbPattern * pattern, FILE * file);
int8_t readArt(EmbPattern * pattern, FILE * file);
int8_t writeArt(EmbPattern * pattern, FILE * file);
int8_t readBmc(EmbPattern * pattern, FILE * file);
int8_t writeBmc(EmbPattern * pattern, FILE * file);
int8_t readBro(EmbPattern * pattern, FILE * file);
int8_t writeBro(EmbPattern * pattern, FILE * file);
int8_t readCnd(EmbPattern * pattern, FILE * file);
int8_t writeCnd(EmbPattern * pattern, FILE * file);
int8_t readCol(EmbPattern * pattern, FILE * file);
int8_t writeCol(EmbPattern * pattern, FILE * file);
int8_t readCsd(EmbPattern * pattern, FILE * file);
int8_t writeCsd(EmbPattern * pattern, FILE * file);
int8_t readCsv(EmbPattern * pattern, FILE * file);
int8_t writeCsv(EmbPattern * pattern, FILE * file);
int8_t readDat(EmbPattern * pattern, FILE * file);
int8_t writeDat(EmbPattern * pattern, FILE * file);
int8_t readDem(EmbPattern * pattern, FILE * file);
int8_t writeDem(EmbPattern * pattern, FILE * file);
int8_t readDsb(EmbPattern * pattern, FILE * file);
int8_t writeDsb(EmbPattern * pattern, FILE * file);
int8_t readDst(EmbPattern * pattern, FILE * file);
int8_t writeDst(EmbPattern * pattern, FILE * file);
int8_t readDsz(EmbPattern * pattern, FILE * file);
int8_t writeDsz(EmbPattern * pattern, FILE * file);
int8_t readDxf(EmbPattern * pattern, FILE * file);
int8_t writeDxf(EmbPattern * pattern, FILE * file);
int8_t readEdr(EmbPattern * pattern, FILE * file);
int8_t writeEdr(EmbPattern * pattern, FILE * file);
int8_t readEmd(EmbPattern * pattern, FILE * file);
int8_t writeEmd(EmbPattern * pattern, FILE * file);
int8_t readExp(EmbPattern * pattern, FILE * file);
int8_t writeExp(EmbPattern * pattern, FILE * file);
int8_t readExy(EmbPattern * pattern, FILE * file);
int8_t writeExy(EmbPattern * pattern, FILE * file);
int8_t readEys(EmbPattern * pattern, FILE * file);
int8_t writeEys(EmbPattern * pattern, FILE * file);
int8_t readFxy(EmbPattern * pattern, FILE * file);
int8_t writeFxy(EmbPattern * pattern, FILE * file);
int8_t readGc(EmbPattern * pattern, FILE * file);
int8_t writeGc(EmbPattern * pattern, FILE * file);
int8_t readGnc(EmbPattern * pattern, FILE * file);
int8_t writeGnc(EmbPattern * pattern, FILE * file);
int8_t readGt(EmbPattern * pattern, FILE * file);
int8_t writeGt(EmbPattern * pattern, FILE * file);
int8_t readHus(EmbPattern * pattern, FILE * file);
int8_t writeHus(EmbPattern * pattern, FILE * file);
int8_t readInb(EmbPattern * pattern, FILE * file);
int8_t writeInb(EmbPattern * pattern, FILE * file);
int8_t readInf(EmbPattern * pattern, FILE * file);
int8_t writeInf(EmbPattern * pattern, FILE * file);
int8_t readJef(EmbPattern * pattern, FILE * file);
int8_t writeJef(EmbPattern * pattern, FILE * file);
int8_t readKsm(EmbPattern * pattern, FILE * file);
int8_t writeKsm(EmbPattern * pattern, FILE * file);
int8_t readMax(EmbPattern * pattern, FILE * file);
int8_t writeMax(EmbPattern * pattern, FILE * file);
int8_t readMit(EmbPattern * pattern, FILE * file);
int8_t writeMit(EmbPattern * pattern, FILE * file);
int8_t readNew(EmbPattern * pattern, FILE * file);
int8_t writeNew(EmbPattern * pattern, FILE * file);
int8_t readOfm(EmbPattern * pattern, FILE * file);
int8_t writeOfm(EmbPattern * pattern, FILE * file);
int8_t readPcd(EmbPattern * pattern, const int8_t *fileName, FILE * file);
int8_t writePcd(EmbPattern * pattern, FILE * file);
int8_t readPcm(EmbPattern * pattern, FILE * file);
int8_t writePcm(EmbPattern * pattern, FILE * file);
int8_t readPcq(EmbPattern * pattern, const int8_t *fileName, FILE * file);
int8_t writePcq(EmbPattern * pattern, FILE * file);
int8_t readPcs(EmbPattern * pattern, const int8_t *fileName, FILE * file);
int8_t writePcs(EmbPattern * pattern, FILE * file);
int8_t readPec(EmbPattern * pattern, const int8_t *fileName, FILE * file);
int8_t writePec(EmbPattern * pattern, const int8_t *fileName, FILE * file);
int8_t readPel(EmbPattern * pattern, FILE * file);
int8_t writePel(EmbPattern * pattern, FILE * file);
int8_t readPem(EmbPattern * pattern, FILE * file);
int8_t writePem(EmbPattern * pattern, FILE * file);
int8_t readPes(EmbPattern * pattern, const int8_t *fileName, FILE * file);
int8_t writePes(EmbPattern * pattern, const int8_t *fileName, FILE * file);
int8_t readPhb(EmbPattern * pattern, FILE * file);
int8_t writePhb(EmbPattern * pattern, FILE * file);
int8_t readPhc(EmbPattern * pattern, FILE * file);
int8_t writePhc(EmbPattern * pattern, FILE * file);
int8_t readPlt(EmbPattern * pattern, FILE * file);
int8_t writePlt(EmbPattern * pattern, FILE * file);
int8_t readRgb(EmbPattern * pattern, FILE * file);
int8_t writeRgb(EmbPattern * pattern, FILE * file);
int8_t readSew(EmbPattern * pattern, FILE * file);
int8_t writeSew(EmbPattern * pattern, FILE * file);
int8_t readShv(EmbPattern * pattern, FILE * file);
int8_t writeShv(EmbPattern * pattern, FILE * file);
int8_t readSst(EmbPattern * pattern, FILE * file);
int8_t writeSst(EmbPattern * pattern, FILE * file);
int8_t readStx(EmbPattern * pattern, FILE * file);
int8_t writeStx(EmbPattern * pattern, FILE * file);
int8_t readSvg(EmbPattern * pattern, FILE * file);
int8_t writeSvg(EmbPattern * pattern, FILE * file);
int8_t readT01(EmbPattern * pattern, FILE * file);
int8_t writeT01(EmbPattern * pattern, FILE * file);
int8_t readT09(EmbPattern * pattern, FILE * file);
int8_t writeT09(EmbPattern * pattern, FILE * file);
int8_t readTap(EmbPattern * pattern, FILE * file);
int8_t writeTap(EmbPattern * pattern, FILE * file);
int8_t readThr(EmbPattern * pattern, FILE * file);
int8_t writeThr(EmbPattern * pattern, FILE * file);
int8_t readTxt(EmbPattern * pattern, FILE * file);
int8_t writeTxt(EmbPattern * pattern, FILE * file);
int8_t readU00(EmbPattern * pattern, FILE * file);
int8_t writeU00(EmbPattern * pattern, FILE * file);
int8_t readU01(EmbPattern * pattern, FILE * file);
int8_t writeU01(EmbPattern * pattern, FILE * file);
int8_t readVip(EmbPattern * pattern, FILE * file);
int8_t writeVip(EmbPattern * pattern, FILE * file);
int8_t readVp3(EmbPattern * pattern, FILE * file);
int8_t writeVp3(EmbPattern * pattern, FILE * file);
int8_t readXxx(EmbPattern * pattern, FILE * file);
int8_t writeXxx(EmbPattern * pattern, FILE * file);
int8_t readZsk(EmbPattern * pattern, FILE * file);
int8_t writeZsk(EmbPattern * pattern, FILE * file);

int read_descriptions(FILE * file, EmbPattern * pattern);
void readHoopName(FILE * file, EmbPattern * pattern);
void readImageString(FILE * file, EmbPattern * pattern);
void readProgrammableFills(FILE * file, EmbPattern * pattern);
void readMotifPatterns(FILE * file, EmbPattern * pattern);
void readFeatherPatterns(FILE * file, EmbPattern * pattern);
void readThreads(FILE * file, EmbPattern * pattern);

void readPESHeaderV5(FILE * file, EmbPattern * pattern);
void readPESHeaderV6(FILE * file, EmbPattern * pattern);
void readPESHeaderV7(FILE * file, EmbPattern * pattern);
void readPESHeaderV8(FILE * file, EmbPattern * pattern);
void readPESHeaderV9(FILE * file, EmbPattern * pattern);
void readPESHeaderV10(FILE * file, EmbPattern * pattern);

/* Get extension from file name. */
int emb_fname_extension(const int8_t *fileName, int8_t ending[5])
{
        int i;

        if (!fileName) {
                puts("ERROR: emb_fname_extension(), fileName argument is null.\n");
                return 0;
        }

        if (fileName[0] == 0) {
                puts("ERROR: emb_fname_extension(), fileName argument is an empty string.\n");
                return 0;
        }

        int offset = string_rchar(fileName, '.');
        if (offset == 0) {
                puts("ERROR: emb_fname_extension(), filename has no stub.\n");
                return 0;
        }

        i = 0;
        while (fileName[offset + i]) {
                ending[i] = char_to_lower(fileName[offset + i]);
                i++;
        }
        ending[i] = 0;          /* terminate the string */
        return 1;
}

/* Identify format from the file name. */
int emb_identify_format(const int8_t *fileName)
{
        int i;
        int8_t ending[5];
        if (!emb_fname_extension(fileName, ending)) {
                puts("Failed to isolate the extension of the supplied fileName.");
                return -1;
        }
        for (i = 0; i < numberOfFormats; i++) {
                if (!strncmp(ending, formatTable[i].extension, 10)) {
                        return i;
                }
        }
        return -1;
}

/* . */
int8_t read_n_bytes(FILE *file, uint8_t *data, uint32_t length)
{
        if (fread(data, 1, length, file) != length) {
                printf("ERROR: failed to read %d bytes from file.", length);
                return 0;
        }
        return 1;
}

/* . */
int8_t embp_read(EmbPattern *pattern, const int8_t *fileName, int format)
{
        int result;
        FILE *file;
        result = 0;
        if (!pattern) {
                printf("ERROR: embp_read(), pattern argument is null.\n");
                return 0;
        }
        if (!fileName) {
                printf("ERROR: embp_read(), fileName argument is null.\n");
                return 0;
        }
        file = fopen(fileName, "rb");
        if (!file) {
                if ((format != EMB_FORMAT_EDR) &&
                    (format != EMB_FORMAT_RGB) &&
                    (format != EMB_FORMAT_COL) && (format != EMB_FORMAT_INF)) {
                        printf("ERROR: Failed to open file with name: %s.\n",
                               fileName);
                }
                return 0;
        }
        if (formatTable[format].check_for_color_file) {
                embp_loadExternalColorFile(pattern, fileName);
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
                result = readPel(pattern, file);
                break;
        case EMB_FORMAT_PEM:
                result = readPem(pattern, file);
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
                embp_end(pattern);
        }
        return result;
}

/* . */
int8_t embp_write(EmbPattern *pattern, const int8_t *fileName, int format)
{
        FILE *file;
        int result = 0;
        if (!pattern) {
                printf("ERROR: embp_write(), pattern argument is null\n");
                return 0;
        }
        if (!fileName) {
                printf("ERROR: embp_write(), fileName argument is null\n");
                return 0;
        }
        if (pattern->stitch_list->count == 0) {
                printf("ERROR: embp_write(), pattern contains no stitches\n");
                return 0;
        }
        if (!formatTable[format].color_only) {
                embp_end(pattern);
        }

        file = fopen(fileName, "wb");
        if (!file) {
                printf("Failed to open file with name: %s.", fileName);
                return 0;
        }
        switch (format) {
        case EMB_FORMAT_100:
                result = write100(pattern, file);
                break;
        case EMB_FORMAT_10O:
                result = write10o(pattern, file);
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
                result = writePel(pattern, file);
                break;
        case EMB_FORMAT_PEM:
                result = writePem(pattern, file);
                break;
        case EMB_FORMAT_PES:
                result = writePes(pattern, fileName, file);
                break;
        case EMB_FORMAT_PHB:
                result = writePhb(pattern, file);
                break;
        case EMB_FORMAT_PHC:
                result = writePhc(pattern, file);
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
                result = writeShv(pattern, file);
                break;
        case EMB_FORMAT_SST:
                result = writeSst(pattern, file);
                break;
        case EMB_FORMAT_STX:
                result = writeStx(pattern, file);
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
                result = writeU00(pattern, file);
                break;
        case EMB_FORMAT_U01:
                result = writeU01(pattern, file);
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
                int8_t externalFileName[1000];
                int stub_length;
                strncpy(externalFileName, fileName, 200);
                stub_length =
                    strlen(fileName) - strlen(formatTable[format].extension);
                externalFileName[stub_length] = 0;
                strcat(externalFileName, ".rgb");
                embp_write(pattern, externalFileName, EMB_FORMAT_RGB);
        }
        fclose(file);
        return result;
}

/* . */
int8_t embp_read_auto(EmbPattern *pattern, const int8_t *fileName)
{
        int format = emb_identify_format(fileName);
        if (format < 0) {
                printf("ERROR: convert(), unsupported read file type: %s\n",
                       fileName);
                return 0;
        }
        return embp_read(pattern, fileName, format);
}

/* . */
int8_t embp_write_auto(EmbPattern *pattern, const int8_t *fileName)
{
        int format = emb_identify_format(fileName);
        printf("embp_write_auto %d %s\n", format, fileName);
        if (format < 0) {
                printf("ERROR: convert(), unsupported write file type: %s\n",
                       fileName);
                return 0;
        }
        return embp_write(pattern, fileName, format);
}
