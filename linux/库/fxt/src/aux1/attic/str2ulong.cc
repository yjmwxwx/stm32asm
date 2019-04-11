
#include "fxttypes.h"

#include <cstdlib>  // atol()
#include <cstring>  // strlen()


ulong
str2ulong(const char *p)
{
    ulong v = 0;
    if ( p!=0 )
    {
        v = atol(p);
        for (int i=strlen(p); i>=0; --i)
        {
            char c = p[i];
            if ( (c=='k') || (c=='K' ) )  { v *= (1UL<<10); break; }
            if ( (c=='m') || (c=='M' ) )  { v *= (1UL<<20); break; }
            if ( (c=='g') || (c=='G' ) )  { v *= (1UL<<30); break; }
        }
    }
    return v;
}
// -------------------------
