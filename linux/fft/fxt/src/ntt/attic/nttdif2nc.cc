
#include "fxttypes.h"
#include "ntt/ntt.h"
#include "perm/revbinpermute.h"


void
ntt_dif2_noncyclic(mod *f, ulong ldn, int is)
//
// radix-2 decimation in frequency NTT
// for noncyclic Z/mZ
// where the element of order 2 isn't ==-1
//
{
    const ulong n = (1UL<<ldn);

    mod dw = mod::root2pow( is>0?ldn:-ldn );
    mod x2 = mod::root2pow( is>0?1:-1 );  // root of order 2
//    if ( is<0 )  x2 = mod::modulus-x2;

    for (ulong ldm=ldn; ldm>0; --ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);

        mod w = (mod::one);

        for (ulong j=0; j<mh; ++j)
        {
            for (ulong r=0; r<n; r+=m)
            {
                const ulong t1 = r+j;
                const ulong t2 = t1+mh;

                mod v = f[t2];
                mod u = f[t1];

                f[t1] += v;
                f[t2] = (u+x2*v)*w;  // instead of (u-v)*w
            }

            w *= dw;
        }

        dw *= dw;
    }

    revbin_permute(f,n);
}
// -------------------------

