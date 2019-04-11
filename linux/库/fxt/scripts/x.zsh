#! /usr/bin/env zsh

# ksubset:  needs binary ./bin
for ((n=1;n<=12;n+=1)); do
    echo $n;
    for ((a=1;a<=n;a+=1)); do
        for ((i=0;i<=a;i+=1));do
            ./bin $n $i $a > /dev/null ;
        done;
    done;
done

exit 0;
####################################
