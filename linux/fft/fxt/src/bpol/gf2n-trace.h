#if !defined  HAVE_GF2N_TRACE_H__
#define       HAVE_GF2N_TRACE_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/parity.h"


inline ulong gf2n_fast_trace(ulong a, ulong tv)
// Fast computation of the trace of a,
//  using the pre-calculated table tv from gf2n_trace_vector()
{
    return  parity( a & tv );  // scalar product over GF(2)
}
// -------------------------


// bpol/gf2n-trace.cc:
ulong gf2n_trace(ulong a, ulong c, ulong h);
ulong gf2n_trace_vector(ulong g, ulong c, ulong h);
ulong gf2n_trace_vector_x(ulong c, ulong n);
ulong gf2n_half_trace(ulong a, ulong c, ulong h);


#endif  // !defined HAVE_GF2N_TRACE_H__
