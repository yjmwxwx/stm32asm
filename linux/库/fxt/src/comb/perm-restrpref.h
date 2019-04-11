#if !defined  HAVE_PERM_RESTRPREF_H__
#define       HAVE_PERM_RESTRPREF_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


class perm_restrpref
// Generate all permutations with restricted prefixes,
// in lexicographic order.
// Algorithm as given by Knuth's "Algorithm X",
//  section 7.2.1.2, p.334 in vol.4A1 of TAOCP.
{
protected:
    ulong n;   // number of elements to permute
    ulong *a;  // current permutation of {1, ..., n}, one-based array!
    ulong *l;  // auxiliary table: links
    ulong *u;  // auxiliary table: undo operations
    bool (*cond)(const ulong*, ulong);  // condition function
    void (*visit)(const ulong*, ulong, ulong);  // visit function

private:  // have pointer data
    perm_restrpref(const perm_restrpref&);  // forbidden
    perm_restrpref & operator = (const perm_restrpref&);  // forbidden

public:
    explicit perm_restrpref(ulong nn,
                            bool (*cnd)(const ulong *a, ulong k),
                            void (*vst)(const ulong *a, ulong n, ulong ct))
    {
        n = (nn > 0 ? nn : 1);
        cond = cnd;
        visit = vst;
        a = new ulong[n+1];
        l = new ulong[n+1];
        u = new ulong[n+1];
    }

    ~perm_restrpref()
    {
        delete [] a;
        delete [] l;
        delete [] u;
    }

    ulong all()
    // Generate (and visit) all valid (according to cond()) permutations.
    // Return number of valid permutations.
    {
        // X1: Initialize
        for (ulong i=0; i<n; i++)  l[i] = i+1;
        l[n] = 0;
        ulong k = 1;
        ulong ct = 0;

    X2:  // X2: Enter level k
        ulong p = 0;
        ulong q = l[0];

    X3:  // X3: test (a[1], ..., a[k])
        a[k] = q;
        if ( ! cond(a, k) )  goto X5;  // inline to optimize
        if ( k==n )
        {
            ++ct;
            visit(a, n, ct);  // inline to optimize
            goto X6;
        }

        // X4: Increase k:
        u[k] = p;
        l[p] = l[q];
        ++k;
        goto X2;

    X5:  // X5: Increase a[k]
        p = q;
        q = l[p];
        if ( q!=0 )  goto X3;

    X6:  // X6: Decrease k
        --k;
        if ( 0==k )  return ct;
        p = u[k];
        q = a[k];
        l[p] = q;
        goto X5;
    }
};
// -------------------------


#endif  // !defined HAVE_PERM_RESTRPREF_H__
