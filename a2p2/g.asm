	.globl	RM
	.align 4
	.type	RM, @object
RM:
	.long	31
	.globl	RMU
	.align 4
	.type	RMU, @object
RMU:
	.long	29
	.globl	RMI
	.align 4
	.type	RMI, @object
RMI:
	.long	13
	.globl	g
	.type	g, @function
g:
	movl	%edi, -4(%rbp)
	movl	$29, %eax
	imull	-4(%rbp), %eax
	movl	%eax, %edx
	movl	$13, %eax
	addl	%edx, %eax
	movl	$31, %ecx
	movl	$0, %edx
	divl	%ecx
	movl	%edx, %eax
	ret
	.globl	r
	.type	r, @function
r:
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -4(%rbp)
	movl	-28(%rbp), %eax
	imull	-28(%rbp), %eax
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
	addq	%rax, %rdx
	movl	-8(%rbp), %eax
	movl	%eax, (%rdx)
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
	ret
