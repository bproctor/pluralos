
	.text
	.align	16
	.globl	bcopy
bcopy:
	movl	4(%esp), %eax
	movl	8(%esp), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, 8(%esp)
	jmp	memmove
