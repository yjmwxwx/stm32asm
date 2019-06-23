#include <stdio.h>
#include <math.h>

#define N   16

int main(void)
{
    static double signal[] = 
      {
	0.02,  0.42,  0.71,  0.97,  1.00,  0.97,  0.71,  0.42, 
	0.00, -0.32, -0.71, -0.87, -1.00, -0.87, -0.71, -0.32, 
      };
    int i;
    double s, x, y, amp;

    x = 0;
    y = 0;
    for (i=0; i<N; i++)
      {                                                                                       
        s = signal[i];                                                                      
                                                                                            
        x += cos(2*M_PI*i/N) * s / N;                                                       
        y += sin(2*M_PI*i/N) * s / N;                                                       
                                                                                            
      }                                                                                       
    amp = 2*sqrt(x*x + y*y);

    printf("\n%f\n", amp);

    return 0;
}
