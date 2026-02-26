CC = $(HOME)/opt/cross/bin/x86_64-elf-gcc
AR = $(HOME)/opt/cross/bin/x86_64-elf-ar

CFLAGS := -g -O0

override CFLAGS += \
	-fdebug-prefix-map=$(CURDIR)=libc \
	-Wall \
	-Wextra \
	-std=c11 \
	-ffreestanding \
	-fno-stack-protector \
    -fno-pic \
	-mno-red-zone

override CPPFLAGS := \
	-Iinclude \
	-I../kernel/include \
	-D__is_libk \
	$(CPPFLAGS) \
	-MMD

override SRCS := $(shell find . -name '*.c')
override OBJS := $(addprefix obj/,$(SRCS:.c=.libk.o))

libk.a: $(OBJS)
	$(AR) rcs $@ $^

obj/%.libk.o: %.c
	mkdir -p "$(dir $@)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf obj libk.a