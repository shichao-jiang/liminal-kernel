#include <arch/x86_64/idt.h>
#include <arch/x86_64/isr.h>
#include <stdint.h>

struct idt_descriptor {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t offset_middle;
    uint32_t offset_high;
    uint32_t zero;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

enum gate_type {
    GATE_TYPE_INTERRUPT = 0xE,
    GATE_TYPE_TRAP = 0xF
};

static struct idt_descriptor idt[256];
static struct idt_ptr idtp;

static void idt_set_gate(uint8_t num, uint64_t offset, uint16_t selector, uint8_t ist, uint8_t dpl,
                         enum gate_type gate_type) {
    idt[num].offset_low = offset & 0xFFFF;
    idt[num].selector = selector;
    idt[num].ist = ist & 0x7;
    idt[num].type_attr = 0x80;
    idt[num].type_attr |= ((dpl & 0x3) << 5) | gate_type;
    idt[num].offset_middle = (offset >> 16) & 0xFFFF;
    idt[num].offset_high = (offset >> 32) & 0xFFFFFFFF;
    idt[num].zero = 0;
}

extern void load_idt(uint64_t idtp_ptr);
extern void isr_wrapper();

void idt_init() {
    idtp.limit = sizeof(idt) - 1;
    idtp.base = (uint64_t)&idt;

    idt_set_gate(0, (uint64_t)isr_wrapper, 0x8, 0, 0, GATE_TYPE_TRAP);

    load_idt((uint64_t)&idtp);
}