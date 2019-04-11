#if !defined  HAVE_SINCOS_H__
#define       HAVE_SINCOS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "aux0/sincos.h"  // this file


#define  SINCOS_AUTOMATIC  // comment out to select routine by hand
// ... and select routine in after #else // defined SINCOS_AUTOMATIC


#if defined SINCOS_AUTOMATIC
// ... automatic selection of routine:

#  if defined  __i386__
#    define  SINCOS_USE_ASM
#  endif

#  if defined  __x86_64__
#    define  SINCOS_USE_ASM
#  endif


#  if !defined SINCOS_USE_ASM  // no asm available

// fix for ARM (should we test for _GNU_SOURCE ?):
#    ifndef  _GLIBCPP_HAVE_SINCOS
#      define  _GLIBCPP_HAVE_SINCOS 0
#    endif

#    if  _GLIBCPP_HAVE_SINCOS == 1
#      define  SINCOS_USE_MATHINLINE
#    else
#      define  SINCOS_USE_C  // use C-version
#    endif  //   _GLIBCPP_HAVE_SINCOS == 1

#  endif  //  !defined SINCOS_USE_ASM


#else  //  defined SINCOS_AUTOMATIC
// ... manual selection of routine:

//#  define  SINCOS_USE_ASM          // asm sincos
//#  define  SINCOS_USE_MATHINLINE   // inline-math sincos
#  define  SINCOS_USE_C            // plain call of sin() and cos()

#endif  //  defined SINCOS_AUTOMATIC




#if defined  SINCOS_USE_ASM
//#  warning 'FYI: SINCOS_USE_ASM'
static inline void SinCos(double a, double *s, double *c)
{
    __asm__ ("fsincos" : "=t" (*c), "=u" (*s) : "0" (a));
}
// used (special i386) constraints:
//    `t'  First (top of stack) floating point register
//    `u'  Second floating point register
#endif  //  defined  SINCOS_USE_ASM


#if defined  SINCOS_USE_MATHINLINE
//#  warning 'FYI: SINCOS_USE_MATHINLINE'
#  include <cmath>
static inline void SinCos(double a, double *s, double *c)
{
    __sincos(a, s, c);
}
#endif  //  defined  SINCOS_USE_MATHINLINE


#if defined  SINCOS_USE_C
//#  warning 'FYI: SINCOS_USE_C'
#  include <cmath>
static inline void SinCos(double a, double *s, double *c)
{
    *s = sin(a);
    *c = cos(a);
}
#endif  //  defined  SINCOS_USE_C



#endif  //  !defined  HAVE_SINCOS_H__
