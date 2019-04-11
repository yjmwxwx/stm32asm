
#include "binarydebruijn.h"


ulong
binary_debruijn::func(ulong n)
//
// Knuths algorithm
// specialized for m=2
// muenchhausenized: recursive part
{
    ulong xret = x_[n];
    if ( (0!=x_[n]) && (t_[n]>=n) )  goto R3;

 R2:
    y_[n] = (n==2 ?  func2() : func(n-1));

 R3:
    if ( 1==y_[n] )  ++t_[n];
    else               t_[n] = 0;

    if ( (t_[n]==n ) && (0!=x_[n]) )  goto R2;

    x_[n] ^= y_[n];

    return  xret;
}
// -------------------------


ulong
binary_debruijn::next()
// muenchhausenized: top level
{
// R1:
    word_ <<= 1;
    word_ |= xx;
    word_ &= (ndb_-1);

    if ( (0!=xx) && (tt>=nn) )  goto R3;

 R2:
    if ( nn>2 )  yy = func(nn-1);
    else
    {
        if ( nn==2 )  yy = func2();
        else          yy = func1();
    }

 R3:
    if ( 1==yy )  ++tt;
    else            tt = 0;

    if ( (tt==nn ) && (0!=xx) )  goto R2;

    xx ^= yy;

//    goto R1;
    return  word_ & 1;
}
// -------------------------

void
binary_debruijn::make_seq(ulong *z, ulong ndb/*=0*/)
{
    if ( 0==ndb )  ndb = ndb_;
    ulong sct = 0;
    do  z[sct] = next();
    while ( ++sct<ndb );
}
// -------------------------
