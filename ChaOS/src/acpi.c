#include <system.h>

#include "acpi.h"

extern int prints(const char* msg);
extern void print(const char* msg, int length);

/* Loads the RSDP Descriptor from memory */
static int load_rsdp_desc(struct rsdp_desc *rsdp) {
  static const char sig[] = "RSD PTR ";
  char *start = (char*)BIOS_MEM_START;
  
  /* Loop through memory until we find it. */
  while (start != (char*)BIOS_MEM_END) {
    
    int i = 0;
    while (start[i] == sig[i] && i < 8) i++;
    
    if (i == 8) {
      kmemcpy(rsdp, start, sizeof(struct rsdp_desc));
      return 0;
    }
    
    start++;
  }
  
  return 1;
}

/* Do a checksum on the descriptor by adding all the bytes. The char will
 * overflow once it hits 0xFF and should equal 0 once the checksum is
 * completed. */
static int doChecksum(struct rsdp_desc *rsdp) {
  unsigned char sum = 0;
  
  int i;
 
  int len = sizeof(struct rsdp_desc) - 1;
  if ((*rsdp).rev == 2) {
    prints("Detected RSDP Version 2.0\n");
    len = (*rsdp).length;
  } else {
    prints("Detected RSDP Version 1.0\n");
  }
  
  // Do the checksum.
  for (i = 0; i < len; i++) {
    sum += ((char *) rsdp)[i];
  }
  
  return sum == (*rsdp).checksum;
}

/* Check to ensure that the rsdp was loaded properly. */
static int check_rsdp(struct rsdp_desc *rsdp) {
  int c = doChecksum(rsdp);
  
  return c;
}

void setup_acpi() {
  struct rsdp_desc rsdp;
  if (load_rsdp_desc(&rsdp) == 0 && check_rsdp(&rsdp)) {
    prints("RSDP Descriptor Loaded Successfully!\n");
  } else {
    prints("RSDP Header failed checksum test...\n");
  }
}