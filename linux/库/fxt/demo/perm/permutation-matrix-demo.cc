
#include "perm-all.h"

#include "aux1/copy.h"

#include "bits/bitlex.h"
#include "bits/graycode.h"
#include "bits/bittransforms.h"

#include "fxtalloca.h"
#include "fxtio.h"
#include "fxttypes.h"  // ulong

#include "nextarg.h"  // NXARG()


//% Matrices corresponding to permutations.


#define  TT(X)  { {cout << " " << #X << endl;}  X; }

template <typename Type>
inline ulong test_delta(const Type *f, ulong n, Type *vp=0)
// If f[] is a delta sequence then
//   return index 0<=i<n where f[i]!=0
// else
//  return ~0
//
// if vp!=0 then
//   set vp to the value of the delta pulse
//   set vp to zero is sequence is no delta sequence
{
    ulong k = 0;
    ulong i = ~0UL;
    // search first element != 0:
    while ( k<n )  { if ( 0!=f[k] ) break;  ++k; }
    // check whether there is another one:
    if ( k<n )
    {
        i = k;
        ++k;
        while ( k<n )
        {
            if ( 0!=f[k] ) { i = ~0UL; break; }
            ++k;
        }
    }
    if ( (i!=~0UL) && (0!=vp) )  *vp = f[i];
    // zero if sequence is not a delta seq.

    return  i;
}
// -------------------------


template <typename Type>
void prsgn(Type *f, ulong n, ulong x)
{
    cout << "  ";
    cout << setw(3) << x << ":";
    cout << " [ ";
    for (ulong k=0; k<n; ++k)
    {
        double v = (double)f[k];
//        cout << setw(2) << (v);  // debug
        cout << (v>0 ? '+' : (v<0 ? '-' : ' ') );
        if ( k<n-1 ) cout << ' ';
    }
    cout << " ]";
}
// -------------------------


void
showmat(const ulong *f, ulong n)
{
    ALLOCA(ulong, g, n);
    for (ulong x=0; x<n; ++x)
    {
        null(g, n);
        g[f[x]] = 1;
        prsgn(g, n, x);
        ulong d;  ulong i = test_delta(g, n, &d);
        if ( i<n )  cout << "  [" << setw(2) << i << "] ";
//        cout << (d > 0 ? '+' : '-');
        cout << endl;
    }
    cout << endl;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong ldn = 5;
    NXARG(ldn, "log_2(number of elements)");
    ulong  n = (1<<ldn);
    bool iq = false;
    NXARG(iq, "Whether to show inverse matrix, too");

    ulong *f = new ulong[n];

    cout << "Operations:" << endl;
    set_seq( f, n );

    // Playground: apply one or more permutations
    TT( gray_permute(f, n) );  // default
//    TT( apply_permutation(gray_code, f, n) );

//    TT( apply_inverse_permutation(blue_code, f, n) );
//    TT( apply_inverse_permutation(negidx2lexrev, f, n) );
//    TT( apply_inverse_permutation(blue_code, f, n) );
//    TT( apply_inverse_permutation(gray_code, f, n) );
//    TT( apply_inverse_permutation(lexrev2negidx, f, n) );

    showmat(f, n);

    if ( iq )
    {
        cout << "Inverse:" << endl;
        make_inverse(f, n);
        showmat(f, n);
    }

    delete [] f;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/permutation-matrix-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/permutation-matrix-demo.cc DEMOFLAGS=-DTIMING"
/// End:

