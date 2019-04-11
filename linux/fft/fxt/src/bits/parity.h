#if !defined HAVE_PARITY_H__
#define      HAVE_PARITY_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/graycode.h"
#include "bits/bitasm.h"



static inline ulong byte_parity(ulong x)
// Return the parities of bytes in parallel
{
#if  BITS_PER_LONG == 32
    return  byte_inverse_gray_code(x) & 0x01010101UL;
#endif

#if  BITS_PER_LONG == 64
    return  byte_inverse_gray_code(x) & 0x0101010101010101UL;
#endif
}
// -------------------------


static inline ulong parity(ulong x)
// Return 0 if the number of set bits is even, else 1
{
#if defined  BITS_USE_ASM    // use x86 asm code
    return  asm_parity(x);
#else
    return  inverse_gray_code(x) & 1;
#endif
}
// -------------------------



#endif  // !defined HAVE_PARITY_H__
