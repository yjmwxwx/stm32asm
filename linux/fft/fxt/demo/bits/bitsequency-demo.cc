
#include "bits/bitsequency.h"

#include "bits/print-bin.h"

#include "nextarg.h"
#include "fxttypes.h"

#include "fxtio.h"
#include "jjassert.h"


//% Generating bit sets of given sequency.


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Word size in bits");
    ulong sq = n+1;
    NXARG(sq, "If <=n, than only show words with sequency sq");


    ulong i0 = 0,  i1 = n;
    if ( sq<=n )  { i0=sq; i1=sq+1; }
    for (ulong i=i0; i<i1 ; ++i)
    {
        ulong c = first_sequency(i+1);

#ifndef TIMING
        cout << endl;
        cout << "   sequency = " << bit_sequency(c) << endl;
        print_bin(" ", c, n);
//        print_bin("    ", c ^ 0xaaaaaaaaUL, n);  // negated sequency
        cout << endl;
#endif

        ulong bct = 0;
        do
        {
            ++bct;
            c = next_sequency(c);

            // special condition for n-bit demo:
            if ( c>=(1UL<<n) )  break;

#ifndef TIMING
            print_bin(" ", c, n);
//            print_bin("    ", c ^ 0xaaaaaaaaUL, n);  // negated sequency
            cout << endl;
            jjassert( bit_sequency(c)==(i+1) );
#endif
        }
        while ( c );

#ifndef TIMING
        cout << " bct == " << bct;
        cout << endl;
#endif
    }

#ifdef TIMING
    cout << " ct=" << (1UL<<n) << endl;
#endif

    return 0;
}
// -------------------------

/*
Timing:
time ./bin 29
arg 1: 29 == n  [Word size in bits]  default=6
 ct=536870912
./bin 29  9.65s user 0.00s system 100% cpu 9.652 total
 ==> 536870912/9.65 == 55,634,291 per second
*/

/*
BENCHARGS=29
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitsequency-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitsequency-demo.cc DEMOFLAGS=-DTIMING"
/// End:

