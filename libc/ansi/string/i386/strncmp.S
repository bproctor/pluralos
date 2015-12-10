
	.text
	.align 	4
	.globl	strncmp
strncmp:
	pushl	%edi
	pushl	%esi
	movl	12(%esp), %esi
	movl	16(%esp), %edi
	movl	20(%esp), %ecx
1:	decl 	%ecx
	js 	2f
	lodsb
	scasb
	jne 	3f
	testb 	%al,%al
	jne 	1b
2:	xorl 	%eax,%eax
	jmp 	4f
3:	sbbl 	%eax,%eax
	orb 	$1,%al
4:	popl	%esi
	popl	%edi
	ret
