#if !defined  HAVE_HAARREVNN_H__
#define       HAVE_HAARREVNN_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


template <typename Type>
void haar_rev_nn(Type *f, ulong ldn)
// Transform with basis:                                                      abs()
//    0: [ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + ]  1/32
//    1: [ + - + - + - + - + - + - + - + - + - + - + - + - + - + - + - + - ]  1/32
//    2: [ +   -   +   -   +   -   +   -   +   -   +   -   +   -   +   -   ]  1/16
//    3: [   +   -   +   -   +   -   +   -   +   -   +   -   +   -   +   - ]  1/16
//    4: [ +       -       +       -       +       -       +       -       ]  1/8
//    5: [   +       -       +       -       +       -       +       -     ]  1/8
//    6: [     +       -       +       -       +       -       +       -   ]  1/8
//    7: [       +       -       +       -       +       -       +       - ]  1/8
//    8: [ +               -               +               -               ]  1/4
//    9: [   +               -               +               -             ]  1/4
//   10: [     +               -               +               -           ]  1/4
//   11: [       +               -               +               -         ]  1/4
//   12: [         +               -               +               -       ]  1/4
//   13: [           +               -               +               -     ]  1/4
//   14: [             +               -               +               -   ]  1/4
//   15: [               +               -               +               - ]  1/4
//   16: [ +                               -                               ]  1/2
//   17: [   +                               -                             ]  1/2
//   18: [     +                               -                           ]  1/2
//   19: [       +                               -                         ]  1/2
//   20: [         +                               -                       ]  1/2
//   21: [           +                               -                     ]  1/2
//   22: [             +                               -                   ]  1/2
//   23: [               +                               -                 ]  1/2
//   24: [                 +                               -               ]  1/2
//   25: [                   +                               -             ]  1/2
//   26: [                     +                               -           ]  1/2
//   27: [                       +                               -         ]  1/2
//   28: [                         +                               -       ]  1/2
//   29: [                           +                               -     ]  1/2
//   30: [                             +                               -   ]  1/2
//   31: [                               +                               - ]  1/2
//
// in-place algorithm
// no normalization
{
//    const ulong n = (1UL<<ldn);
    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        ulong r = 0;
//        for (ulong r=0; r<n; r+=m)  // almost walsh_wak_dif2()
        {
            ulong t1 = r;
            ulong t2 = r + mh;
            for (ulong j=0;  j<mh;  ++j, ++t1, ++t2)
            {
                Type u = f[t1];
                Type v = f[t2];
                f[t1] = u + v;
                f[t2] = u - v;
            }
        }
    }
// =^=
//  revbin_permute(g, n);
//  haar_inplace_nn(g, ldn);
//  revbin_permute(g, n);
}
// -------------------------

template <typename Type>
void inverse_haar_rev_nn(Type *f, ulong ldn)
{
    for (ulong ldm=1; ldm<=ldn; ++ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        ulong r = 0;
//        for (ulong r=0; r<n; r+=m)  // almost walsh_wak_dit2()
        {
            ulong t1 = r;
            ulong t2 = r + mh;
            for (ulong j=0;  j<mh;  ++j, ++t1, ++t2)
            {
                Type u = f[t1] * 0.5;
                Type v = f[t2] * 0.5;
                f[t1] = u + v;
                f[t2] = u - v;
            }
        }
    }
}
// -------------------------



#endif  // !defined HAVE_HAARREVNN_H__
