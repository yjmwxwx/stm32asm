
#include "mod/primes.h"
// demo-include "mod/rabinmiller.cc"

#include "nextarg.h"
#include "fxtio.h"
#include "fxtalloca.h"
#include "fxttypes.h"  // ulong

//% Find composites that are strong pseudoprimes to more than one base.

int
main(int argc, char **argv)
{
    ulong nmax = 20000;
    NXARG(nmax, "Maximum n to test");
    ulong na = 2;
    NXARG(na, "Select n that are strong pseudo-primes to >=na bases");
    ulong maxa = 17;
    NXARG(maxa, "Maximum base a tested");
    ulong ppq = 1;
    NXARG(ppq, "Whether to omit values: 0==>none, 1==>powers, 2==>non-primes");
    ulong iev = 1;
    NXARG(iev, "Whether to include even n: 0==>no 1==>yes");
    iev = ( iev==0 ? 2 : 1 );

    ALLOCA(ulong, aa, maxa+3);  // bases to be tested
    for (ulong x=0; x<=maxa+1; ++x)  aa[x] = 0;
    for (ulong x=0, a=2; a<=maxa; ++a)
    {
        if ( ppq && is_small_perfpow(a) )  continue;
        if ( ppq && (0==is_small_prime(a)) )  continue;
        aa[x++] = a;
    }


    cout << "Bases tested: ";
    for (ulong x=0; aa[x]; ++x)  cout << " " << aa[x];
    cout << endl;

    ALLOCA(ulong, qq, maxa+3);
    for (umod_t n=3; n<=nmax; n+=iev)
    {
        umod_t q;  uint t;
        n2qt(n, q, t);

        ulong a, x;
        ulong ct = 0;
        for (x=0; (a=aa[x]); ++x)
        {
            if ( a>n-2 )  break;
            qq[x] = is_strong_pseudo_prime(n, a, q, t);
            ct += qq[x];
        }

        if ( ct>=na )
        {
            // output only for composite numbers:
            bool pq;  // whether n is prime
            if ( ct < x )
            {
                // failed for at least one base ==> known composite
                pq = 0;
            }
            else
            {
                pq = rabin_miller(n, 20);
                // if pq==1 than n is (very likely) prime
            }

            if ( !pq )
            {
                cout << setw(8) << n << ": ";
                cout << " [" << ct << "]  ";
                for (ulong y=0; y<x; ++y)
                {
                    if ( qq[y] )  cout << setw(3) << aa[y];
                    else          cout << "   ";
                }
                cout << endl;
            }
        }
    }
    cout << endl;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/mod"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/mod/rabinmiller-demo.cc"
/// make-target2: "1demo DSRC=demo/mod/rabinmiller-demo.cc DEMOFLAGS=-DTIMING"
/// End:

