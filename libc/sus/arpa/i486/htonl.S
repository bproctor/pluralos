
        .text
        .p2align 4,,15
        .globl htonl, ntohl
htonl:
ntohl:
        movl    4(%esp),%eax
        bswap   %eax
        ret
        