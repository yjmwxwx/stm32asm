
#include "comb/partition-desc-bb.h"

#include "comb/partition-conj.h"
#include "comb/print-partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions as weakly descending list of parts,
//%   with bounds for size of parts and number of parts.
//% Lexicographic order.

// Cf. comb/partition-desc-demo.cc for all partitions as weakly descending lists
// Cf. comb/partition-asc-demo.cc for all partitions as weakly ascending lists

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 16;
    NXARG(n, "integer partitions of n");

    ulong ba = 6;
    NXARG(ba, "bound for size of parts (0==> no restriction)");
    ulong bm = 6;
    NXARG(bm, "bound for number of parts (0==> no restriction)");

    partition_desc_bb P(n, ba, bm);

    ulong ct = 0;

#ifdef TIMING
#ifdef PARTITION_DESC_FIXARRAYS
    cout << "PARTITION_DESC_FIXARRAYS is defined" << endl;
#endif

//    bool bq = 0;
//    NXARG(bq, "With benchmark: whether to generate in backward order");
//    if ( ! bq )
//    {
//        cout << "forward:" << endl;
        bool q = P.first();
        if ( q )  do  { ++ct; }  while ( P.next() );
//    }
//    else
//    {
//        cout << "backward:" << endl;
//        bool q = P.last();
//        if ( q )  do  { ++ct; }  while ( P.prev() );
//    }

#else  // TIMING

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    bool q = P.first();
//    bool q = P.last();
    if ( q )
    {
        ulong m = P.num_parts();
        do
        {
            ++ct;
            cout << setw(4) << ct << ": ";
            cout << " [" << setw(2) << m << "] ";

//            cout << " d=" << setw(2) << P.durfee_n() << " ";


//            cout << " [" << setw(2) << n-m << "] ";
//            cout << " [" << setw(2) << P.data()[m-1] << "] ";
//            cout << " [" << setw(2) << P.s_ << "] ";

            P.print("  ");
            cout << endl;

//            print_partition_desc_conj("    ", P.data(), m);
//            cout << endl;

            if ( aa )  // ASCII art
            {
                P.print_aa();
//                P.print_conj_aa();
                cout << endl;
                cout << endl;
            }

            jjassert( P.OK() );
        }
        while ( (m=P.next()) );
        //    while ( (m=P.prev()) );
    }
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

gcc 4.5.0:  todo

gcc 4.8.0:

 time ./bin 110 0 0
arg 1: 110 == n  [integer partitions of n]  default=22
arg 2: 0 == ba  [bound for size of parts (0==> no restriction)]  default=7
arg 3: 0 == bm  [bound for number of parts (0==> no restriction)]  default=7
 ct=607163746
./bin 110 0 0  7.78s user 0.00s system 99% cpu 7.788 total
 ==> 607163746/7.78 == 78,041,612 per second

 time ./bin 130 22 22
arg 1: 130 == n  [integer partitions of n]  default=22
arg 2: 22 == ba  [bound for size of parts (0==> no restriction)]  default=7
arg 3: 22 == bm  [bound for number of parts (0==> no restriction)]  default=7
 ct=600482926
./bin 130 22 22  9.86s user 0.00s system 99% cpu 9.858 total
 ==> 600482926/9.86 == 60,900,905 per second


// with "optimize for long tail":
 time ./bin 110 0 0
arg 1: 110 == n  [integer partitions of n]  default=22
arg 2: 0 == ba  [bound for size of parts (0==> no restriction)]  default=7
arg 3: 0 == bm  [bound for number of parts (0==> no restriction)]  default=7
 ct=607163746
./bin 110 0 0  5.99s user 0.00s system 99% cpu 5.988 total
 ==> 607163746/5.99 == 101,362,895 per second

 time ./bin 130 22 22
arg 1: 130 == n  [integer partitions of n]  default=22
arg 2: 22 == ba  [bound for size of parts (0==> no restriction)]  default=7
arg 3: 22 == bm  [bound for number of parts (0==> no restriction)]  default=7
 ct=600482926
./bin 130 22 22  8.45s user 0.00s system 99% cpu 8.453 total
 ==> 600482926/8.45 == 71,063,068 per second


// with both "optimize for long+short tail":
 time ./bin 110 0 0
arg 1: 110 == n  [integer partitions of n]  default=22
arg 2: 0 == ba  [bound for size of parts (0==> no restriction)]  default=7
arg 3: 0 == bm  [bound for number of parts (0==> no restriction)]  default=7
 ct=607163746
./bin 110 0 0  6.10s user 0.00s system 99% cpu 6.106 total
 ==> 607163746/6.10 ==99,535,040  per second

 time ./bin 130 22 22
arg 1: 130 == n  [integer partitions of n]  default=22
arg 2: 22 == ba  [bound for size of parts (0==> no restriction)]  default=7
arg 3: 22 == bm  [bound for number of parts (0==> no restriction)]  default=7
 ct=600482926
./bin 130 22 22  8.53s user 0.00s system 99% cpu 8.535 total
 ==> 600482926/8.53 == 70,396,591 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-desc-bb-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-desc-bb-demo.cc DEMOFLAGS=-DTIMING"
/// End:

