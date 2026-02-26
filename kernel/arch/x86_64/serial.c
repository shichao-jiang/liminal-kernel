#include <arch/x86_64/io.h>
#include <kernel/serial.h>
#include <string.h>

#define COM1 0x3F8

int serial_init() {
    outb(COM1 + 1, 0x00);    // Disable all interrupts
    outb(COM1 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(COM1 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(COM1 + 1, 0x00);    //                  (hi byte)
    outb(COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set

    return 0;
}

int serial_received() {
    return inb(COM1 + 5) & 1;
}

int is_transmit_empty() {
    return inb(COM1 + 5) & 0x20;
}

char serial_read() {
    while (serial_received() == 0);

    return inb(COM1);
}

void serial_putc(char a) {
    while (is_transmit_empty() == 0);

    outb(COM1, a);
}

void serial_write(const char* str, size_t len) {
    for (size_t i = 0; i < len; i++) {
        serial_putc(str[i]);
    }
}

void serial_writestring(const char* str) {
    serial_write(str, strlen(str));
}
