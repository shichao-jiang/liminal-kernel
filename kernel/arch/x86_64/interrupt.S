.intel_syntax noprefix

.global load_idt
.global isr_wrapper

load_idt:
    lidt [rdi]
    ret

isr_wrapper:
    // save rax rbx rcx rdx rbp rdi rsi r8 r9 r10 r11 r12 r13 r14 r15
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    cld
    call interrupt_handler
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
    iretq
