#if !defined HAVE_GREENREVPERMUTE_H__
#define      HAVE_GREENREVPERMUTE_H__


#include "bits/greencode.h"  // green_code()
//#include "bits/bit2pow.h" // is_pow_of_2()
//#include "bits/bitsubset.h" // bitsubset

#include "fxtalloca.h"
#include "fxttypes.h"
#include "restrict.h"


template <typename Type>
inline void green_rev_permute(const Type *f, Type * restrict g, ulong n)
// green_rev_permute() =^=
//  { reverse(); green_permute(); }
{
    for (ulong k=0, m=n-1;  k<n;  ++k, --m)
    {
        ulong r = green_code(m);
        r &= (n-1);
        g[r] = f[k];
    }
}
// -------------------------


template <typename Type>
inline void inverse_green_rev_permute(const Type *f, Type * restrict g, ulong n)
// inverse of green_rev_permute()
// inverse_green_rev_permute() =^=
//  { inverse_green_permute(); reverse(); }
{
    for (ulong k=0, m=n-1;  k<n;  ++k, --m)
    {
        ulong r = green_code(m);
        r &= (n-1);
        g[k] = f[r];
    }
}
// -------------------------


template <typename Type>
void green_rev_permute(Type *f, ulong n)
//.
// todo: in-place version as for gray_permute()
{
    ALLOCA(Type, g, n);
    green_rev_permute(f, g, n);
    copy(g, f, n);
}
// -------------------------


template <typename Type>
void inverse_green_rev_permute(Type *f, ulong n)
//.
// todo: in-place version as for gray_permute()
{
    ALLOCA(Type, g, n);
    inverse_green_rev_permute(f, g, n);
    copy(g, f, n);
}
// -------------------------



#endif // !defined HAVE_GREENREVPERMUTE_H__
