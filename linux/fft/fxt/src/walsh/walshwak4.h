#if !defined  HAVE_WALSHWAK4_H__
#define       HAVE_WALSHWAK4_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "walsh/shortwalshwakdif.h"
#include "walsh/shortwalshwakdit.h"
#include "fxttypes.h"


template <typename Type>
void walsh_wak_dif4(Type *f, ulong ldn)
// Transform wrt. to Walsh-Kronecker basis (wak-functions).
// Radix-4 decimation in frequency (DIF) algorithm.
// Self-inverse.
{
    const ulong n = (1UL<<ldn);

    if ( n<=2 )
    {
        if ( n==2 )  short_walsh_wak_dif_2(f);
        return;
    }

    for (ulong ldm=ldn; ldm>3; ldm-=2)
    {
        ulong m = (1UL<<ldm);
        ulong m4 = (m>>2);
        for (ulong r=0;  r<n;  r+=m)
        {
            for (ulong j=0;  j<m4;  j++)  short_walsh_wak_dif_4(f+j+r, m4);
        }
    }

    if ( ldn & 1 )  // n is not a power of 4, need a radix-8 step
    {
        for (ulong i0=0; i0<n; i0+=8)  short_walsh_wak_dif_8(f+i0);
    }
    else
    {
        for (ulong i0=0; i0<n; i0+=4)  short_walsh_wak_dif_4(f+i0);
    }
}
// -------------------------



template <typename Type>
void walsh_wak_dit4(Type *f, ulong ldn)
// Transform wrt. to Walsh-Kronecker basis (wak-functions).
// Radix-4 decimation in time (DIT) algorithm.
// Self-inverse.
{
    const ulong n = (1UL<<ldn);

    if ( n<=2 )
    {
        if ( n==2 )  short_walsh_wak_dit_2(f);
        return;
    }

    for (ulong ldm=ldn; ldm>3; ldm-=2)
    {
        ulong m = (1UL<<ldm);
        ulong m4 = (m>>2);
        for (ulong r=0;  r<n;  r+=m)
        {
            for (ulong j=0;  j<m4;  j++)  short_walsh_wak_dit_4(f+j+r, m4);
        }
    }

    if ( ldn & 1 )  // n is not a power of 4, need a radix-8 step
    {
        for (ulong i0=0; i0<n; i0+=8)  short_walsh_wak_dit_8(f+i0);
    }
    else
    {
        for (ulong i0=0; i0<n; i0+=4)  short_walsh_wak_dit_4(f+i0);
    }
}
// -------------------------


#endif  // !defined HAVE_WALSHWAK4_H__
