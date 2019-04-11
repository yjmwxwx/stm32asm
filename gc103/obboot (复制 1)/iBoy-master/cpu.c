#include <stdio.h>


#include "defs.h"
#include "regs.h"
#include "hw.h"
#include "cpu.h"
#include "mem.h"
#include "fastmem.h"
#include "cpuregs.h"
#include "cpucore.h"
#include "lcdc.h"

#ifdef USE_ASM
#include "asm.h"
#endif

#include "dyntrans/compiler_defs.h"
#include "dyntrans/cached_compiler.h"
#include "dyntrans/compiler.h"



extern struct cpu cpu;



int advance_all(int clen);
int cpu_emulate_one_block();

extern int cpu_emulate(int i);

extern block_exec_fp no_native;


void cpu_reset()
{
	cpu.speed = 0;
	cpu.halt = 0;
	cpu.div = 0;
	cpu.tim = 0;
	cpu.lcdc = 40;

	cpu.snd = 0;

	IME = 0;

	PC = 0x0100;
	SP = 0xFFFE;
	AF = 0x01B0;
	BC = 0x0013;
	DE = 0x00D8;
	HL = 0x014D;



	if (hw.cgb) A = 0x11;
}



inline void cpu_hw_interrupt(byte i, byte mask)
{
	byte oldif = R_IF;
	i &= 0x1F & mask;
	R_IF |= i & (hw.ilines ^ i);

	/* FIXME - is this correct? not sure the docs understand... */
	if ((R_IF & (R_IF ^ oldif) & R_IE) && cpu.ime) cpu.halt = 0;
	if ((i & (hw.ilines ^ i) & R_IE) && cpu.ime) cpu.halt = 0; // ACHTUNG war original AUSKOMMENTIERT
	//if ((i & R_IE) && cpu.ime) cpu.halt = 0; // ACHTUNG war original AUSKOMMENTIERT
	//cpu.halt = 0;

	hw.ilines &= ~mask;
	hw.ilines |= i;
}


inline void div_advance(int cnt)
{
	cpu.div += (cnt<<1);
	if (cpu.div >= 256)
	{
		R_DIV += (cpu.div >> 8);
		cpu.div &= 0xff;
	}
}

inline void timer_advance(int cnt)
{
	int unit, tima;

	if (!(R_TAC & 0x04)) return;

	unit = ((-R_TAC) & 3) << 1;
	cpu.tim += (cnt<<unit);

	if (cpu.tim >= 512)
	{
		tima = R_TIMA + (cpu.tim >> 9);
		cpu.tim &= 0x1ff;
		if (tima >= 256)
		{
			cpu_hw_interrupt(IF_TIMER, IF_TIMER);
			cpu_hw_interrupt(0, IF_TIMER);
		}
		while (tima >= 256)
			tima = tima - 256 + R_TMA;
		R_TIMA = tima;
	}
}

inline void lcdc_advance(int cnt)
{
	cpu.lcdc -= cnt;
	if (cpu.lcdc <= 0) lcdc_trans(); //FIXME: war original ein if statt while
}

inline void sound_advance(int cnt)
{
	cpu.snd += cnt;
}


inline void cpu_timers(int cnt)
{
	div_advance(cnt << cpu.speed);
	timer_advance(cnt << cpu.speed);
	lcdc_advance(cnt);
	sound_advance(cnt);
}



int advance_all(int clen) {
	#if USE_DEBUG
	if(clen>0) {
	#endif

		clen <<= 1;
		div_advance(clen);
		timer_advance(clen);
		clen >>= cpu.speed;
		lcdc_advance(clen);
		sound_advance(clen);

	#if USE_DEBUG
	} else {
		cpu.halt = 0;
		err_msg("clen <= 0", 300);
	}
	#endif
	return clen;
}


/* modifizierte version, nur einmal aufrufen! */
int cpu_idle(int i)
{
	int cnt, unit, max;

next_idle:
	max = i;
	//if (!(cpu.halt && IME)) return i;
	if (R_IF & R_IE) {	// 1.0.3
		cpu.halt = 0;
		return i;
	}


	/* Make sure we don't miss lcdc status events! */
	if ((R_IE & (IF_VBLANK | IF_STAT)) && (max > cpu.lcdc))
		max = cpu.lcdc;

	/* If timer interrupt cannot happen, this is very simple! */
	if (!((R_IE & IF_TIMER) && (R_TAC & 0x04)))
	{
		cpu_timers(max);
		i-=max;
		if(i > 0) goto next_idle; // mod
		return i;
	}

	/* Figure out when the next timer interrupt will happen */
	unit = ((-R_TAC) & 3) << 1;
	cnt = (511 - cpu.tim + (1<<unit)) >> unit;
	cnt += (255 - R_TIMA) << (9 - unit);

	if (max < cnt)
		cnt = max;

	cpu_timers(cnt);
	i-=cnt;
	if(i > 0) goto next_idle; // mod
	return i;
}
