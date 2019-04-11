#if !defined HAVE_COMPOSITION_NZ_WEAKLY_UNIMODAL_H__
#define      HAVE_COMPOSITION_NZ_WEAKLY_UNIMODAL_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-composition-nz.h"
#include "comb/is-unimodal.h"

#include "comb/comb-print.h"
#include "comb/print-composition-aa.h"

#include "fxttypes.h"

//#include "jjassert.h"


class composition_nz_weakly_unimodal
// Weakly unimodal compositions, lexicographic order.
// Cf. OEIS sequence A001523.
{
public:
    ulong *a_;  // composition: n = a[1] + a[2] + ... + a[m]
    ulong n_;   // compositions of n
    ulong m_;   // number of parts in current composition
    ulong pg1_; // position of last part > 1 (initially == n + 1)
    ulong mv_;  // value of maximal digit(s)

private:  // have pointer data
    composition_nz_weakly_unimodal(const composition_nz_weakly_unimodal&);  // forbidden
    composition_nz_weakly_unimodal & operator = (const composition_nz_weakly_unimodal&);  // forbidden

public:
    explicit composition_nz_weakly_unimodal(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+1];
        a_[0] = 0;  // unused

        first();
    }

    ~composition_nz_weakly_unimodal()
    {
        delete [] a_;
    }

    const ulong * data()  const  { return a_ + 1; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
        mv_ = ( n_ != 0 );
        pg1_ = n_ + 1;  // never read for n<=1
    }

public:

    ulong next()
    // Return number of parts.
    // Return zero if current composition is last.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        const ulong m1 = m_ - 1;
        const ulong z = a_[m_];
        a_[m_] = 1;
        const ulong y = a_[m1];
        const ulong y1 = y + 1;

        if ( pg1_ < m1 )  // easy case: move pg1
        {
            ++pg1_;
            ++a_[pg1_];
            m_ += z - 2;
            return m_;
        }

        if ( z == mv_ )  // easy case: increment second last
        {
            a_[m1] = y1;
            mv_ = y1;
            pg1_ = m1;
            m_ += z - 2;
            return m_;
        }

        if ( y == mv_ )  // easy case: increment second last
        {
            a_[m1] = y1;
            mv_ = y1;
            pg1_ = m1;
            m_ += z - 2;
            return m_;
        }

//        jjassert( m_>=3 );  // else y or z where maximal
        ulong s = z;
        ulong j = m1;
        while ( a_[j-1] == y )  // scan to the left
        {
            s += y;
            a_[j] = 1;
            --j;
        }
        m_ = j + s - 1;
        a_[j] = y1;
        pg1_ = j;
        // mv_ unchanged

        return m_;
    }


    ulong num_parts()  const  { return m_; }
    ulong max_part()  const  { return mv_; }

    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )  return false;

        if ( pg1_ <= n_ )  if ( a_[pg1_] < 2 )  return false;

        ulong mx = 0;  // max OK ?
        for (ulong j=1; j<=m_; ++j)
            if ( a_[j] > mx )  mx = a_[j];
        if ( mx != mv_ )  return false;

        if ( ! is_weakly_unimodal(a_+1, m_) )  return false;

        return  true;
    }

    void print(const char *bla)  const
    { print_vec(bla, a_+1, m_); }

    void print_aa()  const  // ASCII art
    { print_composition_aa(a_+1, m_); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_WEAKLY_UNIMODAL_H__
