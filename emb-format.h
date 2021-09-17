#include "embroidery.h"

/* to help inlining, these can be declared static if they share a
 * file with the format table
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

