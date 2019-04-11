#if !defined HAVE_MIXEDRADIX_MODULAR_GRAY_H__
#define      HAVE_MIXEDRADIX_MODULAR_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


class mixedradix_modular_gray
// Modular Gray code for mixed radix numbers.
// Implementation following Knuth (loopless algorithm).
{
public:
    ulong *a_;  // digits
    ulong *m1_;  // radix minus one ('nines')
    ulong *f_;  // focus pointer
    ulong *s_;  // direction
    ulong n_;   // number of digits
    ulong j_;   // position of last change

private:  // have pointer data
    mixedradix_modular_gray(const mixedradix_modular_gray&);  // forbidden
    mixedradix_modular_gray & operator = (const mixedradix_modular_gray&);  // forbidden

public:
    explicit mixedradix_modular_gray(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;
        a_ = new ulong[n_];
        m1_ = new ulong[n_];  // m1_[j] == m[j] - 1 in Knuth
        f_ = new ulong[n_+1];  // n_ + 1 elements
        s_ = new ulong[n_];

        mixedradix_init(n_, mm, m, m1_);

        first();
    }

    ~mixedradix_modular_gray()
    {
        delete [] a_;
        delete [] m1_;
        delete [] f_;
        delete [] s_;
    }

    const ulong * data()  const  { return a_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  s_[k] = m1_[k];
        for (ulong k=0; k<=n_; ++k)  f_[k] = k;
        j_ = n_;
    }

    bool next()
    {
        const ulong j = f_[0];
        f_[0] = 0;

        if ( j>=n_ )  return false;  // current is last

        j_ = j;  // save position of change

        const ulong m1j = m1_[j];
        ulong aj = a_[j];

        if ( aj==m1j )  aj = 0;
        else            ++aj;
        a_[j] = aj;

        ulong sj = s_[j];
        if ( sj==aj )
        {
            if ( sj == 0 )  sj = m1j;
            else            --sj;
            s_[j] = sj;

            f_[j] = f_[j+1];
            f_[j+1] = j + 1;
        }

        return true;
    }
    // could add prev() and last() (but have them in mixedradix_modular_gray2)

    ulong pos()  const  { return j_; }  // position of last change

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


#endif  // !defined HAVE_MIXEDRADIX_MODULAR_GRAY_H__
