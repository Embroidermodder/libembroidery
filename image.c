#include "embroidery.h"

#include <math.h>

typedef struct EmbImage_ {
    int pixel_width;
    int pixel_height;
    float width;
    float height;
    EmbColor *color;
} EmbImage;

int render_line(EmbLine, EmbImage *, EmbColor);
int render(EmbPattern *pattern, EmbImage *image);
int render_postscript(EmbPattern *pattern, EmbImage *image);

/* Render Line
 * -----------
 * 
 */

int render_line(EmbLine line, EmbImage *image, EmbColor color)
{
    EmbVector diff;
    EmbVector pos;
    int i, x, y;
    float pix_w, pix_h;
    diff.x = line.x2-line.x1;
    diff.y = line.y2-line.y1;
    pix_w = image->width / image->pixel_width;
    pix_h = image->height / image->pixel_height;
    for (i=0; i<1000; i++) {
        pos.x = line.x1 + 0.001*i*diff.x;
        pos.y = line.y1 + 0.001*i*diff.y;
        x = (int)round(pos.x / pix_w);
        y = (int)round(pos.y / pix_h);
        image->color[x+y*image->pixel_width] = color;
    }
}

/* Basic Render
 * ------------
 * This is a simple algorithm that steps through the stitches and
 * then for each line calls render_line.
 *
 * The caller is responsible for the memory in p and image.
 */

int render(EmbPattern *p, EmbImage *image)
{
    int i;
    EmbColor color = {0, 0, 0};
    EmbLine line;
    for (i=1; i<p->stitchList->count; i++)  {
        line.x1 = p->stitchList->stitch[i-1].x;
        line.y1 = p->stitchList->stitch[i-1].y;
        line.x2 = p->stitchList->stitch[i].x;
        line.y2 = p->stitchList->stitch[i].y;
        render_line(line, image, color); /* HACK: st.color); */
    }
}

/* EPS style render
 *
 *
 */

int render_postscript(EmbPattern *pattern, EmbImage *image)
{
    
}

