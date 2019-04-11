#if !defined  HAVE_RULER_FUNC_H__
#define       HAVE_RULER_FUNC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


// If defined, an array is used instead of a pointer:
#define RULER_FUNC_MAX_ARRAY_LEN 64  // speedup

class ruler_func
// Ruler function (zero-based), 2-valuations of n:
//   0 1 0 2 0 1 0 3 0 1 0 2 0 1 0 4 0 1 0 2 0 1 ...
// Loopless algorithm (specialization of Knuth's method
//   for mixed radix Gray code).
// Cf. OEIS sequence A007814.
{
public:
#ifndef RULER_FUNC_MAX_ARRAY_LEN
    ulong *f_;  // focus pointer
#else
    ulong f_[RULER_FUNC_MAX_ARRAY_LEN+2];
#endif
    ulong n_;

private:  // have pointer data
    ruler_func(const ruler_func&);  // forbidden
    ruler_func & operator = (const ruler_func&);  // forbidden

public:
    explicit ruler_func(ulong n)
    {
#ifndef RULER_FUNC_MAX_ARRAY_LEN
        n_ = n;
        f_ = new ulong[n+2];
#else
        n_ = RULER_FUNC_MAX_ARRAY_LEN;
        n_ += (n ^ n);  // avoid warning about unused variable n
#endif
        first();
    }

    ~ruler_func()
    {
#ifndef RULER_FUNC_MAX_ARRAY_LEN
        delete [] f_;
#endif
    }

    void first()
    {
        for (ulong k=0; k<n_+2; ++k)  f_[k] = k;
    }

    ulong next()
    {
        const ulong j = f_[0];
//        if ( j==n_ )  { return n_; }  // leave to user
        f_[0] = 0;
        const ulong nj = j + 1;
        f_[j] = f_[nj];
        f_[nj] = nj;
        return j;
    }
};
// -------------------------

//#undef RULER_FUNC_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_RULER_FUNC_H__
