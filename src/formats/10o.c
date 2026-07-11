/**
 * @file 10o.c
 */

#include "embroidery.h"

/**
 * @brief Reader for Toyota "10o" files.
 *
 * @param pattern The memory for the pattern to be read into.
 * @param file The file to read the pattern from.
 *
 * The Toyota 10o format is a stitch-only format that uses an external color
 * file.
 *
 * The stitch encoding is in 3 byte chunks.
 *
 * @return 1 if successful, 0 otherwise.
 */
int8_t read10o(EmbPattern *pattern, FILE *file)
{
    uint8_t b[10];
    while (fread(b, 1, 3, file) == 3) {
        EmbStitch st;

        uint8_t ctrl = b[0];
        st.y = 0.1 * b[1];
        st.x = 0.1 * b[2];
        st.flags = NORMAL;

        if (ctrl & 0x20) {
            st.x = -st.x;
        }
        if (ctrl & 0x40) {
            st.y = -st.y;
        }
        if (ctrl & 0x01) {
            st.flags = TRIM;
        }
        if ((ctrl & 0x5) == 5) {
            st.flags = STOP;
        }
        if (ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87) {
            st.flags = END;
        }

        emb_add_stitch(pattern, st.x, st.y, st.flags, 1);
    }
    return 1;
}

/**
 * @brief Writer for Toyota "10o" files.
 *
 * @param pattern The memory for the pattern to be read from.
 * @param file The file to write the pattern into.
 *
 * The Toyota 10o format is a stitch-only format that uses an external color
 * file.
 *
 * The stitch encoding is in 3 byte chunks.
 *
 * @return 1 if successful, 0 otherwise.
 */
int8_t write10o(EmbPattern *pattern, FILE *file)
{
    int i;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        uint8_t b[10];
        EmbStitch st = pattern->stitch_list->stitch[i];

        b[0] = 0;
        b[1] = 0;
        b[2] = 0;
        if (st.x < 0) {
            b[2] |= 0x20;
            b[0] = -st.x;
        } else {
            b[0] = st.x;
        }
        if (st.y < 0) {
            b[2] |= 0x40;
            b[1] = -st.y;
        } else {
            b[1] = st.y;
        }
        if (st.flags == TRIM) {
            b[2] |= 1;
        }
        if (st.flags == STOP) {
            b[2] |= 5;
        }
        if (st.flags == END) {
            b[2] = 0xF8;
        }

        if (fwrite(b, 1, 3, file) != 3) {
            return 0;
        }
    }
    return 1;
}
