/* The Toyota 100 format is a stitch-only format that uses an external color
 * file.
 *
 * The stitch encoding is in 4 byte chunks.
 */

#include "embroidery.h"

char read100(EmbPattern *pattern, FILE *file)
{
        unsigned char b[10];
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

                embp_addStitchRel(pattern, st.x, st.y, st.flags, 1);
        }
        return 1;
}

char write100(EmbPattern *pattern, FILE *file)
{
        int i;
        EmbVector position;

        position = pattern->home;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                unsigned char b[10];
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

/* The Toyota 10o format is a stitch-only format that uses an external color
 * file.
 *
 * The stitch encoding is in 3 byte chunks.
 */
char read10o(EmbPattern *pattern, FILE *file)
{
        unsigned char b[10];
        while (fread(b, 1, 3, file) == 3) {
                EmbStitch st;

                unsigned char ctrl = b[0];
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

                embp_addStitchRel(pattern, st.x, st.y, st.flags, 1);
        }
        return 1;
}

/* . */
char write10o(EmbPattern *pattern, FILE *file)
{
        int i;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                unsigned char b[10];
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
