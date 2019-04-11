#define MESS_START		500
#define MESS_END		(1000 + MESS_START)


#include <stdio.h>

#include "emu.h"
#include "defs.h"
#include "regs.h"
#include "hw.h"
#include "cpu.h"
#include "mem.h"
#include "input.h"
#include "rtc.h"
#include "sound.h"
#include "save.h"
#include "cop.h"
#include "cpuregs.h"
#include "lcd.h"

#include "dyntrans/cached_compiler.h"


//static int framelen = 16743;
int framecount = 0;
int emu_running = 1;
int show_fps = 0;

FILE *debug_file = NULL;



void emu_reload() {	emu_running = 0; }


void emu_init(char *save)
{
	FILE *state = NULL;

	if(save && *save) {
		state = fopen(save, "r");
		if(state) {
			loadstate(state);
			fclose(state);
		}
	}
}

/*
 * emu_reset is called to initialize the state of the emulated
 * system. It should set cpu registers, hardware registers, etc. to
 * their appropriate values at powerup time.
 */

void emu_reset()
{
	hw_reset();
	lcd_reset();
	cpu_reset();
	mbc_reset();
	sound_reset();
	ccmpl_reset();
	//cop_stop_draw();
	
#ifdef DEBUG
	debug_file = fopen("/out", "w+");
	if(!debug_file) die("no debugging possible... I better die");
	if(lcd_file) close(lcd_file);
#endif
}

int emu_step()
{
	int delta;
	delta = -cpu_emulate(cpu.lcdc);
	return delta;
}

/*void emu_step()
{
	cpu_emulate(cpu.lcdc);
}*/

/* This mess needs to be moved to another module; it's just here to
 * make things work in the mean time. */


int i_debug;


extern block_exec_fp free_block;
extern block_exec_fp bin_blocks;

void emu_run()
{
	int delta; // too much

#ifdef MEASUREMENT
	int cur_frame=0; //mitzahlen
	int time_hs;
	void *timer;
#endif

	delta = 0;			
	lcd_begin();
	//cop_begin();

	while(emu_running)
	{

		#ifdef MEASUREMENT
		if(cur_frame==MESS_START) {
			cop_end();
			err_msg("Measuring", 100);
			err_msg("Measuring.", 100);
			err_msg("Measuring..", 100);
			err_msg("Measuring...", 100);
			cop_begin();
			timer = sys_timer();
		}
		if(cur_frame==MESS_END) {
			time_hs = sys_elapsed(timer)/10000;
			emu_running = 0;
		}
		cur_frame++;
		#endif


		#ifdef USE_DEBUG
		if(delta >= 2280)
			printf("too much %6d\n", delta);
		else if(delta < 0)
			printf("delta is negative");
		#endif
		
	
		delta = -cpu_emulate(2280 - delta);

		while (R_LY > 0 && R_LY < 144) {
			if(cpu.lcdc > delta){
				delta = -cpu_emulate(cpu.lcdc-delta);
			}
			else{
				delta -= cpu.lcdc;
			}
		}

		rtc_tick();
		sound_mix();
		pcm_submit();
		kb_poll();
	
		if (!(R_LCDC & 0x80))
			delta = -cpu_emulate(32832 - delta);

		// wait for next frame
		while (R_LY > 0)  {
			if(cpu.lcdc > delta){
				delta = -cpu_emulate(cpu.lcdc-delta);
			}
			else{
				delta -= cpu.lcdc;
			}
		}
		
		/*cpu_emulate(2280-delta);

		while (R_LY > 0 && R_LY < 144)
				delta = -cpu_emulate(cpu.lcdc);

		rtc_tick();
		sound_mix();
		pcm_submit();
		kb_poll();
	

		if (!(R_LCDC & 0x80))
			delta = -cpu_emulate(32832);

		// wait for next frame
		while (R_LY > 0)
			delta = -cpu_emulate(cpu.lcdc);*/

	}


#ifdef MEASUREMENT
		cop_end();
		err_msg("%d hs", 3000, time_hs);
		enter_menu();
#endif
}
