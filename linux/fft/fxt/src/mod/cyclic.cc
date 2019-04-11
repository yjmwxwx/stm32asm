// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "mod/factor.h"
#include "fxttypes.h"


bool
is_cyclic(const factorization &f)
// Let f be the factorization of m.
// Return whether the units modulo m, i.e. (Z/mZ)*
//  are a cyclic group.
{
    ulong e2 = f.exponent_of(2);

    if ( 1==f.nprimes() )
    {
        if ( 0==e2 )      return  true;  // p**k, p!=2
        else if ( e2<3 )  return  true;  // 2**k, k<3
        return  false;
    }

    if ( (2==f.nprimes()) && (e2==1) )  return  true;  // 2 * p**k, p!=2

    return  false;
}
// -------------------------
