
	.text
	.p2align 4,,15
	.globl strcmp
strcmp:
	movl	4(%esp),%ecx
	movl	8(%esp),%edx
	movzbl	(%ecx),%eax
	cmpb	(%edx),%al
	je	2f
1:	xorl	%eax,%eax
	ret
	.p2align 4,,7
2:	testb	%al,%al
	je	1b
	incl	%ecx
	incl	%edx
	movzbl	(%ecx),%eax
	cmpb	(%edx),%al
	je	2b
	xorl	%eax,%eax
	ret
