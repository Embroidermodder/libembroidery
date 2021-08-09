#ifndef LIBEMBROIDERY_HEADER__
#define LIBEMBROIDERY_HEADER__

#include "emb-arc.h"
#include "emb-circle.h"
#include "emb-color.h"
#include "emb-compress.h"
#include "emb-ellipse.h"
#include "emb-file.h"
#include "emb-flag.h"
#include "emb-format.h"
#include "emb-hash.h"
#include "emb-hoop.h"
#include "emb-layer.h"
#include "emb-line.h"
#include "emb-logging.h"
/*#include "emb-outline.h"*/
#include "emb-path.h"
#include "emb-pattern.h"
#include "emb-point.h"
#include "emb-polygon.h"
#include "emb-polyline.h"
#include "emb-reader-writer.h"
#include "emb-rect.h"
#include "emb-satin-line.h"
#include "emb-settings.h"
#include "emb-spline.h"
#include "emb-stitch.h"
#include "emb-thread.h"
#include "emb-time.h"
#include "emb-vector.h"
#include "thread-color.h"

#include "api-start.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef ARDUINO /* ARDUINO TODO: This is temporary. Remove when complete. */

extern EMB_PRIVATE int EMB_CALL readExp(EmbPattern* pattern, const char* fileName);
extern EMB_PRIVATE int EMB_CALL writeExp(EmbPattern* pattern, const char* fileName);

#else /* ARDUINO TODO: This is temporary. Remove when complete. */


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

#endif /* ARDUINO TODO: This is temporary. Remove when complete. */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "api-stop.h"

#endif /* EMBROIDERY_H */

