
	.text
	.align 4
	.globl strcpy
strcpy:
	pushl	%edi
	pushl	%esi
	pushl	%ecx
	movl	20(%esp), %esi
	movl	16(%esp), %edi
1:	lodsb
	stosb
	testb 	%al,%al
	jne 	1b
	movl	16(%esp), %eax
	popl	%edx
	popl	%esi
	popl	%edi
	ret
