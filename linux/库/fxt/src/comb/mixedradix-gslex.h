#if !defined HAVE_MIXEDRADIX_GSLEX_H__
#define      HAVE_MIXEDRADIX_GSLEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"

// Cf. comb/mixedradix-gslex2.h for a faster (loopless) implementation

// Cf. comb/mixedradix-gslex-alt2.h for a similar order.
// Cf. comb/mixedradix-subset-lex.h for subset-lex order.


class mixedradix_gslex
// Mixed radix numbers in gslex (generalized, subset-lexicographic) order.
{
public:
    ulong n_;   // n-digit numbers
    ulong *a_;  // digits
    ulong *m1_;  // m1[k] == radix-1 at position k

private:  // have pointer data
    mixedradix_gslex(const mixedradix_gslex&);  // forbidden
    mixedradix_gslex & operator = (const mixedradix_gslex&);  // forbidden

public:
    explicit mixedradix_gslex(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;
        a_ = new ulong[n_ + 1];
        a_[n_] = 1;  // sentinel
        m1_ = new ulong[n_];
        mixedradix_init(n_, mm, m, m1_);
        first();
    }

    ~mixedradix_gslex()
    {
        delete [] a_;
        delete [] m1_;
    }

    const ulong * data()  const  { return a_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        a_[0] = 1;
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
    }

    bool next()
    // Return false if current was last.
    // Can be made loopless by keeping record of current track, see
    // class mixedradix_gslex2.
    {
        ulong e = 0;
        while ( 0==a_[e] )  ++e;  // can read sentinel

        if ( e==n_ )  return false;  // current is last

        ulong ae = a_[e];
        if ( ae != m1_[e] )  // easy case: simple increment
        {
            a_[0] = 1;
            a_[e] = ae + 1;
        }
        else
        {
            a_[e] = 0;
            if ( a_[e+1]==0 )  // can read sentinel
            {
                a_[0] = 1;
                ++a_[e+1];
            }
        }
        return true;
    }

    bool prev()
    // Return false if current was first.
    {
        ulong e = 0;
        while ( 0==a_[e] )  ++e;  // can read sentinel

        if ( 0!=e )  // easy case: prepend nine
        {
            --e;
            a_[e] = m1_[e];
        }
        else
        {
            ulong a0 = a_[0];
            --a0;
            a_[0] = a0;

            if ( 0==a0 )
            {
                do { ++e; }  while ( 0==a_[e] );  // can read sentinel
                if ( e==n_ )  return false;  // current is first
                ulong ae = a_[e];
                --ae;
                a_[e] = ae;
                if ( 0==ae )
                {
                    --e;
                    a_[e] = m1_[e];
                }
            }
        }
        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_mixedradix(bla, a_, n_, dfz); }

    void print_nines(const char *bla)  const
    { print_mixedradix(bla, m1_, n_, false); }

    ulong to_num()  const
    // Return (integer) value of mixed radix number.
    { return mixedradix2num(a_, m1_, n_); }

    bool OK()  const
    {
        if ( ! is_mixedradix_num(a_, n_, m1_) )  return false;
        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_MIXEDRADIX_GSLEX_H__
