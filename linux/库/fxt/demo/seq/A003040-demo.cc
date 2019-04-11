
#include "comb/partition-dist-d-asc.h"
#include "comb/partition-hook-prod.h"
// demo-include "comb/partition-conj.h"
#include "aux0/factorial.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"
#include "jjassert.h"

//% OEIS sequence A003040:
//% Highest degree of an irreducible representation of symmetric group S_n of degree n.
//% Cf. sequence A082914:
//% Minimum product of hook lengths of a partition of n.

// Cf. seq/A218293-demo.cc
// Cf. comb/partition-dist-d-asc-demo.cc for partitions where parts differ by at least d
// Cf. comb/partition-asc-demo.cc for (all) partitions


//#define TIMING  // uncomment to disable printing

#include "bits/bitsperlong.h"

typedef ulong Type;
//typedef __uint128_t Type;  // if available

static void out(Type x)
{
    if ( x==0 )  { cout << 0;  return; }

    const ulong m = ~0UL;
    ulong s = sizeof(Type)/sizeof(ulong) * BITS_PER_LONG;
    s -= BITS_PER_LONG;

    while ( 0 == (m & (x >> s)) )  s -= BITS_PER_LONG;
    ulong r = m & (x >> s);
    cout << r;

    while ( s )
    {
        s -= BITS_PER_LONG;
        r = m & (x >> s);
        cout << setfill('0') << setw(2*BYTES_PER_LONG) << r;
    }

    cout << setfill(' ');
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "integer partitions of n (n<=12 for 32-bit systems, else n<=20)");
    ulong d = 0;
    NXARG(d, "minimal difference of parts");

    partition_dist_d_asc P(n, d);

    ulong ct = 0;

    ulong *B = new ulong[n];
    const Type nf = factorial(n);
    Type md = 1;

    ulong m = P.num_parts();
    do
    {
        ++ct;

        Type hp = partition_asc_hook_prod<Type>(P.data(), m, B);
        const Type t = nf / hp;
        if ( t > md )  md = t;
#ifndef TIMING
        cout << setw(3) << ct << ":";
//        cout << " [" << setw(2) << m << "] ";
        P.print("  ");


        cout << "    #=";
        out(t);

        cout << endl;

#endif  // TIMING

        jjassert( P.OK() );
        jjassert( nf % hp == 0 );  // caused by overflow if n is too big
    }
    while ( (m=P.next()) );

    cout << " ct=" << ct << endl;
    cout << " md=";
    out(md);
    cout << endl;

    delete [] B;

    return 0;
}
// -------------------------

/*
 s=0;  echo $(for n in $(seq 0 20); do ./bin $n $s; done | grep md= ) | sed 's/ md=/, /g;'

 s=1;  echo $(for n in $(seq 0 20); do ./bin $n $s; done | grep md= ) | sed 's/ md=/, /g;'
A000000 (not in the OEIS)
*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A003040-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A003040-demo.cc DEMOFLAGS=-DTIMING"
/// End:
