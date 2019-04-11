#if !defined  HAVE_KOLAKOSKI_SEQ_H__
#define       HAVE_KOLAKOSKI_SEQ_H__
// This file is part of the FXT library.
// Copyright (C) 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

class kolakoski_seq
// Generator for the Oldenburger-Kolakoski sequence.
// See OEIS sequence A000002.
// Cf. https://en.wikipedia.org/wiki/Kolakoski_sequence
// Algorithm by David Eppstein,
//   see http://11011110.livejournal.com/336374.html
{
private:
    ulong x, y;
public:
    kolakoski_seq()
    {
        first();
    }

    void first()
    {
        x = -1UL;
        y = -1UL;
    }

    ulong next()
    {
        const ulong r = ( x & 1UL ? 1 : 2 );
        const ulong f = y & ~(y+1);
        x ^= f;
        y = (y+1) | (f & (x>>1));
        return r;
    }
};
// -------------------------

#endif // !defined HAVE_KOLAKOSKI_SEQ_H__
