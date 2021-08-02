#include "emb-format.h"
#include "emb-logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* TODO: This list needs reviewed in case some stitch formats also can contain object data (EMBFORMAT_STCHANDOBJ). */

EmbFormatList formatTable[100] = {
    {".10o", "Toyota Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY},
    {".100", "Toyota Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY},
    {".art", "Bernina Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY},
    {".bmc", "Bitmap Cache Embroidery Format",     ' ', ' ', EMBFORMAT_STITCHONLY},
    {".bro", "Bits & Volts Embroidery Format",     'U', ' ', EMBFORMAT_STITCHONLY},
    {".cnd", "Melco Embroidery Format",            ' ', ' ', EMBFORMAT_STITCHONLY},
    {".col", "Embroidery Thread Color Format",     'U', 'U', EMBFORMAT_STITCHONLY},
    {".csd", "Singer Embroidery Format",           'U', ' ', EMBFORMAT_STITCHONLY},
    {".csv", "Comma Separated Values Format",      'U', 'U', EMBFORMAT_STITCHONLY},
    {".dat", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".dem", "Melco Embroidery Format",            ' ', ' ', EMBFORMAT_STITCHONLY},
    {".dsb", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".dst", "Tajima Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY},
    {".dsz", "ZSK USA Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".dxf", "Drawing Exchange Format",            ' ', ' ', EMBFORMAT_OBJECTONLY},
    {".edr", "Embird Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY},
    {".emd", "Elna Embroidery Format",             'U', ' ', EMBFORMAT_STITCHONLY},
    {".exp", "Melco Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".exy", "Eltac Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".eys", "Sierra Expanded Embroidery Format",  ' ', ' ', EMBFORMAT_STITCHONLY},
    {".fxy", "Fortron Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".gc",  "Smoothie G-Code Format",             ' ', ' ', EMBFORMAT_STITCHONLY},
    {".gnc", "Great Notions Embroidery Format",    ' ', ' ', EMBFORMAT_STITCHONLY},
    {".gt",  "Gold Thread Embroidery Format",      'U', ' ', EMBFORMAT_STITCHONLY},
    {".hus", "Husqvarna Viking Embroidery Format", 'U', 'U', EMBFORMAT_STITCHONLY},
    {".inb", "Inbro Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".inf", "Embroidery Color Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".jef", "Janome Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY},
    {".ksm", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".max", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".mit", "Mitsubishi Embroidery Format",       'U', ' ', EMBFORMAT_STITCHONLY},
    {".new", "Ameco Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".ofm", "Melco Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".pcd", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".pcm", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".pcq", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".pcs", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".pec", "Brother Embroidery Format",          'U', 'U', EMBFORMAT_STITCHONLY},
    {".pel", "Brother Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY},
    {".pem", "Brother Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY},
    {".pes", "Brother Embroidery Format",          'U', 'U', EMBFORMAT_STITCHONLY},
    {".phb", "Brother Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".phc", "Brother Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".plt", "AutoCAD Plot Drawing Format",        'U', 'U', EMBFORMAT_STITCHONLY},
    {".rgb", "RGB Embroidery Format",              'U', 'U', EMBFORMAT_STITCHONLY},
    {".sew", "Janome Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY},
    {".shv", "Husqvarna Viking Embroidery Format", 'U', ' ', EMBFORMAT_STITCHONLY},
    {".sst", "Sunstar Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".stx", "Data Stitch Embroidery Format",      'U', ' ', EMBFORMAT_STITCHONLY},
    {".svg", "Scalable Vector Graphics",           'U', 'U', EMBFORMAT_OBJECTONLY},
    {".t01", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".t09", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".tap", "Happy Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".thr", "ThredWorks Embroidery Format",       'U', 'U', EMBFORMAT_STITCHONLY},
    {".txt", "Text File",                          ' ', 'U', EMBFORMAT_STITCHONLY},
    {".u00", "Barudan Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {".u01", "Barudan Embroidery Format",          ' ', ' ', EMBFORMAT_STITCHONLY},
    {".vip", "Pfaff Embroidery Format",            'U', ' ', EMBFORMAT_STITCHONLY},
    {".vp3", "Pfaff Embroidery Format",            'U', 'U', EMBFORMAT_STITCHONLY},
    {".xxx", "Singer Embroidery Format",           'U', 'U', EMBFORMAT_STITCHONLY},
    {".zsk", "ZSK USA Embroidery Format",          'U', ' ', EMBFORMAT_STITCHONLY},
    {"END",  "END",                                ' ', ' ', 0,                  }
};

int numberOfFormats = 61;

/**************************************************/
/* EmbFormatList                                  */
/**************************************************/

int embFormat_getExtension(const char *fileName, char *ending)
{
    int i;
    const char *offset;

    if (!fileName) {
        embLog_error("emb-format.c embFormat_getExtension(), fileName argument is null\n");
        return 0;
    }

    if (strlen(fileName) == 0) {
        return 0;
    }
    
    offset = strrchr(fileName, '.');
    if (offset==0) {
        return 0;
    }

    i = 0;
    while (offset[i] != '\0') {
        ending[i] = (char)tolower(offset[i]);
        ++i;
    }
    ending[i] = 0; /* terminate the string */

    return 1;
}

const char* embFormat_extensionFromName(const char* fileName)
{
    int i = 0;
    char ending[2 + EMBFORMAT_MAXEXT];
    const char* extension = 0;

    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }

    for (i=0; i<numberOfFormats; i++) {
        if (!strcmp(ending, formatTable[i].extension)) {
            extension = formatTable[i].extension;
            break;
        }
    }

    return extension;
}

const char* embFormat_descriptionFromName(const char* fileName)
{
    int i = 0;
    char ending[2 + EMBFORMAT_MAXEXT];
    const char* description = 0;

    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }

    for (i=0; i<numberOfFormats; i++) {
        if (!strcmp(ending, formatTable[i].extension)) {
            description = formatTable[i].description;
            break;
        }
    }

    return description;
}

char embFormat_readerStateFromName(const char* fileName)
{
    int i = 0;
    char ending[2 + EMBFORMAT_MAXEXT];
    char readerState = ' ';

    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }

    for (i=0; i<numberOfFormats; i++) {
        if (!strcmp(ending, formatTable[i].extension)) {
            readerState = formatTable[i].reader;
            break;
        }
    }

    return readerState;
}

char embFormat_writerStateFromName(const char* fileName)
{
    int i = 0;
    char ending[2 + EMBFORMAT_MAXEXT];
    char writerState = ' ';

    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }

    for (i=0; i<numberOfFormats; i++) {
        if (!strcmp(ending, formatTable[i].extension)) {
            writerState = formatTable[i].writer;
            break;
        }
    }

    return writerState;
}

int embFormat_typeFromName(const char* fileName)
{
    int i = 0;
    char ending[2 + EMBFORMAT_MAXEXT];
    int type = EMBFORMAT_UNSUPPORTED;

    if (!embFormat_getExtension(fileName, ending)) {
        return 0;
    }

    for (i=0; i<numberOfFormats; i++) {
        if (!strcmp(ending, formatTable[i].extension)) {
            type = formatTable[i].type;
            break;
        }
    }

    return type;
}


/* gcc -DTEST_EMB_FORMAT -o emb-format emb-format.c emb-logging.c */
#ifdef TEST_EMB_FORMAT

int main(void)
{
    const char*  tName = "example.zsk";

    printf("Filename   : %s\n"
           "Extension  : %s\n"
           "Description: %s\n"
           "Reader     : %c\n"
           "Writer     : %c\n"
           "Type       : %d\n\n",
            tName,
            embFormat_extensionFromName(tName),   /* .zsk */
            embFormat_descriptionFromName(tName), /* ZSK USA Embroidery Format */
            embFormat_readerStateFromName(tName), /* 'U' */
            embFormat_writerStateFromName(tName), /* ' ' */
            embFormat_typeFromName(tName)         /* 1 (EMBFORMAT_STITCHONLY) */
            );
    return 0;
}

#endif

