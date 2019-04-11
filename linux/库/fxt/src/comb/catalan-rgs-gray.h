#if !defined  HAVE_CATALAN_RGS_GRAY_H__
#define       HAVE_CATALAN_RGS_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-catalan-rgs.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


class catalan_rgs_gray
// Catalan restricted growth strings (RGS):
// strings a[0,1,...,n-1] where a[0]=0 and a[k] <= a[k-1] + 1.
// Gray code for parenthesis strings (but not for the RGS).
{
public:
    ulong *a_;  // digits of the RGS: a_[k] <= a[k-1] + 1
    ulong n_;   // Number of digits (paren pairs)
    ulong *d_;  // direction
    char *str_;  // paren string

private:  // have pointer data
    catalan_rgs_gray(const catalan_rgs_gray&);  // forbidden
    catalan_rgs_gray & operator = (const catalan_rgs_gray&);  // forbidden

public:
    explicit catalan_rgs_gray(ulong n)
    {
        n_ = (n > 0 ? n : 1);  // shall work for n==0
        a_ = new ulong[n_];
        d_ = new ulong[n_];
        str_ = new char[2*n_+1];
        str_[2*n_] = 0;
        first();
    }

    ~catalan_rgs_gray()
    {
        delete [] a_;
        delete [] d_;
        delete [] str_;
    }

    void first(bool dr0=true)
    {
        if ( dr0 )
        {
            for (ulong k=0; k<n_; ++k)  a_[k] = 0;
            for (ulong k=0; k<n_; ++k)  d_[k] = +1;
        }
        else
        {
            for (ulong k=0; k<n_; ++k)  a_[k] = k;
            for (ulong k=0; k<n_; ++k)  d_[k] = -1UL;
        }
    }

    ulong next()
    // Return position of leftmost change, zero with last.
    {
        ulong j = n_ - 1;
        ulong ij;
        while ( j != 0 )
        {
            ij = a_[j] + d_[j];
            if ( ij <= a_[j-1] + 1 )  break;
            d_[j] = -d_[j];
            --j;
        }

        if ( j==0 )  return 0;  // current is last

        a_[j] = ij;
        ulong i = j;
        while ( ++i < n_ )  a_[i] = (d_[i] == 1 ? 0 : a_[i-1] + 1);
        return j;
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


#endif  // !defined HAVE_CATALAN_RGS_GRAY_H__
