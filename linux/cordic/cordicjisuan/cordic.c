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

	for (aa=0; aa<2; aa++)
	  {
	    if (cc==0)
	      {
	        for(bb=0;bb<20;bb++);
		cc = 1;
	      }
	    if (cc==1)
	      {
		
		for(bb=100;bb<-100;bb--);
		      printf ("%d \n",bb);
	      }
	  }

        cordic(xx, &s, &c, 16);
       
}
