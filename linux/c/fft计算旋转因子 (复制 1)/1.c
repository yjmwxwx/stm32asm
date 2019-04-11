#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void main() {
  float pi,sr,si;

  int rr,ii, n,i;
  n=8;
  pi=3.1415927;    
	for(i=0;i<n/2;i++){
	   sr=cos(2*pi*i/n);
	   si=-sin(2*pi*i/n);
	rr=sr*32768;
	ii=si*32768;
       printf("%04X,%04X,",rr,ii);
}
	printf("\n");
}
	
