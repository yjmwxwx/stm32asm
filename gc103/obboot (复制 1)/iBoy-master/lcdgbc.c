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
#include "lcdgbc.h"

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


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// FELLNIS GBC STUFF ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/*
static int filter[3][4] = {
	{ 195,  25,   0,  35 },
	{  25, 170,  25,  35 },
	{  25,  60, 125,  40 }
};
*/

#ifndef OLD_KERNEL

#define PAL2 (LCDP->pal2)


byte gbc_patpix[4096][8][8];


extern int curline;


void gbc_updatepatpix()
{
	int i, j, k;
	int a, c;
	byte *vram = LCDP->vbank;

	for (i = 0; i < 1024; i++)
	{
		if (i == 384) i = 512;
		if (i == 896) break;
		if (!PATDIRTY[i]) continue;
		PATDIRTY[i] = 0;
		for (j = 0; j < 8; j++)
		{
			a = ((i<<4) | (j<<1));
			for (k = 0; k < 8; k++)
			{
				c = vram[a] & (1<<k) ? 1 : 0;
				c |= vram[a+1] & (1<<k) ? 2 : 0;
				gbc_patpix[i+1024][j][k] = c;
			}
			for (k = 0; k < 8; k++)
				gbc_patpix[i][j][k] = gbc_patpix[i+1024][j][7-k];
		}
		for (j = 0; j < 8; j++)
		{
			for (k = 0; k < 8; k++)
			{
				gbc_patpix[i+2048][j][k] = gbc_patpix[i][7-j][k];
				gbc_patpix[i+3072][j][k] = gbc_patpix[i+1024][7-j][k];
			}
		}
	}
	ANYDIRTY = 0;
}


void gbc_tilebuf()
{
	int i, cnt;
	int base;
	byte *tilemap, *attrmap;
	int *tilebuf;
	int *wrap;
	static int wraptable[64] =
	{
		0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,-32
	};

	base = ((CR_LCDC&0x08)?0x1C00:0x1800) + (T<<5) + S;
	tilemap = LCDP->vbank + base;
	attrmap = LCDP->vbank2 + base;
	tilebuf = BG;
	wrap = wraptable + S;
	cnt = ((WX + 7) >> 3) + 1;

		if (CR_LCDC & 0x10)
			for (i = cnt; i > 0; i--)
			{
				*(tilebuf++) = *tilemap
					| (((int)*attrmap & 0x08) << 6)
					| (((int)*attrmap & 0x60) << 5);
				*(tilebuf++) = (((int)*attrmap & 0x07) << 2);
				attrmap += *wrap + 1;
				tilemap += *(wrap++) + 1;
			}
		else
			for (i = cnt; i > 0; i--)
			{
				*(tilebuf++) = (256 + ((n8)*tilemap))
					| (((int)*attrmap & 0x08) << 6)
					| (((int)*attrmap & 0x60) << 5);
				*(tilebuf++) = (((int)*attrmap & 0x07) << 2);
				attrmap += *wrap + 1;
				tilemap += *(wrap++) + 1;
			}

	if (WX >= 160) return;

	base = ((CR_LCDC&0x40)?0x1C00:0x1800) + (WT<<5);
	tilemap = LCDP->vbank + base;
	attrmap = LCDP->vbank2 + base;
	tilebuf = WND;
	cnt = ((160 - WX) >> 3) + 1;

		if (CR_LCDC & 0x10)
			for (i = cnt; i > 0; i--)
			{
				*(tilebuf++) = *(tilemap++)
					| (((int)*attrmap & 0x08) << 6)
					| (((int)*attrmap & 0x60) << 5);
				*(tilebuf++) = (((int)*(attrmap++)&7) << 2);
			}
		else
			for (i = cnt; i > 0; i--)
			{
				*(tilebuf++) = (256 + ((n8)*(tilemap++)))
					| (((int)*attrmap & 0x08) << 6)
					| (((int)*attrmap & 0x60) << 5);
				*(tilebuf++) = (((int)*(attrmap++)&7) << 2);
			}
}

static int priused(void *attr)
{
	un32 *a = attr;
	return (int)((a[0]|a[1]|a[2]|a[3]|a[4]|a[5]|a[6]|a[7])&0x80808080);
}

void gbc_bg_scan_pri()
{
	int cnt, i;
	byte *src, *dest;

	if (WX <= 0) return;
	i = S;
	cnt = WX;
	dest = PRI;
	src = LCDP->vbank2 + ((CR_LCDC&0x08)?0x1C00:0x1800) + (T<<5);

	if (!priused(src))
	{
		memset(dest, 0, cnt);
		return;
	}

	memset(dest, src[i++&31]&128, 8-U);
	dest += 8-U;
	cnt -= 8-U;
	if (cnt <= 0) return;
	while (cnt >= 8)
	{
		memset(dest, src[i++&31]&128, 8);
		dest += 8;
		cnt -= 8;
	}
	memset(dest, src[i&31]&128, cnt);
}

void gbc_wnd_scan_pri()
{
	int cnt, i;
	byte *src, *dest;

	if (WX >= 160) return;
	i = 0;
	cnt = 160 - WX;
	dest = PRI + WX;
	src = LCDP->vbank2 + ((CR_LCDC&0x40)?0x1C00:0x1800) + (WT<<5);

	if (!priused(src))
	{
		memset(dest, 0, cnt);
		return;
	}

	while (cnt >= 8)
	{
		memset(dest, src[i++]&128, 8);
		dest += 8;
		cnt -= 8;
	}
	memset(dest, src[i]&128, cnt);
}

static void blendcpy(byte *dest, byte *src, byte b, int cnt)
{
	while (cnt--) *(dest++) = *(src++) | b;
}

void gbc_bg_scan()
{
	int cnt;
	byte *src, *dest;
	int *tile;

	if (WX <= 0) return;
	cnt = WX;
	tile = BG;
	dest = CBUF;

	src = gbc_patpix[*(tile++)][V] + U;
	blendcpy(dest, src, *(tile++), 8-U);
	dest += 8-U;
	cnt -= 8-U;
	if (cnt <= 0) return;
	while (cnt >= 8)
	{
		src = gbc_patpix[*(tile++)][V];
		blendcpy(dest, src, *(tile++), 8);
		dest += 8;
		cnt -= 8;
	}
	src = gbc_patpix[*(tile++)][V];
	blendcpy(dest, src, *(tile++), cnt);
}

void gbc_wnd_scan()
{
	int cnt;
	byte *src, *dest;
	int *tile;

	if (WX >= 160) return;
	cnt = 160 - WX;
	tile = WND;
	dest = CBUF + WX;

	while (cnt >= 8)
	{
		src = gbc_patpix[*(tile++)][WV];
		blendcpy(dest, src, *(tile++), 8);
		dest += 8;
		cnt -= 8;
	}
	src = gbc_patpix[*(tile++)][WV];
	blendcpy(dest, src, *(tile++), cnt);
}


void gbc_spr_enum()
{
	int i;
	struct obj *o;
	int v, pat;

	NS = 0;
	if (!(CR_LCDC & 0x02)) return;

	o = LCDP->oam.obj;

	for (i = 40; i; i--, o++)
	{
		if (L >= o->y || L + 16 < o->y)
			continue;
		if (L + 8 >= o->y && !(CR_LCDC & 0x04))
			continue;
		VS[NS].x = (int)o->x - 8;
		v = L - (int)o->y + 16;

			pat = o->pat | (((int)o->flags & 0x60) << 5)
				| (((int)o->flags & 0x08) << 6);
			VS[NS].pal = 32 + ((o->flags & 0x07) << 2);

		VS[NS].pri = (o->flags & 0x80) >> 7;
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
		VS[NS].buf = gbc_patpix[pat][v];
		if (++NS == 10) break;
	}
}

void gbc_spr_scan()
{
	int i, x;
	byte pal, b, ns = NS;
	byte *src, *dest, *bg, *pri;
	struct vissprite *vs;
	static byte bgdup[256];

	if (!ns) return;

	memcpy(bgdup, CBUF, 256);
	vs = &VS[ns-1];

	for (; ns; ns--, vs--)
	{
		x = vs->x;
		if (x >= 160) continue;
		if (x <= -8) continue;
		if (x < 0)
		{
			src = vs->buf - x;
			dest = CBUF;
			i = 8 + x;
		}
		else
		{
			src = vs->buf;
			dest = CBUF + x;
			if (x > 152) i = 160 - x;
			else i = 8;
		}
		pal = vs->pal;

		if (vs->pri)
		{
			bg = bgdup + (dest - CBUF);
			while (i--)
			{
				b = src[i];
				if (b && !(bg[i]&3)) dest[i] = pal|b;
			}
		}
		else
		{
			bg = bgdup + (dest - CBUF);
			pri = PRI + (dest - CBUF);
			while (i--)
			{
				b = src[i];
				if (b && (!pri[i] || !(bg[i]&3)))
					dest[i] = pal|b;
			}
		}
	}

}


byte buf[256];

inline void lcd_gbc_refreshline()
{
	int i;

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
	if(CR_LY > LCD_LAST_LINE)
		return;
	#endif


	if(sys_ipod_is_color())
		CBUF = buf;
	else
		CBUF = (byte *) screen  + CR_LY*160;

	L = CR_LY;
	X = CR_SCX;
	Y = (CR_SCY + L) & 0xff;
	S = X >> 3;
	T = Y >> 3;
	U = X & 7;
	V = Y & 7;


	if (CR_WY>L || /*CR_WY<0 ||*/ CR_WY>143 || WX<-7 || WX>159 || !(CR_LCDC&0x20))
		WX = 160;

	WT = (L - CR_WY) >> 3;
	WV = (L - CR_WY) & 7;


	gbc_tilebuf();

//	if (!(CR_LCDC & 0x01)) memset(BUF, 0, 40);
//	else
	gbc_bg_scan();
	gbc_wnd_scan();
	if (NS) {
		gbc_bg_scan_pri();
		gbc_wnd_scan_pri();
	}

//	if ((CR_LCDC & 0x20)) wnd_scan();

	gbc_spr_enum();
	gbc_spr_scan();

	 if(sys_ipod_is_color()) {
		if(LCDP->palfetch[curline][0]) {
			for(i=0;i<32;i++)
				if(LCDP->palfetch[curline][0]&(1<<i)) {
					updatepalette(i, curline);
					LCDP->palfetch[curline][0] &= ~(1<<i);
				}
		}

		if(LCDP->palfetch[curline][1]) {
			for(i=0;i<32;i++)
				if(LCDP->palfetch[curline][1]&(1<<i)) {
					updatepalette(32+i, curline);
					LCDP->palfetch[curline][1] &= ~(1<<i);
				}
		}

		for(i=0;i<160;i++)
			screen[curline*160 + i] = LCDP->pal2[CBUF[i]];
	}

	if(CR_LY==LCD_LAST_LINE) {
//		#ifdef USE_COP
//			plb = CR_BGP;
//		#endif
//		update_bgpal(plb);
		if(ANYDIRTY) gbc_updatepatpix();	// FIXME
		//updatepalette(i, -1); // FIXME

		//err_msg("blit");
		lcdll_blit(screen, BLITTER_FORMAT_GBC_PAL);
	}
}



void updatepalette(int i, int scanline)
{
	int c, r, g, b;
	// int y, u, v;
//	int rr, gg;

	if(scanline==-1) c = (LCDP->mainpal[i<<1] | ((int)LCDP->mainpal[(i<<1)|1] << 8)) & 0x7FFF;
	else c = (inb(&(LCDP->pals[scanline][i<<1])) | ((int)inb(&(LCDP->pals[scanline][(i<<1)|1])) << 8)) & 0x7FFF;

	r = (c & 0x001F) << 3;
	g = (c & 0x03E0) >> 2;
	b = (c & 0x7C00) >> 7;
	r |= (r >> 5);
	g |= (g >> 5);
	b |= (b >> 5);


	// Generate RGB codes
	// This needs to be byte-swapped for iPod Videos and some iPod colors, but this
	// is left to lcdll.c


	b = (b & 0x1f) << 11;
	r = (r & 0x1f) << 5;
	g = (g & 0x1f) << 0;

	PAL2[i] = b|r|g;

}



void gbc_pal_dirty()
{
	int i;

	for (i = 0; i < 64; i++)
		updatepalette(i, -1);
}
#endif
