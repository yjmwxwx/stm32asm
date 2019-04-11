#if !defined HAVE_SHORTREVBINPERMUTE0_H__
#define      HAVE_SHORTREVBINPERMUTE0_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "fxttypes.h"

//template <typename Type>
//inline void
//revbin_permute0_2(Type *f)
//// unrolled version for length 2
//{
//}  // # of swaps = 0
//// -------------------------

template <typename Type>
inline void revbin_permute0_4(Type *f)
// unrolled version for length 4
{
    swap0(f[1], f[2]);
}  // # of swaps = 1
// -------------------------

template <typename Type>
inline void revbin_permute0_8(Type *f)
// unrolled version for length 8
{
    swap0(f[1], f[4]);
    swap0(f[3], f[6]);
}  // # of swaps = 2
// -------------------------

template <typename Type>
inline void revbin_permute0_16(Type *f)
// unrolled version for length 16
{
    swap0(f[1], f[8]);
    swap2(f[2], f[4]);
    swap0(f[3], f[12]);
    swap0(f[5], f[10]);
    swap0(f[7], f[14]);
    // swap0(f[11], f[13]);
}  // # of swaps = 6 - 1 = 5
// -------------------------

template <typename Type>
inline void revbin_permute0_32(Type *f)
// unrolled version for length 32
{
    swap0(f[1], f[16]);
    swap2(f[2], f[8]);
    swap0(f[3], f[24]);
    swap0(f[5], f[20]);
    swap2(f[6], f[12]);
    swap0(f[7], f[28]);
    swap0(f[9], f[18]);
    swap0(f[11], f[26]);
    swap0(f[13], f[22]);
    swap0(f[15], f[30]);
    // swap0(f[19], f[25]);
    // swap0(f[23], f[29]);
}  // # of swaps = 12 - 2 = 10
// -------------------------

template <typename Type>
inline void revbin_permute0_64(Type *f)
// unrolled version for length 64
{
    swap0(f[1], f[32]);
    swap2(f[2], f[16]);
    swap0(f[3], f[48]);
    swap2(f[4], f[8]);
    swap0(f[5], f[40]);
    swap2(f[6], f[24]);
    swap0(f[7], f[56]);
    swap0(f[9], f[36]);
    swap2(f[10], f[20]);
    swap0(f[11], f[52]);
    swap0(f[13], f[44]);
    swap2(f[14], f[28]);
    swap0(f[15], f[60]);
    swap0(f[17], f[34]);
    swap0(f[19], f[50]);
    swap0(f[21], f[42]);
    swap2(f[22], f[26]);
    swap0(f[23], f[58]);
    swap0(f[25], f[38]);
    swap0(f[27], f[54]);
    swap0(f[29], f[46]);
    swap0(f[31], f[62]);
    // swap0(f[35], f[49]);
    // swap0(f[37], f[41]);
    // swap0(f[39], f[57]);
    // swap0(f[43], f[53]);
    // swap0(f[47], f[61]);
    // swap0(f[55], f[59]);
}  // # of swaps = 28 - 6 = 22
// -------------------------


template <typename Type>
inline void revbin_permute0_leq_64(Type *f, ulong n)
// Must have n \in {2, 4, 8, 16, 32, 64}
{
    switch ( n )
    {
    case 2: break;
    case 4: revbin_permute0_4(f); break;
    case 8: revbin_permute0_8(f); break;
    case 16: revbin_permute0_16(f); break;
    case 32: revbin_permute0_32(f); break;
    case 64: revbin_permute0_64(f); break;
//    default: ;  // ouch...
    }
}
// -------------------------

#endif  // HAVE_SHORTREVBINPERMUTE0_H__
