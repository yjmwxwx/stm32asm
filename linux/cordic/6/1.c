#include "stdio.h"
int main()
{
	long a, b ;
	a = 0xffffffffffffffff;
	b = 0xffffffffffffffff;
	a = a * b; 
        printf("%d\n", a );    
}
