#if !defined  HAVE_APPLYFUNC2D_H__
#define       HAVE_APPLYFUNC2D_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "aux1/applyfunc.h"


template <typename Type>
inline void apply_func(Type **f, ulong nr, ulong nc, Type (*func)(Type))
// apply function func to each element of f[]
{
    while ( nr-- )  apply_func(f[nr], nc, func);
}
// -------------------------


#endif  // !defined HAVE_APPLYFUNC2D_H__
