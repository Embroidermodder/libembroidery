#include <stdio.h>

/* Proof of concept for the datafile approach.
 *
 * Steps through the contents of the string table svg_all_tokens.
 *
 * Need to test the speed of looping through a pattern with 10k stitches.
 */

int svg_all_tokens_table[] = {0, 4};

int string_table(FILE *f, int *table, char *s, int n)
{
    int p, str;
    if (n>=table[1]) {
        puts("ERROR: this is outside of the scope of the table.");
        return 0;
    }
    /* get the position of svg_all_tokens */
    fseek(f, table[0], SEEK_SET);
    fread(&p, 4, 1, f);
    p += 4*n;
    /* get the position of next token */
    fseek(f, p, SEEK_SET);
    fread(&str, 4, 1, f);
    /* go to string */
    fseek(f, str, SEEK_SET);
    fread(s, 1, 20, f);
    return 1;
}

int main(int argc, char *argv[])
{
    char buffer[21];
    FILE *f;
    f = fopen("libembroidery_data.bin", "rb");
    int i;
    for (i=0; i<5; i++) {
        if (!string_table(f, svg_all_tokens_table, buffer, i)) {
            break;
        }
        printf("%s\n", buffer);
    }
    fclose(f);
    return 0;
}

