
#include "bits/blue-fixed-points.h"
#include "bits/bittransforms.h"

#include "bits/print-bin.h"

//#include "bits/revbin.h"
//#include "bits/bithigh.h"

#include "jjassert.h"
#include "nextarg.h"
#include "fxttypes.h"

#include "fxtio.h"


//% Fixed points of the blue code.


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of bits");
    ulong N = 1UL<<n;
    cout << endl;

    for (ulong k=0; k<N; ++k)
    {
        ulong f = blue_fixed_point(k);
        ulong s = blue_fixed_point_idx(f);

        cout << setw(4) << k;
        print_bin(" = ", k, n+1);
        cout << " :  ";
        print_bin("  ", f, 2*n);
        cout << " = ";
        cout << setw(6) << f;

        jjassert( f==blue_code(f) );
        jjassert( s==k );

        // a self-reciprocal word:
//        print_bin("     ", blue_code(revbin(f,highest_one_idx(f)+1)), 2*n);

//        ulong z = (f<<1) ^ (f<<2);
//        jjassert( z==blue_code(z) );
//        z ^= 1;
//        jjassert( z==blue_code(z) );

        cout << endl;
    }

    cout << endl;

    return 0;
}
// -------------------------

// OEIS sequence A118666:
// echo  $(./bin 6 | grep '^ ' | cut -d= -f 3 | sort -n) | sed 's/ /,/g'


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bittransforms-blue-fp-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bittransforms-blue-fp-demo.cc DEMOFLAGS=-DTIMING"
/// End:

