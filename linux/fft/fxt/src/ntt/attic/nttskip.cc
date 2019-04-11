
#include "fxttypes.h"
#include "ntt.h"
#include "bit2pow.h" // ld()

#define MOD_FFT(f, n, is)   ntt_dit4(f, ld(n), is)
#define MOD_FFT0(f, n, is)  ntt_dit4(f, ld(n), is)

void
skip_ntt(mod *f, ulong n, ulong d, mod *w, int is)
//
// compute ntt of the n elements
// [0], [d], [2d], [3d], ..., [(n-1)*d]
//
{
    ulong k, j;

    for (k=0, j=0;  k<n*d;  k+=d, j++)  // fill workspace
    {
        w[j] = f[k];
    }

    MOD_FFT(w, n, is);             // do MOD_FFT

    for (k=0, j=0;  k<n*d;  k+=d, j++)  // write back
    {
        f[k] = w[j];
    }
}
// -------------------------


void
skip_ntt0(mod *f, ulong n, ulong d, mod *w, int is)
//
// compute ntt of the n elements
// [0], [d], [2d], [3d], ..., [(n-1)*d]
//
{
    ulong k, j;

    for (k=0, j=0;  k<(n*d)/2;  k+=d, j++)  // fill workspace
    {
        w[j] = f[k];
    }

    for ( ; k<n*d; j++)  // fill in zeros
    {
        w[j] = mod::zero;
    }


    MOD_FFT0(w, n, is);             // do MOD_FFT


    for (k=0, j=0;  k<n*d;  k+=d, j++)  // write back
    {
        f[k] = w[j];
    }
}
// -------------------------
