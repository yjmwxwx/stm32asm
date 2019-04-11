
// demo-is-self-contained

#include "nextarg.h"
#include "perm/revbinpermute.h"  // revbin_permute()
#include "aux0/swap.h"  // swap2()
#include "bits/print-bin.h"  // print_bin()

#include "fxttypes.h"
#include "jjassert.h"
#include "fxtio.h"

//% Recursive revbin-permutation routine.
// Based on code by Udayan Kale <udayan (AT) pdaelegance (DOT) com>


//#define TIMING  // uncomment to disable printing

template <typename Type>
void bitrev(Type* p, ulong i, ulong l, ulong r, ulong k)
{
    ulong m = (l+r)>>1;
    if ( m>i )  swap2(p[m], p[i]);
    else return;
    bitrev(p, i+k, l, m, k<<1);
    bitrev(p, i+2*k,  m, r, k<<1);
}
// -------------------------


void bitrev_p(ulong i, ulong l, ulong r, ulong k, ulong ind=0)
{
    ulong m = (l+r)>>1;
    if ( m<=i )  return;

    print_bin("  ", m, 8);
    for (ulong j=0; j<ind; ++j)  cout << "    ";
    cout << "  i=" << i << "  m=" << m;  // << "  l=" << l << "  r=" << r << "  k=" << k;

//    if ( m>i )  cout << "  SWAP";  // swap2(p[m], p[i]);
    cout << endl;

//    if ( m<=i )  return;
//    if ( m-l <= 1 )  return;

    bitrev_p(i+k, l, m, k<<1, ind+1);
    bitrev_p(i+2*k,  m, r, k<<1, ind+1);
}
// -------------------------

template <typename Type>
inline bool is_seq(const Type *dst, ulong n, Type start=0, Type step=1)
// Check whether array elements are the sequence
//   start, start+step, start+2*step, ...
// (as filled in by set_seq(dst, n, start, step)
{
    for (ulong k=0;  k<n;  ++k, start += step)
        if ( dst[k] != start )  return false;
    return true;
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong ldn = 6;
    NXARG(ldn, "log_2(n) where n is the length of the array");
    ulong n = 1UL << ldn;
#ifdef TIMING
    ulong kk = 1024;
    NXARG(kk, "Number of times to permute");
    bool q = 0;
    NXARG(q, "0==>FXT's revbin_permute(),  1==>recursive routine()");
#endif

    double* f = new double[n];
    for (ulong k=0; k<n; ++k)  f[k] = (double)k;

#ifndef TIMING
    bitrev_p(1, 0, n, 1);  // print call graph
    for (ulong k=0; k<n; ++k)  f[k] = (double)k;
    revbin_permute(f, n);
    bitrev(f, 1, 0, n, 1);
    jjassert( is_seq(f, n) );
#else
    if ( q )  for (ulong k=0; k<kk; ++k)  bitrev(f, 1, 0, n, 1);
    else      for (ulong k=0; k<kk; ++k)  revbin_permute(f, n);
#endif

    delete [] f;
    return 0;
}
// -------------------------

//./bin 20 10 0  0.87s user 0.01s system 100% cpu 0.876 total  // revbin_permute()
//./bin 20 10 1  1.38s user 0.01s system 99% cpu 1.402 total  // bitrev()

//./bin 8 1000000 0  0.86s user 0.00s system 99% cpu 0.866 total  // revbin_permute()
//./bin 8 1000000 1  2.56s user 0.00s system 99% cpu 2.562 total  // bitrev()

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/revbin-perm-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/revbin-perm-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

