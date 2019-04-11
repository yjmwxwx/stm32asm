
#include "comb/gray-cycle-leaders.h"

#include "bits/graycode.h"
#include "bits/print-bin.h"

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"


//% Cycle leaders (maxima or minima) for Gray permutation


void doit(ulong ldn, bool cq, bool miq)
{
    gray_cycle_leaders L(ldn);

    ulong pn = ldn + 1;  // print precision (int bits)

    ulong len = L.cycle_length();
    ulong num = L.num_cycles();
    cout << "  k =" << setw(2) << ldn << ":";
    cout << setw(3) << num << " cycles of length=" << setw(2) << len << "";
    cout << endl;

    pn = len;

    cout << " maxima = za XOR subsets(v) where " << endl;
    print_bin(" za = ", L.za_, pn);  cout << endl;
    print_bin("  v = ", L.B_.full_set(), pn);  cout << endl;
    cout << " minima = zi XOR subsets(v) where " << endl;
    print_bin(" zi = ", L.zi_, pn);  cout << endl;

    if ( cq ) cout << " Cycles: " << endl;
    else      cout << " Cycle leaders: " << endl;

    do
    {
        ulong m = L.current_max();
        if ( miq )  m = L.current_min();
//        const ulong m = L.current_min();
        print_bin("    L = ", m, pn);  cout << " = " << setw(4) << m;
        cout << endl;

        if ( cq )  // print cycle:
        {
            ulong w = m;
//            ulong mi = ~0UL, ma = 0;  // max and min
            do
            {
//                if ( w>ma )  ma = w;
//                if ( w<mi )  mi = w;
                print_bin("  --> ", w, pn);  cout  << " = " << setw(4) << w;
                cout << endl;
                w = gray_code(w);
            }
            while ( w!=m );
//            print_bin("  diameter = ", ma-mi, pn);  cout  << " = " << setw(4) << ma-mi;

            cout << endl;
        }
    }
    while ( L.next() );
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong ldn = 7;
    NXARG(ldn, "Cycle leaders for Gray permutation where highest bit is at position ldn");
//    NXARG(ldn, "Up to 2**ldn");

    bool miq = 0;
    NXARG(miq, "Whether to use minima instead of maxima as cycle leaders");

    bool cq = 0;
    NXARG(cq, "Whether to print cycles");

    bool aq = 0;
    NXARG(aq, "Whether to print all cycles/leaders for ldm=0..ldn");

    ulong ldm = (aq ? 0 : ldn);
    do
    {
        doit(ldm, cq, miq);
    }
    while ( ++ldm<=ldn );
    cout << endl;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/permgray-leaders-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/permgray-leaders-demo.cc DEMOFLAGS=-DTIMING"
/// End:

