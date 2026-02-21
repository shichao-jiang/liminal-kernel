set auto-load safe-path /

target remote localhost:1234

file kernel/bin/liminal-kernel

set architecture i386:x86-64

break kmain

set disassembly-flavor intel

layout src
layout regs