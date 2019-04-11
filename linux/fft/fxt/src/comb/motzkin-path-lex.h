#if !defined  HAVE_MOTZKIN_PATH_LEX_H__
#define       HAVE_MOTZKIN_PATH_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-motzkin-path.h"
#include "comb/print-catalan-path-aa.h"
#include "comb/comb-print.h"
#include "fxttypes.h"

class motzkin_path_lex
// Motzkin paths in lexicographic order, CAT algorithm.
// Steps are +1, 0, -1 (up, horizontal, down),
// the first and last elements are 0,
// and all elements are non-negative.
// Cf. OEIS sequence A001006.
{
public:
    ulong *a_;
    ulong n_;

private:  // have pointer data
    motzkin_path_lex(const motzkin_path_lex&);  // forbidden
    motzkin_path_lex & operator = (const motzkin_path_lex&);  // forbidden

public:
    explicit motzkin_path_lex(ulong n)
    // Must have n>=1.
    {
        n_ = n;
        a_ = new ulong[n_+2];
        a_[0] = 0;  // lower sentinel
        ++a_;  // nota bene
        a_[n_] = 0;  // used in print() as final element

        first();
    }

    ~motzkin_path_lex()
    {
        --a_;
        delete [] a_;
    }

    void first()
    {
        for (ulong j=0; j<n_; ++j)  a_[j] = 0;
    }

    ulong next()
    {
#if 1  // "easy case" optimization:
        ulong j = n_ - 1;
        if ( a_[j] == 0 )  // easy case: trailing zero becomes one
        {
            a_[j] = 1;
            return j;
        }

        a_[j] = 0;
        --j;
        ulong m = 2;
#else
        ulong j = n_ - 1;
        ulong m = 1;
#endif

        // Find max rising-falling tail, i.e. of the form
        //  s, s+1, s+2, ..., t-3, t-2, t-1, t, t-1, ..., 3, 2, 1
        // or (maximal element t repeated)
        //  s, s+1, s+2, ..., t-3, t-2, t-1, t, t, t-1, ..., 3, 2, 1
        // where s is preceded by an element >= s

        // Scan falling part:
        while ( a_[j] == m )
        {
            a_[j] = 0;
            ++m;
            --j;
        }
        // here m - 1 == t

        // Scan rising part:
        while ( a_[j] > a_[j-1] )  // can read lower sentinel
        {
            a_[j] = 0;
            --j;
        }

        if ( j==0 )   return 0;  // current is last

        // now replace [s, ...] by [s+1, s, s-1, s-2, ..., 3, 2, 1]
        const ulong i = j;
        ulong v = a_[j] + 1;
        do
        {
            a_[j] = v;
            --v;
            ++j;
        }
        while ( v );

        return i;  // leftmost position changed
    }

    const ulong * data()  const  { return a_; }

    ulong area()  const
    {
        ulong s = 0;
        for (ulong j=1; j<n_; ++j)  s += a_[j];
        return s;
    }

    void print(const char *bla, bool dfz=false)
    { print_vec(bla, a_, n_+1, dfz); }

    void print_aa()  const  // ASCII art
    { print_catalan_path_aa(data(), n_, false); }

    void print_horiz_aa()  const  // ASCII art
    { catalan_path_print_horiz_aa(data(), n_); }

    bool OK()  const
    { return is_motzkin_path(data(), n_); }
};
// -------------------------


#endif  // !defined HAVE_MOTZKIN_PATH_LEX_H__
