
#include "perm/printcycles.h"

#include "perm/perminvert.h"  // make_inverse()

#include "comb/comb-print.h"

#include "perm-all.h"  // all permutation stuff

#include "aux1/copy.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% Decomposition of a permutation into cycles.
//% Print cycles and code for the permutation.


// Print And Doit:
#define  PAD( x )  { cout << "Using: " << #x << endl;  x; }

int
main(int argc, char **argv)
{
    ulong ldn = 3;
    NXARG(ldn, "Number of elements is 2**ldn");
    ulong n = 1UL << ldn;
    cout << "  n=" << n << endl;

    bool pcq = 1;
    NXARG(pcq, "Whether to print code");

    ulong *p = new ulong[n];  // the permutation
    ulong *y = new ulong[n];  // effect of permutation (i.e. the inverse of p[])
    for (ulong k=0; k<n; ++k)  y[k] = k;


//    cout << " Apply some permutation:" << endl;
    // choose one or more ...:
//    PAD( revbin_permute(y, n) );
//    PAD( reverse(y, n) );
//    PAD( gray_permute(y, n) );
//    PAD( apply_permutation(gray_code, y, n) );  // same as: gray_permute(y, n)
//    PAD( inverse_gray_permute(y, n) );
//    PAD( apply_permutation(negidx2lexrev, y, n) );
//    PAD( apply_permutation(lexrev2negidx, y, n) );
//    PAD( apply_permutation(blue_code, y, n) );
//    PAD( haar_permute(y, n) );
    PAD( zip(y, n) );  // default
//    PAD( unzip(y, n) );
//    PAD( rotate_left1(y, n) );
//    PAD( rotate_right1(y, n) );

////    ulong zz[] = {4,3,2,0,1,9,8,5,6,7};
//    ulong zz[] = {3,4,2,1,0,7,8,9,6,5};  // need inv.
//    n=sizeof(zz)/sizeof(ulong);  acopy(zz,y,n);

    make_inverse(y, p, n);  // Note

    cout << endl;
    print_perm("Permutation:\n", p, n);
    cout << endl;
    print_perm("Inverse:\n", y, n);
    cout << endl;
    cout << endl;

    cout << "Cycles:" << endl;
    print_cycles_len(p, n);
    cout << endl;

    if ( pcq )
    {
        cout << "Code:" << endl;
        print_inv_perm_code("foo_perm", y, n);
    }

    delete [] p;
    delete [] y;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/cycles-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/cycles-demo.cc DEMOFLAGS=-DTIMING"
/// End:

