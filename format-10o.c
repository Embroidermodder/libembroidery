#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char read10o(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file;

    if (!validateReadPattern(pattern, fileName, "read10o")) return 0;

    file = embFile_open(fileName, "rb", 0);
    if (!file) return 0;

    embPattern_loadExternalColorFile(pattern, fileName);

    while(1)
    {
        int x, y;
        int stitchType = NORMAL;
        unsigned char ctrl = (unsigned char)embFile_getc(file);
        if(feof(file->file))
            break;
        y = embFile_getc(file);
        if(feof(file->file))
            break;
        x = embFile_getc(file);
        if(feof(file->file))
            break;
        if(ctrl & 0x20)
            x = -x;
        if(ctrl & 0x40)
            y = -y;
        if(ctrl & 0x01)
            stitchType = TRIM;
        if((ctrl & 0x5) == 5)
        {
            stitchType = STOP;
        }
        if(ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87)
        {
            embPattern_addStitchRel(pattern, 0, 0, END, 1);
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1);
    }
    embFile_close(file);

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char write10o(EmbPattern* pattern, const char* fileName)
{
    EmbFile *file;
    if (!validateWritePattern(pattern, fileName, "write10o")) return 0;

    file = embFile_open(fileName, "rb", 0);
    if (!file) return 0;

    embFile_close(file);
    return 0; /*TODO: finish write10o */
}

