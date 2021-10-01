#include <stdio.h>

/* Proof of concept for the datafile approach.
 *
 * Steps through the contents of the string table svg_all_tokens.
 *
 * Need to test the speed of looping through a pattern with 10k stitches.
 */

int svg_all_tokens_table[] = {0, 4};

int dereference_int(FILE *f, int p)
{
    int out;
    fseek(f, p, SEEK_SET);
    fread(&out, 4, 1, f);
    return out;
}

int get_str(FILE *f, char *s, int p)
{
    int i;
    char c;
    fseek(f, p, SEEK_SET);
    c = 1;
    for (i=0; c; i++) {
        fread(&c, 1, 1, f);
        s[i] = c;
    }
}

int string_table(FILE *f, int *table, char *s, int n)
{
    int p;
    if (n>=table[1]) {
        puts("ERROR: this is outside of the scope of the table.");
        return 0;
    }
    /* get the position of svg_all_tokens */
    p = dereference_int(f, 4*table[0]) + 4*n;
    /* get the position of next token */
    p = dereference_int(f, p);
    /* read string out */
    get_str(f, s, p);
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

