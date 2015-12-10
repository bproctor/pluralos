
        .text
        .p2align 4,,15
        .globl strlen
strlen:
        movl    4(%esp),%eax
        movl    $3,%edx
        andl    %eax,%edx
        jz      2f
        jp      1f
        cmpb    %dh,(%eax)
        jz      3f
        incl    %eax
        cmpb    %dh,(%eax)
        jz      3f
        incl    %eax
        xorl    $2,%edx
        jz      2f
1:      cmpb    %dh,(%eax)
        jz      3f
        incl    %eax
        xorl    %edx,%edx
2:      movl    (%eax),%ecx
        addl    $4,%eax
        subl    %ecx,%edx
        addl    $0xFEFEFEFF,%ecx
        decl    %edx
        jnc     4f
        xorl    %ecx,%edx
        andl    $~0xFEFEFEFF,%edx
        jnz     4f
        movl    (%eax),%ecx
        addl    $4,%eax
        subl    %ecx,%edx
        addl    $0xFEFEFEFF,%ecx
        decl    %edx
        jnc     4f
        xorl    %ecx,%edx
        andl    $~0xFEFEFEFF,%edx
        jnz     4f
        movl    (%eax),%ecx
        addl    $4,%eax
        subl    %ecx,%edx
        addl    $0xFEFEFEFF,%ecx
        decl    %edx
        jnc     4f
        xorl    %ecx,%edx
        andl    $~0xFEFEFEFF,%edx
        jnz     4f
        movl    (%eax),%ecx
        addl    $4,%eax
        subl    %ecx,%edx
        addl    $0xFEFEFEFF,%ecx
        decl    %edx
        jnc     4f
        xorl    %ecx,%edx
        andl    $~0xFEFEFEFF,%edx
        jz      2b
4:      subl    $4,%eax
        subl    $0xFEFEFEFF,%ecx
        cmpb    $0,%cl
        jz      3f
        incl    %eax
        testb   %ch,%ch
        jz      3f
        shrl    $16,%ecx
        incl    %eax
        cmpb    $0,%cl
        jz      3f
        incl    %eax
3:      subl    4(%esp),%eax
        ret

        