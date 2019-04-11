/************** This is a generated file! **************/

#include "compiler.h"
#include "../mem.h"
#include "../cpuregs.h"
#include "compiler_defs.h"


int temp;


/*********00 NOP
 */
void op_0x00(int af) 
{
}


/*********01 LD  BC,%w
 */
void op_0x01(int af) 
{
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,6, READB(cur_block.pc+1) );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(READB(cur_block.pc+2), 4) );cur_block.genp++;
}


/*********02 LD  (BC),A
 */
void op_0x02(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(6, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,2,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,5,1,6,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,6);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_EQ,0,1,5, 0xff);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********03 INC BC
 */
void op_0x03(int af) 
{
	*cur_block.genp = PM_ADD_IMM(COND_AL,1,6,6, 1);cur_block.genp++;
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 8) );cur_block.genp++;
	//{DAVID mov		r6, r6, lsr #16}
}


/*********04 INC B
 */
void op_0x04(int af) 
{
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,6,6, IMM_ROTL(0x01, 4) );cur_block.genp++;
	//DAVID{mov			r6, r6, lsl #16}
	//DAVID{mov			r6, r6, lsr #16}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 8) );cur_block.genp++;
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, IMM_ROTL(0x0f, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x20);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
}


/*********05 DEC B
 */
void op_0x05(int af) 
{
	*cur_block.genp = PM_SUB_IMM(COND_AL,0,6,6, IMM_ROTL(0x01, 4) );cur_block.genp++;
	{/*FIXME geht auch schneller ?*/}
	*cur_block.genp = PM_MOV(COND_AL,0,6,REG_LSL(6, 16));cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,6,REG_LSR(6, 16));cur_block.genp++;
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0xc0);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, IMM_ROTL(0x0f, 4) );cur_block.genp++;
			*cur_block.genp = PM_CMP_IMM(COND_AL,0, IMM_ROTL(0x0f, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x60);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const1 |= 0x40;
}


/*********06 LD  B,%b
 */
void op_0x06(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(READB(cur_block.pc + 1), 4) );cur_block.genp++;
}


/*********07 RLCA
 */
void op_0x07(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(5, 7));cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,5,0,REG_LSL(5, 1));cur_block.genp++;
	if(ALIVE(FC)){
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSL(0, 4));cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,5, 0xff);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0xe0;
}


/*********08 LD (%w),SP
 */
void op_0x08(int af) 
{
	{temp = READW(cur_block.pc+1);}
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,0,0, IMM_ROTL((temp >> 8) & 0xff, 4) );cur_block.genp++;

	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(0, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,1, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 9);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(0, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,2,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,9,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,0, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 8));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,0,1,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,9, 0xff);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, (temp+1) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,0,0, IMM_ROTL(((temp+1) >> 8) & 0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(9, 8));cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

}


/*********09 ADD HL,BC
 */
void op_0x09(int af) 
{
	*cur_block.genp = PM_ADD(COND_AL,0,0,8,6);cur_block.genp++;
	if(ALIVE(FC|FH)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x80);cur_block.genp++;
		if(ALIVE(FC)){	
			*cur_block.genp = PM_TST_IMM(COND_AL,0, IMM_ROTL(0x01, 8) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,8,0,8);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,8,8,6);cur_block.genp++;
			*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(0x10, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x20);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_MOV(COND_AL,0,8,REG_LSL(0, 16));cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,8,REG_LSR(8, 16));cur_block.genp++;
	cur_block.const0 &= 0x8f;
	cur_block.const1 &= 0x8f;
	cur_block.const0 |= 0x40;
}


/*********0a LD  A,(BC)
 */
void op_0x0a(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(6, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,6,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,6);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,0, 0xff);cur_block.genp++;
}


/*********0b DEC BC
 */
void op_0x0b(int af) 
{
	*cur_block.genp = PM_SUB_IMM(COND_AL,1,6,6, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_MI,0,6,REG_LSR(6, 16));cur_block.genp++;
	//{DAVID}
}


/*********0c INC C
 */
void op_0x0c(int af) 
{
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,6,6, 0x01);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB_IMM(COND_EQ,0,6,6, IMM_ROTL(0x1, 4) );cur_block.genp++;
	
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x20);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
}


/*********0d DEC C
 */
void op_0x0d(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB_IMM(COND_NE,0,6,6, 0x01);cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_EQ,0,6,6, 0xff);cur_block.genp++;
	
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, 0xff);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0xc0);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x60);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const1 |= 0x40;
}


/*********0e LD  C,%b
 */
void op_0x0e(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, READB(cur_block.pc + 1) );cur_block.genp++;
}


/*********0f RRCA
 */
void op_0x0f(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,1,5,REG_LSR(5, 1));cur_block.genp++;
	if(ALIVE(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0xef);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	*cur_block.genp = PM_ORR_IMM(COND_CS,0,5,5, 0x80);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0xe0;
}


/*********10 STOP
 */
void op_0x10(int af) 
{
//{ cop_end(); }
//{ err_msg("STOP", 800); }
//{ cop_begin(); }
//{	mov 	r0, 'IMM_ROTL(0xff, 4)'
//{	orr		r0, r0, #0x4d
//{	___usem	_bl_ mem_read
//{	tst		r0, #0x01
//{	beq		#7
//{	ldr		r1, [r11, 'SPDo']
//{	eor		r1, r1, #0x01
//{	str		r1, [r11, 'SPDo']	
//{	and		r2, r0, #0x7e
//{	orr		r1, r2, r1, lsl #7
//{
//{	mov 	r0, 'IMM_ROTL(0xff, 4)'
//{	orr		r0, r0, #0x4d
//{	___usem	_bl_ mem_write
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_stop)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	{set_constflags(af);}
	{linkblock_begin(0);} 
	{patchblock_begin();}
		{temp = cur_block.pc + 2;} // FIXME +2 or +1 ? 
	{linkblock_end(temp,0/*stop cannot cascade*/);}

}


/*********11 LD  DE,%w
 */
void op_0x11(int af) 
{
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,7, READB(cur_block.pc+1) );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(READB(cur_block.pc+2), 4) );cur_block.genp++;
}


/*********12 LD  (DE),A
 */
void op_0x12(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(7, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,2,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,5,1,7,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,7);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_EQ,0,1,5, 0xff);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********13 INC DE
 */
void op_0x13(int af) 
{
	*cur_block.genp = PM_ADD_IMM(COND_AL,1,7,7, 1);cur_block.genp++;
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 8) );cur_block.genp++;
	//{DAVID mov		r7, r7, lsr #16}
}


/*********14 INC D
 */
void op_0x14(int af) 
{
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,7,7, IMM_ROTL(0x01, 4) );cur_block.genp++;
	//DAVID{mov			r7, r7, lsl #16}
	//DAVID{mov			r7, r7, lsr #16}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 8) );cur_block.genp++;
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, IMM_ROTL(0x0f, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x20);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
}


/*********15 DEC D
 */
void op_0x15(int af) 
{

	*cur_block.genp = PM_SUB_IMM(COND_AL,0,7,7, IMM_ROTL(0x01, 4) );cur_block.genp++;
	{/*FIXME geht auch schneller ?*/}
	*cur_block.genp = PM_MOV(COND_AL,0,7,REG_LSL(7, 16));cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,7,REG_LSR(7, 16));cur_block.genp++;
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0xc0);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, IMM_ROTL(0x0f, 4) );cur_block.genp++;
			*cur_block.genp = PM_CMP_IMM(COND_AL,0, IMM_ROTL(0x0f, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x60);cur_block.genp++;
		}
	}

	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const1 |= 0x40;
}


/*********16 LD  D,%b
 */
void op_0x16(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(READB(cur_block.pc + 1), 4) );cur_block.genp++;
}


/*********17 RLA
 */
void op_0x17(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(5, 7));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSL(5, 1));cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_NE,0,5,5, 0x01);cur_block.genp++;
	}
	else{
		*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSL(5, 1));cur_block.genp++;
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ORR_IMM(COND_AL,0,5,5, 0x01);cur_block.genp++;
		}
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSL(0, 4));cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,5, 0xff);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0xe0;
}


/*********18 JR  %o
 */
void op_0x18(int af) 
{
	{set_constflags(af);}
	{linkblock_begin(0);} //jump
	{patchblock_begin();}
		{temp = cur_block.pc + ((int)(signed char)READB(cur_block.pc+1)) + 2;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
  	{linkblock_end(temp,USE_CASCADING);}
}


/*********19 ADD HL,DE
 */
void op_0x19(int af) 
{
	*cur_block.genp = PM_ADD(COND_AL,0,0,8,7);cur_block.genp++;
	if(ALIVE(FC|FH)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x80);cur_block.genp++;
		if(ALIVE(FC)){	
			*cur_block.genp = PM_TST_IMM(COND_AL,0, IMM_ROTL(0x01, 8) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,8,0,8);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,8,8,7);cur_block.genp++;
			*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(0x10, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x20);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_MOV(COND_AL,0,8,REG_LSL(0, 16));cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,8,REG_LSR(8, 16));cur_block.genp++;
	cur_block.const0 &= 0x8f;
	cur_block.const1 &= 0x8f;
	cur_block.const0 |= 0x40;
}


/*********1a LD  A,(DE)
 */
void op_0x1a(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(7, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,7,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,7);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,0, 0xff);cur_block.genp++;
}


/*********1b DEC DE
 */
void op_0x1b(int af) 
{
	*cur_block.genp = PM_SUB_IMM(COND_AL,1,7,7, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_MI,0,7,REG_LSR(7, 16));cur_block.genp++;
	//{DAVID}
}


/*********1c INC E
 */
void op_0x1c(int af) 
{
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,7,7, 0x01);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB_IMM(COND_EQ,0,7,7, IMM_ROTL(0x1, 4) );cur_block.genp++;
	
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x20);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
}


/*********1d DEC E
 */
void op_0x1d(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB_IMM(COND_NE,0,7,7, 0x01);cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_EQ,0,7,7, 0xff);cur_block.genp++;
	
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, 0xff);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0xc0);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x60);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const1 |= 0x40;
}


/*********1e LD  E,%b
 */
void op_0x1e(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, READB(cur_block.pc + 1) );cur_block.genp++;
}


/*********1f RRA
 */
void op_0x1f(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,5, 0x01);cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSR(5, 1));cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_NE,0,5,5, 0x80);cur_block.genp++;
	}
	else{
		*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSR(5, 1));cur_block.genp++;
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ORR_IMM(COND_AL,0,5,5, 0x80);cur_block.genp++;
		}
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSL(0, 4));cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0xe0;
}


/*********20 JR  NZ,%o
 */
void op_0x20(int af) 
{
	if(!IS_CONSTANT(FZ)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FZ );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_NE); /*@bne 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT1(FZ)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} //jump
	{patchblock_begin();}
		{temp = cur_block.pc + ((int)(signed char)READB(cur_block.pc+1)) + 2;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
  	{linkblock_end(temp,USE_CASCADING);}
	{linkblock_begin(-1);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 2;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
}


/*********21 LD  HL,%w
 */
void op_0x21(int af) 
{
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,8, READB(cur_block.pc+1) );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(READB(cur_block.pc+2), 4) );cur_block.genp++;
}


/*********22 LD  (HLI),A
 */
void op_0x22(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,2,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,5,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_EQ,0,1,5, 0xff);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,8,8, 1);cur_block.genp++;
	{/*bic		r8, r8, 'IMM_ROTL(0xff, 8)' FIXME */}	
}


/*********23 INC HL
 */
void op_0x23(int af) 
{
	*cur_block.genp = PM_ADD_IMM(COND_AL,1,8,8, 1);cur_block.genp++;
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 8) );cur_block.genp++;
	//{DAVID mov		r8, r8, lsr #16}
}


/*********24 INC H
 */
void op_0x24(int af) 
{
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,8,8, IMM_ROTL(0x01, 4) );cur_block.genp++;
	//DAVID{mov			r8, r8, lsl #16}
	//DAVID{mov			r8, r8, lsr #16}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 8) );cur_block.genp++;
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, IMM_ROTL(0x0f, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x20);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
}


/*********25 DEC H
 */
void op_0x25(int af) 
{
	*cur_block.genp = PM_SUB_IMM(COND_AL,0,8,8, IMM_ROTL(0x01, 4) );cur_block.genp++;
	{/*FIXME geht auch schneller ?*/}
	*cur_block.genp = PM_MOV(COND_AL,0,8,REG_LSL(8, 16));cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,8,REG_LSR(8, 16));cur_block.genp++;
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0xc0);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, IMM_ROTL(0x0f, 4) );cur_block.genp++;
			*cur_block.genp = PM_CMP_IMM(COND_AL,0, IMM_ROTL(0x0f, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x60);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const1 |= 0x40;
}


/*********26 LD  H,%b
 */
void op_0x26(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(READB(cur_block.pc + 1), 4) );cur_block.genp++;
}


/*********27 DAA
 */
void op_0x27(int af) 
{
	{set_constflags(0x70);}

	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,4, 0x70);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,1,5,REG_LSL(0, 4));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,2,11, 136, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,0,2,1,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x4f);cur_block.genp++;
	*cur_block.genp = PM_ADD(COND_AL,0,5,5,0);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,2,11, 140, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,0,2,REG_LSR(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,4,4,0);cur_block.genp++;
	cur_block.const0 &= 0x4f;
	cur_block.const1 &= 0x4f;
	cur_block.const0 |= 0x20;
}


/*********28 JR  Z,%o
 */
void op_0x28(int af) 
{
	if(!IS_CONSTANT(FZ)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FZ );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_EQ); /*beq 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT0(FZ)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} //jump
	{patchblock_begin();}
		{temp = cur_block.pc + ((int)(signed char)READB(cur_block.pc+1)) + 2;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
  	{linkblock_end(temp,USE_CASCADING);}
	{linkblock_begin(-1);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 2;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
}


/*********29 ADD HL,HL
 */
void op_0x29(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,8,REG_LSL(8, 1));cur_block.genp++;
	if(ALIVE(FC|FH)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x80);cur_block.genp++;
		if(ALIVE(FC)){	
			*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(0x01, 8) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(0x10, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x20);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_MOV(COND_AL,0,8,REG_LSL(8, 16));cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,8,REG_LSR(8, 16));cur_block.genp++;
	cur_block.const0 &= 0x8f;
	cur_block.const1 &= 0x8f;
	cur_block.const0 |= 0x40;
}


/*********2a LD  A,(HLI)
 */
void op_0x2a(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,0, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,8,8, 1);cur_block.genp++;
	{/*bic		r8, r8, 'IMM_ROTL(0xff, 8)'*/}
}


/*********2b DEC HL
 */
void op_0x2b(int af) 
{
	*cur_block.genp = PM_SUB_IMM(COND_AL,1,8,8, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_MI,0,8,REG_LSR(8, 16));cur_block.genp++;
	//{DAVID}
}


/*********2c INC L
 */
void op_0x2c(int af) 
{
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,8,8, 0x01);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB_IMM(COND_EQ,0,8,8, IMM_ROTL(0x1, 4) );cur_block.genp++;
	
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x20);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
}


/*********2d DEC L
 */
void op_0x2d(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB_IMM(COND_NE,0,8,8, 0x01);cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_EQ,0,8,8, 0xff);cur_block.genp++;
	
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, 0xff);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0xc0);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x60);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const1 |= 0x40;
}


/*********2e LD  L,%b
 */
void op_0x2e(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, READB(cur_block.pc + 1) );cur_block.genp++;
}


/*********2f CPL
 */
void op_0x2f(int af) 
{
	*cur_block.genp = PM_EOR_IMM(COND_AL,0,5,5, 0xff);cur_block.genp++;
	cur_block.const0 &= 0x9f;
	cur_block.const1 &= 0x9f;
	cur_block.const1 |= 0x60;
}


/*********30 JR  NC,%o
 */
void op_0x30(int af) 
{
	if(!IS_CONSTANT(FC)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FC );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_NE); /*@bne 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT1(FC)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} //jump
	{patchblock_begin();}
		{temp = cur_block.pc + ((int)(signed char)READB(cur_block.pc+1)) + 2;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
  	{linkblock_end(temp,USE_CASCADING);}
	{linkblock_begin(-1);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 2;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
}


/*********31 LD  SP,%w
 */
void op_0x31(int af) 
{
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,9, READB(cur_block.pc+1) );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,9,9, IMM_ROTL(READB(cur_block.pc+2), 4) );cur_block.genp++;
}


/*********32 LD  (HLD),A
 */
void op_0x32(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,2,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,5,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_EQ,0,1,5, 0xff);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_SUB_IMM(COND_AL,0,8,8, 1);cur_block.genp++;
	{/*bic		r8, r8, 'IMM_ROTL(0xff, 8)' FIXME */}
}


/*********33 INC SP
 */
void op_0x33(int af) 
{
	*cur_block.genp = PM_ADD_IMM(COND_AL,1,9,9, 1);cur_block.genp++;
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,9,9, IMM_ROTL(0xff, 8) );cur_block.genp++;
	//{DAVID mov		r9, r9, lsr #16}
}


/*********34 INC (HL)
 */
void op_0x34(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,1,0, 1);cur_block.genp++;
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_TST_IMM(COND_AL,1, 0xff);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,1, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x20);cur_block.genp++;
		}
	}	
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
}


/*********35 DEC (HL)
 */
void op_0x35(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_SUB_IMM(COND_AL,0,1,0, 1);cur_block.genp++;
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_TST_IMM(COND_AL,1, 0xff);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0xc0);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,1, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x60);cur_block.genp++;
		}
	}	
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const1 |= 0x40;
}


/*********36 LD  (HL),%b
 */
void op_0x36(int af) 
{
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, READB(cur_block.pc + 1) );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********37 SCF
 */
void op_0x37(int af) 
{
	cur_block.const0 &= 0x8f;
	cur_block.const1 &= 0x8f;
	cur_block.const0 |= 0x60;
	cur_block.const1 |= 0x10;
}


/*********38 JR  C,%o
 */
void op_0x38(int af) 
{
	if(!IS_CONSTANT(FC)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FC );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_EQ); /*beq 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT0(FC)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} //jump
	{patchblock_begin();}
		{temp = cur_block.pc + ((int)(signed char)READB(cur_block.pc+1)) + 2;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
  	{linkblock_end(temp,USE_CASCADING);}
	{linkblock_begin(-1);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 2;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
}


/*********39 ADD HL,SP
 */
void op_0x39(int af) 
{
	*cur_block.genp = PM_ADD(COND_AL,0,0,8,9);cur_block.genp++;
	if(ALIVE(FC|FH)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x80);cur_block.genp++;
		if(ALIVE(FC)){	
			*cur_block.genp = PM_TST_IMM(COND_AL,0, IMM_ROTL(0x01, 8) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,8,0,8);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,8,8,9);cur_block.genp++;
			*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(0x10, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x20);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_MOV(COND_AL,0,8,REG_LSL(0, 16));cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,8,REG_LSR(8, 16));cur_block.genp++;
	cur_block.const0 &= 0x8f;
	cur_block.const1 &= 0x8f;
	cur_block.const0 |= 0x40;
}


/*********3a LD  A,(HLD)
 */
void op_0x3a(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,0, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB_IMM(COND_AL,0,8,8, 1);cur_block.genp++;
	{/*bic		r8, r8, 'IMM_ROTL(0xff, 8)' FIXME */}
}


/*********3b DEC SP
 */
void op_0x3b(int af) 
{
	*cur_block.genp = PM_SUB_IMM(COND_AL,1,9,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_MI,0,9,REG_LSR(9, 16));cur_block.genp++;
	//{DAVID}
}


/*********3c INC A
 */
void op_0x3c(int af) 
{
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,5,5, 0x01);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){ // FIXME and + subs durch EINEN anderen ersetzen  
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,5, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x20);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
}


/*********3d DEC A
 */
void op_0x3d(int af) 
{
	*cur_block.genp = PM_SUB_IMM(COND_AL,0,5,5, 0x01);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
	if(ALIVE(FZ | FH)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x1f);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0xc0);cur_block.genp++;
		}
		if(ALIVE(FH)){ // FIXME and + subs durch EINEN anderen ersetzen  
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,5, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_SUB_IMM(COND_AL,1,0,0, 0x0f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x60);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const1 |= 0x40;
}


/*********3e LD  A,%b
 */
void op_0x3e(int af) 
{
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,5, READB(cur_block.pc + 1) );cur_block.genp++;
}


/*********3f CCF
 */
void op_0x3f(int af) 
{
	if(ALIVE(FC)){
		if(!IS_CONSTANT(FC)){
			*cur_block.genp = PM_EOR_IMM(COND_AL,0,4,4, 0x10);cur_block.genp++;
		}else if(IS_CONSTANT0(FC)){
			*cur_block.genp = PM_ORR_IMM(COND_AL,0,4,4, 0x10);cur_block.genp++;
		}else{
			*cur_block.genp = PM_BIC_IMM(COND_AL,0,4,4, 0x10);cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x8f;
	cur_block.const1 &= 0x8f;
	cur_block.const0 |= 0x60;
}


/*********40 LD  B,B
 */
void op_0x40(int af) 
{
}


/*********41 LD  B,C
 */
void op_0x41(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSL(6, 8));cur_block.genp++;
}


/*********42 LD  B,D
 */
void op_0x42(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,0);cur_block.genp++;
}


/*********43 LD  B,E
 */
void op_0x43(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSL(0, 8));cur_block.genp++;
}


/*********44 LD  B,H
 */
void op_0x44(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,0);cur_block.genp++;
}


/*********45 LD  B,L
 */
void op_0x45(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSL(0, 8));cur_block.genp++;
}


/*********46 LD  B,(HL)
 */
void op_0x46(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSL(0, 8));cur_block.genp++;
}


/*********47 LD  B,A
 */
void op_0x47(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSL(5, 8));cur_block.genp++;
}


/*********48 LD  C,B
 */
void op_0x48(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSR(6, 8));cur_block.genp++;
}


/*********49 LD  C,C
 */
void op_0x49(int af) 
{
}


/*********4a LD  C,D
 */
void op_0x4a(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSR(7, 8));cur_block.genp++;
}


/*********4b LD  C,E
 */
void op_0x4b(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,0);cur_block.genp++;
}


/*********4c LD  C,H
 */
void op_0x4c(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSR(8, 8));cur_block.genp++;
}


/*********4d LD  C,L
 */
void op_0x4d(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,0);cur_block.genp++;
}


/*********4e LD  C,(HL)
 */
void op_0x4e(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,0);cur_block.genp++;
}


/*********4f LD  C,A
 */
void op_0x4f(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,5);cur_block.genp++;
}


/*********50 LD  D,B
 */
void op_0x50(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,0);cur_block.genp++;
}


/*********51 LD  D,C
 */
void op_0x51(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSL(0, 8));cur_block.genp++;
}


/*********52 LD  D,D
 */
void op_0x52(int af) 
{
}


/*********53 LD  D,E
 */
void op_0x53(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSL(7, 8));cur_block.genp++;
}


/*********54 LD  D,H
 */
void op_0x54(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,0);cur_block.genp++;
}


/*********55 LD  D,L
 */
void op_0x55(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSL(0, 8));cur_block.genp++;
}


/*********56 LD  D,(HL)
 */
void op_0x56(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSL(0, 8));cur_block.genp++;
}


/*********57 LD  D,A
 */
void op_0x57(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSL(5, 8));cur_block.genp++;
}


/*********58 LD  E,B
 */
void op_0x58(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSR(6, 8));cur_block.genp++;
}


/*********59 LD  E,C
 */
void op_0x59(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,0);cur_block.genp++;
}


/*********5a LD  E,D
 */
void op_0x5a(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSR(7, 8));cur_block.genp++;
}


/*********5b LD  E,E
 */
void op_0x5b(int af) 
{
}


/*********5c LD  E,H
 */
void op_0x5c(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSR(8, 8));cur_block.genp++;
}


/*********5d LD  E,L
 */
void op_0x5d(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,0);cur_block.genp++;
}


/*********5e LD  E,(HL)
 */
void op_0x5e(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,0);cur_block.genp++;
}


/*********5f LD  E,A
 */
void op_0x5f(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,5);cur_block.genp++;
}


/*********60 LD  H,B
 */
void op_0x60(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,0);cur_block.genp++;
}


/*********61 LD  H,C
 */
void op_0x61(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSL(0, 8));cur_block.genp++;
}


/*********62 LD  H,D
 */
void op_0x62(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,0);cur_block.genp++;
}


/*********63 LD  H,E
 */
void op_0x63(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSL(0, 8));cur_block.genp++;
}


/*********64 LD  H,H
 */
void op_0x64(int af) 
{
}


/*********65 LD  H,L
 */
void op_0x65(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSL(8, 8));cur_block.genp++;
}


/*********66 LD  H,(HL)
 */
void op_0x66(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSL(0, 8));cur_block.genp++;
}


/*********67 LD  H,A
 */
void op_0x67(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSL(5, 8));cur_block.genp++;
}


/*********68 LD  L,B
 */
void op_0x68(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSR(6, 8));cur_block.genp++;
}


/*********69 LD  L,C
 */
void op_0x69(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,0);cur_block.genp++;
}


/*********6a LD  L,D
 */
void op_0x6a(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSR(7, 8));cur_block.genp++;
}


/*********6b LD  L,E
 */
void op_0x6b(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,0);cur_block.genp++;
}


/*********6c LD  L,H
 */
void op_0x6c(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSR(8, 8));cur_block.genp++;
}


/*********6d LD  L,L
 */
void op_0x6d(int af) 
{
}


/*********6e LD  L,(HL)
 */
void op_0x6e(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,0);cur_block.genp++;
}


/*********6f LD  L,A
 */
void op_0x6f(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,5);cur_block.genp++;
}


/*********70 LD  (HL),B
 */
void op_0x70(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(6, 8));cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********71 LD  (HL),C
 */
void op_0x71(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,2,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,6,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_EQ,0,1,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********72 LD  (HL),D
 */
void op_0x72(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(7, 8));cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********73 LD  (HL),E
 */
void op_0x73(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,2,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,7,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_EQ,0,1,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********74 LD  (HL),H
 */
void op_0x74(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 8));cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********75 LD  (HL),L
 */
void op_0x75(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,2,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,8,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_EQ,0,1,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********76 HALT
 */
void op_0x76(int af) 
{
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, 1);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,0,0,11, HALTo , 0,1,1,0);cur_block.genp++;

	{set_constflags(af);}
	{linkblock_begin(0);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 1;}
	{linkblock_end(temp,0/*halt cannot cascade*/);}
}


/*********77 LD  (HL),A
 */
void op_0x77(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,2,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,5,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_EQ,0,1,5, 0xff);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********78 LD  A,B
 */
void op_0x78(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSR(6, 8));cur_block.genp++;
}


/*********79 LD  A,C
 */
void op_0x79(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,6, 0xff);cur_block.genp++;
}


/*********7a LD  A,D
 */
void op_0x7a(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSR(7, 8));cur_block.genp++;
}


/*********7b LD  A,E
 */
void op_0x7b(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,7, 0xff);cur_block.genp++;
}


/*********7c LD  A,H
 */
void op_0x7c(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSR(8, 8));cur_block.genp++;
}


/*********7d LD  A,L
 */
void op_0x7d(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,8, 0xff);cur_block.genp++;
}


/*********7e LD  A,(HL)
 */
void op_0x7e(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,0, 0xff);cur_block.genp++;
}


/*********7f LD  A,A
 */
void op_0x7f(int af) 
{
}


/*********80 ADD A,B
 */
void op_0x80(int af) 
{
	*cur_block.genp = PM_ADD(COND_AL,1,0,5,REG_LSR(6, 8));cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(6, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,0, 0xff);cur_block.genp++;
	
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********81 ADD A,C
 */
void op_0x81(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ADD(COND_AL,1,1,5,0);cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,0,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,0,0,1);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,0, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,1, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(0, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********82 ADD A,D
 */
void op_0x82(int af) 
{
	*cur_block.genp = PM_ADD(COND_AL,1,0,5,REG_LSR(7, 8));cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(7, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,0, 0xff);cur_block.genp++;
	
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********83 ADD A,E
 */
void op_0x83(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ADD(COND_AL,1,1,5,0);cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,0,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,0,0,1);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,0, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,1, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(0, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********84 ADD A,H
 */
void op_0x84(int af) 
{
	*cur_block.genp = PM_ADD(COND_AL,1,0,5,REG_LSR(8, 8));cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(8, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,0, 0xff);cur_block.genp++;
	
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********85 ADD A,L
 */
void op_0x85(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ADD(COND_AL,1,1,5,0);cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,0,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,0,0,1);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,0, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,1, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(0, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********86 ADD A,(HL)
 */
void op_0x86(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD(COND_AL,1,1,5,0);cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,0,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,0,0,1);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,0, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,1, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(0, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********87 ADD A,A
 */
void op_0x87(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSL(5, 1));cur_block.genp++;
	if(!ALIVE(FC) && ALIVE(FH|FZ)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
	}
	
	if(ALIVE(FC)){
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSR(5, 4));cur_block.genp++;
		if(ALIVE(FH)){			
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,5, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
		}
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x70);cur_block.genp++;
	}
	else if(ALIVE(FH)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,5, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********88 ADC A,B
 */
void op_0x88(int af) 
{
	*cur_block.genp = PM_ADD(COND_AL,0,0,5,REG_LSR(6, 8));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ADD_IMM(COND_NE,0,0,0, 1);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,0, 1);cur_block.genp++;
		}
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(6, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,0, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********89 ADC A,C
 */
void op_0x89(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ADD(COND_AL,0,1,5,0);cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ADD_IMM(COND_NE,0,1,1, 1);cur_block.genp++;
	}
	else{
		*cur_block.genp = PM_ADD_IMM(COND_AL,0,1,1, 1);cur_block.genp++;
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,0,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,0,0,1);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,0, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,1, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(0, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********8a ADC A,D
 */
void op_0x8a(int af) 
{
	*cur_block.genp = PM_ADD(COND_AL,0,0,5,REG_LSR(7, 8));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ADD_IMM(COND_NE,0,0,0, 1);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,0, 1);cur_block.genp++;
		}
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(7, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,0, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********8b ADC A,E
 */
void op_0x8b(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ADD(COND_AL,0,1,5,0);cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ADD_IMM(COND_NE,0,1,1, 1);cur_block.genp++;
	}
	else{
		*cur_block.genp = PM_ADD_IMM(COND_AL,0,1,1, 1);cur_block.genp++;
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,0,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,0,0,1);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,0, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,1, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(0, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********8c ADC A,H
 */
void op_0x8c(int af) 
{
	*cur_block.genp = PM_ADD(COND_AL,0,0,5,REG_LSR(8, 8));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ADD_IMM(COND_NE,0,0,0, 1);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,0, 1);cur_block.genp++;
		}
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(8, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,0, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********8d ADC A,L
 */
void op_0x8d(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ADD(COND_AL,0,1,5,0);cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ADD_IMM(COND_NE,0,1,1, 1);cur_block.genp++;
	}
	else{
		*cur_block.genp = PM_ADD_IMM(COND_AL,0,1,1, 1);cur_block.genp++;
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,0,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,0,0,1);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,0, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,1, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(0, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********8e ADC A,(HL)
 */
void op_0x8e(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD(COND_AL,0,1,5,0);cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ADD_IMM(COND_NE,0,1,1, 1);cur_block.genp++;
	}
	else{
		*cur_block.genp = PM_ADD_IMM(COND_AL,0,1,1, 1);cur_block.genp++;
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,0,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,0,0,1);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,0, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,1, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(0, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********8f ADC A
 */
void op_0x8f(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSL(5, 1));cur_block.genp++;
	if(!IS_CONSTANT(FC)) {
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,5,5,REG_LSR(4, 4));cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ORR_IMM(COND_AL,0,5,5, 1);cur_block.genp++;
		}
	}

	if(ALIVE(FZ | FH | FC)){
		if(IS_CONSTANT(FC) || (!IS_CONSTANT(FC) && ALIVE(FC))){
			*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		}		
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,5, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_TST_IMM(COND_AL,5, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x20);cur_block.genp++;
		}
	}
	
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********90 SUB B
 */
void op_0x90(int af) 
{
	*cur_block.genp = PM_SUB(COND_AL,1,0,5,REG_LSR(6, 8));cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(6, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,0, 0xff);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********91 SUB C
 */
void op_0x91(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB(COND_AL,1,0,5,1);cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,1);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,0, 0xff);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********92 SUB D
 */
void op_0x92(int af) 
{
	*cur_block.genp = PM_SUB(COND_AL,1,0,5,REG_LSR(7, 8));cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(7, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,0, 0xff);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********93 SUB E
 */
void op_0x93(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB(COND_AL,1,0,5,1);cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,1);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,0, 0xff);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********94 SUB H
 */
void op_0x94(int af) 
{
	*cur_block.genp = PM_SUB(COND_AL,1,0,5,REG_LSR(8, 8));cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(8, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,0, 0xff);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********95 SUB L
 */
void op_0x95(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB(COND_AL,1,0,5,1);cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,1);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,0, 0xff);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********96 SUB (HL)
 */
void op_0x96(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_SUB(COND_AL,1,2,5,0);cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,2);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,2, IMM_ROTL(0x01, 4) );cur_block.genp++;
			
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,2, 0xff);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********97 SUB A
 */
void op_0x97(int af) 
{
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,5, 0x0);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x30;
	cur_block.const1 |= 0xc0;
}


/*********98 SBC A,B
 */
void op_0x98(int af) 
{
	*cur_block.genp = PM_SUB(COND_AL,0,0,5,REG_LSR(6, 8));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_SUB_IMM(COND_NE,0,0,0, 1);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_SUB_IMM(COND_AL,0,0,0, 1);cur_block.genp++;
		}
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(6, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,0, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********99 SBC A,C
 */
void op_0x99(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB(COND_AL,0,1,5,0);cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_SUB_IMM(COND_NE,0,1,1, 1);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_SUB_IMM(COND_AL,0,1,1, 1);cur_block.genp++;
		}
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,0,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,0,0,1);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,0, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,1, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(0, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********9a SBC A,D
 */
void op_0x9a(int af) 
{
	*cur_block.genp = PM_SUB(COND_AL,0,0,5,REG_LSR(7, 8));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_SUB_IMM(COND_NE,0,0,0, 1);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_SUB_IMM(COND_AL,0,0,0, 1);cur_block.genp++;
		}
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(7, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,0, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********9b SBC A,E
 */
void op_0x9b(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB(COND_AL,0,1,5,0);cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_SUB_IMM(COND_NE,0,1,1, 1);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_SUB_IMM(COND_AL,0,1,1, 1);cur_block.genp++;
		}
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,0,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,0,0,1);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,0, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,1, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(0, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********9c SBC A,H
 */
void op_0x9c(int af) 
{
	*cur_block.genp = PM_SUB(COND_AL,0,0,5,REG_LSR(8, 8));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_SUB_IMM(COND_NE,0,0,0, 1);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_SUB_IMM(COND_AL,0,0,0, 1);cur_block.genp++;
		}
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(8, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,0, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********9d SBC A,L
 */
void op_0x9d(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB(COND_AL,0,1,5,0);cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_SUB_IMM(COND_NE,0,1,1, 1);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_SUB_IMM(COND_AL,0,1,1, 1);cur_block.genp++;
		}
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,0,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,0,0,1);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,0, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,1, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(0, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********9e SBC A,(HL)
 */
void op_0x9e(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_SUB(COND_AL,0,1,5,0);cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_SUB_IMM(COND_NE,0,1,1, 1);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_SUB_IMM(COND_AL,0,1,1, 1);cur_block.genp++;
		}
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,0,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,0,0,1);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,0, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(0, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,0,1, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(0, 4));cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********9f SBC A,A
 */
void op_0x9f(int af) 
{
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		if(ALIVE(FZ | FH | FC)) {		
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
			*cur_block.genp = PM_MOV_IMM(COND_NE,0,4, 0x30);cur_block.genp++;
		}
		*cur_block.genp = PM_MOV_IMM(COND_EQ,0,5, 0x00);cur_block.genp++;
		*cur_block.genp = PM_MOV_IMM(COND_NE,0,5, 0xff);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)) {
			*cur_block.genp = PM_MOV_IMM(COND_AL,0,5, 0xff);cur_block.genp++;
			if(ALIVE(FZ | FH | FC)) {		
				*cur_block.genp = PM_MOV_IMM(COND_AL,0,4, 0x30);cur_block.genp++;
			}
		}
		else{
			*cur_block.genp = PM_MOV_IMM(COND_AL,0,5, 0x00);cur_block.genp++;
			if(ALIVE(FZ | FH | FC)) {		
				*cur_block.genp = PM_MOV_IMM(COND_AL,0,4, 0x80);cur_block.genp++;
			}
		}
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********a0 AND B
 */
void op_0xa0(int af) 
{
	*cur_block.genp = PM_AND(COND_AL,1,5,5,REG_LSR(6, 8));cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x50;
	cur_block.const1 |= 0x20;
}


/*********a1 AND C
 */
void op_0xa1(int af) 
{
	*cur_block.genp = PM_AND(COND_AL,1,5,5,6);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x50;
	cur_block.const1 |= 0x20;
}


/*********a2 AND D
 */
void op_0xa2(int af) 
{
	*cur_block.genp = PM_AND(COND_AL,1,5,5,REG_LSR(7, 8));cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x50;
	cur_block.const1 |= 0x20;
}


/*********a3 AND E
 */
void op_0xa3(int af) 
{
	*cur_block.genp = PM_AND(COND_AL,1,5,5,7);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x50;
	cur_block.const1 |= 0x20;
}


/*********a4 AND H
 */
void op_0xa4(int af) 
{
	*cur_block.genp = PM_AND(COND_AL,1,5,5,REG_LSR(8, 8));cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x50;
	cur_block.const1 |= 0x20;
}


/*********a5 AND L
 */
void op_0xa5(int af) 
{
	*cur_block.genp = PM_AND(COND_AL,1,5,5,8);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x50;
	cur_block.const1 |= 0x20;
}


/*********a6 AND (HL)
 */
void op_0xa6(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND(COND_AL,1,5,5,0);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x50;
	cur_block.const1 |= 0x20;
}


/*********a7 AND A
 */
void op_0xa7(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_CMP_IMM(COND_AL,5, 0);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x50;
	cur_block.const1 |= 0x20;
}


/*********a8 XOR B
 */
void op_0xa8(int af) 
{
	*cur_block.genp = PM_EOR(COND_AL,1,5,5,REG_LSR(6, 8));cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********a9 XOR C
 */
void op_0xa9(int af) 
{
	*cur_block.genp = PM_EOR(COND_AL,0,5,5,6);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********aa XOR D
 */
void op_0xaa(int af) 
{
	*cur_block.genp = PM_EOR(COND_AL,1,5,5,REG_LSR(7, 8));cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********ab XOR E
 */
void op_0xab(int af) 
{
	*cur_block.genp = PM_EOR(COND_AL,0,5,5,7);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********ac XOR H
 */
void op_0xac(int af) 
{
	*cur_block.genp = PM_EOR(COND_AL,1,5,5,REG_LSR(8, 8));cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********ad XOR L
 */
void op_0xad(int af) 
{
	*cur_block.genp = PM_EOR(COND_AL,0,5,5,8);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********ae XOR (HL)
 */
void op_0xae(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_EOR(COND_AL,1,5,5,0);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********af XOR A
 */
void op_0xaf(int af) 
{
  	*cur_block.genp = PM_EOR(COND_AL,0,5,5,5);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
	cur_block.const1 |= 0x80;
}


/*********b0 OR  B
 */
void op_0xb0(int af) 
{
	*cur_block.genp = PM_ORR(COND_AL,1,5,5,REG_LSR(6, 8));cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********b1 OR  C
 */
void op_0xb1(int af) 
{
	*cur_block.genp = PM_ORR(COND_AL,0,5,5,6);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********b2 OR  D
 */
void op_0xb2(int af) 
{
	*cur_block.genp = PM_ORR(COND_AL,1,5,5,REG_LSR(7, 8));cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********b3 OR  E
 */
void op_0xb3(int af) 
{
	*cur_block.genp = PM_ORR(COND_AL,0,5,5,7);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********b4 OR  H
 */
void op_0xb4(int af) 
{
	*cur_block.genp = PM_ORR(COND_AL,1,5,5,REG_LSR(8, 8));cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********b5 OR  L
 */
void op_0xb5(int af) 
{
	*cur_block.genp = PM_ORR(COND_AL,0,5,5,8);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********b6 OR  (HL)
 */
void op_0xb6(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,1,5,5,0);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********b7 OR  A
 */
void op_0xb7(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_CMP_IMM(COND_AL,5, 0);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********b8 CP  B
 */
void op_0xb8(int af) 
{
	*cur_block.genp = PM_SUB(COND_AL,1,0,5,REG_LSR(6, 8));cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(6, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********b9 CP  C
 */
void op_0xb9(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB(COND_AL,1,0,5,1);cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,1);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********ba CP  D
 */
void op_0xba(int af) 
{
	*cur_block.genp = PM_SUB(COND_AL,1,0,5,REG_LSR(7, 8));cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(7, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********bb CP  E
 */
void op_0xbb(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB(COND_AL,1,0,5,1);cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,1);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********bc CP  H
 */
void op_0xbc(int af) 
{
	*cur_block.genp = PM_SUB(COND_AL,1,0,5,REG_LSR(8, 8));cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,REG_LSR(8, 8));cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********bd CP  L
 */
void op_0xbd(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_SUB(COND_AL,1,0,5,1);cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,1);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********be CP  (HL)
 */
void op_0xbe(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_SUB(COND_AL,1,2,5,0);cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,0);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,2);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,2, IMM_ROTL(0x01, 4) );cur_block.genp++;
			
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********bf CP  A
 */
void op_0xbf(int af) 
{
	*cur_block.genp = PM_SUB(COND_AL,1,0,5,5);cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,5);cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********c0 RET NZ
 */
void op_0xc0(int af) 
{
	if(!IS_CONSTANT(FZ)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FZ );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_NE); /*@bne 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT1(FZ)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} 
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,1, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 8);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,2,1,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,1,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,0,2,REG_LSL(1, 8));cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 6);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,0,0,11, 132, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11, 132, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,0,1,REG_LSL(0, 8));cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,1,0);cur_block.genp++;
		*cur_block.genp = PM_ADD_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
	{linkblock_end(LBADDR_UNKNOWN,0);}
	{linkblock_begin(-3);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 1;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}	
}


/*********c1 POP BC
 */
void op_0xc1(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,1, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 8);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,2,1,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,1,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,2,REG_LSL(1, 8));cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,6,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSL(0, 8));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
}


/*********c2 JP  NZ,%w
 */
void op_0xc2(int af) 
{
	if(!IS_CONSTANT(FZ)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FZ );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_NE); /*@bne 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT1(FZ)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} 
	{patchblock_begin();}
		{temp = READW(cur_block.pc+1);}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
	{linkblock_begin(-1);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 3;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}	
}


/*********c3 JP  %w
 */
void op_0xc3(int af) 
{
	{set_constflags(af);}
	{linkblock_begin(0);} 
	{patchblock_begin();}
		{temp = READW(cur_block.pc+1);}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
}


/*********c4 CALL NZ,%w
 */
void op_0xc4(int af) 
{
	if(!IS_CONSTANT(FZ)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FZ );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_NE); /*@bne 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT1(FZ)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} 
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
		{temp = cur_block.pc+3;}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 10);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	{patchblock_begin();}
		{temp = READW(cur_block.pc+1);}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
	{linkblock_begin(-3);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 3;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}	
}


/*********c5 PUSH BC
 */
void op_0xc5(int af) 
{
	*cur_block.genp = PM_SUB_IMM(COND_AL,1,9,9, 2);cur_block.genp++;
	*cur_block.genp = PM_AND(COND_MI,0,9,9,REG_LSR(9, 16));cur_block.genp++;
	
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 9);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,6,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(6, 8));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,6, 0xff);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(6, 8));cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	

	{/*FIXME: bic          andne 		r9, r9, r9 lsr #16*/}
}


/*********c6 ADD A,%b
 */
void op_0xc6(int af) 
{
	{temp=READB(cur_block.pc + 1);}	
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,5, temp );cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,0);cur_block.genp++;
			*cur_block.genp = PM_TST_IMM(COND_AL,1, 0x10);cur_block.genp++;
			if(temp & 0x10){
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x20);cur_block.genp++;
			}else{
				*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x20);cur_block.genp++;
			}		
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,0, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********c7 RST 0h
 */
void op_0xc7(int af) 
{
	{set_constflags(af);}
	{linkblock_begin(0);} 
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
		{temp = cur_block.pc+1;}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 10);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	{patchblock_begin();}
{/*@		mov		r0, #0x00	*/}
	{linkblock_end(0x00, USE_CASCADING);}
}


/*********c8 RET Z
 */
void op_0xc8(int af) 
{
	if(!IS_CONSTANT(FZ)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FZ );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_EQ); /*beq 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT0(FZ)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} 
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,1, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 8);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,2,1,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,1,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,0,2,REG_LSL(1, 8));cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 6);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,0,0,11, 132, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11, 132, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,0,1,REG_LSL(0, 8));cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,1,0);cur_block.genp++;
		*cur_block.genp = PM_ADD_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
	{linkblock_end(LBADDR_UNKNOWN,0);}
	{linkblock_begin(-3);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 1;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}	
}


/*********c9 RET
 */
void op_0xc9(int af) 
{
	{set_constflags(af);}
	{linkblock_begin(0);} 
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,1, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 8);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,2,1,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,1,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,0,2,REG_LSL(1, 8));cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 6);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,0,0,11, 132, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11, 132, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,0,1,REG_LSL(0, 8));cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,1,0);cur_block.genp++;
		*cur_block.genp = PM_ADD_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
	{linkblock_end(LBADDR_UNKNOWN,0);}
}


/*********ca JP  Z,%w
 */
void op_0xca(int af) 
{
	if(!IS_CONSTANT(FZ)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FZ );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_EQ); /*beq 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT0(FZ)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} 
	{patchblock_begin();}
		{temp = READW(cur_block.pc+1);}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
	{linkblock_begin(-1);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 3;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}	
}


/*********cb CB OPs
 */
void op_0xcb(int af) 
{
	{cbop_generators[READB(cur_block.pc+1)](af);}
}


/*********cc CALL Z,%w
 */
void op_0xcc(int af) 
{
	if(!IS_CONSTANT(FZ)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FZ );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_EQ); /*beq 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT0(FZ)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} 
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
		{temp = cur_block.pc+3;}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 10);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	{patchblock_begin();}
		{temp = READW(cur_block.pc+1);}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
	{linkblock_begin(-3);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 3;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}	
}


/*********cd CALL %w
 */
void op_0xcd(int af) 
{
	{set_constflags(af);}
	{linkblock_begin(0);} 
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
		{temp = cur_block.pc+3;}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 10);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	{patchblock_begin();}
		{temp = READW(cur_block.pc+1);}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
}


/*********ce ADC A,%b
 */
void op_0xce(int af) 
{
	{temp=READB(cur_block.pc + 1);}	
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,5, temp );cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ADD_IMM(COND_NE,0,0,0, 1);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			if(temp!=0xff){
				*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,5, (temp+1) );cur_block.genp++;
			}
			else{
				*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,5, IMM_ROTL(0x01,4) );cur_block.genp++;
			}
		}
		else{
			*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,5, temp );cur_block.genp++;
		}
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,0);cur_block.genp++;
			*cur_block.genp = PM_TST_IMM(COND_AL,1, 0x10);cur_block.genp++;
			if(temp & 0x10){
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x20);cur_block.genp++;
			}else{
				*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x20);cur_block.genp++;
			}		
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,0, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x40;
}


/*********cf RST 8h
 */
void op_0xcf(int af) 
{
	{set_constflags(af);}
	{linkblock_begin(0);} 
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
		{temp = cur_block.pc+1;}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 10);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	{patchblock_begin();}
{/*@		mov		r0, #0x08	*/}
	{linkblock_end(0x08, USE_CASCADING);}
}


/*********d0 RET NC
 */
void op_0xd0(int af) 
{
	if(!IS_CONSTANT(FC)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FC );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_NE); /*@bne 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT1(FC)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} 
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,1, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 8);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,2,1,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,1,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,0,2,REG_LSL(1, 8));cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 6);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,0,0,11, 132, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11, 132, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,0,1,REG_LSL(0, 8));cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,1,0);cur_block.genp++;
		*cur_block.genp = PM_ADD_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
	{linkblock_end(LBADDR_UNKNOWN,0);}
	{linkblock_begin(-3);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 1;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}	
}


/*********d1 POP DE
 */
void op_0xd1(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,1, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 8);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,2,1,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,1,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,2,REG_LSL(1, 8));cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,7,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSL(0, 8));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
}


/*********d2 JP  NC,%w
 */
void op_0xd2(int af) 
{
	if(!IS_CONSTANT(FC)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FC );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_NE); /*@bne 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT1(FC)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} 
	{patchblock_begin();}
		{temp = READW(cur_block.pc+1);}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
	{linkblock_begin(-1);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 3;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}	
}


/*********d3 INVALID
 */
void op_0xd3(int af) 
{
	{cmpl_bailout("Invalid Opcode 0xD3 PC: %04X", cur_block.pc);}
}


/*********d4 CALL NC,%w
 */
void op_0xd4(int af) 
{
	if(!IS_CONSTANT(FC)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FC );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_NE); /*@bne 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT1(FC)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} 
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
		{temp = cur_block.pc+3;}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 10);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	{patchblock_begin();}
		{temp = READW(cur_block.pc+1);}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
	{linkblock_begin(-3);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 3;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}	
}


/*********d5 PUSH DE
 */
void op_0xd5(int af) 
{
	*cur_block.genp = PM_SUB_IMM(COND_AL,1,9,9, 2);cur_block.genp++;
	*cur_block.genp = PM_AND(COND_MI,0,9,9,REG_LSR(9, 16));cur_block.genp++;
	
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 9);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,7,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(7, 8));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,7, 0xff);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(7, 8));cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	

	{/*FIXME: bic          andne 		r9, r9, r9 lsr #16*/}
}


/*********d6 SUB %b
 */
void op_0xd6(int af) 
{
	{temp=READB(cur_block.pc + 1);}	
	*cur_block.genp = PM_SUB_IMM(COND_AL,0,0,5, temp );cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,0);cur_block.genp++;
			*cur_block.genp = PM_TST_IMM(COND_AL,1, 0x10);cur_block.genp++;
			if(temp & 0x10){
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x20);cur_block.genp++;
			}else{
				*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x20);cur_block.genp++;
			}		
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,0, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********d7 RST 10h
 */
void op_0xd7(int af) 
{
	{set_constflags(af);}
	{linkblock_begin(0);} 
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
		{temp = cur_block.pc+1;}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 10);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	{patchblock_begin();}
{/*@		mov		r0, #0x10	*/}
	{linkblock_end(0x10, USE_CASCADING);}
}


/*********d8 RET C
 */
void op_0xd8(int af) 
{
	if(!IS_CONSTANT(FC)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FC );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_EQ); /*beq 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT0(FC)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} 
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,1, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 8);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,2,1,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,1,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,0,2,REG_LSL(1, 8));cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 6);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,0,0,11, 132, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11, 132, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,0,1,REG_LSL(0, 8));cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,1,0);cur_block.genp++;
		*cur_block.genp = PM_ADD_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
	{linkblock_end(LBADDR_UNKNOWN,0);}
	{linkblock_begin(-3);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 1;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}	
}


/*********d9 RETI
 */
void op_0xd9(int af) 
{
	{set_constflags(af);}
 	*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, 1);cur_block.genp++;
	//{}str		r0, [r11, 'IMAo']
	*cur_block.genp = PM_MEM(COND_AL,0,0,0,11, IMEo , 0,1,1,0);cur_block.genp++;
	{linkblock_begin(0);} 
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,1, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 8);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,2,1,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,1,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,0,2,REG_LSL(1, 8));cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 6);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,0,0,11, 132, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11, 132, 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,0,1,REG_LSL(0, 8));cur_block.genp++;
			*cur_block.genp = PM_MOV(COND_AL,0,1,0);cur_block.genp++;
			*cur_block.genp = PM_ADD_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
	{linkblock_end(LBADDR_UNKNOWN,3);} //DAVID
}


/*********da JP  C,%w
 */
void op_0xda(int af) 
{
	if(!IS_CONSTANT(FC)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FC );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_EQ); /*beq 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT0(FC)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} 
	{patchblock_begin();}
		{temp = READW(cur_block.pc+1);}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
	{linkblock_begin(-1);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 3;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}	
}


/*********db INVALID
 */
void op_0xdb(int af) 
{
	{cmpl_bailout("Invalid Opcode 0xDB PC: %04X", cur_block.pc);}
}


/*********dc CALL C,%w
 */
void op_0xdc(int af) 
{
	if(!IS_CONSTANT(FC)) {
  		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,4, FC );cur_block.genp++;
		{set_constflags(af);}
		{insert_skip(COND_EQ); /*beq 'LINK_BLOCK_SIZE - 1' @FIXME*/}
	}
  	else{ // why should anybody make a conditional jump on a constant flag ?
		{set_constflags(af);}
		if(IS_CONSTANT0(FC)){
			{insert_skip(COND_AL); /*b 'LINK_BLOCK_SIZE - 1'*/}
		}
	}
	{linkblock_begin(0);} 
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
		{temp = cur_block.pc+3;}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 10);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	{patchblock_begin();}
		{temp = READW(cur_block.pc+1);}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}
	{linkblock_begin(-3);} //no jump
	{patchblock_begin();}
		{temp = cur_block.pc + 3;}
{/*	mov		r0, 'IMM_ROTL(temp >> 8, 4)'*/}
{/*	orr		r0, r0, 'temp & 0xff'		*/}
	{linkblock_end(temp,USE_CASCADING);}	
}


/*********dd INVALID
 */
void op_0xdd(int af) 
{
	{cmpl_bailout("Invalid Opcode 0xDD PC: %04X", cur_block.pc);}

}


/*********de SBC A,%b
 */
void op_0xde(int af) 
{
	{temp=READB(cur_block.pc + 1);}	
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,0,5, temp );cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_SUB_IMM(COND_NE,0,0,0, 1);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			if(temp!=0xff){
				*cur_block.genp = PM_SUB_IMM(COND_AL,0,0,5, (temp+1) );cur_block.genp++;
			}
			else{
				*cur_block.genp = PM_SUB_IMM(COND_AL,0,0,5, IMM_ROTL(0x01,4) );cur_block.genp++;
			}
		}
		else{
			*cur_block.genp = PM_SUB_IMM(COND_AL,0,0,5, temp );cur_block.genp++;
		}
	}
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,5,0);cur_block.genp++;
			*cur_block.genp = PM_TST_IMM(COND_AL,1, 0x10);cur_block.genp++;
			if(temp & 0x10){
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x20);cur_block.genp++;
			}else{
				*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x20);cur_block.genp++;
			}		
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,0, 0xff);cur_block.genp++;
	if(ALIVE(FZ)) {
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********df RST 18h
 */
void op_0xdf(int af) 
{
	{set_constflags(af);}
	{linkblock_begin(0);} 
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
		{temp = cur_block.pc+1;}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 10);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	{patchblock_begin();}
{/*@		mov		r0, #0x18	*/}
	{linkblock_end(0x18, USE_CASCADING);}
}


/*********e0 LDH (%b),A
 */
void op_0xe0(int af) 
{
	{temp = READB(cur_block.pc+1);}
	if(temp >= 0x10 && temp <= 0x3f) { // sound registers
		*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, temp );cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,1,5);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&sound_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	}else if(temp < 0x80 || temp >= 0xff){ // I/O
		*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, temp );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,5, 0xff);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&ioreg_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	}
	else{ //HIRAM_Write
		*cur_block.genp = PM_MEM(COND_AL,1,0,0,11, 144, 0,1,1,0);cur_block.genp++;
		*cur_block.genp = PM_MEM(COND_AL,0,1,5,0, temp , 0,1,1,0);cur_block.genp++;
		*cur_block.genp = PM_MEM(COND_AL,1,0,0,11, 148 + 4*((temp>>5)&0x03) , 0,1,1,0);cur_block.genp++;
		if(temp & 1){ //FIXME i dont understand immrotl
			*cur_block.genp = PM_ORR_IMM(COND_AL,0,0,0, IMM_ROTL(0x02, (temp & 0x1F)>>1) );cur_block.genp++;
		}else{
			*cur_block.genp = PM_ORR_IMM(COND_AL,0,0,0, IMM_ROTL(0x01, (temp & 0x1F)>>1) );cur_block.genp++;
		}
		*cur_block.genp = PM_MEM(COND_AL,0,0,0,11, 148 + 4*((temp>>5)&0x03) , 0,1,1,0);cur_block.genp++;
	}

	//{}mov		r0, 'READB(cur_block.pc + 1)'	
	//{}orr		r0, r0, 'IMM_ROTL(0xff, 4)'
	//{}and		r1, r5, #0xff
	//{} (POINT)usem	_bl_ mem_write 

}


/*********e1 POP HL
 */
void op_0xe1(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,1, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 8);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,2,1,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,1,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,2,REG_LSL(1, 8));cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,8,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSL(0, 8));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
}


/*********e2 LDH (C),A
 */
void op_0xe2(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,0,0, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(0, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,2,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,5,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_NE,0, 1);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,5, 0xff);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********e3 INVALID
 */
void op_0xe3(int af) 
{
	{cmpl_bailout("Invalid Opcode 0xE3 PC: %04X", cur_block.pc);}

}


/*********e4 INVALID
 */
void op_0xe4(int af) 
{
	{cmpl_bailout("Invalid Opcode 0xE4 PC: %04X", cur_block.pc);}

}


/*********e5 PUSH HL
 */
void op_0xe5(int af) 
{
	*cur_block.genp = PM_SUB_IMM(COND_AL,1,9,9, 2);cur_block.genp++;
	*cur_block.genp = PM_AND(COND_MI,0,9,9,REG_LSR(9, 16));cur_block.genp++;
	
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 9);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,8,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 8));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,8, 0xff);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 8));cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	

	{/*FIXME: bic          andne 		r9, r9, r9 lsr #16*/}
}


/*********e6 AND %b
 */
void op_0xe6(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, READB(cur_block.pc + 1) );cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x50;
	cur_block.const1 |= 0x20;
}


/*********e7 RST 20h
 */
void op_0xe7(int af) 
{
	{set_constflags(af);}
	{linkblock_begin(0);} 
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
		{temp = cur_block.pc+1;}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 10);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	{patchblock_begin();}
{/*@		mov		r0, #0x20	*/}
	{linkblock_end(0x20, USE_CASCADING);}
}


/*********e8 ADD SP,%o
 */
void op_0xe8(int af) 
{
	{temp = (signed char) READB(cur_block.pc + 1); }
	if(temp>=0) {
		*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, temp );cur_block.genp++;
	}else{
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,0,9, (-temp)&0xff );cur_block.genp++;
	}
	if(ALIVE(FC|FH)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x80);cur_block.genp++;
		if(ALIVE(FC)){	
			*cur_block.genp = PM_TST_IMM(COND_AL,0, IMM_ROTL(0x01, 8) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,9,0,9);cur_block.genp++;
			*cur_block.genp = PM_EOR_IMM(COND_AL,0,9,9, temp );cur_block.genp++;
			*cur_block.genp = PM_TST_IMM(COND_AL,9, IMM_ROTL(0x10, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x20);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_MOV(COND_AL,0,9,0);cur_block.genp++;
	{/*FIXME use shl shr here*/}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0xc0;
}


/*********e9 JP  HL
 */
void op_0xe9(int af) 
{
	{set_constflags(af);}
	{linkblock_begin(0);} //@FIXME: not patchable
		*cur_block.genp = PM_MOV(COND_AL,0,1,8);cur_block.genp++;
	{linkblock_end(LBADDR_UNKNOWN, 3);} //DAVID
}


/*********ea LD  (%w),A
 */
void op_0xea(int af) 
{
		{temp = READW(cur_block.pc+1);}
		if(temp >= 0xFF00) { // yes, many roms use LD (%w) instead of special LDH opcode
			{temp&= 0xff;}
	if(temp >= 0x10 && temp <= 0x3f) { // sound registers
		*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, temp );cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,1,5);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&sound_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	}else if(temp < 0x80 || temp >= 0xff){ // I/O
		*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, temp );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,5, 0xff);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&ioreg_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	}
	else{ //HIRAM_Write
		*cur_block.genp = PM_MEM(COND_AL,1,0,0,11, 144, 0,1,1,0);cur_block.genp++;
		*cur_block.genp = PM_MEM(COND_AL,0,1,5,0, temp , 0,1,1,0);cur_block.genp++;
		*cur_block.genp = PM_MEM(COND_AL,1,0,0,11, 148 + 4*((temp>>5)&0x03) , 0,1,1,0);cur_block.genp++;
		if(temp & 1){ //FIXME i dont understand immrotl
			*cur_block.genp = PM_ORR_IMM(COND_AL,0,0,0, IMM_ROTL(0x02, (temp & 0x1F)>>1) );cur_block.genp++;
		}else{
			*cur_block.genp = PM_ORR_IMM(COND_AL,0,0,0, IMM_ROTL(0x01, (temp & 0x1F)>>1) );cur_block.genp++;
		}
		*cur_block.genp = PM_MEM(COND_AL,0,0,0,11, 148 + 4*((temp>>5)&0x03) , 0,1,1,0);cur_block.genp++;
	}
		}else{
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, READB(cur_block.pc+1) );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,0,0, IMM_ROTL(READB(cur_block.pc+2), 4) );cur_block.genp++;
			if(temp >= 0xC000 && temp < 0xD000){ //RAM0
				*cur_block.genp = PM_MEM(COND_AL,1,0,1,11, 0x30, 0,1,1,0);cur_block.genp++;
				*cur_block.genp = PM_MEM(COND_AL,0,1,5,1,0,1,1,1,0);cur_block.genp++;
			} else if(temp >= 0xD000 && temp < 0xE000) { //RAMN
				*cur_block.genp = PM_MEM(COND_AL,1,0,1,11, 0x34, 0,1,1,0);cur_block.genp++;
				*cur_block.genp = PM_MEM(COND_AL,0,1,5,1,0,1,1,1,0);cur_block.genp++;
			
			}else if(temp < 0x8000){ // MBC_WRITE
				*cur_block.genp = PM_MOV(COND_AL,0,1,5);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mbc_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
			}else{
				//if(temp >= 0xFF80 && temp < 0xFFFF) {{cop_end(); err_msg("str a %04X",30, temp ); cop_begin();}}
				//{{cop_end(); err_msg("str a %04X",500, temp ); cop_begin();}} // useless?
				*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(0, 12));cur_block.genp++;
				*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
				*cur_block.genp = PM_MEM(COND_AL,1,0,1,2,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
				*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
				*cur_block.genp = PM_MEM(COND_NE,0,1,5,1,0,1,1,1,0);cur_block.genp++;
				*cur_block.genp = PM_BRA(COND_NE,0, 1);cur_block.genp++;
				*cur_block.genp = PM_AND_IMM(COND_AL,0,1,5, 0xff);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		}
	}
}


/*********eb INVALID
 */
void op_0xeb(int af) 
{
	{cmpl_bailout("Invalid Opcode 0xEB PC: %04X", cur_block.pc);}
}


/*********ec INVALID
 */
void op_0xec(int af) 
{
	{cmpl_bailout("Invalid Opcode 0xEC PC: %04X", cur_block.pc);}

}


/*********ed INVALID
 */
void op_0xed(int af) 
{
	{cmpl_bailout("Invalid Opcode 0xED PC: %04X", cur_block.pc);}
}


/*********ee XOR %b
 */
void op_0xee(int af) 
{
 	*cur_block.genp = PM_EOR_IMM(COND_AL,1,5,5, READB(cur_block.pc + 1) );cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********ef RST 28h
 */
void op_0xef(int af) 
{
	{set_constflags(af);}
	{linkblock_begin(0);} 
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
		{temp = cur_block.pc+1;}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 10);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	{patchblock_begin();}
{/*@		mov		r0, #0x28	*/}
	{linkblock_end(0x28, USE_CASCADING);}
}


/*********f0 LDH A,(%b)
 */
void op_0xf0(int af) 
{
	{temp = READB(cur_block.pc+1);}
	if(temp < 0x10 || (temp > 0x3F && temp < 0x80)) { // I/O Range
			switch(temp) {
				case RI_SC:	{ // Special case is handled trough functioncall
								*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, temp );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&ioreg_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
								*cur_block.genp = PM_MOV(COND_AL,0,5,0);cur_block.genp++;
							break;}
				
				case RI_P1:case RI_SB:case RI_DIV:case RI_TIMA:case RI_TMA:case RI_TAC:case RI_LCDC:{}
				case RI_STAT:case RI_SCY:case RI_SCX:case RI_LY:case RI_LYC:case RI_BGP:case RI_OBP0:{}
				case RI_OBP1:case RI_WY:case RI_WX:case RI_IE:case RI_IF:{
								*cur_block.genp = PM_MEM(COND_AL,1,0,0,11, 144, 0,1,1,0);cur_block.genp++;
								*cur_block.genp = PM_MEM(COND_AL,1,1,5,0, temp , 0,1,1,0);cur_block.genp++;
							break;}
					
				case RI_VBK:case RI_BCPS:case RI_OCPS:case RI_BCPD:case RI_OCPD:case RI_SVBK:case RI_KEY1:{}
				case RI_HDMA1:case RI_HDMA2:case RI_HDMA3:case RI_HDMA4:case RI_HDMA5:{}
					if (hw.cgb) {
								*cur_block.genp = PM_MEM(COND_AL,1,0,0,11, 144, 0,1,1,0);cur_block.genp++;
								*cur_block.genp = PM_MEM(COND_AL,1,1,5,0, temp , 0,1,1,0);cur_block.genp++;
						break;{}}
				default: {}
						*cur_block.genp = PM_MOV_IMM(COND_AL,0,5, 0xff);cur_block.genp++;
				} //
	} else { // Sound and Normal HIRAM	
		if (temp >= 0x10 && temp <= 0x3F) { //Sound Register Range
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&sound_mix)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		}
		//{}Read for Normal/Sound Areas
		*cur_block.genp = PM_MEM(COND_AL,1,0,0,11, 144, 0,1,1,0);cur_block.genp++;
		*cur_block.genp = PM_MEM(COND_AL,1,1,5,0, temp , 0,1,1,0);cur_block.genp++;
	} //
	//{}mov		r0,  'IMM_ROTL(0xff, 4)'
	//{}orr		r0, r0, 'READB(cur_block.pc+1)'
	//{}(POINT)usem	_bl_ mem_read
	//{}mov		r5, r0
}


/*********f1 POP AF
 */
void op_0xf1(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,1, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 8);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 4);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,4,1,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0xf0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,1,5,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,4,0, 0xf0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	*cur_block.genp = PM_MOV(COND_AL,0,5,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
}


/*********f2 LDH A,(C)
 */
void op_0xf2(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0xff);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,0,0, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,5,0);cur_block.genp++;
}


/*********f3 DI
 */
void op_0xf3(int af) 
{
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, 0);cur_block.genp++;
//{}	str		r0, [r11, 'IMAo']
	*cur_block.genp = PM_MEM(COND_AL,0,0,0,11, IMEo , 0,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,0,0,11, HALTo , 0,1,1,0);cur_block.genp++;
}


/*********f4 INVALID
 */
void op_0xf4(int af) 
{
	{cmpl_bailout("Invalid Opcode 0xF4 PC: %04X", cur_block.pc);}

}


/*********f5 PUSH AF
 */
void op_0xf5(int af) 
{
	{set_constflags(0xff);}
	*cur_block.genp = PM_SUB_IMM(COND_AL,1,9,9, 2);cur_block.genp++;
	*cur_block.genp = PM_AND(COND_MI,0,9,9,REG_LSR(9, 16));cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,1, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 8);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,2,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 3);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,4,1,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,5,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,4);cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,5);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

}


/*********f6 OR  %b
 */
void op_0xf6(int af) 
{
	*cur_block.genp = PM_ORR_IMM(COND_AL,1,5,5, READB(cur_block.pc + 1) );cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********f7 RST 30h
 */
void op_0xf7(int af) 
{
	{set_constflags(af);}
	{linkblock_begin(0);} 
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
		{temp = cur_block.pc+1;}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 10);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	{patchblock_begin();}
{/*@		mov		r0, #0x30	*/}
	{linkblock_end(0x30, USE_CASCADING);}
}


/*********f8 LD  HL,SP%o
 */
void op_0xf8(int af) 
{
	{temp = (signed char) READB(cur_block.pc + 1);}
	if(temp>=0){
		*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, temp );cur_block.genp++;
	}else{
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,0,9, (-temp)&0xff );cur_block.genp++;
	}
	
	if(ALIVE(FC|FH)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x80);cur_block.genp++;
		if(ALIVE(FC)){	
			*cur_block.genp = PM_TST_IMM(COND_AL,0, IMM_ROTL(0x01, 8) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR(COND_AL,0,1,0,9);cur_block.genp++;
			*cur_block.genp = PM_EOR_IMM(COND_AL,0,1,1, temp );cur_block.genp++;
			*cur_block.genp = PM_TST_IMM(COND_AL,1, IMM_ROTL(0x10, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x20);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,8,0, IMM_ROTL(0xff, 8) );cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0xc0;
}


/*********f9 LD  SP,HL
 */
void op_0xf9(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,9,8);cur_block.genp++;
}


/*********fa LD  A,(%w)
 */
void op_0xfa(int af) 
{
	{temp = READW(cur_block.pc+1);}
	
	
	if(temp >= 0xFF00) { // // yes, many roms use LD (%w) instead of special LDH opcode
		{temp &= 0xFF;} // prepare to use read_hiram macro
	if(temp < 0x10 || (temp > 0x3F && temp < 0x80)) { // I/O Range
			switch(temp) {
				case RI_SC:	{ // Special case is handled trough functioncall
								*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, temp );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&ioreg_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
								*cur_block.genp = PM_MOV(COND_AL,0,5,0);cur_block.genp++;
							break;}
				
				case RI_P1:case RI_SB:case RI_DIV:case RI_TIMA:case RI_TMA:case RI_TAC:case RI_LCDC:{}
				case RI_STAT:case RI_SCY:case RI_SCX:case RI_LY:case RI_LYC:case RI_BGP:case RI_OBP0:{}
				case RI_OBP1:case RI_WY:case RI_WX:case RI_IE:case RI_IF:{
								*cur_block.genp = PM_MEM(COND_AL,1,0,0,11, 144, 0,1,1,0);cur_block.genp++;
								*cur_block.genp = PM_MEM(COND_AL,1,1,5,0, temp , 0,1,1,0);cur_block.genp++;
							break;}
					
				case RI_VBK:case RI_BCPS:case RI_OCPS:case RI_BCPD:case RI_OCPD:case RI_SVBK:case RI_KEY1:{}
				case RI_HDMA1:case RI_HDMA2:case RI_HDMA3:case RI_HDMA4:case RI_HDMA5:{}
					if (hw.cgb) {
								*cur_block.genp = PM_MEM(COND_AL,1,0,0,11, 144, 0,1,1,0);cur_block.genp++;
								*cur_block.genp = PM_MEM(COND_AL,1,1,5,0, temp , 0,1,1,0);cur_block.genp++;
						break;{}}
				default: {}
						*cur_block.genp = PM_MOV_IMM(COND_AL,0,5, 0xff);cur_block.genp++;
				} //
	} else { // Sound and Normal HIRAM	
		if (temp >= 0x10 && temp <= 0x3F) { //Sound Register Range
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&sound_mix)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		}
		//{}Read for Normal/Sound Areas
		*cur_block.genp = PM_MEM(COND_AL,1,0,0,11, 144, 0,1,1,0);cur_block.genp++;
		*cur_block.genp = PM_MEM(COND_AL,1,1,5,0, temp , 0,1,1,0);cur_block.genp++;
	} //
	}else{
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, READB(cur_block.pc+1) );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,0,0, IMM_ROTL(READB(cur_block.pc+2), 4) );cur_block.genp++;
		if(temp >= 0xC000 && temp < 0xD000){
			*cur_block.genp = PM_MEM(COND_AL,1,0,1,11, 0x30, 0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_MEM(COND_AL,1,1,5,1,0,1,1,1,0);cur_block.genp++;
		} else if(temp >= 0xD000 && temp < 0xE000) { 
			*cur_block.genp = PM_MEM(COND_AL,1,0,1,11, 0x34, 0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_MEM(COND_AL,1,1,5,1,0,1,1,1,0);cur_block.genp++;
		} else if(temp < 0x4000){
			//{{cop_end(); err_msg("ld a %04X",300, temp ); cop_begin();}} // useless?
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(0, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,0, 0xff);cur_block.genp++;
		} else{
			//{{cop_end(); err_msg("ld a %04X",300, temp ); cop_begin();}} // useless?
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(0, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,0,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,5,0, 0xff);cur_block.genp++;
		
		}
	}
}


/*********fb EI
 */
void op_0xfb(int af) 
{
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,0, 1);cur_block.genp++;
//{}	str		r0, [r11, 'IMAo']
	*cur_block.genp = PM_MEM(COND_AL,0,0,0,11, IMEo , 0,1,1,0);cur_block.genp++;
}


/*********fc INVALID
 */
void op_0xfc(int af) 
{
	{cmpl_bailout("Invalid Opcode 0xFC PC: %04X", cur_block.pc);}

}


/*********fd INVALID
 */
void op_0xfd(int af) 
{
	{cmpl_bailout("Invalid Opcode 0xFD PC: %04X", cur_block.pc);}

}


/*********fe CP  %b
 */
void op_0xfe(int af) 
{
	{temp=READB(cur_block.pc+1);}
	*cur_block.genp = PM_SUB_IMM(COND_AL,1,0,5, temp );cur_block.genp++;
	if(ALIVE(FZ | FH | FC)) {
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_MOV_IMM(COND_EQ,0,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FH)){
			*cur_block.genp = PM_EOR_IMM(COND_AL,0,1,5, temp );cur_block.genp++;
			*cur_block.genp = PM_EOR(COND_AL,0,1,1,0);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,1, 0x10);cur_block.genp++;
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSL(1, 1));cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, IMM_ROTL(0x01, 4) );cur_block.genp++;
			
			*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_ASR(1, 4));cur_block.genp++;
		}
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const1 |= 0x40;
}


/*********ff RST 38h
 */
void op_0xff(int af) 
{
	{set_constflags(af);}
	{linkblock_begin(0);} 
		*cur_block.genp = PM_SUB_IMM(COND_AL,0,9,9, 2);cur_block.genp++;
		{temp = cur_block.pc+1;}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(9, 20));cur_block.genp++;
	*cur_block.genp = PM_CMN_IMM(COND_AL,0, IMM_ROTL(0x10, 8) );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 10);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(9, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,9,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,0,1,1,0,2,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,0, 5);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,9);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, temp & 0xff );cur_block.genp++;

	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,0,9, 1);cur_block.genp++;
	*cur_block.genp = PM_MOV_IMM(COND_AL,0,1, (temp >> 8) & 0xff );cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_AL,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;

	{patchblock_begin();}
{/*@		mov		r0, #0x38	*/}
	{linkblock_end(0x38, USE_CASCADING);}
}

/************** This is a generated file! **************/


/*********00 RLC B
 */
void cbop_0x00(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,6, IMM_ROTL(0x7f, 4) );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, IMM_ROTL(0x80, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,1,1,1,REG_LSR(0, 8));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSR(0, 11));cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSL(1, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********01 RLC C
 */
void cbop_0x01(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,6, 0x7f);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0x80);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,1,1,1,REG_LSL(0, 24));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSR(0, 3));cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_ROR(1, 31));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********02 RLC D
 */
void cbop_0x02(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,7, IMM_ROTL(0x7f, 4) );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, IMM_ROTL(0x80, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,1,1,1,REG_LSR(0, 8));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSR(0, 11));cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSL(1, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********03 RLC E
 */
void cbop_0x03(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,7, 0x7f);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, 0x80);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,1,1,1,REG_LSL(0, 24));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSR(0, 3));cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_ROR(1, 31));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********04 RLC H
 */
void cbop_0x04(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,8, IMM_ROTL(0x7f, 4) );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, IMM_ROTL(0x80, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,1,1,1,REG_LSR(0, 8));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSR(0, 11));cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSL(1, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********05 RLC L
 */
void cbop_0x05(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,8, 0x7f);cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, 0x80);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,1,1,1,REG_LSL(0, 24));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR(COND_AL,0,4,4,REG_LSR(0, 3));cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_ROR(1, 31));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********06 RLC (HL)
 */
void cbop_0x06(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(0, 7));cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,0,1,REG_LSL(0, 1));cur_block.genp++;
	if(ALIVE(FC)){
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSL(1, 4));cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,1,0, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********07 RLC A
 */
void cbop_0x07(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(5, 7));cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,5,0,REG_LSL(5, 1));cur_block.genp++;
	if(ALIVE(FC)){
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSL(0, 4));cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********08 RRC B
 */
void cbop_0x08(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,1,0,REG_LSR(6, 9));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	*cur_block.genp = PM_ORR_IMM(COND_CS,1,0,0, 0x80);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSL(0, 8));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********09 RRC C
 */
void cbop_0x09(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,1,0,REG_LSR(0, 1));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	*cur_block.genp = PM_ORR_IMM(COND_CS,1,0,0, 0x80);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,0);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********0a RRC D
 */
void cbop_0x0a(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,1,0,REG_LSR(7, 9));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	*cur_block.genp = PM_ORR_IMM(COND_CS,1,0,0, 0x80);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSL(0, 8));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********0b RRC E
 */
void cbop_0x0b(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,1,0,REG_LSR(0, 1));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	*cur_block.genp = PM_ORR_IMM(COND_CS,1,0,0, 0x80);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,0);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********0c RRC H
 */
void cbop_0x0c(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,1,0,REG_LSR(8, 9));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	*cur_block.genp = PM_ORR_IMM(COND_CS,1,0,0, 0x80);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSL(0, 8));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********0d RRC L
 */
void cbop_0x0d(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,1,0,REG_LSR(0, 1));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	*cur_block.genp = PM_ORR_IMM(COND_CS,1,0,0, 0x80);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,0);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********0e RRC (HL)
 */
void cbop_0x0e(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,1,1,REG_LSR(0, 1));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	*cur_block.genp = PM_ORR_IMM(COND_CS,1,1,1, 0x80);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********0f RRC A
 */
void cbop_0x0f(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,1,5,REG_LSR(5, 1));cur_block.genp++;
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	*cur_block.genp = PM_ORR_IMM(COND_CS,1,5,5, 0x80);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********10 RL  B
 */
void cbop_0x10(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,1,6, IMM_ROTL(0x7f, 4) );cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,1,1,1,REG_LSL(0, 3));cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ORR_IMM(COND_AL,1,1,1, 0x80);cur_block.genp++;
		}
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, IMM_ROTL(0x80, 4) );cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSR(0, 11));cur_block.genp++;
	}
	if(ALIVE(FZ)){
		if(!ALIVE(FC)){
			*cur_block.genp = PM_BIC_IMM(COND_AL,0,4,4, 0xe0);cur_block.genp++;
		}
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSL(1, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********11 RL  C
 */
void cbop_0x11(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(6, 1));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_NE,0,1,1, 0x01);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ORR_IMM(COND_AL,0,1,1, 0x01);cur_block.genp++;
		}
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0x80);cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSR(0, 3));cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,1,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_BIC_IMM(COND_AL,0,4,4, 0xe0);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,1);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********12 RL  D
 */
void cbop_0x12(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,1,7, IMM_ROTL(0x7f, 4) );cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,1,1,1,REG_LSL(0, 3));cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ORR_IMM(COND_AL,1,1,1, 0x80);cur_block.genp++;
		}
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, IMM_ROTL(0x80, 4) );cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSR(0, 11));cur_block.genp++;
	}
	if(ALIVE(FZ)){
		if(!ALIVE(FC)){
			*cur_block.genp = PM_BIC_IMM(COND_AL,0,4,4, 0xe0);cur_block.genp++;
		}
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSL(1, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********13 RL  E
 */
void cbop_0x13(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(7, 1));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_NE,0,1,1, 0x01);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ORR_IMM(COND_AL,0,1,1, 0x01);cur_block.genp++;
		}
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, 0x80);cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSR(0, 3));cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,1,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_BIC_IMM(COND_AL,0,4,4, 0xe0);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,1);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********14 RL  H
 */
void cbop_0x14(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,1,8, IMM_ROTL(0x7f, 4) );cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,1,1,1,REG_LSL(0, 3));cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ORR_IMM(COND_AL,1,1,1, 0x80);cur_block.genp++;
		}
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, IMM_ROTL(0x80, 4) );cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSR(0, 11));cur_block.genp++;
	}
	if(ALIVE(FZ)){
		if(!ALIVE(FC)){
			*cur_block.genp = PM_BIC_IMM(COND_AL,0,4,4, 0xe0);cur_block.genp++;
		}
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSL(1, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********15 RL  L
 */
void cbop_0x15(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(8, 1));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_NE,0,1,1, 0x01);cur_block.genp++;
	}
	else{
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ORR_IMM(COND_AL,0,1,1, 0x01);cur_block.genp++;
		}
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, 0x80);cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSR(0, 3));cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,1,1, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_BIC_IMM(COND_AL,0,4,4, 0xe0);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,1);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********16 RL  (HL)
 */
void cbop_0x16(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(0, 7));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(0, 1));cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_NE,0,0,0, 0x01);cur_block.genp++;
	}
	else{
		*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSL(0, 1));cur_block.genp++;
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ORR_IMM(COND_AL,0,0,0, 0x01);cur_block.genp++;
		}
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSL(1, 4));cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,1,0, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********17 RL  A
 */
void cbop_0x17(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(5, 7));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSL(5, 1));cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,4, 0x10);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_NE,0,5,5, 0x01);cur_block.genp++;
	}
	else{
		*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSL(5, 1));cur_block.genp++;
		if(IS_CONSTANT1(FC)){
			*cur_block.genp = PM_ORR_IMM(COND_AL,0,5,5, 0x01);cur_block.genp++;
		}
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSL(0, 4));cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********18 RR  B
 */
void cbop_0x18(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,1,0,REG_LSR(6, 9));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,4, 0x10);cur_block.genp++;
	}
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_ORR(COND_AL,1,0,0,REG_LSL(1, 3));cur_block.genp++;
	}
	else if(IS_CONSTANT1(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_AL,1,0,0, 0x80);cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSL(0, 8));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********19 RR  C
 */
void cbop_0x19(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,1,0,REG_LSR(0, 1));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,4, 0x10);cur_block.genp++;
	}
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_ORR(COND_AL,1,0,0,REG_LSL(1, 3));cur_block.genp++;
	}
	else if(IS_CONSTANT1(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_AL,1,0,0, 0x80);cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,0);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********1a RR  D
 */
void cbop_0x1a(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,1,0,REG_LSR(7, 9));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,4, 0x10);cur_block.genp++;
	}
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_ORR(COND_AL,1,0,0,REG_LSL(1, 3));cur_block.genp++;
	}
	else if(IS_CONSTANT1(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_AL,1,0,0, 0x80);cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSL(0, 8));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********1b RR  E
 */
void cbop_0x1b(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,1,0,REG_LSR(0, 1));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,4, 0x10);cur_block.genp++;
	}
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_ORR(COND_AL,1,0,0,REG_LSL(1, 3));cur_block.genp++;
	}
	else if(IS_CONSTANT1(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_AL,1,0,0, 0x80);cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,0);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********1c RR  H
 */
void cbop_0x1c(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,1,0,REG_LSR(8, 9));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,4, 0x10);cur_block.genp++;
	}
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_ORR(COND_AL,1,0,0,REG_LSL(1, 3));cur_block.genp++;
	}
	else if(IS_CONSTANT1(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_AL,1,0,0, 0x80);cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSL(0, 8));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********1d RR  L
 */
void cbop_0x1d(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,1,0,REG_LSR(0, 1));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,4, 0x10);cur_block.genp++;
	}
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_ORR(COND_AL,1,0,0,REG_LSL(1, 3));cur_block.genp++;
	}
	else if(IS_CONSTANT1(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_AL,1,0,0, 0x80);cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,0);cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********1e RR  (HL)
 */
void cbop_0x1e(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,1,1,REG_LSR(0, 1));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,4, 0x10);cur_block.genp++;
	}
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_ORR(COND_AL,1,1,1,REG_LSL(0, 3));cur_block.genp++;
	}
	else if(IS_CONSTANT1(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_AL,1,1,1, 0x80);cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********1f RR  A
 */
void cbop_0x1f(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,1,5,REG_LSR(5, 1));cur_block.genp++;
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,4, 0x10);cur_block.genp++;
	}
	if(ALIVE(FC | FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x6f);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_CS,0,4,4, 0x10);cur_block.genp++;
	}
	if(!IS_CONSTANT(FC)){
		*cur_block.genp = PM_ORR(COND_AL,1,5,5,REG_LSL(1, 3));cur_block.genp++;
	}
	else if(IS_CONSTANT1(FC)){
		*cur_block.genp = PM_ORR_IMM(COND_AL,1,5,5, 0x80);cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********20 SLA B
 */
void cbop_0x20(int af) 
{
		if(ALIVE(FC)){
			*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSR(6, 11));cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, IMM_ROTL(0x7f, 4) );cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x10);cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}else{
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, IMM_ROTL(0x7f, 4) );cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_MOV_IMM(COND_AL,0,4, 0x00);cur_block.genp++;
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}
		*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSL(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********21 SLA C
 */
void cbop_0x21(int af) 
{
		if(ALIVE(FC)){
			*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSR(6, 3));cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, 0x7f);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x10);cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}else{
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, 0x7f);cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_MOV_IMM(COND_AL,0,4, 0x00);cur_block.genp++;
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}
		*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSL(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********22 SLA D
 */
void cbop_0x22(int af) 
{
		if(ALIVE(FC)){
			*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSR(7, 11));cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, IMM_ROTL(0x7f, 4) );cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x10);cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}else{
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, IMM_ROTL(0x7f, 4) );cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_MOV_IMM(COND_AL,0,4, 0x00);cur_block.genp++;
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}
		*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSL(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********23 SLA E
 */
void cbop_0x23(int af) 
{
		if(ALIVE(FC)){
			*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSR(7, 3));cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, 0x7f);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x10);cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}else{
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, 0x7f);cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_MOV_IMM(COND_AL,0,4, 0x00);cur_block.genp++;
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}
		*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSL(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********24 SLA H
 */
void cbop_0x24(int af) 
{
		if(ALIVE(FC)){
			*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSR(8, 11));cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, IMM_ROTL(0x7f, 4) );cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x10);cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}else{
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, IMM_ROTL(0x7f, 4) );cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_MOV_IMM(COND_AL,0,4, 0x00);cur_block.genp++;
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}
		*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSL(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********25 SLA L
 */
void cbop_0x25(int af) 
{
		if(ALIVE(FC)){
			*cur_block.genp = PM_MOV(COND_AL,0,4,REG_LSR(8, 3));cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, 0x7f);cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x10);cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}else{
			*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, 0x7f);cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_MOV_IMM(COND_AL,0,4, 0x00);cur_block.genp++;
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}
		*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSL(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********26 SLA (HL)
 */
void cbop_0x26(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSL(0, 1));cur_block.genp++;
		if(ALIVE(FC)){
			*cur_block.genp = PM_MOV(COND_AL,0,4,REG_ASR(1, 4));cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_AND_IMM(COND_AL,1,1,1, 0xff);cur_block.genp++;
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x90);cur_block.genp++;
		}else{
			if(ALIVE(FZ)){
				*cur_block.genp = PM_AND_IMM(COND_AL,1,1,1, 0xff);cur_block.genp++;
				*cur_block.genp = PM_MOV_IMM(COND_AL,0,4, 0x00);cur_block.genp++;
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}	
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********27 SLA A
 */
void cbop_0x27(int af) 
{
		*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSL(5, 1));cur_block.genp++;
		if(ALIVE(FC)){
			*cur_block.genp = PM_MOV(COND_AL,0,4,REG_ASR(5, 4));cur_block.genp++;
			*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x90);cur_block.genp++;
		}else{
			*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
			if(ALIVE(FZ)){
				*cur_block.genp = PM_MOV_IMM(COND_AL,0,4, 0x00);cur_block.genp++;
				*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
			}
		}	
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********28 SRA B
 */
void cbop_0x28(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, IMM_ROTL(0xfe, 4) );cur_block.genp++;
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)){
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,6, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,6,6, IMM_ROTL(0x7F, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSR(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********29 SRA C
 */
void cbop_0x29(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, 0xfe);cur_block.genp++;
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)){
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,6, 0x01);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,6,6, 0x7F);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSR(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********2a SRA D
 */
void cbop_0x2a(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, IMM_ROTL(0xfe, 4) );cur_block.genp++;
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)){
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,7, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,7,7, IMM_ROTL(0x7F, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSR(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********2b SRA E
 */
void cbop_0x2b(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, 0xfe);cur_block.genp++;
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)){
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,7, 0x01);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,7,7, 0x7F);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSR(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********2c SRA H
 */
void cbop_0x2c(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, IMM_ROTL(0xfe, 4) );cur_block.genp++;
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)){
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,8,8, IMM_ROTL(0x7F, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSR(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********2d SRA L
 */
void cbop_0x2d(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, 0xfe);cur_block.genp++;
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)){
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,8, 0x01);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_BIC_IMM(COND_AL,0,8,8, 0x7F);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSR(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********2e SRA (HL)
 */
void cbop_0x2e(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
  	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,0, 0x01);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,0, 0xfe);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, 0x80);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,1,1,REG_LSR(0, 1));cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********2f SRA A
 */
void cbop_0x2f(int af) 
{
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,5, 0x01);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,5, 0xfe);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,0,5, 0x80);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,5,0,REG_LSR(5, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********30 SWAP B
 */
void cbop_0x30(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, IMM_ROTL(0x0f, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,6, IMM_ROTL(0xf0, 4) );cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,1,0,1,REG_LSL(0, 8));cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSR(0, 4));cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}		
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********31 SWAP C
 */
void cbop_0x31(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,6, 0x0f);cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,6, 0xf0);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,1,0,1,REG_LSL(0, 8));cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSR(0, 4));cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********32 SWAP D
 */
void cbop_0x32(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, IMM_ROTL(0x0f, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,7, IMM_ROTL(0xf0, 4) );cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,1,0,1,REG_LSL(0, 8));cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSR(0, 4));cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}		
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********33 SWAP E
 */
void cbop_0x33(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,7, 0x0f);cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,7, 0xf0);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,1,0,1,REG_LSL(0, 8));cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSR(0, 4));cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********34 SWAP H
 */
void cbop_0x34(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, IMM_ROTL(0x0f, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,8, IMM_ROTL(0xf0, 4) );cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,1,0,1,REG_LSL(0, 8));cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSR(0, 4));cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}		
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********35 SWAP L
 */
void cbop_0x35(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,0,8, 0x0f);cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,1,8, 0xf0);cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,1,0,1,REG_LSL(0, 8));cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSR(0, 4));cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********36 SWAP (HL)
 */
void cbop_0x36(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		*cur_block.genp = PM_ORR(COND_AL,0,1,0,REG_LSL(0, 8));cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(1, 4));cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,1,1,1, 0xff);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********37 SWAP A
 */
void cbop_0x37(int af) 
{
		*cur_block.genp = PM_ORR(COND_AL,0,5,5,REG_LSL(5, 8));cur_block.genp++;
		*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSR(5, 4));cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,1,5,5, 0xff);cur_block.genp++;
		if(ALIVE(FZ)) {
			*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x70;
}


/*********38 SRL B
 */
void cbop_0x38(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, IMM_ROTL(0xfe, 4) );cur_block.genp++;
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)){
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,6, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSR(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********39 SRL C
 */
void cbop_0x39(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,6, 0xfe);cur_block.genp++;
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)){
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,6, 0x01);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,6,6, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,6,6,REG_LSR(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********3a SRL D
 */
void cbop_0x3a(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, IMM_ROTL(0xfe, 4) );cur_block.genp++;
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)){
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,7, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSR(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********3b SRL E
 */
void cbop_0x3b(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,7, 0xfe);cur_block.genp++;
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)){
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,7, 0x01);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,7,7, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,7,7,REG_LSR(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********3c SRL H
 */
void cbop_0x3c(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, IMM_ROTL(0xfe, 4) );cur_block.genp++;
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)){
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(0x01, 4) );cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, 0xff);cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSR(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********3d SRL L
 */
void cbop_0x3d(int af) 
{
	*cur_block.genp = PM_AND_IMM(COND_AL,1,0,8, 0xfe);cur_block.genp++;
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
		if(ALIVE(FZ)){
			*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
		}
		if(ALIVE(FC)){
			*cur_block.genp = PM_TST_IMM(COND_AL,8, 0x01);cur_block.genp++;
			*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
		}
	}
	*cur_block.genp = PM_AND_IMM(COND_AL,0,8,8, IMM_ROTL(0xff, 4) );cur_block.genp++;
	*cur_block.genp = PM_ORR(COND_AL,0,8,8,REG_LSR(0, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********3e SRL (HL)
 */
void cbop_0x3e(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,0, 0x01);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,0, 0xfe);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(0, 1));cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********3f SRL A
 */
void cbop_0x3f(int af) 
{
	if(ALIVE(FZ|FC)){
		*cur_block.genp = PM_EOR(COND_AL,0,4,4,4);cur_block.genp++;
	}
	if(ALIVE(FC)){
		*cur_block.genp = PM_TST_IMM(COND_AL,5, 0x01);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_NE,0,4,4, 0x10);cur_block.genp++;
	}
	if(ALIVE(FZ)){
		*cur_block.genp = PM_AND_IMM(COND_AL,1,0,5, 0xfe);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	*cur_block.genp = PM_MOV(COND_AL,0,5,REG_LSR(5, 1));cur_block.genp++;
	cur_block.const0 &= 0x0f;
	cur_block.const1 &= 0x0f;
	cur_block.const0 |= 0x60;
}


/*********40 BIT 0,B
 */
void cbop_0x40(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, IMM_ROTL(1<<0, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********41 BIT 0,C
 */
void cbop_0x41(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, 1<<0 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********42 BIT 0,D
 */
void cbop_0x42(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, IMM_ROTL(1<<0, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********43 BIT 0,E
 */
void cbop_0x43(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, 1<<0 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********44 BIT 0,H
 */
void cbop_0x44(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(1<<0, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********45 BIT 0,L
 */
void cbop_0x45(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, 1<<0 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********46 BIT 0,(HL)
 */
void cbop_0x46(int af) 
{
	if(ALIVE(FZ)){
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,0, 1<<0 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********47 BIT 0,A
 */
void cbop_0x47(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,5, 1<<0 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********48 BIT 1,B
 */
void cbop_0x48(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, IMM_ROTL(1<<1, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********49 BIT 1,C
 */
void cbop_0x49(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, 1<<1 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********4a BIT 1,D
 */
void cbop_0x4a(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, IMM_ROTL(1<<1, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********4b BIT 1,E
 */
void cbop_0x4b(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, 1<<1 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********4c BIT 1,H
 */
void cbop_0x4c(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(1<<1, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********4d BIT 1,L
 */
void cbop_0x4d(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, 1<<1 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********4e BIT 1,(HL)
 */
void cbop_0x4e(int af) 
{
	if(ALIVE(FZ)){
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,0, 1<<1 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********4f BIT 1,A
 */
void cbop_0x4f(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,5, 1<<1 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********50 BIT 2,B
 */
void cbop_0x50(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, IMM_ROTL(1<<2, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********51 BIT 2,C
 */
void cbop_0x51(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, 1<<2 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********52 BIT 2,D
 */
void cbop_0x52(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, IMM_ROTL(1<<2, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********53 BIT 2,E
 */
void cbop_0x53(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, 1<<2 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********54 BIT 2,H
 */
void cbop_0x54(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(1<<2, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********55 BIT 2,L
 */
void cbop_0x55(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, 1<<2 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********56 BIT 2,(HL)
 */
void cbop_0x56(int af) 
{
	if(ALIVE(FZ)){
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,0, 1<<2 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********57 BIT 2,A
 */
void cbop_0x57(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,5, 1<<2 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********58 BIT 3,B
 */
void cbop_0x58(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, IMM_ROTL(1<<3, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********59 BIT 3,C
 */
void cbop_0x59(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, 1<<3 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********5a BIT 3,D
 */
void cbop_0x5a(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, IMM_ROTL(1<<3, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********5b BIT 3,E
 */
void cbop_0x5b(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, 1<<3 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********5c BIT 3,H
 */
void cbop_0x5c(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(1<<3, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********5d BIT 3,L
 */
void cbop_0x5d(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, 1<<3 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********5e BIT 3,(HL)
 */
void cbop_0x5e(int af) 
{
	if(ALIVE(FZ)){
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,0, 1<<3 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********5f BIT 3,A
 */
void cbop_0x5f(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,5, 1<<3 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********60 BIT 4,B
 */
void cbop_0x60(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, IMM_ROTL(1<<4, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********61 BIT 4,C
 */
void cbop_0x61(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, 1<<4 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********62 BIT 4,D
 */
void cbop_0x62(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, IMM_ROTL(1<<4, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********63 BIT 4,E
 */
void cbop_0x63(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, 1<<4 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********64 BIT 4,H
 */
void cbop_0x64(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(1<<4, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********65 BIT 4,L
 */
void cbop_0x65(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, 1<<4 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********66 BIT 4,(HL)
 */
void cbop_0x66(int af) 
{
	if(ALIVE(FZ)){
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,0, 1<<4 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********67 BIT 4,A
 */
void cbop_0x67(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,5, 1<<4 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********68 BIT 5,B
 */
void cbop_0x68(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, IMM_ROTL(1<<5, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********69 BIT 5,C
 */
void cbop_0x69(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, 1<<5 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********6a BIT 5,D
 */
void cbop_0x6a(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, IMM_ROTL(1<<5, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********6b BIT 5,E
 */
void cbop_0x6b(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, 1<<5 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********6c BIT 5,H
 */
void cbop_0x6c(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(1<<5, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********6d BIT 5,L
 */
void cbop_0x6d(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, 1<<5 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********6e BIT 5,(HL)
 */
void cbop_0x6e(int af) 
{
	if(ALIVE(FZ)){
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,0, 1<<5 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********6f BIT 5,A
 */
void cbop_0x6f(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,5, 1<<5 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********70 BIT 6,B
 */
void cbop_0x70(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, IMM_ROTL(1<<6, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********71 BIT 6,C
 */
void cbop_0x71(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, 1<<6 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********72 BIT 6,D
 */
void cbop_0x72(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, IMM_ROTL(1<<6, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********73 BIT 6,E
 */
void cbop_0x73(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, 1<<6 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********74 BIT 6,H
 */
void cbop_0x74(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(1<<6, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}

	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********75 BIT 6,L
 */
void cbop_0x75(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, 1<<6 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********76 BIT 6,(HL)
 */
void cbop_0x76(int af) 
{
	if(ALIVE(FZ)){
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,0, 1<<6 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********77 BIT 6,A
 */
void cbop_0x77(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,5, 1<<6 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********78 BIT 7,B
 */
void cbop_0x78(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, IMM_ROTL(1<<7, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********79 BIT 7,C
 */
void cbop_0x79(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,6, 1<<7 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********7a BIT 7,D
 */
void cbop_0x7a(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, IMM_ROTL(1<<7, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********7b BIT 7,E
 */
void cbop_0x7b(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,7, 1<<7 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********7c BIT 7,H
 */
void cbop_0x7c(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, IMM_ROTL(1<<7, 4) );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********7d BIT 7,L
 */
void cbop_0x7d(int af) 
{
  
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,8, 1<<7 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}

	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********7e BIT 7,(HL)
 */
void cbop_0x7e(int af) 
{
	if(ALIVE(FZ)){
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
		*cur_block.genp = PM_TST_IMM(COND_AL,0, 1<<7 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********7f BIT 7,A
 */
void cbop_0x7f(int af) 
{
	if(ALIVE(FZ)){
		*cur_block.genp = PM_TST_IMM(COND_AL,5, 1<<7 );cur_block.genp++;
		*cur_block.genp = PM_AND_IMM(COND_AL,0,4,4, 0x7f);cur_block.genp++;
		*cur_block.genp = PM_ORR_IMM(COND_EQ,0,4,4, 0x80);cur_block.genp++;
  	}
	cur_block.const0 &= 0x1f;
	cur_block.const1 &= 0x1f;
	cur_block.const0 |= 0x40;
	cur_block.const1 |= 0x20;
}


/*********80 RES 0,B
 */
void cbop_0x80(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<0, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<0, 4) );cur_block.genp++;
}


/*********81 RES 0,C
 */
void cbop_0x81(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<0 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, 1<<0 );cur_block.genp++;
}


/*********82 RES 0,D
 */
void cbop_0x82(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<0, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<0, 4) );cur_block.genp++;
}


/*********83 RES 0,E
 */
void cbop_0x83(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<0 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, 1<<0 );cur_block.genp++;
}


/*********84 RES 0,H
 */
void cbop_0x84(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<0, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<0, 4) );cur_block.genp++;
}


/*********85 RES 0,L
 */
void cbop_0x85(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<0 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, 1<<0 );cur_block.genp++;
}


/*********86 RES 0,(HL)
 */
void cbop_0x86(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, (~(1<<0))&0xff );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********87 RES 0,A
 */
void cbop_0x87(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,5,5, (~(1<<0))&0xff );cur_block.genp++;
}


/*********88 RES 1,B
 */
void cbop_0x88(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<1, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<1, 4) );cur_block.genp++;
}


/*********89 RES 1,C
 */
void cbop_0x89(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<1 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, 1<<1 );cur_block.genp++;
}


/*********8a RES 1,D
 */
void cbop_0x8a(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<1, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<1, 4) );cur_block.genp++;
}


/*********8b RES 1,E
 */
void cbop_0x8b(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<1 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, 1<<1 );cur_block.genp++;
}


/*********8c RES 1,H
 */
void cbop_0x8c(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<1, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<1, 4) );cur_block.genp++;
}


/*********8d RES 1,L
 */
void cbop_0x8d(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<1 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, 1<<1 );cur_block.genp++;
}


/*********8e RES 1,(HL)
 */
void cbop_0x8e(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, (~(1<<1))&0xff );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********8f RES 1,A
 */
void cbop_0x8f(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,5,5, (~(1<<1))&0xff );cur_block.genp++;
}


/*********90 RES 2,B
 */
void cbop_0x90(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<2, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<2, 4) );cur_block.genp++;
}


/*********91 RES 2,C
 */
void cbop_0x91(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<2 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, 1<<2 );cur_block.genp++;
}


/*********92 RES 2,D
 */
void cbop_0x92(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<2, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<2, 4) );cur_block.genp++;
}


/*********93 RES 2,E
 */
void cbop_0x93(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<2 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, 1<<2 );cur_block.genp++;
}


/*********94 RES 2,H
 */
void cbop_0x94(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<2, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<2, 4) );cur_block.genp++;
}


/*********95 RES 2,L
 */
void cbop_0x95(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<2 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, 1<<2 );cur_block.genp++;
}


/*********96 RES 2,(HL)
 */
void cbop_0x96(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, (~(1<<2))&0xff );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********97 RES 2,A
 */
void cbop_0x97(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,5,5, (~(1<<2))&0xff );cur_block.genp++;
}


/*********98 RES 3,B
 */
void cbop_0x98(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<3, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<3, 4) );cur_block.genp++;
}


/*********99 RES 3,C
 */
void cbop_0x99(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<3 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, 1<<3 );cur_block.genp++;
}


/*********9a RES 3,D
 */
void cbop_0x9a(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<3, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<3, 4) );cur_block.genp++;
}


/*********9b RES 3,E
 */
void cbop_0x9b(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<3 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, 1<<3 );cur_block.genp++;
}


/*********9c RES 3,H
 */
void cbop_0x9c(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<3, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<3, 4) );cur_block.genp++;
}


/*********9d RES 3,L
 */
void cbop_0x9d(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<3 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, 1<<3 );cur_block.genp++;
}


/*********9e RES 3,(HL)
 */
void cbop_0x9e(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, (~(1<<3))&0xff );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********9f RES 3,A
 */
void cbop_0x9f(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,5,5, (~(1<<3))&0xff );cur_block.genp++;
}


/*********a0 RES 4,B
 */
void cbop_0xa0(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<4, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<4, 4) );cur_block.genp++;
}


/*********a1 RES 4,C
 */
void cbop_0xa1(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<4 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, 1<<4 );cur_block.genp++;
}


/*********a2 RES 4,D
 */
void cbop_0xa2(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<4, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<4, 4) );cur_block.genp++;
}


/*********a3 RES 4,E
 */
void cbop_0xa3(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<4 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, 1<<4 );cur_block.genp++;
}


/*********a4 RES 4,H
 */
void cbop_0xa4(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<4, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<4, 4) );cur_block.genp++;
}


/*********a5 RES 4,L
 */
void cbop_0xa5(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<4 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, 1<<4 );cur_block.genp++;
}


/*********a6 RES 4,(HL)
 */
void cbop_0xa6(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, (~(1<<4))&0xff );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********a7 RES 4,A
 */
void cbop_0xa7(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,5,5, (~(1<<4))&0xff );cur_block.genp++;
}


/*********a8 RES 5,B
 */
void cbop_0xa8(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<5, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<5, 4) );cur_block.genp++;
}


/*********a9 RES 5,C
 */
void cbop_0xa9(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<5 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, 1<<5 );cur_block.genp++;
}


/*********aa RES 5,D
 */
void cbop_0xaa(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<5, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<5, 4) );cur_block.genp++;
}


/*********ab RES 5,E
 */
void cbop_0xab(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<5 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, 1<<5 );cur_block.genp++;
}


/*********ac RES 5,H
 */
void cbop_0xac(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<5, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<5, 4) );cur_block.genp++;
}


/*********ad RES 5,L
 */
void cbop_0xad(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<5 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, 1<<5 );cur_block.genp++;
}


/*********ae RES 5,(HL)
 */
void cbop_0xae(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, (~(1<<5))&0xff );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********af RES 5,A
 */
void cbop_0xaf(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,5,5, (~(1<<5))&0xff );cur_block.genp++;
}


/*********b0 RES 6,B
 */
void cbop_0xb0(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<6, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<6, 4) );cur_block.genp++;
}


/*********b1 RES 6,C
 */
void cbop_0xb1(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<6 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, 1<<6 );cur_block.genp++;
}


/*********b2 RES 6,D
 */
void cbop_0xb2(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<6, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<6, 4) );cur_block.genp++;
}


/*********b3 RES 6,E
 */
void cbop_0xb3(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<6 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, 1<<6 );cur_block.genp++;
}


/*********b4 RES 6,H
 */
void cbop_0xb4(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<6, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<6, 4) );cur_block.genp++;
}


/*********b5 RES 6,L
 */
void cbop_0xb5(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<6 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, 1<<6 );cur_block.genp++;
}


/*********b6 RES 6,(HL)
 */
void cbop_0xb6(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, (~(1<<6))&0xff );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********b7 RES 6,A
 */
void cbop_0xb7(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,5,5, (~(1<<6))&0xff );cur_block.genp++;
}


/*********b8 RES 7,B
 */
void cbop_0xb8(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<7, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<7, 4) );cur_block.genp++;
}


/*********b9 RES 7,C
 */
void cbop_0xb9(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<7 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,6,6, 1<<7 );cur_block.genp++;
}


/*********ba RES 7,D
 */
void cbop_0xba(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<7, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<7, 4) );cur_block.genp++;
}


/*********bb RES 7,E
 */
void cbop_0xbb(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<7 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,7,7, 1<<7 );cur_block.genp++;
}


/*********bc RES 7,H
 */
void cbop_0xbc(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<7, 4) );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<7, 4) );cur_block.genp++;
}


/*********bd RES 7,L
 */
void cbop_0xbd(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<7 );cur_block.genp++;
		*cur_block.genp = PM_EOR_IMM(COND_AL,0,8,8, 1<<7 );cur_block.genp++;
}


/*********be RES 7,(HL)
 */
void cbop_0xbe(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_AND_IMM(COND_AL,0,1,0, (~(1<<7))&0xff );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********bf RES 7,A
 */
void cbop_0xbf(int af) 
{
		*cur_block.genp = PM_AND_IMM(COND_AL,0,5,5, (~(1<<7))&0xff );cur_block.genp++;
}


/*********c0 SET 0,B
 */
void cbop_0xc0(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<0, 4) );cur_block.genp++;
}


/*********c1 SET 0,C
 */
void cbop_0xc1(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<0 );cur_block.genp++;
}


/*********c2 SET 0,D
 */
void cbop_0xc2(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<0, 4) );cur_block.genp++;
}


/*********c3 SET 0,E
 */
void cbop_0xc3(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<0 );cur_block.genp++;
}


/*********c4 SET 0,H
 */
void cbop_0xc4(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<0, 4) );cur_block.genp++;
}


/*********c5 SET 0,L
 */
void cbop_0xc5(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<0 );cur_block.genp++;
}


/*********c6 SET 0,(HL)
 */
void cbop_0xc6(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,1,0, 1<<0 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********c7 SET 0,A
 */
void cbop_0xc7(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,5,5, 1<<0 );cur_block.genp++;
}


/*********c8 SET 1,B
 */
void cbop_0xc8(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<1, 4) );cur_block.genp++;
}


/*********c9 SET 1,C
 */
void cbop_0xc9(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<1 );cur_block.genp++;
}


/*********ca SET 1,D
 */
void cbop_0xca(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<1, 4) );cur_block.genp++;
}


/*********cb SET 1,E
 */
void cbop_0xcb(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<1 );cur_block.genp++;
}


/*********cc SET 1,H
 */
void cbop_0xcc(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<1, 4) );cur_block.genp++;
}


/*********cd SET 1,L
 */
void cbop_0xcd(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<1 );cur_block.genp++;
}


/*********ce SET 1,(HL)
 */
void cbop_0xce(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,1,0, 1<<1 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********cf SET 1,A
 */
void cbop_0xcf(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,5,5, 1<<1 );cur_block.genp++;
}


/*********d0 SET 2,B
 */
void cbop_0xd0(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<2, 4) );cur_block.genp++;
}


/*********d1 SET 2,C
 */
void cbop_0xd1(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<2 );cur_block.genp++;
}


/*********d2 SET 2,D
 */
void cbop_0xd2(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<2, 4) );cur_block.genp++;
}


/*********d3 SET 2,E
 */
void cbop_0xd3(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<2 );cur_block.genp++;
}


/*********d4 SET 2,H
 */
void cbop_0xd4(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<2, 4) );cur_block.genp++;
}


/*********d5 SET 2,L
 */
void cbop_0xd5(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<2 );cur_block.genp++;
}


/*********d6 SET 2,(HL)
 */
void cbop_0xd6(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,1,0, 1<<2 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********d7 SET 2,A
 */
void cbop_0xd7(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,5,5, 1<<2 );cur_block.genp++;
}


/*********d8 SET 3,B
 */
void cbop_0xd8(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<3, 4) );cur_block.genp++;
}


/*********d9 SET 3,C
 */
void cbop_0xd9(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<3 );cur_block.genp++;
}


/*********da SET 3,D
 */
void cbop_0xda(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<3, 4) );cur_block.genp++;
}


/*********db SET 3,E
 */
void cbop_0xdb(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<3 );cur_block.genp++;
}


/*********dc SET 3,H
 */
void cbop_0xdc(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<3, 4) );cur_block.genp++;
}


/*********dd SET 3,L
 */
void cbop_0xdd(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<3 );cur_block.genp++;
}


/*********de SET 3,(HL)
 */
void cbop_0xde(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,1,0, 1<<3 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********df SET 3,A
 */
void cbop_0xdf(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,5,5, 1<<3 );cur_block.genp++;
}


/*********e0 SET 4,B
 */
void cbop_0xe0(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<4, 4) );cur_block.genp++;
}


/*********e1 SET 4,C
 */
void cbop_0xe1(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<4 );cur_block.genp++;
}


/*********e2 SET 4,D
 */
void cbop_0xe2(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<4, 4) );cur_block.genp++;
}


/*********e3 SET 4,E
 */
void cbop_0xe3(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<4 );cur_block.genp++;
}


/*********e4 SET 4,H
 */
void cbop_0xe4(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<4, 4) );cur_block.genp++;
}


/*********e5 SET 4,L
 */
void cbop_0xe5(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<4 );cur_block.genp++;
}


/*********e6 SET 4,(HL)
 */
void cbop_0xe6(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,1,0, 1<<4 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********e7 SET 4,A
 */
void cbop_0xe7(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,5,5, 1<<4 );cur_block.genp++;
}


/*********e8 SET 5,B
 */
void cbop_0xe8(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<5, 4) );cur_block.genp++;
}


/*********e9 SET 5,C
 */
void cbop_0xe9(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<5 );cur_block.genp++;
}


/*********ea SET 5,D
 */
void cbop_0xea(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<5, 4) );cur_block.genp++;
}


/*********eb SET 5,E
 */
void cbop_0xeb(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<5 );cur_block.genp++;
}


/*********ec SET 5,H
 */
void cbop_0xec(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<5, 4) );cur_block.genp++;
}


/*********ed SET 5,L
 */
void cbop_0xed(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<5 );cur_block.genp++;
}


/*********ee SET 5,(HL)
 */
void cbop_0xee(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,1,0, 1<<5 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********ef SET 5,A
 */
void cbop_0xef(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,5,5, 1<<5 );cur_block.genp++;
}


/*********f0 SET 6,B
 */
void cbop_0xf0(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<6, 4) );cur_block.genp++;
}


/*********f1 SET 6,C
 */
void cbop_0xf1(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<6 );cur_block.genp++;
}


/*********f2 SET 6,D
 */
void cbop_0xf2(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<6, 4) );cur_block.genp++;
}


/*********f3 SET 6,E
 */
void cbop_0xf3(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<6 );cur_block.genp++;
}


/*********f4 SET 6,H
 */
void cbop_0xf4(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<6, 4) );cur_block.genp++;
}


/*********f5 SET 6,L
 */
void cbop_0xf5(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<6 );cur_block.genp++;
}


/*********f6 SET 6,(HL)
 */
void cbop_0xf6(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,1,0, 1<<6 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********f7 SET 6,A
 */
void cbop_0xf7(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,5,5, 1<<6 );cur_block.genp++;
}


/*********f8 SET 7,B
 */
void cbop_0xf8(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, IMM_ROTL(1<<7, 4) );cur_block.genp++;
}


/*********f9 SET 7,C
 */
void cbop_0xf9(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,6,6, 1<<7 );cur_block.genp++;
}


/*********fa SET 7,D
 */
void cbop_0xfa(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, IMM_ROTL(1<<7, 4) );cur_block.genp++;
}


/*********fb SET 7,E
 */
void cbop_0xfb(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,7,7, 1<<7 );cur_block.genp++;
}


/*********fc SET 7,H
 */
void cbop_0xfc(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, IMM_ROTL(1<<7, 4) );cur_block.genp++;
}


/*********fd SET 7,L
 */
void cbop_0xfd(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,8,8, 1<<7 );cur_block.genp++;
}


/*********fe SET 7,(HL)
 */
void cbop_0xfe(int af) 
{
	*cur_block.genp = PM_MOV(COND_AL,0,1,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,1,11,REG_LSL(1, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,1, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,1,1,0,1,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_read)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
	*cur_block.genp = PM_ORR_IMM(COND_AL,0,1,0, 1<<7 );cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_AL,0,0,REG_LSR(8, 12));cur_block.genp++;
	*cur_block.genp = PM_ADD_IMM(COND_AL,0,2,11, 64);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_AL,1,0,0,2,REG_LSL(0, 2),1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_CMP_IMM(COND_AL,0, 0);cur_block.genp++;
	*cur_block.genp = PM_MEM(COND_NE,0,1,1,0,8,1,1,1,0);cur_block.genp++;
	*cur_block.genp = PM_MOV(COND_EQ,0,0,8);cur_block.genp++;
	*cur_block.genp = PM_BRA(COND_EQ,1, cmpl_check_boffset((int)(&mem_write)-(int)(cur_block.genp))/4-2 );cur_block.genp++;
}


/*********ff SET 7,A
 */
void cbop_0xff(int af) 
{
		*cur_block.genp = PM_ORR_IMM(COND_AL,0,5,5, 1<<7 );cur_block.genp++;
}

