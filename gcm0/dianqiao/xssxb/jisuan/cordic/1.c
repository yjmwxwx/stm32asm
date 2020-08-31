#include "cordic-16bit.h"
#include "stdio.h"
#include <math.h> // for testing only!

//Print out sin(x) vs fp CORDIC sin(x)
int main(int argc, char **argv)
{
    double p;
    int s,c,ss,cc,pp;
    int i;    
    for(i=0;i<9000;i++)
    {
        p = (i/9000.0)*M_PI/2;        
        //use 32 iterations
	pp=p*32768;
        cordic((p*MUL), &s, &c, 16);
        //these values should be nearly equal
	ss=sin(p)*32768;
	cc=cos(p)*32768;
        printf("%d   :  %d     %d       %d       %d \n", pp, s, ss, c, cc);
    }       
}