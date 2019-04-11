#if !defined  HAVE_CATALAN_RGS_GSLEX_H__
#define       HAVE_CATALAN_RGS_GSLEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-catalan-rgs.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


// Cf. comb/catalan-subset-lex.h for Catalan RGS in subset-lex order.


class catalan_rgs_gslex
// Catalan restricted growth strings (RGS):
// strings a[0,1,...,n-1] where a[0]=0 and a[k] <= a[k-1] + 1.
// Ordering similar to gslex (and subset-lex) order.
// Loopless algorithm.
{
public:
    ulong *a_;  // digits of the RGS: a_[k] <= a[k-1] + 1
    ulong tr_;  // current track
    ulong n_;   // number of digits (paren pairs)
    char *str_;  // paren string

private:  // have pointer data
    catalan_rgs_gslex(const catalan_rgs_gslex&);  // forbidden
    catalan_rgs_gslex & operator = (const catalan_rgs_gslex&);  // forbidden

public:
    explicit catalan_rgs_gslex(ulong n)
    {
        n_ = n;

        a_ = new ulong[n_+ 1 + (n_==0)];  // incl. sentinel
//        a_[0] = +1;  // sentinel !=0  to catch scan to the left
//        ++a_;  // nota bene
        if ( n_==0 )  a_[0] = 0;

        str_ = new char[2*n_+1];
        str_[2*n_] = 0;
        first();
    }

    ~catalan_rgs_gslex()
    {
//        --a_;
        delete [] a_;
        delete [] str_;
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        tr_ = n_ - 1;
        // make things work for n <= 1:
        if ( n_ <= 1 )  tr_ = 0;
        else            a_[tr_] = 1;
    }

    bool next()
    // Loopless algorithm
    {
        ulong j = tr_;
        if ( j==0 )  return false;  // current is last

        const ulong aj = a_[j];
        if ( aj <= a_[j-1] )   // easy case 1: can increment
        {
            a_[j] = aj + 1;
            ++j;
            if ( j < n_ )
            {
                tr_ = n_ - 1;
                a_[tr_] = 1;
            }
            return true;
        }

        if ( aj != 1 )  // easy case 2: can detach
        {
            a_[j] = 0;
            tr_ = j - 1;
            return true;
        }

        // we have a[j]==1 and a[j-1]==0
        a_[j] = 0;
        if ( tr_ == 1 )  // created all-zero RGS (last)
        {
            tr_=0;
            return true;
        }
        // move the 1 to the left:
        a_[j-1] = 1;
        // put 1 at rightmost position:
        j = n_ - 1;
        a_[j] = 1;
        tr_ = j;
        return true;
    }


    const ulong *data()  const  { return a_; }


    // cf. paren-string-to-rgs.cc
    const char* paren_string()
    {
        for (ulong k=0; k<2*n_; ++k)  str_[k] = ')';
        for (ulong k=0, j=0;  k<n_;  ++k, j+=2)  str_[ j-a_[k] ] = '(';
        return str_;
    }

    const char* bit_string()
    {
        for (ulong k=0; k<2*n_; ++k)  str_[k] = '.';
        for (ulong k=0, j=0;  k<n_;  ++k, j+=2)  str_[ j-a_[k] ] = '1';
        return str_;
    }


    bool OK()  const
    { return is_catalan_rgs(data(), n_); }
};
// -------------------------

#endif  // !defined HAVE_CATALAN_RGS_GSLEX_H__
