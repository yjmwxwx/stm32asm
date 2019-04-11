#if !defined HAVE_BITASM_I386_H__
#define      HAVE_BITASM_I386_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#if !defined FXT_NO_WARN_HDR  // defined by make target 'invdep'
#if !defined HAVE_BITASM_H__
#error 'Do not include directly, this file is included by bitasm.h'
#endif  // !defined HAVE_BITASM_H__
#endif  // !defined FXT_NO_WARN_HDR

//#include "fxttypes.h"

static inline ulong asm_bsf(ulong x)
// Bit Scan Forward: return index of lowest one.
{
    asm ("bsfl %0, %0" : "=r" (x) : "0" (x));
    return x;
}
// -------------------------


static inline ulong asm_bsr(ulong x)
// Bit Scan Reverse: return index of highest one.
{
    asm ("bsrl %0, %0" : "=r" (x) : "0" (x));
    return x;
}
// -------------------------


static inline ulong asm_bswap(ulong x)
// Byte swap
{
    asm ("bswap %0" : "=r" (x) : "0" (x));
    return x;
}
// -------------------------


static inline ulong asm_rol(ulong x, ulong r)
// Rotate Left
{
    asm ("roll   %%cl, %0" : "=r" (x) : "0" (x), "c" (r));
    return x;
}
// -------------------------


static inline ulong asm_ror(ulong x, ulong r)
// Rotate Right
{
    asm ("rorl   %%cl, %0" : "=r" (x) : "0" (x), "c" (r));
    return x;
}
// -------------------------


static inline ulong asm_parity(ulong x)
// Return the parity of x (which is the
// _complement_ of x86's parity flag).
// As parity is for the low byte only,
// therefore we need to prepend
// x ^= (x>>16);  x ^= (x>>8);
// in the code
{
    x ^= (x>>16);
    x ^= (x>>8);
    asm ("addl  $0, %0  \n"
         "setnp %%al    \n"
         "movzx %%al, %0"
         : "=r" (x) : "0" (x) : "eax");

    return x;
}
// -------------------------


static inline ulong asm_bt(const ulong *f, ulong i)
// Bit Test
{
    ulong ret;
    asm ( "btl  %2, %1 \n"  // carry = 0 or 1
          "sbbl %0, %0"     // ret = 0 or -1
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline ulong asm_bts(ulong *f, ulong i)
// Bit Test and Set
{
    ulong ret;
    asm ( "btsl %2, %1 \n"
          "sbbl %0, %0"
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline void asm_b_s(ulong *f, ulong i)
// Bit Set
{
    asm ( "btsl  %1, %0 \n"
          : /* void */
          : "m" (*f), "r" (i) );
}
// -------------------------

static inline ulong asm_btr(ulong *f, ulong i)
// Bit Test and Reset
{
    ulong ret;
    asm ( "btrl  %2, %1 \n"
          "sbbl %0, %0"
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline void asm_b_r(ulong *f, ulong i)
// Bit Reset
{
    asm ( "btrl  %1, %0 \n"
          : /* void */
          : "m" (*f), "r" (i) );
}
// -------------------------

static inline ulong asm_btc(ulong *f, ulong i)
// Bit Test and Complement
{
    ulong ret;
    asm ( "btcl  %2, %1 \n"
          "sbbl %0, %0"
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline void asm_b_c(ulong *f, ulong i)
// Bit Complement
{
    asm ( "btcl  %1, %0 \n"
          : /* void */
          : "m" (*f), "r" (i) );
}
// -------------------------


#endif  // !defined HAVE_BITASM_I386_H__
