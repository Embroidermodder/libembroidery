/**
 * @file 100.c
 */

#include "embroidery.h"

/**
 * @brief Reader for Toyota "100" files.
 *
 * @param pattern The memory for the pattern to be read into.
 * @param file The file to read the pattern from.
 *
 * The Toyota 100 format is a stitch-only format that uses an external color
 * file.
 *
 * The stitch encoding is in 4 byte chunks.
 *
 * @return 1 if successful, 0 otherwise.
 */
int8_t read100(EmbPattern *pattern, FILE *file)
{
    uint8_t b[10];
    while (fread(b, 1, 3, file) == 3) {
        EmbStitch st;
        st.x = toyota_position_decode(b[2]);
        st.y = toyota_position_decode(b[3]);
        st.flags = NORMAL;
        /*
           if (!(b[0] & 0xFC)) {
           st.flags = JUMP;
           TODO: review & fix
           }
         */
        if (!(b[0] & 0x01)) {
            st.flags = STOP;
        }
        if (b[0] == 0x1F) {
            st.flags = END;
        }

        emb_add_stitch(pattern, st.x, st.y, st.flags, 1);
    }
    return 1;
}

/**
 * @brief Writer for Toyota "100" files.
 *
 * @param pattern The memory for the pattern to be read from.
 * @param file The file to write the pattern into.
 *
 * The Toyota 100 format is a stitch-only format that uses an external color
 * file.
 *
 * The stitch encoding is in 4 byte chunks.
 *
 * @return 1 if successful, 0 otherwise.
 */
int8_t write100(EmbPattern *pattern, FILE *file)
{
    int i;
    EmbVector position;

    position = pattern->home;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        uint8_t b[10];
        EmbStitch st = pattern->stitch_list->stitch[i];

        EmbVector delta;
        delta.x = st.x - position.x;
        delta.y = st.y - position.y;
        position = emb_vector_add(position, delta);
        b[0] = 0;
        b[1] = 0;
        b[2] = toyota_position_encode(delta.x);
        b[3] = toyota_position_encode(delta.y);
        if (!(st.flags & STOP)) {
            b[0] |= 0x01;
        }
        if (st.flags & END) {
            b[0] = 0x1F;
        }

        if (fwrite(b, 1, 4, file) != 4) {
            return 0;
        }
    }
    return 1;
}

