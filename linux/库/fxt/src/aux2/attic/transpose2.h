#if !defined  HAVE_TRANSPOSE2_H__
#define       HAVE_TRANSPOSE2_H__

#include "fxttypes.h"
#include "jjassert.h"

#include "sort/minmaxmed23.h"
#include "aux0/swap.h"


template <typename Type>
void matrix_transpose2(Type *x, ulong nr, ulong nc, Type *tmp=0)
// Transpose (nr x nc) matrix.
// Only for n*n or n*2n or 2n*n matrix !
//
// Scratchspace, if supplied, must have size max(nr,nc).
//
// Note: this routine is superceded by transpose2_ba()
{
    jjassert( (nr==nc) || (nr==2*nc) || (2*nr==nc) );

    if ( nr==nc )
    {
        for (ulong i=1; i<nr; ++i)
        {
            Type *y = x+i*nc;
            Type *z = x+i;
            for (ulong j=0; j<i; ++j)
            {
                swap2(*y, *z);
                y++;
                z += nc;
            }
        }
    }
    else  // nr!=nc
    {
        ulong i1,i2;
        ulong mrc = max2(nr, nc);
        Type *wd;
        if ( tmp )  wd = tmp;
        else        wd = new Type[mrc];

        if ( nc>nr )
        {
            ulong nch = nc/2;

            for (ulong i=0; i<nr; ++i)
            {
                i1 = i*nc;
                i2 = i1+1;
                for (ulong j=0; j<nch; j++)
                {
//                    i1 = i*nc + 2*j;
//                    i2 = i*nc + 2*j + 1;
                    wd[j] =   x[i1];
                    wd[nch+j] = x[i2];

                    i1 += 2;
                    i2 += 2;
                }

                i1 = i*nc;
                for (ulong j=0; j<nc; j++)
                {
//                    x[i*nc+j] = wd[j];
                    x[i1] = wd[j];
                    i1++;
                }
            }

            for (ulong i=0; i<nr; ++i)
            {
                i1 = i*nc;
                i2 = i;
                for (ulong j=0; j<i; ++j)
                {
//                    i1 = i*nc + j;
//                    i2 = j*nc + i;
                    swap2(x[i1], x[i2]);
                    i1++;
                    i2 += nc;
                }
            }

            for (ulong i=0; i<nr; ++i)
            {
                i1 = i*nc+nch;
                i2 = i+nch;
                for (ulong j=0; j<i; ++j)
                {
//                    i1 = i*nc + nch + j;
//                    i2 = j*nc + nch + i;
                    swap2(x[i1], x[i2]);
                    i1++;
                    i2 += nc;
                }
            }
        }
        else  // nr>nc
        {
            ulong nrh = nr/2;
            for (ulong i=0; i<nrh; ++i)
            {
                i1 = i*nrh;
                i2 = i;
                for (ulong j=0; j<i; ++j)
                {
//                    i1 = i*nrh + j;
//                    i2 = j*nrh + i;
                    swap2(x[i1], x[i2]);
                    i1++;
                    i2 += nrh;
                }
            }

            for (ulong i=0; i<nrh; ++i)
            {
                i1 = nrh*(nrh+i);
                i2 = nrh*nrh+i;
                for (ulong j=0; j<i; ++j)
                {
//                    i1 = nrh*nrh + i*nrh + j;
//                    i2 = nrh*nrh + i + j*nrh;
                    swap2(x[i1], x[i2]);
                    i1++;
                    i2 += nrh;
                }
            }

            for (ulong j=0; j<nc; ++j)
            {

                ulong i3 = 0;
                i1 = j;
                i2 = j+nrh*nrh;
                for (ulong i=0; i<nrh; ++i)
                {
//                    i1 = j + i*nc;
//                    i2 = j + nrh*nrh + i*nc;
//                    wd[2*i] =   x[i1];
//                    wd[2*i+1] = x[i2];
                    wd[i3] =   x[i1];
                    wd[++i3] = x[i2];
                    i3++;
                    i1 += nc;
                    i2 += nc;

                }

                i1 = j;
                for (ulong i=0; i<nr; ++i)
                {
//                    i1 = j + i*nc;
                    x[i1] = wd[i];
                    i1 += nc;
                }
            }
        }

        if ( !tmp )  delete [] wd;
    }
}
// -------------------------


#endif  // !defined HAVE_TRANSPOSE2_H__
