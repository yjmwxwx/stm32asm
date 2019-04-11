#!/usr/bin/env bash


if [ $# -lt 1 ]; then
cat <<EOF
 need at least on arg
USAGE:  $0 some.h
 lists *.cc files depending on some.h
 e.g.
  whodep 'auxdouble.h'
  whodep '\bfxt.h\b'
 options:
  -i : only show depending files that directly include the header
  -I : show depending files that do NOT (directly) include the header
EOF
exit 1;
fi

INCL=0  ## show files that depend on header

if [ "$1" = "-i" ]; then
    INCL=1;
    shift;
fi

if [ "$1" = "-I" ]; then
    INCL=2;
    shift;
fi


NNDEP=depend.nn  ## dependency file without linebreaks

function  mknndep
{
    echo "$0: building $NNDEP" 1>&2
    cp depend.mk $NNDEP
    replace -f -q '\.o:' '.cc:' $NNDEP > /dev/null
    replace -f -q ': +[^ ]+.cc' ': ' $NNDEP > /dev/null
    #replace -f -q '\\\\' '%' $NNDEP
    replace -f -q '\\\\\\n' '' $NNDEP > /dev/null
}

########################

if [ -f $NNDEP ];  then
    if [ depend.mk -nt $NNDEP ];  then
        mknndep;
    fi
else
    mknndep;
fi


if [ $# -ge 1 ];  then
    if [ "$INCL" != "0" ]; then

        LIST=$(grep -E $1 $NNDEP  |  cut -d ':' -f1);
#        echo -e "LIST=[[\n$LIST\n]]\n";

        if [ -n "$LIST" ]; then
            EXPR="#include .*$1";
#            echo "EXPR=[[$EXPR]]";
            if [ "$INCL" = "1" ]; then
                grep -E -l "#include .*$1" $LIST;
            else
                grep -E -L "#include .*$1" $LIST;
            fi
        fi

    else
        LINES=$(grep -E $1 $NNDEP);
        echo "$LINES" | cut -d ':' -f1;
#        for LL in "$LINES"; do
#            echo "$LL"  |  cut -d ':' -f1;
#        done
    fi
fi


exit 0;

########################
########################
