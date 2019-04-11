
#include "bits/bitsperlong.h"
#include "aux1/bytescan.h"
#include "jjassert.h"
#include "fxtio.h"

#include <cmath>
#include <cstdlib>  // strtoul(), rand()
#include <cstring>  // memchr(), strlen()

#include "fxtalloca.h"
#include "fxttypes.h"

#include "test.h"  // last to include



int
main(int argc, char **argv)
{
    cout << "Running misc tests ... " << endl;

    ulong n = 1024*10;
    if ( argc>1 )  n = strtoul(argv[1], 0, 10);

    ulong rep = 30;
    ulong suml = 0;

    ALLOCA(char, ar, n); //, fr[n], gr[n];
    cout << "====================  N = " << n << " :" << endl;
    for (ulong r=1; r<=rep; ++r)
    {
        cout << "+++++++++++++++++++++++++ PASS # " << r
             << " (of " << rep << ") +++++++++++++++++++++++++" << endl;

        for (ulong i=0; i<n; ++i)  ar[i] = (char)(rand() ^ (rand()>>16));
        //    for (ulong i=0; i<n; ++i)  ar[i] <<= 2;
        ar[n-1] = 0;
        char *p = ar;

        cout << "\n----- bytescan: -----" << endl;
        for (ulong k=0; k<n; ++k, ++p)
        {
            ulong l1 = strlen(p);
            suml += l1;
            ulong l2 = long_strlen(p);
            if ( l1 != l2 )
            {
                cout << hex;
                for (ulong z=0; z<=l2+7; ++z)
                {
                    cout << setw(4) << (ulong)(p[z])
                         << "  @ idx=" << (ulong)(z)
                         << "    == * " << (ulong)(p+z)
                         << "  %= " << ((ulong)(p+z))%BYTES_PER_LONG
                         << endl;
                }
                cout << " l1 = " << l1 << " =!= " << l2 << " = l2 " << endl;
                //        cout << " www = " << www << endl;
                cout << dec;
                jjassert( 0 );
            }
            //      cout << " l1 == l2 = " << l1 << endl;

        }  // === ldn ===

        cout << "+++++++++++++++++++ PASS # " << r
             << " (of " << rep << ") ++++++ FINISHED +++++++++++++" << endl;
    } // === r ===

    cout << "\nOK, all passed." << endl;

    //  cout << " suml =  " << suml << endl;
    //  jjassert(0); // stop make      ***NOT*** an error"

    return 0;
}
// -------------------------
