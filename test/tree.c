/*
 * Testing
 */

#include <string.h>
#include <math.h>

#include "../src/embroidery.h"

typedef struct TestData_ {
    int type;
    EmbString label;
    EmbString value;
} TestData;

TestData data[] = {
    {
        .type = EMB_DATATYPE_STR,
        .label = "string_value",
        .value = "test string value"
    },
    {
        .type = EMB_DATATYPE_INT,
        .label = "integer_value",
        .value = "10"
    },
    {
        .type = -1,
        .label = "END",
        .value = "END"
    },

};

int
main(void)
{
    int i;
    ScriptValue *root = emb_create_root();
    if (!root) {
        return 1;
    }

    puts("Adding data to root.");
    for (i=0; data[i].type >= 0; i++) {
        if (!emb_create_leaf(root, data[i].type, data[i].label, data[i].value)) {
            emb_free_root(root);
            return 2;
        }
    }

    printf("Leaves: %d\n", root->n_leaves);
    for (i=0; i<root->n_leaves; i++) {
        printf("%s\n", root->leaves[i].label);
    }

    debug_message("Checking each item is findable.");
    for (i=0; data[i].type >= 0; i++) {
        printf("Attempting to find \"%s\".\n", data[i].label);
        ScriptValue *found = emb_find_leaf(root, data[i].label);
        if (!found) {
            puts("ERROR: failed to find stored string.");
            emb_free_root(root);
            return 3;
        }
        printf("%s = %s\n", found->label, found->s);
    }

    puts("Printing root.");
    emb_print_tree(root, 0);

    emb_free_root(root);
    return 0;
}

