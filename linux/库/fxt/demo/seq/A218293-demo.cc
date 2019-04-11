
#include "comb/partition-dist-d-asc.h"
#include "comb/partition-hook-prod.h"
// demo-include "comb/partition-conj.h"
#include "aux0/factorial.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"
#include "jjassert.h"

//% OEIS sequence A218293:
//% standard Young tableaux with shapes corresponding to partitions into distinct parts.
//% Also OEIS sequences
//% A000085 (all tableaux, d=0),
//% A225121 (tableaux for partitions into distinct parts with minimal difference 2, d=0),

// Cf. seq/A003040-demo.cc
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
    ulong n = 12;
    NXARG(n, "integer partitions of n (n<=12 for 32-bit systems, else n<=20)");
    ulong d = 1;
    NXARG(d, "minimal difference of parts");

    partition_dist_d_asc P(n, d);

    ulong ct = 0;



    ulong *B = new ulong[n];
    const Type nf = factorial(n);
    Type tbct = 0;

    ulong m = P.num_parts();
    do
    {
        ++ct;

        Type hp = partition_asc_hook_prod<Type>(P.data(), m, B);
        const Type t = nf / hp;
        tbct += t;

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
    cout << " tbct=";
    out(tbct);
    cout << endl;

    delete [] B;

    return 0;
}
// -------------------------

/*
 s=1;
 echo $(for n in $(seq 0 20); do ./bin $n $s; done | grep tbct= ) | sed 's/ tbct=/, /g;'
*/

/*
A003040: Highest degree of an irreducible representation of symmetric group S_n of degree n

for n in $(seq 1 13) ; do ./bin $n 0 | cut -s -d\# -f2 | cut -d= -f2 | sort -g | tail -1; done

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A218293-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A218293-demo.cc DEMOFLAGS=-DTIMING"
/// End:
