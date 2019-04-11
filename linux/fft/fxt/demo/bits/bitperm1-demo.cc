
// demo-is-self-contained

#include "bits/bittest.h"  // swap()
#include "aux1/copy.h"  // swap()

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"


//% Certain permutations controlled by a binary word.


void perm1(uchar *a, ulong ldn, const uchar *x)
// Permute a[] according to the 'control word' x[].
// The length of a[] must be 2**ldn.
{
    ulong n = 1L<<ldn;
    for (ulong s=n/2; s>0; s/=2)
    {
        cout << "  " << setw(2) << s << ":  ";
        for (ulong k=0; k<n; k+=s+s)
        {
            cout << setw(3) << k+s-1;
            if ( x[k+s-1]!='0' )
            {
                cout << "x";
                // swap regions [a+k,...,a+k+s-1], [a+k+s,...,a+k+2*s-1]:
                swap(a+k, a+k+s, s);
            }
            else  cout << " ";
        }
        cout << endl;
    }
}
// -------------------------


void inv_perm1(uchar *a, ulong ldn, const uchar *x)
{
    ulong n = 1L<<ldn;
    for (ulong s=1; s<n; s+=s)
    {
        cout << "  " << setw(2) << s << ":  ";
        for (ulong k=0; k<n; k+=s+s)
        {
            cout << setw(3) << k+s-1;
            if ( x[k+s-1]!='0' )
            {
                cout << "x";
                swap(a+k, a+k+s, s);
            }
            else  cout << " ";
        }
        cout << endl;
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    uchar ca[] = { "0123456789ABCDEF" };
    uchar *a = new uchar[17];
    acopy(ca, a, 17);
//    ulong xu = 0xFFFF;  // reverse
//    ulong xu = 0x5555;  // swap pairs
    ulong xu = 0x4444 ^ 0x2020 ^ 0x0800;  // Gray permutation

    NXARG(xu, "Word controlling the permutation");
    cout << "xu = 0x" << hex << xu << dec << endl;
    uchar *x = new uchar[17];
    for (ulong k=0; k<16; ++k)  x[k] = (uchar)('0' + test_bit01(xu, k));
    x[16] = 0;

    cout << "a=" << a << endl;
    cout << "x=" << x << endl;
    perm1(a, 4, x);
    cout << "a=" << a << endl;

//    inv_perm1(a, 4, x);
//    cout << "a=" << a << endl;

    cout << endl;

    delete [] a;
    delete [] x;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitperm1-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitperm1-demo.cc DEMOFLAGS=-DTIMING"
/// End:

