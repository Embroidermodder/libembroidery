	.file	"designs.c"
	.text
	.globl	sgn
	.type	sgn, @function
sgn:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	%xmm0, -4(%rbp)
	movss	-4(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L9
	movl	$1, %eax
	jmp	.L4
.L9:
	pxor	%xmm0, %xmm0
	comiss	-4(%rbp), %xmm0
	jbe	.L10
	movl	$-1, %eax
	jmp	.L4
.L10:
	movl	$0, %eax
.L4:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	sgn, .-sgn
	.globl	theta
	.type	theta, @function
theta:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	%xmm0, -4(%rbp)
	pxor	%xmm0, %xmm0
	comiss	-4(%rbp), %xmm0
	jbe	.L16
	movl	$0, %eax
	jmp	.L14
.L16:
	movl	$1, %eax
.L14:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	theta, .-theta
	.globl	heart4
	.section	.rodata
.LC1:
	.string	"heart4"
.LC2:
	.string	"t"
	.align 8
.LC3:
	.string	"/t exch def(*(cos t)((sin(t)*sqrt(abs(cos(t))))/(sin(t)+7/5) - 2*sin(t) + 2))"
	.align 8
.LC4:
	.string	"/t exch def(*(sin t)((sin(t)*sqrt(abs(cos(t))))/(sin(t)+7/5) - 2*sin(t) + 2))"
	.section	.data.rel.local,"aw"
	.align 32
	.type	heart4, @object
	.size	heart4, 64
heart4:
	.quad	.LC1
	.long	0
	.long	1073741824
	.long	512
	.long	64
	.long	8192
	.long	1025758986
	.long	1025758986
	.zero	4
	.quad	.LC2
	.quad	.LC3
	.quad	.LC4
	.globl	heart5
	.section	.rodata
.LC5:
	.string	"heart5"
.LC6:
	.string	"16 t sin dup dup mul mul mul"
	.align 8
.LC7:
	.string	"13 t cos mul 5 2 t mul cos mul sub 2 3 t mul cos mul sub 4 t mul cos sub"
	.section	.data.rel.local
	.align 32
	.type	heart5, @object
	.size	heart5, 64
heart5:
	.quad	.LC5
	.long	0
	.long	1073741824
	.long	512
	.long	64
	.long	8192
	.long	1025758986
	.long	1025758986
	.zero	4
	.quad	.LC2
	.quad	.LC6
	.quad	.LC7
	.globl	designs
	.section	.rodata
.LC8:
	.string	"__END__"
	.section	.data.rel.local
	.align 32
	.type	designs, @object
	.size	designs, 64
designs:
	.quad	.LC8
	.zero	56
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
