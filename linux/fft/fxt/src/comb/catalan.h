#if !defined  HAVE_CATALAN_H__
#define       HAVE_CATALAN_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "comb/is-catalan-rgs.h"

#include "fxttypes.h"

// Cf. comb/catalan-reg-lex.h for fast iterative generation of lex order.
// Cf. comb/catalan-gray.h for fast iterative generation of the Gray code.

class catalan
// Catalan restricted growth strings (RGS)
// By default in a minimal-change order, i.e.
//  exactly two symbols in paren string change with each step.
// Most changes are adjacent or skip-2
// Non adjacent changes move a bit over ones.
{
public:
    int *as_;   // digits of the RGS: as_[k] <= as[k-1] + 1
    int *d_;    // direction with recursion (+1 or -1)
    ulong n_;   // Number of digits (paren pairs)
    char *str_;  // paren string
    bool xdr_;  // whether to change direction in recursion (==> minimal-change order)
    int dr0_;   // dr0: starting direction in each recursive step:
    //   dr0=+1  ==> start with as[]=[0,0,0,...,0]   == "()()()...()"
    //   dr0=-1  ==> start with as[]=[0,1,2,...,n-1] == "((( ... )))"

private:  // have pointer data
    catalan(const catalan&);  // forbidden
    catalan & operator = (const catalan&);  // forbidden

public:
    explicit catalan(ulong n, bool xdr=true, int dr0=+1)
    {
        n_ = n;
        as_ = new int[n_];
        d_ = new int[n_];
        str_ = new char[2*n_+1];  str_[2*n_] = 0;
        first(xdr, dr0);
    }

    ~catalan()
    {
        delete [] as_;
        delete [] d_;
        delete [] str_;
    }

    void first(bool xdr, int dr0)
    {
        dr0_ = ( (dr0>=0) ? +1 : -1 );
        xdr_ = xdr;

        ulong n = n_;
        if ( dr0_>0 )  for (ulong k=0; k<n; ++k)  as_[k] = 0;
        else           for (ulong k=0; k<n; ++k)  as_[k] = (int)k;

        for (ulong k=0; k<n; ++k)  d_[k] = dr0_;
    }

    bool next()  { return next_rec(n_-1); }

    const int *get()  const  { return as_; }
//    const int *data()  const  { return as_; }  // type here is int*

    const char* paren_string()
    {
        for (ulong k=0; k<2*n_; ++k)  str_[k] = ')';
        for (ulong k=0, j=0;  k<n_;  ++k, j+=2)  str_[ j-(ulong)as_[k] ] = '(';  // jjcast
        return str_;
    }

    void print_internal()  const;

//    bool OK()  const
//    { return is_catalan_rgs(data(), n_); }

protected:
    bool next_rec(ulong k);
};
// -------------------------


#endif  // !defined HAVE_CATALAN_H__
