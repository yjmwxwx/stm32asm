
#include "ds/bitarray.h"
#include "mod/isqrt.h"

#include "fxttypes.h"

#include "nextarg.h"

//% Sieve of Eratosthenes.

void
erastothenes(bitarray &B)
{
    B.set_all();
    B.clear(0);
    B.clear(1);
    ulong n = B.size();
    ulong k = 0;
    while ( (k=B.next_set(k+1)) < n )
    {
        for (ulong j=2, i=j*k;  i<n;  ++j, i=j*k)  B.clear(i);
    }
}
// -------------------------

void
erastothenes_opt(bitarray &B)
{
    B.set_all();
    B.clear(0);
    B.clear(1);
    ulong n = B.size();
    for (ulong k=4; k<n; k+=2)  B.clear(k);
    ulong r = isqrt(n);
    ulong k = 0;
    while ( (k=B.next_set(k+1)) < n )
    {
        if ( k > r )  break;
        for (ulong j=k*k; j<n; j+=k*2)  B.clear(j);
    }
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 100;
    NXARG(n, "Upper limit for prime search");

    ulong q = 1;
    NXARG(q, "1 ==> use optimized sieve, else non-optimized.");


    bitarray B(n);
    if ( 0==q ) erastothenes(B);
    else        erastothenes_opt(B);

    ulong k = 0;
    ulong ct = 0;
    while ( (k=B.next_set(k+1)) < n )
    {
        ++ct;
        cout << " " << k;
    }
    cout << endl;

    cout << "Found " << ct << " primes below " << n << "." << endl;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/mod"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/mod/eratosthenes-demo.cc"
/// make-target2: "1demo DSRC=demo/mod/eratosthenes-demo.cc DEMOFLAGS=-DTIMING"
/// End:

