section .text

global asm_crc32_hash_func

asm_crc32_hash_func:
    push rbp
    mov rbp, rsp

    xor rax, rax
    mov eax, 0xffffffff

    jmp .if_loop
.loop:
    crc32 eax, byte [rdi]
    inc rdi

.if_loop:
    cmp byte [rdi], 0
    ja .loop

    mov rsp, rbp
	pop rbp

    ret
