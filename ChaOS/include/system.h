#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

/* system.c */

// Memory management
uint8_t *kmemcpy(void *dst, const void *src, int count);
uint8_t *kmemset(uint8_t *dst, uint8_t val, int count);
uint16_t *kmemsetw(uint16_t *dst, uint16_t val, int count);
int strlen(const char *str);

// Helpers
// Grabbed from
// http://stackoverflow.com/questions/3440726/what-is-the-proper-way-of-implementing-a-good-itoa-function
void itoa(int value, char *sp, int radix);

// HW Interface
uint8_t inportb(uint16_t _port);
void outportb(uint16_t _port, uint8_t _data); 

#endif