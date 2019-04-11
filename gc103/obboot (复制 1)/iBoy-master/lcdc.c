

#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/soundcard.h>


#include "lcdc.h"
#include "defs.h"
#include "hw.h"
#include "cpu.h"
#include "regs.h"
#include "cop.h"
#include "lcd.h"

#include "sys/lcdll.h"


#define C (cpu.lcdc)


/*
 * stat_trigger updates the STAT interrupt line to reflect whether any
 * of the conditions set to be tested (by bits 3-6 of R_STAT) are met.
 * This function should be called whenever any of the following occur:
 * 1) LY or LYC changes.
 * 2) A state transition affects the low 2 bits of R_STAT (see below).
 * 3) The program writes to the upper bits of R_STAT.
 * stat_trigger also updates bit 2 of R_STAT to reflect whether LY=LYC.
 */

void stat_trigger()
{
	static const int condbits[4] = { 0x08, 0x30, 0x20, 0x00 };
	int flag = 0;

	if ((R_LY < 0x91) && (R_LY == R_LYC))
	{
		R_STAT |= 0x04;
		if (R_STAT & 0x40) flag = IF_STAT;
	}
	else R_STAT &= ~0x04;

	if (R_STAT & condbits[R_STAT&3]) flag = IF_STAT;

	if (!(R_LCDC & 0x80)) flag = 0;

	hw_interrupt(flag, IF_STAT);
}


/*
 * stat_change is called when a transition results in a change to the
 * LCD STAT condition (the low 2 bits of R_STAT).  It raises or lowers
 * the VBLANK interrupt line appropriately and calls stat_trigger to
 * update the STAT interrupt line.
 */

void stat_change(int stat)
{
	stat &= 3;
	R_STAT = (R_STAT & 0x7C) | stat;

	if (stat != 1) hw_interrupt(0, IF_VBLANK);
	/* hw_interrupt((stat == 1) ? IF_VBLANK : 0, IF_VBLANK); */
	stat_trigger();
}


void lcdc_change(byte b)
{
	byte old = R_LCDC;

	R_LCDC = b;
	if ((R_LCDC ^ old) & 0x80) /* lcd on/off change */
	{
		R_LY = 0;
		stat_change(2);
		C = 40;
		lcd_begin();
	}
}

#ifdef USE_COP
extern int dsp;
audio_buf_info buf_info_tim;


inline void copy_hiramregs()
{

	hiramcopy->cR_OBP0 = R_OBP0;
	hiramcopy->cR_OBP1 = R_OBP1;

	if(R_LY == LINE_NUMBER_OF_BACKGOUND_PAL)
		hiramcopy->cR_BGP = R_BGP;

//	hiramcopy->cR_WY = R_WY;
	//hiramcopy->cR_LY = R_LY;
	hiramcopy->cR_WX[R_LY] = R_WX;
	hiramcopy->cR_SCX[R_LY] = R_SCX;
	hiramcopy->cR_SCY[R_LY] = R_SCY;
	hiramcopy->cR_LCDC[R_LY] = R_LCDC;

}
#endif

void lcdc_trans()
{
	if (!(R_LCDC & 0x80))
	{
		while (C <= 0)
		{
			switch ((byte)(R_STAT & 3))
			{
			case 0:
			case 1:
				stat_change(2);
				C += 40;
				break;
			case 2:
				stat_change(3);
				C += 86;
				break;
			case 3:
				stat_change(0);
				if (hw.hdma & 0x80)
					hw_hdma();
				else
					C += 102;
				break;
			}
			return;
		}
	}
	while (C <= 0)
	{
		switch ((byte)(R_STAT & 3))
		{
		case 1:
			if (!(hw.ilines & IF_VBLANK))
			{
				C += 218;
				hw_interrupt(IF_VBLANK, IF_VBLANK);
				break;
			}
			if (R_LY == 0)
			{
				lcd_begin();

				stat_change(2);
				C += 40;
				break;
			}
			else if (R_LY < 152)
				C += 228;
			else if (R_LY == 152)
				C += 28;
			else
			{
				R_LY = -1;
				C += 200;
			}
			R_LY++;
			stat_trigger();
			break;
		case 2:
#ifndef USE_COP
	#ifndef OLD_KERNEL
			if(hw.cgb)
			lcd_gbc_refreshline();
			else
	#endif
			lcd_refreshline();
#else


//			while ((inl(IBOY_COP_STATUS) & IBOY_COP_LINE_REQ)!=0){
//				break; //DONT WAIT FOR COP-GRAPHICs

//				if(R_LY > LCD_LAST_LINE)
//					goto endgraph;
//				ioctl(dsp, SNDCTL_DSP_GETOSPACE, &buf_info_tim);
//				if(((64*1024+256)-buf_info_tim.bytes)<(32*(127-R_LY)+4096)) break;
//			}


			//if((inl(IBOY_COP_STATUS) & IBOY_COP_LINE_REQ)==0) { //FIXME: autointerlace
			if(R_LY <= LCD_LAST_LINE){
				copy_hiramregs();
				//outl(inl(IBOY_COP_STATUS) | IBOY_COP_LINE_REQ, IBOY_COP_STATUS); // set to 1
			}

			//ALWAYS READY !!!!
			//outl(inl(IBOY_COP_STATUS) | IBOY_COP_LINE_REQ, IBOY_COP_STATUS); // set to 1

//endgraph:

#endif
			stat_change(3);
			C += 86;
			break;
		case 3:
			stat_change(0);
			if (hw.hdma & 0x80)
				hw_hdma();
			/* FIXME -- how much of the hblank does hdma use?? */
			/* else */
			C += 102;
			break;
		case 0:
			if (++R_LY >= 144)
			{
				if (cpu.halt)
				{
					hw_interrupt(IF_VBLANK, IF_VBLANK);
					C += 228;
				}
				else C += 10;
				stat_change(1);
				break;
			}
			stat_change(2);
			C += 40;
			break;
		}
	}
}
