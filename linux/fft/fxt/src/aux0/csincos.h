#if !defined  HAVE_CSINCOS_H__
#define       HAVE_CSINCOS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/sincos.h"
#include "complextype.h"

static inline Complex SinCos(double phi)
{
    double c, s;
    SinCos(phi, &s, &c);
    return  Complex(c, s);
}
// -------------------------

//static inline void SinCos(double phi, Complex *z)
//{
//    double *c = (double *)z;  // jjcast
//    double *s = c + 1;
//    SinCos(phi, s, c);
//}
//// -------------------------


#endif  //  !defined  HAVE_CSINCOS_H__
