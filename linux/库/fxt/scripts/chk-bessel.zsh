#! /usr/bin/env zsh

## avoid symbols that are stupidly defined to be Bessel functions:

for B in j0 j0f j0l j1 j1f j1l jn jnf jnl y0 y0f y0l y1 y1f y1l yn ynf ynl; do
    grep --color -E '\b'$B'\b' src/*.h;
    grep --color -E '\b'$B'\b' src/*/*.h;
    grep --color -E '\b'$B'\b' src/*/*.cc;
    grep --color -E '\b'$B'\b' demo/*/*.cc;
done

exit 0;
#####################
