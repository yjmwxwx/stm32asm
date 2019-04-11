#if !defined HAVE_BITSPERLONG_H__
#define      HAVE_BITSPERLONG_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "bits/bitsperlong.h"  // this file

#if !defined BITS_PER_LONG  // could be defined using -DBITS_PER_LONG=value
#include <climits>

#if  ( 4294967295UL==ULONG_MAX )  // long is 32bit
#  define  BITS_PER_LONG  32
#  define  LOG2_BITS_PER_LONG  5
#else
#  if  ( 18446744073709551615UL==ULONG_MAX )  // long is 64 bit
#    define  BITS_PER_LONG  64
#    define  LOG2_BITS_PER_LONG  6
#  else
#    define  BITS_PER_LONG  128  // ... assume long is 128 bit
#    define  LOG2_BITS_PER_LONG  7
#    error 'several functions are not implemented for 128bit long'
// contact me and I might fix it
#  endif  //   ( 18446744073709551615UL==ULONG_MAX )
#endif  //   ( 4294967295UL==ULONG_MAX )

#endif  //  !defined BITS_PER_LONG


#define  BYTES_PER_LONG  (BITS_PER_LONG/8)




#if !defined BITS_PER_LONG_LONG  // could be defined using -DBITS_PER_LONG_LONG=value

#define  BITS_PER_LONG_LONG  64  // default (if ULONG_LONG_MAX is not defined)
#define  LOG2_BITS_PER_LONG_LONG  6

//#include <climits>
//#ifdef ULONG_LONG_MAX
//#  if  ( 4294967295UL==ULONG_LONG_MAX )  // long long is 32bit, strange !
//#    undef   BITS_PER_LONG_LONG
//#    define  BITS_PER_LONG_LONG  32
//#  else  //   ( 4294967295UL==ULONG_LONG_MAX )
//#    if  ( 18446744073709551615UL==ULONG_LONG_MAX )  // long long is 64 bit
//#      undef   BITS_PER_LONG_LONG
//#      define  BITS_PER_LONG_LONG  64
//#    else  //   ( 18446744073709551615UL==ULONG_LONG_MAX )
//#      undef   BITS_PER_LONG_LONG
//#      define  BITS_PER_LONG_LONG  128  // ... assume long long is 128 bit
//#      warning 'some functions might fail for 128bit long long'
// contact me and I might fix it
//#    endif  //   ( 18446744073709551615UL==ULONG_LONG_MAX )
//#  endif  //   ( 4294967295UL==ULONG_LONG_MAX )
//#endif  // def ULONG_LONG_MAX

#endif  //  !defined BITS_PER_LONG_LONG


#define  BYTES_PER_LONG_LONG  (BITS_PER_LONG_LONG/8)



#endif  //  !defined HAVE_BITSPERLONG_H__
