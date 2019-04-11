#if !defined  HAVE_RULER_FUNC_S_H__
#define       HAVE_RULER_FUNC_S_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/composition-nz-sorts.h"

#include "fxttypes.h"

class ruler_func_s : public composition_nz_sorts
// Ruler function (one-based), s-valuations of s*n:
// s=2:  1 2 1 3 1 2 1 4 1 2 1 3 1 2 1 5 1 2 1 3 1 2 1 ...
//   cf. OEIS sequence A001511 and A007814 (zero based)
// s=3:  1 1 2 1 1 2 1 1 3 1 1 2 1 1 2 1 1 3 1 1 2 1 1 ...
//   cf. OEIS sequences A051064 and A007949 (zero based)
// Loopless algorithm.
{
public:
    explicit ruler_func_s(ulong n, ulong s)
        : composition_nz_sorts(n+1, s-1)
    { first(); }

    ~ruler_func_s()  { ; }

    void first()
    { composition_nz_sorts::first(); }

    ulong data()  const
    { return composition_nz_sorts::last_part(); }

    ulong next()
    // n + 1 is returned with last composition.
    {
        composition_nz_sorts::next();
        return  data();  // largest element in composition
    }

    void print_composition(const char *bla)  const
    { composition_nz_sorts::print(bla); }
};
// -------------------------


#endif  // !defined HAVE_RULER_FUNC_S_H__
