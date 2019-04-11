#if !defined  HAVE_BITDEMOS_H__
#define       HAVE_BITDEMOS_H__

// fixme: ugly hack to split the bit*-demos into separate files

#include "fxttypes.h"
#include "bits/bitsperlong.h"

void do_the_show(ulong v);

#include "bits/revbin.h"

#include "jjassert.h"

#include "fxtio.h"

#include <cstdlib>  // strtoul()

#include "bits/print-bin.h"

void print_sep()
{
    cout << "----------------------------------------------------------"
         << endl;
}
// -------------------------

const char *vv[] =
{
    "0000001000000",
    "0000101",
//    "00111111",
//    "00111100",
    "001111000011110111",
    "111101100011100100",
    "00000001",
    "10101010",
    "_83828180",
    "00000000"  // last must be zero
};
// -------------------------

static const char c01[] = ".1";

#define  SHWBIN( func ) \
{ t=func(v); print_bin("", t, 0, c01); \
    cout << " = " << #func << endl; }

#define  SHWBIN2( func, s ) \
{ t=func(v, s); print_bin("", t, 0, c01); \
    cout << " = " << #func << "( x, " <<s<< ")" << endl; }

#define  SHWDEC( func ) \
{ t=func(v); cout.width(BITS_PER_LONG); \
    cout << t << " = " << #func << endl; }

#define WORD \
    print_bin("", v, 0, c01);               \
    cout << "  = " << hex << "0x" << v << dec;  \
    cout << "  == word" << endl;                \
    cout << endl;                               \

int
main()
{
    for (ulong i=0;  ; ++i)
    {
        ulong v;
        if ( vv[i][0]!='_' )  v = strtoul(vv[i], 0, 2);
        else                  v = strtoul(vv[i]+1, 0, 16);

        do_the_show(v);

        v = ~v;
        do_the_show(v);

        v = revbin(~v, BITS_PER_LONG);
        if ( 0==v )  break;
        do_the_show(v);

        v = ~v;
        do_the_show(v);

        print_sep();
        cout << endl;
        cout << endl;
    }

    return 0;
}
// -------------------------


#endif // !defined HAVE_BITDEMOS_H__
