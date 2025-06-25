/*!
 * \file emb_repl.c
 * \brief Utility for using the scripting environment.
 *
 * Libembroidery 1.0.0-alpha
 * https://www.libembroidery.org
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright 2018-2025 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "embroidery.h"

int
main(int argc, char *argv[])
{
    /* When the current opened parenthesis has closed. */
    int level = 0;
    int c;
    ScriptEnv *env = create_script_env();
    while ((c = getchar()) != EOF) {
        if (c == '(') {
            level++;
        }
        if (c == ')') {
            level--;
            if (level == 0) {
                putchar(c);
            }
        }
        if (c == 'A') {
            c = 'a';
        }
    }
    free_script_env(env);

    return 0;
}

