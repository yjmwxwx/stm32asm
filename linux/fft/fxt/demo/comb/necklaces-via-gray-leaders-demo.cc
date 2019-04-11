
#include "comb/gray-cycle-leaders.h"
#include "bits/bittransforms.h"  // yellow_code()
#include "bits/bitcyclic-period.h"

#include "bits/graycode.h"
#include "bits/print-bin.h"
#include "bits/bitcount.h"

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"

#include "jjassert.h"



//% Cycle leaders for gray permutation converted to necklaces

//#define CODE(x) blue_code(x)  // need reversed Gray code
#define CODE(x) yellow_code(x)  // default

void doit(ulong ldn, bool cq)
{
    gray_cycle_leaders L(ldn);

    const ulong len = L.cycle_length();
    const ulong num = L.num_cycles();
    cout << setw(3) << num << " cycles of length=" << setw(2) << len << "";
    cout << endl;

    const ulong s = BITS_PER_LONG - len;
    ulong ct = 0;
    do
    {
        ++ct;
//        ulong i = L.current_max();
        const ulong i = L.current_min();  // default
        print_bin(" L=  ", i, len);   // cycle leader

        const ulong ci = CODE(i);
        print_bin("  [ ", ci, len);  cout << " ]";  // necklace
        const ulong bc = bit_count(ci>>s);
        cout << endl;
        jjassert( len == bit_cyclic_period( ci ) );
        if ( cq )  // print cycle:
        {
            ulong w = i;
            while ( (w=gray_code(w)) != i )
            {
                print_bin(" --> ", w, len);
                const ulong cw = CODE(w);
                print_bin("  [ ", cw, len);  cout << " ]";
                cout << endl;

                jjassert( len == bit_cyclic_period(cw) );
                jjassert( bc == bit_count( cw>>s ) );
            }
            cout << endl;
        }
    }
    while ( L.next() );
    cout
        << "  ldn=" << ldn << ":"
        << " ct=" << ct
        << "  ==2**" << ld(ct) << endl;
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong ldn = 6;
    NXARG(ldn, "necklace with ldn bits");
    jjassert( ldn );
    bool cq = 1;
    NXARG(cq, "whether to print cycles");

    doit(ldn-1, cq);

    cout << endl;

    return 0;
}
// -------------------------

/*

% for n in $(seq 1 17); do echo -n "$n: "; ./bin $n 0 | grep length; done
 1:    1 cycles of length= 1
 2:    1 cycles of length= 2
 3:    1 cycles of length= 4
 4:    2 cycles of length= 4
 5:    2 cycles of length= 8
 6:    4 cycles of length= 8
 7:    8 cycles of length= 8
 8:   16 cycles of length= 8
 9:   16 cycles of length=16
10:   32 cycles of length=16
11:   64 cycles of length=16
12:  128 cycles of length=16
13:  256 cycles of length=16
14:  512 cycles of length=16
15: 1024 cycles of length=16
16: 2048 cycles of length=16
17: 2048 cycles of length=32

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/necklaces-via-gray-leaders-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/necklaces-via-gray-leaders-demo.cc DEMOFLAGS=-DTIMING"
/// End:

