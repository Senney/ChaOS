#ifndef SCREEN_H
#define SCREEN_H

#include <system.h>

#define SCR_HEIGHT 25
#define SCR_WIDTH 80

struct _cursor {
  int x;
  int y;
};

// Keeps track of our cursor position.
struct _cursor screen_curs;

void init_video();
void clear_screen();
void move_cursor();
void scroll_screen();

void putc(unsigned char c);

unsigned short* get_mem_loc();

#endif