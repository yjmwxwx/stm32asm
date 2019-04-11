#if !defined  HAVE_PAREN_STRING_TO_RGS_H__
#define       HAVE_PAREN_STRING_TO_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// comb/paren-string-to-rgs.cc:
void rgs_to_paren_string(const ulong *rgs, ulong n, char *str, bool rq=false);
bool paren_string_to_rgs(const char *str, ulong *rgs);

void rgs_to_paren_bit_string(const ulong *rgs, ulong n, char *str, bool rq=false);
bool paren_bit_string_to_rgs(const char *str, ulong *rgs);



#endif  // !defined HAVE_PAREN_STRING_TO_RGS_H__
