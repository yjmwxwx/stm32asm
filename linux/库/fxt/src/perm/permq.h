#if !defined HAVE_PERMQ_H__
#define      HAVE_PERMQ_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


//#include "ds/bitarray.h"
class bitarray;
//#include "ds/left-rightarray.h"
class left_right_array;


#include "fxttypes.h"


// perm/permq.cc:
bool is_identity(const ulong *f, ulong n);
bool has_fixed_points(const ulong *f, ulong n);
ulong count_fixed_points(const ulong *f, ulong n);
ulong count_descents(const ulong *f, ulong n);
ulong count_excedances(const ulong *f, ulong n, bool eq=true);
ulong count_inversions(const ulong *f, ulong n);
ulong count_inversions(const ulong *f, ulong n, left_right_array *tLR);
bool is_derangement(const ulong *f, ulong n);
bool is_derangement(const ulong *f, const ulong *g, ulong n);
bool is_connected(const ulong *f, ulong n);
bool is_updown_permutation(const ulong *f, ulong n);
bool is_cyclic(const ulong *f, ulong n);
bool is_valid_permutation(const ulong *f, ulong n, bitarray *bp=0);
bool is_involution(const ulong *f, ulong n, bool hint=false);
bool is_inverse(const ulong *f, const ulong *g, ulong n, bool hint=false);
bool is_square(const ulong *f, const ulong *g, ulong n);
ulong get_index(const ulong *f, ulong n);
ulong count_transpositions(const ulong *f, ulong n, bitarray *bp=0);
ulong count_cycles(const ulong *f, ulong n, bitarray *bp=0);
ulong major_index(const ulong *f, ulong n);
//ulong get_periods(const ulong *f, ulong n, ulong *p, bitarray *bp=0);
bool is_simple(const ulong *f, ulong n);


//: functions for the application of permutations to data
//: are found in perm/permapply.h

//: functions for random permutations
//: are found in perm/permrand.h

#endif  // !defined HAVE_PERMQ_H__
