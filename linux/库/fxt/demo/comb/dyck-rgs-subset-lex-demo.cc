
#include "comb/dyck-rgs-subset-lex.h"
#include "comb/is-dyck-rgs.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Restricted growth strings (RGS) for k-ary Dyck words, that is,
//% strings a[0,1,...,n-1] where a[0]=0 and a[j] <= a[j-1] + (k-1).
//% Subset-lex order.
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
#ifdef DYCK_RGS_SUBSET_LEX_SC
    NXARG(n, "Length of RGS");
#else
    NXARG(n, "Length of RGS (n>=2)");
    jjassert( n>=2 );
#endif

    ulong k = 3;
    NXARG(k, "k-ary Dyck words, k>=2 (k==2 gives Catalan RGS).");
    jjassert( k>=2 );

    dyck_rgs_subset_lex C(n, k);
    bool bw = 0;
    NXARG(bw, "Whether to generate backward order");
    if ( bw )  C.last();

    ulong ct = 0;
#ifdef TIMING
#ifdef DYCK_RGS_SUBSET_LEX_SC
    cout << "DYCK_RGS_SUBSET_LEX_SC is defined" << endl;
#endif
    if ( bw )
    {
        cout << "backward:" << endl;
        do  { ++ct; }  while ( C.prev() );
    }
    else
    {
        cout << "forward:" << endl;
        do  { ++ct; }  while ( C.next() );
    }

#else

    bool q;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";

        // print RGS:
        C.print("  ", true);

#if 1
        cout << setw(4) << C.tr_;

        // print Dyck word:
        const char *str = C.bit_string();
        cout << "    " << str;
#endif
        cout << endl;
        jjassert( C.OK() );

        q = ( bw ? C.prev() : C.next() );
    }
    while ( q );
#endif  // TIMING

    cout << " ct=" << ct;
    cout << endl;


    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 19 2 0
DYCK_RGS_SUBSET_LEX_SC is defined
forward:
 ct=1767263190
./bin 19 2 0  5.19s user 0.00s system 99% cpu 5.195 total
 ==> 1767263190/5.19 == 340,513,138 per second

// when DYCK_RGS_SUBSET_LEX_SC is not defined:
./bin 19 2 0  4.54s user 0.00s system 99% cpu 4.541 total


DYCK_RGS_SUBSET_LEX_SC is defined
backward:
 ct=1767263190
./bin 19 2 1  3.70s user 0.00s system 99% cpu 3.705 total
 ==> 1767263190/3.70 == 477,638,700 per second

// when DYCK_RGS_SUBSET_LEX_SC is not defined:
./bin 19 2 1  3.60s user 0.00s system 99% cpu 3.598 total


 time ./bin 14 3 0
DYCK_RGS_SUBSET_LEX_SC is defined
forward:
 ct=1822766520
./bin 14 3 0  5.03s user 0.00s system 99% cpu 5.031 total
 ==> 1822766520/5.03 == 362,379,029 per second

 time ./bin 14 3 1
DYCK_RGS_SUBSET_LEX_SC is defined
backward:
 ct=1822766520
./bin 14 3 1  3.52s user 0.00s system 99% cpu 3.524 total
 ==> 1822766520/3.52 == 517,831,397 per second


 time ./bin 12 4 0
DYCK_RGS_SUBSET_LEX_SC is defined
forward:
 ct=1882933364
./bin 12 4 0  4.97s user 0.00s system 99% cpu 4.974 total
 ==> 1882933364/4.97 == 378,859,831 per second

 time ./bin 12 4 1
DYCK_RGS_SUBSET_LEX_SC is defined
backward:
 ct=1882933364
./bin 12 4 1  3.51s user 0.00s system 99% cpu 3.516 total
 ==> 1882933364/3.51 == 536,448,251 per second

*/

/*
BENCHARGS=19 2 0
BENCHARGS=19 2 1
BENCHARGS=14 3 0
BENCHARGS=14 3 1
BENCHARGS=12 4 0
BENCHARGS=12 4 1
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/dyck-rgs-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/dyck-rgs-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

