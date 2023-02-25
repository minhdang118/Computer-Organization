	.file	"g.c"
	.text
	.globl	RM
	.data
	.align 4
	.type	RM, @object
	.size	RM, 4
RM:
	.long	31
	.globl	RMU
	.align 4
	.type	RMU, @object
	.size	RMU, 4
RMU:
	.long	29
	.globl	RMI
	.align 4
	.type	RMI, @object
	.size	RMI, 4
RMI:
	.long	13
	.text
	.globl	g
	.type	g, @function
g:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %edx
	movl	RMU(%rip), %eax
	imull	%eax, %edx
	movl	RMI(%rip), %eax
	addl	%edx, %eax
	movl	RM(%rip), %ecx
	movl	$0, %edx
	divl	%ecx
	movl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	g, .-g
	.globl	r
	.type	r, @function
r:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -4(%rbp)
	movl	-28(%rbp), %eax
	imull	%eax, %eax
	movl	%eax, %edi
	call	g
	movl	%eax, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L4
.L5:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %edi
	call	g
	movl	%eax, -8(%rbp)
	addl	$1, -4(%rbp)
.L4:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L5
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	r, .-r
	.ident	"GCC: (GNU) 12.2.1 20220819 (Red Hat 12.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
