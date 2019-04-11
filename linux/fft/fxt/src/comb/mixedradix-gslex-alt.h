#if !defined HAVE_MIXEDRADIX_GSLEX_ALT_H__
#define      HAVE_MIXEDRADIX_GSLEX_ALT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"

// Cf. comb/mixedradix-gslex-alt2.h for a faster implementation.
// Cf. comb/mixedradix-gslex.h for a similar order.
// Cf. comb/mixedradix-subset-lex.h for subset-lex order.


class mixedradix_gslex_alt
// Mixed radix numbers in alternative gslex (generalized subset-lex) order.
{
public:
    ulong n_;   // n-digit numbers
    ulong *a_;  // digits,  a[-1]==~0 is a sentinel
    ulong *m1_;  // m1[k] == radix-1 at position k
    ulong e_;   // aux

private:  // have pointer data
    mixedradix_gslex_alt(const mixedradix_gslex_alt&);  // forbidden
    mixedradix_gslex_alt & operator = (const mixedradix_gslex_alt&);  // forbidden

public:
    explicit mixedradix_gslex_alt(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;
        a_ = new ulong[n_ + 1];
        a_[0] = ~0UL;  // sentinel
        ++a_;  // nota bene

        m1_ = new ulong[n_];

        mixedradix_init(n_, mm, m, m1_);

        first();
    }

    ~mixedradix_gslex_alt()
    {
        --a_;  // nota bene
        delete [] a_;
        delete [] m1_;
    }

    const ulong * data()  const  { return a_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        e_ = 0;
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        e_ = n_ - 1;
        a_[e_] = m1_[e_];
    }

    bool next()
    // Return false if current was last
    {
        ulong ae = a_[e_] + 1;
        if ( ae <= m1_[e_] )
        {
            a_[e_] = ae;
            if ( e_ < n_-1 )  ++e_;
        }
        else
        {
            a_[e_] = 0;
            ulong j = e_ - 1;
            while ( 0==a_[j] )  --j;  // can read sentinel
            if ( (long)j < 0 )  // was last
            {
                // need to restore:
                // same as last(), saving the loop:
                e_ = n_ - 1;
                a_[e_] = m1_[e_];

                return false;
            }

            ulong aj = a_[j] + 1;
            if ( aj <= m1_[j] )  a_[j] = aj;
            else
            {
                a_[j] = 0;
                ++j;
                a_[j] = 1;
            }

            e_ = j;
            if ( e_ < n_-1 )  ++e_;
        }
        return true;
    }

    bool prev()
    // Return false if current was first.
    {
        ulong j = e_;
        while ( 0==a_[j] )  --j;  // can read sentinel
        if ( (long)j < 0 )  // was first
        {
            // need to restore:
            // same as first(), saving the loop:
            e_ = 0;

            return false;
        }

        ulong aj = a_[j];
        --aj;

        if ( 0==aj )
        {
            if ( 0!=a_[j-1] )
            {
                a_[j] = aj;
                return true;
            }

            a_[j-1] = m1_[j-1];
        }

        a_[n_-1] = m1_[n_-1];
        e_ = n_ - 1;

        if ( aj )  a_[j] = aj;
        if ( j != n_-1 )  a_[j] = aj;

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


#endif  // !defined HAVE_MIXEDRADIX_GSLEX_ALT_H__
