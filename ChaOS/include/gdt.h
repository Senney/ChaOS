#ifndef GDT_H
#define GDT_H

#include <stdint.h>

// GDT Pointer referenced from the linux kernel.
struct gdt_ptr {
  uint16_t len;
  uint32_t ptr;
} __attribute__ ((packed));

struct gdt_entry {
  uint16_t limit_lwo;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
} __attribute((packed));

struct gdt_entry gdt[3];
struct gdt_ptr gp;

void setupGDT();

#endif