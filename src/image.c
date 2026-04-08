#include <stdlib.h>

#include "embroidery.h"

/* . */
EmbImage
embImage_create(int width, int height)
{
    EmbImage image;
    image.width = width;
    image.height = height;
    image.data = malloc(4*width*height);
    return image;

}

/* . */
void
embImage_read(EmbImage *image, char *fname)
{
    printf("%d, %s\n", image->width, fname);
    /*
    int channels_in_file;
    image->data = stbi_load(
        fname,
        &(image->width),
        &(image->height),
        &channels_in_file,
        3);
    */
}

/* . */
int
embImage_write(EmbImage *image, char *fname)
{
    printf("%d, %s\n", image->width, fname);
    /*
    return stbi_write_png(
         fname,
         image->width,
        image->height,
        4,
        image->data,
        4*image->width);
*/
    return 0;
}

/* . */
void
embImage_free(EmbImage *image)
{
    safe_free(image->data);
}
