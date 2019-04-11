
#include "fxttypes.h"
#include "ntt.h"
#include "bit2pow.h" // ld()
//#include "newop.h"

#include "jjassert.h"
// note: FIXME: yucky code, should be redone


static mod *w;  // workspace

// always call ntt_ndim(), don't call e.g. ntt_3dim() directly !

void ntt_2dim(mod *f, ulong d1, ulong d2, int is);
void ntt_3dim(mod *f, ulong d1, ulong d2, ulong d3, int is);
void ntt_4dim(mod *f, ulong d1, ulong d2, ulong d3, ulong d4, int is);
void ntt_5dim(mod *f, ulong d1, ulong d2, ulong d3, ulong d4, ulong d5, int is);


#define MOD_FFT(f,n,is)  ntt_dit4(f,ld(n),is)


void
ntt_ndim(mod *f, ulong ndim, ulong *ldn, int is)
//
// ndim must be 1,2,3,4 or 5
// ldn[] contains base 2 logarithms of dimensions
//
{
    if ( (ndim<1) || (ndim>5) )
    {
        jjassert2(0, "invalid ndim in ndim_ntt");
    }

    if (ndim==1)  // 1-dim ntt
    {
        MOD_FFT(f, 1UL<<ldn[0], is);
        return;
    }

    // find max(d1,d2,...,dn):
    ulong nw=0;
    for (ulong k=0; k<ndim; ++k)
    {
        if ( ldn[k]>nw )  nw=ldn[k];
    }
    nw = (1UL<<nw);

    w = new mod[nw];

    ulong d1=(1UL<<ldn[0]);
    ulong d2=(1UL<<ldn[1]);
    if (ndim==2)
    {
        ntt_2dim(f,d1,d2,is);
    }
    else
    {
        ulong d3=(1UL<<ldn[2]);
        if (ndim==3)
        {
            ntt_3dim(f,d1,d2,d3,is);
        }
        else
        {
            ulong d4=(1UL<<ldn[3]);
            if (ndim==4)
            {
                ntt_4dim(f,d1,d2,d3,d4,is);
            }
            else
            {
                ulong d5=(1UL<<ldn[4]);
                if (ndim==5)
                {
                    ntt_5dim(f,d1,d2,d3,d4,d5,is);
                }
            }
        }
    }

    delete [] w;
}
// -------------------------


void
ntt_2dim(mod *f, ulong d1, ulong d2, int is)
{
    ulong n=d1*d2;
    ulong k;

    // rows:
    for (k=0; k<n; k+=d1)  MOD_FFT(f+k,d1,is);

    // columns:
    for (k=0; k<d1; k++)  skip_ntt(f+k,d2,d1,w,is);
}
// -------------------------



void
ntt_3dim(mod *f, ulong d1, ulong d2, ulong d3, int is)
{
    ulong d12=d1*d2;
    ulong n=d12*d3;
    ulong k;

    for (k=0; k<n; k+=d12)  ntt_2dim(f+k,d1,d2,is);

    for (k=0; k<d12; k++)  skip_ntt(f+k,d3,d12,w,is);
}
// -------------------------



void
ntt_4dim(mod *f, ulong d1, ulong d2, ulong d3, ulong d4, int is)
{
    ulong d123=d1*d2*d3;
    ulong n=d123*d4;
    ulong k;

    for (k=0; k<n; k+=d123)  ntt_3dim(f+k,d1,d2,d3,is);

    for (k=0; k<d123; k++)  skip_ntt(f+k,d4,d123,w,is);
}
// -------------------------



void
ntt_5dim(mod *f, ulong d1, ulong d2, ulong d3, ulong d4, ulong d5, int is)
{
    ulong d1234=d1*d2*d3*d4;
    ulong n=d1234*d5;
    ulong k;

    for (k=0; k<n; k+=d1234)  ntt_4dim(f+k,d1,d2,d3,d4,is);

    for (k=0; k<d1234; k++)  skip_ntt(f+k,d5,d1234,w,is);
}
// -------------------------

