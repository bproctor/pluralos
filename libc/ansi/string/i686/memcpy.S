
        .text
        .p2align 4,,15
        .globl  memcpy
memcpy:
        pushl   %esi
        pushl   %edi
        movl    4(%esp),%ecx
        movl    8(%esp),%esi
        movl    12(%esp),%edi
        cld
        shrl    $1,%ecx
        jnc     1f
        movsb
1:      shrl    $1,%ecx
        jnc     1f
        movsw
1:      rep;    movsl
        popl    %edi
        popl    %esi
        movl    12(%esp),%eax
        ret
        