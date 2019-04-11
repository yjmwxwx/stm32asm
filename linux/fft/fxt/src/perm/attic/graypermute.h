#if !defined HAVE_GRAYPERMUTE_H__
#define      HAVE_GRAYPERMUTE_H__


#include "inline.h"
#include "auxbit.h"  // graycode()
#include "bits2pow.h" // ld()



//ulong gray_permute_index_cache[BITS_PER_LONG];
//ulong gray_permute_update_masks[BITS_PER_LONG];

// defined in graypermute.cc:
extern ulong gray_permute_index_cache[];
extern ulong gray_permute_update_masks[];

#define  ic  gray_permute_index_cache
#define  xm  gray_permute_update_masks

template <typename Type>
void
gray_permute_cycle(Type *f, ulong s, ulong len)
// moves one cycle of length len starting at index s
// called by gray_permute()
{
    ulong k=len-1, r=s;
    do
    {
        ic[k] = r;
        --k;
        r = graycode(r);
    }
    while ( k );
    ic[0] = r;

    Type t = f[ic[0]];
    for (ulong k=0; k<len-1; ++k)  f[ic[k]] = f[ic[k+1]];
    f[ic[len-1]] = t;
}
// =========================

template <typename Type>
void
inverse_gray_permute_cycle(Type *f, ulong s, ulong len)
// moves one cycle of length len starting at index s
// called by inverse_gray_permute()
{
    ulong k=1, r=s;
    ic[0] = r;
    do
    {
        r = graycode(r);
        ic[k] = r;
        ++k;
    }
    while ( k<len );

    Type t = f[ic[0]];
    for (ulong k=0; k<len-1; ++k)  f[ic[k]] = f[ic[k+1]];
    f[ic[len-1]] = t;
}
// =========================


template <typename Type>
void
gray_permute_ge_512(Type *f, ulong n)
// permutes the upper half for lenths >= 512
// called by gray_permute()
{
    xm[0] = 1;
    xm[1] = 3;
    xm[2] = 7;
    xm[3] = 0;

    ulong ldm=8, m=256, d=m/8;
    ulong ldc = 3, cl;  // ld(cycle len), cycle len
    for (  ;  m<n;  m*=2, d*=2, ++ldm)
    {
        ulong q = one_bit_q(ldm);
        if ( q )  ++ldc; // cycle length doubles
        cl = (1UL<<ldc);

        ulong q1 = 1 - q;
        ulong i = ldm - ldc - 1;
        xm[i] = 0;
        for (--i; i!=0; --i)  xm[i] = 2*xm[i-q1] + q1;
        xm[0] = 1 + q;

        for (ulong k=m,ldr=m;  ; ++k)
        {
            gray_permute_cycle(f, ldr, cl);
            gray_permute_cycle(f, ldr+d, cl);

            ulong i = 0;
            ulong b = 1;
            while ( b & k ) // scan for lowest unset bit
            {
                b <<= 1;
                ++i;
            }

            if ( xm[i]==0 )  break;  // next power of 2
            ldr ^= xm[i];
        }
    }
}
// =========================



template <typename Type>
void
inverse_gray_permute_ge_512(Type *f, ulong n)
// permutes the upper half for lenths >= 512
// called by inverse_gray_permute()
{
    xm[0] = 1;
    xm[1] = 3;
    xm[2] = 7;
    xm[3] = 0;

    ulong ldm=8, m=256, d=m/8;
    ulong ldc = 3, cl;  // ld(cycle len), cycle len
    for (  ;  m<n;  m*=2, d*=2, ++ldm)
    {
        ulong q = one_bit_q(ldm);
        if ( q )  ++ldc; // cycle length doubles
        cl = (1UL<<ldc);

        ulong q1 = 1 - q;
        ulong i = ldm - ldc - 1;
        xm[i] = 0;
        for (--i; i!=0; --i)  xm[i] = 2*xm[i-q1] + q1;
        xm[0] = 1 + q;

        for (ulong k=m,ldr=m;  ; ++k)
        {
            inverse_gray_permute_cycle(f, ldr, cl);
            inverse_gray_permute_cycle(f, ldr+d, cl);

            ulong i = 0;
            ulong b = 1;
            while ( b & k ) // scan for lowest unset bit
            {
                b <<= 1;
                ++i;
            }

            if ( xm[i]==0 )  break;  // next power of 2
            ldr ^= xm[i];
        }
    }
}
// =========================


template <typename Type>
void
gray_permute(Type *f, ulong n)
// heavily optimised version
{
    if ( n<4 )  return;

    // n<=4:
    { Type t=f[2]; f[2]=f[3]; f[3]=t; }
    if ( n<8 )  return;

    // n<=8:
    { Type t=f[4]; f[4]=f[7]; f[7]=f[5]; f[5]=f[6]; f[6]=t; }
    if ( n<16 )  return;

    // n<=16:
    { Type t=f[8]; f[8]=f[15]; f[15]=f[10]; f[10]=f[12]; f[12]=t; }
    { Type t=f[9]; f[9]=f[14]; f[14]=f[11]; f[11]=f[13]; f[13]=t; }
    if ( n<32 )  return;

    // special for n=32, 64, 128, 256:
    for (ulong m=32,c=1;  m<=n;  m*=2,c*=2)
    {
        for (ulong k=0,s=m/2; k<c; ++k,++s)
        {
            gray_permute_cycle(f, s, 8UL);
            gray_permute_cycle(f, s+2*c, 8UL);
        }
        if ( m==256 ) break;
    }
    if ( n<512 )  return;

    // n=512 ... \infty:
    gray_permute_ge_512(f, n);
}
// =========================


template <typename Type>
void
inverse_gray_permute(Type *f, ulong n)
// heavily optimised version
{
    if ( n<4 )  return;

    // n<=4:
    { Type t=f[2]; f[2]=f[3]; f[3]=t; }
    if ( n<8 )  return;

    // n<=8:
    { Type t=f[6]; f[6]=f[5]; f[5]=f[7]; f[7]=f[4]; f[4]=t; }
    if ( n<16 )  return;

    // n<=16:
    { Type t=f[12]; f[12]=f[10]; f[10]=f[15]; f[15]=f[8]; f[8]=t; }
    { Type t=f[13]; f[13]=f[11]; f[11]=f[14]; f[14]=f[9]; f[9]=t; }
    if ( n<32 )  return;

    // special for n=32, 64, 128, 256:
    for (ulong m=32,c=1;  m<=n;  m*=2,c*=2)
    {
        for (ulong k=0,s=m/2; k<c; ++k,++s)
        {
            inverse_gray_permute_cycle(f, s, 8UL);
            inverse_gray_permute_cycle(f, s+2*c, 8UL);
        }
        if ( m==256 ) break;
    }
    if ( n<512 )  return;

    // n=512 ... \infty:
    inverse_gray_permute_ge_512(f, n);
}
// =========================

#undef  ic
#undef  xm


// permute/graypermute.cc:
ulong * xor_tab(ulong ldx);
// used by:
template <typename Type>
void
half_gray_permute(Type *f, ulong n)
// formerly used by (inplace-) gray_permute() and inverse_gray_permute()
// allows inplace permutation with operation count n:
// let h(.) be halfgray_permute(.)
// then
// gray_permute(f, n) == { h(f, n);  h(f, n/2); h(f+n/2, n/2); }
// and
// inverse_gray_permute(f, n) == { h(f, n/2); h(f+n/2, n/2);  h(f, n); }
{
    if ( n<=2 )  return;

    ulong *xm = xor_tab(ld(n));

    ulong k=0, r=0;
    while ( k<n  )
    {
        if ( r>k )  swap(f[k], f[r]);

        r ^= 1;
        ++k;

        if ( r>k )  swap(f[k], f[r]);

        ulong m = 2;
        ulong i = 1;
        while ( m & k )  // scan for lowest unset bit
        {
            m <<= 1;
            ++i;
        }
        r ^= xm[i];
        ++k;
    }
}
// ================= end ==================


#endif // !defined HAVE_GRAYPERMUTE_H__
