#if !defined  HAVE_SUBSETDEBRUIJN_H__
#define       HAVE_SUBSETDEBRUIJN_H__


#include "binarydebruijn.h"

class subset_debruijn : public binary_debruijn
{
public:
    subset_debruijn(ulong nn)
        : binary_debruijn(nn)
    {
        x = NEWOP(ulong, nmax_);
        init();
    }

    ~subset_debruijn()  { delete [] x;}


    void init()
    {
        binary_debruijn::init();
        for (ulong k=0; k<n_; ++k)  binary_debruijn::next();
        sync_x();
    }

    ulong next()  // return number of elements in subset
    {
        binary_debruijn::next();
        sync_x();
        return  word_;
    }

    const ulong * data()  { return x; }


protected:
    void sync_x()
    {
        for (ulong j=0, m=1;  j<n_;  ++j, m<<=1)
        {
            x[j] = (word_ & m ? 1 : 0);
        }
    }

protected:
    ulong *x;
};
// -------------------------



#endif  // !defined HAVE_SUBSETDEBRUIJN_H__
