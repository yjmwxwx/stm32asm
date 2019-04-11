#ifndef COMPILER_DEFS_H_
#define COMPILER_DEFS_H_

#include "../defs.h"
#include "compiler.h"
extern struct block cur_block;

/************************** compiler parameters *****************************/
#define MAX_BASIC_BLOCK_CYC 32	/*maximum cycles to add another instruction */
#define CASH_SIZE (1024 * 256)
#define USE_LIVENESS 1
#define USE_PATCHING 1
#define USE_PATCH_ROM0_TO_ROM0 1
#define USE_PATCH_ROMN_TO_ALLROM 1
#define USE_LOOP_DETECTION 1
#define USE_CASCADING 1
//#define USE_DEBUG 1
#define USE_HIRAM_CACHE 1
#define USE_HIRAM_PATCH 1
#define USE_HIRAM_CASCADE 1
#define USE_LIVENESS_LOOKAHEAD 0
#define USE_TEMP_HASHING 1
#define TEMP_HASH_SIZE 512 /*MUST BE A POWER OF 2*/
#define TEMP_HASH_MASK (TEMP_HASH_SIZE-1)
#define USE_TEMP_PATCH 1
#define MAX_HASH_BLOCKSIZE (32*19)
#define USE_SPEC_JUMP 0
#define PATCH_BLOCK_SIZE	4	/*FIXME 5 should be enough, 4 with branchlink?*/
#define SPEC_PATCH_BLOCK_SIZE	15 /*8*/


/***************************************************************************/

#define MAX_ARM_PER_CYC 20

#define IMEo (-64)
#define IMAo (-60)
#define SPDo (-56)
#define HALTo (-52)

#define ALIVE(x) 	(af & (x))
#define IS_CONSTANT0(x)	(cur_block.const0 & (x))
#define IS_CONSTANT1(x) (cur_block.const1 & (x))
#define IS_CONSTANT(x)  (IS_CONSTANT1(x) | IS_CONSTANT0(x))

#define LBADDR_UNKNOWN -1


extern z80op_generator_fp cbop_generators[256];
extern const byte wmask[256];
extern const byte rmask[256];
extern const byte cbwmask[256];
extern const byte cbrmask[256];
extern const byte imm_ops[256];
extern const byte end_ops[256];
extern const byte cycles_table[256];
extern const byte cb_cycles_table[256];


/* macros to create code ******************************************************/

/* the condition field */
#define COND_EQ 0x0  /* Equal        Z set   */
#define COND_NE 0x1  /* Not equal    Z clear */
#define COND_CS 0x2  /* Carry set    C set   */
#define COND_CC 0x3  /* Carry clear  C clear */
#define COND_MI 0x4  /* Negative     N set   */
#define COND_PL 0x5  /* Positive     N clear */
#define COND_VS 0x6  /* Overflow     V set   */
#define COND_VC 0x7  /* No overflow  V clear */
#define COND_HI 0x8  /* Unsigned higher      */
#define COND_LS 0x9  /* Unsigned lower, same */
#define COND_GE 0xA  /* Sig. greater, equal  */
#define COND_LT 0xB  /* Sig. less than       */
#define COND_GT 0xC  /* Sig. greater than    */
#define COND_LE 0xD  /* Sig. less, equal     */
#define COND_AL 0xE  /* Always               */
#define CONDNV  0xF  /* Special (see A3-5)   */
#define UNCOND COND_AL

/* data processing operation: M_DAT
   cond ... conditional execution
   op ..... opcode
   d ...... destination reg
   n ...... source reg
   S ...... update condition codes
   I ...... switch to immediate mode
   shift .. shifter operand
*/
#define M_DAT(cond,op,d,n,S,I,shift) \
	 (((cond) << 28) | ((op) << 21) | ((d) << 12) | ((n) << 16) | \
					((I) << 25) | ((S) << 20)| ((shift) & 0x00000fff))

/* load and store instruction: M_MEM
   cond ... conditional execution
   L ...... load (L=1) or store (L=0)
   B ...... unsigned byte (B=1) or word (B=0)
   d ...... destination reg
   n ...... base reg for addressing
   adr .... addressing mode specific
*/

#define M_MEM(cond,L,B,d,n,adr,I,P,U,W) \
	*(mcodeptr++) = (((cond) << 28) | (1 << 26) | ((L) << 20) | ((B) << 22) | ((d) << 12) | ((n) << 16) | \
					((adr) & 0x0fff) | ((I) << 25) | ((P) << 24) | ((U) << 23) | ((W) << 21))

#define PM_MEM(cond,L,B,d, n,adr, I,P,U,W) \
	(((cond) << 28) | (1 << 26) | ((L) << 20) | ((B) << 22) | ((d) << 12) | ((n) << 16) | \
	((adr>=0)?((adr) & 0x0fff):((-adr) & 0x0fff)) | ((I) << 25) | ((P) << 24) | ((!(adr<0)) << 23) | ((W) << 21))

/* load and store instruction: M_MEM2
   cond ... conditional execution
   L ...... load (L=1) or store (L=0)
   H ...... halfword (H=1) or signed byte (H=0)
   S ...... signed (S=1) or unsigned (S=0) halfword
   d ...... destination reg
   n ...... base reg for addressing
   adr .... addressing mode specific
*/



#define M_MEM2(cond,L,H,S,d,n,adr,I,P,U,W) \
	*(mcodeptr++) = (((cond) << 28) | (1 << 22) | (0x9 << 4) | ((L) << 20) | ((H) << 5) | ((S) << 6) | ((d) << 12) | ((n) << 16) | \
					(((adr>=0)?(adr):(-adr)) & 0x0f) | ((((adr>=0)?(adr):(-adr)) & 0xf0) << (8-4)) | ((I) << 22) | ((P) << 24) | ((!(adr<0)) << 23) | ((W) << 21))

/* load and store multiple instruction: M_MEM_MULTI
   cond ... conditional execution
   L ...... load (L=1) or store (L=0)
   S ...... special (see "The ARM ARM A3-21")
   regs ... register list
   n ...... base reg for addressing
*/
#define M_MEM_MULTI(cond,L,S,regs,n,P,U,W) \
	*(mcodeptr++) = (((cond) << 28) | (1 << 27) | ((L) << 20) | ((S) << 22) | ((n) << 16) | \
					((regs) & 0xffff) | ((P) << 24) | ((U) << 23) | ((W) << 21))

/* branch and branch with link: M_BRA
   cond ... conditional execution
   L ...... branch with link (L=1)
   offset . 24bit offset
*/
#define M_BRA(cond,L,offset) \
	(((cond) << 28) | (0x5 << 25) | ((L) << 24) | ((offset) & 0x00ffffff))

#define PM_BRA(cond, L, offset) M_BRA(cond, L, offset)

/* multiplies: M_MULT
   cond ... conditional execution
   d ...... destination register
   n, m ... source registers
   S ...... update conditional codes
   A ...... accumulate flag (enables third source)
   s ...... third source register
*/
#define M_MULT(cond,d,n,m,S,A,s) \
	*(mcodeptr++) = (((cond) << 28) | ((d) << 16) | ((n) << 8) | (m) | (0x09 << 4) | ((S) << 20) | ((A) << 21) | ((s) << 12))

/* no operation (mov r0,r0): M_NOP */
#define M_NOP \
	*(mcodeptr++) = (0xe1a00000)

/* software breakpoint (only v5 and above): M_BREAKPOINT */
#define M_BREAKPOINT(imm) \
	*(mcodeptr++) =  (0x0e12 << 20) | (0x07 << 4) | (((imm) & 0xfff0) << (8-4)) | ((imm) & 0x0f)

/* Floating-Point Coprocessor Data Operations: M_CPDO
   cond ... conditional execution
   op ..... opcode
   D ...... dyadic (D=0) or monadic (D=1) instruction
   Fd ..... destination float-register
   Fn ..... source float-register
   Fm ..... source float-register or immediate
*/
#define M_CPDO(cond,op,D,Fd,Fn,Fm) \
	*(mcodeptr++) = (((cond) << 28) | (0x0e << 24) | (1 << 8) | ((op) << 20) | ((D) << 15) | ((Fd) << 12) | ((Fn) << 16) | ((Fm) & 0x0f))

/* Floating-Point Coprocessor Data Transfer: M_CPDT
   cond ... conditional execution
   L ...... load (L=1) or store (L=0)
   Fd ..... destination float-register
   n ...... base reg for addressing
*/
#define M_CPDT(cond,L,T1,T0,Fd,n,off,P,U,W) \
	*(mcodeptr++) = (((cond) << 28) | (0x0c << 24) | (1 << 8) | ((L) << 20) | ((T1) << 22) | ((T0) << 15) | ((Fd) << 12) | ((n) << 16) | \
					((off) & 0xff) | ((P) << 24) | ((U) << 23) | ((W) << 21))

/* Floating-Point Coprocessor Register Transfer: M_CPRT
*/
#define M_CPRT(cond,L,d,Fn,Fm) \
	*(mcodeptr++) = (((cond) << 28) | (0x0e << 24) | (1 << 8) | (1 << 4) | ((L) << 20) | ((d) << 12) | ((Fn) << 16) | (Fm))

/* used to store values! */
#define DCD(val) \
	*(mcodeptr++) = val

/* used to directly access shifter; insert this as shifter operand! */
#define REG_LSL(reg, shift) ( (((shift) & 0x1f) << 7) | ((reg) & 0x0f) )
#define REG_LSR(reg, shift) ( (((shift) & 0x1f) << 7) | ((reg) & 0x0f) | (1 << 5) )
#define REG_ASR(reg, shift) ( (((shift) & 0x1f) << 7) | ((reg) & 0x0f) | (1 << 6) )
#define REG_ROR(reg, shift) ( (((shift) & 0x1f) << 7) | ((reg) & 0x0f) | (1 << 6)|(1 << 5))

#define REG_LSL_REG(reg, s) ( (((s) & 0x0f) << 8) | ((reg) & 0x0f) | (1 << 4) )
#define REG_LSR_REG(reg, s) ( (((s) & 0x0f) << 8) | ((reg) & 0x0f) | (1 << 4) | (1 << 5) )
#define REG_ASR_REG(reg, s) ( (((s) & 0x0f) << 8) | ((reg) & 0x0f) | (1 << 4) | (1 << 6) )

/* used to directly rotate immediate values; insert this as immediate! */
/* ATTENTION: this rotates the immediate right by (2 * rot) bits */
#define IMM_ROTR(imm, rot) ( ((imm) & 0xff) | (((rot) & 0x0f) << 8) )
#define IMM_ROTL(imm, rot) IMM_ROTR(imm, 16-(rot))

/* macros for all arm instructions ********************************************/

#define M_ADD(d,a,b)       M_DAT(UNCOND,0x04,d,a,0,0,b)         /* d = a +  b */
#define M_ADC(d,a,b)       M_DAT(UNCOND,0x05,d,a,0,0,b)         /* d = a +  b (with Carry) */
#define M_SUB(d,a,b)       M_DAT(UNCOND,0x02,d,a,0,0,b)         /* d = a -  b */
#define M_SBC(d,a,b)       M_DAT(UNCOND,0x06,d,a,0,0,b)         /* d = a -  b (with Carry) */
#define M_AND(d,a,b)       M_DAT(UNCOND,0x00,d,a,0,0,b)         /* d = a &  b */
#define M_ORR(d,a,b)       M_DAT(UNCOND,0x0c,d,a,0,0,b)         /* d = a |  b */
#define M_EOR(d,a,b)       M_DAT(UNCOND,0x01,d,a,0,0,b)         /* d = a ^  b */
#define M_TST(a,b)         M_DAT(UNCOND,0x08,0,a,1,0,b)         /* TST a &  b */
#define M_TEQ(a,b)         M_DAT(UNCOND,0x09,0,a,1,0,b)         /* TST a ^  b */
#define M_CMP(a,b)         M_DAT(UNCOND,0x0a,0,a,1,0,b)         /* TST a -  b */
#define M_MOV(d,b)         M_DAT(UNCOND,0x0d,d,0,0,0,b)         /* d =      b */
#define M_ADD_S(d,a,b)     M_DAT(UNCOND,0x04,d,a,1,0,b)         /* d = a +  b (update Flags) */
#define M_SUB_S(d,a,b)     M_DAT(UNCOND,0x02,d,a,1,0,b)         /* d = a -  b (update Flags) */
#define M_MOV_S(d,b)       M_DAT(UNCOND,0x0d,d,0,1,0,b)         /* d =      b (update Flags) */

#define PM_AND(cond,flags,d,s,t)	M_DAT(cond,0x00,d,s,flags,0,t)         /* d =      i */
#define PM_BIC(cond,flags,d,s,t)	M_DAT(cond,0x0e,d,s,flags,0,t)         /* d =      i */
#define PM_EOR(cond,flags,d,s,t)	M_DAT(cond,0x01,d,s,flags,0,t)         /* d =      i */
#define PM_SUB(cond,flags,d,s,t)	M_DAT(cond,0x02,d,s,flags,0,t)         /* d =      i */
#define PM_RSB(cond,flags,d,s,t)	M_DAT(cond,0x03,d,s,flags,0,t)         /* d =      i */
#define PM_ADD(cond,flags,d,s,t)	M_DAT(cond,0x04,d,s,flags,0,t)         /* d =      i */
#define PM_TST(cond,        s,t)	M_DAT(cond,0x08,0,s,1    ,0,t)         /* d =      i */
#define PM_CMP(cond,        s,t)	M_DAT(cond,0x0a,0,s,1    ,0,t)         /* d =      i */
#define PM_CMN(cond,        s,t)	M_DAT(cond,0x0b,0,s,1    ,0,t)         /* d =      i */

#define PM_ORR(cond,flags,d,s,t)	M_DAT(cond,0x0c,d,s,flags,0,t)         /* d =      i */
#define PM_MOV(cond,flags,d,t)		M_DAT(cond,0x0d,d,0,flags,0,t)         /* d =      i */



#define M_ADD_IMM(d,a,i)   M_DAT(UNCOND,0x04,d,a,0,1,i)         /* d = a +  i */
#define M_ADC_IMM(d,a,i)   M_DAT(UNCOND,0x05,d,a,0,1,i)         /* d = a +  i (with Carry) */
#define M_SUB_IMM(d,a,i)   M_DAT(UNCOND,0x02,d,a,0,1,i)         /* d = a -  i */
#define M_SBC_IMM(d,a,i)   M_DAT(UNCOND,0x06,d,a,0,1,i)         /* d = a -  i (with Carry) */
#define M_RSB_IMM(d,a,i)   M_DAT(UNCOND,0x03,d,a,0,1,i)         /* d = -a + i */
#define M_RSC_IMM(d,a,i)   M_DAT(UNCOND,0x07,d,a,0,1,i)         /* d = -a + i (with Carry) */
#define M_AND_IMM(d,a,i)   M_DAT(UNCOND,0x00,d,a,0,1,i)         /* d = a &  i */
#define M_ORR_IMM(d,a,i)   M_DAT(UNCOND,0x0c,d,a,0,1,i)         /* d = a |  i */
#define M_TST_IMM(a,i)     M_DAT(UNCOND,0x08,0,a,1,1,i)         /* TST a &  i */
#define M_TEQ_IMM(a,i)     M_DAT(UNCOND,0x09,0,a,1,1,i)         /* TST a ^  i */
#define M_CMP_IMM(a,i)     M_DAT(UNCOND,0x0a,0,a,1,1,i)         /* TST a -  i */
#define M_CMN_IMM(a,i)     M_DAT(UNCOND,0x0b,0,a,1,1,i)         /* TST a +  i */
#define M_MOV_IMM(d,i)    M_DAT(UNCOND,0x0d,d,0,0,1,i)         /* d =      i */
#define M_ADD_IMMS(d,a,i)  M_DAT(UNCOND,0x04,d,a,1,1,i)         /* d = a +  i (update Flags) */
#define M_SUB_IMMS(d,a,i)  M_DAT(UNCOND,0x02,d,a,1,1,i)         /* d = a -  i (update Flags) */
#define M_RSB_IMMS(d,a,i)  M_DAT(UNCOND,0x03,d,a,1,1,i)         /* d = -a + i (update Flags) */


#define PM_AND_IMM(cond,flags,d,s,i)	M_DAT(cond,0x00,d,s,flags,1,i)         /* d =      i */
#define PM_BIC_IMM(cond,flags,d,s,i)	M_DAT(cond,0x0e,d,s,flags,1,i)         /* d =      i */
#define PM_EOR_IMM(cond,flags,d,s,i)	M_DAT(cond,0x01,d,s,flags,1,i)         /* d =      i */
#define PM_SUB_IMM(cond,flags,d,s,i)	M_DAT(cond,0x02,d,s,flags,1,i)         /* d =      i */
#define PM_RSB_IMM(cond,flags,d,s,i)	M_DAT(cond,0x03,d,s,flags,1,i)         /* d =      i */
#define PM_ADD_IMM(cond,flags,d,s,i)	M_DAT(cond,0x04,d,s,flags,1,i)         /* d =      i */
#define PM_TST_IMM(cond,        s,i)	M_DAT(cond,0x08,0,s,1    ,1,i)         /* d =      i */
#define PM_CMP_IMM(cond,        s,i)	M_DAT(cond,0x0a,0,s,1    ,1,i)         /* d =      i */
#define PM_CMN_IMM(cond,        s,i)	M_DAT(cond,0x0b,0,s,1    ,1,i)         /* d =      i */

#define PM_ORR_IMM(cond,flags,d,s,i)	M_DAT(cond,0x0c,d,s,flags,1,i)         /* d =      i */
#define PM_MOV_IMM(cond,flags,d,i)		M_DAT(cond,0x0d,d,0,flags,1,i)         /* d =      i */



#define M_ADDSUB_IMM(d,a,i) if((i)>=0) M_ADD_IMM(d,a,i); else M_SUB_IMM(d,a,-(i))
#define M_MOVEQ(d,b)       M_DAT(COND_EQ,0x0d,d,0,0,0,b)
#define M_MOVVS_IMM(d,i)   M_DAT(COND_VS,0x0d,d,0,0,1,i)
#define M_MOVNE_IMM(d,i)   M_DAT(COND_NE,0x0d,d,0,0,1,i)
#define M_MOVLS_IMM(d,i)   M_DAT(COND_LS,0x0d,d,0,0,1,i)
#define M_ADDLT_IMM(d,a,i) M_DAT(COND_LT,0x04,d,a,0,1,i)
#define M_ADDGT_IMM(d,a,i) M_DAT(COND_GT,0x04,d,a,0,1,i)
#define M_SUBLT_IMM(d,a,i) M_DAT(COND_LT,0x02,d,a,0,1,i)
#define M_SUBGT_IMM(d,a,i) M_DAT(COND_GT,0x02,d,a,0,1,i)
#define M_RSBMI_IMM(d,a,i) M_DAT(COND_MI,0x03,d,a,0,1,i)
#define M_ADCMI_IMM(d,a,i) M_DAT(COND_MI,0x05,d,a,0,1,i)

#define M_MUL(d,a,b)       M_MULT(UNCOND,d,a,b,0,0,0x0)         /* d = a *  b */


#define M_LDMFD(regs,base) M_MEM_MULTI(UNCOND,1,0,regs,base,0,1,1)
#define M_STMFD(regs,base) M_MEM_MULTI(UNCOND,0,0,regs,base,1,0,1)

#define M_LDR_INTERN(d,base,off)   CHECK_OFFSET(off,0x0fff); M_MEM(UNCOND,1,0,d,base,((off)<0)?-(off):off,0,1,((off)<0)?0:1,0)
#define M_STR_INTERN(d,base,off)   CHECK_OFFSET(off,0x0fff); M_MEM(UNCOND,0,0,d,base,((off)<0)?-(off):off,0,1,((off)<0)?0:1,0)
#define M_LDRH(d,base,off)  CHECK_OFFSET(off,0x00ff); assert(off>=0); M_MEM2(UNCOND,1,1,0,d,base,off,1,1,1,0)
#define M_LDRSH(d,base,off) CHECK_OFFSET(off,0x00ff); assert(off>=0); M_MEM2(UNCOND,1,1,1,d,base,off,1,1,1,0)
#define M_LDRSB(d,base,off) CHECK_OFFSET(off,0x00ff); assert(off>=0); M_MEM2(UNCOND,1,0,1,d,base,off,1,1,1,0)
#define M_STRH(d,base,off)  CHECK_OFFSET(off,0x00ff); assert(off>=0); M_MEM2(UNCOND,0,1,0,d,base,off,1,1,1,0)
#define M_STRB(d,base,off)  CHECK_OFFSET(off,0x0fff); assert(off>=0); M_MEM(UNCOND,0,1,d,base,off,0,1,1,0)

#define M_LDFS_INTERN(d,base,off)  CHECK_OFFSET(off,0x03ff); M_CPDT(UNCOND,1,0,0,d,base,((off)<0)?-(off)>>2:(off)>>2,1,((off)<0)?0:1,0)
#define M_LDFD_INTERN(d,base,off)  CHECK_OFFSET(off,0x03ff); M_CPDT(UNCOND,1,0,1,d,base,((off)<0)?-(off)>>2:(off)>>2,1,((off)<0)?0:1,0)
#define M_STFS_INTERN(d,base,off)  CHECK_OFFSET(off,0x03ff); M_CPDT(UNCOND,0,0,0,d,base,((off)<0)?-(off)>>2:(off)>>2,1,((off)<0)?0:1,0)
#define M_STFD_INTERN(d,base,off)  CHECK_OFFSET(off,0x03ff); M_CPDT(UNCOND,0,0,1,d,base,((off)<0)?-(off)>>2:(off)>>2,1,((off)<0)?0:1,0)


#define M_ADFS(d,a,b)      M_CPDO(UNCOND,0x00,0,d,a,b)          /* d = a +  b */
#define M_SUFS(d,a,b)      M_CPDO(UNCOND,0x02,0,d,a,b)          /* d = a -  b */
#define M_RSFS(d,a,b)      M_CPDO(UNCOND,0x03,0,d,a,b)          /* d = b -  a */
#define M_MUFS(d,a,b)      M_CPDO(UNCOND,0x01,0,d,a,b)          /* d = a *  b */
#define M_DVFS(d,a,b)      M_CPDO(UNCOND,0x04,0,d,a,b)          /* d = a /  b */
#define M_RMFS(d,a,b)      M_CPDO(UNCOND,0x08,0,d,a,b)          /* d = a %  b */
#define M_ADFD(d,a,b)      M_CPDO(UNCOND,0x00,0,d,a,b) | (1<<7) /* d = a +  b */
#define M_SUFD(d,a,b)      M_CPDO(UNCOND,0x02,0,d,a,b) | (1<<7) /* d = a -  b */
#define M_RSFD(d,a,b)      M_CPDO(UNCOND,0x03,0,d,a,b) | (1<<7) /* d = b -  a */
#define M_MUFD(d,a,b)      M_CPDO(UNCOND,0x01,0,d,a,b) | (1<<7) /* d = a *  b */
#define M_DVFD(d,a,b)      M_CPDO(UNCOND,0x04,0,d,a,b) | (1<<7) /* d = a /  b */
#define M_RMFD(d,a,b)      M_CPDO(UNCOND,0x08,0,d,a,b) | (1<<7) /* d = a %  b */
#define M_MVFS(d,a)        M_CPDO(UNCOND,0x00,1,d,0,a)          /* d =      a */
#define M_MVFD(d,a)        M_CPDO(UNCOND,0x00,1,d,0,a) | (1<<7) /* d =      a */
#define M_MNFS(d,a)        M_CPDO(UNCOND,0x01,1,d,0,a)          /* d =    - a */
#define M_MNFD(d,a)        M_CPDO(UNCOND,0x01,1,d,0,a) | (1<<7) /* d =    - a */
#define M_CMF(a,b)         M_CPRT(UNCOND,1,0x0f,a,b) | (1<<23)  /* COMPARE a;  b */
#define M_FLTS(d,a)        M_CPRT(UNCOND,0,a,d,0)               /* d = (float) a */
#define M_FLTD(d,a)        M_CPRT(UNCOND,0,a,d,0) | (1<<7)      /* d = (float) a */
#define M_FIX(d,a)         M_CPRT(UNCOND,1,d,0,a) | (3<<5)      /* d = (int)   a */


#define M_B(off)           M_BRA(UNCOND,0,off)    /* unconditional branch */
#define M_BL(off)          M_BRA(UNCOND,1,off)    /* branch and link      */
#define M_BEQ(off)         M_BRA(COND_EQ,0,off)   /* conditional branches */
#define M_BNE(off)         M_BRA(COND_NE,0,off)
#define M_BGE(off)         M_BRA(COND_GE,0,off)
#define M_BGT(off)         M_BRA(COND_GT,0,off)
#define M_BLT(off)         M_BRA(COND_LT,0,off)
#define M_BLE(off)         M_BRA(COND_LE,0,off)
#define M_BHI(off)         M_BRA(COND_HI,0,off)   /* unsigned conditional */
#define M_BHS(off)         M_BRA(COND_CS,0,off)
#define M_BLO(off)         M_BRA(COND_CC,0,off)
#define M_BLS(off)         M_BRA(COND_LS,0,off)



#endif /*COMPILER_DEFS_H_*/
