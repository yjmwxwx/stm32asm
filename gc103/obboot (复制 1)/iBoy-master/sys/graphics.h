#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "lcdll.h"
#include "cp850-8x8.h"

#define inl(p) (*(volatile unsigned long *) (p))


#define IPOD_LEFT	0x04
#define IPOD_RIGHT	0x02
#define IPOD_UP		0x10
#define IPOD_DOWN	0x08
#define IPOD_CENTER	0x01


#define THREESWAP(a,b) {a^=b;b^=a;a^=b;}

void draw_rect(int x, int y, int xx, int yy, unsigned short pat);
void draw_string(int x, int y, const char *s, int inv);
void draw_refresh();

void err_msg(char *msg, int ms, ...);

#endif /*GRAPHICS_H_*/
