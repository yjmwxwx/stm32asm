
#include "comb/partition-asc-sorts2-pp.h"

#include "sort/sort.h"  // is_sorted()

#include "fxtio.h"

#include "aux1/copy.h"  // fill()
#include "fxtalloca.h"

#include "comb/is-smooth.h"

#include "fxttypes.h"
#include "nextarg.h"

#include "jjassert.h"

//% Partitions into parts of s[k] sorts for part (size) k.
//% Representation as weakly ascending lists.
//% Lexicographic order: major order by parts, minor by sorts, where
//% comparison proceeds as part1, sort1; part2, sort2; part3, sort3, etc.
//% Cf. OEIS sequence A000219 (planar partitions).
//% Cf. OEIS sequences (partitions of n into parts of s kinds):
//% A000041 (s=1), A000712 (s=2), A000716 (s=3), A023003 (s=4),
//% A023004 (s=5), A023005 (s=6), A023006 (s=7), and A023007 (s=8).

// Cf. comb/partition-asc-sorts2-demo.cc
// Cf. comb/composition-nz-sorts2-pp-demo.cc


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "partitions of n");

    ulong ns = 0;
    NXARG(ns, "Number of sorts for parts by size (0==>1,2,3,4,...,n)");

    ulong ct = 0;

#ifdef TIMING
    partition_asc_sorts2_pp P(n, ns);
#ifdef PARTITION_ASC_SORTS2_PP_FIXARRAYS
    cout << "PARTITION_ASC_SORTS2_PP_FIXARRAYS defined." << endl;
#endif
    P.first();
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ALLOCA(ulong, vns, n);
    fill(vns, n, ns);
    RESTARGS("Optionally supply number of sorts for all part sizes (ns ignored)");
    if ( argc>3 )  jjassert( argc == (int)n+3 );
    for (ulong k=3;  k<(ulong)argc; ++k)  vns[k-3] = strtoul(argv[k], 0, 10);

    partition_asc_sorts2_pp P(n, ns, (argc>3? vns:0) );

//#define STATS
#ifdef STATS
    ulong* st = new ulong[n+1];  // stats
    for (ulong j=0; j<n; ++j)  st[j] = 0;
#endif

    ulong m = P.num_parts();
    do
    {
#if 0  // P-distinct: no two parts are of same size
        // ns=1 ==> A000009, prod(n>=1 1+x^k )
        // ns=2 ==> A032302, prod(n>=1 1+2*x^k )
        //   == 2 * A072706  (strongly unimodal partitions into distinct parts)
        // ns=3 ==> A032308, prod(n>=1 1+3*x^k ) == 3 * A000000 for n>=1
        // ns=4 ==> A000000, prod(n>=1 1+4*x^k ) == 4 * A000000 for n>=1
        bool q = true;
        const ulong *A = P.data();
        for (ulong j=1; j<m; ++j)
            if ( A[j] == A[j-1] )  { q=0; break; }
        if ( ! q )  continue;
#endif
#if 0  // S-distinct: no two successive parts are of same sort
        // ns=1 ==> just 1 partition for all n
        // ns=2 ==> A182372 (!)
        // ns=3 ==> A000000
        //   1, 3, 6, 10, 18, 29, 47, 70, 107, 158, 228, 326, 466,
        //    643, 890, 1217, 1659, 2222, 2972, 3940, 5209
        bool q = true;
        const ulong *S = P.sdata();
        for (ulong j=1; j<m; ++j)
            if ( S[j]==S[j-1] )  { q=0; break; }
        if ( ! q )  continue;
#endif
#if 0  // SP-distinct: no two parts are of same sort and size
        // ns=1 ==> A026007, prod(n>=1, (1+q^n)^n )
        // ns=2 ==> A022567, prod(n>=1, 1+q^n )^2
        // ns=3 ==> A022568, prod(n>=1, 1+q^n )^3
        // ns=4 ==> A022569, prod(n>=1, 1+q^n )^4
        // ns=5 ==> A022570, prod(n>=1, 1+q^n )^5
        // ...
        // ns=32 ==> A022596, prod(n>=1, 1+q^n )^32
        bool q = true;
        const ulong *A = P.data();
        const ulong *S = P.sdata();
        for (ulong j=1; j<m; ++j)
        {
            if ( A[j] == A[j-1] )
            {
                if ( S[j]==S[j-1] )  { q=0; break; }
            }
        }
        if ( ! q )  continue;
#endif
#if 0  // no three parts are of same size, no two parts (of same size) of same sort,
        // last part must be first sort.
        // ns=2 ==> A059618 (strongly unimodal partitions)
        if ( P.last_sort() != 0 )  continue;
        bool q = true;
        const ulong *A = P.data();
        const ulong *S = P.sdata();
        for (ulong j=1; j<m; ++j)
        {
            if ( A[j] == A[j-1] )
            {
                if ( S[j]==S[j-1] )  { q=0; break; }
//                if ( j>=2 )
//                    if ( A[j] == A[j-2] )  { q=0; break; }
            }
        }
        if ( ! q )  continue;
#endif
#if 0  // limit max sort (with ns=0):
        const ulong mns = 10;
        // 1 ==> A000041  1/prod(n>=1, (1-x^n)^1) (partitions)
        // 2 ==> A000990  1/prod(n>=1, (1-x^n)^min(n,2) )
        // 3 ==> A000991  1/prod(n>=1, (1-x^n)^min(n,3) )
        // 4 ==> A002799  1/prod(n>=1, (1-x^n)^min(n,4) )
        // 5 ==> A001452  1/prod(n>=1, (1-x^n)^min(n,5) )
        // 6 ==> A225196  1/prod(n>=1, (1-x^n)^min(n,6) )
        // 7 ==> A225197  1/prod(n>=1, (1-x^n)^min(n,7) )
        // 8 ==> A225198  1/prod(n>=1, (1-x^n)^min(n,8) )
        // 9 ==> A225199  1/prod(n>=1, (1-x^n)^min(n,9) )
        // 10 ==> A000000  1/prod(n>=1, (1-x^n)^min(n,10) )
        // infinity ==> A000219 1/prod(n>=1, (1-x^n)^n) (planar partitions)
        const ulong *S = P.sdata();
        ulong j;
        for (j=0; j<m; ++j)
            if ( S[j] >= mns )  break;
        if ( j != m )  continue;
#endif


#ifdef STATS // A091355
        // Columns 1-5 are repectively A000041, A091356, A091357, A091358, and A091359.
        // Columns converge to A091360.
        const ulong *S = P.sdata();
        ulong t = 0;
        for (ulong j=0; j<m; ++j)
            if ( S[j] > t )  t = S[j];
        st[t] += 1;
#endif

#if 0  // only odd parts: A000000 (not A242362 "Plane partitions into odd parts")
        { const ulong *x = P.data();
            ulong j;
            for (j=0; j<m; ++j)  if ( 0==(x[j]&1) )  break;
            if ( j != m )  continue;
        }
#endif


#if 0  // A000000
        if ( ! is_left_smooth(P.data(), P.num_parts()) )  continue;
#endif

        ++ct;

#if 1
        cout << setw(4) << ct << ":";
        P.print("  ");
//        P.print_rev("  ");  // print in weakly descending order
//        P.print_by_sorts("  ");
        cout << endl;

        jjassert( P.OK() );
#endif
    }
    while ( (m=P.next()) );
#endif  // TIMING

#ifdef STATS
    ulong y = 0;
    for (ulong j=0; j<=n; ++j)
    { y += st[j];   cout << st[j] << ", "; }
    cout << endl;
    jjassert( y == ct );
#endif

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)


 time ./bin 110 1
arg 1: 110 == n  [partitions of n]  default=6
arg 2: 1 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
 ct=607163746
./bin 110 1  4.51s user 0.00s system 99% cpu 4.509 total
 ==> 607163746/4.51 == 134,626,107 per second

 time ./bin 60 2
arg 1: 60 == n  [partitions of n]  default=6
arg 2: 2 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
 ct=962759294
./bin 60 2  4.92s user 0.00s system 99% cpu 4.926 total
 ==> 976562500/4.92 == 198,488,313 per second

 time ./bin 35 4
arg 1: 35 == n  [partitions of n]  default=6
arg 2: 4 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
 ct=1837560960
./bin 35 4  7.04s user 0.00s system 99% cpu 7.048 total
 ==> 1837560960/7.04 == 261,017,181 per second

 time ./bin 22 8
arg 1: 22 == n  [partitions of n]  default=6
arg 2: 8 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
 ct=4053978040
./bin 22 8  12.06s user 0.00s system 99% cpu 12.065 total
 ==> 4053978040/12.06 == 336,150,749 per second



 time ./bin 110 1
arg 1: 110 == n  [partitions of n]  default=6
arg 2: 1 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
PARTITION_ASC_SORTS2_PP_FIXARRAYS defined.
 ct=607163746
./bin 110 1  4.31s user 0.00s system 99% cpu 4.314 total
 ==> 607163746/4.31 == 140,873,258 per second

 time ./bin 60 2
arg 1: 60 == n  [partitions of n]  default=6
arg 2: 2 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
PARTITION_ASC_SORTS2_PP_FIXARRAYS defined.
 ct=962759294
./bin 60 2  4.39s user 0.00s system 99% cpu 4.392 total
 ==> 976562500/4.39 == 222,451,594 per second

 time ./bin 35 4
arg 1: 35 == n  [partitions of n]  default=6
arg 2: 4 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
PARTITION_ASC_SORTS2_PP_FIXARRAYS defined.
 ct=1837560960
./bin 35 4  6.45s user 0.00s system 99% cpu 6.455 total
 ==> 1837560960/6.45 == 284,893,172 per second

 time ./bin 22 8
arg 1: 22 == n  [partitions of n]  default=6
arg 2: 8 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
PARTITION_ASC_SORTS2_PP_FIXARRAYS defined.
 ct=4053978040
./bin 22 8  11.86s user 0.00s system 99% cpu 11.859 total
 ==> 4053978040/11.86 == 341,819,396 per second

*/

/*
BENCHARGS=110 1
BENCHARGS=60 2
BENCHARGS=35 4
BENCHARGS=22 8
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-asc-sorts2-pp-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-sorts2-pp-demo.cc DEMOFLAGS=-DTIMING"
/// End:

