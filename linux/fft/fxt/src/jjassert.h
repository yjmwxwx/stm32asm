#if !defined HAVE_JJASSERT_H__
#define      HAVE_JJASSERT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "jjassert.h" // this file

// aux0/jjassert.cc:
// options for last action of jjassert_fail():
#define JJ_ASSERT_IGNORE  0
#define JJ_ASSERT_ABORT   1
//#define JJ_ASSERT_PAUSE   2
#define JJ_ASSERT_SEGV    4
#define JJ_ASSERT_STOP    8  // neat for backtrace with gdb
//
#define JJ_ASSERT_DEFAULT 1   // abort should be default

// Note: the action of jjassert_fail() can be modified
// at runtime using the following function:
void set_fail_action(int a=JJ_ASSERT_DEFAULT);

void jjassert_fail(const char *func, const char *pretty_func,
                   const char *file, const int   line,
                   const char *expr, const char *bla);


#if defined  NDEBUG

#define jjassert(expr)

#else // NDEBUG

// We use the equivalent of __STRING() as defined in <sys/cdefs.h>
// We use a different name to avoid portability trouble:
// Was:
//#define  __STRING(s)   __XSTRING(s)
//#define  __XSTRING(s)  #s
// Changed to:
#define __JJSTRING(s) #s


#define jjassert(expr) \
do { \
if ( !(expr) )  \
jjassert_fail( \
__FUNCTION__, \
__PRETTY_FUNCTION__, \
__FILE__, \
__LINE__, \
__JJSTRING(expr), \
0); \
} while (0)  // no semicolon


#define jjassert_not(expr)  jjassert( !(expr) )


#endif // NDEBUG


#endif  // !defined HAVE_JJASSERT_H__
