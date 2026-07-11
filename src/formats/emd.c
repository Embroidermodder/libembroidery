/* The Elna Embroidery Format (.emd)
 * Stitch Only Format.
 */

#include "embroidery.h"

int8_t emdDecode(uint8_t inputByte)
{
    if (inputByte >= 0x80) {
        return (-~inputByte) - 1;
    }
    return inputByte;
}

/* . */
int8_t readEmd(EmbPattern *pattern, FILE *file)
{
    uint8_t b[2];
    uint8_t jemd0[6];           /* TODO: more descriptive name */
    int width, height, colors, length;

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    if (length < 0x30) {
        puts("File invalid: shorter than the header.");
        return 0;
    }
    fseek(file, 0, SEEK_SET);

    if (fread(jemd0, 1, 6, file) != 6) {
        puts("ERROR: Failed to read 6 bytes for jemd0");
        return 0;
    }
    width = emb_read_i16(file);
    height = emb_read_i16(file);
    colors = emb_read_i16(file);
    printf("%d %d %d\n", width, height, colors);

    fseek(file, 0x30, SEEK_SET);

    while (!feof(file)) {
        int8_t dx, dy;
        int flags = NORMAL;
        if (fread(b, 1, 2, file) != 2) {
            puts("ERROR: Failed to read 2 bytes for stitch.");
            return 0;
        }

        if (b[0] == 0x80) {
            if (b[1] == 0x2A) {
                emb_add_stitch(pattern, 0, 0, STOP, 1);
                continue;
            } else if (b[1] == 0x80) {
                if (fread(b, 1, 2, file) != 2) {
                    puts("ERROR: Failed to read 2 bytes for stitch.");
                    return 0;
                }
                flags = TRIM;
            } else if (b[1] == 0xFD) {
                emb_add_stitch(pattern, 0, 0, END, 1);
                break;
            } else {
                continue;
            }
        }
        dx = emdDecode(b[0]);
        dy = emdDecode(b[1]);
        emb_add_stitch(pattern, dx / 10.0f, dy / 10.0f, flags, 1);
    }
    return 1;
}

int8_t writeEmd(EmbPattern *pattern, FILE *file)
{
    puts("writeEmd not implemented.");
    if (emb_verbose > 1) {
        printf("Called with %p %p\n", (void *)pattern, (void *)file);
    }
    return 0;                   /*TODO: finish writeEmd */
}

