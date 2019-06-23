#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void main() {
  double pi2,sr,si;

  int rr,ii, n,i;
  n=8;
  pi2 = 6.28318530717959;    
	for(i=0;i<n/2;i++){
	   sr=cos(pi2*i/n);
	   si=-sin(pi2*i/n);
	    rr=sr*1024;
	    ii=si*1024;
       printf("0x%04X,0x%04X,",rr,ii);
}
	printf("\n");
}
	
