	.file	"geometry.c"
	.text
	.globl	attribute_get_table
	.data
	.align 32
	.type	attribute_get_table, @object
	.size	attribute_get_table, 80
attribute_get_table:
	.long	0
	.long	0
	.long	152
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	49160
	.long	0
	.long	0
	.long	0
	.globl	attribute_set_table
	.align 32
	.type	attribute_set_table, @object
	.size	attribute_set_table, 80
attribute_set_table:
	.long	0
	.long	0
	.long	24
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	49160
	.long	0
	.long	0
	.long	0
	.globl	attribute_types
	.align 32
	.type	attribute_types, @object
	.size	attribute_types, 80
attribute_types:
	.long	6
	.long	6
	.long	6
	.long	5
	.long	5
	.long	5
	.long	5
	.long	5
	.long	5
	.long	5
	.long	5
	.long	5
	.long	5
	.long	5
	.long	5
	.long	5
	.long	4
	.long	4
	.long	4
	.long	4
	.text
	.globl	emb_vector
	.type	emb_vector, @function
emb_vector:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	%xmm0, -20(%rbp)
	movss	%xmm1, -24(%rbp)
	movss	-20(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-24(%rbp), %xmm0
	movss	%xmm0, -4(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	emb_vector, .-emb_vector
	.globl	emb_vector_normalize
	.type	emb_vector_normalize, @function
emb_vector_normalize:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_length
	movd	%xmm0, %eax
	movl	%eax, -4(%rbp)
	movss	-24(%rbp), %xmm0
	divss	-4(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	movss	-20(%rbp), %xmm0
	divss	-4(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
	movq	-12(%rbp), %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	emb_vector_normalize, .-emb_vector_normalize
	.globl	emb_vector_scale
	.type	emb_vector_scale, @function
emb_vector_scale:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%xmm0, -24(%rbp)
	movss	%xmm1, -28(%rbp)
	movss	-24(%rbp), %xmm0
	mulss	-28(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-20(%rbp), %xmm0
	mulss	-28(%rbp), %xmm0
	movss	%xmm0, -4(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	emb_vector_scale, .-emb_vector_scale
	.globl	emb_vector_add
	.type	emb_vector_add, @function
emb_vector_add:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	movss	-24(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-20(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	emb_vector_add, .-emb_vector_add
	.globl	emb_vector_average
	.type	emb_vector_average, @function
emb_vector_average:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	movss	-24(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	addss	%xmm0, %xmm1
	movss	.LC0(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-20(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	addss	%xmm0, %xmm1
	movss	.LC0(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	emb_vector_average, .-emb_vector_average
	.globl	emb_vector_subtract
	.type	emb_vector_subtract, @function
emb_vector_subtract:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	movss	-24(%rbp), %xmm0
	movss	-32(%rbp), %xmm1
	subss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-20(%rbp), %xmm0
	movss	-28(%rbp), %xmm1
	subss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	emb_vector_subtract, .-emb_vector_subtract
	.globl	emb_vector_dot
	.type	emb_vector_dot, @function
emb_vector_dot:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%xmm0, -8(%rbp)
	movq	%xmm1, -16(%rbp)
	movss	-8(%rbp), %xmm1
	movss	-16(%rbp), %xmm0
	mulss	%xmm0, %xmm1
	movss	-4(%rbp), %xmm2
	movss	-12(%rbp), %xmm0
	mulss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	emb_vector_dot, .-emb_vector_dot
	.globl	emb_vector_cross
	.type	emb_vector_cross, @function
emb_vector_cross:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%xmm0, -8(%rbp)
	movq	%xmm1, -16(%rbp)
	movss	-8(%rbp), %xmm1
	movss	-12(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	movss	-4(%rbp), %xmm2
	movss	-16(%rbp), %xmm1
	mulss	%xmm2, %xmm1
	subss	%xmm1, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	emb_vector_cross, .-emb_vector_cross
	.globl	emb_vector_transpose_product
	.type	emb_vector_transpose_product, @function
emb_vector_transpose_product:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	movss	-24(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-20(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	emb_vector_transpose_product, .-emb_vector_transpose_product
	.globl	emb_vector_length
	.type	emb_vector_length, @function
emb_vector_length:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%xmm0, -8(%rbp)
	movss	-8(%rbp), %xmm1
	movss	-8(%rbp), %xmm0
	mulss	%xmm0, %xmm1
	movss	-4(%rbp), %xmm2
	movss	-4(%rbp), %xmm0
	mulss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtss2sd	%xmm0, %xmm3
	movq	%xmm3, %rax
	movq	%rax, %xmm0
	call	sqrt@PLT
	cvtsd2ss	%xmm0, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	emb_vector_length, .-emb_vector_length
	.globl	emb_vector_relativeX
	.type	emb_vector_relativeX, @function
emb_vector_relativeX:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$40, %rsp
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	movq	%xmm2, -40(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_dot
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	emb_vector_relativeX, .-emb_vector_relativeX
	.globl	emb_vector_relativeY
	.type	emb_vector_relativeY, @function
emb_vector_relativeY:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$40, %rsp
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	movq	%xmm2, -40(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_cross
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	emb_vector_relativeY, .-emb_vector_relativeY
	.globl	emb_vector_angle
	.type	emb_vector_angle, @function
emb_vector_angle:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%xmm0, -8(%rbp)
	movss	-8(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-4(%rbp), %xmm1
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm1, %xmm2
	movq	%xmm2, %rax
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	atan2@PLT
	cvtsd2ss	%xmm0, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	emb_vector_angle, .-emb_vector_angle
	.globl	emb_vector_unit
	.type	emb_vector_unit, @function
emb_vector_unit:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movss	%xmm0, -20(%rbp)
	pxor	%xmm1, %xmm1
	cvtss2sd	-20(%rbp), %xmm1
	movq	%xmm1, %rax
	movq	%rax, %xmm0
	call	cos@PLT
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	pxor	%xmm2, %xmm2
	cvtss2sd	-20(%rbp), %xmm2
	movq	%xmm2, %rax
	movq	%rax, %xmm0
	call	sin@PLT
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -4(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	emb_vector_unit, .-emb_vector_unit
	.globl	emb_vector_distance
	.type	emb_vector_distance, @function
emb_vector_distance:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_length
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	emb_vector_distance, .-emb_vector_distance
	.globl	emb_geometry_move
	.type	emb_geometry_move, @function
emb_geometry_move:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -32(%rbp)
	movq	%xmm0, -40(%rbp)
	movq	-32(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	je	.L32
	cmpl	$2, %eax
	je	.L33
	jmp	.L31
.L32:
	movq	-32(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rbx
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add
	movq	%xmm0, %rax
	movq	%rax, (%rbx)
	movq	-24(%rbp), %rbx
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add
	movq	%xmm0, %rax
	movq	%rax, 8(%rbx)
	movq	-24(%rbp), %rbx
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add
	movq	%xmm0, %rax
	movq	%rax, 16(%rbx)
	jmp	.L31
.L33:
	movq	-32(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rbx
	movq	-40(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add
	movq	%xmm0, %rax
	movq	%rax, (%rbx)
	nop
.L31:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	emb_geometry_move, .-emb_geometry_move
	.globl	emb_approx
	.type	emb_approx, @function
emb_approx:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%xmm0, -8(%rbp)
	movq	%xmm1, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_distance
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	epsilon(%rip), %xmm0
	comisd	%xmm1, %xmm0
	seta	%al
	movzbl	%al, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	emb_approx, .-emb_approx
	.globl	emb_width
	.type	emb_width, @function
emb_width:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$2, %eax
	je	.L39
	cmpl	$5, %eax
	je	.L40
	nop
	movsd	.LC1(%rip), %xmm0
	jmp	.L42
.L39:
	movq	-8(%rbp), %rax
	movss	8(%rax), %xmm0
	addss	%xmm0, %xmm0
	cvtss2sd	%xmm0, %xmm0
	jmp	.L42
.L40:
	movq	-8(%rbp), %rax
	movss	8(%rax), %xmm0
	addss	%xmm0, %xmm0
	cvtss2sd	%xmm0, %xmm0
.L42:
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	emb_width, .-emb_width
	.globl	emb_height
	.type	emb_height, @function
emb_height:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$2, %eax
	je	.L45
	cmpl	$5, %eax
	je	.L46
	nop
	movsd	.LC1(%rip), %xmm0
	jmp	.L48
.L45:
	movq	-8(%rbp), %rax
	movss	8(%rax), %xmm0
	addss	%xmm0, %xmm0
	cvtss2sd	%xmm0, %xmm0
	jmp	.L48
.L46:
	movq	-8(%rbp), %rax
	movss	12(%rax), %xmm0
	addss	%xmm0, %xmm0
	cvtss2sd	%xmm0, %xmm0
.L48:
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE24:
	.size	emb_height, .-emb_height
	.globl	emb_radius
	.type	emb_radius, @function
emb_radius:
.LFB25:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	nop
	movsd	.LC1(%rip), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE25:
	.size	emb_radius, .-emb_radius
	.globl	emb_radius_major
	.type	emb_radius_major, @function
emb_radius_major:
.LFB26:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	nop
	movsd	.LC1(%rip), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE26:
	.size	emb_radius_major, .-emb_radius_major
	.globl	emb_radius_minor
	.type	emb_radius_minor, @function
emb_radius_minor:
.LFB27:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	nop
	movsd	.LC1(%rip), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE27:
	.size	emb_radius_minor, .-emb_radius_minor
	.globl	emb_diameter_major
	.type	emb_diameter_major, @function
emb_diameter_major:
.LFB28:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	nop
	movsd	.LC1(%rip), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE28:
	.size	emb_diameter_major, .-emb_diameter_major
	.globl	emb_diameter_minor
	.type	emb_diameter_minor, @function
emb_diameter_minor:
.LFB29:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	nop
	movsd	.LC1(%rip), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE29:
	.size	emb_diameter_minor, .-emb_diameter_minor
	.globl	emb_diameter
	.type	emb_diameter, @function
emb_diameter:
.LFB30:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	nop
	movsd	.LC1(%rip), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE30:
	.size	emb_diameter, .-emb_diameter
	.globl	emb_quadrant
	.type	emb_quadrant, @function
emb_quadrant:
.LFB31:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movss	.LC2(%rip), %xmm0
	movss	%xmm0, -4(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -24(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	movq	-40(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$2, %eax
	je	.L63
	cmpl	$5, %eax
	je	.L64
	jmp	.L66
.L63:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-40(%rbp), %rax
	movss	8(%rax), %xmm0
	movss	%xmm0, -4(%rbp)
	jmp	.L66
.L64:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	movl	-44(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$-1240768329, %rdx, %rdx
	shrq	$32, %rdx
	addl	%eax, %edx
	sarl	$7, %edx
	movl	%eax, %ecx
	sarl	$31, %ecx
	subl	%ecx, %edx
	imull	$180, %edx, %ecx
	subl	%ecx, %eax
	movl	%eax, %edx
	testl	%edx, %edx
	jne	.L67
	movq	-40(%rbp), %rax
	movss	8(%rax), %xmm0
	movss	%xmm0, -4(%rbp)
	jmp	.L70
.L67:
	movq	-40(%rbp), %rax
	movss	12(%rax), %xmm0
	movss	%xmm0, -4(%rbp)
.L70:
	nop
.L66:
	pxor	%xmm1, %xmm1
	cvtsi2ssl	-44(%rbp), %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	radians
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -16(%rbp)
	movss	-24(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movsd	%xmm2, -56(%rbp)
	pxor	%xmm3, %xmm3
	cvtss2sd	-4(%rbp), %xmm3
	movsd	%xmm3, -64(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %xmm0
	call	cos@PLT
	mulsd	-64(%rbp), %xmm0
	addsd	-56(%rbp), %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -24(%rbp)
	movss	-20(%rbp), %xmm0
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm0, %xmm4
	movsd	%xmm4, -56(%rbp)
	pxor	%xmm5, %xmm5
	cvtss2sd	-4(%rbp), %xmm5
	movsd	%xmm5, -64(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %xmm0
	call	sin@PLT
	mulsd	-64(%rbp), %xmm0
	addsd	-56(%rbp), %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE31:
	.size	emb_quadrant, .-emb_quadrant
	.globl	emb_angle
	.type	emb_angle, @function
emb_angle:
.LFB32:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_angle
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm1
	movsd	.LC4(%rip), %xmm0
	addsd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movsd	.LC4(%rip), %xmm0
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	fmod@PLT
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE32:
	.size	emb_angle, .-emb_angle
	.globl	emb_start_angle
	.type	emb_start_angle, @function
emb_start_angle:
.LFB33:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$496, %rsp
	movq	%rdi, -488(%rbp)
	movq	-488(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	jne	.L77
	leaq	-464(%rbp), %rax
	movq	-488(%rbp), %rcx
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget
	movq	-452(%rbp), %rax
	movq	%rax, -472(%rbp)
	movq	-488(%rbp), %rax
	movq	(%rax), %rdx
	movq	-472(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -480(%rbp)
	movq	-480(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_angle
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm1
	movsd	.LC4(%rip), %xmm0
	addsd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movsd	.LC4(%rip), %xmm0
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	fmod@PLT
	movq	%xmm0, %rax
	jmp	.L75
.L77:
	nop
	movq	.LC5(%rip), %rax
.L75:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE33:
	.size	emb_start_angle, .-emb_start_angle
	.globl	emb_end_angle
	.type	emb_end_angle, @function
emb_end_angle:
.LFB34:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$496, %rsp
	movq	%rdi, -488(%rbp)
	movq	-488(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	jne	.L82
	leaq	-464(%rbp), %rax
	movq	-488(%rbp), %rcx
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget
	movq	-452(%rbp), %rax
	movq	%rax, -472(%rbp)
	movq	-488(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-472(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -480(%rbp)
	movq	-480(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_angle
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm1
	movsd	.LC4(%rip), %xmm0
	addsd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movsd	.LC4(%rip), %xmm0
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	fmod@PLT
	movq	%xmm0, %rax
	jmp	.L80
.L82:
	nop
	movq	.LC5(%rip), %rax
.L80:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE34:
	.size	emb_end_angle, .-emb_end_angle
	.globl	emb_arc_length
	.type	emb_arc_length, @function
emb_arc_length:
.LFB35:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	jne	.L87
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_included_angle
	pxor	%xmm1, %xmm1
	cvtsd2ss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	radians
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movsd	%xmm2, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_radius
	mulsd	-16(%rbp), %xmm0
	jmp	.L85
.L87:
	nop
	pxor	%xmm0, %xmm0
.L85:
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE35:
	.size	emb_arc_length, .-emb_arc_length
	.globl	emb_area
	.type	emb_area, @function
emb_area:
.LFB36:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$13, %eax
	je	.L89
	cmpl	$13, %eax
	jg	.L95
	cmpl	$1, %eax
	je	.L91
	cmpl	$2, %eax
	je	.L92
	jmp	.L95
.L91:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_radius
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_included_angle
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movd	%xmm2, %eax
	movd	%eax, %xmm0
	call	radians
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -24(%rbp)
	movsd	-16(%rbp), %xmm0
	mulsd	%xmm0, %xmm0
	movsd	.LC6(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -48(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %xmm0
	call	sin@PLT
	movsd	-24(%rbp), %xmm1
	subsd	%xmm0, %xmm1
	movsd	-48(%rbp), %xmm0
	mulsd	%xmm1, %xmm0
	jmp	.L93
.L92:
	movq	-40(%rbp), %rax
	movss	8(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp)
	movss	embConstantPi(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	mulsd	-8(%rbp), %xmm0
	mulsd	-8(%rbp), %xmm0
	jmp	.L93
.L89:
	movq	-40(%rbp), %rax
	movss	8(%rax), %xmm1
	movq	-40(%rbp), %rax
	movss	12(%rax), %xmm0
	mulss	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	jmp	.L93
.L95:
	nop
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_width
	movsd	%xmm0, -48(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_height
	mulsd	-48(%rbp), %xmm0
	movq	.LC7(%rip), %xmm1
	andpd	%xmm1, %xmm0
.L93:
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE36:
	.size	emb_area, .-emb_area
	.globl	emb_chord
	.type	emb_chord, @function
emb_chord:
.LFB37:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	jne	.L100
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_distance
	cvtss2sd	%xmm0, %xmm0
	jmp	.L98
.L100:
	nop
	pxor	%xmm0, %xmm0
.L98:
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE37:
	.size	emb_chord, .-emb_chord
	.globl	emb_included_angle
	.type	emb_included_angle, @function
emb_included_angle:
.LFB38:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	jne	.L119
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_chord
	movq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_radius
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	pxor	%xmm0, %xmm0
	comisd	-8(%rbp), %xmm0
	jnb	.L103
	pxor	%xmm0, %xmm0
	comisd	-16(%rbp), %xmm0
	jb	.L116
.L103:
	pxor	%xmm0, %xmm0
	jmp	.L106
.L116:
	movsd	-16(%rbp), %xmm0
	movapd	%xmm0, %xmm1
	addsd	%xmm0, %xmm1
	movsd	-8(%rbp), %xmm0
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	movsd	.LC1(%rip), %xmm1
	comisd	%xmm1, %xmm0
	jbe	.L117
	movsd	.LC1(%rip), %xmm0
	jmp	.L109
.L117:
	movsd	-24(%rbp), %xmm0
.L109:
	movsd	%xmm0, -24(%rbp)
	pxor	%xmm0, %xmm0
	comisd	-24(%rbp), %xmm0
	jbe	.L118
	pxor	%xmm0, %xmm0
	jmp	.L112
.L118:
	movsd	-24(%rbp), %xmm0
.L112:
	movsd	%xmm0, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %xmm0
	call	asin@PLT
	addsd	%xmm0, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movd	%xmm2, %eax
	movd	%eax, %xmm0
	call	degrees
	cvtss2sd	%xmm0, %xmm0
	jmp	.L106
.L119:
	nop
	pxor	%xmm0, %xmm0
.L106:
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE38:
	.size	emb_included_angle, .-emb_included_angle
	.globl	emb_clockwise
	.type	emb_clockwise, @function
emb_clockwise:
.LFB39:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	jne	.L124
	movq	-24(%rbp), %rax
	movss	4(%rax), %xmm0
	movss	.LC8(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movss	%xmm0, 4(%rax)
	movq	-24(%rbp), %rax
	movss	4(%rax), %xmm0
	movss	.LC8(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movss	%xmm0, 12(%rax)
	movq	-24(%rbp), %rax
	movss	20(%rax), %xmm0
	movss	.LC8(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movss	%xmm0, 20(%rax)
	subq	$8, %rsp
	movq	-24(%rbp), %rax
	subq	$40, %rsp
	movq	%rsp, %rdx
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, 16(%rdx)
	movq	%rbx, 24(%rdx)
	movq	32(%rax), %rax
	movq	%rax, 32(%rdx)
	call	emb_arc_clockwise
	addq	$48, %rsp
	jmp	.L122
.L124:
	nop
	movl	$0, %eax
.L122:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE39:
	.size	emb_clockwise, .-emb_clockwise
	.section	.rodata
.LC9:
	.string	"%f\n"
	.text
	.globl	emb_set_start_angle
	.type	emb_set_start_angle, @function
emb_set_start_angle:
.LFB40:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movsd	%xmm0, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %xmm0
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE40:
	.size	emb_set_start_angle, .-emb_set_start_angle
	.globl	emb_set_end_angle
	.type	emb_set_end_angle, @function
emb_set_end_angle:
.LFB41:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movsd	%xmm0, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %xmm0
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE41:
	.size	emb_set_end_angle, .-emb_set_end_angle
	.globl	emb_set_start_point
	.type	emb_set_start_point, @function
emb_set_start_point:
.LFB42:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%xmm0, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	jne	.L134
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	jmp	.L133
.L134:
	nop
.L133:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE42:
	.size	emb_set_start_point, .-emb_set_start_point
	.globl	emb_set_mid_point
	.type	emb_set_mid_point, @function
emb_set_mid_point:
.LFB43:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%xmm0, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	jne	.L138
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 8(%rax)
	jmp	.L137
.L138:
	nop
.L137:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE43:
	.size	emb_set_mid_point, .-emb_set_mid_point
	.globl	emb_set_end_point
	.type	emb_set_end_point, @function
emb_set_end_point:
.LFB44:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%xmm0, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	jne	.L142
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 16(%rax)
	jmp	.L141
.L142:
	nop
.L141:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE44:
	.size	emb_set_end_point, .-emb_set_end_point
	.globl	emb_set_radius
	.type	emb_set_radius, @function
emb_set_radius:
.LFB45:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movsd	%xmm0, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	je	.L148
	cmpl	$2, %eax
	je	.L145
	jmp	.L147
.L145:
	pxor	%xmm0, %xmm0
	cvtsd2ss	-16(%rbp), %xmm0
	movq	-8(%rbp), %rax
	movss	%xmm0, 8(%rax)
	jmp	.L147
.L148:
	nop
.L147:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE45:
	.size	emb_set_radius, .-emb_set_radius
	.globl	emb_set_diameter
	.type	emb_set_diameter, @function
emb_set_diameter:
.LFB46:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movsd	%xmm0, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$2, %eax
	jne	.L152
	movsd	-16(%rbp), %xmm0
	movsd	.LC6(%rip), %xmm1
	divsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movq	-8(%rbp), %rax
	movss	%xmm0, 8(%rax)
	jmp	.L151
.L152:
	nop
.L151:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE46:
	.size	emb_set_diameter, .-emb_set_diameter
	.globl	emb_set_area
	.type	emb_set_area, @function
emb_set_area:
.LFB47:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movsd	%xmm0, -32(%rbp)
	movq	-24(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$2, %eax
	jne	.L156
	movss	embConstantPi(%rip), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-32(%rbp), %xmm0
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	call	sqrt@PLT
	movq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_set_radius
	jmp	.L155
.L156:
	nop
.L155:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE47:
	.size	emb_set_area, .-emb_set_area
	.globl	emb_set_circumference
	.type	emb_set_circumference, @function
emb_set_circumference:
.LFB48:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movsd	%xmm0, -32(%rbp)
	movq	-24(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$2, %eax
	jne	.L160
	movss	embConstantPi(%rip), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-32(%rbp), %xmm0
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_set_diameter
	jmp	.L159
.L160:
	nop
.L159:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE48:
	.size	emb_set_circumference, .-emb_set_circumference
	.globl	emb_set_radius_major
	.type	emb_set_radius_major, @function
emb_set_radius_major:
.LFB49:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movsd	%xmm0, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	addsd	%xmm0, %xmm0
	movq	%xmm0, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_set_diameter_major
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE49:
	.size	emb_set_radius_major, .-emb_set_radius_major
	.globl	emb_set_radius_minor
	.type	emb_set_radius_minor, @function
emb_set_radius_minor:
.LFB50:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movsd	%xmm0, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	addsd	%xmm0, %xmm0
	movq	%xmm0, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_set_diameter_minor
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE50:
	.size	emb_set_radius_minor, .-emb_set_radius_minor
	.globl	emb_set_diameter_major
	.type	emb_set_diameter_major, @function
emb_set_diameter_major:
.LFB51:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movsd	%xmm0, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$5, %eax
	jne	.L166
	pxor	%xmm0, %xmm0
	cvtsd2ss	-16(%rbp), %xmm0
	movq	-8(%rbp), %rax
	movss	%xmm0, 8(%rax)
	jmp	.L165
.L166:
	nop
.L165:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE51:
	.size	emb_set_diameter_major, .-emb_set_diameter_major
	.globl	emb_set_diameter_minor
	.type	emb_set_diameter_minor, @function
emb_set_diameter_minor:
.LFB52:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movsd	%xmm0, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$5, %eax
	jne	.L170
	pxor	%xmm0, %xmm0
	cvtsd2ss	-16(%rbp), %xmm0
	movq	-8(%rbp), %rax
	movss	%xmm0, 8(%rax)
	jmp	.L169
.L170:
	nop
.L169:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE52:
	.size	emb_set_diameter_minor, .-emb_set_diameter_minor
	.globl	emb_circumference
	.type	emb_circumference, @function
emb_circumference:
.LFB53:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$2, %eax
	jne	.L175
	movss	embConstantPi(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movapd	%xmm0, %xmm1
	addsd	%xmm0, %xmm1
	movq	-8(%rbp), %rax
	movss	8(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	mulsd	%xmm1, %xmm0
	jmp	.L173
.L175:
	nop
	movsd	.LC1(%rip), %xmm0
.L173:
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE53:
	.size	emb_circumference, .-emb_circumference
	.globl	embGeometry_init
	.type	embGeometry_init, @function
embGeometry_init:
.LFB54:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	$40, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	-20(%rbp), %edx
	movl	%edx, 28(%rax)
	movq	-8(%rbp), %rax
	movb	$0, 36(%rax)
	movq	-8(%rbp), %rax
	movb	$0, 37(%rax)
	movq	-8(%rbp), %rax
	movb	$0, 38(%rax)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE54:
	.size	embGeometry_init, .-embGeometry_init
	.globl	embGeometry_free
	.type	embGeometry_free, @function
embGeometry_free:
.LFB55:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$5, %eax
	je	.L185
	cmpl	$5, %eax
	jg	.L186
	cmpl	$1, %eax
	je	.L187
	cmpl	$2, %eax
	je	.L188
	jmp	.L186
.L185:
	nop
	jmp	.L179
.L186:
	nop
	jmp	.L179
.L187:
	nop
	jmp	.L179
.L188:
	nop
.L179:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE55:
	.size	embGeometry_free, .-embGeometry_free
	.globl	embGeometry_boundingRect
	.type	embGeometry_boundingRect, @function
embGeometry_boundingRect:
.LFB56:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -28(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -32(%rbp)
	movss	.LC2(%rip), %xmm0
	movss	%xmm0, -24(%rbp)
	movss	.LC2(%rip), %xmm0
	movss	%xmm0, -20(%rbp)
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-16(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	-40(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE56:
	.size	embGeometry_boundingRect, .-embGeometry_boundingRect
	.globl	emb_arc
	.type	emb_arc, @function
emb_arc:
.LFB57:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movss	%xmm0, -76(%rbp)
	movss	%xmm1, -80(%rbp)
	movss	%xmm2, -84(%rbp)
	movss	%xmm3, -88(%rbp)
	movss	%xmm4, -92(%rbp)
	movss	%xmm5, -96(%rbp)
	movss	-76(%rbp), %xmm0
	movss	%xmm0, -64(%rbp)
	movss	-80(%rbp), %xmm0
	movss	%xmm0, -60(%rbp)
	movss	-84(%rbp), %xmm0
	movss	%xmm0, -56(%rbp)
	movss	-88(%rbp), %xmm0
	movss	%xmm0, -52(%rbp)
	movss	-92(%rbp), %xmm0
	movss	%xmm0, -48(%rbp)
	movss	-96(%rbp), %xmm0
	movss	%xmm0, -44(%rbp)
	movl	$1, -36(%rbp)
	movq	-72(%rbp), %rax
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
	movq	-72(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE57:
	.size	emb_arc, .-emb_arc
	.globl	emb_arc_clockwise
	.type	emb_arc_clockwise, @function
emb_arc_clockwise:
.LFB58:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	44(%rbp), %eax
	cmpl	$1, %eax
	je	.L194
	movl	$0, %eax
	jmp	.L198
.L194:
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	32(%rbp), %rax
	movq	%rax, -32(%rbp)
	movss	-40(%rbp), %xmm0
	movss	-48(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	-36(%rbp), %xmm2
	movss	-44(%rbp), %xmm0
	addss	%xmm2, %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	movss	-32(%rbp), %xmm0
	movss	-40(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	-28(%rbp), %xmm2
	movss	-36(%rbp), %xmm0
	addss	%xmm2, %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-48(%rbp), %xmm0
	movss	-32(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	-44(%rbp), %xmm2
	movss	-28(%rbp), %xmm0
	addss	%xmm2, %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -12(%rbp)
	movss	-4(%rbp), %xmm0
	addss	-8(%rbp), %xmm0
	addss	-12(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	comiss	%xmm1, %xmm0
	jb	.L200
	movl	$1, %eax
	jmp	.L198
.L200:
	movl	$0, %eax
.L198:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE58:
	.size	emb_arc_clockwise, .-emb_arc_clockwise
	.section	.rodata
	.align 8
.LC10:
	.string	"ERROR: no intersection, cannot find arcCenter."
	.text
	.globl	emb_arc_center
	.type	emb_arc_center, @function
emb_arc_center:
.LFB59:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$176, %rsp
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	32(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	$0, -36(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -52(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_average
	movq	%xmm0, %rax
	movq	%rax, -68(%rbp)
	movq	-52(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_angle
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	embConstantPi(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC6(%rip), %xmm2
	divsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -4(%rbp)
	movl	-4(%rbp), %eax
	movd	%eax, %xmm0
	call	emb_vector_unit
	movq	%xmm0, %rax
	movq	%rax, -100(%rbp)
	movq	-100(%rbp), %rdx
	movq	-68(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add
	movq	%xmm0, %rax
	movq	%rax, -84(%rbp)
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -60(%rbp)
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_average
	movq	%xmm0, %rax
	movq	%rax, -76(%rbp)
	movq	-60(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_angle
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	embConstantPi(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC6(%rip), %xmm2
	divsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	movl	-8(%rbp), %eax
	movd	%eax, %xmm0
	call	emb_vector_unit
	movq	%xmm0, %rax
	movq	%rax, -108(%rbp)
	movq	-108(%rbp), %rdx
	movq	-76(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add
	movq	%xmm0, %rax
	movq	%rax, -92(%rbp)
	movq	-68(%rbp), %rax
	movq	%rax, -144(%rbp)
	movq	-84(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-76(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	-92(%rbp), %rax
	movq	%rax, -168(%rbp)
	leaq	-36(%rbp), %rsi
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-176(%rbp), %rax
	movq	-168(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-160(%rbp), %rax
	movq	%rax, 16(%rcx)
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-144(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-128(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	%rsi, %rdi
	call	emb_line_intersectionPoint
	addq	$48, %rsp
	movq	%xmm0, %rax
	movq	%rax, -44(%rbp)
	movl	-36(%rbp), %eax
	testl	%eax, %eax
	je	.L202
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L202:
	movq	-44(%rbp), %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE59:
	.size	emb_arc_center, .-emb_arc_center
	.globl	emb_arc_setCenter
	.type	emb_arc_setCenter, @function
emb_arc_setCenter:
.LFB60:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%xmm0, -48(%rbp)
	subq	$8, %rsp
	movq	-40(%rbp), %rax
	subq	$40, %rsp
	movq	%rsp, %rdx
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, 16(%rdx)
	movq	%rbx, 24(%rdx)
	movq	32(%rax), %rax
	movq	%rax, 32(%rdx)
	call	emb_arc_center
	addq	$48, %rsp
	movq	%xmm0, %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	movq	-40(%rbp), %rbx
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add
	movq	%xmm0, %rax
	movq	%rax, (%rbx)
	movq	-40(%rbp), %rbx
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add
	movq	%xmm0, %rax
	movq	%rax, 8(%rbx)
	movq	-40(%rbp), %rbx
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add
	movq	%xmm0, %rax
	movq	%rax, 16(%rbx)
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE60:
	.size	emb_arc_setCenter, .-emb_arc_setCenter
	.globl	emb_arc_setRadius
	.type	emb_arc_setRadius, @function
emb_arc_setRadius:
.LFB61:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)
	movss	%xmm0, -60(%rbp)
	pxor	%xmm0, %xmm0
	comiss	-60(%rbp), %xmm0
	jb	.L210
	movss	.LC11(%rip), %xmm0
	movss	%xmm0, -20(%rbp)
	jmp	.L208
.L210:
	movss	-60(%rbp), %xmm0
	movss	%xmm0, -20(%rbp)
.L208:
	subq	$8, %rsp
	movq	-56(%rbp), %rax
	subq	$40, %rsp
	movq	%rsp, %rdx
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, 16(%rdx)
	movq	%rbx, 24(%rdx)
	movq	32(%rax), %rax
	movq	%rax, 32(%rdx)
	call	emb_arc_center
	addq	$48, %rsp
	movq	%xmm0, %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_length
	movd	%xmm0, %eax
	movl	%eax, -24(%rbp)
	movss	-20(%rbp), %xmm0
	divss	-24(%rbp), %xmm0
	movq	-32(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_scale
	movq	%xmm0, %rax
	movq	%rax, -32(%rbp)
	movq	-56(%rbp), %rbx
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add
	movq	%xmm0, %rax
	movq	%rax, (%rbx)
	movq	-40(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_length
	movd	%xmm0, %eax
	movl	%eax, -24(%rbp)
	movss	-20(%rbp), %xmm0
	divss	-24(%rbp), %xmm0
	movq	-32(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_scale
	movq	%xmm0, %rax
	movq	%rax, -32(%rbp)
	movq	-56(%rbp), %rbx
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add
	movq	%xmm0, %rax
	movq	%rax, 8(%rbx)
	movq	-40(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_length
	movd	%xmm0, %eax
	movl	%eax, -24(%rbp)
	movss	-20(%rbp), %xmm0
	divss	-24(%rbp), %xmm0
	movq	-32(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_scale
	movq	%xmm0, %rax
	movq	%rax, -32(%rbp)
	movq	-56(%rbp), %rbx
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add
	movq	%xmm0, %rax
	movq	%rax, 16(%rbx)
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE61:
	.size	emb_arc_setRadius, .-emb_arc_setRadius
	.section	.rodata
.LC12:
	.string	"%f"
	.text
	.globl	emb_arc_arcLength
	.type	emb_arc_arcLength, @function
emb_arc_arcLength:
.LFB62:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	16(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movq	%rax, %xmm0
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	pxor	%xmm0, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE62:
	.size	emb_arc_arcLength, .-emb_arc_arcLength
	.globl	emb_arc_includedAngle
	.type	emb_arc_includedAngle, @function
emb_arc_includedAngle:
.LFB63:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	16(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movq	%rax, %xmm0
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	pxor	%xmm0, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE63:
	.size	emb_arc_includedAngle, .-emb_arc_includedAngle
	.globl	set_object_color
	.type	set_object_color, @function
set_object_color:
.LFB64:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movzwl	-16(%rbp), %edx
	movw	%dx, 36(%rax)
	movzbl	-14(%rbp), %edx
	movb	%dl, 38(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE64:
	.size	set_object_color, .-set_object_color
	.section	.rodata
.LC13:
	.string	"%p"
.LC14:
	.string	"%d"
	.text
	.globl	embGeometry_setColorRGB
	.type	embGeometry_setColorRGB, @function
embGeometry_setColorRGB:
.LFB65:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE65:
	.size	embGeometry_setColorRGB, .-embGeometry_setColorRGB
	.section	.rodata
.LC15:
	.string	"%p %d\n"
	.text
	.globl	embGeometry_setLineType
	.type	embGeometry_setLineType, @function
embGeometry_setLineType:
.LFB66:
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
	movq	%rax, %rsi
	leaq	.LC15(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE66:
	.size	embGeometry_setLineType, .-embGeometry_setLineType
	.section	.rodata
.LC16:
	.string	"%p %f\n"
	.text
	.globl	embGeometry_setLineWeight
	.type	embGeometry_setLineWeight, @function
embGeometry_setLineWeight:
.LFB67:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movss	%xmm0, -12(%rbp)
	pxor	%xmm1, %xmm1
	cvtss2sd	-12(%rbp), %xmm1
	movq	%xmm1, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %xmm0
	movq	%rax, %rsi
	leaq	.LC16(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE67:
	.size	embGeometry_setLineWeight, .-embGeometry_setLineWeight
	.section	.rodata
.LC17:
	.string	"%p %s\n"
	.text
	.globl	emb_base_rubber_point
	.type	emb_base_rubber_point, @function
emb_base_rubber_point:
.LFB68:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -4(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC17(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE68:
	.size	emb_base_rubber_point, .-emb_base_rubber_point
	.section	.rodata
.LC18:
	.string	""
	.text
	.globl	emb_base_rubber_text
	.type	emb_base_rubber_text, @function
emb_base_rubber_text:
.LFB69:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC17(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC18(%rip), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE69:
	.size	emb_base_rubber_text, .-emb_base_rubber_text
	.globl	emb_circle_main
	.type	emb_circle_main, @function
emb_circle_main:
.LFB70:
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
.LFE70:
	.size	emb_circle_main, .-emb_circle_main
	.globl	emb_circle_set_area
	.type	emb_circle_set_area, @function
emb_circle_set_area:
.LFB71:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movss	%xmm0, -12(%rbp)
	movss	embConstantPi(%rip), %xmm1
	movss	-12(%rbp), %xmm0
	divss	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movq	%xmm2, %rax
	movq	%rax, %xmm0
	call	sqrt@PLT
	cvtsd2ss	%xmm0, %xmm0
	movq	-8(%rbp), %rax
	movss	%xmm0, 8(%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE71:
	.size	emb_circle_set_area, .-emb_circle_set_area
	.globl	emb_ellipse_main
	.type	emb_ellipse_main, @function
emb_ellipse_main:
.LFB72:
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
.LFE72:
	.size	emb_ellipse_main, .-emb_ellipse_main
	.globl	embRect_bottomLeft
	.type	embRect_bottomLeft, @function
embRect_bottomLeft:
.LFB73:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movss	16(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movq	%rax, %xmm0
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	pxor	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -4(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE73:
	.size	embRect_bottomLeft, .-embRect_bottomLeft
	.globl	embRect_bottomRight
	.type	embRect_bottomRight, @function
embRect_bottomRight:
.LFB74:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movss	16(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movq	%rax, %xmm0
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	pxor	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -4(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE74:
	.size	embRect_bottomRight, .-embRect_bottomRight
	.globl	emb_circle
	.type	emb_circle, @function
emb_circle:
.LFB75:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movss	%xmm0, -76(%rbp)
	movss	%xmm1, -80(%rbp)
	movss	%xmm2, -84(%rbp)
	movss	-76(%rbp), %xmm0
	movss	%xmm0, -64(%rbp)
	movss	-80(%rbp), %xmm0
	movss	%xmm0, -60(%rbp)
	movss	-84(%rbp), %xmm0
	movss	%xmm0, -56(%rbp)
	movl	$2, -36(%rbp)
	movb	$0, -28(%rbp)
	movb	$0, -27(%rbp)
	movb	$0, -26(%rbp)
	movl	$0, -32(%rbp)
	movq	-72(%rbp), %rax
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
	movq	-72(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE75:
	.size	emb_circle, .-emb_circle
	.globl	getCircleCircleIntersections
	.type	getCircleCircleIntersections, @function
getCircleCircleIntersections:
.LFB76:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%xmm0, %rax
	movaps	%xmm1, %xmm4
	movdqa	%xmm2, %xmm1
	movaps	%xmm3, %xmm0
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%rax, -64(%rbp)
	movss	%xmm4, -56(%rbp)
	movq	%xmm1, -80(%rbp)
	movss	%xmm0, -72(%rbp)
	movq	-64(%rbp), %rdx
	movq	-80(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -36(%rbp)
	movq	-36(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_length
	movd	%xmm0, %eax
	movl	%eax, -4(%rbp)
	pxor	%xmm0, %xmm0
	ucomiss	-4(%rbp), %xmm0
	jp	.L233
	pxor	%xmm0, %xmm0
	ucomiss	-4(%rbp), %xmm0
	jne	.L233
	movl	$0, %eax
	jmp	.L242
.L233:
	movss	-56(%rbp), %xmm1
	movss	-72(%rbp), %xmm0
	addss	%xmm0, %xmm1
	movss	-4(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L247
	movl	$0, %eax
	jmp	.L242
.L247:
	movss	-56(%rbp), %xmm0
	movss	-72(%rbp), %xmm1
	subss	%xmm1, %xmm0
	comiss	-4(%rbp), %xmm0
	jbe	.L248
	movl	$0, %eax
	jmp	.L242
.L248:
	movss	-56(%rbp), %xmm1
	movss	-56(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	movss	-72(%rbp), %xmm2
	movss	-72(%rbp), %xmm1
	mulss	%xmm1, %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	-4(%rbp), %xmm0
	mulss	%xmm0, %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtss2sd	-4(%rbp), %xmm0
	addsd	%xmm0, %xmm0
	divsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsd2ss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-56(%rbp), %xmm1
	movss	-56(%rbp), %xmm0
	mulss	%xmm0, %xmm1
	movss	-8(%rbp), %xmm0
	mulss	%xmm0, %xmm0
	subss	%xmm0, %xmm1
	pxor	%xmm5, %xmm5
	cvtss2sd	%xmm1, %xmm5
	movq	%xmm5, %rax
	movq	%rax, %xmm0
	call	sqrt@PLT
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	movss	-64(%rbp), %xmm1
	movss	-36(%rbp), %xmm0
	mulss	-8(%rbp), %xmm0
	divss	-4(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -16(%rbp)
	movss	-60(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	mulss	-8(%rbp), %xmm0
	divss	-4(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -20(%rbp)
	movss	-56(%rbp), %xmm1
	movss	-72(%rbp), %xmm0
	addss	%xmm1, %xmm0
	ucomiss	-4(%rbp), %xmm0
	jp	.L240
	ucomiss	-4(%rbp), %xmm0
	jne	.L240
	movq	-88(%rbp), %rax
	movss	-16(%rbp), %xmm0
	movss	%xmm0, (%rax)
	movq	-88(%rbp), %rax
	movss	-20(%rbp), %xmm0
	movss	%xmm0, 4(%rax)
	movq	-96(%rbp), %rax
	movss	-16(%rbp), %xmm0
	movss	%xmm0, (%rax)
	movq	-96(%rbp), %rax
	movss	-20(%rbp), %xmm0
	movss	%xmm0, 4(%rax)
	movl	$1, %eax
	jmp	.L242
.L240:
	movss	-32(%rbp), %xmm0
	mulss	-12(%rbp), %xmm0
	divss	-4(%rbp), %xmm0
	movss	.LC8(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, -24(%rbp)
	movss	-36(%rbp), %xmm0
	mulss	-12(%rbp), %xmm0
	divss	-4(%rbp), %xmm0
	movss	%xmm0, -28(%rbp)
	movss	-16(%rbp), %xmm0
	addss	-24(%rbp), %xmm0
	movq	-88(%rbp), %rax
	movss	%xmm0, (%rax)
	movss	-20(%rbp), %xmm0
	addss	-28(%rbp), %xmm0
	movq	-88(%rbp), %rax
	movss	%xmm0, 4(%rax)
	movss	-16(%rbp), %xmm0
	subss	-24(%rbp), %xmm0
	movq	-96(%rbp), %rax
	movss	%xmm0, (%rax)
	movss	-20(%rbp), %xmm0
	subss	-28(%rbp), %xmm0
	movq	-96(%rbp), %rax
	movss	%xmm0, 4(%rax)
	movl	$1, %eax
.L242:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE76:
	.size	getCircleCircleIntersections, .-getCircleCircleIntersections
	.globl	getCircleTangentPoints
	.type	getCircleTangentPoints, @function
getCircleTangentPoints:
.LFB77:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%xmm0, %rax
	movaps	%xmm1, %xmm0
	movq	%xmm2, -40(%rbp)
	movq	%rdi, -48(%rbp)
	movq	%rsi, -56(%rbp)
	movq	%rax, -32(%rbp)
	movss	%xmm0, -24(%rbp)
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_distance
	movd	%xmm0, %eax
	movl	%eax, -4(%rbp)
	movss	-24(%rbp), %xmm0
	comiss	-4(%rbp), %xmm0
	jbe	.L258
	movl	$0, %eax
	jmp	.L255
.L258:
	movss	-28(%rbp), %xmm0
	ucomiss	-4(%rbp), %xmm0
	jp	.L253
	ucomiss	-4(%rbp), %xmm0
	jne	.L253
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-56(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, (%rax)
	movl	$1, %eax
	jmp	.L255
.L253:
	movq	-40(%rbp), %rax
	movq	%rax, -16(%rbp)
	movss	-4(%rbp), %xmm0
	mulss	%xmm0, %xmm0
	movss	-24(%rbp), %xmm2
	movss	-24(%rbp), %xmm1
	mulss	%xmm2, %xmm1
	subss	%xmm1, %xmm0
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm0, %xmm4
	movq	%xmm4, %rax
	movq	%rax, %xmm0
	call	sqrt@PLT
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	movq	-56(%rbp), %rdx
	movq	-48(%rbp), %rax
	movq	-16(%rbp), %r8
	movss	-8(%rbp), %xmm0
	movq	-32(%rbp), %rcx
	movss	-24(%rbp), %xmm1
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movq	%r8, %xmm2
	movaps	%xmm0, %xmm3
	movq	%rcx, %xmm0
	call	getCircleCircleIntersections
.L255:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE77:
	.size	getCircleTangentPoints, .-getCircleTangentPoints
	.globl	emb_ellipse_init
	.type	emb_ellipse_init, @function
emb_ellipse_init:
.LFB78:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -32(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -28(%rbp)
	movss	.LC2(%rip), %xmm0
	movss	%xmm0, -24(%rbp)
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, -20(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movl	-16(%rbp), %eax
	movl	%eax, 16(%rcx)
	movq	-40(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE78:
	.size	emb_ellipse_init, .-emb_ellipse_init
	.globl	emb_ellipse_diameterX
	.type	emb_ellipse_diameterX, @function
emb_ellipse_diameterX:
.LFB79:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	24(%rbp), %xmm0
	addss	%xmm0, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE79:
	.size	emb_ellipse_diameterX, .-emb_ellipse_diameterX
	.globl	emb_ellipse_diameterY
	.type	emb_ellipse_diameterY, @function
emb_ellipse_diameterY:
.LFB80:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	28(%rbp), %xmm0
	addss	%xmm0, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE80:
	.size	emb_ellipse_diameterY, .-emb_ellipse_diameterY
	.section	.rodata
.LC20:
	.string	"%f %f"
	.text
	.globl	emb_ellipse_setSize
	.type	emb_ellipse_setSize, @function
emb_ellipse_setSize:
.LFB81:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movss	%xmm0, -4(%rbp)
	movss	%xmm1, -8(%rbp)
	pxor	%xmm0, %xmm0
	cvtss2sd	-8(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	-4(%rbp), %xmm2
	movq	%xmm2, %rax
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC20(%rip), %rax
	movq	%rax, %rdi
	movl	$2, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE81:
	.size	emb_ellipse_setSize, .-emb_ellipse_setSize
	.globl	emb_round
	.type	emb_round, @function
emb_round:
.LFB82:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movss	%xmm0, -20(%rbp)
	pxor	%xmm2, %xmm2
	cvtss2sd	-20(%rbp), %xmm2
	movq	%xmm2, %rax
	movq	%rax, %xmm0
	call	floor@PLT
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -4(%rbp)
	movss	-20(%rbp), %xmm0
	subss	-4(%rbp), %xmm0
	movss	.LC21(%rip), %xmm1
	andps	%xmm1, %xmm0
	comiss	.LC0(%rip), %xmm0
	jbe	.L271
	pxor	%xmm3, %xmm3
	cvtss2sd	-20(%rbp), %xmm3
	movq	%xmm3, %rax
	movq	%rax, %xmm0
	call	ceil@PLT
	cvttsd2sil	%xmm0, %eax
	jmp	.L269
.L271:
	movss	-4(%rbp), %xmm0
	cvttss2sil	%xmm0, %eax
.L269:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE82:
	.size	emb_round, .-emb_round
	.globl	radians
	.type	radians, @function
radians:
.LFB83:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	%xmm0, -4(%rbp)
	movss	embConstantPi(%rip), %xmm0
	mulss	-4(%rbp), %xmm0
	movss	.LC22(%rip), %xmm1
	divss	%xmm1, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE83:
	.size	radians, .-radians
	.globl	degrees
	.type	degrees, @function
degrees:
.LFB84:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	%xmm0, -4(%rbp)
	pxor	%xmm1, %xmm1
	cvtss2sd	-4(%rbp), %xmm1
	movsd	.LC23(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movss	embConstantPi(%rip), %xmm1
	cvtss2sd	%xmm1, %xmm1
	divsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE84:
	.size	degrees, .-degrees
	.globl	emb_line_normalVector
	.type	emb_line_normalVector, @function
emb_line_normalVector:
.LFB85:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	16(%rbp), %rdx
	movq	24(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, -12(%rbp)
	movq	-12(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_normalize
	movq	%xmm0, %rax
	movq	%rax, -12(%rbp)
	movss	-12(%rbp), %xmm0
	movss	%xmm0, -4(%rbp)
	movss	-8(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	movss	-4(%rbp), %xmm0
	movss	.LC8(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	cmpl	$0, -20(%rbp)
	jne	.L277
	movss	-12(%rbp), %xmm0
	movss	.LC8(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, -12(%rbp)
	movss	-8(%rbp), %xmm0
	movss	.LC8(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
.L277:
	movq	-12(%rbp), %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE85:
	.size	emb_line_normalVector, .-emb_line_normalVector
	.globl	emb_line_toVector
	.type	emb_line_toVector, @function
emb_line_toVector:
.LFB86:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	16(%rbp), %rdx
	movq	24(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE86:
	.size	emb_line_toVector, .-emb_line_toVector
	.globl	emb_line_intersectionPoint
	.type	emb_line_intersectionPoint, @function
emb_line_intersectionPoint:
.LFB87:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$56, %rsp
	movq	%rdi, -56(%rbp)
	movq	-56(%rbp), %rax
	movl	$0, (%rax)
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	%rax, 16(%rcx)
	call	emb_line_toVector
	addq	$24, %rsp
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	40(%rbp), %rax
	movq	48(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	56(%rbp), %rax
	movq	%rax, 16(%rcx)
	call	emb_line_toVector
	addq	$24, %rsp
	movq	%xmm0, %rax
	movq	%rax, -32(%rbp)
	movq	-24(%rbp), %rdx
	movq	16(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_cross
	movd	%xmm0, %eax
	movl	%eax, -4(%rbp)
	movq	-32(%rbp), %rdx
	movq	40(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_cross
	movd	%xmm0, %eax
	movl	%eax, -8(%rbp)
	movss	.LC24(%rip), %xmm0
	movss	%xmm0, -12(%rbp)
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_cross
	movd	%xmm0, %eax
	movl	%eax, -16(%rbp)
	movss	-16(%rbp), %xmm0
	movss	.LC21(%rip), %xmm1
	andps	%xmm0, %xmm1
	movss	-12(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L287
	movq	-56(%rbp), %rax
	movl	$1, (%rax)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -40(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -36(%rbp)
	movq	-40(%rbp), %rax
	jmp	.L285
.L287:
	movss	-32(%rbp), %xmm0
	mulss	-4(%rbp), %xmm0
	movss	-24(%rbp), %xmm1
	mulss	-8(%rbp), %xmm1
	subss	%xmm1, %xmm0
	divss	-16(%rbp), %xmm0
	movss	%xmm0, -40(%rbp)
	movss	-28(%rbp), %xmm0
	mulss	-4(%rbp), %xmm0
	movss	-20(%rbp), %xmm1
	mulss	-8(%rbp), %xmm1
	subss	%xmm1, %xmm0
	divss	-16(%rbp), %xmm0
	movss	%xmm0, -36(%rbp)
	movq	-40(%rbp), %rax
.L285:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE87:
	.size	emb_line_intersectionPoint, .-emb_line_intersectionPoint
	.globl	emb_rect
	.type	emb_rect, @function
emb_rect:
.LFB88:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movss	%xmm0, -44(%rbp)
	movss	%xmm1, -48(%rbp)
	movss	%xmm2, -52(%rbp)
	movss	%xmm3, -56(%rbp)
	movss	-44(%rbp), %xmm0
	movss	%xmm0, -32(%rbp)
	movss	-48(%rbp), %xmm0
	movss	%xmm0, -28(%rbp)
	movss	-52(%rbp), %xmm0
	movss	%xmm0, -24(%rbp)
	movss	-56(%rbp), %xmm0
	movss	%xmm0, -20(%rbp)
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-16(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	-40(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE88:
	.size	emb_rect, .-emb_rect
	.globl	justify_options
	.section	.rodata
.LC25:
	.string	"Left"
.LC26:
	.string	"Center"
.LC27:
	.string	"Right"
.LC28:
	.string	"Aligned"
.LC29:
	.string	"Middle"
.LC30:
	.string	"Fit"
.LC31:
	.string	"Top Left"
.LC32:
	.string	"Top Center"
.LC33:
	.string	"Top Right"
.LC34:
	.string	"Middle Left"
.LC35:
	.string	"Middle Center"
.LC36:
	.string	"Middle Right"
.LC37:
	.string	"Bottom Left"
.LC38:
	.string	"Bottom Center"
.LC39:
	.string	"Bottom Right"
.LC40:
	.string	"__END__"
	.section	.data.rel.local,"aw"
	.align 32
	.type	justify_options, @object
	.size	justify_options, 128
justify_options:
	.quad	.LC25
	.quad	.LC26
	.quad	.LC27
	.quad	.LC28
	.quad	.LC29
	.quad	.LC30
	.quad	.LC31
	.quad	.LC32
	.quad	.LC33
	.quad	.LC34
	.quad	.LC35
	.quad	.LC36
	.quad	.LC37
	.quad	.LC38
	.quad	.LC39
	.quad	.LC40
	.section	.rodata
.LC41:
	.string	"%p, %s\n"
	.text
	.globl	textSingle_setJustify
	.type	textSingle_setJustify, @function
textSingle_setJustify:
.LFB89:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC41(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE89:
	.size	textSingle_setJustify, .-textSingle_setJustify
	.section	.rodata
	.align 8
.LC42:
	.string	"Failed to set attribute %d with object %d."
	.text
	.globl	emb_gget
	.type	emb_gget, @function
emb_gget:
.LFB90:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$5040, %rsp
	movq	%rdi, -4552(%rbp)
	movq	%rsi, -4560(%rbp)
	movl	%edx, -4564(%rbp)
	leaq	-4064(%rbp), %rax
	movl	.LC3(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	script_real@PLT
	movq	-4560(%rbp), %rax
	movl	28(%rax), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	attribute_get_table(%rip), %rax
	movl	(%rdx,%rax), %eax
	andl	-4564(%rbp), %eax
	testl	%eax, %eax
	jne	.L292
	movq	-4560(%rbp), %rax
	movl	28(%rax), %edx
	movl	-4564(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC42(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-4552(%rbp), %rax
	movq	%rax, %rdi
	leaq	-4064(%rbp), %rax
	movl	$56, %edx
	movq	%rax, %rsi
	movq	%rdx, %rcx
	rep movsq
	jmp	.L291
.L292:
	movq	-4560(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$134217728, %eax
	je	.L294
	cmpl	$134217728, %eax
	jg	.L318
	cmpl	$67108864, %eax
	je	.L296
	cmpl	$67108864, %eax
	jg	.L318
	cmpl	$33554432, %eax
	je	.L297
	cmpl	$33554432, %eax
	jg	.L318
	cmpl	$16777216, %eax
	je	.L298
	cmpl	$16777216, %eax
	jg	.L318
	cmpl	$8388608, %eax
	je	.L299
	cmpl	$8388608, %eax
	jg	.L318
	cmpl	$4194304, %eax
	je	.L319
	cmpl	$4194304, %eax
	jg	.L318
	cmpl	$2097152, %eax
	je	.L320
	cmpl	$2097152, %eax
	jg	.L318
	cmpl	$1048576, %eax
	je	.L302
	cmpl	$1048576, %eax
	jg	.L318
	cmpl	$524288, %eax
	je	.L321
	cmpl	$524288, %eax
	jg	.L318
	cmpl	$262144, %eax
	je	.L322
	cmpl	$262144, %eax
	jg	.L318
	cmpl	$131072, %eax
	je	.L323
	cmpl	$131072, %eax
	jg	.L318
	cmpl	$65536, %eax
	je	.L324
	cmpl	$65536, %eax
	jg	.L318
	cmpl	$32768, %eax
	je	.L325
	cmpl	$32768, %eax
	jg	.L318
	cmpl	$16384, %eax
	je	.L326
	cmpl	$16384, %eax
	jg	.L318
	cmpl	$8192, %eax
	je	.L327
	cmpl	$8192, %eax
	jg	.L318
	cmpl	$4096, %eax
	je	.L328
	cmpl	$4096, %eax
	jg	.L318
	cmpl	$1024, %eax
	je	.L329
	cmpl	$1024, %eax
	jg	.L318
	cmpl	$512, %eax
	je	.L330
	cmpl	$512, %eax
	jg	.L318
	cmpl	$128, %eax
	je	.L313
	cmpl	$256, %eax
	je	.L314
	jmp	.L318
.L297:
	leaq	-3616(%rbp), %rax
	movq	-4560(%rbp), %rcx
	movl	$1048576, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget
	movss	-3616(%rbp), %xmm0
	movss	%xmm0, -4(%rbp)
	leaq	-3168(%rbp), %rax
	movq	-4560(%rbp), %rcx
	movl	$128, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget
	movss	-3168(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-8(%rbp), %xmm0
	subss	-4(%rbp), %xmm0
	movss	.LC21(%rip), %xmm1
	andps	%xmm1, %xmm0
	movd	%xmm0, %edx
	leaq	-5024(%rbp), %rax
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	script_real@PLT
	leaq	-4064(%rbp), %rax
	leaq	-5024(%rbp), %rdx
	movl	$56, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	jmp	.L315
.L294:
	leaq	-2720(%rbp), %rax
	movq	-4560(%rbp), %rcx
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget
	movq	-2708(%rbp), %rax
	movq	%rax, -4072(%rbp)
	leaq	-2272(%rbp), %rax
	movq	-4560(%rbp), %rcx
	movl	$4, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget
	movq	-2260(%rbp), %rax
	movq	%rax, -4080(%rbp)
	movq	-4072(%rbp), %rdx
	movq	-4080(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract
	movq	%xmm0, %rax
	leaq	-5024(%rbp), %rdx
	movq	%rax, %xmm0
	movq	%rdx, %rdi
	call	script_vector@PLT
	leaq	-4064(%rbp), %rax
	leaq	-5024(%rbp), %rdx
	movl	$56, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	jmp	.L315
.L296:
	leaq	-1824(%rbp), %rax
	movq	-4560(%rbp), %rcx
	movl	$134217728, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget
	movq	-1812(%rbp), %rax
	movq	%rax, -4088(%rbp)
	movq	-4088(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_angle
	movd	%xmm0, %eax
	leaq	-5024(%rbp), %rdx
	movd	%eax, %xmm0
	movq	%rdx, %rdi
	call	script_real@PLT
	leaq	-4064(%rbp), %rax
	leaq	-5024(%rbp), %rdx
	movl	$56, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	jmp	.L315
.L299:
	leaq	-5024(%rbp), %rax
	movq	-4560(%rbp), %rcx
	movl	$134217728, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget
	leaq	-4064(%rbp), %rax
	leaq	-5024(%rbp), %rdx
	movl	$56, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	movq	-4052(%rbp), %rax
	movss	.LC0(%rip), %xmm1
	movq	%rax, %xmm0
	call	emb_vector_scale
	movq	%xmm0, %rax
	movq	%rax, -4052(%rbp)
	jmp	.L315
.L314:
	leaq	-5024(%rbp), %rax
	movq	-4560(%rbp), %rcx
	movl	$128, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget
	leaq	-4064(%rbp), %rax
	leaq	-5024(%rbp), %rdx
	movl	$56, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	movss	-4064(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	addsd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC21(%rip), %xmm1
	andps	%xmm1, %xmm0
	movss	%xmm0, -4064(%rbp)
	jmp	.L315
.L313:
	movq	-4560(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	jne	.L331
	leaq	-1376(%rbp), %rax
	movq	-4560(%rbp), %rcx
	movl	$16777216, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget
	movss	-1376(%rbp), %xmm0
	movss	%xmm0, -20(%rbp)
	leaq	-928(%rbp), %rax
	movq	-4560(%rbp), %rcx
	movl	$134217728, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget
	movq	-916(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_length
	movd	%xmm0, %eax
	movl	%eax, -24(%rbp)
	pxor	%xmm3, %xmm3
	cvtss2sd	-24(%rbp), %xmm3
	movsd	%xmm3, -5032(%rbp)
	pxor	%xmm0, %xmm0
	cvtss2sd	-20(%rbp), %xmm0
	movsd	.LC6(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	call	sin@PLT
	addsd	%xmm0, %xmm0
	movsd	-5032(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsd2ss	%xmm1, %xmm0
	movss	.LC21(%rip), %xmm1
	andps	%xmm1, %xmm0
	movd	%xmm0, %edx
	leaq	-5024(%rbp), %rax
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	script_real@PLT
	leaq	-4064(%rbp), %rax
	leaq	-5024(%rbp), %rdx
	movl	$56, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	jmp	.L331
.L298:
	leaq	-480(%rbp), %rax
	movq	-4560(%rbp), %rcx
	movl	$524288, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget
	movss	-480(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	pxor	%xmm4, %xmm4
	cvtss2sd	-12(%rbp), %xmm4
	movq	%xmm4, %rax
	movq	%rax, %xmm0
	call	atan@PLT
	movsd	.LC43(%rip), %xmm1
	mulsd	%xmm1, %xmm0
	pxor	%xmm5, %xmm5
	cvtsd2ss	%xmm0, %xmm5
	movd	%xmm5, %edx
	leaq	-5024(%rbp), %rax
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	script_real@PLT
	leaq	-4064(%rbp), %rax
	leaq	-5024(%rbp), %rdx
	movl	$56, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	jmp	.L315
.L302:
	movq	-4560(%rbp), %rax
	movq	%rax, %rdi
	call	emb_chord
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	leaq	-4544(%rbp), %rax
	movq	-4560(%rbp), %rcx
	movl	$524288, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_gget
	pxor	%xmm0, %xmm0
	cvtss2sd	-16(%rbp), %xmm0
	movsd	.LC6(%rip), %xmm2
	movapd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	movss	-4544(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	mulsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC21(%rip), %xmm1
	andps	%xmm1, %xmm0
	movd	%xmm0, %edx
	movq	-4552(%rbp), %rax
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	script_real@PLT
	jmp	.L291
.L318:
	nop
	jmp	.L315
.L319:
	nop
	jmp	.L315
.L320:
	nop
	jmp	.L315
.L321:
	nop
	jmp	.L315
.L322:
	nop
	jmp	.L315
.L323:
	nop
	jmp	.L315
.L324:
	nop
	jmp	.L315
.L325:
	nop
	jmp	.L315
.L326:
	nop
	jmp	.L315
.L327:
	nop
	jmp	.L315
.L328:
	nop
	jmp	.L315
.L329:
	nop
	jmp	.L315
.L330:
	nop
	jmp	.L315
.L331:
	nop
.L315:
	movq	-4552(%rbp), %rax
	movq	%rax, %rdi
	leaq	-4064(%rbp), %rax
	movl	$56, %edx
	movq	%rax, %rsi
	movq	%rdx, %rcx
	rep movsq
.L291:
	movq	-4552(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE90:
	.size	emb_gget, .-emb_gget
	.section	.rodata
	.align 8
.LC44:
	.string	"ERROR: Failed to set attribute %d with object %d."
.LC45:
	.string	"%d\n"
	.text
	.globl	emb_gset
	.type	emb_gset, @function
emb_gset:
.LFB91:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	attribute_set_table(%rip), %rax
	movl	(%rdx,%rax), %eax
	andl	-12(%rbp), %eax
	testl	%eax, %eax
	jne	.L333
	movq	-8(%rbp), %rax
	movl	28(%rax), %edx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC44(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %eax
	jmp	.L334
.L333:
	movzbl	456(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC45(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$2097152, %eax
	je	.L351
	cmpl	$2097152, %eax
	jg	.L352
	cmpl	$1048576, %eax
	je	.L337
	cmpl	$1048576, %eax
	jg	.L352
	cmpl	$524288, %eax
	je	.L338
	cmpl	$524288, %eax
	jg	.L352
	cmpl	$262144, %eax
	je	.L353
	cmpl	$262144, %eax
	jg	.L352
	cmpl	$131072, %eax
	je	.L354
	cmpl	$131072, %eax
	jg	.L352
	cmpl	$65536, %eax
	je	.L355
	cmpl	$65536, %eax
	jg	.L352
	cmpl	$32768, %eax
	je	.L356
	cmpl	$32768, %eax
	jg	.L352
	cmpl	$16384, %eax
	je	.L357
	cmpl	$16384, %eax
	jg	.L352
	cmpl	$8192, %eax
	je	.L358
	cmpl	$8192, %eax
	jg	.L352
	cmpl	$4096, %eax
	je	.L359
	cmpl	$4096, %eax
	jg	.L352
	cmpl	$512, %eax
	je	.L360
	cmpl	$1024, %eax
	je	.L361
	jmp	.L352
.L337:
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	je	.L362
	movl	$0, %eax
	jmp	.L334
.L338:
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$1, %eax
	je	.L363
	movl	$0, %eax
	jmp	.L334
.L351:
	nop
	jmp	.L348
.L352:
	nop
	jmp	.L348
.L353:
	nop
	jmp	.L348
.L354:
	nop
	jmp	.L348
.L355:
	nop
	jmp	.L348
.L356:
	nop
	jmp	.L348
.L357:
	nop
	jmp	.L348
.L358:
	nop
	jmp	.L348
.L359:
	nop
	jmp	.L348
.L360:
	nop
	jmp	.L348
.L361:
	nop
	jmp	.L348
.L362:
	nop
	jmp	.L348
.L363:
	nop
.L348:
	movl	$0, %eax
.L334:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE91:
	.size	emb_gset, .-emb_gset
	.section	.rodata
	.align 4
.LC0:
	.long	1056964608
	.align 8
.LC1:
	.long	0
	.long	1072693248
	.align 4
.LC2:
	.long	1065353216
	.align 4
.LC3:
	.long	0
	.align 8
.LC4:
	.long	0
	.long	1081507840
	.align 8
.LC5:
	.long	0
	.long	0
	.align 8
.LC6:
	.long	0
	.long	1073741824
	.align 16
.LC7:
	.long	-1
	.long	2147483647
	.long	0
	.long	0
	.align 16
.LC8:
	.long	-2147483648
	.long	0
	.long	0
	.long	0
	.align 4
.LC11:
	.long	869711765
	.align 4
.LC19:
	.long	1073741824
	.align 16
.LC21:
	.long	2147483647
	.long	0
	.long	0
	.long	0
	.align 4
.LC22:
	.long	1127481344
	.align 8
.LC23:
	.long	0
	.long	1080459264
	.align 4
.LC24:
	.long	786163455
	.align 8
.LC43:
	.long	0
	.long	1074790400
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
