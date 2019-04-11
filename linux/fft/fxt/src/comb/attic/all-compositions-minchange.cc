
#include "comb/all-compositions-minchange.h"
#include "comb/composition-colex.h"
#include "aux0/swap.h"

#include "fxtio.h"
#include "fxttypes.h"

#include "jjassert.h"


void
all_compositions_minchange::swap(ulong i1, ulong i2, ulong k)
{
    --i2;
//    jjassert( i2 < b_ );
    for (  ; i1<i2; ++i1,--i2)
    {
        ulong k1 = i1 * k_;
        ulong k2 = i2 * k_;
        for (ulong i=0; i<k; ++i)
        {
            ulong x1 = k1+i, x2 =k2+i;
            swap2( xx_[x1], xx_[x2] );
            jjassert( x1 < k_*b_ );
            jjassert( x2 < k_*b_ );
        }
    }
}
// -------------------------


#define COND(i, v)  (xx_[k+i*k_]!=v)
//
void
all_compositions_minchange::gray(ulong k)
{
    for (ulong v=1; v<n_; v+=2)
    {
        ulong i1 = 0;
        while ( i1<b_ )
        {
            while (  COND(i1, v) )
            {
                ++i1;
                if ( i1>=b_ )  goto next;
            }
            ulong i2 = i1;
            while ( ! COND(i2, v) )
            {
                ++i2;
                if ( i2>=b_ )  break;
            }

            swap(i1, i2, k);
            i1 = i2;
        }
    next: ;
    }
}
// -------------------------
#undef COND


#if 0  // experimental code
uchar tmp[32];
void
all_compositions_minchange::rev(ulong i1, ulong i2, ulong k)
{
    for (  ; i1<i2; ++i1)
    {
        ulong k1 = i1 * k_;
        ulong x1 = k1, x2 =k1+k-1;
        while ( x1<x2 )
        {
            swap2( xx_[x1], xx_[x2] );
            jjassert( x1 < k_*b_ );
            jjassert( x2 < k_*b_ );
            ++x1;
            --x2;
        }
    }
}
// -------------------------

#define COND(i, v)  ( (xx_[k+i*k_]!=v)
//
void
all_compositions_minchange::gray_rev(ulong k)
{
    for (ulong v=1; v<n_; v+=2)
//    for (ulong v=0; v<n_; v+=2)
//    for (ulong v=0; v<n_; ++v)
//    ulong v=0;
    {
        ulong i1 = 0;
        while ( i1<b_ )
        {
            while (  COND(i1, v) )
            {
                ++i1;
                if ( i1>=b_ )  goto next;
            }
            ulong i2 = i1;
            while ( ! COND(i2, v) )
            {
                ++i2;
                if ( i2>=b_ )  break;
            }

            rev(i1, i2, k);
            i1 = i2;
        }
    next: ;
    }
}
// -------------------------
#undef COND
#endif  // experimental code

void
all_compositions_minchange::init()
{
    uchar *p = xx_;
    for (ulong j=0; j<b_; ++j)
    {
        for (ulong i=0; i<k_; ++i)  p[i] = cl_.x_[i];
        cl_.next();
        p += k_;
    }

//    for (ulong k=0; k<k_; ++k)
    for (ulong k=k_-1; k>1; --k)
    {
//        for (ulong j=0; j<b_; ++j)  { print(j); cout << endl; }
//        cout << " --------------- " << endl;

        gray(k);
//        gray_rev(k);
    }

    x_ = xx_;
}
// -------------------------



void
all_compositions_minchange::print()  const
{
    cout << "   ";
    cout << "x[  ";
    for (ulong j=0; j<k_; ++j)
    {
        ulong x = x_[j];
        if ( x )  cout << x;  else cout << '.';
        cout << "  ";
    }
    cout << "]";


    cout << "    ";
    cout << "d[  ";
    for (ulong j=0; j<k_; ++j)
    {
        ulong x = x_[j];
        while ( x-- )  cout << "1 ";
        if ( j<k_-1 )  cout << ". ";
    }
    cout << " ]";
}
// -------------------------

