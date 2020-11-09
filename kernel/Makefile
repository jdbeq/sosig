SRCS = $(wildcard kernel_main/*.c) \
	$(wildcard uart/*.c)

OBJS = $(SRCS:.c=.o)
INCLUDE = include/
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -I$(INCLUDE)
all: clean sosig.img

loader/loader.o: loader/loader.s
	aarch64-none-elf-gcc $(CFLAGS) -c loader/loader.s -o loader/loader.o

%.o: %.c
	aarch64-none-elf-gcc $(CFLAGS) -c $< -o $@

sosig.img: loader/o $(OBJS)
	aarch64-none-elf-ld -nostdlib -nostartfiles loader/o $(OBJS) -T linker.ld -o sosig.elf
	aarch64-none-elf-objcopy -O binary sosig.elf sosig.img

clean:
	rm sosig.elf sosig.img >/dev/null 2>/dev/null || true

run:
	qemu-system-aarch64 -M raspi3 -kernel sosig.img -serial null -serial stdio -d in_asm