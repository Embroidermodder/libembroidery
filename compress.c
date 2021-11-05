/*
 *  Thanks to Jason Weiler for describing the binary formats of the HUS and
 *  VIP formats at:
 *
 *  http://www.jasonweiler.com/HUSandVIPFileFormatInfo.html
 *
 *  Further thanks to github user tatarize for solving the mystery of the
 *  compression in:
 *
 *  https://github.com/EmbroidePy/pyembroidery
 *
 *  with a description of that work here:
 *
 *  https://stackoverflow.com/questions/7852670/greenleaf-archive-library
 *
 *  This is based on their work.
 */

#include "embroidery.h"

#include <string.h>

static int bit_position;
static char *input_data;
static int input_length;
static int block_elements;
static char *character_huffman;
static int *distance_huffman;

static int get_bits(int start_pos_in_bits, int length);
static int pop(int bit_count);
static int peek(int bit_count);
static int read_variable_length(void);
static int load_character_length_huffman(void);
static void load_character_huffman(int length_huffman);
static void load_distance_huffman(void);
static void load_block(void);
static void get_token(void);
static void get_position(void);

int hus_compress(char *data, int length, char *output, int *output_length)
{
    unsigned char *a = (unsigned char*)output;
    a[0] = length%256;
    a[1] = (length/256)%256;
    a[2] = 0x02;
    a[3] = 0xA0;
    a[4] = 0x01;
    a[5] = 0xFE;
    memcpy(output+6, data, length);
    *output_length = length+6;
    return 0;
}

static int get_bits(int start_pos_in_bits, int length)
{
    int i, end_pos_in_bits, start_pos_in_bytes, end_pos_in_bytes, value;
    int mask_sample_bits, unused_bits, original;

    end_pos_in_bits = start_pos_in_bits + length - 1;
    start_pos_in_bytes = start_pos_in_bits / 8;
    end_pos_in_bytes = end_pos_in_bits / 8;
    value = 0;

    for (i=start_pos_in_bytes; i<end_pos_in_bytes+1; i++) {
        value <<= 8;
        if (i > input_length) {
            break;
        }
        value |= (input_data[i]) & 0xFF;
    }

    unused_bits = (7 - end_pos_in_bits) % 8;
    /* there's a mistake here */
    original = (value >> unused_bits) & 0xFFFFFFFF;
    return original;
}

static int pop(int bit_count)
{
    int value = get_bits(bit_position, bit_count);
    bit_position += bit_count;
    return value;
}

static int read_variable_length(void)
{
    int q, m, s;
    m = pop(3);
    if (m!=7) {
        return m;
    }
    for (q=0; q<13; q++) {
        s = pop(1);
        if (s) {
            m++;
        }
        else {
            break;
        }
    }
    return m;
}

static int load_character_length_huffman(void)
{
    /* current work in translation */
    int count, huffman;
    count = pop(5);
    huffman = 0;
    /*
    if (!count) {
    }
    else {
    }
    */
    return huffman;
}

static void load_character_huffman(int length_huffman)
{

}

static void load_distance_huffman(void)
{

}
    
static void load_block(void)
{

}

static void get_token(void)
{
    if (block_elements <= 0) {
        load_block();
    }
    block_elements--;
    /*
    character_huffman();
    */
}

static void get_position(void)
{
    
}

int hus_decompress(char *data, int length, char *output, int *output_length)
{
    int bits_total, character, i;
    bit_position = 0;
    input_data = data;
    input_length = length;
    /*
    bits_total = length*8;
    i = 0;
    while (bits_total > bit_position && i < *output_length) {
        character = get_token();
        if (character < 0x100) {
            output_data[i] = (char)character;
            i++;
        }
        else if (character == 510) {
            break;
        }
        else {
            length = character - 253;
            position = length output_data - get_position() - 1;
            for (j=position; j<position+length; j++) {
                output_data[i] = output_data[j];
                i++;
            }
        }
    }
    */
    return 0;
}

