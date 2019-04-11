#if !defined  HAVE_DYCK_RGS_SUBSET_LEX_H__
#define       HAVE_DYCK_RGS_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-dyck-rgs.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


// Cf. comb/dyck-rgs.h for Dyck RGS in lexicographic order
// Cf. comb/catalan-subset-lex.h for Catalan RGS in subset-lex order.


#define DYCK_RGS_SUBSET_LEX_SC  // whether to allow n<=1
// this gives a small slowdown

class dyck_rgs_subset_lex
// Restricted growth strings (RGS) for k-ary Dyck words, that is,
// strings a[0,1,...,n-1] where a[0]=0 and a[j] <= a[j-1] + (k-1).
// Subset-lex order.
// Loopless algorithm for predecessor (method prev()).
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
public:
    ulong *a_;  // digits of the RGS: a_[k] <= as[k-1] + 1
    ulong tr_;  // current track
    ulong n_;   // Number of digits in RGS
    ulong i_;   // k-ary Dyck words: i = k - 1
    char *str_; // Dyck word

private:  // have pointer data
    dyck_rgs_subset_lex(const dyck_rgs_subset_lex&);  // forbidden
    dyck_rgs_subset_lex & operator = (const dyck_rgs_subset_lex&);  // forbidden

public:
    explicit dyck_rgs_subset_lex(ulong n, ulong k)
    // Must have k>=2
    {
        n_ = n;
        i_ = k - 1;

        a_ = new ulong[n_+ 1 + (n_==0)];  // incl. sentinel
        a_[0] = +1;  // sentinel !=0  to catch scan to the left
        ++a_;  // nota bene
        if ( n_==0 )  a_[0] = 0;

        str_ = new char[k*n_+1];  str_[k*n_] = 0;

        first();
    }

    ~dyck_rgs_subset_lex()
    {
        --a_;
        delete [] a_;
        delete [] str_;
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        tr_ = 1;

        // make things work for n <= 1:
        if ( n_ <= 1 )  tr_ = 0;
    }

    bool next()
    {
        ulong j = tr_;
        if ( a_[j] < a_[j-1] + i_ )   // easy case 1: can increment track
        {
#ifdef DYCK_RGS_SUBSET_LEX_SC
            if ( n_ <= 1 )  return false;
#endif
            a_[j] += 1;
            return true;
        }

        const ulong j1 = j + 1;
        if ( j1 < n_ )  // easy case 2: can attach
        {
            a_[j1] = +1;
            tr_ = j1;
            return true;
        }

        a_[j] = 0;

        // Find nonzero track to the left:
        do  { --j; }  while ( a_[j] == 0 );  // can read sentinel

        if ( (long)j < 0 )  return false;  // current is last

        a_[j] -= 1;
        ++j;
        a_[j] = 1;
        tr_ = j;
        return true;
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        tr_ = n_ - 1;
        // make things work for n <= 1:
        if ( n_==0 )
        {
            tr_ = 0;
            a_[0] = 1;
        }
        if ( n_>=2 )  a_[tr_] = i_;
    }


    bool prev()
    // Loopless algorithm.
    {
#ifdef DYCK_RGS_SUBSET_LEX_SC
        if ( n_<=1 )  return false;  // just one RGS
#endif

        ulong j = tr_;
        if ( a_[j] > 1 )   // can decrement track
        {
            a_[j] -= 1;
            return true;
        }

        const ulong aj = a_[j];  // zero or one

        a_[j] = 0;
        --j;

        if ( a_[j] == a_[j-1] + i_ )  // move track to the left
        {
            --tr_;
            return true;
        }

        if ( j==0 )  // current or next is last
        {
            if ( aj == 0 )  return false;
            return true;
        }

        a_[j] += 1;  // increment left digit
        tr_ = n_ - 1;  // move to right end
        a_[tr_] = a_[tr_-1] + i_;  // set to max value
        return true;
    }

    const ulong *data()  const  { return a_; }

    const char* bit_string()
    {
        const ulong k = i_ + 1;
        for (ulong j=0; j<k*n_; ++j)  str_[j] = '.';
        for (ulong j=0; j<n_; ++j)  str_[j*k - a_[j]] = '1';
        return str_;
    }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }

    bool OK()  const
    { return is_dyck_rgs( data(), n_, i_ ); }
};
// -------------------------

#endif  // !defined HAVE_DYCK_RGS_SUBSET_LEX_H__
