#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdint.h>
#include <stddef.h>

int serial_init();

int serial_received();
int is_transmit_empty();

char serial_read();
void serial_putc(char a);
void serial_write(const char* str, size_t len);
void serial_writestring(const char* str);

#endif