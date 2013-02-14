GCC_ARGS = -Wall -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -m32 -c -I$(INCLUDE)
INCLUDE = include
OBJ_OUT = obj

OBJS = $(wildcard $(OBJ_OUT)/*.o)
C_SRC = src
C_FILES = $(wildcard $(C_SRC)/*.c)
C_O_FILES = $(addprefix $(OBJ_OUT)/,$(notdir $(C_FILES:.c=.o)))

LD_ARGS = -m elf_i386 -T linker.ld

NASM_ARGS = -f elf
ASM_SRC = asm

all: loader $(C_O_FILES) link mkdisk

link:
	ld $(LD_ARGS) -o kernel.bin $(OBJS)
	
obj/%.o: src/%.c
	gcc $(GCC_ARGS) -o $@ $^

loader:
	nasm $(NASM_ARGS) -o $(OBJ_OUT)/loader.o $(ASM_SRC)/loader.s

mkdisk: 
	dd if=/dev/zero of=pad bs=1 count=750
	rm -f floppy.img
	cat grub/stage1 grub/stage2 pad kernel.bin > floppy.img
	
clean:
	rm -f *.o *~
	rm -f pad kernel.bin floppy.img
