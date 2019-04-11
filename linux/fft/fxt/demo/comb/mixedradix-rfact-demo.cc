
#include "comb/mixedradix-rfact.h"

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"


//% Counting in rising factorial base,
//% special case of mixed radix counting.



//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of digits");

    mixedradix_rfact F(n);

    ulong ct = 0;

#ifdef TIMING

#ifdef MIXEDRADIX_RFACT_MAX_ARRAY_LEN
    cout << "MIXEDRADIX_RFACT_MAX_ARRAY_LEN is defined" << endl;
#endif
    bool bq = 0;
    NXARG(bq, "With benchmark: whether to generate in backward order");
    if ( ! bq )
    {
        cout << "forward:" << endl;
        F.first();
        do  { ++ct; }  while ( n != F.next() );
    }
    else
    {
        cout << "backward:" << endl;
        F.last();
        do  { ++ct; }  while ( n != F.prev() );
    }

#else  // TIMING

    cout << endl;
//    F.last();
    ulong j = F.pos();
    do
    {
#if 1
        cout << " " << setw(4) << ct << ":  ";
        F.print("    ", true );
        cout << setw(4) << j;
//        cout << setw(4) << j+1;  // for ct>=1: j = A055881(ct)
        cout << endl;
        ++ct;
#else // A006472
        ulong t = 1;
        for (ulong k=0; k<n; ++k)  t *= (F.data()[k] + 1);
        ct += t;
#endif
    }
    while ( n != (j=F.next()) );
//    while ( n != (j=F.prev()) );

#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 11 0
arg 1: 11 == n  [Number of digits]  default=3
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
 ct=479001600
./bin 11 0  1.61s user 0.00s system 99% cpu 1.617 total
 ==> 479001600/1.61 == 297,516,521 per second

 time ./bin 11 1
arg 1: 11 == n  [Number of digits]  default=3
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
 ct=479001600
./bin 11 1  1.44s user 0.00s system 99% cpu 1.443 total
 ==> 479001600/1.44 == 332,640,000 per second


With MIXEDRADIX_RFACT_MAX_ARRAY_LEN defined:

 time ./bin 11 0
arg 1: 11 == n  [Number of digits]  default=3
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
MIXEDRADIX_RFACT_MAX_ARRAY_LEN is defined
forward:
 ct=479001600
./bin 11 0  1.37s user 0.00s system 99% cpu 1.370 total
 ==> 479001600/1.37 == 349,636,204 per second

 time ./bin 11 1
arg 1: 11 == n  [Number of digits]  default=3
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
MIXEDRADIX_RFACT_MAX_ARRAY_LEN is defined
backward:
 ct=479001600
./bin 11 1  0.96s user 0.00s system 99% cpu 0.959 total
 ==> 479001600/0.96 == 498,960,000 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-rfact-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-rfact-demo.cc DEMOFLAGS=-DTIMING"
/// End:

