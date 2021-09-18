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

/* MATHS MACROS
 *
 * Rather than having to call a max function multiple times these macros allow
 * us to stack the variables up, this is particularly useful for bounding box
 * calculations.
 *
 * This also saves having int, float, double, etc. versions.
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

static int roundDouble(double src);
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

static EmbHash* embHash_create(void);
static void embHash_free(EmbHash* hash);

static int embHash_contains(const EmbHash* hash, const void* key);
static int embHash_insert(EmbHash* hash, const void* key, void* value);
static void* embHash_value(const EmbHash* hash, const void* key);
static void embHash_remove(EmbHash* hash, const void *key);
static void embHash_clear(EmbHash* hash);
static int embHash_empty(const EmbHash* hash);
static long embHash_count(const EmbHash* hash);
static void embHash_rehash(EmbHash* hash, long numOfBuckets);

/*
static const unsigned int NumberOfDifatEntriesInHeader;
static const int pecThreadCount;
static const EmbThread pecThreads[];
static const char imageWithFrame[38][48];
static const EmbThread jefThreads[];
static const int shvThreadCount;
static const EmbThread shvThreads[];
static const double embConstantPi;
*/

static int read100(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int write100(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int read10o(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int write10o(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readArt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeArt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readBmc(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeBmc(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readBro(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeBro(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readCnd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeCnd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readCol(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeCol(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readCsd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeCsd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readCsv(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeCsv(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readDat(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeDat(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readDem(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeDem(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readDsb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeDsb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readDst(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeDst(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readDsz(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeDsz(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readDxf(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeDxf(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readEdr(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeEdr(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readEmd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeEmd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readExp(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeExp(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readExy(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeExy(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readEys(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeEys(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readFxy(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeFxy(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readGc(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeGc(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readGnc(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeGnc(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readGt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeGt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readHus(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeHus(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readInb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeInb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readInf(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeInf(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readJef(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeJef(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readKsm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeKsm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readMax(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeMax(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readMit(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeMit(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readNew(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeNew(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readOfm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeOfm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readPcd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writePcd(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readPcm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writePcm(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readPcq(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writePcq(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readPcs(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writePcs(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readPec(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writePec(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readPel(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writePel(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readPem(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writePem(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readPes(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writePes(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readPhb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writePhb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readPhc(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writePhc(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readPlt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writePlt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readRgb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeRgb(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readSew(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeSew(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readShv(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeShv(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readSst(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeSst(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readStx(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeStx(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readSvg(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeSvg(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readT01(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeT01(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readT09(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeT09(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readTap(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeTap(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readThr(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeThr(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readTxt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeTxt(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readU00(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeU00(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readU01(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeU01(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readVip(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeVip(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readVp3(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeVp3(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readXxx(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeXxx(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int readZsk(EmbPattern *pattern, EmbFile* file, const char* fileName);
static int writeZsk(EmbPattern *pattern, EmbFile* file, const char* fileName);

#include "format-100.c"
#include "format-10o.c"
#include "format-art.c"
#include "format-bmc.c"
#include "format-bro.c"
#include "format-cnd.c"
#include "format-col.c"
#include "format-csd.c"
#include "format-csv.c"
#include "format-dat.c"
#include "format-dem.c"
#include "format-dsb.c"
#include "format-dst.c"
#include "format-dsz.c"
#include "format-dxf.c"
#include "format-edr.c"
#include "format-emd.c"
#include "format-exp.c"
#include "format-exy.c"
#include "format-eys.c"
#include "format-fxy.c"
#include "format-gc.c"
#include "format-gnc.c"
#include "format-gt.c"
#include "format-hus.c"
#include "format-inb.c"
#include "format-inf.c"
#include "format-jef.c"
#include "format-ksm.c"
#include "format-max.c"
#include "format-mit.c"
#include "format-new.c"
#include "format-ofm.c"
#include "format-pcd.c"
#include "format-pcm.c"
#include "format-pcq.c"
#include "format-pcs.c"
#include "format-pec.c"
#include "format-pel.c"
#include "format-pem.c"
#include "format-pes.c"
#include "format-phb.c"
#include "format-phc.c"
#include "format-plt.c"
#include "format-rgb.c"
#include "format-sew.c"
#include "format-shv.c"
#include "format-sst.c"
#include "format-stx.c"
#include "format-svg.c"
#include "format-t01.c"
#include "format-t09.c"
#include "format-tap.c"
#include "format-thr.c"
#include "format-txt.c"
#include "format-u00.c"
#include "format-u01.c"
#include "format-vip.c"
#include "format-vp3.c"
#include "format-xxx.c"
#include "format-zsk.c"

#include "emb-array.c"
#include "emb-compress.c"
#include "emb-file.c"
#include "emb-geometry.c"
#include "emb-pattern.c"
#include "emb-stitch-fill.c"
#include "emb-thread.c"
#include "emb-utility.c"

#include "hashtable.c"

