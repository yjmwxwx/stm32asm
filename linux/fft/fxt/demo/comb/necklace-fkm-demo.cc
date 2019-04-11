
// demo-is-self-contained

#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "nextarg.h"

//% Fredericksen, Kessler, Maiorana (FKM) algorithm for generating necklaces.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Length of necklaces (n>=1)");
    ulong k = 2;
    NXARG(k, "Number of different beads (k>=2)");
    ulong *f = new ulong[n+1];  // 1-based, with sentinel at index zero
    f[0] = 0;

    for (ulong i=1; i<=n; ++i)  f[i] = 0;  // Initialize to 0
    ulong pct = 0, nct = 0, lct = 0;  // count pre-necklaces, necklaces and Lyndon words
    bool nq = 1;  // whether pre-necklace is a necklace
    bool lq = 0;  // whether pre-necklace is a Lyndon word
    ulong j = 1;
    while ( 1 )
    {
#if 0  // monotonic (i.e. modulo symbol permutations)
        for (long i=1, s=-1; (ulong)i<=n; ++i)
        {
            long fi = (long)f[i];
            if ( fi > s )
            {
                s += 1;
                if ( fi != s )  goto next;
            }
        }
        // k = 2:  N: A008965, L: A001037
        // k = 3:  N: A000000, L: A000000
#endif

#if 0  // K = 2:  N: A000016,  L: A000048
        ulong ct = 0;
        for (ulong i=1; i<=n; ++i)  ct += (f[i]==0);
        if ( (ct % 2) == 0 )  goto next;
#endif

        ++pct;
        if ( nq )  ++nct;
        if ( lq )  ++lct;

        // Print necklace:
#ifndef TIMING

        cout << setw(4) << pct << ":";
        print_vec("    ", f+1, n, true);
        cout << "   j=" << j;
        if ( nq )  cout << "  N";
        if ( lq )  cout << "  L";
        cout << endl;

#endif  // TIMING

//    next:

        // Find largest index where we can increment:
        j = n;
        while ( f[j]==k-1 )  { --j; };

        if ( j==0 )  break;

        ++f[j];

        // Copy periodically:
        for (ulong i=1, t=j+1;  t<=n;  ++i, ++t)  f[t] = f[i];

        nq = ( (n%j)==0 );  // necklace if j divides n
        lq = ( j==n );      // Lyndon word if j equals n
    }

#ifndef TIMING
    cout << "" << pct << " (" << n << ", " << k << ") pre-necklaces." << endl;
    cout << "" << nct << " necklaces and " << lct << " Lyndon words." << endl;
#else
    cout << " nct=" << nct << endl;
#endif
    // for OEIS sequences (see near end of file):
//    cout << "ct: " << pct << " " << nct << " " << lct << endl;

    delete [] f;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 32 2
arg 1: 32 == n  [Length of necklaces (n>=1)]  default=6
arg 2: 2 == k  [Number of different beads (k>=2)]  default=2
Generated 277737797 (32, 2) pre-necklaces.
Generated 134219796 necklaces and 134215680 Lyndon words.
./bin 32  11.67s user 0.06s system 99% cpu 11.733 total
 ==> 277737797/11.67 == 23,799,297 pre-necklaces per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 32 2
./bin 32 2  3.80s user 0.00s system 99% cpu 3.803 total
 ==> 277737797/3.80 == 73,088,893 pre-necklaces per second
*/

/*
BENCHARGS=32 2
*/


/*
OEIS sequences:
(descriptions valid only for k a prime power)

k-ary pre-necklaces:
% echo $(for n in $(seq 1 14); do ./bin $n 2 | g 'ct:'; done | cut -d' ' -f2) | sed 's/ /, /g;'
Number of irreducible polynomials over F_k of degree at most n.
a(n)=sum(m=1,n, 1/m* sumdiv(m, d, moebius(d)*k^(m/d) ) );
k=2: A062692, k=3: A114945,  k=4: A114946,  k=5: A114947,
  k=6: A000000, k=7: A000000, k=8: A000000, k=9: A000000

k-ary necklaces:
Number of k-ary irreducible polynomials whose degree divides n.
% echo $(for n in $(seq 1 14); do ./bin $n 2 | g 'ct:'; done | cut -d' ' -f3) | sed 's/ /, /g;'
k=2: A000031, k=3: A001867,

k-ary Lyndon words:
Number of degree-n irreducible polynomials over GF(k)
% echo $(for n in $(seq 1 14); do ./bin $n 2 | g 'ct:'; done | cut -d' ' -f4) | sed 's/ /, /g;'
k=2: A001037,

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/necklace-fkm-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/necklace-fkm-demo.cc DEMOFLAGS=-DTIMING"
/// End:

