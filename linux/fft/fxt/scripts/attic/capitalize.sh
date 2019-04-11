#!/usr/bin/env bash

replace -f -d patches/swap.diff   '\bswap\('    'Swap(' $CH
replace -f -d patches/abs.diff    '\babs\('     'Abs(' $CH
replace -f -d patches/sign.diff   '\bsign\('    'Sign(' $CH
replace -f -d patches/copy.diff   '\bcopy\('    'Copy(' $CH
replace -f -d patches/min.diff    '\bmin\('     'Min(' $CH
replace -f -d patches/max.diff    '\bmax\('     'Max(' $CH
#replace -f -d patches/sincos.diff '\bsincos\('  'SinCos(' $CH

exit 0;
#############################

grep -E '\b[A-Z][a-z_]+\(' $CH | grep -v Compl

