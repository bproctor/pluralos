
	.text
	.align 	4
	.globl	strrchr
strrchr:
	pushl	%esi
	pushl	%ecx
	movl	12(%esp), %esi
	xorl	%ecx, %ecx
	movl	16(%esp), %eax
	movb 	%al,%ah
1:	lodsb
	cmpb 	%ah,%al
	jne 	2f
	leal 	-1(%esi),%ecx
2:	testb 	%al,%al
	jne 	1b
	movl	%ecx, %eax
	popl	%edx
	popl	%esi
	ret
