#include "stdio.h"
#include "cordic-16bit.h"
int main(int argc, char **argv)
{
    double p;
    int s,c;
    int i;    
    for(i=0;i<16384;i++)
    {
        p = i*(3.1415926536897932384626/2);        
        cordic(p, &s, &c, 16);
        printf("%d \n", s);
    }       
}
