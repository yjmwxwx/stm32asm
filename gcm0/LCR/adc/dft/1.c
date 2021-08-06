#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void main() {
  float m,pi,sr,si;

  int rr,ii, n,i;
  n=1000;
  m=100;
  pi=3.141592;    
	for(i=0;i<n;i++){
	   sr=cos(2*pi*i*m/n);
	   si=-sin(2*pi*i*m/n);
	   rr=sr*0x8000;
	   ii=si*0x8000;
	   printf("0x%08X,0x%08X,",rr,ii);
}
	printf("\n");
}
	
