#if !defined HAVE_FUNCEMU_H__
#define      HAVE_FUNCEMU_H__


#include "fxttypes.h"
#include "aux1/copy.h"


#ifdef PARANOIA
#warning  'PARANOIA tests enabled in funcemu.h'
#include "jjassert.h"
#endif // PARANOIA


template <typename Type>
class funcemu
{
public:
    ulong *t_;  // sTate stack
    ulong tp_;  // sTate stack Pointer

    Type  *d_;  // Data stack
    ulong dp_;  // Data stack Pointer

    ulong  nt;  // size of state stack
    ulong  nd;  // size of data stack


public:
    funcemu(ulong maxdepth, ulong ndata)
    {
        nt = maxdepth;
        nd = ndata;
        t_ = new ulong[nt];
        d_ = new Type[nd];
        init();
    }

    ~funcemu()
    {
        delete [] d_;
        delete [] t_;
    }

    void init()  { dp_=0; tp_=0; }

#ifdef PARANOIA
    void chk_tp(ulong j=0)  const
    {
        ulong t = tp_ - j;
        jjassert( (long)t>=0 );
        jjassert( t<nt );
    }

    void chk_dp(ulong j=0)  const
    {
        ulong t = dp_ - j;
        jjassert( (long)t>=0 );
        jjassert( t<nd );
    }
#else
#define chk_tp(j) {;}
#define chk_dp(j) {;}
#endif // PARANOIA

    void stpush(ulong x)   { chk_tp();  t_[tp_] = x;  ++tp_; }
    ulong stpeek()  const  { chk_tp(1);  return  t_[tp_-1]; }
//    void stpeek(ulong &x)  { chk_tp(1);  x = t_[tp_-1]; }
    void stpoke(ulong x)   { chk_tp(1);  t_[tp_-1] = x; }
    void stpop(ulong ct=1)  { tp_-=ct; }

    void stnext()  { chk_tp(1);  ++t_[tp_-1]; }
    void stnext(ulong x)  { chk_tp(1);  t_[tp_-1] = x; }

    bool more()  const  { return (tp_!=0); }


    void push(Type x)  {  chk_dp();  d_[dp_] = x; ++dp_; }
    void push(Type x, Type y)  { push(x); push(y); }
    void push(Type x, Type y, Type z)  { push(x); push(y); push(z); }
    void push(Type x, Type y, Type z, Type u)  { push(x); push(y); push(z); push(u); }

    void npeek(Type &x, ulong n)  { chk_dp(n);  x = d_[dp_-n]; }
    void peek(Type &x)  { npeek(x, 1); }
    void peek(Type &x, Type &y) { npeek(y, 1); npeek(x, 2); }
    void peek(Type &x, Type &y, Type &z) { npeek(z, 1); npeek(y, 2); npeek(x, 3); }
    void peek(Type &x, Type &y, Type &z, Type &u)
    { npeek(u, 1); npeek(z, 2); npeek(y, 3); npeek(x, 4); }

    void npoke(Type &x, ulong n)  { chk_dp(n);  d_[dp_-n] = x; }
    void poke(Type x)  { npoke(x, 1); }
    void poke(Type x, Type y)  { npoke(y, 1); npoke(x, 2); }
    void poke(Type x, Type y, Type z)  { npoke(z, 1); npoke(y, 2); npoke(x, 3); }
    void poke(Type x, Type y, Type z, Type u)
    { npoke(u, 1); npoke(z, 2); npoke(y, 3); npoke(x, 4); }

    void pop(ulong ct=1) { dp_-=ct; }

private:
    funcemu & operator = (const funcemu &);  // forbidden
};
// -------------------------

#undef NDEBUG

#endif // !defined HAVE_FUNCEMU_H__
