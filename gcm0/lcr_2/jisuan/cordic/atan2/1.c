#include "cordic-16bit.h"
#include "stdio.h"
#include <math.h> // for testing only!

//Print out sin(x) vs fp CORDIC sin(x)
int main(int argc, char **argv)
{
    double p,a;
    int s,c,jj,x,y,jiaodu;
    int i;    
    for(i=0;i<360;i++)
    {

        p = i;        
	a = p*M_PI/180;
	x=sin(a)*180/3.1415926;
	y=cos(a)*180/3.1415926;

       cordic((x*MUL),(y*MUL), &jiaodu, &s, &c, 16);
	jj=atan2(y,x)*180/3.1415926;
	jiaodu = jiaodu/32768;
        printf("%d   %d    %d    :   %d   :  %d    \n", i, x, y, jj,  jiaodu);
    }       
}