#if !defined  HAVE_CATALAN_RGS_H__
#define       HAVE_CATALAN_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-catalan-rgs.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


// whether to use arrays instead of pointers:
//#define CATALAN_RGS_FIXARRAYS  // default is off
// slight speedup with GCC 4.9.1


class catalan_rgs
// Catalan restricted growth strings (RGS):
// strings a[0,1,...,n-1] where a[0]=0 and a[k] <= a[k-1] + 1.
// Lexicographic order.
// The number of length-n RGS is (OEIS sequence A000108)
//  1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, ...
// Sequence A239903 gives the RGS.
{
public:
#ifndef CATALAN_RGS_FIXARRAYS
    ulong *a_;  // digits of the RGS: a_[k] <= a[k-1] + 1
#else
    ulong a_[64];
#endif
    ulong n_;   // Number of digits (paren pairs)

    char *str_;  // paren string

private:  // have pointer data
    catalan_rgs(const catalan_rgs&);  // forbidden
    catalan_rgs & operator = (const catalan_rgs&);  // forbidden

public:
    explicit catalan_rgs(ulong n)
    {
        n_ = n;
#ifndef CATALAN_RGS_FIXARRAYS
        a_ = new ulong[n_ + 1];
#endif
        str_ = new char[2*n_+1];
        str_[2*n_] = 0;

        first();
    }

    ~catalan_rgs()
    {
#ifndef CATALAN_RGS_FIXARRAYS
        delete [] a_;
#endif
        delete [] str_;
    }

    const ulong *data()  const  { return a_ + 1; }
    ulong size()  const  { return n_ + 1; }

    void first()
    { for (ulong k=0; k<size(); ++k)  a_[k] = 0; }


    ulong next()
    // Return position of leftmost change, zero with last.
    {
        ulong j = n_;
        while ( j > 1 )
        {
            if ( a_[j] <= a_[j-1] )
            {
                ++a_[j];
                return j - 1;
            }
            a_[j] = 0;
            --j;
        }

        return 0;  // current is last
    }


    const char* bit_string()
    {
        for (ulong k=0; k<2*n_; ++k)  str_[k] = '.';
        const ulong *a = data();
        for (ulong k=0, j=0;  k<n_;  ++k, j+=2)  str_[ j - a[k] ] = '1';
        return str_;
    }

    const char* paren_string()
    {
        for (ulong k=0; k<2*n_; ++k)  str_[k] = ')';
        const ulong *a = data();
        for (ulong k=0, j=0;  k<n_;  ++k, j+=2)  str_[ j - a[k] ] = '(';
        return str_;
    }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }

    bool OK()  const
    { return is_catalan_rgs(data(), n_); }
};
// -------------------------


#endif  // !defined HAVE_CATALAN_RGS_H__
