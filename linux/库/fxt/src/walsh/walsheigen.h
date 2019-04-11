#if !defined  HAVE_WALSHEIGEN_H__
#define       HAVE_WALSHEIGEN_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "walsh/walsh-basis.h"
#include "fxttypes.h"

//: eigenvectors for certain Walsh transforms

// walsh/walsheigen.cc:
void walsh_wak_eigen(double *v, ulong ldn, ulong k);
void walsh_wal_eigen(double *v, ulong ldn, ulong k);
void walsh_pal_eigen(double *v, ulong ldn, ulong k);


#endif  // !defined HAVE_WALSHEIGEN_H__
