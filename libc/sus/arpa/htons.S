
        .text
        .p2align 4,,15
        .globl htons, ntohs
htons:
ntohs:
        movl    4(%esp),%eax
        andl    $0xFFFF,%eax
        rorw    $8,%ax
        ret
        