#include <stdio.h>
#include <stdlib.h>

void main()
{
int m = 40, n =180,i;
int aa[2400] = {0};
for(i=0;i<n;i++) 
{
   aa[i]= ((2*3.1415926535*i/n)+1)*(m-2)/2+1.5;
   printf("%d\n", aa[i]);
}
}
