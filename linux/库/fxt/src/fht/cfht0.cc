
// MACHINE GENERATED FILE, DO NOT EDIT !
// this file was generated from fht0.cc
#include "complextype.h"
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "aux0/cmult.h"
#include "aux0/sumdiff.h"
#include "aux0/sincos.h"
#include "aux0/constants.h"  // COS_1_PI_8, SIN_1_PI_8
#include "perm/revbinpermute.h"
#include "perm/revbinpermute0.h"

#include <cmath>  // M_PI, M_SQRT1_2


// define to use trig recurrence:
// (and possibly lose some precision, see below)
//#define USE_TRIG_REC
// with type 'long double' slight speed loss on my machine,
// with type 'double' little speed gain.

// tuning parameter:
#if defined USE_TRIG_REC
//#warning 'FYI: fht0(double *, ulong) uses trig recursion'
#endif

// tuning parameter:
#define  INITIAL_RADIX_16  1  // 0 or 1 (default)
//
#if  ( INITIAL_RADIX_16==1 )
//#warning 'FYI: INITIAL_RADIX_16 set in fht0(double *, ulong)'
#else
#warning 'INITIAL_RADIX_16 is NOT SET in fht0(Complex *, ulong)'
#endif


void
fht0_dit(Complex *f, ulong ldn)
// Fast Hartley Transform
// Version for zero padded data:
//   fr[k],fi[k] == 0  for  k=n/2 ... n-1
// ldn := base-2 logarithm of the array length.
// Split-radix decimation in time (DIT) algorithm.
{
    if ( ldn<=2 )
    {
        if ( ldn==1 )  // two point fht
        {
            f[1] = f[0];
        }
        else if ( ldn==2 )  // four point fht
        {
            Complex f0, f2;
            sumdiff(f[0], f[1], f0, f2);
            f[0] = f[1] = f0;
            f[2] = f[3] = f2;
        }
        return;
    }

    const ulong n = (1UL<<ldn);
    revbin_permute0(f, n);

    const Complex *fn = f + n;
    ulong ldk = ldn & 1;
    if ( ldk==0 )    // ldn is multiple of 2  => n is a power of 4
    {
#if  ( INITIAL_RADIX_16==1 )
        for (Complex *fi=f; fi<fn; fi+=16)  // radix-16 step
        {
            sumdiff(fi[0], fi[2]);
            fi[3] = fi[2];
            fi[1] = fi[0];
            sumdiff(fi[4], fi[6]);
            fi[7] = fi[6];
            fi[5] = fi[4];
            sumdiff(fi[8], fi[10]);
            fi[11] = fi[10];
            fi[9] = fi[8];
            sumdiff(fi[12], fi[14]);
            fi[15] = fi[14];
            fi[13] = fi[12];

            Complex f0, f1, f2, f3;
            sumdiff(fi[0], fi[4], f0, f1);
            sumdiff(fi[8], fi[12], f2, f3);
            sumdiff(f0, f2, fi[0], fi[8]);
            sumdiff(f1, f3, fi[4], fi[12]);
            sumdiff(fi[2], fi[6], f0, f1);
            f3 = M_SQRT2 * fi[14];
            f2 = M_SQRT2 * fi[10];
            sumdiff(f0, f2, fi[2], fi[10]);
            sumdiff(f1, f3, fi[6], fi[14]);

            Complex a, b, g0, g1, g2, g3;
            sumdiff(fi[5], fi[7], a, b);
            a *= M_SQRT1_2;
            b *= M_SQRT1_2;
            sumdiff(fi[1], a, f0, f1);
            sumdiff(fi[3], b, g0, g1);
            sumdiff(fi[13], fi[15], a, b);
            a *= M_SQRT1_2;
            b *= M_SQRT1_2;
            sumdiff(fi[9], a, f2, f3);
            sumdiff(fi[11], b, g2, g3);
            double c1 = COS_1_PI_8;  // jjkeep
            double s1 = SIN_1_PI_8;  // jjkeep
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, fi[1], fi[9]);
            sumdiff(g1, b, fi[7], fi[15]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, fi[3], fi[11]);
            sumdiff(f1, b, fi[5], fi[13]);
        }
        ldk = 4;
#else  // INITIAL_RADIX_16
        for (Complex *fi=f; fi<fn; fi+=4)  // radix-4 step
        {
            sumdiff(fi[0], fi[2]);
            fi[3] = fi[2];
            fi[1] = fi[0];
        }
        ldk = 2;
#endif  // INITIAL_RADIX_16
    }
    else          // ldk==1,  ldn is no multiple of 2  => n is no power of 4
    {
        for (Complex *fi=f; fi<fn; fi+=8)  // radix-8 step
        {
            Complex f0, f1;
            sumdiff(fi[0], fi[2], f0, f1);
            Complex s1 = fi[4] * M_SQRT2;
            Complex s2 = fi[6] * M_SQRT2;
            Complex f2, f3;
            sumdiff(fi[4], fi[6], f2, f3);

            sumdiff(f0, f2, fi[0], fi[4]);
            sumdiff(f1, f3, fi[2], fi[6]);
            sumdiff(f0, s1, fi[1], fi[5]);
            sumdiff(f1, s2, fi[3], fi[7]);
        }
        ldk = 3;
    }


    for (  ; ldk<ldn;  ldk+=2)
    {
        ulong k   = 1UL<<ldk;
        ulong kh  = k >> 1;
        ulong k2  = k << 1;
        ulong k3  = k2 + k;
        ulong k4  = k2 << 1;

        for (Complex *fi=f, *gi=fi+kh;  fi<fn;  fi+=k4, gi+=k4)
        {
            Complex f0, f1, f2, f3;
            sumdiff(fi[0], fi[k], f0, f1);
            sumdiff(fi[k2], fi[k3], f2, f3);
            sumdiff(f0, f2, fi[0], fi[k2]);
            sumdiff(f1, f3, fi[k], fi[k3]);

            sumdiff(gi[0], gi[k], f0, f1);
            f3 = M_SQRT2 * gi[k3];
            f2 = M_SQRT2 * gi[k2];
            sumdiff(f0, f2, gi[0], gi[k2]);
            sumdiff(f1, f3, gi[k], gi[k3]);
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

            for (Complex *fi=f+i, *gi=f+k-i;  fi<fn;  fi+=k4, gi+=k4)
            {
                Complex a, b, g0, f0, f1, g1, f2, g2, f3, g3;
                cmult(s2, c2, fi[k], gi[k], b, a);
                sumdiff(fi[0], a, f0, f1);
                sumdiff(gi[0], b, g0, g1);

                cmult(s2, c2, fi[k3], gi[k3], b, a);
                sumdiff(fi[k2], a, f2, f3);
                sumdiff(gi[k2], b, g2, g3);

                cmult(s1, c1, f2, g3, b, a);
                sumdiff(f0, a, fi[0], fi[k2]);
                sumdiff(g1, b, gi[k], gi[k3]);

                cmult(c1, s1, g2, f3, b, a);
                sumdiff(g0, a, gi[0], gi[k2]);
                sumdiff(f1, b, fi[k], fi[k3]);
            }
        }
    }
}
// -------------------------
