#! /usr/bin/env zsh

## check whether lines "// Cf. [file-name]" point to a real file.

## to be finished

for f in demo/*/*-demo.cc; do
    grep -E '^// Cf\. .+/.+' $f;
done

for f in src/*/*; do
    grep --color -E '^// Cf\. [^/]+$' $f;
done

exit 0;
#####################
