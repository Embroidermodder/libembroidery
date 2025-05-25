/*! \file compress.S
 * \brief Compression algorithms for the embedded macro version of libembroidery.
 */

	.file	"compress.c"
	.text
	.globl	huffman_lookup_data
	.bss
	.align 8
	.type	huffman_lookup_data, @object
	.size	huffman_lookup_data, 8
huffman_lookup_data:
	.zero	8
	.text
	.globl	hus_compress
	.type	hus_compress, @function
hus_compress:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	movl	-28(%rbp), %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$24, %eax
	addl	%eax, %edx
	movzbl	%dl, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	movl	-28(%rbp), %eax
	leal	255(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$8, %eax
	movl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$24, %eax
	addl	%eax, %edx
	movzbl	%dl, %edx
	subl	%eax, %edx
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movb	%dl, (%rax)
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movb	$2, (%rax)
	movq	-8(%rbp), %rax
	addq	$3, %rax
	movb	$-96, (%rax)
	movq	-8(%rbp), %rax
	addq	$4, %rax
	movb	$1, (%rax)
	movq	-8(%rbp), %rax
	addq	$5, %rax
	movb	$-2, (%rax)
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	-40(%rbp), %rax
	leaq	6(%rax), %rcx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	memcpy@PLT
	movl	-28(%rbp), %eax
	leal	6(%rax), %edx
	movq	-48(%rbp), %rax
	movl	%edx, (%rax)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	hus_compress, .-hus_compress
	.globl	huffman_build_table
	.type	huffman_build_table, @function
huffman_build_table:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movl	$0, -12(%rbp)
	movq	-40(%rbp), %rax
	movl	8008(%rax), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	movl	%eax, -16(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L4
.L6:
	movq	-40(%rbp), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	movl	4(%rax,%rdx,4), %eax
	cmpl	%eax, -12(%rbp)
	jge	.L5
	movq	-40(%rbp), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	movl	4(%rax,%rdx,4), %eax
	movl	%eax, -12(%rbp)
.L5:
	addl	$1, -8(%rbp)
.L4:
	movq	-40(%rbp), %rax
	movl	8008(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L6
	movl	$1, -4(%rbp)
	jmp	.L7
.L13:
	movl	-16(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, -16(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L8
.L12:
	movq	-40(%rbp), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movl	4(%rax,%rdx,4), %eax
	cmpl	%eax, -4(%rbp)
	jne	.L9
	movl	$0, -24(%rbp)
	jmp	.L10
.L11:
	movq	-40(%rbp), %rax
	movl	8012(%rax), %edx
	movl	-24(%rbp), %eax
	addl	%eax, %edx
	movq	-40(%rbp), %rax
	movslq	%edx, %rdx
	leaq	1000(%rdx), %rcx
	movl	-20(%rbp), %edx
	movl	%edx, 8(%rax,%rcx,4)
	movq	-40(%rbp), %rax
	movl	8012(%rax), %eax
	leal	1(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, 8012(%rax)
	addl	$1, -24(%rbp)
.L10:
	movl	-24(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jl	.L11
.L9:
	addl	$1, -20(%rbp)
.L8:
	movq	-40(%rbp), %rax
	movl	4004(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L12
	addl	$1, -4(%rbp)
.L7:
	movq	-40(%rbp), %rax
	movl	8008(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jle	.L13
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	huffman_build_table, .-huffman_build_table
	.globl	huffman_lookup
	.type	huffman_lookup, @function
huffman_lookup:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	leaq	huffman_lookup_data(%rip), %rax
	movq	%rax, -8(%rbp)
	movl	8024(%rbp), %eax
	testl	%eax, %eax
	jne	.L15
	movl	16(%rbp), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	addq	$4, %rax
	movl	$0, (%rax)
	movq	-8(%rbp), %rax
	jmp	.L16
.L15:
	movl	8024(%rbp), %eax
	movl	$16, %edx
	subl	%eax, %edx
	movl	-20(%rbp), %eax
	movl	%edx, %ecx
	sarl	%cl, %eax
	cltq
	addq	$1000, %rax
	movl	24(%rbp,%rax,4), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movq	-8(%rbp), %rdx
	addq	$4, %rdx
	cltq
	movl	20(%rbp,%rax,4), %eax
	movl	%eax, (%rdx)
	movq	-8(%rbp), %rax
.L16:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	huffman_lookup, .-huffman_lookup
	.globl	compress_init
	.type	compress_init, @function
compress_init:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	compress_init, .-compress_init
	.globl	compress_get_bits
	.type	compress_get_bits, @function
compress_get_bits:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movq	-40(%rbp), %rax
	movl	(%rax), %edx
	movl	-44(%rbp), %eax
	addl	%edx, %eax
	subl	$1, %eax
	movl	%eax, -12(%rbp)
	movq	-40(%rbp), %rax
	movl	(%rax), %eax
	leal	7(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$3, %eax
	movl	%eax, -16(%rbp)
	movl	-12(%rbp), %eax
	leal	7(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$3, %eax
	movl	%eax, -20(%rbp)
	movl	$0, -8(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -4(%rbp)
	jmp	.L19
.L22:
	sall	$8, -8(%rbp)
	movq	-40(%rbp), %rax
	movl	16(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jg	.L24
	movq	-40(%rbp), %rax
	movq	8(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movzbl	%al, %eax
	orl	%eax, -8(%rbp)
	addl	$1, -4(%rbp)
.L19:
	movl	-20(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jge	.L22
	jmp	.L21
.L24:
	nop
.L21:
	movl	$7, %eax
	subl	-12(%rbp), %eax
	movl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$29, %eax
	addl	%eax, %edx
	andl	$7, %edx
	subl	%eax, %edx
	movl	%edx, -24(%rbp)
	movl	-44(%rbp), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	subl	$1, %eax
	movl	%eax, -28(%rbp)
	movl	-24(%rbp), %eax
	movl	-8(%rbp), %edx
	movl	%eax, %ecx
	sarl	%cl, %edx
	movl	%edx, %eax
	andl	-28(%rbp), %eax
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	compress_get_bits, .-compress_get_bits
	.globl	compress_pop
	.type	compress_pop, @function
compress_pop:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	-28(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	compress_get_bits
	movl	%eax, -4(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %edx
	movl	-28(%rbp), %eax
	addl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	compress_pop, .-compress_pop
	.globl	compress_peek
	.type	compress_peek, @function
compress_peek:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	compress_get_bits
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	compress_peek, .-compress_peek
	.globl	compress_read_variable_length
	.type	compress_read_variable_length, @function
compress_read_variable_length:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	$3, %esi
	movq	%rax, %rdi
	call	compress_pop
	movl	%eax, -8(%rbp)
	cmpl	$7, -8(%rbp)
	je	.L30
	movl	-8(%rbp), %eax
	jmp	.L31
.L30:
	movl	$0, -4(%rbp)
	jmp	.L32
.L36:
	movq	-24(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	compress_pop
	movl	%eax, -12(%rbp)
	cmpl	$0, -12(%rbp)
	je	.L37
	addl	$1, -8(%rbp)
	addl	$1, -4(%rbp)
.L32:
	cmpl	$12, -4(%rbp)
	jle	.L36
	jmp	.L35
.L37:
	nop
.L35:
	movl	-8(%rbp), %eax
.L31:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	compress_read_variable_length, .-compress_read_variable_length
	.globl	compress_load_character_length_huffman
	.type	compress_load_character_length_huffman, @function
compress_load_character_length_huffman:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	compress_pop
	movl	%eax, -8(%rbp)
	cmpl	$0, -8(%rbp)
	jne	.L39
	movq	-24(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	compress_pop
	movq	-24(%rbp), %rdx
	movl	%eax, 28(%rdx)
	jmp	.L40
.L39:
	movl	$0, -4(%rbp)
	jmp	.L41
.L42:
	movq	-24(%rbp), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	addq	$4, %rdx
	movl	$0, 16(%rax,%rdx,4)
	addl	$1, -4(%rbp)
.L41:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L42
	movl	$0, -4(%rbp)
	jmp	.L43
.L45:
	cmpl	$3, -4(%rbp)
	jne	.L44
	movq	-24(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	compress_pop
	addl	%eax, -4(%rbp)
.L44:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	compress_read_variable_length
	movq	-24(%rbp), %rdx
	movl	-4(%rbp), %ecx
	movslq	%ecx, %rcx
	addq	$4, %rcx
	movl	%eax, 16(%rdx,%rcx,4)
	addl	$1, -4(%rbp)
.L43:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L45
.L40:
	movq	-24(%rbp), %rax
	addq	$28, %rax
	movq	%rax, %rdi
	call	huffman_build_table
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	compress_load_character_length_huffman, .-compress_load_character_length_huffman
	.globl	compress_load_character_huffman
	.type	compress_load_character_huffman, @function
compress_load_character_huffman:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	$9, %esi
	movq	%rax, %rdi
	call	compress_pop
	movl	%eax, -8(%rbp)
	cmpl	$0, -8(%rbp)
	jne	.L47
	movq	-24(%rbp), %rax
	movl	$9, %esi
	movq	%rax, %rdi
	call	compress_pop
	movq	-24(%rbp), %rdx
	movl	%eax, 8044(%rdx)
	jmp	.L48
.L47:
	movl	$0, -4(%rbp)
	jmp	.L49
.L53:
	movq	-24(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	compress_peek
	movl	%eax, %r8d
	movq	-24(%rbp), %rax
	subq	$8016, %rsp
	movq	%rsp, %rdx
	movq	%rdx, %rdi
	addq	$28, %rax
	movl	$1002, %edx
	movq	%rax, %rsi
	movq	%rdx, %rcx
	rep movsq
	movl	%r8d, %edi
	call	huffman_lookup
	addq	$8016, %rsp
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	addq	$4, %rax
	movl	(%rax), %eax
	addl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L50
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	addl	%eax, -4(%rbp)
	jmp	.L49
.L50:
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$1, %eax
	jne	.L51
	movq	-24(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	compress_pop
	addl	$3, %eax
	addl	%eax, -4(%rbp)
	jmp	.L49
.L51:
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$2, %eax
	jne	.L52
	movq	-24(%rbp), %rax
	movl	$9, %esi
	movq	%rax, %rdi
	call	compress_pop
	addl	$20, %eax
	addl	%eax, -4(%rbp)
	jmp	.L49
.L52:
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-2(%rax), %ecx
	movq	-24(%rbp), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	addq	$2008, %rdx
	movl	%ecx, 16(%rax,%rdx,4)
	addl	$1, -4(%rbp)
.L49:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L53
.L48:
	movq	-24(%rbp), %rax
	addq	$8044, %rax
	movq	%rax, %rdi
	call	huffman_build_table
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	compress_load_character_huffman, .-compress_load_character_huffman
	.globl	compress_load_distance_huffman
	.type	compress_load_distance_huffman, @function
compress_load_distance_huffman:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	compress_pop
	movl	%eax, -8(%rbp)
	cmpl	$0, -8(%rbp)
	jne	.L55
	movq	-24(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	compress_pop
	movq	-24(%rbp), %rdx
	movl	%eax, 16060(%rdx)
	jmp	.L56
.L55:
	movl	$0, -4(%rbp)
	jmp	.L57
.L58:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	compress_read_variable_length
	movq	-24(%rbp), %rdx
	movl	-4(%rbp), %ecx
	movslq	%ecx, %rcx
	addq	$4012, %rcx
	movl	%eax, 16(%rdx,%rcx,4)
	addl	$1, -4(%rbp)
.L57:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L58
.L56:
	movq	-24(%rbp), %rax
	addq	$16060, %rax
	movq	%rax, %rdi
	call	huffman_build_table
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	compress_load_distance_huffman, .-compress_load_distance_huffman
	.globl	compress_load_block
	.type	compress_load_block, @function
compress_load_block:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	compress_pop
	movq	-8(%rbp), %rdx
	movl	%eax, 24(%rdx)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	compress_load_character_length_huffman
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	compress_load_character_huffman
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	compress_load_distance_huffman
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	compress_load_block, .-compress_load_block
	.globl	compress_get_token
	.type	compress_get_token, @function
compress_get_token:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	jg	.L61
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	compress_load_block
.L61:
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	leal	-1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-24(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	compress_peek
	movl	%eax, %r8d
	movq	-24(%rbp), %rax
	subq	$8016, %rsp
	movq	%rsp, %rdx
	movq	%rdx, %rdi
	addq	$8044, %rax
	movl	$1002, %edx
	movq	%rax, %rsi
	movq	%rdx, %rcx
	rep movsq
	movl	%r8d, %edi
	call	huffman_lookup
	addq	$8016, %rsp
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$4, %rax
	movl	(%rax), %eax
	addl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	compress_get_token, .-compress_get_token
	.globl	compress_get_position
	.type	compress_get_position, @function
compress_get_position:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -32(%rbp)
	movq	-32(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	compress_peek
	movl	%eax, %r8d
	movq	-32(%rbp), %rax
	subq	$8016, %rsp
	movq	%rsp, %rdx
	movq	%rdx, %rdi
	addq	$16060, %rax
	movl	$1002, %edx
	movq	%rax, %rsi
	movq	%rdx, %rcx
	rep movsq
	movl	%r8d, %edi
	call	huffman_lookup
	addq	$8016, %rsp
	movq	%rax, -16(%rbp)
	movq	-32(%rbp), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	addq	$4, %rax
	movl	(%rax), %eax
	addl	%eax, %edx
	movq	-32(%rbp), %rax
	movl	%edx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L64
	movl	$0, %eax
	jmp	.L65
.L64:
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	subl	$1, %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	$1, %edx
	movl	%edx, %ebx
	movl	%eax, %ecx
	sall	%cl, %ebx
	movl	-20(%rbp), %edx
	movq	-32(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	compress_pop
	addl	%ebx, %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
.L65:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	compress_get_position, .-compress_get_position
	.globl	hus_decompress
	.type	hus_decompress, @function
hus_decompress:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%rcx, -64(%rbp)
	movl	$24080, %edi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	$0, (%rax)
	movq	-16(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-16(%rbp), %rax
	movl	-44(%rbp), %edx
	movl	%edx, 16(%rax)
	movl	-44(%rbp), %eax
	leal	0(,%rax,8), %edx
	movq	-16(%rbp), %rax
	movl	%edx, 20(%rax)
	movl	$0, -4(%rbp)
	jmp	.L67
.L73:
	movl	$0, -20(%rbp)
	cmpl	$255, -20(%rbp)
	jg	.L68
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movl	-20(%rbp), %edx
	movb	%dl, (%rax)
	addl	$1, -4(%rbp)
	jmp	.L67
.L68:
	cmpl	$510, -20(%rbp)
	je	.L75
	movl	-20(%rbp), %eax
	subl	$253, %eax
	movl	%eax, -44(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	compress_get_position
	movl	-4(%rbp), %edx
	subl	%eax, %edx
	subl	$1, %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -8(%rbp)
	jmp	.L71
.L72:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rcx
	movq	-56(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	addl	$1, -4(%rbp)
	addl	$1, -8(%rbp)
.L71:
	movq	-16(%rbp), %rax
	movl	(%rax), %edx
	movl	-44(%rbp), %eax
	addl	%edx, %eax
	cmpl	%eax, -8(%rbp)
	jl	.L72
.L67:
	movq	-16(%rbp), %rax
	movl	20(%rax), %edx
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jle	.L70
	movq	-64(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L73
	jmp	.L70
.L75:
	nop
.L70:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	hus_decompress, .-hus_decompress
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
