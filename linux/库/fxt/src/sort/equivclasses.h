#if !defined  HAVE_EQUIVCLASSES_H__
#define       HAVE_EQUIVCLASSES_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
void equivalence_classes(const Type *s, ulong n, bool (*equiv_q)(Type, Type), ulong *q)
// Given an equivalence relation '==' (as function equiv_q())
//  and a set s[] with n elements,
// write to q[k] the index j of the first element s[j] such that s[k]==s[j].
// For the complexity C:  n<=C<=n*n
//  C=n*n if each element is in its own class
//  C=n   if all elements are in the same class
{
    for (ulong k=0; k<n; ++k)  q[k] = k;  // each in own class
    for (ulong k=1; k<n; ++k)
    {
#if 1
        ulong j = 0;
        while ( ! equiv_q(s[j], s[k]) )  ++j;
        q[k] = q[j];
#else
        ulong j = k;
        while ( j-- )
        {
            if ( equiv_q(s[j], s[k]) )
            {
                q[k] = q[j];
                break;
            }
        }
#endif
    }
}
// -------------------------


#endif  // !defined HAVE_EQUIVCLASSES_H__
