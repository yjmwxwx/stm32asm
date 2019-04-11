#include <stdio.h>
#include <math.h>


#define M_PI 3.1415926536897932384626
#define K1 0.6072529350088812561694

int main()
{
    int i;
    int bits = 16; // number of bits 
    int mul = (1<<(bits-2));
    
    
    int n = bits; // number of elements. 
    //double c;
    int c;


    for(i=0;i<n;i++)
    {
        c = (atan(pow(2, -i)) *  2048);
        printf("0x%08X,",c);
    }
    
}

