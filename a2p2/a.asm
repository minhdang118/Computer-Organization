	.globl	NP
	.data
	.align 4
	.type	NP, @object
NP:
	.long	10
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
	.globl	ask
	.type	ask, @function
ask:
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
	call	scanf
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
	movl	-4(%rbp), %eax
	jmp	.L8
.L3:
	jmp	.L7
.L8:
	ret
