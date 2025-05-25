	.file	"script.c"
	.text
	.local	focussed_pattern
	.comm	focussed_pattern,8,8
	.data
	.align 32
	.type	postscript_data_type, @object
	.size	postscript_data_type, 140
postscript_data_type:
	.string	"string"
	.zero	13
	.string	"array"
	.zero	14
	.string	"real"
	.zero	15
	.string	"int"
	.zero	16
	.string	"bool"
	.zero	15
	.string	"name"
	.zero	15
	.string	"dictionary"
	.zero	9
	.align 32
	.type	in_built_functions, @object
	.size	in_built_functions, 2160
in_built_functions:
	.string	"dup"
	.zero	16
	.string	"exch"
	.zero	15
	.string	"pop"
	.zero	16
	.string	"copy"
	.zero	15
	.string	"roll"
	.zero	15
	.string	"index"
	.zero	14
	.string	"mark"
	.zero	15
	.string	"clear"
	.zero	14
	.string	"count"
	.zero	14
	.string	"counttomark"
	.zero	8
	.string	"add"
	.zero	16
	.string	"sub"
	.zero	16
	.string	"mul"
	.zero	16
	.string	"div"
	.zero	16
	.string	"idiv"
	.zero	15
	.string	"mod"
	.zero	16
	.string	"abs"
	.zero	16
	.string	"neg"
	.zero	16
	.string	"ceiling"
	.zero	12
	.string	"floor"
	.zero	14
	.string	"round"
	.zero	14
	.string	"truncate"
	.zero	11
	.string	"sqrt"
	.zero	15
	.string	"exp"
	.zero	16
	.string	"ln"
	.zero	17
	.string	"log"
	.zero	16
	.string	"sin"
	.zero	16
	.string	"cos"
	.zero	16
	.string	"atan"
	.zero	15
	.string	"rand"
	.zero	15
	.string	"srand"
	.zero	14
	.string	"rrand"
	.zero	14
	.string	"get"
	.zero	16
	.string	"put"
	.zero	16
	.string	"copy"
	.zero	15
	.string	"length"
	.zero	13
	.string	"getinterval"
	.zero	8
	.string	"putinterval"
	.zero	8
	.string	"aload"
	.zero	14
	.string	"astore"
	.zero	13
	.string	"["
	.zero	18
	.string	"]"
	.zero	18
	.string	"setpacking"
	.zero	9
	.string	"currentpacking"
	.zero	5
	.string	"begin"
	.zero	14
	.string	"end"
	.zero	16
	.string	"def"
	.zero	16
	.string	"store"
	.zero	14
	.string	"load"
	.zero	15
	.string	"where"
	.zero	14
	.string	"countdictstack"
	.zero	5
	.string	"cleardictstack"
	.zero	5
	.string	"dictstack"
	.zero	10
	.string	"known"
	.zero	14
	.string	"maxlength"
	.zero	10
	.string	"undef"
	.zero	14
	.string	"<<"
	.zero	17
	.string	">>"
	.zero	17
	.string	"search"
	.zero	13
	.string	"anchorsearch"
	.zero	7
	.string	"token"
	.zero	14
	.string	"eq"
	.zero	17
	.string	"ne"
	.zero	17
	.string	"gt"
	.zero	17
	.string	"ge"
	.zero	17
	.string	"le"
	.zero	17
	.string	"lt"
	.zero	17
	.string	"and"
	.zero	16
	.string	"or"
	.zero	17
	.string	"xor"
	.zero	16
	.string	"true"
	.zero	15
	.string	"false"
	.zero	14
	.string	"not"
	.zero	16
	.string	"if"
	.zero	17
	.string	"ifelse"
	.zero	13
	.string	"exec"
	.zero	15
	.string	"for"
	.zero	16
	.string	"repeat"
	.zero	13
	.string	"loop"
	.zero	15
	.string	"forall"
	.zero	13
	.string	"exit"
	.zero	15
	.string	"countexecstack"
	.zero	5
	.string	"execstack"
	.zero	10
	.string	"stop"
	.zero	15
	.string	"type"
	.zero	15
	.string	"xcheck"
	.zero	13
	.string	"rcheck"
	.zero	13
	.string	"wcheck"
	.zero	13
	.string	"cvlit"
	.zero	14
	.string	"cvx"
	.zero	16
	.string	"readonly"
	.zero	11
	.string	"executeonly"
	.zero	8
	.string	"noaccess"
	.zero	11
	.string	"cvi"
	.zero	16
	.string	"cvr"
	.zero	16
	.string	"cvn"
	.zero	16
	.string	"cvs"
	.zero	16
	.string	"cvrs"
	.zero	15
	.string	"array"
	.zero	14
	.string	"packedarray"
	.zero	8
	.string	"dict"
	.zero	15
	.string	"string"
	.zero	13
	.string	"gstate"
	.zero	13
	.string	"save"
	.zero	15
	.string	"restore"
	.zero	12
	.string	"userdict"
	.zero	11
	.string	"gcheck"
	.zero	13
	.string	""
	.zero	19
	.text
	.globl	script_bool
	.type	script_bool, @function
script_bool:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$344, %rsp
	movq	%rdi, -456(%rbp)
	movl	%esi, %eax
	movb	%al, -460(%rbp)
	movb	$5, -8(%rbp)
	movzbl	-460(%rbp), %eax
	movb	%al, -440(%rbp)
	movq	-456(%rbp), %rax
	movq	%rax, %rdi
	leaq	-448(%rbp), %rax
	movl	$56, %edx
	movq	%rax, %rsi
	movq	%rdx, %rcx
	rep movsq
	movq	-456(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	script_bool, .-script_bool
	.globl	script_int
	.type	script_int, @function
script_int:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$344, %rsp
	movq	%rdi, -456(%rbp)
	movl	%esi, -460(%rbp)
	movb	$1, -8(%rbp)
	movl	-460(%rbp), %eax
	movl	%eax, -444(%rbp)
	movq	-456(%rbp), %rax
	movq	%rax, %rdi
	leaq	-448(%rbp), %rax
	movl	$56, %edx
	movq	%rax, %rsi
	movq	%rdx, %rcx
	rep movsq
	movq	-456(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	script_int, .-script_int
	.globl	script_real
	.type	script_real, @function
script_real:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$344, %rsp
	movq	%rdi, -456(%rbp)
	movss	%xmm0, -460(%rbp)
	movb	$2, -8(%rbp)
	movss	-460(%rbp), %xmm0
	movss	%xmm0, -448(%rbp)
	movq	-456(%rbp), %rax
	movq	%rax, %rdi
	leaq	-448(%rbp), %rax
	movl	$56, %edx
	movq	%rax, %rsi
	movq	%rdx, %rcx
	rep movsq
	movq	-456(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	script_real, .-script_real
	.globl	script_string
	.type	script_string, @function
script_string:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$464, %rsp
	movq	%rdi, -456(%rbp)
	movq	%rsi, -464(%rbp)
	movb	$4, -8(%rbp)
	movq	-464(%rbp), %rax
	leaq	-448(%rbp), %rdx
	leaq	20(%rdx), %rcx
	movl	$199, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	strncpy@PLT
	movq	-456(%rbp), %rax
	movq	%rax, %rdi
	leaq	-448(%rbp), %rax
	movl	$56, %edx
	movq	%rax, %rsi
	movq	%rdx, %rcx
	rep movsq
	movq	-456(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	script_string, .-script_string
	.globl	script_vector
	.type	script_vector, @function
script_vector:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$344, %rsp
	movq	%rdi, -456(%rbp)
	movq	%xmm0, -464(%rbp)
	movb	$7, -8(%rbp)
	movq	-464(%rbp), %rax
	movq	%rax, -436(%rbp)
	movq	-456(%rbp), %rax
	movq	%rax, %rdi
	leaq	-448(%rbp), %rax
	movl	$56, %edx
	movq	%rax, %rsi
	movq	%rdx, %rcx
	rep movsq
	movq	-456(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	script_vector, .-script_vector
	.section	.rodata
.LC0:
	.string	"%d "
.LC1:
	.string	"%s"
.LC2:
	.string	"unknown"
.LC3:
	.string	"exec index %d"
.LC4:
	.string	"literal"
.LC5:
	.string	" %s\n"
	.text
	.globl	analyse_stack
	.type	analyse_stack, @function
analyse_stack:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$152, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -152(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L12
.L17:
	movq	-152(%rbp), %rdx
	movl	-20(%rbp), %eax
	cltq
	imulq	$116, %rax, %rax
	addq	%rdx, %rax
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, -144(%rbp)
	movq	%rbx, -136(%rbp)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, -128(%rbp)
	movq	%rbx, -120(%rbp)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, -112(%rbp)
	movq	%rbx, -104(%rbp)
	movq	48(%rax), %rcx
	movq	56(%rax), %rbx
	movq	%rcx, -96(%rbp)
	movq	%rbx, -88(%rbp)
	movq	64(%rax), %rcx
	movq	72(%rax), %rbx
	movq	%rcx, -80(%rbp)
	movq	%rbx, -72(%rbp)
	movq	80(%rax), %rcx
	movq	88(%rax), %rbx
	movq	%rcx, -64(%rbp)
	movq	%rbx, -56(%rbp)
	movq	96(%rax), %rcx
	movq	104(%rax), %rbx
	movq	%rcx, -48(%rbp)
	movq	%rbx, -40(%rbp)
	movl	112(%rax), %eax
	movl	%eax, -32(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-144(%rbp), %eax
	testl	%eax, %eax
	js	.L13
	movl	-144(%rbp), %eax
	cmpl	$6, %eax
	jg	.L13
	movl	-144(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	leaq	postscript_data_type(%rip), %rdx
	addq	%rdx, %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L14
.L13:
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L14:
	movl	$32, %edi
	call	putchar@PLT
	movl	-140(%rbp), %eax
	testl	%eax, %eax
	je	.L15
	movl	-136(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L16
.L15:
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L16:
	leaq	-144(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -20(%rbp)
.L12:
	movq	-152(%rbp), %rax
	movl	116000(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L17
	nop
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	analyse_stack, .-analyse_stack
	.globl	stack_push
	.type	stack_push, @function
stack_push:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$1, -12(%rbp)
	movl	$0, -16(%rbp)
	movq	-48(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L19
	movl	$-1, %eax
	jmp	.L20
.L19:
	movq	-40(%rbp), %rax
	movl	116000(%rax), %eax
	cltq
	imulq	$116, %rax, %rax
	leaq	16(%rax), %rdx
	movq	-40(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	-48(%rbp), %rax
	movl	$200, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	strncpy@PLT
	movq	-40(%rbp), %rax
	movl	116000(%rax), %eax
	leal	1(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, 116000(%rax)
	movq	-40(%rbp), %rdx
	movq	-40(%rbp), %rax
	movl	116000(%rax), %eax
	cltq
	imulq	$116, %rax, %rax
	subq	$116, %rax
	addq	%rdx, %rax
	movq	%rax, -24(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L21
.L23:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	leaq	in_built_functions(%rip), %rdx
	addq	%rax, %rdx
	movq	-48(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L22
	movq	-24(%rbp), %rax
	movl	$5, (%rax)
	movq	-24(%rbp), %rax
	movl	$1, 4(%rax)
	movq	-24(%rbp), %rax
	movl	-8(%rbp), %edx
	movl	%edx, 8(%rax)
	movl	$5, %eax
	jmp	.L20
.L22:
	addl	$1, -8(%rbp)
.L21:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	leaq	in_built_functions(%rip), %rax
	movzbl	(%rdx,%rax), %eax
	testb	%al, %al
	jne	.L23
	movq	-24(%rbp), %rax
	movl	$0, 4(%rax)
	movq	-48(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$45, %al
	jne	.L24
	addl	$1, -4(%rbp)
.L24:
	movq	-48(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$34, %al
	jne	.L26
	movq	-24(%rbp), %rax
	movl	$0, (%rax)
	movl	$0, %eax
	jmp	.L20
.L31:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	jle	.L27
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$57, %al
	jle	.L28
.L27:
	movl	$0, -12(%rbp)
.L28:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$46, %al
	jne	.L29
	addl	$1, -16(%rbp)
.L29:
	addl	$1, -4(%rbp)
.L26:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L30
	cmpl	$199, -4(%rbp)
	jle	.L31
.L30:
	cmpl	$0, -12(%rbp)
	je	.L32
	cmpl	$0, -16(%rbp)
	jne	.L33
	movq	-24(%rbp), %rax
	movl	$3, (%rax)
	movl	$3, %eax
	jmp	.L20
.L33:
	cmpl	$1, -16(%rbp)
	jne	.L34
	movq	-24(%rbp), %rax
	movl	$2, (%rax)
	movl	$2, %eax
	jmp	.L20
.L34:
	movq	-40(%rbp), %rax
	movl	116000(%rax), %eax
	leal	-1(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, 116000(%rax)
	movl	$-2, %eax
	jmp	.L20
.L32:
	movq	-40(%rbp), %rax
	movl	116000(%rax), %eax
	leal	-1(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, 116000(%rax)
	movl	$-1, %eax
.L20:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	stack_push, .-stack_push
	.globl	stack_pop
	.type	stack_pop, @function
stack_pop:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$152, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -152(%rbp)
	movq	%rsi, -160(%rbp)
	movq	-160(%rbp), %rdx
	movq	-160(%rbp), %rax
	movl	116000(%rax), %eax
	cltq
	imulq	$116, %rax, %rax
	subq	$116, %rax
	leaq	(%rdx,%rax), %rcx
	leaq	-144(%rbp), %rax
	movl	$116, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	movq	-160(%rbp), %rax
	movl	116000(%rax), %eax
	leal	-1(%rax), %edx
	movq	-160(%rbp), %rax
	movl	%edx, 116000(%rax)
	movq	-152(%rbp), %rax
	movq	-144(%rbp), %rcx
	movq	-136(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-128(%rbp), %rcx
	movq	-120(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-112(%rbp), %rcx
	movq	-104(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 96(%rax)
	movq	%rbx, 104(%rax)
	movl	-32(%rbp), %edx
	movl	%edx, 112(%rax)
	movq	-152(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	stack_pop, .-stack_pop
	.section	.rodata
.LC6:
	.string	"Failed to queue token %s\n"
	.text
	.globl	queue_token
	.type	queue_token, @function
queue_token:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jns	.L38
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L39
.L38:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	process_stack_head
	movl	$1, %eax
.L39:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	queue_token, .-queue_token
	.globl	queue_token_list
	.type	queue_token_list, @function
queue_token_list:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$224, %rsp
	movq	%rdi, -216(%rbp)
	movq	%rsi, -224(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L41
.L44:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-224(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	jne	.L42
	movl	-8(%rbp), %eax
	cltq
	movb	$0, -208(%rbp,%rax)
	leaq	-208(%rbp), %rdx
	movq	-216(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	queue_token
	movl	$0, -8(%rbp)
	jmp	.L43
.L42:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-224(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movl	-8(%rbp), %eax
	cltq
	movb	%dl, -208(%rbp,%rax)
	addl	$1, -8(%rbp)
.L43:
	addl	$1, -4(%rbp)
.L41:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-224(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L44
	movq	-224(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L46
	movl	-8(%rbp), %eax
	cltq
	movb	$0, -208(%rbp,%rax)
	leaq	-208(%rbp), %rdx
	movq	-216(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	queue_token
.L46:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	queue_token_list, .-queue_token_list
	.globl	token_is_int
	.type	token_is_int, @function
token_is_int:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	20(%rbp), %eax
	testl	%eax, %eax
	je	.L48
	movl	$0, %eax
	jmp	.L49
.L48:
	movl	16(%rbp), %eax
	cmpl	$3, %eax
	sete	%al
	movzbl	%al, %eax
.L49:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	token_is_int, .-token_is_int
	.globl	string_equal
	.type	string_equal, @function
string_equal:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$200, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncmp@PLT
	testl	%eax, %eax
	sete	%al
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	string_equal, .-string_equal
	.globl	parse_floats
	.type	parse_floats, @function
parse_floats:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$256, %rsp
	movq	%rdi, -232(%rbp)
	movq	%rsi, -240(%rbp)
	movl	%edx, -244(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	movq	-232(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L53
.L59:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %edx
	movl	-16(%rbp), %eax
	cltq
	movb	%dl, -224(%rbp,%rax)
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$44, %al
	je	.L54
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	jne	.L55
.L54:
	movl	-16(%rbp), %eax
	cltq
	movb	$0, -224(%rbp,%rax)
	leaq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	atof@PLT
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-240(%rbp), %rax
	addq	%rdx, %rax
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, (%rax)
	movl	$0, -16(%rbp)
	addl	$1, -12(%rbp)
	movl	-244(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jg	.L58
	movl	$-1, %eax
	jmp	.L60
.L55:
	addl	$1, -16(%rbp)
.L58:
	addq	$1, -8(%rbp)
.L53:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L59
	movl	-16(%rbp), %eax
	cltq
	movb	$0, -224(%rbp,%rax)
	leaq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	atof@PLT
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-240(%rbp), %rax
	addq	%rdx, %rax
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, (%rax)
	movl	-12(%rbp), %eax
	addl	$1, %eax
.L60:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	parse_floats, .-parse_floats
	.globl	parse_vector
	.type	parse_vector, @function
parse_vector:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	leaq	-8(%rbp), %rcx
	movq	-24(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parse_floats
	cmpl	$2, %eax
	jne	.L62
	movl	$0, %eax
	jmp	.L64
.L62:
	movss	-8(%rbp), %xmm0
	movq	-32(%rbp), %rax
	movss	%xmm0, (%rax)
	movss	-4(%rbp), %xmm0
	movq	-32(%rbp), %rax
	movss	%xmm0, 4(%rax)
	movl	$1, %eax
.L64:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	parse_vector, .-parse_vector
	.globl	valid_rgb
	.type	valid_rgb, @function
valid_rgb:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	%xmm0, -4(%rbp)
	movss	%xmm1, -8(%rbp)
	movss	%xmm2, -12(%rbp)
	movss	-4(%rbp), %xmm0
	ucomiss	-4(%rbp), %xmm0
	jnp	.L66
	movl	$0, %eax
	jmp	.L67
.L66:
	movss	-8(%rbp), %xmm0
	ucomiss	-8(%rbp), %xmm0
	jnp	.L68
	movl	$0, %eax
	jmp	.L67
.L68:
	movss	-12(%rbp), %xmm0
	ucomiss	-12(%rbp), %xmm0
	jnp	.L69
	movl	$0, %eax
	jmp	.L67
.L69:
	pxor	%xmm0, %xmm0
	comiss	-4(%rbp), %xmm0
	ja	.L70
	movss	-4(%rbp), %xmm0
	comiss	.LC8(%rip), %xmm0
	jbe	.L79
.L70:
	movl	$0, %eax
	jmp	.L67
.L79:
	pxor	%xmm0, %xmm0
	comiss	-8(%rbp), %xmm0
	ja	.L73
	movss	-8(%rbp), %xmm0
	comiss	.LC8(%rip), %xmm0
	jbe	.L80
.L73:
	movl	$0, %eax
	jmp	.L67
.L80:
	pxor	%xmm0, %xmm0
	comiss	-12(%rbp), %xmm0
	ja	.L76
	movss	-12(%rbp), %xmm0
	comiss	.LC8(%rip), %xmm0
	jbe	.L81
.L76:
	movl	$0, %eax
	jmp	.L67
.L81:
	movl	$1, %eax
.L67:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	valid_rgb, .-valid_rgb
	.section	.rodata
.LC9:
	.string	"__END__"
	.align 8
.LC10:
	.string	"ERROR: Table is missing END_SYMBOL."
	.text
	.globl	table_length
	.type	table_length, @function
table_length:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L83
.L86:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movzbl	(%rax), %eax
	movl	$95, %edx
	cmpb	%dl, %al
	jne	.L84
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC9(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L89
.L84:
	addl	$1, -4(%rbp)
.L83:
	cmpl	$999, -4(%rbp)
	jle	.L86
	jmp	.L85
.L89:
	nop
.L85:
	cmpl	$1000, -4(%rbp)
	jne	.L87
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1000, %eax
	jmp	.L88
.L87:
	movl	-4(%rbp), %eax
.L88:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	table_length, .-table_length
	.section	.rodata
.LC11:
	.string	"r"
.LC12:
	.string	"ERROR: Failed to open \"%s\".\n"
	.text
	.globl	load_file
	.type	load_file, @function
load_file:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	leaq	.LC11(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L91
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L92
.L91:
	movq	-8(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -24(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rax
	movl	%eax, %edx
	movq	-24(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	read_n_bytes@PLT
	testb	%al, %al
	jne	.L93
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	$0, %eax
	jmp	.L92
.L93:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movq	-24(%rbp), %rax
.L92:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	load_file, .-load_file
	.globl	int32_underflow
	.type	int32_underflow, @function
int32_underflow:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	subq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
	movabsq	$-2147483649, %rax
	cmpq	%rax, -8(%rbp)
	jle	.L95
	movl	$2147483648, %eax
	cmpq	%rax, -8(%rbp)
	jl	.L96
.L95:
	movl	$1, %eax
	jmp	.L97
.L96:
	movl	$0, %eax
.L97:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	int32_underflow, .-int32_underflow
	.globl	int32_overflow
	.type	int32_overflow, @function
int32_overflow:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movabsq	$-2147483649, %rax
	cmpq	%rax, -8(%rbp)
	jle	.L99
	movl	$2147483648, %eax
	cmpq	%rax, -8(%rbp)
	jl	.L100
.L99:
	movl	$1, %eax
	jmp	.L101
.L100:
	movl	$0, %eax
.L101:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE24:
	.size	int32_overflow, .-int32_overflow
	.globl	round_to_multiple
	.type	round_to_multiple, @function
round_to_multiple:
.LFB25:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movb	%al, -20(%rbp)
	cmpl	$0, -28(%rbp)
	jne	.L103
	movl	-24(%rbp), %eax
	jmp	.L104
.L103:
	movl	-24(%rbp), %eax
	cltd
	idivl	-28(%rbp)
	movl	%edx, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jne	.L105
	movl	-24(%rbp), %eax
	jmp	.L104
.L105:
	cmpl	$0, -24(%rbp)
	jns	.L106
	cmpb	$0, -20(%rbp)
	je	.L106
	movl	-24(%rbp), %eax
	subl	-4(%rbp), %eax
	jmp	.L104
.L106:
	cmpb	$0, -20(%rbp)
	je	.L107
	movl	-24(%rbp), %edx
	movl	-28(%rbp), %eax
	addl	%edx, %eax
	subl	-4(%rbp), %eax
	jmp	.L104
.L107:
	cmpl	$0, -24(%rbp)
	jns	.L108
	movzbl	-20(%rbp), %eax
	xorl	$1, %eax
	testb	%al, %al
	je	.L108
	movl	-24(%rbp), %eax
	subl	-28(%rbp), %eax
	subl	-4(%rbp), %eax
	jmp	.L104
.L108:
	movl	-24(%rbp), %eax
	subl	-4(%rbp), %eax
.L104:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE25:
	.size	round_to_multiple, .-round_to_multiple
	.section	.rodata
.LC13:
	.string	"debug.log"
.LC14:
	.string	"a"
.LC15:
	.string	"Failed to write to debug.log."
.LC16:
	.string	"%Y-%m-%d %H:%M:%S"
.LC17:
	.string	"%s "
	.text
	.globl	debug_message
	.type	debug_message, @function
debug_message:
.LFB26:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$656, %rsp
	movq	%rdi, -648(%rbp)
	movq	%rsi, -168(%rbp)
	movq	%rdx, -160(%rbp)
	movq	%rcx, -152(%rbp)
	movq	%r8, -144(%rbp)
	movq	%r9, -136(%rbp)
	testb	%al, %al
	je	.L113
	movaps	%xmm0, -128(%rbp)
	movaps	%xmm1, -112(%rbp)
	movaps	%xmm2, -96(%rbp)
	movaps	%xmm3, -80(%rbp)
	movaps	%xmm4, -64(%rbp)
	movaps	%xmm5, -48(%rbp)
	movaps	%xmm6, -32(%rbp)
	movaps	%xmm7, -16(%rbp)
.L113:
	leaq	-608(%rbp), %rax
	leaq	.LC13(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-608(%rbp), %rax
	leaq	.LC14(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -184(%rbp)
	cmpq	$0, -184(%rbp)
	jne	.L111
	leaq	.LC15(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L109
.L111:
	movl	$0, %edi
	call	time@PLT
	movq	%rax, -616(%rbp)
	leaq	-616(%rbp), %rax
	movq	%rax, %rdi
	call	localtime@PLT
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rdx
	leaq	-400(%rbp), %rax
	movq	%rdx, %rcx
	leaq	.LC16(%rip), %rdx
	movl	$26, %esi
	movq	%rax, %rdi
	call	strftime@PLT
	leaq	-400(%rbp), %rdx
	movq	-184(%rbp), %rax
	leaq	.LC17(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movl	$8, -640(%rbp)
	movl	$48, -636(%rbp)
	leaq	16(%rbp), %rax
	movq	%rax, -632(%rbp)
	leaq	-176(%rbp), %rax
	movq	%rax, -624(%rbp)
	leaq	-640(%rbp), %rdx
	movq	-648(%rbp), %rcx
	movq	-184(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	vfprintf@PLT
	movq	-184(%rbp), %rax
	movq	%rax, %rsi
	movl	$10, %edi
	call	fputc@PLT
	movq	-184(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
.L109:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE26:
	.size	debug_message, .-debug_message
	.globl	valid_file_format
	.type	valid_file_format, @function
valid_file_format:
.LFB27:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_identify_format@PLT
	testl	%eax, %eax
	js	.L115
	movl	$1, %eax
	jmp	.L116
.L115:
	movl	$0, %eax
.L116:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE27:
	.size	valid_file_format, .-valid_file_format
	.globl	get_id
	.type	get_id, @function
get_id:
.LFB28:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	table_length
	movl	%eax, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L118
.L121:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	string_equal
	testb	%al, %al
	je	.L119
	movl	-4(%rbp), %eax
	jmp	.L120
.L119:
	addl	$1, -4(%rbp)
.L118:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L121
	movl	$-1, %eax
.L120:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE28:
	.size	get_id, .-get_id
	.type	emb_int_from_bytes, @function
emb_int_from_bytes:
.LFB29:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	sall	$8, %eax
	movl	%eax, %edx
	movl	-12(%rbp), %eax
	cltq
	leaq	1(%rax), %rcx
	movq	-8(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	addl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE29:
	.size	emb_int_from_bytes, .-emb_int_from_bytes
	.type	emb_real_from_bytes, @function
emb_real_from_bytes:
.LFB30:
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
	call	emb_int_from_bytes
	pxor	%xmm1, %xmm1
	cvtsi2sdl	%eax, %xmm1
	movsd	.LC18(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE30:
	.size	emb_real_from_bytes, .-emb_real_from_bytes
	.type	emb_vector_from_bytes, @function
emb_vector_from_bytes:
.LFB31:
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
	call	emb_real_from_bytes
	movd	%xmm0, %eax
	movl	%eax, -8(%rbp)
	movl	-28(%rbp), %eax
	leal	2(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_real_from_bytes
	movd	%xmm0, %eax
	movl	%eax, -4(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE31:
	.size	emb_vector_from_bytes, .-emb_vector_from_bytes
	.globl	get_int_tokens
	.type	get_int_tokens, @function
get_int_tokens:
.LFB32:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$184, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, -52(%rbp)
	movq	-40(%rbp), %rax
	movl	116000(%rax), %eax
	cmpl	%eax, -52(%rbp)
	jle	.L129
	movl	$0, %eax
	jmp	.L130
.L129:
	movl	$0, -20(%rbp)
	jmp	.L131
.L133:
	movq	-40(%rbp), %rax
	movl	116000(%rax), %edx
	movl	-20(%rbp), %eax
	addl	$2, %eax
	movl	%edx, %esi
	subl	%eax, %esi
	movl	-20(%rbp), %eax
	cltq
	imulq	$116, %rax, %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movq	-40(%rbp), %rcx
	movslq	%esi, %rdx
	imulq	$116, %rdx, %rdx
	addq	%rcx, %rdx
	movq	(%rdx), %rcx
	movq	8(%rdx), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16(%rdx), %rcx
	movq	24(%rdx), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32(%rdx), %rcx
	movq	40(%rdx), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48(%rdx), %rcx
	movq	56(%rdx), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	64(%rdx), %rcx
	movq	72(%rdx), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	80(%rdx), %rcx
	movq	88(%rdx), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	96(%rdx), %rcx
	movq	104(%rdx), %rbx
	movq	%rcx, 96(%rax)
	movq	%rbx, 104(%rax)
	movl	112(%rdx), %edx
	movl	%edx, 112(%rax)
	movl	-20(%rbp), %eax
	cltq
	imulq	$116, %rax, %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	subq	$120, %rsp
	movq	%rsp, %rdx
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, 16(%rdx)
	movq	%rbx, 24(%rdx)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, 32(%rdx)
	movq	%rbx, 40(%rdx)
	movq	48(%rax), %rcx
	movq	56(%rax), %rbx
	movq	%rcx, 48(%rdx)
	movq	%rbx, 56(%rdx)
	movq	64(%rax), %rcx
	movq	72(%rax), %rbx
	movq	%rcx, 64(%rdx)
	movq	%rbx, 72(%rdx)
	movq	80(%rax), %rcx
	movq	88(%rax), %rbx
	movq	%rcx, 80(%rdx)
	movq	%rbx, 88(%rdx)
	movq	96(%rax), %rcx
	movq	104(%rax), %rbx
	movq	%rcx, 96(%rdx)
	movq	%rbx, 104(%rdx)
	movl	112(%rax), %eax
	movl	%eax, 112(%rdx)
	call	token_is_int
	addq	$120, %rsp
	testl	%eax, %eax
	jne	.L132
	movl	$0, %eax
	jmp	.L130
.L132:
	addl	$1, -20(%rbp)
.L131:
	movl	-20(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	.L133
	leaq	-192(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_pop
	movl	-52(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	.L134
.L135:
	movl	-20(%rbp), %eax
	cltq
	imulq	$116, %rax, %rdx
	movq	-48(%rbp), %rax
	leaq	(%rdx,%rax), %rbx
	leaq	-192(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_pop
	movq	-192(%rbp), %rax
	movq	-184(%rbp), %rdx
	movq	%rax, (%rbx)
	movq	%rdx, 8(%rbx)
	movq	-176(%rbp), %rax
	movq	-168(%rbp), %rdx
	movq	%rax, 16(%rbx)
	movq	%rdx, 24(%rbx)
	movq	-160(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rax, 32(%rbx)
	movq	%rdx, 40(%rbx)
	movq	-144(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rax, 48(%rbx)
	movq	%rdx, 56(%rbx)
	movq	-128(%rbp), %rax
	movq	-120(%rbp), %rdx
	movq	%rax, 64(%rbx)
	movq	%rdx, 72(%rbx)
	movq	-112(%rbp), %rax
	movq	-104(%rbp), %rdx
	movq	%rax, 80(%rbx)
	movq	%rdx, 88(%rbx)
	movq	-96(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rax, 96(%rbx)
	movq	%rdx, 104(%rbx)
	movl	-80(%rbp), %eax
	movl	%eax, 112(%rbx)
	addl	$1, -20(%rbp)
.L134:
	cmpl	$0, -20(%rbp)
	jns	.L135
	movl	$1, %eax
.L130:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE32:
	.size	get_int_tokens, .-get_int_tokens
	.section	.rodata
.LC19:
	.string	"%d"
.LC20:
	.string	"%f"
	.align 8
.LC21:
	.string	"ERROR: Postscript built-in %d not indexed.\n"
	.text
	.globl	process_stack_head
	.type	process_stack_head, @function
process_stack_head:
.LFB33:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$1656, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -1528(%rbp)
	movq	-1528(%rbp), %rax
	movl	116000(%rax), %eax
	subl	$1, %eax
	movq	-1528(%rbp), %rdx
	cltq
	imulq	$116, %rax, %rax
	addq	%rdx, %rax
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, -352(%rbp)
	movq	%rbx, -344(%rbp)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, -336(%rbp)
	movq	%rbx, -328(%rbp)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, -320(%rbp)
	movq	%rbx, -312(%rbp)
	movq	48(%rax), %rcx
	movq	56(%rax), %rbx
	movq	%rcx, -304(%rbp)
	movq	%rbx, -296(%rbp)
	movq	64(%rax), %rcx
	movq	72(%rax), %rbx
	movq	%rcx, -288(%rbp)
	movq	%rbx, -280(%rbp)
	movq	80(%rax), %rcx
	movq	88(%rax), %rbx
	movq	%rcx, -272(%rbp)
	movq	%rbx, -264(%rbp)
	movq	96(%rax), %rcx
	movq	104(%rax), %rbx
	movq	%rcx, -256(%rbp)
	movq	%rbx, -248(%rbp)
	movl	112(%rax), %eax
	movl	%eax, -240(%rbp)
	movl	-348(%rbp), %eax
	testl	%eax, %eax
	jne	.L137
	movl	$1, %eax
	jmp	.L273
.L137:
	movl	-344(%rbp), %eax
	cmpl	$106, %eax
	ja	.L139
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L141(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L141(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L141:
	.long	.L246-.L141
	.long	.L274-.L141
	.long	.L244-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L236-.L141
	.long	.L235-.L141
	.long	.L234-.L141
	.long	.L233-.L141
	.long	.L232-.L141
	.long	.L231-.L141
	.long	.L230-.L141
	.long	.L229-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L224-.L141
	.long	.L223-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L220-.L141
	.long	.L219-.L141
	.long	.L218-.L141
	.long	.L217-.L141
	.long	.L216-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L185-.L141
	.long	.L184-.L141
	.long	.L183-.L141
	.long	.L182-.L141
	.long	.L181-.L141
	.long	.L180-.L141
	.long	.L179-.L141
	.long	.L178-.L141
	.long	.L177-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L274-.L141
	.long	.L139-.L141
	.long	.L274-.L141
	.text
.L246:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L275
	leaq	-1520(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	leaq	-1520(%rbp), %rax
	leaq	16(%rax), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L244:
	leaq	-1664(%rbp), %rax
	movq	-1528(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_pop
	jmp	.L248
.L236:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L276
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %ebx
	leaq	-1520(%rbp), %rax
	addq	$132, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	leal	(%rbx,%rax), %edx
	leaq	-224(%rbp), %rax
	leaq	.LC19(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L235:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L277
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %ebx
	leaq	-1520(%rbp), %rax
	addq	$132, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	subl	%eax, %ebx
	movl	%ebx, %edx
	leaq	-224(%rbp), %rax
	leaq	.LC19(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L234:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L278
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %ebx
	leaq	-1520(%rbp), %rax
	addq	$132, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	imull	%eax, %ebx
	movl	%ebx, %edx
	leaq	-224(%rbp), %rax
	leaq	.LC19(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L233:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L279
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atof@PLT
	movq	%xmm0, %rbx
	leaq	-1520(%rbp), %rax
	addq	$132, %rax
	movq	%rax, %rdi
	call	atof@PLT
	movq	%rbx, %xmm1
	divsd	%xmm0, %xmm1
	movq	%xmm1, %rdx
	leaq	-224(%rbp), %rax
	movq	%rdx, %xmm0
	leaq	.LC20(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$1, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L232:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L280
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %ebx
	leaq	-1520(%rbp), %rax
	addq	$132, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %esi
	movl	%ebx, %eax
	cltd
	idivl	%esi
	movl	%eax, %edx
	leaq	-224(%rbp), %rax
	leaq	.LC19(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L231:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L281
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %ebx
	leaq	-1520(%rbp), %rax
	addq	$132, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %esi
	movl	%ebx, %eax
	cltd
	idivl	%esi
	movl	%edx, %ecx
	movl	%ecx, %edx
	leaq	-224(%rbp), %rax
	leaq	.LC19(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L230:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L282
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %edx
	negl	%edx
	cmovs	%eax, %edx
	leaq	-224(%rbp), %rax
	leaq	.LC19(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L229:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L283
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	negl	%eax
	movl	%eax, %edx
	leaq	-224(%rbp), %rax
	leaq	.LC19(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L224:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L284
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atof@PLT
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	call	sqrt@PLT
	movq	%xmm0, %rax
	leaq	-224(%rbp), %rdx
	movq	%rax, %xmm0
	leaq	.LC20(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	movl	$1, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L223:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L285
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atof@PLT
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	call	exp@PLT
	movq	%xmm0, %rax
	leaq	-224(%rbp), %rdx
	movq	%rax, %xmm0
	leaq	.LC20(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	movl	$1, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L220:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L286
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atof@PLT
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	call	sin@PLT
	movq	%xmm0, %rax
	leaq	-224(%rbp), %rdx
	movq	%rax, %xmm0
	leaq	.LC20(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	movl	$1, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L219:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L287
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atof@PLT
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	call	cos@PLT
	movq	%xmm0, %rax
	leaq	-224(%rbp), %rdx
	movq	%rax, %xmm0
	leaq	.LC20(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	movl	$1, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L218:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L288
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atof@PLT
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	call	atan@PLT
	movq	%xmm0, %rax
	leaq	-224(%rbp), %rdx
	movq	%rax, %xmm0
	leaq	.LC20(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	movl	$1, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L217:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L289
	call	rand@PLT
	movl	%eax, %edx
	leaq	-224(%rbp), %rax
	leaq	.LC19(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rdx
	movq	-1528(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stack_push
	jmp	.L248
.L216:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	je	.L290
	leaq	-1520(%rbp), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %edi
	call	srand@PLT
	jmp	.L248
.L185:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	jmp	.L248
.L184:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	jmp	.L248
.L183:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	jmp	.L248
.L182:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	jmp	.L248
.L181:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	jmp	.L248
.L180:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	jmp	.L248
.L179:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	jmp	.L248
.L178:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	jmp	.L248
.L177:
	leaq	-1520(%rbp), %rcx
	movq	-1528(%rbp), %rax
	movl	$2, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_int_tokens
	testl	%eax, %eax
	jmp	.L248
.L139:
	movl	-344(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC21(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L248
.L274:
	nop
	jmp	.L248
.L275:
	nop
	jmp	.L248
.L276:
	nop
	jmp	.L248
.L277:
	nop
	jmp	.L248
.L278:
	nop
	jmp	.L248
.L279:
	nop
	jmp	.L248
.L280:
	nop
	jmp	.L248
.L281:
	nop
	jmp	.L248
.L282:
	nop
	jmp	.L248
.L283:
	nop
	jmp	.L248
.L284:
	nop
	jmp	.L248
.L285:
	nop
	jmp	.L248
.L286:
	nop
	jmp	.L248
.L287:
	nop
	jmp	.L248
.L288:
	nop
	jmp	.L248
.L289:
	nop
	jmp	.L248
.L290:
	nop
.L248:
	movl	$0, %eax
.L273:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE33:
	.size	process_stack_head, .-process_stack_head
	.globl	execute_postscript
	.type	execute_postscript, @function
execute_postscript:
.LFB34:
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
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	queue_token_list
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	analyse_stack
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE34:
	.size	execute_postscript, .-execute_postscript
	.section	.rodata
.LC22:
	.string	"embroider 1.0.0-alpha"
	.align 8
.LC23:
	.string	"    Copyright 2018-2024 The Embroidermodder Team."
	.align 8
.LC24:
	.string	"    Licensed under the terms of the zlib license."
.LC25:
	.string	""
	.align 8
.LC26:
	.string	"    https://www.libembroidery.org"
	.align 8
.LC27:
	.string	"                             WARNING"
	.align 8
.LC28:
	.string	"-----------------------------------------------------------------------"
	.align 8
.LC29:
	.string	"    embroider is under active development and is not yet"
	.align 8
.LC30:
	.string	"    ready for any serious use. Please only use in experimental contexts"
	.align 8
.LC31:
	.string	"    not as part of your general workflow."
	.align 8
.LC32:
	.string	"    This interpreter has only just been started, try using the"
	.align 8
.LC33:
	.string	"    --help flag for other features."
.LC34:
	.string	"emb> "
	.align 8
.LC35:
	.string	"Error: input line too long, please break up your command."
.LC36:
	.string	"quit"
	.text
	.globl	emb_repl
	.type	emb_repl, @function
emb_repl:
.LFB35:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$116224, %rsp
	movl	$0, -16(%rbp)
	leaq	.LC22(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC23(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC24(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC25(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC26(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC25(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC27(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC28(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC29(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC30(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC31(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC25(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC32(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC33(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC28(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC25(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1, -4(%rbp)
	jmp	.L293
.L298:
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	leaq	.LC34(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L294
.L296:
	movq	stdin(%rip), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -12(%rbp)
	cmpl	$31, -12(%rbp)
	jle	.L295
	cmpl	$127, -12(%rbp)
	jg	.L295
	movl	-12(%rbp), %eax
	movl	%eax, %edx
	movl	-8(%rbp), %eax
	cltq
	movb	%dl, -116224(%rbp,%rax)
	addl	$1, -8(%rbp)
	cmpl	$200, -8(%rbp)
	jne	.L294
	leaq	.LC35(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L294:
	cmpl	$-1, -12(%rbp)
	jne	.L296
.L295:
	movl	-8(%rbp), %eax
	cltq
	movb	$0, -116224(%rbp,%rax)
	leaq	-116224(%rbp), %rdx
	leaq	-116016(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	execute_postscript
	leaq	-116224(%rbp), %rax
	leaq	.LC36(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L293
	movl	$0, -4(%rbp)
.L293:
	cmpl	$0, -4(%rbp)
	jne	.L298
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE35:
	.size	emb_repl, .-emb_repl
	.section	.rodata
.LC37:
	.string	"state: %s\n"
	.align 8
.LC38:
	.string	"ERROR: there is no focussed pattern, so the arc command cannot be run."
	.align 8
.LC39:
	.string	"ERROR: there is no focussed pattern, so the circle command cannot be run."
.LC40:
	.string	"%f %f"
.LC41:
	.string	"Program command not defined."
	.text
	.globl	emb_processor
	.type	emb_processor, @function
emb_processor:
.LFB36:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movl	%edx, -84(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC37(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, -4(%rbp)
	jmp	.L301
.L309:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	cmpl	$1, %eax
	je	.L302
	cmpl	$2, %eax
	je	.L303
	jmp	.L310
.L302:
	movq	focussed_pattern(%rip), %rax
	testq	%rax, %rax
	jne	.L305
	leaq	.LC38(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L300
.L305:
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_vector_from_bytes
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movl	-4(%rbp), %eax
	leal	5(%rax), %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_vector_from_bytes
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	focussed_pattern(%rip), %rsi
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-32(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	%rsi, %rdi
	call	embPattern_addArc@PLT
	addq	$32, %rsp
	addl	$8, -4(%rbp)
	jmp	.L307
.L303:
	movq	focussed_pattern(%rip), %rax
	testq	%rax, %rax
	jne	.L308
	leaq	.LC39(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L300
.L308:
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_vector_from_bytes
	movq	%xmm0, %rax
	movq	%rax, -56(%rbp)
	movl	-4(%rbp), %eax
	leal	5(%rax), %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_real_from_bytes
	movd	%xmm0, %eax
	movl	%eax, -8(%rbp)
	pxor	%xmm0, %xmm0
	cvtss2sd	-8(%rbp), %xmm0
	movss	-56(%rbp), %xmm1
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm1, %xmm2
	movq	%xmm2, %rax
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC40(%rip), %rax
	movq	%rax, %rdi
	movl	$2, %eax
	call	printf@PLT
	addl	$6, -4(%rbp)
	jmp	.L307
.L310:
	leaq	.LC41(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	nop
.L307:
	addl	$1, -4(%rbp)
.L301:
	movl	-4(%rbp), %eax
	cmpl	-84(%rbp), %eax
	jl	.L309
.L300:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE36:
	.size	emb_processor, .-emb_processor
	.globl	emb_postscript_compiler
	.type	emb_postscript_compiler, @function
emb_postscript_compiler:
.LFB37:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE37:
	.size	emb_postscript_compiler, .-emb_postscript_compiler
	.globl	emb_compiler
	.type	emb_compiler, @function
emb_compiler:
.LFB38:
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
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	cmpl	$1, -28(%rbp)
	jne	.L316
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_postscript_compiler
	jmp	.L314
.L316:
	nop
.L314:
	movl	-8(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE38:
	.size	emb_compiler, .-emb_compiler
	.section	.rodata
.LC42:
	.string	"%p\n"
	.text
	.globl	emb_actuator
	.type	emb_actuator, @function
emb_actuator:
.LFB39:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, -52(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC42(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1000, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movl	$1000, %edi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rdx
	movl	-52(%rbp), %ecx
	movq	-48(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	emb_compiler
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %edx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_processor
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE39:
	.size	emb_actuator, .-emb_actuator
	.globl	emb_create_root
	.type	emb_create_root, @function
emb_create_root:
.LFB40:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$448, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movb	$7, 440(%rax)
	movq	-8(%rbp), %rax
	addq	$220, %rax
	movl	$1953460082, (%rax)
	movb	$0, 4(%rax)
	movq	-8(%rbp), %rax
	addq	$20, %rax
	movl	$1280070990, (%rax)
	movb	$0, 4(%rax)
	movl	$57344, %edi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 424(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 432(%rax)
	movq	-8(%rbp), %rax
	movl	$128, 436(%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE40:
	.size	emb_create_root, .-emb_create_root
	.globl	emb_create_leaf
	.type	emb_create_leaf, @function
emb_create_leaf:
.LFB41:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%rcx, -64(%rbp)
	movq	-40(%rbp), %rax
	movl	432(%rax), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	movq	-40(%rbp), %rax
	movl	436(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L321
	movq	-40(%rbp), %rax
	movl	436(%rax), %eax
	leal	128(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, 436(%rax)
	movq	-40(%rbp), %rax
	movl	436(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$6, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	movq	424(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc@PLT
	movq	-40(%rbp), %rdx
	movq	%rax, 424(%rdx)
.L321:
	movq	-40(%rbp), %rax
	movl	432(%rax), %eax
	leal	1(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, 432(%rax)
	movl	-44(%rbp), %eax
	movl	%eax, %edx
	movq	-40(%rbp), %rax
	movb	%dl, 440(%rax)
	movq	-40(%rbp), %rax
	movq	424(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$6, %rax
	addq	%rcx, %rax
	leaq	220(%rax), %rdx
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	strcpy@PLT
	movq	-40(%rbp), %rax
	movq	424(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$6, %rax
	addq	%rcx, %rax
	leaq	20(%rax), %rdx
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	strcpy@PLT
	cmpl	$5, -44(%rbp)
	je	.L322
	cmpl	$5, -44(%rbp)
	jg	.L323
	cmpl	$4, -44(%rbp)
	je	.L324
	cmpl	$4, -44(%rbp)
	jg	.L323
	cmpl	$1, -44(%rbp)
	je	.L325
	cmpl	$3, -44(%rbp)
	jne	.L323
.L325:
	movq	-40(%rbp), %rax
	movq	424(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$6, %rax
	leaq	(%rcx,%rax), %rbx
	movl	$57344, %edi
	call	malloc@PLT
	movq	%rax, 424(%rbx)
	movq	-40(%rbp), %rax
	movq	424(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$6, %rax
	addq	%rcx, %rax
	movl	$0, 432(%rax)
	movq	-40(%rbp), %rax
	movq	424(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$6, %rax
	addq	%rcx, %rax
	movl	$10, 436(%rax)
	jmp	.L326
.L324:
	movq	-40(%rbp), %rax
	movq	424(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$6, %rax
	leaq	(%rcx,%rax), %rbx
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, 4(%rbx)
	movq	-40(%rbp), %rax
	movq	424(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$6, %rax
	addq	%rcx, %rax
	movl	$0, 436(%rax)
	jmp	.L326
.L322:
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %esi
	movq	-40(%rbp), %rax
	movq	424(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$6, %rax
	addq	%rcx, %rax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%esi, %xmm0
	movss	%xmm0, (%rax)
	movq	-40(%rbp), %rax
	movq	424(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$6, %rax
	addq	%rcx, %rax
	movl	$0, 436(%rax)
	jmp	.L326
.L323:
	movq	-40(%rbp), %rax
	movq	424(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$6, %rax
	addq	%rcx, %rax
	movl	$0, 436(%rax)
	nop
.L326:
	movl	$1, %eax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE41:
	.size	emb_create_leaf, .-emb_create_leaf
	.section	.rodata
.LC43:
	.string	"Error: DATATYPE_NULL"
	.text
	.globl	emb_free_root
	.type	emb_free_root, @function
emb_free_root:
.LFB42:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movzbl	440(%rax), %eax
	movsbl	%al, %eax
	cmpl	$7, %eax
	je	.L329
	cmpl	$7, %eax
	jg	.L334
	cmpl	$3, %eax
	je	.L331
	cmpl	$3, %eax
	jg	.L334
	testl	%eax, %eax
	je	.L332
	cmpl	$1, %eax
	jne	.L334
.L331:
	movq	-8(%rbp), %rax
	movq	424(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	jmp	.L333
.L329:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	jmp	.L333
.L332:
	leaq	.LC43(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L333
.L334:
	nop
.L333:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE42:
	.size	emb_free_root, .-emb_free_root
	.section	.rodata
.LC44:
	.string	"%*c%s:\n"
.LC45:
	.string	"%*c%s: %s\n"
.LC46:
	.string	"%*c%s: %d\n"
.LC47:
	.string	"%*c%s: %f\n"
	.text
	.globl	emb_print_tree
	.type	emb_print_tree, @function
emb_print_tree:
.LFB43:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movq	-24(%rbp), %rax
	movzbl	440(%rax), %eax
	movsbl	%al, %eax
	cmpl	$5, %eax
	ja	.L345
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L338(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L338(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L338:
	.long	.L345-.L338
	.long	.L340-.L338
	.long	.L341-.L338
	.long	.L340-.L338
	.long	.L339-.L338
	.long	.L337-.L338
	.text
.L340:
	movq	-24(%rbp), %rax
	leaq	220(%rax), %rdx
	movl	-28(%rbp), %eax
	movq	%rdx, %rcx
	movl	$32, %edx
	movl	%eax, %esi
	leaq	.LC44(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, -4(%rbp)
	jmp	.L342
.L343:
	movl	-28(%rbp), %eax
	leal	1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_print_tree
	addl	$1, -4(%rbp)
.L342:
	movq	-24(%rbp), %rax
	movl	432(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L343
	jmp	.L344
.L341:
	movq	-24(%rbp), %rax
	leaq	20(%rax), %rcx
	movq	-24(%rbp), %rax
	leaq	220(%rax), %rdx
	movl	-28(%rbp), %eax
	movq	%rcx, %r8
	movq	%rdx, %rcx
	movl	$32, %edx
	movl	%eax, %esi
	leaq	.LC45(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L344
.L339:
	movq	-24(%rbp), %rax
	movl	4(%rax), %ecx
	movq	-24(%rbp), %rax
	leaq	220(%rax), %rdx
	movl	-28(%rbp), %eax
	movl	%ecx, %r8d
	movq	%rdx, %rcx
	movl	$32, %edx
	movl	%eax, %esi
	leaq	.LC46(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L344
.L337:
	movq	-24(%rbp), %rax
	movss	(%rax), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movq	%xmm1, %rdx
	movq	-24(%rbp), %rax
	leaq	220(%rax), %rcx
	movl	-28(%rbp), %eax
	movq	%rdx, %xmm0
	movl	$32, %edx
	movl	%eax, %esi
	leaq	.LC47(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	jmp	.L344
.L345:
	nop
.L344:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE43:
	.size	emb_print_tree, .-emb_print_tree
	.section	.rodata
.LC48:
	.string	"value"
.LC49:
	.string	"test"
	.text
	.globl	test_tree
	.type	test_tree, @function
test_tree:
.LFB44:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	call	emb_create_root
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	.LC48(%rip), %rdx
	movq	%rdx, %rcx
	leaq	.LC49(%rip), %rdx
	movl	$2, %esi
	movq	%rax, %rdi
	call	emb_create_leaf
	movq	-8(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_print_tree
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_free_root
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE44:
	.size	test_tree, .-test_tree
	.section	.rodata
	.align 4
.LC8:
	.long	1132396544
	.align 8
.LC18:
	.long	-1717986918
	.long	1069128089
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
