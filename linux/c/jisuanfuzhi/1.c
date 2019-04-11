#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int lBufOutArray[] = {
	0x0065FF9F,0xFF2701DD,0xFC95FE17,0x0035FEF5,
	0x0648FF62,0xFB9D0000,0xFE62001B,0x0035FD6B,
	0xFE3FF8B0,0x0F430000,0xF5BF0000,0x01E40339, 
	0x08A70000,0xF78B01F5,0x02E0FE0B,0xFE71FEE9,
	0x0065FEC0,0xFFBF01DD,0x01B9FF8F,0x017405F3 ,
	0x03B5FE74,0x008F01E9,0xF8CB025F,0x0423FDA0 ,
	0x03B50584,0x013501E9,0xFE4F0075,0xF6DF0000 ,
	0xFE1BFBA8,0x0135FEEE,0xFC0D0075,0x03560078 ,
	0xFDFE0061,0xFFBFFE2C,0x0380FF8F,0xFF92001E ,
	0x02EA0000,0x0771FEE2,0xFF0EFF8A,0xFE4BFDAD,
	0xFDEA082D,0xFCCDF7D3,0xF6C9FEFC,0xFFABFC08, 
	0x04B60191,0xFD030000,0x06DAFCF3,0xFDBCFE7A, 
	0x012F0000,0x008D01D8,0x03800070,0xFF92001E, 
	0x00000000,0x00000000,0x00000000,0x00000000, 
	0x00000000, 0x00000000,0x00000000,0x00000000, 
	0x00000000,0x00000000,0x00000000,0x00000000};
int lBufMagArray[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		      ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int main()

{
     signed short lX,lY;
     float X,Y,Mag;
     unsigned short i;
	long NPT;
	NPT = 256;
     for(i=0; i<NPT/2; i++)
     {
         lX  = (lBufOutArray[i] << 16) >> 16;
         lY  = (lBufOutArray[i] >> 16);
         X = NPT * ((float)lX) / 32768;
         Y = NPT * ((float)lY) / 32768;
         Mag = sqrt(X * X + Y * Y) / NPT;
         if(i == 0)
             lBufMagArray[i] = (unsigned long)(Mag * 32768);
         else
             lBufMagArray[i] = (unsigned long)(Mag * 65536);
	printf("0x%08x      0x%08x      0x%08x      0x%08x   0x%08x \n", i,  Mag, X, Y, lBufMagArray[i] );
     }

	printf("0x%08x,", i);
     
}

