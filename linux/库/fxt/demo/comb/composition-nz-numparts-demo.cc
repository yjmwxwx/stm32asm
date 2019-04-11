
#include "comb/composition-nz-numparts.h"

#include "nextarg.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "fxtio.h"


//% Compositions of n into non-zero parts.
//% Ordering is firstly by number of parts (1, 2, ..., n)
//% and secondly co-lexicographic (colex).

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Compositions of n (n>=1)");

    composition_nz_numparts P(n);
    P.first();

    ulong ct = 0;

#ifdef TIMING
    do { ++ct; }  while  ( P.next() <= n );
#else

    ulong k = P.num_parts();
    do
    {
        ++ct;

        cout << setw(4) << ct << ":";
        P.print("    ", true);
//        cout << "  " << k;
        cout << endl;
        jjassert( P.OK() );
    }
    while ( (k=P.next()) <= n );
#endif  // TIMING


    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 31
arg 1: 31 == n  [Compositions of n (n>=1)]  default=6
  ct=1073741824
./bin 31  4.77s user 0.00s system 99% cpu 4.771 total
 ==> 1073741824/4.77 == 225,103,107 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-numparts-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-numparts-demo.cc DEMOFLAGS=-DTIMING"
/// End:
