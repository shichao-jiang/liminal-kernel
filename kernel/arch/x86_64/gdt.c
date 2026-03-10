#include <arch/x86_64/gdt.h>

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  flags;
    uint8_t  base_high;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

static struct gdt_entry gdt[3];
static struct gdt_ptr gdtp;

static void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    if (limit > 0xFFFFF) {
        limit = 0xFFFFF;
    }

    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].flags = ((limit >> 16) & 0x0F);

    gdt[num].flags |= ((flags & 0xF) << 4);
    gdt[num].access = access;
}

extern void gdt_flush(uint64_t gdtp_ptr);

void gdt_init() {
    gdtp.limit = sizeof(gdt) - 1;
    gdtp.base = (uint64_t)&gdt;

    gdt_set_gate(0, 0, 0, 0, 0);            // Null segment
    gdt_set_gate(1, 0, 0xFFFFF, 0x9A, 0xA); // Kernel code segment
    gdt_set_gate(2, 0, 0xFFFFF, 0x92, 0xC); // Kernel data segment

    gdt_flush((uint64_t)&gdtp);
}