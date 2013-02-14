GCC_ARGS = -Wall -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -m32 -c -I$(INCLUDE)
INCLUDE = include
OBJ_OUT = obj
ASM_OBJ = obj/asm

OBJS = $(wildcard $(OBJ_OUT)/*.o)
AS_OBJS = $(wildcard $(ASM_OBJ)/*.o)
C_SRC = src
C_FILES = $(wildcard $(C_SRC)/*.c)
C_O_FILES = $(addprefix $(OBJ_OUT)/,$(notdir $(C_FILES:.c=.o)))

LD_ARGS = -m elf_i386 -T linker.ld

NASM_ARGS = -f elf
ASM_SRC = asm
ASM_FILES = $(wildcard $(ASM_SRC)/*.s)
NASM_O_FILES = $(addprefix $(ASM_OBJ)/,$(notdir $(ASM_FILES:.s=.o)))

all: asm c link mkdisk

link:
	ld $(LD_ARGS) -o kernel.bin $(OBJS) $(AS_OBJS)
	
asm: $(NASM_O_FILES)
	
$(ASM_OBJ)/%.o : $(ASM_SRC)/%.s
	nasm $(NASM_ARGS) -o $@ $^
	
c: $(C_O_FILES)
$(OBJ_OUT)/%.o : $(C_SRC)/%.c
		gcc $(GCC_ARGS) -o $@ $^

mkdisk: 
	dd if=/dev/zero of=pad bs=1 count=750
	rm -f floppy.img
	cat grub/stage1 grub/stage2 pad kernel.bin > floppy.img
	
clean:
	rm -f *.o *~
	rm -f $(OBJS)
	rm -f $(C_SRC)/*~ $(ASM_SRC)/*~ $(INCLUDE)/*~
	rm -f pad kernel.bin floppy.img
