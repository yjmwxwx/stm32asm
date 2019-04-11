// NEWORDER VERSION
//
// use 16Bit, with SpritePalette
// now with Background-PAL
// fixed sprite bug
//

#include <fcntl.h>
#include <linux/fb.h>
#include <linux/vt.h>
#include <sys/ioctl.h>
#include <string.h>

#include "defs.h"
#include "regs.h"
#include "hw.h"
#include "mem.h"
#include "lcd.h"

#include "sys/lcdll.h"


#ifdef USE_ASM
#include "asm.h"
#endif
#ifdef USE_COP
#include "cop.h"
#endif


#define MIN(x,y) ((x)<(y))?(x):(y)

#define BG (scan.bg)
#define WND (scan.wnd)
#define BUF (scan.buf)
#define CBUF (scan.cbuf)
#define PRI (scan.pri)

#define PAL (scan.pal)
#define BGPAL (scan.bgpal)

#define VS (scan.vs) // vissprites
#define NS (scan.ns)

#define L (scan.l) // line
#define X (scan.x) // screen position
#define Y (scan.y)
#define S (scan.s) // tilemap position
#define T (scan.t)
#define U (scan.u) // position within tile
#define V (scan.v)
#define WX (scan.wx)
//#define WY (scan.wy) //fixme Sigle core
#define WT (scan.wt)
#define WV (scan.wv)


#ifndef USE_COP
	int lcd_mode;

	struct lcd lcd;

	int *hw_cgbp = &hw.cgb;
#else
	int curline = -1; // first line is curline+1


	#ifdef OLD_KERNEL
		#define LCD_BASE 0x40015038
	#else
		#define LCD_BASE ((byte*) 0x40000300 + 30 * 1024)
	#endif
	struct lcd *lcd = (struct lcd *) LCD_BASE;
	struct hiramcopy *hiramcopy = (struct hiramcopy *) (LCD_BASE + sizeof(struct lcd));
#endif




short screen[145*160];   // for pure gb only 144x20 shorts used
						// for gbc 144x160 bytes used


struct scan scan;

static int sprsort = 0; //


//unsigned short patpix[8*4096]; // 2 * 8 * 4K = 64K
unsigned short patpix_m[(256)*8];  // [256 Tiles mirrored]
unsigned short patpix  [(256 + 128)*8];  // [256 Tiles normal  ][128 Tiles  ]


inline unsigned int reverseShort(unsigned int t) {
	return 	((t&0x0003)<<14) |
		   	((t&0x000C)<<10) |
		   	((t&0x0030)<< 6) |
		   	((t&0x00C0)<< 2) |
		   	((t&0x0300)>> 2) |
		   	((t&0x0C00)>> 6) |
		   	((t&0x3000)>>10) |
		   	((t&0xC000)>>14);
}

inline unsigned int getPatTileLine(int adr) {
	unsigned int t, c, temp, temp1, temp2;
	byte *vram = LCDP->vbank;

			temp1 = vram[adr]; temp1 |= temp1 << 8;
			temp2 = vram[adr+1]; temp2 |= temp2 << 8;

			temp =  (~(temp1 | temp2))&0xffff  & BGPAL[0];  // 00
			temp |= ((temp1 ^ temp2) & temp1) & BGPAL[1];  // 01
			temp |= ((temp1 ^ temp2) & temp2) & BGPAL[2];  // 10
			temp |= ((temp1 & temp2))         & BGPAL[3];  // 11

			temp1 =  temp & 0xff;
			temp2 =  temp >> 8;


	c = (temp1 & 0x10)>>4;
	c |= (temp1 & 0x20)>>3;
	c |= (temp1 & 0x40)>>2;
	c |= (temp1 & 0x80)>>1;
	t = c << 8;
	c = (temp1 & 0x01);
	c |= (temp1 & 0x02)<<1;
	c |= (temp1 & 0x04)<<2;
	c |= (temp1 & 0x08)<<3;
	t |= c;

	c = (temp2 & 0x10)>>3;
	c |= (temp2 & 0x20)>>2;
	c |= (temp2 & 0x40)>>1;
	c |= (temp2 & 0x80);
	t |= (c<<8);
	c = (temp2 & 0x01)<<1;
	c |= (temp2 & 0x02)<<2;
	c |= (temp2 & 0x04)<<3;
	c |= (temp2 & 0x08)<<4;
	t |= c;
	return t;
}
inline void updatepatpix()
{
	unsigned int t;
	int a, i, j;

	for (i = 0; i < 384; i++)
	{
		//if (i == 384) i = 512;
		//if (i == 896) break;
		if (!PATDIRTY[i]) continue;
		PATDIRTY[i] = 0;
		for (j = 0; j < 8; j++)
		{
			a = ((i<<4) + (j<<1));
			t = getPatTileLine(a);
			patpix[j*384 + i] = reverseShort(t);
			if(i < 256)
				patpix_m[j*256+i] = t;
		}
	}
	ANYDIRTY = 0;
}


static void tilebuf()
{
	int i, cnt;
	int base;
	byte *tilemap;
	int *tilebuf;
	int *wrap;
	static int wraptable[64] =
	{
		0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,-32
	};

	base = ((CR_LCDC&0x08)?0x1C00:0x1800) + (T<<5) + S;
	tilemap = LCDP->vbank + base;
	tilebuf = BG;
	wrap = wraptable + S;
	cnt = ((WX + 7) >> 3) + 1;


		if (CR_LCDC & 0x10)
			for (i = cnt; i > 0; i--)
			{
				*(tilebuf++) = *(tilemap++);
				tilemap += *(wrap++);
			}
		else
			for (i = cnt; i > 0; i--)
			{
				*(tilebuf++) = (256 + ((n8)*(tilemap++)));
				tilemap += *(wrap++);
			}


	if (WX >= 160) return;

	base = ((CR_LCDC&0x40)?0x1C00:0x1800) + (WT<<5);
	tilemap = LCDP->vbank + base;
	tilebuf = WND;
	cnt = ((160 - WX) >> 3) + 1;

		if (CR_LCDC & 0x10)
			for (i = cnt; i > 0; i--)
				*(tilebuf++) = *(tilemap++);
		else
			for (i = cnt; i > 0; i--)
				*(tilebuf++) = (256 + ((n8)*(tilemap++)));

}


#define OFF(x) ((x)&0x07)

inline void bg_scan()
{
	int dest, cnt, offset;
	unsigned short *src;
	int *tile;

	if (WX <= 0) return;
	cnt = WX;
	tile = BG;
	src = patpix + (V*384);

	BUF[0] =  (src+(*(tile++)))[0] >> (U<<1) ;

	dest = 8-U;
	offset = (OFF(dest)<<1);
	dest >>=3;

	if(!offset) BUF[dest] = 0;
	BUF[dest++] |= (src+(*(tile)))[0] << offset;
	cnt -= 8;

	while (cnt > 0)
	{
		BUF[dest++] = (src+(*(tile)))[0] >> (16 - offset) | (src+(*(tile+1)))[0] << offset;
		tile++;
		cnt -= 8;
	}
}


inline void wnd_scan()
{
	int cnt, dest, offset;
	unsigned short *src;
	int *tile;

	if (WX >= 160) return;
	cnt = 160 - WX;
	tile = WND;
	dest = WX;
    src = patpix + (WV*384);

    offset = (OFF(dest)<<1);
    dest >>=3;

    if(!offset) BUF[dest] = 0;
	BUF[dest++] |= (src+(*(tile)))[0] << offset;
    cnt -= (16-offset)>>1;

	while (cnt > 0)
	{
		BUF[dest++] = (src+(*(tile)))[0] >> (16 - offset) | (src+(*(tile+1)))[0] << offset;
		tile++;
		cnt -= 8;
	}
}

inline void spr_count()
{
	int i;
	struct obj *o;

	NS = 0;
	if (!(CR_LCDC & 0x02)) return;

	o = LCDP->oam.obj;

	for (i = 40; i; i--, o++)
	{
		if (L >= o->y || L + 16 < o->y)
			continue;
		if (L + 8 >= o->y && !(CR_LCDC & 0x04))
			continue;
		if (++NS == 10) break;
	}
}

inline void spr_enum()
{
	int i, j, x, l;
	struct obj *o;
	struct vissprite ts[10];
	int v, pat;
	//short *p;

	NS = 0;
	if (!(CR_LCDC & 0x02)) return;

	o = LCDP->oam.obj;

	for (i = 40; i; i--, o++)
	{
		if (L >= o->y || L + 16 < o->y)
			continue;
		if (L + 8 >= o->y && !(R_LCDC & 0x04))
			continue;
		VS[NS].x = (int)o->x - 8;
		v = L - (int)o->y + 16;


		VS[NS].pal = (o->flags & 0x10) >> 2; // 0 or 4
		VS[NS].pri = (o->flags & 0x80) >> 7;


/*		pat = o->pat | (((int)o->flags & 0x60) << 5);
		if ((R_LCDC & 0x04))
		{
			pat &= ~1;
			if (v >= 8)
			{
				v -= 8;
				pat++;
			}
			if (o->flags & 0x40) pat ^= 1;
		}
		VS[NS].buf = patpix + (v*384)+pat;*/


		pat = o->pat;

		if ((CR_LCDC & 0x04))
		{
			pat &= ~1;
			if (v >= 8)
			{
				v -= 8;
				pat++;
			}
			if (o->flags & 0x40) pat ^= 1;
		}
		if(o->flags & 0x40)
			v = 7 - v;

		if(o->flags & 0x20)
			VS[NS].pat = *(patpix_m + (v*256) + pat);
		else
			VS[NS].pat = *(patpix + (v*384) + pat);


		//VS[NS].buf = p + (v*384) + pat;

		if (++NS == 10) break;
	}

	if (!sprsort || !NS) return;

        for (i = 0; i < NS; i++)
        {
                l = 0;
                x = VS[0].x;
                for (j = 1; j < NS; j++)
                {
                        if (VS[j].x < x)
                        {
                                l = j;
                                x = VS[j].x;
                        }
                }
                ts[i] = VS[l];
                VS[l].x = 160;
        }
        memcpy(VS, ts, sizeof VS);

}

const unsigned short Pattern[4] = { 0x0000, 0x5555, 0xAAAA, 0xFFFF };
unsigned short bg0_pattern;
static unsigned char plb=0;

int update_bgpal(unsigned char newpal) {
	static byte lp = 0;
	const unsigned short BgPattern[4] = { 0x0000, 0x00FF, 0xFF00, 0xFFFF };

	if(newpal == lp) return 0;

	lp = newpal;

	bg0_pattern = Pattern[lp&3];

	BGPAL[0] = BgPattern[(lp>>0)&3];
	BGPAL[1] = BgPattern[(lp>>2)&3];
	BGPAL[2] = BgPattern[(lp>>4)&3];
	BGPAL[3] = BgPattern[(lp>>6)&3];


	ANYDIRTY = 1;
	memset(PATDIRTY, 1, 384);

	updatepatpix();

	//adjust sprite paletes as well
	update_pal0();
	update_pal1();

	return 1;
}

void update_pal0(){
	byte obp = CR_OBP0;

	//PAL[0] = 0;
	PAL[((plb^ bg0_pattern)>>2) & 3] = Pattern[(obp>>2) & 0x03];
	PAL[((plb^ bg0_pattern)>>4) & 3] = Pattern[(obp>>4) & 0x03];
	PAL[((plb^ bg0_pattern)>>6) & 3] = Pattern[(obp>>6) & 0x03];
}

void update_pal1(){
	byte obp = CR_OBP1;

	//PAL[4] = 0;
	PAL[4| (((plb^ bg0_pattern)>>2) & 3)] = Pattern[(obp>>2) & 0x03];
	PAL[4| (((plb^ bg0_pattern)>>4) & 3)] = Pattern[(obp>>4) & 0x03];
	PAL[4| (((plb^ bg0_pattern)>>6) & 3)] = Pattern[(obp>>6) & 0x03];
}


// Palette for the Sprites
inline unsigned short ApplyPal(unsigned short in, int pal){

	unsigned int temp, ret;

	temp = in | (in<<16);  // Match for Index (01) and (10) (and use 32Bit);

	temp ^= 0x5555AAAA;
	temp &= (temp<<1);
	temp &= 0xAAAAAAAA;
	temp |= (temp>>1);

	ret = temp & (PAL[pal|1]); 				// (01) (pal   is either 0 or 4)
	ret |= (temp >> 16) & (PAL[pal|2]);   // (10) (pal|1 is either 1 or 5) ...

	// Match for Index (11)
	temp |= temp >> 16;  // now the 16 lower bits of temp are (11)  - for (01),(10) in "in"
	ret |= (in & (~temp))  & (PAL[pal|3]); // (11) mask out all (01),(10) from "in" - only (11) stay

	return ret;
}

inline unsigned short CLEAN_MASK(unsigned short in){
	in |= in<<1;
	in &= 0xAAAA;
	in |= in >>1;
	return ~in;
}

// Sprite on left border 1 to 8 Pixel
inline void copy_to_buffer_s_first(unsigned short p, int offset, int pal, int pri /*(Sprite behind Background) */) {
	int temp, mb;



	if(pri){
		mb = CLEAN_MASK(BUF[0] ^ bg0_pattern);
		temp = (p >> (offset << 1)) & mb;
		BUF[0] &= CLEAN_MASK(temp);
		BUF[0] |= ApplyPal(temp, pal);

		//temp = (ApplyPal(p, pal) >> (offset << 1))& CLEAN_MASK(BUF[0] ^ bg0_pattern);
		//BUF[0] &= CLEAN_MASK(temp);
		//BUF[0] |= temp;
	}
	else{
		temp = p >> (offset << 1);
		BUF[0] &= CLEAN_MASK(temp);
		BUF[0] |= ApplyPal(temp, pal);
	}
}

// Sprite always 8 Pixel (might draw over right border)
inline void copy_to_buffer_s8(unsigned short p, int pos, int pal , int pri ) {
	int temp, offset;
	unsigned short s;
	unsigned short mb;

	s = ApplyPal(p, pal);
	offset = OFF(pos) <<1;
	pos>>=3;

	if(pri) {
		// ugh...
		mb = CLEAN_MASK(BUF[pos] ^ bg0_pattern);
		temp = ((p) << (offset)) & mb;
		BUF[pos] &= CLEAN_MASK(temp);
		BUF[pos] |= ((s) << (offset)) & mb;
		pos++;

		mb = CLEAN_MASK(BUF[pos] ^ bg0_pattern);
		temp = ((p) >> (16-offset)) & mb;
		BUF[pos] &= CLEAN_MASK(temp);
		BUF[pos] |= ((s) >> (16-offset)) & mb;


//		temp = (s<<(offset)) & CLEAN_MASK(BUF[pos]^ bg0_pattern);
//		BUF[pos] &= CLEAN_MASK(temp);
//		BUF[pos] |= temp;
//		pos++;
//
//		temp = (s>>(16-offset)) & CLEAN_MASK(BUF[pos]^ bg0_pattern);
//		BUF[pos] &= CLEAN_MASK(temp);
//		BUF[pos] |= temp;

	}
	else {
		temp = (p) << (offset);
		BUF[pos] &= CLEAN_MASK(temp);
		BUF[pos] |= s<<(offset);
		pos++;

		temp = (p >> (16-offset));
		BUF[pos] &= CLEAN_MASK(temp);;
		BUF[pos] |= (s>>(16-offset));
	}
}

inline void spr_scan()
{
	int x;
	byte ns = NS;
	struct vissprite *vs;
	if (!ns) return;

	vs = &VS[ns-1];

	for (; ns; ns--, vs--)
	{
		x = vs->x;
		if (x > 160) continue;
		if (x < -7) continue;
		if (x <= 0)
		{   // Sprite on left Border
			copy_to_buffer_s_first(vs->pat^ bg0_pattern,-x, vs->pal, vs->pri);
		}
		else
		{
			copy_to_buffer_s8(vs->pat^ bg0_pattern, x, vs->pal, vs->pri);
		}
	}
}


inline void lcd_begin()
{
#ifdef USE_COP
	//hiramcopy->cR_WY[R_LY] = R_WY;
	CR_WY = R_WY;
#else
	CR_WY = R_WY;
#endif
}


int interlace = 0;


inline void lcd_refreshline()
{
	//static int next_line = 0;
	static byte pl0=0, pl1=0;

	#ifdef USE_COP
		curline++;
		if(curline > LCD_LAST_LINE){
			curline = 0;
		}

		// dont draw a line twice
		// CR_LCDC is used - a separate variable could be better
		while(inb(&CR_WX) == UNUSED_WX_BYTE){
			if(COP_STOPPED) {
				curline = -1;
				return; // terminate
			}
		}

	#endif
		//if (!(CR_LCDC & 0x80))
	//	return; /* should not happen... */

	WX = CR_WX - 7;

	#ifdef USE_COP
		CR_WX = UNUSED_WX_BYTE; //Mark line as drawn (problems ....
	#endif


	#ifndef USE_COP
	if(CR_LY==LINE_NUMBER_OF_BACKGOUND_PAL) {
		plb = CR_BGP;
	}
	if(CR_LY > LCD_LAST_LINE)
		return;
	#endif


	// update pal0 if changed
	if(pl0 != CR_OBP0){
		update_pal0();
		pl0 = CR_OBP0;
	}

	// update pal1 if changed
	if(pl1 != CR_OBP1){
		update_pal1();
		pl1 = CR_OBP1;
	}

	BUF = screen + CR_LY*20;


	L = CR_LY;
	X = CR_SCX;
	Y = (CR_SCY + L) & 0xff;
	S = X >> 3;
	T = Y >> 3;
	U = X & 7;
	V = Y & 7;


	if (CR_WY>L || /*CR_WY<0 ||*/ CR_WY>143 || WX<-7 || WX>159 || !(CR_LCDC&0x20))
		WX = 160;
	//WT = (L - CR_WY) >> 3;
	//WV = (L - CR_WY) & 7;

	WT = (L - CR_WY) >> 3;
	WV = (L - CR_WY) & 7;

//#ifdef USE_COP
//	cur_dma_line = (unsigned short *)(dma_buffer + (((L << 7) + (L << 5)) >> 2));
//#endif

	tilebuf();

	if (!(CR_LCDC & 0x01)) memset(BUF, 0, 40);
	else bg_scan();
	if ((CR_LCDC & 0x20)) wnd_scan();

	spr_enum();
	spr_scan();

	if(CR_LY==LCD_LAST_LINE) {
		#ifdef USE_COP
			plb = CR_BGP;
		#endif
		update_bgpal(plb);
		if(ANYDIRTY) updatepatpix();	// FIXME


		lcdll_blit(screen, BLITTER_FORMAT_2BP);
		//lcd_display_screen();
		//next_line = 0;
	}

   	//lcd_display_line(BUF);
}


inline void vram_write(addr a, byte b)
{
	if(R_VBK&1){
		LCDP->vbank2[a] = b;
	} else {
		LCDP->vbank/*[0R_VBK&1]*/[a] = b;
	}

	if (a >= 0x1800) return;
	PATDIRTY[((R_VBK&1)<<9)+(a>>4)] = 1;
	ANYDIRTY = 1;
}

inline void vram_dirty()
{
	ANYDIRTY = 1;
}

void cop_lcd_test();

inline void lcd_reset()
{

#ifdef OLD_KERNEL
	LCDP->vbank2 = dummy_vbank;
	memset(PATDIRTY, 1, 384);
#else
	memset(PATDIRTY, 1, 1024);
#endif

	//memset(screen, 0, 144*20*2);
	//memset(LCDP->vbank, 0, sizeof LCDP->vbank);

	lcd_begin();
	vram_dirty();

	#ifndef OLD_KERNEL
		if(hw.cgb) gbc_pal_dirty();
	#endif
}


