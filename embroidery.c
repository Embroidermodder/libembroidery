/*
 * Libembroidery 1.0.0-alpha
 * https://www.libembroidery.org
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 * ---------------------------------------------------------
 *
 * Copyright 2018-2024 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * ---------------------------------------------------------
 *
 * Only uses source from this directory or standard C libraries,
 * not including POSIX headers like unistd since this library
 * needs to support non-POSIX systems like Windows.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#include "embroidery.h"


/* Utility Functions */
EMB_PUBLIC int stringInArray(const char *s, const char **array);
EMB_PUBLIC char *copy_trim(char const *s);
EMB_PUBLIC char* emb_optOut(EmbReal num, char* str);
EMB_PUBLIC void safe_free(void *data);

/* DIFAT functions */
EMB_PUBLIC unsigned int entriesInDifatSector(bcf_file_difat* fat);
EMB_PUBLIC bcf_file_fat* bcfFileFat_create(const unsigned int sectorSize);
EMB_PUBLIC void loadFatFromSector(bcf_file_fat* fat, FILE* file);
EMB_PUBLIC void bcf_file_fat_free(bcf_file_fat** fat);
EMB_PUBLIC bcf_directory* CompoundFileDirectory(const unsigned int maxNumberOfDirectoryEntries);
EMB_PUBLIC void bcf_directory_free(bcf_directory** dir);
EMB_PUBLIC unsigned int numberOfEntriesInDifatSector(bcf_file_difat* fat);
EMB_PUBLIC void bcf_file_difat_free(bcf_file_difat* difat);
EMB_PUBLIC bcf_file_header bcfFileHeader_read(FILE* file);
EMB_PUBLIC int bcfFileHeader_isValid(bcf_file_header header);
EMB_PUBLIC void bcf_file_free(bcf_file* bcfFile);

EMB_PUBLIC void testTangentPoints(EmbCircle c, EmbVector p, EmbVector *t0, EmbVector *t1);
EMB_PUBLIC int create_test_file_1(const char* outf);
EMB_PUBLIC int create_test_file_2(const char* outf);
EMB_PUBLIC int create_test_file_3(const char* outf);
EMB_PUBLIC int testEmbCircle(void);
EMB_PUBLIC int testEmbCircle_2(void);
EMB_PUBLIC int testGeomArc(void);
EMB_PUBLIC int testThreadColor(void);
EMB_PUBLIC int testEmbFormat(void);

/* Encoding/decoding and compression functions. */
EMB_PUBLIC int hus_compress(char* input, int size, char* output, int *out_size);
EMB_PUBLIC int hus_decompress(char* input, int size, char* output, int *out_size);

EMB_PUBLIC void huffman_build_table(huffman *h);
EMB_PUBLIC int *huffman_table_lookup(huffman *h, int byte_lookup, int *lengths);

EMB_PUBLIC int compress_get_bits(compress *c, int length);
EMB_PUBLIC int compress_pop(compress *c, int bit_count);
EMB_PUBLIC int compress_read_variable_length(compress *c);
EMB_PUBLIC void compress_load_character_length_huffman(compress *c);
EMB_PUBLIC void compress_load_character_huffman(compress *c);
EMB_PUBLIC void compress_load_distance_huffman(compress *c);
EMB_PUBLIC void compress_load_block(compress *c);
EMB_PUBLIC int compress_get_token(compress *c);
EMB_PUBLIC int compress_get_position(compress *c);

EMB_PUBLIC EmbReal pfaffDecode(unsigned char a1, unsigned char a2, unsigned char a3);

EMB_PUBLIC int decodeNewStitch(unsigned char value);

EMB_PUBLIC unsigned char mitEncodeStitch(EmbReal value);
EMB_PUBLIC int mitDecodeStitch(unsigned char value);

EMB_PUBLIC void encode_t01_record(unsigned char b[3], int x, int y, int flags);
EMB_PUBLIC int decode_t01_record(unsigned char b[3], int *x, int *y, int *flags);

EMB_PUBLIC int encode_tajima_ternary(unsigned char b[3], int x, int y);
EMB_PUBLIC void decode_tajima_ternary(unsigned char b[3], int *x, int *y);

/*
 * Note that this file only has to exist because we cannot necessary include
 * any of the C standard library on all platforms. For example, "FILE *" and
 * "printf" aren't universal. See the "Supported Platforms" section of
 * the reference manual.
 */

/* Function Declarations
*****************************************************************************/
void readPecStitches(EmbPattern* pattern, FILE* file);
void writePecStitches(EmbPattern* pattern, FILE* file, const char* filename);

void pfaffEncode(FILE* file, int x, int y, int flags);

void readPESHeaderV5(FILE* file, EmbPattern* pattern);
void readPESHeaderV6(FILE* file, EmbPattern* pattern);
void readPESHeaderV7(FILE* file, EmbPattern* pattern);
void readPESHeaderV8(FILE* file, EmbPattern* pattern);
void readPESHeaderV9(FILE* file, EmbPattern* pattern);
void readPESHeaderV10(FILE* file, EmbPattern* pattern);

void readDescriptions(FILE* file, EmbPattern* pattern);
void readHoopName(FILE* file, EmbPattern* pattern);
void readImageString(FILE* file, EmbPattern* pattern);
void readProgrammableFills(FILE* file, EmbPattern* pattern);
void readMotifPatterns(FILE* file, EmbPattern* pattern);
void readFeatherPatterns(FILE* file, EmbPattern* pattern);
void readThreads(FILE* file, EmbPattern* pattern);

void embInt_read(FILE* f, char *label, void *b, int mode);
void embInt_write(FILE* f, char *label, void *b, int mode);
int emb_readline(FILE* file, char *line, int maxLength);

int bcfFile_read(FILE* file, bcf_file* bcfFile);
FILE* GetFile(bcf_file* bcfFile, FILE* file, char* fileToFind);

void binaryReadString(FILE* file, char *buffer, int maxLength);
void binaryReadUnicodeString(FILE* file, char *buffer, const int stringLength);

void fpad(FILE *f, char c, int n);

void write_24bit(FILE* file, int);
int check_header_present(FILE* file, int minimum_header_length);

unsigned short fread_uint16(FILE *file);
short fread_int16(FILE* f);
int fread_int32_be(FILE* f);
void embInt_read(FILE* f, char *label, void *b, int mode);

void binaryWriteUIntBE(FILE* f, unsigned int data);
void binaryWriteUInt(FILE* f, unsigned int data);
void binaryWriteIntBE(FILE* f, int data);
void binaryWriteInt(FILE* f, int data);
void binaryWriteUShort(FILE* f, unsigned short data);
void binaryWriteUShortBE(FILE* f, unsigned short data);
void binaryWriteShort(FILE* f, short data);

bcf_file_difat* bcf_difat_create(FILE* file, unsigned int fatSectors, const unsigned int sectorSize);
unsigned int readFullSector(FILE* file, bcf_file_difat* bcfFile, unsigned int* numberOfDifatEntriesStillToRead);
bcf_directory_entry* CompoundFileDirectoryEntry(FILE* file);
void readNextSector(FILE* file, bcf_directory* dir);

void embColor_read(FILE *f, EmbColor *c, int toRead);
void embColor_write(FILE *f, EmbColor c, int toWrite);

char read100(EmbPattern *pattern, FILE* file);
char write100(EmbPattern *pattern, FILE* file);
char read10o(EmbPattern *pattern, FILE* file);
char write10o(EmbPattern *pattern, FILE* file);
char readArt(EmbPattern *pattern, FILE* file);
char writeArt(EmbPattern *pattern, FILE* file);
char readBmc(EmbPattern *pattern, FILE* file);
char writeBmc(EmbPattern *pattern, FILE* file);
char readBro(EmbPattern *pattern, FILE* file);
char writeBro(EmbPattern *pattern, FILE* file);
char readCnd(EmbPattern *pattern, FILE* file);
char writeCnd(EmbPattern *pattern, FILE* file);
char readCol(EmbPattern *pattern, FILE* file);
char writeCol(EmbPattern *pattern, FILE* file);
char readCsd(EmbPattern *pattern, FILE* file);
char writeCsd(EmbPattern *pattern, FILE* file);
char readCsv(EmbPattern *pattern, FILE* file);
char writeCsv(EmbPattern *pattern, FILE* file);
char readDat(EmbPattern *pattern, FILE* file);
char writeDat(EmbPattern *pattern, FILE* file);
char readDem(EmbPattern *pattern, FILE* file);
char writeDem(EmbPattern *pattern, FILE* file);
char readDsb(EmbPattern *pattern, FILE* file);
char writeDsb(EmbPattern *pattern, FILE* file);
char readDst(EmbPattern *pattern, FILE* file);
char writeDst(EmbPattern *pattern, FILE* file);
char readDsz(EmbPattern *pattern, FILE* file);
char writeDsz(EmbPattern *pattern, FILE* file);
char readDxf(EmbPattern *pattern, FILE* file);
char writeDxf(EmbPattern *pattern, FILE* file);
char readEdr(EmbPattern *pattern, FILE* file);
char writeEdr(EmbPattern *pattern, FILE* file);
char readEmd(EmbPattern *pattern, FILE* file);
char writeEmd(EmbPattern *pattern, FILE* file);
char readExp(EmbPattern *pattern, FILE* file);
char writeExp(EmbPattern *pattern, FILE* file);
char readExy(EmbPattern *pattern, FILE* file);
char writeExy(EmbPattern *pattern, FILE* file);
char readEys(EmbPattern *pattern, FILE* file);
char writeEys(EmbPattern *pattern, FILE* file);
char readFxy(EmbPattern *pattern, FILE* file);
char writeFxy(EmbPattern *pattern, FILE* file);
char readGc(EmbPattern *pattern, FILE* file);
char writeGc(EmbPattern *pattern, FILE* file);
char readGnc(EmbPattern *pattern, FILE* file);
char writeGnc(EmbPattern *pattern, FILE* file);
char readGt(EmbPattern *pattern, FILE* file);
char writeGt(EmbPattern *pattern, FILE* file);
char readHus(EmbPattern *pattern, FILE* file);
char writeHus(EmbPattern *pattern, FILE* file);
char readInb(EmbPattern *pattern, FILE* file);
char writeInb(EmbPattern *pattern, FILE* file);
char readInf(EmbPattern *pattern, FILE* file);
char writeInf(EmbPattern *pattern, FILE* file);
char readJef(EmbPattern *pattern, FILE* file);
char writeJef(EmbPattern *pattern, FILE* file);
char readKsm(EmbPattern *pattern, FILE* file);
char writeKsm(EmbPattern *pattern, FILE* file);
char readMax(EmbPattern *pattern, FILE* file);
char writeMax(EmbPattern *pattern, FILE* file);
char readMit(EmbPattern *pattern, FILE* file);
char writeMit(EmbPattern *pattern, FILE* file);
char readNew(EmbPattern *pattern, FILE* file);
char writeNew(EmbPattern *pattern, FILE* file);
char readOfm(EmbPattern *pattern, FILE* file);
char writeOfm(EmbPattern *pattern, FILE* file);
char readPcd(EmbPattern *pattern, const char *fileName, FILE* file);
char writePcd(EmbPattern *pattern, FILE* file);
char readPcm(EmbPattern *pattern, FILE* file);
char writePcm(EmbPattern *pattern, FILE* file);
char readPcq(EmbPattern *pattern, const char *fileName, FILE* file);
char writePcq(EmbPattern *pattern, FILE* file);
char readPcs(EmbPattern *pattern, const char *fileName, FILE* file);
char writePcs(EmbPattern *pattern, FILE* file);
char readPec(EmbPattern *pattern, const char *fileName, FILE* file);
char writePec(EmbPattern *pattern, const char *fileName,  FILE* file);
char readPel(EmbPattern *pattern, FILE *file);
char writePel(EmbPattern *pattern, FILE *file);
char readPem(EmbPattern *pattern, FILE *file);
char writePem(EmbPattern *pattern, FILE *file);
char readPes(EmbPattern *pattern, const char *fileName, FILE* file);
char writePes(EmbPattern *pattern, const char *fileName, FILE* file);
char readPhb(EmbPattern *pattern, FILE* file);
char writePhb(EmbPattern *pattern, FILE *file);
char readPhc(EmbPattern *pattern, FILE* file);
char writePhc(EmbPattern *pattern, FILE *file);
char readPlt(EmbPattern *pattern, FILE* file);
char writePlt(EmbPattern *pattern, FILE* file);
char readRgb(EmbPattern *pattern, FILE* file);
char writeRgb(EmbPattern *pattern, FILE* file);
char readSew(EmbPattern *pattern, FILE* file);
char writeSew(EmbPattern *pattern, FILE* file);
char readShv(EmbPattern *pattern, FILE* file);
char writeShv(EmbPattern *pattern, FILE *file);
char readSst(EmbPattern *pattern, FILE* file);
char writeSst(EmbPattern *pattern, FILE *file);
char readStx(EmbPattern *pattern, FILE* file);
char writeStx(EmbPattern *pattern, FILE *file);
char readSvg(EmbPattern *pattern, FILE* file);
char writeSvg(EmbPattern *pattern, FILE* file);
char readT01(EmbPattern *pattern, FILE* file);
char writeT01(EmbPattern *pattern, FILE* file);
char readT09(EmbPattern *pattern, FILE* file);
char writeT09(EmbPattern *pattern, FILE* file);
char readTap(EmbPattern *pattern, FILE* file);
char writeTap(EmbPattern *pattern, FILE* file);
char readThr(EmbPattern *pattern, FILE* file);
char writeThr(EmbPattern *pattern, FILE* file);
char readTxt(EmbPattern *pattern, FILE* file);
char writeTxt(EmbPattern *pattern, FILE* file);
char readU00(EmbPattern *pattern, FILE* file);
char writeU00(EmbPattern *pattern, FILE *file);
char readU01(EmbPattern *pattern, FILE* file);
char writeU01(EmbPattern *pattern, FILE *file);
char readVip(EmbPattern *pattern, FILE* file);
char writeVip(EmbPattern *pattern, FILE* file);
char readVp3(EmbPattern *pattern, FILE* file);
char writeVp3(EmbPattern *pattern, FILE* file);
char readXxx(EmbPattern *pattern, FILE* file);
char writeXxx(EmbPattern *pattern, FILE* file);
char readZsk(EmbPattern *pattern, FILE* file);
char writeZsk(EmbPattern *pattern, FILE* file);

#include "cli.c"
#include "array.c"
#include "formats.c"
#include "geometry.c"
#include "pattern.c"
#include "image.c"
#include "fill.c"
#include "compress.c"
#include "encoding.c"
#include "thread-color.c"
