
#include "copy.h" // copy()
#include "graypermute.h"
#include "revbinpermute.h"

#include "fxt.h" // dit2_walsh_wak()


void
walsh_wak0(double *f, ulong ldn)
// transform wrt. to walsh-kronecker basis (wak-functions)
// version for zero padded data
{
    if ( ldn==0 )  return;

    ulong n = (1<<(ulong)ldn);
    dit2_walsh_wak(f,ldn-1);
    copy(f, f+n/2, n/2);
}
// ============= end ===============


void
walsh_wal0(double *f, ulong ldn)
//
// transform wrt. to walsh-kaczmarz basis (wal-functions)
// the wal functions are sequency- ordered
//
{
    const ulong n=(1<<ldn);
    walsh_wak0(f,ldn);
    revbin_permute(f,n);
    inverse_gray_permute(f,n);
}
// ================= end ==================


void
walsh_pal0(double *f, ulong ldn)
// transform wrt. to walsh-paley basis (pal-functions)
// version for zero padded data
{
    if ( ldn==0 )  return;

    ulong n = (1<<(ulong)ldn);
    walsh_wak0(f, ldn);
    revbin_permute(f, n);
}
// ============= end ===============


void
dyadic_convolution0(double *f, double *g, ulong ldn)
// dyadic linear convolution:  g[] := f[] (*dyad) g[]
// ldn := base-2 logarithm of the array length
// input data must be zero padded:
//   f[n/2] .. f[n-1] == 0 and g[n/2] .. g[n-1] == 0
// f and g must not overlap
{
#ifdef PARANOIA
    jjassert( f!=g );
#endif

    WALSH0(f,ldn);
    WALSH0(g,ldn);

    ulong n=(1<<ldn);
    for (ulong k=0; k<n; ++k)  g[k] *= f[k];

    WALSH(g,ldn);
}
// ============= end ===========


void
dyadic_auto_convolution0(double *f, ulong ldn)
// dyadic self convolution:  f[] := f[] (*dyad) f[]
// ldn := base-2 logarithm of the array length
// input data must be zero padded:
//   f[n/2] .. f[n-1] == 0
{
    WALSH0(f,ldn);

    ulong n=(1<<ldn);
    for (ulong k=0; k<n; ++k)  f[k] *= f[k];

    WALSH(f,ldn);
}
// ============= end ===========
