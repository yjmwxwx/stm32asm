#if !defined  HAVE_GREENPERMUTE_H__
#define       HAVE_GREENPERMUTE_H__

#include "aux1/copy.h"
#include "bits/greencode.h"  // green_code()

#include "fxtalloca.h"
#include "fxttypes.h"
#include "restrict.h"


template <typename Type>
inline void green_permute(const Type *f, Type * restrict g, ulong n)
// =^=
// revbin_permute(f, n);
// gray_permute(f, n);
// revbin_permute(f, n);
{
    for (ulong k=0;  k<n;  ++k)
    {
        ulong r = green_code(k);
        r &= (n-1);
        g[r] = f[k];
    }
}
// -------------------------


template <typename Type>
inline void green_permute(Type *f, ulong n)
// =^=
// revbin_permute(f, n);
// gray_permute(f, n);
// revbin_permute(f, n);
//.
// todo: in-place version as for gray_permute()
{
    ALLOCA(Type, g, n);
    green_permute(f, g, n);
    copy(g, f, n);
}
// -------------------------

template <typename Type>
inline void inverse_green_permute(const Type *f, Type * restrict g, ulong n)
// inverse of green_permute()
{
    for (ulong k=0;  k<n;  ++k)
    {
        ulong r = green_code(k);
        r &= (n-1);
        g[k] = f[r];
    }
}
// -------------------------


template <typename Type>
inline void inverse_green_permute(Type *f, ulong n)
// inverse of green_permute()
// =^=
// revbin_permute(f, n);
// inverse_gray_permute(f, n);
// revbin_permute(f, n);
//.
// todo: in-place version as for gray_permute()
{
    ALLOCA(Type, g, n);
    inverse_green_permute(f, g, n);
    copy(g, f, n);
}
// -------------------------

#endif  // !defined HAVE_GREENPERMUTE_H__
