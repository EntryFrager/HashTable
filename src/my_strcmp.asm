section .text

global asm_my_strcmp

asm_my_strcmp:
        push rbp
        mov rbp, rsp

        vmovdqu ymm1, [rdi]
        vpcmpeqb ymm0, ymm1, [rsi]
        vpmovmskb rax, ymm0

        xor rax, 0xffffffff

        mov rsp, rbp
        pop rbp

        ret
