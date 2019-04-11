

#ifndef __CPU_H__
#define __CPU_H__



#include "defs.h"


union reg
{
	byte b[2][2];
	word w[2];
	un32 d; /* padding for alignment, carry */
};

struct cpu
{
	union reg af, bc, de, hl, sp, pc;
	int ime, dummy;
	int speed;
	int halt;
	int div, tim;
	int lcdc;
	int snd;
};

extern struct cpu cpu;

void cpu_reset();
extern int cpu_emulate(int cycles);
int cpu_interrupt_handler(void);
void lcdc_advance(int);
#endif
