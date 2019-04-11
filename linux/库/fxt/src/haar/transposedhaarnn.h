#if !defined  HAVE_TRANSPOSEDHAARNN_H__
#define       HAVE_TRANSPOSEDHAARNN_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

#include "aux1/copy.h"


template <typename Type>
void transposed_haar_nn(Type *f, ulong ldn, Type *ws=0)
// Transform wrt. to transposed non-normalized Haar base.
// This is the inverse_haar() routine without normalization.
{
    ulong n = (1UL<<ldn);
    Type *g = ws;
    if ( !ws )  g = new Type[n];
    for (ulong m=2; m<=n; m<<=1)
    {
        ulong mh = (m>>1);
        for (ulong j=0, k=0;  j<m;  j+=2, k++)
        {
            Type x = f[k];
            Type y = f[mh+k];
            g[j]    =  x + y;
            g[j+1]  =  x - y;
        }
        acopy(g, f, m);
    }
    if ( !ws )  delete [] g;
}
// -------------------------

template <typename Type>
void inverse_transposed_haar_nn(Type *f, ulong ldn, Type *ws=0)
{
    ulong n = (1UL<<ldn);
    Type *g = ws;
    if ( !ws )  g = new Type[n];
    for (ulong m=n; m>1; m>>=1)
    {
        ulong mh = (m>>1);
        for (ulong j=0, k=0;  j<m;  j+=2, k++)
        {
            Type x = f[j]   * 0.5;
            Type y = f[j+1] * 0.5;
            g[k]    =  x + y;
            g[mh+k] =  x - y;
        }
        acopy(g, f, m);
    }
    if ( !ws )  delete [] g;
}
// -------------------------


template <typename Type>
void transposed_haar_inplace_nn(Type *f, ulong ldn)
// Transform wrt. to transposed non-normalized Haar base.
// In-place operation.
// The sequence
//   inverse_haar_permute();  transposed_haar_inplace_nn();
// is equivalent to
//   transposed_haar_nn()
{
    ulong n = 1UL<<ldn;
    for (ulong js=n; js>=2; js>>=1)
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
void inverse_transposed_haar_inplace_nn(Type *f, ulong ldn)
{
    ulong n = 1UL<<ldn;
    for (ulong js=2; js<=n; js<<=1)
    {
        for (ulong j=0, t=js>>1;  j<n;  j+=js, t+=js)
        {
            Type x = f[j] * 0.5;
            Type y = f[t] * 0.5;
            f[j]  =  x + y;
            f[t]  =  x - y;
        }
    }
}
// -------------------------



#endif  // !defined HAVE_TRANSPOSEDHAARNN_H__
