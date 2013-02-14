#include "gdt.h"

static void gdt_set_gate(int num, unsigned long base, unsigned long limit,
			 uint8_t access, uint8_t gran) {
  /* Set the descriptor base address. */
  gdt[num].base_low = (base & 0xFFFF);
  gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;
  
  /* Set the limits. */
  gdt[num].limit_low = (limit & 0xFFFF);
  gdt[num].granularity = ((limit >> 16) & 0x0F);
  
  /* Setup the granularity and access flags. */
  gdt[num].granularity |= (gran & 0xF0);
  gdt[num].access = access;
}

void setup_gdt() {
  /* Setup GDT Pointer - 3 entries at the base of &gdt */
  gp.len = (sizeof(struct gdt_entry) * 3) - 1;
  gp.ptr = (int)&gdt;
  
  /* Setup the NULL descriptor of memory. */
  gdt_set_gate(0, 0, 0, 0, 0);
  
  /* Code segment */
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  
  /* Data segment */
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  
  /* Flush the old GDT */
  gdt_flush();
}