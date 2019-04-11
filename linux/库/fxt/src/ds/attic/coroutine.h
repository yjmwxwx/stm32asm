#if !defined HAVE_COROUTINE_H__
#define      HAVE_COROUTINE_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

#define CHECK_STACKS  // define to detect stack overflow
#ifdef CHECK_STACKS
#include "jjassert.h"
#endif // CHECK_STACKS

template <typename Type>
class coroutine
// Helper class to emulate coroutines
{
public:
    ulong *t_;  // sTate stack
    ulong tp_;  // sTate stack Pointer
    Type  *d_;  // Data stack
    ulong dp_;  // Data stack Pointer
    ulong  n_;  // size of stacks

public:
    coroutine(ulong maxdepth)
    {
        n_ = maxdepth;
        t_ = new ulong[n_];
        d_ = new Type[n_];
        init();
    }

    ~coroutine()
    {
        delete [] d_;
        delete [] t_;
    }

    void init()  { dp_=0; tp_=0; }

#ifdef CHECK_STACKS
    void chk_tp(ulong j=0)  const
    {
        ulong t = tp_ - j;
        jjassert( (long)t>=0 );
        jjassert( t<n_ );
    }

    void chk_dp(ulong j=0)  const
    {
        ulong t = dp_ - j;
        jjassert( (long)t>=0 );
        jjassert( t<n_ );
    }
#else  // do not check
#define chk_tp(j) {;}
#define chk_dp(j) {;}
#endif // CHECK_STACKS


    // --- state stack:
    void stpush(ulong x)   { chk_tp();  t_[tp_] = x;  ++tp_; }
    ulong stpeek()  const  { chk_tp(1);  return  t_[tp_-1]; }
    void stpoke(ulong x)   { chk_tp(1);  t_[tp_-1] = x; }
    void stpop(ulong ct=1)  { tp_-=ct; }
    void stnext()  { chk_tp(1);  ++t_[tp_-1]; }
    void stnext(ulong x)  { chk_tp(1);  t_[tp_-1] = x; }
    bool more()  const  { return (tp_!=0); }

    // --- stack for variables and args:
    void push(Type x)  {  chk_dp();  d_[dp_] = x;  ++dp_; }
    Type &peek()  { chk_dp(1); return d_[dp_-1]; }
    void pop(ulong ct=1) { dp_-=ct; }

private:
    coroutine & operator = (const coroutine &);  // forbidden
};
// -------------------------

#undef CHECK_STACKS


#endif // !defined HAVE_COROUTINE_H__
