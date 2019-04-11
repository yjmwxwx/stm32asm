#if !defined  HAVE_PREFIX_TRANSFORM_H__
#define       HAVE_PREFIX_TRANSFORM_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/bithigh.h"

#include "aux1/copy.h"

#include "restrict.h"
#include "fxtalloca.h"
#include "fxttypes.h"


template <typename Type>
void prefix_transform(Type *f, ulong ldn)
// Prefix transform: let F[] be the transform of f[], then
// F[k] = sum( j \in P(k),  f[j] )  where P(k) is the set of prefixes of k.
//
// Transform with basis:
//
//    0: [ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + ]
//    1: [   +   +   +   +   +   +   +   +   +   +   +   +   +   +   +   + ]
//    2: [     +       +       +       +       +       +       +       +   ]
//    3: [       +       +       +       +       +       +       +       + ]
//    4: [         +               +               +               +       ]
//    5: [           +               +               +               +     ]
//    6: [             +               +               +               +   ]
//    7: [               +               +               +               + ]
//    8: [                 +                               +               ]
//    9: [                   +                               +             ]
//   10: [                     +                               +           ]
//   11: [                       +                               +         ]
//   12: [                         +                               +       ]
//   13: [                           +                               +     ]
//   14: [                             +                               +   ]
//   15: [                               +                               + ]
//   16: [                                 +                               ]
//   17: [                                   +                             ]
//   18: [                                     +                           ]
//   19: [                                       +                         ]
//   20: [                                         +                       ]
//   21: [                                           +                     ]
//   22: [                                             +                   ]
//   23: [                                               +                 ]
//   24: [                                                 +               ]
//   25: [                                                   +             ]
//   26: [                                                     +           ]
//   27: [                                                       +         ]
//   28: [                                                         +       ]
//   29: [                                                           +     ]
//   30: [                                                             +   ]
//   31: [                                                               + ]
//
{
    for (ulong ldm=1; ldm<=ldn; ++ldm)
    {
        const ulong mh = 1UL << (ldm-1);
        for (ulong i=0; i<mh; ++i)  f[i+mh] += f[i];
    }
}
// -------------------------

template <typename Type>
void inverse_prefix_transform(Type *f, ulong ldn)
// Inverse of prefix_transform().
// Transform with basis:
//
//    0: [ + - -   -       -               -                               ]
//    1: [   +   -   -       -               -                             ]
//    2: [     +       -       -               -                           ]
//    3: [       +       -       -               -                         ]
//    4: [         +               -               -                       ]
//    5: [           +               -               -                     ]
//    6: [             +               -               -                   ]
//    7: [               +               -               -                 ]
//    8: [                 +                               -               ]
//    9: [                   +                               -             ]
//   10: [                     +                               -           ]
//   11: [                       +                               -         ]
//   12: [                         +                               -       ]
//   13: [                           +                               -     ]
//   14: [                             +                               -   ]
//   15: [                               +                               - ]
//   16: [                                 +                               ]
//   17: [                                   +                             ]
//   18: [                                     +                           ]
//   19: [                                       +                         ]
//   20: [                                         +                       ]
//   21: [                                           +                     ]
//   22: [                                             +                   ]
//   23: [                                               +                 ]
//   24: [                                                 +               ]
//   25: [                                                   +             ]
//   26: [                                                     +           ]
//   27: [                                                       +         ]
//   28: [                                                         +       ]
//   29: [                                                           +     ]
//   30: [                                                             +   ]
//   31: [                                                               + ]
//
{
    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        const ulong mh = 1UL << (ldm-1);
        for (ulong i=0; i<mh; ++i)  f[i+mh] -= f[i];
    }
}
// -------------------------


template <typename Type>
inline void slow_prefix_convolution(const Type *f, const Type *g, ulong ldn, Type *h)
// Compute the prefix convolution h[] of f[] and g[]:
//  h[k] = sum(j \in P(k),  f[k]*g[j]+f[j]*g[k]) - f[k]*g[k]
// where P(k) is the set of prefixes of k.
// Result written to h[].
// Complexity is O(n*log(n))
{
    const ulong n = 1UL << ldn;
    for (ulong k=0; k<n; ++k)  h[k] = f[k] * g[k];
    for (ulong k=1; k<n; ++k)
    {
        ulong j = k;
        do
        {
            j ^= highest_one(j);
            h[k] += f[k] * g[j];
            h[k] += f[j] * g[k];
        }
        while ( j );
    }
}
// -------------------------

template <typename Type>
inline void slow_prefix_convolution(const Type *f, Type *g, ulong ldn)
// Result written to g[].
{
    const ulong n = 1UL << ldn;
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_prefix_convolution(f, g, ldn, h);
    acopy(h, g, n);
}
// -------------------------

template <typename Type>
inline void prefix_convolution(Type * restrict f, Type * restrict g, ulong ldn)
// Compute the prefix convolution h[] of f[] and g[]:
//  h[k] = sum(j \in P(k),  f[k]*g[j]+f[j]*g[k]) - f[k]*g[k]
// where P(k) is the set of prefixes of k.
// Result written to g[].
// Complexity is O(n)
// Semi-symbolic scheme where (A,B,...,F) denotes (10,11,...,15):
// [0 1 2 3 4 5 6 7 8 9 A B C D E F]
// [1 1   3   5   7   9   B   D   F]
// [2   2       6       A       E  ]
// [3 3   3       7       B       F]
// [4       4               C      ]
// [5 5       5               D    ]
// [6   6       6               E  ]
// [7 7   7       7               F]
// [8               8              ]
// [9 9               9            ]
// [A   A               A          ]
// [B B   B               B        ]
// [C       C               C      ]
// [D D       D               D    ]
// [E   E       E               E  ]
// [F F   F       F               F]
{
    prefix_transform(f, ldn);
    prefix_transform(g, ldn);
    const ulong n = (1UL<<ldn);
    for (ulong k=0; k<n; ++k)  g[k] *= f[k];
    inverse_prefix_transform(g, ldn);
}
// -------------------------

#endif  // !defined HAVE_PREFIX_TRANSFORM_H__
