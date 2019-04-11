#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#include <stdio.h>


#include "../defs.h"
#include "../input.h"
#include "../hw.h"
#include "../lcd.h"

#include "lcdll.h"
#include "nix.h"

#include "config.h"
#include "kb.h"


pSense_kb sense_kb = 0;


// the following arrays define the default keymapping


int push_map[5] = {
	PAD_A,						//x01 = IPOD_CENTER
	PAD_B,						//x02 = IPOD_RIGHT
	PAD_B,						//x04 = IPOD_LEFT
	PAD_B,						//x08 = IPOD_DOWN
	PAD_B,						//x10 = IPOD_UP
};


int push_combo[32];
int spec_combo[32];

int touch_map[8] = {
	PAD_UP,
	PAD_A,
	PAD_RIGHT,
	PAD_START,
	PAD_DOWN,
	PAD_SELECT,
	PAD_LEFT,
	PAD_B
};


void kb_combo_reset()
{
	int i;
	for(i=0; i<32; i++)
		spec_combo[i]=0;
}


void kb_init()
{
	hw_info info;

	sys_ipod_hw_info(&info);

	switch(info.version) {
		case 0x03: /* 3g */
			//touch_map[1] = PAD_DOWN;
			sense_kb = sense_kb_3g;
			break;
		case 0x04: /* iPod Mini 1G */
			//touch_map[1] = PAD_DOWN;
			sense_kb = sense_kb_mini;
			break;
		default:  /* 4g and newer */
			sense_kb = sense_kb_std;
	}
}


void kb_setup(int reset)
{
	int i, j, bit, h;

	// build a map for all possible combinations
	for(i=0; i<32; i++) {
			h = 1;
			push_combo[i] = 0;
			for(bit=0;bit<5;bit++,h<<=1)
				if(i&h) push_combo[i] |= push_map[bit];

		for(j=0; j<32; j++){
			if(spec_combo[j&i] != 0) {
				h = 1;
				for(bit=0;bit<5;bit++,h<<=1){
					if(j&h)
						push_combo[i] &= ~push_map[bit];
				}
				push_combo[i] |= spec_combo[i&j];
			}
		}
	}

	//x01 = IPOD_CENTER
	//x02 = IPOD_RIGHT
	//x04 = IPOD_LEFT
	//x08 = IPOD_DOWN
	//x10 = IPOD_UP

}


void kb_close()
{
#ifdef KB_PORTABLE
	reset_input_mode();
#endif
}


void sense_kb_3g(byte *press, byte *touch)
{
	static int skip, rskip = 0, lskip = 0;
	*touch = 0xff;

	if(!(inb(0xcf000030)&0x20)) {
		*press = IPOD_HOLD;
		return;
	}

	*press = (~inb(0xcf000030)) & 0x1f;

	//convert bits to simulate a 4g keyboard... to be tested
	*press = (*press&0x10) | ((*press>>1)&0x05) | ((*press<<1)&0x0A);


   switch(sys_getkey())
    {
        case 'l':
            if(lskip == 'e') { *touch = 0; }
            else if(lskip == 10) { lskip = 'e';}
            else { lskip++; }
            break;
        case 'r':
            if(rskip == 'e') { *touch = 12; }
            else if(rskip == 10) { rskip = 'e'; }
            else { rskip++; }
            break;
        case -1:
            if(skip == 10) { lskip = rskip = skip = 0; }
            else { skip++; }
            break;
    }
}


void sense_kb_mini(byte *press, byte *touch)
{
	static int skip, rskip = 0, lskip = 0;
	*touch = 0xff;

	if(!(inl(0x6000d030)&0x20)) {  // but 0x20 is used for menu and hold !?
		*press = IPOD_HOLD;
		return;
	}

	*press = (~inb(0x6000d030)) & 0x1f;

	//convert bits to simulate a 4g keyboard... to be tested
	*press = (*press&0x01) | ((*press>>2)&0x06) | ((*press<<3)&0x10) | ((*press<<1)&0x08);


   switch(sys_getkey())
    {
        case 'l':
            if(lskip == 'e') { *touch = 0; }
            else if(lskip == 10) { lskip = 'e';}
            else { lskip++; }
            break;
        case 'r':
            if(rskip == 'e') { *touch = 12; }
            else if(rskip == 10) { rskip = 'e'; }
            else { rskip++; }
            break;
        case -1:
            if(skip == 10) { lskip = rskip = skip = 0; }
            else { skip++; }
            break;
    }
}


void sense_kb_std(byte *press, byte *touch)
{
	int in, st;

	*touch = 0xff;

	if(!(inl(0x6000d030)&0x20)) {
		*press = IPOD_HOLD;
		return;
	}


	in = inl(0x7000C140);

	st = ((in & 0xff000000)>>24);
	//if(st | 0x80) { ??
		*press = (in & 0x00001F00) >> 8;

	if(*press == 0x18) *press = IPOD_HOLD; //ducky emulate hold


	//}
	if(st == 0xc0) *touch = (in & 0x007F0000 ) >> 16;

}


int kb_gethold()
{
	byte press, touch;
	sense_kb(&press, &touch);
	return press==IPOD_HOLD;
}


#ifndef KB_PORTABLE

// FIXME: Do we really need my kb_getch?
int kb_getch()
{
	static byte oldkey=0, fastrepeat=0;
	byte newkey, cnt;
	byte press, touch;

begin_sc:
	sense_kb(&press, &touch);
	newkey = press;

	if(newkey != oldkey) {
		fastrepeat = 0;
	} else {
		if (!fastrepeat) cnt = 20;
		else cnt = 4;
		while(cnt) {
			sys_sleep(1000);
			cnt--;
			sense_kb(&press, &touch);
			if(newkey != press) goto begin_sc;
		}
		fastrepeat = 1;
	}

	oldkey = newkey;

	if(newkey==0) {
		goto begin_sc;
		sys_sleep(1000);
	}

	switch(newkey) {
		case IPOD_UP:	  return 'm';
		case IPOD_DOWN:	  return 'd';
		case IPOD_LEFT:	  return 'l';
		case IPOD_RIGHT:  return 'r';
		case IPOD_CENTER: return '\n';
		case IPOD_HOLD:   return 'h';
	}

	return 0; // never reached ?
}
#endif


void enter_menu();


void kb_poll()
{
	byte touch, button;

	pad_release(0xFF); // release ALL

	sense_kb(&button, &touch);

	if(button) {
		if(button!=IPOD_HOLD) pad_press(push_combo[button]);
		else enter_menu();
	}

	if(touch!=0xff) { 	// touched
		touch+=6;
		touch/=12;
		if(touch>7) touch=0;
		pad_press(touch_map[touch]);
	}
}
