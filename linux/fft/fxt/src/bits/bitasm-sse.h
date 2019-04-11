#if !defined HAVE_BITASM_SSE_H__
#define      HAVE_BITASM_SSE_H__
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

#if 0
static inline ulong sse_byte_zip(ulong x)
// Return word with lower half bytes in even indices
//  and upper half bits in odd indices.
//.
// Slower than the butterfly_8/16() based version!
// This is apparently not what SSE was made for.
{
    // Equivalent function:
    //    x = butterfly_16(x);
    //    x = butterfly_8(x);
    //    return  x;  // ./bin  2.94s user 0.01s system 100% cpu 2.959 total

    ulong l = x & 0xffffffffUL;
    ulong h = x >> 32;
    asm ("movd %2, %%xmm6 \n"
         "movd %1, %%xmm7 \n"
         "punpcklbw %%xmm6, %%xmm7 \n"
         "movd %%xmm7, %0"
         : "=r" (x)  // output
         : "r" (l), "r" (h)  // input
         : "xmm6", "xmm7"  // clobber
         );
    return x;  // ./bin  5.07s user 0.04s system 100% cpu 5.110 total

//    asm ("movd %1, %%xmm6 \n"
//         "pxor %%xmm7, %%xmm7 \n"
//         "punpcklbw %%xmm6, %%xmm7 \n"
//         "movdqa %%xmm7, %%xmm6 \n"
//         "psrldq $1, %%xmm7 \n"
//         "psrldq $8, %%xmm6 \n"
//         "por %%xmm6, %%xmm7 \n"
//         "movd %%xmm7, %0"
//         : "=r" (x)  // output
//         : "0" (x)  // input
//         : "xmm6", "xmm7"  // clobber
//         );
//    return x;  // ./bin  5.44s user 0.04s system 99% cpu 5.487 total

//// saves one instruction but is _slower_:
//    asm ("movd %1, %%xmm6 \n"
//         "pxor %%xmm7, %%xmm7 \n"
//         "punpcklbw %%xmm7, %%xmm6 \n"
//         "movdqa %%xmm6, %%xmm7 \n"
//         "psrldq $7, %%xmm7 \n"
//         "por %%xmm7, %%xmm6 \n"
//         "movd %%xmm6, %0"
//         : "=r" (x)  // output
//         : "0" (x)  // input
//         : "xmm6", "xmm7"  // clobber
//         );
//    return x;  // ./bin  5.83s user 0.03s system 100% cpu 5.864 total
}
// -------------------------
#endif


#endif  //  HAVE_BITASM_SSE_H__
