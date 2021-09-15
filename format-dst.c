/* .DST (Tajima) embroidery file read/write routines
 * Format comments are thanks to tspilman@dalcoathletic.com who's
 * notes appeared at http://www.wotsit.org under Tajima Format.
 */

#include "embroidery.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

/* returns the value of the n-th bit in a */
#define BIT(a, n) \
    ((a & (1 << n)) >> n)

/* returns the value of the n-th bit in a */
#define SETBIT(a, n) \
    a |= (1 << n)

/* TODO: review this then remove since emb-pattern.c has a similar function */
/* void combineJumpStitches(EmbPattern* p, int jumpsPerTrim)
{
    if(!p) { embLog("ERROR: format-dst.c combineJumpStitches(), p argument is null\n"); return; }
    EmbStitchList* pointer = p->stitchList;
    int jumpCount = 0;
    EmbStitchList* jumpListStart = 0;
    char needleDown = 0;
    while(pointer)
    {
        if((pointer->stitch.flags & JUMP) && !(pointer->stitch.flags & STOP))
        {
            if(jumpCount == 0)
            {
                jumpListStart = pointer;
            }
            jumpCount++;
            if(needleDown && jumpCount >= jumpsPerTrim)
            {
                EmbStitchList* removePointer = jumpListStart->next;
                jumpListStart->stitch.x = pointer->stitch.x;
                jumpListStart->stitch.y = pointer->stitch.y;
                jumpListStart->stitch.flags |= TRIM;
                jumpListStart->next = pointer;

                jumpCount-=2;
                for(; jumpCount > 0; jumpCount--)
                {
                    EmbStitchList* tempPointer = removePointer->next;
                    jumpListStart->stitch.flags |= removePointer->stitch.flags;
                    free(removePointer);
                    removePointer = 0;
                    removePointer = tempPointer;
                }
                jumpCount = 0;
                needleDown = 0;
            }
        }
        else
        {
            if(pointer->stitch.flags == NORMAL)
            {
                needleDown = 1;
                jumpCount = 0;
            }
        }
        pointer = pointer->next;
    }
}
*/

static void encode_record(EmbFile* file, int x, int y, int flags)
{
    char b[4];
    b[0] = b[1] = b[2] = 0;

    /* cannot encode values > +121 or < -121. */
    if (x > 121 || x < -121)
        embLog("ERROR: format-dst.c encode_record(), x is not in valid range [-121,121] , x =\n"); /* , x); */
    if (y > 121 || y < -121)
        embLog("ERROR: format-dst.c encode_record(), y is not in valid range [-121,121] , y = \n"); /* , y); */

    if (x >= +41) {
        SETBIT(b[2], 2);
        x -= 81;
    }
    if (x <= -41) {
        SETBIT(b[2], 3);
        x += 81;
    }
    if (x >= +14) {
        SETBIT(b[1], 2);
        x -= 27;
    }
    if (x <= -14) {
        SETBIT(b[1], 3);
        x += 27;
    }
    if (x >= +5) {
        SETBIT(b[0], 2);
        x -= 9;
    }
    if (x <= -5) {
        b[0] += 1 << 3;
        x += 9;
    }
    if (x >= +2) {
        b[1] += 1 << 0;
        x -= 3;
    }
    if (x <= -2) {
        b[1] += 1 << 1;
        x += 3;
    }
    if (x >= +1) {
        b[0] += 1 << 0;
        x -= 1;
    }
    if (x <= -1) {
        b[0] += 1 << 1;
        x += 1;
    }
    if (x != 0) {
        embLog("ERROR: format-dst.c encode_record(), x should be zero yet x = \n"); /*, x); */
    }
    if (y >= +41) {
        b[2] += 1 << 5;
        y -= 81;
    }
    if (y <= -41) {
        b[2] += 1 << 4;
        y += 81;
    }
    if (y >= +14) {
        b[1] += 1 << 5;
        y -= 27;
    }
    if (y <= -14) {
        b[1] += 1 << 4;
        y += 27;
    }
    if (y >= +5) {
        b[0] += 1 << 5;
        y -= 9;
    }
    if (y <= -5) {
        b[0] += 1 << 4;
        y += 9;
    }
    if (y >= +2) {
        b[1] += 1 << 7;
        y -= 3;
    }
    if (y <= -2) {
        b[1] += 1 << 6;
        y += 3;
    }
    if (y >= +1) {
        b[0] += 1 << 7;
        y -= 1;
    }
    if (y <= -1) {
        b[0] += 1 << 6;
        y += 1;
    }
    if (y != 0) {
        embLog("ERROR: format-dst.c encode_record(), y should be zero yet y = \n"); /* , y); */
    }

    b[2] |= (char)3;

    if (flags & END) {
        b[2] = (char)-13;
        b[0] = b[1] = (char)0;
    }

    /* if(flags & TRIM)
    {
        int v = 5;
        int dx = (int)(x/v), dy = (int)(y/v);
        for(i = 1; i < v; i++)
        {
            encode_record(file, dx, dy, JUMP);
        }
        encode_record(file, x - (dx * (v - 1)), y - (dy * (v - 1)), JUMP);
        return;
    } */
    if (flags & (JUMP | TRIM)) {
        b[2] = (char)(b[2] | 0x83);
    }
    if (flags & STOP) {
        b[2] = (char)(b[2] | 0xC3);
    }

    embFile_write(b, 1, 3, file);
}

/*convert 2 characters into 1 int for case statement */
/*#define cci(s) (s[0]*256+s[1]) */
#define cci(c1, c2) (c1 * 256 + c2)

static void set_dst_variable(EmbPattern* pattern, char* var, char* val)
{
    unsigned int i;
    EmbThread t;

    for (i = 0; i <= (unsigned int)strlen(var); i++) {
        /* uppercase the var */
        if (var[i] >= 'a' && var[i] <= 'z') {
            var[i] += 'A' - 'a';
        }
    }

    /* macro converts 2 characters to 1 int, allows case statement... */
    switch (cci(var[0], var[1])) {
    case cci('L', 'A'): /* Design Name (LA) */
        /*pattern->set_variable("Design_Name",val); TODO: review this line. */
        break;
    case cci('S', 'T'): /* Stitch count, 7 digits padded by leading 0's */
    case cci('C', 'O'): /* Color change count, 3 digits padded by leading 0's */
    case cci('+', 'X'): /* Design extents (+/-X,+/-Y), 5 digits padded by leading 0's */
    case cci('-', 'X'):
    case cci('+', 'Y'):
    case cci('-', 'Y'):
        /* don't store these variables, they are recalculated at save */
        break;
    case cci('A', 'X'): /* Relative coordinates of last point, 6 digits, padded with leading spaces, first char may be +/- */
    case cci('A', 'Y'):
    case cci('M', 'X'): /* Coordinates of last point in previous file of multi-volume design, 6 digits, padded with leading spaces, first char may be +/- */
    case cci('M', 'Y'):
        /* store these variables as-is, they will be converted to numbers and back at save; */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    case cci('P', 'D'):
        /* store this string as-is, it will be saved as-is, 6 characters */
        if (strlen(val) != 6) {
            /*pattern->messages.add("Warning: in DST file read, PD is not 6 characters, but ",(int)strlen(val)); */
        }
        /*pattern->set_variable(var,val);*/
        break;
        /* Begin extended fields section */
    case cci('A', 'U'): /* Author string, arbitrary length */
    case cci('C', 'P'): /* Copyright string, arbitrary length */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    case cci('T', 'C'): /*Thread Color: #RRGGBB,Description,Catalog Number (1st field RGB hex values, 2nd&3rd fields optional arbitrary length) */
        /* TODO: review these lines below.
        description=split_cell_str(val,2);
        catalog_number=split_cell_str(val,3);
        */
        t.color = embColor_fromHexStr(val);
        t.description = "";
        t.catalogNumber = "";
        embPattern_addThread(pattern, t);
        break;
    default:
        /* unknown field, just save it. */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    }
}

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int readDst(EmbPattern* pattern, const char* fileName)
{
    char var[3]; /* temporary storage variable name */
    char val[512]; /* temporary storage variable value */
    int valpos;
    unsigned char b[3];
    char header[512 + 1];
    EmbFile* file = 0;
    int i = 0;
    int flags; /* for converting stitches from file encoding */

    /*
    * The header seems to contain information about the design.
    * Seems to be ASCII text delimited by 0x0D (carriage returns).
    * This must be in the file for most new software or hardware
    * to consider it a good file! This is much more important
    * than I originally believed. The header is 125 bytes in
    * length and padded out by 0x20 to 512 bytes total.
    * All entries in the header seem to be 2 ASCII characters
    * followed by a colon, then it's value trailed by a carriage return.
    *
    * char LA[16+1];  First is the 'LA' entry, which is the design name with no
    *                 path or extension information. The blank is 16 characters
    *                 in total, but the name must not be longer that 8 characters
    *                 and padded out with 0x20.
    *
    * char ST[7+1];   Next is the stitch count ST, this is a 7 digit number
    *                 padded by leading zeros. This is the total stitch count
    *                 including color changes, jumps, nups, and special records.
    *
    * char CO[3+1];   Next, is CO or colors, a 3 digit number padded by leading
    *                 zeros. This is the number of color change records in the file.
    *
    * char POSX[5+1]; Next is +X or the positive X extent in centimeters, a 5
    *                 digit non-decimal number padded by leading zeros.
    *
    * char NEGX[5+1]; Following is the -X or the negative X extent in millimeters,
    *                 a 5 digit non-decimal number padded by leading zeros.
    *
    * char POSY[5+1]; Again, the +Y extents.
    *
    * char NEGY[5+1]; Again, the -Y extents.
    *
    * char AX[6+1];   AX and AY should express the relative coordinates of the
    * char AY[6+1];   last point from the start point in 0.1 mm. If the start
    *                 and last points are the same, the coordinates are (0,0).
    *
    * char MX[6+1];   MX and MY should express coordinates of the last point of
    * char MY[6+1];   the previous file for a multi-volume design. A multi-
    *                 volume design means a design consisted of two or more files.
    *                 This was used for huge designs that can not be stored in a
    *                 single paper tape roll. It is not used so much (almost
    *                 never) nowadays.
    *
    * char PD[9+1];   PD is also storing some information for multi-volume design.
    */

    /* TODO: review commented code below
    pattern->clear();
    pattern->set_variable("file_name",filename);
    */

    if (!validateReadPattern(pattern, fileName, "readDst"))
        return 0;

    file = embFile_open(fileName, "rb", 0);
    if (!file)
        return 0;

    embPattern_loadExternalColorFile(pattern, fileName);
    /* READ 512 BYTE HEADER INTO header[] */
    for (i = 0; i < 512; i++) {
        header[i] = (char)embFile_getc(file);
    }

    /*TODO:It would probably be a good idea to validate file before accepting it. */

    /* fill variables from header fields */
    for (i = 0; i < 512; i++) {
        if (header[i] == ':' && i > 1) {
            var[0] = header[i - 2];
            var[1] = header[i - 1];
            var[2] = '\0';
            valpos = i + 1;
            for (i++; i < 512; i++) {
                /* don't accept : without CR because there's a bug below: i-valpos must be > 0 which is not the case if the : is before the third character. */
                if (header[i] == 13 /*||header[i]==':'*/) /* 0x0d = carriage return */
                {
                    if (header[i] == ':') /* : indicates another variable, CR was missing! */
                    {
                        i -= 2;
                    }
                    strncpy(val, &header[valpos], (size_t)(i - valpos));
                    val[i - valpos] = '\0';
                    set_dst_variable(pattern, var, val);
                    break;
                }
            }
        }
    }

    while (embFile_read(b, 1, 3, file) == 3) {
        int x;
        int y;
        /* A version of the stitch decoding with less branching,
         * the BIT macro returns either 0 or 1 based on the value
         * of that bit and then is multiplied by what value that represents.
         */
        if (b[2] == 0xF3) {
            break;
        }
        x  =     BIT(b[0], 1) - BIT(b[0], 2);
        x +=  9*(BIT(b[0], 3) - BIT(b[0], 4));
        y  =     BIT(b[0], 8) - BIT(b[0], 7);
        y +=  9*(BIT(b[0], 6) - BIT(b[0], 5));
        x +=  3*(BIT(b[1], 1) - BIT(b[1], 2));
        x += 27*(BIT(b[1], 3) - BIT(b[1], 4));
        y +=  3*(BIT(b[1], 8) - BIT(b[1], 7));
        y += 27*(BIT(b[1], 6) - BIT(b[1], 5));
        x += 81*(BIT(b[2], 3) - BIT(b[2], 4));
        y += 81*(BIT(b[2], 6) - BIT(b[2], 5));

        flags = (BIT(b[2], 8) * JUMP) | (BIT(b[2], 7) * STOP);
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
    }
    embFile_close(file);

    embPattern_end(pattern);

    /* combineJumpStitches(pattern, 5); */
    return 1;
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int writeDst(EmbPattern* pattern, const char* fileName)
{
    EmbRect boundingRect;
    EmbFile* file = 0;
    int xx, yy, dx, dy, flags, i, ax, ay, mx, my;
    char* pd = 0;
    EmbStitch st;

    if (!validateWritePattern(pattern, fileName, "writeDst"))
        return 0;

    file = embFile_open(fileName, "wb", 0);
    if (!file)
        return 0;

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    /* TODO: make sure that pattern->threads->count defaults to 1 in new patterns */
    flags = NORMAL;
    boundingRect = embPattern_calcBoundingBox(pattern);
    /* TODO: review the code below
    if(pattern->get_variable("design_name") != NULL)
    {
    char *la = stralloccopy(pattern->get_variable("design_name"));
    if(strlen(la)>16) la[16]='\0';

    embFile_print(file,"LA:%-16s\x0d",la);
    free(la);
    }
    else
    {
    */
    /* pad to 16 char */
    embFile_print(file, "LA:Untitled        \x0d");
    /*} */
    /* TODO: check that the number of characters adds to 125, or pad
    correctly. */
    embFile_print(file, "ST:");
    writeInt(file, pattern->stitchList->count, 6);
    embFile_print(file, "\x0dCO:");
    writeInt(file, pattern->threads->count - 1, 6); /* number of color changes, not number of colors! */
    embFile_print(file, "\x0d+X:");
    writeInt(file, (int)(boundingRect.right * 10.0), 6);
    embFile_print(file, "\x0d-X:");
    writeInt(file, (int)(fabs(boundingRect.left) * 10.0), 6);
    embFile_print(file, "\x0d+Y:");
    writeInt(file, (int)(boundingRect.bottom * 10.0), 6);
    embFile_print(file, "\x0d-Y:");
    writeInt(file, (int)(fabs(boundingRect.top) * 10.0), 6);
    embFile_print(file, "\x0d");

    ax = ay = mx = my = 0;
    /* TODO: review the code below */
    /*ax=pattern->get_variable_int("ax"); */ /* will return 0 if not defined */
    /*ay=pattern->get_variable_int("ay"); */
    /*mx=pattern->get_variable_int("mx"); */
    /*my=pattern->get_variable_int("my"); */

    /*pd=pattern->get_variable("pd");*/ /* will return null pointer if not defined */
    pd = 0;
    if (pd == 0 || strlen(pd) != 6) {
        /* pd is not valid, so fill in a default consisting of "******" */
        pd = "******";
    }
    embFile_print(file, "AX:+");
    writeInt(file, ax, 6);
    embFile_print(file, "\x0dAY:+");
    writeInt(file, ay, 6);
    embFile_print(file, "\x0dMX:+");
    writeInt(file, mx, 6);
    embFile_print(file, "\x0dMY:+");
    writeInt(file, my, 6);
    embFile_print(file, "\x0dPD:");
    embFile_print(file, pd); /* 6 char, swap for embFile_write */
    embFile_print(file, "\x0d\x1a"); /* 0x1a is the code for end of section. */

    embFile_pad(file, ' ', 512-125);

    /* write stitches */
    xx = yy = 0;
    for (i = 0; i < pattern->stitchList->count; i++) {
        st = pattern->stitchList->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = roundDouble(st.x * 10.0) - xx;
        dy = roundDouble(st.y * 10.0) - yy;
        xx = roundDouble(st.x * 10.0);
        yy = roundDouble(st.y * 10.0);
        encode_record(file, dx, dy, st.flags);
    }
    /* finish file with a terminator character */
    embFile_write("\xA1\0\0", 1, 3, file);
    embFile_close(file);
    return 1;
}

