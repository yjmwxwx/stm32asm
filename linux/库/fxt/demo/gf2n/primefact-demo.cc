
#include "bpol/bitpol-irred.h"
#include "ds/bitarray.h"
#include "mod/primes.h"
#include "bits/bithigh.h"

#include "fxttypes.h"

#include "fxtio.h"

#include "nextarg.h"


//% Finding odd primes that are composite as polynomials over GF(2).
// Sequence A091209 of the OEIS

int
main(int argc, char **argv)
{
    ulong ldn = 8;
    NXARG(ldn, "Test numbers < 2**ldn");
    const ulong n = 1UL << ldn;

    bitarray *op = make_oddprime_bitarray(n);

    ulong rct = 0;  // count reducible polynomials
    ulong pct = 0;  // count primes
    for (ulong c=3; c<n; c+=2)
    {
        if ( 0==is_small_prime(c, op) )  continue;
        ++pct;

        ulong h = (highest_one(c) >> 1);
        if ( 0==bitpol_irreducible_q(c, h) )  // use != to get irreducibles
        {
            ++rct;
            cout << setw(4) << c << endl;
        }
    }
    cout << "Found " << rct << " composite primes "
         << " among the " << pct << " odd primes <= " << n
         << "   ;-) " << endl;
    cout << endl;

    delete op;

    return 0;
}
// -------------------------

// Found 0 composite primes  among the 0 odd primes <= 2   ;-)
// Found 0 composite primes  among the 1 odd primes <= 4   ;-)
// Found 1 composite primes  among the 3 odd primes <= 8   ;-)
// Found 1 composite primes  among the 5 odd primes <= 16   ;-)
// Found 4 composite primes  among the 10 odd primes <= 32   ;-)
// Found 6 composite primes  among the 17 odd primes <= 64   ;-)
// Found 14 composite primes  among the 30 odd primes <= 128   ;-)
// Found 27 composite primes  among the 53 odd primes <= 256   ;-)
// Found 61 composite primes  among the 96 odd primes <= 512   ;-)
// Found 109 composite primes  among the 171 odd primes <= 1024   ;-)
// Found 216 composite primes  among the 308 odd primes <= 2048   ;-)
// Found 406 composite primes  among the 563 odd primes <= 4096   ;-)
// Found 788 composite primes  among the 1027 odd primes <= 8192   ;-)
// Found 1494 composite primes  among the 1899 odd primes <= 16384   ;-)
// Found 2851 composite primes  among the 3511 odd primes <= 32768   ;-)
// Found 5386 composite primes  among the 6541 odd primes <= 65536   ;-)
// Found 10342 composite primes  among the 12250 odd primes <= 131072   ;-)
// Found 19605 composite primes  among the 22999 odd primes <= 262144   ;-)
// Found 37681 composite primes  among the 43389 odd primes <= 524288   ;-)
// Found 71799 composite primes  among the 82024 odd primes <= 1048576   ;-)
// Found 137839 composite primes  among the 155610 odd primes <= 2097152   ;-)
// Found 264010 composite primes  among the 295946 odd primes <= 4194304   ;-)
// Found 507574 composite primes  among the 564162 odd primes <= 8388608   ;-)

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/primefact-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/primefact-demo.cc DEMOFLAGS=-DTIMING"
/// End:

