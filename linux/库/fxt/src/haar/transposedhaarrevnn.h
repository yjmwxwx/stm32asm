#if !defined  HAVE_TRANSPOSEDHAARREVNN_H__
#define       HAVE_TRANSPOSEDHAARREVNN_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


template <typename Type>
void transposed_haar_rev_nn(Type *f, ulong ldn)
// Transform with basis (transposed basis of haar_rev_nn()):
//    0: [ + + +   +       +               +                               ]
//    1: [ + -   +   +       +               +                             ]
//    2: [ + + -       +       +               +                           ]
//    3: [ + -   -       +       +               +                         ]
//    4: [ + + +   -               +               +                       ]
//    5: [ + -   +   -               +               +                     ]
//    6: [ + + -       -               +               +                   ]
//    7: [ + -   -       -               +               +                 ]
//    8: [ + + +   +       -                               +               ]
//    9: [ + -   +   +       -                               +             ]
//   10: [ + + -       +       -                               +           ]
//   11: [ + -   -       +       -                               +         ]
//   12: [ + + +   -               -                               +       ]
//   13: [ + -   +   -               -                               +     ]
//   14: [ + + -       -               -                               +   ]
//   15: [ + -   -       -               -                               + ]
//   16: [ + + +   +       +               -                               ]
//   17: [ + -   +   +       +               -                             ]
//   18: [ + + -       +       +               -                           ]
//   19: [ + -   -       +       +               -                         ]
//   20: [ + + +   -               +               -                       ]
//   21: [ + -   +   -               +               -                     ]
//   22: [ + + -       -               +               -                   ]
//   23: [ + -   -       -               +               -                 ]
//   24: [ + + +   +       -                               -               ]
//   25: [ + -   +   +       -                               -             ]
//   26: [ + + -       +       -                               -           ]
//   27: [ + -   -       +       -                               -         ]
//   28: [ + + +   -               -                               -       ]
//   29: [ + -   +   -               -                               -     ]
//   30: [ + + -       -               -                               -   ]
//   31: [ + -   -       -               -                               - ]
//
// in-place algorithm
// no normalization
{
    for (ulong ldm=1; ldm<=ldn; ++ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        ulong r = 0;
//        for (ulong r=0; r<n; r+=m)  // almost wak_walsh_dit2()
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
//  transposed_haar_inplace_nn(g, ldn);
//  revbin_permute(g, n);
}
// -------------------------

template <typename Type>
void inverse_transposed_haar_rev_nn(Type *f, ulong ldn)
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
                Type u = f[t1] * 0.5;
                Type v = f[t2] * 0.5;
                f[t1] = u + v;
                f[t2] = u - v;
            }
        }
    }
}
// -------------------------


#endif  // !defined HAVE_TRANSPOSEDHAARREVNN_H__
