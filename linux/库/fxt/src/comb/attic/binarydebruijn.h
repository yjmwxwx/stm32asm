#if !defined  HAVE_BINARYDEBRUIJN_H__
#define       HAVE_BINARYDEBRUIJN_H__


#include "fxttypes.h"
#include "bitsperlong.h"
#include "newop.h"
#include "copy.h"


class binary_debruijn
{
public:
    binary_debruijn(ulong n)
        : nmax_(BITS_PER_LONG)
    {
        x_ = NEWOP(ulong, nmax_);
        y_ = NEWOP(ulong, nmax_);
        t_ = NEWOP(ulong, nmax_);
        init(n);
    }

    ~binary_debruijn()
    {
        delete [] t_;
        delete [] y_;
        delete [] x_;
    }

    void init(ulong n=0)
    {
        if ( 0!=n)  n_ = n;
        ndb_ = 1UL << n_;  // period of the sequence
        ndbac_ = ndb_ + n_ - 1;  // use this length to avoid cyclic match
        null(x_, nmax_);
        null(y_, nmax_);
        null(t_, nmax_);
        word_ = 0;

        ct1 = 0;
        ct2 = 0;
        nn = n_ - 1;
        xx = 0;
        tt = 0;
        yy = 0;
    }

    ulong func1()  // output 01010101...
    {
        ulong ret = ct1;
        ct1 = 1 - ct1;
        return  ret;
    }

    ulong func2()  // output 001100110011...
    {
        ulong ret = ct2 / 2;
        ++ct2;
        ct2 %= 4;
        return  ret;
    }

    ulong func(ulong n);

    ulong next();

    void make_seq(ulong *z, ulong ndb=0);


public:
    ulong n_;
    ulong ndb_;
    ulong ndbac_;  // to avoid cyclic search
    ulong *x_, *y_, *t_;
    const ulong nmax_;
    ulong word_;
private:
    ulong ct1, ct2;
    ulong nn;
    ulong xx, tt, yy;
};
// -------------------------



#endif  // !defined HAVE_BINARYDEBRUIJN_H__
