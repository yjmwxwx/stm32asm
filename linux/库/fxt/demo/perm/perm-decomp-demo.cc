
// demo-is-self-contained

#include "perm-all.h"

#include "aux1/copy.h"  // swap()
#include "fxtio.h"
#include "fxtalloca.h"
#include "aux0/swap.h"
#include "fxttypes.h"  // ulong

#include "nextarg.h"


//% Permutations as Kronecker products of simpler permutations.
//% Nasty but useful code.


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <typename Type1, typename Type2>
inline bool compare(const Type1 *f, const Type2 *g, ulong n)
// Return whether both arrays are identical.
{
    for (ulong k=0; k<n; ++k)  if ( f[k] != g[k] )  return false;
    return true;
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

static void
identity(ulong *, ulong)
// Apply identity permutation (used for permutation recognition).
{ return; }
// -------------------------

static void
hswap(ulong *f, ulong n)
// Swap halves.
{ swap(f, f+n/2, n/2); }
// -------------------------

static void
pswap(ulong *f, ulong n)
// Swap pairs.
{ for (ulong k=0; k<n; k+=2)  swap2(f[k], f[k+1]); }
// -------------------------

static ulong quart[4];
static bool
qtest(const ulong *f, ulong n)
// Test whether permutation is a permutation of the quarters.
{
    ulong n4 = n/4;
    for (ulong k=0; k<n; k+=n4)
    {
        if ( 0!=(f[k] % n4) )    return false;
    }

    for (ulong k=0; k<n; k+=n4)
    {
        if ( 0==is_seq(f+k, n4, f[k], 1UL ) )  return false;
    }

    for (ulong k=0; k<4; ++k)  quart[k] = f[k*n4] / n4;

    return true;
}
// -------------------------

typedef  void (*PF)(ulong *, ulong);

static void
perm_r2(const ulong *f, ulong n,
        const char *str,  PF p1,
        const char *pstr, PF pp,
        ulong *g)
{
    set_seq(g, n);
    pp(g, n); p1(g, n);
    if ( compare(f, g, n) )
    { cout << " = " << str << " .@ " << pstr << endl; }

    set_seq(g, n);
    p1(g, n);  pp(g, n);
    if ( compare(f, g, n) )
    { cout << " = " << pstr << " @. " << str << endl; }

    set_seq(g, n);
    pp(g, n);   p1(g, n);  pp(g, n);
    if ( compare(f, g, n) )
    { cout << " = " <<  pstr << " @. " << str << " .@ " << pstr << endl; }
}
// -------------------------

static void
perm_r1(const ulong *f, ulong n,
        const char *str,  PF p1)
{
    ALLOCA(ulong, g, n);
    set_seq(g, n);
    p1(g, n);
    if ( compare(f, g, n) )
    {
        cout << " == " << str << endl;
        return;
    }

    perm_r2(f, n, str, p1, "r", reverse, g );
    perm_r2(f, n, str, p1, "h", hswap, g );
    perm_r2(f, n, str, p1, "x1", pswap, g );
    perm_r2(f, n, str, p1, "R", revbin_permute, g );
    perm_r2(f, n, str, p1, "zip", zip, g );
    perm_r2(f, n, str, p1, "unzip", unzip, g );
    perm_r2(f, n, str, p1, "zip_rev", zip_rev, g );
    perm_r2(f, n, str, p1, "unzip_rev", unzip_rev, g );

//    perm_r2(f, n, str, p1, str, p1, g );
}
// -------------------------


void
perm_recognize(const ulong *f, ulong n)
// Slightly simple minded routine to analyze permutations.
// Still OK for many purposes.
{
    if ( is_identity(f, n) )
    {
        cout << " == identity." << endl;
        return;
    }

    if ( qtest(f, n) )
    {
        cout << " == quart[";
        for (ulong k=0; k<4; ++k)  cout << quart[k];
        cout << "]" << endl;
        return;
    }

#define  QQ(x)  { perm_r1(f, n, #x, x); }

    QQ( identity );

    QQ( reverse );
    QQ( reverse_0 );

    QQ( gray_permute );
    QQ( inverse_gray_permute );
    QQ( gray_rev_permute );
    QQ( inverse_gray_rev_permute );
//    QQ( green_permute );
//    QQ( inverse_green_permute );
//    QQ( green_rev_permute );
//    QQ( inverse_green_rev_permute );

    QQ( revbin_permute );
    QQ( haar_permute );
    QQ( inverse_haar_permute );

    QQ( zip );
    QQ( unzip );
    QQ( zip_rev );
    QQ( unzip_rev );

//    QQ( grs_negate );
#undef QQ
}
// -------------------------



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static int q = 1;
#define  TT(x)  { if ( q ) { cout << " " << #x << endl;}  x; }
#define  P1(x)  { if ( q ) { cout << " [1]: " << #x << endl;}  x; }
#define  P2(x)  { if ( q ) { cout << " [2]: " << #x << endl;}  x; }


void p1_func(ulong *f, ulong n)
{
    ulong nh = n/2;
    ulong n4 = n/4;

//    P1( zip(f, n) );  // revbin_permute
//    P1( unzip(f, n) );  // ???
//    P1( revbin_permute(f, n) );  // ???
//    P1( gray_permute(f, n) );  // ???
//    P1( haar_permute(f, n) );  // ???
//    P1( inverse_haar_permute(f, n) );  // ???

//    P1( swap(f, f+nh, nh) );  // reverse

    P1( swap(f+nh, f+nh+n4, n4) );  // gray_permute
//    P1( swap(f, f+n4, n4) );  // rev @ gray_rev_permute == rev @ gray_permute @ rev
//    P1( swap(f+n4, f+nh, n4) );  // unzip
//    P2( swap(f, f+nh+n4, n4) );  // unzip @ rev

//    P1( swap(f+n4, f+nh, n4) );  P1( swap(f+nh, f+nh+n4, n4) );  // unzip_rev
//    P1( swap(f, f+n4, n4) );  P1( swap(f, f+nh, n4) );  // rev @ unzip_rev @ rev

//    P2( swap(f, f+n4, n4) );  P2( swap(f, f+nh, nh) );  // gray_rev_permute

//    P1( swap(f, f+nh, n4) );  // inverse_green_rev_permute @ rev
    // == rev @ inverse_green_permute @ rev

//    P1( swap(f+n4, f+nh+n4, n4) );  // inverse_green_permute
    // == rev @ inverse_green_rev_permute
    // == hswap @ inverse_green_permute(g, n) @ hswap

//    P1( reverse(f+nh, nh) );  // inverse_gray_permute
    // == rev @ inverse_gray_rev_permute
//    P1( reverse(f, nh) );  // rev @ inverse_gray_permute @ rev
    // == inverse_gray_rev_permute @ rev

//    P1( negate(f+nh+n4, n4) );  //  grs_negate
//    P1( negate(f+nh, n4) );  //  ???

    nh = n4 = 0;  // avoid warning
    q = 0;
}
// -------------------------

void perm1(ulong *f, ulong n)
// From shorter to longer sub-arrays.
{
    for (ulong k=2; k<=n; k*=2)
    {
        for (ulong j=0; j<n; j+=k)  p1_func(f+j, k);
    }
}
// -------------------------


void p2_func(ulong *f, ulong n)
{
    ulong nh = n/2;
    ulong n4 = n/4;

//    P2( zip(f, n) );  // ???
//    P2( unzip(f, n) );  // revbin_permute

//    P2( revbin_permute(f, n) );  // ???

//    P2( inverse_gray_rev_permute(f, n) );  // ???
//    P2( gray_permute(f, n) );  // ???
//    P2( reverse(f, n) );  // xor_permute(g, n, x) @ rev
//    P2( xor_permute(f, n, 1) );  // identity
//    P2( xor_permute(f, n, nh) );  // identity @ rev

//    P2( swap(f, f+nh, nh) );  // reverse

    P2( swap(f+nh, f+nh+n4, n4) );  // inverse_gray_permute
//    P2( swap(f+n4, f+nh, n4) );  // zip
//    P2( swap(f, f+nh+n4, n4) );  // zip @ rev

//    P2( swap(f, f+n4, n4) );  // inverse_gray_rev_permute @ rev
    // == rev @ inverse_gray_permute @ rev

//    P2( swap(f, f+nh, nh) );  P2( swap(f, f+n4, n4) );  // inverse_gray_rev_permute

//    P1( swap(f+nh, f+nh+n4, n4) );  P1( swap(f+n4, f+nh, n4) );  // zip_rev
//    P1( swap(f, f+nh, n4) );  P1( swap(f, f+n4, n4) );  // rev @ zip_rev @ rev

//    P2( swap(f, f+nh, n4) );  // rev @ green_rev_permute == rev @ green_permute @ rev
//    P2( swap(f+n4, f+nh+n4, n4) );  // green_permute == green_rev_permute @ rev

//    P2( reverse(f+nh, nh) );  // gray
//    P2( reverse(f, nh) );  // rev @ gray_rev_permute

//    P2( negate(f+nh+n4, n4) );  //  grs_negate
//    P2( negate(f+nh, n4) );  //  ???

    nh = n4 = 0;  // avoid warning
    q = 0;
}
// -------------------------

void perm2(ulong *f, ulong n)
// From longer to shorter sub-arrays.
{
    for (ulong k=n; k>=2; k/=2)  // k == n, n/2, n/4, ..., 4, 2
    {
        for (ulong j=0; j<n; j+=k)  p2_func(f+j, k);
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong ldn = 6;
    NXARG(ldn, "Use 2**ldn elements");
    ulong  n = (1<<ldn);

    ulong *f = new ulong[n];
    set_seq( f, n );
    cout << "Operations:" << endl;


    // ---------- start PLAYGROUND ----------

    // --- 1: Try "known" permutations:
    TT( gray_permute(f, n) );  // default
//    TT( gray_rev_permute(f, n) );
//    TT( unzip(f, n) );
//    TT( zip(f, n); );

//    TT(
//       revbin_permute(f, n); gray_permute(f,  n); reverse(f, n);
//       reverse(f, n/2); inverse_gray_permute(f,  n/2); revbin_permute(f, n/2);
//       reverse(f+n/2, n/2); inverse_gray_permute(f+n/2,  n/2); revbin_permute(f+n/2, n/2);
//        );
//// = unzip_rev @. reverse
//// = h @. unzip_rev

//    TT(
//        revbin_permute(f, n/2); gray_permute(f,  n/2); reverse(f, n/2);
//        revbin_permute(f+n/2, n/2); gray_permute(f+n/2,  n/2); reverse(f+n/2, n/2);
//        reverse(f, n); inverse_gray_permute(f,  n); revbin_permute(f, n);
//        );
// = reverse .@ zip_rev
// = zip_rev .@ h


    // --- 2: Discover primitives:
    // 2a: define permutation and its inverse
#define F gray_permute
#define I inverse_gray_permute
//#define F zip_rev
//#define I unzip_rev
    // 2b: select one of:
//    TT( F(f, n) ); TT( I(f, n/2) ); TT( I(f+n/2, n/2) );  // 2b:  F I I
//    TT( I(f, n) ); TT( F(f, n/2) ); TT( F(f+n/2, n/2) );  // 2b:  I F F
//    TT( F(f, n/2) ); TT( F(f+n/2, n/2) ); TT( I(f, n) );  // 2b:  F F I
//    TT( F(f, n/2) ); TT( F(f+n/2, n/2) ); TT( F(f, n) );  // 2b:  I I F

    // --- 3: Permutations from primitives:
//    TT( perm1(f, n); );
//    TT( perm2(f, n); );


    // ---------- end PLAYGROUND ----------


    q = 0;

    cout << "Result:" << endl;
    cout << "[";
    for (ulong k=0; k<n; ++k)
    {
        if ( 0==(k % (n/4)) )  cout << endl;
        ulong v = f[k];
        cout << setw(2) << (v);
        if ( k<n-1 ) cout << ",";
    }
    cout << " ]";
    cout << endl;

    cout << "Analysis:" << endl;
    perm_recognize(f, n);
    cout << endl;

    delete [] f;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/perm-decomp-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/perm-decomp-demo.cc DEMOFLAGS=-DTIMING"
/// End:

