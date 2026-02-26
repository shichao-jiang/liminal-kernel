CC = $(HOME)/opt/cross/bin/x86_64-elf-gcc
AR = $(HOME)/opt/cross/bin/x86_64-elf-ar

CFLAGS = -Wall \
	-Wextra \
	-std=c11 \
	-ffreestanding \
	-fno-stack-protector \
    -fno-pic \
	-mno-red-zone

CPPFLAGS = \
	-Iinclude \
	-I../kernel/include \
	-D__is_libk

SRCS = $(shell find . -name '*.c')
OBJS = $(SRCS:.c=.o)

libk.a: $(OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) libk.a