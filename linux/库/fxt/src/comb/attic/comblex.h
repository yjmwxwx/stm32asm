#if !defined HAVE_COMBLEX_H__
#define      HAVE_COMBLEX_H__

#include "bitcombination.h"
#include "fxttypes.h"
#include "newop.h"
#include "revbin.h"

//#include "fxtio.h"
class ostream;


class comb_lex
{
public:
    ulong n_;
    ulong k_;
    ulong bits_;
    ulong xbits_;
    ulong mask_;  // 111...111000..00 (n zeros)
    ulong nmask_;  // ~mask_
    ulong *x_;


public:
    comb_lex(ulong n, ulong k)
    {
        n_ = (n ? n : 1);  // not zero
        k_ = (k ? k : 1);  // not zero
        mask_ = ~first_comb(n);
        nmask_ = ~mask_;
        x_ = NEWOP(ulong, k);
        first();
    }

    ~comb_lex()  { delete [] x_; }


    ulong first()
    {
        xbits_ = first_comb(n_-k_);
        sync_x();
        return bits_;
    }

    ulong next()  // return zero if previous comb was the last
    {
        xbits_ = next_colex_comb(xbits_);
        sync_x();
        return ( (xbits_ & mask_) ? 0 : xbits_ );
    }

    const ulong * data()  { return x_; }
    const comb_lex &  current()  const  { return *this; }

    friend ostream & operator << (ostream &os, const comb_lex &x);

//private:
    void sync_x()
    {
        bits_ = nmask_ & ~revbin(xbits_, n_);  // jjnote: revbin is too expensive
        ulong tbits = bits_;
        ulong xi = 0, bi = 0;
        while ( bi < n_ )
        {
            if ( tbits & 1 )  x_[xi++] = bi;
            ++bi;
            tbits >>= 1;
        }
    }
};
// -------------------------



#endif  // !defined HAVE_COMBLEX_H__
