#include <stdio.h>
#include <math.h>
int main()
{
    int i;
    int n = 16; 
    int c;
    for(i=0;i<n;i++)
    {
        c = (atan(pow(2, -i)) *  32768);
        printf("0x%08X,",c);
    }
    
}

