
	.text
	.p2align 4,,15
	.globl strcat
strcat:
	pushl	%edi
	pushl	%esi
	pushl	%ecx
	movl	20(%esp), %esi
	xorl	%eax, %eax
	movl	$-1, %ecx
	movl	16(%esp), %edi
	repne;	scasb
	decl 	%edi
1:	lodsb
	stosb
	testb 	%al,%al
	jne 	1b
	movl	16(%esp), %eax
	popl	%edx
	popl	%esi
	popl	%edi
	ret
