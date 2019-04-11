#if !defined  HAVE_CATALAN_RGS_SUBSET_LEX_H__
#define       HAVE_CATALAN_RGS_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-catalan-rgs.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


// Cf. comb/dyck-rgs-subset-lex.h for k-ary Dyck RGS in subset-lex order.
// Cf. comb/catalan-gslex.h for gslex order.


#define CATALAN_RGS_SUBSET_LEX_SC  // whether to allow n<=1
// this happens to give a small speedup(!)

class catalan_rgs_subset_lex
// Catalan restricted growth strings (RGS):
// strings a[0,1,...,n-1] where a[0]=0 and a[k] <= a[k-1] + 1.
// Subset-lex order.
{
public:
    ulong *a_;  // digits of the RGS: a_[k] <= as[k-1] + 1
    ulong tr_;  // current track
    ulong n_;   // Number of digits (paren pairs)
    char *str_;  // paren string

private:  // have pointer data
    catalan_rgs_subset_lex(const catalan_rgs_subset_lex&);  // forbidden
    catalan_rgs_subset_lex & operator = (const catalan_rgs_subset_lex&);  // forbidden

public:
    explicit catalan_rgs_subset_lex(ulong n)
    {
        n_ = n;

        a_ = new ulong[n_+ 1 + (n_==0)];  // incl. sentinel
        a_[0] = +1;  // sentinel !=0  to catch scan to the left
        ++a_;  // nota bene
        if ( n_==0 )  a_[0] = 0;

        str_ = new char[2*n_+1];  str_[2*n_] = 0;
        first();
    }

    ~catalan_rgs_subset_lex()
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
        if ( a_[j] <= a_[j-1] )  // easy case 1: can increment track
        {
#ifdef CATALAN_RGS_SUBSET_LEX_SC
            if ( n_ <= 1 )  return false;
#endif
            ++a_[j];
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

        --a_[j];
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
        if ( n_>=2 )  a_[tr_] = 1;
    }


    bool prev()
    // Loopless algorithm.
    {
#ifdef CATALAN_RGS_SUBSET_LEX_SC
        if ( n_<=1 )  return false;
#endif

        ulong j = tr_;
        if ( a_[j] > 1 )   // easy case 1: can decrement track
        {
            --a_[j];
            return true;
        }

        const ulong aj = a_[j];  // zero or one
        a_[j] = 0;
        --j;
        if ( a_[j] == a_[j-1] + 1 )  // easy case 2: move track to the left
        {
            --tr_;
            return true;
        }

        if ( j==0 )  // current or next is last
        {
            if ( aj == 0 )  return false;
            return true;
        }

        ++a_[j];
        tr_ = n_ - 1;
        a_[tr_] = a_[tr_-1] + 1;
        return true;
    }

    const ulong *data()  const  { return a_; }

    const char* bit_string()
    {
        for (ulong k=0; k<2*n_; ++k)  str_[k] = '.';
        for (ulong k=0, j=0;  k<n_;  ++k, j+=2)  str_[ j - a_[k] ] = '1';
        return str_;
    }

    const char* paren_string()
    {
        for (ulong k=0; k<2*n_; ++k)  str_[k] = ')';
        for (ulong k=0, j=0;  k<n_;  ++k, j+=2)  str_[ j - a_[k] ] = '(';
        return str_;
    }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }

    bool OK()  const
    { return is_catalan_rgs(data(), n_); }
};
// -------------------------

#endif  // !defined HAVE_CATALAN_RGS_SUBSET_LEX_H__
