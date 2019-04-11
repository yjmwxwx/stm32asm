#if !defined HAVE_MIXEDRADIX_GSLEX_ALT2_H__
#define      HAVE_MIXEDRADIX_GSLEX_ALT2_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"

// Cf. comb/mixedradix-gslex-alt.h, the implementation here is faster.
// Cf. comb/mixedradix-gslex.h for a similar order.
// Cf. comb/mixedradix-subset-lex.h for subset-lex order.


class mixedradix_gslex_alt2
// Mixed radix numbers in alternative gslex (generalized subset-lex) order.
{
public:
    ulong n_;   // Number of digits (n kinds of elements in multiset)
    ulong tr_;  // aux: current track
    ulong *a_;  // digits of mixed radix number (multiplicity of kind k in subset).
    ulong *m1_;  // nines (radix minus one) for each digit (multiplicity of kind k in superset).

private:  // have pointer data
    mixedradix_gslex_alt2(const mixedradix_gslex_alt2&);  // forbidden
    mixedradix_gslex_alt2 & operator = (const mixedradix_gslex_alt2&);  // forbidden

public:
    explicit mixedradix_gslex_alt2(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;
        a_ = new ulong[n_+2];  // two sentinels, one left, and one right
        a_[0] = 1;  a_[n_+1] = 1;
        ++a_;  // nota bene
        m1_ = new ulong[n_];
        mixedradix_init(n_, mm, m, m1_);
        first();
    }

    ~mixedradix_gslex_alt2()
    {
        --a_;
        delete [] a_;
        delete [] m1_;
    }

    const ulong * data()  const  { return a_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        tr_ = -1UL;  // nota bene
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        a_[n_-1] = m1_[n_-1];
        tr_ = n_ - 1;
    }

    bool next()
    // Generate next.
    // Return false if current was last.
    {
        ulong j = tr_;
        if ( j+1 < n_ )  // easy case 1: attach new track
        {
            a_[j+1] = 1;
            ++tr_;
            return true;
        }

        if ( a_[j] < m1_[j] )  // easy case 2: increment
        {
            ++a_[j];
            return true;
        }

        a_[j] = 0;

        // find first nonzero digit to the left:
        --j;
        while ( a_[j] == 0 )  { --j; }  // may read sentinel a_[-1]

        if ( (long)j < 0 )  return false;  // current is last

        const ulong aj = a_[j] + 1;
        if ( aj <= m1_[j] )  // increment and stay on track
        {
            a_[j] = aj;
            tr_ = j;
        }
        else  // set to zero and next track to one
        {
            a_[j] = 0;
            a_[j+1] = 1;
            tr_ = j + 1;
        }
        return true;
    }

    bool prev()
    // Generate previous.
    // Return false if current was first.
    // Loopless algorithm.
    {
        ulong j = tr_;
        if ( j == -1UL )  return false;  // current is first

        const ulong aj = a_[j] - 1;
        a_[j] = aj;  // decrement

        if ( aj == 0 )
        {
            if ( a_[j-1] == 0 )
            {
                // put nine left and at end, and jump to end
                a_[j-1] = m1_[j-1];
                tr_ = n_ - 1;
                a_[tr_] = m1_[tr_];
            }
            else  --tr_;  // simply detach
        }
        else
        {
            if ( tr_ != n_-1 )
            {
                // put nine at end, and jump to end
                tr_ = n_ - 1;
                a_[tr_] = m1_[tr_];
            }
        }

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_mixedradix(bla, a_, n_, dfz); }

    void print_nines(const char *bla)  const
    { print_mixedradix(bla, m1_, n_, false); }

    bool OK()  const
    {
        if ( ! is_mixedradix_num(a_, n_, m1_) )  return false;
        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_MIXEDRADIX_GSLEX_ALT2_H__
