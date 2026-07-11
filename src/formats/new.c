/* Ameco Embroidery Format (.new)
 *
 * Stitch Only Format.
 */

#include "embroidery.h"

int8_t writeDst(EmbPattern *pattern, FILE *file);

int8_t readNew(EmbPattern *pattern, FILE *file)
{
    uint32_t stitchCount;
    uint8_t data[3];

    stitchCount = emb_read_i16(file);
    while (fread(data, 1, 3, file) == 3) {
        int x = decodeNewStitch(data[0]);
        int y = decodeNewStitch(data[1]);
        int flag = NORMAL;
        int8_t val = data[2];
        if (data[2] & 0x40) {
            x = -x;
        }
        if (data[2] & 0x20) {
            y = -y;
        }
        if (data[2] & 0x10) {
            flag = TRIM;
        }
        if (data[2] & 0x01) {
            flag = JUMP;
        }
        if ((val & 0x1E) == 0x02) {
            flag = STOP;
        }
        /* Unknown values, possibly TRIM
           155 = 1001 1011 = 0x9B
           145 = 1001 0001 = 0x91
         */
        /*val = (data[2] & 0x1C);
           if (val != 0 && data[2] != 0x9B && data[2] != 0x91) {
           int z = 1;
           } */
        emb_add_stitch(pattern, x / 10.0, y / 10.0, flag, 1);
    }

    return 1;
}

/* . */
int8_t writeNew(EmbPattern *pattern, FILE *file)
{
    puts("Overridden, defaulting to dst.");
    writeDst(pattern, file);
    return 0;                   /*TODO: finish writeNew */
}

