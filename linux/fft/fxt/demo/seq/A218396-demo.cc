
#include "comb/partition-dist-asc.h"
#include "aux0/fibonacci.h"
#include "sort/bsearch.h"

#include "aux0/factorial.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% OEIS sequence A218396:
//% compositions into distinct (nonzero) Fibonacci numbers.
//% Also A032021: compositions into distinct odd numbers.
//% Also A000119: partitions into distinct Fibonacci numbers.
//% Also A000700: partitions into distinct odd numbers.

// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts as weakly ascending compositions
// Cf. comb/partition-demo.cc for partitions given as multiplicities of parts
// Cf. seq/A179080-demo.cc for partitions into distinct parts and adjacent parts have different parity.

//#define TIMING  // uncomment to disable printing

#define N 32
ulong S[N]; // allowed set


int
main(int argc, char **argv)
{
    ulong n = 37;
    NXARG(n, "compositions into distinct parts from a set, via integer partitions");
    bool fq = true;
    NXARG(fq, "whether to use Fibonacci numbers (else odd numbers)");

    partition_dist_asc P(n);


    if ( fq )  for (ulong k=0; k<N; ++k)  S[k] = fibonacci(k+1);
    else  for (ulong k=0; k<N; ++k)  S[k] = 2*k+1;

    jjassert( S[N-1] >= n );  // fixme: need more elements for odd numbers


    ulong pct = 0;  // count partitions
    ulong cct = 0;  // count compositions

    const ulong *x = P.data();
    ulong m = P.m_;
    do
    {

        { // fibs only
            bool q = true;
            for (ulong k=0; k<m; ++k)
                if ( N == bsearch(S, N, x[k]) )  { q=false; break; };
            if ( !q )  continue;
        }


        ulong f = factorial(m);
        cct += f;  // compositions

        ++pct;  // partitions


#ifndef TIMING
        cout << setw(3) << pct << ": ";

        for (ulong k=0; k<m; ++k)  cout << " " << x[k];
        cout << "    (" << f << " composition" << (f>1?"s":"") <<")";
        cout << endl;

        jjassert( P.OK() );
#endif  // TIMING
    }
    while ( (m=P.next()) );

    cout << "  pct=" << pct << endl;
    cout << "  cct=" << cct << endl;

    return 0;
}
// -------------------------

/*

// distinct Fibonacci numbers, compositions (A218396):
 echo $(for n in $(seq 1 25) ; do ./bin $n 1 | g -F 'cct=' | cut -d= -f2; done ) | sed 's/ /, /g;'
1, 1, 3, 2, 3, 8, 2, 9, 8, 8, 32, 6, 9, 32, 8, 38, 30, 32, 150, 6, 33, 32, 32, 158, 30

// cf. A076739: compositions into Fibonacci numbers

// distinct Fibonacci numbers, partitions (A000119):
 echo $(for n in $(seq 1 25) ; do ./bin $n 1 | g -F 'pct=' | cut -d= -f2; done ) | sed 's/ /, /g;'
1, 1, 2, 1, 2, 2, 1, 3, 2, 2, 3, 1, 3, 3, 2, 4, 2, 3, 3, 1, 4, 3, 3, 5, 2

// distinct odd numbers, compositions (A032021):
 echo $(for n in $(seq 1 25) ; do ./bin $n 0 | g -F 'cct=' | cut -d= -f2; done ) | sed 's/ /, /g;'
1, 0, 1, 2, 1, 2, 1, 4, 7, 4, 7, 6, 13, 6, 19, 32, 25, 32, 31, 58, 43, 82, 49, 132, 181

// distinct odd numbers, partitions (A000700):
 echo $(for n in $(seq 1 25) ; do ./bin $n 0 | g -F 'pct=' | cut -d= -f2; done ) | sed 's/ /, /g;'

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A218396-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A218396-demo.cc DEMOFLAGS=-DTIMING"
/// End:
