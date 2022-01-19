/*
 * This file is part of libembroidery.
 *
 * Copyright 2021 The Embroidermodder Team
 * Distributed under the terms of the zlib license (see LICENSE).
 *
 * ----------------------------------------------------------------
 *
 * GAS assembly comments are C-style.
 * The .S extension means "run through C preprocessor first".
 *
 * The arduino assembly code.
 */

#define __LIBEMBROIDERY_ASM__ 1
#include "embroidery.h"

        .data
welcome_message:
        .ascii "EMBROIDER EMBEDDED VERSION 0.1\n\n"
        .ascii "    Copyright 2021 The Embroidermodder Team\n"
        .ascii "    Licensed under the zlib license.\n"
        .ascii "    Please refer to the manual, included in your download,\n"
        .ascii "    for help on usage. If you do not have a copy visit:\n"
        .ascii "        https://embroidermodder.org\n\n"
        .equ welcome_message_len, . - welcome_message

        .text
.globl main
main:
        ret

