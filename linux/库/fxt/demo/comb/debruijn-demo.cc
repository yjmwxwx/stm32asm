
#include "comb/debruijn.h"  // class debruijn
// demo-include "comb/necklace.h"

#include "aux0/ipow.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"

#include "nextarg.h"

//% Generating De Bruijn sequences.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong m = 3;
    NXARG(m, "m-ary De Bruijn sequence")
    ulong n = 4;
    NXARG(n, "length = m**n")

    debruijn S(m, n);
    ulong ns = ipow(m, n);
    cout << "\n n = " << n
         << "  length = " << ns
         << ":" << endl;

    ulong i = S.first_string();
#ifndef TIMING
    do
    {
        cout << " ";
        for (ulong u=1; u<=i; ++u)  cout << S.a_[u];  // note: one-based array
        i = S.next_string();
    }
    while ( i );
    cout << endl;
#endif

    i = S.first_digit();
    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        cout << i;
#endif
        i = S.next_digit();
    }
    while ( i!=m );
    cout << endl;
    cout << " ct=" << ct << endl;
    jjassert( ct == ns );

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

% time ./bin 2 32
arg 1: 2 == m  [m-ary De Bruijn sequence]  default=3
arg 2: 32 == n  [length = m**n]  default=4
 n = 32  length = 4294967296:
 ct=4294967296
./bin 2 32  7.64s user 0.00s system 99% cpu 7.643 total
 ==> 2^32/7.64 == 562,168,494 per second

% time ./bin 5 14
arg 1: 5 == m  [m-ary De Bruijn sequence]  default=3
arg 2: 14 == n  [length = m**n]  default=4
 n = 14  length = 6103515625:
 ct=6103515625
./bin 5 14  12.26s user 0.00s system 99% cpu 12.267 total
 ==> 5^14/12.26 == 497,839,773 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/debruijn-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/debruijn-demo.cc DEMOFLAGS=-DTIMING"
/// End:

