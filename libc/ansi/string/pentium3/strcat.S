
	.text
	.p2align 4,,15
	.globl strcat
strcat:
	pushl	%ebx
	movl	12(%esp),%ecx
	movl	8(%esp),%ebx
	movzbl	(%ecx),%eax
	movl	%ebx,%edx
	testb	%al,%al
	je	2f
	.p2align 4,,15
1:	movb	%al,(%edx)
	incl	%ecx
	incl	%edx
	movzbl	(%ecx),%eax
	testb	%al,%al
	jne	1b
2:	movl	%ebx,%eax
	popl	%ebx
	ret
