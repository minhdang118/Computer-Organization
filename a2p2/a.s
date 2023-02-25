	.file	"a.c"
	.text
	.globl	NP
	.data
	.align 4
	.type	NP, @object
	.size	NP, 4
NP:
	.long	10
	.section	.rodata
.LC0:
	.string	"Press CTRL+C to exit."
	.align 8
.LC1:
	.string	"Enter a positive integer for key size: "
.LC2:
	.string	"%d"
	.align 8
.LC3:
	.string	"Sorry, did not understand your input. Repeating question."
	.align 8
.LC4:
	.string	"Whoops! That's too small. Please enter a higher number!"
	.align 8
.LC5:
	.string	"Whoops! That's too big. Please enter a smaller number!"
.LC6:
	.string	"%d is just right!\n"
	.text
	.globl	ask
	.type	ask, @function
ask:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$.LC0, %edi
	call	puts
.L7:
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	leaq	-4(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	testl	%eax, %eax
	jne	.L2
	movl	$.LC3, %edi
	call	puts
	jmp	.L3
.L2:
	movl	-4(%rbp), %eax
	cmpl	$4, %eax
	jg	.L4
	movl	$.LC4, %edi
	call	puts
	jmp	.L3
.L4:
	movl	-4(%rbp), %edx
	movl	NP(%rip), %eax
	cmpl	%eax, %edx
	jle	.L5
	movl	$.LC5, %edi
	call	puts
	jmp	.L3
.L5:
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	jmp	.L9
.L3:
	jmp	.L7
.L9:
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	ask, .-ask
	.ident	"GCC: (GNU) 12.2.1 20220819 (Red Hat 12.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
