	.text
	.align	16
	.globl bzero
bzero:
	pushl	%ebx
	movl	12(%esp), %eax
	movl	8(%esp), %ebx
	pushl	%eax
	pushl	$0
	pushl	%ebx
	call	memset
	addl	$12, %esp
	movl	%ebx, %eax
	popl	%ebx
	ret
