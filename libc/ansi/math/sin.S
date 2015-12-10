
	.text
	.align	16
        .globl  sin
sin:
        movl    8(%esp),%eax
        andl    $0x7FF00000,%eax
        cmpl    $0x43E00000,%eax
        jae     1f
        fldl    4(%esp)
        fsin
        ret
1:      cmpl    $0x7FF00000, eax
        jb      1f
        flds    __nan
        movl    $1,errno
        ret
1:      fldz
        ret     
