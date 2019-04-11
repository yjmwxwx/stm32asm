// This file is part of the FXT library.
// Copyright (C) 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/ordered-tree-branching-seq.h"

#include "fxtio.h"
#include "fxtalloca.h"
#include "fxttypes.h"


#include "jjassert.h"


void
ordered_tree_branching_seq::print_level_seq(const char *bla, bool dfz)  const
{
    const ulong *B = data();
    const ulong n = size();
    cout << bla;
    cout << "[ ";
    if ( n != 0 )
    {
        // stack S[] (containing heights) for unprocessed branches:
        ALLOCA(ulong, S, n);
        S[0] = 0;  // will be read at end
        ulong t = 1;  // stack end

        ulong h = 0;  // current height
        for (ulong j=0; j<n; ++j)
        {
            if ( h==0 )  cout << ( dfz ? '.' : '0' ) << " ";
            else         cout << h << " ";

            ulong b = B[j];
            if ( b == 0 )  // leaf
            {
                jjassert( t!=0 );
                h = S[--t];  // new height from last branch
            }
            else  // stalk or branch
            {
                h += 1;  // move up
                // put b-1 times height h on stack:
                while ( --b )  { S[t++] = h; }
            }
        }
        jjassert( t==0 );
        jjassert( S[t]==0 );
        jjassert( h==0 );
    }
    cout << "]";
}
// -------------------------
