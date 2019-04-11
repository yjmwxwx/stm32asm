#if !defined  HAVE_PERMCOMPLEMENT_H__
#define       HAVE_PERMCOMPLEMENT_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

inline void make_complement(const ulong *f, ulong *g, ulong n)
// Set (as permutation) g to the complement of f.
// Can have f==g.
{
    for (ulong k=0; k<n; ++k)  g[k] = n - 1 - f[k];
}
// -------------------------


inline void make_complement(ulong *f, ulong n)
// Set (as permutation) f to its complement.
{
    for (ulong k=0; k<n; ++k)  f[k] = n - 1 - f[k];
}
// -------------------------


#endif  // !defined HAVE_PERMCOMPLEMENT_H__
