
#include "bitsasm.h"
#include "fxttypes.h"



#if defined  BITS_USE_ASM  // use x86 ASM asm code

#warning 'FYI: using x86-asm for various bit operations'

#if defined  BITS_USE_ASM    // use x86 asm code


#if defined  BITS__ASM_USE_INLINE
#warning 'FYI: using inline asm templates'
#else // BITS__ASM_USE_INLINE
#warning 'FYI: using asm'

#error 'defunct'

void
asm_bsf(ulong *x)
{
 asm("
movl  4 (%esp), %eax
movl  (%eax), %edx
//jnz .LABEL1
//movl  0xffffffff, %edx
//.LABEL1:
bsf   %edx, %edx
movl  %edx, (%eax)
");
}
//------------------------

void
asm_bsr(ulong *x)
{
 asm("
movl  4 (%esp), %eax
movl  (%eax), %edx
//jnz .LABEL2
//movl  0xffffffff, %edx
//.LABEL2:
bsr   %edx, %edx
movl  %edx, (%eax)
");
}
//------------------------
#endif // BITS__ASM_USE_INLINE
#endif // BITS_USE_ASM



#endif // BITS_USE_ASM
