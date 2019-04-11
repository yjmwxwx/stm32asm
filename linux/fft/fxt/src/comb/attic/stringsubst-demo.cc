
#include "comb/stringsubst.h"

#include "fxtio.h"
//#include "jjassert.h"
#include "fxttypes.h"  // ulong

// define to generate a 'silent' stringsubst binary without default example
//#define MAKE_UTIL
#ifdef MAKE_UTIL
#define FXT_SILENT_NXARG
#endif
#include "nextarg.h"  // NXARG()

#include <unistd.h>  // exit(), close()

//% String substitution engine (Lindenmayer system, or L-system).

// Cf. comb/stringsubst-hilbert3d-demo.cc for the 3D Hilbert curve via string substitution.

static void
usage_err(const char *argv0)
{
    cerr << "Usage:" << endl;
    cerr << "  " << argv0 << " maxdepth starts symbol0 rule0 symbol1 rule1 ... " << endl;
    cerr << "For each symbol a rule must be supplied. " << endl;
    cerr << "At least two symbol/rule pairs are needed. " << endl;
    cerr << "Example 1:  (rabbit sequence)" << endl;
    cerr << "  " << argv0 << "  9   0   0 1      1 10 " << endl;
    cerr << "Example 2:  (Thue sequence)" << endl;
    cerr << "  " << argv0 << "  4   0   0 111   1 110 " << endl;

    close(1);  // so SIG_PIPE is generated when used with pipes
    exit(1);
}
// -------------------------

bool
run_substitutions(ulong maxn, const char *start, ulong nsym, const char ** args)
{
#ifdef MAKE_UTIL
    ulong cmax = 10000000;  // at most that many symbols
#else
    ulong cmax = 100000;  // at most that many symbols
#endif

    string_subst S(cmax, nsym, args);

#if 0  // print command line format
    cout << "cmd:   " << maxn << "  \"" << start << "\"";
    for (ulong j=0; j<nsym; ++j)
    {
        cout << "  \"" << S.symbol_[j] << "\" \"" << S.symrule_[j] << "\"";
    }
    cout << endl;
#endif

    if ( 0!=S.verify(start, false) )  return false;

    S.print_rules(start);
    cout << "-------------" << endl;

    for (ulong j=0; j<=maxn; ++j)
    {
        ulong ctc = S.subst(j, start);

        cout << j << ": ";
        cout << "  (#=" << ctc << ")" << endl;
        cout << "  " << S.string();
        cout << endl;
    }
    return  true;
}
// -------------------------

// rabbit:  ./bin  9   0  0 1  1 10
// Pell:    ./bin  6   0  0 1  1 110
// Thue:    ./bin  4   0  0 111  1 110

int
main(int argc, char *argv[])
{
    ulong maxn = 7;
    NXARG(maxn, "Max depth");

    char *start;
    NXARGSTR(start, "Start symbol(s)", "A");

    RESTARGS("Rules:  sym1 rep1  sym2 rep2  [... symN repN]");
#ifndef MAKE_UTIL
    cout << "Example: " << argv[0] << " 7 A  A x  x xA" << endl;
#endif

    bool ret = true;
#ifndef MAKE_UTIL
    if ( argc > 1 )
#endif
    {
        ulong rem = (ulong)(argc - 3);  // jjcast
        // need at least two rules (4 more args):
        if ( (long)rem < 4 )  { usage_err( argv[0] ); }
        // need an even number of args:
        if ( 0!=(rem%2) )  { usage_err( argv[0] ); }

        ulong nsym = rem / 2;
        ret = run_substitutions( maxn, start, nsym, (const char **)argv+3 );
        if ( ! ret )  { usage_err( argv[0] ); }
        return 0;
    }
#ifndef MAKE_UTIL
    else  // defaults:
    {
        cout << "\n------------- rabbit sequence: -------------" << endl;
        const char * rabbit_rules[] = { "0", "1",
                                        "1", "10" };
        ret = run_substitutions( 7, "0", 2, rabbit_rules );
//        ret = run_substitutions( 7, "0", 2, { "0", "1", "1", "10" } );  // needs -std=c++0x

        cout << "\n------------- Thue-Morse sequence: -------------" << endl;
        const char * thue_morse_rules[] = {
            "0", "01",
            "1", "10" };
        ret = run_substitutions( 6, "0", 2, thue_morse_rules );

        cout << "\n------------- Dragon curve (90deg turns): -------------" << endl;
        const char * dragon_rules[] = {
            "F", "F+G+",
            "G", "-F-G",
            "+", "+",
            "-", "-" };
        ret = run_substitutions( 5, "F", 4, dragon_rules );

#if 0
        cout << "\n------------- modified rabbit sequence: -------------" << endl;
        const char * fibonacci_rules[] = {
            ".", "A",
            "A", "B.",
            "B", "B." };
        ret = run_substitutions( 10, ".", 3, fibonacci_rules );

        cout << "\n------------- Power series of prod(n>=1, 1+x^(2^n-1)): -------------" << endl;
        const char * prod_rules[] = {
            "0", "0",
            "1", "110",
            "A", "A" };
        ret = run_substitutions( 5, "1A", 3, prod_rules );

        cout << "\n------------- Terdragon curve (120deg turns): -------------" << endl;
        const char * terdragon_rules[] = {
            "F", "F+F-F",
            "+", "+",
            "-", "-" };
        ret = run_substitutions( 4, "F", 3, terdragon_rules );

        cout << "\n------------- R5-dragon curve (90deg turns): -------------" << endl;
        const char * r5_dragon_rules[] = {
            "F", "F+F+F-F-F",
            "+", "+",
            "-", "-" };
        ret = run_substitutions( 3, "F", 3, r5_dragon_rules );

        cout << "\n------------- Gosper's 'flowsnake' curve (60deg turns): -------------" << endl;
        const char * gosper_rules[] =
            { "F", "F+G++G-F--FF-G+",
              "G", "-F+GG++G+F--F-G",
              "+", "+",
              "-", "-" };
        ret = run_substitutions( 3, "F", 4, gosper_rules );


        cout << "\n------------- Triangle curve (60deg turns): -------------" << endl;
        const char * triangle_rules[] = {
            "L", "R-L--R++L",
            "R", "R--L++R+L",
            "+", "+",
            "-", "-" };
        ret = run_substitutions( 3, "L", 4, triangle_rules );


        cout << "\n------------- fractal tree (20deg turns): -------------" << endl;
        const char * tree_rules[] = { "L", "R[+L]R[-L]+L",
                                      "R", "RR",
                                      "+", "+",
                                      "-", "-",
                                      "[", "[",  // push position/direction
                                      "]", "]" };  // pop position/direction
        ret = run_substitutions( 3, "L", 6, tree_rules );

        cout << "\n------------- Hilbert curve (90deg turns): -------------" << endl;
        const char * hilbert_rules[] = {
            "a", "-bF+aFa+Fb-",
            "b", "+aF-bFb-Fa+",
            "+", "+",
            "-", "-",
            "F", "F" };
        ret = run_substitutions( 4, "a", 5, hilbert_rules );

        cout << "\n------------- Hilbert curve (moves): -------------" << endl;
        const char * hilbertm_rules[] = {
            "A", "D>A^A<C",
            "B", "C<BvB>D",
            "C", "BvC<C^A",
            "D", "A^D>DvB",
            ">", ">", "<", "<", "^", "^", "v", "v" };
        ret = run_substitutions( 3, "A", 8, hilbertm_rules );


        cout << "\n------------- Hilbert curve (moves): -------------" << endl;
        const char * hilbertm2_rules[] = {
            "A", "A^D>DvB>D>A^A<C^D>A^A<C<BvC<C^A",
            "B", "BvC<C^A<C<BvB>DvC<BvB>D>A^D>DvB",
            "C", "C<BvB>DvBvC<C^A<BvC<C^A^D>A^A<C",
            "D", "D>A^A<C^A^D>DvB>A^D>DvBvC<BvB>D",
            ">", ">", "<", "<", "^", "^", "v", "v" };
        ret = run_substitutions( 2, "A", 8, hilbertm2_rules );

        cout << "\n------------- 3D Hilbert curve (90deg turns): -------------" << endl;
        const char * hilbert3d_rules[] = {
            "a", "^<aF^<aFa-F^>>aFavF+>>aFa-F>a->",
            "F", "F", "<", "<", ">", ">", "^", "^", "v", "v", "+", "+", "-", "-" };
        ret = run_substitutions( 3, "a", 8, hilbert3d_rules );
#endif  // 0
    }
#endif  // MAKE_UTIL

    return  ! ret;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/stringsubst-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/stringsubst-demo.cc DEMOFLAGS=-DTIMING"
/// End:

