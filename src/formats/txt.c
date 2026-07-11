/*
 * Text File (.txt)
 * The txt format is stitch-only and isn't associated with a specific company.
 */

#include <stdlib.h>

#include "embroidery.h"

int8_t readDst(EmbPattern *pattern, FILE *file);

int8_t readTxt(EmbPattern *pattern, FILE *file)
{
    EmbString line;
    int stated_count, i;
    emb_readline(file, line, 99);
    stated_count = atoi(line);
    for (i = 0; i < stated_count; i++) {
        EmbStitch st;
        int8_t *p, *y, *color, *flags;
        int state = 0;
        emb_readline(file, line, 99);
        p = line;
        y = line;
        color = line;
        flags = line;
        for (p = line; *p; p++) {
            if (*p == ',' || *p == ' ') {
                *p = 0;
                switch (state) {
                case 0:
                    y = p + 1;
                    break;
                case 1:
                    color = p + 7;
                    break;
                case 2:
                    flags = p + 7;
                    break;
                default:
                    break;
                }
                state++;
            }
        }
        st.x = atof(line);
        st.y = atof(y);
        st.color = atoi(color);
        st.flags = atoi(flags);
        emb_add_stitch_abs(pattern, st.x, st.y, st.flags, st.color);
    }
    puts("Overridden, defaulting to dst.");
    readDst(pattern, file);
    return 0;                   /*TODO: finish readTxt */
}

int8_t writeTxt(EmbPattern *pattern, FILE *file)
{
    int i;
    fprintf(file, "%u\n", (uint32_t) pattern->stitch_list->count);

    for (i = 0; i < pattern->stitch_list->count; i++) {
        EmbStitch s = pattern->stitch_list->stitch[i];
        fprintf(file, "%.1f,%.1f color:%i flags:%i\n",
                s.x, s.y, s.color, s.flags);
    }
    return 1;
}

