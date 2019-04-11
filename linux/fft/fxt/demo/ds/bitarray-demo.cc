
#include "ds/bitarray.h"

#include "fxttypes.h"
#include "jjassert.h"
#include "fxtio.h"

//% Demo of the bitarray data structure.


// Output dependent on BITS_PER_LONG

#define  PRINT_DO(x) \
{ x;  cout << (#x) << " ==>" << endl;  B.dump_bits(1); }

#define  PRINT_VAL(x) \
{ ulong t = x;  cout << #x << " ==> " << (t?1:0) << " (" << t << ")" << endl; }

#define  PRINT_DO_VAL(x) \
{ ulong t = x;   cout << #x << " ==> " << t << endl;  B.dump_bits(1); }


int
main()
{
    bitarray B(67);
    B.clear_all();
    B.dump();  cout << endl;
    cout << endl;

    PRINT_DO( B.set_all() );
    PRINT_VAL( B.all_set_q() );
    jjassert( B.all_set_q() );

    PRINT_DO( B.clear_all() );
    PRINT_VAL( B.all_clear_q() );
    jjassert( B.all_clear_q() );

    PRINT_DO( B.set(12) );
    PRINT_DO( B.set(13) );
    PRINT_DO( B.set(33) );

    PRINT_VAL( B.test(42) );
    PRINT_VAL( B.test(43) );
    PRINT_VAL( B.test(44) );

    PRINT_VAL( B.next_set(13) );
    PRINT_VAL( B.next_set(14) );
//    PRINT_VAL( B.next_set(999) );

    PRINT_VAL( B.test(13) );
    PRINT_VAL( B.test(14) );
//    PRINT_VAL( B.test(999) );

    PRINT_DO_VAL( B.test_set(24) );
    PRINT_DO_VAL( B.test_clear(24) );
    PRINT_DO_VAL( B.test_change(24) );

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/ds"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/ds/bitarray-demo.cc"
/// make-target2: "1demo DSRC=demo/ds/bitarray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

