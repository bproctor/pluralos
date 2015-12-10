
	.text
	.p2align 4,,15
	.globl	memset
memset:
	pushl	%edi
	pushl	%ecx
	movl	20(%esp), %ecx
	movb	16(%esp), %al
	movl	12(%esp), %edi
	rep;	stosb
	movl	12(%esp), %eax
	popl	%edx
	popl	%edi
	ret
