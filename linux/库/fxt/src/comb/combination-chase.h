#if !defined  HAVE_COMBINATION_CHASE_H__
#define       HAVE_COMBINATION_CHASE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "sort/minmaxmed23.h"  // max2()
#include "fxttypes.h"


class combination_chase
// Combinations (n choose k) in strong minimal-change order.
// The delta set is generated.
// "Chase's sequence", algorithm as given by Knuth.
{
public:
    ulong n_;  // (n choose k)  n>=1
    ulong k_;  // 1<=k<=n
    ulong s_;  // == n_ - k_
    ulong t_;  // == n_ - s_
    ulong r_;  // aux
    ulong *a_;  // data (a delta set)
    ulong *w_;  // aux

private:  // have pointer data
    combination_chase(const combination_chase&);  // forbidden
    combination_chase & operator = (const combination_chase&);  // forbidden

public:
    explicit combination_chase(ulong n, ulong k)
    {
        n_ = (n ? n : 1);
        k_ = k;
        if ( k>n_ )  k=n;
        else { if ( k==0 )  k=n; }

        t_ = k_;
        s_ = n_ - t_;

        a_ = new ulong[n_];
        w_ = new ulong[n_+1];
        first();
    }

    ~combination_chase()
    {
        delete [] a_;
        delete [] w_;
    }

    void first()
    {
        ulong j;
        for (j=0; j<s_; ++j)  a_[j] = 0;
        for (  ; j<n_; ++j)  a_[j] = 1;
        for (ulong i=0; i<=n_; ++i)  w_[i] = 1;
        r_ = (s_>0 ? s_ : t_);
    }

    const ulong * data()  const  { return a_; }

    bool next()
    {
        // C3: [Find j and branch]
        ulong j = r_;
        while ( 0==w_[j] )  { w_[j]=1; ++j; }
        if ( j==n_ )  return false;
        w_[j] = 0;
        if ( 0!=a_[j] )
        {
            if ( j & 1 )  goto C4;  // j odd
            else          goto C5;  // j even
        }
        else  // 0==a_[j]
        {
            if ( j & 1 )  goto C7;  // j odd
            else          goto C6;  // j even
        }

        C4:  // C4: [Move right one]
            a_[j-1] = 1;
            a_[j] = 0;
            if ( (r_==j) && (j>1) )  r_ = j - 1;
            else  if ( r_==j-1 )     r_ = j;
            return true;

        C5:  // C5: [Move right two]
            if ( 0!=a_[j-2] )  goto C4;
            a_[j-2] = 1;
            a_[j] = 0;
            if ( r_==j )          r_ = max2(j-2, 1UL);
            else  if ( r_==j-2 )  r_ = j - 1;
            return true;

        C6:  // C6: [Move left one]
            a_[j] = 1;
            a_[j-1] = 0;
            if ( (r_==j) && (j>1) )  r_ = j - 1;
            else  if ( r_==j-1 )     r_ = j;
            return true;

        C7:  // C7: [Move left two]
            if ( 0!=a_[j-1] )  goto C6;
            a_[j] = 1;
            a_[j-2] = 0;
            if ( r_==j-2 )        r_ = j;
            else  if ( r_==j-1 )  r_ = j - 2;
            return true;
    }
};
// -------------------------


#endif  // !defined HAVE_COMBINATION_CHASE_H__
