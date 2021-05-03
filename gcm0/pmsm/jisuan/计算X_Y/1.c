#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void main() {
  double x,p,y,i;

  int jiaodu,rr,ii,n;
   n = 60;
for(i=0;i<n;i=i+0.03)
    {
        p = i*3.1415926536897932384626/180;
        x = (sin(p)* cos(0))/ (sin(1.0471975) * cos(0));  
	  y = (cos(p) - (x * cos(1.0471975))) / cos(0);   
	 rr = x*0x8000;
	 ii = y*0x8000;
	//printf ("%f,%f\n",x,y);
       printf("0x%04X,0x%04X,", rr,ii);
    }    
	printf("\n");

	
	
}
	
