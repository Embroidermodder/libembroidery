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
;	./emb_elf64_test
;
; You will then find find a ".log" file named after the current patch in the
; same directory that you ran the binary.
;
; ------------------------------------------------------------------------------
;

%include "embroidery.inc"

_start:
	mov	rax, 60
	syscall

