#!/usr/bin/env bash

replace -f -d patches/swapr.diff   '\bSwap\('    'swap(' $CH
replace -f -d patches/absr.diff    '\bAbs\('     'abs(' $CH
replace -f -d patches/signr.diff   '\bSign\('    'sign(' $CH
replace -f -d patches/copyr.diff   '\bCopy\('    'copy(' $CH
replace -f -d patches/minr.diff    '\bMin\('     'min(' $CH
replace -f -d patches/maxr.diff    '\bMax\('     'max(' $CH
#replace -f -d patches/sincosr.diff '\bSinCos\('  'sincos(' $CH

exit 0;
#############################

grep -E '\b[A-Z][a-z_]+\(' $CH | grep -v Compl

