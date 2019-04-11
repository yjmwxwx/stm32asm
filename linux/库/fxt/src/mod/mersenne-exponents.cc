// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014, 2015, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "array-len.h"


extern const ulong mersenne_exp_tab[] =
// Known exponents of Mersenne primes.
// See http://www.mersenne.org/
// See also http://oeis.org/A000043
// and http://www.mersenne.org/report_milestones/
{
    2, 3, 5, 7, 13,
    17, 19, 31, 61, 89,
    107, 127, 521, 607, 1279,
    2203, 2281, 3217, 4253, 4423,
    9689, 9941, 11213, 19937, 21701,
    23209, 44497, 86243, 110503, 132049,
    216091, 756839, 859433,
    1257787,
    1398269,  // November 1996
    2976221,  // August 1997
    3021377,  // January 1998
    6972593,  // June 1999
    // (Jan-2005) no undiscovered Mersenne exponents < 10,000,000
    13466917,  // November 2001
    // (2008) no undiscovered exponents < 13466917
    20996011,  // November 2003
    // (2010) no undiscovered exponents < 20996011
    24036583,  // May 2004
    25964951,  // February 2005
    30402457,  // December 2005
    // (2014) no undiscovered exponents < 30402457
    32582657,  // September 2006
    // (2014) no undiscovered exponents < 32582657
    37156667,  // September 2008
    42643801,  // April 2009
    43112609,  // September 2008
    57885161,  // January 2013
    74207281   // January 2016
};
// -------------------------


extern const ulong mersenne_exp_tab_len = ARRAY_LEN(mersenne_exp_tab);

