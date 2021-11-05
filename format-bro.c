#include "embroidery.h"

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readBro(EmbPattern* pattern, const char* fileName)
{
    unsigned char x55;
    short unknown1, unknown2, unknown3, unknown4, moreBytesToEnd;
    char name[8];
    int stitchType;
    FILE* file;

    if (!validateReadPattern(pattern, fileName, "readBro")) return 0;

    file = fopen(fileName, "rb");
    if (!file) {
        printf("Failed to open file with name: %s.", fileName);
        return 0;
    }

    embPattern_loadExternalColorFile(pattern, fileName);

    fread(&x55, 1, 1, file);
    fread(&unknown1, 2, 1, file); /* TODO: determine what this unknown data is */

    fread(name, 1, 8, file);
    fread(&unknown2, 2, 1, file); /* TODO: determine what this unknown data is */
    fread(&unknown3, 2, 1, file); /* TODO: determine what this unknown data is */
    fread(&unknown4, 2, 1, file); /* TODO: determine what this unknown data is */
    fread(&moreBytesToEnd, 2, 1, file);

    fseek(file, 0x100, SEEK_SET);

    while(1)
    {
        short b1, b2;
        stitchType = NORMAL;
        b1 = (unsigned char)fgetc(file);
        b2 = (unsigned char)fgetc(file);
        if(b1 == -128)
        {
            unsigned char bCode = (unsigned char)fgetc(file);
            fread(&b1, 2, 1, file);
            fread(&b2, 2, 1, file);
            if(bCode == 2)
            {
                stitchType = STOP;
            }
            else if(bCode == 3)
            {
                stitchType = TRIM;
            }
            else if(bCode == 0x7E)
            {
                embPattern_addStitchRel(pattern, 0, 0, END, 1);
                break;
            }
        }
        embPattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1);
    }
    fclose(file);

    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeBro(EmbPattern* pattern, const char* fileName)
{
    if (!validateWritePattern(pattern, fileName, "writeBro")) return 0;

    /* TODO: embFile_open() needs to occur here after the check for no stitches */

    return 0; /*TODO: finish writeBro */
}

