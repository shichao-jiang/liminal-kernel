.intel_syntax noprefix

.global gdt_flush

gdt_flush:
    lgdt [rdi]

    // reload cs register
    push 0x08
    lea rax, [rip + .reload_cs]
    push rax
    retfq

.reload_cs:
    // reload data segment registers
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
