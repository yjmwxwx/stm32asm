
#include "comb/combination-lex.h"

#include "nextarg.h"

#include "fxttypes.h"
#include "fxtio.h"

#include "jjassert.h"


//% Generating all combinations in lexicographic order.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 7, k = 4;
    NXARG(n, "Combinations (n choose k) in lexicographic order:  n>0");
    NXARG(k, " 0 < k <= n");
    jjassert( 0<k );
    jjassert( k<=n );
    bool rq = 0;
    NXARG(rq, "Whether to reverse order");

    combination_lex C(n, k);

    if ( 0==rq )  C.first();
    else          C.last();

    ulong ct = 0;
#ifdef TIMING
    if ( 0==rq )  do  { ++ct; }  while ( k!=C.next() );
    else          do  { ++ct; }  while ( k!=C.prev() );

#else

    ulong j = 0;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";
        C.print_set("    ");
        cout << "  " << j << "  ";
        C.print_deltaset("    ");
        cout << endl;
        if ( 0==rq )  j = C.next();
        else          j = C.prev();
    }
    while ( j < k );
    cout << endl;
#endif  // TIMING

    cout << " ct = " << ct << endl;

    return 0;
}
// -------------------------


/*
Timing:

stem 99% cpu 1.128 total
15:18:21 jj@shuttle:~/work/fxt/ %  time ./bin 32 20
arg 1: 32 == n  [Combinations (n choose k) in lexicographic order:  n>0]  default=7
arg 2: 20 == k  [ 0 < k <= n]  default=4
arg 3: 0 == rq  [Whether to reverse order]  default=0
 ct = 225792840
./bin 32 20  2.17s user 0.00s system 99% cpu 2.172 total
 ==> 225792840/2.17 == 104,052,000 per second

%  time ./bin 32 12
arg 1: 32 == n  [Combinations (n choose k) in lexicographic order:  n>0]  default=7
arg 2: 12 == k  [ 0 < k <= n]  default=4
arg 3: 0 == rq  [Whether to reverse order]  default=0
 ct = 225792840
./bin 32 12  1.36s user 0.00s system 99% cpu 1.367 total
 ==> 225792840/1.36 == 166,024,147 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/combination-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/combination-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

