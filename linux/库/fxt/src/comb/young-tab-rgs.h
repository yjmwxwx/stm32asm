#if !defined  HAVE_YOUNG_TAB_RGS_H__
#define       HAVE_YOUNG_TAB_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-young-tab-rgs.h"
#include "comb/is-shifted-young-tab-rgs.h"
#include "comb/young-tab-rgs-descents.h"

#include "comb/print-young-tab-rgs-aa.h"
#include "comb/comb-print.h"

#include "fxttypes.h"

//#include "jjassert.h"


class young_tab_rgs
// Restricted growth strings (RGS) for standard Young tableaux:
// the k-th occurrence of a digit d in the RGS must precede
// the k-th occurrence of the digit d+1.
// Lexicographic order.
// The strings are also called ballot sequences.
// Cf. OEIS sequences A000085 (all tableaux),
//   A001405 (tableaux with height <= 2, central binomial coefficients)
//   A001006 (tableaux with height <= 3, Motzkin numbers)
//   A005817 (height <= 4),  A049401 (height <= 5),  A007579 (height <= 6)
//   A007578 (height <= 7),  A007580 (height <= 8),  A212915 (height <= 9),
//   A212916 (height <= 10).
//   A001189 (height <= n-1),
//   A014495 (height = 2),  A217323 (height = 3),  A217324 (height = 4),
//   A217325 (height = 5),  A217326 (height = 6),  A217327 (height = 7),
//   A217328 (height = 8).
// Cf. A182172 (tableaux of n cells and height <= k).
// Cf. OEIS sequences A061343 (all shifted tableaux; using condition is_shifted(1)),
//   A210736 (shifted, height <= 2), A082395 (shifted, height <= 3).
// Cf. OEIS sequences A161125 (descent numbers), A225617 (strict inversions),
//   and A225618 (weak inversions).
{
public:
    ulong *a_;   // RGS
    ulong *st_;  // stats: st[j] is the number of occurrences of j in a[]
    // st[] contains a partition of n (as weakly decreasing list).

    ulong n_;   // length of string
    ulong m_;   // number of allowed values for digits (== max height of tableaux)
    ulong h_;   // height: number of different digits used in a[] (==1 + max digit)

    ulong *r_;   // aux for inversions: r[i] is the row (>=1) the entry i lies in
    // generated on demand only;  elements considered mutable

private:  // have pointer data
    young_tab_rgs(const young_tab_rgs&);  // forbidden
    young_tab_rgs & operator = (const young_tab_rgs&);  // forbidden

public:
    explicit young_tab_rgs(ulong n, ulong m=0)
    // Should have n >= 1 (for n==0 we take n=1).
    {
        n_ = (n ? n : 1);
        a_ = new ulong[n_];

        if ( m > n_ )  m = n_;  // avoid inefficiency (unreachable m)
        if ( m==0 )  m = n_;    // zero means all
        m_ = m;

//        st_ = new ulong[m_];
        st_ = new ulong[n_]; // excess elements for is_young_tab_rgs()

        r_ = new ulong[n_];

        first();
    }

    ~young_tab_rgs()
    {
        delete [] a_;
        delete [] st_;
        delete [] r_;
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<m_; ++k)  st_[k] = 0;
        st_[0] = n_;
        h_ = 1;
    }


private:

    bool try_incr(ulong j)
    // Increment a[j] if possible.
    // At entry st[1,2,...,m-1] must be valid for a[0,1,...,j].
    // At return st[1,2,...,m-1] is valid for a[0,1,...,j-1].
    {
        const ulong d = a_[j];
        const ulong st0 = st_[d] - 1;
        st_[d] = st0;  // (decremented) number of digits d

        h_ -= ( st0 == 0 );  // update height
        const ulong mm = h_ - ( m_ == h_ );

        for (ulong d1=d+1; d1<=mm; ++d1)  // optimized, scanning fewer candidates
        {
            ulong st1 = st_[d1] + 1; // (incremented) number of digits d

            if ( st1 <= st0 )  // can increment
            {
                a_[j] = d1;
                st_[d1] = st1;
                h_ += ( st1 == 1 );  // update height
                return true;
            }
        }

        // cannot increment, set digit to zero:
        a_[j] = 0;
        // do _not_ record zeros in suffix; done only at end of next()

        return false;
    }


public:

    ulong next()
    // Return leftmost changed index.
    // Return 0 if current string is last.
    {
        ulong j = n_;  // index of digit trying to increment
        ulong z = 0;   // count zeros filled in while trying to increment
        do
        {
            --j;
            if ( try_incr(j) )  break;
            ++z;  // we left a zero at a[j]

//            jjassert( is_young_tab_rgs(a_, j, st_, true) );

        }
        while ( j );

        st_[0] += z;  // now record zeros written

//        if ( j==0 )  first();  // current is last

        return j;
    }


    const ulong * data()  const  { return a_; }
    const ulong * pdata()  const  { return st_; }


    ulong height()  const
    // Return height of tableaux (== 1 + largest digit used).
    { return h_; }

    ulong first_idx(ulong d)  const
    // Return index of first occurence of d.
    // n is returned if d is not a digit in the word a[].
    {
        for (ulong j=0; j<h_; ++j)
            if ( a_[j] == d )
                return j;
        return n_;
    }

    ulong descent_set(ulong *d)  const
    // A descent in a standard Young tableau is an entry i
    // such that i+1 lies strictly below and weakly left of i.
    { return young_tab_rgs_descent_set(data(), n_, d); }

    ulong major_index()  const
    // The major index is the sum of all i that are descents.
    { return young_tab_rgs_major_index(data(), n_); }

    ulong descent_number()  const
    // The descent number is the number of descents.
    { return young_tab_rgs_descent_number(data(), n_); }

private:
    void make_r()  const
    // compute r[]
    {
        if ( n_==0 )  return;
        // we consider elements of r[] as mutable
        for (ulong k=0; k<n_; ++k)  r_[k] = 0;
        for (ulong j=0; j<height(); ++j)  // rather inefficient
        {
            for (ulong i=0, z=0; z<st_[j]; ++i)
                if ( a_[i] == j )  r_[i] += (z+=1);
        }
    }

public:
    ulong number_strict_inversions()  const
    // A (strict) inversion is a pair (i,j) with i<j where
    // j appears strictly below and strictly left of i.
    {
        if ( n_ <= 2 )  return 0;
        make_r();
        ulong ni = 0;
        for (ulong i=0; i<n_-1; ++i)
        {
            for (ulong j=i+1; j<n_; ++j)
                if ( (a_[j] > a_[i]) & (r_[j] < r_[i]) )
                    ni += 1;
        }
        return ni;
    }

    ulong number_weak_inversions()  const
    // A weak inversion is a pair (i,j) with i<j where
    // j appears weakly below and weakly left of i.
    {
        if ( n_ <= 1 )  return 0;
        make_r();
        ulong ni = 0;
        for (ulong i=0; i<n_-1; ++i)
        {
            for (ulong j=i+1; j<n_; ++j)
                if ( (a_[j] >= a_[i]) & (r_[j] <= r_[i]) )
                    ni += 1;
        }
        return ni;
    }



    bool is_delayed(ulong s=1)  const
    // Return whether the first occurence of a digit d is
    // preceded by at least s+1 occurences of d-1.
    // Always true for s==0.
    {
#if 1
        return is_delayed_young_tab_rgs(data(), n_, height(), s);
#else
        const ulong h = height();
        for (ulong d=0; d<h; ++d)
        {
            ulong ct0 = 0, ct1 = 0;
            for (ulong k=0; k<n_; ++k)
            {
                ct0 += (a_[k]==d);
                ct1 += (a_[k]==d+1);
                if ( ct1 != 0 )
                    if ( (ct1 - ct0) < s )  return false;
            }
        }
        return true;
#endif
    }

    bool is_falling(ulong s=1)  const
    // Return whether falling multiplicities with difference at least s.
    // Same as: allowing only partitions into distinct parts (with diff>=s).
    // Always true for s==0.
    {
#if 1
        return is_falling_young_tab_rgs(pdata(), height(), s);
#else
        const ulong md = height() - 1;
        for (ulong j=md; j>0; --j)
            if ( st_[j-1] - st_[j] < s )
                return false;
        return true;
#endif
    }

    bool is_shifted(ulong s=1)  const
    // Return whether still valid if row k is shifted to the right
    //  by s positions with respect to row k-1.
    // Always true for s==0.
    {
#if 1
        return is_shifted_young_tab_rgs(data(), pdata(), n_, height(), s);
#else
        if ( ! is_falling(s) )  return false;
        if ( ! is_delayed(s) )  return false;
        return true;
#endif
    }

    bool is_strict()  const  // same as: is_shifted( 1 )
    // Return whether the number of occurrences of k in any prefix
    // is strictly greater than the number of occurrences of k+1.
    {
        ulong ct[n_];  // alloca
        for (ulong j=0; j<n_; ++j)  ct[j] = 0;
        for (ulong j=0; j<n_; ++j)
        {
            ulong t = a_[j];
            ct[t] += 1;
            if ( t != 0  && ct[t]==ct[t-1] )  return false;
        }
        return true;
    }

    bool has_shape(const ulong *st, ulong h)
    {
        if ( h != h_ ) return false;
        for (ulong j=0; j<h; ++j)
            if ( st[j] != st_[j] )  return false;
        return true;
    }

    bool is_chess_tableau()  const
    // In a chess tableau the odd numbered cells appear in the first,
    //   third, fifth, etc., skew diagonal, and the even numbered cells
    //   appear in the second, fourth, sixth, etc., skew diagonal.
    // Cf. A238014
    {
#if 1
        // As ballot sequences (with least element and first index
        // either both 0 or both 1) with index of first occurrence of
        // each element e of same parity as e, and identical elements
        // separated by an even number of different elements.

        // could speed up using temp array
        for (ulong e=0; e < height(); ++e)  // for all rows
        {
            bool q = false;  // whether an element e has been seen
            ulong p = 0;  // position
            for (ulong i=e; i<n_; ++i)
            {
                ulong t = a_[i];
                if ( t == e )  // we are in row e
                {
                    const ulong m = 2UL;
                    if ( q )
                    {
                        if ( (i-p) % m != 1  )  return false;
                    }
                    else
                    {
                        if ( (i % m) != (e % m)  )  return false;
                        q = true;
                    }
                    p = i;
                }
            }
        }
        return true;
#else
        // As ballot sequences (with least element zero) with first,
        // third, fifth, ... occurence of even elements in even
        // positions, second, fourth, sixth, ... in odd positions;
        // first, third, fifth, ... occurence of odd elements in odd
        // positions, second, fourth, sixth, ... in even positions.

        // could speed up using temp array ct[]
        for (ulong e=0; e < height(); ++e)  // for all rows
        {
//            ulong ct = 0;
            ulong ct = e & 1;
            for (ulong i=0; i<n_; ++i)
            {
                ulong t = a_[i];
                if ( t == e )  // we are in row e
                {
                    if ( (1UL & (i ^ ct)) != 0 )  return false;
                    ct += 1;
                }
            }
        }
        return true;
#endif
    }


    bool OK()  const
    {
        const ulong h = height();  // height OK?
        if ( n_ != 0 )
        {
            if ( st_[h-1] == 0 )  return false;
            if ( h < n_ )
                if ( st_[h] != 0 )  return false;
        }

        return  is_young_tab_rgs(a_, n_, st_, true);
    }


    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz ); }

    void print1(const char *bla)  const
    { print_vec1(bla, data(), n_ ); }

    void print_stats(const char *bla, bool dfz=true)  const
    { print_vec(bla, st_, n_, dfz ); }

    void print_aa(ulong off=1)  const  // ASCII art
    { print_young_tab_rgs_aa(data(), st_, n_, off); }

    void print_r(const char *bla, bool dfz=true)  const
    {
        make_r();
        print_vec(bla, r_, n_, dfz );
    }
};
// -------------------------


#endif  // !defined HAVE_YOUNG_TAB_RGS_H__
