
#include "fxttypes.h"
#include "aux0/sincos.h"
#include "perm/revbinpermute.h"

#include <cmath>


//#define TEST_TB_FHT

#if defined TEST_TB_FHT
    printf("\n FHT_TABLE: test mode on ! \n");
#endif

void
table_fht(double *fr, ulong ldn, double *cosval, double *sinval)
//
// Fast Hartley Transform using sin/cos tables
// ldn := base-2 logarithm of the array length
//
//  call make_sincos_table(n, n/8, *sinval, *cosval)
//  before call to this function !
//
//  not worth the trouble !
//  performance is less than 1% better
//  than normal FHT
//
// note: integrate table-versions in all trigonometric transforms
// note:  ... selectable by #defines
{
    const long n=(1UL<<ldn);

    long i,k,k1,k2,k3,k4,kx;
    double *fi,*fn,*gi;
    if (ldn<=1)
    {
        if (ldn==1)  // two point fht
        {
            double tt=fr[0];
            fr[0]+=fr[1];
            fr[1]=tt-fr[1];
        }

        return;
    }

    revbin_permute(fr,n);

    k = ldn&1;
    if (k==0)    /* ldn is multiple of 2  => n is a power of 4 */
    {
        for (fi=fr,fn=fr+n;fi<fn;fi+=4)
        {
            double f0,f1,f2,f3;

            f1     = fi[0] -fi[1] ;
            f0     = fi[0] +fi[1] ;
            f3     = fi[2] -fi[3] ;
            f2     = fi[2] +fi[3] ;

            fi[2]  = (f0-f2);
            fi[0]  = (f0+f2);
            fi[3]  = (f1-f3);
            fi[1]  = (f1+f3);
        }
    }
    else          /* k==1,  ldn is no multiple of 2  => n is no power of 4 */
    {
        for (fi=fr,fn=fr+n,gi=fi+1;fi<fn;fi+=8,gi+=8)
        {
            double s1,c1,s2,c2,s3,c3,s4,c4,g0,f0,f1,g1,f2,g2,f3,g3;

            c1     = fi[0]  - gi[0] ;
            s1     = fi[0]  + gi[0] ;
            c2     = fi[2]  - gi[2] ;
            s2     = fi[2]  + gi[2] ;
            c3     = fi[4]  - gi[4] ;
            s3     = fi[4]  + gi[4] ;
            c4     = fi[6]  - gi[6] ;
            s4     = fi[6]  + gi[6] ;

            f1     = (s1 - s2);
            f0     = (s1 + s2);
            g1     = (c1 - c2);
            g0     = (c1 + c2);
            f3     = (s3 - s4);
            f2     = (s3 + s4);
            g3     = M_SQRT2*c4;
            g2     = M_SQRT2*c3;

            fi[4]  = f0 - f2;
            fi[0]  = f0 + f2;
            fi[6]  = f1 - f3;
            fi[2]  = f1 + f3;
            gi[4]  = g0 - g2;
            gi[0]  = g0 + g2;
            gi[6]  = g1 - g3;
            gi[2]  = g1 + g3;
        }
    }

    if (n<16)
        return;

    do
    {
        k  += 2;
        k1  = 1UL  << k;
        k2  = k1 << 1;
        k4  = k2 << 1;
        k3  = k2 + k1;
        kx  = k1 >> 1;
        fi  = fr;
        gi  = fi + kx;
        fn  = fr + n;

        do
        {
            double g0,f0,f1,g1,f2,g2,f3,g3;

            f1      = fi[0]  - fi[k1];
            f0      = fi[0]  + fi[k1];
            f3      = fi[k2] - fi[k3];
            f2      = fi[k2] + fi[k3];

            fi[k2]  = f0     - f2;
            fi[0]   = f0     + f2;
            fi[k3]  = f1     - f3;
            fi[k1]  = f1     + f3;

            g1      = gi[0]  - gi[k1];
            g0      = gi[0]  + gi[k1];
            g3      = M_SQRT2  * gi[k3];
            g2      = M_SQRT2  * gi[k2];

            gi[k2]  = g0     - g2;
            gi[0]   = g0     + g2;
            gi[k3]  = g1     - g3;
            gi[k1]  = g1     + g3;

            gi     += k4;
            fi     += k4;
        }
        while (fi<fn);


        int nx=n/8/kx;

        for (i=1;i<kx;i++)
        {
            double s1,c1, c2,s2;

            {
                int index = nx*i;
                c1 = cosval[index];
                s1 = sinval[index];

#if defined TEST_TB_FHT
                SinCos(arg=M_PI_4*i/kx, &s2, &c2);
                if (s1!=s2)  printf("\n YUCK ! \n");
#endif
                // algebra for double angle
                c2 = c1*c1 - s1*s1;
                s2 = 2*(c1*s1);

                /*
                   // slower than algebra !
                   index<<=1;
                   c2 = cosval[index];
                   s2 = sinval[index];
                */
            }

            fn = fr +n;
            fi = fr +i;
            gi = fr +k1-i;

            do
            {
            double a,b,g0,f0,f1,g1,f2,g2,f3,g3;

                b       = s2*fi[k1] - c2*gi[k1];
                a       = c2*fi[k1] + s2*gi[k1];
                f1      = fi[0]     - a;
                f0      = fi[0]     + a;
                g1      = gi[0]     - b;
                g0      = gi[0]     + b;
                b       = s2*fi[k3] - c2*gi[k3];
                a       = c2*fi[k3] + s2*gi[k3];
                f3      = fi[k2]    - a;
                f2      = fi[k2]    + a;
                g3      = gi[k2]    - b;
                g2      = gi[k2]    + b;
                b       = s1*f2     - c1*g3;
                a       = c1*f2     + s1*g3;
                fi[k2]  = f0        - a;
                fi[0]   = f0        + a;
                gi[k3]  = g1        - b;
                gi[k1]  = g1        + b;
                b       = c1*g2     - s1*f3;
                a       = s1*g2     + c1*f3;
                gi[k2]  = g0        - a;
                gi[0]   = g0        + a;
                fi[k3]  = f1        - b;
                fi[k1]  = f1        + b;
                gi     += k4;
                fi     += k4;
            }
            while (fi<fn);
        }
    }
    while (k4<n);
}
