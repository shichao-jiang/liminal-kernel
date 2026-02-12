# Liminal Kernel: A 64-bit x86 Kernel

A hobbyist operating system built from scratch, targeting the x86_64 architecture using the [Limine Boot Protocol](https://github.com/limine-bootloader/limine).

## Description

This project is a functional, monolithic kernel designed to explore low-level systems programming, memory management, and hardware abstraction. Unlike many tutorial projects, this OS utilizes a custom cross-compiler toolchain and adheres to the Limine Boot Protocol for modern, 64-bit entry.

## Technical Specifications

- **Architecture:** x86_64 (Long Mode)
- **Kernel Type:** Monolithic / Higher-Half (Mapped at `-2GiB`)
- **Boot Protocol:** Limine
- **Build System:** GNU Make
- **Compiler:** `x86_64-elf-gcc` (Cross-Compiler)

## Current Features
- [x] **Cross-Compiler Integration:** Fully isolated build environment.
- [x] **Hybrid ISO:** Bootable via UEFI or Legacy BIOS.

## Roadmap
- [ ] **Serial TTY Driver:** COM1 UART driver for debugging over SSH/Serial.
- [ ] **Global Descriptor Table (GDT):** Establishing kernel/user segments.
- [ ] **Interrupt Descriptor Table (IDT):** Handling CPU exceptions and hardware IRQs.
- [ ] **Physical Memory Manager (PMM):** Bitmap-based allocation of page frames.
- [ ] **Virtual Memory Manager (VMM):** Recursive page table mapping.
- [ ] **User-mode:** Switching to Ring 3 and executing the first user process.

## Building and Running

### Prerequisites

- x86_64-elf cross-compiler
- GNU make
- xorriso
- QEMU

### 1. Setup

```bash
git clone https://github.com/shichao-jiang/liminal-kernel.git
cd liminal-kernel
git submodule update --init --recursive
```

### 2. Build

```bash
make
```
This will build the Limine bootloader tools and create a bootable ISO image (`liminal-kernel.iso`)

### 3. Running

To run the kernel in QEMU with BIOS firmware:

```bash
make run
```

To run the kernel in QEMU with UEFI firmware:

```bash
make run-uefi
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Resources

- [Limine Boot Protocol Specification](https://github.com/limine-bootloader/limine/blob/trunk/PROTOCOL.md)
- [OSDev Wiki](https://wiki.osdev.org/)
