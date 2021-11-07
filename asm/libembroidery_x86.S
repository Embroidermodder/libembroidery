/* GAS assembly comments are C-style.
 * The .S extention means "run through C preprocessor first".
 */

	.data
hello_world:
        .ascii "Hello, world!\n"
	.equ hello_world_len, . - hello_world

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

/* #include "asm_embroidery.h" */

/* .set directive? */

        .text
.globl main
main:
	pushl	%ebp
	movl	$hello_world_len, %edx
	movl	$hello_world, %ecx
	movl	$STDOUT, %ebx
	movl	$SYS_WRITE, %eax
	int	$0x80
	movl	$0, %ebx
	movl	$SYS_EXIT, %eax
	int	$0x80
	leave
        ret

