#include "embroidery.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* MACRO LIBRARY
 *
 * These macros aren't intended for users of the library.
 *
 * In order to reduce the number of function calls and definitions for embedded
 * compatibility some macros can serve as multiple function definitions.
 *
 * For example here we have a way of turning an arbitrary point in a header
 * that may contain, say, 512 bytes into an int without determining what
 * sign that int is as that will be done by the type of the variable.
 *
 * If we need to pass in, say, 30 bytes in then if we pass:
 *     EMB_GET_INT(header+30)
 * then the macro becomes:
 *     (*(header+30) | *(buff+31) << 8 | *(buff+32) << 16 | *(buff+33) << 24)
 * aka:
 *     (header[30] | header[31] << 8 | header[32] << 16 | header[33] << 24)
 */
#define EMB_GET_INT(buff) \
    (*(buff) | *(buff+1) << 8 | *(buff+2) << 16 | *(buff+3) << 24)

#define EMB_GET_SHORT(buff) \
    (*(buff) | *(buff+1) << 8)

#define EMB_GET_INT_BE(buff) \
    (*(buff+3) | *(buff+2) << 8 | *(buff+1) << 16 | *(buff) << 24)

#define EMB_GET_SHORT_BE(buff) \
    (*(buff+1) | *(buff) << 8)

/* This should replace the need for many embFile_readType(file) functions.
 *
 * This also means that we don't need to "skip" padding variables while reading
 * etc as we just read the whole block.
 *
 * The right shift operator works differently with respect to sign so we cast
 * first. Also endianness matters as before.
 */
 
#define EMB_WRITE_INT(buff, a) \
    *(buff+0) = (unsigned int)a & 0x000000FF; \
    *(buff+1) = ((unsigned int)a & 0x0000FF00)>>8; \
    *(buff+2) = ((unsigned int)a & 0x00FF0000)>>16; \
    *(buff+3) = ((unsigned int)a & 0xFF000000)>>24;

#define EMB_WRITE_SHORT(buff, a) \
    *(buff+0) = (unsigned int)a & 0x00FF; \
    *(buff+1) = ((unsigned int)a & 0xFF00)>>8;

#define EMB_WRITE_INT_BE(buff, a) \
    *(buff+3) = (unsigned int)a & 0x000000FF; \
    *(buff+2) = ((unsigned int)a & 0x0000FF00)>>8; \
    *(buff+1) = ((unsigned int)a & 0x00FF0000)>>16; \
    *(buff+0) = ((unsigned int)a & 0xFF000000)>>24;

#define EMB_WRITE_SHORT_BE(buff, a) \
    *(buff+1) = (unsigned int)a & 0x00FF; \
    *(buff+0) = ((unsigned int)a & 0xFF00)>>8;

/* returns the value of the n-th bit in a */
#define BIT(a, n) \
    ((a & (1 << n)) / (1 << n))

/* returns the value of the n-th bit in a */
#define SETBIT(a, n) \
    a |= (1 << n)

/* MATHS MACROS
 *
 * Rather than having to call a max function multiple times these macros allow
 * us to stack the variables up, this is particularly useful for bounding box
 * calculations.
 *
 * This also saves having int, float, float, etc. versions.
 */
#define EMB_MAX_2(a, b) \
    ((a > b) ? a : b)

#define EMB_MAX_3(a, b, c) \
    ((a > b) ? EMB_MAX_2(a, c) : EMB_MAX_2(b, c))

#define EMB_MAX_4(a, b, c, d) \
    EMB_MAX_2(EMB_MAX_2(a, b), EMB_MAX_2(c, d))

#define EMB_MIN_2(a, b) \
    ((a < b) ? a : b)

#define EMB_MIN_3(a, b, c) \
    ((a < b) ? EMB_MIN_2(a, c) : EMB_MIN_2(b, c))

#define EMB_MIN_4(a, b, c, d) \
    EMB_MIN_2(EMB_MIN_2(a, b), EMB_MIN_2(c, d))

/* STATIC FUNCTIONS
 *
 * For functions that can be declared static and inlined automatically
 * that won't be called by users through embroidery.h.
 */

static char binaryReadByte(EmbFile* file);
static int binaryReadBytes(EmbFile* file, unsigned char* destination, int count);
static short binaryReadInt16(EmbFile* file);
static int binaryReadInt32(EmbFile* file);
static unsigned char binaryReadUInt8(EmbFile* file);
static unsigned short binaryReadUInt16(EmbFile* file);
static unsigned int binaryReadUInt32(EmbFile* file);
static short binaryReadInt16BE(EmbFile* file); /* Big endian version */
static unsigned short binaryReadUInt16BE(EmbFile* file); /* Big endian version */
static int binaryReadInt32BE(EmbFile* file);   /* Big endian version */
static unsigned int binaryReadUInt32BE(EmbFile* file);
static float binaryReadFloat(EmbFile* file);
static void binaryReadString(EmbFile* file, char *buffer, int maxLength);
static void binaryReadUnicodeString(EmbFile* file, char *buffer, const int stringLength);

static void binaryWriteByte(EmbFile* file, unsigned char data);
static void binaryWriteBytes(EmbFile* file, const char* data, int size);
static void binaryWriteShort(EmbFile* file, short data);
static void binaryWriteShortBE(EmbFile* file, short data);
static void binaryWriteUShort(EmbFile* file, unsigned short data);
static void binaryWriteUShortBE(EmbFile* file, unsigned short data);
static void binaryWriteInt(EmbFile* file, int data);
static void binaryWriteIntBE(EmbFile* file, int data);
static void binaryWriteUInt(EmbFile* file, unsigned int data);
static void binaryWriteUIntBE(EmbFile* file, unsigned int data);
static void binaryWriteFloat(EmbFile* file, float data);

static int roundDouble(float src);
static void writeInt(EmbFile *, int, int);
static void writeFloat(EmbFile *, float);
static char* lTrim(char* str, char junk);
static char* emb_strdup(char* src);

static void embPointerToArray(char *buffer, void* pointer, int maxDigits);
static void embIntToArray(char *buffer, int number, int maxDigits);
static void embFloatToArray(char *buffer, float number, float tolerence, int before, int after);

static void husExpand(unsigned char* input, unsigned char* output, int compressedSize, int _269);
static int husCompress(unsigned char* _266, unsigned long _inputSize, unsigned char* _267, int _269, int _235);
 
static void readPecStitches(EmbPattern* pattern, EmbFile* file, const char* fileName);
static void writePecStitches(EmbPattern* pattern, EmbFile* file, const char* filename);

static void embLog(const char* str);
static void embTime_initNow(EmbTime* t);
static EmbTime embTime_time(EmbTime* t);

static char read100(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char write100(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char read10o(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char write10o(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readBro(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeBro(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readCol(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeCol(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readCsd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeCsd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readCsv(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeCsv(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readDat(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeDat(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readDem(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeDem(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readDsb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeDsb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readDst(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeDst(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readDsz(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeDsz(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readDxf(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeDxf(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readEdr(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeEdr(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readEmd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeEmd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readExp(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeExp(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readExy(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeExy(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readFxy(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeFxy(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readGt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeGt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readHus(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeHus(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readInb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeInb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readInf(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeInf(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readJef(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeJef(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readKsm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeKsm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readMax(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeMax(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readMit(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeMit(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readNew(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeNew(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readOfm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeOfm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPcd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePcd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPcm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePcm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPcq(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePcq(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPcs(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePcs(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPec(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePec(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPel(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePel(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPem(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePem(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPes(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePes(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPhb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePhb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPhc(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePhc(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readPlt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writePlt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readRgb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeRgb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readSew(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeSew(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readShv(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeShv(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readSst(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeSst(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readStx(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeStx(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readSvg(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeSvg(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readT01(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeT01(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readT09(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeT09(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readTap(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeTap(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readThr(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeThr(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readTxt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeTxt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readU00(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeU00(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readU01(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeU01(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readVip(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeVip(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readVp3(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeVp3(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readXxx(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeXxx(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char readZsk(EmbPattern *pattern, EmbFile* file, const char* fileName);
static char writeZsk(EmbPattern *pattern, EmbFile* file, const char* fileName);

/**************
 * DATA SECTION
 */
static EmbColor black = { 0, 0, 0 };

/**************
 * CODE SECTION
 */
#include "emb-parse-svg.c"
#include "emb-format.c"
#include "emb-array.c"
#include "emb-compress.c"
#include "emb-file.c"
#include "emb-geometry.c"
#include "emb-pattern.c"
#include "emb-stitch-fill.c"
#include "emb-thread.c"
#include "emb-utility.c"

