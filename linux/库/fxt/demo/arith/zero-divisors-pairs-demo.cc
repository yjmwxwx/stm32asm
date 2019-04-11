
#include "aux0/cayley-dickson-mult.h"

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"

#include "jjassert.h"


//% Simple zero-divisors of sedenions (and higher Cayley-Dickson algebras):
//% list all simple zero-products with same left factor in one line.


ulong lrq_;
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

#if 0
    cout << "  i0=" << i0 << "  i1=" << i1 << "  j0=" << j0 << "  j1=" << j1;
    cout << "  p00=" << p00 << "  p01=" << p01 << "  p10=" << p10 << "  p11=" << p11 << endl;
#endif

    return q;
}
// -------------------------


void
test_all()
{
    const int wd = 2;  // width with printing
    for (ulong i0=0; i0<n; ++i0)
    {
        for (ulong i1=i0+1; i1<n; ++i1)
        {

            if ( CD_zerodiv_q(i0, i1) )
            {
                ct += 1;

                cout << setw(4) << ct << ":  "
                     << "("
                     << setw(wd) << i0
                     << ( ni_ ? " - " : " + " )
                     << setw(wd) << i1
                     << " ):  ";


                for (ulong j0=0; j0<n; ++j0)
                {
                    for (ulong j1=j0+1; j1<n; ++j1)
                    {
                        // second factor from right:
                        if ( lrq_ & 1 )
                        {
                            if ( test_prod(i0, i1, j0, j1) )
                            {
                                cout << "  *("
                                     << setw(wd) << j0
                                     << ( nj_ ? " - " : " + " )
                                     << setw(wd) << j1
                                     << " ),";
                            }
                        }

                        // second factor from left:
                        if ( lrq_ & 2 )
                        {
                            if ( test_prod(j0, j1, i0, i1) )
                            {
                                cout << "  ("
                                     << setw(wd) << j0
                                     << ( nj_ ? " - " : " + " )
                                     << setw(wd) << j1
                                     << " )*,";
                            }
                        }
                    }
                }
                cout << endl;
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

    lrq_ = 1;
    NXARG(lrq_, "Side of second factor: 1==>right, 2==>left, 3==>both ");

    sym = new int[n];
    for (ulong k=0; k<n; ++k)  sym[k] = 0;

    ct = 0;

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



    delete [] sym;

    return 0;
}
// -------------------------

/*
./bin 5 . . 3 1 | tr '-' '+' | tr -d '*' | cut -d : -f2- | sort -n | uniq \
  > zero-divisors-no-signs-32-ions.txt
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/arith"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/arith/zero-divisors-pairs-demo.cc"
/// make-target2: "1demo DSRC=demo/arith/zero-divisors-pairs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

