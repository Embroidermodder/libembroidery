#include <math.h>

#include "embroidery.h"

/* p a arc a thread_index a style
 */
void emb_stitchArc(EmbPattern * p, EmbArc arc, int thread_index, int style) {
    printf("DEBUG stitchArc (unfinished): %f %f %d %d\n",
           p->home.x, arc.start.x, thread_index, style);
}

/* p a circle a thread_index a style
 *
 * style determines:
 *     stitch density
 *     fill pattern
 *     outline or fill
 *
 * For now it's a straight fill of 1000 stitches of the whole object by
 * default.
 *
 * Consider the intersection of a line in direction "d" that passes through
 * the disc with center "c", radius "r". The start and end points are:
 *
 *     $(c-r(d/|d|), c + r(d/|d|))$
 *
 * Lines that are above and below this with an even seperation $s$ can be
 * found by taking the point on the line to be c+sn where the $n$ is the
 * unit normal vector to $d$ and the vector to be $d$ again. The
 * intersection points are therefore a right angled triangle, with one side
 * r, another s and the third the length to be solved, by Pythagoras we
 * have:
 *
 *    $(c + sn - \sqrt{r^2-s^2}(d/|d|), c + sn + \sqrt{r^2-s^2}(d/|d|))$
 *
 * repeating this process gives us all the end points and the fill only
 * alters these lines by splitting the ones longer than some tolerence.
 */
void emb_stitchCircle(EmbPattern * p, EmbCircle circle, int thread_index,
                   int style) {
    float s;
    float seperation = 0.1;
    EmbVector direction = { 1.0, 1.0 };
    EmbVector normal = { -1.0, 1.0 };
    direction = emb_vector_normalize(direction);
    normal = emb_vector_normalize(normal);
    printf("style %d\n", style);
    for (s = -circle.radius; s < circle.radius; s += seperation) {
        EmbLine line;
        float length = sqrt(circle.radius * circle.radius - s * s);
        EmbVector scaled = emb_vector_scale(normal, s);
        line.start = emb_vector_add(circle.center, scaled);
        scaled = emb_vector_scale(direction, length);
        line.start = emb_vector_subtract(line.start, scaled);
        scaled = emb_vector_scale(normal, s);
        line.end = emb_vector_add(circle.center, scaled);
        scaled = emb_vector_scale(direction, length);
        line.end = emb_vector_add(line.end, scaled);
        /* Split long stitches here. */
        emb_add_stitch_abs(p, line.start.x, line.start.y, NORMAL, thread_index);
        emb_add_stitch_abs(p, line.end.x, line.end.y, NORMAL, thread_index);
    }
}

/* a p a ellipse a thread_index a style
 *
 * \todo finish stitchEllipse
 */
void emb_stitchEllipse(EmbPattern * p, EmbEllipse ellipse, int thread_index,
                    int style) {
    printf("DEBUG stitchEllipse: %f %f %d %d\n", p->home.x,
           ellipse.center.x, thread_index, style);
}

/*a p a rect a thread_index a style
 *
 * \todo finish stitch path
 */
void emb_stitchPath(EmbPattern * p, EmbPath path, int thread_index, int style) {
    printf("DEBUG stitchPath: %f %d %d %d\n",
           p->home.x, path.pointList->count, thread_index, style);
}

/*a p a rect a thread_index a style
 *
 * \todo finish stitch polygon
 */
void emb_stitchPolygon(EmbPattern * p, EmbPolygon polygon, int thread_index,
                    int style) {
    printf("DEBUG stitchPolygon: %f %d %d %d\n", p->home.x,
           polygon.pointList->count, thread_index, style);
}

/* a p a rect a thread_index a style
 *
 * \todo finish stitch polyline
 */
void emb_stitchPolyline(EmbPattern * p, EmbPolyline polyline, int thread_index,
                     int style) {
    printf("DEBUG stitchPolyline: %f %d %d %d\n", p->home.x,
           polyline.pointList->count, thread_index, style);
}

/* a p a rect a thread_index a style
 *
 * Here we just stitch the rectangle in the direction of it's longer side.
 */
void emb_stitchRect(EmbPattern * p, EmbRect rect, int thread_index, int style) {
    EmbReal seperation = 0.1;
    if (style > 0) {
        puts("WARNING: Only style 0 has been implimented.");
    }
    if (rect.w > rect.h) {
        float s;
        for (s = rect.y; s < rect.y + rect.h; s += seperation) {
            /* Split long stitches here. */
            emb_add_stitch_abs(p, rect.y, s, NORMAL, thread_index);
            emb_add_stitch_abs(p, rect.y + rect.h, s, NORMAL, thread_index);
        }
    } else {
        float s;
        for (s = rect.x; s < rect.x + rect.w; s += seperation) {
            /* Split long stitches here. */
            emb_add_stitch_abs(p, s, rect.x, NORMAL, thread_index);
            emb_add_stitch_abs(p, s, rect.x + rect.w, NORMAL, thread_index);
        }
    }
}

/* a p a rect a thread_index a style
 */
void emb_stitchText(EmbPattern * p, EmbRect rect, int thread_index, int style) {
    printf("DEBUG: %f %f %d %d", p->home.x, rect.y, thread_index, style);
}

/* a p
 */
void emb_convertGeometry(EmbPattern * p) {
    int i;
    for (i = 0; i < p->geometry->count; i++) {
        EmbGeometry g = p->geometry->geometry[i];
        switch (g.type) {
        case EMB_ARC:{
                /* To Do make the thread up here. */
                emb_stitchArc(p, g.object.arc, 0, 0);
                break;
            }
        case EMB_CIRCLE:{
                /* To Do make the thread up here. */
                emb_stitchCircle(p, g.object.circle, 0, 0);
                break;
            }
        case EMB_ELLIPSE:{
                /* To Do make the thread up here. */
                emb_stitchEllipse(p, g.object.ellipse, 0, 0);
                break;
            }
        case EMB_RECT:{
                /* To Do make the thread up here. */
                emb_stitchRect(p, g.object.rect, 0, 0);
                break;
            }
        default:
            break;
        }
    }
    /* Now ignore the geometry when writing. */
    p->geometry->count = 0;
}
