#if !defined HAVE_PRINT_BIN_H__
#define      HAVE_PRINT_BIN_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// bits/print-bin.cc:
void print_bin(const char *bla, unsigned long long x, ulong pd=0, const char *c01=0);
void print_bin_vec(const char *bla, unsigned long long x, ulong pd=0, const char *c01=0);
void print_idx_seq(const char *bla, unsigned long long x, ulong off=0);


// bits/print-bindiff.cc:
void print_bin_diff(const char*bla,
                    unsigned long long x1,
                    unsigned long long x2,
                    ulong pd=0,
                    const char *c01pm=".1+-");


void print_bin_vec_diff(const char*bla,
                        unsigned long long x1,
                        unsigned long long x2,
                        ulong pd/*=0*/,
                        const char *c01pm=".1+-");

// bits/print-bitset.cc:
void print_bit_set(const char *bla, ulong x, ulong rq=0);


#endif  // !defined HAVE_PRINT_BIN_H__
