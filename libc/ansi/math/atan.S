
	.text
	.align	16
        .globl  atan
atan:
        movl    8(%esp),%eax
        andl    $0x7FF00000,%eax
        cmpl    $0x7FF00000,%eax
        je      2f
1:  	fldl    4(%esp)
        fld1
        fpatan
        ret
2:  	movl    8(%esp),%eax
        testl   $0x000FFFFF,%eax
        jnz     3f
        movl    4(%esp),%eax
        testl   %eax,%eax
        jz      1b
3:      movl    $1,errno
        flds    __nan
        ret
