
#include "haar-all.h"
#include "walsh-all.h"
#include "perm-all.h"

#include "aux0/sign.h"  // sign()
#include "aux1/copy.h"  // null()
//#include "aux1/delta.h"  // test_delta()

#include "fxtio.h"
#include "fxttypes.h"  // ulong

#include "nextarg.h"


//% Basis matrices of Walsh and Haar transforms.


#define  TT(x)  { if ( q ) { x; } else { cout << "    " << #x << endl;} }


template <typename Type>
void prsgn(Type *f, ulong n, ulong x, double eps=1e-7)
{
    cout << "  ";
    cout << setw(3) << x << ":";
    cout << " ";

    double s1 = sign( fabs(f[0]) > eps ? f[0] : 0);
    int seq = 0;
    cout << "[ ";
    for (ulong k=0; k<n; ++k)
    {
        double v = f[k];
        if ( fabs(v) < eps )  v = 0;
        double s2 = (v > 0 ? +1 : -1);
        if ( s1!=s2 )  seq++;
        s1 = s2;

        // Option: style of output:
        cout << (v>0 ? '*' : (v<0?' ':'0') );  // for Walsh (default)
//        cout << (v>0 ? '+' : (v<0?'-':' ') );  // for Haar
//        cout << (v ? '*' : ' ');  // for Reed-Muller and permutations
//        cout << f[k] << " ";

//        cout << setw(2) << (v);  // debug
//        if ( v==0 )  cout << "  "; else cout << setw(2) << v;  // debug
//        cout << (v>0 ? '*' : (v<0?'-':' ') );  // debug

        if ( k<n-1 ) cout << ' ';
    }
    cout << " ]";
    cout << " (" << setw(2) << seq << ")";  // sequency

//    Type z =  norm(f, n);
////    Type z =  0;  for (ulong k=0; k<n; ++k)  if ( f[k]>0.001 ) z+=1;
//    cout << " |" << setw(8) << z << "|";  // norm
}
// -------------------------

template <typename Type>
void haar_I(Type *f, ulong ldn)
{
    ulong n = 1UL<<ldn;
    for (ulong js=2; js<=n; js<<=1)
    {
        for (ulong j=0, t=js>>1;  j<n;  j+=js, t+=js)
        {
            Type x = f[j];
            Type y = f[t];
            f[j]  =  x + y;
            f[t]  = (x - y);
        }
    }
}
// -------------------------
template <typename Type>
void inverse_haar_I(Type *f, ulong ldn)
{
    ulong n = 1UL<<ldn;
    for (ulong js=n; js>=2; js>>=1)
    {
        for (ulong j=0, t=js>>1;  j<n;  j+=js, t+=js)
        {
            Type x = f[j];
            Type y = f[t];
            f[j]  =  x + y;
            f[t]  =  x - y;
        }
    }
}
// -------------------------

void
func(double *f, ulong ldn, bool q=true)
// The playground
// variable q is used by the TT() macro
{
    ulong n = 1UL << ldn;

    // default:
    TT( walsh_gray(f, ldn); ); TT( revbin_permute(f, n); ); TT( grs_negate(f, n); );

//    TT( walsh_wak(f, ldn); );

//    TT( haar_rev_nn(f, ldn); );
//    TT( inverse_haar_rev_nn(f, ldn); );
//    TT( inverse_transposed_haar_rev_nn(f, ldn); );
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong ldn = 5;
    NXARG(ldn, "Base-2 logarithm of length");
    ulong  n = (1<<ldn);

    double *f = new double[n];  null(f, n);

    cout << "Operations:" << endl;
    func(f, ldn, false);

    for (ulong x=0; x<n; ++x)
    {
//        make_delta(f, n, x);
        null(f, n);
        f[x] = 1;

        func(f, ldn);

        prsgn(f, n, x, 0);

//        double d;
//        ulong i = test_delta(f, n, &d);
//        if ( i<n )  cout << " d[" << setw(2) << i << "] = " << d;

        cout << endl;
    }

    delete [] f;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/fft"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/fft/walsh-basis-demo.cc"
/// make-target2: "1demo DSRC=demo/fft/walsh-basis-demo.cc DEMOFLAGS=-DTIMING"
/// End:

