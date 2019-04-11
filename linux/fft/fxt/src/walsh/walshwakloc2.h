#if !defined  HAVE_WALSHWAKLOC2_H__
#define       HAVE_WALSHWAKLOC2_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "walsh/walshwak2.h"
#include "walsh/walshwak4.h"
#include "walsh/shortwalshwakdif.h"
#include "walsh/shortwalshwakdit.h"
#include "aux0/sumdiff.h"
#include "fxttypes.h"


template <typename Type>
void walsh_wak_loc_dif2(Type *f, ulong ldn)
// Walsh (wak) transform.
// Recursive decimation in frequency (DIF) algorithm.
// Excellent performance for large array sizes.
{
    if ( ldn<=13 )  // parameter: (2**13)*sizeof(Type) <= L1-cache
    {
        walsh_wak_dif4(f, ldn);
        return;
    }

    //   haar_rev_nn(f, ldn);  =^=
    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        for (ulong t1=0, t2=mh;  t1<mh;  ++t1, ++t2)  sumdiff(f[t1], f[t2]);
    }

    // Recursion:
//    for (ulong ldm=1; ldm<ldn; ++ldm)  walsh_wak_loc_dif2(f+(1UL<<ldm), ldm);
    short_walsh_wak_dif_2(f+2);  // ldm==1
    short_walsh_wak_dif_4(f+4);  // ldm==2
    short_walsh_wak_dif_8(f+8);  // ldm==3
    short_walsh_wak_dif_16(f+16);  // ldm==4
    for (ulong ldm=5; ldm<ldn; ++ldm)  walsh_wak_loc_dif2(f+(1UL<<ldm), ldm);
}
// -------------------------


template <typename Type>
void walsh_wak_loc_dit2(Type *f, ulong ldn)
// Walsh (wak) transform.
// Recursive decimation in time (DIT) algorithm.
// Excellent performance for large array sizes.
{
    if ( ldn<=13 )  // parameter: (2**13)*sizeof(Type) <= L1-cache
    {
        walsh_wak_dif4(f, ldn);  // note: DIF version, result is the same
        return;
    }

    // Recursion:
//    for (ulong ldm=1; ldm<ldn; ++ldm)  walsh_wak_loc_dit2(f+(1UL<<ldm), ldm);
    short_walsh_wak_dit_2(f+2);  // ldm==1
    short_walsh_wak_dit_4(f+4);  // ldm==2
    short_walsh_wak_dit_8(f+8);  // ldm==3
    short_walsh_wak_dit_16(f+16);  // ldm==4
    for (ulong ldm=5; ldm<ldn; ++ldm)  walsh_wak_loc_dit2(f+(1UL<<ldm), ldm);

    // transposed_haar_rev_nn(f, ldn); =^=
    for (ulong ldm=1; ldm<=ldn; ++ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        for (ulong t1=0, t2=mh;  t1<mh;  ++t1, ++t2)  sumdiff(f[t1], f[t2]);
    }
}
// -------------------------


#endif  // !defined HAVE_WALSHWAKLOC2_H__
