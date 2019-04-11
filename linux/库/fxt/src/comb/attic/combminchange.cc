
#include "bitcombination.h"  // first_comb()
#include "combminchange.h"
#include "funcemu.h"
#include "fxttypes.h"
#include "newop.h"

#include "fxtio.h"


#define GEN   0
#define NEG  10
#define RET  20

#define EMU_CALL(func, n, k)  fe_->stpush(func);  fe_->push(n, k);


comb_minchange::comb_minchange(ulong n, ulong k)
{
    n_ = (n ? n : 1);  // not zero
    k_ = (k ? k : 1);  // not zero
    x_ = NEWOP(ulong, k);

    last_ =  (first_comb(k) >> 1) | (1<<(n-1));

    fe_ = new funcemu<ulong>(64, 256);
    EMU_CALL( GEN, n, k );

    first();
}
// -------------------------


comb_minchange::~comb_minchange()
{
    delete fe_;
    delete [] x_;
}
// -------------------------


ulong
comb_minchange::next_recursion()
{
    ulong n, k;

 redo:
    fe_->peek(n, k);

    if ( (k>0) && (k<n) )
    {
        switch ( fe_->stpeek() )
        {
        case GEN: // entry
            fe_->stnext();
            EMU_CALL( GEN, n-1, k );
            goto redo;

        case GEN+1:
            fe_->stnext();
            bit_swap_01(n, k);
            return 1;

        case GEN+2:
            fe_->stnext( RET );
            EMU_CALL( NEG, n-1, k-1 );
            goto redo;


        case NEG: // entry
            fe_->stnext();
            EMU_CALL( GEN, n-1, k-1 );
            goto redo;

        case NEG+1:
            fe_->stnext();
            bit_swap_01(n, k);
            return 1;

        case NEG+2:
            fe_->stnext( RET );
            EMU_CALL( NEG, n-1, k );
            goto redo;

        default: ; // return
        }
    }

    fe_->pop(2);  fe_->stpop();  // emu_return to caller

    if ( fe_->more() )  goto redo;

    return 0;  // return and emu_return from top level call
}
// -------------------------

// original recursive version by Glenn C. Rhoads
//
//  word = (1 << k) - 1;  word <<= (n-k);  // initial comb.
//  Visit(word);  // visit initial bit comb.
//  GEN(n, k);  // visit all following comb.
//
//  void GEN(int n, int k)
//  {
//      if ( (k>0) && (k<n) )
//      {
//          GEN(n-1, k);
//          bit_swap_01(n, k);
//          Visit(word);
//          NEG(n-1, k-1);
//      }
//  }
//
//  void NEG(int n, int k)
//  {
//      if ( (k>0) && (k<n) )
//      {
//          GEN(n-1, k-1);
//          bit_swap_01(n, k);
//          Visit(word);
//          NEG(n-1, k);
//      }
//  }
//// -------------------------


ostream & operator << (ostream &os, const comb_minchange &x)
{
    cout.width(2);
    os << x.x_[0];
    for (ulong i=1; i<x.k_; ++i)
    {
        os << " ";
        cout.width(2);
        cout << x.x_[i];
    }
    return os;
}
// -------------------------
