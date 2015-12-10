
        .text
        .p2align 4,,15
        .globl htonl, ntohl
htonl:
ntohl:
        movl    4(%esp),%eax
        rorw    $8,%ax
        rorl    $16,%eax
        rorw    $8,%ax
        ret
        