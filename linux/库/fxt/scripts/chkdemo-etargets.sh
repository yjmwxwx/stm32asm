#! /usr/bin/env bash

## Check Emacs-targets of demos

test -d demo ||  exit 1

shopt -s nullglob

cd demo

dd=$(find ./ -mindepth 1 -type d)
dd=$(find ./ -mindepth 1 -type d)

Q=1;
#for d in ${=dd} ; do
for d in ${dd} ; do

#    if [ $d != "./comb" ]; then continue; fi; ## XXXXXXXXX

    d=${d/.\/};
#    echo " ------------------- dir = $d ";
    cd $d || exit 1
    for f in *-demo.cc *-bench.cc ; do
#        echo " -- $f ";

#        echo -n '.';  ## show progress

        z="demo/$d";
#        echo $z

        str1='^/// MyRelDir: "'$z'"'
        str2='^/// make-target: "1demo DSRC='$z/$f'"'
        str2='^/// make-target2: "1demo DSRC='$z/$f' DEMOFLAGS=-DTIMING"'
#        echo $str1
        q=1;
        grep -E "$str1" $f >/dev/null || q=0;
        grep -E "$str2" $f >/dev/null || q=0;


        if [ $q != "1" ]; then
            Q=0;
            echo -e "\n *** $z/$f  (missing or incorrect Etarget lines) ***";
            txt="\n";
            txt="${txt}/// Emacs:\n";
            txt="${txt}/// Local Variables:\n";
            txt="${txt}/// MyRelDir: \"$z\"\n";  # <--=
            txt="${txt}/// makefile-dir: \"../../\"\n"
            txt="${txt}/// make-target: \"1demo DSRC=$z/$f\"\n"; # <--=
            txt="${txt}/// make-target2: \"1demo DSRC=$z/$f DEMOFLAGS=-DTIMING\"\n"; # <--=
            txt="${txt}/// End:\n";
            echo "Copy and paste this to end of file:";
            echo -e $txt;
        fi

#        echo -e $txt >> $f; ####

    done
    cd ..
done
echo

[ $Q = "1" ] && { echo 'OK.';  exit 0; }
exit 1;

############################
