
#include "bits/hilbert.h"

#include "nextarg.h"
#include "jjassert.h"
#include "fxttypes.h"  // ulong

//% Moves and turns of the Hilbert curve.


int
main(int argc, char **argv)
{
    ulong ldn = 6;
    NXARG(ldn, "number of moves == 2**ldn");
    ulong n = 1UL << ldn;

    cout << " dx+dy: ";
    for (ulong k=1; k<n; ++k)  cout << ("+-")[ hilbert_p(k) ];
    cout << endl;

    cout << " dx-dy: ";
    for (ulong k=1; k<n; ++k)  cout << ("+-")[ hilbert_m(k) ];
    cout << endl;

    cout << "   dir: ";
    for (ulong k=1; k<n; ++k)
    {
        ulong d = hilbert_dir(k);
//        cout << "(v><^)"[ d ];
        cout << (">v^<")[ d ];
    }
    cout << endl;

    cout << "  turn: ";
    for (ulong k=1; k<n; ++k)
    {
        int u = hilbert_turn(k);
        cout << ("-0+")[u+1];
    }
    cout << endl;


//    cout << "  turn: ";
//    for (ulong k=1; k<n; ++k)
//    {
//        ulong d1 = hilbert_dir(k);
//        ulong d2 = hilbert_dir(k-1);
//        d1 ^= (d1>>1);
//        d2 ^= (d2>>1);
//        cout << ("+.-0+.-")[ d1-d2 + 3];
//    }
//    cout << endl;

    return 0;
}
// -------------------------


// dx+dy: ++-+++-+++----++++-+++-+++----++++-+++-+++----+---+---+---++++-
// dx-dy: +----+++-+++-+++-++++---+---+----++++---+---+----++++---+---+--
//   dir: >^<^^>v>^>vv<v>>^>v>>^<^>^<<v<^^^>v>>^<^>^<<v<^<<v>vv<^<v<^^>^<
//  turn: 0--+0++--++0+--0-++-0--++--0-++00++-0--++--0-++-0--+0++--++0+--

/*
OEIS sequences:

// Horizontal moves:  A163538
% ./bin 8 | grep dir | cut -d: -f2 | sed 's/\(.\)/\1,/g; s/[v^]/0/g; s/>/+1/g; s/</-1/g;'
 ,+1,0,-1,0,0,+1,0,+1,0,+1,0,0,-1,0,+1,+1,0,+1, ...

// Vertical moves:  A163539
% ./bin 8 | grep dir | cut -d: -f2 | sed 's/\(.\)/\1,/g; s/[<>]/0/g; s/\^/+1/g; s/v/-1/g;'
 ,0,+1,0,+1,+1,0,-1,0,+1,0,-1,-1,0,-1,0,0,+1,0,-1,0,0, ...

// Whether moves are either '^' or '>' :
% ./bin 8 | grep dir | cut -d: -f2 | sed 's/\(.\)/\1,/g; s/[v<]/0/g; s/[>^]/1/g;'
 ,1,1,0,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,0,1,1,1,0, ...
// same can be obtained via the following command:
% ./bin 8 | fgrep 'dx+dy' | cut -d: -f2 | sed 's/\(.\)/\1,/g; s/-/0/g; s/+/1/g;'

// Whether moves are horizontal:
% ./bin 8 | grep dir | cut -d: -f2 | sed 's/\(.\)/\1,/g; s/[v^]/0/g; s/[<>]/1/g;'
 ,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0, ...

// Direction:
% ./bin 8 | fgrep 'dir' | cut -d: -f2 | sed 's/\(.\)/\1,/g;' | tr '>v^<' '0123'
 ,0,2,3,2,2,0,1,0,2,0,1,1,3,1,0,0,2,0,1,0,0,2,3,2,0, ...

// Direction: A163540
% ./bin 6 | fgrep 'dir' | cut -d: -f2 | sed 's/\(.\)/\1,/g;' | tr '>^<v' '0123'
 ,0,1,2,1,1,0,3,0,1,0,3,3,2,3,0,0,1,0

// Direction: A163541
% ./bin 6 | fgrep 'dir' | cut -d: -f2 | sed 's/\(.\)/\1,/g;' | tr '^>v<' '0123'
 ,1,0,3,0,0,1,2,1,0,1,2,2,3,2,1,1,0,1,2,1,1,0,3,0,1,0,3,3, ...

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/hilbert-moves-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/hilbert-moves-demo.cc DEMOFLAGS=-DTIMING"
/// End:

