#include <stdio.h>

int x,y,z,i,n;

divide_4q(x,y,n){
   for (i=1; i<=n; i++){
      if (x > 0)
	{
		 if (y > 0)
		{
        	   x = x - y*2^(-i);
         	  z = z + 2^(-i);
		}
		else
		{
        	   x = x + y*2^(-i);
        	   z = z - 2^(-i);
		}
		}
	else
	{        
        	 if (y > 0)
		{
        	    x = x + y*2^(-i);
          	  z = z - 2^(-i);
		}
	
        	 else
		{
          	  x = x - y*2^(-i);
          	  z = z + 2^(-i);
		}
		}	
}
	
   return(z);
}

int main(int argc, char **argv)
{
	x = 1;
	y = 1;
	z = 0;

	
         divide_4q(x,y,  100    )  ;
	printf ("%d  \n",z);
    
}
