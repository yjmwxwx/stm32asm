
#include "comb/setpart-p-rgs-lex.h"

#include "comb/comb-print.h"

#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"

//% Set partitions of the n-set into p parts as restricted growth strings (RGS).
//% Counted by the Stirling numbers of second kind S(n,p).
//% Cf. OEIS sequence A008277.

//#define TIMING  // uncomment to disable printing

// Cf. comb/setpart-rgs-lex-demo.cc for the RGS for all set partitions
// Cf. comb/setpart-ck-rgs-demo.cc for the Cooper-Kennedy RGS
// Cf. comb/setpart-zero-map-rgs-demo.cc for RGS using certain maps

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Partition set of n elements");

    ulong p = 3;
    if ( n<p )  p = n;
    NXARG(p, "Partitions into p parts (1<=p<=n)");
    if ( n )  jjassert( p>=1 );
    jjassert( p<=n );

    setpart_p_rgs_lex P(n, p);
    P.first(p);

    ulong ct = 0;

#ifdef TIMING
    do { ++ct; }  while ( P.next() );

#else

    do
    {
        ++ct;

        cout << setw(3) << ct << ":";
        P.print("  ", true);  // RGS
//        print_vec("  ", P.m_+1, n);  // array of max in prefix
        P.print_sets("    ");  // sets
        cout << endl;

        jjassert ( P.OK() );
    }
    while ( P.next() );
#endif

    cout << " ct=" << ct << endl;  // Stirling numbers of second kind S(n,p).

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 15 8
 ct = 216627840
./bin 15 8  2.00s user 0.00s system 99% cpu 2.005 total
 ==> 216627840/2.00 == 108,313,920 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 15 8
 ct = 216627840
./bin 15 8  1.53s user 0.00s system 99% cpu 1.528 total
 ==> 216627840/1.53 == 141,586,823 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/setpart-p-rgs-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/setpart-p-rgs-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

