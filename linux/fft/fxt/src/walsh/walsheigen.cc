// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "walsh/walsh-basis.h"
#include "fxttypes.h"

#include <cmath>  // sqrt()

void
walsh_wak_eigen(double *v, ulong ldn, ulong k)
// Eigenvectors of the Walsh transform (walsh_wak).
// Eigenvalues are +1 if k<n/2, else -1
{
    ulong n = 1UL << ldn;
    walsh_wak_basis(v, n, k);
    double d = sqrt((double)n);  // normalization
    v[k] += (k<n/2 ? +d : -d);
}
// -------------------------

void
walsh_wal_eigen(double *v, ulong ldn, ulong k)
// Eigenvectors of the Walsh transform (walsh_wal).
// Eigenvalues are +1 if k<n/2, else -1
{
    ulong n = 1UL << ldn;
    walsh_wal_basis(v, n, k);
    double d = sqrt((double)n);  // normalization
    v[k] += (k<n/2 ? +d : -d);
}
// -------------------------


void
walsh_pal_eigen(double *v, ulong ldn, ulong k)
// Eigenvectors of the Walsh transform (walsh_pal).
// Eigenvalues are +1 if k<n/2, else -1
{
    ulong n = 1UL << ldn;
    walsh_pal_basis(v, n, k);
    double d = sqrt((double)n);  // normalization
    v[k] += (k<n/2 ? +d : -d);
}
// -------------------------


