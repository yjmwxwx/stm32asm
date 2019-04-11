
#include "comb/partition-desc.h"

#include "comb/partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions as weakly descending list of parts.
//% Cf. OEIS sequence A000041.

// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending lists

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 11;
    NXARG(n, "integer partitions of n");

    partition_desc P(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef PARTITION_DESC_FIXARRAYS
    cout << "PARTITION_DESC_FIXARRAYS is defined" << endl;
#endif

    bool bq = 0;
    NXARG(bq, "With benchmark: whether to generate in backward order");
    if ( ! bq )
    {
        cout << "forward:" << endl;
        P.first();
        do  { ++ct; }  while ( P.next() );
    }
    else
    {
        cout << "backward:" << endl;
        P.last();
        do  { ++ct; }  while ( P.prev() );
    }

#else  // TIMING

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

//    P.last();
    ulong m = P.num_parts();
    do
    {
#if 0  // only into self-conjugate partitions
        if ( !partition_desc_is_self_conj( P.data(), m ) )  continue;
#endif
#if 0  // modulo conditions:
        const ulong *x = P.data();
        bool q = true;
        for (ulong j=0; j<m; ++j)
        { ulong v=x[j];
//            v%=5; if ( (v!=1) && (v!=4) )  // A003114
//            v%=5; if ( (v!=2) && (v!=3) )  // A003106
//            v%=5; if ( (v!=2) && (v!=1) )  // A035371
//            v%=4; if ( (v!=2) && (v!=1) )  // A035365
//            v%=4; if ( (v!=1) )  // A035451
            v%=4; if ( (v==0) )  // A001935
            { q=false; break; }
        }
        if ( !q )  continue;
#endif
#if 0  // growth conditions:
        const ulong *x = P.data();
        bool q = true;
        for (ulong j=1; j<m; ++j)  // all but first part even
            if ( 0!=(x[j]%2) )  { q=false; break; }  // A119620
        if ( !q )  continue;
#endif
#if 0  // growth conditions:
        const ulong *x = P.data();
        bool q = true;
        for (ulong j=1; j<m; ++j)
        {
//            if ( x[j-1] >= 2 * x[j] )  // A000000
//            if ( x[j-1] > 2 * x[j] )  // A000000
            if ( x[j-1] - x[j] > 1 )  // A034296 (flat partitions)
//            if ( x[j-1] - x[j] > 2 )  // A224956
//            if ( x[j-1] - x[j] < 2 )  // A003114
//            if ( x[j-1] - x[j] < 3 )  // A025157
//            if ( (x[j-1] - x[j])%2==0  )  // A179080
//            if ( (x[j-1] - x[j])%2==1  )  // A096441
            { q=false; break; }
        }
        if ( !q )  continue;
//        if ( P.last_part() != 1 )  continue; // with flat partitions ==> A000009
#endif
#if 0  // all parts (except the largest) may appear only once:
        const ulong *x = P.data();
        bool q = true;
        ulong x0 = x[0];
        { ulong j=1;  while ( (x[j]==x0) && (j<m) )  ++j;
            for ( ; j<m; ++j)
            {
                if ( x[j-1] == x[j] )  // A034296  (flat partitions)
                { q=false; break; }
            }
        }
        if ( !q )  continue;
#endif
#if 0 // bounding box
        if ( m > 7 )  continue;  // max length
//        if ( P.first_part() > 7 )  continue;  // max part
#endif
//        if ( 0!=(P.data()[m-1]&1) )  continue; // least part even: A026805
//        if ( 0!=(m&1) )  continue; // even number of parts: A027187
//        if ( 0!=(P.data()[0]&1) )  continue; // largest part even: A027187 (==even num parts)
        // even num & largest even: A000000 (not in the OEIS)

//        if ( 0==(P.data()[m-1]&1) )  continue; // least part odd: A026804
//        if ( 0==(m&1) )  continue; // odd number of parts: A027193
//        if ( 0==(P.data()[0]&1) )  continue; // largest part odd: A027193 (==odd num parts)
        // odd num & largest odd: A000000 (not in the OEIS)


        ++ct;
//        cout << "[" << setw(2) << ct << "]";  // format for OEIS examples
        cout << setw(4) << ct << ": ";
        cout << " [" << setw(2) << m << "] ";

//        cout << " d=" << setw(2) << P.durfee_n() << " ";


//        cout << " [" << setw(2) << n-m << "] ";
//        cout << " [" << setw(2) << P.data()[m-1] << "] ";
//        cout << " [" << setw(2) << P.s_ << "] ";

        P.print("  ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
//            P.print_conj_aa();
            cout << endl;
            cout << endl;
        }

        jjassert( P.OK() );
    }
    while ( (m=P.next()) );
//    while ( (m=P.prev()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

gcc 4.5.0:

 time ./bin 115 0
arg 1: 115 == n  [integer partitions of n]  default=11
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
 ct=1064144451
./bin 115 0  3.97s user 0.00s system 99% cpu 3.968 total
 ==> 1064144451/3.97 == 268,046,461 per second

 time ./bin 115 0
arg 1: 115 == n  [integer partitions of n]  default=11
PARTITION_DESC_FIXARRAYS is defined
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
 ct=1064144451
./bin 115 0  4.53s user 0.00s system 99% cpu 4.530 total
 ==> 1064144451/4.53 == 234,910,474 per second


 time ./bin 115 1
arg 1: 115 == n  [integer partitions of n]  default=11
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
 ct=1064144451
./bin 115 1  6.34s user 0.00s system 99% cpu 6.347 total
 ==> 1064144451/6.34 == 167,846,127 per second

 time ./bin 115 1
arg 1: 115 == n  [integer partitions of n]  default=11
PARTITION_DESC_FIXARRAYS is defined
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
 ct=1064144451
./bin 115 1  5.33s user 0.00s system 99% cpu 5.328 total
 ==> 1064144451/5.33 == 199,651,866 per second



gcc 4.8.0:

 time ./bin 115 0
arg 1: 115 == n  [integer partitions of n]  default=11
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
 ct=1064144451
./bin 115 0  5.10s user 0.01s system 99% cpu 5.110 total
 ==> 1064144451/5.10 == 208,655,774 per second

 time ./bin 115 0
arg 1: 115 == n  [integer partitions of n]  default=11
PARTITION_DESC_FIXARRAYS is defined
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
 ct=1064144451
./bin 115 0  4.37s user 0.00s system 99% cpu 4.370 total
 ==> 1064144451/4.37 ==243,511,316  per second


 time ./bin 115 1
arg 1: 115 == n  [integer partitions of n]  default=11
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
 ct=1064144451
./bin 115 1  5.32s user 0.00s system 99% cpu 5.318 total
 ==> 1064144451/5.32 == 200,027,152 per second

 time ./bin 115 1
arg 1: 115 == n  [integer partitions of n]  default=11
PARTITION_DESC_FIXARRAYS is defined
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
 ct=1064144451
./bin 115 1  6.02s user 0.00s system 99% cpu 6.021 total
 ==> 1064144451/6.02 ==176,768,181  per second

*/

/*
BENCHARGS=115 0
BENCHARGS=115 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-desc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-desc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

