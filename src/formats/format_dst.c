/*
 * DST FORMAT
 * This file is part of libembroidery.
 *
 * Copyright 2018-2023 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../embroidery_internal.h"

/**
 * \file format_dst.c
 *
 * .DST (Tajima) embroidery file read/write routines
 * Format comments are thanks to tspilman@dalcoathletic.com who's
 * notes appeared at http://www.wotsit.org under Tajima Format.

\subsection tajima-dst-format Tajima Embroidery Format (.dst)
\addindex dst
\addindex Tajima

* Stitch Only Format.
* [X] Basic Read Support
* [X] Basic Write Support
* [ ] Well Tested Read
* [ ] Well Tested Write

.DST (Tajima) embroidery file read/write routines
Format comments are thanks to [tspilman@dalcoathletic.com](tspilman@dalcoathletic.com) who's
notes appeared at [http://www.wotsit.org](http://www.wotsit.org) under Tajima Format.

Other references: \cite kde_tajima , \cite acatina .

\subsubsection dst-header Header

The header contains general information about the design. It is in lines of ASCII, so if you open a DST file as a text file, it's the only part that's easy to read. The line ending symbol is  `0x0D}. The header is necessary for the file to be read by most softwares and hardwares.

The header is 125 bytes of data followed by padding spaces to make it 512 bytes in total.

The lines are as follows.

| *Label* | *Size* | *Description* | *Example* |
|----|----|----|----|
| `LA:` | 17 | The design name with no path or extension. The space reserved is 16 characters, but the name must not be longer than 8 and be padded to 16 with spaces (0x20). | `"LA:Star            "` |
| `ST:` | 8 | The stitch count. An integer in the format `%07d`, that is: a 7 digit number padded by leading zeros. This is the total accross all possible stitch flags. | |
| `CO:` | 4 | The number of color changes (not to be confused with thread count, an all black design we would have the record \textbf{000}). An integer in the format  `%03d`, that is: a 3 digit number padded by leading zeros. | |
| `+X:` | 6 | The extent of the pattern in the postitive x direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit number padded by leading zeros. | |
| `-X:` | 6 | The extent of the pattern in the negative x direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit integer padded by leading zeros. | |
| `+Y:` | 6 | The extent of the pattern in the postitive y direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit integer padded by leading zeros. | |
| `-Y:` | 6 | The extent of the pattern in the negative y direction in millimeters. An integer in the format  `%05d`, that is: a 5 digit integer padded by leading zeros. | |
| `AX:` | 7 | The difference of the end from the start in the x direction in 0.1mm, the first char should be the sign, followed by an integer in the format `%05d`, that is: a 5 digit integer padded by leading zeros. | |
| `AY:` | 7 | The difference of the end from the start in the y direction in 0.1mm, the first char should be the sign, followed by an integer in the format `%05d`, that is: a 5 digit integer padded by leading zeros. | |
| `MX:` | 7 | The x co-ordinate of the last point in the previous file should the design span multiple files. Like AX, it is the sign, followed by a 5 digit integer. If we have a one file design set it to zero. | |
| `MY:` | 7 | The y co-ordinate of the last point in the previous file should the design span multiple files. Like AY, it is the sign, followed by a 5 digit integer. If we have a one file design set it to zero. | |
| `PD:` | 10 | Information about multivolume designs. | |

\subsubsection dst-stitch-data Stitch Data

Uses 3 byte per stitch encoding with the format as follows:

| *Bit* | *7* | *6* | *5* | *4* | *3* | *2* | *1* | *0* |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|
| Byte 0 | y+1 | y-1 | y+9 | y-9 | x-9 | x+9 | x-1 | x+1 |
| Byte 1 | y+3 | y-3 | y+27 | y-27 | x-27 | x+27 | x-3 | x+3 |
| Byte 2 | jump | color change | y+81 | y-81 | x-81 | x+81 | set | set |

T01 and Tap appear to use Tajima Ternary.

Where the stitch type is determined as:

* Normal Stitch `0b00000011 0x03`
* Jump Stitch `0b10000011 0x83`
* Stop/Change Color `0b11000011 0xC3`
* End Design `0b11110011 0xF3`

Inclusive or'ed with the last byte.

Note that the max stitch length is the largest sum of $1+3+9+27+81=121$ where the unit length is 0.1mm so 12.1mm. The coordinate system is right handed.
 *
 */

int decode_record_flags(unsigned char b2)
{
    if (b2 == 0xF3) {
        return END;
    }
    if (b2 & 0x40) {
        return STOP;
    }
    if (b2 & 0x80) {
        return JUMP;
    }
    return NORMAL;
}

/* TODO: review this then remove since emb-pattern.c has a similar function */
/* void combineJumpStitches(EmbPattern* p, int jumpsPerTrim)
{
    if (!p) { printf("ERROR: format-dst.c combineJumpStitches(), p argument is null\n"); return; }
    Embstitch_list* pointer = p->stitch_list;
    int jumpCount = 0;
    Embstitch_list* jumpListStart = 0;
    char needleDown = 0;
    while (pointer) {
        if ((pointer->stitch.flags & JUMP) && !(pointer->stitch.flags & STOP)) {
            if (jumpCount == 0)
            {
                jumpListStart = pointer;
            }
            jumpCount++;
            if (needleDown && jumpCount >= jumpsPerTrim)
            {
                Embstitch_list* removePointer = jumpListStart->next;
                jumpListStart->stitch.x = pointer->stitch.x;
                jumpListStart->stitch.y = pointer->stitch.y;
                jumpListStart->stitch.flags |= TRIM;
                jumpListStart->next = pointer;

                jumpCount-=2;
                for (; jumpCount > 0; jumpCount--)
                {
                    Embstitch_list* tempPointer = removePointer->next;
                    jumpListStart->stitch.flags |= removePointer->stitch.flags;
                    safe_free(removePointer);
                    removePointer = 0;
                    removePointer = tempPointer;
                }
                jumpCount = 0;
                needleDown = 0;
            }
        }
        else {
            if (pointer->stitch.flags == NORMAL)
            {
                needleDown = 1;
                jumpCount = 0;
            }
        }
        pointer = pointer->next;
    }
}
*/

void
encode_record(FILE* file, int x, int y, int flags)
{
    unsigned char b[3];
    encode_tajima_ternary(b, x, y);

    b[2] |= 0x03;

    if (flags & END) {
        /* 0b10001101 = -13 = 0x8D */
        b[0] = 0;
        b[1] = 0;
        b[2] = 0x8D;
    }

    /* make the variable v configurable for the pattern */
    if (flags & TRIM) {
        int dx, dy, i, v = 5;
        dx = x/v;
        dy = y/v;
        for (i = 1; i < v; i++) {
            encode_record(file, dx, dy, JUMP);
        }
        encode_record(file, x - (dx * (v - 1)), y - (dy * (v - 1)), JUMP);
        return;
    }
    if (flags & (JUMP | TRIM)) {
        b[2] = (char) (b[2] | 0x83);
    }
    if (flags & STOP) {
        b[2] = (char) (b[2] | 0xC3);
    }

    fwrite(b, 1, 3, file);
}

/*convert 2 characters into 1 int for case statement */
/*#define cci(s) (s[0]*256+s[1]) */
#define cci(c1,c2) (c1*256+c2)

void
set_dst_variable(EmbPattern* pattern, char* var, char* val) {
    unsigned int i;
    EmbThread t;
    for (i = 0; i <= (unsigned int)strlen(var); i++) {
        /* uppercase the var */
        if (var[i] >= 'a' && var[i] <= 'z') {
            var[i] += 'A' - 'a';
        }
    }

    /* macro converts 2 characters to 1 int, allows case statement... */
    switch(cci(var[0],var[1])) {
    case cci('L','A'): /* Design Name (LA) */
        /*pattern->set_variable("Design_Name",val); TODO: review this line. */
        break;
    case cci('S','T'): /* Stitch count, 7 digits padded by leading 0's */
    case cci('C','O'): /* Color change count, 3 digits padded by leading 0's */
    case cci('+','X'): /* Design extents (+/-X,+/-Y), 5 digits padded by leading 0's */
    case cci('-','X'):
    case cci('+','Y'):
    case cci('-','Y'):
        /* don't store these variables, they are recalculated at save */
        break;
    case cci('A','X'): /* Relative coordinates of last point, 6 digits, padded with leading spaces, first char may be +/- */
    case cci('A','Y'):
    case cci('M','X'): /* Coordinates of last point in previous file of multi-volume design, 6 digits, padded with leading spaces, first char may be +/- */
    case cci('M','Y'):
        /* store these variables as-is, they will be converted to numbers and back at save; */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    case cci('P','D'):
        /* store this string as-is, it will be saved as-is, 6 characters */
        if (strlen(val) != 6) {
            /*pattern->messages.add("Warning: in DST file read,
                PD is not 6 characters, but ",(int)strlen(val)); */
        }
        /*pattern->set_variable(var,val);*/
        break;
        /* Begin extended fields section */
    case cci('A','U'): /* Author string, arbitrary length */
    case cci('C','P'): /* Copyright string, arbitrary length */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
        /*Thread Color: #RRGGBB,Description,Catalog Number (1st field RGB
            hex values, 2nd&3rd fields optional arbitrary length) */
    case cci('T','C'):
        /* TODO: review these lines below.
        description=split_cell_str(val,2);
        catalog_number=split_cell_str(val,3);
        */
        t.color = embColor_fromHexStr(val);
        strcpy(t.description, "");
        strcpy(t.catalogNumber, "");
        embPattern_addThread(pattern, t);
        break;
    default:
        /* unknown field, just save it. */
        /*pattern->set_variable(var,val); TODO: review this line. */
        break;
    }
}

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
char
readDst(EmbPattern* pattern, FILE* file) {
    char var[3];   /* temporary storage variable name */
    char val[512]; /* temporary storage variable value */
    int valpos;
    unsigned char b[3];
    char header[512 + 1];
    int i = 0, flags;

    /* TODO: review commented code below
    pattern->clear();
    pattern->set_variable("file_name",filename);
    */

    fread(header, 1, 512, file);

    /*TODO:It would probably be a good idea to
        validate file before accepting it. */
    /* fill variables from header fields */
    for (i = 0; i < 512; i++) {
        if (header[i] == ':' && i > 1) {
            var[0] = header[i - 2];
            var[1] = header[i - 1];
            var[2] = '\0';
            valpos = i + 1;
            for (i++; i < 512; i++)
            {
                /* don't accept : without CR because there's a bug below: i-valpos must be > 0 which is not the case if the : is before the third character. */
                if (header[i] == 13/*||header[i]==':'*/) { /* 0x0d = carriage return */
                    /* : indicates another variable, CR was missing! */
                    if (header[i] == ':') {
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

    while (fread(b, 1, 3, file) == 3) {
        int x, y;
        decode_tajima_ternary(b, &x, &y);
        flags = decode_record_flags(b[2]);
        if (flags == END) {
            break;
        }
        embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flags, 1);
    }

    /* combineJumpStitches(pattern, 5); */
    return 1;
}

char
writeDst(EmbPattern* pattern, FILE* file) {
    EmbRect boundingRect;
    int i, ax, ay, mx, my;
    EmbVector pos;
    char pd[10];

    embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1);

    /* TODO: make sure that pattern->thread_list->count
     * defaults to 1 in new patterns */
    boundingRect = embPattern_calcBoundingBox(pattern);
    /* TODO: review the code below
    if (pattern->get_variable("design_name") != NULL) {
        char *la = stralloccopy(pattern->get_variable("design_name"));
        if (strlen(la)>16) la[16]='\0';

        fprintf(file,"LA:%-16s\x0d",la);
        safe_free(la);
    }
    */
    fprintf(file, "LA:%-16s\x0d", "Untitled");
    fprintf(file, "ST:%7d\x0d", pattern->stitch_list->count);
    /* number of color changes, not number of colors! */
    fprintf(file, "CO:%3d\x0d", pattern->thread_list->count - 1);
    fprintf(file,
        "+X:%5d\x0d"
        "-X:%5d\x0d"
        "+Y:%5d\x0d"
        "-Y:%5d\x0d",
        (int)(boundingRect.right * 10.0),
        (int)(fabs(boundingRect.left) * 10.0),
        (int)(boundingRect.bottom * 10.0),
        (int)(fabs(boundingRect.top) * 10.0));

    ax = ay = mx = my = 0;
    /* TODO: review the code below */
    /*ax=pattern->get_variable_int("ax"); */ /* will return 0 if not defined */
    /*ay=pattern->get_variable_int("ay"); */
    /*mx=pattern->get_variable_int("mx"); */
    /*my=pattern->get_variable_int("my"); */

    /*pd=pattern->get_variable("pd");*/ /* will return null pointer if not defined */
   /* pd = 0;
    if (pd == 0 || strlen(pd) != 6) { */
        /* pd is not valid, so fill in a default consisting of "******" */
        strcpy(pd, "******");
    /*}*/
    fprintf(file,
        "AX:+%5d\x0d"
        "AY:+%5d\x0d"
        "MX:+%5d\x0d"
        "MY:+%5d\x0d"
        "PD:%6s\x0d\x1a",
        ax, ay, mx, my, pd);

    /* pad out header to proper length */
    fpad(file, ' ', 512-125);

    /* write stitches */
    pos.x = 0.0;
    pos.y = 0.0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch st;
        int dx, dy;
        st = pattern->stitch_list->stitch[i];
        /* convert from mm to 0.1mm for file format */
        dx = (int)emb_round(10.0*(st.x - pos.x));
        dy = (int)emb_round(10.0*(st.y - pos.y));
        pos.x += 0.1*dx;
        pos.y += 0.1*dy;
        if (emb_verbose > 0) {
            printf("%d %f %f %d %d %f %f %d\n", i, st.x, st.y, dx, dy, pos.x, pos.y, st.flags);
        }
        encode_record(file, dx, dy, st.flags);
    }

    /* Finish file with a terminator character and two zeros to
     * keep the post header part a multiple of three.
     */
    fwrite("\xa1\0\0", 1, 3, file);
    return 1;
}

