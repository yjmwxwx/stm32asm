
#include "bitsperlong.h"  // BITS_PER_LONG
#include "auxbit.h"  // graycode()



// referenced from graypermute.h:
ulong gray_permute_index_cache[BITS_PER_LONG];
ulong gray_permute_update_masks[BITS_PER_LONG];
//
// ldm \ xm[]
//  7:    1   3   7
//  8:    2   6  14
//  9:    1   5  13  29
// 10:    1   3  11  27  59
// 11:    1   3   7  23  55 119
// 12:    1   3   7  15  47 111 239
// 13:    1   3   7  15  31  95 223 479
// 14:    1   3   7  15  31  63 191 447  959
// 15:    1   3   7  15  31  63 127 383  895 1919
// 16:    2   6  14  30  62 126 254 766 1790 3838
// 17:    1   5  13  29  61 125 253 509 1533 3581 7677
// 18:    1   3  11  27  59 123 251 507 1019 3067 7163 15355
// 19:    1   3   7  23  55 119 247 503 1015 2039 6135 14327 30711
// 20:    1   3   7  15  47 111 239 495 1007 2031 4079 12271 28655 61423
// 21:    1   3   7  15  31  95 223 479  991 2015 4063  8159 24543 57311 122847


#ifdef  SECOND_BEST_GRAY_PERMUTE  // never defined

ulong *
xor_tab(ulong ldx)
// called by halfgray_permute()
//
// ldx: z[0] [1] [2] [3] ...
//   1:   1
//   2:   1   2
//   3:   1   3   4
//   4:   1   2   7   8
//   5:   1   3   5  15  16
//   6:   1   2   6  10  31  32
//   7:   1   3   4  12  21  63  64
//   8:   1   2   7   8  25  42 127  128
//   9:   1   3   5  15  17  51  85  255  256
//  10:   1   2   6  10  30  34 102  170  511  512
//  11:   1   3   4  12  20  60  68  204  341 1023  1024
//  12:   1   2   7   8  24  40 120  136  409  682  2047  2048
//  13:   1   3   5  15  16  48  80  240  273  819  1365  4095  4096
{
    static const ulong n = BITS_PER_LONG;
    static ulong xm[n+1];

    // to avoid repeated computations for same size use:
//    static ulong lastldx = 0;
//    if ( lastldx==ldx )  return xm;
//    lastldx = ldx;

    if ( ldx==0 )
    {
        xm[0] = 1;
        return xm;
    }

    xm[ldx-1] = 1<<(ldx-1);
    for (ulong j=ldx-1; j>0; --j)
    {
        xm[j-1] = inverse_graycode(xm[j]-((xm[j]+1)>>1));
    }

    return xm;
}
// ================= end ==================

template <typename Type>
void
gray_permute(Type *f, ulong n)
// inplace version, operation count is C*n
{
    if ( n<4 )  return;

    half_gray_permute(f, n);
    half_gray_permute(f, n/2);  half_gray_permute(f+n/2, n/2);
}
// ================= end ==================


template <typename Type>
void
inverse_gray_permute(Type *f, ulong n)
// inplace version, operation count is C*n
{
    if ( n<4 )  return;

    half_gray_permute(f, n/2);  half_gray_permute(f+n/2, n/2);
    half_gray_permute(f, n);
}
// ================= end ==================

#endif //  SECOND_BEST_GRAY_PERMUTE  // never defined


#ifdef  THIRD_BEST_GRAY_PERMUTE  // never defined

template <typename Type>
void
gray_permute(Type *f, ulong n)
// inplace version, operation count is n*log_2(n)
{
    if ( n<4 )  return;

    for (ulong h=n/2; h>=2; h/=2)
    {
        for (Type *p = f+n-h;  p>f;  p-=2*h)
        {
            // reverse(p, h); // =^=
            for (ulong i=0,j=h-1; i<j; ++i,--j)  swap(p[i], p[j]);
        }
    }
}
// ================= end ==================


template <typename Type>
void
inverse_gray_permute(Type *f, ulong n)
// inplace version, operation count is n*log_2(n)
{
    if ( n<4 )  return;

    for (ulong h=2; h<n; h*=2)
    {
        for (Type *p = f+n-h;  p>f;  p-=2*h)
        {
            // reverse(p, h); // =^=
            for (ulong i=0,j=h-1; i<j; ++i,--j)  swap(p[i], p[j]);
        }
    }
}
// ================= end ==================

#endif // THIRD_BEST_GRAY_PERMUTE  // never defined
