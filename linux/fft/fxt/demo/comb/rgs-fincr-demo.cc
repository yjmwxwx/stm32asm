
#include "comb/rgs-fincr.h"


#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"

//% All restricted growth strings (RGS) s[0,...,n-1]
//%   so that  s[k] <= F[j]+i  where
//%  F[0]=i, F[j+1]=( a[j+1]-a[j]==i ?  F[j]+i : F[j] )
//% Lexicographic order.
//% Cf. OEIS sequences
//%  A000110 (i=1),  A004211 (i=2),  A004212 (i=3),
//%  A004213 (i=4),  A005011 (i=5),  A005012 (i=6).



//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Length of restricted growth strings (n>=1)");
    jjassert( n>=1 );

    ulong i = 2;
    NXARG(i, "Increment allowed (1==> set partitions)");
    // i=1 ==> RGS for set partitions (Bell numbers), OEIS sequence A000110
    // i=2 ==> A004211,  i=3 ==> A004212,  i=4 ==> A004213
    // i=5 ==> A005011,  i=6 ==> A005012
    // i=x ==> "shifts one place left under x-th order binomial transform"
    //          a(n)=sum((x^(n-k))*stirling2(n, k)

    rgs_fincr R(n, i);

    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        cout << setw(4) << ct << ":";
        R.print("    ", true);
        cout << endl;
#endif  // TIMING
    }
    while ( R.next() );

    cout << " ct = " << ct << endl;

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 12
 ct = 487026929
./bin 12  3.58s user 0.02s system 99% cpu 3.602 total
 ==> 487026929/3.58 == 136,041,041 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12
arg 1: 12 == n  [Length of restricted growth strings]  default=4
arg 2: 2 == i  [Increment allowed (1==> set partitions)]  default=2
 ct = 487026929
./bin 12  1.73s user 0.00s system 99% cpu 1.731 total
 ==> 487026929/1.73 == 281,518,456 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/rgs-fincr-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/rgs-fincr-demo.cc DEMOFLAGS=-DTIMING"
/// End:

