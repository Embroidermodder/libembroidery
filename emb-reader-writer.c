#include "embroidery.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

/*! Returns a pointer to an EmbReaderWriter if the \a fileName is a supported file type. */
EmbReaderWriter* embReaderWriter_getByFileName(const char* fileName)
{
    int i = 0;
    char ending[5];
    EmbReaderWriter* rw = 0;

    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }

    rw = (EmbReaderWriter*)malloc(sizeof(EmbReaderWriter));
    if(!rw) { printf("ERROR: emb-reader-writer.c embReaderWriter_getByFileName(), cannot allocate memory for rw\n"); return 0; }

    /* checks the first character to see if it is the end symbol */
    for (i=0; file_type_list[i].file_ext[0]!='E'; i++) {
        if (!strcmp(ending, file_type_list[i].file_ext))
        {
            rw->reader = file_type_list[i].reader;
            rw->writer = file_type_list[i].writer;
            return rw;
        }
    }

    printf("ERROR: emb-reader-writer.c embReaderWriter_getByFileName(), unsupported file type: %s\n", ending);
    return 0;
}

