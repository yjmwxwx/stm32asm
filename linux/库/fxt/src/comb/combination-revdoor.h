#if !defined  HAVE_COMBINATION_REVDOOR_H__
#define       HAVE_COMBINATION_REVDOOR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
//#include "jjassert.h"
#include "comb/comb-print.h"


class combination_revdoor
// Combinations (n choose k) in minimal-change order.
// "Revolving door" algorithm following Knuth.
// See:
//   W. H. Payne, F. M. Ives: "Combination Generators",
//   ACM Transactions on Mathematical Software (TOMS),
//   vol.5, no.2, pp.163-172, June-1979.
{
public:
    ulong *c_;  // delta set
    ulong n_, k_;  // (n choose k)  n>=1,  1<=k<=n

private:  // have pointer data
    combination_revdoor(const combination_revdoor&);  // forbidden
    combination_revdoor & operator = (const combination_revdoor&);  // forbidden

public:
    explicit combination_revdoor(ulong n, ulong k)
    // Must have:  1 <= k <= n
    {
        n_ = n;  // (n ? n : 1);
        k_ = k;
//        if ( k>n_ )  k=n;
//        else { if ( k==0 )  k=n; }

        c_ = new ulong[k_+1];  // incl. sentinel
        first();
    }

    ~combination_revdoor()  { delete [] c_; }

    void first()
    {
        for (ulong j=0; j<k_; ++j)  c_[j] = j;
        c_[k_] = n_;  // sentinel
    }

    const ulong* data()  const  { return c_; }

    bool next()
    {
        ulong j = 1;
        // R3: [Easy case?]
        if ( k_ & 1 )  // odd k (try to increase)
        {
            ulong c = c_[0] + 1;
            if ( c < c_[1] )  { c_[0] = c;  return true; }
            else goto R4;
        }
        else  // even k (try to decrease)
        {
            ulong c = c_[0];
            if ( c )  { c_[0] = c-1;  return true; }
            else goto R5;
        }

    R4:  // R4: [Try to decrease]
        if ( j==k_ )  return false;

//        jjassert( c_[j] == c_[j-1]+1 );
        if ( c_[j] > j )
        {
            c_[j] = c_[j-1];
            c_[j-1] = j-1;
            return true;
        }
        ++j;

    R5:  // R5: [Try to increase]
        if ( j==k_ )  return false;

//        jjassert( c_[j-1] == j-1 );
        {
            ulong c = c_[j] + 1;
            if ( c < c_[j+1] )  // can read sentinel
            {
                c_[j-1] = c - 1;
                c_[j] = c;
                return true;
            }
        }
        ++j;
        goto R4;
    }

    void print_set(const char *bla=0)  const
    { ::print_set(bla, c_, k_); }

    void print_deltaset(const char *bla=0)  const
    { print_set_as_deltaset(bla, c_, k_, n_); }
};
// -------------------------


#endif  // !defined HAVE_COMBINATION_REVDOOR_H__
