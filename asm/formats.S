	.file	"formats.c"
	.text
	.globl	shvThreadCount
	.section	.rodata
	.align 4
	.type	shvThreadCount, @object
	.size	shvThreadCount, 4
shvThreadCount:
	.long	42
	.globl	pecThreadCount
	.align 4
	.type	pecThreadCount, @object
	.size	pecThreadCount, 4
pecThreadCount:
	.long	65
	.align 8
.LC0:
	.string	"ERROR: emb_fname_extension(), fileName argument is null.\n"
	.align 8
.LC1:
	.string	"ERROR: emb_fname_extension(), fileName argument is an empty string.\n"
	.align 8
.LC2:
	.string	"ERROR: emb_fname_extension(), filename has no stub.\n"
	.text
	.globl	emb_fname_extension
	.type	emb_fname_extension, @function
emb_fname_extension:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L2
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L3
.L2:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L4
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L3
.L4:
	movq	-24(%rbp), %rax
	movl	$46, %esi
	movq	%rax, %rdi
	call	string_rchar@PLT
	movl	%eax, -8(%rbp)
	cmpl	$0, -8(%rbp)
	jne	.L5
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L3
.L5:
	movl	$0, -4(%rbp)
	jmp	.L6
.L7:
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	char_to_lower@PLT
	movl	%eax, %ecx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	addl	$1, -4(%rbp)
.L6:
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L7
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movl	$1, %eax
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	emb_fname_extension, .-emb_fname_extension
	.section	.rodata
	.align 8
.LC3:
	.string	"Failed to isolate the extension of the supplied fileName."
	.text
	.globl	emb_identify_format
	.type	emb_identify_format, @function
emb_identify_format:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	leaq	-9(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_fname_extension
	testl	%eax, %eax
	jne	.L9
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$-1, %eax
	jmp	.L14
.L9:
	movl	$0, -4(%rbp)
	jmp	.L11
.L13:
	movl	-4(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	formatTable(%rip), %rdx
	leaq	(%rax,%rdx), %rcx
	leaq	-9(%rbp), %rax
	movl	$10, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncmp@PLT
	testl	%eax, %eax
	jne	.L12
	movl	-4(%rbp), %eax
	jmp	.L14
.L12:
	addl	$1, -4(%rbp)
.L11:
	cmpl	$60, -4(%rbp)
	jle	.L13
	movl	$-1, %eax
.L14:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	emb_identify_format, .-emb_identify_format
	.section	.rodata
	.align 8
.LC4:
	.string	"ERROR: failed to read %d bytes from file."
	.text
	.globl	read_n_bytes
	.type	read_n_bytes, @function
read_n_bytes:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movl	-20(%rbp), %edx
	movq	-8(%rbp), %rcx
	movq	-16(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	%rax, %rdx
	movl	-20(%rbp), %eax
	cmpq	%rax, %rdx
	je	.L16
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L17
.L16:
	movl	$1, %eax
.L17:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	read_n_bytes, .-read_n_bytes
	.section	.rodata
	.align 8
.LC5:
	.string	"ERROR: emb_pattern_read(), pattern argument is null."
	.align 8
.LC6:
	.string	"ERROR: emb_pattern_read(), fileName argument is null."
.LC7:
	.string	"rb"
	.align 8
.LC8:
	.string	"ERROR: Failed to open file with name: %s.\n"
	.text
	.globl	emb_pattern_read
	.type	emb_pattern_read, @function
emb_pattern_read:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	$0, -4(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L19
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L20
.L19:
	cmpq	$0, -32(%rbp)
	jne	.L21
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L20
.L21:
	movq	-32(%rbp), %rax
	leaq	.LC7(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L22
	cmpl	$15, -36(%rbp)
	je	.L23
	cmpl	$44, -36(%rbp)
	je	.L23
	cmpl	$6, -36(%rbp)
	je	.L23
	cmpl	$26, -36(%rbp)
	je	.L23
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L23:
	movl	$0, %eax
	jmp	.L20
.L22:
	movl	-36(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	412+formatTable(%rip), %rdx
	movl	(%rax,%rdx), %eax
	testl	%eax, %eax
	je	.L24
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_loadExternalColorFile@PLT
.L24:
	cmpl	$60, -36(%rbp)
	ja	.L90
	movl	-36(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L27(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L27(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L27:
	.long	.L87-.L27
	.long	.L86-.L27
	.long	.L85-.L27
	.long	.L84-.L27
	.long	.L83-.L27
	.long	.L82-.L27
	.long	.L81-.L27
	.long	.L80-.L27
	.long	.L79-.L27
	.long	.L78-.L27
	.long	.L77-.L27
	.long	.L76-.L27
	.long	.L75-.L27
	.long	.L74-.L27
	.long	.L73-.L27
	.long	.L72-.L27
	.long	.L71-.L27
	.long	.L70-.L27
	.long	.L69-.L27
	.long	.L68-.L27
	.long	.L67-.L27
	.long	.L66-.L27
	.long	.L65-.L27
	.long	.L64-.L27
	.long	.L63-.L27
	.long	.L62-.L27
	.long	.L61-.L27
	.long	.L60-.L27
	.long	.L59-.L27
	.long	.L58-.L27
	.long	.L57-.L27
	.long	.L56-.L27
	.long	.L55-.L27
	.long	.L54-.L27
	.long	.L53-.L27
	.long	.L52-.L27
	.long	.L51-.L27
	.long	.L50-.L27
	.long	.L49-.L27
	.long	.L48-.L27
	.long	.L47-.L27
	.long	.L46-.L27
	.long	.L45-.L27
	.long	.L44-.L27
	.long	.L43-.L27
	.long	.L42-.L27
	.long	.L41-.L27
	.long	.L40-.L27
	.long	.L39-.L27
	.long	.L38-.L27
	.long	.L37-.L27
	.long	.L36-.L27
	.long	.L35-.L27
	.long	.L34-.L27
	.long	.L33-.L27
	.long	.L32-.L27
	.long	.L31-.L27
	.long	.L30-.L27
	.long	.L29-.L27
	.long	.L28-.L27
	.long	.L26-.L27
	.text
.L87:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	read100
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L86:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	read10o
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L85:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readArt
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L84:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readBmc
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L83:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readBro
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L82:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readCnd
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L81:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readCol
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L80:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readCsd
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L79:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readCsv
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L78:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readDat
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L77:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readDem
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L76:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readDsb
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L75:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readDst
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L74:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readDsz
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L73:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readDxf
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L72:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readEdr
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L71:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readEmd
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L70:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readExp
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L69:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readExy
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L68:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readEys
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L67:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readFxy
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L66:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readGc
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L65:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readGnc
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L64:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readGt
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L63:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readHus
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L62:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readInb
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L61:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readInf
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L60:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readJef
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L59:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readKsm
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L58:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readMax
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L57:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readMit
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L56:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readNew
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L55:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readOfm
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L54:
	movq	-16(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	readPcd
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L53:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPcm
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L52:
	movq	-16(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	readPcq
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L51:
	movq	-16(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	readPcs
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L50:
	movq	-16(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	readPec
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L49:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPel
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L48:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPem
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L47:
	movq	-16(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	readPes
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L46:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPhb
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L45:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPhc
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L44:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPlt
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L43:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readRgb
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L42:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readSew
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L41:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readShv
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L40:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readSst
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L39:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readStx
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L38:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readSvg
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L37:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readT01
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L36:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readT09
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L35:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readTap
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L34:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readThr
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L33:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readTxt
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L32:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readU00
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L31:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readU01
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L30:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readVip
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L29:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readVp3
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L28:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readXxx
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L26:
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readZsk
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	jmp	.L88
.L90:
	nop
.L88:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-36(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	408+formatTable(%rip), %rdx
	movl	(%rax,%rdx), %eax
	testl	%eax, %eax
	jne	.L89
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_end@PLT
.L89:
	movl	-4(%rbp), %eax
.L20:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	emb_pattern_read, .-emb_pattern_read
	.section	.rodata
	.align 8
.LC9:
	.string	"ERROR: emb_pattern_write(), pattern argument is null"
	.align 8
.LC10:
	.string	"ERROR: emb_pattern_write(), fileName argument is null"
	.align 8
.LC11:
	.string	"ERROR: emb_pattern_write(), pattern contains no stitches"
.LC12:
	.string	"wb"
	.align 8
.LC13:
	.string	"Failed to open file with name: %s."
	.text
	.globl	emb_pattern_write
	.type	emb_pattern_write, @function
emb_pattern_write:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$1064, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -1048(%rbp)
	movq	%rsi, -1056(%rbp)
	movl	%edx, -1060(%rbp)
	movl	$0, -20(%rbp)
	cmpq	$0, -1048(%rbp)
	jne	.L92
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L93
.L92:
	cmpq	$0, -1056(%rbp)
	jne	.L94
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L93
.L94:
	movq	-1048(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	jne	.L95
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L93
.L95:
	movl	-1060(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	408+formatTable(%rip), %rdx
	movl	(%rax,%rdx), %eax
	testl	%eax, %eax
	jne	.L96
	movq	-1048(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_end@PLT
.L96:
	movq	-1056(%rbp), %rax
	leaq	.LC12(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L97
	movq	-1056(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L93
.L97:
	cmpl	$60, -1060(%rbp)
	ja	.L163
	movl	-1060(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L100(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L100(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L100:
	.long	.L160-.L100
	.long	.L159-.L100
	.long	.L158-.L100
	.long	.L157-.L100
	.long	.L156-.L100
	.long	.L155-.L100
	.long	.L154-.L100
	.long	.L153-.L100
	.long	.L152-.L100
	.long	.L151-.L100
	.long	.L150-.L100
	.long	.L149-.L100
	.long	.L148-.L100
	.long	.L147-.L100
	.long	.L146-.L100
	.long	.L145-.L100
	.long	.L144-.L100
	.long	.L143-.L100
	.long	.L142-.L100
	.long	.L141-.L100
	.long	.L140-.L100
	.long	.L139-.L100
	.long	.L138-.L100
	.long	.L137-.L100
	.long	.L136-.L100
	.long	.L135-.L100
	.long	.L134-.L100
	.long	.L133-.L100
	.long	.L132-.L100
	.long	.L131-.L100
	.long	.L130-.L100
	.long	.L129-.L100
	.long	.L128-.L100
	.long	.L127-.L100
	.long	.L126-.L100
	.long	.L125-.L100
	.long	.L124-.L100
	.long	.L123-.L100
	.long	.L122-.L100
	.long	.L121-.L100
	.long	.L120-.L100
	.long	.L119-.L100
	.long	.L118-.L100
	.long	.L117-.L100
	.long	.L116-.L100
	.long	.L115-.L100
	.long	.L114-.L100
	.long	.L113-.L100
	.long	.L112-.L100
	.long	.L111-.L100
	.long	.L110-.L100
	.long	.L109-.L100
	.long	.L108-.L100
	.long	.L107-.L100
	.long	.L106-.L100
	.long	.L105-.L100
	.long	.L104-.L100
	.long	.L103-.L100
	.long	.L102-.L100
	.long	.L101-.L100
	.long	.L99-.L100
	.text
.L160:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	write100
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L159:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	write10o
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L158:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeArt
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L157:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeBmc
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L156:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeBro
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L155:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeCnd
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L154:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeCol
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L153:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeCsd
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L152:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeCsv
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L151:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeDat
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L150:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeDem
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L149:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeDsb
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L148:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeDst
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L147:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeDsz
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L146:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeDxf
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L145:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeEdr
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L144:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeEmd
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L143:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeExp
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L142:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeExy
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L141:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeEys
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L140:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeFxy
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L139:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeGc
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L138:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeGnc
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L137:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeGt
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L136:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeHus
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L135:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeInb
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L134:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeInf
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L133:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeJef
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L132:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeKsm
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L131:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeMax
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L130:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeMit
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L129:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeNew
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L128:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeOfm
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L127:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writePcd
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L126:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writePcm
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L125:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writePcq
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L124:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writePcs
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L123:
	movq	-32(%rbp), %rdx
	movq	-1056(%rbp), %rcx
	movq	-1048(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	writePec
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L122:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writePel
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L121:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writePem
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L120:
	movq	-32(%rbp), %rdx
	movq	-1056(%rbp), %rcx
	movq	-1048(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	writePes
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L119:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writePhb
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L118:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writePhc
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L117:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writePlt
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L116:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeRgb
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L115:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeSew
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L114:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeShv
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L113:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeSst
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L112:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeStx
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L111:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeSvg
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L110:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeT01
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L109:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeT09
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L108:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeTap
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L107:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeThr
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L106:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeTxt
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L105:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeU00
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L104:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeU01
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L103:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeVip
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L102:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeVp3
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L101:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeXxx
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L99:
	movq	-32(%rbp), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeZsk
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	jmp	.L161
.L163:
	nop
.L161:
	movl	-1060(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	416+formatTable(%rip), %rdx
	movl	(%rax,%rdx), %eax
	testl	%eax, %eax
	je	.L162
	movq	-1056(%rbp), %rcx
	leaq	-1040(%rbp), %rax
	movl	$200, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncpy@PLT
	movq	-1056(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movl	%eax, %ebx
	movl	-1060(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	formatTable(%rip), %rdx
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movl	%eax, %edx
	movl	%ebx, %eax
	subl	%edx, %eax
	movl	%eax, -36(%rbp)
	movl	-36(%rbp), %eax
	cltq
	movb	$0, -1040(%rbp,%rax)
	leaq	-1040(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	leaq	-1040(%rbp), %rax
	addq	%rdx, %rax
	movl	$1650946606, (%rax)
	movb	$0, 4(%rax)
	leaq	-1040(%rbp), %rcx
	movq	-1048(%rbp), %rax
	movl	$44, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_write
.L162:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	-20(%rbp), %eax
.L93:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	emb_pattern_write, .-emb_pattern_write
	.section	.rodata
	.align 8
.LC14:
	.string	"ERROR: convert(), unsupported read file type: %s\n"
	.text
	.globl	emb_pattern_readAuto
	.type	emb_pattern_readAuto, @function
emb_pattern_readAuto:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_identify_format
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jns	.L165
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free@PLT
	movl	$0, %eax
	jmp	.L166
.L165:
	movl	-4(%rbp), %edx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_read
.L166:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	emb_pattern_readAuto, .-emb_pattern_readAuto
	.section	.rodata
.LC15:
	.string	"emb_pattern_writeAuto %d %s\n"
	.align 8
.LC16:
	.string	"ERROR: convert(), unsupported write file type: %s\n"
	.text
	.globl	emb_pattern_writeAuto
	.type	emb_pattern_writeAuto, @function
emb_pattern_writeAuto:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_identify_format
	movl	%eax, -4(%rbp)
	movq	-32(%rbp), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC15(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	cmpl	$0, -4(%rbp)
	jns	.L168
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC16(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free@PLT
	movl	$0, %eax
	jmp	.L169
.L168:
	movl	-4(%rbp), %edx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_write
.L169:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	emb_pattern_writeAuto, .-emb_pattern_writeAuto
	.globl	toyota_position_encode
	.type	toyota_position_encode, @function
toyota_position_encode:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movss	%xmm0, -4(%rbp)
	pxor	%xmm0, %xmm0
	comiss	-4(%rbp), %xmm0
	jbe	.L175
	movss	-4(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, %edx
	movl	$-128, %eax
	subl	%edx, %eax
	jmp	.L173
.L175:
	movss	-4(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
.L173:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	toyota_position_encode, .-toyota_position_encode
	.globl	toyota_position_decode
	.type	toyota_position_decode, @function
toyota_position_decode:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	cmpb	$-128, -4(%rbp)
	jbe	.L177
	movzbl	-4(%rbp), %eax
	addl	$-128, %eax
	pxor	%xmm1, %xmm1
	cvtsi2sdl	%eax, %xmm1
	movsd	.LC19(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	jmp	.L178
.L177:
	movzbl	-4(%rbp), %eax
	pxor	%xmm1, %xmm1
	cvtsi2sdl	%eax, %xmm1
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
.L178:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	toyota_position_decode, .-toyota_position_decode
	.globl	read100
	.type	read100, @function
read100:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	jmp	.L180
.L183:
	movzbl	-8(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	toyota_position_decode
	movd	%xmm0, %eax
	movl	%eax, -28(%rbp)
	movzbl	-7(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	toyota_position_decode
	movd	%xmm0, %eax
	movl	%eax, -24(%rbp)
	movl	$0, -32(%rbp)
	movzbl	-10(%rbp), %eax
	movzbl	%al, %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L181
	movl	$4, -32(%rbp)
.L181:
	movzbl	-10(%rbp), %eax
	cmpb	$31, %al
	jne	.L182
	movl	$16, -32(%rbp)
.L182:
	movl	-32(%rbp), %esi
	movss	-24(%rbp), %xmm0
	movl	-28(%rbp), %ecx
	movq	-40(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L180:
	movq	-48(%rbp), %rdx
	leaq	-10(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L183
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	read100, .-read100
	.globl	write100
	.type	write100, @function
write100:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	-72(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -12(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L186
.L191:
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movss	-44(%rbp), %xmm0
	movss	-12(%rbp), %xmm1
	subss	%xmm1, %xmm0
	movss	%xmm0, -56(%rbp)
	movss	-40(%rbp), %xmm0
	movss	-8(%rbp), %xmm1
	subss	%xmm1, %xmm0
	movss	%xmm0, -52(%rbp)
	movq	-56(%rbp), %rdx
	movq	-12(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add@PLT
	movq	%xmm0, %rax
	movq	%rax, -12(%rbp)
	movb	$0, -22(%rbp)
	movb	$0, -21(%rbp)
	movl	-56(%rbp), %eax
	movd	%eax, %xmm0
	call	toyota_position_encode
	movb	%al, -20(%rbp)
	movl	-52(%rbp), %eax
	movd	%eax, %xmm0
	call	toyota_position_encode
	movb	%al, -19(%rbp)
	movl	-48(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	jne	.L187
	movzbl	-22(%rbp), %eax
	orl	$1, %eax
	movb	%al, -22(%rbp)
.L187:
	movl	-48(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L188
	movb	$31, -22(%rbp)
.L188:
	movq	-80(%rbp), %rdx
	leaq	-22(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	cmpq	$4, %rax
	je	.L189
	movl	$0, %eax
	jmp	.L192
.L189:
	addl	$1, -4(%rbp)
.L186:
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L191
	movl	$1, %eax
.L192:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	write100, .-write100
	.globl	read10o
	.type	read10o, @function
read10o:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	jmp	.L194
.L201:
	movzbl	-11(%rbp), %eax
	movb	%al, -1(%rbp)
	movzbl	-10(%rbp), %eax
	movzbl	%al, %eax
	pxor	%xmm1, %xmm1
	cvtsi2sdl	%eax, %xmm1
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -24(%rbp)
	movzbl	-9(%rbp), %eax
	movzbl	%al, %eax
	pxor	%xmm1, %xmm1
	cvtsi2sdl	%eax, %xmm1
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -28(%rbp)
	movl	$0, -32(%rbp)
	movzbl	-1(%rbp), %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L195
	movss	-28(%rbp), %xmm0
	movss	.LC21(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, -28(%rbp)
.L195:
	movzbl	-1(%rbp), %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L196
	movss	-24(%rbp), %xmm0
	movss	.LC21(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, -24(%rbp)
.L196:
	movzbl	-1(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L197
	movl	$2, -32(%rbp)
.L197:
	movzbl	-1(%rbp), %eax
	andl	$5, %eax
	cmpl	$5, %eax
	jne	.L198
	movl	$4, -32(%rbp)
.L198:
	cmpb	$-8, -1(%rbp)
	je	.L199
	cmpb	$-111, -1(%rbp)
	je	.L199
	cmpb	$-121, -1(%rbp)
	jne	.L200
.L199:
	movl	$16, -32(%rbp)
.L200:
	movl	-32(%rbp), %esi
	movss	-24(%rbp), %xmm0
	movl	-28(%rbp), %ecx
	movq	-40(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L194:
	movq	-48(%rbp), %rdx
	leaq	-11(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L201
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	read10o, .-read10o
	.globl	write10o
	.type	write10o, @function
write10o:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L204
.L216:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movb	$0, -14(%rbp)
	movb	$0, -13(%rbp)
	movb	$0, -12(%rbp)
	movss	-28(%rbp), %xmm1
	pxor	%xmm0, %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L219
	movzbl	-12(%rbp), %eax
	orl	$32, %eax
	movb	%al, -12(%rbp)
	movss	-28(%rbp), %xmm0
	movss	.LC21(%rip), %xmm1
	xorps	%xmm1, %xmm0
	cvttss2sil	%xmm0, %eax
	movb	%al, -14(%rbp)
	jmp	.L207
.L219:
	movss	-28(%rbp), %xmm0
	cvttss2sil	%xmm0, %eax
	movb	%al, -14(%rbp)
.L207:
	movss	-24(%rbp), %xmm1
	pxor	%xmm0, %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L220
	movzbl	-12(%rbp), %eax
	orl	$64, %eax
	movb	%al, -12(%rbp)
	movss	-24(%rbp), %xmm0
	movss	.LC21(%rip), %xmm1
	xorps	%xmm1, %xmm0
	cvttss2sil	%xmm0, %eax
	movb	%al, -13(%rbp)
	jmp	.L210
.L220:
	movss	-24(%rbp), %xmm0
	cvttss2sil	%xmm0, %eax
	movb	%al, -13(%rbp)
.L210:
	movl	-32(%rbp), %eax
	cmpl	$2, %eax
	jne	.L211
	movzbl	-12(%rbp), %eax
	orl	$1, %eax
	movb	%al, -12(%rbp)
.L211:
	movl	-32(%rbp), %eax
	cmpl	$4, %eax
	jne	.L212
	movzbl	-12(%rbp), %eax
	orl	$5, %eax
	movb	%al, -12(%rbp)
.L212:
	movl	-32(%rbp), %eax
	cmpl	$16, %eax
	jne	.L213
	movb	$-8, -12(%rbp)
.L213:
	movq	-48(%rbp), %rdx
	leaq	-14(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	cmpq	$3, %rax
	je	.L214
	movl	$0, %eax
	jmp	.L215
.L214:
	addl	$1, -4(%rbp)
.L204:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L216
	movl	$1, %eax
.L215:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	write10o, .-write10o
	.section	.rodata
	.align 8
.LC22:
	.string	"ERROR: readArt is not supported yet."
.LC23:
	.string	"Cannot read %p %p\n"
	.text
	.globl	readArt
	.type	readArt, @function
readArt:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC22(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC23(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	readArt, .-readArt
	.section	.rodata
	.align 8
.LC24:
	.string	"ERROR: writeArt is not supported yet."
.LC25:
	.string	"Cannot write %p %p\n"
	.text
	.globl	writeArt
	.type	writeArt, @function
writeArt:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC24(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC25(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	writeArt, .-writeArt
	.section	.rodata
	.align 8
.LC26:
	.string	"ERROR: readBmc is not supported."
	.text
	.globl	readBmc
	.type	readBmc, @function
readBmc:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC26(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC23(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	readBmc, .-readBmc
	.section	.rodata
.LC27:
	.string	"writeBmc is not implemented"
	.text
	.globl	writeBmc
	.type	writeBmc, @function
writeBmc:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC27(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC25(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	writeBmc, .-writeBmc
	.section	.rodata
.LC28:
	.string	"readBro: %s\n"
.LC29:
	.string	"ERROR"
	.text
	.globl	readBro
	.type	readBro, @function
readBro:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-80(%rbp), %rdx
	leaq	-48(%rbp), %rax
	movq	%rdx, %rcx
	movl	$19, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$19, %rax
	je	.L230
	movl	$0, %eax
	jmp	.L243
.L230:
	addq	$3, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC28(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-80(%rbp), %rax
	movl	$0, %edx
	movl	$256, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L232
.L242:
	movl	$0, -4(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movzbl	%al, %eax
	movw	%ax, -50(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movzbl	%al, %eax
	movw	%ax, -52(%rbp)
	movzwl	-50(%rbp), %eax
	cmpw	$-128, %ax
	jne	.L233
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -25(%rbp)
	movq	-80(%rbp), %rdx
	leaq	-50(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L234
	leaq	.LC29(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L243
.L234:
	movq	-80(%rbp), %rdx
	leaq	-52(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L236
	leaq	.LC29(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L243
.L236:
	cmpb	$2, -25(%rbp)
	je	.L237
	cmpb	$-31, -25(%rbp)
	jne	.L238
.L237:
	movl	$4, -4(%rbp)
	jmp	.L233
.L238:
	cmpb	$3, -25(%rbp)
	jne	.L239
	movl	$2, -4(%rbp)
	jmp	.L233
.L239:
	cmpb	$126, -25(%rbp)
	jne	.L233
	movq	-72(%rbp), %rax
	movl	$1, %edx
	movl	$16, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L241
.L233:
	movzwl	-52(%rbp), %eax
	cwtl
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movzwl	-50(%rbp), %eax
	cwtl
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-4(%rbp), %esi
	movq	-72(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L232:
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	je	.L242
.L241:
	movl	$1, %eax
.L243:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	readBro, .-readBro
	.section	.rodata
.LC31:
	.string	"writeBro is not implemented"
	.text
	.globl	writeBro
	.type	writeBro, @function
writeBro:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC31(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC25(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE24:
	.size	writeBro, .-writeBro
	.section	.rodata
.LC32:
	.string	"readCnd is not implemented"
	.text
	.globl	readCnd
	.type	readCnd, @function
readCnd:
.LFB25:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC32(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC23(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE25:
	.size	readCnd, .-readCnd
	.section	.rodata
.LC33:
	.string	"writeCnd is not implemented"
	.text
	.globl	writeCnd
	.type	writeCnd, @function
writeCnd:
.LFB26:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC33(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC25(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE26:
	.size	writeCnd, .-writeCnd
	.section	.rodata
	.align 8
.LC34:
	.string	"ERROR: Number of colors is zero."
	.align 8
.LC35:
	.string	"ERROR: Empty line in col file."
.LC36:
	.string	"%d,%d,%d,%d"
	.text
	.globl	readCol
	.type	readCol, @function
readCol:
.LFB27:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$480, %rsp
	movq	%rdi, -472(%rbp)
	movq	%rsi, -480(%rbp)
	movq	-472(%rbp), %rax
	movq	24(%rax), %rax
	movl	$0, 24(%rax)
	leaq	-464(%rbp), %rcx
	movq	-480(%rbp), %rax
	movl	$30, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_readline@PLT
	leaq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -8(%rbp)
	cmpl	$0, -8(%rbp)
	jg	.L251
	leaq	.LC34(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L258
.L251:
	movl	$0, -4(%rbp)
	jmp	.L253
.L257:
	leaq	-464(%rbp), %rcx
	movq	-480(%rbp), %rax
	movl	$30, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_readline@PLT
	movzbl	-464(%rbp), %eax
	testb	%al, %al
	jne	.L254
	leaq	.LC35(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L258
.L254:
	leaq	-24(%rbp), %rdi
	leaq	-20(%rbp), %rsi
	leaq	-16(%rbp), %rcx
	leaq	-12(%rbp), %rdx
	leaq	-464(%rbp), %rax
	movq	%rdi, %r9
	movq	%rsi, %r8
	leaq	.LC36(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf@PLT
	cmpl	$4, %eax
	jne	.L259
	movl	-24(%rbp), %eax
	movb	%al, -432(%rbp)
	movl	-20(%rbp), %eax
	movb	%al, -431(%rbp)
	movl	-16(%rbp), %eax
	movb	%al, -430(%rbp)
	movb	$0, -229(%rbp)
	movb	$0, -429(%rbp)
	movq	-472(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-432(%rbp), %rax
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
	addl	$1, -4(%rbp)
.L253:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L257
	jmp	.L256
.L259:
	nop
.L256:
	movl	$1, %eax
.L258:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE27:
	.size	readCol, .-readCol
	.section	.rodata
.LC37:
	.string	"%d\r\n"
.LC38:
	.string	"%d,%d,%d,%d\r\n"
	.text
	.globl	writeCol
	.type	writeCol, @function
writeCol:
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
	movq	24(%rax), %rax
	movl	24(%rax), %edx
	movq	-32(%rbp), %rax
	leaq	.LC37(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movl	$0, -4(%rbp)
	jmp	.L261
.L262:
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -7(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -5(%rbp)
	movzbl	-5(%rbp), %eax
	movzbl	%al, %edi
	movzbl	-6(%rbp), %eax
	movzbl	%al, %esi
	movzbl	-7(%rbp), %eax
	movzbl	%al, %ecx
	movl	-4(%rbp), %edx
	movq	-32(%rbp), %rax
	movl	%edi, %r9d
	movl	%esi, %r8d
	leaq	.LC38(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addl	$1, -4(%rbp)
.L261:
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L262
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE28:
	.size	writeCol, .-writeCol
	.globl	_subMask
	.bss
	.align 32
	.type	_subMask, @object
	.size	_subMask, 479
_subMask:
	.zero	479
	.globl	_xorMask
	.align 32
	.type	_xorMask, @object
	.size	_xorMask, 501
_xorMask:
	.zero	501
	.globl	csd_decryptArray
	.section	.rodata
	.align 32
	.type	csd_decryptArray, @object
	.size	csd_decryptArray, 256
csd_decryptArray:
	.string	"Cnrzvlao|)]b`nab Afj:5Zc|7:*%$*3"
	.ascii	"\020\024\003rLHB\bz^\013oEG_@T\\WUYS:2oSTP\\JV//b,\"e%(808\""
	.ascii	"+%:o'8>?t73w.0=4.2+,\f\030B\023\026\n\025\002\013\034\036\016"
	.ascii	"\b`d\r\tQ%\032\030\026\031\032X\020\024[\b\025\033_\325\322\256"
	.ascii	"\243\301\360\364\350\370\354\246\253\315\370\375\373\342\360"
	.ascii	"\376\372\365\265\367\371\374\271\365\357\364\370\354\277\303"
	.ascii	"\316\327\315\320\327\317\302\333\244\240\260\257\276\230\342"
	.ascii	"\302\221\345\334\332\322\226\304\230\370\311\322\335\323\236"
	.ascii	"\336\256\245\342\214\266\254\243\251\274\250\246\353\213\277"
	.ascii	"\241\254\265\243\273\266\247\330\334\232\252\371\202\373\235"
	.ascii	"\271\253\263\224\301\240\214\213\216\225\217\207\231\347\341"
	.ascii	"\243\203\213\317\243\205\235\203\324\267\203\204\221\227\237"
	.ascii	"\210\217\335\255\220"
	.text
	.globl	BuildDecryptionTable
	.type	BuildDecryptionTable, @function
BuildDecryptionTable:
.LFB29:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	$1103515245, -8(%rbp)
	movl	$12345, -12(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L265
.L266:
	movl	-20(%rbp), %eax
	imull	-8(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-12(%rbp), %eax
	addl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	sarl	$16, %eax
	movl	%eax, %ecx
	movl	-4(%rbp), %eax
	cltq
	leaq	_subMask(%rip), %rdx
	movb	%cl, (%rax,%rdx)
	addl	$1, -4(%rbp)
.L265:
	cmpl	$478, -4(%rbp)
	jle	.L266
	movl	$0, -4(%rbp)
	jmp	.L267
.L268:
	movl	-20(%rbp), %eax
	imull	-8(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-12(%rbp), %eax
	addl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	sarl	$16, %eax
	movl	%eax, %ecx
	movl	-4(%rbp), %eax
	cltq
	leaq	_xorMask(%rip), %rdx
	movb	%cl, (%rax,%rdx)
	addl	$1, -4(%rbp)
.L267:
	cmpl	$500, -4(%rbp)
	jle	.L268
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE29:
	.size	BuildDecryptionTable, .-BuildDecryptionTable
	.globl	DecodeCsdByte
	.type	DecodeCsdByte, @function
DecodeCsdByte:
.LFB30:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, %eax
	movl	%edx, -32(%rbp)
	movb	%al, -28(%rbp)
	subq	$1, -24(%rbp)
	cmpl	$0, -32(%rbp)
	je	.L270
	movq	-24(%rbp), %rax
	movb	$0, %al
	movl	%eax, -8(%rbp)
	movq	-24(%rbp), %rax
	andl	$255, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %edx
	movslq	%edx, %rax
	imulq	$715827883, %rax, %rax
	shrq	$32, %rax
	movl	%eax, %ecx
	sarl	$7, %ecx
	movl	%edx, %eax
	sarl	$31, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	addl	%eax, %eax
	addl	%ecx, %eax
	sall	$8, %eax
	subl	%eax, %edx
	movl	%edx, -16(%rbp)
	cmpl	$256, -16(%rbp)
	je	.L271
	cmpl	$512, -16(%rbp)
	je	.L271
	movl	-4(%rbp), %eax
	cltq
	leaq	csd_decryptArray(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	movzbl	%al, %eax
	orl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	jmp	.L276
.L271:
	cmpl	$256, -16(%rbp)
	je	.L273
	cmpl	$512, -16(%rbp)
	jne	.L273
	cmpl	$0, -4(%rbp)
	jne	.L274
	subl	$256, -8(%rbp)
.L274:
	movl	-4(%rbp), %eax
	cltq
	leaq	csd_decryptArray(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	movzbl	%al, %eax
	orl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	jmp	.L276
.L273:
	cmpl	$1, -4(%rbp)
	je	.L275
	cmpl	$0, -4(%rbp)
	je	.L275
	movl	-4(%rbp), %eax
	cltq
	leaq	csd_decryptArray(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	movzbl	%al, %eax
	orl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	jmp	.L276
.L275:
	subl	$256, -8(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	csd_decryptArray(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	movzbl	%al, %eax
	orl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	jmp	.L276
.L270:
	movq	-24(%rbp), %rax
	movl	%eax, -4(%rbp)
.L276:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$548658497, %rdx, %rdx
	shrq	$32, %rdx
	sarl	$6, %edx
	movl	%eax, %ecx
	sarl	$31, %ecx
	subl	%ecx, %edx
	imull	$501, %edx, %ecx
	subl	%ecx, %eax
	movl	%eax, %edx
	movslq	%edx, %rax
	leaq	_xorMask(%rip), %rdx
	movzbl	(%rax,%rdx), %edx
	movzbl	-28(%rbp), %eax
	xorl	%edx, %eax
	movl	%eax, %esi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$1147715687, %rdx, %rdx
	shrq	$32, %rdx
	sarl	$7, %edx
	movl	%eax, %ecx
	sarl	$31, %ecx
	subl	%ecx, %edx
	imull	$479, %edx, %ecx
	subl	%ecx, %eax
	movl	%eax, %edx
	movslq	%edx, %rax
	leaq	_subMask(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	movl	%eax, %edx
	movl	%esi, %eax
	subl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE30:
	.size	DecodeCsdByte, .-DecodeCsdByte
	.section	.rodata
	.align 8
.LC39:
	.string	"unknown bytes to decode: %c %c"
.LC40:
	.string	"Invalid color change detected"
	.text
	.globl	readCsd
	.type	readCsd, @function
readCsd:
.LFB31:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$488, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -488(%rbp)
	movq	%rsi, -496(%rbp)
	movl	$0, -24(%rbp)
	movb	$0, -25(%rbp)
	movb	$0, -26(%rbp)
	movl	$-1, -32(%rbp)
	movq	-496(%rbp), %rdx
	leaq	-51(%rbp), %rax
	movq	%rdx, %rcx
	movl	$8, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$8, %rax
	je	.L279
	leaq	.LC29(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L301
.L279:
	movzbl	-51(%rbp), %eax
	cmpb	$124, %al
	je	.L281
	movzbl	-49(%rbp), %eax
	cmpb	$-61, %al
	je	.L281
	movl	$1, -24(%rbp)
.L281:
	cmpl	$0, -24(%rbp)
	jne	.L282
	movl	$12, %edi
	call	BuildDecryptionTable
	jmp	.L283
.L282:
	movzbl	-51(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	BuildDecryptionTable
.L283:
	movl	$0, -20(%rbp)
	jmp	.L284
.L285:
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movzbl	%al, %ebx
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rcx
	movl	-24(%rbp), %eax
	movl	%eax, %edx
	movl	%ebx, %esi
	movq	%rcx, %rdi
	call	DecodeCsdByte
	movb	%al, -480(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movzbl	%al, %ebx
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rcx
	movl	-24(%rbp), %eax
	movl	%eax, %edx
	movl	%ebx, %esi
	movq	%rcx, %rdi
	call	DecodeCsdByte
	movb	%al, -479(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movzbl	%al, %ebx
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rcx
	movl	-24(%rbp), %eax
	movl	%eax, %edx
	movl	%ebx, %esi
	movq	%rcx, %rdi
	call	DecodeCsdByte
	movb	%al, -478(%rbp)
	movb	$0, -277(%rbp)
	movb	$0, -477(%rbp)
	movq	-488(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-480(%rbp), %rax
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
	addl	$1, -20(%rbp)
.L284:
	cmpl	$15, -20(%rbp)
	jle	.L285
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movzbl	%al, %ebx
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rcx
	movl	-24(%rbp), %eax
	movl	%eax, %edx
	movl	%ebx, %esi
	movq	%rcx, %rdi
	call	DecodeCsdByte
	movb	%al, -37(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movzbl	%al, %ebx
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rcx
	movl	-24(%rbp), %eax
	movl	%eax, %edx
	movl	%ebx, %esi
	movq	%rcx, %rdi
	call	DecodeCsdByte
	movb	%al, -38(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L286
	movzbl	-38(%rbp), %edx
	movzbl	-37(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC39(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L286:
	movl	$0, -20(%rbp)
	jmp	.L287
.L288:
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movzbl	%al, %ebx
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rcx
	movl	-24(%rbp), %eax
	movl	%eax, %edx
	movl	%ebx, %esi
	movq	%rcx, %rdi
	call	DecodeCsdByte
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movb	%al, -65(%rbp,%rdx)
	addl	$1, -20(%rbp)
.L287:
	cmpl	$13, -20(%rbp)
	jle	.L288
	movl	$0, -20(%rbp)
	jmp	.L289
.L300:
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movzbl	%al, %ebx
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rcx
	movl	-24(%rbp), %eax
	movl	%eax, %edx
	movl	%ebx, %esi
	movq	%rcx, %rdi
	call	DecodeCsdByte
	movb	%al, -39(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movzbl	%al, %ebx
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rcx
	movl	-24(%rbp), %eax
	movl	%eax, %edx
	movl	%ebx, %esi
	movq	%rcx, %rdi
	call	DecodeCsdByte
	movb	%al, -40(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movzbl	%al, %ebx
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rcx
	movl	-24(%rbp), %eax
	movl	%eax, %edx
	movl	%ebx, %esi
	movq	%rcx, %rdi
	call	DecodeCsdByte
	movb	%al, -41(%rbp)
	cmpb	$-8, -39(%rbp)
	je	.L290
	cmpb	$-121, -39(%rbp)
	je	.L290
	cmpb	$-111, -39(%rbp)
	je	.L290
	movzbl	-39(%rbp), %eax
	andl	$32, %eax
	testl	%eax, %eax
	setg	%al
	movb	%al, -42(%rbp)
	movzbl	-39(%rbp), %eax
	andl	$64, %eax
	testl	%eax, %eax
	setg	%al
	movb	%al, -43(%rbp)
	andb	$31, -39(%rbp)
	movzbl	-39(%rbp), %eax
	andl	$31, %eax
	testl	%eax, %eax
	jne	.L291
	movl	$0, -36(%rbp)
	jmp	.L292
.L291:
	movzbl	-39(%rbp), %eax
	andl	$12, %eax
	testl	%eax, %eax
	jle	.L293
	movl	$4, -36(%rbp)
	cmpl	$13, -32(%rbp)
	jle	.L294
	leaq	.LC40(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L294:
	movl	-32(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$-1840700269, %rdx, %rdx
	shrq	$32, %rdx
	addl	%eax, %edx
	sarl	$3, %edx
	movl	%eax, %ecx
	sarl	$31, %ecx
	subl	%ecx, %edx
	imull	$14, %edx, %ecx
	subl	%ecx, %eax
	movl	%eax, %edx
	movslq	%edx, %rax
	movzbl	-65(%rbp,%rax), %eax
	movzbl	%al, %edx
	movq	-488(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_pattern_changeColor@PLT
	addl	$1, -32(%rbp)
	jmp	.L292
.L293:
	movzbl	-39(%rbp), %eax
	andl	$31, %eax
	testl	%eax, %eax
	jle	.L295
	movl	$2, -36(%rbp)
	jmp	.L292
.L295:
	movl	$0, -36(%rbp)
.L292:
	movzbl	-41(%rbp), %eax
	movb	%al, -25(%rbp)
	movzbl	-40(%rbp), %eax
	movb	%al, -26(%rbp)
	cmpb	$0, -42(%rbp)
	je	.L296
	movzbl	-25(%rbp), %eax
	negl	%eax
	movb	%al, -25(%rbp)
.L296:
	cmpb	$0, -43(%rbp)
	je	.L297
	movzbl	-26(%rbp), %eax
	negl	%eax
	movb	%al, -26(%rbp)
.L297:
	cmpl	$4, -36(%rbp)
	jne	.L298
	movl	-36(%rbp), %ecx
	movq	-488(%rbp), %rax
	movl	$1, %edx
	movl	%ecx, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L299
.L298:
	movsbl	-26(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movsbl	-25(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-36(%rbp), %esi
	movq	-488(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L299:
	addl	$1, -20(%rbp)
.L289:
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	je	.L300
.L290:
	movl	$1, %eax
.L301:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE31:
	.size	readCsd, .-readCsd
	.section	.rodata
.LC41:
	.string	"writeCsd is not implemented."
	.align 8
.LC42:
	.string	"Overridden, defaulting to dst."
	.text
	.globl	writeCsd
	.type	writeCsd, @function
writeCsd:
.LFB32:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC41(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC42(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeDst
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE32:
	.size	writeCsd, .-writeCsd
	.section	.rodata
.LC43:
	.string	"STITCH"
.LC44:
	.string	"JUMP"
.LC45:
	.string	"TRIM"
.LC46:
	.string	"COLOR"
.LC47:
	.string	"END"
.LC48:
	.string	"UNKNOWN"
	.text
	.globl	csvStitchFlagToStr
	.type	csvStitchFlagToStr, @function
csvStitchFlagToStr:
.LFB33:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	cmpl	$16, -4(%rbp)
	ja	.L305
	movl	-4(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L307(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L307(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L307:
	.long	.L311-.L307
	.long	.L310-.L307
	.long	.L309-.L307
	.long	.L305-.L307
	.long	.L308-.L307
	.long	.L305-.L307
	.long	.L305-.L307
	.long	.L305-.L307
	.long	.L305-.L307
	.long	.L305-.L307
	.long	.L305-.L307
	.long	.L305-.L307
	.long	.L305-.L307
	.long	.L305-.L307
	.long	.L305-.L307
	.long	.L305-.L307
	.long	.L306-.L307
	.text
.L311:
	leaq	.LC43(%rip), %rax
	jmp	.L312
.L310:
	leaq	.LC44(%rip), %rax
	jmp	.L312
.L309:
	leaq	.LC45(%rip), %rax
	jmp	.L312
.L308:
	leaq	.LC46(%rip), %rax
	jmp	.L312
.L306:
	leaq	.LC47(%rip), %rax
	jmp	.L312
.L305:
	leaq	.LC48(%rip), %rax
.L312:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE33:
	.size	csvStitchFlagToStr, .-csvStitchFlagToStr
	.section	.rodata
	.align 8
.LC49:
	.string	"ERROR: format-csv.c csvStrToStitchFlag(), str argument is null"
	.text
	.globl	csvStrToStitchFlag
	.type	csvStrToStitchFlag, @function
csvStrToStitchFlag:
.LFB34:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L314
	leaq	.LC49(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$-1, %eax
	jmp	.L315
.L314:
	movq	-8(%rbp), %rax
	leaq	.LC43(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L316
	movl	$0, %eax
	jmp	.L315
.L316:
	movq	-8(%rbp), %rax
	leaq	.LC44(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L317
	movl	$1, %eax
	jmp	.L315
.L317:
	movq	-8(%rbp), %rax
	leaq	.LC45(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L318
	movl	$2, %eax
	jmp	.L315
.L318:
	movq	-8(%rbp), %rax
	leaq	.LC46(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L319
	movl	$4, %eax
	jmp	.L315
.L319:
	movq	-8(%rbp), %rax
	leaq	.LC47(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L320
	movl	$16, %eax
	jmp	.L315
.L320:
	movq	-8(%rbp), %rax
	leaq	.LC48(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L321
	movl	$4, %eax
	jmp	.L315
.L321:
	movl	$-1, %eax
.L315:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE34:
	.size	csvStrToStitchFlag, .-csvStrToStitchFlag
	.section	.rodata
	.align 8
.LC50:
	.string	"ERROR: format-csv.c readCsv(), premature newline"
.LC51:
	.string	"#"
.LC52:
	.string	">"
.LC53:
	.string	"$"
.LC54:
	.string	"*"
	.text
	.globl	readCsv
	.type	readCsv, @function
readCsv:
.LFB35:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$688, %rsp
	movq	%rdi, -680(%rbp)
	movq	%rsi, -688(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -40(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	movl	$0, -20(%rbp)
	movl	$1, -24(%rbp)
	movl	$0, -28(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -32(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -44(%rbp)
	movb	$0, -33(%rbp)
	movb	$0, -34(%rbp)
	movb	$0, -35(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L323
.L349:
	movq	-688(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -40(%rbp)
	cmpl	$44, -40(%rbp)
	je	.L324
	cmpl	$44, -40(%rbp)
	jg	.L351
	cmpl	$10, -40(%rbp)
	je	.L326
	cmpl	$34, -40(%rbp)
	jne	.L351
	cmpl	$1, -24(%rbp)
	jne	.L327
	movl	$2, -24(%rbp)
	jmp	.L352
.L327:
	cmpl	$2, -24(%rbp)
	jne	.L352
	movl	$3, -24(%rbp)
	jmp	.L352
.L324:
	cmpl	$3, -24(%rbp)
	jne	.L353
	movl	$1, -16(%rbp)
	jmp	.L353
.L326:
	cmpl	$3, -24(%rbp)
	jne	.L331
	movl	$1, -16(%rbp)
	jmp	.L354
.L331:
	cmpl	$1, -24(%rbp)
	je	.L354
	leaq	.LC50(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L350
.L351:
	nop
	jmp	.L329
.L352:
	nop
	jmp	.L329
.L353:
	nop
	jmp	.L329
.L354:
	nop
.L329:
	cmpl	$0, -16(%rbp)
	je	.L334
	movl	-8(%rbp), %eax
	cltq
	movb	$0, -256(%rbp,%rax)
	movl	$0, -8(%rbp)
	movl	$0, -16(%rbp)
	addl	$1, -12(%rbp)
	movl	$1, -24(%rbp)
	cmpl	$0, -20(%rbp)
	jne	.L335
	leaq	-256(%rbp), %rax
	leaq	.LC51(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L336
	movl	$1, -20(%rbp)
	jmp	.L337
.L336:
	leaq	-256(%rbp), %rax
	leaq	.LC52(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L338
	movl	$2, -20(%rbp)
	jmp	.L337
.L338:
	leaq	-256(%rbp), %rax
	leaq	.LC53(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L339
	movl	$3, -20(%rbp)
	jmp	.L337
.L339:
	leaq	-256(%rbp), %rax
	leaq	.LC54(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L340
	movl	$4, -20(%rbp)
	jmp	.L337
.L340:
	movl	$0, %eax
	jmp	.L350
.L335:
	cmpl	$1, -20(%rbp)
	je	.L337
	cmpl	$2, -20(%rbp)
	je	.L337
	cmpl	$3, -20(%rbp)
	jne	.L341
	cmpl	$2, -12(%rbp)
	je	.L337
	cmpl	$3, -12(%rbp)
	jne	.L342
	leaq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movb	%al, -33(%rbp)
	jmp	.L337
.L342:
	cmpl	$4, -12(%rbp)
	jne	.L343
	leaq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movb	%al, -34(%rbp)
	jmp	.L337
.L343:
	cmpl	$5, -12(%rbp)
	jne	.L344
	leaq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movb	%al, -35(%rbp)
	jmp	.L337
.L344:
	cmpl	$6, -12(%rbp)
	je	.L337
	cmpl	$7, -12(%rbp)
	jne	.L345
	movzbl	-33(%rbp), %eax
	movb	%al, -672(%rbp)
	movzbl	-34(%rbp), %eax
	movb	%al, -671(%rbp)
	movzbl	-35(%rbp), %eax
	movb	%al, -670(%rbp)
	leaq	-672(%rbp), %rax
	addq	$3, %rax
	movabsq	$6000277095769722708, %rsi
	movabsq	$5642809484591583811, %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movb	$0, 16(%rax)
	leaq	-672(%rbp), %rax
	addq	$203, %rax
	movabsq	$6071207690389180244, %rsi
	movabsq	$5572446285066095681, %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movl	$5391682, 16(%rax)
	movq	-680(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-672(%rbp), %rax
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
	movl	$0, -20(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L337
.L345:
	movl	$0, %eax
	jmp	.L350
.L341:
	cmpl	$4, -20(%rbp)
	jne	.L337
	cmpl	$2, -12(%rbp)
	jne	.L346
	leaq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	csvStrToStitchFlag
	movl	%eax, -28(%rbp)
	cmpl	$4, -28(%rbp)
	jne	.L337
	addl	$1, -4(%rbp)
	jmp	.L337
.L346:
	cmpl	$3, -12(%rbp)
	jne	.L347
	leaq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	atof@PLT
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -32(%rbp)
	jmp	.L337
.L347:
	cmpl	$4, -12(%rbp)
	jne	.L348
	leaq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	atof@PLT
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -44(%rbp)
	movl	-28(%rbp), %esi
	movss	-44(%rbp), %xmm0
	movl	-32(%rbp), %ecx
	movq	-680(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
	movl	$0, -20(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L337
.L348:
	movl	$0, %eax
	jmp	.L350
.L337:
	cmpl	$10, -40(%rbp)
	jne	.L323
	movl	$0, -20(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L323
.L334:
	cmpl	$2, -24(%rbp)
	jne	.L323
	cmpl	$34, -40(%rbp)
	je	.L323
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	movl	-40(%rbp), %edx
	cltq
	movb	%dl, -256(%rbp,%rax)
.L323:
	movq	-688(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	je	.L349
	movl	$1, %eax
.L350:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE35:
	.size	readCsv, .-readCsv
	.section	.rodata
	.align 8
.LC55:
	.string	"\"#\",\"Embroidermodder 2 CSV Embroidery File\"\n"
	.align 8
.LC56:
	.string	"\"#\",\"http://embroidermodder.github.io\"\n"
.LC57:
	.string	"\"#\",\" \"\n"
.LC58:
	.string	"\"#\",\"General Notes:\"\n"
	.align 8
.LC59:
	.string	"\"#\",\"This file can be read by Excel or LibreOffice as CSV (Comma Separated Value) or with a text editor.\"\n"
	.align 8
.LC60:
	.string	"\"#\",\"Lines beginning with # are comments.\"\n"
	.align 8
.LC61:
	.string	"\"#\",\"Lines beginning with > are variables: [VAR_NAME], [VAR_VALUE]\"\n"
	.align 8
.LC62:
	.string	"\"#\",\"Lines beginning with $ are threads: [THREAD_NUMBER], [RED], [GREEN], [BLUE], [DESCRIPTION], [CATALOG_NUMBER]\"\n"
	.align 8
.LC63:
	.string	"\"#\",\"Lines beginning with * are stitch entries: [STITCH_TYPE], [X], [Y]\"\n"
.LC64:
	.string	"\"#\",\"Stitch Entry Notes:\"\n"
	.align 8
.LC65:
	.string	"\"#\",\"STITCH instructs the machine to move to the position [X][Y] and then make a stitch.\"\n"
	.align 8
.LC66:
	.string	"\"#\",\"JUMP instructs the machine to move to the position [X][Y] without making a stitch.\"\n"
	.align 8
.LC67:
	.string	"\"#\",\"TRIM instructs the machine to cut the thread before moving to the position [X][Y] without making a stitch.\"\n"
	.align 8
.LC68:
	.string	"\"#\",\"COLOR instructs the machine to stop temporarily so that the user can change to a different color thread before resuming.\"\n"
	.align 8
.LC69:
	.string	"\"#\",\"END instructs the machine that the design is completed and there are no further instructions.\"\n"
	.align 8
.LC70:
	.string	"\"#\",\"UNKNOWN encompasses instructions that may not be supported currently.\"\n"
	.align 8
.LC71:
	.string	"\"#\",\"[X] and [Y] are absolute coordinates in millimeters (mm).\"\n"
	.align 8
.LC72:
	.string	"\"#\",\"[VAR_NAME]\",\"[VAR_VALUE]\"\n"
.LC73:
	.string	"\">\",\"STITCH_COUNT:\",\"%u\"\n"
.LC74:
	.string	"\">\",\"THREAD_COUNT:\",\"%u\"\n"
.LC75:
	.string	"\">\",\"EXTENTS_LEFT:\",\"%f\"\n"
.LC76:
	.string	"\">\",\"EXTENTS_TOP:\",\"%f\"\n"
.LC77:
	.string	"\">\",\"EXTENTS_RIGHT:\",\"%f\"\n"
.LC78:
	.string	"\">\",\"EXTENTS_BOTTOM:\",\"%f\"\n"
.LC79:
	.string	"\">\",\"EXTENTS_WIDTH:\",\"%f\"\n"
.LC80:
	.string	"\">\",\"EXTENTS_HEIGHT:\",\"%f\"\n"
	.align 8
.LC81:
	.string	"\"#\",\"[THREAD_NUMBER]\",\"[RED]\",\"[GREEN]\","
	.align 8
.LC82:
	.string	"\"[BLUE]\",\"[DESCRIPTION]\",\"[CATALOG_NUMBER]\"\n"
	.align 8
.LC83:
	.string	"\"$\",\"%d\",\"%d\",\"%d\",\"%d\",\"%s\",\"%s\"\n"
	.align 8
.LC84:
	.string	"\"#\",\"[STITCH_TYPE]\",\"[X]\",\"[Y]\"\n"
.LC85:
	.string	"\"*\",\"%s\",\"%f\",\"%f\"\n"
	.text
	.globl	writeCsv
	.type	writeCsv, @function
writeCsv:
.LFB36:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$504, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -488(%rbp)
	movq	%rsi, -496(%rbp)
	leaq	-48(%rbp), %rax
	movq	-488(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_bounds@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$44, %edx
	movl	$1, %esi
	leaq	.LC55(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$39, %edx
	movl	$1, %esi
	leaq	.LC56(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$8, %edx
	movl	$1, %esi
	leaq	.LC57(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$21, %edx
	movl	$1, %esi
	leaq	.LC58(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$106, %edx
	movl	$1, %esi
	leaq	.LC59(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$43, %edx
	movl	$1, %esi
	leaq	.LC60(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$68, %edx
	movl	$1, %esi
	leaq	.LC61(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$115, %edx
	movl	$1, %esi
	leaq	.LC62(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$73, %edx
	movl	$1, %esi
	leaq	.LC63(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$8, %edx
	movl	$1, %esi
	leaq	.LC57(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$26, %edx
	movl	$1, %esi
	leaq	.LC64(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$90, %edx
	movl	$1, %esi
	leaq	.LC65(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$89, %edx
	movl	$1, %esi
	leaq	.LC66(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$113, %edx
	movl	$1, %esi
	leaq	.LC67(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$127, %edx
	movl	$1, %esi
	leaq	.LC68(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$100, %edx
	movl	$1, %esi
	leaq	.LC69(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$76, %edx
	movl	$1, %esi
	leaq	.LC70(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$64, %edx
	movl	$1, %esi
	leaq	.LC71(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$8, %edx
	movl	$1, %esi
	leaq	.LC57(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$31, %edx
	movl	$1, %esi
	leaq	.LC72(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-488(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, %edx
	movq	-496(%rbp), %rax
	leaq	.LC73(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movq	-488(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, %edx
	movq	-496(%rbp), %rax
	leaq	.LC74(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movss	-48(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movq	%xmm2, %rdx
	movq	-496(%rbp), %rax
	movq	%rdx, %xmm0
	leaq	.LC75(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf@PLT
	movss	-44(%rbp), %xmm0
	pxor	%xmm3, %xmm3
	cvtss2sd	%xmm0, %xmm3
	movq	%xmm3, %rdx
	movq	-496(%rbp), %rax
	movq	%rdx, %xmm0
	leaq	.LC76(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf@PLT
	movss	-48(%rbp), %xmm1
	movss	-40(%rbp), %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm0, %xmm4
	movq	%xmm4, %rdx
	movq	-496(%rbp), %rax
	movq	%rdx, %xmm0
	leaq	.LC77(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf@PLT
	movss	-44(%rbp), %xmm1
	movss	-36(%rbp), %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm5, %xmm5
	cvtss2sd	%xmm0, %xmm5
	movq	%xmm5, %rdx
	movq	-496(%rbp), %rax
	movq	%rdx, %xmm0
	leaq	.LC78(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf@PLT
	movss	-40(%rbp), %xmm0
	pxor	%xmm6, %xmm6
	cvtss2sd	%xmm0, %xmm6
	movq	%xmm6, %rdx
	movq	-496(%rbp), %rax
	movq	%rdx, %xmm0
	leaq	.LC79(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf@PLT
	movss	-36(%rbp), %xmm0
	pxor	%xmm7, %xmm7
	cvtss2sd	%xmm0, %xmm7
	movq	%xmm7, %rdx
	movq	-496(%rbp), %rax
	movq	%rdx, %xmm0
	leaq	.LC80(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$1, %eax
	call	fprintf@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rsi
	movl	$10, %edi
	call	fputc@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$40, %edx
	movl	$1, %esi
	leaq	.LC81(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$44, %edx
	movl	$1, %esi
	leaq	.LC82(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$0, -20(%rbp)
	jmp	.L356
.L357:
	movq	-488(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rax, %rdx
	leaq	-480(%rbp), %rax
	movl	$50, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	movq	%rsi, %rdx
	movq	%rdi, %rax
	movzwl	(%rdx), %ecx
	movw	%cx, (%rax)
	leaq	2(%rax), %rax
	leaq	2(%rdx), %rdx
	movzbl	(%rdx), %ecx
	movb	%cl, (%rax)
	movzbl	-478(%rbp), %eax
	movzbl	%al, %r8d
	movzbl	-479(%rbp), %eax
	movzbl	%al, %edi
	movzbl	-480(%rbp), %eax
	movzbl	%al, %edx
	movl	-20(%rbp), %eax
	leal	1(%rax), %esi
	movq	-496(%rbp), %rax
	leaq	-480(%rbp), %rcx
	addq	$203, %rcx
	pushq	%rcx
	leaq	-480(%rbp), %rcx
	addq	$3, %rcx
	pushq	%rcx
	movl	%r8d, %r9d
	movl	%edi, %r8d
	movl	%edx, %ecx
	movl	%esi, %edx
	leaq	.LC83(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addq	$16, %rsp
	addl	$1, -20(%rbp)
.L356:
	movq	-488(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L357
	movq	-496(%rbp), %rax
	movq	%rax, %rsi
	movl	$10, %edi
	call	fputc@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rcx
	movl	$32, %edx
	movl	$1, %esi
	leaq	.LC84(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$0, -20(%rbp)
	jmp	.L358
.L359:
	movq	-488(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movss	-56(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movsd	%xmm2, -504(%rbp)
	movss	-60(%rbp), %xmm0
	pxor	%xmm3, %xmm3
	cvtss2sd	%xmm0, %xmm3
	movq	%xmm3, %rbx
	movl	-64(%rbp), %eax
	movl	%eax, %edi
	call	csvStitchFlagToStr
	movq	%rax, %rdx
	movq	-496(%rbp), %rax
	movsd	-504(%rbp), %xmm1
	movq	%rbx, %xmm0
	leaq	.LC85(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
	addl	$1, -20(%rbp)
.L358:
	movq	-488(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L359
	movl	$1, %eax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE36:
	.size	writeCsv, .-writeCsv
	.section	.rodata
	.align 8
.LC86:
	.string	"ERROR: dat file too short to contain header."
.LC87:
	.string	"stitchesRemaining: %d\n"
	.text
	.globl	readDat
	.type	readDat, @function
readDat:
.LFB37:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -16(%rbp)
	cmpl	$255, -16(%rbp)
	jg	.L362
	leaq	.LC86(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L363
.L362:
	movq	-48(%rbp), %rax
	movl	$0, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movzwl	%ax, %eax
	movl	%eax, -20(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L364
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC87(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L364:
	movq	-48(%rbp), %rax
	movl	$0, %edx
	movl	$256, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L365
.L372:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -4(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -8(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -21(%rbp)
	movl	$0, -12(%rbp)
	movzbl	-21(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	jne	.L366
	movl	$2, -12(%rbp)
.L366:
	cmpb	$-121, -21(%rbp)
	jne	.L367
	movl	$4, -12(%rbp)
.L367:
	cmpb	$-8, -21(%rbp)
	je	.L373
	cmpl	$127, -4(%rbp)
	jle	.L370
	movl	-4(%rbp), %eax
	andl	$127, %eax
	negl	%eax
	movl	%eax, -4(%rbp)
.L370:
	cmpl	$127, -8(%rbp)
	jle	.L371
	movl	-8(%rbp), %eax
	andl	$127, %eax
	negl	%eax
	movl	%eax, -8(%rbp)
.L371:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-8(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-4(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-12(%rbp), %esi
	movq	-40(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L365:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	je	.L372
	jmp	.L369
.L373:
	nop
.L369:
	movl	$1, %eax
.L363:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE37:
	.size	readDat, .-readDat
	.globl	writeDat
	.type	writeDat, @function
writeDat:
.LFB38:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movl	$256, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movl	$0, -4(%rbp)
	jmp	.L375
.L383:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movb	$0, -7(%rbp)
	movb	$0, -6(%rbp)
	movb	$0, -5(%rbp)
	movl	-32(%rbp), %eax
	cmpl	$4, %eax
	jne	.L376
	movb	$-121, -5(%rbp)
.L376:
	movl	-32(%rbp), %eax
	cmpl	$16, %eax
	jne	.L377
	movzbl	-5(%rbp), %eax
	orl	$-8, %eax
	movb	%al, -5(%rbp)
	jmp	.L378
.L377:
	movl	-32(%rbp), %eax
	cmpl	$2, %eax
	je	.L378
	movzbl	-5(%rbp), %eax
	orl	$2, %eax
	movb	%al, -5(%rbp)
.L378:
	movss	-28(%rbp), %xmm1
	pxor	%xmm0, %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L379
	movss	-28(%rbp), %xmm1
	movss	.LC88(%rip), %xmm0
	addss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %eax
	movb	%al, -7(%rbp)
.L379:
	movss	-24(%rbp), %xmm1
	pxor	%xmm0, %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L381
	movss	-24(%rbp), %xmm1
	movss	.LC88(%rip), %xmm0
	addss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %eax
	movb	%al, -6(%rbp)
.L381:
	movq	-48(%rbp), %rdx
	leaq	-7(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	addl	$1, -4(%rbp)
.L375:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L383
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE38:
	.size	writeDat, .-writeDat
	.section	.rodata
.LC89:
	.string	"readDem is not implemented."
	.text
	.globl	readDem
	.type	readDem, @function
readDem:
.LFB39:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC89(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC42(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readDst
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE39:
	.size	readDem, .-readDem
	.section	.rodata
.LC90:
	.string	"writeDem is not implemented."
	.text
	.globl	writeDem
	.type	writeDem, @function
writeDem:
.LFB40:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC90(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC42(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeDst
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE40:
	.size	writeDem, .-writeDem
	.globl	readDsb
	.type	readDsb, @function
readDsb:
.LFB41:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$560, %rsp
	movq	%rdi, -552(%rbp)
	movq	%rsi, -560(%rbp)
	movq	-560(%rbp), %rdx
	leaq	-528(%rbp), %rax
	movq	%rdx, %rcx
	movl	$512, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$512, %rax
	je	.L394
	leaq	.LC29(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L403
.L402:
	movl	$0, -12(%rbp)
	movzbl	-531(%rbp), %eax
	movb	%al, -13(%rbp)
	movzbl	-530(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, -8(%rbp)
	movzbl	-529(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, -4(%rbp)
	movzbl	-13(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L395
	movl	$2, -12(%rbp)
.L395:
	movzbl	-13(%rbp), %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L396
	negl	-4(%rbp)
.L396:
	movzbl	-13(%rbp), %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L397
	negl	-8(%rbp)
.L397:
	movzbl	-13(%rbp), %eax
	andl	$5, %eax
	cmpl	$5, %eax
	jne	.L398
	movl	$4, -12(%rbp)
.L398:
	cmpb	$-8, -13(%rbp)
	je	.L399
	cmpb	$-111, -13(%rbp)
	je	.L399
	cmpb	$-121, -13(%rbp)
	jne	.L400
.L399:
	movq	-552(%rbp), %rax
	movl	$1, %edx
	movl	$16, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L401
.L400:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-8(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-4(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-12(%rbp), %esi
	movq	-552(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L394:
	movq	-560(%rbp), %rdx
	leaq	-531(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L402
.L401:
	movl	$1, %eax
.L403:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE41:
	.size	readDsb, .-readDsb
	.section	.rodata
.LC91:
	.string	"writeDsb is not implemented"
	.text
	.globl	writeDsb
	.type	writeDsb, @function
writeDsb:
.LFB42:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC91(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC42(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeDst
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE42:
	.size	writeDsb, .-writeDsb
	.globl	decode_record_flags
	.type	decode_record_flags, @function
decode_record_flags:
.LFB43:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	cmpb	$-13, -4(%rbp)
	jne	.L407
	movl	$16, %eax
	jmp	.L408
.L407:
	movzbl	-4(%rbp), %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L409
	movl	$4, %eax
	jmp	.L408
.L409:
	movzbl	-4(%rbp), %eax
	testb	%al, %al
	jns	.L410
	movl	$1, %eax
	jmp	.L408
.L410:
	movl	$0, %eax
.L408:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE43:
	.size	decode_record_flags, .-decode_record_flags
	.globl	encode_record
	.type	encode_record, @function
encode_record:
.LFB44:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movl	%edx, -48(%rbp)
	movl	%ecx, -52(%rbp)
	movl	-48(%rbp), %edx
	movl	-44(%rbp), %ecx
	leaq	-19(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	encode_tajima_ternary@PLT
	movzbl	-17(%rbp), %eax
	orl	$3, %eax
	movb	%al, -17(%rbp)
	movl	-52(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L412
	movb	$0, -19(%rbp)
	movb	$0, -18(%rbp)
	movb	$-115, -17(%rbp)
.L412:
	movl	-52(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L413
	movl	$5, -8(%rbp)
	movl	-44(%rbp), %eax
	cltd
	idivl	-8(%rbp)
	movl	%eax, -12(%rbp)
	movl	-48(%rbp), %eax
	cltd
	idivl	-8(%rbp)
	movl	%eax, -16(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L414
.L415:
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %esi
	movq	-40(%rbp), %rax
	movl	$1, %ecx
	movq	%rax, %rdi
	call	encode_record
	addl	$1, -4(%rbp)
.L414:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L415
	movl	-8(%rbp), %eax
	subl	$1, %eax
	imull	-16(%rbp), %eax
	movl	-48(%rbp), %edx
	subl	%eax, %edx
	movl	-8(%rbp), %eax
	subl	$1, %eax
	imull	-12(%rbp), %eax
	movl	-44(%rbp), %ecx
	subl	%eax, %ecx
	movl	%ecx, %esi
	movq	-40(%rbp), %rax
	movl	$1, %ecx
	movq	%rax, %rdi
	call	encode_record
	jmp	.L411
.L413:
	movl	-52(%rbp), %eax
	andl	$3, %eax
	testl	%eax, %eax
	je	.L417
	movzbl	-17(%rbp), %eax
	orl	$-125, %eax
	movb	%al, -17(%rbp)
.L417:
	movl	-52(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L418
	movzbl	-17(%rbp), %eax
	orl	$-61, %eax
	movb	%al, -17(%rbp)
.L418:
	movq	-40(%rbp), %rdx
	leaq	-19(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
.L411:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE44:
	.size	encode_record, .-encode_record
	.globl	set_dst_variable
	.type	set_dst_variable, @function
set_dst_variable:
.LFB45:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$448, %rsp
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	%rdx, -440(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L420
.L422:
	movl	-4(%rbp), %edx
	movq	-432(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$96, %al
	jle	.L421
	movl	-4(%rbp), %edx
	movq	-432(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$122, %al
	jg	.L421
	movl	-4(%rbp), %edx
	movq	-432(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	leal	-32(%rax), %ecx
	movl	-4(%rbp), %edx
	movq	-432(%rbp), %rax
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
.L421:
	addl	$1, -4(%rbp)
.L420:
	movq	-432(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	cmpl	-4(%rbp), %eax
	jnb	.L422
	movq	-432(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	sall	$8, %eax
	movl	%eax, %edx
	movq	-432(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	addl	%edx, %eax
	cmpl	$21571, %eax
	je	.L423
	cmpl	$21571, %eax
	jg	.L432
	cmpl	$21332, %eax
	je	.L433
	cmpl	$21332, %eax
	jg	.L432
	cmpl	$20548, %eax
	je	.L426
	cmpl	$20548, %eax
	jg	.L432
	cmpl	$19801, %eax
	jg	.L432
	cmpl	$19800, %eax
	jge	.L434
	cmpl	$19521, %eax
	je	.L435
	cmpl	$19521, %eax
	jg	.L432
	cmpl	$17232, %eax
	je	.L436
	cmpl	$17232, %eax
	jg	.L432
	cmpl	$17231, %eax
	je	.L433
	cmpl	$17231, %eax
	jg	.L432
	cmpl	$16729, %eax
	jg	.L432
	cmpl	$16728, %eax
	jge	.L434
	cmpl	$16725, %eax
	je	.L436
	cmpl	$16725, %eax
	jg	.L432
	cmpl	$11097, %eax
	jg	.L430
	cmpl	$11096, %eax
	jge	.L433
	jmp	.L432
.L430:
	subl	$11608, %eax
	cmpl	$1, %eax
	ja	.L432
	jmp	.L433
.L426:
	movq	-440(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	jmp	.L431
.L423:
	movq	-440(%rbp), %rax
	movq	%rax, %rdi
	call	embColor_fromHexStr@PLT
	cltq
	movb	%al, -416(%rbp)
	movzbl	%ah, %edx
	movb	%dl, -415(%rbp)
	shrq	$16, %rax
	andb	$-1, %ah
	movb	%al, -414(%rbp)
	movb	$0, -413(%rbp)
	movb	$0, -213(%rbp)
	movq	-424(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-416(%rbp), %rax
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
	jmp	.L431
.L432:
	nop
	jmp	.L437
.L433:
	nop
	jmp	.L437
.L434:
	nop
	jmp	.L437
.L435:
	nop
	jmp	.L437
.L436:
	nop
.L431:
.L437:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE45:
	.size	set_dst_variable, .-set_dst_variable
	.section	.rodata
	.align 8
.LC92:
	.string	"ERROR: Failed to read header bytes."
	.text
	.globl	readDst
	.type	readDst, @function
readDst:
.LFB46:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$1088, %rsp
	movq	%rdi, -1080(%rbp)
	movq	%rsi, -1088(%rbp)
	movl	$0, -4(%rbp)
	movq	-1088(%rbp), %rdx
	leaq	-1056(%rbp), %rax
	movq	%rdx, %rcx
	movl	$512, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$512, %rax
	je	.L439
	leaq	.LC92(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L452
.L439:
	movl	$0, -4(%rbp)
	jmp	.L441
.L447:
	movl	-4(%rbp), %eax
	cltq
	movzbl	-1056(%rbp,%rax), %eax
	cmpb	$58, %al
	jne	.L442
	cmpl	$1, -4(%rbp)
	jle	.L442
	movl	-4(%rbp), %eax
	subl	$2, %eax
	cltq
	movzbl	-1056(%rbp,%rax), %eax
	movb	%al, -15(%rbp)
	movl	-4(%rbp), %eax
	subl	$1, %eax
	cltq
	movzbl	-1056(%rbp,%rax), %eax
	movb	%al, -14(%rbp)
	movb	$0, -13(%rbp)
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	addl	$1, -4(%rbp)
	jmp	.L443
.L446:
	movl	-4(%rbp), %eax
	cltq
	movzbl	-1056(%rbp,%rax), %eax
	cmpb	$13, %al
	jne	.L444
	movl	-4(%rbp), %eax
	cltq
	movzbl	-1056(%rbp,%rax), %eax
	cmpb	$58, %al
	jne	.L445
	subl	$2, -4(%rbp)
.L445:
	movl	-4(%rbp), %eax
	subl	-12(%rbp), %eax
	movslq	%eax, %rdx
	leaq	-1056(%rbp), %rcx
	movl	-12(%rbp), %eax
	cltq
	addq	%rax, %rcx
	leaq	-528(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	movl	-4(%rbp), %eax
	subl	-12(%rbp), %eax
	cltq
	movb	$0, -528(%rbp,%rax)
	leaq	-528(%rbp), %rdx
	leaq	-15(%rbp), %rcx
	movq	-1080(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	set_dst_variable
	jmp	.L442
.L444:
	addl	$1, -4(%rbp)
.L443:
	cmpl	$511, -4(%rbp)
	jle	.L446
.L442:
	addl	$1, -4(%rbp)
.L441:
	cmpl	$511, -4(%rbp)
	jle	.L447
	jmp	.L448
.L451:
	leaq	-1064(%rbp), %rdx
	leaq	-1060(%rbp), %rcx
	leaq	-531(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	decode_tajima_ternary@PLT
	movzbl	-529(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	decode_record_flags
	movl	%eax, -8(%rbp)
	cmpl	$16, -8(%rbp)
	je	.L453
	movl	-1064(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movl	-1060(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-8(%rbp), %esi
	movq	-1080(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L448:
	movq	-1088(%rbp), %rdx
	leaq	-531(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L451
	jmp	.L450
.L453:
	nop
.L450:
	movl	$1, %eax
.L452:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE46:
	.size	readDst, .-readDst
	.section	.rodata
.LC94:
	.string	"Untitled"
.LC95:
	.string	"LA:%-16s\r"
.LC96:
	.string	"ST:%7d\r"
.LC97:
	.string	"CO:%3d\r"
.LC99:
	.string	"+X:%5d\r-X:%5d\r+Y:%5d\r-Y:%5d\r"
	.align 8
.LC100:
	.string	"AX:+%5d\rAY:+%5d\rMX:+%5d\rMY:+%5d\rPD:%6s\r\032"
.LC102:
	.string	"%d %f %f %d %d %f %f %d\n"
.LC103:
	.string	"\241"
	.string	""
	.string	""
	.text
	.globl	writeDst
	.type	writeDst, @function
writeDst:
.LFB47:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$304, %rsp
	movq	%rdi, -296(%rbp)
	movq	%rsi, -304(%rbp)
	movq	-296(%rbp), %rax
	movss	.LC93(%rip), %xmm1
	movl	.LC93(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_correctForMaxStitchLength@PLT
	leaq	-64(%rbp), %rax
	movq	-296(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_bounds@PLT
	movq	-304(%rbp), %rax
	leaq	.LC94(%rip), %rdx
	leaq	.LC95(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movq	-296(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %edx
	movq	-304(%rbp), %rax
	leaq	.LC96(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movq	-296(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	leal	-1(%rax), %edx
	movq	-304(%rbp), %rax
	leaq	.LC97(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movss	-60(%rbp), %xmm0
	movss	.LC98(%rip), %xmm1
	andps	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %edi
	movss	-60(%rbp), %xmm1
	movss	-52(%rbp), %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %esi
	movss	-64(%rbp), %xmm0
	movss	.LC98(%rip), %xmm1
	andps	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %ecx
	movss	-64(%rbp), %xmm1
	movss	-56(%rbp), %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %edx
	movq	-304(%rbp), %rax
	movl	%edi, %r9d
	movl	%esi, %r8d
	leaq	.LC99(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movl	$0, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -20(%rbp)
	leaq	-272(%rbp), %rax
	movl	$707406378, (%rax)
	movl	$2763306, 3(%rax)
	movl	-8(%rbp), %r8d
	movl	-12(%rbp), %edi
	movl	-16(%rbp), %ecx
	movl	-20(%rbp), %edx
	movq	-304(%rbp), %rax
	subq	$8, %rsp
	leaq	-272(%rbp), %rsi
	pushq	%rsi
	movl	%r8d, %r9d
	movl	%edi, %r8d
	leaq	.LC100(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addq	$16, %rsp
	movq	-304(%rbp), %rax
	movl	$387, %edx
	movl	$32, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	pxor	%xmm0, %xmm0
	movss	%xmm0, -72(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -68(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L455
.L457:
	movq	-296(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -288(%rbp)
	movq	%rdx, -280(%rbp)
	movss	-284(%rbp), %xmm0
	movss	-72(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, -24(%rbp)
	movss	-280(%rbp), %xmm0
	movss	-68(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, -28(%rbp)
	movss	-72(%rbp), %xmm1
	pxor	%xmm2, %xmm2
	cvtsi2ssl	-24(%rbp), %xmm2
	movss	.LC101(%rip), %xmm0
	mulss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -72(%rbp)
	movss	-68(%rbp), %xmm1
	pxor	%xmm2, %xmm2
	cvtsi2ssl	-28(%rbp), %xmm2
	movss	.LC101(%rip), %xmm0
	mulss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -68(%rbp)
	movl	emb_verbose(%rip), %eax
	testl	%eax, %eax
	jle	.L456
	movl	-288(%rbp), %edi
	movss	-68(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-72(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-280(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-284(%rbp), %xmm3
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm3, %xmm4
	movq	%xmm4, %rsi
	movl	-28(%rbp), %ecx
	movl	-24(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edi, %r8d
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rsi, %xmm0
	movl	%eax, %esi
	leaq	.LC102(%rip), %rax
	movq	%rax, %rdi
	movl	$4, %eax
	call	printf@PLT
.L456:
	movl	-288(%rbp), %ecx
	movl	-28(%rbp), %edx
	movl	-24(%rbp), %esi
	movq	-304(%rbp), %rax
	movq	%rax, %rdi
	call	encode_record
	addl	$1, -4(%rbp)
.L455:
	movq	-296(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L457
	movq	-304(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	leaq	.LC103(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE47:
	.size	writeDst, .-writeDst
	.globl	readDsz
	.type	readDsz, @function
readDsz:
.LFB48:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movl	$0, %edx
	movl	$512, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L460
.L467:
	movl	$0, -12(%rbp)
	movzbl	-16(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, -8(%rbp)
	movzbl	-15(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, -4(%rbp)
	movzbl	-14(%rbp), %eax
	movb	%al, -13(%rbp)
	movzbl	-13(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L461
	movl	$2, -12(%rbp)
.L461:
	movzbl	-13(%rbp), %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L462
	negl	-8(%rbp)
.L462:
	movzbl	-13(%rbp), %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L463
	negl	-4(%rbp)
.L463:
	movzbl	-13(%rbp), %eax
	andl	$14, %eax
	testl	%eax, %eax
	je	.L464
	movl	$4, -12(%rbp)
.L464:
	movzbl	-13(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L465
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movl	$16, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L466
.L465:
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-8(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	movaps	%xmm0, %xmm2
	divss	%xmm1, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-4(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	divss	%xmm1, %xmm0
	movd	%xmm0, %ecx
	movl	-12(%rbp), %esi
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L460:
	movq	-32(%rbp), %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L467
.L466:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE48:
	.size	readDsz, .-readDsz
	.globl	writeDsz
	.type	writeDsz, @function
writeDsz:
.LFB49:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	-80(%rbp), %rax
	movl	$200, %edx
	movl	$32, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	pxor	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L470
.L478:
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movss	-44(%rbp), %xmm0
	movss	%xmm0, -28(%rbp)
	movss	-40(%rbp), %xmm0
	movss	%xmm0, -24(%rbp)
	movq	-20(%rbp), %rdx
	movq	-28(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract@PLT
	movq	%xmm0, %rax
	movq	%rax, -12(%rbp)
	movb	$0, -49(%rbp)
	movl	-48(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L471
	movzbl	-49(%rbp), %eax
	orl	$1, %eax
	movb	%al, -49(%rbp)
.L471:
	movss	-12(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L472
	movzbl	-49(%rbp), %eax
	orl	$32, %eax
	movb	%al, -49(%rbp)
.L472:
	movss	-8(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L474
	movzbl	-49(%rbp), %eax
	orl	$64, %eax
	movb	%al, -49(%rbp)
.L474:
	movl	-48(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L476
	movzbl	-49(%rbp), %eax
	orl	$14, %eax
	movb	%al, -49(%rbp)
.L476:
	movl	-48(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L477
	movzbl	-49(%rbp), %eax
	orl	$16, %eax
	movb	%al, -49(%rbp)
.L477:
	movss	-12(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movb	%al, -51(%rbp)
	movss	-8(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movb	%al, -50(%rbp)
	movq	-80(%rbp), %rdx
	leaq	-51(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	addl	$1, -4(%rbp)
.L470:
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L478
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE49:
	.size	writeDsz, .-writeDsz
	.globl	readLine
	.type	readLine, @function
readLine:
.LFB50:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L483
.L490:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	je	.L484
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	jmp	.L485
.L484:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, %ecx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	je	.L486
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$13, %al
	jne	.L487
.L486:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	jmp	.L485
.L487:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	jne	.L488
	cmpl	$0, -8(%rbp)
	jne	.L489
	subl	$1, -4(%rbp)
	jmp	.L489
.L488:
	movl	$0, -8(%rbp)
.L489:
	addl	$1, -4(%rbp)
.L483:
	cmpl	$253, -4(%rbp)
	jle	.L490
	nop
.L485:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE50:
	.size	readLine, .-readLine
	.section	.rodata
.LC105:
	.string	"pattern: %p\n"
.LC106:
	.string	"bulge: %f\n"
.LC107:
	.string	"%c\n"
.LC108:
	.string	"%f %f %f\n"
.LC109:
	.string	"HEADER"
.LC110:
	.string	"CLASSES"
.LC111:
	.string	"TABLES"
.LC112:
	.string	"BLOCKS"
.LC113:
	.string	"ENTITIES"
.LC114:
	.string	"OBJECTS"
.LC115:
	.string	"THUMBNAILIMAGE"
.LC116:
	.string	"SECTION:%s\n"
.LC117:
	.string	"ENDSEC"
.LC118:
	.string	"ENDSEC:%s\n"
.LC119:
	.string	"ARC"
.LC120:
	.string	"CIRCLE"
.LC121:
	.string	"ELLIPSE"
.LC122:
	.string	"LINE"
.LC123:
	.string	"LWPOLYLINE"
.LC124:
	.string	"POINT"
.LC125:
	.string	"EOF"
.LC126:
	.string	"$ACADVER"
.LC127:
	.string	"AC1006"
.LC128:
	.string	"AC1009"
.LC129:
	.string	"AC1012"
.LC130:
	.string	"ENDTAB"
.LC131:
	.string	"2"
.LC132:
	.string	"LAYER"
.LC133:
	.string	"5"
.LC134:
	.string	"330"
.LC135:
	.string	"100"
.LC136:
	.string	"70"
.LC137:
	.string	"62"
.LC138:
	.string	"inserting:%s,%d,%d,%d\n"
.LC139:
	.string	"8"
.LC140:
	.string	"90"
.LC141:
	.string	"40"
.LC142:
	.string	"41"
.LC143:
	.string	"43"
.LC144:
	.string	"42"
.LC145:
	.string	"bulgeFlag %d\n"
.LC146:
	.string	"10"
.LC147:
	.string	"20"
.LC148:
	.string	"0"
	.align 8
.LC149:
	.string	"ERROR: format-dxf.c readDxf(), missing EOF at end of DXF file"
	.text
	.globl	readDxf
	.type	readDxf, @function
readDxf:
.LFB51:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$1312, %rsp
	movq	%rdi, -1304(%rbp)
	movq	%rsi, -1312(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L492
	movq	-1304(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC105(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L492:
	movl	$0, -4(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L493
	pxor	%xmm3, %xmm3
	cvtss2sd	-8(%rbp), %xmm3
	movq	%xmm3, %rax
	movq	%rax, %xmm0
	leaq	.LC106(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
.L493:
	movb	$1, -9(%rbp)
	movsbl	-9(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC107(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movb	$0, -10(%rbp)
	movl	$0, -16(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -1288(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -1284(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -1280(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -1276(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -1272(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -1268(%rbp)
	movss	-1288(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-1280(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-1272(%rbp), %xmm2
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm2, %xmm4
	movq	%xmm4, %rax
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC108(%rip), %rax
	movq	%rax, %rdi
	movl	$3, %eax
	call	printf@PLT
	movq	-1312(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-1312(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -16(%rbp)
	movq	-1312(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L494
.L523:
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	leaq	-1264(%rbp), %rax
	leaq	.LC109(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L495
	leaq	-1264(%rbp), %rax
	leaq	.LC110(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L495
	leaq	-1264(%rbp), %rax
	leaq	.LC111(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L495
	leaq	-1264(%rbp), %rax
	leaq	.LC112(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L495
	leaq	-1264(%rbp), %rax
	leaq	.LC113(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L495
	leaq	-1264(%rbp), %rax
	leaq	.LC114(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L495
	leaq	-1264(%rbp), %rax
	leaq	.LC115(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L496
.L495:
	leaq	-1264(%rbp), %rdx
	leaq	-432(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy@PLT
	leaq	-1264(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC116(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L496:
	leaq	-1264(%rbp), %rax
	leaq	.LC117(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L497
	movb	$0, -432(%rbp)
	leaq	-1264(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC118(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L497:
	leaq	-1264(%rbp), %rax
	leaq	.LC119(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L498
	leaq	-1264(%rbp), %rax
	leaq	.LC120(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L498
	leaq	-1264(%rbp), %rax
	leaq	.LC121(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L498
	leaq	-1264(%rbp), %rax
	leaq	.LC122(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L498
	leaq	-1264(%rbp), %rax
	leaq	.LC123(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L498
	leaq	-1264(%rbp), %rax
	leaq	.LC124(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L499
.L498:
	leaq	-1264(%rbp), %rdx
	leaq	-1056(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy@PLT
.L499:
	leaq	-1264(%rbp), %rax
	leaq	.LC125(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L500
	movl	$1, -4(%rbp)
.L500:
	leaq	-432(%rbp), %rax
	leaq	.LC109(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L501
	leaq	-1264(%rbp), %rax
	leaq	.LC126(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L494
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	leaq	-224(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	leaq	-224(%rbp), %rax
	leaq	.LC127(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L502
	leaq	-224(%rbp), %rax
	leaq	.LC128(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L502
	leaq	-224(%rbp), %rax
	leaq	.LC128(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L502
	leaq	-224(%rbp), %rax
	leaq	.LC129(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L494
.L502:
	movl	$0, %eax
	jmp	.L525
.L501:
	leaq	-432(%rbp), %rax
	leaq	.LC111(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L504
	leaq	-1264(%rbp), %rax
	leaq	.LC130(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L505
	movb	$0, -640(%rbp)
.L505:
	movzbl	-640(%rbp), %eax
	testb	%al, %al
	jne	.L506
	leaq	-1264(%rbp), %rax
	leaq	.LC131(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L494
	leaq	-640(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L506:
	leaq	-640(%rbp), %rax
	leaq	.LC132(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L494
	leaq	-1264(%rbp), %rax
	leaq	.LC133(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L507
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L507:
	leaq	-1264(%rbp), %rax
	leaq	.LC134(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L508
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L508:
	leaq	-1264(%rbp), %rax
	leaq	.LC135(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L509
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L509:
	leaq	-1264(%rbp), %rax
	leaq	.LC136(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L510
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L510:
	leaq	-1264(%rbp), %rax
	leaq	.LC131(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L511
	leaq	-848(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L511:
	leaq	-1264(%rbp), %rax
	leaq	.LC137(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L494
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	leaq	-1264(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movb	%al, -17(%rbp)
	leaq	-1264(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movb	%al, -17(%rbp)
	movzbl	-17(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	leaq	dxf_colors(%rip), %rdx
	movzwl	(%rax,%rdx), %ecx
	movw	%cx, -1291(%rbp)
	movzbl	2(%rax,%rdx), %eax
	movb	%al, -1289(%rbp)
	movzbl	-1289(%rbp), %eax
	movzbl	%al, %esi
	movzbl	-1290(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-1291(%rbp), %eax
	movzbl	%al, %edx
	leaq	-848(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	leaq	.LC138(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movb	$0, -848(%rbp)
	jmp	.L494
.L504:
	leaq	-432(%rbp), %rax
	leaq	.LC113(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L494
	leaq	-1264(%rbp), %rax
	leaq	.LC133(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L512
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L512:
	leaq	-1264(%rbp), %rax
	leaq	.LC134(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L513
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L513:
	leaq	-1264(%rbp), %rax
	leaq	.LC135(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L514
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L514:
	leaq	-1264(%rbp), %rax
	leaq	.LC139(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L515
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L515:
	leaq	-1056(%rbp), %rax
	leaq	.LC123(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L494
	leaq	-1264(%rbp), %rax
	leaq	.LC140(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L516
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L516:
	leaq	-1264(%rbp), %rax
	leaq	.LC136(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L517
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L517:
	leaq	-1264(%rbp), %rax
	leaq	.LC141(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L518
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L518:
	leaq	-1264(%rbp), %rax
	leaq	.LC142(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L519
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L519:
	leaq	-1264(%rbp), %rax
	leaq	.LC143(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L520
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	jmp	.L494
.L520:
	leaq	-1264(%rbp), %rax
	leaq	.LC144(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L521
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	leaq	-1264(%rbp), %rax
	movq	%rax, %rdi
	call	atof@PLT
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	movb	$1, -10(%rbp)
	movsbl	-10(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC145(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L494
.L521:
	leaq	-1264(%rbp), %rax
	leaq	.LC146(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L522
	leaq	-1264(%rbp), %rdx
	movq	-1312(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readLine
	leaq	-1264(%rbp), %rax
	movq	%rax, %rdi
	call	atof@PLT
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -1280(%rbp)
	jmp	.L494
.L522:
	leaq	-1264(%rbp), %rax
	leaq	.LC147(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L494
	leaq	-1264(%rbp), %rax
	leaq	.LC148(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
.L494:
	movq	-1312(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rdx
	movl	-16(%rbp), %eax
	cltq
	cmpq	%rax, %rdx
	jl	.L523
	cmpl	$0, -4(%rbp)
	jne	.L524
	leaq	.LC149(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L524:
	movl	-4(%rbp), %eax
.L525:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE51:
	.size	readDxf, .-readDxf
	.section	.rodata
	.align 8
.LC150:
	.string	"ERROR: writeDxf not implemented."
.LC151:
	.string	"Called with %p %p\n"
	.text
	.globl	writeDxf
	.type	writeDxf, @function
writeDxf:
.LFB52:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC150(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L527
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC151(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L527:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE52:
	.size	writeDxf, .-writeDxf
	.globl	readEdr
	.type	readEdr, @function
readEdr:
.LFB53:
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
	call	readRgb
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE53:
	.size	readEdr, .-readEdr
	.globl	writeEdr
	.type	writeEdr, @function
writeEdr:
.LFB54:
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
	call	writeRgb
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE54:
	.size	writeEdr, .-writeEdr
	.globl	emdDecode
	.type	emdDecode, @function
emdDecode:
.LFB55:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	testb	%al, %al
	jns	.L534
	movzbl	-4(%rbp), %eax
	jmp	.L535
.L534:
	movzbl	-4(%rbp), %eax
.L535:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE55:
	.size	emdDecode, .-emdDecode
	.section	.rodata
	.align 8
.LC152:
	.string	"File invalid: shorter than the header."
	.align 8
.LC153:
	.string	"ERROR: Failed to read 6 bytes for jemd0"
.LC154:
	.string	"%d %d %d\n"
	.align 8
.LC155:
	.string	"ERROR: Failed to read 2 bytes for stitch."
	.text
	.globl	readEmd
	.type	readEmd, @function
readEmd:
.LFB56:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -8(%rbp)
	cmpl	$47, -8(%rbp)
	jg	.L537
	leaq	.LC152(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L549
.L537:
	movq	-48(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-48(%rbp), %rdx
	leaq	-30(%rbp), %rax
	movq	%rdx, %rcx
	movl	$6, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$6, %rax
	je	.L539
	leaq	.LC153(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L549
.L539:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -12(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -16(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %ecx
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC154(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-48(%rbp), %rax
	movl	$0, %edx
	movl	$48, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L540
.L548:
	movl	$0, -4(%rbp)
	movq	-48(%rbp), %rdx
	leaq	-24(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	je	.L541
	leaq	.LC155(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L549
.L541:
	movzbl	-24(%rbp), %eax
	cmpb	$-128, %al
	jne	.L542
	movzbl	-23(%rbp), %eax
	cmpb	$42, %al
	jne	.L543
	movq	-40(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L540
.L543:
	movzbl	-23(%rbp), %eax
	cmpb	$-128, %al
	jne	.L544
	movq	-48(%rbp), %rdx
	leaq	-24(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	je	.L545
	leaq	.LC155(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L549
.L545:
	movl	$2, -4(%rbp)
	jmp	.L542
.L544:
	movzbl	-23(%rbp), %eax
	cmpb	$-3, %al
	jne	.L540
	movq	-40(%rbp), %rax
	movl	$1, %edx
	movl	$16, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L547
.L542:
	movzbl	-24(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	emdDecode
	movb	%al, -21(%rbp)
	movzbl	-23(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	emdDecode
	movb	%al, -22(%rbp)
	movsbl	-22(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movss	.LC18(%rip), %xmm1
	movaps	%xmm0, %xmm2
	divss	%xmm1, %xmm2
	movsbl	-21(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movss	.LC18(%rip), %xmm1
	divss	%xmm1, %xmm0
	movd	%xmm0, %ecx
	movl	-4(%rbp), %esi
	movq	-40(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L540:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	je	.L548
.L547:
	movl	$1, %eax
.L549:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE56:
	.size	readEmd, .-readEmd
	.section	.rodata
.LC156:
	.string	"writeEmd not implemented."
	.text
	.globl	writeEmd
	.type	writeEmd, @function
writeEmd:
.LFB57:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC156(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L551
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC151(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L551:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE57:
	.size	writeEmd, .-writeEmd
	.globl	expDecode
	.type	expDecode, @function
expDecode:
.LFB58:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE58:
	.size	expDecode, .-expDecode
	.globl	readExp
	.type	readExp, @function
readExp:
.LFB59:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	jmp	.L556
.L564:
	movb	$0, -5(%rbp)
	movb	$0, -6(%rbp)
	movl	$0, -4(%rbp)
	movzbl	-8(%rbp), %eax
	cmpb	$-128, %al
	jne	.L557
	movzbl	-7(%rbp), %eax
	cmpb	$1, %al
	jne	.L558
	movq	-32(%rbp), %rdx
	leaq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	jne	.L566
	movl	$4, -4(%rbp)
	jmp	.L557
.L558:
	movzbl	-7(%rbp), %eax
	cmpb	$4, %al
	jne	.L561
	movq	-32(%rbp), %rdx
	leaq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	jne	.L567
	movl	$1, -4(%rbp)
	jmp	.L557
.L561:
	movzbl	-7(%rbp), %eax
	cmpb	$-128, %al
	jne	.L557
	movq	-32(%rbp), %rdx
	leaq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	jne	.L568
	movl	$2, -4(%rbp)
.L557:
	movzbl	-8(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	expDecode
	movb	%al, -5(%rbp)
	movzbl	-7(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	expDecode
	movb	%al, -6(%rbp)
	movsbl	-6(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movsbl	-5(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-4(%rbp), %esi
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L556:
	movq	-32(%rbp), %rdx
	leaq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	je	.L564
	jmp	.L560
.L566:
	nop
	jmp	.L560
.L567:
	nop
	jmp	.L560
.L568:
	nop
.L560:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE59:
	.size	readExp, .-readExp
	.globl	writeExp
	.type	writeExp, @function
writeExp:
.LFB60:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L570
.L576:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movss	-44(%rbp), %xmm0
	movss	-16(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movb	%al, -5(%rbp)
	movss	-40(%rbp), %xmm0
	movss	-12(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movb	%al, -6(%rbp)
	movss	-16(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsbl	-5(%rbp), %eax
	pxor	%xmm2, %xmm2
	cvtsi2sdl	%eax, %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	movss	-12(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsbl	-6(%rbp), %eax
	pxor	%xmm2, %xmm2
	cvtsi2sdl	%eax, %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	movl	-48(%rbp), %eax
	cmpl	$4, %eax
	je	.L571
	cmpl	$4, %eax
	jg	.L572
	cmpl	$1, %eax
	je	.L573
	cmpl	$2, %eax
	je	.L574
	jmp	.L572
.L571:
	movb	$-128, -20(%rbp)
	movb	$1, -19(%rbp)
	movb	$0, -18(%rbp)
	movb	$0, -17(%rbp)
	movq	-64(%rbp), %rdx
	leaq	-20(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L575
.L573:
	movb	$-128, -20(%rbp)
	movb	$4, -19(%rbp)
	movzbl	-5(%rbp), %eax
	movb	%al, -18(%rbp)
	movzbl	-6(%rbp), %eax
	movb	%al, -17(%rbp)
	movq	-64(%rbp), %rdx
	leaq	-20(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L575
.L574:
	movb	$-128, -20(%rbp)
	movb	$-128, -19(%rbp)
	movb	$7, -18(%rbp)
	movb	$0, -17(%rbp)
	movq	-64(%rbp), %rdx
	leaq	-20(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L575
.L572:
	movzbl	-5(%rbp), %eax
	movb	%al, -20(%rbp)
	movzbl	-6(%rbp), %eax
	movb	%al, -19(%rbp)
	movq	-64(%rbp), %rdx
	leaq	-20(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	nop
.L575:
	addl	$1, -4(%rbp)
.L570:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L576
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	movl	$26, %edi
	call	fputc@PLT
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE60:
	.size	writeExp, .-writeExp
	.globl	decode_exy_flags
	.type	decode_exy_flags, @function
decode_exy_flags:
.LFB61:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -20(%rbp)
	movl	$0, -4(%rbp)
	cmpb	$-13, -20(%rbp)
	jne	.L579
	movl	$16, %eax
	jmp	.L580
.L579:
	movzbl	-20(%rbp), %eax
	andl	$195, %eax
	cmpl	$195, %eax
	jne	.L581
	movl	$6, %eax
	jmp	.L580
.L581:
	movzbl	-20(%rbp), %eax
	testb	%al, %al
	jns	.L582
	orl	$2, -4(%rbp)
.L582:
	movzbl	-20(%rbp), %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L583
	orl	$4, -4(%rbp)
.L583:
	movl	-4(%rbp), %eax
.L580:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE61:
	.size	decode_exy_flags, .-decode_exy_flags
	.globl	readExy
	.type	readExy, @function
readExy:
.LFB62:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movl	$0, %edx
	movl	$256, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L585
.L588:
	leaq	-16(%rbp), %rdx
	leaq	-12(%rbp), %rcx
	leaq	-7(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	decode_tajima_ternary@PLT
	movzbl	-5(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	decode_exy_flags
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L586
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movl	$16, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L587
.L586:
	movl	-16(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movl	-12(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-4(%rbp), %esi
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L585:
	movq	-32(%rbp), %rdx
	leaq	-7(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L588
.L587:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE62:
	.size	readExy, .-readExy
	.section	.rodata
	.align 8
.LC157:
	.string	"ERROR: writeExy has not been finished."
.LC158:
	.string	"file: %p\n"
	.text
	.globl	writeExy
	.type	writeExy, @function
writeExy:
.LFB63:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC157(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L591
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC105(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L591:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L592
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC158(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L592:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE63:
	.size	writeExy, .-writeExy
	.section	.rodata
	.align 8
.LC159:
	.string	"ERROR: readEys and not been finished."
	.text
	.globl	readEys
	.type	readEys, @function
readEys:
.LFB64:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC159(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L595
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC105(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L595:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L596
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC158(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L596:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE64:
	.size	readEys, .-readEys
	.section	.rodata
	.align 8
.LC160:
	.string	"ERROR: writeEys and not been finished."
	.text
	.globl	writeEys
	.type	writeEys, @function
writeEys:
.LFB65:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC160(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L599
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC105(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L599:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L600
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC158(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L600:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE65:
	.size	writeEys, .-writeEys
	.globl	readFxy
	.type	readFxy, @function
readFxy:
.LFB66:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movl	$0, %edx
	movl	$256, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L603
.L610:
	movl	$0, -4(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -8(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -12(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -13(%rbp)
	cmpb	$-111, -13(%rbp)
	jne	.L604
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movl	$16, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L605
.L604:
	movzbl	-13(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L606
	movl	$2, -4(%rbp)
.L606:
	movzbl	-13(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L607
	movl	$4, -4(%rbp)
.L607:
	movzbl	-13(%rbp), %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L608
	negl	-8(%rbp)
.L608:
	movzbl	-13(%rbp), %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L609
	negl	-12(%rbp)
.L609:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-8(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-12(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-4(%rbp), %esi
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L603:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	je	.L610
.L605:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE66:
	.size	readFxy, .-readFxy
	.section	.rodata
.LC161:
	.string	"%p %p\n"
	.text
	.globl	writeFxy
	.type	writeFxy, @function
writeFxy:
.LFB67:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC42(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC161(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE67:
	.size	writeFxy, .-writeFxy
	.section	.rodata
	.align 8
.LC162:
	.string	"ERROR: readGc and not been finished."
	.text
	.globl	readGc
	.type	readGc, @function
readGc:
.LFB68:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC162(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC161(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE68:
	.size	readGc, .-readGc
	.section	.rodata
	.align 8
.LC163:
	.string	"ERROR: writeGc and not been finished."
	.text
	.globl	writeGc
	.type	writeGc, @function
writeGc:
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
	leaq	.LC163(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC161(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE69:
	.size	writeGc, .-writeGc
	.section	.rodata
	.align 8
.LC164:
	.string	"ERROR: readGnc and not been finished."
	.text
	.globl	readGnc
	.type	readGnc, @function
readGnc:
.LFB70:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC164(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC161(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE70:
	.size	readGnc, .-readGnc
	.section	.rodata
	.align 8
.LC165:
	.string	"ERROR: writeGnc and not been finished."
	.text
	.globl	writeGnc
	.type	writeGnc, @function
writeGnc:
.LFB71:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC165(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC161(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE71:
	.size	writeGnc, .-writeGnc
	.globl	readGt
	.type	readGt, @function
readGt:
.LFB72:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movl	$0, %edx
	movl	$512, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L623
.L630:
	movl	$0, -4(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -8(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -12(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -13(%rbp)
	cmpb	$-111, -13(%rbp)
	jne	.L624
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movl	$16, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L625
.L624:
	movzbl	-13(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L626
	movl	$2, -4(%rbp)
.L626:
	movzbl	-13(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L627
	movl	$4, -4(%rbp)
.L627:
	movzbl	-13(%rbp), %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L628
	negl	-8(%rbp)
.L628:
	movzbl	-13(%rbp), %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L629
	negl	-12(%rbp)
.L629:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-8(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-12(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-4(%rbp), %esi
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L623:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	je	.L630
.L625:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE72:
	.size	readGt, .-readGt
	.section	.rodata
	.align 8
.LC166:
	.string	"ERROR: gt not supported in write mode."
	.text
	.globl	writeGt
	.type	writeGt, @function
writeGt:
.LFB73:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC166(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC161(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE73:
	.size	writeGt, .-writeGt
	.globl	husDecodeStitchType
	.type	husDecodeStitchType, @function
husDecodeStitchType:
.LFB74:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	cmpl	$144, %eax
	je	.L635
	cmpl	$144, %eax
	jg	.L636
	cmpl	$132, %eax
	je	.L637
	cmpl	$132, %eax
	jg	.L636
	cmpl	$128, %eax
	je	.L638
	cmpl	$129, %eax
	je	.L639
	jmp	.L636
.L638:
	movl	$0, %eax
	jmp	.L640
.L639:
	movl	$1, %eax
	jmp	.L640
.L637:
	movl	$4, %eax
	jmp	.L640
.L635:
	movl	$16, %eax
	jmp	.L640
.L636:
	movl	$0, %eax
.L640:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE74:
	.size	husDecodeStitchType, .-husDecodeStitchType
	.section	.rodata
	.align 8
.LC167:
	.string	"ERROR: husDecompressData(), cannot allocate memory for decompressedData"
	.text
	.globl	husDecompressData
	.type	husDecompressData, @function
husDecompressData:
.LFB75:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	-32(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L642
	leaq	.LC167(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L643
.L642:
	leaq	-32(%rbp), %rcx
	movq	-8(%rbp), %rdx
	movl	-28(%rbp), %esi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	hus_decompress@PLT
	movq	-8(%rbp), %rax
.L643:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE75:
	.size	husDecompressData, .-husDecompressData
	.section	.rodata
	.align 8
.LC168:
	.string	"ERROR: husCompressData(), cannot allocate memory for compressedData"
	.text
	.globl	husCompressData
	.type	husCompressData, @function
husCompressData:
.LFB76:
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
	movl	-28(%rbp), %eax
	cltq
	addq	%rax, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L645
	leaq	.LC168(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L646
.L645:
	movq	-40(%rbp), %rcx
	movq	-8(%rbp), %rdx
	movl	-28(%rbp), %esi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	hus_compress@PLT
	movq	-8(%rbp), %rax
.L646:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE76:
	.size	husCompressData, .-husCompressData
	.globl	husDecodeByte
	.type	husDecodeByte, @function
husDecodeByte:
.LFB77:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	movsbl	%al, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE77:
	.size	husDecodeByte, .-husDecodeByte
	.globl	husEncodeByte
	.type	husEncodeByte, @function
husEncodeByte:
.LFB78:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movss	%xmm0, -4(%rbp)
	movl	-4(%rbp), %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE78:
	.size	husEncodeByte, .-husEncodeByte
	.globl	husEncodeStitchType
	.type	husEncodeStitchType, @function
husEncodeStitchType:
.LFB79:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	cmpl	$16, -4(%rbp)
	je	.L652
	cmpl	$16, -4(%rbp)
	jg	.L653
	cmpl	$4, -4(%rbp)
	je	.L654
	cmpl	$4, -4(%rbp)
	jg	.L653
	cmpl	$0, -4(%rbp)
	je	.L655
	cmpl	$0, -4(%rbp)
	js	.L653
	movl	-4(%rbp), %eax
	subl	$1, %eax
	cmpl	$1, %eax
	ja	.L653
	jmp	.L658
.L655:
	movl	$-128, %eax
	jmp	.L657
.L658:
	movl	$-127, %eax
	jmp	.L657
.L654:
	movl	$-124, %eax
	jmp	.L657
.L652:
	movl	$-112, %eax
	jmp	.L657
.L653:
	movl	$-128, %eax
.L657:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE79:
	.size	husEncodeStitchType, .-husEncodeStitchType
	.section	.rodata
.LC169:
	.string	"magicCode: %d\n"
.LC170:
	.string	"numberOfStitches: %d\n"
.LC171:
	.string	"numberOfColors: %d\n"
.LC172:
	.string	"positiveXHoopSize: %d\n"
.LC173:
	.string	"positiveYHoopSize: %d\n"
.LC174:
	.string	"negativeXHoopSize: %d\n"
.LC175:
	.string	"negativeYHoopSize: %d\n"
.LC176:
	.string	"attributeOffset: %d\n"
.LC177:
	.string	"xOffset: %d\n"
.LC178:
	.string	"yOffset: %d\n"
	.align 8
.LC179:
	.string	"ERROR: format-hus.c readHus(), cannot allocate memory for stringVal"
	.align 8
.LC180:
	.string	"Ran out of bytes before full file read."
.LC181:
	.string	"unknown: %d\n"
	.align 8
.LC182:
	.string	"ERROR: format-hus.c readHus(), cannot allocate memory for attributeData"
	.align 8
.LC183:
	.string	"ERROR: format-hus.c readHus(), cannot allocate memory for xData"
	.align 8
.LC184:
	.string	"ERROR: format-hus.c readHus(), cannot allocate memory for yData"
	.text
	.globl	readHus
	.type	readHus, @function
readHus:
.LFB80:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$160, %rsp
	movq	%rdi, -152(%rbp)
	movq	%rsi, -160(%rbp)
	movq	$0, -16(%rbp)
	movq	$0, -24(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -40(%rbp)
	movl	$0, -4(%rbp)
	movq	-160(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -44(%rbp)
	movq	-160(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -48(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -52(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -56(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -60(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -64(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -68(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -72(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -76(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -80(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -84(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L660
	movl	-48(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC169(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L660:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L661
	movl	-52(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC170(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L661:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L662
	movl	-56(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC171(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L662:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L663
	movl	-60(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC172(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L663:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L664
	movl	-64(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC173(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L664:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L665
	movl	-68(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC174(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L665:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L666
	movl	-72(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC175(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L666:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L667
	movl	-76(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC176(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L667:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L668
	movl	-80(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC177(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L668:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L669
	movl	-84(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC178(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L669:
	movl	$8, %edi
	call	malloc@PLT
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L670
	leaq	.LC179(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L671
.L670:
	movq	$8, -96(%rbp)
	movq	-160(%rbp), %rcx
	movq	-96(%rbp), %rdx
	movq	-40(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	%rax, -96(%rbp)
	je	.L672
	leaq	.LC180(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L671
.L672:
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -100(%rbp)
	movl	-100(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC181(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, -4(%rbp)
	jmp	.L673
.L674:
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -134(%rbp)
	movswl	-134(%rbp), %eax
	movq	-152(%rbp), %r8
	subq	$8, %rsp
	cltq
	imulq	$403, %rax, %rax
	leaq	hus_colors(%rip), %rcx
	subq	$408, %rsp
	movq	%rsp, %rdx
	addq	%rcx, %rax
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
	addl	$1, -4(%rbp)
.L673:
	movl	-4(%rbp), %eax
	cmpl	-56(%rbp), %eax
	jl	.L674
	movl	-80(%rbp), %eax
	subl	-76(%rbp), %eax
	addl	$1, %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -112(%rbp)
	cmpq	$0, -112(%rbp)
	jne	.L675
	leaq	.LC182(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L671
.L675:
	movl	-80(%rbp), %eax
	subl	-76(%rbp), %eax
	cltq
	movq	%rax, -96(%rbp)
	movq	-160(%rbp), %rcx
	movq	-96(%rbp), %rdx
	movq	-112(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	%rax, -96(%rbp)
	je	.L676
	leaq	.LC180(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L671
.L676:
	movl	-52(%rbp), %eax
	leal	1(%rax), %edx
	movq	-96(%rbp), %rax
	movl	%eax, %ecx
	movq	-112(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	husDecompressData
	movq	%rax, -16(%rbp)
	movl	-84(%rbp), %eax
	subl	-80(%rbp), %eax
	addl	$1, %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -120(%rbp)
	cmpq	$0, -120(%rbp)
	jne	.L677
	leaq	.LC183(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L671
.L677:
	movl	-84(%rbp), %eax
	subl	-80(%rbp), %eax
	cltq
	movq	%rax, -96(%rbp)
	movq	-160(%rbp), %rcx
	movq	-96(%rbp), %rdx
	movq	-120(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	%rax, -96(%rbp)
	je	.L678
	leaq	.LC180(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L671
.L678:
	movq	-96(%rbp), %rax
	movl	%eax, %ecx
	movl	-52(%rbp), %edx
	movq	-120(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	husDecompressData
	movq	%rax, -24(%rbp)
	movl	-44(%rbp), %eax
	subl	-84(%rbp), %eax
	addl	$1, %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -128(%rbp)
	cmpq	$0, -128(%rbp)
	jne	.L679
	leaq	.LC184(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L671
.L679:
	movl	-44(%rbp), %eax
	subl	-84(%rbp), %eax
	cltq
	movq	%rax, -96(%rbp)
	movq	-160(%rbp), %rcx
	movq	-96(%rbp), %rdx
	movq	-128(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	%rax, -96(%rbp)
	je	.L680
	leaq	.LC180(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L671
.L680:
	movq	-96(%rbp), %rax
	movl	%eax, %ecx
	movl	-52(%rbp), %edx
	movq	-128(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	husDecompressData
	movq	%rax, -32(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L681
.L682:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	husDecodeByte
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -144(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	husDecodeByte
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -140(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	husDecodeStitchType
	movl	%eax, -132(%rbp)
	movss	-140(%rbp), %xmm0
	movl	-144(%rbp), %ecx
	movl	-132(%rbp), %esi
	movq	-152(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	addl	$1, -4(%rbp)
.L681:
	movl	-4(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	.L682
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movl	$1, %eax
.L671:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE80:
	.size	readHus, .-readHus
	.section	.rodata
	.align 8
.LC185:
	.string	"ERROR: format-hus.c writeHus(), cannot allocate memory for xValues"
	.align 8
.LC186:
	.string	"ERROR: format-hus.c writeHus(), cannot allocate memory for yValues"
	.align 8
.LC187:
	.string	"ERROR: format-hus.c writeHus(), cannot allocate memory for attributeValues"
	.text
	.globl	writeHus
	.type	writeHus, @function
writeHus:
.LFB81:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$184, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -184(%rbp)
	movq	%rsi, -192(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -48(%rbp)
	movq	$0, -56(%rbp)
	movq	$0, -64(%rbp)
	movq	$0, -72(%rbp)
	movq	$0, -80(%rbp)
	movq	-184(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, -84(%rbp)
	movq	-184(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -88(%rbp)
	cmpl	$24, -20(%rbp)
	jle	.L684
	movl	$24, -20(%rbp)
.L684:
	movl	$13152091, -92(%rbp)
	movl	-92(%rbp), %edx
	movq	-192(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-84(%rbp), %edx
	movq	-192(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-20(%rbp), %edx
	movq	-192(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	leaq	-144(%rbp), %rax
	movq	-184(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_bounds@PLT
	movss	-136(%rbp), %xmm1
	movss	-144(%rbp), %xmm0
	addss	%xmm0, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movw	%ax, -94(%rbp)
	movss	-140(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	negl	%eax
	movw	%ax, -96(%rbp)
	movss	-144(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movw	%ax, -98(%rbp)
	movss	-132(%rbp), %xmm1
	movss	-140(%rbp), %xmm0
	addss	%xmm0, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	negl	%eax
	movw	%ax, -100(%rbp)
	movswl	-94(%rbp), %edx
	movq	-192(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movswl	-96(%rbp), %edx
	movq	-192(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movswl	-98(%rbp), %edx
	movq	-192(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movswl	-100(%rbp), %edx
	movq	-192(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movl	-20(%rbp), %eax
	addl	$21, %eax
	addl	%eax, %eax
	movl	%eax, -104(%rbp)
	movl	-104(%rbp), %edx
	movq	-192(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-84(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L685
	leaq	.LC185(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L693
.L685:
	movl	-84(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -48(%rbp)
	cmpq	$0, -48(%rbp)
	jne	.L687
	leaq	.LC186(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L693
.L687:
	movl	-84(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -56(%rbp)
	cmpq	$0, -56(%rbp)
	jne	.L688
	leaq	.LC187(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L693
.L688:
	pxor	%xmm0, %xmm0
	movss	%xmm0, -28(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -32(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L689
.L690:
	movq	-184(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -176(%rbp)
	movq	%rdx, -168(%rbp)
	movss	-172(%rbp), %xmm0
	movaps	%xmm0, %xmm1
	subss	-28(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movl	-24(%rbp), %edx
	movslq	%edx, %rcx
	movq	-40(%rbp), %rdx
	leaq	(%rcx,%rdx), %rbx
	movd	%eax, %xmm0
	call	husEncodeByte
	movb	%al, (%rbx)
	movss	-172(%rbp), %xmm0
	movss	%xmm0, -28(%rbp)
	movss	-168(%rbp), %xmm0
	subss	-32(%rbp), %xmm0
	movaps	%xmm0, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movl	-24(%rbp), %edx
	movslq	%edx, %rcx
	movq	-48(%rbp), %rdx
	leaq	(%rcx,%rdx), %rbx
	movd	%eax, %xmm0
	call	husEncodeByte
	movb	%al, (%rbx)
	movss	-168(%rbp), %xmm0
	movss	%xmm0, -32(%rbp)
	movl	-176(%rbp), %eax
	movl	-24(%rbp), %edx
	movslq	%edx, %rcx
	movq	-56(%rbp), %rdx
	leaq	(%rcx,%rdx), %rbx
	movl	%eax, %edi
	call	husEncodeStitchType
	movb	%al, (%rbx)
	addl	$1, -24(%rbp)
.L689:
	movq	-184(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -24(%rbp)
	jl	.L690
	leaq	-148(%rbp), %rdx
	movl	-84(%rbp), %ecx
	movq	-56(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	husCompressData
	movq	%rax, -64(%rbp)
	leaq	-152(%rbp), %rdx
	movl	-84(%rbp), %ecx
	movq	-40(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	husCompressData
	movq	%rax, -72(%rbp)
	leaq	-156(%rbp), %rdx
	movl	-84(%rbp), %ecx
	movq	-48(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	husCompressData
	movq	%rax, -80(%rbp)
	movl	-88(%rbp), %eax
	addl	$21, %eax
	leal	(%rax,%rax), %edx
	movl	-148(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -108(%rbp)
	movl	-88(%rbp), %eax
	addl	$21, %eax
	leal	(%rax,%rax), %edx
	movl	-148(%rbp), %eax
	addl	%eax, %edx
	movl	-152(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -112(%rbp)
	movl	-108(%rbp), %edx
	movq	-192(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-112(%rbp), %edx
	movq	-192(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-192(%rbp), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movl	$0, -24(%rbp)
	jmp	.L691
.L692:
	movq	-184(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-24(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movl	$29, %edx
	leaq	hus_colors(%rip), %rcx
	movq	%rcx, %rsi
	movzbl	(%rax), %ecx
	movzbl	1(%rax), %edi
	salq	$8, %rdi
	orq	%rdi, %rcx
	movzbl	2(%rax), %eax
	salq	$16, %rax
	orq	%rcx, %rax
	movq	%rax, %rdi
	call	emb_find_nearest_thread@PLT
	movw	%ax, -114(%rbp)
	movswl	-114(%rbp), %edx
	movq	-192(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	addl	$1, -24(%rbp)
.L691:
	movl	-24(%rbp), %eax
	cmpl	-88(%rbp), %eax
	jl	.L692
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	-192(%rbp), %rcx
	movq	-64(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	-152(%rbp), %eax
	movslq	%eax, %rdx
	movq	-192(%rbp), %rcx
	movq	-72(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	-156(%rbp), %eax
	movslq	%eax, %rdx
	movq	-192(%rbp), %rcx
	movq	-80(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movl	$1, %eax
.L693:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE81:
	.size	writeHus, .-writeHus
	.section	.rodata
	.align 8
.LC188:
	.string	"ERROR: failed to read single byte from file."
.LC189:
	.string	"nullVal: %d\n"
.LC190:
	.string	"stitchCount: %d\n"
.LC191:
	.string	"width: %d\n"
.LC192:
	.string	"height: %d\n"
.LC193:
	.string	"colorCount: %d\n"
.LC194:
	.string	"unknown3: %d\n"
.LC195:
	.string	"unknown2: %d\n"
.LC196:
	.string	"imageWidth: %d\n"
.LC197:
	.string	"imageHeight: %d\n"
.LC198:
	.string	"nullbyte: %d\n"
.LC199:
	.string	"left: %d\n"
.LC200:
	.string	"right: %d\n"
.LC201:
	.string	"top: %d\n"
.LC202:
	.string	"bottom: %d\n"
	.text
	.globl	readInb
	.type	readInb, @function
readInb:
.LFB82:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$384, %rsp
	movq	%rdi, -376(%rbp)
	movq	%rsi, -384(%rbp)
	movq	-384(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -20(%rbp)
	movq	-384(%rbp), %rdx
	leaq	-57(%rbp), %rax
	movq	%rdx, %rcx
	movl	$8, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-384(%rbp), %rdx
	leaq	-58(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L695
	leaq	.LC188(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L695:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L696
	movzbl	-58(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC189(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L696:
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -24(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L697
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC190(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L697:
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -26(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L698
	movswl	-26(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC191(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L698:
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -28(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L699
	movswl	-28(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC192(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L699:
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -30(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L700
	movswl	-30(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC193(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L700:
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -32(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L701
	movswl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC194(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L701:
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -34(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L702
	movswl	-34(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC195(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L702:
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -36(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L703
	movswl	-36(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC196(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L703:
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -38(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L704
	movswl	-38(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC197(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L704:
	movq	-384(%rbp), %rdx
	leaq	-368(%rbp), %rax
	movq	%rdx, %rcx
	movl	$300, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -40(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L705
	movswl	-40(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC198(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L705:
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -42(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L706
	movswl	-42(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC199(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L706:
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -44(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L707
	movswl	-44(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC200(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L707:
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -46(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L708
	movswl	-46(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC201(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L708:
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -48(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L709
	movswl	-48(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC202(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L709:
	movq	-384(%rbp), %rax
	movl	$0, %edx
	movl	$8192, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	-20(%rbp), %eax
	subl	$8192, %eax
	movslq	%eax, %rdx
	imulq	$1431655766, %rdx, %rdx
	movq	%rdx, %rcx
	shrq	$32, %rcx
	cltd
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, -24(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L710
.L715:
	movl	$0, -16(%rbp)
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movsbl	%al, %eax
	movl	%eax, -8(%rbp)
	movq	-384(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -49(%rbp)
	movzbl	-49(%rbp), %eax
	andl	$64, %eax
	testl	%eax, %eax
	jle	.L711
	negl	-4(%rbp)
.L711:
	movzbl	-49(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	jle	.L712
	negl	-8(%rbp)
.L712:
	movzbl	-49(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	jle	.L713
	movl	$4, -16(%rbp)
.L713:
	movzbl	-49(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	jle	.L714
	movl	$2, -16(%rbp)
.L714:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-8(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-4(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-16(%rbp), %esi
	movq	-376(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	addl	$1, -12(%rbp)
.L710:
	movl	-12(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L715
	movq	-376(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE82:
	.size	readInb, .-readInb
	.section	.rodata
	.align 8
.LC203:
	.string	"ERROR: writeInb not implemented."
	.text
	.globl	writeInb
	.type	writeInb, @function
writeInb:
.LFB83:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC203(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L718
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC105(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L718:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L719
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC158(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L719:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE83:
	.size	writeInb, .-writeInb
	.globl	readInf
	.type	readInf, @function
readInf:
.LFB84:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$560, %rsp
	movq	%rdi, -552(%rbp)
	movq	%rsi, -560(%rbp)
	movq	-560(%rbp), %rax
	movl	$1, %edx
	movl	$12, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-560(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -8(%rbp)
	movq	-552(%rbp), %rax
	movq	24(%rax), %rax
	movl	$0, 24(%rax)
	movl	$0, -4(%rbp)
	jmp	.L722
.L723:
	movq	-560(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	leaq	-544(%rbp), %rcx
	movq	-560(%rbp), %rax
	movl	$3, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_read@PLT
	movb	$0, -341(%rbp)
	movb	$0, -541(%rbp)
	movq	-552(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-544(%rbp), %rax
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
	movq	-560(%rbp), %rax
	movl	$1, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	leaq	-64(%rbp), %rcx
	movq	-560(%rbp), %rax
	movl	$50, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	binaryReadString@PLT
	leaq	-128(%rbp), %rcx
	movq	-560(%rbp), %rax
	movl	$50, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	binaryReadString@PLT
	addl	$1, -4(%rbp)
.L722:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L723
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE84:
	.size	readInf, .-readInf
	.section	.rodata
.LC204:
	.string	"RGB(%d,%d,%d)"
.LC205:
	.string	"RGB"
	.string	""
.LC206:
	.string	""
	.string	""
	.text
	.globl	writeInf
	.type	writeInf, @function
writeInf:
.LFB85:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$240, %rsp
	movq	%rdi, -232(%rbp)
	movq	%rsi, -240(%rbp)
	movq	-240(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	emb_write_u32be@PLT
	movq	-240(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	emb_write_u32be@PLT
	movq	-240(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_u32be@PLT
	movq	-232(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, %edx
	movq	-240(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u32be@PLT
	movl	$0, -4(%rbp)
	jmp	.L726
.L727:
	movq	-232(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -17(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -15(%rbp)
	movzbl	-15(%rbp), %eax
	movzbl	%al, %esi
	movzbl	-16(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-17(%rbp), %eax
	movzbl	%al, %edx
	leaq	-224(%rbp), %rax
	movl	%esi, %r8d
	leaq	.LC204(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	addl	$14, %eax
	movw	%ax, -10(%rbp)
	movl	-4(%rbp), %eax
	movw	%ax, -12(%rbp)
	movl	-4(%rbp), %eax
	movw	%ax, -14(%rbp)
	movzwl	-10(%rbp), %eax
	movswl	%ax, %edx
	movq	-240(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16be@PLT
	movzwl	-12(%rbp), %eax
	movswl	%ax, %edx
	movq	-240(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16be@PLT
	movq	-240(%rbp), %rax
	movl	$3, %edx
	movzbl	-17(%rbp), %ecx
	movzbl	-16(%rbp), %esi
	salq	$8, %rsi
	orq	%rcx, %rsi
	movzbl	-15(%rbp), %ecx
	salq	$16, %rcx
	orq	%rsi, %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_write@PLT
	movzwl	-14(%rbp), %eax
	movswl	%ax, %edx
	movq	-240(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16be@PLT
	movq	-240(%rbp), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	leaq	.LC205(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-240(%rbp), %rdx
	leaq	-224(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fputs@PLT
	movq	-240(%rbp), %rax
	movq	%rax, %rcx
	movl	$1, %edx
	movl	$1, %esi
	leaq	.LC206(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	addl	$1, -4(%rbp)
.L726:
	movq	-232(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L727
	movq	-240(%rbp), %rax
	movl	$8, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-240(%rbp), %rax
	movl	$2, %edx
	movq	$-8, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-240(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -8(%rbp)
	movq	-240(%rbp), %rax
	movl	$0, %edx
	movl	$8, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	-8(%rbp), %edx
	movq	-240(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u32be@PLT
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE85:
	.size	writeInf, .-writeInf
	.globl	jefGetHoopSize
	.type	jefGetHoopSize, @function
jefGetHoopSize:
.LFB86:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$49, -4(%rbp)
	jg	.L730
	cmpl	$49, -8(%rbp)
	jg	.L730
	movl	$2, %eax
	jmp	.L731
.L730:
	cmpl	$109, -4(%rbp)
	jg	.L732
	cmpl	$109, -8(%rbp)
	jg	.L732
	movl	$1, %eax
	jmp	.L731
.L732:
	cmpl	$139, -4(%rbp)
	jg	.L733
	cmpl	$199, -8(%rbp)
	jg	.L733
	movl	$3, %eax
	jmp	.L731
.L733:
	movl	$1, %eax
.L731:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE86:
	.size	jefGetHoopSize, .-jefGetHoopSize
	.globl	jefDecode
	.type	jefDecode, @function
jefDecode:
.LFB87:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	testb	%al, %al
	jns	.L735
	movzbl	-4(%rbp), %eax
	jmp	.L736
.L735:
	movzbl	-4(%rbp), %eax
.L736:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE87:
	.size	jefDecode, .-jefDecode
	.section	.rodata
	.align 8
.LC207:
	.string	"ERROR: format-jef.c jefSetHoopFromId(), pattern argument is null"
	.text
	.globl	jefSetHoopFromId
	.type	jefSetHoopFromId, @function
jefSetHoopFromId:
.LFB88:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L738
	leaq	.LC207(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L737
.L738:
	cmpl	$3, -12(%rbp)
	je	.L740
	cmpl	$3, -12(%rbp)
	jg	.L741
	cmpl	$2, -12(%rbp)
	je	.L742
	cmpl	$2, -12(%rbp)
	jg	.L741
	cmpl	$0, -12(%rbp)
	je	.L743
	cmpl	$1, -12(%rbp)
	je	.L744
	jmp	.L741
.L743:
	movq	-8(%rbp), %rax
	movss	.LC208(%rip), %xmm0
	movss	%xmm0, 20(%rax)
	movq	-8(%rbp), %rax
	movss	.LC209(%rip), %xmm0
	movss	%xmm0, 16(%rax)
	jmp	.L737
.L742:
	movq	-8(%rbp), %rax
	movss	.LC210(%rip), %xmm0
	movss	%xmm0, 20(%rax)
	movq	-8(%rbp), %rax
	movss	.LC210(%rip), %xmm0
	movss	%xmm0, 16(%rax)
	jmp	.L737
.L744:
	movq	-8(%rbp), %rax
	movss	.LC209(%rip), %xmm0
	movss	%xmm0, 20(%rax)
	movq	-8(%rbp), %rax
	movss	.LC209(%rip), %xmm0
	movss	%xmm0, 16(%rax)
	jmp	.L737
.L740:
	movq	-8(%rbp), %rax
	movss	.LC211(%rip), %xmm0
	movss	%xmm0, 20(%rax)
	movq	-8(%rbp), %rax
	movss	.LC212(%rip), %xmm0
	movss	%xmm0, 16(%rax)
	jmp	.L737
.L741:
	movq	-8(%rbp), %rax
	movss	.LC213(%rip), %xmm0
	movss	%xmm0, 20(%rax)
	movq	-8(%rbp), %rax
	movss	.LC212(%rip), %xmm0
	movss	%xmm0, 16(%rax)
	nop
.L737:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE88:
	.size	jefSetHoopFromId, .-jefSetHoopFromId
	.globl	read_hoop
	.type	read_hoop, @function
read_hoop:
.LFB89:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L746
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L746:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movq	-16(%rbp), %rdx
	movl	%eax, (%rdx)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movq	-16(%rbp), %rdx
	movl	%eax, 8(%rdx)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movq	-16(%rbp), %rdx
	movl	%eax, 4(%rdx)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movq	-16(%rbp), %rdx
	movl	%eax, 12(%rdx)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE89:
	.size	read_hoop, .-read_hoop
	.section	.rodata
	.align 8
.LC214:
	.string	"ERROR: this file is corrupted or has too many stitches."
.LC215:
	.string	"format flags = %d\n"
.LC216:
	.string	"number of colors = %d\n"
.LC217:
	.string	"number of stitches = %d\n"
.LC218:
	.string	"bounds"
.LC219:
	.string	"rectFrom110x110"
.LC220:
	.string	"rectFrom50x50"
.LC221:
	.string	"rectFrom200x140"
.LC222:
	.string	"rect_from_custom"
	.text
	.globl	readJef
	.type	readJef, @function
readJef:
.LFB90:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$576, %rsp
	movq	%rdi, -568(%rbp)
	movq	%rsi, -576(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -16(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -20(%rbp)
	movq	-576(%rbp), %rdx
	leaq	-336(%rbp), %rax
	movq	%rdx, %rcx
	movl	$8, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-576(%rbp), %rdx
	leaq	-544(%rbp), %rax
	movq	%rdx, %rcx
	movl	$8, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -24(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -28(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %edx
	movq	-568(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	jefSetHoopFromId
	cmpl	$1000000, -28(%rbp)
	jle	.L748
	movl	$1000000, -28(%rbp)
	leaq	.LC214(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L764
.L748:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L750
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC215(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC216(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-28(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC217(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L750:
	leaq	-64(%rbp), %rcx
	movq	-576(%rbp), %rax
	leaq	.LC218(%rip), %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	read_hoop
	leaq	-80(%rbp), %rcx
	movq	-576(%rbp), %rax
	leaq	.LC219(%rip), %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	read_hoop
	leaq	-96(%rbp), %rcx
	movq	-576(%rbp), %rax
	leaq	.LC220(%rip), %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	read_hoop
	leaq	-112(%rbp), %rcx
	movq	-576(%rbp), %rax
	leaq	.LC221(%rip), %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	read_hoop
	leaq	-128(%rbp), %rcx
	movq	-576(%rbp), %rax
	leaq	.LC222(%rip), %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	read_hoop
	movl	$0, -4(%rbp)
	jmp	.L751
.L752:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -40(%rbp)
	movl	-40(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$1739733589, %rdx, %rdx
	shrq	$32, %rdx
	sarl	$5, %edx
	movl	%eax, %ecx
	sarl	$31, %ecx
	subl	%ecx, %edx
	imull	$79, %edx, %ecx
	subl	%ecx, %eax
	movl	%eax, %edx
	movq	-568(%rbp), %r8
	subq	$8, %rsp
	movslq	%edx, %rax
	imulq	$403, %rax, %rax
	leaq	jef_colors(%rip), %rcx
	subq	$408, %rsp
	movq	%rsp, %rdx
	addq	%rcx, %rax
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
	addl	$1, -4(%rbp)
.L751:
	movl	-4(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L752
	movl	-16(%rbp), %eax
	movslq	%eax, %rcx
	movq	-576(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	$0, -8(%rbp)
	jmp	.L753
.L763:
	movb	$0, -33(%rbp)
	movb	$0, -34(%rbp)
	movl	$0, -12(%rbp)
	movq	-576(%rbp), %rdx
	leaq	-546(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	jne	.L765
	movzbl	-546(%rbp), %eax
	cmpb	$-128, %al
	jne	.L756
	movzbl	-545(%rbp), %eax
	movzbl	%al, %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L757
	movq	-576(%rbp), %rdx
	leaq	-546(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	jne	.L766
	movl	$4, -12(%rbp)
	jmp	.L756
.L757:
	movzbl	-545(%rbp), %eax
	cmpb	$2, %al
	je	.L759
	movzbl	-545(%rbp), %eax
	cmpb	$4, %al
	je	.L759
	movzbl	-545(%rbp), %eax
	cmpb	$6, %al
	jne	.L760
.L759:
	movq	-576(%rbp), %rdx
	leaq	-546(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	jne	.L767
	movl	$2, -12(%rbp)
	jmp	.L756
.L760:
	movzbl	-545(%rbp), %eax
	cmpb	$16, %al
	jne	.L756
	movq	-568(%rbp), %rax
	movl	$1, %edx
	movl	$16, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L762
.L756:
	movzbl	-546(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	jefDecode
	movb	%al, -33(%rbp)
	movzbl	-545(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	jefDecode
	movb	%al, -34(%rbp)
	movsbl	-34(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movsbl	-33(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-12(%rbp), %esi
	movq	-568(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	addl	$1, -8(%rbp)
.L753:
	movl	-28(%rbp), %eax
	addl	$99, %eax
	cmpl	%eax, -8(%rbp)
	jle	.L763
	jmp	.L762
.L765:
	nop
	jmp	.L762
.L766:
	nop
	jmp	.L762
.L767:
	nop
.L762:
	movl	$1, %eax
.L764:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE90:
	.size	readJef, .-readJef
	.section	.rodata
	.align 8
.LC223:
	.string	"ERROR: format-jef.c expEncode(), b argument is null"
	.text
	.globl	jefEncode
	.type	jefEncode, @function
jefEncode:
.LFB91:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	%edx, %eax
	movl	%ecx, -20(%rbp)
	movl	%esi, %edx
	movb	%dl, -12(%rbp)
	movb	%al, -16(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L769
	leaq	.LC223(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L768
.L769:
	cmpl	$4, -20(%rbp)
	jne	.L771
	movq	-8(%rbp), %rax
	movb	$-128, (%rax)
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movb	$1, (%rax)
	movq	-8(%rbp), %rax
	leaq	2(%rax), %rdx
	movzbl	-12(%rbp), %eax
	movb	%al, (%rdx)
	movq	-8(%rbp), %rax
	leaq	3(%rax), %rdx
	movzbl	-16(%rbp), %eax
	movb	%al, (%rdx)
	jmp	.L768
.L771:
	cmpl	$16, -20(%rbp)
	jne	.L772
	movq	-8(%rbp), %rax
	movb	$-128, (%rax)
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movb	$16, (%rax)
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movb	$0, (%rax)
	movq	-8(%rbp), %rax
	addq	$3, %rax
	movb	$0, (%rax)
	jmp	.L768
.L772:
	cmpl	$2, -20(%rbp)
	je	.L773
	cmpl	$1, -20(%rbp)
	jne	.L774
.L773:
	movq	-8(%rbp), %rax
	movb	$-128, (%rax)
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movb	$2, (%rax)
	movq	-8(%rbp), %rax
	leaq	2(%rax), %rdx
	movzbl	-12(%rbp), %eax
	movb	%al, (%rdx)
	movq	-8(%rbp), %rax
	leaq	3(%rax), %rdx
	movzbl	-16(%rbp), %eax
	movb	%al, (%rdx)
	jmp	.L768
.L774:
	movzbl	-12(%rbp), %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movzbl	-16(%rbp), %eax
	movb	%al, (%rdx)
.L768:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE91:
	.size	jefEncode, .-jefEncode
	.section	.rodata
.LC225:
	.string	"%04d%02d%02d%02d%02d%02d"
	.text
	.globl	writeJef
	.type	writeJef, @function
writeJef:
.LFB92:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$160, %rsp
	movq	%rdi, -152(%rbp)
	movq	%rsi, -160(%rbp)
	movq	-152(%rbp), %rax
	movss	.LC224(%rip), %xmm1
	movl	.LC224(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_correctForMaxStitchLength@PLT
	movq	-152(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	$6, %edx
	cmpl	%edx, %eax
	cmovl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	addl	$29, %eax
	leal	0(,%rax,4), %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-160(%rbp), %rax
	movl	$10, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	embTime_initNow@PLT
	movl	-92(%rbp), %eax
	movl	%eax, %edi
	movl	-96(%rbp), %eax
	movl	%eax, %esi
	movl	-100(%rbp), %eax
	movl	%eax, %r9d
	movl	-104(%rbp), %eax
	movl	%eax, %r8d
	movl	-108(%rbp), %eax
	addl	$1, %eax
	movl	%eax, %ecx
	movl	-112(%rbp), %eax
	addl	$1900, %eax
	movl	%eax, %edx
	movq	-160(%rbp), %rax
	pushq	%rdi
	pushq	%rsi
	leaq	.LC225(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addq	$16, %rsp
	movq	-160(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-152(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %edx
	movl	$6, %eax
	subl	-8(%rbp), %eax
	testl	%eax, %eax
	js	.L776
	movl	$6, %eax
	subl	-8(%rbp), %eax
	addl	%eax, %eax
	jmp	.L777
.L776:
	movl	$0, %eax
.L777:
	addl	%edx, %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	leaq	-80(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_bounds@PLT
	movss	-72(%rbp), %xmm0
	movss	%xmm0, -20(%rbp)
	movss	-68(%rbp), %xmm0
	movss	%xmm0, -24(%rbp)
	pxor	%xmm1, %xmm1
	cvtss2sd	-20(%rbp), %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %eax
	movl	%eax, -28(%rbp)
	pxor	%xmm1, %xmm1
	cvtss2sd	-24(%rbp), %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %eax
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %edx
	movl	-28(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	jefGetHoopSize
	movl	%eax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	movl	%eax, %ecx
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	cmpl	%eax, %ecx
	jge	.L778
	cmpl	$1101, -28(%rbp)
	setle	%al
	jmp	.L779
.L778:
	cmpl	$1101, -32(%rbp)
	setle	%al
.L779:
	testb	%al, %al
	je	.L780
	cmpl	$1103, -28(%rbp)
	jg	.L781
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	550(%rax), %edx
	jmp	.L782
.L781:
	movl	$-1, %edx
.L782:
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	cmpl	$1103, -32(%rbp)
	jg	.L783
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	550(%rax), %edx
	jmp	.L784
.L783:
	movl	$-1, %edx
.L784:
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	cmpl	$1103, -28(%rbp)
	jg	.L785
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	550(%rax), %edx
	jmp	.L786
.L785:
	movl	$-1, %edx
.L786:
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	cmpl	$1103, -32(%rbp)
	jg	.L787
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	550(%rax), %edx
	jmp	.L788
.L787:
	movl	$-1, %edx
.L788:
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	jmp	.L789
.L780:
	movq	-160(%rbp), %rax
	movl	$-1, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-160(%rbp), %rax
	movl	$-1, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-160(%rbp), %rax
	movl	$-1, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-160(%rbp), %rax
	movl	$-1, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
.L789:
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	movl	%eax, %ecx
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	cmpl	%eax, %ecx
	jge	.L790
	cmpl	$501, -28(%rbp)
	setle	%al
	jmp	.L791
.L790:
	cmpl	$501, -32(%rbp)
	setle	%al
.L791:
	testb	%al, %al
	je	.L792
	cmpl	$503, -28(%rbp)
	jg	.L793
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	250(%rax), %edx
	jmp	.L794
.L793:
	movl	$-1, %edx
.L794:
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	cmpl	$503, -32(%rbp)
	jg	.L795
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	250(%rax), %edx
	jmp	.L796
.L795:
	movl	$-1, %edx
.L796:
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	cmpl	$503, -28(%rbp)
	jg	.L797
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	250(%rax), %edx
	jmp	.L798
.L797:
	movl	$-1, %edx
.L798:
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	cmpl	$503, -32(%rbp)
	jg	.L799
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	250(%rax), %edx
	jmp	.L800
.L799:
	movl	$-1, %edx
.L800:
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	jmp	.L801
.L792:
	movq	-160(%rbp), %rax
	movl	$-1, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-160(%rbp), %rax
	movl	$-1, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-160(%rbp), %rax
	movl	$-1, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-160(%rbp), %rax
	movl	$-1, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
.L801:
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	700(%rax), %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	1000(%rax), %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	700(%rax), %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	1000(%rax), %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	630(%rax), %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	550(%rax), %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	630(%rax), %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	negl	%eax
	leal	550(%rax), %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	$0, -4(%rbp)
	jmp	.L802
.L803:
	movq	-152(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movl	$79, %edx
	leaq	jef_colors(%rip), %rcx
	movq	%rcx, %rsi
	movzbl	(%rax), %ecx
	movzbl	1(%rax), %edi
	salq	$8, %rdi
	orq	%rdi, %rcx
	movzbl	2(%rax), %eax
	salq	$16, %rax
	orq	%rcx, %rax
	movq	%rax, %rdi
	call	emb_find_nearest_thread@PLT
	movl	%eax, -44(%rbp)
	movl	-44(%rbp), %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	addl	$1, -4(%rbp)
.L802:
	movq	-152(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L803
	movl	$0, -4(%rbp)
	jmp	.L804
.L805:
	movl	$13, -40(%rbp)
	movl	-40(%rbp), %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	addl	$1, -4(%rbp)
.L804:
	movl	-12(%rbp), %eax
	subl	-8(%rbp), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L805
	pxor	%xmm0, %xmm0
	movss	%xmm0, -120(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -116(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L806
.L810:
	movb	$0, -124(%rbp)
	movb	$0, -123(%rbp)
	movb	$0, -122(%rbp)
	movb	$0, -121(%rbp)
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -144(%rbp)
	movq	%rdx, -136(%rbp)
	movss	-140(%rbp), %xmm0
	movss	-120(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movb	%al, -33(%rbp)
	movss	-136(%rbp), %xmm0
	movss	-116(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movb	%al, -34(%rbp)
	movss	-120(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsbl	-33(%rbp), %eax
	pxor	%xmm2, %xmm2
	cvtsi2sdl	%eax, %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -120(%rbp)
	movss	-116(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsbl	-34(%rbp), %eax
	pxor	%xmm2, %xmm2
	cvtsi2sdl	%eax, %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -116(%rbp)
	movl	-144(%rbp), %ecx
	movsbl	-34(%rbp), %edx
	movsbl	-33(%rbp), %esi
	leaq	-124(%rbp), %rax
	movq	%rax, %rdi
	call	jefEncode
	movzbl	-124(%rbp), %eax
	cmpb	$-128, %al
	jne	.L807
	movzbl	-123(%rbp), %eax
	cmpb	$1, %al
	je	.L808
	movzbl	-123(%rbp), %eax
	cmpb	$2, %al
	je	.L808
	movzbl	-123(%rbp), %eax
	cmpb	$4, %al
	je	.L808
	movzbl	-123(%rbp), %eax
	cmpb	$16, %al
	jne	.L807
.L808:
	movq	-160(%rbp), %rdx
	leaq	-124(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L809
.L807:
	movq	-160(%rbp), %rdx
	leaq	-124(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
.L809:
	addl	$1, -4(%rbp)
.L806:
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L810
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE92:
	.size	writeJef, .-writeJef
	.section	.rodata
	.align 8
.LC226:
	.string	"ERROR: format-ksm.c ksmEncode(), b argument is null"
	.text
	.globl	ksmEncode
	.type	ksmEncode, @function
ksmEncode:
.LFB93:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	%edx, %eax
	movl	%ecx, -20(%rbp)
	movl	%esi, %edx
	movb	%dl, -12(%rbp)
	movb	%al, -16(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L813
	leaq	.LC226(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L812
.L813:
	cmpl	$2, -20(%rbp)
	jne	.L815
	movq	-8(%rbp), %rax
	movb	$-128, (%rax)
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movb	$2, (%rax)
	movq	-8(%rbp), %rax
	leaq	2(%rax), %rdx
	movzbl	-12(%rbp), %eax
	movb	%al, (%rdx)
	movq	-8(%rbp), %rax
	leaq	3(%rax), %rdx
	movzbl	-16(%rbp), %eax
	movb	%al, (%rdx)
	jmp	.L812
.L815:
	cmpl	$4, -20(%rbp)
	jne	.L816
	movq	-8(%rbp), %rax
	movb	$-128, (%rax)
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movb	$1, (%rax)
	movq	-8(%rbp), %rax
	leaq	2(%rax), %rdx
	movzbl	-12(%rbp), %eax
	movb	%al, (%rdx)
	movq	-8(%rbp), %rax
	leaq	3(%rax), %rdx
	movzbl	-16(%rbp), %eax
	movb	%al, (%rdx)
	jmp	.L812
.L816:
	movzbl	-12(%rbp), %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movzbl	-16(%rbp), %eax
	movb	%al, (%rdx)
.L812:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE93:
	.size	ksmEncode, .-ksmEncode
	.globl	readKsm
	.type	readKsm, @function
readKsm:
.LFB94:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	movq	-32(%rbp), %rax
	movl	$0, %edx
	movl	$512, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L818
.L823:
	movl	$0, -8(%rbp)
	movl	-4(%rbp), %eax
	andl	$8, %eax
	testl	%eax, %eax
	je	.L819
	movzbl	-9(%rbp), %eax
	movsbl	%al, %eax
	andl	$8, %eax
	testl	%eax, %eax
	je	.L819
	movl	$4, -8(%rbp)
	jmp	.L820
.L819:
	movzbl	-9(%rbp), %eax
	movsbl	%al, %eax
	andl	$31, %eax
	testl	%eax, %eax
	je	.L820
	movl	$2, -8(%rbp)
.L820:
	movzbl	-9(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, -4(%rbp)
	movzbl	-9(%rbp), %eax
	movsbl	%al, %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L821
	movzbl	-10(%rbp), %eax
	negl	%eax
	movb	%al, -10(%rbp)
.L821:
	movzbl	-9(%rbp), %eax
	movsbl	%al, %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L822
	movzbl	-11(%rbp), %eax
	negl	%eax
	movb	%al, -11(%rbp)
.L822:
	movzbl	-11(%rbp), %eax
	movsbl	%al, %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movzbl	-10(%rbp), %eax
	movsbl	%al, %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-8(%rbp), %esi
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L818:
	movq	-32(%rbp), %rdx
	leaq	-11(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L823
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE94:
	.size	readKsm, .-readKsm
	.section	.rodata
.LC227:
	.string	"%c%c"
	.text
	.globl	writeKsm
	.type	writeKsm, @function
writeKsm:
.LFB95:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-64(%rbp), %rax
	movl	$512, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	pxor	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L826
.L827:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movss	-44(%rbp), %xmm0
	movss	-16(%rbp), %xmm1
	subss	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %eax
	movb	%al, -5(%rbp)
	movss	-40(%rbp), %xmm0
	movss	-12(%rbp), %xmm1
	subss	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %eax
	movb	%al, -6(%rbp)
	movss	-16(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsbl	-5(%rbp), %eax
	pxor	%xmm2, %xmm2
	cvtsi2sdl	%eax, %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	movss	-12(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsbl	-6(%rbp), %eax
	pxor	%xmm2, %xmm2
	cvtsi2sdl	%eax, %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	movl	-48(%rbp), %ecx
	movsbl	-6(%rbp), %edx
	movsbl	-5(%rbp), %esi
	leaq	-20(%rbp), %rax
	movq	%rax, %rdi
	call	ksmEncode
	movzbl	-19(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-20(%rbp), %eax
	movzbl	%al, %edx
	movq	-64(%rbp), %rax
	leaq	.LC227(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addl	$1, -4(%rbp)
.L826:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L827
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	movl	$26, %edi
	call	fputc@PLT
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE95:
	.size	writeKsm, .-writeKsm
	.globl	max_header
	.section	.rodata
	.align 32
	.type	max_header, @object
	.size	max_header, 213
max_header:
	.string	"VCSM\374\003"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	"\366%"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\b"
	.string	""
	.string	""
	.string	"\005"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"1378"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"Madeira Rayon 40"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\0018\t130/705 H\372"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.text
	.globl	readMax
	.type	readMax, @function
readMax:
.LFB96:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movl	$0, %edx
	movl	$213, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L830
.L831:
	movl	$0, -4(%rbp)
	movzbl	-18(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-19(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-20(%rbp), %eax
	movzbl	%al, %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	pfaffDecode@PLT
	movd	%xmm0, %eax
	movl	%eax, -8(%rbp)
	movzbl	-14(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-15(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-16(%rbp), %eax
	movzbl	%al, %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	pfaffDecode@PLT
	movd	%xmm0, %eax
	movl	%eax, -12(%rbp)
	movss	-12(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	movaps	%xmm0, %xmm2
	divss	%xmm1, %xmm2
	movss	-8(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	divss	%xmm1, %xmm0
	movd	%xmm0, %ecx
	movl	-4(%rbp), %esi
	movq	-40(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
.L830:
	movq	-48(%rbp), %rdx
	leaq	-20(%rbp), %rax
	movq	%rdx, %rcx
	movl	$8, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$8, %rax
	je	.L831
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE96:
	.size	readMax, .-readMax
	.globl	writeMax
	.type	writeMax, @function
writeMax:
.LFB97:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rcx
	movl	$213, %edx
	movl	$1, %esi
	leaq	max_header(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$0, -4(%rbp)
	jmp	.L834
.L835:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movss	-28(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-24(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movss	%xmm0, -12(%rbp)
	movss	-8(%rbp), %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-48(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	write_24bit@PLT
	movss	-12(%rbp), %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-48(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	write_24bit@PLT
	addl	$1, -4(%rbp)
.L834:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L835
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE97:
	.size	writeMax, .-writeMax
	.globl	readMit
	.type	readMit, @function
readMit:
.LFB98:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	jmp	.L838
.L839:
	movzbl	-10(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	mitDecodeStitch@PLT
	movl	%eax, -4(%rbp)
	movzbl	-9(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	mitDecodeStitch@PLT
	movl	%eax, -8(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-8(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-4(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movl	$0, %esi
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L838:
	movq	-32(%rbp), %rdx
	leaq	-10(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	je	.L839
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE98:
	.size	readMit, .-readMit
	.globl	writeMit
	.type	writeMit, @function
writeMit:
.LFB99:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-40(%rbp), %rax
	movss	.LC228(%rip), %xmm1
	movl	.LC228(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_correctForMaxStitchLength@PLT
	pxor	%xmm0, %xmm0
	movss	%xmm0, -4(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L842
.L843:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-12(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movss	-28(%rbp), %xmm0
	subss	-4(%rbp), %xmm0
	movd	%xmm0, %eax
	movd	%eax, %xmm0
	call	mitEncodeStitch@PLT
	movb	%al, -14(%rbp)
	movss	-24(%rbp), %xmm0
	subss	-8(%rbp), %xmm0
	movd	%xmm0, %eax
	movd	%eax, %xmm0
	call	mitEncodeStitch@PLT
	movb	%al, -13(%rbp)
	movss	-28(%rbp), %xmm0
	movss	%xmm0, -4(%rbp)
	movss	-24(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
	movq	-48(%rbp), %rdx
	leaq	-14(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	addl	$1, -12(%rbp)
.L842:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -12(%rbp)
	jl	.L843
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE99:
	.size	writeMit, .-writeMit
	.globl	readNew
	.type	readNew, @function
readNew:
.LFB100:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -16(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L847
	movl	-16(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC190(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L847
.L853:
	movzbl	-20(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	decodeNewStitch@PLT
	movl	%eax, -4(%rbp)
	movzbl	-19(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	decodeNewStitch@PLT
	movl	%eax, -8(%rbp)
	movl	$0, -12(%rbp)
	movzbl	-18(%rbp), %eax
	movb	%al, -17(%rbp)
	movzbl	-18(%rbp), %eax
	movzbl	%al, %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L848
	negl	-4(%rbp)
.L848:
	movzbl	-18(%rbp), %eax
	movzbl	%al, %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L849
	negl	-8(%rbp)
.L849:
	movzbl	-18(%rbp), %eax
	movzbl	%al, %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L850
	movl	$2, -12(%rbp)
.L850:
	movzbl	-18(%rbp), %eax
	movzbl	%al, %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L851
	movl	$1, -12(%rbp)
.L851:
	movsbl	-17(%rbp), %eax
	andl	$30, %eax
	cmpl	$2, %eax
	jne	.L852
	movl	$4, -12(%rbp)
.L852:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-8(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-4(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-12(%rbp), %esi
	movq	-40(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L847:
	movq	-48(%rbp), %rdx
	leaq	-20(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L853
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE100:
	.size	readNew, .-readNew
	.globl	writeNew
	.type	writeNew, @function
writeNew:
.LFB101:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC42(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeDst
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE101:
	.size	writeNew, .-writeNew
	.section	.rodata
	.align 8
.LC229:
	.string	"ERROR: format-ofm.c ofmReadLibrary(), file argument is null"
	.align 8
.LC230:
	.string	"ERROR: format-ofm.c ofmReadLibrary(), unable to allocate memory for libraryName"
	.text
	.globl	ofmReadLibrary
	.type	ofmReadLibrary, @function
ofmReadLibrary:
.LFB102:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movl	$0, -4(%rbp)
	movq	$0, -16(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L858
	leaq	.LC229(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L861
.L858:
	movq	-40(%rbp), %rdx
	leaq	-19(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-40(%rbp), %rdx
	leaq	-20(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movzbl	-20(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	cltq
	addq	%rax, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L860
	leaq	.LC230(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L861
.L860:
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	movslq	%eax, %rdx
	movq	-40(%rbp), %rcx
	movq	-16(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-16(%rbp), %rax
.L861:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE102:
	.size	ofmReadLibrary, .-ofmReadLibrary
	.section	.rodata
	.align 8
.LC231:
	.string	"ERROR: format-ofm.c ofmReadClass(), file argument is null"
.LC232:
	.string	"CExpStitch"
.LC233:
	.string	"CColorChange"
	.text
	.type	ofmReadClass, @function
ofmReadClass:
.LFB103:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$224, %rsp
	movq	%rdi, -216(%rbp)
	cmpq	$0, -216(%rbp)
	jne	.L863
	leaq	.LC231(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L867
.L863:
	movq	-216(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movq	-216(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-216(%rbp), %rcx
	leaq	-208(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movl	-4(%rbp), %eax
	cltq
	movb	$0, -208(%rbp,%rax)
	leaq	-208(%rbp), %rax
	leaq	.LC232(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L865
	movl	$32924, %eax
	jmp	.L867
.L865:
	leaq	-208(%rbp), %rax
	leaq	.LC233(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L866
	movl	$65535, %eax
	jmp	.L867
.L866:
	movl	$0, %eax
.L867:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE103:
	.size	ofmReadClass, .-ofmReadClass
	.section	.rodata
	.align 8
.LC234:
	.string	"ERROR: format-ofm.c ofmReadBlockHeader(), file argument is null"
.LC235:
	.string	"unknown1: %d\n"
	.align 8
.LC236:
	.string	"ERROR: format-ofm.c ofmReadBlockHeader(), unable to allocate memory for s"
.LC237:
	.string	"%d"
.LC238:
	.string	"short1: %d\n"
	.text
	.globl	ofmReadBlockHeader
	.type	ofmReadBlockHeader, @function
ofmReadBlockHeader:
.LFB104:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -88(%rbp)
	movq	$0, -16(%rbp)
	cmpq	$0, -88(%rbp)
	jne	.L869
	leaq	.LC234(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L868
.L869:
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -18(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L871
	movswl	-18(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC235(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L871:
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -24(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L872
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC195(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L872:
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -28(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L873
	movl	-28(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC194(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L873:
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movq	-88(%rbp), %rax
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -29(%rbp)
	movzbl	-29(%rbp), %eax
	addl	%eax, %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L874
	leaq	.LC236(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L868
.L874:
	movzbl	-29(%rbp), %eax
	addl	%eax, %eax
	movslq	%eax, %rdx
	movq	-88(%rbp), %rcx
	movq	-16(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movl	$0, -4(%rbp)
	jmp	.L875
.L876:
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movl	%eax, -80(%rbp,%rdx,4)
	movl	-4(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %eax
	movl	%eax, %esi
	leaq	.LC237(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -4(%rbp)
.L875:
	cmpl	$9, -4(%rbp)
	jle	.L876
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -32(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L868
	movzwl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC238(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L868:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE104:
	.size	ofmReadBlockHeader, .-ofmReadBlockHeader
	.section	.rodata
	.align 8
.LC239:
	.string	"ERROR: format-ofm.c ofmReadColorChange(), file argument is null"
	.align 8
.LC240:
	.string	"ERROR: format-ofm.c ofmReadColorChange(), pattern argument is null"
	.text
	.globl	ofmReadColorChange
	.type	ofmReadColorChange, @function
ofmReadColorChange:
.LFB105:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L880
	leaq	.LC239(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L879
.L880:
	cmpq	$0, -16(%rbp)
	jne	.L882
	leaq	.LC240(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L879
.L882:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	ofmReadBlockHeader
	movq	-16(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L879:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE105:
	.size	ofmReadColorChange, .-ofmReadColorChange
	.section	.rodata
	.align 8
.LC241:
	.string	"ERROR: ofm_read_threads(), file argument is null"
	.align 8
.LC242:
	.string	"ERROR: ofm_read_threads(), p argument is null"
	.align 8
.LC243:
	.string	"ERROR: format-ofm.c ofm_read_threads(), unable to allocate memory for expandedString"
.LC244:
	.string	"threadLibrary: %d\n"
.LC245:
	.string	"colorNumber: %d\n"
.LC246:
	.string	"colorNameLength: %d\n"
.LC247:
	.string	"%10d"
.LC248:
	.string	"primary library name: %s\n"
	.text
	.globl	ofmReadThreads
	.type	ofmReadThreads, @function
ofmReadThreads:
.LFB106:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$1024, %rsp
	movq	%rdi, -1016(%rbp)
	movq	%rsi, -1024(%rbp)
	movq	$0, -16(%rbp)
	movq	$0, -24(%rbp)
	cmpq	$0, -1016(%rbp)
	jne	.L884
	leaq	.LC241(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L883
.L884:
	cmpq	$0, -1024(%rbp)
	jne	.L886
	leaq	.LC242(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L883
.L886:
	movq	-1016(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-1016(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -28(%rbp)
	movq	-1016(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-1016(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L887
	leaq	.LC243(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L883
.L887:
	movl	-32(%rbp), %eax
	movslq	%eax, %rdx
	movq	-1016(%rbp), %rcx
	movq	-24(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movl	$0, -4(%rbp)
	jmp	.L888
.L893:
	leaq	-1008(%rbp), %rcx
	movq	-1016(%rbp), %rax
	movl	$4, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_read@PLT
	movq	-1016(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -52(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L889
	movl	-52(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC244(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L889:
	movq	-1016(%rbp), %rax
	movl	$1, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-1016(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -56(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L890
	movl	-56(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC245(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L890:
	movq	-1016(%rbp), %rax
	movl	$1, %edx
	movl	$3, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-1016(%rbp), %rdx
	leaq	-72(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L891
	leaq	.LC188(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L891:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L892
	movl	-72(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC246(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L892:
	movl	-72(%rbp), %eax
	addl	%eax, %eax
	movslq	%eax, %rdx
	movq	-1016(%rbp), %rcx
	leaq	-592(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-1016(%rbp), %rax
	movl	$1, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	-56(%rbp), %edx
	leaq	-67(%rbp), %rax
	leaq	.LC247(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-67(%rbp), %rax
	leaq	-1008(%rbp), %rdx
	addq	$203, %rdx
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	strcpy@PLT
	leaq	-592(%rbp), %rax
	leaq	-1008(%rbp), %rdx
	addq	$3, %rdx
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	strcpy@PLT
	movq	-1024(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-1008(%rbp), %rax
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
	addl	$1, -4(%rbp)
.L888:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L893
	movq	-1016(%rbp), %rax
	movl	$1, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-1016(%rbp), %rax
	movq	%rax, %rdi
	call	ofmReadLibrary
	movq	%rax, -16(%rbp)
	movq	-1016(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -36(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L894
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC248(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L894:
	movl	$0, -4(%rbp)
	jmp	.L895
.L896:
	movq	-1016(%rbp), %rax
	movq	%rax, %rdi
	call	ofmReadLibrary
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	addl	$1, -4(%rbp)
.L895:
	movl	-4(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L896
.L883:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE106:
	.size	ofmReadThreads, .-ofmReadThreads
	.globl	ofmDecode
	.type	ofmDecode, @function
ofmDecode:
.LFB107:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %edx
	movl	%esi, %eax
	movb	%dl, -20(%rbp)
	movb	%al, -24(%rbp)
	movzbl	-20(%rbp), %eax
	sall	$8, %eax
	movl	%eax, %edx
	movzbl	-24(%rbp), %eax
	orl	%edx, %eax
	cwtl
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movss	%xmm0, -4(%rbp)
	movss	-4(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE107:
	.size	ofmDecode, .-ofmDecode
	.section	.rodata
	.align 8
.LC249:
	.string	"ERROR: format-ofm.c ofmReadExpanded(), file argument is null"
	.align 8
.LC250:
	.string	"ERROR: format-ofm.c ofmReadExpanded(), p argument is null"
	.text
	.globl	ofmReadExpanded
	.type	ofmReadExpanded, @function
ofmReadExpanded:
.LFB108:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$0, -8(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L900
	leaq	.LC249(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L899
.L900:
	cmpq	$0, -48(%rbp)
	jne	.L902
	leaq	.LC250(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L899
.L902:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	ofmReadBlockHeader
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L903
.L908:
	movq	-40(%rbp), %rdx
	leaq	-29(%rbp), %rax
	movq	%rdx, %rcx
	movl	$5, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movzbl	-29(%rbp), %eax
	testb	%al, %al
	jne	.L904
	movzbl	-27(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-28(%rbp), %eax
	movzbl	%al, %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	ofmDecode
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	movzbl	-25(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-26(%rbp), %eax
	movzbl	%al, %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	ofmDecode
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -24(%rbp)
	cmpl	$0, -4(%rbp)
	sete	%al
	movzbl	%al, %esi
	movss	-24(%rbp), %xmm0
	movl	-20(%rbp), %ecx
	movq	-48(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
	jmp	.L905
.L904:
	movzbl	-29(%rbp), %eax
	cmpb	$32, %al
	jne	.L905
	movzbl	-27(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-28(%rbp), %eax
	movzbl	%al, %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	ofmDecode
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	movzbl	-25(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-26(%rbp), %eax
	movzbl	%al, %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	ofmDecode
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	cmpl	$0, -4(%rbp)
	jne	.L906
	movl	$2, %esi
	jmp	.L907
.L906:
	movl	$0, %esi
.L907:
	movss	-16(%rbp), %xmm0
	movl	-12(%rbp), %ecx
	movq	-48(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
.L905:
	addl	$1, -4(%rbp)
.L903:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L908
.L899:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE108:
	.size	ofmReadExpanded, .-ofmReadExpanded
	.section	.rodata
	.align 8
.LC251:
	.string	"Overridden during development."
	.align 8
.LC252:
	.string	"ERROR: format-ofm.c readOfm(), unable to allocate memory for bcfFile"
.LC253:
	.string	"EdsIV Object"
	.align 8
.LC254:
	.string	"ERROR: format-ofm.c readOfm(), unable to allocate memory for s"
.LC255:
	.string	"unknownCount = %d\n"
.LC256:
	.string	"key: %d\n"
	.text
	.globl	readOfm
	.type	readOfm, @function
readOfm:
.LFB109:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movl	$0, -4(%rbp)
	movq	$0, -16(%rbp)
	movq	$0, -24(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L910
	leaq	.LC251(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L911
.L910:
	movl	$104, %edi
	call	malloc@PLT
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L912
	leaq	.LC252(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L911
.L912:
	movq	-24(%rbp), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	bcfFile_read@PLT
	movq	-64(%rbp), %rcx
	movq	-24(%rbp), %rax
	leaq	.LC253(%rip), %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	GetFile@PLT
	movq	%rax, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	bcf_file_free@PLT
	movq	$0, -24(%rbp)
	movq	-32(%rbp), %rax
	movl	$0, %edx
	movl	$454, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-56(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ofmReadThreads
	movq	-32(%rbp), %rax
	movl	$1, %edx
	movl	$272, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-32(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -36(%rbp)
	movl	-36(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L913
	leaq	.LC254(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L911
.L913:
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rcx
	movq	-16(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -40(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L914
	movl	-40(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC255(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L914:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	ofmReadClass
	movl	%eax, -4(%rbp)
.L921:
	cmpl	$65279, -4(%rbp)
	je	.L923
	cmpl	$32924, -4(%rbp)
	jne	.L917
	movq	-56(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ofmReadExpanded
	jmp	.L918
.L917:
	movq	-56(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ofmReadColorChange
.L918:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movzwl	%ax, %eax
	movl	%eax, -4(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L919
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC256(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L919:
	cmpl	$65535, -4(%rbp)
	jne	.L921
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	ofmReadClass
	jmp	.L921
.L923:
	nop
	movq	-56(%rbp), %rax
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	emb_pattern_flip@PLT
	movl	$1, %eax
.L911:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE109:
	.size	readOfm, .-readOfm
	.globl	writeOfm
	.type	writeOfm, @function
writeOfm:
.LFB110:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC42(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeDst
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE110:
	.size	writeOfm, .-writeOfm
	.section	.rodata
.LC257:
	.string	"version: %d\n"
.LC258:
	.string	"hoop size: %d\n"
.LC259:
	.string	"st: %d\n"
	.text
	.globl	readPcd
	.type	readPcd, @function
readPcd:
.LFB111:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$480, %rsp
	movq	%rdi, -456(%rbp)
	movq	%rsi, -464(%rbp)
	movq	%rdx, -472(%rbp)
	movb	$1, -1(%rbp)
	movl	$0, -8(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	movl	$0, -24(%rbp)
	movw	$0, -26(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -27(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -28(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movw	%ax, -26(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L927
	movzwl	-26(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC193(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L927:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L928
	movzbl	-27(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC257(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movzbl	-28(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC258(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L928:
	movl	$0, -8(%rbp)
	jmp	.L929
.L932:
	leaq	-448(%rbp), %rcx
	movq	-472(%rbp), %rax
	movl	$4, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_read@PLT
	movb	$0, -245(%rbp)
	movb	$0, -445(%rbp)
	movzbl	-448(%rbp), %eax
	testb	%al, %al
	jne	.L930
	movzbl	-447(%rbp), %eax
	testb	%al, %al
	jne	.L930
	movzbl	-446(%rbp), %eax
	testb	%al, %al
	je	.L931
.L930:
	movb	$0, -1(%rbp)
.L931:
	movq	-456(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-448(%rbp), %rax
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
	addl	$1, -8(%rbp)
.L929:
	movzwl	-26(%rbp), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L932
	cmpb	$0, -1(%rbp)
	je	.L933
	movq	-464(%rbp), %rdx
	movq	-456(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_loadExternalColorFile@PLT
.L933:
	movq	-472(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movzwl	%ax, %eax
	movl	%eax, -24(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L934
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC259(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L934:
	movl	$0, -8(%rbp)
	jmp	.L935
.L941:
	movq	-472(%rbp), %rdx
	leaq	-37(%rbp), %rax
	movq	%rdx, %rcx
	movl	$9, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$9, %rax
	jne	.L943
	movl	$0, -12(%rbp)
	movzbl	-29(%rbp), %eax
	movzbl	%al, %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L938
	movl	$4, -12(%rbp)
	jmp	.L939
.L938:
	movzbl	-29(%rbp), %eax
	movzbl	%al, %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L939
	movl	$2, -12(%rbp)
.L939:
	movzbl	-34(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-35(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-36(%rbp), %eax
	movzbl	%al, %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	pfaffDecode@PLT
	movd	%xmm0, %eax
	movl	%eax, -16(%rbp)
	movzbl	-30(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-31(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-32(%rbp), %eax
	movzbl	%al, %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	pfaffDecode@PLT
	movd	%xmm0, %eax
	movl	%eax, -20(%rbp)
	movss	-20(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	movaps	%xmm0, %xmm2
	divss	%xmm1, %xmm2
	movss	-16(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	divss	%xmm1, %xmm0
	movd	%xmm0, %ecx
	movl	-12(%rbp), %esi
	movq	-456(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
	addl	$1, -8(%rbp)
.L935:
	movl	-8(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L941
	jmp	.L937
.L943:
	nop
.L937:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE111:
	.size	readPcd, .-readPcd
	.section	.rodata
.LC260:
	.string	"2\003"
	.text
	.globl	writePcd
	.type	writePcd, @function
writePcd:
.LFB112:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	leaq	.LC260(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-56(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movzwl	%ax, %edx
	movq	-64(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u16@PLT
	movl	$0, -20(%rbp)
	jmp	.L945
.L946:
	movq	-56(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -23(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -21(%rbp)
	movq	-64(%rbp), %rax
	movl	$4, %edx
	movzbl	-23(%rbp), %ecx
	movzbl	-22(%rbp), %esi
	salq	$8, %rsi
	orq	%rcx, %rsi
	movzbl	-21(%rbp), %ecx
	salq	$16, %rcx
	orq	%rsi, %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_write@PLT
	addl	$1, -20(%rbp)
.L945:
	movq	-56(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L946
	movl	$16, %eax
	subl	-20(%rbp), %eax
	leal	0(,%rax,4), %edx
	movq	-64(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	movzwl	%ax, %edx
	movq	-64(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u16@PLT
	movl	$0, -20(%rbp)
	jmp	.L947
.L948:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	-48(%rbp), %ebx
	movss	-40(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, %r12d
	movss	-44(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, %esi
	movq	-64(%rbp), %rax
	movl	%ebx, %ecx
	movl	%r12d, %edx
	movq	%rax, %rdi
	call	pfaffEncode@PLT
	addl	$1, -20(%rbp)
.L947:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L948
	movl	$1, %eax
	addq	$48, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE112:
	.size	writePcd, .-writePcd
	.section	.rodata
.LC261:
	.string	"TODO: check header_size %d\n"
	.text
	.globl	readPcm
	.type	readPcm, @function
readPcm:
.LFB113:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movl	$0, -4(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	movl	$38, -20(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L951
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC261(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L951:
	movq	-64(%rbp), %rax
	movl	$0, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	$0, -4(%rbp)
	jmp	.L952
.L953:
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -28(%rbp)
	movq	-56(%rbp), %r8
	subq	$8, %rsp
	movl	-28(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	leaq	pcm_colors(%rip), %rcx
	subq	$408, %rsp
	movq	%rsp, %rdx
	addq	%rcx, %rax
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
	addl	$1, -4(%rbp)
.L952:
	cmpl	$15, -4(%rbp)
	jle	.L953
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16be@PLT
	cwtl
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	$1000000, %edx
	cmpl	%edx, %eax
	cmovg	%edx, %eax
	movl	%eax, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L954
.L960:
	movl	$0, -8(%rbp)
	movq	-64(%rbp), %rdx
	leaq	-37(%rbp), %rax
	movq	%rdx, %rcx
	movl	$9, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$9, %rax
	jne	.L962
	movzbl	-29(%rbp), %eax
	movzbl	%al, %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L957
	movl	$4, -8(%rbp)
	jmp	.L958
.L957:
	movzbl	-29(%rbp), %eax
	movzbl	%al, %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L958
	movl	$2, -8(%rbp)
.L958:
	movzbl	-37(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-36(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-35(%rbp), %eax
	movzbl	%al, %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	pfaffDecode@PLT
	movd	%xmm0, %eax
	movl	%eax, -12(%rbp)
	movzbl	-33(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-32(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-31(%rbp), %eax
	movzbl	%al, %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	pfaffDecode@PLT
	movd	%xmm0, %eax
	movl	%eax, -16(%rbp)
	movss	-16(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	movaps	%xmm0, %xmm2
	divss	%xmm1, %xmm2
	movss	-12(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	divss	%xmm1, %xmm0
	movd	%xmm0, %ecx
	movl	-8(%rbp), %esi
	movq	-56(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
	addl	$1, -4(%rbp)
.L954:
	movl	-4(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L960
	jmp	.L956
.L962:
	nop
.L956:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE113:
	.size	readPcm, .-readPcm
	.section	.rodata
.LC262:
	.string	"overridden, defaulting to dst"
	.text
	.globl	writePcm
	.type	writePcm, @function
writePcm:
.LFB114:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC262(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeDst
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE114:
	.size	writePcm, .-writePcm
	.globl	readPcq
	.type	readPcq, @function
readPcq:
.LFB115:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$480, %rsp
	movq	%rdi, -456(%rbp)
	movq	%rsi, -464(%rbp)
	movq	%rdx, -472(%rbp)
	movb	$1, -1(%rbp)
	movl	$0, -8(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -24(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -25(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -26(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movw	%ax, -28(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L966
	movzwl	-28(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC193(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L966:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L967
	movzbl	-25(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC257(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movzbl	-26(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC258(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L967:
	movl	$0, -8(%rbp)
	jmp	.L968
.L971:
	leaq	-448(%rbp), %rcx
	movq	-472(%rbp), %rax
	movl	$4, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_read@PLT
	movb	$0, -245(%rbp)
	movb	$0, -445(%rbp)
	movzbl	-448(%rbp), %eax
	testb	%al, %al
	jne	.L969
	movzbl	-447(%rbp), %eax
	testb	%al, %al
	jne	.L969
	movzbl	-446(%rbp), %eax
	testb	%al, %al
	je	.L970
.L969:
	movb	$0, -1(%rbp)
.L970:
	movq	-456(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-448(%rbp), %rax
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
	addl	$1, -8(%rbp)
.L968:
	movzwl	-28(%rbp), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L971
	cmpb	$0, -1(%rbp)
	je	.L972
	movq	-464(%rbp), %rdx
	movq	-456(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_loadExternalColorFile@PLT
.L972:
	movq	-472(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movzwl	%ax, %eax
	movl	%eax, -24(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L973
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC259(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L973:
	movl	$0, -8(%rbp)
	jmp	.L974
.L980:
	movl	$0, -12(%rbp)
	movq	-472(%rbp), %rdx
	leaq	-37(%rbp), %rax
	movq	%rdx, %rcx
	movl	$9, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$9, %rax
	jne	.L982
	movzbl	-29(%rbp), %eax
	movzbl	%al, %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L977
	movl	$4, -12(%rbp)
	jmp	.L978
.L977:
	movzbl	-29(%rbp), %eax
	movzbl	%al, %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L978
	movl	$2, -12(%rbp)
.L978:
	movzbl	-34(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-35(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-36(%rbp), %eax
	movzbl	%al, %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	pfaffDecode@PLT
	movd	%xmm0, %eax
	movl	%eax, -16(%rbp)
	movzbl	-30(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-31(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-32(%rbp), %eax
	movzbl	%al, %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	pfaffDecode@PLT
	movd	%xmm0, %eax
	movl	%eax, -20(%rbp)
	movss	-20(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	movaps	%xmm0, %xmm2
	divss	%xmm1, %xmm2
	movss	-16(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	divss	%xmm1, %xmm0
	movd	%xmm0, %ecx
	movl	-12(%rbp), %esi
	movq	-456(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
	addl	$1, -8(%rbp)
.L974:
	movl	-8(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L980
	jmp	.L976
.L982:
	nop
.L976:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE115:
	.size	readPcq, .-readPcq
	.globl	writePcq
	.type	writePcq, @function
writePcq:
.LFB116:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	leaq	.LC260(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-56(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movzwl	%ax, %edx
	movq	-64(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u16@PLT
	movl	$0, -20(%rbp)
	jmp	.L984
.L985:
	movq	-56(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -23(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -21(%rbp)
	movq	-64(%rbp), %rax
	movl	$4, %edx
	movzbl	-23(%rbp), %ecx
	movzbl	-22(%rbp), %esi
	salq	$8, %rsi
	orq	%rcx, %rsi
	movzbl	-21(%rbp), %ecx
	salq	$16, %rcx
	orq	%rsi, %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_write@PLT
	addl	$1, -20(%rbp)
.L984:
	movq	-56(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L985
	movl	$16, %eax
	subl	-20(%rbp), %eax
	leal	0(,%rax,4), %edx
	movq	-64(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	movzwl	%ax, %edx
	movq	-64(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u16@PLT
	movl	$0, -20(%rbp)
	jmp	.L986
.L987:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	-48(%rbp), %ebx
	movss	-40(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, %r12d
	movss	-44(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, %esi
	movq	-64(%rbp), %rax
	movl	%ebx, %ecx
	movl	%r12d, %edx
	movq	%rax, %rdi
	call	pfaffEncode@PLT
	addl	$1, -20(%rbp)
.L986:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L987
	movl	$1, %eax
	addq	$48, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE116:
	.size	writePcq, .-writePcq
	.section	.rodata
.LC266:
	.string	"color count: %d\n"
	.text
	.globl	readPcs
	.type	readPcs, @function
readPcs:
.LFB117:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$480, %rsp
	movq	%rdi, -456(%rbp)
	movq	%rsi, -464(%rbp)
	movq	%rdx, -472(%rbp)
	movb	$1, -1(%rbp)
	movl	$0, -8(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -24(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -25(%rbp)
	movq	-472(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -26(%rbp)
	movzbl	-26(%rbp), %eax
	cmpl	$2, %eax
	je	.L990
	cmpl	$3, %eax
	je	.L991
	jmp	.L992
.L990:
	movq	-456(%rbp), %rax
	movss	.LC263(%rip), %xmm0
	movss	%xmm0, 16(%rax)
	movq	-456(%rbp), %rax
	movss	.LC263(%rip), %xmm0
	movss	%xmm0, 20(%rax)
	jmp	.L992
.L991:
	movq	-456(%rbp), %rax
	movss	.LC264(%rip), %xmm0
	movss	%xmm0, 16(%rax)
	movq	-456(%rbp), %rax
	movss	.LC265(%rip), %xmm0
	movss	%xmm0, 20(%rax)
	nop
.L992:
	movq	-472(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movw	%ax, -28(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L993
	movzwl	-28(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC193(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L993:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L994
	movzbl	-25(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC257(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movzbl	-26(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC258(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movzwl	-28(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC266(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L994:
	movl	$0, -8(%rbp)
	jmp	.L995
.L998:
	leaq	-448(%rbp), %rcx
	movq	-472(%rbp), %rax
	movl	$4, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_read@PLT
	movb	$0, -245(%rbp)
	movb	$0, -445(%rbp)
	movzbl	-448(%rbp), %eax
	testb	%al, %al
	jne	.L996
	movzbl	-447(%rbp), %eax
	testb	%al, %al
	jne	.L996
	movzbl	-446(%rbp), %eax
	testb	%al, %al
	je	.L997
.L996:
	movb	$0, -1(%rbp)
.L997:
	movq	-456(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-448(%rbp), %rax
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
	addl	$1, -8(%rbp)
.L995:
	movzwl	-28(%rbp), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L998
	cmpb	$0, -1(%rbp)
	je	.L999
	movq	-464(%rbp), %rdx
	movq	-456(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_loadExternalColorFile@PLT
.L999:
	movq	-472(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movzwl	%ax, %eax
	movl	%eax, -24(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1000
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC259(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1000:
	movl	$0, -8(%rbp)
	jmp	.L1001
.L1007:
	movl	$0, -12(%rbp)
	movq	-472(%rbp), %rdx
	leaq	-37(%rbp), %rax
	movq	%rdx, %rcx
	movl	$9, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$9, %rax
	jne	.L1009
	movzbl	-29(%rbp), %eax
	movzbl	%al, %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L1004
	movl	$4, -12(%rbp)
	jmp	.L1005
.L1004:
	movzbl	-29(%rbp), %eax
	movzbl	%al, %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L1005
	movl	$2, -12(%rbp)
.L1005:
	movzbl	-34(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-35(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-36(%rbp), %eax
	movzbl	%al, %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	pfaffDecode@PLT
	movd	%xmm0, %eax
	movl	%eax, -16(%rbp)
	movzbl	-30(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-31(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-32(%rbp), %eax
	movzbl	%al, %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	pfaffDecode@PLT
	movd	%xmm0, %eax
	movl	%eax, -20(%rbp)
	movss	-20(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	movaps	%xmm0, %xmm2
	divss	%xmm1, %xmm2
	movss	-16(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	divss	%xmm1, %xmm0
	movd	%xmm0, %ecx
	movl	-12(%rbp), %esi
	movq	-456(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
	addl	$1, -8(%rbp)
.L1001:
	movl	-8(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L1007
	jmp	.L1003
.L1009:
	nop
.L1003:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE117:
	.size	readPcs, .-readPcs
	.globl	writePcs
	.type	writePcs, @function
writePcs:
.LFB118:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	leaq	.LC260(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-56(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movzwl	%ax, %edx
	movq	-64(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u16@PLT
	movl	$0, -20(%rbp)
	jmp	.L1011
.L1012:
	movq	-56(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -23(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -21(%rbp)
	movq	-64(%rbp), %rax
	movl	$4, %edx
	movzbl	-23(%rbp), %ecx
	movzbl	-22(%rbp), %esi
	salq	$8, %rsi
	orq	%rcx, %rsi
	movzbl	-21(%rbp), %ecx
	salq	$16, %rcx
	orq	%rsi, %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_write@PLT
	addl	$1, -20(%rbp)
.L1011:
	movq	-56(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L1012
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	movzwl	%ax, %edx
	movq	-64(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u16@PLT
	movl	$0, -20(%rbp)
	jmp	.L1013
.L1014:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	-48(%rbp), %ebx
	movss	-40(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, %r12d
	movss	-44(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, %esi
	movq	-64(%rbp), %rax
	movl	%ebx, %ecx
	movl	%r12d, %edx
	movq	%rax, %rdi
	call	pfaffEncode@PLT
	addl	$1, -20(%rbp)
.L1013:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L1014
	movl	$1, %eax
	addq	$48, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE118:
	.size	writePcs, .-writePcs
	.globl	readPecStitches
	.type	readPecStitches, @function
readPecStitches:
.LFB119:
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
	movq	%rsi, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -40(%rbp)
	jmp	.L1017
.L1029:
	movzbl	-42(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, -20(%rbp)
	movzbl	-41(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, -24(%rbp)
	movl	$0, -28(%rbp)
	movzbl	-42(%rbp), %eax
	cmpb	$-1, %al
	jne	.L1018
	movzbl	-41(%rbp), %eax
	testb	%al, %al
	jne	.L1018
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_end@PLT
	jmp	.L1016
.L1018:
	movzbl	-42(%rbp), %eax
	cmpb	$-2, %al
	jne	.L1020
	movzbl	-41(%rbp), %eax
	cmpb	$-80, %al
	jne	.L1020
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movq	-56(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L1017
.L1020:
	movl	-20(%rbp), %eax
	andl	$128, %eax
	testl	%eax, %eax
	je	.L1021
	movl	-20(%rbp), %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L1022
	movl	$2, -28(%rbp)
.L1022:
	movl	-20(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L1023
	movl	$1, -28(%rbp)
.L1023:
	movl	-20(%rbp), %eax
	sall	$8, %eax
	andl	$3840, %eax
	movl	%eax, %edx
	movl	-24(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	andl	$2048, %eax
	testl	%eax, %eax
	je	.L1024
	subl	$4096, -20(%rbp)
	jmp	.L1024
.L1021:
	cmpl	$63, -20(%rbp)
	jle	.L1024
	addl	$-128, -20(%rbp)
.L1024:
	movl	-24(%rbp), %eax
	andl	$128, %eax
	testl	%eax, %eax
	je	.L1025
	movl	-24(%rbp), %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L1026
	movl	$2, -28(%rbp)
.L1026:
	movl	-24(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L1027
	movl	$1, -28(%rbp)
.L1027:
	movl	-24(%rbp), %eax
	sall	$8, %eax
	andl	$3840, %eax
	movl	%eax, %ebx
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	addl	%ebx, %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	andl	$2048, %eax
	testl	%eax, %eax
	je	.L1028
	subl	$4096, -24(%rbp)
	jmp	.L1028
.L1025:
	cmpl	$63, -24(%rbp)
	jle	.L1028
	addl	$-128, -24(%rbp)
.L1028:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-24(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-20(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-28(%rbp), %esi
	movq	-56(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L1017:
	movq	-40(%rbp), %rdx
	leaq	-42(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	je	.L1029
.L1016:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE119:
	.size	readPecStitches, .-readPecStitches
	.section	.rodata
	.align 8
.LC267:
	.string	"ERROR: format-pec.c pecEncodeJump(), file argument is null"
	.text
	.globl	pecEncodeJump
	.type	pecEncodeJump, @function
pecEncodeJump:
.LFB120:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	negl	%edx
	cmovns	%edx, %eax
	andl	$2047, %eax
	movl	%eax, -4(%rbp)
	movl	$128, -8(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L1031
	leaq	.LC267(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L1030
.L1031:
	movl	-32(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L1033
	orl	$32, -8(%rbp)
.L1033:
	movl	-32(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L1034
	orl	$16, -8(%rbp)
.L1034:
	cmpl	$0, -28(%rbp)
	jns	.L1035
	movl	-28(%rbp), %eax
	andl	$2047, %eax
	movl	%eax, -4(%rbp)
	orl	$2048, -4(%rbp)
.L1035:
	movl	-4(%rbp), %eax
	sarl	$8, %eax
	andl	$15, %eax
	movl	%eax, %edx
	movl	-8(%rbp), %eax
	orl	%edx, %eax
	movb	%al, -9(%rbp)
	movq	-24(%rbp), %rdx
	leaq	-9(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	-4(%rbp), %eax
	movb	%al, -9(%rbp)
	movq	-24(%rbp), %rdx
	leaq	-9(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
.L1030:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE120:
	.size	pecEncodeJump, .-pecEncodeJump
	.section	.rodata
	.align 8
.LC268:
	.string	"ERROR: format-pec.c pecEncodeStop(), file argument is null"
.LC269:
	.string	"\376\260"
	.text
	.globl	pecEncodeStop
	.type	pecEncodeStop, @function
pecEncodeStop:
.LFB121:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, %eax
	movb	%al, -12(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L1037
	leaq	.LC268(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L1036
.L1037:
	movq	-8(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	leaq	.LC269(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-8(%rbp), %rdx
	leaq	-12(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
.L1036:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE121:
	.size	pecEncodeStop, .-pecEncodeStop
	.section	.rodata
.LC270:
	.string	"fileName: %s\n"
.LC271:
	.string	"graphicsOffset: %d\n"
	.text
	.globl	readPec
	.type	readPec, @function
readPec:
.LFB122:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1040
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC270(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1040:
	movq	-40(%rbp), %rax
	movl	$522, %esi
	movq	%rax, %rdi
	call	check_header_present@PLT
	testl	%eax, %eax
	jne	.L1041
	movl	$0, %eax
	jmp	.L1042
.L1041:
	movq	-40(%rbp), %rax
	movl	$0, %edx
	movl	$56, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -5(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1043
.L1044:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, %edx
	movsbw	%dl, %cx
	movl	%ecx, %eax
	sall	$7, %eax
	subl	%ecx, %eax
	shrw	$8, %ax
	sarb	$5, %al
	movl	%edx, %ecx
	sarb	$7, %cl
	subl	%ecx, %eax
	movl	%eax, %ecx
	sall	$6, %ecx
	addl	%eax, %ecx
	movl	%edx, %eax
	subl	%ecx, %eax
	movsbl	%al, %eax
	movq	-24(%rbp), %r8
	subq	$8, %rsp
	cltq
	imulq	$403, %rax, %rax
	leaq	pec_colors(%rip), %rcx
	subq	$408, %rsp
	movq	%rsp, %rdx
	addq	%rcx, %rax
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
	addl	$1, -4(%rbp)
.L1043:
	movzbl	-5(%rbp), %eax
	cmpl	%eax, -4(%rbp)
	jle	.L1044
	movq	-40(%rbp), %rax
	movl	$0, %edx
	movl	$522, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -12(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	sall	$8, %eax
	orl	%eax, -12(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	sall	$16, %eax
	orl	%eax, -12(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1045
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC271(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1045:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPecStitches
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movl	$1, %eax
.L1042:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE122:
	.size	readPec, .-readPec
	.section	.rodata
	.align 8
.LC272:
	.string	"ERROR: format-pec.c pecEncode(), file argument is null"
	.align 8
.LC273:
	.string	"ERROR: format-pec.c pecEncode(), p argument is null"
.LC274:
	.string	"\377"
	.text
	.globl	pecEncode
	.type	pecEncode, @function
pecEncode:
.LFB123:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -4(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	movb	$2, -9(%rbp)
	cmpq	$0, -72(%rbp)
	jne	.L1047
	leaq	.LC272(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L1046
.L1047:
	cmpq	$0, -80(%rbp)
	jne	.L1049
	leaq	.LC273(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L1046
.L1049:
	movl	$0, -16(%rbp)
	jmp	.L1050
.L1060:
	movq	-80(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-16(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movss	-44(%rbp), %xmm0
	subss	-4(%rbp), %xmm0
	movd	%xmm0, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, -20(%rbp)
	movss	-40(%rbp), %xmm0
	subss	-8(%rbp), %xmm0
	movd	%xmm0, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, -24(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-20(%rbp), %xmm0
	movss	-4(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-24(%rbp), %xmm0
	movss	-8(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	movl	-48(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L1051
	movzbl	-9(%rbp), %edx
	movq	-72(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	pecEncodeStop
	cmpb	$2, -9(%rbp)
	jne	.L1052
	movb	$1, -9(%rbp)
	jmp	.L1053
.L1052:
	movb	$2, -9(%rbp)
	jmp	.L1053
.L1051:
	movl	-48(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L1054
	movq	-72(%rbp), %rax
	movq	%rax, %rcx
	movl	$1, %edx
	movl	$1, %esi
	leaq	.LC274(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L1046
.L1054:
	cmpl	$62, -20(%rbp)
	jg	.L1055
	cmpl	$-63, -20(%rbp)
	jl	.L1055
	cmpl	$62, -24(%rbp)
	jg	.L1055
	cmpl	$-63, -24(%rbp)
	jl	.L1055
	movl	-48(%rbp), %eax
	andl	$3, %eax
	testl	%eax, %eax
	jne	.L1055
	cmpl	$0, -20(%rbp)
	jns	.L1056
	movl	-20(%rbp), %eax
	addl	$-128, %eax
	movb	%al, -50(%rbp)
	jmp	.L1057
.L1056:
	movl	-20(%rbp), %eax
	movb	%al, -50(%rbp)
.L1057:
	cmpl	$0, -24(%rbp)
	jns	.L1058
	movl	-24(%rbp), %eax
	addl	$-128, %eax
	movb	%al, -49(%rbp)
	jmp	.L1059
.L1058:
	movl	-24(%rbp), %eax
	movb	%al, -49(%rbp)
.L1059:
	movq	-72(%rbp), %rdx
	leaq	-50(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L1053
.L1055:
	movl	-48(%rbp), %edx
	movl	-20(%rbp), %ecx
	movq	-72(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	pecEncodeJump
	movl	-48(%rbp), %edx
	movl	-24(%rbp), %ecx
	movq	-72(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	pecEncodeJump
.L1053:
	addl	$1, -16(%rbp)
.L1050:
	movq	-80(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -16(%rbp)
	jl	.L1060
.L1046:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE123:
	.size	pecEncode, .-pecEncode
	.section	.rodata
.LC275:
	.string	"LA:"
.LC276:
	.string	"\r"
.LC277:
	.string	"\377"
	.string	"\006&"
.LC278:
	.string	"1\377\360"
.LC279:
	.string	"\001\340\001\260"
	.text
	.globl	writePecStitches
	.type	writePecStitches, @function
writePecStitches:
.LFB124:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$2016, %rsp
	movq	%rdi, -1992(%rbp)
	movq	%rsi, -2000(%rbp)
	movq	%rdx, -2008(%rbp)
	movq	-2008(%rbp), %rax
	movl	$47, %esi
	movq	%rax, %rdi
	call	string_rchar@PLT
	movslq	%eax, %rdx
	movq	-2008(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -24(%rbp)
	movq	-2008(%rbp), %rax
	movl	$92, %esi
	movq	%rax, %rdi
	call	string_rchar@PLT
	movslq	%eax, %rdx
	movq	-2008(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -32(%rbp)
	movq	-2008(%rbp), %rax
	movl	$46, %esi
	movq	%rax, %rdi
	call	string_rchar@PLT
	movslq	%eax, %rdx
	movq	-2008(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -40(%rbp)
	movq	$0, -16(%rbp)
	movq	-2008(%rbp), %rax
	movq	%rax, -16(%rbp)
	cmpq	$0, -24(%rbp)
	je	.L1062
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -16(%rbp)
.L1062:
	cmpq	$0, -32(%rbp)
	je	.L1063
	movq	-32(%rbp), %rax
	cmpq	%rax, -16(%rbp)
	jnb	.L1063
	movq	-32(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -16(%rbp)
.L1063:
	movq	-2000(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	leaq	.LC275(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-40(%rbp), %rax
	subq	-16(%rbp), %rax
	movl	%eax, -44(%rbp)
	jmp	.L1064
.L1065:
	movq	-2000(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	addq	$1, -16(%rbp)
.L1064:
	movq	-16(%rbp), %rax
	cmpq	-40(%rbp), %rax
	jb	.L1065
	movl	$16, %eax
	subl	-44(%rbp), %eax
	movl	%eax, %edx
	movq	-2000(%rbp), %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-2000(%rbp), %rax
	movq	%rax, %rcx
	movl	$1, %edx
	movl	$1, %esi
	leaq	.LC276(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-2000(%rbp), %rax
	movl	$12, %edx
	movl	$32, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-2000(%rbp), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	leaq	.LC277(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-2000(%rbp), %rax
	movl	$12, %edx
	movl	$32, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-1992(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	subl	$1, %eax
	movb	%al, -1937(%rbp)
	movq	-2000(%rbp), %rdx
	leaq	-1937(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$0, -4(%rbp)
	jmp	.L1066
.L1067:
	movq	-1992(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -1940(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -1938(%rbp)
	movl	$65, %eax
	movl	%eax, %edx
	leaq	pec_colors(%rip), %rax
	movq	%rax, %rsi
	movl	-1940(%rbp), %eax
	andl	$16777215, %eax
	movq	%rax, %rdi
	call	emb_find_nearest_thread@PLT
	movb	%al, -1941(%rbp)
	movq	-2000(%rbp), %rdx
	leaq	-1941(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	addl	$1, -4(%rbp)
.L1066:
	movq	-1992(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1067
	movq	-1992(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movl	$463, %edx
	subl	%eax, %edx
	movq	-2000(%rbp), %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-2000(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-2000(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -48(%rbp)
	movq	-2000(%rbp), %rax
	movl	$3, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-2000(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	leaq	.LC278(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	leaq	-112(%rbp), %rax
	movq	-1992(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_bounds@PLT
	movl	-100(%rbp), %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, -52(%rbp)
	movl	-104(%rbp), %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, -56(%rbp)
	movl	-112(%rbp), %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	negl	%eax
	orw	$-28672, %ax
	movw	%ax, -58(%rbp)
	movl	-108(%rbp), %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	negl	%eax
	orw	$-28672, %ax
	movw	%ax, -60(%rbp)
	movl	-56(%rbp), %eax
	movswl	%ax, %edx
	movq	-2000(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movl	-52(%rbp), %eax
	movswl	%ax, %edx
	movq	-2000(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-2000(%rbp), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	leaq	.LC279(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movzwl	-58(%rbp), %eax
	movswl	%ax, %edx
	movq	-2000(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16be@PLT
	movzwl	-60(%rbp), %eax
	movswl	%ax, %edx
	movq	-2000(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16be@PLT
	movq	-1992(%rbp), %rdx
	movq	-2000(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	pecEncode
	movq	-2000(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, %edx
	movl	-48(%rbp), %eax
	subl	%eax, %edx
	leal	2(%rdx), %eax
	movl	%eax, -64(%rbp)
	movl	-48(%rbp), %eax
	movslq	%eax, %rcx
	movq	-2000(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	-64(%rbp), %eax
	movzbl	%al, %eax
	movq	-2000(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc@PLT
	movl	-64(%rbp), %eax
	sarl	$8, %eax
	movzbl	%al, %eax
	movq	-2000(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc@PLT
	movl	-64(%rbp), %eax
	sarl	$16, %eax
	movzbl	%al, %eax
	movq	-2000(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc@PLT
	movq	-2000(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	leaq	-1936(%rbp), %rax
	leaq	imageWithFrame(%rip), %rdx
	movl	$228, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-52(%rbp), %xmm1
	movsd	.LC280(%rip), %xmm0
	divsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -68(%rbp)
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-56(%rbp), %xmm1
	movsd	.LC281(%rip), %xmm0
	divsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -72(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1068
.L1075:
	movq	-1992(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -1968(%rbp)
	movq	%rdx, -1960(%rbp)
	movss	-1964(%rbp), %xmm0
	movss	-112(%rbp), %xmm1
	subss	%xmm1, %xmm0
	mulss	-72(%rbp), %xmm0
	movd	%xmm0, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	addl	$3, %eax
	movl	%eax, -84(%rbp)
	movss	-1960(%rbp), %xmm0
	movss	-108(%rbp), %xmm1
	subss	%xmm1, %xmm0
	mulss	-68(%rbp), %xmm0
	movd	%xmm0, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	addl	$3, %eax
	movl	%eax, -88(%rbp)
	cmpl	$0, -84(%rbp)
	jle	.L1088
	cmpl	$48, -84(%rbp)
	jg	.L1088
	cmpl	$0, -88(%rbp)
	jle	.L1089
	cmpl	$38, -88(%rbp)
	jg	.L1089
	movl	-84(%rbp), %eax
	movslq	%eax, %rcx
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rbp, %rax
	addq	%rcx, %rax
	subq	$1936, %rax
	movb	$1, (%rax)
	jmp	.L1074
.L1088:
	nop
	jmp	.L1074
.L1089:
	nop
.L1074:
	addl	$1, -4(%rbp)
.L1068:
	movq	-1992(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1075
	leaq	-1936(%rbp), %rdx
	movq	-2000(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeImage@PLT
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1076
.L1087:
	leaq	-1936(%rbp), %rax
	leaq	imageWithFrame(%rip), %rdx
	movl	$228, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	jmp	.L1077
.L1086:
	movq	-1992(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -1984(%rbp)
	movq	%rdx, -1976(%rbp)
	movss	-1980(%rbp), %xmm0
	movss	-112(%rbp), %xmm1
	subss	%xmm1, %xmm0
	mulss	-72(%rbp), %xmm0
	movd	%xmm0, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	addl	$3, %eax
	movl	%eax, -76(%rbp)
	movss	-1976(%rbp), %xmm0
	movss	-108(%rbp), %xmm1
	subss	%xmm1, %xmm0
	mulss	-68(%rbp), %xmm0
	movd	%xmm0, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	addl	$3, %eax
	movl	%eax, -80(%rbp)
	cmpl	$0, -76(%rbp)
	jle	.L1090
	cmpl	$48, -76(%rbp)
	jg	.L1090
	cmpl	$0, -80(%rbp)
	jle	.L1091
	cmpl	$38, -80(%rbp)
	jg	.L1091
	movl	-1984(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	jne	.L1092
	movl	-76(%rbp), %eax
	movslq	%eax, %rcx
	movl	-80(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rbp, %rax
	addq	%rcx, %rax
	subq	$1936, %rax
	movb	$1, (%rax)
	jmp	.L1085
.L1090:
	nop
	jmp	.L1085
.L1091:
	nop
.L1085:
	addl	$1, -8(%rbp)
.L1077:
	movq	-1992(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L1086
	jmp	.L1084
.L1092:
	nop
.L1084:
	leaq	-1936(%rbp), %rdx
	movq	-2000(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	writeImage@PLT
	addl	$1, -4(%rbp)
.L1076:
	movq	-1992(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1087
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE124:
	.size	writePecStitches, .-writePecStitches
	.section	.rodata
.LC283:
	.string	"#PEC0001"
	.text
	.globl	writePec
	.type	writePec, @function
writePec:
.LFB125:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_fixColorCount@PLT
	movq	-8(%rbp), %rax
	movss	.LC282(%rip), %xmm1
	movl	.LC224(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_correctForMaxStitchLength@PLT
	movq	-8(%rbp), %rax
	movl	.LC18(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_scale@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rcx
	movl	$8, %edx
	movl	$1, %esi
	leaq	.LC283(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	writePecStitches
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE125:
	.size	writePec, .-writePec
	.section	.rodata
	.align 8
.LC284:
	.string	"ERROR: readPel is not implemented."
.LC285:
	.string	"%p, %p\n"
	.text
	.globl	readPel
	.type	readPel, @function
readPel:
.LFB126:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC284(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC285(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE126:
	.size	readPel, .-readPel
	.section	.rodata
	.align 8
.LC286:
	.string	"ERROR: writePel is not implemented."
	.text
	.globl	writePel
	.type	writePel, @function
writePel:
.LFB127:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC286(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC285(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE127:
	.size	writePel, .-writePel
	.section	.rodata
	.align 8
.LC287:
	.string	"ERROR: readPem is not implemented."
	.text
	.globl	readPem
	.type	readPem, @function
readPem:
.LFB128:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC287(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC285(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE128:
	.size	readPem, .-readPem
	.section	.rodata
	.align 8
.LC288:
	.string	"ERROR: writePem is not implemented."
	.text
	.globl	writePem
	.type	writePem, @function
writePem:
.LFB129:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC288(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC285(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE129:
	.size	writePem, .-writePem
	.globl	pes_version_strings
	.section	.rodata
.LC289:
	.string	"#PES0001"
.LC290:
	.string	"#PES0020"
.LC291:
	.string	"#PES0022"
.LC292:
	.string	"#PES0030"
.LC293:
	.string	"#PES0040"
.LC294:
	.string	"#PES0050"
.LC295:
	.string	"#PES0055"
.LC296:
	.string	"#PES0056"
.LC297:
	.string	"#PES0060"
.LC298:
	.string	"#PES0070"
.LC299:
	.string	"#PES0080"
.LC300:
	.string	"#PES0090"
.LC301:
	.string	"#PES0100"
	.section	.data.rel.local,"aw"
	.align 32
	.type	pes_version_strings, @object
	.size	pes_version_strings, 104
pes_version_strings:
	.quad	.LC289
	.quad	.LC290
	.quad	.LC291
	.quad	.LC292
	.quad	.LC293
	.quad	.LC294
	.quad	.LC295
	.quad	.LC296
	.quad	.LC297
	.quad	.LC298
	.quad	.LC299
	.quad	.LC300
	.quad	.LC301
	.globl	pes_version
	.bss
	.align 4
	.type	pes_version, @object
	.size	pes_version, 4
pes_version:
	.zero	4
	.section	.rodata
.LC302:
	.string	"%s"
	.align 8
.LC303:
	.string	"ERROR PES: failed to read signature."
	.align 8
.LC304:
	.string	"ERROR PES: failed to read descriptions."
	.text
	.globl	readPes
	.type	readPes, @function
readPes:
.LFB130:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%rdx, -72(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC302(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-72(%rbp), %rdx
	leaq	-33(%rbp), %rax
	movq	%rdx, %rcx
	movl	$8, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$8, %rax
	je	.L1104
	leaq	.LC303(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1123
.L1104:
	movb	$0, -25(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -20(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L1106
.L1109:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	pes_version_strings(%rip), %rax
	movq	(%rdx,%rax), %rdx
	leaq	-33(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L1107
	movl	-12(%rbp), %eax
	movl	%eax, -8(%rbp)
	jmp	.L1108
.L1107:
	addl	$1, -12(%rbp)
.L1106:
	cmpl	$12, -12(%rbp)
	jle	.L1109
.L1108:
	cmpl	$3, -8(%rbp)
	jle	.L1110
	movq	-72(%rbp), %rax
	movl	$0, %edx
	movl	$16, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-56(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	read_descriptions
	testl	%eax, %eax
	jne	.L1110
	leaq	.LC304(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1123
.L1110:
	movl	-8(%rbp), %eax
	subl	$5, %eax
	cmpl	$7, %eax
	ja	.L1124
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L1113(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L1113(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L1113:
	.long	.L1118-.L1113
	.long	.L1118-.L1113
	.long	.L1118-.L1113
	.long	.L1117-.L1113
	.long	.L1116-.L1113
	.long	.L1115-.L1113
	.long	.L1114-.L1113
	.long	.L1112-.L1113
	.text
.L1112:
	movq	-56(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPESHeaderV10
	jmp	.L1119
.L1114:
	movq	-56(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPESHeaderV9
	jmp	.L1119
.L1115:
	movq	-56(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPESHeaderV8
	jmp	.L1119
.L1116:
	movq	-56(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPESHeaderV7
	jmp	.L1119
.L1117:
	movq	-56(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPESHeaderV6
	jmp	.L1119
.L1118:
	movq	-56(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPESHeaderV5
	jmp	.L1119
.L1124:
	nop
.L1119:
	movl	-20(%rbp), %eax
	movslq	%eax, %rcx
	movq	-72(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	addl	$1, %eax
	movl	%eax, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1120
.L1122:
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -16(%rbp)
	movl	$65, %eax
	cmpl	%eax, -16(%rbp)
	jl	.L1121
	movl	$0, -16(%rbp)
.L1121:
	movq	-56(%rbp), %r8
	subq	$8, %rsp
	movl	-16(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	leaq	pec_colors(%rip), %rcx
	subq	$408, %rsp
	movq	%rsp, %rdx
	addq	%rcx, %rax
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
	addl	$1, -4(%rbp)
.L1120:
	movl	-4(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L1122
	movl	-20(%rbp), %eax
	addl	$528, %eax
	movslq	%eax, %rcx
	movq	-72(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-72(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPecStitches
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movl	$1, %eax
.L1123:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE130:
	.size	readPes, .-readPes
	.globl	read_descriptions
	.type	read_descriptions, @function
read_descriptions:
.LFB131:
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
	call	fgetc@PLT
	cltq
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rax
	leaq	10136(%rax), %rdi
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movq	%rax, %rdx
	movl	$1, %esi
	call	fread@PLT
	cmpq	%rax, -8(%rbp)
	je	.L1126
	movl	$0, %eax
	jmp	.L1127
.L1126:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	cltq
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rax
	leaq	10336(%rax), %rdi
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movq	%rax, %rdx
	movl	$1, %esi
	call	fread@PLT
	cmpq	%rax, -8(%rbp)
	je	.L1128
	movl	$0, %eax
	jmp	.L1127
.L1128:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	cltq
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rax
	leaq	10536(%rax), %rdi
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movq	%rax, %rdx
	movl	$1, %esi
	call	fread@PLT
	cmpq	%rax, -8(%rbp)
	je	.L1129
	movl	$0, %eax
	jmp	.L1127
.L1129:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	cltq
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rax
	leaq	10736(%rax), %rdi
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movq	%rax, %rdx
	movl	$1, %esi
	call	fread@PLT
	cmpq	%rax, -8(%rbp)
	je	.L1130
	movl	$0, %eax
	jmp	.L1127
.L1130:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	cltq
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rax
	leaq	10936(%rax), %rdi
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movq	%rax, %rdx
	movl	$1, %esi
	call	fread@PLT
	cmpq	%rax, -8(%rbp)
	je	.L1131
	movl	$0, %eax
	jmp	.L1127
.L1131:
	movl	$1, %eax
.L1127:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE131:
	.size	read_descriptions, .-read_descriptions
	.globl	readPESHeaderV5
	.type	readPESHeaderV5, @function
readPESHeaderV5:
.LFB132:
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
	movl	$1, %edx
	movl	$24, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movl	$24, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readProgrammableFills
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readMotifPatterns
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readFeatherPatterns
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readThreads
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE132:
	.size	readPESHeaderV5, .-readPESHeaderV5
	.globl	readPESHeaderV6
	.type	readPESHeaderV6, @function
readPESHeaderV6:
.LFB133:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$36, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readImageString
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$24, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readProgrammableFills
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readMotifPatterns
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readFeatherPatterns
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readThreads
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE133:
	.size	readPESHeaderV6, .-readPESHeaderV6
	.globl	readPESHeaderV7
	.type	readPESHeaderV7, @function
readPESHeaderV7:
.LFB134:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$36, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readImageString
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$24, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readProgrammableFills
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readMotifPatterns
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readFeatherPatterns
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readThreads
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE134:
	.size	readPESHeaderV7, .-readPESHeaderV7
	.globl	readPESHeaderV8
	.type	readPESHeaderV8, @function
readPESHeaderV8:
.LFB135:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$38, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readImageString
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$26, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readProgrammableFills
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readMotifPatterns
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readFeatherPatterns
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readThreads
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE135:
	.size	readPESHeaderV8, .-readPESHeaderV8
	.globl	readPESHeaderV9
	.type	readPESHeaderV9, @function
readPESHeaderV9:
.LFB136:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$14, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readHoopName
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$30, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readImageString
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$34, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readProgrammableFills
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readMotifPatterns
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readFeatherPatterns
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readThreads
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE136:
	.size	readPESHeaderV9, .-readPESHeaderV9
	.globl	readPESHeaderV10
	.type	readPESHeaderV10, @function
readPESHeaderV10:
.LFB137:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$14, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readHoopName
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$38, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readImageString
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$34, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readProgrammableFills
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readMotifPatterns
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readFeatherPatterns
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readThreads
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE137:
	.size	readPESHeaderV10, .-readPESHeaderV10
	.section	.rodata
.LC305:
	.string	"Called with: (%p, %p)"
	.text
	.globl	readHoopName
	.type	readHoopName, @function
readHoopName:
.LFB138:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1140
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC305(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1140:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE138:
	.size	readHoopName, .-readHoopName
	.globl	readImageString
	.type	readImageString, @function
readImageString:
.LFB139:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1143
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC305(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1143:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE139:
	.size	readImageString, .-readImageString
	.globl	readProgrammableFills
	.type	readProgrammableFills, @function
readProgrammableFills:
.LFB140:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1145
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC305(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1145:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE140:
	.size	readProgrammableFills, .-readProgrammableFills
	.globl	readMotifPatterns
	.type	readMotifPatterns, @function
readMotifPatterns:
.LFB141:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1148
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC305(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1148:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE141:
	.size	readMotifPatterns, .-readMotifPatterns
	.globl	readFeatherPatterns
	.type	readFeatherPatterns, @function
readFeatherPatterns:
.LFB142:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1151
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC305(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1151:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE142:
	.size	readFeatherPatterns, .-readFeatherPatterns
	.section	.rodata
.LC306:
	.string	"color code length: %d\n"
	.align 8
.LC307:
	.string	"description string length: %d\n"
.LC308:
	.string	"brand string length: %d\n"
	.align 8
.LC309:
	.string	"thread chart string length: %d\n"
	.text
	.globl	readThreads
	.type	readThreads, @function
readThreads:
.LFB143:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$448, %rsp
	movq	%rdi, -440(%rbp)
	movq	%rsi, -448(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1154
	movq	-448(%rbp), %rdx
	movq	-440(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC305(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1154:
	movq	-440(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1155
.L1157:
	movq	-440(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -12(%rbp)
	movq	-440(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -432(%rbp)
	movq	-440(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -431(%rbp)
	movq	-440(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -430(%rbp)
	movq	-440(%rbp), %rax
	movl	$1, %edx
	movl	$5, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-440(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -16(%rbp)
	movq	-440(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -20(%rbp)
	movq	-440(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -24(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1156
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC306(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-16(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC307(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC308(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC309(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1156:
	movq	-448(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-432(%rbp), %rax
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
	addl	$1, -4(%rbp)
.L1155:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L1157
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE143:
	.size	readThreads, .-readThreads
	.section	.rodata
.LC310:
	.string	"CSewSeg"
	.align 8
.LC311:
	.string	"Color count exceeds 1000 this is likely an error. Truncating to 1000."
	.align 8
.LC312:
	.string	"Ran out of memory for color info."
	.text
	.globl	pesWriteSewSegSection
	.type	pesWriteSewSegSection, @function
pesWriteSewSegSection:
.LFB144:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$160, %rsp
	movq	%rdi, -152(%rbp)
	movq	%rsi, -160(%rbp)
	movq	$0, -40(%rbp)
	movl	$0, -44(%rbp)
	movl	$0, -4(%rbp)
	movl	$-1, -8(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	movl	$0, -20(%rbp)
	movl	$0, -48(%rbp)
	movl	$0, -24(%rbp)
	leaq	-80(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_bounds@PLT
	movl	$0, -28(%rbp)
	jmp	.L1159
.L1166:
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -112(%rbp)
	movq	%rdx, -104(%rbp)
	movl	-112(%rbp), %eax
	movl	%eax, -44(%rbp)
	movl	-100(%rbp), %edx
	movq	-152(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, %edx
	jge	.L1160
	movq	-152(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-100(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -83(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -81(%rbp)
	jmp	.L1161
.L1160:
	movzwl	pec_colors(%rip), %eax
	movw	%ax, -83(%rbp)
	movzbl	2+pec_colors(%rip), %eax
	movb	%al, -81(%rbp)
.L1161:
	movl	$65, %eax
	movl	%eax, %edx
	leaq	pec_colors(%rip), %rax
	movq	%rax, %rsi
	movzbl	-83(%rbp), %eax
	movzbl	-82(%rbp), %ecx
	salq	$8, %rcx
	orq	%rax, %rcx
	movzbl	-81(%rbp), %eax
	salq	$16, %rax
	orq	%rcx, %rax
	movq	%rax, %rdi
	call	emb_find_nearest_thread@PLT
	movl	%eax, -48(%rbp)
	movl	-48(%rbp), %eax
	cmpl	-8(%rbp), %eax
	je	.L1163
	addl	$1, -20(%rbp)
	movl	-48(%rbp), %eax
	movl	%eax, -8(%rbp)
	jmp	.L1163
.L1165:
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -112(%rbp)
	movq	%rdx, -104(%rbp)
	addl	$1, -4(%rbp)
	addl	$1, -28(%rbp)
.L1163:
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -28(%rbp)
	jge	.L1164
	movl	-112(%rbp), %eax
	cmpl	%eax, -44(%rbp)
	je	.L1165
.L1164:
	addl	$1, -16(%rbp)
	addl	$1, -28(%rbp)
.L1159:
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -28(%rbp)
	jl	.L1166
	movl	-16(%rbp), %eax
	movswl	%ax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-160(%rbp), %rax
	movl	$65535, %esi
	movq	%rax, %rdi
	call	emb_write_u16@PLT
	movq	-160(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-160(%rbp), %rax
	movl	$7, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-160(%rbp), %rax
	movq	%rax, %rcx
	movl	$7, %edx
	movl	$1, %esi
	leaq	.LC310(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	cmpl	$1000, -20(%rbp)
	jle	.L1167
	leaq	.LC311(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1000, -20(%rbp)
.L1167:
	movl	-20(%rbp), %eax
	addl	%eax, %eax
	cltq
	movl	$2, %esi
	movq	%rax, %rdi
	call	calloc@PLT
	movq	%rax, -40(%rbp)
	movl	$-1, -8(%rbp)
	movl	$0, -16(%rbp)
	movl	$0, -28(%rbp)
	jmp	.L1168
.L1182:
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -144(%rbp)
	movq	%rdx, -136(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, -32(%rbp)
	movl	-144(%rbp), %eax
	movl	%eax, -44(%rbp)
	movq	-152(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-132(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -115(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -113(%rbp)
	movl	$65, %eax
	movl	%eax, %edx
	leaq	pec_colors(%rip), %rax
	movq	%rax, %rsi
	movzbl	-115(%rbp), %eax
	movzbl	-114(%rbp), %ecx
	salq	$8, %rcx
	orq	%rax, %rcx
	movzbl	-113(%rbp), %eax
	salq	$16, %rax
	orq	%rcx, %rax
	movq	%rax, %rdi
	call	emb_find_nearest_thread@PLT
	movl	%eax, -48(%rbp)
	movl	-48(%rbp), %eax
	cmpl	-8(%rbp), %eax
	je	.L1169
	movl	-24(%rbp), %eax
	leal	1(%rax), %edx
	movl	-20(%rbp), %eax
	addl	%eax, %eax
	cmpl	%eax, %edx
	jl	.L1170
	leaq	.LC312(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L1171
.L1170:
	movl	-24(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -24(%rbp)
	cltq
	leaq	(%rax,%rax), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	-16(%rbp), %edx
	movw	%dx, (%rax)
	movl	-24(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -24(%rbp)
	cltq
	leaq	(%rax,%rax), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	-48(%rbp), %edx
	movw	%dx, (%rax)
	movl	-48(%rbp), %eax
	movl	%eax, -8(%rbp)
.L1169:
	movl	$0, -4(%rbp)
	jmp	.L1172
.L1174:
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -144(%rbp)
	movq	%rdx, -136(%rbp)
	addl	$1, -4(%rbp)
	addl	$1, -32(%rbp)
.L1172:
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -32(%rbp)
	jge	.L1173
	movl	-144(%rbp), %eax
	cmpl	%eax, -44(%rbp)
	je	.L1174
.L1173:
	movl	-44(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L1175
	movl	$1, -12(%rbp)
	jmp	.L1176
.L1175:
	movl	$0, -12(%rbp)
.L1176:
	movl	-12(%rbp), %eax
	movswl	%ax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movl	-8(%rbp), %eax
	movswl	%ax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movl	-4(%rbp), %eax
	movswl	%ax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movl	-28(%rbp), %eax
	movl	%eax, -32(%rbp)
	jmp	.L1177
.L1180:
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -144(%rbp)
	movq	%rdx, -136(%rbp)
	movl	-144(%rbp), %eax
	cmpl	%eax, -44(%rbp)
	jne	.L1185
	movss	-140(%rbp), %xmm0
	movss	-80(%rbp), %xmm1
	subss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %eax
	movswl	%ax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movss	-136(%rbp), %xmm1
	movss	-76(%rbp), %xmm0
	addss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %eax
	movswl	%ax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	addl	$1, -32(%rbp)
.L1177:
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -32(%rbp)
	jl	.L1180
	jmp	.L1179
.L1185:
	nop
.L1179:
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -32(%rbp)
	jge	.L1181
	movq	-160(%rbp), %rax
	movl	$32771, %esi
	movq	%rax, %rdi
	call	emb_write_u16@PLT
.L1181:
	addl	$1, -16(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, -28(%rbp)
	addl	$1, -28(%rbp)
.L1168:
	movq	-152(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -28(%rbp)
	jl	.L1182
.L1171:
	movl	-20(%rbp), %eax
	movswl	%ax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movl	$0, -28(%rbp)
	jmp	.L1183
.L1184:
	movl	-28(%rbp), %eax
	addl	%eax, %eax
	cltq
	leaq	(%rax,%rax), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movswl	%ax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movl	-28(%rbp), %eax
	addl	%eax, %eax
	cltq
	addq	$1, %rax
	leaq	(%rax,%rax), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movswl	%ax, %edx
	movq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	addl	$1, -28(%rbp)
.L1183:
	movl	-28(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L1184
	movq	-160(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE144:
	.size	pesWriteSewSegSection, .-pesWriteSewSegSection
	.section	.rodata
.LC313:
	.string	"CEmbOne"
	.text
	.globl	pesWriteEmbOneSection
	.type	pesWriteEmbOneSection, @function
pesWriteEmbOneSection:
.LFB145:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$1800, -4(%rbp)
	movl	$1300, -8(%rbp)
	movq	-48(%rbp), %rax
	movl	$7, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rcx
	movl	$7, %edx
	movl	$1, %esi
	leaq	.LC313(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	leaq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_bounds@PLT
	movq	-48(%rbp), %rax
	movl	$16, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-48(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-48(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-48(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-48(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movss	-24(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2ssl	-8(%rbp), %xmm1
	subss	%xmm1, %xmm0
	movss	.LC314(%rip), %xmm1
	divss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-48(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movss	-20(%rbp), %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-4(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	.LC314(%rip), %xmm1
	divss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-48(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-48(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-48(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-48(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movss	-24(%rbp), %xmm0
	cvttss2sil	%xmm0, %eax
	movswl	%ax, %edx
	movq	-48(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movss	-20(%rbp), %xmm0
	cvttss2sil	%xmm0, %eax
	movswl	%ax, %edx
	movq	-48(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-48(%rbp), %rax
	movl	$8, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE145:
	.size	pesWriteEmbOneSection, .-pesWriteEmbOneSection
	.globl	writePes
	.type	writePes, @function
writePes:
.LFB146:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movq	-24(%rbp), %rax
	movl	.LC18(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_scale@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rcx
	movl	$8, %edx
	movl	$1, %esi
	leaq	.LC289(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-40(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-40(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-40(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-40(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-40(%rbp), %rax
	movl	$65535, %esi
	movq	%rax, %rdi
	call	emb_write_u16@PLT
	movq	-40(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	pesWriteEmbOneSection
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	pesWriteSewSegSection
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -4(%rbp)
	movq	-40(%rbp), %rax
	movl	$0, %edx
	movl	$8, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	-4(%rbp), %eax
	movzbl	%al, %eax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc@PLT
	movl	-4(%rbp), %eax
	sarl	$8, %eax
	movzbl	%al, %eax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc@PLT
	movl	-4(%rbp), %eax
	sarl	$16, %eax
	movzbl	%al, %eax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc@PLT
	movq	-40(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	writePecStitches
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE146:
	.size	writePes, .-writePes
	.section	.rodata
.LC315:
	.string	"stor: %d\n"
	.text
	.globl	readPhb
	.type	readPhb, @function
readPhb:
.LFB147:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$432, %rsp
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	-432(%rbp), %rax
	movl	$0, %edx
	movl	$113, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-432(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -6(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1190
.L1191:
	movq	-432(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	cltq
	imulq	$403, %rax, %rdx
	leaq	pec_colors(%rip), %rcx
	leaq	-416(%rbp), %rax
	addq	%rcx, %rdx
	movl	$50, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	movq	%rsi, %rdx
	movq	%rdi, %rax
	movzwl	(%rdx), %ecx
	movw	%cx, (%rax)
	leaq	2(%rax), %rax
	leaq	2(%rdx), %rdx
	movzbl	(%rdx), %ecx
	movb	%cl, (%rax)
	movq	-424(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-416(%rbp), %rax
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
	addl	$1, -4(%rbp)
.L1190:
	movswl	-6(%rbp), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1191
	movq	-432(%rbp), %rax
	movl	$0, %edx
	movl	$84, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	$82, -12(%rbp)
	movq	-432(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	addl	%eax, -12(%rbp)
	movl	-12(%rbp), %ecx
	movq	-432(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-432(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	addl	$2, %eax
	addl	%eax, -12(%rbp)
	movl	-12(%rbp), %ecx
	movq	-432(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-432(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	addl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	addl	$14, %eax
	movl	%eax, %ecx
	movq	-432(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-432(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	cbtw
	movw	%ax, -6(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1192
.L1194:
	movq	-432(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -13(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1193
	movsbl	-13(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC315(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1193:
	addl	$1, -4(%rbp)
.L1192:
	movswl	-6(%rbp), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1194
	movq	-432(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-432(%rbp), %rax
	movl	$1, %edx
	movl	$17, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-432(%rbp), %rdx
	movq	-424(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPecStitches
	movq	-424(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE147:
	.size	readPhb, .-readPhb
	.section	.rodata
	.align 8
.LC316:
	.string	"ERROR: writePhb is not implemented."
	.text
	.globl	writePhb
	.type	writePhb, @function
writePhb:
.LFB148:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC316(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1197
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC151(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1197:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE148:
	.size	writePhb, .-writePhb
	.section	.rodata
.LC317:
	.string	"colorChanges: %d\n"
.LC318:
	.string	"fileLength: %d\n"
.LC319:
	.string	"pecOffset: %d\n"
.LC320:
	.string	"bytesInSection: %d\n"
.LC321:
	.string	"bytesInSection3: %d\n"
	.text
	.globl	readPhc
	.type	readPhc, @function
readPhc:
.LFB149:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$464, %rsp
	movq	%rdi, -456(%rbp)
	movq	%rsi, -464(%rbp)
	movq	-464(%rbp), %rax
	movl	$0, %edx
	movl	$7, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movsbl	%al, %eax
	subl	$48, %eax
	movl	%eax, -8(%rbp)
	movq	-464(%rbp), %rax
	movl	$0, %edx
	movl	$77, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movzwl	%ax, %eax
	movl	%eax, -12(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1200
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC317(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1200:
	movl	$0, -4(%rbp)
	jmp	.L1201
.L1202:
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movsbl	%al, %eax
	cltq
	imulq	$403, %rax, %rdx
	leaq	pec_colors(%rip), %rcx
	leaq	-448(%rbp), %rax
	addq	%rcx, %rdx
	movl	$50, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	movq	%rsi, %rdx
	movq	%rdi, %rax
	movzwl	(%rdx), %ecx
	movw	%cx, (%rax)
	leaq	2(%rax), %rax
	leaq	2(%rdx), %rdx
	movzbl	(%rdx), %ecx
	movb	%cl, (%rax)
	movq	-456(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-448(%rbp), %rax
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
	addl	$1, -4(%rbp)
.L1201:
	movl	-4(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jl	.L1202
	movq	-464(%rbp), %rax
	movl	$0, %edx
	movl	$43, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -13(%rbp)
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -20(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1203
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC318(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1203:
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movw	%ax, -22(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1204
	movzwl	-22(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC319(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1204:
	movzwl	-22(%rbp), %edx
	movsbl	-13(%rbp), %eax
	addl	%edx, %eax
	movslq	%eax, %rcx
	movq	-464(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movw	%ax, -24(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1205
	movzwl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC320(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1205:
	movzwl	-24(%rbp), %ecx
	movq	-464(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movslq	%eax, %rcx
	movq	-464(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movw	%ax, -30(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1206
	movzwl	-30(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC321(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1206:
	movzwl	-30(%rbp), %eax
	addl	$18, %eax
	movslq	%eax, %rcx
	movq	-464(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1207
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC257(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1207:
	movq	-464(%rbp), %rdx
	movq	-456(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readPecStitches
	movq	-456(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE149:
	.size	readPhc, .-readPhc
	.section	.rodata
	.align 8
.LC322:
	.string	"ERROR: writePhc is not implemented."
	.text
	.globl	writePhc
	.type	writePhc, @function
writePhc:
.LFB150:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC322(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1210
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC151(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1210:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE150:
	.size	writePhc, .-writePhc
	.section	.rodata
.LC324:
	.string	"PD%f,%f;"
.LC325:
	.string	"PU%f,%f;"
	.text
	.globl	readPlt
	.type	readPlt, @function
readPlt:
.LFB151:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$544, %rsp
	movq	%rdi, -536(%rbp)
	movq	%rsi, -544(%rbp)
	movss	.LC323(%rip), %xmm0
	movss	%xmm0, -4(%rbp)
	jmp	.L1213
.L1218:
	movzbl	-528(%rbp), %eax
	cmpb	$80, %al
	jne	.L1214
	movzbl	-527(%rbp), %eax
	cmpb	$68, %al
	jne	.L1214
	leaq	-12(%rbp), %rcx
	leaq	-8(%rbp), %rdx
	leaq	-528(%rbp), %rax
	leaq	.LC324(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf@PLT
	cmpl	$1, %eax
	jle	.L1220
	movss	-12(%rbp), %xmm0
	movaps	%xmm0, %xmm1
	divss	-4(%rbp), %xmm1
	movss	-8(%rbp), %xmm0
	divss	-4(%rbp), %xmm0
	movd	%xmm0, %ecx
	movq	-536(%rbp), %rax
	movl	$1, %edx
	movl	$0, %esi
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
	jmp	.L1213
.L1214:
	movzbl	-528(%rbp), %eax
	cmpb	$80, %al
	jne	.L1213
	movzbl	-527(%rbp), %eax
	cmpb	$85, %al
	jne	.L1213
	leaq	-12(%rbp), %rcx
	leaq	-8(%rbp), %rdx
	leaq	-528(%rbp), %rax
	leaq	.LC325(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_sscanf@PLT
	cmpl	$1, %eax
	jle	.L1221
	movss	-12(%rbp), %xmm0
	movaps	%xmm0, %xmm1
	divss	-4(%rbp), %xmm1
	movss	-8(%rbp), %xmm0
	divss	-4(%rbp), %xmm0
	movd	%xmm0, %ecx
	movq	-536(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
.L1213:
	leaq	-528(%rbp), %rcx
	movq	-544(%rbp), %rax
	movl	$511, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_readline@PLT
	testl	%eax, %eax
	jne	.L1218
	jmp	.L1216
.L1220:
	nop
	jmp	.L1216
.L1221:
	nop
.L1216:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE151:
	.size	readPlt, .-readPlt
	.section	.rodata
.LC326:
	.string	"IN;"
.LC327:
	.string	"ND;"
.LC328:
	.string	"ST0.00,0.00;"
.LC329:
	.string	"SP0;"
.LC330:
	.string	"HT0;"
.LC331:
	.string	"HS0;"
.LC332:
	.string	"TT0;"
.LC333:
	.string	"TS0;"
.LC334:
	.string	"PU0.0,0.0;"
	.text
	.globl	writePlt
	.type	writePlt, @function
writePlt:
.LFB152:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movss	.LC323(%rip), %xmm0
	movss	%xmm0, -12(%rbp)
	movb	$1, -1(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	leaq	.LC326(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	leaq	.LC327(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$0, -8(%rbp)
	jmp	.L1223
.L1227:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movl	-32(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L1224
	movb	$1, -1(%rbp)
.L1224:
	cmpb	$0, -1(%rbp)
	je	.L1225
	movss	-24(%rbp), %xmm0
	mulss	-12(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-28(%rbp), %xmm0
	mulss	-12(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movq	%xmm2, %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, %xmm0
	leaq	.LC325(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rcx
	movl	$12, %edx
	movl	$1, %esi
	leaq	.LC328(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	leaq	.LC329(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	leaq	.LC330(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	leaq	.LC331(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	leaq	.LC332(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	leaq	.LC333(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movb	$0, -1(%rbp)
	jmp	.L1226
.L1225:
	movss	-24(%rbp), %xmm0
	mulss	-12(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-28(%rbp), %xmm0
	mulss	-12(%rbp), %xmm0
	pxor	%xmm3, %xmm3
	cvtss2sd	%xmm0, %xmm3
	movq	%xmm3, %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, %xmm0
	leaq	.LC324(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
.L1226:
	addl	$1, -8(%rbp)
.L1223:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L1227
	movq	-48(%rbp), %rax
	movq	%rax, %rcx
	movl	$10, %edx
	movl	$1, %esi
	leaq	.LC334(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rcx
	movl	$10, %edx
	movl	$1, %esi
	leaq	.LC334(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE152:
	.size	writePlt, .-writePlt
	.globl	readRgb
	.type	readRgb, @function
readRgb:
.LFB153:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$432, %rsp
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	-432(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-432(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	leaq	3(%rax), %rdx
	testq	%rax, %rax
	cmovs	%rdx, %rax
	sarq	$2, %rax
	movl	%eax, -8(%rbp)
	movq	-424(%rbp), %rax
	movq	24(%rax), %rax
	movl	$0, 24(%rax)
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC171(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-432(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	$0, -4(%rbp)
	jmp	.L1230
.L1231:
	leaq	-416(%rbp), %rcx
	movq	-432(%rbp), %rax
	movl	$4, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_read@PLT
	movb	$0, -213(%rbp)
	movb	$0, -413(%rbp)
	movq	-424(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-416(%rbp), %rax
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
	addl	$1, -4(%rbp)
.L1230:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L1231
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE153:
	.size	readRgb, .-readRgb
	.globl	writeRgb
	.type	writeRgb, @function
writeRgb:
.LFB154:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1234
.L1235:
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -7(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -5(%rbp)
	movq	-32(%rbp), %rax
	movl	$4, %edx
	movzbl	-7(%rbp), %ecx
	movzbl	-6(%rbp), %esi
	salq	$8, %rsi
	orq	%rcx, %rsi
	movzbl	-5(%rbp), %ecx
	salq	$16, %rcx
	orq	%rsi, %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_write@PLT
	addl	$1, -4(%rbp)
.L1234:
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1235
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE154:
	.size	writeRgb, .-writeRgb
	.globl	sewDecode
	.type	sewDecode, @function
sewDecode:
.LFB155:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE155:
	.size	sewDecode, .-sewDecode
	.section	.rodata
.LC335:
	.string	"current position: %ld\n"
	.text
	.globl	readSew
	.type	readSew, @function
readSew:
.LFB156:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movb	$0, -9(%rbp)
	movq	-48(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -16(%rbp)
	movq	-48(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -20(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	sall	$8, %eax
	addl	%eax, -20(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1240
.L1241:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$-770891565, %rdx, %rdx
	shrq	$32, %rdx
	addl	%eax, %edx
	sarl	$6, %edx
	movl	%eax, %ecx
	sarl	$31, %ecx
	subl	%ecx, %edx
	imull	$78, %edx, %ecx
	subl	%ecx, %eax
	movl	%eax, %edx
	movq	-40(%rbp), %r8
	subq	$8, %rsp
	movslq	%edx, %rax
	imulq	$403, %rax, %rax
	leaq	jef_colors(%rip), %rcx
	subq	$408, %rsp
	movq	%rsp, %rdx
	addq	%rcx, %rax
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
	addl	$1, -4(%rbp)
.L1240:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L1241
	movq	-48(%rbp), %rax
	movl	$0, %edx
	movl	$7544, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	$0, -4(%rbp)
	jmp	.L1242
.L1251:
	movq	-48(%rbp), %rdx
	leaq	-30(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movl	$0, -8(%rbp)
	cmpb	$0, -9(%rbp)
	je	.L1243
	movl	$2, -8(%rbp)
	movb	$0, -9(%rbp)
.L1243:
	movzbl	-30(%rbp), %eax
	cmpb	$-128, %al
	jne	.L1244
	movzbl	-29(%rbp), %eax
	cmpb	$1, %al
	jne	.L1245
	movq	-48(%rbp), %rdx
	leaq	-30(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movl	$4, -8(%rbp)
	jmp	.L1244
.L1245:
	movzbl	-29(%rbp), %eax
	cmpb	$2, %al
	je	.L1246
	movzbl	-29(%rbp), %eax
	cmpb	$4, %al
	jne	.L1247
.L1246:
	movb	$1, -9(%rbp)
	movq	-48(%rbp), %rdx
	leaq	-30(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movl	$2, -8(%rbp)
	jmp	.L1244
.L1247:
	movzbl	-29(%rbp), %eax
	cmpb	$16, %al
	je	.L1253
.L1244:
	movzbl	-30(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	sewDecode
	movb	%al, -21(%rbp)
	movzbl	-29(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	sewDecode
	movb	%al, -22(%rbp)
	movzbl	-21(%rbp), %eax
	movl	%eax, %edx
	negb	%dl
	cmovns	%edx, %eax
	cmpb	$127, %al
	je	.L1249
	movzbl	-22(%rbp), %eax
	movl	%eax, %edx
	negb	%dl
	cmovns	%edx, %eax
	cmpb	$127, %al
	jne	.L1250
.L1249:
	movb	$1, -9(%rbp)
	movl	$2, -8(%rbp)
.L1250:
	movsbl	-22(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movsbl	-21(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-8(%rbp), %esi
	movq	-40(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	addl	$1, -4(%rbp)
.L1242:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rdx
	movl	-16(%rbp), %eax
	cltq
	cmpq	%rax, %rdx
	jl	.L1251
	jmp	.L1248
.L1253:
	nop
.L1248:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rsi
	leaq	.LC335(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE156:
	.size	readSew, .-readSew
	.section	.rodata
.LC336:
	.string	"Debugging Information"
	.text
	.globl	writeSew
	.type	writeSew, @function
writeSew:
.LFB157:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	movq	-72(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movswl	%ax, %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1255
	leaq	.LC336(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-72(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, %esi
	leaq	.LC216(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, %esi
	leaq	.LC217(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1255:
	movl	$0, -4(%rbp)
	jmp	.L1256
.L1257:
	movq	-72(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -19(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -17(%rbp)
	movl	$79, %edx
	leaq	jef_colors(%rip), %rax
	movq	%rax, %rsi
	movzbl	-19(%rbp), %eax
	movzbl	-18(%rbp), %ecx
	salq	$8, %rcx
	orq	%rax, %rcx
	movzbl	-17(%rbp), %eax
	salq	$16, %rax
	orq	%rcx, %rax
	movq	%rax, %rdi
	call	emb_find_nearest_thread@PLT
	movw	%ax, -16(%rbp)
	movswl	-16(%rbp), %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	addl	$1, -4(%rbp)
.L1256:
	movq	-72(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1257
	movq	-72(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movl	$3771, %edx
	subl	%eax, %edx
	addl	%edx, %edx
	movq	-80(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movl	$0, -4(%rbp)
	jmp	.L1258
.L1264:
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movss	-44(%rbp), %xmm0
	movaps	%xmm0, %xmm1
	subss	-8(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movb	%al, -13(%rbp)
	movss	-40(%rbp), %xmm0
	movaps	%xmm0, %xmm1
	subss	-12(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movb	%al, -14(%rbp)
	pxor	%xmm1, %xmm1
	cvtss2sd	-8(%rbp), %xmm1
	movsbl	-13(%rbp), %eax
	pxor	%xmm2, %xmm2
	cvtsi2sdl	%eax, %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	pxor	%xmm1, %xmm1
	cvtss2sd	-12(%rbp), %xmm1
	movsbl	-14(%rbp), %eax
	pxor	%xmm2, %xmm2
	cvtsi2sdl	%eax, %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	movl	-48(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L1259
	movb	$-128, -52(%rbp)
	movb	$1, -51(%rbp)
	movzbl	-13(%rbp), %eax
	movb	%al, -50(%rbp)
	movzbl	-14(%rbp), %eax
	movb	%al, -49(%rbp)
	movq	-80(%rbp), %rdx
	leaq	-52(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L1260
.L1259:
	movl	-48(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L1261
	movb	$-128, -52(%rbp)
	movb	$16, -51(%rbp)
	movb	$0, -50(%rbp)
	movb	$0, -49(%rbp)
	movq	-80(%rbp), %rdx
	leaq	-52(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L1260
.L1261:
	movl	-48(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	jne	.L1262
	movl	-48(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L1263
.L1262:
	movb	$-128, -52(%rbp)
	movb	$2, -51(%rbp)
	movzbl	-13(%rbp), %eax
	movb	%al, -50(%rbp)
	movzbl	-14(%rbp), %eax
	movb	%al, -49(%rbp)
	movq	-80(%rbp), %rdx
	leaq	-52(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L1260
.L1263:
	movzbl	-13(%rbp), %eax
	movb	%al, -52(%rbp)
	movzbl	-14(%rbp), %eax
	movb	%al, -51(%rbp)
	movq	-80(%rbp), %rdx
	leaq	-52(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
.L1260:
	addl	$1, -4(%rbp)
.L1258:
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1264
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE157:
	.size	writeSew, .-writeSew
	.globl	shvDecode
	.type	shvDecode, @function
shvDecode:
.LFB158:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	testb	%al, %al
	jns	.L1267
	movzbl	-4(%rbp), %eax
	jmp	.L1268
.L1267:
	movzbl	-4(%rbp), %eax
.L1268:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE158:
	.size	shvDecode, .-shvDecode
	.globl	shvDecodeShort
	.type	shvDecodeShort, @function
shvDecodeShort:
.LFB159:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movw	%ax, -4(%rbp)
	cmpw	$-32768, -4(%rbp)
	jbe	.L1270
	movzwl	-4(%rbp), %eax
	jmp	.L1271
.L1270:
	movzwl	-4(%rbp), %eax
.L1271:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE159:
	.size	shvDecodeShort, .-shvDecodeShort
	.section	.rodata
	.align 8
.LC337:
	.string	"Embroidery disk created using software licensed from Viking Sewing Machines AB, Sweden"
.LC338:
	.string	"halfDesignWidth: %d\n"
.LC339:
	.string	"halfDesignHeight: %d\n"
.LC340:
	.string	"halfDesignWidth2: %d\n"
.LC341:
	.string	"halfDesignHeight2: %d\n"
.LC342:
	.string	"something: %d\n"
.LC343:
	.string	"something2: %d\n"
.LC344:
	.string	"numberOfSections: %d\n"
.LC345:
	.string	"something3: %d\n"
	.text
	.globl	readShv
	.type	readShv, @function
readShv:
.LFB160:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$1144, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -1128(%rbp)
	movq	%rsi, -1136(%rbp)
	movb	$0, -21(%rbp)
	leaq	.LC337(%rip), %rax
	movq	%rax, -48(%rbp)
	movb	$0, -49(%rbp)
	movb	$0, -50(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -32(%rbp)
	movq	-1136(%rbp), %rax
	movl	$25, %esi
	movq	%rax, %rdi
	call	check_header_present@PLT
	testl	%eax, %eax
	jne	.L1273
	movl	$0, %eax
	jmp	.L1307
.L1273:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rcx
	movq	-1136(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -51(%rbp)
	movzbl	-51(%rbp), %ecx
	movq	-1136(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -52(%rbp)
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -53(%rbp)
	movq	-1136(%rbp), %rdx
	leaq	-85(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L1275
	leaq	.LC188(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L1275:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1276
	movzbl	-85(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC338(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1276:
	movq	-1136(%rbp), %rdx
	leaq	-86(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L1277
	leaq	.LC188(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L1277:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1278
	movzbl	-86(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC339(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1278:
	movq	-1136(%rbp), %rdx
	leaq	-87(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L1279
	leaq	.LC188(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L1279:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1280
	movzbl	-87(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC340(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1280:
	movq	-1136(%rbp), %rdx
	leaq	-88(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L1281
	leaq	.LC188(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L1281:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1282
	movzbl	-88(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC341(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1282:
	movzbl	-53(%rbp), %eax
	andl	$1, %eax
	testb	%al, %al
	je	.L1283
	movzbl	-53(%rbp), %eax
	leal	1(%rax), %edx
	movzbl	-52(%rbp), %eax
	imull	%edx, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movslq	%eax, %rcx
	movq	-1136(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L1284
.L1283:
	movzbl	-53(%rbp), %edx
	movzbl	-52(%rbp), %eax
	imull	%edx, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movslq	%eax, %rcx
	movq	-1136(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
.L1284:
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -54(%rbp)
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movw	%ax, -56(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1285
	movzwl	-56(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC169(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1285:
	movq	-1136(%rbp), %rax
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -60(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1286
	movl	-60(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC342(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1286:
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -62(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1287
	movswl	-62(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC199(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1287:
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movw	%ax, -64(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1288
	movswl	-64(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC201(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1288:
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movw	%ax, -66(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1289
	movswl	-66(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC200(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1289:
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movw	%ax, -68(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1290
	movswl	-68(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC202(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1290:
	movq	-1136(%rbp), %rdx
	leaq	-89(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L1291
	leaq	.LC188(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L1291:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1292
	movzbl	-89(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC343(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1292:
	movq	-1136(%rbp), %rdx
	leaq	-90(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L1293
	leaq	.LC188(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L1293:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1294
	movzbl	-90(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC344(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1294:
	movq	-1136(%rbp), %rdx
	leaq	-91(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L1295
	leaq	.LC188(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L1295:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1296
	movzbl	-91(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC345(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1296:
	movl	$0, -20(%rbp)
	jmp	.L1297
.L1298:
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -80(%rbp)
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -84(%rbp)
	movl	-84(%rbp), %ecx
	movl	%ecx, %eax
	imulq	$799063683, %rax, %rax
	shrq	$32, %rax
	shrl	$3, %eax
	imull	$43, %eax, %edx
	movl	%ecx, %eax
	subl	%edx, %eax
	movq	-1128(%rbp), %r8
	subq	$8, %rsp
	movl	%eax, %eax
	imulq	$403, %rax, %rax
	leaq	shv_colors(%rip), %rcx
	subq	$408, %rsp
	movq	%rsp, %rdx
	addq	%rcx, %rax
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
	movl	-80(%rbp), %edx
	movl	-20(%rbp), %eax
	cltq
	movl	%edx, -1120(%rbp,%rax,4)
	movq	-1136(%rbp), %rax
	movl	$1, %edx
	movl	$9, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	addl	$1, -20(%rbp)
.L1297:
	movsbl	-54(%rbp), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L1298
	movq	-1136(%rbp), %rax
	movl	$1, %edx
	movq	$-2, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	$0, -20(%rbp)
	jmp	.L1299
.L1306:
	movl	$0, -36(%rbp)
	cmpb	$0, -21(%rbp)
	je	.L1300
	movl	$1, -36(%rbp)
.L1300:
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -69(%rbp)
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -70(%rbp)
	movl	-32(%rbp), %eax
	cltq
	movl	-1120(%rbp,%rax,4), %eax
	cmpl	%eax, -28(%rbp)
	jl	.L1301
	movq	-1128(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	addl	$1, -32(%rbp)
	movl	$0, -28(%rbp)
.L1301:
	cmpb	$-128, -69(%rbp)
	jne	.L1302
	addl	$1, -28(%rbp)
	cmpb	$3, -70(%rbp)
	je	.L1308
	cmpb	$2, -70(%rbp)
	jne	.L1305
	movb	$0, -21(%rbp)
	jmp	.L1304
.L1305:
	cmpb	$1, -70(%rbp)
	jne	.L1302
	addl	$2, -28(%rbp)
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movw	%ax, -72(%rbp)
	movzwl	-72(%rbp), %eax
	sall	$8, %eax
	movl	%eax, %ebx
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	orl	%ebx, %eax
	movw	%ax, -72(%rbp)
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movw	%ax, -74(%rbp)
	movzwl	-74(%rbp), %eax
	sall	$8, %eax
	movl	%eax, %ebx
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	orl	%ebx, %eax
	movw	%ax, -74(%rbp)
	movl	$2, -36(%rbp)
	movb	$1, -21(%rbp)
	movzwl	-74(%rbp), %eax
	movl	%eax, %edi
	call	shvDecodeShort
	cwtl
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movss	%xmm3, -1140(%rbp)
	movzwl	-72(%rbp), %eax
	movl	%eax, %edi
	call	shvDecodeShort
	cwtl
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm4, %xmm4
	cvtsd2ss	%xmm0, %xmm4
	movd	%xmm4, %ecx
	movl	-36(%rbp), %esi
	movq	-1128(%rbp), %rax
	movl	$1, %edx
	movss	-1140(%rbp), %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L1304
.L1302:
	movzbl	-69(%rbp), %eax
	movl	%eax, %edi
	call	shvDecode
	movb	%al, -49(%rbp)
	movzbl	-70(%rbp), %eax
	movl	%eax, %edi
	call	shvDecode
	movb	%al, -50(%rbp)
	addl	$1, -28(%rbp)
	movsbl	-50(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movsbl	-49(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm5, %xmm5
	cvtsd2ss	%xmm0, %xmm5
	movd	%xmm5, %ecx
	movl	-36(%rbp), %esi
	movq	-1128(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L1304
.L1308:
	nop
.L1304:
	addl	$1, -20(%rbp)
.L1299:
	movq	-1136(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	je	.L1306
	movq	-1128(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movl	$1, %eax
.L1307:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE160:
	.size	readShv, .-readShv
	.section	.rodata
.LC346:
	.string	"writeShv not implemented."
	.text
	.globl	writeShv
	.type	writeShv, @function
writeShv:
.LFB161:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC346(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1310
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC151(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1310:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE161:
	.size	writeShv, .-writeShv
	.globl	readSst
	.type	readSst, @function
readSst:
.LFB162:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -16(%rbp)
	movq	-48(%rbp), %rax
	movl	$0, %edx
	movl	$160, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L1313
.L1320:
	movl	$0, -4(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -8(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -12(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -17(%rbp)
	cmpb	$4, -17(%rbp)
	jne	.L1314
	movq	-40(%rbp), %rax
	movl	$1, %edx
	movl	$16, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L1315
.L1314:
	movzbl	-17(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L1316
	movl	$4, -4(%rbp)
.L1316:
	movzbl	-17(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L1317
	movl	$1, -4(%rbp)
.L1317:
	movzbl	-17(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	jne	.L1318
	negl	-12(%rbp)
.L1318:
	movzbl	-17(%rbp), %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L1319
	negl	-8(%rbp)
.L1319:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-12(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-8(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-4(%rbp), %esi
	movq	-40(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L1313:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rdx
	movl	-16(%rbp), %eax
	cltq
	cmpq	%rax, %rdx
	jl	.L1320
.L1315:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE162:
	.size	readSst, .-readSst
	.globl	writeSst
	.type	writeSst, @function
writeSst:
.LFB163:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$160, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1323
.L1324:
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$32, %edi
	call	fputc@PLT
	addl	$1, -4(%rbp)
.L1323:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L1324
	movl	$0, -4(%rbp)
	jmp	.L1325
.L1326:
	movl	$46, %edi
	call	putchar@PLT
	addl	$1, -4(%rbp)
.L1325:
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1326
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE163:
	.size	writeSst, .-writeSst
	.section	.rodata
	.align 8
.LC347:
	.string	"ERROR: format-stx.c stxReadThread(), thread argument is null"
	.align 8
.LC348:
	.string	"ERROR: format-stx.c stxReadThread(), file argument is null"
	.align 8
.LC349:
	.string	"ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeBuff"
	.align 8
.LC350:
	.string	"ERROR: format-stx.c stxReadThread(), unable to allocate memory for codeNameBuff"
.LC351:
	.string	"col red: %d\n"
.LC352:
	.string	"col green: %d\n"
.LC353:
	.string	"col blue: %d\n"
	.align 8
.LC354:
	.string	"ERROR: format-stx.c stxReadThread(), unable to allocate memory for sectionNameBuff"
.LC355:
	.string	"somethingSomething: %d\n"
.LC356:
	.string	"somethingSomething2: %d\n"
.LC357:
	.string	"somethingElse: %d\n"
.LC358:
	.string	"numberOfOtherDescriptors: %d\n"
	.align 8
.LC359:
	.string	"ERROR: format-stx.c stxReadThread(), unable to allocate memory for thread->subDescriptors"
	.align 8
.LC360:
	.string	"ERROR: format-stx.c stxReadThread(), unable to allocate memory for subCodeBuff"
	.align 8
.LC361:
	.string	"ERROR: format-stx.c stxReadThread(), unable to allocate memory for subColorNameBuff"
	.text
	.globl	stxReadThread
	.type	stxReadThread, @function
stxReadThread:
.LFB164:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$144, %rsp
	movq	%rdi, -136(%rbp)
	movq	%rsi, -144(%rbp)
	movl	$0, -8(%rbp)
	movq	$0, -16(%rbp)
	movq	$0, -24(%rbp)
	movq	$0, -32(%rbp)
	cmpq	$0, -136(%rbp)
	jne	.L1329
	leaq	.LC347(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1346
.L1329:
	cmpq	$0, -144(%rbp)
	jne	.L1331
	leaq	.LC348(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1346
.L1331:
	movq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L1332
	leaq	.LC349(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1346
.L1332:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-144(%rbp), %rcx
	movq	-16(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-136(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -36(%rbp)
	movl	-36(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L1333
	leaq	.LC350(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1346
.L1333:
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	-144(%rbp), %rcx
	movq	-24(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-136(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 8(%rax)
	leaq	-91(%rbp), %rcx
	movq	-144(%rbp), %rax
	movl	$4, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_read@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1334
	movzbl	-91(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC351(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movzbl	-90(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC352(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movzbl	-89(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC353(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1334:
	movq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -40(%rbp)
	movl	-40(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L1335
	leaq	.LC354(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1346
.L1335:
	movl	-40(%rbp), %eax
	movslq	%eax, %rdx
	movq	-144(%rbp), %rcx
	movq	-32(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-136(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -44(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1336
	movl	-44(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC355(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1336:
	movq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -48(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1337
	movl	-48(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC356(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1337:
	movq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -52(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1338
	movl	-52(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC357(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1338:
	movq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -56(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1339
	movl	-56(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC358(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1339:
	movl	-56(%rbp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-136(%rbp), %rax
	movq	%rdx, 24(%rax)
	movq	-136(%rbp), %rax
	movq	24(%rax), %rax
	testq	%rax, %rax
	jne	.L1340
	leaq	.LC359(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1346
.L1340:
	movl	$0, -4(%rbp)
	jmp	.L1341
.L1345:
	movq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -128(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -124(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -60(%rbp)
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -72(%rbp)
	cmpq	$0, -72(%rbp)
	jne	.L1342
	leaq	.LC360(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1346
.L1342:
	movl	-60(%rbp), %eax
	movslq	%eax, %rdx
	movq	-144(%rbp), %rcx
	movq	-72(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-72(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -76(%rbp)
	movl	-76(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -88(%rbp)
	cmpq	$0, -88(%rbp)
	jne	.L1344
	leaq	.LC361(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1346
.L1344:
	movl	-76(%rbp), %eax
	movslq	%eax, %rdx
	movq	-144(%rbp), %rcx
	movq	-88(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-88(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -120(%rbp)
	movq	-136(%rbp), %rax
	movq	24(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$5, %rdx
	leaq	(%rax,%rdx), %rcx
	movq	-128(%rbp), %rax
	movq	-120(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-112(%rbp), %rax
	movq	-104(%rbp), %rdx
	movq	%rax, 16(%rcx)
	movq	%rdx, 24(%rcx)
	addl	$1, -4(%rbp)
.L1341:
	movl	-4(%rbp), %eax
	cmpl	-56(%rbp), %eax
	jl	.L1345
	movl	$1, %eax
.L1346:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE164:
	.size	stxReadThread, .-stxReadThread
	.section	.rodata
.LC362:
	.string	"ERROR: header is not present."
.LC363:
	.string	"paletteLength: %d\n"
.LC364:
	.string	"imageLength: %d\n"
.LC365:
	.string	"something1: %d\n"
.LC366:
	.string	"stitchDataOffset: %d\n"
.LC367:
	.string	"threadDescriptionOffset: %d\n"
.LC368:
	.string	"colors: %d\n"
	.align 8
.LC369:
	.string	"ERROR: format-stx.c readStx(), unable to allocate memory for gif"
	.align 8
.LC370:
	.string	"ERROR: format-stx.c readStx(), unable "
	.align 8
.LC371:
	.string	"to allocate memory for stxThreads"
.LC372:
	.string	"identify val[%d] = %d"
.LC373:
	.string	"val[4] == val[5] == 0"
.LC374:
	.string	"val[10] == val[11] == 0"
	.text
	.globl	readStx
	.type	readStx, @function
readStx:
.LFB165:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$648, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -648(%rbp)
	movq	%rsi, -656(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -48(%rbp)
	movq	-656(%rbp), %rax
	movl	$15, %esi
	movq	%rax, %rdi
	call	check_header_present@PLT
	testl	%eax, %eax
	jne	.L1348
	leaq	.LC362(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1380
.L1348:
	leaq	-113(%rbp), %rcx
	movq	-656(%rbp), %rax
	movl	$7, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	read_n_bytes
	testb	%al, %al
	jne	.L1350
	movl	$0, %eax
	jmp	.L1380
.L1350:
	leaq	-113(%rbp), %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rcx
	leaq	-117(%rbp), %rax
	movl	$3, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	movq	-48(%rbp), %rax
	addq	$3, %rax
	movl	(%rax), %eax
	movl	%eax, -122(%rbp)
	movb	$0, -114(%rbp)
	movb	$0, -118(%rbp)
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -49(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1351
	movsbl	-49(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC315(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1351:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -56(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1352
	movl	-56(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC363(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1352:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -60(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1353
	movl	-60(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC364(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1353:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -64(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1354
	movl	-64(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC365(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1354:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -68(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1355
	movl	-68(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC366(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1355:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -72(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1356
	movl	-72(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC345(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1356:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -76(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1357
	movl	-76(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC367(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1357:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -80(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1358
	movl	-80(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC190(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1358:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -84(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1359
	movl	-84(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC368(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1359:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -88(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1360
	movl	-88(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC200(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1360:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -92(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1361
	movl	-92(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC199(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1361:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -96(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1362
	movl	-96(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC202(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1362:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -100(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1363
	movl	-100(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC201(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1363:
	movl	-60(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L1364
	leaq	.LC369(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1380
.L1364:
	movl	-60(%rbp), %edx
	movq	-32(%rbp), %rcx
	movq	-656(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	read_n_bytes
	testb	%al, %al
	jne	.L1365
	movl	$0, %eax
	jmp	.L1380
.L1365:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -104(%rbp)
	movl	-104(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L1366
	leaq	.LC370(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC371(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1380
.L1366:
	movl	$0, -20(%rbp)
	jmp	.L1367
.L1368:
	movq	-656(%rbp), %rdx
	leaq	-640(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	stxReadThread
	movzwl	-608(%rbp), %eax
	movw	%ax, -592(%rbp)
	movzbl	-606(%rbp), %eax
	movb	%al, -590(%rbp)
	movq	-632(%rbp), %rax
	leaq	-592(%rbp), %rdx
	addq	$3, %rdx
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	strcpy@PLT
	movq	-640(%rbp), %rax
	leaq	-592(%rbp), %rdx
	addq	$203, %rdx
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	strcpy@PLT
	movq	-648(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-592(%rbp), %rax
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
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	-640(%rbp), %rcx
	movq	-632(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-624(%rbp), %rcx
	movq	-616(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-608(%rbp), %rdx
	movq	%rdx, 32(%rax)
	addl	$1, -20(%rbp)
.L1367:
	movl	-20(%rbp), %eax
	cmpl	-104(%rbp), %eax
	jl	.L1368
	movq	-656(%rbp), %rax
	movl	$1, %edx
	movl	$15, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	$0, -20(%rbp)
	jmp	.L1369
.L1371:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movswl	%ax, %edx
	movl	-20(%rbp), %eax
	cltq
	movl	%edx, -176(%rbp,%rax,4)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1370
	movl	-20(%rbp), %eax
	cltq
	movl	-176(%rbp,%rax,4), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC372(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1370:
	addl	$1, -20(%rbp)
.L1369:
	cmpl	$11, -20(%rbp)
	jle	.L1371
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1372
	leaq	.LC373(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC374(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L1372:
	movq	-656(%rbp), %rax
	movl	$1, %edx
	movl	$8, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	$1, -20(%rbp)
	jmp	.L1373
.L1379:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -105(%rbp)
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -106(%rbp)
	cmpb	$-128, -105(%rbp)
	jne	.L1374
	movsbl	-106(%rbp), %eax
	cmpl	$2, %eax
	je	.L1375
	cmpl	$2, %eax
	jg	.L1381
	cmpl	$-94, %eax
	je	.L1382
	cmpl	$1, %eax
	jne	.L1381
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -105(%rbp)
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -106(%rbp)
	addl	$1, -20(%rbp)
	jmp	.L1373
.L1375:
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -105(%rbp)
	movq	-656(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -106(%rbp)
	movsbl	-106(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movsbl	-105(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movq	-648(%rbp), %rax
	movl	$1, %edx
	movl	$1, %esi
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	addl	$1, -20(%rbp)
	jmp	.L1373
.L1381:
	nop
	jmp	.L1373
.L1382:
	nop
	jmp	.L1373
.L1374:
	movsbl	-106(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movsbl	-105(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm4, %xmm4
	cvtsd2ss	%xmm0, %xmm4
	movd	%xmm4, %ecx
	movq	-648(%rbp), %rax
	movl	$1, %edx
	movl	$0, %esi
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	addl	$1, -20(%rbp)
.L1373:
	movl	-20(%rbp), %eax
	cmpl	-80(%rbp), %eax
	jl	.L1379
	movq	-648(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movl	$1, %eax
.L1380:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE165:
	.size	readStx, .-readStx
	.section	.rodata
	.align 8
.LC375:
	.string	"ERROR: writeStx is not implemented."
	.text
	.globl	writeStx
	.type	writeStx, @function
writeStx:
.LFB166:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC375(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1384
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC151(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1384:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE166:
	.size	writeStx, .-writeStx
	.globl	svgCreator
	.bss
	.align 4
	.type	svgCreator, @object
	.size	svgCreator, 4
svgCreator:
	.zero	4
	.globl	svgExpect
	.align 4
	.type	svgExpect, @object
	.size	svgExpect, 4
svgExpect:
	.zero	4
	.globl	svgMultiValue
	.align 4
	.type	svgMultiValue, @object
	.size	svgMultiValue, 4
svgMultiValue:
	.zero	4
	.globl	current_element_id
	.align 4
	.type	current_element_id, @object
	.size	current_element_id, 4
current_element_id:
	.zero	4
	.globl	attributeList
	.align 32
	.type	attributeList, @object
	.size	attributeList, 16000
attributeList:
	.zero	16000
	.globl	n_attributes
	.align 4
	.type	n_attributes, @object
	.size	n_attributes, 4
n_attributes:
	.zero	4
	.globl	currentAttribute
	.align 32
	.type	currentAttribute, @object
	.size	currentAttribute, 1000
currentAttribute:
	.zero	1000
	.globl	currentValue
	.align 32
	.type	currentValue, @object
	.size	currentValue, 1000
currentValue:
	.zero	1000
	.text
	.globl	readSvg
	.type	readSvg, @function
readSvg:
.LFB167:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1387
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC105(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1387:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1388
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC158(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1388:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE167:
	.size	readSvg, .-readSvg
	.section	.rodata
.LC376:
	.string	"<?xml version=\"1.0\"?>\n"
	.align 8
.LC377:
	.string	"<!-- Embroidermodder 2 SVG Embroidery File -->\n"
	.align 8
.LC378:
	.string	"<!-- http://embroidermodder.github.io -->\n"
.LC379:
	.string	"<svg "
.LC381:
	.string	"viewBox=\"%f %f %f %f\" "
	.align 8
.LC382:
	.string	"xmlns=\"http://www.w3.org/2000/svg\" version=\"1.2\" baseProfile=\"tiny\">"
.LC383:
	.string	"\n<g transform=\"scale(10)\">"
	.align 8
.LC384:
	.string	"\n<circle stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" cx=\"%f\" cy=\"%f\" r=\"%f\" />"
	.align 8
.LC385:
	.string	"\n<ellipse stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" />"
	.align 8
.LC386:
	.string	"\n<line stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />"
	.align 8
.LC387:
	.string	"\n<line stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />"
	.align 8
.LC388:
	.string	"\n<polygon stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"%s,%s"
.LC389:
	.string	" %s,%s"
.LC390:
	.string	"\"/>"
	.align 8
.LC391:
	.string	"\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" points=\"%s,%s"
	.align 8
.LC392:
	.string	"\n<rect stroke-width=\"0.2\" stroke=\"#%02x%02x%02x\" fill=\"none\" x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" />"
.LC393:
	.string	"\n</g>\n</svg>\n"
	.text
	.globl	writeSvg
	.type	writeSvg, @function
writeSvg:
.LFB168:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$376, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -376(%rbp)
	movq	%rsi, -384(%rbp)
	movq	-376(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	leaq	-80(%rbp), %rax
	movq	-376(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_bounds@PLT
	movq	-384(%rbp), %rax
	movq	%rax, %rcx
	movl	$22, %edx
	movl	$1, %esi
	leaq	.LC376(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-384(%rbp), %rax
	movq	%rax, %rcx
	movl	$47, %edx
	movl	$1, %esi
	leaq	.LC377(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-384(%rbp), %rax
	movq	%rax, %rcx
	movl	$42, %edx
	movl	$1, %esi
	leaq	.LC378(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-384(%rbp), %rax
	movq	%rax, %rcx
	movl	$5, %edx
	movl	$1, %esi
	leaq	.LC379(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, -224(%rbp)
	movq	%rdx, -216(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -208(%rbp)
	movss	-224(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -224(%rbp)
	movss	-220(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -220(%rbp)
	movss	-216(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -216(%rbp)
	movss	-212(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -212(%rbp)
	movss	-224(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-216(%rbp), %xmm1
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm1, %xmm2
	movsd	.LC20(%rip), %xmm1
	mulsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -224(%rbp)
	movss	-216(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-216(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movsd	.LC380(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -216(%rbp)
	movss	-220(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-212(%rbp), %xmm1
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm1, %xmm2
	movsd	.LC20(%rip), %xmm1
	mulsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -220(%rbp)
	movss	-212(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-212(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movsd	.LC380(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -212(%rbp)
	movss	-212(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-216(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-220(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-224(%rbp), %xmm3
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm3, %xmm4
	movq	%xmm4, %rdx
	movq	-384(%rbp), %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rdx, %xmm0
	leaq	.LC381(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$4, %eax
	call	fprintf@PLT
	movq	-384(%rbp), %rax
	movq	%rax, %rcx
	movl	$68, %edx
	movl	$1, %esi
	leaq	.LC382(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-384(%rbp), %rax
	movq	%rax, %rcx
	movl	$26, %edx
	movl	$1, %esi
	leaq	.LC383(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$0, -20(%rbp)
	jmp	.L1391
.L1406:
	movq	-376(%rbp), %rax
	movq	40(%rax), %rax
	movq	(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, -368(%rbp)
	movq	%rbx, -360(%rbp)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, -352(%rbp)
	movq	%rbx, -344(%rbp)
	movq	32(%rax), %rax
	movq	%rax, -336(%rbp)
	movl	-340(%rbp), %eax
	cmpl	$13, %eax
	ja	.L1413
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L1394(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L1394(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L1394:
	.long	.L1413-.L1394
	.long	.L1413-.L1394
	.long	.L1400-.L1394
	.long	.L1413-.L1394
	.long	.L1413-.L1394
	.long	.L1399-.L1394
	.long	.L1413-.L1394
	.long	.L1398-.L1394
	.long	.L1413-.L1394
	.long	.L1413-.L1394
	.long	.L1397-.L1394
	.long	.L1396-.L1394
	.long	.L1395-.L1394
	.long	.L1393-.L1394
	.text
.L1400:
	movq	-368(%rbp), %rax
	movq	%rax, -236(%rbp)
	movl	-360(%rbp), %eax
	movl	%eax, -228(%rbp)
	movss	-228(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-232(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-236(%rbp), %xmm2
	pxor	%xmm5, %xmm5
	cvtss2sd	%xmm2, %xmm5
	movq	%xmm5, %rsi
	movzbl	-330(%rbp), %eax
	movzbl	%al, %edi
	movzbl	-331(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-332(%rbp), %eax
	movzbl	%al, %edx
	movq	-384(%rbp), %rax
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rsi, %xmm0
	movl	%edi, %r8d
	leaq	.LC384(%rip), %rsi
	movq	%rax, %rdi
	movl	$3, %eax
	call	fprintf@PLT
	jmp	.L1401
.L1399:
	movq	-368(%rbp), %rax
	movq	-360(%rbp), %rdx
	movq	%rax, -256(%rbp)
	movq	%rdx, -248(%rbp)
	movl	-352(%rbp), %eax
	movl	%eax, -240(%rbp)
	movzwl	-332(%rbp), %eax
	movw	%ax, -115(%rbp)
	movzbl	-330(%rbp), %eax
	movb	%al, -113(%rbp)
	movss	-244(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-248(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-252(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-256(%rbp), %xmm3
	pxor	%xmm6, %xmm6
	cvtss2sd	%xmm3, %xmm6
	movq	%xmm6, %rsi
	movzbl	-113(%rbp), %eax
	movzbl	%al, %edi
	movzbl	-114(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-115(%rbp), %eax
	movzbl	%al, %edx
	movq	-384(%rbp), %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rsi, %xmm0
	movl	%edi, %r8d
	leaq	.LC385(%rip), %rsi
	movq	%rax, %rdi
	movl	$4, %eax
	call	fprintf@PLT
	jmp	.L1401
.L1398:
	movq	-368(%rbp), %rax
	movq	-360(%rbp), %rdx
	movq	%rax, -288(%rbp)
	movq	%rdx, -280(%rbp)
	movq	-352(%rbp), %rax
	movq	%rax, -272(%rbp)
	movzwl	-332(%rbp), %eax
	movw	%ax, -115(%rbp)
	movzbl	-330(%rbp), %eax
	movb	%al, -113(%rbp)
	movss	-276(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-280(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-284(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-288(%rbp), %xmm3
	pxor	%xmm7, %xmm7
	cvtss2sd	%xmm3, %xmm7
	movq	%xmm7, %rsi
	movzbl	-113(%rbp), %eax
	movzbl	%al, %edi
	movzbl	-114(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-115(%rbp), %eax
	movzbl	%al, %edx
	movq	-384(%rbp), %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rsi, %xmm0
	movl	%edi, %r8d
	leaq	.LC386(%rip), %rsi
	movq	%rax, %rdi
	movl	$4, %eax
	call	fprintf@PLT
	jmp	.L1401
.L1397:
	movq	-368(%rbp), %rax
	movq	-360(%rbp), %rdx
	movq	%rax, -304(%rbp)
	movq	%rdx, -296(%rbp)
	movss	-300(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-304(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-300(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-304(%rbp), %xmm3
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm3, %xmm4
	movq	%xmm4, %rsi
	movzbl	-290(%rbp), %eax
	movzbl	%al, %edi
	movzbl	-291(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-292(%rbp), %eax
	movzbl	%al, %edx
	movq	-384(%rbp), %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rsi, %xmm0
	movl	%edi, %r8d
	leaq	.LC387(%rip), %rsi
	movq	%rax, %rdi
	movl	$4, %eax
	call	fprintf@PLT
	jmp	.L1401
.L1396:
	movq	-368(%rbp), %rax
	movq	%rax, -48(%rbp)
	movzwl	-368(%rbp), %eax
	movw	%ax, -115(%rbp)
	movzbl	-366(%rbp), %eax
	movb	%al, -113(%rbp)
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movl	4(%rax), %eax
	leaq	-192(%rbp), %rdx
	movq	%rdx, %rdi
	movd	%eax, %xmm0
	call	emb_optOut@PLT
	movq	%rax, %rbx
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %eax
	leaq	-160(%rbp), %rdx
	movq	%rdx, %rdi
	movd	%eax, %xmm0
	call	emb_optOut@PLT
	movq	%rax, %rsi
	movzbl	-113(%rbp), %eax
	movzbl	%al, %edi
	movzbl	-114(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-115(%rbp), %eax
	movzbl	%al, %edx
	movq	-384(%rbp), %rax
	subq	$8, %rsp
	pushq	%rbx
	movq	%rsi, %r9
	movl	%edi, %r8d
	leaq	.LC388(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addq	$16, %rsp
	movl	$1, -24(%rbp)
	jmp	.L1402
.L1403:
	movq	-48(%rbp), %rax
	movq	(%rax), %rcx
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movl	4(%rax), %eax
	leaq	-192(%rbp), %rdx
	movq	%rdx, %rdi
	movd	%eax, %xmm0
	call	emb_optOut@PLT
	movq	%rax, %rbx
	movq	-48(%rbp), %rax
	movq	(%rax), %rcx
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	leaq	-160(%rbp), %rdx
	movq	%rdx, %rdi
	movd	%eax, %xmm0
	call	emb_optOut@PLT
	movq	%rax, %rdx
	movq	-384(%rbp), %rax
	movq	%rbx, %rcx
	leaq	.LC389(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addl	$1, -24(%rbp)
.L1402:
	movq	-48(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -24(%rbp)
	jl	.L1403
	movq	-384(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	leaq	.LC390(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L1401
.L1395:
	movq	-368(%rbp), %rax
	movq	%rax, -40(%rbp)
	movzwl	-348(%rbp), %eax
	movw	%ax, -115(%rbp)
	movzbl	-346(%rbp), %eax
	movb	%al, -113(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movl	4(%rax), %eax
	leaq	-192(%rbp), %rdx
	movq	%rdx, %rdi
	movd	%eax, %xmm0
	call	emb_optOut@PLT
	movq	%rax, %rbx
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %eax
	leaq	-160(%rbp), %rdx
	movq	%rdx, %rdi
	movd	%eax, %xmm0
	call	emb_optOut@PLT
	movq	%rax, %rsi
	movzbl	-113(%rbp), %eax
	movzbl	%al, %edi
	movzbl	-114(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-115(%rbp), %eax
	movzbl	%al, %edx
	movq	-384(%rbp), %rax
	subq	$8, %rsp
	pushq	%rbx
	movq	%rsi, %r9
	movl	%edi, %r8d
	leaq	.LC391(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addq	$16, %rsp
	movl	$1, -24(%rbp)
	jmp	.L1404
.L1405:
	movq	-40(%rbp), %rax
	movq	(%rax), %rcx
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movl	4(%rax), %eax
	leaq	-192(%rbp), %rdx
	movq	%rdx, %rdi
	movd	%eax, %xmm0
	call	emb_optOut@PLT
	movq	%rax, %rbx
	movq	-40(%rbp), %rax
	movq	(%rax), %rcx
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	leaq	-160(%rbp), %rdx
	movq	%rdx, %rdi
	movd	%eax, %xmm0
	call	emb_optOut@PLT
	movq	%rax, %rdx
	movq	-384(%rbp), %rax
	movq	%rbx, %rcx
	leaq	.LC389(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addl	$1, -24(%rbp)
.L1404:
	movq	-40(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -24(%rbp)
	jl	.L1405
	movq	-384(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	leaq	.LC390(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L1401
.L1393:
	movq	-368(%rbp), %rax
	movq	-360(%rbp), %rdx
	movq	%rax, -112(%rbp)
	movq	%rdx, -104(%rbp)
	movq	-352(%rbp), %rax
	movq	%rax, -96(%rbp)
	movzwl	-368(%rbp), %eax
	movw	%ax, -115(%rbp)
	movzbl	-366(%rbp), %eax
	movb	%al, -113(%rbp)
	movss	-100(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-104(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-108(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-112(%rbp), %xmm3
	pxor	%xmm5, %xmm5
	cvtss2sd	%xmm3, %xmm5
	movq	%xmm5, %rsi
	movzbl	-113(%rbp), %eax
	movzbl	%al, %edi
	movzbl	-114(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-115(%rbp), %eax
	movzbl	%al, %edx
	movq	-384(%rbp), %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rsi, %xmm0
	movl	%edi, %r8d
	leaq	.LC392(%rip), %rsi
	movq	%rax, %rdi
	movl	$4, %eax
	call	fprintf@PLT
	jmp	.L1401
.L1413:
	nop
.L1401:
	addl	$1, -20(%rbp)
.L1391:
	movq	-376(%rbp), %rax
	movq	40(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L1406
	movb	$0, -25(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L1407
.L1411:
	movq	-376(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -320(%rbp)
	movq	%rdx, -312(%rbp)
	movl	-320(%rbp), %eax
	testl	%eax, %eax
	jne	.L1408
	cmpb	$0, -25(%rbp)
	jne	.L1408
	movb	$1, -25(%rbp)
	movq	-376(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-308(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -115(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -113(%rbp)
	movl	-312(%rbp), %eax
	leaq	-192(%rbp), %rdx
	movq	%rdx, %rdi
	movd	%eax, %xmm0
	call	emb_optOut@PLT
	movq	%rax, %rbx
	movl	-316(%rbp), %eax
	leaq	-160(%rbp), %rdx
	movq	%rdx, %rdi
	movd	%eax, %xmm0
	call	emb_optOut@PLT
	movq	%rax, %rsi
	movzbl	-113(%rbp), %eax
	movzbl	%al, %edi
	movzbl	-114(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-115(%rbp), %eax
	movzbl	%al, %edx
	movq	-384(%rbp), %rax
	subq	$8, %rsp
	pushq	%rbx
	movq	%rsi, %r9
	movl	%edi, %r8d
	leaq	.LC391(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	addq	$16, %rsp
	jmp	.L1409
.L1408:
	movl	-320(%rbp), %eax
	testl	%eax, %eax
	jne	.L1410
	cmpb	$0, -25(%rbp)
	je	.L1410
	movl	-312(%rbp), %eax
	leaq	-192(%rbp), %rdx
	movq	%rdx, %rdi
	movd	%eax, %xmm0
	call	emb_optOut@PLT
	movq	%rax, %rbx
	movl	-316(%rbp), %eax
	leaq	-160(%rbp), %rdx
	movq	%rdx, %rdi
	movd	%eax, %xmm0
	call	emb_optOut@PLT
	movq	%rax, %rdx
	movq	-384(%rbp), %rax
	movq	%rbx, %rcx
	leaq	.LC389(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	jmp	.L1409
.L1410:
	movl	-320(%rbp), %eax
	testl	%eax, %eax
	je	.L1409
	cmpb	$0, -25(%rbp)
	je	.L1409
	movb	$0, -25(%rbp)
	movq	-384(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	leaq	.LC390(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
.L1409:
	addl	$1, -20(%rbp)
.L1407:
	movq	-376(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L1411
	movq	-384(%rbp), %rax
	movq	%rax, %rcx
	movl	$13, %edx
	movl	$1, %esi
	leaq	.LC393(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-376(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movl	$1, %eax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE168:
	.size	writeSvg, .-writeSvg
	.globl	readT01
	.type	readT01, @function
readT01:
.LFB169:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	jmp	.L1415
.L1418:
	leaq	-16(%rbp), %rcx
	leaq	-12(%rbp), %rdx
	leaq	-8(%rbp), %rsi
	leaq	-3(%rbp), %rax
	movq	%rax, %rdi
	call	decode_t01_record@PLT
	movl	-8(%rbp), %esi
	movl	-16(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movl	-12(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	movl	-8(%rbp), %eax
	cmpl	$16, %eax
	je	.L1420
.L1415:
	movq	-32(%rbp), %rdx
	leaq	-3(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L1418
	jmp	.L1417
.L1420:
	nop
.L1417:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE169:
	.size	readT01, .-readT01
	.section	.rodata
	.align 8
.LC394:
	.string	"bounding rectangle with top %f not used "
.LC395:
	.string	"in the function writeT01"
	.text
	.globl	writeT01
	.type	writeT01, @function
writeT01:
.LFB170:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	-88(%rbp), %rax
	movss	.LC93(%rip), %xmm1
	movl	.LC93(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_correctForMaxStitchLength@PLT
	leaq	-48(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_bounds@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1422
	movss	-48(%rbp), %xmm0
	pxor	%xmm3, %xmm3
	cvtss2sd	%xmm0, %xmm3
	movq	%xmm3, %rax
	movq	%rax, %xmm0
	leaq	.LC394(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	leaq	.LC395(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L1422:
	pxor	%xmm0, %xmm0
	movss	%xmm0, -56(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -52(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1423
.L1424:
	movq	-88(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movss	-76(%rbp), %xmm0
	movss	-56(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, -8(%rbp)
	movss	-72(%rbp), %xmm0
	movss	-52(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, -12(%rbp)
	movss	-56(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	pxor	%xmm2, %xmm2
	cvtsi2sdl	-8(%rbp), %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -56(%rbp)
	movss	-52(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	pxor	%xmm2, %xmm2
	cvtsi2sdl	-12(%rbp), %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -52(%rbp)
	movl	-80(%rbp), %ecx
	movl	-12(%rbp), %edx
	movl	-8(%rbp), %esi
	leaq	-59(%rbp), %rax
	movq	%rax, %rdi
	call	encode_t01_record@PLT
	movq	-96(%rbp), %rdx
	leaq	-59(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	addl	$1, -4(%rbp)
.L1423:
	movq	-88(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1424
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE170:
	.size	writeT01, .-writeT01
	.globl	readT09
	.type	readT09, @function
readT09:
.LFB171:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movl	$0, %edx
	movl	$12, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L1427
.L1433:
	movl	$0, -4(%rbp)
	movzbl	-16(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, -8(%rbp)
	movzbl	-15(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, -12(%rbp)
	movzbl	-14(%rbp), %eax
	movb	%al, -13(%rbp)
	cmpb	$0, -13(%rbp)
	je	.L1435
	movzbl	-13(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L1430
	movl	$4, -4(%rbp)
.L1430:
	movzbl	-13(%rbp), %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L1431
	negl	-8(%rbp)
.L1431:
	movzbl	-13(%rbp), %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L1432
	negl	-12(%rbp)
.L1432:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-8(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-12(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-4(%rbp), %esi
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L1427:
	movq	-32(%rbp), %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L1433
	jmp	.L1429
.L1435:
	nop
.L1429:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE171:
	.size	readT09, .-readT09
	.globl	writeT09
	.type	writeT09, @function
writeT09:
.LFB172:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-64(%rbp), %rax
	movl	$12, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	pxor	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1437
.L1441:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movss	-44(%rbp), %xmm0
	movss	-20(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, -8(%rbp)
	movss	-40(%rbp), %xmm0
	movss	-16(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, -12(%rbp)
	movss	-20(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	pxor	%xmm2, %xmm2
	cvtsi2sdl	-8(%rbp), %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	movss	-16(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	pxor	%xmm2, %xmm2
	cvtsi2sdl	-12(%rbp), %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	movl	-8(%rbp), %eax
	movb	%al, -23(%rbp)
	movl	-12(%rbp), %eax
	movb	%al, -22(%rbp)
	movb	$0, -21(%rbp)
	movl	-48(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L1438
	movzbl	-21(%rbp), %eax
	orl	$16, %eax
	movb	%al, -21(%rbp)
.L1438:
	cmpl	$0, -8(%rbp)
	jns	.L1439
	movl	-8(%rbp), %eax
	negl	%eax
	movb	%al, -23(%rbp)
	movzbl	-21(%rbp), %eax
	orl	$32, %eax
	movb	%al, -21(%rbp)
.L1439:
	cmpl	$0, -12(%rbp)
	jns	.L1440
	movl	-12(%rbp), %eax
	negl	%eax
	movb	%al, -23(%rbp)
	movzbl	-21(%rbp), %eax
	orl	$64, %eax
	movb	%al, -21(%rbp)
.L1440:
	movq	-64(%rbp), %rdx
	leaq	-23(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	addl	$1, -4(%rbp)
.L1437:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1441
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE172:
	.size	writeT09, .-writeT09
	.globl	encode_tap_record
	.type	encode_tap_record, @function
encode_tap_record:
.LFB173:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	%ecx, -36(%rbp)
	movl	-32(%rbp), %edx
	movl	-28(%rbp), %ecx
	leaq	-3(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	encode_tajima_ternary@PLT
	movzbl	-1(%rbp), %eax
	orl	$3, %eax
	movb	%al, -1(%rbp)
	movl	-36(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L1444
	movb	$0, -3(%rbp)
	movb	$0, -2(%rbp)
	movb	$-13, -1(%rbp)
.L1444:
	movl	-36(%rbp), %eax
	andl	$3, %eax
	testl	%eax, %eax
	je	.L1445
	movzbl	-1(%rbp), %eax
	orl	$-125, %eax
	movb	%al, -1(%rbp)
.L1445:
	movl	-36(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L1446
	movzbl	-1(%rbp), %eax
	orl	$-61, %eax
	movb	%al, -1(%rbp)
.L1446:
	movq	-24(%rbp), %rdx
	leaq	-3(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE173:
	.size	encode_tap_record, .-encode_tap_record
	.globl	decode_tap_record_flags
	.type	decode_tap_record_flags, @function
decode_tap_record_flags:
.LFB174:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	cmpb	$-13, -4(%rbp)
	jne	.L1448
	movl	$16, %eax
	jmp	.L1449
.L1448:
	movzbl	-4(%rbp), %eax
	andl	$195, %eax
	cmpl	$195, %eax
	je	.L1450
	cmpl	$195, %eax
	jg	.L1451
	cmpl	$3, %eax
	je	.L1452
	cmpl	$131, %eax
	je	.L1453
	jmp	.L1451
.L1452:
	movl	$0, %eax
	jmp	.L1449
.L1453:
	movl	$2, %eax
	jmp	.L1449
.L1450:
	movl	$4, %eax
	jmp	.L1449
.L1451:
	movl	$0, %eax
.L1449:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE174:
	.size	decode_tap_record_flags, .-decode_tap_record_flags
	.globl	readTap
	.type	readTap, @function
readTap:
.LFB175:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	jmp	.L1455
.L1458:
	leaq	-16(%rbp), %rdx
	leaq	-12(%rbp), %rcx
	leaq	-7(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	decode_tajima_ternary@PLT
	movzbl	-5(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	decode_tap_record_flags
	movl	%eax, -4(%rbp)
	movl	-16(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movl	-12(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-4(%rbp), %esi
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	cmpl	$16, -4(%rbp)
	je	.L1460
.L1455:
	movq	-32(%rbp), %rdx
	leaq	-7(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L1458
	jmp	.L1457
.L1460:
	nop
.L1457:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE175:
	.size	readTap, .-readTap
	.globl	writeTap
	.type	writeTap, @function
writeTap:
.LFB176:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-56(%rbp), %rax
	movss	.LC93(%rip), %xmm1
	movl	.LC93(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_correctForMaxStitchLength@PLT
	pxor	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1462
.L1463:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movss	-44(%rbp), %xmm0
	movss	-20(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, -8(%rbp)
	movss	-40(%rbp), %xmm0
	movss	-16(%rbp), %xmm2
	movaps	%xmm0, %xmm1
	subss	%xmm2, %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movl	%eax, -12(%rbp)
	movss	-20(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	pxor	%xmm2, %xmm2
	cvtsi2sdl	-8(%rbp), %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	movss	-16(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	pxor	%xmm2, %xmm2
	cvtsi2sdl	-12(%rbp), %xmm2
	movsd	.LC20(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	movl	-48(%rbp), %ecx
	movl	-12(%rbp), %edx
	movl	-8(%rbp), %esi
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	encode_tap_record
	addl	$1, -4(%rbp)
.L1462:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1463
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE176:
	.size	writeTap, .-writeTap
	.section	.rodata
.LC396:
	.string	"header.hoopSize: %d\n"
.LC397:
	.string	"header.reserved[%d] = %d\n"
.LC398:
	.string	"background: %c %c %c\n"
	.text
	.globl	readThr
	.type	readThr, @function
readThr:
.LFB177:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$496, %rsp
	movq	%rdi, -488(%rbp)
	movq	%rsi, -496(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -64(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -60(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -56(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movw	%ax, -54(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1466
	movzwl	-54(%rbp), %eax
	movzwl	%ax, %eax
	movl	%eax, %esi
	leaq	.LC396(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1466:
	movl	$0, -8(%rbp)
	jmp	.L1467
.L1468:
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16@PLT
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	movw	%ax, -52(%rbp,%rdx,2)
	movl	-8(%rbp), %eax
	cltq
	movzwl	-52(%rbp,%rax,2), %eax
	movzwl	%ax, %edx
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC397(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -8(%rbp)
.L1467:
	cmpl	$6, -8(%rbp)
	jle	.L1468
	movl	-64(%rbp), %eax
	andl	$16777215, %eax
	cmpl	$7628914, %eax
	jne	.L1469
	movl	-64(%rbp), %eax
	shrl	$24, %eax
	movl	%eax, -16(%rbp)
	cmpl	$0, -16(%rbp)
	je	.L1481
	movl	-16(%rbp), %eax
	subl	$1, %eax
	cmpl	$1, %eax
	ja	.L1471
	movq	-496(%rbp), %rax
	movl	$1, %edx
	movl	$144, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L1469
.L1471:
	movl	$0, %eax
	jmp	.L1480
.L1481:
	nop
.L1469:
	movl	$-1, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L1474
.L1476:
	movl	$0, -12(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movss	%xmm0, -20(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movss	%xmm0, -24(%rbp)
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -28(%rbp)
	movss	-20(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, -20(%rbp)
	movss	-24(%rbp), %xmm0
	movss	.LC18(%rip), %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, -24(%rbp)
	movl	-28(%rbp), %eax
	andl	$15, %eax
	cmpl	%eax, -4(%rbp)
	je	.L1475
	movl	-28(%rbp), %eax
	andl	$15, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %edx
	movq	-488(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_pattern_changeColor@PLT
	movl	$6, -12(%rbp)
.L1475:
	movl	-12(%rbp), %esi
	movss	-24(%rbp), %xmm0
	movl	-20(%rbp), %ecx
	movq	-488(%rbp), %rax
	movl	$0, %edx
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
	addl	$1, -8(%rbp)
.L1474:
	movzwl	-56(%rbp), %eax
	movzwl	%ax, %eax
	cmpl	%eax, -8(%rbp)
	jl	.L1476
	movq	-496(%rbp), %rax
	movl	$1, %edx
	movl	$16, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	leaq	-67(%rbp), %rcx
	movq	-496(%rbp), %rax
	movl	$4, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_read@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1477
	movzbl	-65(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-66(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-67(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC398(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1477:
	movl	$0, -8(%rbp)
	jmp	.L1478
.L1479:
	leaq	-480(%rbp), %rax
	addq	$3, %rax
	movl	$1280070990, (%rax)
	movb	$0, 4(%rax)
	leaq	-480(%rbp), %rax
	addq	$203, %rax
	movl	$1280070990, (%rax)
	movb	$0, 4(%rax)
	leaq	-480(%rbp), %rcx
	movq	-496(%rbp), %rax
	movl	$4, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_read@PLT
	movq	-488(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-480(%rbp), %rax
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
	addl	$1, -8(%rbp)
.L1478:
	cmpl	$15, -8(%rbp)
	jle	.L1479
	movl	$1, %eax
.L1480:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE177:
	.size	readThr, .-readThr
	.section	.rodata
.LC400:
	.string	"\377\377\377"
	.string	""
	.text
	.globl	writeThr
	.type	writeThr, @function
writeThr:
.LFB178:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$272, %rsp
	movq	%rdi, -264(%rbp)
	movq	%rsi, -272(%rbp)
	movb	$0, -5(%rbp)
	movq	-264(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, -12(%rbp)
	leaq	-64(%rbp), %rax
	movl	$28, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movzbl	-5(%rbp), %eax
	sall	$24, %eax
	orl	$7628914, %eax
	movl	%eax, -64(%rbp)
	movl	-12(%rbp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$16, %eax
	movl	%eax, -60(%rbp)
	cmpb	$1, -5(%rbp)
	je	.L1483
	cmpb	$2, -5(%rbp)
	jne	.L1484
.L1483:
	movl	-60(%rbp), %eax
	addl	$28, %eax
	movl	%eax, -60(%rbp)
.L1484:
	movl	-12(%rbp), %eax
	movw	%ax, -56(%rbp)
	movw	$5, -54(%rbp)
	movl	-64(%rbp), %edx
	movq	-272(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u32@PLT
	movl	-60(%rbp), %edx
	movq	-272(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u32@PLT
	movzwl	-56(%rbp), %eax
	movzwl	%ax, %edx
	movq	-272(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u16@PLT
	movzwl	-54(%rbp), %eax
	movzwl	%ax, %edx
	movq	-272(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u16@PLT
	movl	$0, -4(%rbp)
	jmp	.L1485
.L1486:
	movl	-4(%rbp), %eax
	cltq
	movzwl	-52(%rbp,%rax,2), %eax
	movzwl	%ax, %edx
	movq	-272(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u16@PLT
	addl	$1, -4(%rbp)
.L1485:
	cmpl	$6, -4(%rbp)
	jle	.L1486
	cmpb	$1, -5(%rbp)
	je	.L1487
	cmpb	$2, -5(%rbp)
	jne	.L1488
.L1487:
	leaq	-208(%rbp), %rax
	movl	$144, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movb	$1, -96(%rbp)
	movss	.LC399(%rip), %xmm0
	movss	%xmm0, -208(%rbp)
	movss	.LC399(%rip), %xmm0
	movss	%xmm0, -204(%rbp)
	movss	-208(%rbp), %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-272(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movss	-204(%rbp), %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-272(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movss	-200(%rbp), %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-272(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-272(%rbp), %rax
	leaq	-208(%rbp), %rdx
	leaq	12(%rdx), %rdi
	movq	%rax, %rcx
	movl	$50, %edx
	movl	$1, %esi
	call	fwrite@PLT
	movq	-272(%rbp), %rax
	leaq	-208(%rbp), %rdx
	leaq	62(%rdx), %rdi
	movq	%rax, %rcx
	movl	$50, %edx
	movl	$1, %esi
	call	fwrite@PLT
	movzbl	-96(%rbp), %eax
	movsbl	%al, %eax
	movq	-272(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc@PLT
	movq	-272(%rbp), %rax
	leaq	-208(%rbp), %rdx
	leaq	113(%rdx), %rdi
	movq	%rax, %rcx
	movl	$31, %edx
	movl	$1, %esi
	call	fwrite@PLT
.L1488:
	movl	$0, -4(%rbp)
	jmp	.L1489
.L1490:
	movl	$524288, -16(%rbp)
	movq	-264(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -240(%rbp)
	movq	%rdx, -232(%rbp)
	movss	-236(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -20(%rbp)
	movss	-232(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -24(%rbp)
	movss	-20(%rbp), %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-272(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movss	-24(%rbp), %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-272(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	-228(%rbp), %eax
	andl	$15, %eax
	orl	-16(%rbp), %eax
	movl	%eax, %edx
	movq	-272(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u32@PLT
	addl	$1, -4(%rbp)
.L1489:
	movq	-264(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1490
	movq	-272(%rbp), %rdx
	leaq	-224(%rbp), %rax
	movq	%rdx, %rcx
	movl	$16, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-272(%rbp), %rax
	movq	%rax, %rcx
	movl	$4, %edx
	movl	$1, %esi
	leaq	.LC400(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$0, -4(%rbp)
	jmp	.L1491
.L1494:
	movq	-264(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -243(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -241(%rbp)
	movq	-272(%rbp), %rax
	movl	$4, %edx
	movzbl	-243(%rbp), %ecx
	movzbl	-242(%rbp), %esi
	salq	$8, %rsi
	orq	%rcx, %rsi
	movzbl	-241(%rbp), %ecx
	salq	$16, %rcx
	orq	%rsi, %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_write@PLT
	cmpl	$15, -4(%rbp)
	jg	.L1496
	addl	$1, -4(%rbp)
.L1491:
	movq	-264(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1494
	jmp	.L1493
.L1496:
	nop
.L1493:
	movl	$16, %eax
	subl	-4(%rbp), %eax
	leal	0(,%rax,4), %edx
	movq	-272(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-272(%rbp), %rax
	movl	$16, %edx
	movl	$52, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE178:
	.size	writeThr, .-writeThr
	.globl	readTxt
	.type	readTxt, @function
readTxt:
.LFB179:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$288, %rsp
	movq	%rdi, -280(%rbp)
	movq	%rsi, -288(%rbp)
	leaq	-256(%rbp), %rcx
	movq	-288(%rbp), %rax
	movl	$99, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_readline@PLT
	leaq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -48(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1498
.L1508:
	movl	$0, -44(%rbp)
	leaq	-256(%rbp), %rcx
	movq	-288(%rbp), %rax
	movl	$99, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_readline@PLT
	leaq	-256(%rbp), %rax
	movq	%rax, -16(%rbp)
	leaq	-256(%rbp), %rax
	movq	%rax, -24(%rbp)
	leaq	-256(%rbp), %rax
	movq	%rax, -32(%rbp)
	leaq	-256(%rbp), %rax
	movq	%rax, -40(%rbp)
	leaq	-256(%rbp), %rax
	movq	%rax, -16(%rbp)
	jmp	.L1499
.L1507:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$44, %al
	je	.L1500
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	jne	.L1501
.L1500:
	movq	-16(%rbp), %rax
	movb	$0, (%rax)
	cmpl	$2, -44(%rbp)
	je	.L1502
	cmpl	$2, -44(%rbp)
	jg	.L1510
	cmpl	$0, -44(%rbp)
	je	.L1504
	cmpl	$1, -44(%rbp)
	je	.L1505
	jmp	.L1510
.L1504:
	movq	-16(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -24(%rbp)
	jmp	.L1506
.L1505:
	movq	-16(%rbp), %rax
	addq	$7, %rax
	movq	%rax, -32(%rbp)
	jmp	.L1506
.L1502:
	movq	-16(%rbp), %rax
	addq	$7, %rax
	movq	%rax, -40(%rbp)
	jmp	.L1506
.L1510:
	nop
.L1506:
	addl	$1, -44(%rbp)
.L1501:
	addq	$1, -16(%rbp)
.L1499:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L1507
	leaq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	atof@PLT
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -268(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	atof@PLT
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -264(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -260(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -272(%rbp)
	movl	-260(%rbp), %edx
	movl	-272(%rbp), %esi
	movss	-264(%rbp), %xmm0
	movl	-268(%rbp), %ecx
	movq	-280(%rbp), %rax
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
	addl	$1, -4(%rbp)
.L1498:
	movl	-4(%rbp), %eax
	cmpl	-48(%rbp), %eax
	jl	.L1508
	leaq	.LC42(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-288(%rbp), %rdx
	movq	-280(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readDst
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE179:
	.size	readTxt, .-readTxt
	.section	.rodata
.LC401:
	.string	"%u\n"
.LC402:
	.string	"%.1f,%.1f color:%i flags:%i\n"
	.text
	.globl	writeTxt
	.type	writeTxt, @function
writeTxt:
.LFB180:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, %edx
	movq	-48(%rbp), %rax
	leaq	.LC401(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movl	$0, -4(%rbp)
	jmp	.L1512
.L1513:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movl	-32(%rbp), %ecx
	movl	-20(%rbp), %edx
	movss	-24(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-28(%rbp), %xmm1
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm1, %xmm2
	movq	%xmm2, %rsi
	movq	-48(%rbp), %rax
	movapd	%xmm0, %xmm1
	movq	%rsi, %xmm0
	leaq	.LC402(%rip), %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
	addl	$1, -4(%rbp)
.L1512:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1513
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE180:
	.size	writeTxt, .-writeTxt
	.globl	readU00
	.type	readU00, @function
readU00:
.LFB181:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$448, %rsp
	movq	%rdi, -440(%rbp)
	movq	%rsi, -448(%rbp)
	movb	$0, -5(%rbp)
	movb	$0, -6(%rbp)
	movl	$0, -12(%rbp)
	movq	-448(%rbp), %rax
	movl	$256, %esi
	movq	%rax, %rdi
	call	check_header_present@PLT
	testl	%eax, %eax
	jne	.L1516
	movl	$0, %eax
	jmp	.L1528
.L1516:
	movq	-448(%rbp), %rax
	movl	$0, %edx
	movl	$8, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	$0, -4(%rbp)
	jmp	.L1518
.L1519:
	leaq	-432(%rbp), %rcx
	movq	-448(%rbp), %rax
	movl	$3, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_read@PLT
	movb	$0, -229(%rbp)
	movb	$0, -429(%rbp)
	movq	-440(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-432(%rbp), %rax
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
	addl	$1, -4(%rbp)
.L1518:
	cmpl	$15, -4(%rbp)
	jle	.L1519
	movq	-448(%rbp), %rax
	movl	$0, %edx
	movl	$256, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L1520
.L1527:
	movzbl	-17(%rbp), %eax
	cmpb	$-8, %al
	je	.L1521
	movzbl	-17(%rbp), %eax
	cmpb	$-121, %al
	je	.L1521
	movzbl	-17(%rbp), %eax
	cmpb	$-111, %al
	je	.L1521
	movzbl	-17(%rbp), %eax
	movzbl	%al, %eax
	andl	$15, %eax
	testl	%eax, %eax
	jne	.L1522
	movl	$0, -12(%rbp)
	jmp	.L1523
.L1522:
	movzbl	-17(%rbp), %eax
	movzbl	%al, %eax
	andl	$31, %eax
	cmpl	$1, %eax
	jne	.L1524
	movl	$1, -12(%rbp)
	jmp	.L1523
.L1524:
	movzbl	-17(%rbp), %eax
	movzbl	%al, %eax
	andl	$15, %eax
	testl	%eax, %eax
	jle	.L1523
	movl	$4, -12(%rbp)
.L1523:
	movzbl	-17(%rbp), %eax
	movzbl	%al, %eax
	andl	$32, %eax
	testl	%eax, %eax
	setg	%al
	movb	%al, -13(%rbp)
	movzbl	-17(%rbp), %eax
	movzbl	%al, %eax
	andl	$64, %eax
	testl	%eax, %eax
	setg	%al
	movb	%al, -14(%rbp)
	movzbl	-15(%rbp), %eax
	movb	%al, -5(%rbp)
	movzbl	-16(%rbp), %eax
	movb	%al, -6(%rbp)
	cmpb	$0, -13(%rbp)
	je	.L1525
	movzbl	-5(%rbp), %eax
	negl	%eax
	movb	%al, -5(%rbp)
.L1525:
	cmpb	$0, -14(%rbp)
	je	.L1526
	movzbl	-6(%rbp), %eax
	negl	%eax
	movb	%al, -6(%rbp)
.L1526:
	movsbl	-6(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movsbl	-5(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-12(%rbp), %esi
	movq	-440(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L1520:
	movq	-448(%rbp), %rdx
	leaq	-17(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L1527
.L1521:
	movl	$1, %eax
.L1528:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE181:
	.size	readU00, .-readU00
	.section	.rodata
.LC403:
	.string	"writeU00 not implemented."
	.text
	.globl	writeU00
	.type	writeU00, @function
writeU00:
.LFB182:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC403(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1530
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC151(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1530:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE182:
	.size	writeU00, .-writeU00
	.section	.rodata
.LC404:
	.string	"file length: %d\n"
	.text
	.globl	readU01
	.type	readU01, @function
readU01:
.LFB183:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	movl	$0, -4(%rbp)
	movq	-48(%rbp), %rax
	movl	$256, %esi
	movq	%rax, %rdi
	call	check_header_present@PLT
	testl	%eax, %eax
	jne	.L1533
	movl	$0, %eax
	jmp	.L1544
.L1533:
	movq	-48(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -20(%rbp)
	movq	-48(%rbp), %rax
	movl	$0, %edx
	movl	$256, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1536
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC404(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L1536
.L1543:
	movzbl	-23(%rbp), %eax
	cmpb	$-8, %al
	je	.L1537
	movzbl	-23(%rbp), %eax
	cmpb	$-121, %al
	je	.L1537
	movzbl	-23(%rbp), %eax
	cmpb	$-111, %al
	je	.L1537
	movzbl	-23(%rbp), %eax
	movzbl	%al, %eax
	andl	$15, %eax
	testl	%eax, %eax
	jne	.L1538
	movl	$0, -4(%rbp)
	jmp	.L1539
.L1538:
	movzbl	-23(%rbp), %eax
	movzbl	%al, %eax
	andl	$31, %eax
	cmpl	$1, %eax
	jne	.L1540
	movl	$1, -4(%rbp)
	jmp	.L1539
.L1540:
	movzbl	-23(%rbp), %eax
	movzbl	%al, %eax
	andl	$15, %eax
	testl	%eax, %eax
	jle	.L1539
	movl	$4, -4(%rbp)
.L1539:
	movzbl	-23(%rbp), %eax
	movzbl	%al, %eax
	andl	$32, %eax
	testl	%eax, %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, -12(%rbp)
	movzbl	-23(%rbp), %eax
	movzbl	%al, %eax
	andl	$64, %eax
	testl	%eax, %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, -16(%rbp)
	movzbl	-21(%rbp), %eax
	movb	%al, -5(%rbp)
	movzbl	-22(%rbp), %eax
	movb	%al, -6(%rbp)
	cmpl	$0, -12(%rbp)
	je	.L1541
	movzbl	-5(%rbp), %eax
	negl	%eax
	movb	%al, -5(%rbp)
.L1541:
	cmpl	$0, -16(%rbp)
	je	.L1542
	movzbl	-6(%rbp), %eax
	negl	%eax
	movb	%al, -6(%rbp)
.L1542:
	movsbl	-6(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movsbl	-5(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-4(%rbp), %esi
	movq	-40(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L1536:
	movq	-48(%rbp), %rdx
	leaq	-23(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L1543
.L1537:
	movl	$1, %eax
.L1544:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE183:
	.size	readU01, .-readU01
	.globl	writeU01
	.type	writeU01, @function
writeU01:
.LFB184:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1546
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC151(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1546:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE184:
	.size	writeU01, .-writeU01
	.globl	vipDecodingTable
	.section	.rodata
	.align 32
	.type	vipDecodingTable, @object
	.size	vipDecodingTable, 400
vipDecodingTable:
	.string	".\202\344o8\251\334\306{\266(\254\375\252\212Nv.\360\344%\033\212hN\222\271\264\225\360>\357\367@$\03091\273\341S\250\037\261:\007\373\313\346"
	.string	"\201P\016@\341,sP\r\221\326\n]\326\213\270b\256G"
	.string	"SZ\267\200\252(\367]p^,\013\230\343\240\230`G\211\233\202\373@\311\264"
	.ascii	"\016hj\036\t\205\300S\201\321\230\211\257\350\205O\343i\211\003"
	.ascii	"\241.\217\317\355\221\237X\036\326\204<\t'\275\364\303\220\300"
	.ascii	"Q\033+c\274\271=@Mbo\340\214\365]\b\375=P6\327\311\311C\344-"
	.ascii	"\313\225\266\364\r\352\302\375f?^\275i\006*\003\031G+\3378\352"
	.ascii	"O\200I\225\262\326\371\232u\364\330\233\035\260\244i\333\251"
	.ascii	"!yo\330\3363\376\237\004\345\232k\233s\203b|\271fv\362[\311^"
	.ascii	"\374t\252l\361\315\223\316\351\200S\003;\227K9v\302\301V\313"
	.ascii	"p\375;>RW\201]V\215Q\220\324v\327\325\026\002m\362M\341\016\226"
	.ascii	"O\241:\240`Yd\004\032\344g\266\355?t U\037\373#\222\221S\310"
	.ascii	"e\253\235Q\326s\336\001\261\200\267\300\326\200\034.<\203c\356"
	.ascii	"\2743%\342\016zg\336?q\024I\234\222\223\r&\232\016\332\355o\244"
	.ascii	"\211\f\033\360\241\337\341\236<\004x\344\253m\377\234\257\312"
	.ascii	"\307\210\027\234\345\2673m\334\355\217l\030\035q\006\261\305"
	.ascii	"\342\317\023w\201\305\267\n\024\nk@&\240\210\321bj\263P\022\271"
	.ascii	"\233\265\203\2337"
	.text
	.globl	vipDecodeByte
	.type	vipDecodeByte, @function
vipDecodeByte:
.LFB185:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	testb	%al, %al
	jns	.L1549
	movzbl	-4(%rbp), %eax
	negl	%eax
	movzbl	%al, %eax
	negl	%eax
	jmp	.L1550
.L1549:
	movzbl	-4(%rbp), %eax
.L1550:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE185:
	.size	vipDecodeByte, .-vipDecodeByte
	.globl	vipDecodeStitchType
	.type	vipDecodeStitchType, @function
vipDecodeStitchType:
.LFB186:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	cmpl	$144, %eax
	je	.L1552
	cmpl	$144, %eax
	jg	.L1553
	cmpl	$132, %eax
	je	.L1554
	cmpl	$132, %eax
	jg	.L1553
	cmpl	$128, %eax
	je	.L1555
	cmpl	$129, %eax
	je	.L1556
	jmp	.L1553
.L1555:
	movl	$0, %eax
	jmp	.L1557
.L1556:
	movl	$2, %eax
	jmp	.L1557
.L1554:
	movl	$4, %eax
	jmp	.L1557
.L1552:
	movl	$16, %eax
	jmp	.L1557
.L1553:
	movl	$0, %eax
.L1557:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE186:
	.size	vipDecodeStitchType, .-vipDecodeStitchType
	.section	.rodata
	.align 8
.LC405:
	.string	"ERROR: format-vip.c vipDecompressData(), cannot allocate memory for decompressedData"
	.text
	.globl	vipDecompressData
	.type	vipDecompressData, @function
vipDecompressData:
.LFB187:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	-32(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L1559
	leaq	.LC405(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1560
.L1559:
	leaq	-32(%rbp), %rcx
	movq	-8(%rbp), %rdx
	movl	-28(%rbp), %esi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	hus_decompress@PLT
	movq	-8(%rbp), %rax
.L1560:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE187:
	.size	vipDecompressData, .-vipDecompressData
	.section	.rodata
	.align 8
.LC406:
	.string	"ERROR: file shorter than header."
	.align 8
.LC407:
	.string	"ERROR: format-vip.c readVip(), "
	.align 8
.LC408:
	.string	"cannot allocate memory for decodedColors"
	.align 8
.LC409:
	.string	"ERROR: format-vip.c readVip(), cannot allocate memory for attributeData"
	.align 8
.LC410:
	.string	"ERROR: format-vip.c readVip(), cannot allocate memory for xData"
	.align 8
.LC411:
	.string	"ERROR: format-vip.c readVip(), cannot allocate memory for yData"
	.text
	.globl	readVip
	.type	readVip, @function
readVip:
.LFB188:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$584, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -568(%rbp)
	movq	%rsi, -576(%rbp)
	movb	$0, -21(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -48(%rbp)
	movq	$0, -56(%rbp)
	movq	$0, -64(%rbp)
	movq	$0, -72(%rbp)
	movq	$0, -80(%rbp)
	movq	-576(%rbp), %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	check_header_present@PLT
	movl	%eax, -84(%rbp)
	cmpl	$0, -84(%rbp)
	jne	.L1562
	leaq	.LC406(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L1575
.L1562:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -144(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -140(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -136(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -132(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -130(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -128(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -126(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -124(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -120(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -116(%rbp)
	leaq	-144(%rbp), %rax
	leaq	32(%rax), %rcx
	movq	-576(%rbp), %rax
	movl	$8, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	read_n_bytes
	testb	%al, %al
	jne	.L1564
	movl	$0, %eax
	jmp	.L1575
.L1564:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -104(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -100(%rbp)
	movl	-136(%rbp), %eax
	sall	$2, %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L1565
	leaq	.LC407(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC408(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1575
.L1565:
	movl	$0, -20(%rbp)
	jmp	.L1566
.L1567:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -89(%rbp)
	movl	-20(%rbp), %eax
	cltq
	leaq	vipDecodingTable(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	xorb	-89(%rbp), %al
	movb	%al, -90(%rbp)
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-40(%rbp), %rax
	addq	%rax, %rdx
	movzbl	-90(%rbp), %eax
	xorb	-21(%rbp), %al
	movb	%al, (%rdx)
	movzbl	-89(%rbp), %eax
	movb	%al, -21(%rbp)
	addl	$1, -20(%rbp)
.L1566:
	movl	-136(%rbp), %eax
	sall	$2, %eax
	cmpl	%eax, -20(%rbp)
	jl	.L1567
	movl	$0, -20(%rbp)
	jmp	.L1568
.L1569:
	movl	-20(%rbp), %eax
	sall	$2, %eax
	movl	%eax, -88(%rbp)
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movb	%al, -560(%rbp)
	movl	-88(%rbp), %eax
	cltq
	leaq	1(%rax), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movb	%al, -559(%rbp)
	movl	-88(%rbp), %eax
	cltq
	leaq	2(%rax), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movb	%al, -558(%rbp)
	movq	-568(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-560(%rbp), %rax
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
	addl	$1, -20(%rbp)
.L1568:
	movl	-136(%rbp), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L1569
	movl	-124(%rbp), %eax
	movslq	%eax, %rcx
	movq	-576(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	-120(%rbp), %edx
	movl	-124(%rbp), %eax
	subl	%eax, %edx
	movslq	%edx, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L1570
	leaq	.LC409(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1575
.L1570:
	movl	-120(%rbp), %edx
	movl	-124(%rbp), %eax
	subl	%eax, %edx
	movslq	%edx, %rdx
	movq	-576(%rbp), %rcx
	movq	-32(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movl	-140(%rbp), %edx
	movl	-120(%rbp), %ecx
	movl	-124(%rbp), %eax
	subl	%eax, %ecx
	movq	-32(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	vipDecompressData
	movq	%rax, -48(%rbp)
	movl	-120(%rbp), %eax
	movslq	%eax, %rcx
	movq	-576(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	-116(%rbp), %edx
	movl	-120(%rbp), %eax
	subl	%eax, %edx
	movslq	%edx, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -56(%rbp)
	cmpq	$0, -56(%rbp)
	jne	.L1571
	leaq	.LC410(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1575
.L1571:
	movl	-116(%rbp), %edx
	movl	-120(%rbp), %eax
	subl	%eax, %edx
	movslq	%edx, %rdx
	movq	-576(%rbp), %rcx
	movq	-56(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movl	-140(%rbp), %edx
	movl	-116(%rbp), %ecx
	movl	-120(%rbp), %eax
	subl	%eax, %ecx
	movq	-56(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	vipDecompressData
	movq	%rax, -64(%rbp)
	movl	-116(%rbp), %eax
	movslq	%eax, %rcx
	movq	-576(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	-116(%rbp), %eax
	movl	-84(%rbp), %edx
	subl	%eax, %edx
	movslq	%edx, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -72(%rbp)
	cmpq	$0, -72(%rbp)
	jne	.L1572
	leaq	.LC411(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1575
.L1572:
	movl	-116(%rbp), %eax
	movl	-84(%rbp), %edx
	subl	%eax, %edx
	movslq	%edx, %rdx
	movq	-576(%rbp), %rcx
	movq	-72(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movl	-140(%rbp), %edx
	movl	-116(%rbp), %eax
	movl	-84(%rbp), %ecx
	subl	%eax, %ecx
	movq	-72(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	vipDecompressData
	movq	%rax, -80(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L1573
.L1574:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	vipDecodeStitchType
	movl	%eax, %ebx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	vipDecodeByte
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movss	%xmm2, -580(%rbp)
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	vipDecodeByte
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movq	-568(%rbp), %rax
	movl	$1, %edx
	movl	%ebx, %esi
	movss	-580(%rbp), %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	addl	$1, -20(%rbp)
.L1573:
	movl	-140(%rbp), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L1574
	movq	-568(%rbp), %rax
	movl	$1, %edx
	movl	$16, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free@PLT
	movl	$1, %eax
.L1575:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE188:
	.size	readVip, .-readVip
	.section	.rodata
	.align 8
.LC412:
	.string	"ERROR: format-vip.c vipCompressData(), cannot allocate memory for compressedData"
	.text
	.globl	vipCompressData
	.type	vipCompressData, @function
vipCompressData:
.LFB189:
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
	movl	-28(%rbp), %eax
	addl	%eax, %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L1577
	leaq	.LC412(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1578
.L1577:
	movq	-40(%rbp), %rcx
	movq	-8(%rbp), %rdx
	movl	-28(%rbp), %esi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	hus_compress@PLT
	movq	-8(%rbp), %rax
.L1578:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE189:
	.size	vipCompressData, .-vipCompressData
	.globl	vipEncodeByte
	.type	vipEncodeByte, @function
vipEncodeByte:
.LFB190:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movss	%xmm0, -4(%rbp)
	movl	-4(%rbp), %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE190:
	.size	vipEncodeByte, .-vipEncodeByte
	.globl	vipEncodeStitchType
	.type	vipEncodeStitchType, @function
vipEncodeStitchType:
.LFB191:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	cmpl	$16, -4(%rbp)
	je	.L1582
	cmpl	$16, -4(%rbp)
	jg	.L1583
	cmpl	$4, -4(%rbp)
	je	.L1584
	cmpl	$4, -4(%rbp)
	jg	.L1583
	cmpl	$0, -4(%rbp)
	je	.L1585
	cmpl	$0, -4(%rbp)
	js	.L1583
	movl	-4(%rbp), %eax
	subl	$1, %eax
	cmpl	$1, %eax
	ja	.L1583
	jmp	.L1588
.L1585:
	movl	$-128, %eax
	jmp	.L1587
.L1588:
	movl	$-127, %eax
	jmp	.L1587
.L1584:
	movl	$-124, %eax
	jmp	.L1587
.L1582:
	movl	$-112, %eax
	jmp	.L1587
.L1583:
	movl	$-128, %eax
.L1587:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE191:
	.size	vipEncodeStitchType, .-vipEncodeStitchType
	.section	.rodata
.LC413:
	.string	"VIP not yet implemented."
	.text
	.globl	writeVip
	.type	writeVip, @function
writeVip:
.LFB192:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$192, %rsp
	movq	%rdi, -184(%rbp)
	movq	%rsi, -192(%rbp)
	movl	$0, -132(%rbp)
	movl	$0, -136(%rbp)
	movl	$0, -140(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -100(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -104(%rbp)
	movq	$0, -96(%rbp)
	movq	$0, -64(%rbp)
	movq	$0, -72(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -76(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -80(%rbp)
	movl	$0, -84(%rbp)
	movl	$0, -4(%rbp)
	movq	$0, -16(%rbp)
	movq	$0, -24(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -48(%rbp)
	movb	$0, -49(%rbp)
	leaq	.LC413(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE192:
	.size	writeVip, .-writeVip
	.section	.rodata
	.align 8
.LC414:
	.string	"ERROR: format-vp3.c vp3ReadString(), file argument is null"
	.align 8
.LC415:
	.string	"ERROR: format-vp3.c vp3ReadString(), cannot allocate memory for charString"
	.text
	.globl	vp3ReadString
	.type	vp3ReadString, @function
vp3ReadString:
.LFB193:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	$0, -8(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L1592
	leaq	.LC414(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1593
.L1592:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16be@PLT
	movw	%ax, -10(%rbp)
	movswq	-10(%rbp), %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L1594
	leaq	.LC415(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1593
.L1594:
	movswq	-10(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-8(%rbp), %rax
.L1593:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE193:
	.size	vp3ReadString, .-vp3ReadString
	.globl	vp3Decode
	.type	vp3Decode, @function
vp3Decode:
.LFB194:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	cmpb	$-128, -4(%rbp)
	jbe	.L1596
	movzbl	-4(%rbp), %eax
	negl	%eax
	movzbl	%al, %eax
	negl	%eax
	jmp	.L1597
.L1596:
	movzbl	-4(%rbp), %eax
.L1597:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE194:
	.size	vp3Decode, .-vp3Decode
	.globl	vp3DecodeInt16
	.type	vp3DecodeInt16, @function
vp3DecodeInt16:
.LFB195:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movw	%ax, -4(%rbp)
	cmpw	$-32768, -4(%rbp)
	jbe	.L1599
	movzwl	-4(%rbp), %eax
	jmp	.L1600
.L1599:
	movzwl	-4(%rbp), %eax
.L1600:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE195:
	.size	vp3DecodeInt16, .-vp3DecodeInt16
	.section	.rodata
	.align 8
.LC416:
	.string	"ERROR: format-vp3.c vp3ReadHoopSection(), file argument is null"
	.text
	.globl	vp3ReadHoopSection
	.type	vp3ReadHoopSection, @function
vp3ReadHoopSection:
.LFB196:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$104, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	cmpq	$0, -112(%rbp)
	jne	.L1602
	leaq	.LC416(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, -92(%rbp)
	movl	$0, -88(%rbp)
	movl	$0, -96(%rbp)
	movl	$0, -84(%rbp)
	movl	$0, -80(%rbp)
	movb	$0, -76(%rbp)
	movb	$0, -75(%rbp)
	movw	$0, -74(%rbp)
	movl	$0, -72(%rbp)
	movl	$0, -68(%rbp)
	movl	$0, -64(%rbp)
	movl	$0, -60(%rbp)
	movb	$0, -56(%rbp)
	movb	$0, -55(%rbp)
	movb	$0, -54(%rbp)
	movl	$0, -52(%rbp)
	movl	$0, -48(%rbp)
	movl	$0, -44(%rbp)
	movl	$0, -40(%rbp)
	movl	$0, -32(%rbp)
	movl	$0, -36(%rbp)
	movq	-104(%rbp), %rax
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movl	-32(%rbp), %edx
	movl	%edx, 64(%rax)
	jmp	.L1604
.L1602:
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -96(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -92(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -88(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -84(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -80(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -76(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -75(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16be@PLT
	movw	%ax, -74(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -72(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -68(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -64(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -60(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -56(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -55(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -54(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -52(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -48(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -44(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -40(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -36(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -32(%rbp)
	movq	-104(%rbp), %rax
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movl	-32(%rbp), %edx
	movl	%edx, 64(%rax)
.L1604:
	movq	-104(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE196:
	.size	vp3ReadHoopSection, .-vp3ReadHoopSection
	.section	.rodata
.LC417:
	.string	"some: %d\n"
.LC418:
	.string	"softwareVendorString: %s\n"
.LC419:
	.string	"someShort: %d\n"
.LC420:
	.string	"someByte: %d\n"
.LC421:
	.string	"bytesRemainingInFile: %d\n"
.LC422:
	.string	"hoopConfigurationOffset: %d\n"
.LC423:
	.string	"anotherCommentString: %s\n"
.LC424:
	.string	"v%d = %d\n"
	.align 8
.LC425:
	.string	"ERROR: Failed to read magicCode."
	.align 8
.LC426:
	.string	"anotherSoftwareVendorString: %s\n"
	.align 8
.LC427:
	.string	"ERROR: format-vp3.c Color Check Byte #1: 0 == %d\n"
	.align 8
.LC428:
	.string	"ERROR: format-vp3.c Color Check Byte #2: 5 == %d\n"
	.align 8
.LC429:
	.string	"ERROR: format-vp3.c Color Check Byte #3: 0 == %d\n"
.LC431:
	.string	"number of bytes in color: %d\n"
.LC432:
	.string	"thread color number: %s\n"
.LC433:
	.string	"offset to next color x: %d\n"
.LC434:
	.string	"offset to next color y: %d\n"
.LC435:
	.string	"color name: %s\n"
.LC436:
	.string	"thread vendor: %s\n"
.LC437:
	.string	"fileCommentString: %s\n"
	.align 8
.LC438:
	.string	"ERROR: format-vp3.c could not read stitch block in entirety"
	.text
	.globl	readVp3
	.type	readVp3, @function
readVp3:
.LFB197:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$656, %rsp
	movq	%rdi, -568(%rbp)
	movq	%rsi, -576(%rbp)
	movq	$0, -24(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -48(%rbp)
	movq	-576(%rbp), %rdx
	leaq	-140(%rbp), %rax
	movq	%rdx, %rcx
	movl	$5, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-576(%rbp), %rdx
	leaq	-141(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L1606
	leaq	.LC188(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L1606:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1607
	movzbl	-141(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC417(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1607:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	vp3ReadString
	movq	%rax, -24(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1608
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC418(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1608:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	movw	%ax, -50(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1609
	movswl	-50(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC419(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1609:
	movq	-576(%rbp), %rdx
	leaq	-148(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L1610
	leaq	.LC188(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L1610:
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1611
	movzbl	-148(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC420(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1611:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -56(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1612
	movl	-56(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC421(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1612:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	vp3ReadString
	movq	%rax, -40(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -60(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1613
	movl	-60(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC422(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1613:
	leaq	-656(%rbp), %rax
	movq	-576(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	vp3ReadHoopSection
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	vp3ReadString
	movq	%rax, -48(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1614
	movq	-48(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC423(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1614:
	movl	$0, -12(%rbp)
	jmp	.L1615
.L1617:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -135(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1616
	movzbl	-135(%rbp), %edx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC424(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1616:
	addl	$1, -12(%rbp)
.L1615:
	cmpl	$17, -12(%rbp)
	jle	.L1617
	movq	-576(%rbp), %rdx
	leaq	-147(%rbp), %rax
	movq	%rdx, %rcx
	movl	$6, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$6, %rax
	je	.L1618
	leaq	.LC425(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1633
.L1618:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	vp3ReadString
	movq	%rax, -32(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1620
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC426(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L1620:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16be@PLT
	cwtl
	movl	%eax, -64(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	cltq
	movq	%rax, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L1621
.L1632:
	movb	$0, -357(%rbp)
	movb	$0, -557(%rbp)
	movq	-8(%rbp), %rcx
	movq	-576(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC427(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC428(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC429(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	cltq
	movq	%rax, -8(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	addq	%rax, -8(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -68(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -72(%rbp)
	movl	-72(%rbp), %eax
	negl	%eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC430(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-68(%rbp), %xmm0
	movsd	.LC430(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movq	-568(%rbp), %rax
	movl	$1, %edx
	movl	$1, %esi
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs@PLT
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -73(%rbp)
	movq	-576(%rbp), %rax
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	leaq	-560(%rbp), %rcx
	movq	-576(%rbp), %rax
	movl	$3, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_read@PLT
	movq	-568(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-560(%rbp), %rax
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
	movsbl	-73(%rbp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	$1, %eax
	movslq	%eax, %rcx
	movq	-576(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	vp3ReadString
	movq	%rax, -88(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	vp3ReadString
	movq	%rax, -96(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	vp3ReadString
	movq	%rax, -104(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -108(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -112(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16be@PLT
	cwtl
	movl	%eax, -116(%rbp)
	movl	-116(%rbp), %eax
	movslq	%eax, %rcx
	movq	-576(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32be@PLT
	movl	%eax, -120(%rbp)
	movq	-576(%rbp), %rax
	movl	$1, %edx
	movl	$3, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1623
	movl	-120(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC431(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-88(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC432(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-108(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC433(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-112(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC434(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-96(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC435(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-104(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC436(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC437(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L1623
.L1630:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -124(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movzbl	%al, %eax
	movl	%eax, %edi
	call	vp3Decode
	movl	%eax, -128(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movzbl	%al, %eax
	movl	%eax, %edi
	call	vp3Decode
	movl	%eax, -132(%rbp)
	cmpl	$128, -128(%rbp)
	jne	.L1624
	cmpl	$3, -132(%rbp)
	je	.L1634
	cmpl	$3, -132(%rbp)
	jg	.L1635
	cmpl	$0, -132(%rbp)
	je	.L1634
	cmpl	$1, -132(%rbp)
	je	.L1627
	jmp	.L1635
.L1627:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16be@PLT
	movw	%ax, -134(%rbp)
	movzwl	-134(%rbp), %eax
	movzwl	%ax, %eax
	movl	%eax, %edi
	call	vp3DecodeInt16
	cwtl
	movl	%eax, -128(%rbp)
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16be@PLT
	movw	%ax, -134(%rbp)
	movzwl	-134(%rbp), %eax
	movzwl	%ax, %eax
	movl	%eax, %edi
	call	vp3DecodeInt16
	cwtl
	movl	%eax, -132(%rbp)
	movq	-576(%rbp), %rax
	movl	$1, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-132(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-128(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm4, %xmm4
	cvtsd2ss	%xmm0, %xmm4
	movd	%xmm4, %ecx
	movq	-568(%rbp), %rax
	movl	$1, %edx
	movl	$2, %esi
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L1629
.L1624:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-132(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-128(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm5, %xmm5
	cvtsd2ss	%xmm0, %xmm5
	movd	%xmm5, %ecx
	movq	-568(%rbp), %rax
	movl	$1, %edx
	movl	$0, %esi
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L1629
.L1634:
	nop
	jmp	.L1629
.L1635:
	nop
.L1629:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rdx
	movl	-124(%rbp), %eax
	cltq
	cmpq	%rax, %rdx
	jne	.L1623
	leaq	.LC438(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1633
.L1623:
	movq	-576(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	-8(%rbp), %rdx
	subq	$1, %rdx
	cmpq	%rdx, %rax
	jl	.L1630
	movl	-12(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, -64(%rbp)
	jle	.L1631
	movq	-568(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	pxor	%xmm1, %xmm1
	movl	.LC17(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L1631:
	addl	$1, -12(%rbp)
.L1621:
	movl	-12(%rbp), %eax
	cmpl	-64(%rbp), %eax
	jl	.L1632
	movq	-568(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movl	$1, %eax
.L1633:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE197:
	.size	readVp3, .-readVp3
	.globl	vp3WriteStringLen
	.type	vp3WriteStringLen, @function
vp3WriteStringLen:
.LFB198:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movl	-20(%rbp), %eax
	movzwl	%ax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u16be@PLT
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rcx
	movq	-16(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE198:
	.size	vp3WriteStringLen, .-vp3WriteStringLen
	.globl	vp3WriteString
	.type	vp3WriteString, @function
vp3WriteString:
.LFB199:
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
	movq	%rax, %rdi
	call	strlen@PLT
	movl	%eax, %edx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	vp3WriteStringLen
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE199:
	.size	vp3WriteString, .-vp3WriteString
	.section	.rodata
.LC439:
	.string	"Patching byte count: %d\n"
	.text
	.globl	vp3PatchByteCount
	.type	vp3PatchByteCount, @function
vp3PatchByteCount:
.LFB200:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -4(%rbp)
	movl	-28(%rbp), %eax
	movslq	%eax, %rcx
	movq	-24(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	-4(%rbp), %eax
	subl	-28(%rbp), %eax
	movl	%eax, %edx
	movl	-32(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, %esi
	leaq	.LC439(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-4(%rbp), %eax
	subl	-28(%rbp), %eax
	movl	%eax, %edx
	movl	-32(%rbp), %eax
	addl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	-24(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE200:
	.size	vp3PatchByteCount, .-vp3PatchByteCount
	.section	.rodata
.LC441:
	.string	"%vsm%"
	.string	""
.LC442:
	.string	"Embroidermodder"
.LC443:
	.string	""
	.string	"\002"
	.string	""
.LC444:
	.string	""
.LC446:
	.string	"\f"
	.string	"\001"
	.string	"\003"
	.string	""
.LC447:
	.string	"xxPP\001"
	.string	""
.LC448:
	.string	"%d\n"
	.align 8
.LC449:
	.string	"format-vp3.c DEBUG %d, %f, %f\n"
.LC450:
	.string	"last %f %f %d\n"
.LC451:
	.string	"\001"
	.string	""
	.align 8
.LC452:
	.string	"format-vp3.c writeVp3(), switching to color (%d, %d, %d)\n"
.LC453:
	.string	""
	.string	""
	.string	"\005"
.LC454:
	.string	"#%02x%02x%02x"
	.text
	.globl	writeVp3
	.type	writeVp3, @function
writeVp3:
.LFB201:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
	movq	%rdi, -120(%rbp)
	movq	%rsi, -128(%rbp)
	movl	$1, -4(%rbp)
	movb	$-2, -83(%rbp)
	movb	$-2, -82(%rbp)
	movb	$-2, -81(%rbp)
	leaq	-80(%rbp), %rax
	movq	-120(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_bounds@PLT
	movq	-120(%rbp), %rax
	movss	.LC440(%rip), %xmm1
	movl	.LC440(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_correctForMaxStitchLength@PLT
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rcx
	movl	$6, %edx
	movl	$1, %esi
	leaq	.LC441(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-128(%rbp), %rax
	leaq	.LC442(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	vp3WriteString
	movq	-128(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	leaq	.LC443(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -12(%rbp)
	movq	-128(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-128(%rbp), %rax
	leaq	.LC444(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	vp3WriteString
	movss	-80(%rbp), %xmm1
	movss	-72(%rbp), %xmm0
	addss	%xmm0, %xmm1
	movss	.LC445(%rip), %xmm0
	mulss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-128(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movss	-76(%rbp), %xmm1
	movss	-68(%rbp), %xmm0
	addss	%xmm0, %xmm1
	movss	.LC445(%rip), %xmm0
	mulss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-128(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movss	-80(%rbp), %xmm1
	movss	.LC445(%rip), %xmm0
	mulss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-128(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movss	-76(%rbp), %xmm1
	movss	.LC445(%rip), %xmm0
	mulss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-128(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movq	-128(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	fputc@PLT
	movq	-120(%rbp), %rax
	movzbl	-83(%rbp), %edx
	movzbl	-82(%rbp), %ecx
	salq	$8, %rcx
	orq	%rdx, %rcx
	movzbl	-81(%rbp), %edx
	salq	$16, %rdx
	orq	%rcx, %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_color_count@PLT
	movl	%eax, -16(%rbp)
	movq	-128(%rbp), %rdx
	movl	-16(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rcx
	movl	$6, %edx
	movl	$1, %esi
	leaq	.LC446(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -20(%rbp)
	movq	-128(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-128(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movq	-128(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movq	-128(%rbp), %rax
	movl	$3, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movss	-80(%rbp), %xmm1
	movss	-72(%rbp), %xmm0
	addss	%xmm0, %xmm1
	movss	.LC445(%rip), %xmm0
	mulss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-128(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movss	-76(%rbp), %xmm1
	movss	-68(%rbp), %xmm0
	addss	%xmm0, %xmm1
	movss	.LC445(%rip), %xmm0
	mulss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-128(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movss	-80(%rbp), %xmm1
	movss	.LC445(%rip), %xmm0
	mulss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-128(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movss	-76(%rbp), %xmm1
	movss	.LC445(%rip), %xmm0
	mulss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-128(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movss	-72(%rbp), %xmm1
	movss	.LC445(%rip), %xmm0
	mulss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-128(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movss	-68(%rbp), %xmm1
	movss	.LC445(%rip), %xmm0
	mulss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-128(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movq	-128(%rbp), %rax
	leaq	.LC444(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	vp3WriteString
	movq	-128(%rbp), %rax
	movl	$25700, %esi
	movq	%rax, %rdi
	call	emb_write_i16be@PLT
	movq	-128(%rbp), %rax
	movl	$4096, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movq	-128(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movq	-128(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movq	-128(%rbp), %rax
	movl	$4096, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rcx
	movl	$6, %edx
	movl	$1, %esi
	leaq	.LC447(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-128(%rbp), %rax
	leaq	.LC444(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	vp3WriteString
	movl	-16(%rbp), %eax
	movswl	%ax, %edx
	movq	-128(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16be@PLT
	movl	$0, -8(%rbp)
	jmp	.L1640
.L1644:
	movq	$0, -91(%rbp)
	movl	$0, -24(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -108(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -104(%rbp)
	movl	$0, -100(%rbp)
	movl	$0, -112(%rbp)
	cmpl	$0, -4(%rbp)
	jne	.L1641
	movq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	fputc@PLT
.L1641:
	movq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	fputc@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$5, %edi
	call	fputc@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	fputc@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -28(%rbp)
	movq	-128(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1642
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC448(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movss	-104(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-108(%rbp), %xmm1
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm1, %xmm2
	movq	%xmm2, %rdx
	movl	-112(%rbp), %eax
	movapd	%xmm0, %xmm1
	movq	%rdx, %xmm0
	movl	%eax, %esi
	leaq	.LC449(%rip), %rax
	movq	%rax, %rdi
	movl	$2, %eax
	call	printf@PLT
.L1642:
	movss	-108(%rbp), %xmm1
	movss	.LC445(%rip), %xmm0
	mulss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-128(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movss	-104(%rbp), %xmm0
	movss	.LC21(%rip), %xmm1
	xorps	%xmm0, %xmm1
	movss	.LC445(%rip), %xmm0
	mulss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movq	-128(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movl	$0, -4(%rbp)
	movss	-108(%rbp), %xmm0
	movss	%xmm0, -32(%rbp)
	movss	-104(%rbp), %xmm0
	movss	%xmm0, -36(%rbp)
	movl	-100(%rbp), %eax
	movl	%eax, -40(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1643
	pxor	%xmm0, %xmm0
	cvtss2sd	-36(%rbp), %xmm0
	pxor	%xmm3, %xmm3
	cvtss2sd	-32(%rbp), %xmm3
	movq	%xmm3, %rax
	movl	-40(%rbp), %edx
	movl	%edx, %esi
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC450(%rip), %rax
	movq	%rax, %rdi
	movl	$2, %eax
	call	printf@PLT
.L1643:
	movq	-128(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	leaq	.LC451(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movzbl	-81(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-82(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-83(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC452(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-128(%rbp), %rax
	movl	$4, %edx
	movzbl	-83(%rbp), %ecx
	movzbl	-82(%rbp), %esi
	salq	$8, %rsi
	orq	%rcx, %rsi
	movzbl	-81(%rbp), %ecx
	salq	$16, %rcx
	orq	%rsi, %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_write@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rcx
	movl	$3, %edx
	movl	$1, %esi
	leaq	.LC453(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$40, %edi
	call	fputc@PLT
	movq	-128(%rbp), %rax
	leaq	.LC444(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	vp3WriteString
	movzbl	-83(%rbp), %eax
	movzbl	%al, %esi
	movzbl	-82(%rbp), %eax
	movzbl	%al, %ecx
	movzbl	-81(%rbp), %eax
	movzbl	%al, %edx
	leaq	-91(%rbp), %rax
	movl	%esi, %r8d
	leaq	.LC454(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-91(%rbp), %rdx
	movq	-128(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	vp3WriteString
	movq	-128(%rbp), %rax
	leaq	.LC444(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	vp3WriteString
	movq	-128(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movq	-128(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32be@PLT
	movq	-128(%rbp), %rax
	movl	$1, %edx
	leaq	.LC206(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	vp3WriteStringLen
	movq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -44(%rbp)
	movq	-128(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$10, %edi
	call	fputc@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$246, %edi
	call	fputc@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	fputc@PLT
	movl	-44(%rbp), %ecx
	movq	-128(%rbp), %rax
	movl	$-4, %edx
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	vp3PatchByteCount
	movl	-28(%rbp), %ecx
	movq	-128(%rbp), %rax
	movl	$-3, %edx
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	vp3PatchByteCount
	addl	$1, -8(%rbp)
.L1640:
	movq	-120(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L1644
	movl	-20(%rbp), %ecx
	movq	-128(%rbp), %rax
	movl	$-4, %edx
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	vp3PatchByteCount
	movl	-12(%rbp), %ecx
	movq	-128(%rbp), %rax
	movl	$-4, %edx
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	vp3PatchByteCount
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_flipVertical@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE201:
	.size	writeVp3, .-writeVp3
	.globl	xxxDecodeByte
	.type	xxxDecodeByte, @function
xxxDecodeByte:
.LFB202:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	testb	%al, %al
	jns	.L1647
	movzbl	-4(%rbp), %eax
	jmp	.L1648
.L1647:
	movzbl	-4(%rbp), %eax
.L1648:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE202:
	.size	xxxDecodeByte, .-xxxDecodeByte
	.section	.rodata
.LC455:
	.string	"readXxx has been overridden."
	.text
	.globl	readXxx
	.type	readXxx, @function
readXxx:
.LFB203:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$456, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -456(%rbp)
	movq	%rsi, -464(%rbp)
	movl	$0, -20(%rbp)
	movl	$0, -24(%rbp)
	movb	$0, -29(%rbp)
	movl	emb_verbose(%rip), %eax
	cmpl	$1, %eax
	jle	.L1650
	leaq	.LC455(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L1651
.L1650:
	movq	-464(%rbp), %rax
	movl	$0, %edx
	movl	$39, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -40(%rbp)
	movq	-464(%rbp), %rax
	movl	$0, %edx
	movl	$252, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32@PLT
	movl	%eax, -44(%rbp)
	movl	-44(%rbp), %eax
	addl	$6, %eax
	movslq	%eax, %rcx
	movq	-464(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	$0, -28(%rbp)
	jmp	.L1652
.L1653:
	leaq	-448(%rbp), %rax
	addq	$203, %rax
	movl	$1280070990, (%rax)
	movb	$0, 4(%rax)
	leaq	-448(%rbp), %rax
	addq	$3, %rax
	movl	$1280070990, (%rax)
	movb	$0, 4(%rax)
	movq	-464(%rbp), %rax
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	leaq	-448(%rbp), %rcx
	movq	-464(%rbp), %rax
	movl	$3, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_read@PLT
	movq	-456(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-448(%rbp), %rax
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
	addl	$1, -28(%rbp)
.L1652:
	movl	-28(%rbp), %eax
	cmpl	-40(%rbp), %eax
	jl	.L1653
	movq	-464(%rbp), %rax
	movl	$0, %edx
	movl	$256, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	$0, -28(%rbp)
	jmp	.L1654
.L1665:
	movl	$0, -36(%rbp)
	cmpb	$0, -29(%rbp)
	je	.L1655
	movl	$2, -36(%rbp)
.L1655:
	movb	$0, -29(%rbp)
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -30(%rbp)
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -31(%rbp)
	cmpb	$126, -30(%rbp)
	je	.L1656
	cmpb	$125, -30(%rbp)
	jne	.L1657
.L1656:
	movzbl	-31(%rbp), %ebx
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movsbl	%al, %eax
	sall	$8, %eax
	addl	%ebx, %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	cwtl
	movl	%eax, -20(%rbp)
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16@PLT
	cwtl
	movl	%eax, -24(%rbp)
	movl	$2, -36(%rbp)
	jmp	.L1658
.L1657:
	cmpb	$127, -30(%rbp)
	jne	.L1659
	cmpb	$23, -31(%rbp)
	je	.L1660
	cmpb	$70, -31(%rbp)
	je	.L1660
	cmpb	$7, -31(%rbp)
	jbe	.L1660
	movb	$0, -30(%rbp)
	movb	$0, -31(%rbp)
	movb	$1, -29(%rbp)
	movl	$4, -36(%rbp)
	jmp	.L1661
.L1660:
	cmpb	$1, -31(%rbp)
	jne	.L1666
	movl	$2, -36(%rbp)
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -30(%rbp)
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -31(%rbp)
.L1661:
	movzbl	-30(%rbp), %eax
	movl	%eax, %edi
	call	xxxDecodeByte
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	movzbl	-31(%rbp), %eax
	movl	%eax, %edi
	call	xxxDecodeByte
	movsbl	%al, %eax
	movl	%eax, -24(%rbp)
	jmp	.L1658
.L1659:
	movzbl	-30(%rbp), %eax
	movl	%eax, %edi
	call	xxxDecodeByte
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	movzbl	-31(%rbp), %eax
	movl	%eax, %edi
	call	xxxDecodeByte
	movsbl	%al, %eax
	movl	%eax, -24(%rbp)
.L1658:
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-24(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-20(%rbp), %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-36(%rbp), %esi
	movq	-456(%rbp), %rax
	movl	$1, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
	jmp	.L1663
.L1666:
	nop
.L1663:
	addl	$1, -28(%rbp)
.L1654:
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	jne	.L1664
	movq	-464(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, %rdx
	movl	-44(%rbp), %eax
	cltq
	cmpq	%rax, %rdx
	jl	.L1665
.L1664:
	movl	$1, %eax
.L1651:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE203:
	.size	readXxx, .-readXxx
	.globl	xxxEncodeStop
	.type	xxxEncodeStop, @function
xxxEncodeStop:
.LFB204:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rdx, %rcx
	movq	%rsi, %rax
	movq	%rdi, %rdx
	movq	%rcx, %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$127, %edi
	call	fputc@PLT
	movl	-20(%rbp), %eax
	addl	$8, %eax
	movzbl	%al, %eax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE204:
	.size	xxxEncodeStop, .-xxxEncodeStop
	.globl	xxxEncodeStitch
	.type	xxxEncodeStitch, @function
xxxEncodeStitch:
.LFB205:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movss	%xmm0, -12(%rbp)
	movss	%xmm1, -16(%rbp)
	movl	%esi, -20(%rbp)
	movl	-20(%rbp), %eax
	andl	$3, %eax
	testl	%eax, %eax
	je	.L1669
	movss	-12(%rbp), %xmm0
	movss	.LC98(%rip), %xmm1
	andps	%xmm1, %xmm0
	comiss	.LC456(%rip), %xmm0
	ja	.L1670
	movss	-16(%rbp), %xmm0
	movss	.LC98(%rip), %xmm1
	andps	%xmm1, %xmm0
	comiss	.LC456(%rip), %xmm0
	jbe	.L1669
.L1670:
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$126, %edi
	call	fputc@PLT
	movss	-12(%rbp), %xmm0
	cvttss2sil	%xmm0, %eax
	movswl	%ax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movss	-16(%rbp), %xmm0
	cvttss2sil	%xmm0, %eax
	movswl	%ax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	jmp	.L1672
.L1669:
	movl	-12(%rbp), %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movzbl	%al, %eax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc@PLT
	movl	-16(%rbp), %eax
	movd	%eax, %xmm0
	call	emb_round@PLT
	movzbl	%al, %eax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc@PLT
	nop
.L1672:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE205:
	.size	xxxEncodeStitch, .-xxxEncodeStitch
	.globl	xxxEncodeDesign
	.type	xxxEncodeDesign, @function
xxxEncodeDesign:
.LFB206:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	movq	-64(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	jle	.L1674
	movq	-64(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movss	4(%rax), %xmm0
	movss	%xmm0, -8(%rbp)
	movq	-64(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movss	8(%rax), %xmm0
	movss	%xmm0, -12(%rbp)
.L1674:
	movl	$0, -4(%rbp)
	jmp	.L1675
.L1678:
	movq	-64(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movss	-8(%rbp), %xmm0
	movss	%xmm0, -16(%rbp)
	movss	-12(%rbp), %xmm0
	movss	%xmm0, -20(%rbp)
	movss	-44(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-40(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	movss	-8(%rbp), %xmm0
	subss	-16(%rbp), %xmm0
	movss	%xmm0, -24(%rbp)
	movss	-12(%rbp), %xmm0
	subss	-20(%rbp), %xmm0
	movss	%xmm0, -28(%rbp)
	movl	-48(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L1676
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	xxxEncodeStop
	jmp	.L1677
.L1676:
	movl	-48(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	jne	.L1677
	movl	-48(%rbp), %ecx
	movss	-28(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movss	-24(%rbp), %xmm1
	movss	.LC18(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movd	%xmm1, %edx
	movq	-56(%rbp), %rax
	movl	%ecx, %esi
	movaps	%xmm2, %xmm1
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	xxxEncodeStitch
.L1677:
	addl	$1, -4(%rbp)
.L1675:
	movq	-64(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1678
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE206:
	.size	xxxEncodeDesign, .-xxxEncodeDesign
	.section	.rodata
.LC459:
	.string	"\177\177\003\024"
	.string	""
	.string	""
.LC460:
	.string	""
	.string	"\001"
	.text
	.globl	writeXxx
	.type	writeXxx, @function
writeXxx:
.LFB207:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	-72(%rbp), %rax
	movss	.LC457(%rip), %xmm1
	movl	.LC456(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_correctForMaxStitchLength@PLT
	movq	-80(%rbp), %rax
	movl	$23, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-80(%rbp), %rax
	movl	$12, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-72(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movswl	%ax, %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-80(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	leaq	-48(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_bounds@PLT
	movss	-40(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-36(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	pxor	%xmm1, %xmm1
	cvtss2sd	-8(%rbp), %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %eax
	movswl	%ax, %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	pxor	%xmm1, %xmm1
	cvtss2sd	-12(%rbp), %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %eax
	movswl	%ax, %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	pxor	%xmm0, %xmm0
	cvtss2sd	-8(%rbp), %xmm0
	movsd	.LC458(%rip), %xmm2
	movapd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %eax
	movswl	%ax, %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	pxor	%xmm0, %xmm0
	cvtss2sd	-12(%rbp), %xmm0
	movsd	.LC458(%rip), %xmm2
	movapd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %eax
	movswl	%ax, %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	pxor	%xmm0, %xmm0
	cvtss2sd	-8(%rbp), %xmm0
	movsd	.LC458(%rip), %xmm2
	movapd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %eax
	movswl	%ax, %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	pxor	%xmm0, %xmm0
	cvtss2sd	-12(%rbp), %xmm0
	movsd	.LC458(%rip), %xmm2
	movapd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	movsd	.LC30(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %eax
	movswl	%ax, %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_i16@PLT
	movq	-80(%rbp), %rax
	movl	$197, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-80(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_write_i32@PLT
	movq	-72(%rbp), %rdx
	movq	-80(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	xxxEncodeDesign
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -16(%rbp)
	movq	-80(%rbp), %rax
	movl	$0, %edx
	movl	$252, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	-16(%rbp), %edx
	movq	-80(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_write_u32@PLT
	movq	-80(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-80(%rbp), %rax
	movq	%rax, %rcx
	movl	$6, %edx
	movl	$1, %esi
	leaq	.LC459(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$0, -4(%rbp)
	jmp	.L1680
.L1681:
	movq	-72(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -51(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -49(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	fputc@PLT
	movq	-80(%rbp), %rax
	movl	$3, %edx
	movzbl	-51(%rbp), %ecx
	movzbl	-50(%rbp), %esi
	salq	$8, %rsi
	orq	%rcx, %rsi
	movzbl	-49(%rbp), %ecx
	salq	$16, %rcx
	orq	%rsi, %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_write@PLT
	addl	$1, -4(%rbp)
.L1680:
	movq	-72(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1681
	movl	$0, -4(%rbp)
	jmp	.L1682
.L1683:
	movq	-80(%rbp), %rax
	movl	$16777216, %esi
	movq	%rax, %rdi
	call	emb_write_u32@PLT
	addl	$1, -4(%rbp)
.L1682:
	movq	-72(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movl	$22, %edx
	subl	%eax, %edx
	cmpl	%edx, -4(%rbp)
	jl	.L1683
	movq	-80(%rbp), %rax
	movq	%rax, %rcx
	movl	$2, %edx
	movl	$1, %esi
	leaq	.LC460(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE207:
	.size	writeXxx, .-writeXxx
	.globl	readZsk
	.type	readZsk, @function
readZsk:
.LFB208:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$432, %rsp
	movq	%rdi, -424(%rbp)
	movq	%rsi, -432(%rbp)
	movq	-432(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-432(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	cmpq	$559, %rax
	jg	.L1686
	movl	$0, %eax
	jmp	.L1701
.L1686:
	movq	-432(%rbp), %rax
	movl	$0, %edx
	movl	$560, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-432(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -1(%rbp)
	jmp	.L1688
.L1689:
	leaq	-416(%rbp), %rcx
	movq	-432(%rbp), %rax
	movl	$3, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	embColor_read@PLT
	movb	$0, -213(%rbp)
	movb	$0, -413(%rbp)
	movq	-424(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-416(%rbp), %rax
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
	movq	-432(%rbp), %rax
	movl	$1, %edx
	movl	$72, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-432(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -1(%rbp)
.L1688:
	cmpb	$0, -1(%rbp)
	jne	.L1689
	movq	-432(%rbp), %rax
	movl	$1, %edx
	movl	$46, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L1690
.L1700:
	movl	$0, -8(%rbp)
	movzbl	-11(%rbp), %eax
	movsbl	%al, %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L1691
	movzbl	-9(%rbp), %eax
	negl	%eax
	movb	%al, -9(%rbp)
.L1691:
	movzbl	-11(%rbp), %eax
	movsbl	%al, %eax
	andl	$8, %eax
	testl	%eax, %eax
	je	.L1692
	movzbl	-10(%rbp), %eax
	negl	%eax
	movb	%al, -10(%rbp)
.L1692:
	movzbl	-11(%rbp), %eax
	movsbl	%al, %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L1693
	movl	$1, -8(%rbp)
.L1693:
	movzbl	-11(%rbp), %eax
	movsbl	%al, %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L1694
	movzbl	-10(%rbp), %eax
	cmpb	$2, %al
	jne	.L1695
	movl	$2, -8(%rbp)
	jmp	.L1696
.L1695:
	movzbl	-10(%rbp), %eax
	cmpb	$-1, %al
	je	.L1702
	movzbl	-9(%rbp), %eax
	testb	%al, %al
	je	.L1699
	movzbl	-9(%rbp), %eax
	movb	%al, -1(%rbp)
.L1699:
	movl	$4, -8(%rbp)
	movzbl	-1(%rbp), %eax
	leal	-1(%rax), %edx
	movq	-424(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	emb_pattern_changeColor@PLT
.L1696:
	movb	$0, -10(%rbp)
	movb	$0, -9(%rbp)
.L1694:
	movzbl	-9(%rbp), %eax
	movsbl	%al, %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtsd2ss	%xmm0, %xmm2
	movzbl	-10(%rbp), %eax
	movsbl	%al, %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm3, %xmm3
	cvtsd2ss	%xmm0, %xmm3
	movd	%xmm3, %ecx
	movl	-8(%rbp), %esi
	movq	-424(%rbp), %rax
	movl	$0, %edx
	movaps	%xmm2, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel@PLT
.L1690:
	movq	-432(%rbp), %rdx
	leaq	-11(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$3, %rax
	je	.L1700
	jmp	.L1698
.L1702:
	nop
.L1698:
	movl	$1, %eax
.L1701:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE208:
	.size	readZsk, .-readZsk
	.globl	writeZsk
	.type	writeZsk, @function
writeZsk:
.LFB209:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$464, %rsp
	movq	%rdi, -456(%rbp)
	movq	%rsi, -464(%rbp)
	movq	-464(%rbp), %rax
	movl	$560, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movq	-456(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movq	-464(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc@PLT
	movq	-456(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, -4(%rbp)
	jmp	.L1704
.L1705:
	movq	-456(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	imulq	$403, %rdx, %rdx
	subq	$403, %rdx
	addq	%rax, %rdx
	leaq	-448(%rbp), %rax
	movl	$50, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	rep movsq
	movq	%rsi, %rdx
	movq	%rdi, %rax
	movzwl	(%rdx), %ecx
	movw	%cx, (%rax)
	leaq	2(%rax), %rax
	leaq	2(%rdx), %rdx
	movzbl	(%rdx), %ecx
	movb	%cl, (%rax)
	movq	-464(%rbp), %rax
	movl	$3, %edx
	movq	-448(%rbp), %rsi
	movq	%rax, %rdi
	call	embColor_write@PLT
	movq	-464(%rbp), %rax
	movl	$72, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movl	-4(%rbp), %eax
	leal	-1(%rax), %edx
	movq	-464(%rbp), %rax
	movq	%rax, %rsi
	movl	%edx, %edi
	call	fputc@PLT
	subl	$1, -4(%rbp)
.L1704:
	cmpl	$0, -4(%rbp)
	jg	.L1705
	movq	-464(%rbp), %rax
	movl	$46, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fpad@PLT
	movl	$0, -4(%rbp)
	jmp	.L1706
.L1716:
	movq	-456(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movb	$0, -35(%rbp)
	movss	-28(%rbp), %xmm0
	cvttss2sil	%xmm0, %eax
	movb	%al, -34(%rbp)
	movss	-24(%rbp), %xmm0
	cvttss2sil	%xmm0, %eax
	movb	%al, -33(%rbp)
	movl	-32(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L1707
	movzbl	-35(%rbp), %eax
	orl	$2, %eax
	movb	%al, -35(%rbp)
.L1707:
	movss	-28(%rbp), %xmm1
	pxor	%xmm0, %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L1708
	movzbl	-35(%rbp), %eax
	orl	$8, %eax
	movb	%al, -35(%rbp)
	movss	-28(%rbp), %xmm0
	movss	.LC21(%rip), %xmm1
	xorps	%xmm1, %xmm0
	cvttss2sil	%xmm0, %eax
	movb	%al, -34(%rbp)
.L1708:
	movss	-24(%rbp), %xmm1
	pxor	%xmm0, %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L1710
	movzbl	-35(%rbp), %eax
	orl	$4, %eax
	movb	%al, -35(%rbp)
	movss	-24(%rbp), %xmm0
	movss	.LC21(%rip), %xmm1
	xorps	%xmm1, %xmm0
	cvttss2sil	%xmm0, %eax
	movb	%al, -33(%rbp)
.L1710:
	movl	-32(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L1712
	movzbl	-35(%rbp), %eax
	orl	$32, %eax
	movb	%al, -35(%rbp)
	movb	$0, -34(%rbp)
	movb	$0, -33(%rbp)
.L1712:
	movl	-32(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L1713
	movzbl	-35(%rbp), %eax
	orl	$32, %eax
	movb	%al, -35(%rbp)
	movb	$0, -34(%rbp)
	movl	-20(%rbp), %eax
	movb	%al, -33(%rbp)
.L1713:
	movl	-32(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L1714
	movzbl	-35(%rbp), %eax
	orl	$32, %eax
	movb	%al, -35(%rbp)
	movb	$-128, -34(%rbp)
	movb	$0, -33(%rbp)
	movq	-464(%rbp), %rdx
	leaq	-35(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L1715
.L1714:
	movq	-464(%rbp), %rdx
	leaq	-35(%rbp), %rax
	movq	%rdx, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	addl	$1, -4(%rbp)
.L1706:
	movq	-456(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1716
.L1715:
	movl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE209:
	.size	writeZsk, .-writeZsk
	.section	.rodata
	.align 4
.LC17:
	.long	0
	.align 4
.LC18:
	.long	1092616192
	.align 8
.LC19:
	.long	-1717986918
	.long	-1078355559
	.align 8
.LC20:
	.long	-1717986918
	.long	1069128089
	.align 16
.LC21:
	.long	-2147483648
	.long	0
	.long	0
	.long	0
	.align 8
.LC30:
	.long	0
	.long	1076101120
	.align 4
.LC88:
	.long	1132396544
	.align 4
.LC93:
	.long	1094818202
	.align 16
.LC98:
	.long	2147483647
	.long	0
	.long	0
	.long	0
	.align 4
.LC101:
	.long	1036831949
	.align 4
.LC208:
	.long	1123811328
	.align 4
.LC209:
	.long	1121714176
	.align 4
.LC210:
	.long	1112014848
	.align 4
.LC211:
	.long	1124859904
	.align 4
.LC212:
	.long	1128792064
	.align 4
.LC213:
	.long	1130758144
	.align 4
.LC224:
	.long	1095447347
	.align 4
.LC228:
	.long	1106771968
	.align 4
.LC263:
	.long	1117782016
	.align 4
.LC264:
	.long	1122369536
	.align 4
.LC265:
	.long	1123024896
	.align 8
.LC280:
	.long	0
	.long	1077936128
	.align 8
.LC281:
	.long	0
	.long	1078263808
	.align 4
.LC282:
	.long	1129100083
	.align 4
.LC314:
	.long	1073741824
	.align 4
.LC323:
	.long	1109393408
	.align 8
.LC380:
	.long	-1717986918
	.long	1070176665
	.align 4
.LC399:
	.long	1142947840
	.align 8
.LC430:
	.long	0
	.long	1083129856
	.align 4
.LC440:
	.long	1162346496
	.align 4
.LC445:
	.long	1148846080
	.align 4
.LC456:
	.long	1123549184
	.align 4
.LC457:
	.long	1123942400
	.align 8
.LC458:
	.long	0
	.long	1073741824
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
