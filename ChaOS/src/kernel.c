#include <stdint.h>

// ChaOS includes.
#include <gdt.h>

#define CONSOLE_COLOR 0x07

volatile unsigned char* vram = (unsigned char*)0xB8000;

void clear(void);
void chput(char c);
int prints(const char* msg);
int cprints(const char* msg, int color);
void print(const char* msg, int len);

int out_point = 0;

char welcomeMessage[] = "Hello world! I am ";
char chaOS[] = "ChaOS.";

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
	clear();
	prints(welcomeMessage);
	cprints(chaOS, 0x04);
	
	prints("Setting up GDT...\n");
	setup_gdt();
	prints("GDT set up successfully!");

	return 0xDEADBABA;
}

void clear(void) {
	const int W = 160;
	const int H = 80;

	int i = 0;
	int j;
	while (i < H) {
		j = 0;
		while (j < W) {
			vram[(i * H) + j] = 0;
			j++;
		}
		i++;
	}
}

void chput(char c) {
	vram[out_point] = (int)c;
	vram[out_point+1] = CONSOLE_COLOR;
	out_point += 2;	
}

void chputc(char c, int color) {
	vram[out_point] = (int)c;
	vram[out_point+1] = color;
	out_point += 2;
}

int prints(const char* msg) {
	int i = 0;
	while (msg[i] != 0) {
		chput(msg[i]);
		i++;
	}
	return i;
}

int cprints(const char* msg, int color) {
	int i = 0;
	while (msg[i] != 0) {
		chputc(msg[i], color);
		i++;
	}
	return i;
}

void print(const char* msg, int len) {
	int i = 0;
	while (i < len) {
		chput(msg[i]);
		i++;
	}
}
