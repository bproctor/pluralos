
	.text
	.align 	4
	.globl	strnlen
strnlen:
	movl	4(%esp), %ecx
	movl	8(%esp), %edx
	movl 	%ecx,%eax
	jmp 	2f
1:	cmpb 	$0,(%eax)
	je 	3f
	incl 	%eax
2:	decl 	%edx
	cmpl 	$-1,%edx
	jne 	1b
3:	subl 	%ecx,%eax
	ret
