#if !defined  HAVE_DYCK_GRAY_H__
#define       HAVE_DYCK_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


//#include "comb/is-dyck-rgs.h"

#include "fxttypes.h"


class dyck_gray
// Gray code for k-ary Dyck words with all transitions homogenous.
// Loopless algorithm following
//   Dominique Roelants van Baronaigien:
//   "A Loopless Gray-Code Algorithm for Listing k-ary Trees",
//   Journal of Algorithms, vol.35, pp.100-107, (2000).
{
public:
    ulong *sq_;  // sequence of bit positions (seq[])  elements \in {1,2,...,n}
    ulong *dr_;  // aux: direction            (dir[])
    ulong *np_;  // aux: next position        (nextPos[])
    ulong *mx_;  // aux: max position         (max[])
    ulong n_;    // n (internal) nodes
    ulong k_;    // k-ary Dyck words
//    ulong sqi_;  // last value of sq_[i]  (aux: for delta set)

private:  // have pointer data
    dyck_gray(const dyck_gray&);  // forbidden
    dyck_gray & operator = (const dyck_gray&);  // forbidden

public:
    explicit dyck_gray(ulong n, ulong k)
    // Must have k >= 2.
    {
        n_ = n;
        k_ = k;

        // all arrays are one-based:
        sq_ = new ulong[n_+1];
        dr_ = new ulong[n_+1];
        np_ = new ulong[n_+2];  // last is sentinel (index n+1)
        mx_ = new ulong[n_+1];  // unchanged in next()
        first();
    }

    ~dyck_gray()
    {
        delete [] sq_;
        delete [] dr_;
        delete [] np_;
        delete [] mx_;
    }

    void first(ulong k=0)
    {
        if ( k )  k_ = k;
        for (ulong j=1, e=1; j<=n_; ++j, e+=k_)  sq_[j] = mx_[j] = e;
        for (ulong j=0; j<=n_; ++j)  dr_[j] = 1;  // "right"
        for (ulong j=0; j<=n_+1; ++j)  np_[j] = j - 1;
//        sqi_ = n_ - 1;
    }

    const ulong * data()  const  { return sq_+1; }

    ulong next()
    {
        ulong i = np_[n_+1];

        if ( i==1 )  return 0;  // current string is last

//        sqi_ = sq_[i] - 1;  // save last value

        if ( dr_[i]==1 )  // direction == "right"
        {
            if ( sq_[i] == mx_[i] )   sq_[i] = sq_[i-1] + 1;
            else                      sq_[i] += 1;

            if ( sq_[i] == mx_[i] - 1 )
            {
                np_[i+1] = np_[i];  // can access sentinel
                np_[i] = i - 1;
                dr_[i] = -1UL;      // "left"
            }
        }
        else
        {
            if ( sq_[i] == sq_[i-1] + 1 )
            {
                sq_[i] = mx_[i];
                dr_[i] = 1;         // "right"
                np_[i+1] = np_[i];  // can access sentinel
                np_[i] = i - 1;
            }
            else  sq_[i] -= 1;
        }

        if ( i<n_ )  np_[n_+1] = n_;

        return i - 1;
    }

//    bool OK()  const  // need another test
//    { return is_dyck_rgs( sq_, n_, k_ ); }
};
// -------------------------


#endif  // !defined HAVE_DYCK_GRAY_H__
