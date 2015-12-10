
	.text
	.align	16
        .globl  ceil
ceil:
        subl    $4,%esp
        movl    12(%esp),%eax
        andl    $0x7FF00000,%eax
        cmpl    $0x7FF00000,%eax
        je      3f
1:      fnstcw  (%esp)
        fwait
        movw    (%esp),%ax
        andw    $0xf3ff,%ax
        orw     $0x0800,%ax
        movw    %ax,2(%esp)
        fldcw   2(%esp)
        fldl    8(%esp)
        frndint
        fldcw   (%esp)
2:      addl    $4,%esp
        ret
3:      movl    12(%esp),%eax
        testl   $0x000FFFFF,%eax
        jnz     4f
        movl    8(%esp),%eax
        testl   %eax,%eax
        jz      1b
4:      movl    $1,errno
        flds    __nan
        jmp	2b
