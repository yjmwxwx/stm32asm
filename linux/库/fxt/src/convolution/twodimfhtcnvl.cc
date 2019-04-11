// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "aux0/sumdiff.h"
#include "aux1/arith1.h"


inline void
fht_cnvl_core_core(const double *fp, const double *fm, double *gp, double *gm)
// auxiliary routine for twodim_fht_convolution_core()
{
    double s1, d1;
    sumdiff(*fp, *fm, s1, d1);
    double h2p = *gp,  h2m = *gm;
    *gp = h2p * s1 + h2m * d1;
    *gm = h2m * s1 - h2p * d1;
}
// -------------------------


void
twodim_fht_convolution_core(const double *f, double *g, ulong nr, ulong nc)
// convolution core for 2dim convolution using FHT
//
// nr := number of rows
// nc := number of columns
{
    ulong rh = nr/2;
    if ( nr&1 )  rh++;

    ulong ch = nc/2;
    if ( nc&1 )  ch++;

    ulong n = nr * nc;
    for (ulong tr=1, ctr=nc;  tr<rh;  tr++, ctr+=nc)  // ctr = nc*tr
    {
        // note: use array style code for inner loop
        const double *paf = f + ctr;
        const double *pbf = paf + nc;
        const double *pcf = f + n - ctr;
        const double *pdf = pcf + nc;

        double *pag = g + ctr;
        double *pbg = pag + nc;
        double *pcg = g + n - ctr;
        double *pdg = pcg + nc;

        for (ulong tc=1; tc<ch; tc++)
        {
            paf++;
            pbf--;
            pcf++;
            pdf--;

            pag++;
            pbg--;
            pcg++;
            pdg--;

            fht_cnvl_core_core(paf, pdf, pag, pdg);
            fht_cnvl_core_core(pbf, pcf, pbg, pcg);
        }
    }

    multiply_val(g, n, 0.5/(double)n);
}
// -------------------------
