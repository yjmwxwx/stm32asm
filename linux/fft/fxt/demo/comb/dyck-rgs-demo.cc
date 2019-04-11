
#include "comb/dyck-rgs.h"

#include "comb/comb-print.h"

#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"

//% Restricted growth strings (RGS) for k-ary Dyck words:
//% strings s[0,...,n-1] such that s[j] <= s[j-1] + i (where i=k-1).
//% Lexicographic order.
//% Number of RGS is binomial(i*n,n)/((i-1)*n+1), (Catalan numbers for i=1).


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Length of restricted growth strings");
    ulong i = 2;
    NXARG(i, "Increment allowed (1==> RGS for parentheses strings)");
    // OEIS sequences:
    // i=1 ==> A000108 = binomial(2n,n)/(n+1) (Catalan numbers)
    // i=2 ==> A001764 = binomial(3n,n)/(2n+1)
    // i=3 ==> A002293 = binomial(4n,n)/(3n+1)
    // i=4 ==> A002294 = binomial(5n,n)/(4n+1)
    // i=x ==> binomial(x*n,n)/((x-1)*n+1)
    bool bw = 0;
    NXARG(bw, "Whether to generate in backward order.");

    dyck_rgs R(n, i);

    ulong ct = 0;

#ifdef TIMING

    if ( ! bw )
    {
        cout << "forward:" << endl;
        R.first();
        do  { ++ct; }  while ( R.next() );
    }
    else
    {
        cout << "backward:" << endl;
        R.last();
        do  { ++ct; }  while ( R.prev() );
    }

#else  // TIMING

    const ulong k = i + 1;  // k-ary Dyck words (or trees)

    ulong *ds = new ulong[n];  // positions of ones in Dyck word
    const ulong N = k * n;  // size of delta set

    const ulong *a = R.data();

    if ( ! bw )  R.first();
    else         R.last();
    ulong j=0;
    do
    {
        ++ct;
        // positions of ones in delta sequence:
        for (ulong u=0; u<n; ++u)  ds[u] = k*u - a[u];

//        {  // OEIS sequence A004148:
//            // Number of Dyck paths of semilength n-1 with no UUU's and no DDD's,
//            ulong dt[N];  // delta sequence
//            for (ulong j=0; j<N; ++j)  dt[j] = 0;
//            for (ulong j=0; j<n; ++j)  dt[ds[j]] = 1;
//
//            bool q = true;
//            for (ulong j=2; j<N; ++j)
//                if ( (dt[j]==dt[j-1]) && (dt[j-1]==dt[j-2]) )  { q=false; break; }
//            if ( !q )  { --ct; continue; }
//        }

        cout << setw(4) << ct << ":";
        R.print("  ", true);

        cout << setw(4) << j;

        print_set_as_deltaset("    ", ds, n, N);
        print_vec("    ", ds, n);

        cout << endl;
        jjassert( R.OK() );

        if ( bw )  j =  R.prev();
        else       j =  R.next();
    }
    while ( j );

    delete [] ds;

#endif  // TIMING

    cout << " ct=" << ct << endl;



    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 18 1
 ct = 477638700
./bin 18 1  2.84s user 0.00s system 99% cpu 2.851 total
 ==> 477638700/2.84 == 168,182,640 per second

 time ./bin 13 2
 ct = 300830572
./bin 13 2  1.55s user 0.00s system 99% cpu 1.561 total
 ==> 300830572/1.55 == 194,084,240 per second

 time ./bin 12 3
 ct = 1882933364
./bin 12 3  8.61s user 0.00s system 99% cpu 8.632 total
 ==> 1882933364/8.61 == 218,691,447 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 18 1 0
 ct = 477638700
./bin 18 1 0  1.37s user 0.00s system 99% cpu 1.374 total
 ==> 477638700/1.37 == 348,641,386 per second

 time ./bin 18 1 1  # backward
 ct = 477638700
./bin 18 1 1  1.70s user 0.00s system 99% cpu 1.703 total
 ==> 477638700/1.70 == 280,963,941 per second

 time ./bin 14 2 0
 ct = 1822766520
./bin 14 2 0  5.04s user 0.00s system 99% cpu 5.046 total
 ==> 1822766520/5.04 == 361,660,023 per second

  time ./bin 14 2 1  # backward
 ct = 1822766520
./bin 14 2 1  5.94s user 0.00s system 99% cpu 5.942 total
 ==> 1822766520/5.94 == 306,863,050 per second

 time ./bin 12 3 0
 ct = 1882933364
./bin 12 3 0  4.92s user 0.00s system 99% cpu 4.924 total
 ==> 1882933364/4.92 == 382,710,033 per second

 time ./bin 12 3 1  # backward
 ct = 1882933364
./bin 12 3 1  6.14s user 0.00s system 99% cpu 6.143 total
 ==> 1882933364/6.14 == 306,666,671 per second


*/

/*
BENCHARGS=18 1 0
BENCHARGS=18 1 1
BENCHARGS=14 2 0
BENCHARGS=14 2 1
BENCHARGS=12 3 0
BENCHARGS=12 3 1
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/dyck-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/dyck-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

