#if !defined  HAVE_NUM_NECKLACES_H__
#define       HAVE_NUM_NECKLACES_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"

// comb/num-necklaces.cc:

//: num_necklaces_tab[n] == number of binary n-bit necklaces
extern const ulong num_necklaces_tab[BITS_PER_LONG+1];

//: num_lyndon_tab[n] == number of binary n-bit Lyndon words
extern const ulong num_lyndon_tab[BITS_PER_LONG+1];


#endif  // !defined HAVE_NUM_NECKLACES_H__
