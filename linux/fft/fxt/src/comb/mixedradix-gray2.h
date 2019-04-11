#if !defined HAVE_MIXEDRADIX_GRAY2_H__
#define      HAVE_MIXEDRADIX_GRAY2_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


class mixedradix_gray2
// Gray code for mixed radix numbers.
// Loopless algorithm. Implementation following Knuth.
{
public:
    ulong *a_;  // digits
    ulong *m1_;  // radix minus one ('nines')
    ulong *f_;  // focus pointer
    ulong *d_;  // direction
    ulong n_;   // number of digits
    ulong j_;   // position of last change
    int dm_;    // direction of last move

private:  // have pointer data
    mixedradix_gray2(const mixedradix_gray2&);  // forbidden
    mixedradix_gray2 & operator = (const mixedradix_gray2&);  // forbidden

public:
    explicit mixedradix_gray2(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;
        a_ = new ulong[n_];
        m1_ = new ulong[n_];
        d_ = new ulong[n_];    // m1_[j] == m[j] - 1 in Knuth
        f_ = new ulong[n_+1];  // n_ + 1 elements

        mixedradix_init(n_, mm, m, m1_);

        first();
    }

    ~mixedradix_gray2()
    {
        delete [] a_;
        delete [] m1_;
        delete [] d_;
        delete [] f_;
    }

    const ulong * data()  const  { return a_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  d_[k] = 1;
        for (ulong k=0; k<=n_; ++k)  f_[k] = k;
        dm_ = 0;
        j_ = n_;
    }

    bool next()
    {
        const ulong j = f_[0];
        f_[0] = 0;

        if ( j>=n_ )  return false;

        const ulong dj = d_[j];
        const ulong aj = a_[j] + dj;
        a_[j] = aj;

        dm_ = (int)dj;  // save for dir()
        j_ = j;         // save for pos()

        if ( aj + dj > m1_[j] )  // was last move?
        {
            d_[j] = -dj;      // change direction

            f_[j] = f_[j+1];  // lookup next position
            f_[j+1] = j + 1;
        }

        return true;
    }
    // could add prev() and last() (but have them in mixedradix_gray)

    ulong pos()  const  { return j_; }  // position of last change
    int dir()  const  { return dm_; }

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


#endif  // !defined HAVE_MIXEDRADIX_GRAY2_H__
