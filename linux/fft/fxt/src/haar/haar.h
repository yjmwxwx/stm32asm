#if !defined  HAVE_HAAR_H__
#define       HAVE_HAAR_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <cmath>  // sqrt()

#include "fxttypes.h"

#include "aux1/copy.h"


template <typename Type>
void haar(Type *f, ulong ldn, Type *ws=0)
// Transform wrt. to Haar base
//
// The basis functions are:
//  0: [+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +]
//  1: [+ + + + + + + + + + + + + + + + - - - - - - - - - - - - - - - -]
//  2: [+ + + + + + + + - - - - - - - -                                ]
//  3: [                                + + + + + + + + - - - - - - - -]
//  4: [+ + + + - - - -                                                ]
//  5: [                + + + + - - - -                                ]
//  6: [                                + + + + - - - -                ]
//  7: [                                                + + + + - - - -]
//  8: [+ + - -                                                        ]
//  9: [        + + - -                                                ]
// 10: [                + + - -                                        ]
// 11: [                        + + - -                                ]
// 12: [                                + + - -                        ]
// 13: [                                        + + - -                ]
// 14: [                                                + + - -        ]
// 15: [                                                        + + - -]
// 16: [+ -                                                            ]
// 17: [    + -                                                        ]
// 18: [        + -                                                    ]
// 19: [            + -                                                ]
// 20: [                + -                                            ]
// 21: [                    + -                                        ]
// 22: [                        + -                                    ]
// 23: [                            + -                                ]
// 24: [                                + -                            ]
// 25: [                                    + -                        ]
// 26: [                                        + -                    ]
// 27: [                                            + -                ]
// 28: [                                                + -            ]
// 29: [                                                    + -        ]
// 30: [                                                        + -    ]
// 31: [                                                            + -]
//
{
    ulong n = (1UL<<ldn);
    Type s2 = sqrt(0.5);
    Type v = 1.0;
    Type *g = ws;
    if ( !ws )  g = new Type[n];
    for (ulong m=n; m>1; m>>=1)
    {
        v *= s2;
        ulong mh = (m>>1);
        for (ulong j=0, k=0;  j<m;  j+=2, k++)
        {
            Type x = f[j];
            Type y = f[j+1];
            g[k]    =  x + y;
            g[mh+k] = (x - y) * v;
        }
        acopy(g, f, m);
    }
    f[0] *= v;  // v == 1.0/sqrt(n);
    if ( !ws )  delete [] g;
}
// -------------------------


template <typename Type>
void inverse_haar(Type *f, ulong ldn, Type *ws=0)
// Inverse transform wrt. to Haar base
{
    ulong n = (1UL<<ldn);
    Type s2 = sqrt(2.0);
    Type v = 1.0/sqrt((double)n);
    Type *g = ws;
    if ( !ws )  g = new Type[n];
    f[0] *= v;
    for (ulong m=2; m<=n; m<<=1)
    {
        ulong mh = (m>>1);
        for (ulong j=0, k=0;  j<m;  j+=2, k++)
        {
            Type x = f[k];
            Type y = f[mh+k] * v;
            g[j]    =  x + y;
            g[j+1]  =  x - y;
        }
        acopy(g, f, m);
        v *= s2;
    }
    if ( !ws )  delete [] g;
}
// -------------------------


template <typename Type>
void haar_inplace(Type *f, ulong ldn)
// Transform wrt. to haar base.
// In-place operation.
// The sequence
//   haar_inplace();  haar_permute();
// is equivalent to
//   haar()
//
// The basis (is the Haar basis, reordered):
//  0: [+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +]
//  1: [+ -                                                            ]
//  2: [+ + - -                                                        ]
//  3: [    + -                                                        ]
//  4: [+ + + + - - - -                                                ]
//  5: [        + -                                                    ]
//  6: [        + + - -                                                ]
//  7: [            + -                                                ]
//  8: [+ + + + + + + + - - - - - - - -                                ]
//  9: [                + -                                            ]
// 10: [                + + - -                                        ]
// 11: [                    + -                                        ]
// 12: [                + + + + - - - -                                ]
// 13: [                        + -                                    ]
// 14: [                        + + - -                                ]
// 15: [                            + -                                ]
// 16: [+ + + + + + + + + + + + + + + + - - - - - - - - - - - - - - - -]
// 17: [                                + -                            ]
// 18: [                                + + - -                        ]
// 19: [                                    + -                        ]
// 20: [                                + + + + - - - -                ]
// 21: [                                        + -                    ]
// 22: [                                        + + - -                ]
// 23: [                                            + -                ]
// 24: [                                + + + + + + + + - - - - - - - -]
// 25: [                                                + -            ]
// 26: [                                                + + - -        ]
// 27: [                                                    + -        ]
// 28: [                                                + + + + - - - -]
// 29: [                                                        + -    ]
// 30: [                                                        + + - -]
// 31: [                                                            + -]
//
{
    ulong n = 1UL<<ldn;
    Type s2 = sqrt(0.5);
    Type v = 1.0;
    for (ulong js=2; js<=n; js<<=1)
    {
        v *= s2;
        for (ulong j=0, t=js>>1;  j<n;  j+=js, t+=js)
        {
            Type x = f[j];
            Type y = f[t];
            f[j]  =  x + y;
            f[t]  = (x - y) * v;
        }
    }
    f[0] *= v;  // v==1.0/sqrt(n);
}
// -------------------------


template <typename Type>
void inverse_haar_inplace(Type *f, ulong ldn)
// Inverse transform wrt. to Haar base.
// In-place operation.
// The sequence
//   inverse_haar_permute();  inverse_haar_inplace();
// is equivalent to
//   inverse_haar()
{
    ulong n = 1UL<<ldn;
    Type s2 = sqrt(2.0);
    Type v = 1.0/sqrt((double)n);
    f[0] *= v;
    for (ulong js=n; js>=2; js>>=1)
    {
        for (ulong j=0, t=js>>1;  j<n;  j+=js, t+=js)
        {
            Type x = f[j];
            Type y = f[t] * v;
            f[j]  =  x + y;
            f[t]  =  x - y;
        }
        v *= s2;
    }
}
// -------------------------


#endif  // !defined HAVE_HAAR_H__
