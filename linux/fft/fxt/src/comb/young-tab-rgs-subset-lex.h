#if !defined  HAVE_YOUNG_TAB_RGS_SUBSET_LEX_H__
#define       HAVE_YOUNG_TAB_RGS_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-young-tab-rgs.h"
#include "comb/is-shifted-young-tab-rgs.h"

#include "comb/print-young-tab-rgs-aa.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


class young_tab_rgs_subset_lex
// Restricted growth strings (RGS) for standard Young tableaux:
// the k-th occurrence of a digit d in the RGS must precede
// the k-th occurrence of the digit d+1.
// Subset-lex order.
// Cf. OEIS sequences A000085 (all tableaux),
// A061343 (all shifted tableaux; using condition is_shifted(1)),
// A210736 (shifted, height <= 2), A082395 (shifted, height <= 3).
{
public:
    ulong *a_;   // RGS
    ulong *st_;  // stats: st[j] is the number of occurrences of j in a[]
    // st[] contains a partition of n

    ulong tr_;  // track: position of last non-zero digit
    ulong n_;   // length of string
    ulong h_;   // height: number of different digits used in a[] (==1 + max digit)

private:  // have pointer data
    young_tab_rgs_subset_lex(const young_tab_rgs_subset_lex&);  // forbidden
    young_tab_rgs_subset_lex & operator = (const young_tab_rgs_subset_lex&);  // forbidden

public:
    explicit young_tab_rgs_subset_lex(ulong n)
    // Should have n >= 1 (for n==0 we take n=1).
    {
        n_ = (n ? n : 1);
        a_ = new ulong[n_+1];
        a_[0] = 0;  // sentinel

        st_ = new ulong[n_+2];
        st_[n_] = 0;  // sentinel
        st_[n_+1] = 1;  // sentinel

        first();
    }

    ~young_tab_rgs_subset_lex()
    {
        delete [] a_;
        delete [] st_;
    }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  st_[k] = 0;
        st_[0] = n_;
        tr_ = 1;
        h_ = 1;
    }


private:
    ulong next_dig(ulong d)  const
    {
        ulong sd = st_[d];
        ulong d1 = d + 1;
        ulong sd1 = st_[d1];
        while ( sd1 == sd )
        {
            d = d1;
            d1 += 1;
            sd = sd1;
            sd1 = st_[d1];
        }
        return d1;
    }

    ulong prev_dig(ulong d)  const
    {
        d -= 1;
        if ( d==0 )  return 0;
        ulong sd = st_[d];
        ulong d1 = d - 1;
        ulong sd1 = st_[d1];
        while ( sd == sd1 )
        {
            d = d1;
            if ( d==0 )  break;
            d1 -= 1;
            sd = sd1;
            sd1 = st_[d1];
        }
        return d;
    }


public:
    ulong next()
    // Return leftmost changed index.
    // Return 0 if current string is last.
    {
        ulong j = tr_;  // index of digit trying to increment

        const ulong st0 = st_[0];
        ulong z0 = n_ - tr_;  // number of zeros to the right
        st_[0] = st0 - z0;  // temporarily change stats for zero

        ulong d = a_[j];  // digit we are looking at
        st_[d] -= 1;  // update stats
        ulong d1 = next_dig(d);

        if ( d1 < n_ )  // can increment
        {
            a_[j] = d1;
            st_[d1] += 1;   // update stats
            st_[0] = st0;   // restore stats for zero
            h_ += ( d1 >= h_ );  // update height
            return tr_ - 1;
        }

        st_[d] += 1;  // restore stats (could not increment digit d)

        if ( tr_ < n_ )  // can append digit
        {
            d1 = next_dig(0);
            tr_ += 1;
            a_[tr_] = d1;
            st_[0] = st0 - 1;  // restore stats for zero
            st_[d1] += 1;  // update stats
            h_ += ( d1 >= h_ );  // update height
            return tr_ - 1;
        }

        // have to change 2 or 3 digits:

        if ( st0 >= n_ - 1 )  return 0;  // current is last

        const ulong w = a_[j];
        a_[j] = 0;
        st_[w] -= 1;  // update stats

        // find previous nonzero digit:
        do  { j -= 1; }  while ( 0==a_[j] );
        d = a_[j];

        z0 = n_ - j;  // number of zeros to the right
        st_[0] = st0 - z0;  // temporarily change stats for zero
        st_[d] -= 1;  // update stats

        st_[0] += 1;   // temporarily change stats for zero
        d1 = prev_dig(d);
        const ulong d1z = (d1 == 0);

        a_[j] = d1;
        st_[d1] += 1;  // update stats

        j += 1;
        z0 = n_ - j;  // number of zeros to the right
        st_[0] = st0 - z0 + d1z;  // temporarily change stats for zero
        const ulong d2 = next_dig(0);

        a_[j] = d2;
        st_[d2] += 1;

        st_[0] = st0 + d1z;  // restore stats

        // update height:
        h_ -= 1;
        h_ -= (st_[h_-1]==0);

        tr_ = j;
        return tr_ - 1;
    }


    const ulong * data()  const  { return a_ + 1; }
    const ulong * pdata()  const  { return st_; }


    ulong height()  const
    // Return height of tableaux (== 1 + largest digit used).
    { return h_; }

    ulong first_idx(ulong d)  const
    // Return index of first occurence of d.
    // n is returned if d is not a digit in the word a[].
    {
        for (ulong j=1; j<=h_; ++j)
            if ( a_[j] == d )
                return j - 1;
        return n_;
    }


    bool is_delayed(ulong s=1)  const
    // Return whether the first occurence of a digit d is
    // preceded by at least s+1 occurences of d-1.
    // Always true for s==0.
    { return is_delayed_young_tab_rgs(data(), n_, height(), s); }

    bool is_falling(ulong s=1)  const
    // Return whether falling multiplicities with difference at least s.
    // Same as: allowing only partitions into distinct parts (with diff>=s).
    // Always true for s==0.
    { return is_falling_young_tab_rgs(pdata(), height(), s); }

    bool is_shifted(ulong s=1)  const
    // Return whether still valid if row k is shifted to the right
    //  by s positions with respect to row k-1.
    // Always true for s==0.
    { return is_shifted_young_tab_rgs(data(), pdata(), n_, height(), s); }

    bool has_shape(const ulong *st, ulong h)
    {
        if ( h != h_ ) return false;
        for (ulong j=0; j<h; ++j)
            if ( st[j] != st_[j] )  return false;
        return true;
    }


    bool OK()  const
    {
        const ulong h = height();  // height OK?
        if ( n_ != 0 )
        {
            if ( st_[h-1] == 0 )  return false;
            if ( st_[h] != 0 )  return false;
        }

        return  is_young_tab_rgs(data(), n_, st_, true);
    }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz ); }

    void print1(const char *bla)  const
    { print_vec1(bla, data(), n_ ); }

    void print_stats(const char *bla, bool dfz=true)  const
    { print_vec(bla, st_, n_, dfz ); }

    void print_aa(ulong off=1)  const  // ASCII art
    { print_young_tab_rgs_aa(data(), st_, n_, off); }
};
// -------------------------


#endif  // !defined HAVE_YOUNG_TAB_RGS_SUBSET_LEX_H__
