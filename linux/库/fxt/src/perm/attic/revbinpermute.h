#if !defined  HAVE_REVBINPERMUTE_H__
#define       HAVE_REVBINPERMUTE_H__


// tuning parameter:
#define  REVBIN_PERMUTE_UNROLL   1  // 0 or 1 (unroll, default)
#define  REVBIN_PERMUTE0_UNROLL  1  // 0 or 1 (unroll, default)


#if  ( REVBIN_PERMUTE_UNROLL==1 )
//#warning 'FYI: REVBIN_PERMUTE_UNROLL activated'
#else
//#warning 'FYI: no REVBIN_PERMUTE_UNROLL'
#endif

#if  ( REVBIN_PERMUTE0_UNROLL==1 )
//#warning 'FYI: REVBIN_PERMUTE0_UNROLL activated'
#else
//#warning 'FYI: no REVBIN_PERMUTE0_UNROLL'
#endif


template <typename Type>
void revbin_permute(Type *f, ulong n)
// put data in revbin order
// self-inverse
{
    if ( n<=2 )  return;

    const ulong nh = (n>>1);
    Type * const f1 = f + n - 1;
    swap(f[1], f[nh]);

    ulong k=2, r=nh;
#if  ( REVBIN_PERMUTE_UNROLL==1 )
    while ( 1  )
#else
    while ( k<nh  )
#endif
    {
        // k even:
        r ^= nh;
        for (ulong m=(nh>>1); !((r^=m)&m); m>>=1)  {;}
        if ( r>k )
        {
            swap(f[k], f[r]);     // k<nh, r<nh
            swap(f1[-k], f1[-r]); // n-k>nh, n-r>nh
        }
        ++k;

        // k odd:
        r += nh;
        swap(f[k], f[r]);  // k<nh, r>nh
        ++k;

#if  ( REVBIN_PERMUTE_UNROLL==1 )
        if ( k>=nh )  break;  // break always happens here

        // k even:
        r ^= nh;
        r ^= (nh>>1);
        for (ulong m=(nh>>2); !((r^=m)&m); m>>=1)  {;}
        if ( r>k )
        {
            swap(f[k], f[r]);     // k<nh, r<nh
            swap(f1[-k], f1[-r]); // n-k>nh, n-r>nh
        }
        ++k;

        // k odd:
        r += nh;
        swap(f[k], f[r]);  // k<nh, r>nh
        ++k;
#endif // REVBIN_PERMUTE_UNROLL
    }
}
//============== end =================


template <typename Type>
void revbin_permute0(Type *f, ulong n)
// put data in revbin order
// version for zero padded data
{
    if ( n<=2 )  return;

    const ulong nh = (n>>1);
    ulong k=2, r=nh;

    f[nh] = f[1];
    f[1] = 0;
#if  ( REVBIN_PERMUTE0_UNROLL==1 )
    while ( 1  )
#else
    while ( k<nh  )
#endif
//    for (ulong k=1,r=0; k<nh;  )
    {
        // k even:
        r ^= nh;
        for (ulong m=(nh>>1); !((r^=m)&m); m>>=1)  {;}
        if ( r>k )
        {
            swap(f[k], f[r]);
            // f[-k]==0, f[-r]==0
        }
        ++k;

        // k odd: f[k]!=0, f[r]==0
        r += nh;
        f[r] = f[k];
        f[k] = 0;
        ++k;

#if  ( REVBIN_PERMUTE0_UNROLL==1 )
        if ( k>=nh )  break;  // break always happens here

        // k even:
        r ^= nh;
        r ^= (nh>>1);
        for (ulong m=(nh>>2); !((r^=m)&m); m>>=1)  {;}
        if ( r>k )
        {
            swap(f[k], f[r]);
            // f[-k]==0, f[-r]==0
        }
        ++k;

        // k odd: f[k]!=0, f[r]==0
        r += nh;
        f[r] = f[k];
        f[k] = 0;
        ++k;
#endif // REVBIN_PERMUTE0_UNROLL
    }
}
//============== end =================

#endif // !defined HAVE_REVBINPERMUTE_H__
