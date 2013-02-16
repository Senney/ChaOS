#include <stdint.h>

// ChaOS includes.
#include <system.h>
#include <screen.h>
#include <print.h>
#include <gdt.h>
#include <acpi.h>

#define CONSOLE_COLOR 0x07

struct multiboot {
  // Multiboot Header
  int magic;
  int flags;
  int checksum;

  // Data
  int mboot;
  int code;
  int bss;
  int end;
  int loader;
};

int kmain(/*struct multiboot *mboot_ptr*/) {
  init_video();  
  clear_screen();
  
  setup_gdt();

  setup_acpi();

  return 0xDEADBABA;
}