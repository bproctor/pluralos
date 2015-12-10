
	.text
	.align 	4
	.globl 	strncpy
strncpy:
	pushl	%edi
	pushl	%esi
	pushl	%edi
	movl	20(%esp), %esi
	movl	24(%esp), %ecx
	movl	16(%esp), %edi
1:	decl 	%ecx
	js 	2f
	lodsb
	stosb
	testb 	%al,%al
	jne 	1b
	rep;	stosb
2:	movl	16(%esp), %eax
	popl	%esi
	popl	%esi
	popl	%edi
	ret
