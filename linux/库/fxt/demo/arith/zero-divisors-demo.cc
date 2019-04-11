
#include "aux0/cayley-dickson-mult.h"


#include "ds/bitarray.h"

#include "fxtio.h"
#include "nextarg.h"
#include "bits/print-bin.h"
#include "fxttypes.h"

#include "jjassert.h"


//% Simple zero-divisors of sedenions (and higher Cayley-Dickson algebras).


//#define TIMING  // uncomment to disable printing

//#define USE_MAT  // count zero-divisors (else only relations are counted)
#ifdef USE_MAT
bitarray *B;  // matrix
#endif

bool ni_, nj_;
int *sym;
ulong ldn, n;
ulong ct;


bool
test_prod(ulong i0, ulong i1, ulong j0, ulong j1)
{
    int s00, s01, s10, s11;  // signs of products
    ulong p00, p01, p10, p11;  // positions (indices) of products

    // (i0+i1) * (j0+j1) ==
    // i0*j0 + i0*j1 + i1*j0 + i1*j1 ==
    // s00*p00 + s01*p01 + s10*p10 + s11*p11  where
    // s** is +-1 (sign) and p** the component number
    s00 = CD_sign_it(i0, j0, n);
//    if ( ni_ )  s00 = -s00;  // negate
    p00 = i0^j0;
    sym[p00] += s00;

    s01 = CD_sign_it(i0, j1, n);
    if ( nj_ )  s01 = -s01;  // negate
    p01 = i0^j1;
    sym[p01] += s01;

    s10 = CD_sign_it(i1, j0, n);
    if ( ni_ )  s10 = -s10;  // negate
    p10 = i1^j0;
    sym[p10] += s10;

    s11 = CD_sign_it(i1, j1, n);
    if ( ni_ != nj_ )  s11 = -s11;  // negate
    p11 = i1^j1;
    sym[p11] += s11;

    bool q = true;
    q &= (sym[p00]==0);
    q &= (sym[p01]==0);
    q &= (sym[p10]==0);
    q &= (sym[p11]==0);

    sym[p00]=0;  sym[p01]=0;  sym[p10]=0;  sym[p11]=0;

    return q;
}
// -------------------------


//#define XOR_SC  // use XOR-shortcut
//
void
test_all()
{
    for (ulong i0=0; i0<n; ++i0)
    {
        for (ulong i1=i0+1; i1<n; ++i1)
        {
#ifdef XOR_SC
            const ulong xi = i0 ^ i1;  // for XOR-shortcut
#endif
            for (ulong j0=i0+1; j0<n; ++j0)
            {
                for (ulong j1=j0+1; j1<n; ++j1)
                {
#ifdef XOR_SC
                    if ( xi != (j0^j1) )  continue;  // test: XOR-shortcut
#endif

                    bool q = test_prod(i0, i1, j0, j1);
                    ct += q;
#if 0  // changes output
                    // check that right zero-divisor is left zero-divisor:
                    swap2( ni_, nj_ );
                    jjassert( q==test_prod(j0, j1, i0, i1) );
                    swap2( ni_, nj_ );
#endif

#ifdef USE_MAT
                    if ( q )
                    {
                        B->set( n*i0 + i1 );
                        B->set( n*i1 + i0 );
                        B->set( n*j0 + j1 );
                        B->set( n*j1 + j0 );
                    }
#endif


#ifndef TIMING
                    if ( q )
                    {
                        const int wd = 2;  // width with printing
                        cout
                            << setw(4) << ct << ":  "
                            << "("
                            << setw(wd) << i0
                            << ( ni_ ? " - " : " + " )
                            << setw(wd) << i1
                            << " ) * ("
                            << setw(wd) << j0
                            << ( nj_ ? " - " : " + " )
                            << setw(wd) << j1
                            << " )";
                        //        const ulong xi = i0^i1,  xj=j0^j1;
                        //        print_bin("  ", i0, ldn); print_bin("  ", i1, ldn);
                        //        print_bin("  ", j0, ldn); print_bin("  ", j1, ldn);
                        //        print_bin("    ", xi, ldn); print_bin("  ", xj, ldn);
                        //        jjassert( xi == xj );

                        cout << endl;
                    }
//                    else
//                    {
//                        const ulong xi = i0^i1,  xj=j0^j1;
//                        jjassert( xi != xj );  // NOT true
//                    }

#endif  // TIMING

#if 0
                    if ( q ) jjassert( CD_zerodiv_q(i0, i1) );
#endif
                }
            }
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    ldn = 4;
    NXARG(ldn, "Zero-divisors of (2**ldn)-ions");
    n = 1UL << ldn;

    bool ni = false;
    NXARG(ni, "Whether to use differences in first factor");

    bool nj = false;
    NXARG(nj, "Whether to use differences in second factor");

    bool aq = false;
    NXARG(aq, "Whether to run for all ni=+-1, nj=+-1");

    sym = new int[n];
    for (ulong k=0; k<n; ++k)  sym[k] = 0;

    ct = 0;
#ifdef USE_MAT
    B = new bitarray( n*n );  B->clear_all();
#endif

    cout << endl;
    if ( aq )
    {
        ni_=0;  nj_=0;  test_all();
        ni_=0;  nj_=1;  test_all();
        ni_=1;  nj_=0;  test_all();
        ni_=1;  nj_=1;  test_all();
    }
    else
    {
        ni_ = ni;  nj_ = nj;  test_all();
    }

    cout << " ct=" << ct << endl;  // number of relations


#ifdef USE_MAT
    cout << endl;
    ulong ct2 = 0;
    for (ulong i0=0; i0<n; ++i0)
    {
        for (ulong i1=0; i1<n; ++i1)
        {
            bool q = B->test(i0*n+i1);
            ct2 += q;
            cout << ( q ? '1' : '.' );
        }
        cout << endl;
    }
    cout << " ct2=" << ct2 << endl;  // number of zero-divisors
    delete B;
#endif

    delete [] sym;

    return 0;
}
// -------------------------

/*

 n =   3,  4,   5,    6,    7,     8,      9
ct =   0, 42,  630,  6510, 58590, 496062,
ct/42= 0,  1,   15,   155,  1395,  11811,
// == OEIS sequence A006096, Gaussian binomial coefficient [ n,3 ] for q=2.

 n    = 3,  4,  5,   6,    7,     8,      9
ct2   = 0, 84, 588, 3036, 13884, 59772,
ct2/2 = 0, 42, 294, 1518,  6942, 29886,
ct2/3 = 0, 28, 196, 1012,  4628, 19924,
ct2/4 = 0, 21, 147,  759,  3471, 14943,
ct2/6 = 0, 14,  98,  506,  2314,  9962,
ct2/12= 0,  7,  49,  253,  1157,  4981,

ct2*2 = 0, 168, 1176, 6072, 27768, 119544,

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/arith"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/arith/zero-divisors-demo.cc"
/// make-target2: "1demo DSRC=demo/arith/zero-divisors-demo.cc DEMOFLAGS=-DTIMING"
/// End:

