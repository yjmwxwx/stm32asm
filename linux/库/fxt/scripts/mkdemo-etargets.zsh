#! /usr/bin/env zsh

test -d demo ||  exit 1

cd demo

dd=$(find ./ -type d -mindepth 1)
echo $dd

for d in ${=dd} ; do
    d=${d/.\/};
    echo " ------------------- dir = $d ";
    cd $d || exit 1
    for f in *-demo.cc *-bench.cc;  do
        echo " -- $f ";

        z="demo/$d";
#        echo $z

        txt="\n";
        txt+="/// Emacs:\n";
        txt+="/// Local Variables:\n";
        txt+="/// MyRelDir: \"$z\"\n";  # <--=
        txt+="/// makefile-dir: \"../../\"\n"
        txt+="/// make-target: \"1demo DSRC=$z/$f\"\n"; # <--=
        txt+="/// make-target2: \"1demo DSRC=$z/$f\"\n"; # <--=
        txt+="/// End:\n";

#        echo -e $txt >> $f; #### 

    done
    cd ..
done



exit 0;
############################
