#ifndef LCD_4G_H_
#define LCD_4G_H_

#include "../defs.h"
#include "stdio.h"

typedef void (*pBlitter)(unsigned short *buf, byte format);  // assume GB Size 160 x 144 here

extern pBlitter lcdll_blit;

void blitter_ipod_update_nano(unsigned short * addr, byte format);
void blitter_ipod_update_photo(unsigned short * addr, byte format);
void blitter_ipod_update_video(unsigned short * addr, byte format);
void blitter_ipod_update_4g(unsigned short * addr, byte format);
void blitter_ipod_update_mini(unsigned short * addr, byte format);

void blitter_setwindow(int startx, int starty, int endx, int endy);

int blitter_init(void);

#define LCD_LOW_GRAY 	2		/* 0:1/4   1:1/3   2:1/2   3:0 */
#define LCD_HI_GRAY  	0   	/* 0:3/4   1:2/3   2:1/2   3:1 */
#define LCD_ENABLE   	0x01
#define LCD_INVERT   	0x02

#define LCD_MODE_VIS_TOP -10
#define LCD_MODE_VIS_MID 3
#define LCD_MODE_VIS_BOT 4
#define LCD_MODE_SCALE -20

#define LCD_MODE_MINI_LEFT 0
#define LCD_MODE_MINI_MID 1
#define LCD_MODE_MINI_RIGHT 3
#define LCD_MODE_MINI_SCALE 0x10

#define BLITTER_FORMAT_GBC_PAL 2
#define BLITTER_FORMAT_2BP_MENU 1
#define BLITTER_FORMAT_2BP 0


#ifdef USE_COP
	#define LCD_MODE_P 0x40015030
	#define LCD_MINI_MODE_P 0x40015034
#else
	extern int lcd_mode;
	#define LCD_MODE_P &lcd_mode
	extern int lcd_mini_mode;
	#define LCD_MINI_MODE_P &lcd_mini_mode
#endif

//#define ipod_lcd_base	0x70003000  orig quite different !!
//#define ipod_rtc 		0x60005010

#define outs(v,p) (*(volatile unsigned short *) (p) = (v))


#ifndef PORTABLE
#define inl(p) (*(volatile unsigned long *) (p))
#define ins(p) (*(volatile unsigned short *) (p))
#define outl(v,p) (*(volatile unsigned long *) (p) = (v))
#define inb(p) (*(volatile unsigned char *) (p))
#define outb(v,p) (*(volatile unsigned char *) (p) = (v))
#define inw(p) (*(volatile unsigned short *) (p))
#define outw(v,p) (*(volatile unsigned short *) (p) = (v))
// FIXME: outw, inw as good as outl, inl
#else
int inl(int p);
byte inb(int p);
void outl(int v, int p);
#endif


//#define lcd_wait_write() {while( (inl(ipod_lcd_base) & 0x8000) ) ;}

#ifdef PORTABLE
void reset_input_mode (void);
#endif

#endif /*LCD_4G_H_*/
