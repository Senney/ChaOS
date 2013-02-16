#include <stdarg.h>
#include <screen.h>
#include <system.h>
#include "print.h"

void print(const char* str, int len) {
  while (len--) {
    putc(*str++);
  }
}

void prints(const char* str) {
  print(str, strlen(str));
}

static int numDigits(int n) {
  int digits = 0;
  if (n < 0) digits = 1;
  while (n) {
    n /= 10;
    digits ++;
  }
  
  return digits;
}

/* Formats a print statement
 * 	%d - Integer Value
 * 	%c - Character Value
 * 	%s - String value
 * 	%x - Hex value
 */
void printf(const char* str, ...) {
  va_list args;
  va_start(args, str);
  
  int len = strlen(str);
  char c;
  while (len--) {
    c = *str;
    if (c == '%') {
      c = *(++str);
      if (c == 'd') {		// Expect integer.
	int d = va_arg(args, int), n = numDigits(d);
	char d_str[n];
	itoa(d, d_str, 10);
	print(d_str, n);
      } else if (c == 'c') {	// Expect character.
	char c_str = va_arg(args, int);
	putc(c_str);
      } else if (c == 's') {	// Expect string.
	char *c_str = (char*)va_arg(args, void*);
	prints(c_str);
      } else if (c == 'x') {	// Expect int.
	
      } else {
	putc(*(str-1));
	putc(c);
      }
    } else {
      putc(c);
    }
    
    str++;
  }
  
  va_end(args);
}
