#if !defined HAVE_APPLYFUNC_H__
#define      HAVE_APPLYFUNC_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


template <typename Type>
inline void apply_func(Type *f, ulong n, Type (*func)(Type))
// apply func to each element of f[]
{
    while ( n-- )  f[n] = func( f[n] );
}
// -------------------------

template <typename Type>
inline void apply_func(Type *f, ulong n, Type (*func)(Type, Type), const Type *g)
// set f[k] = func(f[k], g[k])  for all k
{
    while ( n-- )  f[n] = func( f[n], g[n] );
}
// -------------------------

template <typename Type>
inline void apply_idx_func(Type *f, ulong n, Type (*func)(Type, ulong))
// set f[k] = func(f[k], k)  for all k
{
    while ( n-- )  f[n] = func( f[n], n );
}
// -------------------------

template <typename Type>
inline void apply_idx_func(Type *f, ulong n, Type (*func)(Type, Type, ulong), const Type *g)
// set f[k] = func(f[k], g[k], k)  for all k
{
    while ( n-- )  f[n] = func( f[n], g[n], n );
}
// -------------------------


template <typename Type>
inline void val2idxvec_func(const Type *f, ulong n, ulong (* func)(Type), ulong *x)
// for all k set  x[k] = func(f[k])
// (e.g. for computing a delta sequence wrt. to some condition)
{
    for (ulong k=0; k<n; ++k)  x[k] = func( f[k] );
}
// -------------------------

template <typename Type>
inline void idxvec2val_func(const ulong *x, ulong n, Type (* func)(ulong), Type *f)
// for all k set  f[k] = func(x[k])
// (e.g. for tabulating a function (in math sense) for permuted values)
{
    for (ulong k=0; k<n; ++k)  f[k] = func( x[k] );
}
// -------------------------

template <typename Type>
inline void idx2val_func(Type *f, ulong n, Type (* func)(Type), Type x0=0, Type x1=1)
// for all k set  f[k] = func( x0 + k*((x1-x0)/(n-1)) )
// (e.g. for tabulating a function (in math sense) from x0 to x1)
{
    if ( n<=1 )
    {
        if ( 0!=n )  f[0] = func( x0 );
        return;
    }

    Type step = (x1-x0) / (Type)(n-1);
    for (ulong k=0;  k<n;  ++k, x0+=step)  f[k] = func( x0 );
}
// -------------------------



#endif // !defined HAVE_APPLYFUNC_H__
