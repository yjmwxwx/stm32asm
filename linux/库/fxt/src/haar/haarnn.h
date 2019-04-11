#if !defined  HAVE_HAARNN_H__
#define       HAVE_HAARNN_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "aux1/copy.h"


template <typename Type>
void haar_nn(Type *f, ulong ldn, Type *ws=0)
// Transform wrt. to non-normalized Haar base
{
    ulong n = (1UL<<ldn);
    Type *g = ws;
    if ( !ws )  g = new Type[n];
    for (ulong m=n; m>1; m>>=1)
    {
        ulong mh = (m>>1);
        for (ulong j=0, k=0;  j<m;  j+=2, k++)
        {
            Type x = f[j];
            Type y = f[j+1];
            g[k]    =  x + y;
            g[mh+k] =  x - y;
        }
        acopy(g, f, m);
    }
    if ( !ws )  delete [] g;
}
// -------------------------

template <typename Type>
void inverse_haar_nn(Type *f, ulong ldn, Type *ws=0)
{
    ulong n = (1UL<<ldn);
    Type s2 = 2.0;
    Type v = 1.0/n;
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
void haar_inplace_nn(Type *f, ulong ldn)
// Transform wrt. to non-normalized Haar base,
// In-place operation.
// The sequence
//   haar_inplace_nn();  haar_permute();
// is equivalent to
//   haar_nn()
{
    ulong n = 1UL<<ldn;
    for (ulong js=2; js<=n; js<<=1)
    {
        for (ulong j=0, t=js>>1;  j<n;  j+=js, t+=js)
        {
            Type x = f[j];
            Type y = f[t];
            f[j]  =  x + y;
            f[t]  =  x - y;
        }
    }
}
// -------------------------

template <typename Type>
void inverse_haar_inplace_nn(Type *f, ulong ldn)
// Inverse transform wrt. to Haar base
// In-place operation.
// The sequence
//   inverse_haar_permute();  inverse_haar_inplace();
// is equivalent to
//   inverse_haar()
{
    ulong n = 1UL<<ldn;
    Type s2 = 2.0;
    Type v = 1.0/n;
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



#endif  // !defined HAVE_HAARNN_H__
