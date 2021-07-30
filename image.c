#include "embroidery.h"

#include <math.h>

typedef struct EmbImage_ {
    int pixel_width;
    int pixel_height;
    float width;
    float height;
    EmbColor *color;
} EmbImage;

int read_ppm_image(char *fname, EmbImage *a);
void write_ppm_image(char *fname, EmbImage *a);
float image_diff(EmbImage *, EmbImage *);
int render_line(EmbLine, EmbImage *, EmbColor);
int render(EmbPattern *pattern, EmbImage *image);
int render_postscript(EmbPattern *pattern, EmbImage *image);

/* PPM Images
 * ----------
 *
 * Basic read/write support for images, so we can convert
 * to any other format we need using imagemagick.
 *
 * We only support P6 ppm, that is the original, 8 bits per channel.
 *
 * This also allows support for making animations using ffmpeg/avconv
 * of the stitching process.
 */
int read_ppm_image(char *fname, EmbImage *a)
{
    int i, state;
    FILE *f;
    char header[2];
    f = fopen(fname, "r");
    if (!f) {
        return 0;
    }
    a->pixel_width = 100;
    a->pixel_height = 75;
    state = 0;
    while (fread(header, 1, 1, f) == 1) {
        /* state machine for dealing with the header */
        if (header[0] == '\n') {
            state++;
        }
        if (state == 4) {
            break;
        }
    }
    for (i=0; i<a->pixel_width * a->pixel_height; i++) {
        embColor_read(f, &(a->color[i]), 3);
    }
    fclose(f);
    return 1;
}


/*
 * This function should work, combine with:
 *    $ convert example.ppm example.png
 */
void write_ppm_image(char *fname, EmbImage *a)
{
    int i;
    FILE *f;
    f = fopen(fname, "w");
    fprintf(f, "P6\n%d %d\n%d\n", a->pixel_width, a->pixel_height, 255);
    for (i=0; i<a->pixel_width * a->pixel_height; i++) {
        embColor_write(f, a->color[i], 3);
    }
    fclose(f);
}


/*
 *
 */
float image_diff(EmbImage *a, EmbImage* b)
{
    int i, j;
    float total;
    total = 0.0;
    for (i=0; i<a->pixel_width; i++) {
        for (j=0; j<a->pixel_height; j++) {
            total += embColor_distance(
                a->color[i+j*a->pixel_width],
                b->color[i+j*b->pixel_width]
            );
        }
    }
    return total;
}

/* Render Line
 * -----------
 * 
 */

int render_line(EmbLine line, EmbImage *image, EmbColor color) {
    EmbVector diff;
    EmbVector pos;
    int i, x, y;
    float pix_w, pix_h;
    diff.x = line.x2-line.x1;
    diff.y = line.y2-line.y1;
    pix_w = image->width / image->pixel_width;
    pix_h = image->height / image->pixel_height;
    for (i = 0; i < 1000; i++) {
        pos.x = line.x1 + 0.001*i*diff.x;
        pos.y = line.y1 + 0.001*i*diff.y;
        x = (int)round(pos.x / pix_w);
        y = (int)round(pos.y / pix_h);
        image->color[x+y*image->pixel_width] = color;
    }
    return 1;
}

/* Basic Render
 * ------------
 * This is a simple algorithm that steps through the stitches and
 * then for each line calls render_line.
 *
 * The caller is responsible for the memory in p and image.
 */

int render(EmbPattern *p, EmbImage *image) {
    int i;
    EmbColor color = {0, 0, 0};
    EmbLine line;
    for (i=1; i < p->stitchList->count; i++)  {
        line.x1 = p->stitchList->stitch[i-1].x;
        line.y1 = p->stitchList->stitch[i-1].y;
        line.x2 = p->stitchList->stitch[i].x;
        line.y2 = p->stitchList->stitch[i].y;
        render_line(line, image, color); /* HACK: st.color); */
    }
    return 1;
}

/* EPS style render
 *
 *
 */

int render_postscript(EmbPattern *pattern, EmbImage *image) {
    return 1;
}

