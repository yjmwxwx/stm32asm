#! /usr/bin/env zsh

q=0;
FF=''

for f in src/*.h src/*/*.h src/*/*.cc; do
#    echo -n '.';  ## show progress

    ## whether there is a note at all:
#    grep -E '// Copyright (C) 2010 Joerg Arndt' $f >/dev/null;
    grep -E '// Copyright \(C\) .*\b2[0-9]{3}\b Joerg Arndt' $f >/dev/null;
    [[ $? != '0' ]] && { echo; echo "Add copyright notice to file [$f]" 1>&2; exit 1; }
    ## whether note is up to date:
    FDT=$(date +"%Y" -r $f); ## last modification
    grep -E '// Copyright .* \b'"$FDT"'\b Joerg Arndt' $f >/dev/null;
#    [[ $? != '0' ]] && { echo; echo "Update copyright notice in file [$f] to year $FDT" 1>&2; exit 2; }
    [[ $? != '0' ]] &&
    {
        echo;
        echo "Update copyright notice in file [$f] to year $FDT" 1>&2;
        q=1;
        FF=$FF" $f"
    }
done

#echo;
echo $FF
#echo;

exit $q;
#######################

// This file is part of the FXT library.
// Copyright (C) 2099 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.
