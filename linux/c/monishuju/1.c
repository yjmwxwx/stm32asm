#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main()
{
  int i,fx,fs;
  float pi2;
  pi2 = 6.28318530717959;
  fs = 44800;
  for (i=0; i<256; i++)
      {
	fx  = 1500 * sin(pi2*i*350.0/fs) + 2700 * sin(pi2*i*8400.0/fs) + 4000*sin(pi2*i*18725.0/fs);
	printf("%d,", fx);
	
}
     
}

