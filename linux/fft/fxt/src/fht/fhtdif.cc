// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/cmult.h"
#include "aux0/sumdiff.h"
#include "aux0/constants.h"  // COS_1_PI_8, SIN_1_PI_8
#include "aux0/sincos.h"
#include "perm/revbinpermute.h"
#include "fxttypes.h"


#include <cmath>  // M_PI, M_SQRT1_2

// tuning parameter:
// define to use trig recurrence:
// (and possibly lose some precision, see below)
//#define USE_TRIG_REC
// with type 'long double' slight speed loss on my machine,
// with type 'double' little speed gain.
//
#if defined USE_TRIG_REC
//#warning 'fht(double *, ulong) uses trig recursion'
#endif

// tuning parameter:
#define  FINAL_RADIX_16  1  // 0 or 1 (default)
//
#if  ( FINAL_RADIX_16==1 )
//#warning 'FYI: FINAL_RADIX_16 set in fht_dif(double *, ulong)'
#else
#warning 'FINAL_RADIX_16 is NOT SET in fht_dif(double *, ulong)'
#endif


void
fht_dif_core(double *f, ulong ldn)
// Decimation in frequency (DIF) FHT.
// Output data is in revbin_permuted order.
// ldn := base-2 logarithm of the array length.
{
    if ( ldn<=2 )
    {
        if ( ldn==1 )  // two point fht
        {
            sumdiff(f[0], f[1]);
        }
        else if ( ldn==2 )  // four point fht
        {
            double f0, f1, f2, f3;
            sumdiff(f[0], f[2], f0, f1);
            sumdiff(f[1], f[3], f2, f3);
            sumdiff(f0, f2, f[0], f[1]);
            sumdiff(f1, f3, f[2], f[3]);
        }
        return;
    }

    const ulong n = (1UL<<ldn);
    const double *fn = f + n;
    ulong ldk = ldn - 2;

#if  ( FINAL_RADIX_16==1 )
    for (  ; ldk>2;  ldk-=2)
#else  // FINAL_RADIX_16
    for (  ; ldk>1;  ldk-=2)
#endif  // FINAL_RADIX_16
    {
        ulong k   = 1UL<<ldk;
        ulong kh  = k >> 1;
        ulong k2  = k << 1;
        ulong k3  = k2 + k;
        ulong k4  = k2 << 1;

        for (double *fi=f, *gi=f+kh;  fi<fn;  fi+=k4, gi+=k4)
        {
            double f0, f1, f2, f3;
            sumdiff(fi[0], fi[k], f0, f1);
            sumdiff(fi[k2], fi[k3], f2, f3);
            sumdiff(f0, f2, fi[0], fi[k2]);
            sumdiff(f1, f3, fi[k], fi[k3]);

            sumdiff(gi[0], gi[k2], f0, f2);
            sumdiff(gi[k], gi[k3], f1, f3);
            gi[k3] = M_SQRT2 * f3;
            gi[k2] = M_SQRT2 * f2;
            sumdiff(f0, f1, gi[0], gi[k]);
        }

        double tt = M_PI_4/(double)kh;  // jjkeep
#if defined USE_TRIG_REC
        double s1 = 0.0,  c1 = 1.0;  // jjkeep
        double al = sin(0.5*tt);  // jjkeep
        al *= (2.0*al);
        double be = sin(tt);  // jjkeep
#endif  // USE_TRIG_REC

        for (ulong i=1; i<kh; i++)
        {
#if defined USE_TRIG_REC
            {
                double t1 = c1;  // jjkeep
                c1 -= (al*t1+be*s1);
                s1 -= (al*s1-be*t1);
            }
#else
            double s1, c1;  // jjkeep
            SinCos(tt*(double)i, &s1, &c1);  // jjkeep
#endif  // USE_TRIG_REC

            double c2, s2;  // jjkeep
            csqr(c1, s1, c2, s2);

            for (double *fi=f+i, *gi=f+k-i;  fi<fn;  fi+=k4, gi+=k4)
            {
                double a, b, g0, f0, f1, g1, f2, g2, f3, g3;

                sumdiff(gi[0], gi[k2], g0, a);
                sumdiff(fi[k], fi[k3], f1, b);
                cmult_inv(c1, s1, b, a, g2, f3);

                sumdiff(fi[0], fi[k2], f0, a);
                sumdiff(gi[k], gi[k3], g1, b);
                cmult_inv(s1, c1, b, a, f2, g3);

                sumdiff(f2, f3, fi[k2], a);
                sumdiff(g2, g3, gi[k2], b);
                cmult_inv(s2, c2, b, a, fi[k3], gi[k3]);

                sumdiff(f0, f1, fi[0], a);
                sumdiff(g0, g1, gi[0], b);
                cmult_inv(s2, c2, b, a, fi[k], gi[k]);
            }
        }
    }


    if ( ldk & 1 )
    {
        for (double *fi=f; fi<fn; fi+=8)  // radix-8 step
        {
            double g0, f0, f1, g1;
            sumdiff(fi[0], fi[4], f0, g0);
            sumdiff(fi[2], fi[6], f1, g1);
            sumdiff(f0, f1);
            sumdiff(g0, g1);
            double s1, c1, s2, c2;
            sumdiff(fi[1], fi[5], s1, c1);
            sumdiff(fi[3], fi[7], s2, c2);
            sumdiff(s1, s2);
            sumdiff(f0, s1, fi[0], fi[1]);
            sumdiff(f1, s2, fi[2], fi[3]);
            c1 *= M_SQRT2;
            c2 *= M_SQRT2;
            sumdiff(g0, c1, fi[4], fi[5]);
            sumdiff(g1, c2, fi[6], fi[7]);
        }
    }
    else
    {
#if  ( FINAL_RADIX_16==1 )
        // ldk == 4
        for (double *fi=f; fi<fn; fi+=16)  // radix-16 step
        {
            double f0, f1, f2, f3;
            sumdiff(fi[0], fi[8], f0, f1);
            sumdiff(fi[4], fi[12], f2, f3);
            sumdiff(f0, f2, fi[0], fi[4]);
            sumdiff(f1, f3, fi[8], fi[12]);

            sumdiff(fi[2], fi[10], f0, f1);
            sumdiff(fi[6], fi[14], f2, f3);
            sumdiff(f0, f2, fi[2], fi[6]);
            sumdiff(f1, f3, fi[10], fi[14]);

            sumdiff(fi[1], fi[9], f0, f1);
            sumdiff(fi[5], fi[13], f2, f3);
            sumdiff(f0, f2, fi[1], fi[5]);
            sumdiff(f1, f3, fi[9], fi[13]);

            sumdiff(fi[3], fi[11], f0, f1);
            sumdiff(fi[7], fi[15], f2, f3);
            sumdiff(f0, f2, fi[3], fi[7]);
            sumdiff(f1, f3, fi[11], fi[15]);

            sumdiff(fi[0], fi[2], f0, f1);
            sumdiff(fi[1], fi[3], f2, f3);
            sumdiff(f0, f2, fi[0], fi[1]);
            sumdiff(f1, f3, fi[2], fi[3]);

            sumdiff(fi[4], fi[6], f0, f1);
            f3 = M_SQRT2 * fi[7];
            f2 = M_SQRT2 * fi[5];
            sumdiff(f0, f2, fi[4], fi[5]);
            sumdiff(f1, f3, fi[6], fi[7]);

            double a, b, g0, g1, g2, g3;
            sumdiff(fi[10], fi[14], a, b);
            a *= M_SQRT1_2;
            b *= M_SQRT1_2;
            sumdiff(fi[8], a, f0, f1);
            sumdiff(fi[12], b, g0, g1);
            sumdiff(fi[11], fi[15], a, b);
            a *= M_SQRT1_2;
            b *= M_SQRT1_2;
            sumdiff(fi[9], a, f2, f3);
            sumdiff(fi[13], b, g2, g3);
            double c1 = COS_1_PI_8;  // jjkeep
            double s1 = SIN_1_PI_8;  // jjkeep
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, fi[8], fi[9]);
            sumdiff(g1, b, fi[14], fi[15]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, fi[12], fi[13]);
            sumdiff(f1, b, fi[10], fi[11]);
        }
#else  // FINAL_RADIX_16
        // ldk == 2
        for (double *fi=f; fi<fn; fi+=4)  // radix-4 step
        {
            double f0, f1, f2, f3;
            sumdiff(fi[0], fi[2], f0, f1);
            sumdiff(fi[1], fi[3], f2, f3);
            sumdiff(f0, f2, fi[0], fi[1]);
            sumdiff(f1, f3, fi[2], fi[3]);
        }
#endif  // FINAL_RADIX_16
    }
}
// -------------------------


void
fht_dif(double *f, ulong ldn)
// Fast Hartley Transform
// Split-radix decimation in frequency (DIF) algorithm.
// ldn := base-2 logarithm of the array length.
{
    if ( ldn<=2 )
    {
        if ( ldn==1 )  // two point fht
        {
            sumdiff(f[0], f[1]);
        }
        else if ( ldn==2 )  // four point fht
        {
            double f0, f1, f2, f3;
            sumdiff(f[0], f[2], f0, f1);
            sumdiff(f[1], f[3], f2, f3);
            sumdiff(f0, f2, f[0], f[2]);
            sumdiff(f1, f3, f[1], f[3]);
        }

        return;
    }

    fht_dif_core(f, ldn);
    revbin_permute(f, 1UL<<ldn);
}
// -------------------------
