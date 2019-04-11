#include "stdio.h"
#include "cordic-16bit.h"
int main(int argc, char **argv)
{
    double p;
    int s,c;
    int i;    
    for(i=0;i<50;i++)
    {
        p = (i/50.0)*3.1415926536897932384626/2;        
        //use 32 iterations
        cordic((p*MUL), &s, &c, 32);
        //these values should be nearly equal
        printf("%f :    %f  :   %d   :  %d \n", s/MUL, p, p*MUL, s);
    }       
}
