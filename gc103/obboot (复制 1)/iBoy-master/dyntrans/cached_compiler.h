#ifndef HASH_H_
#define HASH_H_

//typedef int (*native_block)();
#include "compiler.h"
#include "compiler_defs.h"

extern struct mbc mbc;

extern void int_0x40();
extern void int_0x48();
extern void int_0x50();
extern void int_0x58();
extern void int_0x60();

extern unsigned int hiram_dirty_mask[];
//extern unsigned int hiram_compliled[];

block_exec_fp pc_to_native(int pc);
void ccmpl_alloc_rbn();
void ccmpl_clear_all();
int ccmpl_get_reseted();
void ccmpl_reset();
void ccmpl_clear_ram();


#if USE_TEMP_HASHING == 1
	struct temp_block{
		int from_pc;
		unsigned int bytes;
		unsigned int crc;
		unsigned int field[MAX_HASH_BLOCKSIZE];
	};

	extern struct temp_block temp_block[TEMP_HASH_SIZE];

#endif

	struct hiram_block{
			unsigned int pc; //FIXME: needed?
			unsigned int field[MAX_HASH_BLOCKSIZE];
	};
	extern struct hiram_block hiram_block[128];

#endif /*HASH_H_*/
