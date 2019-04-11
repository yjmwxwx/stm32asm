#if !defined  HAVE_CATALAN_PATH_LEX_H__
#define       HAVE_CATALAN_PATH_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-catalan-path.h"
#include "comb/print-catalan-path-aa.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


//#define CATALAN_PATH_LEX_NO_FLAT_STEPS  // default on
// If *not* defined, flat steps are allowed and
// C(n+1) (instead of C(n)) objects are generated,
// where C(n) is the n-th Catalan number.


class catalan_path_lex
// Catalan paths in lexicographic order, CAT algorithm.
// Steps are +1, 0, -1 (up, horizontal, down),
// the first and last elements are 0, all elements are non-negative,
// and even/odd positions respectively have even/odd entries only.
{
public:
    ulong *a_;
    ulong n_;

private:  // have pointer data
    catalan_path_lex(const catalan_path_lex&);  // forbidden
    catalan_path_lex & operator = (const catalan_path_lex&);  // forbidden

public:
    explicit catalan_path_lex(ulong n)
    // Must have n>=1.
    {
        n_ = 2 * n;  // length = 2 * n

        if ( n==0 )  n_ = 1;  // make things work for n==0


        a_ = new ulong[n_+2];
        a_[0] = 0;  // lower sentinel
        ++a_;  // nota bene
        a_[n_] = 0;  // used in print() as final element

        first();
    }

    ~catalan_path_lex()
    {
        --a_;
        delete [] a_;
    }

    void first()
    {
#ifdef CATALAN_PATH_LEX_NO_FLAT_STEPS
        for (ulong j=0; j<n_; ++j)  a_[j] = j & 1UL;
#else
        for (ulong j=0; j<n_; ++j)  a_[j] = 0;
#endif
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

#ifdef CATALAN_PATH_LEX_NO_FLAT_STEPS
        a_[j] = j & 1;
#else
        a_[j] = 0;
#endif
        --j;
        ulong m = 2;

#else  // easy case optimization

        ulong j = n_ - 1;
        ulong m = 1;
#endif  // easy case optimization


        // Scan falling part:
        while ( a_[j] == m )
        {
#ifdef CATALAN_PATH_LEX_NO_FLAT_STEPS
            a_[j] = j & 1;
#else
            a_[j] = 0;
#endif
            ++m;
            --j;
        }
        // here m - 1 == t

        // Scan rising part:
        while ( a_[j] > a_[j-1] )  // can read lower sentinel
        {
#ifdef CATALAN_PATH_LEX_NO_FLAT_STEPS
            a_[j] = j & 1;
#else
            a_[j] = 0;
#endif
            --j;
        }

        if ( j==0 )   return 0;  // current is last


        if ( a_[j-1] == 0 )
        {
            a_[j-1] = 1;
            a_[j] = 0;
            return  j - 1;  // leftmost position changed
        }
        else
        {
            const ulong i = j;
            ulong v = a_[j] + 1;
            a_[j] = v + 1;
            ++j;

            do
            {
                a_[j] = v;
                --v;
                ++j;
            }
            while ( v );

            return i;  // leftmost position changed
        }
    }

    const ulong * data()  const  { return a_; }

    ulong area()  const
    {
        ulong s = 0;
        for (ulong j=1; j<n_; ++j)  s += a_[j];
        return s;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, a_, n_+1, dfz); }

    void print_aa()  const  // ASCII art
    {
#ifdef CATALAN_PATH_LEX_NO_FLAT_STEPS
        print_catalan_path_aa(data(), n_, true);
#else
        print_catalan_path_aa(data(), n_, false);
#endif
    }

    void print_horiz_aa()  const  // ASCII art
    { catalan_path_print_horiz_aa(data(), n_); }

    bool OK()  const
    { return is_catalan_path( data(), n_ ); }
};
// -------------------------


#endif  // !defined HAVE_CATALAN_PATH_LEX_H__
