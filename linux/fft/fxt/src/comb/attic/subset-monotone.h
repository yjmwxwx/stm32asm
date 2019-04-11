#if !defined HAVE_SUBSET_MONOTONE_H__
#define      HAVE_SUBSET_MONOTONE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/bitcombcolex.h"
#include "fxttypes.h"

class subset_monotone
// Subsets of the set {0,1,2,...,n-1} ordered by cardinality
{
protected:
    ulong *x;
    ulong n;
    ulong num;
    ulong s;
    ulong mask;

private:  // have pointer data
    subset_monotone(const subset_monotone&);  // forbidden
    subset_monotone & operator = (const subset_monotone&);  // forbidden

public:
    explicit subset_monotone(ulong nn)
    {
        n = (nn ? nn : 1);  // not zero
        x = new ulong[n];
        mask = (1UL<<n) - 1;
        first();
    }

    virtual ~subset_monotone()  { delete [] x; }


    ulong first()
    {
        num = 0;
        s = 0;
        for (ulong k=0; k<n; ++k)  x[k] = 0;
        return  num;
    }

    ulong next()  // return number of elements in subset
    {
        make_next();
        return  num;
    }

    const ulong * data()  const { return x; }


protected:
    void make_next()
    {
        s = next_colex_comb(s);
        if ( (s==0) || s != (s & mask) )
        {
            ++num;
            if ( num <= n )  s = first_comb( num );
            else  { first(); return; }
        }

        for (ulong k=0, m=1;  k<n;  ++k, m<<=1)  { x[k] = (s & m ? 1 : 0); }
    }
};
// -------------------------



#endif  // !defined HAVE_SUBSET_MONOTONE_H__
