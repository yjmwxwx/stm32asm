
#include "chirpzt/chirpzt.h"  // fft_arblen()

#include "fft-all.h"  // slow_ft()

#include "aux1/copy.h"
#include "aux1/arith1.h"

#include "aux0/randf.h"  // rand()

#include "nextarg.h"
#include "fxttypes.h"  // ulong
#include "fxtio.h"
#include "jjassert.h"


//% Arbitrary length FFT

// Output dependent on FPU

double
chop(double x, double eps=1e-9)
{
    if ( fabs(x) < eps )  x = 0;
    return  x;
}
// -------------------------

Complex
chop(Complex x, double eps=1e-9)
{
    return  Complex(chop(x.real(), eps), chop(x.imag(), eps));
}
// -------------------------

void
printit(const char *bla, Complex *f, ulong n)
{
    cout << bla << endl;
    for (ulong k=0; k<n; ++k)
    {
        double r = chop(f[k].real()), i=chop(f[k].imag());
        cout << setw(4) << k << ": ";
        cout << setw(10) << r << "  ";
        cout << setw(10) << i << "";
        cout << endl;
    }
}
// -------------------------

template <typename Type>
inline Type sqr_diff(const Type *f, const Type *g, ulong n)
// return \sum_k { (f[k]-g[k])^2 }
{
    Type s(0);
    while ( n-- ) { Type d = f[n] - g[n];  s += d * d; }
    return  s;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 13;
    NXARG(n, "Length of FFT");

    long d = 1;
    NXARG(d, "Create delta at position d (real part). If d<0 use 'random' data");

    int is = +1;
    NXARG(is, "Sign of the transform.");
    jjassert( (is==+1) || (is==-1) );


    ulong pq = 1;
    NXARG(pq, "Verbosity.");

    const double eps = 1e-12;

    Complex *f = new Complex[n];
    Complex *s = new Complex[n];
    Complex *g = new Complex[n];

    null(f, n);
    if ( d>=0 )  f[d] = Complex(1.0, 0.0);  // delta peak
    else  // "random"
    {
        rseed( (uint)-d );
        for (ulong k=0; k<n; ++k)  rnd01( (double *)(f+k), 2);
    }

    acopy(f, g, n);  // store original
    acopy(f, s, n);  // for slow_ft()

    if ( pq>=1 )  printit("---- f[]=", f, n);

    fft_arblen(f, n, is);
    slow_ft(s, n, is);

    if ( pq>=1 )  printit("---- FFT(f[])=", f, n);

    Complex sdsf = sqr_diff(s, f, n);
    sdsf = chop(sdsf, eps);
    if ( abs(sdsf) >= eps )
    {
        printit("---- s[]=", s, n);
        cout << " sqr_diff=" <<  sdsf << endl;
        jjassert( abs(sdsf) < eps );
    }


    fft_arblen(f, n, -is);
    multiply_val(f, n, Complex(1.0/(double)n, 0.0));
    if ( pq>=2 )  printit("---- IFFT(FFT(f[]))=", f, n);

//    subtract(g, n, f);
//    printit("---- diff[]=", g, n);
    Complex sdgf = sqr_diff(g, f, n);
    cout << " sqr_diff=" <<  sdgf << endl;
    sdgf = chop(sdgf, eps);
    jjassert( abs(sdgf)<eps );

    delete [] f;
    delete [] s;
    delete [] g;

    return 0;
}
// -------------------------


/*
 make 1demo DSRC=demo/fft-arblen-demo.cc

// TEST all values and is = +1:
 for n in $(seq 1 100); do echo $n":  "; ./bin $n -1 +1 0 || break ; done
// test all values and is = -1:
 for n in $(seq 1 100); do echo $n":  "; ./bin $n -1 -1 0 || break ; done

 // test odd values and is=+1:
 for n in $(seq 1 2 100); do echo $n":  "; ./bin $n -1 +1 0 || break ; done
 // test odd values and is=-1:
 for n in $(seq 1 2 100); do echo $n":  "; ./bin $n -1 -1 0 || break ; done

 // test even values and is=+1:
 for n in $(seq 2 2 100); do echo $n":  "; ./bin $n -1 +1 0 || break ; done
 // test even values and is=-1:
 for n in $(seq 2 2 100); do echo $n":  "; ./bin $n -1 -1 0 || break ; done

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/fft"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/fft/fft-arblen-demo.cc"
/// make-target2: "1demo DSRC=demo/fft/fft-arblen-demo.cc DEMOFLAGS=-DTIMING"
/// End:

