[BITS 32]

[GLOBAL gdt_flush]
[EXTERN gp]

gdt_flush:
  lgdt	[gp]		; Load the GDT with our pointer.
  mov 	ax, 0x10	; 0x10 is the offset in the GDT to our data seg.
  
  ; Setup the segment registers so they all point to the right spot.
  mov	ds, ax
  mov	es, ax
  mov	fs, ax
  mov	gs, ax
  mov	ss, ax
  
  jmp	0x08:flush2	; Far jump to flush2
flush2:
  ret			; Return to calling code.
