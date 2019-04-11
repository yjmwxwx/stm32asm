#if !defined  HAVE_PAREN_GRAY_H__
#define       HAVE_PAREN_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "aux0/swap.h"

class paren_gray
// Parentheses strings in a homogeneous minimal-change order.
{
private:
    ulong n, j;
    char *par;  // parenthesis string in p[1,...,2*n]
    ulong *l, *d, *e;
    bool jj;  // whether current string is the last

private:  // have pointer data
    paren_gray(const paren_gray&);  // forbidden
    paren_gray & operator = (const paren_gray&);  // forbidden

public:
    explicit paren_gray(ulong nn)
    {
        n = nn;
        par = new char[2*n+2];
        par[2*n+1] = 0;
        l = new ulong[n+1];
        d = new ulong[n+1];
        e = new ulong[n+1];
        first();
    }

    ~paren_gray()
    {
        delete [] par;
        delete [] l;
        delete [] d;
        delete [] e;
    }

    void first()
    {
        for (ulong i=1; i<=2*n; i+=2)  { par[i] = '(';  par[i+1] = ')'; }
        for (ulong i=1; i<=n; ++i)  l[i] = 2*i-1;
        for (ulong i=1; i<=n; ++i)  d[i] = 1;
        for (ulong i=0; i<=n; ++i)  e[i] = i;
        j = n;
        jj = true;
    }

    bool next()
    // Code as in:
    //  Tadao Takaoka, Stephen Violich:
    //  "Combinatorial Generation by Fusing Loopless Algorithms"
    {
        if ( !jj ) { first();  return false; }

        e[n] = n;
        ulong i = l[j];
        if ( d[j]==1 )
        {
            if ( l[j]==2*j-1 )  l[j] = l[j-1] + 1;
            else                ++l[j];
        }
        else
        {
            if ( l[j]==l[j-1]+1 )  l[j] = 2*j - 1;
            else                   --l[j];
        }

        swap2( par[i], par[l[j]] );
        if ( l[j] >= 2*j-2 )
        {
            d[j] = -d[j];
            e[j] = e[j-1];
            e[j-1] = j-1;
        }
        j = e[n];
        jj = ( j!=1 );

        return true;
    }

    const char * paren_string() const  { return par+1; }
};
// -------------------------


#endif  // !defined HAVE_PAREN_GRAY_H__
