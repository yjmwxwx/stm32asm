#if !defined  HAVE_CHEBYSHEV_H__
#define       HAVE_CHEBYSHEV_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "mod/mtypes.h"

// mod/chebyshev1.cc:
void chebyT(umod_t n, umod_t x, umod_t &t1, umod_t &t0, umod_t m);
umod_t chebyT(umod_t n, umod_t x, umod_t m);
void chebyT2(umod_t n, umod_t &t1, umod_t &t0, umod_t m);
umod_t chebyT2(umod_t n, umod_t m);

// mod/chebyshev2.cc:
void chebyU(umod_t n, umod_t x, umod_t &t1, umod_t &t0, umod_t m);
umod_t chebyU(umod_t n, umod_t x, umod_t m);
void chebyU2(umod_t n, umod_t &u1, umod_t &u0, umod_t m);
umod_t chebyU2(umod_t n, umod_t m);


#endif  // !defined HAVE_CHEBYSHEV_H__
