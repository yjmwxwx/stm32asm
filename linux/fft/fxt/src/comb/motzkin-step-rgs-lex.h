#if !defined HAVE_MOTZKIN_STEP_RGS_LEX_H__
#define      HAVE_MOTZKIN_STEP_RGS_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-motzkin-step-rgs.h"
#include "comb/print-catalan-step-rgs-aa.h"

#include "comb/comb-print.h"

#include "fxttypes.h"

class motzkin_step_rgs_lex
// Motzkin step RGS (restricted growth strings), lexicographic order.
// RGS are a[] such that a[k] >= a[k-1] (weakly ascending), a[k]<=k, and
// a[k] - a[k-1] != 1 (no increments by 1).
// Same as: rising factorial numbers where the digits are sorted
// where increments by 1 are disallowed.
// Cf. OEIS sequence A001006.
{
public:
    ulong *a_;  // RGS
    ulong n_;   // length of the RGS.

private:  // have pointer data
    motzkin_step_rgs_lex(const motzkin_step_rgs_lex&);  // forbidden
    motzkin_step_rgs_lex & operator = (const motzkin_step_rgs_lex&);  // forbidden

public:
    explicit motzkin_step_rgs_lex(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+2];
        a_[0] = 0;  // sentinel
        ++a_;  // nota bene
        // layout of a[]:
        // [ -1, 0, 1, 2, 3, ..., n-1, n ]  index
        // [  0, 0, *, *, *, ...,  *,  * ]  value

        first();
    }

    ~motzkin_step_rgs_lex()
    {
        --a_;
        delete [] a_;
    }

    const ulong * data()  const  { return a_ + 1; }

    void first()
    { for (ulong k=0; k<=n_; ++k)  a_[k] = 0; }

    ulong next()
    // Return position of leftmost change (1,...,n-1).
    // Return zero if current RGS is last.
    {
        ulong j = n_;
        while ( j != 0 )
        {
            ulong a1 = a_[j] + 1 + (a_[j]==a_[j-1]);   // can read sentinel
            if ( a1 <= j )
            {
                for (ulong i=j; i<=n_; ++i)  a_[i] = a1;
                return j;
            }
            --j;
        }

        return 0;
    }

    void print(const char *bla, bool dfz)  const
    { print_vec(bla, data(), n_, dfz); }

    void print_aa()  const  // ASCII art
    { catalan_step_rgs_print_aa(data(), n_); }

    bool OK()  const
    { return is_motzkin_step_rgs(a_, n_+1); }
};
// -------------------------


#endif  // !defined HAVE_MOTZKIN_STEP_RGS_LEX_H__
