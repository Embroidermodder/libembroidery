#include "emb-reader-writer.h"
#include "emb-logging.h"
#include "formats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef ARDUINO /* ARDUINO TODO: This is temporary. Remove when complete. */
typedef struct reader_writer_prototype {
    char file_ext[10];
    int (*reader)(EmbPattern*, const char*);
    int (*writer)(EmbPattern*, const char*);
} reader_writer_proto;

reader_writer_proto file_type_list[] = {
    {".10o", read10o, write10o},
    {".100", read100, write100},
    {".art", readArt, writeArt},
    {".bmc", readBmc, writeBmc},
    {".bro", readBro, writeBro},
    {".cnd", readCnd, writeCnd},
    {".col", readCol, writeCol},
    {".csd", readCsd, writeCsd},
    {".csv", readCsv, writeCsv},
    {".dat", readDat, writeDat},
    {".dem", readDem, writeDem},
    {".dsb", readDsb, writeDsb},
    {".dst", readDst, writeDst},
    {".dsz", readDsz, writeDsz},
    {".dxf", readDxf, writeDxf},
    {".edr", readEdr, writeEdr},
    {".emd", readEmd, writeEmd},
    {".exp", readExp, writeExp},
    {".exy", readExy, writeExy},
    {".eys", readEys, writeEys},
    {".fxy", readFxy, writeFxy},
    {".gc", readGc, writeGc},
    {".gnc", readGnc, writeGnc},
    {".gt", readGt, writeGt},
    {".hus", readHus, writeHus},
    {".inb", readInb, writeInb},
    {".inf", readInf, writeInf},
    {".jef", readJef, writeJef},
    {".ksm", readKsm, writeKsm},
    {".max", readMax, writeMax},
    {".mit", readMit, writeMit},
    {".new", readNew, writeNew},
    {".ofm", readOfm, writeOfm},
    {".pcd", readPcd, writePcd},
    {".pcm", readPcm, writePcm},
    {".pcq", readPcq, writePcq},
    {".pcs", readPcs, writePcs},
    {".pec", readPec, writePec},
    {".pel", readPel, writePel},
    {".pem", readPem, writePem},
    {".pes", readPes, writePes},
    {".phb", readPhb, writePhb},
    {".phc", readPhc, writePhc},
    {".plt", readPlt, writePlt},
    {".rgb", readRgb, writeRgb},
    {".sew", readSew, writeSew},
    {".shv", readShv, writeShv},
    {".sst", readSst, writeSst},
    {".stx", readStx, writeStx},
    {".svg", readSvg, writeSvg},
    {".t01", readT01, writeT01},
    {".t09", readT09, writeT09},
    {".tap", readTap, writeTap},
    {".thr", readThr, writeThr},
    {".txt", readTxt, writeTxt},
    {".u00", readU00, writeU00},
    {".u01", readU01, writeU01},
    {".vip", readVip, writeVip},
    {".vp3", readVp3, writeVp3},
    {".xxx", readXxx, writeXxx},
    {".zsk", readZsk, writeZsk},
    {"END", 0, 0}
};
#endif

/*! Returns a pointer to an EmbReaderWriter if the \a fileName is a supported file type. */
EmbReaderWriter* embReaderWriter_getByFileName(const char* fileName)
{
    int i = 0;
    char ending[5];
    EmbReaderWriter* rw = 0;

    if(!fileName) { embLog_error("emb-reader-writer.c embReaderWriter_getByFileName(), fileName argument is null\n"); return 0; }

    if(strlen(fileName) == 0) return 0;
    strcpy(ending, strrchr(fileName, '.'));

    while(ending[i] != '\0')
    {
        ending[i] = (char)tolower(ending[i]);
        ++i;
    }
    rw = (EmbReaderWriter*)malloc(sizeof(EmbReaderWriter));
    if(!rw) { embLog_error("emb-reader-writer.c embReaderWriter_getByFileName(), cannot allocate memory for rw\n"); return 0; }

    #ifdef ARDUINO /* ARDUINO TODO: This is temporary. Remove when complete. */
    if(!strcmp(ending, ".exp"))
    {
        rw->reader = readExp;
        rw->writer = writeExp;
        return rw;
    }
    #else /* ARDUINO TODO: This is temporary. Remove when complete. */        
    /* checks the first character to see if it is the end symbol */
    for (i=0; file_type_list[i].file_ext[0]!='E'; i++) {
        if (!strcmp(ending, file_type_list[i].file_ext))
        {
            rw->reader = file_type_list[i].reader;
            rw->writer = file_type_list[i].writer;
            return rw;
        }
    }
    #endif /* ARDUINO TODO: This is temporary. Remove when complete. */

    embLog_error("emb-reader-writer.c embReaderWriter_getByFileName(), unsupported file type: %s\n", ending);
    return 0;
}

/* kate: bom off; indent-mode cstyle; indent-width 4; replace-trailing-space-save on; */
