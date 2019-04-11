
#include "mod/primes.h"
#include "mod/modarith.h"

#include "ds/bitarray.h"

#include "mod/factor.h"
#include "nextarg.h"
#include "fxttypes.h"  // ulong


//% Find moduli where all quadratic (or higher) residues are non-prime.

// OEIS sequence A065428, Numbers n such that all x^2 mod n are nonprimes.
// 1, 2, 3, 4, 5, 8, 12, 15, 16, 24, 28, 40, 48, 56, 60, 72, 88, 112,
// 120, 168, 232, 240, 280, 312, 408, 520, 760, 840, 1320, 1848

int
main(int argc, char **argv)
{
    ulong n = 2000;
    NXARG(n, "Search limit for moduli");
    bitarray *B = make_oddprime_bitarray(n);
    ulong e = 2;
    NXARG(e, "Exponent (2==>squares, 3==>cubes, ...)");

    ulong ct = 0;
    for ( umod_t m=2; m<n; ++m)
    {
        for ( umod_t x=0; x<m; ++x )
        {
            umod_t z = pow_mod(x, e, m);
            if ( is_small_prime( z, B ) )  goto next;
        }

        {
            factorization fm(m);
            ++ct;
            cout << m;
            cout << " == " << fm;
            cout << endl;
        }
    next: ;
    }

    cout << endl;
    cout << " #=" << ct << endl;

    delete B;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/mod"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/mod/mod-residues-demo.cc"
/// make-target2: "1demo DSRC=demo/mod/mod-residues-demo.cc DEMOFLAGS=-DTIMING"
/// End:

