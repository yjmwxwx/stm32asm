
#include "comb/binary-debruijn.h"  // class binary_debruijn
// demo-include "comb/binary-necklace.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"

#include "nextarg.h"

//% Generating binary De Bruijn sequences.

int
main(int argc, char **argv)
{
    const ulong m = 2;
    ulong n = 6;
    NXARG(n, "length = m**n")

    binary_debruijn S(n);
    ulong ns = 1UL<<n;
    cout << "\n n = " << n
         << "  length = " << ns
         << ":" << endl;

    ulong i = S.first_string();
    do
    {
        cout << " ";
        for (ulong u=1; u<=i; ++u)  cout << S.a_[u];  // note: one-based array
        i = S.next_string();
    }
    while ( i );
    cout << endl;

    i = S.first_digit();
    ulong ct = 0;
    do
    {
        ++ct;
        cout << i;
        i = S.next_digit();
    }
    while ( i!=m );
    cout << endl;
    cout << " ct=" << ct << endl;
    jjassert( ct == ns );

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/binary-debruijn-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/binary-debruijn-demo.cc DEMOFLAGS=-DTIMING"
/// End:

