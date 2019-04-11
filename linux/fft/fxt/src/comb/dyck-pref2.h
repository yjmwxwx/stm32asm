#if !defined  HAVE_DYCK_PREF2_H__
#define       HAVE_DYCK_PREF2_H__
// This file is part of the FXT library.
// Copyright (C) 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


class dyck_pref2
// k-ary Dyck words
// Algorithm "coolKat" as given (right in figure "Algorithms 1") in
//   Stephane Durocher, Pak Ching Li, Debajyoti Mondal, Aaron Williams:
//   "Ranking and Loopless Generation of k-ary Dyck Words in Cool-lex Order",
//   The 22nd International Workshop on Combinatorial Algorithms,
//   Victoria, Canada, IWOCA, (2011).
{
public:
    ulong *B_;   // Dyck word as delta set (length=k*n=len); one-based array!
    ulong *A_;   // aux., length n-2
    ulong n_;    // number of ones (variable t in the paper)
    ulong k_;    // k-ary Dyck words
//    ulong k1n_;  // ==(k-1)*n, number of zeros
    ulong n1k_;  // ==k*(n-1), aux
    ulong len_;  // == k*n (length of Dyck words)
    ulong x_, y_;  // aux

private:  // have pointer data
    dyck_pref2(const dyck_pref2&);  // forbidden
    dyck_pref2 & operator = (const dyck_pref2&);  // forbidden

public:
    explicit dyck_pref2(ulong n, ulong k)
    // Must have:  n>=1,  k>=1.
    {
        n_ = n;
        k_ = k;
        n1k_ = (n-1)*k;
        len_ = k*n;
        x_ = n_;  y_ = n_;

        // arrays are one-based:
        A_ = new ulong[n_-1];
        A_[0] = 0;  // unused
        B_ = new ulong[len_+1];
        B_[0] = 0;  // unused
        first();
    }

    ~dyck_pref2()
    {
        delete [] A_;
        delete [] B_;
    }

    void first()
    {
        for (ulong j=1; j<=n_; ++j)  B_[j] = 1;
        for (ulong j=n_+1; j<=len_; ++j)  B_[j] = 0;
    }

    const ulong * data()  const  { return B_+1; }

    bool next()
    {
        if ( x_ > n1k_ )  return false;  // current is last
        B_[x_] = 0;  B_[y_] = 1;
        ++x_;  ++y_;
        if ( B_[x_]==0 )
        {
            if ( x_-2 == k_*(y_-2) )
            {
                if ( 1==B_[x_+1] )  A_[y_-2] = 0;
                ++A_[y_-2];
                x_ += A_[y_-2];
            }
            else
            {
                B_[x_] = 1;
                B_[2] = 0;
                if ( y_>3 )  x_ = 3;
                y_ = 2;
            }
        }
        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_DYCK_PREF2_H__
