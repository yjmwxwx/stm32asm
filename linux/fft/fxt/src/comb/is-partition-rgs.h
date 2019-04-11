#if !defined HAVE_IS_PARTITION_RGS_H__
#define      HAVE_IS_PARTITION_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
//#include "jjassert.h"


template <typename Type>
inline bool is_partition_rgs(const Type *f, ulong n, bool dq=true)
// Return whether sequence is rgs for partition.
// dq determines whether the RGS is for a partition as descending list.
{
    if ( n == 0 )  return true;
    if ( f[0] != 0 )  return false;

    ulong ct1 = (dq ? n+1 : 0);  // count of last element
    ulong ct0 = 0;  // count of current element
    ulong v = 0;  // value of current element
    for (ulong j=0; j<n; ++j)
    {
        if ( f[j]==v )
        {
            ++ct0;
        }
        else
        {
            ++v; // == f[j];
            ulong fj = f[j];
            if ( fj != v )  return false;

            bool q = ( dq ? ct1 < ct0 : ct1 > ct0);
//            jjassert_not( q );
            if ( q )  return false;
            ct1 = ct0;
            ct0 = 0;
        }
    }

    bool q = ( dq ? ct1 < ct0 : ct1 > ct0);
//    jjassert_not( q );
    if ( q )  return false;

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_PARTITION_RGS_H__
