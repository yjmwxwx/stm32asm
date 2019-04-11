#if !defined HAVE_BITASM_H__
#define      HAVE_BITASM_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "bits/bitasm.h"  // this file
#include "fxttypes.h"

#if defined  __GNUC__  // GNU compiler

// Comment out the following line to disable asm usage:
//#  define DISABLE_BIT_ASM

#  ifndef DISABLE_BIT_ASM  // for automatic testing
#    ifdef __i386__
#      define  BITS_USE_ASM       // use asm code
#      define  BITS_USE_ASM_I386  // use i386 asm code
#      include "bitasm-i386.h"
#    endif
#    ifdef __x86_64__
#      define  BITS_USE_ASM        // use asm code
#      define  BITS_USE_ASM_AMD64  // use AMD64 asm code
#      include "bitasm-amd64.h"
#      define  BITS_USE_ASM_SSE    // use SSE asm code
#      include "bitasm-sse.h"
#    endif
#  endif  // ndef DISABLE_BIT_ASM

#endif  //  defined  __GNUC__


#endif  //  !defined HAVE_BITASM_H__
