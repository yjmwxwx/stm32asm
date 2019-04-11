#if !defined  HAVE_HAARI2I_H__
#define       HAVE_HAARI2I_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong

// haar/haari2i.cc:
void haar_i2i(double *f, ulong ldn, double *ws=0);
void inverse_haar_i2i(double *f, ulong ldn, double *ws=0);


#endif  // !defined HAVE_HAARI2I_H__
