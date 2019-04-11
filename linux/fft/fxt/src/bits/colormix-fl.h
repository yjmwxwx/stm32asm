#if !defined HAVE_COLORMIX_FL_H__
#define      HAVE_COLORMIX_FL_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/colormix.h"

//<<
// Various operations on 32-bit integers where 3 color channels
// of 8 bit are expected to be in the least significant 24 bits.
// The order (e.g. 0x00RRGGBB vs. 0x00BBGGRR) does not matter.
// This file contains the scaling operations with floating point
// numbers.  Note that the conversion float<-->int is expensive.
//>>

static inline uint fl_color01(uint c, double v)
//  0.0   ...  +1.0
//   0          c2
{
    return  color01(c, (ulong)( v * 65536.0 ));
}
// -------------------------

static inline uint fl_ccolor11(uint c, double v)
//      -1.0       ... 0.0 ... +1.0
//  complement(c)       0        c
{
    if ( v<=0.0 )
    {
        c = 0xffffff ^ c;
        v = -v;
    }

    if ( v<1.0 ) c = color01( c, (ulong)(65535*v+0.5) );

    return  c;
}
// -------------------------


static inline uint fl_color_mix_11(uint c1, uint c2, double v)
// -1.0  ...   0.0      ... +1.0
//   c1     (c1+c2)/2        c2
{
    return  color_mix(c1, c2, (ulong)((v+1.0) * 0.5 * 65536.0 ));
}
// -------------------------


static inline uint fl_color_mix_1b1(uint c1, uint c2, double v)
// -1.0  ...   0.0   ...  +1.0
//   c1         0          c2
{
    uint c;
    if ( v<0.0 )  c = color01(c1, (ulong)( v * -65536.0 ));
    else          c = color01(c2, (ulong)( v *  65536.0 ));
    return  c;
}
// -------------------------



#endif  // !defined HAVE_COLORMIX_FL_H__
