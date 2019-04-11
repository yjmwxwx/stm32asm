#if !defined  HAVE_KSUBSET_GRAY_H__
#define       HAVE_KSUBSET_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "aux0/swap.h"
#include "comb/comb-print.h"


class ksubset_gray
// k-subsets (kmin<=k<=kmax) of the set {1,2,...,n}
// in minimal-change (Gray code) order.
// Algorithm following Jenkyns ("Loopless Gray Code Algorithms")
// Limitation: cannot mix calls to next() and prev().
{
public:
    ulong n_;   // k-subsets of {1, 2, ..., n}
    ulong kmin_, kmax_;  // kmin <= k <= kmax
    ulong k_;   // k elements in current set
    ulong *S_;  // set in S[1,2,...,k] with elements \in {1,2,...,n}
    ulong j_;   // aux

private:  // have pointer data
    ksubset_gray(const ksubset_gray&);  // forbidden
    ksubset_gray & operator = (const ksubset_gray&);  // forbidden

public:
    explicit ksubset_gray(ulong n, ulong kmin, ulong kmax)
    {
        n_ = (n>0 ? n : 1);
        // Must have 1<=kmin<=kmax<=n
        kmin_ = kmin;
        kmax_ = kmax;
        if ( kmax_ < kmin_ )  swap2(kmin_, kmax_);
        if ( kmin_==0 )  kmin_ = 1;

        S_ = new ulong[kmax_+1];
        S_[0] = 0;  // sentinel: != 1
        first();
    }

    ~ksubset_gray()  { delete [] S_; }
    const ulong * data()  const  { return S_+1; }
    ulong num()  const  { return k_; }

    ulong last()
    {
        S_[1] = 1;  k_ = kmin_;
        if ( kmin_==1 )  { j_ = 1; }
        else
        {
            for (ulong i=2; i<=kmin_; ++i)  { S_[i] = n_ - kmin_ + i; }
            j_ = 2;
        }
        return k_;
    }


    ulong first()
    {
        k_ = kmin_;
        for (ulong i=1; i<=kmin_; ++i)  { S_[i] = n_ - kmin_ + i; }
        j_ = 1;
        return k_;
    }

    bool is_first()  const  { return ( S_[1] == n_ - kmin_ + 1 );  }

    bool is_last()  const
    {
        if  ( S_[1] != 1  )   return 0;
        if ( kmin_<=1 )  return (k_==1);
        return  (S_[2]==n_-kmin_+2);
    }

private:
    void prev_even()
    {
        ulong &n=n_, &kmin=kmin_, &kmax=kmax_, &j=j_;
        if ( S_[j-1] == S_[j]-1 )  // can read sentinel S[0]
        {
            S_[j-1] = S_[j];
            if ( j > kmin )
            {
                if ( S_[kmin] == n )  { j = j-2; }  else  { j = j-1; }
            }
            else
            {
                S_[j] = n - kmin + j;
                if ( S_[j-1]==S_[j]-1 )  { j = j-2; }
            }
        }
        else
        {
            S_[j] = S_[j] - 1;
            if ( j < kmax )
            {
                S_[j+1] = S_[j] + 1;
                if ( j >= kmin-1 )  { j = j+1; }  else  { j = j+2; }
            }
        }
    }

    void prev_odd()
    {
        ulong &n=n_, &kmin=kmin_, &kmax=kmax_, &j=j_;
        if ( S_[j] == n )  { j = j-1; }
        else
        {
            if ( j < kmax )
            {
                S_[j+1] = n;
                j = j+1;
            }
            else
            {
                S_[j] = S_[j]+1;
                if ( S_[kmin]==n )  { j = j-1; }
            }
        }
    }

public:
    ulong prev()
    {
        if ( is_first() )  { last(); return 0; }

        if ( j_&1 )  prev_odd();
        else         prev_even();

        if ( j_<kmin_ )  { k_ = kmin_; }  else  { k_ = j_; };

        return k_;
    }

    ulong next()
    {
        if ( is_last() )  { first();  return 0; }

        if ( j_&1 )  prev_even();
        else         prev_odd();

        if ( j_<kmin_ )  { k_ = kmin_; }  else  { k_ = j_; };

        return k_;
    }

    void print_set(const char *bla=0)  const
    { ::print_set(bla, S_+1, k_); }

    void print_deltaset(const char *bla=0)  const
    { print_set1_as_deltaset(bla, S_+1, k_, n_); }
};
// -------------------------


#endif  // !defined HAVE_KSUBSET_GRAY_H__
