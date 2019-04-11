#if !defined HAVE_BITASM_AMD64_H__
#define      HAVE_BITASM_AMD64_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#if !defined FXT_NO_WARN_HDR  // defined by make target 'invdep'
#if !defined HAVE_BITASM_H__
#error 'Do not include directly, this file is included by bitasm.h'
#endif  // !defined HAVE_BITASM_H__
#endif  // !defined FXT_NO_WARN_HDR

//#include "fxttypes.h"


#ifdef HAVE_AMD64_POPCNT
//#warning HAVE_AMD64_POPCNT
static inline ulong asm_bit_count(ulong x)
{
    asm ("popcntq %0, %0" : "=r" (x) : "0" (x));
    return x;
}
// -------------------------
#endif  // HAVE_AMD64_POPCNT


// AMD 24592:
// The BSF and BSR instructions search a source operand for the
// least-significant (BSF) or most-significant (BSR) bit that is set
// to 1. If a set bit is found, its bit index is loaded into the
// destination operand, and the zero flag (ZF) is set. If no set bit
// is found , the zero flag is cleared and the contents of the
// destination are undefined.

static inline ulong asm_bsf(ulong x)
// Bit Scan Forward
{
    asm ("bsfq %0, %0" : "=r" (x) : "0" (x));
    return x;
}
// -------------------------


static inline ulong asm_bsr(ulong x)
// Bit Scan Reverse
{
    asm ("bsrq %0, %0" : "=r" (x) : "0" (x));
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
    asm ("rolq   %%cl, %0" : "=r" (x) : "0" (x), "c" (r));
    return x;
}
// -------------------------


static inline ulong asm_ror(ulong x, ulong r)
// Rotate Right
{
    asm ("rorq   %%cl, %0" : "=r" (x) : "0" (x), "c" (r));
    return x;
}
// -------------------------


static inline ulong asm_parity(ulong x)
// Return the parity of x (which is the
// _complement_ of AMD64's parity flag).
// As parity is for the low byte only,
// therefore we need to prepend
// x ^= (x>>32);  x ^= (x>>16);  x ^= (x>>8);
// in the code
{
    x ^= (x>>32);
    x ^= (x>>16);
    x ^= (x>>8);
    asm ("addq  $0, %0  \n"
         "setnp %%al    \n"
         "movzx %%al, %0"
         : "=r" (x) : "0" (x) : "rax");

    return x;
}
// -------------------------

// AMD 24592:
// The BTx instructions copy a specified bit in the first operand to
// the carry flag (CF) and leave the source bit unchanged (BT), or
// complement the source bit (BTC), or clear the source bit to 0
// (BTR), or set the source bit to 1 (BTS).

static inline ulong asm_bt(const ulong *f, ulong i)
// Bit Test
{
    ulong ret;
    asm ( "btq  %2, %1 \n"  // carry = 0 or 1
          "sbbq %0, %0"    // ret = 0 or -1
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline ulong asm_bts(ulong *f, ulong i)
// Bit Test and Set
{
    ulong ret;
    asm ( "btsq %2, %1 \n"
          "sbbq %0, %0"
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline void asm_b_s(ulong *f, ulong i)
// Bit Set
{
    asm ( "btsq  %1, %0 \n"
          : /* void */
          : "m" (*f), "r" (i) );
}
// -------------------------

static inline ulong asm_btr(ulong *f, ulong i)
// Bit Test and Reset
{
    ulong ret;
    asm ( "btrq  %2, %1 \n"
          "sbbq %0, %0"
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline void asm_b_r(ulong *f, ulong i)
// Bit Reset
{
    asm ( "btrq  %1, %0 \n"
          : /* void */
          : "m" (*f), "r" (i) );
}
// -------------------------

static inline ulong asm_btc(ulong *f, ulong i)
// Bit Test and Complement
{
    ulong ret;
    asm ( "btcq  %2, %1 \n"
          "sbbq %0, %0"
          : "=r" (ret)
          : "m" (*f), "r" (i) );
    return ret;
}
// -------------------------

static inline void asm_b_c(ulong *f, ulong i)
// Bit Complement
{
    asm ( "btcq  %1, %0 \n"
          : /* void */
          : "m" (*f), "r" (i) );
}
// -------------------------


#endif  //  HAVE_BITASM_AMD64_H__
