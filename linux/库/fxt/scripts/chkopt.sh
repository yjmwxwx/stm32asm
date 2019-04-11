#! /usr/bin/env bash

## make sure optimization is turned on for distribution

grep -E '^FXT_CXXFLAGS \+= \$\(OFLAGS\)' makefile >/dev/null  && exit 0;

echo '*** Uncomment the line FXT_CXXFLAGS += $(OFLAGS) near top of makefile ***';

exit 1;
############

