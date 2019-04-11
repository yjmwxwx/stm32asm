
#include "aux0/sincos.h"


#if defined __GNUC__  // if GNUC
//#  warning "FYI: sincos:  GNU-C"
#endif

#if defined __i386__  // if x86 cpu
//#  warning  "FYI: sincos: x86 CPU"
#endif

//<<
// SINCOS_* #defined in sincos.h

#if !defined SINCOS_AUTOMATIC
//#  warning 'FYI: automatic sincos-code selection was DISABLED in sincos.h'
#else
//#  warning 'FYI: automatic sincos-code selection'
#endif //  !defined SINCOS_AUTOMATIC


#if defined SINCOS_USE_ASM_TEMPLATE
//#  warning "FYI: sincos: x86 asm template sincos"
#endif //  defined SINCOS_USE_ASM_TEMPLATE


#if defined SINCOS_USE_ASM
//#  warning "FYI: sincos: x86 asm sincos"
void
SinCos(double a, double *s, double *c)
{ asm(
      "fldl 4 (%esp)"
      "fsincos"
      "movl 16 (%esp), %eax"
      "fstpl (%eax)"
      "movl 12 (%esp), %eax"
      "fstpl (%eax)"
      "ret"
      );
}
#endif //  defined SINCOS_USE_ASM


#if defined SINCOS_USE_MATHINLINE
//#  warning 'FYI: sincos: inline-math sincos'
#endif

#if defined  SINCOS_USE_C
//#  warning 'FYI: sincos: C sincos'
#endif
//>>
