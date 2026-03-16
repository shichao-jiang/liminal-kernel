#include <arch/x86_64/isr.h>
#include <stdio.h>

void interrupt_handler() {
    // For now, just print a message and halt the CPU.
    // In a real kernel, you would want to handle the interrupt properly.
    printf("Interrupt received!\n");
    for (;;) {
        asm("hlt");
    }
}
