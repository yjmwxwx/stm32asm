#if !defined  HAVE_FHT_DEFAULT_H__
#define       HAVE_FHT_DEFAULT_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.



//: Default FHT implementations:

//#include "fht/fht.h"
#include "fht/fhtloc2.h"

#include "fxttypes.h"  // ulong
#include "complextype.h"  // type Complex

inline void fht(double *f, ulong ldn)
{ fht_loc(f, ldn); }

inline void fht(Complex *f, ulong ldn)
{ fht_loc(f, ldn); }

inline void fht0(double *f, ulong ldn)
{ fht0_loc(f, ldn); }

inline void fht0(Complex *f, ulong ldn)
{ fht0_loc(f, ldn); }


#endif  // !defined HAVE_FHT_DEFAULT_H__
