#if !defined  HAVE_BITPOLMOD_SOLVEQUADRATIC_H__
#define       HAVE_BITPOLMOD_SOLVEQUADRATIC_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"  // ulong

// bpol/bitpolmod-solvequadratic.cc:
bool bitpolmod_solve_reduced_quadratic(ulong c, ulong& r, ulong m);
bool bitpolmod_solve_quadratic(ulong a, ulong b, ulong c, ulong& r0, ulong& r1, ulong m);


#endif  // !defined HAVE_BITPOLMOD_SOLVEQUADRATIC_H__
