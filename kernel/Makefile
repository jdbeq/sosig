SRCS = $(wildcard kernel_main/*.c) \
	$(wildcard uart/*.c)


OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles

all: clean sosig.img

loader/o: loader/loader.s
	aarch64-none-elf-gcc $(CFLAGS) -c loader/loader.s -o loader/o

%.o: %.c
	aarch64-none-elf-gcc $(CFLAGS) -c $< -o $@

sosig.img: loader/o $(OBJS)
	aarch64-none-elf-ld -nostdlib -nostartfiles loader/o $(OBJS) -T linker.ld -o sosig.elf
	aarch64-none-elf-objcopy -O binary sosig.elf sosig.img

clean:
	rm sosig.elf sosig.img *.o >/dev/null 2>/dev/null || true

run:
	qemu-system-aarch64 -M raspi3 -kernel sosig.img -serial null -serial stdio
