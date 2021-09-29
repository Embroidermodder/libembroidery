#include <stdio.h>

/* Proof of concept for the datafile approach.
 *
 * Steps through the contents of the string table svg_all_tokens.
 */

int svg_all_tokens_pos = 0;

int main(int argc, char *argv[])
{
    char buffer[21];
    FILE *f;
    f = fopen("libembroidery_data.bin", "rb");
    int p, str;
    /* get the position of svg_all_tokens */
    fseek(f, svg_all_tokens_pos, SEEK_SET);
    fread(&p, 4, 1, f);
    printf("%d\n", p);
str = 1;
    while (str) {
        /* get the position of next token */
    fseek(f, p, SEEK_SET);
    fread(&str, 4, 1, f);
        printf("%d\n", str);
        p += 4;
        /* go to string */
        fseek(f, str, SEEK_SET);
        fread(buffer, 1, 20, f);
        printf("%s\n", buffer);
    }
    fclose(f);
    return 0;
}
