#include "cordic-16bit.h"
#include "stdio.h"
#include <math.h> // for testing only!

//Print out sin(x) vs fp CORDIC sin(x)
int main(int argc, char **argv)
{
    double p,a;
    int s,c,pp,ss,cc;
    int i;    
    for(i=0;i<360;i++)
    {
        p = i;        
	a = p*M_PI/180;
	pp=p;
       cordic((p*MUL), &s, &c, 16);
	ss=sin(a)*32768;
	cc=cos(a)*32768;
        printf("%d   :  %d     %d      %d       %d \n", pp, s, ss, c, cc);
    }       
}