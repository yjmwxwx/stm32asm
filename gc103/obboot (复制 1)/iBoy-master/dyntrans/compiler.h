#ifndef COMPILER_H_
#define COMPILER_H_

typedef void (*z80op_generator_fp)(int);
typedef void (*block_exec_fp)(void);

struct block {
	int z80_len;
	int z80bytes;
	int pc;
	int from_pc;
	int cycles;
	unsigned char const0; // constant flags
	unsigned char const1; // constant flags
	unsigned char pad1[2];  // dummy
	unsigned int *genp;
	unsigned int *startp;
	unsigned int *lastpatchp;
	unsigned int *lastskipp;
	unsigned char lastskipc;
	unsigned char pad2[3]; // dummy
	int	toofat;
	int ei_stop;
	int allow_patch;
	int spec;
};

struct stored_successor {
	int pc;
	block_exec_fp native_successor;
};

//extern struct stored_successor stored_successor;
//extern struct block cur_block;

extern block_exec_fp point_of_return;
extern block_exec_fp point_of_return_lu;
extern block_exec_fp patch_point_of_return;
extern block_exec_fp patch_spec_point_of_return;
extern block_exec_fp int_vec_table_template[];
extern block_exec_fp int_vec_table[];
extern block_exec_fp Anchor;

void ccmpl_hiram_reset();

int compile(int from_pc, block_exec_fp dest, int permanent);
void cmpl_init();
void cmpl_bailout(char *,...);
struct stored_successor *cmpl_patch(int pc, unsigned int *paddr, int cascade);
int cmpl_check_boffset(int offset);

void insert_skip(unsigned char cond);
void linkblock_begin(int);
void patchblock_begin();
void linkblock_end(int addr, int cascade);
void set_constflags(unsigned char af);
int cmpl_get_z80bytes();
int cmpl_get_z80len();
void flush_cache(void * start, void * end);

#define SPEC_JUMP       0x10
#define SPEC_JUMP_ROM1  0x20
#define SPEC_PATCH_BACK 0x40

#endif /*COMPILER_H_*/
