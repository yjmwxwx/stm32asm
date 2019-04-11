// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/setpart-rgs-gray.h"

#include "sort/minmaxmed23.h"  // max2()

#include "fxtio.h"
#include "fxttypes.h"


void
setpart_rgs_gray::print()  const
{
//    const char sep[]=", ";
    const char sep[]=" ";
    ulong n = n_;

    cout << "s[ ";
    for (ulong j=0; j<n; ++j)  cout << s_[j] << sep;
    cout << "]";

    cout << "    m[ ";
    for (ulong j=1; j<=n; ++j)  cout << m_[j] << sep;
    cout << "]";

    cout << "    d[ ";
    for (ulong j=0; j<n; ++j)  cout << (d_[j]==1UL ? '+' : '-') << sep;
    cout << "]";
}
// -------------------------

