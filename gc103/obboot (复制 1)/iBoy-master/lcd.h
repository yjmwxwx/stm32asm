

#ifndef __LCD_H__
#define __LCD_H__

#include "defs.h"



struct vissprite
{
	int x;
	byte pal, pri, pad[6];
	unsigned short pat;
	byte *buf;  // gbc
};

struct scan
{
	int bg[64];
	int wnd[64];
	unsigned short *buf;
	byte *cbuf;
	//byte pal1[128];
	//un16 pal2[64];
	//un32 pal4[64];
	unsigned short pal[8];
	unsigned short bgpal[4];

#ifndef OLD_KERNEL
	byte pri[256];
#endif
	struct vissprite vs[16];
	int ns, l, x, y, s, t, u, v, wx, wy, wt, wv;
};


struct obj
{
	byte y;
	byte x;
	byte pat;
	byte flags;
};


#ifdef OLD_KERNEL
byte dummy_vbank[8192];
#endif

struct lcd
{
	byte vbank[8192];
	#ifdef OLD_KERNEL
		byte *vbank2;
	#else
		byte vbank2[8192];
	#endif
	union
	{
		byte mem[256];
		struct obj obj[40];
	} oam;

	#ifdef OLD_KERNEL
		byte patdirty[384];   // mono only
	#else
		byte patdirty[1024];   // 1024 for color
	#endif


	byte anydirty;

	#ifndef OLD_KERNEL
		byte mainpal[128];
		byte needmainpal;

		int palfetch[144][2];
		byte pals[144][128];  // oh my god, if sram wasnt full, now it is
		short pal2[64];
	#endif

};




#ifdef USE_COP
	struct hiramcopy
	{
		byte cR_BGP;
		byte cR_OBP0;
		byte cR_OBP1;
		//byte cR_LY;
		unsigned char cR_WY;	 // has special semantic (is not copied)
								 // should be [144], bad... FIXME
		byte cR_WX[144];
		byte cR_SCX[144];
		byte cR_SCY[144];
		byte cR_LCDC[144];

		byte cop_stop;
	};

	extern struct hiramcopy *hiramcopy;
	extern struct lcd *lcd;
	#define LCDP lcd
#else
	#define LCDP (&lcd)
	extern struct lcd lcd;
#endif





#ifndef USE_COP
	#define CR_LCDC	(R_LCDC)
	#define CR_OBP0	(R_OBP0)
	#define CR_OBP1	(R_OBP1)
	#define CR_BGP	(R_BGP)
	#define CR_WX	(R_WX)
	#define CR_WY	(scan.wy)
	#define CR_LY	(R_LY)
	#define CR_SCX	(R_SCX)
	#define CR_SCY	(R_SCY)
#else

	#define CR_OBP0	((hiramcopy->cR_OBP0))
	#define CR_OBP1	((hiramcopy->cR_OBP1))
	#define CR_BGP	((hiramcopy->cR_BGP))
	#define CR_WY	((hiramcopy->cR_WY))
	#define CR_LY	curline
	#define CR_WX	((hiramcopy->cR_WX[curline]))
	#define CR_SCX	((hiramcopy->cR_SCX[curline]))
	#define CR_SCY	((hiramcopy->cR_SCY[curline]))
	#define CR_LCDC	((hiramcopy->cR_LCDC[curline]))
#endif



#define LCD_LAST_LINE 143
#define LINE_NUMBER_OF_BACKGOUND_PAL 17
#define UNUSED_WX_BYTE 0x7D  /*just a guess*/



#define ANYDIRTY (LCDP->anydirty)
#define PATDIRTY (LCDP->patdirty)

extern struct scan scan;
extern short screen[145*160];



void updatepatpix();
void lcd_reset();
void lcd_begin();
void vram_write(addr a, byte b);
void update_pal0();
void update_pal1();
void lcd_refreshline();
void vram_dirty();

int lcd_set_interlace(int on);
void lcd_set_yoffset(int val);
void lcd_yflip();

#ifdef PORTABLE
	void set_input_mode();
#endif




void gbc_pal_dirty();
void pal_write(int i, byte b);
void lcd_gbc_refreshline();

#endif
