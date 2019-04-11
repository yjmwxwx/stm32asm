

id="slow bits aux0 bpol aux1 aux2 ds walsh haar perm comb mod ntt wavelet sort"

#id="aux0 bpol aux1 aux2 ds walsh haar perm comb mod ntt wavelet sort"

for d in $id; do
    echo "========= $d :";
    for h in $d/*.h; do
        b=$(basename $h);
        echo "--------- $b :";
        p='#include ''"'$b'"' ;
        t='#include ''"'$d/$b'"' ;
        echo "p=[$p]" ;
        echo "t=[$t]" ;
        ii=$(grep -E -l "$p" */*.{cc,h});
#        echo "ii=[$ii]" ;
        if test "$ii" = ""; then
            true;
        else
            dd=zz/zz-$(basename $b .h).diff ;
            echo "dd=$dd" ;
            replace -f -d $dd "$p" "$t" $ii;
        fi;

    done;

done;


exit 0;
