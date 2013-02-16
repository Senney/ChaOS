#include "screen.h"

// Pointer to the location in memory 
// where console-memory is stored.
unsigned short* memptr;
int color = 0x0F;

/* Gets index within the memory pointer */
static inline int get_screen_index(int x, int y) {
  return (y * SCR_WIDTH) + x;
}

/* Initialize the video */
void init_video() {
  memptr = (unsigned short*)0xB8000;
  screen_curs.x = 0;
  screen_curs.y = 0;
}

/* Clear the screen and reset the cursor to 0, 0 */
void clear_screen() {
  unsigned short blank;
  int i;
  
  // Setup the char that we will draw in the bg for
  // clearing the screen.
  blank = 0x20 | (color << 8);
  
  // Clear the screen 1 line at a time.
  for (i = 0; i < SCR_HEIGHT; i++) {
    kmemsetw(memptr + (i * SCR_WIDTH), blank, SCR_WIDTH);
  }
  
  screen_curs.x = 0;
  screen_curs.y = 0;
  move_cursor();
}

/* Move the cursor to the specified position. */
void move_cursor() {
  unsigned short temp = get_screen_index(screen_curs.x,
					 screen_curs.y);
  
  /* Change the cursor location in the CRT Control Reg */
  outportb(0x3D4, 14);
  outportb(0x3D5, temp >> 8);
  outportb(0x3D4, 14);
  outportb(0x3D5, temp);
}

void scroll_screen() {
  unsigned short blank, temp;
  
  // Set the character to clear with.
  blank = 0x20 | (color << 8);
  
  if (screen_curs.y >= SCR_HEIGHT) {
    temp = screen_curs.y - SCR_HEIGHT + 1;
    
    // Move the previous screen info up 1 level.
    kmemcpy(memptr, 
	    memptr + (temp * SCR_WIDTH),
	    (SCR_HEIGHT - temp) * SCR_WIDTH * 2);
    
    // Clear the bottom line.
    kmemsetw(memptr + (SCR_HEIGHT - temp) * SCR_WIDTH,
	     blank,
	     SCR_WIDTH);
  }
}

void putc(unsigned char c) {
  unsigned short attr = (color << 8);
  unsigned short* scr;
  
  // Backspace
  if (c == 0x08) {
    if (screen_curs.x != 0) screen_curs.x--;
  }
  // Tab
  else if (c == 0x09) {
    screen_curs.x = (screen_curs.x + 8) & ~(8-1);
  }
  // Carriage Return
  else if (c == '\r') {
    screen_curs.x = 0;
  }
  // Newline
  else if (c == '\n') {
    screen_curs.x = 0;
    screen_curs.y++;
  }
  // All other characters.
  else if (c >= ' ') {
    scr = get_mem_loc();
    *scr = c | attr; // Set the character.
    screen_curs.x++;
  }
  
  if (screen_curs.x >= 80) {
    screen_curs.x = 0;
    screen_curs.y++;
  }
  
  scroll_screen();
  move_cursor();
}

unsigned short* get_mem_loc() {
  return memptr + get_screen_index(screen_curs.x,
				   screen_curs.y);
}
