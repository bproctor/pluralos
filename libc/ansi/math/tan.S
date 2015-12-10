
        .text
        .align  16
        .globl  tan
tan:
        movl    8(%esp),%eax
        andl    $0x7FF00000,%eax
        cmpl    $0x43E00000,%eax
        jae     1f
        fldl    4(%esp)
        fptan
        fstp    %st(0)
        ret
1:      cmpl    $0x7FF00000, %eax
        je      1f
        fldz
        ret     
1:      movl    $1,errno
        flds    __nan
        ret
