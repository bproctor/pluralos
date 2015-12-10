
	.text
	.align 4
	.globl strlen
strlen:
	pushl	%edi
	movl	8(%esp), %edi
	xorl	%eax, %eax
	movl	$-1, %ecx
	cld
	repnz;	scasb
	movl	$-2, %eax
	subl	%ecx, %eax
	popl	%edi
	ret
