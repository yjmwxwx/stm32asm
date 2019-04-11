#include <fftw3.h>
#include <stdio.h>
#include <math.h>

#define ARRAY_SIZE(x) (sizeof((x))/sizeof(*(x)))

int main(void)
{
  int i;
    static double signal[] = 
      {
	0.3535, 0.3535, 0.6464, 1.0607, 0.3535, -1.0607, -1.3535, -0.3535,
      };
    fftw_complex spectrum[ARRAY_SIZE(signal)/2+1];
    double signal2[ARRAY_SIZE(signal)];
    fftw_plan plan_fwd, plan_bwd;

    plan_fwd = fftw_plan_dft_r2c_1d(ARRAY_SIZE(signal), signal, spectrum, FFTW_ESTIMATE);
    plan_bwd = fftw_plan_dft_c2r_1d(ARRAY_SIZE(signal2), spectrum, signal2, FFTW_ESTIMATE);

    for (i=0; i<ARRAY_SIZE(signal); ++i)
      printf("% 6.2f\n", signal[i]);

    printf("\n");

    fftw_execute(plan_fwd);

    for (i=0; i<ARRAY_SIZE(spectrum); ++i)
      printf("% 6.2f + j % 6.2f\n", spectrum[i][0], spectrum[i][1]);

    printf("\n");

    spectrum[0][0] = 0;
    spectrum[0][1] = 0;
    for (i = 2; i<ARRAY_SIZE(spectrum); ++i)
      {
        spectrum[i][0] = 0;
        spectrum[i][1] = 0;
      }

    for (i=0; i<ARRAY_SIZE(spectrum); ++i)
      printf("% 6.2f + j % 6.2f\n", spectrum[i][0], spectrum[i][1]);

    printf("\n");

    fftw_execute(plan_bwd);

    for (i=0; i<ARRAY_SIZE(signal2); ++i)
      printf("% 6.2f\n", signal2[i]);

    fftw_destroy_plan(plan_bwd);
    fftw_destroy_plan(plan_fwd);

    return 0;
}
