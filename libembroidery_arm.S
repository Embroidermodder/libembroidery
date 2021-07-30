/*
 * This file is part of libembroidery.
 *
 * Copyright 2021 The Embroidermodder Team
 * Distributed under the terms of the zlib license (see LICENSE).
 *
 * ----------------------------------------------------------------
 *
 * GAS assembly comments are C-style.
 * The .S extention means "run through C preprocessor first".
 *
 * ARM originally Acorn RISC Machine
 * now Advanced RISC Machine
 * The instruction set is called THUMB.
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

/* Look up THUMB defines
 * ---------------------
 */
	.equ SYS_EXIT, 1
	.equ SYS_READ, 3
	.equ SYS_WRITE, 4
	.equ SYS_OPEN, 5
	.equ SYS_CLOSE, 6
	.equ SYS_CREAT, 8
	.equ SYS_LINK, 9
	.equ SYS_UNLINK, 10
	.equ SYS_TIME, 13
	.equ SYS_STAT, 18
	.equ STDOUT, 1
	.equ SUCCESS, 0

        .text
.global _start
_start:
	mov	r2, $welcome_message_len
	mov	r1, %pc
	add	r0, $24
	mov	r0, $STDOUT
	mov	r7, $SYS_WRITE
	svc	$0

	mov	r0, $SUCCESS
	mov	r7, $SYS_EXIT
	svc	$0

