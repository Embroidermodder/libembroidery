/*
 * Thread color tests.
 */

#include <string.h>

#include "embroidery.h"

int
main(void)
{
    unsigned int tColor = 0xFF0d6b2f;
    int tBrand = EMB_BRAND_SVG;
    char name[100];

    int color_num = threadColorNum(tColor, tBrand);
    if (color_num != 29) {
        printf("ERROR: SVG color 0xFF0D6B2F misidentified as %d.\n", color_num);
        return 1;
    }
    sprintf(name, threadColorName(tColor, tBrand));
    if (strcmp(name, "darkolivegreen")) {
        printf("ERROR: SVG color 0xFF0D6B2F misidentified as \"%s\".\n", name);
        return 1;
    }

    return 0;
}

