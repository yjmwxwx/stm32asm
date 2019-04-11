#if !defined  HAVE_WALSHWAK8_H__
#define       HAVE_WALSHWAK8_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "walsh/shortwalshwakdif.h"
#include "walsh/shortwalshwakdit.h"
#include "fxttypes.h"


#define WALSH_DIF8_USE_FINAL_16  // define to avoid radix-2 step
template <typename Type>
void walsh_wak_dif8(Type *f, ulong ldn)
// Transform wrt. to Walsh-Kronecker basis (wak-functions).
// Radix-8 decimation in frequency (DIF) algorithm.
// Self-inverse.
{
    const ulong n = (1UL<<ldn);

    if ( n<=4 )
    {
        switch (n )
        {
        case 4:  short_walsh_wak_dif_4(f);  break;
        case 2:  short_walsh_wak_dif_2(f);  break;
        }
        return;
    }

#ifdef WALSH_DIF8_USE_FINAL_16
    const ulong xx = 4;
#else
    const ulong xx = 3;
#endif
    ulong ldm;
    for (ldm=ldn; ldm>xx; ldm-=3)
    {
        ulong m = (1UL<<ldm);
        ulong m8 = (m>>3);
        for (ulong r=0;  r<n;  r+=m)
        {
            for (ulong j=0;  j<m8;  j++)  short_walsh_wak_dif_8(f+j+r, m8);
        }
    }

    switch ( ldm )
    {
    case 4:
        for (ulong i0=0; i0<n; i0+=16)  short_walsh_wak_dif_16(f+i0);
        break;
    case 3:
        for (ulong i0=0; i0<n; i0+=8)  short_walsh_wak_dif_8(f+i0);
        break;
    case 2:
        for (ulong i0=0; i0<n; i0+=4)  short_walsh_wak_dif_4(f+i0);
        break;
#ifndef WALSH_DIF8_USE_FINAL_16
    case 1:
        for (ulong i0=0; i0<n; i0+=2)  short_walsh_wak_dif_2(f+i0);
#endif
    }
}
// -------------------------
#undef WALSH_DIF8_USE_FINAL_16



#define WALSH_DIT8_USE_FINAL_16  // define to avoid radix-2 step
template <typename Type>
void walsh_wak_dit8(Type *f, ulong ldn)
// Transform wrt. to Walsh-Kronecker basis (wak-functions).
// Radix-8 decimation in time (DIT) algorithm.
// Self-inverse.
{
    const ulong n = (1UL<<ldn);

    if ( n<=4 )
    {
        switch (n )
        {
        case 4:  short_walsh_wak_dit_4(f);  break;
        case 2:  short_walsh_wak_dit_2(f);  break;
        }
        return;
    }

#ifdef WALSH_DIT8_USE_FINAL_16
    const ulong xx = 4;
#else
    const ulong xx = 3;
#endif
    ulong ldm;
    for (ldm=ldn; ldm>xx; ldm-=3)
    {
        ulong m = (1UL<<ldm);
        ulong m8 = (m>>3);
        for (ulong r=0;  r<n;  r+=m)
        {
            for (ulong j=0;  j<m8;  j++)  short_walsh_wak_dit_8(f+j+r, m8);
        }
    }

    switch ( ldm )
    {
    case 4:
        for (ulong i0=0; i0<n; i0+=16)  short_walsh_wak_dit_16(f+i0);
        break;
    case 3:
        for (ulong i0=0; i0<n; i0+=8)  short_walsh_wak_dit_8(f+i0);
        break;
    case 2:
        for (ulong i0=0; i0<n; i0+=4)  short_walsh_wak_dit_4(f+i0);
        break;
#ifndef WALSH_DIT8_USE_FINAL_16
    case 1:
        for (ulong i0=0; i0<n; i0+=2)  short_walsh_wak_dit_2(f+i0);
#endif
    }
}
// -------------------------
#undef WALSH_DIF8_USE_FINAL_16



#endif  // !defined HAVE_WALSHWAK8_H__
