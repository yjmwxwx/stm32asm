#if !defined  HAVE_RULER_FUNC1_H__
#define       HAVE_RULER_FUNC1_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/composition-nz.h"

#include "fxttypes.h"

class ruler_func1 : public composition_nz
// Ruler function (one-based), 2-valuations of 2*n:
//   1 2 1 3 1 2 1 4 1 2 1 3 1 2 1 5 1 2 1 3 1 2 1 ...
// Loopless algorithm.
// Cf. OEIS sequence A001511.
{
public:
    explicit ruler_func1(ulong n)
        : composition_nz(n+1)
    { first(); }

    ~ruler_func1()  { ; }

    void first()
    { composition_nz::first(); }

    ulong data()  const
    { return composition_nz::last_part(); }

    ulong next()
    // n + 1 is returned with last composition.
    {
        composition_nz::next();
        return  data();  // largest element in composition
    }

    void print_composition(const char *bla)  const
    { composition_nz::print(bla); }
};
// -------------------------


#endif  // !defined HAVE_RULER_FUNC1_H__
