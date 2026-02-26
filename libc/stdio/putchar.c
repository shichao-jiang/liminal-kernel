#include <stdio.h>

#if defined(__is_libk)
#include <kernel/serial.h>
#endif

int putchar(int ic) {
#if defined(__is_libk)
    char c = (char) ic;
    serial_write(&c, sizeof(c));
    return ic;
#else
    // TODO: Implement putchar for user-space applications.
#endif
    return ic;
}