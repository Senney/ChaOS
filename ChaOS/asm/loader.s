; Code referenced from http://wiki.osdev.org/Bare_Bones
; http://www.jamesmolloy.co.uk/tutorial_html/2.-Genesis.html

[BITS 32]

[GLOBAL mboot]		; Make mboot accessible from C.
[EXTERN code] 		; Start of .text
[EXTERN	bss]		; Start of .bss
[EXTERN	end]		; End of the last loadable section.

; Set up multiboot header.
MODULEALIGN	equ 1<<0
MEMINFO		equ 1<<1
FLAGS		equ MODULEALIGN | MEMINFO
MAGIC		equ 0x1BADB002 
CHECKSUM	equ -(MAGIC + FLAGS)

mboot:
	dd	MAGIC
	dd	FLAGS
	dd	CHECKSUM

	dd	mboot		; Location of the descriptor
	dd	code		; Start of the kernel .text section.
	dd	bss			; End of bss section.
	dd	end			; End of the kernel space.
	dd	loader		; Location of the start point.
 
[EXTERN kmain]		; C entry point.
[GLOBAL	loader]		; Visibility of entry point.

; Reserve stack space for kernel.
STACKSIZE	equ 0x4000	; 16 kb of stack space.

loader:
	push	ebx		; Load multiboot header location.

	mov	esp, stack + STACKSIZE
	mov	[magic], eax

	cli					; Disable interrupts.
	call 	kmain		; Jump to C entry point
	
.hang:
	hlt
	jmp	.hang

section	.bss

align 4
stack:	resb STACKSIZE
magic:	resd 1
mbd:	resd 1
