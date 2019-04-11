#if !defined HAVE_COMBCOLEX_H__
#define      HAVE_COMBCOLEX_H__

#include "bitcombination.h"
#include "fxttypes.h"

#include "newop.h"

//#include "fxtio.h"
class ostream;

class comb_colex
{
public:
    ulong n_;
    ulong k_;
    ulong bits_;
    ulong mask_;  // 111...111000..00 (n zeros)
    ulong *x_;


public:
    comb_colex(ulong n, ulong k)
    {
        n_ = (n ? n : 1);  // not zero
        k_ = (k ? k : 1);  // not zero
        x_ = NEWOP(ulong, k);
        first();
    }

    ~comb_colex()  { delete [] x_; }

    ulong first()
    {
        bits_ = first_comb(k_);
        return  sync_x();
    }

    ulong last()
    {
        bits_ = first_comb(k_) << (n_ - k_);
        return  sync_x();
    }

    ulong next()  // return zero if previous comb was the last
    {
        bits_ = next_colex_comb(bits_);
        return  sync_x();
    }

    ulong prev()  // return zero if previous comb was the last
    {
        bits_ = prev_colex_comb(bits_);
        return  sync_x();
    }

    const ulong * data()  { return x_; }

    friend ostream & operator << (ostream &os, const comb_colex &x);

//private:
    ulong sync_x()
    {
        ulong tbits = bits_;
        ulong xi = 0, bi = 0;
        while ( bi < n_ )
        {
            if ( tbits & 1 )  x_[xi++] = bi;
            ++bi;
            tbits >>= 1;
        }

        return ! tbits;
    }
};
// -------------------------



#endif  // !defined HAVE_COMBCOLEX_H__
