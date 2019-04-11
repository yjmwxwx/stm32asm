
#include "bits/fibrep-subset-lexrev.h"

#include "bits/print-bin.h"


#include "aux0/fibonacci.h"
#include "bits/fibrep.h"

#include "fxttypes.h"
#include "fxtio.h"

//#include "bits/bitcount.h"
//#include "bits/bitlow.h"

#include "bits/bitsperlong.h"
#include "jjassert.h"

#include "nextarg.h"


//% Generating Fibonacci words in subset-lexrev order.

// Cf. bits/fibrep2-demo.cc for lexicographic order (wrt. to delta sets).
// Cf. bits/bitlex-demo.cc for the same order for all binary words.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "n-bit binary words");
    jjassert( n < BITS_PER_LONG );
    const ulong mm = 1UL<<(n-1);  // last
    bool bq = 0;
    NXARG(bq, "Whether to print list backwards");
    // Note: with benchmark: whether to go backwards

#ifdef TIMING

    if ( !bq )
    {
        cout << "forward:" << endl;
        ulong x = (1UL<<(n-1));
        do  { x = next_subset_lexrev_fib(x); }  while ( x!=0 );
    }
    else
    {
        cout << "backward:" << endl;
        ulong x = 0;
        do  { x = prev_subset_lexrev_fib(x); }  while ( x!=mm );
    }
    cout << " ct=" << fibonacci(n+2) << endl;

#else  // TIMING

    const ulong rq = n;

    if ( !bq )  // forward:
    {
        ulong x = 1UL<<(n-1);  // first subset
        ulong ct = 0;
        do
        {
            ++ct;
            cout  << setw(4) << ct << ":";
            print_bin("  ", x, n);
            cout << " = ";
            print_bit_set("  ", x, rq);
            cout << endl;
            x = next_subset_lexrev_fib(x);
        }
        while ( x );
    }
    else  // backward
    {
        ulong x = 0;
        ulong ct = 1;
        do
        {
            x = prev_subset_lexrev_fib(x);
            cout  << setw(4) << ct << ":";

            print_bin("  ", x, n);
            cout << "  = ";
            print_bit_set("  ", x, rq);

//            cout << "  :" << x << ":";  // OEIS A000000
//            cout << "  :" << fibrep2bin(x) << ":";  // OEIS A000000
//            print_bin("   ", fibrep2bin(x), n);  // OEIS A000000
//            cout << "  :" << lowest_one_idx(x) << ":";  // OEIS A000000
//            cout << "  :" << bit_count(x) << ":";  // OEIS A000000

            ++ct;
            cout << endl;
        }
        while ( x != mm );
    }
#endif  // TIMING


    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 44 0
arg 1: 44 == n  [n-bit binary words]  default=8
arg 2: 0 == bq  [Whether to print list backwards]  default=0
forward:
 ct=1836311903
./bin 44 0  5.15s user 0.00s system 99% cpu 5.153 total
 ==> 1836311903/5.15 == 356,565,418 per second

 time ./bin 44 1
arg 1: 44 == n  [n-bit binary words]  default=8
arg 2: 1 == bq  [Whether to print list backwards]  default=0
backward:
 ct=1836311903
./bin 44 1  4.28s user 0.00s system 99% cpu 4.284 total
 ==> 1836311903/4.28 == 429,044,837 per second

*/

/*
BENCHARGS=44 0
BENCHARGS=44 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/fibrep-subset-lexrev-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/fibrep-subset-lexrev-demo.cc DEMOFLAGS=-DTIMING"
/// End:

