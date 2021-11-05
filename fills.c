#include "embroidery.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *rules[] = {"+BF-AFA-FB+", "-AF+BFB+FA-"};

L_system hilbert_curve_l_system = {
    'A', "AB", "F+-", (char**)rules
};

int max_stitches = 100000;

/* This is a slow generation algorithm */
int lindenmayer_system(L_system L, char *state, int iterations, int complete)
{
    /* We know that the full length of the curve has to fit within
     * the number of stitches and we can cancel consequtive +-, -+
     * etc.
     *

Potential reference:

@book{Prusinkiewicz1996Mar,
	author = {Prusinkiewicz, Przemyslaw and Lindenmayer, Aristid and Hanan, J. S. and Fracchia, F. D. and Fowler, D. R. and de Boer, M. J. M. and Mercer, L.},
	title = {{The Algorithmic Beauty of Plants (The Virtual Laboratory)}},
	year = {1996},
	month = {Mar},
	publisher = {Springer}
}
     */
    char *new_state;
    int j;

    if (complete == 0) {
        state[0] = L.axiom;
        state[1] = 0;
        lindenmayer_system(L, state, iterations, complete+1);
        return 0;
    }

    new_state = state + max_stitches*5;

    new_state[0] = 0;

    /* replace letters using rules by copying to new_state */
    for (j=0; j<strlen(state); j++) {
        if (state[j] >= 'A' && state[j] < 'F') {
            strcat(new_state, L.rules[state[j]-'A']);
        }
        if (state[j] == 'F') strcat(new_state, "F");
        if (state[j] == '+') strcat(new_state, "+");
        if (state[j] == '-') strcat(new_state, "-");
    }
    memcpy(state, new_state, strlen(new_state)+1);

    if (complete < iterations) {
        lindenmayer_system(L, state, iterations, complete+1);
    }
    return 0;
}

int hilbert_curve(int iterations)
{
    /*
    https://en.wikipedia.org/wiki/Hilbert_curve

    Using the Lindenmayer System, so we can save work across
    different functions
    */
    char *state;
    int i, position[2], direction;
    FILE *f;

    /* Make the n-th iteration. */
    state = malloc(max_stitches*10);
    lindenmayer_system(hilbert_curve_l_system, state, iterations, 0);

    /* Convert to an embroidery pattern. */
    position[0] = 0;
    position[1] = 0;
    direction = 0;

    f = fopen("plot.py", "w");
    fprintf(f, "#!/usr/bin/env python3\n");
    fprintf(f, "A = [\n    0, 0");

    for (i=0; i<strlen(state); i++) {
        if (state[i] == '+') {
            direction = (direction + 1) % 4;
            continue;
        }
        if (state[i] == '-') {
            direction = (direction + 3) % 4;
            continue;
        }
        if (state[i] == 'F') {
            switch (direction) {
            case 0:
            default:
                position[0]--;
                break;
            case 1:
                position[1]++;
                break;
            case 2:
                position[0]++;
                break;
            case 3:
                position[1]--;
                break;
            }
            fprintf(f, ",\n    %d, %d", position[0], position[1]);
        }
    }
    fprintf(f, "]\n");

    fprintf(f, "import matplotlib.pyplot as plt\n"
           "plt.plot(A[0::2], A[1::2])\n"
           "plt.show()\n"
    );

    fclose(f);

    system("python3 plot.py");
    free(state);
    return 0;
}

/* using the "paper folding" method (find citation) */
void generate_dragon_curve(char *state, int iterations)
{
    int i, length;
    if (iterations==1) {
        state[0] = 'R';
        state[1] = 0;
        return;
    }
    length = strlen(state);
    for (i=length-1; i>=0; i--) {
        state[2*i+1] = state[i];
        if (i%2 == 0) {
            state[2*i] = 'R';
        }
        else {
            state[2*i] = 'L';
        }
    }
    state[2*length+1] = 0;
    generate_dragon_curve(state, iterations-1);
}

int dragon_curve(int iterations)
{
    return 0;
}
