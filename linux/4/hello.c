#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cordic-32bit.h"

//Print out sin(x) vs fp CORDIC sin(x)
int main(int argc, char **argv)
{
    double p;
    int s,c;
    int i;    
    for(i=0;i<1024;i++)
    {
        p = (i/1024.0)*M_PI/2;        
        //use 32 iterations
        cordic((p*MUL), &s, &c, 32);
        //these values should be nearly equal
	printf("%f\n", s/MUL);
    }       
}

