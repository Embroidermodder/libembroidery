#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readDsz(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file = 0;

    if (!validateReadPattern(pattern, fileName, "readDsz")) return 0;

    file = embFile_open(fileName, "rb", 0);
    if (!file) return 0;

    embPattern_loadExternalColorFile(pattern, fileName);

    embFile_seek(file, 0x200, SEEK_SET);
    while(1)
    {
        int x, y;
        unsigned char ctrl;
        int stitchType = NORMAL;

        y = embFile_getc(file);
        if(feof(file->file)) break;
        x = embFile_getc(file);
        if(feof(file->file)) break;
        ctrl = (unsigned char)embFile_getc(file);
        if(feof(file->file)) break;
        if(ctrl & 0x01) stitchType = TRIM;
        if(ctrl & 0x20) y = -y;
        if(ctrl & 0x40) x = -x;

        if(ctrl & 0x0E)
        {
            int headNumber = (ctrl & 0x0E) >> 1;
            stitchType = STOP;
        }
        if(ctrl & 0x10)
        {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x  / 10.0, y  / 10.0, stitchType, 1);
    }
    embFile_close(file);

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeDsz(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeDsz")) return 0;

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writeDsz */
}

