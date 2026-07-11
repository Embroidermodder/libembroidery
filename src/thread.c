/* The Thread Management System
 * -----------------------------------------------------------------------------
 */

#include <stdlib.h>
#include <string.h>

#include "embroidery.h"

/* . */
int embColor_distance(EmbColor a, EmbColor b)
{
    int t;
    t = (a.r - b.r) * (a.r - b.r);
    t += (a.g - b.g) * (a.g - b.g);
    t += (a.b - b.b) * (a.b - b.b);
    return t;
}

/* . */
void embColor_read(void *f, EmbColor *c, int toRead)
{
    uint8_t b[4];
    if (fread(b, 1, toRead, f) < (uint32_t) toRead) {
        puts("ERROR: Failed to read embColor bytes.");
        return;
    }
    c->r = b[0];
    c->g = b[1];
    c->b = b[2];
}

/* . */
void embColor_write(void *f, EmbColor c, int toWrite)
{
    uint8_t b[4];
    b[0] = c.r;
    b[1] = c.g;
    b[2] = c.b;
    b[3] = 0;
    fwrite(b, 1, toWrite, f);
}

/* Returns the closest color to the required color based on
 * a list of available threads. The algorithm is a simple least
 * squares search against the list. If the (square of) Euclidean 3-dimensional
 * distance between the points in (red, green, blue) space is smaller
 * then the index is saved and the remaining index is returned to the
 * caller.
 *
 * color:  The EmbColor color to match.
 * colors: The EmbThreadList pointer to start the search at.
 * mode:   Is the argument an array of threads (0) or colors (1)?
 * Returns closestIndex: The entry in the ThreadList that matches.
 */
int emb_find_nearest_color(EmbColor color, EmbColor *color_list, int n_colors)
{
    int currentClosestValue = 256 * 256 * 3;
    int closestIndex = -1, i;
    for (i = 0; i < n_colors; i++) {
        int delta = embColor_distance(color, color_list[i]);

        if (delta <= currentClosestValue) {
            currentClosestValue = delta;
            closestIndex = i;
        }
    }
    return closestIndex;
}

/* The maximum distance. */
int
emb_find_nearest_thread(EmbColor color, EmbThread *thread_list, int n_threads)
{
    int currentClosestValue = 256 * 256 * 3;
    int closestIndex = -1, i;
    for (i = 0; i < n_threads; i++) {
        int delta = embColor_distance(color, thread_list[i].color);

        if (delta <= currentClosestValue) {
            currentClosestValue = delta;
            closestIndex = i;
        }
    }
    return closestIndex;
}

/*
 * Returns a random thread color, useful in filling in cases where the
 * actual color of the thread doesn't matter but one needs to be declared
 * to test or render a pattern.
 *
 * Returns c: The resulting color.
 */
EmbThread emb_get_random_thread(void)
{
    EmbThread c;
    c.color.r = rand() % 256;
    c.color.g = rand() % 256;
    c.color.b = rand() % 256;
    strcpy(c.description, "random");
    strcpy(c.catalogNumber, "");
    return c;
}

int threadColor(const int8_t * name, int brand) {
    int i;
    for (i = 0; brand_codes[brand].codes[i].manufacturer_code >= 0; i++) {
        if (!strcmp(brand_codes[brand].codes[i].name, name)) {
            return brand_codes[brand].codes[i].hex_code;
        }
    }
    return -1;
}

int threadColorNum(uint32_t color, int brand) {
    int i;
    for (i = 0; brand_codes[brand].codes[i].manufacturer_code >= 0; i++) {
        if (brand_codes[brand].codes[i].hex_code == color) {
            return brand_codes[brand].codes[i].manufacturer_code;
        }
    }

    return -1;
}

const int8_t *threadColorName(uint32_t color, int brand) {
    int i;
    for (i = 0; brand_codes[brand].codes[i].manufacturer_code >= 0; i++) {
        if (brand_codes[brand].codes[i].hex_code == color) {
            return brand_codes[brand].codes[i].name;
        }
    }

    return "COLOR NOT FOUND";
}
