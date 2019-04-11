#if !defined  HAVE_IS_MOTZKIN_STEP_RGS_H__
#define       HAVE_IS_MOTZKIN_STEP_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "comb/is-catalan-step-rgs.h"

inline bool is_motzkin_step_rgs(const ulong *rgs, ulong n)
// Return whether rgs[] is a valid Motzkin (step-)RGS,
// i.e., a Catalan (step-)RGS with no increments by 1.
{
    if ( n==0 )  return true;  // nothing to check

    if ( ! is_catalan_step_rgs(rgs, n) )   return false;

    for (ulong j=1; j<n; ++j)  // no steps of size 1
        if ( rgs[j] - rgs[j-1] == 1 )  return false;

    return true;
}
// -------------------------



#endif  // !defined HAVE_IS_MOTZKIN_STEP_RGS_H__
