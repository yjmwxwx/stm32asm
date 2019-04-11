#include <stdlib.h>    
#include <limits.h>    
#include <stdio.h>    
#include <errno.h>  
int main(int argc,char *argv[])
{
  int offset,S_,I1,I2;
   int imm10,imm11,J1,J2,v,v1,v2;
  int src_addr,dst_addr;
    src_addr = atol(argv[1]);      
    dst_addr = atol(argv[2]);  

   printf ("%x \n",src_addr);
   printf ("%x \n",dst_addr);

   offset = dst_addr-(src_addr+4);
   offset &= 0x1FFFFFF; 

   S_ = (offset & 0x1000000) >> 24;
   I1 = (offset & 0x800000) >> 23;
   I2 = (offset & 0x400000) >> 22;
   imm10 = (offset & 0x3FF000) >> 12;
   imm11 = (offset & 0xFFE) >> 1;
   J1 = (!I1)^S_;
   J2 = (!I2)^S_;

  S_ <<= 26;
  imm10 <<= 16;
  J1 <<= 13;
  J2 <<= 11;

   v = 0xF000D000+S_+imm10+J1+J2+imm11;
	printf("%x \n" ,v);
}


