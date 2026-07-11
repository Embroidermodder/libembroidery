/* Mitsubishi Embroidery Format (.mit)
 *
 * Stitch Only Format.
 */

#include "embroidery.h"

int8_t readMit(EmbPattern *pattern, FILE *file)
{
    uint8_t data[2];

    while (fread(data, 1, 2, file) == 2) {
        int x = mitDecodeStitch(data[0]);
        int y = mitDecodeStitch(data[1]);
        emb_add_stitch(pattern, x / 10.0, y / 10.0, NORMAL, 1);
    }
    return 1;
}

int8_t writeMit(EmbPattern *pattern, FILE *file)
{
    EmbReal xx, yy;
    int i;

    emb_correctForMaxStitchLength(pattern, 0x1F, 0x1F);
    xx = 0;
    yy = 0;
    for (i = 0; i < pattern->stitch_list->count; i++) {
        uint8_t b[2];
        EmbStitch st = pattern->stitch_list->stitch[i];
        b[0] = mitEncodeStitch(st.x - xx);
        b[1] = mitEncodeStitch(st.y - yy);
        xx = st.x;
        yy = st.y;
        fwrite(b, 1, 2, file);
    }
    return 1;
}

