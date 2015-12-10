
	.text
	.align 4
	.globl	strcmp
strcmp:
	pushl	%edi
	pushl	%esi
	movl	12(%esp), %esi
	movl	16(%esp), %edi
1:	lodsb
	scasb
	jne 	2f
	testb 	%al,%al
	jne 	1b
	xorl 	%eax,%eax
	jmp 	3f
2:	sbbl 	%eax,%eax
	orb 	$1,%al
3:	popl	%esi
	popl	%edi
	ret
