
#include "sort/equivclasses.h"  // equivalence_classes()
#include "sort/sortbykey.h"  // sort_by_key()

#include "bits/revbin.h"  // revbin()


//#include "perm/permrand.h"  // random_permute()

#include "bits/print-bin.h"  // print_bin()
#include "nextarg.h"  // NXARG()
#include "fxttypes.h"  // ulong
//#include "bits/bitsperlong.h"

#include "fxtio.h"
#include "fxtalloca.h"


//% Equivalence classes: bit-strings with reversal and complement.
// Entry A005418 in the OEIS.

static ulong nb;  // number of bits
static ulong mm;  // mask to complement

bool bs_equiv_q(ulong x, ulong y)  // identify words that are mutal reverses
{
    if ( x==y )  return 1;
    if ( x==revbin(y, nb) )  return 1;
    return 0;
}
// -------------------------

bool bsu_equiv_q(ulong x, ulong y)  // unlabeled bit-strings
{
    if ( bs_equiv_q(y, x) )  return 1;
    x ^= mm;
    if ( bs_equiv_q(y, x) )  return 1;
    return  0;
}
// -------------------------


int
main(int argc, char **argv)
{
    nb = 6;
    NXARG(nb, "Number of bits of bit-strings (0<nb<BITS_PER_LONG).");
    ulong n = 1UL<<nb;
    mm = n-1;

    ulong cq = 1;
    NXARG(cq, "Whether equivalence includes complements (==> unlabeled bit-strings).");

    ulong ksq = 0;
    NXARG(ksq, "Whether to print key-sorted array.");

    ALLOCA(ulong, s, n);
    for (ulong k=0; k<n; ++k)  s[k] = k;
//    random_permute(s, n);

    ulong *e = new ulong[n];
    if ( 0==cq )  equivalence_classes(s, n, bs_equiv_q, e);
    else          equivalence_classes(s, n, bsu_equiv_q, e);

    // --- print all elements with 'coset leaders':
    for (ulong k=0; k<n; ++k)
    {
        cout << setw(3) << k << ": ";
        print_bin(" ", s[k], nb);
        cout << "  " << setw(2) << e[k];
        cout << endl;
    }
    cout << endl;


    sort_by_key(s, n, e, 0, true);
    if ( ksq )
    {
        for (ulong k=0; k<n; ++k)
        {
            cout << setw(3) << k << ": ";
            print_bin(" ", s[k], nb);
            cout << "  " << setw(2) << e[k];
            cout << endl;
        }
        cout << endl;
    }

    // --- print all elements in each equivalence class:
    ulong cct = 0;  // count number of classes
    for (ulong k=0; k<n; /**/ )
    {
        ++cct;
        ulong el = e[k];
        cout << setw(3) << el << ": ";
        ulong ct;
        for (ct=0;  k<n;  ++ct, ++k)
        {
            ulong ek = e[k];
            if ( ek != el )
            {
                break;
            }
            print_bin("  ", s[k], nb);
        }
        cout << "  [#=" << ct << "]";
        cout << endl;
    }
    cout << endl;
    cout << "  # of equivalence classes = " << cct << "";
    cout << endl;

    delete [] e;

    return 0;
}
// -------------------------

/*
% for n in $(seq 1 15) ; do  echo -n $n:; ./bin $n 0 | grep 'of equiv'| cut -d= -f2; done
1: 2
2: 3
3: 6
4: 10
5: 20
6: 36
7: 72
8: 136
9: 272
10: 528
11: 1056
12: 2080
13: 4160
14: 8256
15: 16512

unlabled: (shifted version of the same sequence)
% for n in $(seq 1 15) ; do  echo -n $n:; ./bin $n 1 | grep 'of equiv'| cut -d= -f2; done
1: 1
2: 2
3: 3
4: 6
5: 10
6: 20
7: 36
8: 72
9: 136
10: 272
11: 528
12: 1056
13: 2080
14: 4160
15: 8256
http://oeis.org/A005418
 Number of n-bead black-white reversible strings; also binary grids;
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/sort"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/sort/equivclass-bitstring-demo.cc"
/// make-target2: "1demo DSRC=demo/sort/equivclass-bitstring-demo.cc DEMOFLAGS=-DTIMING"
/// End:

