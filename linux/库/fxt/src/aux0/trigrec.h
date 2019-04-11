#if !defined  HAVE_TRIGREC_H__
#define       HAVE_TRIGREC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/sincos.h"
#include "fxttypes.h"
#include <cmath>  // sinl()

template <typename Type>
class trigrec
// Type either double or long double.
{
    Type al, be;
public:
    explicit trigrec(Type step)
    {
        al = sinl(0.5*step);
        al *= (2.0*al);
        be = sinl(step);
    }

    ~trigrec()  {;}

    void next(Type &s, Type &c)
    {
        Type t = c;
        c -= (al*t+be*s);
        s -= (al*s-be*t);
    }
};
// -------------------------


#endif  // !defined HAVE_TRIGREC_H__
