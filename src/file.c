#include <string.h>

#include "embroidery.h"

/* WARNING: Not unicode safe. */
unsigned char char_to_lower(unsigned char a);

/*
 * Formats
 */

char read100(EmbPattern * pattern, FILE * file);
char write100(EmbPattern * pattern, FILE * file);
char read10o(EmbPattern * pattern, FILE * file);
char write10o(EmbPattern * pattern, FILE * file);
char readArt(EmbPattern * pattern, FILE * file);
char writeArt(EmbPattern * pattern, FILE * file);
char readBmc(EmbPattern * pattern, FILE * file);
char writeBmc(EmbPattern * pattern, FILE * file);
char readBro(EmbPattern * pattern, FILE * file);
char writeBro(EmbPattern * pattern, FILE * file);
char readCnd(EmbPattern * pattern, FILE * file);
char writeCnd(EmbPattern * pattern, FILE * file);
char readCol(EmbPattern * pattern, FILE * file);
char writeCol(EmbPattern * pattern, FILE * file);
char readCsd(EmbPattern * pattern, FILE * file);
char writeCsd(EmbPattern * pattern, FILE * file);
char readCsv(EmbPattern * pattern, FILE * file);
char writeCsv(EmbPattern * pattern, FILE * file);
char readDat(EmbPattern * pattern, FILE * file);
char writeDat(EmbPattern * pattern, FILE * file);
char readDem(EmbPattern * pattern, FILE * file);
char writeDem(EmbPattern * pattern, FILE * file);
char readDsb(EmbPattern * pattern, FILE * file);
char writeDsb(EmbPattern * pattern, FILE * file);
char readDst(EmbPattern * pattern, FILE * file);
char writeDst(EmbPattern * pattern, FILE * file);
char readDsz(EmbPattern * pattern, FILE * file);
char writeDsz(EmbPattern * pattern, FILE * file);
char readDxf(EmbPattern * pattern, FILE * file);
char writeDxf(EmbPattern * pattern, FILE * file);
char readEdr(EmbPattern * pattern, FILE * file);
char writeEdr(EmbPattern * pattern, FILE * file);
char readEmd(EmbPattern * pattern, FILE * file);
char writeEmd(EmbPattern * pattern, FILE * file);
char readExp(EmbPattern * pattern, FILE * file);
char writeExp(EmbPattern * pattern, FILE * file);
char readExy(EmbPattern * pattern, FILE * file);
char writeExy(EmbPattern * pattern, FILE * file);
char readEys(EmbPattern * pattern, FILE * file);
char writeEys(EmbPattern * pattern, FILE * file);
char readFxy(EmbPattern * pattern, FILE * file);
char writeFxy(EmbPattern * pattern, FILE * file);
char readGc(EmbPattern * pattern, FILE * file);
char writeGc(EmbPattern * pattern, FILE * file);
char readGnc(EmbPattern * pattern, FILE * file);
char writeGnc(EmbPattern * pattern, FILE * file);
char readGt(EmbPattern * pattern, FILE * file);
char writeGt(EmbPattern * pattern, FILE * file);
char readHus(EmbPattern * pattern, FILE * file);
char writeHus(EmbPattern * pattern, FILE * file);
char readInb(EmbPattern * pattern, FILE * file);
char writeInb(EmbPattern * pattern, FILE * file);
char readInf(EmbPattern * pattern, FILE * file);
char writeInf(EmbPattern * pattern, FILE * file);
char readJef(EmbPattern * pattern, FILE * file);
char writeJef(EmbPattern * pattern, FILE * file);
char readKsm(EmbPattern * pattern, FILE * file);
char writeKsm(EmbPattern * pattern, FILE * file);
char readMax(EmbPattern * pattern, FILE * file);
char writeMax(EmbPattern * pattern, FILE * file);
char readMit(EmbPattern * pattern, FILE * file);
char writeMit(EmbPattern * pattern, FILE * file);
char readNew(EmbPattern * pattern, FILE * file);
char writeNew(EmbPattern * pattern, FILE * file);
char readOfm(EmbPattern * pattern, FILE * file);
char writeOfm(EmbPattern * pattern, FILE * file);
char readPcd(EmbPattern * pattern, const char *fileName, FILE * file);
char writePcd(EmbPattern * pattern, FILE * file);
char readPcm(EmbPattern * pattern, FILE * file);
char writePcm(EmbPattern * pattern, FILE * file);
char readPcq(EmbPattern * pattern, const char *fileName, FILE * file);
char writePcq(EmbPattern * pattern, FILE * file);
char readPcs(EmbPattern * pattern, const char *fileName, FILE * file);
char writePcs(EmbPattern * pattern, FILE * file);
char readPec(EmbPattern * pattern, const char *fileName, FILE * file);
char writePec(EmbPattern * pattern, const char *fileName, FILE * file);
char readPel(EmbPattern * pattern, FILE * file);
char writePel(EmbPattern * pattern, FILE * file);
char readPem(EmbPattern * pattern, FILE * file);
char writePem(EmbPattern * pattern, FILE * file);
char readPes(EmbPattern * pattern, const char *fileName, FILE * file);
char writePes(EmbPattern * pattern, const char *fileName, FILE * file);
char readPhb(EmbPattern * pattern, FILE * file);
char writePhb(EmbPattern * pattern, FILE * file);
char readPhc(EmbPattern * pattern, FILE * file);
char writePhc(EmbPattern * pattern, FILE * file);
char readPlt(EmbPattern * pattern, FILE * file);
char writePlt(EmbPattern * pattern, FILE * file);
char readRgb(EmbPattern * pattern, FILE * file);
char writeRgb(EmbPattern * pattern, FILE * file);
char readSew(EmbPattern * pattern, FILE * file);
char writeSew(EmbPattern * pattern, FILE * file);
char readShv(EmbPattern * pattern, FILE * file);
char writeShv(EmbPattern * pattern, FILE * file);
char readSst(EmbPattern * pattern, FILE * file);
char writeSst(EmbPattern * pattern, FILE * file);
char readStx(EmbPattern * pattern, FILE * file);
char writeStx(EmbPattern * pattern, FILE * file);
char readSvg(EmbPattern * pattern, FILE * file);
char writeSvg(EmbPattern * pattern, FILE * file);
char readT01(EmbPattern * pattern, FILE * file);
char writeT01(EmbPattern * pattern, FILE * file);
char readT09(EmbPattern * pattern, FILE * file);
char writeT09(EmbPattern * pattern, FILE * file);
char readTap(EmbPattern * pattern, FILE * file);
char writeTap(EmbPattern * pattern, FILE * file);
char readThr(EmbPattern * pattern, FILE * file);
char writeThr(EmbPattern * pattern, FILE * file);
char readTxt(EmbPattern * pattern, FILE * file);
char writeTxt(EmbPattern * pattern, FILE * file);
char readU00(EmbPattern * pattern, FILE * file);
char writeU00(EmbPattern * pattern, FILE * file);
char readU01(EmbPattern * pattern, FILE * file);
char writeU01(EmbPattern * pattern, FILE * file);
char readVip(EmbPattern * pattern, FILE * file);
char writeVip(EmbPattern * pattern, FILE * file);
char readVp3(EmbPattern * pattern, FILE * file);
char writeVp3(EmbPattern * pattern, FILE * file);
char readXxx(EmbPattern * pattern, FILE * file);
char writeXxx(EmbPattern * pattern, FILE * file);
char readZsk(EmbPattern * pattern, FILE * file);
char writeZsk(EmbPattern * pattern, FILE * file);

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
int emb_fname_extension(const char *fileName, char ending[5])
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
int emb_identify_format(const char *fileName)
{
        int i;
        char ending[5];
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
char read_n_bytes(FILE *file, unsigned char *data, unsigned int length)
{
        if (fread(data, 1, length, file) != length) {
                printf("ERROR: failed to read %d bytes from file.", length);
                return 0;
        }
        return 1;
}

/* . */
char embp_read(EmbPattern *pattern, const char *fileName, int format)
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
char embp_write(EmbPattern *pattern, const char *fileName, int format)
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
                char externalFileName[1000];
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
char embp_read_auto(EmbPattern *pattern, const char *fileName)
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
char embp_write_auto(EmbPattern *pattern, const char *fileName)
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
