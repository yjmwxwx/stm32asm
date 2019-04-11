#! /usr/bin/env zsh

TMP1=./tmp1
TMP2=./tmp2

rm -f $TMP1
for f in doc/*-doc.txt; do
    grep 'HEADER FILE' $f  | cut -d':' -f1 | cut -d' ' -f5 | sort | uniq >> $TMP1;
done
ls */*.h | sort >  $TMP2
for h in $(cat $TMP2); do grep $h $TMP1 >/dev/null || echo $h; done
rm -f $TMP1 $TMP2

#############################
