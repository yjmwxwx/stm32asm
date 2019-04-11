// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mset-perm-lex-rec.h"

#include "fxttypes.h"
//#include "jjassert.h"


void
mset_perm_lex_rec::mset_perm_rec(ulong d)
{
    if ( d>=n_ )
    {
        ++ct_;
        visit_( *this );
    }
    else
    {
        for (ulong jf=k_, j=nn_[jf];  j<k_;  jf=j, j=nn_[j])  // for all nonempty buckets
        {
            ++rct_;  // work == number of recursions
//            jjassert( r_[j] );

            --r_[j];     // take element from bucket
            ms_[d] = j;  // put element in place

            if ( r_[j]==0 )  // bucket now empty?
            {
                ulong f = nn_[jf];  // where we come from
                nn_[jf] = nn_[j];  // let recursions skip over j
                mset_perm_rec(d+1);     // recursion
                nn_[jf] = f;       // remove skip
            }
            else  mset_perm_rec(d+1);   // recursion

            ++r_[j];      // put element back
        }
    }
}
// -------------------------
