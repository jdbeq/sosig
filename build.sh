aarch64-none-elf-gcc -c kernel/arch/aarch64/loader.s -o kernel/arch/aarch64/loader.o
aarch64-none-elf-gcc -ffreestanding -nostdlib -lk -lgcc -c kernel/kernel/kernel.c -o kernel/kernel/kernel.o -O2 -Wall -Wextra
aarch64-none-elf-gcc -T kernel/arch/aarch64/linker.ld -o myos.elf -ffreestanding -O2 -nostdlib kernel/arch/aarch64/loader.o kernel/kernel/kernel.o -lgcc
