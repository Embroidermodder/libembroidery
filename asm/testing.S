	.file	"testing.c"
	.text
	.globl	test_functions
	.section	.data.rel.local,"aw"
	.align 32
	.type	test_functions, @object
	.size	test_functions, 72
test_functions:
	.quad	test_circle_tangents
	.quad	test_thread_lookup
	.quad	test_format_table
	.quad	test_create_files
	.quad	test_convert_csv_svg
	.quad	test_convert_csv_dst
	.quad	test_fractal_generation
	.quad	test_arc_properties
	.quad	0
	.globl	tests
	.section	.rodata
	.align 8
.LC0:
	.string	"ctangent 0.001 0.0 0.0 3.0 4.0 0.0 2.25 1.9843 2.25 -1.9843"
.LC1:
	.string	"extension example.zsk .zsk"
	.align 8
.LC2:
	.string	"description example.zsk \"ZSK USA Embroidery Format\""
.LC3:
	.string	"reader example.zsk U"
	.section	.data.rel.local
	.align 32
	.type	tests, @object
	.size	tests, 32
tests:
	.quad	.LC0
	.quad	.LC1
	.quad	.LC2
	.quad	.LC3
	.section	.rodata
.LC4:
	.string	"test%02d%s"
.LC5:
	.string	"test%02d_out%s"
	.align 8
.LC6:
	.string	"Converting test case %d: %s to %s.\n"
	.text
	.globl	test_convert
	.type	test_convert, @function
test_convert:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$432, %rsp
	movl	%edi, -420(%rbp)
	movl	%esi, -424(%rbp)
	movl	%edx, -428(%rbp)
	movl	-424(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	formatTable(%rip), %rdx
	leaq	(%rax,%rdx), %rcx
	movl	-420(%rbp), %edx
	leaq	-208(%rbp), %rax
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	movl	-428(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	formatTable(%rip), %rdx
	leaq	(%rax,%rdx), %rcx
	movl	-420(%rbp), %edx
	leaq	-416(%rbp), %rax
	leaq	.LC5(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-416(%rbp), %rcx
	leaq	-208(%rbp), %rdx
	movl	-420(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-424(%rbp), %edx
	movl	-420(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	create_test_file
	testl	%eax, %eax
	je	.L2
	movl	$1, %eax
	jmp	.L4
.L2:
	leaq	-416(%rbp), %rdx
	leaq	-208(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	convert@PLT
	movl	$0, %eax
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	test_convert, .-test_convert
	.section	.rodata
.LC7:
	.string	"example.zsk"
	.align 8
.LC8:
	.string	"Filename   : %s\nExtension  : %s\nDescription: %s\nReader     : %c\nWriter     : %c\nType       : %d\n\n"
.LC9:
	.string	".zsk"
	.align 8
.LC10:
	.string	"In format table test the extension lookup failed."
.LC11:
	.string	"ZSK USA Embroidery Format"
	.align 8
.LC12:
	.string	"In format table test the description lookup failed."
	.align 8
.LC13:
	.string	"In format table test the reader_state lookup failed."
	.align 8
.LC14:
	.string	"In format table test the write_state lookup failed."
	.align 8
.LC15:
	.string	"In format table test the type lookup failed."
	.text
	.globl	test_format_table
	.type	test_format_table, @function
test_format_table:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	.LC7(%rip), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_identify_format@PLT
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	404+formatTable(%rip), %rdx
	movl	(%rax,%rdx), %esi
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	401+formatTable(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	movsbl	%al, %r8d
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	400+formatTable(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	movsbl	%al, %edi
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	192(%rax), %rdx
	leaq	formatTable(%rip), %rax
	addq	%rdx, %rax
	leaq	8(%rax), %rcx
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	formatTable(%rip), %rdx
	addq	%rax, %rdx
	movq	-8(%rbp), %rax
	subq	$8, %rsp
	pushq	%rsi
	movl	%r8d, %r9d
	movl	%edi, %r8d
	movq	%rax, %rsi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$16, %rsp
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	formatTable(%rip), %rdx
	addq	%rdx, %rax
	leaq	.LC9(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L6
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$20, %eax
	jmp	.L7
.L6:
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	192(%rax), %rdx
	leaq	formatTable(%rip), %rax
	addq	%rdx, %rax
	addq	$8, %rax
	leaq	.LC11(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L8
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$21, %eax
	jmp	.L7
.L8:
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	400+formatTable(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	cmpb	$85, %al
	je	.L9
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$22, %eax
	jmp	.L7
.L9:
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	401+formatTable(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	cmpb	$32, %al
	je	.L10
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$23, %eax
	jmp	.L7
.L10:
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	404+formatTable(%rip), %rdx
	movl	(%rax,%rdx), %eax
	cmpl	$1, %eax
	je	.L11
	leaq	.LC15(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$24, %eax
	jmp	.L7
.L11:
	movl	$0, %eax
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	test_format_table, .-test_format_table
	.globl	test_create_files
	.type	test_create_files, @function
test_create_files:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	jmp	.L13
.L16:
	movl	$8, %esi
	movl	$0, %edi
	call	create_test_file
	movl	%eax, -8(%rbp)
	cmpl	$0, -8(%rbp)
	je	.L14
	movl	-8(%rbp), %eax
	jmp	.L15
.L14:
	addl	$1, -4(%rbp)
.L13:
	cmpl	$2, -4(%rbp)
	jle	.L16
	movl	$0, %eax
.L15:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	test_create_files, .-test_create_files
	.globl	test_convert_from_to
	.type	test_convert_from_to, @function
test_convert_from_to:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L18
.L21:
	movl	-24(%rbp), %edx
	movl	-20(%rbp), %ecx
	movl	-4(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	test_convert
	movl	%eax, -8(%rbp)
	cmpl	$0, -8(%rbp)
	je	.L19
	movl	-8(%rbp), %eax
	jmp	.L20
.L19:
	addl	$1, -4(%rbp)
.L18:
	cmpl	$2, -4(%rbp)
	jle	.L21
	movl	$0, %eax
.L20:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	test_convert_from_to, .-test_convert_from_to
	.globl	test_convert_csv_svg
	.type	test_convert_csv_svg, @function
test_convert_csv_svg:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$49, %esi
	movl	$8, %edi
	call	test_convert_from_to
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	test_convert_csv_svg, .-test_convert_csv_svg
	.globl	test_convert_csv_dst
	.type	test_convert_csv_dst, @function
test_convert_csv_dst:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$49, %esi
	movl	$8, %edi
	call	test_convert_from_to
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	test_convert_csv_dst, .-test_convert_csv_dst
	.globl	cirtan_test
	.data
	.align 32
	.type	cirtan_test, @object
	.size	cirtan_test, 40
cirtan_test:
	.long	981668463
	.long	0
	.long	0
	.long	1077936128
	.long	1082130432
	.long	0
	.long	1074790400
	.long	1073610123
	.long	1074790400
	.long	-1073873525
	.text
	.globl	get_circle
	.type	get_circle, @function
get_circle:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	addq	$8, %rax
	movss	(%rax), %xmm1
	movq	-16(%rbp), %rax
	addq	$4, %rax
	movss	(%rax), %xmm0
	movq	-16(%rbp), %rax
	movl	(%rax), %edx
	movq	-8(%rbp), %rax
	movaps	%xmm1, %xmm2
	movaps	%xmm0, %xmm1
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_circle@PLT
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	get_circle, .-get_circle
	.globl	get_vector
	.type	get_vector, @function
get_vector:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$4, %rax
	movss	(%rax), %xmm0
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movaps	%xmm0, %xmm1
	movd	%eax, %xmm0
	call	emb_vector@PLT
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	get_vector, .-get_vector
	.globl	test_circle_tangents
	.type	test_circle_tangents, @function
test_circle_tangents:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movss	cirtan_test(%rip), %xmm0
	movss	%xmm0, -20(%rbp)
	leaq	4+cirtan_test(%rip), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	get_circle
	leaq	16+cirtan_test(%rip), %rax
	movq	%rax, %rdi
	call	get_vector
	movq	%xmm0, %rax
	movq	%rax, -72(%rbp)
	leaq	24+cirtan_test(%rip), %rax
	movq	%rax, %rdi
	call	get_vector
	movq	%xmm0, %rax
	movq	%rax, -80(%rbp)
	leaq	32+cirtan_test(%rip), %rax
	movq	%rax, %rdi
	call	get_vector
	movq	%xmm0, %rax
	movq	%rax, -88(%rbp)
	movss	-20(%rbp), %xmm0
	movq	-88(%rbp), %r8
	movq	-80(%rbp), %rdi
	movq	-72(%rbp), %rsi
	subq	$8, %rsp
	subq	$40, %rsp
	movq	%rsp, %rax
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-32(%rbp), %rdx
	movq	%rdx, 32(%rax)
	movaps	%xmm0, %xmm3
	movq	%r8, %xmm2
	movq	%rdi, %xmm1
	movq	%rsi, %xmm0
	call	test_ctangents
	addq	$48, %rsp
	movl	%eax, -24(%rbp)
	cmpl	$0, -24(%rbp)
	je	.L31
	movl	-24(%rbp), %eax
	jmp	.L34
.L31:
	leaq	-144(%rbp), %rax
	movss	.LC16(%rip), %xmm2
	movss	.LC17(%rip), %xmm1
	movl	.LC18(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_circle@PLT
	movq	-144(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movq	-128(%rbp), %rax
	movq	-120(%rbp), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, -32(%rbp)
	movss	.LC19(%rip), %xmm1
	movl	.LC20(%rip), %eax
	movd	%eax, %xmm0
	call	emb_vector@PLT
	movq	%xmm0, %rax
	movq	%rax, -72(%rbp)
	movss	.LC21(%rip), %xmm1
	movl	.LC22(%rip), %eax
	movd	%eax, %xmm0
	call	emb_vector@PLT
	movq	%xmm0, %rax
	movq	%rax, -80(%rbp)
	movss	.LC23(%rip), %xmm1
	movl	.LC24(%rip), %eax
	movd	%eax, %xmm0
	call	emb_vector@PLT
	movq	%xmm0, %rax
	movq	%rax, -88(%rbp)
	movss	-20(%rbp), %xmm0
	movq	-88(%rbp), %r8
	movq	-80(%rbp), %rdi
	movq	-72(%rbp), %rsi
	subq	$8, %rsp
	subq	$40, %rsp
	movq	%rsp, %rax
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-32(%rbp), %rdx
	movq	%rdx, 32(%rax)
	movaps	%xmm0, %xmm3
	movq	%r8, %xmm2
	movq	%rdi, %xmm1
	movq	%rsi, %xmm0
	call	test_ctangents
	addq	$48, %rsp
	movl	%eax, -24(%rbp)
	cmpl	$0, -24(%rbp)
	je	.L33
	movl	-24(%rbp), %eax
	jmp	.L34
.L33:
	movl	$0, %eax
.L34:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	test_circle_tangents, .-test_circle_tangents
	.section	.rodata
	.align 8
.LC25:
	.string	"Color : 0x%X\nBrand : %d\nNum   : %d\nName  : %s\n\n"
	.text
	.globl	test_thread_lookup
	.type	test_thread_lookup, @function
test_thread_lookup:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	$-15897809, -4(%rbp)
	movl	$6, -8(%rbp)
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	threadColorNum@PLT
	movl	%eax, -12(%rbp)
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	threadColorName@PLT
	movq	%rax, %rcx
	leaq	-64(%rbp), %rax
	movl	$49, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncpy@PLT
	leaq	-64(%rbp), %rsi
	movl	-12(%rbp), %ecx
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movq	%rsi, %r8
	movl	%eax, %esi
	leaq	.LC25(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	test_thread_lookup, .-test_thread_lookup
	.section	.rodata
.LC26:
	.string	"hilbert_level_3.png"
.LC27:
	.string	"hilbert_level_3.avi"
.LC28:
	.string	"hilbert curve result: %d\n"
.LC29:
	.string	"render result: %d\n"
.LC30:
	.string	"simulate result: %d\n"
	.text
	.globl	test_fractal_generation
	.type	test_fractal_generation, @function
test_fractal_generation:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	call	emb_pattern_create@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$3, %esi
	movq	%rax, %rdi
	call	hilbert_curve@PLT
	movl	%eax, -12(%rbp)
	movq	-8(%rbp), %rax
	leaq	.LC26(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_render@PLT
	movl	%eax, -16(%rbp)
	movq	-8(%rbp), %rax
	leaq	.LC27(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_simulate@PLT
	movl	%eax, -20(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC28(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-16(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC29(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC30(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free@PLT
	movl	-12(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	test_fractal_generation, .-test_fractal_generation
	.section	.rodata
.LC35:
	.string	"Clockwise Test:"
.LC39:
	.string	"Counter-Clockwise Test:"
	.text
	.globl	test_arc_properties
	.type	test_arc_properties, @function
test_arc_properties:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8208, %rsp
	leaq	-8144(%rbp), %rax
	movss	.LC31(%rip), %xmm5
	movss	.LC32(%rip), %xmm4
	pxor	%xmm3, %xmm3
	pxor	%xmm2, %xmm2
	pxor	%xmm1, %xmm1
	movl	.LC31(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_arc@PLT
	movss	.LC34(%rip), %xmm0
	movss	%xmm0, -4(%rbp)
	leaq	-8096(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movq	-8084(%rbp), %rax
	movq	%rax, -8152(%rbp)
	leaq	-7648(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$134217728, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movss	-7648(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
	leaq	-7200(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$128, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movss	-7200(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	leaq	-6752(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$256, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movss	-6752(%rbp), %xmm0
	movss	%xmm0, -16(%rbp)
	leaq	-6304(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$8388608, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movq	-6292(%rbp), %rax
	movq	%rax, -8160(%rbp)
	leaq	-5856(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$1048576, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movss	-5856(%rbp), %xmm0
	movss	%xmm0, -20(%rbp)
	leaq	-5408(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$33554432, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movss	-5408(%rbp), %xmm0
	movss	%xmm0, -24(%rbp)
	leaq	-4960(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$16777216, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movss	-4960(%rbp), %xmm0
	movss	%xmm0, -28(%rbp)
	leaq	-4512(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$268435456, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movzbl	-4504(%rbp), %eax
	movb	%al, -29(%rbp)
	leaq	.LC35(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movzbl	-29(%rbp), %eax
	movsbl	%al, %edi
	movss	-24(%rbp), %xmm5
	movss	-20(%rbp), %xmm4
	movq	-8160(%rbp), %r9
	movss	-8(%rbp), %xmm3
	movss	-16(%rbp), %xmm2
	movss	-12(%rbp), %xmm1
	movq	-8152(%rbp), %r8
	movl	-4(%rbp), %esi
	movss	-28(%rbp), %xmm0
	leaq	-8(%rsp), %rsp
	movss	%xmm0, (%rsp)
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-8144(%rbp), %rax
	movq	-8136(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-8128(%rbp), %rax
	movq	%rax, 16(%rcx)
	movaps	%xmm5, %xmm7
	movaps	%xmm4, %xmm6
	movq	%r9, %xmm5
	movaps	%xmm3, %xmm4
	movaps	%xmm2, %xmm3
	movaps	%xmm1, %xmm2
	movq	%r8, %xmm1
	movd	%esi, %xmm0
	call	printArcResults
	addq	$32, %rsp
	movss	.LC36(%rip), %xmm0
	movss	%xmm0, -4(%rbp)
	leaq	-8208(%rbp), %rax
	movss	.LC31(%rip), %xmm5
	movss	.LC37(%rip), %xmm4
	pxor	%xmm3, %xmm3
	pxor	%xmm2, %xmm2
	pxor	%xmm1, %xmm1
	movl	.LC38(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_arc@PLT
	movq	-8208(%rbp), %rax
	movq	-8200(%rbp), %rdx
	movq	%rax, -8144(%rbp)
	movq	%rdx, -8136(%rbp)
	movq	-8192(%rbp), %rax
	movq	-8184(%rbp), %rdx
	movq	%rax, -8128(%rbp)
	movq	%rdx, -8120(%rbp)
	movq	-8176(%rbp), %rax
	movq	%rax, -8112(%rbp)
	leaq	-4064(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movq	-4052(%rbp), %rax
	movq	%rax, -8152(%rbp)
	leaq	-3616(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$134217728, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movss	-3616(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
	leaq	-3168(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$128, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movss	-3168(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	leaq	-2720(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$256, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movss	-2720(%rbp), %xmm0
	movss	%xmm0, -16(%rbp)
	leaq	-2272(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$8388608, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movq	-2260(%rbp), %rax
	movq	%rax, -8160(%rbp)
	leaq	-1824(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$1048576, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movss	-1824(%rbp), %xmm0
	movss	%xmm0, -20(%rbp)
	leaq	-1376(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$33554432, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movss	-1376(%rbp), %xmm0
	movss	%xmm0, -24(%rbp)
	leaq	-928(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$16777216, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movss	-928(%rbp), %xmm0
	movss	%xmm0, -28(%rbp)
	leaq	-480(%rbp), %rax
	leaq	-8144(%rbp), %rcx
	movl	$268435456, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget@PLT
	movzbl	-472(%rbp), %eax
	movb	%al, -29(%rbp)
	leaq	.LC39(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movzbl	-29(%rbp), %eax
	movsbl	%al, %edi
	movss	-24(%rbp), %xmm5
	movss	-20(%rbp), %xmm4
	movq	-8160(%rbp), %r9
	movss	-8(%rbp), %xmm3
	movss	-16(%rbp), %xmm2
	movss	-12(%rbp), %xmm1
	movq	-8152(%rbp), %r8
	movl	-4(%rbp), %esi
	movss	-28(%rbp), %xmm0
	leaq	-8(%rsp), %rsp
	movss	%xmm0, (%rsp)
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-8144(%rbp), %rax
	movq	-8136(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-8128(%rbp), %rax
	movq	%rax, 16(%rcx)
	movaps	%xmm5, %xmm7
	movaps	%xmm4, %xmm6
	movq	%r9, %xmm5
	movaps	%xmm3, %xmm4
	movaps	%xmm2, %xmm3
	movaps	%xmm1, %xmm2
	movq	%r8, %xmm1
	movd	%esi, %xmm0
	call	printArcResults
	addq	$32, %rsp
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	test_arc_properties, .-test_arc_properties
	.section	.rodata
.LC40:
	.string	"Running Test %d\n"
	.align 8
.LC41:
	.string	"------------------------------------"
	.align 8
.LC42:
	.string	"------------------------------------\n"
	.text
	.globl	testMain
	.type	testMain, @function
testMain:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	cmpl	$7, -20(%rbp)
	jg	.L42
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC40(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC41(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	test_functions(%rip), %rax
	movq	(%rdx,%rax), %rax
	call	*%rax
	movl	%eax, -4(%rbp)
	leaq	.LC42(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	-4(%rbp), %eax
	jmp	.L43
.L42:
	movl	$10, %eax
.L43:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	testMain, .-testMain
	.section	.rodata
.LC44:
	.string	"errors: %f %f\n"
.LC45:
	.string	"Error calculating vector sum."
	.text
	.globl	test_vadd
	.type	test_vadd, @function
test_vadd:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%xmm0, -40(%rbp)
	movq	%xmm1, -48(%rbp)
	movq	%xmm2, -56(%rbp)
	movss	%xmm3, -60(%rbp)
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add@PLT
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	movss	-24(%rbp), %xmm0
	movss	-56(%rbp), %xmm1
	subss	%xmm1, %xmm0
	movss	.LC43(%rip), %xmm1
	andps	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp)
	movss	-20(%rbp), %xmm0
	movss	-52(%rbp), %xmm1
	subss	%xmm1, %xmm0
	movss	.LC43(%rip), %xmm1
	andps	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	movq	-8(%rbp), %rax
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC44(%rip), %rax
	movq	%rax, %rdi
	movl	$2, %eax
	call	printf@PLT
	pxor	%xmm1, %xmm1
	cvtss2sd	-60(%rbp), %xmm1
	movsd	-8(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L53
	leaq	.LC45(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L50
.L53:
	pxor	%xmm1, %xmm1
	cvtss2sd	-60(%rbp), %xmm1
	movsd	-16(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L54
	leaq	.LC45(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L50
.L54:
	movl	$0, %eax
.L50:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	test_vadd, .-test_vadd
	.globl	test_vsubtract
	.type	test_vsubtract, @function
test_vsubtract:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%xmm0, -40(%rbp)
	movq	%xmm1, -48(%rbp)
	movq	%xmm2, -56(%rbp)
	movss	%xmm3, -60(%rbp)
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract@PLT
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	movss	-24(%rbp), %xmm0
	movss	-56(%rbp), %xmm1
	subss	%xmm1, %xmm0
	movss	.LC43(%rip), %xmm1
	andps	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp)
	movss	-20(%rbp), %xmm0
	movss	-52(%rbp), %xmm1
	subss	%xmm1, %xmm0
	movss	.LC43(%rip), %xmm1
	andps	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	movq	-8(%rbp), %rax
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC44(%rip), %rax
	movq	%rax, %rdi
	movl	$2, %eax
	call	printf@PLT
	pxor	%xmm1, %xmm1
	cvtss2sd	-60(%rbp), %xmm1
	movsd	-8(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L64
	leaq	.LC45(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L61
.L64:
	pxor	%xmm1, %xmm1
	cvtss2sd	-60(%rbp), %xmm1
	movsd	-16(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L65
	leaq	.LC45(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L61
.L65:
	movl	$0, %eax
.L61:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	test_vsubtract, .-test_vsubtract
	.section	.rodata
	.align 8
.LC46:
	.string	"Error calculating tangent points."
	.align 8
.LC47:
	.string	"Circle : cr=%f, cx=%f, cy=%f\nPoint  : px=%f, py=%f\nTangent: tx0=%f, ty0=%f\nTangent: tx1=%f, ty1=%f\n\n"
	.align 8
.LC48:
	.string	"Error larger than tolerance, circle test 2: %f.\n\n"
	.text
	.globl	test_ctangents
	.type	test_ctangents, @function
test_ctangents:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%xmm0, -40(%rbp)
	movq	%xmm1, -48(%rbp)
	movq	%xmm2, -56(%rbp)
	movss	%xmm3, -60(%rbp)
	leaq	-24(%rbp), %rdx
	leaq	-16(%rbp), %rax
	movq	-40(%rbp), %r8
	movq	16(%rbp), %rcx
	movss	24(%rbp), %xmm1
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movq	%r8, %xmm2
	movq	%rcx, %xmm0
	call	getCircleTangentPoints@PLT
	testl	%eax, %eax
	jne	.L67
	leaq	.LC46(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L71
.L67:
	movss	-20(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-24(%rbp), %xmm1
	pxor	%xmm7, %xmm7
	cvtss2sd	%xmm1, %xmm7
	movss	-12(%rbp), %xmm1
	pxor	%xmm6, %xmm6
	cvtss2sd	%xmm1, %xmm6
	movss	-16(%rbp), %xmm1
	pxor	%xmm5, %xmm5
	cvtss2sd	%xmm1, %xmm5
	movss	-36(%rbp), %xmm1
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm1, %xmm4
	movss	-40(%rbp), %xmm1
	pxor	%xmm3, %xmm3
	cvtss2sd	%xmm1, %xmm3
	movss	20(%rbp), %xmm1
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm1, %xmm2
	movss	16(%rbp), %xmm1
	cvtss2sd	%xmm1, %xmm1
	movss	24(%rbp), %xmm8
	pxor	%xmm9, %xmm9
	cvtss2sd	%xmm8, %xmm9
	movq	%xmm9, %rax
	subq	$8, %rsp
	leaq	-8(%rsp), %rsp
	movsd	%xmm0, (%rsp)
	movq	%rax, %xmm0
	leaq	.LC47(%rip), %rax
	movq	%rax, %rdi
	movl	$8, %eax
	call	printf@PLT
	addq	$16, %rsp
	movq	-48(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_distance@PLT
	movss	%xmm0, -64(%rbp)
	movq	-56(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_distance@PLT
	addss	-64(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp)
	pxor	%xmm1, %xmm1
	cvtss2sd	-60(%rbp), %xmm1
	movsd	-8(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L73
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	leaq	.LC48(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$1, %eax
	jmp	.L71
.L73:
	movl	$0, %eax
.L71:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	test_ctangents, .-test_ctangents
	.section	.rodata
.LC49:
	.string	"test_arc:"
.LC50:
	.string	"center"
.LC51:
	.string	"chordMid"
	.align 8
.LC52:
	.string	"bulge     = %f\nradius    = %f\ndiameter  = %f\nchord     = %f\nsagitta   = %f\napothem   = %f\nincAngle  = %f\nclockwise = %d\n\n"
	.text
	.globl	printArcResults
	.type	printArcResults, @function
printArcResults:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movss	%xmm0, -4(%rbp)
	movq	%xmm1, -12(%rbp)
	movss	%xmm2, -16(%rbp)
	movss	%xmm3, -20(%rbp)
	movss	%xmm4, -24(%rbp)
	movq	%xmm5, -32(%rbp)
	movss	%xmm6, -36(%rbp)
	movss	%xmm7, -40(%rbp)
	movl	%edi, %eax
	movb	%al, -44(%rbp)
	leaq	.LC49(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	%rax, 16(%rcx)
	call	emb_arc_print@PLT
	addq	$32, %rsp
	movq	-12(%rbp), %rdx
	leaq	.LC50(%rip), %rax
	movq	%rax, %rdi
	movq	%rdx, %xmm0
	call	emb_vector_print@PLT
	movq	-32(%rbp), %rdx
	leaq	.LC51(%rip), %rax
	movq	%rax, %rdi
	movq	%rdx, %xmm0
	call	emb_vector_print@PLT
	movsbl	-44(%rbp), %edx
	pxor	%xmm5, %xmm5
	cvtss2sd	40(%rbp), %xmm5
	pxor	%xmm4, %xmm4
	cvtss2sd	-40(%rbp), %xmm4
	pxor	%xmm3, %xmm3
	cvtss2sd	-36(%rbp), %xmm3
	pxor	%xmm2, %xmm2
	cvtss2sd	-24(%rbp), %xmm2
	pxor	%xmm1, %xmm1
	cvtss2sd	-20(%rbp), %xmm1
	pxor	%xmm0, %xmm0
	cvtss2sd	-16(%rbp), %xmm0
	pxor	%xmm7, %xmm7
	cvtss2sd	-4(%rbp), %xmm7
	movq	%xmm7, %rax
	movl	%edx, %esi
	movapd	%xmm5, %xmm6
	movapd	%xmm4, %xmm5
	movapd	%xmm3, %xmm4
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC52(%rip), %rax
	movq	%rax, %rdi
	movl	$7, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	printArcResults, .-printArcResults
	.section	.rodata
	.align 8
.LC53:
	.string	"ERROR: convert(), cannot allocate memory for p\n"
.LC59:
	.string	"This case is not covered."
	.text
	.globl	create_test_file
	.type	create_test_file, @function
create_test_file:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$328, %rsp
	.cfi_offset 3, -24
	movl	%edi, -324(%rbp)
	movl	%esi, -328(%rbp)
	call	emb_pattern_create@PLT
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L76
	leaq	.LC53(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L90
.L76:
	movq	-32(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	black_thread(%rip), %rax
	movl	$50, %ecx
	movq	%rdx, %rdi
	movq	%rax, %rsi
	rep movsq
	movq	%rsi, %rax
	movq	%rdi, %rdx
	movzwl	(%rax), %ecx
	movw	%cx, (%rdx)
	leaq	2(%rdx), %rdx
	leaq	2(%rax), %rax
	movzbl	(%rax), %ecx
	movb	%cl, (%rdx)
	movq	%r8, %rdi
	call	emb_pattern_addThread@PLT
	addq	$416, %rsp
	cmpl	$2, -324(%rbp)
	je	.L78
	cmpl	$2, -324(%rbp)
	jg	.L79
	cmpl	$0, -324(%rbp)
	je	.L80
	cmpl	$1, -324(%rbp)
	je	.L81
	jmp	.L79
.L80:
	movl	$0, -20(%rbp)
	jmp	.L82
.L83:
	movq	-32(%rbp), %rax
	movl	$0, %edx
	movl	$1, %esi
	movss	.LC31(%rip), %xmm1
	movl	.LC33(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	addl	$1, -20(%rbp)
.L82:
	cmpl	$19, -20(%rbp)
	jle	.L83
	movl	$0, -20(%rbp)
	jmp	.L84
.L85:
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-20(%rbp), %xmm1
	movsd	.LC54(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movq	%rax, %xmm0
	call	sin@PLT
	movsd	.LC55(%rip), %xmm1
	mulsd	%xmm0, %xmm1
	movsd	.LC55(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -252(%rbp)
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-20(%rbp), %xmm1
	movsd	.LC54(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movq	%rax, %xmm0
	call	cos@PLT
	movsd	.LC55(%rip), %xmm1
	mulsd	%xmm0, %xmm1
	movsd	.LC55(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -248(%rbp)
	movl	$0, -256(%rbp)
	movl	$0, -244(%rbp)
	movl	-244(%rbp), %edx
	movl	-256(%rbp), %esi
	movss	-248(%rbp), %xmm0
	movl	-252(%rbp), %ecx
	movq	-32(%rbp), %rax
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
	addl	$1, -20(%rbp)
.L84:
	cmpl	$199, -20(%rbp)
	jle	.L85
	jmp	.L86
.L81:
	movl	$0, -24(%rbp)
	jmp	.L87
.L88:
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-24(%rbp), %xmm1
	movsd	.LC56(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movq	%rax, %xmm0
	call	sin@PLT
	movsd	.LC55(%rip), %xmm1
	mulsd	%xmm0, %xmm1
	movsd	.LC55(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -268(%rbp)
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-24(%rbp), %xmm1
	movsd	.LC57(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	movsd	.LC55(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -264(%rbp)
	movl	$0, -272(%rbp)
	movl	$0, -260(%rbp)
	movl	-260(%rbp), %edx
	movl	-272(%rbp), %esi
	movss	-264(%rbp), %xmm0
	movl	-268(%rbp), %ecx
	movq	-32(%rbp), %rax
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
	addl	$1, -24(%rbp)
.L87:
	cmpl	$99, -24(%rbp)
	jle	.L88
	jmp	.L86
.L78:
	leaq	-320(%rbp), %rax
	movss	.LC37(%rip), %xmm2
	movss	.LC31(%rip), %xmm1
	movl	.LC58(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_circle@PLT
	movq	-32(%rbp), %rax
	movq	40(%rax), %rdx
	subq	$8, %rsp
	subq	$40, %rsp
	movq	%rsp, %rax
	movq	-320(%rbp), %rcx
	movq	-312(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-304(%rbp), %rcx
	movq	-296(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-288(%rbp), %rcx
	movq	%rcx, 32(%rax)
	movq	%rdx, %rdi
	call	emb_array_add_geometry@PLT
	addq	$48, %rsp
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_convertGeometry@PLT
	jmp	.L86
.L79:
	leaq	.LC59(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	nop
.L86:
	movl	-328(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	formatTable(%rip), %rdx
	leaq	(%rax,%rdx), %rcx
	movl	-324(%rbp), %edx
	leaq	-240(%rbp), %rax
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_end@PLT
	movl	-328(%rbp), %edx
	leaq	-240(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_write@PLT
	testb	%al, %al
	jne	.L89
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free@PLT
	movl	$16, %eax
	jmp	.L90
.L89:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free@PLT
	movl	$0, %eax
.L90:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	create_test_file, .-create_test_file
	.section	.rodata
	.align 4
.LC16:
	.long	1088048805
	.align 4
.LC17:
	.long	1093368021
	.align 4
.LC18:
	.long	1101097180
	.align 4
.LC19:
	.long	1100112462
	.align 4
.LC20:
	.long	1103280787
	.align 4
.LC21:
	.long	1099669019
	.align 4
.LC22:
	.long	1100528275
	.align 4
.LC23:
	.long	1096195296
	.align 4
.LC24:
	.long	1104382683
	.align 4
.LC31:
	.long	1065353216
	.align 4
.LC32:
	.long	1073741824
	.align 4
.LC33:
	.long	0
	.align 4
.LC34:
	.long	-1093397555
	.align 4
.LC36:
	.long	1075479162
	.align 4
.LC37:
	.long	1084227584
	.align 4
.LC38:
	.long	1082130432
	.align 16
.LC43:
	.long	2147483647
	.long	0
	.long	0
	.long	0
	.align 8
.LC54:
	.long	1509068714
	.long	1067455935
	.align 8
.LC55:
	.long	0
	.long	1076101120
	.align 8
.LC56:
	.long	-1260068086
	.long	1069834032
	.align 8
.LC57:
	.long	-1717986918
	.long	1069128089
	.align 4
.LC58:
	.long	1092616192
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
