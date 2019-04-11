#if !defined  HAVE_FHTLOC2_H__
#define       HAVE_FHTLOC2_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fht/fht.h"  // fht_dif_core(), fht_dit_core()
#include "fht/hartleyshift.h"  // hartley_shift_05()
#include "aux0/sumdiff.h"
#include "perm/revbinpermute.h"
#include "fht/shortfhtdifcore.h"
#include "fht/shortfhtditcore.h"

#include "fxttypes.h"

// whether to use trig recursion:
#define USE_TRIG_REC  // (default: yes)


template <typename Type>
void fht_loc_dif2_core(Type *f, ulong ldn)
// Fast Hartley transform (FHT).
// Recursive decimation in frequency (DIF) algorithm.
// Excellent performance for large array sizes.
{
    if ( ldn<=13 )  // sizeof(Type)*(2**threshold) <= L1_CACHE_BYTES
    {
        fht_dif_core(f, ldn);
        return;
    }

    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);

        for (ulong t1=0, t2=mh;  t1<mh;  ++t1, ++t2)
            sumdiff(f[t1], f[t2]);

#ifdef USE_TRIG_REC
        hartley_shift_05_v2rec(f+mh, mh);
#else
        hartley_shift_05_v2(f+mh, mh);
#endif
    }

    // Recursion:
//    for (ulong ldm=1; ldm<ldn; ++ldm)
//        fht_loc_dif2_core(f+(1UL<<ldm), ldm);

    fht_dif_core_2(f+2);  // ldm==1
    fht_dif_core_4(f+4);  // ldm==2
    fht_dif_core_8(f+8);  // ldm==3
//    fht_dif_core_16(f+16);  // ldm==4
    for (ulong ldm=4; ldm<ldn; ++ldm)
        fht_loc_dif2_core(f+(1UL<<ldm), ldm);
}
// -------------------------


template <typename Type>
void fht_loc_dit2_core(Type *f, ulong ldn)
// Fast Hartley transform (FHT).
// Recursive decimation in time (DIT) algorithm.
// Excellent performance for large array sizes.
{
    if ( ldn<=13 )
    {
        fht_dit_core(f, ldn);
        return;
    }

    // Recursion:
//    for (ulong ldm=1; ldm<ldn; ++ldm)
//        fht_loc_dit2_core(f+(1UL<<ldm), ldm);

    fht_dit_core_2(f+2);  // ldm==1
    fht_dit_core_4(f+4);  // ldm==2
    fht_dit_core_8(f+8);  // ldm==3
//    fht_dit_core_16(f+16);  // ldm==4
    for (ulong ldm=4; ldm<ldn; ++ldm)
        fht_loc_dit2_core(f+(1UL<<ldm), ldm);


    for (ulong ldm=1; ldm<=ldn; ++ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
#ifdef USE_TRIG_REC
        hartley_shift_05_v2rec(f+mh, mh);
#else
        hartley_shift_05_v2(f+mh, mh);
#endif
        for (ulong t1=0, t2=mh;  t1<mh;  ++t1, ++t2)
            sumdiff(f[t1], f[t2]);
    }
}
// -------------------------


//: inlines give default implementations:

template <typename Type>
inline void fht_loc(Type *f, ulong ldn)
{
    fht_loc_dif2_core(f, ldn);
    revbin_permute(f, 1UL<<ldn);
}
// -------------------------

template <typename Type>
inline void fht0_loc(Type *f, ulong ldn)
{
    // todo: no special version for zero padded data yet:
    fht_loc_dif2_core(f, ldn);
    revbin_permute(f, 1UL<<ldn);
}
// -------------------------

#undef USE_TRIG_REC

#endif  // !defined HAVE_FHTLOC2_H__
