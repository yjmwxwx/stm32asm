#! /usr/bin/env bash

echo ' =============== Running several tests ... ==============='

## Warning: MAKEFLAGS is unset below
export MAKEFLAGS='';

#make 1test  TESTSRC=test/test-bits.cc  || exit 1
#exit 0;

#JUST_BITS=1

if test -z ${JUST_BITS}; then
    make 1test  TESTSRC=test/test-include-all.cc  || exit 1
    make 1test  TESTSRC=test/test-fact.cc  || exit 1
    make 1test  TESTSRC=test/test-permute.cc  || exit 1
    make 1test  TESTSRC=test/test-fht.cc  || exit 1
    make 1test  TESTSRC=test/test-fft.cc  || exit 1
    make 1test  TESTSRC=test/test-transforms.cc  || exit 1
    make 1test  TESTSRC=test/test-convolution.cc  || exit 1
    make 1test  TESTSRC=test/test-misc.cc  || exit 1
    make 1test  TESTSRC=test/test-transpose.cc  || exit 1
fi

make 1test  TESTSRC=test/test-bits.cc  || exit 1
#
OLDCXXFLAGS=${CXXFLAGS}
echo "Recompiling everything, disabling asm ... ";
make clobber
CXXFLAGS="${CXXFLAGS} -DDISABLE_BIT_ASM";
make -j4 lib   || exit 1  ## NOTE -j4
make 1test  TESTSRC=test/test-bits.cc CXXFLAGS="${CXXFLAGS}"  || exit 1
#
make clobber
#CXXFLAGS="${CXXFLAGS} -UDISABLE_BIT_ASM";
CXXFLAGS="${OLDCXXFLAGS} -UDISABLE_BIT_ASM";
echo "Recompiling everything, re-enabling asm ... ";
make -j4 lib ## NOTE -j4
#make 1test  TESTSRC=test/test-bits.cc CXXFLAGS="${CXXFLAGS}"  || exit 1
make 1test  TESTSRC=test/test-bits.cc CXXFLAGS="${OLDCXXFLAGS}"  || exit 1

exit

echo ' =============== OK, all passed. ==============='


exit 0;
###########################

