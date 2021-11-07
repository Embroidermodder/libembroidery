#include "embroidery.h"
#include <stdio.h>

const EmbThread jefThreads[] = {
    {{0, 0, 0}, "Placeholder", "000"},
    {{0, 0, 0}, "Black", "002"},
    {{255, 255, 255}, "White", "001"},
    {{255, 255, 23}, "Yellow", "204"},
    {{255, 102, 0}, "Orange", "203"},
    {{47, 89, 51}, "Olive Green", "219"},
    {{35, 115, 54}, "Green", "226"},
    {{101, 194, 200}, "Sky", "217"},
    {{171, 90, 150}, "Purple", "208"},
    {{246, 105, 160}, "Pink", "201"},
    {{255, 0, 0}, "Red", "225"},
    {{177, 112, 78}, "Brown", "214"},
    {{11, 47, 132}, "Blue", "207"},
    {{228, 195, 93}, "Gold", "003"},
    {{72, 26, 5}, "Dark Brown", "205"},
    {{172, 156, 199}, "Pale Violet", "209"},
    {{252, 242, 148}, "Pale Yellow", "210"},
    {{249, 153, 183}, "Pale Pink", "211"},
    {{250, 179, 129}, "Peach", "212"},
    {{201, 164, 128}, "Beige", "213"},
    {{151, 5, 51}, "Wine Red", "215"},
    {{160, 184, 204}, "Pale Sky", "216"},
    {{127, 194, 28}, "Yellow Green", "218"},
    {{229, 229, 229}, "Silver Gray", "220"},
    {{136, 155, 155}, "Gray", "221"},
    {{152, 214, 189}, "Pale Aqua", "227"},
    {{178, 225, 227}, "Baby Blue", "228"},
    {{54, 139, 160}, "Powder Blue", "229"},
    {{79, 131, 171}, "Bright Blue", "230"},
    {{56, 106, 145}, "Slate Blue", "231"},
    {{7, 22, 80}, "Navy Blue", "232"},
    {{249, 153, 162}, "Salmon Pink", "233"},
    {{249, 103, 107}, "Coral", "234"},
    {{227, 49, 31}, "Burnt Orange", "235"},
    {{226, 161, 136}, "Cinnamon", "236"},
    {{181, 148, 116}, "Umber", "237"},
    {{228, 207, 153}, "Blond", "238"},
    {{255, 203, 0}, "Sunflower", "239"},
    {{225, 173, 212}, "Orchid Pink", "240"},
    {{195, 0, 126}, "Peony Purple", "241"},
    {{128, 0, 75}, "Burgundy", "242"},
    {{84, 5, 113}, "Royal Purple", "243"},
    {{177, 5, 37}, "Cardinal Red", "244"},
    {{202, 224, 192}, "Opal Green", "245"},
    {{137, 152, 86}, "Moss Green", "246"},
    {{92, 148, 26}, "Meadow Green", "247"},
    {{0, 49, 20}, "Dark Green", "248"},
    {{93, 174, 148}, "Aquamarine", "249"},
    {{76, 191, 143}, "Emerald Green", "250"},
    {{0, 119, 114}, "Peacock Green", "251"},
    {{89, 91, 97}, "Dark Gray", "252"},
    {{255, 255, 242}, "Ivory White", "253"},
    {{177, 88, 24}, "Hazel", "254"},
    {{203, 138, 7}, "Toast", "255"},
    {{152, 108, 128}, "Salmon", "256"},
    {{152, 105, 45}, "Cocoa Brown", "257"},
    {{77, 52, 25}, "Sienna", "258"},
    {{76, 51, 11}, "Sepia", "259"},
    {{51, 32, 10}, "Dark Sepia", "260"},
    {{82, 58, 151}, "Violet Blue", "261"},
    {{13, 33, 126}, "Blue Ink", "262"},
    {{30, 119, 172}, "Sola Blue", "263"},
    {{178, 221, 83}, "Green Dust", "264"},
    {{243, 54, 137}, "Crimson", "265"},
    {{222, 100, 158}, "Floral Pink", "266"},
    {{152, 65, 97}, "Wine", "267"},
    {{76, 86, 18}, "Olive Drab", "268"},
    {{76, 136, 31}, "Meadow", "269"},
    {{228, 222, 121}, "Mustard", "270"},
    {{203, 138, 26}, "Yellow Ocher", "271"},
    {{203, 162, 28}, "Old Gold", "272"},
    {{255, 152, 5}, "Honey Dew", "273"},
    {{252, 178, 87}, "Tangerine", "274"},
    {{0xFF, 0xE5, 0x05}, "Canary Yellow", "275"},
    {{0xF0, 0x33, 0x1F}, "Vermilion", "202"},
    {{0x1A, 0x84, 0x2D}, "Bright Green", "206"},
    {{0x38, 0x6C, 0xAE}, "Ocean Blue", "222"},
    {{0xE3, 0xC4, 0xB4}, "Beige Gray", "223"},
    {{0xE3, 0xAC, 0x81}, "Bamboo", "224"}
};

#define HOOP_126X110 0
#define	HOOP_110X110 1
#define	HOOP_50X50   2
#define	HOOP_140X200 3
#define HOOP_230X200 4

static int jefGetHoopSize(int width, int height)
{
    if(width <  50 && height <  50) { return HOOP_50X50; }
    if(width < 110 && height < 110) { return HOOP_110X110; }
    if(width < 140 && height < 200) { return HOOP_140X200; }
    return ((int) HOOP_110X110);
}
static char jefDecode(unsigned char inputByte)
{
    if(inputByte >= 0x80)
        return (char) ((-~inputByte) - 1);
    return ((char) inputByte);
}
static void jefSetHoopFromId(EmbPattern* pattern, int hoopCode)
{
    if(!pattern) { printf("ERROR: format-jef.c jefSetHoopFromId(), pattern argument is null\n"); return; }

    switch(hoopCode)
    {
        case HOOP_126X110:
            pattern->hoop.height = 126.0;
            pattern->hoop.width = 110.0;
            break;
        case HOOP_50X50:
            pattern->hoop.height = 50.0;
            pattern->hoop.width = 50.0;
            break;
        case HOOP_110X110:
           pattern->hoop.height = 110.0;
            pattern->hoop.width = 110.0;
            break;
        case HOOP_140X200:
            pattern->hoop.height = 140.0;
            pattern->hoop.width = 200.0;
            break;
        case HOOP_230X200:
            pattern->hoop.height = 230.0;
            pattern->hoop.width = 200.0;
            break;
    }
}

struct hoop_padding
{
    int left;
    int right;
    int top;
    int bottom;
};

/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
char readJef(EmbPattern* pattern, const char* fileName)
{
    int stitchOffset, formatFlags, numberOfColors, numberOfStitchs;
    int hoopSize, i;
    struct hoop_padding bounds, rectFrom110x110, rectFrom50x50, rectFrom200x140, rect_from_custom;
    int stitchCount;
    char date[8], time[8];
  
    EmbFile* file = 0;
 
    unsigned char b0 = 0, b1 = 0;
    char dx = 0, dy = 0;
    int flags = 0;

    if (!validateReadPattern(pattern, fileName, "readJef")) {
        return 0;
    }

    file = embFile_open(fileName, "rb", 0);
    if (!file) {
        return 0;
    }

    stitchOffset = binaryReadInt32(file);
    formatFlags = binaryReadInt32(file); /* TODO: find out what this means */

    binaryReadBytes(file, (unsigned char*) date, 8); /* TODO: check return value */
    binaryReadBytes(file, (unsigned char*) time, 8); /* TODO: check return value */
    numberOfColors = binaryReadInt32(file);
    numberOfStitchs = binaryReadInt32(file);
    hoopSize = binaryReadInt32(file);
    jefSetHoopFromId(pattern, hoopSize);

    bounds.left = binaryReadInt32(file);
    bounds.top = binaryReadInt32(file);
    bounds.right = binaryReadInt32(file);
    bounds.bottom = binaryReadInt32(file);

    rectFrom110x110.left = binaryReadInt32(file);
    rectFrom110x110.top = binaryReadInt32(file);
    rectFrom110x110.right = binaryReadInt32(file);
    rectFrom110x110.bottom = binaryReadInt32(file);

    rectFrom50x50.left = binaryReadInt32(file);
    rectFrom50x50.top = binaryReadInt32(file);
    rectFrom50x50.right = binaryReadInt32(file);
    rectFrom50x50.bottom = binaryReadInt32(file);

    rectFrom200x140.left = binaryReadInt32(file);
    rectFrom200x140.top = binaryReadInt32(file);
    rectFrom200x140.right = binaryReadInt32(file);
    rectFrom200x140.bottom = binaryReadInt32(file);

    rect_from_custom.left = binaryReadInt32(file);
    rect_from_custom.top = binaryReadInt32(file);
    rect_from_custom.right = binaryReadInt32(file);
    rect_from_custom.bottom = binaryReadInt32(file);

    for (i = 0; i < numberOfColors; i++) {
        embPattern_addThread(pattern, jefThreads[binaryReadInt32(file) % 79]);
    }
    embFile_seek(file, stitchOffset, SEEK_SET);
    stitchCount = 0;
    while(stitchCount < numberOfStitchs + 100)
    {
        flags = NORMAL;
        b0 = (unsigned char)embFile_getc(file);
        if(feof(file->file))
        {
            break;
        }
        b1 = (unsigned char)embFile_getc(file);
        if(feof(file->file))
        {
            break;
        }
        if(b0 == 0x80)
        {
            if(b1 & 1)
            {
                b0 = (unsigned char)embFile_getc(file);
                if(feof(file->file))
                    break;
                b1 = (unsigned char)embFile_getc(file);
                if(feof(file->file))
                    break;
                flags = STOP;
            }
            else if((b1 == 2) || (b1 == 4) || b1 == 6)
            {
                flags = TRIM;
                b0 = (unsigned char)embFile_getc(file);
                if (feof(file->file))
                {
                    break;
                }
                b1 = (unsigned char)embFile_getc(file);
                if (feof(file->file))
                {
                    break;
                }
            }
            else if(b1 == 0x10)
            {
                embPattern_addStitchRel(pattern, 0.0, 0.0, END, 1);
                break;
            }
        }
        dx = jefDecode(b0);
        dy = jefDecode(b1);
        embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1);
    }
    embFile_close(file);

    embPattern_end(pattern);
    return 1;
}

static void jefEncode(unsigned char* b, char dx, char dy, int flags)
{
    if(!b)
    {
        printf("ERROR: format-jef.c expEncode(), b argument is null\n");
        return;
    }
    if(flags == STOP)
    {
        b[0] = 0x80;
        b[1] = 1;
        b[2] = dx;
        b[3] = dy;
    }
    else if (flags == END)
    {
        b[0] = 0x80;
        b[1] = 0x10;
        b[2] = 0;
        b[3] = 0;
    }
    else if(flags == TRIM || flags == JUMP)
    {
        b[0] = 0x80;
        b[1] = 2;
        b[2] = dx;
        b[3] = dy;
    }
    else
    {
        b[0] = dx;
        b[1] = dy;
    }
}

/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
char writeJef(EmbPattern* pattern, const char* fileName)
{
    int colorlistSize, minColors, designWidth, designHeight, i;
    EmbRect boundingRect;
    EmbFile* file = 0;
    EmbTime time;
    EmbStitchList* stitches = 0;
    EmbStitch st;
    double dx = 0.0, dy = 0.0, xx = 0.0, yy = 0.0;
    unsigned char b[4];

    if (!validateWritePattern(pattern, fileName, "writeJef")) {
        return 0;
    }

    file = embFile_open(fileName, "wb", 0);
    if (!file) return 0;

    embPattern_correctForMaxStitchLength(pattern, 12.7, 12.7);

    colorlistSize = pattern->threads->count;
    minColors = embMaxInt(colorlistSize, 6);
    binaryWriteInt(file, 0x74 + (minColors * 4));
    binaryWriteInt(file, 0x0A);

    embTime_initNow(&time);

    embFile_printf(file, "%04d%02d%02d%02d%02d%02d", (int)(time.year + 1900),
            (int)(time.month + 1), (int)(time.day), (int)(time.hour),
            (int)(time.minute), (int)(time.second));
    binaryWriteByte(file, 0x00);
    binaryWriteByte(file, 0x00);
    binaryWriteInt(file, pattern->threads->count);
    binaryWriteInt(file, embStitchList_count(pattern->stitchList) + embMaxInt(0, (6 - colorlistSize) * 2) + 1);

    boundingRect = embPattern_calcBoundingBox(pattern);

    designWidth = (int)(embRect_width(boundingRect) * 10.0);
    designHeight = (int)(embRect_width(boundingRect) * 10.0);

    binaryWriteInt(file, jefGetHoopSize(designWidth, designHeight));

    /* Distance from center of Hoop */
    binaryWriteInt(file, (int) (designWidth / 2));  /* left */
    binaryWriteInt(file, (int) (designHeight / 2)); /* top */
    binaryWriteInt(file, (int) (designWidth / 2));  /* right */
    binaryWriteInt(file, (int) (designHeight / 2)); /* bottom */

    /* Distance from default 110 x 110 Hoop */
    if(embMinDouble(550 - designWidth / 2, 550 - designHeight / 2) >= 0)
    {
        binaryWriteInt(file, embMaxInt(-1, 550 - designWidth / 2));  /* left */
        binaryWriteInt(file, embMaxInt(-1, 550 - designHeight / 2)); /* top */
        binaryWriteInt(file, embMaxInt(-1, 550 - designWidth / 2));  /* right */
        binaryWriteInt(file, embMaxInt(-1, 550 - designHeight / 2)); /* bottom */
    }
    else
    {
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
    }

    /* Distance from default 50 x 50 Hoop */
    if(embMinDouble(250 - designWidth / 2, 250 - designHeight / 2) >= 0)
    {
        binaryWriteInt(file, (int) embMaxInt(-1, 250 - designWidth / 2));  /* left */
        binaryWriteInt(file, (int) embMaxInt(-1, 250 - designHeight / 2)); /* top */
        binaryWriteInt(file, (int) embMaxInt(-1, 250 - designWidth / 2));  /* right */
        binaryWriteInt(file, (int) embMaxInt(-1, 250 - designHeight / 2)); /* bottom */
    }
    else
    {
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
        binaryWriteInt(file, -1);
    }

    /* Distance from default 140 x 200 Hoop */
    binaryWriteInt(file, (int) (700 - designWidth / 2));   /* left */
    binaryWriteInt(file, (int) (1000 - designHeight / 2)); /* top */
    binaryWriteInt(file, (int) (700 - designWidth / 2));   /* right */
    binaryWriteInt(file, (int) (1000 - designHeight / 2)); /* bottom */

    /* repeated Distance from default 140 x 200 Hoop */
    /* TODO: Actually should be distance to custom hoop */
    binaryWriteInt(file, (int) (630 - designWidth / 2));  /* left */
    binaryWriteInt(file, (int) (550 - designHeight / 2)); /* top */
    binaryWriteInt(file, (int) (630 - designWidth / 2));  /* right */
    binaryWriteInt(file, (int) (550 - designHeight / 2)); /* bottom */

    for (i=0; i<pattern->threads->count; i++) {
        int j = embThread_findNearestColor_fromThread(pattern->threads->thread[i].color, (EmbThread *)jefThreads, 79);
        binaryWriteInt(file, j);
    }

    for (i = 0; i < (minColors - colorlistSize); i++) {
        binaryWriteInt(file, 0x0D);
    }

    for (stitches=pattern->stitchList; stitches; stitches=stitches->next) {
        st = stitches->stitch;
        dx = st.x * 10.0 - xx;
        dy = st.y * 10.0 - yy;
        xx = st.x * 10.0;
        yy = st.y * 10.0;
        jefEncode(b, (char)roundDouble(dx), (char)roundDouble(dy), st.flags);
        if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
            embFile_printf(file, "%c%c%c%c", b[0], b[1], b[2], b[3]);
        }
        else {
            embFile_printf(file, "%c%c", b[0], b[1]);
        }
    }
    embFile_close(file);
    return 1;
}

