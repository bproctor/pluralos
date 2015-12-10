
	.text
	.align	16
        .globl  ffs
ffs:
        bsfl    4(%esp),%eax
        jnz     1f
        movl    $-1,%eax
1:      incl    %eax
        ret
                        