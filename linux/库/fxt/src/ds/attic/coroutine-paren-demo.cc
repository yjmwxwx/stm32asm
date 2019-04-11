
#include "ds/coroutine.h"
//#include "comb/paren.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% Generate all well-formed pairs of parentheses using coroutines.


class paren
{
protected:
    typedef struct { int i,s,k,t; } vars;
    coroutine<vars> *cr_;
    int *x;
    // x[i] is the number of right parentheses between the
    // i-th left parenthesis and the (i+1)-th left parenthesis.
    char *str;

    int n;
    int q;
    int idx;

public:
    paren(int nn);
    ~paren();

    int next()
    {
        if ( 0==q )  return 0;
        else
        {
            q = next_recursion();
            return  ( q ? ++idx : 0 );
        }
    }

    const int *data()  const  { return x; }
    const char *string()  const  { return str; }
    int current()  const  { return idx; }

protected:
    int next_recursion();
};
// -------------------------


#define ST_INIT    0  // initial state
#define ST_RETURN  20

//           args=(i, s)  (k, t)=locals
#define CORO_CALL(vi, vs, vk, vt) \
 { vars V_; V_.i=vi; V_.s=vs; V_.k=vk; V_.t=vt; \
   cr_->push(V_);  cr_->stpush(ST_INIT); }

#define CORO_RETURN()  { cr_->pop();  cr_->stpop(); }


paren::paren(int nn)
{
    n = (nn>0 ? nn : 1);
    x = new int[n+1];
    ++x;

    str = new char[2*n+1];
    int i = 0;
    for (  ; i<n  ; ++i)  str[i] = '('; // OPEN_CHAR;
    for (  ; i<2*n; ++i)  str[i] = ')'; // CLOSE_CHAR;
    str[2*n] = 0;

    cr_ = new coroutine<vars>((ulong)n+1);

    //         i, s, k, t
    CORO_CALL( 0, 0, 0, 0 );

    idx = 0;
    q = next_recursion();
}
// -------------------------

paren::~paren()
{
    --x;
    delete [] x;
    delete [] str;
    delete cr_;
}
// -------------------------


int
paren::next_recursion()
{
 redo:
    vars &V = cr_->peek();
    int &i=V.i,  &s=V.s; // args
    int &k=V.k,  &t=V.t; // locals

 loop:
    switch ( cr_->stpeek() )
    {
    case 0:
        if ( i>=n )
        {
            x[i-1] = n - s;
            cr_->stnext( ST_RETURN );  return 1;
        }
        cr_->stnext();

    case 1:
        // loop end ?
        if ( k>i-s )  { break; }  // shortcut: nothing to do at end

        cr_->stnext();

    case 2: // start of loop body
        {
            long ii = i - 1;
            x[ii] = k;
            t = s + k;

            str[t+i] = '('; // OPEN_CHAR;

            cr_->stnext();
            CORO_CALL( i+1, t, 0, 0 );
            goto redo;
        }

    case 3:
        str[t+i] = ')'; // CLOSE_CHAR;
        ++k;

        // loop end ?
        if ( k>i-s )  { break; }  // shortcut: nothing to do at end

        cr_->stpoke(2);  goto loop; // shortcut: back to loop body

    default: ;
    }

    CORO_RETURN();

    if ( cr_->more() )  goto redo;

    return 0;
}
// -------------------------


// based on Glenn Rhoad's:
//void paren(long i, long s)
//{
//    long k, t;
//
//    printf("P(%ld, %ld)  ", i, s);
//    if ( i<n )
//    {
//        for (k=0; k<=i-s;  ++k)
//        {
////            printf("i = %d \n", i);
//            assert( i >= 0 );  assert( i < n );
//            a[i] = k;
//            t = s + a[i];
//            q[t+i] = '(';
//            paren(i+1, t);  // recursion
//            q[t+i] = ')';
//        }
//    }
//    else
//    {
//        // a[i] = n - s;  // never read
//        Visit();  // next set of parens available
//    }
//}
//// -------------------------



int
main(int argc, char **argv)
{
    int n = 5;
    NXARG(n, "Number of paren pairs");

    paren pa(n);
    const int *x = pa.data();
    const char *str = pa.string();

    do
    {
        cout << " #" << setw(3) << pa.current() << ":   ";
        for (int i=0; i<n; ++i)  cout << x[i] << " ";

        cout << "  " << str;

        cout << endl;
    }
    while ( pa.next() );

//    cerr << "n= " << n << " total # = " << (1+pa.current()) << endl;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/ds"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/ds/coroutine-paren-demo.cc"
/// make-target2: "1demo DSRC=demo/ds/coroutine-paren-demo.cc DEMOFLAGS=-DTIMING"
/// End:

