
#include  "mod.h"

// multiply array by s:
void
multiply_val(mod *f, ulong n, mod s)
{
    while ( n-- )  f[n] *= s;
}
// -------------------------


void
copy(const mod *src, mod *dst, ulong n)
{
//    memcpy(dst,src,n*sizeof(mod));
    while ( n-- )  dst[n] = src[n];
}
// -------------------------
//  void * memcpy (void *TO, const void *FROM, size_t SIZE)
//  undefined if the two arrays TO and FROM overlap;
//
//  void * memmove (void *TO, const void *FROM, size_t SIZE)
//  ... even if those two blocks of space overlap.
