#include "cordic-16bit.h"
#include <stdio.h>

//Print out sin(x) vs fp CORDIC sin(x)
int main(int argc, char **argv)
{
    int p;
    int s,c;
    int i,aa;    
    for(i=0;i<50;i++)
    {
	aa = i*1000;
	aa = aa/50;
	aa = aa*1570;
	aa = aa/1000;
	aa = aa*16384;
	aa = aa/1000;       

        printf("%d \n", aa);
    }       
}
