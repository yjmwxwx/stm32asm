#if !defined  HAVE_REALLOC_H__
#define       HAVE_REALLOC_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

//#define USE_C_REALLOC  // comment out to disable use of realloc()

#ifdef USE_C_REALLOC
#include <cstdlib>  // realloc()
//#else
//#include "aux1/copy.h"  // copy()
#endif

#ifdef USE_C_REALLOC
template <typename Type>
inline Type *ReAlloc(Type *p, ulong n, ulong /*nold*/)
{
    // valgrind complains about this version.
    return (Type *)realloc((void *)p, n*sizeof(Type));
}
// -------------------------

#else  // USE_C_REALLOC

template <typename Type>
inline Type *ReAlloc(Type *p, ulong n, ulong nold)
{
    Type *np = new Type[n];
    ulong nc = (nold < n ? nold : n);
    for (ulong k=0; k<nc; ++k)  np[k] = p[k];
    delete [] p;
    return np;
}
// -------------------------
#endif  // USE_C_REALLOC

#undef USE_C_REALLOC


#endif  // !defined HAVE_REALLOC_H__
