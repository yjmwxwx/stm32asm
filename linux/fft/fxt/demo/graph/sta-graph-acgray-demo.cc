
// demo-is-self-contained

#include "bits/print-bin.h"
#include "bits/bitrotate.h"

#include "fxttypes.h"
#include "nextarg.h"
#include "jjassert.h"


//% Paths through a directed graph: adjacent changes (AC) Gray paths.
//% Streamlined standalone routine (for backtracking).

#define MAX_N 1024

ulong n=0;
ulong N=0;  // 2**n
ulong m=0;  // mask = N-1

ulong rv[MAX_N];  // path
ulong B[MAX_N];  // tag array

ulong ct = 0;
ulong maxct = 0;


void visit()
{
//    const ulong ch = rv[0] ^ rv[N-1];
//    if ( ch != ( ch & -ch ) )  return;  // only cycles

//    // wrap-around adjacency condition:
//    const ulong ch0 = rv[0] ^ rv[1];
//    if ( ( (ch0 & (ch<<1)) == 0 ) && ( (ch0 & (ch>>1)) == 0 ) )  return;

    ++ct;
    if ( (ct & 0xffff) == 0 )  cout << ct << ":" << endl;
#if 1
    cout << ct << ":" << endl;
    for (ulong j=0; j<N; ++j)
    {
        cout << setw(4) << j;
        print_bin(": ", rv[j], n);
        if ( j!=0 )  print_bin("    ", rv[j]^rv[j-1], n);
        cout << endl;
    }
    cout << endl;
#endif
}
// -------------------------


void search(ulong v, ulong b, ulong nv)
// Visit node v (which must be marked)
{
//    jjassert( nv < N );

    rv[nv] = v;
    ++nv;
    if ( nv == N )  // found a path
    {
        visit();
        if ( ct==maxct )
        {
            cout << " ct=" << ct << endl;
            exit(0);  // note exit()
        }
    }

    ulong b1;

#if 1  // right adjacent
    b1 = (b >> 1) & m;
    if ( b1 )
    {
        ulong v1 = v ^ b1;
        if ( ! B[v1] )  { B[v1]=1; search(v1, b1, nv); }
    }
#endif

#if 1  // left adjacent
    b1 = (b << 1) & m;
    if ( b1 )
    {
        ulong v1 = v ^ b1;
        if ( ! B[v1] )  { B[v1]=1; search(v1, b1, nv); }
    }
#endif

#if 0  // left two-close
//    if ( ((b>>1) & m) == 0 )
    if ( ((b&0xaaaaaaaa) & m) == 0 )
    {
        b1 = (b << 2) & m;
        if ( b1 )
        {
            ulong v1 = v ^ b1;
            if ( ! B[v1] )  { B[v1]=1; search(v1, b1, nv); }
        }
    }
#endif

#if 0  // right two-close
//    if ( ((b<<1) & m) == 0 )
    if ( ((b&0xaaaaaaaa) & m) == 0 )
    {
        b1 = (b >> 2) & m;
        if ( b1 )
        {
            ulong v1 = v ^ b1;
            if ( ! B[v1] )  { B[v1]=1; search(v1, b1, nv); }
        }
    }
#endif
    B[v] = 0;
}
// -------------------------



int main(int argc, char **argv)
{
    n = 6;
    NXARG(n, "number of bits (n>=3)");
    N = 1UL << n;
    jjassert( N <= MAX_N );

    m = N - 1;
    //    cout << "N=" << N << endl;
    maxct = 1;
    NXARG(maxct, "stop after that many paths (0 ==> find all paths)");
    if ( maxct == 0 )  maxct = -1UL;

    for (ulong j=0; j<N; ++j)  B[j] = 0;  // clear tag array

    // start from zero:
    const ulong v0 = 0;
    B[0] = 1;
    rv[0] = v0;

    ulong Nh = (1UL << ( n / 2 )) + 1;
//    ulong Nh = N/2;
    cout << "Nh=" << Nh << endl;
    for (ulong b1=1; b1<Nh; b1<<=1)
    {
//        cout << " :: b1=" << b1 << endl;
        const ulong v1 = v0 ^ b1;
        B[v1] = 1;
#if 0
        search(v1, b1, 1);
#else
        const ulong b2 = b1 << 1;
        const ulong v2 = v1 ^ b2;
        rv[1] = v1;
        B[v2] = 1;

        search(v2, b2, 2);

        B[v2] = 0;
#endif
        B[v1] = 0;
    }

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

% time ./bin 7
arg 1: 7 == n  [number of bits (n>=3)]  default=6
arg 2: 0 == maxct  [stop after that many paths (0 ==> find all paths)]  default=0
Nh=9
 ct=0
./bin 7  1.35s user 0.00s system 99% cpu 1.349 total

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/graph"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/graph/sta-graph-acgray-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/sta-graph-acgray-demo.cc DEMOFLAGS=-DTIMING"
/// End:
