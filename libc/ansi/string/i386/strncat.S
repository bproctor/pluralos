
	.text
	.align 	4
	.globl 	strncat
strncat:
	pushl	%edi
	pushl	%esi
	pushl	%edi
	movl	20(%esp), %esi
	movl	24(%esp), %edx
	xorl	%eax, %eax
	movl	$-1, %ecx
	movl	16(%esp), %edi
	repne;	scasb
	decl 	%edi
	movl 	%edx,%ecx
1:	decl 	%ecx
	js 	2f
	lodsb
	stosb
	testb 	%al,%al
	jne 	1b
2:	xorl 	%eax,%eax
	stosb
	movl	16(%esp), %eax
	popl	%esi
	popl	%esi
	popl	%edi
	ret
