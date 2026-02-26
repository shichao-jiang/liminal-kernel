#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static bool print(const char *str, size_t len) {
    const uint8_t* bytes = (const uint8_t*) str;
    for (size_t i = 0; i < len; i++) {
        if (putchar(bytes[i]) == EOF) {
            return false;
        }
    }
    return true;
}

int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int written = 0;

    while (*format != '\0') {
        size_t maxrem = INT32_MAX - written;

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%') {
                format++;
            }
            size_t len = 1;
            while (format[len] && format[len] != '%') {
                len++;
            }
            if (len > maxrem) {
                return -1; // TODO: Set errno to EOVERFLOW.
            }
            if (!print(format, len)) {
                return -1;
            }
            format += len;
            written += len;
            continue;
        }

        const char* format_begin = format++;

        if (*format == 'c') {
            format++;
            char c = (char) va_arg(args, int);

            if (!maxrem) {
                return -1; // TODO: Set errno to EOVERFLOW.
            }
            if (!print(&c, sizeof(c))) {
                return -1;
            }

            written++;
        } else if (*format == 's') {
            format++;
            const char* str = va_arg(args, const char*);
            size_t len = strlen(str);

            if (len > maxrem) {
                return -1; // TODO: Set errno to EOVERFLOW.
            }
            if (!print(str, len)) {
                return -1;
            }

            written += len;
        } else if (*format == 'd') {
            format++;
            int num = va_arg(args, int);
            char buffer[11];

            size_t i = sizeof(buffer) - 1;
            if (num == 0) {
                buffer[i--] = '0';
            } else {
                unsigned int unum = (num < 0) ? -(unsigned int) num : (unsigned int) num;
                while (unum) {
                    int digit = unum % 10;
                    buffer[i--] = '0' + digit;
                    unum /= 10;
                }
                if (num < 0) {
                    buffer[i--] = '-';
                }
            }

            size_t len = sizeof(buffer) - i;
            if (len > maxrem) {
                return -1; // TODO: Set errno to EOVERFLOW.
            }
            if (!print(buffer + i + 1, len)) {
                return -1;
            }

            written += len;
        } else {
            format = format_begin;
            size_t len = strlen(format);

            if (len > maxrem) {
                return -1; // TODO: Set errno to EOVERFLOW.
            }
            if (!print(format, len)) {
                return -1;
            }

            written += len;
            format += len;
        }
    }

    va_end(args);
    return written;
}