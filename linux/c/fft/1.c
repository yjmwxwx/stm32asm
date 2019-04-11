#include "stdio.h"
#include "math.h"
volatile int
a,b,N;
short
x1_re[N];
short
x1_im[N];
short
x2_re[N];
short
x2_im[N];
short
sine[N+N/4];
unsigned short
result[N];
short
brev[N];
extern void sineinit();
void bit_rev_init(short *br)
{
volatile int bit,rev,tmp1,tmp2,maskl,maskh,m,n,shift;
volatile float x,y;
x = log(N);
y = log(2);
bit = (int)(x/y);
rev = 0;
for (n=0;n<N;n++)
{
for (m=0;m<(bit/2)+0.5;m++)
shift = (bit-((m*2)+1));
maskl = 1<<m;
tmp1 = (n & maskl) << shift;
maskh = N/2>>m;
tmp2 = (n & maskh) >> shift;
rev = rev | tmp1 | tmp2;
}
br[n] = rev * 2;
rev = 0;
}
}
void sineinit(short *si)
{
double rad;
int i;
i = 0;
while (++i < (N + N/4) )
{
rad = (double)(i*2.0*3.141592654/N);
si[i] = (int)(sin(rad)*32768);
}
}
void Print()
{
FILE
*f;
f = fopen("result.txt","w");
if (f == NULL)
printf("Error in opening file 'result.txt'\n");
for(a=0;a<N;a++)
fprintf(f,"\%d\n",x1_re[a]);
fprintf(f,"\n");
for(a=0;a<N;a++)
{
fprintf(f,"\%d\n",result[a]);
}
fclose(f);
}
main()
{
double
rad;
volatile
int A = 305;
volatile
int f = 1;
sineinit(&sine[0]);
bit_rev_init(&brev[0]);
for(a=0;a<N;a++)
x1_re[a] = x1_im[a] = x2_re[a] = x2_im[a] = 0;
for(f=1;f<N;f++)
{
//-----test-----
for(a=0;a<N;a++)
{
rad = (double)((f*a*2.0*3.141592654)/(N));
x1_re[a] = (int)(sin(rad)*A);
/*
if (a != N/2)
x1_re[a] = (((int)(sin(rad)*A+0.5))-1)/2;
else
x1_re[a] = ((int)(sin(rad)*A+0.5))/2;
*/
}
//----test end--
//---calculate radix-2 FFT-----
Rad2fft(&x2_re[0], &brev[0], &sine[0], &x1_re[0], &x1_im[0], &result[0]);
//---Write result to file----
Print();
}
for(;;);
}

