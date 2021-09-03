#include "embroidery.h"

static int decodeNewStitch(unsigned char value)
{
    return (int)value;
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readNew(EmbPattern* pattern, const char* fileName)
{
    unsigned int stitchCount;
    unsigned char data[3];
    EmbFile* file;

    if (!validateReadPattern(pattern, fileName, "readNew")) return 0;

    file = embFile_open(fileName, "rb", 0);
    if (!file) return 0;

    embPattern_loadExternalColorFile(pattern, fileName);
    stitchCount = binaryReadUInt16(file);
    while(binaryReadBytes(file, data, 3) == 3)
    {
        int x = decodeNewStitch(data[0]);
        int y = decodeNewStitch(data[1]);
        int flag = NORMAL;
        char val = data[2];
        if(data[2] & 0x40)
        {
            x = -x;
        }
        if(data[2] & 0x20)
        {
            y = -y;
        }
        if(data[2] & 0x10)
        {
            flag = TRIM;
        }
        if(data[2] & 0x01)
        {
            flag = JUMP;
        }
        if((val & 0x1E) == 0x02)
        {
            flag = STOP;
        }
        /* Unknown values, possibly TRIM
        155 = 1001 1011 = 0x9B
        145 = 1001 0001 = 0x91
        */
        /*val = (data[2] & 0x1C);
        if(val != 0 && data[2] != 0x9B && data[2] != 0x91)
        {
            int z = 1;
        }*/
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flag, 1);
    }

    embFile_close(file);
    embPattern_end(pattern);

    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeNew(EmbPattern* pattern, const char* fileName)
{
    EmbFile* file;
    if (!validateWritePattern(pattern, fileName, "writeNew")) {
        return 0;
    }
    file = embFile_open(fileName, "wb", 0);
    if (!file) return 0;

    embFile_close(file);
    return 0; /*TODO: finish writeNew */
}

