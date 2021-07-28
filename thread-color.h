#ifndef THREAD_COLOR_H
#define THREAD_COLOR_H

#define Arc_Polyester           0
#define Arc_Rayon               1
#define CoatsAndClark_Rayon     2
#define Exquisite_Polyester     3
#define Fufu_Polyester          4
#define Fufu_Rayon              5
#define Hemingworth_Polyester   6
#define Isacord_Polyester       7
#define Isafil_Rayon            8
#define Marathon_Polyester      9
#define Marathon_Rayon          10
#define Madeira_Polyester       11
#define Madeira_Rayon           12
#define Metro_Polyester         13
#define Pantone                 14
#define RobisonAnton_Polyester  15
#define RobisonAnton_Rayon      16
#define Sigma_Polyester         17
#define Sulky_Rayon             18
#define ThreadArt_Rayon         19
#define ThreadArt_Polyester     20
#define ThreaDelight_Polyester  21
#define Z102_Isacord_Polyester  22

#ifdef __cplusplus
extern "C" {
#endif

typedef struct thread_color_ {
    char name[50];
    unsigned int hex_code;
    int manufacturer_code;
} thread_color;

/* NOTE:
 * colors must be passed in #AARRGGBB format with
 * the alpha value always being FF, i.e. opaque
*/

int threadColorNum(unsigned int color, int brand);
const char* threadColorName(unsigned int color, int brand);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* THREAD_COLOR_H */

/* kate: bom off; indent-mode cstyle; indent-width 4; replace-trailing-space-save on; */
