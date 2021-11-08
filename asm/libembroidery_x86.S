/* GAS assembly comments are C-style.
 * The .S extention means "run through C preprocessor first".
 */

	.data
welcome_message:
        .ascii "EMBROIDER EMBEDDED VERSION 0.1\n\n"
	.ascii "    Copyright 2021 The Embroidermodder Team\n"
	.ascii "    Licensed under the zlib license.\n"
	.ascii "    Please obtain a copy of the printed documentation from:\n"
	.ascii "        https://embroidermodder.org/libembroidery_manual_current.pdf\n"
        .ascii "    for help on usage.\n\n"
	.equ welcome_message_len, . - welcome_message

/* Linux system defines
 * --------------------
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

#include "asm_embroidery.h"

/* .set directive? */

        .text
.globl main
main:
	pushl	%ebp
	movl	$welcome_message_len, %edx
	movl	$welcome_message, %ecx
	movl	$STDOUT, %ebx
	movl	$SYS_WRITE, %eax
	int	$0x80
	movl	$0, %ebx
	movl	$SYS_EXIT, %eax
	int	$0x80
	leave
        ret

