;
; Libembroidery 1.0.0-alpha
; https://www.libembroidery.org
;
; A library for reading, writing, altering and otherwise
; processing machine embroidery files and designs.
;
; Also, the core library supporting the Embroidermodder Project's
; family of machine embroidery interfaces.
;
; ------------------------------------------------------------------------------
;
; The elf64 testing platform is fully automated, create a log like this:
;	nasm -felf64 emb_elf64_test.asm -o emb_elf64_test
;	./emb_elf64_test > output.log
;
; ------------------------------------------------------------------------------
;

	global	_start

; Write message at argument 1 of length in argument 2.
%macro	write	2
	mov	rax, 1
	mov	rdi, 1
	mov	rsi, %1
	mov	rdx, %2
	syscall
%endmacro

; Exit with code in argument 1.
%macro	exit	1
	mov	rax, 60
	mov	rdi, $1
	syscall
%endmacro

; Uses the macros above.
%include "embroidery.inc"

	section .text

_start:
	startup
	exit	0

	section .data

