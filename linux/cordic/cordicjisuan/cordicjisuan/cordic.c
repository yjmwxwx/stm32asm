#include <stdio.h>
#include "cordic-16bit.h"

//Print out sin(x) vs fp CORDIC sin(x)
int main(int argc, char **argv)
{
    double p;
    int s,c;
    int i; 
    int xx,aa,bb,cc;  
    cc = 0;
    bb = 0;
    aa = 0;

    for(i=-80;i<80;i++)
    {
        cordic(i, &s, &c, 16);
        printf("%d   %d  \n", i, s );
    }       
}
