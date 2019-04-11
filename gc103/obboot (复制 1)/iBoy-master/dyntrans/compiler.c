
#include <sys/mman.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"

#include "op_generators.h"
#include "compiler_defs.h"
#include "cached_compiler.h"

#include "../defs.h"
#include "../fastmem.h"
#include "../disas.h"

struct block cur_block;

byte godown_immediates[(MAX_BASIC_BLOCK_CYC+1)];
byte goup_alive[(MAX_BASIC_BLOCK_CYC+1)];

void linkblock_toofat();

void cmpl_dump()
{
	int i;
	printf("from_pc:%04x z80len:%d\n", cur_block.from_pc, cur_block.z80_len);
	for(i=0;i<sizeof(cur_block)/4;i++)
		printf("cur_block+0x%02x: 0x%08x\n", 4*i, ((int*)(&cur_block))[i]);
}


void cmpl_bailout(char *fmt, ...)
{
	va_list ap;
  	cmpl_dump();
	va_start(ap, fmt);
 	vdie(fmt, ap);
    va_end(ap);
}


int cmpl_check_boffset(int offset)
{
	if( (offset < (1<<23)) && (offset >= -(1<<23)) ) return offset;

	cmpl_bailout("compiler error: bad offset %08x\n", offset);
	return 0; // another warning
}


inline int cmpl_getcycles(int pc, byte op)
{
	if(op != 0xcb)
		return cycles_table[op];
	else {
		op = readb(pc);
		return cb_cycles_table[op];
	}
}


/*
 * discovers endop or toofat
 *
 * sets: cur_block_z80_len, cur_block.pc, toofat *
 * returns: cycles of z80 block
 */
int cmpl_godown()
{
	int cycles=0, op;
	int border=0xFFFF;
	cur_block.z80bytes = 0;


	if(cur_block.pc < 0x4000) {
		border = 0x4000;
	} else if(cur_block.pc < 0x8000) {
		border = 0x8000;
	}


	do {
		//debug_disassemble(cur_block.pc, 1);
		op = readb(cur_block.pc++);
		cycles += cmpl_getcycles(cur_block.pc, op);
		cur_block.pc += imm_ops[op];
		cur_block.z80bytes += imm_ops[op] + 1;
		godown_immediates[cur_block.z80_len++] = imm_ops[op];   // FIXME check opcnt
		if((cur_block.ei_stop || cur_block.pc >= (border-1) || cycles >= (MAX_BASIC_BLOCK_CYC-1)) && !end_ops[op]) {
			cur_block.toofat = 1;
			return cycles;
		}
		if(op == 0xfb) {
			cur_block.ei_stop = 1;  // EI
		}
	} while(!end_ops[op]);

	return cycles;
}

#define BR_STRAIGHT	0
#define BR_A_COND	2
#define BR_A_UNCOND	3
#define BR_R_COND	4
#define BR_R_UNCOND	5
#define BR_COMPUTED 6
#define BR_RESET 	7

const byte  branchtype[256] = {
//  	0 1 2 3  4 5 6 7  8 9 a b  c d e f
/*0*/	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
/*1*/	0,0,0,0, 0,0,0,0, 5,0,0,0, 0,0,0,0,
/*2*/	4,0,0,0, 0,0,0,0, 4,0,0,0, 0,0,0,0,
/*3*/	4,0,0,0, 0,0,0,0, 4,0,0,0, 0,0,0,0,

/*4*/	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
/*5*/	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
/*6*/	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
/*7*/	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,

/*8*/	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
/*9*/	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
/*a*/	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
/*b*/	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,

/*c*/	6,0,2,3, 2,0,0,7, 6,6,2,0, 2,3,0,7,
/*d*/	6,0,2,0, 2,0,0,7, 6,6,2,0, 2,0,0,7,
/*e*/	0,0,0,0, 0,0,0,7, 0,6,0,0, 0,0,0,7,
/*f*/	0,0,0,0, 0,0,0,7, 0,0,0,0, 0,0,0,7
};


/* new version of lookahead:
*
*	gets PC of the instruction that wants to know wich flags it should deliver
*	still doesn work
*/
byte cmpl_alive(int pc, byte unknown, int n, int include)
{
	int op, pc_a, pc_b, self_read, self_write, new_unknown;
	byte successor_flags;

	if(pc == 0) {	 //special case for instructions with just one successor (dummy)
		return 0x00; //no flags alive
	}

	if(n <= 0) {
		return unknown; // time is up, everything unknown might be alive
	}

	switch(branchtype[(op =readb(pc))]) {
		case BR_STRAIGHT:
				pc_a = pc + imm_ops[op]+1;
				pc_b = 0;
			break;
		break;

		case BR_A_UNCOND:
				pc_a = readw(pc+1);
				pc_b = 0;
		break;

		case BR_R_UNCOND:
				pc_a = pc + ((int)(signed char)READB(pc+1)) + 2;
				pc_b = 0;
		break;

		case BR_A_COND:
				pc_a = pc + imm_ops[op]+1;
				pc_b = readw(pc+1);
		break;

		case BR_R_COND:
				pc_a = pc + imm_ops[op]+1;
				pc_b = pc + ((int)(signed char)READB(pc+1)) + 2;
		break;

		default:
				return unknown; //fallback everything unknown is alive
		break;
	}

	//checking the range:
	if(pc < 0x4000) { // Rombank 0: only lookahead in rombank 0
		if(pc_a >= 0x4000)
			pc_a = 0;
		if(pc_b >= 0x4000)
			pc_b = 0;
	}
	else if(pc < 0x8000) {	// Rombank n: lookahead to all 0 and n
		if(pc_a >= 0x8000)
			pc_a = 0;
		if(pc_b >= 0x8000)
			pc_b = 0;

	}else if(pc >= 0x8000) { // outside main rom: no lookahead
		pc_a = pc_b = 0;
	}


	if(op == 0xcb) {
		self_read = cbrmask[readb(pc+1)];
		self_write = cbwmask[readb(pc+1)];
	}else{
		self_read = rmask[op];
		self_write = wmask[op];
	}

	if(include) {	//use flags from current opcode or just successors?
		new_unknown = unknown & ~(self_read | ~self_write);
	}else{
		new_unknown = unknown;
	}

	if(new_unknown){
		successor_flags = cmpl_alive(pc_a,new_unknown,n-1,1) | cmpl_alive(pc_b,new_unknown,n-1,1);
	}else{
		successor_flags = 0;
	}

	if(include) {
		return (unknown & self_read) | successor_flags;
	} else {
		return successor_flags;
	}
}


/*
 * sets: cur_block.pc, goup_alive
 */
void cmpl_goup()
{
	int len = cur_block.z80_len;
	byte op;

	#if USE_LIVENESS_LOOKAHEAD == 1
	goup_alive[len] = cmpl_alive(cur_block.pc-(godown_immediates[len-1]+1),0xf0,30,0);
	#else
	goup_alive[len] = 0xf0;
	#endif

	while(len>0) { // go through each z80 op
		cur_block.pc -= (godown_immediates[--len] + 1);
		op = readb(cur_block.pc);
		if(op!=0xcb) {
			goup_alive[len] = goup_alive[len+1] & wmask[op];
			if(USE_LIVENESS) goup_alive[len] |= rmask[op];
			else goup_alive[len] |= 0xf0;
		} else {
			op = readb(cur_block.pc+1);
			goup_alive[len] = goup_alive[len+1] & cbwmask[op];
			if(USE_LIVENESS) goup_alive[len] |= cbrmask[op];
			else goup_alive[len] |= 0xf0;
		}
	}
}



/*
 * Our Compiler is quite simple
 * returns: Number of arm words (32bit) generated
 */
int compile(int from_pc, block_exec_fp dest, int allow_patch)
{
	int i;
	byte op;

	#ifdef USE_DEBUG
	if(from_pc<0 || from_pc>0xffff || dest == 0) {
		cop_end();
		err_msg("to large PC", 1200);
		err_msg("cut and continue!", 1200);
		cop_begin();
		//cmpl_bailout("Bad Parameters pc:%0x, dest:%0x", from_pc, dest);
		from_pc &= 0xffff;
	}
	#endif

/*	cur_block.z80_len=0;
	cur_block.const0 = 0x00; // no constant flags at begin of block
	cur_block.const1 = 0x00; // no constant flags at begin of block
	cur_block.toofat = 0;
	cur_block.lastskipp = 0;
	cur_block.lastpatchp = 0;
	cur_block.lastskipc = 0;*/

	memset(&cur_block, 0, sizeof(cur_block));

	cur_block.startp = (unsigned int *) dest;
	cur_block.allow_patch = allow_patch;
	cur_block.genp = (unsigned int *) dest;
	cur_block.from_pc = cur_block.pc = from_pc;


	/* go forward */
	cur_block.cycles = cmpl_godown();

	/* and reverse */
	cmpl_goup();



	for(i=0; i<cur_block.z80_len; i++) { // go through each z80 op
		op = readb(cur_block.pc);
		op_generators[op](goup_alive[i+1]);  /* attention: liveness-offset-shift */
		cur_block.pc += (1 + imm_ops[op]);
	}

	if(cur_block.toofat)
		linkblock_toofat();

	#ifdef PORTABLE
		flush_cache(dest, cur_block.genp);		//FIXME: this should flush the cache
	#endif

	return (unsigned int)cur_block.genp-(unsigned int)dest;
}


/**************************** Link-Blocks **************************/

void linkblock_begin(int delta_cyc)
{
	*cur_block.genp++ = PM_SUB_IMM(COND_AL,1,10,10,cur_block.cycles+delta_cyc);
}

void patchblock_begin()
{
	cur_block.lastpatchp = cur_block.genp;
}

void spec_patchblock_begin()
{
	cur_block.lastpatchp = cur_block.genp;
	cur_block.spec = 1;
}

void insert_skip(unsigned char cond)
{
	cur_block.lastskipp = cur_block.genp++;
	cur_block.lastskipc = cond;
}

void linkblock_toofat()
{
	set_constflags(goup_alive[cur_block.z80_len]); //FIXME: all flags alive?
	linkblock_begin(0);
	patchblock_begin();
	linkblock_end(cur_block.pc, USE_CASCADING);
}

void linkblock_end(int addr, int cascade)
{
	int spec, skip_crc=0;

	if(addr<-1 || addr > 0xffff) {
		#ifdef USE_DEBUG
		cop_end();
		err_msg("linkblock PC large", 200);
		err_msg("cut and continue!", 200);
		cop_begin();
		#endif
		addr &= 0xffff;
	}


	#if USE_LOOP_DETECTION == 1
	if((addr == cur_block.from_pc) && !cur_block.ei_stop) {		// loop detect
		if(cascade) {
			*cur_block.genp =
			PM_BRA(COND_GT,0,cmpl_check_boffset((unsigned int)(cur_block.startp)-(unsigned int)(cur_block.genp))/4-2);
			cur_block.genp++;
		}
		*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&point_of_return)-(int)(cur_block.genp))/4-2 );
		cur_block.genp++;
		*cur_block.genp++ = cur_block.from_pc;		// here will come pc FIXME: additional data?
		*cur_block.genp++ = (unsigned int) cur_block.startp;
	} else
	#endif

	if(
		USE_PATCHING			&&
		cur_block.allow_patch	&&
		addr != LBADDR_UNKNOWN	&&
		(0
	//#if USE_PATCH_ROM0_TO_ROM0 == 1
			|| (addr < 0x4000)
	//#endif

	#if USE_PATCH_ROMN_TO_ALLROM == 1
			|| (cur_block.from_pc>=0x4000 && cur_block.from_pc<0x8000
										&& addr < 0x8000)
	#endif

		)
	) {
		// Prepare patching

		#ifdef USE_DEBUG
		if(!cur_block.lastpatchp)
			cmpl_bailout("Patchblock without pointer");
		#endif

		*cur_block.genp++ = PM_MOV_IMM(COND_AL,0,2, (!!cascade)  && (!cur_block.ei_stop));
		*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&patch_point_of_return)-(int)(cur_block.genp))/4-2 );
		cur_block.genp++;
		*cur_block.genp++ = addr;
		*cur_block.genp++ = (unsigned int) cur_block.lastpatchp; // native successor misusage

		#ifdef USE_DEBUG
		if(cur_block.genp-cur_block.lastpatchp>PATCH_BLOCK_SIZE)
			cmpl_bailout("Patchblock overflow");
		#endif
	} else {
		if(addr != LBADDR_UNKNOWN) {
			if(addr >=0xFF80) { // HIRAM
				if(cascade && !cur_block.ei_stop) {
					*cur_block.genp=PM_BRA(COND_GT,0, cmpl_check_boffset((unsigned int)(hiram_block[addr&0x7F].field)-(unsigned int)(cur_block.genp))/4-2);
					*cur_block.genp++;
				}
				//skip_crc = hiram_compliled[(cur_block.from_pc>>5)&0x03] & (1 << (cur_block.from_pc & 0x1F));
				*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&point_of_return)-(int)(cur_block.genp))/4-2 );
				cur_block.genp++;
				*cur_block.genp++ = addr;		// here will come pc FIXME: additional data?
				*cur_block.genp++ = (unsigned int) &hiram_block[addr&0x7F].field[skip_crc];

			} else {
				*cur_block.genp++ = PM_MOV_IMM(COND_AL,0,1, addr&0xff);
				*cur_block.genp++ = PM_ORR_IMM(COND_AL,0,1,1, IMM_ROTL(((addr>>8)&0xff), 4) );

				#if USE_TEMP_HASHING == 1
				//TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST
				if(addr > 0x8000 && (addr < 0xFF80)&& cascade && !cur_block.ei_stop) {
					*cur_block.genp=PM_BRA(COND_GT,0, cmpl_check_boffset((unsigned int)(temp_block[addr&TEMP_HASH_MASK].field)-(unsigned int)(cur_block.genp))/4-2);
					*cur_block.genp++;
				}

				//TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST
				#endif
				*cur_block.genp++ = M_ADD_IMM(15,11,IMM_ROTL( (((unsigned char)(&point_of_return_lu-&Anchor))), 1 ));
			}
		} else if (USE_SPEC_JUMP == 1 && USE_PATCHING && cur_block.allow_patch /*&& cascade != 3*/ && (!cur_block.ei_stop)) { //FIXME
			spec = SPEC_JUMP;
			if(cur_block.from_pc >= 0x4000 && cur_block.from_pc < 0x8000)
			spec |= SPEC_JUMP_ROM1;
			//TEST2 TEST2 TEST2 TEST2 TEST2 TEST2 TEST2 TEST2 TEST2 TEST2
			spec_patchblock_begin();
			*cur_block.genp++ = PM_MOV_IMM(COND_AL,0,2, 1 | spec); // mark as unknown

			*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&patch_spec_point_of_return)-(int)(cur_block.genp))/4-2 );
			cur_block.genp++;
			*cur_block.genp++ = addr; // addr = -1 at this time
			*cur_block.genp++ = (unsigned int) cur_block.lastpatchp; // native successor misusage
			//TEST2 TEST2 TEST2 TEST2 TEST2 TEST2 TEST2 TEST2 TEST2 TEST2
		}else{
			*cur_block.genp++ = M_ADD_IMM(15,11,IMM_ROTL( (((unsigned char)(&point_of_return_lu-&Anchor))), 1 ));
		}
	}

	if(cur_block.lastpatchp) {
		if(cur_block.spec){
			cur_block.genp = cur_block.lastpatchp + SPEC_PATCH_BLOCK_SIZE;
			cur_block.spec = 0;
		}
		else{
			cur_block.genp = cur_block.lastpatchp + PATCH_BLOCK_SIZE;
		}
		cur_block.lastpatchp = 0;
	}

	if(cur_block.lastskipp) {
		*cur_block.lastskipp = PM_BRA(cur_block.lastskipc, 0, ((cur_block.genp-cur_block.lastskipp)-2));
		cur_block.lastskipp = 0;
	}
}


void set_constflags(unsigned char af)
{
	if(cur_block.const0 & af) {
		*cur_block.genp++ = M_AND_IMM(4, 4, (~cur_block.const0)&0xff);
	}
	if(cur_block.const1 & af) {
		*cur_block.genp++ = M_ORR_IMM(4, 4, (cur_block.const1)&0xff);
	}
}

int cmpl_get_z80len()
{
	return cur_block.z80_len;
}

int cmpl_get_z80bytes()
{
	return cur_block.z80bytes;
}
