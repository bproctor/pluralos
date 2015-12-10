
	.text
	.p2align 4,,15
	.globl	memchr
memchr:
	pushl	%edi
	movl	16(%esp), %ecx
	testl	%ecx, %ecx
	movl	8(%esp), %edi
	movl	12(%esp), %eax
	jne	1f
	xorl	%eax, %eax
	jmp	3f
	.p2align 2
1:	repne;	scasb
	je 	2f
	movl 	$1,%edi
2:	decl 	%edi
	movl	%edi, %eax
3:	popl	%edi
	ret
