

#include "fxttypes.h"
#include "mod.h"
#include "modm.h"

//#include "jjassert.h"

//#include <cmath>
#include <cstdlib>  // rand()


void
rand(mod *f, ulong n, umod_t m)
{
    for (ulong i=0; i<n; ++i)
    {
        umod_t t = (umod_t)((double)(m-1)*rand()/(RAND_MAX+1.0));
//        jjassert( t<m );
        f[i] = t;
    }
}
// -------------------------

