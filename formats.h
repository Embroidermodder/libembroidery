#ifndef FORMATS_H
#define FORMATS_H

#include "emb-file.h"
#include "emb-pattern.h"

#include "api-start.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef ARDUINO /* ARDUINO TODO: This is temporary. Remove when complete. */

extern EMB_PRIVATE int EMB_CALL readExp(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeExp(EmbPattern* pattern, const char* fileName);

#else /* ARDUINO TODO: This is temporary. Remove when complete. */

/* Structs for specific file types */
typedef enum
{
    CSV_EXPECT_NULL,
    CSV_EXPECT_QUOTE1,
    CSV_EXPECT_QUOTE2,
    CSV_EXPECT_COMMA
} CSV_EXPECT;

typedef enum
{
    CSV_MODE_NULL,
    CSV_MODE_COMMENT,
    CSV_MODE_VARIABLE,
    CSV_MODE_THREAD,
    CSV_MODE_STITCH
} CSV_MODE;


typedef struct SvgAttribute_     SvgAttribute;
typedef struct SvgAttributeList_ SvgAttributeList;
typedef struct SvgElement_       SvgElement;

struct SvgAttribute_
{
    char* name;
    char* value;
};

struct SvgAttributeList_
{
    SvgAttribute attribute;
    SvgAttributeList* next;
};

struct SvgElement_
{
    char* name;
    SvgAttributeList* attributeList;
    SvgAttributeList* lastAttribute;
};

typedef enum
{
    SVG_CREATOR_NULL,
    SVG_CREATOR_EMBROIDERMODDER,
    SVG_CREATOR_ILLUSTRATOR,
    SVG_CREATOR_INKSCAPE
} SVG_CREATOR;

typedef enum
{
    SVG_EXPECT_NULL,
    SVG_EXPECT_ELEMENT,
    SVG_EXPECT_ATTRIBUTE,
    SVG_EXPECT_VALUE
} SVG_EXPECT;

typedef enum
{
    SVG_NULL,
    SVG_ELEMENT,
    SVG_PROPERTY,
    SVG_MEDIA_PROPERTY,
    SVG_ATTRIBUTE,
    SVG_CATCH_ALL
} SVG_TYPES;

/* variables used across formats */
extern const char imageWithFrame[38][48];
extern const int pecThreadCount;
extern const EmbThread pecThreads[100];

extern const EmbThread jefThreads[100];

/* Reader/writer functions for specific file types */
extern EMB_PRIVATE int EMB_CALL read100(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL write100(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL read10o(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL write10o(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readArt(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeArt(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readBmc(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeBmc(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readBro(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeBro(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readCnd(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeCnd(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readCol(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeCol(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readCsd(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeCsd(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readCsv(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeCsv(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readDat(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeDat(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readDem(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeDem(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readDsb(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeDsb(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readDst(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeDst(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readDsz(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeDsz(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readDxf(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeDxf(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readEdr(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeEdr(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readEmd(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeEmd(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readExp(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeExp(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readExy(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeExy(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readEys(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeEys(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readFxy(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeFxy(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readGc(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeGc(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readGnc(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeGnc(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readGt(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeGt(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readHus(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeHus(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readInb(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeInb(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readInf(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeInf(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readJef(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeJef(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readKsm(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeKsm(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readMax(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeMax(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readMit(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeMit(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readNew(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeNew(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readOfm(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeOfm(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readPcd(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writePcd(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readPcm(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writePcm(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readPcq(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writePcq(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readPcs(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writePcs(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readPec(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writePec(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE void EMB_CALL readPecStitches(EmbPattern* pattern, EmbFile* file);
extern EMB_PRIVATE void EMB_CALL writePecStitches(EmbPattern* pattern, EmbFile* file, const char* filename);

extern EMB_PRIVATE int EMB_CALL readPel(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writePel(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readPem(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writePem(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readPes(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writePes(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readPhb(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writePhb(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readPhc(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writePhc(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readPlt(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writePlt(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readRgb(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeRgb(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readSew(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeSew(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readShv(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeShv(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readSst(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeSst(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readStx(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeStx(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readSvg(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeSvg(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readT01(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeT01(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readT09(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeT09(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readTap(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeTap(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readThr(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeThr(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readTxt(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeTxt(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readU00(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeU00(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readU01(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeU01(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readVip(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeVip(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readVp3(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeVp3(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readXxx(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeXxx(EmbPattern* pattern, const char* fileName);

extern EMB_PRIVATE int EMB_CALL readZsk(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeZsk(EmbPattern* pattern, const char* fileName);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "api-stop.h"

#endif /* ARDUINO TODO: This is temporary. Remove when complete. */

#endif /* FORMATS_H */


