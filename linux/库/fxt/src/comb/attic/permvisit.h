#if !defined HAVE_PERMVISIT_H__
#define      HAVE_PERMVISIT_H__

#include "fxttypes.h"
#include "aux0/funcemu.h"


class perm_visit
{
protected:
    void first();
    ulong next_recursion();
    ulong n;
    ulong q;
    ulong idx;
    ulong *x;  // current permutation
    ulong *xi; // inverse of x[]
    funcemu<ulong> *fe;

public:
    perm_visit(ulong nn);
    ~perm_visit();

    ulong next()
    {
        if ( 0==q )  return 0;
        else
        {
            q = next_recursion();
            return  ( q ? ++idx : 0 );
        }
    }

    ulong current()  const  { return idx; }
    const ulong *data()  const  { return x; }
    const ulong *idata()  const  { return xi; }
};
// -------------------------


#endif  // !defined HAVE_PERMVISIT_H__
