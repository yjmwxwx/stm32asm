#if !defined  HAVE_SUBSET_DELTALEX_H__
#define       HAVE_SUBSET_DELTALEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// If defined, an array is used instead of a pointer:
#define SUBSET_DELTALEX_MAX_ARRAY_LEN 64  // speedup

class subset_deltalex
// Subsets in lexicographic order for delta sets
{
public:
#ifndef SUBSET_DELTALEX_MAX_ARRAY_LEN
    ulong *d_;  // subset as delta set
#else
    ulong d_[SUBSET_DELTALEX_MAX_ARRAY_LEN];
#endif
    ulong n_;   // subsets of the  n-set {0,1,2,...,n-1}

private:  // have pointer data
    subset_deltalex(const subset_deltalex&);  // forbidden
    subset_deltalex & operator = (const subset_deltalex&);  // forbidden

public:
    explicit subset_deltalex(ulong n)
    {
        n_ = n;
#ifndef SUBSET_DELTALEX_MAX_ARRAY_LEN
        d_ = new ulong[n+1];
#endif
        d_[n] = 0;  // sentinel
        first();
    }

    ~subset_deltalex()
    {
#ifndef SUBSET_DELTALEX_MAX_ARRAY_LEN
        delete [] d_;
#endif
    }

    void first()
    { for (ulong k=0; k<n_; ++k)  d_[k] = 0; }

    bool next()
    {
        ulong k = 0;
        while ( d_[k]==1 )  { d_[k]=0;  ++k; }

        if ( k==n_ )  return false;  // current subset is last

        d_[k] = 1;
        return true;
    }

    const ulong * data()  const  { return d_; }
};
// -------------------------

//#undef SUBSET_DELTALEX_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_SUBSET_DELTALEX_H__
