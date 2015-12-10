
	.text
	.p2align 4,,15
	.globl	memmove
memmove:
	pushl	%edi
	pushl	%esi
	movl	12(%esp), %eax
	movl	16(%esp), %esi
	cmpl	%esi, %eax
	movl	20(%esp), %ecx
	jae	1f
	movl	%eax, %edi
	rep;	movsb
	jmp	2f
	.p2align 2
1:	leal	-1(%ecx,%esi), %esi
	leal	-1(%ecx,%eax), %edi
	std
	rep;	movsb
	cld
2:	popl	%esi
	popl	%edi
	ret
