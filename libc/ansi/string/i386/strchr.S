
	.text
	.align 4
	.globl	strchr
strchr:
	pushl	%esi
	movl	8(%esp), %esi
	movl	12(%esp), %eax
	movb 	%al,%ah
1:	lodsb
	cmpb 	%ah,%al
	je 	2f
	testb 	%al,%al
	jne 	1b
	movl 	$1,%esi
2:	movl 	%esi,%eax
	decl 	%eax
	popl	%esi
	ret
