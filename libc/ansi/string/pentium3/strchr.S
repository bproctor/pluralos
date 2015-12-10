
	.text
	.p2align 4,,15
	.globl strchr
strchr:
	pushl	%ebx
	movl	8(%esp), %edx
	movl	12(%esp), %ebx
	movzbl	(%edx), %eax
	cmpb	%bl, %al
	je	2f
	.p2align 4,,15
1:	xorl	%ecx, %ecx
	testb	%al, %al
	je	3f
	incl	%edx
	movzbl	(%edx), %eax
	cmpb	%bl, %al
	jne	1b
2:	movl	%edx, %ecx
3:	popl	%ebx
	movl	%ecx, %eax
	ret
