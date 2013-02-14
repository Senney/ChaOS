#include "system.h"

/* Copy memory src to dst */
uint8_t *kmemcpy(void *dst, const void *src, int count) {
  char* dst_c = (char*)dst;
  char* src_c = (char*)src;
  
  while (count--) {
   *dst_c++ = *src_c++; 
  }
  
  return dst;
}

/* Set the memory at [dst] to [val], [count] times. */
uint8_t *kmemset(uint8_t *dst, uint8_t val, int count) {
  int i;
  for (i = 0; i < count; i++) {
    dst[i] = val;
  }
  return dst;
}

/* Set larger amounts of memory */
uint16_t *kmemsetw(uint16_t *dst, uint16_t val, int count) {
  int i;
  for (i = 0; i < count; i++) {
    dst[i] = val;
  }
  return dst;
}

/* Get the length of an input string up to the nearest null-terminator */
int strlen(const char *str) {
  int l = 0;
  while (*(str++) != 0) l++;
  return l;
}

// HW Interface
/* Read from the specified port. */
uint8_t inportb(uint16_t _port) {
  uint8_t rv;
  __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
  return rv;
}

void outportb(uint16_t _port, uint8_t _data) {
  __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

// Convert integer to character.
void itoa(int value, char *sp, int radix) {
 char tmp[16];
 char *tp = (char*)tmp;
 int i;
 unsigned int v = 0;
 int sign;
 
 sign = (radix == 10 && value < 0);
 if (sign)	v = -v;
 else		v = (unsigned)value;
 
 while (v || tp == tmp) {
   i = v % radix;
   v /= radix;
   if (i < 10)
     *tp++ = i + '0';
   else
     *tp++ = i + 'a' - 10;
 }
 
 if (sign)
   *sp++ = '-';
 while (tp > tmp)
   *sp++ = *--tp;
}



