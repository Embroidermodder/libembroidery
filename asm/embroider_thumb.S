	.file	"embroider.c"
	.text
	.globl	help_msg
	.section	.rodata
	.align 8
.LC0:
	.string	"Usage: embroider [OPTIONS] fileToRead... "
.LC1:
	.string	""
.LC2:
	.string	"Conversion:"
	.align 8
.LC3:
	.string	"    -t, --to        Convert all files given to the format specified"
	.align 8
.LC4:
	.string	"                    by the arguments to the flag, for example:"
	.align 8
.LC5:
	.string	"                        $ embroider -t dst input.pes"
	.align 8
.LC6:
	.string	"                    would convert \"input.pes\" to \"input.dst\""
	.align 8
.LC7:
	.string	"                    in the same directory the program runs in."
	.align 8
.LC8:
	.string	"                    The accepted input formats are (TO BE DETERMINED)."
	.align 8
.LC9:
	.string	"                    The accepted output formats are (TO BE DETERMINED)."
.LC10:
	.string	"Analysis:"
	.align 8
.LC11:
	.string	"    -R, --report    Report various statistics on the loaded pattern."
.LC12:
	.string	"Output:"
	.align 8
.LC13:
	.string	"    -h, --help       Print this message."
	.align 8
.LC14:
	.string	"    -F, --formats     Print help on the formats that embroider can deal with."
	.align 8
.LC15:
	.string	"    -q, --quiet      Only print fatal errors."
	.align 8
.LC16:
	.string	"    -V, --verbose    Print everything that has reporting."
	.align 8
.LC17:
	.string	"    -v, --version    Print the version."
.LC18:
	.string	"Modify patterns:"
	.align 8
.LC19:
	.string	"    --combine        takes 3 arguments and combines the first"
	.align 8
.LC20:
	.string	"                     two by placing them atop each other and"
	.align 8
.LC21:
	.string	"                     outputs to the third"
	.align 8
.LC22:
	.string	"                        $ embroider --combine a.dst b.dst output.dst"
.LC23:
	.string	"Graphics:"
	.align 8
.LC24:
	.string	"    -c, --circle     Add a circle defined by the arguments given to the current pattern."
	.align 8
.LC25:
	.string	"    -e, --ellipse    Add a circle defined by the arguments given to the current pattern."
	.align 8
.LC26:
	.string	"    -l, --line       Add a line defined by the arguments given to the current pattern."
	.align 8
.LC27:
	.string	"    -P, --polyline   Add a polyline."
	.align 8
.LC28:
	.string	"    -p, --polygon    Add a polygon."
	.align 8
.LC29:
	.string	"    -r, --render     Create an image in PNG format of what the embroidery should look like."
	.align 8
.LC30:
	.string	"    -s, --satin      Fill the current geometry with satin stitches according"
	.align 8
.LC31:
	.string	"                     to the defined algorithm."
	.align 8
.LC32:
	.string	"    -S, --stitch     Add a stitch defined by the arguments given to the current pattern."
.LC33:
	.string	"Quality Assurance:"
	.align 8
.LC34:
	.string	"        --test N           Run the test number N."
	.align 8
.LC35:
	.string	"        --convert-test A N M Test conversion of test file A from format N to format M."
	.align 8
.LC36:
	.string	"        --full-test-suite  Run all tests, even those we expect to fail."
.LC37:
	.string	"EOF"
	.section	.data.rel.local,"aw"
	.align 32
	.type	help_msg, @object
	.size	help_msg, 352
help_msg:
	.quad	.LC0
	.quad	.LC1
	.quad	.LC2
	.quad	.LC3
	.quad	.LC4
	.quad	.LC5
	.quad	.LC6
	.quad	.LC7
	.quad	.LC1
	.quad	.LC8
	.quad	.LC9
	.quad	.LC1
	.quad	.LC10
	.quad	.LC11
	.quad	.LC1
	.quad	.LC12
	.quad	.LC13
	.quad	.LC14
	.quad	.LC15
	.quad	.LC16
	.quad	.LC17
	.quad	.LC1
	.quad	.LC18
	.quad	.LC19
	.quad	.LC20
	.quad	.LC21
	.quad	.LC22
	.quad	.LC1
	.quad	.LC23
	.quad	.LC24
	.quad	.LC25
	.quad	.LC26
	.quad	.LC27
	.quad	.LC28
	.quad	.LC29
	.quad	.LC30
	.quad	.LC31
	.quad	.LC32
	.quad	.LC1
	.quad	.LC33
	.quad	.LC34
	.quad	.LC35
	.quad	.LC36
	.quad	.LC37
	.globl	welcome_message
	.section	.rodata
	.align 8
.LC38:
	.string	"EMBROIDER\n    A command line program for machine embroidery.\n    Copyright 2018-2024 The Embroidermodder Team\n    Licensed under the terms of the zlib license.\n\n    https://github.com/Embroidermodder/libembroidery\n    https://www.libembroidery.org\n"
	.section	.data.rel.local
	.align 8
	.type	welcome_message, @object
	.size	welcome_message, 8
welcome_message:
	.quad	.LC38
	.globl	flag_list
	.section	.rodata
	.align 32
	.type	flag_list, @object
	.size	flag_list, 8200
flag_list:
	.string	"--to"
	.zero	195
	.string	"-t"
	.zero	197
	.string	"--help"
	.zero	193
	.string	"-h"
	.zero	197
	.string	"--formats"
	.zero	190
	.string	"-F"
	.zero	197
	.string	"--quiet"
	.zero	192
	.string	"-q"
	.zero	197
	.string	"--verbose"
	.zero	190
	.string	"-V"
	.zero	197
	.string	"--version"
	.zero	190
	.string	"-v"
	.zero	197
	.string	"--circle"
	.zero	191
	.string	"-c"
	.zero	197
	.string	"--ellipse"
	.zero	190
	.string	"-e"
	.zero	197
	.string	"--line"
	.zero	193
	.string	"-l"
	.zero	197
	.string	"--polyline"
	.zero	189
	.string	"-P"
	.zero	197
	.string	"--polygon"
	.zero	190
	.string	"-p"
	.zero	197
	.string	"--render"
	.zero	191
	.string	"-r"
	.zero	197
	.string	"--satin"
	.zero	192
	.string	"-s"
	.zero	197
	.string	"--stitch"
	.zero	191
	.string	"-S"
	.zero	197
	.string	"--test"
	.zero	193
	.string	"--full-test-suite"
	.zero	182
	.string	"--convert-test"
	.zero	185
	.string	"--hilbert-curve"
	.zero	184
	.string	"--sierpinski-triangle"
	.zero	178
	.string	"--fill"
	.zero	193
	.string	"-f"
	.zero	197
	.string	"--simulate"
	.zero	189
	.string	"--combine"
	.zero	190
	.string	"--cross-stitch"
	.zero	185
	.string	"--ps"
	.zero	195
	.string	"--render"
	.zero	191
	.string	"-R"
	.zero	197
	.text
	.globl	usage
	.type	usage, @function
usage:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	welcome_message(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	help_msg(%rip), %rax
	movq	(%rdx,%rax), %rax
	movq	%rax, %rdi
	call	puts@PLT
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	help_msg(%rip), %rax
	movq	(%rdx,%rax), %rax
	leaq	.LC37(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L3
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	usage, .-usage
	.section	.rodata
	.align 8
.LC39:
	.string	"Not enough arguments supplied to circle command: 3 required."
.LC40:
	.string	"%s %s %s circle"
.LC41:
	.string	"This flag is not implemented."
.LC42:
	.string	"%d\n"
	.align 8
.LC43:
	.string	"Defaulting to the output name 'output.png'."
.LC44:
	.string	"output.png"
	.align 8
.LC45:
	.string	"Defaulting to the output name 'output.avi'."
.LC46:
	.string	"output.avi"
	.align 8
.LC47:
	.string	"--combine takes 3 arguments and you have supplied <3."
	.align 8
.LC48:
	.string	"Failed test %d with error %d.\n"
	.align 8
.LC49:
	.string	"Please enter an output format for your file, see --help."
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$116736, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movl	%edi, -116308(%rbp)
	movq	%rsi, -116320(%rbp)
	call	emb_pattern_create@PLT
	movq	%rax, -32(%rbp)
	cmpl	$1, -116308(%rbp)
	jne	.L5
	call	usage
	movl	$0, %eax
	jmp	.L6
.L5:
	movl	-116308(%rbp), %eax
	imull	$100, %eax, %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -56(%rbp)
	movl	-116308(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -40(%rbp)
	movl	$1, -20(%rbp)
	jmp	.L7
.L57:
	movl	$-1, -36(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L8
.L11:
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rcx
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	leaq	flag_list(%rip), %rdx
	addq	%rdx, %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L9
	movl	-24(%rbp), %eax
	movl	%eax, -36(%rbp)
	jmp	.L10
.L9:
	addl	$1, -24(%rbp)
.L8:
	cmpl	$40, -24(%rbp)
	jle	.L11
.L10:
	cmpl	$40, -36(%rbp)
	ja	.L12
	movl	-36(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L14(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L14(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L14:
	.long	.L38-.L14
	.long	.L38-.L14
	.long	.L37-.L14
	.long	.L37-.L14
	.long	.L36-.L14
	.long	.L36-.L14
	.long	.L35-.L14
	.long	.L35-.L14
	.long	.L34-.L14
	.long	.L34-.L14
	.long	.L33-.L14
	.long	.L33-.L14
	.long	.L32-.L14
	.long	.L32-.L14
	.long	.L31-.L14
	.long	.L31-.L14
	.long	.L30-.L14
	.long	.L30-.L14
	.long	.L29-.L14
	.long	.L29-.L14
	.long	.L28-.L14
	.long	.L28-.L14
	.long	.L27-.L14
	.long	.L27-.L14
	.long	.L26-.L14
	.long	.L26-.L14
	.long	.L25-.L14
	.long	.L25-.L14
	.long	.L24-.L14
	.long	.L23-.L14
	.long	.L22-.L14
	.long	.L21-.L14
	.long	.L20-.L14
	.long	.L19-.L14
	.long	.L12-.L14
	.long	.L18-.L14
	.long	.L17-.L14
	.long	.L16-.L14
	.long	.L15-.L14
	.long	.L13-.L14
	.long	.L13-.L14
	.text
.L38:
	movl	-20(%rbp), %edx
	movl	-116308(%rbp), %ecx
	movq	-116320(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	to_flag@PLT
	jmp	.L39
.L37:
	call	usage
	jmp	.L39
.L36:
	call	formats@PLT
	jmp	.L39
.L35:
	movl	$-1, emb_verbose(%rip)
	jmp	.L39
.L34:
	movl	$1, emb_verbose(%rip)
	jmp	.L39
.L32:
	movl	-20(%rbp), %eax
	addl	$3, %eax
	cmpl	%eax, -116308(%rbp)
	jg	.L40
	leaq	.LC39(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	-116308(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	.L39
.L40:
	movl	-20(%rbp), %eax
	cltq
	addq	$3, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rsi
	movl	-20(%rbp), %eax
	cltq
	addq	$2, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rcx
	movl	-20(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	leaq	-116096(%rbp), %rax
	movq	%rsi, %r8
	leaq	.LC40(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-116096(%rbp), %rcx
	movq	-32(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_actuator@PLT
	jmp	.L39
.L31:
	leaq	.LC41(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L39
.L30:
	leaq	.LC41(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L39
.L29:
	leaq	.LC41(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L39
.L28:
	leaq	.LC41(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L39
.L26:
	leaq	.LC41(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L39
.L25:
	leaq	.LC41(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L39
.L20:
	leaq	.LC41(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L39
.L19:
	movl	-20(%rbp), %eax
	addl	$3, %eax
	cmpl	%eax, -116308(%rbp)
	jle	.L60
	addl	$1, -20(%rbp)
	leaq	-116752(%rbp), %rax
	movl	$2000, %edx
	movl	$2000, %esi
	movq	%rax, %rdi
	call	embImage_create@PLT
	leaq	-116096(%rbp), %rax
	leaq	-116752(%rbp), %rdx
	movl	$54, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	leaq	-116096(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	embImage_read@PLT
	addl	$1, -20(%rbp)
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %edx
	leaq	-116096(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_horizontal_fill@PLT
	leaq	-116096(%rbp), %rax
	movq	%rax, %rdi
	call	embImage_free@PLT
	addl	$1, -20(%rbp)
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_writeAuto@PLT
	jmp	.L60
.L27:
	movl	-20(%rbp), %eax
	addl	$2, %eax
	cmpl	%eax, -116308(%rbp)
	jle	.L43
	movl	-20(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_readAuto@PLT
	movq	-32(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, %esi
	leaq	.LC42(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-20(%rbp), %eax
	cltq
	addq	$2, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_render@PLT
	addl	$2, -20(%rbp)
	jmp	.L39
.L43:
	leaq	.LC43(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-32(%rbp), %rax
	leaq	.LC44(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_render@PLT
	jmp	.L39
.L18:
	movl	-20(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, -116308(%rbp)
	jle	.L44
	addl	$1, -20(%rbp)
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movzbl	(%rax), %eax
	cmpb	$45, %al
	jne	.L45
	leaq	.LC45(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-32(%rbp), %rax
	leaq	.LC46(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_simulate@PLT
	subl	$1, -20(%rbp)
	jmp	.L39
.L45:
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_simulate@PLT
	jmp	.L39
.L44:
	leaq	.LC45(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-32(%rbp), %rax
	leaq	.LC46(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_simulate@PLT
	jmp	.L39
.L17:
	movl	-20(%rbp), %eax
	addl	$3, %eax
	cmpl	%eax, -116308(%rbp)
	jle	.L47
	call	emb_pattern_create@PLT
	movq	%rax, -64(%rbp)
	call	emb_pattern_create@PLT
	movq	%rax, -72(%rbp)
	movl	-20(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_readAuto@PLT
	movl	-20(%rbp), %eax
	cltq
	addq	$2, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_readAuto@PLT
	movq	-72(%rbp), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_combine@PLT
	movq	%rax, -80(%rbp)
	movl	-20(%rbp), %eax
	cltq
	addq	$3, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-80(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_writeAuto@PLT
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free@PLT
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free@PLT
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free@PLT
	jmp	.L39
.L47:
	leaq	.LC47(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L39
.L33:
	movq	version_string(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L39
.L21:
	call	emb_pattern_create@PLT
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movl	$3, %esi
	movq	%rax, %rdi
	call	hilbert_curve@PLT
	jmp	.L39
.L24:
	movl	-20(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, -116308(%rbp)
	jle	.L61
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free@PLT
	movl	-20(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %edi
	call	testMain@PLT
	jmp	.L6
.L23:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free@PLT
	movl	$0, -44(%rbp)
	jmp	.L50
.L52:
	movl	-44(%rbp), %eax
	movl	%eax, %edi
	call	testMain@PLT
	movl	%eax, -84(%rbp)
	cmpl	$0, -84(%rbp)
	je	.L51
	movl	-84(%rbp), %edx
	movl	-44(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC48(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %eax
	jmp	.L6
.L51:
	addl	$1, -44(%rbp)
.L50:
	cmpl	$9, -44(%rbp)
	jle	.L52
	movl	$0, %eax
	jmp	.L6
.L22:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free@PLT
	movl	-20(%rbp), %eax
	addl	$3, %eax
	cmpl	%eax, -116308(%rbp)
	jle	.L53
	movl	-20(%rbp), %eax
	cltq
	addq	$3, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %r12d
	movl	-20(%rbp), %eax
	cltq
	addq	$2, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %ebx
	movl	-20(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%r12d, %edx
	movl	%ebx, %esi
	movl	%eax, %edi
	call	test_convert@PLT
	jmp	.L6
.L53:
	movl	$0, %eax
	jmp	.L6
.L16:
	movl	-20(%rbp), %eax
	addl	$3, %eax
	cmpl	%eax, -116308(%rbp)
	jle	.L62
	leaq	-116752(%rbp), %rax
	movl	$2000, %edx
	movl	$2000, %esi
	movq	%rax, %rdi
	call	embImage_create@PLT
	leaq	-116096(%rbp), %rax
	leaq	-116752(%rbp), %rdx
	movl	$54, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	leaq	-116096(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	embImage_read@PLT
	movl	-20(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, %edx
	leaq	-116096(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_crossstitch@PLT
	leaq	-116096(%rbp), %rax
	movq	%rax, %rdi
	call	embImage_free@PLT
	movl	-20(%rbp), %eax
	cltq
	addq	$2, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_writeAuto@PLT
	addl	$3, -20(%rbp)
	jmp	.L62
.L15:
	movl	$0, -96(%rbp)
	movb	$0, -116304(%rbp)
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -48(%rbp)
	jmp	.L55
.L56:
	movl	-48(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	leaq	-116304(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
	leaq	-116304(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	leaq	-116304(%rbp), %rax
	addq	%rdx, %rax
	movw	$32, (%rax)
	addl	$1, -48(%rbp)
.L55:
	movl	-48(%rbp), %eax
	cmpl	-116308(%rbp), %eax
	jl	.L56
	leaq	-116304(%rbp), %rdx
	leaq	-116096(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	execute_postscript@PLT
	jmp	.L39
.L13:
	movl	-20(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	-116320(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_readAuto@PLT
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_details@PLT
	addl	$1, -20(%rbp)
	jmp	.L39
.L12:
	subl	$1, -40(%rbp)
	jmp	.L39
.L60:
	nop
	jmp	.L39
.L61:
	nop
	jmp	.L39
.L62:
	nop
.L39:
	addl	$1, -20(%rbp)
.L7:
	movl	-20(%rbp), %eax
	cmpl	-116308(%rbp), %eax
	jl	.L57
	cmpl	$0, -40(%rbp)
	jne	.L58
	cmpl	$3, -116308(%rbp)
	jne	.L58
	movq	-116320(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rdx
	movq	-116320(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	convert@PLT
	jmp	.L59
.L58:
	cmpl	$0, -40(%rbp)
	jne	.L59
	leaq	.LC49(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L59:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free@PLT
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movl	$0, %eax
.L6:
	addq	$116736, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
