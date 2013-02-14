#ifndef ACPI_H
#define ACPI_H

#include <stdint.h>

//#define VERSION_1
#define VERSION_2

#define BIOS_MEM_START 	0x000E0000
#define BIOS_MEM_END	0x000FFFFF

// Two variations on the rsdp header.


// V1.0
#ifdef ACPI_VERSION_1
struct rsdp_desc {
  char signiture[8];
  uint8_t checksum;
  char oemid[6];
  uint8_t rev;
  uint32_t rsdt_addr;
} __attribute__ ((packed));
#else
// V2.0
struct rsdp_desc {
  char signiture[8];
  uint8_t checksum;
  char oemid[6];
  uint8_t rev;
  uint32_t rsdt_addr;
  
  uint32_t length;
  uint64_t xsdt_addr;
  uint8_t ext_checksum;
  uint8_t reserved[3];
} __attribute__ ((packed));
#endif

struct rsdp_desc rsdp;

void setup_acpi();

#endif