/**
 * @file pattern.c
 */

#include <math.h>

#include "embroidery.h"

/* The Pattern Properties
 */
int embp_color_count(EmbPattern *pattern, EmbColor startColor)
{
        int colors = 0, i;
        EmbColor color = startColor;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbColor newColor;
                EmbStitch st;

                st = pattern->stitch_list->stitch[i];

                newColor = pattern->thread_list->thread[st.color].color;
                if (embColor_distance(newColor, color) != 0) {
                        colors++;
                        color = newColor;
                } else if (st.flags & END || st.flags & STOP) {
                        colors++;
                }

                while (pattern->stitch_list->stitch[i + 1].flags == st.flags) {
                        i++;
                        if (i >= pattern->stitch_list->count - 2) {
                                break;
                        }
                }
        }
        return colors;
}

/*
 * Print out pattern details.
 */
void embp_details(EmbPattern *pattern)
{
        int colors, num_stitches, real_stitches, jump_stitches, trim_stitches;
        int unknown_stitches;
        EmbRect bounds;
        float thread_usage;
        float minimum_length;
        float maximum_length;

        // colors = embp_color_count(pattern);
        colors = 1;
        num_stitches = pattern->stitch_list->count;
        real_stitches = embp_realStitches(pattern);
        jump_stitches = embp_jumpStitches(pattern);
        trim_stitches = embp_trimStitches(pattern);
        unknown_stitches = 0;   // embp_unknownStitches(pattern);
        bounds = embp_bounds(pattern);
        thread_usage = emb_total_thread_length(pattern);
        minimum_length = embp_shortest_stitch(pattern);
        maximum_length = embp_longest_stitch(pattern);

        /* Print Report */
        printf("Design Details\n");
        printf("--------------\n");
        printf("real_stitches: %d\n", real_stitches);
        printf("trim_stitches: %d\n", trim_stitches);
        printf("unknown_stitches: %d\n", unknown_stitches);
        printf("total_stitches: %d\n", num_stitches);
        printf("num_colors: %d\n", pattern->thread_list->count);

        printf("Total thread usage: %f mm\n", thread_usage);
        printf("Shortest stitch: %f mm\n", minimum_length);
        printf("Longest stitch: %f mm\n", maximum_length);

        printf("Stitches: %d\n", num_stitches);
        printf("Colors: %d\n", colors);
        printf("Jumps: %d\n", jump_stitches);

        printf("Top: %f mm\n", bounds.y);
        printf("Left: %f mm\n", bounds.x);
        printf("Bottom: %f mm\n", bounds.h + bounds.y);
        printf("Right: %f mm\n", bounds.w + bounds.x);
        printf("Width: %f mm\n", bounds.w);
        printf("Height: %f mm\n", bounds.h);
        printf("\n");

        /*
           EmbReal minx = 0.0, maxx = 0.0, miny = 0.0, maxy = 0.0;
           int number_of_minlength_stitches = 0;
           int number_of_maxlength_stitches = 0;

           EmbReal xx = 0.0, yy = 0.0;
           EmbReal length = 0.0;

           if (num_stitches == 0) {
           QMessageBox::warning(this, tr("No Design Loaded"), tr("<b>A design needs to be loaded or created before details can be determined.</b>"));
           return;
           }
           QVector<EmbReal> stitchLengths;

           EmbReal binSize = max_stitchlength / NUMBINS;

           QString str;
           int i;
           for (i = 0; i < NUMBINS; i++) {
           str += QString::number(binSize * (i), 'f', 1) + " - " + QString::number(binSize * (i+1), 'f', 1) + " mm: " +  QString::number(bin[i]) + "\n\n";
           }

           grid->addWidget(new QLabel(tr("\nStitch Distribution: \n")),9,0,1,2);
           grid->addWidget(new QLabel(str), 10, 0, 1, 1);
           grid->addWidget(new QLabel(tr("\nThread Length By Color: \n")),11,0,1,2);
           int currentRow = 12;

           int i;
           for (i = 0; i < num_colors; i++) {
           QFrame *frame = new QFrame();
           frame->setGeometry(0,0,30,30);
           QPalette palette = frame->palette();
           EmbColor t = embThreadList_getAt(pattern->threadList, i).color;
           palette.setColor(backgroundRole(), QColor( t.r, t.g, t.b ) );
           frame->setPalette( palette );
           frame->setAutoFillBackground(true);
           grid->addWidget(frame, currentRow,0,1,1);
           debug_message("size: %d i: %d", stitchLengths.size(), i);
           grid->addWidget(new QLabel(QString::number(stitchLengths.at(i)) + " mm"), currentRow,1,1,1);
           currentRow++;
           }

           QDialogButtonBox buttonbox(Qt::Horizontal, &dialog);
           QPushButton button(&dialog);
           button.setText("Ok");
           buttonbox.addButton(&button, QDialogButtonBox::AcceptRole);
           buttonbox.setCenterButtons(true);
           connect(&buttonbox, SIGNAL(accepted()), &dialog, SLOT(accept()));

           grid->addWidget(&buttonbox, currentRow, 0, 1, 2);
         */
}

/* . */
void embp_print(EmbPattern *pattern)
{
        EmbArray *sts = pattern->stitch_list;
        int i;
        for (i = 0; i < sts->count; i++) {
                printf("%d: %f %f %d\n",
                       i, sts->stitch[i].x, sts->stitch[i].y,
                       sts->stitch[i].flags);
        }
}

void embp_lengthHistogram(EmbPattern *pattern, int *bin, int NUMBINS)
{
        int i;
        float max_stitch_length = embp_longest_stitch(pattern);
        EmbArray *sts = pattern->stitch_list;
        for (i = 0; i <= NUMBINS; i++) {
                bin[i] = 0;
        }

        for (i = 1; i < sts->count; i++) {
                EmbStitch st_prev = sts->stitch[i - 1];
                EmbStitch st = sts->stitch[i];
                if ((st.flags == NORMAL) & (st_prev.flags == NORMAL)) {
                        float length = emb_stitch_length(st_prev, st);
                        bin[(int)
                            (floor(NUMBINS * length / max_stitch_length))]++;
                }
        }
}

int embp_realStitches(EmbPattern *pattern)
{
        int i;
        EmbArray *sts = pattern->stitch_list;
        int real_stitches = 0;
        for (i = 0; i < sts->count; i++) {
                if (!(sts->stitch[i].flags & (JUMP | TRIM | END))) {
                        real_stitches++;
                }
        }
        return real_stitches;
}

int embp_jumpStitches(EmbPattern *pattern)
{
        int i;
        EmbArray *sts = pattern->stitch_list;
        int jump_stitches = 0;
        for (i = 0; i < sts->count; i++) {
                if (sts->stitch[i].flags & JUMP) {
                        jump_stitches++;
                }
        }
        return jump_stitches;
}

int embp_trimStitches(EmbPattern *pattern)
{
        int i;
        EmbArray *sts = pattern->stitch_list;
        int trim_stitches = 0;
        for (i = 0; i < sts->count; i++) {
                if (sts->stitch[i].flags & TRIM) {
                        trim_stitches++;
                }
        }
        return trim_stitches;
}

/* Get the position as a vector from the stitch. */
EmbVector emb_st_pos(EmbStitch st)
{
        return emb_vector(st.x, st.y);
}

/* Length of stitch starting of "prev_st" and ending at "st". */
double emb_stitch_length(EmbStitch prev_st, EmbStitch st)
{
        EmbVector pos = emb_st_pos(st);
        EmbVector prev_pos = emb_st_pos(prev_st);
        double length = emb_vector_distance(pos, prev_pos);
        return length;
}

/* Returns the number of real stitches in a pattern.
 * We consider SEQUIN to be a real stitch in this count.
 */
int embp_real_count(EmbPattern *pattern)
{
        int i;
        int total = 0;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch st = pattern->stitch_list->stitch[i];
                if (!(st.flags & (JUMP | TRIM))) {
                        total++;
                }
        }
        return total;
}

/* The length of the longest stitch in the pattern. */
EmbReal embp_longest_stitch(EmbPattern *pattern)
{
        if (pattern->stitch_list->count < 2) {
                return 0.0;
        }

        int i;
        EmbReal max_stitch = 0.0;
        EmbStitch prev_st = pattern->stitch_list->stitch[0];
        for (i = 1; i < pattern->stitch_list->count; i++) {
                EmbStitch st = pattern->stitch_list->stitch[i];
                if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
                        double length = emb_stitch_length(st, prev_st);
                        if (length > max_stitch) {
                                max_stitch = length;
                        }
                }
                prev_st = st;
        }
        return max_stitch;
}

/* The length of the shortest stitch in the pattern. */
EmbReal embp_shortest_stitch(EmbPattern *pattern)
{
        if (pattern->stitch_list->count < 2) {
                return 0.0;
        }

        int i;
        EmbReal min_stitch = 1.0e10;
        EmbStitch prev_st = pattern->stitch_list->stitch[0];
        for (i = 1; i < pattern->stitch_list->count; i++) {
                EmbStitch st = pattern->stitch_list->stitch[i];
                if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
                        double length = emb_stitch_length(st, prev_st);
                        if (length < min_stitch) {
                                min_stitch = length;
                        }
                }
                prev_st = st;
        }
        return min_stitch;
}

/* Returns the number of stitches in a pattern that are of any of the types
 * or-ed together in "flag". For example to count the total number of
 * TRIM and STOP stitches use:
 *
 *     embp_count_type(pattern, TRIM | STOP);
 */
int embp_count_type(EmbPattern *pattern, int flag)
{
        int i;
        int total = 0;
        for (i = 0; i < pattern->stitch_list->count; i++) {
                EmbStitch st = pattern->stitch_list->stitch[i];
                if (st.flags & flag) {
                        total++;
                }
        }
        return total;
}

/* . */
void emb_length_histogram(EmbPattern *pattern, int *bins)
{
        if (pattern->stitch_list->count < 2) {
                return;
        }

        int i;
        for (i = 0; i <= NUMBINS; i++) {
                bins[i] = 0;
        }

        double max_stitchlength = embp_longest_stitch(pattern);
        EmbStitch prev_st = pattern->stitch_list->stitch[0];
        for (i = 1; i < pattern->stitch_list->count; i++) {
                EmbStitch st = pattern->stitch_list->stitch[i];
                if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
                        double length = emb_stitch_length(st, prev_st);
                        int bin_number =
                            (int)floor(NUMBINS * length / max_stitchlength);
                        bins[bin_number]++;
                }
                prev_st = st;
        }
}

/* . */
void emb_color_histogram(EmbPattern *pattern, int **bins)
{
        if (pattern->stitch_list->count < 2) {
                return;
        }

        int i, j;
        for (j = 0; j < pattern->thread_list->count; j++)
                for (i = 0; i <= NUMBINS; i++) {
                        bins[j][i] = 0;
                }

        double max_stitchlength = embp_longest_stitch(pattern);
        EmbStitch prev_st = pattern->stitch_list->stitch[0];
        for (i = 1; i < pattern->stitch_list->count; i++) {
                EmbStitch st = pattern->stitch_list->stitch[i];
                /* Can't count first normal stitch. */
                if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
                        double length = emb_stitch_length(st, prev_st);
                        int bin_number =
                            (int)floor(NUMBINS * length / max_stitchlength);
                        bins[0][bin_number]++;
                }
                prev_st = st;
        }
}

/* . */
double emb_total_thread_length(EmbPattern *pattern)
{
        if (pattern->stitch_list->count < 2) {
                return 0.0;
        }

        int i;
        double total = 0.0;
        EmbStitch prev_st = pattern->stitch_list->stitch[0];
        for (i = 1; i < pattern->stitch_list->count; i++) {
                EmbStitch st = pattern->stitch_list->stitch[i];
                /* Can't count first normal stitch. */
                if (st.flags == NORMAL) {
                        total += emb_stitch_length(st, prev_st);
                }
                prev_st = st;
        }
        return total;
}

/* FIXME. */
double emb_total_thread_of_color(EmbPattern *pattern, int thread_index)
{
        if (pattern->stitch_list->count < 2) {
                return 0.0;
        }

        int i;
        double total = 0.0;
        EmbStitch prev_st = pattern->stitch_list->stitch[0];
        for (i = 1; i < pattern->stitch_list->count; i++) {
                EmbStitch st = pattern->stitch_list->stitch[i];
                /* Can't count first normal stitch. */
                if (st.color == thread_index)
                        if ((prev_st.flags == NORMAL) && (st.flags == NORMAL)) {
                                total += emb_stitch_length(st, prev_st);
                        }
                prev_st = st;
        }
        return total;
}
